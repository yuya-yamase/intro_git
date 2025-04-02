/* 5.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_BDOOR                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_BDOOR_C_MAJOR                    (5)
#define ALERT_B_BDOOR_C_MINOR                    (5)
#define ALERT_B_BDOOR_C_PATCH                    (0)

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
#if (ALERT_B_BDOOR_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_BDOOR.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Configuration Check                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if !defined(ALERT_CFG_B_BDOOR_RRCY)
#error "alert_cfg_private.h : ALERT_CFG_B_BDOOR_RRCY is undefined!"
#endif
#if !defined(ALERT_CFG_B_BDOOR_RLCY)
#error "alert_cfg_private.h : ALERT_CFG_B_BDOOR_RLCY is undefined!"
#endif
#if !defined(ALERT_CFG_B_BDOOR_BCTY)
#error "alert_cfg_private.h : ALERT_CFG_B_BDOOR_BCTY is undefined!"
#endif
#if !defined(ALERT_CFG_B_BDOOR_LGCY)
#error "alert_cfg_private.h : ALERT_CFG_B_BDOOR_LGCY is undefined!"
#endif
#if !defined(ALERT_CFG_B_BDOOR_HDCY_BDB)
#error "alert_cfg_private.h : ALERT_CFG_B_BDOOR_HDCY_BDB is undefined!"
#endif
#if !defined(ALERT_CFG_B_BDOOR_RPSDWARN)
#error "alert_cfg_private.h : ALERT_CFG_B_BDOOR_RPSDWARN is undefined!"
#endif
#if !defined(ALERT_CFG_B_BDOOR_LPSDWARN)
#error "alert_cfg_private.h : ALERT_CFG_B_BDOOR_LPSDWARN is undefined!"
#endif
#if !defined(ALERT_CFG_B_BDOOR_SLP_POS)
#error "alert_cfg_private.h : ALERT_CFG_B_BDOOR_SLP_POS is undefined!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_BDOOR_NUM_DST                    (32U)
#define ALERT_B_BDOOR_RUNSTS_STOP                (0x00U)
#define ALERT_B_BDOOR_RUNSTS_RUN                 (0x01U)
#define ALERT_B_BDOOR_RUNSTS_FAST                (0x02U)
#define ALERT_B_BDOOR_SLP_TBL_NUM                (8U)

#define ALERT_B_BDOOR_SLP_POS_ACT                (1U)
#define ALERT_B_BDOOR_SLP_POS_INACT              (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_b_bdoor_dlycnt;
static U1      u1_s_alert_b_bdoor_runsts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_bdoorSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U1      u1_s_AlertB_bdoorGetSgnl  (const U1 u1_a_BDB1S01STS, const U1 u1_a_BDB1F01STS, const U1 u1_a_DRL1S03STS, const U1 u1_a_DRR1S03STS);
static U1      u1_s_AlertB_bdoorGetSlp   (const U1 u1_a_SLP1S01STS);
static void    vd_s_AlertB_bdoorGetRunSts(void);
static U1      u1_s_AlertB_bdoorGetDlySts(const U1 u1_a_SGNL, const U1 u1_a_SLP, const U1 u1_a_RUNSTS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_B_BDOOR_DST[ALERT_B_BDOOR_NUM_DST] = {
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
    (U1)ALERT_REQ_B_BDOOR_CYCLE,                                               /* 10 CYCLE                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_B_BDOOR_CYCLE,                                               /* 13 CYCLE                                           */
    (U1)ALERT_REQ_B_BDOOR_CYCLE,                                               /* 14 CYCLE                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_B_BDOOR_CYCLE,                                               /* 18 CYCLE                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_B_BDOOR_CYCLE,                                               /* 21 CYCLE                                           */
    (U1)ALERT_REQ_B_BDOOR_CYCLE,                                               /* 22 CYCLE                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_B_BDOOR_CYCLE,                                               /* 26 CYCLE                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_B_BDOOR_CYCLE,                                               /* 29 CYCLE                                           */
    (U1)ALERT_REQ_B_BDOOR_CYCLE,                                               /* 30 CYCLE                                           */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_B_BDOOR_MTRX[1] = {
    {
        &u4_s_AlertB_bdoorSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_BDOOR_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_B_BDOOR_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_bdoorInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_bdoorInit(void)
{
    u4_s_alert_b_bdoor_dlycnt = (U4)0U;
    u1_s_alert_b_bdoor_runsts = (U1)ALERT_B_BDOOR_RUNSTS_STOP;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_bdoorSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_bdoorSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_BDOOR_THSH_TO_BDB1S = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U2 u2_s_ALERT_B_BDOOR_THSH_TO_BDB1F = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#if (ALERT_CFG_B_BDOOR_LPSDWARN == TRUE)
    static const U2 u2_s_ALERT_B_BDOOR_THSH_TO_DRL1S = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#endif /* (ALERT_CFG_B_BDOOR_LPSDWARN == TRUE) */
#if (ALERT_CFG_B_BDOOR_RPSDWARN == TRUE)
    static const U2 u2_s_ALERT_B_BDOOR_THSH_TO_DRR1S = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#endif /* (ALERT_CFG_B_BDOOR_RPSDWARN == TRUE) */
#if (ALERT_CFG_B_BDOOR_SLP_POS == TRUE)
    static const U2 u2_s_ALERT_B_BDOOR_THSH_TO_SLP1S = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#endif /* (ALERT_CFG_B_BDOOR_SLP_POS == TRUE) */
    static const U1 u1_s_ALERT_B_BDOOR_LSB_SGNL      = (U1)3U;
    static const U1 u1_s_ALERT_B_BDOOR_LSB_SLP       = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts_bdb1s01;
    U1              u1_t_msgsts_bdb1f01;
    U1              u1_t_msgsts_drl1s03;
    U1              u1_t_msgsts_drr1s03;
    U1              u1_t_msgsts_slp1s01;
    U1              u1_t_sgnl;
    U1              u1_t_slp;

    u1_t_msgsts_bdb1s01 = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1S01_RXCH0,
                                                (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                                u2_s_ALERT_B_BDOOR_THSH_TO_BDB1S) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_msgsts_bdb1f01 = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BDB1F01_RXCH0,
                                                (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                                u2_s_ALERT_B_BDOOR_THSH_TO_BDB1F) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

#if (ALERT_CFG_B_BDOOR_LPSDWARN == TRUE)
    u1_t_msgsts_drl1s03 = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DRL1S03_RXCH0,
                                                (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                                u2_s_ALERT_B_BDOOR_THSH_TO_DRL1S) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts_drl1s03 = (U1)COM_NO_RX;
#endif /* (ALERT_CFG_B_BDOOR_LPSDWARN == TRUE) */

#if (ALERT_CFG_B_BDOOR_RPSDWARN == TRUE)
    u1_t_msgsts_drr1s03 = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_DRR1S03_RXCH0,
                                                (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                                u2_s_ALERT_B_BDOOR_THSH_TO_DRR1S) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts_drr1s03 = (U1)COM_NO_RX;
#endif /* (ALERT_CFG_B_BDOOR_RPSDWARN == TRUE) */

#if (ALERT_CFG_B_BDOOR_SLP_POS == TRUE)
    u1_t_msgsts_slp1s01 = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SLP1S01,
                                                (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                                u2_s_ALERT_B_BDOOR_THSH_TO_SLP1S) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts_slp1s01 = (U1)COM_NO_RX;
#endif /* (ALERT_CFG_B_BDOOR_SLP_POS == TRUE) */

    u1_t_sgnl           = u1_s_AlertB_bdoorGetSgnl(u1_t_msgsts_bdb1s01, u1_t_msgsts_bdb1f01, u1_t_msgsts_drl1s03, u1_t_msgsts_drr1s03);
    u1_t_slp            = u1_s_AlertB_bdoorGetSlp(u1_t_msgsts_slp1s01);
    vd_s_AlertB_bdoorGetRunSts();
    u4_t_src_chk        = (U4)u1_s_alert_b_bdoor_runsts;
    u4_t_src_chk       |= (U4)u1_s_AlertB_bdoorGetDlySts(u1_t_sgnl, u1_t_slp, u1_s_alert_b_bdoor_runsts);
    u4_t_src_chk       |= ((U4)u1_t_sgnl << u1_s_ALERT_B_BDOOR_LSB_SGNL);
    u4_t_src_chk       |= ((U4)u1_t_slp  << u1_s_ALERT_B_BDOOR_LSB_SLP );
    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertB_bdoorGetSgnl(const U1 u1_a_BDB1S01STS, const U1 u1_a_BDB1F01STS,                                      */
/*                                          const U1 u1_a_DRL1S03STS, const U1 u1_a_DRR1S03STS)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertB_bdoorGetSgnl(const U1 u1_a_BDB1S01STS, const U1 u1_a_BDB1F01STS, const U1 u1_a_DRL1S03STS, const U1 u1_a_DRR1S03STS)
{
    U1              u1_t_sgnl;
    U1              u1_t_retval;

    u1_t_retval = (U1)0U;
    if(u1_a_BDB1S01STS == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_DCTY, &u1_t_retval);

        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_PCTY, &u1_t_sgnl);
        u1_t_retval |= u1_t_sgnl;

#if (ALERT_CFG_B_BDOOR_RRCY == TRUE)
        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_RRCY, &u1_t_sgnl);
        u1_t_retval |= u1_t_sgnl;
#endif /* (ALERT_CFG_B_BDOOR_RRCY == TRUE) */

#if (ALERT_CFG_B_BDOOR_RLCY == TRUE)
        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_RLCY, &u1_t_sgnl);
        u1_t_retval |= u1_t_sgnl;
#endif /* (ALERT_CFG_B_BDOOR_RLCY == TRUE) */

#if (ALERT_CFG_B_BDOOR_BCTY == TRUE)
        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_BCTY, &u1_t_sgnl);
        u1_t_retval |= u1_t_sgnl;
#endif /* (ALERT_CFG_B_BDOOR_BCTY == TRUE) */

#if (ALERT_CFG_B_BDOOR_LGCY == TRUE)
        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_LGCY, &u1_t_sgnl);
        u1_t_retval |= u1_t_sgnl;
#endif /* (ALERT_CFG_B_BDOOR_LGCY == TRUE) */
    }

