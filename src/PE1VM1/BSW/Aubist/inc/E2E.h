/* E2E_h_v2-1-0                                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name      | E2E/E2E/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes            |                                                       */
/****************************************************************************/

#ifndef E2E_H
#define E2E_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Crc.h>
#include <Std_Types.h>

/* [lib_SC1-1_e2e_1000] */
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* SWS_E2E_00038 */
#define E2E_VENDOR_ID                   (0x0053U)
#define E2E_MODULE_ID                   (207U)
#define E2E_SW_MAJOR_VERSION            (2U)
#define E2E_SW_MINOR_VERSION            (1U)
#define E2E_SW_PATCH_VERSION            (0U)

/* SWS_E2E_00347, PRS_E2E_00597 */
#define E2E_P_OK                        (E2E_PCheckStatusType)(0x00U)
#define E2E_P_REPEATED                  (E2E_PCheckStatusType)(0x01U)
#define E2E_P_WRONGSEQUENCE             (E2E_PCheckStatusType)(0x02U)
#define E2E_P_ERROR                     (E2E_PCheckStatusType)(0x03U)
#define E2E_P_NOTAVAILABLE              (E2E_PCheckStatusType)(0x04U)
#define E2E_P_NONEWDATA                 (E2E_PCheckStatusType)(0x05U)

/* SWS_E2E_00047 */
#define E2E_E_OK                        (Std_ReturnType)(0x00U)
#define E2E_E_INPUTERR_NULL             (Std_ReturnType)(0x13U)
#define E2E_E_INPUTERR_WRONG            (Std_ReturnType)(0x17U)
#define E2E_E_INTERR                    (Std_ReturnType)(0x19U)
#define E2E_E_WRONGSTATE                (Std_ReturnType)(0x1AU)

/* SWS_E2E_00200 */
#define E2E_P01_DATAID_BOTH             (E2E_P01DataIDMode)(0x00U)
#define E2E_P01_DATAID_ALT              (E2E_P01DataIDMode)(0x01U)
#define E2E_P01_DATAID_LOW              (E2E_P01DataIDMode)(0x02U)
#define E2E_P01_DATAID_NIBBLE           (E2E_P01DataIDMode)(0x03U)

/* SWS_E2E_00022, PRS_E2E_00588 */
#define E2E_P01STATUS_OK                (E2E_P01CheckStatusType)(0x00U)
#define E2E_P01STATUS_NONEWDATA         (E2E_P01CheckStatusType)(0x01U)
#define E2E_P01STATUS_WRONGCRC          (E2E_P01CheckStatusType)(0x02U)
#define E2E_P01STATUS_SYNC              (E2E_P01CheckStatusType)(0x03U)
#define E2E_P01STATUS_INITIAL           (E2E_P01CheckStatusType)(0x04U)
#define E2E_P01STATUS_REPEATED          (E2E_P01CheckStatusType)(0x08U)
#define E2E_P01STATUS_OKSOMELOST        (E2E_P01CheckStatusType)(0x20U)
#define E2E_P01STATUS_WRONGSEQUENCE     (E2E_P01CheckStatusType)(0x40U)

/* SWS_E2E_00337, PRS_E2E_00590 */
#define E2E_P04STATUS_OK                (E2E_P04CheckStatusType)(0x00U)
#define E2E_P04STATUS_NONEWDATA         (E2E_P04CheckStatusType)(0x01U)
#define E2E_P04STATUS_ERROR             (E2E_P04CheckStatusType)(0x07U)
#define E2E_P04STATUS_REPEATED          (E2E_P04CheckStatusType)(0x08U)
#define E2E_P04STATUS_OKSOMELOST        (E2E_P04CheckStatusType)(0x20U)
#define E2E_P04STATUS_WRONGSEQUENCE     (E2E_P04CheckStatusType)(0x40U)

/* SWS_E2E_00440, PRS_E2E_00591 */
#define E2E_P05STATUS_OK                (E2E_P05CheckStatusType)(0x00U)
#define E2E_P05STATUS_NONEWDATA         (E2E_P05CheckStatusType)(0x01U)
#define E2E_P05STATUS_ERROR             (E2E_P05CheckStatusType)(0x07U)
#define E2E_P05STATUS_REPEATED          (E2E_P05CheckStatusType)(0x08U)
#define E2E_P05STATUS_OKSOMELOST        (E2E_P05CheckStatusType)(0x20U)
#define E2E_P05STATUS_WRONGSEQUENCE     (E2E_P05CheckStatusType)(0x40U)

