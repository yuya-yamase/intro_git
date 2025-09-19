/* v0-2-1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CanIfProxy.c                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "CanIfProxy.h"
#include "Std_Types.h"
#include "chipcom.h"
#include "Can.h"
#include "VCan.h"
#include "CanIf.h"
#include "LIB.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CANIFPROXY_OK        ((U1)E_OK)
#define CANIFPROXY_NOT_OK    ((U1)E_NOT_OK)

#define CANIFPROXY_BUFF_TX_DATA_SIZE            ((U2)(45U))

#define CANIFPROXY_TRANSREQ_POS_PARAM           (0U)
#define CANIFPROXY_TRANSREQ_POS_PDUIDLEN        (1U)
#define CANIFPROXY_TRANSREQ_POS_PDUID1          (2U)
#define CANIFPROXY_TRANSREQ_POS_PDUID2          (3U)
#define CANIFPROXY_TRANSREQ_POS_SDULEN_LEN      (4U)
#define CANIFPROXY_TRANSREQ_POS_SDULEN1         (5U)
#define CANIFPROXY_TRANSREQ_POS_SDULEN2         (6U)
#define CANIFPROXY_TRANSREQ_POS_SDULEN3         (7U)
#define CANIFPROXY_TRANSREQ_POS_SDULEN4         (8U)
#define CANIFPROXY_TRANSREQ_POS_SDULENGTH       (9U)
#define CANIFPROXY_TRANSREQ_POS_DATA_OFFSET     (10U)
#define CANIFPROXY_TRANSREQ_POS_MDATA_LEN       (42U)
#define CANIFPROXY_TRANSREQ_POS_MDATA_CANID1    (43U)
#define CANIFPROXY_TRANSREQ_POS_MDATA_CANID2    (44U)
#define CANIFPROXY_TRANSREQ_POS_MDATA_CANID3    (45U)
#define CANIFPROXY_TRANSREQ_POS_MDATA_CANID4    (46U)

#define CANIFPROXY_RXIND_BUFF_SIZE              ((U2)45U)
#define CANIFPROXY_RXIND_QUEUE_SIZE             ((U2)30U)

#define CANIFPROXY_SHIFT_1BYTE          (8U)
#define CANIFPROXY_SHIFT_2BYTE          (16U)
#define CANIFPROXY_SHIFT_3BYTE          (24U)
#define CANIFPROXY_1BYTEMASK_HIGH       (0xF0U)
#define CANIFPROXY_1BYTEMASK_LOW        (0x0FU)
#define CANIFPROXY_2BYTEMASK_HIGH       (0xFF00U)
#define CANIFPROXY_2BYTEMASK_LOW        (0x00FFU)
#define CANIFPROXY_4BYTEMASK_1BYTE      (0x000000FFUL)
#define CANIFPROXY_4BYTEMASK_2BYTE      (0x0000FF00UL)
#define CANIFPROXY_4BYTEMASK_3BYTE      (0x00FF0000UL)
#define CANIFPROXY_4BYTEMASK_4BYTE      (0xFF000000UL)

#define CANIFPROXY_VCANRX_POS_PARAMNUM             (0U)
#define CANIFPROXY_VCANRX_POS_P1U1CTRLERLENGTH     (1U)
#define CANIFPROXY_VCANRX_POS_P1U1CTRLERDATA       (2U)
#define CANIFPROXY_VCANRX_POS_P2U1MSGBUFLENGTH     (3U)
#define CANIFPROXY_VCANRX_POS_P2U1MSGBUFDATA       (4U)
#define CANIFPROXY_VCANRX_POS_P3U4IDLENGTH         (5U)
#define CANIFPROXY_VCANRX_POS_P3U4IDDATA1          (6U)
#define CANIFPROXY_VCANRX_POS_P3U4IDDATA2          (7U)
#define CANIFPROXY_VCANRX_POS_P3U4IDDATA3          (8U)
#define CANIFPROXY_VCANRX_POS_P3U4IDDATA4          (9U)
#define CANIFPROXY_VCANRX_POS_P4U1LENGTHLENGTH     (10U)
#define CANIFPROXY_VCANRX_POS_P4U1LENGTHDATA       (11U)
#define CANIFPROXY_VCANRX_POS_P5U4DATALENGTH       (12U)
#define CANIFPROXY_VCANRX_POS_P5U4DATADATA0        (13U)

#define CANIFPROXY_SHIFT_1BYTE          (8U)
#define CANIFPROXY_SHIFT_2BYTE          (16U)
#define CANIFPROXY_SHIFT_3BYTE          (24U)
#define CANIFPROXY_POS_VCANDATA_OFFSET  (14U)
#define CANIFPROXY_VCANID_OFFSET        (4U)

#define CANIFPROXY_VCAN_VIRTUAL_CH_PROXY            ((U1)0x80U)
#define CANIFPROXY_VCAN_CONTROL                     ((U1)0x00U)
#define CANIFPROXY_VCAN_CONTROLLER                  (CANIFPROXY_VCAN_VIRTUAL_CH_PROXY | CANIFPROXY_VCAN_CONTROL)
#define CANIFPROXY_VCAN_MBOX                        ((U1)0x06U)
#define CANIFPROXY_VCAN_MESSAGEBUFFER               (CANIFPROXY_VCAN_MBOX)
#define CANIFPROXY_VCAN_DATA_BUFNUM                 ((U1)40U)
#define CANIFPROXY_VCAN_DATA_BUFNUM_MASK            ((U1)0x3FU)
#define CANIFPROXY_VCAN_DATA_BUFSIZE_TX             ((U1)0x40U)

#define CANIFPROXY_VCANRX_PARANUM                   ((U1)5U)
#define CANIFPROXY_VCANRX_P1U1CTRLERLENGTH          ((U1)1U)
#define CANIFPROXY_VCANRX_P2U1MSGBUFLENGTH          ((U1)1U)
#define CANIFPROXY_VCANRX_P3U4IDLENGTH              ((U1)4U)
#define CANIFPROXY_VCANRX_P4U1LENGTHDATA            ((U1)1U)
#define CANIFPROXY_VCANRX_P5U4DATALENGTH            ((U1)32U)

#define CANIFPROXY_RX_CANID_FRAMETYPE_11BIT_LIMIT   ((U4)0x00000800U)
#define CANIFPROXY_RX_CANID_FRAMETYPE_CANFD         ((U4)0x80000000U)   /* CANFD 31bit=ON */
#define CANIFPROXY_RX_EXTENDED_CANID_MASK           ((U4)0xFFFFFF00U)
#define CANIFPROXY_RX_CANID_18DAE1XX_CANFD          ((U4)0xD8DAE100U)   /* CANID + CanFDBit31 + ExtendedBit30 */
#define CANIFPROXY_RX_CANID_18DAE1XX_CLASSIC        ((U4)0x98DAE100U)   /* CANID + ExtendedBit30 */
#define CANIDPROXY_RX_CANID_FRAMETYPE_FUNCADDR      ((U4)0x98DB33F1U)   /* D(1101b)8DB33F1 or 9(1001b)8DB33F1 */
#define CANIFPROXY_RX_CANID_18DB33F1_CANFD          ((U4)0xD8DB33F1U)   /* CANID + CanFDBit31 + ExtendedBit30 */
#define CANIFPROXY_RX_CANID_18DB33F1_CLASSIC        ((U4)0x98DB33F1U)   /* CANID + ExtendedBit30 */
#define CANIFPROXY_RX_STANDARD_CANID_MASK           ((U4)0xFFFFFFF8U)   /* CANID Mask for 11bit Standard 708-70F */
#define CANIFPROXY_RX_CANID_00000708_070F           ((U4)0x00000708U)   /* CANID for 11bit Standard Physical 708-70F */
#define CANIFPROXY_RX_CANID_000007DF                ((U4)0x000007DFU)   /* CANID for 11bit Standard Functional 7DF */



