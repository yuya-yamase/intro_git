/* ChipCom_Wrapper_h_v1_0_0                                                 */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | ChipCom_Wrapper/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CHIPCOM_WRAPPER_H
#define CHIPCOM_WRAPPER_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* I-PDU Status */
#define CHIPCOM_TRX_START                         (0x01U)

/* PeriodicID Name */
#define CHIPCOM_PERIODICID_ETHERSWT_MCUINFO                     ((uint8)(17U))
#define CHIPCOM_PERIODICID_DOIPMGR_DOIPCOMPWR                   ((uint8)(10U))
#define CHIPCOM_PERIODICID_VIS_UTC                              ((uint8)(18U))
#define CHIPCOM_PERIODICID_VIS_ODO                              ((uint8)(19U))
#define CHIPCOM_PERIODICID_VIS_VOLT                             ((uint8)(20U))
#define CHIPCOM_PERIODICID_VIS_TRIP                             ((uint8)(21U))
#define CHIPCOM_PERIODICID_VIS_SPD                              ((uint8)(22U))
#define CHIPCOM_PERIODICID_VIS_RDYSTS                           ((uint8)(23U))
#define CHIPCOM_PERIODICID_VIS_BASICSTATE                       ((uint8)(24U))
#define CHIPCOM_PERIODICID_VIS_SPECIALSTATE                     ((uint8)(25U))
#define CHIPCOM_PERIODICID_VIS_TRANSFLG                         ((uint8)(26U))
#define CHIPCOM_PERIODICID_VIS_OTASWACT                         ((uint8)(27U))
#define CHIPCOM_PERIODICID_VIS_PWRERRST                         ((uint8)(28U))
#define CHIPCOM_PERIODICID_VIS_CRLYOF                           ((uint8)(29U))
#define CHIPCOM_PERIODICID_VIS_VIN                              ((uint8)(30U))
#define CHIPCOM_PERIODICID_VIS_COMPWR                           ((uint8)(31U))
#define CHIPCOM_PERIODICID_ETHERSWT_REGERRSTS                   ((uint8)(11U))
#define CHIPCOM_PERIODICID_ETHERMGR_MACADDR                     ((uint8)(12U))
#define CHIPCOM_PERIODICID_VSM_SLEEPNG                          ((uint8)(1U))
#define CHIPCOM_PERIODICID_ETHERSWT_SWIC_LINKINFO               ((uint8)(13U))
#define CHIPCOM_PERIODICID_ETHERSWT_SWIC_MIB                    ((uint8)(14U))
#define CHIPCOM_PERIODICID_ETHERSWT_SWIC_SQI                    ((uint8)(15U))
#define CHIPCOM_PERIODICID_ETHERSWT_SWIC_DATAUSAGEEXCEED        ((uint8)(16U))
#define CHIPCOM_PERIODICID_VIS_SAILRESETST                      ((uint8)(32U))
#define CHIPCOM_PERIODICID_CANWKUPSLP                           ((uint8)(9U))
#define CHIPCOM_PERIODICID_ETHERSWT_SWIC_RESETRESTART           ((uint8)(34U))
#define CHIPCOM_PERIODICID_SAILDATARSTREQ                       ((uint8)(36U))
#define CHIPCOM_PERIODICID_SAILDATARSTRES                       ((uint8)(5U))

/* Data Length */
#define CHIPCOM_LENGTH_ETHERSWT_MCUINFO                         ((uint8)(8U))
#define CHIPCOM_LENGTH_DOIPMGR_DOIPCOMPWR                       ((uint8)(1U))
#define CHIPCOM_LENGTH_VIS_UTC                                  ((uint8)(6U))
#define CHIPCOM_LENGTH_VIS_ODO                                  ((uint8)(4U))
#define CHIPCOM_LENGTH_VIS_VOLT                                 ((uint8)(1U))
#define CHIPCOM_LENGTH_VIS_TRIP                                 ((uint8)(3U))
#define CHIPCOM_LENGTH_VIS_SPD                                  ((uint8)(1U))
#define CHIPCOM_LENGTH_VIS_RDYSTS                               ((uint8)(1U))
#define CHIPCOM_LENGTH_VIS_BASICSTATE                           ((uint8)(2U))
#define CHIPCOM_LENGTH_VIS_SPECIALSTATE                         ((uint8)(2U))
#define CHIPCOM_LENGTH_VIS_TRANSFLG                             ((uint8)(2U))
#define CHIPCOM_LENGTH_VIS_OTASWACT                             ((uint8)(2U))
#define CHIPCOM_LENGTH_VIS_PWRERRST                             ((uint8)(2U))
#define CHIPCOM_LENGTH_VIS_CRLYOF                               ((uint8)(2U))
#define CHIPCOM_LENGTH_VIS_VIN                                  ((uint8)(18U))
#define CHIPCOM_LENGTH_VIS_COMPWR                               ((uint8)(1U))
#define CHIPCOM_LENGTH_ETHERSWT_REGERRSTS                       ((uint8)(8U))
#define CHIPCOM_LENGTH_ETHERMGR_MACADDR                         ((uint8)(6U))
#define CHIPCOM_LENGTH_VSM_SLEEPNG                              ((uint8)(1U))
#define CHIPCOM_LENGTH_ETHERSWT_SWIC_LINKINFO                   ((uint8)(16U))
#define CHIPCOM_LENGTH_ETHERSWT_SWIC_MIB                        ((uint8)(244U))
#define CHIPCOM_LENGTH_ETHERSWT_SWIC_SQI                        ((uint8)(8U))
#define CHIPCOM_LENGTH_ETHERSWT_SWIC_DATAUSAGEEXCEED            ((uint8)(24U))
#define CHIPCOM_LENGTH_VIS_SAILRESETST                          ((uint8)(1U))
#define CHIPCOM_LENGTH_CANWKUPSLP                               ((uint8)(1U))
#define CHIPCOM_LENGTH_ETHERSWT_SWIC_RESETRESTART               ((uint8)(4U))
#define CHIPCOM_LENGTH_SAILDATARSTREQ                           ((uint8)(1U))
#define CHIPCOM_LENGTH_SAILDATARSTRES                           ((uint8)(1U))

/* SAILRESETST */
#define SIGNAL_CHIPCOM_CH0_BUS_SPI_ALL                          ((uint16)(32U))

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint16                          ChipCom_PduIdType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Scheduled Functions */

/* Service API */
Std_ReturnType ChipCom_SetPeriodicTxData( const uint8 periodic_id, const uint16 trans_len, const uint8* const trans_data );
Std_ReturnType ChipCom_GetPeriodicRxData( const uint8 periodic_id, uint16* receive_len, uint8* receive_data, uint32* receive_counter );
ChipCom_IpduStatusType ChipCom_GetIPDUStatus( ChipCom_PduIdType ChipCom_PduId );

/* Callback Functions and Notifications */

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* CHIPCOM_WRAPPER_H */

/**** End of File ***********************************************************/
