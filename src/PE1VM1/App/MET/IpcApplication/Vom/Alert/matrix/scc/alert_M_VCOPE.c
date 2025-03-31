/* 5.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert M_VCOPE                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_M_VCOPE_C_MAJOR                    (5)
#define ALERT_M_VCOPE_C_MINOR                    (2)
#define ALERT_M_VCOPE_C_PATCH                    (0)

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
#if (ALERT_M_VCOPE_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_M_VCOPE.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_M_VCOPE_NUM_DST                    (20U)

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
static U4      u4_s_AlertM_vcopeSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_M_VCOPE_CRIT[ALERT_M_VCOPE_NUM_DST] = {
    (U4)0x00000009U,                                                           /* 00 WT_STP                                          */
    (U4)0x00000021U,                                                           /* 01 WT_STP                                          */
    (U4)0x00000081U,                                                           /* 02 WT_STP                                          */
    (U4)0x00000006U,                                                           /* 03 WT_STP                                          */
    (U4)0x00000024U,                                                           /* 04 WT_STP                                          */
    (U4)0x00000084U,                                                           /* 05 WT_STP                                          */
    (U4)0x00000012U,                                                           /* 06 WT_STP                                          */
    (U4)0x00000018U,                                                           /* 07 WT_STP                                          */
    (U4)0x00000090U,                                                           /* 08 WT_STP                                          */
    (U4)0x00000042U,                                                           /* 09 WT_STP                                          */
    (U4)0x00000048U,                                                           /* 10 WT_STP                                          */
    (U4)0x00000060U,                                                           /* 11 WT_STP                                          */
    (U4)0x00000001U,                                                           /* 12 WAIT                                            */
    (U4)0x00000004U,                                                           /* 13 WAIT                                            */
    (U4)0x00000010U,                                                           /* 14 WAIT                                            */
    (U4)0x00000040U,                                                           /* 15 WAIT                                            */
    (U4)0x00000002U,                                                           /* 16 STOP                                            */
    (U4)0x00000008U,                                                           /* 17 STOP                                            */
    (U4)0x00000020U,                                                           /* 18 STOP                                            */
    (U4)0x00000080U                                                            /* 19 STOP                                            */
};
static const U4  u4_sp_ALERT_M_VCOPE_MASK[ALERT_M_VCOPE_NUM_DST] = {
    (U4)0x0000030FU,                                                           /* 00 WT_STP                                          */
    (U4)0x00000333U,                                                           /* 01 WT_STP                                          */
    (U4)0x000003C3U,                                                           /* 02 WT_STP                                          */
    (U4)0x0000030FU,                                                           /* 03 WT_STP                                          */
    (U4)0x0000033CU,                                                           /* 04 WT_STP                                          */
    (U4)0x000003CCU,                                                           /* 05 WT_STP                                          */
    (U4)0x00000333U,                                                           /* 06 WT_STP                                          */
    (U4)0x0000033CU,                                                           /* 07 WT_STP                                          */
    (U4)0x000003F0U,                                                           /* 08 WT_STP                                          */
    (U4)0x000003C3U,                                                           /* 09 WT_STP                                          */
    (U4)0x000003CCU,                                                           /* 10 WT_STP                                          */
    (U4)0x000003F0U,                                                           /* 11 WT_STP                                          */
    (U4)0x00000303U,                                                           /* 12 WAIT                                            */
    (U4)0x0000030CU,                                                           /* 13 WAIT                                            */
    (U4)0x00000330U,                                                           /* 14 WAIT                                            */
    (U4)0x000003C0U,                                                           /* 15 WAIT                                            */
    (U4)0x00000303U,                                                           /* 16 STOP                                            */
    (U4)0x0000030CU,                                                           /* 17 STOP                                            */
    (U4)0x00000330U,                                                           /* 18 STOP                                            */
    (U4)0x000003C0U                                                            /* 19 STOP                                            */
};
static const U1  u1_sp_ALERT_M_VCOPE_DST[ALERT_M_VCOPE_NUM_DST] = {
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 00 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 01 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 02 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 03 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 04 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 05 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 06 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 07 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 08 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 09 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 10 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WT_STP,                                              /* 11 WT_STP                                          */
    (U1)ALERT_REQ_M_VCOPE_WAIT,                                                /* 12 WAIT                                            */
    (U1)ALERT_REQ_M_VCOPE_WAIT,                                                /* 13 WAIT                                            */
    (U1)ALERT_REQ_M_VCOPE_WAIT,                                                /* 14 WAIT                                            */
    (U1)ALERT_REQ_M_VCOPE_WAIT,                                                /* 15 WAIT                                            */
    (U1)ALERT_REQ_M_VCOPE_STOP,                                                /* 16 STOP                                            */
    (U1)ALERT_REQ_M_VCOPE_STOP,                                                /* 17 STOP                                            */
    (U1)ALERT_REQ_M_VCOPE_STOP,                                                /* 18 STOP                                            */
    (U1)ALERT_REQ_M_VCOPE_STOP                                                 /* 19 STOP                                            */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_M_VCOPE_MTRX[1] = {
    {
        &u4_s_AlertM_vcopeSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_M_VCOPE_MASK[0],                                          /* u4p_MASK                                           */
        &u4_sp_ALERT_M_VCOPE_CRIT[0],                                          /* u4p_CRIT                                           */

        &u1_sp_ALERT_M_VCOPE_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_M_VCOPE_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertM_vcopeSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertM_vcopeSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_M_VCOPE_TO_THRESH    = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_M_VCOPE_LSB_MSGSTS   = (U1)8U;
#ifdef ComConf_ComSignal_LTAVRAPR
    static const U1 u1_s_ALERT_M_VCOPE_LSB_LTAVRAPR = (U1)6U;
#endif /* ComConf_ComSignal_LTAVRAPR */
#ifdef ComConf_ComSignal_ISAVRAPR
    static const U1 u1_s_ALERT_M_VCOPE_LSB_ISAVRAPR = (U1)4U;
#endif /* ComConf_ComSignal_ISAVRAPR */
#ifdef ComConf_ComSignal_CCSVRAPR
    static const U1 u1_s_ALERT_M_VCOPE_LSB_CCSVRAPR = (U1)2U;
#endif /* ComConf_ComSignal_CCSVRAPR */
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
#if (defined(ComConf_ComSignal_LTAVRAPR) || defined(ComConf_ComSignal_ISAVRAPR)) || (defined(ComConf_ComSignal_CCSVRAPR) || defined(ComConf_ComSignal_ACCVRAPR))
    U1              u1_t_sgnl;
#endif /* (defined(ComConf_ComSignal_LTAVRAPR) || defined(ComConf_ComSignal_ISAVRAPR)) || (defined(ComConf_ComSignal_CCSVRAPR) || defined(ComConf_ComSignal_ACCVRAPR)) */

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_FCM1S58_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_M_VCOPE_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_M_VCOPE_LSB_MSGSTS);

#ifdef ComConf_ComSignal_LTAVRAPR
    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_LTAVRAPR, &u1_t_sgnl);
#endif
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_M_VCOPE_LSB_LTAVRAPR);
#endif /* ComConf_ComSignal_LTAVRAPR */

#ifdef ComConf_ComSignal_ISAVRAPR
    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_ISAVRAPR, &u1_t_sgnl);
#endif
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_M_VCOPE_LSB_ISAVRAPR);
#endif /* ComConf_ComSignal_ISAVRAPR */

#ifdef ComConf_ComSignal_CCSVRAPR
    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_CCSVRAPR, &u1_t_sgnl);
#endif
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_M_VCOPE_LSB_CCSVRAPR);
#endif /* ComConf_ComSignal_CCSVRAPR */

#ifdef ComConf_ComSignal_ACCVRAPR
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCVRAPR, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;
#endif /* ComConf_ComSignal_ACCVRAPR */

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
/*  5.0.0     3/26/2021  SM       New.                                                                                               */
/*  5.1.0     7/ 5/2021  MY       Delete signals.                                                                                    */
/*  5.2.0    11/25/2021  MY       Update for 900B 1A1H(Version update).                                                              */
/*                                                                                                                                   */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
