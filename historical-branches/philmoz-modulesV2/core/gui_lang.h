#ifndef GUI_LANG_H
#define GUI_LANG_H

// CHDK Language String numbers

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//-------------------------------------------------------------------
#define LANG_MENU_MAIN_TITLE            1

#define LANG_MENU_MAIN_RAW_PARAM        2
#define LANG_MENU_MAIN_OSD_PARAM        3
#define LANG_MENU_MAIN_HISTO_PARAM      4
#define LANG_MENU_MAIN_ZEBRA_PARAM      5
#define LANG_MENU_MAIN_SCRIPT_PARAM     6
#define LANG_MENU_MAIN_VISUAL_PARAM     7
#define LANG_MENU_MAIN_MISC             8
#define LANG_MENU_MAIN_DEBUG            9
#define LANG_MENU_MAIN_RESET_OPTIONS    10
#define LANG_MENU_MAIN_SAVE_OPTIONS     11

#define LANG_MENU_BACK                  12


#define LANG_MENU_RAW_TITLE             13

#define LANG_MENU_RAW_SAVE              14
#define LANG_MENU_RAW_FIRST_ONLY        16
#define LANG_MENU_RAW_SAVE_IN_DIR       17
#define LANG_MENU_RAW_PREFIX            18
#define LANG_MENU_RAW_EXTENSION         19


#define LANG_MENU_OSD_TITLE             20

#define LANG_MENU_OSD_SHOW              21
#define LANG_MENU_OSD_SHOW_STATES       22
#define LANG_MENU_OSD_SHOW_MISC_VALUES  23
#define LANG_MENU_OSD_ZOOM_VALUE        24
#define LANG_MENU_OSD_SHOW_DOF_CALC     25
#define LANG_MENU_OSD_SHOW_CLOCK        26
#define LANG_MENU_OSD_LAYOUT_EDITOR     27
#define LANG_MENU_OSD_BATT_PARAMS       28


#define LANG_MENU_HISTO_TITLE           29

#define LANG_MENU_HISTO_SHOW            30
#define LANG_MENU_HISTO_LAYOUT          31
#define LANG_MENU_HISTO_MODE            32
#define LANG_MENU_HISTO_EXP             33
#define LANG_MENU_HISTO_IGNORE_PEAKS    34
#define LANG_MENU_HISTO_MAGNIFY         35


#define LANG_MENU_ZEBRA_TITLE           36

#define LANG_MENU_ZEBRA_DRAW            37
#define LANG_MENU_ZEBRA_MODE            38
#define LANG_MENU_ZEBRA_UNDER           39
#define LANG_MENU_ZEBRA_OVER            40
#define LANG_MENU_ZEBRA_RESTORE_SCREEN  41
#define LANG_MENU_ZEBRA_RESTORE_OSD     42
#define LANG_MENU_ZEBRA_DRAW_OVER       43


#define LANG_MENU_SCRIPT_TITLE          44

#define LANG_MENU_SCRIPT_LOAD           45
#define LANG_MENU_SCRIPT_DELAY          46
#define LANG_MENU_SCRIPT_CURRENT        47
#define LANG_MENU_SCRIPT_PARAMS         48


#define LANG_MENU_VIS_TITLE             49

#define LANG_MENU_VIS_LANG              50
#define LANG_MENU_VIS_OSD_FONT          51
#define LANG_MENU_VIS_MENU_FONT         52
#define LANG_MENU_VIS_COLORS            53
#define LANG_MENU_VIS_OSD_TEXT          54
#define LANG_MENU_VIS_OSD_BKG           55
#define LANG_MENU_VIS_HISTO             56
#define LANG_MENU_VIS_HISTO_BKG         57
#define LANG_MENU_VIS_HISTO_BORDER      58
#define LANG_MENU_VIS_HISTO_MARKERS     59
#define LANG_MENU_VIS_ZEBRA_UNDER       60
#define LANG_MENU_VIS_ZEBRA_OVER        61
#define LANG_MENU_VIS_BATT_ICON         62
#define LANG_MENU_VIS_MENU_TEXT         63
#define LANG_MENU_VIS_MENU_BKG          64
#define LANG_MENU_VIS_READER_TEXT       65
#define LANG_MENU_VIS_READER_BKG        66


#define LANG_MENU_MISC_TITLE            67

#define LANG_MENU_MISC_FILE_BROWSER     68
#define LANG_MENU_MISC_CALENDAR         69
#define LANG_MENU_MISC_TEXT_READER      70
#define LANG_MENU_MISC_GAMES            71
#define LANG_MENU_MISC_FLASHLIGHT       72
#define LANG_MENU_MISC_SHOW_SPLASH      73
#define LANG_MENU_MISC_ZOOM_FOR_MF      74
#define LANG_MENU_MISC_ALT_BUTTON       75
#define LANG_MENU_MISC_PALETTE          76
#define LANG_MENU_MISC_BUILD_INFO       77
#define LANG_MENU_MISC_MEMORY_INFO      78


