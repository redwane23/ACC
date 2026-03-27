#ifndef MPC_ADD_ON_H
#define MPC_ADD_ON_H


#include "vehical_state.h"

void mpc_variable_initialization(SystemState* shared_system_state);
void mpc_variable_update(SystemState* shared_system_state);
double compute_desired_gap_ratelimited(double v_ego, double dt);
#endif 