// Camera - ixus65_sd630 - platform_camera.h

// This file contains the various settings values specific to the ixus65_sd630 camera.
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

    #define CAM_RAW_ROWPIX                  2888    // for 6 MP
    #define CAM_RAW_ROWS                    2136   // for 6 MP

    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Print", "Display" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_DISPLAY }

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_HAS_HI_ISO_AUTO_MODE        1
    #define CAM_DRAW_EXPOSITION             1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_FEATURE_FEATHER             1

    #undef  CAM_HAS_IS
    #undef  CAM_CHDK_HAS_EXT_VIDEO_MENU

    #define CAM_DNG_LENS_INFO               { 58,10, 174,10, 28,10, 49,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                              \
     783384, 1000000, -227078, 1000000, -127919, 1000000, \
    -181247, 1000000,  661743, 1000000,   58868, 1000000, \
      25727, 1000000,   43891, 1000000,  247655, 1000000

    #define cam_CalibrationIlluminant1      1       // Daylight
    // cropping
    #define CAM_JPEG_WIDTH                  2816
    #define CAM_JPEG_HEIGHT                 2112
    #define CAM_ACTIVE_AREA_X1              44
    #define CAM_ACTIVE_AREA_Y1              8
    #define CAM_ACTIVE_AREA_X2              2884
    #define CAM_ACTIVE_AREA_Y2              2136
    // camera name
    #define PARAM_CAMERA_NAME               3       // parameter number for GetParameterData
    #define DNG_EXT_FROM                    ".DPS"

//    #define REMOTE_SYNC_STATUS_LED     0xC0xxyyyy        // specifies an LED that turns on while camera waits for USB remote to sync

    // Keyboard repeat and initial delays
    #undef  KBD_REPEAT_DELAY
    #define KBD_REPEAT_DELAY                140
    #undef  KBD_INITIAL_DELAY
    #define KBD_INITIAL_DELAY               300

    #define CAM_SD_OVER_IN_AF               1
    #define CAM_SD_OVER_IN_AFL              1
    #define CAM_SD_OVER_IN_MF               1

//--------------------------------------------------

    #undef  CAM_DEFAULT_MENU_CURSOR_BG
    #undef  CAM_DEFAULT_MENU_CURSOR_FG
    #define CAM_DEFAULT_MENU_CURSOR_BG  IDX_COLOR_RED      // Override menu cursor colors
    #define CAM_DEFAULT_MENU_CURSOR_FG  IDX_COLOR_WHITE    // Override menu cursor colors
