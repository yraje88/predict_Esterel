PROJECT?=ensemble

DARKNET=../darknet
VPATH=$(DARKNET):$(DARKNET)/include/*

SRC = 	$(wildcard $(DARKNET)/src/*.c)
OBJ =	$(SRC:.c=.o)
DEPS=	$(wildcard $(DARKNET)/obj/*.o)

# Force 32-bit build on Athlon64/Opteron systems
ifeq ($(shell uname -p), x86_64)
  GCC32=-m32 
endif

export ESTEREL=/opt/esterelv6_01

CC       = gcc
CFLAGS   = $(GCC32) -Wall -L$(ESTEREL)/lib -I$(ESTEREL)/include
LDFLAGS  = $(GCC32) -L$(ESTEREL)/lib -I$(ESTEREL)/include -lrt -lpthread

#CFG      = /home/esterel/etc/v5_92-env
#ESTEREL := $(shell sed -n -e "s/ESTEREL=\(.*\)/\1/p" $(CFG))

ESTEREL2C= $(ESTEREL)/bin/esterel
EFLAGS   =
EFLAGS4X = -simul -I

XES      = $(ESTEREL)/bin/xes
XESFLAGS = -cc "$(CC)" $(foreach t,$(GCC32),-Xcomp $(t))

XEVE     = $(ESTEREL)/bin/xeve

# Fix for XES on a Linux system with glibc-2.3.3:
#    ": undefined reference to `__ctype_b'"
# see: http://newweb.ices.utexas.edu/misc/ctype.c
#
ifeq ($(shell uname -s), Linux)
  XESCTYPEFIX=ctype.o
endif

darknet: 
	$(MAKE) objs -C $(DARKNET)

all: darknet esterel main

proj: esterel main

esterel: $(PROJECT).c

main: $(DEPS) main.c ensemble.c ensemble_data.c tmr.c
	$(CC) -o main $(DEPS) main.c ensemble.c ensemble_data.c tmr.c -I $(DARKNET)/include/include.h -lm -ggdb3 -pthread

mainonly: main.c 
	$(CC) -o main main.c -lm -ggdb3

$(PROJECT).c: $(PROJECT).strl $(PROJECT).h
	@echo " *** Esterel COMPILE $<  --->   $@"
	$(ESTEREL2C) $(EFLAGS) $<