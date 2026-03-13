/* Dem_Dcm_PID_EDS_c(v5-8-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dcm_PID_EDS/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem_Dcm.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_OBD.h"
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

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
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcmGetDTCOfOBDFreezeFrame                            */
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
/*               |        DEM_E_NO_DTC_AVAILABLE : Initialization non-compl */
/*               |                                 etion.                   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTCOfOBDFreezeFrame
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
        internalRetVal = Dem_Control_GetDTCOfOBDFreezeFrame( DEM_CALLER_DCM, FrameNumber, &dtcValue );
        *DTC = dtcValue;

        /* Convert return value */
        if( internalRetVal == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
        else if( internalRetVal == DEM_IRT_UNINIT )
        {
            retVal = DEM_E_NO_DTC_AVAILABLE;
        }
        else
        {
            /* No Process */
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfOBDFreezeFrame                          */
/* Description   | Gets data element per PID and index of the most importa- */
/*               | nt freeze frame being selected for the output of service */
/*               | 02. The function stores the data in the provided DestBu- */
/*               | ffer. API is needed in OBD-relevant ECUs only.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID :                                               */
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
/* Return Value  | Std_ReturnType :                                         */
/*               |        E_OK : Freeze frame data was successfully report- */
/*               |               ed                                         */
/*               |        E_NOT_OK : Freeze frame data was not successfully */
/*               |                   reported                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfOBDFreezeFrame
(
    VAR( uint8, AUTOMATIC ) PID,
    VAR( uint8, AUTOMATIC ) DataElementIndexOfPID,
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

        internalRetVal = Dem_Control_ReadDataOfOBDFreezeFrame( DEM_CALLER_DCM, PID, DataElementIndexOfPID, DestBuffer, &internalBufSize );
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

#if ( DEM_OBDONEDS_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DcmGetDTCOfOBDFreezeFrame                            */
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
/*               |        DEM_E_NO_DTC_AVAILABLE : Initialization non-compl */
/*               |                                 etion.                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTCOfOBDFreezeFrame
(
    VAR( uint8, AUTOMATIC ) FrameNumber,                /* MISRA DEVIATION */
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTC       /* MISRA DEVIATION */
)
{
    return E_NOT_OK;
}

/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfOBDFreezeFrame                          */
/* Description   | Gets data element per PID and index of the most importa- */
/*               | nt freeze frame being selected for the output of service */
/*               | 02. The function stores the data in the provided DestBu- */
/*               | ffer. API is needed in OBD-relevant ECUs only.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID :                                               */
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
/* Return Value  | Std_ReturnType :                                         */
/*               |        E_OK : Freeze frame data was successfully report- */
/*               |               ed                                         */
/*               |        E_NOT_OK : Freeze frame data was not successfully */
/*               |                   reported                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfOBDFreezeFrame
(
    VAR( uint8, AUTOMATIC ) PID,                            /* MISRA DEVIATION */
    VAR( uint8, AUTOMATIC ) DataElementIndexOfPID,          /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,    /* MISRA DEVIATION */
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize       /* MISRA DEVIATION */
)
{
    return E_NOT_OK;
}
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_OFF )    */
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
