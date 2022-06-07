#ifndef PROCESS_DEBUG_H
#define PROCESS_DEBUG_H

#include "make_menu.h"

void debug_process_menu();
#define PROCESS_MENU_CHOICES_LEN    2
#define PROCESS_MENU_CHOICES  ((MenuChoice[])  {    \
    {"attach", "attach to process", (void(*)()) NULL},  \
	{"exit", "", (void(*)()) NULL}  \
})
#endif // PROCESS_DEBUG_H

