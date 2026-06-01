#ifndef SWITCHING_MODULE_H
#define SWITCHING_MODULE_H

#include "../headers/vehical_state.h"

#ifdef __cplusplus
extern "C" {
#endif


void switcher(Sim_threads* threads_info,char target_mode);
void switch_checker(SystemState* state);


#ifdef __cplusplus
}
#endif

#endif // SWITCHING_MODULE_H