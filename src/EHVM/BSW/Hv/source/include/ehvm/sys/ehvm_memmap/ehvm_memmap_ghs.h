/*
    Copyright (C) 2022 eSOL Co.,Ltd. All rights reserved.

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
[ ehvm_memmap_ghs.h ] - Memory Mapping internal header for OS module (GHS)
****************************************************************************/

/*
 * [CODE]
 * 
 * Section Type    : CODE
 * Initial Policy  : (N/A)
 * Core Scope      : (omitted)
 * alignment       : (N/A)
 */
#if defined EHVM_START_SEC_CODE
#ifndef _in_asm_source_
/*#pragma alignvar (unspedified) */
#pragma ghs section text=".text.ehvm"
#else
    .section ".text.ehvm", "ax"
/*    .align unspecified */
#endif
#undef EHVM_START_SEC_CODE
#undef MEMMAP_ERROR
#elif defined EHVM_STOP_SEC_CODE
#ifndef _in_asm_source_
#pragma ghs section text=default
#else
    .previous 
#endif
#undef EHVM_STOP_SEC_CODE
#undef MEMMAP_ERROR

/*
 * [RODATA]
 * 
 * Section Type    : RODATA
 * Initial Policy  : (N/A)
 * Core Scope      : (omitted)
 * alignment       : (N/A)
 */
#elif defined EHVM_START_SEC_RODATA
#ifndef _in_asm_source_
#pragma ghs section rodata=".rodata.ehvm"
#else
    .section ".rodata.ehvm", "a"
#endif
#undef EHVM_START_SEC_RODATA
#undef MEMMAP_ERROR
#elif defined EHVM_STOP_SEC_RODATA
#ifndef _in_asm_source_
#pragma ghs section rodata=default
#else
    .previous 
#endif
#undef EHVM_STOP_SEC_RODATA
#undef MEMMAP_ERROR

/*
 * [ROSDATA]
 * 
 * Section Type    : ROSDATA
 * Initial Policy  : (N/A)
 * Core Scope      : (omitted)
 * alignment       : (N/A)
 */
#elif defined EHVM_START_SEC_ROSDATA
#ifndef _in_asm_source_
#pragma ghs section rosdata=".rosdata.ehvm"
#else
    .section ".rosdata.ehvm", "a"
#endif
#undef EHVM_START_SEC_ROSDATA
#undef MEMMAP_ERROR
#elif defined EHVM_STOP_SEC_ROSDATA
#ifndef _in_asm_source_
#pragma ghs section rosdata=default
#else
    .previous 
#endif
#undef EHVM_STOP_SEC_ROSDATA
#undef MEMMAP_ERROR

/*
 * [DATA]
 * 
 * Section Type    : DATA
 * Initial Policy  : POWER_ON_INIT
 * Core Scope      : (omitted)
 * alignment       : UNSPECIFIED
 */
#elif defined EHVM_START_SEC_DATA
#ifndef _in_asm_source_
/*#pragma alignvar (unspedified) */
#pragma ghs section data=".data.ehvm"
#else
    .section ".data.ehvm", "aw"
/*    .align unspecified */
#endif
#undef EHVM_START_SEC_DATA
#undef MEMMAP_ERROR
#elif defined EHVM_STOP_SEC_DATA
#ifndef _in_asm_source_
#pragma ghs section data=default
#else
    .previous 
#endif
#undef EHVM_STOP_SEC_DATA
#undef MEMMAP_ERROR

/*
 * [SDATA]
 * 
 * Section Type    : SDATA
 * Initial Policy  : POWER_ON_INIT
 * Core Scope      : (omitted)
 * alignment       : UNSPECIFIED
 */
#elif defined EHVM_START_SEC_SDATA
#ifndef _in_asm_source_
/*#pragma alignvar (unspedified) */
#pragma ghs section sdata=".sdata.ehvm"
#else
    .section ".sdata.ehvm", "aw"
/*    .align unspecified */
#endif
#undef EHVM_START_SEC_SDATA
#undef MEMMAP_ERROR
#elif defined EHVM_STOP_SEC_SDATA
#ifndef _in_asm_source_
#pragma ghs section sdata=default
#else
    .previous 
