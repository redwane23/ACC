/*
 * adaptive_mpc_wrapper.h
 *
 * Code generation for function 'adaptive_mpc_wrapper'
 *
 */

#ifndef ADAPTIVE_MPC_WRAPPER_H
#define ADAPTIVE_MPC_WRAPPER_H

/* Include files */
#include "adaptive_mpc_wrapper_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void adaptive_mpc_wrapper(const struct5_T *state_in,
                                 struct6_T *onlineData, const double y[2],
                                 const double r[2], double md,
                                 const double Ad[9], const double Bd[6],
                                 const double Cd[6], const double Dd[4],
                                 double *u, struct5_T *state_out);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (adaptive_mpc_wrapper.h) */
