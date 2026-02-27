/* Dem_Udm_DataAvl_h(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Udm_DataAvl/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_UDM_DATAAVL_H
#define DEM_UDM_DATAAVL_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes - PreInit section                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
FUNC( void, DEM_CODE_TRUST ) Dem_UdmData_PreInitForAvl       /*  PreInit section     */
( void );
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*------------------------------------------*/
/*  UserDefinedMemory only                  */
/*------------------------------------------*/
#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDataAvl_SetEvtAvl
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( boolean, AUTOMATIC ) AvailableStatus
);
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */
FUNC( boolean, DEM_CODE ) Dem_UdmDataAvl_GetEvtAvl
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDataAvl_GetUdmEventIndexByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDataAvl_GetDTCByUdmEventIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )   */

#endif /* DEM_UDM_DATAAVL_H */

/****************************************************************************/
/* History                                                                  */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
