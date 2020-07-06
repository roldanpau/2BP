/*! \file
    \brief Derivative of the flow of the Kepler problem: main prog.

    $Author: roldan $
    $Date: 2013-03-26 22:18:08 $
*/

#include <stdio.h>
#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE
#include "dflow_module.h"

/**
  Derivative of the flow of the Kepler problem: main prog.  

  Compute the derivative of the flow \f$ D\phi(t,x) \f$ with respect to x of
  the Kepler problem for a given time and initial condition. 
  The time $t$ may be positive or negative, allowing for forward or backward
  integration.
  This is done by numerically integrating the variational equations.

  It reads the following input from stdin:
 
  - mu: mass parameter
  - t1: integration time
  - x[DIM]: Argument of the derivative, 4 coordinates: 
  \f$ (x, y, \dot x, \dot y). \f$
 
  The derivative is written to stdout, in the form of a 4-by-4 matrix.
 */

int main( )
{
   double mu;
   double t1;			/* final time */
   double x[DIM];
   double D[DIMV];	/* derivative of the flow */
   int status;

   // Input mass parameter, integration time and initial condition from stdin.
   if(scanf("%le %le %le %le %le %le", &mu, &t1, x, x+1, x+2, x+3) < 6)
   {
      perror("main: error reading input");
      exit(EXIT_FAILURE);
   }

   // Integrate variational equations numerically. 
   status=dflow(mu,t1,x,D);
   if(status)
   {
      fprintf(stderr, "main: error integrating variational equations");
      exit(EXIT_FAILURE);
   }

   // Output derivative matrix to stdout
   if( printf("%.15le %.15le %.15le %.15le\n", D[0], D[1], D[2], D[3])<0 || 
	   printf("%.15le %.15le %.15le %.15le\n", D[0], D[1], D[2], D[3])<0 || 
	   printf("%.15le %.15le %.15le %.15le\n", D[0], D[1], D[2], D[3])<0 || 
	   printf("%.15le %.15le %.15le %.15le\n", D[0], D[1], D[2], D[3])<0 )
   {
      perror("main: error writting output");
      exit(EXIT_FAILURE);
   }
   exit(EXIT_SUCCESS);
}
