// ===============================================================
// Two Body Problem equations (Kepler problem)
// ===============================================================
// FILE:          2bp.c
// AUTHOR:        Pau Roldan
//                All code is my own except where credited to others.
// DATE:          September 30, 2009
//
// PURPOSE:
//    The program computes the vectorfield of the 2BP at a point named "x".
//
// It reads the following input from stdin:
//
// - mu: mass parameter
// - x[DIM]: point in phase space, 4 coordinates: (x, y, \dot x, \dot  y)
//
// The vectorfield at (t,x) is written to stdout, 4 coordinates: d/dt(x, y,
// \dot x, \dot y).
//
// NOTES:
//
// OVERALL METHOD:
// The list of general tasks is:
// 1. Input mass parameter and point from stdin.
// 2. Compute vectorfield
// 3. Otput vectorfield to stdout.
//
// FUNCTIONS:

#include <stdio.h>
#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE
#include <gsl/gsl_matrix.h>
#include "vareq_module.h"

int main( )
{
   double mu;
   double x[DIM];
   double y[DIM];
   int status;

   // Input mass parameter, and phase space point from stdin.
   if(scanf("%le %le %le %le %le", &mu, x, x+1, x+2, x+3) < 5)
   {
      perror("main: error reading input");
      exit(EXIT_FAILURE);
   }

   // Initialize variations to identity
   gsl_matrix_view X = gsl_matrix_view_array(&(x[DIM]), DIM, DIM);
   gsl_matrix_set_identity(&X.matrix);

   // Compute RHS of variational equations:
   status=vareq(0.0,x,y,&mu);
   if(status)
   {
      fprintf(stderr, "main: error computing variational equations");
      exit(EXIT_FAILURE);
   }

   // Output RHS to stdout.
   gsl_matrix_view Y = gsl_matrix_view_array(y, 1+DIM, DIM);
   gsl_matrix_fprintf(stdout, &Y.matrix, "%f");

   exit(EXIT_SUCCESS);
}