#endif
#undef EHVM_STOP_SEC_SDATA
#undef MEMMAP_ERROR

/*
 * [BSS]
 * 
 * Section Type    : BSS
 * Initial Policy  : INIT
 * Core Scope      : (omitted)
 * alignment       : UNSPECIFIED
 */
#elif defined EHVM_START_SEC_BSS
#ifndef _in_asm_source_
/*#pragma alignvar (unspedified) */
#pragma ghs section bss=".bss.ehvm"
#else
    .section ".bss.ehvm", "awb"
/*    .align unspecified */
#endif
#undef EHVM_START_SEC_BSS
#undef MEMMAP_ERROR
#elif defined EHVM_STOP_SEC_BSS
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous 
#endif
#undef EHVM_STOP_SEC_BSS
#undef MEMMAP_ERROR


/*
 * [BSS GLOBAL]
 * 
 * Section Type    : BSS GLOBAL
 * Initial Policy  : INIT
 * Core Scope      : (omitted)
 * alignment       : UNSPECIFIED
 */
#elif defined EHVM_START_SEC_BSS_GLOBAL
#ifndef _in_asm_source_
/*#pragma alignvar (unspedified) */
#pragma ghs section bss=".bss.ehvm.global"
#else
    .section ".bss.ehvm.global", "awb"
/*    .align unspecified */
#endif
#undef EHVM_START_SEC_BSS_GLOBAL
#undef MEMMAP_ERROR
#elif defined EHVM_STOP_SEC_BSS_GLOBAL
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous 
#endif
#undef EHVM_STOP_SEC_BSS_GLOBAL
#undef MEMMAP_ERROR

/*
 * [SBSS]
 * 
 * Section Type    : SBSS
 * Initial Policy  : INIT
 * Core Scope      : (omitted)
 * alignment       : UNSPECIFIED
 */
#elif defined EHVM_START_SEC_SBSS
#ifndef _in_asm_source_
/*#pragma alignvar (unspedified) */
#pragma ghs section sbss=".sbss.ehvm"
#else
    .section ".sbss.ehvm", "awb"
/*    .align unspecified */
#endif
#undef EHVM_START_SEC_SBSS
#undef MEMMAP_ERROR
#elif defined EHVM_STOP_SEC_SBSS
#ifndef _in_asm_source_
#pragma ghs section sbss=default
#else
    .previous 
#endif
#undef EHVM_STOP_SEC_SBSS
#undef MEMMAP_ERROR

/*
 * [NOINIT]
 * 
 * Section Type    : NOINIT
 * Initial Policy  : NO_INIT
 * Core Scope      : (omitted)
 * alignment       : UNSPECIFIED
 */
#elif defined EHVM_START_SEC_NOINIT
#ifndef _in_asm_source_
/*#pragma alignvar (unspedified) */
#pragma ghs section bss=".noinit.ehvm"
#else
    .section ".noinit.ehvm", "awb"
/*    .align unspecified */
#endif
#undef EHVM_START_SEC_NOINIT
#undef MEMMAP_ERROR
#elif defined EHVM_STOP_SEC_NOINIT
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous 
#endif
#undef EHVM_STOP_SEC_NOINIT
#undef MEMMAP_ERROR

/*
 * [STACK]
 * 
 * Section Type    : STACK
 * Initial Policy  : NO_INIT
 * Core Scope      : (omitted)
 * alignment       : UNSPECIFIED
 */
#elif defined EHVM_START_SEC_STACK
#ifndef _in_asm_source_
/*#pragma alignvar (unspedified) */
#pragma ghs section bss=".stack.ehvm"
#else
    .section ".stack.ehvm", "awb"
/*    .align unspecified */
#endif
#undef EHVM_START_SEC_STACK
#undef MEMMAP_ERROR
#elif defined EHVM_STOP_SEC_STACK
#ifndef _in_asm_source_
#pragma ghs section bss=default
#else
    .previous 
#endif
#undef EHVM_STOP_SEC_STACK
#undef MEMMAP_ERROR

#endif /* EHVM_xx_SEC_xx */
