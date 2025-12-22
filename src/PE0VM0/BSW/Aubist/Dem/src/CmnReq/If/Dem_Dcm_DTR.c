/* Dem_Dcm_DTR_OBD_c(v5-3-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dcm_DTR_OBD/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem_Dcm.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_DTR_SUPPORT == STD_ON )

#include "../../../inc/Dem_Pm_Control_DTR.h"

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
/* Function Name | Dem_DcmGetAvailableOBDMIDs                               */
/* Description   | Gets value of OBDMID.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Obdmid       : OBDMID.                             */
/*               | [out] Obdmidvalue  : value of OBDMID.                    */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Report of DTR result successful.       */
/*               |        E_NOT_OK : Report of DTR result failed.           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetAvailableOBDMIDs
(
    VAR(uint8, AUTOMATIC) Obdmid,
    P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) Obdmidvalue
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC) internalReturnValue;
    VAR( Dem_u32_DTRObdMidBmpType, AUTOMATIC) obdmidvalue;

    retVal = E_NOT_OK;

    if( Obdmidvalue != NULL_PTR )
    {
        obdmidvalue = ((Dem_u32_DTRObdMidBmpType)0U);

        /* Gets value of OBDMID */
        internalReturnValue = Dem_Control_GetAvailableOBDMIDs( (Dem_u08_DTRObdMidType)Obdmid, &obdmidvalue);

        /* Converts parameters and return value */
        if ( internalReturnValue == DEM_IRT_OK )
        {
            *Obdmidvalue = (uint32)obdmidvalue;

            retVal = E_OK;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DcmGetNumTIDsOfOBDMID                                */
/* Description   | Gets number of TID.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Obdmid       : Monitor ID of DTR.                  */
/*               | [out] numberOfTIDs : number of TID.                      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Report of DTR result successful.       */
/*               |        E_NOT_OK : Report of DTR result failed.           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetNumTIDsOfOBDMID
(
    VAR(uint8, AUTOMATIC) Obdmid,
    P2VAR(uint8 , AUTOMATIC, DEM_APPL_DATA) numberOfTIDs
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC) internalReturnValue;
    VAR( Dem_u08_DTRTidIndexType, AUTOMATIC) numOfTID;

    retVal = E_NOT_OK;

    if( numberOfTIDs != NULL_PTR )
    {
        numOfTID = ((Dem_u08_DTRTidIndexType)0U);

        /* Gets number of TID */
        internalReturnValue = Dem_Control_GetNumTIDsOfOBDMID( (Dem_u08_DTRObdMidType)Obdmid, &numOfTID);

        /* Converts parameters and return value */
        if ( internalReturnValue == DEM_IRT_OK )
        {
            *numberOfTIDs = numOfTID;

            retVal = E_OK;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DcmGetDTRData                                        */
/* Description   | Gets a DTR result.                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Obdmid      : Monitor ID of DTR.                   */
/*               | [in]  TIDindex    : Test ID Index of DTR.                */
/*               | [out] TIDvalue    : Test ID of DTR.                      */
/*               | [out] UaSID       : UnitAndScalingID of DTR.             */
/*               | [out] Testvalue   : Test result of DTR.                  */
/*               | [out] Lowlimvalue : Lower limit of DTR.                  */
/*               | [out] Upplimvalue : Upper limit of DTR.                  */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Report of DTR result successful.       */
/*               |        E_NOT_OK : Report of DTR result failed.           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTRData
(
    VAR(uint8, AUTOMATIC) Obdmid,
    VAR(uint8, AUTOMATIC) TIDindex,
    P2VAR(uint8 , AUTOMATIC, DEM_APPL_DATA) TIDvalue,
    P2VAR(uint8 , AUTOMATIC, DEM_APPL_DATA) UaSID,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Testvalue,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Lowlimvalue,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Upplimvalue
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC) internalReturnValue;
    VAR( Dem_DtrDataType, AUTOMATIC) dtrData;

    retVal = E_NOT_OK;

    if( TIDvalue == NULL_PTR )
    {
        /* No Process */
    }
    else if( UaSID == NULL_PTR )
    {
        /* No Process */
    }
    else if( Testvalue == NULL_PTR )
    {
        /* No Process */
    }
    else if( Lowlimvalue == NULL_PTR )
    {
        /* No Process */
    }
    else if( Upplimvalue == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        dtrData.TIDValue   = ((Dem_u08_DTRTidIndexType)0U);
        dtrData.UaSID      = ((Dem_u08_DTRUasidType)0U);
        dtrData.TestResult = ((Dem_u16_DTRValueStoreType)0U);
        dtrData.LowerLimit = ((Dem_u16_DTRValueStoreType)0U);
        dtrData.UpperLimit = ((Dem_u16_DTRValueStoreType)0U);
        dtrData.CtrlVal    = DEM_DTR_CTL_NORMAL;
        dtrData.RawTestResult = ((Dem_s32_DTRValueRawType)0);
        dtrData.RawLowerLimit = ((Dem_s32_DTRValueRawType)0);
        dtrData.RawUpperLimit = ((Dem_s32_DTRValueRawType)0);

        /* Gets a DTR result */
        internalReturnValue = Dem_Control_GetDTRData( (Dem_u08_DTRObdMidType)Obdmid, ( Dem_u08_DTRTidIndexType )TIDindex, &dtrData);

        /* Converts parameters and return value */
        if ( internalReturnValue == DEM_IRT_OK )
        {
            *TIDvalue    = (uint8)dtrData.TIDValue;
            *UaSID       = (uint8)dtrData.UaSID;
            *Testvalue   = (uint16)dtrData.TestResult;
            *Lowlimvalue = (uint16)dtrData.LowerLimit;
            *Upplimvalue = (uint16)dtrData.UpperLimit;

            retVal = E_OK;
        }
    }
    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
