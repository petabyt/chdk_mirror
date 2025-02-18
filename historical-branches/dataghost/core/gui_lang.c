#include "conf.h"
#include "lang.h"
#include "gui_lang.h"

//-------------------------------------------------------------------
static char* gui_lang_default = \
"  1 \"Main Menu\"\n"

"  2 \"RAW parameters ->\"\n"
"  3 \"OSD parameters ->\"\n"
"  4 \"Histogram parameters ->\"\n"
"  5 \"Zebra parameters ->\"\n"
"  6 \"Scripting parameters ->\"\n"
"  7 \"Visual settings ->\"\n"
"  8 \"Miscellaneous stuff ->\"\n"
"  9 \"Debug parameters ->\"\n"
" 10 \"Reset options to default...\"\n"
" 11 \"Save options now...\"\n"

" 12 \"<- Back\"\n"


" 13 \"RAW\"\n"

" 14 \"Save RAW\"\n"
" 16 \"Only first RAW in series\"\n"
" 17 \"RAW file in dir with JPEG\"\n"
" 18 \"RAW file prefix\"\n"
" 19 \"RAW file extension\"\n"


" 20 \"OSD\"\n"

" 21 \"Show OSD\"\n"
" 22 \"Show State\"\n"
" 23 \"Show misc values\"\n"
" 24 \" Show Zoom value as\"\n"
" 25 \"Show DOF calculator\"\n"
" 26 \"Show clock\"\n"
" 27 \"OSD layout editor\"\n"
" 28 \"Battery->\"\n"


" 29 \"Histogram\"\n"

" 30 \"Show live histogram\"\n"
" 31 \"Histogram layout\"\n"
" 32 \"Histogram mode\"\n"
" 33 \"Show histogram over/under EXP\"\n"
" 34 \"Ignore boundary peaks\"\n"
" 35 \"Auto magnify\"\n"


" 36 \"Zebra\"\n"

" 37 \"Draw Zebra\"\n"
" 38 \"Zebra mode\"\n"
" 39 \"UnderExposure threshold\"\n"
" 40 \"OverExposure threshold\"\n"
" 41 \"Restore original screen\"\n"
" 42 \"Restore OSD\"\n"
" 43 \"Draw over zebra\"\n"


" 44 \"Script\"\n"

" 45 \"Load script from file...\"\n"
" 46 \"Script shoot delay (.1s)\"\n"
" 47 \"Current script\"\n"
" 48 \"Script parameters\"\n"


" 49 \"Visual settings\"\n"

" 50 \"Language...\"\n"
" 51 \"OSD codepage\"\n"
" 52 \"Menu RBF font...\"\n"
" 53 \"Colors\"\n"
" 54 \"OSD text\"\n"
" 55 \"OSD background\"\n"
" 56 \"Histogram\"\n"
" 57 \"Histogram background\"\n"
" 58 \"Histogram border\"\n"
" 59 \"Histogram EXP markers\"\n"
" 60 \"Zebra Underexposure\"\n"
" 61 \"Zebra Overexposure\"\n"
" 62 \"Battery icon\"\n"
" 63 \"Menu text\"\n"
" 64 \"Menu background\"\n"
" 65 \"Text reader text\"\n"
" 66 \"Text reader background\"\n"


" 67 \"Miscellaneous\"\n"

" 68 \"File browser\"\n"
" 69 \"Calendar\"\n"
" 70 \"Text file reader ->\"\n"
" 71 \"Games ->\"\n"
" 72 \"Flashlight\"\n"
" 73 \"Show splash screen on load\"\n"
" 74 \"Use zoom buttons for MF\"\n"
" 75 \"<ALT> mode button\"\n"
" 76 \"Draw palette\"\n"
" 77 \"Show build info\"\n"
" 78 \"Show memory info\"\n"


" 79 \"Debug\"\n"

" 80 \"Show PropCases\"\n"
" 81 \"PropCase/ParamsData page\"\n"
" 82 \"Show misc. values\"\n"
" 83 \"Memory browser\"\n"
" 84 \"Dump RAM on ALT +/- press\"\n"
" 85 \"Make card bootable...\"\n"

" 86 \"Battery showing settings\"\n"

