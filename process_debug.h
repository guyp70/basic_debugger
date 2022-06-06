#ifndef PROCESS_DEBUG_H
#define PROCESS_DEBUG_H

#include "make_menu.h"

void debug_process_menu();
size_t PROCESS_MENU_CHOICES_LEN = 2;
MenuChoice PROCESS_MENU_CHOICES[] = {
                        {"attach", "attach to process", (void(*)()) NULL},
						{"exit", "", (void(*)()) NULL}
                  };


#endif // PROCESS_DEBUG_H

