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
#include <Crypto_82_Hsm_Custom_Algorithms.h>
#include <Csm_User.h>
#include <SecOC_Cbk.h>
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Csm */
#define CSM_CFG_JOB_CONFIG_MAX          (49UL)
#define CSM_CFG_PRIMITIVE_INFO_MAX      (4UL)
#define CSM_CFG_KEY_MAX                 (2UL)
#define CSM_CFG_QUEUE_MAX               (3UL)
#define CSM_CFG_JOB_REDIRECT_INFO_MAX   (0UL)
#define CSM_CFG_ERROR_CALLOUT_MAX       (1UL)
#define CSM_CFG_TIMEOUT_CALLOUT_MAX     (1UL)

#define CSM_CFG_QUEUE_PRIORITY_SIZE_000            (1UL)
#define CSM_CFG_QUEUE_PRIORITY001_SIZE_000           (1UL)

#define CSM_CFG_QUEUE_PRIORITY_SIZE_001            (1UL)
#define CSM_CFG_QUEUE_PRIORITY001_SIZE_001           (1UL)

#define CSM_CFG_QUEUE_PRIORITY_SIZE_002            (1UL)
#define CSM_CFG_QUEUE_PRIORITY001_SIZE_002           (1UL)



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
static VAR(Csm_Cfg_Ram_QueueElementType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueElement_Priority001_000[CSM_CFG_QUEUE_PRIORITY001_SIZE_000];

static VAR(Csm_Cfg_Ram_QueueRingBufferType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueRingBuffer_000[CSM_CFG_QUEUE_PRIORITY_SIZE_000];
static VAR(Csm_Cfg_Ram_QueueElementType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueElement_Priority001_001[CSM_CFG_QUEUE_PRIORITY001_SIZE_001];

static VAR(Csm_Cfg_Ram_QueueRingBufferType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueRingBuffer_001[CSM_CFG_QUEUE_PRIORITY_SIZE_001];
static VAR(Csm_Cfg_Ram_QueueElementType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueElement_Priority001_002[CSM_CFG_QUEUE_PRIORITY001_SIZE_002];

static VAR(Csm_Cfg_Ram_QueueRingBufferType, CSM_VAR_NO_INIT) Csm_Cfg_Ram_stQueueRingBuffer_002[CSM_CFG_QUEUE_PRIORITY_SIZE_002];


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
      0UL,                        /* resultLength */
      CRYPTO_KEYSETVALID,         /* service */
      {
        CRYPTO_ALGOFAM_NOT_SET,                 /* family */
        CRYPTO_ALGOFAM_NOT_SET,                 /* secondaryFamily */
        0UL,                      /* keyLength */
        CRYPTO_ALGOMODE_NOT_SET                  /* mode */
      }
    },
    {
      16UL,                         /* resultLength */
      CRYPTO_MACGENERATE,          /* service */
      {
        CRYPTO_ALGOFAM_AES,        /* family */
        CRYPTO_ALGOFAM_NOT_SET,    /* secondaryFamily */
        16UL,                       /* keyLength */
        CRYPTO_ALGOMODE_CMAC       /* mode */
      }
    },
    {
      0UL,                         /* resultLength */
      CRYPTO_MACVERIFY,          /* service */
      {
        CRYPTO_ALGOFAM_AES,        /* family */
        CRYPTO_ALGOFAM_NOT_SET,    /* secondaryFamily */
        16UL,                       /* keyLength */
        CRYPTO_ALGOMODE_CMAC       /* mode */
      }
    }
};

static CONST(Csm_Cfg_JobConfigType, CSM_SHARED_CONFIG_DATA) Csm_Cfg_stJobConfig[CSM_CFG_JOB_CONFIG_MAX] =
{
    {
      {
        0UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        1UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        2UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        3UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        4UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        5UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        6UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        7UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        8UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        9UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        10UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        11UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        12UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        13UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        14UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        15UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        16UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        17UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        18UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        19UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        20UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        21UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        22UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        23UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        24UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        25UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        26UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        27UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        28UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        29UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        30UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        31UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        32UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        33UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        34UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        35UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        36UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        37UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        38UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        39UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        40UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        41UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        42UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        43UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        44UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[3], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        45UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[2], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        46UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[1], /* primitiveInfo */
        0UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        47UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[1], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
        CRYPTO_PROCESSING_ASYNC    /* processingType */
      }
    },
    {
      {
        48UL,                /* jobId */
        1UL    /* jobPriority */
      },
      {
        &Csm_Cfg_stPrimitiveInfo[0], /* primitiveInfo */
        1UL,                        /* cryIfKeyId */
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
    1U
};

CONST(AB_83_ConstV Csm_Cfg_KeyConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stKey = 
{
    &Csm_Cfg_u4KeyConfig[0],    /* ptConfig */
    (uint32)CSM_CFG_KEY_MAX     /* u4ConfigNum */
};

static CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, CSM_CONFIG_DATA) Csm_Cfg_stQueuePriorityConfig_000[CSM_CFG_QUEUE_PRIORITY_SIZE_000] =
{
    {
        CSM_CFG_QUEUE_PRIORITY001_SIZE_000,              /* u4QueueSize */
        &Csm_Cfg_Ram_stQueueElement_Priority001_000[0],  /* ptElementData */
        &Csm_Cfg_Ram_stQueueRingBuffer_000[0],   /* ptRingBuffData */
        1U,                  /* u2Priority */
        0U                                      /* u2Dummy */
    }

};
static CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, CSM_CONFIG_DATA) Csm_Cfg_stQueuePriorityConfig_001[CSM_CFG_QUEUE_PRIORITY_SIZE_001] =
{
    {
        CSM_CFG_QUEUE_PRIORITY001_SIZE_001,              /* u4QueueSize */
        &Csm_Cfg_Ram_stQueueElement_Priority001_001[0],  /* ptElementData */
        &Csm_Cfg_Ram_stQueueRingBuffer_001[0],   /* ptRingBuffData */
        1U,                  /* u2Priority */
        0U                                      /* u2Dummy */
    }

};
static CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, CSM_CONFIG_DATA) Csm_Cfg_stQueuePriorityConfig_002[CSM_CFG_QUEUE_PRIORITY_SIZE_002] =
{
    {
        CSM_CFG_QUEUE_PRIORITY001_SIZE_002,              /* u4QueueSize */
        &Csm_Cfg_Ram_stQueueElement_Priority001_002[0],  /* ptElementData */
        &Csm_Cfg_Ram_stQueueRingBuffer_002[0],   /* ptRingBuffData */
        1U,                  /* u2Priority */
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
      10U,                         /* u2ChannelTimeOut */
      0U                                    /* u2Dummy */
    },
    {
      1UL,                             /* u4CryIfChannelId */
      1UL,                         /* u4DequeueStop */
      CSM_CFG_QUEUE_PRIORITY_SIZE_001,                             /* u4ConfigNum */
      &Csm_Cfg_stQueuePriorityConfig_001[0],/* ptPriorityConfig */
      &Csm_Cfg_Ram_stQueueChannelData[1],    /* ptChannelData */
      10U,                         /* u2ChannelTimeOut */
      0U                                    /* u2Dummy */
    },
    {
      2UL,                             /* u4CryIfChannelId */
      1UL,                         /* u4DequeueStop */
      CSM_CFG_QUEUE_PRIORITY_SIZE_002,                             /* u4ConfigNum */
      &Csm_Cfg_stQueuePriorityConfig_002[0],/* ptPriorityConfig */
      &Csm_Cfg_Ram_stQueueChannelData[2],    /* ptChannelData */
      10U,                         /* u2ChannelTimeOut */
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
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[1],         /* ptJobQueue */
      &SecOC_MacGenCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[2],         /* ptJobQueue */
      &SecOC_MacVerCallback,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[0],         /* ptJobQueue */
      &CsmCallback_General,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[1],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[0],         /* ptJobQueue */
      &CsmCallback_KeySetValid,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[0],         /* ptJobQueue */
      &CsmCallback_KeySetValid,           /* ptJobPrimitiveCallbackFunc */
      0U,                    /* u2QueuePriorityIndex */
      0U                                /* u2Dummy */
    },
    {
      NULL_PTR,                    /* ptJobRedirectionInfo */
      &Csm_Cfg_u4KeyConfig[0],           /* ptJobKey */
      &Csm_Cfg_stQueueConfig[0],         /* ptJobQueue */
      &CsmCallback_General,           /* ptJobPrimitiveCallbackFunc */
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
        1UL,           /* u4CryptoKeyId */
        0UL             /* u4CryptoIndex */
    },
    {
        0UL,           /* u4CryptoKeyId */
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
        5UL,            /* u4ObjectId */
        0UL             /* u4CryptoIndex */
    },
    {
        4UL,            /* u4ObjectId */
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
        Crypto_82_Hsm_ProcessJob,
        Crypto_82_Hsm_CancelJob,
        Crypto_82_Hsm_KeyElementSet,
        Crypto_82_Hsm_KeySetValid,
        Crypto_82_Hsm_KeyElementGet,
        Crypto_82_Hsm_KeyElementCopy,
        Crypto_82_Hsm_KeyElementCopyPartial,
        Crypto_82_Hsm_KeyCopy,
        Crypto_82_Hsm_RandomSeed,
        Crypto_82_Hsm_KeyGenerate,
        Crypto_82_Hsm_KeyDerive,
        Crypto_82_Hsm_KeyExchangeCalcPubVal,
        Crypto_82_Hsm_KeyExchangeCalcSecret
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
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

