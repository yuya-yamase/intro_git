/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_PKSB                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_PKSB_C_MAJOR                     (5)
#define ALERT_S_PKSB_C_MINOR                     (3)
#define ALERT_S_PKSB_C_PATCH                     (0)

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
#if (ALERT_S_PKSB_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_PKSB.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_PKSB_TT_NUM_DST                  (16U)
#define ALERT_S_PKSB_PD_NUM_DST                  (9U)

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
static U4      u4_s_AlertS_pksbTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_pksbPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertS_pksbPdRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_PKSB_TT_DST[ALERT_S_PKSB_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_PKSB_TT_ON,                                                /* 01 ON                                              */
    (U1)ALERT_REQ_S_PKSB_TT_FLASH,                                             /* 02 FLASH                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_S_PKSB_TT_ON,                                                /* 08 ON                                              */
    (U1)ALERT_REQ_S_PKSB_TT_ON,                                                /* 09 ON                                              */
    (U1)ALERT_REQ_S_PKSB_TT_ON,                                                /* 10 ON                                              */
    (U1)ALERT_REQ_S_PKSB_TT_ON,                                                /* 11 ON                                              */
    (U1)ALERT_REQ_S_PKSB_TT_ON,                                                /* 12 ON                                              */
    (U1)ALERT_REQ_S_PKSB_TT_ON,                                                /* 13 ON                                              */
    (U1)ALERT_REQ_S_PKSB_TT_ON,                                                /* 14 ON                                              */
    (U1)ALERT_REQ_S_PKSB_TT_ON                                                 /* 15 ON                                              */
};
static const U4  u4_sp_ALERT_S_PKSB_PD_CRIT[ALERT_S_PKSB_PD_NUM_DST] = {
    (U4)0x00000001U,                                                           /* 00 SYSWRKNG1                                       */
    (U4)0x00000002U,                                                           /* 01 SYSWRKNG2                                       */
    (U4)0x00000003U,                                                           /* 02 SYSWRKNG3                                       */
    (U4)0x00000004U,                                                           /* 03 SYSWRKNG4                                       */
    (U4)0x00000005U,                                                           /* 04 RW                                              */
    (U4)0x00000011U,                                                           /* 05 SYSWRKNG5                                       */
    (U4)0x00010000U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x00020000U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x00030000U                                                            /* 08 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_S_PKSB_PD_MASK[ALERT_S_PKSB_PD_NUM_DST] = {
    (U4)0x0003FFFFU,                                                           /* 00 SYSWRKNG1                                       */
    (U4)0x0003FFFFU,                                                           /* 01 SYSWRKNG2                                       */
    (U4)0x0003FFFFU,                                                           /* 02 SYSWRKNG3                                       */
    (U4)0x0003FFFFU,                                                           /* 03 SYSWRKNG4                                       */
    (U4)0x0003FFFDU,                                                           /* 04 RW                                              */
    (U4)0x0003FFFFU,                                                           /* 05 SYSWRKNG5                                       */
    (U4)0x00030000U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x00030000U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x00030000U                                                            /* 08 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_S_PKSB_PD_DST[ALERT_S_PKSB_PD_NUM_DST] = {
    (U1)ALERT_REQ_S_PKSB_PD_SYSWRKNG1,                                         /* 00 SYSWRKNG1                                       */
    (U1)ALERT_REQ_S_PKSB_PD_SYSWRKNG2,                                         /* 01 SYSWRKNG2                                       */
    (U1)ALERT_REQ_S_PKSB_PD_SYSWRKNG3,                                         /* 02 SYSWRKNG3                                       */
    (U1)ALERT_REQ_S_PKSB_PD_SYSWRKNG4,                                         /* 03 SYSWRKNG4                                       */
    (U1)ALERT_REQ_S_PKSB_PD_RW,                                                /* 04 RW                                              */
    (U1)ALERT_REQ_S_PKSB_PD_SYSWRKNG5,                                         /* 05 SYSWRKNG5                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 08 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_PKSB_MTRX[2] = {
    {
        &u4_s_AlertS_pksbTtSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_PKSB_TT_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_S_PKSB_TT_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_pksbPdSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertS_pksbPdRwTx,                                               /* fp_vd_XDST                                         */

        &u4_sp_ALERT_S_PKSB_PD_MASK[0],                                        /* u4p_MASK                                           */
        &u4_sp_ALERT_S_PKSB_PD_CRIT[0],                                        /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_PKSB_PD_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_S_PKSB_PD_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_pksbTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_pksbTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_CSR1S04_RXCH0) && defined(ComConf_ComSignal_ICSLAMP)
    static const U2 u2_s_ALERT_ICSLAMP_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_ICSLAMP_LSB_MSGSTS = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_ICSLAMP_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ICSLAMP, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_ICSLAMP_LSB_MSGSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_CSR1S04_RXCH0) && defined(ComConf_ComSignal_ICSLAMP) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_pksbPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_pksbPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_CSR1S04_RXCH0) && defined(ComConf_ComSignal_ICSINFO)
    static const U2 u2_s_ALERT_ICSINFO_TO_THRESH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_ICSINFO_LSB_MSGSTS = (U1)16U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U2              u2_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_ICSINFO_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u2_t_sgnl     = (U2)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ICSINFO, &u2_t_sgnl);
    u4_t_src_chk  = (U4)u2_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_ICSINFO_LSB_MSGSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_CSR1S04_RXCH0) && defined(ComConf_ComSignal_ICSINFO) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertS_pksbPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertS_pksbPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                    ) &&
        (u1_a_DST                         == (U1)ALERT_REQ_S_PKSB_PD_RW)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_ASSW, &u1_t_sgnl);    /* COM Tx STUB delete */
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
/*  5.0.0     3/23/2020  SK       New.                                                                                               */
/*  5.1.0     9/07/2020  TI       Update timeout status for PD.                                                                      */
/*  5.1.1     3/17/2021  MO       Update for 840B CV(Version update).                                                                */
/*  5.2.0    10/26/2021  KT       Update for 840B 1A(Version update).                                                                */
/*  5.3.0    11/17/2023  KH       Update for 19PFv3 CV(Version update).                                                              */
/*                                                                                                                                   */
/*  * SK   = Satoshi Kasai, NTTD MSE                                                                                                 */
/*  * TI   = Takuro Iwanaga, NTTD MSE                                                                                                */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
