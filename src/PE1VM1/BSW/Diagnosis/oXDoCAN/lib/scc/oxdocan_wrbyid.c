/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  SID 0x2E Write by Identifier                                                                                                     */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_WRBYID_C_MAJOR                   (1U)
#define OXDOCAN_WRBYID_C_MINOR                   (0U)
#define OXDOCAN_WRBYID_C_PATCH                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "oxdocan_xid_cfg_private.h"

#include "Dcm.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDOCAN_WRBYID_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "oxdocan_wrbyid.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (OXDOCAN_WRBYID_C_MAJOR != OXDOCAN_SAL_H_MAJOR)
#error "oxdocan_wrbyid.c and oxdocan_sal.h : source and header files are inconsistent!"
#endif

#if (OXDOCAN_WRBYID_C_MAJOR != OXDOCAN_XID_CFG_H_MAJOR)
#error "oxdocan_wrbyid.c and oxdocan_xid_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_WRBYID_DID_NBYTE                    (2U)
#define OXDC_WRBYID_DID_HI                       (0U)
#define OXDC_WRBYID_DID_LO                       (1U)

#define OXDC_WRBYID_LSB_ID_HI                    (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2                    u2_s_oxdc_wrbyid_xid;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXdcWrbyIdReqchk(const ST_OXDC_REQ * st_ap_REQ);

