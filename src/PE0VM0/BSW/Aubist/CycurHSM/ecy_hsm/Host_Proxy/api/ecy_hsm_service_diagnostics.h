/**
 * @file
 ***********************************************************************************************
 * @brief Functions Diagnostics
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2020, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_DIAGNOSTICS_H
#define ECY_HSM_SERVICE_DIAGNOSTICS_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_csai_diagnostics.h"

/**
 * @addtogroup GROUP_CSAI_DIAGNOSTICS
 * @{
 */

/** Minimum priority required by Diagnostics applet */
#define ecy_hsm_APPLET_DIAGNOSTICS_MIN_PRIVILEGE 0

/* *********** Deprecated Macro definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_DIAGNOSTICS_MIN_PRIVILEGE
 */
#define APPLET_DIAGNOSTICS_MIN_PRIVILEGE         ecy_hsm_APPLET_DIAGNOSTICS_MIN_PRIVILEGE

/*
**********************************************************************************************************************
* Type definitions
**********************************************************************************************************************
*/

/**
 * Applet parameter data for Diagnostics applet for HSM Dump Init
 */
typedef struct ecy_hsm_DiagnosticsDumpInitParamT
{
    void*                                pExtInfo;   /**< pointer to receive data in user specific structure     */
    ecy_hsm_Csai_DiagnosticsDumpUseCaseT useCaseId;  /**< To determine which HSM Dump use case is requested      */
    uint32*                              pImageSize; /**< Size of the Image                                      */
    uint32*                              pImageAddr; /**< Address of the Image                                   */
} ecy_hsm_DiagnosticsDumpInitParamT;

/**
 * Applet parameter data for Diagnostics applet for HSM Dump Update
 */
typedef struct ecy_hsm_DiagnosticsDumpUpdateParamT
{
    uint8*  pDumpBuffer;    /**< Pointer to start address of array block for the dump   */
    uint32  bufferSize;     /**< Length of block to be dumped                           */
    uint32* pBytesDumped;   /**< How many bytes are dumped by the HSM                   */
    uint32* pBytesLeftFlag; /**< Flag indicating if more bytes needed to be dumped      */
} ecy_hsm_DiagnosticsDumpUpdateParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_DiagnosticsDumpInitParamT
 */
#define HSM_DiagnosticsDumpInitParamT   ecy_hsm_DiagnosticsDumpInitParamT
/**
 * @deprecated by @ref ecy_hsm_DiagnosticsDumpUpdateParamT
 */
#define HSM_DiagnosticsDumpUpdateParamT ecy_hsm_DiagnosticsDumpUpdateParamT

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/
/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/**
 * @}
 */
#endif /* Multiple inclusion lock  */
