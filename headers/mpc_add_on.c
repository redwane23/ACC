// #include "mpc_add_on.h"
// #include "../fixed_mpc_grt_rtw/fixed_mpc.h"   // the generated header
// #include <stdio.h>

// // --------------------------------------------------------------------------
// // Initialization – sets all constant and initial values
// // --------------------------------------------------------------------------
// void mpc_variable_initialization(SystemState* shared_system_state) {
//     // ----- Read current measurements from shared state -----
//     double measured_gap  = atomic_load(&shared_system_state->x_lead) - atomic_load(&shared_system_state->pos_x);
//     double measured_v_ego = atomic_load(&shared_system_state->v_ego);
//     double measured_a_ego = atomic_load(&shared_system_state->ego_acceleration);
//     double v_lead         = atomic_load(&shared_system_state->v_lead);
//     double Ts = 0.1;   // sample time

//     // ----- Discrete plant matrices (constant) -----
//     const double Ad[3][3] = {
//         {1.0,       -0.1,       -0.0046826882694954641},
//         {0.0,        1.0,        0.090634623461009076},
//         {0.0,        0.0,        0.81873075307798182}
//     };
//     const double Bd[3][2] = {
//         {0.0,        0.0046826882694954641},
//         {0.0,        0.090634623461009076},
//         {0.18126924692201815, 0.0}
//     };
//     const double Cd[2][3] = {
//         {1.0, 0.0, 0.0},
//         {0.0, 1.0, 0.0}
//     };
//     const double Dd[2][2] = {
//         {0.0, 0.0},
//         {0.0, 0.0}
//     };

