/* BswM_RequestModeSession_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestModeSession/CODE                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <BswM.h>
#include "BswM_Local.h"

#include <Rte.h>
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
static FUNC(void, BSWM_CODE_FAST) BswM_Act_SessionDef (void);
static FUNC(void, BSWM_CODE_FAST) BswM_Act_SessionExt (void);
static FUNC(void, BSWM_CODE_FAST) BswM_Act_SessionPrg (void);


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
/* Function Name | BswM_RequestMode_Session                                   */
/* Description   | Session mode request                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_SESSION_DEF                                */
/*               |       BSWM_MODE_SESSION_EXT                                */
/*               |       BSWM_MODE_SESSION_PRG                                */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Session
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    if( Mode == BSWM_MODE_SESSION_DEF )
    {
        BswM_Act_SessionDef();
    }
    else if( Mode == BSWM_MODE_SESSION_EXT )
    {
        BswM_Act_SessionExt();
    }
    else if( Mode == BSWM_MODE_SESSION_PRG )
    {
        BswM_Act_SessionPrg();
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQMODE_SESSION, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_SessionDef                                        */
/* Description   | Action of the session mode control(Default session)        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_SessionDef (void)
{
    BswM_CtrlReqMode.Session = BSWM_MODE_SESSION_DEF;

    Rte_RpgEvtHk_SessionEvt_Def();

    SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_SESSION, SUBMICONIF_MODE_SESSION_DEF);

    return;
}

/******************************************************************************/
/* Function Name | BswM_Act_SessionExt                                        */
/* Description   | Action of the session mode control                         */
/*               | (Extended diagnostic session)                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_SessionExt (void)
{
    BswM_CtrlReqMode.Session = BSWM_MODE_SESSION_EXT;

    Rte_RpgEvtHk_SessionEvt_Ext();

    SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_SESSION, SUBMICONIF_MODE_SESSION_EXT);

    return;
}

/******************************************************************************/
/* Function Name | BswM_Act_SessionPrg                                        */
/* Description   | Action of the session mode control(Programming session)    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_SessionPrg (void)
{
    BswM_CtrlReqMode.Session = BSWM_MODE_SESSION_PRG;

    Rte_RpgEvtHk_SessionEvt_Prg();

    SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_SESSION, SUBMICONIF_MODE_SESSION_PRG);

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

