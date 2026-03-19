/**
 * @file ecy_hsm_host_storage.c
 ***********************************************************************************************
 * @brief Function and data structures for managing host storage for CycurHSM
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2019, all rights reserved
 **********************************************************************************************/

/* To avoid the Guam specific file includes*/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif

#if (ecy_hsm_HOST_STORAGE == ENABLED)
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_host_storage.h"
#include "ecy_hsm_host_storage_internal.h"
#include "ecy_hsm_host_storage_config.h"
#include "ecy_hsm_basicsrvs.h"

/* *** defines ********************************************************************************/
#if defined(GUAM)
    /** Helper macro that allows a function to have external linkage */
    #define HOST_STORAGE_PRIVATE
#else
    /** Helper macro that allows a function to have internal linkage */
    #define HOST_STORAGE_PRIVATE static
#endif

/** Reset value for the sync update counters */
#define SYNC_RESET_VALUE                    (0u)

/** Value used to mark cache contents as being empty */
#define CACHE_ELEMENT_EMPTY                 (0u)

/** Value to consider a section as initialized */
#define HOST_STORAGE_SECTION_INIT_TRUE      (1u)

/** Value to consider a section as NOT initialized */
#define HOST_STORAGE_SECTION_INIT_FALSE     (0u)

/* *** local variables ************************************************************************/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/** Structure containing host storage callouts */
static HSM_HostStorageCalloutT HostStorageCallout = { NULL_PTR, NULL_PTR };


#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_8
#include "ecy_hsm_MemMap.h"

/** The initialization status of each cache section */
/* PRQA S 1504 1 */ /* <Justification: object must have external linkage for testing (GUAM only) */
HOST_STORAGE_PRIVATE uint8 HSM_HostStorage_sectionInitStatus[HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS];

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_8
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_8
#include "ecy_hsm_MemMap.h"
/**
 * Variable tracking that initialization was already triggered, although it may not have been completed yet.
 *
 * @note This variable is used to help protecting API calls when the module was not yet initialized, which could
 *       cause non-initialized pointers being used
 */
/* PRQA S 1504 1 */ /* <Justification: object must have external linkage for testing (GUAM only) */
HOST_STORAGE_PRIVATE boolean HSM_HostStorage_InitTriggered = FALSE;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_8
#include "ecy_hsm_MemMap.h"

/** Place the host storage cache elements that require a special alignment to cope with CPU cache constraints into a
 * dedicated memory area that ensures those constraints are adhered to */
/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMHOSTSTORAGECACHE_8
#include "ecy_hsm_MemMap.h"

/**
 * @brief The host side shared RAM buffer for the host storage cache
 *
 * @remarks To ensure the host side cache buffer is not corrupted due the CPU memory cache operations that may happen
 *          unpredictably, we must ensure that no other data will occupy a cache line linked with this buffer.
 *          Therefore, ensure size is properly padded.
 */
/* PRQA S 3218 1 */ /* <Justification: Must be placed in separate section for cache line alignment */
static uint8 HSM_HostStorage_CacheBuffer[ ecy_hsm_CSAI_HOST_CACHE_LENGTH_PAD_U8( HSM_HOST_STORAGE_CACHE_SIZE ) ];

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMHOSTSTORAGECACHE_8
#include "ecy_hsm_MemMap.h"

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMHOSTSTORAGECACHE_16
#include "ecy_hsm_MemMap.h"

/**
 * @brief Array to support synchronization of cache contents by tracking an update counter last processed for a given
 *        section
 *
 * @remarks To ensure the host side cache buffer is not corrupted due the CPU memory cache operations that may happen
 *          unpredictably, we must ensure that no other data will occupy a cache line linked with this buffer.
 *          Therefore, ensure size is properly padded.
 */
/* PRQA S 3218 1 */ /* <Justification: Must be placed in separate section for cache line alignment */
static uint16 HSM_HostStorage_Sync_PreviousCounter[ ecy_hsm_CSAI_HOST_CACHE_LENGTH_PAD_U8( HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS ) ];
/**
 * @brief Array to support synchronization of cache contents by tracking an update counter that is currently applicable
 *        for a given section
 *
 * @remarks To ensure the host side cache buffer is not corrupted due the CPU memory cache operations that may happen
 *          unpredictably, we must ensure that no other data will occupy a cache line linked with this buffer.
 *          Therefore, ensure size is properly padded.
 */
