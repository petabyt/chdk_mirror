#include "platform.h"
#include "lolevel.h"
#include "leds.h"

void shutdown()
{
	// 0xC0220000+0x1C @ FF829C28
	volatile long *p = (void*)0xC022001C;

	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");

	*p = 0x44;

	while(1);
}

// 0x73 @ FF95D974
int get_flash_params_count(void) { return 115; }

void debug_led(int state)
{
	*(int*)LED_PR = state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright)
{
	static char led_table[5]={4,5,7,8,9};
	_LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

void JogDial_CW(void)
{
	_PostLogicalEventForNotPowerType(0x874, 1);  // RotateJogDialRight
}

void JogDial_CCW(void)
{
	_PostLogicalEventForNotPowerType(0x875, 1);  // RotateJogDialLeft
}
