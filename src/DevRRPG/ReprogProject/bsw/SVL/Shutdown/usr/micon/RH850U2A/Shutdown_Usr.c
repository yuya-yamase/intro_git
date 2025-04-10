/* Shutdown_Usr_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Shutdown/Usr/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "Shutdown_Usr_Micon.h"


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
#define SHUTDOWN_START_SEC_VAR
#include <Shutdown_MemMap.h>

#define SHUTDOWN_STOP_SEC_VAR
#include <Shutdown_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SHUTDOWN_START_SEC_CST
#include <Shutdown_MemMap.h>

#define SHUTDOWN_STOP_SEC_CST
#include <Shutdown_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define SHUTDOWN_START_SEC_CODE
#include <Shutdown_MemMap.h>

/******************************************************************************/
/* Function Name | Shutdown_Usr_DeInitHw                                      */
/* Description   | Initialize hardware before shutdown for user custom        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function should initialize hardware to reset values   */
/*               | about resources which Startup_Usr_InitHw function changed. */
/******************************************************************************/
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_Usr_DeInitHw (void)
{

    return;
}

/******************************************************************************/
/* Function Name | Shutdown_Usr_RequestSubCore                                */
/* Description   | MainCore request SubCore to start shutdown process         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_Usr_RequestSubCore (void)
{

    return;
}

/******************************************************************************/
/* Function Name | Shutdown_Usr_WaitSubCore                                   */
/* Description   | MainCore wait for SubCore to finish shutdown process       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_Usr_WaitSubCore (void)
{

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define SHUTDOWN_STOP_SEC_CODE
#include <Shutdown_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