/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static U1 CanIfProxy_IsSailTransferCanId(U4 u4_Canid);
static U1 CanIfProxy_RxInd_Queue_Push(U1* RxData);
static U1 CanIfProxy_RxInd_Queue_Pop(U1* RxData);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
U1  CanIfProxy_McuSpiTxData[CANIFPROXY_BUFF_TX_DATA_SIZE];
U1  CanIfProxy_VCanDataTx[CANIFPROXY_VCAN_DATA_BUFNUM][CANIFPROXY_VCAN_DATA_BUFSIZE_TX];
U1  CanIfProxy_VCanDataTx_index;

CanMsgType CanIfProxy_VCan_CanMsgTx[CANIFPROXY_VCAN_DATA_BUFNUM];

static U1 CanIfProxy_RxData[CANIFPROXY_RXIND_BUFF_SIZE];
typedef struct {
    U1 buffer[CANIFPROXY_RXIND_QUEUE_SIZE][CANIFPROXY_RXIND_BUFF_SIZE];
    U4 head;
    U4 tail;
    U1 full;
} CanIfProxy_RxInd_Queue_Type;
static CanIfProxy_RxInd_Queue_Type CanIfProxy_RxInd_Queue;

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
void CanIfProxy_Init( void )
{
    U4 u4_t_CopyCnt;
    U4 u4_t_QueueCnt;
    U1 u1_t_TxBuff_Cnt;

    LIB_memset(CanIfProxy_McuSpiTxData, 0x00, CANIFPROXY_BUFF_TX_DATA_SIZE);

    for( u1_t_TxBuff_Cnt=0; u1_t_TxBuff_Cnt < CANIFPROXY_VCAN_DATA_BUFNUM; u1_t_TxBuff_Cnt++ ) {
        LIB_memset(&(CanIfProxy_VCanDataTx[u1_t_TxBuff_Cnt][0]), 0x00, CANIFPROXY_VCAN_DATA_BUFSIZE_TX);
    }
    CanIfProxy_VCanDataTx_index = (uint8)0;

    for (u4_t_CopyCnt=0; u4_t_CopyCnt < CANIFPROXY_RXIND_BUFF_SIZE; u4_t_CopyCnt++) {
        CanIfProxy_RxData[u4_t_CopyCnt] = 0x00;
    }

    CanIfProxy_RxInd_Queue.head = 0;
    CanIfProxy_RxInd_Queue.tail = 0;
    CanIfProxy_RxInd_Queue.full = FALSE;
    for (u4_t_QueueCnt=0; u4_t_QueueCnt < CANIFPROXY_RXIND_QUEUE_SIZE; u4_t_QueueCnt++) {
        for (u4_t_CopyCnt=0; u4_t_CopyCnt < CANIFPROXY_RXIND_BUFF_SIZE; u4_t_CopyCnt++) {
            CanIfProxy_RxInd_Queue.buffer[u4_t_QueueCnt][u4_t_CopyCnt] = 0x00;
        }
    }

    return;
}

