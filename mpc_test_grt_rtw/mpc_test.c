/*
 * mpc_test.c
 *
 * Code generation for model "mpc_test".
 *
 * Model version              : 1.11
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Wed Mar 11 21:00:25 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "mpc_test.h"
#include "rtwtypes.h"
#include <string.h>
#include <emmintrin.h>
#include <math.h>
#include "rt_nonfinite.h"
#include "mpc_test_private.h"

/* Named constants for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
#define mpc_test_Wdu                   (2.25)
#define mpc_test_Wu                    (0.010000000000000002)
#define mpc_test_degrees               (5)
#define mpc_test_p                     (20)
#define mpc_test_uoff                  (0.0)

/* Block signals (default storage) */
B_mpc_test_T mpc_test_B;

/* Block states (default storage) */
DW_mpc_test_T mpc_test_DW;

/* External inputs (root inport signals with default storage) */
ExtU_mpc_test_T mpc_test_U;

/* Real-time model */
static RT_MODEL_mpc_test_T mpc_test_M_;
RT_MODEL_mpc_test_T *const mpc_test_M = &mpc_test_M_;

/* Forward declaration for local functions */
static int32_T mpc_test_xpotrf(real_T b_A[25]);
static real_T mpc_test_minimum(const real_T x[5]);
static void mpc_test_trisolve(const real_T b_A[25], real_T b_B[25]);
static real_T mpc_test_norm(const real_T x[5]);
static real_T mpc_test_maximum(const real_T x[5]);
static real_T mpc_test_xnrm2(int32_T n, const real_T x[25], int32_T ix0);
static void mpc_test_xgemv(int32_T b_m, int32_T n, const real_T b_A[25], int32_T
  ia0, const real_T x[25], int32_T ix0, real_T y[5]);
static void mpc_test_xgerc(int32_T b_m, int32_T n, real_T alpha1, int32_T ix0,
  const real_T y[5], real_T b_A[25], int32_T ia0);
static real_T mpc_test_KWIKfactor(const real_T b_Ac[40], const int32_T iC[8],
  int32_T nA, const real_T b_Linv[25], real_T RLinv[25], real_T b_D[25], real_T
  b_H[25], int32_T n);
static void mpc_test_DropConstraint(int32_T kDrop, boolean_T iA[8], int32_T *nA,
  int32_T iC[8]);
static void mpc_test_qpkwik(const real_T b_Linv[25], const real_T b_Hinv[25],
  const real_T f[5], const real_T b_Ac[40], const real_T b[8], boolean_T iA[8],
  int32_T maxiter, real_T FeasTol, real_T x[5], real_T lambda[8], int32_T
  *status);
static void mpc_test_mpcblock_optimizer(const real_T rseq[40], const real_T
  vseq[21], const real_T x[4], real_T old_u, const boolean_T iA[8], const real_T
  b_Mlim[8], real_T b_Mx[32], real_T b_Mu1[8], real_T b_Mv[168], const real_T
  b_utarget[20], real_T b_uoff, real_T b_H[25], real_T b_Ac[40], const real_T
  b_Wy[2], const real_T b_Jm[80], const real_T b_I1[20], const real_T b_A[16],
  const real_T Bu[84], const real_T Bv[84], const real_T b_C[8], const real_T
  Dv[42], const int32_T b_Mrows[8], real_T *u, real_T useq[21], real_T *status,
  boolean_T iAout[8]);
