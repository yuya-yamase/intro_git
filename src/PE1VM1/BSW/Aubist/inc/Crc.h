/* Crc_h_v2-0-0                                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Crc/Crc/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRC_H
#define CRC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../Crc/cfg/Crc_Cfg.h"
#include <Std_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Version Information             [SWS_Crc_00048] */
/* [lib_SC1-1_crc_0100] */
#define CRC_AR_RELEASE_MAJOR_VERSION    (4U)
#define CRC_AR_RELEASE_MINOR_VERSION    (5U)
#define CRC_AR_RELEASE_REVISION_VERSION (0U)
#define CRC_VENDOR_ID                   (0x0053U)
#define CRC_MODULE_ID                   (201U)
#define CRC_SW_MAJOR_VERSION            (2U)
#define CRC_SW_MINOR_VERSION            (0U)
#define CRC_SW_PATCH_VERSION            (0U)
/* Implements [lib_SDD1-1_crc_0101] */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRC_START_SEC_CODE
#include <Crc_MemMap.h>
/* SWS_Crc_00050 */
/* [lib_SC1-1_crc_0101] */
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall );        /* SWS_Crc_00031 */
/* Implements [lib_SDD1-1_crc_0001] */

/* [lib_SC1-1_crc_0102] */
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8H2F( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall );  /* SWS_Crc_00043 */
/* Implements [lib_SDD1-1_crc_0002] */

/* [lib_SC1-1_crc_0103] */
FUNC(uint16, CRC_CODE) Crc_CalculateCRC16( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall );     /* SWS_Crc_00019 */
/* Implements [lib_SDD1-1_crc_0003] */

/* [lib_SC1-1_crc_0104] */
FUNC(uint32, CRC_CODE) Crc_CalculateCRC32( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall );     /* SWS_Crc_00020 */
/* Implements [lib_SDD1-1_crc_0004] */

/* [lib_SC1-1_crc_0105] */
FUNC(uint32, CRC_CODE) Crc_CalculateCRC32P4( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall );   /* SWS_Crc_00058 */
/* Implements [lib_SDD1-1_crc_0005] */

/* [lib_SC1-1_crc_0107] */
FUNC(uint64, CRC_CODE) Crc_CalculateCRC64( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint64 Crc_StartValue64, boolean Crc_IsFirstCall );     /* SWS_Crc_00062 */
/* Implements [lib_SDD1-1_crc_0007] */

/* [lib_SC1-1_crc_0106] */
FUNC(void, CRC_CODE) Crc_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, CRC_APPL_DATA) Versioninfo );                                                                /* SWS_Crc_00021 */
/* Implements [lib_SDD1-1_crc_0006] */
#define CRC_STOP_SEC_CODE
#include <Crc_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* CRC_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2020/12/18                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
