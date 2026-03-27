/**
 * @file
 ***********************************************************************************************
 * @brief This header file defines CycurHSM system constants.
 * CycurHSM System Contants.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SESSIONS_PARAMS_H
#define ECY_HSM_SESSIONS_PARAMS_H

#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif

/* *** includes *******************************************************************************/

#if !defined(GUAM) || (BUILDING != HSM_BOOT_BUILD)
/* Session parameters for external/delivery builds or internal/GUAM-specific Host and HSM Core builds */
#include "ecy_hsm_sessions_params_core.h"
#else
/* Session parameters for internal/GUAM-specific HSM bootloader builds */
#include "ecy_hsm_sessions_params_boot.h"
#endif

#endif /* ECY_HSM_SESSIONS_PARAMS_H */
