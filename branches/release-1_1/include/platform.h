#ifndef PLATFORM_H
#define PLATFORM_H

#include "camera.h"

#define SSID_INVALID (-32767)
#define ASID_INVALID (-32767)

#define MODE_MASK               0x0300
#define MODE_REC                0x0100
#define MODE_PLAY               0x0200

#define MODE_SHOOTING_MASK      0x00FF

/* capture mode constants. These are in their own header for easier sed processing*/
#include "modelist.h"

// converted large macro to function in platform/generic/shooting.c (philmoz July 2011)
extern int mode_is_video(int);
#define MODE_IS_VIDEO(m)    mode_is_video(m)

// return whether video is actually being recorded
extern int is_video_recording();

/* propcase ID constants. These are in their own header files for easier sed processing */
#if CAM_PROPSET == 5
    #include "propset5.h"   // DryOS R50
#elif CAM_PROPSET == 4
    #include "propset4.h"
#elif CAM_PROPSET == 3
    #include "propset3.h"
#elif CAM_PROPSET == 2      // most digic3 cameras
    #include "propset2.h"
#elif CAM_PROPSET == 1      // most digic2 cameras
    #include "propset1.h"
#else
    #error unknown camera processor
#endif

#define MIN_DIST                    CAMERA_MIN_DIST     // Defined in camera.h (can be overridden in platform_camera.h)
#define MAX_DIST                    CAMERA_MAX_DIST     // Defined in camera.h (can be overridden in platform_camera.h)
#define INFINITY_DIST               0xFFFFFFFF          // Value to send to firmware to select 'infinity' focus

//********************
//char * get_debug();
//********************

#define MODE_SCREEN_MASK            0x0C00
#define MODE_SCREEN_OPENED          0x0400
#define MODE_SCREEN_ROTATED         0x0800

// Video recording current status constants, see movie_status variable 
#define VIDEO_RECORD_NEVER_STARTED  0  
#define VIDEO_RECORD_STOPPED        1  
#define VIDEO_RECORD_IN_PROGRESS    4

//Optical & digital zoom status constants, see zoom_status variable 
#define ZOOM_OPTICAL_MIN            1
#define ZOOM_OPTICAL_MAX            2
#define ZOOM_OPTICAL_MEDIUM         3
#define ZOOM_OPTICAL_IN             4
#define ZOOM_OPTICAL_OUT            5
#define ZOOM_OPTICAL_REACHED_MIN    7

#define ZOOM_DIGITAL_MAX            9
#define ZOOM_DIGITAL_MEDIUM         10
#define ZOOM_DIGITAL_IN             11
#define ZOOM_DIGITAL_OUT            12
#define ZOOM_DIGITAL_REACHED_MAX    13

typedef struct {
    unsigned short hackmode;   // platform independent mode values from MODE_xxx enum
    unsigned short canonmode;  // PROPCASE_SHOOTING_MODE value
} CapturemodeMap;

typedef struct {
    short id;       // hacks id
    short prop_id;  // Canons id
    char name[8];
    short shutter_dfs_value; // shutter speed to use dark frame substraction
} ISOTable;

typedef struct {
    short id;       // hacks id
    short prop_id;  // Canons id
    char name[8];
    long usec;
} ShutterSpeed;

typedef struct {
    short id;       // hacks id
    short prop_id;  // Canons id
    char name[8];
} ApertureSize;

typedef struct {
    short av96;
    short dav96;
    short av96_step;
    short tv96;
    short dtv96;
    short tv96_step;
    short sv96;
    short dsv96;
    short sv96_step;
    short iso;
    short diso;
    short iso_step;
    short subj_dist;
    short dsubj_dist;
    short subj_dist_step;
    short shoot_counter;
    short type;
} EXPO_BRACKETING_VALUES;

#define SET_NOW      1
#define SET_LATER    0

#define SHOW_ALWAYS    1
#define SHOW_HALF      2


typedef struct {
    short av96;
    short tv96;
    short sv96;
    short subj_dist;
    short nd_filter;
} PHOTO_PARAM;

typedef struct {
    short hyperfocal_valid;
    short distance_valid;
    int   hyperfocal_distance_1e3;
    int   aperture_value;
    int   focal_length;
    int   subject_distance;
    int   near_limit;
    int   far_limit;
    int   hyperfocal_distance;
    int   depth_of_field;
    int   min_stack_distance;
} DOF_TYPE;

extern DOF_TYPE dof_values;

