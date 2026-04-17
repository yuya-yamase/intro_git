/* Dem_MM_RecordInfo_c(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MM_RecordInfo/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

#include "../../../cfg/Dem_MM_Cfg.h"
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Mm_MemSync_RecordInfo.h"
#include "../../../inc/Dem_Mm_MM_RecordInfo.h"
#include "Dem_MM_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_MEMINTO_1BLOCK_PER_RECORD   (( Dem_u16_NvBlockIndexType )1U)
#define DEM_MEMINTO_2BLOCK_PER_RECORD   (( Dem_u16_NvBlockIndexType )2U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_GetBlockRecordKindByNvMBlockId
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC, AUTOMATIC ) BlockRecordKindPtr,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) RecordIndexPtr
);


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
/* Function Name | Dem_MM_GetRecordInfoByNvMBlockId                         */
/* Description   | Get record information by NvM block Id.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] BlockId : block Id.                                 */
/*               | [out] RecordKindPtr :                                    */
/*               |        Pointer to the area to get record kind.           */
/*               | [out] EventIdPtr :                                       */
/*               |        Pointer to the area to get eventid.               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_GetRecordInfoByNvMBlockId
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_RecordKindType, AUTOMATIC, AUTOMATIC ) RecordKindPtr,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetRecordKind;
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) blkRecordKind;
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) recordIndex;

    retVal = DEM_IRT_NG;
    blkRecordKind       =   DEM_MMBLKRECKINDINDEX_INVALID;
    recordIndex         =   DEM_RECORDINDEX_INVALID;

    /*  get record kind and index from block id.        */
    retGetRecordKind    =   Dem_MM_GetBlockRecordKindByNvMBlockId( BlockId, &blkRecordKind, &recordIndex );

    if ( retGetRecordKind == DEM_IRT_OK )
    {
        /*  output record kind.                 */
        *RecordKindPtr  =   ( Dem_RecordKindType )blkRecordKind;

        /*  get eventid from record data.       */
        Dem_MemSync_GetEventIdFromRecord( blkRecordKind, recordIndex, EventIdPtr );

        retVal = DEM_IRT_OK;

    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_MM_GetRecordInfoByNvMBlockId                         */
/* Description   | Get record information by NvM block Id.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] BlockId : block Id.                                 */
/*               | [out] BlockRecordKindPtr :                               */
/*               | [out] RecordIndexPtr :                                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_GetBlockRecordKindByNvMBlockId
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC, AUTOMATIC ) BlockRecordKindPtr,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) RecordIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) recKind;
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) recKindNum;
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) tgtRecKind;

    VAR( Dem_BlockIdType, AUTOMATIC ) blockIdFirst;
    VAR( Dem_BlockIdType, AUTOMATIC ) blockIdNum;

    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) recordIndex;

    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) blockTargetIndex;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) blockSearchIndex;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) blockNumPerRecord;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) blockIndexFirst;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) blockTotalNum;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) blockCnt;

    retVal = DEM_IRT_NG;
    recKindNum = Dem_MMNvMRecKindNum;

    tgtRecKind  =   DEM_MMBLKRECKINDINDEX_INVALID;

    for( recKind = (Dem_u16_MMBlockRecKindIndexType)0U; recKind < recKindNum; recKind++ )   /* [GUD:for]recKind */
    {
        blockIdNum      =   Dem_RecordInfo_NvBlockTable[ recKind ].DemBlockTotalNum;        /* [GUD]recKind */
        blockIdFirst    =   Dem_RecordInfo_NvBlockTable[ recKind ].DemBlockIdFirst;         /* [GUD]recKind */

        if ( BlockId >= blockIdFirst )
        {
            if ( BlockId < ( blockIdFirst + blockIdNum ) )
            {
                /*  get record kind.        */
                tgtRecKind  =   recKind;                    /* [GUD]tgtRecKind */
                break;
            }
        }

    }

    if ( tgtRecKind != DEM_MMBLKRECKINDINDEX_INVALID )
    {
        *BlockRecordKindPtr      =   tgtRecKind;

        /*  get record index.               */
        blockIndexFirst     =   Dem_RecordInfo_NvBlockTable[ tgtRecKind ].DemBlockIndexFirst;       /* [GUD]tgtRecKind */
        blockNumPerRecord   =   Dem_RecordInfo_NvBlockTable[ tgtRecKind ].DemBlockNumPerRecord;     /* [GUD]tgtRecKind */
        blockTotalNum       =   Dem_RecordInfo_NvBlockTable[ tgtRecKind ].DemBlockTotalNum;         /* [GUD]tgtRecKind */

        blockIdFirst        =   Dem_RecordInfo_NvBlockTable[ recKind ].DemBlockIdFirst;             /* [GUD]recKind */
        blockTargetIndex    =   (( Dem_u16_NvBlockIndexType )BlockId - blockIdFirst ) + blockIndexFirst;

        if ( blockNumPerRecord == DEM_MEMINTO_1BLOCK_PER_RECORD )
        {
            /*  1record 1block      */
            recordIndex     =   ( Dem_u16_RecordIndexType )( blockTargetIndex - blockIndexFirst );
        }
        else if ( blockNumPerRecord == DEM_MEMINTO_2BLOCK_PER_RECORD )
        {
            /*  1record 2block      */
            recordIndex     =   ( Dem_u16_RecordIndexType )( blockTargetIndex - blockIndexFirst );
            recordIndex     =   recordIndex >> ( Dem_u16_RecordIndexType )1U;
        }
        else
        {
            /*  1record multiblock          */
            /*  first record index.             */
            recordIndex         =   ( Dem_u16_RecordIndexType )0U;
            blockCnt            =   ( Dem_u16_NvBlockIndexType )0U;

            /*  record block                    */
            blockSearchIndex    =   blockIndexFirst + blockNumPerRecord;

            /*  search block position.          */
            while( blockCnt <= blockTotalNum )
            {
                if ( blockTargetIndex >= blockSearchIndex )
                {
                    /*  check next record area.         */
                    blockSearchIndex    =   blockSearchIndex + blockNumPerRecord;
                    recordIndex         =   recordIndex + ( Dem_u16_RecordIndexType )1U;
                    blockCnt            =   blockCnt + blockNumPerRecord;
                }
                else
                {
                    break;  /*  find it.        */
                }
            }
        }

        *RecordIndexPtr =   recordIndex;
        retVal = DEM_IRT_OK;
    }

    return retVal;
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
