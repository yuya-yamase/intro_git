/* Dem_Control_PID_c(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_PID/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_Control_local.h"
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_PID_SUPPORT == STD_ON )

#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_OBD.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../usr/Dem_Readiness_Callout.h"
#include "../../../usr/Dem_SavedZone_Callout.h"

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

/****************************************************************************/
/* Function Name | Dem_Control_ReadDataOfPID01                              */
/* Description   | Service to report the value of PID01                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID01value :                                       */
/*               |        Buffer containing the contents of PID01 computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID01
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID01value
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( boolean, AUTOMATIC ) execClearDTC;
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) getDTCGroup;
    VAR( Dem_DTCOriginType, AUTOMATIC ) getDTCOrigin;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        execClearDTC = Dem_Control_CheckExecClearDTCProcess();
        Dem_Control_GetClearType( &getDTCGroup, &getDTCOrigin );

        if ( ( execClearDTC == (boolean)TRUE ) && ( getDTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY ) )
        {
            Dem_PID_ReadInitDataOfPID01( ReadinessCaller, PID01value );
        }
        else
        {
            Dem_PID_ReadDataOfPID01AndPIDF501( ReadinessCaller, DEM_READINESS_PIDF401, PID01value );
        }
    }
    else
    {
        Dem_PID_ReadInitDataOfPID01( ReadinessCaller, PID01value );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_ReadDataOfPID1C                              */
/* Description   | Service to report the value of PID1C                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID1Cvalue :                                       */
/*               |        Buffer containing the contents of PID1C           */
/*               |        computed by the Dem. The buffer is provided by    */
/*               |        the Dcm or SWC with the appropriate size.         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID1C
(
    CONSTP2VAR( uint8, AUTOMATIC, AUTOMATIC ) PID1Cvalue
)
{
    Dem_PID_ReadDataOfPID1C( PID1Cvalue );

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_ReadDataOfPID21                              */
/* Description   | Service to report the value of PID21                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID21value :                                       */
/*               |        Buffer containing the contents of PID21           */
/*               |        computed by the Dem. The buffer is provided by    */
/*               |        the Dcm or SWC with the appropriate size.         */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID21
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        Dem_PID_ReadDataOfPID21( PID21value );
    }
    else
    {
        Dem_PID_ReadInitDataOfPID21( PID21value );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_ReadDataOfPID30                              */
/* Description   | Service to report the value of PID30                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID30value :                                       */
/*               |        Buffer containing the contents of PID30 computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID30
(
    CONSTP2VAR( uint8, AUTOMATIC, AUTOMATIC ) PID30value
)
{
#if ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_UpdateTimingOfPID30Type, AUTOMATIC ) obdUpdateTimingOfPID30;
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) warmUpCycleFlag;
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) dcyFlag;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opCycleObdDcy;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opCycleWarmUp;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    obdUpdateTimingOfPID30 = Dem_OBDUpdateTimingOfPID30;

    if( checkStatus == DEM_IRT_OK )
    {
        /*------------------------------*/
        /*  enter PID exclusion         */
        /*------------------------------*/
        /* Starts exclusion. */
        SchM_Enter_Dem_PID();

        Dem_PID_ReadDataOfPID30( PID30value );

        if ( obdUpdateTimingOfPID30 == DEM_WARMUPCONDITION_FULFILLED )
        {
            /*  check maximum limit.                */
            if ( *PID30value < DEM_PID_WUCCNT_MAX )
            {
                /*  check DCY state.                */
                opCycleObdDcy = Dem_ConfDemOperationCycleObdDcy;
                dcyFlag = Dem_OpCycle_GetCycleStartNoticeFlag( opCycleObdDcy );

                if ( dcyFlag == DEM_CYCLE_NOTIFY_START )
                {
                    /* check warmup cycle state.         */
                    opCycleWarmUp = Dem_ConfDemOperationCycleWarmUp;
                    warmUpCycleFlag = Dem_OpCycle_GetCycleStartNoticeFlag( opCycleWarmUp );
                    if ( warmUpCycleFlag == DEM_CYCLE_NOTIFY_START )
                    {
                        *PID30value =   *PID30value + ( uint8 )1U;
                    }
                }
            }
        }
        /*------------------------------*/
        /*  exit PID exclusion          */
        /*------------------------------*/
        /* Finishes exclusion. */
        SchM_Exit_Dem_PID();
    }
    else
