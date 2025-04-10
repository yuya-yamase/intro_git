/* Sys_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Sys/CODE                                                    */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Sys.h>

#include <Gpt.h>
#include <Int.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SYS_COMBINEDATA_BIT_SHIFT   (8U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define SYS_START_SEC_VAR
#include <Sys_MemMap.h>

#define SYS_STOP_SEC_VAR
#include <Sys_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SYS_START_SEC_CST
#include <Sys_MemMap.h>

#define SYS_STOP_SEC_CST
#include <Sys_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define SYS_START_SEC_CODE
#include <Sys_MemMap.h>

/******************************************************************************/
/* Function Name | MaskInterruptAll                                           */
/* Description   | Mask all interrupts                                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | MaskPattern                                                */
/* Notes         | - Call this function between Int_Init() and Int_DeInit().  */
/*               | - Specify the return value of this function as the         */
/*               |   argument of UnMaskInterruptAll().                        */
/******************************************************************************/
FUNC(uint8, SYS_CODE_SLOW) MaskInterruptAll (void)
{
    VAR(uint8, AUTOMATIC) MaskPattern;

    /* Mask all interrupts using MCAL INT driver */
    MaskPattern = Int_DisableIntMaskLevel(INT_MASK_ALL);

    return MaskPattern;
}

/******************************************************************************/
/* Function Name | UnMaskInterruptAll                                         */
/* Description   | Unmask the interrupt                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] MaskPattern : Return value of MaskInterruptAll()      */
/* Return Value  | None                                                       */
/* Notes         | - Call this function between Int_Init() and Int_DeInit().  */
/*               | - Specify the return value of MaskInterruptAll() as the    */
/*               |   argument of this function.                               */
/******************************************************************************/
FUNC(void, SYS_CODE_SLOW) UnMaskInterruptAll
(
    VAR(uint8, AUTOMATIC) MaskPattern
)
{
    /* Unmask interrupts specified by argument(mask pattern), using MCAL INT driver */
    Int_EnableIntMaskLevel(MaskPattern);

    return;
}

/******************************************************************************/
/* Function Name | GetCounterValue                                            */
/* Description   | Reads the current count value of a counter                 */
/* Preconditions |                                                            */
/* Parameters    | [IN]  CounterID : The Counter ID                           */
/*               | [OUT] Value     : Current count value                      */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | Call this function between Gpt_Init() and Gpt_DeInit()     */
/******************************************************************************/
FUNC(StatusType, SYS_CODE_SLOW) GetCounterValue
(
    VAR(CounterType, AUTOMATIC) CounterID,
    VAR(TickRefType, AUTOMATIC) Value
)
{
    VAR(StatusType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    /* Check if parameters are valid */
    if( ( CounterID == SYS_COUNTER_ID ) && ( Value != NULL_PTR ) )
    {
        /* Get free running timer value from MCAL GPT driver */
        Ret = (StatusType)Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_32BIT, (U4 *)Value);
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Rpg_MemCopy                                                */
/* Description   | Copy block of memory                                       */
/* Preconditions |                                                            */
/* Parameters    | [OUT] DestAddress : The memory location to copy to         */
/*               | [IN]  SrcAddress  : The memory location to copy from       */
/*               | [IN]  Size        : Number of bytes to copy                */
/* Return Value  | None                                                       */
/* Notes         | This function does not check arguments.                    */
/******************************************************************************/
FUNC(void, SYS_CODE_SLOW) Rpg_MemCopy
(
    P2VAR(uint8, AUTOMATIC, SYS_APPL_DATA) DestAddress,
    P2CONST(uint8, AUTOMATIC, SYS_APPL_CONST) SrcAddress,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(uint32, AUTOMATIC) i;
    P2VAR(uint8, AUTOMATIC, SYS_APPL_DATA) DestPtr;
    P2CONST(uint8, AUTOMATIC, SYS_APPL_CONST) SrcPtr;

    DestPtr = DestAddress;
    SrcPtr = SrcAddress;

    for( i = 0UL; i < Size; i++ )
    {
        DestPtr[i] = SrcPtr[i];
    }

    return;
}

/******************************************************************************/
/* Function Name | Rpg_MemSet                                                 */
/* Description   | Fill block of memory                                       */
/* Preconditions |                                                            */
/* Parameters    | [OUT] DestAddress : The memory location to fill to         */
/*               | [IN]  Value       : Fill byte                              */
/*               | [IN]  Size        : Number of bytes to fill                */
/* Return Value  | None                                                       */
/* Notes         | This function does not check arguments.                    */
/******************************************************************************/
FUNC(void, SYS_CODE_SLOW) Rpg_MemSet
(
    P2VAR(uint8, AUTOMATIC, SYS_APPL_DATA) DestAddress,
    VAR(uint8, AUTOMATIC) Value,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(uint32, AUTOMATIC) i;
    P2VAR(uint8, AUTOMATIC, SYS_APPL_DATA) DestPtr;

    DestPtr = DestAddress;

    for( i = 0UL; i < Size; i++ )
    {
        DestPtr[i] = Value;
    }

    return;
}

/******************************************************************************/
/* Function Name | Rpg_ByteCombine                                            */
/* Description   | Combine data                                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] SrcAddress : The memory location to combine to        */
/*               | [IN] Size       : Number of bytes to combine               */
/* Return Value  | Combined data                                              */
/* Notes         | - This function does not check arguments.                  */
/*               | - Size of the parameter supports only 2 or 4.              */
/*               | - The return value has to cast depending on Size of the    */
/*               |   parameter.                                               */
/******************************************************************************/
FUNC(uint32, SYS_CODE_SLOW) Rpg_ByteCombine
(
    P2CONST(uint8, AUTOMATIC, SYS_APPL_CONST) SrcAddress,
    VAR(uint8, AUTOMATIC) Size
)
{
    VAR(uint32, AUTOMATIC) CombineData;
    VAR(uint8, AUTOMATIC) i;
    P2CONST(uint8, AUTOMATIC, SYS_APPL_CONST) SrcPtr;

    CombineData = 0UL;
    SrcPtr = SrcAddress;

    for( i = 0U; i < Size; i++ )
    {
        CombineData = (CombineData << SYS_COMBINEDATA_BIT_SHIFT) | (uint32)SrcPtr[i];
    }

    return CombineData;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define SYS_STOP_SEC_CODE
#include <Sys_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

