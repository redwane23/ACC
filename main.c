#define _DEFAULT_SOURCE
#include "headers/vehical_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

int main() {
    bool running = true;
    int modes[3] = {0, 1, 2};
    int current_mode = modes[1];
    printf("Starting the controller in %d mode.\n", current_mode);



    //Allocate SystemState
    SystemState *shared_system_state = malloc(sizeof(SystemState));
    pthread_mutex_init(&shared_system_state->lock, NULL);

    // Allocate PIDMathUtils 
    PIDMathUtils *speed_pid = malloc(sizeof(PIDMathUtils));
    memset(speed_pid, 0, sizeof(PIDMathUtils)); // Clear math values

    // Allocate controller args
    controller_args_t* args = malloc(sizeof(controller_args_t));
    args->state = shared_system_state; 
    args->pid = speed_pid;            

    // Allocate Thread Manager
    Sim_threads *controle_threads = malloc(sizeof(Sim_threads));
    controle_threads->ctrl_args = args;

    if (current_mode == 1) {
        printf("Initializing LQR controller.\n");
        controle_threads->current_mode = 'L';
        controle_threads->target_mode = 'L';
    } else if (current_mode == 2) {
        printf("Initializing MPC controller.\n");
        controle_threads->current_mode = 'M';
        controle_threads->target_mode = 'M';
    }
    //Initialize shared state using Mutex
    pthread_mutex_lock(&shared_system_state->lock);
    shared_system_state->running = true;
    shared_system_state->pos_x =0;
    shared_system_state->v_ego = 20.0;  
    shared_system_state->ego_acceleration = 0.0;

    shared_system_state->v_lead = 20.0;  
    shared_system_state->lead_acceleration = 0.0;          
    shared_system_state->x_lead =shared_system_state->pos_x + 31.0; 

    shared_system_state->force_cmd = 0.0;
    shared_system_state->target_speed = 20.0; //in m/s  
    pthread_mutex_unlock(&shared_system_state->lock);

    // 6. Start Threads
    switch(current_mode) {
        case 1:
            printf("Starting the LQR controller thread.\n");
            pthread_create(&controle_threads->LQR_thread, NULL, (void* (*)(void*))LQR_speed_base_controller, controle_threads->ctrl_args);
            break;
        case 2:
            printf("Starting the MPC controller thread.\n");
            pthread_create(&controle_threads->MPC_thread, NULL, (void* (*)(void*))MPC_gap_based_controller, shared_system_state);
            break;

    }

    pthread_t sim_thread;
    // Pass the pointer directly
    if (pthread_create(&sim_thread, NULL, run_simulation, controle_threads) != 0) {
        fprintf(stderr, "Fatal Error: Simulation thread failed\n");
        exit(101);
    }

    // 7. Main Loop
    while(running) {
        pthread_mutex_lock(&shared_system_state->lock);
        running = shared_system_state->running;
        pthread_mutex_unlock(&shared_system_state->lock);
        
        // usleep(10000); 
    }

    pthread_join(sim_thread, NULL);
    return EXIT_SUCCESS;
}