#if (ALERT_CFG_B_BDOOR_HDCY_BDB == TRUE)
    if(u1_a_BDB1F01STS == (U1)0U){
        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_HDCY_BDB, &u1_t_sgnl);
        u1_t_retval |= u1_t_sgnl;
    }
#endif /* (ALERT_CFG_B_BDOOR_HDCY_BDB == TRUE) */

#if (ALERT_CFG_B_BDOOR_LPSDWARN == TRUE)
    if(u1_a_DRL1S03STS == (U1)0U){
        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_LPSDWARN, &u1_t_sgnl);
        u1_t_retval |= u1_t_sgnl;
    }
#endif /* (ALERT_CFG_B_BDOOR_LPSDWARN == TRUE) */

#if (ALERT_CFG_B_BDOOR_RPSDWARN == TRUE)
    if(u1_a_DRR1S03STS == (U1)0U){
        u1_t_sgnl    = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_RPSDWARN, &u1_t_sgnl);
        u1_t_retval |= u1_t_sgnl;
    }
#endif /* (ALERT_CFG_B_BDOOR_RPSDWARN == TRUE) */

    return(u1_t_retval);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertB_bdoorGetSlp   (const U1 u1_a_SLP1S01STS)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertB_bdoorGetSlp(const U1 u1_a_SLP1S01STS)
{
#if (ALERT_CFG_B_BDOOR_SLP_POS == TRUE)
    U1              u1_t_sgnl;
    U1              u1_t_retval;
    static const U1 u1_sp_ALERT_B_BDOOR_SLP_TBL[ALERT_B_BDOOR_SLP_TBL_NUM] = {
        (U1)ALERT_B_BDOOR_SLP_POS_INACT,
        (U1)ALERT_B_BDOOR_SLP_POS_ACT,
        (U1)ALERT_B_BDOOR_SLP_POS_ACT,
        (U1)ALERT_B_BDOOR_SLP_POS_ACT,
        (U1)ALERT_B_BDOOR_SLP_POS_ACT,
        (U1)ALERT_B_BDOOR_SLP_POS_ACT,
        (U1)ALERT_B_BDOOR_SLP_POS_INACT,
        (U1)ALERT_B_BDOOR_SLP_POS_INACT
    };

    u1_t_retval = (U1)ALERT_B_BDOOR_SLP_POS_INACT;
    if(u1_a_SLP1S01STS == (U1)0U){
        u1_t_sgnl   = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_SLP_POS, &u1_t_sgnl);
        if(u1_t_sgnl < (U1)ALERT_B_BDOOR_SLP_TBL_NUM){
            u1_t_retval = u1_sp_ALERT_B_BDOOR_SLP_TBL[u1_t_sgnl];
        }
    }

    return(u1_t_retval);
