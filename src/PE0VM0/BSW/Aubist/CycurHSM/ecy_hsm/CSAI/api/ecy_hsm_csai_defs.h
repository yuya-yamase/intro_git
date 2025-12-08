/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Definitions.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * general preprocessor definitions used throughout the interface.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

/* PRQA S 0883 EOF */ /* <Deviation: dir_4.10_0883 */
#ifndef ECY_HSM_CSAI_DEFS_H
#define ECY_HSM_CSAI_DEFS_H

/* *** includes *******************************************************************************/
  /* To avoid the Guam specific file includes*/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif

/* *** defines ********************************************************************************/

/**
 * @addtogroup GROUP_CSAI_DEFS
 * @{
 */

#if ecy_hsm_CSAI_BUILD_TYPE == APP
#   ifndef ecy_hsm_CSAI_DECLSPEC
    /** Define the C declaration specifier to use */
#       define ecy_hsm_CSAI_DECLSPEC extern
#   endif
#   ifndef ecy_hsm_CSAI_CALL
    /** Define the C call semantic to use */
#       define ecy_hsm_CSAI_CALL
#   endif
#endif

#if ecy_hsm_CSAI_BUILD_TYPE == LIB
#   ifndef ecy_hsm_CSAI_DECLSPEC
#       define ecy_hsm_CSAI_DECLSPEC extern
#   endif
#   ifndef ecy_hsm_CSAI_CALL
#       define ecy_hsm_CSAI_CALL
#   endif
#endif

#if defined(GUAM) && (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_PC)
#   if defined (_WIN32)
       /** Export symbol from Windows shared library (.dll) */
#      define ecy_hsm_CSAI_EXPORT __declspec(dllexport)
       /** Import symbol from Windows shared library (.dll) */
#      define ecy_hsm_CSAI_IMPORT __declspec(dllimport)
#   else
       /** Export symbol from Linux shared library (.so) */
#      define ecy_hsm_CSAI_EXPORT __attribute__((visibility("default")))
       /** Symbol importing is only used on Windows */
#      define ecy_hsm_CSAI_IMPORT
#   endif
#else
    /** Symbol exporting is only used for virtual HSM */
#   define ecy_hsm_CSAI_EXPORT
    /** Symbol importing is only used for virtual HSM */
#   define ecy_hsm_CSAI_IMPORT
#endif

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
