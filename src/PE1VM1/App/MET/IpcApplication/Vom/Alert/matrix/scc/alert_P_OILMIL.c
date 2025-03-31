/* 5.2.2 */
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
#define ALERT_P_OILMIL_C_MINOR                   (2)
#define ALERT_P_OILMIL_C_PATCH                   (2)

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
#if (ALERT_P_OILMIL_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_OILMIL.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_OILMIL_NUM_DST                   (64U)

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
static U4      u4_s_AlertP_oilmilSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertP_oilmilRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_P_OILMIL_DST[ALERT_P_OILMIL_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND,                                            /* 01 OILDMND                                         */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN,                                          /* 02 OILPREWRN                                       */
    (U1)ALERT_REQ_P_OILMIL_RESETCMPLT,                                         /* 03 RESETCMPLT                                      */
    (U1)ALERT_REQ_P_OILMIL_RW_OMDW,                                            /* 04 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND,                                            /* 05 OILDMND                                         */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN_RW,                                       /* 06 OILPREWRN_RW                                    */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_OMDW,                                      /* 07 RESETCMP_OMDW                                   */
    (U1)ALERT_REQ_P_OILMIL_RW_OMPW,                                            /* 08 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND_RW,                                         /* 09 OILDMND_RW                                      */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN,                                          /* 10 OILPREWRN                                       */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_OMPW,                                      /* 11 RESETCMP_OMPW                                   */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND,                                            /* 13 OILDMND                                         */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN,                                          /* 14 OILPREWRN                                       */
    (U1)ALERT_REQ_P_OILMIL_RESETCMPLT,                                         /* 15 RESETCMPLT                                      */
    (U1)ALERT_REQ_P_OILMIL_RW_OMDW,                                            /* 16 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND,                                            /* 17 OILDMND                                         */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN_RW,                                       /* 18 OILPREWRN_RW                                    */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_OMDW,                                      /* 19 RESETCMP_OMDW                                   */
    (U1)ALERT_REQ_P_OILMIL_RW_OMDW,                                            /* 20 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND,                                            /* 21 OILDMND                                         */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN_RW,                                       /* 22 OILPREWRN_RW                                    */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_OMDW,                                      /* 23 RESETCMP_OMDW                                   */
    (U1)ALERT_REQ_P_OILMIL_RW,                                                 /* 24 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_OILDMND_RW,                                         /* 25 OILDMND_RW                                      */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN_RW,                                       /* 26 OILPREWRN_RW                                    */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_RW,                                        /* 27 RESETCMP_RW                                     */
    (U1)ALERT_REQ_P_OILMIL_RW_OMDW,                                            /* 28 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND,                                            /* 29 OILDMND                                         */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN_RW,                                       /* 30 OILPREWRN_RW                                    */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_OMDW,                                      /* 31 RESETCMP_OMDW                                   */
    (U1)ALERT_REQ_P_OILMIL_RW_OMPW,                                            /* 32 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND_RW,                                         /* 33 OILDMND_RW                                      */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN,                                          /* 34 OILPREWRN                                       */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_OMPW,                                      /* 35 RESETCMP_OMPW                                   */
    (U1)ALERT_REQ_P_OILMIL_RW,                                                 /* 36 RW                                              */
    (U1)ALERT_REQ_P_OILMIL_OILDMND_RW,                                         /* 37 OILDMND_RW                                      */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN_RW,                                       /* 38 OILPREWRN_RW                                    */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_RW,                                        /* 39 RESETCMP_RW                                     */
    (U1)ALERT_REQ_P_OILMIL_RW_OMPW,                                            /* 40 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND_RW,                                         /* 41 OILDMND_RW                                      */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN,                                          /* 42 OILPREWRN                                       */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_OMPW,                                      /* 43 RESETCMP_OMPW                                   */
    (U1)ALERT_REQ_P_OILMIL_RW_OMPW,                                            /* 44 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND_RW,                                         /* 45 OILDMND_RW                                      */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN,                                          /* 46 OILPREWRN                                       */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_OMPW,                                      /* 47 RESETCMP_OMPW                                   */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND,                                            /* 49 OILDMND                                         */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN,                                          /* 50 OILPREWRN                                       */
    (U1)ALERT_REQ_P_OILMIL_RESETCMPLT,                                         /* 51 RESETCMPLT                                      */
    (U1)ALERT_REQ_P_OILMIL_RW_OMDW,                                            /* 52 RW_OMDW                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND,                                            /* 53 OILDMND                                         */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN_RW,                                       /* 54 OILPREWRN_RW                                    */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_OMDW,                                      /* 55 RESETCMP_OMDW                                   */
    (U1)ALERT_REQ_P_OILMIL_RW_OMPW,                                            /* 56 RW_OMPW                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND_RW,                                         /* 57 OILDMND_RW                                      */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN,                                          /* 58 OILPREWRN                                       */
    (U1)ALERT_REQ_P_OILMIL_RESETCMP_OMPW,                                      /* 59 RESETCMP_OMPW                                   */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 60 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILMIL_OILDMND,                                            /* 61 OILDMND                                         */
    (U1)ALERT_REQ_P_OILMIL_OILPREWRN,                                          /* 62 OILPREWRN                                       */
    (U1)ALERT_REQ_P_OILMIL_RESETCMPLT                                          /* 63 RESETCMPLT                                      */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_OILMIL_MTRX[1] = {
    {
        &u4_s_AlertP_oilmilSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_oilmilRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_OILMIL_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_P_OILMIL_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_oilmilSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_oilmilSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_P_OILMIL_TO_THRESH    = ((U2)7500U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_P_OILMIL_LSB_B_OMWI   = (U1)2U;
    static const U1 u1_s_ALERT_P_OILMIL_LSB_HV_B_OMW = (U1)4U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_P_OILMIL_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    if(u1_t_msgsts == (U1)0U){
#if 0   /* BEV BSW provisionally */
        (void)Com_ReceiveSignal(ComConf_ComSignal_B_OMWI2, &u1_t_sgnl);
#endif
    }
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
#if defined(OXCAN_PDU_RX_CAN_ENG1G92_RXCH0) && defined(ComConf_ComSignal_B_OMWI)
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G92_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;

    if((u1_t_msgsts & (U1)COM_NO_RX) == (U1)0U){
#if 0   /* BEV BSW provisionally */
        (void)Com_ReceiveSignal(ComConf_ComSignal_B_OMWI, &u1_t_sgnl);
#endif
    }
#endif /* defined(OXCAN_PDU_RX_CAN_ENG1G92_RXCH0) && defined(ComConf_ComSignal_B_OMWI) */
    u4_t_src_chk |= (U4)((U4)u1_t_sgnl << u1_s_ALERT_P_OILMIL_LSB_B_OMWI);

    u1_t_sgnl     = (U1)0U;
#if defined(OXCAN_PDU_RX_CAN_HEG1S90) && defined(ComConf_ComSignal_HV_B_OMW)
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_HEG1S90,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;

    if((u1_t_msgsts & (U1)COM_NO_RX) == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_HV_B_OMW, &u1_t_sgnl);
    }
#endif /* defined(OXCAN_PDU_RX_CAN_HEG1S90) && defined(ComConf_ComSignal_HV_B_OMW) */
    u4_t_src_chk |= (U4)((U4)u1_t_sgnl << u1_s_ALERT_P_OILMIL_LSB_HV_B_OMW);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertP_oilmilRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_oilmilRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U2 u2_s_ALERT_P_OILMIL_OMDW_CRT = ((U2)((U2)1U << ALERT_REQ_P_OILMIL_OILDMND      )
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_OILDMND_RW   )
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_OILPREWRN_RW )
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_RESETCMP_OMDW)
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_RESETCMP_RW  )
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_RW_OMDW      )
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_RW           ));

    static const U2 u2_s_ALERT_P_OILMIL_OMPW_CRT = ((U2)((U2)1U << ALERT_REQ_P_OILMIL_OILPREWRN    )
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_OILDMND_RW   )
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_OILPREWRN_RW )
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_RESETCMP_OMPW)
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_RESETCMP_RW  )
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_RW_OMPW      )
                                                 |  (U2)((U2)1U << ALERT_REQ_P_OILMIL_RW           ));

    static const U1 u1_s_ALERT_P_OILMIL_RWTX_MSK = (U1)0x0FU;
    U1              u1_t_omdw;
    U1              u1_t_ompw;
    U2              u2_t_rw;

    u1_t_omdw = (U1)ALERT_RW_SGNL_OFF;
    u1_t_ompw = (U1)ALERT_RW_SGNL_OFF;
    u2_t_rw   = ((U2)1U << (u1_a_DST & u1_s_ALERT_P_OILMIL_RWTX_MSK));

    if((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U){
        if((u2_t_rw  & (U2)u2_s_ALERT_P_OILMIL_OMDW_CRT) != (U2)0U){
            u1_t_omdw = (U1)ALERT_RW_SGNL_ON;
        }
        if((u2_t_rw  & (U2)u2_s_ALERT_P_OILMIL_OMPW_CRT) != (U2)0U){
            u1_t_ompw = (U1)ALERT_RW_SGNL_ON;
        }
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_OMDW, &u1_t_omdw);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_OMPW, &u1_t_ompw);    /* COM Tx STUB delete */
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
/*  5.0.0     2/19/2020  FN       New.                                                                                               */
/*  5.0.1     7/27/2020  ZS       Update module spec 800B CV-R.                                                                      */
/*  5.1.0    12/ 8/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.1.1     3/26/2021  MO       Update for 840B CV(Version update).                                                                */
/*  5.2.0    11/19/2021  RI       Add B_OMWI, and HV_B_OMW.                                                                          */
/*  5.2.1     5/30/2022  KK       Update for 840B#2 1A(Version update).                                                              */
/*  5.2.2     2/13/2024  GM       Update for 19PFv3 PreCV(Version update).                                                           */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * KK   = Kenta Kawahara, NTTD MSE                                                                                                */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
