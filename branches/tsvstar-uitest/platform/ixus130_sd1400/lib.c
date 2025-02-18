#include "platform.h"
#include "lolevel.h"

#define LED_IO_G 0xC0220130
#define LED_IO_R 0xC0220134
#define LED_IO_Y 0xC0220134
#define LED_AF   0xC0223030


// Force Screen to refresh like original Firmware
// from SX210, thanks asm1989
void vid_bitmap_refresh() {
    extern int enabled_refresh_physical_screen;
    extern int full_screen_refresh;
 
    // asm1989: i've tried refreshphysical screen (screen unlock) and that caused the canon and
    // function menu to not display at all. This seems to work and is called in a similar
    // way in other places where original OSD should be refreshed.
    extern void _LockAndRefresh();   // wrapper function for screen lock
    extern void _UnlockAndRefresh();   // wrapper function for screen unlock
 
    _LockAndRefresh();
 
    enabled_refresh_physical_screen=1;
    full_screen_refresh=3;   // found in ScreenUnlock underneath a CameraLog.c call
 
    _UnlockAndRefresh();
}

void shutdown() {
  volatile long *p = (void*)0xc022001C; // from task_by (not really complete)

  asm(
    "MRS     R1, CPSR\n"
    "AND     R0, R1, #0x80\n"
    "ORR     R1, R1, #0x80\n"
    "MSR     CPSR_cf, R1\n"
    :::"r1","r0");

  *p = 0x44;

  while (1) {
    asm volatile ("nop\n");
  }
}

int get_flash_params_count(void) { return 0x94; }                          // Found @0xff986190

// based on SX10, values found by experiment
void camera_set_led(int led, int state, int bright) {
  return; // doesn't seem to work
  static char led_table[]={0, // green
                           1, // orange, right
                           2, // yellow, left
                           3, // power
                           // 4,5,6,7,
                           8, // blue
                           9 // af
  };
  if ((unsigned)led < sizeof(led_table)) {
    _LEDDrive(led_table[led], state<=1 ? !state : state);
  }
}

#define DEBUG_LED LED_IO_Y
void debug_led(int state)
{
    * (int *) DEBUG_LED = state ? 0x46 : 0x44;
}

// from sx10
void JogDial_CW(void){
  //_PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
  //_PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}


