
#include <stdlib.h>

static long alt_mode_key_mask = 0x000001000; // =  KEY_PRINT
static long alt_mode_key_reg  = 2;

#include "../generic/kbd.c"

static KeyMap keymap[] = {
    /* tiny bug: key order matters. see kbd_get_pressed_key()
     * for example
     */
	{ KEY_UP	, 0x00000001 },
	{ KEY_DOWN	, 0x00000002 },
	{ KEY_LEFT	, 0x00000008 },
	{ KEY_RIGHT	, 0x00000004 },
	{ KEY_SET	, 0x00000100 },
	{ KEY_SHOOT_FULL, 0x00000030 }, // note 3 here!
    { KEY_SHOOT_FULL_ONLY, 0x00000020 },
	{ KEY_SHOOT_HALF, 0x00000010 },
	{ KEY_ZOOM_IN	, 0x00000040 },
	{ KEY_ZOOM_OUT	, 0x00000080 },
	{ KEY_MENU	, 0x00000200 },
	{ KEY_DISPLAY	, 0x00000400 },
	{ KEY_PRINT	, 0x00001000 },
	{ KEY_ERASE	, 0x00000800 },
        { KEY_DUMMY	, 0x00001000 },
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

