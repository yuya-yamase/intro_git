/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_BRK-CSTD-A0                                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRK_0_C_MAJOR                    (5)
#define ALERT_C_BRK_0_C_MINOR                    (1)
#define ALERT_C_BRK_0_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_C_BRK_0_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_BRK-CSTD-A0.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_BRK_0_NUM_DST                    (20U)

#define ALERT_C_BRK_0_EGRT_FLG_OFF               (0x00U)
#define ALERT_C_BRK_0_EGRT_FLG_ON                (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_c_brk_dly_tm_elpsd;
static U1      u1_s_alert_c_brk_run_flg;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertC_brk_0Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U1      u1_s_AlertC_brk_0RunSts(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_C_BRK_0_CRIT[ALERT_C_BRK_0_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000080U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x000000A0U,                                                           /* 02 UNKNOWN                                         */
    (U4)0x000000A1U,                                                           /* 03 UNKNOWN                                         */
    (U4)0x000000A2U,                                                           /* 04 UNKNOWN                                         */
    (U4)0x000000A3U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x000000A4U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x000000A8U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x000000B0U,                                                           /* 08 UNKNOWN                                         */
    (U4)0x000000B1U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x000000B2U,                                                           /* 10 UNKNOWN                                         */
    (U4)0x000000B3U,                                                           /* 11 LOW                                             */
    (U4)0x000000B4U,                                                           /* 12 UNKNOWN                                         */
    (U4)0x000000B8U,                                                           /* 13 UNKNOWN                                         */
    (U4)0x000000C0U,                                                           /* 14 UNKNOWN                                         */
    (U4)0x000000C1U,                                                           /* 15 UNKNOWN                                         */
    (U4)0x000000C2U,                                                           /* 16 UNKNOWN                                         */
    (U4)0x000000C3U,                                                           /* 17 TMODE                                           */
    (U4)0x000000C4U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x000000C8U                                                            /* 19 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_C_BRK_0_MASK[ALERT_C_BRK_0_NUM_DST] = {
    (U4)0x00000080U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x000000E0U,                                                           /* 01 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 02 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 03 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 04 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 05 UNKNOWN                                         */
    (U4)0x000000FCU,                                                           /* 06 UNKNOWN                                         */
    (U4)0x000000F8U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 08 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 09 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 10 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 11 LOW                                             */
    (U4)0x000000FCU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x000000F8U,                                                           /* 13 UNKNOWN                                         */
    (U4)0x000000CFU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x000000CFU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x000000CFU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x000000CFU,                                                           /* 17 TMODE                                           */
    (U4)0x000000CCU,                                                           /* 18 UNKNOWN                                         */
    (U4)0x000000C8U                                                            /* 19 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_C_BRK_0_DST[ALERT_C_BRK_0_NUM_DST] = {
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
    (U1)ALERT_REQ_C_BRK_0_LOW,                                                 /* 11 LOW                                             */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_C_BRK_0_TMODE,                                               /* 17 TMODE                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 19 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_C_BRK_0_MTRX[1] = {
    {
        &u4_s_AlertC_brk_0Srcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_BRK_0_MASK[0],                                          /* u4p_MASK                                           */
        &u4_sp_ALERT_C_BRK_0_CRIT[0],                                          /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_BRK_0_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_C_BRK_0_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertC_brk_0Init(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertC_brk_0Init(void)
{
    u4_s_alert_c_brk_dly_tm_elpsd = (U4)0U;
    u1_s_alert_c_brk_run_flg      = (U1)ALERT_C_BRK_0_EGRT_FLG_OFF;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_brkSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_brk_0Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U4 u4_s_ALERT_C_BRK_TIM_DLY         = ((U4)7100U / (U4)ALERT_MAIN_TICK);
    static const U2 u2_s_ALERT_C_BRK_TO_ZN11S17      = ((U2)1000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_BRK_ZN11S17_LSB_STS = (U1)2U;
    static const U1 u1_s_ALERT_C_BRK_SGNL_LSB_BVWRSW = (U1)1U;

    static const U4 u4_s_ALERT_C_BRK_BIT_EG_RT_ON    = (U4)0x00000010U;
    static const U4 u4_s_ALERT_C_BRK_BIT_DLY_CMP     = (U4)0x00000020U;
    static const U4 u4_s_ALERT_C_BRK_BIT_TMODE_ON    = (U4)0x00000040U;
    static const U4 u4_s_ALERT_C_BRK_BIT_IGN_ON      = (U4)0x00000080U;
    static const U4 u4_s_ALERT_C_BRK_BIT_MSK         = (U4)0x0000001FU;
    static const U4 u4_s_ALERT_C_BRK_BIT_MSK_SGNL    = (U4)0x00000013U;

    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_egrt_on;
    U1              u1_t_tmode_on;

    u1_t_egrt_on  = (U1)0U;
    u4_t_src_chk  = (U4)0U;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ZN11S17_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                     u2_s_ALERT_C_BRK_TO_ZN11S17) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_BRK_ZN11S17_LSB_STS);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BVWRSW_V, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BVWRSW, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl<< u1_s_ALERT_C_BRK_SGNL_LSB_BVWRSW);

    u1_t_egrt_on = u1_s_AlertC_brk_0RunSts();

    if(u1_t_egrt_on == (U1)ALERT_C_BRK_0_EGRT_FLG_ON){
        u4_t_src_chk |= u4_s_ALERT_C_BRK_BIT_EG_RT_ON;
    }

    if((u4_t_src_chk & u4_s_ALERT_C_BRK_BIT_MSK) != u4_s_ALERT_C_BRK_BIT_MSK_SGNL){
        u4_s_alert_c_brk_dly_tm_elpsd = (U4)0U;
    }
    else{
        if(u4_s_alert_c_brk_dly_tm_elpsd >= u4_s_ALERT_C_BRK_TIM_DLY){
            u4_s_alert_c_brk_dly_tm_elpsd = u4_s_ALERT_C_BRK_TIM_DLY;
            u4_t_src_chk |= u4_s_ALERT_C_BRK_BIT_DLY_CMP;
        }
        else{
            u4_s_alert_c_brk_dly_tm_elpsd++;
        }
    }

    u1_t_tmode_on    = u1_g_AlertCfgC_brk_0IsTmode();
    if(u1_t_tmode_on == (U1)TRUE){
        u4_t_src_chk |= u4_s_ALERT_C_BRK_BIT_TMODE_ON;
    }
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_C_BRK_BIT_IGN_ON;
    }

    return(u4_t_src_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_AlertC_brk_0RunSts(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertC_brk_0RunSts(void)
{
    static const U2 u2_s_ALERT_C_BRK_THRSH_400RPM = (U2)400U;
    static const U2 u2_s_ALERT_C_BRK_THRSH_200RPM = (U2)200U;

    U1 u1_t_run_flg;
    U2 u2_t_egrt_val;

    u1_t_run_flg  = (U1)ALERT_C_BRK_0_EGRT_FLG_OFF;

    u2_t_egrt_val = u2_g_AlertCfgC_brk_0EngineRPMVal();

    if(u2_t_egrt_val >= u2_s_ALERT_C_BRK_THRSH_400RPM){
        u1_t_run_flg = (U1)ALERT_C_BRK_0_EGRT_FLG_ON;
    }
    else if((u2_t_egrt_val            >=  u2_s_ALERT_C_BRK_THRSH_200RPM)&&
            (u1_s_alert_c_brk_run_flg == (U1)ALERT_C_BRK_0_EGRT_FLG_ON)){
        u1_t_run_flg = (U1)ALERT_C_BRK_0_EGRT_FLG_ON;
    }
    else{
        /* Do nothing */
    }

    u1_s_alert_c_brk_run_flg = u1_t_run_flg;

    return(u1_s_alert_c_brk_run_flg);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0    12/07/2023  AA       New.                                                                                               */
/*  5.1.0    03/14/2024  AA       Revised LSB for timer                                                                              */
/*                                                                                                                                   */
/*  * AA   = Anna Asuncion, DT                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
