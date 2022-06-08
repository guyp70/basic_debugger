#ifndef PROCESS_DEBUG_H
#define PROCESS_DEBUG_H

#include <sys/ptrace.h>
#include <sys/user.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "make_menu.h"


/**
 * @brief Enter process debug menu and offer debuging operations on the specified process.
 * 
 * @param data Should be a void pointer to pid int. (i.e. int pid = 1928; debug_process_menu((void*)pid); )
 */
void debug_process_menu(void *data);

/**
 * @brief Resume the attached process run. 
 * 
 * @param data Should be a void pointer to pid int. (i.e. int pid = 1928; debug_process_menu((void*)pid); )
 */
void process_continue(void *data);

/**
 * @brief Print the process' registers.
 * 
 * @param data Should be a void pointer to pid int. (i.e. int pid = 1928; debug_process_menu((void*)pid); )
 */
void process_get_registers(void *data);


/**
 * @brief Set the process' registers to specified values.
 * 
 * @param data Should be a void pointer to pid int. (i.e. int pid = 1928; debug_process_menu((void*)pid); )
 */
void process_set_registers(void *data);




#define PROCESS_DEBUG_MENU_CHOICES_LEN    3
#define ARRAY_SIZE(a) (size_t)(sizeof(a) / sizeof(*a))
#define PROCESS_DEBUG_MENU_CHOICES(pid)  ((MenuChoice[])  {    \
    {"continue", "Resume process run", &process_continue, (void*) (&pid)},   \
    {"regs", "Print the process' registers", &process_get_registers, (void*) (&pid)},   \
    {"wregs", "Set the process' registers to values given", &process_set_registers, (void*) (&pid)}   \
})

#define PROCESS_WREGS_MENU_CHOICES_LEN    35
#define PROCESS_WREGS_MENU_CHOICES(regs, fpregs)  ((MenuChoice[])  {    \
    {"cs", "", &set_value_llu, (void*)(&(regs.cs))},    \
    {"ds", "", &set_value_llu, (void*)(&(regs.ds))},    \
    {"es", "", &set_value_llu, (void*)(&(regs.es))},    \
    {"eflags", "", &set_value_llu, (void*)(&(regs.eflags))},    \
    {"fs", "", &set_value_llu, (void*)(&(regs.fs))},    \
    {"fs_base", "", &set_value_llu, (void*)(&(regs.fs_base))},    \
    {"gs", "", &set_value_llu, (void*)(&(regs.gs))},    \
    {"gs_base", "", &set_value_llu, (void*)(&(regs.gs_base))},    \
    {"orig_rax", "", &set_value_llu, (void*)(&(regs.orig_rax))},    \
    {"r8", "", &set_value_llu, (void*)(&(regs.r8))},    \
    {"r9", "", &set_value_llu, (void*)(&(regs.r9))},    \
    {"r10", "", &set_value_llu, (void*)(&(regs.r10))},    \
    {"r11", "", &set_value_llu, (void*)(&(regs.r11))},    \
    {"r12", "", &set_value_llu, (void*)(&(regs.r12))},    \
    {"r13", "", &set_value_llu, (void*)(&(regs.r13))},    \
    {"r14", "", &set_value_llu, (void*)(&(regs.r14))},    \
    {"r15", "", &set_value_llu, (void*)(&(regs.r15))},    \
    {"rax", "", &set_value_llu, (void*)(&(regs.rax))},    \
    {"rbx", "", &set_value_llu, (void*)(&(regs.rbx))},    \
    {"rcx", "", &set_value_llu, (void*)(&(regs.rcx))},    \
    {"rbp", "", &set_value_llu, (void*)(&(regs.rbp))},    \
    {"rdi", "", &set_value_llu, (void*)(&(regs.rdi))},    \
    {"rdx", "", &set_value_llu, (void*)(&(regs.rdx))},    \
    {"rip", "", &set_value_llu, (void*)(&(regs.rip))},    \
    {"rsi", "", &set_value_llu, (void*)(&(regs.rsi))},    \
    {"rsp", "", &set_value_llu, (void*)(&(regs.rsp))},    \
    {"ss", "", &set_value_llu, (void*)(&(regs.ss))},    \
    {"cwd", "", &set_value_h ,(void*)(&(fpregs.cwd))},    \
    {"swd", "", &set_value_h ,(void*)(&(fpregs.swd))},    \
    {"ftw", "", &set_value_h ,(void*)(&(fpregs.ftw))},    \
    {"fop", "", &set_value_h ,(void*)(&(fpregs.fop))},    \
    {"rip", "", &set_value_llu, (void*)(&(fpregs.rip))},    \
    {"rdp", "", &set_value_llu, (void*)(&(fpregs.rdp))},    \
    {"mxcsr", "", &set_value_int, (void*)(&(fpregs.mxcsr))},    \
    {"mxcr_mask", "", &set_value_int, (void*)(&(fpregs.mxcr_mask))}    \
})
#endif // PROCESS_DEBUG_H

