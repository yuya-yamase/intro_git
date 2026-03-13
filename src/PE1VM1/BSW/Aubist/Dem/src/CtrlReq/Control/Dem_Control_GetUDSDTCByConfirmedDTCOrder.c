/* Dem_Control_GetUDSDTCByConfirmedDTCOrder_c(v5-7-0)                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_GetUDSDTCByConfirmedDTCOrder/CODE             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_Control_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------*/
/* Unit External functions                                                  */
/*--------------------------------------------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetUDSDTCByConfirmedDTCOrder                 */
/* Description   | Get ConfirmedDTC list.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] UDSDTCBufferPtr :  UDSDTC list.                    */
/*               | [in/out] UDSDTCNumPtr :  UDSDTC list number.             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of order was successful          */
/*               |        DEM_IRT_NG : get of order failed                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetUDSDTCByConfirmedDTCOrder
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) UDSDTCBufferPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) UDSDTCNumPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) confirmedDTC;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) confirmedCylDTC;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) confirmedOccurrenceOrder;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) confirmedCylOccurrenceOrder;
    VAR( uint16, AUTOMATIC ) udsDTCBufferNum;
    VAR( uint16, AUTOMATIC ) udsDTCNum;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) confirmedOrderListIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetConfirmedUDSDTCAndOrder;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireConfirmedOrderIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetMisfireConfirmedUDSDTCAndOrder;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    VAR( boolean,AUTOMATIC ) loopEnd;

    retVal = DEM_IRT_NG;
    udsDTCNum = (uint16)0U;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        udsDTCBufferNum = *UDSDTCNumPtr;
        if( udsDTCBufferNum > (uint16)0U )
        {
            SchM_Enter_Dem_EventMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();

            confirmedOrderListIndex = (Dem_u08_OrderIndexType)0U;
            retGetConfirmedUDSDTCAndOrder = Dem_Data_GetConfirmedUDSDTCAndOrder( &confirmedOrderListIndex, &confirmedDTC, &confirmedOccurrenceOrder );

            misfireConfirmedOrderIndex = (Dem_MisfireCylinderNumberType)0U;
            retGetMisfireConfirmedUDSDTCAndOrder = Dem_Misfire_GetConfirmedUDSDTCAndOrder( misfireConfirmedOrderIndex, &confirmedCylDTC, &confirmedCylOccurrenceOrder );

            loopEnd = (boolean)FALSE;
            while( loopEnd == (boolean)FALSE )
            {
                if( udsDTCNum < udsDTCBufferNum )
                {
                    /*----------------------------------------------------------------------------------------------------------------------------------------------------------*/
                    /* retGetConfirmedUDSDTCAndOrder | retGetMisfireConfirmedUDSDTCAndOrder | Where to get ConfirmedUDSDTC                                                      */
                    /*-------------------------------|--------------------------------------|-----------------------------------------------------------------------------------*/
                    /*                    DEM_IRT_OK | DEM_IRT_OK                           | Dem_OdrLst_Confirmed_OrderList[] or Dem_MisfireComRecord.ConfirmedOrderCylList[]  */
                    /*                    DEM_IRT_OK | DEM_IRT_NO_MATCHING_ELEMENT          | Dem_OdrLst_Confirmed_OrderList[]                                                  */
                    /*   DEM_IRT_NO_MATCHING_ELEMENT | DEM_IRT_OK                           | Dem_MisfireComRecord.ConfirmedOrderCylList[]                                      */
                    /*   DEM_IRT_NO_MATCHING_ELEMENT | DEM_IRT_NO_MATCHING_ELEMENT          | None (end of loop)                                                                */
                    /*----------------------------------------------------------------------------------------------------------------------------------------------------------*/

                    if( retGetConfirmedUDSDTCAndOrder == DEM_IRT_OK )
                    {
                        if( retGetMisfireConfirmedUDSDTCAndOrder == DEM_IRT_OK )
                        {
                            /* Compare confirmedOccurrenceOrder and confirmedCylOccurrenceOrder and store the one whose failure is confirmed first. */
                            if( confirmedOccurrenceOrder < confirmedCylOccurrenceOrder )
                            {
                                UDSDTCBufferPtr[udsDTCNum] = confirmedDTC;/* [ARYCHK] udsDTCBufferNum / 1 / udsDTCNum */

                                confirmedOrderListIndex = confirmedOrderListIndex + (Dem_u08_OrderIndexType)1U;
                                retGetConfirmedUDSDTCAndOrder = Dem_Data_GetConfirmedUDSDTCAndOrder( &confirmedOrderListIndex, &confirmedDTC, &confirmedOccurrenceOrder );
                            }
                            else
                            {
                                UDSDTCBufferPtr[udsDTCNum] = confirmedCylDTC;/* [ARYCHK] udsDTCBufferNum / 1 / udsDTCNum */

                                misfireConfirmedOrderIndex = misfireConfirmedOrderIndex + (Dem_MisfireCylinderNumberType)1U;
                                retGetMisfireConfirmedUDSDTCAndOrder = Dem_Misfire_GetConfirmedUDSDTCAndOrder( misfireConfirmedOrderIndex, &confirmedCylDTC, &confirmedCylOccurrenceOrder );
                            }
                        }
                        else
                        {
                            UDSDTCBufferPtr[udsDTCNum] = confirmedDTC;/* [ARYCHK] udsDTCBufferNum / 1 / udsDTCNum */

                            confirmedOrderListIndex = confirmedOrderListIndex + (Dem_u08_OrderIndexType)1U;
                            retGetConfirmedUDSDTCAndOrder = Dem_Data_GetConfirmedUDSDTCAndOrder( &confirmedOrderListIndex, &confirmedDTC, &confirmedOccurrenceOrder );
                        }

                        udsDTCNum = udsDTCNum + (uint16)1U;
                    }
                    else
                    {
                        if( retGetMisfireConfirmedUDSDTCAndOrder == DEM_IRT_OK )
                        {
                            UDSDTCBufferPtr[udsDTCNum] = confirmedCylDTC;/* [ARYCHK] udsDTCBufferNum / 1 / udsDTCNum */
                            udsDTCNum = udsDTCNum + (uint16)1U;

                            misfireConfirmedOrderIndex = misfireConfirmedOrderIndex + (Dem_MisfireCylinderNumberType)1U;
                            retGetMisfireConfirmedUDSDTCAndOrder = Dem_Misfire_GetConfirmedUDSDTCAndOrder( misfireConfirmedOrderIndex, &confirmedCylDTC, &confirmedCylOccurrenceOrder );
                        }
                        else
                        {
                            /* If no more can be obtained */
                            loopEnd = (boolean)TRUE;
                        }
                    }
                }
                else
                {
                    /* When the specified number of ConfirmedDTC has been stored */
                    loopEnd = (boolean)TRUE;
                }
            }
        }

        retVal = DEM_IRT_OK;
    }

    *UDSDTCNumPtr = udsDTCNum;

    return retVal;
}
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */


#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Control_GetUDSDTCByConfirmedDTCOrder                 */
/* Description   | Get ConfirmedDTC list.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] UDSDTCBufferPtr :  UDSDTC list.                    */
/*               | [in/out] UDSDTCNumPtr :  UDSDTC list number.             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of order was successful          */
/*               |        DEM_IRT_NG : get of order failed                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetUDSDTCByConfirmedDTCOrder
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) UDSDTCBufferPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) UDSDTCNumPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) confirmedDTC;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) confirmedOccurrenceOrder;
    VAR( uint16, AUTOMATIC ) udsDTCBufferNum;
    VAR( uint16, AUTOMATIC ) udsDTCNum;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) confirmedOrderListIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetConfirmedUDSDTCAndOrder;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    VAR( boolean,AUTOMATIC ) loopEnd;

    retVal = DEM_IRT_NG;
    udsDTCNum = (uint16)0U;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        udsDTCBufferNum = *UDSDTCNumPtr;
        if( udsDTCBufferNum > (uint16)0U )
        {
            SchM_Enter_Dem_EventMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();

            confirmedOrderListIndex = (Dem_u08_OrderIndexType)0U;
            retGetConfirmedUDSDTCAndOrder = Dem_Data_GetConfirmedUDSDTCAndOrder( &confirmedOrderListIndex, &confirmedDTC, &confirmedOccurrenceOrder );

            loopEnd = (boolean)FALSE;
            while( loopEnd == (boolean)FALSE )
            {
                if( udsDTCNum < udsDTCBufferNum )
                {
                    if( retGetConfirmedUDSDTCAndOrder == DEM_IRT_OK )
                    {
                        UDSDTCBufferPtr[udsDTCNum] = confirmedDTC;/* [ARYCHK] udsDTCBufferNum / 1 / udsDTCNum */

                        confirmedOrderListIndex = confirmedOrderListIndex + (Dem_u08_OrderIndexType)1U;
                        retGetConfirmedUDSDTCAndOrder = Dem_Data_GetConfirmedUDSDTCAndOrder( &confirmedOrderListIndex, &confirmedDTC, &confirmedOccurrenceOrder );

                        udsDTCNum = udsDTCNum + (uint16)1U;
                    }
                    else
                    {
                        /* If no more can be obtained */
                        loopEnd = (boolean)TRUE;
                    }
                }
                else
                {
                    /* When the specified number of ConfirmedDTC has been stored */
                    loopEnd = (boolean)TRUE;
                }
            }
        }

        retVal = DEM_IRT_OK;
    }

    *UDSDTCNumPtr = udsDTCNum;

    return retVal;
}
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_OFF ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT== STD_ON )   */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