/* SWS_E2E_00445, PRS_E2E_00592 */
#define E2E_P06STATUS_OK                (E2E_P06CheckStatusType)(0x00U)
#define E2E_P06STATUS_NONEWDATA         (E2E_P06CheckStatusType)(0x01U)
#define E2E_P06STATUS_ERROR             (E2E_P06CheckStatusType)(0x07U)
#define E2E_P06STATUS_REPEATED          (E2E_P06CheckStatusType)(0x08U)
#define E2E_P06STATUS_OKSOMELOST        (E2E_P06CheckStatusType)(0x20U)
#define E2E_P06STATUS_WRONGSEQUENCE     (E2E_P06CheckStatusType)(0x40U)

/* SWS_E2E_00542, PRS_E2E_00593 */
#define E2E_P07STATUS_OK                (E2E_P07CheckStatusType)(0x00U)
#define E2E_P07STATUS_NONEWDATA         (E2E_P07CheckStatusType)(0x01U)
#define E2E_P07STATUS_ERROR             (E2E_P07CheckStatusType)(0x07U)
#define E2E_P07STATUS_REPEATED          (E2E_P07CheckStatusType)(0x08U)
#define E2E_P07STATUS_OKSOMELOST        (E2E_P07CheckStatusType)(0x20U)
#define E2E_P07STATUS_WRONGSEQUENCE     (E2E_P07CheckStatusType)(0x40U)

/* SWS_E2E_00344, PRS_E2E_00596 */
#define E2E_SM_VALID                    (E2E_SMStateType)(0x00U)
#define E2E_SM_DEINIT                   (E2E_SMStateType)(0x01U)
#define E2E_SM_NODATA                   (E2E_SMStateType)(0x02U)
#define E2E_SM_INIT                     (E2E_SMStateType)(0x03U)
#define E2E_SM_INVALID                  (E2E_SMStateType)(0x04U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* SWS_E2E_00347 */
typedef uint8 E2E_PCheckStatusType;

/* SWS_E2E_00200 */
typedef uint8 E2E_P01DataIDMode;

/* SWS_E2E_00018, PRS_E2E_00227, PRS_E2E_00228, PRS_E2E_00307 */
typedef struct {
    uint16                    CounterOffset;
    uint16                    CRCOffset;
    uint16                    DataID;
    uint16                    DataIDNibbleOffset;
    E2E_P01DataIDMode         DataIDMode;
    uint16                    DataLength;
    uint8                     MaxDeltaCounterInit;
    uint8                     MaxNoNewOrRepeatedData;
    uint8                     SyncCounterInit;
} E2E_P01ConfigType;

/* SWS_E2E_00020 */
typedef struct {
    uint8 Counter;
} E2E_P01ProtectStateType;

/* SWS_E2E_00022 */
typedef uint8 E2E_P01CheckStatusType;

/* SWS_E2E_00021 */
typedef struct {
    uint8                     LastValidCounter;
    uint8                     MaxDeltaCounter;
    boolean                   WaitForFirstData;
    boolean                   NewDataAvailable;
    uint8                     LostData;
    E2E_P01CheckStatusType    Status;
    uint8                     SyncCounter;
    uint8                     NoNewOrRepeatedDataCounter;
} E2E_P01CheckStateType;

typedef E2E_P01ProtectStateType E2E_P01SenderStateType;
typedef E2E_P01CheckStateType E2E_P01ReceiverStateType;
typedef E2E_P01CheckStatusType E2E_P01ReceiverStatusType;

/* SWS_E2E_00334, PRS_E2E_00584, PRS_E2E_00585 */
typedef struct {
    uint32                  DataID;
    uint16                  Offset;
    uint16                  MinDataLength;
    uint16                  MaxDataLength;
    uint16                  MaxDeltaCounter;
} E2E_P04ConfigType;

/* SWS_E2E_00335 */
typedef struct { 
    uint16 Counter; /* wrap around */
} E2E_P04ProtectStateType;

/* SWS_E2E_00337 */
typedef uint8 E2E_P04CheckStatusType;

/* SWS_E2E_00336 */
typedef struct {
    E2E_P04CheckStatusType  Status;
    uint16                  Counter;
} E2E_P04CheckStateType;

/* SWS_E2E_00437 */
typedef struct {
    uint16  Offset;
    uint16  DataLength;
    uint16  DataID;
    uint8   MaxDeltaCounter;
} E2E_P05ConfigType;

