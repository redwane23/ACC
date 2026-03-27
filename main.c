#include "headers/vehical_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdatomic.h>

int main(){
    

        //lauching safety module first
        bool running = true;
        bool mode_switch_condition = false; 

        //char modes [] = {"manual", "lqr", "mpc"}; i wanted to use string but swtich  are dump
        int modes [3] = {0,1,2};
        int current_mode = modes[1]; 

        printf("Starting the controller in %d mode.\n", current_mode);
        printf("hello");
        // call sensor reading module


        //update_state();


        //determine the mode of operation based on the state of the car and the environment
        //set_initial_mode();


        //initialize the shared state and the PID controller math module
        SystemState shared_system_state;;
        PIDMathUtils speed_pid;
        controller_args_t* args = malloc(sizeof(controller_args_t));

        atomic_store(&shared_system_state.v_ego, 20.0);  // we used . instead of -> because it's not a pointer but a direct struct variable
        atomic_store(&shared_system_state.pos_x, 0.0);
        atomic_store(&shared_system_state.ego_acceleration, 0.0);
        // atomic_store(&state.v_error, 0.0);
        // atomic_store(&state.z, 0.0);

        atomic_store(&shared_system_state.v_lead, 20.0);
        atomic_store(&shared_system_state.x_lead, 30.0);
        atomic_store(&shared_system_state.lead_acceleration, 0.0);
        
        atomic_store(&shared_system_state.force_cmd, 0.0);
        atomic_store(&shared_system_state.running, true);


        pthread_t sim_thread;
        pthread_t ctrl_thread;

        // pthread_create(thread_id, attributes, function_pointer, argument_pointer)
        if (pthread_create(&sim_thread, NULL, run_simulation, &shared_system_state) != 0) {
            fprintf(stderr, "Fatal Error: Controller failed to create thread: %d\n", 101);
            exit(101);
        }


        switch(current_mode) {
            case 0: 
                //running loop with no effect just ready
            break;

            case 1: 

            args->state = &shared_system_state;
            args->pid   = &speed_pid;

                if (pthread_create(&ctrl_thread, NULL, (void* (*)(void*))LQR_speed_base_controller, args)  != 0) {
                    fprintf(stderr, "Fatal Error: Controller failed to create thread:: %d\n", 101);
                    exit(101);
                }
            break;

            case 2: 
                printf("Starting the MPC controller thread.\n");
            if (pthread_create(&ctrl_thread, NULL, (void* (*)(void*))MPC_gap_based_controller, &shared_system_state) != 0) {
                fprintf(stderr, "Fatal Error: Controller failed to create thread:: %d\n", 101);
                exit(101);
            }

            break;
        
            default:

                current_mode = modes[0];
        }


        while(running) {
            //check for mode switch conditions this function will take the pointer and change the current mode in needed 
           // mode_switch_condition = check_mode_switch_conditions(&current_mode); 


            // if(mode_switch_condition){
            //     // call the switching module
            // }




            //data logger module (KAFKA)
        }
 
    
        // pthread_join(thread_id, return_value_pointer)
        pthread_join(sim_thread, NULL);
        pthread_join(ctrl_thread, NULL);


    return EXIT_SUCCESS;

}