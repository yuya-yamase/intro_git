/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_OILLVG                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_OILLVG_C_MAJOR                   (5)
#define ALERT_P_OILLVG_C_MINOR                   (1)
#define ALERT_P_OILLVG_C_PATCH                   (0)

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
#if (ALERT_P_OILLVG_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_OILLVG.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_OILLVG_NUM_DST                   (32U)

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
static U4      u4_s_AlertP_oillvgSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertP_oillvgRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_OILLVG_DST[ALERT_P_OILLVG_NUM_DST] = {
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
    (U1)ALERT_REQ_P_OILLVG_REDUCE,                                             /* 11 REDUCE                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILLVG_MALFUNC,                                            /* 14 MALFUNC                                         */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_OILLVG_MTRX[1] = {
    {
        &u4_s_AlertP_oillvgSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_oillvgRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_OILLVG_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_P_OILLVG_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_oillvgSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_oillvgSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_P_OILLVG_LSB_MSGSTS = (U1)4U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_EOILVL, &u1_t_sgnl);
#endif
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_P_OILLVG_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void      vd_s_AlertP_oillvgRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_oillvgRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U4 u4_s_ALERT_P_OILLVG_TIM_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
    U1              u1_t_sgnl_olsw;
    U1              u1_t_sgnl_olhw;

    if (((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                         ) &&
        (u4_a_IGN_TM                       >= u4_s_ALERT_P_OILLVG_TIM_RW_ENBL) &&
        (u1_a_DST                          == (U1)ALERT_REQ_P_OILLVG_MALFUNC )) {
        u1_t_sgnl_olsw = (U1)ALERT_RW_SGNL_ON;
    }
    else {
        u1_t_sgnl_olsw = (U1)ALERT_RW_SGNL_OFF;
    }

    if (((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                         ) &&
        (u4_a_IGN_TM                       >= u4_s_ALERT_P_OILLVG_TIM_RW_ENBL) &&
        (u1_a_DST                          == (U1)ALERT_REQ_P_OILLVG_REDUCE  )) {
        u1_t_sgnl_olhw = (U1)ALERT_RW_SGNL_ON;
    }
    else {
        u1_t_sgnl_olhw = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_OLSW, &u1_t_sgnl_olsw);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_OLHW, &u1_t_sgnl_olhw);    /* COM Tx STUB delete */
#endif
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0    12/19/2023  KH       New.                                                                                               */
/*  5.1.0     3/26/2024  AA       Added remote warning of OLSW and OLHW                                                              */
/*                                                                                                                                   */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
