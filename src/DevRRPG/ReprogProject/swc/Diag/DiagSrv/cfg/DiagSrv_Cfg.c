/* DiagSrv_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/Cfg/CODE                                            */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv.h>

#include "DiagSrv_Cfg.h"

#include "DiagSrv_0x10.h"
#include "DiagSrv_0x11.h"
#include "DiagSrv_0x27.h"
#include "DiagSrv_0x3E.h"
#include "DiagSrv_0x22.h"
#include "DiagSrv_0x2E.h"
#include "DiagSrv_0x31.h"
#include "DiagSrv_0x34.h"
#include "DiagSrv_0x36.h"
#include "DiagSrv_0x37.h"

/* #include "DiagSrv_Template.h" */


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_SIDINFO_NUM     (sizeof(DiagSrv_SidInfoConfig) / sizeof(DiagSrv_SidInfoConfig[0]))
#define DIAGSRV_CFG_SIDFUNCINFO_NUM (sizeof(DiagSrv_SidFuncInfoConfig) / sizeof(DiagSrv_SidFuncInfoConfig[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(DiagSrv_SidInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SidInfoConfig[] = {
     /* SID               Addressing(Func)  Addressing(Phys)      Session(Def)      Session(Prg)      Session(Ext)          SecurityLock */
     { DIAG_SID_DSC,   { DIAG_SUPPORT,     DIAG_SUPPORT     }, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ DIAG_SID_ER,    { DIAG_SUPPORT,     DIAG_SUPPORT     }, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ DIAG_SID_SA,    { DIAG_NOT_SUPPORT, DIAG_SUPPORT     }, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ DIAG_SID_TP,    { DIAG_SUPPORT,     DIAG_SUPPORT     }, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ DIAG_SID_RDBI,  { DIAG_NOT_SUPPORT, DIAG_SUPPORT     }, { DIAG_SUPPORT,     DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_SUPPORT     } }
    ,{ DIAG_SID_WDBI,  { DIAG_NOT_SUPPORT, DIAG_SUPPORT     }, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
    ,{ DIAG_SID_RC,    { DIAG_NOT_SUPPORT, DIAG_SUPPORT     }, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
    ,{ DIAG_SID_RD,    { DIAG_NOT_SUPPORT, DIAG_SUPPORT     }, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
    ,{ DIAG_SID_TD,    { DIAG_NOT_SUPPORT, DIAG_SUPPORT     }, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
    ,{ DIAG_SID_RTE,   { DIAG_NOT_SUPPORT, DIAG_SUPPORT     }, { DIAG_NOT_SUPPORT, DIAG_SUPPORT,     DIAG_NOT_SUPPORT }, { DIAG_NOT_SUPPORT } }
};

CONST(DiagSrv_SidConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SidConfig = {
    &DiagSrv_SidInfoConfig[0],
    DIAGSRV_CFG_SIDINFO_NUM
};

static CONST(DiagSrv_SidFuncInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SidFuncInfoConfig[] = {
     { DIAG_SID_DSC,   &DiagSrv_0x10_Init, &DiagSrv_0x10_Time, &DiagSrv_0x10_Processing, &DiagSrv_0x10_Confirmation, &DiagSrv_0x10_NotifyChangeSession }
    ,{ DIAG_SID_ER,    &DiagSrv_0x11_Init, &DiagSrv_0x11_Time, &DiagSrv_0x11_Processing, &DiagSrv_0x11_Confirmation, NULL_PTR                          }
    ,{ DIAG_SID_SA,    &DiagSrv_0x27_Init, &DiagSrv_0x27_Time, &DiagSrv_0x27_Processing, &DiagSrv_0x27_Confirmation, &DiagSrv_0x27_NotifyChangeSession }
    ,{ DIAG_SID_TP,    &DiagSrv_0x3E_Init, &DiagSrv_0x3E_Time, &DiagSrv_0x3E_Processing, &DiagSrv_0x3E_Confirmation, NULL_PTR                          }
    ,{ DIAG_SID_RDBI,  &DiagSrv_0x22_Init, &DiagSrv_0x22_Time, &DiagSrv_0x22_Processing, &DiagSrv_0x22_Confirmation, NULL_PTR                          }
    ,{ DIAG_SID_WDBI,  &DiagSrv_0x2E_Init, &DiagSrv_0x2E_Time, &DiagSrv_0x2E_Processing, &DiagSrv_0x2E_Confirmation, NULL_PTR                          }
    ,{ DIAG_SID_RC,    &DiagSrv_0x31_Init, &DiagSrv_0x31_Time, &DiagSrv_0x31_Processing, &DiagSrv_0x31_Confirmation, NULL_PTR                          }
    ,{ DIAG_SID_RD,    &DiagSrv_0x34_Init, &DiagSrv_0x34_Time, &DiagSrv_0x34_Processing, &DiagSrv_0x34_Confirmation, NULL_PTR                          }
    ,{ DIAG_SID_TD,    &DiagSrv_0x36_Init, &DiagSrv_0x36_Time, &DiagSrv_0x36_Processing, &DiagSrv_0x36_Confirmation, NULL_PTR                          }
    ,{ DIAG_SID_RTE,   &DiagSrv_0x37_Init, &DiagSrv_0x37_Time, &DiagSrv_0x37_Processing, &DiagSrv_0x37_Confirmation, NULL_PTR                          }
};

CONST(DiagSrv_SidFuncConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SidFuncConfig = {
    &DiagSrv_SidFuncInfoConfig[0],
    DIAGSRV_CFG_SIDFUNCINFO_NUM
};

CONST(DiagSrv_ApEntryConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_ApEntryConfig = {
    DIAG_SESSION_PRG,
    DIAG_SECURITY_LOCK
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
/**** End of File *************************************************************/

