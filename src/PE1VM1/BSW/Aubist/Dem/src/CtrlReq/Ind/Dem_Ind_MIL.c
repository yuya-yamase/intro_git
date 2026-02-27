/* Dem_Ind_MIL_c(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Ind_OBD/CODE                                          */
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
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Ind.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_Misfire.h"

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

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Ind_GetMILStatus                                     */
/* Description   | Get MIL Status .                                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] IndicatorStatusPtr                                 */
/*               |        Pointer to data for set Indicator Status.         */
/*               |        This pointer is pointing to                       */
/*               |        Dem_GetIndicatorStatus 2nd parameter.             */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_BLINKING   : Indicator Blinking   */
/*               |          DEM_INDICATOR_BLINK_CONT : Indicator On and Bl- */
/*               |                                     inking               */
/*               |          DEM_INDICATOR_SHORT      : Indicator Short      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetMILStatus
(
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_IndMI_GetMILStatus( IndicatorStatusPtr );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Ind_GetMILStatusByEventStrgIndex                     */
/* Description   | Get MIL Status by Event.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Parameters    | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_BLINKING   : Indicator Blinking   */
/*               |          DEM_INDICATOR_BLINK_CONT : Indicator On and Bl- */
/*               |                                     inking               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetMILStatusByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_IndMI_GetMILStatusByEventStrgIndex( EventStrgIndex, IndicatorStatusPtr );

    return retVal;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#if ( DEM_OBD_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Ind_GetMILStatus                                     */
/* Description   | Get MIL Status .                                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_BLINKING   : Indicator Blinking   */
/*               |          DEM_INDICATOR_BLINK_CONT : Indicator On and Bl- */
/*               |                                     inking               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetMILStatus             /* MISRA DEVIATION */
(
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr   /* MISRA DEVIATION */
)
{
    /*  This is empty function for function switching.  */
    return DEM_IRT_NG;
}

/****************************************************************************/
/* Function Name | Dem_Ind_GetMILStatusByEventStrgIndex                     */
/* Description   | Get MIL Status by Event.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Parameters    | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_BLINKING   : Indicator Blinking   */
/*               |          DEM_INDICATOR_BLINK_CONT : Indicator On and Bl- */
/*               |                                     inking               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetMILStatusByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                        /* MISRA DEVIATION */
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr   /* MISRA DEVIATION */
)
{
    /*  This is empty function for function switching.  */
    return DEM_IRT_NG;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_OFF )   */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
