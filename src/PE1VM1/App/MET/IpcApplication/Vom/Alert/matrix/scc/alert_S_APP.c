/* 5.1.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_APP                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_APP_C_MAJOR                      (5)
#define ALERT_S_APP_C_MINOR                      (1)
#define ALERT_S_APP_C_PATCH                      (2)

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
#if (ALERT_S_APP_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_APP.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_APP_BC_NUM_DST                   (32U)
#define ALERT_S_APP_PD_NUM_DST                   (64U)

#define ALERT_S_APP_NUM_RWSGNL                   (2U)
#define ALERT_S_APP_APP_EXT_BIT                  (0x80U)

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
static U4      u4_s_AlertS_appBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_appPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertS_appPdRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_APP_BC_DST[ALERT_S_APP_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_APP_BC_NOTOPERATED1,                                       /* 01 NOTOPERATED1                                    */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 02 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_NOTOPERATED2,                                       /* 03 NOTOPERATED2                                    */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_S_APP_BC_COMPLETION,                                         /* 06 COMPLETION                                      */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 16 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 17 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 18 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 19 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 20 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 21 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 22 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 23 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 24 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 25 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 26 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 27 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 28 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 29 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE,                                        /* 30 DISCONTINUE                                     */
    (U1)ALERT_REQ_S_APP_BC_DISCONTINUE                                         /* 31 DISCONTINUE                                     */
};
static const U1  u1_sp_ALERT_S_APP_PD_DST[ALERT_S_APP_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_APP_PD_OPERATION,                                          /* 01 OPERATION                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 03 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_BRAKE,                                              /* 04 BRAKE                                           */
    (U1)ALERT_REQ_S_APP_PD_CANCELLED,                                          /* 05 CANCELLED                                       */
    (U1)ALERT_REQ_S_APP_PD_REMMTEWAR,                                          /* 06 REMMTEWAR                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
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
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 32 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 33 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 34 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 35 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 36 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 37 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 38 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 39 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 40 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 41 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 42 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 43 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 44 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 45 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 46 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 47 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 48 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 49 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 50 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 51 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 52 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 53 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 54 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 55 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 56 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 57 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 58 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 59 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 60 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 61 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC,                                            /* 62 MALFUNC                                         */
    (U1)ALERT_REQ_S_APP_PD_MALFUNC                                             /* 63 MALFUNC                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_APP_MTRX[2] = {
    {
        &u4_s_AlertS_appBcSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_APP_BC_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_APP_BC_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_appPdSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertS_appPdRwTx,                                                /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_APP_PD_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_APP_PD_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_appBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_appBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_IPA1S05_CH0) && defined(ComConf_ComSignal_IPA_BZ2)
    static const U2 u2_s_ALERT_S_APP_BC_THRSH_TO   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_APP_BC_LSB_COMSTS = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IPA1S05_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_APP_BC_THRSH_TO) & (U1)(COM_TIMEOUT | COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_IPA_BZ2, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_S_APP_BC_LSB_COMSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_IPA1S05_CH0) && defined(ComConf_ComSignal_IPA_BZ2) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_appPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_appPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_IPA1S05_CH0) && defined(ComConf_ComSignal_APPME)
    static const U2 u2_s_ALERT_S_APP_PD_THRSH_TO   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_APP_PD_LSB_COMSTS = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IPA1S05_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_S_APP_PD_THRSH_TO) & (U1)(COM_TIMEOUT | COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_APPME, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts  << u1_s_ALERT_S_APP_PD_LSB_COMSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_IPA1S05_CH0) && defined(ComConf_ComSignal_APPME) */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertS_appPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertS_appPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U1 u1_sp_ALERT_S_APP_RWTX_CRT[ALERT_S_APP_NUM_RWSGNL] = {
        ((U1)((U1)1U << ALERT_REQ_S_APP_PD_MALFUNC  ) | (U1)ALERT_S_APP_APP_EXT_BIT),
         (U1)((U1)1U << ALERT_REQ_S_APP_PD_REMMTEWAR)   /* No need APP_EXT */
    };
    U4              u4_t_idx;
    U1              u1_t_sgnl;
    U1              u1_t_rw;
    U1              u1_t_esopt_app_ext;

    u1_t_esopt_app_ext = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_S_APP_APP_EXT);

    u1_t_rw  = (U1)0U;
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U               ) &&
       (u1_a_DST                          != (U1)ALERT_REQ_UNKNOWN)){
        u1_t_rw = ((U1)1U << u1_a_DST);
        if(u1_t_esopt_app_ext == (U1)TRUE){
            u1_t_rw |= (U1)ALERT_S_APP_APP_EXT_BIT;
        }
    }

    u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    for(u4_t_idx = (U4)0U; u4_t_idx < (U4)ALERT_S_APP_NUM_RWSGNL; u4_t_idx++){
        if((u1_t_rw & u1_sp_ALERT_S_APP_RWTX_CRT[u4_t_idx]) == u1_sp_ALERT_S_APP_RWTX_CRT[u4_t_idx]){
            u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
        }
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_APPW, &u1_t_sgnl);    /* COM Tx STUB delete */
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
/*  5.0.0     3/23/2020  KH       New.                                                                                               */
/*  5.1.0     8/18/2020  ZS       Fix remote warning logic.                                                                          */
/*  5.1.1     3/25/2021  MO       Update for 840B CV(Version update).                                                                */
/*  5.1.2     1/19/2022  KAT      Update for 840B#2 CV(Version update).                                                              */
/*                                                                                                                                   */
/*  * KH   = Koji Hattori, NTTD MSE                                                                                                  */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * KAT  = Katsushi Takahashi, NTTD MSE                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
