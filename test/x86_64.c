#include "cargs_arg.h"
#include "cargs_themes.h"
#include "cargs_call_x86_64.h"
#include "cargs_type/x86_64.h"
#include <stdio.h>
#include <malloc.h>

cargs_arg(one_arg, __SET__("arg"),
          __SET__(arg_type_int,
                  arg_type_int,
                  arg_type_byte,
                  arg_type_int,
                  arg_type_int,
                  arg_type_int,
                  arg_type_int,
                  arg_type_int
                  ));

cargs_process(one_arg,
              __SET__(cargs_theme_arg(one_arg, true)),
              int a, int b, char c, int d, int e, int f, int g, int h)
{
    printf("%d %d %c\n", a, b, c);
    printf("%d %d %d\n", d, e, f);
    printf("%d %d\n", g, h);
}


int main(int argc, char **argv)
{
    const struct __cargs_theme *process;

    printf("%d\n", argc);

    cargs_args_init();
    cargs_arg_type_init();
    cargs_processes_init();

    cargs_transfer(argc, argv);
    process = cargs_satisfy_process();
    
    if (process == NULL) {
        printf("WHAT\n");
        return 0;
    }

    cargs_call_x86_64(process);
}
