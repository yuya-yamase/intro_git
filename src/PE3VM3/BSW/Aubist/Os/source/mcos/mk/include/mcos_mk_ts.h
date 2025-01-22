/*
    Copyright (C) 2011 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_mk_ts.h] - eMCOS/MK thread scheduler local header
****************************************************************************/
#ifndef MCOS_MK_TS_H
#define MCOS_MK_TS_H

#if !MCOS_AUTOSAR

#include "mcos_mk.h"

/* leaf thread scheduler interface functions */
void mcos_ts_main(uint32_t param, mcos_uintptr_t exinf);
mcos_bool_t mcos_ts_create_server(const mkcb_t *mkcb);
void mcos_ts_start_timer(mcos_id_t lcid);

#endif /* !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MK_TS_H */
