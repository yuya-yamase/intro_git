/**
 * @file
 ***********************************************************************************************
 * @brief Trusted Boot applet interface
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2017, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_APPLET_TRUSTED_BOOT_H
#define ECY_HSM_APPLET_TRUSTED_BOOT_H

/* *** includes *******************************************************************************/
#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai_manual_tabs_verification.h"
#include "ecy_hsm_csai_smart_tb.h"
#include "ecy_hsm_csai_trusted_boot.h"
#include "ecy_hsm_csai_trusted_sw_part_verification.h"

/**
 * @addtogroup APPLET_IMPL
 * @{
 */

/* *** type declarations **********************************************************************/

/**
 * @brief Possible states for TB applet
 *
 * @details
 * @section APPLET_TB Trusted Boot applet
 * @subsection APPLET_TB_STATES Applet states
 *
 * @startuml
 * state "ecy_hsm_APPLET_TB_FUNC_REQUEST_VERI" as _VERIFY                         : Request single SW part verification
 * state "ecy_hsm_APPLET_TB_FUNC_REQUEST_VERIFICATION" as _VERIFY_EXT             : Request multiple SW parts verification
 * state "ecy_hsm_APPLET_TB_FUNC_END_AUTH_BOOT" as _AUTHENTIFY                    : End authenticated boot
 * state "ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_INIT" as _Init                    : Initialize table entry & CMAC calculation
 * state "ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_UPDATE" as _Update                : Update CMAC calculation
 * state "ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_FINISH" as _Finish                : Finish CMAC calculation
 * state "ecy_hsm_APPLET_TB_FUNC_REF_Table_FINALIZE" as _Final                    : persist temporary reference table into non-volatile storage
 * state "ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE" as _SetSign        : Specify signature type and location for TABS use case
 * state "ecy_hsm_APPLET_TB_FUNC_REF_REQUEST_MANUAL_VERI" as _ManualVerify        : Trigger a manual TABS verification
 * state "ecy_hsm_APPLET_TB_FUNC_RTMD_SUSPEND" as _Suspend                        : Manual RTMD suspend
 * state "ecy_hsm_APPLET_TB_FUNC_RTMD_REACTIVATION" as _Reactivation              : Manual RTMD reactivation
 * state "ecy_hsm_APPLET_TB_FUNC_RTMD_READ_SUSPENSION_DATA" as _ReadData          : Read Manual suspension data

 * state "ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_INIT" as _SwPartInit             : Initialize of the sw part table entry, CMAC and hashes calculation
 * state "ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_UPDATE" as _SwPartUpdate         : Update CMAC and hashes calculation
 * state "ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_SET_SIGNATURE" as _SwPartSetSign : Specify signature type and location for TABS use case and the signature validation
 * state "ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINISH" as _SwPartFinish         : Finish CMAC calculation, hash calculation and verify the signature
 * state "ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINALIZE" as _SwPartFinal        : persist temporary reference table into non-volatile storage
 * [*]      --> _Init       :ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_INIT
 * _Init    --> _SetSign    :ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE
 * _Init    --> _Update     :ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_UPDATE
 * _Init    --> _Finish     :ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_FINISH\n(Remove entry)
 * _Init    --> _Init       :ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_INIT
 * _SetSign --> _Update     :ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_UPDATE
 * _SetSign --> _Finish     :ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_FINISH
 * _Update  --> _Update     :ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_UPDATE
 * _Update  --> _Finish     :ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_FINISH
 * _Finish  --> _Init       :ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_INIT
 * _Finish  --> _Final      :APPLET_TB_FUNC_REF_Table_PART_FINAL
 * _Final   --> [*]
 *
 * [*]             --> _VERIFY
 * _VERIFY      --> [*]
 * [*]             --> _VERIFY_EXT
 * _VERIFY_EXT  --> [*]
 * [*]             --> _ManualVerify
 * _ManualVerify      --> [*]
 * [*]             --> _AUTHENTIFY
 * _AUTHENTIFY  --> [*]
 * [*]             --> _Suspend
 * _Suspend  --> [*]
 * [*]             --> _Reactivation
 * _Reactivation  --> [*]
 * [*]             --> _ReadData
 * _ReadData  --> [*]
 *
 * [*]                  --> _SwPartInit         :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_INIT
 * _SwPartInit          --> _SwPartSetSign      :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_SET_SIGNATURE
 * _SwPartInit          --> _SwPartUpdate       :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_UPDATE
 * _SwPartInit          --> _SwPartFinish       :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINISH\n(Remove entry, only possible in privemode or secure access)
 * _SwPartInit          --> _SwPartInit         :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_INIT
 * _SwPartSetSign       --> _SwPartUpdate       :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_UPDATE
 * _SwPartSetSign       --> _SwPartFinish       :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINISH
 * _SwPartUpdate        --> _SwPartUpdate       :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_UPDATE
 * _SwPartUpdate        --> _SwPartSetSign      :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_SET_SIGNATURE
 * _SwPartUpdate        --> _SwPartFinish       :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINISH
 * _SwPartFinishFinish  --> _SwPartInit         :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_INIT
 * _SwPartFinishFinish  --> _SwPartFinal        :ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINALIZE
 * _SwPartFinal         --> [*]
 * @enduml
 */
