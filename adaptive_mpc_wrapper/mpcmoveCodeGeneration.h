/*
 * mpcmoveCodeGeneration.h
 *
 * Code generation for function 'mpcmoveCodeGeneration'
 *
 */

#ifndef MPCMOVECODEGENERATION_H
#define MPCMOVECODEGENERATION_H

/* Include files */
#include "adaptive_mpc_wrapper_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double mpcmoveCodeGeneration(
    struct5_T *statedata, const double onlinedata_signals_ym[2],
    const double onlinedata_signals_ref[2], double onlinedata_signals_md,
    const double onlinedata_model_A[9], const double onlinedata_model_B[6],
    const double onlinedata_model_C[6], const double onlinedata_model_D[4],
    const double onlinedata_model_X[3], const double onlinedata_model_U[2],
    const double onlinedata_model_Y[2], const double onlinedata_model_DX[3]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (mpcmoveCodeGeneration.h) */
