SHELL = /bin/sh
prefix = $(HOME)
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
includedir = $(prefix)/include
libdir = $(exec_prefix)/lib
CFLAGS = -O3 #-g
LDFLAGS = -O3 #-g
LDLIBS = -lm -lgsl -lgslcblas

all : 2bp

install : 2bp 2bp_module.o 2bp_module.h
	ar rv $(libdir)/lib2BP.a 2bp_module.o
	cp 2bp_module.h $(includedir)
	cp 2bp $(bindir)

2bp : 2bp.o 2bp_module.o

clean : 
	rm 2bp 2bp.o 2bp_module.o
