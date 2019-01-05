#include "ckeys.h"
#include "action_layer.h"

#define _BASE           0  // base layer
#define _LAYERS         1  // layer of all layers
#define _MUSIC          2  // music mode
#define _MUSIC_4_LIFE   3  // music mode until unplugged
#define _MOUSE          4  // mousekeys
#define _TERMINAL       5  // terminal
#define _ADMIN          6  // admin duties

#define _____ KC_TRNS

enum custom_keycodes {
  TERM_ABOUT = SAFE_RANGE,
  TERM_PRINT,
  TERM_FLUSH,
  TERM_HELP,
  CKEYS_ABOUT,
};

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE (numpad)
   * ,-----------------------.
   * |  7  |  8  |  9  |  /  | <-- Hold for LAYERS
   * |-----+-----+-----+-----|
   * |  4  |  5  |  6  |  *  |
   * |-----+-----+-----+-----|
   * |  1  |  2  |  3  |  -  |
   * |-----+-----+-----+-----|
   * |  0  |  .  |  =  |  +  |
   * `---------------------- '
   */
  [_BASE] = KEYMAP(
    KC_KP_7, KC_KP_8, KC_KP_9, LT(MO(_LAYERS), KC_PSLS), \
    KC_KP_4, KC_KP_5, KC_KP_6, KC_PAST,                  \
    KC_KP_1, KC_KP_2, KC_KP_3, KC_PMNS,                  \
    KC_KP_0, KC_KP_DOT, KC_KP_EQUAL, KC_PPLS \
  ),
    /* LAYERS
   * ,---------------------------.
   * |  MUSIC  |     |     |  X  |
   * |---------+-----+-----+-----|
   * |  MOUSE  |     |     |     |
   * |---------+-----+-----+-----|
   * |TERMINAL |     |     |     |
   * |---------+-----+-----+-----|
   * |  ADMIN  |     |     |     |
   * `---------------------------'
   */
  [_LAYERS] = KEYMAP(
    TG(_MUSIC),    _____, _____, _____, \
    TG(_MOUSE),    _____, _____, _____, \
    TG(_TERMINAL), _____, _____, _____, \
    TG(_ADMIN),    _____, _____, _____ \
  ),
    /* MUSIC
   * ,-----------------------.
   * |  X  |     |     |  X  |
   * |-----+-----+-----+-----|
   * |     |     |     |4EVER|
   * |-----+-----+-----+-----|
   * | OFF |     |     |     |
   * |-----+-----+-----+-----|
   * |  ON |     |     |MODES|
   * `---------------------- '
   */
  // TODO: Make this music layer the one to jump to other music layers (different octaves)
  [_MUSIC] = KEYMAP(
    _____,  _____, _____, _____,             \
    _____,  _____, _____, TG(_MUSIC_4_LIFE), \
    MU_OFF, _____, _____, _____,             \
    MU_ON,  _____, _____, MU_MOD \
  ),
    /* MUSIC_4_LIFE
   * ,-----------------------.
   * |  ♫  |  ♫  |  ♫  |  ♫  |
   * |-----+-----+-----+-----|
   * |  ♫  |  ♫  |  ♫  |  ♫  |
   * |-----+-----+-----+-----|
   * |  ♫  |  ♫  |  ♫  |  ♫  |
   * |-----+-----+-----+-----|
   * |  ♫  |  ♫  |  ♫  |  ♫  |
   * `---------------------- '
   */
  [_MUSIC_4_LIFE] = KEYMAP(
    KC_M, KC_M, KC_M, KC_M, \
    KC_M, KC_M, KC_M, KC_M, \
    KC_M, KC_M, KC_M, KC_M, \
    KC_M, KC_M, KC_M, KC_M \
  ),
    /* MOUSE
   * ,-------------------------------------------------.
   * |  BUTTON 5 |           | SCROLL UP  |     X      |
   * |-----------+-----------+------------+------------|
   * |     X     |LEFT CLICK |     UP     |RIGHT CLICK |
   * |-----------+-----------+------------+------------|
   * |  BUTTON 4 |   LEFT    |    DOWN    |   RIGHT    |
   * |-----------+-----------+------------+------=-----|
   * |  BUTTON 3 |SCROLL LEFT|SCROLL DOWN |SCROLL RIGHT|
   * `-------------------------------------------------'
   */
  [_MOUSE] = KEYMAP(
    KC_MS_BTN5, _____,         KC_MS_WH_UP,   _____,         \
    _____,      KC_MS_BTN1,    KC_MS_UP,      KC_MS_BTN2,    \
    KC_MS_BTN4, KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_RIGHT,   \
    KC_MS_BTN3, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_RIGHT \
  ),
    /* TERMINAL
   * ,---------------------------------------.
   * |            |ABOUT|          |    X    |
   * |------------+-----+----------+---------|
   * |TERMINAL OFF|PRINT|          |         |
   * |------------+-----+----------+---------|
   * |     X      |FLUSH|          |         |
   * |------------+-----+----------+---------|
   * |TERMINAL ON |HELP |          |         |
   * `--------=======------------------------'
   */
  [_TERMINAL] = KEYMAP(
    _____,    TERM_ABOUT, _____, _____, \
    TERM_OFF, TERM_PRINT, _____, _____, \
    _____,    TERM_FLUSH, _____, _____, \
    TERM_ON,  TERM_HELP , _____, _____ \
  ),
    /* ADMIN
   * ,-----------------------------------------.
   * |   RESET    |     |           |    X     |
   * |------------+-----+-----------+----------|
   * |ABOUT CKEYS |     |           |          |
   * |------------+-----+-----------+----------|
   * |            |     |CLICKY UP  |CLICKY OFF|
   * |------------+-----+-----------+----------|
   * |     X      |     |CLICKY DOWN|CLICKY ON |
   * `-----------------------------------------'
   */
  [_ADMIN] = KEYMAP(
    RESET,       _____, _____, _____,  \
    CKEYS_ABOUT, _____, _____, _____,  \
    _____,       _____, _____, CK_OFF, \
    _____,       _____, _____, CK_ON \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TERM_ABOUT:
      if (record->event.pressed) {
        // when keycode TERM_ABOUT is pressed
        SEND_STRING("about"SS_TAP(X_ENTER));
      } else {
        // when keycode TERM_ABOUT is released
      }
      break;
    case TERM_PRINT:
      if (record->event.pressed) {
        SEND_STRING("print"SS_TAP(X_ENTER));
      } else { }
      break;
    case TERM_FLUSH:
      if (record->event.pressed) {
        SEND_STRING("flush"SS_TAP(X_ENTER));
      } else { }
      break;
    case TERM_HELP:
      if (record->event.pressed) {
        SEND_STRING("help"SS_TAP(X_ENTER));
      } else { }
      break;
    case CKEYS_ABOUT:
      if (record->event.pressed) {
        SEND_STRING("https://cKeys.org"SS_TAP(X_ENTER)"Making people smile one keyboard at a time."SS_TAP(X_ENTER)"cKeys is a volunteer run 501(c)(3) nonprofit."SS_TAP(X_ENTER));
      } else { }
      break;
  }
  return true;
};
