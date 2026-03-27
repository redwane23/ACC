/*
 * adaptive_mpc_wrapper_types.h
 *
 * Code generation for function 'adaptive_mpc_wrapper'
 *
 */

#ifndef ADAPTIVE_MPC_WRAPPER_TYPES_H
#define ADAPTIVE_MPC_WRAPPER_TYPES_H

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct11_T
#define typedef_struct11_T
typedef struct {
  double A[9];
  double B[6];
  double C[6];
  double D[4];
  double X[3];
  double U[2];
  double Y[2];
  double DX[3];
} struct11_T;
#endif /* typedef_struct11_T */

#ifndef typedef_struct7_T
#define typedef_struct7_T
typedef struct {
  double ym[2];
  double ref[2];
  double md;
} struct7_T;
#endif /* typedef_struct7_T */

#ifndef typedef_struct6_T
#define typedef_struct6_T
typedef struct {
  struct7_T signals;
  struct11_T model;
} struct6_T;
#endif /* typedef_struct6_T */

#ifndef typedef_struct5_T
#define typedef_struct5_T
typedef struct {
  double Plant[3];
  double Disturbance;
  double LastMove;
  double Covariance[16];
  boolean_T iA[6];
} struct5_T;
#endif /* typedef_struct5_T */

#endif
/* End of code generation (adaptive_mpc_wrapper_types.h) */
