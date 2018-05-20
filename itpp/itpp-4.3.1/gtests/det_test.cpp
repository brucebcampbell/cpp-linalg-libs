/*!
 * \file
 * \brief Determinant routines test program
 * \author Tony Ottosson and Adam Piatyszek
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 1995-2012  (see AUTHORS file for a list of contributors)
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

#include <itpp/itstat.h>
#include "gtest/gtest.h"

using namespace itpp;

TEST(Det, All)
{
  const double eps = 1e-14;
  int i,j;

  {
    //Real matrix
    RNG_reset(0);
    mat X = randn(5, 5);
    mat X_expect = "-0.53867916598526822 -0.8784344572039396 -0.5319684156366868 -1.2762774231089256 0.3825268969473976; "
                   "-1.2749137275918296 1.290111844695397 -3.7326992066642575 0.3873527275026688 -0.61039461776231596; "
                   "1.0282326809755016 -0.67538252183750369 -0.1127551468065689 -0.38752244901288929 0.34978316627410816; "
                   "-0.12769391261256544 -0.70127933871039161 -0.94014676063834202 0.014601505447491007 1.296765364185652; "
                   "-0.36545017988288314 0.8109093563933464 0.24924688123208288 0.8757911319502223 -0.1954802954379749";
    for (i = 0; i < X.rows(); ++i) {
      for (j = 0; j < X.cols(); ++j) {
        ASSERT_NEAR(X_expect(i,j), X(i,j), eps) << i << "x" <<j;
      }
    }
    ASSERT_NEAR(0.66839836915094319, det(X), eps);
    X = randn(5, 5);
    X_expect = "-0.4666178935859201 0.6790123468142621 -0.1506573640358516 -1.4360879893536755 0.4030712283482284; "
              "0.6408133401112543 0.05873344803854057 -0.6416139139672489 -0.1482778381797205 1.288501360291362; "
              "1.4474891816308055 0.5489595758126958 0.891211050120127 0.1682537210323091 1.97906140519714; "
              "0.5851355400297025 1.2829179929933634 -0.5092715284656911 2.253018410970866 1.144800467126237; "
              "0.2543632831435936 -1.4664575603599146 -1.752607448846632 1.144350801849226 -0.8485065927711128";
    for (i = 0; i < X.rows(); ++i) {
      for (j = 0; j < X.cols(); ++j) {
        ASSERT_NEAR(X_expect(i,j), X(i,j), eps) << i << "x" <<j;
      }
    }
    ASSERT_NEAR(3.0077725055851996, det(X), eps);
  }

  {
    //Complex matrix
    RNG_reset(0);
    cmat X = randn_c(5, 5);
    cmat X_expect = "-0.3809036911520969-0.9015001422080015i -0.3761584740737651-2.6394169211619425i 0.2704873628177524-0.4316141734195043i "
    "0.4801342349417566+0.04153081939051976i -1.015467555652538-0.1048482648765619i; "
    "0.7270703013554011-0.09029323152458742i -0.07972992892060955-0.6647841497579375i 0.2473340488173235+0.9169515826235172i "
    "0.3881730386544478+0.9071600125518429i 0.1189733471018154+1.593124596535639i; "
    "-0.2584123003810302-0.6211469615168297i 0.1762441599088038-0.9024644205556137i -0.1382254424925418-0.3299486767775869i "
    "-1.0369420852527764-0.106530843745441i 0.809178212043851+0.2850143988662237i; "
    "0.9122468338732012-0.4775675610861703i 0.273899740328242-0.2740197515590321i 0.4531234582674694+1.0235294160253086i "
    "-0.4536895494698837+0.6301813770083259i 0.911108049430113+1.399407739999475i; "
    "-0.4958793759081356+0.573399504833354i 0.0103248235174532+0.6192778483050445i 0.4137533082682551+0.1798620023957089i "
    "-0.360109351243328-1.2392806118375086i 0.8094961734104893-0.5999847656299462i";
    for (i = 0; i < X.rows(); ++i) {
      for (j = 0; j < X.cols(); ++j) {
        ASSERT_NEAR(X_expect(i,j).real(), X(i,j).real(), eps) << i << "x" <<j;
        ASSERT_NEAR(X_expect(i,j).imag(), X(i,j).imag(), eps) << i << "x" <<j;
      }
    }
    std::complex<double> d = det(X);
    ASSERT_NEAR(-6.1046669217012699, d.real(), eps);
    ASSERT_NEAR(1.4975632311302132, d.imag(), eps);

    X = randn_c(5, 5);
    X_expect = "-0.8696275831109568+0.7570043306871584i -0.6238632012662513+0.04914321647156545i 0.03429401822619-0.5558754225740515i "
    "0.1666364451082585+0.4007317486458041i -0.5893392184430184+0.1674181706465156i; "
    "0.7287475585975989-0.1326379358269829i -1.10390652648413-0.9635435410370933i -0.2154901642550677-0.7622797901336434i "
    "0.1344928439490188+0.9887947312211245i -0.6116368553547598-0.04220192308753814i; "
    "0.3229109080077305+0.648281980978702i 1.580133781005509+0.4497496320949741i 0.4460947554352002-0.7594798687045069i "
    "0.1667005240265463-1.309249975681504i -0.2730774606391793-0.9649958584432418i; "
    "0.5393189597808304-1.698775822486131i -1.340916266239779+0.1034133351433764i 0.04215845908992501+0.4537234814943746i "
    "-1.3548706130263835+0.8596469645054249i 0.3249565584899411+0.3836772302093931i; "
    "0.8257068048973116-0.3091289715393962i 0.3939126587361242+0.6689829815540316i -0.1218813738886838-0.5598128607210444i "
    "-1.047042745257851-0.1636197700545179i 0.4042670413266145-0.4705694687533109i";
    for (i = 0; i < X.rows(); ++i) {
      for (j = 0; j < X.cols(); ++j) {
        ASSERT_NEAR(X_expect(i,j).real(), X(i,j).real(), eps) << i << "x" <<j;
        ASSERT_NEAR(X_expect(i,j).imag(), X(i,j).imag(), eps) << i << "x" <<j;
      }
    }
    d = det(X);
    ASSERT_NEAR(2.8403149701685253, d.real(), eps);
    ASSERT_NEAR(4.4243483627459055, d.imag(), eps);
  }
}
