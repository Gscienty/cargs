#include "cargs.h"

/**
 * cargs run
 * 
 */
int cargs_run(int argc, char ** argv, notfound_functype fptr)
{
    const struct __cargs_theme *__process;         
    cargs_args_init();                             
    cargs_arg_type_init();                         
    cargs_processes_init();                        

    cargs_transfer(argc, argv);                    

    __process = cargs_satisfy_process();
    if (__process == NULL) {
        if (fptr != NULL)
            fptr();
        return 1;                                  
    }                                              

    cargs_call(__process);                         

    return 0;
}
