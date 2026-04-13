/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Operational Mode for Toyota                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_TYBEV3_C_MAJOR                 (2)
#define VEH_OPEMD_TYBEV3_C_MINOR                 (1)
#define VEH_OPEMD_TYBEV3_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "veh_opemd_cfg_private.h"
#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VEH_OPEMD_TYBEV3_C_MAJOR != VEH_OPEMD_TYBEV3_H_MAJOR) || \
     (VEH_OPEMD_TYBEV3_C_MINOR != VEH_OPEMD_TYBEV3_H_MINOR) || \
     (VEH_OPEMD_TYBEV3_C_PATCH != VEH_OPEMD_TYBEV3_H_PATCH))
#error "veh_opemd_tybev3.c and veh_opemd_xmode.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_VPS_NUM_CHK                    (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_MDLSB_NM_0                     (31U)
#define VEH_OPEMD_COMRX_VALID                    (0x00U)
#define VEH_OPEMD_COMRX_UNKNOWN                  (0x01U)
#define VEH_OPEMD_COMRX_INVALID                  (0x02U)

#define VEH_OPEMD_PTS_CHK_ON                     (0x04U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2              u2_crit;
    U2              u2_mdbit;
}ST_VEH_OPEMD_VPS_CHK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2      u2_s_veh_opemd_unk_tocnt;

static U1                       u1_s_veh_opemd_pts_chk;

