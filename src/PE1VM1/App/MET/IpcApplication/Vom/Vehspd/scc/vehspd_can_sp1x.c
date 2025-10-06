/* 2.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Vehicle Speed                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_CAN_SP1X_C_MAJOR                  (2)
#define VEHSPD_CAN_SP1X_C_MINOR                  (0)
#define VEHSPD_CAN_SP1X_C_PATCH                  (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vehspd_can_sp1x_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VEHSPD_CAN_SP1X_C_MAJOR != VEHSPD_CAN_SP1X_H_MAJOR) || \
     (VEHSPD_CAN_SP1X_C_MINOR != VEHSPD_CAN_SP1X_H_MINOR) || \
     (VEHSPD_CAN_SP1X_C_PATCH != VEHSPD_CAN_SP1X_H_PATCH))
#error "vehspd_can_sp1x.c and vehspd_can_sp1x.h : source and header files are inconsistent!"
#endif

#if ((VEHSPD_CAN_SP1X_C_MAJOR != VEHSPD_CAN_SP1X_CFG_H_MAJOR) || \
     (VEHSPD_CAN_SP1X_C_MINOR != VEHSPD_CAN_SP1X_CFG_H_MINOR) || \
     (VEHSPD_CAN_SP1X_C_PATCH != VEHSPD_CAN_SP1X_CFG_H_PATCH))
#error "vehspd_can_sp1x.c and vehspd_can_sp1x_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_CAN_FLTR_NUM_STS                  (4U)
#define VEHSPD_CAN_FLTR_INIT                     (0U)
#define VEHSPD_CAN_FLTR_RUN                      (1U)
#define VEHSPD_CAN_FLTR_EMST                     (2U)
#define VEHSPD_CAN_FLTR_INACT                    (3U)

#define VEHSPD_CAN_FLTR_ACT_TO_INACT             (0U)
#define VEHSPD_CAN_FLTR_ACT_TO_INIT              (1U)
#define VEHSPD_CAN_FLTR_ACT_INIT                 (2U)
#define VEHSPD_CAN_FLTR_ACT_INIT_NRT             (3U)      /* No Rx Timeout since power-on mask is active */
#define VEHSPD_CAN_FLTR_ACT_TO_RUN               (4U)
#define VEHSPD_CAN_FLTR_ACT_RUN                  (5U)
#define VEHSPD_CAN_FLTR_ACT_RUN_NRT              (6U)      /* No Rx Timeout since power-on mask is active */
#define VEHSPD_CAN_FLTR_ACT_TO_EMST              (7U)

#define VEHSPD_CAN_FLTR_NUM_CHK                  (16U)
#define VEHSPD_CAN_FLTR_BIT_IGN_RUN              (0x01U)   /* Ignition is in Run                */
#define VEHSPD_CAN_FLTR_BIT_SNS_INIT             (0x02U)   /* Sensor/ECU initialization         */
#define VEHSPD_CAN_FLTR_BIT_SP1X_RX              (0x04U)   /* SP1 is less than or equal minimum */
#define VEHSPD_CAN_FLTR_BIT_SP1_EQZ              (0x08U)

