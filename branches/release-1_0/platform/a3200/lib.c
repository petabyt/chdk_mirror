#include "platform.h"
#include "lolevel.h"

void shutdown()
{
	volatile long *p = (void*)0xC02200F4;

	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");

	*p = 0x44;  // power off.

	while(1);
}

#define LED_PR 0xC02200F0


void debug_led(int state)
{
 *(int*)LED_PR=state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright) {
 static char led_table[2]={0,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 0xa0;	// Found @0xff994830  a3300is
}

long vid_get_viewport_height()
{
	return 240;
}


long vid_get_bitmap_screen_width()
{
	return 360;
}


long vid_get_bitmap_screen_height()
{
	return 240;
}


long vid_get_bitmap_buffer_width() 
{ 
	return 720; 
}


long vid_get_bitmap_buffer_height() 
{ 
	return 240; 
}


//Have to disable here and add to /sub for 100a 
//cause 100d crashes when in shoot mode trying to access Alt menu.
//Re-Added in /SUB/100a
//---------------------------------------------------------------
/*void vid_bitmap_refresh() {
	
	extern int full_screen_refresh;
	extern void _ScreenUnlock();
	extern void _ScreenLock();

	full_screen_refresh |= 3;
	_ScreenLock();
	_ScreenUnlock();
}*/



