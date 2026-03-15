#ifndef pid_math_private_h_
#define pid_math_private_h_

#include "../headers/vehical_state.h"
#include "pid_math_modules.c"


// Math Utility Functions
double math_update_integral(PIDMathUtils* utils, double error, double dt);
double math_update_derivative(PIDMathUtils* utils, double current_val, double dt);
//void math_reset(PIDMathUtils* utils);

// Helper function (Static inline for performance)
static inline double sign(double x) {
    return (double)((x > 0) - (x < 0));
}

#endif