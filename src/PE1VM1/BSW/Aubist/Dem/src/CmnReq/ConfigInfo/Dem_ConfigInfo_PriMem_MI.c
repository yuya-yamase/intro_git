/* Dem_ConfigInfo_PriMem_MI_c(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_PriMem_MI/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )

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
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) chkClass;

    chkClass    =   Dem_CfgInfoPm_GetIsMILIndicator( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */

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
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) chkClass;

    chkClass    =   Dem_CfgInfoPm_GetIsWIRIndicator( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */

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

#if ( DEM_PFC_SUPPORT == STD_ON )
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
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) chkClass;

    chkClass    =   Dem_CfgInfoPm_GetIsMILIndicator( EventStrgIndex );  /* [GUDCHK:CALLER]EventStrgIndex */

    return chkClass;
}
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

#if ( DEM_OBD_SUPPORT == STD_ON )
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
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
