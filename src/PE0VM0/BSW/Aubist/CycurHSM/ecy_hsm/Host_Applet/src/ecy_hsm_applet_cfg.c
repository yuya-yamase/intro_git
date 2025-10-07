/**********************************************************************************************************************
 * @file
 * Applet configuration framework for HOST
 *********************************************************************************************************************/

/***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/**********************************************************************************************************************
 * Includes
 *********************************************************************************************************************/

#include "ecy_hsm_applet_cfg.h"

/**********************************************************************************************************************
 * Variables
 *********************************************************************************************************************/
/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* Indexed List of all registered applets */
Applet_ts const * const ecy_hsm_AppletList_cas[APPLET_ID_MAXNUM_APPLETS] =
{
     // no host applets
     NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR // 5
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR // 10
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR // 15
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR // 20
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR // 25
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR // 30
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR
    ,NULL_PTR // 35
    ,NULL_PTR
};
/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"
