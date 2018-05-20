/*!
 * \file
 * \brief Frequency filter test program
 * \author Simon Wood and Adam Piatyszek
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 1995-2013  (see AUTHORS file for a list of contributors)
 *
 * This file is part of IT++ - a C++ library of mathematical, signal
 * processing, speech processing, and communications classes and functions.
 *
 * IT++ is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * IT++ is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along
 * with IT++.  If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#include <itpp/itsignal.h>
#include "gtest/gtest.h"

using namespace itpp;
using namespace std;


TEST (FreqFilt, All)
{
  static const double eps = 1e-4;
  int i;

  vec b = "1 2 3 4";
  vec x(20);
  x.zeros();
  x(0) = 1;

  // Define a filter object for doubles
  Freq_Filt<double> FF(b, x.length());

  // Filter the data
  vec y = FF.filter(x);

  // Check the FFT and block sizes that were used
  int fftsize = FF.get_fft_size();
  int blksize = FF.get_blk_size();
  ASSERT_EQ(8, fftsize);
  ASSERT_EQ(5, blksize);

  vec y_ref = "1 2 3 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
  for (i = 0; i < y.length(); ++i) {
    ASSERT_NEAR(y_ref[i], y[i], eps);
  }

  // Test streaming mode
  x = linspace(0, 10, 100);
  Freq_Filt<double> FFS(b, x.length());
  vec y1 = FFS.filter(x(0, 49), 1);
  vec y2 = FFS.filter(x(50, 99), 1);
  vec conc = concat(y1, y2);
  vec conc_ref = "0 0.10101 0.40404 1.0101 2.0202 3.0303 4.0404 5.05051 6.06061 7.07071 8.08081 9.09091 "
  "10.101 11.1111 12.1212 13.1313 14.1414 15.1515 16.1616 17.1717 18.1818 19.1919 20.202 21.2121 22.2222 "
  "23.2323 24.2424 25.2525 26.2626 27.2727 28.2828 29.2929 30.303 31.3131 32.3232 33.3333 34.3434 35.3535 "
  "36.3636 37.3737 38.3838 39.3939 40.404 41.4141 42.4242 43.4343 44.4444 45.4545 46.4646 47.4747 48.4848 "
  "49.4949 50.5051 51.5152 52.5253 53.5354 54.5455 55.5556 56.5657 57.5758 58.5859 59.596 60.6061 61.6162 "
  "62.6263 63.6364 64.6465 65.6566 66.6667 67.6768 68.6869 69.697 70.7071 71.7172 72.7273 73.7374 74.7475 "
  "75.7576 76.7677 77.7778 78.7879 79.798 80.8081 81.8182 82.8283 83.8384 84.8485 85.8586 86.8687 87.8788 "
  "88.8889 89.899 90.9091 91.9192 92.9293 93.9394 94.9495 95.9596 96.9697 97.9798";
  for (i = 0; i < conc_ref.length(); ++i) {
    ASSERT_NEAR(conc_ref[i], conc[i], eps);
  }
}
