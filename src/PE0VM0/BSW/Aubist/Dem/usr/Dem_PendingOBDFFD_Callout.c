/* Dem_PendingOBDFFD_Callout_c(v5-5-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PendingOBDFFD_Callout/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_OBDFFD_SUPPORT == STD_ON )

#include "Dem_PendingOBDFFD_Callout.h"

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


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_JudgePendingOBDFFDUpdateAtConfirmedTrigger           */
/* Description   | Returns judged value which to update PendingFFD for OBD  */
/*               | at confirmed trigger or not.                             */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | boolean                                                  */
/*               |       TRUE  : Update PendingFFD for OBD.                 */
/*               |       FALSE : Not update PendingFFD for OBD.             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_JudgePendingOBDFFDUpdateAtConfirmedTrigger
( void )
{
    VAR( boolean, AUTOMATIC ) judgePendingOBDFFDUpdate;

    /* Returns judged value which to not update. */
    judgePendingOBDFFDUpdate = (boolean)FALSE;

    return judgePendingOBDFFDUpdate;
}

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_JudgeOutputPendingOBDFFDWithoutCDTC                  */
/* Description   | Returns judged value which to output PendingFFD for OBD  */
/*               | without confirmedDTC.                                    */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | boolean                                                  */
/*               |       TRUE  : Output PendingFFD for OBD.                 */
/*               |       FALSE : Not output PendingFFD for OBD.             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_JudgeOutputPendingOBDFFDWithoutCDTC
( void )
{
    VAR( boolean, AUTOMATIC ) judgePendingOBDFFDOutput;

    /* Returns judged value which to not output. */
    judgePendingOBDFFDOutput = (boolean)FALSE;

    return judgePendingOBDFFDOutput;
}
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )   */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
