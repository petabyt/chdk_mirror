#ifndef PROPSET2_H
#define PROPSET2_H
/* 
constants for propset 2, most digic3 camera
WARNING:
 The build uses tools/gen_propset_lua.sed to generate propset2.lua from this file
*/
#define PROPCASE_DRIVE_MODE                 102
#define PROPCASE_FOCUS_MODE                 133     //WIKI|Propcase manual_focus
#define PROPCASE_REAL_FOCUS_MODE            6       //WIKI|Propcase focus_mode
#define PROPCASE_FOCUS_STATE                18
#define PROPCASE_FLASH_MODE                 143
#define PROPCASE_FLASH_FIRE                 122
#define PROPCASE_FLASH_MANUAL_OUTPUT        141
#define PROPCASE_FLASH_ADJUST_MODE          121
#define PROPCASE_USER_TV                    264
#define PROPCASE_TV                         262
#define PROPCASE_USER_AV                    26
#define PROPCASE_AV                         23
#define PROPCASE_MIN_AV                     25
#define PROPCASE_SV                         247
#define PROPCASE_DELTA_SV                   79
#define PROPCASE_SV_MARKET                  246
#define PROPCASE_BV                         34
#define PROPCASE_SUBJECT_DIST1              245
#define PROPCASE_SUBJECT_DIST2              65
#define PROPCASE_ISO_MODE                   149
#define PROPCASE_SHOOTING                   206
#define PROPCASE_IS_FLASH_READY             208
#define PROPCASE_OVEREXPOSURE               103
#define PROPCASE_SHOOTING_MODE              49
#define PROPCASE_IS_MODE                    145
#define PROPCASE_QUALITY                    57
#define PROPCASE_RESOLUTION                 218
#define PROPCASE_EV_CORRECTION_1            107
#define PROPCASE_EV_CORRECTION_2            207
#define PROPCASE_ORIENTATION_SENSOR         219
#define PROPCASE_DIGITAL_ZOOM_STATE         94      //G10 Digital Zoom Mode/State 0 = Digital Zoom off, 1 = Digital Zoom on
#define PROPCASE_DIGITAL_ZOOM_POSITION      95      //G10 Digital Zoom position 0 to 6 where 0=off,  6= full digital zoom
#define PROPCASE_DISPLAY_MODE               105
#define PROPCASE_BRACKET_MODE               29
#define PROPCASE_FLASH_SYNC_CURTAIN         64
#define PROPCASE_METERING_MODE              155
#define PROPCASE_WB_ADJ                     269 
#define PROPCASE_ASPECT_RATIO               294
#define PROPCASE_TIMER_MODE                 223
#define PROPCASE_OPTICAL_ZOOM_POSITION      195
//#define PROPCASE_OPTICAL_ZOOM_POSITION      251     //not working sx200is
#define PROPCASE_AE_LOCK                    3       //G10 0 = AE not locked, 1 = AE locked
#define PROPCASE_AF_FRAME                   8       //G10 1 = FlexiZone, 2 = Face AiAF / Tracking AF
#define PROPCASE_CONTINUOUS_AF              12      //G10 0 = Continuous AF off, 1 = Continuous AF on
#define PROPCASE_DIGITAL_ZOOM_MODE          91      //G10 Digital Zoom Mode/State 0 = off/standard, 2 = 1.7x, 3 = 2.1x
#define PROPCASE_STITCH_DIRECTION           233     //D10 0=left>right, 1=right>left
#define PROPCASE_STITCH_SEQUENCE            238     //D10 counts shots in stitch sequence, positive=left>right, negative=right>left
#endif
