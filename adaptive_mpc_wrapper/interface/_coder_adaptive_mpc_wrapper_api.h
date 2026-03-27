/*
 * _coder_adaptive_mpc_wrapper_api.h
 *
 * Code generation for function 'adaptive_mpc_wrapper'
 *
 */

#ifndef _CODER_ADAPTIVE_MPC_WRAPPER_API_H
#define _CODER_ADAPTIVE_MPC_WRAPPER_API_H

/* Include files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef typedef_struct11_T
#define typedef_struct11_T
typedef struct {
  real_T A[9];
  real_T B[6];
  real_T C[6];
  real_T D[4];
  real_T X[3];
  real_T U[2];
  real_T Y[2];
  real_T DX[3];
} struct11_T;
#endif /* typedef_struct11_T */

#ifndef typedef_struct5_T
#define typedef_struct5_T
typedef struct {
  real_T Plant[3];
  real_T Disturbance;
  real_T LastMove;
  real_T Covariance[16];
  boolean_T iA[6];
} struct5_T;
#endif /* typedef_struct5_T */

#ifndef typedef_struct7_T
#define typedef_struct7_T
typedef struct {
  real_T ym[2];
  real_T ref[2];
  real_T md;
} struct7_T;
#endif /* typedef_struct7_T */

#ifndef typedef_struct6_T
#define typedef_struct6_T
typedef struct {
  struct7_T signals;
  struct11_T model;
} struct6_T;
#endif /* typedef_struct6_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void adaptive_mpc_wrapper(struct5_T *state_in, struct6_T *onlineData,
                          real_T y[2], real_T r[2], real_T md, real_T Ad[9],
                          real_T Bd[6], real_T Cd[6], real_T Dd[4], real_T *u,
                          struct5_T *state_out);

void adaptive_mpc_wrapper_api(const mxArray *const prhs[10], int32_T nlhs,
                              const mxArray *plhs[2]);

void adaptive_mpc_wrapper_atexit(void);

void adaptive_mpc_wrapper_initialize(void);

void adaptive_mpc_wrapper_terminate(void);

void adaptive_mpc_wrapper_xil_shutdown(void);

void adaptive_mpc_wrapper_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_adaptive_mpc_wrapper_api.h) */
