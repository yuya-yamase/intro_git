/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Variation Defines / Organized Master Unified System Vehicle Information                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_OMUS_CAN_CFG_C_MAJOR                 (1)
#define VARDEF_OMUS_CAN_CFG_C_MINOR                 (0)
#define VARDEF_OMUS_CAN_CFG_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_omus_cfg_private.h"
#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_OMUS_CAN_CFG_C_MAJOR != VARDEF_OMUS_CFG_H_MAJOR) || \
     (VARDEF_OMUS_CAN_CFG_C_MINOR != VARDEF_OMUS_CFG_H_MINOR) || \
     (VARDEF_OMUS_CAN_CFG_C_PATCH != VARDEF_OMUS_CFG_H_PATCH))
#error "vardef_omus_can_cfg.c and vardef_omus_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_OMUS_CAN_CFG_C_MAJOR != VARDEF_OMUS_CAN_CFG_PRIV_H_MAJOR) || \
     (VARDEF_OMUS_CAN_CFG_C_MINOR != VARDEF_OMUS_CAN_CFG_PRIV_H_MINOR) || \
     (VARDEF_OMUS_CAN_CFG_C_PATCH != VARDEF_OMUS_CAN_CFG_PRIV_H_PATCH))
#error "vardef_omus_can_cfg.c and vardef_omus_can_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
static U1    u1_s_VardefOmusCfgBDC1SV2Rx(void);
static U1    u1_s_VardefOmusCfgBDB1S08Rx(void);

static U1    u1_s_VardefOmusCfgTSLCLR_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgRRCT_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgRLCT_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgLGTR_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgHDCT_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgRPSD_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgLPSD_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgRRDR_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgRRODS_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgRCODS_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgRLODS_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgR2RODS_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgR2CODS_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgR2LODS_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgR3RODS_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgR3CODS_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgR3LODS_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgFBWTH_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgMETSRT_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgMETCPD_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgOMBINF_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgSPMKM_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgSPMMPH_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgSPMFSP_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgDIMFTL_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgMETCSR_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgMETCTT_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgBRAND_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgMETSPO_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgBDSTL_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgFC_SCL_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgEC_SCL_B(U1 * u1p_a_canrx);
static U1    u1_s_VardefOmusCfgCSWPOS_B(U1 * u1p_a_canrx);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1                     u1_g_VDF_OMUS_RXC_UNK = (U1)OXCAN_RXD_EVC_UNK;
const U1                     u1_g_VDF_OMUS_RXC_MAX = (U1)OXCAN_RXD_EVC_MAX;

