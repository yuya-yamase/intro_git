/* Dem_OpCycle_ProgressEngineRPM_c(v5-5-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OpCycle_ProgressEngineRPM/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )

#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_Rc_OpCycleMng.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
typedef uint8   Dem_u08_ProgressEngine1000rpmType;

#define     DEM_ENGINERPM_4000RPM       ((Dem_u08_ProgressEngine1000rpmType)4U)

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

static VAR( Dem_u08_ProgressEngine1000rpmType, DEM_VAR_NO_INIT )    Dem_ProgressEngine1000rpm;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_OpCycle_ClearProgressEngine1000RPM                   */
/* Description   | clear progress engine 1000rpm.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycle_ClearProgressEngine1000RPM
( void )
{
    Dem_ProgressEngine1000rpm   =   ( Dem_u08_ProgressEngine1000rpmType )0U;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_OpCycle_UpdateProgressEngine1000RPM                  */
/* Description   | update progress engine 1000rpm and check reach 4000rpm.  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | if reached 4000rpm, set Engine4000PRMOccurred status.    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycle_UpdateProgressEngine1000RPM
( void )
{
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) engine4000rpmOccurredIndex;

    if ( Dem_ProgressEngine1000rpm < DEM_ENGINERPM_4000RPM )
    {
        Dem_ProgressEngine1000rpm   =   Dem_ProgressEngine1000rpm + ( Dem_u08_ProgressEngine1000rpmType )1U;

        if ( Dem_ProgressEngine1000rpm >= DEM_ENGINERPM_4000RPM )
        {
            engine4000rpmOccurredIndex  =   Dem_ConfDemOperationCycleEngine4000RPMOccurred;
            Dem_OpCycle_SetCycleStartNoticeFlag( engine4000rpmOccurredIndex, DEM_CYCLE_NOTIFY_START );
        }
    }
    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
