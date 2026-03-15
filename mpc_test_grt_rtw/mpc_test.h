/*
 * mpc_test.h
 *
 * Code generation for model "mpc_test".
 *
 * Model version              : 1.11
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Wed Mar 11 21:00:25 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef mpc_test_h_
#define mpc_test_h_
#ifndef mpc_test_COMMON_INCLUDES_
#define mpc_test_COMMON_INCLUDES_
#include "rtwtypes.h"
// #include "rtw_continuous.h"
// #include "rtw_solver.h"
// #include "rt_logging.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* mpc_test_COMMON_INCLUDES_ */

#include "mpc_test_types.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include <float.h>
#include <string.h>
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T c_Hv[840];
  real_T Su[800];
} B_mpc_test_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T last_mv_DSTATE;               /* '<S2>/last_mv' */
  real_T LastPcov_PreviousInput[16];   /* '<S2>/LastPcov' */
  real_T last_x_PreviousInput[4];      /* '<S2>/last_x' */
  boolean_T Memory_PreviousInput[8];   /* '<S2>/Memory' */
} DW_mpc_test_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T A[9];                         /* '<Root>/A' */
  real_T B[3];                         /* '<Root>/B' */
  real_T C[6];                         /* '<Root>/C' */
  real_T D[2];                         /* '<Root>/In4' */
  real_T U;                            /* '<Root>/In5' */
  real_T X[3];                         /* '<Root>/In1' */
  real_T DX[3];                        /* '<Root>/In2' */
  real_T Y[2];                         /* '<Root>/In3' */
  real_T In6[2];                       /* '<Root>/In6' */
  real_T In7[2];                       /* '<Root>/In7' */
} ExtU_mpc_test_T;

/* Parameters (default storage) */
struct P_mpc_test_T_ {
  real_T E_zero_Value;                 /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/E_zero'
                                        */
  real_T F_zero_Value[2];              /* Expression: zeros(1,2)
                                        * Referenced by: '<S1>/F_zero'
                                        */
  real_T G_zero_Value;                 /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/G_zero'
                                        */
  real_T LastPcov_InitialCondition[16];/* Expression: lastPcov
                                        * Referenced by: '<S2>/LastPcov'
                                        */
  real_T ywt_zero_Value[2];            /* Expression: zeros(2,1)
                                        * Referenced by: '<S1>/y.wt_zero'
                                        */
  real_T uwt_zero_Value;               /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/u.wt_zero'
                                        */
  real_T duwt_zero_Value;              /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/du.wt_zero'
                                        */
  real_T extmv_zero_Value;             /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/ext.mv_zero'
                                        */
  real_T extmv_scale_Gain;             /* Expression: RMVscale
                                        * Referenced by: '<S2>/ext.mv_scale'
                                        */
  real_T last_mv_InitialCondition;     /* Expression: lastu+uoff
                                        * Referenced by: '<S2>/last_mv'
                                        */
  real_T last_x_InitialCondition[4];   /* Expression: lastx+xoff
                                        * Referenced by: '<S2>/last_x'
                                        */
  real_T md_zero_Value;                /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/md_zero'
                                        */
  real_T umin_zero_Value;              /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/umin_zero'
                                        */
  real_T umax_zero_Value;              /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/umax_zero'
                                        */
  real_T ymin_zero_Value[2];           /* Expression: zeros(2,1)
                                        * Referenced by: '<S1>/ymin_zero'
                                        */
  real_T ymax_zero_Value[2];           /* Expression: zeros(2,1)
                                        * Referenced by: '<S1>/ymax_zero'
                                        */
  real_T umin_scale4_Gain;         /* Expression: MVscale(:,ones(1,max(nCC,1)))'
                                    * Referenced by: '<S2>/umin_scale4'
                                    */
  real_T ymin_scale1_Gain[2];       /* Expression: Yscale(:,ones(1,max(nCC,1)))'
                                     * Referenced by: '<S2>/ymin_scale1'
                                     */
  real_T S_zero_Value;                 /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/S_zero'
                                        */
  real_T ymin_scale2_Gain;         /* Expression: MDscale(:,ones(1,max(nCC,1)))'
                                    * Referenced by: '<S2>/ymin_scale2'
                                    */
  real_T switch_zero_Value;            /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/switch_zero'
                                        */
  real_T mvtarget_zero_Value;          /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/mv.target_zero'
                                        */
  real_T uref_scale_Gain;              /* Expression: RMVscale
                                        * Referenced by: '<S2>/uref_scale'
                                        */
  real_T ecrwt_zero_Value;             /* Expression: zeros(1,1)
                                        * Referenced by: '<S1>/ecr.wt_zero'
                                        */
  int32_T FixedHorizonOptimizer_Ndis;  /* Expression: Ndis
                                        * Referenced by: '<S30>/FixedHorizonOptimizer'
                                        */
  boolean_T Memory_InitialCondition[8];/* Expression: iA
                                        * Referenced by: '<S2>/Memory'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_mpc_test_T {
  const char_T *errorStatus;
  //RTWLogInfo *rtwLogInfo; i manulay comented this 

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_mpc_test_T mpc_test_P;

/* Block signals (default storage) */
extern B_mpc_test_T mpc_test_B;

/* Block states (default storage) */
extern DW_mpc_test_T mpc_test_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_mpc_test_T mpc_test_U;

/* Model entry point functions */
extern void mpc_test_initialize(void);
extern void mpc_test_step(void);
extern void mpc_test_terminate(void);

/* Real-time Model object */
extern RT_MODEL_mpc_test_T *const mpc_test_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'mpc_test'
 * '<S1>'   : 'mpc_test/Adaptive MPC Controller'
 * '<S2>'   : 'mpc_test/Adaptive MPC Controller/MPC'
 * '<S3>'   : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check'
 * '<S4>'   : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check A'
 * '<S5>'   : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check B'
 * '<S6>'   : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check C'
 * '<S7>'   : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check D'
 * '<S8>'   : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check DX'
 * '<S9>'   : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check U'
 * '<S10>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check X'
 * '<S11>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check Y'
 * '<S12>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check1'
 * '<S13>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Matrix Signal Check2'
 * '<S14>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Preview Signal Check'
 * '<S15>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Preview Signal Check1'
 * '<S16>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Preview Signal Check2'
 * '<S17>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Preview Signal Check3'
 * '<S18>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Preview Signal Check4'
 * '<S19>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Preview Signal Check5'
 * '<S20>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Preview Signal Check6'
 * '<S21>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Preview Signal Check7'
 * '<S22>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Preview Signal Check8'
 * '<S23>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Scalar Signal Check'
 * '<S24>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Scalar Signal Check1'
 * '<S25>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Scalar Signal Check2'
 * '<S26>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Vector Signal Check'
 * '<S27>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Vector Signal Check1'
 * '<S28>'  : 'mpc_test/Adaptive MPC Controller/MPC/MPC Vector Signal Check6'
 * '<S29>'  : 'mpc_test/Adaptive MPC Controller/MPC/moorx'
 * '<S30>'  : 'mpc_test/Adaptive MPC Controller/MPC/optimizer'
 * '<S31>'  : 'mpc_test/Adaptive MPC Controller/MPC/optimizer/FixedHorizonOptimizer'
 */
#endif                                 /* mpc_test_h_ */
