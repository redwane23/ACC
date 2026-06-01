#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 199309L
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include "headers/vehical_state.h"
#include "headers/mpc_add_on.h"
#include <stdio.h>
#include <adaptive_mpc_wrapper/adaptive_mpc_wrapper.h>
#include "adaptive_mpc_wrapper/adaptive_mpc_wrapper_types.h"
#include "adaptive_mpc_wrapper/adaptive_mpc_wrapper_initialize.h"

real_T acceleration = 0;
const double Ts = 0.1;

void MPC_gap_based_controller(SystemState* shared_system_state) {
    // printf("MPC thread %lu starting, stateData fields: some_field = %f\n", pthread_self(), stateData.some_field);

    // declaring variables out of the loop
    double v_ego;
    double v_lead;
    double x_lead;
    double x_ego;
    double desired_gap;
    double measured_gap;
    double gap_error;
    double y[2];
    double r[2];
    double md;
    
    static struct5_T stateData; // Persistent state/memory
    static struct6_T onlineData; // Signals and model matrices
    static struct5_T next_state; // Temporary for the next step output

    double u = 0.0;
    adaptive_mpc_wrapper_initialize();

    // 3x3 Ad (Column-major from MATLAB)
    static double Ad[9] = {1.0, 0.0, 0.0, -0.1, 1.0, 0.0, 0.0, 0.0906, 0.8187};
    // 3x2 Bd
    static double Bd[6] = {0.0, 0.0, 0.0906, 0.1, 0.0, 0.0};
    // 2x3 Cd
    static double Cd[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    // 2x2 Dd
    static double Dd[4] = {0.0, 0.0, 0.0, 0.0};

    printf("MPC Controller started.\n");

    while (true) {
        printf("MPC Controller loop iteration.\n");
        // PROTECTED READ SECTION 
        pthread_mutex_lock(&shared_system_state->lock);
        v_ego = shared_system_state->v_ego;
        v_lead = shared_system_state->v_lead;
        x_lead = shared_system_state->x_lead;
        x_ego = shared_system_state->pos_x;
        
        bool should_run = shared_system_state->running;
        pthread_mutex_unlock(&shared_system_state->lock);

        if (!should_run) break;

        desired_gap = compute_desired_gap_ratelimited(v_lead, Ts);
        measured_gap = x_lead - x_ego;
        gap_error = measured_gap - desired_gap;
        printf("v_ego: %f, v_lead: %f, x_ego: %f, x_lead: %f, desired_gap: %f, measured_gap: %f, gap_error: %f\n", 
                v_ego, v_lead, x_ego, x_lead, desired_gap, measured_gap, gap_error);
        // Prepare input arrays
        y[0] = gap_error;
        y[1] = v_ego;
        r[0] = 0;
        r[1] = v_lead;
        md = v_lead;

        adaptive_mpc_wrapper(&stateData, &onlineData, y, r, md, Ad, Bd, Cd, Dd, &u, &next_state);

        stateData = next_state;

        // PROTECTED WRITE SECTION
        pthread_mutex_lock(&shared_system_state->lock);
        shared_system_state->force_cmd = u * 1500.0;
        pthread_mutex_unlock(&shared_system_state->lock);
        printf("MPC u = %f (accel m/s²), force_cmd = %f\n", u, u * 1500.0);
        printf("gap_error = %f, measured_gap = %f, desired_gap = %f\n", gap_error, measured_gap, desired_gap);
        // Wait for MPC_TS (0.1s)
        // usleep(100000); 
    }
}
