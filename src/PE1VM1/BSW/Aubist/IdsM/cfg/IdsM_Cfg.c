/* IdsM_Cfg_c_v2-1-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Cfg/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/



/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../inc/IdsM_Cfg_Fixed.h"
#include "../inc/IdsM_General.h"
#include "../inc/IdsM_Filter.h"
#include "../../../Security/oXSEC/scc/oxsec_aubif_idsm.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define IDSM_CFG_EVEBUF_NUM         (67U)
#define IDSM_CFG_IDSM_EVENT_NUM     (10U)
#define IDSM_CFG_FILTER_CHAIN_NUM   (4U)
#define IDSM_CFG_AGGRE_DATA_NUM     (9U)
#define IDSM_CFG_CTX_BOX_NUM        (1U)
#define IDSM_CFG_00000_CTX_BUF_SIZE (56U)
#define IDSM_CFG_00000_CTX_BUF_NUM  (67U)

#define IDSM_CFG_CTXDATA_MAXSIZE        (IDSM_CFG_00000_CTX_BUF_SIZE)

#define IDSM_CFG_QSEVBUF_NUM            (20U)
#define IDSM_CFG_TIMESTAMP_SIZE         (0U)
#define IDSM_CFG_CTXDATA_SIZE_HEADER    (1U)
#define IDSM_CFG_QSEVTXBUF_SIZE         (IDSM_EVENTFRAME_SIZE + IDSM_CFG_TIMESTAMP_SIZE + IDSM_CFG_CTXDATA_SIZE_HEADER + IDSM_CFG_CTXDATA_MAXSIZE)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint32 u4Dummy;
    uint8 u1Data00000[ IDSM_CFG_00000_CTX_BUF_NUM * IDSM_CFG_00000_CTX_BUF_SIZE ];
} IdsMCtxDataBuffDataType;

typedef struct {
    uint32 u4Dummy;
    uint8 u1Data[ IDSM_CFG_QSEVTXBUF_SIZE ];
} IdsMTxBuffType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_VAR_NO_INIT
#include <IdsM_MemMap.h>

static VAR(volatile IdsMCtxDataBuffDataType, IDSM_VAR_NO_INIT) IdsM_Cfg_CtxDataBuffData;
static VAR(volatile IdsM_CtxDataBuffStatusType, IDSM_VAR_NO_INIT) IdsM_Cfg_CtxDataBuffStatus00000[ IDSM_CFG_00000_CTX_BUF_NUM ];

static VAR(volatile IdsMEventBuffType, IDSM_VAR_NO_INIT)  IdsM_Cfg_EventBuff[ IDSM_CFG_EVEBUF_NUM ];

static VAR(volatile IdsMAggreFilTmpType, IDSM_VAR_NO_INIT) IdsM_Cfg_AggreBuff[ IDSM_CFG_AGGRE_DATA_NUM ];

static VAR(volatile IdsMQSEvBuffType, IDSM_VAR_NO_INIT) IdsM_Cfg_QSEvBuff[ IDSM_CFG_QSEVBUF_NUM ];
static VAR(IdsMTxBuffType, IDSM_VAR_NO_INIT) IdsM_Cfg_IdsRTxBuff;

VAR(volatile IdsMEventBuffType, IDSM_VAR_NO_INIT) IdsM_Cfg_InterBuff_EveBuffFull;
VAR(volatile IdsMEventBuffType, IDSM_VAR_NO_INIT) IdsM_Cfg_InterBuff_CtxBuffFull;

static VAR(volatile IdsMFilChainTmpType, IDSM_VAR_NO_INIT)  IdsM_Cfg_FilChainTmp[ IDSM_CFG_FILTER_CHAIN_NUM ];

#define IDSM_STOP_SEC_VAR_NO_INIT
#include <IdsM_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_CONST_CONFIG
#include <IdsM_MemMap.h>

CONST(AB_83_ConstV boolean, IDSM_CONFIG_DATA) IdsM_Cfg_bDevErroDetect = FALSE;
CONST(AB_83_ConstV boolean, IDSM_CONFIG_DATA) IdsM_Cfg_bDiagnosticSupport = FALSE;
CONST(AB_83_ConstV boolean, IDSM_CONFIG_DATA) IdsM_Cfg_bSignatureSupport = FALSE;
CONST(AB_83_ConstV boolean, IDSM_CONFIG_DATA) IdsM_Cfg_bVersionInfoApi = FALSE;

CONST(AB_83_ConstV uint16, IDSM_CONFIG_DATA) IdsM_Cfg_u2InstanceId = 11U;

CONST(AB_83_ConstV uint16, IDSM_CONFIG_DATA) IdsM_Cfg_u2IfTxHandleId = 0U;
CONST(AB_83_ConstV uint16, IDSM_CONFIG_DATA) IdsM_Cfg_u2IfTxPduRef = 0U;
CONST(AB_83_ConstV uint16, IDSM_CONFIG_DATA) IdsM_Cfg_u2CtxDataBuffMaxSize = IDSM_CFG_CTXDATA_MAXSIZE;
CONST(AB_83_ConstV uint32, IDSM_CONFIG_DATA) IdsM_Cfg_u4TxPduRTimeOut = 94U;
CONST(AB_83_ConstV IdsM_TxCalloutType, IDSM_CONFIG_DATA) IdsM_Cfg_ptIdsRTxCalloutFunc = &u1_g_oXSECAubIfIdsMIdsRTxAck;
CONST(AB_83_ConstV IdsM_QSEvErrCalloutType, IDSM_CONFIG_DATA) IdsM_Cfg_ptQSEvErrCalloutFunc = &vd_g_oXSECAubIfIdsMQSEvErrAck;
CONST(AB_83_ConstV IdsM_ParamErrCalloutType, IDSM_CONFIG_DATA) IdsM_Cfg_ptParamErrCalloutFunc = &vd_g_oXSECAubIfIdsMParamErrAck;
CONST(AB_83_ConstV IdsM_RamErrCalloutType, IDSM_CONFIG_DATA) IdsM_Cfg_ptRamErrCalloutFunc = &vd_g_oXSECAubIfIdsMRamErrAck;
CONST(AB_83_ConstV IdsM_SecurityEventIdType, IDSM_CONFIG_DATA) IdsM_Cfg_udEveFullId = 2U;
CONST(AB_83_ConstV IdsM_SecurityEventIdType, IDSM_CONFIG_DATA) IdsM_Cfg_udCtxFullId = 3U;

static CONST(AB_83_ConstV IdsMCtxDataBuffType, IDSM_CONFIG_DATA) IdsM_Cfg_CtxData00000 = 
{
    IDSM_CFG_00000_CTX_BUF_SIZE,          /* u2CtxDataBufferSize */
    IDSM_CFG_00000_CTX_BUF_NUM,           /* u2CtxDataBufferNum */
    &IdsM_Cfg_CtxDataBuffStatus00000[0],  /* ptCtxDataStatus */
    &IdsM_Cfg_CtxDataBuffData.u1Data00000[0]         /* ptCtxData */
};


