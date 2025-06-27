/* 5.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_BOS                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_BOS_C_MAJOR                      (5)
#define ALERT_S_BOS_C_MINOR                      (1)
#define ALERT_S_BOS_C_PATCH                      (1)

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
#if (ALERT_S_BOS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_BOS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_BOS_NUM_DST                      (12U)

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
static U4      u4_s_AlertS_bosSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertS_bosRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_S_BOS_CRIT[ALERT_S_BOS_NUM_DST] = {
    (U4)0x00000009U,                                                           /* 00 ON_MSG2                                         */
    (U4)0x0000000BU,                                                           /* 01 FLSH_MSG2                                       */
    (U4)0x0000000CU,                                                           /* 02 ON_MSG2                                         */
    (U4)0x00000029U,                                                           /* 03 ON_MSG3                                         */
    (U4)0x0000002BU,                                                           /* 04 FLSH_MSG3                                       */
    (U4)0x0000002CU,                                                           /* 05 ON_MSG3                                         */
    (U4)0x00000001U,                                                           /* 06 ON                                              */
    (U4)0x00000003U,                                                           /* 07 FLSH                                            */
    (U4)0x00000004U,                                                           /* 08 ON                                              */
    (U4)0x00000008U,                                                           /* 09 MSG2                                            */
    (U4)0x00000028U,                                                           /* 10 MSG3                                            */
    (U4)0x00000080U                                                            /* 11 FLSH_MSG3                                       */
};
static const U4  u4_sp_ALERT_S_BOS_MASK[ALERT_S_BOS_NUM_DST] = {
    (U4)0x000000FFU,                                                           /* 00 ON_MSG2                                         */
    (U4)0x000000FFU,                                                           /* 01 FLSH_MSG2                                       */
    (U4)0x000000FFU,                                                           /* 02 ON_MSG2                                         */
    (U4)0x000000FFU,                                                           /* 03 ON_MSG3                                         */
    (U4)0x000000FFU,                                                           /* 04 FLSH_MSG3                                       */
    (U4)0x000000FFU,                                                           /* 05 ON_MSG3                                         */
    (U4)0x000000C7U,                                                           /* 06 ON                                              */
    (U4)0x000000C7U,                                                           /* 07 FLSH                                            */
    (U4)0x000000C7U,                                                           /* 08 ON                                              */
    (U4)0x000000F8U,                                                           /* 09 MSG2                                            */
    (U4)0x000000F8U,                                                           /* 10 MSG3                                            */
    (U4)0x00000080U                                                            /* 11 FLSH_MSG3                                       */
};
static const U1  u1_sp_ALERT_S_BOS_DST[ALERT_S_BOS_NUM_DST] = {
    (U1)ALERT_REQ_S_BOS_ON_MSG2,                                               /* 00 ON_MSG2                                         */
    (U1)ALERT_REQ_S_BOS_FLSH_MSG2,                                             /* 01 FLSH_MSG2                                       */
    (U1)ALERT_REQ_S_BOS_ON_MSG2,                                               /* 02 ON_MSG2                                         */
    (U1)ALERT_REQ_S_BOS_ON_MSG3,                                               /* 03 ON_MSG3                                         */
    (U1)ALERT_REQ_S_BOS_FLSH_MSG3,                                             /* 04 FLSH_MSG3                                       */
    (U1)ALERT_REQ_S_BOS_ON_MSG3,                                               /* 05 ON_MSG3                                         */
    (U1)ALERT_REQ_S_BOS_ON,                                                    /* 06 ON                                              */
    (U1)ALERT_REQ_S_BOS_FLSH,                                                  /* 07 FLSH                                            */
    (U1)ALERT_REQ_S_BOS_ON,                                                    /* 08 ON                                              */
    (U1)ALERT_REQ_S_BOS_MSG2,                                                  /* 09 MSG2                                            */
    (U1)ALERT_REQ_S_BOS_MSG3,                                                  /* 10 MSG3                                            */
    (U1)ALERT_REQ_S_BOS_FLSH_MSG3                                              /* 11 FLSH_MSG3                                       */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_BOS_MTRX[1] = {
    {
        &u4_s_AlertS_bosSrcchk,                                                /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertS_bosRwTx,                                                  /* fp_vd_XDST                                         */

        &u4_sp_ALERT_S_BOS_MASK[0],                                            /* u4p_MASK                                           */
        &u4_sp_ALERT_S_BOS_CRIT[0],                                            /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_BOS_DST[0],                                             /* u1p_DST                                            */
        (U2)ALERT_S_BOS_NUM_DST,                                               /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_bosSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_bosSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_ENG1G92_CH0)
    static const U2 u2_s_ALERT_S_BOS_TO_TRSH_ENG1G92 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#elif defined(OXCAN_PDU_RX_CAN_ENG1S92)
    static const U2 u2_s_ALERT_S_BOS_TO_TRSH_ENG1S92 = ((U2)5200U / (U2)OXCAN_MAIN_TICK);
#endif /* defined(OXCAN_RXD_PDU_CAN_ENG1G92_CH0) */
#ifdef ComConf_ComSignal_BOSMINF
    static const U1 u1_s_ALERT_S_BOS_LSB_BOSMINF     = (U1)3U;
#endif /* ComConf_ComSignal_BOSMINF */
    static const U1 u1_s_ALERT_S_BOS_LSB_MSGSTS      = (U1)6U;
    U1              u1_t_msgsts;
#if defined(ComConf_ComSignal_BOSLAMP) || defined(ComConf_ComSignal_BOSMINF)
    U1              u1_t_sgnl;
#endif /* defined(ComConf_ComSignal_BOSLAMP) || defined(ComConf_ComSignal_BOSMINF) */
    U4              u4_t_src_chk;

#if defined(OXCAN_RXD_PDU_CAN_ENG1G92_CH0)
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ENG1G92_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_BOS_TO_TRSH_ENG1G92) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#elif defined(OXCAN_PDU_RX_CAN_ENG1S92)
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_PDU_RX_CAN_ENG1S92,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_BOS_TO_TRSH_ENG1S92) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = (U1)0U;
#endif /* defined(OXCAN_RXD_PDU_CAN_ENG1G92_CH0) */

    u4_t_src_chk = ((U4)u1_t_msgsts << u1_s_ALERT_S_BOS_LSB_MSGSTS);

