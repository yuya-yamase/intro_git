/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_C_MAJOR                          (2U)
#define OXDOCAN_C_MINOR                          (0U)
#define OXDOCAN_C_PATCH                          (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"

#include "Dcm.h"
#include "Dcm_Apl_SID14.h"
#include "Dcm_Apl_SID19.h"
#include "Dcm_Apl_SID22.h"
#include "Dcm_Apl_SID2E.h"
#include "Dcm_Apl_SID31.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXDOCAN_C_MAJOR != OXDOCAN_H_MAJOR) || \
     (OXDOCAN_C_MINOR != OXDOCAN_H_MINOR) || \
     (OXDOCAN_C_PATCH != OXDOCAN_H_PATCH))
#error "oxdocan.c and oxdocan.h : source and header files are inconsistent!"
#endif

#if ((OXDOCAN_C_MAJOR != OXDOCAN_CFG_H_MAJOR) || \
     (OXDOCAN_C_MINOR != OXDOCAN_CFG_H_MINOR) || \
     (OXDOCAN_C_PATCH != OXDOCAN_CFG_H_PATCH))
#error "oxdocan.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
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
static Dcm_MsgContextType    st_s_oxdc_msg_trx;

static U2                    u2_s_oxdc_serv_tim_elpsd;

static U1                    u1_s_oxdc_serv_act;
static U1                    u1_s_oxdc_ses_bfr;
static U1                    u1_s_oxdc_task_cyccnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXdcInit(void);
static void    vd_s_oXdcServiceAct(const U1 u1_a_SID, const Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext);
static U1      u1_s_oXdcSessionchk(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANBonInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANBonInit(void)
{
    Dcm_ConfigType         st_t_type;

    st_t_type.InitMode   = (uint8)DCM_INITMODE_INIT;
    Dcm_Init(&st_t_type);
    vd_s_oXdcInit();

    vd_g_oXDoCANCfgBonInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRstInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRstInit(void)
{
    Dcm_ConfigType         st_t_type;

    st_t_type.InitMode   = (uint8)DCM_INITMODE_INIT;
    Dcm_Init(&st_t_type);
    vd_s_oXdcInit();

    vd_g_oXDoCANCfgRstInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANWkupInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANWkupInit(void)
{
    Dcm_ConfigType         st_t_type;

    st_t_type.InitMode   = (uint8)DCM_INITMODE_WAKEUP;
    Dcm_Init(&st_t_type);
    vd_s_oXdcInit();

    vd_g_oXDoCANCfgWkupInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANMainTask(void)
{
    ST_OXDC_REQ            st_t_req;
    ST_OXDC_ANS            st_t_ans;
    U2                     u2_t_tslot;

    /* ---------------------------------------------------------------------------------------------------- */
    if(u1_s_oxdc_task_cyccnt >= (U1)OXDC_TASK_NUM_SLOT){
        u1_s_oxdc_task_cyccnt = (U1)0U;
    }
    u2_t_tslot = (U2)0x0001U << u1_s_oxdc_task_cyccnt;
    u1_s_oxdc_task_cyccnt++;

    if(u2_s_oxdc_serv_tim_elpsd >= (U2)U2_MAX){
        u2_s_oxdc_serv_tim_elpsd = (U2)0U;
    }
    else if(u2_s_oxdc_serv_tim_elpsd >= (U2)OXDC_SERV_TIM_MAX){
        u2_s_oxdc_serv_tim_elpsd = (U2)OXDC_SERV_TIM_MAX;
    }
    else{
        u2_s_oxdc_serv_tim_elpsd++;
    }
    st_t_req.u1p_RX       = st_s_oxdc_msg_trx.reqData;
    st_t_req.u4_nbyte     = st_s_oxdc_msg_trx.reqDataLen;

    st_t_req.u2_tim_elpsd = u2_s_oxdc_serv_tim_elpsd;

    st_t_req.u1_sid       = u1_s_oxdc_serv_act;
    st_t_req.u1_req_type  = st_s_oxdc_msg_trx.msgAddInfo.reqType;
    st_t_req.u1_ses_bfr   = u1_s_oxdc_ses_bfr;
    st_t_req.u1_ses_aft   = u1_s_oXdcSessionchk();

    st_t_ans.u1p_tx       = st_s_oxdc_msg_trx.resData;
    st_t_ans.u4_nbyte     = st_s_oxdc_msg_trx.resMaxDataLen;

    /* ---------------------------------------------------------------------------------------------------- */
    vd_g_oXDoCANCfgMainbySid(&st_t_req, &st_t_ans, u2_t_tslot);
    /* ---------------------------------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANShtdwnOk(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_shtdwn : TRUE(Shutdown OK), FALSE(Shutdown NG)                                                           */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANShtdwnOk(void)
{
    return(Dcm_GetSleepPermission());
}
/*===================================================================================================================================*/
/*  Std_ReturnType u1_g_oXDoCANApl_SID14(Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
Std_ReturnType u1_g_oXDoCANApl_SID14(Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)
{
    vd_s_oXdcServiceAct((U1)OXDC_SID_14, OpStatus, pMsgContext);
    return((Std_ReturnType)E_OK); /* The return value is discarded in Aubist/Dcm. */
}
/*===================================================================================================================================*/
/*  Std_ReturnType u1_g_oXDoCANApl_SID19(Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
Std_ReturnType u1_g_oXDoCANApl_SID19(Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)
{
    vd_s_oXdcServiceAct((U1)OXDC_SID_19, OpStatus, pMsgContext);
    return((Std_ReturnType)E_OK); /* The return value is discarded in Aubist/Dcm. */
}
/*===================================================================================================================================*/
/*  Std_ReturnType u1_g_oXDoCANApl_SID22(Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
Std_ReturnType u1_g_oXDoCANApl_SID22(Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)
{
    vd_s_oXdcServiceAct((U1)OXDC_SID_22, OpStatus, pMsgContext);
    return((Std_ReturnType)E_OK); /* The return value is discarded in Aubist/Dcm. */
}
/*===================================================================================================================================*/
/*  Std_ReturnType u1_g_oXDoCANApl_SID2E(Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
Std_ReturnType u1_g_oXDoCANApl_SID2E(Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)
{
    vd_s_oXdcServiceAct((U1)OXDC_SID_2E, OpStatus, pMsgContext);
    return((Std_ReturnType)E_OK); /* The return value is discarded in Aubist/Dcm. */
}
/*===================================================================================================================================*/
/*  Std_ReturnType u1_g_oXDoCANApl_SID31(Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
Std_ReturnType u1_g_oXDoCANApl_SID31(Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)
{
    vd_s_oXdcServiceAct((U1)OXDC_SID_31, OpStatus, pMsgContext);
    return((Std_ReturnType)E_OK); /* The return value is discarded in Aubist/Dcm. */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANAnsTx(const U1 u1_a_NRC, const ST_OXDC_ANS * st_ap_ANS)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANAnsTx(const U1 u1_a_NRC, const ST_OXDC_ANS * st_ap_ANS)
{
    if(u1_s_oxdc_serv_act >= (U1)OXDC_NUM_SID){
        /* do nothing */
    }
    else if(u1_a_NRC > (U1)OXDC_SAL_PROC_FIN){
        Dcm_ExternalSetNegResponse(&st_s_oxdc_msg_trx, u1_a_NRC);
        Dcm_ExternalProcessingDone(&st_s_oxdc_msg_trx);
    }
    else if((st_ap_ANS           != vdp_PTR_NA               ) &&
            (st_ap_ANS->u1p_tx   == st_s_oxdc_msg_trx.resData) &&
            (st_ap_ANS->u4_nbyte >  (U4)0U                   )){
        st_s_oxdc_msg_trx.resDataLen = st_ap_ANS->u4_nbyte;
        Dcm_ExternalProcessingDone(&st_s_oxdc_msg_trx);
    }
    else{
        Dcm_SendNegativeNoResponse(&st_s_oxdc_msg_trx);
    }

    st_s_oxdc_msg_trx.reqData                        = vdp_PTR_NA;
    st_s_oxdc_msg_trx.reqDataLen                     = (Dcm_MsgLenType)0U;
    st_s_oxdc_msg_trx.resData                        = vdp_PTR_NA;
    st_s_oxdc_msg_trx.resDataLen                     = (Dcm_MsgLenType)0U;
    st_s_oxdc_msg_trx.msgAddInfo.reqType             = (uint8)0U;
    st_s_oxdc_msg_trx.msgAddInfo.suppressPosResponse = (uint8)0U;
    st_s_oxdc_msg_trx.resMaxDataLen                  = (Dcm_MsgLenType)0U;
    st_s_oxdc_msg_trx.idContext                      = (Dcm_IdContextType)0U;
    st_s_oxdc_msg_trx.dcmRxPduId                     = (PduIdType)0U;

    u2_s_oxdc_serv_tim_elpsd = (U2)OXDC_SERV_TIM_MAX;
    u1_s_oxdc_serv_act       = (U1)OXDC_SID_INA;
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcInit(void)
{
    st_s_oxdc_msg_trx.reqData                        = vdp_PTR_NA;
    st_s_oxdc_msg_trx.reqDataLen                     = (Dcm_MsgLenType)0U;
    st_s_oxdc_msg_trx.resData                        = vdp_PTR_NA;
    st_s_oxdc_msg_trx.resDataLen                     = (Dcm_MsgLenType)0U;
    st_s_oxdc_msg_trx.msgAddInfo.reqType             = (uint8)0U;
    st_s_oxdc_msg_trx.msgAddInfo.suppressPosResponse = (uint8)0U;
    st_s_oxdc_msg_trx.resMaxDataLen                  = (Dcm_MsgLenType)0U;
    st_s_oxdc_msg_trx.idContext                      = (Dcm_IdContextType)0U;
    st_s_oxdc_msg_trx.dcmRxPduId                     = (PduIdType)0U;

    u2_s_oxdc_serv_tim_elpsd       = (U2)OXDC_SERV_TIM_MAX;
    u1_s_oxdc_serv_act             = (U1)OXDC_SID_INA;
    u1_s_oxdc_ses_bfr              = (U1)OXDC_SESSION_DEF;

    u1_s_oxdc_task_cyccnt          = (U1)OXDC_TASK_NUM_SLOT;
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcServiceAct(const U1 u1_a_SID, const Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcServiceAct(const U1 u1_a_SID, const Dcm_OpStatusType OpStatus, const Dcm_MsgContextType * pMsgContext)
{
    if(OpStatus == DCM_INITIAL){

        st_s_oxdc_msg_trx.reqData                        = pMsgContext->reqData;
        st_s_oxdc_msg_trx.reqDataLen                     = pMsgContext->reqDataLen;
        st_s_oxdc_msg_trx.resData                        = pMsgContext->resData;
        st_s_oxdc_msg_trx.resDataLen                     = pMsgContext->resDataLen;
        st_s_oxdc_msg_trx.msgAddInfo.reqType             = pMsgContext->msgAddInfo.reqType;
        st_s_oxdc_msg_trx.msgAddInfo.suppressPosResponse = pMsgContext->msgAddInfo.suppressPosResponse;
        st_s_oxdc_msg_trx.resMaxDataLen                  = pMsgContext->resMaxDataLen;
        st_s_oxdc_msg_trx.idContext                      = pMsgContext->idContext;
        st_s_oxdc_msg_trx.dcmRxPduId                     = pMsgContext->dcmRxPduId;

        u2_s_oxdc_serv_tim_elpsd = (U2)U2_MAX;
        u1_s_oxdc_serv_act       = u1_a_SID;
    }
    else{

        st_s_oxdc_msg_trx.reqData                        = vdp_PTR_NA;
        st_s_oxdc_msg_trx.reqDataLen                     = (Dcm_MsgLenType)0U;
        st_s_oxdc_msg_trx.resData                        = vdp_PTR_NA;
        st_s_oxdc_msg_trx.resDataLen                     = (Dcm_MsgLenType)0U;
        st_s_oxdc_msg_trx.msgAddInfo.reqType             = (uint8)0U;
        st_s_oxdc_msg_trx.msgAddInfo.suppressPosResponse = (uint8)0U;
        st_s_oxdc_msg_trx.resMaxDataLen                  = (Dcm_MsgLenType)0U;
        st_s_oxdc_msg_trx.idContext                      = (Dcm_IdContextType)0U;
        st_s_oxdc_msg_trx.dcmRxPduId                     = (PduIdType)0U;

        u2_s_oxdc_serv_tim_elpsd = (U2)OXDC_SERV_TIM_MAX;
        u1_s_oxdc_serv_act       = (U1)OXDC_SID_INA;
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXdcSessionchk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXdcSessionchk(void)
{
    U1                     u1_t_ses_aft;

    u1_t_ses_aft = (U1)OXDC_SESSION_DEF;
    (void)Dcm_GetSesCtrlType(&u1_t_ses_aft);
    u1_s_oxdc_ses_bfr = u1_t_ses_aft;

    return(u1_t_ses_aft);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/16/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000, Function Name tydocan -> oxdocan.          */
/*  1.0.1    12/13/2022  TM       Aubist/SEC Gen1 -> Gen2.                                                                           */
/*  1.0.2     7/ 6/2023  ST       Adding PreInit Function call.                                                                      */
/*  1.0.3     8/24/2023  TI       Maximum security level support.                                                                    */
/*  1.0.4    11/23/2023  ToI      Reflects change in function name oxdocan_ssr -> oxdocan_tmstp.                                     */
/*  1.0.5     2/23/2024  ToI      Added vd_g_oXDoCANStaTmrwk.                                                                        */
/*  1.0.6     3/11/2024  ToI      Added SID$86.                                                                                      */
/*  1.0.7     9/ 6/2024  ToI      Added vd_g_oXDoCANAubIfStoreReqData, vd_g_oXDoCANGetStoredReqData.                                 */
/*  1.0.8     9/25/2024  II       Bug Fixed. Reprog Software Jump function.                                                          */
/*                                                                                                                                   */
/*  * HU = Hayato Usui, DENSO                                                                                                        */
/*  * TM = Takanori Maruyama, DENSO                                                                                                  */
/*  * ST = Shohei Takada, DENSO                                                                                                      */
/*  * TI = Takaehisa Inoue, DENSO                                                                                                    */
/*  * ToI= Tomoko Inuzuka, DENSO                                                                                                     */
/*  * II = Itsuki Ito, DENSO                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
