// Camera - G7x - platform_camera.h

// This file contains the various settings values specific to the G7x camera.
// This file is referenced via the 'include/camera.h' file and should not be loaded directly.

// If adding a new settings value put a suitable default in 'include/camera.h',
// along with documentation on what the setting does and how to determine the correct value.
// If the setting should not have a default value then add it in 'include/camera.h'
// using the '#undef' directive along with appropriate documentation.

// Override any default values with your camera specific values in this file. Try and avoid
// having override values that are the same as the default value.

// When overriding a setting value there are two cases:
// 1. If removing the value, because it does not apply to your camera, use the '#undef' directive.
// 2. If changing the value it is best to use an '#undef' directive to remove the default value
//    followed by a '#define' to set the new value.

// When porting CHDK to a new camera, check the documentation in 'include/camera.h'
// for information on each setting. If the default values are correct for your camera then
// don't override them again in here.

    #define CAM_PROPSET                         7

    #define CAM_AV_OVERRIDE_IRIS_FIX            1   // for cameras that require _MoveIrisWithAv function to override Av (for bracketing).
    #define CAM_HAS_NATIVE_ND_FILTER            1   // Camera has built-in ND filter with Canon menu support for enable/disable
    #define CAM_HAS_ND_FILTER                   1           // Camera has built-in ND filter (in addition to iris)

    #define CAM_BRACKETING                      1 // camera has native bracketing

    #undef  CAM_KEY_PRESS_DELAY
    #define CAM_KEY_PRESS_DELAY                 60          // delay after a press

    #define CAM_ADJUSTABLE_ALT_BUTTON           1

    #define CAM_ALT_BUTTON_NAMES                { "Playback", "Video", "Wifi" }
    #define CAM_ALT_BUTTON_OPTIONS              { KEY_PLAYBACK, KEY_VIDEO, KEY_WIFI}
    #define CAM_DRIVE_MODE_FROM_TIMER_MODE      1

    // default zebra shortcut (left) conflicts with canon AF lock
    #define SHORTCUT_TOGGLE_ZEBRA               KEY_MENU

    #define CAM_DRYOS                           1
    #define CAM_DRYOS_2_3_R39                   1
    #define CAM_DRYOS_2_3_R47                   1

    #define CAM_RAW_ROWPIX                      5632
    #define CAM_RAW_ROWS                        3710

    #define CAM_HAS_CMOS                        1

    // unlocked by default, not needed
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_HAS_VIDEO_BUTTON                1

    #undef  CAM_HAS_DISP_BUTTON
    #undef  CAM_USE_ZOOM_FOR_MF

// not implemented
    #undef  CAM_CHDK_HAS_EXT_VIDEO_MENU
    #undef  CAM_VIDEO_CONTROL

// minimal recording or not only
    #define CAM_SIMPLE_MOVIE_STATUS             1

    #define  CAM_IS_VID_REC_WORKS               1 // Define if the 'is_video_recording()' function works

    #define CAM_HAS_JOGDIAL                     1
    #undef  CAM_USE_ZOOM_FOR_MF

// OK
    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                    0x40000000

    #undef  CAM_CIRCLE_OF_CONFUSION
    #define CAM_CIRCLE_OF_CONFUSION             11  // CoC value for camera/sensor (see http://www.dofmaster.com/digital_coc.html)

// OK
    #define CAM_DNG_LENS_INFO                   { 88,10,368,10,18,10,28,10 }
// OK
    #define cam_CFAPattern                      0x02010100

    #define cam_CalibrationIlluminant1          17

    // from CR2 converted to DNG with adobe DNG converter
    #define CAM_COLORMATRIX1 \
    11125, 10000, -5937, 10000,  355, 10000, \
    -2979, 10000, 10926, 10000, 2360, 10000, \
     -116, 10000,   835, 10000, 6064, 10000

    #define cam_CalibrationIlluminant2          21      // D65

    #define CAM_COLORMATRIX2 \
     9602, 10000, -3823, 10000, -937, 10000, \
    -2984, 10000, 11495, 10000, 1675, 10000, \
     -407, 10000,  1415, 10000, 5049, 10000,

    #define CAM_FORWARDMATRIX1 \
     4264, 10000, 4193, 10000, 1187, 10000, \
     1832, 10000, 7811, 10000,  357, 10000, \
      854, 10000,   16, 10000, 7381, 10000

    #define CAM_FORWARDMATRIX2 \
	 4036, 10000, 4056, 10000, 1551, 10000, \
     1780, 10000, 7757, 10000,  463, 10000, \
      764, 10000,    1, 10000, 7487, 10000

    #define CAM_JPEG_WIDTH                      5472
    #define CAM_JPEG_HEIGHT                     3648

// TODO - from cr2
    #define CAM_ACTIVE_AREA_X1                  132
    #define CAM_ACTIVE_AREA_Y1                  40
    #define CAM_ACTIVE_AREA_X2                  5604
    #define CAM_ACTIVE_AREA_Y2                  3688

    #define PARAM_CAMERA_NAME                   3
