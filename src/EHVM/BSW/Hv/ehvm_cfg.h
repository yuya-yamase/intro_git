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
 [ ehvm_cfg.h ] - EHVM module's configuration header file
****************************************************************************/

#ifndef EHVM_CFG_H
#define EHVM_CFG_H

#include "ehvm.h"
#include "ehvm_cfg_pe0.h"
#include "ehvm_cfg_pe1.h"
#include "ehvm_cfg_pe2.h"
#include "ehvm_cfg_pe3.h"

#pragma ghs section rodata=".rodata.ehvm.cfg"

#define EHVM_INT_OFF                      ((ehvm_uint32_t)(0xFFFFFFFFU))

/* HVCM */
#define HVCM_NUM_OF_USE_HVC               (0x1BU)

/* VCC */
/* Number of VccId */
#define VCC_NUM_OF_VCCID                  (0x0015U)

/* Number of VccIds associated with SPID */
#define SPID0_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID1_NUM_OF_RECEIVED_VCCID       (0x0CU)
#define SPID2_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID3_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID4_NUM_OF_RECEIVED_VCCID       (0x0DU)
#define SPID5_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID6_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID7_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID8_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID9_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID10_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID11_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID12_NUM_OF_RECEIVED_VCCID       (0x0DU)
#define SPID13_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID14_NUM_OF_RECEIVED_VCCID       (0x0EU)
#define SPID15_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID16_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID17_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID18_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID19_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID20_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID21_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID22_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID23_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID24_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID25_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID26_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID27_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID28_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID29_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID30_NUM_OF_RECEIVED_VCCID       (0x01U)
#define SPID31_NUM_OF_RECEIVED_VCCID       (0x01U)

