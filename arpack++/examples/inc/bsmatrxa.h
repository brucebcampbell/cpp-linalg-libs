/*
   ARPACK++ v1.0 8/1/1997
   c++ interface to ARPACK code.

   MODULE BSMatrxA.h
   Function template for the matrix

                          | T -I          |
                          |-I  T -I       |
                      A = |   -I  T       |
                          |        ...  -I|
                          |           -I T|

   derived from the standard central difference discretization of the
   2-dimensional Laplacian on the unit square with zero Dirichlet 
   boundary conditions.

   Matrix A is generated in symmetric band format, which means that
   only the main diagonal and the lower or the upper band of the 
   matrix are stored.

   ARPACK Authors
      Richard Lehoucq
      Danny Sorensen
      Chao Yang
      Dept. of Computational & Applied Mathematics
      Rice University
      Houston, Texas
*/

#ifndef BSMATRXA_H
#define BSMATRXA_H

#include <math.h>

template<class FLOAT, class INT>
void BandMatrixA(INT nx, INT& n, INT& nD, FLOAT* &A, char uplo='L')

{

  // Defining internal variables.

  INT    i, j, lda;
  FLOAT  h2, df, dd;

  // Defining constants.

  h2  = 1.0/(FLOAT(nx+1)*FLOAT(nx+1));
  dd  = 4.0/h2;
  df  = -1.0/h2;

  // Defining the number of columns and the upper or the lower bandwidth.

  n   = nx*nx;
  nD  = nx;

  // Creating output vector A.

  lda = nD+1;
  A   = new FLOAT[n*lda];

  // Filling A with zeros.

  for (j=0; j<(n*lda); j++ ) A[j] = (FLOAT)0.0;

  // Creating matrix A.

  if (uplo == 'L') {

    for (i=0, j=0; i<n; i++, j+=lda) {
      A[j] = dd;
      if ((i+1)%nx)  A[j+1]  = df;
      if (i<(n-nx))  A[j+nx] = df;
    }

  }
  else {

    for (i=0, j=nD; i<n; i++, j+=lda) {
      if (i>=nx) A[j-nx] = df;
      if (i%nx)  A[j-1]  = df;
      A[j] = dd;
    }

  }
    
} // BandMatrixA.

#endif // BSMATRXA_H

