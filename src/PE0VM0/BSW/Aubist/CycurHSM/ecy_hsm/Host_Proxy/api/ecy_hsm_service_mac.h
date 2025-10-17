/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Message Authentication Code generation and verification.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for generating and verifying Message Authentication Codes.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2022, all rights reserved.
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_SERVICE_MAC_H
#define ECY_HSM_SERVICE_MAC_H


/**
 * @addtogroup GROUP_CSAI_MAC
 * @{
 */

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai_mac.h"
#include "ecy_hsm_csai_mac_extended.h"
#include "ecy_hsm_service_basic.h"

/* *** defines ********************************************************************************/
/**
* @brief Upper limit for maximum block size "quick route"
*
*/
#define ecy_hsm_MAX_QUICK_ROUTE_BYTES_UPPER_LIMIT           (512U)

/* In case customer configure ecy_hsm_MAX_QUICK_ROUTE_BYTES higher than the upper limit prompt error */
#if (ecy_hsm_MAX_QUICK_ROUTE_BYTES > ecy_hsm_MAX_QUICK_ROUTE_BYTES_UPPER_LIMIT)
#error "ecy_hsm_MAX_QUICK_ROUTE_BYTES exceededs the upper limit(512 bytes)"
#endif

/* In case customer configure ecy_hsm_MAX_QUICK_ROUTE_BYTES to 0 prompt error */
#if (ecy_hsm_MAX_QUICK_ROUTE_BYTES == 0U)
#error "0 is not a valid value for ecy_hsm_MAX_QUICK_ROUTE_BYTES. Please set ecy_hsm_QUICK_ROUTE to DISABLED if you want to disable the quick route."
#endif

#define ecy_hsm_MAX_BULK_MODE_MESSAGE_LENGTH                (64U)     /**< Maximum length of the bulk mode message in bytes */

#if defined(GUAM)
#if (ECY_HSM_VMS_FS_APPLET_MAC_VERIFY_MIN_MACLENGTH_24BIT == ENABLED)
#define ecy_hsm_MIN_VERIFY_MAC_BIT_LENGTH                   (24U)     /**< Minimum length of the macBitLength parameter for MAC verification (mitigate "abuse verify only key for mac generation" vulnerability) */
#else /* #if (ECY_HSM_VMS_FS_APPLET_MAC_VERIFY_MIN_MACLENGTH_24BIT == ENABLED) */
#define ecy_hsm_MIN_VERIFY_MAC_BIT_LENGTH                   (27U)     /**< Minimum length of the macBitLength parameter for MAC verification (mitigate "abuse verify only key for mac generation" vulnerability) */
#endif  /* #if (ECY_HSM_VMS_FS_APPLET_MAC_VERIFY_MIN_MACLENGTH_24BIT == ENABLED) */
/**
 * @deprecated by ecy_hsm_MIN_VERIFY_MAC_BIT_LENGTH
 */
#define MIN_VERIFY_MAC_BIT_LENGTH                   ecy_hsm_MIN_VERIFY_MAC_BIT_LENGTH
#endif


/** Maximum bit length of calculated MAC with SipHash 2-4 */
#define ecy_hsm_SIP_HASH_24_MAX_MAC_SIZE_BITS   64U
/** Maximum byte length of calculated MAC with SipHash 2-4 */
#define ecy_hsm_SIP_HASH_24_MAX_MAC_SIZE_BYTES  (ecy_hsm_SIP_HASH_24_MAX_MAC_SIZE_BITS / 8UL)
/* *********** Deprecated Macro definitions ***************/
/**
 * @deprecated by ecy_hsm_MAX_BULK_MODE_MESSAGE_LENGTH
 */
#define MAX_BULK_MODE_MESSAGE_LENGTH ecy_hsm_MAX_BULK_MODE_MESSAGE_LENGTH
/**
 * @deprecated by ecy_hsm_MAX_QUICK_ROUTE_BYTES_UPPER_LIMIT
 */
#define MAX_QUICK_ROUTE_BYTES_UPPER_LIMIT ecy_hsm_MAX_QUICK_ROUTE_BYTES_UPPER_LIMIT
/* *** type declarations **********************************************************************/