typedef struct {
    short av96;
    short tv96;
    short sv96;
    short iso;
    short sv96_market;
    short iso_market;
    short bv96_measured;
    short bv96_seted;       //Ev96_internal-Sv96
    short ev96_seted;       //Tv96+Av96
    short ev96_measured;    //Bv96+Sv96
    short dev96;            // Ev96_external-Ev96_internal
    short dev96_canon;      // Canon OverExposure
    int b;                  //average scene luminance 
} EXPO_TYPE;

typedef struct {
    float value;
    char fraction[10];
} shutter_speed;


/******************************************************************/

int get_focal_length(int zp);
int get_effective_focal_length(int zp);
int get_zoom_x(int zp);

/******************************************************************/

long get_tick_count();

void remount_filesystem();
void mark_filesystem_bootable();

/******************************************************************/

short get_parameter_size(long id);
long get_parameter_data(long id, void *buf, long bufsize);
long set_parameter_data(long id, void *buf, long bufsize);

long get_property_case(long id, void *buf, long bufsize);
long set_property_case(long id, void *buf, long bufsize);

long get_file_counter();
long get_exposure_counter();
long get_file_next_counter();
void get_target_dir_name(char*);
#ifndef CAM_DATE_FOLDER_NAMING
    long get_target_dir_num();
#endif
long get_target_file_num();

/******************************************************************/

void kbd_key_press(long key);
void kbd_key_release(long key);
void kbd_key_release_all();
long kbd_is_key_pressed(long key);
long kbd_is_key_clicked(long key);
long kbd_get_pressed_key();
long kbd_get_clicked_key();
long kbd_get_autoclicked_key();
long kbd_use_zoom_as_mf();
long kbd_use_up_down_left_right_as_fast_switch();
void kbd_set_alt_mode_key_mask(long key);
int get_usb_power(int edge);
long get_jogdial_direction(void);
/******************************************************************/

long vid_is_bitmap_shown();
void *vid_get_bitmap_fb();

void *vid_get_viewport_fb();
void *vid_get_viewport_fb_d();
void *vid_get_viewport_live_fb();

void vid_bitmap_refresh();
void vid_turn_off_updates();
void vid_turn_on_updates();

// These define the viewport dimensions both physically and in terms of the CHDK co-ordinate system
// CHDK works in a 360x240 screen dimension / co-ordinate system
extern long vid_get_viewport_height();          // Viewport height in CHDK screen pixels 
extern int vid_get_viewport_width();            // Viewport width in CHDK screen pixels
extern int vid_get_viewport_xoffset();          // X offset of viewport edge relative to the viewport buffer (in CHDK screen pixels)
extern int vid_get_viewport_yoffset();          // Y offset of viewport top relative to the viewport buffer (in CHDK screen pixels)
extern int vid_get_viewport_display_xoffset();  // X offset of viewport edge relative to LCD screen (in CHDK screen pixels)
extern int vid_get_viewport_display_yoffset();  // Y offset of viewport top relative to LCD screen (in CHDK screen pixels)
extern int vid_get_viewport_byte_width();       // Physical width of viewport row in bytes
extern int vid_get_viewport_yscale();           // Y multiplier for cameras with 480 pixel high viewports (CHDK code assumes 240)
extern int vid_get_viewport_image_offset();     // Byte offset from start of viewport memory to first displayed pixel
extern int vid_get_viewport_row_offset();       // Difference between physical width of viewport and displayed width (in bytes)


// PTP Live View functions
// These functions return actual size/offset in pixels of the viewport and bitmap buffers
extern int vid_get_viewport_display_xoffset_proper();   // X Offset (for variable image size)
extern int vid_get_viewport_display_yoffset_proper();   // Y Offset (for variable image size)
extern int vid_get_viewport_width_proper();             // Visible viewport width (for variable image size)
extern int vid_get_viewport_height_proper();            // Visible viewport height (for variable image size)
extern int vid_get_viewport_fullscreen_width();            // Width of screen in buffer pixels
extern int vid_get_viewport_fullscreen_height();           // Height of screen in buffer pixels
extern int vid_get_viewport_buffer_width_proper();      // Physical viewport buffer width in pixels
extern int vid_get_palette_type();                      // Palette type (0 - 3)
extern int vid_get_palette_size();                      // Palette size (in bytes)
extern int vid_get_aspect_ratio();                      // LCD aspect ratio (0 = 4:3 or 1 = 16:9)

extern void *vid_get_viewport_active_buffer();          // Return active live viewport memory address
extern void *vid_get_bitmap_active_buffer();            // Return current active bitmap memory address
extern void *vid_get_bitmap_active_palette();           // Return current palette memory address