#if defined(ComConf_ComSignal_BOSLAMP) || defined(ComConf_ComSignal_BOSMINF)
    u1_t_sgnl     = (U1)0U;
#endif /* defined(ComConf_ComSignal_BOSLAMP) || defined(ComConf_ComSignal_BOSMINF) */

#ifdef ComConf_ComSignal_BOSLAMP
    (void)Com_ReceiveSignal(ComConf_ComSignal_BOSLAMP, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;
#endif /* ComConf_ComSignal_BOSLAMP */

#ifdef ComConf_ComSignal_BOSMINF
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BOSMINF, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_S_BOS_LSB_BOSMINF);
#endif /* ComConf_ComSignal_BOSMINF */

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertS_bosRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertS_bosRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U2 u2_s_ALERT_S_BOS_RW_CRT = ((U2)((U2)1U << ALERT_REQ_S_BOS_ON_MSG3  )
                                            |  (U2)((U2)1U << ALERT_REQ_S_BOS_FLSH     )
                                            |  (U2)((U2)1U << ALERT_REQ_S_BOS_FLSH_MSG2)
                                            |  (U2)((U2)1U << ALERT_REQ_S_BOS_FLSH_MSG3)
                                            |  (U2)((U2)1U << ALERT_REQ_S_BOS_MSG3     ));            /* BOSW                        */
    static const U1 u1_s_ALERT_S_BOS_RW_MSK = (U1)0x0FU;

    U1              u1_t_sgnl;
    U2              u2_t_rw;

    u2_t_rw = ((U2)1U << (u1_a_DST & u1_s_ALERT_S_BOS_RW_MSK));
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN   ) != (U1)0U) &&
       ((u2_t_rw  & u2_s_ALERT_S_BOS_RW_CRT) != (U2)0U)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_BOSW, &u1_t_sgnl);    /* COM Tx STUB delete */
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
/*  5.0.0     4/ 1/2020  KH       New.                                                                                               */
/*  5.1.0     8/31/2020  KH       Update for 800B CV-R.                                                                              */
/*  5.1.1     2/16/2023  MY       Change compile switch for ENG1G92 / ENG1S92.                                                       */
/*                                                                                                                                   */
/*  * KH   = Koji Hattori, NTTD MSE                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
