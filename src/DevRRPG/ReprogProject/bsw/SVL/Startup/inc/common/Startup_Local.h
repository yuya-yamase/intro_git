/* Startup_Local_h_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Startup/Local/HEADER                                        */
/******************************************************************************/
#ifndef STARTUP_LOCAL_H
#define STARTUP_LOCAL_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Gpt.h>
#include <Wdg.h>
#include <Mcu.h>
#include <WdgM.h>

#include "Startup_Ucfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Address judge result */
#define STARTUP_ADDR_AP     ((uint8)0x00U)
#define STARTUP_ADDR_NOT_AP ((uint8)0x01U)

#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
/* StayInBoot entry */
#define STARTUP_STAYINBOOT_ENTRY        ((uint8)0x00U)
#define STARTUP_STAYINBOOT_NOT_ENTRY    ((uint8)0x01U)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32  ApCheckSpAddress;
    uint32  ApCheckSpSize;
} Startup_ApCheckSpConfigType;

typedef struct {
    uint32  ApCheckAddress;
    uint32  ApCheckSize;
    uint32  ApCheckValue;
} Startup_ApCheckInfoConfigType;

typedef struct {
    uint32  ApCheckNum;
    P2CONST(Startup_ApCheckInfoConfigType, TYPEDEF, STARTUP_APPL_CONST) ApCheckInfoPtr;
} Startup_ApCheckConfigType;

typedef struct {
    uint32  ApAreaAddress;
    uint32  ApAreaSize;
} Startup_ApAreaInfoConfigType;

typedef struct {
    uint32  ApAreaNum;
    P2CONST(Startup_ApAreaInfoConfigType, TYPEDEF, STARTUP_APPL_CONST) ApAreaInfoPtr;
} Startup_ApAreaConfigType;

typedef struct {
    P2CONST(Gpt_ConfigType, TYPEDEF, STARTUP_APPL_CONST) GptConfigTypePtr;
    P2CONST(Wdg_ConfigType, TYPEDEF, STARTUP_APPL_CONST) WdgConfigTypePtr;
    P2CONST(Mcu_ConfigType, TYPEDEF, STARTUP_APPL_CONST) McuConfigTypePtr;
    P2CONST(WdgM_ConfigType, TYPEDEF, STARTUP_APPL_CONST) WdgMConfigTypePtr;
} Startup_InitCfgConfigType;

typedef struct {
    P2CONST(Startup_ApCheckSpConfigType, TYPEDEF, STARTUP_APPL_CONST) ApCheckSpDataPtr;
    P2CONST(Startup_ApCheckConfigType, TYPEDEF, STARTUP_APPL_CONST) ApCheckDataPtr;
    P2CONST(Startup_ApAreaConfigType, TYPEDEF, STARTUP_APPL_CONST) ApAreaDataPtr;
    P2CONST(Startup_InitCfgConfigType, TYPEDEF, STARTUP_APPL_CONST) InitCfgDataPtr;
    uint32  ApJumpAddress;
    uint32  PllLockCheckMaxNum;
    uint32  ClearRamBlockSize;
} Startup_ConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
/* Startup.c */
FUNC(Std_ReturnType, STARTUP_CODE_FAST) Startup_JudgeApCheckData (void);
FUNC(uint32, STARTUP_CODE_FAST) Startup_GetApAddress (void);
FUNC(uint8, STARTUP_CODE_FAST) Startup_JudgeAddressApCheck
(
    VAR(uint32, AUTOMATIC) Address
);
FUNC(uint8, STARTUP_CODE_FAST) Startup_JudgeAddressApArea
(
    VAR(uint32, AUTOMATIC) Address
);
FUNC(void, STARTUP_CODE_FAST) Startup_CopyRomToRam1st (void);
FUNC(void, STARTUP_CODE_FAST) Startup_CopyRomToRam2nd (void);
FUNC(void, STARTUP_CODE_FAST) Startup_WdgTrigger (void);
/* Called from Startup.c */
FUNC(void, STARTUP_CODE_FAST) Startup_MemBarrier32
(
    P2CONST(uint32, AUTOMATIC, STARTUP_APPL_CONST) ReadAddress
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define STARTUP_START_SEC_CST
#include <Startup_MemMap.h>

extern CONST(Startup_ApCheckInfoConfigType, STARTUP_CONFIG_DATA) Startup_Ucfg_ApCheckInfo[STARTUP_UCFG_APCHECK_NUM];
extern CONST(Startup_ApAreaInfoConfigType, STARTUP_CONFIG_DATA) Startup_Ucfg_ApAreaInfo[STARTUP_UCFG_APAREA_NUM];
extern CONST(Startup_ConfigType, STARTUP_CONFIG_DATA) Startup_Cfg_Data;

#define STARTUP_STOP_SEC_CST
#include <Startup_MemMap.h>


#endif /* STARTUP_LOCAL_H */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

