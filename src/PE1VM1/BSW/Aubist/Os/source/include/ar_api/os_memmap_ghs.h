/*
    Copyright (C) 2016 eSOL Co.,Ltd. Tokyo, Japan
    This software is protected by the law and the agreement concerning
    a Japanese country copyright method, an international agreement,
    and other intellectual property right and may be used and copied
    only in accordance with the terms of such license and with the inclusion
    of the above copyright notice.
    This software or any other copies thereof may not be provided
    or otherwise made available to any other person.  No title to
    and ownership of the software is hereby transferred.
    The information in this software is subject to change without
    notice and should not be construed as a commitment by eSOL Co.,Ltd.
*/
/****************************************************************************
[ os_memmap_ghs.h ] - Memory Mapping internal header for OS module (GHS)
****************************************************************************/

/*
 * [VAR_NO_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : (omitted)
 * alignment       : BOOLEAN
 */
#if defined OS_START_SEC_VAR_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Global_NoInit_Boolean"
#else
    .section ".osVar_Global_NoInit_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_NO_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : (omitted)
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_NO_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Global_NoInit_8"
#else
    .section ".osVar_Global_NoInit_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_NO_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_NO_INIT_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_NO_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_NO_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : (omitted)
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_NO_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Global_NoInit_16"
#else
    .section ".osVar_Global_NoInit_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_NO_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_NO_INIT_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_NO_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_NO_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : (omitted)
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_NO_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Global_NoInit_32"
#else
    .section ".osVar_Global_NoInit_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_NO_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_NO_INIT_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_NO_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_NO_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : (omitted)
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_NO_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Global_NoInit_64"
#else
    .section ".osVar_Global_NoInit_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_NO_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_NO_INIT_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_NO_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_NO_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : (omitted)
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Global_NoInit_Unspecified"
#else
    .section ".osVar_Global_NoInit_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_CLEARED_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : (omitted)
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Global_Cleared_Boolean"
#else
    .section ".osVar_Global_Cleared_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_CLEARED_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_CLEARED_8]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : (omitted)
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_CLEARED_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Global_Cleared_8"
#else
    .section ".osVar_Global_Cleared_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_CLEARED_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_CLEARED_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_CLEARED_8
#undef MEMMAP_ERROR