#ifdef CAM_LOAD_CUSTOM_COLORS
// Color palette function
extern void load_chdk_palette();
#endif
/******************************************************************/

void *hook_raw_fptr();
void *hook_raw_ret_addr();
char *hook_raw_image_addr();
char *hook_alt_raw_image_addr();
long hook_raw_size();
void hook_raw_install();
void hook_raw_save_complete();

/******************************************************************/

long lens_get_zoom_pos();
void lens_set_zoom_pos(long newpos);
long lens_get_zoom_point();
void lens_set_zoom_point(long newpt);
void lens_set_zoom_speed(long newspd); //for S-series
long lens_get_focus_pos();
long lens_get_focus_pos_from_lens();
void lens_set_focus_pos(long newpos);
long lens_get_target_distance();

/******************************************************************/

int shooting_in_progress();
int shooting_is_flash();
int shooting_is_flash_ready();
short shooting_get_flash_mode();


/******************************************************************/
int shooting_get_user_tv_id();
#if defined(CAM_DRAW_EXPOSITION)
    char* shooting_get_tv_str();
#endif
short shooting_get_tv96_from_shutter_speed(float t);
short shooting_get_tv96();
void shooting_set_tv96(short v, short is_now);
void shooting_set_tv96_direct(short v, short is_now);
void shooting_set_shutter_speed_ubasic(int t, short is_now);
short shooting_get_user_tv96();
void shooting_set_user_tv96(short v);
float shooting_get_shutter_speed_from_tv96(short tv);
float shooting_get_shutter_speed_override_value();
const char * shooting_get_tv_override_value();
const char * shooting_get_tv_bracket_value();
const char * shooting_get_bracket_type();
void shooting_set_user_tv_by_id(int v);
void shooting_set_user_tv_by_id_rel(int v);
const ShutterSpeed *shooting_get_tv_line();
/******************************************************************/
short shooting_get_aperture_sizes_table_size();
short shooting_get_max_aperture_sizes_table_prop_id();
short shooting_get_aperture_from_av96(short av96);
int shooting_get_user_av_id();
#if defined(CAM_DRAW_EXPOSITION)
    char* shooting_get_av_str();
#endif
void shooting_set_user_av_by_id(int v);
short shooting_get_av96();
void shooting_set_av96(short v,short is_now);
void shooting_set_av96_direct(short v, short is_now);
short shooting_get_user_av96();
void shooting_set_user_av96(short v);
void shooting_set_user_av_by_id_rel(int v);
short shooting_get_real_aperture();
short shooting_get_min_real_aperture();
short shooting_get_av96_override_value();
const char * shooting_get_av_bracket_value();
void shooting_set_nd_filter_state(short v, short is_now);
/******************************************************************/
int shooting_get_day_seconds();
int shooting_get_tick_count();
/******************************************************************/
void shooting_set_prop(int id, int v);
int shooting_get_prop(int id);
/******************************************************************/
extern int circle_of_confusion;
/******************************************************************/
extern short shooting_get_is_mode();
extern short shooting_get_resolution();
extern short shooting_get_display_mode();
/******************************************************************/
extern const int zoom_points;
int shooting_get_zoom();
void shooting_set_zoom(int v);
void shooting_set_zoom_rel(int v);
void shooting_set_zoom_speed(int v);
/******************************************************************/
void shooting_set_focus(int v, short is_now);
short shooting_get_focus_mode();
short shooting_get_real_focus_mode();
short shooting_get_focus_state();
short shooting_get_focus_ok();
void shooting_update_dof_values();
int shooting_get_hyperfocal_distance();
int shooting_get_hyperfocal_distance_1e3_f(int av, int fl);
int shooting_get_near_limit_of_acceptable_sharpness();
int shooting_get_far_limit_of_acceptable_sharpness();
int shooting_get_depth_of_field();
int shooting_get_min_stack_distance();
int shooting_get_subject_distance();
int shooting_get_subject_distance_override_value();
int shooting_get_subject_distance_bracket_value();
int shooting_get_subject_distance_override_koef();
int shooting_get_lens_to_focal_plane_width();
short shooting_get_drive_mode();
short shooting_can_focus();
short shooting_get_common_focus_mode();
short shooting_is_infinity_distance();
/******************************************************************/
int shooting_get_iso_mode();
void shooting_set_iso_mode(int v);
short shooting_get_sv96();
short shooting_get_svm96();
short shooting_get_iso_market();
short shooting_get_iso_real();
void shooting_set_iso_real(short iso, short is_now);
//void shooting_set_iso_market(short isom);
//void shooting_set_iso_real_delta_from_base(short diso);
void shooting_set_sv96(short sv96, short is_now);
short shooting_get_iso_override_value();
short shooting_get_iso_bracket_value();
/******************************************************************/
short shooting_get_canon_overexposure_value();
short shooting_get_bv96();
int shooting_get_luminance();
//const char* shooting_get_flash_light_value();
/******************************************************************/
int shooting_get_canon_subject_distance();
int shooting_get_exif_subject_dist();
/******************************************************************/
void shooting_expo_param_override();
void shooting_bracketing(void);

