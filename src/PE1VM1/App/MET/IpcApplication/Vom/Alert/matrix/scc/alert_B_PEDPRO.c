/* 5.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_PEDPRO                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_PEDPRO_C_MAJOR                   (5)
#define ALERT_B_PEDPRO_C_MINOR                   (1)
#define ALERT_B_PEDPRO_C_PATCH                   (1)

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
#if (ALERT_B_PEDPRO_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_PEDPRO.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_PEDPRO_NUM_DST                   (16U)

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
static U4      u4_s_AlertB_pedproSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertB_pedproRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_B_PEDPRO_DST[ALERT_B_PEDPRO_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,                                          /* 01 DIAGDTRMN                                       */
    (U1)ALERT_REQ_B_PEDPRO_PRIMARYCHK,                                         /* 02 PRIMARYCHK                                      */
    (U1)ALERT_REQ_B_PEDPRO_PUHDVCACT,                                          /* 03 PUHDVCACT                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,                                          /* 08 DIAGDTRMN                                       */
    (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,                                          /* 09 DIAGDTRMN                                       */
    (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,                                          /* 10 DIAGDTRMN                                       */
    (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,                                          /* 11 DIAGDTRMN                                       */
    (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,                                          /* 12 DIAGDTRMN                                       */
    (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,                                          /* 13 DIAGDTRMN                                       */
    (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,                                          /* 14 DIAGDTRMN                                       */
    (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN                                           /* 15 DIAGDTRMN                                       */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_B_PEDPRO_MTRX[1] = {
    {
        &u4_s_AlertB_pedproSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertB_pedproRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_PEDPRO_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_B_PEDPRO_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_pedproSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_pedproSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(ComConf_ComSignal_PDS_WL) && defined(OXCAN_RXD_PDU_CAN_PDS1S01_CH0) /* _840B_CAN_ */
    static const U2 u2_s_ALERT_B_PEDPRO_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_PEDPRO_LSB_MSGSTS = (U1)2U;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U4              u4_t_src_chk;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_PDS1S01_CH0,
                                          (U4)OXCAN_SYS_IGR,
                                          u2_s_ALERT_B_PEDPRO_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PDS_WL, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_PEDPRO_LSB_MSGSTS);

    return(u4_t_src_chk);
#else /* defined(ComConf_ComSignal_PDS_WL) && defined(OXCAN_RXD_PDU_CAN_PDS1S01_CH0)  */
    return((U4)0U);
#endif /* defined(ComConf_ComSignal_PDS_WL) && defined(OXCAN_RXD_PDU_CAN_PDS1S01_CH0)  */
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertB_pedproRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertB_pedproRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#if defined(ComConf_ComSignal_PEDW)
    static const U4 u4_s_ALERT_B_PEDPRO_TIM_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
#endif /* defined(ComConf_ComSignal_PEDW) */
#if defined(ComConf_ComSignal_PUHW) /* _300D_CAN_ */
    U1              u1_t_sgnl_PUHW;
#endif                              /* _300D_CAN_ */
#if defined(ComConf_ComSignal_PEDW)
    U1              u1_t_sgnl_PEDW;
#endif /* defined(ComConf_ComSignal_PEDW) */
    U1              u1_t_esopt;

    u1_t_esopt = u1_g_AlertEsOptAvailable((U2)ALERT_OPT_ID_B_PEDPRO_PUH_FLG);

#if defined(ComConf_ComSignal_PUHW) /* _300D_CAN_ */
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                          ) &&
       (u1_t_esopt                        == (U1)TRUE                        ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN)){
        u1_t_sgnl_PUHW = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl_PUHW = (U1)ALERT_RW_SGNL_OFF;
    }
#endif                              /* _300D_CAN_ */

#if defined(ComConf_ComSignal_PEDW)
    if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                          ) &&
       (u4_a_IGN_TM                       >= u4_s_ALERT_B_PEDPRO_TIM_RW_ENBL ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_B_PEDPRO_PUHDVCACT)){
        u1_t_sgnl_PEDW = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl_PEDW = (U1)ALERT_RW_SGNL_OFF;
    }
#endif /* defined(ComConf_ComSignal_PEDW) */

#if defined(ComConf_ComSignal_PUHW) /* _300D_CAN_ */
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_PUHW, &u1_t_sgnl_PUHW);    /* COM Tx STUB delete */
#endif
#endif                              /* _300D_CAN_ */
#if defined(ComConf_ComSignal_PEDW)
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_PEDW, &u1_t_sgnl_PEDW);    /* COM Tx STUB delete */
#endif
#endif /* defined(ComConf_ComSignal_PEDW) */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/18/2021  SO       New.                                                                                               */
/*  5.1.0    10/25/2021  KT       Add remote warning of PEDW.                                                                        */
/*  5.1.1     7/12/2022  RN       Update for 840B#2 1A(Version update).                                                              */
/*                                                                                                                                   */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * RN   = Ryuga Nakanishi, NTTD MSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
