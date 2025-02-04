/* Startup_Micon_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Startup/Micon/HEADER                                        */
/******************************************************************************/
#ifndef STARTUP_MICON_H
#define STARTUP_MICON_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* ECC(ROM) error state */
#define STARTUP_ECC_ROM_OK              ((uint8)0x00U)
#define STARTUP_ECC_ROM_NG_AP           ((uint8)0x01U)
#define STARTUP_ECC_ROM_NG_NOT_AP       ((uint8)0x02U)

/* ECC(RAM) error state */
#define STARTUP_ECC_RAM_OK              ((uint8)0x00U)
#define STARTUP_ECC_RAM_NG              ((uint8)0x01U)

/* Vector Kind */
#define STARTUP_VECT_ROM                ((uint8)0x01U)
#define STARTUP_VECT_RAM                ((uint8)0x02U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/* Module standby setting info */
typedef struct {
    uint32 RegAddr;
    uint32 RegVal;
} Startup_StandbyConfigInfoType;

typedef struct {
    uint32 StandbyNum;
    P2CONST(Startup_StandbyConfigInfoType, TYPEDEF, STARTUP_APPL_CONST) StandbyInfoPtr;
} Startup_StandbyConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
/* Startup_Micon.c */
FUNC(uint8, STARTUP_CODE_FAST) Startup_JudgeApStart (void);
FUNC(uint8, STARTUP_CODE_FAST) Startup_CheckRomErrorAddress
(
    VAR(uint32, AUTOMATIC) Address
);
FUNC(void, STARTUP_CODE_FAST) Startup_PreGearUp (void);
FUNC(void, STARTUP_CODE_FAST) Startup_SetGearUp (void);
FUNC(void, STARTUP_CODE_FAST) Startup_ReprogStart
(
    VAR(uint8, AUTOMATIC) BootKind
);
/* Startup_MiconHw.c */
FUNC(uint8, STARTUP_CODE_FAST) Startup_CheckPoweronReset (void);
FUNC(void, STARTUP_CODE_FAST) Startup_ClearResetFactor (void);
FUNC(void, STARTUP_CODE_FAST) Startup_EccRomInit (void);
FUNC(void, STARTUP_CODE_FAST) Startup_EccRomDeInit
(
    VAR(uint8, AUTOMATIC) ResetErrInt
);
FUNC(void, STARTUP_CODE_FAST) Startup_EccRamInit (void);
FUNC(void, STARTUP_CODE_FAST) Startup_EccRamDeInit
(
    VAR(uint8, AUTOMATIC) ResetErrInt
);
FUNC(void, STARTUP_CODE_FAST) Startup_ClearEccRomErrorStatus (void);
FUNC(uint8, STARTUP_CODE_FAST) Startup_GetEccRomErrorStatus (void);
FUNC(uint8, STARTUP_CODE_FAST) Startup_GetEccRamErrorStatus (void);
FUNC(void, STARTUP_CODE_FAST) Startup_SetVector
(
    VAR(uint8, AUTOMATIC) VectKind
);
FUNC(Std_ReturnType, STARTUP_CODE_FAST) Startup_StandbyInit (void);
FUNC(void, STARTUP_CODE_FAST) Startup_InitHw (void);
/* Startup_Core.850 */
FUNC(void, STARTUP_CODE_FAST) Startup_InitHwCore (void);
FUNC(void, STARTUP_CODE_FAST) Startup_JumpApCore
(
    VAR(uint32, AUTOMATIC) Address
);
FUNC(void, STARTUP_CODE_FAST) Startup_SyncBarrier (void);
/* Startup_MemBarrier32() is defined by Startup_Local.h */


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define STARTUP_START_SEC_CST
#include <Startup_MemMap.h>

extern CONST(Startup_StandbyConfigInfoType, STARTUP_CONFIG_DATA) Startup_Ucfg_StandbyInfo[STARTUP_UCFG_STANDBY_SETTING_NUM];
extern CONST(Startup_StandbyConfigType, STARTUP_CONFIG_DATA) Startup_Cfg_StandbyData;
extern CONST(uint8, STARTUP_CONFIG_DATA) Startup_Cfg_MiconName;

#define STARTUP_STOP_SEC_CST
#include <Startup_MemMap.h>

#endif /* STARTUP_MICON_H */


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

