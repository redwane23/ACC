#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

#include <stdbool.h>
#include <stdatomic.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CONTROLLER_LQR,
    CONTROLLER_MPC
} ControllerMode;


typedef struct {
    //lqr related states
    _Atomic double v_error;
    _Atomic double z; //integral of velocity error

    //mpc related states
    _Atomic double v_lead;
    _Atomic double x_lead;
    _Atomic double lead_acceleration;

    //shared in both
    _Atomic double pos_x;
    _Atomic double v_ego;
    _Atomic double ego_acceleration;

    _Atomic double force_cmd;

    ControllerMode mode; //mode switching variable
    atomic_bool running;

} SystemState;// this strcture need some update to seperate the logic somehowe

typedef struct {
    double integral;      // accumulated integral value
    double prev_error;    // previous error for derivative (position mode)
    double prev_val;      // previous value for derivative (velocity/measurement mode)
    double max_integral;  // anti-windup limit (optional)
    double min_integral;  // anti-windup limit (optional)
} PIDMathUtils;

typedef struct {
    SystemState* state;
    PIDMathUtils* pid;
} controller_args_t;


// Control and Simulation Logic
void LQR_speed_base_controller(void* arg);
void MPC_gap_based_controller(SystemState* state);
void* run_simulation(void* arg);
bool check_mode_switch_conditions(const char* current_mode);

#ifdef __cplusplus
}
#endif

#endif // VEHICLE_STATE_H