/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXention of CAN Aubist Interface Layer                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_AUBIF_COM_C_MAJOR                  (2U)
#define OXCAN_AUBIF_COM_C_MINOR                  (0U)
#define OXCAN_AUBIF_COM_C_PATCH                  (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_aubif_cfg_private.h"
#include "oxcan_aubif.h"

#include "bsw_com_config.h"            /* BSW_COM_TX_MSG_NUM is defined in bsw_com_config.h            */

#include "bsw_com_st.h"                /* bsw_com_stMsgInfoTbl[] is defined in bsw_com_st.h            */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_E2E_NUM_TRA > 0U) || (OXCAN_E2E_NUM_REC > 0U))
#include "E2E.h"
#endif /* #if ((OXCAN_E2E_NUM_TRA > 0U) || (OXCAN_E2E_NUM_REC > 0U)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_AUBIF_COM_C_MAJOR != OXCAN_AUBIF_H_MAJOR) || \
     (OXCAN_AUBIF_COM_C_MINOR != OXCAN_AUBIF_H_MINOR) || \
     (OXCAN_AUBIF_COM_C_PATCH != OXCAN_AUBIF_H_PATCH))
#error "oxcan_aubif_com.c and oxcan_aubif.h : source and header files are inconsistent!"
#endif

#if ((OXCAN_AUBIF_COM_C_MAJOR != OXCAN_AUBIF_CFG_H_MAJOR) || \
     (OXCAN_AUBIF_COM_C_MINOR != OXCAN_AUBIF_CFG_H_MINOR) || \
     (OXCAN_AUBIF_COM_C_PATCH != OXCAN_AUBIF_CFG_H_PATCH))
#error "oxcan_aubif_com.c and oxcan_aubif_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_E2E_OFFSET                         (0U)
#define OXCAN_E2E_MAX_DELTA_CNT                  (3U)
#define OXCAN_E2E_LEN_BYT_TO_BIT                 (3U)

#if (OXCAN_OMA_NUM_REC > 0U)
#define OXCAN_OMA_OFFSET_VR                      (4U)
#define OXCAN_OMA_OFFSET_FV                      (11U)
#endif /* #if (OXCAN_OMA_NUM_REC > 0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_E2E_NUM_TRA > 0U)
static E2E_P05ProtectStateType            st_sp_oxcan_e2e_tra[OXCAN_E2E_NUM_TRA];
#endif /* #if (OXCAN_E2E_NUM_TRA > 0U) */

#if (OXCAN_E2E_NUM_REC > 0U)
static E2E_P05CheckStateType              st_sp_oxcan_e2e_rec[OXCAN_E2E_NUM_REC]; 
#endif /* #if (OXCAN_E2E_NUM_REC > 0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_E2E_NUM_TRA > 0U)
static inline void    vd_s_oXCANAubIfE2ePrepTx(PduIdType PduId, PduInfoType* PduInfoPtr);
#endif /* #if (OXCAN_E2E_NUM_TRA != 0U) */
#if (OXCAN_E2E_NUM_REC > 0U)
static inline U1      u1_s_oXCANAubIfE2eRxOk(PduIdType PduId, BswConstR PduInfoType* PduInfoPtr);
#endif /* #if (OXCAN_E2E_NUM_REC > 0U) */

#if (OXCAN_OMA_NUM_REC > 0U)
static inline U1      u1_s_oXCANAubIfOMARxOk(PduIdType PduId, BswConstR PduInfoType* PduInfoPtr);
#endif /* #if (OXCAN_OMA_NUM_REC > 0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/



#if (BSW_COM_TX_MSG_NUM > 0U)



