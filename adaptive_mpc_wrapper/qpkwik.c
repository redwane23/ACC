/*
 * qpkwik.c
 *
 * Code generation for function 'qpkwik'
 *
 */

/* Include files */
#include "qpkwik.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include "xgerc.h"
#include "xnrm2.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Variable Definitions */
static const signed char iv[24] = {-1, -1, -1, 1, 1, 1, 0, -1, -1, 0, 1, 1,
                                   0,  0,  -1, 0, 0, 1, 0, 0,  0,  0, 0, 0};

/* Function Declarations */
static void DropConstraint(int kDrop, boolean_T iA[6], int *nA, int iC[6]);

static double KWIKfactor(const int iC[6], int nA, const double Linv[16],
                         double RLinv[16], double D[16], double H[16]);

/* Function Definitions */
static void DropConstraint(int kDrop, boolean_T iA[6], int *nA, int iC[6])
{
  int i;
  if (kDrop > 0) {
    int q0;
    iA[iC[kDrop - 1] - 1] = false;
    if (kDrop < *nA) {
      q0 = *nA;
      if (q0 < -2147483647) {
        q0 = MIN_int32_T;
      } else {
        q0--;
      }
      q0++;
      for (i = kDrop; i < q0; i++) {
        iC[i - 1] = iC[i];
      }
    }
    iC[*nA - 1] = 0;
    q0 = *nA;
    if (q0 < -2147483647) {
      q0 = MIN_int32_T;
    } else {
      q0--;
    }
    *nA = q0;
  }
}

