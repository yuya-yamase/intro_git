/* BswM_RequestMode_Mmicon_Session_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestMode/Mmicon/Session/CODE                        */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <BswM.h>
#include "BswM_Local.h"

#include <Gdn.h>


#if (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)
/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_Mmicon_Session
(
    VAR(Gdn_Dcm_SesCtrlType, AUTOMATIC) DcmSession
);


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
/* Function Name | BswM_RequestMode_Mmicon_Session                            */
/* Description   | Session mode request                                       */
/*               | (Synchronous processing with the main micon)               */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_SESSION_DEF                                */
/*               |       BSWM_MODE_SESSION_EXT                                */
/*               |       BSWM_MODE_SESSION_PRG                                */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_SUB    */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Mmicon_Session
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    VAR(uint8, AUTOMATIC) ErrFlg;
    VAR(Gdn_Dcm_SesCtrlType, AUTOMATIC) DcmSession;

    ErrFlg = STD_OFF;

    if( Mode == BSWM_MODE_SESSION_DEF )
    {
        DcmSession = GDN_DCM_DEFAULT_SESSION;
    }
    else if( Mode == BSWM_MODE_SESSION_EXT )
    {
        DcmSession = GDN_DCM_EXTENDED_SESSION;
    }
    else if( Mode == BSWM_MODE_SESSION_PRG )
    {
        DcmSession = GDN_DCM_REPROG_SESSION;
    }
    else
    {
        ErrFlg = STD_ON;
    }

    if( ErrFlg == (uint8)STD_OFF )
    {
        BswM_Act_Mmicon_Session(DcmSession);
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQ_MMICON_SESSION, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_Mmicon_Session                                    */
/* Description   | Action of the session mode control                         */
/*               | (Synchronous processing with the main micon)               */
/* Preconditions |                                                            */
/* Parameters    | [IN] DcmSession : Session to notify Dcm                    */
/*               |       GDN_DCM_DEFAULT_SESSION                              */
/*               |       GDN_DCM_EXTENDED_SESSION                             */
/*               |       GDN_DCM_REPROG_SESSION                               */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_SUB    */
/*               | is defined.                                                */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_Mmicon_Session
(
    VAR(Gdn_Dcm_SesCtrlType, AUTOMATIC) DcmSession
)
{
    Gdn_Dcm_NotifyChangeSession(DcmSession);

    return;
}

#define BSWM_STOP_SEC_CODE
#include <BswM_MemMap.h>

#endif  /* (REPROG_CFG_SUBMICON_USE_SUB == STD_ON) */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

