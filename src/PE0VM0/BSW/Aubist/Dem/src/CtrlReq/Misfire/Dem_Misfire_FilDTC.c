/* Dem_Misfire_FilDTC_c(v5-6-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_FilDTC/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_CmnLib_DTC_FilDTC.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "Dem_Misfire_local.h"

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

static FUNC( void, DEM_CODE ) Dem_Misfire_PrepareBitDTCCylinder
( void );

static FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_Misfire_GetFilteredStatusOfDTC
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNum
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireObdFilteredCylinder;
static VAR( Dem_MisfireCylinderNumberType, DEM_VAR_NO_INIT )   Dem_MisfireObdSearchCylinderNum;

static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireFilteredBit0Cylinder;
static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireFilteredBit1Cylinder;
static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireFilteredBit2Cylinder;
static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireFilteredBit3Cylinder;
static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireFilteredBit4Cylinder;
static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireFilteredBit5Cylinder;
static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireFilteredBit6Cylinder;
static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT )  Dem_MisfireFilteredBit7Cylinder;


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Misfire_SetFilteredDTC                               */
/* Description   | The function set the Misfire DTC filter For UDS DTC.     */
/* Preconditions |                                                          */
/* Parameters    | [out] EventStrgIndexPtr :                                */
/*               |        filter serch start event index                    */
/*               | [in] DTCStatusMask :                                     */
/*               |        Status-byte mask for DTC status-byte filtering    */
/*               | [in] DTCKind :                                           */
/*               |        DTCKind type of Dem's external definition.        */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_SetFilteredDTCForUds(v5-3-0).    */
/*   v5-5-0      | branch changed.                                          */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetFilteredDTC
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat
)
{
    VAR( boolean, AUTOMATIC ) execFilterOBDDTC;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) execDTCStatusMask;

    Dem_MisfireObdFilteredCylinder = DEM_MISFIRE_CYLINDER_NON;
    Dem_MisfireObdSearchCylinderNum = (Dem_MisfireCylinderNumberType)0U;

    /* prepare to generate DTCStatus */
    Dem_Misfire_PrepareBitDTCCylinder();

    if( DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS )
    {
        execFilterOBDDTC    =   (boolean)TRUE;

        if ( DTCFormat == DEM_DTC_FORMAT_UDS )
        {
            /*----------------------------------------------------------------------------------------------*/
            /*  this judge logic is used in Dem_Misfire_GetFilteredUdsDTCAndSeverity_AtEmiRelDTC() only.    */
            /*----------------------------------------------------------------------------------------------*/
            /*  check productSupportBit and DemDtcStatusAvailabilityMask.   */
            execDTCStatusMask   =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( DTCStatusMask );
            if ( execDTCStatusMask == ( Dem_UdsStatusByteType )0x00U )
            {
                execFilterOBDDTC    =   (boolean)FALSE;
            }
        }

        if ( execFilterOBDDTC == (boolean)TRUE )
        {
            switch( DTCStatusMask )
            {
                case DEM_UDS_STATUS_PDTC:
                    Dem_MisfireObdFilteredCylinder = Dem_MisfireFilteredBit2Cylinder;
                    break;
                case DEM_UDS_STATUS_CDTC:
                    Dem_MisfireObdFilteredCylinder = Dem_MisfireFilteredBit3Cylinder;
                    break;

                default:
                    /*  no process.     */
                    break;
            }
        }
    }
    return;
}

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetFilteredEdsDTC                            */
/* Description   | Gets the next filtered Misfire EdsDTC.                   */
/* Preconditions |                                                          */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        The DTC value which matchs the specified event i- */
/*               |        ndex and the filter criteria.                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFilteredEdsDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) checkCylinder;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireSearchCylinderNum;
    VAR( boolean, AUTOMATIC ) retDTCClearTarget;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

    /*  check misfire event available.      */
    availableMisfireKind = Dem_DataAvl_GetMisfireCylDTCAvailable();

    if ( availableMisfireKind != DEM_MISFIRE_KINDBIT_NONE )
    {
        retDTCClearTarget = Dem_Misfire_JudgeDTCClearTarget();

        if( retDTCClearTarget == (boolean)FALSE )
        {
            misfireCylinderNum = Dem_MisfireCylinderNum;
            for( misfireSearchCylinderNum = Dem_MisfireObdSearchCylinderNum; misfireSearchCylinderNum < misfireCylinderNum; misfireSearchCylinderNum++ )
            {
                checkCylinder = (Dem_MisfireCylinderType)(Dem_MisfireObdFilteredCylinder >> misfireSearchCylinderNum) & DEM_MISFIRE_CHECK_CYLINDER_BIT;
                if( checkCylinder != DEM_MISFIRE_CYLINDER_NON )
                {
                    *DTCValuePtr    =   Dem_CfgInfoPm_GetOBDDTCByMisfireCylinderNumber( misfireSearchCylinderNum );
                    Dem_MisfireObdSearchCylinderNum = misfireSearchCylinderNum + (Dem_MisfireCylinderNumberType)1U;
                    retVal = DEM_IRT_OK;
                    break;
                }
            }
        }
    }
    if( retVal != DEM_IRT_OK )
    {
        Dem_MisfireObdSearchCylinderNum = Dem_MisfireCylinderNum;
    }

    return retVal;
}
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )  */

