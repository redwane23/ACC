#ifndef MPC_GAP_BASED_CONTROLLER_H
#define MPC_GAP_BASED_CONTROLLER_H

#include "../headers/vehical_state.h"

int update_vehicle_physics(VehicleState* state, double u_cmd, double dt,float TAU);
double calculate_desired_gap(double v_ego,double A_COEFF,double B_COEFF,double C_COEFF,float VIS_FACTOR);

#endif