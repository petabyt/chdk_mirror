#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "core.h"
#include "conf.h"
#include "gui.h"
#include "font.h"
#include "gui_draw.h"
#include "gui_batt.h"
#include "gui_read.h"
#include "gui_menu.h"
#include "gui_lang.h"

#include "modules.h"
#include "module_load.h"

//-------------------------------------------------------------------

extern void gui_read_kbd_process_menu_btn();
void gui_read_kbd_process();
void gui_read_draw(int enforce_redraw);
void gui_read_kbd_leave();

gui_handler GUI_MODE_READ = 
    /*GUI_MODE_READ*/   { GUI_MODE_MODULE,   gui_read_draw,        gui_read_kbd_process,       gui_read_kbd_process_menu_btn,	0,	GUI_MODE_MAGICNUM };

//-------------------------------------------------------------------
static int read_file;
static int read_file_size;
static int read_on_screen;
static int read_to_draw;
static coord x, y, h, w;
#define READ_BUFFER_SIZE  100
static char buffer[READ_BUFFER_SIZE+1];
static long last_time;
static int xx, yy;
static int pause;

static int reader_is_active;	// Flag raised when reader is succesfully runned
								// purpose: we shouldn't process "leave" sequence if we call unload module but reader was not runed yet

//-------------------------------------------------------------------
static void gui_read_draw_batt() {
    sprintf(buffer, "Batt:%3d%%", get_batt_perc());
    draw_txt_string((camera_screen.width-camera_screen.ts_button_border)/FONT_WIDTH-2-1-1-9, 0, buffer, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
}

//-------------------------------------------------------------------
static void gui_read_draw_clock() {
    static struct tm *ttm;

    ttm = get_localtime();
    sprintf(buffer, "%2u:%02u", ttm->tm_hour, ttm->tm_min);
    draw_txt_string((camera_screen.width-camera_screen.ts_button_border)/FONT_WIDTH-2-1-1-9-2-5, 0, buffer, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE));
}