/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  boolean Com_TxIpduCallout( PduIdType PduId, PduInfoType* PduInfoPtr )                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Aubist/cs Type Definitions                                                                                                       */
/*                  PduIdType:      typedef unsigned short                                                                           */
/*                  PduInfoType:    refer to following member                                                                        */
/*                      - SduDataPtr:   unsigned char * SduDataPtr                                                                   */
/*                      - SduLength:    unsigned short  SduLength                                                                    */
/*===================================================================================================================================*/
boolean Com_TxIpduCallout( PduIdType PduId, PduInfoType* PduInfoPtr )
{
#if (OXCAN_E2E_NUM_TRA > 0U)
    vd_s_oXCANAubIfE2ePrepTx(PduId, PduInfoPtr);
#endif /* #if (OXCAN_E2E_NUM_TRA > 0U) */

#if ((defined(CAN_LPR_H)) && (CAN_LPR_RR_EN_IPDU_TX == 1U))
    return(u1_g_CANLpRIngIPduTx(PduId, PduInfoPtr));
#else
    return((boolean)TRUE);
#endif /* #if ((defined(CAN_LPR_H)) && (CAN_LPR_RR_EN_IPDU_TX == 1U)) */
}
/*===================================================================================================================================*/
/*  void    Com_CbkTxReq(NetworkHandleType network, PduIdType PduId, Com_TxModeType TxMode)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Aubist/cs Type Definitions                                                                                                       */
/*                  NetworkHandleType:  typedef unsigned char                                                                        */
/*                  PduIdType:          typedef unsigned short                                                                       */
/*                  Com_TxModeType:     typedef unsigned char                                                                        */
/*===================================================================================================================================*/
void    Com_CbkTxReq(NetworkHandleType network, PduIdType PduId, Com_TxModeType TxMode)
{
    vd_g_oXCANUsrhkIPduTraReq(network, PduId, TxMode);
}
/*===================================================================================================================================*/
/*  void    Com_CbkTxAck(PduIdType PduId)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Aubist/cs Type Definitions                                                                                                       */
/*                  PduIdType:          typedef unsigned short                                                                       */
/*===================================================================================================================================*/
void    Com_CbkTxAck(PduIdType PduId)
{
    vd_g_oXCANUsrhkIPduTraAck(PduId);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/



#endif /* #if (BSW_COM_TX_MSG_NUM > 0U) */



/*-----------------------------------------------------------------------------------------------------------------------------------*/



#if ((OXCAN_E2E_NUM_REC > 0U) || (OXCAN_OMA_NUM_REC > 0U))



/*===================================================================================================================================*/
/*  boolean Com_RxIpduCallout(PduIdType PduId, BswConstR PduInfoType* PduInfoPtr)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Aubist/cs Type Definitions                                                                                                       */
/*                  PduIdType:      typedef unsigned short                                                                           */
/*                  BswConstR:      #define BswConstR   const                                                                        */
/*                  PduInfoType:    refer to following member                                                                        */
/*                      - SduDataPtr:   unsigned char * SduDataPtr                                                                   */
/*                      - SduLength:    unsigned short  SduLength                                                                    */
/*                  boolean:        typedef unsigned char                                                                            */
/*===================================================================================================================================*/
boolean Com_RxIpduCallout(PduIdType PduId, BswConstR PduInfoType* PduInfoPtr)
{
    
    boolean u1_t_ret;
    
    u1_t_ret = (boolean)TRUE;
    
    
    #if (OXCAN_OMA_NUM_REC > 0U)
    u1_t_ret = u1_s_oXCANAubIfOMARxOk(PduId, PduInfoPtr);
    #endif /* #if (OXCAN_OMA_NUM_REC > 0U) */
    
    
    #if (OXCAN_E2E_NUM_REC > 0U)
    if(u1_t_ret == (boolean)TRUE){
        u1_t_ret = u1_s_oXCANAubIfE2eRxOk(PduId, PduInfoPtr);
    }
    #endif /* #if (OXCAN_E2E_NUM_REC > 0U) */
    
    return(u1_t_ret);
}
#endif /* #if ((OXCAN_E2E_NUM_REC > 0U) || (OXCAN_OMA_NUM_REC > 0U)) */
/*===================================================================================================================================*/
/*  void    Com_CbkRxAck(PduIdType PduId)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Aubist/cs Type Definitions                                                                                                       */
/*                  PduIdType:          typedef unsigned short                                                                       */
/*===================================================================================================================================*/
void    Com_CbkRxAck(PduIdType PduId)
{
#if ((OXCAN_LIB_CFG_EN_RXD == 1U) || (OXCAN_LIB_CFG_EN_RXD == 2U))
    vd_g_oXCANRxdPduAck((U1)OXCAN_RXD_GR_CAN, PduId);
#endif /* #if ((OXCAN_LIB_CFG_EN_RXD == 1U) || (OXCAN_LIB_CFG_EN_RXD == 2U)) */

#ifdef OXDOCAN_AUBIF_MA_H
    vd_g_TyDoCANAubIfComKzkRx(PduId);
#endif /* #ifdef OXDOCAN_AUBIF_MA_H */

    vd_g_oXCANUsrhkIPduRecAck(PduId);
}
/*===================================================================================================================================*/

#if ((OXCAN_E2E_NUM_TRA > 0U) || (OXCAN_E2E_NUM_REC > 0U))

/*===================================================================================================================================*/
/*  void    vd_g_oXCANAubIfE2eInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANAubIfE2eInit(void)
{
    U4                           u4_t_lpcnt;

#if (OXCAN_E2E_NUM_TRA > 0U)
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_E2E_NUM_TRA; u4_t_lpcnt++){
        /* typedef struct {           */
        /*     uint8 Counter;         */
        /* } E2E_P05ProtectStateType; */
        st_sp_oxcan_e2e_tra[u4_t_lpcnt].Counter = (U1)0U;
    }