static U1      u1_s_oXdcWrbyIdXidchk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcWrbyIdSessionchk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcWrbyIdReqLenchk(const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcWrbyIdSecuritychk(const ST_OXDC_REQ * st_ap_REQ);
#if(OXDC_SID2E_NR_22_USE == OXDC_USE)
static U1      u1_s_oXdcWrbyIdConditionchk(const ST_OXDC_REQ * st_ap_REQ);
#endif
static void    vd_s_oXdcWrbyIdProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANWrbyIdInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANWrbyIdInit(void)
{
    u2_s_oxdc_wrbyid_xid = (U2)U2_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANWrbyIdMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANWrbyIdMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    if(st_ap_REQ->u1_sid == (U1)OXDC_SID_2E){

        if(st_ap_REQ->u2_tim_elpsd == (U2)0U){
            vd_s_oXdcWrbyIdReqchk(st_ap_REQ);
        }

        if(u2_s_oxdc_wrbyid_xid < u2_g_OXDC_DATA_NUM_XID){
            vd_s_oXdcWrbyIdProcRun(st_ap_REQ, st_ap_ans);
        }
        else if(st_ap_REQ->u2_tim_elpsd > (U2)0U){
            vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_NR_10, vdp_PTR_NA);
        }
        else{
            /* Do Nothing */
        }
    }
    else{
        u2_s_oxdc_wrbyid_xid = (U2)U2_MAX;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcWrbyIdReqchk(const ST_OXDC_REQ * st_ap_REQ)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_oXdcWrbyIdReqchk(const ST_OXDC_REQ * st_ap_REQ)
{
    static U1 ( * const      fp_sp_u1_OXDC_WRBYID_CHK[])(const ST_OXDC_REQ * st_ap_REQ) = {
        &u1_s_oXdcWrbyIdXidchk,
        &u1_s_oXdcWrbyIdSessionchk,
        &u1_s_oXdcWrbyIdReqLenchk,
        &u1_s_oXdcWrbyIdSecuritychk,
#if(OXDC_SID2E_NR_22_USE == OXDC_USE)
        &u1_s_oXdcWrbyIdConditionchk,
#endif
        vdp_PTR_NA
    };

    U4                       u4_t_lpcnt;
    U1                       u1_t_proc;

    u1_t_proc  = (U1)OXDC_SAL_PROC_RUN;
    u4_t_lpcnt = (U4)0U;
    while((u1_t_proc                            == (U1)OXDC_SAL_PROC_RUN) &&
          (fp_sp_u1_OXDC_WRBYID_CHK[u4_t_lpcnt] != vdp_PTR_NA           )){

        u1_t_proc = (*fp_sp_u1_OXDC_WRBYID_CHK[u4_t_lpcnt])(st_ap_REQ);
        u4_t_lpcnt++;
    }

    if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
        u2_s_oxdc_wrbyid_xid = (U2)U2_MAX;
        vd_g_oXDoCANAnsTx(u1_t_proc, vdp_PTR_NA);
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcWrbyIdXidchk(const ST_OXDC_REQ * st_ap_REQ)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcWrbyIdXidchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U2                       u2_t_xid;
    U1                       u1_t_proc;
    U1                       u1_t_sup;

    if((st_ap_REQ->u1p_RX   != vdp_PTR_NA               ) &&
       (st_ap_REQ->u4_nbyte >  (U4)OXDC_WRBYID_DID_NBYTE)){

        u2_t_xid  = (U2)st_ap_REQ->u1p_RX[OXDC_WRBYID_DID_HI] << OXDC_WRBYID_LSB_ID_HI;
        u2_t_xid |= (U2)st_ap_REQ->u1p_RX[OXDC_WRBYID_DID_LO];
        u2_t_xid  = u2_g_oXDoCANXidSearchDid(u2_t_xid, &st_gp_OXDC_DATA_XID[0], u2_g_OXDC_DATA_NUM_XID);

        u2_s_oxdc_wrbyid_xid = u2_t_xid;

        if(u2_t_xid >= u2_g_OXDC_DATA_NUM_XID){
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
        else if(st_gp_OXDC_DATA_CFG[u2_t_xid].fp_u1_WRITE == vdp_PTR_NA){
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
/*  static U1      u1_s_oXdcWrbyIdSessionchk(const ST_OXDC_REQ * st_ap_REQ)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcWrbyIdSessionchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U2                       u2_t_conf_ses;
    U1                       u1_t_proc;

    u2_t_conf_ses = st_gp_OXDC_DATA_XID[u2_s_oxdc_wrbyid_xid].u2_wr_ses;
    u1_t_proc = u1_g_oXDoCANCfgDidSessionBitChk(st_ap_REQ->u1_ses_aft, u2_t_conf_ses);

    if(u1_t_proc == (U1)E_OK){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcWrbyIdReqLenchk(const ST_OXDC_REQ * st_ap_REQ)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcWrbyIdReqLenchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U4                       u4_t_req_nbyte;
    U1                       u1_t_proc;

    u4_t_req_nbyte = (U4)st_gp_OXDC_DATA_XID_ML[u2_s_oxdc_wrbyid_xid].u2_req_nbyte + (U4)OXDC_WRBYID_DID_NBYTE;
    if(st_ap_REQ->u4_nbyte != u4_t_req_nbyte){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_13;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcWrbyIdSecuritychk(const ST_OXDC_REQ * st_ap_REQ)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcWrbyIdSecuritychk(const ST_OXDC_REQ * st_ap_REQ)
{
    U1                       u1_t_proc;
    U1                       u1_t_sec;

    if(st_gp_OXDC_DATA_XID[u2_s_oxdc_wrbyid_xid].fp_u1_WRSEC_CHK == vdp_PTR_NA){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_sec = DCM_SEC_LEV_LOCKED;
        (void)Dcm_GetSecurityLevel(&u1_t_sec);
        u1_t_proc = (*st_gp_OXDC_DATA_XID[u2_s_oxdc_wrbyid_xid].fp_u1_WRSEC_CHK)(u1_t_sec);
    }

    return(u1_t_proc);
}
#if(OXDC_SID2E_NR_22_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcWrbyIdConditionchk(const ST_OXDC_REQ * st_ap_REQ)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcWrbyIdConditionchk(const ST_OXDC_REQ * st_ap_REQ)
{
    U1                       u1_t_proc;
    U1                       u1_t_result;

    u1_t_result = u1_g_oXDoCANCWriteByIdChk();
    if(u1_t_result == (U1)E_OK){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;

    }

    return(u1_t_proc);
}
#endif
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcWrbyIdProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_oXdcWrbyIdProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    U1 ( *                   fp_t_u1_write)(const U1 * u1_ap_REQ, const U2 u2_a_ELPSD);

    U4                       u4_t_req_nbyte;
    U1                       u1_t_proc;

    fp_t_u1_write  = st_gp_OXDC_DATA_CFG[u2_s_oxdc_wrbyid_xid].fp_u1_WRITE;
    u4_t_req_nbyte = (U4)st_gp_OXDC_DATA_XID_ML[u2_s_oxdc_wrbyid_xid].u2_req_nbyte + (U4)OXDC_WRBYID_DID_NBYTE;
    if((st_ap_REQ->u1p_RX   != vdp_PTR_NA               ) &&
       (st_ap_REQ->u4_nbyte == u4_t_req_nbyte           ) &&
       (st_ap_ans->u1p_tx   != vdp_PTR_NA               ) &&
       (st_ap_ans->u4_nbyte >= (U4)OXDC_WRBYID_DID_NBYTE) &&
       (fp_t_u1_write       != vdp_PTR_NA               )){

        u1_t_proc = (*fp_t_u1_write)(&(st_ap_REQ->u1p_RX[OXDC_WRBYID_DID_NBYTE]), st_ap_REQ->u2_tim_elpsd);
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_10;
    }

    if(u1_t_proc == (U1)OXDC_SAL_PROC_FIN){

        u2_s_oxdc_wrbyid_xid = (U2)U2_MAX;

        st_ap_ans->u1p_tx[OXDC_WRBYID_DID_HI] = st_ap_REQ->u1p_RX[OXDC_WRBYID_DID_HI];
        st_ap_ans->u1p_tx[OXDC_WRBYID_DID_LO] = st_ap_REQ->u1p_RX[OXDC_WRBYID_DID_LO];
        st_ap_ans->u4_nbyte                   = (U4)OXDC_WRBYID_DID_NBYTE;
        
        vd_g_oXDoCANAnsTx(u1_t_proc, st_ap_ans);
    }
    else if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){

        u2_s_oxdc_wrbyid_xid = (U2)U2_MAX;

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
/*  1.0.0     3/16/2022  HU       ty19epf_ren_d1x_v220_r009 -> x25epf_ren_d1x_v100_r000, Function Name tydocan_wrbyid ->             */
/*                                oxdocan_wrbyid.                                                                                    */
/*  1.0.1     8/22/2023  II       Maximum security level support.                                                                    */
/*                                                                                                                                   */
/*  * HU = Hayato Usui, DENSO                                                                                                        */
/*  * II = Itsuki Ito,  DENSO                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
