
/*
    This file is part of GNU APL, a free implementation of the
    ISO/IEC Standard 13751, "Programming Language APL, Extended"

    mtx Copyright (C) 2024  Dr. C. H. L. Moller

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//#include "../mtx_config.h"

#include<cmath>
#include<complex>
#include<iostream>
#include<fstream>
#include<string>
#include <vector>

#include <alloca.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

#include "Quat.hh"

#undef PACKAGE
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_URL
#undef PACKAGE_VERSION
#undef VERSION

#define R2D(r) (180.0 * (r)/M_PI)

// https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation

Quat
getEigens (Rotation *rot)
{
  // tr(M) = 2 cos(T) + 1
  // 2 cos(T) =  tr(M) - 1
  //   cos(T) = (tr(M) - 1) / 2
  //       T  = acos ((tr(M) - 1) / 2)

  double trM = 0.0;
  for (int i = 0; i < 2; i++) trM += rot->mtx[i][i];
  trM -= 1.0;
  trM /= 2.0;
  double T = acos(trM);
  fprintf(stderr, "\nT = %g\n", R2D (T));
  
  double *data =
    (double *)alloca (3 * 3 * sizeof(double));
  int i = 0;
  for (int j = 0; j < 3; j++) {
    for (int k = 0; k < 3; k++, i++) {
      data[i] = rot->mtx[j][k];
    }
  }
  
  gsl_matrix_view m = gsl_matrix_view_array (data, 3, 3);

  gsl_vector_complex *eval = gsl_vector_complex_alloc (3);
  gsl_matrix_complex *evec =
    gsl_matrix_complex_alloc (3, 3);

  gsl_eigen_nonsymmv_workspace *w = gsl_eigen_nonsymmv_alloc (3);

  gsl_eigen_nonsymmv (&m.matrix, eval, evec, w);

  gsl_eigen_nonsymmv_free (w);

  gsl_eigen_nonsymmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);

  /***
      90 ->    / 180
      60 -> 45 / 135
      45 -> 45 / 135
      30 -> 90
       0 -> 45 / 135
   ***/

  double q0 = NAN;
  double qa[3] = {NAN, NAN, NAN};
  double cosf = 1.0;
  double sinf = 1.0;
  for (int i = 0; i < 3; i++) {
    gsl_vector_complex_view evec_i = gsl_matrix_complex_column (evec, i);
    gsl_complex eval_i = gsl_vector_complex_get (eval, i);

    double realval = GSL_REAL(eval_i);
    double imagval = GSL_IMAG(eval_i);

    double m = hypot (realval, imagval);
    double p =  R2D (atan2 (imagval, realval));
    fprintf (stderr, "\n%g<%g:  ", m, p);
    //    fprintf (stderr, "\n[%g %g]:  ", realval, imagval);
    for (int j = 0; j < 3; j++) {
      gsl_complex z = gsl_vector_complex_get(&evec_i.vector, j);
      double m = hypot (GSL_REAL(z), GSL_IMAG(z)); 
      double p =  R2D (atan2 (GSL_IMAG(z), GSL_REAL(z))); 
      fprintf (stderr, "%g<%g  ", m, p);
      //      fprintf (stderr, "[%g %g]  ", GSL_REAL(z), GSL_IMAG(z)); 
    }
    fprintf (stderr, "\n\n");

    if (i == 0) {
      for (int j = 0; j < 3; j++) {
	gsl_complex z = gsl_vector_complex_get(&evec_i.vector, j);
	qa[j] = GSL_REAL(z);
      }
    }
    if (i == 1) {
      q0 = atan2 (imagval, realval);
      //      fprintf (stderr, "q0 %g %g\n", q0, R2D (q0));
      cosf = cos (q0/2.0);
      sinf = sin (q0/2.0);
    }
  }
  for (int i = 0; i < 3; i++)
    qa[i] *= sinf;
  Quat q = Quat (cosf, qa);

  return q;
}


