#include "driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

int main(){

        //lauching safety module first

        bool running = true;
        bool mode_switch_condition = false; 

        char modes [] = {"manual", "lqr", "mpc"};
        char current_mode = modes[0]; // default to manual mode

        // call sensor reading module


        //update_state();


        //determine the mode of operation based on the state of the car and the environment
        //set_initial_mode();


        //initialize the shared state and the PID controller
        VehicleState shared_state;
        MathUtils speed_pid;


        pthread_t sim_thread;
        // pthread_create(thread_id, attributes, function_pointer, argument_pointer)
        if (pthread_create(&sim_thread, NULL, (void* (*)(void*))run_simulation, &shared_state) != 0) {
            fprintf(stderr, "Fatal Error: Controller failed to create thread: %d\n", 101);
            exit(101);
        }


        switch(current_mode) {
            case 'manual': 
                //running loop with no effect just ready
            break;

            case 'lqr': 
                pthread_t ctrl_thread;

                if (pthread_create(&ctrl_thread, NULL, (void* (*)(void*))LQR_speed_base_controller, &shared_state) != 0) {
                    fprintf(stderr, "Fatal Error: Controller failed to create thread:: %d\n", 101);
                    exit(101);
                }
            break;

            case 'mpc': 

            break;
        
            default:

                current_mode = modes[0];
        }


        while(running) {
            //check for mode switch conditions this function will take the pointer and change the current mode in needed 
            mode_switch_condition = check_mode_switch_conditions(&current_mode); 

            if(mode_switch_condition){
                // call the switching module
            }




            //data logger module (KAFKA)

        }
 


        pthread_t ctrl_thread;

        if (pthread_create(&ctrl_thread, NULL, (void* (*)(void*))LQR_speed_base_controller, &shared_state) != 0) {
            fprintf(stderr, "Fatal Error: Controller failed to create thread:: %d\n", 101);
            exit(101);
        }
    

        // pthread_join(thread_id, return_value_pointer)
        pthread_join(sim_thread, NULL);
        pthread_join(ctrl_thread, NULL);


    return EXIT_SUCCESS;

}