/* VCCID:0 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH0     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH0         (0x06U)
#define VCC_SIZE_OF_PACKET_CH0              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH0      (VCC_SIZE_OF_PACKET_CH0 / VCC_MESSAGE_ALIGN)

/* VCCID:1 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH1     (0x01U)
#define VCC_NUM_OF_RING_ELEMENT_CH1         (0x03U)
#define VCC_SIZE_OF_PACKET_CH1              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH1      (VCC_SIZE_OF_PACKET_CH1 / VCC_MESSAGE_ALIGN)

/* VCCID:2 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH2     (0x01U)
#define VCC_NUM_OF_RING_ELEMENT_CH2         (0x03U)
#define VCC_SIZE_OF_PACKET_CH2              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH2      (VCC_SIZE_OF_PACKET_CH2 / VCC_MESSAGE_ALIGN)

/* VCCID:3 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH3     (0x01U)
#define VCC_NUM_OF_RING_ELEMENT_CH3         (0x03U)
#define VCC_SIZE_OF_PACKET_CH3              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH3      (VCC_SIZE_OF_PACKET_CH3 / VCC_MESSAGE_ALIGN)

/* VCCID:4 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH4     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH4         (0x5AU)
#define VCC_SIZE_OF_PACKET_CH4              (0x00000048U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH4      (VCC_SIZE_OF_PACKET_CH4 / VCC_MESSAGE_ALIGN)

/* VCCID:5 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH5     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH5         (0x1EU)
#define VCC_SIZE_OF_PACKET_CH5              (0x00000048U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH5      (VCC_SIZE_OF_PACKET_CH5 / VCC_MESSAGE_ALIGN)

/* VCCID:6 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH6     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH6         (0x1EU)
#define VCC_SIZE_OF_PACKET_CH6              (0x00000048U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH6      (VCC_SIZE_OF_PACKET_CH6 / VCC_MESSAGE_ALIGN)

/* VCCID:7 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH7     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH7         (0x1EU)
#define VCC_SIZE_OF_PACKET_CH7              (0x00000048U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH7      (VCC_SIZE_OF_PACKET_CH7 / VCC_MESSAGE_ALIGN)

/* VCCID:8 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH8     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH8         (0x03U)
#define VCC_SIZE_OF_PACKET_CH8              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH8      (VCC_SIZE_OF_PACKET_CH8 / VCC_MESSAGE_ALIGN)

/* VCCID:9 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH9     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH9         (0x03U)
#define VCC_SIZE_OF_PACKET_CH9              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH9      (VCC_SIZE_OF_PACKET_CH9 / VCC_MESSAGE_ALIGN)

/* VCCID:10 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH10     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH10         (0x03U)
#define VCC_SIZE_OF_PACKET_CH10              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH10      (VCC_SIZE_OF_PACKET_CH10 / VCC_MESSAGE_ALIGN)

/* VCCID:11 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH11     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH11         (0x03U)
#define VCC_SIZE_OF_PACKET_CH11              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH11      (VCC_SIZE_OF_PACKET_CH11 / VCC_MESSAGE_ALIGN)

/* VCCID:12 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH12     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH12         (0x0FU)
#define VCC_SIZE_OF_PACKET_CH12              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH12      (VCC_SIZE_OF_PACKET_CH12 / VCC_MESSAGE_ALIGN)

/* VCCID:13 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH13     (0x01U)
#define VCC_NUM_OF_RING_ELEMENT_CH13         (0x0FU)
#define VCC_SIZE_OF_PACKET_CH13              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH13      (VCC_SIZE_OF_PACKET_CH13 / VCC_MESSAGE_ALIGN)

/* VCCID:14 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH14     (0x01U)
#define VCC_NUM_OF_RING_ELEMENT_CH14         (0x0FU)
#define VCC_SIZE_OF_PACKET_CH14              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH14      (VCC_SIZE_OF_PACKET_CH14 / VCC_MESSAGE_ALIGN)

/* VCCID:15 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH15     (0x02U)
#define VCC_NUM_OF_RING_ELEMENT_CH15         (0x0FU)
#define VCC_SIZE_OF_PACKET_CH15              (0x00000004U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH15      (VCC_SIZE_OF_PACKET_CH15 / VCC_MESSAGE_ALIGN)

/* VCCID:16 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH16     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH16         (0x03U)
#define VCC_SIZE_OF_PACKET_CH16              (0x00000100U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH16      (VCC_SIZE_OF_PACKET_CH16 / VCC_MESSAGE_ALIGN)

/* VCCID:17 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH17     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH17         (0x03U)
#define VCC_SIZE_OF_PACKET_CH17              (0x00000100U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH17      (VCC_SIZE_OF_PACKET_CH17 / VCC_MESSAGE_ALIGN)

/* VCCID:18 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH18     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH18         (0x03U)
#define VCC_SIZE_OF_PACKET_CH18              (0x00000100U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH18      (VCC_SIZE_OF_PACKET_CH18 / VCC_MESSAGE_ALIGN)

/* VCCID:19 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH19     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH19         (0x03U)
#define VCC_SIZE_OF_PACKET_CH19              (0x00000100U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH19      (VCC_SIZE_OF_PACKET_CH19 / VCC_MESSAGE_ALIGN)

/* VCCID:20 */
#define VCC_NUM_OF_RECEIVER_CHANNEL_CH20     (0x03U)
#define VCC_NUM_OF_RING_ELEMENT_CH20         (0x03U)
#define VCC_SIZE_OF_PACKET_CH20              (0x00000040U)
#define VCC_SIZE_OF_MESSAGE_BUFFER_CH20      (VCC_SIZE_OF_PACKET_CH20 / VCC_MESSAGE_ALIGN)


