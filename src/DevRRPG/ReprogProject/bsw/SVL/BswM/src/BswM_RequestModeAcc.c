/* BswM_RequestModeAcc_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestModeAcc/CODE                                    */
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
static FUNC(void, BSWM_CODE_FAST) BswM_Act_AccOff (void);
static FUNC(void, BSWM_CODE_FAST) BswM_Act_AccOn (void);


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
/* Function Name | BswM_RequestMode_Acc                                       */
/* Description   | Acc mode request                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_ACC_OFF                                    */
/*               |       BSWM_MODE_ACC_ON                                     */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Acc
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    if( Mode == BSWM_MODE_ACC_OFF )
    {
        BswM_Act_AccOff();
    }
    else if( Mode == BSWM_MODE_ACC_ON )
    {
        BswM_Act_AccOn();
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQMODE_ACC, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_AccOff                                            */
/* Description   | Action of the acc mode control(Acc off)                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_AccOff (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.Acc */

    if( ( BswM_CtrlReqMode.Acc == BSWM_MODE_ACC_NONE ) ||
        ( BswM_CtrlReqMode.Acc == BSWM_MODE_ACC_ON ) )
    {
        BswM_CtrlReqMode.Acc = BSWM_MODE_ACC_OFF;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.Acc */

    if( UpdateFlg == (uint8)STD_ON )
    {
        Rte_RpgEvtHk_ModeEvt_AccOff();

        SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_ACC, SUBMICONIF_MODE_ACC_OFF);

        if( BswM_CfgPtr->AccIgActDataPtr->ActAcc != BSWM_SHUTDOWN_NONE )
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
/* Function Name | BswM_Act_AccOn                                             */
/* Description   | Action of the acc mode control(Acc on)                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_AccOn (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.Acc */

    if( BswM_CtrlReqMode.Acc == BSWM_MODE_ACC_NONE )
    {
        BswM_CtrlReqMode.Acc = BSWM_MODE_ACC_ON;
        UpdateFlg = STD_ON;
    }
    else if( BswM_CtrlReqMode.Acc == BSWM_MODE_ACC_OFF )
    {
        if( BswM_CfgPtr->AccIgActDataPtr->ActAcc == BSWM_SHUTDOWN_NONE )
        {
            BswM_CtrlReqMode.Acc = BSWM_MODE_ACC_ON;
            UpdateFlg = STD_ON;
        }
    }
    else
    {
        /* No process */
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.Acc */

    if( UpdateFlg == (uint8)STD_ON )
    {
        Rte_RpgEvtHk_ModeEvt_AccOn();

        SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_ACC, SUBMICONIF_MODE_ACC_ON);
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

