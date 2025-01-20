/* MemErrM_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemErrM/CODE                                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <MemErrM.h>

#include <Ecc.h>
#include <Shutdown.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define MEMERRM_ECC_AREA_NONE   (0x00000000UL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define MEMERRM_START_SEC_VAR
#include <MemErrM_MemMap.h>


#define MEMERRM_STOP_SEC_VAR
#include <MemErrM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define MEMERRM_START_SEC_CST
#include <MemErrM_MemMap.h>


#define MEMERRM_STOP_SEC_CST
#include <MemErrM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define MEMERRM_START_SEC_CODE
#include <MemErrM_MemMap.h>

/******************************************************************************/
/* Function Name | MemErrM_Init                                               */
/* Description   | Initializes MemErrM                                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, MEMERRM_CODE_SLOW) MemErrM_Init (void)
{

    return;
}

/******************************************************************************/
/* Function Name | MemErrM_DeInit                                             */
/* Description   | Deinitializes MemErrM                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, MEMERRM_CODE_SLOW) MemErrM_DeInit (void)
{

    return;
}

/******************************************************************************/
/* Function Name | MemErrM_Time                                               */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, MEMERRM_CODE_SLOW) MemErrM_Time (void)
{
    VAR(uint32, AUTOMATIC) CheckResult;

    CheckResult = Ecc_CheckError();
    if( (CheckResult & (~ECC_AREA_USR)) != MEMERRM_ECC_AREA_NONE )
    {
        Shutdown_ResetMcuRam();
    }

    return;
}

/******************************************************************************/
/* Function Name | MemErrM_ClearErrorInfo                                     */
/* Description   | Clears the memory error information of Reprog targeting    */
/*               | area                                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, MEMERRM_CODE_SLOW) MemErrM_ClearErrorInfo (void)
{
    Ecc_ClearErrorInfo(ECC_AREA_USR);

    return;
}

/******************************************************************************/
/* Function Name | MemErrM_CheckErrorInfo                                     */
/* Description   | Checks whether the memory error occurred                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | When the memory error occurred in Reprog targeting area,   */
/*               | this funciton clears the memory error information.         */
/*               | If user calls this function several times, keep the memory */
/*               | error information as necessary.                            */
/******************************************************************************/
FUNC(Std_ReturnType, MEMERRM_CODE_SLOW) MemErrM_CheckErrorInfo (void)
{
    VAR(uint32, AUTOMATIC) CheckResult;
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    CheckResult = Ecc_CheckError();
    if( CheckResult != MEMERRM_ECC_AREA_NONE )
    {
        if( (CheckResult & (~ECC_AREA_USR)) != MEMERRM_ECC_AREA_NONE )
        {
            Shutdown_ResetMcuRam();
        }
        else
        {
            Ecc_ClearErrorInfo(ECC_AREA_USR);
        }
    }
    else
    {
        Result = E_OK;
    }

    return Result;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define MEMERRM_STOP_SEC_CODE
#include <MemErrM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

