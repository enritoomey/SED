#include "__cf_modelo.h"
#include <math.h>
#include "modelo_acc.h"
#include "modelo_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { uint32_T lo ; uint32_T
hi ; lo = * u % 127773U * 16807U ; hi = * u / 127773U * 2836U ; if ( lo < hi
) { * u = 2147483647U - ( hi - lo ) ; } else { * u = lo - hi ; } return (
real_T ) * u * 4.6566128752457969E-10 ; } static void mdlOutputs ( SimStruct
* S , int_T tid ) { real_T B_0_0_0 [ 3 ] ; real_T B_0_21_0 ; real_T B_0_25_0
[ 3 ] ; real_T B_0_22_0 ; int32_T i ; B_modelo_T * _rtB ; P_modelo_T * _rtP ;
DW_modelo_T * _rtDW ; _rtDW = ( ( DW_modelo_T * ) ssGetRootDWork ( S ) ) ;
_rtP = ( ( P_modelo_T * ) ssGetDefaultParam ( S ) ) ; _rtB = ( ( B_modelo_T *
) _ssGetBlockIO ( S ) ) ; B_0_0_0 [ 0 ] = ( ( X_modelo_T * ) ssGetContStates
( S ) ) -> Integrator_CSTATE [ 0 ] ; B_0_0_0 [ 1 ] = ( ( X_modelo_T * )
ssGetContStates ( S ) ) -> Integrator_CSTATE [ 1 ] ; B_0_0_0 [ 2 ] = ( (
X_modelo_T * ) ssGetContStates ( S ) ) -> Integrator_CSTATE [ 2 ] ; _rtB ->
B_0_3_0 [ 0 ] = _rtP -> P_1 * B_0_0_0 [ 0 ] ; _rtB -> B_0_3_0 [ 1 ] = _rtP ->
P_1 * B_0_0_0 [ 1 ] ; _rtB -> B_0_3_0 [ 2 ] = _rtP -> P_1 * B_0_0_0 [ 2 ] ;
ssCallAccelRunBlock ( S , 0 , 2 , SS_CALL_MDL_OUTPUTS ) ; ( ( B_modelo_T * )
_ssGetBlockIO ( S ) ) -> B_0_3_0 [ 0 ] = ( ( X_modelo_T * ) ssGetContStates (
S ) ) -> Integrator_CSTATE_o [ 0 ] ; ( ( B_modelo_T * ) _ssGetBlockIO ( S ) )
-> B_0_3_0 [ 1 ] = ( ( X_modelo_T * ) ssGetContStates ( S ) ) ->
Integrator_CSTATE_o [ 1 ] ; ( ( B_modelo_T * ) _ssGetBlockIO ( S ) ) ->
B_0_3_0 [ 2 ] = ( ( X_modelo_T * ) ssGetContStates ( S ) ) ->
Integrator_CSTATE_o [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) { _rtB -> B_0_4_0 [
i ] = 0.0 ; _rtB -> B_0_4_0 [ i ] += _rtP -> P_3 [ i ] * _rtB -> B_0_3_0 [ 0
] ; _rtB -> B_0_4_0 [ i ] += _rtP -> P_3 [ i + 3 ] * _rtB -> B_0_3_0 [ 1 ] ;
_rtB -> B_0_4_0 [ i ] += _rtP -> P_3 [ i + 6 ] * _rtB -> B_0_3_0 [ 2 ] ; }
ssCallAccelRunBlock ( S , 0 , 5 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit
( S , 2 , 0 ) ) { _rtB -> B_0_7_0 [ 0 ] = _rtP -> P_7 * _rtDW ->
UniformRandomNumber_NextOutput [ 0 ] ; _rtB -> B_0_7_0 [ 1 ] = _rtP -> P_7 *
_rtDW -> UniformRandomNumber_NextOutput [ 1 ] ; _rtB -> B_0_7_0 [ 2 ] = _rtP
-> P_7 * _rtDW -> UniformRandomNumber_NextOutput [ 2 ] ; } if ( ssIsSampleHit
( S , 1 , 0 ) ) { B_0_22_0 = ssGetTaskTime ( S , 1 ) ; if ( ssIsMajorTimeStep
( S ) ) { _rtDW -> Step_MODE [ 0 ] = ( B_0_22_0 >= _rtP -> P_8 ) ; _rtDW ->
Step_MODE [ 1 ] = ( B_0_22_0 >= _rtP -> P_8 ) ; _rtDW -> Step_MODE [ 2 ] = (
B_0_22_0 >= _rtP -> P_8 ) ; } if ( _rtDW -> Step_MODE [ 0 ] == 1 ) { _rtB ->
B_0_8_0 [ 0 ] = _rtP -> P_10 [ 0 ] ; } else { _rtB -> B_0_8_0 [ 0 ] = _rtP ->
P_9 [ 0 ] ; } if ( _rtDW -> Step_MODE [ 1 ] == 1 ) { _rtB -> B_0_8_0 [ 1 ] =
_rtP -> P_10 [ 1 ] ; } else { _rtB -> B_0_8_0 [ 1 ] = _rtP -> P_9 [ 1 ] ; }
if ( _rtDW -> Step_MODE [ 2 ] == 1 ) { _rtB -> B_0_8_0 [ 2 ] = _rtP -> P_10 [
2 ] ; } else { _rtB -> B_0_8_0 [ 2 ] = _rtP -> P_9 [ 2 ] ; } } { real_T t =
ssGetTaskTime ( S , 0 ) ; real_T timeStampA = _rtDW -> Derivative1_RWORK .
TimeStampA ; real_T timeStampB = _rtDW -> Derivative1_RWORK . TimeStampB ;
real_T * lastU = & _rtDW -> Derivative1_RWORK . LastUAtTimeA [ 0 ] ; if (
timeStampA >= t && timeStampB >= t ) { B_0_25_0 [ 0 ] = 0.0 ; B_0_25_0 [ 1 ]
= 0.0 ; B_0_25_0 [ 2 ] = 0.0 ; } else { real_T deltaT ; real_T lastTime =
timeStampA ; if ( timeStampA < timeStampB ) { if ( timeStampB < t ) {
lastTime = timeStampB ; lastU = & _rtDW -> Derivative1_RWORK . LastUAtTimeB [
0 ] ; } } else if ( timeStampA >= t ) { lastTime = timeStampB ; lastU = &
_rtDW -> Derivative1_RWORK . LastUAtTimeB [ 0 ] ; } deltaT = t - lastTime ;
B_0_25_0 [ 0 ] = ( ( ( B_modelo_T * ) _ssGetBlockIO ( S ) ) -> B_0_8_0 [ 0 ]
- * lastU ++ ) / deltaT ; B_0_25_0 [ 1 ] = ( ( ( B_modelo_T * ) _ssGetBlockIO
( S ) ) -> B_0_8_0 [ 1 ] - * lastU ++ ) / deltaT ; B_0_25_0 [ 2 ] = ( ( (
B_modelo_T * ) _ssGetBlockIO ( S ) ) -> B_0_8_0 [ 2 ] - * lastU ++ ) / deltaT
; } } _rtB -> B_0_10_0 [ 0 ] = _rtB -> B_0_7_0 [ 0 ] + B_0_25_0 [ 0 ] ; _rtB
-> B_0_10_0 [ 1 ] = _rtB -> B_0_7_0 [ 1 ] + B_0_25_0 [ 1 ] ; _rtB -> B_0_10_0
[ 2 ] = _rtB -> B_0_7_0 [ 2 ] + B_0_25_0 [ 2 ] ; ssCallAccelRunBlock ( S , 0
, 11 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_0_13_0 = ( ( _rtB -> B_0_4_0 [ 0 ] *
_rtB -> B_0_3_0 [ 0 ] + _rtB -> B_0_4_0 [ 1 ] * _rtB -> B_0_3_0 [ 1 ] ) +
_rtB -> B_0_4_0 [ 2 ] * _rtB -> B_0_3_0 [ 2 ] ) * _rtP -> P_11 ;
ssCallAccelRunBlock ( S , 0 , 14 , SS_CALL_MDL_OUTPUTS ) ; B_0_22_0 = ( _rtB
-> B_0_10_0 [ 0 ] * _rtB -> B_0_4_0 [ 0 ] + _rtB -> B_0_10_0 [ 1 ] * _rtB ->
B_0_4_0 [ 1 ] ) + _rtB -> B_0_10_0 [ 2 ] * _rtB -> B_0_4_0 [ 2 ] ; { real_T t
= ssGetTaskTime ( S , 0 ) ; real_T timeStampA = _rtDW -> Derivative_RWORK .
TimeStampA ; real_T timeStampB = _rtDW -> Derivative_RWORK . TimeStampB ;
real_T * lastU = & _rtDW -> Derivative_RWORK . LastUAtTimeA ; if ( timeStampA
>= t && timeStampB >= t ) { B_0_21_0 = 0.0 ; } else { real_T deltaT ; real_T
lastTime = timeStampA ; if ( timeStampA < timeStampB ) { if ( timeStampB < t
) { lastTime = timeStampB ; lastU = & _rtDW -> Derivative_RWORK .
LastUAtTimeB ; } } else if ( timeStampA >= t ) { lastTime = timeStampB ;
lastU = & _rtDW -> Derivative_RWORK . LastUAtTimeB ; } deltaT = t - lastTime
; B_0_21_0 = ( ( ( B_modelo_T * ) _ssGetBlockIO ( S ) ) -> B_0_13_0 - * lastU
++ ) / deltaT ; } } _rtB -> B_0_17_0 = B_0_21_0 - B_0_22_0 ;
ssCallAccelRunBlock ( S , 0 , 18 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_0_19_0 [
0 ] = _rtP -> P_12 * _rtB -> B_0_3_0 [ 0 ] ; _rtB -> B_0_19_0 [ 1 ] = _rtP ->
P_12 * _rtB -> B_0_3_0 [ 1 ] ; _rtB -> B_0_19_0 [ 2 ] = _rtP -> P_12 * _rtB
-> B_0_3_0 [ 2 ] ; ssCallAccelRunBlock ( S , 0 , 20 , SS_CALL_MDL_OUTPUTS ) ;
B_0_21_0 = _rtB -> B_0_3_0 [ 1 ] * _rtB -> B_0_4_0 [ 2 ] - _rtB -> B_0_3_0 [
2 ] * _rtB -> B_0_4_0 [ 1 ] ; B_0_25_0 [ 0 ] = _rtP -> P_13 * B_0_21_0 ;
B_0_25_0 [ 1 ] = ( _rtB -> B_0_3_0 [ 2 ] * _rtB -> B_0_4_0 [ 0 ] - _rtB ->
B_0_3_0 [ 0 ] * _rtB -> B_0_4_0 [ 2 ] ) * _rtP -> P_13 ; B_0_25_0 [ 2 ] = (
_rtB -> B_0_3_0 [ 0 ] * _rtB -> B_0_4_0 [ 1 ] - _rtB -> B_0_3_0 [ 1 ] * _rtB
-> B_0_4_0 [ 0 ] ) * _rtP -> P_13 ; B_0_25_0 [ 0 ] += _rtB -> B_0_10_0 [ 0 ]
; B_0_25_0 [ 1 ] += _rtB -> B_0_10_0 [ 1 ] ; B_0_25_0 [ 2 ] += _rtB ->
B_0_10_0 [ 2 ] ; for ( i = 0 ; i < 3 ; i ++ ) { _rtB -> B_0_26_0 [ i ] = 0.0
; _rtB -> B_0_26_0 [ i ] += _rtP -> P_14 [ i ] * B_0_25_0 [ 0 ] ; _rtB ->
B_0_26_0 [ i ] += _rtP -> P_14 [ i + 3 ] * B_0_25_0 [ 1 ] ; _rtB -> B_0_26_0
[ i ] += _rtP -> P_14 [ i + 6 ] * B_0_25_0 [ 2 ] ; } ssCallAccelRunBlock ( S
, 0 , 27 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_0_28_0 = ( ( _rtB -> B_0_3_0 [ 1
] * muDoubleScalarSin ( B_0_0_0 [ 1 ] ) * muDoubleScalarSin ( B_0_0_0 [ 2 ] )
+ _rtB -> B_0_3_0 [ 0 ] * muDoubleScalarCos ( B_0_0_0 [ 1 ] ) ) + _rtB ->
B_0_3_0 [ 2 ] * muDoubleScalarSin ( B_0_0_0 [ 1 ] ) * muDoubleScalarCos (
B_0_0_0 [ 2 ] ) ) / muDoubleScalarCos ( B_0_0_0 [ 1 ] ) ; _rtB -> B_0_29_0 =
( _rtB -> B_0_3_0 [ 1 ] * muDoubleScalarSin ( B_0_0_0 [ 2 ] ) + _rtB ->
B_0_3_0 [ 2 ] * muDoubleScalarCos ( B_0_0_0 [ 2 ] ) ) / muDoubleScalarCos (
B_0_0_0 [ 1 ] ) ; _rtB -> B_0_30_0 = ( _rtB -> B_0_3_0 [ 1 ] *
muDoubleScalarCos ( B_0_0_0 [ 1 ] ) * muDoubleScalarCos ( B_0_0_0 [ 2 ] ) -
_rtB -> B_0_3_0 [ 2 ] * muDoubleScalarCos ( B_0_0_0 [ 1 ] ) *
muDoubleScalarSin ( B_0_0_0 [ 2 ] ) ) / muDoubleScalarCos ( B_0_0_0 [ 1 ] ) ;
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { B_modelo_T * _rtB ;
P_modelo_T * _rtP ; DW_modelo_T * _rtDW ; _rtDW = ( ( DW_modelo_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_modelo_T * ) ssGetDefaultParam ( S ) )
; _rtB = ( ( B_modelo_T * ) _ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S ,
2 , 0 ) ) { _rtDW -> UniformRandomNumber_NextOutput [ 0 ] = ( _rtP -> P_5 [ 0
] - _rtP -> P_4 [ 0 ] ) * rt_urand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed [
0 ] ) + _rtP -> P_4 [ 0 ] ; _rtDW -> UniformRandomNumber_NextOutput [ 1 ] = (
_rtP -> P_5 [ 1 ] - _rtP -> P_4 [ 1 ] ) * rt_urand_Upu32_Yd_f_pw_snf ( &
_rtDW -> RandSeed [ 1 ] ) + _rtP -> P_4 [ 1 ] ; _rtDW ->
UniformRandomNumber_NextOutput [ 2 ] = ( _rtP -> P_5 [ 2 ] - _rtP -> P_4 [ 2
] ) * rt_urand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed [ 2 ] ) + _rtP -> P_4
[ 2 ] ; } { real_T timeStampA = _rtDW -> Derivative1_RWORK . TimeStampA ;
real_T timeStampB = _rtDW -> Derivative1_RWORK . TimeStampB ; real_T *
lastTime = & _rtDW -> Derivative1_RWORK . TimeStampA ; real_T * lastU = &
_rtDW -> Derivative1_RWORK . LastUAtTimeA [ 0 ] ; if ( timeStampA != rtInf )
{ if ( timeStampB == rtInf ) { lastTime = & _rtDW -> Derivative1_RWORK .
TimeStampB ; lastU = & _rtDW -> Derivative1_RWORK . LastUAtTimeB [ 0 ] ; }
else if ( timeStampA >= timeStampB ) { lastTime = & _rtDW ->
Derivative1_RWORK . TimeStampB ; lastU = & _rtDW -> Derivative1_RWORK .
LastUAtTimeB [ 0 ] ; } } * lastTime = ssGetTaskTime ( S , 0 ) ; * lastU ++ =
( ( B_modelo_T * ) _ssGetBlockIO ( S ) ) -> B_0_8_0 [ 0 ] ; * lastU ++ = ( (
B_modelo_T * ) _ssGetBlockIO ( S ) ) -> B_0_8_0 [ 1 ] ; * lastU ++ = ( (
B_modelo_T * ) _ssGetBlockIO ( S ) ) -> B_0_8_0 [ 2 ] ; } { real_T timeStampA
= _rtDW -> Derivative_RWORK . TimeStampA ; real_T timeStampB = _rtDW ->
Derivative_RWORK . TimeStampB ; real_T * lastTime = & _rtDW ->
Derivative_RWORK . TimeStampA ; real_T * lastU = & _rtDW -> Derivative_RWORK
. LastUAtTimeA ; if ( timeStampA != rtInf ) { if ( timeStampB == rtInf ) {
lastTime = & _rtDW -> Derivative_RWORK . TimeStampB ; lastU = & _rtDW ->
Derivative_RWORK . LastUAtTimeB ; } else if ( timeStampA >= timeStampB ) {
lastTime = & _rtDW -> Derivative_RWORK . TimeStampB ; lastU = & _rtDW ->
Derivative_RWORK . LastUAtTimeB ; } } * lastTime = ssGetTaskTime ( S , 0 ) ;
* lastU ++ = ( ( B_modelo_T * ) _ssGetBlockIO ( S ) ) -> B_0_13_0 ; }
UNUSED_PARAMETER ( tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_modelo_T * _rtB ; P_modelo_T
* _rtP ; _rtP = ( ( P_modelo_T * ) ssGetDefaultParam ( S ) ) ; _rtB = ( (
B_modelo_T * ) _ssGetBlockIO ( S ) ) ; { ( ( XDot_modelo_T * ) ssGetdX ( S )
) -> Integrator_CSTATE [ 0 ] = ( ( B_modelo_T * ) _ssGetBlockIO ( S ) ) ->
B_0_29_0 ; ( ( XDot_modelo_T * ) ssGetdX ( S ) ) -> Integrator_CSTATE [ 1 ] =
( ( B_modelo_T * ) _ssGetBlockIO ( S ) ) -> B_0_30_0 ; ( ( XDot_modelo_T * )
ssGetdX ( S ) ) -> Integrator_CSTATE [ 2 ] = ( ( B_modelo_T * ) _ssGetBlockIO
( S ) ) -> B_0_28_0 ; } { ( ( XDot_modelo_T * ) ssGetdX ( S ) ) ->
Integrator_CSTATE_o [ 0 ] = ( ( B_modelo_T * ) _ssGetBlockIO ( S ) ) ->
B_0_26_0 [ 0 ] ; ( ( XDot_modelo_T * ) ssGetdX ( S ) ) -> Integrator_CSTATE_o
[ 1 ] = ( ( B_modelo_T * ) _ssGetBlockIO ( S ) ) -> B_0_26_0 [ 1 ] ; ( (
XDot_modelo_T * ) ssGetdX ( S ) ) -> Integrator_CSTATE_o [ 2 ] = ( (
B_modelo_T * ) _ssGetBlockIO ( S ) ) -> B_0_26_0 [ 2 ] ; } }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { ( ( ZCV_modelo_T * )
ssGetSolverZcSignalVector ( S ) ) -> Step_StepTime_ZC = ssGetT ( S ) - ( (
P_modelo_T * ) ssGetDefaultParam ( S ) ) -> P_8 ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 4034872413U
) ; ssSetChecksumVal ( S , 1 , 3936411131U ) ; ssSetChecksumVal ( S , 2 ,
2854028179U ) ; ssSetChecksumVal ( S , 3 , 3369665888U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "8.1" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_modelo_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_modelo_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_modelo_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & modelo_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; }
static void mdlInitializeSampleTimes ( SimStruct * S ) { } static void
mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
