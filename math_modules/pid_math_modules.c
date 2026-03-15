// math_utils.c
#include "../headers/vehical_state.h"
/**
 * Update integral term with anti-windup protection
 * 
 * @param utils   Pointer to PIDMathUtils struct containing integral state
 * @param error   Current error value
 * @param dt      Time step (seconds)
 * @return        Updated integral value
 */
double math_update_integral(PIDMathUtils* utils, double error, double dt) {
    if (!utils) return 0.0;
    
    // Basic integral accumulation
    utils->integral += error * dt;
    
    // Anti-windup clamping (if limits are set)
    if (utils->max_integral > utils->min_integral) {
        if (utils->integral > utils->max_integral) {
            utils->integral = utils->max_integral;
        } else if (utils->integral < utils->min_integral) {
            utils->integral = utils->min_integral;
        }
    }
    
    return utils->integral;
}

/**
 * Update derivative term (can work in two modes)
 * 
 * @param utils        Pointer to PIDMathUtils struct
 * @param current_val  Current value (error or measurement)
 * @param dt           Time step (seconds)
 * @return             Derivative value
 * 
 * Note: Two common modes:
 *   1. Derivative on error: pass error as current_val
 *   2. Derivative on measurement: pass measurement as current_val
 */
double math_update_derivative(PIDMathUtils* utils, double current_val, double dt) {
    if (!utils || dt <= 0.0) return 0.0;
    
    double derivative;
    
    // Check if we're using error-based or measurement-based derivative
    // This assumes we stored prev_error from last call
    // For measurement-based, store the measurement in prev_error
    derivative = (current_val - utils->prev_error) / dt;
    
    // Store current value for next derivative calculation
    utils->prev_error = current_val;
    
    return derivative;
}

/**
 * Alternative: Separate storage for error and measurement derivatives
 */
double math_update_derivative_error(PIDMathUtils* utils, double error, double dt) {
    if (!utils || dt <= 0.0) return 0.0;
    
    double derivative = (error - utils->prev_error) / dt;
    utils->prev_error = error;
    return derivative;
}

double math_update_derivative_measurement(PIDMathUtils* utils, double measurement, double dt) {
    if (!utils || dt <= 0.0) return 0.0;
    
    double derivative = (measurement - utils->prev_val) / dt;
    utils->prev_val = measurement;
    return derivative;
}

/**
 * Initialize the math utilities structure
 */
void math_utils_init(PIDMathUtils* utils, double max_integral, double min_integral) {
    if (!utils) return;
    
    utils->integral = 0.0;
    utils->prev_error = 0.0;
    utils->prev_val = 0.0;
    utils->max_integral = max_integral;
    utils->min_integral = min_integral;
}

/**
 * Reset the integral term (e.g., on mode change)
 */
void math_utils_reset_integral(PIDMathUtils* utils) {
    if (utils) {
        utils->integral = 0.0;
    }
}