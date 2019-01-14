#include "cargs_arg.h"
#include <stdio.h>

cargs_flag(simple_arg_flag1, __SET__("flag1", "flag2", "flag3") );
cargs_flag(simple_arg_flag2, __SET__("flag1", "flag4"));
cargs_flag(simple_arg_flag3, __SET__("flag1"));
cargs_flag(simple_arg_flag4, __SET__("flag2"));
cargs_subflag(simple_arg_flag2, simple_arg_flag5, __SET__("flag5"));

cargs_arg(simple_arg_int,
          __SET__("arg1"),
          __SET__(arg_type_int, arg_type_byte, arg_type_short));

int main(int argc, char **argv)
{
    struct cargs_llnode *head;
    struct cargs_llnode *p;
    bool transfer_success;

    cargs_arg_type_init();
    cargs_args_init();

    head = cargs_args_find("flag1");

    transfer_success = cargs_transfer(argc, argv);
    printf("%d\n", transfer_success);

    for (p = head->next; p != head; p = p->next) {
        if (ll_entry(p, struct __cargs_arg_llnode, node)->arg->enable) {
            printf("%s\n", ll_entry(p, struct __cargs_arg_llnode, node)->arg->_inner_name);
        }
    }

    printf("%ld\n", cargs_arg_size(&CARGS_ARG_STRUCT_NAME(simple_arg_int)));

    return 0;
}
