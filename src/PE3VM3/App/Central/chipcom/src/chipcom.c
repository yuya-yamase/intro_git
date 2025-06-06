/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "chipcom.h"

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
#define CHIPCOM_RCV_FRM_MAX         (XSPI_RCV_FRM_MAX - 12U)
#define CHIPCOM_SND_FRM_MAX         (XSPI_SND_FRM_MAX - 12U)

#define CHIPCOM_POS_LENGTH1_OFFSET  ((uint16)0x0001U)
#define CHIPCOM_POS_LENGTH2_OFFSET  ((uint16)0x0002U)
#define CHIPCOM_POS_DATA_OFFSET     ((uint16)0x0003U)
#define CHIPCOM_HEADER_LENGTH       ((uint16)0x0003U)

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
static void ChipCom_memset(uint8 Dst[], uint8 WriteData, uint32 Size);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static uint8        ChipCom_SpiRxData[CHIPCOM_RCV_FRM_MAX];
static uint8        ChipCom_SpiTxData[CHIPCOM_SND_FRM_MAX];

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

    ChipCom_memset(ChipCom_SpiTxData, 0x00, CHIPCOM_SND_FRM_MAX);
    ChipCom_memset(ChipCom_SpiRxData, 0x00, CHIPCOM_RCV_FRM_MAX);
    for (i = 0; i < CHIPCOM_PERIODICID_MAX; i++) {
        pInitBuff = PeriodicRelation[i].InitVal;
        if( PeriodicRelation[i].TxPos < CHIPCOM_POS_TX_EVENTDATA_OFFSET ) {
            for (j = 0; j < PeriodicRelation[i].DataLen; j++) {
                ChipCom_SpiTxData[((PeriodicRelation[i].TxPos) + j)] = (pInitBuff[j]);
            } 
        }
        if( PeriodicRelation[i].RxPos < CHIPCOM_POS_RX_EVENTDATA_OFFSET ) {
            for (j = 0; j < PeriodicRelation[i].DataLen; j++) {
                ChipCom_SpiRxData[((PeriodicRelation[i].RxPos) + j)] = (pInitBuff[j]);
            }
        }
    }
    ChipCom_SeqNumberRx = 0;
    ChipCom_SeqNumberTx = 0;

    ChipCom_SpiTxData_index = CHIPCOM_POS_TX_EVENTDATA_OFFSET;

    return;
}

