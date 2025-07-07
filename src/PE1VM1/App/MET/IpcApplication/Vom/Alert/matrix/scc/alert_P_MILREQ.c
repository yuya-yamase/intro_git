/* 5.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_MILREQ                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_MILREQ_C_MAJOR                   (5)
#define ALERT_P_MILREQ_C_MINOR                   (1)
#define ALERT_P_MILREQ_C_PATCH                   (0)

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
#if (ALERT_P_MILREQ_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_MILREQ.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_MILREQ_NUM_DST                   (64U)

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
static U4      u4_s_AlertP_milreqSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertP_milreqRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_MILREQ_DST[ALERT_P_MILREQ_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_MILREQ_ON,                                                 /* 01 ON                                              */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 02 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_FLASH_REDUCE,                                       /* 03 FLASH_REDUCE                                    */
    (U1)ALERT_REQ_P_MILREQ_FLASH_4HZ,                                          /* 04 FLASH_4HZ                                       */
    (U1)ALERT_REQ_P_MILREQ_FLASH_READY,                                        /* 05 FLASH_READY                                     */
    (U1)ALERT_REQ_P_MILREQ_FLASH_EUREADY,                                      /* 06 FLASH_EUREADY                                   */
    (U1)ALERT_REQ_P_MILREQ_ON,                                                 /* 07 ON                                              */
    (U1)ALERT_REQ_P_MILREQ_ON,                                                 /* 08 ON                                              */
    (U1)ALERT_REQ_P_MILREQ_ON,                                                 /* 09 ON                                              */
    (U1)ALERT_REQ_P_MILREQ_ON,                                                 /* 10 ON                                              */
    (U1)ALERT_REQ_P_MILREQ_ON,                                                 /* 11 ON                                              */
    (U1)ALERT_REQ_P_MILREQ_ON,                                                 /* 12 ON                                              */
    (U1)ALERT_REQ_P_MILREQ_ON,                                                 /* 13 ON                                              */
    (U1)ALERT_REQ_P_MILREQ_ON,                                                 /* 14 ON                                              */
    (U1)ALERT_REQ_P_MILREQ_ON,                                                 /* 15 ON                                              */
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
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 32 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 33 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 34 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 35 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 36 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 37 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 38 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 39 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 40 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 41 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 42 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 43 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 44 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 45 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 46 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 47 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 48 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 49 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 50 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 51 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 52 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 53 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 54 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 55 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 56 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 57 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 58 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 59 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 60 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 61 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW,                                              /* 62 ON_RW                                           */
    (U1)ALERT_REQ_P_MILREQ_ON_RW                                               /* 63 ON_RW                                           */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_MILREQ_MTRX[1] = {
    {
        &u4_s_AlertP_milreqSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_milreqRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_MILREQ_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_P_MILREQ_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_milreqSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_milreqSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_P_MILREQ_TO_THRESH  = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_P_MILREQ_LSB_MSGSTS = (U1)4U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

#ifdef OXCAN_PDU_RX_CAN_ENG1F07
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_PDU_RX_CAN_ENG1F07,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_P_MILREQ_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ENG1G17_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_P_MILREQ_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#endif /* OXCAN_PDU_RX_CAN_ENG1F07 */

    u1_t_sgnl     = (U1)0U;
#if 0   /* BEV BSW provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_MILREQ, &u1_t_sgnl);
#endif
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_P_MILREQ_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertP_milreqRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_milreqRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                       ) &&
        (u1_a_DST                         == (U1)ALERT_REQ_P_MILREQ_ON_RW)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_ENGW, &u1_t_sgnl);    /* COM Tx STUB delete */
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
/*  5.0.0     3/11/2020  SM       New.                                                                                               */
/*  5.1.0     3/27/2024  AA       Added IGON checking for remote warning                                                             */
/*                                                                                                                                   */
/*  * SM   = Shingo Miyamoto, NTTD MSE                                                                                               */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
