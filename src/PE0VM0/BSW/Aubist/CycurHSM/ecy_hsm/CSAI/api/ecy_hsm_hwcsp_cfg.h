/**
 * @file
 ***********************************************************************************************
 * @brief This header file defines common structures and types of the HwCsp module.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2023, all rights reserved
 **********************************************************************************************/
/* [$Satisfies $COMPONENT HWCSP_Applet] */

#ifndef ECY_HSM_HWCSP_CFG_H
#define ECY_HSM_HWCSP_CFG_H

#if defined(GUAM)
# include "ecy_hsm_general.h"
#else
# include "ecy_hsm_general_pubcfg.h"
#endif

#if (ECY_HSM_VMS_FS_APPLETHWCSP == ENABLED)
# include "ecy_hsm_hwcsp_keystore_cfg_arch.h"
# include "Std_Types.h"

/** @brief Structure holding the table for host key handles and hardware key slots association.
 *  @note ecy_hsm_HwCspKeystore_KeyTableUnionT and ecy_hsm_HwCspKeystore_KeyTableVersionT are
 *        target dependent as each target might need different information to map a host key handle
 *        to a HwCsp slot.
 */
typedef struct ecy_hsm_HwCspKeystore_KeyTableTag
{
    ecy_hsm_HwCspKeystore_KeyTableVersionT version;       /**< Key table version identifier. */
    boolean                                isInitialized; /**< Flag to signal that the table is initialized. */
    ecy_hsm_HwCspKeystore_KeyTableUnionT   keyTable;      /**< Key table union containing different versions of the table. */
} ecy_hsm_HwCspKeystore_KeyTableT;

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
# define ECY_HSM_START_SEC_VAR_HWCSP_KEYSTORE_TABLE_UNSPECIFIED
# include "ecy_hsm_MemMap.h"

/** Shared table between Host and HSM to track the current state of the HwCsp's keystore.
 *  This table is used by the host sided HwCsp applets to translate host key handles to slots of the
 *  underlying hardware.
 */
extern volatile ecy_hsm_HwCspKeystore_KeyTableT ecy_hsm_HwCspKeystore_SharedTable;

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map variables to special memory sections */
# define ECY_HSM_STOP_SEC_VAR_HWCSP_KEYSTORE_TABLE_UNSPECIFIED
# include "ecy_hsm_MemMap.h"

#endif /* if (ECY_HSM_VMS_FS_APPLETHWCSP == ENABLED) */
#endif /* ECY_HSM_HWCSP_CFG_H */