void shooting_video_bitrate_change(int v);
extern int auto_started;
void shooting_tv_bracketing();
void shooting_av_bracketing();
/******************************************************************/
// capture mode functions
// return a CHDK mode enum for a PROPCASE_SHOOTING_MODE value, or 0 if not found
int shooting_mode_canon2chdk(int canonmode);
// return a PROPCASE_SHOOTING_MODE value for a CHDK mode enum value, or -1 if not found. 0 is a valid mode on some cameras.
int shooting_mode_chdk2canon(int hackmode);
// set capture mode from CHDK mode, returns 0 if mode not found or not in rec, otherwise 1
int shooting_set_mode_chdk(int mode);
// set capture mode from PROPCASE_SHOOTING_MODE value. return 0 if not in rec or mode is -1, otherwise 1
int shooting_set_mode_canon(int mode);

// returns 0 if in play, nonzero if rec
int rec_mode_active(void); 

// not used. Right now this is just to preserve code from earlier version of mode_get()
// in case we want to check play/rec switch state in the future.
// WARNING: it isn't known if all variants of this check the switch state or some other bit.
// should return 0 is switch is in play position, non-zero otherwise
//int rec_switch_state(void);

// swivel screen state.
#ifdef CAM_SWIVEL_SCREEN
// 0 not open, non-zero open
int screen_opened(void);
// 0 not rotated, non-zero rotated
int screen_rotated(void);
#endif

/******************************************************************/
void clear_values();
/******************************************************************/

int mode_get();

/******************************************************************/

long stat_get_vbatt();
int get_ccd_temp();
int get_optical_temp();
int get_battery_temp();
long get_vbatt_min();
long get_vbatt_max();
void play_sound(unsigned sound);
void camera_set_raw(int mode);
void camera_set_nr(int mode);
int camera_get_nr();
int camera_get_script_autostart();
void camera_set_script_autostart();
void enter_alt();
void exit_alt();
void camera_shutdown_in_a_second(void);

void disable_shutdown();
void enable_shutdown();

void JogDial_CW(void);
void JogDial_CCW(void);
void change_video_tables(int a, int b);
int get_flash_params_count(void);

/******************************************************************/
void __attribute__((noreturn)) shutdown();
void camera_set_led(int led, int state, int bright);
void debug_led(int state);
/****************************************/
extern int canon_menu_active;
extern char canon_shoot_menu_active;
extern int recreview_hold;

extern int movie_status;
unsigned int movie_reset;
unsigned int GetFreeCardSpaceKb(void);
unsigned int GetTotalCardSpaceKb(void);



int swap_partitions(int new_partition);
unsigned char get_active_partition(void);
int get_part_type(void);
int get_part_count(void);
int is_partition_changed(void);
void create_partitions(void);
extern char * camera_jpeg_count_str();

unsigned int GetJpgCount(void);
unsigned int GetRawCount(void);

void MakeAFScan(void);
extern int movie_status;
extern int zoom_status;
void EnterToCompensationEVF(void);
void ExitFromCompensationEVF(void);

extern void PutInNdFilter();
extern void PutOutNdFilter();
extern long GetCurrentAvValue();
extern long IsStrobeChargeCompleted();
extern void SetCurrentCaptureModeType();
#if CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
extern void UnsetZoomForMovie();
#endif
#ifdef CAM_AV_OVERRIDE_IRIS_FIX
extern int MoveIrisWithAv(short*);
#endif
#if CAM_EV_IN_VIDEO
extern void ExpCtrlTool_StartContiAE(int, int);
extern void ExpCtrlTool_StopContiAE(int, int);
extern short SetAE_ShutterSpeed(short* tv);
#endif

void TurnOnBackLight(void);
void TurnOffBackLight(void);

void wait_until_remote_button_is_released(void);
short shooting_get_ev_correction1();
short shooting_get_ev_correction2();

//image_quality_override
void shooting_set_image_quality(int imq);

