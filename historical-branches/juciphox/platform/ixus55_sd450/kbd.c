#include "lolevel.h"
#include "platform.h"
#include "conf.h"
#include "core.h"
#include "keyboard.h"

typedef struct {
	long hackkey;
	long canonkey;
} KeyMap;

volatile long *mmio1 = (void*)0xc0220204;

static long kbd_new_state[3];
static long kbd_prev_state[3];
static long kbd_mod_state;
static KeyMap keymap[];
static long last_kbd_key = 0;
static int usb_power=0;
static int remote_key, remote_count;
static int shoot_counter=0;
#define DELAY_TIMEOUT 10000

#define NEW_SS (0x2000)
#define SD_READONLY_FLAG (0x20000)

#define USB_MASK 0x40 
#define USB_REG 1

#ifndef MALLOCD_STACK
static char kbd_stack[NEW_SS];
#endif

long __attribute__((naked)) wrap_kbd_p1_f() ;

long get_mmio(void)
{
long x = (long)*mmio1;	
return x;	
}

void wait_until_remote_button_is_released(void)
{
long x;
int count1;
int count2;
int tick,tick2,tick3;
int nSW;
int prev_usb_power,cur_usb_power;

static int nMode;

asm volatile ("STMFD SP!, {R0-R11,LR}\n"); // store R0-R11 and LR in stack


debug_led(1);
tick=get_tick_count();
tick2 = tick;

 if (conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable && (!shooting_get_drive_mode()|| (shooting_get_drive_mode()==1) || ((shooting_get_drive_mode()==2) && state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)))

  {
if(conf.ricoh_ca1_mode && conf.remote_enable)
{
   nMode=0;
	x=get_mmio();

        if(x&USB_MASK) nMode=1;

} // ricoh_ca1_mode


if(conf.ricoh_ca1_mode && conf.remote_enable)
    {
	if(shooting_get_drive_mode()==1 && state_shooting_progress == SHOOTING_PROGRESS_PROCESSING){			//continuous-shooting mode
		if(conf.bracket_type>2){                          // alternating
			if(shoot_counter<2) shutter_int=3;
			shoot_counter--;
			}
		else{                                              // lighter/darker
			prev_usb_power=0;
			nSW = 0;
			do
				{     
				x=get_mmio();
				cur_usb_power = x&USB_MASK;
				if(cur_usb_power)
                            {
					if(!prev_usb_power)
                                   {
						 tick2 = get_tick_count();
						 prev_usb_power=cur_usb_power;
						}
					   else
                                    {
						 if((int)get_tick_count()-tick2>1000) {debug_led(0);}
						}
					}
				else{
					if(prev_usb_power)
                                {
						tick3 = (int)get_tick_count()-tick2;
						if(nSW==10) 
                                         {
							 if(tick3>50) shutter_int=1;
							 nSW=20;
							}
						if(nSW==0 && tick3>0) 
                                          {
							 if(tick3<50) 
                                             {
							    nSW=10;
							   }
						       else
                                             {
							      if(tick3>1000) shutter_int=1;
								nSW=20;
							    }
						         }
						      prev_usb_power=cur_usb_power;
						}
					  } // else

				           if((int)get_tick_count()-tick >= DELAY_TIMEOUT) {nSW=20;shutter_int=2;}
				      }

			        while(nSW<20);
			 }    // lighter/darker

		  } 		//continuous-shooting mode
 
		 else{		//nomal mode 
			shoot_counter=0;
			if(conf.bracket_type>2)
                       {
				shoot_counter=(conf.bracket_type-2)*2;
				}
           do
             x=get_mmio();

        while(((!(x&USB_MASK) && (nMode==0)) || ((x&USB_MASK) && (nMode==1))) &&  ((int)get_tick_count()-tick < DELAY_TIMEOUT));

}
} // ricoh ca1 mode

else
{
   do
   x=get_mmio();
   while((x&USB_MASK) &&  ((int)get_tick_count()-tick < DELAY_TIMEOUT));
}


if (conf.synch_delay_enable && conf.synch_delay_value>0)                                // if delay is switched on and greater than 0
  {
    for (count1=0;count1<conf.synch_delay_value+(conf.synch_delay_coarse_value*1000);count1++) // wait delay_value * 0.1ms
    {
      for (count2=0;count2<1400;count2++)            // delay approx. 0.1ms
        {
        }
     }
  }
}
debug_led(0);
asm volatile ("LDMFD SP!, {R0-R11,LR}\n"); // restore R0-R11 and LR from stack
}