void CanIfProxy_Main( void )
{
    U1 u1_t_PopResult;
    U1 u1_t_PushResult = CANIFPROXY_NOT_OK;
    Std_ReturnType ChipCom_RetVal;
    
    u1_t_PopResult = CanIfProxy_RxInd_Queue_Pop(&(CanIfProxy_RxData[0]));
    while(u1_t_PopResult == CANIFPROXY_OK) {
        ChipCom_RetVal = ChipCom_Transmit(CHIPCOM_DATAID_CANTP_RXIND , CANIFPROXY_RXIND_BUFF_SIZE, &(CanIfProxy_RxData[0]));
        if (ChipCom_RetVal == E_NOT_OK) {
            u1_t_PushResult = CanIfProxy_RxInd_Queue_Push(&(CanIfProxy_RxData[0]));
            if (u1_t_PushResult == CANIFPROXY_NOT_OK) {
                /* [TBD]CanTp_TxConf(NG/OK) */
            }
            u1_t_PopResult = CANIFPROXY_NOT_OK;
        } else {
            u1_t_PopResult = CanIfProxy_RxInd_Queue_Pop(&(CanIfProxy_RxData[0]));
        }
    }
    return;
}

void CanIfProxy_Transmit(const U2 receive_len, const U1* const receive_data)
{
    U1   u1_t_TxData_Cnt;
    U1   ret;

    ret = CAN_PROC_NG;

    LIB_memset(&(CanIfProxy_VCanDataTx[CanIfProxy_VCanDataTx_index][0]), 0x00, CANIFPROXY_VCAN_DATA_BUFSIZE_TX);

    /* Length */
    CanIfProxy_VCan_CanMsgTx[CanIfProxy_VCanDataTx_index].u1Length = receive_data[CANIFPROXY_TRANSREQ_POS_SDULEN4];

    /* TxData */
    for (u1_t_TxData_Cnt=0; u1_t_TxData_Cnt < CanIfProxy_VCan_CanMsgTx[CanIfProxy_VCanDataTx_index].u1Length; u1_t_TxData_Cnt++) {
        CanIfProxy_VCanDataTx[CanIfProxy_VCanDataTx_index][u1_t_TxData_Cnt] = (U1)receive_data[CANIFPROXY_TRANSREQ_POS_DATA_OFFSET + u1_t_TxData_Cnt];
    }
    CanIfProxy_VCan_CanMsgTx[CanIfProxy_VCanDataTx_index].ptData = &(CanIfProxy_VCanDataTx[CanIfProxy_VCanDataTx_index][0]);

    /* CanId */
    CanIfProxy_VCan_CanMsgTx[CanIfProxy_VCanDataTx_index].u4Id = (U4)
        ((receive_data[CANIFPROXY_TRANSREQ_POS_MDATA_CANID1]) << CANIFPROXY_SHIFT_3BYTE ) |
        ((receive_data[CANIFPROXY_TRANSREQ_POS_MDATA_CANID2]) << CANIFPROXY_SHIFT_2BYTE ) |
        ((receive_data[CANIFPROXY_TRANSREQ_POS_MDATA_CANID3]) << CANIFPROXY_SHIFT_1BYTE ) |
        ((receive_data[CANIFPROXY_TRANSREQ_POS_MDATA_CANID4])  );

    ret = VCan_TxReq(CANIFPROXY_VCAN_CONTROLLER, CANIFPROXY_VCAN_MESSAGEBUFFER, &(CanIfProxy_VCan_CanMsgTx[CanIfProxy_VCanDataTx_index]) );
    if( ret == CAN_PROC_OK ){
        /* */
    }

    CanIfProxy_VCanDataTx_index++;
    if (CanIfProxy_VCanDataTx_index >= (CANIFPROXY_VCAN_DATA_BUFNUM - 1) ) {
        CanIfProxy_VCanDataTx_index = 0;
    }

    return;
}