int get_ev_video_avail(void);
void set_ev_video_avail(int);
int get_ev_video(void);
void set_ev_video(int);
//dng related
// new version to support DNG double buffer
void reverse_bytes_order2(char* from, char* to, int count);
// convert old version calls to new version (to minimise code changes)
#define reverse_bytes_order(start, count)   reverse_bytes_order2(start,start,count)
void save_ext_for_dng(void);
void change_ext_to_dng(void);
void change_ext_to_default(void);

void DoAFLock(void);
void UnlockAF(void);

void drv_self_hide(void);
void drv_self_unhide(void);

void  PostLogicalEventForNotPowerType(unsigned event, unsigned unk);
void  PostLogicalEventToUI(unsigned event, unsigned unk);
void  SetLogicalEventActive(unsigned event, unsigned state);
void SetScriptMode(unsigned mode);
/*
 call C function with argument list created at runtime.
 See lib/armutil/callfunc.S for documentation
*/
unsigned call_func_ptr(void *func, const unsigned *args, unsigned n_args);

/*
 reboot, optionally loading a different binary
 see lib/armutil/reboot.c for documentation
*/
int reboot(const char *bootfile);

/*
arm cache control
*/
void icache_flush_all(void);
void dcache_clean_all(void);

#define started() debug_led(1)
#define finished() debug_led(0)

#ifdef CAM_CHDK_PTP

typedef struct {
    int code;
    int sess_id;
    int trans_id;
    int num_param;
    int param1;
    int param2;
    int param3;
    int param4;
    int param5;
} PTPContainer;

typedef struct {
    int handle;
    int (*send_data)(int handle, const char *buf, int part_size, int total_size, int, int, int); // (0xFF9F525C), total_size should be 0 except for the first call
    int (*recv_data)(int handle, char *buf, int size, int, int); // (0xFF9F5500)
    int (*send_resp)(int handle, PTPContainer *resp, int zero); // (0xFF9F5688), ixus30/40 needs a third argument, which is always 0
    int (*get_data_size)(int handle); // (0xFF9F5830)
    int (*send_err_resp)(int handle, PTPContainer *resp); // (0xFF9F5784)
    int unknown1; // ???
    int (*f2)(); // ??? (0xFF8D5B24)
    int (*f3)(); // ??? (0xFF8D5B5C)
    // more??
} ptp_data;

typedef int (*ptp_handler)(int, ptp_data*, int, int, int, int, int, int, int, int);

int add_ptp_handler(int opcode, ptp_handler handler, int unknown);

void init_chdk_ptp();
void init_chdk_ptp_task();

typedef struct {
    unsigned size;
    unsigned script_id; // id of script message is to/from 
    unsigned type;
    unsigned subtype;
    char data[];
} ptp_script_msg;
int ptp_script_write_msg(ptp_script_msg *msg);
ptp_script_msg* ptp_script_read_msg(void);
ptp_script_msg* ptp_script_create_msg(unsigned type, unsigned subtype, unsigned datasize, const void *data);
int ptp_script_write_error_msg(unsigned errtype, const char *err);

#endif // CAM_CHDK_PTP

int switch_mode_usb(int mode); // 0 = playback, 1 = record; return indicates success
                               // N.B.: switch_mode only supported when USB is connected

void ExitTask();

// Data returned from GetMemInfo & GetExMemInfo functions stored in this data structure
typedef struct {
    int start_address;
    int end_address;
    int total_size;
    int allocated_size;
    int allocated_peak;
    int allocated_count;
    int free_size;
    int free_block_max_size;
    int free_block_count;
} cam_meminfo;

// Always included for module_inspector
extern void GetMemInfo(cam_meminfo*);
extern int GetExMemInfo(cam_meminfo*);

#ifdef OPT_EXMEM_MALLOC
    extern void exmem_malloc_init(void);
#endif

#ifdef CAM_TOUCHSCREEN_UI
extern unsigned short  touch_screen_x, touch_screen_y;
extern int touch_screen_active;
#endif

unsigned char SetFileAttributes(const char* fn, unsigned char attr);

#ifdef CAM_HAS_GPS
    void GPS_UpdateData();
	extern char * camera_jpeg_current_filename();
	extern char * camera_jpeg_current_latitude();
	extern char * camera_jpeg_current_longitude();
	extern char * camera_jpeg_current_height();
#endif

// debug logging function - see generic wrappers.c to adjust destination
// WARNING fixed length buffer
extern void dbg_printf(char *fmt,...);

//#define DEBUG_LOGGING
// debug with timestamp
#ifdef DEBUG_LOGGING
#define DBGPRINTF(fmt,args...) dbg_printf("%08d DBG:" fmt,get_tick_count(), ##args)
#else
#define DBGPRINTF(...)
#endif

#endif