" 87 \"Battery MAX Voltage (mV)\"\n"
" 88 \"Battery MIN Voltage (mV)\"\n"
" 89 \"Step Size (ON=25,OFF=1 mV)\"\n"
" 90 \"Show Battery percent\"\n"
" 91 \"Show Battery volts\"\n"
" 92 \"Show Battery icon\"\n"


" 93 \"Text file reader\"\n"

" 94 \"Open new file...\"\n"
" 95 \"Open last opened file\"\n"
" 96 \"Select RBF font\"\n"
" 97 \"Codepage\"\n"
" 98 \"Wrap by words\"\n"
" 99 \"Enable autoscroll\"\n"
"100 \"Autoscroll delay (sec)\"\n"


"101 \"Games\"\n"

"102 \"Reversi\"\n"
"103 \"Sokoban\"\n"

"104 \"*** Reset options ***\"\n"
"105 \"Are you SURE to reset\\noptions to default?\"\n"

"106 \"*** Build Info ***\"\n"
"107 \"CHDK Ver: %s, #%s\\nDate:    %s\\nTime:    %s\\nCamera:  %s\\nFW Vers: %s\"\n"

"108 \"*** Memory Info ***\"\n"
"109 \"Free memory: %d bytes\"\n"

"110 \"*** Information ***\"\n"
"111 \"Please switch your camera\\nto PLAY mode\\nand try again. :)\"\n"

"112 \"File Browser\"\n"
"113 \"Select script file\"\n"
"114 \"Select text file\"\n"
"115 \"Select RBF-font file\"\n"
"116 \"Select language file\"\n"

"117 \"January\"\n"
"118 \"February\"\n"
"119 \"March\"\n"
"120 \"April\"\n"
"121 \"May\"\n"
"122 \"June\"\n"
"123 \"July\"\n"
"124 \"August\"\n"
"125 \"September\"\n"
"126 \"October\"\n"
"127 \"November\"\n"
"128 \"December\"\n"

"129 \"Mon\"\n"
"130 \"Tue\"\n"
"131 \"Wed\"\n"
"132 \"Thu\"\n"
"133 \"Fri\"\n"
"134 \"Sat\"\n"
"135 \"Sun\"\n"

"136 \"Today:\"\n"

"137 \"Ok\"\n"
"138 \"Yes\"\n"
"139 \"No\"\n"
"140 \"Cancel\"\n"

"141 \"Histogram\"\n"
"142 \"DOF calc\"\n"
"143 \"RAW/EXP\"\n"
"144 \"Misc values\"\n"
"145 \"Batt icon\"\n"
"146 \"Batt text\"\n"
"147 \"Clock\"\n"

"148 \"Press SET to draw particular color\"\n"
"149 \"       Press MENU to exit         \"\n"
"150 \"Color\"\n"
"151 \"Use %s to select color\"\n"

"152 \"*** Game Results ***\"\n"
"153 \"You won the game! :)\"\n"
"154 \"You lost the game! :(\"\n"
"155 \"Draw! :/\"\n"

"156 \"*** Wrong move ***\"\n"
"157 \"You can't place here!\"\n"
"158 \"This cell is not empty!\"\n"

"159 \"Move: You     \"\n"
"160 \"Move: Computer\"\n"
"161 \"  GAME  OVER  \"\n"
"162 \" White  Black \"\n"

"163 \"*** About ***\"\n"

"164 \"  Level\"\n"
"165 \"  Moves\"\n"
"166 \"*** Finished ***\"\n"
"167 \"YES!\\n  You did it!  \"\n"

"168 \"*** STARTED ***\"\n"
"169 \"*** INTERRUPTED ***\"\n"
"170 \"*** FINISHED ***\"\n"

"171 \"*** Erase directory ***\"\n"
"172 \"Are you SURE to delete\\nALL files from\\nselected directory?\"\n"
"173 \"*** Delete file ***\"\n"
"174 \"Are you SURE to delete\\nselected file?\"\n"

"175 \"Benchmark\"\n"
"176 \"Calculating...\"\n"
"177 \"Camera benchmark   Press [set] to start\"\n"
"178 \"Screen\"\n"
"179 \"Write       :\"\n"
"180 \"Read        :\"\n"
"181 \"Memory\"\n"
"182 \"Flash-card\"\n"
"183 \"Write (RAW) :\"\n"
"184 \"Write (Mem) :\"\n"
"185 \"Write (64k) :\"\n"
"186 \"Read  (64k) :\"\n"