int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static int32_T mpc_test_xpotrf(real_T b_A[25])
{
  int32_T b_k;
  int32_T info;
  int32_T j;
  int32_T jm1;
  boolean_T exitg1;
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j < 5)) {
    real_T c;
    real_T ssq;
    int32_T idxAjj;
    idxAjj = j * 5 + j;
    ssq = 0.0;
    if (j >= 1) {
      for (b_k = 0; b_k < j; b_k++) {
        c = b_A[b_k * 5 + j];
        ssq += c * c;
      }
    }

    ssq = b_A[idxAjj] - ssq;
    if (ssq > 0.0) {
      ssq = sqrt(ssq);
      b_A[idxAjj] = ssq;
      if (j + 1 < 5) {
        int32_T b_iy;
        int32_T d;
        if (j != 0) {
          b_iy = ((j - 1) * 5 + j) + 2;
          for (b_k = j + 2; b_k <= b_iy; b_k += 5) {
            jm1 = b_k - j;
            c = -b_A[div_nde_s32_floor(jm1 - 2, 5) * 5 + j];
            d = jm1 + 3;
            for (jm1 = b_k; jm1 <= d; jm1++) {
              int32_T tmp_0;
              tmp_0 = ((idxAjj + jm1) - b_k) + 1;
              b_A[tmp_0] += b_A[jm1 - 1] * c;
            }
          }
        }

        ssq = 1.0 / ssq;
        jm1 = (idxAjj - j) + 5;
        b_iy = (((((jm1 - idxAjj) - 1) / 2) << 1) + idxAjj) + 2;
        d = b_iy - 2;
        for (b_k = idxAjj + 2; b_k <= d; b_k += 2) {
          __m128d tmp;
          tmp = _mm_loadu_pd(&b_A[b_k - 1]);
          _mm_storeu_pd(&b_A[b_k - 1], _mm_mul_pd(tmp, _mm_set1_pd(ssq)));
        }

        for (b_k = b_iy; b_k <= jm1; b_k++) {
          b_A[b_k - 1] *= ssq;
        }
      }

      j++;
    } else {
      b_A[idxAjj] = ssq;
      info = j + 1;
      exitg1 = true;
    }
  }

  return info;
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static real_T mpc_test_minimum(const real_T x[5])
{
  real_T ex;
  int32_T idx;
  int32_T k;
  if (!rtIsNaN(x[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 6)) {
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
    for (k = idx + 1; k < 6; k++) {
      real_T x_0;
      x_0 = x[k - 1];
      if (ex > x_0) {
        ex = x_0;
      }
    }
  }

  return ex;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static void mpc_test_trisolve(const real_T b_A[25], real_T b_B[25])
{
  int32_T b_k;
  int32_T i;
  int32_T j;
  for (j = 0; j < 5; j++) {
    int32_T jBcol;
    jBcol = 5 * j;
    for (b_k = 0; b_k < 5; b_k++) {
      real_T b_B_0;
      int32_T b_B_tmp;
      int32_T kAcol;
      kAcol = 5 * b_k;
      b_B_tmp = b_k + jBcol;
      b_B_0 = b_B[b_B_tmp];
      if (b_B_0 != 0.0) {
        b_B[b_B_tmp] = b_B_0 / b_A[b_k + kAcol];
        for (i = b_k + 2; i < 6; i++) {
          int32_T tmp;
          tmp = (i + jBcol) - 1;
          b_B[tmp] -= b_A[(i + kAcol) - 1] * b_B[b_B_tmp];
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static real_T mpc_test_norm(const real_T x[5])
{
  real_T scale;
  real_T y;
  int32_T k;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  for (k = 0; k < 5; k++) {
    real_T absxk;
    absxk = fabs(x[k]);
    if (absxk > scale) {
      real_T t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      real_T t;
      t = absxk / scale;
      y += t * t;
    }
  }

  y = scale * sqrt(y);
  if (rtIsNaN(y)) {
    k = 0;
    int32_T exitg1;
    do {
      exitg1 = 0;
      if (k < 5) {
        if (rtIsNaN(x[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        y = (rtInf);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return y;
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static real_T mpc_test_maximum(const real_T x[5])
{
  real_T ex;
  int32_T idx;
  int32_T k;
  if (!rtIsNaN(x[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 6)) {
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
    for (k = idx + 1; k < 6; k++) {
      real_T x_0;
      x_0 = x[k - 1];
      if (ex < x_0) {
        ex = x_0;
      }
    }
  }

  return ex;
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static real_T mpc_test_xnrm2(int32_T n, const real_T x[25], int32_T ix0)
{
  real_T y;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      real_T scale;
      int32_T kend;
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        real_T absxk;
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
      if (rtIsNaN(y)) {
        k = ix0;
        int32_T exitg1;
        do {
          exitg1 = 0;
          if (k <= kend) {
            if (rtIsNaN(x[k - 1])) {
              exitg1 = 1;
            } else {
              k++;
            }
          } else {
            y = (rtInf);
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
    }
  }

  return y;
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T a;
  real_T b;
  real_T y;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = sqrt(a * a + 1.0) * b;
  } else if (a > b) {
    b /= a;
    y = sqrt(b * b + 1.0) * a;
  } else if (rtIsNaN(b)) {
    y = (rtNaN);
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static void mpc_test_xgemv(int32_T b_m, int32_T n, const real_T b_A[25], int32_T
  ia0, const real_T x[25], int32_T ix0, real_T y[5])
{
  int32_T b_iy;
  int32_T ia;
  if ((b_m != 0) && (n != 0)) {
    int32_T b;
    if (n - 1 >= 0) {
      memset(&y[0], 0, (uint32_T)n * sizeof(real_T));
    }

    b = (n - 1) * 5 + ia0;
    for (b_iy = ia0; b_iy <= b; b_iy += 5) {
      real_T c;
      int32_T d;
      c = 0.0;
      d = b_iy + b_m;
      for (ia = b_iy; ia < d; ia++) {
        c += x[((ix0 + ia) - b_iy) - 1] * b_A[ia - 1];
      }

      ia = div_nde_s32_floor(b_iy - ia0, 5);
      y[ia] += c;
    }
  }
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static void mpc_test_xgerc(int32_T b_m, int32_T n, real_T alpha1, int32_T ix0,
  const real_T y[5], real_T b_A[25], int32_T ia0)
{
  int32_T ijA;
  int32_T j;
  if (!(alpha1 == 0.0)) {
    int32_T jA;
    jA = ia0;
    for (j = 0; j < n; j++) {
      real_T temp;
      temp = y[j];
      if (temp != 0.0) {
        int32_T b;
        temp *= alpha1;
        b = b_m + jA;
        for (ijA = jA; ijA < b; ijA++) {
          b_A[ijA - 1] += b_A[((ix0 + ijA) - jA) - 1] * temp;
        }
      }

      jA += 5;
    }
  }
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static real_T mpc_test_KWIKfactor(const real_T b_Ac[40], const int32_T iC[8],
  int32_T nA, const real_T b_Linv[25], real_T RLinv[25], real_T b_D[25], real_T
  b_H[25], int32_T n)
{
  __m128d tmp;
  real_T R[25];
  real_T TL[25];
  real_T b_A[25];
  real_T tau[5];
  real_T work[5];
  real_T Status;
  real_T atmp;
  real_T b_A_0;
  real_T xnorm;
  int32_T b_coltop;
  int32_T b_lastv;
  int32_T coltop;
  int32_T exitg1;
  int32_T ii;
  int32_T k_i;
  int32_T knt;
  int32_T scalarLB;
  int32_T vectorUB;
  boolean_T exitg2;
  Status = 1.0;
  memset(&RLinv[0], 0, 25U * sizeof(real_T));
  for (k_i = 0; k_i < nA; k_i++) {
    b_lastv = iC[k_i];
    for (b_coltop = 0; b_coltop < 5; b_coltop++) {
      RLinv[b_coltop + 5 * k_i] = 0.0;
    }

    for (b_coltop = 0; b_coltop < 5; b_coltop++) {
      atmp = b_Ac[((b_coltop << 3) + b_lastv) - 1];
      for (knt = 0; knt < 5; knt++) {
        coltop = 5 * k_i + knt;
        RLinv[coltop] += b_Linv[5 * b_coltop + knt] * atmp;
      }
    }
  }

  memcpy(&b_A[0], &RLinv[0], 25U * sizeof(real_T));
  for (k_i = 0; k_i < 5; k_i++) {
    tau[k_i] = 0.0;
    work[k_i] = 0.0;
  }

  for (k_i = 0; k_i < 5; k_i++) {
    ii = k_i * 5 + k_i;
    if (k_i + 1 < 5) {
      atmp = b_A[ii];
      b_lastv = ii + 2;
      tau[k_i] = 0.0;
      xnorm = mpc_test_xnrm2(4 - k_i, b_A, ii + 2);
      if (xnorm != 0.0) {
        b_A_0 = b_A[ii];
        xnorm = rt_hypotd_snf(b_A_0, xnorm);
        if (b_A_0 >= 0.0) {
          xnorm = -xnorm;
        }

        if (fabs(xnorm) < 1.0020841800044864E-292) {
          knt = 0;
          do {
            knt++;
            coltop = (ii - k_i) + 5;
            scalarLB = (((((coltop - ii) - 1) / 2) << 1) + ii) + 2;
            vectorUB = scalarLB - 2;
            for (b_coltop = b_lastv; b_coltop <= vectorUB; b_coltop += 2) {
              tmp = _mm_loadu_pd(&b_A[b_coltop - 1]);
              _mm_storeu_pd(&b_A[b_coltop - 1], _mm_mul_pd(tmp, _mm_set1_pd
                (9.9792015476736E+291)));
            }

            for (b_coltop = scalarLB; b_coltop <= coltop; b_coltop++) {
              b_A[b_coltop - 1] *= 9.9792015476736E+291;
            }

            xnorm *= 9.9792015476736E+291;
            atmp *= 9.9792015476736E+291;
          } while ((fabs(xnorm) < 1.0020841800044864E-292) && (knt < 20));

          xnorm = rt_hypotd_snf(atmp, mpc_test_xnrm2(4 - k_i, b_A, ii + 2));
          if (atmp >= 0.0) {
            xnorm = -xnorm;
          }

          tau[k_i] = (xnorm - atmp) / xnorm;
          atmp = 1.0 / (atmp - xnorm);
          vectorUB = scalarLB - 2;
          for (b_coltop = b_lastv; b_coltop <= vectorUB; b_coltop += 2) {
            tmp = _mm_loadu_pd(&b_A[b_coltop - 1]);
            _mm_storeu_pd(&b_A[b_coltop - 1], _mm_mul_pd(tmp, _mm_set1_pd(atmp)));
          }

          for (b_coltop = scalarLB; b_coltop <= coltop; b_coltop++) {
            b_A[b_coltop - 1] *= atmp;
          }

          for (b_lastv = 0; b_lastv < knt; b_lastv++) {
            xnorm *= 1.0020841800044864E-292;
          }

          atmp = xnorm;
        } else {
          tau[k_i] = (xnorm - b_A_0) / xnorm;
          atmp = 1.0 / (b_A_0 - xnorm);
          b_coltop = (ii - k_i) + 5;
          scalarLB = (((((b_coltop - ii) - 1) / 2) << 1) + ii) + 2;
          vectorUB = scalarLB - 2;
          for (knt = b_lastv; knt <= vectorUB; knt += 2) {
            tmp = _mm_loadu_pd(&b_A[knt - 1]);
            _mm_storeu_pd(&b_A[knt - 1], _mm_mul_pd(tmp, _mm_set1_pd(atmp)));
          }

          for (knt = scalarLB; knt <= b_coltop; knt++) {
            b_A[knt - 1] *= atmp;
          }

          atmp = xnorm;
        }
      }

      b_A[ii] = 1.0;
      if (tau[k_i] != 0.0) {
        b_lastv = 5 - k_i;
        knt = (ii - k_i) + 4;
        while ((b_lastv > 0) && (b_A[knt] == 0.0)) {
          b_lastv--;
          knt--;
        }

        knt = 4 - k_i;
        exitg2 = false;
        while ((!exitg2) && (knt > 0)) {
          b_coltop = ((knt - 1) * 5 + ii) + 5;
          coltop = b_coltop;
          do {
            exitg1 = 0;
            if (coltop + 1 <= b_coltop + b_lastv) {
              if (b_A[coltop] != 0.0) {
                exitg1 = 1;
              } else {
                coltop++;
              }
            } else {
              knt--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        b_lastv = 0;
        knt = 0;
      }

      if (b_lastv > 0) {
        mpc_test_xgemv(b_lastv, knt, b_A, ii + 6, b_A, ii + 1, work);
        mpc_test_xgerc(b_lastv, knt, -tau[k_i], ii + 1, work, b_A, ii + 6);
      }

      b_A[ii] = atmp;
    } else {
      tau[4] = 0.0;
    }
  }

  for (k_i = 0; k_i < 5; k_i++) {
    for (ii = 0; ii <= k_i; ii++) {
      R[ii + 5 * k_i] = b_A[5 * k_i + ii];
    }

    for (ii = k_i + 2; ii < 6; ii++) {
      R[(ii + 5 * k_i) - 1] = 0.0;
    }

    work[k_i] = 0.0;
  }

  for (k_i = 4; k_i >= 0; k_i--) {
    b_lastv = k_i * 5 + k_i;
    if (k_i + 1 < 5) {
      b_A[b_lastv] = 1.0;
      if (tau[k_i] != 0.0) {
        knt = 5 - k_i;
        b_coltop = (b_lastv - k_i) + 4;
        while ((knt > 0) && (b_A[b_coltop] == 0.0)) {
          knt--;
          b_coltop--;
        }

        b_coltop = 4 - k_i;
        exitg2 = false;
        while ((!exitg2) && (b_coltop > 0)) {
          coltop = ((b_coltop - 1) * 5 + b_lastv) + 5;
          ii = coltop;
          do {
            exitg1 = 0;
            if (ii + 1 <= coltop + knt) {
              if (b_A[ii] != 0.0) {
                exitg1 = 1;
              } else {
                ii++;
              }
            } else {
              b_coltop--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        knt = 0;
        b_coltop = 0;
      }

      if (knt > 0) {
        mpc_test_xgemv(knt, b_coltop, b_A, b_lastv + 6, b_A, b_lastv + 1, work);
        mpc_test_xgerc(knt, b_coltop, -tau[k_i], b_lastv + 1, work, b_A, b_lastv
                       + 6);
      }

      b_coltop = (b_lastv - k_i) + 5;
      scalarLB = (((((b_coltop - b_lastv) - 1) / 2) << 1) + b_lastv) + 2;
      vectorUB = scalarLB - 2;
      for (knt = b_lastv + 2; knt <= vectorUB; knt += 2) {
        tmp = _mm_loadu_pd(&b_A[knt - 1]);
        _mm_storeu_pd(&b_A[knt - 1], _mm_mul_pd(tmp, _mm_set1_pd(-tau[k_i])));
      }

      for (knt = scalarLB; knt <= b_coltop; knt++) {
        b_A[knt - 1] *= -tau[k_i];
      }
    }

    b_A[b_lastv] = 1.0 - tau[k_i];
    for (knt = 0; knt < k_i; knt++) {
      b_A[(b_lastv - knt) - 1] = 0.0;
    }
  }

  k_i = 0;
  do {
    exitg1 = 0;
    if (k_i <= nA - 1) {
      if (fabs(R[5 * k_i + k_i]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        k_i++;
      }
    } else {
      for (k_i = 0; k_i < n; k_i++) {
        for (ii = 0; ii < n; ii++) {
          atmp = 0.0;
          for (b_coltop = 0; b_coltop < 5; b_coltop++) {
            atmp += b_Linv[5 * k_i + b_coltop] * b_A[5 * ii + b_coltop];
          }

          TL[k_i + 5 * ii] = atmp;
        }
      }

      memset(&RLinv[0], 0, 25U * sizeof(real_T));
      for (k_i = nA; k_i >= 1; k_i--) {
        b_coltop = (k_i - 1) * 5;
        knt = (k_i + b_coltop) - 1;
        RLinv[knt] = 1.0;
        for (ii = k_i; ii <= nA; ii++) {
          coltop = ((ii - 1) * 5 + k_i) - 1;
          RLinv[coltop] /= R[knt];
        }

        if (k_i > 1) {
          for (ii = 0; ii <= k_i - 2; ii++) {
            for (b_lastv = k_i; b_lastv <= nA; b_lastv++) {
              knt = (b_lastv - 1) * 5;
              coltop = knt + ii;
              RLinv[coltop] -= RLinv[(knt + k_i) - 1] * R[b_coltop + ii];
            }
          }
        }
      }

      for (k_i = 0; k_i < n; k_i++) {
        for (ii = k_i + 1; ii <= n; ii++) {
          b_coltop = (ii - 1) * 5 + k_i;
          b_H[b_coltop] = 0.0;
          for (b_lastv = nA + 1; b_lastv <= n; b_lastv++) {
            knt = (b_lastv - 1) * 5;
            b_H[b_coltop] -= TL[(knt + ii) - 1] * TL[knt + k_i];
          }

          b_H[(ii + 5 * k_i) - 1] = b_H[b_coltop];
        }
      }

      for (k_i = 0; k_i < nA; k_i++) {
        for (ii = 0; ii < n; ii++) {
          b_coltop = 5 * k_i + ii;
          b_D[b_coltop] = 0.0;
          for (b_lastv = k_i + 1; b_lastv <= nA; b_lastv++) {
            knt = (b_lastv - 1) * 5;
            b_D[b_coltop] += TL[knt + ii] * RLinv[knt + k_i];
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static void mpc_test_DropConstraint(int32_T kDrop, boolean_T iA[8], int32_T *nA,
  int32_T iC[8])
{
  int32_T i;
  if (kDrop > 0) {
    iA[iC[kDrop - 1] - 1] = false;
    if (kDrop < *nA) {
      for (i = kDrop; i < *nA; i++) {
        iC[i - 1] = iC[i];
      }
    }

    iC[*nA - 1] = 0;
    (*nA)--;
  }
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static void mpc_test_qpkwik(const real_T b_Linv[25], const real_T b_Hinv[25],
  const real_T f[5], const real_T b_Ac[40], const real_T b[8], boolean_T iA[8],
  int32_T maxiter, real_T FeasTol, real_T x[5], real_T lambda[8], int32_T
  *status)
{
  __m128d tmp;
  __m128d tmp_0;
  real_T RLinv[25];
  real_T U[25];
  real_T b_D[25];
  real_T b_H[25];
  real_T Opt[10];
  real_T Rhs[10];
  real_T cTol[8];
  real_T r[5];
  real_T z[5];
  real_T Xnorm0;
  real_T cMin;
  real_T cVal;
  real_T rMin;
  real_T t;
  int32_T iC[8];
  int32_T b_exponent;
  int32_T exitg1;
  int32_T exitg3;
  int32_T exponent;
  int32_T i;
  int32_T iC_0;
  int32_T iSave;
  int32_T kDrop;
  int32_T nA;
  boolean_T ColdReset;
  boolean_T DualFeasible;
  boolean_T cTolComputed;
  boolean_T exitg2;
  boolean_T exitg4;
  boolean_T guard1;
  boolean_T guard2;
  for (i = 0; i < 5; i++) {
    x[i] = 0.0;
  }

  memset(&lambda[0], 0, sizeof(real_T) << 3U);
  *status = 1;
  for (i = 0; i < 5; i++) {
    r[i] = 0.0;
  }

  rMin = 0.0;
  cTolComputed = false;
  for (i = 0; i < 8; i++) {
    cTol[i] = 1.0;
    iC[i] = 0;
  }

  nA = 0;
  for (i = 0; i < 8; i++) {
    if (iA[i]) {
      nA++;
      iC[nA - 1] = i + 1;
    }
  }

  guard1 = false;
  if (nA > 0) {
    memset(&Opt[0], 0, 10U * sizeof(real_T));
    for (i = 0; i < 5; i++) {
      Rhs[i] = f[i];
      Rhs[i + 5] = 0.0;
    }

    DualFeasible = false;
    ColdReset = false;
    do {
      exitg3 = 0;
      if ((!DualFeasible) && (nA > 0) && (*status <= maxiter)) {
        Xnorm0 = mpc_test_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, b_D, b_H,
          mpc_test_degrees);
        if (Xnorm0 < 0.0) {
          if (ColdReset) {
            *status = -2;
            exitg3 = 2;
          } else {
            nA = 0;
            for (i = 0; i < 8; i++) {
              iA[i] = false;
              iC[i] = 0;
            }

            ColdReset = true;
          }
        } else {
          for (i = 0; i < nA; i++) {
            Rhs[i + 5] = b[iC[i] - 1];
            for (kDrop = i + 1; kDrop <= nA; kDrop++) {
              iC_0 = (5 * i + kDrop) - 1;
              U[iC_0] = 0.0;
              for (iSave = 0; iSave < nA; iSave++) {
                U[iC_0] += RLinv[(5 * iSave + kDrop) - 1] * RLinv[5 * iSave + i];
              }

              U[i + 5 * (kDrop - 1)] = U[iC_0];
            }
          }

          for (i = 0; i < 5; i++) {
            Xnorm0 = 0.0;
            for (iC_0 = 0; iC_0 < 5; iC_0++) {
              Xnorm0 += b_H[5 * iC_0 + i] * Rhs[iC_0];
            }

            Opt[i] = Xnorm0;
            for (kDrop = 0; kDrop < nA; kDrop++) {
              Opt[i] += b_D[5 * kDrop + i] * Rhs[kDrop + 5];
            }
          }

          for (i = 0; i < nA; i++) {
            Xnorm0 = 0.0;
            for (iC_0 = 0; iC_0 < 5; iC_0++) {
              Xnorm0 += b_D[5 * i + iC_0] * Rhs[iC_0];
            }

            Opt[i + 5] = Xnorm0;
            for (kDrop = 0; kDrop < nA; kDrop++) {
              Opt[i + 5] += U[5 * kDrop + i] * Rhs[kDrop + 5];
            }
          }

          Xnorm0 = -1.0E-12;
          kDrop = -1;
          for (i = 0; i < nA; i++) {
            cMin = Opt[i + 5];
            lambda[iC[i] - 1] = cMin;
            if ((cMin < Xnorm0) && (i + 1 <= nA)) {
              kDrop = i;
              Xnorm0 = cMin;
            }
          }

          if (kDrop + 1 <= 0) {
            DualFeasible = true;
            for (i = 0; i < 5; i++) {
              x[i] = Opt[i];
            }
          } else {
            (*status)++;
            if (*status > 5) {
              nA = 0;
              for (i = 0; i < 8; i++) {
                iA[i] = false;
                iC[i] = 0;
              }

              ColdReset = true;
            } else {
              lambda[iC[kDrop] - 1] = 0.0;
              mpc_test_DropConstraint(kDrop + 1, iA, &nA, iC);
            }
          }
        }
      } else {
        if (nA <= 0) {
          memset(&lambda[0], 0, sizeof(real_T) << 3U);
          for (i = 0; i < 5; i++) {
            Xnorm0 = 0.0;
            for (iC_0 = 0; iC_0 < 5; iC_0++) {
              Xnorm0 += -b_Hinv[5 * iC_0 + i] * f[iC_0];
            }

            x[i] = Xnorm0;
          }
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    for (i = 0; i < 5; i++) {
      Xnorm0 = 0.0;
      for (iC_0 = 0; iC_0 < 5; iC_0++) {
        Xnorm0 += -b_Hinv[5 * iC_0 + i] * f[iC_0];
      }

      x[i] = Xnorm0;
    }

    guard1 = true;
  }

  if (guard1) {
    Xnorm0 = mpc_test_norm(x);
    exitg2 = false;
    while ((!exitg2) && (*status <= maxiter)) {
      cMin = -FeasTol;
      i = -1;
      for (kDrop = 0; kDrop < 8; kDrop++) {
        if (!cTolComputed) {
          for (iSave = 0; iSave <= 2; iSave += 2) {
            z[iSave] = fabs(b_Ac[(iSave << 3) + kDrop] * x[iSave]);
            z[iSave + 1] = fabs(b_Ac[((iSave + 1) << 3) + kDrop] * x[iSave + 1]);
          }

          for (iSave = 4; iSave < 5; iSave++) {
            z[iSave] = fabs(b_Ac[(iSave << 3) + kDrop] * x[iSave]);
          }

          cTol[kDrop] = fmax(cTol[kDrop], mpc_test_maximum(z));
        }

        if (!iA[kDrop]) {
          cVal = 0.0;
          for (iC_0 = 0; iC_0 < 5; iC_0++) {
            cVal += b_Ac[(iC_0 << 3) + kDrop] * x[iC_0];
          }

          cVal = (cVal - b[kDrop]) / cTol[kDrop];
          if (cVal < cMin) {
            cMin = cVal;
            i = kDrop;
          }
        }
      }

      cTolComputed = true;
      if (i + 1 <= 0) {
        exitg2 = true;
      } else if (*status == maxiter) {
        *status = 0;
        exitg2 = true;
      } else {
        do {
          exitg1 = 0;
          if ((i + 1 > 0) && (*status <= maxiter)) {
            guard2 = false;
            if (nA == 0) {
              for (iC_0 = 0; iC_0 < 5; iC_0++) {
                z[iC_0] = 0.0;
              }

              for (iC_0 = 0; iC_0 < 5; iC_0++) {
                cMin = b_Ac[(iC_0 << 3) + i];
                for (kDrop = 0; kDrop <= 2; kDrop += 2) {
                  tmp_0 = _mm_loadu_pd(&z[kDrop]);
                  _mm_storeu_pd(&z[kDrop], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
                    (&b_Hinv[5 * iC_0 + kDrop]), _mm_set1_pd(cMin)), tmp_0));
                }

                for (kDrop = 4; kDrop < 5; kDrop++) {
                  z[kDrop] += b_Hinv[5 * iC_0 + kDrop] * cMin;
                }
              }

              guard2 = true;
            } else {
              cMin = mpc_test_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, b_D, b_H,
                mpc_test_degrees);
              if (cMin <= 0.0) {
                *status = -2;
                exitg1 = 1;
              } else {
                for (iC_0 = 0; iC_0 <= 22; iC_0 += 2) {
                  tmp_0 = _mm_loadu_pd(&b_H[iC_0]);
                  _mm_storeu_pd(&U[iC_0], _mm_mul_pd(tmp_0, _mm_set1_pd(-1.0)));
                }

                for (iC_0 = 24; iC_0 < 25; iC_0++) {
                  U[iC_0] = -b_H[iC_0];
                }

                for (iC_0 = 0; iC_0 < 5; iC_0++) {
                  z[iC_0] = 0.0;
                }

                for (iC_0 = 0; iC_0 < 5; iC_0++) {
                  cMin = b_Ac[(iC_0 << 3) + i];
                  for (kDrop = 0; kDrop <= 2; kDrop += 2) {
                    tmp_0 = _mm_loadu_pd(&U[5 * iC_0 + kDrop]);
                    tmp = _mm_loadu_pd(&z[kDrop]);
                    _mm_storeu_pd(&z[kDrop], _mm_add_pd(_mm_mul_pd(tmp_0,
                      _mm_set1_pd(cMin)), tmp));
                  }

                  for (kDrop = 4; kDrop < 5; kDrop++) {
                    z[kDrop] += U[5 * iC_0 + kDrop] * cMin;
                  }
                }

                for (kDrop = 0; kDrop < nA; kDrop++) {
                  cVal = 0.0;
                  for (iC_0 = 0; iC_0 < 5; iC_0++) {
                    cVal += b_Ac[(iC_0 << 3) + i] * b_D[5 * kDrop + iC_0];
                  }

                  r[kDrop] = cVal;
                }

                guard2 = true;
              }
            }

            if (guard2) {
              kDrop = 0;
              cMin = 0.0;
              DualFeasible = true;
              ColdReset = true;
              if (nA > 0) {
                iSave = 0;
                exitg4 = false;
                while ((!exitg4) && (iSave <= nA - 1)) {
                  if (r[iSave] >= 1.0E-12) {
                    ColdReset = false;
                    exitg4 = true;
                  } else {
                    iSave++;
                  }
                }
              }

              if ((nA != 0) && (!ColdReset)) {
                for (iSave = 0; iSave < nA; iSave++) {
                  cVal = r[iSave];
                  if (cVal > 1.0E-12) {
                    cVal = lambda[iC[iSave] - 1] / cVal;
                    if ((kDrop == 0) || (cVal < rMin)) {
                      rMin = cVal;
                      kDrop = iSave + 1;
                    }
                  }
                }

                if (kDrop > 0) {
                  cMin = rMin;
                  DualFeasible = false;
                }
              }

              t = 0.0;
              for (iC_0 = 0; iC_0 < 5; iC_0++) {
                t += b_Ac[(iC_0 << 3) + i] * z[iC_0];
              }

              if (t <= 0.0) {
                cVal = 0.0;
                ColdReset = true;
              } else {
                cVal = 0.0;
                for (iC_0 = 0; iC_0 < 5; iC_0++) {
                  cVal += b_Ac[(iC_0 << 3) + i] * x[iC_0];
                }

                cVal = (b[i] - cVal) / t;
                ColdReset = false;
              }

              if (DualFeasible && ColdReset) {
                *status = -1;
                exitg1 = 1;
              } else {
                if (ColdReset) {
                  t = cMin;
                } else if (DualFeasible) {
                  t = cVal;
                } else if (cMin < cVal) {
                  t = cMin;
                } else {
                  t = cVal;
                }

                for (iSave = 0; iSave < nA; iSave++) {
                  iC_0 = iC[iSave];
                  lambda[iC_0 - 1] -= t * r[iSave];
                  if ((iC_0 <= 8) && (lambda[iC_0 - 1] < 0.0)) {
                    lambda[iC_0 - 1] = 0.0;
                  }
                }

                lambda[i] += t;
                frexp(1.0, &exponent);
                if (fabs(t - cMin) < 2.2204460492503131E-16) {
                  mpc_test_DropConstraint(kDrop, iA, &nA, iC);
                }

                if (!ColdReset) {
                  for (iC_0 = 0; iC_0 <= 2; iC_0 += 2) {
                    tmp_0 = _mm_loadu_pd(&z[iC_0]);
                    tmp = _mm_loadu_pd(&x[iC_0]);
                    _mm_storeu_pd(&x[iC_0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(t),
                      tmp_0), tmp));
                  }

                  for (iC_0 = 4; iC_0 < 5; iC_0++) {
                    x[iC_0] += t * z[iC_0];
                  }

                  frexp(1.0, &b_exponent);
                  if (fabs(t - cVal) < 2.2204460492503131E-16) {
                    if (nA == mpc_test_degrees) {
                      *status = -1;
                      exitg1 = 1;
                    } else {
                      nA++;
                      iC[nA - 1] = i + 1;
                      kDrop = nA - 1;
                      exitg4 = false;
                      while ((!exitg4) && (kDrop + 1 > 1)) {
                        iC_0 = iC[kDrop - 1];
                        if (iC[kDrop] > iC_0) {
                          exitg4 = true;
                        } else {
                          iSave = iC[kDrop];
                          iC[kDrop] = iC_0;
                          iC[kDrop - 1] = iSave;
                          kDrop--;
                        }
                      }

                      iA[i] = true;
                      i = -1;
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                } else {
                  (*status)++;
                }
              }
            }
          } else {
            cMin = mpc_test_norm(x);
            if (fabs(cMin - Xnorm0) > 0.001) {
              Xnorm0 = cMin;
              for (i = 0; i < 8; i++) {
                cTol[i] = fmax(fabs(b[i]), 1.0);
              }

              cTolComputed = false;
            }

            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S30>/FixedHorizonOptimizer' */
static void mpc_test_mpcblock_optimizer(const real_T rseq[40], const real_T
  vseq[21], const real_T x[4], real_T old_u, const boolean_T iA[8], const real_T
  b_Mlim[8], real_T b_Mx[32], real_T b_Mu1[8], real_T b_Mv[168], const real_T
  b_utarget[20], real_T b_uoff, real_T b_H[25], real_T b_Ac[40], const real_T
  b_Wy[2], const real_T b_Jm[80], const real_T b_I1[20], const real_T b_A[16],
  const real_T Bu[84], const real_T Bv[84], const real_T b_C[8], const real_T
  Dv[42], const int32_T b_Mrows[8], real_T *u, real_T useq[21], real_T *status,
  boolean_T iAout[8])
{
  __m128d tmp;
  __m128d tmp_0;
  __m128d tmp_2;
  real_T WySuJm[160];
  real_T c_SuJm[160];
  real_T c_Sx[160];
  real_T c_Kv[84];
  real_T I2Jm[80];
  real_T WduJm[80];
  real_T WuI2Jm[80];
  real_T CA_0[42];
  real_T Sum_0[40];
  real_T c_Su1[40];
  real_T L[25];
  real_T b_Jm_0[16];
  real_T c_SuJm_0[16];
  real_T CA[8];
  real_T CA_1[8];
  real_T b_Mv_0[8];
  real_T varargin_1[5];
  real_T zopt[5];
  real_T c_Ku1[4];
  real_T c_Su1_0[4];
  real_T Sum[2];
  real_T tmp_1[2];
  real_T CA_2;
  real_T CA_3;
  real_T b_C_0;
  real_T normH;
  real_T s;
  int32_T I2Jm_tmp;
  int32_T Tries;
  int32_T i;
  int32_T kidx;
  int16_T ixw;
  int8_T a[400];
  int8_T b[25];
  int8_T rows[2];
  int8_T kidx_0;
  int8_T rows_tmp;
  static const int8_T c_A[400] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T guard1;
  boolean_T guard2;
  memset(&useq[0], 0, 21U * sizeof(real_T));
  for (i = 0; i < 8; i++) {
    iAout[i] = false;
  }

  Sum[0] = 0.0;
  Sum[1] = 0.0;
  normH = 0.0;
  s = 0.0;
  for (i = 0; i < 4; i++) {
    CA_2 = 0.0;
    CA_3 = 0.0;
    for (Tries = 0; Tries < 4; Tries++) {
      _mm_storeu_pd(&tmp_1[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&b_C[Tries <<
        1]), _mm_set1_pd(b_A[(i << 2) + Tries])), _mm_set_pd(CA_3, CA_2)));
      CA_2 = tmp_1[0];
      CA_3 = tmp_1[1];
    }

    Tries = i << 1;
    CA[Tries + 1] = CA_3;
    CA[Tries] = CA_2;
    CA_2 = Bu[i];
    CA_3 = b_C[Tries];
    Sum[0] += CA_3 * CA_2;
    b_C_0 = b_C[Tries + 1];
    Sum[1] += b_C_0 * CA_2;
    CA_2 = Bv[i];
    normH += CA_3 * CA_2;
    s += b_C_0 * CA_2;
  }

  mpc_test_B.c_Hv[0] = normH;
  mpc_test_B.c_Hv[40] = Dv[0];
  mpc_test_B.c_Hv[1] = s;
  mpc_test_B.c_Hv[41] = Dv[1];
  for (i = 0; i < 19; i++) {
    Tries = (i + 2) * 40;
    mpc_test_B.c_Hv[Tries] = 0.0;
    mpc_test_B.c_Hv[Tries + 1] = 0.0;
  }

  for (i = 0; i < 21; i++) {
    memset(&mpc_test_B.c_Hv[i * 40 + 2], 0, 38U * sizeof(real_T));
  }

  for (i = 0; i < 4; i++) {
    Tries = i << 1;
    c_Sx[40 * i] = CA[Tries];
    c_Sx[40 * i + 1] = CA[Tries + 1];
  }

  c_Su1[0] = Sum[0];
  c_Su1[1] = Sum[1];
  for (i = 0; i < 38; i++) {
    c_Sx[i + 2] = 0.0;
    c_Sx[i + 42] = 0.0;
    c_Sx[i + 82] = 0.0;
    c_Sx[i + 122] = 0.0;
    c_Su1[i + 2] = 0.0;
  }

  mpc_test_B.Su[0] = Sum[0];
  mpc_test_B.Su[1] = Sum[1];
  for (i = 0; i < 19; i++) {
    Tries = (i + 1) * 40;
    mpc_test_B.Su[Tries] = 0.0;
    mpc_test_B.Su[Tries + 1] = 0.0;
  }

  for (i = 0; i < 20; i++) {
    memset(&mpc_test_B.Su[i * 40 + 2], 0, 38U * sizeof(real_T));
  }

  for (kidx = 0; kidx < 19; kidx++) {
    kidx_0 = (int8_T)(((kidx + 1) << 1) + 1);
    normH = Bu[1];
    s = Bu[0];
    CA_2 = Bu[2];
    CA_3 = Bu[3];
    for (i = 0; i < 2; i++) {
      rows_tmp = (int8_T)(i + kidx_0);
      rows[i] = rows_tmp;
      b_C_0 = (((CA[i + 2] * normH + CA[i] * s) + CA[i + 4] * CA_2) + CA[i + 6] *
               CA_3) + Sum[i];
      Sum[i] = b_C_0;
      c_Su1[rows_tmp - 1] = b_C_0;
      Sum_0[i] = b_C_0;
    }

    kidx_0 = rows[0];
    rows_tmp = rows[1];
    for (i = 0; i < 19; i++) {
      Tries = (i + 1) << 1;
      Sum_0[Tries] = mpc_test_B.Su[(40 * i + kidx_0) - 3];
      Sum_0[Tries + 1] = mpc_test_B.Su[(40 * i + rows_tmp) - 3];
    }

    kidx_0 = rows[0];
    rows_tmp = rows[1];
    for (i = 0; i < 20; i++) {
      Tries = i << 1;
      mpc_test_B.Su[(kidx_0 + 40 * i) - 1] = Sum_0[Tries];
      mpc_test_B.Su[(rows_tmp + 40 * i) - 1] = Sum_0[Tries + 1];
    }

    normH = 0.0;
    s = 0.0;
    for (i = 0; i < 4; i++) {
      tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&CA[i << 1]), _mm_set1_pd(Bv[i])),
                         _mm_set_pd(s, normH));
      _mm_storeu_pd(&tmp_1[0], tmp_2);
      normH = tmp_1[0];
      s = tmp_1[1];
    }

    CA_0[0] = normH;
    CA_0[1] = s;
    kidx_0 = rows[0];
    rows_tmp = rows[1];
    for (i = 0; i < 20; i++) {
      Tries = (i + 1) << 1;
      CA_0[Tries] = mpc_test_B.c_Hv[(40 * i + kidx_0) - 3];
      CA_0[Tries + 1] = mpc_test_B.c_Hv[(40 * i + rows_tmp) - 3];
    }

    kidx_0 = rows[0];
    rows_tmp = rows[1];
    for (i = 0; i < 21; i++) {
      Tries = i << 1;
      mpc_test_B.c_Hv[(kidx_0 + 40 * i) - 1] = CA_0[Tries];
      mpc_test_B.c_Hv[(rows_tmp + 40 * i) - 1] = CA_0[Tries + 1];
    }

    for (i = 0; i < 4; i++) {
      CA_2 = 0.0;
      CA_3 = 0.0;
      for (Tries = 0; Tries < 4; Tries++) {
        tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&CA[Tries << 1]), _mm_set1_pd
          (b_A[(i << 2) + Tries])), _mm_set_pd(CA_3, CA_2));
        _mm_storeu_pd(&tmp_1[0], tmp_2);
        CA_2 = tmp_1[0];
        CA_3 = tmp_1[1];
      }

      Tries = i << 1;
      CA_1[Tries + 1] = CA_3;
      CA_1[Tries] = CA_2;
    }

    memcpy(&CA[0], &CA_1[0], sizeof(real_T) << 3U);
    kidx_0 = rows[0];
    rows_tmp = rows[1];
    for (i = 0; i < 4; i++) {
      Tries = i << 1;
      c_Sx[(kidx_0 + 40 * i) - 1] = CA[Tries];
      c_Sx[(rows_tmp + 40 * i) - 1] = CA[Tries + 1];
    }
  }

  for (i = 0; i < 40; i++) {
    c_SuJm[i] = 0.0;
    c_SuJm[i + 40] = 0.0;
    c_SuJm[i + 80] = 0.0;
    c_SuJm[i + 120] = 0.0;
  }

  for (i = 0; i < 4; i++) {
    for (Tries = 0; Tries < 20; Tries++) {
      CA_2 = b_Jm[20 * i + Tries];
      for (kidx = 0; kidx <= 38; kidx += 2) {
        tmp_2 = _mm_loadu_pd(&mpc_test_B.Su[40 * Tries + kidx]);
        I2Jm_tmp = 40 * i + kidx;
        tmp_0 = _mm_loadu_pd(&c_SuJm[I2Jm_tmp]);
        _mm_storeu_pd(&c_SuJm[I2Jm_tmp], _mm_add_pd(_mm_mul_pd(tmp_2,
          _mm_set1_pd(CA_2)), tmp_0));
      }
    }
  }

  if (b_Mrows[0] > 0) {
    kidx = 0;
    exitg1 = false;
    while ((!exitg1) && (kidx < 8)) {
      if (b_Mrows[kidx] <= 40) {
        Tries = b_Mrows[kidx];
        i = b_Mrows[kidx];
        b_Ac[kidx] = -c_SuJm[Tries - 1];
        b_Mx[kidx] = -c_Sx[i - 1];
        b_Ac[kidx + 8] = -c_SuJm[Tries + 39];
        b_Mx[kidx + 8] = -c_Sx[i + 39];
        b_Ac[kidx + 16] = -c_SuJm[Tries + 79];
        b_Mx[kidx + 16] = -c_Sx[i + 79];
        b_Ac[kidx + 24] = -c_SuJm[Tries + 119];
        b_Mx[kidx + 24] = -c_Sx[i + 119];
        b_Mu1[kidx] = -c_Su1[b_Mrows[kidx] - 1];
        Tries = b_Mrows[kidx];
        for (i = 0; i < 21; i++) {
          b_Mv[kidx + (i << 3)] = -mpc_test_B.c_Hv[(40 * i + Tries) - 1];
        }

        kidx++;
      } else if (b_Mrows[kidx] <= 80) {
        Tries = b_Mrows[kidx];
        i = b_Mrows[kidx];
        b_Ac[kidx] = c_SuJm[Tries - 41];
        b_Mx[kidx] = c_Sx[i - 41];
        b_Ac[kidx + 8] = c_SuJm[Tries - 1];
        b_Mx[kidx + 8] = c_Sx[i - 1];
        b_Ac[kidx + 16] = c_SuJm[Tries + 39];
        b_Mx[kidx + 16] = c_Sx[i + 39];
        b_Ac[kidx + 24] = c_SuJm[Tries + 79];
        b_Mx[kidx + 24] = c_Sx[i + 79];
        b_Mu1[kidx] = c_Su1[b_Mrows[kidx] - 41];
        Tries = b_Mrows[kidx];
        for (i = 0; i < 21; i++) {
          b_Mv[kidx + (i << 3)] = mpc_test_B.c_Hv[(40 * i + Tries) - 41];
        }

        kidx++;
      } else {
        exitg1 = true;
      }
    }
  }

  kidx = -1;
  for (Tries = 0; Tries < 20; Tries++) {
    for (i = 0; i < 20; i++) {
      a[(kidx + i) + 1] = c_A[20 * Tries + i];
    }

    kidx += 20;
    I2Jm[Tries] = 0.0;
    I2Jm[Tries + 20] = 0.0;
    I2Jm[Tries + 40] = 0.0;
    I2Jm[Tries + 60] = 0.0;
  }

  for (i = 0; i < 4; i++) {
    for (Tries = 0; Tries < 20; Tries++) {
      CA_2 = b_Jm[20 * i + Tries];
      for (kidx = 0; kidx < 20; kidx++) {
        I2Jm_tmp = 20 * i + kidx;
        I2Jm[I2Jm_tmp] += (real_T)a[20 * Tries + kidx] * CA_2;
      }
    }
  }

  ixw = 1;
  for (kidx = 0; kidx < 40; kidx++) {
    normH = b_Wy[ixw - 1];
    _mm_storeu_pd(&tmp_1[0], _mm_mul_pd(_mm_set_pd(c_SuJm[kidx + 40], normH),
      _mm_set_pd(normH, c_SuJm[kidx])));
    WySuJm[kidx] = tmp_1[0];
    WySuJm[kidx + 40] = tmp_1[1];
    _mm_storeu_pd(&tmp_1[0], _mm_mul_pd(_mm_set_pd(c_SuJm[kidx + 120],
      c_SuJm[kidx + 80]), _mm_set1_pd(normH)));
    WySuJm[kidx + 80] = tmp_1[0];
    WySuJm[kidx + 120] = tmp_1[1];
    ixw++;
    if (ixw > 2) {
      ixw = 1;
    }
  }

  for (kidx = 0; kidx <= 18; kidx += 2) {
    tmp_2 = _mm_loadu_pd(&I2Jm[kidx]);
    tmp_0 = _mm_set1_pd(mpc_test_Wu);
    _mm_storeu_pd(&WuI2Jm[kidx], _mm_mul_pd(tmp_0, tmp_2));
    tmp_2 = _mm_set1_pd(mpc_test_Wdu);
    _mm_storeu_pd(&WduJm[kidx], _mm_mul_pd(tmp_2, _mm_loadu_pd(&b_Jm[kidx])));
    tmp = _mm_loadu_pd(&I2Jm[kidx + 20]);
    _mm_storeu_pd(&WuI2Jm[kidx + 20], _mm_mul_pd(tmp, tmp_0));
    _mm_storeu_pd(&WduJm[kidx + 20], _mm_mul_pd(_mm_loadu_pd(&b_Jm[kidx + 20]),
      tmp_2));
    tmp = _mm_loadu_pd(&I2Jm[kidx + 40]);
    _mm_storeu_pd(&WuI2Jm[kidx + 40], _mm_mul_pd(tmp, tmp_0));
    _mm_storeu_pd(&WduJm[kidx + 40], _mm_mul_pd(_mm_loadu_pd(&b_Jm[kidx + 40]),
      tmp_2));
    tmp = _mm_loadu_pd(&I2Jm[kidx + 60]);
    _mm_storeu_pd(&WuI2Jm[kidx + 60], _mm_mul_pd(tmp, tmp_0));
    _mm_storeu_pd(&WduJm[kidx + 60], _mm_mul_pd(_mm_loadu_pd(&b_Jm[kidx + 60]),
      tmp_2));
  }

  for (i = 0; i < 4; i++) {
    for (Tries = 0; Tries < 4; Tries++) {
      CA_2 = 0.0;
      for (kidx = 0; kidx < 40; kidx++) {
        CA_2 += c_SuJm[40 * Tries + kidx] * WySuJm[40 * i + kidx];
      }

      I2Jm_tmp = (i << 2) + Tries;
      c_SuJm_0[I2Jm_tmp] = CA_2;
      CA_2 = 0.0;
      for (kidx = 0; kidx < 20; kidx++) {
        CA_2 += b_Jm[20 * Tries + kidx] * WduJm[20 * i + kidx];
      }

      b_Jm_0[I2Jm_tmp] = CA_2;
    }
  }

  for (i = 0; i < 4; i++) {
    for (Tries = 0; Tries < 4; Tries++) {
      CA_2 = 0.0;
      for (kidx = 0; kidx < 20; kidx++) {
        CA_2 += I2Jm[20 * i + kidx] * WuI2Jm[20 * Tries + kidx];
      }

      I2Jm_tmp = (Tries << 2) + i;
      b_H[i + 5 * Tries] = (c_SuJm_0[I2Jm_tmp] + b_Jm_0[I2Jm_tmp]) + CA_2;
    }
  }

  normH = 0.0;
  s = 0.0;
  CA_2 = 0.0;
  CA_3 = 0.0;
  for (i = 0; i < 40; i++) {
    _mm_storeu_pd(&tmp_1[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd(WySuJm[i + 40],
      c_Su1[i]), _mm_set_pd(c_Su1[i], WySuJm[i])), _mm_set_pd(s, normH)));
    normH = tmp_1[0];
    s = tmp_1[1];
    _mm_storeu_pd(&tmp_1[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd(WySuJm[i + 120],
      WySuJm[i + 80]), _mm_set1_pd(c_Su1[i])), _mm_set_pd(CA_3, CA_2)));
    CA_2 = tmp_1[0];
    CA_3 = tmp_1[1];
  }

  c_Su1_0[3] = CA_3;
  c_Su1_0[2] = CA_2;
  c_Su1_0[1] = s;
  c_Su1_0[0] = normH;
  normH = 0.0;
  s = 0.0;
  CA_2 = 0.0;
  CA_3 = 0.0;
  for (i = 0; i < 20; i++) {
    _mm_storeu_pd(&tmp_1[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd(WuI2Jm[i + 20],
      b_I1[i]), _mm_set_pd(b_I1[i], WuI2Jm[i])), _mm_set_pd(s, normH)));
    normH = tmp_1[0];
    s = tmp_1[1];
    _mm_storeu_pd(&tmp_1[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd(WuI2Jm[i + 60],
      WuI2Jm[i + 40]), _mm_set1_pd(b_I1[i])), _mm_set_pd(CA_3, CA_2)));
    CA_2 = tmp_1[0];
    CA_3 = tmp_1[1];
  }

  tmp_2 = _mm_add_pd(_mm_loadu_pd(&c_Su1_0[0]), _mm_set_pd(s, normH));
  _mm_storeu_pd(&c_Ku1[0], tmp_2);
  tmp_2 = _mm_add_pd(_mm_loadu_pd(&c_Su1_0[2]), _mm_set_pd(CA_3, CA_2));
  _mm_storeu_pd(&c_Ku1[2], tmp_2);
  for (i = 0; i <= 78; i += 2) {
    tmp_2 = _mm_loadu_pd(&WuI2Jm[i]);
    _mm_storeu_pd(&WuI2Jm[i], _mm_mul_pd(tmp_2, _mm_set1_pd(-1.0)));
  }

  for (i = 0; i < 4; i++) {
    for (Tries = 0; Tries < 4; Tries++) {
      CA_2 = 0.0;
      for (kidx = 0; kidx < 40; kidx++) {
        CA_2 += c_Sx[40 * Tries + kidx] * WySuJm[40 * i + kidx];
      }

      c_SuJm_0[Tries + (i << 2)] = CA_2;
    }

    for (Tries = 0; Tries < 21; Tries++) {
      CA_2 = 0.0;
      for (kidx = 0; kidx < 40; kidx++) {
        CA_2 += mpc_test_B.c_Hv[40 * Tries + kidx] * WySuJm[40 * i + kidx];
      }

      c_Kv[Tries + 21 * i] = CA_2;
    }
  }

  for (i = 0; i <= 158; i += 2) {
    tmp_2 = _mm_loadu_pd(&WySuJm[i]);
    _mm_storeu_pd(&WySuJm[i], _mm_mul_pd(tmp_2, _mm_set1_pd(-1.0)));
  }

  kidx = 0;
  memcpy(&L[0], &b_H[0], 25U * sizeof(real_T));
  Tries = mpc_test_xpotrf(L);
  guard1 = false;
  if (Tries == 0) {
    for (Tries = 0; Tries < 5; Tries++) {
      varargin_1[Tries] = L[5 * Tries + Tries];
    }

    if (mpc_test_minimum(varargin_1) > 1.4901161193847656E-7) {
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    normH = 0.0;
    Tries = 0;
    exitg2 = false;
    while ((!exitg2) && (Tries < 5)) {
      s = 0.0;
      for (i = 0; i < 5; i++) {
        s += fabs(b_H[5 * i + Tries]);
      }

      if (rtIsNaN(s)) {
        normH = (rtNaN);
        exitg2 = true;
      } else {
        if (s > normH) {
          normH = s;
        }

        Tries++;
      }
    }

    if (normH >= 1.0E+10) {
      kidx = 2;
    } else {
      Tries = 0;
      exitg1 = false;
      while ((!exitg1) && (Tries <= 4)) {
        normH = rt_powd_snf(10.0, (real_T)Tries) * 1.4901161193847656E-7;
        for (i = 0; i < 25; i++) {
          b[i] = 0;
        }

        for (kidx = 0; kidx < 5; kidx++) {
          b[kidx + 5 * kidx] = 1;
        }

        for (i = 0; i < 25; i++) {
          s = normH * (real_T)b[i] + b_H[i];
          b_H[i] = s;
          L[i] = s;
        }

        kidx = mpc_test_xpotrf(L);
        guard2 = false;
        if (kidx == 0) {
          for (kidx = 0; kidx < 5; kidx++) {
            varargin_1[kidx] = L[5 * kidx + kidx];
          }

          if (mpc_test_minimum(varargin_1) > 1.4901161193847656E-7) {
            kidx = 1;
            exitg1 = true;
          } else {
            guard2 = true;
          }
        } else {
          guard2 = true;
        }

        if (guard2) {
          kidx = 3;
          Tries++;
        }
      }
    }
  }

  if (kidx > 1) {
    *u = old_u + b_uoff;
    for (i = 0; i < 21; i++) {
      useq[i] = *u;
    }

    *status = -2.0;
  } else {
    for (i = 0; i < 25; i++) {
      b[i] = 0;
    }

    for (kidx = 0; kidx < 5; kidx++) {
      b[kidx + 5 * kidx] = 1;
    }

    for (kidx = 0; kidx < 5; kidx++) {
      for (Tries = 0; Tries < 5; Tries++) {
        I2Jm_tmp = 5 * kidx + Tries;
        b_H[I2Jm_tmp] = b[I2Jm_tmp];
      }

      varargin_1[kidx] = 0.0;
    }

    mpc_test_trisolve(L, b_H);
    for (kidx = 0; kidx < 4; kidx++) {
      normH = 0.0;
      for (i = 0; i < 40; i++) {
        normH += WySuJm[40 * kidx + i] * rseq[i];
      }

      s = 0.0;
      for (i = 0; i < 21; i++) {
        s += c_Kv[21 * kidx + i] * vseq[i];
      }

      CA_2 = 0.0;
      for (i = 0; i < 20; i++) {
        CA_2 += WuI2Jm[20 * kidx + i] * b_utarget[i];
      }

      i = kidx << 2;
      varargin_1[kidx] = ((((((c_SuJm_0[i + 1] * x[1] + c_SuJm_0[i] * x[0]) +
        c_SuJm_0[i + 2] * x[2]) + c_SuJm_0[i + 3] * x[3]) + normH) + c_Ku1[kidx]
                           * old_u) + s) + CA_2;
    }

    normH = x[1];
    s = x[0];
    CA_2 = x[2];
    CA_3 = x[3];
    for (i = 0; i < 8; i++) {
      iAout[i] = iA[i];
      CA[i] = ((((b_Mx[i + 8] * normH + b_Mx[i] * s) + b_Mx[i + 16] * CA_2) +
                b_Mx[i + 24] * CA_3) + b_Mlim[i]) + b_Mu1[i] * old_u;
      b_Mv_0[i] = 0.0;
    }

    for (i = 0; i < 21; i++) {
      CA_2 = vseq[i];
      for (Tries = 0; Tries <= 6; Tries += 2) {
        tmp_2 = _mm_loadu_pd(&b_Mv[(i << 3) + Tries]);
        tmp_0 = _mm_loadu_pd(&b_Mv_0[Tries]);
        _mm_storeu_pd(&b_Mv_0[Tries], _mm_add_pd(_mm_mul_pd(tmp_2, _mm_set1_pd
          (CA_2)), tmp_0));
      }
    }

    for (i = 0; i < 5; i++) {
      for (Tries = 0; Tries < 5; Tries++) {
        CA_2 = 0.0;
        for (kidx = 0; kidx < 5; kidx++) {
          CA_2 += b_H[5 * Tries + kidx] * b_H[5 * i + kidx];
        }

        L[Tries + 5 * i] = CA_2;
      }
    }

    for (i = 0; i <= 6; i += 2) {
      tmp_2 = _mm_loadu_pd(&CA[i]);
      tmp_0 = _mm_loadu_pd(&b_Mv_0[i]);
      _mm_storeu_pd(&CA_1[i], _mm_mul_pd(_mm_add_pd(tmp_2, tmp_0), _mm_set1_pd
        (-1.0)));
    }

    mpc_test_qpkwik(b_H, L, varargin_1, b_Ac, CA_1, iAout, 120, 1.0E-6, zopt, CA,
                    &kidx);
    if ((kidx < 0) || (kidx == 0)) {
      for (i = 0; i < 5; i++) {
        zopt[i] = 0.0;
      }
    }

    *status = kidx;
    *u = (old_u + zopt[0]) + b_uoff;
  }
}

/* Model step function */
void mpc_test_step(void)
{
  __m128d tmp_3;
  __m128d tmp_4;
  __m128d tmp_5;
  real_T Cm[168];
  real_T Bu[84];
  real_T Bv[84];
  real_T Dv[42];
  real_T rseq[40];
  real_T CovMat[36];
  real_T tmp_1[32];
  real_T b_tmp[24];
  real_T rtb_useq[21];
  real_T vseq[21];
  real_T b_B[20];
  real_T tmp_2[20];
  real_T L_tmp[16];
  real_T L_tmp_0[16];
  real_T Pk1[16];
  real_T b_A[16];
  real_T Cm_0[8];
  real_T L[8];
  real_T b_C[8];
  real_T b_Mlim[8];
  real_T c_A_tmp[8];
  real_T tmp[8];
  real_T tmp_0[8];
  real_T Kinv[4];
  real_T UnknownIn[4];
  real_T c_A[4];
  real_T b_b[3];
  real_T Y[2];
  real_T tmp_6[2];
  real_T y_innov[2];
  real_T L_tmp_1;
  real_T L_tmp_2;
  real_T L_tmp_3;
  real_T L_tmp_4;
  real_T L_tmp_5;
  real_T L_tmp_6;
  real_T Y_0;
  real_T Y_1;
  real_T a21;
  real_T a22;
  int32_T L_tmp_7;
  int32_T L_tmp_tmp;
  int32_T b_C_tmp;
  int32_T r1;
  int32_T r2;
  static const real_T c[16] = { 1.0, 0.0, 0.0, 0.0, -0.1, 1.0, 0.0, 0.0,
    -0.0046826882694954641, 0.090634623461009076, 0.81873075307798182, 0.0, 0.0,
    0.0, 0.0, 1.0 };

  static const real_T d[20] = { -0.00031731173050453558, 0.0093653765389909265,
    0.18126924692201815, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const int8_T e[8] = { 1, 0, 0, 1, 0, 0, 0, 1 };

  static const int8_T f[8] = { 3, 3, 3, 3, 5, 5, 5, 5 };

  static const int32_T b_Mrows[8] = { 81, 82, 83, 84, 101, 102, 103, 104 };

  static const int8_T b_D[10] = { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 };

  static const real_T q[8] = { -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0 };

  static const real_T r[25] = { 618.16240884286356, 531.09770804158347,
    453.52343669742248, 383.07831197495358, 0.0, 531.09770804158347,
    460.76748230799495, 392.03550188291229, 331.57580637552167, 0.0,
    453.52343669742248, 392.03550188291229, 337.89639543813212,
    284.28017018266377, 0.0, 383.07831197495352, 331.57580637552167,
    284.28017018266377, 243.39122232988987, 0.0, 0.0, 0.0, 0.0, 0.0, 100000.0 };

  static const real_T t[40] = { -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -0.0,
    -1.0, -1.0, -1.0, 0.0, 1.0, 1.0, 1.0, -0.0, -0.0, -1.0, -1.0, 0.0, 0.0, 1.0,
    1.0, -0.0, -0.0, -0.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0 };

  static const real_T v[80] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  real_T t_0[40];
  real_T r_0[25];
  boolean_T tmp_7[8];

  /* MATLAB Function: '<S30>/FixedHorizonOptimizer' incorporates:
   *  Inport: '<Root>/A'
   *  Inport: '<Root>/B'
   *  Inport: '<Root>/C'
   *  Inport: '<Root>/In2'
   *  Inport: '<Root>/In3'
   *  Inport: '<Root>/In5'
   *  Inport: '<Root>/In7'
   *  Memory: '<S2>/LastPcov'
   */
  b_b[0] = mpc_test_U.B[0];
  b_b[1] = mpc_test_U.B[1];
  b_b[2] = mpc_test_U.B[2];
  memset(&Bu[0], 0, 84U * sizeof(real_T));
  memset(&Bv[0], 0, 84U * sizeof(real_T));
  memset(&Dv[0], 0, 42U * sizeof(real_T));
  memset(&Cm[0], 0, 168U * sizeof(real_T));
  memcpy(&b_A[0], &c[0], sizeof(real_T) << 4U);
  memcpy(&b_B[0], &d[0], 20U * sizeof(real_T));
  for (r1 = 0; r1 < 8; r1++) {
    b_C[r1] = e[r1];
  }

  for (r1 = 0; r1 < 3; r1++) {
    b_C_tmp = r1 << 1;
    b_C[b_C_tmp] = mpc_test_U.C[b_C_tmp];
    b_C[b_C_tmp + 1] = mpc_test_U.C[b_C_tmp + 1];
    b_C_tmp = r1 << 2;
    b_A[b_C_tmp] = mpc_test_U.A[3 * r1];
    b_A[b_C_tmp + 1] = mpc_test_U.A[3 * r1 + 1];
    b_A[b_C_tmp + 2] = mpc_test_U.A[3 * r1 + 2];
    b_B[r1] = b_b[r1];
  }

  UnknownIn[0] = 1.0;
  UnknownIn[1] = 3.0;
  UnknownIn[2] = 4.0;
  UnknownIn[3] = 5.0;
  for (r1 = 0; r1 < 4; r1++) {
    Bu[r1] = b_B[r1];
    Bv[r1] = b_B[r1 + 4];
    b_C_tmp = r1 << 1;
    Cm[b_C_tmp] = b_C[b_C_tmp];
    Cm[b_C_tmp + 1] = b_C[b_C_tmp + 1];
    b_C_tmp = (int8_T)UnknownIn[r1] - 1;
    r2 = b_C_tmp << 2;
    b_tmp[6 * r1] = b_B[r2];
    b_tmp[6 * r1 + 1] = b_B[r2 + 1];
    b_tmp[6 * r1 + 2] = b_B[r2 + 2];
    b_tmp[6 * r1 + 3] = b_B[r2 + 3];
    r2 = b_C_tmp << 1;
    b_tmp[6 * r1 + 4] = b_D[r2];
    b_tmp[6 * r1 + 5] = b_D[r2 + 1];
  }

  for (r1 = 0; r1 < 6; r1++) {
    for (b_C_tmp = 0; b_C_tmp < 6; b_C_tmp++) {
      CovMat[b_C_tmp + 6 * r1] = 0.0;
    }

    for (b_C_tmp = 0; b_C_tmp < 4; b_C_tmp++) {
      a22 = b_tmp[6 * b_C_tmp + r1];
      for (r2 = 0; r2 <= 4; r2 += 2) {
        tmp_4 = _mm_loadu_pd(&b_tmp[6 * b_C_tmp + r2]);
        L_tmp_tmp = 6 * r1 + r2;
        tmp_5 = _mm_loadu_pd(&CovMat[L_tmp_tmp]);
        _mm_storeu_pd(&CovMat[L_tmp_tmp], _mm_add_pd(_mm_mul_pd(tmp_4,
          _mm_set1_pd(a22)), tmp_5));
      }
    }
  }

  Dv[0] = 0.0;
  Dv[1] = 0.0;
  Y[0] = mpc_test_U.Y[0];
  Y[1] = mpc_test_U.Y[1];
  for (r1 = 0; r1 < 8; r1++) {
    a22 = f[r1];
    b_Mlim[r1] = a22;
    if (b_Mrows[r1] <= 100) {
      b_Mlim[r1] = (mpc_test_uoff - mpc_test_U.U) + a22;
    } else {
      b_Mlim[r1] = a22 - (mpc_test_uoff - mpc_test_U.U);
    }
  }

  for (r1 = 0; r1 < 20; r1++) {
    b_B[r1] = 0.0 - mpc_test_U.U;
  }

  Bv[0] = mpc_test_U.DX[0];
  Bv[1] = mpc_test_U.DX[1];
  Bv[2] = mpc_test_U.DX[2];
  for (r1 = 0; r1 < 21; r1++) {
    vseq[r1] = 1.0;
  }

  a22 = mpc_test_U.In7[0];
  a21 = mpc_test_U.In7[1];
  Y_0 = mpc_test_U.Y[0];
  Y_1 = mpc_test_U.Y[1];
  for (r1 = 0; r1 < 20; r1++) {
    b_C_tmp = r1 << 1;
    rseq[b_C_tmp] = a22 - Y_0;
    rseq[b_C_tmp + 1] = a21 - Y_1;
  }

  UnknownIn[0] = 0.0;
  UnknownIn[1] = 0.0;
  UnknownIn[2] = 0.0;
  UnknownIn[3] = 0.0;
  for (r1 = 0; r1 < 2; r1++) {
    UnknownIn[r1 + (r1 << 1)] = 1.0;
    b_C_tmp = r1 << 2;
    c_A_tmp[b_C_tmp] = Cm[r1];
    c_A_tmp[b_C_tmp + 1] = Cm[r1 + 2];
    c_A_tmp[b_C_tmp + 2] = Cm[r1 + 4];
    c_A_tmp[b_C_tmp + 3] = Cm[r1 + 6];
  }

  for (r1 = 0; r1 < 4; r1++) {
    a22 = 0.0;
    a21 = 0.0;
    for (b_C_tmp = 0; b_C_tmp < 4; b_C_tmp++) {
      tmp_4 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Cm[b_C_tmp << 1]), _mm_set1_pd
        (mpc_test_DW.LastPcov_PreviousInput[(r1 << 2) + b_C_tmp])), _mm_set_pd
                         (a21, a22));
      _mm_storeu_pd(&tmp_6[0], tmp_4);
      a22 = tmp_6[0];
      a21 = tmp_6[1];
    }

    b_C_tmp = r1 << 1;
    Cm_0[b_C_tmp + 1] = a21;
    Cm_0[b_C_tmp] = a22;
  }

  for (r1 = 0; r1 < 2; r1++) {
    a22 = Cm_0[r1 + 2];
    a21 = Cm_0[r1];
    Y_0 = Cm_0[r1 + 4];
    Y_1 = Cm_0[r1 + 6];
    for (b_C_tmp = 0; b_C_tmp <= 0; b_C_tmp += 2) {
      r2 = (b_C_tmp + 1) << 2;
      L_tmp_tmp = b_C_tmp << 2;
      _mm_storeu_pd(&tmp_6[0], _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd
        (_mm_mul_pd(_mm_set_pd(c_A_tmp[r2 + 1], c_A_tmp[L_tmp_tmp + 1]),
                    _mm_set1_pd(a22)), _mm_mul_pd(_mm_set_pd(c_A_tmp[r2],
        c_A_tmp[L_tmp_tmp]), _mm_set1_pd(a21))), _mm_mul_pd(_mm_set_pd
        (c_A_tmp[r2 + 2], c_A_tmp[L_tmp_tmp + 2]), _mm_set1_pd(Y_0))),
        _mm_mul_pd(_mm_set_pd(c_A_tmp[r2 + 3], c_A_tmp[L_tmp_tmp + 3]),
                   _mm_set1_pd(Y_1))), _mm_set_pd(CovMat[((b_C_tmp + 5) * 6 + r1)
        + 4], CovMat[((b_C_tmp + 4) * 6 + r1) + 4])));
      c_A[r1 + (b_C_tmp << 1)] = tmp_6[0];
      c_A[r1 + ((b_C_tmp + 1) << 1)] = tmp_6[1];
    }
  }

  if (fabs(c_A[1]) > fabs(c_A[0])) {
    r1 = 1;
    r2 = 0;
  } else {
    r1 = 0;
    r2 = 1;
  }

  a21 = c_A[r2] / c_A[r1];
  Y_0 = c_A[r1 + 2];
  a22 = c_A[r2 + 2] - Y_0 * a21;
  b_C_tmp = r1 << 1;
  Kinv[b_C_tmp] = UnknownIn[0] / c_A[r1];
  r2 <<= 1;
  Kinv[r2] = (UnknownIn[2] - Kinv[b_C_tmp] * Y_0) / a22;
  Kinv[b_C_tmp] -= Kinv[r2] * a21;
  Kinv[b_C_tmp + 1] = UnknownIn[1] / c_A[r1];
  Kinv[r2 + 1] = (UnknownIn[3] - Kinv[b_C_tmp + 1] * Y_0) / a22;
  Kinv[b_C_tmp + 1] -= Kinv[r2 + 1] * a21;
  for (r1 = 0; r1 < 4; r1++) {
    Y_0 = 0.0;
    Y_1 = 0.0;
    L_tmp_5 = 0.0;
    L_tmp_6 = 0.0;
    for (b_C_tmp = 0; b_C_tmp < 4; b_C_tmp++) {
      r2 = b_C_tmp << 2;
      tmp_4 = _mm_set1_pd(mpc_test_DW.LastPcov_PreviousInput[(r1 << 2) + b_C_tmp]);
      tmp_5 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&b_A[r2]), tmp_4), _mm_set_pd
                         (Y_1, Y_0));
      _mm_storeu_pd(&tmp_6[0], tmp_5);
      Y_0 = tmp_6[0];
      Y_1 = tmp_6[1];
      tmp_4 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&b_A[r2 + 2]), tmp_4),
                         _mm_set_pd(L_tmp_6, L_tmp_5));
      _mm_storeu_pd(&tmp_6[0], tmp_4);
      L_tmp_5 = tmp_6[0];
      L_tmp_6 = tmp_6[1];
    }

    L_tmp_tmp = r1 << 2;
    L_tmp[L_tmp_tmp + 3] = L_tmp_6;
    L_tmp[L_tmp_tmp + 2] = L_tmp_5;
    L_tmp[L_tmp_tmp + 1] = Y_1;
    L_tmp[L_tmp_tmp] = Y_0;
  }

  for (r1 = 0; r1 < 4; r1++) {
    Y_0 = L_tmp[r1 + 4];
    Y_1 = L_tmp[r1];
    L_tmp_5 = L_tmp[r1 + 8];
    L_tmp_6 = L_tmp[r1 + 12];
    for (b_C_tmp = 0; b_C_tmp <= 0; b_C_tmp += 2) {
      r2 = (b_C_tmp + 1) << 2;
      L_tmp_tmp = b_C_tmp << 2;
      _mm_storeu_pd(&tmp_6[0], _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd
        (_mm_mul_pd(_mm_set_pd(c_A_tmp[r2 + 1], c_A_tmp[L_tmp_tmp + 1]),
                    _mm_set1_pd(Y_0)), _mm_mul_pd(_mm_set_pd(c_A_tmp[r2],
        c_A_tmp[L_tmp_tmp]), _mm_set1_pd(Y_1))), _mm_mul_pd(_mm_set_pd
        (c_A_tmp[r2 + 2], c_A_tmp[L_tmp_tmp + 2]), _mm_set1_pd(L_tmp_5))),
        _mm_mul_pd(_mm_set_pd(c_A_tmp[r2 + 3], c_A_tmp[L_tmp_tmp + 3]),
                   _mm_set1_pd(L_tmp_6))), _mm_set_pd(CovMat[(b_C_tmp + 5) * 6 +
        r1], CovMat[(b_C_tmp + 4) * 6 + r1])));
      Cm_0[r1 + L_tmp_tmp] = tmp_6[0];
      Cm_0[r1 + r2] = tmp_6[1];
    }
  }

  /* Memory: '<S2>/last_x' incorporates:
   *  Inport: '<Root>/In1'
   *  MATLAB Function: '<S30>/FixedHorizonOptimizer'
   */
  tmp_4 = _mm_add_pd(_mm_sub_pd(_mm_loadu_pd(&mpc_test_DW.last_x_PreviousInput[0]),
    _mm_loadu_pd(&mpc_test_U.X[0])), _mm_mul_pd(_mm_loadu_pd(&Bu[0]),
    _mm_set1_pd(0.0)));

  /* MATLAB Function: '<S30>/FixedHorizonOptimizer' incorporates:
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/In6'
   *  Memory: '<S2>/LastPcov'
   *  Memory: '<S2>/last_x'
   */
  _mm_storeu_pd(&UnknownIn[0], tmp_4);
  UnknownIn[2] = (mpc_test_DW.last_x_PreviousInput[2] - mpc_test_U.X[2]) + Bu[2]
    * 0.0;
  UnknownIn[3] = Bu[3] * 0.0 + mpc_test_DW.last_x_PreviousInput[3];
  for (r1 = 0; r1 < 2; r1++) {
    a22 = 0.0;
    a21 = 0.0;
    Y_0 = 0.0;
    Y_1 = 0.0;
    for (b_C_tmp = 0; b_C_tmp < 2; b_C_tmp++) {
      r2 = b_C_tmp << 2;
      tmp_4 = _mm_set1_pd(Kinv[(r1 << 1) + b_C_tmp]);
      tmp_5 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Cm_0[r2]), tmp_4), _mm_set_pd
                         (a21, a22));
      _mm_storeu_pd(&tmp_6[0], tmp_5);
      a22 = tmp_6[0];
      a21 = tmp_6[1];
      tmp_4 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Cm_0[r2 + 2]), tmp_4),
                         _mm_set_pd(Y_1, Y_0));
      _mm_storeu_pd(&tmp_6[0], tmp_4);
      Y_0 = tmp_6[0];
      Y_1 = tmp_6[1];
    }

    L_tmp_7 = r1 << 2;
    L[L_tmp_7 + 3] = Y_1;
    L[L_tmp_7 + 2] = Y_0;
    L[L_tmp_7 + 1] = a21;
    L[L_tmp_7] = a22;
    y_innov[r1] = (mpc_test_U.In6[r1] - Y[r1]) - (((Cm[r1 + 2] * UnknownIn[1] +
      Cm[r1] * UnknownIn[0]) + Cm[r1 + 4] * UnknownIn[2]) + Cm[r1 + 6] *
      UnknownIn[3]);
    a22 = 0.0;
    a21 = 0.0;
    Y_0 = 0.0;
    Y_1 = 0.0;
    for (b_C_tmp = 0; b_C_tmp < 4; b_C_tmp++) {
      r2 = b_C_tmp << 2;
      L_tmp_tmp = L_tmp_7 + b_C_tmp;
      tmp_4 = _mm_set1_pd(c_A_tmp[L_tmp_tmp]);
      tmp_5 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&mpc_test_DW.LastPcov_PreviousInput[r2]), tmp_4), _mm_set_pd(a21, a22));
      _mm_storeu_pd(&tmp_6[0], tmp_5);
      a22 = tmp_6[0];
      a21 = tmp_6[1];
      tmp_4 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&mpc_test_DW.LastPcov_PreviousInput[r2 + 2]), tmp_4), _mm_set_pd(Y_1,
        Y_0));
      _mm_storeu_pd(&tmp_6[0], tmp_4);
      Y_0 = tmp_6[0];
      Y_1 = tmp_6[1];
      tmp_0[L_tmp_tmp] = 0.0;
    }

    tmp[L_tmp_7 + 3] = Y_1;
    tmp[L_tmp_7 + 2] = Y_0;
    tmp[L_tmp_7 + 1] = a21;
    tmp[L_tmp_7] = a22;
  }

  for (r1 = 0; r1 < 2; r1++) {
    b_C_tmp = r1 << 2;
    a22 = tmp_0[b_C_tmp];
    a21 = tmp_0[b_C_tmp + 1];
    Y_0 = tmp_0[b_C_tmp + 2];
    Y_1 = tmp_0[b_C_tmp + 3];
    for (r2 = 0; r2 < 2; r2++) {
      L_tmp_tmp = r2 << 2;
      tmp_4 = _mm_set1_pd(Kinv[(r1 << 1) + r2]);
      tmp_5 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&tmp[L_tmp_tmp]), tmp_4),
                         _mm_set_pd(a21, a22));
      _mm_storeu_pd(&tmp_6[0], tmp_5);
      a22 = tmp_6[0];
      a21 = tmp_6[1];
      tmp_4 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&tmp[L_tmp_tmp + 2]), tmp_4),
                         _mm_set_pd(Y_1, Y_0));
      _mm_storeu_pd(&tmp_6[0], tmp_4);
      Y_0 = tmp_6[0];
      Y_1 = tmp_6[1];
    }

    tmp_0[b_C_tmp + 3] = Y_1;
    tmp_0[b_C_tmp + 2] = Y_0;
    tmp_0[b_C_tmp + 1] = a21;
    tmp_0[b_C_tmp] = a22;
  }

  a22 = y_innov[1];
  a21 = y_innov[0];
  for (r1 = 0; r1 <= 2; r1 += 2) {
    tmp_4 = _mm_loadu_pd(&tmp_0[r1 + 4]);
    tmp_5 = _mm_loadu_pd(&tmp_0[r1]);
    tmp_3 = _mm_loadu_pd(&UnknownIn[r1]);
    _mm_storeu_pd(&c_A[r1], _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_4, _mm_set1_pd
      (a22)), _mm_mul_pd(tmp_5, _mm_set1_pd(a21))), tmp_3));
  }

  memset(&tmp_1[0], 0, sizeof(real_T) << 5U);
  memset(&Cm[0], 0, 168U * sizeof(real_T));
  Y[0] = 100.0;
  Y[1] = 1.0;
  for (r1 = 0; r1 < 20; r1++) {
    tmp_2[r1] = 1.0;
  }

  /* Memory: '<S2>/Memory' */
  for (r1 = 0; r1 < 8; r1++) {
    tmp_7[r1] = mpc_test_DW.Memory_PreviousInput[r1];
  }

  /* End of Memory: '<S2>/Memory' */

  /* MATLAB Function: '<S30>/FixedHorizonOptimizer' */
  memcpy(&c_A_tmp[0], &q[0], sizeof(real_T) << 3);
  memcpy(&r_0[0], &r[0], 25U * sizeof(real_T));
  memcpy(&t_0[0], &t[0], 40U * sizeof(real_T));

  /* Update for Memory: '<S2>/Memory' incorporates:
   *  Inport: '<Root>/In5'
   *  MATLAB Function: '<S30>/FixedHorizonOptimizer'
   *  UnitDelay: '<S2>/last_mv'
   */
  mpc_test_mpcblock_optimizer(rseq, vseq, c_A, mpc_test_DW.last_mv_DSTATE -
    mpc_test_U.U, tmp_7, b_Mlim, tmp_1, c_A_tmp, Cm, b_B, mpc_test_U.U, r_0, t_0,
    Y, v, tmp_2, b_A, Bu, Bv, b_C, Dv, b_Mrows, &a21, rtb_useq, &a22,
    mpc_test_DW.Memory_PreviousInput);

  /* MATLAB Function: '<S30>/FixedHorizonOptimizer' incorporates:
   *  Inport: '<Root>/In5'
   */
  a22 = a21 - mpc_test_U.U;
  for (r1 = 0; r1 < 4; r1++) {
    Y_0 = 0.0;
    Y_1 = 0.0;
    L_tmp_5 = 0.0;
    L_tmp_6 = 0.0;
    for (b_C_tmp = 0; b_C_tmp < 4; b_C_tmp++) {
      r2 = b_C_tmp << 2;
      tmp_4 = _mm_set1_pd(b_A[r2 + r1]);
      tmp_5 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&L_tmp[r2]), tmp_4), _mm_set_pd
                         (Y_1, Y_0));
      _mm_storeu_pd(&tmp_6[0], tmp_5);
      Y_0 = tmp_6[0];
      Y_1 = tmp_6[1];
      tmp_4 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&L_tmp[r2 + 2]), tmp_4),
                         _mm_set_pd(L_tmp_6, L_tmp_5));
      _mm_storeu_pd(&tmp_6[0], tmp_4);
      L_tmp_5 = tmp_6[0];
      L_tmp_6 = tmp_6[1];
      L_tmp_0[b_C_tmp + (r1 << 2)] = 0.0;
    }

    L_tmp_tmp = r1 << 2;
    L_tmp_1 = L_tmp_0[L_tmp_tmp];
    L_tmp_2 = L_tmp_0[L_tmp_tmp + 1];
    L_tmp_3 = L_tmp_0[L_tmp_tmp + 2];
    L_tmp_4 = L_tmp_0[L_tmp_tmp + 3];
    for (b_C_tmp = 0; b_C_tmp < 2; b_C_tmp++) {
      r2 = b_C_tmp << 2;
      tmp_4 = _mm_set1_pd(L[r2 + r1]);
      tmp_5 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Cm_0[r2]), tmp_4), _mm_set_pd
                         (L_tmp_2, L_tmp_1));
      _mm_storeu_pd(&tmp_6[0], tmp_5);
      L_tmp_1 = tmp_6[0];
      L_tmp_2 = tmp_6[1];
      tmp_4 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Cm_0[r2 + 2]), tmp_4),
                         _mm_set_pd(L_tmp_4, L_tmp_3));
      _mm_storeu_pd(&tmp_6[0], tmp_4);
      L_tmp_3 = tmp_6[0];
      L_tmp_4 = tmp_6[1];
    }

    L_tmp_0[L_tmp_tmp + 3] = L_tmp_4;
    L_tmp_0[L_tmp_tmp + 2] = L_tmp_3;
    L_tmp_0[L_tmp_tmp + 1] = L_tmp_2;
    L_tmp_0[L_tmp_tmp] = L_tmp_1;
    tmp_4 = _mm_add_pd(_mm_sub_pd(_mm_set_pd(Y_1, Y_0), _mm_set_pd(L_tmp_2,
      L_tmp_1)), _mm_loadu_pd(&CovMat[6 * r1]));
    _mm_storeu_pd(&Pk1[L_tmp_tmp], tmp_4);
    tmp_4 = _mm_add_pd(_mm_sub_pd(_mm_set_pd(L_tmp_6, L_tmp_5), _mm_set_pd
      (L_tmp_4, L_tmp_3)), _mm_loadu_pd(&CovMat[6 * r1 + 2]));
    _mm_storeu_pd(&Pk1[L_tmp_tmp + 2], tmp_4);
  }

  /* Update for UnitDelay: '<S2>/last_mv' incorporates:
   *  MATLAB Function: '<S30>/FixedHorizonOptimizer'
   */
  mpc_test_DW.last_mv_DSTATE = a21;

  /* MATLAB Function: '<S30>/FixedHorizonOptimizer' */
  a21 = UnknownIn[1];
  Y_0 = UnknownIn[0];
  Y_1 = UnknownIn[2];
  L_tmp_5 = UnknownIn[3];
  for (r1 = 0; r1 < 4; r1++) {
    /* MATLAB Function: '<S30>/FixedHorizonOptimizer' incorporates:
     *  Memory: '<S2>/LastPcov'
     */
    b_C_tmp = r1 << 2;
    tmp_4 = _mm_set1_pd(0.5);
    tmp_5 = _mm_mul_pd(_mm_add_pd(_mm_loadu_pd(&Pk1[b_C_tmp]), _mm_set_pd(Pk1[r1
      + 4], Pk1[r1])), tmp_4);
    _mm_storeu_pd(&mpc_test_DW.LastPcov_PreviousInput[b_C_tmp], tmp_5);
    tmp_4 = _mm_mul_pd(_mm_add_pd(_mm_loadu_pd(&Pk1[b_C_tmp + 2]), _mm_set_pd
      (Pk1[r1 + 12], Pk1[r1 + 8])), tmp_4);
    _mm_storeu_pd(&mpc_test_DW.LastPcov_PreviousInput[b_C_tmp + 2], tmp_4);
    UnknownIn[r1] = ((((b_A[r1 + 4] * a21 + b_A[r1] * Y_0) + b_A[r1 + 8] * Y_1)
                      + b_A[r1 + 12] * L_tmp_5) + Bu[r1] * a22) + Bv[r1];
  }

  /* MATLAB Function: '<S30>/FixedHorizonOptimizer' incorporates:
   *  Inport: '<Root>/In1'
   */
  a22 = 0.0;
  a21 = 0.0;
  Y_0 = 0.0;
  Y_1 = 0.0;
  for (r1 = 0; r1 < 2; r1++) {
    b_C_tmp = r1 << 2;
    tmp_4 = _mm_set1_pd(y_innov[r1]);
    tmp_5 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&L[b_C_tmp]), tmp_4), _mm_set_pd
                       (a21, a22));
    _mm_storeu_pd(&tmp_6[0], tmp_5);
    a22 = tmp_6[0];
    a21 = tmp_6[1];
    tmp_4 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&L[b_C_tmp + 2]), tmp_4),
                       _mm_set_pd(Y_1, Y_0));
    _mm_storeu_pd(&tmp_6[0], tmp_4);
    Y_0 = tmp_6[0];
    Y_1 = tmp_6[1];
  }

  c_A[3] = Y_1;
  c_A[2] = Y_0;
  c_A[1] = a21;
  c_A[0] = a22;
  tmp_4 = _mm_add_pd(_mm_add_pd(_mm_loadu_pd(&UnknownIn[0]), _mm_loadu_pd(&c_A[0])),
                     _mm_loadu_pd(&mpc_test_U.X[0]));

  /* Update for Memory: '<S2>/last_x' incorporates:
   *  Inport: '<Root>/In1'
   *  MATLAB Function: '<S30>/FixedHorizonOptimizer'
   */
  _mm_storeu_pd(&mpc_test_DW.last_x_PreviousInput[0], tmp_4);
  mpc_test_DW.last_x_PreviousInput[2] = (UnknownIn[2] + Y_0) + mpc_test_U.X[2];
  mpc_test_DW.last_x_PreviousInput[3] = UnknownIn[3] + Y_1;

  /* Matfile logging */
  //rt_UpdateTXYLogVars(mpc_test_M->rtwLogInfo, (&mpc_test_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.1s, 0.0s] */
    if ((rtmGetTFinal(mpc_test_M)!=-1) &&
        !((rtmGetTFinal(mpc_test_M)-mpc_test_M->Timing.taskTime0) >
          mpc_test_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(mpc_test_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++mpc_test_M->Timing.clockTick0)) {
    ++mpc_test_M->Timing.clockTickH0;
  }

  mpc_test_M->Timing.taskTime0 = mpc_test_M->Timing.clockTick0 *
    mpc_test_M->Timing.stepSize0 + mpc_test_M->Timing.clockTickH0 *
    mpc_test_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void mpc_test_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)mpc_test_M, 0,
                sizeof(RT_MODEL_mpc_test_T));
  rtmSetTFinal(mpc_test_M, 10.0);
  mpc_test_M->Timing.stepSize0 = 0.1;

  /* Setup for data logging */
  // {
  //   static RTWLogInfo rt_DataLoggingInfo;
  //   rt_DataLoggingInfo.loggingInterval = (NULL);
  //   mpc_test_M->rtwLogInfo = &rt_DataLoggingInfo;
  // }

  // /* Setup for data logging */
  // {
  //   rtliSetLogXSignalInfo(mpc_test_M->rtwLogInfo, (NULL));
  //   rtliSetLogXSignalPtrs(mpc_test_M->rtwLogInfo, (NULL));
  //   rtliSetLogT(mpc_test_M->rtwLogInfo, "tout");
  //   rtliSetLogX(mpc_test_M->rtwLogInfo, "");
  //   rtliSetLogXFinal(mpc_test_M->rtwLogInfo, "");
  //   rtliSetLogVarNameModifier(mpc_test_M->rtwLogInfo, "rt_");
  //   rtliSetLogFormat(mpc_test_M->rtwLogInfo, 4);
  //   rtliSetLogMaxRows(mpc_test_M->rtwLogInfo, 0);
  //   rtliSetLogDecimation(mpc_test_M->rtwLogInfo, 1);
  //   rtliSetLogY(mpc_test_M->rtwLogInfo, "");
  //   rtliSetLogYSignalInfo(mpc_test_M->rtwLogInfo, (NULL));
  //   rtliSetLogYSignalPtrs(mpc_test_M->rtwLogInfo, (NULL));
  // }

  // no data loging is set up, so the above code is commented out

  /* states (dwork) */
  (void) memset((void *)&mpc_test_DW, 0,
                sizeof(DW_mpc_test_T));

  /* external inputs */
  (void)memset(&mpc_test_U, 0, sizeof(ExtU_mpc_test_T));

  /* Matfile logging */
  //rt_StartDataLoggingWithStartTime(mpc_test_M->rtwLogInfo, 0.0, rtmGetTFinal
   // (mpc_test_M), mpc_test_M->Timing.stepSize0, (&rtmGetErrorStatus(mpc_test_M)));

  {
    int32_T i;

    /* InitializeConditions for Memory: '<S2>/LastPcov' */
    memcpy(&mpc_test_DW.LastPcov_PreviousInput[0],
           &mpc_test_P.LastPcov_InitialCondition[0], sizeof(real_T) << 4U);

    /* InitializeConditions for Memory: '<S2>/Memory' */
    for (i = 0; i < 8; i++) {
      mpc_test_DW.Memory_PreviousInput[i] = mpc_test_P.Memory_InitialCondition[i];
    }

    /* End of InitializeConditions for Memory: '<S2>/Memory' */

    /* InitializeConditions for UnitDelay: '<S2>/last_mv' */
    mpc_test_DW.last_mv_DSTATE = mpc_test_P.last_mv_InitialCondition;

    /* InitializeConditions for Memory: '<S2>/last_x' */
    mpc_test_DW.last_x_PreviousInput[0] = mpc_test_P.last_x_InitialCondition[0];
    mpc_test_DW.last_x_PreviousInput[1] = mpc_test_P.last_x_InitialCondition[1];
    mpc_test_DW.last_x_PreviousInput[2] = mpc_test_P.last_x_InitialCondition[2];
    mpc_test_DW.last_x_PreviousInput[3] = mpc_test_P.last_x_InitialCondition[3];
  }
}

/* Model terminate function */
void mpc_test_terminate(void)
{
  /* (no terminate code required) */
}
