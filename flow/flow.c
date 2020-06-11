/*! \file
    \brief Flow of the Kepler problem: main prog.

    $Author: roldan $
    $Date: 2013-03-26 22:18:08 $
*/

#include <stdio.h>
#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE
#include "flow_module.h"

/**
  Flow of the Kepler problem: main prog.

  Compute the flow $\phi(t,x)$ of the Kepler problem for a given time and
  initial condition. 
  The time $t$ may be positive or negative, allowing for forward or backward
  integration.
  The trajectory is integrated numerically.
 
  It reads the following input from stdin:
 
  - mu: mass parameter
  - t1: integration time
  - x[DIM]: initial condition, x=(x,y,\dot x,\dot y)
 
  The final point is written to stdout, in the form x=(x,y,\dot x,\dot y)
  
 */

int main( )
{
   double mu;
   double t1;			/* final time */
   double x[DIM];
   int status;

   // Input mass parameter, integration time and initial condition from stdin.
   if(scanf("%le %le %le %le %le %le", &mu, &t1, x, x+1, x+2, x+3) < 6)
   {
      perror("main: error reading input");
      exit(EXIT_FAILURE);
   }

   // Integrate trajectory numerically. 
   status=flow(mu,t1,x);
   if(status)
   {
      fprintf(stderr, "main: error integrating trajectory");
      exit(EXIT_FAILURE);
   }

   // Output final point to stdout.
   if(printf("%.15le %.15le %.15le %.15le\n", x[0], x[1], x[2], x[3])<0)
   {
      perror("main: error writting output");
      exit(EXIT_FAILURE);
   }
   exit(EXIT_SUCCESS);
}
