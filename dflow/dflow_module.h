/*! \file
    \brief Derivative of the flow of the Kepler problem

    $Author: roldan $
    $Date: 2013-03-26 22:18:08 $
*/

#include <2bp_module.h>	// DIM
#include <vareq_module.h>	// DIMV

/**
  Derivative of the flow of the Kepler problem

  Compute the derivative of the flow \f$ D\phi(t,x) \f$ with respect to x of
  the Kepler problem for a given time and initial condition. 
  The time $t$ may be positive or negative, allowing for forward or backward
  integration.
  This is done by numerically integrating the variational equations.
 
  \param[in] mu
     mass parameter

  \param[in] t1
     integration time 

  \param[in] x[DIM]
     Argument of the derivative, 4 coordinates: \f$ (x, y, \dot x, \dot y). \f$

  \param[out] dphi
     On return of this function, it holds the derivative \f$D\phi(t,x)\f$ with
     respect to $x$.
  
  \return
  a non-zero error code to indicate an error and 0 to indicate success.
 
  \remark
  A Runge-Kutta Prince-Dormand (8,9) method is used to solve the variational
  equations.

  \remark
  We request absolute local error 10^{-16} and relative local error 0.
  
 */

int dflow(double mu, double t1, double x[DIM], double dphi[DIMV]);