typedef enum ecy_hsm_Csai_Applet_TB_StateT
{
    ecy_hsm_APPLET_TB_FUNC_REQUEST_VERI,                          /**< Request SW part verification */
    ecy_hsm_APPLET_TB_FUNC_END_AUTH_BOOT,                         /**< End authenticated boot */
    ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_INIT,                   /**< Create a temporary SW-part reference table entry in RAM
                                                                        and initialize CMAC calculation for this SW-part */
    ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_UPDATE,                 /**< Update the CMAC of the active SW-part with the given data chunk */
    ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_FINISH,                 /**< Finish the CMAC calculation of the active SW-part */
    ecy_hsm_APPLET_TB_FUNC_REF_Table_FINALIZE,                    /**< Persist the temporary reference table updates into HSM non-volatile storage */
    ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE,          /**< Set signature address, signature type and keystore-slot of certificate/public key for TABS using
                                                                        keystore, or signature address and certificate address for TABS using memory-mapped certificate.
                                                                        The choice is selected by the signature verification mode. */
    ecy_hsm_APPLET_TB_FUNC_REF_Table_FULL_INIT,                   /**< A state to trigger the whole reference table initialization in the production state */
    ecy_hsm_APPLET_TB_FUNC_REF_REQUEST_MANUAL_VERI,               /**< Request manual SW part verification single shot */
    ecy_hsm_APPLET_TB_FUNC_RTMD_SUSPEND,                          /**< suspend the RTMD manually */
    ecy_hsm_APPLET_TB_FUNC_RTMD_REACTIVATION,                     /**< reactivate the RTMD manually */
    ecy_hsm_APPLET_TB_FUNC_RTMD_READ_SUSPENSION_DATA,             /**< read out the current RTMD suspension data*/
    ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_INIT,                  /**< Request trusted SW-part verification streaming:
                                                                        Create a temporary SW-part reference table entry in RAM and
                                                                        initialize CMAC and signature calculation for this SW-part */
    ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_UPDATE,                /**< Update the Hashes for the signature verification and CMAC
                                                                        of the active SW-part with the given data chunk */
    ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_SET_SIGNATURE,         /**< Set signature address, signature type and keystore-slot of certificate/public key for TABS using
                                                                        keystore, or signature address, certificate address for TABS using memory-mapped certificate.
                                                                        and signature length.
                                                                        The choice is selected by the signature verification mode. */
    ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINISH,                /**< Finish the signature verification and CMAC calculation of the active SW-part */
    ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINALIZE,              /**< Persist the temporary reference table updates into HSM non-volatile storage */
    ecy_hsm_APPLET_TB_FUNC_SMART_TB_INIT,                         /**< Trigger the parsing of memory descriptor, and copy to HSM RAM */
    ecy_hsm_APPLET_TB_FUNC_SMART_TB_UPDATE,                       /**< Verify update header, then parse and verify SW part details from current header to
                                                                       populate temporary trusted boot table and calculate cmac value */
    ecy_hsm_APPLET_TB_FUNC_SMART_TB_FINISH,                       /**< Does Host Pflash coverage check and persist temp trusted boot table entries into DFlash */
    ecy_hsm_APPLET_TB_FUNC_SMART_TB_FULL,                         /**< Single shot method performing SMART_TB_INIT, SMART_TB_UPDATE and SMART_TB_FINISH in sequence */
    ecy_hsm_APPLET_TB_FUNC_SMART_TB_UPDATE_DESCRIPTOR,            /**< Parse the descriptor fields, upon successful verification of all fields. persist the descriptor data into DFlash */
    ecy_hsm_APPLET_TB_FUNC_TB_FOTA_USECASE,                       /**< The use case to support the TB FOTA handling. Currently supported use case is copying the TB reference table of the active bank to the TB reference table of the inactive bank */
    ecy_hsm_APPLET_TB_FUNC_INIT,                                  /**< TB initialisation, only required for certain use cases, like ABHost */
    ecy_hsm_APPLET_TB_FUNC_REQUEST_VERIFICATION,                  /**< New variant of ecy_hsm_APPLET_TB_FUNC_REQUEST_VERI for software part verification */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_TB_NUMSTATES_E                                 /**< Number of states */
} ecy_hsm_Csai_Applet_TB_StateT;

