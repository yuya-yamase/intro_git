/* IdsM_Sink_c_v2-0-3                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/_Sink/CODE                                            */
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
#include "../inc/IdsM_Context.h"
#include "../inc/IdsM_Sink.h"
#include "../inc/IdsM_Std.h"

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )
#include <Rte_StbM_Type.h>
#endif  /* IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR */

#include "../usr/IdsM_Connector.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define IDSM_IDSPROTOCOL_POS0                ((uint8)0U)
#define IDSM_IDSPROTOCOL_POS1                ((uint8)1U)
#define IDSM_IDSPROTOCOL_POS2                ((uint8)2U)
#define IDSM_IDSPROTOCOL_POS3                ((uint8)3U)
#define IDSM_IDSPROTOCOL_POS4                ((uint8)4U)
#define IDSM_IDSPROTOCOL_POS5                ((uint8)5U)
#define IDSM_IDSPROTOCOL_POS6                ((uint8)6U)
#define IDSM_IDSPROTOCOL_POS7                ((uint8)7U)
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
#define IDSM_IDSPROTOCOL_POS8                ((uint8)8U)
#define IDSM_IDSPROTOCOL_POS9                ((uint8)9U)
#define IDSM_IDSPROTOCOL_POS10               ((uint8)10U)
#define IDSM_IDSPROTOCOL_POS11               ((uint8)11U)
#define IDSM_IDSPROTOCOL_POS12               ((uint8)12U)
#define IDSM_IDSPROTOCOL_POS13               ((uint8)13U)
#define IDSM_IDSPROTOCOL_POS14               ((uint8)14U)
#define IDSM_IDSPROTOCOL_POS15               ((uint8)15U)
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */

#define IDSM_PROTOCOL_VERSION                ((uint8)1U)

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
#define IDSM_PROTOCOLHEADER_CTXDATA          ((uint8)0x1U)
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
#define IDSM_PROTOCOLHEADER_TIMESTAMP        ((uint8)0x2U)
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */

#define IDSM_INSTANCEID_MASK                 ((uint16)0x3FFU)

#define IDSM_SENSORID_MASK                   ((uint8)0x3FU)

#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
#define IDSM_TIMESTAMP_SIZE                  ((uint8)8U)
#if (IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR)
#define IDSM_TIMESTAMP_AUTOSAR_MASK          ((uint8)0x3FU)
#define IDSM_TIMESTAMP_AUTOSAR_MASK_64BIT    ((IdsM_TimestampType)0x3FFFFFFFFFFFFFFFU)
#else
#define IDSM_TIMESTAMP_CUSTOM_MASK           ((uint8)0x7FU)
#define IDSM_TIMESTAMP_CUSTOM_MASK_64BIT     ((IdsM_TimestampType)0x7FFFFFFFFFFFFFFFU)
#define IDSM_TIMESTAMP_SOURCE                ((uint8)0x80U)
#define IDSM_TIMESTAMP_SOURCE_64BIT          ((IdsM_TimestampType)0x8000000000000000U)
#endif /* IDSM_CFG_USE_TIMESTAMP */
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
#define IDSM_CTXDATA_SHORTHEADER_SIZE        ((uint16)1U)
#define IDSM_CTXDATA_LONGHEADER_SIZE         ((uint16)4U)
#define IDSM_CTXDATA_LENGTHFORMAT_LONG       ((uint8)0x80U)
#define IDSM_CTXDATA_LENGTHFORMAT_CHK        ((uint16)127U)
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */

#if (IDSM_CFG_USE_IDSR == STD_ON)
#define IDSM_PDUR_S_IDLE                     ((IdsM_PduRStatusType)0x00U)
#define IDSM_PDUR_S_SENDING                  ((IdsM_PduRStatusType)0xE1U)
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#if (IDSM_CFG_USE_IDSR == STD_ON)
typedef uint8 IdsM_PduRStatusType;
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

static FUNC(void, IDSM_CODE) IdsM_Sink_BuildTxMsg
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptEventInfo,
    P2VAR(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptTxMsgData
);

static FUNC(void, IDSM_CODE) IdsM_Sink_BuildEventFrame
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptEventInfo,
    P2VAR(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptTxMsgData
);

#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
static FUNC(Std_ReturnType, IDSM_CODE) IdsM_Sink_ExtractTimestamp
(
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptTxMsgData,
    P2VAR(IdsM_TimestampType, AUTOMATIC, AUTOMATIC) ptTimestamp
);
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
static FUNC(Std_ReturnType, IDSM_CODE) IdsM_Sink_ExtractCtxData
(
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptTxMsgData,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptCtxDataPos,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptCtxDataSize
);
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */

static FUNC(void, IDSM_CODE) IdsM_Sink_ClearBuff
(
    VAR(uint16, AUTOMATIC) u2Index
);

#if (IDSM_CFG_USE_IDSR == STD_ON)
static FUNC(void, IDSM_CODE) IdsM_Sink_IdsRPduRTransmit
(
    void
);

#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_VAR_NO_INIT
#include <IdsM_MemMap.h>

#if (IDSM_CFG_USE_IDSR == STD_ON)
static VAR(volatile IdsM_PduRStatusType, IDSM_VAR_NO_INIT) IdsM_Sink_udPduRStatus;
static VAR(PduInfoType, IDSM_VAR_NO_INIT) IdsM_Sink_stPduInfo;
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Sink_u2IdsRSetQSEvNum;
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Sink_u2IdsRBuffGetIndex;
static VAR(uint32, IDSM_VAR_NO_INIT) IdsM_Sink_u4PduRTxTimerCnt;
static VAR(volatile Std_ReturnType, IDSM_VAR_NO_INIT) IdsM_Sink_udPduRTxResult;
static VAR(volatile boolean, IDSM_VAR_NO_INIT) IdsM_Sink_bPduRTxConfirmation;
static VAR(volatile IdsM_Ab_ErrorStatusType, IDSM_VAR_NO_INIT) IdsM_Sink_udIdsRQSEvError;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Sink_u2IdsRSetQSEvNumRed;
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Sink_u2IdsRBuffGetIndexRed;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if (IDSM_CFG_USE_DEM == STD_ON)
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Sink_u2DemSetQSEvNum;
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Sink_u2DemBuffGetIndex;
static VAR(volatile IdsM_Ab_ErrorStatusType, IDSM_VAR_NO_INIT) IdsM_Sink_udDemQSEvError;
static VAR(uint16, IDSM_VAR_NO_INIT)  IdsM_Sink_u2DemMsgSize;
#if(IDSM_CFG_DEM_BUFF_PADDING == STD_ON)
static VAR(uint16, IDSM_VAR_NO_INIT)  IdsM_Sink_u2DemBuffSize;
#endif  /* IDSM_CFG_DEM_BUFF_PADDING == STD_ON */
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Sink_u2DemSetQSEvNumRed;
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Sink_u2DemBuffGetIndexRed;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
#endif  /* IDSM_CFG_USE_DEM == STD_ON */