/*
 * [VAR_CLEARED_16]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : (omitted)
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_CLEARED_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Global_Cleared_16"
#else
    .section ".osVar_Global_Cleared_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_CLEARED_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_CLEARED_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_CLEARED_16
#undef MEMMAP_ERROR

/*
 * [VAR_CLEARED_32]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : (omitted)
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_CLEARED_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Global_Cleared_32"
#else
    .section ".osVar_Global_Cleared_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_CLEARED_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_CLEARED_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_CLEARED_32
#undef MEMMAP_ERROR

/*
 * [VAR_CLEARED_64]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : (omitted)
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_CLEARED_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Global_Cleared_64"
#else
    .section ".osVar_Global_Cleared_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_CLEARED_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_CLEARED_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_CLEARED_64
#undef MEMMAP_ERROR

/*
 * [VAR_CLEARED_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : (omitted)
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Global_Cleared_Unspecified"
#else
    .section ".osVar_Global_Cleared_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : (omitted)
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Global_Init_Boolean"
#else
    .section ".osVar_Global_Init_Boolean", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : (omitted)
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Global_Init_8"
#else
    .section ".osVar_Global_Init_8", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_INIT_8
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : (omitted)
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section data=".osVar_Global_Init_16"
#else
    .section ".osVar_Global_Init_16", "aw"
    .align 2
#endif
#undef OS_START_SEC_VAR_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_INIT_16
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : (omitted)
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section data=".osVar_Global_Init_32"
#else
    .section ".osVar_Global_Init_32", "aw"
    .align 4
#endif
#undef OS_START_SEC_VAR_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_INIT_32
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : (omitted)
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section data=".osVar_Global_Init_64"
#else
    .section ".osVar_Global_Init_64", "aw"
    .align 8
#endif
#undef OS_START_SEC_VAR_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_INIT_64
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : (omitted)
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section data=".osVar_Global_Init_Unspecified"
#else
    .section ".osVar_Global_Init_Unspecified", "aw"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_NO_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_GLOBAL_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Global_NoInit_Boolean"
#else
    .section ".osVar_Global_NoInit_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_GLOBAL_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_NO_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_NO_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Global_NoInit_8"
#else
    .section ".osVar_Global_NoInit_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_GLOBAL_NO_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_NO_INIT_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_NO_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_NO_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_NO_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Global_NoInit_16"
#else
    .section ".osVar_Global_NoInit_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_GLOBAL_NO_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_NO_INIT_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_NO_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_NO_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_NO_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Global_NoInit_32"
#else
    .section ".osVar_Global_NoInit_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_GLOBAL_NO_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_NO_INIT_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_NO_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_NO_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_NO_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Global_NoInit_64"
#else
    .section ".osVar_Global_NoInit_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_GLOBAL_NO_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_NO_INIT_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_NO_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_NO_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Global_NoInit_Unspecified"
#else
    .section ".osVar_Global_NoInit_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_CLEARED_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : GLOBAL
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_GLOBAL_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Global_Cleared_Boolean"
#else
    .section ".osVar_Global_Cleared_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_GLOBAL_CLEARED_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_CLEARED_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_CLEARED_8]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : GLOBAL
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_CLEARED_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Global_Cleared_8"
#else
    .section ".osVar_Global_Cleared_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_GLOBAL_CLEARED_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_CLEARED_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_CLEARED_8
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_CLEARED_16]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : GLOBAL
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_CLEARED_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Global_Cleared_16"
#else
    .section ".osVar_Global_Cleared_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_GLOBAL_CLEARED_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_CLEARED_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_CLEARED_16
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_CLEARED_32]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : GLOBAL
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_CLEARED_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Global_Cleared_32"
#else
    .section ".osVar_Global_Cleared_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_GLOBAL_CLEARED_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_CLEARED_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_CLEARED_32
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_CLEARED_64]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : GLOBAL
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_CLEARED_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Global_Cleared_64"
#else
    .section ".osVar_Global_Cleared_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_GLOBAL_CLEARED_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_CLEARED_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_CLEARED_64
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_CLEARED_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : GLOBAL
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_GLOBAL_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Global_Cleared_Unspecified"
#else
    .section ".osVar_Global_Cleared_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_GLOBAL_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : GLOBAL
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_GLOBAL_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Global_Init_Boolean"
#else
    .section ".osVar_Global_Init_Boolean", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_GLOBAL_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : GLOBAL
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Global_Init_8"
#else
    .section ".osVar_Global_Init_8", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_GLOBAL_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_INIT_8
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : GLOBAL
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section data=".osVar_Global_Init_16"
#else
    .section ".osVar_Global_Init_16", "aw"
    .align 2
#endif
#undef OS_START_SEC_VAR_GLOBAL_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_INIT_16
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : GLOBAL
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section data=".osVar_Global_Init_32"
#else
    .section ".osVar_Global_Init_32", "aw"
    .align 4
#endif
#undef OS_START_SEC_VAR_GLOBAL_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_INIT_32
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : GLOBAL
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_GLOBAL_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section data=".osVar_Global_Init_64"
#else
    .section ".osVar_Global_Init_64", "aw"
    .align 8
#endif
#undef OS_START_SEC_VAR_GLOBAL_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_INIT_64
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_GLOBAL_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : GLOBAL
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_GLOBAL_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section data=".osVar_Global_Init_Unspecified"
#else
    .section ".osVar_Global_Init_Unspecified", "aw"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_GLOBAL_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_GLOBAL_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_GLOBAL_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_NO_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL0
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL0_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local0_NoInit_Boolean"
#else
    .section ".osVar_Local0_NoInit_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL0_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_NO_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL0
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_NO_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local0_NoInit_8"
#else
    .section ".osVar_Local0_NoInit_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL0_NO_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_NO_INIT_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_NO_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_NO_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL0
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_NO_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local0_NoInit_16"
#else
    .section ".osVar_Local0_NoInit_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL0_NO_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_NO_INIT_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_NO_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_NO_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL0
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local0_NoInit_32"
#else
    .section ".osVar_Local0_NoInit_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_NO_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL0
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_NO_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local0_NoInit_64"
#else
    .section ".osVar_Local0_NoInit_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL0_NO_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_NO_INIT_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_NO_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_NO_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL0
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL0_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local0_NoInit_Unspecified"
#else
    .section ".osVar_Local0_NoInit_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL0_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_CLEARED_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL0
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL0_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local0_Cleared_Boolean"
#else
    .section ".osVar_Local0_Cleared_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL0_CLEARED_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_CLEARED_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_CLEARED_8]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL0
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_CLEARED_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local0_Cleared_8"
#else
    .section ".osVar_Local0_Cleared_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL0_CLEARED_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_CLEARED_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_CLEARED_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_CLEARED_16]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL0
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_CLEARED_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local0_Cleared_16"
#else
    .section ".osVar_Local0_Cleared_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL0_CLEARED_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_CLEARED_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_CLEARED_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_CLEARED_32]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL0
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_CLEARED_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local0_Cleared_32"
#else
    .section ".osVar_Local0_Cleared_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL0_CLEARED_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_CLEARED_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_CLEARED_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_CLEARED_64]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL0
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_CLEARED_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local0_Cleared_64"
#else
    .section ".osVar_Local0_Cleared_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL0_CLEARED_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_CLEARED_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_CLEARED_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_CLEARED_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL0
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL0_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local0_Cleared_Unspecified"
#else
    .section ".osVar_Local0_Cleared_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL0_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL0
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL0_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local0_Init_Boolean"
#else
    .section ".osVar_Local0_Init_Boolean", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL0_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL0
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local0_Init_8"
#else
    .section ".osVar_Local0_Init_8", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL0_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_INIT_8
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL0
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section data=".osVar_Local0_Init_16"
#else
    .section ".osVar_Local0_Init_16", "aw"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL0_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_INIT_16
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL0
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section data=".osVar_Local0_Init_32"
#else
    .section ".osVar_Local0_Init_32", "aw"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL0_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_INIT_32
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL0
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL0_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section data=".osVar_Local0_Init_64"
#else
    .section ".osVar_Local0_Init_64", "aw"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL0_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_INIT_64
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL0_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL0
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL0_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section data=".osVar_Local0_Init_Unspecified"
#else
    .section ".osVar_Local0_Init_Unspecified", "aw"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL0_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [OS_START_SEC_VAR_LOCAL0_MKMSG_BUFFERS]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL0
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL0_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=".osVar_Local0_Mkmsg_Buffers"
#else
    .section ".osVar_Local0_Mkmsg_Buffers", "awb"
#endif
#undef OS_START_SEC_VAR_LOCAL0_MKMSG_BUFFERS
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL0_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL0_MKMSG_BUFFERS
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_NO_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL1
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL1_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local1_NoInit_Boolean"
#else
    .section ".osVar_Local1_NoInit_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL1_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_NO_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL1
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_NO_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local1_NoInit_8"
#else
    .section ".osVar_Local1_NoInit_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL1_NO_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_NO_INIT_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_NO_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_NO_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL1
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_NO_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local1_NoInit_16"
#else
    .section ".osVar_Local1_NoInit_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL1_NO_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_NO_INIT_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_NO_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_NO_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL1
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_NO_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local1_NoInit_32"
#else
    .section ".osVar_Local1_NoInit_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL1_NO_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_NO_INIT_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_NO_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_NO_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL1
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_NO_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local1_NoInit_64"
#else
    .section ".osVar_Local1_NoInit_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL1_NO_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_NO_INIT_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_NO_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_NO_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL1
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL1_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local1_NoInit_Unspecified"
#else
    .section ".osVar_Local1_NoInit_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL1_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_CLEARED_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL1
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL1_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local1_Cleared_Boolean"
#else
    .section ".osVar_Local1_Cleared_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL1_CLEARED_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_CLEARED_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_CLEARED_8]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL1
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_CLEARED_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local1_Cleared_8"
#else
    .section ".osVar_Local1_Cleared_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL1_CLEARED_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_CLEARED_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_CLEARED_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_CLEARED_16]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL1
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_CLEARED_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local1_Cleared_16"
#else
    .section ".osVar_Local1_Cleared_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL1_CLEARED_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_CLEARED_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_CLEARED_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_CLEARED_32]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL1
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_CLEARED_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local1_Cleared_32"
#else
    .section ".osVar_Local1_Cleared_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL1_CLEARED_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_CLEARED_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_CLEARED_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_CLEARED_64]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL1
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_CLEARED_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local1_Cleared_64"
#else
    .section ".osVar_Local1_Cleared_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL1_CLEARED_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_CLEARED_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_CLEARED_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_CLEARED_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL1
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL1_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local1_Cleared_Unspecified"
#else
    .section ".osVar_Local1_Cleared_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL1_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL1
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL1_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local1_Init_Boolean"
#else
    .section ".osVar_Local1_Init_Boolean", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL1_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL1
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local1_Init_8"
#else
    .section ".osVar_Local1_Init_8", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL1_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_INIT_8
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL1
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section data=".osVar_Local1_Init_16"
#else
    .section ".osVar_Local1_Init_16", "aw"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL1_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_INIT_16
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL1
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section data=".osVar_Local1_Init_32"
#else
    .section ".osVar_Local1_Init_32", "aw"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL1_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_INIT_32
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL1
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL1_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section data=".osVar_Local1_Init_64"
#else
    .section ".osVar_Local1_Init_64", "aw"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL1_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_INIT_64
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL1_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL1
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL1_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section data=".osVar_Local1_Init_Unspecified"
#else
    .section ".osVar_Local1_Init_Unspecified", "aw"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL1_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [OS_START_SEC_VAR_LOCAL1_MKMSG_BUFFERS]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL1
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL1_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=".osVar_Local1_Mkmsg_Buffers"
#else
    .section ".osVar_Local1_Mkmsg_Buffers", "awb"
#endif
#undef OS_START_SEC_VAR_LOCAL1_MKMSG_BUFFERS
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL1_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL1_MKMSG_BUFFERS
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_NO_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL2
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL2_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local2_NoInit_Boolean"
#else
    .section ".osVar_Local2_NoInit_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL2_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_NO_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL2
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_NO_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local2_NoInit_8"
#else
    .section ".osVar_Local2_NoInit_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL2_NO_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_NO_INIT_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_NO_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_NO_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL2
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_NO_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local2_NoInit_16"
#else
    .section ".osVar_Local2_NoInit_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL2_NO_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_NO_INIT_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_NO_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_NO_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL2
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_NO_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local2_NoInit_32"
#else
    .section ".osVar_Local2_NoInit_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL2_NO_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_NO_INIT_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_NO_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_NO_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL2
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_NO_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local2_NoInit_64"
#else
    .section ".osVar_Local2_NoInit_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL2_NO_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_NO_INIT_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_NO_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_NO_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL2
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL2_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local2_NoInit_Unspecified"
#else
    .section ".osVar_Local2_NoInit_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL2_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_CLEARED_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL2
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL2_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local2_Cleared_Boolean"
#else
    .section ".osVar_Local2_Cleared_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL2_CLEARED_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_CLEARED_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_CLEARED_8]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL2
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_CLEARED_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local2_Cleared_8"
#else
    .section ".osVar_Local2_Cleared_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL2_CLEARED_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_CLEARED_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_CLEARED_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_CLEARED_16]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL2
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_CLEARED_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local2_Cleared_16"
#else
    .section ".osVar_Local2_Cleared_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL2_CLEARED_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_CLEARED_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_CLEARED_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_CLEARED_32]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL2
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_CLEARED_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local2_Cleared_32"
#else
    .section ".osVar_Local2_Cleared_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL2_CLEARED_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_CLEARED_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_CLEARED_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_CLEARED_64]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL2
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_CLEARED_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local2_Cleared_64"
#else
    .section ".osVar_Local2_Cleared_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL2_CLEARED_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_CLEARED_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_CLEARED_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_CLEARED_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL2
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL2_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local2_Cleared_Unspecified"
#else
    .section ".osVar_Local2_Cleared_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL2_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL2
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL2_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local2_Init_Boolean"
#else
    .section ".osVar_Local2_Init_Boolean", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL2_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL2
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local2_Init_8"
#else
    .section ".osVar_Local2_Init_8", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL2_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_INIT_8
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL2
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section data=".osVar_Local2_Init_16"
#else
    .section ".osVar_Local2_Init_16", "aw"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL2_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_INIT_16
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL2
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section data=".osVar_Local2_Init_32"
#else
    .section ".osVar_Local2_Init_32", "aw"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL2_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_INIT_32
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL2
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL2_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section data=".osVar_Local2_Init_64"
#else
    .section ".osVar_Local2_Init_64", "aw"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL2_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_INIT_64
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL2_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL2
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL2_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section data=".osVar_Local2_Init_Unspecified"
#else
    .section ".osVar_Local2_Init_Unspecified", "aw"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL2_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [OS_START_SEC_VAR_LOCAL2_MKMSG_BUFFERS]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL2
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL2_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=".osVar_Local2_Mkmsg_Buffers"
#else
    .section ".osVar_Local2_Mkmsg_Buffers", "awb"
#endif
#undef OS_START_SEC_VAR_LOCAL2_MKMSG_BUFFERS
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL2_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL2_MKMSG_BUFFERS
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_NO_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL3
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL3_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local3_NoInit_Boolean"
#else
    .section ".osVar_Local3_NoInit_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL3_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_NO_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL3
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_NO_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local3_NoInit_8"
#else
    .section ".osVar_Local3_NoInit_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL3_NO_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_NO_INIT_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_NO_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_NO_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL3
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_NO_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local3_NoInit_16"
#else
    .section ".osVar_Local3_NoInit_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL3_NO_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_NO_INIT_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_NO_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_NO_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL3
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_NO_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local3_NoInit_32"
#else
    .section ".osVar_Local3_NoInit_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL3_NO_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_NO_INIT_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_NO_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_NO_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL3
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_NO_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local3_NoInit_64"
#else
    .section ".osVar_Local3_NoInit_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL3_NO_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_NO_INIT_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_NO_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_NO_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL3
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL3_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local3_NoInit_Unspecified"
#else
    .section ".osVar_Local3_NoInit_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL3_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_CLEARED_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL3
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL3_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local3_Cleared_Boolean"
#else
    .section ".osVar_Local3_Cleared_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL3_CLEARED_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_CLEARED_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_CLEARED_8]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL3
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_CLEARED_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local3_Cleared_8"
#else
    .section ".osVar_Local3_Cleared_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL3_CLEARED_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_CLEARED_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_CLEARED_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_CLEARED_16]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL3
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_CLEARED_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local3_Cleared_16"
#else
    .section ".osVar_Local3_Cleared_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL3_CLEARED_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_CLEARED_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_CLEARED_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_CLEARED_32]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL3
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_CLEARED_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local3_Cleared_32"
#else
    .section ".osVar_Local3_Cleared_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL3_CLEARED_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_CLEARED_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_CLEARED_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_CLEARED_64]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL3
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_CLEARED_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local3_Cleared_64"
#else
    .section ".osVar_Local3_Cleared_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL3_CLEARED_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_CLEARED_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_CLEARED_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_CLEARED_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL3
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL3_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local3_Cleared_Unspecified"
#else
    .section ".osVar_Local3_Cleared_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL3_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL3
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL3_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local3_Init_Boolean"
#else
    .section ".osVar_Local3_Init_Boolean", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL3_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL3
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local3_Init_8"
#else
    .section ".osVar_Local3_Init_8", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL3_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_INIT_8
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL3
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section data=".osVar_Local3_Init_16"
#else
    .section ".osVar_Local3_Init_16", "aw"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL3_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_INIT_16
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL3
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section data=".osVar_Local3_Init_32"
#else
    .section ".osVar_Local3_Init_32", "aw"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL3_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_INIT_32
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL3
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL3_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section data=".osVar_Local3_Init_64"
#else
    .section ".osVar_Local3_Init_64", "aw"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL3_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_INIT_64
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL3_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL3
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL3_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section data=".osVar_Local3_Init_Unspecified"
#else
    .section ".osVar_Local3_Init_Unspecified", "aw"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL3_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [OS_START_SEC_VAR_LOCAL3_MKMSG_BUFFERS]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL3
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL3_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=".osVar_Local3_Mkmsg_Buffers"
#else
    .section ".osVar_Local3_Mkmsg_Buffers", "awb"
#endif
#undef OS_START_SEC_VAR_LOCAL3_MKMSG_BUFFERS
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL3_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL3_MKMSG_BUFFERS
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_NO_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL4
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL4_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local4_NoInit_Boolean"
#else
    .section ".osVar_Local4_NoInit_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL4_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_NO_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL4
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_NO_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local4_NoInit_8"
#else
    .section ".osVar_Local4_NoInit_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL4_NO_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_NO_INIT_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_NO_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_NO_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL4
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_NO_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local4_NoInit_16"
#else
    .section ".osVar_Local4_NoInit_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL4_NO_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_NO_INIT_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_NO_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_NO_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL4
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_NO_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local4_NoInit_32"
#else
    .section ".osVar_Local4_NoInit_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL4_NO_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_NO_INIT_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_NO_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_NO_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL4
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_NO_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local4_NoInit_64"
#else
    .section ".osVar_Local4_NoInit_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL4_NO_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_NO_INIT_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_NO_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_NO_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL4
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL4_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local4_NoInit_Unspecified"
#else
    .section ".osVar_Local4_NoInit_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL4_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_CLEARED_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL4
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL4_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local4_Cleared_Boolean"
#else
    .section ".osVar_Local4_Cleared_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL4_CLEARED_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_CLEARED_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_CLEARED_8]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL4
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_CLEARED_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local4_Cleared_8"
#else
    .section ".osVar_Local4_Cleared_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL4_CLEARED_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_CLEARED_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_CLEARED_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_CLEARED_16]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL4
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_CLEARED_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local4_Cleared_16"
#else
    .section ".osVar_Local4_Cleared_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL4_CLEARED_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_CLEARED_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_CLEARED_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_CLEARED_32]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL4
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_CLEARED_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local4_Cleared_32"
#else
    .section ".osVar_Local4_Cleared_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL4_CLEARED_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_CLEARED_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_CLEARED_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_CLEARED_64]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL4
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_CLEARED_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local4_Cleared_64"
#else
    .section ".osVar_Local4_Cleared_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL4_CLEARED_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_CLEARED_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_CLEARED_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_CLEARED_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL4
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL4_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local4_Cleared_Unspecified"
#else
    .section ".osVar_Local4_Cleared_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL4_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL4
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL4_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local4_Init_Boolean"
#else
    .section ".osVar_Local4_Init_Boolean", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL4_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL4
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local4_Init_8"
#else
    .section ".osVar_Local4_Init_8", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL4_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_INIT_8
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL4
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section data=".osVar_Local4_Init_16"
#else
    .section ".osVar_Local4_Init_16", "aw"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL4_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_INIT_16
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL4
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section data=".osVar_Local4_Init_32"
#else
    .section ".osVar_Local4_Init_32", "aw"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL4_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_INIT_32
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL4
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL4_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section data=".osVar_Local4_Init_64"
#else
    .section ".osVar_Local4_Init_64", "aw"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL4_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_INIT_64
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL4_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL4
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL4_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section data=".osVar_Local4_Init_Unspecified"
#else
    .section ".osVar_Local4_Init_Unspecified", "aw"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL4_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [OS_START_SEC_VAR_LOCAL4_MKMSG_BUFFERS]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL4
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL4_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=".osVar_Local4_Mkmsg_Buffers"
#else
    .section ".osVar_Local4_Mkmsg_Buffers", "awb"
#endif
#undef OS_START_SEC_VAR_LOCAL4_MKMSG_BUFFERS
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL4_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL4_MKMSG_BUFFERS
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_NO_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL5
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL5_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local5_NoInit_Boolean"
#else
    .section ".osVar_Local5_NoInit_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL5_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_NO_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL5
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_NO_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local5_NoInit_8"
#else
    .section ".osVar_Local5_NoInit_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL5_NO_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_NO_INIT_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_NO_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_NO_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL5
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_NO_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local5_NoInit_16"
#else
    .section ".osVar_Local5_NoInit_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL5_NO_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_NO_INIT_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_NO_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_NO_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL5
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_NO_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local5_NoInit_32"
#else
    .section ".osVar_Local5_NoInit_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL5_NO_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_NO_INIT_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_NO_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_NO_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL5
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_NO_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local5_NoInit_64"
#else
    .section ".osVar_Local5_NoInit_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL5_NO_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_NO_INIT_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_NO_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_NO_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL5
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL5_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local5_NoInit_Unspecified"
#else
    .section ".osVar_Local5_NoInit_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL5_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_CLEARED_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL5
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL5_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local5_Cleared_Boolean"
#else
    .section ".osVar_Local5_Cleared_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL5_CLEARED_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_CLEARED_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_CLEARED_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_CLEARED_8]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL5
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_CLEARED_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVar_Local5_Cleared_8"
#else
    .section ".osVar_Local5_Cleared_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL5_CLEARED_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_CLEARED_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_CLEARED_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_CLEARED_16]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL5
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_CLEARED_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVar_Local5_Cleared_16"
#else
    .section ".osVar_Local5_Cleared_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL5_CLEARED_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_CLEARED_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_CLEARED_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_CLEARED_32]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL5
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_CLEARED_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVar_Local5_Cleared_32"
#else
    .section ".osVar_Local5_Cleared_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL5_CLEARED_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_CLEARED_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_CLEARED_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_CLEARED_64]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL5
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_CLEARED_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVar_Local5_Cleared_64"
#else
    .section ".osVar_Local5_Cleared_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL5_CLEARED_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_CLEARED_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_CLEARED_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_CLEARED_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : CLEARED
 * Core Scope      : LOCAL5
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL5_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVar_Local5_Cleared_Unspecified"
#else
    .section ".osVar_Local5_Cleared_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL5_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_CLEARED_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_INIT_BOOLEAN]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL5
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_LOCAL5_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local5_Init_Boolean"
#else
    .section ".osVar_Local5_Init_Boolean", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL5_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_INIT_8]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL5
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section data=".osVar_Local5_Init_8"
#else
    .section ".osVar_Local5_Init_8", "aw"
    .align 1
#endif
#undef OS_START_SEC_VAR_LOCAL5_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_INIT_8
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_INIT_16]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL5
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section data=".osVar_Local5_Init_16"
#else
    .section ".osVar_Local5_Init_16", "aw"
    .align 2
#endif
#undef OS_START_SEC_VAR_LOCAL5_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_INIT_16
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_INIT_32]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL5
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section data=".osVar_Local5_Init_32"
#else
    .section ".osVar_Local5_Init_32", "aw"
    .align 4
#endif
#undef OS_START_SEC_VAR_LOCAL5_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_INIT_32
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_INIT_64]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL5
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_LOCAL5_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section data=".osVar_Local5_Init_64"
#else
    .section ".osVar_Local5_Init_64", "aw"
    .align 8
#endif
#undef OS_START_SEC_VAR_LOCAL5_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_INIT_64
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_LOCAL5_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR
 * Initial Policy  : INIT
 * Core Scope      : LOCAL5
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL5_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section data=".osVar_Local5_Init_Unspecified"
#else
    .section ".osVar_Local5_Init_Unspecified", "aw"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_LOCAL5_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [OS_START_SEC_VAR_LOCAL5_MKMSG_BUFFERS]
 *
 * Section Type    : VAR
 * Initial Policy  : NO_INIT
 * Core Scope      : LOCAL5
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_LOCAL5_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=".osVar_Local5_Mkmsg_Buffers"
#else
    .section ".osVar_Local5_Mkmsg_Buffers", "awb"
#endif
#undef OS_START_SEC_VAR_LOCAL5_MKMSG_BUFFERS
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_LOCAL5_MKMSG_BUFFERS
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_LOCAL5_MKMSG_BUFFERS
#undef MEMMAP_ERROR

/*
 * [VAR_SPINLOCK_GLOBAL_NO_INIT_BOOLEAN]
 *
 * Section Type    : VAR_SPINLOCK
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVarSpinlock_Global_NoInit_Boolean"
#else
    .section ".osVarSpinlock_Global_NoInit_Boolean", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [VAR_SPINLOCK_GLOBAL_NO_INIT_8]
 *
 * Section Type    : VAR_SPINLOCK
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section bss=".osVarSpinlock_Global_NoInit_8"
#else
    .section ".osVarSpinlock_Global_NoInit_8", "awb"
    .align 1
#endif
#undef OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_8
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_8
#undef MEMMAP_ERROR

/*
 * [VAR_SPINLOCK_GLOBAL_NO_INIT_16]
 *
 * Section Type    : VAR_SPINLOCK
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section bss=".osVarSpinlock_Global_NoInit_16"
#else
    .section ".osVarSpinlock_Global_NoInit_16", "awb"
    .align 2
#endif
#undef OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_16
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_16
#undef MEMMAP_ERROR

/*
 * [VAR_SPINLOCK_GLOBAL_NO_INIT_32]
 *
 * Section Type    : VAR_SPINLOCK
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section bss=".osVarSpinlock_Global_NoInit_32"
#else
    .section ".osVarSpinlock_Global_NoInit_32", "awb"
    .align 4
#endif
#undef OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_32
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_32
#undef MEMMAP_ERROR

/*
 * [VAR_SPINLOCK_GLOBAL_NO_INIT_64]
 *
 * Section Type    : VAR_SPINLOCK
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section bss=".osVarSpinlock_Global_NoInit_64"
#else
    .section ".osVarSpinlock_Global_NoInit_64", "awb"
    .align 8
#endif
#undef OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_64
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_64
#undef MEMMAP_ERROR

/*
 * [VAR_SPINLOCK_GLOBAL_NO_INIT_256]
 *
 * Section Type    : VAR_SPINLOCK
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : 256 bit
 */
