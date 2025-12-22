/* Dcm_Dsd_MsgChk_h(v5-0-0)                                                 */
/****************************************************************************/
/* Protected */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | DCM/Dsd_MsgChk/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSD_MSGCHK_H
#define DCM_DSD_MSGCHK_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include "../../Dsd/inc/Dcm_Dsd_Main.h"

/*--------------------------------------------------------------------------*/
/* Macros */
/*--------------------------------------------------------------------------*/
#define DCM_DSD_REQVFY_SF_BIT           ((uint8)0x10U)
#define DCM_DSD_REQVFY_CHKSERVICE       ((uint8)0x00U)
#define DCM_DSD_REQVFY_CHKSUBFUNCTION   ((uint8)0x01U)
#define DCM_DSD_REQVFY_CHKMANUFACTURER  ((uint8)0x00U)
#define DCM_DSD_REQVFY_CHKSUPPLIER      ((uint8)0x02U)

/*--------------------------------------------------------------------------*/
/* Types */
/*--------------------------------------------------------------------------*/
typedef struct{
    P2CONST(AB_83_ConstV Dcm_Dsd_ServiceTableType, AUTOMATIC, DCM_APPL_CONST) ptServiceTable;
    P2CONST(AB_83_ConstV Dcm_Dsd_ServiceType, AUTOMATIC, DCM_APPL_CONST) ptService;
}Dcm_Dsd_ServiceCheckType;

typedef struct{
    P2CONST(AB_83_ConstV Dcm_Dsd_ServiceType, AUTOMATIC, DCM_APPL_CONST) ptService;
    P2CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, AUTOMATIC, DCM_APPL_CONST) ptSubService;
}Dcm_Dsd_SubServiceCheckType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkSID
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    P2VAR(Dcm_Dsd_ServiceCheckType, AUTOMATIC, DCM_APPL_DATA) ptServiceInfo,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) ptsubfunc,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkSubfunction
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    P2VAR(Dcm_Dsd_SubServiceCheckType, AUTOMATIC, DCM_APPL_DATA) ptSubServiceInfo,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ReqVerify
(
    const uint8 u1SID,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1ExecMode,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);

#if( DCM_SID86_ROE_USE == STD_ON )
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkRoeSrvSupSid
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )                      ptServToResp,
    const   uint32                                                  u4ServToRespToRecLen,
    P2VAR(Dcm_Dsd_ServiceCheckType, AUTOMATIC, DCM_APPL_DATA)       ptServiceInfo,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)                        ptSubfunc
);
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkRoeSrvSupSubFunc
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )                      ptServToResp,
    const   uint32                                                  u4ServToRespToRecLen,
    P2VAR(Dcm_Dsd_SubServiceCheckType, AUTOMATIC, DCM_APPL_DATA)    ptSubServiceInfo
);
#endif /* DCM_SID86_ROE_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_DSD_MSGCHK_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2021-12-24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
