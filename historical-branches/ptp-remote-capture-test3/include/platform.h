#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef CHDK_MODULE_CODE
#error platform.h cannot be #included in module code.
#endif

#include "camera.h"
#include "keyboard.h"
#include "clock.h"
#include "modes.h"
#include "backlight.h"
#include "viewport.h"
#include "properties.h"
#include "sd_card.h"
#include "meminfo.h"
#include "debug_led.h"
#include "shooting.h"
#include "file_counter.h"
#include "temperature.h"
#include "battery.h"
#include "lens.h"
#include "shutdown.h"
#include "sound.h"
#include "task.h"

/******************************************************************/
    
#if !CAM_DRYOS
extern void drv_self_hide(void);
extern void drv_self_unhide(void);
#endif

/******************************************************************/

/******************************************************************/
#ifdef CAM_HAS_FILEWRITETASK_HOOK
char *hook_yuv_shooting_buf_addr();
int hook_yuv_shooting_buf_width();
int hook_yuv_shooting_buf_height();
#endif
/******************************************************************/
int is_image_save_complete();
/******************************************************************/
//experimental
int register_pt_hooks();
void supported_pt_completefilewrite();
void image_save_completed();
// debug logging function - see generic wrappers.c to adjust destination
// WARNING fixed length buffer
extern void dbg_printf(char *fmt,...);

//#define DEBUG_LOGGING
// debug with timestamp
#ifdef DEBUG_LOGGING
#define DBGPRINTF(fmt,args...) dbg_printf("%08d DBG:" fmt,get_tick_count(), ##args)
#else
#define DBGPRINTF(...)
#endif

#endif

