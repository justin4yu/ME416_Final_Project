/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ME416_Autonomy_Model.c
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

#include "ME416_Autonomy_Model.h"
#include "rtwtypes.h"
#include "ME416_Autonomy_Model_private.h"
#include <math.h>
#define ME416_Autonomy_Model_period    (0.01)

/* Block signals (default storage) */
B_ME416_Autonomy_Model_T ME416_Autonomy_Model_B;

/* Continuous states */
X_ME416_Autonomy_Model_T ME416_Autonomy_Model_X;

/* Block states (default storage) */
DW_ME416_Autonomy_Model_T ME416_Autonomy_Model_DW;

/* Real-time model */
static RT_MODEL_ME416_Autonomy_Model_T ME416_Autonomy_Model_M_;
RT_MODEL_ME416_Autonomy_Model_T *const ME416_Autonomy_Model_M =
  &ME416_Autonomy_Model_M_;

/* Simplified version of numjac.cpp, for use with RTW. */
void local_numjac( RTWSolverInfo *si, real_T *y, const real_T *Fty, real_T *fac,
                  real_T *dFdy )
{
  /* constants */
  real_T THRESH = 1e-6;
  real_T EPS = 2.2e-16;                /* utGetEps(); */
  real_T BL = pow(EPS, 0.75);
  real_T BU = pow(EPS, 0.25);
  real_T FACMIN = pow(EPS, 0.78);
  real_T FACMAX = 0.1;
  int_T nx = 6;
  real_T *x = rtsiGetContStates(si);
  real_T del;
  real_T difmax;
  real_T FdelRowmax;
  real_T temp;
  real_T Fdiff;
  real_T maybe;
  real_T xscale;
  real_T fscale;
  real_T *p;
  int_T rowmax;
  int_T i,j;
  if (x != y)
    (void) memcpy(x, y,
                  (uint_T)nx*sizeof(real_T));
  rtsiSetSolverComputingJacobian(si,true);
  for (p = dFdy, j = 0; j < nx; j++, p += nx) {
    /* Select an increment del for a difference approximation to
       column j of dFdy.  The vector fac accounts for experience
       gained in previous calls to numjac. */
    xscale = fabs(x[j]);
    if (xscale < THRESH)
      xscale = THRESH;
    temp = (x[j] + fac[j]*xscale);
    del = temp - y[j];
    while (del == 0.0) {
      if (fac[j] < FACMAX) {
        fac[j] *= 100.0;
        if (fac[j] > FACMAX)
          fac[j] = FACMAX;
        temp = (x[j] + fac[j]*xscale);
        del = temp - x[j];
      } else {
        del = THRESH;                  /* thresh is nonzero */
        break;
      }
    }

    /* Keep del pointing into region. */
    if (Fty[j] >= 0.0)
      del = fabs(del);
    else
      del = -fabs(del);

    /* Form a difference approximation to column j of dFdy. */
    temp = x[j];
    x[j] += del;
    ME416_Autonomy_Model_step();
    rtsiSetdX(si,p);
    ME416_Autonomy_Model_derivatives();
    x[j] = temp;
    difmax = 0.0;
    rowmax = 0;
    FdelRowmax = p[0];
    temp = 1.0 / del;
    for (i = 0; i < nx; i++) {
      Fdiff = p[i] - Fty[i];
      maybe = fabs(Fdiff);
      if (maybe > difmax) {
        difmax = maybe;
        rowmax = i;
        FdelRowmax = p[i];
      }

      p[i] = temp * Fdiff;
    }

    /* Adjust fac for next call to numjac. */
    if (((FdelRowmax != 0.0) && (Fty[rowmax] != 0.0)) || (difmax == 0.0)) {
      fscale = fabs(FdelRowmax);
      if (fscale < fabs(Fty[rowmax]))
        fscale = fabs(Fty[rowmax]);
      if (difmax <= BL*fscale) {
        /* The difference is small, so increase the increment. */
        fac[j] *= 10.0;
        if (fac[j] > FACMAX)
          fac[j] = FACMAX;
      } else if (difmax > BU*fscale) {
        /* The difference is large, so reduce the increment. */
        fac[j] *= 0.1;
        if (fac[j] < FACMIN)
          fac[j] = FACMIN;
      }
    }
  }

  rtsiSetSolverComputingJacobian(si,false);
}                                      /* end local_numjac */

