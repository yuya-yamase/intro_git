/* 5.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_BATTRW                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_BATTRW_C_MAJOR                      (5)
#define ALERT_H_BATTRW_C_MINOR                      (5)
#define ALERT_H_BATTRW_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_H_BATTRW_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_BATTRW.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_BATTRW_PD_NUM_DST                (8U)
#define ALERT_H_BATTRW_BC_NUM_DST                (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_h_battrw_msgsts_pd;
static U1      u1_s_alert_h_battrw_msgsts_bc;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertH_battrwPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertH_battrwBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_H_BATTRW_PD_DST[ALERT_H_BATTRW_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_H_BATTRW_PD_THERMALPD,                                       /* 05 THERMALPD                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_H_BATTRW_BC_DST[ALERT_H_BATTRW_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_H_BATTRW_BC_THERMALBC,                                       /* 09 THERMALBC                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};


/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_BATTRW_MTRX[2] = {
    {
        &u4_s_AlertH_battrwPdSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_BATTRW_PD_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_H_BATTRW_PD_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertH_battrwBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_BATTRW_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_H_BATTRW_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertH_battrwInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertH_battrwInit(void)
{
    u1_s_alert_h_battrw_msgsts_pd = (U1)COM_NO_RX;
    u1_s_alert_h_battrw_msgsts_bc = (U1)COM_NO_RX;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_battrwPdSrcchk      (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_VOM                                                                                                         */
/*                  u4_a_IGN_TM                                                                                                      */
/*                  u1_a_LAS                                                                                                         */
/*  Return:         u4_t_src_chk                                                                                                     */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_battrwPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U1 u1_s_ALERT_H_BATTRW_PD_LSB_BAT1E48 = (U1)1U;
    static const U4 u4_s_ALERT_H_BATTRW_PD_BIT_BAT_WT  = (U4)0x00000004U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BAT1E48,
                                   (U2)OXCAN_RX_SYS_NRX_BAT,
                                   (U2)U2_MAX) & (U1)COM_NO_RX;
    vd_g_AlertBRxTrnsSts(&u1_s_alert_h_battrw_msgsts_pd, u1_t_msgsts);

    u4_t_src_chk = (((U4)u1_s_alert_h_battrw_msgsts_pd & (U4)COM_NO_RX) << u1_s_ALERT_H_BATTRW_PD_LSB_BAT1E48);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BTRDISP, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_H_BATTRW_PD_BIT_BAT_WT;
    }

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_battrwBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_VOM                                                                                                         */
/*                  u4_a_IGN_TM                                                                                                      */
/*                  u1_a_LAS                                                                                                         */
/*  Return:         u4_t_src_chk                                                                                                     */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_battrwBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if 0   /* BEV Rebase provisionally */
    static const U2 u2_s_ALERT_H_BATTRW_BC_TO_THRESH   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_H_BATTRW_BC_LSB_BAT1E48 = (U1)1U;
    static const U4 u4_s_ALERT_H_BATTRW_BC_BIT_BAT_WT  = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BTRBUZZ, &u1_t_sgnl);

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_BAT1E48,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     (U2)u2_s_ALERT_H_BATTRW_BC_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_h_battrw_msgsts_bc, u1_t_msgsts);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_h_battrw_msgsts_bc << u1_s_ALERT_H_BATTRW_BC_LSB_BAT1E48);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_H_BATTRW_BC_BIT_BAT_WT;
    }

    return(u4_t_src_chk);
#else   /* BEV Rebase provisionally */
    return((U4)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.5.0    3/17/2025   SH       Newly created for 19PFv3                                                                           */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
