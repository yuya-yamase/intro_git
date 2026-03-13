/* Dem_Readiness_Callout_h(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Readiness_Callout/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_READINESS_CALLOUT_H
#define DEM_READINESS_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Cfg.h"

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_READINESS_PIDF401               ((Dem_u08_ReadinessKindType)0x01U)
#define DEM_READINESS_PIDF441               ((Dem_u08_ReadinessKindType)0x02U)
#define DEM_READINESS_PIDF501               ((Dem_u08_ReadinessKindType)0x03U)

#define DEM_READINESS_PIDF401_SWC           ( DEM_READINESS_PIDF401 + DEM_READINESS_CALLBY_SWC )
#define DEM_READINESS_PIDF441_SWC           ( DEM_READINESS_PIDF441 + DEM_READINESS_CALLBY_SWC )
#define DEM_READINESS_PIDF501_SWC           ( DEM_READINESS_PIDF501 + DEM_READINESS_CALLBY_SWC )

#define DEM_PIDF4XX_EXTREMEBIT_CCM          ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF4XX_EXTREMEBIT_FLSYS        ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF4XX_EXTREMEBIT_MISF         ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF4XX_EXTREMEBIT_EGR          ((Dem_u08_ReadinessCondType)0x80U)
#define DEM_PIDF4XX_EXTREMEBIT_O2SENSHT     ((Dem_u08_ReadinessCondType)0x40U)
#define DEM_PIDF4XX_EXTREMEBIT_O2SENS       ((Dem_u08_ReadinessCondType)0x20U)
#define DEM_PIDF4XX_EXTREMEBIT_SPARK_PMFLT  ((Dem_u08_ReadinessCondType)0x10U)
#define DEM_PIDF4XX_EXTREMEBIT_SECAIR       ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF4XX_EXTREMEBIT_EVAP         ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF4XX_EXTREMEBIT_HTCAT        ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF4XX_EXTREMEBIT_CAT          ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF4XX_EXTREMEBIT_COMP_PMFLT   ((Dem_u08_ReadinessCondType)0x40U)
#define DEM_PIDF4XX_EXTREMEBIT_EGSENS       ((Dem_u08_ReadinessCondType)0x20U)
#define DEM_PIDF4XX_EXTREMEBIT_BOOSTPR      ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF4XX_EXTREMEBIT_NOXCAT       ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF4XX_EXTREMEBIT_HCCAT        ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF5XX_EXTREMEBIT_ECS          ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF5XX_EXTREMEBIT_CCM          ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF5XX_EXTREMEBIT_FLSYS        ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF5XX_EXTREMEBIT_MISF         ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF5XX_EXTREMEBIT_NOXCAT       ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF5XX_EXTREMEBIT_HTCAT        ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF5XX_EXTREMEBIT_HCCAT        ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF5XX_EXTREMEBIT_CAT          ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF5XX_EXTREMEBIT_PMFLT        ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF5XX_EXTREMEBIT_BOOSTPR      ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF5XX_EXTREMEBIT_SECAIR       ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF5XX_EXTREMEBIT_EVAP         ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF5XX_EXTREMEBIT_VVT          ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF5XX_EXTREMEBIT_EGR          ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF5XX_EXTREMEBIT_PCV          ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF5XX_EXTREMEBIT_EGSENS       ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF5XX_EXTREMEBIT_OTHER        ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF5XX_EXTREMEBIT_NOXADSORB    ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF5XX_EXTREMEBIT_CSER         ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF5XX_EXTREMEBIT_DOR          ((Dem_u08_ReadinessCondType)0x01U)

/*  target readiness group for  support bit     */
#define DEM_PIDF4XX_SUPPORTBIT_CCM          ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF4XX_SUPPORTBIT_FLSYS        ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF4XX_SUPPORTBIT_MISF         ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF4XX_SUPPORTBIT_EGR          ((Dem_u08_ReadinessCondType)0x80U)
#define DEM_PIDF4XX_SUPPORTBIT_O2SENSHT     ((Dem_u08_ReadinessCondType)0x40U)
#define DEM_PIDF4XX_SUPPORTBIT_O2SENS       ((Dem_u08_ReadinessCondType)0x20U)
#define DEM_PIDF4XX_SUPPORTBIT_SPARK_PMFLT  ((Dem_u08_ReadinessCondType)0x10U)
#define DEM_PIDF4XX_SUPPORTBIT_SECAIR       ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF4XX_SUPPORTBIT_EVAP         ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF4XX_SUPPORTBIT_HTCAT        ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF4XX_SUPPORTBIT_CAT          ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF4XX_SUPPORTBIT_COMP_PMFLT   ((Dem_u08_ReadinessCondType)0x40U)
#define DEM_PIDF4XX_SUPPORTBIT_EGSENS       ((Dem_u08_ReadinessCondType)0x20U)
#define DEM_PIDF4XX_SUPPORTBIT_BOOSTPR      ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF4XX_SUPPORTBIT_NOXCAT       ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF4XX_SUPPORTBIT_HCCAT        ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF5XX_SUPPORTBIT_ECS          ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF5XX_SUPPORTBIT_CCM          ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF5XX_SUPPORTBIT_FLSYS        ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF5XX_SUPPORTBIT_MISF         ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF5XX_SUPPORTBIT_NOXCAT       ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF5XX_SUPPORTBIT_HTCAT        ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF5XX_SUPPORTBIT_HCCAT        ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF5XX_SUPPORTBIT_CAT          ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF5XX_SUPPORTBIT_PMFLT        ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF5XX_SUPPORTBIT_BOOSTPR      ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF5XX_SUPPORTBIT_SECAIR       ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF5XX_SUPPORTBIT_EVAP         ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF5XX_SUPPORTBIT_VVT          ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF5XX_SUPPORTBIT_EGR          ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF5XX_SUPPORTBIT_PCV          ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF5XX_SUPPORTBIT_EGSENS       ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_PIDF5XX_SUPPORTBIT_OTHER        ((Dem_u08_ReadinessCondType)0x08U)
#define DEM_PIDF5XX_SUPPORTBIT_NOXADSORB    ((Dem_u08_ReadinessCondType)0x04U)
#define DEM_PIDF5XX_SUPPORTBIT_CSER         ((Dem_u08_ReadinessCondType)0x02U)
#define DEM_PIDF5XX_SUPPORTBIT_DOR          ((Dem_u08_ReadinessCondType)0x01U)

#define DEM_READINESS_SUPPORTCOND_ALL       ((Dem_u08_ReadinessCondType)0xFFU)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE_CALLOUT ) Dem_JudgeReadinessConditions
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC) DataKind,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) ExtremeConditionsDataBPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) ExtremeConditionsDataCPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) ExtremeConditionsDataDPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) ExtremeConditionsDataEPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) ExtremeConditionsDataFPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) CompleteConditionsDataBPtr
);

#if ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE_CALLOUT ) Dem_JudgeReadinessSupported
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC) DataKind,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) SupportConditionsDataBPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) SupportConditionsDataCPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) SupportConditionsDataDPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) SupportConditionsDataEPtr,
    P2VAR( Dem_u08_ReadinessCondType, AUTOMATIC, AUTOMATIC ) SupportConditionsDataFPtr
);
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_JudgeReadinessGroupIdSupported
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId
);
#endif  /* ( DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_CODE_CALLOUT
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


#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

#endif /* DEM_READINESS_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
