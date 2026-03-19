/**
 * @file
 ***********************************************************************************************
 * @brief MAC verification applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_MAC_VERIFY_H
#define ECY_HSM_APPLET_MAC_VERIFY_H

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
 * @brief Possible states for MAC verification applet
 *
 * @details
 * @section APPLET_MAC_VERIFY MAC verification applet
 *
 * @subsection APPLET_MAC_VERIFY_STATES Applet states
 *
 * @image html ./states_mac_verify.png "State diagram of applet: MAC verification" width=15cm
 * @image rtf  ./states_mac_verify.png "State diagram of applet: MAC verification" width=15cm
 */
typedef enum ecy_hsm_Applet_MacVerify_StateT
{
    ecy_hsm_APPLET_MACVERIFY_STATE_INIT_E,      /**< state for MAC verify init */
    ecy_hsm_APPLET_MACVERIFY_STATE_UPDATE_E,    /**< state for MAC verify update */
    ecy_hsm_APPLET_MACVERIFY_STATE_FINAL_E,     /**< state for MAC verify final */
    ecy_hsm_APPLET_MACVERIFY_STATE_FULL_E,      /**< state for full MAC verification */
    ecy_hsm_APPLET_MACVERIFY_STATE_BULK_E,      /**< state for bulk MAC verification */
    ecy_hsm_APPLET_MACVERIFY_STATE_BULKFAST_E,  /**< state for bulk MAC verification (improved interface) */
    ecy_hsm_APPLET_MACVERIFY_STATE_EXTENDED_E,  /**< state for extended MAC verification */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_MACVERIFY_NUMSTATES_E    /**< number of states */
} ecy_hsm_Applet_MacVerify_State_ten;
/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_MACVERIFY_STATE_INIT_E
 */
#define APPLET_MACVERIFY_STATE_INIT_E ecy_hsm_APPLET_MACVERIFY_STATE_INIT_E
/**
 * @deprecated by ecy_hsm_APPLET_MACVERIFY_STATE_UPDATE_E
 */
#define APPLET_MACVERIFY_STATE_UPDATE_E ecy_hsm_APPLET_MACVERIFY_STATE_UPDATE_E
/**
 * @deprecated by ecy_hsm_APPLET_MACVERIFY_STATE_FINAL_E
 */
#define APPLET_MACVERIFY_STATE_FINAL_E ecy_hsm_APPLET_MACVERIFY_STATE_FINAL_E
/**
 * @deprecated by ecy_hsm_APPLET_MACVERIFY_STATE_FULL_E
 */
#define APPLET_MACVERIFY_STATE_FULL_E ecy_hsm_APPLET_MACVERIFY_STATE_FULL_E
/**
 * @deprecated by ecy_hsm_APPLET_MACVERIFY_STATE_BULK_E
 */
#define APPLET_MACVERIFY_STATE_BULK_E ecy_hsm_APPLET_MACVERIFY_STATE_BULK_E
/**
 * @deprecated by ecy_hsm_APPLET_MACVERIFY_STATE_BULKFAST_E
 */
#define APPLET_MACVERIFY_STATE_BULKFAST_E ecy_hsm_APPLET_MACVERIFY_STATE_BULKFAST_E
/**
 * @deprecated by ecy_hsm_APPLET_MACVERIFY_NUMSTATES_E
 */
#define APPLET_MACVERIFY_NUMSTATES_E ecy_hsm_APPLET_MACVERIFY_NUMSTATES_E
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_MacVerify_State_ten
 */
#define Applet_MacVerify_State_ten ecy_hsm_Applet_MacVerify_State_ten
/**
 * @deprecated by ecy_hsm_Applet_MacVerify_StateT
 */
#define Applet_MacVerify_StateT ecy_hsm_Applet_MacVerify_StateT
/**
 * Applet context data for MAC verification applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_MacVerifyParamT Applet_MacVerifyCtx_tst;

/**
 * Applet context data for MAC verification applet for bulk function
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_BulkMacVerifyParamT Applet_MacVerifyBulkCtx_tst;

/**
 * Applet context data for MAC verification applet for bulk function
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_BulkMacFastVerParamT Applet_MacVerBulkFastCtx_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief MAC verify applet control structure
 */
extern const Applet_ts Applet_MacVerify_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_MAC_VERIFY_H