//-------------------------------------------------------------------
static void gui_read_draw_scroll_indicator() {
    draw_txt_char((camera_screen.width-camera_screen.ts_button_border)/FONT_WIDTH-2, 0, (conf.reader_autoscroll)?((pause)?'\x05':'\x04'):'\x03', MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title infoline
}

//-------------------------------------------------------------------
int gui_read_init(const char* file) {
    static struct STD_stat   st;
    read_file = safe_open(file, O_RDONLY, 0777);
    if (strcmp(file, conf.reader_file)!=0) {
        conf.reader_pos = 0;
        strcpy(conf.reader_file, file);
    }
    read_on_screen = 0;
    read_file_size = (read_file>=0 && safe_stat((char*)file, &st)==0)?st.st_size:0;
    if (read_file_size<=conf.reader_pos) {
        conf.reader_pos = 0;
    }
    pause = 0;
    read_to_draw = 1;
    x=camera_screen.ts_button_border+6; 
    y=FONT_HEIGHT;
    w=camera_screen.width-camera_screen.ts_button_border*2-6-6-8;
    h=camera_screen.height-y;
    last_time = get_tick_count();
    
	reader_is_active=1;    
    gui_set_mode(&GUI_MODE_READ);

    draw_filled_rect(0, 0, camera_screen.width-1, y-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
    draw_filled_rect(0, y, camera_screen.width-1, camera_screen.height-1, MAKE_COLOR(BG_COLOR(conf.reader_color), BG_COLOR(conf.reader_color)));

    gui_read_draw_scroll_indicator();
    gui_read_draw_batt();

    return (read_file >= 0);
}

//-------------------------------------------------------------------
static void read_goto_next_line() {
    draw_filled_rect(xx, yy, x+w-1, yy+rbf_font_height()-1, MAKE_COLOR(BG_COLOR(conf.reader_color), BG_COLOR(conf.reader_color)));
    xx  = x;
    yy += rbf_font_height();
}

//-------------------------------------------------------------------
static int read_fit_next_char(int ch) {
    return (xx+rbf_char_width(ch) < x+w);
}

//-------------------------------------------------------------------
void gui_read_draw(int enforce_redraw) {
    if (conf.reader_autoscroll && !pause && get_tick_count()-last_time >= conf.reader_autoscroll_delay*1000 && (conf.reader_pos+read_on_screen)<read_file_size) {
        conf.reader_pos += read_on_screen;
        read_to_draw = 1;
    }
    if (read_to_draw) {
        int n, i, ii, ll, new_word=1;
        
        xx=x; yy=y;

        lseek(read_file, conf.reader_pos, SEEK_SET);
        read_on_screen=0;

        while (yy<=y+h-rbf_font_height()) {
            n=read(read_file, buffer, READ_BUFFER_SIZE);
            if (n==0) {
                 read_goto_next_line();
                 if (yy < y+h)
                     draw_filled_rect(x, yy, x+w-1, y+h-1, MAKE_COLOR(BG_COLOR(conf.reader_color), BG_COLOR(conf.reader_color)));
                 break;
            }
            i=0;
            while (i<n && yy<=y+h-rbf_font_height()) {
                switch (buffer[i]) {
                    case '\r':
                        new_word = 1;
                        break;
                    case '\n':
                        read_goto_next_line();
                        new_word = 1;
                        break;
                    case '\t':
                        buffer[i] = ' ';
                        // no break here
                    default:
                        if (conf.reader_wrap_by_words) {
                            if (buffer[i] == ' ') {
                                new_word = 1;
                                if (xx==x) //ignore leading spaces
                                    break;
                            } else if (new_word) {
                                new_word = 0;
                                for (ii=i, ll=0; ii<n && buffer[ii]!=' ' && buffer[ii]!='\t' && buffer[ii]!='\r' && buffer[ii]!='\n'; ++ii) {
                                    ll+=rbf_char_width(buffer[ii]);
                                }
                                if (ii==n) {
                                    memcpy(buffer, buffer+i, n-i);
                                    n=ii=n-i;
                                    read_on_screen+=i;
                                    i=0;
                                    n+=read(read_file, buffer+n, READ_BUFFER_SIZE-n);
                                    for (; ii<n && buffer[ii]!=' ' && buffer[ii]!='\t' && buffer[ii]!='\r' && buffer[ii]!='\n'; ++ii) {
                                        ll+=rbf_char_width(buffer[ii]);
                                    }
                                }
                                if (xx+ll>=x+w && ll<w) {
                                    read_goto_next_line();
                                    continue;
                                }
                            }
                        }
                        if (!read_fit_next_char(buffer[i])) {
                            read_goto_next_line();
                            continue;
                        }
                        xx+=rbf_draw_char(xx, yy, buffer[i], conf.reader_color);
                        break;
                }
                ++i;
                if (xx >= x+w) {
                    xx  = x;
                    yy += rbf_font_height();
                }
            }
            read_on_screen+=i;
        }
    
        sprintf(buffer, "(%3d%%) %d/%d  ", (read_file_size)?(conf.reader_pos*100/read_file_size):0, conf.reader_pos, read_file_size);
        buffer[camera_screen.width/FONT_WIDTH]=0;
        draw_txt_string((camera_screen.ts_button_border/FONT_WIDTH), 0, buffer, MAKE_COLOR(COLOR_BLACK, COLOR_WHITE)); //title infoline

        // scrollbar
        if (read_file_size) {
            i=h-1 -1;           // full height
            n=i*read_on_screen/read_file_size;           // bar height
            if (n<20) n=20;
            i=(i-n)*conf.reader_pos/read_file_size;   // top pos
            draw_filled_rect(x+w+6+2, y+1,   x+w+6+6, y+1+i,   MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            draw_filled_rect(x+w+6+2, y+i+n, x+w+6+6, y+h-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
            draw_filled_rect(x+w+6+2, y+1+i, x+w+6+6, y+i+n,   MAKE_COLOR(COLOR_WHITE, COLOR_WHITE));
        } else {
            draw_filled_rect((x+w)*FONT_WIDTH+2, y*FONT_HEIGHT+1, 
                             (x+w)*FONT_WIDTH+6, (y+h)*FONT_HEIGHT-1-1, MAKE_COLOR(COLOR_BLACK, COLOR_BLACK));
        }

        read_to_draw = 0;
        last_time = get_tick_count();
    }
    gui_read_draw_batt();
    gui_read_draw_clock();
}

//-------------------------------------------------------------------
void gui_read_kbd_process() {
    switch (kbd_get_autoclicked_key() | get_jogdial_direction()) {
        case JOGDIAL_LEFT:
        case KEY_ZOOM_OUT:
        case KEY_UP:
        case KEY_LEFT:
            if (conf.reader_pos>0) {
                conf.reader_pos -= 45*15;
                if (conf.reader_pos<0) conf.reader_pos=0;
                read_to_draw = 1;
            }
            break;
        case JOGDIAL_RIGHT:
        case KEY_ZOOM_IN:
        case KEY_DOWN:
        case KEY_RIGHT:
        case KEY_SHOOT_HALF:
            if ((conf.reader_pos+read_on_screen)<read_file_size) {
                conf.reader_pos += read_on_screen;
                read_to_draw = 1;
            }
            break;
        case KEY_SET:
            break;
        case KEY_DISPLAY:
            pause = !pause;
            gui_read_draw_scroll_indicator();
            last_time = get_tick_count();
            break;
        case KEY_MENU:
			gui_read_kbd_leave();
            break;
    }
}

// =========  MODULE INIT =================
#include "module_load.h"
int module_idx=-1;

//-------------------------------------------------------------------
// Menu button handled for text reader
void gui_read_kbd_process_menu_btn()
{
    gui_read_kbd_process();
    gui_default_kbd_process_menu_btn();
  	module_async_unload(module_idx);
}

void gui_read_kbd_leave()
{
	if ( !reader_is_active )
		return;

    reader_is_active = 0;
    rbf_load_from_file(conf.menu_rbf_file, FONT_CP_WIN);
	if (read_file >= 0) {
    	close(read_file);
	    read_file=-1;
    }
}

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

void* MODULE_EXPORT_LIST[] = {
	/* 0 */	(void*)EXPORTLIST_MAGIC_NUMBER,
	/* 1 */	(void*)0
		};


//---------------------------------------------------------
// PURPOSE:   Bind module symbols with chdk. 
//		Required function
// PARAMETERS: pointer to chdk list of export
// RETURN VALUE: 1 error, 0 ok
//---------------------------------------------------------
int _module_loader( unsigned int* chdk_export_list )
{
  if ( chdk_export_list[0] != EXPORTLIST_MAGIC_NUMBER )
     return 1;

  if ( !API_VERSION_MATCH_REQUIREMENT( gui_version.common_api, 1, 0 ) )
	  return 1;
  if ( !API_VERSION_MATCH_REQUIREMENT( conf.api_version, 2, 0 ) )
	 return 1;

  return 0;
}



//---------------------------------------------------------
// PURPOSE: Finalize module operations (close allocs, etc)
// RETURN VALUE: 0-ok, 1-fail
//---------------------------------------------------------
int _module_unloader()
{
    // We should make "leave sequence" to restore font settings
    gui_read_kbd_leave();

    GUI_MODE_READ.magicnum = 0;	//sanity clean to prevent accidentaly assign/restore guimode to unloaded module 

    return 0;
}


//---------------------------------------------------------
// PURPOSE: Default action for simple modules (direct run)
// NOTE: Please comment this function if no default action and this library module
//---------------------------------------------------------
int _module_run(int moduleidx, int argn, int* arguments)
{
  module_idx=moduleidx;

  if ( argn!=1 || arguments[0]==0) {
	module_async_unload(moduleidx);
    return 1;
  }

  char* fn=(char*)arguments[0];
  gui_read_init(fn);

  return 0;
}


/******************** Module Information structure ******************/

struct ModuleInfo _module_info = {	MODULEINFO_V1_MAGICNUM,
									sizeof(struct ModuleInfo),

									ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
									ANY_PLATFORM_ALLOWED,		// Specify platform dependency
									MODULEINFO_FLAG_SYSTEM,		// flag
									(int32_t)"Text reader",		// Module name
									1, 0,						// Module version
									0
								 };

/*************** END OF AUXILARY PART *******************/
