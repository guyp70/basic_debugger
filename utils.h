#ifndef UTILS_H
#define UTILS_H

#include <curses.h>
#include <stdio.h>


extern int ATTACHED_PROCESSES[256];



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


#define ARRAY_SIZE(a) (size_t)(sizeof(a) / sizeof(*a))


#define MIN_PID	1
#define MAX_PID	99999

#endif // UTILS_H

