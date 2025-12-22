/* Dem_DataOeo_c(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataOeo/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DataOeo.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_OBD_SUPPORT == STD_ON )

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

static FUNC( Dem_u08_OBDOverwritePossibilityType, DEM_CODE ) Dem_DcOeo_CheckOBDEventOvw_MILcheck
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
static VAR( Dem_u08_FaultIndexType, DEM_VAR_NO_INIT ) Dem_TargetOfOBDonEdsFFD_FaultIndex;
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )   */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_OBDONEDS_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DcOeo_CheckOBDEventOverwritePossibility              */
/* Description   | check  MIL active and returns the result.                */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex                                          */
/*               |        Fault Index                                       */
/*               | [out] None                                               */
/* Return Value  | Dem_u08_OBDOverwritePossibilityType                      */
/*               |  DEM_OBDOVW_OVERWRITE_POSSIBLE               : overwrite possible.*/
/*               |  DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_MIL      : MIL active        */
/* Notes         | activate condition of this function is :                 */
/*               |           DEM_OBDONUDS_SUPPORT == STD_ON                 */
/*               |           DEM_WWH_OBD_SUPPORT  == STD_ON                 */
/*               |           DEM_ZEVONUDS_SUPPORT == STD_ON                 */
/*               | inactivate condition of this function is :               */
/*               |           DEM_OBDONEDS_SUPPORT                           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_OBDOverwritePossibilityType, DEM_CODE ) Dem_DcOeo_CheckOBDEventOverwritePossibility
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_OBDOverwritePossibilityType, AUTOMATIC ) retVal;

    retVal  =   Dem_DcOeo_CheckOBDEventOvw_MILcheck( FaultIndex );

    return retVal;
}

#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_OFF )     */
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcOeo_SetEdsOBDFFDTarget                             */
/* Description   | Initialize of OBDonEDS OBDFFD target.                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DcOeo_SetEdsOBDFFDTarget
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSearchPriority;

    /*  get current OBDonEDS OBDFFD target.     */
    Dem_TargetOfOBDonEdsFFD_FaultIndex  =   DEM_FAULTINDEX_INVALID;
    retSearchPriority   =   Dem_DataCtl_SearchPriorityOBDFreezeFrame( &eventStrgIndex, &faultIndex );
    if( retSearchPriority == DEM_IRT_OK )
    {
        Dem_TargetOfOBDonEdsFFD_FaultIndex  =   faultIndex;
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_DcOeo_CheckOBDEventOverwritePossibility              */
/* Description   | FaultIndex specified from the CALL source is Function    */
/*               |        that checks whether the rule is the oldest or     */
/*               |        MIL active and returns the result.                */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex                                          */
/*               |        Fault Index                                       */
/*               | [out] None                                               */
/* Return Value  | Dem_u08_OBDOverwritePossibilityType                      */
/*               |  DEM_OBDOVW_OVERWRITE_POSSIBLE               : overwrite possible.*/
/*               |  DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_OBDFFD   : oldest OBD        */
/*               |  DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_MIL      : MIL active        */
/* Notes         | activate condition of this function is :                 */
/*               |           DEM_OBDONEDS_SUPPORT == STD_ON                 */
/*               | inactivate condition of this function is :               */
/*               |           DEM_OBDONUDS_SUPPORT                           */
/*               |           DEM_WWH_OBD_SUPPORT                            */
/*               |           DEM_ZEVONUDS_SUPPORT                           */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_OBDOverwritePossibilityType, DEM_CODE ) Dem_DcOeo_CheckOBDEventOverwritePossibility
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_OBDOverwritePossibilityType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndexForOBDFFD;

    faultIndexForOBDFFD =   Dem_TargetOfOBDonEdsFFD_FaultIndex;
    if( faultIndexForOBDFFD == FaultIndex )
    {
        /*  it's not overwritten faultindex.            */
        retVal = DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_OBDFFD;
    }
    else
    {
        retVal  =   Dem_DcOeo_CheckOBDEventOvw_MILcheck( FaultIndex );
    }

    return retVal;
}
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_DcOeo_CheckOBDEventOvw_MILcheck                      */
/* Description   | check  MIL active and returns the result.                */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex                                          */
/*               |        Fault Index                                       */
/*               | [out] None                                               */
/* Return Value  | Dem_u08_OBDOverwritePossibilityType                      */
/*               |  DEM_OBDOVW_OVERWRITE_POSSIBLE               : overwrite possible.*/
/*               |  DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_MIL      : MIL active        */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_OBDOverwritePossibilityType, DEM_CODE ) Dem_DcOeo_CheckOBDEventOvw_MILcheck
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
)
{
    VAR( Dem_u08_OBDOverwritePossibilityType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetStatusOfDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventStrgIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) isMILIndicator;

    /*  initialize: possible overwritten.       */
    retVal = DEM_OBDOVW_OVERWRITE_POSSIBLE;

    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    resultOfGetEventStrgIndex = Dem_DataMngC_GetFR_EventStrgIndex( FaultIndex, &eventStrgIndex );   /* [GUD:RET:DEM_IRT_OK] eventStrgIndex */

    if( resultOfGetEventStrgIndex == DEM_IRT_OK )
    {
        /*  check target event has MIL attribute.       */
        isMILIndicator  =   Dem_CfgInfoPm_ChkDTCCls_HasMILInd( eventStrgIndex );        /* [GUD]eventStrgIndex */
        if( isMILIndicator == (boolean)TRUE )
        {
            statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
            /* Gets the status of DTC of the event record corresponding to the specified event index. */
            resultOfGetStatusOfDTC = Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );    /* [GUD]eventStrgIndex */
            /* Checks the result of retrieving the status of DTC of the event record. */
            if( resultOfGetStatusOfDTC == DEM_IRT_OK )
            {
                /*  bit7 == ON ?                */
                if (( statusOfDTC & DEM_UDS_STATUS_WIR ) == DEM_UDS_STATUS_WIR )    /*  statusOfDTC : bit7  */
                {
                    /*  it's not overwritten faultindex.        */
                    retVal = DEM_OBDOVW_OVERWRITE_IMPOSSIBLE_BY_MIL;
                }
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
