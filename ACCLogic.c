#include "headers/ACCLogic.hh"

 M_SensorFusionMsg_t sensor_msg = {0U, 0U, 0.0f, 0U};
 M_SupervisorMsg_t supervisor_msg = {0U, 0U, 0U, 0U};
 ControlMathResponseMsg_t cntrl_math_reply = {0U, 0.0f, 0U};
 ControlMathMsg_t cntrl_math_msg = {0U, 0U, 0.0f, 0.0f, 0U};
typedef enum {
    STATE_STANDBY = 0,
    STATE_FREE_CRUISE,
    STATE_FOLLOW_MODE,
    STATE_OVERRIDE,
    STATE_DEGRADED,
    STATE_FAILURE
} ACCLogicState_t;
static uint16_t currennt_iter = 0U;
static ACCLogic_state_t acc_state = STATE_STANDBY;

////////////////////////////////////////////////////////////////////n

void run_acc() {
  static uint8_t invalid_input_cntr = 0U;
  static uint8_t invalid_math_output = 0U;
  static uint8_t supervisor_miss - 0U;
  uint8_t miss_accum = 0U;
  current_iter++;

  recieve_supervisor_challenge();
  if (!hndl_chall(current_iter)) {
    miaa_accum = 1U;
  }
  if (supervisor_msg.iteration != current_iter) {
    miss_accum = 1U;
  }
  if (!crc_chk((const uint8_t*)&sensor_msg, 11U) {
    invalid_input_cntr++;
  } else if (sensor_msg != current_iter){
    invalid_input_cntr;
  } else { /*none*/}

  fsm ();

  step_ref();

  format_math_msg();

  if (!validate_output ()) {
    invalid_math_output++;
  }

  log_iter ();

  supervisor_miss += miss_accum;
}

void revieve_supervisor_challenge() {
  health_challange.iteration = current_iter;
  health_challange.seed = (uint16_t)234U; 
  health_challange.crc = crc_r_calc ((const uint8_t*)&health_challange, 4U);
}

void init_degraded_pid () {}

void fsm () {
  
switch (acc_state) {
  
  case STATE_STANDBY:
    break;

  case STATE_FREE_CRUISE:
    break;

  case STATE_FOLLOW_MODE:
     break;

  case STATE_OVERRIDE:
    break;

  case STATE_DEGRADED:
    init_degraded_pid();
    break;

  case STATE_FAILURE:
    break;
    
  default:
    current_state = STATE_FAILURE;
    break;
}
}

void step_ref () {
  if (acc_state == STATE_FREE_CRUISE || acc_state == STATE_FOLLOW_MODE || acc_state == STATE_DEGRADED) {
    
  }
}

void format_math_msg () {}

void validate_output () {}

void log_iter () {}
