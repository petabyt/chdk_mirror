// Camera - sx420is - platform_camera.h

// This file contains the various settings values specific to the sx420is camera.
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

    #define CAM_PROPSET                     10
    #define CAM_DRYOS                       1
    #define CAM_DRYOS_2_3_R39               1 // Defined for cameras with DryOS version R39 or higher
    #define CAM_DRYOS_2_3_R47               1 // Defined for cameras with DryOS version R47 or higher

    #define CAM_RAW_ROWPIX                  5248    
    #define CAM_RAW_ROWS                    3920     

    #define CAM_JPEG_WIDTH                  5152    
    #define CAM_JPEG_HEIGHT                 3864    

    #define CAM_ACTIVE_AREA_X1              8      
    #define CAM_ACTIVE_AREA_Y1              16      
    #define CAM_ACTIVE_AREA_X2              5192 
    #define CAM_ACTIVE_AREA_Y2              3904 

    #undef  CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT                0x40000000     

    #undef CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL       12

    #define CAM_DNG_LENS_INFO               { 43,10, 1806, 10, 35,10, 66,10 } // See comments in camera.h

    #define cam_CFAPattern                  0x02010100 // Red  Green  Green  Blue

    // C&P from ixus175
    #define CAM_COLORMATRIX1                             \
    827547, 1000000, -290458, 1000000, -126086, 1000000, \
    -12829, 1000000,  530507, 1000000,   50537, 1000000, \
      5181, 1000000,   48183, 1000000,  245014, 1000000
    #define cam_CalibrationIlluminant1      1       // Daylight
	
    #define CAM_AV_OVERRIDE_IRIS_FIX            1   // for cameras that require _MoveIrisWithAv function to override Av (for bracketing).

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_MANUAL_FOCUS
	#undef  CAM_HAS_DISP_BUTTON

    #define CAM_HAS_VIDEO_BUTTON                1
    #define CAM_HAS_MOVIE_DIGEST_MODE           1   // camera doesn't actually have digest mode, this is needed by is_video_recording
    #define CAM_IS_VID_REC_WORKS                1   // is_video_recording() function works
    
    #undef  CAM_VIDEO_CONTROL
    #undef  CAM_CHDK_HAS_EXT_VIDEO_MENU


    #undef CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  // unlocked in canon firmware by default

    // MakeDirectory_Fut not found, using mkdir
    #define MKDIR_RETURN_ONE_ON_SUCCESS

    //aspect correction
    #undef  CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION          1
    #undef  CAM_BITMAP_WIDTH
    #define CAM_BITMAP_WIDTH                    720   // Actual width of bitmap screen in bytes
    #undef  CAM_BITMAP_HEIGHT
    #define CAM_BITMAP_HEIGHT                   360   

    #define CAM_ADJUSTABLE_ALT_BUTTON           1

    #define CAM_ALT_BUTTON_NAMES                { "Playback", "Video", "Wifi" }
    #define CAM_ALT_BUTTON_OPTIONS              { KEY_PLAYBACK, KEY_VIDEO, KEY_WIFI }

    
    #undef  CAM_USB_EVENTID
    #define CAM_USB_EVENTID                     0x302 // Levent ID for USB control. Changed in DryOS R58 so needs to be overridable.

    
    #define CAM_DATE_FOLDER_NAMING              0x080    

    #define PARAM_CAMERA_NAME                   3 

    #define CAM_FILE_COUNTER_IS_VAR             1 // file counter is variable file_counter_var in stubs, not a param

    #define CAM_NEED_SET_ZOOM_DELAY             500     // Define to add a delay after setting the zoom position


    #undef CAM_AF_LED
    #define CAM_AF_LED                          1

    #undef  CAM_KEY_PRESS_DELAY
    #define CAM_KEY_PRESS_DELAY                 60  // delay after a press - Required by zoom_in/zoom_out buttons

    #define CAM_SD_OVER_IN_AFL                  1
    #define CAM_SD_OVER_IN_MF                   1

    #define DRAW_ON_ACTIVE_BITMAP_BUFFER_ONLY   1
	
	#define CAM_3ARG_DebugAssert                1
    
//----------------------------------------------------------
    #undef  CAM_DEFAULT_MENU_CURSOR_BG
    #undef  CAM_DEFAULT_MENU_CURSOR_FG
    #define CAM_DEFAULT_MENU_CURSOR_BG  IDX_COLOR_RED      // Override menu cursor colors
    #define CAM_DEFAULT_MENU_CURSOR_FG  IDX_COLOR_WHITE    // Override menu cursor colors