/* SWS_E2E_00438 */
typedef struct { 
    uint8 Counter; /* wrap around */
} E2E_P05ProtectStateType;

/* SWS_E2E_00440 */
typedef uint8 E2E_P05CheckStatusType;

/* SWS_E2E_00439 */
typedef struct {
    E2E_P05CheckStatusType  Status;
    uint8                   Counter;
} E2E_P05CheckStateType;

/* SWS_E2E_00441 */
typedef struct {
    uint16  Offset;
    uint16  MinDataLength;
    uint16  MaxDataLength;
    uint16  DataID;
    uint8   MaxDeltaCounter;
} E2E_P06ConfigType;

/* SWS_E2E_00443 */
typedef struct { 
    uint8 Counter; /* wrap around */
} E2E_P06ProtectStateType;

/* SWS_E2E_00445 */
typedef uint8 E2E_P06CheckStatusType;

/* SWS_E2E_00444 */
typedef struct {
    E2E_P06CheckStatusType  Status;
    uint8                   Counter;
} E2E_P06CheckStateType;

/* SWS_E2E_00544, PRS_E2E_00483, PRS_E2E_00586, PRS_E2E_00587 */
typedef struct {
    uint32  DataID;
    uint32  Offset;
    uint32  MinDataLength;
    uint32  MaxDataLength;
    uint32  MaxDeltaCounter;
} E2E_P07ConfigType;

/* SWS_E2E_00545 */
typedef struct { 
    uint32 Counter; /* wrap around */
} E2E_P07ProtectStateType;

/* SWS_E2E_00591 */
typedef uint8 E2E_P07CheckStatusType;

/* SWS_E2E_00542 */
typedef struct {
    E2E_P07CheckStatusType  Status;
    uint32                  Counter;
} E2E_P07CheckStateType;

/* SWS_E2E_00344 */
typedef uint8 E2E_SMStateType;

/* SWS_E2E_00342 */
typedef struct {
    uint8   WindowSizeValid;
    uint8   MinOkStateInit;
    uint8   MaxErrorStateInit;
    uint8   MinOkStateValid;
    uint8   MaxErrorStateValid;
    uint8   MinOkStateInvalid;
    uint8   MaxErrorStateInvalid;
    uint8   WindowSizeInit;
    uint8   WindowSizeInvalid;
    boolean ClearToInvalid;
} E2E_SMConfigType;

/* SWS_E2E_00343 */
typedef struct {
    uint8*  ProfileStatusWindow;
    uint8   WindowTopIndex;
    uint8   OkCount;
    uint8   ErrorCount;
    E2E_SMStateType SMState;
} E2E_SMCheckStateType;
/* Implements [lib_SDD1-1_e2e_0101] */

#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* [lib_SC1-1_e2e_0133] */
FUNC(void, E2E_CODE) E2E_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfo );                                                                                                    /* SWS_E2E_00032 */
/* Implements [lib_SDD1-1_e2e_0033] */

/* [lib_SC1-1_e2e_1100] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P01Protect( P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P01ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr );                /* SWS_E2E_00166 */
/* Implements [lib_SDD1-1_e2e_0112] */
/* [lib_SC1-1_e2e_1101] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P01ProtectInit( P2VAR(E2E_P01ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );                                                                                                                            /* SWS_E2E_00385 */
/* Implements [lib_SDD1-1_e2e_0113] */
/* [lib_SC1-1_e2e_1102] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P01Check( P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr );                  /* SWS_E2E_00158 */
/* Implements [lib_SDD1-1_e2e_0114] */
/* [lib_SC1-1_e2e_1103] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P01CheckInit( P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );                                                                                                                                /* SWS_E2E_00390 */
/* Implements [lib_SDD1-1_e2e_0115] */
/* [lib_SC1-1_e2e_1104] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P01MapStatusToSM( Std_ReturnType CheckReturn, E2E_P01CheckStatusType Status, boolean profileBehavior );                                                                                                   /* SWS_E2E_00382 */
/* Implements [lib_SDD1-1_e2e_0116] */

