#include "switching_moduale.h"
#include <pthread.h>
#include <stdio.h>

void switcher(Sim_threads* threads_info,char target_mode) {
    printf("step one \n");
    printf("current mode: %c, target mode: %c\n", threads_info->current_mode, threads_info->target_mode);


        printf("right section \n");
        //switch required

        if(target_mode == 'M') {
            printf("in the switchin to MPC controller...\n");

            pthread_mutex_lock(&threads_info->ctrl_args->state->lock);

            pthread_cancel(threads_info->LQR_thread);
            printf(threads_info->LQR_thread == 0 ? "LQR thread successfully cancelled.\n" : "Failed to cancel LQR thread.\n");
            pthread_create(&threads_info->MPC_thread, NULL, (void* (*)(void*))MPC_gap_based_controller, threads_info->ctrl_args->state);

            threads_info->ctrl_args->state->pos_x =0;
            threads_info->ctrl_args->state->v_ego = 20.0;  
            threads_info->ctrl_args->state->ego_acceleration = 0.0;

            threads_info->ctrl_args->state->v_lead = 20.0;  
            threads_info->ctrl_args->state->lead_acceleration = 0.0;          
            threads_info->ctrl_args->state->x_lead = threads_info->ctrl_args->state->pos_x + 30.0; 

            threads_info->ctrl_args->state->force_cmd = 0.0;
            threads_info->ctrl_args->state->target_speed = 20.0;
            threads_info->current_mode = 'M';

            pthread_mutex_unlock(&threads_info->ctrl_args->state->lock);
        }
        else if(target_mode == 'L') {
            printf("in the switchin to LQR controller...\n");
            pthread_mutex_lock(&threads_info->ctrl_args->state->lock);

            pthread_cancel(threads_info->MPC_thread);
            pthread_create(&threads_info->LQR_thread, NULL, (void* (*)(void*))LQR_speed_base_controller, threads_info->ctrl_args);

            threads_info->ctrl_args->state->pos_x =0;
            threads_info->ctrl_args->state->v_ego = 20.0;  
            threads_info->ctrl_args->state->ego_acceleration = 0.0;

            threads_info->ctrl_args->state->v_lead = 0.0;  
            threads_info->ctrl_args->state->lead_acceleration = 0.0;          
            threads_info->ctrl_args->state->x_lead = threads_info->ctrl_args->state->pos_x - 30.0;  //hide it

            threads_info->ctrl_args->state->force_cmd = 0.0;
            threads_info->ctrl_args->state->target_speed = 20.0;
            threads_info->current_mode = 'L';

            pthread_mutex_unlock(&threads_info->ctrl_args->state->lock);
        }
}

void switch_checker(SystemState* state) {

}