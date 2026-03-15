#include "mpc_test_grt_rtw/mpc_test.h"
#include <string.h>   // for memcpy
#include <math.h>
#include <unistd.h>   // for usleep
#include "headers/vehical_state.h"

void wait_for_next_tick(double Ts) {
    usleep((useconds_t)(Ts * 1e6));  // Ts in seconds → microseconds
}

// Example plant matrices (replace with your actual values)
static const real_T A[9] = {
    0.0, -1.0, 0.0,
    0.0,  0.0, 1.0,
    0.0,  0.0, -2.0    // -1/tau with tau=0.5
};
static const real_T B[3] = {0.0, 0.0, 2.0};    // 1/tau
static const real_T C[6] = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0
};
static const real_T D[2] = {0.0, 0.0};
static const real_T Ts = 0.1;

// External lead velocity (example)
extern real_T get_lead_velocity(void);
extern real_T get_ego_velocity(void);
extern real_T get_gap_error(void);
extern void apply_acceleration(real_T accel);

void MPC_gap_based_controller(SystemState* state) {
    // Initialize the controller
    mpc_test_initialize();

    // State estimates (replace with real estimator if available)
    real_T X[3] = {0.0, 0.0, 0.0};   // [gap_error; velocity; acceleration]
    real_T DX[3] = {0.0, 0.0, 0.0};
    real_T U = 0.0;                   // previous control

    // Control loop (runs every Ts seconds)
    while (1) {
        // 1. Read sensors
        // real_T v_lead = get_lead_velocity();
        
        // real_T v_ego  = get_ego_velocity();
        // real_T gap_err = get_gap_error();

        // real_T meas[2] = {gap_err, v_ego};
        // real_T ref[2]  = {0.0, v_lead};   // desired gap error = 0, track lead speed

        // 2. Fill the PlantBus structure
        // PlantBus plant;
        // memcpy(plant.A, A, sizeof(A));
        // memcpy(plant.B, B, sizeof(B));
        // memcpy(plant.C, C, sizeof(C));
        // memcpy(plant.D, D, sizeof(D));
        // plant.U = U;                       // previous control
        // memcpy(plant.Y, meas, sizeof(meas)); // current measurement (Y is same as meas here)
        // memcpy(plant.X, X, sizeof(X));      // current state estimate
        // memcpy(plant.DX, DX, sizeof(DX));   // state derivative (if not available, set to zero)

        // 3. Compute control
        real_T mv;
       // mpc_test_step(ref, meas, &plant, &mv);
        mpc_test_step();

        // 4. Apply control
        // apply_acceleration(mv);

        // 5. Update previous control for next step
        U = mv;

        // 6. (Optional) Update state estimator here to get new X, DX for next iteration

        // 7. Wait for next sample (use timer, sleep, etc.)
        wait_for_next_tick(Ts);
    }
}