#endif /* #if (OXCAN_E2E_NUM_TRA > 0U) */

#if (OXCAN_E2E_NUM_REC > 0U)
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_E2E_NUM_REC; u4_t_lpcnt++){
        /* typedef uint8 E2E_P05CheckStatusType; */
        /* typedef struct {                      */
        /*     E2E_P05CheckStatusType  Status;   */
        /*     uint8                   Counter;  */
        /* } E2E_P05CheckStateType;              */
        st_sp_oxcan_e2e_rec[u4_t_lpcnt].Status  = E2E_P05STATUS_ERROR;
        st_sp_oxcan_e2e_rec[u4_t_lpcnt].Counter = (U1)U1_MAX;
    }
#endif /* #if (OXCAN_E2E_NUM_REC > 0U) */
}
#endif /* #if ((OXCAN_E2E_NUM_TRA > 0U) || (OXCAN_E2E_NUM_REC > 0U)) */
/*===================================================================================================================================*/

#if (OXCAN_E2E_NUM_TRA > 0U)

/*===================================================================================================================================*/
/*  static inline void    vd_s_oXCANAubIfE2ePrepTx(PduIdType PduId, PduInfoType* PduInfoPtr)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_oXCANAubIfE2ePrepTx(PduIdType PduId, PduInfoType* PduInfoPtr)
{
    E2E_P05ConfigType            st_t_cfg;
    U2                           u2_t_length;
    U2                           u2_t_offset;
    U1                           u1_t_ok;

    /* ----------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                           */
    /* ----------------------------------------------------------------------------------------------------- */
    /* To prevent build errors, the check for an unsigned integer being greater than or equal to zero        */
    /* is omitted when OXCAN_E2E_TRA_MIN is 0.                                                               */
    /* ----------------------------------------------------------------------------------------------------- */
#if (OXCAN_E2E_TRA_MIN > 0U)
    if((PduId >= (U2)OXCAN_E2E_TRA_MIN) &&
       (PduId <= (U2)OXCAN_E2E_TRA_MAX)){
#else
    if(PduId <= (U2)OXCAN_E2E_TRA_MAX){
#endif /* #if (OXCAN_E2E_TRA_MIN > 0U) */
 
        u2_t_offset = PduId - (U2)OXCAN_E2E_TRA_MIN;
        u2_t_offset = u2_gp_OXCAN_E2E_TRA_BY_IPDU[u2_t_offset];
        if((u2_t_offset           <  (U2)OXCAN_E2E_NUM_TRA                   ) &&
           (PduInfoPtr->SduLength >= (U4)u1_gp_OXCAN_E2E_TRA_LEN[u2_t_offset])){

            u2_t_length              = (U2)u1_gp_OXCAN_E2E_TRA_LEN[u2_t_offset];
            st_t_cfg.Offset          = (U2)OXCAN_E2E_OFFSET;
            st_t_cfg.DataLength      = u2_t_length << OXCAN_E2E_LEN_BYT_TO_BIT;
            st_t_cfg.DataID          = (U2)Com_GetFrameID(PduId);
            st_t_cfg.MaxDeltaCounter = (U1)OXCAN_E2E_MAX_DELTA_CNT;
            (void)E2E_P05Protect(&st_t_cfg, &st_sp_oxcan_e2e_tra[u2_t_offset], PduInfoPtr->SduDataPtr, u2_t_length);
        }
    }
}
#endif /* #if (OXCAN_E2E_NUM_TRA > 0U) */
/*===================================================================================================================================*/

