#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CONTROLLER_LQR,
    CONTROLLER_MPC
} ControllerMode;

#ifdef __cplusplus
    #include <atomic>
    // C++ version
    typedef std::atomic<double> atomic_double_t;
    typedef std::atomic<bool>   atomic_bool_t;
#else
    #include <stdatomic.h>
    // C version
    typedef _Atomic double atomic_double_t;
    typedef _Atomic bool   atomic_bool_t;
#endif

typedef struct {
    //Mutex to protect the data
    pthread_mutex_t lock;

    //lqr related states
    double v_error;
    double digital_velocity; 
    double target_speed;
    double previous_velocity;
    
    //mpc related states
    double v_lead;
    double x_lead;
    double lead_acceleration;

    //shared in both
    double pos_x;
    double v_ego;
    double ego_acceleration;

    double force_cmd;
    
    ControllerMode mode;
    bool running; 
} SystemState;

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


typedef struct {
    pthread_t MPC_thread;
    pthread_t LQR_thread;

    char current_mode ;
    char target_mode ;

    controller_args_t* ctrl_args;

} Sim_threads;


// Control and Simulation Logic
void LQR_speed_base_controller(void* arg);
void MPC_gap_based_controller(SystemState* state);
void* run_simulation(void* arg);
bool check_mode_switch_conditions(const char* current_mode);

#ifdef __cplusplus
}
#endif

#endif // VEHICLE_STATE_H