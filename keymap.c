#include QMK_KEYBOARD_H

enum my_layers {
  BASE_LAYER,
  SHIFT_LAYER,
  SPACE_LAYER,
  ENTER_LAYER,
  ESCAPE_LAYER,
  LEFT_LAYER,
  RIGHT_LAYER
};

enum my_keycodes {
    M_ESCQ = SAFE_RANGE,
    M_ESCW,
    M_ALTT,
    M_NDESK,
    M_PDESK,
    M_XTAB,
    M_APP1,
    M_APP2,
    M_APP3,
    M_APP4,
    M_APP5,
    M_LIKE,
    M_1PASS,
    M_NTRM,
    M_EMOJI,
    M_ISCB,
    M_ISWIN
};

// Tap-hold tap dances require custom types and functions.

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_DOUBLE_TAP,
  TD_HOLD
} td_state_t;

typedef struct {
  td_state_t state;
} td_tap_t;

static td_tap_t td_shift = {
  .state = TD_NONE
};

static td_tap_t td_space = {
  .state = TD_NONE
};

static td_tap_t td_enter = {
  .state = TD_NONE
};

static td_tap_t td_escape = {
  .state = TD_NONE
};

td_state_t td_get_state(tap_dance_state_t *state);

void shift_finished(tap_dance_state_t *state, void *user_data);
void shift_reset(tap_dance_state_t *state, void *user_data);
void space_finished(tap_dance_state_t *state, void *user_data);
void space_reset(tap_dance_state_t *state, void *user_data);
void enter_finished(tap_dance_state_t *state, void *user_data);
void enter_reset(tap_dance_state_t *state, void *user_data);
void escape_finished(tap_dance_state_t *state, void *user_data);
void escape_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance definitions

enum {
  TD_SHIFT,
  TD_SPACE,
  TD_ENTER,
  TD_ESCAPE
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_finished, shift_reset),
    [TD_SPACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, space_finished, space_reset),
    [TD_ENTER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, enter_finished, enter_reset),
    [TD_ESCAPE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, escape_finished, escape_reset)
};

// Stores state of M_ALTT macro - true if we are currently tabbing between
// windows.
static bool m_altt_pressed = false;

