/* 1.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  SID 0x22 Read by Identifier                                                                                                      */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_REBYID_C_MAJOR                   (1U)
#define OXDOCAN_REBYID_C_MINOR                   (0U)
#define OXDOCAN_REBYID_C_PATCH                   (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "oxdocan_xid_cfg_private.h"

#include "Dcm.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDOCAN_REBYID_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "oxdocan_rebyid.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (OXDOCAN_REBYID_C_MAJOR != OXDOCAN_SAL_H_MAJOR)
#error "oxdocan_rebyid.c and oxdocan_sal.h : source and header files are inconsistent!"
#endif

#if (OXDOCAN_REBYID_C_MAJOR != OXDOCAN_XID_CFG_H_MAJOR)
#error "oxdocan_rebyid.c and oxdocan_xid_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_REBYID_DID_NBYTE                    (2U)
#define OXDC_REBYID_DID_HI                       (0U)
#define OXDC_REBYID_DID_LO                       (1U)

#define OXDC_REBYID_LSB_DID_HI                   (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_REBYID_REQCHKOK                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4                    u4_s_oxdc_rebyid_ansnbyte;
static U1                    u1_s_oxdc_rebyid_numof_xid;
static U1                    u1_s_oxdc_rebyid_status;

U2                           u2_gp_oxdc_rebyid_xidlist[OXDC_REBYID_NUMOFDID_MAX];
U1                           u1_g_oxdc_rebyid_xidcnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXdcRebyIdReqchk(const ST_OXDC_REQ * st_ap_REQ);

static U1      u1_s_oXdcRebyIdXidchk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcRebyIdSessionchk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ);
static U1      u1_s_oXdcRebyIdSecuritychk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ);
#if(OXDC_SID22_NR_22_USE == OXDC_USE)
static U1      u1_s_oXdcRebyIdConditionchk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ);
#endif

