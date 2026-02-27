/**
 * @file
 *  ********************************************************************************************
 * @brief Diagnostics applet
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2020, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_DIAGNOSTICS_H
#define ECY_HSM_APPLET_DIAGNOSTICS_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"

/**
 * @addtogroup APPLET_IMPL
 * @{
 */
/*
**********************************************************************************************************************
* Type definitions
**********************************************************************************************************************
*/
/**
 * @brief Possible states for Diagnostics applet
 * @details
 * @section APPLET_DIAGNOSTICS HSM Diagnostics applet
 *
 * @subsection APPLET_DIAGNOSTICS_STATES Applet states
 *
 */
typedef enum ecy_hsm_Applet_Diagnostics_StateT
{
    ecy_hsm_APPLET_DIAGNOSTICS_STATE_DUMP_INIT_E,   /**< state for Diagnostics - HSM dump init */
    ecy_hsm_APPLET_DIAGNOSTICS_STATE_DUMP_UPDATE_E, /**< state for Diagnostics - HSM dump update */
    ecy_hsm_APPLET_DIAGNOSTICS_STATE_DUMP_FINAL_E,  /**< state for Diagnostics - HSM dump finalize */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_DIAGNOSTICS_NUMSTATES_E /**< number of states */
} ecy_hsm_Applet_Diagnostics_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_DIAGNOSTICS_STATE_DUMP_INIT_E
 */
#define APPLET_DIAGNOSTICS_STATE_DUMP_INIT_E   ecy_hsm_APPLET_DIAGNOSTICS_STATE_DUMP_INIT_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_DIAGNOSTICS_STATE_DUMP_UPDATE_E
 */
#define APPLET_DIAGNOSTICS_STATE_DUMP_UPDATE_E ecy_hsm_APPLET_DIAGNOSTICS_STATE_DUMP_UPDATE_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_DIAGNOSTICS_STATE_DUMP_FINAL_E
 */
#define APPLET_DIAGNOSTICS_STATE_DUMP_FINAL_E  ecy_hsm_APPLET_DIAGNOSTICS_STATE_DUMP_FINAL_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_DIAGNOSTICS_NUMSTATES_E
 */
#define APPLET_DIAGNOSTICS_NUMSTATES_E         ecy_hsm_APPLET_DIAGNOSTICS_NUMSTATES_E
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_Diagnostics_StateT
 */
#define Applet_Diagnostics_StateT              ecy_hsm_Applet_Diagnostics_StateT

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief Diagnostics applet control structures
 */
extern const Applet_ts Applet_Diagnostics_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif /* ECY_HSM_APPLET_DIAGNOSTICS_H */
