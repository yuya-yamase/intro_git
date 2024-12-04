/* NvM_Dem_Connector.c v2-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/DEM/CONNECTOR/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "NvM_Dem_Connector.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Dem_ReportErrorStatus                                */
/* Description   | Function for connection with Dem_SetEventStatus.         */
/* Preconditions | None                                                     */
/* Parameters    | EventId     : Identification of an event by assigned     */
/*               |               Event ID.                                  */
/*               | EventStatus : Monitor test result                        */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Dem_ReportErrorStatus(
    NvM_Dem_EventIdType EventId,
    NvM_Dem_EventStatusType EventStatus
){
    /* [Manual configuration] Add the necessary description for the user below. */
    /* [Manual configuration] Add the necessary description for the user above. */

    return;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2020/11/27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
