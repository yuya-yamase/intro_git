/* DiagSrv_SubMicon_Core_Cfg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/SubMicon/Core/Cfg/HEADER                            */
/******************************************************************************/
#ifndef DIAGSRV_SUBMICON_CORE_CFG_H
#define DIAGSRV_SUBMICON_CORE_CFG_H

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 MiconId;
    uint8 InfoNum;
    P2CONST(uint8, TYPEDEF, DIAGSRV_APPL_CONST) InfoPtr;
} DiagSrv_SubMRewriteAreaInfoConfigType;

typedef struct {
    uint8 MiconNum;
    P2CONST(DiagSrv_SubMRewriteAreaInfoConfigType, TYPEDEF, DIAGSRV_APPL_CONST) AreaPtr;
} DiagSrv_SubMRewriteConfigType;


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

extern CONST(DiagSrv_SubMRewriteConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SubMRewriteConfig;

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>

#endif /* (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) */
#endif /* DIAGSRV_SUBMICON_CORE_CFG_H */


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

