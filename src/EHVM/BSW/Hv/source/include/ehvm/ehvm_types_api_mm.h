/*
    Copyright (C) 2025 eSOL Co.,Ltd. All rights reserved.

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
 [ ehvm_types_api_mm.h ] - EHVM API MM types header
****************************************************************************/

#ifndef EHVM_TYPES_API_MM_H
#define EHVM_TYPES_API_MM_H

/****************************************************************************
    macro definitions
****************************************************************************/

#define EHVM_MM_HWORD_SIZE                  ((ehvm_uint8_t)sizeof(ehvm_int16_t))
#define EHVM_MM_WORD_SIZE                   ((ehvm_uint8_t)sizeof(ehvm_int32_t))
#define EHVM_MM_DWORD_SIZE                  ((ehvm_uint8_t)sizeof(ehvm_int64_t))
#define EHVM_MM_QWORD_SIZE                  ((ehvm_uint8_t)16U)

#endif  /* EHVM_TYPES_API_MM_H */
