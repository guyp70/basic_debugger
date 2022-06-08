#include "main_menu.h"


void main_menu(){
    make_menu(MAIN_MENU_CHOICES, MAIN_MENU_CHOICES_LEN);
}


void wait_for_key_press() {
    printw("Press any key to continue...");
    getch();
}


int find_pid_cell_idx(int pid) {
    size_t i;
    for(i=0; (ATTACHED_PROCESSES[i] != pid) && (i < ARRAY_SIZE(ATTACHED_PROCESSES)); ++i);
    if (i < ARRAY_SIZE(ATTACHED_PROCESSES)) {
        return i;
    }
    return -1;
}


int get_pid_from_user(){
    int pid;
    printw("Please enter pid to attach to: ");
    while ((scanw("%d", &pid) != 1) && (MIN_PID <= pid && pid <= MAX_PID)) {
        printw("Bad input format. Please enter a valid pid: ");
    }
    return pid;
}


void detach_from_process(){
    int pid, pid_cell_idx;
    pid = get_pid_from_user();
    pid_cell_idx = find_pid_cell_idx(pid);
    if (pid_cell_idx == -1) {
        printw("Process %d has no trace attached. (at least not one with this process as its tracer)\n", pid);
        wait_for_key_press();
        return;
    }
    // detach trace from process
    if (ptrace(PTRACE_DETACH, pid, 0, 0) == -1) {
        perror("Failed to detach from process");
    } else {
        ATTACHED_PROCESSES[pid_cell_idx] = EMPTY_PID_CELL_MARKER;
        printw("Process trace detached.\n");
    }
    wait_for_key_press();    
}


void attach_to_process(){
    size_t i, empty_cell_idx;
    int pid;

    pid = get_pid_from_user();
    if (find_pid_cell_idx(pid) != -1) {
        printw("Process %d was already attached a trace.", pid);
        wait_for_key_press();
        return;
    }
    for(i=0; (ATTACHED_PROCESSES[i] != EMPTY_PID_CELL_MARKER) && (i < ARRAY_SIZE(ATTACHED_PROCESSES)); ++i);
    if ( i >= ARRAY_SIZE(ATTACHED_PROCESSES)) {
        printw("Maximum number of attached processes reached. Please detach from some and try again.");
        wait_for_key_press();
        return;
    } 
    empty_cell_idx = i;
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


