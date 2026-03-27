#include "headers/vehical_state.h"
#include "math_modules/pid_math_module.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <stdatomic.h>

// Assuming sign() and MathUtils helpers are provided by your headers as mentioned
extern double sign(double x); 

void LQR_speed_base_controller(void* arg) {
    controller_args_t* args = (controller_args_t*)arg;
    SystemState* state = args->state;
    PIDMathUtils* pid= args->pid;


    //void LQR_speed_base_controller(SystemState* state, PIDMathUtils* pid);

        double K[3] = {    0.1098 ,   0.0966  ,  0.0010};
        double PID[3] = {1, 0.05 , 0.7};

        int m = 1500;           // Mass [kg]
        float g = 9.81;           // Gravity
        float rho = 1.225;        // Air density
        float Cd = 0.3;           // Drag coefficient
        float Af = 2.2;           // Frontal area
        float Cr = 0.015;         // Rolling resistance
        float J_engine = 0.15;    // Engine rotational inertia [kg·m²]
        float J_wheels = 1.2;     // Wheel rotational inertia [kg·m²]
        float r_wheel = 0.3;      // Wheel radius [m]
        float gear_ratio = 4.0;   // Overall gear ratio

        double u_lqr = 0.0;
        double last_accel_cmd=0;
        double desired_accel = 0.0;
        double max_jerk = 2.0; // Maximum jerk (m/s^3
        double accel_cmd=0;
        double grade_angle=0;

        double curent_velocity = atomic_load(&state->v_ego);
        double v_error;
        double acceleration;
        double z;
        double finla_output;

        double dt;
        
        struct timespec last_time;
        clock_gettime(CLOCK_MONOTONIC, &last_time);

        struct timespec next_tick;
        clock_gettime(CLOCK_MONOTONIC, &next_tick);
        
        struct timespec last_send_time;
        clock_gettime(CLOCK_MONOTONIC, &last_send_time);

        while (true)
        {    
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            
            // next_tick += target_interval (10000us = 10ms)
            next_tick.tv_nsec += 10000000;
            if (next_tick.tv_nsec >= 1000000000L) {
                next_tick.tv_sec++;
                next_tick.tv_nsec -= 1000000000L;
            }

            struct timespec current_time;
            clock_gettime(CLOCK_MONOTONIC, &current_time);

            double elapsed = (current_time.tv_sec - last_time.tv_sec) + 
                             (current_time.tv_nsec - last_time.tv_nsec) / 1e9;
            last_time = current_time;
            dt = elapsed;

            double time_since_send = (now.tv_sec - last_send_time.tv_sec) + 
                                     (now.tv_nsec - last_send_time.tv_nsec) / 1e9;

            if (time_since_send >= 0.066) { // 66ms
                    //read from sensors (in our case we read from the shared state updated by the sim)
                    v_error = atomic_load(&state->v_error);
                    acceleration = atomic_load(&state->ego_acceleration);
                    z = atomic_load(&state->z);
                
                printf("v_error : %f m/s, acceleration: %f m/s^2,, z: %f\n", v_error, acceleration, z);

                u_lqr = -( (K[0] * v_error) +
                            (K[1] * acceleration) +
                            (K[2] * z) );

                printf("Computed LQR Output (acceleration Command): %f m/s^2\n", u_lqr);

                desired_accel = u_lqr;
                last_send_time = now;
            }
                
            double diff = desired_accel - last_accel_cmd;

            if (fabs(diff) > (max_jerk * dt)) {
                accel_cmd = last_accel_cmd + sign(diff) * (max_jerk * dt);            
            }
            else{
                accel_cmd = desired_accel;
            }
            last_accel_cmd = accel_cmd;

        float F_inertia = m * accel_cmd; 
        float F_aero = 0.5 * rho * Cd * Af * pow(curent_velocity, 2); 
        float F_roll = m * g * Cr; 
        float F_grade = m * g * sin(grade_angle); 
        float J_total = J_engine * pow(gear_ratio,2) + J_wheels; 
        float m_rotational_equiv = J_total / pow(r_wheel,2); 
        float F_rotational = m_rotational_equiv * accel_cmd; 
        
        float F_ffwd = F_inertia + F_aero + F_roll + F_grade + F_rotational;

        double integral_v_error = math_update_integral(pid, v_error, dt);
        double derivative_v_error = math_update_derivative(pid, acceleration, dt);

        double u_pid = (PID[0] * v_error) + (PID[1] * integral_v_error) + (PID[2] * derivative_v_error);

        finla_output = F_ffwd + u_pid;

        atomic_store(&state->force_cmd, finla_output);

        // this part is mac conpatibale " only "to sleep till the next loop
        // i found this on stackoverflow and it seems to be the most accurate way to sleep for a specific time in C (hot sure if it work right)
        struct timespec sleep_now;
        clock_gettime(CLOCK_MONOTONIC, &sleep_now);
        double time_to_sleep = (next_tick.tv_sec - sleep_now.tv_sec) + 
                               (next_tick.tv_nsec - sleep_now.tv_nsec) / 1e9;
        if (time_to_sleep > 0) {
            struct timespec delay;
            delay.tv_sec = (time_t)time_to_sleep;
            delay.tv_nsec = (long)((time_to_sleep - (double)delay.tv_sec) * 1e9);
            nanosleep(&delay, NULL);
        }
        else {
            printf("Warning: Controller loop is running behind schedule by %f seconds\n", -time_to_sleep);
        }
}
}