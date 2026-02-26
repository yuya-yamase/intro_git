/**
 * @file ecy_hsm_applet_manager.h
 ***********************************************************************************************
 * @brief Applet manager Interface
 * @details Applet manager handles user job requests using applet controls
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_MANAGER_H
#define ECY_HSM_APPLET_MANAGER_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */

#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai_types.h"
#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "Platform_Types.h"

/**
 * @addtogroup APPLET_MANAGER
 * @{
 */

/*
 **********************************************************************************************************************
 * Defines / Macros
 **********************************************************************************************************************
 */

/* check first in we are in guam environment */
#if (defined(GUAM))

/* BUILDING macro only exists in GUAM environment */
#if (BUILDING == HSM_BOOT_BUILD)
#include "boot_bridge.h"
#define Applet_RelocOffset( _typ, _adr ) ((_typ)(RELOC_FUNCPTR_ADDR(_adr)))
#else
#define Applet_RelocOffset( _typ, _adr ) (_adr)
#endif //#if (BUILDING == HSM_BOOT_BUILD)

#else
#define Applet_RelocOffset( _typ, _adr ) (_adr)
#endif //#if (defined(GUAM))

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 974]
 * Generic applet priority check
 * checks if the requested priority is within allowed priorities which may be used
 * for applet execution
 * [$Satisfies $ARCH 245] [$Satisfies $ARCH 224] [$Satisfies $ARCH 249] [$Satisfies $ARCH 313]
 *
 * @param pPriority Pointer to the requested priority
 * @param appFunc requested function/state of the applet
 * @param paramBlock Operation parameters block
 *
 * @return
 *      ecy_hsm_CSAI_SUCCESS                  if requested priority OK
 *      ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED      if applet not found
 *      ecy_hsm_CSAI_ERR_PRIORITY_NOT_ALLOWED if requested priority is not supported by applet or function
 */
Applet_ErrorStateT Applet_isPriorityOk(ecy_hsm_Csai_JobPriorityT *pPriority, Applet_FunctionT appFunc, const uint8 *paramBlock);

/**
 * [$DD 975]
 * Generic applet option check
 * checks if the requested option is allowed or not
 * [$Satisfies $ARCH 245]
 *
 * @param option requested option
 * @param appFunc requested function/state of the applet
 * @param sessionId Session of the actual applet
 *
 * @return
 *      ecy_hsm_CSAI_SUCCESS               if requested option OK
 *      ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED   if applet not found
 *      ecy_hsm_CSAI_ERR_INSTANCE_EXCEEDED if multi-instance option is not supported by applet or function
 */
Applet_ErrorStateT Applet_isOptionOk( Applet_Option_IdT option,
                                      Applet_FunctionT appFunc,
                                      ecy_hsm_Csai_SessionHandleT sessionId );
/**
 * [$DD 976]
 * @brief Schedule an applet operation
 * [$Satisfies $ARCH 245]
 * [$Satisfies $ARCH 263]
 * [$Satisfies $ARCH 280]
 * [$Satisfies $ARCH 281]
 * [$Satisfies $ARCH 283]
 * [$Satisfies $ARCH 284]
 * [$Satisfies $ARCH 282]
 * [$Satisfies $ARCH 287]
 * [$Satisfies $ARCH 285]
 * [$Satisfies $ARCH 286]
 * [$Satisfies $SW_ARCH 1221]
 * [$Satisfies $ARCH 222]
 * [$Satisfies $ARCH 223]
 * [$Satisfies $ARCH 249]
 * [$Satisfies $ARCH 230]
 * [$Satisfies $ARCH 231]
 * [$Satisfies $ARCH 225]
 * [$Satisfies $ARCH 228]
 * [$Satisfies $ARCH 229]
 * [$Satisfies $ARCH 226]
 * [$Satisfies $ARCH 227]
 * [$Satisfies $ARCH 250]
 * [$Satisfies $ARCH 307]
 * @param hSession Session to schedule the operation on (reference to applet context)
 * @param priority Priority for the job
 * @param appFunc Operation function code
 * @param paramBlockSize Size of the operation parameters block
 * @param pParamBlock Operation parameters block
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS.                The call succeeded. The operation is scheduled on the HSM.
 *  - @ref ecy_hsm_CSAI_FC_BUSY.                Another job is still pending completion in this session.
 *                                              Either finish the previous job or cancel the running job using @ref ecy_hsm_Csai_CancelJob.
 *                                              hJob will contain the value CSAI_INVALID_JOB_HANDLE.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE.     The parameter is not a valid handle or the used handle has the wrong type.
 */
Applet_ReturnTypeT Applet_Function( Applet_SessionT            hSession,
                                    ecy_hsm_Csai_JobPriorityT  priority,
                                    Applet_FunctionT           appFunc,
                                    uint32                     paramBlockSize,
                                    void * const               pParamBlock );


/**
 * Get the status of the specified operation/job, it is one of type @ref HSM_PortStatusT.
 * Also get the error code of the last operation, if that operation has just completed
 * (if *pStatus == @ref HSM_STATUS_COMPLETE)
 * @details This function will return HSM_STATUS_COMPLETE and the operation error code only once, after which the
 *          operation is considered complete, the port status becomes HSM_STATUS_IDLE and the error code is cleared to
 *          @ref ecy_hsm_CSAI_SUCCESS
 *
 * @param hSession Session to check job status
 *
 * @returns Error status code returned from the HSM,
 *          unless some parameter of the call is invalid in which case the error code indicates that
 */
Applet_ReturnTypeT Applet_GetOpStatus( Applet_SessionT  hSession );

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
 */   // APPLET_MANAGER

#endif /* ECY_HSM_APPLET_MANAGER_H */
