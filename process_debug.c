#include "process_debug.h"


void debug_process_menu(void *data) {
    int pid = *((int*) data);
    
    make_menu(PROCESS_DEBUG_MENU_CHOICES(pid), PROCESS_DEBUG_MENU_CHOICES_LEN);
}


void process_continue(void *data){
    int pid = *((int*) data);
    if (ptrace(PTRACE_CONT, pid, 0, 0) == -1) {
        perror("Failed to continue process run");
    } else {
        printw("Process run resumed.\n");
    }
    wait_for_key_press();
}

void process_read_memory(void *data){
    int pid = *((int*) data);
    unsigned long long addr = 0;
    unsigned long long peeked_word = 0;

    if (get_address(&addr) == -1) {
        return;
    }
    errno = 0;
    peeked_word = ptrace(PTRACE_PEEKDATA, pid, (void*) &addr, NULL);
    if (errno != 0) {
        perror("Failed to peek into memory at the specified address");
    } else {
        printw("Process memory at address %p: %llX.\n", addr, peeked_word);
    }
    wait_for_key_press();
}

void process_set_memory(void *data){
    int pid = *((int*) data);
    unsigned long long addr = 0;
    unsigned long long word = 0;

    printw("Dest address:\n");
    if (get_address(&addr) == -1) {
        return;
    }
    printw("Word to write to dest:\n");
    if (get_value_llu(&word) == -1) {
        return;
    }
    ;
    if (ptrace(PTRACE_POKEDATA, pid, (void*) &addr, (void*) &word) == -1) {
        perror("Failed to write into memory at the specified address");
    } else {
        printw("Process memory at address %p was set to value: %llX.\n", addr, word);
    }
    wait_for_key_press();
}

void process_get_registers(void *data){
    struct user_fpregs_struct fpregs;
    struct user_regs_struct regs;
    int pid = *((int*) data);

    if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1) {
        perror("Failed to read process general purpose registers");
    } else {
        printw("General purpose registers:\n");
        printw("cs: %llX\n", regs.cs);
        printw("ds: %llX\n", regs.ds);
        printw("es: %llX\n", regs.es);
        printw("eflags: %llX\n", regs.eflags);
        printw("fs: %llX\n", regs.fs);
        printw("fs_base: %llX\n", regs.fs_base);
        printw("gs: %llX\n", regs.gs);
        printw("gs_base: %llX\n", regs.gs_base);
        printw("orig_rax: %llX\n", regs.orig_rax);
        printw("r8: %llX\n", regs.r8);
        printw("r9: %llX\n", regs.r9);
        printw("r10: %llX\n", regs.r10);
        printw("r11: %llX\n", regs.r11);
        printw("r12: %llX\n", regs.r12);
        printw("r13: %llX\n", regs.r13);
        printw("r14: %llX\n", regs.r14);
        printw("r15: %llX\n", regs.r15);
        printw("rax: %llX\n", regs.rax);
        printw("rbx: %llX\n", regs.rbx);
        printw("rcx: %llX\n", regs.rcx);
        printw("rbp: %llX\n", regs.rbp);
        printw("rdi: %llX\n", regs.rdi);
        printw("rdx: %llX\n", regs.rdx);
        printw("rip: %llX\n", regs.rip);
        printw("rsi: %llX\n", regs.rsi);
        printw("rsp: %llX\n", regs.rsp);
        printw("ss: %llX\n", regs.ss);
    }
    if (ptrace(PTRACE_GETFPREGS, pid, 0, &fpregs) == -1) {
        perror("Failed to read process floating point registers");
    } else {
        printw("Floating point registers:\n");
        printw("cwd: %hX\n", fpregs.cwd);
        printw("swd: %hX\n", fpregs.swd);
        printw("ftw: %hX\n", fpregs.ftw);
        printw("fop: %hX\n", fpregs.fop);
        printw("rip: %llu\n", fpregs.rip);
        printw("rdp: %llu\n", fpregs.rdp);
        printw("mxcsr: %X\n", fpregs.mxcsr);
        printw("mxcr_mask: %X\n", fpregs.mxcr_mask);
        //TODO: print st_space and xmm_space
    }
    wait_for_key_press();
}

void process_set_registers(void *data){
    struct user_fpregs_struct fpregs;
    struct user_regs_struct regs;
    int pid = *((int*) data);

    if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1) {
        perror("Failed to read process general purpose registers");
        wait_for_key_press();
        return;
    }
    if (ptrace(PTRACE_GETFPREGS, pid, 0, &fpregs) == -1) {
        perror("Failed to read process floating point registers");
        wait_for_key_press();
        return;
    }
    make_menu(PROCESS_WREGS_MENU_CHOICES(regs, fpregs), PROCESS_WREGS_MENU_CHOICES_LEN);
    if (ptrace(PTRACE_SETREGS, pid, 0, &regs) == -1) {
        perror("Failed to set process general purpose registers");
        wait_for_key_press();
        return;
    }
    if (ptrace(PTRACE_SETFPREGS, pid, 0, &fpregs) == -1) {
        perror("Failed to set process floating point registers");
        wait_for_key_press();
        return;
    }
    printw("Process registers updated.\n");
    wait_for_key_press();
}