/* 5.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert O_PDSMAL                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_O_PDSMAL_C_MAJOR                      (5)
#define ALERT_O_PDSMAL_C_MINOR                      (0)
#define ALERT_O_PDSMAL_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_O_PDSMAL_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_O_PDSMAL.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_O_PDSMAL_BC_NUM_DST                (16U)
#define ALERT_O_PDSMAL_PD_NUM_DST                (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_BUZ)
static U1      u1_s_alert_o_pdsmal_cycl_sts;
#endif /* defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_BUZ) */
#if defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_DISP)
static U1      u1_s_alert_o_pdsmal_mulfunc_sts;
#endif /* defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_DISP) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertO_pdsmalBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertO_pdsmalPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_O_PDSMAL_BC_DST[ALERT_O_PDSMAL_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_O_PDSMAL_BC_CYCL,                                            /* 09 CYCL                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_O_PDSMAL_PD_DST[ALERT_O_PDSMAL_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_O_PDSMAL_PD_MULFUNC,                                         /* 09 MULFUNC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_O_PDSMAL_MTRX[2] = {
    {
        &u4_s_AlertO_pdsmalBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_O_PDSMAL_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_O_PDSMAL_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertO_pdsmalPdSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_O_PDSMAL_PD_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_O_PDSMAL_PD_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertO_pdsmalInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertO_pdsmalInit(void)
{
#if defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_BUZ)
    u1_s_alert_o_pdsmal_cycl_sts = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_BUZ) */
#if defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_DISP)
    u1_s_alert_o_pdsmal_mulfunc_sts = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_DISP) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertO_pdsmalBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertO_pdsmalBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_BUZ)
    static const U1 u1_s_ALERT_O_PDSMAL_LSB_BC_MSGSTS  = (U1)2U;
    static const U4 u4_s_ALERT_O_PDSMAL_BIT_BC_BTWT    = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_PDU_RX_CAN_BDC1S46_RXCH0,
                                          (U4)ALERT_CAN_SYS_PNC_ALL,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
    vd_g_AlertBRxTrnsSts(&u1_s_alert_o_pdsmal_cycl_sts, u1_t_msgsts);

    u4_t_src_chk  = (((U4)u1_s_alert_o_pdsmal_cycl_sts & (U4)COM_NO_RX) << u1_s_ALERT_O_PDSMAL_LSB_BC_MSGSTS);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PDS_BUZ, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_O_PDSMAL_BIT_BC_BTWT;
    }

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_BUZ) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertO_pdsmalPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertO_pdsmalPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_DISP)
    static const U1 u1_s_ALERT_O_PDSMAL_LSB_PD_MSGSTS  = (U1)2U;
    static const U4 u4_s_ALERT_O_PDSMAL_BIT_PD_BTWT    = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_PDU_RX_CAN_BDC1S46_RXCH0,
                                          (U4)ALERT_CAN_SYS_PNC_ALL,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
    vd_g_AlertBRxTrnsSts(&u1_s_alert_o_pdsmal_mulfunc_sts, u1_t_msgsts);

    u4_t_src_chk  = (((U4)u1_s_alert_o_pdsmal_mulfunc_sts & (U4)COM_NO_RX) << u1_s_ALERT_O_PDSMAL_LSB_PD_MSGSTS);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_PDS_DISP, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_O_PDSMAL_BIT_PD_BTWT;
    }

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_BDC1S46_RXCH0) && defined(ComConf_ComSignal_PDS_DISP) */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0    06/20/2025  KO       New.                                                                                               */
/*                                                                                                                                   */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/