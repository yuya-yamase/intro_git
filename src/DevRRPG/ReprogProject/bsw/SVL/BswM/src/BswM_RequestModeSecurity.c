/* BswM_RequestModeSecurity_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestModeSecurity/CODE                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Rte.h>
#include <Sys.h>
#include <SubMiconIf.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_SecurityUnlock
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
);
static FUNC(void, BSWM_CODE_FAST) BswM_Act_SecurityLock (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_VAR
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC_VAR
#include <BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_CST
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC_CST
#include <BswM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define BSWM_START_SEC_CODE
#include <BswM_MemMap.h>

/******************************************************************************/
/* Function Name | BswM_RequestMode_Security                                  */
/* Description   | Security mode request                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV1                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV2                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV3                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV4                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV5                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV6                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV7                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV8                        */
/*               |       BSWM_MODE_SECURITY_LOCK                              */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Security
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    if( ( Mode == BSWM_MODE_SECURITY_UNLOCK_LV1 ) ||
        ( Mode == BSWM_MODE_SECURITY_UNLOCK_LV2 ) ||
        ( Mode == BSWM_MODE_SECURITY_UNLOCK_LV3 ) ||
        ( Mode == BSWM_MODE_SECURITY_UNLOCK_LV4 ) ||
        ( Mode == BSWM_MODE_SECURITY_UNLOCK_LV5 ) ||
        ( Mode == BSWM_MODE_SECURITY_UNLOCK_LV6 ) ||
        ( Mode == BSWM_MODE_SECURITY_UNLOCK_LV7 ) ||
        ( Mode == BSWM_MODE_SECURITY_UNLOCK_LV8 ) )
    {
        BswM_Act_SecurityUnlock(Mode);
    }
    else if( Mode == BSWM_MODE_SECURITY_LOCK )
    {
        BswM_Act_SecurityLock();
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQMODE_SECURITY, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_SecurityUnlock                                    */
/* Description   | Action of the security mode control(Unlock)                */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV1                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV2                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV3                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV4                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV5                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV6                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV7                        */
/*               |       BSWM_MODE_SECURITY_UNLOCK_LV8                        */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_SecurityUnlock
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.Security */

    if( BswM_CtrlReqMode.Security == BSWM_MODE_SECURITY_LOCK )
    {
        BswM_CtrlReqMode.Security = Mode;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.Security */

    if( UpdateFlg == (uint8)STD_ON )
    {
        Rte_RpgEvtHk_RpgEvt_UnlockSec();

        SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_SECURITY, (uint16)Mode);
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_Act_SecurityLock                                      */
/* Description   | Action of the security mode control(Lock)                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_SecurityLock (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.Security */

    if( ( BswM_CtrlReqMode.Security == BSWM_MODE_SECURITY_UNLOCK_LV1 ) ||
        ( BswM_CtrlReqMode.Security == BSWM_MODE_SECURITY_UNLOCK_LV2 ) ||
        ( BswM_CtrlReqMode.Security == BSWM_MODE_SECURITY_UNLOCK_LV3 ) ||
        ( BswM_CtrlReqMode.Security == BSWM_MODE_SECURITY_UNLOCK_LV4 ) ||
        ( BswM_CtrlReqMode.Security == BSWM_MODE_SECURITY_UNLOCK_LV5 ) ||
        ( BswM_CtrlReqMode.Security == BSWM_MODE_SECURITY_UNLOCK_LV6 ) ||
        ( BswM_CtrlReqMode.Security == BSWM_MODE_SECURITY_UNLOCK_LV7 ) ||
        ( BswM_CtrlReqMode.Security == BSWM_MODE_SECURITY_UNLOCK_LV8 ) )
    {
        BswM_CtrlReqMode.Security = BSWM_MODE_SECURITY_LOCK;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.Security */

    if( UpdateFlg == (uint8)STD_ON )
    {
        Rte_RpgEvtHk_RpgEvt_LockSec();

        SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_SECURITY, SUBMICONIF_MODE_SECURITY_LOCK);
    }

    return;
}

#define BSWM_STOP_SEC_CODE
#include <BswM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

