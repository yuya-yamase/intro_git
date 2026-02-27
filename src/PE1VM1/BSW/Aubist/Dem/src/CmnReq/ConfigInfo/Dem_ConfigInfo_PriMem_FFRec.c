/* Dem_ConfigInfo_PriMem_FFRec_c(v5-10-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_PriMem_FFRec/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forOutput         */
/* Description   | get FreezeFrameRecordTrigger type.                       */
/* Preconditions | ( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum ) */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                       */
/*               |          FreezeFrameRecordClassIndex.                    */
/*               | [out] FreezeFrameRecordNumberPtr :                       */
/*               |          FreezeFrameRecordNumber.                        */
/*               | [out] FreezeFrameRecordTriggerPtr :                      */
/*               |        FreezeFrameRecordTrigger type.                    */
/*               | [out] FreezeFrameRecordToDcmPtr :                        */
/*               |          output to Dcm or not.                           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forOutput
(
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,               /*  [PRMCHK:CALLER]     */
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordNumberPtr,
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordToDcmPtr
)
{
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;

    *FreezeFrameRecordNumberPtr     =   Dem_FreezeFrameRecordClassTable[ FreezeFrameRecordClassIndex ].DemFreezeFrameRecordNumber;  /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex  */
    *FreezeFrameRecordToDcmPtr      =   Dem_FreezeFrameRecordClassTable[ FreezeFrameRecordClassIndex ].DemFreezeFrameRecordToDcm;   /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex  */

    /*  trigger type.               */
    freezeFrameRecordTrigger        =   Dem_FreezeFrameRecordClassTable[ FreezeFrameRecordClassIndex ].DemFreezeFrameRecordTrigger; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex  */
    *FreezeFrameRecordTriggerPtr    =   freezeFrameRecordTrigger & DEM_TRIGGER_ON_TRIGGERTYPE_MASK;

    return ;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forOutputOBDFFD   */
/* Description   | get FreezeFrameRecordTrigger type.                       */
/* Preconditions | ( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum ) */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                       */
/*               |          FreezeFrameRecordClassIndex.                    */
/*               | [out] FreezeFrameRecordNumberPtr :                       */
/*               |          FreezeFrameRecordNumber.                        */
/*               | [out] FreezeFrameRecordTriggerPtr :                      */
/*               |        FreezeFrameRecordTrigger type.                    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forOutputOBDFFD
(
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,               /*  [PRMCHK:CALLER]     */
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordNumberPtr,
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr
)
{
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;

    *FreezeFrameRecordNumberPtr     =   Dem_FreezeFrameRecordClassTable[ FreezeFrameRecordClassIndex ].DemFreezeFrameRecordNumber;  /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex  */

    /*  trigger type.               */
    freezeFrameRecordTrigger        =   Dem_FreezeFrameRecordClassTable[ FreezeFrameRecordClassIndex ].DemFreezeFrameRecordTrigger; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex  */
    *FreezeFrameRecordTriggerPtr    =   freezeFrameRecordTrigger & DEM_TRIGGER_ON_TRIGGERTYPE_MASK;

    return ;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetFreezeFrameRecordTriggerType            */
/* Description   | get FreezeFrameRecordTrigger type.                       */
/* Preconditions | ( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum ) */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                       */
/*               |          FreezeFrameRecordClassIndex.                    */
/* Return Value  | Dem_u08_StorageTriggerType                               */
/*               |        FreezeFrameRecordTrigger type.                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_StorageTriggerType, DEM_CODE ) Dem_CfgInfoPm_GetFreezeFrameRecordTriggerType
(
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex    /*  [PRMCHK:CALLER]     */
)
{
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;

    /*  trigger type.               */
    freezeFrameRecordTrigger    =   Dem_FreezeFrameRecordClassTable[ FreezeFrameRecordClassIndex ].DemFreezeFrameRecordTrigger; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex  */
    freezeFrameRecordTrigger    =   freezeFrameRecordTrigger & DEM_TRIGGER_ON_TRIGGERTYPE_MASK;

    return freezeFrameRecordTrigger;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forCapture      */
/* Description   | get FreezeFrameRecordTrigger type.(for capture)          */
/* Preconditions | ( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum ) */
/* Parameters    | [in] FreezeFrameRecordClassIndex :                       */
/*               |          FreezeFrameRecordClassIndex.                    */
/*               | [out] FreezeFrameRecordUpdatePtr :                       */
/*               |          FreezeFrameRecordUpdate.                        */
/* Return Value  | Dem_u08_StorageTriggerType                               */
/*               |        FreezeFrameRecordTrigger type.                    */
/* Notes         | After returning from this function, call function        */
/*               | Dem_CfgInfo_CheckTrigger() next to update the trigger type. */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_StorageTriggerType, DEM_CODE ) Dem_CfgInfoPm_GetFreezeFrameRecordInfo_forCapture
(
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,    /*  [PRMCHK:CALLER]     */
    P2VAR( Dem_u08_UpdateRecordType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordUpdatePtr
)
{
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;

    *FreezeFrameRecordUpdatePtr =   Dem_FreezeFrameRecordClassTable[ FreezeFrameRecordClassIndex ].DemFreezeFrameRecordUpdate; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex  */

    /*  trigger type & update type.     */
    freezeFrameRecordTrigger    =   Dem_FreezeFrameRecordClassTable[ FreezeFrameRecordClassIndex ].DemFreezeFrameRecordTrigger; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex  */

    return freezeFrameRecordTrigger;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
