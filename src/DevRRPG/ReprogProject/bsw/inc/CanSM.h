/* CanSM_h_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanSM/HEADER                                                */
/******************************************************************************/
#ifndef CANSM_H
#define CANSM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComStack_Types.h>
#include <ComM.h>
#include <Gdn.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CANSM_MAXNETWORK_NUM ((uint8)16U)
#define CANSM_LINKRECORD_NUM ((uint8)3U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32 CanId;
    Gdn_PduIdType PduId;
    uint8  Controller;
} CanSM_PduIdSettingConfigType;

typedef struct {
    P2CONST(CanSM_PduIdSettingConfigType, TYPEDEF, CANSM_APPL_CONST) PduIdSettingTbl;
    uint8 PduIdNum;
} CanSM_PduIdConfigType;

typedef struct {
    uint8 ControllerId;
} CanSM_ControllerSettingConfigType;

typedef struct {
    P2CONST(CanSM_ControllerSettingConfigType, TYPEDEF, CANSM_APPL_CONST) ControllerSettingTbl;
    uint8 ControllerNum;
    NetworkHandleType NetworkId;
} CanSM_NetworkSettingConfigType;

typedef struct {
    uint16 ModeRequestRepetitionTime;
    uint8  ModeRequestRepetitionMax;
    uint8  NetworkNum;
    P2CONST(CanSM_NetworkSettingConfigType, TYPEDEF, CANSM_APPL_CONST) NetworkSettingTbl;
} CanSM_NetworkConfigType;

typedef struct {
    uint16 Baudrate;
} CanSM_BaudrateSettingConfigType;

typedef struct {
    P2CONST(CanSM_BaudrateSettingConfigType, TYPEDEF, CANSM_APPL_CONST) BaudrateSettingTbl;
    uint8 BaudrateNum;
} CanSM_BaudrateConfigType;

typedef struct {
    P2CONST(CanSM_NetworkConfigType, TYPEDEF, CANSM_APPL_CONST) NetworkInfoTbl;
    P2CONST(CanSM_PduIdConfigType, TYPEDEF, CANSM_APPL_CONST) PduIdInfoTbl;
    P2CONST(CanSM_BaudrateConfigType, TYPEDEF, CANSM_APPL_CONST) BaudrateInfoTbl;
} CanSM_ConfigType;

typedef struct {
    uint8 linkControlType;
    uint8 linkControlModeIdentifier;
    uint8 linkRecord[CANSM_LINKRECORD_NUM];
}CanSM_BaudrateInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, CANSM_CODE_SLOW) CanSM_Init
(
    P2CONST(CanSM_ConfigType, AUTOMATIC, CANSM_APPL_CONST) ConfigPtr
);

FUNC(void, CANSM_CODE_SLOW) CanSM_MainFunction (void);

#if 0   /* Nbr1503(ChangeBaudrate) */
FUNC(Std_ReturnType, CANSM_CODE_SLOW) CanSM_SetBaudrate
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    VAR(uint16, AUTOMATIC) BaudRateConfigID
);

FUNC(Std_ReturnType, CANSM_CODE_SLOW) CanSM_CheckBaudrate
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    VAR(uint16, AUTOMATIC) BaudRateConfigID
);

FUNC(Std_ReturnType, CANSM_CODE_SLOW) CanSM_GetNetworkId
(
    VAR(PduIdType, AUTOMATIC) PduId,
    P2VAR(NetworkHandleType, AUTOMATIC, CANSM_APPL_DATA) NetworkId
);
#endif

FUNC(Std_ReturnType, CANSM_CODE_SLOW) CanSM_GetBaudrateConfigId
(
    P2CONST(CanSM_BaudrateInfoType, TYPEDEF, CANSM_APPL_CONST) BaudrateInfo,
    P2VAR(uint16, AUTOMATIC, CANSM_APPL_DATA) BaudRateConfigID
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CANSM_START_SEC_CST
#include <CanSM_MemMap.h>

extern CONST(CanSM_ConfigType, CANSM_CONFIG_DATA) CanSM_Cfg_Data;

#define CANSM_STOP_SEC_CST
#include <CanSM_MemMap.h>


#endif /* CANSM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v3.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