/* [lib_SC1-1_e2e_0111] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04Protect( P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length ); /* SWS_E2E_00338 */
/* Implements [lib_SDD1-1_e2e_0011] */
/* [lib_SC1-1_e2e_0112] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04ProtectInit( P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );                                                                                                                            /* SWS_E2E_00373 */
/* Implements [lib_SDD1-1_e2e_0012] */
/* [lib_SC1-1_e2e_0113] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04Check( P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length );   /* SWS_E2E_00339 */
/* Implements [lib_SDD1-1_e2e_0013] */
/* [lib_SC1-1_e2e_0114] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04CheckInit( P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );                                                                                                                                /* SWS_E2E_00350 */
/* Implements [lib_SDD1-1_e2e_0014] */
/* [lib_SC1-1_e2e_0115] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P04MapStatusToSM( Std_ReturnType CheckReturn, E2E_P04CheckStatusType Status );                                                                                                                            /* SWS_E2E_00349 */
/* Implements [lib_SDD1-1_e2e_0015] */

/* [lib_SC1-1_e2e_0116] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05Protect( P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P05ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length ); /* SWS_E2E_00446 */
/* Implements [lib_SDD1-1_e2e_0016] */
/* [lib_SC1-1_e2e_0117] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05ProtectInit( P2VAR(E2E_P05ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );                                                                                                                            /* SWS_E2E_00447 */
/* Implements [lib_SDD1-1_e2e_0017] */
/* [lib_SC1-1_e2e_0118] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05Check( P2CONST(E2E_P05ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length );   /* SWS_E2E_00449 */
/* Implements [lib_SDD1-1_e2e_0018] */
/* [lib_SC1-1_e2e_0119] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P05CheckInit( P2VAR(E2E_P05CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );                                                                                                                                /* SWS_E2E_00450 */
/* Implements [lib_SDD1-1_e2e_0019] */
/* [lib_SC1-1_e2e_0120] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P05MapStatusToSM( Std_ReturnType CheckReturn, E2E_P05CheckStatusType Status );                                                                                                                            /* SWS_E2E_00452 */
/* Implements [lib_SDD1-1_e2e_0020] */

/* [lib_SC1-1_e2e_1105] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06Protect( P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length ); /* SWS_E2E_00393 */
/* Implements [lib_SDD1-1_e2e_0117] */
/* [lib_SC1-1_e2e_1106] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06ProtectInit( P2VAR(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );                                                                                                                            /* SWS_E2E_00455 */
/* Implements [lib_SDD1-1_e2e_0118] */
/* [lib_SC1-1_e2e_1107] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06Check( P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length );   /* SWS_E2E_00457 */
/* Implements [lib_SDD1-1_e2e_0119] */
/* [lib_SC1-1_e2e_1108] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06CheckInit( P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );                                                                                                                                /* SWS_E2E_00458 */
/* Implements [lib_SDD1-1_e2e_0120] */
/* [lib_SC1-1_e2e_1109] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P06MapStatusToSM( Std_ReturnType CheckReturn, E2E_P06CheckStatusType Status );                                                                                                                            /* SWS_E2E_00460 */
/* Implements [lib_SDD1-1_e2e_0121] */

/* [lib_SC1-1_e2e_1001] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P07Protect( P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P07ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint32 Length ); /* SWS_E2E_00546 */
/* Implements [lib_SDD1-1_e2e_0102] */
/* [lib_SC1-1_e2e_1002] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P07ProtectInit( P2VAR(E2E_P07ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );                                                                                                                            /* SWS_E2E_00547 */
/* Implements [lib_SDD1-1_e2e_0103] */
/* [lib_SC1-1_e2e_1003] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P07Check( P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint32 Length );   /* SWS_E2E_00548 */
/* Implements [lib_SDD1-1_e2e_0104] */
/* [lib_SC1-1_e2e_1004] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P07CheckInit( P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );                                                                                                                                /* SWS_E2E_00549 */
/* Implements [lib_SDD1-1_e2e_0105] */
/* [lib_SC1-1_e2e_1005] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P07MapStatusToSM( Std_ReturnType CheckReturn, E2E_P07CheckStatusType Status );
                                           /* SWS_E2E_00550 */
/* Implements [lib_SDD1-1_e2e_0106] */

/* [lib_SC1-1_e2e_0126] */
FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheck( E2E_PCheckStatusType ProfileStatus, P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );  /* SWS_E2E_00340 */
/* Implements [lib_SDD1-1_e2e_0026] */
/* [lib_SC1-1_e2e_0127] */
FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheckInit( P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr );                                  /* SWS_E2E_00353 */
/* Implements [lib_SDD1-1_e2e_0027] */

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* E2E_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-1-0         :2022/09/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
