/* Dem_MemSync_RecordInfo_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MemSync/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

#include "../../../inc/Dem_Mm_MemSync_RecordInfo.h"
#include "../../../inc/Dem_Rc_RecMngCmn_rc.h"
#include "Dem_MemInfo_FncTable.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

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
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_MemSync_GetEventIdFromRecord                         */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordKind  :                                      */
/*               | [in]  RecordIndex :                                      */
/*               | [in]  EventIdPtr  :                                      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MemSync_GetEventIdFromRecord
(
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) BlockRecordKind,      /* [PRMCHK:CALLER] */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{

    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) recordFieldIndex;

    recordFieldIndex = Dem_RecordFieldIndexTableForMemBlockRecordInfoFunc[BlockRecordKind]; /* [GUDCHK:CALLER]BlockRecordKind */
#ifndef JGXSTACK
    /* Write processing completion notification */
    (void)Dem_MemBlockRecordInfo_FuncTable[BlockRecordKind].DemGetEventIdFromRecordDataFnc( recordFieldIndex, RecordIndex, EventIdPtr );  /* no return check required */    /* [GUDCHK:CALLER]BlockRecordKind */
#else /* JGXSTACK */
    /* Write processing completion notification for stack */
    (void)Dem_GetEventIdFromRecordDataFnc_ForStack( recordFieldIndex, RecordIndex, EventIdPtr );   /* no return check required */
#endif /* JGXSTACK */

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
