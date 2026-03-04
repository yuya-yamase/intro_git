/**
 * @file
 ***********************************************************************************************
 * @brief HwCsp applet header
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2023, all rights reserved.
 **********************************************************************************************/
/* [$Satisfies $COMPONENT HWCSP_Applet] */

#ifndef ECY_HSM_APPLET_HWCSP_H
#define ECY_HSM_APPLET_HWCSP_H
#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai_hwcsp.h"
/**
 * @addtogroup APPLET_HWCSP
 * @{
 */

/**
 * @brief Possible states for HwCsp applet
 *
 * @section APPLET_HWCSP HwCsp Applet
 *
 * @subsection APPLET_HWCSP_STATES Applet states
 *
 */
typedef enum ecy_hsm_Applet_HwCsp_StateT
{
    ecy_hsm_APPLET_HWCSP_FUNC_LOAD_KEY,    /*!< CSAI load key from host to the HwCsp's keystore */
    ecy_hsm_APPLET_HWCSP_FUNC_RELEASE_KEY, /*!< CSAI release key from the the HwCsp's keystore */
    ecy_hsm_APPLET_HWCSP_FUNC_INIT,        /*!< CSAI init HwCsp module */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_HWCSP_NUMSTATES /*!< number of states */
} ecy_hsm_Applet_HwCsp_StateT;

/** Parameter struct for the ecy_hsm_Csai_HwCsp_Init applet function.*/
typedef struct ecy_hsm_Applet_HwCsp_Init_ParametersTag
{
    volatile void*                              pSharedTable; /**< Pointer to shared table. */
    uint32                                      size;         /**< Size of shared table. */
    ecy_hsm_Csai_HwCsp_Init_ParamSetAndVersionT params;       /**< The parameter struct. */
} ecy_hsm_Applet_HwCsp_Init_ParametersT;

/**
 * Applet context data for HwCsp testing applet
 * @ingroup APPLET_CONTEXT
 */

/*
************************************************************************************************
* Extern declarations
************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief HwCsp applet control structure.
 */
extern const Applet_ts Applet_HwCsp_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif
