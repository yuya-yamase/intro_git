/* Dem_Utl_Similar_c(v5-9-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Utl_Similar/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
#include "../../../inc/Dem_Utl_Similar.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif  /* DEM_SIT_RANGE_CHECK */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_UTLSIM_BITSHIFT_8  ((uint32) 8U)
#define DEM_UTLSIM_BITSHIFT_16 ((uint32)16U)
#define DEM_UTLSIM_BITSHIFT_24 ((uint32)24U)

#define DEM_UTLSIM_BUF_UINT32POS_1  ((Dem_u08_SimilarConditionIndexType) 1U)
#define DEM_UTLSIM_BUF_UINT32POS_2  ((Dem_u08_SimilarConditionIndexType) 2U)
#define DEM_UTLSIM_BUF_UINT32POS_3  ((Dem_u08_SimilarConditionIndexType) 3U)
#define DEM_UTLSIM_BUF_UINT32_SIZE  ((Dem_u08_SimilarConditionIndexType) 4U)

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


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UtlSimilar_CnvBinaryToSimilarConditionArray          */
/* Description   | Convert binary array to SimilarCondition array.          */
/* Preconditions |                                                          */
/* Parameters    | [out]  SimilarConditionArrayPtr:                         */
/*               |         The pointer for storage location for destination.*/
/*               | [in]   BufferPtr :                                       */
/*               |         The pointer for storage location for source.     */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UtlSimilar_CnvBinaryToSimilarConditionArray
(
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionArrayPtr,
    P2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr
)
{
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) idx;
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) buffidx;
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) similartypeNum;

    similartypeNum  =   Dem_SimilartypeNum;

    buffidx = (Dem_u08_SimilarConditionIndexType)0U;
    for ( idx = (Dem_u08_SimilarConditionIndexType)0U; idx < similartypeNum; idx++ )    /* [GUD:for]idx */
    {
        SimilarConditionArrayPtr[ idx ] = ( Dem_SimilarConditionValueType )( ( (uint32)BufferPtr[ buffidx ]) |                              /* [GUD]buffidx *//* [ARYCHK] DEM_SIT_R_CHK_SIMILAR_CONDITION_ARRAY_SIZE / 1 / idx *//* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE-(DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4) / 1 / buffidx *//* [ARYDESC]DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4:DEM_SPCEVT_DATABUF_SIMILARCONDITION */
                                             ( ((uint32)BufferPtr[DEM_UTLSIM_BUF_UINT32POS_1 + buffidx ]) << DEM_UTLSIM_BITSHIFT_8  ) |     /* [GUD]buffidx *//* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE-(DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4) / 1 / DEM_UTLSIM_BUF_UINT32POS_1+buffidx *//* [ARYDESC]DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4:DEM_SPCEVT_DATABUF_SIMILARCONDITION */
                                             ( ((uint32)BufferPtr[DEM_UTLSIM_BUF_UINT32POS_2 + buffidx ]) << DEM_UTLSIM_BITSHIFT_16 ) |     /* [GUD]buffidx *//* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE-(DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4) / 1 / DEM_UTLSIM_BUF_UINT32POS_2+buffidx *//* [ARYDESC]DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4:DEM_SPCEVT_DATABUF_SIMILARCONDITION */
                                             ( ((uint32)BufferPtr[DEM_UTLSIM_BUF_UINT32POS_3 + buffidx ]) << DEM_UTLSIM_BITSHIFT_24 ) );    /* [GUD]buffidx *//* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE-(DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4) / 1 / DEM_UTLSIM_BUF_UINT32POS_3+buffidx *//* [ARYDESC]DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4:DEM_SPCEVT_DATABUF_SIMILARCONDITION */
        buffidx = buffidx + DEM_UTLSIM_BUF_UINT32_SIZE;                         /* [GUD:logic]buffidx */
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_UtlSimilar_CnvSimilarConditionArrayToBinary          */
/* Description   | Convert SimilarCondition array to binary array.          */
/* Preconditions |                                                          */
/* Parameters    | [out]  BufferPtr:                                        */
/*               |         The pointer for storage location for destination.*/
/*               | [in]   SimilarConditionArrayPtr :                        */
/*               |         The pointer for storage location for source.     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UtlSimilar_CnvSimilarConditionArrayToBinary
(
    P2VAR( uint8, AUTOMATIC , DEM_APPL_DATA ) BufferPtr,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionArrayPtr
)
{
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) idx;
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) buffidx;
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) similartypeNum;

    similartypeNum  =   Dem_SimilartypeNum;

    buffidx = (Dem_u08_SimilarConditionIndexType)0U;
    for ( idx = (Dem_u08_SimilarConditionIndexType)0U; idx < similartypeNum; idx++ )    /* [GUD:for]idx */
    {
        BufferPtr[buffidx]  = (uint8)( SimilarConditionArrayPtr[ idx ] );       /* [GUD]buffidx *//* [GUD]idx *//* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE - (DEM_ASYNCDATAQUE_EVENTSTATUS_POS + 4) / 1 / buffidx *//* [ARYCHK] DEM_SIT_R_CHK_SIMILAR_CONDITION_ARRAY_SIZE / 1 / idx *//* [ARYDESC]DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4:DEM_SPCEVT_DATABUF_SIMILARCONDITION */
        BufferPtr[buffidx + DEM_UTLSIM_BUF_UINT32POS_1]  = (uint8)( ((uint32)SimilarConditionArrayPtr[ idx ]) >> DEM_UTLSIM_BITSHIFT_8  );      /* [GUD]buffidx *//* [GUD]idx *//* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE - (DEM_ASYNCDATAQUE_EVENTSTATUS_POS + 4) / 1 / buffidx+DEM_UTLSIM_BUF_UINT32POS_1 *//* [ARYCHK] DEM_SIT_R_CHK_SIMILAR_CONDITION_ARRAY_SIZE / 1 / idx *//* [ARYDESC]DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4:DEM_SPCEVT_DATABUF_SIMILARCONDITION */
        BufferPtr[buffidx + DEM_UTLSIM_BUF_UINT32POS_2]  = (uint8)( ((uint32)SimilarConditionArrayPtr[ idx ]) >> DEM_UTLSIM_BITSHIFT_16 );      /* [GUD]buffidx *//* [GUD]idx *//* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE - (DEM_ASYNCDATAQUE_EVENTSTATUS_POS + 4) / 1 / buffidx+DEM_UTLSIM_BUF_UINT32POS_2 *//* [ARYCHK] DEM_SIT_R_CHK_SIMILAR_CONDITION_ARRAY_SIZE / 1 / idx *//* [ARYDESC]DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4:DEM_SPCEVT_DATABUF_SIMILARCONDITION */
        BufferPtr[buffidx + DEM_UTLSIM_BUF_UINT32POS_3]  = (uint8)( ((uint32)SimilarConditionArrayPtr[ idx ]) >> DEM_UTLSIM_BITSHIFT_24 );      /* [GUD]buffidx *//* [GUD]idx *//* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE - (DEM_ASYNCDATAQUE_EVENTSTATUS_POS + 4) / 1 / buffidx+DEM_UTLSIM_BUF_UINT32POS_3 *//* [ARYCHK] DEM_SIT_R_CHK_SIMILAR_CONDITION_ARRAY_SIZE / 1 / idx *//* [ARYDESC]DEM_ASYNCDATAQUE_EVENTSTATUS_POS+4:DEM_SPCEVT_DATABUF_SIMILARCONDITION */
        buffidx = buffidx + DEM_UTLSIM_BUF_UINT32_SIZE;                         /* [GUD:logic]buffidx */
    }
    return ;
}

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UtlSimilar_CopySimilarConditionArray                 */
/* Description   | Copy nonvolatile memory storage format.                  */
/* Preconditions |                                                          */
/* Parameters    | [out]  DestSimilarConditionArrayPtr:                     */
/*               |         The pointer for storage location for destination.*/
/*               | [in]   SrcSimilarConditionArrayPtr :                     */
/*               |         The pointer for storage location for source.     */
/*               | [in]   NumberOfSimilarCondition:                         */
/*               |         number of array DestSimilarConditionArrayPtr.    */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UtlSimilar_CopySimilarConditionArray
(
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) DestSimilarConditionArrayPtr,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) SrcSimilarConditionArrayPtr
)
{
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) idx;
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) similartypeNum;

    similartypeNum  =   Dem_SimilartypeNum;
    for ( idx = (Dem_u08_SimilarConditionIndexType)0U; idx < similartypeNum; idx++ )    /* [GUD:for]idx */
    {
        DestSimilarConditionArrayPtr[ idx ] = SrcSimilarConditionArrayPtr[ idx ];   /* [GUD]idx *//* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / idx *//* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / idx */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_UtlSimilar_SetSimilarConditionArray                  */
/* Description   | Copy nonvolatile memory storage format.                  */
/* Preconditions |                                                          */
/* Parameters    | [out]  DestSimilarConditionArrayPtr:                     */
/*               |         The pointer for storage location for destination.*/
/*               | [in]   Value :                                           */
/*               |         set value.                                       */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UtlSimilar_SetSimilarConditionArray
(
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) DestSimilarConditionArrayPtr,
    VAR( Dem_SimilarConditionValueType, AUTOMATIC ) Value
)
{
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) idx;
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) similartypeNum;

    similartypeNum  =   Dem_SimilartypeNum;
    for ( idx = (Dem_u08_SimilarConditionIndexType)0U; idx < similartypeNum; idx++ )    /* [GUD:for]idx */
    {
        DestSimilarConditionArrayPtr[ idx ] = Value;    /* [GUD]idx *//* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / idx */
    }
    return ;
}
#endif /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