/*
 * This function updates continuous states using the ODE14X fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static int_T rt_ODE14x_N[4] = { 12, 8, 6, 4 };

  time_T t0 = rtsiGetT(si);
  time_T t1 = t0;
  time_T h = rtsiGetStepSize(si);
  real_T *x1 = rtsiGetContStates(si);
  int_T order = rtsiGetSolverExtrapolationOrder(si);
  int_T numIter = rtsiGetSolverNumberNewtonIterations(si);
  ODE14X_IntgData *id = (ODE14X_IntgData *)rtsiGetSolverData(si);
  real_T *x0 = id->x0;
  real_T *f0 = id->f0;
  real_T *x1start = id->x1start;
  real_T *f1 = id->f1;
  real_T *Delta = id->Delta;
  real_T *E = id->E;
  real_T *fac = id->fac;
  real_T *dfdx = id->DFDX;
  real_T *W = id->W;
  int_T *pivots = id->pivots;
  real_T *xtmp = id->xtmp;
  real_T *ztmp = id->ztmp;
  int_T *N = &(rt_ODE14x_N[0]);
  int_T i,j,k,iter;
  int_T nx = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(x0, x1,
                (uint_T)nx*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */

  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  ME416_Autonomy_Model_derivatives();
  local_numjac(si,x0,f0,fac,dfdx );
  for (j = 0; j < order; j++) {
    real_T *p;
    real_T hN = h/N[j];

    /* Get the iteration matrix and solution at t0 */

    /* [L,U] = lu(M - hN*J) */
    (void) memcpy(W, dfdx,
                  (uint_T)nx*nx*sizeof(real_T));
    for (p = W, i = 0; i < nx*nx; i++, p++) {
      *p *= (-hN);
    }

    for (p = W, i = 0; i < nx; i++, p += (nx+1)) {
      *p += 1.0;
    }

    rt_lu_real(W, nx,
               pivots);

    /* First Newton's iteration at t0. */
    /* rhs = hN*f0 */
    for (i = 0; i < nx; i++) {
      Delta[i] = hN*f0[i];
    }

    /* Delta = (U \ (L \ rhs)) */
    rt_ForwardSubstitutionRR_Dbl(W, Delta,
      f1, nx,
      1, pivots,
      1);
    rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
      Delta, nx,
      1, 0);

    /* ytmp = y0 + Delta
       ztmp = (ytmp-y0)/h
     */
    (void) memcpy(x1, x0,
                  (uint_T)nx*sizeof(real_T));
    for (i = 0; i < nx; i++) {
      x1[i] += Delta[i];
      ztmp[i] = Delta[i]/hN;
    }

    /* Additional Newton's iterations, if desired.
       for iter = 2:NewtIter
       rhs = hN*feval(odefun,tn,ytmp,extraArgs{:}) - M*(ytmp - yn);
       if statedepM   % only for state dep. Mdel ~= 0
       Mdel = M - feval(massfun,tn,ytmp);
       rhs = rhs + Mdel*ztmp*h;
       end
       Delta = ( U \ ( L \ rhs ) );
       ytmp = ytmp + Delta;
       ztmp = (ytmp - yn)/h
       end
     */
    rtsiSetT(si, t0);
    rtsiSetdX(si, f1);
    for (iter = 1; iter < numIter; iter++) {
      ME416_Autonomy_Model_step();
      ME416_Autonomy_Model_derivatives();
      for (i = 0; i < nx; i++) {
        Delta[i] = hN*f1[i];
        xtmp[i] = x1[i] - x0[i];
      }

      /* rhs = hN*f(tn,ytmp) - (ytmp-yn) */
      for (i = 0; i < nx; i++) {
        Delta[i] -= xtmp[i];
      }

      rt_ForwardSubstitutionRR_Dbl(W, Delta,
        f1, nx,
        1, pivots,
        1);
      rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
        Delta, nx,
        1, 0);

      /* ytmp = ytmp + delta
         ztmp = (ytmp - yn)/h
       */
      for (i = 0; i < nx; i++) {
        x1[i] += Delta[i];
        ztmp[i] = (x1[i] - x0[i])/hN;
      }
    }

    /* Steps from t0+hN to t1 -- subintegration of N(j) steps for extrapolation
       ttmp = t0;
       for i = 2:N(j)
       ttmp = ttmp + hN
       ytmp0 = ytmp;
       for iter = 1:NewtIter
       rhs = (ytmp0 - ytmp) + hN*feval(odefun,ttmp,ytmp,extraArgs{:});
       Delta = ( U \ ( L \ rhs ) );
       ytmp = ytmp + Delta;
       end
       end
     */
    for (k = 1; k < N[j]; k++) {
      t1 = t0 + k*hN;
      (void) memcpy(x1start, x1,
                    (uint_T)nx*sizeof(real_T));
      rtsiSetT(si, t1);
      rtsiSetdX(si, f1);
      for (iter = 0; iter < numIter; iter++) {
        ME416_Autonomy_Model_step();
        ME416_Autonomy_Model_derivatives();
        if (iter == 0) {
          for (i = 0; i < nx; i++) {
            Delta[i] = hN*f1[i];
          }
        } else {
          for (i = 0; i < nx; i++) {
            Delta[i] = hN*f1[i];
            xtmp[i] = (x1[i]-x1start[i]);
          }

          /* rhs = hN*f(tn,ytmp) - M*(ytmp-yn) */
          for (i = 0; i < nx; i++) {
            Delta[i] -= xtmp[i];
          }
        }

        rt_ForwardSubstitutionRR_Dbl(W, Delta,
          f1, nx,
          1, pivots,
          1);
        rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
          Delta, nx,
          1, 0);

        /* ytmp = ytmp + Delta
           ztmp = (ytmp - ytmp0)/h
         */
        for (i = 0; i < nx; i++) {
          x1[i] += Delta[i];
          ztmp[i] = (x1[i] - x1start[i])/hN;
        }
      }
    }

    /* Extrapolate to order j
       E(:,j) = ytmp
       for k = j:-1:2
       coef = N(k-1)/(N(j) - N(k-1))
       E(:,k-1) = E(:,k) + coef*( E(:,k) - E(:,k-1) )
       end
     */
    (void) memcpy(&(E[nx*j]), x1,
                  (uint_T)nx*sizeof(real_T));
    for (k = j; k > 0; k--) {
      real_T coef = (real_T)(N[k-1]) / (N[j]-N[k-1]);
      for (i = 0; i < nx; i++) {
        x1[i] = E[nx*k+i] + coef*(E[nx*k+i] - E[nx*(k-1)+i]);
      }

      (void) memcpy(&(E[nx*(k-1)]), x1,
                    (uint_T)nx*sizeof(real_T));
    }
  }

  /* x1 = E(:,1); */
  (void) memcpy(x1, E,
                (uint_T)nx*sizeof(real_T));

  /* t1 = t0 + h; */
  rtsiSetT(si,rtsiGetSolverStopTime(si));
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void ME416_Autonomy_Model_step(void)
{
  /* local block i/o variables */
  real_T rtb_FilterCoefficient;
  real_T rtb_FilterCoefficient_k;
  real_T rtb_IntegralGain;
  real_T rtb_IntegralGain_i;
  real_T rtb_Filter_i;
  real_T rtb_left_error;
  int32_T i;
  char_T b[5];
  static const char_T tmp[5] = "none";
  if (rtmIsMajorTimeStep(ME416_Autonomy_Model_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&ME416_Autonomy_Model_M->solverInfo,
                          ((ME416_Autonomy_Model_M->Timing.clockTick0+1)*
      ME416_Autonomy_Model_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(ME416_Autonomy_Model_M)) {
    ME416_Autonomy_Model_M->Timing.t[0] = rtsiGetT
      (&ME416_Autonomy_Model_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(ME416_Autonomy_Model_M)) {
    /* MATLABSystem: '<Root>/LED' */
    for (i = 0; i < 5; i++) {
      b[i] = tmp[i];
    }

    EXT_LED_setTrigger(0U, &b[0]);
    EXT_LED_write(0U, (uint8_T)ME416_Autonomy_Model_B.estop);

    /* End of MATLABSystem: '<Root>/LED' */

    /* RateLimiter: '<S7>/RateLim_v_ref' */
    rtb_left_error = ME416_Autonomy_Model_ConstB.Sat_v_ref -
      ME416_Autonomy_Model_DW.PrevY;
    if (rtb_left_error > ME416_Autonomy_Model_period) {
      /* Switch: '<S10>/Switch_left_raw1' */
      ME416_Autonomy_Model_B.Sat_left_raw1 = ME416_Autonomy_Model_DW.PrevY +
        ME416_Autonomy_Model_period;
    } else if (rtb_left_error < -0.01) {
      /* Switch: '<S10>/Switch_left_raw1' */
      ME416_Autonomy_Model_B.Sat_left_raw1 = ME416_Autonomy_Model_DW.PrevY -
        0.01;
    } else {
      /* Switch: '<S10>/Switch_left_raw1' */
      ME416_Autonomy_Model_B.Sat_left_raw1 =
        ME416_Autonomy_Model_ConstB.Sat_v_ref;
    }

    ME416_Autonomy_Model_DW.PrevY = ME416_Autonomy_Model_B.Sat_left_raw1;

    /* End of RateLimiter: '<S7>/RateLim_v_ref' */

    /* Switch: '<S7>/Switch_v_cmd' */
    if (!ME416_Autonomy_Model_ConstB.drive_enable) {
      /* Switch: '<S10>/Switch_left_raw1' incorporates:
       *  Constant: '<S7>/Const_zero'
       */
      ME416_Autonomy_Model_B.Sat_left_raw1 = 0.0;
    }

    /* End of Switch: '<S7>/Switch_v_cmd' */

    /* RateLimiter: '<S7>/Rate RateLim_w_ref' */
    rtb_left_error = ME416_Autonomy_Model_ConstB.Sat_w_ref -
      ME416_Autonomy_Model_DW.PrevY_e;
    if (rtb_left_error > ME416_Autonomy_Model_period) {
      rtb_Filter_i = ME416_Autonomy_Model_DW.PrevY_e +
        ME416_Autonomy_Model_period;
    } else if (rtb_left_error < -0.01) {
      rtb_Filter_i = ME416_Autonomy_Model_DW.PrevY_e - 0.01;
    } else {
      rtb_Filter_i = ME416_Autonomy_Model_ConstB.Sat_w_ref;
    }

    ME416_Autonomy_Model_DW.PrevY_e = rtb_Filter_i;

    /* End of RateLimiter: '<S7>/Rate RateLim_w_ref' */

    /* Switch: '<S7>/Switch_w_cmd' incorporates:
     *  Constant: '<S7>/Const_zero'
     */
    if (!ME416_Autonomy_Model_ConstB.drive_enable) {
      rtb_Filter_i = 0.0;
    }

    /* Product: '<S8>/Product' incorporates:
     *  Constant: '<S8>/w_term'
     *  Switch: '<S7>/Switch_w_cmd'
     */
    rtb_Filter_i *= 0.075;

    /* DiscreteTransferFcn: '<S9>/LowPassFilter_left' */
    ME416_Autonomy_Model_B.LowPassFilter_left = 0.16666666666666666 *
      ME416_Autonomy_Model_DW.LowPassFilter_left_states;

    /* Sum: '<S12>/Sum_left_error' incorporates:
     *  DiscreteTransferFcn: '<S9>/LowPassFilter_left'
     *  Gain: '<S8>/Gain_inv_r_left'
     *  Sum: '<S8>/Sum_v_left'
     */
    rtb_left_error = (ME416_Autonomy_Model_B.Sat_left_raw1 - rtb_Filter_i) *
      33.333333333333336 - ME416_Autonomy_Model_B.LowPassFilter_left;

    /* Gain: '<S49>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S41>/Filter'
     *  Gain: '<S40>/Derivative Gain'
     *  Sum: '<S41>/SumD'
     */
    rtb_FilterCoefficient = (0.0 * rtb_left_error -
      ME416_Autonomy_Model_DW.Filter_DSTATE) * 100.0;

    /* Switch: '<S10>/Switch_left_raw' incorporates:
     *  Constant: '<S10>/Const_zero'
     *  DiscreteIntegrator: '<S46>/Integrator'
     *  Gain: '<S51>/Proportional Gain'
     *  Sum: '<S55>/Sum'
     */
    if (ME416_Autonomy_Model_ConstB.safe_enable) {
      ME416_Autonomy_Model_B.LowPassFilter_right = (0.8 * rtb_left_error +
        ME416_Autonomy_Model_DW.Integrator_DSTATE) + rtb_FilterCoefficient;
    } else {
      ME416_Autonomy_Model_B.LowPassFilter_right = 0.0;
    }

    /* End of Switch: '<S10>/Switch_left_raw' */

    /* Saturate: '<S10>/Sat_left_raw' */
    if (ME416_Autonomy_Model_B.LowPassFilter_right > 1.0) {
      /* Saturate: '<S10>/Sat_left_raw' */
      ME416_Autonomy_Model_B.Sat_left_raw = 1.0;
    } else if (ME416_Autonomy_Model_B.LowPassFilter_right < -1.0) {
      /* Saturate: '<S10>/Sat_left_raw' */
      ME416_Autonomy_Model_B.Sat_left_raw = -1.0;
    } else {
      /* Saturate: '<S10>/Sat_left_raw' */
      ME416_Autonomy_Model_B.Sat_left_raw =
        ME416_Autonomy_Model_B.LowPassFilter_right;
    }

    /* End of Saturate: '<S10>/Sat_left_raw' */

    /* DiscreteTransferFcn: '<S9>/LowPassFilter_right' */
    ME416_Autonomy_Model_B.LowPassFilter_right = 0.16666666666666666 *
      ME416_Autonomy_Model_DW.LowPassFilter_right_states;

    /* Sum: '<S12>/Sum_right_error' incorporates:
     *  DiscreteTransferFcn: '<S9>/LowPassFilter_right'
     *  Gain: '<S8>/gain_inv_r_right'
     *  Sum: '<S8>/Sum_v_right'
     */
    rtb_Filter_i = (ME416_Autonomy_Model_B.Sat_left_raw1 + rtb_Filter_i) *
      33.333333333333336 - ME416_Autonomy_Model_B.LowPassFilter_right;

    /* Gain: '<S97>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S89>/Filter'
     *  Gain: '<S88>/Derivative Gain'
     *  Sum: '<S89>/SumD'
     */
    rtb_FilterCoefficient_k = (0.0 * rtb_Filter_i -
      ME416_Autonomy_Model_DW.Filter_DSTATE_k) * 100.0;

    /* Switch: '<S10>/Switch_left_raw1' */
    if (ME416_Autonomy_Model_ConstB.safe_enable) {
      /* Switch: '<S10>/Switch_left_raw1' incorporates:
       *  DiscreteIntegrator: '<S94>/Integrator'
       *  Gain: '<S99>/Proportional Gain'
       *  Sum: '<S103>/Sum'
       */
      ME416_Autonomy_Model_B.Sat_left_raw1 = (0.8 * rtb_Filter_i +
        ME416_Autonomy_Model_DW.Integrator_DSTATE_o) + rtb_FilterCoefficient_k;
    } else {
      /* Switch: '<S10>/Switch_left_raw1' incorporates:
       *  Constant: '<S10>/Const_zero1'
       */
      ME416_Autonomy_Model_B.Sat_left_raw1 = 0.0;
    }

    /* End of Switch: '<S10>/Switch_left_raw1' */

    /* Saturate: '<S10>/Sat_left_raw1' */
    if (ME416_Autonomy_Model_B.Sat_left_raw1 > 1.0) {
      /* Switch: '<S10>/Switch_left_raw1' incorporates:
       *  Saturate: '<S10>/Sat_left_raw1'
       */
      ME416_Autonomy_Model_B.Sat_left_raw1 = 1.0;
    } else if (ME416_Autonomy_Model_B.Sat_left_raw1 < -1.0) {
      /* Switch: '<S10>/Switch_left_raw1' incorporates:
       *  Saturate: '<S10>/Sat_left_raw1'
       */
      ME416_Autonomy_Model_B.Sat_left_raw1 = -1.0;
    }

    /* End of Saturate: '<S10>/Sat_left_raw1' */

    /* Gain: '<S11>/Gain_v_wheels' incorporates:
     *  DiscreteTransferFcn: '<S9>/LowPassFilter_left'
     *  Sum: '<S11>/Sum_omega_lr'
     */
    ME416_Autonomy_Model_B.Gain_v_wheels =
      (ME416_Autonomy_Model_B.LowPassFilter_left +
       ME416_Autonomy_Model_B.LowPassFilter_left) * 0.015;

    /* Gain: '<S11>/w_imu_weight' incorporates:
     *  Gain: '<S11>/Gain_w_wheels'
     *  Sum: '<S11>/Diff_omega_lr'
     */
    ME416_Autonomy_Model_B.w_imu_weight =
      (ME416_Autonomy_Model_B.LowPassFilter_right -
       ME416_Autonomy_Model_B.LowPassFilter_left) * 0.2 * 0.30000000000000004;
  }

  /* Integrator: '<S114>/w_R_integrator' */
  ME416_Autonomy_Model_B.w_L = ME416_Autonomy_Model_X.w_R_integrator_CSTATE;

  /* Integrator: '<S113>/w_L_integrator' */
  ME416_Autonomy_Model_B.w_L_integrator =
    ME416_Autonomy_Model_X.w_L_integrator_CSTATE;

  /* Gain: '<S111>/r_L_wheel_track_Gain' incorporates:
   *  Sum: '<S111>/Sum'
   */
  ME416_Autonomy_Model_B.r_L_wheel_track_Gain = (ME416_Autonomy_Model_B.w_L -
    ME416_Autonomy_Model_B.w_L_integrator) * 0.2;

  /* Sum: '<S11>/w_fusion' incorporates:
   *  Gain: '<S11>/w_enc_weight'
   */
  ME416_Autonomy_Model_B.w_fusion = 0.7 *
    ME416_Autonomy_Model_B.r_L_wheel_track_Gain +
    ME416_Autonomy_Model_B.w_imu_weight;

  /* Rounding: '<S112>/round_left_ticks' incorporates:
   *  Gain: '<S112>/gain_counts_per_rad_left'
   *  Integrator: '<S112>/left_encoder_integrator'
   */
  ME416_Autonomy_Model_B.round_left_ticks = rt_roundd_snf(700.28174960433955 *
    ME416_Autonomy_Model_X.left_encoder_integrator_CSTATE);

  /* Rounding: '<S112>/round_right_ticks' incorporates:
   *  Gain: '<S112>/gain_counts_per_rad_right'
   *  Integrator: '<S112>/left_encoder_integrator1'
   */
  ME416_Autonomy_Model_B.round_right_ticks = rt_roundd_snf(700.28174960433955 *
    ME416_Autonomy_Model_X.left_encoder_integrator1_CSTATE);
  if (rtmIsMajorTimeStep(ME416_Autonomy_Model_M)) {
    /* UnitDelay: '<S9>/enc_right_UnitDelay' */
    ME416_Autonomy_Model_B.enc_right_UnitDelay =
      ME416_Autonomy_Model_DW.enc_right_UnitDelay_DSTATE;
  }

  /* Gain: '<S9>/Gain_rad2rads_right' incorporates:
   *  Gain: '<S9>/Gain_ticks2rad_right'
   *  Sum: '<S9>/DeltaTicks_right'
   */
  ME416_Autonomy_Model_B.Gain_rad2rads_right =
    (ME416_Autonomy_Model_B.round_right_ticks -
     ME416_Autonomy_Model_B.enc_right_UnitDelay) * 0.0014279966607226332 * 100.0;
  if (rtmIsMajorTimeStep(ME416_Autonomy_Model_M)) {
    /* UnitDelay: '<S9>/enc_left_UnitDelay' */
    ME416_Autonomy_Model_B.enc_left_UnitDelay =
      ME416_Autonomy_Model_DW.enc_left_UnitDelay_DSTATE;
  }

  /* Gain: '<S9>/Gain_rad2rads_left' incorporates:
   *  Gain: '<S9>/Gain_ticks2rad_left'
   *  Sum: '<S9>/DeltaTicks_left'
   */
  ME416_Autonomy_Model_B.Gain_rad2rads_left =
    (ME416_Autonomy_Model_B.round_left_ticks -
     ME416_Autonomy_Model_B.enc_left_UnitDelay) * 0.0014279966607226332 * 100.0;
  if (rtmIsMajorTimeStep(ME416_Autonomy_Model_M)) {
    /* Product: '<S5>/V_left_batt' incorporates:
     *  Constant: '<S5>/Vbatt'
     */
    ME416_Autonomy_Model_B.V_left_batt = ME416_Autonomy_Model_B.Sat_left_raw *
      12.0;

    /* Product: '<S5>/V_right_batt' incorporates:
     *  Constant: '<S5>/Vbatt'
     */
    ME416_Autonomy_Model_B.V_right_batt = 12.0 *
      ME416_Autonomy_Model_B.Sat_left_raw1;
  }

  /* Gain: '<S113>/Arm_L_Inv_Gain' incorporates:
   *  Gain: '<S113>/Arm_R_Gain'
   *  Gain: '<S113>/Back_EMF_Gain'
   *  Integrator: '<S113>/i_L_integrator'
   *  Sum: '<S113>/Add'
   */
  ME416_Autonomy_Model_B.Arm_L_Inv_Gain = ((ME416_Autonomy_Model_B.V_left_batt -
    8.0 * ME416_Autonomy_Model_X.i_L_integrator_CSTATE) - 0.03 *
    ME416_Autonomy_Model_B.w_L_integrator) * 1000.0;

  /* Gain: '<S113>/Rotor_Inertia_Gain' incorporates:
   *  Gain: '<S113>/Torque_Const'
   *  Gain: '<S113>/Visc_Damping_Coeff'
   *  Integrator: '<S113>/i_L_integrator'
   *  Sum: '<S113>/Sum'
   */
  ME416_Autonomy_Model_B.Rotor_Inertia_Gain = (0.03 *
    ME416_Autonomy_Model_X.i_L_integrator_CSTATE - 0.0002 *
    ME416_Autonomy_Model_B.w_L_integrator) * 49999.999999999993;

  /* Gain: '<S114>/Arm_L_Inv_Gain' incorporates:
   *  Gain: '<S114>/Arm_R_Gain'
   *  Gain: '<S114>/Back_EMF_Gain'
   *  Integrator: '<S114>/i_R_integrator'
   *  Sum: '<S114>/Add'
   */
  ME416_Autonomy_Model_B.Arm_L_Inv_Gain_m =
    ((ME416_Autonomy_Model_B.V_right_batt - 8.0 *
      ME416_Autonomy_Model_X.i_R_integrator_CSTATE) - 0.03 *
     ME416_Autonomy_Model_B.w_L) * 1000.0;

  /* Gain: '<S114>/Rotor_Inertia_Gain' incorporates:
   *  Gain: '<S114>/Torque_Const'
   *  Gain: '<S114>/Visc_Damping_Coeff'
   *  Integrator: '<S114>/i_R_integrator'
   *  Sum: '<S114>/Sum'
   */
  ME416_Autonomy_Model_B.Rotor_Inertia_Gain_b = (0.03 *
    ME416_Autonomy_Model_X.i_R_integrator_CSTATE - 0.0002 *
    ME416_Autonomy_Model_B.w_L) * 49999.999999999993;
  if (rtmIsMajorTimeStep(ME416_Autonomy_Model_M)) {
    /* Gain: '<S91>/Integral Gain' */
    rtb_IntegralGain = 4.0 * rtb_Filter_i;

    /* Gain: '<S43>/Integral Gain' */
    rtb_IntegralGain_i = 4.0 * rtb_left_error;

    /* MATLABSystem: '<Root>/PWM' */
    EXT_PWMBlock_setDutyCycle(ME416_Autonomy_Model_DW.obj.PinNumber, 0.0);
  }

  if (rtmIsMajorTimeStep(ME416_Autonomy_Model_M)) {
    if (rtmIsMajorTimeStep(ME416_Autonomy_Model_M)) {
      /* Update for DiscreteTransferFcn: '<S9>/LowPassFilter_left' */
      ME416_Autonomy_Model_DW.LowPassFilter_left_states =
        ME416_Autonomy_Model_B.Gain_rad2rads_left - -0.83333333333333337 *
        ME416_Autonomy_Model_DW.LowPassFilter_left_states;

      /* Update for DiscreteIntegrator: '<S46>/Integrator' */
      ME416_Autonomy_Model_DW.Integrator_DSTATE += 0.01 * rtb_IntegralGain_i;

      /* Update for DiscreteIntegrator: '<S41>/Filter' */
      ME416_Autonomy_Model_DW.Filter_DSTATE += 0.01 * rtb_FilterCoefficient;

      /* Update for DiscreteTransferFcn: '<S9>/LowPassFilter_right' */
      ME416_Autonomy_Model_DW.LowPassFilter_right_states =
        ME416_Autonomy_Model_B.Gain_rad2rads_right - -0.83333333333333337 *
        ME416_Autonomy_Model_DW.LowPassFilter_right_states;

      /* Update for DiscreteIntegrator: '<S94>/Integrator' */
      ME416_Autonomy_Model_DW.Integrator_DSTATE_o += 0.01 * rtb_IntegralGain;

      /* Update for DiscreteIntegrator: '<S89>/Filter' */
      ME416_Autonomy_Model_DW.Filter_DSTATE_k += 0.01 * rtb_FilterCoefficient_k;

      /* Update for UnitDelay: '<S9>/enc_right_UnitDelay' */
      ME416_Autonomy_Model_DW.enc_right_UnitDelay_DSTATE =
        ME416_Autonomy_Model_B.round_right_ticks;

      /* Update for UnitDelay: '<S9>/enc_left_UnitDelay' */
      ME416_Autonomy_Model_DW.enc_left_UnitDelay_DSTATE =
        ME416_Autonomy_Model_B.round_left_ticks;
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
      extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
        ME416_Autonomy_Model_M->Timing.t[0];

      /* Trigger External Mode event */
      errorCode = extmodeEvent(0,currentTime);
      if (errorCode != EXTMODE_SUCCESS) {
        /* Code to handle External Mode event errors
           may be added here */
      }
    }

    if (rtmIsMajorTimeStep(ME416_Autonomy_Model_M)) {/* Sample time: [0.01s, 0.0s] */
      extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
      extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
        ((ME416_Autonomy_Model_M->Timing.clockTick1) * 0.01);

      /* Trigger External Mode event */
      errorCode = extmodeEvent(1,currentTime);
      if (errorCode != EXTMODE_SUCCESS) {
        /* Code to handle External Mode event errors
           may be added here */
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(ME416_Autonomy_Model_M)) {
    rt_ertODEUpdateContinuousStates(&ME416_Autonomy_Model_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++ME416_Autonomy_Model_M->Timing.clockTick0;
    ME416_Autonomy_Model_M->Timing.t[0] = rtsiGetSolverStopTime
      (&ME416_Autonomy_Model_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      ME416_Autonomy_Model_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void ME416_Autonomy_Model_derivatives(void)
{
  XDot_ME416_Autonomy_Model_T *_rtXdot;
  _rtXdot = ((XDot_ME416_Autonomy_Model_T *) ME416_Autonomy_Model_M->derivs);

  /* Derivatives for Integrator: '<S114>/w_R_integrator' */
  _rtXdot->w_R_integrator_CSTATE = ME416_Autonomy_Model_B.Rotor_Inertia_Gain_b;

  /* Derivatives for Integrator: '<S113>/w_L_integrator' */
  _rtXdot->w_L_integrator_CSTATE = ME416_Autonomy_Model_B.Rotor_Inertia_Gain;

  /* Derivatives for Integrator: '<S112>/left_encoder_integrator' */
  _rtXdot->left_encoder_integrator_CSTATE =
    ME416_Autonomy_Model_B.w_L_integrator;

  /* Derivatives for Integrator: '<S112>/left_encoder_integrator1' */
  _rtXdot->left_encoder_integrator1_CSTATE = ME416_Autonomy_Model_B.w_L;

  /* Derivatives for Integrator: '<S113>/i_L_integrator' */
  _rtXdot->i_L_integrator_CSTATE = ME416_Autonomy_Model_B.Arm_L_Inv_Gain;

  /* Derivatives for Integrator: '<S114>/i_R_integrator' */
  _rtXdot->i_R_integrator_CSTATE = ME416_Autonomy_Model_B.Arm_L_Inv_Gain_m;
}

/* Model initialize function */
void ME416_Autonomy_Model_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&ME416_Autonomy_Model_M->solverInfo,
                          &ME416_Autonomy_Model_M->Timing.simTimeStep);
    rtsiSetTPtr(&ME416_Autonomy_Model_M->solverInfo, &rtmGetTPtr
                (ME416_Autonomy_Model_M));
    rtsiSetStepSizePtr(&ME416_Autonomy_Model_M->solverInfo,
                       &ME416_Autonomy_Model_M->Timing.stepSize0);
    rtsiSetdXPtr(&ME416_Autonomy_Model_M->solverInfo,
                 &ME416_Autonomy_Model_M->derivs);
    rtsiSetContStatesPtr(&ME416_Autonomy_Model_M->solverInfo, (real_T **)
                         &ME416_Autonomy_Model_M->contStates);
    rtsiSetNumContStatesPtr(&ME416_Autonomy_Model_M->solverInfo,
      &ME416_Autonomy_Model_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&ME416_Autonomy_Model_M->solverInfo,
      &ME416_Autonomy_Model_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&ME416_Autonomy_Model_M->solverInfo,
      &ME416_Autonomy_Model_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&ME416_Autonomy_Model_M->solverInfo,
      &ME416_Autonomy_Model_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&ME416_Autonomy_Model_M->solverInfo,
                          (&rtmGetErrorStatus(ME416_Autonomy_Model_M)));
    rtsiSetRTModelPtr(&ME416_Autonomy_Model_M->solverInfo,
                      ME416_Autonomy_Model_M);
  }

  rtsiSetSimTimeStep(&ME416_Autonomy_Model_M->solverInfo, MAJOR_TIME_STEP);
  ME416_Autonomy_Model_M->intgData.x0 = ME416_Autonomy_Model_M->odeX0;
  ME416_Autonomy_Model_M->intgData.f0 = ME416_Autonomy_Model_M->odeF0;
  ME416_Autonomy_Model_M->intgData.x1start = ME416_Autonomy_Model_M->odeX1START;
  ME416_Autonomy_Model_M->intgData.f1 = ME416_Autonomy_Model_M->odeF1;
  ME416_Autonomy_Model_M->intgData.Delta = ME416_Autonomy_Model_M->odeDELTA;
  ME416_Autonomy_Model_M->intgData.E = ME416_Autonomy_Model_M->odeE;
  ME416_Autonomy_Model_M->intgData.fac = ME416_Autonomy_Model_M->odeFAC;

  /* initialize */
  {
    int_T i;
    real_T *f = ME416_Autonomy_Model_M->intgData.fac;
    for (i = 0; i < (int_T)(sizeof(ME416_Autonomy_Model_M->odeFAC)/sizeof(real_T));
         i++) {
      f[i] = 1.5e-8;
    }
  }

  ME416_Autonomy_Model_M->intgData.DFDX = ME416_Autonomy_Model_M->odeDFDX;
  ME416_Autonomy_Model_M->intgData.W = ME416_Autonomy_Model_M->odeW;
  ME416_Autonomy_Model_M->intgData.pivots = ME416_Autonomy_Model_M->odePIVOTS;
  ME416_Autonomy_Model_M->intgData.xtmp = ME416_Autonomy_Model_M->odeXTMP;
  ME416_Autonomy_Model_M->intgData.ztmp = ME416_Autonomy_Model_M->odeZTMP;
  ME416_Autonomy_Model_M->intgData.isFirstStep = true;
  rtsiSetSolverExtrapolationOrder(&ME416_Autonomy_Model_M->solverInfo, 4);
  rtsiSetSolverNumberNewtonIterations(&ME416_Autonomy_Model_M->solverInfo, 1);
  ME416_Autonomy_Model_M->contStates = ((X_ME416_Autonomy_Model_T *)
    &ME416_Autonomy_Model_X);
  rtsiSetSolverData(&ME416_Autonomy_Model_M->solverInfo, (void *)
                    &ME416_Autonomy_Model_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&ME416_Autonomy_Model_M->solverInfo,
    false);
  rtsiSetSolverName(&ME416_Autonomy_Model_M->solverInfo,"ode14x");
  rtmSetTPtr(ME416_Autonomy_Model_M, &ME416_Autonomy_Model_M->Timing.tArray[0]);
  rtmSetTFinal(ME416_Autonomy_Model_M, 10.0);
  ME416_Autonomy_Model_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  ME416_Autonomy_Model_M->Sizes.checksums[0] = (1300549639U);
  ME416_Autonomy_Model_M->Sizes.checksums[1] = (395780391U);
  ME416_Autonomy_Model_M->Sizes.checksums[2] = (2351874435U);
  ME416_Autonomy_Model_M->Sizes.checksums[3] = (2624967588U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    ME416_Autonomy_Model_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(ME416_Autonomy_Model_M->extModeInfo,
      &ME416_Autonomy_Model_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(ME416_Autonomy_Model_M->extModeInfo,
                        ME416_Autonomy_Model_M->Sizes.checksums);
    rteiSetTPtr(ME416_Autonomy_Model_M->extModeInfo, rtmGetTPtr
                (ME416_Autonomy_Model_M));
  }

  {
    int32_T ret;
    char_T b_0[45];
    char_T b[5];
    static const char_T tmp[5] = "none";
    static const char_T tmp_0[45] =
      "Unable to configure pin %u for PWM output.\\n";

    /* InitializeConditions for Integrator: '<S114>/w_R_integrator' */
    ME416_Autonomy_Model_X.w_R_integrator_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S113>/w_L_integrator' */
    ME416_Autonomy_Model_X.w_L_integrator_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S112>/left_encoder_integrator' */
    ME416_Autonomy_Model_X.left_encoder_integrator_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S112>/left_encoder_integrator1' */
    ME416_Autonomy_Model_X.left_encoder_integrator1_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S113>/i_L_integrator' */
    ME416_Autonomy_Model_X.i_L_integrator_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S114>/i_R_integrator' */
    ME416_Autonomy_Model_X.i_R_integrator_CSTATE = 0.0;

    /* Start for MATLABSystem: '<Root>/LED' */
    ME416_Autonomy_Model_DW.obj_g.matlabCodegenIsDeleted = false;
    ME416_Autonomy_Model_DW.obj_g.isInitialized = 1;
    for (ret = 0; ret < 5; ret++) {
      b[ret] = tmp[ret];
    }

    EXT_LED_setTrigger(0U, &b[0]);
    ME416_Autonomy_Model_DW.obj_g.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/LED' */

    /* Start for MATLABSystem: '<Root>/PWM' */
    ME416_Autonomy_Model_DW.obj.matlabCodegenIsDeleted = false;
    ME416_Autonomy_Model_DW.obj.isInitialized = 1;
    ME416_Autonomy_Model_DW.obj.PinNumber = 21U;
    ret = EXT_PWMBlock_init(ME416_Autonomy_Model_DW.obj.PinNumber, 500U, 0.0);
    if (ret != 0) {
      for (ret = 0; ret < 45; ret++) {
        b_0[ret] = tmp_0[ret];
      }

      printf(&b_0[0], ME416_Autonomy_Model_DW.obj.PinNumber);
    }

    ME416_Autonomy_Model_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/PWM' */
  }
}

/* Model terminate function */
void ME416_Autonomy_Model_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/LED' */
  if (!ME416_Autonomy_Model_DW.obj_g.matlabCodegenIsDeleted) {
    ME416_Autonomy_Model_DW.obj_g.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/LED' */
  /* Terminate for MATLABSystem: '<Root>/PWM' */
  if (!ME416_Autonomy_Model_DW.obj.matlabCodegenIsDeleted) {
    ME416_Autonomy_Model_DW.obj.matlabCodegenIsDeleted = true;
    if ((ME416_Autonomy_Model_DW.obj.isInitialized == 1) &&
        ME416_Autonomy_Model_DW.obj.isSetupComplete) {
      EXT_PWMBlock_terminate(ME416_Autonomy_Model_DW.obj.PinNumber);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
