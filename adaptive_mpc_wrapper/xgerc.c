/*
 * xgerc.c
 *
 * Code generation for function 'xgerc'
 *
 */

/* Include files */
#include "xgerc.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void xgerc(int m, int n, double alpha1, int ix0, const double y[4],
           double A[16], int ia0)
{
  int ijA;
  int j;
  if (!(alpha1 == 0.0)) {
    int i;
    int jA;
    jA = ia0;
    i = (unsigned char)n;
    for (j = 0; j < i; j++) {
      double temp;
      temp = y[j];
      if (temp != 0.0) {
        int i1;
        temp *= alpha1;
        i1 = m + jA;
        for (ijA = jA; ijA < i1; ijA++) {
          A[ijA - 1] += A[((ix0 + ijA) - jA) - 1] * temp;
        }
      }
      jA += 4;
    }
  }
}

/* End of code generation (xgerc.c) */
