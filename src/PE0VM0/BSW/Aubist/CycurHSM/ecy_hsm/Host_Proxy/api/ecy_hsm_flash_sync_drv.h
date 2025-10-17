/**
 * @file ecy_hsm_flash_sync_drv.h
 ***********************************************************************************************
 * @brief Flash sync driver adapter interface
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2020, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_FLASH_SYNC_DRV_H
#define ECY_HSM_FLASH_SYNC_DRV_H

/**
 * @addtogroup FLASH_SYNC_DRV
 * @{
 */

/* *** includes *******************************************************************************/
#include "Platform_Types.h"
#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif

/* Requires the definition of ENABLED/DISABLED, included above */
#if ( (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_RH850_V3_S4) || \
      (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_RH850_V3_S2) || \
      (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_CYPRESS) )
# define IS_FLASH_SYNC_REQUIRED             ENABLED         /**< Flash sync is required for this target */
#else
# define IS_FLASH_SYNC_REQUIRED             DISABLED        /**< Flash sync is not required for this target */
#endif

#if (IS_FLASH_SYNC_REQUIRED == ENABLED)
/* File only exists for certain architectures */
#include "ecy_hsm_flash_sync_mcal.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/


/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @brief Acquire the Flash Access for reading
 *
 * This function requests to change the Host Flash Access State to reading from C/D-Flash.
 *
 * @note This function is only implemented in HOST BUILD
 *
 * @param[in, out]    pParam                The Pointer is a reserved parameter for future configuration of the Interface. It will not be considered in this build.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS.                       The call succeeded. The Flash Access State changed.
 *   - @ref ecy_hsm_CSAI_ERR_INTERNAL_PARAM             Internal error occurred during flash access.
 *
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_FlashSyncDrv_HostRead ecy_hsm_FlashSyncMcal_HostRead


/**
 * @brief Acquire the Flash Access for writing
 *
 * This function requests to change the Host Flash Access State to writing to C/D-Flash.
 *
 * @note This function is only implemented in HOST BUILD
 *
 * @param[in, out]    pParam                The Pointer is a reserved parameter for future configuration of the Interface. It will not be considered in this build.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS.                       The call succeeded. The Flash Access State changed.
 *   - @ref ecy_hsm_CSAI_ERR_INTERNAL_PARAM             Internal error occurred during flash access.
 *
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_FlashSyncDrv_HostWrite ecy_hsm_FlashSyncMcal_HostWrite


/**
 * @brief Reseting the Flash Access to no-flash-access
 *
 * This function requests to change the Host Flash Access State to writing to C/D-Flash.
 *
 * @note This function is only implemented in HOST BUILD
 *
 * @param[in, out]    pParam                The Pointer is a reserved parameter for future configuration of the Interface. It will not be considered in this build.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS.                       The call succeeded. The Flash Access State changed.
 *   - @ref ecy_hsm_CSAI_ERR_INTERNAL_PARAM             Internal error occurred during flash access.
 *
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_FlashSyncDrv_HostEnd ecy_hsm_FlashSyncMcal_HostEnd

/* *INDENT-OFF* */
#ifdef __cplusplus
    } /* extern "C" */
#endif
/* *INDENT-ON* */

#endif /* IS_FLASH_SYNC_REQUIRED == ENABLED */

/**
 * @}
 */

#endif /* ECY_HSM_FLASH_SYNC_DRV_H */