static void    vd_s_oXdcRebyIdProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRebyIdInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRebyIdInit(void)
{
    U4                       u4_t_lpcnt;
     
    u4_s_oxdc_rebyid_ansnbyte  = (U4)0U;
    u1_g_oxdc_rebyid_xidcnt    = (U1)0U;
    u1_s_oxdc_rebyid_numof_xid = (U1)0U;
    u1_s_oxdc_rebyid_status    = (U1)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXDC_REBYID_NUMOFDID_MAX; u4_t_lpcnt++){
        u2_gp_oxdc_rebyid_xidlist[u4_t_lpcnt] = (U2)0U;
    }

}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRebyIdMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRebyIdMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    U1                       u1_t_didmax;

    if(st_ap_REQ->u1_req_type == (U1)OXDC_REQ_TYPE_PHYS){
        u1_t_didmax = (U1)OXDC_REBYID_DIDMAX_PFYS;
    }
    else{
        u1_t_didmax = (U1)OXDC_REBYID_DIDMAX_FUNC;
    }

    if(st_ap_REQ->u1_sid == (U1)OXDC_SID_22){

        if(st_ap_REQ->u2_tim_elpsd == (U2)0U){
            
            vd_s_oXdcRebyIdReqchk(st_ap_REQ);
        }
        
        if((u1_s_oxdc_rebyid_status                            == (U1)OXDC_REBYID_REQCHKOK  ) &&
           (u1_g_oxdc_rebyid_xidcnt                             < u1_s_oxdc_rebyid_numof_xid) &&
           (u1_s_oxdc_rebyid_numof_xid                         <= u1_t_didmax               ) &&
           (u2_gp_oxdc_rebyid_xidlist[u1_g_oxdc_rebyid_xidcnt]  < u2_g_OXDC_DATA_NUM_XID    )){

            vd_s_oXdcRebyIdProcRun(st_ap_REQ, st_ap_ans);
        }
        else if(st_ap_REQ->u2_tim_elpsd > (U2)0U){
            vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_NR_10, vdp_PTR_NA);
        }
        else{
            /* Do Nothing */
        }
    }
    else{
        u1_s_oxdc_rebyid_status = (U1)0U;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRebyIdReqchk(const ST_OXDC_REQ * st_ap_REQ)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_oXdcRebyIdReqchk(const ST_OXDC_REQ * st_ap_REQ)
{
    static U1 ( * const      fp_sp_u1_OXDC_REBYID_CHK[])(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ) = {
        &u1_s_oXdcRebyIdXidchk,
        &u1_s_oXdcRebyIdSessionchk,
        &u1_s_oXdcRebyIdSecuritychk,
#if(OXDC_SID22_NR_22_USE == OXDC_USE)
        &u1_s_oXdcRebyIdConditionchk,
#endif
        vdp_PTR_NA
    };
    
    U4                       u4_t_loopcnt_xid;
    U4                       u4_t_xid_idx;
    U4                       u4_t_whilecnt_chk;
    U2                       u2_t_xid;
    U1                       u1_t_proc;
    U1                       u1_t_didmax;
    U1                       u1_t_numof_xid;

    vd_g_oXDoCANRebyIdInit();

    if(st_ap_REQ->u1_req_type == (U1)OXDC_REQ_TYPE_PHYS){
        u1_t_didmax = (U1)OXDC_REBYID_DIDMAX_PFYS;
    }
    else{
        u1_t_didmax = (U1)OXDC_REBYID_DIDMAX_FUNC;
    }

    u1_t_numof_xid =  (U1)(st_ap_REQ->u4_nbyte / (U4)OXDC_REBYID_DID_NBYTE);
    u1_s_oxdc_rebyid_numof_xid = u1_t_numof_xid;

    if((st_ap_REQ->u1p_RX                                 != vdp_PTR_NA     ) &&
       ((st_ap_REQ->u4_nbyte % (U4)OXDC_REBYID_DID_NBYTE) == (U4)0U         ) &&
       (u1_t_numof_xid                                     > (U1)0U         ) &&
       (u1_t_numof_xid                                    <= (U1)u1_t_didmax)){

        u1_s_oxdc_rebyid_status = (U1)OXDC_REBYID_REQCHKOK;

        u4_t_xid_idx = (U4)0U;
        for(u4_t_loopcnt_xid = (U4)0U; u4_t_loopcnt_xid < (U4)u1_t_numof_xid; u4_t_loopcnt_xid++){

            u2_t_xid  = (U2)st_ap_REQ->u1p_RX[(OXDC_REBYID_DID_NBYTE * u4_t_loopcnt_xid)/* + OXDC_REBYID_DID_HI */] << OXDC_REBYID_LSB_DID_HI;
            u2_t_xid |= (U2)st_ap_REQ->u1p_RX[(OXDC_REBYID_DID_NBYTE * u4_t_loopcnt_xid)   + OXDC_REBYID_DID_LO   ];
            u2_t_xid  = u2_g_oXDoCANXidSearchDid(u2_t_xid, &st_gp_OXDC_DATA_XID[0], u2_g_OXDC_DATA_NUM_XID);

            u2_gp_oxdc_rebyid_xidlist[u4_t_xid_idx] = u2_t_xid;

            u1_t_proc      = (U1)OXDC_SAL_PROC_RUN;
            u4_t_whilecnt_chk = (U4)0U;
            while((u1_t_proc                                   == (U1)OXDC_SAL_PROC_RUN) &&
                  (fp_sp_u1_OXDC_REBYID_CHK[u4_t_whilecnt_chk] != vdp_PTR_NA           )){

                u1_t_proc = (*fp_sp_u1_OXDC_REBYID_CHK[u4_t_whilecnt_chk])(u2_t_xid, st_ap_REQ);
                u4_t_whilecnt_chk++;
            }

#ifdef OXDC_SID22_PH6
            if(u1_t_proc == (U1)OXDC_SAL_PROC_NR_31){
                if(u4_t_loopcnt_xid < (U4)((U4)u1_t_numof_xid - (U4)1U)){
                    u1_s_oxdc_rebyid_numof_xid--;
                }
                else if(u4_t_xid_idx > (U4)0U){
                    u1_s_oxdc_rebyid_numof_xid--;
                    u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
                }
                else{
                    /* Do Nothing */
                }
            }
            else if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
                break;
            }
            else{
                u4_t_xid_idx++;
            }
#else
            if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
                break;
            }
            else{
                u4_t_xid_idx++;
            }
#endif
        }

        if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
            u1_s_oxdc_rebyid_status = (U1)0U;
            vd_g_oXDoCANAnsTx(u1_t_proc, vdp_PTR_NA);
        }
    }
    else{
        u1_s_oxdc_rebyid_status = (U1)0U;
        vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_NR_13, vdp_PTR_NA);
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRebyIdXidchk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRebyIdXidchk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ)
{
    U1                       u1_t_proc;
    U1                       u1_t_sup;


    if(u2_a_REBYID_XID >= u2_g_OXDC_DATA_NUM_XID){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }
    else if(st_gp_OXDC_DATA_XID[u2_a_REBYID_XID].fp_u1_SUP == vdp_PTR_NA){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_sup = (*st_gp_OXDC_DATA_XID[u2_a_REBYID_XID].fp_u1_SUP)();
        if(u1_t_sup < (U1)OXDC_XID_SUP_NOT){
            u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
        }
        else{
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRebyIdSessionchk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRebyIdSessionchk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ)
{
    U2                       u2_t_conf_ses;
    U1                       u1_t_proc;

    u2_t_conf_ses = st_gp_OXDC_DATA_XID[u2_a_REBYID_XID].u2_rd_ses;
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
/*  static U1      u1_s_oXdcRebyIdSecuritychk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRebyIdSecuritychk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ)
{
    U1                       u1_t_proc;
    U1                       u1_t_sec;

    if(st_gp_OXDC_DATA_XID[u2_a_REBYID_XID].fp_u1_RDSEC_CHK == vdp_PTR_NA){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_sec = DCM_SEC_LEV_LOCKED;
        (void)Dcm_GetSecurityLevel(&u1_t_sec);
        u1_t_proc = (*st_gp_OXDC_DATA_XID[u2_a_REBYID_XID].fp_u1_RDSEC_CHK)(u1_t_sec);
    }

    return(u1_t_proc);
}
#if(OXDC_SID22_NR_22_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcRebyIdConditionchk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U1      u1_s_oXdcRebyIdConditionchk(const U2 u2_a_REBYID_XID, const ST_OXDC_REQ * st_ap_REQ)
{
    U1                       u1_t_proc;
    U1                       u1_t_result;

    u1_t_result = u1_g_oXDoCANCReadByIdChk();
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
/*  static void    vd_s_oXdcRebyIdProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_oXdcRebyIdProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    U1 ( *                   fp_t_u1_read)(U1 * u1_ap_ans, const U2 u2_a_ELPSD);

    U4                       u4_t_tx_nbyte_tmp;
    U2                       u2_t_rdcnt;
    U1                       u1_t_proc;

    u2_t_rdcnt = (U2)0U;
    do{
        u2_t_rdcnt++;
        u4_t_tx_nbyte_tmp = u4_s_oxdc_rebyid_ansnbyte + (U4)OXDC_REBYID_DID_NBYTE + (U4)st_gp_OXDC_DATA_XID_ML[u2_gp_oxdc_rebyid_xidlist[u1_g_oxdc_rebyid_xidcnt]].u2_ans_nbyte;

        if((st_ap_ans->u1p_tx   != vdp_PTR_NA       ) &&
           (st_ap_ans->u4_nbyte >= u4_t_tx_nbyte_tmp)){

            fp_t_u1_read = st_gp_OXDC_DATA_CFG[u2_gp_oxdc_rebyid_xidlist[u1_g_oxdc_rebyid_xidcnt]].fp_u1_READ;
            u1_t_proc    = (*fp_t_u1_read)(&(st_ap_ans->u1p_tx[u4_s_oxdc_rebyid_ansnbyte + OXDC_REBYID_DID_NBYTE]), st_ap_REQ->u2_tim_elpsd);
        }
        else{
            u1_t_proc    = (U1)OXDC_SAL_PROC_NR_14;
        }

        if(u1_t_proc == (U1)OXDC_SAL_PROC_FIN){

            st_ap_ans->u1p_tx[u4_s_oxdc_rebyid_ansnbyte/* + OXDC_REBYID_DID_HI */] = st_ap_REQ->u1p_RX[(OXDC_REBYID_DID_NBYTE * u1_g_oxdc_rebyid_xidcnt)/* + OXDC_REBYID_DID_HI */];
            st_ap_ans->u1p_tx[u4_s_oxdc_rebyid_ansnbyte   + OXDC_REBYID_DID_LO   ] = st_ap_REQ->u1p_RX[(OXDC_REBYID_DID_NBYTE * u1_g_oxdc_rebyid_xidcnt)   + OXDC_REBYID_DID_LO   ];
            u4_s_oxdc_rebyid_ansnbyte                                         = u4_t_tx_nbyte_tmp;

            u1_g_oxdc_rebyid_xidcnt++;
            if(u1_g_oxdc_rebyid_xidcnt >= u1_s_oxdc_rebyid_numof_xid){

                st_ap_ans->u4_nbyte = u4_s_oxdc_rebyid_ansnbyte;

                u1_s_oxdc_rebyid_status = (U1)0U;
                vd_g_oXDoCANAnsTx(u1_t_proc, st_ap_ans);
            }
        }
        else if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
            u1_s_oxdc_rebyid_status = (U1)0U;
            vd_g_oXDoCANAnsTx(u1_t_proc, vdp_PTR_NA);
        }
        else{
            /* Do Nothing */
        }
    }while((u1_t_proc               == (U1)OXDC_SAL_PROC_FIN     ) &&
           (u1_g_oxdc_rebyid_xidcnt <  u1_s_oxdc_rebyid_numof_xid) &&
           (u2_t_rdcnt              <  u2_g_OXDC_RBID_1CYC_READ  ));
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/16/2022  HU       ty19epf_ren_d1x_v220_r009 -> x25epf_ren_d1x_v100_r000, Function Name tydocan_rebyid ->             */
/*                                oxdocan_rebyid.                                                                                    */
/*  1.0.1     7/ 7/2023  ST       Update for OEM standardization.                                                                    */
/*  1.0.2     8/24/2023  TI       Maximum security level support.                                                                    */
/*                                                                                                                                   */
/*  * HU = Hayato Usui, DENSO                                                                                                        */
/*  * ST = Shohei Takada, DENSO                                                                                                      */
/*  * TI = Takaehisa Inoue, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
