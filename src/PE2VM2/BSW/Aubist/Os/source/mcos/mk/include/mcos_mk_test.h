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
[ mcos_mk_test.h ] - eMCOS microkernel test header
****************************************************************************/
#ifndef MCOS_MK_TEST_H
#define MCOS_MK_TEST_H

#include "mcos_cmn.h"

#define mcos_mk_test_assert(msg, condition) mcos_mk_test_assert_log(msg, condition, __FILE__, __LINE__)

#define mcos_mk_test_check_only(msg, condition) mcos_mk_test_check_only_log(msg, condition, __FILE__, __LINE__)


void test_hwl_main(mcos_id_t lcid);
void test_hwl_msg(mcos_id_t lcid);

/* test assert */
void mcos_mk_test_assert_log(
        const char *msg,
        int32_t condition,
        char *filename,
        int line);

/* test assert */
void mcos_mk_test_check_only_log(
        const char *msg,
        int32_t condition,
        char *filename,
        int line);

#endif /* #ifndef MCOS_MK_TEST_H */