"187 \"Disable LCD off\"\n"

"188 \"Cut\"\n"
"189 \"Copy\"\n"
"190 \"Paste\"\n"
"191 \"Delete\"\n"
"192 \"Select inverse\"\n"
"193 \"*** Cut files ***\"\n"
"194 \"Are you SURE to cut\\n%d selected files\\nfrom %s/?\"\n"
"195 \"*** Copy files ***\"\n"
"196 \"Are you SURE to copy\\n%d selected files\\nfrom %s/?\"\n"
"197 \"*** Delete files ***\"\n"
"198 \"Are you SURE to delete\\n%d selected files?\"\n"
"199 \"Please wait...\"\n"

"200 \"Show grid lines\"\n"
"201 \"Load grid from file...\"\n"
"202 \"Grid lines\"\n"
"203 \"Grid->\"\n"
"204 \"Select grid file\"\n"
"205 \"Current grid\"\n"

"206 \"Noise reduction\"\n"

"207 \"Override grid colors\"\n"
"208 \"Line color\"\n"
"209 \"Fill color\"\n"

"210 \"DOF Calculator\"\n"
"211 \"DOF Calculator->\"\n"
"212 \"Canon Subj. Dist. as Near Limit\"\n"
"213 \"Use EXIF Subj. Dist. (PC65)\"\n"
"214 \"Show Subj. Dist. in Misc.\"\n"
"215 \"Show Near Limit in Misc.\"\n"
"216 \"Show Far Limit in Misc.\"\n"
"217 \"Show Hyperfocal Dist. in Misc.\"\n"
"218 \"Show Depth of Field in Misc.\"\n"

"219 \"Miscellaneous Values\"\n"		
"220 \"Miscellaneous Values->\"\n"		
"221 \"Show in Review mode\"\n"		
"222 \"Show Zoom\"\n"		
"223 \"Show 'real' Aperture\"\n"
"224 \"Show 'real' ISO\"\n"
"225 \"Show 'market' ISO\"\n"
"226 \" Show ISO only in Autoiso mode\"\n"
"227 \"Show Set Exposure Ev (Tv+Av)\"\n"
"228 \"Show Measured Ev (Bv+Sv)\"\n"
"229 \"Show Set Bv (Brightness Value)\"\n"
"230 \"Show Measured Bv\"\n"
"231 \"Show Overexp. Value (No Flash!)\"\n"
"232 \"Show Scene luminance (cd/m2)\"\n"

"233 \"Video Parameters\"\n"
"234 \"Video Parameters->\"\n"
"235 \"Video Mode\"\n"
"236 \"Video Bitrate\"\n"
"237 \"Video Quality\"\n"

"238 \"Extra Photo Operations\"\n"
"239 \"Extra Photo Operations->\"\n"
"240 \"Override shutter speed\"\n"
"241 \"   Value factor\"\n"
"242 \"Override aperture\"\n"
"243 \"Override ISO value\"\n"
"244 \"   Value factor\"\n"
"245 \"Override Subj. Dist. Value (MF)\"\n"
"246 \"   Value factor (mm)\"\n"

"247 \"Bracketing in continuous mode\"\n"
"248 \"Bracketing in continuous mode->\"\n"
"249 \"TV bracketing value\"\n"
"250 \"AV bracketing value\"\n"
"251 \"ISO bracketing value\"\n"
"252 \"    Value factor\"\n"
"253 \"Subj. Dist. Bracket Value (MF)\"\n"
"254 \"    Value factor (mm)\"\n"
"255 \"Bracketing type\"\n"

"256 \"Script Autostart\"\n"
"257 \"Enable remote (USB)->\"\n"

"258 \"Exposure control (no flash)\"\n"
"259 \"Exposure control (no flash)->\"\n"
"260 \"Recalc Exposure\"\n"
"261 \"TV Exposure recalc order\"\n"
"262 \"AV Exposure recalc order\"\n"
"263 \"ISO Exposure recalc order\"\n"

"264 \"Clear override values on start\"\n"

"265 \"Show Canon overexp. value\"\n"

