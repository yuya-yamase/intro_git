/**
 * @file
 ***********************************************************************************************
 * @brief Checksum calculation applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_CHKSUM_H
#define ECY_HSM_APPLET_CHKSUM_H

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
 * @brief Possible states for checksum applet
 *
 * @details
 * @section APPLET_CHECKSUM Checksum applet
 *
 * @image html ./states_chksum.png "State diagram of applet: Checksum calculation" width=15cm
 * @image rtf  ./states_chksum.png "State diagram of applet: Checksum calculation" width=15cm
 */
typedef enum ecy_hsm_Applet_Chksum_StateT
{
    ecy_hsm_APPLET_CHKSUM_STATE_INIT,  /**< Initialize checksum calculation */
    ecy_hsm_APPLET_CHKSUM_STATE_UPDATE,/**< Update checksum calculation with new data block */
    ecy_hsm_APPLET_CHKSUM_STATE_FINAL, /**< Finish checksum calculation */
    ecy_hsm_APPLET_CHKSUM_STATE_FULL,  /**< Perform full checksum calculation */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_CHKSUM_NUMSTATES    /**< Number of states */
} ecy_hsm_Applet_Chksum_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_CHKSUM_STATE_INIT
 */
#define APPLET_CHKSUM_STATE_INIT ecy_hsm_APPLET_CHKSUM_STATE_INIT
/**
 * @deprecated by @ref ecy_hsm_APPLET_CHKSUM_STATE_UPDATE
 */
#define APPLET_CHKSUM_STATE_UPDATE ecy_hsm_APPLET_CHKSUM_STATE_UPDATE
/**
 * @deprecated by @ref ecy_hsm_APPLET_CHKSUM_STATE_FINAL
 */
#define APPLET_CHKSUM_STATE_FINAL ecy_hsm_APPLET_CHKSUM_STATE_FINAL
/**
 * @deprecated by @ref ecy_hsm_APPLET_CHKSUM_STATE_FULL
 */
#define APPLET_CHKSUM_STATE_FULL ecy_hsm_APPLET_CHKSUM_STATE_FULL
/**
 * @deprecated by @ref ecy_hsm_APPLET_CHKSUM_NUMSTATES
 */
#define APPLET_CHKSUM_NUMSTATES ecy_hsm_APPLET_CHKSUM_NUMSTATES
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_Chksum_StateT
 */
#define Applet_Chksum_StateT ecy_hsm_Applet_Chksum_StateT

/**
 * Applet context data for checksum calculation
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_CheckSumParamT Applet_CheckSumCtx_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief Checksum applet control structures
 */
extern const Applet_ts Applet_ChkSum_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_CHKSUM_H