#define LANG_MENU_DEBUG_TITLE           79

#define LANG_MENU_DEBUG_DISPLAY         80
#define LANG_MENU_DEBUG_PROPCASE_PAGE   81
#define LANG_MENU_DEBUG_SHOW_MISC_VALS  82
#define LANG_MENU_DEBUG_MEMORY_BROWSER  83
#define LANG_MENU_DEBUG_SHORTCUT_ACTION 84
#define LANG_MENU_DEBUG_MAKE_BOOTABLE   85


#define LANG_MENU_BATT_TITLE            86

#define LANG_MENU_BATT_VOLT_MAX         87
#define LANG_MENU_BATT_VOLT_MIN         88
#define LANG_MENU_BATT_STEP_25          89
#define LANG_MENU_BATT_SHOW_PERCENT     90
#define LANG_MENU_BATT_SHOW_VOLTS       91
#define LANG_MENU_BATT_SHOW_ICON        92


#define LANG_MENU_READ_TITLE            93

#define LANG_MENU_READ_OPEN_NEW         94
#define LANG_MENU_READ_OPEN_LAST        95
#define LANG_MENU_READ_SELECT_FONT      96
#define LANG_MENU_READ_CODEPAGE         97
#define LANG_MENU_READ_WORD_WRAP        98
#define LANG_MENU_READ_AUTOSCROLL       99
#define LANG_MENU_READ_AUTOSCROLL_DELAY 100


#define LANG_MENU_GAMES_TITLE           101

#define LANG_MENU_GAMES_REVERSI         102
#define LANG_MENU_GAMES_SOKOBAN         103


#define LANG_MSG_RESET_OPTIONS_TITLE    104
#define LANG_MSG_RESET_OPTIONS_TEXT     105

#define LANG_MSG_BUILD_INFO_TITLE       106
#define LANG_MSG_BUILD_INFO_TEXT        107

#define LANG_MSG_MEMORY_INFO_TITLE      108
#define LANG_MSG_MEMORY_INFO_TEXT       109

#define LANG_MSG_INFO_TITLE             110
#define LANG_MSG_SWITCH_TO_PLAY_MODE    111


#define LANG_STR_FILE_BROWSER           112
#define LANG_STR_SELECT_SCRIPT_FILE     113
#define LANG_STR_SELECT_TEXT_FILE       114
#define LANG_STR_SELECT_FONT_FILE       115
#define LANG_STR_SELECT_LANG_FILE       116


#define LANG_CALENDAR_JANUARY           117
#define LANG_CALENDAR_FEBRUARY          118
#define LANG_CALENDAR_MARCH             119
#define LANG_CALENDAR_APRIL             120
#define LANG_CALENDAR_MAY               121
#define LANG_CALENDAR_JUNE              122
#define LANG_CALENDAR_JULY              123
#define LANG_CALENDAR_AUGUST            124
#define LANG_CALENDAR_SEPTEMBER         125
#define LANG_CALENDAR_OCTOBER           126
#define LANG_CALENDAR_NOVEMBER          127
#define LANG_CALENDAR_DECEMBER          128

#define LANG_CALENDAR_MON               129
#define LANG_CALENDAR_TUE               130
#define LANG_CALENDAR_WED               131
#define LANG_CALENDAR_THU               132
#define LANG_CALENDAR_FRI               133
#define LANG_CALENDAR_SAT               134
#define LANG_CALENDAR_SUN               135

#define LANG_CALENDAR_TODAY             136


#define LANG_MBOX_BTN_OK                137
#define LANG_MBOX_BTN_YES               138
#define LANG_MBOX_BTN_NO                139
#define LANG_MBOX_BTN_CANCEL            140


#define LANG_OSD_LAYOUT_EDITOR_HISTO    141
#define LANG_OSD_LAYOUT_EDITOR_DOF_CALC 142
#define LANG_OSD_LAYOUT_EDITOR_STATES   143
#define LANG_OSD_LAYOUT_EDITOR_MISC     144
#define LANG_OSD_LAYOUT_EDITOR_BAT_ICON 145
#define LANG_OSD_LAYOUT_EDITOR_BAT_TEXT 146
#define LANG_OSD_LAYOUT_EDITOR_CLOCK    147


#define LANG_PALETTE_TEXT_1             148
#define LANG_PALETTE_TEXT_2             149
#define LANG_PALETTE_TEXT_COLOR         150
#define LANG_PALETTE_TEXT_SELECT_COLOR  151

