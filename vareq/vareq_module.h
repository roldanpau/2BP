/*! \file
    \brief Two Body Problem variational equations (Kepler Problem).

    $Author: roldan $
    $Date: 2013-03-26 22:26:03 $
*/

#include <2bp_module.h>	// DIM, ERR_COLLISION

#define DIMV 16 ///< dimension of the 2BP variational equations

/**
  Two Body Problem variational equations (Kepler problem)

  \author Pau Roldan

  The function computes the variational equations of Kepler's problem at a
  point named "x".

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

  \param[in] xvar[DIM+DIMV]
  phase space point x (4 coords) + variations var (16)

  \param[out] yvar[DIM+DIMV]
  right-hand side of the variational equations:
  vectorfield at (t,x), 4 coordinates: d/dt(x, y, \dot x, \dot y) + 
  D_x F \times var, where D_x F is the Jacobian of the system.


  \param[in] params 
  pointer to the parameter of the system: the mass parameter "mu".

  \returns status code of the function (success/error).

  \retval GSL_SUCCESS success.

  \retval ERR_COLLISION collision singularity.
 */
int vareq(double t, const double *x, double *y, void *params);