static U1      u1_s_veh_opemd_apofrq_onoff;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline U2      u2_s_VehopemdVpschk(const U2 u2_a_RX, const ST_VEH_OPEMD_VPS_CHK * st_ap_CHK, const U2 u2_a_NUM_CHK);
static U2             u2_s_VehopemdReadbdc1s81(void);
static U2             u2_s_VehopemdReadbdc1s91(void);
static U1             u1_s_VehopemdDiagPowOn(void);
static        void     vd_s_VehopemdPtschk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT);
static        U1       u1_s_VehopemdPtschk_RDYIND(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT);
static void            vd_s_VehopemdApofrqchk(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VehopemdCfgRstInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehopemdCfgRstInit(void)
{
    u2_s_veh_opemd_unk_tocnt = (U2)U2_MAX;
    u1_s_veh_opemd_pts_chk       = (U1)VEH_OPEMD_COMRX_UNKNOWN;
    u1_s_veh_opemd_apofrq_onoff = (U1)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_VehopemdCfgWkupInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehopemdCfgWkupInit(void)
{
    u2_s_veh_opemd_unk_tocnt = (U2)U2_MAX;
    u1_s_veh_opemd_pts_chk       = (U1)VEH_OPEMD_COMRX_UNKNOWN;
    u1_s_veh_opemd_apofrq_onoff = (U1)0U;
}
/*===================================================================================================================================*/
/*  U4      u4_g_VehopemdCfgMdupdt(const U4 u4_a_MDBIT, U4 * u4_ap_evbit)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_VehopemdCfgMdupdt(const U4 u4_a_MDBIT, U4 * u4_ap_evbit)
{
    static const ST_VEH_OPEMD_VPS_CHK    st_sp_VEH_OPEMD_VPS_CHK[VEH_OPEMD_VPS_NUM_CHK] = {
        {(U2)0x0016U, (U2)0x001aU},   /* ACC |        PBA | IG_R */
        {(U2)0x001eU, (U2)0x001eU},   /* ACC | IG_P | PBA | IG_R */
        {(U2)0x0006U, (U2)0x000aU},   /* ACC |        PBA        */
        {(U2)0x0002U, (U2)0x0008U}    /*              PBA        */
    };

    static const U2                      u2_s_VEH_OPEMD_UNK_TOUT = (U2)3000U / (U2)10U;

    U4                                   u4_t_mdbit;
    U4                                   u4_t_evbit;
    U4                                   u4_t_ev_off;
    U4                                   u4_t_ev_on;

    U2                                   u2_t_vps_chk;
    U2                                   u2_t_vps_rx;
    U1                                   u1_t_ipdu_st;
    U1                                   u1_t_diag_pon;

    u4_t_mdbit   = u4_a_MDBIT & (U4)VEH_OPEMD_MDBIT_FIELDS;
    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S81_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    /* -------------------------------------------------------------------------------------------------- */
    /* Note :                                                                                             */
    /* -------------------------------------------------------------------------------------------------- */
    /* VPS is determined according to the following.                                                      */
    /* |--------------------------------------------------------------|                                   */
    /* |                     |               BDC1S91                  |                                   */
    /* |         Msg State   | COM_NO_RX   | COM_TIMEOUT |   OTHER    |                                   */
    /* |---------------------|-------------|-------------|------------|                                   */
    /* |BDC1S81  COM_NO_RX   | Prev Value  | Prev Value  | Prev Value |                                   */
    /* |         COM_TIMEOUT | Prev Value  | Prev Value  | BDC1S91    |                                   */
    /* |         OTHER       | BDC1S81     | BDC1S81     | BDC1S81    |                                   */
    /* -------------------------------------------------------------------------------------------------- */
 
    if(u1_t_ipdu_st == (U1)0U){
        u2_t_vps_rx = u2_s_VehopemdReadbdc1s81();
    } else if((u1_t_ipdu_st & (U1)COM_TIMEOUT) != (U1)0U) {
        u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S91_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        if(u1_t_ipdu_st == (U1)0U){
            u2_t_vps_rx = u2_s_VehopemdReadbdc1s91();
        }
    } else {
        /* do nothing */
    }

    if(u1_t_ipdu_st == (U1)0U){
        u2_t_vps_chk = u2_s_VehopemdVpschk(u2_t_vps_rx, &st_sp_VEH_OPEMD_VPS_CHK[0U], (U2)VEH_OPEMD_VPS_NUM_CHK);

        if(u2_t_vps_chk != (U2)VEH_OPEMD_MDBIT_UNK){
            u4_t_mdbit = (U4)u2_t_vps_chk;
            u2_s_veh_opemd_unk_tocnt = (U2)U2_MAX;
        }
        else if(u2_s_veh_opemd_unk_tocnt >= (U2)U2_MAX){
            u2_s_veh_opemd_unk_tocnt = (U2)0U;
        }
        else if(u2_s_veh_opemd_unk_tocnt >= u2_s_VEH_OPEMD_UNK_TOUT){
         /* u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_UNK; */
        }
        else{
            u2_s_veh_opemd_unk_tocnt++;
        }
    }
    /* BDC1S81 is "COM_TIMEOUT" or "COM_NO_RX" and BDC1S91 is "COM_NO_RX"   */
    else if(u1_t_ipdu_st == (U1)COM_NO_RX){
        u2_s_veh_opemd_unk_tocnt = (U2)U2_MAX;
    }
    /* BDC1S81 is "COM_TIMEOUT" or "COM_NO_RX" and BDC1S91 is "COM_TIMEOUT" */
    else{
     /* u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_UNK; */
        u2_s_veh_opemd_unk_tocnt = (U2)U2_MAX;
    }

    u1_t_diag_pon = u1_s_VehopemdDiagPowOn();
    if(u1_t_diag_pon == (U1)TRUE){
        u4_t_mdbit = u4_t_mdbit | (U4)VEH_OPEMD_MDBIT_DIAG;
    }

    u4_t_evbit  = u4_a_MDBIT ^ u4_t_mdbit;
    u4_t_ev_off = ((u4_t_evbit & u4_a_MDBIT) & (U4)VEH_OPEMD_MDBIT_FIELDS) << 16U;
    u4_t_ev_on  = ((u4_t_evbit & u4_t_mdbit) & (U4)VEH_OPEMD_MDBIT_FIELDS);

    (*u4_ap_evbit) = u4_t_ev_off | u4_t_ev_on;
    vd_s_VehopemdPtschk(u4_t_mdbit, (*u4_ap_evbit));

    vd_s_VehopemdApofrqchk();

    return(u4_t_mdbit);
}
/*===================================================================================================================================*/
/*  static inline U4      u2_s_VehopemdVpschk(const U2 u2_a_RX, const ST_VEH_OPEMD_VPS_CHK * st_ap_CHK, const U2 u2_a_NUM_CHK)       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U2      u2_s_VehopemdVpschk(const U2 u2_a_RX, const ST_VEH_OPEMD_VPS_CHK * st_ap_CHK, const U2 u2_a_NUM_CHK)
{
    U4                             u4_t_lpcnt;
    U2                             u2_t_chk;

    u2_t_chk = (U2)VEH_OPEMD_MDBIT_UNK;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_a_NUM_CHK; u4_t_lpcnt++){
        if(u2_a_RX == st_ap_CHK[u4_t_lpcnt].u2_crit){
            u2_t_chk = st_ap_CHK[u4_t_lpcnt].u2_mdbit;
            break;
        }
    }

    return(u2_t_chk);
}
/*===================================================================================================================================*/
/*  static U2      u2_s_VehopemdReadbdc1s81(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_VehopemdReadbdc1s81(void)
{
    U2                             u2_t_vps_rx;
    U1                             u1_t_vps_inf;

    u1_t_vps_inf = (U1)0U;   
 
    Com_ReceiveSignal(ComConf_ComSignal_VPSINFO1, &u1_t_vps_inf);
    u2_t_vps_rx  = (U2)u1_t_vps_inf;
    Com_ReceiveSignal(ComConf_ComSignal_VPSINFO2, &u1_t_vps_inf);
    u2_t_vps_rx |= (U2)u1_t_vps_inf << 1U;
    Com_ReceiveSignal(ComConf_ComSignal_VPSINFO3, &u1_t_vps_inf);
    u2_t_vps_rx |= (U2)u1_t_vps_inf << 2U;
    Com_ReceiveSignal(ComConf_ComSignal_VPSINFO4, &u1_t_vps_inf);
    u2_t_vps_rx |= (U2)u1_t_vps_inf << 3U;
    Com_ReceiveSignal(ComConf_ComSignal_VPSINFO5, &u1_t_vps_inf);
    u2_t_vps_rx |= (U2)u1_t_vps_inf << 4U;

    return(u2_t_vps_rx);
}

/*===================================================================================================================================*/
/*  static U2      u2_s_VehopemdReadbdc1s91(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_VehopemdReadbdc1s91(void)
{
    U2                             u2_t_vps_rx;
    U1                             u1_t_vps_inf;

    u1_t_vps_inf = (U1)0U;
    
    Com_ReceiveSignal(ComConf_ComSignal_VPSINF1S, &u1_t_vps_inf);
    u2_t_vps_rx  = (U2)u1_t_vps_inf;
    Com_ReceiveSignal(ComConf_ComSignal_VPSINF2S, &u1_t_vps_inf);
    u2_t_vps_rx |= (U2)u1_t_vps_inf << 1U;
    Com_ReceiveSignal(ComConf_ComSignal_VPSINF3S, &u1_t_vps_inf);
    u2_t_vps_rx |= (U2)u1_t_vps_inf << 2U;
    Com_ReceiveSignal(ComConf_ComSignal_VPSINF4S, &u1_t_vps_inf);
    u2_t_vps_rx |= (U2)u1_t_vps_inf << 3U;
    Com_ReceiveSignal(ComConf_ComSignal_VPSINF5S, &u1_t_vps_inf);
    u2_t_vps_rx |= (U2)u1_t_vps_inf << 4U;
            
    return(u2_t_vps_rx);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VehopemdPtsOn(const U1 u1_a_INV)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VehopemdPtsOn(const U1 u1_a_INV)
{
    U1  u1_t_pts;

    u1_t_pts = (U1)FALSE;
    if((u1_s_veh_opemd_pts_chk & (U1)VEH_OPEMD_PTS_CHK_ON) != (U1)0U){
        u1_t_pts = (U1)TRUE;
    }
    if((u1_s_veh_opemd_pts_chk & (U1)VEH_OPEMD_COMRX_INVALID) != (U1)0U){
        if(u1_a_INV == (U1)VEH_OPEMD_PTS_INV_ON){
            u1_t_pts = (U1)TRUE;
        }
        else if(u1_a_INV == (U1)VEH_OPEMD_PTS_INV_OFF){
            u1_t_pts = (U1)FALSE;
        }
        else{
            /* keep last */
        }
    }
    return(u1_t_pts);
}
/*===================================================================================================================================*/
/*  static void     vd_s_VehopemdPtschk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_VehopemdPtschk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
    U4                             u4_t_ignon;
    U1                             u1_t_pts_chk;

    u4_t_ignon    = u4_a_MDBIT & (U4)VEH_OPEMD_MDBIT_IG_R;
    if(u4_t_ignon == (U1)0U){
        u1_t_pts_chk = (U1)VEH_OPEMD_COMRX_UNKNOWN;
    }
    else{
        u1_t_pts_chk = u1_s_VehopemdPtschk_RDYIND(u4_a_MDBIT, u4_a_EVTBIT);
    }

    u1_s_veh_opemd_pts_chk       = u1_t_pts_chk;

}
/*===================================================================================================================================*/
/*  static U1       u1_s_VehopemdPtschk_RDYIND(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_VehopemdPtschk_RDYIND(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
    U1                             u1_t_sgnl;
    U1                             u1_t_pts_chk;

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_RDYIND, &u1_t_sgnl);
    u1_t_pts_chk = Com_GetIPDUStatus(MSG_ENG1G90_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if((u1_t_pts_chk == (U1)0U) &&
       (u1_t_sgnl == (U1)TRUE)){
        u1_t_pts_chk  = (U1)VEH_OPEMD_PTS_CHK_ON;
    }
    else if(u1_t_pts_chk == (U1)COM_TIMEOUT){
        u1_t_pts_chk |= (u1_s_veh_opemd_pts_chk & (U1)VEH_OPEMD_PTS_CHK_ON);  /* keep last */
    }
    else{
        /* Do Nothing */
    }

    return(u1_t_pts_chk);
}
/*===================================================================================================================================*/
/*  static void     vd_s_VehopemdApofrqchk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_VehopemdApofrqchk(void)
{
    U1  u1_t_ipdu_st;
    U1  u1_t_apofrq_sig;

    u1_t_apofrq_sig = (U1)0U;
    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S81_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if(u1_t_ipdu_st == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_APOFRQ, &u1_t_apofrq_sig);
        u1_s_veh_opemd_apofrq_onoff = u1_t_apofrq_sig;
    }
    else if(u1_t_ipdu_st == (U1)COM_NO_RX){
        u1_s_veh_opemd_apofrq_onoff = (U1)0U;
    }
    else{
        u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S91_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        if(u1_t_ipdu_st == (U1)0U){
            (void)Com_ReceiveSignal(ComConf_ComSignal_APOFRQS, &u1_t_apofrq_sig);
            u1_s_veh_opemd_apofrq_onoff = u1_t_apofrq_sig;
        }
        else if(u1_t_ipdu_st == (U1)COM_NO_RX){
            u1_s_veh_opemd_apofrq_onoff = (U1)0U;
        }
        else{
            /* Do Nothing */
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_VehopemdApofrqOn(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_veh_opemd_apofrq_onoff                                                                                      */
/*===================================================================================================================================*/
U1      u1_g_VehopemdApofrqOn(void)
{
    return(u1_s_veh_opemd_apofrq_onoff);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_VehopemdDiagPowOn(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         Diag Power Stataus  (TRUE/FALSE)                                                                                 */
/*===================================================================================================================================*/
static U1      u1_s_VehopemdDiagPowOn(void)
{
    U1                             u1_t_vps_rx;
    U1                             u1_t_vps_inf;
    U1                             u1_t_pow_sts;
    U1                             u1_t_ipdu_st;
 
    u1_t_vps_inf = (U1)0U;   
    u1_t_pow_sts = (U1)FALSE;

    u1_t_ipdu_st = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_BDC1S81_CH0,(U4)0x00090016U,u2_OXCAN_RXTO_THRSH((U2)2000U));
    if((u1_t_ipdu_st & (U1)(~OXCAN_RXD_TOM_EN)) == (U1)0U){
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO1, &u1_t_vps_inf);
        u1_t_vps_rx  = (U1)u1_t_vps_inf;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO2, &u1_t_vps_inf);
        u1_t_vps_rx |= (U1)u1_t_vps_inf << 1U;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO3, &u1_t_vps_inf);
        u1_t_vps_rx |= (U1)u1_t_vps_inf << 2U;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO4, &u1_t_vps_inf);
        u1_t_vps_rx |= (U1)u1_t_vps_inf << 3U;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO5, &u1_t_vps_inf);
        u1_t_vps_rx |= (U1)u1_t_vps_inf << 4U;

        Com_ReceiveSignal(ComConf_ComSignal_VPSINFOS, &u1_t_vps_inf);
    
        if((u1_t_vps_rx == (U1)0x1eU) && (u1_t_vps_inf == (U1)0x00U)){
            u1_t_pow_sts = (U1)TRUE;
        }
    }

    return(u1_t_pow_sts);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/ 3/2015  TN       New.                                                                                               */
/*  1.1.0     3/23/2015  TN       Timer Function was implemented                                                                     */
/*  1.2.0    11/ 2/2017  TN       Design Change : vd_s_VehopemdTmUpdt was moved from veh_opemd.c to veh_opemd_tycan.c.               */
/*  1.2.1     6/23/2020  HU       QAC warnings were fixed.                                                                           */
/*  1.3.0    12/ 7/2020  ST       AUBIST/CAN, COM v1.0.6 -> v1.1.5                                                                   */
/*  2.0.0     2/ 3/2025  ST       Supported vehicle power state.                                                                     */
/*  2.1.0     2/ 7/2025  TN       BEVStep3 Vehicle Power State requirement was implemented.                                          */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    02/06/2026  TS       Change for BEV FF2.(MET-M_ONOFF-CSTD-1)                                                            */
/*                                Add visual OFF flag determination and notification processing during riding.                       */
/*                                Change power status judgment process so that VPSINFO6 and VPSINFO7 signals are not referenced.     */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * HU   = Hayato Usui, Denso Create                                                                                               */
/*  * ST   = Satoshi Tanaka, Denso Create                                                                                            */
/*  * TS   = Takuo Suganuma, Denso Techno                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
