// Camera - a470 - platform_camera.h

// This file contains the various settings values specific to the a470 camera.
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

    #define CAM_PROPSET                     2
    #define CAM_DRYOS                       1

    #define CAM_RAW_ROWPIX                  3152    // for 7 MP
    #define CAM_RAW_ROWS                    2340    // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ZOOM_LEVER
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE         1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO                 1
    #define CAM_MULTIPART                   1

    #define CAM_DNG_LENS_INFO               { 63,10, 216,10, 30,10, 58,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                              \
     673251, 1000000, -200684, 1000000,  -98680, 1000000, \
    -163638, 1000000,  651247, 1000000,   74004, 1000000, \
      14221, 1000000,   52979, 1000000,  265291, 1000000
    #define cam_CalibrationIlluminant1      1       // Daylight
    // cropping
    #define CAM_JPEG_WIDTH                  3096
    #define CAM_JPEG_HEIGHT                 2324
    #define CAM_ACTIVE_AREA_X1              12
    #define CAM_ACTIVE_AREA_Y1              8
    #define CAM_ACTIVE_AREA_X2              3108
    #define CAM_ACTIVE_AREA_Y2              2332
    // camera name
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData
    #define CAM_STARTUP_CRASH_FILE_OPEN_FIX 1
    #define CAM_EXT_TV_RANGE                1
    #define CAM_DETECT_SCREEN_ERASE         1
    //#define DNG_EXT_FROM                  ".DPS"
//----------------------------------------------------------
