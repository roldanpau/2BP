SHELL = /bin/sh
prefix = $(HOME)
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin/2bp
includedir = $(prefix)/include/2bp
libdir = $(exec_prefix)/lib/2bp

LDFLAGS = -O3 -L$(HOME)/lib/2bp
CFLAGS = -O3 -DNDEBUG -I$(HOME)/include/2bp
LDLIBS = -lgsl -lgslcblas -l2BP -lm

all : vareq

install : vareq vareq_module.o vareq_module.h
	ar rv $(libdir)/lib2BP.a vareq_module.o
	cp vareq_module.h $(includedir)
	cp vareq $(bindir)

vareq : vareq.o vareq_module.o

clean : 
	rm vareq vareq.o vareq_module.o
