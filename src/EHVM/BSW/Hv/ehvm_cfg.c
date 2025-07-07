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
 [ ehvm_cfg.c ] - EHVM module's configuration data file
****************************************************************************/

#include "ehvm.h"
#include "ehvm_cfg.h"
#include "ehvm_cfg_memory.h"

#if ( VCC_NUM_OF_VCCID > VCC_MAX_NUM_OF_VCCID )
#error VCCID exceeds the upper limit.
#endif

#pragma ghs section bss=".bss.ehvm.cfg.global"

static ehvm_uint32_t   CH0_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH0][VCC_SIZE_OF_MESSAGE_BUFFER_CH0];
static ehvm_uint32_t   CH1_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH1][VCC_SIZE_OF_MESSAGE_BUFFER_CH1];
static ehvm_uint32_t   CH2_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH2][VCC_SIZE_OF_MESSAGE_BUFFER_CH2];
static ehvm_uint32_t   CH3_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH3][VCC_SIZE_OF_MESSAGE_BUFFER_CH3];
static ehvm_uint32_t   CH4_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH4][VCC_SIZE_OF_MESSAGE_BUFFER_CH4];
static ehvm_uint32_t   CH5_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH5][VCC_SIZE_OF_MESSAGE_BUFFER_CH5];
static ehvm_uint32_t   CH6_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH6][VCC_SIZE_OF_MESSAGE_BUFFER_CH6];
static ehvm_uint32_t   CH7_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH7][VCC_SIZE_OF_MESSAGE_BUFFER_CH7];
static ehvm_uint32_t   CH8_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH8][VCC_SIZE_OF_MESSAGE_BUFFER_CH8];
static ehvm_uint32_t   CH9_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH9][VCC_SIZE_OF_MESSAGE_BUFFER_CH9];
static ehvm_uint32_t   CH10_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH10][VCC_SIZE_OF_MESSAGE_BUFFER_CH10];
static ehvm_uint32_t   CH11_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH11][VCC_SIZE_OF_MESSAGE_BUFFER_CH11];
static ehvm_uint32_t   CH12_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH12][VCC_SIZE_OF_MESSAGE_BUFFER_CH12];
static ehvm_uint32_t   CH13_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH13][VCC_SIZE_OF_MESSAGE_BUFFER_CH13];
static ehvm_uint32_t   CH14_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH14][VCC_SIZE_OF_MESSAGE_BUFFER_CH14];
static ehvm_uint32_t   CH15_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH15][VCC_SIZE_OF_MESSAGE_BUFFER_CH15];
static ehvm_uint32_t   CH16_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH16][VCC_SIZE_OF_MESSAGE_BUFFER_CH16];
static ehvm_uint32_t   CH17_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH17][VCC_SIZE_OF_MESSAGE_BUFFER_CH17];
static ehvm_uint32_t   CH18_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH18][VCC_SIZE_OF_MESSAGE_BUFFER_CH18];
static ehvm_uint32_t   CH19_Vcc_Msg_Buffer[VCC_NUM_OF_RING_ELEMENT_CH19][VCC_SIZE_OF_MESSAGE_BUFFER_CH19];

#pragma ghs section bss=default

#pragma ghs section bss=".bss.ehvm.cfg.global"

static ehvm_uint8_t   CH0_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH1_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH2_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH3_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH4_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH5_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH6_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH7_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH8_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH9_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH10_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH11_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH12_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH13_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH14_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH15_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH16_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH17_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH18_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH19_Vcc_Receive_SPID[VCC_MAX_VALUE_OF_SPID];

static ehvm_vcc_ring_buffer_t   CH0_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH0];
static ehvm_vcc_ring_buffer_t   CH1_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH1];
static ehvm_vcc_ring_buffer_t   CH2_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH2];
static ehvm_vcc_ring_buffer_t   CH3_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH3];
static ehvm_vcc_ring_buffer_t   CH4_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH4];
static ehvm_vcc_ring_buffer_t   CH5_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH5];
static ehvm_vcc_ring_buffer_t   CH6_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH6];
static ehvm_vcc_ring_buffer_t   CH7_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH7];
static ehvm_vcc_ring_buffer_t   CH8_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH8];
static ehvm_vcc_ring_buffer_t   CH9_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH9];
static ehvm_vcc_ring_buffer_t   CH10_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH10];
static ehvm_vcc_ring_buffer_t   CH11_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH11];
static ehvm_vcc_ring_buffer_t   CH12_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH12];
static ehvm_vcc_ring_buffer_t   CH13_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH13];
static ehvm_vcc_ring_buffer_t   CH14_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH14];
static ehvm_vcc_ring_buffer_t   CH15_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH15];
static ehvm_vcc_ring_buffer_t   CH16_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH16];
static ehvm_vcc_ring_buffer_t   CH17_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH17];
static ehvm_vcc_ring_buffer_t   CH18_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH18];
static ehvm_vcc_ring_buffer_t   CH19_Vcc_Ring_Buffer[VCC_NUM_OF_RECEIVER_CHANNEL_CH19];

