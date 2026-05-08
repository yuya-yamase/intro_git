/* Dem_UtlMem_c(v5-7-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UtlMem/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../inc/Dem_Utl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_UTILMEM_BYTE_SHIFT                                      ((uint8)0x08U)
#define DEM_UTILMEM_LOW_BYTE_MASK                                   ((uint16)0x00FFU)

#define DEM_UTILMEM_REMAINED_BUFSIZE_8                              ((uint16)8U)
#define DEM_UTILMEM_REMAINED_BUFSIZE_7                              ((uint16)7U)
#define DEM_UTILMEM_REMAINED_BUFSIZE_6                              ((uint16)6U)
#define DEM_UTILMEM_REMAINED_BUFSIZE_5                              ((uint16)5U)
#define DEM_UTILMEM_REMAINED_BUFSIZE_4                              ((uint16)4U)
#define DEM_UTILMEM_REMAINED_BUFSIZE_3                              ((uint16)3U)
#define DEM_UTILMEM_REMAINED_BUFSIZE_2                              ((uint16)2U)
#define DEM_UTILMEM_REMAINED_BUFSIZE_1                              ((uint16)1U)
#define DEM_UTILMEM_REMAINED_BUFSIZE_0                              ((uint16)0U)

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )

#define DEM_UTILMEM_CHECKSUM_CARRY_SHIFT                        ( (uint8)0x10U )
#define DEM_UTILMEM_CHECKSUM_CARRY_MASK                         ( (Dem_u32_FFCheckSumAddCarryType)0x0000FFFFU )

#define DEM_UTILMEM_CHECKSUM_STORE_SHIFT                        ( (uint8)0x08U )
#define DEM_UTILMEM_CHECKSUM_STORE_MASK                         ( (Dem_u16_FFCheckSumType)0x00FFU )

#endif  /*  ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )   */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON)
static FUNC( Dem_u32_FFCheckSumAddCarryType, DEM_CODE ) Dem_UtlMem_AddCarry
(
    VAR( Dem_u32_FFCheckSumAddCarryType, AUTOMATIC ) SumVal
);
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UtlMem_SplitByteData                                 */
/* Description   | Split 2byte data into 1byte.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] SplitData : 2-byte data to be split.                */
/*               | [out] UpperBytePtr : Upper-byte of SplitData.            */
/*               | [out] LowerBytePtr : Lower-byte of SplitData.            */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UtlMem_SplitByteData
(
    VAR( uint16, AUTOMATIC ) SplitData,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) UpperBytePtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) LowerBytePtr
)
{
    (*UpperBytePtr) = (uint8)( SplitData >> DEM_UTILMEM_BYTE_SHIFT );
    (*LowerBytePtr) = (uint8)( SplitData & DEM_UTILMEM_LOW_BYTE_MASK );

    return;
}


/****************************************************************************/
/* Function Name | Dem_UtlMem_ConvertByteData                               */
/* Description   | Convert 1byte data to 2byte.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] UpperByte : Upper-byte.                             */
/*               | [in] LowerByte : Lower-byte.                             */
/* Return Value  | uint16                                                   */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( uint16, DEM_CODE ) Dem_UtlMem_ConvertByteData
(
    VAR( uint8, AUTOMATIC ) UpperByte,
    VAR( uint8, AUTOMATIC ) LowerByte
)
{
    VAR( uint16, AUTOMATIC ) convertData;

    convertData = (uint16)( (uint16)UpperByte << DEM_UTILMEM_BYTE_SHIFT );
    convertData |= (uint16)LowerByte;

    return convertData;
}


/****************************************************************************/
/* Function Name | Dem_UtlMem_CopyMemory                                    */
/* Description   | Copy nonvolatile memory storage format.                  */
/* Preconditions |                                                          */
/* Parameters    | [out]  DestBufferPtr:                                    */
/*               |         The pointer for storage location for destination.*/
/*               | [in]   SrcBufferPtr :                                    */
/*               |         The pointer for storage location for source.     */
/*               | [in]  BufSize:                                           */
/*               |         The storage size of DestBufferPtr.               */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UtlMem_CopyMemory
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2CONST( uint8, AUTOMATIC , DEM_VAR_SAVED_ZONE ) SrcBufferPtr,
    VAR( uint16, AUTOMATIC ) BufSize
)
{
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) dstPtr;
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) srcPtr;
    VAR( uint16, AUTOMATIC ) bufSize;

    dstPtr = DestBufferPtr;
    srcPtr = SrcBufferPtr;
    bufSize = BufSize;

    while( bufSize >= DEM_UTILMEM_REMAINED_BUFSIZE_8 )
    {
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_7] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_7];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_7 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_7 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_6 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_6 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
        dstPtr = &dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_8];                                   /* [OUTOFTGT_ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_8 */
        srcPtr = &srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_8];                                   /* [OUTOFTGT_ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_8 */
        bufSize -= DEM_UTILMEM_REMAINED_BUFSIZE_8;
    }

    switch( bufSize )
    {
        case DEM_UTILMEM_REMAINED_BUFSIZE_7:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_6 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_6 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_6:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_5:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_4:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_3:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_2:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_1:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];/* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        default:
            /* No process */
            break;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UtlMem_SetMemory                                     */
