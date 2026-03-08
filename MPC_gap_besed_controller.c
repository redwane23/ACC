#include <stdio.h>
#include <math.h>
#include "headers/vehical_state.h" // Your central header

//constantes
#define TAU 0.5
#define TS 0.1
#define A_COEFF 3.0
#define B_COEFF 0.7
#define C_COEFF 0.035
#define VIS_FACTOR 1.0
#define MAX_CHANGE_RATE 2.0

// Simplified Controller (The "mpcmove" equivalent)
// Note: Real MPC requires an optimization library. 
// This placeholder implements the logic flow.
double compute_control_action(VehicleState* state, double v_lead, double x_lead) {
    double v_ego = atomic_load(&state->cur_velocity);
    double x_ego = atomic_load(&state->pos_x);
    
    // 1. Calculate desired gap
    double d_target = calculate_desired_gap(v_ego);
    
    // 2. Calculate errors
    double actual_gap = x_lead - x_ego;
    double gap_error = actual_gap - d_target;
    double v_error = v_lead - v_ego;

    // 3. MPC/Control Law
    // In a real project, you'd call a QP Solver here.
    // For now, we use a high-gain feedback as a placeholder:
    double K_gap = 0.8; 
    double K_vel = 0.5;
    double u = (K_gap * gap_error) + (K_vel * v_error);

    // 4. Apply Constraints (mpcobj.MV.Min/Max)
    if (u > 3.0) u = 3.0;
    if (u < -5.0) u = -5.0;

    return u;
}