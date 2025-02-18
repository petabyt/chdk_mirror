// Taken from A2000

#define PARAM_FILE_COUNTER      0x38

// DRYOS-Notes:
// propertycase
//   196 - overall brightness (of viewport?)

#include "platform.h"

const ApertureSize aperture_sizes_table[] = {

	// Without ND filter
	{9,  328, "3.2"},
	{10, 331, "3.2"},
	{11, 338, "3.5"},
	{12, 349, "3.5"},
	{13, 364, "3.5"},
	{14, 378, "4"},
	{15, 390, "4"},
	{16, 402, "4.5"},
	{17, 414, "4.5"},
	{18, 427, "4.5"},
	{19, 439, "5"},
	{20, 452, "5"},
	{21, 468, "5.6"},
	{22, 488, "5.6"},
	{23, 500, "5.9"},

	// With ND filter
	{24, 608, "9"},
	{25, 611, "9"},
	{26, 618, "10"},
	{27, 629, "10"},
	{28, 644, "10"},
	{29, 658, "11"},
	{30, 670, "11"},
	{31, 682, "13"},
	{32, 694, "13"},
	{33, 707, "13"},
	{34, 719, "14"},
	{35, 732, "14"},
	{36, 748, "16"},
	{37, 768, "16"},
	{38, 780, "17"}
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
    { -1,    1,   "HI", -1},
    {  0,    0, "Auto", -1},
    {  1,   80,   "80", -1},
    {  2,  100,  "100", -1},
    {  3,  200,  "200", -1},
    {  4,  400,  "400", -1},
    {  5,  800,  "800", -1},
    {  6, 1600, "1600", -1},
};          

/*
http://www.usa.canon.com/consumer/controller?act=ModelInfoAct&fcategoryid=221&modelid=17482#ModelTechSpecsAct
Shooting Modes
	Auto, Easy, P, Portrait, Landscape, 
	Special Scene
		(Night Scene, Foliage, Snow, Beach, Sunset, Fireworks, Aquarium, ISO 3200),
	Indoor, Kids & Pets, Night Snapshot, Movie

Movie: 640 x 480 (30 fps/30 fps LP), 320 x 240 (30 fps) available up to 4GB or 60 minutes per clip, 160 x 120 (15 fps) up to 3 minutes per clip
canon mode list FFEB9B10 in 100c
*/
const CapturemodeMap modemap[] = {
  { MODE_LONG_SHUTTER,       32774 },  // not verified
  { MODE_VIDEO_STD,          2600  },
  { MODE_VIDEO_COMPACT,      2602  },
  { MODE_SCN_AQUARIUM,       16408 },
  { MODE_SCN_SNOW,           16404 },
  { MODE_SCN_FOLIAGE,        16403 },
  { MODE_SCN_SUNSET,         16402 },
  { MODE_SCN_NIGHT_SCENE,    16398 },
  { MODE_SCN_ISO_3200,       16413 },
  { MODE_SCN_FIREWORK,       16406 },
  { MODE_SCN_BEACH,          16405 },
  { MODE_INDOOR,             32785 },
  { MODE_KIDS_PETS,          32784 },
  { MODE_NIGHT_SNAPSHOT,     32779 },
  { MODE_LANDSCAPE,          32780 },
  { MODE_PORTRAIT,           32781 },
  { MODE_AUTO,               32768 },
  { MODE_P,                  32772 },
  { MODE_EASY,               33311 } 
};

#include "../generic/shooting.c"

const int dof_tbl[] = {5800, 6420, 7060, 7700, 8340, 9950, 11550, 13160, 14750, 17150, 19570, 22760, 26750, 30750, 34800};
const int dof_tbl_size = sizeof(dof_tbl)/sizeof(dof_tbl[0]);

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