// Toggle for keys that affect the the desktop - value can be changed in
// function layer
static bool m_is_chromebook = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE_LAYER] = LAYOUT_split_3x5_2(
    KC_Q,          LCTL_T(KC_W),  LALT_T(KC_F),  LGUI_T(KC_P),  KC_B,  KC_J,  LGUI_T(KC_L),  LALT_T(KC_U),  LCTL_T(KC_Y),  KC_BSPC,
    KC_A,          KC_R,          KC_S,          KC_T,          KC_G,  KC_M,  KC_N,          KC_E,          KC_I,          KC_O,
    OSL(LEFT_LAYER),   KC_X,          KC_C,          KC_D,          KC_V,  KC_K,  KC_H,          KC_COMM,       KC_DOT,        OSL(RIGHT_LAYER),
    TD(TD_SHIFT),  TD(TD_SPACE),  TD(TD_ENTER),  TD(TD_ESCAPE)
  ),

  [SHIFT_LAYER] = LAYOUT_split_3x5_2(
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_MS_U,  KC_NO,    KC_DEL,
    KC_NO,    KC_ACL0,  KC_ACL1,  KC_ACL2,  KC_NO,  KC_WH_U,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_WH_D,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_TRNS,  KC_TRNS,  KC_BTN1,  KC_BTN2
  ),

  [SPACE_LAYER] = LAYOUT_split_3x5_2(
    KC_ESC,   KC_PSCR,  M_ISCB,   M_ISWIN,  KC_INS,   M_XTAB,   M_PDESK,  LCTL(KC_TAB),  M_ALTT,   M_NDESK,
    KC_TAB,   KC_MNXT,  KC_MPLY,  KC_VOLU,  KC_BRIU,  KC_NO,    KC_LEFT,  KC_DOWN,       KC_UP,    KC_RGHT,
    KC_CAPS,  KC_MPRV,  KC_MUTE,  KC_VOLD,  KC_BRID,  KC_NO,    KC_HOME,  KC_PGDN,       KC_PGUP,  KC_END,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [ENTER_LAYER] = LAYOUT_split_3x5_2(
    KC_PAST,  KC_1,     KC_2,     KC_3,    KC_PPLS,  KC_NO,  KC_F1,   KC_F2,    KC_F3,  KC_NO,
    KC_PSLS,  KC_4,     KC_5,     KC_6,    KC_PMNS,  KC_NO,  KC_F4,   KC_F5,    KC_F6,  KC_NO,
    KC_0,     KC_7,     KC_8,     KC_9,    KC_DOT,   KC_NO,  KC_F7,   KC_F8,    KC_F9,  KC_F10,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [ESCAPE_LAYER] = LAYOUT_split_3x5_2(
    M_ESCQ,   M_ESCW,      M_NTRM,      M_1PASS,           M_LIKE,      KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_NO,
    KC_NO,    M_APP1,      M_APP2,      M_APP3,            M_APP4,      KC_NO,  KC_NO,  M_EMOJI,  KC_NO,  KC_NO,
    KC_NO,    LCTL(KC_X),  LCTL(KC_C),  LSFT(LCTL(KC_C)),  LCTL(KC_V),  KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_NO,
    KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS
  ),

  [LEFT_LAYER] = LAYOUT_split_3x5_2(
    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_CIRC,  KC_AMPR,        KC_ASTR,        KC_UNDS,  KC_PLUS,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_COLN,  LSFT(KC_QUOT),  LSFT(KC_BSLS),  KC_MINS,  KC_EQL,
    KC_Z,     KC_NO,    KC_NO,    KC_NO,   KC_NO,  KC_SCLN,  KC_QUOT,        KC_BSLS,        KC_GRV,   KC_QUES,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [RIGHT_LAYER] = LAYOUT_split_3x5_2(
    KC_EXLM,  LSFT(KC_2),     LSFT(KC_3),  KC_DLR,   KC_PERC,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_ESC,   LSFT(KC_NUBS),  KC_LBRC,     KC_LCBR,  KC_LPRN,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    CW_TOGG,  KC_NUBS,        KC_RBRC,     KC_RCBR,  KC_RPRN,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_SLSH,
    KC_TRNS,  KC_TRNS,        KC_TRNS,     KC_TRNS
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Stop pressing the alt key once a key other than the alt-tab macro has been
  // pressed.
  if (keycode != M_ALTT && m_altt_pressed) {
    unregister_code(KC_LALT);
    m_altt_pressed = false;
  }

  // Ensure shift is not pressed when the left and right layers is active.
  if (IS_LAYER_ON(LEFT_LAYER) || IS_LAYER_ON(RIGHT_LAYER)) {
    switch (keycode) {
      case OSL(LEFT_LAYER):
      case OSL(RIGHT_LAYER):
      case KC_Z:
      case KC_SLSH:
        break;
      default:
        del_mods(MOD_MASK_SHIFT);
        del_oneshot_mods(MOD_MASK_SHIFT);
    }
  }

  switch (keycode) {
    case M_ESCQ:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESC)":q!"SS_TAP(X_ENT));
      } else {
        layer_move(BASE_LAYER);
      }
      break;
    case M_ESCW:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESC)":wq"SS_TAP(X_ENT));
      } else {
        layer_move(BASE_LAYER);
      }
      break;
    case M_ALTT:
      if (record->event.pressed) {
        if (!m_altt_pressed) {
          register_code(KC_LALT);
          m_altt_pressed = true;
        }
        tap_code(KC_TAB);
      }
      break;
    case M_APP1:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP2:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_2));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_2));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP3:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_3));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_3));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP4:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_4));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_4));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP5:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_5));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_5));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_LIKE:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_5)SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_5));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
        SEND_STRING(SS_DELAY(100));
        SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LALT));
        SEND_STRING(SS_TAP(X_B));
        SEND_STRING(SS_UP(X_LALT)SS_UP(X_LSFT));
      }
      break;
    case M_1PASS:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_1)SS_UP(X_LALT));
          SEND_STRING(SS_DELAY(100));
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_X));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_SPC));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_NDESK:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_RBRC));
          SEND_STRING(SS_UP(X_LGUI));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_RGHT));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LCTL));
        }
      }
      break;
    case M_PDESK:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_LBRC));
          SEND_STRING(SS_UP(X_LGUI));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_LEFT));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LCTL));
        }
      }
      break;
    case M_XTAB:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_W)SS_UP(X_LCTL));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_F4)SS_UP(X_LCTL));
        }
      }
      break;
    case M_NTRM:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_T)SS_UP(X_LCTL));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_EMOJI:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_SPC));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LSFT));
        } else {
          SEND_STRING(SS_DOWN(X_LGUI)SS_TAP(X_SCLN)SS_UP(X_LGUI));
        }
      }
      break;
    case M_ISCB:
      if (record->event.pressed) {
        m_is_chromebook = true;
      }
      break;
    case M_ISWIN:
      if (record->event.pressed) {
        m_is_chromebook = false;
      }
      break;
  }

  return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Set the tapping term for the homerow mods.
    case LCTL_T(KC_W):
    case LALT_T(KC_F):
    case LGUI_T(KC_P):
    case LGUI_T(KC_L):
    case LALT_T(KC_U):
    case LCTL_T(KC_Y):
      return TAPPING_TERM_MODS;
    // Set the tapping term for tap dance keys.
    case TD(TD_SHIFT):
    case TD(TD_SPACE):
    case TD(TD_ENTER):
    case TD(TD_ESCAPE):
      return TAPPING_TERM_TD_THUMB;
    default:
      return TAPPING_TERM;
  }
}

