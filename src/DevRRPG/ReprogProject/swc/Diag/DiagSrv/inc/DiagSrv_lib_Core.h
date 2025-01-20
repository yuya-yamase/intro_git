/* DiagSrv_lib_Core_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/lib/Core/HEADER                                     */
/******************************************************************************/
#ifndef DIAGSRV_LIB_CORE_H
#define DIAGSRV_LIB_CORE_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_REWRITEAREA_INVALID             ((uint8)0xFFU)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetRewriteAreaNumber (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetRewriteAreaNumber
(
    VAR(uint8, AUTOMATIC) Number
);
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_CheckRewriteArea
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    VAR(uint32, AUTOMATIC) CheckAddr,
    VAR(uint32, AUTOMATIC) CheckSize
);
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_CheckSblArea
(
    VAR(uint32, AUTOMATIC) CheckAddr,
    VAR(uint32, AUTOMATIC) CheckSize
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_GetRewriteAreaInfo
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) RewriteAddr,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) RewriteSize
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_GetSblAreaInfo
(
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) SblAddr,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) SblSize
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


#endif /* DIAGSRV_LIB_CORE_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

