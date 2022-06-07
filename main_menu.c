#include "main_menu.h"


void main_menu(){
    make_menu(MAIN_MENU_CHOICES, MAIN_MENU_CHOICES_LEN);
}


void wait_for_key_press() {
    printw("Press any key to continue...");
    getch();
}


void attach_to_process(){
    size_t i, empty_cell_idx;
    int pid;
    printw("Please enter pid to attach to: ");
    while ((scanw("%d", &pid) != 1) && (MIN_PID <= pid && pid <= MAX_PID)) {
        printw("Bad input format. Please enter a valid pid: ");
    }
    for(i=0; (ATTACHED_PROCESSES[i] != EMPTY_PID_CELL_MARKER) && (i < ARRAY_SIZE(ATTACHED_PROCESSES)); ++i);
    if ( i >= ARRAY_SIZE(ATTACHED_PROCESSES)) {
        printw("Maximum attached processes reached. Please detach from some and try again.");
        wait_for_key_press();
        return;
    } 
    empty_cell_idx = i;
    for(i=0; (ATTACHED_PROCESSES[i] != pid) && (i < ARRAY_SIZE(ATTACHED_PROCESSES)); ++i);
    if (i < ARRAY_SIZE(ATTACHED_PROCESSES)) {
        printw("Process %d was already attached a trace.", pid);
        wait_for_key_press();
        return;
    }
    // attach trace to process
    if (ptrace(PTRACE_ATTACH, pid, 0, 0) == -1) {
        perror("Failed to attach to process");
    } else {
        // waitpid(pid);
        ATTACHED_PROCESSES[empty_cell_idx] = pid;
        printw("Process trace attached.\n");
    }
    wait_for_key_press();
}


