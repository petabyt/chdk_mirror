#include "stdlib.h"
#include "keyboard.h"
#include "platform.h"
#include "histogram.h"
#include "core.h"
#include "lang.h"
#include "conf.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_batt.h"
#include "gui_grid.h"
#include "gui_osd.h"


//-------------------------------------------------------------------
typedef struct {
    int     title;
    OSD_pos *pos;
    OSD_pos size;
} OSD_elem;

static OSD_elem osd[]={
    {LANG_OSD_LAYOUT_EDITOR_HISTO,      &conf.histo_pos,        {HISTO_WIDTH+2, HISTO_HEIGHT}   },
    {LANG_OSD_LAYOUT_EDITOR_DOF_CALC,   &conf.dof_pos,          {17*FONT_WIDTH, 2*FONT_HEIGHT}  },
    {LANG_OSD_LAYOUT_EDITOR_STATES,     &conf.mode_state_pos,   {3*FONT_WIDTH, 2*FONT_HEIGHT}   },
    {LANG_OSD_LAYOUT_EDITOR_MISC,       &conf.values_pos,       {8*FONT_WIDTH, 3*FONT_HEIGHT}   },
    {LANG_OSD_LAYOUT_EDITOR_BAT_ICON,   &conf.batt_icon_pos,    {28, 12}                        },
    {LANG_OSD_LAYOUT_EDITOR_BAT_TEXT,   &conf.batt_txt_pos,     {5*FONT_WIDTH, FONT_HEIGHT}     },
    {LANG_OSD_LAYOUT_EDITOR_CLOCK,      &conf.clock_pos,        {5*FONT_WIDTH, FONT_HEIGHT}     },
    {0}
};
static int osd_to_draw;
static int curr_item;
static char osd_buf[64];
static int step;
static unsigned char *img_buf, *scr_buf;
static int timer = 0;
static char *buf = NULL;

//-------------------------------------------------------------------
void gui_osd_init() {
    osd_to_draw = 1;
    curr_item = 0;
    step = 10;
    draw_restore();
}

//-------------------------------------------------------------------
void gui_osd_draw() {
    if (osd_to_draw) {
        int i;
        draw_restore();
        gui_osd_draw_histo();
        gui_osd_draw_dof();
        gui_batt_draw_osd();
        gui_osd_draw_state();
        gui_osd_draw_values();
        gui_osd_draw_clock();
        for (i=1; i<=2; ++i) {
            draw_rect((osd[curr_item].pos->x>=i)?osd[curr_item].pos->x-i:0, (osd[curr_item].pos->y>=i)?osd[curr_item].pos->y-i:0, 
                      osd[curr_item].pos->x+osd[curr_item].size.x+i-1, osd[curr_item].pos->y+osd[curr_item].size.y+i-1,
                      COLOR_GREEN);
        }
        sprintf(osd_buf, " %s:  x:%d y:%d s:%d ", lang_str(osd[curr_item].title), osd[curr_item].pos->x, osd[curr_item].pos->y, step);
        draw_string(0, (osd[curr_item].pos->x<strlen(osd_buf)*FONT_WIDTH+4 && osd[curr_item].pos->y<FONT_HEIGHT+4)?screen_height-FONT_HEIGHT:0,
                    osd_buf, MAKE_COLOR(COLOR_RED, COLOR_WHITE));
        osd_to_draw = 0;
    }
}

