/* Dem_If_DTR_OBD_c(v5-3-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_DTR_OBD/CODE                                       */
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

#include "../../../inc/Dem_Pm_Control_DTR.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
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
/* Function Name | Dem_SetDTR                                               */
/* Description   | Reports a DTR result with lower and upper limit.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTRId      : DTR identifier.                        */
/*               | [in] TestResult : Test result of DTR.                    */
/*               | [in] LowerLimit : Lower limit of DTR.                    */
/*               | [in] UpperLimit : Upper limit of DTR.                    */
/*               | [in] Ctrlval    : Control value of the DTR to support    */
/*               |                   its interpretation Dem-internally.     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Report of DTR result successful.       */
/*               |        E_NOT_OK : Report of DTR result failed.           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetDTR
(
    VAR( uint16, AUTOMATIC ) DTRId,
    VAR( sint32, AUTOMATIC ) TestResult,
    VAR( sint32, AUTOMATIC ) LowerLimit,
    VAR( sint32, AUTOMATIC ) UpperLimit,
    VAR( Dem_DTRControlType, AUTOMATIC ) Ctrlval
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC) internalReturnValue;

    retVal = E_NOT_OK;

    /* Queues the DTR report */
    internalReturnValue = Dem_Control_SetDTR( (Dem_u16_DTRIndexType)DTRId, (Dem_s32_DTRValueRawType)TestResult, (Dem_s32_DTRValueRawType)LowerLimit, (Dem_s32_DTRValueRawType)UpperLimit, Ctrlval);

    /* Converts return value */
    if ( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}

#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetDTR                                               */
/* Description   | Gets a DTR result with lower and upper limit.            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DTRId          : DTR identifier.                   */
/*               | [out] TestResultPtr  : Test result of DTR.               */
/*               | [out] LowerLimitPtr  : Lower limit of DTR.               */
/*               | [out] UpperLimitPtr  : Upper limit of DTR.               */
/*               | [out] CtrlvalPtr     : Control value of the DTR .        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Report of DTR result successful.       */
/*               |        E_NOT_OK : Report of DTR result failed.           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetDTR
(
    VAR( uint16, AUTOMATIC ) DTRId,
    P2VAR( sint32, AUTOMATIC, DEM_APPL_DATA ) TestResultPtr,
    P2VAR( sint32, AUTOMATIC, DEM_APPL_DATA ) LowerLimitPtr,
    P2VAR( sint32, AUTOMATIC, DEM_APPL_DATA ) UpperLimitPtr,
    P2VAR( Dem_DTRControlType, AUTOMATIC, DEM_APPL_DATA ) CtrlvalPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_DtrDataType, AUTOMATIC ) dtrData;

    retVal = E_NOT_OK;

    if( TestResultPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( LowerLimitPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( UpperLimitPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( CtrlvalPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        dtrData.TIDValue   = ((Dem_u08_DTRTidIndexType)0U);
        dtrData.UaSID      = ((Dem_u08_DTRUasidType)0U);
        dtrData.TestResult = ((Dem_u16_DTRValueStoreType)0U);
        dtrData.LowerLimit = ((Dem_u16_DTRValueStoreType)0U);
        dtrData.UpperLimit = ((Dem_u16_DTRValueStoreType)0U);
        dtrData.CtrlVal    = DEM_DTR_CTL_NORMAL;

        dtrData.RawTestResult = ((Dem_s32_DTRValueRawType)0);
        dtrData.RawLowerLimit = ((Dem_s32_DTRValueRawType)0);
        dtrData.RawUpperLimit = ((Dem_s32_DTRValueRawType)0);

        /* Gets the DTR report */
        internalReturnValue = Dem_Control_GetDTR(DTRId, &dtrData);

        /* Converts return value */
        if ( internalReturnValue == DEM_IRT_OK )
        {
            *TestResultPtr = (sint32)dtrData.RawTestResult;
            *LowerLimitPtr = (sint32)dtrData.RawLowerLimit;
            *UpperLimitPtr = (sint32)dtrData.RawUpperLimit;
            *CtrlvalPtr    = dtrData.CtrlVal;

            retVal = E_OK;
        }
    }

    return retVal;
}
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
