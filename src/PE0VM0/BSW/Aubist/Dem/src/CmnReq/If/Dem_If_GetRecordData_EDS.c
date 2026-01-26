/* Dem_If_GetRecordData_EDS_c(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_GetRecordData_EDS/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_Control_OBD.h"

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

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetDTCOfOBDFreezeFrame                               */
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
/* Return Value  | Std_ReturnType :                                         */
/*               |        E_OK : operation was successful                   */
/*               |        E_NOT_OK : no DTC available                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetDTCOfOBDFreezeFrame
(
    VAR( uint8, AUTOMATIC ) FrameNumber,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTC
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;

    retVal = E_NOT_OK;

    if( DTC == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        dtcValue = (Dem_u32_DTCValueType)0U;  /*  out paramter.   */
        internalRetVal = Dem_Control_GetDTCOfOBDFreezeFrame( FrameNumber, &dtcValue );
        *DTC = dtcValue;

        /* Convert return value */
        if( internalRetVal == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
        else
        {
            /* No Process */
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_ReadDataOfOBDFreezeFrame                             */
/* Description   | Gets data element per PID and index of the most importa- */
/*               | nt freeze frame being selected for the output of service */
/*               | 02. The function stores the data in the provided DestBu- */
/*               | ffer. API is needed in OBD-relevant ECUs only.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID :                                               */
/*               |        This parameter is an identifier for a PID as      */
/*               |        defined in ISO15031-5.                            */
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
/* Return Value  | Std_ReturnType :                                         */
/*               |        E_OK : Freeze frame data was successfully report- */
/*               |               ed                                         */
/*               |        E_NOT_OK : Freeze frame data was not successfully */
/*               |                   reported                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfOBDFreezeFrame
(
    VAR( uint8, AUTOMATIC ) PID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( uint16, AUTOMATIC ) internalBufSize;

    retVal = E_NOT_OK;

    if( DestBuffer == NULL_PTR )
    {
        /* No Process */
    }
    else if( BufSize == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        internalBufSize = *BufSize;

        internalRetVal = Dem_Control_ReadDataOfOBDFreezeFrame( DEM_CALLER_SWC, PID, (uint8)0U, DestBuffer, &internalBufSize );
        *BufSize = internalBufSize;

        /* Convert return value */
        if( internalRetVal == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
        else
        {
            /* No Process */
        }
    }

    return retVal;
}
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )   */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
