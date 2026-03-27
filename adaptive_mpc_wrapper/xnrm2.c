/*
 * xnrm2.c
 *
 * Code generation for function 'xnrm2'
 *
 */

/* Include files */
#include "xnrm2.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
double xnrm2(int n, const double x[16], int ix0)
{
  double y;
  int k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      double scale;
      int kend;
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        double absxk;
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          double t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          double t;
          t = absxk / scale;
          y += t * t;
        }
      }
      y = scale * sqrt(y);
      if (rtIsNaN(y)) {
        int b_k;
        b_k = ix0;
        int exitg1;
        do {
          exitg1 = 0;
          if (b_k <= kend) {
            if (rtIsNaN(x[b_k - 1])) {
              exitg1 = 1;
            } else {
              b_k++;
            }
          } else {
            y = rtInf;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
    }
  }
  return y;
}

/* End of code generation (xnrm2.c) */
