/* IdsM_InterSEv_c_v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/InterSEv/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM.h>
#include <SchM_IdsM.h>
#include "../inc/IdsM_Cfg_Fixed.h"
#include "../inc/IdsM_General.h"
#include "../inc/IdsM_Filter.h"
#include "../inc/IdsM_InterSEv.h"

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

/****************************************************************************/
/* Function Name | IdsM_InterSEv_Init                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_InterSEv_Init
(
    void
)
{
#if (  IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON )
    IdsM_Cfg_InterBuff_EveBuffFull.u2Count = 0U;
#endif /* (  IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) */

#if (  IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON )
    IdsM_Cfg_InterBuff_CtxBuffFull.u2Count = 0U;
#endif /* (  IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) */

#if (  IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )
    IdsM_Cfg_InterBuff_TrafficLimit.u2Count = 0U;
#endif /* (  IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) */

    return ;
}

#if ( ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || (  IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || (  IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) )
/****************************************************************************/
/* Function Name | IdsM_InterSEv_SetBuff                                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udSecurityEventId                                        */
/*               | ptDst                                                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_InterSEv_SetBuff
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) udSecurityEventId,
    P2VAR(volatile IdsMEventBuffType, AUTOMATIC, IDSM_CONFIG_DATA) ptDst
)
{
    IdsM_Filters_ReportingModeType ud_ReportMode;

    ud_ReportMode = IdsM_Filter_ReportingMode( udSecurityEventId );

    if( ud_ReportMode != IDSM_REPORTING_MODE_OFF )
    {
        if( ptDst->u2Count == (uint16)0U )
        {
            ptDst->udSEvId = udSecurityEventId;
            ptDst->u2Count = IDSM_NO_COUNT;
#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
            ptDst->udTimestamp = IDSM_INVALID_TIMESTAMP;
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )||( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM ) */
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
            ptDst->u2CtxDataSize = 0U;
            ptDst->u2TableIndex = IDSM_INVALID_INDEX;
            ptDst->u2RecordIndex = IDSM_INVALID_INDEX;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_InterSEv_ClearBuff                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptDst                                                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_InterSEv_ClearBuff
(
    P2VAR(volatile IdsMEventBuffType, AUTOMATIC, IDSM_CONFIG_DATA) ptDst
)
{
    ptDst->u2Count = 0U;

    return ;
}

#endif /* ( ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) || (  IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) || (  IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) ) */


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
