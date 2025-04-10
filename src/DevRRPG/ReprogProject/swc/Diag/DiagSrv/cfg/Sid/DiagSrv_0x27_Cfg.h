/* DiagSrv_0x27_Cfg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x27/Cfg/HEADER                                     */
/******************************************************************************/
#ifndef DIAGSRV_0X27_CFG_H
#define DIAGSRV_0X27_CFG_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_0X27_SUPPORT_SECLEVEL_NUM    (1U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 SecurityAccessType;
    uint8 AttCnt;
    uint8 StaticSeed;
    uint16 DelayTimer;
    uint16 SeedSize;
    P2VAR(uint8, TYPEDEF, DIAGSRV_APPL_DATA) SeedPtr;
    uint16 KeySize;
    P2VAR(uint8, TYPEDEF, DIAGSRV_APPL_DATA) KeyPtr;
} DiagSrv_0x27_SecLevelInfoConfigType;

typedef struct {
    P2CONST(DiagSrv_0x27_SecLevelInfoConfigType, TYPEDEF, DIAGSRV_APPL_CONST) InfoPtr;
    uint8 Num;
} DiagSrv_0x27_SecLevelConfigType;


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

extern CONST(Diag_SubfuncConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x27_SubfuncConfig;
extern CONST(DiagSrv_0x27_SecLevelConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x27_SecLevelConfig;

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


#endif /* DIAGSRV_0X27_CFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