#define LANG_REVERSI_MSG_RESULTS_TITLE  152
#define LANG_REVERSI_MSG_RESULTS_WON    153
#define LANG_REVERSI_MSG_RESULTS_LOST   154
#define LANG_REVERSI_MSG_RESULTS_DRAW   155

#define LANG_REVERSI_MSG_WRONG_TITLE    156
#define LANG_REVERSI_MSG_WRONG_TEXT_1   157
#define LANG_REVERSI_MSG_WRONG_TEXT_2   158

#define LANG_REVERSI_MOVE_WHITE         159
#define LANG_REVERSI_MOVE_BLACK         160
#define LANG_REVERSI_GAME_OVER          161
#define LANG_REVERSI_WHITE_BLACK        162


#define LANG_MBOX_ABOUT_TITLE           163


#define LANG_SOKOBAN_TEXT_LEVEL         164
#define LANG_SOKOBAN_TEXT_MOVES         165

#define LANG_SOKOBAN_MSG_FINISH_TITLE   166
#define LANG_SOKOBAN_MSG_FINISH_TEXT    167


#define LANG_CONSOLE_TEXT_STARTED       168
#define LANG_CONSOLE_TEXT_INTERRUPTED   169
#define LANG_CONSOLE_TEXT_FINISHED      170


#define LANG_BROWSER_ERASE_DIR_TITLE    171
#define LANG_BROWSER_ERASE_DIR_TEXT     172
#define LANG_BROWSER_DELETE_FILE_TITLE  173
#define LANG_BROWSER_DELETE_FILE_TEXT   174

#define LANG_MENU_DEBUG_BENCHMARK       175

#define LANG_BENCH_CALCULATING          176
#define LANG_BENCH_TITLE                177
#define LANG_BENCH_SCREEN               178
#define LANG_BENCH_WRITE                179
#define LANG_BENCH_READ                 180
#define LANG_BENCH_MEMORY               181
#define LANG_BENCH_FLASH_CARD           182
#define LANG_BENCH_WRITE_RAW            183
#define LANG_BENCH_WRITE_MEM            184
#define LANG_BENCH_WRITE_64K            185
#define LANG_BENCH_READ_64K             186

#define LANG_MENU_MISC_DISABLE_LCD_OFF  187

#define LANG_POPUP_CUT                  188
#define LANG_POPUP_COPY                 189
#define LANG_POPUP_PASTE                190
#define LANG_POPUP_DELETE               191
#define LANG_POPUP_SELINV               192
#define LANG_FSELECT_CUT_TITLE          193
#define LANG_FSELECT_CUT_TEXT           194
#define LANG_FSELECT_COPY_TITLE         195
#define LANG_FSELECT_COPY_TEXT          196
#define LANG_FSELECT_DELETE_TITLE       197
#define LANG_FSELECT_DELETE_TEXT        198
#define LANG_FSELECT_PROGRESS_TITLE     199

#define LANG_MENU_SHOW_GRID                     200
#define LANG_MENU_GRID_LOAD                     201
#define LANG_MENU_GRID_TITLE                    202
#define LANG_MENU_OSD_GRID_PARAMS               203
#define LANG_STR_SELECT_GRID_FILE               204
#define LANG_MENU_GRID_CURRENT                  205

#define LANG_MENU_RAW_NOISE_REDUCTION           206

#define LANG_MENU_GRID_FORCE_COLOR              207
#define LANG_MENU_GRID_COLOR_LINE               208
#define LANG_MENU_GRID_COLOR_FILL               209

#define LANG_MENU_DOF_TITLE                     210
#define LANG_MENU_OSD_DOF_CALC                  211
#define LANG_MENU_DOF_SUBJ_DIST_AS_NEAR_LIMIT   212
#define LANG_MENU_DOF_USE_EXIF_SUBJ_DIST        213
#define LANG_MENU_DOF_SUBJ_DIST_IN_MISC         214
#define LANG_MENU_DOF_NEAR_LIMIT_IN_MISC        215
#define LANG_MENU_DOF_FAR_LIMIT_IN_MISC         216
#define LANG_MENU_DOF_HYPERFOCAL_IN_MISC        217
#define LANG_MENU_DOF_DEPTH_LIMIT_IN_MISC       218

