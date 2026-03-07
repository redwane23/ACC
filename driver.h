#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

#include <stdbool.h>
#include <stdatomic.h>
#include "math_modules/pid_math_module.h"

typedef struct {
    _Atomic double v_error;
    _Atomic double acceleration;
    _Atomic double z;
    _Atomic double cur_velocity;
    _Atomic double pos_x;
    
    _Atomic double force_cmd;
    atomic_bool running;
} VehicleState;



// Control and Simulation Logic
// We pass pointers (VehicleState*) instead of C++ references (VehicleState&)
void LQR_speed_base_controller(VehicleState* state, MathUtils* pid);
void run_simulation(VehicleState* state);

bool check_mode_switch_conditions(const char* current_mode);

#endif