/** Structure for the data passed to a MACGenerate Fast call operation   */
typedef struct ecy_hsm_MacGenerateParamTag {
    ecy_hsm_Csai_MACAlgorithmT  algorithm;         /**< Algorithm for MAC                                                                      */
    ecy_hsm_Csai_KeyHandleT     hKey;              /**< Handle to a key available in the HSM's session context to use for encryption           */
    const uint8*                msg;               /**< Pointer to  data block for operation                                                   */
    uint32                      msgLength;         /**< Length of data block                                                                   */
    uint8*                      pMac;              /**< Pointer to space where the HSM can store the MAC                                       */
    uint32                      macBitLength;      /**< Length of MAC                                                                          */
    uint32*                     pMacCount;         /**< Pointer to buffer for the number of bytes written to MAC buffer                        */
    uint32                      truncationAllowed; /**< Set TRUE to permit the MAC to be truncated to fit within MacLength bytes, if FALSE and
                                                 MacLength bytes is insufficient, ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL will be returned    */
} ecy_hsm_MacGenerateParamT;

/** Structure for the data passed to a MACVerifyStart operation     */
typedef struct ecy_hsm_MacVerifyStartParamTag {
    ecy_hsm_Csai_MACAlgorithmT algorithm;  /**< Algorithm for MAC                                                                      */
    ecy_hsm_Csai_KeyHandleT    hKey;       /**< Handle to a key available in the HSM's session context to use for encryption           */
    const uint8*               msg;        /**< Pointer to first (or only) data block for operation                                    */
    uint32                     msgLength;  /**< Length of data block                                                                   */
} ecy_hsm_MacVerifyStartParamT;

/** Structure for the data passed to a MACVerifyUpdate operation   */
typedef struct ecy_hsm_MacVerifyUpdateParamTag {
    const uint8* chunk;                     /**< Pointer to next data block for operation               */
    uint32 length;                          /**< Length of data block                                   */
} ecy_hsm_MacVerifyUpdateParamT;

/** Structure for the data passed to a MACVerifyFinish operation   */
typedef struct ecy_hsm_MacVerifyFinishParamTag {
    const uint8* pExpectedMac;              /**< Pointer to MAC to be verified                          */
    uint32 macBitLength;                    /**< Length of MAC                                          */
    uint32* pResultFlag;                    /**< MAC result Flag                                        */
} ecy_hsm_MacVerifyFinishParamT;

/** Structure for the data passed to a MACVerify operation   */
typedef struct ecy_hsm_MacVerifyParamTag {
    ecy_hsm_Csai_MACAlgorithmT algorithm;   /**< Algorithm for MAC                                                              */
    ecy_hsm_Csai_KeyHandleT hKey;           /**< Handle to a key available in the HSM's session context to use for encryption   */
    const uint8* msg;                       /**< Pointer to first (or only) data block for operation                            */
    uint32 msgLength;                       /**< Length of data block                                                           */
    const uint8* pExpectedMac;              /**< Pointer to MAC to be verified                                                  */
    uint32 macBitLength;                    /**< Length for MAC comparison in bits                                              */
    uint32* pResultFlag;                    /**< MAC result Flag                                                                */
    uint8* safetyMac;                       /**< @deprecated safetyMac is a leftover from a previous "safety path",
                                             *    that was removed. It is only kept for backwards compatibility.                */
} ecy_hsm_MacVerifyParamT;

/** Structure for the data passed to a MAC Verify or Generate Quick call operation (where the operation
    is done within the ISR by the HSM) */
typedef struct ecy_hsm_MacQuickParamTag {
    ecy_hsm_Csai_KeyHandleT hKey;           /**< Handle to a key available in the HSM's session context to use for encryption   */
    const uint8* msg;                       /**< Pointer to data block for operation                                            */
    uint32 msgLength;                       /**< Length of data block                                                           */
    const uint8* pExpectedMac;              /**< Pointer to MAC to be verified                                                  */
    uint32 macBitLength;                    /**< Length for MAC comparison in bits                                              */
    uint8* safetyMac;                       /**< @deprecated safetyMac is a leftover from a previous "safety path",
                                             *    that was removed. It is only kept for backwards compatibility.                */
} ecy_hsm_MacQuickParamT;

