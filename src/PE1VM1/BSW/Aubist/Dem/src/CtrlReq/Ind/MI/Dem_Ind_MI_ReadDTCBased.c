/* Dem_Ind_MI_ReadDTCBased_c(v5-7-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Ind_MI_ReadDTCBased/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )

#include <Dem/Dem_InternalDataElement.h>

#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_Control.h"
#include "../../../../inc/Dem_Pm_Ind.h"
#include "../../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Pm_DTC.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_INDMI_DATABUF_SIZE           ((uint16)2U)
#define DEM_INDMI_DATABUF_B1COUNTER_HIGH ((uint8)0U)
#define DEM_INDMI_DATABUF_B1COUNTER_LOW  ((uint8)1U)

#define DEM_INDMI_BITSHIFT_8             ((uint8)8U)

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
/* Function Name | Dem_IndMI_ReadDTCBasedIndMIB1Counter                     */
/* Description   | Read DTC Based B1Counter at WWH-OBD.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in]     EventCtrlIndex                                  */
/*               | [in]     DTCValue                                        */
/*               | [in]     GetExtendDataMode                               */
/*               |            DEM_EDR_GETEDRMODE_DTC   : get by DTC.        */
/*               |            DEM_EDR_GETEDRMODE_EVENT : get by EventId.    */
/*               | [out]    BufferPtr                                       */
/*               | [in/out] BufSizePtr                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_WRONG_RECORDNUMBER : wrong recordnumber    */
/*               |       DEM_IRT_WRONG_BUFFERSIZE : buffer size overflow    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based from Dem_IUMPR_ReadDTCBasedIUMPR.     */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_ReadDTCBasedIndMIB1Counter
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,    /* MISRA DEVIATION */
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u16_B1CounterOutputType, AUTOMATIC )   b1Counter;
    VAR( uint16, AUTOMATIC )                    bufSizeIn;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) chkClass;
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1CounterThresholdBy3min;
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1CounterHoldBy3min;
    VAR( Dem_u16_B1CounterOutputType, AUTOMATIC ) b1CounterThresholdBy6min;
    VAR( Dem_u16_B1CounterOutputType, AUTOMATIC ) b1CounterHoldBy6min;
    VAR( boolean, AUTOMATIC ) retDTCClearTarget;
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u16_B1CounterOutputType, AUTOMATIC )   tmpB1Counter;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  */
    VAR( boolean, AUTOMATIC ) eventAvailableDef;

    bufSizeIn = (*BufSizePtr);
    b1Counter = ( Dem_u16_B1CounterOutputType )0U;

    retVal = DEM_IRT_WRONG_RECORDNUMBER;
    retTempVal = DEM_IRT_NG;

    SchM_Enter_Dem_IndMI();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_IndMI();

    Dem_CfgInfoPm_GetB1CounterThresholdAndHold( &b1CounterThresholdBy3min, &b1CounterHoldBy3min );
    b1CounterThresholdBy6min = ( Dem_u16_B1CounterOutputType )( b1CounterThresholdBy3min >> ( Dem_u32_B1CounterType )1U );
    b1CounterHoldBy6min      = ( Dem_u16_B1CounterOutputType )( b1CounterHoldBy3min >> ( Dem_u32_B1CounterType )1U );

    if( GetExtendDataMode == DEM_EDR_GETEDRMODE_DTC )
    {
        /* get start event index by EventCtrlIndex. */
        /* EventCtrlIndex is latched by Dem_DcmDisableDTCRecordUpdate(). */
        /* This index is already adopted calibration. */
        /* For that reason, it is unnecessary get index from DTCValue. */
        eventStrgIndex = Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );   /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ] eventStrgIndex */

        /* get num of event index in DTC group. */
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
        eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( eventStrgIndex );      /* [GUDCHK:CALLER]EventCtrlIndex */

        if( eventStrgIndexNum == ( Dem_u16_EventStrgIndexType )1U )
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )          */
        {
            /*  check user B1 counter config.      */
            chkClass = Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( eventStrgIndex );                  /* [GUDCHK:CALLER]EventCtrlIndex */
            if ( chkClass == (boolean)TRUE )
            {
                /* Check available status. */
                eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );       /* [GUD:RET:TRUE] eventStrgIndex */
                if( eventAvailableDef == (boolean)TRUE )
                {
                    /*  get B1 counter.             */
                    retDTCClearTarget = Dem_DTC_JudgeDTCClearTarget( eventStrgIndex );                  /* [GUD] eventStrgIndex */
                    Dem_IndMI_GetB1CounterByEventStrgIndex_By6Minutes( eventStrgIndex, &b1Counter );    /* [GUD] eventStrgIndex */

                    if ( retDTCClearTarget == (boolean)TRUE )
                    {
                        if ( b1Counter >= b1CounterThresholdBy6min )
                        {
                            b1Counter = b1CounterHoldBy6min;
                        }
                    }

                    retTempVal =  DEM_IRT_OK;
                }
            }
        }
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /*  [FuncSw]    */
        else
        {
            tmpB1Counter = ( Dem_u16_B1CounterOutputType )0U;
            retDTCClearTarget = Dem_DTC_JudgeDTCClearTarget( eventStrgIndex );

            for( eventStrgIndexCnt = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndexCnt < eventStrgIndexNum; eventStrgIndexCnt++ )  /* [GUD:for]eventStrgIndexCnt */
            {
                /*  check user B1 counter config.      */
                chkClass = Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( eventStrgIndex );
                if ( chkClass == (boolean)TRUE )
                {
                    /* Check available status. */
                    eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
                    if( eventAvailableDef == (boolean)TRUE )
                    {
                        /*  get B1 counter.             */
                        Dem_IndMI_GetB1CounterByEventStrgIndex_By6Minutes( eventStrgIndex, &tmpB1Counter );

                        if ( retDTCClearTarget == (boolean)TRUE )
                        {
                            if ( tmpB1Counter >= b1CounterThresholdBy6min )
                            {
                                tmpB1Counter = b1CounterHoldBy6min;
                            }
                        }

                        if( tmpB1Counter > b1Counter )
                        {
                            b1Counter = tmpB1Counter;
                        }
                        retTempVal =  DEM_IRT_OK;
                    }
                }
                /* get next event index. */
                eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndex );
            }
        }
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  */

        if( retTempVal == DEM_IRT_OK )
        {
            if ( bufSizeIn >= DEM_INDMI_DATABUF_SIZE )
            {
                BufferPtr[DEM_INDMI_DATABUF_B1COUNTER_HIGH] = (uint8)( b1Counter >> DEM_INDMI_BITSHIFT_8 );/* [ARYCHK] *BufSizePtr / 1 / DEM_INDMI_DATABUF_B1COUNTER_HIGH */
                BufferPtr[DEM_INDMI_DATABUF_B1COUNTER_LOW]  = (uint8)( b1Counter );/* [ARYCHK] *BufSizePtr / 1 / DEM_INDMI_DATABUF_B1COUNTER_LOW */
                (*BufSizePtr) = DEM_INDMI_DATABUF_SIZE;
                retVal = DEM_IRT_OK;
            }
            else
            {
                retVal = DEM_IRT_WRONG_BUFFERSIZE;
            }
        }
    }
    else
    {
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );
        chkClass        =   Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( eventStrgIndex );

        /*  check user B1 counter config.      */
        if ( chkClass == (boolean)TRUE )
        {
            if( bufSizeIn >= DEM_INDMI_DATABUF_SIZE )
            {
                /*  get B1 counter.             */
                Dem_IndMI_GetB1CounterByEventStrgIndex_By6Minutes( eventStrgIndex, &b1Counter );

                BufferPtr[DEM_INDMI_DATABUF_B1COUNTER_HIGH] = (uint8)( b1Counter >> DEM_INDMI_BITSHIFT_8 );/* [ARYCHK] *BufSizePtr / 1 / DEM_INDMI_DATABUF_B1COUNTER_HIGH */
                BufferPtr[DEM_INDMI_DATABUF_B1COUNTER_LOW]  = (uint8)( b1Counter );/* [ARYCHK] *BufSizePtr / 1 / DEM_INDMI_DATABUF_B1COUNTER_LOW */
                (*BufSizePtr) = DEM_INDMI_DATABUF_SIZE;

                retVal = DEM_IRT_OK;
            }
            else
            {
                retVal = DEM_IRT_WRONG_BUFFERSIZE;
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