/* Description   | Set nonvolatile memory storage format.                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [out] DestBufferPtr :                                    */
/*               |        The pointer for storage location for destination. */
/*               | [in] CharData :                                          */
/*               |        The pointer for storage location for source.      */
/*               | [in] Count :                                             */
/*               |         The storage size of DestBufferPtr.               */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UtlMem_SetMemory
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    VAR( uint8, AUTOMATIC ) CharData,
    VAR( uint16, AUTOMATIC ) Count
)
{
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) dstPtr;
    VAR( uint16, AUTOMATIC ) loopCnt;

    dstPtr = DestBufferPtr;
    loopCnt = Count;

    while( loopCnt >= DEM_UTILMEM_REMAINED_BUFSIZE_8 )
    {
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_7] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_7 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_6 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
        dstPtr = &dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_8];       /* [OUTOFTGT_ARYCHK] loopCnt/1/DEM_UTILMEM_REMAINED_BUFSIZE_8 */
        loopCnt -= DEM_UTILMEM_REMAINED_BUFSIZE_8;
    }

    switch( loopCnt )
    {
        case DEM_UTILMEM_REMAINED_BUFSIZE_7:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_6 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_6:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_5:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_4:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_3:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_2:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_1:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = CharData;/* [ARYCHK] loopCnt / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        default:
            /* No process */
            break;
    }

    return;
}

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON)
/****************************************************************************/
/* Function Name | Dem_UtlMem_CopyMemoryWithChecksum                        */
/* Description   | Copy nonvolatile memory storage format with checksum.    */
/* Preconditions |                                                          */
/* Parameters    | [out]  DestBufferPtr:                                    */
/*               |         The pointer for storage location for destination.*/
/*               | [in]   SrcBufferPtr :                                    */
/*               |         The pointer for storage location for source.     */
/*               | [in]  BufSize:                                           */
/*               |         The storage size of DestBufferPtr.               */
/*               | [in]  PosDataStart:                                      */
/*               |         The position of data start to store.             */
/*               | [in]  PosChecksumUpper:                                  */
/*               |         The position of checksum-upper byte to store.    */
/*               | [in]  PosChecksumLower:                                  */
/*               |         The position of checksum-lower byte to store.    */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UtlMem_CopyMemoryWithChecksum
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) DestBufferSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) DestBufferPtr,
    P2CONST( uint8, AUTOMATIC , DEM_VAR_NO_INIT ) SrcBufferPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) BufSize,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) PosDataStart,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) PosChecksumUpper,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) PosChecksumLower
)
{
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) dstPtr;
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) srcPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) bufSize;

    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) chksum;
    VAR( Dem_u32_FFCheckSumAddCarryType, AUTOMATIC ) sum;

    dstPtr = &DestBufferPtr[PosDataStart]; /* [ARYCHK] DestBufferSize/1/PosDataStart */
    srcPtr = SrcBufferPtr;
    bufSize = BufSize;
    sum = (Dem_u32_FFCheckSumAddCarryType)0U;

    while( bufSize >= DEM_UTILMEM_REMAINED_BUFSIZE_8 )
    {
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_7] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_7];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_7 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_7 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_6 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_6 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_5 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_5 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
        dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
        sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_7];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_7 */
        sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_6 */
        sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_5 */
        sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 */
        sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 */
        sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
        sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
        sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
        dstPtr = &dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_8];                                   /* [OUTOFTGT_ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_8 */
        srcPtr = &srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_8];                                   /* [OUTOFTGT_ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_8 */
        bufSize -= DEM_UTILMEM_REMAINED_BUFSIZE_8;
    }

    switch( bufSize )
    {
        case DEM_UTILMEM_REMAINED_BUFSIZE_7:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_6 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_6 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_5 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_5 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_6 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_5 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_6:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_5 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_5 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_5 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_5:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_4:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_3:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_2:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_1:
            dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0] = srcPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];    /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 *//* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            sum = sum + dstPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];     /*  no wrap around      */  /* [ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        default:
            /* No process */
            break;
    }

    sum = Dem_UtlMem_AddCarry( sum );
    chksum = (Dem_u16_FFCheckSumType)sum;

    DestBufferPtr[PosChecksumUpper] = (uint8)( chksum >> DEM_UTILMEM_CHECKSUM_STORE_SHIFT );    /* [ARYCHK] DestBufferSize/1/PosChecksumUpper */
    DestBufferPtr[PosChecksumLower] = (uint8)( chksum & DEM_UTILMEM_CHECKSUM_STORE_MASK );      /* [ARYCHK] DestBufferSize/1/PosChecksumLower */

    return;
}

