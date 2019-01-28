#include "cargs_call.h"

#ifdef X86_64

#include "cargs_call_x86_64.c"

/**
 * arch x86_64 call
 * @param process: process
 * 
 */
void cargs_call(const struct __cargs_theme * const process)
{
    __call_x86_64(process);
}

#endif
