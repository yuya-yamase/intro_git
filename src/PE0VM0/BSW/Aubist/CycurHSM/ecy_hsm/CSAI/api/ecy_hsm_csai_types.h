/**
 * @file
 ***********************************************************************************************
 * @brief CSAI type definitions.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * general types used within other parts of the interface.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_TYPES_H
#define ECY_HSM_CSAI_TYPES_H

/**
 * @addtogroup GROUP_CSAI_TYPES
 * @{
 */

/* *** includes *******************************************************************************/

#include "Std_Types.h"
  /* To avoid the Guam specific file includes*/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_csai_defs.h"

/* *** defines ********************************************************************************/
#define ecy_hsm_CSAI_INVALID_SESSION_HANDLE_VALUE   ((ecy_hsm_Csai_SessionHandleT)0xFFFFFFFFUL)     /**< Invalid session handle value      */
#define ecy_hsm_CSAI_VIRTUAL_SESSION_HANDLE_VALUE   ((ecy_hsm_Csai_SessionHandleT)0xFFFFFFFEUL)     /**< "Virtual" session handle value,
                                                                                                         used for HSM internal keys, which
                                                                                                         can use all keystore features, but
                                                                                                         cannot be referenced by the HOST  */
#define ecy_hsm_CSAI_INVALID_JOB_HANDLE_VALUE       ((ecy_hsm_Csai_JobHandleT)0xFFFFFFFFUL)         /**< Invalid job handle value          */
#define ecy_hsm_CSAI_INVALID_KEY_HANDLE_VALUE       ((ecy_hsm_Csai_KeyHandleT)0xFFFFFFFFUL)         /**< Invalid key handle value          */
#define ecy_hsm_CSAI_NO_KEY_HANDLE                  ((ecy_hsm_Csai_KeyHandleT)0xFFFFFFFEUL)         /**< Empty key handle value            */

/**
 * Special key handle to the silicon manufacturer defined secret key.
 * This key handle is not valid for any other function than @ref ecy_hsm_Csai_DeriveKey as
 * @c hParentKey if and only if @ref ecy_hsm_CSAI_KDF_NIST_SP800_108_AES_CMAC is specified
 * as Key derivation function.
 */

#define ecy_hsm_CSAI_SECURE_KEY_HANDLE             ((ecy_hsm_Csai_KeyHandleT)(0xFFFF0000UL))

/* *** type declarations **********************************************************************/

typedef uint32                  ecy_hsm_Csai_ErrorT;            /**< CSAI Error Return Type
                                                                     @see ecy_hsm_csai_error.h  */
typedef uint32                  ecy_hsm_Csai_HandleT;           /**< CSAI Generic Handle Type   */
typedef ecy_hsm_Csai_HandleT    ecy_hsm_Csai_SessionHandleT;    /**< CSAI Session Handle Type   */
typedef ecy_hsm_Csai_HandleT    ecy_hsm_Csai_KeyHandleT;        /**< CSAI Key Handle Type, encodes the session owning the key and
                                                       some information by which the key can be identified           */
typedef ecy_hsm_Csai_HandleT    ecy_hsm_Csai_HostKeyHandleT;    /**< CSAI Host Key Handle Type */
typedef ecy_hsm_Csai_HandleT    ecy_hsm_Csai_CertHandleT;       /**< CSAI Cert Handle Type   */
/**< @details The lower sixteen bits of the key handle hold the byte offset into the RAM keystore at which the
       key is stored.
     The upper sixteen bits holds the session index, corresponding to hSession     */
typedef ecy_hsm_Csai_HandleT    ecy_hsm_Csai_JobHandleT;        /**< CSAI Job Handle Type       */
typedef uint32                  ecy_hsm_Csai_WorkspacesMaskT;   /**< CSAI Workspace Type.
                                                                     Bit field where each bit represents a workspace.
                                                                     Example: 0x3 -> 0b11 -> Workspace 0 and 1. */
typedef uint32                  ecy_hsm_Csai_WorkspaceIdT;      /**< CSAI Workspace Type for selecting a single workspace */