/****************************************************************************/
/* Function Name | Dem_UtlMem_Checksum                                      */
/* Description   | Chekcs sum.                                              */
/* Preconditions |                                                          */
/* Parameters    | [in]   BufferPtr :                                       */
/*               |         The pointer for storage location for source.     */
/*               | [in]  BufSize:                                           */
/*               |         The storage size of DestBufferPtr.               */
/*               |                                                          */
/* Return Value  | Dem_u16_FFCheckSumType                                   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_UtlMem_Checksum
(
    P2CONST( uint8, AUTOMATIC , DEM_VAR_SAVED_ZONE ) BufferPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) BufSize
)
{
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) bufferPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) bufSize;

    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) chksum;
    VAR( Dem_u32_FFCheckSumAddCarryType, AUTOMATIC ) sum;

    bufferPtr = BufferPtr;
    bufSize = BufSize;
    sum = (Dem_u32_FFCheckSumAddCarryType)0U;

    while( bufSize >= DEM_UTILMEM_REMAINED_BUFSIZE_8 )
    {
        sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_7];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_7 */
        sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_6 */
        sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 */
        sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
        sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
        sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
        sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
        sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */

        bufferPtr = &bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_8];                                 /* [OUTOFTGT_ARYCHK] bufSize/1/DEM_UTILMEM_REMAINED_BUFSIZE_8 */
        bufSize -= DEM_UTILMEM_REMAINED_BUFSIZE_8;
    }

    switch( bufSize )
    {
        case DEM_UTILMEM_REMAINED_BUFSIZE_7:
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_6];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_6 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_6:
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_5];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_5 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_5:
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_4];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_4 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_4:
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_3];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_3 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_3:
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_2];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_2 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_2:
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_1];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_1 */
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        case DEM_UTILMEM_REMAINED_BUFSIZE_1:
            sum = sum + bufferPtr[DEM_UTILMEM_REMAINED_BUFSIZE_0];      /*  no wrap around      *//* [ARYCHK] bufSize / 1 / DEM_UTILMEM_REMAINED_BUFSIZE_0 */
            break;
        default:
            /* No process */
            break;
    }

    sum = Dem_UtlMem_AddCarry( sum );
    chksum = (Dem_u16_FFCheckSumType)sum;

    return chksum;
}

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UtlMem_SetChecksum                                   */
/* Description   | Set chekcs sum.                                          */
/* Preconditions |                                                          */
/* Parameters    | [in]  BufferPtr :                                        */
/*               |         The pointer for storage location for source.     */
/*               | [in]  Checksum:                                          */
/*               |         Checksum.                                        */
/*               | [in]  PosChecksumUpper:                                  */
/*               |         The position of checksum-upper byte to store.    */
/*               | [in]  PosChecksumLower:                                  */
/*               |         The position of checksum-lower byte to store.    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UtlMem_SetChecksum
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) BufferSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) BufferPtr,
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) Checksum,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) PosChecksumUpper,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) PosChecksumLower
)
{
    BufferPtr[PosChecksumUpper] = (uint8)( Checksum >> DEM_UTILMEM_CHECKSUM_STORE_SHIFT ); /* [ARYCHK] BufferSize/1/PosChecksumUpper */
    BufferPtr[PosChecksumLower] = (uint8)( Checksum & DEM_UTILMEM_CHECKSUM_STORE_MASK ); /* [ARYCHK] BufferSize/1/PosChecksumLower */

    return;
}
#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_UtlMem_AddCarry                                      */
/* Description   | Adds carry of sum.                                       */
/* Preconditions |                                                          */
/* Parameters    | [in]  Sum:                                               */
/*               |         The total value of data for checksum.            */
/*               |                                                          */
/* Return Value  | uint32                                                   */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( Dem_u32_FFCheckSumAddCarryType, DEM_CODE ) Dem_UtlMem_AddCarry
(
    VAR( Dem_u32_FFCheckSumAddCarryType, AUTOMATIC ) SumVal
)
{
    VAR( Dem_u32_FFCheckSumAddCarryType, AUTOMATIC ) carry;
    VAR( Dem_u32_FFCheckSumAddCarryType, AUTOMATIC ) sum;

    sum = SumVal;

    if( sum > DEM_UTILMEM_CHECKSUM_CARRY_MASK )
    {
        carry = sum >> DEM_UTILMEM_CHECKSUM_CARRY_SHIFT;
        sum = ( sum & DEM_UTILMEM_CHECKSUM_CARRY_MASK ) + carry;        /*  no wrap around      */
    }

    return sum;
}
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
