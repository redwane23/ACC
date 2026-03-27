/*
 * norm.c
 *
 * Code generation for function 'norm'
 *
 */

/* Include files */
#include "norm.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
double b_norm(const double x[4])
{
  double absxk;
  double scale;
  double t;
  double y;
  boolean_T b;
  scale = 3.3121686421112381E-170;
  absxk = fabs(x[0]);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }
  absxk = fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }
  absxk = fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }
  absxk = fabs(x[3]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }
  y = scale * sqrt(y);
  b = rtIsNaN(y);
  if (b) {
    int k;
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k < 4) {
        if (rtIsNaN(x[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        y = rtInf;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return y;
}

/* End of code generation (norm.c) */
