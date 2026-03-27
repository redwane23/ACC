/*
 * adaptive_mpc_wrapper.c
 *
 * Code generation for function 'adaptive_mpc_wrapper'
 *
 */

/* Include files */
#include "adaptive_mpc_wrapper.h"
#include "adaptive_mpc_wrapper_types.h"
#include "mpcmoveCodeGeneration.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void adaptive_mpc_wrapper(const struct5_T *state_in, struct6_T *onlineData,
                          const double y[2], const double r[2], double md,
                          const double Ad[9], const double Bd[6],
                          const double Cd[6], const double Dd[4], double *u,
                          struct5_T *state_out)
{
  int i;
  onlineData->signals.ym[0] = y[0];
  onlineData->signals.ref[0] = r[0];
  onlineData->signals.ym[1] = y[1];
  onlineData->signals.ref[1] = r[1];
  memcpy(&onlineData->model.A[0], &Ad[0], 9U * sizeof(double));
  for (i = 0; i < 6; i++) {
    onlineData->model.B[i] = Bd[i];
    onlineData->model.C[i] = Cd[i];
  }
  onlineData->model.D[0] = Dd[0];
  onlineData->model.D[1] = Dd[1];
  onlineData->model.D[2] = Dd[2];
  onlineData->model.D[3] = Dd[3];
  *state_out = *state_in;
  *u = mpcmoveCodeGeneration(
      state_out, onlineData->signals.ym, onlineData->signals.ref, md,
      onlineData->model.A, onlineData->model.B, onlineData->model.C,
      onlineData->model.D, onlineData->model.X, onlineData->model.U,
      onlineData->model.Y, onlineData->model.DX);
}

/* End of code generation (adaptive_mpc_wrapper.c) */
