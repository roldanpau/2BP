SHELL = /bin/sh
prefix = $(HOME)
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin/2bp
includedir = $(prefix)/include/2bp
libdir = $(exec_prefix)/lib/2bp

LDFLAGS = -O3 -L$(HOME)/lib/2bp
CFLAGS = -O3 -DNDEBUG -I$(HOME)/include/2bp
LDLIBS = -lgsl -lgslcblas -l2BP -lm

all : dflow

install : dflow dflow_module.o dflow_module.h 
	ar rv $(libdir)/lib2BP.a dflow_module.o 
	cp dflow_module.h $(includedir)
	cp dflow $(bindir)

dflow : dflow.o dflow_module.o

clean : 
	rm dflow dflow.o dflow_module.o
