/****************************************************************************
 * Protected                                                                *
 * Copyright AUBASS CO., LTD.                                               *
 ****************************************************************************

    Copyright (C) 2022 eSOL Co.,Ltd. Tokyo, Japan

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
 [ mcos_c_init_table.h ] - OS module's configuration file
****************************************************************************/

#ifndef MCOS_C_INIT_TABLE_H
#define MCOS_C_INIT_TABLE_H

#include "Os.h"

/*
 * Information for initializing the text section
 */
struct text_section_info_st
{
    const MemoryStartAddressType *src;
    const MemoryStartAddressType *dst_start;
    const MemoryStartAddressType *dst_end;
};
typedef struct text_section_info_st text_section_info_t;

/*
 * Information for initializing the data section
 */
struct data_section_info_st
{
    const MemoryStartAddressType *src;
    const MemoryStartAddressType *dst_start;
    const MemoryStartAddressType *dst_end;
};
typedef struct data_section_info_st data_section_info_t;

/*
 * Information for initializing the bss section
 */
struct bss_section_info_st
{
    const MemoryStartAddressType *dst_start;
    const MemoryStartAddressType *dst_end;
};
typedef struct bss_section_info_st bss_section_info_t;

/*
 * Prototype declarations of variables defined in linker script
 *
 */

/*
 * text sections on master core
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const text_section_info_t mcos_global_text_init_table[1];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*
 * data sections on master core
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const data_section_info_t mcos_global_var_init_table[1];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*
 * bss sections on master core
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const bss_section_info_t mcos_global_var_cleared_table[1];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*
 * text sections initialized on core 0 (lcid 1)
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const text_section_info_t mcos_local_core01_text_init_table[1];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*
 * data sections initialized on core 0 (lcid 1)
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const data_section_info_t mcos_local_core01_var_init_table[1];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/*
 * bss sections initialized on core 0 (lcid 1)
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const bss_section_info_t mcos_local_core01_var_cleared_table[1];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#endif /* MCOS_C_INIT_TABLE_H */
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
