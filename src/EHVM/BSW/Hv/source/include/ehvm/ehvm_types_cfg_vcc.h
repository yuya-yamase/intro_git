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
 [ ehvm_types_cfg_vcc.h ] - VCC module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_VCC_H
#define EHVM_TYPES_CFG_VCC_H

/* type definitions */
#define NOUSE_VCC_INTERRUPT         (0xFFFFFFFFU)
#define VCC_EDGE_DETECTION_DISABLE    (0x00U)
#define VCC_EDGE_DETECTION_ENABLE    (0x01U)
#define NOUSE_VCC_EDGE_DETECTION    (0xFFFFU)

#define VCC_OVERWRITE_DISABLE      (0x00U)
#define VCC_OVERWRITE_ENABLE       (0x01U)

typedef ehvm_uint32_t ehvm_vcc_id_t;

typedef struct {
    ehvm_spid_t                           VccReceiverSpid;
    ehvm_uint32_t                              VccReceiveInterruptNumber;
    ehvm_uint32_t                              VccOverwriteInterruptNumber;
    ehvm_uint16_t                              VccEdgeRequest;
} ehvm_vcc_receiver_channel_t;

typedef struct {
    ehvm_uint32_t                              VccTransmitVMMask;
    ehvm_uint32_t                              VccTransmitInterruptNumber;
    ehvm_uint16_t                              VccEdgeEnable;
    ehvm_uint8_t                               VccNumOfReceiveVM;
    EhvmConst ehvm_vcc_receiver_channel_t*    VccReceiverChannel;
    ehvm_uint32_t                              VccReceiveVMMask;
    ehvm_uint32_t                              VccPacketSize;
    ehvm_uint8_t                               VccNumOfRingElement;
    ehvm_uint8_t                               VccOverwriteConfiguration;
} ehvm_vcc_channel_t;

typedef struct {
    ehvm_uint32_t                      VccReceiverMask;
    ehvm_uint32_t*                     VccTransmitDataPointer;
    ehvm_uint32_t                      VccTransmitDataLength;
    ehvm_uint32_t                      VccClearCompletionFlag;
} ehvm_vcc_ring_element_t;

typedef struct {
    ehvm_spid_t                   VccReceiverSpid;
    ehvm_uint32_t                      VccIndexOfRp;
    ehvm_uint32_t                      VccRingBufferStatus;
    ehvm_uint16_t                      VccId;
    ehvm_uint8_t                       VccRpUpdateFlag;
} ehvm_vcc_ring_buffer_t;

typedef struct {
    ehvm_vcc_ring_buffer_t**  list;
} ring_buffer_list_t;

typedef struct {
    ehvm_uint16_t                     VccNumOfVccId;
    EhvmConst ehvm_vcc_channel_t*     VccChannel;
    EhvmConst ring_buffer_list_t*     VccRingBufferList;
} ehvm_vcc_config_t;

#endif /* EHVM_TYPES_CFG_VCC_H */