#define VEHSPD_CAN_SP1P_MAX                      (0x3fU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2        u2_sp1;                                      /* CAN Rx signal SP1                           */
    U1        u1_sp1p;                                     /* CAN Rx signal SP1P                          */
    U1        u1_stsbit;                                   /* Vehicle speed CAN message status            */
}ST_VEHSPD_SP1X;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2       u2_s_vehspd_can_tmelpsd;                   /* Elapsed time from IG-ON                     */
static U1       u1_s_vehspd_can_fltrsts;                   /* Vehicle speed filter status                 */
static U1       u1_s_vehspd_can_sp1p_base;                 /* Based value of SP1P                         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_VehspdCanSp1xIgnchk(void);
static void    vd_s_VehspdCanSp1xFltrAct(const U1 u1_a_FLTRCHK, ST_VEHSPD_SP1X * st_ap_sp1x);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VehspdCanSp1xInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdCanSp1xInit(void)
{
    u2_s_vehspd_can_tmelpsd   = (U2)0U;
    u1_s_vehspd_can_fltrsts   = (U1)VEHSPD_CAN_FLTR_INACT;
    u1_s_vehspd_can_sp1p_base = (U1)U1_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_VehspdCanSp1xOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VehspdCanSp1xOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
    U4                    u4_t_evtchk;
    U2                    u2_t_sp1;
    U1                    u1_t_sp1p;
    U1                    u1_t_stsbit;
    U1                    u1_t_updt;

    u1_t_updt = (U1)FALSE;
#if 0   /* BEV Rebase provisionally */
    u4_t_evtchk = u4_a_EVTBIT & (U4)VEH_OPEMD_EVTBIT_IGN_TO_ON;
#else   /* BEV Rebase provisionally */
    u4_t_evtchk = (U4)0U;
