#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "keyboard.h"

/*-----------------------------------------------------------------------------
	kbd.c

	In this file we have to define the key which toggles the <ALT> mode.
	
	e.g. in this file KEY_VIDEO is used to activate/deactivate <ALT> mode.
	line 35: alt_mode_key_mask = 0x00004000
	line 62: { 2, KEY_PRINT		     ,0x00004000 },  //KEY_VIDEO for ALT menu
	
------------------------------------------------------------------------------*/

typedef struct {
	short grp;
	short hackkey;
	long canonkey;
} KeyMap;

long kbd_new_state[3];
static long kbd_prev_state[3];
static long kbd_mod_state[3];

static long last_kbd_key = 0;
static long alt_mode_key_mask = 0x00004000; // KEY_VIDEO
static int usb_power=0;
static int remote_key, remote_count;
static int shoot_counter=0;
extern void _GetKbdState(long*);

#define DELAY_TIMEOUT 10000

#define KEYS_MASK0 (0x00004000|0X00000004)
#define KEYS_MASK1 (0x00000000)
#define KEYS_MASK2 (0x00004000|0x00000300|0x00000100|0x00000080|0x00000040|0x00000010|0x00000020|0x00000004|0x00000008|0x00000002|0x00000001)

#define NEW_SS (0x2000)

#define SD_READONLY_FLAG (0x00020000)
#define SD_READONLY_REG 2

#define USB_REG 2
#define USB_MASK (0x04000000)

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

