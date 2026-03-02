/**
 * @file ecy_hsm_flash_sync.h
 ***********************************************************************************************
 * @brief CSAI flash_sync operations
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for secure flash programming
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2020, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_FLASH_SYNC_H
#define ECY_HSM_FLASH_SYNC_H

/* *** includes *******************************************************************************/
#include "Std_Types.h"
#include "Platform_Types.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_service.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @addtogroup GROUP_HSM_FLASH_SYNC
 * @{
 * functions for handling the hardware flash sync
 */
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 1458]
 * @brief Acquire the Flash Access for reading
 *
 * This function requests to change the Host Flash Access State to Reading from C/D-Flash.
 * On certain controllers the Flash access must be synchronized with the other cores and the HSM-Core.
 * This interface changes the Host Flash Access State and communicates it to the other cores.
 * [$Satisfies $SW_ARCH 900][$Satisfies $SW_ARCH 901]
 *
 * @param[in, out]    pParam                The Pointer is a reserved parameter for future configuration of the Interface. It will not be considered in this build.
 * @param[in]         timeout_ms            Timeout definition for setting new state.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS.                       The call succeeded. The Flash Access State changed.
 *   - @ref ecy_hsm_CSAI_ERR_TIMEOUT                    The provided timeout has expired.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given function is not supported by this HSM build
 *
 * @note
 * On Renesas F1KM target: The flash access must be synchronized with other cores, since there is only one flash controller on the target.
 * If a core writes on the flash then the other cores are not allowed to read or write from flash.
 * Parallel C/D-Flash read  from different cores is supported.
 */
ecy_hsm_Csai_ErrorT ecy_hsm_Csai_FlashSync_HostRead(void *pParam,
                                                    uint32 timeout_ms);


/**
 * [$DD 1459]
 * @brief Acquire the Flash Access for writing
 *
 * This function requests to change the Host Flash Access State to writing to C/D-Flash.
 * On certain controllers the Flash access must be synchronized with the other cores and the HSM-Core.
 * This interface changes the Host Flash Access State and communicates it to the other cores.
 * [$Satisfies $SW_ARCH 900][$Satisfies $SW_ARCH 901][$Satisfies $SW_ARCH 902]
 *
 * @param[in, out]    pParam                The Pointer is a reserved parameter for future configuration of the Interface. It will not be considered in this build.
 * @param[in]         timeout_ms            Timeout definition for setting new state.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS.                       The call succeeded. The Flash Access State changed.
 *   - @ref ecy_hsm_CSAI_ERR_TIMEOUT                    The provided timeout has expired.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given function is not supported by this HSM build
 *
 * @note
 * On Renesas F1KM target: The flash access must be synchronized with other cores, since there is only one flash controller on the target.
 * If a core writes on the flash then the other cores are not allowed to read or write from flash.
 * Parallel C/D-Flash read  from different cores is supported.
 */
ecy_hsm_Csai_ErrorT ecy_hsm_Csai_FlashSync_HostWrite(void *pParam,
                                                     uint32 timeout_ms);

/**
 * [$DD 1460]
 * @brief Reset the Flash Access
 *
 * This function requests to change the Host Flash Access State to no operation to C/D-Flash.
 * On certain controllers the Flash access must be synchronized with the other cores and the HSM-Core.
 * This interface changes the Host Flash Access State and communicates it to the other cores.
 * [$Satisfies $SW_ARCH 900][$Satisfies $SW_ARCH 901]
 *
 * @param[in, out]    pParam                The Pointer is a reserved parameter for future configuration of the Interface. It will not be considered in this build.
 * @param[in]         timeout_ms            Timeout definition for setting new state.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS.                       The call succeeded. The Flash Access State changed.
 *   - @ref ecy_hsm_CSAI_ERR_TIMEOUT                    The provided timeout has expired.
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given function is not supported by this HSM build
 *
 * @note
 * On Renesas F1KM target: The flash access must be synchronized with other cores, since there is only one flash controller on the target.
 * If a core writes on the flash then the other cores are not allowed to read or write from flash.
 * Parallel C/D-Flash read  from different cores is supported.
 */
ecy_hsm_Csai_ErrorT ecy_hsm_Csai_FlashSync_HostEnd(void *pParam,
                                                   uint32 timeout_ms);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    } /* extern "C" */
#endif
/* *INDENT-ON* */

/** @} */ // GROUP_HSM_FLASH_SYNC
#endif /* ECY_HSM_FLASH_SYNC_H */
