/* Csm_Cfg_c_v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | Csm/Cfg/CODE                                               */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Csm_Cfg_Fixed.h>
#include "../../../../swc/Sec/inc/Sec_Usr_GenSeedCallback.h"
#include <WrapCrypto.h>
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Csm */
#define CSM_CFG_JOB_CONFIG_MAX          (5UL)
#define CSM_CFG_PRIMITIVE_INFO_MAX      (5UL)
#define CSM_CFG_KEY_MAX                 (5UL)
#define CSM_CFG_QUEUE_MAX               (5UL)
#define CSM_CFG_JOB_REDIRECT_INFO_MAX   (0UL)
#define CSM_CFG_ERROR_CALLOUT_MAX       (1UL)
#define CSM_CFG_TIMEOUT_CALLOUT_MAX     (1UL)

#define CSM_CFG_QUEUE_PRIORITY_SIZE_000            (1UL)
#define CSM_CFG_QUEUE_PRIORITY256_SIZE_000           (2UL)

#define CSM_CFG_QUEUE_PRIORITY_SIZE_001            (1UL)
#define CSM_CFG_QUEUE_PRIORITY256_SIZE_001           (2UL)

#define CSM_CFG_QUEUE_PRIORITY_SIZE_002            (1UL)
#define CSM_CFG_QUEUE_PRIORITY256_SIZE_002           (2UL)

#define CSM_CFG_QUEUE_PRIORITY_SIZE_003            (1UL)
#define CSM_CFG_QUEUE_PRIORITY256_SIZE_003           (2UL)

#define CSM_CFG_QUEUE_PRIORITY_SIZE_004            (1UL)
#define CSM_CFG_QUEUE_PRIORITY256_SIZE_004           (2UL)



/* CryIf */
#define CRYIF_KEY_ELEMENT_MAX_SIZE          (1UL)
#define CRYIF_CRYPTO_NUM                    (1UL)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define CSM_START_SEC_VAR_NO_INIT
#include <Csm_MemMap.h>