/* PRQA S 3218 1 */ /* <Justification: Must be placed in separate section for cache line alignment */
static uint16 HSM_HostStorage_Sync_CurrentCounter[ ecy_hsm_CSAI_HOST_CACHE_LENGTH_PAD_U8( HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS ) ];

/** Stop placement of host storage cache elements into a dedicated memory region with special alignment requirements */
/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMHOSTSTORAGECACHE_16
#include "ecy_hsm_MemMap.h"

/** Place host storage related elements into a dedicated memory region shared between host and hsm */
/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief Structure containing host storage cache and relevant properties shared between host and hsm
 *
 * @remarks This structure does not have any further special alignment constraints (except ones applicable by
 *          default at system level). Consequently, it does not need to go into the special host storage cache
 *          memory area as other elements. However, if it is placed there, we need to ensure that it won't
 *          cause misalignments of other data
 */
static volatile HSM_HostStorageCacheT HSM_HostStorageCache;

/** Stop placing host storage related elements into a dedicated memory region shared between host and hsm */
/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/* *** function prototypes ********************************************************************/
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * @brief Reset the synchronisation counters to SYNC_RESET_VALUE for all sections.
 *
 * @note: Reset behaviour cannot be guaranteed under asynchronous access conditions; Hence, this
 * function should not be called when the sync counters are in active use by the HSM.
 *
 * @note: This function requires that the array length for the current and previous counter(s)
 * within type @ref HSM_HostStorageSyncT are equal.
 *
 * @internal
 * Link to detailed description: @ref host_storage_dd_ecy_hsm_HostStorage_Sync_Reset
 * @endinternal
 *
 * @pre The sync control pointers must have been initialized to be a valid pointer (NOT NULL_PTR)
 *      prior to calling this function.
 */
static void ecy_hsm_HostStorage_Sync_Reset(void);

/**
 * @brief Detect if a section within the host storage cache has been updated.
 *
 * @internal
 * Link to detailed description: @ref host_storage_dd_ecy_hsm_HostStorage_Sync_DetectUpdate
 * @endinternal
 *
 * @param       section     Section index to checked for updates.
 *
 * @return      boolean     Section update status
 * @retval      TRUE        Section update detected
 * @retval      FALSE       Section update not detected
 *
 * @pre The section parameter must be a valid index within the sync counter array bounds.
 * @pre The sync control pointers must have been initialized to be a valid pointer (NOT NULL_PTR)
 *      prior to calling this function.
 */
static boolean ecy_hsm_HostStorage_Sync_DetectUpdate(uint32 section);

/**
 * @brief Check if a given section number is within the valid range.
 *
 * @param[in]   section     Section index to check.
 *
 * @return      boolean     Status indicating if section is in range or out of range.
 * @retval      TRUE        Section is in the valid range.
 * @retval      FALSE       Section is NOT in the valid range.
 */
static INLINE boolean ecy_hsm_HostStorage_IsSectionInRange(uint32 section);

/* *** public implementation  *****************************************************************/

/* [$Satisfies $DD 1233] */
boolean ecy_hsm_HostStorage_IsInitialized(void)
{
    boolean isInitialized = TRUE;
    uint32 section;

    if ( FALSE == HSM_HostStorage_InitTriggered )
    {
        isInitialized = FALSE;
    }
    else
    {
        for (section = 0u; section < HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS; section++)
        {
            if (HOST_STORAGE_SECTION_INIT_FALSE == HSM_HostStorage_sectionInitStatus[section])
            {
                isInitialized = FALSE;
                break;
            }
        }
    }

    return isInitialized;
}

