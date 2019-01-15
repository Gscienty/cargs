#include "cargs_arg_type.h"
#include <stdlib.h>

static bool __is_number(const char * const arg)
{
    int i;
    if (arg[0] == '-') {
        i = 1;
    }
    else {
        i = 0;
    }

    for (; arg[i] != 0; i++) {
        if (arg[i] < '0' || '9' < arg[i]) {
            return false;
        }
    }

    if (i == 0) {
        return false;
    }

    return true;
}

static bool __attribute__((used)) __byte_examiner(const char * const arg)
{
    char val;
    if (!__is_number(arg)) {
        return false;
    }

    val = atoi(arg);
    return -0x80 <= val && val <= 0x7F;
}

static void __attribute__((used)) __byte_transfer(char * const buf, const char * const arg)
{
    buf[0] = atoi(arg);
}

cargs_arg_type(arg_type_byte, 8,
               __byte_examiner, __byte_transfer);

static bool __attribute__((used)) __short_examiner(const char * const arg)
{
    short val;

    if (!__is_number(arg)) {
        return false;
    }

    val = atoi(arg);
    return -0x8000 <= val && val <= 0x7FFF;
}

static void  __attribute__((used)) __short_transfer(char * const buf, const char * const arg)
{
    int val;
    int i;

    val = atoi(arg);
    for (i = 0; i < 2; i++) {
        buf[i] = ((char *) &val)[i];
    }
}

cargs_arg_type(arg_type_short, 8,
               __short_examiner, __short_transfer);

static bool  __attribute__((used)) __int_examiner(const char * const arg)
{
    int val;

    if (!__is_number(arg)) {
        return false;
    }

    val = atoi(arg);
    return -0x80000000L <= val && val <= 0x7FFFFFFF;
}

static void  __attribute__((used)) __int_transfer(char * const buf, const char * const arg)
{
    int val;
    int i;
    
    val = atoi(arg);
    for (i = 0; i < 4; i++) {
        buf[i] = ((char *) &val)[i];
    }
}

cargs_arg_type(arg_type_int, 8,
               __int_examiner, __int_transfer);

static bool  __attribute__((used)) __string_examiner(const char * const arg)
{
    (void) arg;
    return true;
}

static void  __attribute__((used)) __string_transfer(char * const buf, const char * const arg)
{
    size_t i;

    for (i = 0; i < sizeof(char *); i++) {
        buf[i] = ((char *) &arg)[i];
    }
}

cargs_arg_type(arg_type_string, 8,
               __string_examiner, __string_transfer);
