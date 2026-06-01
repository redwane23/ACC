#include <mpc_math_module.h>
#include "../headers/vehical_state.h"


int update_vehicle_physics(VehicleState* state, double u_cmd, double dt,float TAU) {
    
    double current_a = atomic_load(&state->acceleration);
    double a_dot = (u_cmd - current_a) / TAU;
    double new_a = current_a + (a_dot * dt);
    
    double current_v = atomic_load(&state->cur_velocity);
    double new_v = current_v + (new_a * dt);
    
    double current_x = atomic_load(&state->pos_x);
    double new_x = current_x + (new_v * dt);


    atomic_store(&state->acceleration, new_a);
    atomic_store(&state->cur_velocity, new_v);
    atomic_store(&state->pos_x, new_x);
}

// Logic of the Quadratic Gap equations
double calculate_desired_gap(double v_ego,double A_COEFF,double B_COEFF,double C_COEFF,float VIS_FACTOR) {
    double gap = (A_COEFF + B_COEFF * v_ego + C_COEFF * pow(v_ego, 2)) * VIS_FACTOR;
    

    if (gap < 2.0) gap = 2.0;
    if (gap > 150.0) gap = 150.0;
    
    return gap;
}