/**
 * Copy @ref HSM_MacQuickParamTag
 * On PowerPC targets, copying must be done field by field, otherwise GHS compiler uses memmove() to copy, which is slower
 *
 * @param[out]   _dst    @ref HSM_MacQuickParamTag destination object
 * @param[in]    _pSrc   Pointer to @ref HSM_MacQuickParamTag source object
 */
#if (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_POWER)
# define ecy_hsm_MAC_COPY_QUICK_PARAM(_dst, _pSrc)                                                                                                   \
     do                                                                                                                                              \
     {                                                                                                                                               \
         (_dst).hKey         = (_pSrc)->hKey;                                                                                                        \
         (_dst).msg          = (_pSrc)->msg;                                                                                                         \
         (_dst).msgLength    = (_pSrc)->msgLength;                                                                                                   \
         (_dst).pExpectedMac = (_pSrc)->pExpectedMac;                                                                                                \
         (_dst).macBitLength = (_pSrc)->macBitLength;                                                                                                \
         (_dst).safetyMac    = (_pSrc)->safetyMac;                                                                                                   \
     }                                                                                                                                               \
     while (0)
#else
# define ecy_hsm_MAC_COPY_QUICK_PARAM(_dst, _pSrc)                                                                                                   \
    do                                                                                                                                               \
    {                                                                                                                                                \
        (_dst) = *(_pSrc);                                                                                                                           \
    } while (0)
#endif

/** Structure for the data passed as part of a bulk safe MAC verify operation */
typedef struct ecy_hsm_BulkMacVerifyParamTag
{
    const ecy_hsm_Csai_BulkMacControlVerifyJobT* pTable; /**< Pointer to table of jobs, the table is not actually of this type because the length of
                                                            the MAC buffer is fixed by macByteSize */
    uint32 numOfEntries; /**< Number of jobs in the tables                                                                          */
    uint32 macByteSize;  /**< Length in bytes of of the receivedMac field of the job table element, will be a multiple of four      */
    uint8* data1;        /**< Array of first part of data for MACing (array in numOfEntries long)                                   */
    uint32 data1Size;    /**< Length in bytes of data1 array element length (should be a multiple of four)                          */
    uint8* data2;        /**< Array of second part of data for MACing (array in numOfEntries long)                                  */
    uint32 data2Size;    /**< Length in bytes of data2 array element length (should be a multiple of four)                          */

} ecy_hsm_BulkMacVerifyParamT;

/** Structure for the data passed as part of a bulk MAC generate operation */
typedef struct ecy_hsm_BulkMacGenerateParamTag
{
    const ecy_hsm_Csai_BulkMacControlGenerateJobT* pTable; /**< Pointer to table of jobs, the table is not actually of this type because the length of
                                                              the MAC buffer is fixed by macByteSize */
    uint32 numOfEntries; /**< Number of jobs in the tables                                                                          */
    uint32 macByteSize;  /**< Length in bytes of of the receivedMac field of the job table element, will be a multiple of four      */
    uint8* data1;        /**< Array of first part of data for MACing (array in numOfEntries long)                                   */
    uint32 data1Size;    /**< Length in bytes of data1 array element length (should be a multiple of four)                          */
    uint8* data2;        /**< Array of second part of data for MACing (array in numOfEntries long)                                  */
    uint32 data2Size;    /**< Length in bytes of data2 array element length (should be a multiple of four)                          */
} ecy_hsm_BulkMacGenerateParamT;

/** Structure for the data passed as part of a bulk safe MAC fast verify operation */
typedef struct ecy_hsm_BulkMacFastVerParamTag {
    ecy_hsm_Csai_BulkMacFastVerJob* pTable; /**< Pointer to table of jobs, the table is not actually of this type because the length of
                                                 the MAC buffer is fixed by macByteSize                                                 */
    uint32 numOfEntries;                    /**< Number of jobs in the tables                                                           */
} ecy_hsm_BulkMacFastVerParamT;