static ehvm_vcc_ring_element_t   CH0_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH0];
static ehvm_vcc_ring_element_t   CH1_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH1];
static ehvm_vcc_ring_element_t   CH2_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH2];
static ehvm_vcc_ring_element_t   CH3_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH3];
static ehvm_vcc_ring_element_t   CH4_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH4];
static ehvm_vcc_ring_element_t   CH5_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH5];
static ehvm_vcc_ring_element_t   CH6_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH6];
static ehvm_vcc_ring_element_t   CH7_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH7];
static ehvm_vcc_ring_element_t   CH8_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH8];
static ehvm_vcc_ring_element_t   CH9_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH9];
static ehvm_vcc_ring_element_t   CH10_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH10];
static ehvm_vcc_ring_element_t   CH11_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH11];
static ehvm_vcc_ring_element_t   CH12_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH12];
static ehvm_vcc_ring_element_t   CH13_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH13];
static ehvm_vcc_ring_element_t   CH14_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH14];
static ehvm_vcc_ring_element_t   CH15_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH15];
static ehvm_vcc_ring_element_t   CH16_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH16];
static ehvm_vcc_ring_element_t   CH17_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH17];
static ehvm_vcc_ring_element_t   CH18_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH18];
static ehvm_vcc_ring_element_t   CH19_Vcc_Ring_Element_Info[VCC_NUM_OF_RING_ELEMENT_CH19];

#pragma ghs section bss=default

#pragma ghs section rodata=".rodata.ehvm.cfg"

static ehvm_uint32_t* EhvmConst VccMsgBufferManagement[VCC_NUM_OF_VCCID] = {
    CH0_Vcc_Msg_Buffer[0],
    CH1_Vcc_Msg_Buffer[0],
    CH2_Vcc_Msg_Buffer[0],
    CH3_Vcc_Msg_Buffer[0],
    CH4_Vcc_Msg_Buffer[0],
    CH5_Vcc_Msg_Buffer[0],
    CH6_Vcc_Msg_Buffer[0],
    CH7_Vcc_Msg_Buffer[0],
    CH8_Vcc_Msg_Buffer[0],
    CH9_Vcc_Msg_Buffer[0],
    CH10_Vcc_Msg_Buffer[0],
    CH11_Vcc_Msg_Buffer[0],
    CH12_Vcc_Msg_Buffer[0],
    CH13_Vcc_Msg_Buffer[0],
    CH14_Vcc_Msg_Buffer[0],
    CH15_Vcc_Msg_Buffer[0],
    CH16_Vcc_Msg_Buffer[0],
    CH17_Vcc_Msg_Buffer[0],
    CH18_Vcc_Msg_Buffer[0],
    CH19_Vcc_Msg_Buffer[0]
};

static ehvm_uint8_t* EhvmConst VccReceiveSPIDManagement[VCC_NUM_OF_VCCID] = {
    &CH0_Vcc_Receive_SPID[0],
    &CH1_Vcc_Receive_SPID[0],
    &CH2_Vcc_Receive_SPID[0],
    &CH3_Vcc_Receive_SPID[0],
    &CH4_Vcc_Receive_SPID[0],
    &CH5_Vcc_Receive_SPID[0],
    &CH6_Vcc_Receive_SPID[0],
    &CH7_Vcc_Receive_SPID[0],
    &CH8_Vcc_Receive_SPID[0],
    &CH9_Vcc_Receive_SPID[0],
    &CH10_Vcc_Receive_SPID[0],
    &CH11_Vcc_Receive_SPID[0],
    &CH12_Vcc_Receive_SPID[0],
    &CH13_Vcc_Receive_SPID[0],
    &CH14_Vcc_Receive_SPID[0],
    &CH15_Vcc_Receive_SPID[0],
    &CH16_Vcc_Receive_SPID[0],
    &CH17_Vcc_Receive_SPID[0],
    &CH18_Vcc_Receive_SPID[0],
    &CH19_Vcc_Receive_SPID[0]
};

static ehvm_vcc_ring_buffer_t* EhvmConst VccRingBufferManagement[VCC_NUM_OF_VCCID] = {
    &CH0_Vcc_Ring_Buffer[0],
    &CH1_Vcc_Ring_Buffer[0],
    &CH2_Vcc_Ring_Buffer[0],
    &CH3_Vcc_Ring_Buffer[0],
    &CH4_Vcc_Ring_Buffer[0],
    &CH5_Vcc_Ring_Buffer[0],
    &CH6_Vcc_Ring_Buffer[0],
    &CH7_Vcc_Ring_Buffer[0],
    &CH8_Vcc_Ring_Buffer[0],
    &CH9_Vcc_Ring_Buffer[0],
    &CH10_Vcc_Ring_Buffer[0],
    &CH11_Vcc_Ring_Buffer[0],
    &CH12_Vcc_Ring_Buffer[0],
    &CH13_Vcc_Ring_Buffer[0],
    &CH14_Vcc_Ring_Buffer[0],
    &CH15_Vcc_Ring_Buffer[0],
    &CH16_Vcc_Ring_Buffer[0],
    &CH17_Vcc_Ring_Buffer[0],
    &CH18_Vcc_Ring_Buffer[0],
    &CH19_Vcc_Ring_Buffer[0]
};

