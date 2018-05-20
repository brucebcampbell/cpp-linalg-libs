
#ifndef _testfftunit_h
#define _testfftunit_h

#include "ap.h"
#include "ialglib.h"

#include "ftbase.h"
#include "fft.h"


/*************************************************************************
Test
*************************************************************************/
bool testfft(bool silent);


/*************************************************************************
Silent unit test
*************************************************************************/
bool testfftunit_test_silent();


/*************************************************************************
Unit test
*************************************************************************/
bool testfftunit_test();


#endif

