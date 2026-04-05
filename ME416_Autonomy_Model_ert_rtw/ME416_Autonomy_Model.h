/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ME416_Autonomy_Model.h
 *
 * Code generated for Simulink model 'ME416_Autonomy_Model'.
 *
 * Model version                  : 1.50
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Sat Apr  4 16:18:03 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 64-bit (LP64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ME416_Autonomy_Model_h_
#define RTW_HEADER_ME416_Autonomy_Model_h_
#ifndef ME416_Autonomy_Model_COMMON_INCLUDES_
#define ME416_Autonomy_Model_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_mode.h"
#include "LED.h"
#include "MW_pigs.h"
#endif                               /* ME416_Autonomy_Model_COMMON_INCLUDES_ */

#include "ME416_Autonomy_Model_types.h"
#include "math.h"
#include <string.h>
#include <math.h>
#include "rt_matrixlib.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeDELTA
#define rtmGetOdeDELTA(rtm)            ((rtm)->odeDELTA)
#endif

#ifndef rtmSetOdeDELTA
#define rtmSetOdeDELTA(rtm, val)       ((rtm)->odeDELTA = (val))
#endif

#ifndef rtmGetOdeDFDX
#define rtmGetOdeDFDX(rtm)             ((rtm)->odeDFDX)
#endif

#ifndef rtmSetOdeDFDX
#define rtmSetOdeDFDX(rtm, val)        ((rtm)->odeDFDX = (val))
#endif

#ifndef rtmGetOdeE
#define rtmGetOdeE(rtm)                ((rtm)->odeE)
#endif

#ifndef rtmSetOdeE
#define rtmSetOdeE(rtm, val)           ((rtm)->odeE = (val))
#endif

#ifndef rtmGetOdeF0
#define rtmGetOdeF0(rtm)               ((rtm)->odeF0)
#endif

#ifndef rtmSetOdeF0
#define rtmSetOdeF0(rtm, val)          ((rtm)->odeF0 = (val))
#endif

#ifndef rtmGetOdeF1
#define rtmGetOdeF1(rtm)               ((rtm)->odeF1)
#endif

#ifndef rtmSetOdeF1
#define rtmSetOdeF1(rtm, val)          ((rtm)->odeF1 = (val))
#endif

#ifndef rtmGetOdeFAC
#define rtmGetOdeFAC(rtm)              ((rtm)->odeFAC)
#endif

#ifndef rtmSetOdeFAC
#define rtmSetOdeFAC(rtm, val)         ((rtm)->odeFAC = (val))
#endif

#ifndef rtmGetOdePIVOTS
#define rtmGetOdePIVOTS(rtm)           ((rtm)->odePIVOTS)
#endif

#ifndef rtmSetOdePIVOTS
#define rtmSetOdePIVOTS(rtm, val)      ((rtm)->odePIVOTS = (val))
#endif

#ifndef rtmGetOdeW
#define rtmGetOdeW(rtm)                ((rtm)->odeW)
#endif

#ifndef rtmSetOdeW
#define rtmSetOdeW(rtm, val)           ((rtm)->odeW = (val))
#endif

#ifndef rtmGetOdeX0
#define rtmGetOdeX0(rtm)               ((rtm)->odeX0)
#endif

#ifndef rtmSetOdeX0
#define rtmSetOdeX0(rtm, val)          ((rtm)->odeX0 = (val))
#endif

#ifndef rtmGetOdeX1START
#define rtmGetOdeX1START(rtm)          ((rtm)->odeX1START)
#endif

#ifndef rtmSetOdeX1START
#define rtmSetOdeX1START(rtm, val)     ((rtm)->odeX1START = (val))
#endif

#ifndef rtmGetOdeXTMP
#define rtmGetOdeXTMP(rtm)             ((rtm)->odeXTMP)
#endif

#ifndef rtmSetOdeXTMP
#define rtmSetOdeXTMP(rtm, val)        ((rtm)->odeXTMP = (val))
#endif

#ifndef rtmGetOdeZTMP
#define rtmGetOdeZTMP(rtm)             ((rtm)->odeZTMP)
#endif

#ifndef rtmSetOdeZTMP
#define rtmSetOdeZTMP(rtm, val)        ((rtm)->odeZTMP = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
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
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Sat_left_raw;                 /* '<S10>/Sat_left_raw' */
  real_T Sat_left_raw1;                /* '<S10>/Sat_left_raw1' */
  real_T Gain_v_wheels;                /* '<S11>/Gain_v_wheels' */
  real_T w_L;                          /* '<S114>/w_R_integrator' */
  real_T w_L_integrator;               /* '<S113>/w_L_integrator' */
  real_T r_L_wheel_track_Gain;         /* '<S111>/r_L_wheel_track_Gain' */
  real_T w_imu_weight;                 /* '<S11>/w_imu_weight' */
  real_T w_fusion;                     /* '<S11>/w_fusion' */
  real_T round_left_ticks;             /* '<S112>/round_left_ticks' */
  real_T round_right_ticks;            /* '<S112>/round_right_ticks' */
  real_T enc_right_UnitDelay;          /* '<S9>/enc_right_UnitDelay' */
  real_T Gain_rad2rads_right;          /* '<S9>/Gain_rad2rads_right' */
  real_T enc_left_UnitDelay;           /* '<S9>/enc_left_UnitDelay' */
  real_T Gain_rad2rads_left;           /* '<S9>/Gain_rad2rads_left' */
  real_T V_left_batt;                  /* '<S5>/V_left_batt' */
  real_T Arm_L_Inv_Gain;               /* '<S113>/Arm_L_Inv_Gain' */
  real_T Rotor_Inertia_Gain;           /* '<S113>/Rotor_Inertia_Gain' */
  real_T V_right_batt;                 /* '<S5>/V_right_batt' */
  real_T Arm_L_Inv_Gain_m;             /* '<S114>/Arm_L_Inv_Gain' */
  real_T Rotor_Inertia_Gain_b;         /* '<S114>/Rotor_Inertia_Gain' */
  real_T zero_pitch;                   /* '<S111>/zero_pitch' */
  real_T LowPassFilter_right;          /* '<S9>/LowPassFilter_right' */
  real_T LowPassFilter_left;           /* '<S9>/LowPassFilter_left' */
  boolean_T estop;                     /* '<Root>/estop' */
} B_ME416_Autonomy_Model_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  raspi_internal_PWMBlock_ME416_T obj; /* '<Root>/PWM' */
  codertarget_raspi_internal_LE_T obj_g;/* '<Root>/LED' */
  real_T LowPassFilter_left_states;    /* '<S9>/LowPassFilter_left' */
  real_T Integrator_DSTATE;            /* '<S46>/Integrator' */
  real_T Filter_DSTATE;                /* '<S41>/Filter' */
  real_T LowPassFilter_right_states;   /* '<S9>/LowPassFilter_right' */
  real_T Integrator_DSTATE_o;          /* '<S94>/Integrator' */
  real_T Filter_DSTATE_k;              /* '<S89>/Filter' */
  real_T enc_right_UnitDelay_DSTATE;   /* '<S9>/enc_right_UnitDelay' */
  real_T enc_left_UnitDelay_DSTATE;    /* '<S9>/enc_left_UnitDelay' */
  real_T PrevY;                        /* '<S7>/RateLim_v_ref' */
  real_T PrevY_e;                      /* '<S7>/Rate RateLim_w_ref' */
  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    void *LoggedData;
  } imu_pitch_PWORK;                   /* '<Root>/imu_pitch' */

  struct {
    void *LoggedData[8];
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *LoggedData;
  } enc_right_ticks_PWORK;             /* '<Root>/enc_right_ticks' */

  struct {
    void *LoggedData;
  } enc_left_ticks_PWORK;              /* '<Root>/enc_left_ticks' */

  struct {
    void *LoggedData;
  } w_measure_PWORK;                   /* '<Root>/w_measure' */

  struct {
    void *LoggedData;
  } imu_yaw_rate_PWORK;                /* '<Root>/imu_yaw_rate' */

  struct {
    void *LoggedData[2];
  } Scope_PWORK_l;                     /* '<S3>/Scope' */

  struct {
    void *LoggedData;
  } v_measure_PWORK;                   /* '<Root>/v_measure' */

  struct {
    void *LoggedData;
  } u_right_PWORK;                     /* '<Root>/u_right' */

  struct {
    void *LoggedData;
  } u_left_PWORK;                      /* '<Root>/u_left' */
} DW_ME416_Autonomy_Model_T;