static ehvm_vcc_ring_element_t* EhvmConst VccRingElementManagement[VCC_NUM_OF_VCCID] = {
    &CH0_Vcc_Ring_Element_Info[0],
    &CH1_Vcc_Ring_Element_Info[0],
    &CH2_Vcc_Ring_Element_Info[0],
    &CH3_Vcc_Ring_Element_Info[0],
    &CH4_Vcc_Ring_Element_Info[0],
    &CH5_Vcc_Ring_Element_Info[0],
    &CH6_Vcc_Ring_Element_Info[0],
    &CH7_Vcc_Ring_Element_Info[0],
    &CH8_Vcc_Ring_Element_Info[0],
    &CH9_Vcc_Ring_Element_Info[0],
    &CH10_Vcc_Ring_Element_Info[0],
    &CH11_Vcc_Ring_Element_Info[0],
    &CH12_Vcc_Ring_Element_Info[0],
    &CH13_Vcc_Ring_Element_Info[0],
    &CH14_Vcc_Ring_Element_Info[0],
    &CH15_Vcc_Ring_Element_Info[0],
    &CH16_Vcc_Ring_Element_Info[0],
    &CH17_Vcc_Ring_Element_Info[0],
    &CH18_Vcc_Ring_Element_Info[0],
    &CH19_Vcc_Ring_Element_Info[0]
};

#pragma ghs section rodata=default

#pragma ghs section bss=".bss.ehvm.cfg.global"

