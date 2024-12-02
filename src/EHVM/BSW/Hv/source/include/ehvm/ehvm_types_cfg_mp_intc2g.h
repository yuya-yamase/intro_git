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
 [ ehvm_types_cfg_mp_intc2g.h ] - INTC2G module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_MP_INTC2G_H
#define EHVM_TYPES_CFG_MP_INTC2G_H

/* type definitions */

#define INTC2G_MPIDADDR_BASE              (ehvm_uint32_t)(0xFFC64040U)
#define INTC2G_PROTADDR_BASE              (ehvm_uint32_t)(0xFFC64100U)
#define INTC2G_PROT_CHANNEL_OFFSET        (ehvm_uint32_t)(0x04U)
#define INTC2G_MPIDN_OFFSET( peid )       ( (peid) + INTC2G_PROT_CHANNEL_OFFSET )
#define INTC2GPROT_ADDRESS( ch )          ( INTC2G_PROTADDR_BASE + ( INTC2G_PROT_CHANNEL_OFFSET * (ehvm_uint32_t)(ch) ) )
#define INTC2GMPID_ADDRESS( ch )          ( INTC2G_MPIDADDR_BASE + ( INTC2G_PROT_CHANNEL_OFFSET * INTC2G_MPIDN_OFFSET(ch) ) )

/* INTC2G */
#define INTC2G_SWITCH_ENABLE              (0x01U)
#define INTC2G_SWITCH_DISABLE             (0x00U)

typedef struct {
    ehvm_uint32_t                              Intc2gPROT;
} ehvm_intc2g_channel_t;

typedef struct {
    ehvm_uint32_t                              Intc2gChannelNumber;
    ehvm_uint32_t                              Intc2gPROT;
} ehvm_intc2g_n_channel_t;

typedef struct {
    ehvm_uint32_t                              Intc2gSPID;
} ehvm_intc2g_spid_t;

typedef struct {
    ehvm_uint32_t                              Intc2gNumOfSPID;
    EhvmConst ehvm_intc2g_spid_t*             Intc2gSPIDPtr;
    ehvm_uint32_t                              Intc2gNumOfINTC2G_n;
    EhvmConst ehvm_intc2g_n_channel_t*        Intc2gINTC2G_n_Ptr;
    ehvm_uint32_t                              Intc2gNumOfINTC2G_GR;
    EhvmConst ehvm_intc2g_channel_t*          Intc2gINTC2G_GR_Ptr;
    ehvm_uint32_t                              Intc2gNumOfINTC2G_IMR;
    EhvmConst ehvm_intc2g_channel_t*          Intc2gINTC2G_IMR_Ptr;
} ehvm_intc2g_config_t;

typedef struct {
    ehvm_uint32_t                              Intc2gProtAddress;
} ehvm_intc2g_n_channel_switch_t;

typedef struct {
    ehvm_uint32_t                              Intc2gMpidAddress;
    ehvm_spid_t                           Intc2gSPID;
    ehvm_uint32_t                              Intc2gNumOfChannelSwitch;
    EhvmConst ehvm_intc2g_n_channel_switch_t* Intc2gChannelSwitchPtr;
} ehvm_intc2g_prot_switch_t;

typedef struct {
    ehvm_uint32_t                              Intc2gNumOfVM;
    EhvmConst ehvm_intc2g_prot_switch_t*      Intc2gProtSwitchPtr;
} ehvm_intc2g_prot_switch_config_t;

#endif /* EHVM_TYPES_CFG_MP_INTC2G_H */
