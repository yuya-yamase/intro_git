/**
 * @file
 ***********************************************************************************************
 * @brief MAC generation applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_SECFLASH_H
#define ECY_HSM_APPLET_SECFLASH_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai_secflash.h"

/**
 * @addtogroup APPLET_IMPL
 * @{
 */

/*
**********************************************************************************************************************
* Type definitions
**********************************************************************************************************************
*/
/**
 * @brief Secure flashing modes
 */
typedef enum ecy_hsm_Applet_SecFlashModeTag
{
    ecy_hsm_APPLET_SECFLASH_MODE_HOSTPROG,    /**< Host programming mode */
    ecy_hsm_APPLET_SECFLASH_MODE_HSMREPROG,   /**< HSM reprogramming mode */
    ecy_hsm_APPLET_SECFLASH_MODE_HSMSYNCBANK, /**< HSM synchronize flash banks mode */
    ecy_hsm_APPLET_SECFLASH_MODE_HSMDUALBANK, /**< HSM update with automated synchronize flash banks mode */
    ecy_hsm_APPLET_SECFLASH_MODE_HSMSWAPBANK, /**< HSM swap flash banks mode */
} ecy_hsm_Applet_SecFlashModeT;

/**
 * @brief Possible states for secure flashing applet
 *
 * @details
 * @section APPLET_SECFLASH secure flash programming applet
 *
 * @subsection APPLET_SECFLASH_NOHEADER Secure flash programming - default mode
 * @startuml "State diagram of applet: Secure flash programming"
 *
 * state "ecy_hsm_APPLET_SECFLASH_STATE_INIT_E" as INIT : Initialize buffers, hash & MAC calculation ...
 * state "ecy_hsm_APPLET_SECFLASH_STATE_UPDATE_E" as UPDATE : Update hash & MAC calculations
 * state "ecy_hsm_APPLET_SECFLASH_STATE_FINAL_E" as FINAL : finish signature verification, write CMAC
 * ' state "APPLET_SECFLASH_STATE_SETBOOTIDS_E" as BOOTIDS : Set ID's for secure boot
 * state "ecy_hsm_APPLET_SECFLASH_STATE_CANCEL_E" as CANCEL : Cancel current operation
 *
 * [*] --> INIT : _Init
 * INIT --> UPDATE : _Update
 * INIT --> CANCEL : _Cancel
 * ' INIT --> BOOTIDS : _SetBootIds
 * UPDATE --> INIT : _Init
 * UPDATE --> UPDATE : _Update
 * ' UPDATE --> BOOTIDS : _SetBootIds
 * UPDATE --> FINAL : _Finalize
 * UPDATE --> CANCEL : _Cancel
 * ' BOOTIDS --> UPDATE : _Update
 * ' BOOTIDS --> FINAL : _Finalize
 * CANCEL --> [*]
 * FINAL --> [*]
 *
 * @enduml
 *
 * @internal
 * @subsection APPLET_SECFLASH_SIGNED_HEADER Secure flash programming - Verification using a signed header
 * An alternate process of re-programming HSM, using the verification header has a parallel state machine
 * @startuml "State diagram of applet: Secure flash programming with a Signed Verification header"
 *
 * state "ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_E" as SIGNED_HEADER_VERIFICATION : Starts the header verification process
 * state "ecy_hsm_APPLET_SECFLASH_UPDATE_FROM_DATA_CONTAINER_E" as DATA_TRANSFER_AND_FLASHING : Flashes the update package and verifies boot and core
 * hashes
 *
 * [*] --> SIGNED_HEADER_VERIFICATION : _VerifyHeader
 * SIGNED_HEADER_VERIFICATION --> SIGNED_HEADER_VERIFICATION : _VerifyHeader
 * SIGNED_HEADER_VERIFICATION --> DATA_TRANSFER_AND_FLASHING : _UpdateAndFinalize
 * DATA_TRANSFER_AND_FLASHING -->[*]
 * @enduml
 * @endinternal
 */
