/*! \file
    \brief Derivative of the flow of the Kepler problem

    $Author: roldan $
    $Date: 2013-03-26 22:18:08 $
*/

#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv.h>
#include <vareq_module.h>		// vareq

int dflow(double mu, double t1, double x[DIM], double dphi[DIMV])
{
   double eps_abs = 1.e-16;     /* absolute error for local error control */
   double eps_rel = 0.0;        /* relative error for local error control */

   double t = 0.0;
   double h;    /* step size */
   double xvar[DIM+DIMV];   /* point + derivative */
   int status, i;

   // Initial condition
   for(i=0; i<DIM; i++)
      xvar[i] = x[i];

   // Initialize derivative to the identity.
   xvar[ 4]=1; xvar[ 5]=0; xvar[ 6]=0; xvar[ 7]=0;
   xvar[ 8]=0; xvar[ 9]=1; xvar[10]=0; xvar[11]=0;
   xvar[12]=0; xvar[13]=0; xvar[14]=1; xvar[15]=0;
   xvar[16]=0; xvar[17]=0; xvar[18]=0; xvar[19]=1;

   // Embedded Runge-Kutta Prince-Dormand (8,9) method.
   const gsl_odeiv_step_type *T = gsl_odeiv_step_rk8pd;
   gsl_odeiv_step *s = gsl_odeiv_step_alloc(T,DIM+DIMV);

   // Control to determine optimal step size: keep the local error on each
   // step within an absolute error of eps_abs and relative error of eps_rel
   // with respect to the solution.
   gsl_odeiv_control *c = gsl_odeiv_control_y_new(eps_abs,eps_rel);
   gsl_odeiv_evolve *e = gsl_odeiv_evolve_alloc(DIM+DIMV);

   // define system of equations (NULL = we don't provide the jacobian)
   gsl_odeiv_system sys = {vareq,NULL,DIM+DIMV,&mu};

   // Integrate trajectory numerically.
   // The time $t1$ may be positive or negative, allowing for forward or
   // backward integration.
   if(t1>=0)
   {
      // Forward integration
      h = 1.e-6;
      while (t<t1)
      {
	 status = gsl_odeiv_evolve_apply(e,c,s,&sys,&t,t1,&h,xvar);
	 if (status != GSL_SUCCESS)
	 {
	    fprintf(stderr, "dflow: error integrating variational equations");
	    return(1);
	 }
      }
   }
   else // t1<0
   {
      // Backward integration
      h = -1.e-6;
      while (t>t1)
      {
	 status = gsl_odeiv_evolve_apply(e,c,s,&sys,&t,t1,&h,xvar);
	 if (status != GSL_SUCCESS)
	 {
	    fprintf(stderr, "dflow: error integrating variational equations");
	    return(1);
	 }
      }
   }

   // Save derivative to matrix "dphi"
   for(i=0; i<DIMV; i++)
      dphi[i] = xvar[DIM+i];
   return(0);
}