#endif   /* BEV Rebase provisionally */
    if(u4_t_evtchk != (U4)0U){

        u2_t_sp1    = (U2)0U;
        u1_t_sp1p   = (U1)0U;
        u1_t_stsbit = u1_g_VehspdCanSp1xComRx(&u2_t_sp1, &u1_t_sp1p);
        if((u1_s_vehspd_can_fltrsts >= (U1)VEHSPD_CAN_FLTR_INACT) ||
           (u1_t_stsbit             != (U1)VEHSPD_STSBIT_VALID  ) ||
           (u2_t_sp1                <  (U2)VEHSPD_CAN_SP1_MIN   )){

            vd_g_VehspdCanSp1xInit();
            vd_g_VehspdCanSp1xComRxInit();
            u1_t_updt = (U1)TRUE;
        }
    }
    return(u1_t_updt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VehspdCanSp1xKmph(U2 * u2_ap_kmph, U4 * u4_ap_odocnt)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VehspdCanSp1xKmph(U2 * u2_ap_kmph, U4 * u4_ap_odocnt)
{
    ST_VEHSPD_SP1X        st_t_sp1x;
    U1                    u1_t_fltrchk;

    st_t_sp1x.u2_sp1    = (U2)0U;
    st_t_sp1x.u1_sp1p   = (U1)0U;
    st_t_sp1x.u1_stsbit = u1_g_VehspdCanSp1xComRx(&st_t_sp1x.u2_sp1, &st_t_sp1x.u1_sp1p);

    if(st_t_sp1x.u1_stsbit != (U1)VEHSPD_STSBIT_VALID){
        (*u4_ap_odocnt)   = (U4)0U;
        st_t_sp1x.u1_sp1p = (U1)U1_MAX;
        u1_t_fltrchk      = (U1)0U;
    }
    else if(st_t_sp1x.u2_sp1 < (U2)VEHSPD_CAN_SP1_MIN){
        (*u4_ap_odocnt)   = (U4)0U;
        st_t_sp1x.u2_sp1  = (U2)0U;
        u1_t_fltrchk      = (U1)VEHSPD_CAN_FLTR_BIT_SP1_EQZ | (U1)VEHSPD_CAN_FLTR_BIT_SP1X_RX;
    }
    else if(u1_s_vehspd_can_sp1p_base > (U1)VEHSPD_CAN_SP1P_MAX){
        (*u4_ap_odocnt)   = (U4)0U;
        u1_t_fltrchk      = (U1)VEHSPD_CAN_FLTR_BIT_SP1X_RX;
    }
    else{
        (*u4_ap_odocnt)   = ((U4)st_t_sp1x.u1_sp1p - (U4)u1_s_vehspd_can_sp1p_base) & (U4)VEHSPD_CAN_SP1P_MAX;
        /* The variable of u1_sp1p is rolling counter                                                                                */
        /* Therefore no max protection is implemented.                                                                               */
        u1_t_fltrchk      = (U1)VEHSPD_CAN_FLTR_BIT_SP1X_RX;
    }

    u1_t_fltrchk |= u1_s_VehspdCanSp1xIgnchk();
    vd_s_VehspdCanSp1xFltrAct(u1_t_fltrchk, &st_t_sp1x);

    *u2_ap_kmph               = st_t_sp1x.u2_sp1;
    u1_s_vehspd_can_sp1p_base = st_t_sp1x.u1_sp1p;

    return(st_t_sp1x.u1_stsbit);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_VehspdCanSp1xIgnchk(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_VehspdCanSp1xIgnchk(void)
{
    U1                    u1_t_fltrchk;
    U1                    u1_t_igon;

    u1_t_igon = u1_g_VehspdCanSp1xIgnOn();
    if(u1_t_igon == (U1)TRUE){

        if(u2_s_vehspd_can_tmelpsd < (U2)U2_MAX){
            u2_s_vehspd_can_tmelpsd++;
        }

        if(u2_s_vehspd_can_tmelpsd < u2_g_VEHSPD_CAN_SP1X_1ST_TOUT){
            u1_t_fltrchk = (U1)VEHSPD_CAN_FLTR_BIT_SNS_INIT | (U1)VEHSPD_CAN_FLTR_BIT_IGN_RUN;
        }
        else{
            u1_t_fltrchk = (U1)VEHSPD_CAN_FLTR_BIT_IGN_RUN;
        }
    }
    else{
        u2_s_vehspd_can_tmelpsd = (U2)0U;
        u1_t_fltrchk            = (U1)0U;
    }

    return(u1_t_fltrchk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_VehspdCanSp1xFltrAct(const U1 u1_a_FLTRCHK, ST_VEHSPD_SP1X * st_ap_sp1x)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VehspdCanSp1xFltrAct(const U1 u1_a_FLTRCHK, ST_VEHSPD_SP1X * st_ap_sp1x)
{
    static const U1       u1_sp_VEHSPD_CAN_FLTR_STM[VEHSPD_CAN_FLTR_NUM_CHK][VEHSPD_CAN_FLTR_NUM_STS] = {  /* Action decision table  */
        {
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_INIT,       (U1)VEHSPD_CAN_FLTR_ACT_RUN,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INIT,    (U1)VEHSPD_CAN_FLTR_ACT_TO_INIT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_INIT_NRT,   (U1)VEHSPD_CAN_FLTR_ACT_RUN_NRT,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INIT,    (U1)VEHSPD_CAN_FLTR_ACT_TO_INIT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_TO_EMST,    (U1)VEHSPD_CAN_FLTR_ACT_TO_EMST,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_EMST,    (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_RUN,        (U1)VEHSPD_CAN_FLTR_ACT_RUN,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_RUN,     (U1)VEHSPD_CAN_FLTR_ACT_TO_RUN
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_TO_EMST,    (U1)VEHSPD_CAN_FLTR_ACT_TO_EMST,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_EMST,    (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_RUN,        (U1)VEHSPD_CAN_FLTR_ACT_RUN,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_RUN,     (U1)VEHSPD_CAN_FLTR_ACT_TO_RUN
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_INIT,       (U1)VEHSPD_CAN_FLTR_ACT_RUN,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INIT,    (U1)VEHSPD_CAN_FLTR_ACT_TO_INIT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_INIT_NRT,   (U1)VEHSPD_CAN_FLTR_ACT_RUN_NRT,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INIT,    (U1)VEHSPD_CAN_FLTR_ACT_TO_INIT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_RUN,        (U1)VEHSPD_CAN_FLTR_ACT_RUN,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_RUN,     (U1)VEHSPD_CAN_FLTR_ACT_TO_RUN
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT,   (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT
        },
        {
            (U1)VEHSPD_CAN_FLTR_ACT_RUN,        (U1)VEHSPD_CAN_FLTR_ACT_RUN,
            (U1)VEHSPD_CAN_FLTR_ACT_TO_RUN,     (U1)VEHSPD_CAN_FLTR_ACT_TO_RUN
        }
    };

    U1                    u1_t_fltract;

    if(u1_s_vehspd_can_fltrsts < (U1)VEHSPD_CAN_FLTR_NUM_STS){
        u1_t_fltract = u1_sp_VEHSPD_CAN_FLTR_STM[u1_a_FLTRCHK][u1_s_vehspd_can_fltrsts];
    }
    else{
        u1_t_fltract = (U1)VEHSPD_CAN_FLTR_ACT_TO_INACT;
    }

    switch(u1_t_fltract){
        case VEHSPD_CAN_FLTR_ACT_TO_INIT:
            u1_s_vehspd_can_fltrsts   = (U1)VEHSPD_CAN_FLTR_INIT;
            u2_s_vehspd_can_tmelpsd   = (U2)0U;
            st_ap_sp1x->u2_sp1        = (U2)0U;
            st_ap_sp1x->u1_stsbit     = (U1)VEHSPD_STSBIT_UNKNOWN;
            break;
        case VEHSPD_CAN_FLTR_ACT_INIT:
            u1_s_vehspd_can_fltrsts   = (U1)VEHSPD_CAN_FLTR_INIT;
            st_ap_sp1x->u2_sp1        = (U2)0U;
            st_ap_sp1x->u1_stsbit    |= (U1)VEHSPD_STSBIT_UNKNOWN;
            break;
        case VEHSPD_CAN_FLTR_ACT_INIT_NRT:
            u1_s_vehspd_can_fltrsts   = (U1)VEHSPD_CAN_FLTR_INIT;
            st_ap_sp1x->u2_sp1        = (U2)0U;
            st_ap_sp1x->u1_stsbit     = (U1)VEHSPD_STSBIT_UNKNOWN;
            break;
        case VEHSPD_CAN_FLTR_ACT_TO_RUN:
            u1_s_vehspd_can_fltrsts   = (U1)VEHSPD_CAN_FLTR_RUN;
            u2_s_vehspd_can_tmelpsd   = (U2)0U;
            break;
        case VEHSPD_CAN_FLTR_ACT_RUN:
            u1_s_vehspd_can_fltrsts   = (U1)VEHSPD_CAN_FLTR_RUN;
            break;
        case VEHSPD_CAN_FLTR_ACT_RUN_NRT:
            u1_s_vehspd_can_fltrsts   = (U1)VEHSPD_CAN_FLTR_RUN;
            st_ap_sp1x->u1_stsbit     = (U1)VEHSPD_STSBIT_VALID;
            break;
        case VEHSPD_CAN_FLTR_ACT_TO_EMST:
            u1_s_vehspd_can_fltrsts   = (U1)VEHSPD_CAN_FLTR_EMST;
            st_ap_sp1x->u1_stsbit     = (U1)VEHSPD_STSBIT_EMSTOP;
            break;
        default:
            u1_s_vehspd_can_fltrsts   = (U1)VEHSPD_CAN_FLTR_INACT;
            st_ap_sp1x->u1_sp1p       = (U1)U1_MAX;
            st_ap_sp1x->u1_stsbit     = (U1)VEHSPD_STSBIT_UNKNOWN;
            break;
    }
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     1/29/2018  TN       New.                                                                                               */
/*  1.1.0     3/27/2018  TN       QAC function metrics was improved.                                                                 */
/*  1.2.0     9/18/2019  TN       #define VEHSPD_CAN_SP1_MIN was moved to vehspd_can_sp1x_cfg_private.h.                             */
/*  1.3.0     7/20/2020  TN       Bug Fix : The power-on mask timer was not initialized if u1_s_vehspd_can_fltrsts was               */
/*                                VEHSPD_CAN_FLTR_EMST.                                                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
