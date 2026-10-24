// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
// Rebuilt on 2026-10-24 from what was flashed on the keyboard (read over the Vial
// protocol with gnome-custom/vial-new-ui/vialctl.py) + the 29/12/25 logic from Notion.
//
// Layers: 0 base (home row mods) | 1 base without left home row mods (hold Esc toggles)
//         2 nav / F-keys (hold Space) | 3 mouse (hold Enter)

#include QMK_KEYBOARD_H

// ==================== CONFIGURABLE SECTION ====================
#define ALT_MOD         KC_RALT   // The Alt key the user holds
#define TRIGGER_KEY     KC_LBRC   // The key that cycles (the '[' key)
#define ALT_TAB_KEYCODE KC_TAB    // key that activates tab, dont need to change in most cases
// ==================== END CONFIGURABLE SECTION ====================

enum {
    TD_RALT4_CSG = 0,    // TD(0): RAlt+4 tap, Ctrl+Shift+G double-tap (not on any key now)
    TD_5_F5,             // TD(1): 5 tap, F5 hold, Alt+5 tap-hold
    TD_4_F4,             // TD(2): 4 tap, F4 hold, Alt+4 tap-hold
    TD_8_F8,             // TD(3): 8 tap, F8 hold, Alt+8 tap-hold
    TD_0_F10,            // TD(4): 0 tap, F10 hold, Alt+0 tap-hold
    TD_LCTL_ALT7,        // TD(5): LCtrl tap, Alt+7 double-tap
    TD_P_BSPC,           // TD(6): P tap, Backspace hold
    TD_1_F1,             // TD(7): 1 tap, F1 hold, Alt+1 tap-hold
    TD_2_F2,             // TD(8): 2 tap, F2 hold, Alt+2 tap-hold
    TD_3_F3,             // TD(9): 3 tap, F3 hold, Alt+3 tap-hold
    TD_6_F6,             // TD(10): 6 tap, F6 hold, Alt+6 tap-hold
    TD_7_F7,             // TD(11): 7 tap, F7 hold, Alt+7 tap-hold
    TD_9_F9,             // TD(12): 9 tap, F9 hold, Alt+9 tap-hold
    TD_EQL_PLUS,         // TD(13): = tap, + hold (layer 2, P position)
    TD_MINS_UNDS,        // TD(14): - tap, _ hold (layer 2, semicolon position)
    TD_ESC_L1,           // TD(15): ESC tap, toggle layer 1 on hold
    TD_SLSH_BSLS,        // TD(16): / tap, \ hold
    TD_Z_UNDO,           // TD(17): Z tap, CTRLZ_REP hold
};

// Ctrl+Z once, then after CTRLZ_REPEAT_DELAY keeps repeating like a held key
// (a plain LCTL(KC_Z) hold repeated after the OS's 500 ms and undid too much)
enum custom_keycodes {
    CTRLZ_REP = QK_KB_0,
};
#define CTRLZ_REPEAT_DELAY    1000
#define CTRLZ_REPEAT_INTERVAL 30

// Vial wipes the EEPROM (keymaps, tap dances) on the first boot of a new build.
// Seed the tap dances only then, so the ones edited live (vial-new-ui) survive a replug.
static bool seed_tap_dances = false;

void via_init_kb(void) {
    seed_tap_dances = !via_eeprom_is_valid();
}

