/* Mem_Sub_h                                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/Mem/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MEM_SUB_H
#define MEM_SUB_H

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
FUNC(void, MEM_CODE) Mem_Sub_InitVariables(void);
FUNC(void, MEM_CODE) Mem_Sub_Det_ReportError
(
    VAR(uint16, AUTOMATIC) ModuleID,
    VAR(uint8, AUTOMATIC) InstanceID,
    VAR(uint8, AUTOMATIC) ApiID,
    VAR(uint8, AUTOMATIC) ErrID
);
FUNC(void, MEM_CODE) Mem_Sub_SetJobStatus
(
    VAR(uint8, AUTOMATIC) sts
);
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckParamErase
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(uint32, AUTOMATIC) u4EraseAddr,
    VAR(uint32, AUTOMATIC) u4EraseSize,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1InfoNum
);
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckParamRead
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(uint32, AUTOMATIC) u4SourceAddr,
    P2CONST(Mem_DataType, AUTOMATIC, MEM_APPL_DATA) pu1TargetAddr,
    VAR(uint32, AUTOMATIC) u4DataSize,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1InfoNum
);
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckParamWrite
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(uint32, AUTOMATIC) u4TargetAddr,
    P2CONST(Mem_DataType, AUTOMATIC, MEM_APPL_DATA) pu1sourceDataPtr,
    VAR(uint32, AUTOMATIC) u4DataSize,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1InfoNum
);
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckParamBlankCheck
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(uint32, AUTOMATIC) u4TargetAddr,
    VAR(uint32, AUTOMATIC) u4DataSize,
    P2VAR(uint8, AUTOMATIC, MEM_APPL_DATA) pu1InfoNum
);
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_InstanceIdCheck
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId
);
FUNC(Std_ReturnType, MEM_CODE) Mem_Sub_CheckMirrorOpInfo(void);
FUNC(void, MEM_CODE) Mem_Sub_ReadOp(void);
FUNC(void, MEM_CODE) Mem_Sub_ReqCodeFls(void);
FUNC(void, MEM_CODE) Mem_Sub_Failed(void);
FUNC(void, MEM_CODE) Mem_Sub_CmpltChkCodeFls(void);


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


#endif  /* MEM_SUB_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
