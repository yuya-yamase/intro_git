/**
 * @file ecy_hsm_host_storage_internal.h
 ***********************************************************************************************
 * @brief This header file helper functions for internal use only on the host side implementation
 *        of CycurHSM.
 *
 * @remarks The types and functions declared here are not intended for the public API, but are
 *          required by to support the functionality of this module
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2019, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_HOST_STORAGE_INTERNAL_H
#define ECY_HSM_HOST_STORAGE_INTERNAL_H

/**
 * @addtogroup GROUP_HSM_HOST_STORAGE_INTERNAL
 * @{
 */

/* *** includes *******************************************************************************/
#include "Std_Types.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_vms_pub_hoststorage.h"
#include "ecy_hsm_host_storage_config.h"
#include "ecy_hsm_service.h"

/* *** defines ********************************************************************************/

#if defined(GUAM)

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_8
#include "ecy_hsm_MemMap.h"

extern boolean HSM_HostStorage_InitTriggered;
extern uint8 HSM_HostStorage_sectionInitStatus[HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS];

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_8
#include "ecy_hsm_MemMap.h"

#endif

/* *** function prototypes ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-ON* */
/**
 * @brief Accessor function to get the address of the host storage cache within shared memory.
 *
 * @return      volatile* ecy_hsm_HostStorage_GetCachePtr       Pointer to the host storage cache
 */
volatile HSM_HostStorageCacheT* ecy_hsm_HostStorage_GetCachePtr(void);

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
