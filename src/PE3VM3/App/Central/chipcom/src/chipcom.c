/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "chipcom.h"
#include "aip_common.h"
#include "LIB.h"

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

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void ChipCom_DispatchReceiveDate(uint8* pReceiveData);

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

    ChipCom_SpiTxData_index = CHIPCOM_POS_TX_EVENTDATA_OFFSET;

    return;
}

void ChipCom_MainRx(void)
{
    uint8 SpiRead_Result;
    uint16 RxLoopCnt;

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
        CHIPCOM_ENABLE_INTERRUPT();

        ChipCom_DispatchReceiveDate(&(ChipCom_SpiRxDataU1[0U]));
    }

    return;
}

void ChipCom_MainTx(void)
{
    uint8 SpiState;
    uint8 SpiWrite_Result;
    uint16 TxLoopCnt;

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
        }

        /* Enable Interrupt */
        CHIPCOM_ENABLE_INTERRUPT();
    }

    return;
}

static void ChipCom_DispatchReceiveDate(uint8* pReceiveData)
{
    uint8 DataId;
    uint16 TotalLength;
    uint16 PayloadLength;
    uint16 i = CHIPCOM_POS_RX_EVENTDATA_OFFSET;

    TotalLength = (pReceiveData[CHIPCOM_POS_TOTALLENGTH1] << CHIPCOM_SHIFT_1BYTE);
    TotalLength = (TotalLength | pReceiveData[CHIPCOM_POS_TOTALLENGTH2]);

    while (i < TotalLength) {
        DataId = pReceiveData[i];
        PayloadLength = pReceiveData[i + CHIPCOM_POS_LENGTH1_OFFSET];
        PayloadLength = ((PayloadLength << CHIPCOM_SHIFT_1BYTE) | pReceiveData[i + CHIPCOM_POS_LENGTH2_OFFSET]);

        if (DataId < CHIPCOM_DATAID_MAX) {
            (NotificationFunction[DataId].NotificationFuncPtr)(PayloadLength, &pReceiveData[i + CHIPCOM_POS_DATA_OFFSET]);
        }
        i += CHIPCOM_HEADER_LENGTH + PayloadLength;/* Header+Length */
    }

    return;
}

Std_ReturnType  ChipCom_Transmit(const uint8 data_id, const uint16 transreq_len, const uint8* const transreq_data)
{
    uint16 u2t_TxDataCount;
    Std_ReturnType Ret = E_NOT_OK;

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


/**** End of File ***********************************************************/