static double KWIKfactor(const int iC[6], int nA, const double Linv[16],
                         double RLinv[16], double D[16], double H[16])
{
  __m128d r;
  double Q[16];
  double R[16];
  double TL[16];
  double tau[4];
  double work[4];
  double Status;
  int b_i;
  int c_i;
  int coltop;
  int d_i;
  int e_i;
  int exitg1;
  int i;
  int iaii;
  int ii;
  int knt;
  int scalarLB;
  boolean_T exitg2;
  Status = 1.0;
  memset(&RLinv[0], 0, 16U * sizeof(double));
  i = (unsigned char)nA;
  for (b_i = 0; b_i < i; b_i++) {
    c_i = b_i << 2;
    RLinv[c_i] = 0.0;
    RLinv[c_i + 1] = 0.0;
    RLinv[c_i + 2] = 0.0;
    RLinv[c_i + 3] = 0.0;
    for (d_i = 0; d_i < 4; d_i++) {
      __m128d r1;
      r = _mm_loadu_pd(&RLinv[c_i]);
      coltop = d_i << 2;
      r1 = _mm_set1_pd(iv[(iC[b_i] + 6 * d_i) - 1]);
      _mm_storeu_pd(&RLinv[c_i],
                    _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&Linv[coltop]), r1)));
      r = _mm_loadu_pd(&RLinv[c_i + 2]);
      _mm_storeu_pd(
          &RLinv[c_i + 2],
          _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&Linv[coltop + 2]), r1)));
    }
  }
  memcpy(&TL[0], &RLinv[0], 16U * sizeof(double));
  tau[0] = 0.0;
  work[0] = 0.0;
  tau[1] = 0.0;
  work[1] = 0.0;
  tau[2] = 0.0;
  work[2] = 0.0;
  tau[3] = 0.0;
  work[3] = 0.0;
  for (e_i = 0; e_i < 4; e_i++) {
    ii = (e_i << 2) + e_i;
    if (e_i + 1 < 4) {
      double atmp;
      double xnorm;
      atmp = TL[ii];
      iaii = ii + 2;
      tau[e_i] = 0.0;
      xnorm = xnrm2(3 - e_i, TL, ii + 2);
      if (xnorm != 0.0) {
        double a;
        double beta1;
        double d;
        d = TL[ii];
        a = fabs(d);
        beta1 = fabs(xnorm);
        if (a < beta1) {
          a /= beta1;
          beta1 *= sqrt(a * a + 1.0);
        } else if (a > beta1) {
          beta1 /= a;
          beta1 = a * sqrt(beta1 * beta1 + 1.0);
        } else if (rtIsNaN(beta1)) {
          beta1 = rtNaN;
        } else {
          beta1 = a * 1.4142135623730951;
        }
        if (d >= 0.0) {
          beta1 = -beta1;
        }
        if (fabs(beta1) < 1.0020841800044864E-292) {
          knt = 0;
          coltop = (ii - e_i) + 4;
          scalarLB = (((((coltop - ii) - 1) / 2) << 1) + ii) + 2;
          c_i = scalarLB - 2;
          do {
            knt++;
            for (b_i = iaii; b_i <= c_i; b_i += 2) {
              r = _mm_loadu_pd(&TL[b_i - 1]);
              _mm_storeu_pd(&TL[b_i - 1],
                            _mm_mul_pd(_mm_set1_pd(9.9792015476736E+291), r));
            }
            for (b_i = scalarLB; b_i <= coltop; b_i++) {
              TL[b_i - 1] *= 9.9792015476736E+291;
            }
            beta1 *= 9.9792015476736E+291;
            atmp *= 9.9792015476736E+291;
          } while ((fabs(beta1) < 1.0020841800044864E-292) && (knt < 20));
          xnorm = fabs(atmp);
          beta1 = fabs(xnrm2(3 - e_i, TL, ii + 2));
          if (xnorm < beta1) {
            xnorm /= beta1;
            beta1 *= sqrt(xnorm * xnorm + 1.0);
          } else if (xnorm > beta1) {
            beta1 /= xnorm;
            beta1 = xnorm * sqrt(beta1 * beta1 + 1.0);
          } else if (rtIsNaN(beta1)) {
            beta1 = rtNaN;
          } else {
            beta1 = xnorm * 1.4142135623730951;
          }
          if (atmp >= 0.0) {
            beta1 = -beta1;
          }
          tau[e_i] = (beta1 - atmp) / beta1;
          xnorm = 1.0 / (atmp - beta1);
          c_i = scalarLB - 2;
          for (b_i = iaii; b_i <= c_i; b_i += 2) {
            r = _mm_loadu_pd(&TL[b_i - 1]);
            _mm_storeu_pd(&TL[b_i - 1], _mm_mul_pd(_mm_set1_pd(xnorm), r));
          }
          for (b_i = scalarLB; b_i <= coltop; b_i++) {
            TL[b_i - 1] *= xnorm;
          }
          for (b_i = 0; b_i < knt; b_i++) {
            beta1 *= 1.0020841800044864E-292;
          }
          atmp = beta1;
        } else {
          tau[e_i] = (beta1 - d) / beta1;
          xnorm = 1.0 / (d - beta1);
          c_i = (ii - e_i) + 4;
          coltop = (((((c_i - ii) - 1) / 2) << 1) + ii) + 2;
          scalarLB = coltop - 2;
          for (b_i = iaii; b_i <= scalarLB; b_i += 2) {
            r = _mm_loadu_pd(&TL[b_i - 1]);
            _mm_storeu_pd(&TL[b_i - 1], _mm_mul_pd(_mm_set1_pd(xnorm), r));
          }
          for (b_i = coltop; b_i <= c_i; b_i++) {
            TL[b_i - 1] *= xnorm;
          }
          atmp = beta1;
        }
      }
      TL[ii] = 1.0;
      if (tau[e_i] != 0.0) {
        knt = 4 - e_i;
        c_i = (ii - e_i) + 3;
        while ((knt > 0) && (TL[c_i] == 0.0)) {
          knt--;
          c_i--;
        }
        c_i = 3 - e_i;
        exitg2 = false;
        while ((!exitg2) && (c_i > 0)) {
          coltop = (ii + ((c_i - 1) << 2)) + 4;
          scalarLB = coltop;
          do {
            exitg1 = 0;
            if (scalarLB + 1 <= coltop + knt) {
              if (TL[scalarLB] != 0.0) {
                exitg1 = 1;
              } else {
                scalarLB++;
              }
            } else {
              c_i--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        knt = 0;
        c_i = 0;
      }
      if (knt > 0) {
        xgemv(knt, c_i, TL, ii + 5, TL, ii + 1, work);
        xgerc(knt, c_i, -tau[e_i], ii + 1, work, TL, ii + 5);
      }
      TL[ii] = atmp;
    } else {
      tau[3] = 0.0;
    }
  }
  ii = 3;
  for (d_i = 0; d_i < 4; d_i++) {
    for (b_i = 0; b_i <= d_i; b_i++) {
      coltop = b_i + (d_i << 2);
      R[coltop] = TL[coltop];
    }
    c_i = d_i + 2;
    if (c_i <= 4) {
      memset(&R[(d_i * 4 + c_i) + -1], 0,
             (unsigned int)(-c_i + 5) * sizeof(double));
    }
    work[d_i] = 0.0;
  }
  for (d_i = 3; d_i >= 0; d_i--) {
    iaii = d_i + (d_i << 2);
    if (d_i + 1 < 4) {
      TL[iaii] = 1.0;
      if (tau[ii] != 0.0) {
        knt = 4 - d_i;
        c_i = (iaii - d_i) + 3;
        while ((knt > 0) && (TL[c_i] == 0.0)) {
          knt--;
          c_i--;
        }
        c_i = 3 - d_i;
        exitg2 = false;
        while ((!exitg2) && (c_i > 0)) {
          coltop = (iaii + ((c_i - 1) << 2)) + 4;
          scalarLB = coltop;
          do {
            exitg1 = 0;
            if (scalarLB + 1 <= coltop + knt) {
              if (TL[scalarLB] != 0.0) {
                exitg1 = 1;
              } else {
                scalarLB++;
              }
            } else {
              c_i--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        knt = 0;
        c_i = 0;
      }
      if (knt > 0) {
        xgemv(knt, c_i, TL, iaii + 5, TL, iaii + 1, work);
        xgerc(knt, c_i, -tau[ii], iaii + 1, work, TL, iaii + 5);
      }
      c_i = iaii + 2;
      coltop = (iaii - d_i) + 4;
      scalarLB = (((((coltop - iaii) - 1) / 2) << 1) + iaii) + 2;
      knt = scalarLB - 2;
      for (b_i = c_i; b_i <= knt; b_i += 2) {
        r = _mm_loadu_pd(&TL[b_i - 1]);
        _mm_storeu_pd(&TL[b_i - 1], _mm_mul_pd(_mm_set1_pd(-tau[ii]), r));
      }
      for (b_i = scalarLB; b_i <= coltop; b_i++) {
        TL[b_i - 1] *= -tau[ii];
      }
    }
    TL[iaii] = 1.0 - tau[ii];
    for (b_i = 0; b_i < d_i; b_i++) {
      TL[(iaii - b_i) - 1] = 0.0;
    }
    ii = d_i - 1;
  }
  for (b_i = 0; b_i < 4; b_i++) {
    c_i = b_i << 2;
    Q[c_i] = TL[c_i];
    Q[c_i + 1] = TL[c_i + 1];
    Q[c_i + 2] = TL[c_i + 2];
    Q[c_i + 3] = TL[c_i + 3];
  }
  c_i = 0;
  do {
    exitg1 = 0;
    if (c_i <= (unsigned char)nA - 1) {
      if (fabs(R[c_i + (c_i << 2)]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        c_i++;
      }
    } else {
      for (b_i = 0; b_i < 4; b_i++) {
        c_i = b_i << 2;
        for (d_i = 0; d_i < 4; d_i++) {
          coltop = d_i << 2;
          TL[b_i + coltop] =
              ((Linv[c_i] * Q[coltop] + Linv[c_i + 1] * Q[coltop + 1]) +
               Linv[c_i + 2] * Q[coltop + 2]) +
              Linv[c_i + 3] * Q[coltop + 3];
        }
      }
      memset(&RLinv[0], 0, 16U * sizeof(double));
      for (e_i = nA; e_i >= 1; e_i--) {
        scalarLB = (e_i - 1) << 2;
        c_i = (e_i + scalarLB) - 1;
        RLinv[c_i] = 1.0;
        for (b_i = e_i; b_i <= nA; b_i++) {
          coltop = (e_i + ((b_i - 1) << 2)) - 1;
          RLinv[coltop] /= R[c_i];
        }
        if (e_i > 1) {
          for (b_i = 0; b_i <= e_i - 2; b_i++) {
            for (d_i = e_i; d_i <= nA; d_i++) {
              c_i = (d_i - 1) << 2;
              coltop = b_i + c_i;
              RLinv[coltop] -= R[b_i + scalarLB] * RLinv[(e_i + c_i) - 1];
            }
          }
        }
      }
      if (nA > 2147483646) {
        c_i = MAX_int32_T;
      } else {
        c_i = nA + 1;
      }
      for (b_i = 0; b_i < 4; b_i++) {
        for (d_i = b_i + 1; d_i < 5; d_i++) {
          coltop = b_i + ((d_i - 1) << 2);
          H[coltop] = 0.0;
          for (e_i = c_i; e_i < 5; e_i++) {
            scalarLB = (e_i - 1) << 2;
            H[coltop] -= TL[b_i + scalarLB] * TL[(d_i + scalarLB) - 1];
          }
          H[(d_i + (b_i << 2)) - 1] = H[coltop];
        }
      }
      for (b_i = 0; b_i < i; b_i++) {
        for (d_i = 0; d_i < 4; d_i++) {
          c_i = d_i + (b_i << 2);
          D[c_i] = 0.0;
          for (e_i = b_i + 1; e_i <= nA; e_i++) {
            coltop = (e_i - 1) << 2;
            D[c_i] += TL[d_i + coltop] * RLinv[b_i + coltop];
          }
        }
      }
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  return Status;
}

int qpkwik(const double Linv[16], const double Hinv[16], const double f[4],
           const double b[6], boolean_T iA[6], double x[4], double lambda[6])
{
  __m128d b_r;
  __m128d r1;
  __m128d r2;
  double D[16];
  double H[16];
  double RLinv[16];
  double U[16];
  double Opt[8];
  double Rhs[8];
  double cTol[6];
  double r[4];
  double z[4];
  double cMin;
  double lambdamin;
  double rMin;
  double t;
  double t1;
  int iC[6];
  int U_tmp;
  int b_i;
  int i;
  int iSave;
  int idx;
  int k;
  int kDrop;
  int nA;
  int status;
  boolean_T ColdReset;
  boolean_T cTolComputed;
  boolean_T guard1;
  x[0] = 0.0;
  x[1] = 0.0;
  x[2] = 0.0;
  x[3] = 0.0;
  status = 1;
  r[0] = 0.0;
  r[1] = 0.0;
  r[2] = 0.0;
  r[3] = 0.0;
  rMin = 0.0;
  cTolComputed = false;
  for (i = 0; i < 6; i++) {
    lambda[i] = 0.0;
    cTol[i] = 1.0;
    iC[i] = 0;
  }
  nA = 0;
  for (i = 0; i < 6; i++) {
    if (iA[i]) {
      nA++;
      iC[nA - 1] = i + 1;
    }
  }
  guard1 = false;
  if (nA > 0) {
    int exitg3;
    memset(&Opt[0], 0, 8U * sizeof(double));
    Rhs[0] = f[0];
    Rhs[4] = 0.0;
    Rhs[1] = f[1];
    Rhs[5] = 0.0;
    Rhs[2] = f[2];
    Rhs[6] = 0.0;
    Rhs[3] = f[3];
    Rhs[7] = 0.0;
    ColdReset = false;
    do {
      exitg3 = 0;
      if ((nA > 0) && (status <= 120)) {
        lambdamin = KWIKfactor(iC, nA, Linv, RLinv, D, H);
        if (lambdamin < 0.0) {
          if (ColdReset) {
            status = -2;
            exitg3 = 1;
          } else {
            nA = 0;
            for (i = 0; i < 6; i++) {
              iA[i] = false;
              iC[i] = 0;
            }
            ColdReset = true;
          }
        } else {
          iSave = (unsigned char)nA;
          for (i = 0; i < iSave; i++) {
            Rhs[i + 4] = b[iC[i] - 1];
            for (b_i = i + 1; b_i <= nA; b_i++) {
              idx = (b_i + (i << 2)) - 1;
              U[idx] = 0.0;
              for (k = 0; k < iSave; k++) {
                U_tmp = k << 2;
                U[idx] += RLinv[(b_i + U_tmp) - 1] * RLinv[i + U_tmp];
              }
              U[i + ((b_i - 1) << 2)] = U[idx];
            }
          }
          for (i = 0; i < 4; i++) {
            Opt[i] = ((H[i] * Rhs[0] + H[i + 4] * Rhs[1]) + H[i + 8] * Rhs[2]) +
                     H[i + 12] * Rhs[3];
            for (b_i = 0; b_i < iSave; b_i++) {
              Opt[i] += D[i + (b_i << 2)] * Rhs[b_i + 4];
            }
          }
          lambdamin = -1.0E-12;
          kDrop = 0;
          for (b_i = 0; b_i < iSave; b_i++) {
            idx = b_i << 2;
            Opt[b_i + 4] = ((D[idx] * Rhs[0] + D[idx + 1] * Rhs[1]) +
                            D[idx + 2] * Rhs[2]) +
                           D[idx + 3] * Rhs[3];
            for (i = 0; i < iSave; i++) {
              Opt[b_i + 4] += U[b_i + (i << 2)] * Rhs[i + 4];
            }
            t = Opt[b_i + 4];
            lambda[iC[b_i] - 1] = t;
            if ((t < lambdamin) && (b_i + 1 <= nA)) {
              kDrop = b_i + 1;
              lambdamin = t;
            }
          }
          if (kDrop <= 0) {
            x[0] = Opt[0];
            x[1] = Opt[1];
            x[2] = Opt[2];
            x[3] = Opt[3];
            exitg3 = 2;
          } else {
            status++;
            if (status > 5) {
              nA = 0;
              for (i = 0; i < 6; i++) {
                iA[i] = false;
                iC[i] = 0;
              }
              ColdReset = true;
            } else {
              lambda[iC[kDrop - 1] - 1] = 0.0;
              DropConstraint(kDrop, iA, &nA, iC);
            }
          }
        }
      } else {
        exitg3 = 2;
      }
    } while (exitg3 == 0);
    if (exitg3 != 1) {
      if (nA <= 0) {
        for (i = 0; i < 6; i++) {
          lambda[i] = 0.0;
        }
        lambdamin = f[0];
        t = f[1];
        cMin = f[2];
        t1 = f[3];
        for (i = 0; i <= 2; i += 2) {
          b_r = _mm_loadu_pd(&Hinv[i]);
          b_r = _mm_mul_pd(b_r, _mm_set1_pd(-1.0));
          r1 = _mm_mul_pd(b_r, _mm_set1_pd(lambdamin));
          b_r = _mm_loadu_pd(&Hinv[i + 4]);
          b_r = _mm_mul_pd(b_r, _mm_set1_pd(-1.0));
          b_r = _mm_mul_pd(b_r, _mm_set1_pd(t));
          r2 = _mm_add_pd(r1, b_r);
          b_r = _mm_loadu_pd(&Hinv[i + 8]);
          b_r = _mm_mul_pd(b_r, _mm_set1_pd(-1.0));
          b_r = _mm_mul_pd(b_r, _mm_set1_pd(cMin));
          r1 = _mm_add_pd(r2, b_r);
          b_r = _mm_loadu_pd(&Hinv[i + 12]);
          b_r = _mm_mul_pd(b_r, _mm_set1_pd(-1.0));
          b_r = _mm_mul_pd(b_r, _mm_set1_pd(t1));
          b_r = _mm_add_pd(r1, b_r);
          _mm_storeu_pd(&x[i], b_r);
        }
      }
      guard1 = true;
    }
  } else {
    lambdamin = f[0];
    cMin = f[1];
    t1 = f[2];
    t = f[3];
    for (i = 0; i <= 2; i += 2) {
      b_r = _mm_loadu_pd(&Hinv[i]);
      b_r = _mm_mul_pd(b_r, _mm_set1_pd(-1.0));
      r1 = _mm_mul_pd(b_r, _mm_set1_pd(lambdamin));
      b_r = _mm_loadu_pd(&Hinv[i + 4]);
      b_r = _mm_mul_pd(b_r, _mm_set1_pd(-1.0));
      b_r = _mm_mul_pd(b_r, _mm_set1_pd(cMin));
      r1 = _mm_add_pd(r1, b_r);
      b_r = _mm_loadu_pd(&Hinv[i + 8]);
      b_r = _mm_mul_pd(b_r, _mm_set1_pd(-1.0));
      b_r = _mm_mul_pd(b_r, _mm_set1_pd(t1));
      r1 = _mm_add_pd(r1, b_r);
      b_r = _mm_loadu_pd(&Hinv[i + 12]);
      b_r = _mm_mul_pd(b_r, _mm_set1_pd(-1.0));
      b_r = _mm_mul_pd(b_r, _mm_set1_pd(t));
      b_r = _mm_add_pd(r1, b_r);
      _mm_storeu_pd(&x[i], b_r);
    }
    guard1 = true;
  }
  if (guard1) {
    double Xnorm0;
    boolean_T exitg2;
    Xnorm0 = b_norm(x);
    exitg2 = false;
    while ((!exitg2) && (status <= 120)) {
      int kNext;
      boolean_T exitg4;
      cMin = -1.0E-6;
      kNext = -1;
      for (b_i = 0; b_i < 6; b_i++) {
        if (!cTolComputed) {
          z[0] = fabs((double)iv[b_i] * x[0]);
          z[1] = fabs((double)iv[b_i + 6] * x[1]);
          z[2] = fabs((double)iv[b_i + 12] * x[2]);
          z[3] = fabs((double)iv[b_i + 18] * x[3]);
          if (!rtIsNaN(z[0])) {
            idx = 1;
          } else {
            idx = 0;
            U_tmp = 2;
            exitg4 = false;
            while ((!exitg4) && (U_tmp < 5)) {
              if (!rtIsNaN(z[U_tmp - 1])) {
                idx = U_tmp;
                exitg4 = true;
              } else {
                U_tmp++;
              }
            }
          }
          if (idx == 0) {
            lambdamin = z[0];
          } else {
            lambdamin = z[idx - 1];
            idx++;
            for (i = idx; i < 5; i++) {
              t = z[i - 1];
              if (lambdamin < t) {
                lambdamin = t;
              }
            }
          }
          cTol[b_i] = fmax(cTol[b_i], lambdamin);
        }
        if (!iA[b_i]) {
          lambdamin = (((((double)iv[b_i] * x[0] + (double)iv[b_i + 6] * x[1]) +
                         (double)iv[b_i + 12] * x[2]) +
                        (double)iv[b_i + 18] * x[3]) -
                       b[b_i]) /
                      cTol[b_i];
          if (lambdamin < cMin) {
            cMin = lambdamin;
            kNext = b_i;
          }
        }
      }
      cTolComputed = true;
      if (kNext + 1 <= 0) {
        exitg2 = true;
      } else if (status == 120) {
        status = 0;
        exitg2 = true;
      } else {
        int exitg1;
        do {
          exitg1 = 0;
          if ((kNext + 1 > 0) && (status <= 120)) {
            signed char AcRow[4];
            boolean_T guard2;
            AcRow[0] = iv[kNext];
            AcRow[1] = iv[kNext + 6];
            AcRow[2] = iv[kNext + 12];
            AcRow[3] = iv[kNext + 18];
            guard2 = false;
            if (nA == 0) {
              memset(&z[0], 0, sizeof(double) << 2);
              for (i = 0; i < 4; i++) {
                b_r = _mm_loadu_pd(&z[0]);
                idx = i << 2;
                r1 = _mm_set1_pd(AcRow[i]);
                _mm_storeu_pd(
                    &z[0],
                    _mm_add_pd(b_r, _mm_mul_pd(_mm_loadu_pd(&Hinv[idx]), r1)));
                b_r = _mm_loadu_pd(&z[2]);
                _mm_storeu_pd(
                    &z[2],
                    _mm_add_pd(b_r,
                               _mm_mul_pd(_mm_loadu_pd(&Hinv[idx + 2]), r1)));
              }
              guard2 = true;
            } else {
              lambdamin = KWIKfactor(iC, nA, Linv, RLinv, D, H);
              if (lambdamin <= 0.0) {
                status = -2;
                exitg1 = 1;
              } else {
                for (i = 0; i <= 14; i += 2) {
                  b_r = _mm_loadu_pd(&H[i]);
                  _mm_storeu_pd(&U[i], _mm_mul_pd(b_r, _mm_set1_pd(-1.0)));
                }
                memset(&z[0], 0, sizeof(double) << 2);
                for (i = 0; i < 4; i++) {
                  idx = i << 2;
                  b_r = _mm_loadu_pd(&U[idx]);
                  r1 = _mm_loadu_pd(&z[0]);
                  r2 = _mm_set1_pd(AcRow[i]);
                  _mm_storeu_pd(&z[0], _mm_add_pd(r1, _mm_mul_pd(b_r, r2)));
                  b_r = _mm_loadu_pd(&U[idx + 2]);
                  r1 = _mm_loadu_pd(&z[2]);
                  _mm_storeu_pd(&z[2], _mm_add_pd(r1, _mm_mul_pd(b_r, r2)));
                }
                idx = (unsigned char)nA;
                for (i = 0; i < idx; i++) {
                  U_tmp = i << 2;
                  r[i] = (((double)AcRow[0] * D[U_tmp] +
                           (double)AcRow[1] * D[U_tmp + 1]) +
                          (double)AcRow[2] * D[U_tmp + 2]) +
                         (double)AcRow[3] * D[U_tmp + 3];
                }
                guard2 = true;
              }
            }
            if (guard2) {
              boolean_T isT1Inf;
              kDrop = 0;
              t1 = 0.0;
              isT1Inf = true;
              ColdReset = true;
              if (nA > 0) {
                idx = 0;
                exitg4 = false;
                while ((!exitg4) && (idx <= (unsigned char)nA - 1)) {
                  if (r[idx] >= 1.0E-12) {
                    ColdReset = false;
                    exitg4 = true;
                  } else {
                    idx++;
                  }
                }
              }
              if ((nA != 0) && (!ColdReset)) {
                idx = (unsigned char)nA;
                for (i = 0; i < idx; i++) {
                  lambdamin = r[i];
                  if (lambdamin > 1.0E-12) {
                    lambdamin = lambda[iC[i] - 1] / lambdamin;
                    if ((kDrop == 0) || (lambdamin < rMin)) {
                      rMin = lambdamin;
                      kDrop = i + 1;
                    }
                  }
                }
                if (kDrop > 0) {
                  t1 = rMin;
                  isT1Inf = false;
                }
              }
              lambdamin = ((z[0] * (double)AcRow[0] + z[1] * (double)AcRow[1]) +
                           z[2] * (double)AcRow[2]) +
                          z[3] * (double)AcRow[3];
              if (lambdamin <= 0.0) {
                lambdamin = 0.0;
                ColdReset = true;
              } else {
                lambdamin =
                    (b[kNext] -
                     ((((double)AcRow[0] * x[0] + (double)AcRow[1] * x[1]) +
                       (double)AcRow[2] * x[2]) +
                      (double)AcRow[3] * x[3])) /
                    lambdamin;
                ColdReset = false;
              }
              if (isT1Inf && ColdReset) {
                status = -1;
                exitg1 = 1;
              } else {
                if (ColdReset) {
                  t = t1;
                } else if (isT1Inf) {
                  t = lambdamin;
                } else if (t1 < lambdamin) {
                  t = t1;
                } else {
                  t = lambdamin;
                }
                idx = (unsigned char)nA;
                for (i = 0; i < idx; i++) {
                  U_tmp = iC[i];
                  lambda[U_tmp - 1] -= t * r[i];
                  if (lambda[U_tmp - 1] < 0.0) {
                    lambda[U_tmp - 1] = 0.0;
                  }
                }
                lambda[kNext] += t;
                if (fabs(t - t1) < 2.2204460492503131E-16) {
                  DropConstraint(kDrop, iA, &nA, iC);
                }
                if (!ColdReset) {
                  b_r = _mm_loadu_pd(&z[0]);
                  r1 = _mm_loadu_pd(&x[0]);
                  r2 = _mm_set1_pd(t);
                  _mm_storeu_pd(&x[0], _mm_add_pd(r1, _mm_mul_pd(r2, b_r)));
                  b_r = _mm_loadu_pd(&z[2]);
                  r1 = _mm_loadu_pd(&x[2]);
                  _mm_storeu_pd(&x[2], _mm_add_pd(r1, _mm_mul_pd(r2, b_r)));
                  if (fabs(t - lambdamin) < 2.2204460492503131E-16) {
                    if (nA == 4) {
                      status = -1;
                      exitg1 = 1;
                    } else {
                      if (nA > 2147483646) {
                        nA = MAX_int32_T;
                      } else {
                        nA++;
                      }
                      iC[nA - 1] = kNext + 1;
                      idx = nA - 1;
                      exitg4 = false;
                      while ((!exitg4) && (idx + 1 > 1)) {
                        U_tmp = iC[idx - 1];
                        if (iC[idx] > U_tmp) {
                          exitg4 = true;
                        } else {
                          iSave = iC[idx];
                          iC[idx] = U_tmp;
                          iC[idx - 1] = iSave;
                          idx--;
                        }
                      }
                      iA[kNext] = true;
                      kNext = -1;
                      status++;
                    }
                  } else {
                    status++;
                  }
                } else {
                  status++;
                }
              }
            }
          } else {
            lambdamin = b_norm(x);
            if (fabs(lambdamin - Xnorm0) > 0.001) {
              Xnorm0 = lambdamin;
              for (i = 0; i < 6; i++) {
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
  return status;
}

/* End of code generation (qpkwik.c) */
