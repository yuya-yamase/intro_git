/* Dem_MM_BlockTable_c(v5-7-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MM_BlockTable/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Mm_MM.h"
#include "Dem_MM_local.h"
#include "../../../cfg/Dem_MM_Cfg.h"

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

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
/* Function Name | Dem_MM_GetNvBlockIndex                                   */
/* Description   | Process of acquiring nonvolatile block management infor- */
/*               | mation.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecIndex :                                          */
/*               |        Record Index                                      */
/*               | [in] DataOffset :                                        */
/*               |        DataOffset (for FFR,TSFFR)                        */
/*               | [in] RecKind :                                           */
/*               |        Record kind                                       */
/*               | [out] ListIndexPtr :                                     */
/*               |        List Index                                        */
/* Return Value  | void                                                     */
/*               |                                                          */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MM_GetNvBlockIndex
(
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecIndex,
    VAR( Dem_u16_RecordDataSizeType, AUTOMATIC ) DataOffset,
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) BlockRecordKind,      /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_NvBlockIndexType, AUTOMATIC, AUTOMATIC ) ListIndexPtr
)
{
    /* ListIndex is  Calculated  from BlockRecordKind, RecIndex and RecordDataOffset */
    *ListIndexPtr = (Dem_u16_NvBlockIndexType)( Dem_RecordInfo_NvBlockTable[BlockRecordKind].DemBlockIndexFirst     /* [GUDCHK:CALLER]BlockRecordKind */
                    + ( RecIndex * Dem_RecordInfo_NvBlockTable[BlockRecordKind].DemBlockNumPerRecord )              /* [GUDCHK:CALLER]BlockRecordKind */
                    + DataOffset );

    return ;
}


/****************************************************************************/
/* Function Name | Dem_MM_GetNvBlockInfo                                    */
/* Description   | Process of acquiring nonvolatile block management infor- */
/*               | mation.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] ListIndex :                                         */
/*               |        NvRamBlockListIndex                               */
/*               | [out] NvBlockTypePtr :                                   */
/*               |         NvBlockInfomation                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_GetNvBlockInfo
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    P2VAR( Dem_NvBlockType, AUTOMATIC, AUTOMATIC ) NvBlockTypePtr
)
{
    /* Auto variable definition */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )  retVal;
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) recKind;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC )    nvBlockIndexInRecKind;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) targetPtr;
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) recKindNum;
    VAR( Dem_u16_RecordDataSizeType, AUTOMATIC )  recPtrOffset;

    /* Variable initialization */
    retVal = DEM_IRT_NG;
    recKindNum = Dem_MMNvMRecKindNum;

    for( recKind = (Dem_u16_MMBlockRecKindIndexType)0U; recKind < recKindNum; recKind++ )   /* [GUD:for]recKind */
    {
        if( ( Dem_RecordInfo_NvBlockTable[recKind].DemBlockIndexFirst <= ListIndex ) &&     /* [GUD]recKind */
            ( ListIndex <= Dem_RecordInfo_NvBlockTable[recKind].DemBlockIndexLast ) )       /* [GUD]recKind */
        {
            nvBlockIndexInRecKind                  = ListIndex - Dem_RecordInfo_NvBlockTable[recKind].DemBlockIndexFirst;               /* [GUD]recKind */
            /* Block ID */
            NvBlockTypePtr->DemNvRamBlockId        = Dem_RecordInfo_NvBlockTable[recKind].DemBlockIdFirst + nvBlockIndexInRecKind;      /* [GUD]recKind */
            /* Block Length */
            NvBlockTypePtr->DemNvBlockLength       = Dem_RecordInfo_NvBlockTable[recKind].DemBlockSize;                                 /* [GUD]recKind */
            /* RamBlockDataAddress */
            targetPtr                              = (P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ))( Dem_RecordInfo_NvBlockTable[recKind].DemRamDataFirstPtr );        /* [GUD]recKind */
            recPtrOffset                           = (Dem_u16_BlockSizeType)( nvBlockIndexInRecKind * NvBlockTypePtr->DemNvBlockLength );   /* [GUD:logic]recPtrOffset */

            /* Do not access outside the targetPtr[recPtrOffset] because it is consistent with Aubist-Configurator */
            NvBlockTypePtr->DemRamBlockDataAddress = (P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ))&targetPtr[recPtrOffset];           /* [GUD]recPtrOffset *//* [ARYCHK] (Dem_RecordInfo_NvBlockTable[recKind].DemBlockSize)*(Dem_RecordInfo_NvBlockTable[recKind].DemBlockTotalNum) / 1 / recPtrOffset */

            NvBlockTypePtr->BlockRecordKind = recKind;

            retVal = DEM_IRT_OK;

            break;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
