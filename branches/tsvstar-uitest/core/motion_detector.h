/*

Motion detection module

Author: mx3 (Max Sagaydachny) . win1251 ( ������ ����������� )
Email: win.drivers@gmail.com
Skype: max_dtc
ICQ#: 125-985-663
Country: Ukraine
Sity: Kharkiv

idea: mx3
implementation: mx3

purpose of the module:
 implement 2 uBASIC procedures
   md_detect_changes( columns [in], rows [in], pixel_measure_mode,  )
   md_get_cell_change ( col [in], row [in], val [out] )

explanation:

 - for motion detection used array of YUV pixels which are used to display thumbnail picture on LCD

declaration:

function md_detect_changes ( 

  columns, // input parameter. number of columns to split screen into

  rows, // input parameter. number of rows to split screen into

  pixel_measure_mode, // input parameter.
		// 1 - for Y,
    // 2 for U, - (mx3)not sure if this mode required
    // 3 for V, - (mx3)not sure if this mode required
    // 4 for gray, - (mx3)not sure if this mode required
    // 5 for R, - (mx3)not sure if this mode required
    // 6 for G, - (mx3)not sure if this mode required
    // 7 for B - (mx3)not sure if this mode required
	// 9 for face detection

  detection_timeout, // input parameter. number of millisecnds to abort detection. detected_cells_count will be 0 for timeout condition

  measure_interval, // input parameter. number of milliseconds between comparison of two pictures

  threshold, // input parameter. difference value for which procedure will trigger detection of changes

  draw_grid, // boolean input parameter. 
             // true(1) to draw grid(detected sectors/cells).
             // false(0) - to not display grid/detected sectors

  detected_cells_count, // output parameter. count of cells where pixel values differs enough to trigger motion detection

// clipping. allows to exclude some region from mtion detection triggering
// or use onli selected area to make motion detection
// I'm not sure that following parameters are required but using them anyway

  clipping_region_mode, // input parameter.
			// 0 no clipping regions
      // 1 - for excluding selected region from motion detection 
      // 2 - use this only region to make motion detection
  clipping_region_column1, // input parameter.
  clipping_region_row1, // input parameter. 
   // this is top-left corner of clipping region 

  clipping_region_column2, // input parameter.
  clipping_region_row2, // input parameter.
	 // this is right bottom corner of clipping region
)

function md_get_cell_diff ( 
  col [in], // column of the cell we are requesting
  row [in], // row of the cell we are requesting
  val [out] // value of difference between measurements
)

*/

#ifndef __MOTION_DETECTOR__
#define __MOTION_DETECTOR__

#include "../include/platform.h"
#include "../include/stdlib.h"

#define MOTION_DETECTOR_CELLS 1024

struct libmotiondetect_sym {
	int version;

    void (*md_close_motion_detector)();
    int (*md_init_motion_detector)(
         int columns,
         int rows,
         int pixel_measure_mode,
         int detection_timeout,
         int measure_interval,
         int threshold,
         int draw_grid,
         int clipping_region_mode,
         int clipping_region_column1,
         int clipping_region_row1,
         int clipping_region_column2,
         int clipping_region_row2,
         int parameters,
         int pixels_step,
         int msecs_before_trigger
    );

    int (*md_detect_motion)(void);
    int (*md_get_cell_diff)(int column, int row);
    void (*md_draw_grid)();
    int (*md_get_result)();
};

//-------------------------------------------------------------------
// Defines of exported to chdk symbols
#ifdef THIS_IS_CHDK_CORE
	// This section is for CHDK core
	extern struct libmotiondetect_sym* libmotiondetect;
    extern struct libmotiondetect_sym* module_mdetect_load();		// 0fail, addr-ok
    extern void module_mdetect_unload();
#else
	// This section is for module

extern void md_close_motion_detector();

extern int md_init_motion_detector(

 int columns, // input parameter. number of columns to split screen into

 int rows, // input parameter. number of rows to split screen into

 int pixel_measure_mode, // input parameter.
		// 1 - for Y,
    // 2 for U, - (mx3)not sure if this mode required
    // 3 for V, - (mx3)not sure if this mode required
    // 4 for gray, - (mx3)not sure if this mode required
    // 5 for R, - (mx3)not sure if this mode required
    // 6 for G, - (mx3)not sure if this mode required
    // 7 for B - (mx3)not sure if this mode required
	// 9 for face detection

 int detection_timeout, // input parameter. number of millisecnds to abort detection. detected_cells_count will be 0 for timeout condition

 int measure_interval, // input parameter. number of milliseconds between comparison of two pictures

 int threshold, // input parameter. difference value for which procedure will trigger detection of changes

 int draw_grid, // boolean input parameter. 
             // true(1) to draw grid(detected sectors/cells).
             // false(0) - to not display grid/detected sectors

// clipping. allows to exclude some region from mtion detection triggering
// or use onli selected area to make motion detection
// I'm not sure that following parameters are required but using them anyway

 int clipping_region_mode, // input parameter.
			// 0 no clipping regions
      // 1 - for excluding selected region from motion detection 
      // 2 - use this only region to make motion detection
 int clipping_region_column1, // input parameter.
 int clipping_region_row1, // input parameter. 
   // this is top-left corner of clipping region 

 int clipping_region_column2, // input parameter.
 int clipping_region_row2, // input parameter.
	 // this is right bottom corner of clipping region
 int parameters,
 int pixels_step,
 int msecs_before_trigger
);

extern int md_detect_motion(void);
extern int md_get_cell_diff(int column, int row);
extern void md_draw_grid();
extern int md_get_result();

#endif

#endif






 

