/* Dem_DataElement_c(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataElement/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../../inc/Dem_CmnLib_DataElement.h"


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



#if ( DEM_READFUNC_MONITORDATA_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataElement_ReadData                                 */
/* Description   | Call DemDataElementReadFnc.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] dataElementClassPtr :                               */
/*               |       The pointer of  DataElementClassTable.             */
/*               | [in] Dataptr :                                           */
/*               |       The pointer of Databuffer.                         */
/*               | {in] monitorData0 :  monitor data                        */
/* Return Value  | Std_ReturnType                                           */
/*               |       E_OK :                                             */
/*               |       E_NOT_OK :                                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType , DEM_CODE ) Dem_DataElement_ReadData
(
    P2CONST( AB_83_ConstV Dem_DataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) dataElementClassPtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) DataPtr,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
)
{
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;

#ifndef JGXSTACK
    resultOfCallback = dataElementClassPtr->DemDataElementReadFnc( DataPtr, monitorData0 );
#else /* JGXSTACK */
    /* user-defined */
    resultOfCallback = E_OK;
#endif /* JGXSTACK */

    return resultOfCallback;
}
#endif /* (DEM_READFUNC_MONITORDATA_SUPPORT == STD_ON) */


#if ( DEM_READFUNC_MONITORDATA_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DataElement_ReadData                                 */
/* Description   | Call DemDataElementReadFnc.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] dataElementClassPtr :                               */
/*               |       The pointer of  DataElementClassTable.             */
/*               | [in] Dataptr :                                           */
/*               |       The pointer of Databuffer.                         */
/*               | {in] monitorData0 :                                      */
/* Return Value  | Std_ReturnType                                           */
/*               |       E_OK :                                             */
/*               |       E_NOT_OK :                                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType , DEM_CODE ) Dem_DataElement_ReadData
(
    P2CONST( AB_83_ConstV Dem_DataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) dataElementClassPtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) DataPtr,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0 /* MISRA DEVIATION */
)
{
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;

#ifndef JGXSTACK
    resultOfCallback = dataElementClassPtr->DemDataElementReadFnc( DataPtr );
#else /* JGXSTACK */
    /* user-defined */
    resultOfCallback = E_OK;
#endif /* JGXSTACK */

    return resultOfCallback;
}
#endif /* ( DEM_READFUNC_MONITORDATA_SUPPORT == STD_OFF ) */



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
