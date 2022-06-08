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

size_t get_num_of_attached_processes() {
    size_t num_of_attached_processes = 0, i = 0;
    for (i=0; i < ARRAY_SIZE(ATTACHED_PROCESSES); i++) {
        if (EMPTY_PID_CELL_MARKER != ATTACHED_PROCESSES[i]) {
            num_of_attached_processes++;
        }
    }
    return num_of_attached_processes;
}


int get_process_cmd_by_pid(const int pid, char* buf) {
    size_t i;
    FILE* f;

    sprintf(buf, "/proc/%d/cmdline", pid);
    f = fopen(buf,"r");
    if(f){
        size_t size;
        size = fread(buf, sizeof(char), MAX_PROCESS_CMD_LEN, f);
        if(size > 0){
            for (i=0; i < size-1; i++) {
                if ('\00' == buf[i]) {
                    buf[i] = ' ';
                }
            }
            if('\n' == buf[size-1])
                buf[size - 1] = '\0';
        }
        else {
            //TODO: ADD ERROR HANDLING
            return -1;
        }
        fclose(f);
    }
    else {
        //TODO: ADD ERROR HANDLING
        return -1;
    }
    return 0;
}

