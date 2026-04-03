// #include "fixed_mpc_grt_rtw/fixed_mpc.h"
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "headers/vehical_state.h"
#include "headers/mpc_add_on.h"
#include <stdio.h>
#include <adaptive_mpc_wrapper/adaptive_mpc_wrapper.h>
#include "adaptive_mpc_wrapper/adaptive_mpc_wrapper_types.h"
#include "adaptive_mpc_wrapper/adaptive_mpc_wrapper_initialize.h"

real_T acceleration = 0;
const double Ts = 0.1;

void MPC_gap_based_controller(SystemState* shared_system_state) {
    //declaring variables out of the loop 
    double v_ego ;
    double v_lead;
    double x_lead;
    double x_ego;

    double desired_gap;
    double measured_gap;
    double gap_error;

    double y[2];
    double r[2];

    double md;

    double next_mpc_time = 0.0;
    double sim_time = 0.0;

    static struct5_T stateData;     // Persistent state/memory
    static struct6_T onlineData;    // Signals and model matrices
    static struct5_T next_state;    // Temporary for the next step output
    
    // Define the Adaptive Model Matrices (3x3 A, 3x2 B, etc.)

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
    while(true){ 

                v_ego = atomic_load(&shared_system_state->v_ego);
                v_lead = atomic_load(&shared_system_state->v_lead);
                x_lead = atomic_load(&shared_system_state->x_lead);
                x_ego = atomic_load(&shared_system_state->pos_x);

                desired_gap = compute_desired_gap_ratelimited(v_lead, Ts);
                measured_gap = x_lead - x_ego;
                gap_error = measured_gap - desired_gap;

                // Prepare input arrays 
                y[0]=gap_error;
                y[1]=v_ego;

                //r[2] = {0.0, v_lead};
                r[0]=0;
                r[1]=v_lead;

                md = v_lead;

                // 2. The MPC already "knows" its weights. Just call it:
                adaptive_mpc_wrapper(&stateData, &onlineData, y, r, md, 
                    Ad, Bd, Cd, Dd, &u, &next_state);

                printf("acceleration cmd (u): %f\n",u);


                // 3. Update the memory for the next loop
                stateData = next_state;

                // 4. Send 'u' to your car's accelerator
                acceleration=u;
                atomic_store(&shared_system_state->force_cmd,acceleration*1500); //F=a*m
                
                // Wait for MPC_TS (0.1s)
                
            next_mpc_time += Ts;
        }
        usleep(10000); // 10 ms
    }
