/* Dem_PreFFD_FFDOutputJudge_c(v5-5-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PreFFD_FFDOutputJudge/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_Utl.h"
#include "Dem_PreFFD_FFDOutputJudge.h"


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
/* Function Name | Dem_PreFFD_SetFFDOutputJudge                             */
/* Description   | Sets FFDOutputJudge and returns FFD output allow.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DidClassPtr :                                       */
/*               |       The pointer of  DIDClassTable.                     */
/*               | [out] FreezeFrameDataPtr :                               */
/*               |       The pointer of freeze frame data.                  */
/*               | {in/out] FreezeFrameDataOffsetPtr :                      */
/*               |       The pointer of freeze frame data offset.           */
/* Return Value  | boolean                                                  */
/*               |       TRUE  : FFDOutput allow.                           */
/*               |       FALSE : FFDOutout not allow.                       */
/* Notes         | -                                                        */
/****************************************************************************/
#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_PreFFD_SetFFDOutputJudge
(
    P2CONST( AB_83_ConstV Dem_DidClassType, AUTOMATIC, DEM_CONFIG_DATA ) DidClassPtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FreezeFrameDataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameDataOffsetPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) useFFDOutputJudge;
    VAR( Dem_FFDOutputJudgeType, AUTOMATIC ) ffdOutputJudge;
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) didIdentifier;

    retVal = (boolean)TRUE;

    useFFDOutputJudge = DidClassPtr->DemUseFFDOutputJudge;
    if( useFFDOutputJudge == (boolean)TRUE )
    {
        didIdentifier = DidClassPtr->DemDidIdentifier;
        ffdOutputJudge = Dem_GetFFDOutputJudge( didIdentifier );
        FreezeFrameDataPtr[(*FreezeFrameDataOffsetPtr)] = ffdOutputJudge;

        (*FreezeFrameDataOffsetPtr) = (*FreezeFrameDataOffsetPtr) + (Dem_u16_FFDStoredIndexType)1U;

        if( ffdOutputJudge == DEM_FFDOUTPUT_NOT_ALLOW )
        {
            retVal = (boolean)FALSE;
        }
    }

    return retVal;
}
#endif /* (DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON) */
#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_OFF )
FUNC( boolean, DEM_CODE ) Dem_PreFFD_SetFFDOutputJudge
(
    P2CONST( AB_83_ConstV Dem_DidClassType, AUTOMATIC, DEM_CONFIG_DATA ) DidClassPtr, /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FreezeFrameDataPtr, /* MISRA DEVIATION */
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameDataOffsetPtr /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) retVal;

    /* This is empty function for function switching. */

    retVal = (boolean)TRUE;

    return retVal;
}
#endif /* ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_OFF ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
