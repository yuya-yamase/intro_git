/* Dem_Readiness_Callout_c(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Readiness_Callout/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
#include "Dem_Readiness_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

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
/* Function Name | Dem_JudgeReadinessConditions                             */
/* Description   | Judge readiness at conditions.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DataKind: Kind of PID Data                         */
/*               | [out] ExtremeConditionsDataBPtr: Extream Condition DataB */
/*               | [out] ExtremeConditionsDataCPtr: Extream Condition DataC */
/*               | [out] ExtremeConditionsDataDPtr: Extream Condition DataD */
/*               | [out] ExtremeConditionsDataEPtr: Extream Condition DataE */
/*               | [out] ExtremeConditionsDataFPtr: Extream Condition DataF */
/*               | [out] CompleteConditionsDataBPtr: Complete Condition     */
/*               |       DataB.                                             */
/* Return Value  | none.                                                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_JudgeReadinessConditions
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) DataKind,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) ExtremeConditionsDataBPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) ExtremeConditionsDataCPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) ExtremeConditionsDataDPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) ExtremeConditionsDataEPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) ExtremeConditionsDataFPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) CompleteConditionsDataBPtr
)
{
    *ExtremeConditionsDataBPtr =   ( Dem_u08_ReadinessCondType )0x00U;
    *ExtremeConditionsDataCPtr =   ( Dem_u08_ReadinessCondType )0x00U;
    *ExtremeConditionsDataDPtr =   ( Dem_u08_ReadinessCondType )0x00U;
    *ExtremeConditionsDataEPtr =   ( Dem_u08_ReadinessCondType )0x00U;
    *ExtremeConditionsDataFPtr =   ( Dem_u08_ReadinessCondType )0x00U;
    *CompleteConditionsDataBPtr =  ( Dem_u08_ReadinessCondType )0x00U;

    return ;
}

#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_JudgeReadinessSupported                              */
/* Description   | Judge readiness at conditions.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DataKind: Kind of PID Data                         */
/*               | [out] SupportConditionsDataBPtr: Support Condition DataB */
/*               | [out] SupportConditionsDataCPtr: Support Condition DataC */
/*               | [out] SupportConditionsDataDPtr: Support Condition DataD */
/*               | [out] SupportConditionsDataEPtr: Support Condition DataE */
/*               | [out] SupportConditionsDataFPtr: Support Condition DataF */
/* Return Value  | none.                                                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_JudgeReadinessSupported
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) DataKind,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) SupportConditionsDataBPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) SupportConditionsDataCPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) SupportConditionsDataDPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) SupportConditionsDataEPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) SupportConditionsDataFPtr
)
{
    *SupportConditionsDataBPtr =   DEM_READINESS_SUPPORTCOND_ALL;
    *SupportConditionsDataCPtr =   DEM_READINESS_SUPPORTCOND_ALL;
    *SupportConditionsDataDPtr =   DEM_READINESS_SUPPORTCOND_ALL;
    *SupportConditionsDataEPtr =   DEM_READINESS_SUPPORTCOND_ALL;
    *SupportConditionsDataFPtr =   DEM_READINESS_SUPPORTCOND_ALL;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_JudgeReadinessGroupIdSupported                       */
/* Description   | Judge readiness group supported.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in]  ReadinessGroupId: ReadinessGroupId.                */
/* Return Value  | boolean.                                                 */
/*               |              TRUE  : supported.                          */
/*               |              FALSE : not supported.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_JudgeReadinessGroupIdSupported
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId
)
{
    return (boolean)TRUE;
}

#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
