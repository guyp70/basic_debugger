#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <stdio.h>
#include <sys/ptrace.h>
#include "process_debug.h"

int ATTACHED_PROCESSES[256] = {0};

void main_menu();
void attach_to_process();

size_t MAIN_MENU_CHOICES_LEN = 4;
MenuChoice MAIN_MENU_CHOICES[] = {
                        {"attach", "attach to process", &attach_to_process},
						{"dettach", "dettach from process", (void(*)()) NULL},
						{"debug", "debug attached process", &debug_process_menu},
						{"exit", "", (void(*)()) NULL}
                  };



#endif // MAIN_MENU_H

