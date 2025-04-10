/* Dem_If_WWHOBD_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_WWHOBD/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )

#include "../../../inc/Dem_Pm_Control_WWHOBD.h"

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
/* Function Name | Dem_SetMILAtShortMI                                      */
/* Description   | Set MIL statusd to SHORT-MI events.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] MILStatus      : MIL status.                        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : successful.                            */
/*               |        E_NOT_OK : failed.                                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetMILAtShortMI
(
    VAR( boolean, AUTOMATIC ) MILStatus
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;

    retVal = E_NOT_OK;


    internalReturnValue = Dem_Control_SetMILAtShortMI( MILStatus );

    /* Converts return value */
    if ( internalReturnValue == DEM_IRT_OK )
    {
        retVal = E_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_GetB1Counter                                         */
/* Description   | Get B1 Counter                                           */
/* Preconditions | none                                                     */
/* Parameters    | [out] B1Counter      : B1Counter.                        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : successful.                            */
/*               |        E_NOT_OK : failed.                                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetB1Counter
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) B1Counter
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) b1Counter;

    retVal = E_NOT_OK;

    if ( B1Counter != NULL_PTR )
    {
        b1Counter   =   (Dem_u32_B1CounterType)0U;
        internalReturnValue = Dem_Control_GetB1Counter( &b1Counter );

        /* Converts return value */
        if ( internalReturnValue == DEM_IRT_OK )
        {
            *B1Counter  =   b1Counter;
            retVal = E_OK;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_GetB1CounterByEventId                                */
/* Description   | Get B1 Counter by EventId.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventId        : EventId.                          */
/*               | [out] B1CounterPtr   : B1Counter.                        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : successful.                            */
/*               |        E_NOT_OK : failed.                                */
/*               |        DEM_NO_SUCH_ELEMENT : Target Event doesn't have B1Counter. */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetB1CounterByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) B1CounterPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_u16_B1CounterOutputType, AUTOMATIC ) b1Counter;

    retVal = E_NOT_OK;

    if ( B1CounterPtr != NULL_PTR )
    {
        b1Counter   =   (Dem_u16_B1CounterOutputType)0U;
        internalReturnValue = Dem_Control_GetB1CounterByEventId( EventId, &b1Counter );

        /* Converts return value */
        if ( internalReturnValue == DEM_IRT_OK )
        {
            *B1CounterPtr   =   b1Counter;
            retVal = E_OK;
        }
        else if( internalReturnValue == DEM_IRT_WRONG_DTC )
        {
            *B1CounterPtr   =   (Dem_u16_B1CounterOutputType)0U;
            retVal = DEM_NO_SUCH_ELEMENT;
        }
        else
        {
            /*  no process.     */
        }
    }
    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_WWH_OBD_SUPPORT== STD_ON )    */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