static KeyMap keymap[] = {
	/* tiny bug: key order matters. see kbd_get_pressed_key() */

	{ 2, KEY_PRINT		     ,0x00004000 },  //KEY_VIDEO for ALT menu
    { 2, KEY_SHOOT_FULL      ,0x00000300 }, // Found @0xff3a8018, levent 0x01
    { 2, KEY_SHOOT_FULL_ONLY ,0x00000200 }, // Found @0xff3a8018, levent 0x01
    { 2, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xff3a8010, levent 0x00
    { 2, KEY_MENU            ,0x00000001 }, // Found @0xff3a7fd0, levent 0x09
    { 2, KEY_SET             ,0x00000002 }, // Found @0xff3a7fd8, levent 0x08
    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xff3a7fe0, levent 0x02
    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xff3a7fe8, levent 0x03
    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xff3a7ff0, levent 0x06
    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xff3a7ff8, levent 0x07
    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xff3a8000, levent 0x05
	{ 2, KEY_DISPLAY         ,0x00000040 },
    { 2, KEY_UP              ,0x00000080 }, // Found @0xff3a8008, levent 0x04
	{ 2, KEY_VIDEO		     , 0x00004000 },
//	{ 2, KEY_PLAYBACK	     , 0x00008000 },
	
    { 0, 0, 0 }
};


long __attribute__((naked)) wrap_kbd_p1_f() ;

void wait_until_remote_button_is_released(void)
{
int count1;
int count2;
int tick,tick2,tick3;
int nSW;
int prev_usb_power,cur_usb_power;
 // ------ add by Masuji SUTO (start) --------------
    static int nMode;
 // ------ add by Masuji SUTO (end)   --------------

asm volatile ("STMFD SP!, {R0-R11,LR}\n"); // store R0-R11 and LR in stack
debug_led(1);
tick = get_tick_count();
tick2 = tick;
static long usb_physw[3];
if (conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable && (!shooting_get_drive_mode()|| ((shooting_get_drive_mode()==2) && state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)))  // synch mode enable so wait for USB to disconnect
  {
// ------ add by Masuji SUTO (start) --------------
        nMode=0;
        usb_physw[2] = 0;                                             // makes sure USB bit is cleared.
        _kbd_read_keys_r2(usb_physw);
        if((usb_physw[2] & USB_MASK)==USB_MASK) nMode=1;
// ------ add by Masuji SUTO (end)   --------------
     if(conf.ricoh_ca1_mode && conf.remote_enable)
     {
	if(shooting_get_drive_mode()==1 && state_shooting_progress == SHOOTING_PROGRESS_PROCESSING){			//continuous-shooting mode
		if(conf.bracket_type>2){
			if(shoot_counter<2) shutter_int=3;
			shoot_counter--;
			}
		else{
			prev_usb_power=0;
			nSW = 0;
			do
				{
				usb_physw[2] = 0;                                             // makes sure USB bit is cleared.
				_kbd_read_keys_r2(usb_physw);
				cur_usb_power = (usb_physw[2] & USB_MASK)==USB_MASK;
				if(cur_usb_power){
					if(!prev_usb_power){
						tick2 = get_tick_count();
						prev_usb_power=cur_usb_power;
						}
					else{
						if((int)get_tick_count()-tick2>1000) {debug_led(0);}
						}
					}
				else{
					if(prev_usb_power){
						tick3 = (int)get_tick_count()-tick2;
						if(nSW==10) {
							if(tick3>50) shutter_int=1;
							nSW=20;
							}
						if(nSW==0 && tick3>0) {
							if(tick3<50) {
							nSW=10;
							}
						else{
							if(tick3>1000) shutter_int=1;
								nSW=20;
							}
						}
						prev_usb_power=cur_usb_power;
						}
					}
				if((int)get_tick_count()-tick >= DELAY_TIMEOUT) {nSW=20;shutter_int=2;}
				}
			 while(nSW<20);
			 }
		} 		//continuous-shooting mode
		else{		//nomal mode
			shoot_counter=0;
			if(conf.bracket_type>2){
				shoot_counter=(conf.bracket_type-2)*2;
				}
        do
           {
         //  _GetKbdState(x);
           usb_physw[2] = 0;
          _kbd_read_keys_r2(usb_physw);
           }

// ------ modif by Masuji SUTO (start) --------------
    while(((((usb_physw[2] & USB_MASK)!=USB_MASK) && (nMode==0)) || (((usb_physw[2] & USB_MASK)==USB_MASK) && (nMode==1))) && ((int)get_tick_count()-tick < DELAY_TIMEOUT));
// ------ modif by Masuji SUTO (end)   --------------
	}
       } // ricoh ca-1 mode

else

       {
         do
          {
         //  _GetKbdState(x);
           usb_physw[2] = 0;
          _kbd_read_keys_r2(usb_physw);
           }
        while((usb_physw[2]&USB_MASK) &&  ((int)get_tick_count()-tick < DELAY_TIMEOUT));

        }

  } // synch enable


if (conf.synch_delay_enable && conf.synch_delay_value>0)       // if delay is switched on and greater than 0
  {
    for (count1=0;count1<conf.synch_delay_value+(conf.synch_delay_coarse_value*1000);count1++) // wait delay_value * 0.1ms
    {
      for (count2=0;count2<1400;count2++)            // delay approx. 0.1ms
        {
        }
     }
  }

debug_led(0);

asm volatile ("LDMFD SP!, {R0-R11,LR}\n"); // restore R0-R11 and LR from stack
}


static void __attribute__((noinline)) mykbd_task_proceed()
{
	while (physw_run){
		_SleepTask(10);

		if (wrap_kbd_p1_f() == 1){ // autorepeat ?
			_kbd_p2_f();
		}
	}
}

void __attribute__((naked,noinline)) mykbd_task()
{
	mykbd_task_proceed();

	_ExitTask();
}


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{
	asm volatile(
        "STMFD   SP!, {R1-R7,LR}\n"
        "MOV     R5, #0\n"	
		"BL      my_kbd_read_keys\n"

		"B       _kbd_p1_f_cont\n" // address is automatically taken from stubs_entry.S
	);

	 return 0; // shut up the compiler
}

void my_kbd_read_keys()
{
	kbd_prev_state[0] = kbd_new_state[0];
	kbd_prev_state[1] = kbd_new_state[1];
	kbd_prev_state[2] = kbd_new_state[2];

	_GetKbdState(kbd_new_state);

	/* Get the rest of the buttons */
	
	_kbd_read_keys_r2(kbd_new_state);
	
	kbd_new_state[2] |=0x00008000;  /// disable the battery door switch


	if (kbd_process() == 0) {
		// leave it alone...
		physw_status[0] = kbd_new_state[0];
		physw_status[1] = kbd_new_state[1];
		physw_status[2] = kbd_new_state[2];

		physw_status[0] |= alt_mode_key_mask;  /// disable the ALT mode button

	}
	else {
		// override keys

		physw_status[0] = (kbd_new_state[0] & (~KEYS_MASK0)) |(kbd_mod_state[0] & KEYS_MASK0);
		physw_status[1] = (kbd_new_state[1] & (~KEYS_MASK1)) | (kbd_mod_state[1] & KEYS_MASK1);
		physw_status[2] = (kbd_new_state[2] & (~KEYS_MASK2)) |(kbd_mod_state[2] & KEYS_MASK2);
	}
	
	// useful for further debugging: print keypress values on display
		// char osd_buf[64];
        // extern long physw_status[3];
        // sprintf(osd_buf, "1:%8x  ", physw_status[0]);
        // draw_txt_string(8, 10, osd_buf, conf.osd_color);

        // sprintf(osd_buf, "2:%8x  ", physw_status[1]);
        // draw_txt_string(8, 11, osd_buf, conf.osd_color);

        // sprintf(osd_buf, "3:%8x  ", physw_status[2]);
        // draw_txt_string(8, 12, osd_buf, conf.osd_color);
		
		
	remote_key = (physw_status[2] & USB_MASK)==USB_MASK;
	if (remote_key) {
		remote_count += 1;
	}
	else if (remote_count) {
		usb_power = remote_count;
		remote_count = 0;
	}

	if (conf.remote_enable) {
		physw_status[2] = physw_status[SD_READONLY_REG] & ~(SD_READONLY_FLAG | USB_MASK);
	} else {
		physw_status[2] = physw_status[SD_READONLY_REG] & ~SD_READONLY_FLAG;
	}
}


void kbd_set_alt_mode_key_mask(long key)
{
	int i;
	for (i=0; keymap[i].hackkey; ++i) {
		if (keymap[i].hackkey == key) {
			alt_mode_key_mask = keymap[i].canonkey;
			return;
		}
	}
}


void kbd_key_press(long key)
{
	int i;

	for (i=0;keymap[i].hackkey;i++){
		if (keymap[i].hackkey == key)
		{
			kbd_mod_state[keymap[i].grp] &= ~keymap[i].canonkey;
			return;
		}
	}
}


void kbd_key_release(long key)
{
	int i;
	for (i=0;keymap[i].hackkey;i++){
		if (keymap[i].hackkey == key){
			kbd_mod_state[keymap[i].grp] |= keymap[i].canonkey;
			return;
		}
	}
}


void kbd_key_release_all()
{
	kbd_mod_state[0] |= KEYS_MASK0;
	kbd_mod_state[1] |= KEYS_MASK1;
	kbd_mod_state[2] |= KEYS_MASK2;
}


long kbd_is_key_pressed(long key)
{
	int i;

	for (i=0;keymap[i].hackkey;i++){
		if (keymap[i].hackkey == key){
			return ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) ? 1:0;
		}
	}
	return 0;
}


