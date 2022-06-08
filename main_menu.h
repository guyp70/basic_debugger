#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include "make_menu.h"
#include "utils.h"
#include "process_debug.h"



/**
 * @brief Print the debugger's main menu and handle user input.
 * 
 */
void main_menu();


/**
 * @brief Prompt user for pid and attach a trace to the specified process. (data is ignored)
 * 
 */
void attach_to_process(void *data);

/**
 * @brief Prompt user for pid and detach the trace from specified process. (data is ignored)
 * 
 */
void detach_from_process(void *data);


/**
 * @brief Enter list of attached processes menu and handle user input. (data is ignored)
 * 
 */
void attached_processes_menu(void *data);


#define EMPTY_PID_CELL_MARKER 0


#define MAIN_MENU_CHOICES_LEN 4
#define MAIN_MENU_CHOICES ((MenuChoice[])  {	\
	{"attach", "attach trace to process", &attach_to_process, (void*) NULL},	\
	{"detach", "detach trace from process", &detach_from_process, (void*) NULL},	\
	{"debug", "debug attached process", &attached_processes_menu, (void*) NULL}	\
})

#endif // MAIN_MENU_H

