/**
 * @file
 ***********************************************************************************************
 * @brief Applet configuration interface
 * @details Interface for applet manager to:
 * - register a list of applets based on configuration
 * - select specified applet control data from this list
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_CFG_H
#define ECY_HSM_APPLET_CFG_H

/*
 * Includes
 */

#include "ecy_hsm_applet.h"

/**
 * @addtogroup APPLET_CONFIG
 * @{
 */
/*
 * type definitions
 */

/*
 * macros / defines
 */

/*
 * external declarations
 */
/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"
/**
 * @brief Indexed List of all registered applets
 *
 * This list contains a slot for each known applet in @ref Applet_Id.
 * If an applet is NOT registered, the corresponding slot contains a @c NULL_PTR.
 * @see Applet_Id
 */
extern Applet_ts const * const ecy_hsm_AppletList_cas[APPLET_ID_MAXNUM_APPLETS];

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"
/*
 * function prototypes & inlines
 */

/** @} */

#endif /* ECY_HSM_APPLET_CFG_H */
