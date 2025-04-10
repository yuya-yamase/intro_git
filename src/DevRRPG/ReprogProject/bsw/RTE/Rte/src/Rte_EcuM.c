/* Rte_EcuM_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/EcuM/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Rte_EcuM.h>


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
#define RTE_ECUM_START_SEC_VAR
#include <Rte_EcuM_MemMap.h>

#define RTE_ECUM_STOP_SEC_VAR
#include <Rte_EcuM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RTE_ECUM_START_SEC_CST
#include <Rte_EcuM_MemMap.h>

#define RTE_ECUM_STOP_SEC_CST
#include <Rte_EcuM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define RTE_ECUM_START_SEC_CODE
#include <Rte_EcuM_MemMap.h>

/******************************************************************************/
/* Function Name | Rte_EcuM_ReportError                                       */
/* Description   | Wrapper of EcuM_ReportError()                              */
/* Preconditions |                                                            */
/* Parameters    | [In] ErrorInfo : Error information                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_EcuM_ReportError
(
    P2CONST(Rte_EcuM_ErrorType, AUTOMATIC, RTE_APPL_CONST) ErrorInfo
)
{
    EcuM_ReportError(ErrorInfo);

    return;
}

/******************************************************************************/
/* Function Name | Rte_EcuM_GetBootMode                                       */
/* Description   | Wrapper of EcuM_GetBootMode()                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | boot mode                                                  */
/*               |  RTE_ECUM_START_AP_ENTRY                                   */
/*               |  RTE_ECUM_START_BOOT_ENTRY                                 */
/*               |  RTE_ECUM_START_BOOT_POSRES_ENTRY                          */
/*               |  RTE_ECUM_START_STAYINBOOT_ENTRY                           */
/* Notes         | - RTE_ECUM_START_BOOT_POSRES_ENTRY can be used when        */
/*               |   REPROG_CFG_POSRES_AFTER_RESET is STD_ON.                 */
/*               | - RTE_ECUM_START_STAYINBOOT_ENTRY can be used when         */
/*               |   REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                  */
/******************************************************************************/
FUNC(uint8, RTE_CODE_SLOW) Rte_EcuM_GetBootMode (void)
{
    VAR(uint8, AUTOMATIC) Mode;

    Mode = EcuM_GetBootMode();

    return Mode;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define RTE_ECUM_STOP_SEC_CODE
#include <Rte_EcuM_MemMap.h>

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