// found by calling GetImageFolder with single bits sets
    #define CAM_DATE_FOLDER_NAMING              0x80
    #define CAM_FILE_COUNTER_IS_VAR             1     // file counter is variable file_counter_var in stubs, not a param
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL           12

    // black level appears to be ~512 in normal shooting (ISO125 P or M)
    #undef CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL                     511

// TODO expdrv not implemented, but camera does multi-minute exposures natively
// this allows > 60s in overrid (untested)
    #define CAM_EXT_TV_RANGE                    1

    // TODO actual range untested
    // #undef CAM_EXT_AV_RANGE
    // #define CAM_EXT_AV_RANGE                    ?   // Number of 1/3 stop increments to extend the Av range beyond the Canon default smallest aperture

    #define CAM_SHOW_OSD_IN_SHOOT_MENU          1

    #define DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY   1           // Draw pixels on active bitmap buffer only.
    #define CAM_HAS_DISPLAY_REFRESH_FLAG        1   // 'display_needs_refresh' variable is available to trigger CHDK UI update

    #undef  CAM_BITMAP_WIDTH
    #undef  CAM_BITMAP_HEIGHT
    #undef  CAM_SCREEN_WIDTH
    #undef  CAM_SCREEN_HEIGHT
    #define CAM_BITMAP_WIDTH                    360 // Actual width of bitmap screen in <s>bytes</s> pixels
    #define CAM_BITMAP_HEIGHT                   240 // Actual height of bitmap screen in rows
    #define CAM_SCREEN_WIDTH                    360 // Width of bitmap screen in CHDK co-ordinates (360 or 480)
    #define CAM_SCREEN_HEIGHT                   240 // Height of bitmap screen in CHDK co-ordinates (always 240 on all cameras so far)
    

    #undef  EDGE_HMARGIN
    #define EDGE_HMARGIN                        10

    // doesn't appear to use complicated multi pass or seek in normal cases
    #define CAM_HAS_FILEWRITETASK_HOOK          1
    //#define CAM_FILEWRITETASK_SEEKS             1

    #define CAM_ZEBRA_NOBUF                     1

    #undef  CAMERA_MIN_DIST
    #define CAMERA_MIN_DIST                     50         // Override min subject distance, min get_focus() value using MF
    #undef  CAMERA_MAX_DIST
    #define CAMERA_MAX_DIST                     177552     // Override max subject distance, max get_focus() value at max zoom using MF before it goes to -1


    //#define CAM_CHDK_HAS_EXT_VIDEO_TIME         1

    #undef  CAM_USB_EVENTID
    #define CAM_USB_EVENTID                     0x202       // Levent ID for USB control. Changed in DryOS R49, R50 so needs to be overridable.

//    #define CAM_HAS_MOVIE_DIGEST_MODE           1 

// TODO - haven't checked default values, these seem to work
    #define CAM_NEED_SET_ZOOM_DELAY             300

    #define MKDIR_RETURN_ONE_ON_SUCCESS         1    // mkdir() return 1 on success, 0 on fail.

    #undef  REMOTE_SYNC_STATUS_LED
    // #define REMOTE_SYNC_STATUS_LED              0xC022C30C  // TODO specifies an LED that turns on while camera waits for USB remote to sync
    #define CAM_REMOTE_HDMI_HPD                 1 // Camera supports using HDMI hotplug detect for remote signal
    #define CAM_REMOTE_HDMI_POWER_OVERRIDE      1 // Camera requires HDMI power to be forced on in rec mode
    #define CAM_REMOTE_ANALOG_AV                1 // Camera supports analog AV detect for remote signal
    #define CAM_REMOTE_AtoD_CHANNEL             3 // Camera supports using 3rd battery terminal as well as USB for remote - value = A/D channel to poll
    // g7x - Open circuit = ~4090, 10k ohm = ~1380 (=25c bat temp), 3.5k = ~620 (55c)
    #undef CAM_REMOTE_AtoD_THRESHOLD
    #define CAM_REMOTE_AtoD_THRESHOLD       800 // 3rd battery terminal A/D reading threshold ( lower = 1, higher = 0 )

// crashes with ASSERT!! FocusLensController.c Line 1106 on shoot
//    #define CAM_SD_OVER_IN_AF                   1
    #define CAM_SD_OVER_IN_AFL                  1
    #define CAM_SD_OVER_IN_MF                   1
 
    // "real" to "market" conversion definitions
    #define SV96_MARKET_OFFSET                  0   // market and real appear to be identical on this cam
    #define ISO_MARKET_TO_REAL_MULT         1
    #define ISO_MARKET_TO_REAL_SHIFT        0
    #define ISO_MARKET_TO_REAL_ROUND        0
    #define ISO_REAL_TO_MARKET_MULT         1
    #define ISO_REAL_TO_MARKET_SHIFT        0
    #define ISO_REAL_TO_MARKET_ROUND        0

// AF led, for MD test code
    #undef CAM_AF_LED
    #define CAM_AF_LED                      1

    #define CAM_HAS_CANON_RAW                   1   // has native Canon raw
    #define CAM_CLEAN_OVERLAY                   1

    #define CAM_HAS_WIFI                        1   // Camera has wifi support

//--------------------------------------------------
