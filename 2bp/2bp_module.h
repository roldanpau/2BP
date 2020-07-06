/*! \file
    \brief Two Body Problem equations (Kepler Problem).

    $Author: roldan $
    $Date: 2013-03-26 22:26:03 $
*/

/*! \mainpage Two Body Problem Library

  \section Description

  Library of routines related to the Two Body Problem, or Kepler problem:
  - vectorfield of the 2BP
  - flow of the 2BP
  - variational equations
  
  This project will be used mostly by my students.

  The goal of this project is to familiarize with the 2BP and with numerical
  integration.

  \section Installation

  This code is intended for Linux systems (or compatible). It assumes that the
  GSL development package has been installed. In Ubuntu, for example, this can
  be done via
  ``sudo apt-get install libgsl-dev``

  First clone this repository to your local machine. 

  In the root directory (2BP) there are several subdirs (e.g. 2BP/flow). Each
  subdir contains code to perform a specific task (e.g. to compute the time-t
  flow).

  To compile everything, just type `make' in the root directory. This will
  compile all code and build all test programs. This will also create some
  directories in your HOME,to hold the binaries/include files/libraries:
  - $(HOME)/bin/2bp
  - $(HOME)/include/2bp
  - $(HOME)/lib/2bp

  To uninstall, just type `make clean' in the root directory.
  */

#define DIM 4	///< dimension of the (planar) 2BP
#define ERR_COLLISION 1
double Hamilt(double mu, const double *x);

/**
  Two Body Problem equations (Kepler problem)

  \author Pau Roldan

  The function computes the vectorfield of Kepler's problem at a point named
  "x".

  One particle ('planet') has mass \f$ m \f$ and its position is fixed at the
  origin.
  The other particle ('satellite') has mass zero. The equations that describe
  the motion of the satellite are
  \f[ \ddot q = -\frac{\mu q}{\norm{q}^3}, \f]
  where \f$ q\in R^2 \f$ is the position of the satellite and \f$ \mu \f$ is
  the constant \f$ Gm \f$ where \f$ G \f$ is the gravitational constant and \f$
  m \f$ is the mass of the planet.

  By defining \f$ p = \dot q \f$, this equation becomes Hamiltonian with 
  Hamiltonian function
  \f[   H(q,p) = \frac{\norm{p}^2}{2} - \frac{\mu}{\norm{q}}. \f]
  The function sets the value of the vectorfield in the variable "y".
  It returns a status code (success/error).

  \param[in] t
  adimensional time at which the vectorfield is evaluated. Since this is
  an autonomous ODE (does not depend on time), this parameter is not used.

  \param[in] x[4]
  point in phase space, 4 coordinates: (q,p)=(x, y, \dot x, \dot y).

  \param[out] y[4]
  vectorfield at (t,x), 4 coordinates: d/dt(x, y, \dot x, \dot y).

  \param[in] params 
  pointer to the parameter of the system: the mass parameter "mu".

  \returns status code of the function (success/error).

  \retval GSL_SUCCESS success.

  \retval ERR_COLLISION collision singularity.
 */
int twobp(double t, const double *x, double *y, void *params);