#endif  /* ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )          */
    {
        Dem_PID_ReadInitDataOfPID30( PID30value );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_ReadDataOfPID31                              */
/* Description   | Service to report the value of PID31                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID31value :                                       */
/*               |        Buffer containing the contents of PID31 computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID31
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        Dem_PID_ReadDataOfPID31( PID31value );
    }
    else
    {
        Dem_PID_ReadInitDataOfPID31( PID31value );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_ReadDataOfPID41                              */
/* Description   | Service to report the value of PID41                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID41value :                                       */
/*               |        Buffer containing the contents of PID41 computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID41
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( boolean, AUTOMATIC ) execClearDTC;
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) getDTCGroup;
    VAR( Dem_DTCOriginType, AUTOMATIC ) getDTCOrigin;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        execClearDTC = Dem_Control_CheckExecClearDTCProcess();
        Dem_Control_GetClearType( &getDTCGroup, &getDTCOrigin );

        if ( ( execClearDTC == (boolean)TRUE ) && ( getDTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY ) )
        {
            Dem_PID_ReadInitDataOfPID41( ReadinessCaller, PID41value );
        }
        else
        {
            Dem_PID_ReadDataOfPID41( ReadinessCaller, PID41value );
        }
    }
    else
    {
        Dem_PID_ReadInitDataOfPID41( ReadinessCaller, PID41value );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_ReadDataOfPID4D                              */
/* Description   | Service to report the value of PID4D                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Dvalue :                                       */
/*               |        Buffer containing the contents of PID4D computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID4D
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        Dem_PID_ReadDataOfPID4D( PID4Dvalue );
    }
    else
    {
        Dem_PID_ReadInitDataOfPID4D( PID4Dvalue );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_ReadDataOfPID4E                              */
/* Description   | Service to report the value of PID4E                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Evalue :                                       */
/*               |        Buffer containing the contents of PID4E computed  */
/*               |        by the Dem. The buffer is provided by the Dcm or  */
/*               |        SWC with the appropriate size.                    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID4E
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        Dem_PID_ReadDataOfPID4E( PID4Evalue );
    }
    else
    {
        Dem_PID_ReadInitDataOfPID4E( PID4Evalue );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_ReadDataOfPIDF501                            */
/* Description   | Service to report the value of PIDF501                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] PIDF501value :                                     */
/*               |        Buffer containing the contents of PIDF501 comput- */
/*               |        ed by the Dem. The buffer is provided by the Dcm  */
/*               |        or SWC with the appropriate size.                 */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPIDF501
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDF501value
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( boolean, AUTOMATIC ) execClearDTC;
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) getDTCGroup;
    VAR( Dem_DTCOriginType, AUTOMATIC ) getDTCOrigin;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        execClearDTC = Dem_Control_CheckExecClearDTCProcess();
        Dem_Control_GetClearType( &getDTCGroup, &getDTCOrigin );

        if ( ( execClearDTC == (boolean)TRUE ) && ( getDTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY ) )
        {
            Dem_PID_ReadInitDataOfPIDF501( ReadinessCaller, PIDF501value );
        }
        else
        {
            Dem_PID_ReadDataOfPID01AndPIDF501( ReadinessCaller, DEM_READINESS_PIDF501, PIDF501value );
        }
    }
    else
    {
        Dem_PID_ReadInitDataOfPIDF501( ReadinessCaller, PIDF501value );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_SetDataOfPID21                               */
/* Description   | Service to set the value of PID21                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID21value :                                        */
/*               |        Buffer containing the contents of PID21. The      */
/*               |        buffer is provided by the SWC with the            */
/*               |        appropriate size.                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : PID21value setting successful        */
/*               |        DEM_IRT_NG : PID21value setting not successful    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDataOfPID21
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        Dem_PID_SetDataOfPID21( PID21value );

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetDataOfPID31                               */
/* Description   | Service to set the value of PID31                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID31value :                                        */
/*               |        Buffer containing the contents of PID31. The      */
/*               |        buffer is provided by the SWC with the            */
/*               |        appropriate size.                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : PID31value setting successful        */
/*               |        DEM_IRT_NG : PID31value setting not successful    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDataOfPID31
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        Dem_PID_SetDataOfPID31( PID31value );

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetDataOfPID4D                               */
/* Description   | Service to set the value of PID4D                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID4Dvalue :                                        */
/*               |        Buffer containing the contents of PID4D. The      */
/*               |        buffer is provided by the SWC with the appropria- */
/*               |        te size.                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : PID4Dvalue setting successful        */
/*               |        DEM_IRT_NG : PID4Dvalue setting not successful    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDataOfPID4D
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        Dem_PID_SetDataOfPID4D( PID4Dvalue );

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetDataOfPID4E                               */
/* Description   | Service to set the value of PID4E                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID4Evalue :                                        */
/*               |        Buffer containing the contents of PID4E. The      */
/*               |        buffer is provided by the SWC with the appropria- */
/*               |        te size.                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : PID4Evalue setting successful        */
/*               |        DEM_IRT_NG : PID4Evalue setting not successful    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDataOfPID4E
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        Dem_PID_SetDataOfPID4E( PID4Evalue );

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
