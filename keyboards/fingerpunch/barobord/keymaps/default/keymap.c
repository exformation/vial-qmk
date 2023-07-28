#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_barobord(
      _______,         _______,      _______,      _______,      _______,      _______,    _______,      _______,      _______,      _______,
      _______,         0,            1,            2,            3,            13,         12,           11,           10,           _______,
      _______,         4,            5,            6,            7,            17,         16,           15,           14,           _______,
      _______,         _______,      _______,      8,            9,            19,         18,           _______,      _______,      _______,
                                                                 _______,      _______  // These are for the rotary encoders
    ),
};


static uint16_t state;
uint16_t start = 0;
enum SIDE{NONE,RIGHT,LEFT};
enum SIDE side = NONE;
#define r 1<<0
#define s 1<<1
#define n 1<<2
#define i 1<<3
#define a 1<<4
#define o 1<<5
#define t 1<<6
#define e 1<<7
#define it 1<<8
#define ot 1<<9

static void process(uint16_t val) {
    uint16_t v = 0;
    // uint16_t thumb = 0;
    switch (val) {
        case e: v=KC_E;break;
        case t: v=KC_T;break;
        case o: v=KC_O; break;
        case a: v=KC_A;break;
        case e|t: v=KC_H;break;
        case t|o: v=KC_U;break;
        default: v=0;
    }
    if(v) {
        tap_code16(v);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(record->event.pressed) {
        if(side == keycode/10+1){
            state |= 1 << (keycode%10); 
        } else {
            if(side != NONE) {
                process(state);
                state = 0;
            }
            side = keycode/10+1;
            state |= 1 << (keycode%10);
        }
    } else {
        process(state);
        state = 0;
    }
    return false;
};

