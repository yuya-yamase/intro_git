/* Dem_PID_EdsFFD_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PID_EdsFFD/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )

#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "Dem_PID_local.h"

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
/* Function Name | Dem_PID_ReadDataOfOBDFreezeFrame                         */
/* Description   | Gets data element per PID and index of the most importa- */
/*               | nt freeze frame being selected for the output of service */
/*               | 02. The function stores the data in the provided DestBu- */
/*               | ffer. API is needed in OBD-relevant ECUs only.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index                                       */
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
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Freeze frame data was successfully   */
/*               |               reported                                   */
/*               |        DEM_IRT_NG : Freeze frame data was not            */
/*               |                     successfully reported                */
/*               |        DEM_IRT_WRONG_DIDNUMBER : No PID data             */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : buffer size overflow   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PID_ReadDataOfOBDFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_PIDNumberType, AUTOMATIC ) PID,
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) DataElementIndexOfPID,     /* [PRMCHK:CALLER] */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSize
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) obdRecordNumber;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFFRecordByPidData;

    retVal = DEM_IRT_NG;

    obdRecordNumber = DEM_FFRECNUM_FOR_OBD;
    retGetFFRecordByPidData = Dem_Data_GetFFRecordByPidData( EventStrgIndex, obdRecordNumber, PID, DataElementIndexOfPID, DestBuffer, BufSize );    /* [GUDCHK:CALLER]DataElementIndexOfPID */
    switch( retGetFFRecordByPidData )
    {
        case DEM_IRT_OK:
        case DEM_IRT_WRONG_DIDNUMBER:
        case DEM_IRT_WRONG_BUFFERSIZE:
            retVal = retGetFFRecordByPidData;
            break;
        case DEM_IRT_WRONG_RECORDNUMBER:
        case DEM_IRT_NODATAAVAILABLE:
        default:
            /* No process */
            break;
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
/****************************************************************************/

/**** End of File ***********************************************************/