static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Sink_u2BuffSetIndex;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Sink_u2BuffSetIndexRed;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

#define IDSM_STOP_SEC_VAR_NO_INIT
#include <IdsM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

/****************************************************************************/
/* Function Name | IdsM_Sink_Init                                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Sink_Init
(
    void
)
{
    uint16 u2_Index;
    
    for( u2_Index = 0U; u2_Index < IdsM_Cfg_QSEvBuffAcss.u2ConfigNum; u2_Index++)
    {
#if (IDSM_CFG_USE_IDSR == STD_ON)
        IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2_Index].bIdsRQSEvGet = FALSE;
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */
#if (IDSM_CFG_USE_DEM == STD_ON)
        IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2_Index].bDemQSEvGet  = FALSE;
#endif  /* IDSM_CFG_USE_DEM == STD_ON */
    }
    
#if (IDSM_CFG_USE_IDSR == STD_ON)
    IdsM_Sink_u2IdsRSetQSEvNum     = 0U;
    IdsM_Sink_u2IdsRBuffGetIndex   = 0U;
    IdsM_Sink_bPduRTxConfirmation  = FALSE;
    IdsM_Sink_udIdsRQSEvError      = IDSM_AB_E_NONE;
    IdsM_Sink_udPduRStatus         = IDSM_PDUR_S_IDLE;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    IdsM_Sink_u2IdsRSetQSEvNumRed   = IDSM_RED_INIT_U2;
    IdsM_Sink_u2IdsRBuffGetIndexRed = IDSM_RED_INIT_U2;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if (IDSM_CFG_USE_DEM == STD_ON)
    IdsM_Sink_u2DemSetQSEvNum   = 0U;
    IdsM_Sink_u2DemBuffGetIndex = 0U;
    IdsM_Sink_udDemQSEvError    = IDSM_AB_E_NONE;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    IdsM_Sink_u2DemSetQSEvNumRed   = IDSM_RED_INIT_U2;
    IdsM_Sink_u2DemBuffGetIndexRed = IDSM_RED_INIT_U2;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
#endif  /* IDSM_CFG_USE_DEM == STD_ON */

    IdsM_Sink_u2BuffSetIndex = 0U;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    IdsM_Sink_u2BuffSetIndexRed = IDSM_RED_INIT_U2;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
    
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Sink_TxMsgSizeCalc                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptEventInfo                                              */
/*               | ptTxMsgSize                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Sink_TxMsgSizeCalc
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptEventInfo,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptTxMsgSize
)
{
    uint16 u2_TxMsgDataLen = IDSM_EVENTFRAME_SIZE;
#if (IDSM_CFG_USE_CTXDATA == STD_ON)
    uint16 u2_CtxDataSize = ptEventInfo->u2CtxDataSize;

    if( u2_CtxDataSize > (uint16)0U )
    {
        u2_TxMsgDataLen += u2_CtxDataSize;
        
        if( u2_CtxDataSize <= IDSM_CTXDATA_LENGTHFORMAT_CHK )
        {
            u2_TxMsgDataLen += IDSM_CTXDATA_SHORTHEADER_SIZE;
        }
        else
        {
            u2_TxMsgDataLen += IDSM_CTXDATA_LONGHEADER_SIZE;
        }
    }
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */

