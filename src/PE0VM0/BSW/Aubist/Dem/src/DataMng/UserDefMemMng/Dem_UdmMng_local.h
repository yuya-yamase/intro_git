/* Dem_UdmMng_local_h(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/UdmMng_local/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_UDMMNG_LOCAL_H
#define DEM_UDMMNG_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMng_rc.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
#define DEM_UDMMNG_CHECKSUM_SHIFT       ( (uint8)0x08U )
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------*/
/*  Dem_UdmFaultMng.c                   */
/*--------------------------------------*/
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#if ( DEM_UDMFAULT_RECORD_PADDING_EXIST == STD_ON )
FUNC( void, DEM_CODE ) Dem_UdmFaultMng_Get_PaddingRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2VAR( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
);
#endif /*   ( DEM_UDMFAULT_RECORD_PADDING_EXIST == STD_ON )  */
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/*--------------------------------------*/
/*  Dem_DataMng_RecDt_UdmFFD.c          */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmFFDMng_Verified
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);


/*--------------------------------------*/
/*  Dem_UdmMngVld.c                     */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmMngVld_DataInit
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmMngVld_DataVerify
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern VAR( Dem_UdmFreezeFrameRecordMngType, DEM_VAR_NO_INIT ) Dem_TmpVerifyUdmFreezeFrameRecord[DEM_UDM_MAX_NUMBER_FF_PER_DTC];

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

#endif  /* DEM_UDMMNG_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