void ChipCom_Main(void)
{
    uint8 SpiState;
    uint8 SpiWrite_Result;
    uint8 SpiRead_Result;

    SpiState = xspi_GetCondition(XSPI_CH_03);
    if ((SpiState == XSPI_DCOND_IDLE) || (SpiState == XSPI_DCOND_TRANSMIT)) {
          /* Disable Interrupt  */
          CHIPCOM_DISABLE_INTERRUPT();
          ChipCom_SpiTxData[CHIPCOM_POS_TOTALLENGTH1] = (uint8)((ChipCom_SpiTxData_index & CHIPCOM_2BYTEMASK_HIGH) >> CHIPCOM_SHIFT_1BYTE);   /* Total Length High byte */
          ChipCom_SpiTxData[CHIPCOM_POS_TOTALLENGTH2] = (uint8)((ChipCom_SpiTxData_index & CHIPCOM_2BYTEMASK_LOW));                           /* Total Length Low byte */

          /* SPI Write */
          SpiWrite_Result = xspi_Write(XSPI_CH_03, ChipCom_SpiTxData, (uint32)ChipCom_SpiTxData_index);
          if (SpiWrite_Result == XSPI_NG)
          {
              /* ToDo: Invalid Procedure */
          } else {
              /* Clear Tx Event Buffer */
              ChipCom_memset(&(ChipCom_SpiTxData[CHIPCOM_POS_TX_EVENTDATA_OFFSET]), 0x00U, (CHIPCOM_SND_FRM_MAX-CHIPCOM_POS_TX_EVENTDATA_OFFSET));
              ChipCom_SpiTxData_index = CHIPCOM_POS_TX_EVENTDATA_OFFSET;

              /* Send Counter(Wrap Around) */ 
              ChipCom_SeqNumberTx++;
              ChipCom_SpiTxData[CHIPCOM_POS_SEQUENCENO1] = (uint8)((ChipCom_SeqNumberTx & CHIPCOM_4BYTEMASK_HIGHEST) >> CHIPCOM_SHIFT_3BYTE);
              ChipCom_SpiTxData[CHIPCOM_POS_SEQUENCENO2] = (uint8)((ChipCom_SeqNumberTx & CHIPCOM_4BYTEMASK_HIGH   ) >> CHIPCOM_SHIFT_2BYTE);
              ChipCom_SpiTxData[CHIPCOM_POS_SEQUENCENO3] = (uint8)((ChipCom_SeqNumberTx & CHIPCOM_4BYTEMASK_LOW    ) >> CHIPCOM_SHIFT_1BYTE);
              ChipCom_SpiTxData[CHIPCOM_POS_SEQUENCENO4] = (uint8)((ChipCom_SeqNumberTx & CHIPCOM_4BYTEMASK_LOWEST )                       );
          }

          /* Enable Interrupt */
          CHIPCOM_ENABLE_INTERRUPT();
    }

    /* SPI Read */
    SpiRead_Result = xspi_Read(XSPI_CH_03, ChipCom_SpiRxData, CHIPCOM_RCV_FRM_MAX);
    if (SpiRead_Result == XSPI_OK)
    {
        ChipCom_SeqNumberRx = (uint32)
                     ((ChipCom_SpiRxData[CHIPCOM_POS_SEQUENCENO1]) << CHIPCOM_SHIFT_3BYTE ) |
                     ((ChipCom_SpiRxData[CHIPCOM_POS_SEQUENCENO2]) << CHIPCOM_SHIFT_2BYTE ) |
                     ((ChipCom_SpiRxData[CHIPCOM_POS_SEQUENCENO3]) << CHIPCOM_SHIFT_1BYTE ) |
                     ((ChipCom_SpiRxData[CHIPCOM_POS_SEQUENCENO4])  );

        ChipCom_DispatchReceiveDate(&ChipCom_SpiRxData[0U]);
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
    uint16 i;
    Std_ReturnType Ret = E_OK;

    /* Disable Interrupt */
    CHIPCOM_DISABLE_INTERRUPT();
    
    if (ChipCom_SpiTxData_index < CHIPCOM_SND_FRM_MAX) {
        if (data_id < CHIPCOM_DATAID_MAX) {
            /* Review Guard Condition for Multiframe */
            if ((CHIPCOM_HEADER_LENGTH + transreq_len) <= (CHIPCOM_SND_FRM_MAX - ChipCom_SpiTxData_index)) {
                /* Common Valid Data ID */
                ChipCom_SpiTxData[ChipCom_SpiTxData_index] = data_id;
                ChipCom_SpiTxData_index++;
                ChipCom_SpiTxData[ChipCom_SpiTxData_index] = (uint8)((transreq_len & CHIPCOM_2BYTEMASK_HIGH) >> CHIPCOM_SHIFT_1BYTE);
                ChipCom_SpiTxData_index++;
                ChipCom_SpiTxData[ChipCom_SpiTxData_index] = (uint8)(transreq_len & CHIPCOM_2BYTEMASK_LOW);
                ChipCom_SpiTxData_index++;
                
                for (i = 0; i < transreq_len; i++) {
                    ChipCom_SpiTxData[ChipCom_SpiTxData_index + i] = transreq_data[i];
                }
                ChipCom_SpiTxData_index += i;
            } else {
                Ret = E_NOT_OK;
            }
        } else {
            Ret = E_NOT_OK;
        }
    } else {
        Ret = E_NOT_OK;
    }
    /* Enable Interrupt */
    CHIPCOM_ENABLE_INTERRUPT();
    
    return (Ret);
}

Std_ReturnType ChipCom_SetPeriodicTxData(const uint8 periodic_id, const uint16 trans_len, const uint8* const trans_data)
{
    Std_ReturnType Ret = E_OK;
    uint16 i = 0;

    if (periodic_id < CHIPCOM_PERIODICID_MAX) {
        if (PeriodicRelation[periodic_id].TxPos < CHIPCOM_POS_TX_EVENTDATA_OFFSET) {
            if (trans_len ==  PeriodicRelation[periodic_id].DataLen){
                for (i = 0; i < PeriodicRelation[periodic_id].DataLen; i++) {
                    ChipCom_SpiTxData[(PeriodicRelation[periodic_id].TxPos +i)] = trans_data[i];
                }
            } else {
                Ret = E_NOT_OK;
            }
        } else {
            Ret = E_NOT_OK;
        }
    } else {
        Ret = E_NOT_OK;
    }

    return Ret;
}
Std_ReturnType ChipCom_GetPeriodicRxData(const uint8 periodic_id, uint16* receive_len, uint8* receive_data, uint32* receive_counter)
{
    Std_ReturnType Ret = E_OK;
    uint16 i = 0;

    if (periodic_id < CHIPCOM_PERIODICID_MAX) {
        if (PeriodicRelation[periodic_id].RxPos < CHIPCOM_POS_RX_EVENTDATA_OFFSET) {
            *receive_len = PeriodicRelation[periodic_id].DataLen;
            for (i = 0; i < PeriodicRelation[periodic_id].DataLen; i++) {
                receive_data[i] = ChipCom_SpiRxData[(PeriodicRelation[periodic_id].RxPos +i)];
            }
            *receive_counter = ChipCom_SeqNumberRx;
        } else {
            Ret = E_NOT_OK;
        }
    } else {
        Ret = E_NOT_OK;
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
static void ChipCom_memset( uint8 Dst[], uint8 WriteData, uint32 Size )
{
    uint8  *DstTmp = Dst;
    uint32 SizeTmp = Size;

    while ( SizeTmp > 0U ) {
        *DstTmp = WriteData;
        DstTmp++;
        SizeTmp--;
    }
    return;
}

/**** End of File ***********************************************************/