#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
    if( ptEventInfo->udTimestamp != IDSM_INVALID_TIMESTAMP )
    {
        u2_TxMsgDataLen += (uint16)IDSM_TIMESTAMP_SIZE;
    }
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */
    
    *ptTxMsgSize = u2_TxMsgDataLen;
    
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Sink_SetBuff                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptEventInfo :                                            */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Sink_SetBuff
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptEventInfo
)
{
    Std_ReturnType ud_StdRet = E_NOT_OK;
    uint16         u2_SetIndex = IdsM_Sink_u2BuffSetIndex;
#if (IDSM_CFG_USE_IDSR == STD_ON)
    uint16         u2_IdsRSetQSEvNum = IdsM_Sink_u2IdsRSetQSEvNum;
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */
#if (IDSM_CFG_USE_DEM == STD_ON)
    uint16         u2_DemSetQSEvNum = IdsM_Sink_u2DemSetQSEvNum;
#endif  /* IDSM_CFG_USE_DEM == STD_ON */

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    uint16         u2_SetIndexRed = IdsM_Sink_u2BuffSetIndexRed;
#if (IDSM_CFG_USE_IDSR == STD_ON)
    uint16         u2_IdsRSetQSEvNumRed = IdsM_Sink_u2IdsRSetQSEvNumRed;
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */
#if (IDSM_CFG_USE_DEM == STD_ON)
    uint16         u2_DemSetQSEvNumRed  = IdsM_Sink_u2DemSetQSEvNumRed;
#endif  /* IDSM_CFG_USE_DEM == STD_ON */

#if ((IDSM_CFG_USE_IDSR == STD_ON) && (IDSM_CFG_USE_DEM == STD_ON))
    if( ( u2_IdsRSetQSEvNum == (uint16)(~u2_IdsRSetQSEvNumRed) ) &&
        ( u2_DemSetQSEvNum  == (uint16)(~u2_DemSetQSEvNumRed) ) &&
        ( u2_SetIndex       == (uint16)(~u2_SetIndexRed) ) )
    {
#elif ((IDSM_CFG_USE_IDSR == STD_ON) && (IDSM_CFG_USE_DEM != STD_ON))
    if( ( u2_IdsRSetQSEvNum == (uint16)(~u2_IdsRSetQSEvNumRed) ) &&
        ( u2_SetIndex       == (uint16)(~u2_SetIndexRed) ) )
    {
#else
    if( ( u2_DemSetQSEvNum  == (uint16)(~u2_DemSetQSEvNumRed) ) &&
        ( u2_SetIndex       == (uint16)(~u2_SetIndexRed) ) )
    {
#endif
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

#if ((IDSM_CFG_USE_IDSR == STD_ON) && (IDSM_CFG_USE_DEM == STD_ON))
        if(( u2_IdsRSetQSEvNum < IdsM_Cfg_QSEvBuffAcss.u2ConfigNum ) && ( u2_DemSetQSEvNum < IdsM_Cfg_QSEvBuffAcss.u2ConfigNum ))
#elif ((IDSM_CFG_USE_IDSR == STD_ON) && (IDSM_CFG_USE_DEM != STD_ON))
        if( u2_IdsRSetQSEvNum < IdsM_Cfg_QSEvBuffAcss.u2ConfigNum )
#else
        if( u2_DemSetQSEvNum < IdsM_Cfg_QSEvBuffAcss.u2ConfigNum )
#endif
        {
            IdsM_Std_EventBuffCopy(&IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2_SetIndex].stEventInfo, ptEventInfo);
#if (IDSM_CFG_USE_IDSR == STD_ON)
            u2_IdsRSetQSEvNum++;
            IdsM_Sink_u2IdsRSetQSEvNum = u2_IdsRSetQSEvNum;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
            IdsM_Sink_u2IdsRSetQSEvNumRed = (uint16)(~u2_IdsRSetQSEvNum);
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if (IDSM_CFG_USE_DEM == STD_ON)
            u2_DemSetQSEvNum++;
            IdsM_Sink_u2DemSetQSEvNum = u2_DemSetQSEvNum;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
            IdsM_Sink_u2DemSetQSEvNumRed = (uint16)(~u2_DemSetQSEvNum);
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
#endif  /* IDSM_CFG_USE_DEM == STD_ON */

            u2_SetIndex++;
            if( u2_SetIndex >= IdsM_Cfg_QSEvBuffAcss.u2ConfigNum )
            {
                u2_SetIndex = 0U;
            }
            
            IdsM_Sink_u2BuffSetIndex = u2_SetIndex;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
            IdsM_Sink_u2BuffSetIndexRed = (uint16)(~u2_SetIndex);
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
            
            ud_StdRet = E_OK;
        }

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    }
    else
    {
        IdsM_General_SetRamError();
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    return ud_StdRet;
}

#if (IDSM_CFG_USE_IDSR == STD_ON)
/****************************************************************************/
/* Function Name | IdsM_Sink_IdsRTransmit                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Sink_IdsRTransmit
(
    void
)
{
    P2VAR(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_IdsRTxBuff;
    VAR(IdsMEventBuffType, AUTOMATIC) ud_EventInfo;
    uint16              u2_TxMsgDataLen;
    uint16              u2_IdsRSetQSEvNum;
    uint16              u2_IdsRGetIndex;
    uint16              u2_GetQSEvCnt;
    boolean             b_SinkIdsR    = FALSE;
    IdsM_PduRStatusType ud_PduRStatus = IdsM_Sink_udPduRStatus;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    boolean             b_RamChkError = FALSE;
    uint16              u2_IdsRSetQSEvNumRed;
    uint16              u2_IdsRGetIndexRed;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    if( ud_PduRStatus == IDSM_PDUR_S_IDLE )
    {
        SchM_Enter_IdsM_General();
        u2_IdsRGetIndex   = IdsM_Sink_u2IdsRBuffGetIndex;
        u2_IdsRSetQSEvNum = IdsM_Sink_u2IdsRSetQSEvNum;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
        u2_IdsRGetIndexRed   = IdsM_Sink_u2IdsRBuffGetIndexRed;
        u2_IdsRSetQSEvNumRed = IdsM_Sink_u2IdsRSetQSEvNumRed;

        if( ( u2_IdsRGetIndex   == (uint16)(~u2_IdsRGetIndexRed) ) &&
            ( u2_IdsRSetQSEvNum == (uint16)(~u2_IdsRSetQSEvNumRed) ) )
        {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
            for( u2_GetQSEvCnt = 0U; u2_GetQSEvCnt < u2_IdsRSetQSEvNum; u2_GetQSEvCnt++ )
            {
                IdsM_Std_EventBuffCopy(&ud_EventInfo, &IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2_IdsRGetIndex].stEventInfo);

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
                if( ud_EventInfo.udSEvId < IdsM_Cfg_EventAcss.u2ConfigNum )
                {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

                    b_SinkIdsR = IdsM_Cfg_EventAcss.ptConfig[ud_EventInfo.udSEvId].bSinkIdsR;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
                }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

                if( b_SinkIdsR == (boolean)TRUE )
                {
                    break;
                }

                IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2_IdsRGetIndex].bIdsRQSEvGet = TRUE;
                IdsM_Sink_ClearBuff( u2_IdsRGetIndex );
                u2_IdsRGetIndex++;
                if( u2_IdsRGetIndex >= IdsM_Cfg_QSEvBuffAcss.u2ConfigNum )
                {
                    u2_IdsRGetIndex = 0U;
                }
            }
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
        }
        else
        {
            b_RamChkError = (boolean)TRUE;
        }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
        SchM_Exit_IdsM_General();

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
        if ( b_RamChkError == (boolean)TRUE )
        {
            IdsM_General_SetRamError();
        }
        else
        {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
            if( b_SinkIdsR == (boolean)TRUE )
            {
                IdsM_Sink_TxMsgSizeCalc( &ud_EventInfo, &u2_TxMsgDataLen );

                if( u2_TxMsgDataLen <= IdsM_Cfg_IdsRTxBuffAcss.u2BuffSize )
                {
                    pt_IdsRTxBuff = IdsM_Cfg_IdsRTxBuffAcss.ptIdsRTxBuff;
                    IdsM_Sink_BuildTxMsg( &ud_EventInfo, pt_IdsRTxBuff );

                    IdsM_Sink_stPduInfo.SduDataPtr = pt_IdsRTxBuff;
                    IdsM_Sink_stPduInfo.SduLength  = u2_TxMsgDataLen;

                    IdsM_Sink_u4PduRTxTimerCnt = 0UL;

                    IdsM_Sink_IdsRPduRTransmit();
                }
            }

            SchM_Enter_IdsM_General();
            if( b_SinkIdsR == (boolean)TRUE )
            {
                IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2_IdsRGetIndex].bIdsRQSEvGet = TRUE;
                IdsM_Sink_ClearBuff( u2_IdsRGetIndex );
                
                u2_IdsRGetIndex++;
                if( u2_IdsRGetIndex >= IdsM_Cfg_QSEvBuffAcss.u2ConfigNum )
                {
                    u2_IdsRGetIndex = 0U;
                }
                u2_GetQSEvCnt++;
            }

            IdsM_Sink_u2IdsRBuffGetIndex = u2_IdsRGetIndex;
            u2_IdsRSetQSEvNum = IdsM_Sink_u2IdsRSetQSEvNum - u2_GetQSEvCnt;
            IdsM_Sink_u2IdsRSetQSEvNum = u2_IdsRSetQSEvNum;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
            IdsM_Sink_u2IdsRBuffGetIndexRed = (uint16)(~u2_IdsRGetIndex);
            IdsM_Sink_u2IdsRSetQSEvNumRed = (uint16)(~u2_IdsRSetQSEvNum);
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
            SchM_Exit_IdsM_General();

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
        }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Sink_IdsRTxConfirmation                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId                                                  */
/*               | udresult                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Sink_IdsRTxConfirmation
(
    VAR(PduIdType, AUTOMATIC) udPduId,
    VAR(Std_ReturnType, AUTOMATIC) udresult
)
{
    uint16 u2_IfTxHandleId = IdsM_Cfg_u2IfTxHandleId;
    IdsM_PduRStatusType ud_PduRStatus;
    
    if( udPduId == (PduIdType)u2_IfTxHandleId )
    {
        ud_PduRStatus = IdsM_Sink_udPduRStatus;
        if( ud_PduRStatus == IDSM_PDUR_S_SENDING )
        {
            IdsM_Sink_udPduRTxResult      = udresult;
            IdsM_Sink_bPduRTxConfirmation = TRUE;
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Sink_IdsRTxConfirmationChk                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Sink_IdsRTxConfirmationChk
(
    void
)
{
    uint32    u4_TxPduRTimeOut;
    PduIdType ud_IfTxPduRef;
    Std_ReturnType ud_ConfResult = E_OK;
    IdsM_PduRStatusType ud_PduRStatus = IdsM_Sink_udPduRStatus;
    boolean b_PduRTxConfirmation;
    Std_ReturnType ud_PduRTxResult;

    if( ud_PduRStatus == IDSM_PDUR_S_SENDING )
    {
        b_PduRTxConfirmation = IdsM_Sink_bPduRTxConfirmation;
        if( b_PduRTxConfirmation == (boolean)TRUE )
        {
            ud_PduRTxResult = IdsM_Sink_udPduRTxResult;
            if( ud_PduRTxResult != (Std_ReturnType)E_OK )
            {
                IdsM_Sink_udIdsRQSEvError = IDSM_AB_E_PDUR_TX_CONFIRMATION_ERROR;
                ud_ConfResult = E_NOT_OK;
            }

            IdsM_Sink_udPduRStatus        = IDSM_PDUR_S_IDLE;
            IdsM_Sink_bPduRTxConfirmation = FALSE;
        }
        else
        {
            IdsM_Sink_u4PduRTxTimerCnt++;
            u4_TxPduRTimeOut = IdsM_Cfg_u4TxPduRTimeOut;

            if( IdsM_Sink_u4PduRTxTimerCnt >= u4_TxPduRTimeOut )
            {
                ud_IfTxPduRef = (PduIdType)IdsM_Cfg_u2IfTxPduRef;
                (void)IdsM_Connector_PduRCancelTransmit( ud_IfTxPduRef );/* no return check required */

                IdsM_Sink_udIdsRQSEvError     = IDSM_AB_E_PDUR_TX_TIMEOUT;
                IdsM_Sink_udPduRStatus        = IDSM_PDUR_S_IDLE;
                IdsM_Sink_bPduRTxConfirmation = FALSE;
                ud_ConfResult = E_NOT_OK;
            }
        }
    }

    return ud_ConfResult;
}

