/* 1.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  SID 0x2F I/O Control                                                                                                             */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_IOC_C_MAJOR                      (1U)
#define OXDOCAN_IOC_C_MINOR                      (0U)
#define OXDOCAN_IOC_C_PATCH                      (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "oxdocan_xid_cfg_private.h"

#include "Dcm.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDOCAN_IOC_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "oxdocan_ioc.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (OXDOCAN_IOC_C_MAJOR != OXDOCAN_SAL_H_MAJOR)
#error "oxdocan_ioc.c and oxdocan_sal.h : source and header files are inconsistent!"
#endif

#if (OXDOCAN_IOC_C_MAJOR != OXDOCAN_XID_CFG_H_MAJOR)
#error "oxdocan_ioc.c and oxdocan_xid_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_IOC_DID_HI                          (0U)
#define OXDC_IOC_DID_LO                          (1U)

#define OXDC_IOC_LSB_DID_HI                      (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U2                           u2_g_oxdc_ioc_xid;
static U2                    u2_s_oxdc_ioc_tmcnt;
static U2                    u2_s_oxdc_ioc_vsok_tmcnt;
static U1                    u1_s_oxdc_ioc_vsok;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_oXdcIocVehspdchk(const ST_OXDC_REQ * st_ap_REQ);

static void    vd_s_oXdcIocReqchk(const ST_OXDC_REQ * st_ap_REQ);

static U1      u1_s_oXdcIocXidchk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcIocPrmchk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcIocReqLenChk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcIocCsmchk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcIocSecuritychk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcIocVsok(const ST_OXDC_REQ * st_ap_REQ);

