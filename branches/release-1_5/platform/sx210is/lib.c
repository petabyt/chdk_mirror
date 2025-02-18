#include "platform.h"
#include "lolevel.h"

/*
void vid_bitmap_refresh() //ASM1989
{
 extern int enabled_refresh_physical_screen;
 enabled_refresh_physical_screen=1;
 *(int*)0x9D08=3;//this is set somewhere in a function called by RefreshPhysicalScreen, should be easy to find
 _RefreshPhysicalScreen(1);
}

*/


void vid_bitmap_refresh()
{
	extern int enabled_refresh_physical_screen;
	extern int full_screen_refresh;

	// i've tried refreshphysical screen (screen unlock) and that caused the canon and
	// function menu to not display at all. This seems to work and is called in a similar
	// way in other places where original OSD should be refreshed.
	extern void _LockAndRefresh(); // wrapper function for screen lock
	extern void _UnlockAndRefresh(); // wrapper function for screen unlock

	_LockAndRefresh();

	enabled_refresh_physical_screen=1;
	full_screen_refresh=3; //found in ScreenUnlock underneath a CameraLog.c call sub_FFA02598

	_UnlockAndRefresh();
}




void shutdown()
{
	volatile long *p = (void*)0xC022001C;

	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");

	*p = 0x44;  // power off.

	while(1);
}

#define LED_PR 0xC0220130    // -> C0223030 front led ASM1989 08.24.2010 found at  FF8E73F0  in sx200 was FF91E09C


void debug_led(int state)
{
 *(int*)LED_PR=state ? 0x46 : 0x44;
}

void camera_set_led(int led, int state, int bright) {
 static char led_table[5]={4,5,7,8,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 120;
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x876, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x877, 2);  // RotateJogDialLeft
}


//ASm1989 like sx30 testing

// Viewport and Bitmap values that shouldn't change across firmware versions.
// Values that may change are in lib.c for each firmware version.

// Physical width of viewport row in bytes
int vid_get_viewport_byte_width() {
	return 960 * 6 / 4;     // SX210IS - wide screen LCD is 960 pixels wide, each group of 4 pixels uses 6 bytes (UYVYYY)
}

//This cam is 0 -> 16:9,  1 -> 4:3

int vid_get_viewport_width()
{
	// viewport width table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
	//static long vp_w[5] = { 480, 360, 360, 272, 216 };
	
	// 0 = 16:9, 1 = 4:3
	// somehow, prop PROPCASE_ASPECT_RATIO doesn't work
	//static long vp_w[5] =  { 480, 360, 360, 272, 216 };
	//return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
	
	// if widescreen, photo and video modes
	if( ( (shooting_get_prop(PROPCASE_RESOLUTION) == 8) && (!MODE_IS_VIDEO(mode_get())) ) ||
	    ( (MODE_IS_VIDEO(mode_get())) && (shooting_get_prop(PROPCASE_VIDEO_RESOLUTION) == 4) ) )
		return 480;
	else
		return 360;
}

int vid_get_viewport_display_xoffset()
{
	// viewport width offset table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
	//static long vp_w[5] = { 0, 60, 0, 44, 72 };
	
	// 0 = 16:9, 1 = 4:3
	// see vid_get_viewport_width()
	//static long vp_w[5] = { 0, 60, 0, 44, 72 };				// should all be even values for edge overlay
	//return vp_w[shooting_get_prop(PROPCASE_ASPECT_RATIO)];

	// if widescreen, photo and video modes
	if( ( (shooting_get_prop(PROPCASE_RESOLUTION) == 8) && (!MODE_IS_VIDEO(mode_get())) ) ||
	    ( (MODE_IS_VIDEO(mode_get())) && (shooting_get_prop(PROPCASE_VIDEO_RESOLUTION) == 4) ) )
		return 0;
	else
		return 60;
}

long vid_get_viewport_height()
{
	// viewport height table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
	//static long vp_h[5] = { 240, 240, 214, 240, 240 };
	//return vp_h[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
	// is always 240 on sx210is
	return 240;
}

int vid_get_viewport_display_yoffset()
{
	// viewport height offset table for each image size
	// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
	//static long vp_h[5] = { 0, 0, 13, 0, 0 };
	//return vp_h[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
	return 0;
}

int vid_get_viewport_buffer_width_proper()      { return 960; }
int vid_get_palette_type()                      { return 3; }
int vid_get_palette_size()                      { return 256 * 4; }
int vid_get_aspect_ratio()                      { return 1; }
extern int _GetVRAMHPixelsSize();
extern int _GetVRAMVPixelsSize();

int vid_get_viewport_width_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?960:_GetVRAMHPixelsSize();
}

int vid_get_viewport_height_proper() {
    return ((mode_get()&MODE_MASK) == MODE_PLAY)?240:_GetVRAMVPixelsSize();
}

// Defined in stubs_min.S
extern char active_viewport_buffer;
extern void* viewport_buffers[];

void *vid_get_viewport_live_fb()
{
/*
ffb64808: 0x40547700
ffb6480c: 0x405c6000
ffb64810: 0x40644900
ffb64814: 0x409de0d0
ffb64818: 0x417f4030
ffb6481c: 0x41872930
ffb64820: 0x418f1230
ffb64824: 0x4196fb30
*/
    unsigned char buff = active_viewport_buffer;
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return viewport_buffers[buff];
}

void *vid_get_bitmap_active_palette()
{
    extern int active_palette_buffer;
    extern int** palette_buffer_ptr;
    return (palette_buffer_ptr[active_palette_buffer]+0x3);
}
