/*
    Copyright(C) 2019 eSOL Co., Ltd. All rights reserved.

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
[mcos_v850_hook_code.h] - MCOS hook interface header
****************************************************************************/
#ifndef MCOS_V850_HOOK_CODE_H
#define MCOS_V850_HOOK_CODE_H

#define MCOS_HOOK_PRODUCT_HWL_V850    0x85000000U

#define MCOS_HOOK_MODULE_HWL_V850                 (MCOS_HOOK_PRODUCT_HWL_V850 | 0x00010000U)
#define MCOS_HOOK_FILE_HWL_V850                   (MCOS_HOOK_MODULE_HWL_V850 | 0x00000100U)

#endif  /* #ifndef MCOS_V850_HOOK_CODE_H */
