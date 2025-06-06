/* 5.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_ACONOF                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_ACONOF_C_MAJOR                   (5)
#define ALERT_H_ACONOF_C_MINOR                   (2)
#define ALERT_H_ACONOF_C_PATCH                   (1)

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
#if (ALERT_H_ACONOF_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_ACONOF.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_ACONOF_NUM_DST                   (32U)

#define ALERT_H_ACONOF_NUM_VSP_MSG               (8U)
#define ALERT_H_ACONOF_NUM_PTSYS                 (8U)
#define ALERT_H_ACONOF_DISPINFO_UNKNOWN          (0U)
#define ALERT_H_ACONOF_DISPINFO_START            (1U)
#define ALERT_H_ACONOF_DISPINFO_STOP1            (2U)
#define ALERT_H_ACONOF_DISPINFO_STOP2            (3U)
#define ALERT_H_ACONOF_DISPINFO_STOP3            (4U)
#define ALERT_H_ACONOF_DISPINFO_START2           (5U)

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
static U4      u4_s_AlertH_aconofSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_aconofDsp      (void);
static U1      u1_s_AlertH_aconofPtsysInfo(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_ACONOF_DST[ALERT_H_ACONOF_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_H_ACONOF_VSPSTART,                                           /* 01 VSPSTART                                        */
    (U1)ALERT_REQ_H_ACONOF_VSPSTOP1,                                           /* 02 VSPSTOP1                                        */
    (U1)ALERT_REQ_H_ACONOF_VSPSTOP2,                                           /* 03 VSPSTOP2                                        */
    (U1)ALERT_REQ_H_ACONOF_VSPSTOP3,                                           /* 04 VSPSTOP3                                        */
    (U1)ALERT_REQ_H_ACONOF_VSPSTART2,                                          /* 05 VSPSTART2                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_ACONOF_MTRX[1] = {
    {
        &u4_s_AlertH_aconofSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_ACONOF_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_H_ACONOF_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_aconofSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_aconofSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_H_ACONOF_TRSH_EHV1S94 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_ACONOF_LSB_EHV1S94  = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S94_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_H_ACONOF_TRSH_EHV1S94) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u4_t_src_chk  = u4_s_AlertH_aconofDsp();
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_H_ACONOF_LSB_EHV1S94);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_aconofDsp(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_aconofDsp(void)
{
    static const U1 u1_s_ALERT_H_ACONOF_VSP_STOPPED = (U1)0x03U;
    static const U1 u1_sp_ALERT_H_ACONOF_VSP_MSG[ALERT_H_ACONOF_NUM_VSP_MSG] = {
        (U1)ALERT_H_ACONOF_DISPINFO_UNKNOWN,
        (U1)ALERT_H_ACONOF_DISPINFO_START,
        (U1)ALERT_H_ACONOF_DISPINFO_STOP1,
        (U1)ALERT_H_ACONOF_DISPINFO_UNKNOWN,
        (U1)ALERT_H_ACONOF_DISPINFO_UNKNOWN,
        (U1)ALERT_H_ACONOF_DISPINFO_UNKNOWN,
        (U1)ALERT_H_ACONOF_DISPINFO_START2,
        (U1)ALERT_H_ACONOF_DISPINFO_UNKNOWN
    };
    U1              u1_t_sgnl;
    U4              u4_t_dispinfo;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_VSP_MSG, &u1_t_sgnl);

    if(u1_s_ALERT_H_ACONOF_VSP_STOPPED == u1_t_sgnl){
        u4_t_dispinfo = (U4)u1_s_AlertH_aconofPtsysInfo();
    }
    else if((U1)ALERT_H_ACONOF_NUM_VSP_MSG <= u1_t_sgnl){
        u4_t_dispinfo = (U4)ALERT_H_ACONOF_DISPINFO_UNKNOWN;
    }
    else{
        u4_t_dispinfo = (U4)u1_sp_ALERT_H_ACONOF_VSP_MSG[u1_t_sgnl];
    }

    return(u4_t_dispinfo);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertH_aconofPtsysInfo(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertH_aconofPtsysInfo(void)
{
    static const U1 u1_s_ALERT_H_ACONOF_PTSYS_MAX = (U1)8U;
    static const U1 u1_s_ALERT_H_ACONOF_PTSYS_NRX = (U1)0x1FU;
    static const U1 u1_sp_ALERT_H_ACONOF_PTSYS_INFO[ALERT_H_ACONOF_NUM_PTSYS] = {
        (U1)ALERT_H_ACONOF_DISPINFO_UNKNOWN,
        (U1)ALERT_H_ACONOF_DISPINFO_UNKNOWN,
        (U1)ALERT_H_ACONOF_DISPINFO_UNKNOWN,
        (U1)ALERT_H_ACONOF_DISPINFO_STOP2,
        (U1)ALERT_H_ACONOF_DISPINFO_STOP2,
        (U1)ALERT_H_ACONOF_DISPINFO_STOP3,
        (U1)ALERT_H_ACONOF_DISPINFO_STOP2,
        (U1)ALERT_H_ACONOF_DISPINFO_STOP2
    };
    U1              u1_t_sgnl;
    U1              u1_t_ptsysinfo;

    u1_t_sgnl = u1_g_AlertPtsys();

    if(u1_s_ALERT_H_ACONOF_PTSYS_NRX      == u1_t_sgnl){
        u1_t_ptsysinfo = (U1)ALERT_H_ACONOF_DISPINFO_STOP2;
    }
    else if(u1_s_ALERT_H_ACONOF_PTSYS_MAX <= u1_t_sgnl){
        u1_t_ptsysinfo = (U1)ALERT_H_ACONOF_DISPINFO_UNKNOWN;
    }
    else{
        u1_t_ptsysinfo = u1_sp_ALERT_H_ACONOF_PTSYS_INFO[u1_t_sgnl];
    }

    return(u1_t_ptsysinfo);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     4/ 9/2020  TH       New.                                                                                               */
/*  5.0.1     9/ 9/2020  MO       This file was renamed.                                                                             */
/*  5.1.0    12/15/2020  KT       Update for 032D CV(Version update).                                                                */
/*  5.2.0     2/10/2021  RI       Added Communication disruption Judgement.                                                          */
/*  5.2.1     1/19/2022  HU       Update for 840B #2 CV(Version update).                                                             */
/*                                                                                                                                   */
/*  * TH   = Takuya Hiraide, NTTD MSE                                                                                                */
/*  * MO   = Masaya Ozawa, NTTD MSE                                                                                                  */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * RI   = Ren Itou, NTTD MSE                                                                                                      */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
