/**
 * @file
 ***********************************************************************************************
 * @brief Read and set Lifecycle applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_LIFECYCLE_H
#define ECY_HSM_APPLET_LIFECYCLE_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai_lifecycle.h"
#include "ecy_hsm_service.h"

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
 * Lifecycle states for applet
 */
typedef enum ecy_hsm_Applet_Lifecycle_StateT
{
    ecy_hsm_APPLET_LIFECYCLE_READ_STATE_E,   /**< lifecycle state */
    ecy_hsm_APPLET_LIFECYCLE_UPDATE_STATE_E, /**< lifecycle update request */
    ecy_hsm_APPLET_LIFECYCLE_NUMSTATES_E     /**< number of states */
} ecy_hsm_Applet_Lifecycle_StateT;

/**
 * Lifecycle states
 */
typedef enum ecy_hsm_Lifecycle_StateT
{
    ecy_hsm_LIFECYCLE_STATE_INIT_E,   /**< lifecycle init */
    ecy_hsm_LIFECYCLE_STATE_UPDATE_E, /**< lifecycle update */
    ecy_hsm_LIFECYCLE_STATE_FINAL_E,  /**< lifecycle final */
    ecy_hsm_LIFECYCLE_STATE_CANCEL_E, /**< lifecycle cancel */
    /* This needs to be the final entry */
    ecy_hsm_LIFECYCLE_STATE_NUMSTATES_E /**< number of states */
} ecy_hsm_Lifecycle_StateT;

/**
 * Applet parameter data for lifecycle applet
 */
typedef struct ecy_hsm_LifecycleParamT
{
    uint32  nextState; /**< next lifecycle state */
    uint32* pCurState; /**< current lifecycle state */
    uint32* pHwState;  /**< current hardware state */
} ecy_hsm_LifecycleParamT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_LIFECYCLE_READ_STATE_E
 */
#define APPLET_LIFECYCLE_READ_STATE_E   ecy_hsm_APPLET_LIFECYCLE_READ_STATE_E
/**
 * @deprecated by ecy_hsm_APPLET_LIFECYCLE_UPDATE_STATE_E
 */
#define APPLET_LIFECYCLE_UPDATE_STATE_E ecy_hsm_APPLET_LIFECYCLE_UPDATE_STATE_E
/**
 * @deprecated by ecy_hsm_APPLET_LIFECYCLE_NUMSTATES_E
 */
#define APPLET_LIFECYCLE_NUMSTATES_E    ecy_hsm_APPLET_LIFECYCLE_NUMSTATES_E
/**
 * @deprecated by ecy_hsm_LIFECYCLE_STATE_INIT_E
 */
#define LIFECYCLE_STATE_INIT_E          ecy_hsm_LIFECYCLE_STATE_INIT_E
/**
 * @deprecated by ecy_hsm_LIFECYCLE_STATE_UPDATE_E
 */
#define LIFECYCLE_STATE_UPDATE_E        ecy_hsm_LIFECYCLE_STATE_UPDATE_E
/**
 * @deprecated by ecy_hsm_LIFECYCLE_STATE_FINAL_E
 */
#define LIFECYCLE_STATE_FINAL_E         ecy_hsm_LIFECYCLE_STATE_FINAL_E
/**
 * @deprecated by ecy_hsm_LIFECYCLE_STATE_CANCEL_E
 */
#define LIFECYCLE_STATE_CANCEL_E        ecy_hsm_LIFECYCLE_STATE_CANCEL_E
/**
 * @deprecated by ecy_hsm_LIFECYCLE_STATE_NUMSTATES_E
 */
#define LIFECYCLE_STATE_NUMSTATES_E     ecy_hsm_LIFECYCLE_STATE_NUMSTATES_E
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_Lifecycle_StateT
 */
#define Applet_Lifecycle_StateT         ecy_hsm_Applet_Lifecycle_StateT
/**
 * @deprecated by ecy_hsm_Lifecycle_StateT
 */
#define Lifecycle_StateT                ecy_hsm_Lifecycle_StateT
/**
 * @deprecated by ecy_hsm_LifecycleParamT
 */
#define HSM_LifecycleParamT             ecy_hsm_LifecycleParamT
/**
 * Applet context data for lifecycle applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_LifecycleParamT Applet_LifecycleCtx_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief LIFECYCLE applet control structures
 */
extern const Applet_ts Applet_Lifecycle_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // _APPLET_LIFECYCLE_H_