/* EM */
/* ContextId */
#define EM_CONTEXT_VM0_PE0             (0x00U)
#define EM_CONTEXT_VM1_PE0             (0x01U)
#define EM_CONTEXT_VM2_PE0             (0x02U)
#define EM_CONTEXT_VM3_PE0             (0x03U)
#define EM_CONTEXT_VM4_PE0             (0x04U)
#define EM_CONTEXT_VM5_PE0             (0x05U)
#define EM_CONTEXT_VM6_PE0             (0x06U)
#define EM_CONTEXT_VM7_PE0             (0x07U)
#define EM_CONTEXT_VM0_PE1             (0x10U)
#define EM_CONTEXT_VM1_PE1             (0x11U)
#define EM_CONTEXT_VM2_PE1             (0x12U)
#define EM_CONTEXT_VM3_PE1             (0x13U)
#define EM_CONTEXT_VM4_PE1             (0x14U)
#define EM_CONTEXT_VM5_PE1             (0x15U)
#define EM_CONTEXT_VM6_PE1             (0x16U)
#define EM_CONTEXT_VM7_PE1             (0x17U)
#define EM_CONTEXT_VM0_PE2             (0x20U)
#define EM_CONTEXT_VM1_PE2             (0x21U)
#define EM_CONTEXT_VM2_PE2             (0x22U)
#define EM_CONTEXT_VM3_PE2             (0x23U)
#define EM_CONTEXT_VM4_PE2             (0x24U)
#define EM_CONTEXT_VM5_PE2             (0x25U)
#define EM_CONTEXT_VM6_PE2             (0x26U)
#define EM_CONTEXT_VM7_PE2             (0x27U)
#define EM_CONTEXT_VM0_PE3             (0x30U)
#define EM_CONTEXT_VM1_PE3             (0x31U)
#define EM_CONTEXT_VM2_PE3             (0x32U)
#define EM_CONTEXT_VM3_PE3             (0x33U)
#define EM_CONTEXT_VM4_PE3             (0x34U)
#define EM_CONTEXT_VM5_PE3             (0x35U)
#define EM_CONTEXT_VM6_PE3             (0x36U)
#define EM_CONTEXT_VM7_PE3             (0x37U)

/* Number of EmId */
#define EM_NUM_OF_EMID                      (0x04U)

/* EMID:0 */
#define EM_NUM_OF_RECEIVER_CHANNEL_CH0      (0x01U)
#define EM_NUM_OF_RING_ELEMENT_CH0          (0x03U)
#define EM_SIZE_OF_PACKET_CH0               (EM_TOTAL_ERROR_MSG_SIZE_VM0_PE0)
#define EM_SIZE_OF_MESSAGE_BUFFER_CH0       (EM_ERROR_BUFFER_SIZE_VM0_PE0)

/* EMID:1 */
#define EM_NUM_OF_RECEIVER_CHANNEL_CH1      (0x01U)
#define EM_NUM_OF_RING_ELEMENT_CH1          (0x03U)
#define EM_SIZE_OF_PACKET_CH1               (EM_TOTAL_ERROR_MSG_SIZE_VM0_PE1)
#define EM_SIZE_OF_MESSAGE_BUFFER_CH1       (EM_ERROR_BUFFER_SIZE_VM0_PE1)

/* EMID:2 */
#define EM_NUM_OF_RECEIVER_CHANNEL_CH2      (0x01U)
#define EM_NUM_OF_RING_ELEMENT_CH2          (0x03U)
#define EM_SIZE_OF_PACKET_CH2               (EM_TOTAL_ERROR_MSG_SIZE_VM0_PE2)
#define EM_SIZE_OF_MESSAGE_BUFFER_CH2       (EM_ERROR_BUFFER_SIZE_VM0_PE2)

/* EMID:3 */
#define EM_NUM_OF_RECEIVER_CHANNEL_CH3      (0x01U)
#define EM_NUM_OF_RING_ELEMENT_CH3          (0x03U)
#define EM_SIZE_OF_PACKET_CH3               (EM_TOTAL_ERROR_MSG_SIZE_VM0_PE3)
#define EM_SIZE_OF_MESSAGE_BUFFER_CH3       (EM_ERROR_BUFFER_SIZE_VM0_PE3)


/* Num of Get Lock Component */
#define HVM_NUM_OF_GET_LOCK_COMPONENT       (0x02U)

#pragma ghs section rodata=default

extern ehvm_uint32_t ehvm_em_cbk_make_error_message( EhvmConstR ehvm_em_error_msg_t* errorMessageInfo, EhvmConstR ehvm_uint32_t messageSizemax, ehvm_uint32_t* EhvmConstR messagebuf );
extern ehvm_uint32_t ehvm_em_cbk_error_handling( ehvm_peid_t peId, ehvm_context_id_t contextId, EhvmConstR ehvm_uint32_t errorCause, EhvmConstR ehvm_uint32_t* EhvmConstR databuffer, EhvmConstR ehvm_uint32_t lenbytes );
extern void ehvm_em_cbk_transmit_error( ehvm_context_id_t contextId, EhvmConstR ehvm_uint32_t errorCause );

extern void ehvm_intm_ecm_error( void );

#endif /* EHVM_CFG_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-2-0-z0001                                        */
/****************************************************************************/