#elif defined OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#ifndef _in_asm_source_
#pragma alignvar (32)
#pragma ghs section bss=".osVarSpinlock_Global_NoInit_256"
#else
    .section ".osVarSpinlock_Global_NoInit_256", "awb"
    .align 32
#endif
#undef OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_256
#undef MEMMAP_ERROR

/*
 * [VAR_SPINLOCK_GLOBAL_NO_INIT_512]
 *
 * Section Type    : VAR_SPINLOCK
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : 512 bit
 */
#elif defined OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_512
#ifndef _in_asm_source_
#pragma alignvar (64)
#pragma ghs section bss=".osVarSpinlock_Global_NoInit_512"
#else
    .section ".osVarSpinlock_Global_NoInit_512", "awb"
    .align 64
#endif
#undef OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_512
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_512
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_512
#undef MEMMAP_ERROR

/*
 * [VAR_SPINLOCK_GLOBAL_NO_INIT_UNSPECIFIED]
 *
 * Section Type    : VAR_SPINLOCK
 * Initial Policy  : NO_INIT
 * Core Scope      : GLOBAL
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section bss=".osVarSpinlock_Global_NoInit_Unspecified"
#else
    .section ".osVarSpinlock_Global_NoInit_Unspecified", "awb"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous
#endif
#undef OS_STOP_SEC_VAR_SPINLOCK_GLOBAL_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [CONST_BOOLEAN]
 *
 * Section Type    : CONST
 * Initial Policy  : (N/A)
 * Core Scope      : (N/A)
 * alignment       : BOOLEAN
 */