/** Structure for the data passed as part of a bulk MAC fast generate operation */
typedef struct ecy_hsm_BulkMacFastGenParamTag {
    ecy_hsm_Csai_BulkMacFastGenJob* pTable; /**< Pointer to table of jobs, the table is not actually of this type because the length of
                                                 the MAC buffer is fixed by macByteSize                                                 */
    uint32 numOfEntries;                    /**< Number of jobs in the table                                                        */
} ecy_hsm_BulkMacFastGenParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_MacGenerateParamTag
 */
#define HSM_MacGenerateParamTag ecy_hsm_MacGenerateParamTag
/**
 * @deprecated by ecy_hsm_MacGenerateParamT
 */
#define HSM_MacGenerateParamT ecy_hsm_MacGenerateParamT
/**
 * @deprecated by ecy_hsm_MacVerifyStartParamTag
 */
#define HSM_MacVerifyStartParamTag ecy_hsm_MacVerifyStartParamTag
/**
 * @deprecated by ecy_hsm_MacVerifyStartParamT
 */
#define HSM_MacVerifyStartParamT ecy_hsm_MacVerifyStartParamT
/**
 * @deprecated by ecy_hsm_MacVerifyUpdateParamTag
 */
#define HSM_MacVerifyUpdateParamTag ecy_hsm_MacVerifyUpdateParamTag
/**
 * @deprecated by ecy_hsm_MacVerifyUpdateParamT
 */
#define HSM_MacVerifyUpdateParamT ecy_hsm_MacVerifyUpdateParamT
/**
 * @deprecated by ecy_hsm_MacVerifyFinishParamTag
 */
#define HSM_MacVerifyFinishParamTag ecy_hsm_MacVerifyFinishParamTag
/**
 * @deprecated by ecy_hsm_MacVerifyFinishParamT
 */
#define HSM_MacVerifyFinishParamT ecy_hsm_MacVerifyFinishParamT
/**
 * @deprecated by ecy_hsm_MacVerifyParamTag
 */
#define HSM_MacVerifyParamTag ecy_hsm_MacVerifyParamTag
/**
 * @deprecated by ecy_hsm_MacVerifyParamT
 */
#define HSM_MacVerifyParamT ecy_hsm_MacVerifyParamT
/**
 * @deprecated by ecy_hsm_MacQuickParamTag
 */
#define HSM_MacQuickParamTag ecy_hsm_MacQuickParamTag
/**
 * @deprecated by ecy_hsm_MacQuickParamT
 */
#define HSM_MacQuickParamT ecy_hsm_MacQuickParamT
/**
 * @deprecated by ecy_hsm_BulkMacVerifyParamTag
 */
#define HSM_BulkMacVerifyParamTag ecy_hsm_BulkMacVerifyParamTag
/**
 * @deprecated by ecy_hsm_BulkMacVerifyParamT
 */
#define HSM_BulkMacVerifyParamT ecy_hsm_BulkMacVerifyParamT
/**
 * @deprecated by ecy_hsm_BulkMacGenerateParamTag
 */
#define HSM_BulkMacGenerateParamTag ecy_hsm_BulkMacGenerateParamTag
/**
 * @deprecated by ecy_hsm_BulkMacGenerateParamT
 */
#define HSM_BulkMacGenerateParamT ecy_hsm_BulkMacGenerateParamT
/**
 * @deprecated by ecy_hsm_BulkMacFastVerParamTag
 */
#define HSM_BulkMacFastVerParamTag ecy_hsm_BulkMacFastVerParamTag
/**
 * @deprecated by ecy_hsm_BulkMacFastVerParamT
 */
#define HSM_BulkMacFastVerParamT ecy_hsm_BulkMacFastVerParamT
/**
 * @deprecated by ecy_hsm_BulkMacFastGenParamTag
 */
#define HSM_BulkMacFastGenParamTag ecy_hsm_BulkMacFastGenParamTag
/**
 * @deprecated by ecy_hsm_BulkMacFastGenParamT
 */
#define HSM_BulkMacFastGenParamT ecy_hsm_BulkMacFastGenParamT
/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* *INDENT-OFF* */
#ifdef __cplusplus
    } /* extern "C" */
#endif
/* *INDENT-ON* */

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