#define LANG_MENU_OSD_VALUES_TITLE              219
#define LANG_MENU_OSD_VALUES                    220
#define LANG_MENU_VALUES_SHOW_IN_REVIEW         221
#define LANG_MENU_VALUES_SHOW_ZOOM              222
#define LANG_MENU_VALUES_SHOW_REAL_APERTURE     223
#define LANG_MENU_VALUES_SHOW_REAL_ISO          224
#define LANG_MENU_VALUES_SHOW_MARKET_ISO        225
#define LANG_MENU_SHOW_ISO_ONLY_IN_AUTOISO_MODE 226
#define LANG_MENU_VALUES_SHOW_EV_SETED          227
#define LANG_MENU_VALUES_SHOW_EV_MEASURED       228
#define LANG_MENU_VALUES_SHOW_BV_SETED          229
#define LANG_MENU_VALUES_SHOW_BV_MEASURED       230
#define LANG_MENU_VALUES_SHOW_OVEREXPOSURE      231
#define LANG_MENU_VALUES_SHOW_LUMINANCE         232

#define LANG_MENU_VIDEO_PARAM_TITLE             233
#define LANG_MENU_VIDEO_PARAM                   234
#define LANG_MENU_VIDEO_MODE                    235
#define LANG_MENU_VIDEO_BITRATE                 236
#define LANG_MENU_VIDEO_QUALITY                 237

#define LANG_MENU_OPERATION_PARAM_TITLE         238
#define LANG_MENU_OPERATION_PARAM               239
#define LANG_MENU_OVERRIDE_TV_VALUE             240
#define	LANG_MENU_OVERRIDE_TV_LONG_EXP          241
#define LANG_MENU_OVERRIDE_AV_VALUE             242
#define	LANG_MENU_OVERRIDE_ISO_VALUE            243
#define	LANG_MENU_OVERRIDE_TV_SHORT_EXP         244
#define	LANG_MENU_OVERRIDE_SUBJ_DIST_VALUE      245
#define	LANG_MENU_OVERRIDE_SUBJ_DIST_KOEF       246

#define LANG_MENU_BRACKET_IN_CONTINUOUS_TITLE   247
#define LANG_MENU_BRACKET_IN_CONTINUOUS         248
#define LANG_MENU_TV_BRACKET_VALUE              249
#define LANG_MENU_AV_BRACKET_VALUE              250
#define LANG_MENU_ISO_BRACKET_VALUE             251
#define LANG_MENU_SUBJ_DIST_BRACKET_VALUE       253
#define LANG_MENU_BRACKET_TYPE                  255

#define LANG_MENU_SCRIPT_AUTOSTART              256
#define LANG_MENU_REMOTE_ENABLE                 257

#define LANG_MENU_LUA_NATIVE_CALLS_WARNING      258
#define LANG_MENU_ENABLE_LUA_NATIVE_CALLS       259
#define LANG_CONSOLE_TEXT_TERMINATED            260
#define LANG_CONSOLE_TEXT_AUTOSTARTED           261

#define LANG_MENU_CLEAR_OVERRIDE_VALUES         264
#define LANG_MENU_SHOW_CANON_OVEREXPOSURE       265

#define LANG_MENU_RAW_DEVELOP                   266
#define LANG_RAW_DEVELOP_MESSAGE                267
#define LANG_RAW_DEVELOP_SELECT_FILE            268
#define LANG_POPUP_RAW_SUM                      269
#define LANG_POPUP_RAW_AVERAGE                  270
#define LANG_AVERAGE_NO_CARD_SPACE              271

#define LANG_MENU_OSD_SHOW_IN_REVIEW            272
#define LANG_MENU_DEBUG_TASKLIST_START          273

#define LANG_MENU_CLEAR_BRACKET_VALUES          275

#define LANG_MENU_DEBUG_CREATE_MULTIPART        276
#define LANG_MENU_DEBUG_SWAP_PART               277
#define LANG_PARTITIONS_CREATE_WARNING          278
#define LANG_ONLY_ONE_PARTITION                 279
#define LANG_ERROR                              280
#define LANG_WARNING                            281
#define LANG_INFORMATION                        282
#define LANG_MENU_ZEBRA_MULTICHANNEL            283

#define LANG_MENU_OVERRIDE_ND_FILTER            284

#define LANG_MENU_HISTO_SHOW_EV_GRID            285

#define LANG_MENU_VIS_OSD_WARNING               286
#define LANG_MENU_VIS_OSD_WARNING_BKG           287
#define LANG_MENU_VIS_SPACE_ICON                288
#define LANG_MENU_SPACE_SHOW_ICON               289
#define LANG_OSD_LAYOUT_EDITOR_SPACE_ICON       290
#define LANG_MENU_SPACE_SHOW_PERCENT            291
#define LANG_MENU_SPACE_SHOW_MB                 292
#define LANG_OSD_LAYOUT_EDITOR_SPACE_TEXT       293
#define LANG_MENU_OSD_SHOW_REMAINING_RAW        294
#define LANG_OSD_LAYOUT_EDITOR_RAW              295
#define LANG_MENU_OSD_SHOW_RAW_STATE            296

#define LANG_MENU_SHOW_VALUES_IN_VIDEO          297

