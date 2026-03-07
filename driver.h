#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

#include <stdbool.h>
#include <stdatomic.h>

typedef struct {
    _Atomic double v_error;
    _Atomic double acceleration;
    _Atomic double z;
    _Atomic double cur_velocity;
    _Atomic double pos_x;
    
    _Atomic double force_cmd;
    atomic_bool running;
} VehicleState;

/* MathUtils "Class" converted to a C Struct 
*/
typedef struct {
    double integral;
    double prev_value;
    double limit;
} MathUtils;



// Math Utility Functions
double math_update_integral(MathUtils* utils, double error, double dt);
double math_update_derivative(MathUtils* utils, double current_val, double dt);
void math_reset(MathUtils* utils);

// Helper function (Static inline for performance)
static inline double sign(double x) {
    return (double)((x > 0) - (x < 0));
}

// Control and Simulation Logic
// We pass pointers (VehicleState*) instead of C++ references (VehicleState&)
void LQR_speed_base_controller(VehicleState* state, MathUtils* pid);
void run_simulation(VehicleState* state);

bool check_mode_switch_conditions(const char* current_mode);

#endif