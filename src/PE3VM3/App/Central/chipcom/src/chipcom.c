/* v0-4-0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  chipcom.c                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "chipcom.h"
#include "aip_common.h"
#include "LIB.h"

#ifdef CHIPCOM_SAIL_SETTING
#include "CanIf.h"
#include "CanIf_Cbk.h"
#include "CanIfStub.h"
#include "CDD_DebugLog.h" /* CanIfStub Debug Code*/
#endif /* CHIPCOM_SAIL_SETTING */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_POS_TOTALLENGTH1    ((uint16)0x0008U)
#define CHIPCOM_POS_TOTALLENGTH2    ((uint16)0x0009U)
#define CHIPCOM_POS_SEQUENCENO1     ((uint16)0x000AU)
#define CHIPCOM_POS_SEQUENCENO2     ((uint16)0x000BU)
#define CHIPCOM_POS_SEQUENCENO3     ((uint16)0x000CU)
#define CHIPCOM_POS_SEQUENCENO4     ((uint16)0x000DU)
#define CHIPCOM_POS_USERDATA_OFFSET ((uint16)0x000EU)
#define CHIPCOM_RCV_FRM_MAX         ((uint16)(XSPI_FRM_MAX - 4U))
#define CHIPCOM_SND_FRM_MAX         ((uint16)(XSPI_FRM_MAX - 4U))
#define CHIPCOM_RCV_FRM_MAX_WORD    ((uint16)(XSPI_FRM_MAX_WORD - 1U))
#define CHIPCOM_SND_FRM_MAX_WORD    ((uint16)(XSPI_FRM_MAX_WORD - 1U))

#define CHIPCOM_NORXTIME_INITVAL                ((uint16)    0U)
#define CHIPCOM_NORXTIME_ADDVAL                 ((uint16)    5U)
#define CHIPCOM_NORXTIME_TIMEOUT                ((uint16)10150U)

#define CHIPCOM_BUFFER_INITVAL   	((uint8) 0x00U)
#define CHIPCOM_U4CNT_TO_U1IDX      (4U)

#define CHIPCOM_POS_LENGTH1_OFFSET  ((uint16)0x0001U)
#define CHIPCOM_POS_LENGTH2_OFFSET  ((uint16)0x0002U)
#define CHIPCOM_POS_DATA_OFFSET     ((uint16)0x0003U)
#define CHIPCOM_HEADER_LENGTH       ((uint16)0x0003U)

#define CHIPCOM_CANIFTRANS_POS_PDUID_DATA0  ((uint8)2U)
#define CHIPCOM_CANIFTRANS_POS_PDUID_DATA1  ((uint8)3U)

#define CHIPCOM_2BYTEMASK_HIGH      ((uint16)0xFF00U)
#define CHIPCOM_2BYTEMASK_LOW       ((uint16)0x00FFU)
#define CHIPCOM_4BYTEMASK_HIGHEST   ((uint32)0xFF000000U)
#define CHIPCOM_4BYTEMASK_HIGH      ((uint32)0x00FF0000U)
#define CHIPCOM_4BYTEMASK_LOW       ((uint32)0x0000FF00U)
#define CHIPCOM_4BYTEMASK_LOWEST    ((uint32)0x000000FFU)
#define CHIPCOM_SHIFT_1BYTE         (8U)
#define CHIPCOM_SHIFT_2BYTE         (16U)
#define CHIPCOM_SHIFT_3BYTE         (24U)

#define CHIPCOM_TXCONF_PDUIDQUEUE_SIZE  ((uint8)30U)
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void ChipCom_DispatchReceiveData(uint8* pReceiveData);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static uint8        ChipCom_SpiRxDataU1[CHIPCOM_RCV_FRM_MAX];
static uint8        ChipCom_SpiTxDataU1[CHIPCOM_SND_FRM_MAX];
static uint32       ChipCom_SpiRxDataU4[CHIPCOM_RCV_FRM_MAX_WORD];
static uint32       ChipCom_SpiTxDataU4[CHIPCOM_SND_FRM_MAX_WORD];

static uint32       ChipCom_SeqNumberRx;
static uint32       ChipCom_SeqNumberTx;

static uint16       ChipCom_SpiTxData_index;
static ChipCom_IpduStatusType   ChipCom_RxSts[SIGNAL_CHIPCOM_MAX];
static uint16                   ChipCom_NoRxTime[SIGNAL_CHIPCOM_MAX];   /* Time since last received data(ms) */