#if (OXCAN_E2E_NUM_REC > 0U)

/*===================================================================================================================================*/
/*  static inline U1      u1_s_oXCANAubIfE2eRxOk(PduIdType PduId, BswConstR PduInfoType* PduInfoPtr)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U1      u1_s_oXCANAubIfE2eRxOk(PduIdType PduId, BswConstR PduInfoType* PduInfoPtr)
{
    E2E_P05CheckStateType *      st_tp_rec;
    E2E_P05ConfigType            st_t_cfg;
    U2                           u2_t_offset;
    U2                           u2_t_length;
    U1                           u1_t_ok;

    u1_t_ok = (U1)TRUE;

    /* ----------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                           */
    /* ----------------------------------------------------------------------------------------------------- */
    /* To prevent build errors, the check for an unsigned integer being greater than or equal to zero        */
    /* is omitted when OXCAN_E2E_REC_MIN is 0.                                                               */
    /* ----------------------------------------------------------------------------------------------------- */
#if (OXCAN_E2E_REC_MIN > 0U)
    if((PduId >= (U2)OXCAN_E2E_REC_MIN) &&
       (PduId <= (U2)OXCAN_E2E_REC_MAX)){
#else
    if(PduId <= (U2)OXCAN_E2E_REC_MAX){
#endif /* #if (OXCAN_E2E_REC_MIN > 0U) */

        u2_t_offset = PduId - (U2)OXCAN_E2E_REC_MIN;
        u2_t_offset = u2_gp_OXCAN_E2E_REC_BY_IPDU[u2_t_offset];
        if(u2_t_offset >= (U2)OXCAN_E2E_NUM_REC){
         /* u1_t_ok = (U1)TRUE; */
        }
        else if(PduInfoPtr->SduLength < (U4)u1_gp_OXCAN_E2E_REC_LEN[u2_t_offset]){
            u1_t_ok = (U1)FALSE;
        }
        else{
            u2_t_length              = (U2)u1_gp_OXCAN_E2E_REC_LEN[u2_t_offset];
            st_t_cfg.Offset          = (U2)OXCAN_E2E_OFFSET;
            st_t_cfg.DataLength      = u2_t_length << OXCAN_E2E_LEN_BYT_TO_BIT;
            st_t_cfg.DataID          = (U2)Com_GetFrameID(PduId);
            st_t_cfg.MaxDeltaCounter = (U1)OXCAN_E2E_MAX_DELTA_CNT;

            /* #define E2E_P05STATUS_OK                (E2E_P05CheckStatusType)(0x00U) */
            /* #define E2E_P05STATUS_NONEWDATA         (E2E_P05CheckStatusType)(0x01U) */
            /* #define E2E_P05STATUS_ERROR             (E2E_P05CheckStatusType)(0x07U) */
            /* #define E2E_P05STATUS_REPEATED          (E2E_P05CheckStatusType)(0x08U) */
            /* #define E2E_P05STATUS_OKSOMELOST        (E2E_P05CheckStatusType)(0x20U) */
            /* #define E2E_P05STATUS_WRONGSEQUENCE     (E2E_P05CheckStatusType)(0x40U) */
            st_tp_rec          = &st_sp_oxcan_e2e_rec[u2_t_offset];
            st_tp_rec->Status  = E2E_P05STATUS_ERROR;
            (void)E2E_P05Check(&st_t_cfg, st_tp_rec, PduInfoPtr->SduDataPtr, u2_t_length);

            st_tp_rec->Status &= ((U1)U1_MAX ^ (U1)E2E_P05STATUS_OKSOMELOST);
            if(st_tp_rec->Status != E2E_P05STATUS_OK){
                u1_t_ok = (U1)FALSE;
            }
        }
    }

    return(u1_t_ok);
}
#endif /* #if (OXCAN_E2E_NUM_REC > 0U) */


