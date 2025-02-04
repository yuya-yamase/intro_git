/* BswM_RequestModeFlsPrg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestModeFlsPrg/CODE                                 */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Rte.h>
#include <Sys.h>
#include <SchM_BswM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_FlsPrgNotReady (void);
static FUNC(void, BSWM_CODE_FAST) BswM_Act_FlsPrgReady (void);


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
/* Function Name | BswM_RequestMode_FlsPrg                                    */
/* Description   | Flash program mode request                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_FLS_PRG_NOTREADY                           */
/*               |       BSWM_MODE_FLS_PRG_READY                              */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_FlsPrg
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    if( Mode == BSWM_MODE_FLS_PRG_NOTREADY )
    {
        BswM_Act_FlsPrgNotReady();
    }
    else if( Mode == BSWM_MODE_FLS_PRG_READY )
    {
        BswM_Act_FlsPrgReady();
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQMODE_FLSPRG, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_FlsPrgNotReady                                    */
/* Description   | Action of the flash program mode control(Not ready)        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_FlsPrgNotReady (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.FlsPrg */

    if( BswM_CtrlReqMode.FlsPrg == BSWM_MODE_FLS_PRG_READY )
    {
        BswM_CtrlReqMode.FlsPrg = BSWM_MODE_FLS_PRG_NOTREADY;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.FlsPrg */

    if( UpdateFlg == (uint8)STD_ON )
    {
        SchM_Notification_FlsProgram(SCHM_FLS_PRG_NOTREADY);

        Rte_RpgEvtHk_RpgEvt_FlsPrgNotReady();
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_Act_FlsPrgReady                                       */
/* Description   | Action of the flash program mode control(Ready)            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_FlsPrgReady (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.FlsPrg */

    if( BswM_CtrlReqMode.FlsPrg == BSWM_MODE_FLS_PRG_NOTREADY )
    {
        BswM_CtrlReqMode.FlsPrg = BSWM_MODE_FLS_PRG_READY;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.FlsPrg */

    if( UpdateFlg == (uint8)STD_ON )
    {
        SchM_Notification_FlsProgram(SCHM_FLS_PRG_READY);

        Rte_RpgEvtHk_RpgEvt_FlsPrgReady();
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

