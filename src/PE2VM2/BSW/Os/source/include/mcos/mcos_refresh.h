/*
    Copyright (C) 2017 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_refresh.h] - MCOS register refresh interface header
****************************************************************************/

#ifndef     MCOS_REFRESH_H
#define     MCOS_REFRESH_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define MCOS_E_REFRESH_OK                (0)     /* OK */
#define MCOS_E_REFRESH_FIXED             (-1)    /* detected invalid values */
                                                 /*  & fixed all registers */
#define MCOS_E_REFRESH_INVALID_VALUE     (-2)    /* detected invalid values */
#define MCOS_E_REFRESH_NOT_OK            (-3)    /* Error */

typedef sint32 mcos_refresh_err_t;

mcos_refresh_err_t  mcos_refresh_register_values(boolean should_fix);
mcos_refresh_err_t  mcos_refresh_register_values_internal(boolean should_fix);

#endif  /* MCOS_REFRESH_H */