/* Continuous states (default storage) */
typedef struct {
  real_T w_R_integrator_CSTATE;        /* '<S114>/w_R_integrator' */
  real_T w_L_integrator_CSTATE;        /* '<S113>/w_L_integrator' */
  real_T left_encoder_integrator_CSTATE;/* '<S112>/left_encoder_integrator' */
  real_T left_encoder_integrator1_CSTATE;/* '<S112>/left_encoder_integrator1' */
  real_T i_L_integrator_CSTATE;        /* '<S113>/i_L_integrator' */
  real_T i_R_integrator_CSTATE;        /* '<S114>/i_R_integrator' */
} X_ME416_Autonomy_Model_T;

/* State derivatives (default storage) */
typedef struct {
  real_T w_R_integrator_CSTATE;        /* '<S114>/w_R_integrator' */
  real_T w_L_integrator_CSTATE;        /* '<S113>/w_L_integrator' */
  real_T left_encoder_integrator_CSTATE;/* '<S112>/left_encoder_integrator' */
  real_T left_encoder_integrator1_CSTATE;/* '<S112>/left_encoder_integrator1' */
  real_T i_L_integrator_CSTATE;        /* '<S113>/i_L_integrator' */
  real_T i_R_integrator_CSTATE;        /* '<S114>/i_R_integrator' */
} XDot_ME416_Autonomy_Model_T;

