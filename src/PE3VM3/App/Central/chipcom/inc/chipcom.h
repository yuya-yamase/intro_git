/* v0-4-0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  chipcom.h                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

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
typedef enum {
    CHIPCOM_NO_RX = 0x00U,                  /* After data initialization, no data has been received. */
    CHIPCOM_TIMEOUT,                        /* Timeout occurred during data reception. */
    CHIPCOM_TRX_START,                      /* Receiving operation is normal. */
} ChipCom_IpduStatusType;
typedef uint16  ChipCom_PduIdType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void            ChipCom_Init( void );
void            ChipCom_MainRx( void );
void            ChipCom_MainTx( void );

Std_ReturnType ChipCom_Transmit(const uint8 data_id, const uint16 transreq_len, const uint8* const transreq_data);
Std_ReturnType ChipCom_SetPeriodicTxData(const uint8 periodic_id, const uint16 trans_len, const uint8* const trans_data);
Std_ReturnType ChipCom_GetPeriodicRxData(const uint8 periodic_id, uint16* receive_len, uint8* receive_data, uint32* receive_counter);
ChipCom_IpduStatusType ChipCom_GetIPDUStatus( ChipCom_PduIdType ChipCom_PduId );

uint16 ChipCom_GetTxSize(void);
void ChipCom_Nop(const uint16 receive_len, const uint8* const receive_data);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define ChipCom_GetErrInfo()        xspi_GetErrInfo(XSPI_CH_03)

#endif  /* CHIPCOM_H */
/**** End of File ***********************************************************/
