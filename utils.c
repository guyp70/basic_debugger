#include "utils.h"


void wait_for_key_press() {
    printw("Press any key to continue...");
    getch();
}


int get_pid_from_user(){
    int pid;
    printw("Please enter pid to attach to: ");
    while ((scanw("%d", &pid) != 1) && (MIN_PID <= pid && pid <= MAX_PID)) {
        printw("Bad input format. Please enter a valid pid: ");
    }
    return pid;
}



int find_pid_cell_idx(int pid) {
    size_t i;
    for(i=0; (ATTACHED_PROCESSES[i] != pid) && (i < ARRAY_SIZE(ATTACHED_PROCESSES)); ++i);
    if (i < ARRAY_SIZE(ATTACHED_PROCESSES)) {
        return i;
    }
    return -1;
}
