#ifndef CONF_H
#define CONF_H

#include "gui.h"
#include "script.h"

typedef struct {
    unsigned short  x, y;
} OSD_pos;

typedef struct {
    int save_raw;
    int raw_in_dir;
    int raw_prefix;
    int raw_ext;
    int raw_save_first_only; //for series shooting
    int raw_nr;

    int show_osd;
    int script_shoot_delay;
    int show_histo;
    int ubasic_vars[SCRIPT_NUM_PARAMS];
    char script_file[100];

    int show_dof;
    int batt_volts_max;
    int batt_volts_min;
    int batt_step_25;
    int batt_perc_show;
    int batt_volts_show;
    int batt_icon_show;
    int show_clock;

    int zoom_value;

    int show_state;
    int show_values;
    int show_overexp;

    int histo_mode;
    int histo_auto_ajust;
    int histo_ignore_boundary;
    int histo_layout;

    int zebra_draw;
    int zebra_mode;
    int zebra_restore_screen;
    int zebra_restore_osd;
    int zebra_over;
    int zebra_under;
    int zebra_draw_osd;

    OSD_pos histo_pos;
    OSD_pos dof_pos;
    OSD_pos batt_icon_pos;
    OSD_pos batt_txt_pos;
    OSD_pos mode_state_pos;
    OSD_pos values_pos;
    OSD_pos clock_pos;

    color histo_color;
    color histo_color2; // markers/border
    color osd_color;
    color batt_icon_color;
    color menu_color;
    color reader_color;
    color zebra_color; // under/over
    color grid_color;

    int font_cp;
    char menu_rbf_file[100];

    char lang_file[100];

    char reader_file[100];
    int  reader_pos;
    int  reader_autoscroll;
    int  reader_autoscroll_delay;
    char reader_rbf_file[100];
    int  reader_codepage;
    int  reader_wrap_by_words;

    int sokoban_level;

    int flashlight;
    int splash_show;

    int use_zoom_mf;
    long alt_mode_button; //for S-series
    int alt_prevent_shutdown;

    int show_grid_lines;
    char grid_lines_file[100];
    int grid_force_color;

    int movie_hi_compress;

    int ns_enable_memdump;
} Conf;

extern Conf conf;

#define ALT_PREVENT_SHUTDOWN_NO         0
#define ALT_PREVENT_SHUTDOWN_ALT        1
#define ALT_PREVENT_SHUTDOWN_ALT_SCRIPT 2

#define SHOOTING_PROGRESS_NONE          0
#define SHOOTING_PROGRESS_STARTED       1
#define SHOOTING_PROGRESS_PROCESSING    2
#define SHOOTING_PROGRESS_DONE          3

extern int state_kbd_script_run;
extern int state_shooting_progress;
extern int state_save_raw_nth_only;
extern int state_expos_recalculated;
extern int state_expos_under;
extern int state_expos_over;

extern int state_debug1;
extern int debug_propcase_show;
extern int debug_propcase_page;
extern int debug_vals_show;

extern void conf_save();
extern void conf_restore();
extern void conf_load_defaults();

#endif
