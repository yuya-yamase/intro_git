/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_MCAL_Internal_Cfg.h
 * [Module]			Configuration
 * [Function]		Configuration of SS_MCAL internal
 * [Revision]		1.10
 * [Notes]			Customize file
 ****************************************************************************/

#ifndef SS_MCAL_INTERNAL_CFG_H
#define SS_MCAL_INTERNAL_CFG_H

/*----------------------------------------------------------------------------
 *		Macros
 *--------------------------------------------------------------------------*/
#define SS_LWH_NONE  (0U)
#define SS_LWH_EXIST (1U)
#define SS_USE_LWH   (SS_LWH_NONE)

#define SS_USE_RESET (STD_ON)

#define SS_U2A16        (0U)
#define SS_U2A8         (1U)
#define SS_U2A6         (2U)
#define SS_RCARS4       (3U)
#define SS_TARGETDEVICE SS_U2A16

#define SS_GEN_U2A    (0U)
#define SS_GEN_RCARS4 (1U)

#if ((SS_TARGETDEVICE == SS_U2A16) || (SS_TARGETDEVICE == SS_U2A8) || (SS_TARGETDEVICE == SS_U2A6))
#define SS_GEN_PRODUCT SS_GEN_U2A
#elif (SS_TARGETDEVICE == SS_RCARS4)
#define SS_GEN_PRODUCT SS_GEN_RCARS4
#else
#error "Illegal configuration."
#endif

#endif /* SS_MCAL_INTERNAL_CFG_H */