/** Verification record for keystore-based certificate ( @ref ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_PUBKEY / @ref ecy_hsm_CSAI_TB_VERIFMODE_KEYSTORE_CERT) */
typedef struct ecy_hsm_Csai_TB_VerifKeystore_ParamTag
{
    /** The key ID of the certificate or public key */
    ecy_hsm_Csai_KeyIdT swPartKeyId;
    /** The start address of the SW-part signature */
    uint32 swPartSignatureAddress;
    /** The signature type @ref ecy_hsm_Csai_SignatureSchemeTag (for the public key use case)
     * @remarks Not all signature types from @ref ecy_hsm_Csai_SignatureSchemeTag are supported, especially not the prehashed types.
     */
    uint16 swPartSignatureType;
} ecy_hsm_Csai_TB_VerifKeystoreParamT;

/** Verification record for memory-mapped certificate ( @ref ecy_hsm_CSAI_TB_VERIFMODE_MEMMAPPED_CERT) */
typedef struct ecy_hsm_Csai_TB_VerifMemMappedParamTag
{
    /** The start address of the SW-part signature */
    uint32 swPartSignatureAddress;
    /** The start address of the SW-part certificate */
    uint32 swPartCertAddress;
} ecy_hsm_Csai_TB_VerifMemMappedParamT;

/** Allow for different record types while maintaining layout backward compatibility.
 * The actual record being used is determined by field @ref TB_InfoTable_RecordTag.SwPartVerifSignMode */
/* PRQA S 0750 2 */ /* <Justification: Definition of a union is appropriate here. */
typedef union ecy_hsm_Csai_TB_VerifParamTag
{
    ecy_hsm_Csai_TB_VerifKeystoreParamT  KeystoreRecord;  /**< record in the keystore */
    ecy_hsm_Csai_TB_VerifMemMappedParamT MemMappedRecord; /**< mapped record */
} ecy_hsm_Csai_TB_VerifParamT;

/** Structure for the data passed to a trusted boot software part verification operation, see @ref TrustedBoot_VerifySwPart */
typedef struct ecy_hsm_Csai_TB_RequestVerifyParamTag
{
    uint32 swPartAddr; /**< The Address of the SW Part, if SwPartId is 0 */
    uint8  swPartId;   /**< The identifier of the SW part to be verified */
} ecy_hsm_Csai_TB_RequestVerifyParamT;

