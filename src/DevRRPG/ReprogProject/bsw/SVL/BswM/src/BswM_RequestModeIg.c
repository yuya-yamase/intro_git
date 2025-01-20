/* BswM_RequestModeIg_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestModeIg/CODE                                     */
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
static FUNC(void, BSWM_CODE_FAST) BswM_Act_IgOff (void);
static FUNC(void, BSWM_CODE_FAST) BswM_Act_IgOn (void);


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
/* Function Name | BswM_RequestMode_Ig                                        */
/* Description   | Ig mode request                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_IG_OFF                                     */
/*               |       BSWM_MODE_IG_ON                                      */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Ig
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    if( Mode == BSWM_MODE_IG_OFF )
    {
        BswM_Act_IgOff();
    }
    else if( Mode == BSWM_MODE_IG_ON )
    {
        BswM_Act_IgOn();
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQMODE_IG, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_IgOff                                             */
/* Description   | Action of the Ig mode control(Ig off)                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_IgOff (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.Ig */

    if( ( BswM_CtrlReqMode.Ig == BSWM_MODE_IG_NONE ) ||
        ( BswM_CtrlReqMode.Ig == BSWM_MODE_IG_ON ) )
    {
        BswM_CtrlReqMode.Ig = BSWM_MODE_IG_OFF;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.Ig */

    if( UpdateFlg == (uint8)STD_ON )
    {
        Rte_RpgEvtHk_ModeEvt_IgOff();

        SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_IG, SUBMICONIF_MODE_IG_OFF);

        if( BswM_CfgPtr->AccIgActDataPtr->ActIg != BSWM_SHUTDOWN_NONE )
        {
#if (REPROG_CFG_ETH_USE == STD_ON)
            BswM_RequestMode_EthSendRcv(BSWM_MODE_ETH_SENDRCV_WAITSTOP);
#else
            SchM_Finish_MainFunction();
#endif
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_Act_IgOn                                              */
/* Description   | Action of the Ig mode control(Ig on)                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_IgOn (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.Ig */

    if( BswM_CtrlReqMode.Ig == BSWM_MODE_IG_NONE )
    {
        BswM_CtrlReqMode.Ig = BSWM_MODE_IG_ON;
        UpdateFlg = STD_ON;
    }
    else if( BswM_CtrlReqMode.Ig == BSWM_MODE_IG_OFF )
    {
        if( BswM_CfgPtr->AccIgActDataPtr->ActIg == BSWM_SHUTDOWN_NONE )
        {
            BswM_CtrlReqMode.Ig = BSWM_MODE_IG_ON;
            UpdateFlg = STD_ON;
        }
    }
    else
    {
        /* No process */
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.Ig */

    if( UpdateFlg == (uint8)STD_ON )
    {
        Rte_RpgEvtHk_ModeEvt_IgOn();

        SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_IG, SUBMICONIF_MODE_IG_ON);
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

