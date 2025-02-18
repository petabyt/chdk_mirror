// Camera - ixus700_sd500 - platform_camera.h

// This file contains the various settings values specific to the ixus700_sd500 camera.
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

    #define CAM_PROPSET                     1

    #define CAM_RAW_ROWPIX                  3152    // for 7 MP
    #define CAM_RAW_ROWS                    2340    // for 7 MP

    #undef  CAM_CIRCLE_OF_CONFUSION
    #define CAM_CIRCLE_OF_CONFUSION         6   // CoC value for camera/sensor (see http://www.dofmaster.com/digital_coc.html)

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_DRAW_EXPOSITION             1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1
    #undef  CAM_HAS_IS
    #define CAM_MULTIPART                   1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1

    #define CAM_DNG_LENS_INFO               { 77,10, 231,10, 28,10, 49,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1             \
      15265, 1,   -6193,  1,   -1558, 1, \
      -4125, 1,   12116,  1,    2010, 1, \
       -888, 1,    1639,  1,    5220, 1

    #define cam_CalibrationIlluminant1      17      // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH                  3072
    #define CAM_JPEG_HEIGHT                 2304
    #define CAM_ACTIVE_AREA_X1              38
    #define CAM_ACTIVE_AREA_Y1              14
    #define CAM_ACTIVE_AREA_X2              3146
    #define CAM_ACTIVE_AREA_Y2              2338
    // camera name
    #define PARAM_CAMERA_NAME               2       // parameter number for GetParameterData
    #define DNG_EXT_FROM                    ".DPS"

//    #define REMOTE_SYNC_STATUS_LED     0xC0xxyyyy        // specifies an LED that turns on while camera waits for USB remote to sync

    #define CAM_WAIT_FOR_FILESYSTEM         1       // wait for 'file_system_started' on startup

    // "real" to "market" conversion definitions
    #define SV96_MARKET_OFFSET              20          // market-real sv96 conversion value

    // Conversion values for pow(2,-20/96) 'market' to 'real', and pow(2,20/96) 'real' to 'market'
    // Uses integer arithmetic to avoid floating point calculations. Values choses to get as close
    // to the desired multiplication factor as possible within normal ISO range.
    #define ISO_MARKET_TO_REAL_MULT         3545
    #define ISO_MARKET_TO_REAL_SHIFT        12
    #define ISO_MARKET_TO_REAL_ROUND        2048
    #define ISO_REAL_TO_MARKET_MULT         9465
    #define ISO_REAL_TO_MARKET_SHIFT        13
    #define ISO_REAL_TO_MARKET_ROUND        4096

//--------------------------------------------------

    #undef  CAM_DEFAULT_MENU_CURSOR
    #define CAM_DEFAULT_MENU_CURSOR     MAKE_COLOR(COLOR_RED,COLOR_WHITE)  // Override menu cursor colors