#if defined(ecy_hsm_HOST_DRIVER_VERSION_2_7_9)
/* Struct in version v2.7.9.r0 */
typedef enum ecy_hsm_Applet_SecFlash_StateT
{
    ecy_hsm_APPLET_SECFLASH_STATE_INIT_E,                                      /**< secure flash init */
    ecy_hsm_APPLET_SECFLASH_STATE_UPDATE_E,                                    /**< secure flash update */
    ecy_hsm_APPLET_SECFLASH_STATE_FINAL_E,                                     /**< secure flash final */
    ecy_hsm_APPLET_SECFLASH_STATE_CANCEL_E,                                    /**< secure flash cancel */
    ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_E,                      /**< alternate SecFlash process - signed header verification */
    ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_STORE_MAC_E,            /**< alternate SecFlash process - store MAC over signed header provided by host */
    ecy_hsm_APPLET_SECFLASH_UPDATE_FROM_DATA_CONTAINER_E,                      /**< alternate SecFlash process - update data transfer and application */
    ecy_hsm_APPLET_SECFLASH_STATE_SYNC_E,                                      /**< synchronize the inactive with the active bank (bankswap) */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_SECFLASH_NUMSTATES_E,                                       /**< number of states */

    ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_RETRIEVE_MAC_E = 0xFDU, /**< dummy ID */
    ecy_hsm_APPLET_SECFLASH_STATE_BANKSWAP_E                          = 0xFEU, /**< dummy ID */
    ecy_hsm_APPLET_SECFLASH_HOST_SIGNED_HEADER_VERIFICATION_E         = 0xFFU, /**< dummy ID */
} ecy_hsm_Applet_SecFlash_StateT;
#elif defined(ecy_hsm_HOST_DRIVER_VERSION_2_7_10)
/* Struct in version >= v2.7.10.r0 and <= v2.7.12.r0 */
typedef enum ecy_hsm_Applet_SecFlash_StateT
{
    ecy_hsm_APPLET_SECFLASH_STATE_INIT_E,                                   /**< secure flash init */
    ecy_hsm_APPLET_SECFLASH_STATE_UPDATE_E,                                 /**< secure flash update */
    ecy_hsm_APPLET_SECFLASH_STATE_FINAL_E,                                  /**< secure flash final */
    ecy_hsm_APPLET_SECFLASH_STATE_CANCEL_E,                                 /**< secure flash cancel */
    ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_E,                   /**< alternate SecFlash process - signed header verification */
    ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_RETRIEVE_MAC_E,      /**< alternate SecFlash process - retrieve MAC from the HSM */
    ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_STORE_MAC_E,         /**< alternate SecFlash process - store MAC over signed header provided by host */
    ecy_hsm_APPLET_SECFLASH_UPDATE_FROM_DATA_CONTAINER_E,                   /**< alternate SecFlash process - update data transfer and application */
    ecy_hsm_APPLET_SECFLASH_STATE_SYNC_E,                                   /**< synchronize the inactive with the active bank (bankswap) */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_SECFLASH_NUMSTATES_E,                                    /**< number of states */

    ecy_hsm_APPLET_SECFLASH_STATE_BANKSWAP_E                    = 0xFEU,    /**< dummy ID */
    ecy_hsm_APPLET_SECFLASH_HOST_SIGNED_HEADER_VERIFICATION_E   = 0xFFU,    /**< dummy ID */
} ecy_hsm_Applet_SecFlash_StateT;
/* Struct in version <= v2.7.8.r0 (up to STATE_SYNC) and >= v2.7.12.r1 */
#else
typedef enum ecy_hsm_Applet_SecFlash_StateT
{
    ecy_hsm_APPLET_SECFLASH_STATE_INIT_E,                           /**< secure flash init */
    ecy_hsm_APPLET_SECFLASH_STATE_UPDATE_E,                         /**< secure flash update */
    ecy_hsm_APPLET_SECFLASH_STATE_FINAL_E,                          /**< secure flash final */
    ecy_hsm_APPLET_SECFLASH_STATE_CANCEL_E,                         /**< secure flash cancel */
    ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_E,           /**< alternate SecFlash process - signed header verification */
    ecy_hsm_APPLET_SECFLASH_UPDATE_FROM_DATA_CONTAINER_E,           /**< alternate SecFlash process - update data transfer and application */
    ecy_hsm_APPLET_SECFLASH_STATE_SYNC_E,                           /**< synchronize the inactive with the active bank (bankswap) */
    ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_STORE_MAC_E, /**< alternate SecFlash process - store MAC over signed header provided by host */
    ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_RETRIEVE_MAC_E, /**< alternate SecFlash process - retrieve MAC from the HSM */
    ecy_hsm_APPLET_SECFLASH_STATE_BANKSWAP_E,                          /**< Perform a stand alone HSM independent bank swap */
    ecy_hsm_APPLET_SECFLASH_HOST_SIGNED_HEADER_VERIFICATION_E,         /**< alternate SecFlash process - host signed header verification */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_SECFLASH_NUMSTATES_E                                 /**< number of states */
} ecy_hsm_Applet_SecFlash_StateT;
#endif

/**
 * Applet parameter data for secure flash applet
 */
typedef struct ecy_hsm_SecFlashParamT
{
    uint8 const*                  pFlashStart;   /**< Pointer to start address of flash block to be programmed   */
    uint32                        numBytesFlash; /**< Length of block to be flashed                              */
    ecy_hsm_Csai_SignatureSchemeT scheme;        /**< digital signature schemes supported by the HSM             */
    ecy_hsm_Csai_KeyHandleT       hKey;          /**< Handle to a key available in the HSM's session context to
                                                      use for signature                                          */
    ecy_hsm_Csai_SecFlash_FlashOptBmT bmOptions; /**< Bit mask for specified SecFlash options
                                                      @ref GROUP_CSAI_SECFLASH_OPTIONS                           */
    uint8 const* msg;                            /**< Pointer to first (or only) data block for operation        */
    uint32       msgLength;                      /**< Length of data block                                       */
    uint8 const* pSign;                          /**< Pointer to the Sign for Verification                       */
    uint32       signLength;                     /**< Length of Signature                                        */
    uint32*      pResultFlag;                    /**< Signature verification result Flag                         */
} ecy_hsm_SecFlashParamT;