#define LANG_MENU_TV_ENUM_TYPE                  298
#define LANG_MENU_USER_MENU_ENABLE              299
#define LANG_MENU_USER_MENU                     300
#define LANG_MENU_ITEM_BLANK                    301

#define LANG_MENU_OSD_ZOOM_SCALE                302
#define LANG_MENU_SPACE_SHOW_BAR                303
#define LANG_MENU_SPACE_BAR_SIZE                304
#define LANG_MENU_SPACE_BAR_WIDTH               305
#define LANG_MENU_SPACE_WARN_PERCENT            306
#define LANG_MENU_SPACE_WARN_MB                 307
#define LANG_MENU_SPACE_WARN_TYPE               308
#define LANG_MENU_OSD_RAW_TRESHOLD              309
#define LANG_MENU_OPTICAL_ZOOM_IN_VIDEO         310
#define LANG_MENU_OSD_CLOCK_PARAMS              311
#define LANG_MENU_OSD_CLOCK_PARAMS_TITLE        312
#define LANG_MENU_OSD_CLOCK_FORMAT              313
#define LANG_MENU_VIS_SPACE_ICON_BKG            314
#define LANG_MENU_OSD_CLOCK_INDICATOR           315
#define LANG_MENU_OSD_CLOCK_HALFPRESS           316

#define LANG_MENU_OSD_RAW_STATE_PARAMS_TITLE    317
#define LANG_MENU_OSD_RAW_STATE_PARAMS          318

#define LANG_MENU_OSD_SPACE_PARAMS_TITLE        319
#define LANG_MENU_OSD_SPACE_PARAMS              320

#define LANG_MENU_AUTOISO_TITLE                 321
#define LANG_MENU_AUTOISO                       322
#define LANG_MENU_AUTOISO_ENABLED               323
#define LANG_MENU_AUTOISO_MIN_SHUTTER           324
#define LANG_MENU_AUTOISO_USER_FACTOR           325
#define LANG_MENU_AUTOISO_IS_FACTOR             326
#define LANG_MENU_AUTOISO_MAX_ISO_HI            327
#define LANG_MENU_AUTOISO_MAX_ISO_AUTO          328
#define LANG_MENU_AUTOISO_MIN_ISO               329

#define LANG_MENU_VIS_MENU_TITLE_TEXT           330 
#define LANG_MENU_VIS_MENU_TITLE_BKG            331
#define LANG_MENU_VIS_MENU_CURSOR_TEXT          332 
#define LANG_MENU_VIS_MENU_CURSOR_BKG           333
#define LANG_MENU_VIS_MENU_CENTER               334
#define LANG_MENU_MUTE_ON_ZOOM                  335
#define LANG_MENU_BAD_PIXEL_REMOVAL             336 
#define LANG_MENU_BAD_PIXEL_OFF                 337 
#define LANG_MENU_BAD_PIXEL_INTERPOLATION       338 
#define LANG_MENU_BAD_PIXEL_RAW_CONVERTER       339 
#define LANG_MENU_VIS_OSD_OVERRIDE              340
#define LANG_MENU_VIS_OSD_OVERRIDE_BKG          341
#define LANG_MENU_OVERRIDE_DISABLE              342
#define LANG_MENU_OVERRIDE_DISABLE_ALL          343
#define LANG_MENU_OSD_HIDE_PLAYBACK             344
#define LANG_MENU_RAW_SAVE_IN_VIDEO             345
#define LANG_MENU_OSD_SHOW_VIDEO_TIME           346
#define LANG_MENU_OSD_SHOW_VIDEO_REFRESH        347
#define LANG_OSD_LAYOUT_EDITOR_VIDEO            348
#define LANG_MENU_CLEAR_VIDEO_VALUES            349
#define LANG_MENU_MISC_FAST_EV                  350
#define LANG_OSD_LAYOUT_EDITOR_EV               352

#define LANG_FSELECT_PURGE_DCIM_TEXT            353
#define LANG_FSELECT_PURGE_CANON_FOLDER_TEXT    354
#define LANG_FSELECT_PURGE_LIST_TEXT            355
#define LANG_FSELECT_PURGE_DISABLED_TEXT        356
#define LANG_FSELECT_PURGE_TITLE                357
#define LANG_POPUP_PURGE                        358

#define LANG_MENU_USER_MENU_AS_ROOT             359

#define LANG_MENU_VIS_MENU_SYMBOL_FONT          360
#define LANG_STR_SELECT_SYMBOL_FILE             361
#define LANG_MENU_VIS_SYMBOL                    362
#define LANG_MENU_VIS_MENU_SYMBOL_TEXT          363
#define LANG_MENU_VIS_MENU_SYMBOL_BKG           364