/*
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
   if (conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable && (!shooting_get_drive_mode()|| (shooting_get_drive_mode()==1) || ((shooting_get_drive_mode()==2) && state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)))                                      
// if (conf.synch_enable && conf.ricoh_ca1_mode && conf.remote_enable && (!shooting_get_drive_mode()|| ((shooting_get_drive_mode()==2) && state_shooting_progress != SHOOTING_PROGRESS_PROCESSING)))   // synch mode enable so wait for USB to disconnect
  {

// ------ add by Masuji SUTO (start) --------------
        nMode=0;
        usb_physw[1] = 0;                                             // makes sure USB bit is cleared.
        _kbd_read_keys_r2(usb_physw);
        if((usb_physw[1] & USB_MASK)==USB_MASK) nMode=1;
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
				usb_physw[1] = 0;                                             // makes sure USB bit is cleared.
				_kbd_read_keys_r2(usb_physw);
				cur_usb_power = (usb_physw[1] & USB_MASK)==USB_MASK;
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
            usb_physw[1] = 0;                                             // makes sure USB bit is cleared.
           _kbd_read_keys_r2(usb_physw);
           }
 //  while(((usb_physw[1] & USB_MASK)==USB_MASK) && ((int)get_tick_count()-tick < DELAY_TIMEOUT));

// ------ modif by Masuji SUTO (start) --------------
        while(((((usb_physw[1] & USB_MASK)!=USB_MASK) && (nMode==0)) || (((usb_physw[1] & USB_MASK)==USB_MASK) && (nMode==1))) && ((int)get_tick_count()-tick < DELAY_TIMEOUT));
// ------ modif by Masuji SUTO (end)   --------------
	}
 }

else
   {

      do
          {
            usb_physw[1] = 0;                                             // makes sure USB bit is cleared.
           _kbd_read_keys_r2(usb_physw);
             
           }
        while((usb_physw[1]&USB_MASK) &&  ((int)get_tick_count()-tick < DELAY_TIMEOUT));
    }

  }

if (conf.synch_delay_enable && conf.synch_delay_value>0)                                // if delay is switched on and greater than 0
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
*/

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
    /* WARNING
     * Stack pointer manipulation performed here!
     * This means (but not limited to):
     *	function arguments destroyed;
     *	function CAN NOT return properly;
     *	MUST NOT call or use stack variables before stack
     *	is setup properly;
     *
     */

    register int i;
    register long *newstack;

#ifndef MALLOCD_STACK
    newstack = (void*)kbd_stack;
#else
    newstack = malloc(NEW_SS);
#endif

    for (i=0;i<NEW_SS/4;i++)
	newstack[i]=0xdededede;

    asm volatile (
	"MOV	SP, %0"
	:: "r"(((char*)newstack)+NEW_SS)
	: "memory"
    );

    mykbd_task_proceed();

    /* function can be modified to restore SP here...
     */

    _ExitTask();
}


long __attribute__((naked,noinline)) wrap_kbd_p1_f()
{

    asm volatile(
                "STMFD   SP!, {R4-R7,LR}\n"
                "SUB     SP, SP, #0xC\n"
                "BL      my_kbd_read_keys\n"
		"B	 _kbd_p1_f_cont\n"
    );
    return 0; // shut up the compiler
}


