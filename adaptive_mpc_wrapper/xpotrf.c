/*
 * xpotrf.c
 *
 * Code generation for function 'xpotrf'
 *
 */

/* Include files */
#include "xpotrf.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>

/* Function Definitions */
int xpotrf(double A[16])
{
  int iac;
  int info;
  int j;
  int k;
  boolean_T exitg1;
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j < 4)) {
    double c;
    double ssq;
    int idxAjj;
    idxAjj = j + (j << 2);
    ssq = 0.0;
    if (j >= 1) {
      for (k = 0; k < j; k++) {
        c = A[j + (k << 2)];
        ssq += c * c;
      }
    }
    ssq = A[idxAjj] - ssq;
    if (ssq > 0.0) {
      ssq = sqrt(ssq);
      A[idxAjj] = ssq;
      if (j + 1 < 4) {
        int c_tmp;
        int ia0;
        int idxAjp1j;
        int scalarLB;
        int vectorUB;
        ia0 = j + 2;
        idxAjp1j = idxAjj + 2;
        if (j != 0) {
          int i;
          i = (j + ((j - 1) << 2)) + 2;
          for (iac = ia0; iac <= i; iac += 4) {
            c_tmp = iac - j;
            c = -A[j + (((c_tmp - 2) >> 2) << 2)];
            scalarLB = c_tmp + 2;
            for (k = iac; k <= scalarLB; k++) {
              vectorUB = ((idxAjj + k) - iac) + 1;
              A[vectorUB] += A[k - 1] * c;
            }
          }
        }
        ssq = 1.0 / ssq;
        c_tmp = (idxAjj - j) + 4;
        scalarLB = ((c_tmp - idxAjp1j) + 1) / 2 * 2 + idxAjp1j;
        vectorUB = scalarLB - 2;
        for (k = idxAjp1j; k <= vectorUB; k += 2) {
          __m128d r;
          r = _mm_loadu_pd(&A[k - 1]);
          r = _mm_mul_pd(_mm_set1_pd(ssq), r);
          _mm_storeu_pd(&A[k - 1], r);
        }
        for (k = scalarLB; k <= c_tmp; k++) {
          A[k - 1] *= ssq;
        }
      }
      j++;
    } else {
      A[idxAjj] = ssq;
      info = j + 1;
      exitg1 = true;
    }
  }
  return info;
}

/* End of code generation (xpotrf.c) */
