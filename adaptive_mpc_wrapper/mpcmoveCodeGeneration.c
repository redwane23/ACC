/*
 * mpcmoveCodeGeneration.c
 *
 * Code generation for function 'mpcmoveCodeGeneration'
 *
 */

/* Include files */
#include "mpcmoveCodeGeneration.h"
#include "adaptive_mpc_wrapper_types.h"
#include "minOrMax.h"
#include "qpkwik.h"
#include "rt_nonfinite.h"
#include "trisolve.h"
#include "xpotrf.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
double mpcmoveCodeGeneration(
    struct5_T *statedata, const double onlinedata_signals_ym[2],
    const double onlinedata_signals_ref[2], double onlinedata_signals_md,
    const double onlinedata_model_A[9], const double onlinedata_model_B[6],
    const double onlinedata_model_C[6], const double onlinedata_model_D[4],
    const double onlinedata_model_X[3], const double onlinedata_model_U[2],
    const double onlinedata_model_Y[2], const double onlinedata_model_DX[3])
{
  static const double dv2[24] = {-0.00031731173050453574,
                                 0.0093653765389909282,
                                 0.18126924692201815,
                                 0.0,
                                 0.1,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.1,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0};
  static const double dv1[16] = {1.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 -0.1,
                                 1.0,
                                 0.0,
                                 0.0,
                                 -0.0046826882694954641,
                                 0.090634623461009076,
                                 0.81873075307798182,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 1.0};
  static const double dv3[16] = {4790.2718241573075,
                                 3767.094773531147,
                                 2890.4274653344855,
                                 0.0,
                                 3767.094773531147,
                                 2971.0418849175471,
                                 2285.2963721190081,
                                 0.0,
                                 2890.4274653344855,
                                 2285.2963721190081,
                                 1764.080946593258,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 100000.0};
  static const signed char A[169] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
      1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
      1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  static const signed char iv4[39] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const signed char iv5[39] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const signed char iv1[12] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1};
  static const signed char b_iv[8] = {1, 0, 0, 1, 0, 0, 0, 1};
  static const signed char Mrows[6] = {53, 54, 55, 66, 67, 68};
  static const signed char iv2[6] = {3, 3, 3, 5, 5, 5};
  static const signed char iv6[6] = {-1, -1, -1, 1, 1, 1};
  __m128d b_r;
  __m128d b_r2;
  __m128d r1;
  __m128d r3;
  __m128d r4;
  double Hv[728];
  double Su[338];
  double b_Sx[104];
  double Kv[84];
  double SuJm[78];
  double WySuJm[78];
  double I2Jm[39];
  double WduJm[39];
  double WuI2Jm[39];
  double CovMat[36];
  double b_B[30];
  double c_B[30];
  double v[28];
  double Su1[26];
  double r[26];
  double B[24];
  double Linv[16];
  double Pcov[16];
  double b_L[16];
  double b_L_tmp[16];
  double dv[16];
  double Sx[12];
  double b_SuJm[9];
  double dv4[9];
  double Bv[8];
  double CA[8];
  double L[8];
  double L_tmp[8];
  double b_CA[8];
  double b_statedata[8];
  double c_statedata[8];
  double b[6];
  double b_b[6];
  double Bu[4];
  double Kinv[4];
  double d_B[4];
  double x[4];
  double xk[4];
  double xoff[4];
  double X0[3];
  double b_Su1[3];
  double dv5[3];
  double Sum[2];
  double y_innov[2];
  double U_idx_0;
  double a21;
  double a22;
  double d;
  double d1;
  double s;
  double u;
  int Kinv_tmp;
  int b_i;
  int b_r1;
  int i;
  int i1;
  int kidx;
  int r2;
  short ixw;
  signed char a[169];
  signed char UnknownIn[5];
  boolean_T iA[6];
  boolean_T guard1;
  memcpy(&dv[0], &dv1[0], 16U * sizeof(double));
  memcpy(&B[0], &dv2[0], 24U * sizeof(double));
  for (i = 0; i < 8; i++) {
    CA[i] = b_iv[i];
  }
  for (i = 0; i < 12; i++) {
    Sx[i] = iv1[i];
  }
  for (i = 0; i < 6; i++) {
    b[i] = onlinedata_model_B[i];
  }
  for (i = 0; i < 3; i++) {
    r2 = i << 1;
    CA[r2] = onlinedata_model_C[r2];
    CA[r2 + 1] = onlinedata_model_C[r2 + 1];
    r2 = i << 2;
    dv[r2] = onlinedata_model_A[3 * i];
    dv[r2 + 1] = onlinedata_model_A[3 * i + 1];
    dv[r2 + 2] = onlinedata_model_A[3 * i + 2];
    B[i] = b[i];
    B[i + 4] = b[i + 3];
  }
  for (i = 0; i < 2; i++) {
    Sx[i + 2] = onlinedata_model_D[i + 2];
    r2 = (i + 1) << 2;
    kidx = i << 2;
    Bv[kidx] = B[r2];
    Bv[kidx + 1] = B[r2 + 1];
    Bv[kidx + 2] = B[r2 + 2];
    Bv[kidx + 3] = B[r2 + 3];
  }
  UnknownIn[0] = 1;
  UnknownIn[1] = 2;
  UnknownIn[2] = 4;
  UnknownIn[3] = 5;
  UnknownIn[4] = 6;
  for (i = 0; i < 5; i++) {
    r2 = UnknownIn[i] - 1;
    kidx = r2 << 2;
    b_B[6 * i] = B[kidx];
    b_B[6 * i + 1] = B[kidx + 1];
    b_B[6 * i + 2] = B[kidx + 2];
    b_B[6 * i + 3] = B[kidx + 3];
    r2 <<= 1;
    b_B[6 * i + 4] = Sx[r2];
    b_B[6 * i + 5] = Sx[r2 + 1];
  }
  for (i = 0; i < 4; i++) {
    for (b_i = 0; b_i < 5; b_i++) {
      c_B[b_i + 5 * i] = B[i + ((UnknownIn[b_i] - 1) << 2)];
    }
  }
  for (i = 0; i < 2; i++) {
    for (b_i = 0; b_i < 5; b_i++) {
      c_B[b_i + 5 * (i + 4)] = Sx[i + ((UnknownIn[b_i] - 1) << 1)];
    }
  }
  memset(&CovMat[0], 0, 36U * sizeof(double));
  Bu[0] = B[0];
  Bu[1] = B[1];
  Bu[2] = B[2];
  Bu[3] = B[3];
  xoff[3] = 0.0;
  Bv[4] = onlinedata_model_DX[0];
  Bv[5] = onlinedata_model_DX[1];
  Bv[6] = onlinedata_model_DX[2];
  U_idx_0 = onlinedata_model_U[0];
  for (i = 0; i < 6; i++) {
    r2 = 6 * i + 2;
    kidx = 6 * i + 4;
    for (b_i = 0; b_i < 5; b_i++) {
      b_r = _mm_loadu_pd(&b_B[6 * b_i]);
      r1 = _mm_loadu_pd(&CovMat[6 * i]);
      b_r2 = _mm_set1_pd(c_B[b_i + 5 * i]);
      _mm_storeu_pd(&CovMat[6 * i], _mm_add_pd(r1, _mm_mul_pd(b_r, b_r2)));
      b_r = _mm_loadu_pd(&b_B[6 * b_i + 2]);
      r1 = _mm_loadu_pd(&CovMat[r2]);
      _mm_storeu_pd(&CovMat[r2], _mm_add_pd(r1, _mm_mul_pd(b_r, b_r2)));
      b_r = _mm_loadu_pd(&b_B[6 * b_i + 4]);
      r1 = _mm_loadu_pd(&CovMat[kidx]);
      _mm_storeu_pd(&CovMat[kidx], _mm_add_pd(r1, _mm_mul_pd(b_r, b_r2)));
    }
    a21 = iv2[i];
    b[i] = a21;
    if (Mrows[i] <= 65) {
      a21 += 0.0 - U_idx_0;
      b[i] = a21;
    } else {
      a21 -= 0.0 - U_idx_0;
      b[i] = a21;
    }
  }
  xoff[0] = onlinedata_model_X[0];
  xoff[1] = onlinedata_model_X[1];
  xoff[2] = onlinedata_model_X[2];
  memset(&r[0], 0, 26U * sizeof(double));
  b_r = _mm_loadu_pd(&onlinedata_model_Y[0]);
  b_r = _mm_sub_pd(_mm_loadu_pd(&onlinedata_signals_ref[0]), b_r);
  _mm_storeu_pd(&Sum[0], b_r);
  _mm_storeu_pd(&r[0], b_r);
  a21 = Sum[0];
  s = Sum[1];
  for (i = 0; i < 12; i++) {
    r2 = (i + 1) << 1;
    r[r2] = a21;
    r[r2 + 1] = s;
  }
  for (i = 0; i < 28; i++) {
    v[i] = 1.0;
  }
  a21 = onlinedata_signals_md - onlinedata_model_U[1];
  v[0] = a21;
  for (i = 0; i < 13; i++) {
    v[(i + 1) << 1] = a21;
  }
  for (i = 0; i < 2; i++) {
    r2 = i << 2;
    L_tmp[r2] = CA[i];
    L_tmp[r2 + 1] = CA[i + 2];
    L_tmp[r2 + 2] = CA[i + 4];
    L_tmp[r2 + 3] = CA[i + 6];
  }
  memcpy(&b_CA[0], &L_tmp[0], 8U * sizeof(double));
  memset(&b_statedata[0], 0, sizeof(double) << 3);
  for (i = 0; i < 4; i++) {
    b_r = _mm_loadu_pd(&CA[0]);
    r2 = i << 1;
    r1 = _mm_loadu_pd(&b_statedata[r2]);
    kidx = i << 2;
    _mm_storeu_pd(
        &b_statedata[r2],
        _mm_add_pd(r1,
                   _mm_mul_pd(b_r, _mm_set1_pd(statedata->Covariance[kidx]))));
    b_r = _mm_loadu_pd(&CA[2]);
    r1 = _mm_loadu_pd(&b_statedata[r2]);
    _mm_storeu_pd(
        &b_statedata[r2],
        _mm_add_pd(
            r1, _mm_mul_pd(b_r, _mm_set1_pd(statedata->Covariance[kidx + 1]))));
    b_r = _mm_loadu_pd(&CA[4]);
    r1 = _mm_loadu_pd(&b_statedata[r2]);
    _mm_storeu_pd(
        &b_statedata[r2],
        _mm_add_pd(
            r1, _mm_mul_pd(b_r, _mm_set1_pd(statedata->Covariance[kidx + 2]))));
    b_r = _mm_loadu_pd(&CA[6]);
    r1 = _mm_loadu_pd(&b_statedata[r2]);
    _mm_storeu_pd(
        &b_statedata[r2],
        _mm_add_pd(
            r1, _mm_mul_pd(b_r, _mm_set1_pd(statedata->Covariance[kidx + 3]))));
  }
  for (i = 0; i < 2; i++) {
    a21 = b_statedata[i];
    a22 = b_statedata[i + 2];
    s = b_statedata[i + 4];
    d = b_statedata[i + 6];
    for (b_i = 0; b_i < 2; b_i++) {
      r2 = b_i << 2;
      d_B[i + (b_i << 1)] =
          (((a21 * L_tmp[r2] + a22 * L_tmp[r2 + 1]) + s * L_tmp[r2 + 2]) +
           d * L_tmp[r2 + 3]) +
          CovMat[(i + 6 * (b_i + 4)) + 4];
    }
  }
  if (fabs(d_B[1]) > fabs(d_B[0])) {
    b_r1 = 1;
    r2 = 0;
  } else {
    b_r1 = 0;
    r2 = 1;
  }
  a21 = d_B[r2] / d_B[b_r1];
  s = d_B[b_r1 + 2];
  a22 = d_B[r2 + 2] - a21 * s;
  Kinv_tmp = b_r1 << 1;
  Kinv[Kinv_tmp] = 1.0 / d_B[b_r1];
  kidx = r2 << 1;
  Kinv[kidx] = (0.0 - Kinv[Kinv_tmp] * s) / a22;
  Kinv[Kinv_tmp] -= Kinv[kidx] * a21;
  Kinv[Kinv_tmp + 1] = 0.0 / d_B[b_r1];
  Kinv[kidx + 1] = (1.0 - Kinv[Kinv_tmp + 1] * s) / a22;
  Kinv[Kinv_tmp + 1] -= Kinv[kidx + 1] * a21;
  memset(&b_L_tmp[0], 0, sizeof(double) << 4);
  for (i = 0; i < 4; i++) {
    r2 = i << 2;
    for (b_i = 0; b_i < 4; b_i++) {
      kidx = b_i << 2;
      b_r = _mm_loadu_pd(&dv[kidx]);
      r1 = _mm_loadu_pd(&b_L_tmp[r2]);
      b_r2 = _mm_set1_pd(statedata->Covariance[b_i + r2]);
      _mm_storeu_pd(&b_L_tmp[r2], _mm_add_pd(r1, _mm_mul_pd(b_r, b_r2)));
      b_r = _mm_loadu_pd(&dv[kidx + 2]);
      r1 = _mm_loadu_pd(&b_L_tmp[r2 + 2]);
      _mm_storeu_pd(&b_L_tmp[r2 + 2], _mm_add_pd(r1, _mm_mul_pd(b_r, b_r2)));
    }
  }
  for (i = 0; i < 4; i++) {
    a21 = b_L_tmp[i];
    a22 = b_L_tmp[i + 4];
    s = b_L_tmp[i + 8];
    d = b_L_tmp[i + 12];
    for (b_i = 0; b_i < 2; b_i++) {
      kidx = b_i << 2;
      L_tmp[i + kidx] =
          (((a21 * b_CA[kidx] + a22 * b_CA[kidx + 1]) + s * b_CA[kidx + 2]) +
           d * b_CA[kidx + 3]) +
          CovMat[i + 6 * (b_i + 4)];
    }
  }
  memset(&L[0], 0, sizeof(double) << 3);
  b_r = _mm_loadu_pd(&statedata->Plant[0]);
  r1 = _mm_loadu_pd(&xoff[0]);
  b_r2 = _mm_loadu_pd(&Bu[0]);
  _mm_storeu_pd(&xk[0], _mm_add_pd(_mm_sub_pd(b_r, r1),
                                   _mm_mul_pd(b_r2, _mm_set1_pd(0.0))));
  xk[2] = (statedata->Plant[2] - onlinedata_model_X[2]) + B[2] * 0.0;
  xk[3] = statedata->Disturbance + B[3] * 0.0;
  memset(&y_innov[0], 0, sizeof(double) << 1);
  b_r = _mm_loadu_pd(&CA[0]);
  r1 = _mm_loadu_pd(&y_innov[0]);
  _mm_storeu_pd(&y_innov[0],
                _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(xk[0]))));
  b_r = _mm_loadu_pd(&CA[2]);
  r1 = _mm_loadu_pd(&y_innov[0]);
  _mm_storeu_pd(&y_innov[0],
                _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(xk[1]))));
  b_r = _mm_loadu_pd(&CA[4]);
  r1 = _mm_loadu_pd(&y_innov[0]);
  _mm_storeu_pd(&y_innov[0],
                _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(xk[2]))));
  b_r = _mm_loadu_pd(&CA[6]);
  r1 = _mm_loadu_pd(&y_innov[0]);
  _mm_storeu_pd(&y_innov[0],
                _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(xk[3]))));
  memset(&Sum[0], 0, sizeof(double) << 1);
  b_r = _mm_loadu_pd(&Sx[2]);
  r1 = _mm_loadu_pd(&Sum[0]);
  r3 = _mm_set1_pd(v[0]);
  _mm_storeu_pd(&Sum[0], _mm_add_pd(r1, _mm_mul_pd(b_r, r3)));
  b_r = _mm_loadu_pd(&Sx[4]);
  r1 = _mm_loadu_pd(&Sum[0]);
  r4 = _mm_set1_pd(v[1]);
  _mm_storeu_pd(&Sum[0], _mm_add_pd(r1, _mm_mul_pd(b_r, r4)));
  memset(&c_statedata[0], 0, sizeof(double) << 3);
  for (b_i = 0; b_i < 2; b_i++) {
    kidx = b_i << 1;
    r1 = _mm_loadu_pd(&L_tmp[0]);
    b_r1 = b_i << 2;
    b_r2 = _mm_loadu_pd(&L[b_r1]);
    b_r = _mm_set1_pd(Kinv[kidx]);
    _mm_storeu_pd(&L[b_r1], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    r1 = _mm_loadu_pd(&L_tmp[2]);
    b_r2 = _mm_loadu_pd(&L[b_r1 + 2]);
    _mm_storeu_pd(&L[b_r1 + 2], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    r1 = _mm_loadu_pd(&L_tmp[4]);
    b_r2 = _mm_loadu_pd(&L[b_r1]);
    b_r = _mm_set1_pd(Kinv[kidx + 1]);
    _mm_storeu_pd(&L[b_r1], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    r1 = _mm_loadu_pd(&L_tmp[6]);
    b_r2 = _mm_loadu_pd(&L[b_r1 + 2]);
    _mm_storeu_pd(&L[b_r1 + 2], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    y_innov[b_i] = (onlinedata_signals_ym[b_i] - onlinedata_model_Y[b_i]) -
                   (y_innov[b_i] + Sum[b_i]);
    for (i = 0; i < 4; i++) {
      r2 = i << 2;
      b_r = _mm_loadu_pd(&statedata->Covariance[r2]);
      r1 = _mm_loadu_pd(&c_statedata[b_r1]);
      b_r2 = _mm_set1_pd(b_CA[i + b_r1]);
      _mm_storeu_pd(&c_statedata[b_r1], _mm_add_pd(r1, _mm_mul_pd(b_r, b_r2)));
      b_r = _mm_loadu_pd(&statedata->Covariance[r2 + 2]);
      r1 = _mm_loadu_pd(&c_statedata[b_r1 + 2]);
      _mm_storeu_pd(&c_statedata[b_r1 + 2],
                    _mm_add_pd(r1, _mm_mul_pd(b_r, b_r2)));
    }
  }
  memset(&b_statedata[0], 0, sizeof(double) << 3);
  for (i = 0; i < 2; i++) {
    kidx = i << 1;
    r1 = _mm_loadu_pd(&c_statedata[0]);
    r2 = i << 2;
    b_r2 = _mm_loadu_pd(&b_statedata[r2]);
    b_r = _mm_set1_pd(Kinv[kidx]);
    _mm_storeu_pd(&b_statedata[r2], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    r1 = _mm_loadu_pd(&c_statedata[2]);
    b_r2 = _mm_loadu_pd(&b_statedata[r2 + 2]);
    _mm_storeu_pd(&b_statedata[r2 + 2], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    r1 = _mm_loadu_pd(&c_statedata[4]);
    b_r2 = _mm_loadu_pd(&b_statedata[r2]);
    b_r = _mm_set1_pd(Kinv[kidx + 1]);
    _mm_storeu_pd(&b_statedata[r2], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    r1 = _mm_loadu_pd(&c_statedata[6]);
    b_r2 = _mm_loadu_pd(&b_statedata[r2 + 2]);
    _mm_storeu_pd(&b_statedata[r2 + 2], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
  }
  a21 = y_innov[0];
  s = y_innov[1];
  for (i = 0; i <= 2; i += 2) {
    b_r = _mm_loadu_pd(&b_statedata[i]);
    r1 = _mm_mul_pd(b_r, _mm_set1_pd(a21));
    b_r = _mm_loadu_pd(&b_statedata[i + 4]);
    b_r = _mm_mul_pd(b_r, _mm_set1_pd(s));
    b_r = _mm_add_pd(r1, b_r);
    r1 = _mm_loadu_pd(&xk[i]);
    b_r = _mm_add_pd(r1, b_r);
    _mm_storeu_pd(&x[i], b_r);
  }
  u = statedata->LastMove - onlinedata_model_U[0];
  for (i = 0; i < 6; i++) {
    iA[i] = statedata->iA[i];
  }
  memcpy(&Linv[0], &dv3[0], 16U * sizeof(double));
  for (i = 0; i < 6; i++) {
    statedata->iA[i] = false;
  }
  memset(&b_CA[0], 0, sizeof(double) << 3);
  memset(&Sum[0], 0, sizeof(double) << 1);
  for (i = 0; i < 4; i++) {
    b_r = _mm_loadu_pd(&CA[0]);
    kidx = i << 1;
    r1 = _mm_loadu_pd(&b_CA[kidx]);
    r2 = i << 2;
    _mm_storeu_pd(&b_CA[kidx],
                  _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(dv[r2]))));
    b_r = _mm_loadu_pd(&CA[2]);
    r1 = _mm_loadu_pd(&b_CA[kidx]);
    _mm_storeu_pd(&b_CA[kidx],
                  _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(dv[r2 + 1]))));
    b_r = _mm_loadu_pd(&CA[4]);
    r1 = _mm_loadu_pd(&b_CA[kidx]);
    _mm_storeu_pd(&b_CA[kidx],
                  _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(dv[r2 + 2]))));
    b_r = _mm_loadu_pd(&CA[6]);
    r1 = _mm_loadu_pd(&b_CA[kidx]);
    _mm_storeu_pd(&b_CA[kidx],
                  _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(dv[r2 + 3]))));
    b_r = _mm_loadu_pd(&CA[kidx]);
    r1 = _mm_loadu_pd(&Sum[0]);
    _mm_storeu_pd(&Sum[0], _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(Bu[i]))));
  }
  memset(&d_B[0], 0, sizeof(double) << 2);
  for (i = 0; i < 2; i++) {
    b_r = _mm_loadu_pd(&CA[0]);
    b_r1 = i << 1;
    r1 = _mm_loadu_pd(&d_B[b_r1]);
    kidx = i << 2;
    _mm_storeu_pd(&d_B[b_r1],
                  _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(Bv[kidx]))));
    b_r = _mm_loadu_pd(&CA[2]);
    r1 = _mm_loadu_pd(&d_B[b_r1]);
    _mm_storeu_pd(&d_B[b_r1],
                  _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(Bv[kidx + 1]))));
    b_r = _mm_loadu_pd(&CA[4]);
    r1 = _mm_loadu_pd(&d_B[b_r1]);
    _mm_storeu_pd(&d_B[b_r1],
                  _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(Bv[kidx + 2]))));
    b_r = _mm_loadu_pd(&CA[6]);
    r1 = _mm_loadu_pd(&d_B[b_r1]);
    _mm_storeu_pd(&d_B[b_r1],
                  _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(Bv[kidx + 3]))));
    Hv[26 * i] = d_B[b_r1];
    r2 = (i + 1) << 1;
    kidx = 26 * (i + 2);
    Hv[kidx] = Sx[r2];
    Hv[26 * i + 1] = d_B[b_r1 + 1];
    Hv[kidx + 1] = Sx[r2 + 1];
  }
  for (i = 0; i < 24; i++) {
    r2 = 26 * (i + 4);
    Hv[r2] = 0.0;
    Hv[r2 + 1] = 0.0;
  }
  for (i = 0; i < 28; i++) {
    memset(&Hv[i * 26 + 2], 0, 24U * sizeof(double));
  }
  for (i = 0; i < 4; i++) {
    r2 = i << 1;
    b_Sx[26 * i] = b_CA[r2];
    b_Sx[26 * i + 1] = b_CA[r2 + 1];
    memset(&b_Sx[i * 26 + 2], 0, 24U * sizeof(double));
  }
  Su1[0] = Sum[0];
  Su1[1] = Sum[1];
  memset(&Su1[2], 0, 24U * sizeof(double));
  Su[0] = Sum[0];
  Su[1] = Sum[1];
  for (i = 0; i < 12; i++) {
    r2 = 26 * (i + 1);
    Su[r2] = 0.0;
    Su[r2 + 1] = 0.0;
  }
  for (i = 0; i < 13; i++) {
    memset(&Su[i * 26 + 2], 0, 24U * sizeof(double));
  }
  a21 = Bu[0];
  a22 = Bu[1];
  s = Bu[2];
  d = Bu[3];
  for (b_i = 0; b_i < 12; b_i++) {
    double c_CA[56];
    double b_Sum[26];
    signed char Su_tmp[2];
    signed char iv3[2];
    signed char c_i;
    signed char i2;
    r2 = (b_i + 1) * 2;
    for (i = 0; i < 2; i++) {
      kidx = (r2 + i) + 1;
      d1 = Sum[i] + (((b_CA[i] * a21 + b_CA[i + 2] * a22) + b_CA[i + 4] * s) +
                     b_CA[i + 6] * d);
      Sum[i] = d1;
      iv3[i] = (signed char)kidx;
      Su1[kidx - 1] = d1;
      Su_tmp[i] = (signed char)(kidx - 2);
      b_Sum[i] = d1;
    }
    c_i = Su_tmp[0];
    i2 = Su_tmp[1];
    for (i = 0; i < 12; i++) {
      kidx = (i + 1) << 1;
      b_Sum[kidx] = Su[(c_i + 26 * i) - 1];
      b_Sum[kidx + 1] = Su[(i2 + 26 * i) - 1];
    }
    c_i = iv3[0];
    i2 = iv3[1];
    for (i = 0; i < 13; i++) {
      kidx = i << 1;
      Su[(c_i + 26 * i) - 1] = b_Sum[kidx];
      Su[(i2 + 26 * i) - 1] = b_Sum[kidx + 1];
    }
    memset(&d_B[0], 0, sizeof(double) << 2);
    for (i = 0; i < 2; i++) {
      b_r = _mm_loadu_pd(&b_CA[0]);
      r2 = i << 1;
      r1 = _mm_loadu_pd(&d_B[r2]);
      kidx = i << 2;
      _mm_storeu_pd(&d_B[r2],
                    _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(Bv[kidx]))));
      b_r = _mm_loadu_pd(&b_CA[2]);
      r1 = _mm_loadu_pd(&d_B[r2]);
      _mm_storeu_pd(&d_B[r2],
                    _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(Bv[kidx + 1]))));
      b_r = _mm_loadu_pd(&b_CA[4]);
      r1 = _mm_loadu_pd(&d_B[r2]);
      _mm_storeu_pd(&d_B[r2],
                    _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(Bv[kidx + 2]))));
      b_r = _mm_loadu_pd(&b_CA[6]);
      r1 = _mm_loadu_pd(&d_B[r2]);
      _mm_storeu_pd(&d_B[r2],
                    _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(Bv[kidx + 3]))));
      c_CA[r2] = d_B[r2];
      c_CA[r2 + 1] = d_B[r2 + 1];
    }
    c_i = Su_tmp[0];
    i2 = Su_tmp[1];
    for (i = 0; i < 26; i++) {
      kidx = (i + 2) << 1;
      c_CA[kidx] = Hv[(c_i + 26 * i) - 1];
      c_CA[kidx + 1] = Hv[(i2 + 26 * i) - 1];
    }
    c_i = iv3[0];
    i2 = iv3[1];
    for (i = 0; i < 28; i++) {
      kidx = i << 1;
      Hv[(c_i + 26 * i) - 1] = c_CA[kidx];
      Hv[(i2 + 26 * i) - 1] = c_CA[kidx + 1];
    }
    memset(&CA[0], 0, sizeof(double) << 3);
    for (i = 0; i < 4; i++) {
      b_r = _mm_loadu_pd(&b_CA[0]);
      r2 = i << 1;
      r1 = _mm_loadu_pd(&CA[r2]);
      kidx = i << 2;
      _mm_storeu_pd(&CA[r2],
                    _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(dv[kidx]))));
      b_r = _mm_loadu_pd(&b_CA[2]);
      r1 = _mm_loadu_pd(&CA[r2]);
      _mm_storeu_pd(&CA[r2],
                    _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(dv[kidx + 1]))));
      b_r = _mm_loadu_pd(&b_CA[4]);
      r1 = _mm_loadu_pd(&CA[r2]);
      _mm_storeu_pd(&CA[r2],
                    _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(dv[kidx + 2]))));
      b_r = _mm_loadu_pd(&b_CA[6]);
      r1 = _mm_loadu_pd(&CA[r2]);
      _mm_storeu_pd(&CA[r2],
                    _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(dv[kidx + 3]))));
    }
    memcpy(&b_CA[0], &CA[0], 8U * sizeof(double));
    for (i = 0; i < 4; i++) {
      kidx = i << 1;
      b_Sx[(c_i + 26 * i) - 1] = b_CA[kidx];
      b_Sx[(i2 + 26 * i) - 1] = b_CA[kidx + 1];
    }
  }
  memset(&SuJm[0], 0, 78U * sizeof(double));
  for (i = 0; i < 3; i++) {
    for (b_i = 0; b_i < 13; b_i++) {
      r2 = iv4[b_i + 13 * i];
      for (i1 = 0; i1 <= 24; i1 += 2) {
        b_r = _mm_loadu_pd(&Su[i1 + 26 * b_i]);
        kidx = i1 + 26 * i;
        r1 = _mm_loadu_pd(&SuJm[kidx]);
        _mm_storeu_pd(&SuJm[kidx],
                      _mm_add_pd(r1, _mm_mul_pd(b_r, _mm_set1_pd(r2))));
      }
    }
  }
  kidx = -1;
  for (i = 0; i < 13; i++) {
    for (b_i = 0; b_i < 13; b_i++) {
      a[(kidx + b_i) + 1] = A[b_i + 13 * i];
    }
    kidx += 13;
  }
  memset(&I2Jm[0], 0, 39U * sizeof(double));
  for (i = 0; i < 3; i++) {
    for (b_i = 0; b_i < 13; b_i++) {
      r2 = iv4[b_i + 13 * i];
      for (i1 = 0; i1 < 13; i1++) {
        kidx = i1 + 13 * i;
        I2Jm[kidx] += (double)(a[i1 + 13 * b_i] * r2);
      }
    }
  }
  ixw = 1;
  for (i = 0; i < 26; i++) {
    r2 = (short)((short)(-9999 * (ixw - 1)) + 10000);
    WySuJm[i] = (double)r2 * SuJm[i];
    WySuJm[i + 26] = (double)r2 * SuJm[i + 26];
    WySuJm[i + 52] = (double)r2 * SuJm[i + 52];
    ixw++;
    if (ixw > 2) {
      ixw = 1;
    }
  }
  for (i = 0; i < 13; i++) {
    WuI2Jm[i] = 0.09 * I2Jm[i];
    WduJm[i] = 0.64000000000000012 * (double)iv4[i];
    WuI2Jm[i + 13] = 0.09 * I2Jm[i + 13];
    WduJm[i + 13] = 0.64000000000000012 * (double)iv4[i + 13];
    WuI2Jm[i + 26] = 0.09 * I2Jm[i + 26];
    WduJm[i + 26] = 0.64000000000000012 * (double)iv4[i + 26];
  }
  memset(&dv4[0], 0, 9U * sizeof(double));
  for (i1 = 0; i1 < 3; i1++) {
    for (i = 0; i < 3; i++) {
      a21 = 0.0;
      for (b_i = 0; b_i < 26; b_i++) {
        a21 += SuJm[b_i + 26 * i] * WySuJm[b_i + 26 * i1];
      }
      b_SuJm[i + 3 * i1] = a21;
    }
    a21 = dv4[3 * i1];
    r2 = 3 * i1 + 1;
    kidx = 3 * i1 + 2;
    for (i = 0; i < 13; i++) {
      s = WduJm[i + 13 * i1];
      a21 += (double)iv5[3 * i] * s;
      dv4[r2] += (double)iv5[3 * i + 1] * s;
      dv4[kidx] += (double)iv5[3 * i + 2] * s;
    }
    dv4[3 * i1] = a21;
  }
  memset(&b_Su1[0], 0, 3U * sizeof(double));
  memset(&dv5[0], 0, 3U * sizeof(double));
  for (i1 = 0; i1 < 3; i1++) {
    for (b_i = 0; b_i < 3; b_i++) {
      a21 = 0.0;
      for (i = 0; i < 13; i++) {
        a21 += I2Jm[i + 13 * i1] * WuI2Jm[i + 13 * b_i];
      }
      r2 = i1 + 3 * b_i;
      Linv[i1 + (b_i << 2)] = (b_SuJm[r2] + dv4[r2]) + a21;
    }
    a21 = b_Su1[i1];
    for (i = 0; i < 26; i++) {
      a21 += Su1[i] * WySuJm[i + 26 * i1];
    }
    b_Su1[i1] = a21;
    s = dv5[i1];
    for (i = 0; i < 13; i++) {
      s += WuI2Jm[i + 13 * i1];
    }
    dv5[i1] = s;
    X0[i1] = a21 + s;
  }
  for (i = 0; i <= 36; i += 2) {
    b_r = _mm_loadu_pd(&WuI2Jm[i]);
    _mm_storeu_pd(&WuI2Jm[i], _mm_mul_pd(b_r, _mm_set1_pd(-1.0)));
  }
  WuI2Jm[38] = -WuI2Jm[38];
  for (i = 0; i < 3; i++) {
    for (b_i = 0; b_i < 4; b_i++) {
      a21 = 0.0;
      for (i1 = 0; i1 < 26; i1++) {
        a21 += b_Sx[i1 + 26 * b_i] * WySuJm[i1 + 26 * i];
      }
      Sx[b_i + (i << 2)] = a21;
    }
  }
  for (i = 0; i < 3; i++) {
    for (b_i = 0; b_i < 28; b_i++) {
      a21 = 0.0;
      for (i1 = 0; i1 < 26; i1++) {
        a21 += Hv[i1 + 26 * b_i] * WySuJm[i1 + 26 * i];
      }
      Kv[b_i + 28 * i] = a21;
    }
  }
  for (i = 0; i <= 76; i += 2) {
    b_r = _mm_loadu_pd(&WySuJm[i]);
    _mm_storeu_pd(&WySuJm[i], _mm_mul_pd(b_r, _mm_set1_pd(-1.0)));
  }
  kidx = 0;
  memcpy(&b_L[0], &Linv[0], 16U * sizeof(double));
  r2 = xpotrf(b_L);
  guard1 = false;
  if (r2 == 0) {
    d_B[0] = b_L[0];
    d_B[1] = b_L[5];
    d_B[2] = b_L[10];
    d_B[3] = b_L[15];
    if (!(minimum(d_B) > 1.4901161193847656E-7)) {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }
  if (guard1) {
    boolean_T exitg2;
    a21 = 0.0;
    r2 = 0;
    exitg2 = false;
    while ((!exitg2) && (r2 < 4)) {
      s = ((fabs(Linv[r2]) + fabs(Linv[r2 + 4])) + fabs(Linv[r2 + 8])) +
          fabs(Linv[r2 + 12]);
      if (rtIsNaN(s)) {
        a21 = rtNaN;
        exitg2 = true;
      } else {
        if (s > a21) {
          a21 = s;
        }
        r2++;
      }
    }
    if (a21 >= 1.0E+10) {
      kidx = 2;
    } else {
      boolean_T exitg1;
      b_r1 = 0;
      exitg1 = false;
      while ((!exitg1) && (b_r1 <= 4)) {
        boolean_T guard2;
        if (b_r1 == 0) {
          a21 = 1.0;
        } else if (b_r1 == 1) {
          a21 = 10.0;
        } else if (b_r1 == 2) {
          a21 = 100.0;
        } else {
          a21 = pow(10.0, b_r1);
        }
        a21 *= 1.4901161193847656E-7;
        memset(&Pcov[0], 0, 16U * sizeof(double));
        Pcov[0] = 1.0;
        Pcov[5] = 1.0;
        Pcov[10] = 1.0;
        Pcov[15] = 1.0;
        for (i = 0; i <= 14; i += 2) {
          b_r = _mm_loadu_pd(&Pcov[i]);
          r1 = _mm_loadu_pd(&Linv[i]);
          b_r = _mm_add_pd(r1, _mm_mul_pd(_mm_set1_pd(a21), b_r));
          _mm_storeu_pd(&Linv[i], b_r);
          _mm_storeu_pd(&b_L[i], b_r);
        }
        r2 = xpotrf(b_L);
        guard2 = false;
        if (r2 == 0) {
          d_B[0] = b_L[0];
          d_B[1] = b_L[5];
          d_B[2] = b_L[10];
          d_B[3] = b_L[15];
          if (minimum(d_B) > 1.4901161193847656E-7) {
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
          b_r1++;
        }
      }
    }
  }
  if (kidx > 1) {
    u += onlinedata_model_U[0];
  } else {
    memset(&Pcov[0], 0, 16U * sizeof(double));
    Pcov[0] = 1.0;
    Pcov[5] = 1.0;
    Pcov[10] = 1.0;
    Pcov[15] = 1.0;
    for (i = 0; i < 4; i++) {
      r2 = i << 2;
      Linv[r2] = Pcov[r2];
      Linv[r2 + 1] = Pcov[r2 + 1];
      Linv[r2 + 2] = Pcov[r2 + 2];
      Linv[r2 + 3] = Pcov[r2 + 3];
    }
    trisolve(b_L, Linv);
    d_B[0] = 0.0;
    d_B[1] = 0.0;
    d_B[2] = 0.0;
    d_B[3] = 0.0;
    for (b_i = 0; b_i < 3; b_i++) {
      r2 = b_i << 2;
      a21 = 0.0;
      for (i = 0; i < 26; i++) {
        a21 += WySuJm[i + 26 * b_i] * r[i];
      }
      a22 = 0.0;
      for (i = 0; i < 28; i++) {
        a22 += Kv[i + 28 * b_i] * v[i];
      }
      s = 0.0;
      for (i = 0; i < 13; i++) {
        s += WuI2Jm[i + 13 * b_i] * (0.0 - U_idx_0);
      }
      d_B[b_i] = ((((((Sx[r2] * x[0] + Sx[r2 + 1] * x[1]) + Sx[r2 + 2] * x[2]) +
                     Sx[r2 + 3] * x[3]) +
                    a21) +
                   X0[b_i] * u) +
                  a22) +
                 s;
    }
    a21 = x[0];
    a22 = x[1];
    s = x[2];
    d = x[3];
    for (i = 0; i < 6; i++) {
      statedata->iA[i] = iA[i];
      b_b[i] = (b[i] + (((0.0 * a21 + 0.0 * a22) + 0.0 * s) + 0.0 * d)) +
               (double)iv6[i] * u;
    }
    memset(&b[0], 0, 6U * sizeof(double));
    for (i = 0; i < 28; i++) {
      b_r = _mm_loadu_pd(&b[0]);
      r1 = _mm_set1_pd(0.0 * v[i]);
      _mm_storeu_pd(&b[0], _mm_add_pd(b_r, r1));
      b_r = _mm_loadu_pd(&b[2]);
      _mm_storeu_pd(&b[2], _mm_add_pd(b_r, r1));
      b_r = _mm_loadu_pd(&b[4]);
      _mm_storeu_pd(&b[4], _mm_add_pd(b_r, r1));
    }
    for (i = 0; i < 4; i++) {
      r2 = i << 2;
      for (b_i = 0; b_i < 4; b_i++) {
        kidx = b_i << 2;
        b_L[b_i + r2] =
            ((Linv[kidx] * Linv[r2] + Linv[kidx + 1] * Linv[r2 + 1]) +
             Linv[kidx + 2] * Linv[r2 + 2]) +
            Linv[kidx + 3] * Linv[r2 + 3];
      }
    }
    b_r = _mm_loadu_pd(&b_b[0]);
    r1 = _mm_loadu_pd(&b[0]);
    b_r2 = _mm_set1_pd(-1.0);
    _mm_storeu_pd(&b_b[0], _mm_mul_pd(_mm_add_pd(b_r, r1), b_r2));
    b_r = _mm_loadu_pd(&b_b[2]);
    r1 = _mm_loadu_pd(&b[2]);
    _mm_storeu_pd(&b_b[2], _mm_mul_pd(_mm_add_pd(b_r, r1), b_r2));
    b_r = _mm_loadu_pd(&b_b[4]);
    r1 = _mm_loadu_pd(&b[4]);
    _mm_storeu_pd(&b_b[4], _mm_mul_pd(_mm_add_pd(b_r, r1), b_r2));
    r2 = qpkwik(Linv, b_L, d_B, b_b, statedata->iA, Kinv, b);
    if ((r2 < 0) || (r2 == 0)) {
      Kinv[0] = 0.0;
    }
    u = (u + Kinv[0]) + onlinedata_model_U[0];
  }
  a21 = u - onlinedata_model_U[0];
  a22 = xk[0];
  s = xk[1];
  d = xk[2];
  d1 = xk[3];
  for (i = 0; i <= 2; i += 2) {
    b_r = _mm_loadu_pd(&dv[i]);
    r1 = _mm_mul_pd(b_r, _mm_set1_pd(a22));
    b_r = _mm_loadu_pd(&dv[i + 4]);
    b_r = _mm_mul_pd(b_r, _mm_set1_pd(s));
    r1 = _mm_add_pd(r1, b_r);
    b_r = _mm_loadu_pd(&dv[i + 8]);
    b_r = _mm_mul_pd(b_r, _mm_set1_pd(d));
    r1 = _mm_add_pd(r1, b_r);
    b_r = _mm_loadu_pd(&dv[i + 12]);
    b_r = _mm_mul_pd(b_r, _mm_set1_pd(d1));
    r1 = _mm_add_pd(r1, b_r);
    b_r = _mm_loadu_pd(&Bu[i]);
    b_r = _mm_mul_pd(b_r, _mm_set1_pd(a21));
    b_r = _mm_add_pd(r1, b_r);
    _mm_storeu_pd(&Kinv[i], b_r);
  }
  memset(&Bu[0], 0, sizeof(double) << 2);
  b_r = _mm_loadu_pd(&Bv[0]);
  r1 = _mm_loadu_pd(&Bu[0]);
  _mm_storeu_pd(&Bu[0], _mm_add_pd(r1, _mm_mul_pd(b_r, r3)));
  b_r = _mm_loadu_pd(&Bv[2]);
  r1 = _mm_loadu_pd(&Bu[2]);
  _mm_storeu_pd(&Bu[2], _mm_add_pd(r1, _mm_mul_pd(b_r, r3)));
  b_r = _mm_loadu_pd(&Bv[4]);
  r1 = _mm_loadu_pd(&Bu[0]);
  _mm_storeu_pd(&Bu[0], _mm_add_pd(r1, _mm_mul_pd(b_r, r4)));
  b_r = _mm_loadu_pd(&Bv[6]);
  r1 = _mm_loadu_pd(&Bu[2]);
  _mm_storeu_pd(&Bu[2], _mm_add_pd(r1, _mm_mul_pd(b_r, r4)));
  a21 = y_innov[0];
  s = y_innov[1];
  for (i = 0; i <= 2; i += 2) {
    b_r = _mm_loadu_pd(&Kinv[i]);
    r1 = _mm_loadu_pd(&Bu[i]);
    b_r2 = _mm_add_pd(b_r, r1);
    b_r = _mm_loadu_pd(&L[i]);
    r1 = _mm_mul_pd(b_r, _mm_set1_pd(a21));
    b_r = _mm_loadu_pd(&L[i + 4]);
    b_r = _mm_mul_pd(b_r, _mm_set1_pd(s));
    b_r = _mm_add_pd(r1, b_r);
    b_r = _mm_add_pd(b_r2, b_r);
    r1 = _mm_loadu_pd(&xoff[i]);
    b_r = _mm_add_pd(b_r, r1);
    _mm_storeu_pd(&x[i], b_r);
  }
  statedata->Plant[0] = x[0];
  statedata->Plant[1] = x[1];
  statedata->Plant[2] = x[2];
  statedata->Disturbance = x[3];
  memset(&Pcov[0], 0, sizeof(double) << 4);
  for (i = 0; i < 4; i++) {
    r2 = i << 2;
    for (b_i = 0; b_i < 4; b_i++) {
      kidx = b_i << 2;
      b_r = _mm_loadu_pd(&b_L_tmp[kidx]);
      r1 = _mm_loadu_pd(&Pcov[r2]);
      b_r2 = _mm_set1_pd(dv[i + kidx]);
      _mm_storeu_pd(&Pcov[r2], _mm_add_pd(r1, _mm_mul_pd(b_r, b_r2)));
      b_r = _mm_loadu_pd(&b_L_tmp[kidx + 2]);
      r1 = _mm_loadu_pd(&Pcov[r2 + 2]);
      _mm_storeu_pd(&Pcov[r2 + 2], _mm_add_pd(r1, _mm_mul_pd(b_r, b_r2)));
    }
  }
  memset(&b_L_tmp[0], 0, sizeof(double) << 4);
  for (i = 0; i < 4; i++) {
    r1 = _mm_loadu_pd(&L_tmp[0]);
    r2 = i << 2;
    b_r2 = _mm_loadu_pd(&b_L_tmp[r2]);
    b_r = _mm_set1_pd(L[i]);
    _mm_storeu_pd(&b_L_tmp[r2], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    r1 = _mm_loadu_pd(&L_tmp[2]);
    b_r2 = _mm_loadu_pd(&b_L_tmp[r2 + 2]);
    _mm_storeu_pd(&b_L_tmp[r2 + 2], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    r1 = _mm_loadu_pd(&L_tmp[4]);
    b_r2 = _mm_loadu_pd(&b_L_tmp[r2]);
    b_r = _mm_set1_pd(L[i + 4]);
    _mm_storeu_pd(&b_L_tmp[r2], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    r1 = _mm_loadu_pd(&L_tmp[6]);
    b_r2 = _mm_loadu_pd(&b_L_tmp[r2 + 2]);
    _mm_storeu_pd(&b_L_tmp[r2 + 2], _mm_add_pd(b_r2, _mm_mul_pd(r1, b_r)));
    b_r = _mm_loadu_pd(&Pcov[r2]);
    r1 = _mm_loadu_pd(&b_L_tmp[r2]);
    b_r2 = _mm_loadu_pd(&CovMat[6 * i]);
    _mm_storeu_pd(&Pcov[r2], _mm_add_pd(_mm_sub_pd(b_r, r1), b_r2));
    b_r = _mm_loadu_pd(&Pcov[r2 + 2]);
    r1 = _mm_loadu_pd(&b_L_tmp[r2 + 2]);
    b_r2 = _mm_loadu_pd(&CovMat[6 * i + 2]);
    _mm_storeu_pd(&Pcov[r2 + 2], _mm_add_pd(_mm_sub_pd(b_r, r1), b_r2));
  }
  for (i = 0; i < 4; i++) {
    r2 = i << 2;
    statedata->Covariance[r2] = 0.5 * (Pcov[r2] + Pcov[i]);
    statedata->Covariance[r2 + 1] = 0.5 * (Pcov[r2 + 1] + Pcov[i + 4]);
    statedata->Covariance[r2 + 2] = 0.5 * (Pcov[r2 + 2] + Pcov[i + 8]);
    statedata->Covariance[r2 + 3] = 0.5 * (Pcov[r2 + 3] + Pcov[i + 12]);
  }
  statedata->LastMove = u;
  return u;
}

/* End of code generation (mpcmoveCodeGeneration.c) */
