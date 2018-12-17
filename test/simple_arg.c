#include "cargs_arg.h"
#include <stdio.h>

cargs_flag(simple_arg_flag1, __SET__("flag1", "flag2", "flag3") );
cargs_flag(simple_arg_flag2, __SET__("flag1", "flag4"));
cargs_flag(simple_arg_flag3, __SET__("flag1"));
cargs_flag(simple_arg_flag4, __SET__("flag2"));

int main()
{
    struct cargs_llnode *head;
    struct cargs_llnode *p;
    int i = 0;

    cargs_args_init();

    head = cargs_args_find("flag1");

    for (p = head->next; p != head; p = p->next) {
        i++;
    }

    printf("%d\n", i);

    return 0;
}