void keyboard_post_init_user(void) {
    if (!seed_tap_dances) return;

    // vial_tap_dance_entry_t: { on_tap, on_hold, on_double_tap, on_tap_hold, custom_tapping_term }
    vial_tap_dance_entry_t td0  = { RALT(KC_4), KC_NO, LCTL(LSFT(KC_G)), KC_NO, 200 };
    vial_tap_dance_entry_t td1  = { KC_5, KC_F5, KC_NO, LALT(KC_5), 200 };
    vial_tap_dance_entry_t td2  = { KC_4, KC_F4, KC_NO, LALT(KC_4), 200 };
    vial_tap_dance_entry_t td3  = { KC_8, KC_F8, KC_NO, LALT(KC_8), 200 };
    vial_tap_dance_entry_t td4  = { KC_0, KC_F10, KC_NO, LALT(KC_0), 200 };
    vial_tap_dance_entry_t td5  = { KC_LCTL, KC_NO, LALT(KC_7), KC_NO, 200 };
    vial_tap_dance_entry_t td6  = { KC_P, KC_BSPC, KC_NO, KC_NO, 200 };
    vial_tap_dance_entry_t td7  = { KC_1, KC_F1, KC_NO, LALT(KC_1), 200 };
    vial_tap_dance_entry_t td8  = { KC_2, KC_F2, KC_NO, LALT(KC_2), 200 };
    vial_tap_dance_entry_t td9  = { KC_3, KC_F3, KC_NO, LALT(KC_3), 200 };
    vial_tap_dance_entry_t td10 = { KC_6, KC_F6, KC_NO, LALT(KC_6), 200 };
    vial_tap_dance_entry_t td11 = { KC_7, KC_F7, KC_NO, LALT(KC_7), 200 };
    vial_tap_dance_entry_t td12 = { KC_9, KC_F9, KC_NO, LALT(KC_9), 200 };
    vial_tap_dance_entry_t td13 = { KC_EQL, LSFT(KC_EQL), KC_NO, KC_NO, 200 };
    vial_tap_dance_entry_t td14 = { KC_MINS, LSFT(KC_MINS), KC_NO, KC_NO, 200 };
    vial_tap_dance_entry_t td15 = { KC_ESC, TG(1), KC_NO, KC_NO, 200 };
    vial_tap_dance_entry_t td16 = { KC_SLSH, KC_BSLS, KC_NO, KC_NO, 200 };
    vial_tap_dance_entry_t td17 = { KC_Z, CTRLZ_REP, KC_NO, KC_NO, 200 };

    dynamic_keymap_set_tap_dance(TD_RALT4_CSG, &td0);
    dynamic_keymap_set_tap_dance(TD_5_F5, &td1);
    dynamic_keymap_set_tap_dance(TD_4_F4, &td2);
    dynamic_keymap_set_tap_dance(TD_8_F8, &td3);
    dynamic_keymap_set_tap_dance(TD_0_F10, &td4);
    dynamic_keymap_set_tap_dance(TD_LCTL_ALT7, &td5);
    dynamic_keymap_set_tap_dance(TD_P_BSPC, &td6);
    dynamic_keymap_set_tap_dance(TD_1_F1, &td7);
    dynamic_keymap_set_tap_dance(TD_2_F2, &td8);
    dynamic_keymap_set_tap_dance(TD_3_F3, &td9);
    dynamic_keymap_set_tap_dance(TD_6_F6, &td10);
    dynamic_keymap_set_tap_dance(TD_7_F7, &td11);
    dynamic_keymap_set_tap_dance(TD_9_F9, &td12);
    dynamic_keymap_set_tap_dance(TD_EQL_PLUS, &td13);
    dynamic_keymap_set_tap_dance(TD_MINS_UNDS, &td14);
    dynamic_keymap_set_tap_dance(TD_ESC_L1, &td15);
    dynamic_keymap_set_tap_dance(TD_SLSH_BSLS, &td16);
    dynamic_keymap_set_tap_dance(TD_Z_UNDO, &td17);
}

// Tab hold-only: tap = Tab, hold = Alt+Tab window switcher
static bool tab_is_held = false;
static uint16_t tab_hold_timer = 0;
static bool alt_tab_active = false;

static bool ctrlz_is_held = false;
static bool ctrlz_repeating = false;
static uint16_t ctrlz_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    uint8_t mods = get_mods();

    if (keycode == CTRLZ_REP) {
        ctrlz_is_held = record->event.pressed;
        if (record->event.pressed) {
            tap_code16(LCTL(KC_Z));
            ctrlz_timer = timer_read();
            ctrlz_repeating = false;
        }
        return false;
    }

    if (keycode == KC_TAB) {
        if (record->event.pressed) {
            tab_is_held = true;
            tab_hold_timer = timer_read();
        } else {
            if (alt_tab_active) {
                // Was holding - release Alt
                unregister_code(KC_LALT);
                alt_tab_active = false;
            } else if (timer_elapsed(tab_hold_timer) < TAPPING_TERM) {
                // Quick tap - send Tab
                tap_code(KC_TAB);
            }
            tab_is_held = false;
        }
        return false; // We handle Tab ourselves
    }

    // E hold = Super+E was removed: it made typing lag (see Notion)

    // Intercept '[' only if Right Alt is physically held
    if (keycode == TRIGGER_KEY && record->event.pressed) {
        if (mods & MOD_BIT(ALT_MOD)) {
            // RAlt is held → send a Tab and DO NOT send '['
            tap_code(ALT_TAB_KEYCODE);
            return false; // consume '['
        }
        return true;
    }

    // J hold (Alt) + F = Alt + Tab
    // F is MT(MOD_LALT, KC_F), so we need to check for the MT keycode
    if (keycode == MT(MOD_LALT, KC_F) && record->event.pressed) {
        if (mods & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) {
            // Send Tab while keeping Alt held
            tap_code(KC_TAB);
            return false; // consume F, don't send it
        }
        return true;
    }

    // J hold (Alt) + G = Alt + Esc
    if (keycode == KC_G && record->event.pressed) {
        if (mods & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) {
            // Send Esc while keeping Alt held
            tap_code(KC_ESC);
            return false; // consume G, don't send it
        }
        return true;
    }

    return true;
}

