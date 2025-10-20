/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert D_CVTOIL                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_CVTOIL_C_MAJOR                   (5)
#define ALERT_D_CVTOIL_C_MINOR                   (1)
#define ALERT_D_CVTOIL_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_D_CVTOIL_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_D_CVTOIL.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_CVTOIL_NUM_DST                   (32U)

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
static U4      u4_s_AlertD_cvtoilSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertD_cvtoilRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_D_CVTOIL_DST[ALERT_D_CVTOIL_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_CVTOIL_TEMPH,                                              /* 01 TEMPH                                           */
    (U1)ALERT_REQ_D_CVTOIL_MALFUNC,                                            /* 02 MALFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_D_CVTOIL_ON,                                                 /* 04 ON                                              */
    (U1)ALERT_REQ_D_CVTOIL_ON_TEMPH,                                           /* 05 ON_TEMPH                                        */
    (U1)ALERT_REQ_D_CVTOIL_ON_MALFUNC,                                         /* 06 ON_MALFUNC                                      */
    (U1)ALERT_REQ_D_CVTOIL_ON,                                                 /* 07 ON                                              */
    (U1)ALERT_REQ_D_CVTOIL_FLASH,                                              /* 08 FLASH                                           */
    (U1)ALERT_REQ_D_CVTOIL_FLASH_TEMPH,                                        /* 09 FLASH_TEMPH                                     */
    (U1)ALERT_REQ_D_CVTOIL_FLASH_MALFUNC,                                      /* 10 FLASH_MALFUNC                                   */
    (U1)ALERT_REQ_D_CVTOIL_FLASH,                                              /* 11 FLASH                                           */
    (U1)ALERT_REQ_D_CVTOIL_ON,                                                 /* 12 ON                                              */
    (U1)ALERT_REQ_D_CVTOIL_ON_TEMPH,                                           /* 13 ON_TEMPH                                        */
    (U1)ALERT_REQ_D_CVTOIL_ON_MALFUNC,                                         /* 14 ON_MALFUNC                                      */
    (U1)ALERT_REQ_D_CVTOIL_ON,                                                 /* 15 ON                                              */
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
const ST_ALERT_MTRX st_gp_ALERT_D_CVTOIL_MTRX[1] = {
    {
        &u4_s_AlertD_cvtoilSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertD_cvtoilRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_CVTOIL_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_D_CVTOIL_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_cvtoilSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_cvtoilSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U1 u1_s_ALERT_D_CVTOIL_LSB_MSGSTS   = (U1)4U;
#ifdef ComConf_ComSignal_B_OILWTT
    static const U1 u1_s_ALERT_D_CVTOIL_LSB_B_OILWTT = (U1)2U;
#endif /* ComConf_ComSignal_B_OILWTT */
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

#ifdef OXCAN_PDU_RX_CAN_ECT1G92
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECT1G92,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECT1S93,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#endif /* OXCAN_PDU_RX_CAN_ECT1G92 */

    u1_t_sgnl     = (U1)0U;
#ifdef ComConf_ComSignal_B_OILWMI
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_OILWMI, &u1_t_sgnl);
#endif /* ComConf_ComSignal_B_OILWMI */
    u4_t_src_chk  = (U4)u1_t_sgnl;

#ifdef ComConf_ComSignal_B_OILWTT
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_OILWTT, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_D_CVTOIL_LSB_B_OILWTT);
#endif /* ComConf_ComSignal_B_OILWTT */

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_D_CVTOIL_LSB_MSGSTS);

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertD_cvtoilRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertD_cvtoilRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_D_CVTOIL_RW_CRT = (U2)((U2)1U << ALERT_REQ_D_CVTOIL_FLASH        )
                                               | (U2)((U2)1U << ALERT_REQ_D_CVTOIL_MALFUNC      )
                                               | (U2)((U2)1U << ALERT_REQ_D_CVTOIL_ON_MALFUNC   )
                                               | (U2)((U2)1U << ALERT_REQ_D_CVTOIL_FLASH_TEMPH  )
                                               | (U2)((U2)1U << ALERT_REQ_D_CVTOIL_FLASH_MALFUNC);               /* ATSW             */
    static const U1 u1_s_ALERT_D_CVTOIL_RW_MSK = (U1)0x0FU;
    U1              u1_t_sgnl;
    U2              u2_t_rw;

    u2_t_rw = ((U2)1U << (u1_a_DST & u1_s_ALERT_D_CVTOIL_RW_MSK));
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN)       != (U1)0U) &&
       ((u2_t_rw  & u2_s_ALERT_D_CVTOIL_RW_CRT) != (U2)0U)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ATSW, &u1_t_sgnl);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     2/27/2020  SM       New.                                                                                               */
/*  5.1.0    12/ 8/2020  TN       Change The processing order of the CAN signal.                                                     */
/*                                                                                                                                   */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
