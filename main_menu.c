#include "main_menu.h"


void main_menu(){
    make_menu(MAIN_MENU_CHOICES, MAIN_MENU_CHOICES_LEN);
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
    if (get_num_of_attached_processes() >= ARRAY_SIZE(ATTACHED_PROCESSES)) {
        printw("Maximum number of attached processes reached. Please detach from some and try again.");
        wait_for_key_press();
        return;
    } 
    for(i=0; (ATTACHED_PROCESSES[i] != EMPTY_PID_CELL_MARKER) && (i < ARRAY_SIZE(ATTACHED_PROCESSES)); ++i);
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


void attached_processes_menu() {
    size_t i, menu_idx = 0, num_of_attached_procs;
    MenuChoice *procs_menu_choices;
    num_of_attached_procs = get_num_of_attached_processes();

    procs_menu_choices = (MenuChoice*) (calloc(num_of_attached_procs, sizeof(MenuChoice)));
    if (NULL == procs_menu_choices) {
        //TODO: ADD ERROR HANDLING
    }

    menu_idx = 0;
    for (i=0; i < ARRAY_SIZE(ATTACHED_PROCESSES); i++) {
        if (EMPTY_PID_CELL_MARKER != ATTACHED_PROCESSES[i]){
            sprintf(procs_menu_choices[menu_idx].name, "%d", ATTACHED_PROCESSES[i]);
            if (-1 == get_process_cmd_by_pid(ATTACHED_PROCESSES[i], procs_menu_choices[menu_idx].description)) {
                //TODO: ADD ERROR HANDLING
            }
            procs_menu_choices[menu_idx].action_func = &debug_process_menu;

        }
    }
    make_menu(procs_menu_choices, num_of_attached_procs);
    free(procs_menu_choices);
}