/* State disabled  */
typedef struct {
  boolean_T w_R_integrator_CSTATE;     /* '<S114>/w_R_integrator' */
  boolean_T w_L_integrator_CSTATE;     /* '<S113>/w_L_integrator' */
  boolean_T left_encoder_integrator_CSTATE;/* '<S112>/left_encoder_integrator' */
  boolean_T left_encoder_integrator1_CSTATE;/* '<S112>/left_encoder_integrator1' */
  boolean_T i_L_integrator_CSTATE;     /* '<S113>/i_L_integrator' */
  boolean_T i_R_integrator_CSTATE;     /* '<S114>/i_R_integrator' */
} XDis_ME416_Autonomy_Model_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Sat_v_ref;              /* '<S7>/Sat_v_ref' */
  const real_T Sat_w_ref;              /* '<S7>/Sat_w_ref' */
  const boolean_T NOT_estop;           /* '<S7>/NOT_estop' */
  const boolean_T drive_enable;        /* '<S7>/AND_enable_safe' */
  const boolean_T NOT_estop_active;    /* '<S10>/NOT_estop_active' */
  const boolean_T safe_enable;         /* '<S10>/AND_drive_enable' */
} ConstB_ME416_Autonomy_Model_T;

#ifndef ODE14X_INTG
#define ODE14X_INTG

