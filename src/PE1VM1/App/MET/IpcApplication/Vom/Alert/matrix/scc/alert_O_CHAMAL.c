/* 5.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert O_CHAMAL                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_O_CHAMAL_C_MAJOR                   (5)
#define ALERT_O_CHAMAL_C_MINOR                   (1)
#define ALERT_O_CHAMAL_C_PATCH                   (1)

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
#if (ALERT_O_CHAMAL_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_O_CHAMAL.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_O_CHAMAL_NUM_DST                   (32U)

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
static U4      u4_s_AlertO_chamalSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertO_chamalRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_O_CHAMAL_DST[ALERT_O_CHAMAL_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_O_CHAMAL_MALFUNC,                                            /* 01 MALFUNC                                         */
    (U1)ALERT_REQ_O_CHAMAL_PRMRYCHK,                                           /* 02 PRMRYCHK                                        */
    (U1)ALERT_REQ_O_CHAMAL_INSPECTION,                                         /* 03 INSPECTION                                      */
    (U1)ALERT_REQ_O_CHAMAL_CYCL,                                               /* 04 CYCL                                            */
    (U1)ALERT_REQ_O_CHAMAL_MALFUNC_BZ,                                         /* 05 MALFUNC_BZ                                      */
    (U1)ALERT_REQ_O_CHAMAL_PRMRYCHK_BZ,                                        /* 06 PRMRYCHK_BZ                                     */
    (U1)ALERT_REQ_O_CHAMAL_INSPECTION_BZ,                                      /* 07 INSPECTION_BZ                                   */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_O_CHAMAL_MALFUNC,                                            /* 17 MALFUNC                                         */
    (U1)ALERT_REQ_O_CHAMAL_PRMRYCHK,                                           /* 18 PRMRYCHK                                        */
    (U1)ALERT_REQ_O_CHAMAL_INSPECTION,                                         /* 19 INSPECTION                                      */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_O_CHAMAL_MALFUNC,                                            /* 21 MALFUNC                                         */
    (U1)ALERT_REQ_O_CHAMAL_PRMRYCHK,                                           /* 22 PRMRYCHK                                        */
    (U1)ALERT_REQ_O_CHAMAL_INSPECTION,                                         /* 23 INSPECTION                                      */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_O_CHAMAL_MTRX[1] = {
    {
        &u4_s_AlertO_chamalSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertO_chamalRwTx,                                               /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_O_CHAMAL_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_O_CHAMAL_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertO_chamalSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertO_chamalSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_O_CHAMAL_TO_THRESH    = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_O_CHAMAL_LSB_MSGSTS   = (U1)3U;
    static const U1 u1_s_ALERT_O_CHAMAL_LSB_CHAW_BZR = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G92_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                          u2_s_ALERT_O_CHAMAL_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_O_CHAMAL_LSB_MSGSTS);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_CHAWID, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_CHAW_BZR, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_O_CHAMAL_LSB_CHAW_BZR);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertO_chamalRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertO_chamalRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
#ifdef ComConf_ComSignal_LW /* 130D_CAN */
    static const U4 u4_s_ALERT_O_CHAMAL_RWTX_CRT    = (U4)(((U4)1U << ALERT_REQ_O_CHAMAL_MALFUNC      )
                                                         | ((U4)1U << ALERT_REQ_O_CHAMAL_INSPECTION   )
                                                         | ((U4)1U << ALERT_REQ_O_CHAMAL_MALFUNC_BZ   )
                                                         | ((U4)1U << ALERT_REQ_O_CHAMAL_INSPECTION_BZ));
    static const U1 u1_s_ALERT_O_CHAMAL_RWTX_MSK    = (U1)0x07U;
    static const U4 u4_s_ALERT_O_CHAMAL_TIM_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
    U1              u1_t_sgnl;
    U4              u4_t_rw;

    u4_t_rw = ((U4)1U << (u1_a_DST & u1_s_ALERT_O_CHAMAL_RWTX_MSK));

    if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON)        != (U1)0U                         ) &&
       (u4_a_IGN_TM                              >= u4_s_ALERT_O_CHAMAL_TIM_RW_ENBL) &&
       ((u4_t_rw & u4_s_ALERT_O_CHAMAL_RWTX_CRT) != (U4)0U                         )){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_LW, &u1_t_sgnl);
#endif /* ComConf_ComSignal_LW */ /* 130D_CAN */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     4/27/2020  ZS       New.                                                                                               */
/*  5.1.0    12/ 8/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.1.1     3/26/2021  MO       Update for 840B CV(Version update).                                                                */
/*                                                                                                                                   */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
