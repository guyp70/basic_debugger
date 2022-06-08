#include "process_debug.h"


void debug_process_menu(void *data) {
    int pid = *((int*) data);
    
    make_menu(PROCESS_DEBUG_MENU_CHOICES(pid), PROCESS_DEBUG_MENU_CHOICES_LEN);
}


void process_continue(void *data){
    int pid = *((int*) data);
    if (ptrace(PTRACE_CONT, pid, 0, 0) == -1) {
        perror("Failed to continue process run.");
    } else {
        printw("Process run resumed.\n");
    }
    wait_for_key_press();
}