#include "platform.h"
#include "lolevel.h"

static char*    frame_buffer[2];


void shutdown()
{
    volatile long *p = (void*)0xc022012C; // from S90

    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");

    *p = 0x44;

    while(1);
}


#define LED_GREEN 0xc0220130

void debug_led(int state)
{
    if (state)
		*((long*) LED_GREEN) = 0x46;
    else
		*((long*) LED_GREEN) = 0x44;
}


void camera_set_led(int led, int state, int bright) {
	static char led_table[4]={0,1,9,10};

    _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}


int get_flash_params_count(void){
	return 0x9a;	// found in GetParameterData
}


void vid_bitmap_refresh()
{
	 extern int enabled_refresh_physical_screen; // screen lock counter
	 extern void _ScreenUnlock();

	_ScreenLock();
	enabled_refresh_physical_screen=1;
	_ScreenUnlock();
}


void shutdown_soft()
{
   _PostLogicalEventForNotPowerType(0x1005,0);
}


int vid_get_viewport_width()
{
	return 360;
}

long vid_get_viewport_height()
{
   return 240;

}

// Y multiplier for cameras with 480 pixel high viewports (CHDK code assumes 240)
int vid_get_viewport_yscale() {
	return 2;               // S95 viewport is 480 pixels high
}
