/* RpgLib_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RpgLib/HEADER                                               */
/******************************************************************************/
#ifndef RPGLIB_H
#define RPGLIB_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComStack_Types.h>

#include <Rte.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define RPGLIB_IDLE                 ((uint8)0x00U)
#define RPGLIB_BUSY                 ((uint8)0x01U)
#define RPGLIB_UPDATEIDLE           ((uint8)0x02U)
#define RPGLIB_UPDATEBUSY           ((uint8)0x03U)
#define RPGLIB_UPDATECOMPLETE       ((uint8)0x04U)

#define RPGLIB_JOB_OK               ((uint8)0x00U)
#define RPGLIB_JOB_FAILED           ((uint8)0x01U)
#define RPGLIB_JOB_PENDING          ((uint8)0x02U)
#define RPGLIB_JOB_MEMERR           ((uint8)0x03U)

#define RPGLIB_CHANGEBAUDRATE_OK    ((uint8)0x00U)
#define RPGLIB_CHANGEBAUDRATE_NG    ((uint8)0x01U)

#define RPGLIB_FLSCTRL_NOTREADY     (RTE_SCHM_BSWM_FLS_PRG_NOTREADY)
#define RPGLIB_FLSCTRL_READY        (RTE_SCHM_BSWM_FLS_PRG_READY)

#define RPGLIB_MEMORYID_0           ((uint32)0UL)
#define RPGLIB_MEMORYID_1           ((uint32)1UL)

#define RPGLIB_DEVICE_TYPE_CODEFLS       (RTE_MEMM_DEVICE_TYPE_CODEFLS)
#define RPGLIB_DEVICE_TYPE_EXTCODEFLS    (RTE_MEMM_DEVICE_TYPE_EXTCODEFLS)
#define RPGLIB_DEVICE_TYPE_CODERAM       (RTE_MEMM_DEVICE_TYPE_CODERAM)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32 BlockTopAddr;
    uint32 BlockSize;
} RpgLib_MemBlockInfoType;

#if 0   /* Nbr1503(ChangeBaudrate) */
typedef struct {
    uint16 BaudrateConfigId;
    NetworkHandleType NetworkId;
} RpgLib_CheckBaudrateResultType;

typedef Rte_CanSM_BaudrateInfoType RpgLib_BaudrateInfoType;
#endif
#if 0   /* Nbr1503(CtrlFrame) */
typedef P2FUNC(void, RPGLIB_CALLOUT_CODE, RpgLib_CtrlFrameTxCallbackType)
(
    VAR(PduIdType, AUTOMATIC) PduId
);

typedef P2FUNC(void, RPGLIB_CALLOUT_CODE, RpgLib_CtrlFrameRxCallbackType)
(
    VAR(PduIdType, AUTOMATIC) PduId,
    P2CONST(PduInfoType, AUTOMATIC, RPGLIB_APPL_CONST) PduInfo
);
#endif


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_Init (void);
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_DeInit (void);
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_Time (void);
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_MainFunction (void);
FUNC(uint8, RPGLIB_CODE_SLOW) RpgLib_GetStatus (void);
FUNC(uint8, RPGLIB_CODE_SLOW) RpgLib_GetJobResult (void);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqInvalidApl
(
    VAR(uint32, AUTOMATIC) MemoryId
);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqValidApl (void);
#if 0   /* Nbr1503(ChangeBaudrate) */
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_CheckChangeBaudrate
(
    VAR(PduIdType, AUTOMATIC) PduId,
    P2CONST(RpgLib_BaudrateInfoType, AUTOMATIC, RPGLIB_APPL_CONST) BaudrateInfo,
    P2VAR(RpgLib_CheckBaudrateResultType, AUTOMATIC, RPGLIB_APPL_DATA) CheckBaudrateResult
);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqChangeBaudrate
(
    P2CONST(RpgLib_CheckBaudrateResultType, AUTOMATIC, RPGLIB_APPL_CONST) CheckBaudrateResult
);
#endif
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_NotifyChangeBaudrate
(
    VAR(uint8, AUTOMATIC) ChangeResult
);
#if 0   /* Nbr1503(CtrlFrame) */
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_CtrlFrameRegistTxConfCallback
(
    VAR(PduIdType, AUTOMATIC) PduId,
    VAR(RpgLib_CtrlFrameTxCallbackType, AUTOMATIC) Callback
);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_CtrlFrameRegistRxIndCallback
(
    VAR(PduIdType, AUTOMATIC) PduId,
    VAR(RpgLib_CtrlFrameRxCallbackType, AUTOMATIC) Callback
);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_CtrlFrameTransmit
(
    VAR(PduIdType, AUTOMATIC) PduId,
    P2CONST(PduInfoType, AUTOMATIC, RPGLIB_APPL_CONST) PduInfo
);
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_CtrlFrameTxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId
);
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_CtrlFrameRxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, RPGLIB_APPL_CONST) PduInfo
);
#endif
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_GetMemBlockInfo
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) TargetAddr,
    P2VAR(RpgLib_MemBlockInfoType, AUTOMATIC, RPGLIB_APPL_DATA) BlockInfo
);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqMemBlockErase
(
    VAR(uint32, AUTOMATIC) MemoryId,
    P2CONST(RpgLib_MemBlockInfoType, AUTOMATIC, RPGLIB_APPL_CONST) BlockInfo
);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_WriteMemStart
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) WriteTopAddr,
    VAR(uint32, AUTOMATIC) WriteTotalSize
);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqWriteMemUpdate
(
    P2CONST(uint8, AUTOMATIC, RPGLIB_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_WriteMemFinish (void);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqMemRead
(
    VAR(uint32, AUTOMATIC) MemoryId,
    P2VAR(uint8, AUTOMATIC, RPGLIB_APPL_DATA) DestAddr,
    VAR(uint32, AUTOMATIC) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_NotifyFlsCtrlMode
(
    VAR(uint16, AUTOMATIC) Mode
);
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_CnvPhysicalAddr
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) VirtualAddr,
    P2VAR(uint32, AUTOMATIC, RPGLIB_APPL_DATA) PhysicalAddr,
    P2VAR(uint8, AUTOMATIC, RPGLIB_APPL_DATA) DeviceType
);
FUNC(uint32, RPGLIB_CODE_SLOW) RpgLib_GetNextWriteAddr (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define RPGLIB_START_SEC_VAR
#include <RpgLib_MemMap.h>

#define RPGLIB_STOP_SEC_VAR
#include <RpgLib_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RPGLIB_START_SEC_CST
#include <RpgLib_MemMap.h>

#define RPGLIB_STOP_SEC_CST
#include <RpgLib_MemMap.h>


#endif /* RPGLIB_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/03/01 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