/* [$Satisfies $DD 1234] */
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_Host_Storage */ /* Justification: Public API function */
ecy_hsm_Csai_ErrorT ecy_hsm_HostStorage_Init(ecy_hsm_pFunctionInitSectionT    pFunctionInitSection,
                                             ecy_hsm_pFunctionPersistSectionT pFunctionPersistSection)
{
    ecy_hsm_Csai_ErrorT errorCode;

    if( TRUE == HSM_HostStorage_InitTriggered )
    {
        /* Already went through the initialization procedure */
        errorCode = ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID;
    }
    else if( (NULL_PTR == pFunctionInitSection) || (NULL_PTR == pFunctionPersistSection) )
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }
    else
    {
        /* init default cache parameters */
        HSM_HostStorageCache.pImage = &( HSM_HostStorage_CacheBuffer[0] );
        HSM_HostStorageCache.sync.pPreviousCounter = &( HSM_HostStorage_Sync_PreviousCounter[0] );
        HSM_HostStorageCache.sync.pCurrentCounter = &( HSM_HostStorage_Sync_CurrentCounter[0] );
        HSM_HostStorageCache.numSections = HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS;
        HSM_HostStorageCache.numBytesPerSection = HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION;

        /* reset sync to default start state */
        ecy_hsm_HostStorage_Sync_Reset();

        /* init callouts */
        HostStorageCallout.pFunctionInitSection = pFunctionInitSection;
        HostStorageCallout.pFunctionPersistSection = pFunctionPersistSection;

        /* Track that the initialization was started even through it may not be fully complete yet as the initialization
         * of the different sections in cache is still pending. This allows key functions
         * (@ref ecy_hsm_HostStorage_InitSection()) to complete the initialization process asynchronously, if required */
        HSM_HostStorage_InitTriggered = TRUE;

        /* sequentially request the initialization of all sections */
        uint32 currentSection;
        for(currentSection = 0u; currentSection < HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS; currentSection++)
        {
            HSM_HostStorage_sectionInitStatus[currentSection] = HOST_STORAGE_SECTION_INIT_FALSE;
            HostStorageCallout.pFunctionInitSection(currentSection);
        }

        errorCode = ecy_hsm_CSAI_SUCCESS;
    }

    return errorCode;
}

/* [$Satisfies $DD 1235] */
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_Host_Storage */ /* Justification: Public API function */
ecy_hsm_Csai_ErrorT ecy_hsm_HostStorage_InitSection(uint32 section, const uint8 * pBuffer, uint32 bufferLength)
{
    ecy_hsm_Csai_ErrorT errorCode;

    if( FALSE == HSM_HostStorage_InitTriggered )
    {
        /* Initialization of section not possible */
        errorCode = ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID;
    }
    else if ( ( FALSE == ecy_hsm_HostStorage_IsSectionInRange( section ) ) ||
              ( (NULL_PTR != pBuffer) && (bufferLength != HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION) ) )
    {
        /* Section out of range / provided size not supported */
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else if ( HOST_STORAGE_SECTION_INIT_TRUE == HSM_HostStorage_sectionInitStatus[section] )
    {
        /* Don't allow initializing an already initialized section again */
        errorCode = ecy_hsm_CSAI_ERR_HOST_STORAGE_ALREADY_INITIALIZED;
    }
    else
    {
        uint32 cacheOffset = section * HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION;

        /* Cache is divided into multiple sections of the same size per design, which is true also for the last one */
        uint32 sectionLength = HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION;

        if ( NULL_PTR != pBuffer )
        {
            /* Section data is available. Update our host storage cache */
            (void)ecy_memcpy( &( HSM_HostStorageCache.pImage[cacheOffset] ), pBuffer, sectionLength);
        }
        else
        {
            /* Section data is NOT available. Consider host storage cache section empty */
            (void)ecy_memset( &( HSM_HostStorageCache.pImage[cacheOffset] ), CACHE_ELEMENT_EMPTY, sectionLength );
        }

        /* Initialization of section is considered now complete */
        HSM_HostStorage_sectionInitStatus[section] = HOST_STORAGE_SECTION_INIT_TRUE;

        errorCode = ecy_hsm_CSAI_SUCCESS;
    }

    return errorCode;
}

/* [$Satisfies $DD 1237] */
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_Host_Storage */ /* Justification: Public API function */
ecy_hsm_Csai_ErrorT ecy_hsm_HostStorage_ReadSection(uint32 section, uint8 * pBuffer, uint32 bufferLength, uint32 * pSectionLength)
{
    ecy_hsm_Csai_ErrorT errorCode;

    if ( FALSE == ecy_hsm_HostStorage_IsInitialized() )
    {
        errorCode = ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID;
    }
    else if ( ( FALSE == ecy_hsm_HostStorage_IsSectionInRange( section ) ) || ( NULL_PTR == pBuffer ) )
    {
        errorCode = ecy_hsm_CSAI_ERR_INVALID_PARAM;
    }
    else if ( bufferLength < HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION )
    {
        errorCode = ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL;
    }
    else
    {
        uint32 cacheOffset = section * HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION;

        /* Cache is divided into multiple sections of the same size as per design, which holds also true
         * for the last section, so copy is safe */
        (void)ecy_memcpy( pBuffer, &( HSM_HostStorageCache.pImage[cacheOffset] ), HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION );

        /* Return the read section length to the caller if requested by passing a valid pSectionLength pointer */
        if ( NULL_PTR != pSectionLength )
        {
            *pSectionLength = HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION;
        }

        errorCode = ecy_hsm_CSAI_SUCCESS;
    }

    return errorCode;
}

/* [$Satisfies $DD 1236] */
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_Host_Storage */ /* Justification: Public API function */
ecy_hsm_Csai_ErrorT ecy_hsm_HostStorage_Main(void)
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;

    if (FALSE == ecy_hsm_HostStorage_IsInitialized())
    {
        errorCode = ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID;
    }
    else
    {
        uint32 section;

        for (section = 0u; section < HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS; ++section)
        {
            if ( TRUE == ecy_hsm_HostStorage_Sync_DetectUpdate(section) )
            {
                HostStorageCallout.pFunctionPersistSection(section);
            }
        }
    }

    return errorCode;
}