#elif defined OS_START_SEC_CONST_BOOLEAN
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section rodata=".osConst_Boolean"
#else
    .section ".osConst_Boolean", "a"
    .align 1
#endif
#undef OS_START_SEC_CONST_BOOLEAN
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_CONST_BOOLEAN
#ifndef _in_asm_source_
#pragma ghs section rodata=default
#else
    .previous
#endif
#undef OS_STOP_SEC_CONST_BOOLEAN
#undef MEMMAP_ERROR

/*
 * [CONST_8]
 *
 * Section Type    : CONST
 * Initial Policy  : (N/A)
 * Core Scope      : (N/A)
 * alignment       : 8 bit
 */
#elif defined OS_START_SEC_CONST_8
#ifndef _in_asm_source_
#pragma alignvar (1)
#pragma ghs section rodata=".osConst_8"
#else
    .section ".osConst_8", "a"
    .align 1
#endif
#undef OS_START_SEC_CONST_8
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_CONST_8
#ifndef _in_asm_source_
#pragma ghs section rodata=default
#else
    .previous
#endif
#undef OS_STOP_SEC_CONST_8
#undef MEMMAP_ERROR

/*
 * [CONST_16]
 *
 * Section Type    : CONST
 * Initial Policy  : (N/A)
 * Core Scope      : (N/A)
 * alignment       : 16 bit
 */
