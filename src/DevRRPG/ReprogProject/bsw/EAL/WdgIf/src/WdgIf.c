/* WdgIf_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | WdgIf/CODE                                                  */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <WdgIf.h>

#include <Wdg.h>
#include <EcuM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define WDGIF_API_ID_SETTRIGGERCOND (0x00U)

#define WDGIF_E_PARAM_DEVICE        (0x01U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define WDGIF_START_SEC_VAR
#include <WdgIf_MemMap.h>

#define WDGIF_STOP_SEC_VAR
#include <WdgIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define WDGIF_START_SEC_CST
#include <WdgIf_MemMap.h>

#define WDGIF_STOP_SEC_CST
#include <WdgIf_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define WDGIF_START_SEC_CODE
#include <WdgIf_MemMap.h>

/******************************************************************************/
/* Function Name | WdgIf_SetTriggerCondition                                  */
/* Description   | Sets the value of the Watchdog timeout                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] DeviceIndex : Driver instance                         */
/*               | [IN] Timeout     : Timeout value (milliseconds)            */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WDGIF_CODE_SLOW) WdgIf_SetTriggerCondition
(
    VAR(uint8, AUTOMATIC) DeviceIndex,
    VAR(uint16, AUTOMATIC) Timeout
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) ErrorInfo;

    if( DeviceIndex == WDGIF_DEVICEINDEX_0 )
    {
        Wdg_SetTriggerCondition(Timeout);
    }
    else
    {
        ErrorInfo.ModuleId = ECUM_MODULE_WDGIF;
        ErrorInfo.ApiId = WDGIF_API_ID_SETTRIGGERCOND;
        ErrorInfo.ErrorId = WDGIF_E_PARAM_DEVICE;
        EcuM_ReportError(&ErrorInfo);
    }

    return;
}

/******************************************************************************/
/* Function Name | WdgIf_Trigger                                              */
/* Description   | Clears the Watchdog timer                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WDGIF_CODE_SLOW) WdgIf_Trigger (void)
{
    Wdg_Trigger();

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
#define WDGIF_STOP_SEC_CODE
#include <WdgIf_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

