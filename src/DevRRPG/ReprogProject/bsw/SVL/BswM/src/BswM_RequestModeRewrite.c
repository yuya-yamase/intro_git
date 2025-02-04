/* BswM_RequestModeRewrite_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestModeRewrite/CODE                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Rte.h>
#include <Sys.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_RewriteStart (void);
static FUNC(void, BSWM_CODE_FAST) BswM_Act_RewriteFinish (void);


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
/* Function Name | BswM_RequestMode_Rewrite                                   */
/* Description   | Rewrite mode request                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_REWRITE_START                              */
/*               |       BSWM_MODE_REWRITE_FINISH                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Rewrite
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    if( Mode == BSWM_MODE_REWRITE_START )
    {
        BswM_Act_RewriteStart();
    }
    else if( Mode == BSWM_MODE_REWRITE_FINISH )
    {
        BswM_Act_RewriteFinish();
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQMODE_REWRITE, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_RewriteStart                                      */
/* Description   | Action of the Rewrite mode control(Start)                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_RewriteStart (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.Rewrite */

    if( ( BswM_CtrlReqMode.Rewrite == BSWM_MODE_REWRITE_NONE ) ||
        ( BswM_CtrlReqMode.Rewrite == BSWM_MODE_REWRITE_FINISH ) )
    {
        BswM_CtrlReqMode.Rewrite = BSWM_MODE_REWRITE_START;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.Rewrite */

    if( UpdateFlg == (uint8)STD_ON )
    {
        Rte_RpgEvtHk_RpgEvt_PreMemErase();
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_Act_RewriteFinish                                     */
/* Description   | Action of the Rewrite mode control(Finish)                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_RewriteFinish (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.Rewrite */

    if( BswM_CtrlReqMode.Rewrite == BSWM_MODE_REWRITE_START )
    {
        BswM_CtrlReqMode.Rewrite = BSWM_MODE_REWRITE_FINISH;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.Rewrite */

    if( UpdateFlg == (uint8)STD_ON )
    {
        Rte_RpgEvtHk_RpgEvt_PostPrgChk();
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

