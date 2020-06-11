# top-level Makefile
#
SHELL = /bin/sh

# Export these variables.
# Variables used by implicit rules like these are NOT normally passed down.
# To override variables used by the sub-make, one has to use the -e switch 
# to make, see below.
prefix = $(HOME)
exec_prefix = $(prefix)
export bindir = $(exec_prefix)/bin/2bp
export includedir = $(prefix)/include/2bp
export libdir = $(exec_prefix)/lib/2bp
export LDFLAGS = -O3 -L$(HOME)/lib/2bp
export CFLAGS = -O3 -DNDEBUG -I$(HOME)/include/2bp

DIRS = 2bp flow

# the sets of directories to do various things in
BUILDDIRS = $(DIRS:%=build-%)
INSTALLDIRS = $(DIRS:%=install-%)
CLEANDIRS = $(DIRS:%=clean-%)
TESTDIRS = $(DIRS:%=test-%)

all: $(BUILDDIRS)
$(DIRS): $(BUILDDIRS)

# Configure makefile for debug/release builds
debug: export LDFLAGS = -g -L$(HOME)/lib/2bp
debug: export CFLAGS = -g -I$(HOME)/include/2bp
debug: $(BUILDDIRS)

# For each subdir, determine the subdir name (by stripping off the 
# "install-") and do a "make" in that dir.
#
# make "install" right after making "build" in each dir.
#
# To override variables CFLAGS/LDFLAGS used by the sub-make, one has to use the
# -e switch.
$(BUILDDIRS): $(bindir) $(includedir) $(libdir)
	$(MAKE) -e -C $(@:build-%=%) 
	$(MAKE) -e -C $(@:build-%=%) install

# Have a target for each directory that must exist
$(bindir): 
	mkdir $@

$(includedir): 
	mkdir $@

$(libdir): 
	mkdir $@

# build dependencies
build-taylor: install-rtbp
build-frtbp: install-taylor
build-prtbp: install-prtbp_noloops
build-cardel:install-hinv install-utils
build-prtbp_del_car: install-cardel install-section install-frtbp \
    install-prtbp_del install-utils
build-intersec_del_car: install-utils install-prtbp install-prtbp_del_car \
	install-errmfld
build-errmfld: install-prtbp_noloops
build-invmfld: install-errmfld
build-invmfld_del_car: install-errmfld install-invmfld \
	install-approxint_del_car
build-frtbp_red: install-2bp
build-flow: install-2bp
build-prtbp_del: install-flow install-hinv_del
build-inner_circ: install-frtbp_red
build-outer_circ: install-flow install-prtbp_del install-inner_circ
build-portbp: install-initcond install-dprtbp
build-portbp_apo: install-initcond_apo install-dprtbp
build-sec1sec2: install-prtbp

install: $(INSTALLDIRS)

$(INSTALLDIRS):
	$(MAKE) -e -C $(@:install-%=%) install

# install dependencies
install-rtbp : build-rtbp
install-taylor: build-taylor
install-frtbp: build-frtbp
install-section: build-section
install-hinv: build-hinv
install-cardel: build-cardel
install-prbtp_del_car: build-prtbp_del_car
install-prbtp: build-prtbp
install-utils: build-utils
install-intersec_del_car: build-intersec_del_car
install-prtbp_noloops: build-prtbp_noloops
install-errmfld: build-errmfld
install-invmfld: build-invmfld
install-invmfld_del_car: build-invmfld_del_car
install-2bp : build-2bp
install-frtbp_red : build-frtbp_red
install-hinv_del : build-hinv_del
install-flow : build-flow
install-prtbp_del : build-prtbp_del
install-inner_circ: build-inner_circ
install-outer_circ: build-outer_circ
install-initcond: build-initcond
install-initcond_apo: build-initcond_apo
install-dprtbp: build-dprtbp
install-portbp: build-portbp
install-portbp_apo: build-portbp_apo
install-sec1sec2: build-portbp
install-hyper: build-hyper
install-approxint_del_car: build-approxint_del_car
install-inner_ell_stoch: build-inner_ell_stoch
install-outer_ell_stoch: build-outer_ell_stoch
install-approxint: build-approxint
install-intersec: build-intersec
install-splitting: build-splitting
install-trtbp: build-trtbp

test: $(TESTDIRS) all
$(TESTDIRS): 
	$(MAKE) -C $(@:test-%=%) test

clean: $(CLEANDIRS) cleanlib cleanfolders

$(CLEANDIRS): 
	$(MAKE) -e -C $(@:clean-%=%) clean

cleanlib:
	rm $(libdir)/lib2BP.a

# This does not work yet... directories must be empty before removing them!
cleanfolders:
#	rmdir $(bindir) $(includedir) $(libdir)

.PHONY: $(DIRS)
.PHONY: $(BUILDDIRS)
.PHONY: $(INSTALLDIRS)
.PHONY: $(TESTDIRS)
.PHONY: $(CLEANDIRS)
.PHONY: all install clean cleanlib test

