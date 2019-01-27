CC = gcc
PWD = $(shell pwd)
BFLAG = -g
INC = $(PWD)/include
SRC = $(PWD)/src/
BUILDOBJ = $(CC) $(BFLAG) -c -I $(INC) -o $@.o $(SRC)$@.c

MODULES = cargs_arg                  \
		  cargs_arg_type             \
		  cargs_call_x86_64          \
		  cargs_linked_list          \
		  cargs_rbtree               \
		  cargs_themes

LIBNAME = libcargs.so
ARNAME = libcargs.a

all: objs
	#$(CC) -shared $(BFLAG) -pipe $(addsuffix .o, $(MODULES)) -o $(LIBNAME)
	ar -rc $(ARNAME) $(addsuffix .o, $(MODULES))

objs: $(MODULES)

cargs_arg:
	$(BUILDOBJ)

cargs_arg_type:
	$(BUILDOBJ)

cargs_call_x86_64:
	$(BUILDOBJ)

cargs_linked_list:
	$(BUILDOBJ)

cargs_rbtree:
	$(BUILDOBJ)

cargs_themes:
	$(BUILDOBJ)

clean:
	rm $(addsuffix .o, $(MODULES))
	rm $(LIBNAME)
	rm $(ARNAME)
