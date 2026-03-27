/*
 * trisolve.c
 *
 * Code generation for function 'trisolve'
 *
 */

/* Include files */
#include "trisolve.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void trisolve(const double A[16], double B[16])
{
  int b_i;
  int j;
  int k;
  for (j = 0; j < 4; j++) {
    int jBcol;
    jBcol = (j << 2) - 1;
    for (k = 0; k < 4; k++) {
      double d;
      int i;
      int kAcol;
      kAcol = (k << 2) - 1;
      i = (k + jBcol) + 1;
      d = B[i];
      if (d != 0.0) {
        int i1;
        B[i] = d / A[(k + kAcol) + 1];
        i1 = k + 2;
        for (b_i = i1; b_i < 5; b_i++) {
          int i2;
          i2 = b_i + jBcol;
          B[i2] -= B[i] * A[b_i + kAcol];
        }
      }
    }
  }
}

/* End of code generation (trisolve.c) */
