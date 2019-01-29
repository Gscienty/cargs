CC = gcc
PWD = $(shell pwd)
BFLAG = -g -D=X86_64
INC = $(PWD)/include
SRC = $(PWD)/src/
BUILDOBJ = $(CC) $(BFLAG) -c -I $(INC) -o $@.o $(SRC)$@.c

MODULES = cargs_arg         \
		  cargs_arg_type    \
		  cargs_call        \
		  cargs_linked_list \
		  cargs_rbtree      \
		  cargs_themes		\
		  cargs

ARNAME = libcargs.a

all: objs
	ar -rc $(ARNAME) $(addsuffix .o, $(MODULES))

objs: $(MODULES)

cargs_arg:
	$(BUILDOBJ)

cargs_arg_type:
	$(BUILDOBJ)

cargs_call:
	$(BUILDOBJ)

cargs_linked_list:
	$(BUILDOBJ)

cargs_rbtree:
	$(BUILDOBJ)

cargs_themes:
	$(BUILDOBJ)

cargs:
	$(BUILDOBJ)

clean:
	rm $(addsuffix .o, $(MODULES))
	rm $(ARNAME)
