/* DiagSrv_0x10_Cfg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x10/Cfg/HEADER                                     */
/******************************************************************************/
#ifndef DIAGSRV_0X10_CFG_H
#define DIAGSRV_0X10_CFG_H

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
    uint8 Subfunc;
    uint16 P2ServerMax;      /* (LSB:1ms) */
    uint16 P2AsterServerMax; /* (LSB:10ms) */
} DiagSrv_0x10_TimingParamInfoConfigType;

typedef struct {
    P2CONST(DiagSrv_0x10_TimingParamInfoConfigType, TYPEDEF, DIAGSRV_APPL_CONST) InfoPtr;
    uint8 TimingParamNum;
} DiagSrv_0x10_TimingParamConfigType;


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

extern CONST(Diag_SubfuncConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x10_SubfuncConfig;
extern CONST(DiagSrv_0x10_TimingParamConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_0x10_TimingParamConfig;

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


#endif /* DIAGSRV_0X10_CFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