#elif defined OS_START_SEC_CONST_16
#ifndef _in_asm_source_
#pragma alignvar (2)
#pragma ghs section rodata=".osConst_16"
#else
    .section ".osConst_16", "a"
    .align 2
#endif
#undef OS_START_SEC_CONST_16
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_CONST_16
#ifndef _in_asm_source_
#pragma ghs section rodata=default
#else
    .previous
#endif
#undef OS_STOP_SEC_CONST_16
#undef MEMMAP_ERROR

/*
 * [CONST_32]
 *
 * Section Type    : CONST
 * Initial Policy  : (N/A)
 * Core Scope      : (N/A)
 * alignment       : 32 bit
 */
#elif defined OS_START_SEC_CONST_32
#ifndef _in_asm_source_
#pragma alignvar (4)
#pragma ghs section rodata=".osConst_32"
#else
    .section ".osConst_32", "a"
    .align 4
#endif
#undef OS_START_SEC_CONST_32
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_CONST_32
#ifndef _in_asm_source_
#pragma ghs section rodata=default
#else
    .previous
#endif
#undef OS_STOP_SEC_CONST_32
#undef MEMMAP_ERROR

/*
 * [CONST_64]
 *
 * Section Type    : CONST
 * Initial Policy  : (N/A)
 * Core Scope      : (N/A)
 * alignment       : 64 bit
 */
