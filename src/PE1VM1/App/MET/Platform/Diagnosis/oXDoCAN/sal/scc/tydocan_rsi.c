/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN Service Application Layer / Rewriting Specification Information                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_RSI_C_MAJOR                 (1)
#define TYDOCAN_RSI_C_MINOR                 (0)
#define TYDOCAN_RSI_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_nvmif_cfg_private.h"

#include "tydocan_rsi_cfg_private.h"
#include "tydocan_rsi.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define     TYDC_RSI_INC_VLD            (3U)

#define     TYDC_RSI_NB_N32             (4U)

#define     TYDC_RSI_MD_INI             (0U)
#define     TYDC_RSI_MD_RUN_RX          (1U)
#define     TYDC_RSI_MD_RUN_VLD         (2U)
#define     TYDC_RSI_MD_FIN             (3U)
#define     TYDC_RSI_MD_FAI             (4U)
#define     TYDC_RSI_MD_DTC             (5U)

#define     TYDC_RSI_RSLT_INI           (0x00U)     /* Initialized          */
#define     TYDC_RSI_RSLT_RUN           (0x01U)     /* Running              */
#define     TYDC_RSI_RSLT_FIN           (0x02U)     /* Finalized            */
#define     TYDC_RSI_RSLT_FAI           (0x03U)     /* Failed               */
#define     TYDC_RSI_RSLT_FTE           (0x04U)     /* Forced Termination   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4                 u4_rx_last;           /* Received Last Value             */
    U1                 u1_rx_inc;            /* Received incremental counter    */
}ST_TYDC_RSI_BUF;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                   u1_s_tydc_rsi_md_ctrl;
static U1                   u1_s_tydc_req_rid;

static U2                   u2_s_tydc_rsi_tm_elpsd;
static U2                   u2_s_tydc_rsi_tm_wri_sta;

static ST_TYDC_RSI_BUF      st_s_tydc_rsi_buf;
static U1                   u1_s_tydc_rsi_rxev_last;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_TyDoCANRsiFinInit(void);

