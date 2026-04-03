/* Dem_If_GetConfirmedDTCOrder_c(v5-6-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_GetConfirmedDTCOrder/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
#include <Dem/Dem_Common.h>
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
/* Function Name | Dem_GetUDSDTCByConfirmedUDSDTCOrder                      */
/* Description   | Get ConfirmedDTC list.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] UDSDTCBufferPtr :  EventId list.                   */
/*               | [in/out] UDSDTCNumPtr :  EventId list number.            */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetUDSDTCByConfirmedDTCOrder
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) UDSDTCBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) UDSDTCNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( uint16, AUTOMATIC ) udsDTCNum;

    retVal = E_NOT_OK;

    if( UDSDTCBufferPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( UDSDTCNumPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        udsDTCNum = *UDSDTCNumPtr;
        internalRetVal = Dem_Control_GetUDSDTCByConfirmedDTCOrder( UDSDTCBufferPtr, &udsDTCNum );
        *UDSDTCNumPtr = udsDTCNum;

        if( internalRetVal == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT== STD_ON )   */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
