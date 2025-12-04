/* IdsM_Connector_c_v2-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Usr/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM.h>
#include "../inc/IdsM_Cfg_Fixed.h"
#include "../inc/IdsM_General.h"

#if (IDSM_CFG_USE_IDSR == STD_ON)
#include <PduR_Cdd1.h>
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )
#include <Rte_StbM_Type.h>
#include <StbM.h>
#endif  /* IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR */

#include "./IdsM_Connector.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>


#if (IDSM_CFG_USE_IDSR == STD_ON)
/****************************************************************************/
/* Function Name | IdsM_Connector_PduRTransmit                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId                                                  */
/*               | ptPduInfo                                                */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Connector_PduRTransmit
(
    VAR(PduIdType, AUTOMATIC) udPduId,
    P2CONST(PduInfoType, AUTOMATIC, IDSM_VAR_NO_INIT) ptPduInfo
)
{
    Std_ReturnType ud_StdRet;
    
    ud_StdRet = PduR_Cdd1Transmit( udPduId, ptPduInfo );
    
    if( ud_StdRet == (Std_ReturnType)PDUR_BUSY )
    {
        ud_StdRet = IDSM_E_BUSY;
    }
    
    return ud_StdRet;
}

/****************************************************************************/
/* Function Name | IdsM_Connector_PduRCancelTransmit                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId                                                  */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Connector_PduRCancelTransmit
(
    VAR(PduIdType, AUTOMATIC) udPduId
)
{
    Std_ReturnType ud_StdRet;
    
    ud_StdRet = PduR_Cdd1CancelTransmit( udPduId );
    
    return ud_StdRet;
}

#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if (IDSM_CFG_USE_DEM == STD_ON)
/****************************************************************************/
/* Function Name | IdsM_Connector_DemTransmit                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udDemEventId                                             */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Connector_DemTransmit
(
    VAR(Dem_EventIdType, AUTOMATIC) udDemEventId
)
{
    Std_ReturnType ud_StdRet;
    
    ud_StdRet = Dem_SetEventFailedWithSyncFreezeFrame( udDemEventId );
    
    return ud_StdRet;
}

#endif  /* IDSM_CFG_USE_DEM == STD_ON */

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )
/****************************************************************************/
/* Function Name | IdsM_Connector_StbMGetCurrentTime                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udTimestamp                                              */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Connector_StbMGetCurrentTime
(
    P2VAR(StbM_TimeStampType, AUTOMATIC, IDSM_APPL_DATA) ptStbMTimestamp
)
{
    Std_ReturnType ud_Ret;
    StbM_UserDataType ud_UserData;
    uint16 u2_StbMSyncTimeBaseRef = IdsM_Cfg_u2StbMSyncTimeBaseRef;

    ud_Ret = StbM_GetCurrentTime( u2_StbMSyncTimeBaseRef,
                                  ptStbMTimestamp,
                                  &ud_UserData );

    return ud_Ret;
}

#elif ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
/****************************************************************************/
/* Function Name | IdsM_Connector_GetCurrentTime                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udTimestamp                                              */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Connector_GetCurrentTime
(
    P2VAR(IdsM_TimestampType, AUTOMATIC, IDSM_APPL_DATA) ptTimestamp
)
{
    return E_OK;
}
#else     /* IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR */
#endif    /* IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
