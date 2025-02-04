/* Rte_BswM_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/BswM/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Rte_BswM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define RTE_BSWM_START_SEC_VAR
#include <Rte_BswM_MemMap.h>

#define RTE_BSWM_STOP_SEC_VAR
#include <Rte_BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RTE_BSWM_START_SEC_CST
#include <Rte_BswM_MemMap.h>

#define RTE_BSWM_STOP_SEC_CST
#include <Rte_BswM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define RTE_BSWM_START_SEC_CODE
#include <Rte_BswM_MemMap.h>

/******************************************************************************/
/* Function Name | Rte_BswM_Switch_RpgEvtHkUsrReset                           */
/* Description   | Wrapper of BswM_RequestMode()                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : Reset mode                                     */
/*               |       RTE_BSWM_MODE_USR_RESET_EXECUTE                      */
/* Return Value  | None                                                       */
/* Notes         | Call this function between RpgEvtHk_SchEvt_InitLast() and  */
/*               | RpgEvtHk_SchEvt_DeInitFirst().                             */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_BswM_Switch_RpgEvtHkUsrReset
(
    VAR(uint16, AUTOMATIC) Mode
)
{
    BswM_RequestMode(BSWM_USER_RTE_USR_RESET, (BswM_ModeType)Mode);

    return;
}

#if 0   /* Nbr1503(SleepAPI) */
/******************************************************************************/
/* Function Name | Rte_BswM_Switch_RpgEvtHkUsrSleep                           */
/* Description   | Wrapper of BswM_RequestMode()                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : Sleep mode                                     */
/*               |       RTE_BSWM_MODE_USR_SLEEP_EXECUTE                      */
/* Return Value  | None                                                       */
/* Notes         | Call this function between RpgEvtHk_SchEvt_InitLast() and  */
/*               | RpgEvtHk_SchEvt_DeInitFirst().                             */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_BswM_Switch_RpgEvtHkUsrSleep
(
    VAR(uint16, AUTOMATIC) Mode
)
{
    BswM_RequestMode(BSWM_USER_RTE_USR_SLEEP, (BswM_ModeType)Mode);

    return;
}
#endif

/******************************************************************************/
/* Function Name | Rte_BswM_Switch_VehInfAccControl                           */
/* Description   | Wrapper of BswM_RequestMode()                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : ACC mode                                       */
/*               |       RTE_BSWM_MODE_ACC_OFF                                */
/*               |       RTE_BSWM_MODE_ACC_ON                                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_BswM_Switch_VehInfAccControl
(
    VAR(uint16, AUTOMATIC) Mode
)
{
    BswM_RequestMode(BSWM_USER_RTE_ACC, (BswM_ModeType)Mode);

    return;
}

/******************************************************************************/
/* Function Name | Rte_BswM_Switch_VehInfIgControl                            */
/* Description   | Wrapper of BswM_RequestMode()                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : IG mode                                        */
/*               |       RTE_BSWM_MODE_IG_OFF                                 */
/*               |       RTE_BSWM_MODE_IG_ON                                  */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_BswM_Switch_VehInfIgControl
(
    VAR(uint16, AUTOMATIC) Mode
)
{
    BswM_RequestMode(BSWM_USER_RTE_IG, (BswM_ModeType)Mode);

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define RTE_BSWM_STOP_SEC_CODE
#include <Rte_BswM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

