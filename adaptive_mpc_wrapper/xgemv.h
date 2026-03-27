/*
 * xgemv.h
 *
 * Code generation for function 'xgemv'
 *
 */

#ifndef XGEMV_H
#define XGEMV_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void xgemv(int m, int n, const double A[16], int ia0, const double x[16],
           int ix0, double y[4]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (xgemv.h) */
