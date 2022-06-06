#include "main_menu.h"


void main_menu(){
    make_menu(MAIN_MENU_CHOICES, MAIN_MENU_CHOICES_LEN);
}


void attach_to_process(){
    int i = -1;
    int pid;
    printw("Please enter pid to attach to: ");
    while ((scanw("%d", &pid) != 1) && (1 <= pid && pid <= 99999)) {
        printw("Bad input format. Please enter a valid pid: ");
    }
    while (ATTACHED_PROCESSES[++i] != 0);
    if ((unsigned long) i >= ARRAY_SIZE(ATTACHED_PROCESSES)) {
        printw("Maximum attached processes reached. Please detach from some and try again.");
        return;
    } 
    // attach
    ptrace(PTRACE_ATTACH, pid, 0, 0);
    // waitpid(pid);
    ATTACHED_PROCESSES[i] = pid;
    printw("Process trace attached.");

}

