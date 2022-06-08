#ifndef PROCESS_DEBUG_H
#define PROCESS_DEBUG_H

#include <sys/ptrace.h>
#include "make_menu.h"


/**
 * @brief Enter process debug menu and offer debuging operations on the specified process.
 * 
 * @param data Should be a void pointer to pid int. (i.e. int pid = 1928; debug_process_menu((void*)pid); )
 */
void debug_process_menu(void *data);

/**
 * @brief Resume the attached process run. 
 * 
 * @param data Should be a void pointer to pid int. (i.e. int pid = 1928; debug_process_menu((void*)pid); )
 */
void process_continue(void *data);


#define PROCESS_DEBUG_MENU_CHOICES_LEN    1
#define ARRAY_SIZE(a) (size_t)(sizeof(a) / sizeof(*a))
#define PROCESS_DEBUG_MENU_CHOICES(pid)  ((MenuChoice[])  {    \
    {"continue", "resume process run", process_continue, (void*) (&pid)}   \
})
#endif // PROCESS_DEBUG_H