#ifdef CHIPCOM_SAIL_SETTING
static PduIdType    ChipCom_TxConfPduIdQueue[CHIPCOM_TXCONF_PDUIDQUEUE_SIZE];
static uint8        ChipCom_TxConfPduIdQueue_index;
static uint8        ChipCom_TxConfPduIdQueue_Num;

static uint8        ChipCom_TxConf_isTxConfBurstEnabled;
#endif /* CHIPCOM_SAIL_SETTING */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
void ChipCom_Init(void)
{
    uint8 i = 0, j = 0;
    uint8* pInitBuff = NULL_PTR;

    LIB_memset(&(ChipCom_SpiRxDataU1[0]), CHIPCOM_BUFFER_INITVAL, CHIPCOM_RCV_FRM_MAX);
    LIB_memset(&(ChipCom_SpiTxDataU1[0]), CHIPCOM_BUFFER_INITVAL, CHIPCOM_SND_FRM_MAX);
    LIB_memset((uint8 *)&(ChipCom_SpiRxDataU4[0]), CHIPCOM_BUFFER_INITVAL, CHIPCOM_RCV_FRM_MAX);
    LIB_memset((uint8 *)&(ChipCom_SpiTxDataU4[0]), CHIPCOM_BUFFER_INITVAL, CHIPCOM_SND_FRM_MAX);
    for (i = 0; i < CHIPCOM_PERIODICID_MAX; i++) {
        pInitBuff = PeriodicRelation[i].InitVal;
        if( PeriodicRelation[i].TxPos < CHIPCOM_POS_TX_EVENTDATA_OFFSET ) {
            for (j = 0; j < PeriodicRelation[i].DataLen; j++) {
                ChipCom_SpiTxDataU1[((PeriodicRelation[i].TxPos) + j)] = (pInitBuff[j]);
            }
        }
        if( PeriodicRelation[i].RxPos < CHIPCOM_POS_RX_EVENTDATA_OFFSET ) {
            for (j = 0; j < PeriodicRelation[i].DataLen; j++) {
                ChipCom_SpiRxDataU1[((PeriodicRelation[i].RxPos) + j)] = (pInitBuff[j]);
            }
        }
    }

    ChipCom_SeqNumberRx = 0;
    ChipCom_SeqNumberTx = 0;

    for (i = 0; i < SIGNAL_CHIPCOM_MAX; i++) {
        ChipCom_RxSts[i] = CHIPCOM_NO_RX;
        ChipCom_NoRxTime[i] = CHIPCOM_NORXTIME_INITVAL;
    }

    ChipCom_SpiTxData_index = CHIPCOM_POS_TX_EVENTDATA_OFFSET;

#ifdef CHIPCOM_SAIL_SETTING
    LIB_memset((uint8 *)&(ChipCom_TxConfPduIdQueue[0]), CHIPCOM_BUFFER_INITVAL, CHIPCOM_TXCONF_PDUIDQUEUE_SIZE);
    ChipCom_TxConfPduIdQueue_index = 0;
    ChipCom_TxConfPduIdQueue_Num = 0;
    ChipCom_TxConf_isTxConfBurstEnabled = FALSE;
#endif /* CHIPCOM_SAIL_SETTING */

    return;
}

