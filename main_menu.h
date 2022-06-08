#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <errno.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include "make_menu.h"
#include "process_debug.h"

extern int ATTACHED_PROCESSES[256];

/**
 * @brief Print the debugger's main menu and handle user input.
 * 
 */
void main_menu();


/**
 * @brief Prompt user for pid and attach a trace to the specified process.
 * 
 */
void attach_to_process();

/**
 * @brief Prompt user for pid and detach the trace from specified process.
 * 
 */
void detach_from_process();

/**
 * @brief Prompt user to press any key and block untill he does so.
 * 
 */
void wait_for_key_press();


/**
 * @brief Prompt user for pid and return the pid entered.
 * 
 * @return int 
 */
int get_pid_from_user();


/**
 * @brief Get the index of the pid in ATTACHED_PROCESSES array.\
 *        Return -1 if pid not in ATTACHED_PROCESSES array.
 * 
 * @param pid 
 * @return size_t 
 */
int find_pid_cell_idx(int pid);

#define MAIN_MENU_CHOICES_LEN 4
#define EMPTY_PID_CELL_MARKER 0
#define MIN_PID	1
#define MAX_PID	99999
#define MAIN_MENU_CHOICES ((MenuChoice[])  {	\
	{"attach", "attach trace to process", &attach_to_process},	\
	{"detach", "detach trace from process", &detach_from_process},	\
	{"debug", "debug attached process", &debug_process_menu}	\
})



#endif // MAIN_MENU_H

