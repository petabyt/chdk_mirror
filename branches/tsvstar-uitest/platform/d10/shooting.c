#define PARAM_FILE_COUNTER      0x38 // OK

#include "platform.h"

// These F-numbers are the "mock" values shown by the cam.
// They're linked to FL (zoom) and ND filter.
// aperture_sizes_table[].id is just a serial number.
const ApertureSize aperture_sizes_table[] = { // PROPCASE 23
    {  9, 292, "2.8" }, // zoom 1.0
    { 10, 308, "3.2" }, // zoom 1.2
    { 11, 326, "3.2" }, // etc.
    { 12, 348, "3.5" }, 
    { 13, 375, "4.0" }, 
    { 14, 409, "4.5" },
    { 15, 449, "4.9" },
// The rest are the same physical apertures as above, but with ND:
    { 16, 575, "8.0" },
    { 17, 591, "9.0" },
    { 18, 609, "9.0" },
    { 19, 631, "10.0" },
    { 20, 658, "11.0" },
    { 21, 692, "13.0" },
    { 22, 732, "14.0" },
};

// OLD copied comment!
// TODO copied from 850
// Another set of "mock" values, which can probably
// be derived from the table found at FFB4E258 in FW.
// At the moment, I see no reason to amend it.
const ShutterSpeed shutter_speeds_table[] = {
    { -12, -384, "15", 15000000 },
    { -11, -352, "13", 13000000 },
    { -10, -320, "10", 10000000 },
    {  -9, -288, "8",   8000000 },
    {  -8, -256, "6",   6000000 },
    {  -7, -224, "5",   5000000 },
    {  -6, -192, "4",   4000000 },
    {  -5, -160, "3.2", 3200000 },
    {  -4, -128, "2.5", 2500000 },
    {  -3,  -96, "2",   2000000 },
    {  -2,  -64, "1.6", 1600000 },
    {  -1,  -32, "1.3", 1300000 },
    {   0,    0, "1",   1000000 },
    {   1,   32, "0.8",  800000 },
    {   2,   64, "0.6",  600000 },
    {   3,   96, "0.5",  500000 },
    {   4,  128, "0.4",  400000 },
    {   5,  160, "0.3",  300000 },
    {   6,  192, "1/4",  250000 },
    {   7,  224, "1/5",  200000 },
    {   8,  256, "1/6",  166667 },
    {   9,  288, "1/8",  125000 },
    {  10,  320, "1/10", 100000 },
    {  11,  352, "1/13",  76923 },
    {  12,  384, "1/15",  66667 },
    {  13,  416, "1/20",  50000 },
    {  14,  448, "1/25",  40000 },
    {  15,  480, "1/30",  33333 },
    {  16,  512, "1/40",  25000 },
    {  17,  544, "1/50",  20000 },
    {  18,  576, "1/60",  16667 },
    {  19,  608, "1/80",  12500 },
    {  20,  640, "1/100", 10000 },
    {  21,  672, "1/125",  8000 },
    {  22,  704, "1/160",  6250 },
    {  23,  736, "1/200",  5000 },
    {  24,  768, "1/250",  4000 },
    {  25,  800, "1/320",  3125 },
    {  26,  832, "1/400",  2500 },
    {  27,  864, "1/500",  2000 },
    {  28,  896, "1/640",  1563 },
    {  29,  928, "1/800",  1250 },
    {  30,  960, "1/1000", 1000 },
    {  31,  992, "1/1250",  800 },
    {  32, 1021, "1/1600",  625 },
};

const ISOTable iso_table[] = {
    { -1,     1,    "HI", -1},
    {  0,     0,  "Auto", -1},
    {  1,    80,    "80", -1},
    {  2,   100,   "100", -1},
    {  3,   200,   "200", -1},
    {  4,   400,   "400", -1},
    {  5,   800,   "800", -1},
    {  6,  1600,  "1600", -1},
};          

// TODO setting the DP button as a shortcut to movie in canon menu
// gives a value of (current mode)+1024 while movie is recording, unless
// already in movie mode
/*
http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&tabact=ModelTechSpecsTabAct&fcategoryid=2592&modelid=18332#ModelTechSpecsAct

Shooting Modes
Shooting Modes
	Auto, P, 
	Special Scene 
		(Portrait, Landscape, Night Scene, Foliage, Snow, Beach, Sunset, Fireworks,
		Aquarium, Underwater, ISO 3200, Long Shutter, Indoor, Kids & Pets, 
		Night Snapshot, Color Accent, Color Swap, Stitch Assist), 
	Movie
		640 x 480 (30 fps), 320 x 240 (30 fps) 

canon mode list FFB32F18 in 100a

*/
const CapturemodeMap modemap[] = {
    { MODE_SCN_LONG_SHUTTER,   16390 },
    { MODE_P,                  32772 },
    { MODE_SCN_STITCH,         16906 }, // SCN, either direction
    { MODE_SCN_COLOR_ACCENT,   16923 },
    { MODE_SCN_COLOR_SWAP,     16924 },
    { MODE_SCN_ISO_3200,       16413 },
    { MODE_AUTO,               32768 }, 
    { MODE_SCN_FOLIAGE,        16403 },
    { MODE_SCN_LANDSCAPE,      16396 },
    { MODE_SCN_SUNSET,         16402 },
    { MODE_SCN_PORTRAIT,       16397 },
    { MODE_SCN_NIGHT_SNAPSHOT, 16395 },
    { MODE_SCN_SNOW,           16404 },
    { MODE_SCN_BEACH,          16405 },
    { MODE_SCN_INDOOR,         16401 },
    { MODE_SCN_UNDERWATER,     16407 },
    { MODE_SCN_AQUARIUM,       16408 },
    { MODE_SCN_KIDS_PETS,      16400 },
    { MODE_SCN_FIREWORK,       16406 },
    { MODE_VIDEO_COLOR_ACCENT, 2599  },
    { MODE_VIDEO_STD,          2601  },
    { MODE_VIDEO_COLOR_SWAP,   2600  },

};

#include "../generic/shooting.c"

long get_file_next_counter() {
    return get_file_counter();
}

long get_target_file_num() {
    long n;
    
    n = get_file_next_counter();
    n = (n>>4)&0x3FFF;
    return n;
}

long get_target_dir_num() {
    long n;
    
    n = get_file_next_counter();
    n = (n>>18)&0x3FF;
    return n;
}

// TODO
int circle_of_confusion = 6;

// not used ? -> CAM_DRAW_EXPOSITION
