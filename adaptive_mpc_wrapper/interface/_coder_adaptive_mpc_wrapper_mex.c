/*
 * _coder_adaptive_mpc_wrapper_mex.c
 *
 * Code generation for function 'adaptive_mpc_wrapper'
 *
 */

/* Include files */
#include "_coder_adaptive_mpc_wrapper_mex.h"
#include "_coder_adaptive_mpc_wrapper_api.h"

/* Function Definitions */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&adaptive_mpc_wrapper_atexit);
  adaptive_mpc_wrapper_initialize();
  unsafe_adaptive_mpc_wrapper_mexFunction(nlhs, plhs, nrhs, prhs);
  adaptive_mpc_wrapper_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1,
                           NULL, "UTF-8", true);
  return emlrtRootTLSGlobal;
}

void unsafe_adaptive_mpc_wrapper_mexFunction(int32_T nlhs, mxArray *plhs[2],
                                             int32_T nrhs,
                                             const mxArray *prhs[10])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *b_prhs[10];
  const mxArray *outputs[2];
  int32_T i;
  int32_T i1;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs < 10) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooFewInputsConstants", 9, 4, 20,
                        "adaptive_mpc_wrapper", 4, 20, "adaptive_mpc_wrapper",
                        4, 20, "adaptive_mpc_wrapper");
  }
  if (nrhs != 10) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 10, 4,
                        20, "adaptive_mpc_wrapper");
  }
  if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 20,
                        "adaptive_mpc_wrapper");
  }
  /* Call the function. */
  for (i = 0; i < 10; i++) {
    b_prhs[i] = prhs[i];
  }
  adaptive_mpc_wrapper_api(b_prhs, nlhs, outputs);
  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    i1 = 1;
  } else {
    i1 = nlhs;
  }
  emlrtReturnArrays(i1, &plhs[0], &outputs[0]);
}

/* End of code generation (_coder_adaptive_mpc_wrapper_mex.c) */