void my_kbd_read_keys()
{
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    _kbd_pwr_on();

    kbd_fetch_data(kbd_new_state);

#if 0
    if ((new_state[2] & 0x00001000 /* print button */) == 0 )
	started();
    else
	finished();
#endif


    if (kbd_process() == 0){
	// leave it alone...
	physw_status[0] = kbd_new_state[0];
	physw_status[1] = kbd_new_state[1];
	physw_status[2] = kbd_new_state[2];
#if 0
	kbd_mod_state = kbd_new_state[2];
#endif
    } else {
	// override keys
#if 0
	physw_status[2] = kbd_mod_state;
#else
	physw_status[0] = kbd_new_state[0];
	physw_status[1] = kbd_new_state[1];
	physw_status[2] = (kbd_new_state[2] & (~0xaffe)) |
			  (kbd_mod_state & 0xaffe);
#endif
#if defined(USB_MASK) && defined(USB_REG)
remote_key = (kbd_new_state[USB_REG] & USB_MASK)==USB_MASK;

			if (remote_key) 
				remote_count += 1;
			else if (remote_count) {
				usb_power = remote_count;
				remote_count = 0;
			}
		if (conf.remote_enable) {
	physw_status[USB_REG] = kbd_new_state[USB_REG] & ~USB_MASK;
		}
#endif
    }

    _kbd_read_keys_r2(physw_status);
    physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;

    _kbd_pwr_off();

}
int get_usb_power(int edge)
{
	int x;

	if (edge) return remote_key;
	x = usb_power;
	usb_power = 0;
	return x;
}
/****************/


void kbd_key_press(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (keymap[i].hackkey == key){
	    kbd_mod_state &= ~keymap[i].canonkey;
	    return;
	}
    }
}

void kbd_key_release(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (keymap[i].hackkey == key){
	    kbd_mod_state |= keymap[i].canonkey;
	    return;
	}
    }
}

void kbd_key_release_all()
{
    kbd_mod_state |= 0xaffe;
}

long kbd_is_key_pressed(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (keymap[i].hackkey == key){
	    return ((kbd_new_state[2] & keymap[i].canonkey) == 0) ? 1:0;
	}
    }
    return 0;
}

long kbd_is_key_clicked(long key)
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (keymap[i].hackkey == key){
	    return ((kbd_prev_state[2] & keymap[i].canonkey) != 0) &&
		    ((kbd_new_state[2] & keymap[i].canonkey) == 0);
	}
    }
    return 0;
}

long kbd_get_pressed_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if ((kbd_new_state[2] & keymap[i].canonkey) == 0){
	    return keymap[i].hackkey;
	}
    }
    return 0;
}

long kbd_get_clicked_key()
{
    int i;
    for (i=0;keymap[i].hackkey;i++){
	if (((kbd_prev_state[2] & keymap[i].canonkey) != 0) &&
	    ((kbd_new_state[2] & keymap[i].canonkey) == 0)){
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

long kbd_use_zoom_as_mf() {
    static long v;
    static long zoom_key_pressed = 0;

    if (kbd_is_key_pressed(KEY_ZOOM_IN) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
        if (v) {
            kbd_key_release_all();
            kbd_key_press(KEY_RIGHT);
            zoom_key_pressed = KEY_ZOOM_IN;
            return 1;
        }
    } else {
        if (zoom_key_pressed==KEY_ZOOM_IN) {
            kbd_key_release(KEY_RIGHT);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    if (kbd_is_key_pressed(KEY_ZOOM_OUT) && (mode_get()&MODE_MASK) == MODE_REC) {
        get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
        if (v) {
            kbd_key_release_all();
            kbd_key_press(KEY_LEFT);
            zoom_key_pressed = KEY_ZOOM_OUT;
            return 1;
        }
    } else {
        if (zoom_key_pressed==KEY_ZOOM_OUT) {
            kbd_key_release(KEY_LEFT);
            zoom_key_pressed = 0;
            return 1;
        }
    }
    return 0;
}





static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
        {KEY_UP      , 0x00000020 },
        {KEY_DOWN    , 0x00000040 }, 
        {KEY_LEFT    , 0x00000080 }, 
        {KEY_RIGHT   , 0x00000100 },
        {KEY_SET     , 0x00000200 },
        {KEY_SHOOT_HALF, 0x00000002 },
        {KEY_SHOOT_FULL, 0x00000004 },
        {KEY_ZOOM_IN , 0x00000008 },
        {KEY_ZOOM_OUT, 0x00000010 },
        {KEY_MENU    , 0x00000400 },
        {KEY_DISPLAY , 0x00000800 },
        {KEY_PRINT   , 0x00002000 },
        { 0, 0 }
};

void kbd_fetch_data(long *dst)
{
    volatile long *mmio1 = (void*)0xc0220204;
    volatile long *mmio2 = (void*)0xc0220208;

    dst[0] = 0;
    dst[1] = *mmio1;
    dst[2] = *mmio2 & 0xffff;
}