static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid0[SPID0_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid1[SPID1_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid2[SPID2_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid3[SPID3_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid4[SPID4_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid5[SPID5_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid6[SPID6_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid7[SPID7_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid8[SPID8_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid9[SPID9_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid10[SPID10_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid11[SPID11_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid12[SPID12_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid13[SPID13_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid14[SPID14_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid15[SPID15_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid16[SPID16_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid17[SPID17_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid18[SPID18_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid19[SPID19_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid20[SPID20_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid21[SPID21_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid22[SPID22_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid23[SPID23_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid24[SPID24_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid25[SPID25_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid26[SPID26_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid27[SPID27_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid28[SPID28_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid29[SPID29_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid30[SPID30_NUM_OF_RECEIVED_VCCID];
static ehvm_vcc_ring_buffer_t *ehvm_vcc_ring_buffer_spid31[SPID31_NUM_OF_RECEIVED_VCCID];

#pragma ghs section bss=default

#pragma ghs section bss=".bss.ehvm.cfg.global"

/* EM */
static ehvm_uint32_t   CH0_Em_Msg_Buffer[EM_NUM_OF_RING_ELEMENT_CH0][EM_SIZE_OF_MESSAGE_BUFFER_CH0];
static ehvm_uint32_t   CH1_Em_Msg_Buffer[EM_NUM_OF_RING_ELEMENT_CH1][EM_SIZE_OF_MESSAGE_BUFFER_CH1];
static ehvm_uint32_t   CH2_Em_Msg_Buffer[EM_NUM_OF_RING_ELEMENT_CH2][EM_SIZE_OF_MESSAGE_BUFFER_CH2];
static ehvm_uint32_t   CH3_Em_Msg_Buffer[EM_NUM_OF_RING_ELEMENT_CH3][EM_SIZE_OF_MESSAGE_BUFFER_CH3];

static ehvm_uint8_t   CH0_Em_Receive_SPID[EM_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH1_Em_Receive_SPID[EM_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH2_Em_Receive_SPID[EM_MAX_VALUE_OF_SPID];
static ehvm_uint8_t   CH3_Em_Receive_SPID[EM_MAX_VALUE_OF_SPID];

static ehvm_em_ring_buffer_t   CH0_Em_Ring_Buffer[EM_NUM_OF_RECEIVER_CHANNEL_CH0];
static ehvm_em_ring_buffer_t   CH1_Em_Ring_Buffer[EM_NUM_OF_RECEIVER_CHANNEL_CH1];
static ehvm_em_ring_buffer_t   CH2_Em_Ring_Buffer[EM_NUM_OF_RECEIVER_CHANNEL_CH2];
static ehvm_em_ring_buffer_t   CH3_Em_Ring_Buffer[EM_NUM_OF_RECEIVER_CHANNEL_CH3];

static ehvm_em_ring_element_t   CH0_Em_Ring_Element_Info[EM_NUM_OF_RING_ELEMENT_CH0];
static ehvm_em_ring_element_t   CH1_Em_Ring_Element_Info[EM_NUM_OF_RING_ELEMENT_CH1];
static ehvm_em_ring_element_t   CH2_Em_Ring_Element_Info[EM_NUM_OF_RING_ELEMENT_CH2];
static ehvm_em_ring_element_t   CH3_Em_Ring_Element_Info[EM_NUM_OF_RING_ELEMENT_CH3];

#pragma ghs section bss=default

#pragma ghs section rodata=".rodata.ehvm.cfg"

static ehvm_uint32_t* EhvmConst EmMsgBufferManagement[EM_NUM_OF_EMID] = {
     CH0_Em_Msg_Buffer[0],
     CH1_Em_Msg_Buffer[0],
     CH2_Em_Msg_Buffer[0],
     CH3_Em_Msg_Buffer[0]
};

static ehvm_uint8_t* EhvmConst EmReceiveSPIDManagement[EM_NUM_OF_EMID] = {
     &CH0_Em_Receive_SPID[0],
     &CH1_Em_Receive_SPID[0],
     &CH2_Em_Receive_SPID[0],
     &CH3_Em_Receive_SPID[0]
};

static ehvm_em_ring_buffer_t* EhvmConst EmRingBufferManagement[EM_NUM_OF_EMID] = {
    &CH0_Em_Ring_Buffer[0],
    &CH1_Em_Ring_Buffer[0],
    &CH2_Em_Ring_Buffer[0],
    &CH3_Em_Ring_Buffer[0]
};

static ehvm_em_ring_element_t* EhvmConst EmRingElementManagement[EM_NUM_OF_EMID] = {
    &CH0_Em_Ring_Element_Info[0],
    &CH1_Em_Ring_Element_Info[0],
    &CH2_Em_Ring_Element_Info[0],
    &CH3_Em_Ring_Element_Info[0]
};

#pragma ghs section rodata=default

#pragma ghs section rodata=".rodata.ehvm.cfg"

static EhvmConst ring_buffer_list_t ring_buffer_list[VCC_MAX_VALUE_OF_SPID] = {
    { &ehvm_vcc_ring_buffer_spid0[0] },
    { &ehvm_vcc_ring_buffer_spid1[0] },
    { &ehvm_vcc_ring_buffer_spid2[0] },
    { &ehvm_vcc_ring_buffer_spid3[0] },
    { &ehvm_vcc_ring_buffer_spid4[0] },
    { &ehvm_vcc_ring_buffer_spid5[0] },
    { &ehvm_vcc_ring_buffer_spid6[0] },
    { &ehvm_vcc_ring_buffer_spid7[0] },
    { &ehvm_vcc_ring_buffer_spid8[0] },
    { &ehvm_vcc_ring_buffer_spid9[0] },
    { &ehvm_vcc_ring_buffer_spid10[0] },
    { &ehvm_vcc_ring_buffer_spid11[0] },
    { &ehvm_vcc_ring_buffer_spid12[0] },
    { &ehvm_vcc_ring_buffer_spid13[0] },
    { &ehvm_vcc_ring_buffer_spid14[0] },
    { &ehvm_vcc_ring_buffer_spid15[0] },
    { &ehvm_vcc_ring_buffer_spid16[0] },
    { &ehvm_vcc_ring_buffer_spid17[0] },
    { &ehvm_vcc_ring_buffer_spid18[0] },
    { &ehvm_vcc_ring_buffer_spid19[0] },
    { &ehvm_vcc_ring_buffer_spid20[0] },
    { &ehvm_vcc_ring_buffer_spid21[0] },
    { &ehvm_vcc_ring_buffer_spid22[0] },
    { &ehvm_vcc_ring_buffer_spid23[0] },
    { &ehvm_vcc_ring_buffer_spid24[0] },
    { &ehvm_vcc_ring_buffer_spid25[0] },
    { &ehvm_vcc_ring_buffer_spid26[0] },
    { &ehvm_vcc_ring_buffer_spid27[0] },
    { &ehvm_vcc_ring_buffer_spid28[0] },
    { &ehvm_vcc_ring_buffer_spid29[0] },
    { &ehvm_vcc_ring_buffer_spid30[0] },
    { &ehvm_vcc_ring_buffer_spid31[0] }
};

#pragma ghs section rodata=default

#pragma ghs section bss=".bss.ehvm.cfg.global"

static ehvm_vcc_info_t         VccInfoData[VCC_NUM_OF_VCCID];
static ehvm_em_info_t          EmInfoData[EM_NUM_OF_EMID];

#pragma ghs section bss=default

#pragma ghs section bss=".bss.ehvm.cfg.global"

static ehvm_uint32_t           HvcAccDenyList[HVCM_NUM_OF_USE_HVC];

#pragma ghs section bss=default

#pragma ghs section rodata=".rodata.ehvm.cfg"

/****************************************************************************************/
/* Hv4mHypervisorCallManagementConfig                                                   */
/****************************************************************************************/
static EhvmConst ehvm_hvcm_vm_acl_inf_t s_HvcmVmAclConfigInf[HVCM_NUM_OF_USE_HVC] = {
    {   /* EHVM_VCC_TRANSMIT */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VCC_RECEIVE */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VWDT_SET_MODE */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VWDT_SET_TRIGGER_CONDITION */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_EXIT */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_GET_RESET_FACTOR */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_EM_ERR_MSG_RECEIVE */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VCC_CLEAR */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VCC_GET_OVERWRITE_STATUS */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_HVC_SET_ACCESS_DENY_LIST */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_HVC_GET_ACCESS_DENY_LIST */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_SCH_SET_SCHEDULE_TABLE */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_SCH_GET_SCHEDULE_TABLE */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_ENABLE_SUPPRESSION */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_DISABLE_SUPPRESSION */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_GET_VM_STATUS_TABLE */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_RESET_VM */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VCC_CLEAR_CHANNEL */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_GET_WAKEUP_FACTOR */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_SET_WAKEUP_FACTOR */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_CLEAR_WAKEUP_FACTOR */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_ENABLE_WAKEUP_FACTOR */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_DISABLE_WAKEUP_FACTOR */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_VMM_GET_ALL_OTHER_VM_STATUS */
        (ehvm_uint32_t)0x00000001U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x01010101U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_SCH_DISABLE_VM_SWITCH */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_SCH_ENABLE_VM_SWITCH */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    },
    {   /* EHVM_UC_CALL_FUNCTION */
        (ehvm_uint32_t)0x01010101U,  /* hvcAclVmMask */
        (ehvm_uint32_t)0x00000001U   /* hvcFixedAclVmMask */
    }
};

static EhvmConst ehvm_uint8_t s_NumOfVmByPe[PEID_NUM] = {
    VM_NUM_PE0,
    VM_NUM_PE1,
    VM_NUM_PE2,
    VM_NUM_PE3
};

static EhvmConst ehvm_hvcm_config_t s_HvcmConfigData = {
    &s_HvcmVmAclConfigInf[0],  /* hvcmVmAclConfigInf */
    HVCM_NUM_OF_USE_HVC,       /* hvcmNumOfUseHvc */
    (ehvm_uint8_t)PEID_NUM,    /* hvcmNumOfPe */
    &s_NumOfVmByPe[0]          /* numOfVmByPe */
};

static EhvmConst ehvm_hvcm_info_t HvcmInfoData = {
    &s_HvcmConfigData,  /* hvcmConfigData */
    &HvcAccDenyList[0]  /* hvcAccDenyList */
};

/****************************************************************************************/
/* Hv4mVirtualCommunicationChannelConfig                                                */
/****************************************************************************************/
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH0[VCC_NUM_OF_RECEIVER_CHANNEL_CH0] = {
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH1[VCC_NUM_OF_RECEIVER_CHANNEL_CH1] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH2[VCC_NUM_OF_RECEIVER_CHANNEL_CH2] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH3[VCC_NUM_OF_RECEIVER_CHANNEL_CH3] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH4[VCC_NUM_OF_RECEIVER_CHANNEL_CH4] = {
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH5[VCC_NUM_OF_RECEIVER_CHANNEL_CH5] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH6[VCC_NUM_OF_RECEIVER_CHANNEL_CH6] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH7[VCC_NUM_OF_RECEIVER_CHANNEL_CH7] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH8[VCC_NUM_OF_RECEIVER_CHANNEL_CH8] = {
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH9[VCC_NUM_OF_RECEIVER_CHANNEL_CH9] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH10[VCC_NUM_OF_RECEIVER_CHANNEL_CH10] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH11[VCC_NUM_OF_RECEIVER_CHANNEL_CH11] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH12[VCC_NUM_OF_RECEIVER_CHANNEL_CH12] = {
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH13[VCC_NUM_OF_RECEIVER_CHANNEL_CH13] = {
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH14[VCC_NUM_OF_RECEIVER_CHANNEL_CH14] = {
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH15[VCC_NUM_OF_RECEIVER_CHANNEL_CH15] = {
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH16[VCC_NUM_OF_RECEIVER_CHANNEL_CH16] = {
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH17[VCC_NUM_OF_RECEIVER_CHANNEL_CH17] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH18[VCC_NUM_OF_RECEIVER_CHANNEL_CH18] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000EU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};
static EhvmConst ehvm_vcc_receiver_channel_t s_VccReceiver_CH19[VCC_NUM_OF_RECEIVER_CHANNEL_CH19] = {
    {
        0x00000001U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x00000004U,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    },
    {
        0x0000000CU,    /* VccReceiverSpid */
        NOUSE_VCC_INTERRUPT,           /* VccReceiveInterruptNumber */
        NOUSE_VCC_INTERRUPT,           /* VccOverwriteInterruptNumber */
        NOUSE_VCC_EDGE_DETECTION         /* VccEdgeRequest */
    }
};

static EhvmConst ehvm_vcc_channel_t s_VccChannelData[VCC_NUM_OF_VCCID] = {
    /* VCCID:0 */
    {
        0x00000002U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH0,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH0[0],             /* VccReceiverChannel */
        0x00005010U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH0,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH0,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:1 */
    {
        0x00000010U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH1,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH1[0],             /* VccReceiverChannel */
        0x00000002U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH1,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH1,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:2 */
    {
        0x00001000U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH2,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH2[0],             /* VccReceiverChannel */
        0x00000002U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH2,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH2,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:3 */
    {
        0x00004000U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH3,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH3[0],             /* VccReceiverChannel */
        0x00000002U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH3,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH3,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:4 */
    {
        0x00000002U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH4,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH4[0],             /* VccReceiverChannel */
        0x00005010U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH4,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH4,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:5 */
    {
        0x00000010U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH5,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH5[0],             /* VccReceiverChannel */
        0x00005002U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH5,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH5,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:6 */
    {
        0x00001000U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH6,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH6[0],             /* VccReceiverChannel */
        0x00004012U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH6,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH6,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:7 */
    {
        0x00004000U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH7,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH7[0],             /* VccReceiverChannel */
        0x00001012U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH7,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH7,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:8 */
    {
        0x00000002U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH8,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH8[0],             /* VccReceiverChannel */
        0x00005010U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH8,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH8,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:9 */
    {
        0x00000010U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH9,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH9[0],             /* VccReceiverChannel */
        0x00005002U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH9,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH9,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:10 */
    {
        0x00001000U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH10,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH10[0],             /* VccReceiverChannel */
        0x00004012U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH10,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH10,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:11 */
    {
        0x00004000U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH11,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH11[0],             /* VccReceiverChannel */
        0x00001012U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH11,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH11,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:12 */
    {
        0x00000002U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH12,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH12[0],             /* VccReceiverChannel */
        0x00005010U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH12,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH12,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:13 */
    {
        0x00000010U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH13,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH13[0],             /* VccReceiverChannel */
        0x00004000U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH13,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH13,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:14 */
    {
        0x00001000U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH14,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH14[0],             /* VccReceiverChannel */
        0x00004000U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH14,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH14,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:15 */
    {
        0x00004000U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH15,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH15[0],             /* VccReceiverChannel */
        0x00001010U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH15,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH15,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:16 */
    {
        0x00000002U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH16,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH16[0],             /* VccReceiverChannel */
        0x00005010U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH16,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH16,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:17 */
    {
        0x00000010U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH17,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH17[0],             /* VccReceiverChannel */
        0x00005002U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH17,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH17,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:18 */
    {
        0x00001000U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH18,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH18[0],             /* VccReceiverChannel */
        0x00004012U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH18,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH18,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    },
    /* VCCID:19 */
    {
        0x00004000U,                       /* VccTransmitVMMask */
        NOUSE_VCC_INTERRUPT,               /* VccTransmitInterruptNumber */
        VCC_EDGE_DETECTION_DISABLE,        /* VccEdgeEnable */
        VCC_NUM_OF_RECEIVER_CHANNEL_CH19,   /* VccNumOfReceiveVM */
        &s_VccReceiver_CH19[0],             /* VccReceiverChannel */
        0x00001012U,                       /* VccReceiveVMMask */
        VCC_SIZE_OF_PACKET_CH19,            /* VccPacketSize */
        VCC_NUM_OF_RING_ELEMENT_CH19,       /* VccNumOfRingElement */
        VCC_OVERWRITE_ENABLE              /* VccOverwriteConfiguration */
    }
};

static EhvmConst ehvm_vcc_config_t ehvmVccConfigData = {
    20U,                     /* VccNumOfVccId */
    &s_VccChannelData[0],   /* VccChannel */
    &ring_buffer_list[0]    /* VccRingBufferList */
};

/****************************************************************************************/
/* Hv4mErrorManagementConfigSet                                                         */
/****************************************************************************************/
static EhvmConst ehvm_em_receiver_channel_t em_Receiver_CH0[EM_NUM_OF_RECEIVER_CHANNEL_CH0] = {
    {
        0x00000001U,   /* receiver_SPID */
        NOUSE_EM_INTERRUPT         /* EmReceiveInterruptNumber */
    }
};
static EhvmConst ehvm_em_receiver_channel_t em_Receiver_CH1[EM_NUM_OF_RECEIVER_CHANNEL_CH1] = {
    {
        0x00000001U,   /* receiver_SPID */
        NOUSE_EM_INTERRUPT         /* EmReceiveInterruptNumber */
    }
};
static EhvmConst ehvm_em_receiver_channel_t em_Receiver_CH2[EM_NUM_OF_RECEIVER_CHANNEL_CH2] = {
    {
        0x00000001U,   /* receiver_SPID */
        NOUSE_EM_INTERRUPT         /* EmReceiveInterruptNumber */
    }
};
static EhvmConst ehvm_em_receiver_channel_t em_Receiver_CH3[EM_NUM_OF_RECEIVER_CHANNEL_CH3] = {
    {
        0x00000001U,   /* receiver_SPID */
        NOUSE_EM_INTERRUPT         /* EmReceiveInterruptNumber */
    }
};

static EhvmConst ehvm_em_channel_t em_channelData[EM_NUM_OF_EMID] = {
    /* EMID:0 */
    {
        EM_NUM_OF_RECEIVER_CHANNEL_CH0,         /* EmNumOfReceiveVM */
        &em_Receiver_CH0[0],                    /* EmReceiverChannel */
        0x00000002U,                            /* EmReceiveVMMask */
        EM_SIZE_OF_PACKET_CH0,                  /* EmPacketSize */
        EM_NUM_OF_RING_ELEMENT_CH0              /* EmNumOfRingElement */
     },
    /* EMID:1 */
    {
        EM_NUM_OF_RECEIVER_CHANNEL_CH1,         /* EmNumOfReceiveVM */
        &em_Receiver_CH1[0],                    /* EmReceiverChannel */
        0x00000002U,                            /* EmReceiveVMMask */
        EM_SIZE_OF_PACKET_CH1,                  /* EmPacketSize */
        EM_NUM_OF_RING_ELEMENT_CH1              /* EmNumOfRingElement */
     },
    /* EMID:2 */
    {
        EM_NUM_OF_RECEIVER_CHANNEL_CH2,         /* EmNumOfReceiveVM */
        &em_Receiver_CH2[0],                    /* EmReceiverChannel */
        0x00000002U,                            /* EmReceiveVMMask */
        EM_SIZE_OF_PACKET_CH2,                  /* EmPacketSize */
        EM_NUM_OF_RING_ELEMENT_CH2              /* EmNumOfRingElement */
     },
    /* EMID:3 */
    {
        EM_NUM_OF_RECEIVER_CHANNEL_CH3,         /* EmNumOfReceiveVM */
        &em_Receiver_CH3[0],                    /* EmReceiverChannel */
        0x00000002U,                            /* EmReceiveVMMask */
        EM_SIZE_OF_PACKET_CH3,                  /* EmPacketSize */
        EM_NUM_OF_RING_ELEMENT_CH3              /* EmNumOfRingElement */
     }
};

static EhvmConst ehvm_em_message_config_t em_messageData = {
    EM_NUM_OF_EMID,
    &em_channelData[0]
};

static EhvmConst ehvm_em_pe_context_t em_contextData_pe0[VM_NUM_PE0] = {
    {
        EM_CONTEXT_VM0_PE0,                 /* EmContextId */
        0x00000000U,                        /* EmId */
        EM_TOTAL_ERROR_MSG_SIZE_VM0_PE0,    /* EmMessageSize */
        &ehvm_em_err_msg_array_VM0_PE0[0]   /* EmMessageStartAddress */
    }
};
static EhvmConst ehvm_em_pe_context_t em_contextData_pe1[VM_NUM_PE1] = {
    {
        EM_CONTEXT_VM0_PE1,                 /* EmContextId */
        0x00000001U,                        /* EmId */
        EM_TOTAL_ERROR_MSG_SIZE_VM0_PE1,    /* EmMessageSize */
        &ehvm_em_err_msg_array_VM0_PE1[0]   /* EmMessageStartAddress */
    }
};
static EhvmConst ehvm_em_pe_context_t em_contextData_pe2[VM_NUM_PE2] = {
    {
        EM_CONTEXT_VM0_PE2,                 /* EmContextId */
        0x00000002U,                        /* EmId */
        EM_TOTAL_ERROR_MSG_SIZE_VM0_PE2,    /* EmMessageSize */
        &ehvm_em_err_msg_array_VM0_PE2[0]   /* EmMessageStartAddress */
    }
};
static EhvmConst ehvm_em_pe_context_t em_contextData_pe3[VM_NUM_PE3] = {
    {
        EM_CONTEXT_VM0_PE3,                 /* EmContextId */
        0x00000003U,                        /* EmId */
        EM_TOTAL_ERROR_MSG_SIZE_VM0_PE3,    /* EmMessageSize */
        &ehvm_em_err_msg_array_VM0_PE3[0]   /* EmMessageStartAddress */
    }
};

static EhvmConst ehvm_em_pe_management_t pe_managementData[PEID_NUM] = {
    {
        VM_NUM_PE0,                         /* EmNumOfPeContext */
        &em_contextData_pe0[0]              /* EmPeContextPtr */
    },
    {
        VM_NUM_PE1,                         /* EmNumOfPeContext */
        &em_contextData_pe1[0]              /* EmPeContextPtr */
    },
    {
        VM_NUM_PE2,                         /* EmNumOfPeContext */
        &em_contextData_pe2[0]              /* EmPeContextPtr */
    },
    {
        VM_NUM_PE3,                         /* EmNumOfPeContext */
        &em_contextData_pe3[0]              /* EmPeContextPtr */
    }
};

static EhvmConst ehvm_em_config_t ehvmEmConfigData = {
    PEID_NUM,               /* EmNumOfPE */
    &pe_managementData[0],  /* EmPeManagementPtr */
    &em_messageData,        /* EmMessagePtr */
    &ehvm_em_cbk_make_error_message,  /* EmCallbackMakeMsgFnc */
    &ehvm_em_cbk_error_handling,  /* EmCallbackErrHandlingFnc */
    &ehvm_em_cbk_transmit_error   /* EmCallbackTransmitErrFnc */
};

/****************************************************************************************/
/* Hv4mEmIntmConfig                                                                     */
/****************************************************************************************/
static EhvmConst ehvm_intm_common_config_t IntmCommonConfigData = {
    NOUSE_INTM_INTERRUPT,             /* intno */
    &ehvm_intm_ecm_error   /* IntmCallbackEcmErrFnc */
};

/****************************************************************************************/
/* ehvm_sch_PatternNumTable                                                             */
/****************************************************************************************/
static EhvmConst ehvm_uint8_t ehvm_sch_PatternNumTable[PEID_NUM] = {
    EHVM_SCH_NUM_OF_PATTERNS_PE0,
    EHVM_SCH_NUM_OF_PATTERNS_PE1,
    EHVM_SCH_NUM_OF_PATTERNS_PE2,
    EHVM_SCH_NUM_OF_PATTERNS_PE3
};

/****************************************************************************************/
/* Hv4mUserCalloutConfigSet                                                             */
/****************************************************************************************/

static EhvmConst ehvm_uc_config_t UcConfigData = {
    0U,                     /* NumOfFuncCfg */
    NULL_PTR                /* FuncConfig */
};

/****************************************************************************************/
/* ehvm_cfg_tbl_conmon                                                                  */
/****************************************************************************************/
EhvmConst ehvm_cfg_tbl_cmn_t ehvm_cfg_tbl_conmon =
{
    &ehvm_sch_PatternNumTable[0], /* SchPatternNumTable */
    &VccInfoData[0],              /* VccInfo */
    VccMsgBufferManagement,       /* Vcc_Msg_Buffer_Management */
    VccReceiveSPIDManagement,     /* Vcc_Receive_SPID_Management */
    VccRingBufferManagement,      /* Vcc_Ring_Buffer_Management */
    VccRingElementManagement,     /* Vcc_Ring_Element_Management */
    &ehvmVccConfigData,           /* VccConfigData */
    &EmInfoData[0],               /* EmInfo */
    EmMsgBufferManagement,        /* Em_Msg_Buffer_Management */
    EmReceiveSPIDManagement,      /* Em_Receive_SPID_Management */
    EmRingBufferManagement,       /* Em_Ring_Buffer_Management */
    EmRingElementManagement,      /* Em_Ring_Element_Management */
    &ehvmEmConfigData,            /* EmConfigData */
    &ehvmPbgConfigData,           /* ehvm_PbgConfigData */
    &ehvmHbgConfigData,           /* ehvm_HbgConfigData */
    &ehvmIbgConfigData,           /* ehvm_IbgConfigData */
    &ehvmDmagConfigData,          /* ehvm_DmagConfigData */
    &ehvmDtsgConfigData,          /* ehvm_DtsgConfigData */
    &ehvmIntc2gConfigData,        /* ehvm_Intc2gConfigData */
    &ehvmCrgConfigData,           /* ehvm_CrgConfigData */
    &ehvmSpidConfigData,          /* ehvm_SpidConfigData */
    &IntmCommonConfigData,        /* ehvm_IntmCommonConfigData */
    INTC2G_SWITCH_REGISTER,       /* ehvm_intc2g_switch_register */
    EHVM_INT_OFF,    /* vm_status_update_int_no */
    0U,  /* pwrgd_cnt_value_deep_stop */
    EM_CONTEXT_VM0_PE0,                  /* master_vm */
    0x00000000U,                  /* special_vm_mask */
    VWDT_ENABLE,                /* VWdtEnable */
    &HvcmInfoData,                /* HvcmInfo */
    &UcConfigData,                /* ehvm_UcConfig */
    6U                           /* ehvm_sch_disable_vm_switch_upper_margin */
};

#pragma ghs section rodata=default

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

