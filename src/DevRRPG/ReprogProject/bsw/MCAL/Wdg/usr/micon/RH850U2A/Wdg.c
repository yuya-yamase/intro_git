/* Wdg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Wdg/CODE                                                    */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Wdg.h>

#include <Sys.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
/* Base address(WDTB0) */
#define WDG_BASE                     ((U4)0xFFBF1000UL)

#define WDG_REG_WDTB0WDTE            (*(volatile U1*)(WDG_BASE + 0x00UL)) /* WDTB enable register */
#define WDG_REG_WDTB0MD              (*(volatile U1*)(WDG_BASE + 0x0CUL)) /* WDTB mode register */

#define WDG_WDTB0WDTE_VALUE          ((U1)0xACU)                          /* WDTB0 start/restart value */
#define WDG_WDTB0MD_VALUE            ((U1)0x67U)                          /* WDTB0MD register set value                 */
                                                                          /* WDTB0WMS         0  :Window size of Window */
                                                                          /*                      Open function is set  */
                                                                          /*                      by WDTB0WS[1:0].      */
                                                                          /* WDTB0OVF[2:0]    110:2^15 / WDTBTCKI       */
                                                                          /* WDTB0WIE         0  :WDTB0TIT disabled     */
                                                                          /* WDTB0ERM         1  :Reset mode            */
                                                                          /* WDTB0WS[1:0]     11 :100%                  */
#define WDG_WDGTRRIGER_CYCLE         (2000UL)                             /* 1UL = 1microsecond */
#define WDG_MS_CONVERT_MICROS        (1000UL)
#define WDG_TIMEOUT_OCCURRED         (0UL)
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define WDG_START_SEC_VAR
#include <Wdg_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(U4, WDG_VAR_CLEARED) Wdg_BasePoint_TimeoutValueReload;
static VAR(U4, WDG_VAR_CLEARED) Wdg_BasePoint_WdgTimerClear;
static VAR(U4, WDG_VAR_CLEARED) Wdg_TimeoutVal;
/*===== Sample ===============================================================*/

#define WDG_STOP_SEC_VAR
#include <Wdg_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define WDG_START_SEC_CST
#include <Wdg_MemMap.h>

#define WDG_STOP_SEC_CST
#include <Wdg_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define WDG_START_SEC_CODE
#include <Wdg_MemMap.h>

/******************************************************************************/
/* Function Name | Wdg_Init                                                   */
/* Description   | Initializes Wdg                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] Config : Address of the Wdg configuration table       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WDG_CODE_SLOW) Wdg_Init
(
    P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) Config
)
{
/*===== Sample ===============================================================*/
    WDG_REG_WDTB0MD = WDG_WDTB0MD_VALUE;
    WDG_REG_WDTB0WDTE = WDG_WDTB0WDTE_VALUE;

    Wdg_TimeoutVal = (U4)((U4)(Config->WdgSetting->WdgInitialTimeout) * WDG_MS_CONVERT_MICROS);

    /* As the first argument is correct, the return value of GetCounterValue() is always E_OK */
    /* Therefore, the return value's type is converted void type */
    (void)GetCounterValue(SYS_COUNTER_ID, &Wdg_BasePoint_WdgTimerClear);

    Wdg_BasePoint_TimeoutValueReload = Wdg_BasePoint_WdgTimerClear;

/*===== Sample ===============================================================*/
    return;
}

/******************************************************************************/
/* Function Name | Wdg_SetTriggerCondition                                    */
/* Description   | Sets the value of the Watchdog timeout                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] Timeout : Timeout value (milliseconds)                */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WDG_CODE_SLOW) Wdg_SetTriggerCondition
(
    VAR(U2, AUTOMATIC) Timeout
)
{
/*===== Sample ===============================================================*/
    if( Timeout <= WDG_CFG_DATA.WdgSetting->WdgMaxTimeout )
    {
        Wdg_TimeoutVal = (U4)((U4)Timeout * WDG_MS_CONVERT_MICROS);

        /* As the first argument is correct, the return value of GetCounterValue() is always E_OK */
        /* Therefore, the return value's type is converted void type */
        (void)GetCounterValue(SYS_COUNTER_ID, &Wdg_BasePoint_TimeoutValueReload);
    }

/*===== Sample ===============================================================*/
    return;
}

/******************************************************************************/
/* Function Name | Wdg_Trigger                                                */
/* Description   | Clears the Watchdog timer                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WDG_CODE_SLOW) Wdg_Trigger (void)
{
/*===== Sample ===============================================================*/
    VAR(U4, AUTOMATIC) CurrentTime;
    VAR(U4, AUTOMATIC) PassedTime;

    if( Wdg_TimeoutVal > WDG_TIMEOUT_OCCURRED)
    {
        /* As the first argument is correct, the return value of GetCounterValue() is always E_OK */
        /* Therefore, the return value's type is converted void type */
        (void)GetCounterValue(SYS_COUNTER_ID, &CurrentTime);
        PassedTime = CurrentTime - Wdg_BasePoint_TimeoutValueReload;
        if( Wdg_TimeoutVal > PassedTime )
        {
            Wdg_TimeoutVal = Wdg_TimeoutVal - PassedTime;
        }
        else
        {
            Wdg_TimeoutVal = WDG_TIMEOUT_OCCURRED;
        }

        Wdg_BasePoint_TimeoutValueReload = CurrentTime;

        if( (CurrentTime - Wdg_BasePoint_WdgTimerClear) > WDG_WDGTRRIGER_CYCLE )
        {
            WDG_REG_WDTB0WDTE = WDG_WDTB0WDTE_VALUE;
            Wdg_BasePoint_WdgTimerClear = CurrentTime;
        }
    }

/*===== Sample ===============================================================*/
    return;
}

/******************************************************************************/
/* Function Name | Wdg_DeInit                                                 */
/* Description   | Deinitializes Wdg                                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WDG_CODE_SLOW) Wdg_DeInit (void)
{
/*===== Sample ===============================================================*/
    Wdg_BasePoint_TimeoutValueReload = 0UL;
    Wdg_BasePoint_WdgTimerClear = 0UL;
    Wdg_TimeoutVal = 0UL;

/*===== Sample ===============================================================*/
    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
#define WDG_STOP_SEC_CODE
#include <Wdg_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