// Activate Alt+Tab once Tab has been held for TAPPING_TERM
void matrix_scan_user(void) {
    if (tab_is_held && !alt_tab_active && timer_elapsed(tab_hold_timer) >= TAPPING_TERM) {
        register_code(KC_LALT);
        tap_code(KC_TAB);
        alt_tab_active = true;
    }

    if (ctrlz_is_held && timer_elapsed(ctrlz_timer) >= (ctrlz_repeating ? CTRLZ_REPEAT_INTERVAL : CTRLZ_REPEAT_DELAY)) {
        tap_code16(LCTL(KC_Z));
        ctrlz_timer = timer_read();
        ctrlz_repeating = true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(TD_ESC_L1),            TD(TD_1_F1),              TD(TD_2_F2),              TD(TD_3_F3),              TD(TD_4_F4),              TD(TD_5_F5),              TD(TD_6_F6),              TD(TD_7_F7),              TD(TD_8_F8),              TD(TD_9_F9),              TD(TD_0_F10),             KC_BSPC,
        KC_TAB,                   KC_Q,                     KC_W,                     KC_E,                     KC_R,                     KC_T,                     KC_Y,                     KC_U,                     KC_I,                     KC_O,                     TD(TD_P_BSPC),            KC_LBRC,
        KC_LSFT,                  MT(MOD_LCTL, KC_A),       MT(MOD_LSFT, KC_S),       MT(MOD_LGUI, KC_D),       MT(MOD_LALT, KC_F),       KC_G,                     KC_H,                     MT(MOD_LALT, KC_J),       MT(MOD_RGUI, KC_K),       MT(MOD_RSFT, KC_L),       MT(MOD_LCTL, KC_SCLN),    KC_ENT,
        TD(TD_LCTL_ALT7),         TD(TD_Z_UNDO),            KC_X,                     KC_C,                     KC_V,                     KC_B,                     KC_N,                     KC_M,                     KC_COMM,                  KC_DOT,                   TD(TD_SLSH_BSLS),         TD(TD_LCTL_ALT7),
                                                                                      MT(MOD_LALT, KC_LGUI),    LT(2, KC_SPC),            LT(3, KC_ENT),            LT(3, KC_ENT),            LT(2, KC_SPC),            MT(MOD_LALT, KC_LGUI)
    ),
    [1] = LAYOUT(
        TD(TD_ESC_L1),            TD(TD_1_F1),              TD(TD_2_F2),              TD(TD_3_F3),              TD(TD_4_F4),              TD(TD_5_F5),              TD(TD_6_F6),              TD(TD_7_F7),              TD(TD_8_F8),              TD(TD_9_F9),              TD(TD_0_F10),             KC_BSPC,
        KC_TAB,                   KC_Q,                     KC_W,                     KC_E,                     KC_R,                     KC_T,                     KC_Y,                     KC_U,                     KC_I,                     KC_O,                     TD(TD_P_BSPC),            KC_LBRC,
        KC_LSFT,                  KC_A,                     KC_S,                     KC_D,                     KC_F,                     KC_G,                     KC_H,                     MT(MOD_LALT, KC_J),       MT(MOD_RGUI, KC_K),       MT(MOD_RSFT, KC_L),       MT(MOD_LCTL, KC_SCLN),    KC_ENT,
        TD(TD_LCTL_ALT7),         KC_Z,                     KC_X,                     KC_C,                     KC_V,                     KC_B,                     KC_N,                     KC_M,                     KC_COMM,                  KC_DOT,                   KC_SLSH,                  TD(TD_LCTL_ALT7),
                                                                                      MT(MOD_LALT, KC_LGUI),    LT(2, KC_SPC),            LT(3, KC_ENT),            LT(3, KC_ENT),            LT(2, KC_SPC),            MT(MOD_LALT, KC_LGUI)
    ),
    [2] = LAYOUT(
        KC_PSCR,                  KC_F1,                    KC_F2,                    KC_F3,                    KC_F4,                    KC_F5,                    KC_F6,                    KC_F7,                    KC_F8,                    KC_F9,                    KC_F10,                   KC_DEL,
        KC_GRV,                   KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_PGUP,                  KC_UP,                    KC_PGDN,                  TD(TD_EQL_PLUS),          KC_RBRC,
        KC_RGHT,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_LEFT,                  KC_DOWN,                  KC_RGHT,                  TD(TD_MINS_UNDS),         KC_QUOT,
        KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_PGDN,                  KC_HOME,                  KC_END,                   LSFT(KC_BSLS),            KC_BSLS,
                                                                                      KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS
    ),
    [3] = LAYOUT(
        KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,
        KC_TRNS,                  KC_Q,                     KC_W,                     KC_E,                     KC_TRNS,                  KC_R,                     KC_TRNS,                  KC_TRNS,                  KC_MS_U,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,
        KC_TRNS,                  KC_A,                     KC_S,                     KC_D,                     KC_F,                     KC_TRNS,                  KC_TRNS,                  KC_MS_L,                  KC_MS_D,                  KC_MS_R,                  KC_TRNS,                  KC_TRNS,
        KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_TRNS,
                                                                                      KC_TRNS,                  KC_TRNS,                  KC_TRNS,                  KC_BTN1,                  KC_BTN2,                  KC_BTN3
    )
};
