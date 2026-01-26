/* Dem_DataCtl_InfoFFD_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_InfoFFD/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Rc_DataMng.h"

#include "Dem_DataCtl_local.h"

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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetFFRTriggerByFFRClassIndex                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/*               | [out] FreezeFrameRecordTriggerPtr :                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRTriggerByFFRClassIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,      /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr
)
{
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;

    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    /* Initializes the auto variable. */
    retVal = DEM_IRT_NG;
    ffrRecordClassConfigureNum = Dem_FFRRecordClassConfigureNum;

    /* Checks the reference of freeze frame class. */
    Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef ); /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */
    if( freezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                                                           /* [GUD:if] freezeFrameClassRef */
    {
        /* Checks the reference of freeze frame record number class. */
        if( freezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                           /* [GUD:if] freezeframeRecNumClassRef */
        {
            /* Holds the FreezeFrameRecNumClass table pointed to */
            /* by the FreezeFrameRecNumClass table list Index of the held DTCAttribute table. */
            freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[freezeframeRecNumClassRef];                /* [GUD] freezeframeRecNumClassRef */

            /* Holds the DemFreezeFrameRecordIndex pointed to */
            /* by the DemFreezeFrameRecordClassRef Index of the held FreezeFrameRecNumClass table. */
            freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[FreezeFrameRecordClassIndex]; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */

            if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                          /* [GUD:if] freezeFrameRecordClassIndex */
            {
                /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex. */
                *FreezeFrameRecordTriggerPtr = Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex].DemFreezeFrameRecordTrigger;    /* [GUD] freezeFrameRecordClassIndex */
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT    STD_ON ) */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_CheckStoredOBDFFDInFaultRecord                  */
/* Description   | Check OBD FFD is stored.                                 */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultRecordPtr :                                    */
/*               |        The pointer of fault record which to check.       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : OBD FFD is stored                    */
/*               |        DEM_IRT_NG : OBD FFD is not stored                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CheckStoredOBDFFDInFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )  retVal;
    VAR( boolean, AUTOMATIC ) existDataFlag;

    retVal = DEM_IRT_NG;

    SchM_Enter_Dem_EventMemory();

    /*  get fault record.       */
    existDataFlag = Dem_DataMngC_GetFR_CheckExistOBDFFD( FaultIndex );

    SchM_Exit_Dem_EventMemory();

    if ( existDataFlag == (boolean)TRUE )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )    */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_JudgeOutputOBDFFDTrigger                        */
/* Description   | Judge whether to output OBDFFD of specified trigger.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] StatusOfDTC    : statusOfDTC.                       */
/*               | [in] FreezeFrameRecordTrigger : Trigger of stored OBDFFD */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : OBDFFD can be output                        */
/*               |      FALSE : OBDFFD cannot be output                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Data_JudgeOutputOBDFFDTrigger
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) StatusOfDTC,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) outputPendingOBDFFDWithoutCDTC;

    /* Sets the return value to TRUE (OBDFFD can be output). */
    retVal = (boolean)TRUE;

    if( FreezeFrameRecordTrigger == DEM_TRIGGER_ON_PENDING )
    {
        /* Checks condition that can be output OBDFFD of pending trigger. */
        outputPendingOBDFFDWithoutCDTC = Dem_CfgInfoPm_JudgeOutputPendingOBDFFDWithoutCDTC();
        if( outputPendingOBDFFDWithoutCDTC == (boolean)FALSE )
        {
            if( ( StatusOfDTC & DEM_UDS_STATUS_CDTC ) != DEM_UDS_STATUS_CDTC )  /*  statusOfDTC : bit3  */
            {
                /* Sets the return value to FALSE (OBDFFD cannot be output). */
                retVal = (boolean)FALSE;
            }
        }
    }

    return retVal;
}
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
