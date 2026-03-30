/**
 * @file
 ***********************************************************************************************
 * @brief MAC generation applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_MAC_GEN_H
#define ECY_HSM_APPLET_MAC_GEN_H

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
 * @brief Possible states for MAC generation applet
 *
 * @details
 * @section APPLET_MAC_GEN MAC generation applet
 *
 * @subsection APPLET_MAC_GEN_STATES Applet states
 *
 * @image html ./states_mac_generate.png "State diagram of applet: MAC generation" width=15cm
 * @image rtf  ./states_mac_generate.png "State diagram of applet: MAC generation" width=15cm
 */
typedef enum ecy_hsm_Applet_MacGen_StateT
{
    ecy_hsm_APPLET_MACGEN_STATE_INIT_E,      /**< state for MAC generate init */
    ecy_hsm_APPLET_MACGEN_STATE_UPDATE_E,    /**< state for MAC generate update */
    ecy_hsm_APPLET_MACGEN_STATE_FINAL_E,     /**< state for MAC generate final */
    ecy_hsm_APPLET_MACGEN_STATE_FULL_E,      /**< state for full MAC generation */
    ecy_hsm_APPLET_MACGEN_STATE_BULK_E,      /**< state for bulk MAC generation */
    ecy_hsm_APPLET_MACGEN_STATE_BULKFAST_E,  /**< state for bulk MAC generation (improved interface) */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_MACGEN_NUMSTATES_E        /**< number of states */
} ecy_hsm_Applet_MacGen_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_MACGEN_STATE_INIT_E
 */
#define APPLET_MACGEN_STATE_INIT_E ecy_hsm_APPLET_MACGEN_STATE_INIT_E
/**
 * @deprecated by ecy_hsm_APPLET_MACGEN_STATE_UPDATE_E
 */
#define APPLET_MACGEN_STATE_UPDATE_E ecy_hsm_APPLET_MACGEN_STATE_UPDATE_E
/**
 * @deprecated by ecy_hsm_APPLET_MACGEN_STATE_FINAL_E
 */
#define APPLET_MACGEN_STATE_FINAL_E ecy_hsm_APPLET_MACGEN_STATE_FINAL_E
/**
 * @deprecated by ecy_hsm_APPLET_MACGEN_STATE_FULL_E
 */
#define APPLET_MACGEN_STATE_FULL_E ecy_hsm_APPLET_MACGEN_STATE_FULL_E
/**
 * @deprecated by ecy_hsm_APPLET_MACGEN_STATE_BULK_E
 */
#define APPLET_MACGEN_STATE_BULK_E ecy_hsm_APPLET_MACGEN_STATE_BULK_E
/**
 * @deprecated by ecy_hsm_APPLET_MACGEN_STATE_BULKFAST_E
 */
#define APPLET_MACGEN_STATE_BULKFAST_E ecy_hsm_APPLET_MACGEN_STATE_BULKFAST_E
/**
 * @deprecated by ecy_hsm_APPLET_MACGEN_NUMSTATES_E
 */
#define APPLET_MACGEN_NUMSTATES_E ecy_hsm_APPLET_MACGEN_NUMSTATES_E
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_MacGen_StateT
 */
#define Applet_MacGen_StateT ecy_hsm_Applet_MacGen_StateT
/**
 * Applet context data for MAC generation applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_MacGenerateParamT Applet_MacGenCtx_tst;

/**
 * Applet context data for MAC generation applet for bulk function
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_BulkMacGenerateParamT Applet_MacGenBulkCtx_tst;

/**
 * Applet context data for MAC generation applet for bulk function
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_BulkMacFastGenParamT Applet_MacGenBulkFastCtx_tst;
/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief MACGEN applet control structures
 */
extern const Applet_ts Applet_MacGen_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_MAC_GEN_H