static void     vd_s_TyDoCANRsiPduRx(void);
static U1       u1_s_TyDoCANRsiNvmWrite(void);
static U1       u1_s_TyDoCANRsiValid(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2     u2_s_TYDC_RSI_TOUT = (U2)7000U / (U2)10U;    /* 7s  */

/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANRsiInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANRsiInit(void)
{
    u1_s_tydc_rsi_md_ctrl       = (U1)TYDC_RSI_MD_INI;

    vd_s_TyDoCANRsiFinInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANRsiInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TyDoCANRsiFinInit(void)
{
    st_s_tydc_rsi_buf.u1_rx_inc     = (U1)0U;
    st_s_tydc_rsi_buf.u4_rx_last    = (U4)U4_MAX;
    u1_s_tydc_rsi_rxev_last         = (U1)OXCAN_RX_RXEV_CNT_MAX;

    u2_s_tydc_rsi_tm_elpsd          = (U2)0U;
    u2_s_tydc_rsi_tm_wri_sta        = (U2)0U;

    u1_s_tydc_req_rid               = (U1)TYDC_RSI_RID_UNKW;
}
/*===================================================================================================================================*/
/*  void      vd_g_TyDoCANRsiMainTask(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void      vd_g_TyDoCANRsiMainTask(void)
{
    U1      u1_t_igon;

    u1_t_igon = u1_g_VehopemdIgnOn();

    if(u1_t_igon == (U1)FALSE){
        u1_s_tydc_rsi_md_ctrl = (U1)TYDC_RSI_MD_INI;
        vd_s_TyDoCANRsiFinInit();
    }
    else if(u1_s_tydc_rsi_md_ctrl == (U1)TYDC_RSI_MD_RUN_RX){

        if(u2_s_tydc_rsi_tm_elpsd < u2_s_TYDC_RSI_TOUT){

            vd_s_TyDoCANRsiPduRx();
            u2_s_tydc_rsi_tm_elpsd++;

            if(st_s_tydc_rsi_buf.u1_rx_inc >= (U1)TYDC_RSI_INC_VLD){

                u2_s_tydc_rsi_tm_wri_sta  = u2_s_tydc_rsi_tm_elpsd;
                u2_s_tydc_rsi_tm_elpsd    = (U1)0U;
                u1_s_tydc_rsi_md_ctrl     = (U1)TYDC_RSI_MD_RUN_VLD;
            }
        }
        else{
            u1_s_tydc_rsi_md_ctrl         = (U1)TYDC_RSI_MD_FAI;
            vd_s_TyDoCANRsiFinInit();
        }
    }
    else if((u1_s_tydc_rsi_md_ctrl == (U1)TYDC_RSI_MD_RUN_VLD) &&
            (u1_s_tydc_req_rid     == (U1)TYDC_RSI_RID_1007  )){

        u1_s_tydc_rsi_md_ctrl = u1_s_TyDoCANRsiNvmWrite();
        if(u1_s_tydc_rsi_md_ctrl != (U1)TYDC_RSI_MD_RUN_VLD){

            vd_s_TyDoCANRsiFinInit();
        }
        else{
            u2_s_tydc_rsi_tm_elpsd++;
        }
    }
    else if((u1_s_tydc_rsi_md_ctrl == (U1)TYDC_RSI_MD_RUN_VLD) &&
            (u1_s_tydc_req_rid     == (U1)TYDC_RSI_RID_1008  )){

        u1_s_tydc_rsi_md_ctrl = u1_s_TyDoCANRsiValid();
        vd_s_TyDoCANRsiFinInit();
    }
    else{
            /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANRsiReqRun(const U1 u1_a_RID)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANRsiReqRun(const U1 u1_a_RID)
{
    U1 u1_t_proc;

    if(u1_s_tydc_req_rid == (U1)TYDC_RSI_RID_UNKW){

        u1_s_tydc_req_rid     = u1_a_RID;
        u1_s_tydc_rsi_md_ctrl = (U1)TYDC_RSI_MD_RUN_RX;
        u1_t_proc             = (U1)OXDC_SAL_PROC_FIN;
    }
    else if(u1_s_tydc_req_rid == u1_a_RID){

        u1_t_proc = (U1)OXDC_SAL_PROC_NR_24;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
    }
    
    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANRsiRsltChk(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANRsiRsltChk(void)
{
    U1      u1_t_rslt;

    switch(u1_s_tydc_rsi_md_ctrl){
        case    TYDC_RSI_MD_INI     :
            u1_t_rslt   =   (U1)TYDC_RSI_RSLT_INI;
            break;
        case    TYDC_RSI_MD_RUN_RX  :
            u1_t_rslt   =   (U1)TYDC_RSI_RSLT_RUN;
            break;
        case    TYDC_RSI_MD_RUN_VLD :
            u1_t_rslt   =   (U1)TYDC_RSI_RSLT_RUN;
            break;
        case    TYDC_RSI_MD_FIN     :
            u1_t_rslt   =   (U1)TYDC_RSI_RSLT_FIN;
            break;
        case    TYDC_RSI_MD_FAI     :
            u1_t_rslt   =   (U1)TYDC_RSI_RSLT_FAI;
            break;
        case    TYDC_RSI_MD_DTC     :
            u1_t_rslt   =   (U1)TYDC_RSI_RSLT_FIN;
            break;
        default :
            u1_t_rslt   =   (U1)TYDC_RSI_RSLT_FAI;
            break;
    }

    return(u1_t_rslt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANRsiTrchk(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANRsiTrchk(void)
{
    U1      u1_t_trchk;

    if(u1_s_tydc_rsi_md_ctrl == (U1)TYDC_RSI_MD_DTC){
        u1_t_trchk = (U1)TRUE;
    }
    else{
        u1_t_trchk = (U1)FALSE;
    }

    return(u1_t_trchk);
}
/*===================================================================================================================================*/
/*  void      vd_g_TyDoCANRsiDtcClr(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void      vd_g_TyDoCANRsiDtcClr(void)
{
    u1_s_tydc_rsi_md_ctrl = (U1)TYDC_RSI_MD_INI;
    vd_s_TyDoCANRsiFinInit();
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANRsiNvmIf_Ans(const U2 u2_a_DID, const U1 u1_a_NVM_OK, U4 * u4_ap_b32_tx)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANRsiNvmIf_Ans(const U2 u2_a_DID, const U1 u1_a_NVM_OK, U4 * u4_ap_b32_tx)
{
    if(u1_a_NVM_OK != (U1)TRUE ){

        u4_ap_b32_tx[TYDC_B32_WO_LA] = (U4)0U;
    }

    return((U1)OXDC_SAL_PROC_FIN);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANRsiNvmIf_Req(const U2 u2_a_DID, U4 * u4_ap_b32_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANRsiNvmIf_Req(const U2 u2_a_DID, U4 * u4_ap_b32_rx)
{
    return((U1)OXDC_SAL_PROC_RUN);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANRsiNvmIf_Syn(const U2 u2_a_DID)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANRsiNvmIf_Syn(const U2 u2_a_DID)
{
    U1            u1_t_proc;

    u1_t_proc = u1_g_TyDoCANNvmIfSynchk(u2_a_DID);
#if 0
    if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
        vd_g_VardefGradeUpdate();
    }
#endif

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANRsiXidSup(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANRsiXidSup(void)
{
    U1      u1_t_sup;

    if(u1_g_TYDC_RSI_SUP == (U1)TRUE){
        u1_t_sup = (U1)OXDC_XID_SUP_PUB;
    }
    else{
        u1_t_sup = (U1)OXDC_XID_SUP_NOT;
    }

    return(u1_t_sup);
}
/*===================================================================================================================================*/
/*  static void      vd_s_TyDoCANRsiPduRx(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_TyDoCANRsiPduRx(void)
{
    U4 ( *      fp_u4_t_sig)(void);
    U2          u2_t_pdu_idx;
    U2          u2_t_sys_chk;
    U2          u2_t_rx_tout;

    U1          u1_t_rx_stat;
    U1          u1_t_rxc_nex;
    U1          u1_t_rxc_inc;

    U4          u4_t_sig;

    fp_u4_t_sig  = st_gp_TYDC_RSI.stp_IF->fp_u4_SIG;
    u2_t_pdu_idx = st_gp_TYDC_RSI.u2_pdu_idx;
    u2_t_sys_chk = st_gp_TYDC_RSI.u2_sys_chk;
    u2_t_rx_tout = st_gp_TYDC_RSI.u2_rx_tout;


    u1_t_rx_stat  = u1_g_oXCANRxStat(u2_t_pdu_idx, u2_t_sys_chk, u2_t_rx_tout) & ((U1)COM_NO_RX | (U1)COM_TIMEOUT); 
    u1_t_rxc_nex  = u1_g_oXCANRxEvcnt(u2_t_pdu_idx);
    u1_t_rxc_inc  = (U1)(u1_t_rxc_nex - u1_s_tydc_rsi_rxev_last) & (U1)OXCAN_RX_RXEV_CNT_MAX;

    if(fp_u4_t_sig != vdp_PTR_NA){

        u4_t_sig = (* fp_u4_t_sig)();
    }
    else{
        u4_t_sig     = (U4)U4_MAX;
        u1_t_rx_stat = (U1)COM_NO_RX;
    }

    if((u1_t_rx_stat              ==  (U1)0U                       ) &&
        (u1_t_rxc_nex             <=  (U1)OXCAN_RX_RXEV_CNT_MAX    ) &&
        (u1_s_tydc_rsi_rxev_last  <=  (U1)OXCAN_RX_RXEV_CNT_MAX    ) &&
        (u1_t_rxc_inc             !=  (U1)0U                       )){

        if(st_s_tydc_rsi_buf.u4_rx_last == u4_t_sig){

            st_s_tydc_rsi_buf.u1_rx_inc++;
        }
        else{
            st_s_tydc_rsi_buf.u1_rx_inc = (U1)0U;
        }
    }
    else{
        /* Do nothing */
    }

    st_s_tydc_rsi_buf.u4_rx_last  = u4_t_sig;
    u1_s_tydc_rsi_rxev_last       = u1_t_rxc_nex;

}
/*===================================================================================================================================*/
/*  static U1    u1_s_TyDoCANRsiNvmWrite(const U2 u2_a_ELPSD)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_TyDoCANRsiNvmWrite(void)
{
    static const U2 u2_s_TYDC_RSI_NVMIF_TOUT  = (U2)5000U / (U2)10U;

    U4 ( *          fp_u4_t_chk)(const U4 u4_a_DATA);
    U4              u4_t_chk_data;

    U1              u1_tp_nvm_data[TYDC_RSI_NB_N32];

    U1              u1_t_next;
    U1              u1_t_proc;

    u1_t_next       = (U1)TYDC_RSI_MD_FAI;
    fp_u4_t_chk     = st_gp_TYDC_RSI.stp_IF->fp_u4_CHK;
    vd_g_MemfillU1(u1_tp_nvm_data, (U1)0U, (U4)TYDC_RSI_NB_N32);

    if(fp_u4_t_chk != vdp_PTR_NA){

        u4_t_chk_data   = (* fp_u4_t_chk)(st_s_tydc_rsi_buf.u4_rx_last);
        (void)u1_g_TyDoCANNu32Tx(u1_tp_nvm_data, u4_t_chk_data, (U2)TYDC_RSI_NB_N32);

        u1_t_proc = u1_g_TyDoCANNvmIfWrite(u1_tp_nvm_data, u2_s_tydc_rsi_tm_elpsd, (U2)TYDC_NVM_RSI);

        /*============================================================*/
        /* Rsi Time Out(7s) includes Nvmif Time Out(5s)               */
        /* u1_g_TyDoCANNvmIfWrite will start writing when timer is 0s */
        /*============================================================*/
        if(u2_s_tydc_rsi_tm_elpsd == (U2)0U){
            if(u2_s_tydc_rsi_tm_wri_sta  > (u2_s_TYDC_RSI_TOUT - u2_s_TYDC_RSI_NVMIF_TOUT)){

                u2_s_tydc_rsi_tm_elpsd = u2_s_TYDC_RSI_NVMIF_TOUT - (u2_s_TYDC_RSI_TOUT - u2_s_tydc_rsi_tm_wri_sta);
            }
            else{
                u2_s_tydc_rsi_tm_elpsd = u2_s_tydc_rsi_tm_wri_sta;
            }
        }

        if(u1_t_proc == (U1)OXDC_SAL_PROC_RUN){

            u1_t_next = (U1)TYDC_RSI_MD_RUN_VLD;
        }
        else if(u1_t_proc == (U1)OXDC_SAL_PROC_FIN){

            u1_t_next = (U1)TYDC_RSI_MD_FIN;
        }
        else{
            /* u1_t_next       = (U1)TYDC_RSI_MD_FAI; */
        }
    }
    else{
        /* u1_t_next       = (U1)TYDC_RSI_MD_FAI; */
    }

    return(u1_t_next);
}
/*===================================================================================================================================*/
/*  static U1    u1_s_TyDoCANRsiValid(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_TyDoCANRsiValid(void)
{
    U4 ( *          fp_u4_t_chk)(const U4 u4_a_DATA);
    U4              u4_t_vld_data;

    U1              u1_tp_nvm_data[TYDC_RSI_NB_N32];
    U4              u4_t_rea_data;

    U1              u1_t_next;
    U1              u1_t_proc;


    u1_t_next       = (U1)TYDC_RSI_MD_DTC;
    fp_u4_t_chk     = st_gp_TYDC_RSI.stp_IF->fp_u4_CHK;
    vd_g_MemfillU1(u1_tp_nvm_data, (U1)0U, (U4)TYDC_RSI_NB_N32);

    u1_t_proc = u1_g_TyDoCANNvmIfRead(u1_tp_nvm_data, (U2)TYDC_NVM_RSI);

    if((u1_t_proc   == (U1)OXDC_SAL_PROC_FIN) &&
       (fp_u4_t_chk != vdp_PTR_NA           )){

        u4_t_rea_data = u4_g_TyDoCANNu32(u1_tp_nvm_data, (U2)TYDC_RSI_NB_N32);
        u4_t_vld_data = (* fp_u4_t_chk)(st_s_tydc_rsi_buf.u4_rx_last);

        if(u4_t_rea_data == u4_t_vld_data){
            u1_t_next = (U1)TYDC_RSI_MD_FIN;
        }
        else{
            /* u1_t_next = (U1)TYDC_RSI_MD_DTC; */
        }
    }
    else{
        /* u1_t_next = (U1)TYDC_RSI_MD_DTC; */
    }

    return(u1_t_next);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     7/27/2020  AS       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19pfv3-1  5/28/2024  TN       Delete Grade reference.                                                                            */
/*                                                                                                                                   */
/*  * AS = Atsunori Sugita, DENSO-TECHNO                                                                                             */
/*  * TN = Tetsushi Nakano, DENSO-TECHNO                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