void ChipCom_MainRx(void)
{
    uint8 SpiRead_Result;
    uint16 RxLoopCnt;
    uint16 PduIdCnt;
#ifdef CHIPCOM_SAIL_SETTING
    uint8 u1t_TxConf_Cnt;
#endif /* CHIPCOM_SAIL_SETTING */

    /* SPI Read */
    SpiRead_Result = xspi_Read(XSPI_CH_03, &(ChipCom_SpiRxDataU4[0]), (uint32)CHIPCOM_RCV_FRM_MAX_WORD);
    if (SpiRead_Result == XSPI_OK)
    {
        /* Convert U4 array to U1 */
        CHIPCOM_DISABLE_INTERRUPT();
        for (RxLoopCnt = 0; RxLoopCnt < CHIPCOM_SND_FRM_MAX_WORD; RxLoopCnt++) {
            ChipCom_SpiRxDataU1[(RxLoopCnt * CHIPCOM_U4CNT_TO_U1IDX)]   = (uint8)(ChipCom_SpiRxDataU4[RxLoopCnt]  & CHIPCOM_4BYTEMASK_LOWEST);
            ChipCom_SpiRxDataU1[(RxLoopCnt * CHIPCOM_U4CNT_TO_U1IDX)+1] = (uint8)((ChipCom_SpiRxDataU4[RxLoopCnt] & CHIPCOM_4BYTEMASK_LOW)     >> CHIPCOM_SHIFT_1BYTE);
            ChipCom_SpiRxDataU1[(RxLoopCnt * CHIPCOM_U4CNT_TO_U1IDX)+2] = (uint8)((ChipCom_SpiRxDataU4[RxLoopCnt] & CHIPCOM_4BYTEMASK_HIGH)    >> CHIPCOM_SHIFT_2BYTE);
            ChipCom_SpiRxDataU1[(RxLoopCnt * CHIPCOM_U4CNT_TO_U1IDX)+3] = (uint8)((ChipCom_SpiRxDataU4[RxLoopCnt] & CHIPCOM_4BYTEMASK_HIGHEST) >> CHIPCOM_SHIFT_3BYTE);
        }
        
        ChipCom_SeqNumberRx = (uint32)
                     ((ChipCom_SpiRxDataU1[CHIPCOM_POS_SEQUENCENO1]) << CHIPCOM_SHIFT_3BYTE ) |
                     ((ChipCom_SpiRxDataU1[CHIPCOM_POS_SEQUENCENO2]) << CHIPCOM_SHIFT_2BYTE ) |
                     ((ChipCom_SpiRxDataU1[CHIPCOM_POS_SEQUENCENO3]) << CHIPCOM_SHIFT_1BYTE ) |
                     ((ChipCom_SpiRxDataU1[CHIPCOM_POS_SEQUENCENO4])  );

        for (PduIdCnt = 0; PduIdCnt < SIGNAL_CHIPCOM_MAX; PduIdCnt++) {
            ChipCom_RxSts[PduIdCnt] = CHIPCOM_TRX_START;
            ChipCom_NoRxTime[PduIdCnt] = CHIPCOM_NORXTIME_INITVAL;
        }
        CHIPCOM_ENABLE_INTERRUPT();

        ChipCom_DispatchReceiveData(&(ChipCom_SpiRxDataU1[0U]));
#ifdef CHIPCOM_SAIL_SETTING
        if (ChipCom_TxConf_isTxConfBurstEnabled == TRUE) {
            /* Send All TxConfirmation When RxInd receive Task */
            if (ChipCom_TxConfPduIdQueue_Num > 0) {
                for(u1t_TxConf_Cnt=0; u1t_TxConf_Cnt < ChipCom_TxConfPduIdQueue_Num; u1t_TxConf_Cnt++) {
                    CanIfStub_TxConfirmation(ChipCom_TxConfPduIdQueue[u1t_TxConf_Cnt]);
                }
                LIB_memset((uint8 *)&(ChipCom_TxConfPduIdQueue[0]), CHIPCOM_BUFFER_INITVAL, CHIPCOM_TXCONF_PDUIDQUEUE_SIZE);
                ChipCom_TxConfPduIdQueue_index = 0;
                ChipCom_TxConfPduIdQueue_Num = 0;
            }
        }
#endif /* CHIPCOM_SAIL_SETTING */
    }
    else {
        for (PduIdCnt = 0; PduIdCnt < SIGNAL_CHIPCOM_MAX; PduIdCnt++) {
            if ( ChipCom_RxSts[PduIdCnt] == CHIPCOM_TRX_START) {
                if (ChipCom_NoRxTime[PduIdCnt] < (CHIPCOM_NORXTIME_TIMEOUT)) {
                    ChipCom_NoRxTime[PduIdCnt] += CHIPCOM_NORXTIME_ADDVAL;
                }
                if (ChipCom_NoRxTime[PduIdCnt] >= CHIPCOM_NORXTIME_TIMEOUT) {
                    ChipCom_RxSts[PduIdCnt] = CHIPCOM_TIMEOUT;
                }
            }
        }
    }

    return;
}

