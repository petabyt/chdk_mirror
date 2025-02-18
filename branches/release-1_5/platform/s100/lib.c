#include "platform.h"
#include "platform_palette.h"
#include "lolevel.h"

static char*    frame_buffer[2];

void vid_bitmap_refresh()
{
	extern int full_screen_refresh;
	extern void _ScreenUnlock();
	extern void _ScreenLock();

	full_screen_refresh |= 3;
	_ScreenLock();
	_ScreenUnlock();
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

#define LED_PR 0xC022C30C	// Power LED (@FF15B178 & @FF15B1CC)

void debug_led(int state)
{
	// using power LED, which defaults to on
	// for debugging turn LED off if state is 1 and on for state = 0
	// leaves LED on at end of debugging
    volatile long *p = (void*)LED_PR;
    *p = (*p & 0xFFFFFFCF) | ((state) ? 0x00 : 0x20);
}

// S100 has two 'lights' - Power LED, and AF assist lamp
// Power Led = first entry in table (led 0)
// AF Assist Lamp = second entry in table (led 1)
void camera_set_led(int led, int state, int bright) {
 static char led_table[2]={7,10};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

void shutdown_soft()
{
   _PostLogicalEventForNotPowerType(0x1005,0);
}

void JogDial_CW(void){
	_PostLogicalEventToUI(0x872, 1);  // RotateJogDialRight (levent_table)
}

void JogDial_CCW(void){
	_PostLogicalEventToUI(0x873, 1);  // RotateJogDialLeft (levent_table)
}

void *vid_get_viewport_live_fb() // use sigfinder's address
{
    return vid_get_viewport_fb();
}

// Defined in stubs_min.S
extern int active_bitmap_buffer;
extern char* bitmap_buffer[];

// Y multiplier for cameras with 480 pixel high viewports (CHDK code assumes 240)
int vid_get_viewport_yscale() {
	return 2;
}

int vid_get_viewport_width()
{
    if ((mode_get() & MODE_MASK) == MODE_PLAY)
    {
        return 360;
    }
    extern int _GetVRAMHPixelsSize();
    return _GetVRAMHPixelsSize() >> 1;
}

// viewport width offset table for each image size
// 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
static long vp_xo[5] = { 0, 0, 0, 44, 72 };				// should all be even values for edge overlay

int vid_get_viewport_xoffset()
{
    if ((mode_get() & MODE_MASK) == MODE_PLAY)
    {
        return 0;
    }
    else if (shooting_get_prop(PROPCASE_SHOOTING_MODE) == 16909) // Stitch mode
    {
        return 0;
    }
    else
    {
        return vp_xo[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    }
}

int vid_get_viewport_display_xoffset()
{
    if ((mode_get() & MODE_MASK) == MODE_PLAY)
    {
        return 0;
    }
    else if (shooting_get_prop(PROPCASE_SHOOTING_MODE) == 16909) // Stitch mode
    {
        if (shooting_get_prop(PROPCASE_STITCH_DIRECTION) == 0)      // Direction check
            if (shooting_get_prop(PROPCASE_STITCH_SEQUENCE) == 0)   // Shot already taken?
                return 40;
            else
                return 140;
        else
            if (shooting_get_prop(PROPCASE_STITCH_SEQUENCE) == 0)   // Shot already taken?
                return 140;
            else
                return 40;
    }
    else
    {
        return vp_xo[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    }
}

long vid_get_viewport_height()
{
    if ((mode_get() & MODE_MASK) == MODE_PLAY)
    {
        return 240;
    }
    extern int _GetVRAMVPixelsSize();
    return _GetVRAMVPixelsSize() >> 1;
}

static int vp_yoffset(int stitch)
{
    // viewport height offset table for each image size
    // 0 = 4:3, 1 = 16:9, 2 = 3:2, 3 = 1:1, 4 = 4:5
    static long vp_yo[5] = { 0, 30, 13, 0, 0 };

    int m = mode_get();
    if ((m & MODE_MASK) == MODE_PLAY)
    {
        return 0;
    }
    else if (shooting_get_prop(PROPCASE_SHOOTING_MODE) == 16908) // Stitch mode
    {
        return stitch;
    }
    else if (mode_is_video(m))
    {
        return 30;
    }
    else
    {
	    return vp_yo[shooting_get_prop(PROPCASE_ASPECT_RATIO)];
    }
}

int vid_get_viewport_yoffset()
{
    return vp_yoffset(0);
}

int vid_get_viewport_display_yoffset()
{
    return vp_yoffset(72);
}

// Functions for PTP Live View system
int vid_get_viewport_display_xoffset_proper()   { return vid_get_viewport_display_xoffset() * 2; }
int vid_get_viewport_display_yoffset_proper()   { return vid_get_viewport_display_yoffset() * 2; }
int vid_get_viewport_height_proper()            { return vid_get_viewport_height() * 2; }
int vid_get_viewport_fullscreen_height()        { return 480; }
int vid_get_palette_type()                      { return 5; }
int vid_get_palette_size()                      { return 256 * 4; }

void *vid_get_bitmap_active_buffer()
{
    return bitmap_buffer[active_bitmap_buffer];
}

void *vid_get_bitmap_active_palette()
{
    extern int active_palette_buffer;
    extern char* palette_buffer[];
    void* p = palette_buffer[active_palette_buffer];
    // Don't add offset if value is 0
    if (p) p += 4;
    return p;
}

// Function to load CHDK custom colors into active Canon palette
void load_chdk_palette()
{
    extern int active_palette_buffer;
    // Only load for the standard record and playback palettes
    if ((active_palette_buffer == 0) || (active_palette_buffer == 3))
    {
        int *pal = (int*)vid_get_bitmap_active_palette();
        if (pal && pal[CHDK_COLOR_BASE+0] != 0x33ADF62)
        {
            pal[CHDK_COLOR_BASE+0]  = 0x33ADF62;  // Red
            pal[CHDK_COLOR_BASE+1]  = 0x326EA40;  // Dark Red
            pal[CHDK_COLOR_BASE+2]  = 0x34CD57F;  // Light Red
            pal[CHDK_COLOR_BASE+3]  = 0x373BFAE;  // Green
            pal[CHDK_COLOR_BASE+4]  = 0x34BD6CA;  // Dark Green
            pal[CHDK_COLOR_BASE+5]  = 0x395AB95;  // Light Green
            pal[CHDK_COLOR_BASE+6]  = 0x34766F0;  // Blue
            pal[CHDK_COLOR_BASE+7]  = 0x31250F3;  // Dark Blue
            pal[CHDK_COLOR_BASE+8]  = 0x37F408F;  // Cyan
            pal[CHDK_COLOR_BASE+9]  = 0x3512D5B;  // Magenta
            pal[CHDK_COLOR_BASE+10] = 0x3A9A917;  // Yellow
            pal[CHDK_COLOR_BASE+11] = 0x3819137;  // Dark Yellow
            pal[CHDK_COLOR_BASE+12] = 0x3DED115;  // Light Yellow
            pal[CHDK_COLOR_BASE+13] = 0x0090000;  // Transparent dark grey

            extern char palette_control;
            palette_control = 1;
            vid_bitmap_refresh();
        }
    }
}
