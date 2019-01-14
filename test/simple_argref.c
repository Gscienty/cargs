#include "cargs_themes.h"
#include "cargs_arg.h"
#include <stdio.h>

cargs_flag(a, __SET__("a"));
cargs_subarg(a, a_v1, __SET__("av1"),
             __SET__(arg_type_int));
cargs_subarg(a, a_v2, __SET__("av2"),
             __SET__(arg_type_short));

cargs_process(a_process,
              __SET__(cargs_theme_arg(a_v1, true),
                      cargs_theme_arg(a_v2, false)),
              int val, short val2) {
    printf("%d %d\n", val, val2);
}

int main(int argc, char **argv)
{
    bool transfer_success;
    cargs_processes_init();
    cargs_args_init();
    cargs_arg_type_init();

    transfer_success = cargs_transfer(argc, argv);
    printf("%d\n", transfer_success);

    const struct __cargs_theme *process = cargs_satisfy_process();

    printf("%08x %ld\n",
           (unsigned int) process,
           cargs_process_args_size(process));

    return 0;
}