/**
 * Applet parameter data for secure flash applet for SECFLASH_HSM_REPROG_SINGLESHOT
 */
typedef struct ecy_hsm_SecFlashSingleShotParamT
{
    ecy_hsm_Csai_SyncFlashAccessUpdateT* pFlashUsageSyncHost; /**< Synchronization state */
    ecy_hsm_Csai_UpdateContainerParamT*  pCustomParam;        /**< Parameters of update container */
} ecy_hsm_SecFlashSingleShotParamT;

/**
 * Structure containing a MAC to be passed from Host to HSM during update.
 */
typedef struct ecy_hsm_SetSignedHeaderMacParamT
{
    const uint8* pHeaderMac;      /**< Pointer to a Signed Header MAC */
    uint32       headerMacLength; /**< Size of Signed Header MAC in bytes */
} ecy_hsm_SetSignedHeaderMacParamT;

/**
 * Structure containing a MAC to be returned from HSM to Host during update.
 */
typedef struct ecy_hsm_RetrieveSignedHeaderMacParamT
{
    uint8*  pHeaderMac;       /**< Pointer to a Signed Header MAC */
    uint32* pHeaderMacLength; /**< Size of Signed Header MAC in bytes */
} ecy_hsm_RetrieveSignedHeaderMacParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_SecFlashSingleShotParamT
 */
#define HSM_SecFlashSingleShotParamT                              ecy_hsm_SecFlashSingleShotParamT
/**
 * @deprecated by ecy_hsm_SecFlashParamT
 */
#define HSM_SecFlashParamT                                        ecy_hsm_SecFlashParamT
/**
 * @deprecated by ecy_hsm_Applet_SecFlash_StateT
 */
#define Applet_SecFlash_StateT                                    ecy_hsm_Applet_SecFlash_StateT
/**
 * @deprecated by ecy_hsm_Applet_SecFlashModeT
 */
#define Applet_SecFlashModeT                                      ecy_hsm_Applet_SecFlashModeT

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_STORE_MAC_E
 */
#define APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_STORE_MAC_E    ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_STORE_MAC_E
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_STATE_INIT_E
 */
#define APPLET_SECFLASH_STATE_INIT_E                              ecy_hsm_APPLET_SECFLASH_STATE_INIT_E
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_STATE_UPDATE_E
 */
#define APPLET_SECFLASH_STATE_UPDATE_E                            ecy_hsm_APPLET_SECFLASH_STATE_UPDATE_E
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_STATE_FINAL_E
 */
#define APPLET_SECFLASH_STATE_FINAL_E                             ecy_hsm_APPLET_SECFLASH_STATE_FINAL_E
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_STATE_CANCEL_E
 */
#define APPLET_SECFLASH_STATE_CANCEL_E                            ecy_hsm_APPLET_SECFLASH_STATE_CANCEL_E
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_E
 */
#define APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_E              ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_E
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_RETRIEVE_MAC_E
 */
#define APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_RETRIEVE_MAC_E ecy_hsm_APPLET_SECFLASH_SIGNED_HEADER_VERIFICATION_RETRIEVE_MAC_E
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_UPDATE_FROM_DATA_CONTAINER_E
 */
#define APPLET_SECFLASH_UPDATE_FROM_DATA_CONTAINER_E              ecy_hsm_APPLET_SECFLASH_UPDATE_FROM_DATA_CONTAINER_E
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_STATE_SYNC_E
 */
#define APPLET_SECFLASH_STATE_SYNC_E                              ecy_hsm_APPLET_SECFLASH_STATE_SYNC_E
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_NUMSTATES_E
 */
#define APPLET_SECFLASH_NUMSTATES_E                               ecy_hsm_APPLET_SECFLASH_NUMSTATES_E
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_MODE_HOSTPROG
 */
#define APPLET_SECFLASH_MODE_HOSTPROG                             ecy_hsm_APPLET_SECFLASH_MODE_HOSTPROG
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_MODE_HSMREPROG
 */
#define APPLET_SECFLASH_MODE_HSMREPROG                            ecy_hsm_APPLET_SECFLASH_MODE_HSMREPROG
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_MODE_HSMSYNCBANK
 */
#define APPLET_SECFLASH_MODE_HSMSYNCBANK                          ecy_hsm_APPLET_SECFLASH_MODE_HSMSYNCBANK
/**
 * @deprecated by ecy_hsm_APPLET_SECFLASH_MODE_HSMDUALBANK
 */
#define APPLET_SECFLASH_MODE_HSMDUALBANK                          ecy_hsm_APPLET_SECFLASH_MODE_HSMDUALBANK

/**
 * Applet context data for secure flash applet
 * @ingroup APPLET_CONTEXT
 */
typedef HSM_SecFlashParamT Applet_SecFlashCtx_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief SecFlash applet control structures
 */
extern const Applet_ts Applet_SecFlash_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_SECFLASH_H