//-------------------------------------------------------------------
void gui_osd_kbd_process() {
    switch (kbd_get_autoclicked_key()) {
    case KEY_LEFT:
        if (osd[curr_item].pos->x > 0) {
            osd[curr_item].pos->x-=(osd[curr_item].pos->x>=step)?step:osd[curr_item].pos->x;
            osd_to_draw = 1;
        }
        break;
    case KEY_RIGHT:
        if (osd[curr_item].pos->x < screen_width-osd[curr_item].size.x) {
            osd[curr_item].pos->x+=(screen_width-osd[curr_item].size.x-osd[curr_item].pos->x>step)?step:screen_width-osd[curr_item].size.x-osd[curr_item].pos->x;
            osd_to_draw = 1;
        }
        break;
    case KEY_UP:
        if (osd[curr_item].pos->y > 0) {
            osd[curr_item].pos->y-=(osd[curr_item].pos->y>=step)?step:osd[curr_item].pos->y;
            osd_to_draw = 1;
        }
        break;
    case KEY_DOWN:
        if (osd[curr_item].pos->y < screen_height-osd[curr_item].size.y) {
            osd[curr_item].pos->y+=(screen_height-osd[curr_item].size.y-osd[curr_item].pos->y>step)?step:screen_height-osd[curr_item].size.y-osd[curr_item].pos->y;
            osd_to_draw = 1;
        }
        break;
    case KEY_SET:
        ++curr_item;
        if (!osd[curr_item].pos) 
            curr_item = 0;
        osd_to_draw = 1;
        break;
    case KEY_DISPLAY:
        step=(step==1)?10:1;
        osd_to_draw = 1;
        break;
    }
}

//-------------------------------------------------------------------
static void gui_osd_draw_single_histo(int hist, coord x, coord y, int small) {
    register unsigned int i, v, threshold;
    register color cl, cl_over, cl_bg=conf.histo_color>>8;
    coord w=HISTO_WIDTH, h=HISTO_HEIGHT;

    switch (hist) {
        case HISTO_R: 
            cl=COLOR_RED; 
            break;
        case HISTO_G: 
            cl=COLOR_GREEN; 
            break;
        case HISTO_B: 
            cl=((mode_get()&MODE_MASK) == MODE_REC)?0xDF:0xCC; 
            break;
        case HISTO_RGB:
        case HISTO_Y:
        default:
            cl=conf.histo_color; 
            break;
    }

    if (small) {
        h>>=1; w>>=1;
        for (i=0; i<w; ++i) {
            threshold = (histogram[hist][i<<1]+histogram[hist][(i<<1)+1])>>2;

            for (v=1; v<h-1; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl:cl_bg);
            cl_over = (threshold==h && conf.show_overexp)?conf.histo_color2>>8:cl;
            for (; v<h; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl_over:cl_bg);
        }
    } else {
        for (i=0; i<w; ++i) {
            threshold = histogram[hist][i];

            for (v=1; v<h-3; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl:cl_bg);
            cl_over = (threshold==h && conf.show_overexp)?conf.histo_color2>>8:cl;
            for (; v<h; ++v)
                draw_pixel(x+1+i, y+h-v, (v<=threshold)?cl_over:cl_bg);
        }
    }
      
    draw_rect(x, y, x+1+w, y+h, conf.histo_color2&0xFF);

}

//-------------------------------------------------------------------
void gui_osd_zebra_init() {
    timer = 0;
}

//-------------------------------------------------------------------
static void draw_pixel_buffered(unsigned int offset, color cl) {
    buf[offset] = cl;
}

//-------------------------------------------------------------------
static void gui_osd_draw_zebra_osd() {
    switch (conf.zebra_draw_osd) {
        case ZEBRA_DRAW_NONE:
            break;
        case ZEBRA_DRAW_OSD:
            if (conf.show_osd) {
                draw_set_draw_proc(draw_pixel_buffered);
                if ((mode_get()&MODE_MASK) == MODE_REC) {
                    if (conf.show_grid_lines) {
                        gui_grid_draw_osd(1);
                    }
                    if (conf.show_dof) {
                        gui_osd_draw_dof();
                    }
                    if (conf.show_state) {
                        gui_osd_draw_state();
                    }
                    if (conf.show_values) {
                        gui_osd_draw_values();
                    }
                }
                gui_batt_draw_osd();
                if (conf.show_clock) {
                    gui_osd_draw_clock();
                }
                draw_set_draw_proc(NULL);
            }
            /* no break here */
        case ZEBRA_DRAW_HISTO:
        default:
            if (conf.show_histo) {
                draw_set_draw_proc(draw_pixel_buffered);
                gui_osd_draw_histo();
                draw_set_draw_proc(NULL);
            }
            break;
    }
}

