SHELL = /bin/sh
prefix = $(HOME)
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin/2bp
includedir = $(prefix)/include/2bp
libdir = $(exec_prefix)/lib/2bp
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