/** Structure to init reference table calculation */
typedef struct ecy_hsm_Csai_TB_ReferenceTablePartInitTag
{
    uint32 swPartAddr;      /**< The Address of the SW Part, if SwPartId is 0 */
    uint8  swPartId;        /**< The identifier of the SW part to be verified */
    uint8  swPartBootMode;  /**< The boot mode of the SW part */
    uint8  swPartRtmdOrder; /**< The RTMD order of the SW Part */
} ecy_hsm_Csai_TB_ReferenceTablePartInitT;

/** Structure to update the reference table */
typedef struct ecy_hsm_Csai_TB_ReferenceTablePartUpdateTag
{
    uint32       swPartChunkNumBytes; /**< The length in bytes of the data chunk */
    const uint8* pSwPartChunk;        /**< A data chunk of the current SW part to be verified */
} ecy_hsm_Csai_TB_ReferenceTablePartUpdateT;

/** Structure to persist the reference table */
typedef struct ecy_hsm_Csai_TB_ReferenceTablePartFinalizeTag
{
    uint32* pNumPersistedEntries; /**< Pointer to the location of the number of reference table entries that were persisted */
} ecy_hsm_Csai_TB_ReferenceTablePartFinalizeT;

/** Structure to set the location of the signature for trust anchor based on signatures feature */
typedef struct ecy_hsm_Csai_TB_ReferenceTablePartSetSignTag
{
    ecy_hsm_Csai_TB_VerifParamT swPartVerifParams;   /**< The verification parameters (trust anchor based on signature feature) */
    uint8                       swPartVerifSignMode; /**< The signature verification mode. Also used as a filler byte for alignment */
} ecy_hsm_Csai_TB_ReferenceTablePartSetSignT;

/** Structure for the manual RTMD suspend data */
typedef struct ecy_hsm_Csai_TB_RTMDSuspendDataTag
{
    void*  pData;
    uint32 dataLength;
} ecy_hsm_Csai_TB_RTMDSuspendDataParamT;

/**
 * Applet parameter data for Trusted Boot applet
 */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_TB_ReferenceTable_ParamTag
{
    ecy_hsm_Csai_TB_Init_ParamSetAndVersionT           TB_InitParam;                           /**< parameters for initialising certain trusted boot features like ABHost */
    ecy_hsm_Csai_TB_SwVerification_ParamSetAndVersionT TB_SwVerificationParam;                 /**< parameters for verifying multiple SW parts */
    ecy_hsm_Csai_TB_RequestVerifyParamT                TB_RequestVerifyParam;                  /**< parameters for verify */
    ecy_hsm_Csai_TB_ReferenceTablePartInitT            TB_ReferenceTablePartInitParam;         /**< parameters for init */
    ecy_hsm_Csai_TB_ReferenceTablePartUpdateT          TB_ReferenceTablePartUpdateParam;       /**< parameters for update */
    ecy_hsm_Csai_TB_ReferenceTablePartFinalizeT        TB_ReferenceTablePartFinalizeParam;     /**< parameters for finalize */
    ecy_hsm_Csai_TB_ReferenceTablePartSetSignT         TB_ReferenceTablePartSetSignParam;      /**< parameters for set sign */
    ecy_hsm_Csai_TB_RequestManualVerifyParamT          TB_RequestManualTabsVerifyContextParam; /**< parameters for manual tabs verification */
    ecy_hsm_Csai_TB_RTMDSuspendDataParamT              TB_RTMDSuspendDataParam;                /**< parameters for manual RTMD suspend data */
    TB_SwPartParamT                                    TB_TrustedSwPartParam;                  /**< parameters for trusted SW-part verification */
    ecy_hsm_Csai_SMART_TBDataT                         TB_SMARTParam;                          /**< parameters for SMART TB */
    ecy_hsm_Csai_TB_FOTA_DataT                         TB_FOTAParam;                           /**< parameters for TB FOTA */

} ecy_hsm_Csai_TB_ParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_VerifKeystoreParamT
 */