long kbd_is_key_clicked(long key)
{
	int i;
	for (i=0;keymap[i].hackkey;i++){
		if (keymap[i].hackkey == key){
			return ((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
			       ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0);
		}
	}
	return 0;
}


long kbd_get_pressed_key()
{
	int i;
	for (i=0;keymap[i].hackkey;i++){
		if ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0){
			return keymap[i].hackkey;
		}
	}
	return 0;
}


long kbd_get_clicked_key()
{
	int i;
	for (i=0;keymap[i].hackkey;i++){
		if (((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
		    ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)) {
			return keymap[i].hackkey;
		}
	}
	return 0;
}


void kbd_reset_autoclicked_key() {
	last_kbd_key = 0;
}


long kbd_get_autoclicked_key() {
	static long last_kbd_time = 0, press_count = 0;
	register long key, t;

	key=kbd_get_clicked_key();
	if (key) {
		last_kbd_key = key;
		press_count = 0;
		last_kbd_time = get_tick_count();
		return key;
	} else {
		if (last_kbd_key && kbd_is_key_pressed(last_kbd_key)) {
			t = get_tick_count();
			if (t-last_kbd_time>((press_count)?175:500)) {
				++press_count;
				last_kbd_time = t;
				return last_kbd_key;
			} else {
				return 0;
			}
		} else {
			last_kbd_key = 0;
			return 0;
		}
	}
}


int get_usb_power(int edge)
{
	int x;

	if (edge) return remote_key;
	x = usb_power;
	usb_power = 0;
	return x;
}


long kbd_use_zoom_as_mf() {
	return 0;
}
