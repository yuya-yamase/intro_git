/* Dem_Control_PID_EdsFFD_c(v5-8-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_PID_EdsFFD/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_Control_local.h"
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Control_OBD.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_PID.h"

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

static VAR( Dem_u16_EventStrgIndexType, DEM_VAR_NO_INIT ) Dem_HighPriorityEventStrgIndex;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_GetDTCOfOBDFreezeFrame                       */
/* Description   | Gets DTC by freeze frame record number.                  */
/*               | API is needed in OBD-relevant ECUs only.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] FrameNumber :                                       */
/*               |        Unique identifier for a freeze frame record as    */
/*               |        defined in ISO 15031-5. The value 0x00 indicates  */
/*               |        the complete OBD freeze frame. Other values are   */
/*               |        reserved for future functionality.                */
/*               | [out] DTC :                                              */
/*               |        Diagnostic Trouble Code in OBD format. If the     */
/*               |        return value of the function is other than E_OK   */
/*               |        this parameter does not contain valid data.       */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |        DEM_IRT_OK : operation was successful             */
/*               |        DEM_IRT_NG : no DTC available                     */
/*               |        DEM_IRT_UNINIT : uninitilized                     */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : wrong record number  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTCOfOBDFreezeFrame
(
    VAR( Dem_u08_RequestCallerType, AUTOMATIC ) Caller,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) FrameNumber,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTC
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSearchPriority;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTCOfOBDFreezeFrame;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Check FrameNunmer */
        if( FrameNumber == DEM_FFRECNUM_FOR_OBD )
        {
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [DataMng] function directory.                      */
            /*  - This function called from SW-C/Dcm context.                           */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/
            retSearchPriority = Dem_DataCtl_SearchPriorityOBDFreezeFrame( &eventStrgIndex, &faultIndex );
            if( Caller == DEM_CALLER_DCM )
            {
                Dem_HighPriorityEventStrgIndex  =   eventStrgIndex;
            }
            if( retSearchPriority == DEM_IRT_OK )
            {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );    /* [GUD:RET:TRUE] EventStrgIndex */
                if( misfireEventKind == (boolean)TRUE )
                {
                    retGetDTCOfOBDFreezeFrame = Dem_Misfire_GetEdsDTCOfOBDFreezeFrame( DTC );
                    if( retGetDTCOfOBDFreezeFrame == DEM_IRT_OK )
                    {
                        retVal = DEM_IRT_OK;
                    }
                }
                else
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                {
                    retGetDTC = Dem_DataAvl_GetOBDDTCByEventStrgIndex( eventStrgIndex, DTC );
                    if ( retGetDTC == DEM_IRT_OK )
                    {
                        retVal = DEM_IRT_OK;
                    }
                }
            }
        }
        else
        {
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
    }
    else
    {
        retVal = DEM_IRT_UNINIT;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_ReadDataOfOBDFreezeFrame                     */
/* Description   | Gets data element per PID and index of the most importa- */
/*               | nt freeze frame being selected for the output of service */
/*               | 02. The function stores the data in the provided DestBu- */
/*               | ffer. API is needed in OBD-relevant ECUs only.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] Caller :                                            */
/*               |        The caller of this function.                      */
/*               |        DCM or SW-C                                       */
/*               | [in] PID :                                               */
/*               |        This parameter is an identifier for a PID as      */
/*               |        defined in ISO15031-5.                            */
/*               | [in] DataElementIndexOfPID :                             */
/*               |        Data element index of this PID according to the   */
/*               |        Dcm configuration of service 02. It is zero-bas-  */
/*               |        ed and consecutive, and ordered by the data       */
/*               |        element positions (configured in Dcm, refer to    */
/*               |        SWS_Dem_00597).                                   */
/*               | [in/out] DestBuffer :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the data element of    */
/*               |        the PID shall be written to. The format is raw    */
/*               |        hexadecimal values and contains no header-inform- */
/*               |        ation.                                            */
/*               | [in/out] BufSize :                                       */
/*               |        When the function is called this parameter conta- */
/*               |        ins the maximum number of data bytes that can be  */
/*               |        written to the buffer. The function returns the   */
/*               |        actual number of written data bytes in this       */
/*               |        parameter.                                        */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |        DEM_IRT_OK : Freeze frame data was successfully   */
/*               |                     reported                             */
/*               |        DEM_IRT_NG : Freeze frame data was not            */
/*               |                     successfully reported                */
/*               |        DEM_IRT_WRONG_DIDNUMBER : No PID data             */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : buffer size overflow   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ReadDataOfOBDFreezeFrame
(
    VAR( Dem_u08_RequestCallerType, AUTOMATIC ) Caller,
    VAR( Dem_u08_PIDNumberType, AUTOMATIC ) PID,
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) DataElementIndexOfPID,         /* [PRMCHK:CALLER] */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSize
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSearchPriority;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*--------------------------------------------------------------------------*/
        /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
        /* These are the reasons why this function needs to get exclusive.          */
        /*  - This function call [DataMng] function directory.                      */
        /*  - This function called from SW-C/Dcm context.                           */
        /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
        SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
        SchM_Exit_Dem_EventMemory();
        /*--------------------------------------------------------------------------*/
        if( Caller == DEM_CALLER_DCM )
        {
            eventStrgIndex  =   Dem_HighPriorityEventStrgIndex;
            if ( eventStrgIndex < eventStorageNum )
            {
                retVal = Dem_PID_ReadDataOfOBDFreezeFrame( eventStrgIndex, PID, DataElementIndexOfPID, DestBuffer, BufSize );   /* [GUDCHK:CALLER]DataElementIndexOfPID */
            }
        }
        else
        {
            retSearchPriority = Dem_DataCtl_SearchPriorityOBDFreezeFrame( &eventStrgIndex, &faultIndex );

            if( retSearchPriority == DEM_IRT_OK )
            {
                retVal = Dem_PID_ReadDataOfOBDFreezeFrame( eventStrgIndex, PID, DataElementIndexOfPID, DestBuffer, BufSize );                   /* [GUDCHK:CALLER]DataElementIndexOfPID */
            }
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
