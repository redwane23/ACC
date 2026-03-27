/*
 * minOrMax.c
 *
 * Code generation for function 'minOrMax'
 *
 */

/* Include files */
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Definitions */
double minimum(const double x[4])
{
  double ex;
  int b_k;
  int idx;
  if (!rtIsNaN(x[0])) {
    idx = 1;
  } else {
    int k;
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5)) {
      if (!rtIsNaN(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    ex = x[0];
  } else {
    ex = x[idx - 1];
    idx++;
    for (b_k = idx; b_k < 5; b_k++) {
      double d;
      d = x[b_k - 1];
      if (ex > d) {
        ex = d;
      }
    }
  }
  return ex;
}

/* End of code generation (minOrMax.c) */
