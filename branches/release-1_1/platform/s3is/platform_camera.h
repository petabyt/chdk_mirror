// Camera - s3is - platform_camera.h

// This file contains the various settings values specific to the s3is camera.
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
    #define CAM_RAW_ROWS                    2136    // for 6 MP

    #undef  CAM_SYNCH
    #define CAM_SWIVEL_SCREEN               1
    #define CAM_ADJUSTABLE_ALT_BUTTON       1
    #define CAM_ALT_BUTTON_NAMES            { "Shrtcut", "Flash", "Timer", "ISO", "Video" }
    #define CAM_ALT_BUTTON_OPTIONS          { KEY_PRINT, KEY_FLASH, KEY_TIMER, KEY_ISO, KEY_VIDEO }
    #define CAM_MULTIPART                   1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_HAS_VIDEO_BUTTON            1

    #define CAM_DNG_LENS_INFO               { 60,10, 720,10, 27,10, 35,10 } // See comments in camera.h
    // pattern
    #define cam_CFAPattern                  0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                        \
      14062, 10000,   -5199, 10000,   -1446, 10000, \
      -4712, 10000,   12470, 10000,    2243, 10000, \
      -1286, 10000,    2028, 10000,    4836, 10000

    #define cam_CalibrationIlluminant1      17      // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH                  2816
    #define CAM_JPEG_HEIGHT                 2112
    #define CAM_ACTIVE_AREA_X1              44
    #define CAM_ACTIVE_AREA_Y1              8
    #define CAM_ACTIVE_AREA_X2              2884
    #define CAM_ACTIVE_AREA_Y2              2136
    // camera name
    #define PARAM_CAMERA_NAME               3       // parameter number for GetParameterData
    #define CAM_BRACKETING                  1
    #define DNG_EXT_FROM                    ".DPS"

    #define CAM_EXT_TV_RANGE                1
	
//	#define REMOTE_SYNC_STATUS_LED 	0xC0xxyyyy		// specifies an LED that turns on while camera waits for USB remote to sync
	
//----------------------------------------------------------