//-------------------------------------------------------------------
int gui_osd_draw_zebra() {
    unsigned int v, s, x, y, f, over;
    color cl_under=conf.zebra_color>>8, cl_over=conf.zebra_color&0xFF;
    static int need_restore=0;
    int viewport_height;

    if (!buf) {
        buf = malloc(screen_size);
        scr_buf = vid_get_bitmap_fb();
    }

    if (buf) {
        ++timer;
        img_buf=((mode_get()&MODE_MASK) == MODE_PLAY)?vid_get_viewport_fb_d():vid_get_viewport_fb();
        viewport_height = vid_get_viewport_height();
        switch (conf.zebra_mode) {
            case ZEBRA_MODE_ZEBRA_1:
                f = 4;
                break;
            case ZEBRA_MODE_ZEBRA_2:
                f = 8;
                break;
            case ZEBRA_MODE_SOLID:
                f = 1; 
                break;
            case ZEBRA_MODE_BLINKED_1:
                f = timer&2; 
                break;
            case ZEBRA_MODE_BLINKED_3:
                f = timer&8; 
                break;
            case ZEBRA_MODE_BLINKED_2:
            default:
                f = timer&4; 
                break;
        }
        if (!f) {
            if (need_restore) {
                if (conf.zebra_restore_screen || conf.zebra_restore_osd) {
                    draw_restore();
                } else {
                    memset(buf, COLOR_TRANSPARENT, screen_size);
                    gui_osd_draw_zebra_osd();
                    memcpy(scr_buf, buf, screen_size);
                    memcpy(scr_buf+screen_size, buf, screen_size);
                }
                need_restore=0;
            }
            return !(conf.zebra_restore_screen && conf.zebra_restore_osd);
        } else {
            over = 255-conf.zebra_over;
            if (conf.zebra_mode == ZEBRA_MODE_ZEBRA_1 || conf.zebra_mode == ZEBRA_MODE_ZEBRA_2) {
                for (s=0, y=0; y<screen_height; ++y) {
                    v=y*viewport_height/screen_height*screen_width*3+1;
                    for (x=0; x<screen_width; ++x, ++s, v+=3) {
                        buf[s]=(img_buf[v]>over && ((y-x-timer)&f))?cl_over:((img_buf[v]<conf.zebra_under && ((y-x-timer)&f))?cl_under:COLOR_TRANSPARENT);
                    }
                }
            } else {
                for (s=0, v=y=1; y<=viewport_height; ++y) {
                    for (x=0; x<screen_width; ++x, ++s, v+=3) {
                        buf[s]=(img_buf[v]>over)?cl_over:((img_buf[v]<conf.zebra_under)?cl_under:COLOR_TRANSPARENT);
                    }
                    if (y*screen_height/viewport_height == (s+screen_width)/screen_width) {
                        memcpy(buf+s, buf+s-screen_width, screen_width);
                        s+=screen_width;
                    }
                }
            }
            
            gui_osd_draw_zebra_osd();
            memcpy(scr_buf, buf, screen_size);
            memcpy(scr_buf+screen_size, buf, screen_size);

            need_restore=1;
            return 1;
        }
    }
    return 0;
}

//-------------------------------------------------------------------
static void gui_osd_draw_blended_histo(coord x, coord y) {
    register unsigned int i, v, red, grn, blu, sel;
    int m = ((mode_get()&MODE_MASK) == MODE_REC);
    color cls[] = {
        conf.histo_color>>8,
        (m)?0xDF:0xCC,
        COLOR_GREEN,
        (m)?COLOR_BLUE_LT:0x99,
        COLOR_RED,
        (m)?0x66:0xE2,
        (m)?COLOR_YELLOW:0x66,
        COLOR_WHITE
    };

    for (i=0; i<HISTO_WIDTH; ++i) {
        red = histogram[HISTO_R][i];
        grn = histogram[HISTO_G][i];
        blu = histogram[HISTO_B][i];

        for (v=1; v<HISTO_HEIGHT; ++v) {
            sel = 0;

            if (v < red) sel = 4;
            if (v < grn) sel |= 2;
            if (v < blu) sel |= 1;

            draw_pixel(x+1+i, y+HISTO_HEIGHT-v, cls[sel]);
        }
    }

    draw_rect(x, y, x+1+HISTO_WIDTH, y+HISTO_HEIGHT, conf.histo_color2&0xFF);
}

