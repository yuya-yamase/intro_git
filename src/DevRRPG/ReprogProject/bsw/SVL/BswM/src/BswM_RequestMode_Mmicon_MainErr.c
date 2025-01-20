/* BswM_RequestMode_Mmicon_MainErr_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/RequestMode/Mmicon/MainErr/CODE                        */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Sys.h>
#include <SchM_BswM.h>

#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
#include <SchM.h>
#endif


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
static FUNC(void, BSWM_CODE_FAST) BswM_Act_Mmicon_MainErrOccur (void);


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
/* Function Name | BswM_RequestMode_Mmicon_MainErr                            */
/* Description   | Main micon error mode request                              */
/*               | (Synchronous processing with the main micon)               */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : The requested mode                             */
/*               |       BSWM_MODE_MAIN_ERR_OCCUR                             */
/*               |       ~BSWM_MODE_MAIN_ERR_OCCUR                            */
/* Return Value  | None                                                       */
/* Notes         | - This function is valid when REPROG_CFG_SUBMICON_USE_SUB  */
/*               |   is defined.                                              */
/*               | - ~BSWM_MODE_MAIN_ERR_OCCUR can be used when               */
/*               |   REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                  */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_RequestMode_Mmicon_MainErr
(
    VAR(BswM_ModeType, AUTOMATIC) Mode
)
{
    if( Mode == BSWM_MODE_MAIN_ERR_OCCUR )
    {
        BswM_Act_Mmicon_MainErrOccur();
    }
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
    else if( Mode == (BswM_ModeType)~BSWM_MODE_MAIN_ERR_OCCUR )
    {
        /* Even if this function call returned with E_NOT_OK, nothing to do. */
        (void)SchM_SetStayInBootState(SCHM_STATE_STAYINBOOT_TMO);

        BswM_Act_Mmicon_MainErrOccur();
    }
#endif
    else
    {
        BswM_ReportError(BSWM_API_ID_REQ_MMICON_MAINERR, BSWM_E_REQ_MODE_OUT_OF_RANGE);
    }

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_Act_Mmicon_MainErrOccur                               */
/* Description   | Action of the main micon mode control                      */
/*               | (Synchronous processing with the main micon)               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_SUB    */
/*               | is defined.                                                */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_Act_Mmicon_MainErrOccur (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

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
        SchM_Finish_MainFunction();
    }

    return;
}

#define BSWM_STOP_SEC2_CODE
#include <BswM_MemMap.h>

#endif  /* (REPROG_CFG_SUBMICON_USE_SUB == STD_ON) */

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

