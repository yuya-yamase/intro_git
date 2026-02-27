/* Dem_Rc_UdmMng_rc_h(v5-5-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_UdmMng_rc/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_UDMMNG_RC_H
#define DEM_RC_UDMMNG_RC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "Dem_Rc_UdmMng.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------*/
/*  Dem_UdmMngTable.c                   */
/*--------------------------------------*/
/* Enter exclusive area */
typedef P2FUNC( void, DEM_CODE, DemUdmMngExcEnterFncPtr )
( void );

/* Exit exclusive area */
typedef P2FUNC( void, DEM_CODE, DemUdmMngExcExitFncPtr )
( void );

/* Table type for RecMngCmn */
typedef struct {
    DemUdmMngExcEnterFncPtr             ExclusiveEnterFnc;
    DemUdmMngExcExitFncPtr              ExclusiveExitFnc;
} Dem_UdmExcFncType;

/*--------------------------------------*/
/*  Dem_UdmEventMng.c                   */
/*--------------------------------------*/
typedef struct {
    P2VAR( Dem_UdmEventRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE )    DemEventRecordListStartPtr;
    Dem_u16_UdmEventStrgIndexType                                   DemEventRecordNum;
} Dem_UdmEventRecordAccessType;

typedef struct {
    P2VAR( Dem_u08_RecMngMtxStsType, TYPEDEF, DEM_VAR_NO_INIT )     DemUdmEventNvMStatusPtr;
    Dem_u16_RecordKindIndexType                                     DemRecMngCmnKindUdmEvent;
} Dem_UdmEventNvMStatusType;

/*--------------------------------------*/
/*  Dem_UdmFaultMng.c                   */
/*--------------------------------------*/
typedef struct {
    P2VAR( Dem_UdmFaultRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE )    DemFaultRecordListStartPtr;
    Dem_u08_UdmFaultIndexType                                       DemFaultRecordNum;
} Dem_UdmFaultRecordAccessType;

typedef struct {
    P2VAR( Dem_u08_RecMngMtxStsType, TYPEDEF, DEM_VAR_NO_INIT )     DemUdmFaultNvMStatusPtr;
    Dem_u16_RecordKindIndexType                                     DemRecMngCmnKindUdmFault;
} Dem_UdmFaultNvMStatusType;

/*--------------------------------------*/
/*  Dem_DataMng_RecDt_UdmFFD.c          */
/*--------------------------------------*/
typedef struct {
    P2VAR( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE )                              DemFreezeFrameRecordListStartDataPtr;
    Dem_u16_FFDStoredIndexType                                               DemFFDMaxLength;
    Dem_u16_FFDStoredIndexType                                               DemFFDStoredFormatSize;
    Dem_u16_UdmFFDIndexType                                                  DemFFDRecordNum;
} Dem_UdmFreezeFrameRecordAccessType;

typedef struct {
    P2VAR( Dem_u08_RecMngMtxStsType, TYPEDEF, DEM_VAR_NO_INIT )              DemUdmFFDNvMStatusPtr;
    Dem_u16_RecordKindIndexType                                              DemRecMngCmnKindUdmFFD;
} Dem_UdmFFDNvMStatusType;

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
typedef struct {
    P2VAR( uint8, TYPEDEF, DEM_VAR_NO_INIT )                                 DemTmpUdmFFDMirrorDataPtr;
    Dem_u16_NvBlockIndexType                                                 DemUdmFFDRecordNvBlockSize;
} Dem_UdmFreezeFrameRecordNvMAccessType;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/*--------------------------------------*/
/*  Dem_DataMng_RecDt_UdmTSFFD.c        */
/*--------------------------------------*/
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
typedef struct {
    P2VAR( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE )                           DemFreezeFrameRecordListStartDataPtr;
    Dem_u16_FFDStoredIndexType                                            DemFFDMaxLength;
    Dem_u16_FFDStoredIndexType                                            DemFFDStoredFormatSize;
    Dem_u16_TSFFDIndexType                                                DemFFDRecordNum;
} Dem_UdmTSFFRecordAccessType;

typedef struct {
    P2VAR( Dem_u08_RecMngMtxStsType, TYPEDEF, DEM_VAR_NO_INIT )           DemUdmTSFFDNvMStatusPtr;
    Dem_u16_RecordKindIndexType                                           DemRecMngCmnKindUdmTSFFD;
} Dem_UdmTSFFDNvMStatusType;

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
typedef struct {
    P2VAR( uint8, TYPEDEF, DEM_VAR_NO_INIT )                              DemTmpUdmTSFFDMirrorDataPtr;
    Dem_u16_NvBlockIndexType                                              DemUdmTSFFDRecordNvBlockSize;
} Dem_UdmTSFFRecordNvMAccessType;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
#endif  /* (DEM_TSFF_UDM_SUPPORT == STD_ON) */



/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

#endif  /* DEM_RC_UDMMNG_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