//-------------------------------------------------------------------
void gui_osd_draw_histo() {
    switch (conf.histo_layout) {
        case OSD_HISTO_LAYOUT_Y:
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y, 0);
                break;
        case OSD_HISTO_LAYOUT_A_Y:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                break;
        case OSD_HISTO_LAYOUT_R_G_B:
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT*2, 0);
                break;
        case OSD_HISTO_LAYOUT_A_yrgb:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                break;
        case OSD_HISTO_LAYOUT_Y_argb:
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y, 0);
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_R, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT, 1);
                gui_osd_draw_single_histo(HISTO_G, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                gui_osd_draw_single_histo(HISTO_B, conf.histo_pos.x+HISTO_WIDTH/2+1, conf.histo_pos.y+HISTO_HEIGHT+HISTO_HEIGHT/2, 1);
                break;
        case OSD_HISTO_LAYOUT_BLEND:
                gui_osd_draw_blended_histo(conf.histo_pos.x, conf.histo_pos.y);
                break;
        case OSD_HISTO_LAYOUT_BLEND_Y:
                gui_osd_draw_blended_histo(conf.histo_pos.x, conf.histo_pos.y);
                gui_osd_draw_single_histo(HISTO_Y, conf.histo_pos.x, conf.histo_pos.y+HISTO_HEIGHT, 0);
                break;
        case OSD_HISTO_LAYOUT_A:
        default:
                gui_osd_draw_single_histo(HISTO_RGB, conf.histo_pos.x, conf.histo_pos.y, 0);
                break;
    }

    if (conf.histo_layout != OSD_HISTO_LAYOUT_R_G_B) {
        if (under_exposed && conf.show_overexp) {
            draw_filled_ellipse(conf.histo_pos.x+5, conf.histo_pos.y+5, 3, 3, MAKE_COLOR(conf.histo_color2>>8, conf.histo_color2>>8));
        }

        if (over_exposed && conf.show_overexp) {
            draw_filled_ellipse(conf.histo_pos.x+HISTO_WIDTH-5, conf.histo_pos.y+5, 3, 3, MAKE_COLOR(conf.histo_color2>>8, conf.histo_color2>>8));
        }
    }

    if (histo_magnification) {
        sprintf(osd_buf, " %d.%02dx ", histo_magnification/1000, histo_magnification/10%100);
        draw_string(conf.histo_pos.x, conf.histo_pos.y-FONT_HEIGHT, osd_buf, conf.histo_color);
    } else {
        draw_filled_rect(conf.histo_pos.x, conf.histo_pos.y-FONT_HEIGHT, conf.histo_pos.x+8*FONT_WIDTH, conf.histo_pos.y-1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
    }
}

//-------------------------------------------------------------------
static void sprintf_dist(char *buf, float dist) {
// length of printed string is always 4
    if (dist<=0 || dist>65500) {
        sprintf(buf, " inf");
//    } else if (dist<1000) {
//        sprintf(buf, ".%03d", (int)dist);
    } else if (dist<10000) {
        sprintf(buf, "%d.%02d", (int)(dist/1000), (int)(dist/10)%100);
    } else if (dist<100000) {
        sprintf(buf, "%02d.%d", (int)(dist/1000), (int)(dist/100)%10);
    } else {
        sprintf(buf, "%4d", (int)(dist/1000));
    }
}

