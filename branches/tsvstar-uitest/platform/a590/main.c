#include "camera.h"
#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "stdlib.h"

extern long link_bss_start;
extern long link_bss_end;
extern void boot();


void startup()
{
    long *bss = &link_bss_start;
    long *ptr;

    // sanity check
    if ((long)&link_bss_end > (MEMISOSTART + MEMISOSIZE)){
	started();
	shutdown();
    }
		
    // initialize .bss senment
    while (bss<&link_bss_end)
	*bss++ = 0;


    boot();
}

// Focus length table in firmware @0xfffe29ac
#define NUM_FL      8   // 0 - 7, entries in firmware
#define NUM_DATA    3   // 3 words each entry, first is FL
extern int focus_len_table[NUM_FL*NUM_DATA];

// Conversion factor lens FL --> 35mm equiv
// lens      35mm     CF
// ----      ----     --
// 5.8       35       ( 35/ 5.8) * 58 = 350  (min FL)
// 23.2      140      (140/23.2) * 58 = 350  (max FL)
#define CF_EFL      350
#define	CF_EFL_DIV  58

const int zoom_points = NUM_FL;

int get_effective_focal_length(int zp) {
    return (CF_EFL*get_focal_length(zp))/CF_EFL_DIV;
}

int get_focal_length(int zp) {
    if (zp < 0) zp = 0;
    else if (zp >= NUM_FL) zp = NUM_FL-1;
    return focus_len_table[zp*NUM_DATA];
}

int get_zoom_x(int zp) {
    return get_focal_length(zp)*10/focus_len_table[0];
}

#if 0
int rec_switch_state(void) {
//	mode  = (physw_status[1] & 0x02000000)?MODE_REC:MODE_PLAY;
	return (physw_status[1] & 0x02000000);
}
#endif

long get_vbatt_min()
{
    return 2300;
}

long get_vbatt_max()
{
    return 2550;
}