#define TB_VerifKeystoreParamT ecy_hsm_Csai_TB_VerifKeystoreParamT
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_VerifMemMappedParamT
 */
#define TB_VerifMemMappedParamT ecy_hsm_Csai_TB_VerifMemMappedParamT
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_VerifParamT
 */
#define TB_VerifParamT ecy_hsm_Csai_TB_VerifParamT
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_RequestVerifyParamT
 */
#define TB_RequestVerifyParamT ecy_hsm_Csai_TB_RequestVerifyParamT
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_ReferenceTablePartInitT
 */
#define TB_ReferenceTablePartInitT ecy_hsm_Csai_TB_ReferenceTablePartInitT
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_ReferenceTablePartUpdateT
 */
#define TB_ReferenceTablePartUpdateT ecy_hsm_Csai_TB_ReferenceTablePartUpdateT
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_ReferenceTablePartFinalizeT
 */
#define TB_ReferenceTablePartFinalizeT ecy_hsm_Csai_TB_ReferenceTablePartFinalizeT
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_ReferenceTablePartSetSignT
 */
#define TB_ReferenceTablePartSetSignT ecy_hsm_Csai_TB_ReferenceTablePartSetSignT
/**
 * @deprecated by @ref ecy_hsm_Csai_TB_RTMDSuspendDataParamT
 */
#define TB_RTMDSuspendDataParamT ecy_hsm_Csai_TB_RTMDSuspendDataParamT
/**
 * @deprecated by ecy_hsm_Csai_Applet_TB_StateT
 */
#define Applet_TB_StateT ecy_hsm_Csai_Applet_TB_StateT
/**
 * @deprecated by ecy_hsm_Csai_TB_VerifKeystore_ParamTag
 */
#define TB_VerifKeystore_ParamTag ecy_hsm_Csai_TB_VerifKeystore_ParamTag
/**
 * @deprecated by ecy_hsm_Csai_TB_VerifMemMappedParamTag
 */
#define TB_VerifMemMappedParamTag ecy_hsm_Csai_TB_VerifMemMappedParamTag
/**
 * @deprecated by ecy_hsm_Csai_TB_VerifParamTag
 */
#define TB_VerifParamTag ecy_hsm_Csai_TB_VerifParamTag
/**
 * @deprecated by ecy_hsm_Csai_TB_RequestVerifyParamTag
 */
#define TB_RequestVerifyParamTag ecy_hsm_Csai_TB_RequestVerifyParamTag
/**
 * @deprecated by ecy_hsm_Csai_TB_ReferenceTablePartInitTag
 */
#define TB_ReferenceTablePartInitTag ecy_hsm_Csai_TB_ReferenceTablePartInitTag
/**
 * @deprecated by ecy_hsm_Csai_TB_ReferenceTablePartUpdateTag
 */
#define TB_ReferenceTablePartUpdateTag ecy_hsm_Csai_TB_ReferenceTablePartUpdateTag
/**
 * @deprecated by ecy_hsm_Csai_TB_ReferenceTablePartFinalizeTag
 */
#define TB_ReferenceTablePartFinalizeTag ecy_hsm_Csai_TB_ReferenceTablePartFinalizeTag
/**
 * @deprecated by ecy_hsm_Csai_TB_ReferenceTablePartSetSignTag
 */
#define TB_ReferenceTablePartSetSignTag ecy_hsm_Csai_TB_ReferenceTablePartSetSignTag
/**
 * @deprecated by ecy_hsm_Csai_TB_RTMDSuspendDataTag
 */
