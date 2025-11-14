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
 [ ehvm_types_cfg_em.h ] - EM module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_EM_H
#define EHVM_TYPES_CFG_EM_H

#define NOUSE_EM_INTERRUPT         (0xFFFFFFFFU)

#define CONVERT_SPID_MASK( spid )          ( (ehvm_uint32_t)0x01U << (spid) )

#define EM_ERROR_HEADDER_SIZE              (0x14U)
#define EM_MESSAGE_ALIGN                   (0x04U)

typedef struct {
    ehvm_uint32_t               timeStamp_high;
    ehvm_uint32_t               timeStamp_low;
    ehvm_uint32_t               errorInfo_1;
    ehvm_uint32_t               errorInfo_2;
    ehvm_uint32_t               errorCause;
    ehvm_context_id_t      contextId;
} ehvm_em_error_msg_t;

typedef ehvm_uint32_t (*ehvm_em_trigger_on_mk_msg_t)( EhvmConstR ehvm_em_error_msg_t* errorMessageInfo, EhvmConstR ehvm_uint32_t mesageSizemax, ehvm_uint32_t* EhvmConstR messagebuf );
typedef void (*ehvm_em_trigger_on_tx_err_t)( ehvm_context_id_t contextId, EhvmConstR ehvm_uint32_t errorCause );
typedef ehvm_uint32_t (*ehvm_em_trigger_on_err_handling_t)( ehvm_peid_t peId, ehvm_uint8_t contextID, EhvmConstR ehvm_uint32_t errorCause, EhvmConstR ehvm_uint32_t* EhvmConstR msgBuf, EhvmConstR ehvm_uint32_t msgSize );

typedef struct {
    ehvm_context_id_t                   EmContextId;
    ehvm_em_id_t                        EmId;
    ehvm_uint32_t                            EmMessageSize;
    ehvm_uint32_t*                           EmMessageStartAddress;
} ehvm_em_pe_context_t;

typedef struct {
    ehvm_uint32_t                            EmNumOfPeContext;
    EhvmConst ehvm_em_pe_context_t*         EmPeContextPtr;
} ehvm_em_pe_management_t;

typedef struct {
    ehvm_spid_t                         EmReceiverSpid;
    ehvm_uint32_t                            EmReceiveInterruptNumber;
} ehvm_em_receiver_channel_t;

typedef struct {
    ehvm_uint8_t                             EmNumOfReceiveVM;
    EhvmConst ehvm_em_receiver_channel_t*    EmReceiverChannel;
    ehvm_uint32_t                            EmReceiveVMMask;
    ehvm_uint32_t                            EmPacketSize;
    ehvm_uint8_t                             EmNumOfRingElement;
} ehvm_em_channel_t;

typedef struct {
    ehvm_uint8_t                             EmNumOfEmId;
    EhvmConst ehvm_em_channel_t*            EmChannel;
} ehvm_em_message_config_t;

typedef struct {
    ehvm_uint32_t                            EmNumOfPE;
    EhvmConst ehvm_em_pe_management_t*      EmPeManagementPtr;
    EhvmConst ehvm_em_message_config_t*     EmMessagePtr;
    ehvm_em_trigger_on_mk_msg_t         EmCallbackMakeMsgFnc;
    ehvm_em_trigger_on_err_handling_t   EmCallbackErrHandlingFnc;
    ehvm_em_trigger_on_tx_err_t         EmCallbackTransmitErrFnc;
} ehvm_em_config_t;


typedef struct {
    ehvm_uint32_t                            EmReceiverMask;
    ehvm_uint32_t*                           EmTransmitDataPointer;
    ehvm_uint32_t                            EmTransmitDataLength;
} ehvm_em_ring_element_t;

typedef struct {
    ehvm_uint32_t                            EmIndexOfRp;
} ehvm_em_ring_buffer_t;



#endif /* EHVM_TYPES_CFG_EM_H */
