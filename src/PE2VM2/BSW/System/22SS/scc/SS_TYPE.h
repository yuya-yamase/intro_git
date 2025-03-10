/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_TYPE.h
 * [Module]			System
 * [Function]		System symbols
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_TYPE_H
#define SS_TYPE_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*
 * for basic type
 */
#define SS_TYPE_u1U1BITSIZE ((uint8)8U)
#define SS_TYPE_u1U2BITSIZE ((uint8)16U)
#define SS_TYPE_u1U4BITSIZE ((uint8)32U)

#define SS_TYPE_u1U1SIGNBIT ((uint8)0x80U)
#define SS_TYPE_u2U2SIGNBIT ((uint16)0x8000U)
#define SS_TYPE_u4U3SIGNBIT (0x00800000UL)
#define SS_TYPE_u4U4SIGNBIT (0x80000000UL)

#define SS_TYPE_bSET ((boolean)1U)
#define SS_TYPE_bCLR ((boolean)0U)

#define SS_TYPE_s1MIN ((sint8)-128)
#define SS_TYPE_s1MAX ((sint8)127)

#define SS_TYPE_s2MIN ((sint16)-32768)
#define SS_TYPE_s2MAX ((sint16)32767)

/* S4_MIN: "-1" is a measure for the QAC-tool's bug that warn -2147483648L at 101-situations */
#define SS_TYPE_s4MIN ((sint32)(-2147483647L - 1L))
#define SS_TYPE_s4MAX ((sint32)2147483647L)

#define SS_TYPE_u1MIN ((uint8)0U)
#define SS_TYPE_u1MAX ((uint8)255U)

#define SS_TYPE_u2MIN ((uint16)0U)
#define SS_TYPE_u2MAX ((uint16)65535U)

#define SS_TYPE_u4MIN (0UL)
#define SS_TYPE_u4MAX (0xFFFFFFFFUL)

/*
 * for SS_BootType in SS_ISeq_Callout.c
 */
#define SS_PM_BOOT_SUP (0xAA55AA55UL)
#define SS_PM_BOOT_WUP (0x55AA55AAUL)

/*
 * for SS_RequestType in SS_ISeq/SS_State
 */
#define SS_REQUEST_NONE  (0xA5A5A5A5UL)
#define SS_REQUEST_EXIST (0x5A5A5A5AUL)

/*
 * for SS_ShutdownReqSrcType in SS_ISeq_Callout.c
 */
#define SS_PM_u4REQSRC_POWEROFF (0xAA55AA55UL)
#define SS_PM_u4REQSRC_SLEEP    (0x55AA55AAUL)
#define SS_PM_u4REQSRC_INIT     (0xCC33CC33UL)
#define SS_PM_u4REQSRC_ERROR    (0x33CC33CCUL)
#define SS_PM_u4REQSRC_TRANSIT  (0x00FF00FFUL)
#define SS_PM_u4REQSRC_PREINIT  (0xFF00FF00UL)

#if !defined(__LANGUAGE_ASM__)

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/
typedef uint32 SS_BootType;
typedef uint32 SS_RequestType;
typedef uint32 SS_ShutdownReqSrcType;

#endif /* !defined(__LANGUAGE_ASM__) */

#endif /* SS_TYPE_H */
