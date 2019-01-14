#include "cargs_themes.h"
#include <stdio.h>

cargs_process(test_process, __SET__(), int a, int b)
{
    printf("%d\n", a + b);
}


typedef void (*void_fptr_int_int)(int, int);

int main()
{
    cargs_processes_init();

    const struct __cargs_theme *theme = cargs_find_process("test_process");

    void_fptr_int_int fptr = (void_fptr_int_int) theme->fptr;

    fptr(255, 245);

    return 0;
}