//-------------------------------------------------------------------
void gui_osd_draw_dof() {
    long av, fp; 
    float r1=-1.0f, r2=-1.0f, hyp=-1.0f, fl, v;
    
    fl=get_focal_length(lens_get_zoom_point());
    av=shooting_get_real_av();
    fp=lens_get_target_distance();

    if (av) {
        hyp=(fl*fl)/(10*circle_of_confusion*av);
        if (fp>=0 && fp<65500) {
            v = (hyp+fp);
            if (v!=0.0f)
                r1=(hyp*fp)/v;
            v = (hyp-fp);
            if (v!=0.0f)
                r2=(hyp*fp)/v;
        }
    }

    draw_string(conf.dof_pos.x, conf.dof_pos.y, "R1/R2:", conf.osd_color);
    sprintf_dist(osd_buf, r1);
    osd_buf[4]='/';
    sprintf_dist(osd_buf+5, r2);
    draw_string(conf.dof_pos.x+6*FONT_WIDTH, conf.dof_pos.y, osd_buf, conf.osd_color);
        
    draw_string(conf.dof_pos.x, conf.dof_pos.y+FONT_HEIGHT, "DOF/HYP:", conf.osd_color);
    sprintf_dist(osd_buf, (r1>=0.0f && r2>=0.0f)?r2-r1:-1.0f);
    osd_buf[4]='/';
    sprintf_dist(osd_buf+5, hyp);
    draw_string(conf.dof_pos.x+8*FONT_WIDTH, conf.dof_pos.y+FONT_HEIGHT, osd_buf, conf.osd_color);
}

//-------------------------------------------------------------------
void gui_osd_draw_state() {
    int n=0, gui_mode=gui_get_mode();

    if (conf.save_raw || gui_mode==GUI_MODE_OSD){
        draw_string(conf.mode_state_pos.x, conf.mode_state_pos.y, "RAW", conf.osd_color);
        n+=FONT_HEIGHT;
    }
    if (((gui_mode==GUI_MODE_NONE || gui_mode==GUI_MODE_ALT) && conf.show_histo && conf.show_overexp && kbd_is_key_pressed(KEY_SHOOT_HALF)) || gui_mode==GUI_MODE_OSD) {
        draw_string(conf.mode_state_pos.x, conf.mode_state_pos.y+n, (under_exposed || over_exposed)?"EXP":"   ", conf.osd_color);
    }
}

//-------------------------------------------------------------------
void gui_osd_draw_values() {
    int zp=lens_get_zoom_point(), av=shooting_get_real_av(), fl, lfp;

    switch (conf.zoom_value) {
        case ZOOM_SHOW_FL:
            fl=get_focal_length(zp);
            sprintf(osd_buf, "Z:%d.%dmm%8s", fl/1000, fl%1000/100, "");
            break;
        case ZOOM_SHOW_EFL:
            fl=get_effective_focal_length(zp);
            sprintf(osd_buf, "Z:%3dmm%8s", fl/1000, "");
            break;
        case ZOOM_SHOW_X:
        default:
            fl=get_zoom_x(zp);
            sprintf(osd_buf, "Z:%ld/%d.%dx%8s", zp, fl/10, fl%10, "");
            break;
    }
    osd_buf[8]=0;
    draw_string(conf.values_pos.x, conf.values_pos.y, osd_buf, conf.osd_color);

    lfp = lens_get_target_distance();
    strcpy(osd_buf, "F:");
    sprintf_dist(osd_buf+2, lfp);
    sprintf(osd_buf+strlen(osd_buf), "%8s", "");
    osd_buf[8]=0;
    draw_string(conf.values_pos.x, conf.values_pos.y+FONT_HEIGHT, osd_buf, conf.osd_color);

    sprintf(osd_buf, "Av:%d.%02d ", av/100, av%100);
    osd_buf[8]=0;
    draw_string(conf.values_pos.x, conf.values_pos.y+FONT_HEIGHT*2, osd_buf, conf.osd_color);
}

//-------------------------------------------------------------------
void gui_osd_draw_clock() {
    unsigned long t;
    static struct tm *ttm;

    t = time(NULL);
    ttm = localtime(&t);
    sprintf(osd_buf, "%2u:%02u", ttm->tm_hour, ttm->tm_min);
    draw_string(conf.clock_pos.x, conf.clock_pos.y, osd_buf, conf.osd_color);
}

//-------------------------------------------------------------------