const ST_VDF_OMUS_CAN_RX_CFG      st_gp_VDF_OMUS_CAN_RX_CFG[VDF_OMUS_CAN_NUM] = {
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgTSLCLR_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgRRCT_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgRLCT_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgLGTR_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgHDCT_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgRPSD_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgLPSD_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgRRDR_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgRRODS_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgRCODS_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgRLODS_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgR2RODS_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgR2CODS_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgR2LODS_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgR3RODS_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgR3CODS_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgR3LODS_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgFBWTH_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgMETSRT_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgMETCPD_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgOMBINF_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgSPMKM_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgSPMMPH_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgSPMFSP_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgDIMFTL_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgMETCSR_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgMETCTT_B,
    },
    {
        &u1_s_VardefOmusCfgBDB1S08Rx,
        &u1_s_VardefOmusCfgBRAND_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgMETSPO_B,
    },
    {
        &u1_s_VardefOmusCfgBDB1S08Rx,
        &u1_s_VardefOmusCfgBDSTL_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgFC_SCL_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgEC_SCL_B,
    },
    {
        &u1_s_VardefOmusCfgBDC1SV2Rx,
        &u1_s_VardefOmusCfgCSWPOS_B,
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U1    u1_s_VardefOmusCfgBDC1SV2Rx(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgBDC1SV2Rx(void)
{
    return(u1_g_oXCANRxdEvcnt((U2)OXCAN_RXD_PDU_CAN_BDC1SV2_CH0));
}

/*===================================================================================================================================*/
/*  static U1    u1_s_VardefOmusCfgBDB1S08Rx(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgBDB1S08Rx(void)
{
    return(u1_g_oXCANRxdEvcnt((U2)OXCAN_RXD_PDU_CAN_BDB1S08_CH0));
}

/*===================================================================================================================================*/
/*  static U1    u1_s_VardefOmusCfgTSLCLR_B(U1 * u1p_a_canrx)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgTSLCLR_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;

    (void)Com_ReceiveSignal(ComConf_ComSignal_TSLCLR_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_TSLCLR_B_RD){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_VardefOmusCfgRRCT_B(U1 * u1p_a_canrx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgRRCT_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RRCT_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_RRCT_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_VardefOmusCfgRLCT_B(U1 * u1p_a_canrx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgRLCT_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RLCT_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_RLCT_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_VardefOmusCfgLGTR_B(U1 * u1p_a_canrx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgLGTR_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LGTR_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_LGTR_B_BD){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgHDCT_B(U1 * u1p_a_canrx)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgHDCT_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_HDCT_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_HDCT_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgRPSD_B(U1 * u1p_a_canrx)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgRPSD_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RPSD_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_RPSD_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgLPSD_B(U1 * u1p_a_canrx)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgLPSD_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LPSD_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_LPSD_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgRRDR_B(U1 * u1p_a_canrx)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgRRDR_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RRDR_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_RRDR_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgRRODS_B(U1 * u1p_a_canrx)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgRRODS_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RRODS_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_RRODS_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgRCODS_B(U1 * u1p_a_canrx)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgRCODS_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RCODS_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_RCODS_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgRLODS_B(U1 * u1p_a_canrx)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgRLODS_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RLODS_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_RLODS_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgR2RODS_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgR2RODS_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_R2RODS_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_R2RODS_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgR2CODS_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgR2CODS_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_R2CODS_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_R2CODS_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgR2LODS_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgR2LODS_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_R2LODS_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_R2LODS_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgR3RODS_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgR3RODS_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_R3RODS_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_R3RODS_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgR3CODS_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgR3CODS_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_R3CODS_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_R3CODS_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgR3LODS_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgR3LODS_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_R3LODS_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_R3LODS_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgFBWTH_B(U1 * u1p_a_canrx)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgFBWTH_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FBWTH_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_FBWTH_B_ON){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgMETSRT_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgMETSRT_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_METSRT_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_METSRT_B_NORSEAT){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgMETCPD_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgMETCPD_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_METCPD_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_METCPD_B_LEFT){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgOMBINF_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgOMBINF_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_OMBINF_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_OMBINF_B_BUTTON_1){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgSPMKM_B(U1 * u1p_a_canrx)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgSPMKM_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SPMKM_B, &u1_t_sig);
    if((u1_t_sig >= (U1)VDF_OMUS_SPMKM_B_120) &&
       (u1_t_sig <= (U1)VDF_OMUS_SPMKM_B_360)){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgSPMMPH_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgSPMMPH_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SPMMPH_B, &u1_t_sig);
    if((u1_t_sig >= (U1)VDF_OMUS_SPMMPH_B_120) &&
       (u1_t_sig <= (U1)VDF_OMUS_SPMMPH_B_360)){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgSPMFSP_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgSPMFSP_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SPMFSP_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_SPMFSP_B_FSPORT){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgDIMFTL_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgDIMFTL_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DIMFTL_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_DIMFTL_B_OTHER){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgMETCSR_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgMETCSR_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_METCSR_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_METCSR_B_CHN){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgMETCTT_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgMETCTT_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_METCTT_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_METCTT_B_UNR){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgBRAND_B(U1 * u1p_a_canrx)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgBRAND_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BRAND_B, &u1_t_sig);
    if((u1_t_sig >= (U1)VDF_OMUS_BRAND_B_TOYOTA) &&
       (u1_t_sig <= (U1)VDF_OMUS_BRAND_B_GR)){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgMETSPO_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgMETSPO_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_METSPO_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_METSPO_B_F){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgBDSTL_B(U1 * u1p_a_canrx)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgBDSTL_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BDSTL_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_BDSTL_B_PICKUP_TRUCK){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgFC_SCL_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgFC_SCL_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_FC_SCL_B, &u1_t_sig);
    if((u1_t_sig >= (U1)VDF_OMUS_FC_SCL_B_NO_1) &&
       (u1_t_sig <= (U1)VDF_OMUS_FC_SCL_B_NO_6)){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgEC_SCL_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgEC_SCL_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EC_SCL_B, &u1_t_sig);
    if((u1_t_sig >= (U1)VDF_OMUS_EC_SCL_B_NO_1) &&
       (u1_t_sig <= (U1)VDF_OMUS_EC_SCL_B_NO_6)){
        u1_t_ret = (U1)TRUE;
    }
    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*   static U1    u1_s_VardefOmusCfgCSWPOS_B(U1 * u1p_a_canrx)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_VardefOmusCfgCSWPOS_B(U1 * u1p_a_canrx)
{
    U1  u1_t_sig;
    U1  u1_t_ret;

    u1_t_sig = (U1)VDF_OMUS_FF_NRX;
    u1_t_ret = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_CSWPOS_B, &u1_t_sig);
    if(u1_t_sig <= (U1)VDF_OMUS_CSWPOS_B_R_WIP_L_LIT){
        u1_t_ret = (U1)TRUE;
    }

    *u1p_a_canrx = u1_t_sig;
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     1/22/2026  SH       New.                                                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1     1/22/2026  SH       New.                                                                                               */
/*                                                                                                                                   */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