/* Csm */
static VAR(Csm_Cfg_Ram_QueueElementType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueElement_Priority256_000[CSM_CFG_QUEUE_PRIORITY256_SIZE_000];

static VAR(Csm_Cfg_Ram_QueueRingBufferType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueRingBuffer_000[CSM_CFG_QUEUE_PRIORITY_SIZE_000];
static VAR(Csm_Cfg_Ram_QueueElementType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueElement_Priority256_001[CSM_CFG_QUEUE_PRIORITY256_SIZE_001];

static VAR(Csm_Cfg_Ram_QueueRingBufferType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueRingBuffer_001[CSM_CFG_QUEUE_PRIORITY_SIZE_001];
static VAR(Csm_Cfg_Ram_QueueElementType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueElement_Priority256_002[CSM_CFG_QUEUE_PRIORITY256_SIZE_002];

static VAR(Csm_Cfg_Ram_QueueRingBufferType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueRingBuffer_002[CSM_CFG_QUEUE_PRIORITY_SIZE_002];
static VAR(Csm_Cfg_Ram_QueueElementType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueElement_Priority256_003[CSM_CFG_QUEUE_PRIORITY256_SIZE_003];

static VAR(Csm_Cfg_Ram_QueueRingBufferType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueRingBuffer_003[CSM_CFG_QUEUE_PRIORITY_SIZE_003];
static VAR(Csm_Cfg_Ram_QueueElementType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueElement_Priority256_004[CSM_CFG_QUEUE_PRIORITY256_SIZE_004];

static VAR(Csm_Cfg_Ram_QueueRingBufferType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueRingBuffer_004[CSM_CFG_QUEUE_PRIORITY_SIZE_004];


static VAR(Csm_Cfg_Ram_QueueChannelDataType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueChannelData[CSM_CFG_QUEUE_MAX];

static VAR(Csm_Cfg_Ram_JobSubDataType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stJobSubData[CSM_CFG_JOB_CONFIG_MAX];

#define CSM_STOP_SEC_VAR_NO_INIT
#include <Csm_MemMap.h>

#define CSM_START_SEC_SHARED_VAR_NO_INIT
#include <Csm_MemMap.h>

static VAR(Csm_Cfg_Ram_JobDataType, CSM_SHARED_VAR_NO_INIT) Csm_Cfg_Ram_stJobData[CSM_CFG_JOB_CONFIG_MAX];

/* CryIf */
static VAR(uint8, CSM_SHARED_VAR_NO_INIT) CryIf_Cfg_u1KeyElem[CRYIF_KEY_ELEMENT_MAX_SIZE];

#define CSM_STOP_SEC_SHARED_VAR_NO_INIT
#include <Csm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CSM_START_SEC_SHARED_CONST_CONFIG
#include <Csm_MemMap.h>

static CONST(Crypto_PrimitiveInfoType, CSM_SHARED_CONFIG_DATA) Csm_Cfg_stPrimitiveInfo[CSM_CFG_PRIMITIVE_INFO_MAX] =
{
    {
      16UL,                         /* resultLength */
      CRYPTO_ENCRYPT,          /* service */
      {
        CRYPTO_ALGOFAM_AES,        /* family */
        CRYPTO_ALGOFAM_NOT_SET,    /* secondaryFamily */
        16UL,                       /* keyLength */
        CRYPTO_ALGOMODE_ECB       /* mode */
      }
    },
    {
      4096UL,                         /* resultLength */
      CRYPTO_DECRYPT,          /* service */
      {
        CRYPTO_ALGOFAM_AES,        /* family */
        CRYPTO_ALGOFAM_NOT_SET,    /* secondaryFamily */
        16UL,                       /* keyLength */
        CRYPTO_ALGOMODE_CBC       /* mode */
      }
    },
    {
      0UL,                         /* resultLength */
      CRYPTO_SIGNATUREVERIFY,          /* service */
      {
        CRYPTO_ALGOFAM_RSA,        /* family */
        CRYPTO_ALGOFAM_NOT_SET,    /* secondaryFamily */
        384UL,                       /* keyLength */
        CRYPTO_ALGOMODE_RSASSA_PSS       /* mode */
      }
    },
    {
      0UL,                        /* resultLength */
      CRYPTO_RANDOMSEED,          /* service */
      {
        CRYPTO_ALGOFAM_RNG,        /* family */
        CRYPTO_ALGOFAM_NOT_SET,    /* secondaryFamily */
        0UL,                      /* keyLength */
        CRYPTO_ALGOMODE_CTRDRBG       /* mode */
      }
    },
    {
      16UL,                         /* resultLength */
      CRYPTO_RANDOMGENERATE,          /* service */
      {
        CRYPTO_ALGOFAM_RNG,        /* family */
        CRYPTO_ALGOFAM_NOT_SET,    /* secondaryFamily */
        0UL,                       /* keyLength */
        CRYPTO_ALGOMODE_CTRDRBG       /* mode */
      }
    }
};

static CONST(Csm_Cfg_JobConfigType, CSM_SHARED_CONFIG_DATA) Csm_Cfg_stJobConfig[CSM_CFG_JOB_CONFIG_MAX] =
{
    {
      {
        0UL,                /* jobId */
        256UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[0], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        1UL,                /* jobId */
        256UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[1], /* primitiveInfo */
        2UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        2UL,                /* jobId */
        256UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        3UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        3UL,                /* jobId */
        256UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        4UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        4UL,                /* jobId */
        256UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[4], /* primitiveInfo */
        4UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    }
};

#define CSM_STOP_SEC_SHARED_CONST_CONFIG
#include <Csm_MemMap.h>

#define CSM_START_SEC_CONST_CONFIG
#include <Csm_MemMap.h>

/* Csm */
CONST(AB_83_ConstV boolean, CSM_CONFIG_DATA) Csm_Cfg_bVersionInfoApi = FALSE;

static CONST(AB_83_ConstV uint32, CSM_CONFIG_DATA) Csm_Cfg_u4KeyConfig[CSM_CFG_KEY_MAX] =
{
    0U,
    1U,
    2U,
    3U,
    4U
};

CONST(AB_83_ConstV Csm_Cfg_KeyConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stKey = 
{
    &Csm_Cfg_u4KeyConfig[0],    /* ptConfig */
    (uint32)CSM_CFG_KEY_MAX     /* u4ConfigNum */
};

static CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, CSM_CONFIG_DATA) Csm_Cfg_stQueuePriorityConfig_000[CSM_CFG_QUEUE_PRIORITY_SIZE_000] =
{
    {
        CSM_CFG_QUEUE_PRIORITY256_SIZE_000,              /* u4QueueSize */
        &Csm_Cfg_Ram_stQueueElement_Priority256_000[0],  /* ptElementData */
        &Csm_Cfg_Ram_stQueueRingBuffer_000[0],   /* ptRingBuffData */
        256U,                  /* u2Priority */
        0U                                      /* u2Dummy */
    }

};
static CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, CSM_CONFIG_DATA) Csm_Cfg_stQueuePriorityConfig_001[CSM_CFG_QUEUE_PRIORITY_SIZE_001] =
{
    {
        CSM_CFG_QUEUE_PRIORITY256_SIZE_001,              /* u4QueueSize */
        &Csm_Cfg_Ram_stQueueElement_Priority256_001[0],  /* ptElementData */
        &Csm_Cfg_Ram_stQueueRingBuffer_001[0],   /* ptRingBuffData */
        256U,                  /* u2Priority */
        0U                                      /* u2Dummy */
    }

};
static CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, CSM_CONFIG_DATA) Csm_Cfg_stQueuePriorityConfig_002[CSM_CFG_QUEUE_PRIORITY_SIZE_002] =
{
    {
        CSM_CFG_QUEUE_PRIORITY256_SIZE_002,              /* u4QueueSize */
        &Csm_Cfg_Ram_stQueueElement_Priority256_002[0],  /* ptElementData */
        &Csm_Cfg_Ram_stQueueRingBuffer_002[0],   /* ptRingBuffData */
        256U,                  /* u2Priority */
        0U                                      /* u2Dummy */
    }

};
static CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, CSM_CONFIG_DATA) Csm_Cfg_stQueuePriorityConfig_003[CSM_CFG_QUEUE_PRIORITY_SIZE_003] =
{
    {
        CSM_CFG_QUEUE_PRIORITY256_SIZE_003,              /* u4QueueSize */
        &Csm_Cfg_Ram_stQueueElement_Priority256_003[0],  /* ptElementData */
        &Csm_Cfg_Ram_stQueueRingBuffer_003[0],   /* ptRingBuffData */
        256U,                  /* u2Priority */
        0U                                      /* u2Dummy */
    }

};
static CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, CSM_CONFIG_DATA) Csm_Cfg_stQueuePriorityConfig_004[CSM_CFG_QUEUE_PRIORITY_SIZE_004] =
{
    {
        CSM_CFG_QUEUE_PRIORITY256_SIZE_004,              /* u4QueueSize */
        &Csm_Cfg_Ram_stQueueElement_Priority256_004[0],  /* ptElementData */
        &Csm_Cfg_Ram_stQueueRingBuffer_004[0],   /* ptRingBuffData */
        256U,                  /* u2Priority */
        0U                                      /* u2Dummy */
    }

};


static CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, CSM_CONFIG_DATA) Csm_Cfg_stQueueConfig[CSM_CFG_QUEUE_MAX] =
{
    {
      0UL,                             /* u4CryIfChannelId */
      1UL,                         /* u4DequeueStop */
      CSM_CFG_QUEUE_PRIORITY_SIZE_000,                             /* u4ConfigNum */
      &Csm_Cfg_stQueuePriorityConfig_000[0],/* ptPriorityConfig */
      &Csm_Cfg_Ram_stQueueChannelData[0],    /* ptChannelData */
      5000U,                         /* u2ChannelTimeOut */
      0U                                    /* u2Dummy */
    },
    {
      1UL,                             /* u4CryIfChannelId */
      1UL,                         /* u4DequeueStop */
      CSM_CFG_QUEUE_PRIORITY_SIZE_001,                             /* u4ConfigNum */
      &Csm_Cfg_stQueuePriorityConfig_001[0],/* ptPriorityConfig */
      &Csm_Cfg_Ram_stQueueChannelData[1],    /* ptChannelData */
      5000U,                         /* u2ChannelTimeOut */
      0U                                    /* u2Dummy */
    },
    {
      2UL,                             /* u4CryIfChannelId */
      1UL,                         /* u4DequeueStop */
      CSM_CFG_QUEUE_PRIORITY_SIZE_002,                             /* u4ConfigNum */
      &Csm_Cfg_stQueuePriorityConfig_002[0],/* ptPriorityConfig */
      &Csm_Cfg_Ram_stQueueChannelData[2],    /* ptChannelData */
      5000U,                         /* u2ChannelTimeOut */
      0U                                    /* u2Dummy */
    },
    {
      3UL,                             /* u4CryIfChannelId */
      1UL,                         /* u4DequeueStop */
      CSM_CFG_QUEUE_PRIORITY_SIZE_003,                             /* u4ConfigNum */
      &Csm_Cfg_stQueuePriorityConfig_003[0],/* ptPriorityConfig */
      &Csm_Cfg_Ram_stQueueChannelData[3],    /* ptChannelData */
      5000U,                         /* u2ChannelTimeOut */
      0U                                    /* u2Dummy */
    },
    {
      4UL,                             /* u4CryIfChannelId */
      1UL,                         /* u4DequeueStop */
      CSM_CFG_QUEUE_PRIORITY_SIZE_004,                             /* u4ConfigNum */
      &Csm_Cfg_stQueuePriorityConfig_004[0],/* ptPriorityConfig */
      &Csm_Cfg_Ram_stQueueChannelData[4],    /* ptChannelData */
      5000U,                         /* u2ChannelTimeOut */
      0U                                    /* u2Dummy */
    }
};

CONST(AB_83_ConstV Csm_Cfg_QueueConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stQueue = 
{
    &Csm_Cfg_stQueueConfig[0],           /* ptConfig */
    (uint32)CSM_CFG_QUEUE_MAX            /* u4ConfigNum */
};



static CONST(Csm_Cfg_JobSubConfigType, CSM_CONFIG_DATA) Csm_Cfg_stJobSubConfig[CSM_CFG_JOB_CONFIG_MAX] =
{
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[1],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[0],         /* ptJobQueue */
      &WrapCrypto_EncryptCallout,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[2],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &WrapCrypto_DecryptCallout,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[3],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &WrapCrypto_SigVerifyCallout,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[4],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[3],         /* ptJobQueue */
      &Sec_Usr_CallbackRandomSeed,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[4],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[4],         /* ptJobQueue */
      &Sec_Usr_CallbackRandomGenerate,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    }
};

CONST(Csm_Cfg_JobConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stJob = 
{
    &Csm_Cfg_stJobConfig[0],        /* ptConfig */
    &Csm_Cfg_stJobSubConfig[0],     /* ptSubConfig */
    &Csm_Cfg_Ram_stJobData[0],      /* ptData */
    &Csm_Cfg_Ram_stJobSubData[0],   /* ptSubData */
    CSM_CFG_JOB_CONFIG_MAX  /* u4ConfigNum */
};

static CONST(AB_83_ConstV Csm_ErrorCalloutType, CSM_CONFIG_DATA) Csm_Cfg_ptErrorCalloutFunc[CSM_CFG_ERROR_CALLOUT_MAX] =
{
    &WrapCrypto_ErrorCallout
};

CONST(AB_83_ConstV Csm_Cfg_ErrorCalloutConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stErrorCallout = 
{
    &Csm_Cfg_ptErrorCalloutFunc[0],    /* ptConfig */
    (uint32)CSM_CFG_ERROR_CALLOUT_MAX  /* u4ConfigNum */
};

static CONST(AB_83_ConstV Csm_TimeOutCalloutType, CSM_CONFIG_DATA) Csm_Cfg_ptTimeOutCalloutFunc[CSM_CFG_TIMEOUT_CALLOUT_MAX] =
{
    &WrapCrypto_TimeoutCallout
};

CONST(AB_83_ConstV Csm_Cfg_TimeOutCalloutConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stTimeOutCallout = 
{
    &Csm_Cfg_ptTimeOutCalloutFunc[0],    /* ptConfig */
    CSM_CFG_TIMEOUT_CALLOUT_MAX  /* u4ConfigNum */
};

/* CryIf */
CONST(AB_83_ConstV boolean, CSM_CONFIG_DATA) CryIf_Cfg_bVersionInfoApi = FALSE;

static CONST(AB_83_ConstV CryIf_Cfg_KeyConfigType, CSM_CONFIG_DATA) CryIf_Cfg_stKeyConfig[CSM_CFG_KEY_MAX] =
{
    {
        15UL,           /* u4CryptoKeyId */
        0UL             /* u4CryptoIndex */
    },
    {
        4UL,           /* u4CryptoKeyId */
        0UL             /* u4CryptoIndex */
    },
    {
        5UL,           /* u4CryptoKeyId */
        0UL             /* u4CryptoIndex */
    },
    {
        17UL,           /* u4CryptoKeyId */
        0UL             /* u4CryptoIndex */
    },
    {
        16UL,           /* u4CryptoKeyId */
        0UL             /* u4CryptoIndex */
    }
};

CONST(AB_83_ConstV CryIf_Cfg_KeyConfigAccessType, CSM_CONFIG_DATA) CryIf_Cfg_stKey =
{
    &CryIf_Cfg_stKeyConfig[0],  /* ptConfig */
    (uint32)CSM_CFG_KEY_MAX     /* u4ConfigNum */
};

static CONST(AB_83_ConstV CryIf_Cfg_ChannelConfigType, CSM_CONFIG_DATA) CryIf_Cfg_stChannelConfig[CSM_CFG_QUEUE_MAX] =
{
    {
        4UL,            /* u4ObjectId */
        0UL             /* u4CryptoIndex */
    },
    {
        5UL,            /* u4ObjectId */
        0UL             /* u4CryptoIndex */
    },
    {
        6UL,            /* u4ObjectId */
        0UL             /* u4CryptoIndex */
    },
    {
        2UL,            /* u4ObjectId */
        0UL             /* u4CryptoIndex */
    },
    {
        3UL,            /* u4ObjectId */
        0UL             /* u4CryptoIndex */
    }
};

CONST(AB_83_ConstV CryIf_Cfg_ChannelConfigAccessType, CSM_CONFIG_DATA) CryIf_Cfg_stChannel =
{
    &CryIf_Cfg_stChannelConfig[0],    /* ptConfig */
    (uint32)CSM_CFG_QUEUE_MAX         /* u4ConfigNum */

};

static CONST(AB_83_ConstV CryIf_Cfg_FuncConfigType, CSM_CONFIG_DATA) CryIf_Cfg_stFuncConfig[CRYIF_CRYPTO_NUM] =
{
    {
        Crypto_83_sw_ProcessJob,
        Crypto_83_sw_CancelJob,
        Crypto_83_sw_KeyElementSet,
        Crypto_83_sw_KeySetValid,
        Crypto_83_sw_KeyElementGet,
        Crypto_83_sw_KeyElementCopy,
        Crypto_83_sw_KeyElementCopyPartial,
        Crypto_83_sw_KeyCopy,
        Crypto_83_sw_RandomSeed,
        Crypto_83_sw_KeyGenerate,
        Crypto_83_sw_KeyDerive,
        Crypto_83_sw_KeyExchangeCalcPubVal,
        Crypto_83_sw_KeyExchangeCalcSecret
    }
};

CONST(AB_83_ConstV CryIf_Cfg_FuncConfigAccessType, CSM_CONFIG_DATA) CryIf_Cfg_stFunc =
{
    &CryIf_Cfg_stFuncConfig[0],     /* ptConfig */
    (uint32)CRYIF_CRYPTO_NUM        /* u4ConfigNum */

};

CONST(AB_83_ConstV CryIf_Cfg_ElemConfigAccessType, CSM_CONFIG_DATA) CryIf_Cfg_stElem =
{
    &CryIf_Cfg_u1KeyElem[0],        /* ptConfig */
    CRYIF_KEY_ELEMENT_MAX_SIZE      /* u4ConfigNum */
};

#define CSM_STOP_SEC_CONST_CONFIG
#include <Csm_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/



/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/




/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