#elif defined OS_START_SEC_CONST_64
#ifndef _in_asm_source_
#pragma alignvar (8)
#pragma ghs section rodata=".osConst_64"
#else
    .section ".osConst_64", "a"
    .align 8
#endif
#undef OS_START_SEC_CONST_64
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_CONST_64
#ifndef _in_asm_source_
#pragma ghs section rodata=default
#else
    .previous
#endif
#undef OS_STOP_SEC_CONST_64
#undef MEMMAP_ERROR

/*
 * [CONST_UNSPECIFIED]
 *
 * Section Type    : CONST
 * Initial Policy  : (N/A)
 * Core Scope      : (N/A)
 * alignment       : UNSPECIFIED
 */
#elif defined OS_START_SEC_CONST_UNSPECIFIED
#ifndef _in_asm_source_
#pragma alignvar (__ghs_alignment)
#pragma ghs section rodata=".osConst_Unspecified"
#else
    .section ".osConst_Unspecified", "a"
    .align __ghs_alignment
#endif
#undef OS_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_CONST_UNSPECIFIED
#ifndef _in_asm_source_
#pragma ghs section rodata=default
#else
    .previous
#endif
#undef OS_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

/*
 * [CODE]
 *
 * Section Type    : CODE
 * Initial Policy  : (N/A)
 * Core Scope      : (omitted)
 * alignment       : (N/A)
 */