//     // ----- Fill the 'model' bus (A, B, C, D, U, Y, X, DX) -----
//     // A (3x3)
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             fixed_mpc_U.A[i*3 + j] = Ad[i][j];
//         }
//     }
//     // B (3x2)
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 2; j++) {
//             fixed_mpc_U.B[i*2 + j] = Bd[i][j];
//         }
//     }
//     // C (2x3)
//     for (int i = 0; i < 2; i++) {
//         for (int j = 0; j < 3; j++) {
//             fixed_mpc_U.C[i*3 + j] = Cd[i][j];
//         }
//     }
//     // D (2x2)
//     for (int i = 0; i < 2; i++) {
//         for (int j = 0; j < 2; j++) {
//             fixed_mpc_U.D[i*2 + j] = Dd[i][j];
//         }
//     }

//     // Nominal state X (3x1)
//     fixed_mpc_U.X[0] = 0.0; //gap error
//     fixed_mpc_U.X[1] = v_lead;
//     fixed_mpc_U.X[2] = 0.0; //ecceleration

//     // Nominal output Y (2x1)
//     fixed_mpc_U.Y[0] = 0.0;
//     fixed_mpc_U.Y[1] = v_lead;

//     // Nominal input U (2x1)
//     fixed_mpc_U.U[0] = 0.0;      // MV nominal
//     fixed_mpc_U.U[1] = v_lead;   // MD nominal

//     // DX (3x1) – first call: set to zero
//     static double X_prev[3] = {0.0, 0.0, 0.0};
//     for (int i = 0; i < 3; i++) {
//         fixed_mpc_U.DX[i] = fixed_mpc_U.X[i] - X_prev[i];
//         X_prev[i] = fixed_mpc_U.X[i];
//     }

//     // ----- Measured outputs (mo port) – likely In9 -----
//     double gap_error = measured_gap;   // actual gap - desired gap (desired gap computed below)
//     // Compute desired gap (2‑second rule)
//     double desired_gap = 2.0 * measured_v_ego;
//     gap_error = measured_gap - desired_gap;   // because measured_gap is actual gap

//    fixed_mpc_U.In9[0] = gap_error;
//     fixed_mpc_U.In9[1] = measured_v_ego;

//     // ----- Reference signals (ref port) – likely In10 -----
//     fixed_mpc_U.In10[0] = 0.0;      // desired gap error = 0
//     fixed_mpc_U.In10[1] = v_lead;   // desired ego speed = lead speed

//     // -----  (md port) 
//     fixed_mpc_U.In11 = 0.0;          

//     // ----- (Optional) If the generated code has a parameter structure, set scale gain -----
//     // fixed_mpc_P.u_scale_Gain = 1.0;   // if used
// }


// static double desired_gap = 0.0;
// static double new_desired = 0.0;
// static double last_update_time = 0.0;  // keep track of time

// Rate‑limited desired gap calculation
double compute_desired_gap_ratelimited(double v_ego, double dt) {
    const double a = 3.0, b = 0.7, c = 0.035;
    double new_val = (a + b*v_ego + c*v_ego*v_ego);
    static double last_val = 0.0;
    if (last_val == 0.0) last_val = new_val;
    double max_change = 2.0 * dt;  // rate limit 2 m/s² * dt
    double delta = new_val - last_val;
    if (delta > max_change) delta = max_change;
    if (delta < -max_change) delta = -max_change;
    last_val = last_val + delta;
    return last_val;
}
// // --------------------------------------------------------------------------
// // Update – called at each simulation step
// // --------------------------------------------------------------------------

// void mpc_variable_update(SystemState* shared_system_state) {


//     // Print these values



//     // ----- Read current measurements -----
//     double measured_gap = atomic_load(&shared_system_state->x_lead) - atomic_load(&shared_system_state->pos_x);
//     double measured_v_ego = atomic_load(&shared_system_state->v_ego);
//     double measured_a_ego = atomic_load(&shared_system_state->ego_acceleration);
//     double v_lead         = atomic_load(&shared_system_state->v_lead);
//     double Ts = 0.1;


//     // ----- Update nominal values (X_nom, Y_nom, U_nom, DX) -----
//     // Nominal state
//     fixed_mpc_U.X[0] = 0.0;  
//     fixed_mpc_U.X[1] = v_lead;
//     fixed_mpc_U.X[2] = 0.0;  

//     // Nominal output
//     fixed_mpc_U.Y[0] = 0.0;
//     fixed_mpc_U.Y[1] = v_lead;

//     // Nominal input
//     fixed_mpc_U.U[0] = 0.0;
//     fixed_mpc_U.U[1] = v_lead;

//     // DX = X(k) - X(k-1) – using static persistence
//     static double X_prev[3] = {0.0, 0.0, 0.0};
//     for (int i = 0; i < 3; i++) {
//         fixed_mpc_U.DX[i] = fixed_mpc_U.X[i] - X_prev[i];
//         X_prev[i] = fixed_mpc_U.X[i];
//     }

//     // ----- Measured outputs (mo) -----
//     // double desired_gap = compute_desired_gap_ratelimited(measured_v_ego, Ts);  
//     double desired_gap = 1.5 * v_lead + 2.0;
//     printf("desired gap %f : \n",desired_gap);
//     double gap_error = measured_gap - desired_gap;
//     printf("gap_error %f : \n",gap_error);
//     fixed_mpc_U.In9[0] = gap_error;
//     fixed_mpc_U.In9[1] = measured_v_ego;
    
//     // Reference (ref)
//     fixed_mpc_U.In10[0] = 0.0;
//     fixed_mpc_U.In10[1] = v_lead;
    
//     // Measured disturbance (md)
//     fixed_mpc_U.In11 = v_lead;   
//     // ----- Previous MV – this is typically set by feeding back the block's own output.
//     // In Simulink you use a Unit Delay. In this external code, you must pass it as an argument.
//     // For now, we assume it is already set before calling mpc_variable_update.
//     // If not, you can store it in a static variable and update it after the MPC step.
    

//     printf("Update: measured_gap=%.2f, desired_gap=%.2f, gap_error=%.2f, v_ego=%.2f, v_lead=%.2f\n",
//         measured_gap, desired_gap, gap_error, measured_v_ego, v_lead);
// }