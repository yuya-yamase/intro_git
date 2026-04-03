/* Dcm_Main_Common_h(v5-8-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Main_Common/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_MAIN_COMMON_H
#define DCM_MAIN_COMMON_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dcm/Main/cfg/Dcm_Main_Common_Cfg.h"

#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* NRC RCRRP */
#define DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING   ((Dcm_NegativeResponseCodeType)0x78U)

#define DCM_MAIN_E_CHECK_OK          ( (uint8)0x00U )
#define DCM_MAIN_E_CHECK_NOT_OK      ( (uint8)0x01U )
#define DCM_MAIN_E_INVALID_CONFIG    ( (uint8)0x02U )

/* VIN Data Size */
#define DCM_MAIN_VIN_DATA_SIZE  ((uint8)17U)        /* VIN Data Size        */

#if( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
/* VIN Update Status */
#define DCM_MAIN_VIN_STATUS_INIT     ( (uint8)0U )
#define DCM_MAIN_VIN_STATUS_PENDING  ( (uint8)1U )
#define DCM_MAIN_VIN_STATUS_UPDATED  ( (uint8)2U )
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8    Dcm_Main_ReturnCheckType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SyncOsapComplete
( void );
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Main_SetVin
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
);
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_OFF )
#if ( DCM_SUPPORT_SID2E == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Main_SetVin
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
);
#endif /* DCM_SUPPORT_SID2E == STD_ON */
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_OFF */

#if( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Main_SyncOsapDataCbk
(
    const uint8 u1TimerId
);
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Main_SetMemory
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    ptBufferPtr,
    const uint8                                 u1CharData,
    const uint16                                u2BufferSize
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CODE_SHARE
#include <Dcm_MemMap.h>

#if( DCM_M_SATELLITE_USED == STD_ON )
#if( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Main_ReadSatelliteVin
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
);
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */
#endif /* DCM_M_SATELLITE_USED == STD_ON */

#if( DCM_M_SATELLITE_USED == STD_ON )
#if( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Main_ClearSatelliteVin
( void );
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */
#endif /* DCM_M_SATELLITE_USED == STD_ON */

#define DCM_STOP_SEC_CODE_SHARE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_MAIN_COMMON_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
