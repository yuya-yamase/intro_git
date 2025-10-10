/* 2.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Control sensors for Tripcom                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_CFG_C_MAJOR                    (2)
#define TRIPSNSR_CFG_C_MINOR                    (1)
#define TRIPSNSR_CFG_C_PATCH                    (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripsnsr_cfg_private.h"
#include "oxcan.h"
#include "gpt_drv_frt.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPSNSR_CFG_C_MAJOR != TRIPSNSR_H_MAJOR) || \
     (TRIPSNSR_CFG_C_MINOR != TRIPSNSR_H_MINOR) || \
     (TRIPSNSR_CFG_C_PATCH != TRIPSNSR_H_PATCH))
#error "tripsnsr_cfg.c and tripsnsr.h : source and header files are inconsistent!"
#endif

#if ((TRIPSNSR_CFG_C_MAJOR != TRIPSNSR_CFG_H_MAJOR) || \
     (TRIPSNSR_CFG_C_MINOR != TRIPSNSR_CFG_H_MINOR) || \
     (TRIPSNSR_CFG_C_PATCH != TRIPSNSR_CFG_H_PATCH))
#error "tripsnsr_cfg.c and tripsnsr_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TRIPCOM_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (TRIPCOM_STSBIT_INVALID != COM_TIMEOUT))
#error "tripcom status bit and com status bit are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_PLG1S06_FAILTIM                (5000U/OXCAN_MAIN_TICK)
#define TRIPSNSR_EHV1S31_FAILTIM                (5000U/OXCAN_MAIN_TICK)
#define TRIPSNSR_EHV1S96_FAILTIM                (3600U/OXCAN_MAIN_TICK)
#define TRIPSNSR_ENG1S28_FAILTIM                (10000U/OXCAN_MAIN_TICK)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U4      u4_sp_tripsnsr_elpsdtm_frt[GPT_FRT_USELPSD_NUM_PARAM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const   ST_TRIPSNSR_CNTTS                       st_gp_TRIPSNSR_CNTTS_CFG[TRIPSNSR_NUM_SNSR]         = {
    {   &vd_g_TripsnsrElpsdtmInit,  &vd_g_TripsnsrElpsdtmSmplngTask,    &u2_g_TripsnsrElpsdtmGetDelta,  vdp_PTR_NA                   },
    {   vdp_PTR_NA,                 vdp_PTR_NA,                         vdp_PTR_NA,                     vdp_PTR_NA                   },
    {   vdp_PTR_NA,                 vdp_PTR_NA,                         vdp_PTR_NA,                     vdp_PTR_NA                   },
    {   &vd_g_TripsnsrOdocntInit,   &vd_g_TripsnsrOdocntSmplngTask,     &u2_g_TripsnsrOdocntGetDelta,   vdp_PTR_NA                   },
    {   &vd_g_TripsnsrAvgeeInit,    &vd_g_TripsnsrAvgeeSmplngTask,      &u2_g_TripsnsrAvgeeGetDelta,    vdp_PTR_NA                   },
    {   &vd_g_TripsnsrInsteeInit,   &vd_g_TripsnsrInsteeSmplngTask,     &u2_g_TripsnsrInsteeGetDelta,   &u1_g_TripsnsrInsteeRxReset  },
    {   vdp_PTR_NA,                 vdp_PTR_NA,                         vdp_PTR_NA,                     vdp_PTR_NA                   },
    {   vdp_PTR_NA,                 vdp_PTR_NA,                         &u2_g_TripsnsrOdocntEmgfGetDelta,vdp_PTR_NA                  }
};
const   U4                                      u4_g_TRIPSNSR_ELPSDTM_FRT_1US                       = (U4)GPT_FRT_1US;  /*  1 [us]   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgEcoMode(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgEcoMode(void)
{
    /* Exist eco-run mode or not from Variation */
    return ((U1)FALSE);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgGetECOMODE3(U1 * u1p_a_ecomode)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgGetECOMODE3(U1 * u1p_a_ecomode)
{
#if 0   /* BEV Rebase provisionally */
#if defined(ComConf_ComSignal_ECOMODE3)
    (void)Com_ReceiveSignal(ComConf_ComSignal_ECOMODE3, u1p_a_ecomode);
    return ((U1)Com_GetIPDUStatus(MSG_ECO1S90_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX));
#else
    (*u1p_a_ecomode) = (U1)0U;
    return ((U1)TRIPCOM_STSBIT_INVALID);
#endif
#else   /* BEV Rebase provisionally */
    (*u1p_a_ecomode) = (U1)0U;
    return ((U1)TRIPCOM_STSBIT_INVALID);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgGetPtsSts(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgGetPtsSts(void)
{
    U1          u1_t_msgsts;
    U1          u1_t_calib;

    u1_t_msgsts = (U1)TRIPCOM_STSBIT_UNKNOWN;
    u1_t_calib  = u1_CALIB_MCUID0237_CANMOVEFLAG;

    if (u1_t_calib == (U1)CALIB_MCUID0237_NE1) {
#if 0   /* BEV Rebase provisionally */
        u1_t_msgsts = (U1)Com_GetIPDUStatus(MSG_ENG1G02_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#endif   /* BEV Rebase provisionally */
    }
    else {
#if 0   /* BEV Rebase provisionally */
        u1_t_msgsts = (U1)Com_GetIPDUStatus(MSG_ENG1G90_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#endif   /* BEV Rebase provisionally */
    }

    return (u1_t_msgsts);
}

/*===================================================================================================================================*/
/* void            vd_g_TripsnsrCfgElpsdtmInit(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrCfgElpsdtmInit(void)
{
    u4_sp_tripsnsr_elpsdtm_frt[GPT_FRT_USELPSD_BASE]  = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
    u4_sp_tripsnsr_elpsdtm_frt[GPT_FRT_USELPSD_CRRNT] = (U4)0U;
}

/*===================================================================================================================================*/
/* U4              u4_g_TripsnsrCfgElpsdtmGetDlt(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4              u4_g_TripsnsrCfgElpsdtmGetDlt(void)
{
    U4          u4_t_frt_elpsd;

    u4_t_frt_elpsd = u4_g_Gpt_FrtGetUsElapsed(&u4_sp_tripsnsr_elpsdtm_frt[0]);
    u4_sp_tripsnsr_elpsdtm_frt[GPT_FRT_USELPSD_BASE] = u4_sp_tripsnsr_elpsdtm_frt[GPT_FRT_USELPSD_CRRNT];

    return (u4_t_frt_elpsd);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgGetBFC(U4 * u4p_a_fuel_inst)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgGetBFC(U4 * u4p_a_fuel_inst)
{
    U1          u1_t_msgsts;
    U2          u2_t_bfc;


#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_FC, &u2_t_bfc);
#else   /* BEV Rebase provisionally */
    u2_t_bfc = (U1)0U;
#endif   /* BEV Rebase provisionally */
    (*u4p_a_fuel_inst) = (U4)u2_t_bfc;
#if 0   /* BEV Rebase provisionally */
    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S28,
                                        (U2)(OXCAN_RX_SYS_NRX_IGP | OXCAN_RX_SYS_TOE_IGP),
                                        (U2)TRIPSNSR_ENG1S28_FAILTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else   /* BEV Rebase provisionally */
    u1_t_msgsts = (U1)COM_NO_RX;
#endif   /* BEV Rebase provisionally */

    return (u1_t_msgsts);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgRxCntBFC(U1 * u1p_a_rollcnt)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgRxCntBFC(U1 * u1p_a_rollcnt)
{
    U1          u1_t_status;

#if 0   /* BEV Rebase provisionally */
    (*u1p_a_rollcnt) = u1_g_oXCANRxEvcnt((U2)OXCAN_PDU_RX_CAN_ENG1S28);

    u1_t_status = (U1)TRIPCOM_STSBIT_VALID;
    if ((*u1p_a_rollcnt) == (U1)OXCAN_RX_RXEV_CNT_UNK) {
        u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
    }
#else   /* BEV Rebase provisionally */
    (*u1p_a_rollcnt) == (U1)OXCAN_RXD_EVC_UNK;
    u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
#endif   /* BEV Rebase provisionally */

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgGetCNSMH2(U4 * u4p_a_hydr_inst)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgGetCNSMH2(U4 * u4p_a_hydr_inst)
{
    U1          u1_t_msgsts;

    (*u4p_a_hydr_inst) = (U4)0U;
    u1_t_msgsts = (U1)TRIPCOM_STSBIT_VALID;

    return (u1_t_msgsts);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgRxCntCNSMH2(U1 * u1p_a_rollcnt)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgRxCntCNSMH2(U1 * u1p_a_rollcnt)
{
    U1          u1_t_status;

#if 0   /* BEV Rebase provisionally */
    (*u1p_a_rollcnt) = (U1)OXCAN_RX_RXEV_CNT_UNK;
#else   /* BEV Rebase provisionally */
    (*u1p_a_rollcnt) = (U1)OXCAN_RXD_EVC_UNK;
#endif   /* BEV Rebase provisionally */

    u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* void              vd_g_TripsnsrCfgEvDteDist(U2 * u2p_a_dist)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void              vd_g_TripsnsrCfgEvDteDist(U2 * u2p_a_dist)
{
#if defined(ComConf_ComSignal_PIEVD06)
    U2          u2_t_dist;

    u2_t_dist = (U2)0U;
#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_PIEVD06, &u2_t_dist);
#endif   /* BEV Rebase provisionally */
    (*u2p_a_dist) = u2_t_dist;
#else
    (*u2p_a_dist) = (U2)0U;
#endif
}

/*===================================================================================================================================*/
/* void              vd_g_TripsnsrCfgEvDteSubRate(U1 * u1p_a_subrate)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void              vd_g_TripsnsrCfgEvDteSubRate(U1 * u1p_a_subrate)
{
#if defined(ComConf_ComSignal_PIEVDSR)
    U1          u1_t_subrate;

    u1_t_subrate = (U1)0U;
#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_PIEVDSR, &u1_t_subrate);
#endif   /* BEV Rebase provisionally */
    (*u1p_a_subrate) = u1_t_subrate;
#else
    (*u1p_a_subrate) = (U1)0U;
#endif
}

/*===================================================================================================================================*/
/* void              vd_g_TripsnsrCfgEvDtePIEVE06(U1 * u1p_a_pieve06)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void              vd_g_TripsnsrCfgEvDtePIEVE06(U1 * u1p_a_pieve06)
{
    U1          u1_t_pieve06;
    
    u1_t_pieve06 = (U1)0U;
#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_PIEVE06, &u1_t_pieve06);
#endif   /* BEV Rebase provisionally */
    (*u1p_a_pieve06) = u1_t_pieve06;

}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgEvDteCNGPIEVD(U1 * u1p_a_cngpievd)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgEvDteCNGPIEVD(U1 * u1p_a_cngpievd)
{
#if 0   /* BEV Rebase provisionally */
#if defined(ComConf_ComSignal_CNGPIEVD)
    U1          u1_t_msgsts;

    u1_t_msgsts =  u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S31,
                                         (U2)(OXCAN_RX_SYS_NRX_IGR | OXCAN_RX_SYS_TOE_IGR),
                                         (U2)U2_MAX) & ((U1)TRIPSNSR_EVDTE_INVALID | (U1)TRIPSNSR_EVDTE_UNKNOWN);
    (void)Com_ReceiveSignal(ComConf_ComSignal_CNGPIEVD, u1p_a_cngpievd);
    return(u1_t_msgsts);

#else
    *u1p_a_cngpievd = (U1)0U;
    return((U1)TRIPSNSR_EVDTE_UNKNOWN);
#endif
#else   /* BEV Rebase provisionally */
    *u1p_a_cngpievd = (U1)0U;
    return((U1)TRIPSNSR_EVDTE_UNKNOWN);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgEvDteSts(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgEvDteSts(void)
{
    U1          u1_t_sts;
    U1          u1_t_ret;

    u1_t_ret = (U1)TRIPSNSR_EVDTE_VALID;
    
#if 0   /* BEV Rebase provisionally */
    u1_t_sts  =  u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PLG1S06,
                                       (U2)(OXCAN_RX_SYS_NRX_IGR | OXCAN_RX_SYS_TOE_IGR),
                                       (U2)TRIPSNSR_PLG1S06_FAILTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else   /* BEV Rebase provisionally */
    u1_t_sts = (U1)COM_NO_RX;
#endif   /* BEV Rebase provisionally */

    u1_t_sts |= u1_g_TripsnsrCfgGetPtsSts();

    if((u1_t_sts & (U1)COM_TIMEOUT) != (U1)0U){

        u1_t_ret = (U1)TRIPSNSR_EVDTE_INVALID;
    }
    
    if((u1_t_sts & (U1)COM_NO_RX) != (U1)0U){

        u1_t_ret |= (U1)TRIPSNSR_EVDTE_UNKNOWN;
    }


    return (u1_t_ret);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgEvDteBatSts(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgEvDteBatSts(void)
{
    U1          u1_t_sts;
    U1          u1_t_ret;

    u1_t_ret = (U1)TRIPSNSR_EVDTE_VALID;

#if 0   /* BEV Rebase provisionally */
    u1_t_sts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PLG1S06,
                                (U2)(OXCAN_RX_SYS_NRX_BAT | OXCAN_RX_SYS_TOE_BAT),
                                (U2)TRIPSNSR_PLG1S06_FAILTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else   /* BEV Rebase provisionally */
    u1_t_sts = (U1)COM_NO_RX;
#endif   /* BEV Rebase provisionally */

    if((u1_t_sts & (U1)COM_TIMEOUT) != (U1)0U){
        u1_t_ret = (U1)TRIPSNSR_EVDTE_INVALID;
    }

    if((u1_t_sts & (U1)COM_NO_RX) != (U1)0U){
        u1_t_ret |= (U1)TRIPSNSR_EVDTE_UNKNOWN;
    }

    return (u1_t_ret);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgGetInsEpusd(S4 * s4p_a_insepusd)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgGetInsEpusd(S4 * s4p_a_insepusd)
{
#if 0   /* BEV Rebase provisionally */
#if defined(ComConf_ComSignal_INS_BATE) && defined(OXCAN_PDU_RX_CAN_EHV1S31)
    U1          u1_t_msgsts;
    S2          s2_t_insepusd;

    s2_t_insepusd = (S2)0;
    (void)Com_ReceiveSignal(ComConf_ComSignal_INS_BATE, &s2_t_insepusd);
    (*s4p_a_insepusd) = (S4)s2_t_insepusd;
    u1_t_msgsts =  u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S31,
                                         (U2)(OXCAN_RX_SYS_NRX_IGR | OXCAN_RX_SYS_TOE_IGR),
                                         (U2)TRIPSNSR_EHV1S31_FAILTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return (u1_t_msgsts);
#else
    (*s4p_a_insepusd) = (S4)0; 
    return ((U1)COM_NO_RX);
#endif
#else   /* BEV Rebase provisionally */
    (*s4p_a_insepusd) = (S4)0; 
    return ((U1)COM_NO_RX);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgGetInsEvdist(U4 * u4p_a_evdist)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgGetInsEvdist(U4 * u4p_a_evdist)
{
#if 0   /* BEV Rebase provisionally */
#if defined(ComConf_ComSignal_INS_EVD) && defined(OXCAN_PDU_RX_CAN_EHV1S31)
    U1          u1_t_msgsts;
    U2          u2_t_evdist;

    u2_t_evdist = (U2)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_INS_EVD, &u2_t_evdist);
    (*u4p_a_evdist) = (U4)u2_t_evdist;
    u1_t_msgsts =  u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S31,
                                         (U2)(OXCAN_RX_SYS_NRX_IGR | OXCAN_RX_SYS_TOE_IGR),
                                         (U2)TRIPSNSR_EHV1S31_FAILTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return (u1_t_msgsts);
#else
    (*u4p_a_evdist) = (U4)0U;
    return ((U1)COM_NO_RX);
#endif
#else   /* BEV Rebase provisionally */
    (*u4p_a_evdist) = (U4)0U;
    return ((U1)COM_NO_RX);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgGetInsUpdtflg(U1 * u1p_a_updtflg)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgGetInsUpdtflg(U1 * u1p_a_updtflg)
{
#if 0   /* BEV Rebase provisionally */
#if defined(ComConf_ComSignal_INS_UPD) && defined(OXCAN_PDU_RX_CAN_EHV1S31)
    U1          u1_t_msgsts;
    U1          u1_t_updtflg;

    u1_t_updtflg = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_INS_UPD, &u1_t_updtflg);
    (*u1p_a_updtflg) = u1_t_updtflg;
    u1_t_msgsts =  u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S31,
                                         (U2)(OXCAN_RX_SYS_NRX_IGR | OXCAN_RX_SYS_TOE_IGR),
                                         (U2)TRIPSNSR_EHV1S31_FAILTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return (u1_t_msgsts);
#else
    (*u1p_a_updtflg) = (U1)0U;
    return ((U1)COM_NO_RX);
#endif
#else   /* BEV Rebase provisionally */
    (*u1p_a_updtflg) = (U1)0U;
    return ((U1)COM_NO_RX);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgGetEpusd(S4 * s4p_a_epusd)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgGetEpusd(S4 * s4p_a_epusd)
{
#if 0   /* BEV Rebase provisionally */
#if defined(ComConf_ComSignal_EC_MON) && defined(OXCAN_PDU_RX_CAN_EHV1S96)
    U1          u1_t_msgsts;
    S2          s2_t_epusd;


    s2_t_epusd = (S2)0;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EC_MON, &s2_t_epusd);
    (*s4p_a_epusd) = (S4)s2_t_epusd;
    u1_t_msgsts =  u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S96,
                                         (U2)(OXCAN_RX_SYS_NRX_IGP | OXCAN_RX_SYS_TOE_IGP),
                                         (U2)TRIPSNSR_EHV1S96_FAILTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return (u1_t_msgsts);
#else
    (*s4p_a_epusd) = (S4)0;
    return ((U1)COM_NO_RX);
#endif
#else   /* BEV Rebase provisionally */
    (*s4p_a_epusd) = (S4)0;
    return ((U1)COM_NO_RX);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrCfgGetEpUpdflg(U1 * u1p_a_epupdflg)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrCfgGetEpUpdflg(U1 * u1p_a_epupdflg)
{
#if 0   /* BEV Rebase provisionally */
#if defined(ComConf_ComSignal_RNEC_MON) && defined(OXCAN_PDU_RX_CAN_EHV1S96)
    U1          u1_t_msgsts;
    U1          u1_t_epupdflg;


    u1_t_epupdflg = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RNEC_MON, &u1_t_epupdflg);
    (*u1p_a_epupdflg) = u1_t_epupdflg;
    u1_t_msgsts =  u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S96,
                                         (U2)(OXCAN_RX_SYS_NRX_IGP | OXCAN_RX_SYS_TOE_IGP),
                                         (U2)TRIPSNSR_EHV1S96_FAILTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    return (u1_t_msgsts);
#else
    (*u1p_a_epupdflg) = (U1)0U;
    return ((U1)COM_NO_RX);
#endif
#else   /* BEV Rebase provisionally */
    (*u1p_a_epupdflg) = (U1)0U;
    return ((U1)COM_NO_RX);
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
/*  1.0.0    11/07/2018  HY       New.                                                                                               */
/*  1.1.0    03/23/2020  YA       Change for 800B CV                                                                                 */
/*  1.1.1    07/27/2020  YA       Change status to be determined only during IG-ON                                                   */
/*  2.0.1    10/18/2021  TA(M)    tripsnsr.c v1.1.1 -> v2.0.1.                                                                       */
/*  2.0.2    10/27/2021  TK       tripsnsr.c v2.0.1 -> v2.0.2.                                                                       */
/*  2.1.0    04/14/2022  TA(M)    tripsnsr.c v2.0.2 -> v2.1.0.                                                                       */
/*  2.1.1    08/08/2022  YI       tripsnsr.c v2.1.0 -> v2.1.1.                                                                       */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/*  19PFv3-1 02/12/2024  PG       Change  for MET-M_DMEVRNGE-CSTD-1-07-A-C1                                                          */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
