#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

#include <stdbool.h>
#include <stdatomic.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    _Atomic double v_error;
    _Atomic double acceleration;
    _Atomic double z;
    _Atomic double cur_velocity;
    _Atomic double pos_x;
    
    _Atomic double force_cmd;
    atomic_bool running;
} VehicleState;

typedef struct {
    _Atomic double v_ego;
    _Atomic double x_ego;
    _Atomic double v_lead;
    _Atomic double x_lead;
    _Atomic double pos_x;
    
    _Atomic double force_cmd;
    atomic_bool running;
} SystemState;

typedef struct {
    double integral;      // accumulated integral value
    double prev_error;    // previous error for derivative (position mode)
    double prev_val;      // previous value for derivative (velocity/measurement mode)
    double max_integral;  // anti-windup limit (optional)
    double min_integral;  // anti-windup limit (optional)
} PIDMathUtils;

// Control and Simulation Logic
void LQR_speed_base_controller(VehicleState* state, PIDMathUtils* pid);
void MPC_gap_based_controller(SystemState* state);
void* run_simulation(void* arg);
bool check_mode_switch_conditions(const char* current_mode);

#ifdef __cplusplus
}
#endif

#endif // VEHICLE_STATE_H