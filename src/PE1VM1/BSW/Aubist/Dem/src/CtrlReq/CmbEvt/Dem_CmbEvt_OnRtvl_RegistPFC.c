/* Dem_CmbEvt_OnRtvl_RegistPFC_c(v5-5-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmbEvt_OnRtvl_RegistPFC/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
#if ( DEM_PFC_SUPPORT == STD_ON )

#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Rc_PFCMng.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

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
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section               */
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section               */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_CmbEvt_CheckRegistPFC                                */
/* Description   | check regist PFC.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : regist OK.                                */
/*               |        FALSE : regist NG.                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckRegistPFC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexPFC;
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) obdDTCValueRegist;
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) obdDTCValuePFC;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retGetPFCResult;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    retVal = (boolean)TRUE;
    pfcRecordNum = Dem_PFCRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* check base : */
    /* get ObdDTCValue */
    obdDTCValueRegist =   Dem_CfgInfoPm_GetObdDTCValue( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */

    /* check PFC record : */
    for( pfcRecordIndex = ( Dem_u08_PFCIndexType )0U; pfcRecordIndex < pfcRecordNum; pfcRecordIndex++ )
    {
        /* Get EventStrgIndex */
        retGetPFCResult = Dem_PFCMng_GetPFCRecordData( pfcRecordIndex, &eventStrgIndexPFC );
        if ( retGetPFCResult == DEM_IRT_OK )
        {
            if ( eventStrgIndexPFC < eventStorageNum )          /* [GUD:if]eventStrgIndexPFC */
            {
                /* check all PFCRecord */
                obdDTCValuePFC =   Dem_CfgInfoPm_GetObdDTCValue( eventStrgIndexPFC );   /* [GUD]eventStrgIndexPFC */
                if( obdDTCValuePFC == obdDTCValueRegist )
                {
                    /* if matched, not output */
                    retVal = (boolean)FALSE;
                    break;
                }
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_OFF )  */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CmbEvt_CheckRegistPFC                                */
/* Description   | check regist PFC.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : regist OK.                                */
/*               |        FALSE : regist NG.                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckRegistPFC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexPFC;
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) obdDTCValueRegist;
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) obdDTCValuePFC;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) maxNumberEventEntryPermanent;
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) retGetPFCResult;
    VAR( boolean, AUTOMATIC ) retKindOfMisfire;
    VAR( boolean, AUTOMATIC ) retKindOfMisfirePFC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    retVal = (boolean)TRUE;
    maxNumberEventEntryPermanent = Dem_MaxNumberEventEntryPermanent;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* check misfire event. */
    retKindOfMisfire    =   Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );   /* [GUD:RET:TRUE] EventStrgIndex */
    if ( retKindOfMisfire == (boolean)TRUE )
    {
        /* misfire event is always regist OK. */
    }
    else
    {
        /* check base : */
        /* get ObdDTCValue */
        obdDTCValueRegist =   Dem_CfgInfoPm_GetObdDTCValue( EventStrgIndex );       /* [GUDCHK:CALLER]EventStrgIndex */

        /* check PFC record : */
        for( pfcRecordIndex = ( Dem_u08_PFCIndexType )0U; pfcRecordIndex < maxNumberEventEntryPermanent; pfcRecordIndex++ )
        {
            /* Get EventStrgIndex */
            retGetPFCResult = Dem_PFCMng_GetPFCRecordData( pfcRecordIndex, &eventStrgIndexPFC );
            if ( retGetPFCResult == DEM_IRT_OK )
            {
                if ( eventStrgIndexPFC < eventStorageNum )                                      /* [GUD:if]eventStrgIndexPFC */
                {
                    retKindOfMisfirePFC    =   Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndexPFC ); /* [GUD:RET:TRUE] eventStrgIndexPFC */
                    if ( retKindOfMisfirePFC == (boolean)FALSE )
                    {
                        /* check all PFCRecord */
                        obdDTCValuePFC =   Dem_CfgInfoPm_GetObdDTCValue( eventStrgIndexPFC );   /* [GUD]eventStrgIndexPFC */

                        if( obdDTCValuePFC == obdDTCValueRegist )
                        {
                            /* if matched, not output */
                            retVal = (boolean)FALSE;
                            break;
                        }
                    }
                }
            }
        }
    }
    return retVal;
}
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