/****************************************************************************/
/* Function Name | IdsM_Sink_IdsRQSEvErrNotify                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Sink_IdsRQSEvErrNotify
(
    void
)
{
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_IdsRTxBuff;
    CONST(IdsM_QSEvErrCalloutType, AUTOMATIC) pt_QSEvErrCallout = IdsM_Cfg_ptQSEvErrCalloutFunc;
    IdsM_Ab_ErrorStatusType ud_IdsRQSEvError    = IdsM_Sink_udIdsRQSEvError;
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
    IdsM_TimestampType  ud_Timestamp = 0U;
    Std_ReturnType      ud_TimestampRet;
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */
#if (IDSM_CFG_USE_CTXDATA == STD_ON)
    Std_ReturnType      ud_CtxDataRet;
    uint16              u2_CtxDataPos  = 0U;
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */
    P2CONST(IdsM_TimestampType, AUTOMATIC, AUTOMATIC) pt_Timestamp = NULL_PTR;
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_CtxData         = NULL_PTR;
    uint16 u2_CtxDataSize = 0U;
    
    if( ud_IdsRQSEvError != IDSM_AB_E_NONE )
    {
        if( pt_QSEvErrCallout != NULL_PTR )
        {
            pt_IdsRTxBuff = IdsM_Cfg_IdsRTxBuffAcss.ptIdsRTxBuff;
            
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
            ud_TimestampRet = IdsM_Sink_ExtractTimestamp( pt_IdsRTxBuff, &ud_Timestamp );
            if( ud_TimestampRet == (Std_ReturnType)E_OK )
            {
                pt_Timestamp = &ud_Timestamp;
            }
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
            ud_CtxDataRet = IdsM_Sink_ExtractCtxData( pt_IdsRTxBuff, &u2_CtxDataPos, &u2_CtxDataSize );
            if( ud_CtxDataRet == (Std_ReturnType)E_OK )
            {
                pt_CtxData = &pt_IdsRTxBuff[u2_CtxDataPos];
            }
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */

            pt_QSEvErrCallout( pt_IdsRTxBuff,
                               pt_Timestamp,
                               pt_CtxData,
                               u2_CtxDataSize,
                               ud_IdsRQSEvError );
        }
        
        IdsM_Sink_udIdsRQSEvError = IDSM_AB_E_NONE;
    }
    
    return ;
}