void ChipCom_MainTx(void)
{
    uint8 SpiState;
    uint8 SpiWrite_Result;
    uint16 TxLoopCnt;
#ifdef CHIPCOM_SAIL_SETTING
    uint8 u1t_TxConf_Cnt;

    if (ChipCom_TxConf_isTxConfBurstEnabled == TRUE) {
        /* Send All TxConfirmation When RxInd receive Task */
        if (ChipCom_TxConfPduIdQueue_Num > 0) {
            for(u1t_TxConf_Cnt=0; u1t_TxConf_Cnt < ChipCom_TxConfPduIdQueue_Num; u1t_TxConf_Cnt++) {
                CanIfStub_TxConfirmation(ChipCom_TxConfPduIdQueue[u1t_TxConf_Cnt]);
            }
            LIB_memset((uint8 *)&(ChipCom_TxConfPduIdQueue[0]), CHIPCOM_BUFFER_INITVAL, CHIPCOM_TXCONF_PDUIDQUEUE_SIZE);
            ChipCom_TxConfPduIdQueue_index = 0;
            ChipCom_TxConfPduIdQueue_Num = 0;
        }
        ChipCom_TxConf_isTxConfBurstEnabled = FALSE;
    }
#endif /* CHIPCOM_SAIL_SETTING */

    SpiState = xspi_GetCondition(XSPI_CH_03);
    if ((SpiState == XSPI_DCOND_IDLE) || (SpiState == XSPI_DCOND_TRANSMIT)) {
        /* Disable Interrupt  */
        CHIPCOM_DISABLE_INTERRUPT();
        ChipCom_SpiTxDataU1[CHIPCOM_POS_TOTALLENGTH1] = (uint8)((ChipCom_SpiTxData_index & CHIPCOM_2BYTEMASK_HIGH) >> CHIPCOM_SHIFT_1BYTE);   /* Total Length High byte */
        ChipCom_SpiTxDataU1[CHIPCOM_POS_TOTALLENGTH2] = (uint8)((ChipCom_SpiTxData_index & CHIPCOM_2BYTEMASK_LOW));                           /* Total Length Low byte */

        /* Convert U1 array to U4 */
        for (TxLoopCnt = 0; TxLoopCnt < CHIPCOM_SND_FRM_MAX_WORD; TxLoopCnt++) {
            ChipCom_SpiTxDataU4[TxLoopCnt]  = (((uint32)ChipCom_SpiTxDataU1[(TxLoopCnt * CHIPCOM_U4CNT_TO_U1IDX)    ]                       ) & CHIPCOM_4BYTEMASK_LOWEST);
            ChipCom_SpiTxDataU4[TxLoopCnt] |= (((uint32)ChipCom_SpiTxDataU1[(TxLoopCnt * CHIPCOM_U4CNT_TO_U1IDX) + 1] << CHIPCOM_SHIFT_1BYTE) & CHIPCOM_4BYTEMASK_LOW);
            ChipCom_SpiTxDataU4[TxLoopCnt] |= (((uint32)ChipCom_SpiTxDataU1[(TxLoopCnt * CHIPCOM_U4CNT_TO_U1IDX) + 2] << CHIPCOM_SHIFT_2BYTE) & CHIPCOM_4BYTEMASK_HIGH);
            ChipCom_SpiTxDataU4[TxLoopCnt] |= (((uint32)ChipCom_SpiTxDataU1[(TxLoopCnt * CHIPCOM_U4CNT_TO_U1IDX) + 3] << CHIPCOM_SHIFT_3BYTE) & CHIPCOM_4BYTEMASK_HIGHEST);
        }

        /* SPI Write */
        SpiWrite_Result = xspi_Write(XSPI_CH_03, &(ChipCom_SpiTxDataU4[0]), (uint32)CHIPCOM_RCV_FRM_MAX_WORD);
        if (SpiWrite_Result == XSPI_NG)
        {
            /* ToDo: Invalid Procedure */
        } else {
            /* Clear Tx Event Buffer */
            LIB_memset(&(ChipCom_SpiTxDataU1[CHIPCOM_POS_TX_EVENTDATA_OFFSET]), CHIPCOM_BUFFER_INITVAL, (CHIPCOM_SND_FRM_MAX-CHIPCOM_POS_TX_EVENTDATA_OFFSET));
            ChipCom_SpiTxData_index = CHIPCOM_POS_TX_EVENTDATA_OFFSET;

            /* Send Counter(Wrap Around) */ 
            ChipCom_SeqNumberTx++;
            ChipCom_SpiTxDataU1[CHIPCOM_POS_SEQUENCENO1] = (uint8)((ChipCom_SeqNumberTx & CHIPCOM_4BYTEMASK_HIGHEST) >> CHIPCOM_SHIFT_3BYTE);
            ChipCom_SpiTxDataU1[CHIPCOM_POS_SEQUENCENO2] = (uint8)((ChipCom_SeqNumberTx & CHIPCOM_4BYTEMASK_HIGH   ) >> CHIPCOM_SHIFT_2BYTE);
            ChipCom_SpiTxDataU1[CHIPCOM_POS_SEQUENCENO3] = (uint8)((ChipCom_SeqNumberTx & CHIPCOM_4BYTEMASK_LOW    ) >> CHIPCOM_SHIFT_1BYTE);
            ChipCom_SpiTxDataU1[CHIPCOM_POS_SEQUENCENO4] = (uint8)((ChipCom_SeqNumberTx & CHIPCOM_4BYTEMASK_LOWEST )                       );
#ifdef CHIPCOM_SAIL_SETTING
            /* Send TxConfirmation */
            if (ChipCom_TxConfPduIdQueue_Num > 0) {
                for(u1t_TxConf_Cnt=0; u1t_TxConf_Cnt < ChipCom_TxConfPduIdQueue_Num; u1t_TxConf_Cnt++) {
                    CanIfStub_TxConfirmation(ChipCom_TxConfPduIdQueue[u1t_TxConf_Cnt]);
                }
                LIB_memset((uint8 *)&(ChipCom_TxConfPduIdQueue[0]), CHIPCOM_BUFFER_INITVAL, CHIPCOM_TXCONF_PDUIDQUEUE_SIZE);
                ChipCom_TxConfPduIdQueue_index = 0;
                ChipCom_TxConfPduIdQueue_Num = 0;
            }
#endif /* CHIPCOM_SAIL_SETTING */
        }

        /* Enable Interrupt */
        CHIPCOM_ENABLE_INTERRUPT();
    }

    return;
}

