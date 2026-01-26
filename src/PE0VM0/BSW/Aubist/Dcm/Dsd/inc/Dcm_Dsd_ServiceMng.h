/* Dcm_Dsd_ServiceMng_h(v5-1-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsd_ServiceMng/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DCM_DSD_SERVICEMNG_H
#define DCM_DSD_SERVICEMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct tagDcm_Dsd_DataIndicationType {
    uint8 u1ReqType;
    PduIdType u2PduId;
}Dcm_Dsd_DataIndicationType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC( void, DCM_CODE ) Dcm_Dsd_ServiceMng_Init
( void );
FUNC( void, DCM_CODE ) Dcm_Dsd_DataIndicationFunctionality
(
    P2CONST( Dcm_Dsd_DataIndicationType, AUTOMATIC, DCM_APPL_DATA ) ptDataIndInfo,
    P2CONST( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxInfo,
    P2CONST( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptTxInfo
) ;
FUNC( void, DCM_CODE ) Dcm_Dsd_CancelService
( void );
FUNC_P2VAR( Dcm_MsgContextType, DCM_APPL_DATA, DCM_CODE ) Dcm_Dsd_ServiceMng_GetMsgCntxt
( void );
FUNC( void, DCM_CODE ) Dcm_Dsd_ServiceMng_SetSID
(
    const uint8 u1SID
);
FUNC( uint8, DCM_CODE ) Dcm_Dsd_GetSID
( void );
FUNC(uint8, DCM_CODE) Dcm_Dsd_GetDirectSID
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptRxBuff
);
FUNC( boolean, DCM_CODE ) Dcm_Dsd_ServiceMng_IsRunning
( void );
FUNC( void, DCM_CODE ) Dcm_Dsd_ServiceMng_ClrRunning
( void );
FUNC( uint8, DCM_CODE ) Dcm_Dsd_ServiceMng_GetOffsetLen
( void );
FUNC( void, DCM_CODE ) Dcm_Dsd_ServiceMng_ExecForceRP
( void );
FUNC( boolean, DCM_CODE ) Dcm_Dsd_isKeepAliveMsg
(
    const uint8 u1ReqType,
    P2CONST( AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA ) ptRxInfo
);
#if ( ( DCM_SUPPORT_SID28 == STD_ON ) || ( DCM_SUPPORT_SID85 == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) )
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_ChkServiceSupported
(
    const uint8 u1Sid,
    const PduIdType u2RxPduId,
    const Dcm_SesCtrlType u1SesCtrlType
);
#endif /* DCM_SUPPORT_SID28 == STD_ON || DCM_SUPPORT_SID85 == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON */
#if ( DCM_SID86_ROE_USE == STD_ON )
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_ChkRoeServiceSupported
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )  ptServToResp,
    const   uint32                              u4ServToRespToRecLen,
    const   PduIdType                           u2RxPduId
);
#endif /* DCM_SID86_ROE_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_DSD_SERVICEMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
