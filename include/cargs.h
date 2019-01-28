#ifndef _CARGS_H
#define _CARGS_H

#include "cargs_arg.h"
#include "cargs_themes.h"
#include "cargs_arg_type.h"
#include "cargs_call.h"

typedef void (*notfound_functype) ();

/**
 * cargs run
 * 
 */
int cargs_run(int argc, char ** argv, notfound_functype fptr);

#endif
