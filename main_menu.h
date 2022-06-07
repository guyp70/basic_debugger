#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <errno.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include "make_menu.h"
#include "process_debug.h"

extern int ATTACHED_PROCESSES[256];

void main_menu();
void attach_to_process();

#define MAIN_MENU_CHOICES_LEN 	4
#define MAIN_MENU_CHOICES ((MenuChoice[])  {	\
	{"attach", "attach to process", &attach_to_process},	\
	{"dettach", "dettach from process", (void(*)()) NULL},	\
	{"debug", "debug attached process", &debug_process_menu}	\
})



#endif // MAIN_MENU_H

