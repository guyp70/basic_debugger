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
    int error_num;
    FILE* f;
    char *err_msg_init;

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
            err_msg_init = "Empty command line. (process may have terminated)";
            strcpy(buf, err_msg_init);
            return -1;
        }
        fclose(f);
    }
    else {
        //TODO: ADD ERROR HANDLING
        error_num = errno;
        err_msg_init = "Porcess cmd line not found. Error: ";
        strcpy(buf, err_msg_init);
        strerror_r(error_num, &(buf[strlen(err_msg_init) - 1]), MAX_PROCESS_CMD_LEN - (strlen(err_msg_init) - 1));
        return -1;
    }
    return 0;
}


int get_address(unsigned long long *addr){
    int n = 0;
    printw("Please enter an hexadecimal address (unsigned long long): ");
    if (scanw("%p%n", addr, &n) == 1 && n == 0){
        printw("n %d %X11", n, addr);
        return 0;
    }
    printw("n %d %p", n, addr);
    printw("Bad format. Value not recieved.\n");
    wait_for_key_press();
    return -1;
}


int get_value_llu(unsigned long long *addr){
    int n = 0;
    printw("Please enter an hexadecimal value (long long): ");
    if (scanw("%Xll%n", addr, &n) == 1 && 0 == n){
        printw("Value recieved.\n");
        wait_for_key_press();
        return 0;
    } else {
        printw("Bad format. Value not recieved.\n");
        wait_for_key_press();
        return -1;
    }
}


void set_value_llu(void *addr){
    get_value_llu((unsigned long long*)addr);
}


void set_value_h(void *addr){
    int n = 0;
    printw("Please enter an hexadecimal value (short): ");
    if (scanw("%Xh%n", ((unsigned short int*)(addr)), &n) == 1 && 0 == n){
        printw("Value recieved.\n");
    } else {
        printw("Bad format. Value not recieved.\n");
    }
    wait_for_key_press();
}
void set_value_int(void *addr){
    int n = 0;
    printw("Please enter an hexadecimal value (int): ");
    if (scanw("%X%n", ((unsigned int*)(addr)), &n) == 1 && 0 == n){
        printw("Value recieved.\n");
    } else {
        printw("Bad format. Value not recieved.\n");
    }
    wait_for_key_press();
}
