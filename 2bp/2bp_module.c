/*! \file
    \brief Two Body Problem equations (Kepler problem)

    $Author: roldan $
    $Date: 2013-03-26 22:26:03 $
*/

#include <math.h>		// sqrt
#include <assert.h>
#include <gsl/gsl_errno.h>	// GSL_SUCCESS
#include "2bp_module.h"		// ERR_COLLISION

//const double COLLISION_TOL = 1.e-12;

double Hamilt(double mu, const double *x)
{
   double q1 = x[0];
   double q2 = x[1];
   double p1 = x[2];
   double p2 = x[3];

   // auxiliary variables
   double d = sqrt(q1*q1 + q2*q2);
   double p_norm = sqrt(p1*p1 + p2*p2);

//   if(d == 0) 
//	   return ERR_COLLISION;

   return p_norm/2.0 - mu/d;
}

int twobp(double t, const double *x, double *y, void *params)
{
   double mu = *(double *)params;
   double q1 = x[0];
   double q2 = x[1];
   double p1 = x[2];
   double p2 = x[3];

   // auxiliary variables
   double d = sqrt(q1*q1 + q2*q2);

   if(d == 0) 
	   return ERR_COLLISION;

   // vector field
   y[0] = p1;	// \dot q1
   y[1] = p2;	// \dot q2
   y[2] = -mu/(d*d*d) * q1;		// \dot p1
   y[3] = -mu/(d*d*d) * q2;		// \dot p2

   // DEBUG:
   //fprintf(stderr, "%e %e %e %e %e %e\n", t, y[0], y[2], l, g, r);
   
   return GSL_SUCCESS;
}
