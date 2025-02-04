/* BswM_RequestModeMainErr_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestModeMainErr/CODE                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Sys.h>
#include <SubMiconIf.h>

#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
#include <SchM.h>
#endif


#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_MainErrOccur (void);


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
/* Function Name | BswM_RequestMode_MainErr                                   */
/* Description   | Main micon error mode request                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_MAIN_ERR_OCCUR                             */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when either of the following is     */
/*               | defined.                                                   */
/*               |  * REPROG_CFG_SUBMICON_NOUSE                               */
/*               |  * REPROG_CFG_SUBMICON_USE_MAIN                            */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_MainErr
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    if( Mode == BSWM_MODE_MAIN_ERR_OCCUR )
    {
        BswM_Act_MainErrOccur();
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_REQMODE_MAINERR, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_MainErrOccur                                      */
/* Description   | Action of the main micon error mode control(occur)         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when either of the following is     */
/*               | defined.                                                   */
/*               |  * REPROG_CFG_SUBMICON_NOUSE                               */
/*               |  * REPROG_CFG_SUBMICON_USE_MAIN                            */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_MainErrOccur (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
    VAR(uint8, AUTOMATIC) State;
#endif

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CtrlReqMode.MainErr */

    if( BswM_CtrlReqMode.MainErr == BSWM_MODE_MAIN_ERR_NONE )
    {
        BswM_CtrlReqMode.MainErr = BSWM_MODE_MAIN_ERR_OCCUR;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CtrlReqMode.MainErr */

    if( UpdateFlg == (uint8)STD_ON )
    {
#if (REPROG_CFG_STAYINBOOT_ENABLE != STD_ON)
        SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_MAIN_ERR, SUBMICONIF_MODE_MAIN_ERR_OCCUR);
#else
        State = SchM_GetStayInBootState();
        if( State == SCHM_STATE_STAYINBOOT_TMO )
        {
            SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_MAIN_ERR, (uint16)~SUBMICONIF_MODE_MAIN_ERR_OCCUR);
        }
        else
        {
            SubMiconIf_Main_NotifyEvent(SUBMICONIF_USER_BSWM_MAIN_ERR, SUBMICONIF_MODE_MAIN_ERR_OCCUR);
        }
#endif
    }

    return;
}

#define BSWM_STOP_SEC_CODE
#include <BswM_MemMap.h>

#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