/* [$Satisfies $DD 1596] */
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1_1503_Host_Storage */ /* Justification: Public API function */
ecy_hsm_Csai_ErrorT ecy_hsm_HostStorage_ConfigureCallouts(ecy_hsm_pFunctionInitSectionT    pFunctionInitSection,
                                                          ecy_hsm_pFunctionPersistSectionT pFunctionPersistSection)
{
    ecy_hsm_Csai_ErrorT errorCode;

    if( (NULL_PTR == pFunctionInitSection) || (NULL_PTR == pFunctionPersistSection) )
    {
        errorCode = ecy_hsm_CSAI_ERR_NULL_CALLOUT;
    }
    else
    {
        /* configure callouts */
        HostStorageCallout.pFunctionInitSection = pFunctionInitSection;
        HostStorageCallout.pFunctionPersistSection = pFunctionPersistSection;

        errorCode = ecy_hsm_CSAI_SUCCESS;
    }

    return errorCode;
}

volatile HSM_HostStorageCacheT* ecy_hsm_HostStorage_GetCachePtr(void)
{
    return &HSM_HostStorageCache;
}

/* *** private implementation  ****************************************************************/

/* [$Satisfies $DD 1239] */
static void ecy_hsm_HostStorage_Sync_Reset(void)
{
    uint32 section;
    for(section = 0u; section < HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS; section++)
    {
        /* set current and previous counters for the given section to SYNC_RESET_VALUE */
        HSM_HostStorageCache.sync.pCurrentCounter[section] = SYNC_RESET_VALUE;
        HSM_HostStorageCache.sync.pPreviousCounter[section] = SYNC_RESET_VALUE;
    }
}

/* [$Satisfies $DD 1238] */
static boolean ecy_hsm_HostStorage_Sync_DetectUpdate(uint32 section)
{
    boolean status = FALSE;

    /* get counter values prior to comparison (in case counter is updated during host processing) */
    uint16 currentCounter  = HSM_HostStorageCache.sync.pCurrentCounter[section];
    uint16 previousCounter = HSM_HostStorageCache.sync.pPreviousCounter[section];

    if(currentCounter != previousCounter)
    {
        /* update detected, so set previous counter to prevent repeated detections */
        HSM_HostStorageCache.sync.pPreviousCounter[section] = currentCounter;
        status = TRUE;
    }

    return status;
}


static INLINE boolean ecy_hsm_HostStorage_IsSectionInRange(uint32 section)
{
    return ( section < HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS ) ? TRUE : FALSE;
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

#endif /* #if (ecy_hsm_HOST_STORAGE == ENABLED) */