#define LANG_MENU_CURVE_PARAM_TITLE             365
#define LANG_MENU_CURVE_PARAM                   366
#define LANG_MENU_CURVE_LOAD                    367
#define LANG_MENU_CURVE_ENABLE                  368
#define LANG_STR_SELECT_CURVE_FILE              369

#define LANG_MENU_EDGE_OVERLAY_TITLE            370
#define LANG_MENU_EDGE_OVERLAY                  371
#define LANG_MENU_EDGE_OVERLAY_ENABLE           372
#define LANG_MENU_EDGE_OVERLAY_TRESH            373
#define LANG_MENU_EDGE_OVERLAY_COLOR            374

#define LANG_MENU_REMOTE_PARAM_TITLE            375
#define LANG_MENU_REMOTE_PARAM                  376
#define LANG_MENU_SYNCHABLE_REMOTE_ENABLE       377 
#define LANG_MENU_SYNCH_ENABLE                  378
#define LANG_MENU_SYNCH_DELAY_ENABLE            379
#define LANG_MENU_SYNCH_DELAY_VALUE             380
#define LANG_MENU_SYNCH_DELAY_COARSE_VALUE      381

#define LANG_MENU_VIDEO_AF_KEY                  382
#define LANG_MENU_SCRIPT_DEFAULT_VAL            383
#define LANG_MENU_SCRIPT_PARAM_SET              384

#define LANG_MENU_RAW_SAVE_IN_SPORTS            385
#define LANG_MENU_RAW_SAVE_IN_BURST             386
#define LANG_MENU_RAW_SAVE_IN_EV_BRACKETING     387
#define LANG_MENU_RAW_SAVE_IN_TIMER             388

#define LANG_MENU_OSD_RAW_EXCEPTIONS_PARAMS     389
#define LANG_MENU_OSD_RAW_EXCEPTIONS_PARAMS_TITLE 390
#define LANG_MENU_RAW_WARN                      391
#define LANG_MENU_SELECT_FIRST_ENTRY            392

#define LANG_MENU_REMOTE_SHOOT_HALF_TIMEOUT     393
#define LANG_MENU_SYNCHABLE_REMOTE              394

#define LANG_MENU_FAST_SWITCH_VIDEO             395
#define LANG_OSD_LAYOUT_EDITOR_TEMP             396
#define LANG_MENU_OSD_SHOW_TEMP                 397
#define LANG_MENU_FAST_SWITCH_QUALITY_VIDEO     398

#define LANG_MENU_REMOTE_ZOOM_ENABLE            399
#define LANG_MENU_REMOTE_ZOOM_TIMEOUT           400
#define LANG_MENU_MISC_START_SOUND              401
#define LANG_MENU_SUB_PREFIX                    402
#define LANG_MENU_SUB_EXTENSION                 403
#define LANG_MENU_SUB_IN_DARK_VALUE             404
#define LANG_MENU_SUB_OUT_DARK_VALUE            405
#define LANG_FSELECT_SUB_FROM                   406
#define LANG_FSELECT_SUB_AND_MORE               407
#define LANG_FSELECT_SUBTRACT                   408
#define LANG_POPUP_SUB_FROM_MARKED              409
#define LANG_MENU_SCRIPT_PARAM_SAVE             410
#define LANG_OSD_LAYOUT_EDITOR_EV_VIDEO         411
#define	LANG_MENU_OVERRIDE_ZOOM_VALUE           412
#define	LANG_MENU_OVERRIDE_ZOOM                 413
#define LANG_MENU_CLEAR_ZOOM_OVERRIDE_VALUES    414
#define LANG_MENU_BRACKETING_ADD_RAW_SUFFIX     415
#define LANG_MENU_OSD_TEMP_FAHRENHEIT           416
#define LANG_MENU_EDGE_LOAD                     417
#define LANG_MENU_EDGE_SAVE                     418
#define LANG_MENU_EDGE_PLAY                     419
#define LANG_MENU_EDGE_ZOOM                     421
#define LANG_MENU_EDGE_PANO                     422
#define LANG_MENU_REAR_CURTAIN                  423 
#define LANG_MENU_DNG_FORMAT                    424
#define LANG_MENU_RAW_CACHED                    425
#define LANG_CANNOT_OPEN_BADPIXEL_FILE          426
#define LANG_MENU_RAW_TIMER                     427

#define LANG_MENU_GAMES_CONNECT4                428
#define LANG_CONNECT4_RIVAL                     429
#define LANG_CONNECT4_HUMAN                     430
#define LANG_CONNECT4_P1_WIN                    431
#define LANG_CONNECT4_P2_WIN                    432
#define LANG_CONNECT4_CAM_WIN                   433
#define LANG_CONNECT4_DRAW                      434

