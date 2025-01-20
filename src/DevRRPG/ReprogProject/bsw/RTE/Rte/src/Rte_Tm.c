/* Rte_Tm_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/Tm/CODE                                                 */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Rte_Tm.h>


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
#define RTE_TM_START_SEC_VAR
#include <Rte_Tm_MemMap.h>

#define RTE_TM_STOP_SEC_VAR
#include <Rte_Tm_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RTE_TM_START_SEC_CST
#include <Rte_Tm_MemMap.h>

#define RTE_TM_STOP_SEC_CST
#include <Rte_Tm_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define RTE_TM_START_SEC_CODE
#include <Rte_Tm_MemMap.h>

/******************************************************************************/
/* Function Name | Rte_Tm_ResetTimer1us32bit                                  */
/* Description   | Wrapper of Tm_ResetTimer1us32bit()                         */
/* Preconditions |                                                            */
/* Parameters    | [OUT] TimerPtr : Timer instance                            */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_SLOW) Rte_Tm_ResetTimer1us32bit
(
    P2VAR(Rte_Tm_PredefTimer1us32bitType, AUTOMATIC, RTE_APPL_DATA) TimerPtr
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = Tm_ResetTimer1us32bit((Tm_PredefTimer1us32bitType *)TimerPtr);

    return Ret;
}

/******************************************************************************/
/* Function Name | Rte_Tm_GetTimeSpan1us32bit                                 */
/* Description   | Wrapper of Tm_GetTimeSpan1us32bit()                        */
/* Preconditions |                                                            */
/* Parameters    | [IN]  TimerPtr    : Timer instance                         */
/*               | [OUT] TimeSpanPtr : Time span                              */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_SLOW) Rte_Tm_GetTimeSpan1us32bit
(
    P2CONST(Rte_Tm_PredefTimer1us32bitType, AUTOMATIC, RTE_APPL_CONST) TimerPtr,
    P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) TimeSpanPtr
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = Tm_GetTimeSpan1us32bit((const Tm_PredefTimer1us32bitType *)TimerPtr, TimeSpanPtr);

    return Ret;
}

/******************************************************************************/
/* Function Name | Rte_Tm_ShiftTimer1us32bit                                  */
/* Description   | Wrapper of Tm_ShiftTimer1us32bit()                         */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] TimerPtr  : Timer instance                         */
/*               | [IN]    TimeValue : Time value                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_Tm_ShiftTimer1us32bit
(
    P2VAR(Rte_Tm_PredefTimer1us32bitType, AUTOMATIC, RTE_APPL_DATA) TimerPtr,
    VAR(uint32, AUTOMATIC) TimeValue
)
{
    Tm_ShiftTimer1us32bit((Tm_PredefTimer1us32bitType *)TimerPtr, TimeValue);

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define RTE_TM_STOP_SEC_CODE
#include <Rte_Tm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