#else
    return((U1)ALERT_B_BDOOR_SLP_POS_INACT);
#endif /* (ALERT_CFG_B_BDOOR_SLP_POS == TRUE) */
}

/*===================================================================================================================================*/
/*  static void      vd_s_AlertB_bdoorGetRunSts(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_AlertB_bdoorGetRunSts(void)
{
    static const U2 u2_s_ALERT_B_BDOOR_THRSH_FAST = (U2)1000U;
    static const U2 u2_s_ALERT_B_BDOOR_THRSH_RUN  = (U2)500U;
    static const U2 u2_s_ALERT_B_BDOOR_THRSH_STOP = (U2)400U;
    U2              u2_t_instspd;
    U1              u1_t_vehspd_sts;
    U1              u1_t_runsts;

    u2_t_instspd              = (U2)0U;
    u1_t_vehspd_sts           = u1_g_AlertSpdKmphInst(&u2_t_instspd, (U1)TRUE);
    u1_t_runsts               = (U1)ALERT_B_BDOOR_RUNSTS_STOP;

    if(u1_t_vehspd_sts == (U1)ALERT_SPD_STSBIT_VALID){
        if(u2_s_ALERT_B_BDOOR_THRSH_FAST < u2_t_instspd){
            u1_t_runsts = (U1)ALERT_B_BDOOR_RUNSTS_FAST;
        }
        else if(u2_s_ALERT_B_BDOOR_THRSH_RUN <= u2_t_instspd){
            u1_t_runsts = (U1)ALERT_B_BDOOR_RUNSTS_RUN;
        }
        else if((u2_s_ALERT_B_BDOOR_THRSH_STOP <  u2_t_instspd                 ) &&
                (u1_s_alert_b_bdoor_runsts     != (U1)ALERT_B_BDOOR_RUNSTS_STOP)){
            u1_t_runsts = (U1)ALERT_B_BDOOR_RUNSTS_RUN;
        }
        else{
            /* Do Nothing */
        }
    }

    u1_s_alert_b_bdoor_runsts = u1_t_runsts;
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertB_bdoorGetDlySts(const U1 u1_a_SGNL, const U1 u1_a_SLP, const U1 u1_a_RUNSTS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertB_bdoorGetDlySts(const U1 u1_a_SGNL, const U1 u1_a_SLP, const U1 u1_a_RUNSTS)
{
    static const U4  u4_s_ALERT_B_BDOOR_DLYTM      = ((U4)1000U / (U4)ALERT_MAIN_TICK);
    static const U1  u1_s_ALERT_B_BDOOR_BIT_DLYCMP = (U1)0x04U;
    U1               u1_t_retval;
    U1               u1_t_flctsts;

    u1_t_retval  = (U1)0U;
    u1_t_flctsts = u1_g_AlertSpdFluctStat();

    if((u1_a_RUNSTS == (U1)ALERT_B_BDOOR_RUNSTS_STOP  ) ||
       ((u1_a_SGNL  == (U1)0U                         ) &&
        (u1_a_SLP   == (U1)ALERT_B_BDOOR_SLP_POS_INACT))){
        u4_s_alert_b_bdoor_dlycnt = (U4)0U;
    }
    else if((u1_a_RUNSTS              == (U1)ALERT_B_BDOOR_RUNSTS_FAST) ||
            (u4_s_ALERT_B_BDOOR_DLYTM <= u4_s_alert_b_bdoor_dlycnt    ) ||
            (u1_t_flctsts             != (U1)ALERT_SPD_FLUCT_DECR     )){
        u4_s_alert_b_bdoor_dlycnt = (U4)U4_MAX;
        u1_t_retval               = u1_s_ALERT_B_BDOOR_BIT_DLYCMP;
    }
    else{
        u4_s_alert_b_bdoor_dlycnt++;
    }

    return(u1_t_retval);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     4/ 7/2020  SN       New.                                                                                               */
/*  5.1.0    12/ 8/2020  TN       Update for 800B 1A(Version update).                                                                */
/*  5.2.0     3/17/2021  SO       Add signal of LGCY/LPSDWARN/RPSDWARN, and add compile switch.                                      */
/*  5.3.0     6/23/2021  MO       Add signal of SLP_POS, and add compile switch.                                                     */
/*  5.4.0     8/ 6/2021  MO       Change dlytimer thresh.                                                                            */
/*  5.4.1    11/16/2021  TM       Fix QAC Warning.                                                                                   */
/*  5.4.2     5/26/2022  HU       Fix QAC Warning(Empty if Statement).                                                               */
/*  5.5.0     3/ 7/2023  MY       Change available signals to config.                                                                */
/*                                                                                                                                   */
/*  * SN   = Shinichiro Naito, NTTD MSE                                                                                              */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
