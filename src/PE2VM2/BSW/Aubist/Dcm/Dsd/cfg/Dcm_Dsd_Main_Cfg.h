/* Dcm_Dsd_Main_Cfg_h(v5-4-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsd_Main_Cfg/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DCM_DSD_MAIN_CFG_H
#define DCM_DSD_MAIN_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include <Dcm/Dcm_Main_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Multiplicity of DcmDsdServiceRequestManufacturerNotification(Xxx_Indication) */
#define DCM_D_MFRINDNOTIFY_NUM              (0U)

/* Multiplicity of DcmDsdServiceRequestManufacturerNotification(Xxx_Confirmation) */
#define DCM_D_MFRCONFNOTIFY_NUM             (0U)

/* Multiplicity of DcmDsdServiceRequestSupplierNotification(Xxx_Indication) */
#define DCM_D_SPLRINDNOTIFY_NUM             (0U)

/* Multiplicity of DcmDsdServiceRequestSupplierNotification(Xxx_Confirmation) */
#define DCM_D_SPLRCONFNOTIFY_NUM            (0U)

/* Multiplicity of ServiceTable */
#define DCM_D_SERVICETABLE_NUM              (8U)

/* NUM of all services  */
#define DCM_D_SERVICE_NUM                   (8U)

/* Supported OBD System */
#define DCM_DSD_OBDSYS_ON_UDS               ((uint8)0x01U)
#define DCM_DSD_OBDSYS_ON_EDS               ((uint8)0x02U)
#define DCM_DSD_OBDSYS_NONOBD               ((uint8)0x03U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Definition of Function Pointer Type  */
typedef P2FUNC(Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsd_IndicationFuncType )
(
    uint8 SID,
    P2VAR( uint8, TYPEDEF, DCM_APPL_DATA ) RequestData,
    uint32 DataSize,
    uint8 ReqType,
    uint16 ConnectionId,
    P2VAR( Dcm_NegativeResponseCodeType,TYPEDEF, DCM_APPL_DATA ) ErrorCode,
    Dcm_ProtocolType ProtocolType,
    uint16 TesterSourceAddress
);
typedef P2FUNC(Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsd_ConfirmationFuncType )
(
    uint8 SID,
    uint8 ReqType,
    uint16 ConnectionId,
    Dcm_ConfirmationStatusType ConfirmationStatus,
    Dcm_ProtocolType ProtocolType,
    uint16 TesterSourceAddress
);
typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_Dsd_ServiceFuncType )
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, TYPEDEF, DCM_APPL_DATA ) pMsgContext
);

/* Container Structure : DcmDsdSubService */
typedef struct tagDcm_Dsd_SubServiceType{
    Dcm_Dsd_ServiceFuncType ptFnc;
    P2CONST( AB_83_ConstV uint8, TYPEDEF, DCM_APPL_CONST ) ptSecurityLevelRef;
    P2CONST( AB_83_ConstV uint8, TYPEDEF, DCM_APPL_CONST ) ptSessionLevelRef;
    uint8 u1Id;
    uint8 u1SecurityLevelNum;
    uint8 u1SessionLevelNum;
}Dcm_Dsd_SubServiceType;


/* Container Structure : DcmDsdService */
typedef struct tagDcm_Dsd_ServiceType{
    Dcm_Dsd_ServiceFuncType ptFnc;
    P2CONST( AB_83_ConstV uint8, TYPEDEF, DCM_APPL_CONST ) ptSecurityLevelRef;
    P2CONST( AB_83_ConstV uint8, TYPEDEF, DCM_APPL_CONST ) ptSessionLevelRef;
    P2CONST( AB_83_ConstV Dcm_Dsd_SubServiceType, TYPEDEF, DCM_APPL_CONST ) ptSubService;
    uint8 u1Id;
    boolean bSubfuncAvail;
    uint8 u1SecurityLevelNum;
    uint8 u1SessionLevelNum;
    uint8 u1SubServiceNum;
}Dcm_Dsd_ServiceType;


/* Container Structure : DcmDsdServiceTable */
typedef struct tagDcm_Dsd_ServiceTableType{
    uint16 u2Id;
    uint8 u1ServiceNum;
    P2CONST( AB_83_ConstV uint16, TYPEDEF, DCM_APPL_CONST ) ptServiceIdx;
}Dcm_Dsd_ServiceTableType;



/* Container Structure : DcmDsd */
typedef struct tagDcm_DsdType{
    boolean bReqMfrNotifyEnabled;
    boolean bReqSplrNotifyEnabled;
    P2CONST(AB_83_ConstV Dcm_Dsd_IndicationFuncType, TYPEDEF, DCM_APPL_CONST) ptMfrIndNotify;
    P2CONST(AB_83_ConstV Dcm_Dsd_ConfirmationFuncType, TYPEDEF, DCM_APPL_CONST) ptMfrConfNotify;
    P2CONST(AB_83_ConstV Dcm_Dsd_IndicationFuncType, TYPEDEF, DCM_APPL_CONST) ptSplrIndNotify;
    P2CONST(AB_83_ConstV Dcm_Dsd_ConfirmationFuncType, TYPEDEF, DCM_APPL_CONST) ptSplrConfNotify;
    Dcm_Dsd_ServiceTableType stServiceTable[DCM_D_SERVICETABLE_NUM];
}Dcm_DsdType ;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

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
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>


/* extern */
extern CONST(AB_83_ConstV Dcm_DsdType, DCM_CONFIG_DATA) Dcm_Dsd_stConfigSet;

extern CONST(AB_83_ConstV Dcm_Dsd_ServiceType, DCM_CONFIG_DATA) Dcm_Dsd_stService[DCM_D_SERVICE_NUM];

extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Mfrindnotify_Num;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Mfrconfnotify_Num;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Splrindnotify_Num;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Splrconfnotify_Num;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1Servicetable_Num;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsd_u1SupportObdSystem;
extern CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_Dsd_bNoSuppressNegResIMLOIFToOBDClient;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_DSD_MAIN_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
