// Camera - ixus870_sd880 - platform_camera.h

// This file contains the various settings values specific to the ixus870_sd880 camera.
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

    #define CAM_DRYOS                       1
    #define CAM_PROPSET                     2

    #define CAM_RAW_ROWPIX                  3720
    #define CAM_RAW_ROWS                    2772

    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_BRACKETING                  1       // XXX
    #define CAM_EXT_TV_RANGE                1
    #define CAM_HAS_JOGDIAL                 1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER               1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_MULTIPART                   1

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                0x40000000 // 0xFF874198 (via ExMem.FreeCacheable
    #define PARAM_CAMERA_NAME               4       // parameter number for GetParameterData

    #define CAM_JPEG_WIDTH                  3648
    #define CAM_JPEG_HEIGHT                 2736
    #define CAM_ACTIVE_AREA_X1              14      // XXX
    #define CAM_ACTIVE_AREA_Y1              8       // XXX
    #define CAM_ACTIVE_AREA_X2              3682    // XXX
    #define CAM_ACTIVE_AREA_Y2              2764    // XXX

    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #define CAM_DNG_LENS_INFO               { 50,10, 200,10, 28,10, 58,10 } // See comments in camera.h
    #define cam_CFAPattern                  0x02010100  // Red  Green  Green  Blue
    #define CAM_COLORMATRIX1                              \
     827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829, 1000000,  530507, 1000000,   50537, 1000000, \
       5181, 1000000,   48183, 1000000,  245014, 1000000    // XXX
    #define cam_CalibrationIlluminant1      1       // Daylight       XXX

    // CHDK functionality
    #define CAM_SHOW_OSD_IN_SHOOT_MENU      1
    #undef  DEFAULT_RAW_EXT
    #define DEFAULT_RAW_EXT                 2       // use .CR2

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_VIDEO_CONTROL                       // XXX

//----------------------------------------------------------