#if (OXCAN_OMA_NUM_REC > 0U)
/*===================================================================================================================================*/
/*  static inline U1      u1_s_oXCANAubIfOMARxOk(PduIdType PduId, BswConstR PduInfoType* PduInfoPtr)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  OMA = On-Board MAC Authentication                                                                                                */
/*===================================================================================================================================*/
static inline U1      u1_s_oXCANAubIfOMARxOk(PduIdType PduId, BswConstR PduInfoType* PduInfoPtr)
{
    
    U4                           u4_t_sduLength;
#if (OXCAN_OMA_SEV_GEN == 1U)
    U4                           u4_t_canid;
    U4                           u4_t_pos;
#endif /* #if (OXCAN_OMA_SEV_GEN == 1U) */
    U2                           u2_t_offset;
    U1                           u1_t_oma_ret;
    U1                           u1_t_ret;

    u1_t_ret = (U1)TRUE;
    
    
#if (OXCAN_OMA_REC_MIN > 0U)
    if((PduId >= (U2)OXCAN_OMA_REC_MIN) &&
       (PduId <= (U2)OXCAN_OMA_REC_MAX)){
#else
    if(PduId <= (U2)OXCAN_OMA_REC_MAX){
#endif /* #if (OXCAN_OMA_REC_MIN > 0U) */

        u2_t_offset = PduId - (U2)OXCAN_OMA_REC_MIN;
        u2_t_offset = u2_gp_OXCAN_OMA_REC_BY_IPDU[u2_t_offset];
        if(u2_t_offset >= (U2)OXCAN_OMA_NUM_REC){
            /* u1_t_ret = (U1)TRUE; */
        }
        else if(PduInfoPtr->SduLength < (U4)u1_gp_OXCAN_OMA_REC_LEN[u2_t_offset]){
            u1_t_ret = (U1)FALSE;
        }
        else{
            u4_t_sduLength = PduInfoPtr->SduLength - (U4)OXCAN_OMA_OFFSET_VR;
            u1_t_oma_ret = PduInfoPtr->SduDataPtr[u4_t_sduLength];
            
            /* #define SECOC_VERIFICATIONSUCCESS                ((SecOC_VerificationResultType)0x00)  */
            /* #define SECOC_VERIFICATIONFAILURE                ((SecOC_VerificationResultType)0x01)  */
            /* #define SECOC_FRESHNESSFAILURE                   ((SecOC_VerificationResultType)0x02)  */
            /* #define SECOC_AUTHENTICATIONBUILDFAILURE         ((SecOC_VerificationResultType)0x03)  */
            /* #define SECOC_NO_VERIFICATION                    ((SecOC_VerificationResultType)0x04)  */
            /* #define SECOC_VERIFICATIONFAILURE_OVERWRITTEN    ((SecOC_VerificationResultType)0x05)  */
            /* #define SECOC_AB_VERIFICATIONFAILURE_VERIFYSTART ((SecOC_VerificationResultType)0x40)  */
            
            if(u1_t_oma_ret != (U1)0x00U){
                u1_t_ret = (U1)FALSE;
            }
            vd_g_oXCANUsrhkOmaRecRslt(u2_t_offset ,u1_t_oma_ret);
#if (OXCAN_OMA_SEV_GEN == 1U)
            u4_t_canid = Com_GetFrameID(PduId);
            u4_t_pos = PduInfoPtr->SduLength - (U4)OXCAN_OMA_OFFSET_FV;
            vd_g_oXSECIedOmaRslt(u2_t_offset, u1_t_oma_ret, u4_t_canid, (const U1 *)&PduInfoPtr->SduDataPtr[u4_t_pos]);  
#endif /* #if (OXCAN_OMA_SEV_GEN == 1U) */
        }
    }
    return(u1_t_ret);
    
}
#endif /* #if (OXCAN_OMA_NUM_REC > 0U) */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     2/21/2025  TN       oxcan_aubif.c v1.2.0 -> v2.0.0 was redesigned for Toyota BEVStep3.                                 */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