Std_ReturnType  ChipCom_Transmit(const uint8 data_id, const uint16 transreq_len, const uint8* const transreq_data)
{
    uint16 u2t_TxDataCount;
    Std_ReturnType Ret = E_NOT_OK;
#ifdef CHIPCOM_SAIL_SETTING
    uint16 u2t_PduId;
#endif /* CHIPCOM_SAIL_SETTING */

    /* Disable Interrupt */
    CHIPCOM_DISABLE_INTERRUPT();
    
    if (ChipCom_SpiTxData_index < CHIPCOM_SND_FRM_MAX) {
        if (data_id < CHIPCOM_DATAID_MAX) {
            /* Review Guard Condition for Multiframe */
            if ((CHIPCOM_HEADER_LENGTH + transreq_len) <= (CHIPCOM_SND_FRM_MAX - ChipCom_SpiTxData_index)) {
                /* Common Valid Data ID */
                ChipCom_SpiTxDataU1[ChipCom_SpiTxData_index] = data_id;
                ChipCom_SpiTxData_index++;
                ChipCom_SpiTxDataU1[ChipCom_SpiTxData_index] = (uint8)((transreq_len & CHIPCOM_2BYTEMASK_HIGH) >> CHIPCOM_SHIFT_1BYTE);
                ChipCom_SpiTxData_index++;
                ChipCom_SpiTxDataU1[ChipCom_SpiTxData_index] = (uint8)(transreq_len & CHIPCOM_2BYTEMASK_LOW);
                ChipCom_SpiTxData_index++;
                
                for (u2t_TxDataCount = 0; u2t_TxDataCount < transreq_len; u2t_TxDataCount++) {
                    ChipCom_SpiTxDataU1[ChipCom_SpiTxData_index + u2t_TxDataCount] = transreq_data[u2t_TxDataCount];
                }
                ChipCom_SpiTxData_index += u2t_TxDataCount;

#ifdef CHIPCOM_SAIL_SETTING
                if (data_id == CHIPCOM_DATAID_CANIFPROXY_TRANSMIT) {
                    u2t_PduId = (uint16)((transreq_data[CHIPCOM_CANIFTRANS_POS_PDUID_DATA0]) << CHIPCOM_SHIFT_1BYTE);
                    u2t_PduId = u2t_PduId | (uint16)(transreq_data[CHIPCOM_CANIFTRANS_POS_PDUID_DATA1]);
                    if (ChipCom_TxConfPduIdQueue_Num < (CHIPCOM_TXCONF_PDUIDQUEUE_SIZE - 1)) {
                        ChipCom_TxConfPduIdQueue[ChipCom_TxConfPduIdQueue_index] = u2t_PduId;
                        ChipCom_TxConfPduIdQueue_index++;
                        ChipCom_TxConfPduIdQueue_Num++;
                    }
                }
#endif /* CHIPCOM_SAIL_SETTING */
                Ret = E_OK;
            }
        }
    }
    /* Enable Interrupt */
    CHIPCOM_ENABLE_INTERRUPT();
    
    return (Ret);
}

