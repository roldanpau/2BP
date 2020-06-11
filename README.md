# Description

Library of routines related to the Two Body Problem, or Kepler problem:

* vectorfield of the 2BP
* flow of the 2BP

This project will be used mostly by my students.

The goal of this project is to familiarize with the 2BP and with numerical
integration.

# Installation

The code is intended for Linux systems (or compatible). It assumes that the
GSL development package has been installed. In Ubuntu, for example, this can be
done via
```
sudo apt-get install libgsl-dev
```

First clone this repository to your local machine.

In the root directory (2BP) there are several subdirs (e.g. 2BP/flow). Each
subdir contains code to perform a specific task (e.g. to compute the time-t
flow).

To compile everything, just type 'make' in the root directory. This will
compile all code and build all test programs. This will also create some
directories in your HOME, to hold the binaries/include files/libraries:

* $(HOME)/bin/2bp
* $(HOME)/include/2bp
* $(HOME)/lib/2bp

To uninstall, just type 'make clean' in the root directory.