td_state_t td_get_state(tap_dance_state_t *state) {
  if (state->count == 1) {
    // If the keypress has been interrupted by another keypress or is no longer
    // held down by the end of the tap time, then we know it was just a single
    // tap.
    if (state->interrupted || !state->pressed)
      return TD_SINGLE_TAP;
    else
      // If it is still held at the end of the tap time, then it is a hold.
      return TD_HOLD;
  } else if (state->count > 1) {
    // In the case where there has been more than one tap in the tap time, we
    // have to make a judgement call. If the key is still held down we will
    // assume it was a flutter and call it a hold.
    if (state->pressed)
      return TD_HOLD;
    // If the keypress has finished or has been interrupted then we will assume
    // that there was some actual fast typing going on and issue two taps, which
    // will be the most common scenario.
    if (state->interrupted || !state->pressed)
      return TD_DOUBLE_TAP;
  }
  return TD_UNKNOWN;
}

void shift_finished(tap_dance_state_t *state, void *user_data) {
    td_shift.state = td_get_state(state);
    switch (td_shift.state) {
        case TD_SINGLE_TAP:
          set_oneshot_mods(MOD_LSFT);
          break;
        case TD_DOUBLE_TAP:
          caps_word_on();
          break;
        case TD_HOLD:
          layer_on(SHIFT_LAYER);
          break;
        default:
          break;
    }
}

void shift_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_shift.state) {
        case TD_SINGLE_TAP:
          // Do nothing - the oneshot mod will switch itself off after another
          // key has been pressed.
          break;
        case TD_DOUBLE_TAP:
          // Do nothing - caps word will finish itself.
          break;
        case TD_HOLD:
          layer_off(SHIFT_LAYER);
        default:
          break;
    }
    td_shift.state = TD_NONE;
}

void space_finished(tap_dance_state_t *state, void *user_data) {
    td_space.state = td_get_state(state);
    switch (td_space.state) {
        case TD_SINGLE_TAP:
          register_code(KC_SPC);
          break;
        case TD_DOUBLE_TAP:
          register_code(KC_TAB);
          break;
        case TD_HOLD:
          layer_on(SPACE_LAYER);
          break;
        default:
          break;
    }
}

void space_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_space.state) {
        case TD_SINGLE_TAP:
          unregister_code(KC_SPC);
          break;
        case TD_DOUBLE_TAP:
          unregister_code(KC_TAB);
          break;
        case TD_HOLD:
          layer_off(SPACE_LAYER);
        default:
          break;
    }
    td_space.state = TD_NONE;
}

void enter_finished(tap_dance_state_t *state, void *user_data) {
    td_enter.state = td_get_state(state);
    switch (td_enter.state) {
        case TD_DOUBLE_TAP:
          register_code(KC_ENT);
          unregister_code(KC_ENT);
        case TD_SINGLE_TAP:
          register_code(KC_ENT);
          break;
        case TD_HOLD:
          layer_on(ENTER_LAYER);
          break;
        default:
          break;
    }
}

void enter_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_enter.state) {
        case TD_DOUBLE_TAP:
        case TD_SINGLE_TAP:
          unregister_code(KC_ENT);
          break;
        case TD_HOLD:
          layer_off(ENTER_LAYER);
        default:
          break;
    }
    td_enter.state = TD_NONE;
}

void escape_finished(tap_dance_state_t *state, void *user_data) {
    td_escape.state = td_get_state(state);
    switch (td_escape.state) {
        case TD_DOUBLE_TAP:
          register_code(KC_ESC);
          unregister_code(KC_ESC);
        case TD_SINGLE_TAP:
          register_code(KC_ESC);
          break;
        case TD_HOLD:
          layer_on(ESCAPE_LAYER);
          break;
        default:
          break;
    }
}

void escape_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_escape.state) {
        case TD_DOUBLE_TAP:
        case TD_SINGLE_TAP:
          unregister_code(KC_ESC);
          break;
        case TD_HOLD:
          layer_off(ESCAPE_LAYER);
        default:
          break;
    }
    td_escape.state = TD_NONE;
}