#define TB_RTMDSuspendDataTag ecy_hsm_Csai_TB_RTMDSuspendDataTag
/**
 * @deprecated by ecy_hsm_Csai_TB_ReferenceTable_ParamTag
 */
#define TB_ReferenceTable_ParamTag ecy_hsm_Csai_TB_ReferenceTable_ParamTag
/**
 * @deprecated by ecy_hsm_Csai_TB_ParamT
 */
#define TB_ParamT ecy_hsm_Csai_TB_ParamT

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_REQUEST_VERI
 */
#define APPLET_TB_FUNC_REQUEST_VERI ecy_hsm_APPLET_TB_FUNC_REQUEST_VERI
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_END_AUTH_BOOT
 */
#define APPLET_TB_FUNC_END_AUTH_BOOT ecy_hsm_APPLET_TB_FUNC_END_AUTH_BOOT
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_INIT
 */
#define APPLET_TB_FUNC_REF_Table_PART_INIT ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_INIT
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_UPDATE
 */
#define APPLET_TB_FUNC_REF_Table_PART_UPDATE ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_UPDATE
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_FINISH
 */
#define APPLET_TB_FUNC_REF_Table_PART_FINISH ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_FINISH
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_REF_Table_FINALIZE
 */
#define APPLET_TB_FUNC_REF_Table_FINALIZE ecy_hsm_APPLET_TB_FUNC_REF_Table_FINALIZE
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE
 */
#define APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE ecy_hsm_APPLET_TB_FUNC_REF_Table_PART_SET_SIGNATURE
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_REF_Table_FULL_INIT
 */
#define APPLET_TB_FUNC_REF_Table_FULL_INIT ecy_hsm_APPLET_TB_FUNC_REF_Table_FULL_INIT
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_REF_REQUEST_MANUAL_VERI
 */
#define APPLET_TB_FUNC_REF_REQUEST_MANUAL_VERI ecy_hsm_APPLET_TB_FUNC_REF_REQUEST_MANUAL_VERI
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_RTMD_SUSPEND
 */
#define APPLET_TB_FUNC_RTMD_SUSPEND ecy_hsm_APPLET_TB_FUNC_RTMD_SUSPEND
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_RTMD_REACTIVATION
 */
#define APPLET_TB_FUNC_RTMD_REACTIVATION ecy_hsm_APPLET_TB_FUNC_RTMD_REACTIVATION
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_RTMD_READ_SUSPENSION_DATA
 */
#define APPLET_TB_FUNC_RTMD_READ_SUSPENSION_DATA ecy_hsm_APPLET_TB_FUNC_RTMD_READ_SUSPENSION_DATA
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_INIT
 */
#define APPLET_TB_FUNC_TRUSTED_SW_PART_INIT ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_INIT
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_UPDATE
 */
#define APPLET_TB_FUNC_TRUSTED_SW_PART_UPDATE ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_UPDATE
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_SET_SIGNATURE
 */
#define APPLET_TB_FUNC_TRUSTED_SW_PART_SET_SIGNATURE ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_SET_SIGNATURE
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINISH
 */
#define APPLET_TB_FUNC_TRUSTED_SW_PART_FINISH ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINISH
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINALIZE
 */
#define APPLET_TB_FUNC_TRUSTED_SW_PART_FINALIZE ecy_hsm_APPLET_TB_FUNC_TRUSTED_SW_PART_FINALIZE
/**
 * @deprecated by @ref ecy_hsm_APPLET_TB_NUMSTATES_E
 */
#define APPLET_TB_NUMSTATES_E ecy_hsm_APPLET_TB_NUMSTATES_E

/**
 * Applet context data for Trusted Boot applet
 * @ingroup APPLET_CONTEXT
 */
typedef TB_ParamT Applet_TBCtx_tst;
/* *** extern declarations *********************************************************************/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief Trusted Boot applet control structures
 */
extern const Applet_ts Applet_TB_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // ECY_HSM_APPLET_TRUSTED_BOOT_H
