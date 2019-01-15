#ifndef _CARGS_CALL_X86_64_H
#define _CARGS_CALL_X86_64_H

#include "cargs_themes.h"

#define CARGS_X86_64_ASM_PARAM_1 "%%rdi"
#define CARGS_X86_64_ASM_PARAM_2 "%%rsi"
#define CARGS_X86_64_ASM_PARAM_3 "%%rdx"
#define CARGS_X86_64_ASM_PARAM_4 "%%rcx"
#define CARGS_X86_64_ASM_PARAM_5 "%%r8"
#define CARGS_X86_64_ASM_PARAM_6 "%%r9"

#define CARGS_X86_64_ASM_REG_MAX 6

/**
 * arch x86_64 call
 * @param process: process
 * 
 */
void cargs_call_x86_64(const struct __cargs_theme * const process);

#endif
