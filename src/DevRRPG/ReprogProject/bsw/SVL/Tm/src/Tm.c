/* Tm_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Tm/CODE                                                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Tm.h>

#include <Gpt.h>
#include <EcuM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* EcuM_ErrorType */
#define TM_API_ID_SHIFT_TM  (0x01U)
#define TM_E_PARAM_POINTER  (0x01U)

#define TM_UINT32_MAX       ((uint32)0xFFFFFFFFUL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define TM_START_SEC_VAR
#include <Tm_MemMap.h>

#define TM_STOP_SEC_VAR
#include <Tm_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define TM_START_SEC_CST
#include <Tm_MemMap.h>

#define TM_STOP_SEC_CST
#include <Tm_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define TM_START_SEC_CODE
#include <Tm_MemMap.h>

/******************************************************************************/
/* Function Name | Tm_ResetTimer1us32bit                                      */
/* Description   | Resets a timer instance                                    */
/* Preconditions |                                                            */
/* Parameters    | [OUT] TimerPtr : Timer instance                            */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, TM_CODE_SLOW) Tm_ResetTimer1us32bit
(
    P2VAR(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_DATA) TimerPtr
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( TimerPtr != NULL_PTR )
    {
        /* Get free running timer value from MCAL GPT driver */
        Ret = Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_32BIT,
                                      (U4 *)&TimerPtr->StartPoint);
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Tm_GetTimeSpan1us32bit                                     */
/* Description   | Delivers the time difference                               */
/* Preconditions |                                                            */
/* Parameters    | [IN]  TimerPtr    : Timer instance                         */
/*               | [OUT] TimeSpanPtr : Time span                              */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, TM_CODE_SLOW) Tm_GetTimeSpan1us32bit
(
    P2CONST(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr,
    P2VAR(uint32, AUTOMATIC, TM_APPL_DATA) TimeSpanPtr
)
{
    VAR(uint32, AUTOMATIC) CurrentTimeValue;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;
    CurrentTimeValue = 0UL;

    if( ( TimerPtr != NULL_PTR ) && ( TimeSpanPtr != NULL_PTR ) )
    {
        /* Get free running timer value from MCAL GPT driver */
        Ret = Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_32BIT,
                                      (U4 *)&CurrentTimeValue);
        if( Ret == (Std_ReturnType)E_OK )
        {
            /* Calculate the difference between current time and start time */
            if( CurrentTimeValue >= TimerPtr->StartPoint )
            {
                *TimeSpanPtr = CurrentTimeValue - TimerPtr->StartPoint;
            }
            else
            {
                *TimeSpanPtr = ( ( TM_UINT32_MAX - TimerPtr->StartPoint ) + 1UL ) + CurrentTimeValue;   /* no wrap around */
            }
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Tm_ShiftTimer1us32bit                                      */
/* Description   | Shifts the reference time of the timer instance            */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] TimerPtr  : Timer instance                         */
/*               | [IN]    TimeValue : Time value                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, TM_CODE_SLOW) Tm_ShiftTimer1us32bit
(
    P2VAR(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_DATA) TimerPtr,
    VAR(uint32, AUTOMATIC) TimeValue
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) Error;

    if( TimerPtr != NULL_PTR )
    {
        /* Update start time of timer instance */
        if( ( TM_UINT32_MAX - TimeValue ) >= TimerPtr->StartPoint )
        {
            TimerPtr->StartPoint += TimeValue;
        }
        else
        {
            TimerPtr->StartPoint = TimeValue - ( ( TM_UINT32_MAX - TimerPtr->StartPoint ) + 1UL );  /* no wrap around */
        }
    }
    else
    {
        /* Notify EcuM of parameter pointer error */
        Error.ModuleId = ECUM_MODULE_TM;
        Error.ApiId = TM_API_ID_SHIFT_TM;
        Error.ErrorId = TM_E_PARAM_POINTER;

        EcuM_ReportError(&Error);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define TM_STOP_SEC_CODE
#include <Tm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2022/06/07 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

