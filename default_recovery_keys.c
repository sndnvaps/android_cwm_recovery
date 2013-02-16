#include <linux/input.h>

#include "recovery_ui.h"
#include "common.h"
#include "extendedcommands.h"


int device_toggle_display(volatile char* key_pressed, int key_code) {
    int alt = key_pressed[KEY_LEFTALT] || key_pressed[KEY_RIGHTALT];
    if (alt && key_code == KEY_L)
        return 1;
    // allow toggling of the display if the correct key is pressed, and the display toggle is allowed or the display is currently off
    if (ui_get_showing_back_button()) {
        return 0;
        //return get_allow_toggle_display() && (key_code == KEY_HOME || key_code == KEY_MENU || key_code == KEY_END);
    }
    return get_allow_toggle_display() && (key_code == KEY_HOME || key_code == KEY_MENU || key_code == KEY_POWER || key_code == KEY_END);
}

int device_handle_key(int key_code, int visible) {
    if (visible) {
        switch (key_code) {
            case KEY_VOLUMEDOWN:
                return HIGHLIGHT_DOWN;

            case KEY_VOLUMEUP:
                return HIGHLIGHT_UP;

#if defined(TARGET_DEVICE_SC02C) || defined(TARGET_DEVICE_SC05D) || defined(TARGET_DEVICE_SC03D) ||\
        defined(TARGET_DEVICE_SO03C) || defined(TARGET_DEVICE_ISW13HT) || defined(TARGET_DEVICE_SC02E)
            case KEY_HOME:
            case KEY_POWER:
#endif
#if defined(TARGET_DEVICE_SC06D)
            case KEY_HOMEPAGE:
            case KEY_POWER:
#endif
                if (ui_get_showing_back_button()) {
                    return SELECT_ITEM;
                }
                if (!get_allow_toggle_display() && !ui_root_menu) {
                    return GO_BACK;
                }
                break;

            case KEY_BACK:
                if (!ui_root_menu) {
                    return GO_BACK;
                }
        }
    }

    return NO_ACTION;
}