#define LANG_MENU_RAW_SAVE_IN_EDGEOVERLAY       435
#define LANG_MENU_RAW_SAVE_IN_AUTO              436
#define LANG_MENU_FLASH_VIDEO_OVERRIDE          437
#define LANG_MENU_RAW_DNG_EXT                   439
#define LANG_MENU_DNG_VIA_USB                   440 
#define LANG_MENU_GAMES_MASTERMIND              441
#define LANG_MENU_GAMES_AC_COLORS               442
#define LANG_MENU_GAMES_RIGHT_PLACE             443
#define LANG_MENU_GAMES_C_IN_ANSWER             444
#define LANG_MENU_GAMES_RIGHT                   445
#define LANG_MENU_GAMES_GAME_OVER               446
#define LANG_MENU_GAMES_CURSOR1                 447
#define LANG_MENU_GAMES_CURSOR2                 448
#define LANG_MENU_GAMES_CURSOR3                 449
#define LANG_MENU_GAMES_DCOLOR                  450
#define LANG_MENU_RESET_FILES                   451
#define LANG_MENU_RESTART_CAMERA                452
#define LANG_MENU_FLASH_MANUAL_OVERRIDE         453
#define LANG_MENU_MISC_IMAGE_QUALITY            454
#define LANG_MENU_LUA_RESTART                   455
#define LANG_MENU_EDGE_FILTER                   456
#define LANG_MENU_EDGE_SHOW                     457
#define LANG_MENU_EDGE_PANO_OVERLAP             458
#define LANG_MENU_BADPIXEL_CREATE               459
#define LANG_MSG_RECMODE_REQUIRED               460
#define LANG_CONSOLE_SCRIPT_DISABLED_IN_BUILD   461

// Touch screen
#define LANG_MENU_TOUCHSCREEN_VALUES            462
#define LANG_MENU_TS_VIDEO_AE_DISABLE           463
#define LANG_MENU_TS_ALT_SHORTCUTS_DISABLE      464

#define LANG_OSD_LAYOUT_EDITOR_USB_INFO         465
#define LANG_MENU_USB_SHOW_INFO                 466

// Save ROM crash log messages
#define LANG_SAVE_ROMLOG                        467
#define LANG_SAVE_ROMLOG_INIT_ERROR             468
#define LANG_SAVE_ROMLOG_FAIL                   469
#define LANG_SAVE_ROMLOG_OK                     470

// next gen USB remote
#define LANG_MENU_REMOTE_DEVICE                 471
#define LANG_MENU_REMOTE_LOGIC                  472
#define LANG_MENU_REMOTE_OPTIONS                473

#define LANG_STR_TEXTBOX_SETTINGS               474
#define LANG_MENU_VIS_CHARMAP		            475
#define LANG_POPUP_MORE				            476
#define LANG_POPUP_MKDIR			            477
#define LANG_POPUP_RENAME			            478
#define LANG_PROMPT_MKDIR			            479
#define LANG_PROMPT_RENAME			            480
#define LANG_POPUP_RMDIR                        481

