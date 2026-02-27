/* ChipCom_h_v1_0_0                                                         */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | ChipCom/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CHIPCOM_H
#define CHIPCOM_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "ComStack_Types.h" /* PduIdType */
#include "xspi.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*++++++++++++++++*/
/* Compile Switch */
/*++++++++++++++++*/
#define CHIPCOM_BSW_AUBIST                      (0U)
#define CHIPCOM_BSW_MICROSAR                    (1U)
#if defined __ghs__
  #define CHIPCOM_BSW                             CHIPCOM_BSW_AUBIST
#elif defined __ARMCC_VERSION
  #define CHIPCOM_BSW                             CHIPCOM_BSW_MICROSAR
#else
  #error "ChipCom.h, wrong pragma command"
#endif

/* Module Version */
#define CHIPCOM_MAJOR_VERSION                   (0x01U)
#define CHIPCOM_MINOR_VERSION                   (0x00U)
#define CHIPCOM_REVISION_VERSION                (0x00U)

/* I-PDU Status */
#define CHIPCOM_STATUS_NONE                     (0x00U)
#define CHIPCOM_TIMEOUT                         (0x02U)
#define CHIPCOM_NO_RX                           (0x01U)

/* Error Information */
#define CHIPCOM_ERR_KIND_NONE                   XSPI_ERR_KIND_NONE          /* No Error */
#define CHIPCOM_ERR_KIND_TRX                    XSPI_ERR_KIND_TRX           /* TRx Error */
#define CHIPCOM_ERR_KIND_INTG                   XSPI_ERR_KIND_INTG          /* Data Integrity */
#define CHIPCOM_ERR_KIND_ENCHG                  XSPI_ERR_KIND_ENCHG         /* EN Signal Change */
#define CHIPCOM_ERR_KIND_TIN                    XSPI_ERR_KIND_TIN           /* Airtime Over */
#define CHIPCOM_ERR_KIND_RX_BUF_OVF             XSPI_ERR_KIND_RX_BUF_OVF    /* RxBuffer Overflow */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* I-PDU Status Type */
typedef uint8  ChipCom_IpduStatusType;

#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST
  #include "Can.h" /* CanMsgType */
  #include "Com.h" /* SignalIdType */
#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */
/* CAN Message Type */
typedef struct
{
    uint8*              ptData;
    uint32              u4Id;
    uint8               u1Length;
} CanMsgType;

/* SignalId Type */
typedef uint16 Com_SignalIdType;
#endif

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Scheduled Functions */
void ChipCom_Init( void );
void ChipCom_DeInit( void );
void ChipCom_MainFunction( void );
void ChipCom_MainFunctionPostApp( void );
void ChipCom_MainFunctionPreApp( void );
void ChipCom_MainFunctionPreTx( void );
void ChipCom_MainFunctionPostRx( void );

/* Service API */
uint8 ChipCom_SendSignal( Com_SignalIdType t_u2SignalId, const void* t_pvdSignalDataPtr );
uint8 ChipCom_ReceiveSignal( Com_SignalIdType t_u2SignalId, void* t_pvdSignalDataPtr );
ChipCom_IpduStatusType ChipCom_GetSignalStatus( Com_SignalIdType t_u2SignalId );
Std_ReturnType ChipCom_CanTransmit( const CanMsgType* t_pstMsg );
uint8 ChipCom_GetErrInfo( void );

/* Callback Functions and Notifications */

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#include "ChipCom_Wrapper.h"

#endif /* CHIPCOM_H */

/**** End of File ***********************************************************/
