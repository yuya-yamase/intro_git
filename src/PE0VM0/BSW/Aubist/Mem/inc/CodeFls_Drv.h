/* CodeFls_Drv_h                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/CodeFls/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CODEFLS_DRV_H
#define CODEFLS_DRV_H

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
/* Param Struct */
typedef struct
{
    uint32      u4Addr;
    uint32      u4Bit;
    uint32      u4Time;
} CodeFls_GetRegParam;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
FUNC(void, MEM_CODE) CodeFls_Drv_ResetInitr
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(uint16, MEM_CODE) CodeFls_Drv_GetFlashMode
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_SwitchModeStart
(
    VAR(uint8, AUTOMATIC) u1FaciNum,
    VAR(uint16, AUTOMATIC) u2Mode
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_ForcedStop
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(void, MEM_CODE) CodeFls_Drv_InitRegister
(
    VAR(uint8, AUTOMATIC) u1Request,
    VAR(uint8, AUTOMATIC) u1FaciMax
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_VerifyID(void);
FUNC(void, MEM_CODE) CodeFls_Drv_ErrRefresh
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(uint8, MEM_CODE) CodeFls_Drv_CheckReady
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(void, MEM_CODE) CodeFls_Drv_GetClockValue(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_Clear_Cache_Asm(void);
FUNC(void, MEM_CODE) CodeFls_Drv_StartTimer(void);
FUNC(uint8, MEM_CODE) CodeFls_Drv_GetRegReady_Asm
(
    P2CONST(CodeFls_GetRegParam, AUTOMATIC, MEM_APPL_DATA) pstParam
); /* MISRA DEVIATION */ /* Not defined in the project */
FUNC(void, MEM_CODE) CodeFls_Drv_GetRegReady16bit_Asm
(
    P2CONST(CodeFls_GetRegParam, AUTOMATIC, MEM_APPL_DATA) pstParam
); /* MISRA DEVIATION */ /* Not defined in the project */
FUNC(void, MEM_CODE) CodeFls_Drv_Syncp_Asm(void); /* MISRA DEVIATION */ /* Not defined in the project */
FUNC(uint32, MEM_CODE) CodeFls_Drv_Div_Asm
(
    VAR(uint32, AUTOMATIC) u4Dividend,
    VAR(uint32, AUTOMATIC) u4Divisor
); /* MISRA DEVIATION */ /* Not defined in the project */
FUNC(uint32, MEM_CODE) CodeFls_Drv_GetPEID_Asm(void); /* MISRA DEVIATION */ /* Not defined in the project */
FUNC(void, MEM_CODE) CodeFls_Drv_ResetRegister
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(void, MEM_CODE) CodeFls_Drv_EraseOp
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(void, MEM_CODE) CodeFls_Drv_WriteOp
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_BlankCheckOp(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_SuspendOp
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_CheckError
(
    VAR(uint8, AUTOMATIC) u1FaciNum
);
FUNC(uint8, MEM_CODE) CodeFls_Drv_GetMapMode(void);
FUNC(void, MEM_CODE) CodeFls_Drv_SetCsaWriteDataChengeArea(void);
FUNC(uint8, MEM_CODE) CodeFls_Drv_SetCsaWriteDataOtherArea(void);
FUNC(void, MEM_CODE) CodeFls_Drv_SetSwitchWriteData(void);
FUNC(uint8, MEM_CODE) CodeFls_Drv_CheckSwitchArea(void);
FUNC(void, MEM_CODE) CodeFls_Drv_CsaEraseOp(void);
FUNC(void, MEM_CODE) CodeFls_Drv_CsaWriteOp(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_SwitchEraseOp(void);
FUNC(void, MEM_CODE) CodeFls_Drv_SwitchWriteOp(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_TagEraseOp(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_TagUpdateOp(void);
FUNC(Std_ReturnType, MEM_CODE) CodeFls_Drv_FinishSwitchValidArea(void);
FUNC(void, MEM_CODE) CodeFls_Drv_GetCounterValue
(
    P2VAR(uint32, AUTOMATIC, MEM_APPL_DATA) u4aLtscCnt
);
FUNC(uint8, MEM_CODE) CodeFls_Drv_GetEccErrorAddressRom1bit
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
);
FUNC(uint8, MEM_CODE) CodeFls_Drv_GetEccErrorAddressRom2bit
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
);


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


#endif  /* CODEFLS_DRV_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