static void    vd_s_oXdcIocProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANIocInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANIocInit(void)
{
    u2_g_oxdc_ioc_xid        = (U2)U2_MAX;
    u2_s_oxdc_ioc_tmcnt      = (U2)U2_MAX;

    u2_s_oxdc_ioc_vsok_tmcnt = (U2)U2_MAX;
    u1_s_oxdc_ioc_vsok       = (U1)OXDC_SAL_PROC_RUN;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANIocMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANIocMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    static const U2          u2_s_OXDC_IOC_TOUT = (U2)5000U / (U2)OXDC_MAIN_TICK;

    U4                       u4_t_lpcnt;
    U1                       u1_t_deact;

    u1_t_deact = u1_s_oXdcIocVehspdchk(st_ap_REQ);
    if((st_ap_REQ->u1_ses_bfr != st_ap_REQ->u1_ses_aft) &&
       (st_ap_REQ->u1_ses_bfr == (U1)OXDC_SESSION_EXT )){
        u1_t_deact = (U1)TRUE;
    }

    if(u2_s_oxdc_ioc_tmcnt < (U2)U2_MAX){
        u2_s_oxdc_ioc_tmcnt++;
    }

    if((u2_s_oxdc_ioc_tmcnt                        == u2_s_OXDC_IOC_TOUT      ) ||
       ((u2_s_oxdc_ioc_tmcnt < u2_s_OXDC_IOC_TOUT) && (u1_t_deact == (U1)TRUE))){

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_g_OXDC_NUM_IOC; u4_t_lpcnt++){
            (void)(*st_gp_OXDC_IOC_IF[u4_t_lpcnt].fp_u1_CSM_CHK)((U1)OXDC_IOC_PRM_CTE, vdp_PTR_NA);
            (*st_gp_OXDC_IOC_IF[u4_t_lpcnt].fp_vd_DEACT)();
        }

        u2_g_oxdc_ioc_xid   = (U2)U2_MAX;
        u2_s_oxdc_ioc_tmcnt = (U2)U2_MAX;
    }

    if(st_ap_REQ->u1_sid == (U1)OXDC_SID_2F){

        if(st_ap_REQ->u2_tim_elpsd == (U2)0U){
            vd_s_oXdcIocReqchk(st_ap_REQ);
        }

        if(u2_g_oxdc_ioc_xid < u2_g_OXDC_DATA_NUM_XID){
            vd_s_oXdcIocProcRun(st_ap_REQ, st_ap_ans);
        }
        else if(st_ap_REQ->u2_tim_elpsd > (U2)0U){
            vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_NR_10, vdp_PTR_NA);
        }
        else{
            /* Do Nothing */
        }
    }
    else{
        u2_g_oxdc_ioc_xid = (U2)U2_MAX;
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcIocVehspdchk(const ST_OXDC_REQ * st_ap_REQ)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcIocVehspdchk(const ST_OXDC_REQ * st_ap_REQ)
{
    static const U2          u2_s_OXDC_IOC_KMPH_MIN   = (U2)400U;                      /* 4.00 km/h        */
    static const U2          u2_s_OXDC_IOC_TIM_TO_ACT = (U2)200U / (U2)OXDC_MAIN_TICK; /* 200 milliseconds */

    U1                       u1_t_diag_on;
    U1                       u1_t_deact;

    u1_t_deact  = (U1)FALSE;
    u1_t_diag_on = st_ap_REQ->u1_eom_aft & (U1)OXDC_EOM_DIAG_ON;
    if(u1_t_diag_on != (U1)OXDC_EOM_DIAG_ON){
        u2_s_oxdc_ioc_vsok_tmcnt = (U2)U2_MAX;
        u1_t_deact               = (U1)TRUE;
    }
    else if(st_ap_REQ->u2_kmph > u2_s_OXDC_IOC_KMPH_MIN){
        u2_s_oxdc_ioc_vsok_tmcnt = (U2)U2_MAX;
    }
    else if(u2_s_oxdc_ioc_vsok_tmcnt >= (U2)U2_MAX){
        u2_s_oxdc_ioc_vsok_tmcnt = (U2)0U;
    }
    else if(u2_s_oxdc_ioc_vsok_tmcnt >= u2_s_OXDC_IOC_TIM_TO_ACT){
        u2_s_oxdc_ioc_vsok_tmcnt = u2_s_OXDC_IOC_TIM_TO_ACT;
    }
    else{
        u2_s_oxdc_ioc_vsok_tmcnt++;
    }

    if((u2_s_oxdc_ioc_vsok_tmcnt < (U2)U2_MAX               ) &&
       (u2_s_oxdc_ioc_vsok_tmcnt >= u2_s_OXDC_IOC_TIM_TO_ACT)){
        u1_s_oxdc_ioc_vsok = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_s_oxdc_ioc_vsok = (U1)OXDC_SAL_PROC_NR_22;
    }

    return(u1_t_deact);
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcIocReqchk(const ST_OXDC_REQ * st_ap_REQ)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcIocReqchk(const ST_OXDC_REQ * st_ap_REQ)
{
    static U1 ( * const      fp_sp_u1_OXDC_IOC_CHK[])(const ST_OXDC_REQ * st_ap_REQ) = {
        &u1_s_oXdcIocXidchk,
        &u1_s_oXdcIocPrmchk,
        &u1_s_oXdcIocReqLenChk,
        &u1_s_oXdcIocCsmchk,
        &u1_s_oXdcIocSecuritychk,
        &u1_s_oXdcIocVsok,
        vdp_PTR_NA
    };

    U4                       u4_t_lpcnt;
    U1                       u1_t_proc;

    u1_t_proc  = (U1)OXDC_SAL_PROC_RUN;
    u4_t_lpcnt = (U4)0U;
    while((u1_t_proc                         == (U1)OXDC_SAL_PROC_RUN) &&
          (fp_sp_u1_OXDC_IOC_CHK[u4_t_lpcnt] != vdp_PTR_NA           )){

        u1_t_proc = (*fp_sp_u1_OXDC_IOC_CHK[u4_t_lpcnt])(st_ap_REQ);
        u4_t_lpcnt++;
    }

    if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
        u2_g_oxdc_ioc_xid = (U2)U2_MAX;
        vd_g_oXDoCANAnsTx(u1_t_proc, vdp_PTR_NA);
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcIocXidchk(const ST_OXDC_REQ * st_ap_REQ)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcIocXidchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U2                       u2_t_xid;
    U1                       u1_t_proc;
    U1                       u1_t_sup;

    if((st_ap_REQ->u1p_RX   != vdp_PTR_NA      ) &&
       (st_ap_REQ->u4_nbyte >= (U4)OXDC_IOC_CSM)){

        u2_t_xid  = (U2)st_ap_REQ->u1p_RX[OXDC_IOC_DID_HI] << OXDC_IOC_LSB_DID_HI;
        u2_t_xid |= (U2)st_ap_REQ->u1p_RX[OXDC_IOC_DID_LO];
        u2_t_xid  = u2_g_oXDoCANXidSearchXid(u2_t_xid, &st_gp_OXDC_DATA_XID[0], u2_g_OXDC_DATA_NUM_XID);

        u2_g_oxdc_ioc_xid = u2_t_xid;

        if(u2_t_xid >= u2_g_OXDC_DATA_NUM_XID){
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
        else if(st_gp_OXDC_DATA_CFG[u2_t_xid].stp_IOC == vdp_PTR_NA){
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
        else if(st_gp_OXDC_DATA_XID[u2_t_xid].fp_u1_SUP == vdp_PTR_NA){
            u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
        }
        else{

            u1_t_sup = (*st_gp_OXDC_DATA_XID[u2_t_xid].fp_u1_SUP)();
            if(u1_t_sup < (U1)OXDC_XID_SUP_NOT){
                u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
            }
            else{
                u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
            }
        }
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_13;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcIocPrmchk(const ST_OXDC_REQ * st_ap_REQ)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcIocPrmchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U1                       u1_t_prm;
    U1                       u1_t_proc;

    u1_t_prm = st_ap_REQ->u1p_RX[OXDC_IOC_PRM];
    if((u1_t_prm == (U1)OXDC_IOC_PRM_CTE) ||
       (u1_t_prm == (U1)OXDC_IOC_PRM_STA)){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }

    return (u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcIocReqLenChk(const ST_OXDC_REQ * st_ap_REQ)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         OXDC_SAL_PROC_RUN(Check OK)/OXDC_SAL_PROC_NR_13(Check NG)                                                        */
/*===================================================================================================================================*/
static U1      u1_s_oXdcIocReqLenChk(const ST_OXDC_REQ * st_ap_REQ)
{
    U4                       u4_t_req_nbyte;
    U4                       u4_t_ans_nbyte;
    U1                       u1_t_prm;
    U1                       u1_t_proc;

    /* st_gp_OXDC_DATA_XID_ML[].u2_req_nbyte = length of ControlState and length of ControlMask */
    /* st_gp_OXDC_DATA_XID_ML[].u2_ans_nbyte = length of ControlState                           */
    u4_t_req_nbyte = (U4)st_gp_OXDC_DATA_XID_ML[u2_g_oxdc_ioc_xid].u2_req_nbyte + (U4)OXDC_IOC_CSM;
    u4_t_ans_nbyte = (U4)st_gp_OXDC_DATA_XID_ML[u2_g_oxdc_ioc_xid].u2_ans_nbyte;
    u1_t_prm      = st_ap_REQ->u1p_RX[OXDC_IOC_PRM];
    if((u1_t_prm       == (U1)OXDC_IOC_PRM_CTE) &&
       (u4_t_req_nbyte >= u4_t_ans_nbyte      )){
        u4_t_req_nbyte -= u4_t_ans_nbyte;   /* length of ControlMask */
    }
    else if(u1_t_prm != (U1)OXDC_IOC_PRM_STA){
        u4_t_req_nbyte = (U4)0U;
    }
    else{
        /* Do Nothing */
    }

    if(st_ap_REQ->u4_nbyte == u4_t_req_nbyte){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_13;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcIocCsmchk(const ST_OXDC_REQ * st_ap_REQ)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcIocCsmchk(const ST_OXDC_REQ * st_ap_REQ)
{
    const ST_OXDC_IOC_IF *   st_tp_IOC;
    U1                       u1_t_proc;

    st_tp_IOC = st_gp_OXDC_DATA_CFG[u2_g_oxdc_ioc_xid].stp_IOC;
    u1_t_proc = (*st_tp_IOC->fp_u1_CSM_CHK)(st_ap_REQ->u1p_RX[OXDC_IOC_PRM], &(st_ap_REQ->u1p_RX[OXDC_IOC_CSM]));
    if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcIocSecuritychk(const ST_OXDC_REQ * st_ap_REQ)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcIocSecuritychk(const ST_OXDC_REQ * st_ap_REQ)
{
    U1                       u1_t_proc;
    U2                       u2_t_sec;

    u2_t_sec = st_gp_OXDC_DATA_CFG[u2_g_oxdc_ioc_xid].stp_IOC->u2_sec;
    u1_t_proc = u1_g_oXDoCANCfgSecurityBitChk(u2_t_sec);

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcIocVsok(const ST_OXDC_REQ * st_ap_REQ)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcIocVsok(const ST_OXDC_REQ * st_ap_REQ)
{
    return(u1_s_oxdc_ioc_vsok);
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcIocProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_oXdcIocProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    U1 ( *                   fp_t_u1_read)(U1 * u1_ap_ans, const U2 u2_a_ELPSD);

    const ST_OXDC_IOC_IF *   st_tp_IOC;

    U4                       u4_t_tx_nbyte;
    U2                       u2_t_ans_nbyte;
    U2                       u2_t_elpsd;
    U1                       u1_t_proc;
    U1                       u1_t_prm;

    u2_t_ans_nbyte = st_gp_OXDC_DATA_XID_ML[u2_g_oxdc_ioc_xid].u2_ans_nbyte;
    u4_t_tx_nbyte  = (U4)u2_t_ans_nbyte + (U4)OXDC_IOC_CSM;

    st_tp_IOC      = st_gp_OXDC_DATA_CFG[u2_g_oxdc_ioc_xid].stp_IOC;

    if((st_tp_IOC           != vdp_PTR_NA      ) &&
       (st_ap_REQ->u1p_RX   != vdp_PTR_NA      ) &&
       (st_ap_REQ->u4_nbyte >= (U4)OXDC_IOC_CSM) &&
       (st_ap_ans->u1p_tx   != vdp_PTR_NA      ) &&
       (st_ap_ans->u4_nbyte >= u4_t_tx_nbyte   )){

        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
        u1_t_prm  = st_ap_REQ->u1p_RX[OXDC_IOC_PRM];
        if(st_ap_REQ->u2_tim_elpsd > (U2)0U){

            if(st_ap_REQ->u2_tim_elpsd >= u2_g_OXDC_IOC_RDBK_DLY_MAX){
                fp_t_u1_read = st_gp_OXDC_DATA_CFG[u2_g_oxdc_ioc_xid].fp_u1_READ;
                u2_t_elpsd   = st_ap_REQ->u2_tim_elpsd - u2_g_OXDC_IOC_RDBK_DLY_MAX;
                u1_t_proc    = (*fp_t_u1_read)(&(st_ap_ans->u1p_tx[OXDC_IOC_CSM]), u2_t_elpsd);
            }
        }
        else if(u1_t_prm == (U1)OXDC_IOC_PRM_STA){
            (*(st_tp_IOC->fp_vd_ACT))();
            u2_s_oxdc_ioc_tmcnt = (U2)0U;
        }
        else if(u1_t_prm == (U1)OXDC_IOC_PRM_CTE){
            (*(st_tp_IOC->fp_vd_DEACT))();
        }
        else{
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_10;
        }
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_10;
    }

    if(u1_t_proc == (U1)OXDC_SAL_PROC_FIN){

        u2_g_oxdc_ioc_xid = (U2)U2_MAX;

        st_ap_ans->u1p_tx[OXDC_IOC_DID_HI] = st_ap_REQ->u1p_RX[OXDC_IOC_DID_HI];
        st_ap_ans->u1p_tx[OXDC_IOC_DID_LO] = st_ap_REQ->u1p_RX[OXDC_IOC_DID_LO];
        st_ap_ans->u1p_tx[OXDC_IOC_PRM]    = st_ap_REQ->u1p_RX[OXDC_IOC_PRM];
        st_ap_ans->u4_nbyte                = u4_t_tx_nbyte;

        vd_g_oXDoCANAnsTx(u1_t_proc, st_ap_ans);
    }
    else if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){

        u2_g_oxdc_ioc_xid = (U2)U2_MAX;
        vd_g_oXDoCANAnsTx(u1_t_proc, vdp_PTR_NA);
    }
    else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/16/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000, Function Name tydocan_ioc -> oxdocan_ioc.  */
/*  1.0.1     8/24/2023  TI       Update for OEM standardization & Maximum security level support.                                   */
/*  1.0.2     7/25/2025  TI       Fixed to allow controlEnableMaskRecord.                                                            */
/*                                                                                                                                   */
/*  * HU = Hayato Usui, DENSO                                                                                                        */
/*  * TI = Takaehisa Inoue, DENSO                                                                                                    */
/*  * ToI = Tomoko Inuzuka, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
