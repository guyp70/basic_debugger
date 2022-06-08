#ifndef PROCESS_DEBUG_H
#define PROCESS_DEBUG_H

#include "make_menu.h"


/**
 * @brief Enter process debug menu and offer debuging operations on the specified process.
 *        Data should be a void pointer to pid int. (i.e. int pid = 1928; debug_process_menu((void*)pid);)
 * 
 * @param data 
 */
void debug_process_menu(void *data);


#define PROCESS_DEBUG_MENU_CHOICES_LEN    2
#define PROCESS_DEBUG_MENU_CHOICES  ((MenuChoice[])  {    \
    {"continue", "attach to process", (void(*)(void*)) NULL, (void*) NULL}   \
})
#endif // PROCESS_DEBUG_H