"266 \"RAW develop\"\n"
"267 \"Please switch camera\\nto record mode and take\\none shot.\"\n"
"268 \"Select RAW file\"\n"
"269 \"RAW sum\"\n"
"270 \"RAW average\"\n"
"271 \"Not enough memory card space:\\n%dM required, %dM available.\"\n"

"272 \"Show OSD in Review Mode\"\n"
"273 \"Show Parameter Data\"\n"

"274 \"Subject distance from lens\"\n"

"275 \"Clear Bracket Values on Start\"\n"

"276 \"Create card with two partitions\"\n"
"277 \"Swap partitions\"\n"
"278 \"This DESTROYS ALL INFORMATION\\non card. Continue?\"\n"
"279 \"This card has only one partition.\"\n"
"280 \"Error\"\n"
"281 \"Warning\"\n"
"282 \"Information\"\n"
"283 \"RGB zebra (overexp. only)\"\n"

"284 \"ND filter state\"\n"

"285 \"Show Histo Ev Grid\"\n"

"286 \"OSD Warning\"\n"
"287 \"OSD Warning Background\"\n"
"288 \"Remaining Space Icon Color\"\n"
"289 \"Show Filespace Icon\"\n"
"290 \"Remaining Space\"\n"
"291 \"Show Filespace in Percent\"\n"
"292 \"Show Filespace in MB\"\n"
"293 \"Filespace Text\"\n"
"294 \"  Show RAW shoot remain\"\n"
"295 \"Remaining RAW\"\n"
"296 \"Show RAW state \"\n"

"297 \"Show values in video\"\n"

"298 \"  Shutter speed enum type\"\n"
"299 \"User Menu Enable\"\n"
"300 \"User Menu\"\n"
"301 \" \"\n"

"302 \" Adapter Lens Scale, 100=1x\"\n"
"303 \"Show Space Bar\"\n"
"304 \"  Size on Screen\"\n"
"305 \"  Width/Height\"\n"
"306 \"  % threshold\"\n"
"307 \"  MB threshold\"\n"
"308 \"Warning Unit\"\n"
"309 \"  Warning threshold\"\n"
"310 \"Enable optical zoom\"\n"
"311 \"Clock->\"\n"
"312 \"Clock Settings\"\n"
"313 \"Clock format\"\n"
"314 \"Remaining Space Background Color\"\n"
"315 \"12h Clock Indicator\"\n"
"316 \"@Shutter half-press show\"\n"

"317 \"Raw showing settings\"\n"
"318 \"Raw->\"\n"

"319 \"Filespace showing settings\"\n"
"320 \"Filespace->\"\n"

"321 \"Custom Auto ISO\"\n"
"322 \"Custom Auto ISO->\"\n"
"323 \"Enable Custom Auto ISO\"\n"
"324 \"Minimal Shutter speed\"\n"
"325 \"User Factor (1/FL/factor)\"\n"
"326 \"IS Factor (Tv*factor)\"\n"
"327 \"Max ISO HI (x10)\"\n"
"328 \"Max ISO AUTO (x10)\"\n"
"329 \"Min ISO (x10)\"\n"

"330 \"Menu Title Text Color\"\n" 
"331 \"Menu Title Background Color\"\n"
"332 \"Cursor Text Color\"\n" 
"333 \"Cursor Background Color\"\n"
"334 \"Center Menu\"\n"

"335 \"DataGhost's menu ->\"\n"
"336 \"DataGhost's menu\"\n"
"337 \"Adjust IS lens position\"\n"
"338 \"Find IS lens center\"\n"
"339 \"Post LED messages ->\"\n"
"340 \"LED disco\"\n"
"341 \"Display brightness ->\"\n"

"342 \"Display brightness\"\n"
"343 \"Canon LCD low brightness\"\n"
"344 \"Canon LCD high brightness\"\n"
"345 \"Canon EVF low brightness\"\n"
"346 \"Canon EVF high brightness\"\n"
"347 \"Current LCD brightness\"\n"
"348 \"Current EVF brightness\"\n"

"349 \"Please switch your camera\\nto REC mode\\nand try again. :)\"\n"

