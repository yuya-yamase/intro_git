/* Dem_DataCtl_FFDOutputJudge_c(v5-7-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_FFDOutputJudge/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl_FFDOutputJudge.h"
#include "../../../usr/Dem_FFDOutputJudge_Callout.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif /* DEM_SIT_RANGE_CHECK */


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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_Data_SetFFDOutputJudge                               */
/* Description   | Sets FFDOutputJudge and returns FFD output allow.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DidClassIndex :                                     */
/*               |       The index of  DIDClassTable.                       */
/*               | [out] FreezeFrameDataPtr :                               */
/*               |       The pointer of freeze frame data.                  */
/*               |          DEM_VAR_NO_INIT    : FreezeFrame                */
/*               |          DEM_VAR_SAVED_ZONE : prestoreFreezeFrame        */
/*               | {in/out] FreezeFrameDataOffsetPtr :                      */
/*               |       The pointer of freeze frame data offset.           */
/* Return Value  | boolean                                                  */
/*               |       TRUE  : FFDOutput allow.                           */
/*               |       FALSE : FFDOutout not allow.                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Data_SetFFDOutputJudge
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) FreezeFrameDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2CONST( AB_83_ConstV Dem_DidClassType, AUTOMATIC, DEM_CONFIG_DATA ) DidClassPtr,   /* MISRA DEVIATION *//* [PRMCHK:CALLER] */
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FreezeFrameDataPtr,                   /* MISRA DEVIATION */
    P2VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameDataOffsetPtr  /* MISRA DEVIATION *//* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) retVal;

#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )  /* [FuncSw] */
    VAR( boolean, AUTOMATIC ) useFFDOutputJudge;
    VAR( Dem_FFDOutputJudgeType, AUTOMATIC ) ffdOutputJudge;
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) didIdentifier;
#endif  /* ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )       */

    retVal = (boolean)TRUE;

#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )  /* [FuncSw] */
    useFFDOutputJudge   =   DidClassPtr->DemUseFFDOutputJudge;                      /* [GUDCHK:CALLER]DidClassPtr */
    if( useFFDOutputJudge == (boolean)TRUE )
    {
        didIdentifier = DidClassPtr->DemDidIdentifier;                              /* [GUDCHK:CALLER]DidClassPtr */
        ffdOutputJudge = Dem_GetFFDOutputJudge( didIdentifier );                                        /* [GUDCHK:CALLER](*FreezeFrameDataOffsetPtr) */
        FreezeFrameDataPtr[(*FreezeFrameDataOffsetPtr)] = ffdOutputJudge;                               /* [GUDCHK:CALLER](*FreezeFrameDataOffsetPtr) *//* [ARYCHK] FreezeFrameDataSize / 1 / (*FreezeFrameDataOffsetPtr) */

        /* (*FreezeFrameDataOffsetPtr) value range is 0x0001-0xFFFF(width of Dem_u16_FFDStoredIndexType), so no wrap around.      */
        (*FreezeFrameDataOffsetPtr) = (*FreezeFrameDataOffsetPtr) + (Dem_u32_FFDStoredIndexType)1U;     /* no wrap around */

        if( ffdOutputJudge == DEM_FFDOUTPUT_NOT_ALLOW )
        {
            retVal = (boolean)FALSE;
        }
    }
#endif  /* ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )       */

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_AddFFDOutputJudgeSize                           */
/* Description   | Adds FFDOutputJudge sieze.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] DidClassIndex :                                     */
/*               |       The index of  DIDClassTable.                       */
/*               | {in/out] AddedDataSizePtr :                              */
/*               |       The pointer of cumulative DidDataSize.             */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_AddFFDOutputJudgeSize
(
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) DidClassIndex,          /* [PRMCHK:CALLER] */
    P2VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) AddedDataSizePtr
)
{
    VAR( boolean, AUTOMATIC ) useFFDOutputJudge;

    useFFDOutputJudge   =   Dem_DIDClassTable[DidClassIndex].DemUseFFDOutputJudge;                      /* [GUDCHK:CALLER]DidClassIndex */
    if( useFFDOutputJudge == (boolean)TRUE )
    {
        /* (*AddedDataSizePtr) value range is 0x0001-0xFFFF(width of Dem_u16_FFDStoredIndexType), so no wrap around.      */
        (*AddedDataSizePtr) = (*AddedDataSizePtr) + (Dem_u32_FFDStoredIndexType)1U;  /* Add 1-byte for FFDOutputJudge. *//* no wrap around */
    }

    return;
}
#endif /* (DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON) */

/****************************************************************************/
/* Function Name | Dem_Data_GetFFDOutputAllow                               */
/* Description   | Gets FFDOutputJudge.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] DidClassIndex :                                     */
/*               |       The index of  DIDClassTable.                       */
/*               | [in] FreezeFrameDataPtr :                                */
/*               |       The pointer of freeze frame data.                  */
/*               | [in/out] FreezeFrameDataOffsetPtr :                      */
/*               |       The pointer of freeze frame data offset.           */
/* Return Value  | boolean                                                  */
/*               |       TRUE  : FFDOutput allow.                           */
/*               |       FALSE : FFDOutout not allow.                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Data_GetFFDOutputAllow
(
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) DidClassIndex,  /* MISRA DEVIATION *//* [PRMCHK:CALLER] */
    VAR( uint8, AUTOMATIC ) FFDOutputJudge,                     /* MISRA DEVIATION */
    P2VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameDataOffsetPtr  /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) ffdOutputAllow;

#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )  /* [FuncSw] */
    VAR( boolean, AUTOMATIC ) useFFDOutputJudge;
#endif  /* ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )       */


    ffdOutputAllow = (boolean)TRUE;


#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )  /* [FuncSw] */
    useFFDOutputJudge   =   Dem_DIDClassTable[DidClassIndex].DemUseFFDOutputJudge;                      /* [GUDCHK:CALLER]DidClassIndex */

    if( useFFDOutputJudge == (boolean)TRUE )
    {
        /* (*FreezeFrameDataOffsetPtr) value range is 0x0001-0xFFFF(width of Dem_u16_FFDStoredIndexType), so no wrap around.      */
        (*FreezeFrameDataOffsetPtr) = (*FreezeFrameDataOffsetPtr) + (Dem_u32_FFDStoredIndexType)1U;     /* no wrap around */

        if( FFDOutputJudge == DEM_FFDOUTPUT_NOT_ALLOW ) /* DEM_FFDOUTPUT_ALLOW and 0xFF returns TRUE. */
        {
            ffdOutputAllow = (boolean)FALSE;
        }
    }
#endif  /* ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )       */

    return ffdOutputAllow;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
