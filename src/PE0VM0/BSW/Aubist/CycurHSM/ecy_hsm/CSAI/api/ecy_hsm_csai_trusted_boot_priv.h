/**
 * @file
 ***********************************************************************************************
 * @brief Private header file for trusted boot
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2023, all rights reserved.
 **********************************************************************************************/
/* [$Satisfies $COMPONENT Trusted_Software_Applet] */

#include "ecy_hsm_general.h"
#ifndef ECY_HSM_CSAI_TRUSTED_BOOT_PRIV_H
# define ECY_HSM_CSAI_TRUSTED_BOOT_PRIV_H

/** Param buffer type for ecy_hsm_APPLET_TB_FUNC_INIT */
typedef struct ecy_hsm_Csai_TB_Init_ParamBufferTag
{
    uint32* pCntSwParts_HOST; /**< Host pointer for pCntSwParts */
    uint32  cntSwParts_HSM;   /**< HSM buffer for pCntSwParts, which is used for the service to prevent TOCTOU attacks */
} ecy_hsm_Csai_TB_Init_ParamBufferT;

/** Param buffer union which is used to copy the parameters to the HSM's workspace.
 *  Needed to protect against TOCTOU attacks.
 */
typedef union TB_ParamBufferTag
{
    ecy_hsm_Csai_TB_Init_ParamBufferT initParamBuffer; /**< Param buffer for ecy_hsm_APPLET_TB_FUNC_INIT */
} TB_ParamBufferT;

#endif
