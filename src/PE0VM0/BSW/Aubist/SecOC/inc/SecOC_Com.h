/* SecOC_Com_h_v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Com/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef SECOC_COM_H
#define SECOC_COM_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOC.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Bit to Byte */
#define SECOC_COM_BIT2BYTE_SHIFT            (3UL)
#define SECOC_COM_BIT2BYTE_SURPLUS          (0x07UL)
#define SECOC_COM_BIT2BYTE_ROUND_ADD        (7UL)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptProtData;
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptFreshnessValue;
    uint32  u4DataId;
    uint16  u2DataIdLength;
    uint16  u2FreshnessValueSize;
    uint32  u4ProtDataSize;
} SecOC_Com_BuildAuthDataType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

#if (((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) \
  || ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)))
FUNC(void, SECOC_CODE) SecOC_Com_BuildAuthData
(
    P2CONST(SecOC_Com_BuildAuthDataType, AUTOMATIC, SECOC_APPL_DATA) ptInfo,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptData,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptSize
);
#endif

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* SECOC_COM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
