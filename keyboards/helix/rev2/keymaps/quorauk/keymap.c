#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "keymap_uk.h"



#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _GAMING,
    _PLANCK,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOTION
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  GAMING,
  PLANCK,
  LOWER,
  RAISE,
  ADJUST,
  MOTION,
  MOTION_TAP,
  BACKLIT,
  EISU,
  KANA,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `    |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |--------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab    |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |--------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |Esc/CTRL|   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |Enter |
   * |--------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift  |   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |--------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |        |Adjust| Alt  | GUI  | Alt  |Space | Lower|Raise |Space |Motion| Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_GRV,        KC_1,    KC_2,    KC_3,    KC_4,     KC_5,                    KC_6,   KC_7,   KC_8,    KC_9,    KC_0,   KC_DEL, \
      KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,                    KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,   KC_BSPC, \
      CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT, \
      KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_LBRC, KC_RBRC, KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_NO,         ADJUST,  KC_LALT, KC_LGUI, KC_LALT, KC_SPC, LOWER,   RAISE,   KC_SPC, MOTION, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  /* Gaming
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Caps |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | CTRL |      | GUI  | ALT  |Space |Space |Lower|Raise  |Space | KANA | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_GAMING] = LAYOUT( \
      KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
      KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_LCTRL, KC_NO,  KC_LGUI,  KC_LALT, KC_SPC,  KC_SPACE, LOWER,   RAISE,  KC_SPACE, KANA,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

   /* Plank
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Caps |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | CTRL |      | GUI  | ALT  |Space |Space |Lower|Raise  |Space | KANA | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_PLANCK] = LAYOUT( \
      KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,                      KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,  KC_5, \
      KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,                      KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,  KC_T, \
      KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,                      KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G, \
      KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_LBRC, KC_RBRC, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B, \
      KC_SPACE, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, LOWER,   RAISE,  KC_LCTRL, KC_NO,   KC_LGUI, KC_LALT, LOWER, KC_SPACE \
      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | F1   | F2   | F3   |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  | F10  | F11  | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |  |   |   _  |   +  |   {  |   }  |  "   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | CAPS |      |      |      |      |      |  (   |   )  |      |      |      | Home | End  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,         KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH,       KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
      _______, _______, LALT(KC_3), LSFT(KC_QUOT), KC_QUOT, _______,                   KC_TILD,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_QUOT, \
      KC_CAPS, KC_BSLS, _______, _______,       _______, _______, KC_LPRN, KC_RPRN, _______,  _______, _______, KC_HOME, KC_END,  _______, \
      _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),


  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | BSPC |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |  \   |   -  |   =  |   [  |   ]  |  @   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | CAPS |  |   |      |      |      |      |      |      |      |      |      |PageDn|PageUp|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
      KC_F1,   KC_F2,         KC_F3,     KC_F4,     KC_F5,    KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      KC_GRV,  KC_1,          KC_2,      KC_3,      KC_4,     KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
      _______, _______,       _______,   _______,   _______,  _______,                   KC_BSLS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, LSFT(KC_QUOT), \
      KC_CAPS, KC_PIPE, _______,   _______,   _______,  _______, _______, _______, _______,  _______, _______, KC_PGDN, KC_PGUP, _______, \
      _______, _______,       _______,   _______,   _______,  _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  [_MOTION] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______,  _______, _______, \
      _______, _______, _______, _______, _______, _______,                   KC_MS_L, KC_MS_D,  KC_MS_U, KC_MS_R, _______, _______, \
      _______, KC_WH_U, KC_WH_D, KC_BTN2, KC_BTN1, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______,  QWERTY, _______, _______,  _______, _______ \
      ),

  /* Adjust (Lower + Raise)
   * ,-------------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5    |  F6  |             |  F7   |  F8   |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+--------+------|             |-------+-------+------+------+------+------|
   * |      | Reset|RGBRST|      |        |      |             |Win/Nix|Qwerty |Gaming|      |      |  Del |
   * |------+------+------+------+--------+------|             |-------+-------+------+------+------+------|
   * |      |      |      |mswhup|mswhdown| Mac  |             | ms l  |ms d   |ms u  |ms r  |      |      |
   * |------+------+------+------+--------+------+------+------+-------+-------+------+------+------+------|
   * |      |      |      |      |        |      |      |      |ms btn1|ms btn2|RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+--------+------+------+------+-------+-------+------+------+------+------|
   * |      |      |      |      |        |      |      |      |       |       | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      _______, RESET,   RGBRST,  _______, _______, _______,                   AG_TOGG, QWERTY,   GAMING,  _______, _______, KC_DEL, \
      _______, KC_WH_U, KC_WH_D, KC_BTN2, KC_BTN1, AG_NORM,                   KC_MS_L, KC_MS_D,  KC_MS_U, KC_MS_R, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      )
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case GAMING:
      persistent_default_layer_set(1UL<<_GAMING);
      return false;
      break;
    case PLANCK:
      persistent_default_layer_set(1UL<<_PLANCK);
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case MOTION:
        if (record->event.pressed) {
          layer_on(_MOTION);
        } else {
          layer_off(_MOTION);
        }
        return false;
        break;
    case MOTION_TAP:
        if (record->event.pressed) {
          persistent_default_layer_set(_MOTION);
        }
        return false;
        break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_QWERTY (1<<_QWERTY)
#define L_GAMING (1<<_GAMING)
#define L_PLANCK (1<<_PLANCK)
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_MOTION (1<<_MOTION)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_config.mode,
                   rgblight_config.hue/RGBLIGHT_HUE_STEP,
                   rgblight_config.sat/RGBLIGHT_SAT_STEP,
                   rgblight_config.val/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ",rgblight_config.mode);
      }
      matrix_write(matrix, buf);
  }
#endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
        switch (default_layer_state) {
          case L_QWERTY:
            matrix_write_P(matrix, PSTR("Qwerty"));
            break;
          case L_GAMING:
            matrix_write_P(matrix, PSTR("Gaming"));
            break;
          case L_PLANCK:
            matrix_write_P(matrix, PSTR("Planck"));
            break;
          }
          break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_MOTION:
           matrix_write_P(matrix, PSTR("Motion"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write_P(matrix, PSTR("Undef-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}, {{0x99, 0x9a}, {0xb8, 0xb9, 0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write_P(matrix, os_logo[2][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[2][1]);
  }else{
    matrix_write_P(matrix, os_logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[1][1]);
  }

  matrix_write_P(matrix, PSTR(" "));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  // Host Keyboard LED Status
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
  matrix_write_P(matrix, PSTR("\n"));
  render_rgbled_status(true, matrix);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
    render_rgbled_status(false, &matrix);
    render_layer_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
