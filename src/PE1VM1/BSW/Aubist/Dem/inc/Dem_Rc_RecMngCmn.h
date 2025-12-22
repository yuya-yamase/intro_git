/* Dem_Rc_RecMngCmn_h(v5-5-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_RecMngCmn/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_RECMNGCMN_H
#define DEM_RC_RECMNGCMN_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"
#include "../inc/Dem_Mm_MemSync.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_RECMNGCMN_NVM_STS_NON_TARGET         ((Dem_u08_RecMngMtxStsType)0x00U)
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#define DEM_RECMNGCMN_NVM_STS_TARGET             ((Dem_u08_RecMngMtxStsType)0x11U)
#define DEM_RECMNGCMN_NVM_STS_WRITING            ((Dem_u08_RecMngMtxStsType)0x22U)
#define DEM_RECMNGCMN_NVM_STS_UPDATA_WRITING     ((Dem_u08_RecMngMtxStsType)0x33U)
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
#define DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED       ((Dem_u08_RecMngMtxStsType)0xFFU)

#define DEM_RECORD_ONE_FIELD                     ((Dem_u16_RecordFieldIndexType)0xFFFFU)
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE ) Dem_RecMngCmn_Init
( void );

FUNC( void, DEM_CODE ) Dem_RecMngCmn_Shutdown
( void );
FUNC( void, DEM_CODE ) Dem_RecMngCmn_InitSavedZone
( void );
FUNC( void, DEM_CODE ) Dem_RecMngCmn_AfterNvBlockReadComplete
( void );

FUNC( void, DEM_CODE ) Dem_RecMngCmn_InitDataVerify
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngCmn_DataVerify
( void );

FUNC( void, DEM_CODE ) Dem_RecMngCmn_SetNvMWriteStatus
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngCmn_GetNvMWriteData
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngCmn_NotifyCompleteNvMWrite
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
);

FUNC( void, DEM_CODE ) Dem_RecMngCmn_ExclusiveDummy
( void );

FUNC( boolean, DEM_CODE ) Dem_RecMngCmn_GetRequestOfNvMWrite
( void );
FUNC( void, DEM_CODE ) Dem_RecMngCmn_ResetRequestOfNvMWrite
( void );
FUNC( void, DEM_CODE ) Dem_RecMngCmn_RefreshRAM
( void );

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* DEM_RECMNGCMN_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

