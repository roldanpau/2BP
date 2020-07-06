/*! \file
    \brief Two Body Problem variational equations (Kepler problem)

    $Author: roldan $
    $Date: 2013-03-26 22:26:03 $
*/

#include <math.h>		// sqrt
#include <assert.h>
#include <gsl/gsl_errno.h>	// GSL_SUCCESS
#include <gsl/gsl_matrix.h>	
#include <gsl/gsl_blas.h>	// gsl_blas_dgemm
#include "2bp_module.h"		// DIM, ERR_COLLISION

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

int vareq(double t, const double *x, double *y, void *params)
{
   double mu = *(double *)params;
   double q1 = x[0];
   double q2 = x[1];
   double p1 = x[2];
   double p2 = x[3];

   // auxiliary variables
   int i,j;

   // auxiliary variables
   double d = sqrt(q1*q1 + q2*q2);
   double d2 = d*d;
   double d3 = d*d*d;
   double d5 = d*d*d*d*d;

   if(d == 0) 
	   return ERR_COLLISION;

   // vector field
   y[0] = p1;	// \dot q1
   y[1] = p2;	// \dot q2
   y[2] = -mu/d3 * q1;		// \dot p1
   y[3] = -mu/d3 * q2;		// \dot p2

   
   double f31 = -mu*(d2-3*q1*q1)/d5;	// \pd{f_3}{q_1}
   double f32 = 3*mu*q1*q2/d5;			// \pd{f_3}{q_2}
   double f41 = f32;					// \pd{f_4}{q_1}
   double f42 = -mu*(d2-3*q2*q2)/d5;	// \pd{f_4}{q_2}

   // Jacobian D_x F
   gsl_matrix * J = gsl_matrix_alloc (DIM, DIM);
   gsl_matrix_set (J, 0, 0, 0.0);
   gsl_matrix_set (J, 0, 1, 0.0);
   gsl_matrix_set (J, 0, 2, 1.0);
   gsl_matrix_set (J, 0, 3, 0.0);
   gsl_matrix_set (J, 1, 0, 0.0);
   gsl_matrix_set (J, 1, 1, 0.0);
   gsl_matrix_set (J, 1, 2, 0.0);
   gsl_matrix_set (J, 1, 3, 1.0);
   gsl_matrix_set (J, 2, 0, f31);
   gsl_matrix_set (J, 2, 1, f32);
   gsl_matrix_set (J, 2, 2, 0.0);
   gsl_matrix_set (J, 2, 3, 0.0);
   gsl_matrix_set (J, 3, 0, f41);
   gsl_matrix_set (J, 3, 1, f42);
   gsl_matrix_set (J, 3, 2, 0.0);
   gsl_matrix_set (J, 3, 3, 0.0);

   // matrix of variations [ \delta_{ij} ]
   gsl_matrix_const_view variations = 
	   gsl_matrix_const_view_array(&(x[DIM]), DIM, DIM);

   // RHS of variational equations: D_x F * [variations]
   gsl_matrix_view Y = gsl_matrix_view_array(&(y[DIM]), DIM, DIM); 
   gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, J, &variations.matrix,
		   0.0, &Y.matrix);
   
   return GSL_SUCCESS;
}
