/*
 * xgemv.c
 *
 * Code generation for function 'xgemv'
 *
 */

/* Include files */
#include "xgemv.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void xgemv(int m, int n, const double A[16], int ia0, const double x[16],
           int ix0, double y[4])
{
  int ia;
  int iac;
  if (n != 0) {
    int i;
    int i1;
    i = (unsigned char)n;
    memset(&y[0], 0, (unsigned int)i * sizeof(double));
    i1 = ia0 + ((n - 1) << 2);
    for (iac = ia0; iac <= i1; iac += 4) {
      double c;
      c = 0.0;
      i = iac + m;
      for (ia = iac; ia < i; ia++) {
        c += A[ia - 1] * x[((ix0 + ia) - iac) - 1];
      }
      i = (iac - ia0) >> 2;
      y[i] += c;
    }
  }
}

/* End of code generation (xgemv.c) */
