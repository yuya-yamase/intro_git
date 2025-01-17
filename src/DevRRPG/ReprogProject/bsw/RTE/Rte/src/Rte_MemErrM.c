/* Rte_MemErrM_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/MemErrM/CODE                                            */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Rte_MemErrM.h>


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
#define RTE_MEMERRM_START_SEC_VAR
#include <Rte_MemErrM_MemMap.h>

#define RTE_MEMERRM_STOP_SEC_VAR
#include <Rte_MemErrM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RTE_MEMERRM_START_SEC_CST
#include <Rte_MemErrM_MemMap.h>

#define RTE_MEMERRM_STOP_SEC_CST
#include <Rte_MemErrM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define RTE_MEMERRM_START_SEC_CODE
#include <Rte_MemErrM_MemMap.h>

/******************************************************************************/
/* Function Name | Rte_MemErrM_ClearErrorInfo                                 */
/* Description   | Wrapper of MemErrM_ClearErrorInfo()                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_MemErrM_ClearErrorInfo (void)
{
    MemErrM_ClearErrorInfo();

    return;
}

/******************************************************************************/
/* Function Name | Rte_MemErrM_CheckErrorInfo                                 */
/* Description   | Wrapper of MemErrM_CheckErrorInfo()                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | When the memory error occurred in Reprog targeting area,   */
/*               | this funciton clears the memory error information.         */
/*               | If user calls this function several times, keep the memory */
/*               | error information as necessary.                            */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_SLOW) Rte_MemErrM_CheckErrorInfo (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = MemErrM_CheckErrorInfo();

    return Ret;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define RTE_MEMERRM_STOP_SEC_CODE
#include <Rte_MemErrM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