/****************************************************************************/
/* Function Name | Dem_Misfire_GetFilteredUdsDTCAndSeverity_AtEmiRelDTC     */
/* Description   | Gets the next filtered Misfire UdsDTC From Fault data.   */
/* Preconditions |                                                          */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        The DTC value which matchs the filter criteria.   */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The DTC status which matchs filter criterria.     */
/*               | [out] DTCSeverityPtr :                                   */
/*               |        The DTC Severity which matchs the filter criter - */
/*               |        ia.                                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetFilteredFaultUdsDTCAndSeverity(v5-3-0). */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFilteredUdsDTCAndSeverity_AtEmiRelDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) checkCylinder;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireSearchCylinderNum;
    VAR( boolean, AUTOMATIC ) retDTCClearTarget;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

    if ( Dem_MisfireObdFilteredCylinder != DEM_MISFIRE_CYLINDER_NON )
    {
        /*  check misfire event available.      */
        availableMisfireKind = Dem_DataAvl_GetMisfireCylDTCAvailable();

        if ( availableMisfireKind != DEM_MISFIRE_KINDBIT_NONE )
        {
            retDTCClearTarget = Dem_Misfire_JudgeDTCClearTarget();
            if( retDTCClearTarget == (boolean)FALSE )
            {
                misfireCylinderNum = Dem_MisfireCylinderNum;
                for( misfireSearchCylinderNum = Dem_MisfireObdSearchCylinderNum; misfireSearchCylinderNum < misfireCylinderNum; misfireSearchCylinderNum++ )
                {
                    checkCylinder = (Dem_MisfireCylinderType)(Dem_MisfireObdFilteredCylinder >> misfireSearchCylinderNum) & DEM_MISFIRE_CHECK_CYLINDER_BIT;
                    if( checkCylinder != DEM_MISFIRE_CYLINDER_NON )
                    {
                        *DTCValuePtr    =   Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( misfireSearchCylinderNum );
                        *DTCStatusPtr   =   Dem_Misfire_GetFilteredStatusOfDTC( misfireSearchCylinderNum );

                        *DTCStatusPtr   =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( *DTCStatusPtr );

                        *DTCSeverityPtr = DEM_DTC_CLASS_1;
                        Dem_MisfireObdSearchCylinderNum = misfireSearchCylinderNum + (Dem_MisfireCylinderNumberType)1U;
                        retVal = DEM_IRT_OK;
                        break;
                    }
                }
            }
        }
    }

    if( retVal != DEM_IRT_OK )
    {
        Dem_MisfireObdSearchCylinderNum = Dem_MisfireCylinderNum;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_GetFilteredUdsDTCAndSeverity                 */
/* Description   | Gets the next filtered Misfire UdsDTC.                   */
/* Preconditions |                                                          */
/* Parameters    | [out] DTCStatusMask :                                    */
/*               |        The DTC status mask                               */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        The DTC value which matchs the filter criteria.   */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The DTC status which matchs filter criterria.     */
/*               | [out] DTCSeverityPtr :                                   */
/*               |        The DTC Severity which matchs the filter criter - */
/*               |        ia.                                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFilteredUdsDTCAndSeverity
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkStatusOfDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireSearchCylinderNum;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( boolean, AUTOMATIC ) retDTCClearTarget;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    misfireCylinderNum = Dem_MisfireCylinderNum;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

    /*  check misfire event available.      */
    availableMisfireKind = Dem_DataAvl_GetMisfireCylDTCAvailable();

    if ( availableMisfireKind != DEM_MISFIRE_KINDBIT_NONE )
    {
        retDTCClearTarget = Dem_Misfire_JudgeDTCClearTarget();

        for( misfireSearchCylinderNum = Dem_MisfireObdSearchCylinderNum; misfireSearchCylinderNum < misfireCylinderNum; misfireSearchCylinderNum++ )
        {
            if( retDTCClearTarget == (boolean)FALSE )
            {
                statusOfDTC = Dem_Misfire_GetFilteredStatusOfDTC( misfireSearchCylinderNum );
            }
            else
            {
                statusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
            }

            /*------------------------------------------*/
            /*  convert to output statusOfDTC.          */
            /*  for judge DTCStatusMask.                */
            /*------------------------------------------*/
            statusOfDTC =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( statusOfDTC );

            retChkStatusOfDTC = Dem_DTC_CheckDTCStatusForFilter( DTCStatusMask, statusOfDTC );
            if( retChkStatusOfDTC == DEM_IRT_OK )
            {
                *DTCValuePtr = Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( misfireSearchCylinderNum );
                *DTCStatusPtr = statusOfDTC;
                *DTCSeverityPtr = DEM_DTC_CLASS_1;
                Dem_MisfireObdSearchCylinderNum = misfireSearchCylinderNum + (Dem_MisfireCylinderNumberType)1U;
                retVal = DEM_IRT_OK;
                break;
            }
        }
    }
    if( retVal != DEM_IRT_OK )
    {
        Dem_MisfireObdSearchCylinderNum = Dem_MisfireCylinderNum;
    }

    return retVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dem_Misfire_PrepareBitDTCCylinder                        */
/* Description   | The function prepare the Misfire DTCCylinder BIT0-BIT7.  */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_PrepareBitDTCCylinder
( void )
{
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailable();

    Dem_MisfireFilteredBit0Cylinder = Dem_Misfire_GetBit0Cylinder( availableMisfireKind );
    Dem_MisfireFilteredBit1Cylinder = Dem_Misfire_GetBit1Cylinder( availableMisfireKind );
    Dem_MisfireFilteredBit2Cylinder = Dem_Misfire_GetBit2Cylinder( availableMisfireKind );
    Dem_MisfireFilteredBit3Cylinder = Dem_Misfire_GetBit3Cylinder( availableMisfireKind );
    Dem_MisfireFilteredBit4Cylinder = Dem_Misfire_GetBit4Cylinder( availableMisfireKind );
    Dem_MisfireFilteredBit5Cylinder = Dem_Misfire_GetBit5Cylinder( availableMisfireKind );
    Dem_MisfireFilteredBit6Cylinder = Dem_Misfire_GetBit6Cylinder( availableMisfireKind );
    Dem_MisfireFilteredBit7Cylinder = Dem_Misfire_GetBit7Cylinder( availableMisfireKind, Dem_MisfireFilteredBit3Cylinder );

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetFilteredStatusOfDTC                       */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinderNum :                                */
/*               |        Specify Cylinder of StatusOfDTC to get            */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_Misfire_GetFilteredStatusOfDTC
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNum
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) checkCylinderMask;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) retStatusOfDTC;

    retStatusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
    checkCylinderMask   =   DEM_MISFIRE_CHECK_CYLINDER_BIT << MisfireCylinderNum;

    if( ( Dem_MisfireFilteredBit0Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = DEM_UDS_STATUS_TF;                         /*  statusOfDTC : bit0  */
    }

    if( ( Dem_MisfireFilteredBit1Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_TFTOC;     /*  statusOfDTC : bit1  */
    }

    if( ( Dem_MisfireFilteredBit2Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_PDTC;     /*  statusOfDTC : bit2  */
    }

    if( ( Dem_MisfireFilteredBit3Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_CDTC;     /*  statusOfDTC : bit3  */
    }

    if( ( Dem_MisfireFilteredBit4Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_TNCSLC;   /*  statusOfDTC : bit4  */
    }

    if( ( Dem_MisfireFilteredBit5Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_TFSLC;    /*  statusOfDTC : bit5  */
    }

    if( ( Dem_MisfireFilteredBit6Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_TNCTOC;   /*  statusOfDTC : bit6  */
    }

    if( ( Dem_MisfireFilteredBit7Cylinder & checkCylinderMask ) == checkCylinderMask )
    {
        retStatusOfDTC = retStatusOfDTC | DEM_UDS_STATUS_WIR;      /*  statusOfDTC : bit7  */
    }

    return retStatusOfDTC;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
