#ifndef ACCLOGIC_H
#define ACCLOGIC_H

#include "hlth.h"

#pragma pack(push,1)
typedef struct {
    uint8_t mode;
    uint16_t iteration;
    float ego_speed;
    uint32_t crc;
} M_SensorFusionMsg_t;

typedef struct {
    uint8_t command_code;
    uint16_t iteration;
    uint32_t optional_params;
    uint32_t crc;
} M_SupervisorMsg_t;

typedef struct {
    uint16_t iteration;
    float delta_acceleration;
    uint32_t crc;
} ControlMathResponseMsg_t;

typedef struct {
    uint8_t mode; 
    uint16_t iteration;
    float delta_speed;
    float delta_time;
    uint32_t crc;
} ControlMathMsg_t;
#pragma pack(pop)

extern M_SensorFusionMsg_t sensor_msg;
extern M_SupervisorMsg_t supervisor_msg;
extern ControlMathResponseMsg_t cntrl_math_reply;
extern ControlMathMsg_t cntrl_math_msg;

#endif
