/* DiagSrv_lib_Core_Cfg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/lib/Core/Cfg/HEADER                                 */
/******************************************************************************/
#ifndef DIAGSRV_LIB_CORE_CFG_H
#define DIAGSRV_LIB_CORE_CFG_H

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
    uint32 Addr;
    uint32 Size;
} DiagSrv_MemoryConfigType;

typedef struct {
    uint8 RewriteAreaNum;
    DiagSrv_MemoryConfigType RewriteAreaInfo;
} DiagSrv_RewriteAreaInfoConfigType;

typedef struct {
    P2CONST(DiagSrv_RewriteAreaInfoConfigType, TYPEDEF, DIAGSRV_APPL_CONST) InfoPtr;
    uint8 RewriteInfoNum;
} DiagSrv_RewriteAreaConfigType;

typedef DiagSrv_MemoryConfigType DiagSrv_SblAreaConfigType;


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

extern CONST(DiagSrv_RewriteAreaConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_RewriteAreaConfig;
extern CONST(DiagSrv_SblAreaConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_SblAreaConfig;

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


#endif /* DIAGSRV_LIB_CORE_CFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

