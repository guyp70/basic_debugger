#include "process_debug.h"


void debug_process_menu(void *data) {
    UNUSED(data);
    make_menu(PROCESS_DEBUG_MENU_CHOICES, PROCESS_DEBUG_MENU_CHOICES_LEN);
}