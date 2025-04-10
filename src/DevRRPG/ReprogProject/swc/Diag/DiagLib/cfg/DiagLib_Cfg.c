/* DiagLib_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagLib/Cfg/CODE                                            */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagLib.h>
#include "DiagLib_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGLIB_CFG_SECLEVEL_NUM    (sizeof(DiagLib_SecLevelInfo) / sizeof(DiagLib_SecLevelInfo[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGLIB_START_SEC_CST
#include <DiagLib_MemMap.h>

CONST(DiagLib_TransferConfigType, DIAGLIB_CONFIG_DATA) DiagLib_TransferConfig = {
    1026UL,
    0UL
};

static CONST(DiagLib_SecLevelInfoType, DIAGLIB_CONFIG_DATA) DiagLib_SecLevelInfo[] = {
     { 0x01U }
};

CONST(DiagLib_SecLevelConfigType, DIAGLIB_CONFIG_DATA) DiagLib_SecLevelConfig = {
    &DiagLib_SecLevelInfo[0],
    DIAGLIB_CFG_SECLEVEL_NUM
};

#define DIAGLIB_STOP_SEC_CST
#include <DiagLib_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

