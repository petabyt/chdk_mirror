#include "stubs_asm.h"

DEF(physw_status, 0x44818) // sync with a560 and a630
DEF(physw_run, 0x7980)	// sync with a560 and a630	
DEF(zoom_busy, 0x776E0)	// sync with a560 and a630
DEF(focus_busy, 0x76F6C)	// sync with a630 but not sure 
DEF(playrec_mode, 0xBC3C)	// sync with a560
DEF(FlashParamsTable,0xFFEAC254) // sync with a560 and a630
DEF(canon_menu_active,0x2E18)	// sync with a560 and a630
DEF(canon_shoot_menu_active,0x2795) // not found
DEF(recreview_hold, 0x2588)	// sync with a560 and a630
DEF(movie_status, 0x9BAFC)  
DEF(some_flag_for_af_scan, 0xB92C)
DEF(zoom_status, 0x2650)
DEF(some_f_for_dng, 0x60C8) 
DEF(second_ext_for_dng, 0x60EC) // ".THM"

DEF(levent_table,0xFFE9D378)
DEF(sys_mempart_id, 0x48D0) // calloc
