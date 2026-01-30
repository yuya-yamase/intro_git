/* Dem_If_PFC_c(v5-6-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_PFC/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_Control_OBD.h"

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

#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetPermanentUDSDTC                                   */
/* Description   | Get PermanentDTC                                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] PermanentDTCBufferPtr :                            */
/*               |        PemanetDTC                                        */
/*               | [out] PermanentDTCNumPtr :                               */
/*               |        PemanetDTC Number                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_GetPermanentOBDDTC.            */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetPermanentUDSDTC
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCNumPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( uint8, AUTOMATIC ) permanentDTCNum;

    retVal = E_NOT_OK;
    if( PermanentDTCNumPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( PermanentDTCBufferPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        permanentDTCNum = (uint8)0U;  /*  out paramter.   */
        internalReturnValue = Dem_Control_GetPermanentUDSDTC( PermanentDTCBufferPtr, &permanentDTCNum );
        *PermanentDTCNumPtr = permanentDTCNum;

        if( internalReturnValue == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
    }

    return retVal;

}

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetPermanentOBDDTC                                   */
/* Description   | Get PermanentDTC                                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] PermanentDTCBufferPtr :                            */
/*               |        PemanetDTC                                        */
/*               | [out] PermanentDTCNumPtr :                               */
/*               |        PemanetDTC Number                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_GetPermanentDTC(v5-3-0).                 */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetPermanentOBDDTC
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCNumPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC )    retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( uint8, AUTOMATIC ) permanentDTCNum;

    retVal = E_NOT_OK;
    if( PermanentDTCNumPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( PermanentDTCBufferPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        permanentDTCNum = (uint8)0U;  /*  out paramter.   */
        internalReturnValue = Dem_Control_GetPermanentOBDDTC( PermanentDTCBufferPtr, &permanentDTCNum );
        *PermanentDTCNumPtr = permanentDTCNum;

        if( internalReturnValue == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
    }
    return retVal;

}
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_GetClearPFCCycleQualified                            */
/* Description   | Gets PFC cycle qualified.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] PassedCycleQualifiedPtr :                          */
/*               | [out] DrivingConditionQualifiedPtr :                     */
/*               | [out] PFCCycleQualifiedPtr :                             */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetClearPFCCycleQualified
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) PassedCycleQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) DrivingConditionQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) PFCCycleQualifiedPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) passedCycleQualified;
    VAR( boolean, AUTOMATIC ) drivingConditionQualified;
    VAR( boolean, AUTOMATIC ) pfcCycleQualified;

    retVal = E_NOT_OK;

    if( PassedCycleQualifiedPtr == NULL_PTR )
    {
        /*  no process      */
    }
    else
    if( DrivingConditionQualifiedPtr == NULL_PTR )
    {
        /*  no process      */
    }
    else
    if( PFCCycleQualifiedPtr == NULL_PTR )
    {
        /*  no process      */
    }
    else
    {
        passedCycleQualified        = (boolean)FALSE;
        drivingConditionQualified   = (boolean)FALSE;
        pfcCycleQualified           = (boolean)FALSE;
        internalReturnValue = Dem_Control_GetClearPFCCycleQualified( EventId, &passedCycleQualified, &drivingConditionQualified, &pfcCycleQualified );

        if( internalReturnValue == DEM_IRT_OK )
        {
            *PassedCycleQualifiedPtr        = passedCycleQualified;
            *DrivingConditionQualifiedPtr   = drivingConditionQualified;
            *PFCCycleQualifiedPtr           = pfcCycleQualified;
            retVal = E_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_CheckExistPermanentDTCByEventId                      */
/* Description   | check exist PFC.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               | [out] IsPermanentDTCPtr :                                */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_GetClearPFCCycleQualified.      */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_CheckExistPermanentDTCByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) IsPermanentDTCPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) isPermanentDTC;

    retVal = E_NOT_OK;

    if( IsPermanentDTCPtr == NULL_PTR )
    {
        /*  no process      */
    }
    else
    {
        isPermanentDTC      = (boolean)FALSE;
        internalReturnValue = Dem_Control_CheckExistPermanentDTCByEventId( EventId, &isPermanentDTC );

        if( internalReturnValue == DEM_IRT_OK )
        {
            *IsPermanentDTCPtr      = isPermanentDTC;
            retVal = E_OK;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetEventIdWithPermanentDTC                           */
/* Description   | Get eventId list.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [out] EventIdBufferPtr :  EventId list.                  */
/*               | [out] EventIdNumPtr :  EventId list number.              */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_GetEventIdWithPendingDTC.      */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventIdWithPermanentDTC
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) EventIdNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_EventIdType, AUTOMATIC ) eventIdNum;

    retVal = E_NOT_OK;

    if( EventIdBufferPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( EventIdNumPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        eventIdNum      =   (Dem_EventIdType)0U;
        internalReturnValue  =   Dem_Control_GetEventIdWithPermanentDTC( EventIdBufferPtr, &eventIdNum );
        *EventIdNumPtr  =   eventIdNum;

        if( internalReturnValue == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
    }
    return retVal;
}

#if ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DisablePFCRecordUpdate                               */
/* Description   | Disable PFC Record update.                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : set of event status was successful         */
/*               |        E_NOT_OK : set of PFC memory Suppression event st-*/
/*               |        atus failed or could not be accepted (e.g.        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DisablePFCRecordUpdate
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_DisablePFCRecordUpdate();

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
/* Function Name | Dem_EnablePFCRecordUpdate                                */
/* Description   | Enable PFC Record update.                                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : set of event status was successful         */
/*               |        E_NOT_OK : set of PFC memory Suppression event st-*/
/*               |        atus failed or could not be accepted (e.g.        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_EnablePFCRecordUpdate
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_EnablePFCRecordUpdate();

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
#endif /* ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_ClearAllPFC                                          */
/* Description   | Clear all PFC Record forcibly.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ClearAllPFC
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    internalReturnValue = Dem_Control_ClearAllPFC();

    if( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
