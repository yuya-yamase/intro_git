/**
 * @file
 ***********************************************************************************************
 * @brief Header file for host side SHE private helper functions and data
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SHE_HOST_PRIVATE_H
#define ECY_HSM_SHE_HOST_PRIVATE_H

/**
 * @addtogroup GROUP_SHE_PRIVATE
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_service.h"
#include "ecy_hsm_applet_she.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
   extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/** Internal session handle used for all SHE jobs. */
extern ecy_hsm_Csai_SessionHandleT     SHE_Session;
#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)
/** This is an additional backup session handle for the hot swap concept that was introduced for SHE_CMD_CANCEL.
    If SHE_CMD_CANCEL is executed, it will swap SHE_Session and SHE_Session_backup. */
extern ecy_hsm_Csai_SessionHandleT     SHE_Session_backup;
/** This is an additional variable containing the priority information for the hot swap concept that was introduced for SHE_CMD_CANCEL.*/
extern ecy_hsm_Csai_JobPriorityT       SHE_Priority;
#endif

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_PTR
#include "ecy_hsm_MemMap.h"

/** Internal session status pointer used for SHE status queries. */
extern const volatile HSM_PortStatusT *pSHE_SessionStatus;

#if (ECY_HSM_VMS_FS_APPLET_SHE_CANCEL == ENABLED)

/** This is an additional status pointer for the backup session */
extern const volatile HSM_PortStatusT *pSHE_SessionStatus_backup;

#endif

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_PTR
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 2416]
 * [$Satisfies $ARCH 872]
 * Function to load an applet onto the HSM's SHE session
 *
 * @param[in] function       Applet function code
 * @param[in] paramBlockSize Size of the function parameter block
 * @param[in] pParamBlock    Pointer to parameter block
 *
 * @returns Error code or ERC_NO_ERROR
 */
extern SHE_ErrorCodeT SHE_LoadApplet( Applet_She_StateT function, uint32 paramBlockSize, void * const pParamBlock );

/**
 * Function to route a SHE request via the "Quick" path.
 *
 * @param[in] function       Applet function code
 * @param[in] paramBlockSize Size of the function parameter block
 * @param[in] pParamBlock    Pointer to parameter block
 *
 * @returns Error code returned from the HSM. This is the request error code.
 *  - @ref ecy_hsm_CSAI_SUCCESS                       The call succeeded without errors
 *  - @ref ecy_hsm_CSAI_ERR_QUICK_ROUTE_NOT_POSSIBLE  The HSM's internal state meant that the quick route could not be used
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE            An invalid session was used
 *  - @ref ecy_hsm_CSAI_ERR_HSM_SUSPENDED             The HSM is in suspended mode
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM             Invalid arguments (e.g. NULL_PTR)
 *  - @ref ecy_hsm_CSAI_ERR_INPUT_TOO_LARGE           paramBlockSize is bigger than HSM_OP_PARAM_BLOCK_SIZE
 *  - @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT              The HSM Proxy callouts have not been configured (the pointer is NULL_PTR)
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT                   An unexpected timeout occurred while trying to communicate with the HSM
 *  - else                                            Error code returned form Quick route call
 */
extern ecy_hsm_Csai_ErrorT SHE_QuickRoute(HSM_FunctionT function, uint32 paramBlockSize, void* const pParamBlock);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
   } /* extern "C" */
#endif
/* *INDENT-ON* */

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
