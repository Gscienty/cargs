#include "cargs_themes.h"
#include <malloc.h>
#include <stdlib.h>

#define CARGS_X86_64_ASM_PARAM_1 "%%rdi"
#define CARGS_X86_64_ASM_PARAM_2 "%%rsi"
#define CARGS_X86_64_ASM_PARAM_3 "%%rdx"
#define CARGS_X86_64_ASM_PARAM_4 "%%rcx"
#define CARGS_X86_64_ASM_PARAM_5 "%%r8"
#define CARGS_X86_64_ASM_PARAM_6 "%%r9"

#define CARGS_X86_64_ASM_REG_MAX 6

static void __call_x86_64(const struct __cargs_theme * const process)
{
    struct __cargs_arg_type *arg_type;
    char *arg;
    int args_count = cargs_process_args_count(process);
    int args_size = cargs_process_args_size(process);
    int remain_args = 0;
    int args_off = 0;
    int i;
    int j;
    void *args_buffer = calloc(args_size, 1);
    if (args_buffer == NULL) {
        exit(-1);
    }

    for (i = 0;
         process->args[i].arg
         && i < CARGS_THEME_ARGS_MAX;
         i++) {
        for (j = 0;
             process->args[i].arg->args_type[j] != arg_type_null
             && j < CARGS_ARG_TYPE_MAX;
             j++) {
           arg_type = cargs_find_arg_type(process->args[i].arg->args_type[j]);
           arg = process->args[i].arg->params[j];
           arg_type->transfer(args_buffer + args_off, arg);
           args_off += arg_type->value_size;
        }
    }
    
    switch (args_count) {
    case 0:
        break;
    case 1:
        __asm__ __volatile__ (
                              "mov %0, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_1 ";"
                              :
                              : "m" (args_buffer));
        break;
    case 2:
        __asm__ __volatile__ (
                              "mov %0, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_2 ";"
                              :
                              : "m" (args_buffer));
        break;
    case 3:
        __asm__ __volatile__ (
                              "mov %0, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_2 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_3 ";"
                              :
                              : "m" (args_buffer));
        break;
    case 4:
        __asm__ __volatile__ (
                              "mov %0, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_2 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_3 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_4 ";"
                              :
                              : "m" (args_buffer));
        break;
    case 5:
        __asm__ __volatile__ (
                              "mov %0, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_2 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_3 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_4 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_5 ";"
                              :
                              : "m" (args_buffer));
        break;
    case 6:
        __asm__ __volatile__ (
                              "mov %0, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_2 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_3 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_4 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_5 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_6 ";"
                              :
                              : "m" (args_buffer));
        break;
    default:
        remain_args = (args_count - 6) * 8;
        __asm__ __volatile__ (
                              "mov %0, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_2 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_3 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_4 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_5 ";"
                              "add $0x8, %%eax;"
                              "mov (%%eax), " CARGS_X86_64_ASM_PARAM_6 ";"
                              :
                              : "m" (args_buffer));
        __asm__ __volatile__ (
                              "mov %1, %%eax;"
                              "mov %0, %%ebx;"
                              "add $0x28, %%ebx;"
                              "add %%ebx, %%eax;"

                              "__prepare:;"
                              "push (%%eax);"
                              "sub $0x8, %%eax;"
                              "cmp %%eax, %%ebx;"
                              "jnz __prepare;"
                              :
                              : "m" (args_buffer),
                                "m" (remain_args));
        break;
    }
    __asm__ __volatile__ (
                          "call *%0"
                          :
                          : "m" (process->fptr));

    free(args_buffer);
}
