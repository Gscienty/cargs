#include "cargs_call_x86_64.h"
#include <malloc.h>
#include <stdlib.h>

/**
 * arch x86_64 call
 * @param process: process
 * 
 */
void cargs_call_x86_64(const struct __cargs_theme * const process)
{
    struct __cargs_arg_type *arg_type;
    char *arg;
    int args_count = cargs_process_args_count(process);
    int args_size = cargs_process_args_size(process);
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
        __asm__ __volatile__ ("call *%0"
                              :
                              :"m" (process->fptr));
        break;
    case 1:
        __asm__ __volatile__ ("push %%rbp;"
                              "mov %1, %%rbp;"
                              "mov (%%rbp), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "pop %%rbp;"
                              "call *%0"
                              :
                              : "m" (process->fptr),
                                "m" (args_buffer));
        break;
    case 2:
        __asm__ __volatile__ ("push %%rbp;"
                              "mov %1, %%rbp;"
                              "mov (%%rbp), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "mov 0x8(%%rbp), " CARGS_X86_64_ASM_PARAM_2 ";"
                              "pop %%rbp;"
                              "call *%0"
                              :
                              : "m" (process->fptr),
                                "m" (args_buffer));
        break;
    case 3:
        __asm__ __volatile__ ("push %%rbp;"
                              "mov %1, %%rbp;"
                              "mov (%%rbp), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "mov 0x8(%%rbp), " CARGS_X86_64_ASM_PARAM_2 ";"
                              "mov 0x10(%%rbp), " CARGS_X86_64_ASM_PARAM_3 ";"
                              "pop %%rbp;"
                              "call *%0"
                              :
                              : "m" (process->fptr),
                                "m" (args_buffer));
        break;
    case 4:
        __asm__ __volatile__ ("push %%rbp;"
                              "mov %1, %%rbp;"
                              "mov (%%rbp), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "mov 0x8(%%rbp), " CARGS_X86_64_ASM_PARAM_2 ";"
                              "mov 0x10(%%rbp), " CARGS_X86_64_ASM_PARAM_3 ";"
                              "mov 0x18(%%rbp), " CARGS_X86_64_ASM_PARAM_4 ";"
                              "pop %%rbp;"
                              "call *%0"
                              :
                              : "m" (process->fptr),
                                "m" (args_buffer));
        break;
    case 5:
        __asm__ __volatile__ ("push %%rbp;"
                              "mov %1, %%rbp;"
                              "mov (%%rbp), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "mov 0x8(%%rbp), " CARGS_X86_64_ASM_PARAM_2 ";"
                              "mov 0x10(%%rbp), " CARGS_X86_64_ASM_PARAM_3 ";"
                              "mov 0x18(%%rbp), " CARGS_X86_64_ASM_PARAM_4 ";"
                              "mov 0x20(%%rbp), " CARGS_X86_64_ASM_PARAM_5 ";"
                              "pop %%rbp;"
                              "call *%0"
                              :
                              : "m" (process->fptr),
                                "m" (args_buffer));
        break;
    case 6:
        __asm__ __volatile__ ("push %%rbp;"
                              "mov %1, %%rbp;"
                              "mov (%%rbp), " CARGS_X86_64_ASM_PARAM_1 ";"
                              "mov 0x8(%%rbp), " CARGS_X86_64_ASM_PARAM_2 ";"
                              "mov 0x10(%%rbp), " CARGS_X86_64_ASM_PARAM_3 ";"
                              "mov 0x18(%%rbp), " CARGS_X86_64_ASM_PARAM_4 ";"
                              "mov 0x20(%%rbp), " CARGS_X86_64_ASM_PARAM_5 ";"
                              "mov 0x28(%%rbp), " CARGS_X86_64_ASM_PARAM_6 ";"
                              "pop %%rbp;"
                              "call *%0"
                              :
                              : "m" (process->fptr),
                                "m" (args_buffer));
        break;
    }

    free(args_buffer);
}
