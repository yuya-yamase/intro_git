/* Dem_If_DTCCtrl_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_DTCCtrl/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_Pm_Control.h"

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
/* Function Name | Dem_ClearDTC                                             */
/* Description   | Clears single DTCs, as well as groups of DTCs.    This - */
/*               | API is intended for complex device driver. It can only - */
/*               | be used through the RTE (due to work-around described b- */
/*               | elow SWS_Dem_00659), and therefore no declaration is ex- */
/*               | ported via Dem.h.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC :                                               */
/*               |        Defines the DTC in respective format, that shall  */
/*               |         be cleared from the event memory. If the DTC fi- */
/*               |        ts to a DTC group number, all DTCs of the group - */
/*               |        shall be cleared.                                 */
/*               | [in] DTCFormat :                                         */
/*               |        Defines the input-format of the provided DTC val- */
/*               |        ue.                                               */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory t- */
/*               |        his parameter is used to select the source memor- */
/*               |        y the DTCs shall be read from.                    */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : success                                    */
/*               |        DEM_CLEAR_WRONG_DTC : wrong DTC                   */
/*               |        DEM_CLEAR_WRONG_DTCORIGIN : wrong DTC origin      */
/*               |        DEM_CLEAR_FAILED : failed                         */
/*               |        DEM_CLEAR_PENDING : pending                       */
/*               |        DEM_CLEAR_BUSY : busy                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ClearDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = (Std_ReturnType)DEM_CLEAR_FAILED;

    internalReturnValue = Dem_Control_ClearDTC( DEM_CALLER_CDD , (Dem_u32_DTCGroupType)DTC , DTCFormat , DTCOrigin );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = E_OK;
            break;
        case DEM_IRT_WRONG_DTC:
            retVal = (Std_ReturnType)DEM_CLEAR_WRONG_DTC;
            break;
        case DEM_IRT_WRONG_DTCORIGIN:
            retVal = (Std_ReturnType)DEM_CLEAR_WRONG_DTCORIGIN;
            break;
        case DEM_IRT_NG:
            /* No Process */
            break;
        case DEM_IRT_PENDING:
            retVal = (Std_ReturnType)DEM_CLEAR_PENDING;
            break;
        case DEM_IRT_BUSY:
            retVal = (Std_ReturnType)DEM_CLEAR_BUSY;
            break;
        case DEM_IRT_MEMORY_ERROR:
            retVal = (Std_ReturnType)DEM_CLEAR_MEMORY_ERROR;
            break;
        default:
            /* No Process */
            break;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DisableDTCSetting                                    */
/* Description   | Disables the DTC setting for a DTC group.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        Defines the group of DTC that shall be disabled - */
/*               |        to store in event memory.                         */
/*               | [in] DTCKind :                                           */
/*               |        This parameter defines the requested DTC kind, e- */
/*               |        ither only OBD-relevant DTCs or all DTCs          */
/* Return Value  | Dem_ReturnControlDTCSettingType                          */
/*               |        DEM_CONTROL_DTC_SETTING_OK : DTC setting control  */
/*               |         successful                                       */
/*               |        DEM_CONTROL_DTC_SETTING_N_OK : DTC setting contr- */
/*               |        ol not successful                                 */
/*               |        DEM_CONTROL_DTC_WRONG_DTCGROUP : DTC setting con- */
/*               |        trol not successful becouse group of DTC was wro- */
/*               |        ng                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnControlDTCSettingType, DEM_CODE ) Dem_DisableDTCSetting
(
    VAR( uint32, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnControlDTCSettingType, AUTOMATIC ) retVal;

    retVal = DEM_CONTROL_DTC_SETTING_N_OK;
    internalReturnValue = Dem_Control_DisableDTCSetting( (Dem_u32_DTCGroupType)DTCGroup, DTCKind );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = DEM_CONTROL_DTC_SETTING_OK;
            break;
        case DEM_IRT_NG:
            /* No Process */
            break;
        case DEM_IRT_WRONG_DTCGROUP:
            retVal = DEM_CONTROL_DTC_WRONG_DTCGROUP;
            break;
        default:
            /* No Process */
            break;
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_EnableDTCSetting                                     */
/* Description   | Enables the DTC setting for a DTC group. This API is in- */
/*               | tended for the Dcm.    It can only be used through the - */
/*               | RTE (due to work-around described below SWS_Dem_00035),  */
/*               |  and therefore no declaration is exported via Dem_Dcm.h. */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        Defines the group of DTC that shall be enabled t- */
/*               |        o store in event memory.                          */
/*               | [in] DTCKind :                                           */
/*               |        This parameter defines the requested DTC kind, e- */
/*               |        ither only OBD-relevant DTCs or all DTCs          */
/* Return Value  | Dem_ReturnControlDTCSettingType                          */
/*               |        DEM_CONTROL_DTC_SETTING_OK : DTC setting control  */
/*               |         successful                                       */
/*               |        DEM_CONTROL_DTC_SETTING_N_OK : DTC setting contr- */
/*               |        ol not successful                                 */
/*               |        DEM_CONTROL_DTC_WRONG_DTCGROUP : DTC setting con- */
/*               |        trol not successful becouse group of DTC was wro- */
/*               |        ng                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnControlDTCSettingType, DEM_CODE ) Dem_EnableDTCSetting
(
    VAR( uint32, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnControlDTCSettingType, AUTOMATIC ) retVal;

    retVal = DEM_CONTROL_DTC_SETTING_N_OK;
    internalReturnValue = Dem_Control_EnableDTCSetting((Dem_u32_DTCGroupType)DTCGroup, DTCKind );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = DEM_CONTROL_DTC_SETTING_OK;
            break;
        case DEM_IRT_NG:
            /* No Process */
            break;
        case DEM_IRT_WRONG_DTCGROUP:
            retVal = DEM_CONTROL_DTC_WRONG_DTCGROUP;
            break;
        default:
            /* No Process */
            break;
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
