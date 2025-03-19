/* 5.3.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_UNIOVE                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_UNIOVE_C_MAJOR                   (5)
#define ALERT_H_UNIOVE_C_MINOR                   (3)
#define ALERT_H_UNIOVE_C_PATCH                   (2)

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
#if (ALERT_H_UNIOVE_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_UNIOVE.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_UNIOVE_TT_BC_NUM_DST             (64U)
#define ALERT_H_UNIOVE_PD_NUM_DST                (5U)

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
static U4      u4_s_AlertH_unioveTtBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_uniovePdSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertH_unioveTtBcRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_UNIOVE_TT_BC_DST[ALERT_H_UNIOVE_TT_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_RW,                                           /* 01 RW                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_MALFUNC,                                      /* 08 MALFUNC                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_MALFUNC,                                      /* 09 MALFUNC                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_MALFUNC,                                      /* 10 MALFUNC                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_MALFUNC,                                      /* 11 MALFUNC                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_MALFUNC,                                      /* 12 MALFUNC                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_MALFUNC,                                      /* 13 MALFUNC                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_MALFUNC,                                      /* 14 MALFUNC                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_MALFUNC,                                      /* 15 MALFUNC                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_PRMCHK,                                       /* 16 PRMCHK                                          */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_PRM_RW,                                       /* 17 PRM_RW                                          */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_PRMCHK,                                       /* 18 PRMCHK                                          */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_PRMCHK,                                       /* 19 PRMCHK                                          */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_PRMCHK,                                       /* 20 PRMCHK                                          */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_PRMCHK,                                       /* 21 PRMCHK                                          */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_PRMCHK,                                       /* 22 PRMCHK                                          */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_PRMCHK,                                       /* 23 PRMCHK                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_RW,                                           /* 25 RW                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_RW,                                           /* 33 RW                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_RW,                                           /* 41 RW                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 47 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_RW,                                           /* 49 RW                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 55 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_H_UNIOVE_TT_BC_RW,                                           /* 57 RW                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 58 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 59 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 60 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 61 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 62 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 63 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_H_UNIOVE_PD_CRIT[ALERT_H_UNIOVE_PD_NUM_DST] = {
    (U4)0x00000001U,                                                           /* 00 HVSYSOVHT                                       */
    (U4)0x00000019U,                                                           /* 01 HVSYSOVHT                                       */
    (U4)0x00000021U,                                                           /* 02 HVSYSOVHT                                       */
    (U4)0x00000039U,                                                           /* 03 FCVSYSOVHT                                      */
    (U4)0x000000F9U                                                            /* 04 HVSYSOVHT                                       */
};
static const U4  u4_sp_ALERT_H_UNIOVE_PD_MASK[ALERT_H_UNIOVE_PD_NUM_DST] = {
    (U4)0x000000FFU,                                                           /* 00 HVSYSOVHT                                       */
    (U4)0x000000FFU,                                                           /* 01 HVSYSOVHT                                       */
    (U4)0x000000EFU,                                                           /* 02 HVSYSOVHT                                       */
    (U4)0x000000FFU,                                                           /* 03 FCVSYSOVHT                                      */
    (U4)0x000000FFU                                                            /* 04 HVSYSOVHT                                       */
};
static const U1  u1_sp_ALERT_H_UNIOVE_PD_DST[ALERT_H_UNIOVE_PD_NUM_DST] = {
    (U1)ALERT_REQ_H_UNIOVE_PD_HVSYSOVHT,                                       /* 00 HVSYSOVHT                                       */
    (U1)ALERT_REQ_H_UNIOVE_PD_HVSYSOVHT,                                       /* 01 HVSYSOVHT                                       */
    (U1)ALERT_REQ_H_UNIOVE_PD_HVSYSOVHT,                                       /* 02 HVSYSOVHT                                       */
    (U1)ALERT_REQ_H_UNIOVE_PD_FCVSYSOVHT,                                      /* 03 FCVSYSOVHT                                      */
    (U1)ALERT_REQ_H_UNIOVE_PD_HVSYSOVHT                                        /* 04 HVSYSOVHT                                       */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_UNIOVE_MTRX[2] = {
    {
        &u4_s_AlertH_unioveTtBcSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertH_unioveTtBcRwTx,                                           /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_UNIOVE_TT_BC_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_H_UNIOVE_TT_BC_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_uniovePdSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_UNIOVE_PD_MASK[0],                                      /* u4p_MASK                                           */
        &u4_sp_ALERT_H_UNIOVE_PD_CRIT[0],                                      /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_UNIOVE_PD_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_H_UNIOVE_PD_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_unioveTtBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_unioveTtBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_ENG1G97) && defined(ComConf_ComSignal_B_EXKAME)
    static const U1 u1_s_ALERT_H_UNIOVE_TTBC_LSB_ENG = (U1)2U;
    U1              u1_t_msgsts_eng;
    U1              u1_t_sgnl_b_exkame;
#endif /* defined(OXCAN_PDU_RX_CAN_ENG1G97) && defined(ComConf_ComSignal_B_EXKAME) */

#if defined(OXCAN_PDU_RX_CAN_EHV1S94_RXCH0) && defined(ComConf_ComSignal_HVOTID)
    static const U1 u1_s_ALERT_H_UNIOVE_TTBC_LSB_EHV = (U1)5U;
    static const U1 u1_s_ALERT_H_UNIOVE_TTBC_LSB_SGN = (U1)3U;
    U1              u1_t_msgsts_ehv;
    U1              u1_t_sgnl_hvotid;
#endif /* defined(OXCAN_PDU_RX_CAN_EHV1S94_RXCH0) && defined(ComConf_ComSignal_HVOTID) */

    U4              u4_t_src_chk;

#if defined(OXCAN_PDU_RX_CAN_ENG1G97) && defined(ComConf_ComSignal_B_EXKAME)
    u1_t_msgsts_eng    = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G97,
                                               (U2)OXCAN_RX_SYS_NRX_IGR,
                                               (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl_b_exkame = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_EXKAME, &u1_t_sgnl_b_exkame);
    u4_t_src_chk       = (U4)u1_t_sgnl_b_exkame;
    u4_t_src_chk      |= ((U4)u1_t_msgsts_eng  << u1_s_ALERT_H_UNIOVE_TTBC_LSB_ENG);
#else
    u4_t_src_chk       = (U4)0U;
#endif /* defined(OXCAN_PDU_RX_CAN_ENG1G97) && defined(ComConf_ComSignal_B_EXKAME) */

#if defined(OXCAN_PDU_RX_CAN_EHV1S94_RXCH0) && defined(ComConf_ComSignal_HVOTID)
    u1_t_msgsts_ehv    = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S94_RXCH0,
                                               (U2)OXCAN_RX_SYS_NRX_IGR,
                                               (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl_hvotid   = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVOTID, &u1_t_sgnl_hvotid);
    u4_t_src_chk      |= ((U4)u1_t_sgnl_hvotid << u1_s_ALERT_H_UNIOVE_TTBC_LSB_SGN);
    u4_t_src_chk      |= ((U4)u1_t_msgsts_ehv  << u1_s_ALERT_H_UNIOVE_TTBC_LSB_EHV);
#endif /* defined(OXCAN_PDU_RX_CAN_EHV1S94_RXCH0) && defined(ComConf_ComSignal_HVOTID) */

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_uniovePdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_uniovePdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_EHV1S94_RXCH0) && defined(ComConf_ComSignal_HVOTID)
    static const U1 u1_s_ALERT_H_UNIOVE_PD_LSB_EHV   = (U1)2U;
    static const U1 u1_s_ALERT_H_UNIOVE_PD_LSB_PTSYS = (U1)3U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S94_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_HVOTID, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_UNIOVE_PD_LSB_EHV);

    u1_t_sgnl     = u1_g_AlertPtsys();
    if(u1_t_sgnl > (U1)ALERT_PTSYS_1F_NRX){
        u1_t_sgnl = (U1)ALERT_PTSYS_0F_UNK;
    }
    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_H_UNIOVE_PD_LSB_PTSYS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_EHV1S94_RXCH0) && defined(ComConf_ComSignal_HVOTID) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertH_unioveTtBcRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertH_unioveTtBcRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U1 u1_s_ALERT_H_UNIOVE_RWTX_CRT = ((U1)((U1)1U << ALERT_REQ_H_UNIOVE_TT_BC_MALFUNC)
                                                 |  (U1)((U1)1U << ALERT_REQ_H_UNIOVE_TT_BC_RW     )
                                                 |  (U1)((U1)1U << ALERT_REQ_H_UNIOVE_TT_BC_PRM_RW ));
    static const U1 u1_s_ALERT_H_UNIOVE_RWTX_MSK = (U1)0x07U;
    U1              u1_t_sgnl;
    U1              u1_t_rw;

    u1_t_rw = ((U1)1U << (u1_a_DST & u1_s_ALERT_H_UNIOVE_RWTX_MSK));
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN)         != (U1)0U) &&
       ((u1_t_rw  & u1_s_ALERT_H_UNIOVE_RWTX_CRT) != (U1)0U)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MIHW, &u1_t_sgnl);    /* COM Tx STUB delete */
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
/*  5.0.0     3/23/2020  FN       New.                                                                                               */
/*  5.1.0     8/25/2020  TN       Change CAN Signal to get B_EXKAME (ENG1S97/ENG1G97 -> ENG1G97).                                    */
/*  5.2.0     9/23/2020  TM       Processing reception PTSYS signal was fixed.                                                       */
/*  5.3.0    12/ 8/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.3.1     3/26/2021  TN       Update for 840B CV(Version update).                                                                */
/*  5.3.2     5/14/2021  TN       Fix 800B Bug.                                                                                      */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
