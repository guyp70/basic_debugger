#ifndef UTILS_H
#define UTILS_H

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>


#define EMPTY_PID_CELL_MARKER 0
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


/**
 * @brief Get the num of processes this process is currently tracing.
 * 
 * @return size_t 
 */
size_t get_num_of_attached_processes();

/**
 * @brief reutrn the pid's process' command line.
 * 
 * @param pid 
 * @return int 
 * 
 * @param buf buffer to copy the process cmd into. Should be at least sizeof(char) * MAX_PROCESS_CMD_LEN bytes long. 
 * @return char* 
 */
int get_process_cmd_by_pid(const int pid, char* buf);


#define ARRAY_SIZE(a) (size_t)(sizeof(a) / sizeof(*a))


#define MIN_PID	1
#define MAX_PID	99999
#define MAX_PID_LEN 5
#define MAX_PROCESS_CMD_LEN 1024 // must be larger than (len of "/proc//cmdline" + MAX_PID_LEN)

#endif // UTILS_H

