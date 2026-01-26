/* Dem_IUMPR_Callout_c(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPR_Callout/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )

#include "Dem_IUMPR_Callout.h"

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

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_IUMPR_NotifyRatioUpdate                              */
/* Description   | Called when the denominator and numerator counters       */
/*               | are added.                                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioID :                                           */
/*               | [in] IumprDataType :                                     */
/*               |        DEM_IUMPR_DATA_DENOMINATOR                        */
/*               |            With denominator addition.                    */
/*               |        DEM_IUMPR_DATA_NUMERATOR                          */
/*               |            With molecular addition.                      */
/*               |        DEM_IUMPR_DATA_DENOMINATOR_AND_NUMERATOR          */
/*               |            With denominator and numerator addition.      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_IUMPR_NotifyRatioUpdate
(
    VAR( Dem_RatioIdType, AUTOMATIC )   RatioID,
    VAR( Dem_IumprDataType, AUTOMATIC ) IumprDataType
)
{

    return;
}
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )    */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_JudgeAlternativeIUMPRPauseConditions                 */
/* Description   | Judge alternativeIUMPR pause conditions.                 */
/* Preconditions | none                                                     */
/* Parameters    | [out] MADConditionPtr : MAD pause condition.             */
/*               | [out] MANConditionPtr : MAN pause condition.             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_JudgeAlternativeIUMPRPauseConditions
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) MADConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) MANConditionPtr
)
{
    *MADConditionPtr = (boolean)FALSE;
    *MANConditionPtr = (boolean)FALSE;
    return;
}
#endif /* ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_IUMPR_NotifyGeneralDenominatorUpdate                 */
/* Description   | Called when the general denominator counter is updated.  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_IUMPR_NotifyGeneralDenominatorUpdate
(void)
{

    return;
}

/****************************************************************************/
/* Function Name | Dem_IUMPR_NotifyIGCycleCounterUpdate                     */
/* Description   | Called when the IG cycle counter are updated.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_IUMPR_NotifyIGCycleCounterUpdate
(void)
{

    return;
}


#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
