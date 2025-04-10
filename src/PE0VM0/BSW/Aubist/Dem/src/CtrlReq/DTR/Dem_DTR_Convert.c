/* Dem_DTR_Convert_c(v5-3-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTR_Convert/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_DTR_SUPPORT == STD_ON )

#include "../../../inc/Dem_Pm_DTR.h"
#include "Dem_DTR_Convert.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_DTR_ADJUST_LIMIT ((Dem_u16_DTRValueStoreType)1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC(void, DEM_CODE) Dem_DTR_AdjustDTRResult
(
    VAR( Dem_u08_DTRUasidType, AUTOMATIC ) DtrUasid,
    P2VAR( Dem_DTRConvertOutputType, AUTOMATIC, AUTOMATIC ) DtrConvertOutputPtr
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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DTR_ConvertLinearAndAdjust                           */
/* Description   | Converts linear and Adjust DTR                           */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DTRConvertInputPtr  : DTR input data.              */
/*               | [out] DTRConvertOutputPtr : DTR output data.             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTR_ConvertLinearAndAdjust
(
    P2CONST( Dem_DTRConvertInputType, AUTOMATIC, AUTOMATIC ) DtrConvertInputPtr,
    P2VAR( Dem_DTRConvertOutputType, AUTOMATIC, AUTOMATIC ) DtrConvertOutputPtr
)
{
    /*  call callout function.      */
    Dem_DTR_ConvertLinear( DtrConvertInputPtr, DtrConvertOutputPtr );

    /* Adjusts DtrData if DTR result is changed */
    Dem_DTR_AdjustDTRResult( DtrConvertInputPtr->DtrUasid, DtrConvertOutputPtr );

    return;
}

/****************************************************************************/
/* Function Name | Dem_DTR_AdjustDTRResult                                  */
/* Description   | Adjust DtrData if DTR result is changed                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] DtrUasid       : DTR UasId.                         */
/* Parameters    | [in/out] DtrConvertOutputPtr  : DTR data pointer         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(void, DEM_CODE) Dem_DTR_AdjustDTRResult
(
    VAR( Dem_u08_DTRUasidType, AUTOMATIC ) DtrUasid,
    P2VAR( Dem_DTRConvertOutputType, AUTOMATIC, AUTOMATIC ) DtrConvertOutputPtr
)
{
    VAR( Dem_s16_DTRValueStoreType, AUTOMATIC ) tmpLowerLimit;
    VAR( Dem_s16_DTRValueStoreType, AUTOMATIC ) tmpUpperLimit;

    if ( DtrConvertOutputPtr->ConvertInfo == DEM_DTR_TESTRESULT_INVALID_LOWER )
    {
        if ( DtrUasid >= DEM_DTR_UASID_SIGNED )
        {
            if ( (( Dem_s16_DTRValueStoreType )( DtrConvertOutputPtr->LowerLimit )) <= (( Dem_s16_DTRValueStoreType )( DtrConvertOutputPtr->TestResult )) )
            {
                tmpLowerLimit = ( Dem_s16_DTRValueStoreType )( DtrConvertOutputPtr->LowerLimit ) + ( Dem_s16_DTRValueStoreType )DEM_DTR_ADJUST_LIMIT;
                DtrConvertOutputPtr->LowerLimit = ( Dem_u16_DTRValueStoreType )tmpLowerLimit;
            }
        }
        else
        {
            if ( DtrConvertOutputPtr->LowerLimit <= DtrConvertOutputPtr->TestResult )
            {
                DtrConvertOutputPtr->LowerLimit = DtrConvertOutputPtr->LowerLimit + DEM_DTR_ADJUST_LIMIT;
            }
        }
    }
    else if ( DtrConvertOutputPtr->ConvertInfo == DEM_DTR_TESTRESULT_INVALID_UPPER )
    {
        if ( DtrUasid >= DEM_DTR_UASID_SIGNED )
        {
            if ( ((Dem_s16_DTRValueStoreType)( DtrConvertOutputPtr->UpperLimit )) >= ((Dem_s16_DTRValueStoreType)( DtrConvertOutputPtr->TestResult )) )
            {
                tmpUpperLimit = ( Dem_s16_DTRValueStoreType )( DtrConvertOutputPtr->UpperLimit ) - ( Dem_s16_DTRValueStoreType )DEM_DTR_ADJUST_LIMIT;
                DtrConvertOutputPtr->UpperLimit = ( Dem_u16_DTRValueStoreType )tmpUpperLimit;
            }
        }
        else
        {
            if ( DtrConvertOutputPtr->UpperLimit >= DtrConvertOutputPtr->TestResult )
            {
                DtrConvertOutputPtr->UpperLimit = DtrConvertOutputPtr->UpperLimit - DEM_DTR_ADJUST_LIMIT;
            }
        }
    }
    else
    {
        /* No Process */
    }

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