Std_ReturnType ChipCom_SetPeriodicTxData(const uint8 periodic_id, const uint16 trans_len, const uint8* const trans_data)
{
    Std_ReturnType Ret = E_NOT_OK;
    uint16 i = 0;

    if (periodic_id < CHIPCOM_PERIODICID_MAX) {
        if (PeriodicRelation[periodic_id].TxPos < CHIPCOM_POS_TX_EVENTDATA_OFFSET) {
            if (trans_len ==  PeriodicRelation[periodic_id].DataLen){
                CHIPCOM_DISABLE_INTERRUPT();
                for (i = 0; i < PeriodicRelation[periodic_id].DataLen; i++) {
                    ChipCom_SpiTxDataU1[(PeriodicRelation[periodic_id].TxPos +i)] = trans_data[i];
                }
                CHIPCOM_ENABLE_INTERRUPT();
                Ret = E_OK;
            }
        }
    }

    return Ret;
}
Std_ReturnType ChipCom_GetPeriodicRxData(const uint8 periodic_id, uint16* receive_len, uint8* receive_data, uint32* receive_counter)
{
    Std_ReturnType Ret = E_NOT_OK;
    uint16 i = 0;

    if (periodic_id < CHIPCOM_PERIODICID_MAX) {
        if (PeriodicRelation[periodic_id].RxPos < CHIPCOM_POS_RX_EVENTDATA_OFFSET) {
            CHIPCOM_DISABLE_INTERRUPT();
            *receive_len = PeriodicRelation[periodic_id].DataLen;
            for (i = 0; i < PeriodicRelation[periodic_id].DataLen; i++) {
                receive_data[i] = ChipCom_SpiRxDataU1[(PeriodicRelation[periodic_id].RxPos +i)];
            }
            *receive_counter = ChipCom_SeqNumberRx;
            CHIPCOM_ENABLE_INTERRUPT();
            Ret = E_OK;
        }
    }

    return Ret;
}

ChipCom_IpduStatusType ChipCom_GetIPDUStatus( ChipCom_PduIdType ChipCom_PduId )
{
    ChipCom_IpduStatusType RxDataStatus;
    RxDataStatus = CHIPCOM_NO_RX;

    if (ChipCom_PduId < SIGNAL_CHIPCOM_MAX) {
        RxDataStatus = ChipCom_RxSts[ChipCom_PduId];
    }

    return RxDataStatus;
}

uint16 ChipCom_GetTxSize(void)
{
    return (CHIPCOM_SND_FRM_MAX - ChipCom_SpiTxData_index);
}

void ChipCom_Nop(const uint16 receive_len, const uint8* const receive_data)
{
    /* NOP */
    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
static void ChipCom_DispatchReceiveData(uint8* pReceiveData)
{
    uint8 DataId;
    uint16 TotalLength;
    uint16 PayloadLength;
    uint16 i = CHIPCOM_POS_RX_EVENTDATA_OFFSET;

    TotalLength = (pReceiveData[CHIPCOM_POS_TOTALLENGTH1] << CHIPCOM_SHIFT_1BYTE);
    TotalLength = (TotalLength | pReceiveData[CHIPCOM_POS_TOTALLENGTH2]);

    if (TotalLength <= CHIPCOM_RCV_FRM_MAX) {
        while (i < TotalLength) {
            DataId = pReceiveData[i];
            PayloadLength = pReceiveData[i + CHIPCOM_POS_LENGTH1_OFFSET];
            PayloadLength = ((PayloadLength << CHIPCOM_SHIFT_1BYTE) | pReceiveData[i + CHIPCOM_POS_LENGTH2_OFFSET]);

            if ((TotalLength - i) < (CHIPCOM_HEADER_LENGTH + PayloadLength)) {
                break;
            }
            else {
                if (DataId < CHIPCOM_DATAID_MAX) {
#ifdef CHIPCOM_SAIL_SETTING
                    if (DataId == CHIPCOM_DATAID_CANTP_RXIND) {
                        ChipCom_TxConf_isTxConfBurstEnabled = TRUE;
                    }
#endif
                    (NotificationFunction[DataId].NotificationFuncPtr)(PayloadLength, &pReceiveData[i + CHIPCOM_POS_DATA_OFFSET]);
                }
                i += CHIPCOM_HEADER_LENGTH + PayloadLength;/* Header+Length */
            }
        }
    }

    return;
}



/**** End of File ***********************************************************/
