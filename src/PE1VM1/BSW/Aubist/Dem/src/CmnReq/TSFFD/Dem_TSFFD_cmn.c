/* Dem_TSFFD_cmn_c(v5-7-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/TSFFD_cmn/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl.h"
#include "../../../inc/Dem_CmnLib_DataCtl_SamplingFFD.h"
#include "../../../inc/Dem_CmnLib_TSFFD.h"
#include "../../../usr/Dem_SavedZone_Callout.h"

#if ( DEM_TSFF_SUPPORT == STD_ON )

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

static FUNC( boolean, DEM_CODE ) Dem_TSFFD_GetSamplingFreezeFrameAllowed
(
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) SamplingFreezeFrameTableIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u16_TSFFDSamplingCycleCounterType, DEM_VAR_NO_INIT ) Dem_SamplingCycleCounter[DEM_TSFF_SAMPLING_FF_CLASS_CONFIGURE_NUM];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_TSFFD_Init                                           */
/* Description   | Init process of Dem_TSFFD unit.                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_TSFFD_Init
( void )
{
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) loopSample;
    VAR( Dem_u16_SmpTSFFCPerTSFFIndexType, AUTOMATIC ) samplingFFClassRef;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) tsffSamplingFFClassConfigureNum;

    tsffSamplingFFClassConfigureNum = Dem_TSFFSamplingFFClassConfigureNum;
    for( loopSample = (Dem_u16_SmpTSFFRecClassIndexType)0U; loopSample < tsffSamplingFFClassConfigureNum; loopSample++ )    /* [GUD:for]loopSample */
    {
        tsFFClassRef = Dem_SamplingFreezeFrameTable[loopSample].DemTimeSeriesFreezeFrameClassRef;                                                               /* [GUD]loopSample *//* [GUD:CFG:IF_GUARDED: loopSample ]tsFFClassRef */
        samplingFFClassRef = Dem_SamplingFreezeFrameTable[loopSample].DemSamplingFreezeFrameClassRef;                                                           /* [GUD]loopSample */
        Dem_SamplingCycleCounter[loopSample] = Dem_TSFFClassTable[tsFFClassRef].Dem_SamplingFreezeFrameClass[samplingFFClassRef].DemSamplingIntervalOffset;     /* [GUD]tsFFClassRef *//* [GUD]loopSample */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_TSFFD_SampleFreezeFrame                              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_TSFFD_SampleFreezeFrame
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSample[DEM_TSFF_SAMPLING_FF_CLASS_CONFIGURE_NUM];
    VAR( boolean, AUTOMATIC ) samplingAllowed;
    VAR( boolean, AUTOMATIC ) sampled;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) loopSample;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) loopCapture;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) samplingFFRef;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsffRecordClassConfigureNum;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsffSamplingFFClassConfigureNum;

    sampled = (boolean)FALSE;
    tsffRecordClassConfigureNum = Dem_TSFFRecordClassConfigureNum;
    tsffSamplingFFClassConfigureNum = Dem_TSFFSamplingFFClassConfigureNum;

    for( loopSample = (Dem_u16_SmpTSFFRecClassIndexType)0U; loopSample < tsffSamplingFFClassConfigureNum; loopSample++ )    /* [GUD:for]loopSample */
    {
        resultOfSample[loopSample] = DEM_IRT_NG;                                                                            /* [GUD]loopSample *//* [ARYCHK] DEM_TSFF_SAMPLING_FF_CLASS_CONFIGURE_NUM / 1 / loopSample */

        samplingAllowed = Dem_TSFFD_GetSamplingFreezeFrameAllowed( loopSample );                                            /* [GUD]loopSample */

        if( samplingAllowed == (boolean)TRUE )
        {
            resultOfSample[loopSample] = Dem_Data_SampleFreezeFrame( loopSample );                                          /* [GUD]loopSample *//* [ARYCHK] DEM_TSFF_SAMPLING_FF_CLASS_CONFIGURE_NUM / 1 / loopSample */

            if( resultOfSample[loopSample] == DEM_IRT_OK )                                                                  /* [GUD]loopSample *//* [ARYCHK] DEM_TSFF_SAMPLING_FF_CLASS_CONFIGURE_NUM / 1 / loopSample */
            {
                sampled = (boolean)TRUE;
            }
        }
    }

    if( sampled == (boolean)TRUE )
    {
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/
        for( loopCapture = (Dem_u16_TSFFRecClassIndexType)0U; loopCapture < tsffRecordClassConfigureNum; loopCapture++ )    /* [GUD:for]loopCapture */
        {
            samplingFFRef = Dem_SamplingFreezeFrameBindTable[loopCapture].DemSamplingFreezeFrameRef;                        /* [GUD]loopCapture *//* [GUD:CFG:IF_GUARDED: loopCapture ]samplingFFRef */

            if( resultOfSample[samplingFFRef] == DEM_IRT_OK )                                                               /* [GUD]samplingFFRef *//* [ARYCHK] DEM_TSFF_SAMPLING_FF_CLASS_CONFIGURE_NUM / 1 / samplingFFRef */
            {
                Dem_Data_CaptureAfterTriggeredTimeSeriesFreezeFrame( loopCapture );                                         /* [GUD]loopCapture */
            }
        }
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
    }

    return ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dem_TSFFD_GetSamplingFreezeFrameAllowed                  */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SamplingFreezeFrameTableIndex :                     */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE :                                            */
/*               |        FALSE :                                           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_TSFFD_GetSamplingFreezeFrameAllowed
(
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) SamplingFreezeFrameTableIndex            /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;

    retVal = (boolean)FALSE;

    if( Dem_SamplingCycleCounter[SamplingFreezeFrameTableIndex] == (Dem_u16_TSFFDSamplingCycleCounterType)0U )              /* [GUDCHK:CALLER]SamplingFreezeFrameTableIndex */
    {
        retVal = (boolean)TRUE;

        tsFFClassRef = Dem_SamplingFreezeFrameTable[SamplingFreezeFrameTableIndex].DemTimeSeriesFreezeFrameClassRef;        /* [GUDCHK:CALLER]SamplingFreezeFrameTableIndex *//* [GUD:CFG:IF_GUARDED: SamplingFreezeFrameTableIndex ]tsFFClassRef */

        Dem_SamplingCycleCounter[SamplingFreezeFrameTableIndex] = Dem_TSFFClassTable[tsFFClassRef].DemSamplingInterval;     /* [GUDCHK:CALLER]SamplingFreezeFrameTableIndex */
    }
    else
    {
        /* No process */
    }

    Dem_SamplingCycleCounter[SamplingFreezeFrameTableIndex] = Dem_SamplingCycleCounter[SamplingFreezeFrameTableIndex] - (Dem_u16_TSFFDSamplingCycleCounterType)1U;  /* [GUDCHK:CALLER]SamplingFreezeFrameTableIndex */

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_TSFF_SUPPORT */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
