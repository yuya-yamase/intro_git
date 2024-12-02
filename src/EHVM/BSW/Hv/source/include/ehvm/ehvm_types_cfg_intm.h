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
 [ ehvm_types_cfg_intm.h ] - INTM module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_INTM_H
#define EHVM_TYPES_CFG_INTM_H

typedef void         (*ehvm_intm_trigger_on_ecm_err_fnc_t)( void );

typedef ehvm_uint32_t  ehvm_intno_t;

#define NOUSE_INTM_INTERRUPT           (ehvm_uint32_t)(0x7FFFFFFF)

typedef struct ehvm_guest_int_config_st{
    ehvm_intno_t      intno;
    ehvm_peid_t       Peid;
    ehvm_gpid_t       Gpid;
}ehvm_guest_int_config_t;

typedef struct ehvm_int_config_common_st{
    ehvm_intno_t      intno;
    ehvm_intm_trigger_on_ecm_err_fnc_t               IntmCallbackEcmErrFnc;
}ehvm_intm_common_config_t;

#endif /* EHVM_TYPES_CFG_INTM_H */