#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if (IDSM_CFG_USE_DEM == STD_ON)
/****************************************************************************/
/* Function Name | IdsM_Sink_DemTransmit                                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Sink_DemTransmit
(
    void
)
{
    P2VAR(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_DemTxBuff;
    VAR(IdsMEventBuffType, AUTOMATIC) ud_EventInfo;
    uint16             u2_TxMsgDataLen;
    uint16             u2_DemSetQSEvNum;
    uint16             u2_DemGetIndex;
    uint16             u2_GetQSEvCnt;
    boolean            b_SinkDem    = FALSE;
    Std_ReturnType     ud_DemRet;
    Dem_EventIdType    ud_DemEventId;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    boolean            b_RamChkError = FALSE;
    uint16             u2_DemSetQSEvNumRed;
    uint16             u2_DemGetIndexRed;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    SchM_Enter_IdsM_General();
    u2_DemGetIndex   = IdsM_Sink_u2DemBuffGetIndex;
    u2_DemSetQSEvNum = IdsM_Sink_u2DemSetQSEvNum;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    u2_DemGetIndexRed   = IdsM_Sink_u2DemBuffGetIndexRed;
    u2_DemSetQSEvNumRed = IdsM_Sink_u2DemSetQSEvNumRed;

    if( ( u2_DemGetIndex   == (uint16)(~u2_DemGetIndexRed) ) &&
        ( u2_DemSetQSEvNum == (uint16)(~u2_DemSetQSEvNumRed) ) )
    {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
        for( u2_GetQSEvCnt = 0U; u2_GetQSEvCnt < u2_DemSetQSEvNum; u2_GetQSEvCnt++ )
        {
            IdsM_Std_EventBuffCopy(&ud_EventInfo, &IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2_DemGetIndex].stEventInfo);

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
            if( ud_EventInfo.udSEvId < IdsM_Cfg_EventAcss.u2ConfigNum )
            {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

                b_SinkDem = IdsM_Cfg_EventAcss.ptConfig[ud_EventInfo.udSEvId].bSinkDem;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
            }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
            
            if( b_SinkDem == (boolean)TRUE )
            {
                break;
            }
            
            IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2_DemGetIndex].bDemQSEvGet = TRUE;
            IdsM_Sink_ClearBuff( u2_DemGetIndex );
            u2_DemGetIndex++;
            if( u2_DemGetIndex >= IdsM_Cfg_QSEvBuffAcss.u2ConfigNum )
            {
                u2_DemGetIndex = 0U;
            }
        }
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    }
    else
    {
        b_RamChkError = (boolean)TRUE;
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
    SchM_Exit_IdsM_General();

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    if ( b_RamChkError == (boolean)TRUE )
    {
        IdsM_General_SetRamError();
    }
    else
    {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
        if( b_SinkDem == (boolean)TRUE )
        {
            IdsM_Sink_TxMsgSizeCalc( &ud_EventInfo, &u2_TxMsgDataLen );
            
            if( u2_TxMsgDataLen <= IdsM_Cfg_DemTxBuffAcss.u2BuffSize )
            {
                pt_DemTxBuff = IdsM_Cfg_DemTxBuffAcss.ptDemTxBuff;
                IdsM_Sink_BuildTxMsg( &ud_EventInfo, pt_DemTxBuff );
                
                if( u2_TxMsgDataLen <= IdsM_Cfg_EventAcss.ptConfig[ud_EventInfo.udSEvId].u2DemBuffSize )
                {
                    IdsM_Sink_u2DemMsgSize  = u2_TxMsgDataLen;
#if(IDSM_CFG_DEM_BUFF_PADDING == STD_ON)
                    IdsM_Sink_u2DemBuffSize = IdsM_Cfg_EventAcss.ptConfig[ud_EventInfo.udSEvId].u2DemBuffSize;
#endif  /* IDSM_CFG_DEM_BUFF_PADDING == STD_ON */
                    
                    ud_DemEventId = IdsM_Cfg_EventAcss.ptConfig[ud_EventInfo.udSEvId].udDemEventId;
                    ud_DemRet = IdsM_Connector_DemTransmit( ud_DemEventId );
                    
                    if( ud_DemRet == (Std_ReturnType)E_OK )
                    {
                        /* No Processing */
                    }
                    else if( ud_DemRet == (Std_ReturnType)DEM_E_ACCESS_PROCESSING )
                    {
                        IdsM_Sink_udDemQSEvError = IDSM_AB_E_DEM_ACCESS_PROCESSING;
                    }
                    else if( ud_DemRet == (Std_ReturnType)DEM_E_MEMORY_OVERFLOW )
                    {
                        IdsM_Sink_udDemQSEvError = IDSM_AB_E_DEM_MEMORY_OVERFLOW;
                    }
                    else
                    {
                        IdsM_Sink_udDemQSEvError = IDSM_AB_E_DEM_REQUEST_ERROR;
                    }
                }
                else
                {
                    IdsM_Sink_udDemQSEvError = IDSM_AB_E_DEM_BUFFSIZE_ERROR;
                }
            }
        }

        SchM_Enter_IdsM_General();
        if( b_SinkDem == (boolean)TRUE )
        {
            IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2_DemGetIndex].bDemQSEvGet = TRUE;
            IdsM_Sink_ClearBuff( u2_DemGetIndex );
            
            u2_DemGetIndex++;
            if( u2_DemGetIndex >= IdsM_Cfg_QSEvBuffAcss.u2ConfigNum )
            {
                u2_DemGetIndex = 0U;
            }
            u2_GetQSEvCnt++;
        }

        IdsM_Sink_u2DemBuffGetIndex = u2_DemGetIndex;
        u2_DemSetQSEvNum = IdsM_Sink_u2DemSetQSEvNum - u2_GetQSEvCnt;
        IdsM_Sink_u2DemSetQSEvNum = u2_DemSetQSEvNum;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
        IdsM_Sink_u2DemBuffGetIndexRed = (uint16)(~u2_DemGetIndex);
        IdsM_Sink_u2DemSetQSEvNumRed = (uint16)(~u2_DemSetQSEvNum);
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
        SchM_Exit_IdsM_General();

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Sink_DemQSEvErrNotify                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Sink_DemQSEvErrNotify
(
    void
)
{
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_DemTxBuff;
    CONST(IdsM_QSEvErrCalloutType, AUTOMATIC) pt_QSEvErrCallout = IdsM_Cfg_ptQSEvErrCalloutFunc;
    IdsM_Ab_ErrorStatusType ud_DemQSEvError     = IdsM_Sink_udDemQSEvError;
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
    IdsM_TimestampType  ud_Timestamp = 0U;
    Std_ReturnType      ud_TimestampRet;
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */
#if (IDSM_CFG_USE_CTXDATA == STD_ON)
    Std_ReturnType      ud_CtxDataRet;
    uint16              u2_CtxDataPos  = 0U;
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */
    P2CONST(IdsM_TimestampType, AUTOMATIC, AUTOMATIC) pt_Timestamp = NULL_PTR;
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_CtxData         = NULL_PTR;
    uint16 u2_CtxDataSize = 0U;
    
    if( ud_DemQSEvError != IDSM_AB_E_NONE )
    {
        if( pt_QSEvErrCallout != NULL_PTR )
        {
            pt_DemTxBuff = IdsM_Cfg_DemTxBuffAcss.ptDemTxBuff;
            
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
            ud_TimestampRet = IdsM_Sink_ExtractTimestamp( pt_DemTxBuff, &ud_Timestamp );
            if( ud_TimestampRet == (Std_ReturnType)E_OK )
            {
                pt_Timestamp = &ud_Timestamp;
            }
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
            ud_CtxDataRet = IdsM_Sink_ExtractCtxData( pt_DemTxBuff, &u2_CtxDataPos, &u2_CtxDataSize );
            if( ud_CtxDataRet == (Std_ReturnType)E_OK )
            {
                pt_CtxData = &pt_DemTxBuff[u2_CtxDataPos];
            }
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */

            pt_QSEvErrCallout( pt_DemTxBuff,
                               pt_Timestamp,
                               pt_CtxData,
                               u2_CtxDataSize,
                               ud_DemQSEvError );
        }
        
        IdsM_Sink_udDemQSEvError = IDSM_AB_E_NONE;
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Sink_DemReadCallback                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptBuffer                                                 */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Sink_DemReadCallback
(
    P2VAR(uint8, AUTOMATIC, IDSM_APPL_DATA) ptBuffer
)
{
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_DemTxBuff;
    Std_ReturnType ud_StdRet = E_NOT_OK;
#if(IDSM_CFG_DEM_BUFF_PADDING == STD_ON)
    uint8 u1_PaddingData = IdsM_Cfg_u1DemBuffPaddingData;
#endif  /* IDSM_CFG_DEM_BUFF_PADDING == STD_ON */
    
    if( ptBuffer != NULL_PTR )
    {
        pt_DemTxBuff = IdsM_Cfg_DemTxBuffAcss.ptDemTxBuff;
        
        IdsM_Std_MemCpy( &ptBuffer[0], &pt_DemTxBuff[0], IdsM_Sink_u2DemMsgSize );
#if(IDSM_CFG_DEM_BUFF_PADDING == STD_ON)
        IdsM_Std_MemSet( &ptBuffer[IdsM_Sink_u2DemMsgSize], u1_PaddingData, IdsM_Sink_u2DemBuffSize - IdsM_Sink_u2DemMsgSize );
#endif  /* IDSM_CFG_DEM_BUFF_PADDING == STD_ON */

        ud_StdRet = E_OK;
    }
    else
    {
        IdsM_Sink_udDemQSEvError = IDSM_AB_E_DEM_POINTER_ERROR;
    }
    
    return ud_StdRet;
}

#endif  /* IDSM_CFG_USE_DEM == STD_ON */

/****************************************************************************/
/* Function Name | IdsM_Sink_QSEvBuffFullNotify                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptEventInfo :                                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Sink_QSEvBuffFullNotify
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptEventInfo
)
{
    uint8 u1_EventFrame[IDSM_EVENTFRAME_SIZE];
    CONST(IdsM_QSEvErrCalloutType, AUTOMATIC) pt_QSEvErrCallout = IdsM_Cfg_ptQSEvErrCalloutFunc;
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
    IdsM_TimestampType  ud_Timestamp;
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */
    P2CONST(IdsM_TimestampType, AUTOMATIC, AUTOMATIC) pt_Timestamp      = NULL_PTR;
    P2CONST(volatile uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_CtxDataBuff = NULL_PTR;
    uint16 u2_CtxDataSize = 0U;

    if( pt_QSEvErrCallout != NULL_PTR )
    {
        IdsM_Sink_BuildEventFrame( ptEventInfo, &u1_EventFrame[0] );
    
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
        if( ptEventInfo->udTimestamp != IDSM_INVALID_TIMESTAMP )
        {
#if (IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR)
            ud_Timestamp =  ptEventInfo->udTimestamp & IDSM_TIMESTAMP_AUTOSAR_MASK_64BIT;
#else
            ud_Timestamp = ( IDSM_TIMESTAMP_SOURCE_64BIT | ( ptEventInfo->udTimestamp & IDSM_TIMESTAMP_CUSTOM_MASK_64BIT ) );
#endif /* IDSM_CFG_USE_TIMESTAMP */

            pt_Timestamp = &ud_Timestamp;
        }
#endif /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
        if( ptEventInfo->u2CtxDataSize > (uint16)0U )
        {
            u2_CtxDataSize = ptEventInfo->u2CtxDataSize;
            pt_CtxDataBuff = IdsM_Context_GetBuffAdr( ptEventInfo->u2TableIndex, ptEventInfo->u2RecordIndex );
            if( pt_CtxDataBuff == NULL_PTR )
            {
                u2_CtxDataSize = 0U;
            }
        }
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */

        pt_QSEvErrCallout( &u1_EventFrame[0],
                           pt_Timestamp,
                           pt_CtxDataBuff,
                           u2_CtxDataSize,
                           IDSM_AB_E_QSEVBUFF_FULL );
    }

    return ;
}

#if ((IDSM_CFG_RAM_ERROR_CHECK == STD_ON) && (IDSM_CFG_USE_IDSR == STD_ON))
/****************************************************************************/
/* Function Name | IdsM_Sink_DetectRamError                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Sink_DetectRamError
(
    void
)
{
    IdsM_PduRStatusType ud_PduRStatus = IdsM_Sink_udPduRStatus;

    if( ( ud_PduRStatus != IDSM_PDUR_S_IDLE ) &&
        ( ud_PduRStatus != IDSM_PDUR_S_SENDING ) )
    {
        IdsM_General_SetRamError();
    }
    
    return ;
}
#endif /* ((IDSM_CFG_RAM_ERROR_CHECK == STD_ON) && (IDSM_CFG_USE_IDSR == STD_ON)) */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | IdsM_Sink_BuildTxMsg                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptEventInfo                                              */
/*               | ptTxMsgData                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, IDSM_CODE) IdsM_Sink_BuildTxMsg
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptEventInfo,
    P2VAR(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptTxMsgData
)
{
#if (IDSM_CFG_USE_CTXDATA == STD_ON)
    uint16 u2_Index = IDSM_EVENTFRAME_SIZE;
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */
    
    IdsM_Sink_BuildEventFrame( ptEventInfo, ptTxMsgData );

#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
    if( ptEventInfo->udTimestamp != IDSM_INVALID_TIMESTAMP )
    {
#if (IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR)
        ptTxMsgData[IDSM_IDSPROTOCOL_POS8]  =  (uint8)( ptEventInfo->udTimestamp >> IDSM_BIT_SHIFT_56 ) & IDSM_TIMESTAMP_AUTOSAR_MASK ;
#else
        ptTxMsgData[IDSM_IDSPROTOCOL_POS8]  = ( IDSM_TIMESTAMP_SOURCE | ( (uint8)( ptEventInfo->udTimestamp >> IDSM_BIT_SHIFT_56 ) & IDSM_TIMESTAMP_CUSTOM_MASK ) );
#endif /* IDSM_CFG_USE_TIMESTAMP */
        ptTxMsgData[IDSM_IDSPROTOCOL_POS9]  = (uint8) ( ptEventInfo->udTimestamp >> IDSM_BIT_SHIFT_48 );
        ptTxMsgData[IDSM_IDSPROTOCOL_POS10] = (uint8) ( ptEventInfo->udTimestamp >> IDSM_BIT_SHIFT_40 );
        ptTxMsgData[IDSM_IDSPROTOCOL_POS11] = (uint8) ( ptEventInfo->udTimestamp >> IDSM_BIT_SHIFT_32 );
        ptTxMsgData[IDSM_IDSPROTOCOL_POS12] = (uint8) ( ptEventInfo->udTimestamp >> IDSM_BIT_SHIFT_24 );
        ptTxMsgData[IDSM_IDSPROTOCOL_POS13] = (uint8) ( ptEventInfo->udTimestamp >> IDSM_BIT_SHIFT_16 );
        ptTxMsgData[IDSM_IDSPROTOCOL_POS14] = (uint8) ( ptEventInfo->udTimestamp >> IDSM_BIT_SHIFT_8 );
        ptTxMsgData[IDSM_IDSPROTOCOL_POS15] = (uint8) ( ptEventInfo->udTimestamp );

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
        u2_Index += (uint16)IDSM_TIMESTAMP_SIZE;
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */
    }
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
    if( ptEventInfo->u2CtxDataSize > (uint16)0U )
    {
        if( ptEventInfo->u2CtxDataSize <= IDSM_CTXDATA_LENGTHFORMAT_CHK )
        {
            ptTxMsgData[u2_Index] = (uint8)ptEventInfo->u2CtxDataSize;

            u2_Index += IDSM_CTXDATA_SHORTHEADER_SIZE;
        }
        else
        {
            ptTxMsgData[u2_Index] = IDSM_CTXDATA_LENGTHFORMAT_LONG;
            ptTxMsgData[u2_Index + IDSM_IDSPROTOCOL_POS1] = 0U;
            ptTxMsgData[u2_Index + IDSM_IDSPROTOCOL_POS2] = (uint8)( ptEventInfo->u2CtxDataSize >> IDSM_BIT_SHIFT_8 );
            ptTxMsgData[u2_Index + IDSM_IDSPROTOCOL_POS3] = (uint8)( ptEventInfo->u2CtxDataSize );

            u2_Index += IDSM_CTXDATA_LONGHEADER_SIZE;
        }

        IdsM_Context_GetCtxData( ptEventInfo->u2TableIndex,
                                 ptEventInfo->u2RecordIndex,
                                 ptEventInfo->u2CtxDataSize,
                                 &ptTxMsgData[u2_Index] );
    }
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */
    
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Sink_BuildEventFrame                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptEventInfo                                              */
/*               | ptTxMsgData                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, IDSM_CODE) IdsM_Sink_BuildEventFrame
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptEventInfo,
    P2VAR(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptTxMsgData
)
{
    uint8  u1_ProtocolHeader = 0U;
    
#if (IDSM_CFG_USE_CTXDATA == STD_ON)
    if( ptEventInfo->u2CtxDataSize > (uint16)0U )
    {
        u1_ProtocolHeader = IDSM_PROTOCOLHEADER_CTXDATA;
    }
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */
    
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
    if( ptEventInfo->udTimestamp != (uint64)IDSM_INVALID_TIMESTAMP )
    {
        u1_ProtocolHeader |= IDSM_PROTOCOLHEADER_TIMESTAMP;
    }
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */
    
    ptTxMsgData[IDSM_IDSPROTOCOL_POS0] = ( IDSM_PROTOCOL_VERSION << IDSM_BIT_SHIFT_4 ) | u1_ProtocolHeader;
    ptTxMsgData[IDSM_IDSPROTOCOL_POS1] = (uint8)(( IdsM_Cfg_u2InstanceId & IDSM_INSTANCEID_MASK ) >> IDSM_BIT_SHIFT_2 );
    ptTxMsgData[IDSM_IDSPROTOCOL_POS2] = (uint8)(( IdsM_Cfg_u2InstanceId & IDSM_INSTANCEID_MASK ) << IDSM_BIT_SHIFT_6 ) | 
                                         ( IdsM_Cfg_EventAcss.ptConfig[ptEventInfo->udSEvId].u1SensorInstanceId & IDSM_SENSORID_MASK );
    ptTxMsgData[IDSM_IDSPROTOCOL_POS3] = (uint8)( IdsM_Cfg_EventAcss.ptConfig[ptEventInfo->udSEvId].u2ExternalEventId >> IDSM_BIT_SHIFT_8 );
    ptTxMsgData[IDSM_IDSPROTOCOL_POS4] = (uint8)( IdsM_Cfg_EventAcss.ptConfig[ptEventInfo->udSEvId].u2ExternalEventId );
    ptTxMsgData[IDSM_IDSPROTOCOL_POS5] = (uint8)( ptEventInfo->u2Count >> IDSM_BIT_SHIFT_8 );
    ptTxMsgData[IDSM_IDSPROTOCOL_POS6] = (uint8)( ptEventInfo->u2Count );
    ptTxMsgData[IDSM_IDSPROTOCOL_POS7] = 0U;
    
    return ;
}

#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
/****************************************************************************/
/* Function Name | IdsM_Sink_ExtractTimestamp                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptTxMsgData                                              */
/*               | ptTimestamp                                              */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, IDSM_CODE) IdsM_Sink_ExtractTimestamp
(
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptTxMsgData,
    P2VAR(IdsM_TimestampType, AUTOMATIC, AUTOMATIC) ptTimestamp
)
{
    Std_ReturnType ud_StdRet = E_NOT_OK;

    if( (ptTxMsgData[IDSM_IDSPROTOCOL_POS0] & IDSM_PROTOCOLHEADER_TIMESTAMP) != (uint8)0U )
    {
        *ptTimestamp  = (IdsM_TimestampType)ptTxMsgData[IDSM_IDSPROTOCOL_POS8]  << IDSM_BIT_SHIFT_56;
        *ptTimestamp |= (IdsM_TimestampType)ptTxMsgData[IDSM_IDSPROTOCOL_POS9]  << IDSM_BIT_SHIFT_48;
        *ptTimestamp |= (IdsM_TimestampType)ptTxMsgData[IDSM_IDSPROTOCOL_POS10] << IDSM_BIT_SHIFT_40;
        *ptTimestamp |= (IdsM_TimestampType)ptTxMsgData[IDSM_IDSPROTOCOL_POS11] << IDSM_BIT_SHIFT_32;
        *ptTimestamp |= (IdsM_TimestampType)ptTxMsgData[IDSM_IDSPROTOCOL_POS12] << IDSM_BIT_SHIFT_24;
        *ptTimestamp |= (IdsM_TimestampType)ptTxMsgData[IDSM_IDSPROTOCOL_POS13] << IDSM_BIT_SHIFT_16;
        *ptTimestamp |= (IdsM_TimestampType)ptTxMsgData[IDSM_IDSPROTOCOL_POS14] << IDSM_BIT_SHIFT_8;
        *ptTimestamp |= (IdsM_TimestampType)ptTxMsgData[IDSM_IDSPROTOCOL_POS15];
        
        ud_StdRet = E_OK;
    }
    
    return ud_StdRet;
}
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
/****************************************************************************/
/* Function Name | IdsM_Sink_ExtractCtxData                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptTxMsgData                                              */
/*               | ptTimestamp                                              */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, IDSM_CODE) IdsM_Sink_ExtractCtxData
(
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptTxMsgData,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptCtxDataPos,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptCtxDataSize
)
{
    Std_ReturnType ud_StdRet = E_NOT_OK;
    uint16 u2_Index;

    if( (ptTxMsgData[IDSM_IDSPROTOCOL_POS0] & IDSM_PROTOCOLHEADER_CTXDATA) != (uint8)0U )
    {
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
        if( (ptTxMsgData[IDSM_IDSPROTOCOL_POS0] & IDSM_PROTOCOLHEADER_TIMESTAMP) != (uint8)0U )
        {
            u2_Index = (uint16)IDSM_EVENTFRAME_SIZE + (uint16)IDSM_TIMESTAMP_SIZE;
        }
        else
        {
            u2_Index = IDSM_EVENTFRAME_SIZE;
        }
#else
        u2_Index = IDSM_EVENTFRAME_SIZE;
#endif  /* IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE */
        
        if( (ptTxMsgData[u2_Index] & IDSM_CTXDATA_LENGTHFORMAT_LONG) != (uint8)0U )
        {
            *ptCtxDataSize  = (uint16)ptTxMsgData[u2_Index + IDSM_IDSPROTOCOL_POS2] << IDSM_BIT_SHIFT_8;
            *ptCtxDataSize |= (uint16)ptTxMsgData[u2_Index + IDSM_IDSPROTOCOL_POS3];
            
            u2_Index += IDSM_CTXDATA_LONGHEADER_SIZE;
        }
        else
        {
            *ptCtxDataSize = (uint16)ptTxMsgData[u2_Index];
            
            u2_Index += IDSM_CTXDATA_SHORTHEADER_SIZE;
        }
        
        *ptCtxDataPos = u2_Index;
        
        ud_StdRet = E_OK;
    }
    else
    {
        *ptCtxDataSize = 0U;
    }
    
    return ud_StdRet;
}
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */

/****************************************************************************/
/* Function Name | IdsM_Sink_ClearBuff                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index                                                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, IDSM_CODE) IdsM_Sink_ClearBuff
(
    VAR(uint16, AUTOMATIC) u2Index
)
{
#if (IDSM_CFG_USE_IDSR == STD_ON)
    boolean b_SendIdsR     = IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2Index].bIdsRQSEvGet;
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if (IDSM_CFG_USE_DEM == STD_ON)
    boolean b_SendDem      = IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2Index].bDemQSEvGet;
#endif  /* IDSM_CFG_USE_DEM == STD_ON */

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
    uint16  u2_TableIndex  = IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2Index].stEventInfo.u2TableIndex;
    uint16  u2_RecordIndex = IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2Index].stEventInfo.u2RecordIndex;
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */

#if ((IDSM_CFG_USE_IDSR == STD_ON) && (IDSM_CFG_USE_DEM == STD_ON))
    if( (b_SendIdsR == (boolean)TRUE ) && ( b_SendDem == (boolean)TRUE ) )
    {
        IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2Index].bIdsRQSEvGet = FALSE;
        IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2Index].bDemQSEvGet = FALSE;

#elif ((IDSM_CFG_USE_IDSR == STD_ON) && (IDSM_CFG_USE_DEM != STD_ON))
    if( b_SendIdsR == (boolean)TRUE )
    {
        IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2Index].bIdsRQSEvGet = FALSE;

