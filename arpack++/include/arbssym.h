/*
   ARPACK++ v1.0 8/1/1997
   c++ interface to ARPACK code.

   MODULE ARBSSym.h.
   Arpack++ class ARluSymStdEig definition
   (band matrix version).

   ARPACK Authors
      Richard Lehoucq
      Danny Sorensen
      Chao Yang
      Dept. of Computational & Applied Mathematics
      Rice University
      Houston, Texas
*/

#ifndef ARBSSYM_H
#define ARBSSYM_H

#include <stddef.h>
#include "arch.h"
#include "arssym.h"
#include "arbsmat.h"


template<class FLOAT>
class ARluSymStdEig:
  public virtual ARSymStdEig<FLOAT, ARbdSymMatrix<FLOAT> > {

 public:

 // a) Public functions:

 // a.1) Functions that allow changes in problem parameters.

  virtual void ChangeShift(FLOAT sigmaRp);

  virtual void SetRegularMode();

  virtual void SetShiftInvertMode(FLOAT sigmap);

 // a.2) Constructors and destructor.

  ARluSymStdEig() { }
  // Short constructor.

  ARluSymStdEig(int nevp, ARbdSymMatrix<FLOAT>& A,
                char* whichp = "LM", int ncvp = 0,
                FLOAT tolp = 0.0, int maxitp = 0,
                FLOAT* residp = NULL, bool ishiftp = true);
  // Long constructor (regular mode).

  ARluSymStdEig(int nevp, ARbdSymMatrix<FLOAT>& A,
                FLOAT sigma, char* whichp = "LM", int ncvp = 0,
                FLOAT tolp = 0.0, int maxitp = 0,
                FLOAT* residp = NULL, bool ishiftp = true);
  // Long constructor (shift and invert mode).

  ARluSymStdEig(const ARluSymStdEig& other) { Copy(other); }
  // Copy constructor.

  virtual ~ARluSymStdEig() { }
  // Destructor.

 // b) Operators.

  ARluSymStdEig& operator=(const ARluSymStdEig& other);
  // Assignment operator.

}; // class ARluSymStdEig.


// ------------------------------------------------------------------------ //
// ARluSymStdEig member functions definition.                               //
// ------------------------------------------------------------------------ //


template<class FLOAT>
inline void ARluSymStdEig<FLOAT>::
ChangeShift(FLOAT sigmaRp)
{

  sigmaR    = sigmaRp;
  sigmaI    = 0.0;
  mode      = 3;
  iparam[7] = mode;

  objOP->FactorAsI(sigmaR);
  Restart();

} // ChangeShift.


template<class FLOAT>
inline void ARluSymStdEig<FLOAT>::SetRegularMode()
{

  ARStdEig<FLOAT, FLOAT, ARbdSymMatrix<FLOAT> >::
    SetRegularMode(objOP, &ARbdSymMatrix<FLOAT>::MultMv);

} // SetRegularMode.


template<class FLOAT>
inline void ARluSymStdEig<FLOAT>::SetShiftInvertMode(FLOAT sigmap)
{

  ARStdEig<FLOAT, FLOAT, ARbdSymMatrix<FLOAT> >::
    SetShiftInvertMode(sigmap, objOP, &ARbdSymMatrix<FLOAT>::MultInvv);

} // SetShiftInvertMode.


template<class FLOAT>
inline ARluSymStdEig<FLOAT>::
ARluSymStdEig(int nevp, ARbdSymMatrix<FLOAT>& A,
              char* whichp, int ncvp, FLOAT tolp,
              int maxitp, FLOAT* residp, bool ishiftp)
{

  NoShift();
  DefineParameters(A.ncols(), nevp, &A, ARbdSymMatrix<FLOAT>::MultMv,
                   whichp, ncvp, tolp, maxitp, residp, ishiftp);

} // Long constructor (regular mode).


template<class FLOAT>
inline ARluSymStdEig<FLOAT>::
ARluSymStdEig(int nevp, ARbdSymMatrix<FLOAT>& A,
              FLOAT sigmap, char* whichp, int ncvp, FLOAT tolp,
              int maxitp, FLOAT* residp, bool ishiftp)

{

  DefineParameters(A.ncols(), nevp, &A, &ARbdSymMatrix<FLOAT>::MultInvv,
                   whichp, ncvp, tolp, maxitp, residp, ishiftp);
  ChangeShift(sigmap);

} // Long constructor (shift and invert mode).


template<class FLOAT>
ARluSymStdEig<FLOAT>& ARluSymStdEig<FLOAT>::
operator=(const ARluSymStdEig<FLOAT>& other)
{

  if (this != &other) { // Stroustrup suggestion.
    ClearMem();
    Copy(other);
  }
  return *this;

} // operator=.


#endif // ARBSSYM_H