/* uint8 CanIfProxy_RxIndication(uint8 u1Controller, uint8 u1MsgBuffer, CanConstR CanMsgType* ptMsg)*/
U1  VCan_URxIndication(U1 u1Controller, U1 u1MsgBuffer, CanConstR CanMsgType* ptMsg)
{
    U1      u1_t_PayloadCnt;
    U1      *ptDst;
    U1      *ptSrc;
    U1      u1_t_PayloadLength;
    U1      u1_t_ret;
    U4      u4_t_canid;
    U1      u1_t_SendSailFlag;
    Std_ReturnType ChipCom_RetVal;

    u4_t_canid     = ptMsg->u4Id;
    u1_t_PayloadLength = (ptMsg->u1Length);
    u1_t_ret = (U1)CAN_PROC_OK;

    LIB_memset(&CanIfProxy_McuSpiTxData[0], 0x00, CANIFPROXY_RXIND_BUFF_SIZE);

    u1_t_SendSailFlag = CanIfProxy_IsSailTransferCanId(u4_t_canid);
    if( ptMsg->u1Length > CANIFPROXY_VCANRX_P5U4DATALENGTH ){
        u1_t_SendSailFlag = FALSE;
    }

    if( u1_t_SendSailFlag == TRUE ) {
        /* Send to Sail,   */
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_PARAMNUM]         = CANIFPROXY_VCANRX_PARANUM;
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P1U1CTRLERLENGTH] = CANIFPROXY_VCANRX_P1U1CTRLERLENGTH;
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P1U1CTRLERDATA]   = u1Controller;
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P2U1MSGBUFLENGTH] = CANIFPROXY_VCANRX_P2U1MSGBUFLENGTH;
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P2U1MSGBUFDATA]   = u1MsgBuffer;
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P3U4IDLENGTH]     = CANIFPROXY_VCANRX_P3U4IDLENGTH;
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P3U4IDDATA1]      = (U1)((u4_t_canid & CANIFPROXY_4BYTEMASK_4BYTE) >> CANIFPROXY_SHIFT_3BYTE);
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P3U4IDDATA2]      = (U1)((u4_t_canid & CANIFPROXY_4BYTEMASK_3BYTE) >> CANIFPROXY_SHIFT_2BYTE);
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P3U4IDDATA3]      = (U1)((u4_t_canid & CANIFPROXY_4BYTEMASK_2BYTE) >> CANIFPROXY_SHIFT_1BYTE);
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P3U4IDDATA4]      = (U1)(u4_t_canid & CANIFPROXY_4BYTEMASK_1BYTE);
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P4U1LENGTHLENGTH] = CANIFPROXY_VCANRX_P4U1LENGTHDATA;
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P4U1LENGTHDATA]   = (U1)u1_t_PayloadLength;
        CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P5U4DATALENGTH]   = CANIFPROXY_VCANRX_P5U4DATALENGTH;

        /* Payload */
        ptSrc = (U1*)ptMsg->ptData;
        ptDst = (U1*)&CanIfProxy_McuSpiTxData[CANIFPROXY_VCANRX_POS_P5U4DATADATA0];
        for( u1_t_PayloadCnt=0; u1_t_PayloadCnt<u1_t_PayloadLength; u1_t_PayloadCnt++ ){
            *ptDst = *ptSrc;
            ++ptSrc;
            ++ptDst;
        }
        ChipCom_RetVal = ChipCom_Transmit(CHIPCOM_DATAID_CANTP_RXIND, CANIFPROXY_BUFF_TX_DATA_SIZE, &CanIfProxy_McuSpiTxData[0]);
        if (ChipCom_RetVal == E_NOT_OK) {
            CanIfProxy_RxInd_Queue_Push(&(CanIfProxy_McuSpiTxData[0]));
        };
        u1_t_ret = (U1)CAN_PROC_NG;
     }

     return( (U1)u1_t_ret );

}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
static U1 CanIfProxy_IsSailTransferCanId(U4 CanId)
{
    U1  u1_t_ret;
    U4  u4_t_CanId;

    u1_t_ret = FALSE;
    u4_t_CanId =CanId;

    if ((u4_t_CanId & CANIDPROXY_RX_CANID_FRAMETYPE_FUNCADDR) == CANIDPROXY_RX_CANID_FRAMETYPE_FUNCADDR) {
        /* Funcational Address */
        if (u4_t_CanId == CANIFPROXY_RX_CANID_18DB33F1_CANFD) {
            /* Extended FD */
            u1_t_ret = TRUE;
        } 
        else if (u4_t_CanId == CANIFPROXY_RX_CANID_18DB33F1_CLASSIC) {
            /* Extended Classic */
            u1_t_ret = TRUE;
        }
        else {
            /* do nothing */
        }
    }
    else if(u4_t_CanId == CANIFPROXY_RX_CANID_000007DF) {
            /* Functional Address */
            /* Standard Classic */
            u1_t_ret = TRUE;
    } else {
        /* Physical Address(not target functional CanId) */
        if( (u4_t_CanId & CANIFPROXY_RX_CANID_FRAMETYPE_CANFD) >= CANIFPROXY_RX_CANID_FRAMETYPE_11BIT_LIMIT) {
            /* 29bit Extended */
            if ((u4_t_CanId & CANIFPROXY_RX_EXTENDED_CANID_MASK) == CANIFPROXY_RX_CANID_18DAE1XX_CANFD) {
                /* Extended FD */
                u1_t_ret = TRUE;
            }
            else if ((u4_t_CanId & CANIFPROXY_RX_EXTENDED_CANID_MASK) == CANIFPROXY_RX_CANID_18DAE1XX_CLASSIC) {
                /* Extended Classic*/
                u1_t_ret = TRUE;
            }
            else {
                /* do nothing */
            }
        } else {
            /* 11bit Classical CAN2.0 */
            if ((u4_t_CanId & CANIFPROXY_RX_STANDARD_CANID_MASK) == CANIFPROXY_RX_CANID_00000708_070F) {
                u1_t_ret = TRUE;
            } 
            else {
                /* do nothing */
            }
        }
    }

    return u1_t_ret;
}

