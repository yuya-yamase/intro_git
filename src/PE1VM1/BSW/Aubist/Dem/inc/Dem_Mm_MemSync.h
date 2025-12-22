/* Dem_Mm_Sync_h(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Mm_MemSync/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_MM_MEMSYNC_H
#define DEM_MM_MEMSYNC_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    P2VAR( void, TYPEDEF, DEM_VAR_NO_INIT ) MirrorPtr;
    Dem_u16_RecordDataSizeType          MirrorLength;
    Dem_u16_RecordIndexType             RecordIndex;
    Dem_u16_RecordDataSizeType          RecordDataOffset;
    Dem_u16_MMBlockRecKindIndexType     BlockRecordKind;
} Dem_DataMirrorInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE ) Dem_DmSnc_Init
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DmSnc_GetNvMWriteData
(
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
FUNC( void, DEM_CODE ) Dem_DmSnc_CompleteWrite
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
);
FUNC( void, DEM_CODE ) Dem_DmSnc_RefreshRAM
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON */

#endif /* DEM_MM_MEMSYNC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

