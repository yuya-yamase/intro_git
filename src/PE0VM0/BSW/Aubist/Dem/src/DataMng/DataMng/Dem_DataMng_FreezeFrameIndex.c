/* Dem_DataMng_FreezeFrameIndex_c(v5-5-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataMng_FreezeFrameIndex/CODE                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../inc/Dem_Rc_DataMng.h"
#include "Dem_DataMng_FreezeFrame.h"
#include "Dem_DataMng_local.h"

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

static VAR( Dem_u08_FFDIndexType, DEM_VAR_NO_INIT ) Dem_DataMng_SearchFFDIndex;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static VAR( Dem_u08_FFDIndexType, DEM_VAR_NO_INIT ) Dem_DataMng_SearchObdFFDIndex;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataMng_ClearSearchFFDIndex                           */
/* Description   | Set SearchFFDIndex                                       */
/*               |  format.                                                 */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_ClearSearchFFDIndex
( void )
{
    Dem_DataMng_SearchFFDIndex = (Dem_u08_FFDIndexType)0U;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_DataMng_SearchObdFFDIndex = (Dem_u08_FFDIndexType)0U;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    return;
}


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngM_UpdateSearchFFDIndex                        */
/* Description   | Update Minimam Value Of EmptyFreezeFrameIndex            */
/* Preconditions |                                                          */
/* Parameters    | [in] EmptyFreezeFrameIndex                               */
/*               |        Index of Empty FreezeFrame Record                 */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngM_UpdateSearchFFDIndex
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) EmptyFreezeFrameIndex
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;

    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    if( EmptyFreezeFrameIndex < nonObdFFDRecordNum )
    {
        if( EmptyFreezeFrameIndex <  Dem_DataMng_SearchFFDIndex )
        {
            Dem_DataMng_SearchFFDIndex = EmptyFreezeFrameIndex;
        }
        else
        {
            /* No process */
        }
    }

    return;
}


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngM_UpdateSearchObdFFDIndex                     */
/* Description   | Update Minimam Value Of EmptyFreezeFrameIndex for OBD    */
/* Preconditions |                                                          */
/* Parameters    | [in] EmptyFreezeFrameIndex                               */
/*               |        Index of Empty FreezeFrame Record for OBD         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngM_UpdateSearchObdFFDIndex
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) EmptyFreezeFrameIndex
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;

    obdFFDRecordNum = Dem_ObdFFDRecordNum;

    if( EmptyFreezeFrameIndex < obdFFDRecordNum )
    {
        if( EmptyFreezeFrameIndex <  Dem_DataMng_SearchObdFFDIndex )
        {
            Dem_DataMng_SearchObdFFDIndex = EmptyFreezeFrameIndex;
        }
        else
        {
            /* No process */
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetEmptyFFDIndex                            */
/* Description   | Get Index of Empty FreezeFrame Record                    */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | Index of Empty FreezeFrame Record                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_DataMngC_GetEmptyFFDIndex
( void )
{
    /* Variable declaration */
    VAR( Dem_u08_FFDIndexType, AUTOMATIC  ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    posRecordStatus = Dem_NonObdFreezeFrameDataPosTable.RecordStatus;                                                                   /* [GUD:CFG]posRecordStatus */

    for( freezeFrameRecordIndex = Dem_DataMng_SearchFFDIndex; freezeFrameRecordIndex < nonObdFFDRecordNum; freezeFrameRecordIndex++)    /* [GUD:for]freezeFrameRecordIndex */
    {
        if( Dem_FreezeFrameRecordList[freezeFrameRecordIndex].Data[posRecordStatus] != DEM_FFD_STORED)                                  /* [GUD]freezeFrameRecordIndex *//* [GUD]posRecordStatus */
        {
            break;
        }
        else
        {
            /* No process */
        }
    }

    if( freezeFrameRecordIndex >= nonObdFFDRecordNum )
    {
        Dem_DataMng_SearchFFDIndex = nonObdFFDRecordNum;
    }
    else
    {
        Dem_DataMng_SearchFFDIndex = freezeFrameRecordIndex + (Dem_u08_FFDIndexType)1U;
    }

    return freezeFrameRecordIndex;
}


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetEmptyObdFFDIndex                         */
/* Description   | Get Index of Empty FreezeFrame Record                    */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | Index of Empty FreezeFrame Record                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_DataMngC_GetEmptyObdFFDIndex
( void )
{
    /* Variable declaration */
    VAR( Dem_u08_FFDIndexType, AUTOMATIC  ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    obdFFDRecordNum = Dem_ObdFFDRecordNum;
    posRecordStatus = Dem_ObdFreezeFrameDataPosTable.RecordStatus;                                                                      /* [GUD:CFG]posRecordStatus */

    for( freezeFrameRecordIndex = Dem_DataMng_SearchObdFFDIndex; freezeFrameRecordIndex < obdFFDRecordNum; freezeFrameRecordIndex++)    /* [GUD:for]freezeFrameRecordIndex */
    {
        if( Dem_ObdFreezeFrameRecordList[freezeFrameRecordIndex].Data[posRecordStatus] != DEM_FFD_STORED)                               /* [GUD]freezeFrameRecordIndex *//* [GUD]posRecordStatus */
        {
            break;
        }
        else
        {
            /* No process */
        }
    }

    if( freezeFrameRecordIndex >= obdFFDRecordNum )
    {
        Dem_DataMng_SearchObdFFDIndex = obdFFDRecordNum;
    }
    else
    {
        Dem_DataMng_SearchObdFFDIndex = freezeFrameRecordIndex + (Dem_u08_FFDIndexType)1U;
    }

    return freezeFrameRecordIndex;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
