/*
 * qpkwik.h
 *
 * Code generation for function 'qpkwik'
 *
 */

#ifndef QPKWIK_H
#define QPKWIK_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
int qpkwik(const double Linv[16], const double Hinv[16], const double f[4],
           const double b[6], boolean_T iA[6], double x[4], double lambda[6]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (qpkwik.h) */