/** Define CSAI interface mode definitions. */
typedef enum ecy_hsm_Csai_InterfaceModeTag
{
    ecy_hsm_CSAI_INTERFACE_MODE_SYNCHRONOUS      = 0U,             /**< The interface answers in synchronous mode */
    ecy_hsm_CSAI_INTERFACE_MODE_ASYNCHRONOUS     = 1U,             /**< The interface answers in asynchronous mode */
    ecy_hsm_CSAI_INTERFACE_MODE_QUICKROUTE       = 2U,             /**< The interface answers in synchronous mode and skips the applet manager*/
    ecy_hsm_CSAI_INTERFACE_MODE_RESERVED         = 0x7fffffffU     /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_InterfaceModeT;

/** Define CSAI hardware mode definitions. */
typedef enum ecy_hsm_Csai_HardwareModeTag
{
    /** The driver uses the CPU to read/write commands and data from/to the registers of the hardware peripheral */
    ecy_hsm_CSAI_HARDWARE_MODE_CPU = 0U,
    /** The driver configures one or more DMA channels to read/write commands and data from/to the registers of the hardware peripheral*/
    ecy_hsm_CSAI_HARDWARE_MODE_DMA,
    /** Value defined to use memory size of uint32 for enums */
    ecy_hsm_CSAI_HARDWARE_MODE_RESERVED = 0x7fffffffU
} ecy_hsm_Csai_HardwareModeT;

/** Define CSAI job priority definitions */
typedef enum ecy_hsm_Csai_JobPriorityTag
{
    ecy_hsm_CSAI_PRIO_BACKGROUND      = 0U,       /**< HSM background scheduling priority.            */
    ecy_hsm_CSAI_PRIO_LOW             = 1U,       /**< HSM low scheduling priority.                   */
    ecy_hsm_CSAI_PRIO_MEDIUM          = 2U,       /**< HSM medium scheduling priority                 */
    ecy_hsm_CSAI_PRIO_HIGH            = 3U,       /**< HSM high scheduling priority                   */
    ecy_hsm_CSAI_PRIO_SAFETY          = ecy_hsm_CSAI_PRIO_HIGH, /** @deprecated < Safety priority (legacy, same as PRIO_HIGH) */
    /* If new higher priorities are added, note that the higher priority should be defined in CSAI_PRIO_MAX_HOST_TASK */
    ecy_hsm_CSAI_PRIO_UNCHANGED       = 5U,       /**< Same priority as last operation scheduled      */
    ecy_hsm_CSAI_JOBPRIORITY_RESERVED = 0x7fffffffU     /**< Value defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_JobPriorityT;

/** The maximum valid task priority in host */
#define CSAI_PRIO_MAX_HOST_TASK     ecy_hsm_CSAI_PRIO_SAFETY

/** Structure to hold a key PIN */
typedef struct ecy_hsm_Csai_PinRefTag
{
    uint8 *pin;                     /**< UTF-8 string representing the PIN, up to max. 32 bytes */
    uint32 length;                  /**< The actual length of the PIN                           */
} ecy_hsm_Csai_PinRefT;


/* PRQA S 0750 2*/ /* Justification: See below*/
/** Union to convert between byte array and word    */
typedef union ecy_hsm_Csai_ByteWordUnionT_Tag {
    uint32 word;                /**< structure member word */
    uint8 bytes[4];             /**< structure member bytes array */
} ecy_hsm_Csai_ByteWordUnionT;

#if (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_IFX)

/* Core cache can result in overwriting host variables that happen to be located in the same cache
 * block as variables written by core. Therefore variables written by core must be in dedicated
 * cache blocks that are aligned and padded to complete cache blocks */
#define ecy_hsm_CSAI_CACHE_BLOCK_SIZE_BYTES         (16u)   /**< Defined by cache HW, must be a power of 2 */

/* Size of a cache line of the host core cache */
#define ecy_hsm_CSAI_HOST_CACHE_BLOCK_SIZE_BYTES    (32u)   /**< Defined by cache HW, must be a power of 2 */

/* Attribute positions a variable (generally one that can be written by core) at the start of a cache block
 * (i.e. no need to worry about  host variables located before this variable in RAM).
 * However, if the variable length is not a multiple of ecy_hsm_CSAI_CACHE_BLOCK_SIZE_BYTES then need to consider what variables
 * may share the last cache block and which are at risk of being overwritten by an old value when the cache is cleaned.
 */
#if defined(GUAM)
#define ecy_hsm_CSAI_HSM_CACHE_ALIGN_ATTR           __attribute__((aligned(ecy_hsm_CSAI_CACHE_BLOCK_SIZE_BYTES)))
#define ecy_hsm_CSAI_HOST_CACHE_ALIGN_ATTR          __attribute__((aligned(ecy_hsm_CSAI_HOST_CACHE_BLOCK_SIZE_BYTES)))
#endif /* defined(GUAM) */

/** Pad uint8 array that has been aligned by ecy_hsm_CSAI_HSM_CACHE_ALIGN_ATTR to fill an integer number of cache blocks.
 *  This prevents data at the end of a block that has been recently written by host from being restored
 *  to an earlier (invalid) value when the hsm cache is cleaned/flushed */
#define ecy_hsm_CSAI_HSM_CACHE_LENGTH_PAD_U8(x)     (((x) + (ecy_hsm_CSAI_CACHE_BLOCK_SIZE_BYTES-1u)) & ~(ecy_hsm_CSAI_CACHE_BLOCK_SIZE_BYTES-1u))

/** Adjust a supplied length to be multiple of the host cache line length */
#define ecy_hsm_CSAI_HOST_CACHE_LENGTH_PAD_U8(x)    (((x) + (ecy_hsm_CSAI_HOST_CACHE_BLOCK_SIZE_BYTES-1u)) & ~(ecy_hsm_CSAI_HOST_CACHE_BLOCK_SIZE_BYTES-1u))

#else /* #if (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_IFX) */

#define ecy_hsm_CSAI_CACHE_BLOCK_SIZE_BYTES         (0u)    /* Only TC2x includes the host-core cache */
#define ecy_hsm_CSAI_HOST_CACHE_BLOCK_SIZE_BYTES    (0u)    /* Only TC2x includes the host-core cache */

#if defined(GUAM)
#define ecy_hsm_CSAI_HSM_CACHE_ALIGN_ATTR           __attribute__((aligned(4)))
#define ecy_hsm_CSAI_HOST_CACHE_ALIGN_ATTR          __attribute__((aligned(4)))
#endif /* defined(GUAM) */

#define ecy_hsm_CSAI_HSM_CACHE_BYTE_LENGTH_PAD(x)   (x)
#define ecy_hsm_CSAI_HOST_CACHE_BYTE_LENGTH_PAD(x)  (x)

#endif /* #if (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_IFX) */

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * @}
 */

#endif /* Multiple inclusion lock  */
