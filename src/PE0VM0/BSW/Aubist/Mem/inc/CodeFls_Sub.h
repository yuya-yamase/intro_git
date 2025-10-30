/* CodeFls_Sub_h                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CODEFLS_SUB_H
#define CODEFLS_SUB_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
FUNC(void, MEM_CODE) CodeFls_Sub_InitVariables(void);
FUNC(void, MEM_CODE) CodeFls_Sub_InitOpInfo(void);
FUNC(uint8, MEM_CODE) CodeFls_Sub_GetFaciMax(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_Reset
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(uint8, MEM_CODE) CodeFls_Sub_GetFaciNum
(
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckParamCtrl
(
    VAR(uint8, AUTOMATIC) u1ReqKind,
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckParamErase
(
    VAR(uint32, AUTOMATIC) u4EraseAddr,
    VAR(uint32, AUTOMATIC) u4EraseSize,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1InfoNum
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckParamWrite
(
    VAR(uint32, AUTOMATIC) u4TargetAddr,
    VAR(uint32, AUTOMATIC) u4DataSize
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckTimeOut(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckSwitchValidArea(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_MultiOperation
(
    VAR(uint8, AUTOMATIC) u1FaciNum,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1IsFinish
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckInvalidArea
(
    VAR(uint32, AUTOMATIC) u4Addr,
    VAR(uint32, AUTOMATIC) u4Size
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckParamBlankCheck
(
    VAR(uint32, AUTOMATIC) u4TargetAddr,
    VAR(uint32, AUTOMATIC) u4DataSize
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Sub_CheckMirrorOpInfo(void);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_CONST_32
#include <Mem_MemMap.h>


#endif  /* CODEFLS_SUB_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
