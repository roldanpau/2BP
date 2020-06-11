SHELL = /bin/sh
prefix = $(HOME)
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin/2bp
includedir = $(prefix)/include/2bp
libdir = $(exec_prefix)/lib/2bp

LDFLAGS = -O3 -L$(HOME)/lib/2bp
CFLAGS = -O3 -DNDEBUG -I$(HOME)/include/2bp
LDLIBS = -lgsl -lgslcblas -l2BP -lm

all : flow

install : flow flow_module.o flow_module.h 
	ar rv $(libdir)/lib2BP.a flow_module.o 
	cp flow_module.h $(includedir)
	cp flow $(bindir)

flow : flow.o flow_module.o

clean : 
	rm flow flow.o flow_module.o
