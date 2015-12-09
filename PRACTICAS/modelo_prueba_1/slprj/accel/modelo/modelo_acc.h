#include "__cf_modelo.h"
#ifndef RTW_HEADER_modelo_acc_h_
#define RTW_HEADER_modelo_acc_h_
#ifndef modelo_acc_COMMON_INCLUDES_
#define modelo_acc_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif
#include "modelo_acc_types.h"
typedef struct { real_T B_0_7_0 [ 3 ] ; real_T B_0_8_0 [ 3 ] ; real_T
B_0_13_0 ; real_T B_0_26_0 [ 3 ] ; real_T B_0_28_0 ; real_T B_0_29_0 ; real_T
B_0_30_0 ; real_T B_0_4_0 [ 3 ] ; real_T B_0_10_0 [ 3 ] ; real_T B_0_17_0 ;
real_T B_0_19_0 [ 3 ] ; real_T B_0_3_0 [ 3 ] ; } B_modelo_T ; typedef struct
{ real_T UniformRandomNumber_NextOutput [ 3 ] ; struct { real_T TimeStampA ;
real_T LastUAtTimeA [ 3 ] ; real_T TimeStampB ; real_T LastUAtTimeB [ 3 ] ; }
Derivative1_RWORK ; struct { real_T TimeStampA ; real_T LastUAtTimeA ; real_T
TimeStampB ; real_T LastUAtTimeB ; } Derivative_RWORK ; struct { void *
LoggedData ; } psithetaphi_PWORK ; struct { void * LoggedData ; } H_PWORK ;
struct { void * LoggedData ; } Lc_PWORK ; struct { void * LoggedData ; }
T_PWORK ; struct { void * LoggedData ; } dTdV_PWORK ; struct { void *
LoggedData ; } w_PWORK ; struct { void * LoggedData ; } Scope2_PWORK ;
uint32_T RandSeed [ 3 ] ; int_T Step_MODE [ 3 ] ; } DW_modelo_T ; typedef
struct { real_T Integrator_CSTATE [ 3 ] ; real_T Integrator_CSTATE_o [ 3 ] ;
} X_modelo_T ; typedef struct { real_T Integrator_CSTATE [ 3 ] ; real_T
Integrator_CSTATE_o [ 3 ] ; } XDot_modelo_T ; typedef struct { boolean_T
Integrator_CSTATE [ 3 ] ; boolean_T Integrator_CSTATE_o [ 3 ] ; }
XDis_modelo_T ; typedef struct { real_T Integrator_CSTATE [ 3 ] ; real_T
Integrator_CSTATE_o [ 3 ] ; } CStateAbsTol_modelo_T ; typedef struct { real_T
Step_StepTime_ZC ; } ZCV_modelo_T ; typedef struct { ZCSigState
Step_StepTime_ZCE ; } PrevZCX_modelo_T ; struct P_modelo_T_ { real_T P_0 ;
real_T P_1 ; real_T P_2 [ 3 ] ; real_T P_3 [ 9 ] ; real_T P_4 [ 3 ] ; real_T
P_5 [ 3 ] ; real_T P_6 ; real_T P_7 ; real_T P_8 ; real_T P_9 [ 3 ] ; real_T
P_10 [ 3 ] ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T P_14 [ 9 ] ; }
; extern P_modelo_T modelo_rtDefaultP ;
#endif
