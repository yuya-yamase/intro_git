/****************************************************************************/

#ifndef CHIPCOM_H
#define CHIPCOM_H

#include "Std_Types.h"
#include "chipcom_config.h"
#include "xspi.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_ERR_MAXK_KIND       XSPI_ERR_MAXK_KIND          /* Error Kind */
#define CHIPCOM_ERR_KIND_NONE       XSPI_ERR_KIND_NONE          /* No Error */
#define CHIPCOM_ERR_KIND_TRX        XSPI_ERR_KIND_TRX           /* TRx Error */
#define CHIPCOM_ERR_KIND_INTG       XSPI_ERR_KIND_INTG          /* Data Integrity */
#define CHIPCOM_ERR_KIND_ENCHG      XSPI_ERR_KIND_ENCHG         /* EN Signal Change */
#define CHIPCOM_ERR_KIND_TIN        XSPI_ERR_KIND_TIN           /* Airtime Over */
#define CHIPCOM_ERR_KIND_RX_BUF_OVF XSPI_ERR_KIND_RX_BUF_OVF    /* RxBuffer Overflow */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void            ChipCom_Init( void );
void            ChipCom_MainRx( void );
void            ChipCom_MainTx( void );

Std_ReturnType ChipCom_Transmit(const uint8 data_id, const uint16 transreq_len, const uint8* const transreq_data);
Std_ReturnType ChipCom_SetPeriodicTxData(const uint8 periodic_id, const uint16 trans_len, const uint8* const trans_data);
Std_ReturnType ChipCom_GetPeriodicRxData(const uint8 periodic_id, uint16* receive_len, uint8* receive_data, uint32* receive_counter);			

uint16 ChipCom_GetTxSize(void);
void ChipCom_Nop(const uint16 receive_len, const uint8* const receive_data);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define ChipCom_GetErrInfo()        xspi_GetErrInfo(XSPI_CH_03)

#endif  /* CHIPCOM_H */
/**** End of File ***********************************************************/
