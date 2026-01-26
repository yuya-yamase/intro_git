/* Dem_ConfigInfo_PriMem_MI_WWH_c(v5-5-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_PriMem_MI_WWH/CODE                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_Control.h"

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
/* Function Name | Dem_CfgInfoPm_ChkDTCCls_MILONAtConfirmed                 */
/* Description   | Check DTCClass type of eventStrgIndex.                   */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex : Event Storage index.               */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : matched.                                  */
/*               |        FALSE : no matched.                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_MILONAtConfirmed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) chkClass;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;

    chkClass    =   (boolean)FALSE;
    dtcClass    =   Dem_CfgInfoPm_GetDTCSeverityClass( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
    if ( dtcClass == DEM_DTC_CLASS_1 )
    {
        chkClass    =   (boolean)TRUE;
    }

    return chkClass;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_ChkDTCCls_WIRbitONAtConfirmed              */
/* Description   | Check DTCClass type of eventStrgIndex.                   */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex : Event Storage index.               */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : matched.                                  */
/*               |        FALSE : no matched.                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_WIRbitONAtConfirmed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) chkClass;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;

    chkClass    =   (boolean)FALSE;

    dtcClass    =   Dem_CfgInfoPm_GetDTCSeverityClass( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
    if ( dtcClass == DEM_DTC_CLASS_1 )
    {
        chkClass    =   (boolean)TRUE;
    }
    else
    if ( ( dtcClass == DEM_DTC_CLASS_0 ) || ( dtcClass == DEM_SEVERITY_NO_SEVERITY ) )
    {
        /*  CLASS_0 : check WIR indicator status.(for user indicator).      */
        chkClass    =   Dem_CfgInfoPm_GetIsWIRIndicator( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */
    }
    else
    {
        /*  CLASS_2 - CLASS_4 : Don't change WIR bit to ON.     */
    }

    return chkClass;
}

#if ( DEM_INDICATOR_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_ChkDTCCls_WIRbitOFFAtHealing               */
/* Description   | Check DTCClass type of eventStrgIndex.                   */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex : Event Storage index.               */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : matched.                                  */
/*               |        FALSE : no matched.                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_WIRbitOFFAtHealing
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) chkClass;

    chkClass    =   Dem_CfgInfoPm_GetIsWIRIndicator( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */

    return chkClass;
}
#endif  /* ( DEM_INDICATOR_USE == STD_ON )  */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_ChkDTCCls_AFACBitONAtCycUpd                */
/* Description   | Check DTCClass type of eventStrgIndex.                   */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex : Event Storage index.               */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : matched.                                  */
/*               |        FALSE : no matched.                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_AFACBitONAtCycUpd
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) chkClass;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;

    chkClass    =   (boolean)FALSE;
    dtcClass    =   Dem_CfgInfoPm_GetDTCSeverityClass( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
    if (( dtcClass == DEM_DTC_CLASS_2 ) || ( dtcClass == DEM_DTC_CLASS_3 ))
    {
        chkClass    =   (boolean)TRUE;
    }

    return chkClass;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_ChkDTCCls_UseB1Counter                     */
/* Description   | Check DTCClass type of eventStrgIndex.                   */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex : Event Storage index.               */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : matched.                                  */
/*               |        FALSE : no matched.                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_UseB1Counter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) chkClass;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;

    chkClass    =   (boolean)FALSE;
    dtcClass    =   Dem_CfgInfoPm_GetDTCSeverityClass( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
    if ( dtcClass == DEM_DTC_CLASS_2 )
    {
        chkClass    =   (boolean)TRUE;
    }

    return chkClass;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_ChkDTCCls_HasContinuousMI                  */
/* Description   | Check DTCClass type of eventStrgIndex.                   */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex : Event Storage index.               */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : matched.                                  */
/*               |        FALSE : no matched.                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_HasContinuousMI
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) chkClass;

    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcClass;

    chkClass    =   (boolean)FALSE;
    dtcClass    =   Dem_CfgInfoPm_GetDTCSeverityClass( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
    if (( dtcClass == DEM_DTC_CLASS_1 ) ||( dtcClass == DEM_DTC_CLASS_2 ))
    {
        chkClass    =   (boolean)TRUE;
    }

    return chkClass;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_IsMILInd                                   */
/* Description   | Check DTCClass type of eventStrgIndex.                   */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventStrgIndex : Event Storage index.               */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : matched.                                  */
/*               |        FALSE : no matched.                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_HasMILInd
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) chkClass;

    chkClass    =   Dem_CfgInfoPm_GetIsMILIndicator( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */

    return chkClass;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetB1CounterThreshold                      */
/* Description   | Get Configuration value Dem_WWHOBDB1CounterThreshold     */
/* Preconditions | -                                                        */
/* Parameters    | void                                                     */
/* Return Value  | Dem_u32_B1CounterType                                    */
/*               |        B1 Counter Threshold.                             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u32_B1CounterType, DEM_CODE ) Dem_CfgInfoPm_GetB1CounterThreshold
( void )
{
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1CounterThreshold;
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1CounterHold;

    Dem_CfgInfoPm_GetB1CounterThresholdAndHold( &b1CounterThreshold, &b1CounterHold );

    return b1CounterThreshold;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetB1CounterHold                           */
/* Description   | Get Configuration value Dem_WWHOBDB1CounterHold          */
/* Preconditions | -                                                        */
/* Parameters    | void                                                     */
/* Return Value  | Dem_u32_B1CounterType                                    */
/*               |        B1 Counter Hold.                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u32_B1CounterType, DEM_CODE ) Dem_CfgInfoPm_GetB1CounterHold
( void )
{
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1CounterThreshold;
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1CounterHold;

    Dem_CfgInfoPm_GetB1CounterThresholdAndHold( &b1CounterThreshold, &b1CounterHold );

    return b1CounterHold;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