static U1 CanIfProxy_RxInd_Queue_Push(U1* RxData)
{
    U1 u1_t_RetVal = CANIFPROXY_NOT_OK;
    U4 u4_t_CopyCnt;
    u4_t_CopyCnt = 0;
    
    if (CanIfProxy_RxInd_Queue.full == FALSE) {
        for (u4_t_CopyCnt=0; u4_t_CopyCnt < CANIFPROXY_RXIND_BUFF_SIZE; u4_t_CopyCnt++) {
            CanIfProxy_RxInd_Queue.buffer[CanIfProxy_RxInd_Queue.head][u4_t_CopyCnt] = RxData[u4_t_CopyCnt];
        }
        CanIfProxy_RxInd_Queue.head = (CanIfProxy_RxInd_Queue.head + 1) % CANIFPROXY_RXIND_QUEUE_SIZE;

        if (CanIfProxy_RxInd_Queue.head == CanIfProxy_RxInd_Queue.tail ) {
            CanIfProxy_RxInd_Queue.full = TRUE; 
        }
        u1_t_RetVal = CANIFPROXY_OK;
    }

    return u1_t_RetVal;
}

static U1 CanIfProxy_RxInd_Queue_Pop(U1* RxData)
{
    U4 u4_t_CopyCnt;
    U1 u1_t_Ret;

    u4_t_CopyCnt = 0;
    u1_t_Ret = CANIFPROXY_NOT_OK;
    
    if ((CanIfProxy_RxInd_Queue.head == CanIfProxy_RxInd_Queue.tail) && (CanIfProxy_RxInd_Queue.full == FALSE)) {
        /* do not nothing */
        /* Buffer Empty */
    } else {
        for (u4_t_CopyCnt=0; u4_t_CopyCnt < CANIFPROXY_RXIND_BUFF_SIZE; u4_t_CopyCnt++) {
            RxData[u4_t_CopyCnt] = CanIfProxy_RxInd_Queue.buffer[CanIfProxy_RxInd_Queue.tail][u4_t_CopyCnt];
        }
        CanIfProxy_RxInd_Queue.tail = (CanIfProxy_RxInd_Queue.tail + 1) % CANIFPROXY_RXIND_QUEUE_SIZE;
        CanIfProxy_RxInd_Queue.full = FALSE;

        u1_t_Ret = CANIFPROXY_OK;
    }

    return u1_t_Ret;
}

/**** End of File ***********************************************************/
