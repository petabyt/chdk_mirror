#include "platform.h"

char *hook_raw_image_addr() 
{
	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at FF45516C used in sub_FF0DDADC
	// [0x3188 + 0xC] --> defines which buffer is active
	
    if (*((int*)(0x3188 + 0xC)) != 0)       //loc_ff07154c: 0x3188 (@FF071550 ) + 0xC (@FF07157C)
        return (char*) 0x4ADB54A0;
    else
        return (char*) 0x44000000;          
}

char *hook_alt_raw_image_addr() {
    if (*((int*)(0x3188 + 0xC)) == 0)
        return (char*) 0x4ADB54A0;
    else
        return (char*) 0x44000000;
}

char *camera_jpeg_current_filename() {
     return (void*)0xD922C;                 //@ FF22FADC search for  "%03d-%04d"  sx230:0xCA818
}

//Found by finsig sx240hs 100c
//void *vid_get_bitmap_fb()        { return (void*)0x406c5000; }             // Found @0xff047848
//void *vid_get_viewport_fb()      { return (void*)0x4081ab80; }             // Found @0xff3e3784
void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2ec0+0x54)); } // Found @0xff062d0c & 0xff062d44
char *camera_jpeg_count_str()    { return (char*)0x000dd3b4; }             // Found @0xff26fe7c
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff1f401c

char *camera_jpeg_current_gps() {
    return (void*)0xD92A0;
}
