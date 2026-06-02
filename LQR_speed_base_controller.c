#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 199309L
#include "headers/vehical_state.h"
#include "math_modules/pid_math_module.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

extern double sign(double x);

void LQR_speed_base_controller(void* arg) {
    printf("LQR Controller started.\n");
    controller_args_t* args = (controller_args_t*)arg;
    SystemState* state = args->state;
    PIDMathUtils* pid = args->pid;

    // double K[3] = { 0.1298 , 0.0966 , 0.0010};
    double K[2] = {10.235326 , 4.534963};
    int m = 1500; 
    float g = 9.81; 
    float rho = 1.225; 
    float Cd = 0.3; 
    float Af = 2.2; 
    float Cr = 0.015; 
    float J_engine = 0.15; 
    float J_wheels = 1.2; 
    float r_wheel = 0.3; 
    float gear_ratio = 4.0; 

    double u_lqr = 0.0;
    double last_accel_cmd = 0;
    double desired_accel = 0.0;
    double max_jerk = 5.0; 
    double accel_cmd = 0;
    double grade_angle = 0;
    double d;
    
    // Initial read
    pthread_mutex_lock(&state->lock);
    double curent_velocity = state->v_ego;
    pthread_mutex_unlock(&state->lock);

    double v_error = 0;
    double acceleration = 0;
    double z = 0;
    double finla_output;
    double dt;

    struct timespec last_time;
    clock_gettime(CLOCK_MONOTONIC, &last_time);
    struct timespec next_tick;
    clock_gettime(CLOCK_MONOTONIC, &next_tick);
    struct timespec last_send_time;
    clock_gettime(CLOCK_MONOTONIC, &last_send_time);

    while (true) {
        
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);

        next_tick.tv_nsec += 10000000;
        if (next_tick.tv_nsec >= 1000000000L) {
            next_tick.tv_sec++;
            next_tick.tv_nsec -= 1000000000L;
        }

        struct timespec current_time;
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        double elapsed = (current_time.tv_sec - last_time.tv_sec) + (current_time.tv_nsec - last_time.tv_nsec) / 1e9;
        last_time = current_time;
        dt = elapsed;

        double time_since_send = (now.tv_sec - last_send_time.tv_sec) + (now.tv_nsec - last_send_time.tv_nsec) / 1e9;
        
        if (time_since_send >= 0.066) { 

            pthread_mutex_lock(&state->lock);

            v_error = state->v_error;
            acceleration = state->ego_acceleration;
            // z = state->z;
            curent_velocity = state->v_ego; 
            bool should_run = state->running;
            d=state->digital_velocity - curent_velocity;
            pthread_mutex_unlock(&state->lock);

            if (!should_run) break;

             printf("v_error : %f m/s, acceleration: %f m/s^2  \n ", v_error, acceleration);
            u_lqr = -( (K[0] * v_error) + (K[1] * acceleration) )+d;
            desired_accel = u_lqr;
            last_send_time = now;
        }

        double diff = desired_accel - last_accel_cmd;
        if (fabs(diff) > (max_jerk * dt)) {  //fabs for absulute value
            accel_cmd = last_accel_cmd + sign(diff) * (max_jerk * dt);
        } else {
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



   
        finla_output = accel_cmd * m ; 
        
        //don't apply external forces(F_ffwd) becouse the sim doesn't have them yet


        pthread_mutex_lock(&state->lock);
        state->force_cmd = finla_output;
        pthread_mutex_unlock(&state->lock);
        printf("finla_output: %f m/s^2 \n ", finla_output);

        struct timespec sleep_now;
        clock_gettime(CLOCK_MONOTONIC, &sleep_now);
        double time_to_sleep = (next_tick.tv_sec - sleep_now.tv_sec) + (next_tick.tv_nsec - sleep_now.tv_nsec) / 1e9;
        
        if (time_to_sleep > 0) {
            struct timespec delay;
            delay.tv_sec = (time_t)time_to_sleep;
            delay.tv_nsec = (long)((time_to_sleep - (double)delay.tv_sec) * 1e9);
            nanosleep(&delay, NULL);
        } else {
            printf("Warning: Controller loop is running behind schedule by %f seconds\n", -time_to_sleep);
        }
    }
}
