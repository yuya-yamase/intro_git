/* 1.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXention of CAN Aubist Interface Layer                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_AUBIF_COM_C_MAJOR                  (1U)
#define OXCAN_AUBIF_COM_C_MINOR                  (3U)
#define OXCAN_AUBIF_COM_C_PATCH                  (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_aubif_cfg_private.h"
#include "oxcan_aubif.h"

#include "bsw_com_config.h"            /* BSW_COM_TX_MSG_NUM is defined in bsw_com_config.h            */

#include "bsw_com_st.h"                /* bsw_com_stMsgInfoTbl[] is defined in bsw_com_st.h            */
#include "bsw_cannm_ch_config.h"       /* BSW_CANNM_NM_TYPE_USE(x) is defined in bsw_cannm_ch_config.h */

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
#define OXCAN_E2E_MAXDELTACNT                    (3U)

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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
    U1                  u1_t_ok;

    u1_t_ok = u1_g_oXCANMsgOnline(PduId);
#if (OXCAN_E2E_NUM_REC > 0U)
    if(u1_t_ok == (U1)TRUE){
        u1_t_ok = u1_s_oXCANAubIfE2eRxOk(PduId, PduInfoPtr);
    }
#endif /* #if (OXCAN_E2E_NUM_REC > 0U) */

    return(u1_t_ok);
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
    vd_g_oXCANUsrhkTxConfirm(PduId, network, TxMode);
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
    vd_g_oXCANUsrhkTxAck(PduId);
}
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
    if(PduId < (U2)BSW_COM_MSG_NUM){
        vd_g_oXCANRxAck(bsw_com_stMsgInfoTbl[PduId].u1Network, PduId);
    }

#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS   )  ) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)  ) && \
     (BSW_BSWM_CS_CFG_FUNC_CS    == BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC == BSW_USE))
    vd_g_TyDoCANAubIfComKzkRx(PduId);
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && ... */

    vd_g_oXCANUsrhkRxMsg(PduId);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/



#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)



/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  boolean Com_CbkPreEventTxReq(PduIdType PduId)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Aubist/cs Type Definitions                                                                                                       */
/*                  PduIdType:          typedef unsigned short                                                                       */
/*                  boolean:            typedef unsigned char                                                                        */
/*===================================================================================================================================*/
boolean Com_CbkPreEventTxReq(PduIdType PduId)
{
#if (BSW_COM_TX_MSG_NUM > 0U)
    if(PduId < (U2)BSW_COM_TX_MSG_NUM){
        vd_g_oXCANNmwkEvtxByCh(bsw_com_stMsgInfoTbl[PduId].u1Network);
        vd_g_oXCANUsrhkEvtxReqed(PduId);
    }
#endif

    return((boolean)TRUE);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/



#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */



/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  boolean    Com_CbkCounterErr(PduIdType PduId, Std_ReturnType CheckResult, uint8 ExpectedCounter, uint8 ReceivedCounter)          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Aubist/cs Type Definitions                                                                                                       */
/*                  PduIdType:          typedef unsigned short                                                                       */
/*                  Std_ReturnType:     typedef unsigned char                                                                        */
/*                  uint8:              typedef unsigned char                                                                        */
/*                  boolean:            typedef unsigned char                                                                        */
/*===================================================================================================================================*/
boolean    Com_CbkCounterErr(PduIdType PduId, Std_ReturnType CheckResult, uint8 ExpectedCounter, uint8 ReceivedCounter)
{
    U1          u1_t_permission;

    if(CheckResult == COM_FIRST_RX){
        u1_t_permission = (U1)TRUE;
    }
    else{
        u1_t_permission = u1_g_oXCANUsrhkCntChk(PduId, CheckResult, ExpectedCounter, ReceivedCounter);
    }

    return(u1_t_permission);
}
/*===================================================================================================================================*/
/*  void    Com_CbkTxTOut(PduIdType PduId)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Aubist/cs Type Definitions                                                                                                       */
/*                  PduIdType:          typedef unsigned short                                                                       */
/*===================================================================================================================================*/
void    Com_CbkTxTOut(PduIdType PduId)
{
    vd_g_oXCANUsrhkTxTOut(PduId);
}
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
    vd_s_oXCANAubIfE2ePrepTx(PduId, PduInfoPtr );
#endif /* #if (OXCAN_E2E_NUM_TRA > 0U) */

    return ((boolean)TRUE);
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
        st_sp_oxcan_e2e_tra[u4_t_lpcnt].Counter = (U1)0;
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
        st_sp_oxcan_e2e_rec[u4_t_lpcnt].Counter = (U1)0U;
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

    if((PduId >= (U2)OXCAN_E2E_TRA_MIN) &&
       (PduId <= (U2)OXCAN_E2E_TRA_MAX)){
 
        u2_t_offset = PduId - (U2)OXCAN_E2E_TRA_MIN;
        u2_t_offset = u2_gp_OXCAN_E2E_TRA_BY_PDU[u2_t_offset];
        if(u2_t_offset < (U2)OXCAN_E2E_NUM_TRA){

            u2_t_length              = PduInfoPtr->SduLength;
            st_t_cfg.Offset          = (U2)OXCAN_E2E_OFFSET;
            st_t_cfg.DataLength      = u2_t_length << 3U;
            st_t_cfg.DataID          = (U2)Com_GetFrameID(PduId);
            st_t_cfg.MaxDeltaCounter = (U1)OXCAN_E2E_MAXDELTACNT;
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
    if((PduId >= (U2)OXCAN_E2E_REC_MIN) &&
       (PduId <= (U2)OXCAN_E2E_REC_MAX)){

        u2_t_offset = PduId - (U2)OXCAN_E2E_REC_MIN;
        u2_t_offset = u2_gp_OXCAN_E2E_REC_BY_PDU[u2_t_offset];
        if(u2_t_offset < (U2)OXCAN_E2E_NUM_REC){

            u2_t_length              = PduInfoPtr->SduLength;
            st_t_cfg.Offset          = (U2)OXCAN_E2E_OFFSET;
            st_t_cfg.DataLength      = u2_t_length << 3U;
            st_t_cfg.DataID          = (U2)Com_GetFrameID(PduId);
            st_t_cfg.MaxDeltaCounter = (U1)OXCAN_E2E_MAXDELTACNT;

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
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.3.0    12/20/2024  TN       oxcan_aubif.c was divided by Aubist/Com component.                                                 */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
