/* Rte_Sys_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/Sys/CODE                                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Rte_Sys.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define RTE_SYS_START_SEC_VAR
#include <Rte_Sys_MemMap.h>

#define RTE_SYS_STOP_SEC_VAR
#include <Rte_Sys_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RTE_SYS_START_SEC_CST
#include <Rte_Sys_MemMap.h>

#define RTE_SYS_STOP_SEC_CST
#include <Rte_Sys_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define RTE_SYS_START_SEC_CODE
#include <Rte_Sys_MemMap.h>

/******************************************************************************/
/* Function Name | Rte_MaskInterruptAll                                       */
/* Description   | Wrapper of MaskInterruptAll()                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Mask pattern                                               */
/* Notes         | - Call this function between RpgEvtHk_SchEvt_InitFirst()   */
/*               |   and RpgEvtHk_SchEvt_DeInitLast().                        */
/*               | - Specify the return value of this function as the         */
/*               |   argument of Rte_UnMaskInterruptAll().                    */
/******************************************************************************/
FUNC(uint8, RTE_CODE_SLOW) Rte_MaskInterruptAll (void)
{
    VAR(uint8, AUTOMATIC) MaskPattern;

    MaskPattern = MaskInterruptAll();

    return MaskPattern;
}

/******************************************************************************/
/* Function Name | Rte_UnMaskInterruptAll                                     */
/* Description   | Wrapper of UnMaskInterruptAll()                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] MaskPattern : Return value of MaskInterruptAll()      */
/* Return Value  | None                                                       */
/* Notes         | - Call this function between RpgEvtHk_SchEvt_InitFirst()   */
/*               |   and RpgEvtHk_SchEvt_DeInitLast().                        */
/*               | - Specify the return value of Rte_MaskInterruptAll as the  */
/*               |   argument of this function.                               */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_UnMaskInterruptAll
(
    VAR(uint8, AUTOMATIC) MaskPattern
)
{
    UnMaskInterruptAll(MaskPattern);

    return;
}

/******************************************************************************/
/* Function Name | Rte_GetCounterValue                                        */
/* Description   | Wrapper of GetCounterValue()                               */
/* Preconditions |                                                            */
/* Parameters    | [IN]  CounterID : The Counter ID                           */
/*               |        RTE_SYS_COUNTER_ID                                  */
/*               | [OUT] Value     : Current count value                      */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | Call this function between RpgEvtHk_SchEvt_InitFirst() and */
/*               | RpgEvtHk_SchEvt_DeInitLast().                              */
/******************************************************************************/
FUNC(StatusType, RTE_CODE_SLOW) Rte_GetCounterValue
(
    VAR(Rte_CounterType, AUTOMATIC) CounterID,
    VAR(Rte_TickRefType, AUTOMATIC) Value
)
{
    VAR(StatusType, AUTOMATIC) Ret;

    Ret = GetCounterValue((CounterType)CounterID, (TickRefType)Value);

    return Ret;
}

/******************************************************************************/
/* Function Name | Rte_Rpg_MemCopy                                            */
/* Description   | Wrapper of Rpg_MemCopy()                                   */
/* Preconditions |                                                            */
/* Parameters    | [OUT] DestAddress : The memory location to copy to         */
/*               | [IN]  SrcAddress  : The memory location to copy from       */
/*               | [IN]  Size        : Number of bytes to copy                */
/* Return Value  | None                                                       */
/* Notes         | This function does not check arguments.                    */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_Rpg_MemCopy
(
    P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DestAddress,
    P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) SrcAddress,
    VAR(uint32, AUTOMATIC) Size
)
{
    Rpg_MemCopy(DestAddress, SrcAddress, Size);

    return;
}

/******************************************************************************/
/* Function Name | Rte_Rpg_MemSet                                             */
/* Description   | Wrapper of Rpg_MemSet()                                    */
/* Preconditions |                                                            */
/* Parameters    | [OUT] DestAddress : The memory location to fill to         */
/*               | [IN]  Value       : Fill byte                              */
/*               | [IN]  Size        : Number of bytes to fill                */
/* Return Value  | None                                                       */
/* Notes         | This function does not check arguments.                    */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_Rpg_MemSet
(
    P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DestAddress,
    VAR(uint8, AUTOMATIC) Value,
    VAR(uint32, AUTOMATIC) Size
)
{
    Rpg_MemSet(DestAddress, Value, Size);

    return;
}

/******************************************************************************/
/* Function Name | Rte_Rpg_ByteCombine                                        */
/* Description   | Wrapper of Rpg_ByteCombine()                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] SrcAddress : The memory location to combine to        */
/*               | [IN] Size       : Number of bytes to combine               */
/* Return Value  | Combined data                                              */
/* Notes         | - This function does not check arguments.                  */
/*               | - Size of the parameter supports only 2 or 4.              */
/*               | - The return value has to cast depending on Size of the    */
/*               |   parameter.                                               */
/******************************************************************************/
FUNC(uint32, RTE_CODE_SLOW) Rte_Rpg_ByteCombine
(
    P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) SrcAddress,
    VAR(uint8, AUTOMATIC) Size
)
{
    VAR(uint32, AUTOMATIC) CombineData;

    CombineData = Rpg_ByteCombine(SrcAddress, Size);

    return CombineData;
}

/******************************************************************************/
/* Function Name | Rte_Rpg_Div_u32                                            */
/* Description   | Wrapper of Rpg_Div_u32()                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] Dividend : Dividend                                   */
/*               | [IN] Divisor  : Divisor                                    */
/* Return Value  | Quotient                                                   */
/* Notes         | This function does not check arguments.                    */
/******************************************************************************/
FUNC(uint32, RTE_CODE_SLOW) Rte_Rpg_Div_u32
(
    VAR(uint32, AUTOMATIC) Dividend,
    VAR(uint32, AUTOMATIC) Divisor
)
{
    VAR(uint32, AUTOMATIC) Quotient;

    Quotient = Rpg_Div_u32(Dividend, Divisor);

    return Quotient;
}

/******************************************************************************/
/* Function Name | Rte_Rpg_Mod_u32                                            */
/* Description   | Wrapper of Rpg_Mod_u32()                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] Dividend : Dividend                                   */
/*               | [IN] Divisor  : Divisor                                    */
/* Return Value  | Remainder                                                  */
/* Notes         | This function does not check arguments.                    */
/******************************************************************************/
FUNC(uint32, RTE_CODE_SLOW) Rte_Rpg_Mod_u32
(
    VAR(uint32, AUTOMATIC) Dividend,
    VAR(uint32, AUTOMATIC) Divisor
)
{
    VAR(uint32, AUTOMATIC) Remainder;

    Remainder = Rpg_Mod_u32(Dividend, Divisor);

    return Remainder;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define RTE_SYS_STOP_SEC_CODE
#include <Rte_Sys_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

