/*
   ARPACK++ v1.0 8/1/1997
   c++ interface to ARPACK code.

   MODULE LNMatrxA.h
   Function template for the 2-D Brusselator Wave model. 
*/

#ifndef LNMATRXA_H
#define LNMATRXA_H

#include <math.h>

template<class FLOAT, class INT>

void BrusselatorMatrix(FLOAT L, FLOAT delta1, FLOAT delta2, 
                       FLOAT alpha, FLOAT beta, INT n, INT& nnz,
                       FLOAT* &A, INT* &irow, INT* &pcol)

{

  // Defining internal variables.

  INT    i, j, icount;
  INT    m, m2;
  FLOAT  h, tau1, tau2;
  FLOAT  d1, d2, alpha2;

  // Defining constants.

  const FLOAT one  = 1.0;
  const FLOAT four = 4.0;

  m      = INT(sqrt(n/2));
  m2     = 2*m;
  h      = one / FLOAT(m+1);
  tau1   = delta1/(h*h*L*L);
  tau2   = delta2/(h*h*L*L);
  alpha2 = alpha*alpha;
  d1     = -tau1*four + beta - one;
  d2     = -tau2*four - alpha2;

  // Defining the number of nonzero elements of matrix.

  nnz    = 6*n-8*m;

  // Creating output vectors.

  A    = new FLOAT[nnz];
  irow = new INT[nnz];
  pcol = new INT[n+1];

  // Creating brusselator matrix.

  pcol[0] = 0;

  // First two columns.

  A[0] = d1;              irow[0] = 0; 
  A[1] = -beta;           irow[1] = 1;
  A[2] = tau1;            irow[2] = 2;
  A[3] = tau1;            irow[3] = m2;
  pcol[1] = 4;

  A[4] = alpha2;          irow[4] = 0;
  A[5] = d2;              irow[5] = 1;
  A[6] = tau2;            irow[6] = 3;
  A[7] = tau2;            irow[7] = m2+1;
  pcol[2] = 8;

  // Next 2m-2 columns.
 
  i = pcol[2];

  for (j = 2; j < m2; j += 2) {
    
    A[i] = tau1;        irow[i++] = j-2;
    A[i] = d1;          irow[i++] = j;
    A[i] = -beta;       irow[i++] = j+1;
    if (j != m2-2) {
      A[i] = tau1;      irow[i++] = j+2;
    }
    A[i] = tau1;        irow[i++] = m2+j;
    pcol[j+1] = i;

    A[i] = tau2;        irow[i++] = j-1;
    A[i] = alpha2;      irow[i++] = j;
    A[i] = d2;          irow[i++] = j+1;
    if (j != m2-2) {
      A[i] = tau2;      irow[i++] = j+3;
    }
    A[i] = tau2;        irow[i++] = m2+j+1;
    pcol[j+2] = i;

  }

  // Next n-4m columns.

  icount = 0;

  for (j = m2; j < n-m2; j += 2) {

    A[i] = tau1;        irow[i++] = j-m2;
    if (icount != 0) {
      A[i] = tau1;      irow[i++] = j-2;
    }
    A[i] = d1;          irow[i++] = j; 
    A[i] = -beta;       irow[i++] = j+1;
    if (icount != m2-2) { 
       A[i] = tau1;     irow[i++] = j+2;
    }
    A[i] = tau1;        irow[i++] = j+m2;
    pcol[j+1] = i;

    A[i] = tau2;        irow[i++] = j-m2+1;
    if (icount != 0) {
      A[i] = tau2;      irow[i++] = j-1;
    }
    A[i] = alpha2;      irow[i++] = j;
    A[i] = d2;          irow[i++] = j+1;
    if (icount != m2-2) { 
       A[i] = tau2;     irow[i++] = j+3;
    }
    A[i] = tau2;        irow[i++] = j+m2+1;
    pcol[j+2] = i;

    icount = (icount+2)%(m2);

  }
 
  // Next 2m-2 columns.
 
  for (j = n-m2; j < n-2; j += 2) {

    A[i] = tau1;        irow[i++] = j-m2;
    if (j != n-m2) {
      A[i] = tau1;      irow[i++] = j-2;
    }
    A[i] = d1;          irow[i++] = j;
    A[i] = -beta;       irow[i++] = j+1;
    A[i] = tau1;        irow[i++] = j+2;
    pcol[j+1] = i;

    A[i] = tau2;        irow[i++] = j-m2+1;
    if (j != n-m2) {
      A[i] = tau2;      irow[i++] = j-1;
    }
    A[i] = alpha2;      irow[i++] = j;
    A[i] = d2;          irow[i++] = j+1;
    A[i] = tau2;        irow[i++] = j+3;
    pcol[j+2] = i;

  }
  
  // Last two columns.  

  A[i] = tau1;          irow[i++] = n-m2-2;
  A[i] = tau1;          irow[i++] = n-4;
  A[i] = d1;            irow[i++] = n-2;
  A[i] = -beta;         irow[i++] = n-1;
  pcol[n-1] = i;

  A[i] = tau2;          irow[i++] = n-m2-1;
  A[i] = tau2;          irow[i++] = n-3;
  A[i] = alpha2;        irow[i++] = n-2;
  A[i] = d2;            irow[i++] = n-1;
  pcol[n] = i;

} // BrusselatorMatrix. 

#endif // LNMATRXA_H