static CONST(AB_83_ConstV IdsMCtxDataBuffAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_CtxDataBuffAcss[IDSM_CFG_CTX_BOX_NUM] = 
{
    { &IdsM_Cfg_CtxData00000 }              /* ptCD[0] */
};

CONST(AB_83_ConstV IdsMCtxDataBoxAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_CtxDataBoxAcss = 
{
    &IdsM_Cfg_CtxDataBuffAcss[0],    /* ptCBox */
    IDSM_CFG_CTX_BOX_NUM,            /* u2CBNum */
    0U                               /* u2Dummy */
};

CONST(AB_83_ConstV IdsMEventBuffAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_EventBuffAcss = 
{
    &IdsM_Cfg_EventBuff[0],           /* ptConfig */
    IDSM_CFG_EVEBUF_NUM,              /* u2ConfigNum */
    0U                                /* u2Dummy */
};

CONST(AB_83_ConstV IdsMAggreFilTmpAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_AggreFilTmpAcss = 
{
    &IdsM_Cfg_AggreBuff[0],              /* ptConfig */
    IDSM_CFG_AGGRE_DATA_NUM,             /* u2ConfigNum */
    0U                                   /* u2Dummy */
};



CONST(AB_83_ConstV IdsMQSEvBuffAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_QSEvBuffAcss = 
{
    &IdsM_Cfg_QSEvBuff[0],              /* ptConfig */
    IDSM_CFG_QSEVBUF_NUM,               /* u2ConfigNum */
    0U                                  /* u2Dummy */
};

CONST(AB_83_ConstV IdsMIdsRTxBuffAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_IdsRTxBuffAcss = 
{
    &IdsM_Cfg_IdsRTxBuff.u1Data[0],      /* ptConfig */
    IDSM_CFG_QSEVTXBUF_SIZE,             /* u2BuffSize */
    0U                                   /* u2Dummy */
};


CONST(AB_83_ConstV IdsMFilEveRateLimitType, IDSM_CONFIG_DATA) IdsM_Cfg_FilEveRateLimit =
{
    200U,     /* u4RateLimitTimeInterval */ 
    10U,    /* u2RateLimitMaximumEvents */
    0U      /* u2Dummy */
};


static CONST(AB_83_ConstV IdsMEventType, IDSM_CONFIG_DATA) IdsM_Cfg_Event[ IDSM_CFG_IDSM_EVENT_NUM ] =
{
    { 0xC500U, IDSM_REPORTING_MODE_DETAILED, 0U, FALSE, TRUE, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, 0U },     /* [0] */
    { 0x85A2U, IDSM_REPORTING_MODE_DETAILED, 0U, FALSE, TRUE, 0U, 0U, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, 0U },     /* [1] */
    { 0x002EU, IDSM_REPORTING_MODE_DETAILED, 0U, FALSE, TRUE, 3U, 1U, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, 0U },     /* [2] */
    { 0x002FU, IDSM_REPORTING_MODE_DETAILED, 0U, FALSE, TRUE, 3U, 2U, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, 0U },     /* [3] */
    { 0xC5D0U, IDSM_REPORTING_MODE_DETAILED, 0U, FALSE, TRUE, 1U, 3U, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, 0U },     /* [4] */
    { 0x85D0U, IDSM_REPORTING_MODE_DETAILED, 0U, FALSE, TRUE, 2U, 4U, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, 0U },     /* [5] */
    { 0xC5A4U, IDSM_REPORTING_MODE_DETAILED, 0U, FALSE, TRUE, 1U, 5U, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, 0U },     /* [6] */
    { 0x85A4U, IDSM_REPORTING_MODE_DETAILED, 0U, FALSE, TRUE, 2U, 6U, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, 0U },     /* [7] */
    { 0xC5C1U, IDSM_REPORTING_MODE_DETAILED, 0U, FALSE, TRUE, 1U, 7U, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, 0U },     /* [8] */
    { 0x85C1U, IDSM_REPORTING_MODE_DETAILED, 0U, FALSE, TRUE, 1U, 8U, IDSM_INVALID_INDEX, IDSM_INVALID_INDEX, 0U }     /* [9] */
};

CONST(AB_83_ConstV IdsMEventAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_EventAcss = 
{
    &IdsM_Cfg_Event[0],               /* ptConfig */
    IDSM_CFG_IDSM_EVENT_NUM,          /* u2ConfigNum */
    0U                                /* u2Dummy */
};

static CONST(AB_83_ConstV IdsMFilterChainType, IDSM_CONFIG_DATA) IdsM_Cfg_FilterChain[ IDSM_CFG_FILTER_CHAIN_NUM ] =
{
    { { IDSM_FILTERS_CTX_USE_FIRST, 0U, 0U, 0U, 60U } }, /* [0] */
    { { IDSM_FILTERS_CTX_USE_FIRST, 0U, 0U, 0U, 202U } }, /* [1] */
    { { IDSM_FILTERS_CTX_USE_FIRST, 0U, 0U, 0U, 102U } }, /* [2] */
    { { IDSM_FILTERS_CTX_USE_FIRST, 0U, 0U, 0U, 1994U } } /* [3] */
};

CONST(AB_83_ConstV IdsMFilterChainAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_FilterChainAcss = 
{
    &IdsM_Cfg_FilterChain[0],         /* ptConfig */
    IDSM_CFG_FILTER_CHAIN_NUM,        /* u2ConfigNum */
    0U                                /* u2Dummy */
};

static CONST(AB_83_ConstV IdsMFilChainFuncTblType, IDSM_CONFIG_DATA) IdsM_Cfg_FilChainFuncTbl[ IDSM_CFG_FILTER_CHAIN_NUM ] =
{
    {{ NULL_PTR, NULL_PTR, &IdsM_Filter_AggreSetBuff, NULL_PTR }}, /* [0] */
    {{ NULL_PTR, NULL_PTR, &IdsM_Filter_AggreSetBuff, NULL_PTR }}, /* [1] */
    {{ NULL_PTR, NULL_PTR, &IdsM_Filter_AggreSetBuff, NULL_PTR }}, /* [2] */
    {{ NULL_PTR, NULL_PTR, &IdsM_Filter_AggreSetBuff, NULL_PTR }} /* [3] */
};

CONST(AB_83_ConstV IdsMFilChainFuncTblAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_FilChainFuncTblAcss = 
{
    &IdsM_Cfg_FilChainFuncTbl[0],     /* ptConfig */
    IDSM_CFG_FILTER_CHAIN_NUM,        /* u2ConfigNum */
    0U                                /* u2Dummy */
};

CONST(AB_83_ConstV IdsMGlobalRateFilFuncTblType, IDSM_CONFIG_DATA) IdsM_Cfg_GlobalRateFilFuncTbl =
{
    { &IdsM_Filter_EventRateLimitation,  NULL_PTR }
};

CONST(AB_83_ConstV IdsMFilChainTmpAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_FilChainTmpAcss = 
{
    &IdsM_Cfg_FilChainTmp[0],         /* ptTmp */
    IDSM_CFG_FILTER_CHAIN_NUM,        /* u2ConfigNum */
    0U                                /* u2Dummy */
};

#define IDSM_STOP_SEC_CONST_CONFIG
#include <IdsM_MemMap.h>



/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