//CHDK-DE
#define LANG_MENU_CURVE_CURRENT                 482
#define LANG_MENU_GAMES_TETRIS                  482
#define LANG_MENU_SHOW_PARTITION_NR             484
#define LANG_MENU_VIDEO_EXT_TIME                485
#define LANG_WARN_VIDEO_EXT_TIME                486
//-------------------------------------------------------------------
// GPS
#define LANG_MENU_GPS                           487
#define LANG_MENU_GPS_NAVI_SHOW 	            488
#define LANG_MENU_GPS_KOMPASS_SHOW              489
#define LANG_MENU_GPS_COORDINATES_SHOW          490
#define LANG_MENU_GPS_HEIGHT_SHOW               491
#define LANG_MENU_GPS_WAYPOINT_SAVE             492
#define LANG_MENU_GPS_TRACK_TIME                493
#define LANG_MENU_GPS_TRACK_START               494
#define LANG_MENU_GPS_TRACK_STOP                495
#define LANG_MENU_GPS_KOMPASS_HIDE              496
#define LANG_MENU_GPS_NAVI_HIDE					497
#define LANG_MENU_GPS_WAIT_FOR_SIGNAL			498
#define LANG_MENU_GPS_KOMPASS_TIME				499
#define LANG_MENU_GPS_NAVI_TIME					500
#define LANG_MENU_GPS_REC_PLAY_TIME				501
#define LANG_MENU_GPS_PLAY_DARK_TIME			502
#define LANG_MENU_GPS_VALUES					503
#define LANG_MENU_GPS_WAIT_FOR_SIGNAL_TIME		504
#define LANG_MENU_GPS_KOMPASS_SMOOTH			505
#define LANG_MENU_GPS_LOGGING				    506
#define LANG_MENU_GPS_TAGGING					507
#define LANG_MENU_GPS_NAVIGATION				508
#define LANG_MENU_GPS_BATT						509
#define LANG_MENU_GPS_COUNTDOWN					510
#define LANG_MENU_GPS_2D_3D_FIX					511
#define LANG_MENU_GPS_COUNTDOWN_BLINK			512
#define LANG_MENU_GPS_REC_PLAY_SET				513
#define LANG_MENU_GPS_PLAY_DARK_SET				514
#define LANG_MENU_GPS_REC_PLAY_SET_1			515
#define LANG_MENU_GPS_PLAY_DARK_SET_1			516
#define LANG_MENU_GPS_REC_PLAY_TIME_1			517
#define LANG_MENU_GPS_PLAY_DARK_TIME_1			518
#define LANG_MENU_GPS_SYMBOL_SHOW				519
#define LANG_MENU_GPS_BATT_WARNING				520
#define LANG_MENU_GPS_MARK_HOME					521
#define LANG_MENU_GPS_NAVI_HOME					522
#define LANG_MENU_GPS_MARK_TIMEZONE				523
#define LANG_MENU_GPS_TRACK_SYMBOL				524
#define LANG_MENU_GPS_NAVI_HOME_END				525
#define LANG_MENU_GPS_TEST_TIMEZONE				526
#define LANG_MENU_GPS_BEEP_WARNING				527
#define LANG_MENU_GPS_ON_OFF					528
#define LANG_MENU_GPS_t_1 						529
#define LANG_MENU_GPS_t_2  						530
#define LANG_MENU_GPS_t_3  						531
#define LANG_MENU_GPS_t_4  						532
#define LANG_MENU_GPS_t_5  						533
#define LANG_MENU_GPS_t_6  						534
#define LANG_MENU_GPS_t_7  						535
#define LANG_MENU_GPS_t_8  						536
#define LANG_MENU_GPS_t_9  						537
#define LANG_MENU_GPS_t_10 						538
#define LANG_MENU_GPS_t_11 						539
#define LANG_MENU_GPS_t_12 						540
#define LANG_MENU_GPS_t_13 						541
#define LANG_MENU_GPS_t_14 						542
#define LANG_MENU_GPS_t_15 						543
#define LANG_MENU_GPS_t_16 						544
#define LANG_MENU_GPS_t_17 						545	

#define LANG_MENU_AUTOISO_MIN_SHUTTER2   		546
#define LANG_MENU_AUTOISO_MAX_ISO2       		547
#define LANG_MENU_AUTOISO_OVEREXP_EV     		548
#define LANG_MENU_AUTOISO_OVEREXP_THRES  		549

#define LANG_MENU_GPS_t_18 						550

#define LANG_MENU_SCRIPT_START_ENABLE			551
#define LANG_MENU_MISC_ZOOM_ASSIST              552
#define LANG_MENU_DNG_VERSION                   553
#define LANG_MENU_MENU_SETTINGS                 554
#define LANG_MENU_SHOW_ALT_HELP                 555
#define LANG_MENU_SHOW_ALT_HELP_DELAY           556
#define LANG_MENU_CHDK_SETTINGS                 557

// <ALT> mode help screen text
#define LANG_HELP_HEADER                        558
#define LANG_HELP_ALT_SHORTCUTS                 559
#define LANG_HELP_HALF_PRESS                    560
#define LANG_HELP_CHDK_MENU                     561
#define LANG_HELP_USER_MENU                     562
#define LANG_HELP_SCRIPTS                       563
#define LANG_HELP_FOCUS                         564
#define LANG_HELP_MANUAL_FOCUS                  565
#define LANG_HELP_HIDE_OSD                      566
#define LANG_HELP_NOT_ALT                       567

#define LANG_USER_MENU_ITEM_ADDED				568
#define LANG_USER_MENU_FULL     				569

#define LANG_SD_CARD                            570
#define LANG_MENU_FONT_SETTINGS                 571

#define LANG_MENU_USER_MENU_SCRIPT_ADD          572

#define LANG_HELP_INF_FOCUS                     573
#define LANG_HELP_CHG_FOCUS_FACTOR              574

#define LANG_MENU_MISC_EXTRA_BUTTON             575

#define LANG_MENU_MODULES                       576
#define LANG_MENU_MODULE_INSPECTOR              577
#define LANG_MENU_MODULE_LOGGING                578
#define LANG_MENU_DELETE_MODULE_LOG             579

#define GUI_LANG_ITEMS                          579

//-------------------------------------------------------------------
extern void gui_lang_init();

//-------------------------------------------------------------------
#endif
