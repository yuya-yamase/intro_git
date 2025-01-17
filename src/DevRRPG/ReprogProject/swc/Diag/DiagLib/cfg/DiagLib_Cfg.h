/* DiagLib_Cfg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagLib/Cfg/HEADER                                          */
/******************************************************************************/
#ifndef DIAGLIB_CFG_H
#define DIAGLIB_CFG_H

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
    uint32 DlMaxNumOfBlockLen;
    uint32 UlMaxNumOfBlockLen;
} DiagLib_TransferConfigType;

typedef struct {
    uint8 SecurityLevel;
} DiagLib_SecLevelInfoType;

typedef struct {
    P2CONST(DiagLib_SecLevelInfoType, TYPEDEF, DIAGLIB_APPL_CONST) InfoPtr;
    uint8 Num;
} DiagLib_SecLevelConfigType;


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGLIB_START_SEC_CST
#include <DiagLib_MemMap.h>

extern CONST(DiagLib_TransferConfigType, DIAGLIB_CONFIG_DATA) DiagLib_TransferConfig;
extern CONST(DiagLib_SecLevelConfigType, DIAGLIB_CONFIG_DATA) DiagLib_SecLevelConfig;

#define DIAGLIB_STOP_SEC_CST
#include <DiagLib_MemMap.h>


#endif /* DIAGLIB_CFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

