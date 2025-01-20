/* Dem_FFD_c(v5-5-0)                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/FFD/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_FFD.h"
#include "../../../inc/Dem_Pm_DataCtl.h"

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

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_DID_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_FFD_GetEventFreezeFrameData                          */
/* Description   | Gets freeze frame data by EventStrgIndex.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Identifier to specify the event record including  */
/*               |         the freeze frame.                                */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a free- */
/*               |        zeframe record as defined in ISO15031-5 and ISO1- */
/*               |        4229-1.0xFF means most recent freeze frame recor- */
/*               |        d is returned.                                    */
/*               | [in] DataID :                                            */
/*               |        This parameter specifies the PID (ISO15031-5 map- */
/*               |        ped in UDS range 0xF400 - 0xF4FF) or DID (ISO142- */
/*               |        29-1) that shall be copied to the destination bu- */
/*               |        ffer.                                             */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the freeze frame data  */
/*               |         record shall be written to.The format is raw he- */
/*               |        xadecimal values and contains no header-informat- */
/*               |        ion.                                              */
/*               | [in/out] BufSizePtr :                                    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG :                                      */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : The requestedrecord  */
/*               |         number is not supported by the event             */
/*               |        DEM_IRT_WRONG_DIDNUMBER : The requested DID isno- */
/*               |        t supported by the freeze frame                   */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_GetEventFreezeFrameData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    if( ( RecordNumber == DEM_FFRECNUM_FOR_OBD_FIRST ) || ( RecordNumber == DEM_FFRECNUM_FOR_OBD_LATEST ) )
    {
        /* Get FreezeFrameData corresponding to EventStrgIndex */
        retVal = Dem_Data_GetEventFreezeFrameData( EventStrgIndex, RecordNumber, DEM_FFD_TYPE_OBDFFD, DataID, DestBufferPtr, BufSizePtr );
    }
    else
    {
        /* Get FreezeFrameData corresponding to EventStrgIndex */
        retVal = Dem_Data_GetEventFreezeFrameData( EventStrgIndex, RecordNumber, DEM_FFD_TYPE_NONOBDFFD, DataID, DestBufferPtr, BufSizePtr );
    }

    return retVal;
}

#endif  /* ( DEM_OBDFFD_DID_SUPPORT == STD_ON )     */
#if ( DEM_OBDFFD_DID_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_FFD_GetEventFreezeFrameData                          */
/* Description   | Gets freeze frame data by EventStrgIndex.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Identifier to specify the event record including  */
/*               |         the freeze frame.                                */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a free- */
/*               |        zeframe record as defined in ISO15031-5 and ISO1- */
/*               |        4229-1.0xFF means most recent freeze frame recor- */
/*               |        d is returned.                                    */
/*               | [in] DataID :                                            */
/*               |        This parameter specifies the PID (ISO15031-5 map- */
/*               |        ped in UDS range 0xF400 - 0xF4FF) or DID (ISO142- */
/*               |        29-1) that shall be copied to the destination bu- */
/*               |        ffer.                                             */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the freeze frame data  */
/*               |         record shall be written to.The format is raw he- */
/*               |        xadecimal values and contains no header-informat- */
/*               |        ion.                                              */
/*               | [in/out] BufSizePtr :                                    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG :                                      */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : The requestedrecord  */
/*               |         number is not supported by the event             */
/*               |        DEM_IRT_WRONG_DIDNUMBER : The requested DID isno- */
/*               |        t supported by the freeze frame                   */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_GetEventFreezeFrameData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) piddataID;

    if( ( RecordNumber == DEM_FFRECNUM_FOR_OBD_FIRST ) || ( RecordNumber == DEM_FFRECNUM_FOR_OBD_LATEST ) )
    {
        piddataID = (uint8)( DataID & DEM_DID_TO_PID_MASK );

        retVal = Dem_Data_GetFFRecordByPidData( EventStrgIndex, RecordNumber, piddataID, DEM_PID_DATAELEMENT_INDEX_FIRST, DestBufferPtr, BufSizePtr );
    }
    else
    {
        /* Get FreezeFrameData corresponding to EventStrgIndex */
        retVal = Dem_Data_GetEventFreezeFrameData( EventStrgIndex, RecordNumber, DEM_FFD_TYPE_NONOBDFFD, DataID, DestBufferPtr, BufSizePtr );
    }

    return retVal;
}
#endif  /* ( DEM_OBDFFD_DID_SUPPORT == STD_OFF )     */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

#if ( DEM_OBDFFD_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_FFD_GetEventFreezeFrameData                          */
/* Description   | Gets freeze frame data by EventStrgIndex.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Identifier to specify the event record including  */
/*               |         the freeze frame.                                */
/*               | [in] RecordNumber :                                      */
/*               |        This parameter is a unique identifier for a free- */
/*               |        zeframe record as defined in ISO15031-5 and ISO1- */
/*               |        4229-1.0xFF means most recent freeze frame recor- */
/*               |        d is returned.                                    */
/*               | [in] DataID :                                            */
/*               |        This parameter specifies the PID (ISO15031-5 map- */
/*               |        ped in UDS range 0xF400 - 0xF4FF) or DID (ISO142- */
/*               |        29-1) that shall be copied to the destination bu- */
/*               |        ffer.                                             */
/*               | [out] DestBufferPtr :                                    */
/*               |        This parameter contains a byte pointer that poin- */
/*               |        ts to the buffer, to which the freeze frame data  */
/*               |         record shall be written to.The format is raw he- */
/*               |        xadecimal values and contains no header-informat- */
/*               |        ion.                                              */
/*               | [in/out] BufSizePtr :                                    */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG :                                      */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : The requestedrecord  */
/*               |         number is not supported by the event             */
/*               |        DEM_IRT_WRONG_DIDNUMBER : The requested DID isno- */
/*               |        t supported by the freeze frame                   */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_GetEventFreezeFrameData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    if( ( RecordNumber == DEM_FFRECNUM_FOR_OBD_FIRST ) || ( RecordNumber == DEM_FFRECNUM_FOR_OBD_LATEST ) )
    {
        retVal = DEM_IRT_WRONG_RECORDNUMBER;
    }
    else
    {
        /* Get FreezeFrameData corresponding to EventStrgIndex */
        retVal = Dem_Data_GetEventFreezeFrameData( EventStrgIndex, RecordNumber, DEM_FFD_TYPE_NONOBDFFD, DataID, DestBufferPtr, BufSizePtr );
    }

    return retVal;
}

#endif  /* ( DEM_OBDFFD_SUPPORT == STD_OFF )   */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