/* ODE14X Integration Data */
typedef struct {
  real_T *x0;
  real_T *f0;
  real_T *x1start;
  real_T *f1;
  real_T *Delta;
  real_T *E;
  real_T *fac;
  real_T *DFDX;
  real_T *W;
  int_T *pivots;
  real_T *xtmp;
  real_T *ztmp;
  real_T *M;
  real_T *M1;
  real_T *Edot;
  real_T *xdot;
  real_T *fminusMxdot;
  boolean_T isFirstStep;
} ODE14X_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM_ME416_Autonomy_Model_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  X_ME416_Autonomy_Model_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_ME416_Autonomy_Model_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeX0[6];
  real_T odeF0[6];
  real_T odeX1START[6];
  real_T odeF1[6];
  real_T odeDELTA[6];
  real_T odeE[4*6];
  real_T odeFAC[6];
  real_T odeDFDX[6*6];
  real_T odeW[6*6];
  int_T odePIVOTS[6];
  real_T odeXTMP[6];
  real_T odeZTMP[6];
  ODE14X_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_ME416_Autonomy_Model_T ME416_Autonomy_Model_B;

/* Continuous states (default storage) */
extern X_ME416_Autonomy_Model_T ME416_Autonomy_Model_X;

/* Block states (default storage) */
extern DW_ME416_Autonomy_Model_T ME416_Autonomy_Model_DW;
extern const ConstB_ME416_Autonomy_Model_T ME416_Autonomy_Model_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void ME416_Autonomy_Model_initialize(void);
extern void ME416_Autonomy_Model_step(void);
extern void ME416_Autonomy_Model_terminate(void);

