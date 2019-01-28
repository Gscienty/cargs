#ifndef _CARGS_H
#define _CARGS_H

#include "cargs_arg.h"
#include "cargs_themes.h"
#include "cargs_arg_type.h"
#include "cargs_call.h"

typedef void (*notfound_functype) ();

#define cargs_run(argc, argv, notfound_func) ({                                              \
                                              const struct __cargs_theme *__process;         \
                                              cargs_args_init();                             \
                                              cargs_arg_type_init();                         \
                                              cargs_processes_init();                        \
                                              cargs_transfer(argc, argv);                    \
                                              __process = cargs_satisfy_process();           \
                                              if (__process == NULL) {                       \
                                                  if (notfound_func != NULL)                 \
                                                      ((notfound_functype) notfound_func)(); \
                                                  return 0;                                  \
                                              }                                              \
                                              cargs_call(__process);                         \
                                              })



#endif