#elif defined OS_START_SEC_CODE
#ifndef _in_asm_source_
#pragma ghs section text=".osCode_Global"
#else
    .section ".osCode_Global", "ax"
#endif
#undef OS_START_SEC_CODE
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_CODE
#ifndef _in_asm_source_
#pragma ghs section text=default
#else
    .previous
#endif
#undef OS_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * [CODE_GLOBAL]
 *
 * Section Type    : CODE
 * Initial Policy  : (N/A)
 * Core Scope      : GLOBAL
 * alignment       : (N/A)
 */
#elif defined OS_START_SEC_CODE_GLOBAL
#ifndef _in_asm_source_
#pragma ghs section text=".osCode_Global"
#else
    .section ".osCode_Global", "ax"
#endif
#undef OS_START_SEC_CODE_GLOBAL
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_CODE_GLOBAL
#ifndef _in_asm_source_
#pragma ghs section text=default
#else
    .previous
#endif
#undef OS_STOP_SEC_CODE_GLOBAL
#undef MEMMAP_ERROR

/*
 * [CALLOUT_CODE]
 *
 * Section Type    : CALLOUT_CODE
 * Initial Policy  : (N/A)
 * Core Scope      : (omitted)
 * alignment       : (N/A)
 */
#elif defined OS_START_SEC_CALLOUT_CODE
#ifndef _in_asm_source_
#pragma ghs section text=".osCodeCallOut_Global"
#else
    .section ".osCodeCallOut_Global", "ax"
#endif
#undef OS_START_SEC_CALLOUT_CODE
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_CALLOUT_CODE
#ifndef _in_asm_source_
#pragma ghs section text=default
#else
    .previous
#endif
#undef OS_STOP_SEC_CALLOUT_CODE
#undef MEMMAP_ERROR

/*
 * [CODE_SHARED]
 *
 * Section Type    : CODE_SHARED
 * Initial Policy  : (N/A)
 * Core Scope      : (omitted)
 * alignment       : (N/A)
 */
#elif defined OS_START_SEC_CODE_SHARED
#ifndef _in_asm_source_
#pragma ghs section text=".osCode_Shared_Global"
#else
    .section ".osCode_Shared_Global", "ax"
#endif
#undef OS_START_SEC_CODE_SHARED
#undef MEMMAP_ERROR
#elif defined OS_STOP_SEC_CODE_SHARED
#ifndef _in_asm_source_
#pragma ghs section text=default
#else
    .previous
#endif
#undef OS_STOP_SEC_CODE_SHARED
#undef MEMMAP_ERROR

#endif
