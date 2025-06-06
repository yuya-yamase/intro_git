/* 5.3.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert M_T120                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_M_T120_C_MAJOR                     (5)
#define ALERT_M_T120_C_MINOR                     (3)
#define ALERT_M_T120_C_PATCH                     (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_M_T120_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_M_T120.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_M_T120_NUM_DST                     (64U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertM_t120Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_M_T120_DST[ALERT_M_T120_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 33 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 35 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 37 PRMRYCHK                                        */
    (U1)ALERT_REQ_M_T120_TT_PD_ON,                                             /* 38 TT_PD_ON                                        */
    (U1)ALERT_REQ_M_T120_PRMRYCHK_PD,                                          /* 39 PRMRYCHK_PD                                     */
    (U1)ALERT_REQ_M_T120_TT_PD_ON,                                             /* 40 TT_PD_ON                                        */
    (U1)ALERT_REQ_M_T120_PRMRYCHK_PD,                                          /* 41 PRMRYCHK_PD                                     */
    (U1)ALERT_REQ_M_T120_TT_PD_ON,                                             /* 42 TT_PD_ON                                        */
    (U1)ALERT_REQ_M_T120_PRMRYCHK_PD,                                          /* 43 PRMRYCHK_PD                                     */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 45 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 47 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 49 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 51 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 53 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 55 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 57 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 58 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 59 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 60 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK,                                             /* 61 PRMRYCHK                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 62 UNKNOWN                                         */
    (U1)ALERT_REQ_M_T120_PRMRYCHK                                              /* 63 PRMRYCHK                                        */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_M_T120_MTRX[1] = {
    {
        &u4_s_AlertM_t120Srcchk,                                               /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_M_T120_DST[0],                                            /* u1p_DST                                            */
        (U2)ALERT_M_T120_NUM_DST,                                              /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertM_t120Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertM_t120Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U4 u4_s_ALERT_M_T120_TIM_PRMRYCHK = ((U4)3000U / (U4)ALERT_MAIN_TICK);
    static const U2 u2_s_ALERT_M_T120_THRSH_LOWER  = (U2)11950U;
    static const U2 u2_s_ALERT_M_T120_THRSH_UPPER  = (U2)12050U;

    static const U4 u4_s_ALERT_M_T120_BIT_PRMRYCHK = (U4)0x00000001U;
    static const U4 u4_s_ALERT_M_T120_BIT_HYS_JDG  = (U4)0x00000002U;
    static const U4 u4_s_ALERT_M_T120_BIT_SPD_MID  = (U4)0x00000004U;
    static const U4 u4_s_ALERT_M_T120_BIT_SPD_HIGH = (U4)0x00000008U;
    static const U4 u4_s_ALERT_M_T120_BIT_SPD_INVD = (U4)0x00000010U;
    static const U4 u4_s_ALERT_M_T120_BIT_IGN_ON   = (U4)0x00000020U;
    static const U1 u1_s_ALERT_M_T120_LAST_REQ_MSK = (U1)0x03U;

    U4              u4_t_src_chk;
    U2              u2_t_vehspd;
    U1              u1_t_vehspd_sts;
    U1              u1_t_last_req;

    u1_t_last_req   = (U1)0U;
    if(u1_a_LAS != (U1)ALERT_REQ_UNKNOWN){
        u1_t_last_req = (U1)(u1_a_LAS & u1_s_ALERT_M_T120_LAST_REQ_MSK);
    }

    u4_t_src_chk    = (U4)0U;
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk  = u4_s_ALERT_M_T120_BIT_IGN_ON;
        if(u4_a_IGN_TM < u4_s_ALERT_M_T120_TIM_PRMRYCHK){
            u4_t_src_chk |= u4_s_ALERT_M_T120_BIT_PRMRYCHK;
        }
        if(u1_t_last_req != (U1)ALERT_REQ_M_T120_PRMRYCHK){
            u4_t_src_chk |= u4_s_ALERT_M_T120_BIT_HYS_JDG;
        }
    }

    u2_t_vehspd     = (U2)0U;
    u1_t_vehspd_sts = u1_g_AlertSpdKmphBiased(&u2_t_vehspd, (U1)FALSE);

    if(u1_t_vehspd_sts == (U1)ALERT_SPD_STSBIT_VALID){
        if(u2_s_ALERT_M_T120_THRSH_UPPER <= u2_t_vehspd){
            u4_t_src_chk |= u4_s_ALERT_M_T120_BIT_SPD_HIGH;
        }
        else if(u2_s_ALERT_M_T120_THRSH_LOWER < u2_t_vehspd){
            u4_t_src_chk |= u4_s_ALERT_M_T120_BIT_SPD_MID;
        }
        else{
            /* SPD_LOW(0) */
        }
    }
    else{
        u4_t_src_chk |= u4_s_ALERT_M_T120_BIT_SPD_INVD;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     2/26/2020  SK       New.                                                                                               */
/*  5.1.0     5/15/2020  ZS       Modify Hysteresis timing.                                                                          */
/*  5.2.0     6/10/2020  ZS       Fix valve check time 3050ms -> 3000ms.                                                             */
/*  5.3.0    12/ 8/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.3.1     3/17/2021  MO       Update for 840B CV(Version update).                                                                */
/*  5.3.2     1/19/2022  KAT      Update for 840B#2 CV(Version update).                                                              */
/*                                                                                                                                   */
/*  * SK   = Satoshi Kasai, NTTD MSE                                                                                                 */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * KAT  = Katsushi Takahashi, NTTD MSE                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
