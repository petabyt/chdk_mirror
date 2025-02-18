// Camera - sx10 - platform_camera.h

// This file contains the various settings values specific to the sx10 camera.
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

    #define CAM_RAW_ROWPIX                  3720
    #define CAM_RAW_ROWS                    2772

    #define CAM_SWIVEL_SCREEN               1
    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Shrtcut", "Flash", "Video" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_FLASH, KEY_VIDEO }
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_HAS_VIDEO_BUTTON            1
    #define CAM_VIDEO_QUALITY_ONLY          1
    #define CAM_BRACKETING                  1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_MULTIPART                   1
    #define CAM_HAS_JOGDIAL                 1
    #define CAM_HAS_HI_ISO_AUTO_MODE        1
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_UNCACHED_BIT                        // shut up compiler
    #define CAM_UNCACHED_BIT                0x40000000

    #define CAM_DNG_LENS_INFO               { 50,10, 100,10, 28,10, 57,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x02010100 // Red  Green  Green  Blue
    // color

    #define CAM_COLORMATRIX1                              \
     827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829, 1000000,  530507, 1000000,   50537, 1000000, \
       5181, 1000000,   48183, 1000000,  245014, 1000000

    #define cam_CalibrationIlluminant1      1       // Daylight
    // cropping
    #define CAM_JPEG_WIDTH                  3648
    #define CAM_JPEG_HEIGHT                 2736
    #define CAM_ACTIVE_AREA_X1              6
    #define CAM_ACTIVE_AREA_Y1              12
    #define CAM_ACTIVE_AREA_X2              3690
    #define CAM_ACTIVE_AREA_Y2              2772
    // camera name
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData

    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12
    #define CAM_HOTSHOE_OVERRIDE            1

    #define REMOTE_SYNC_STATUS_LED          0xC0220060  // specifies an LED that turns on while camera waits for USB remote to sync

    #define CAM_SD_OVER_IN_AF               1
    #define CAM_SD_OVER_IN_AFL              1
    #define CAM_SD_OVER_IN_MF               1

    #define CAM_IS_VID_REC_WORKS            1   // is_video_recording() function works
    
//--------------------------------------------------

    #undef  CAM_DEFAULT_MENU_CURSOR_BG
    #undef  CAM_DEFAULT_MENU_CURSOR_FG
    #define CAM_DEFAULT_MENU_CURSOR_BG  IDX_COLOR_RED      // Override menu cursor colors
    #define CAM_DEFAULT_MENU_CURSOR_FG  IDX_COLOR_WHITE    // Override menu cursor colors