/* Real-time Model object */
extern RT_MODEL_ME416_Autonomy_Model_T *const ME416_Autonomy_Model_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

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
 * '<Root>' : 'ME416_Autonomy_Model'
 * '<S1>'   : 'ME416_Autonomy_Model/ArmControl (Jacobian + PID Joints)'
 * '<S2>'   : 'ME416_Autonomy_Model/ArmKinematics (FK//IK + Jacobian)'
 * '<S3>'   : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)'
 * '<S4>'   : 'ME416_Autonomy_Model/Perception (Pi Camera, Ultrasonic, IMU)'
 * '<S5>'   : 'ME416_Autonomy_Model/Plant'
 * '<S6>'   : 'ME416_Autonomy_Model/Supervisor (FSM)'
 * '<S7>'   : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/CommandSafety'
 * '<S8>'   : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/DifferentialDrive'
 * '<S9>'   : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/EncoderSpeed'
 * '<S10>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/OutputSafety'
 * '<S11>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/StateEstimate'
 * '<S12>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI'
 * '<S13>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left'
 * '<S14>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right'
 * '<S15>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Anti-windup'
 * '<S16>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/D Gain'
 * '<S17>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Filter'
 * '<S18>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Filter ICs'
 * '<S19>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/I Gain'
 * '<S20>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Ideal P Gain'
 * '<S21>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Ideal P Gain Fdbk'
 * '<S22>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Integrator'
 * '<S23>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Integrator ICs'
 * '<S24>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/N Copy'
 * '<S25>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/N Gain'
 * '<S26>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/P Copy'
 * '<S27>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Parallel P Gain'
 * '<S28>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Reset Signal'
 * '<S29>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Saturation'
 * '<S30>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Saturation Fdbk'
 * '<S31>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Sum'
 * '<S32>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Sum Fdbk'
 * '<S33>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Tracking Mode'
 * '<S34>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Tracking Mode Sum'
 * '<S35>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Tsamp - Integral'
 * '<S36>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Tsamp - Ngain'
 * '<S37>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/postSat Signal'
 * '<S38>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/preSat Signal'
 * '<S39>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Anti-windup/Passthrough'
 * '<S40>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/D Gain/Internal Parameters'
 * '<S41>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Filter/Disc. Forward Euler Filter'
 * '<S42>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Filter ICs/Internal IC - Filter'
 * '<S43>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/I Gain/Internal Parameters'
 * '<S44>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Ideal P Gain/Passthrough'
 * '<S45>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Ideal P Gain Fdbk/Disabled'
 * '<S46>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Integrator/Discrete'
 * '<S47>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Integrator ICs/Internal IC'
 * '<S48>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/N Copy/Disabled'
 * '<S49>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/N Gain/Internal Parameters'
 * '<S50>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/P Copy/Disabled'
 * '<S51>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Parallel P Gain/Internal Parameters'
 * '<S52>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Reset Signal/Disabled'
 * '<S53>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Saturation/Passthrough'
 * '<S54>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Saturation Fdbk/Disabled'
 * '<S55>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Sum/Sum_PID'
 * '<S56>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Sum Fdbk/Disabled'
 * '<S57>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Tracking Mode/Disabled'
 * '<S58>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Tracking Mode Sum/Passthrough'
 * '<S59>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Tsamp - Integral/TsSignalSpecification'
 * '<S60>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/Tsamp - Ngain/Passthrough'
 * '<S61>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/postSat Signal/Forward_Path'
 * '<S62>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_left/preSat Signal/Forward_Path'
 * '<S63>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Anti-windup'
 * '<S64>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/D Gain'
 * '<S65>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Filter'
 * '<S66>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Filter ICs'
 * '<S67>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/I Gain'
 * '<S68>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Ideal P Gain'
 * '<S69>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Ideal P Gain Fdbk'
 * '<S70>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Integrator'
 * '<S71>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Integrator ICs'
 * '<S72>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/N Copy'
 * '<S73>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/N Gain'
 * '<S74>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/P Copy'
 * '<S75>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Parallel P Gain'
 * '<S76>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Reset Signal'
 * '<S77>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Saturation'
 * '<S78>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Saturation Fdbk'
 * '<S79>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Sum'
 * '<S80>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Sum Fdbk'
 * '<S81>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Tracking Mode'
 * '<S82>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Tracking Mode Sum'
 * '<S83>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Tsamp - Integral'
 * '<S84>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Tsamp - Ngain'
 * '<S85>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/postSat Signal'
 * '<S86>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/preSat Signal'
 * '<S87>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Anti-windup/Passthrough'
 * '<S88>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/D Gain/Internal Parameters'
 * '<S89>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Filter/Disc. Forward Euler Filter'
 * '<S90>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Filter ICs/Internal IC - Filter'
 * '<S91>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/I Gain/Internal Parameters'
 * '<S92>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Ideal P Gain/Passthrough'
 * '<S93>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Ideal P Gain Fdbk/Disabled'
 * '<S94>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Integrator/Discrete'
 * '<S95>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Integrator ICs/Internal IC'
 * '<S96>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/N Copy/Disabled'
 * '<S97>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/N Gain/Internal Parameters'
 * '<S98>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/P Copy/Disabled'
 * '<S99>'  : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Parallel P Gain/Internal Parameters'
 * '<S100>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Reset Signal/Disabled'
 * '<S101>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Saturation/Passthrough'
 * '<S102>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Saturation Fdbk/Disabled'
 * '<S103>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Sum/Sum_PID'
 * '<S104>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Sum Fdbk/Disabled'
 * '<S105>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Tracking Mode/Disabled'
 * '<S106>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Tracking Mode Sum/Passthrough'
 * '<S107>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Tsamp - Integral/TsSignalSpecification'
 * '<S108>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/Tsamp - Ngain/Passthrough'
 * '<S109>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/postSat Signal/Forward_Path'
 * '<S110>' : 'ME416_Autonomy_Model/DriveControl (PID, IMU, Encoder, DC Motors)/WheelPI/PI_right/preSat Signal/Forward_Path'
 * '<S111>' : 'ME416_Autonomy_Model/Plant/DifferentialDriveModel'
 * '<S112>' : 'ME416_Autonomy_Model/Plant/EncoderModel'
 * '<S113>' : 'ME416_Autonomy_Model/Plant/MotorDynamics_Left'
 * '<S114>' : 'ME416_Autonomy_Model/Plant/MotorDynamics_Right'
 */
#endif                                 /* RTW_HEADER_ME416_Autonomy_Model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
