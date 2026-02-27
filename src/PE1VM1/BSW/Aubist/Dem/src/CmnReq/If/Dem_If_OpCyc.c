/* Dem_If_OpCyc_c(v5-5-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_OpCyc/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnIf_Control.h"

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
/* Function Name | Dem_RestartOperationCycle                                */
/* Description   | Sets an operation cycle state.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleId :                                  */
/*               |        Identification of operation cycle, like power cy- */
/*               |        cle, driving cycle.                               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : set of operation cycle was accepted and w- */
/*               |        ill be handled asynchronously.                    */
/*               |        E_NOT_OK : set of operation cycle was rejected.   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_RestartOperationCycle
(
    VAR( uint8, AUTOMATIC ) OperationCycleId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;
    internalReturnValue = Dem_Control_RestartOperationCycle( (Dem_u08_OpCycleIndexType)OperationCycleId );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = E_OK;
            break;
        case DEM_IRT_NG:
            /* No Process */
            break;
        default:
            /* No Process */
            break;
    }

    return retVal;
}

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_SetCycleQualified                                    */
/* Description   | Sets a dependent operation cycle as qualified, so it may */
/*               | be processed along with its leading cycle.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleId :                                  */
/*               |        Identification of a configured DemOperationCycle. */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetCycleQualified
(
    VAR( uint8, AUTOMATIC ) OperationCycleId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;
    internalReturnValue = Dem_Control_SetCycleQualified( (Dem_u08_OpCycleIndexType)OperationCycleId );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = E_OK;
            break;
        case DEM_IRT_NG:
            /* No Process */
            break;
        default:
            /* No Process */
            break;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetCycleQualified                                    */
/* Description   | Returns the qualification state of the dependent operat- */
/*               | ion cycle.                                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleId :                                  */
/*               |        Identification of a configured DemOperationCycle. */
/*               | [out] IsQualified :                                      */
/*               |        TRUE  : The dependent operation cylcle is qualif- */
/*               |                ied.                                      */
/*               |        FALSE : The qualification conditions of the depe- */
/*               |                ndent operation cylcle have not been met. */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetCycleQualified
(
    VAR( uint8, AUTOMATIC ) OperationCycleId,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) IsQualified
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) cycleQualified;

    retVal = E_NOT_OK;

    if( IsQualified != NULL_PTR )
    {
        cycleQualified = (boolean)FALSE;    /*  out parameter.  */
        internalReturnValue = Dem_Control_GetCycleQualified( (Dem_u08_OpCycleIndexType)OperationCycleId, &cycleQualified );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *IsQualified = cycleQualified;  /*  set value to out parameter. */
                retVal = E_OK;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            default:
                /* No Process */
                break;
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}
#endif  /* ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )     */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
