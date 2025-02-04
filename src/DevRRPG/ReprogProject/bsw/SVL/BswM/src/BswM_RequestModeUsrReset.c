/* BswM_RequestModeUsrReset_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestModeUsrReset/CODE                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Sys.h>
#include <SchM_BswM.h>
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
static FUNC(void, BSWM_CODE_FAST) BswM_Act_UsrResetExe (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC2_VAR
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC2_VAR
#include <BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC2_CST
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC2_CST
#include <BswM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define BSWM_START_SEC2_CODE
#include <BswM_MemMap.h>

/******************************************************************************/
/* Function Name | BswM_RequestMode_UsrReset                                  */
/* Description   | User reset mode request                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_USR_RESET_EXECUTE                          */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_UsrReset
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    if( Mode == BSWM_MODE_USR_RESET_EXECUTE )
    {
        BswM_Act_UsrResetExe();
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQMODE_USRRESET, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_UsrResetExe                                       */
/* Description   | Action of the User reset mode control(execute)             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_UsrResetExe (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.UsrReset */

    if( BswM_CtrlReqMode.UsrReset == BSWM_MODE_USR_RESET_NONE )
    {
        BswM_CtrlReqMode.UsrReset = BSWM_MODE_USR_RESET_EXECUTE;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.UsrReset */

    if( UpdateFlg == (uint8)STD_ON )
    {
        SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_USR_RESET, SUBMICONIF_MODE_USR_RESET_EXECUTE);

#if (REPROG_CFG_ETH_USE == STD_ON)
        BswM_RequestMode_EthSendRcv(BSWM_MODE_ETH_SENDRCV_WAITSTOP);
#else
        SchM_Finish_MainFunction();
#endif
    }

    return;
}

#define BSWM_STOP_SEC2_CODE
#include <BswM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/02/13 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

