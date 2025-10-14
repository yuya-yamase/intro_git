/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_OILMIL                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_OILMIL_C_MAJOR                   (5)
#define ALERT_P_OILMIL_C_MINOR                   (3)
#define ALERT_P_OILMIL_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_P_OILMIL_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_OILMIL.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_OILMIL_DISP_NUM_DST              (16U)
#define ALERT_P_OILMIL_RW_NUM_DST                (64U)

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
static U4      u4_s_AlertP_oilmilDispSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_oilmilRwSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertP_oilmilRwRwTx    (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_OILMIL_DISP_DST[ALERT_P_OILMIL_DISP_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_DISP_DMNDWRN,                                       /* 01 DMNDWRN                                         */
    (U1)ALERT_REQ_P_OILMIL_DISP_PREWRN,                                        /* 02 PREWRN                                          */
    (U1)ALERT_REQ_P_OILMIL_DISP_RESETCMP,                                      /* 03 RESETCMP                                        */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_P_OILMIL_RW_DST[ALERT_P_OILMIL_RW_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 01 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 02 RW_OMPW                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 04 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 05 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 06 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 07 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 08 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 09 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 10 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 11 RW_OMPW                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 13 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 14 RW_OMPW                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 16 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 17 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 18 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 19 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 20 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 21 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 22 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 23 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 24 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 25 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 26 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 27 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 28 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 29 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 30 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 31 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 32 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 33 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 34 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 35 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 36 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 37 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 38 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 39 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 40 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 41 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 42 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 43 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 44 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 45 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 46 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 47 RW_OMPW                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 49 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 50 RW_OMPW                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 52 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 53 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 54 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 55 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 56 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW,                                              /* 57 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 58 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 59 RW_OMPW                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 60 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMDW,                                         /* 61 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_RW_RW_OMPW,                                         /* 62 RW_OMPW                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 63 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_OILMIL_MTRX[2] = {
    {
        &u4_s_AlertP_oilmilDispSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_OILMIL_DISP_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_P_OILMIL_DISP_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_oilmilRwSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_oilmilRwRwTx,                                             /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_OILMIL_RW_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_P_OILMIL_RW_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_oilmilDispSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_oilmilDispSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_P_OILMIL_DISP_TO_TRSH = ((U2)7500U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_P_OILMIL_DISP_LSB_COM = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S99,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_P_OILMIL_DISP_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_P_OILMIL_DISP_LSB_COM);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_OMWI2, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_oilmilRwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_oilmilRwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_P_OILMIL_RW_TO_THRESH = ((U2)7500U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_P_OILMIL_RW_LSB_OMWI  = (U1)2U;
    static const U1 u1_s_ALERT_P_OILMIL_RW_LSB_HV_B  = (U1)4U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_esopt;
    U4              u4_t_src_chk;
    U1              u1_t_oilmil_pid;

    u1_t_msgsts     = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S99,
                                       (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                       u2_s_ALERT_P_OILMIL_RW_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl       = (U1)0U;
    u1_t_esopt      = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_P_OILMIL_OILMNTMI);

    if((u1_t_msgsts == (U1)0U  ) &&
       (u1_t_esopt  == (U1)TRUE)){
        (void)Com_ReceiveSignal(ComConf_ComSignal_B_OMWI2, &u1_t_sgnl);
    }

    u1_t_oilmil_pid = u1_g_AlertCfgOilmilIsEnable();
    if(u1_t_oilmil_pid == (U1)FALSE){
        u1_t_sgnl   = (U1)0U;
    }

    u4_t_src_chk    = (U4)u1_t_sgnl;

    u1_t_sgnl       = (U1)0U;
    u1_t_msgsts     = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G92,
                                       (U2)OXCAN_RX_SYS_NRX_IGR,
                                       (U2)U2_MAX) & (U1)COM_NO_RX;

    if((u1_t_msgsts & (U1)COM_NO_RX) == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_B_OMWI, &u1_t_sgnl);
    }
    u4_t_src_chk   |= ((U4)u1_t_sgnl << u1_s_ALERT_P_OILMIL_RW_LSB_OMWI);

    u1_t_sgnl       = (U1)0U;
#if defined(OXCAN_PDU_RX_CAN_HEG1S90) && defined(ComConf_ComSignal_HV_B_OMW)
    u1_t_msgsts     = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_HEG1S90,
                                       (U2)OXCAN_RX_SYS_NRX_IGR,
                                       (U2)U2_MAX) & (U1)COM_NO_RX;

    if((u1_t_msgsts & (U1)COM_NO_RX) == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_HV_B_OMW, &u1_t_sgnl);
    }
#endif /* defined(OXCAN_PDU_RX_CAN_HEG1S90) && defined(ComConf_ComSignal_HV_B_OMW) */
    u4_t_src_chk   |= ((U4)u1_t_sgnl << u1_s_ALERT_P_OILMIL_RW_LSB_HV_B);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertP_oilmilRwRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_oilmilRwRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U2 u2_s_ALERT_P_OILMIL_RW_OMDW_CRT = ((U2)((U2)1U << ALERT_REQ_P_OILMIL_RW_RW_OMDW)
                                                    |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_RW_RW     ));

    static const U2 u2_s_ALERT_P_OILMIL_RW_OMPW_CRT = ((U2)((U2)1U << ALERT_REQ_P_OILMIL_RW_RW_OMPW)
                                                    |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_RW_RW     ));

    static const U1 u1_s_ALERT_P_OILMIL_RW_RWTX_MSK = (U1)0x07U;
    U1              u1_t_omdw;
    U1              u1_t_ompw;
    U2              u2_t_rw;

    u1_t_omdw = (U1)ALERT_RW_SGNL_OFF;
    u1_t_ompw = (U1)ALERT_RW_SGNL_OFF;
    u2_t_rw   = ((U2)1U << (u1_a_DST & u1_s_ALERT_P_OILMIL_RW_RWTX_MSK));

    if((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U){
        if((u2_t_rw  & (U2)u2_s_ALERT_P_OILMIL_RW_OMDW_CRT) != (U2)0U){
            u1_t_omdw = (U1)ALERT_RW_SGNL_ON;
        }
        if((u2_t_rw  & (U2)u2_s_ALERT_P_OILMIL_RW_OMPW_CRT) != (U2)0U){
            u1_t_ompw = (U1)ALERT_RW_SGNL_ON;
        }
    }

    (void)Com_SendSignal(ComConf_ComSignal_OMDW, &u1_t_omdw);
    (void)Com_SendSignal(ComConf_ComSignal_OMPW, &u1_t_ompw);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     2/19/2020  FN       New.                                                                                               */
/*  5.0.1     7/27/2020  ZS       Update module spec 800B CV-R.                                                                      */
/*  5.1.0    12/ 8/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.1.1     3/26/2021  MO       Update for 840B CV(Version update).                                                                */
/*  5.2.0    11/19/2021  RI       Add B_OMWI, and HV_B_OMW.                                                                          */
/*  5.2.1     5/30/2022  KK       Update for 840B#2 1A(Version update).                                                              */
/*  5.2.2     2/13/2024  GM       Update for 19PFv3 PreCV(Version update).                                                           */
/*  5.3.0     4/23/2025  AA       Update for MET19PFV3-44769 bug                                                                     */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * KK   = Kenta Kawahara, NTTD MSE                                                                                                */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * AA   = Anna Asuncion, DTPH                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
