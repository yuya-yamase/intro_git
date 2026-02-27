/**
 * @file
 ***********************************************************************************************
 * @brief CSAI type definitions.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * general types used within other parts of the interface.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_H
#define ECY_HSM_CSAI_H

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * @addtogroup GROUP_CSAI_TYPES
 * @{
 */

/* *** includes *******************************************************************************/

#include "Std_Types.h"
#include "ecy_hsm_csai_defs.h"
#include "ecy_hsm_csai_error.h"
#include "ecy_hsm_csai_job.h"
#include "ecy_hsm_csai_types.h"
#include "ecy_hsm_csai_session.h"
#if defined(GUAM)
#include "ecy_hsm_general.h"
#endif /* #if defined(GUAM) */

/** Macro for unused parameter in a function */
#define CSAI_PARAM_UNUSED(x) ((void)(x))

#ifdef QACCHECK
#pragma PRQA_MACRO_MESSAGES_OFF "CSAI_PARAM_UNUSED"
/* Justification: QA-C does not understand CSAI_PARAM_UNUSED(x) whereas (void)x is OK */
#endif

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
