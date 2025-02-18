// CHDK palette colors for the sx130is

// Define color values as needed in this file.
// Values not defined here will be set to default values in core/gui_draw.h
// See comments in core/gui_draw.h for more details on CHDK color definitions.

    #define COLOR_WHITE                 0x01
    #define COLOR_RED                   0x1e
    #define COLOR_GREY                  0x1a
    #define COLOR_GREEN                 0x17
    #define COLOR_BLUE_LT               0x10
    #define COLOR_BLUE                  0x14
    #define COLOR_YELLOW                0x60
    #define COLOR_GREY_DK               0x62
    #define COLOR_RED_DK                COLOR_RED
    #define COLOR_RED_LT                0x1e        // Orange
    #define COLOR_GREY_LT               0x16
    // Override histogram colors if needed
    #define COLOR_REC_RED               0x66
    #define COLOR_PLY_RED               0xA0
    #define COLOR_REC_BLUE              0x61
    #define COLOR_PLY_BLUE              0xA2
    #define COLOR_REC_GREEN             0x5F
    #define COLOR_PLY_GREEN             0xA1
    #define COLOR_REC_MAGENTA           COLOR_RED
    #define COLOR_PLY_MAGENTA           COLOR_REC_MAGENTA
    #define COLOR_PLY_YELLOW            0x80

// Icon colors
// 3 shades of Red, Green, Yellow and Grey
// Separate definitions for record and playback mode
// to cater for cameras with variable palettes
    #define COLOR_ICON_REC_RED          0x66
    #define COLOR_ICON_REC_RED_DK       0x66
    #define COLOR_ICON_REC_RED_LT       0x66
    #define COLOR_ICON_REC_GREEN        0x6B
    #define COLOR_ICON_REC_GREEN_DK     0x6B
    #define COLOR_ICON_REC_GREEN_LT     0x69
    #define COLOR_ICON_REC_YELLOW       0x60
    #define COLOR_ICON_REC_YELLOW_DK    0x45
    #define COLOR_ICON_REC_YELLOW_LT    0x6C
    #define COLOR_ICON_REC_GREY         COLOR_GREY
    #define COLOR_ICON_REC_GREY_DK      0x19
    #define COLOR_ICON_REC_GREY_LT      0x10
    #define COLOR_ICON_PLY_RED          0xA0
    #define COLOR_ICON_PLY_RED_DK       0xA0
    #define COLOR_ICON_PLY_RED_LT       0xA0
    #define COLOR_ICON_PLY_GREEN        0xA1
    #define COLOR_ICON_PLY_GREEN_DK     0xA1
    #define COLOR_ICON_PLY_GREEN_LT     0xA1
    #define COLOR_ICON_PLY_YELLOW       0x6A
    #define COLOR_ICON_PLY_YELLOW_DK    0x6F
    #define COLOR_ICON_PLY_YELLOW_LT    0x63
    #define COLOR_ICON_PLY_GREY         COLOR_ICON_REC_GREY
    #define COLOR_ICON_PLY_GREY_DK      COLOR_ICON_REC_GREY_DK
    #define COLOR_ICON_PLY_GREY_LT      COLOR_ICON_REC_GREY_LT

