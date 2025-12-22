/* Dem_DataAvl_UserDefMem_DTC_c(v5-7-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataAvl_UserDefMem_DTC/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_Udm_DataAvl.h"

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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmDataAvl_GetUdmEventIndexByDTC                     */
/* Description   | Gets the udm event index corresponding to the specified  */
/*               | DTC value.                                               */
/* Preconditions | The specified DTC value has been already registered.     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        The specified DTC value.                          */
/* Parameters    | [in] UdmInfoTableIndex :                                 */
/*               |        The Index of Dem_UserDefinedMemoryInfoTable       */
/*               | [out] UdmEventIndexPtr :                                 */
/*               |        The Udm event index corresponding to the specifi- */
/*               |        ed DTC value.                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the event index was succ- */
/*               |        essful.                                           */
/*               |        DEM_IRT_WRONG_DTC : Retrieving the event index    */
/*               |        was failed.                                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] UdmEventIndexPtr                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDataAvl_GetUdmEventIndexByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexStart;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexEnd;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexStart;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexEnd;
    VAR( boolean, AUTOMATIC ) loopEndFlag;

    VAR( boolean, AUTOMATIC ) resultValidateDTC;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;

    VAR( boolean, AUTOMATIC ) availableStatus;

    /* Initializes the return value and loopEndFlag to NG. */
    retVal = DEM_IRT_WRONG_DTC;
    loopEndFlag = (boolean)FALSE;

    resultValidateDTC = Dem_DataAvl_ValidateDTC( DTCValue );

    if( resultValidateDTC == (boolean)TRUE )
    {
        /* get UDM group index. */
        Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndex( UdmInfoTableIndex, &udmGroupKindIndexStart, &udmGroupKindIndexNum );
        udmGroupKindIndexEnd = udmGroupKindIndexStart + udmGroupKindIndexNum; /*  end pos of search loop by udm group */

        /* Loop by udm group */
        for( udmGroupKindIndex = udmGroupKindIndexStart; udmGroupKindIndex < udmGroupKindIndexEnd; udmGroupKindIndex++ )  /* [GUD:for]udmGroupKindIndex */
        {
            udmEventIndexStart  =   Dem_CfgInfoUdm_GetStartUdmEventIndex_InMemory( udmGroupKindIndex );
            udmEventIndexNum    =   Dem_CfgInfoUdm_GetConfigureNumOfUdmEventIndex_InMemory( udmGroupKindIndex );
            udmEventIndexEnd    =   udmEventIndexStart + udmEventIndexNum;

            /* Event index loops by udm group.*/
            for( udmEventIndex = udmEventIndexStart; udmEventIndex < udmEventIndexEnd; udmEventIndex++ )   /* [GUD:for]udmEventIndex */
            {
                /* Holds the event table pointed to by the event index. */
                udsDTCValue = Dem_CfgInfoUdm_GetUdsDTCValue( udmEventIndex );       /* [GUD]udmEventIndex */

                /* Confirm comparison between DemDtcValue of the held DTC table and specified DTC value*/
                if( udsDTCValue == DTCValue )
                {
                    /* Leave the loop. */
                    loopEndFlag = (boolean)TRUE;
                    /* Checks event available status */
                    availableStatus = Dem_UdmDataAvl_GetEvtAvl( udmEventIndex );    /* [GUD]udmEventIndex */

                    if( availableStatus == (boolean)TRUE )
                    {
                        /* Store the event index in the specified event index storage area. */
                        *UdmEventIndexPtr = udmEventIndex;                          /* [GUD]udmEventIndex */

                        /* Sets the return value to OK. */
                        retVal = DEM_IRT_OK;
                    }
                    break;
                }
            }

            if( loopEndFlag == (boolean)TRUE )
            {
                break;
            }
        }
    }

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmDataAvl_GetDTCByUdmEventIndex                      */
/* Description   | Gets the UDS DTC value which is corresponding to the sp- */
/*               | ecified event index and the specified format is configu- */
/*               | redin.                                                   */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] DTCFormat :                                         */
/*               |        DTCFormat type of Dem's external definition.      */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value corresponding the specified event - */
/*               |        index.                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEN_IRT_OK :  EventIndex has UDS DTC.             */
/*               |        DEM_IRT_NG : Retrieving the DTC value was failed. */
/*               |        DEM_IRT_NODATAAVAILABLE :                         */
/*               |                      EventIndex has no UDS DTC.          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDataAvl_GetDTCByUdmEventIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) resultValidateDTC;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) udsDTCValue;

    /* Initializes the return value to OK. */

    /* Checks the DTCFormat. */
    if( DTCFormat == DEM_DTC_FORMAT_UDS )
    {
        retVal = DEM_IRT_NODATAAVAILABLE;

       /* Holds the event table pointed to by the specified event index. */
        udsDTCValue =   Dem_CfgInfoUdm_GetUdsDTCValue( UdmEventIndex );

        resultValidateDTC = Dem_DataAvl_ValidateDTC( udsDTCValue );
        if( resultValidateDTC == (boolean)TRUE )
        {
            /* Store the DTC value of the DTC table held in the designated DTC value storage area. */
            *DTCValuePtr = udsDTCValue;
            retVal = DEM_IRT_OK;
        }
    }
    else if( DTCFormat == DEM_DTC_FORMAT_OBD )
    {
        retVal = DEM_IRT_NODATAAVAILABLE;
    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