"350 \"IS Lens adjustment\"\n"
"351 \"\x18\x19\x1b\x1a: position the lens\\nZOOM: set position step size\\n SET: reset to default settings\\nMENU: return\"\n"
"352 \"Pitch: set 0x%3X,  cur 0x%3X\"\n"
"353 \"Yaw:   set 0x%3X,  cur 0x%3X\"\n"
"354 \"Step: %3d\"\n"
"355 \"WARNING: Use of this feature may\\ndamage the IS lens mechanism.\\nThe camera will now determine the\\nlimits. You can toggle the limit\\noverride by pressing the FUNC key.\\n\\nDo you want to continue?\"\n"
"356 \"ERROR: Assertion failed, default IS\\nlens position is not within IS lens\\nlimits. This should never happen.\\nPlease do not use this feature\\nunless you know what you're doing.\"\n"
"357 \"CAUTION! LIMIT OVERRIDE ENABLED, CAMERA MAY\"\n"
"358 \"BE DAMAGED! READ ONLINE DOCS FOR MORE INFO\"\n"

"359 \"Post LED messages\"\n"
"360 \"LED number\"\n"
"361 \"Action\"\n"
"362 \"Brightness\"\n"
"363 \"Blink count\"\n"
"364 \"Post message\"\n"

"365 \"Turn on display\"\n"
"366 \"Turn off display\"\n"
"367 \"Turn on backlight\"\n"
"368 \"Turn off backlight\"\n"

"369 \"Quick debugger (code of the day)\"\n"

"370 \"Advanced memory viewer\"\n"

"371 \"IS Menu ->\"\n"
"372 \"IS Menu\"\n"
"373 \"Show IS internals\"\n"

"374 \"Hall dev off. P:   %2X, Y:   %2X\"\n"
"375 \"Hall dev gain P:   %2X, Y:   %2X\"\n"
"376 \"Gyro offset   P: %4X, Y: %4X\"\n"
"377 \"Gyro gain     P:   %2X, Y:   %2X\"\n"
"378 \"Lens cent. ax.A: %4X, B: %4X\"\n"
"379 \"Lens EVi axis A: %6d, B: %6d\"\n"
"380 \"Lens damp ax. A: %4X, B: %4X\"\n"
"381 \"Lens PWM      P: %4X, Y: %4X\"\n"
"382 \"Lens position P: %4X, Y: %4X\"\n"
"383 \"Camera orientation demo\"\n"

"384 \"Show IS intern. ontop (non-ALT)\"\n"
"385 \"Show IS intern2 ontop (non-ALT)\"\n"

"386 \"Show IS internals 2\"\n"

"387 \"Drive     A: %4X, B: %4X\"\n"
"388 \"Pos       A: %4X, B: %4X\"\n"
"389 \"Hall off  A:   %2X, B:   %2X\"\n"
"390 \"Hall gain A:   %2X, B:   %2X\"\n"
"391 \"Gyro gain A:   %2X, B:   %2X\"\n"
"392 \"Coeff P   A: %4X, B: %4X\"\n"
"393 \"Coeff I   A: %4X, B: %4X\"\n"
"394 \"Coeff D   A: %4X, B: %4X\"\n"
"395 \"PLF       A: %4X, B: %4X\"\n"
"396 \"LPF       A: %4X, B: %4X\"\n"
"397 \"Damp      A: %4X, B: %4X\"\n"
"398 \"EVi       A: %6d, B: %6d\"\n"

"399 \"Fast-draw game test\"\n"

"400 \"Draw camera log on screen\"\n"
"401 \"Log camera log to file\"\n"
"402 \"Stop logging camera log to file\"\n"
"403 \"Resume logging camera log to file\"\n"

"404 \"Firmware dumping ->\"\n"
"405 \"Firmware dumping\"\n"
"406 \"FW start address\"\n"
"407 \"Dump FW to A/PRIMARY.BIN\"\n"

;

/* Virtual screen

----------------------------------- <-- MBOX
------------------------------------------- <- Screen


*/


//-------------------------------------------------------------------
void gui_lang_init() {
    lang_init(GUI_LANG_ITEMS);
    lang_load_from_mem(gui_lang_default);
    if (conf.lang_file && *conf.lang_file) {
        lang_load_from_file(conf.lang_file);
    }
}

//-------------------------------------------------------------------
