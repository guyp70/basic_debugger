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

void process_get_registers(void *data){
    struct user_fpregs_struct fpregs;
    struct user_regs_struct regs;
    int pid = *((int*) data);

    if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1) {
        perror("Failed to read process general purpose registers");
    } else {
        printw("General purpose registers:\n");
        printw("cs: %Xll\n", regs.cs);
        printw("ds: %Xll\n", regs.ds);
        printw("es: %Xll\n", regs.es);
        printw("eflags: %Xll\n", regs.eflags);
        printw("fs: %Xll\n", regs.fs);
        printw("fs_base: %Xll\n", regs.fs_base);
        printw("gs: %Xll\n", regs.gs);
        printw("gs_base: %Xll\n", regs.gs_base);
        printw("orig_rax: %Xll\n", regs.orig_rax);
        printw("r8: %Xll\n", regs.r8);
        printw("r9: %Xll\n", regs.r9);
        printw("r10: %Xll\n", regs.r10);
        printw("r11: %Xll\n", regs.r11);
        printw("r12: %Xll\n", regs.r12);
        printw("r13: %Xll\n", regs.r13);
        printw("r14: %Xll\n", regs.r14);
        printw("r15: %Xll\n", regs.r15);
        printw("rax: %Xll\n", regs.rax);
        printw("rbx: %Xll\n", regs.rbx);
        printw("rcx: %Xll\n", regs.rcx);
        printw("rbp: %Xll\n", regs.rbp);
        printw("rdi: %Xll\n", regs.rdi);
        printw("rdx: %Xll\n", regs.rdx);
        printw("rip: %Xll\n", regs.rip);
        printw("rsi: %Xll\n", regs.rsi);
        printw("rsp: %Xll\n", regs.rsp);
        printw("ss: %Xll\n", regs.ss);
    }
    if (ptrace(PTRACE_GETFPREGS, pid, 0, &fpregs) == -1) {
        perror("Failed to read process floating point registers");
    } else {
        printw("Floating point registers:\n");
        printw("cwd: %Xh\n", fpregs.cwd);
        printw("swd: %Xh\n", fpregs.swd);
        printw("ftw: %Xh\n", fpregs.ftw);
        printw("fop: %Xh\n", fpregs.fop);
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