#else
    if( b_SendDem == (boolean)TRUE )
    {
        IdsM_Cfg_QSEvBuffAcss.ptQSEvBuff[u2Index].bDemQSEvGet = FALSE;

#endif

#if (IDSM_CFG_USE_CTXDATA == STD_ON)
        if( u2_TableIndex != IDSM_INVALID_INDEX )
        {
            IdsM_Context_ClearBuff( u2_TableIndex, u2_RecordIndex );
        }
#endif  /* IDSM_CFG_USE_CTXDATA == STD_ON */
    }

    return ;
}

#if (IDSM_CFG_USE_IDSR == STD_ON)
/****************************************************************************/
/* Function Name | IdsM_Sink_IdsRPduRTransmit                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, IDSM_CODE) IdsM_Sink_IdsRPduRTransmit
(
    void
)
{
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_IdsRTxBuff;
    Std_ReturnType     ud_CalloutRet = E_OK;
    Std_ReturnType     ud_PduRRet;
    PduIdType          ud_IfTxPduRef;
    CONST(IdsM_TxCalloutType, IDSM_CONFIG_DATA) pt_TxCallout  = IdsM_Cfg_ptIdsRTxCalloutFunc;
    
    if( pt_TxCallout != NULL_PTR )
    {
        pt_IdsRTxBuff = IdsM_Cfg_IdsRTxBuffAcss.ptIdsRTxBuff;
        ud_CalloutRet = pt_TxCallout( pt_IdsRTxBuff, (uint16)IdsM_Sink_stPduInfo.SduLength );
    }
    
    if( ud_CalloutRet == (Std_ReturnType)E_OK )
    {
        IdsM_Sink_udPduRStatus = IDSM_PDUR_S_SENDING;
        
        ud_IfTxPduRef = (PduIdType)IdsM_Cfg_u2IfTxPduRef;
        ud_PduRRet = IdsM_Connector_PduRTransmit( ud_IfTxPduRef, &IdsM_Sink_stPduInfo );
        
        if( ud_PduRRet == (Std_ReturnType)E_OK )
        {
            /* No Processing */
        }
        else if( ud_PduRRet == IDSM_E_BUSY )
        {
            IdsM_Sink_udIdsRQSEvError = IDSM_AB_E_PDUR_TX_REQUEST_BUSY;
            IdsM_Sink_udPduRStatus    = IDSM_PDUR_S_IDLE;
        }
        else
        {
            IdsM_Sink_udIdsRQSEvError = IDSM_AB_E_PDUR_TX_REQUEST_ERROR;
            IdsM_Sink_udPduRStatus    = IDSM_PDUR_S_IDLE;
        }
    }

    return ;
}

#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/*  v2-0-1     :2023/01/23                                                  */
/*  v2-0-2     :2023/02/24                                                  */
/*  v2-0-3     :2023/04/10                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
