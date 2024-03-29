#pragma once

#include "USBHost_t36.h"
#include "keylayouts.h"

enum KeyCodes : uint8_t {
    UP =           KEYD_UP,        //0xDA
    DOWN =         KEYD_DOWN,      //0xD9
    LEFT =         KEYD_LEFT,      //0xD8
    RIGHT =        KEYD_RIGHT,     //0xD7
    INSERT =       KEYD_INSERT,    //0xD1
    DELETE =       KEYD_DELETE,    //0xD4
    PAGE_UP =      KEYD_PAGE_UP,   //0xD3
    PAGE_DOWN =    KEYD_PAGE_DOWN, //0xD6
    HOME =         KEYD_HOME,      //0xD2
    END =          KEYD_END,       //0xD5
    F1 =           KEYD_F1,        //0xC2
    F2 =           KEYD_F2,        //0xC3
    F3 =           KEYD_F3,        //0xC4
    F4 =           KEYD_F4,        //0xC5
    F5 =           KEYD_F5,        //0xC6
    F6 =           KEYD_F6,        //0xC7
    F7 =           KEYD_F7,        //0xC8
    F8 =           KEYD_F8,        //0xC9
    F9 =           KEYD_F9,        //0xCA
    F10 =          KEYD_F10,       //0xCB
    F11 =          KEYD_F11,       //0xCC
    F12 =          KEYD_F12,       //0xCD
};

enum KeyModifiers : uint8_t {
    CTRL            = 0x01, // MODIFIERKEY_CTRL 
    SHIFT           = 0x02, // MODIFIERKEY_SHIFT
    ALT             = 0x04, // MODIFIERKEY_ALT
    GUI             = 0x08, // MODIFIERKEY_GUI
    LEFT_CTRL       = 0x01, // MODIFIERKEY_LEFT_CTRL
    LEFT_SHIFT      = 0x02, // MODIFIERKEY_LEFT_SHIFT
    LEFT_ALT        = 0x04, // MODIFIERKEY_LEFT_ALT
    LEFT_GUI        = 0x08, // MODIFIERKEY_LEFT_GUI
    RIGHT_CTRL      = 0x10, // MODIFIERKEY_RIGHT_CTRL
    RIGHT_SHIFT     = 0x20, // MODIFIERKEY_RIGHT_SHIFT
    RIGHT_ALT       = 0x40, // MODIFIERKEY_RIGHT_ALT
    RIGHT_GUI       = 0x80, // MODIFIERKEY_RIGHT_GUI
};

// #define KEY_SYSTEM_POWER_DOWN   ( 0x81 | 0xE200 )
// #define KEY_SYSTEM_SLEEP        ( 0x82 | 0xE200 )
// #define KEY_SYSTEM_WAKE_UP      ( 0x83 | 0xE200 )

// #define KEY_MEDIA_PLAY          ( 0xB0 | 0xE400 )
// #define KEY_MEDIA_PAUSE         ( 0xB1 | 0xE400 )
// #define KEY_MEDIA_RECORD        ( 0xB2 | 0xE400 )
// #define KEY_MEDIA_FAST_FORWARD  ( 0xB3 | 0xE400 )
// #define KEY_MEDIA_REWIND        ( 0xB4 | 0xE400 )
// #define KEY_MEDIA_NEXT_TRACK    ( 0xB5 | 0xE400 )
// #define KEY_MEDIA_PREV_TRACK    ( 0xB6 | 0xE400 )
// #define KEY_MEDIA_STOP          ( 0xB7 | 0xE400 )
// #define KEY_MEDIA_EJECT         ( 0xB8 | 0xE400 )
// #define KEY_MEDIA_RANDOM_PLAY   ( 0xB9 | 0xE400 )
// #define KEY_MEDIA_PLAY_PAUSE    ( 0xCD | 0xE400 )
// #define KEY_MEDIA_PLAY_SKIP     ( 0xCE | 0xE400 )
// #define KEY_MEDIA_MUTE          ( 0xE2 | 0xE400 )
// #define KEY_MEDIA_VOLUME_INC    ( 0xE9 | 0xE400 )
// #define KEY_MEDIA_VOLUME_DEC    ( 0xEA | 0xE400 )

