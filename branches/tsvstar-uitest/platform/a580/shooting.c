#define PARAM_FILE_COUNTER      0x38

// DRYOS-Notes:
// propertycase
//   196 - overall brightness (of viewport?)

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {
    {  9, 267, "2.6" }, // without ND
    { 10, 279, "2.8" },
    { 11, 302, "3.2" },
    { 12, 337, "3.5" },
    { 13, 383, "4.0" },
    { 14, 437, "4.5" },
    { 15, 503, "5.0" },
    { 16, 565, "5.5" },
    { 17, 675, "7.1 ND" }, // with ND
    { 18, 705, "7.1 ND" },
    { 19, 763, "8.0 ND" },
    { 20, 850, "9.0 ND" },
    { 21, 965, "10.0 ND" },
    { 22, 1103, "11.0 ND" },
    { 23, 1269, "13.0 ND" },
    { 24, 1425, "14.0 ND" }
};

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
    {  33, 1053, "1/2000",  500 },
};

const ISOTable iso_table[] = {
    { -1,    1, "Auto HI", -1},
    {  0,    0,    "Auto", -1},
    {  1,   80,      "80", -1},
    {  2,  100,     "100", -1},
    {  3,  200,     "200", -1},
    {  4,  400,     "400", -1},
    {  5,  800,     "800", -1},
    {  6, 1600,    "1600", -1},
};

/*
http://www.usa.canon.com/cusa/support/consumer/digital_cameras/powershot_a_series/powershot_a580#Specifications

Shooting Modes
	Auto, Easy, Camera M, Portrait, Landscape,
	Special Scene
		(Foliage, Snow, Beach, Sunset, Fireworks, Night Scene, Aquarium),
	Indoor, Kids & Pets, Night Snapshot, Movie
Movie: 640 x 480 (20 fps/20 fps LP), 320 x 240 (30 fps) available up to 4GB or 60 minutes, 160 x 120 (up to 3 minutes at 15 fps)

canon mode list in @FFE7CFFC in 100c
*/
const CapturemodeMap modemap[] = {
    { MODE_P,                  32772 }, // OK!
    { MODE_LONG_SHUTTER,       32774 }, // OK!
    { MODE_AUTO,               32768 }, // OK!
    { MODE_EASY,               33311 }, // OK!
    { MODE_PORTRAIT,           32781 }, // OK!
    { MODE_LANDSCAPE,          32780 }, // OK!
    { MODE_NIGHT_SNAPSHOT,     32779 }, // OK!
    { MODE_KIDS_PETS,          32784 }, // OK!
    { MODE_INDOOR,             32785 }, // OK!

    { MODE_SCN_NIGHT_SCENE,    16398 }, // OK!
    { MODE_SCN_SUNSET,         16402 }, // OK!
    { MODE_SCN_FOLIAGE,        16403 }, // OK!
    { MODE_SCN_SNOW,           16404 }, // OK!
    { MODE_SCN_BEACH,          16405 }, // OK!
    { MODE_SCN_FIREWORK,       16406 }, // OK!
    { MODE_SCN_AQUARIUM,       16408 }, // OK!

    { MODE_VIDEO_STD,          2599  }, // OK!
    { MODE_VIDEO_COMPACT,      2601  }, // OK!
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

int circle_of_confusion = 5;
