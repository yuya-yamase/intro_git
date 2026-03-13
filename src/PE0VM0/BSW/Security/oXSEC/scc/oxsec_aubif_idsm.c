/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXention of SEC Aubist Interface Layer                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXSEC_AUBIF_IDSM_C_MAJOR                  (2U)
#define OXSEC_AUBIF_IDSM_C_MINOR                  (0U)
#define OXSEC_AUBIF_IDSM_C_PATCH                  (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include <IdsM.h>
#include <IdsM_Cfg_Fixed.h>
#include <IdsM_General.h>

#if (IDSM_CFG_USE_IDSR == STD_ON)
#include <PduR_Cdd1.h>
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )
#include <Rte_StbM_Type.h>
#include <StbM.h>
#endif  /* IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR */

#include <IdsM_Connector.h>

#include "oxsec_aubif_idsm.h"
#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXSEC_AUBIF_IDSM_C_MAJOR != OXSEC_AUBIF_IDSM_H_MAJOR) || \
     (OXSEC_AUBIF_IDSM_C_MINOR != OXSEC_AUBIF_IDSM_H_MINOR) || \
     (OXSEC_AUBIF_IDSM_C_PATCH != OXSEC_AUBIF_IDSM_H_PATCH))
#error "oxsec_aubif_idsm.c and oxsec_aubif_idsm.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  Std_ReturnType vd_g_oXSECAubIfIdsMIdsRTxAck( const uint8* ptData, uint16 u2DataSize )                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
Std_ReturnType vd_g_oXSECAubIfIdsMIdsRTxAck( const uint8* ptData, uint16 u2DataSize )
{
    
    U4               u4_t_sys_act;
    Std_ReturnType   u1_t_ret;
    
    u1_t_ret = (U1)E_NOT_OK;
    u4_t_sys_act = u4_g_oXCANSysActvtd();
    if((u4_t_sys_act & (U4)OXCAN_SYS_VIR_0) == (U4)OXCAN_SYS_VIR_0){
        u1_t_ret = (U1)E_OK;
    }
    
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  void vd_g_oXSECAubIfIdsMQSEvErrAck( const uint8* ptEventFrame, const IdsM_TimestampType* ptTimestamp,                            */
/*                            const volatile uint8* ptContextData, uint16 u2ContextDataSize, IdsM_Ab_ErrorStatusType udQSEvError )   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_oXSECAubIfIdsMQSEvErrAck
(
    const uint8* ptEventFrame,
    const IdsM_TimestampType* ptTimestamp,
    const volatile uint8* ptContextData,
    uint16 u2ContextDataSize,
    IdsM_Ab_ErrorStatusType udQSEvError
)
{
    return;
}
/*===================================================================================================================================*/
/*  void vd_g_oXSECAubIfIdsMParamErrAck( IdsM_SecurityEventIdType udSecurityEventId, IdsM_Ab_ErrorStatusType udParamError )          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_oXSECAubIfIdsMParamErrAck( IdsM_SecurityEventIdType udSecurityEventId, IdsM_Ab_ErrorStatusType udParamError )
{
    return;
}
/*===================================================================================================================================*/
/*  void vd_g_oXSECAubIfIdsMRamErrAck( IdsM_Ab_ErrorStatusType udError )                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_oXSECAubIfIdsMRamErrAck( IdsM_Ab_ErrorStatusType udError )
{
    return;
}



/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Move from IdsM/usr/IdsM_Connector.c   START                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Move from IdsM/usr/IdsM_Connector.c   END                                                                                         */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0    12/02/2025  KT       new                                                                                                */
/*                                                                                                                                   */
/*  * KT   = Kazuya Takayama, DENSO CREATE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
