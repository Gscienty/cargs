#include "cargs.h"
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
    cargs_run(argc, argv, NULL);

}