// #define KEY_A                   (   4  | 0xF000 )
// #define KEY_B                   (   5  | 0xF000 )
// #define KEY_C                   (   6  | 0xF000 )
// #define KEY_D                   (   7  | 0xF000 )
// #define KEY_E                   (   8  | 0xF000 )
// #define KEY_F                   (   9  | 0xF000 )
// #define KEY_G                   (  10  | 0xF000 )
// #define KEY_H                   (  11  | 0xF000 )
// #define KEY_I                   (  12  | 0xF000 )
// #define KEY_J                   (  13  | 0xF000 )
// #define KEY_K                   (  14  | 0xF000 )
// #define KEY_L                   (  15  | 0xF000 )
// #define KEY_M                   (  16  | 0xF000 )
// #define KEY_N                   (  17  | 0xF000 )
// #define KEY_O                   (  18  | 0xF000 )
// #define KEY_P                   (  19  | 0xF000 )
// #define KEY_Q                   (  20  | 0xF000 )
// #define KEY_R                   (  21  | 0xF000 )
// #define KEY_S                   (  22  | 0xF000 )
// #define KEY_T                   (  23  | 0xF000 )
// #define KEY_U                   (  24  | 0xF000 )
// #define KEY_V                   (  25  | 0xF000 )
// #define KEY_W                   (  26  | 0xF000 )
// #define KEY_X                   (  27  | 0xF000 )
// #define KEY_Y                   (  28  | 0xF000 )
// #define KEY_Z                   (  29  | 0xF000 )
// #define KEY_1                   (  30  | 0xF000 )
// #define KEY_2                   (  31  | 0xF000 )
// #define KEY_3                   (  32  | 0xF000 )
// #define KEY_4                   (  33  | 0xF000 )
// #define KEY_5                   (  34  | 0xF000 )
// #define KEY_6                   (  35  | 0xF000 )
// #define KEY_7                   (  36  | 0xF000 )
// #define KEY_8                   (  37  | 0xF000 )
// #define KEY_9                   (  38  | 0xF000 )
// #define KEY_0                   (  39  | 0xF000 )
// #define KEY_ENTER               (  40  | 0xF000 )
// #define KEY_ESC                 (  41  | 0xF000 )
// #define KEY_BACKSPACE           (  42  | 0xF000 )
// #define KEY_TAB                 (  43  | 0xF000 )
// #define KEY_SPACE               (  44  | 0xF000 )
// #define KEY_MINUS               (  45  | 0xF000 )
// #define KEY_EQUAL               (  46  | 0xF000 )
// #define KEY_LEFT_BRACE          (  47  | 0xF000 )
// #define KEY_RIGHT_BRACE         (  48  | 0xF000 )
// #define KEY_BACKSLASH           (  49  | 0xF000 )
// #define KEY_NON_US_NUM          (  50  | 0xF000 )
// #define KEY_SEMICOLON           (  51  | 0xF000 )
// #define KEY_QUOTE               (  52  | 0xF000 )
// #define KEY_TILDE               (  53  | 0xF000 )
// #define KEY_COMMA               (  54  | 0xF000 )
// #define KEY_PERIOD              (  55  | 0xF000 )
// #define KEY_SLASH               (  56  | 0xF000 )
// #define KEY_CAPS_LOCK           (  57  | 0xF000 )
// #define KEY_F1                  (  58  | 0xF000 )
// #define KEY_F2                  (  59  | 0xF000 )
// #define KEY_F3                  (  60  | 0xF000 )
// #define KEY_F4                  (  61  | 0xF000 )
// #define KEY_F5                  (  62  | 0xF000 )
// #define KEY_F6                  (  63  | 0xF000 )
// #define KEY_F7                  (  64  | 0xF000 )
// #define KEY_F8                  (  65  | 0xF000 )
// #define KEY_F9                  (  66  | 0xF000 )
// #define KEY_F10                 (  67  | 0xF000 )
// #define KEY_F11                 (  68  | 0xF000 )
// #define KEY_F12                 (  69  | 0xF000 )
// #define KEY_PRINTSCREEN         (  70  | 0xF000 )
// #define KEY_SCROLL_LOCK         (  71  | 0xF000 )
// #define KEY_PAUSE               (  72  | 0xF000 )
// #define KEY_INSERT              (  73  | 0xF000 )
// #define KEY_HOME                (  74  | 0xF000 )
// #define KEY_PAGE_UP             (  75  | 0xF000 )
// #define KEY_DELETE              (  76  | 0xF000 )
// #define KEY_END                 (  77  | 0xF000 )
// #define KEY_PAGE_DOWN           (  78  | 0xF000 )
// #define KEY_RIGHT               (  79  | 0xF000 )
// #define KEY_LEFT                (  80  | 0xF000 )
// #define KEY_DOWN                (  81  | 0xF000 )
// #define KEY_UP                  (  82  | 0xF000 )
// #define KEY_NUM_LOCK            (  83  | 0xF000 )
// #define KEYPAD_SLASH            (  84  | 0xF000 )
// #define KEYPAD_ASTERIX          (  85  | 0xF000 )
// #define KEYPAD_MINUS            (  86  | 0xF000 )
// #define KEYPAD_PLUS             (  87  | 0xF000 )
// #define KEYPAD_ENTER            (  88  | 0xF000 )
// #define KEYPAD_1                (  89  | 0xF000 )
// #define KEYPAD_2                (  90  | 0xF000 )
// #define KEYPAD_3                (  91  | 0xF000 )
// #define KEYPAD_4                (  92  | 0xF000 )
// #define KEYPAD_5                (  93  | 0xF000 )
// #define KEYPAD_6                (  94  | 0xF000 )
// #define KEYPAD_7                (  95  | 0xF000 )
// #define KEYPAD_8                (  96  | 0xF000 )
// #define KEYPAD_9                (  97  | 0xF000 )
// #define KEYPAD_0                (  98  | 0xF000 )
// #define KEYPAD_PERIOD           (  99  | 0xF000 )
// #define KEY_NON_US_BS           ( 100  | 0xF000 )
// #define KEY_MENU        	       ( 101  | 0xF000 )
// #define KEY_F13                 ( 104  | 0xF000 )
// #define KEY_F14                 ( 105  | 0xF000 )
// #define KEY_F15                 ( 106  | 0xF000 )
// #define KEY_F16                 ( 107  | 0xF000 )
// #define KEY_F17                 ( 108  | 0xF000 )
// #define KEY_F18                 ( 109  | 0xF000 )
// #define KEY_F19                 ( 110  | 0xF000 )
// #define KEY_F20                 ( 111  | 0xF000 )
// #define KEY_F21                 ( 112  | 0xF000 )
// #define KEY_F22                 ( 113  | 0xF000 )
// #define KEY_F23                 ( 114  | 0xF000 )
// #define KEY_F24                 ( 115  | 0xF000 )
