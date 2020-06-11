/*! \file
    \brief Flow of the Kepler problem

    $Author: roldan $
    $Date: 2013-03-26 22:18:08 $
*/

#include <2bp_module.h>	// DIM

/// dimension of the (planar) RTBP variational equations
#define DIMV 16

/**
  Flow of the Kepler problem

  Compute the flow $\phi(t,x)$ of the Kepler problem for a given time and
  initial condition. 
  The time $t$ may be positive or negative, allowing for forward or backward
  integration.
  The trajectory is integrated numerically.
 
  \param[in] mu
     mass parameter

  \param[in] t1
     integration time 

  \param[in,out] x[DIM]
     Initial condition, 4 coordinates: (x, y, \dot x, \dot y). 
     On return of this function, it holds the final point $\phi(t,x)$.
  
  \return
  a non-zero error code to indicate an error and 0 to indicate success.
  If an integration error is encountered, the function returns a non-zero
  value.
 
  \remark
  A Runge-Kutta Prince-Dormand (8,9) method is used to solve the ODE. 
  We request absolute local error 10^{-16} and relative local error 0.
  
 */

int flow(double mu, double t1, double x[DIM]);
