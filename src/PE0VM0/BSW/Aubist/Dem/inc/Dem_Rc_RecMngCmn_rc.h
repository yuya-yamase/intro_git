/* Dem_Rc_RecMngCmn_rc_h(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Rc_RecMngCmn_rc/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_RECMNGCMN_RC_H
#define DEM_RC_RECMNGCMN_RC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#include "../cfg/Dem_MM_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"

#include "Dem_Rc_DataMng.h"
#include "Dem_Rc_ClrInfoMng.h"
#include "Dem_Rc_PFCMng.h"
#include "Dem_Rc_IndMIMng.h"
#include "Dem_Rc_IUMPRMng.h"
#include "Dem_Rc_AltIUMPRMng.h"
#include "Dem_Rc_OpCycleMng.h"
#include "Dem_Rc_OccrDTCMng.h"
#include "Dem_Rc_PIDMng.h"
#include "Dem_Rc_DTRMng.h"
#include "Dem_Rc_PreFFDMng.h"
#include "Dem_Rc_UdmMng.h"
#include "Dem_Rc_MisfireMng.h"
#include "Dem_Rc_SimilarMng.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*======================================*/
/*  for RecMngCmn table                 */
/*======================================*/
/*----------------------------------*/
/* Set the Writing RamData */
/*----------------------------------*/
typedef P2FUNC( void, DEM_CODE, DemRecMngCmnSetMirrorDataFncPtr )
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);

/*----------------------------------*/
/* Enter exclusive area */
/*----------------------------------*/
typedef P2FUNC( void, DEM_CODE, DemRecMngCmnExcEnterFncPtr )
( void );

/*----------------------------------*/
/* Exit exclusive area */
/*----------------------------------*/
typedef P2FUNC( void, DEM_CODE, DemRecMngCmnExcExitFncPtr )
( void );

/*----------------------------------*/
/* Table type for RecMngCmn */
/*----------------------------------*/
typedef struct {
    DemRecMngCmnSetMirrorDataFncPtr          SetRecordMirrorFnc;
    DemRecMngCmnExcEnterFncPtr               ExclusiveEnterFnc;
    DemRecMngCmnExcExitFncPtr                ExclusiveExitFnc;
    P2VAR( Dem_u08_RecMngMtxStsType, TYPEDEF, DEM_VAR_NO_INIT ) NvMStatusPtr;
    Dem_u16_RecordIndexType                  RecordNum;
    Dem_u16_BlockSizeType                    DemBlockSize;
    Dem_u16_NvBlockPerRecordNumType          BlockNumPerRecord;
    Dem_u16_MMBlockRecKindIndexType          BlockRecordKind;
} Dem_NvMWriteInfoType;


/*======================================*/
/*  for MemSync table                   */
/*======================================*/

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/*======================================*/
/*  for RecMngCmn system table          */
/*======================================*/
/*----------------------------------*/
/* Init function */
/*----------------------------------*/
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
typedef P2FUNC( void, DEM_CODE, DemRecMngCmnInitFncPtr )
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

/*----------------------------------*/
/* Shutdown function */
/*----------------------------------*/
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
typedef P2FUNC( void, DEM_CODE, DemRecMngCmnInitSavedZoneFncPtr )
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);

/*----------------------------------*/
/* DataVerify function */
/*----------------------------------*/
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
typedef P2FUNC( Dem_u08_InternalReturnType, DEM_CODE, DemRecMngCmnDataVerifyFncPtr )
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

typedef struct {
    DemRecMngCmnInitFncPtr              InitFnc;
    DemRecMngCmnInitSavedZoneFncPtr     InitSavedZoneFnc;
    DemRecMngCmnDataVerifyFncPtr        DataVerifyFnc;
} Dem_RecordInitInfoType;

typedef P2FUNC( Dem_u08_InternalReturnType, DEM_CODE, DemClrNotVerifiedRecordFuncPtr )
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
typedef P2FUNC( Dem_u08_InternalReturnType, DEM_CODE, DemUdmClrNotVerifiedRecordFuncPtr )
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
);
#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*======================================*/
/*  for MemInfo table                   */
/*======================================*/
/*----------------------------------*/
/* GetRecordData function           */
/*----------------------------------*/
typedef P2FUNC( Dem_u08_InternalReturnType, DEM_CODE, DemMemInfoGetEventIdFromRecordDataFncPtr )
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
/* Function pointer type */
typedef struct {
    DemMemInfoGetEventIdFromRecordDataFncPtr     DemGetEventIdFromRecordDataFnc;
} Dem_MemInfoRecordDataType;
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* DEM_RC_RECMNGCMN_RC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
