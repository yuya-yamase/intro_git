/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Secure HSM flash operations
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * types and functions for secure HSM flash programming
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_CSAI_SECFLASH
#define ECY_HSM_CSAI_SECFLASH

/* *** includes *******************************************************************************/

#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_sign.h"
#include "ecy_hsm_csai_hash.h"

/**
 * @addtogroup GROUP_CSAI_SECFLASH
 * @{
 * Secure HSM flash programming API
 *
 */

/**
 * @addtogroup GROUP_CSAI_SECFLASH_OPTIONS
 * @{
 * Secure flashing options to be used in @ref ecy_hsm_Csai_SecFlash_Init
 */

/**
 * No special options indicated.
 * If the target has bankswap activated, both banks will be updated (Dual bank update).
 * Bankswap is currently only supported on TC3Hx(_SE), RH850 U2A Dual Map and CYT2BL.
 * If the target has independent bankswap activated, then this option is not allowed.
 * Independent bankswap is currently only supported on STSR6 targets.
 * If the target is a "bankswap only target", this option is also not allowed.
 * A "bankswap only target" is currently only the RH850 U2x in Dual Map Mode.
 */
#define ecy_hsm_CSAI_SECFLASH_OPT_NONE                 (0x00000000UL)

/**
 * Option bit to indicate if the HSM configuration data has to be updated during HSM re-programming
 *
 * This bit must be set to include the HSM configuration data in the HSM re-programming.
 *
 * @note
 * Please note that HSM configuration data can only be programmed together with HSM software
 *
 * @note
 * This option bit will only be accepted, if HSM reprogramming is triggered by selection of the
 * corresponding address range of HSM flash.
 * Otherwise this option will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM
 *
 * @warning
 * This option is currently only enabled for TC3xx(_SE) and STSR6. For other targets it is disabled
 * and will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.
 */
#define ecy_hsm_CSAI_SECFLASH_OPT_HSMCFG               (0x00000001UL)

/**
 * Option bit to indicate if the HSM update package contains a signed verification header
 * that has to be verified during HSM re-programming.
 * If this bit is set, the HSM update verification mechanism is shifted from verification of separate
 * signatures for config, core and boot to the verification of combined signature present in the signed update
 * verification header. In this context, the config area and bootloader will be flashed seamlessly and will be
 * protected by one hash located at the end of the bootloader. Core application is protected by its own hash. Both
 * hashes must be contained in the signed header to be provisioned by means of
 * @ref ecy_hsm_Csai_SecFlash_VerifySignedHeader before calling @ref ecy_hsm_Csai_SecFlash_UpdateFromDataContainer. This
 * is an internal option and cannot be passed by the CSAI to the HSM.
 *
 * @note
 * The HSM re-programming using a signed header cannot be used in conjunction with the HSM chunk-wise
 * re-programming CSAI API
 *
 * @warning
 */
#define ecy_hsm_CSAI_SECFLASH_OPT_SIGNED_HEADER_UPDATE (0x00000002UL)

/**
 * Option bit to indicate that only the inactive/shadow bank will be updated
 *
 * If this option bit is set, the update process will only apply an update on the inactive/shadow bank.
 * The inactive/shadow bank should be updated with a newer hex file version.
 * After the update the active bank still runs on the same version as before.
 *
 * If a bank swap occurs after a successful update, the Software-Over-The-Air use case has been fully executed.
 *
 * @note
 * This option bit will only be accepted, if the target hardware has bankswap activated.
 * Otherwise this option will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.
 *
 * @warning
 * This option is currently only enabled for TC3Hx(_SE), RH850 U2A Dual Map, CYT2BL and STSR6.
 * For other targets it is disabled and will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.
 */
#define ecy_hsm_CSAI_SECFLASH_OPT_SOTA                 (0x00000004UL)

/**
 * The inactive/shadow bank will be synchronized with the currently active bank
 *
 * If this option bit is set, the inactive/shadow bank will be updated with the data from the active bank.
 * After this process both banks should contain the same hex data.
 *
 * @note
 * This option bit will only be accepted, if the target hardware has bankswap activated.
 * Otherwise this option will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.
 *
 * @warning
 * This option is currently only enabled for TC3Hx(_SE), RH850 U2A Dual Map, CYT2BL and STSR6 targets. For other targets it is disabled
 * and will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.
 */
#define ecy_hsm_CSAI_SECFLASH_OPT_SYNC                 (0x00000008UL)

/**
 * The HSM performs a bank swap. If passed with ecy_hsm_CSAI_SECFLASH_OPT_SOTA,
 * the bank swap will be performed after a successful update.
 *
 * @note
 * This option bit will only be accepted, if the target hardware has independent bankswap activated.
 * Otherwise this option will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.
 *
 * @warning
 * This option is currently only enabled for STSR6-targets. For other targets it is disabled
 * and will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.
 */
#define ecy_hsm_CSAI_SECFLASH_OPT_SWAP                 (0x00000010UL)

/**
 * Option bit to indicate that only the inactive or shadow bank will be updated from core app
 *
 * If this option bit is set, the update process will only apply an update on the inactive/shadow bank.
 * The inactive/shadow bank should be updated with a newer hex file version.
 * After the successful update of the inactive bank, the active bank still runs on the same version as before.
 *
 * If a bank swap occurs after a successful update, the Software-Over-The-Air use case has been fully executed.
 *
 * @note
 * This option bit will only be accepted when it is coupled with SOTA or SYNC,
 * if the target hardware has bankswap activated.
 * Otherwise this option will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.
 *
 * @warning
 * This option is currently only enabled for D6_DM, D7_DM, U2A6_DM.
 * For other targets it is disabled and will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM.
 */
#define ecy_hsm_CSAI_SECFLASH_OPT_FOTA                 (0x00000020UL)

/**
 * Option bit for INSECURE flashing
 *
 * If this bit is set, HSM wil NOT perform Secure Flashing Procedure!
 * (In particular a support for secure/authentic boot is NOT possible)
 *
 * User permissions for programming will still be checked.
 *
 * @note
 * This option bit will only be accepted, if also activated in HSM SW build configuration.
 * Otherwise this option will cause a @ref ecy_hsm_CSAI_ERR_INVALID_PARAM
 */
#define ecy_hsm_CSAI_SECFLASH_OPT_INSECURE             (0x80000000UL)

/** Bit mask of secure flash options */
typedef uint32 ecy_hsm_Csai_SecFlash_FlashOptBmT;

/** @} */ // GROUP_CSAI_SECFLASH_OPTIONS

/**
 * @addtogroup GROUP_CSAI_SECFLASH_SEQUENCE
 * @{
 * Functions for secure HSM flash programming
 */

/**
 * @brief Supported signed header types.
 *
 * @details
 * Each type implies a packed binary structure to be passed to ecy_hsm_Csai_SecFlash_VerifySignedHeader() as pointer in
 * @ref ecy_hsm_Csai_SignedHeaderRefT
 *
 * Signed headers contain security relevant parameters such as hashes of the core application, configuration area and bootloader
 * as well as a hash of the entire update container. The authenticity of the signed header will be verified before the update.
 * After flashing the configuration area, the bootloader and core application the hashes will be recalculated compared with these from
 * this signed header.
 *
 * @note Must be provided in big endian order to the HSM.
 */
typedef enum ecy_hsm_Csai_SignedHeaderType
{
    /**
     * @brief Standard signed header for HSM update purposes.
     *
     * @details
     * <table>
     *  <caption>ecy_hsm_CSAI_SIGNED_HEADER_STANDARD data structure</caption>
     *  <tr><th> Field                               <th> Size [bytes]  <th> Description
     *  <tr><td> Module ID                           <td>   2           <td> Module ID, must match entry in HSM Info Block
     *  <tr><td> HSM Bootloader message digest       <td>  32           <td> This message digest is a SHA256 security parameter that is
     *                                                                       primarily used to verify the integrity of the configuration
     *                                                                       area and the bootloader software image after it is decrypted
     *                                                                       (if required) and programmed into the flash memory. The content
     *                                                                       of this field is identical to the Message Digest of Plaintext
     *                                                                       HSM Bootloader parameter defined in the HSM Bootloader SW Info
     *  <tr><td> HSM Core App. message digest        <td>  32           <td> This message digest is a SHA256 security parameter that is
     *                                                                       primarily used to verify the integrity of the core application
     *                                                                       software image after it is decrypted (if required) and
     *                                                                       programmed into the flash memory. The content of this field is
     *                                                                       identical to the Message Digest of Plaintext HSM Core parameter
     *                                                                       defined in the HSM Core SW Info in the update container.
     *  <tr><td> Host/HSM Bootloader compat. ID      <td>   2           <td> The host bootloader uses this parameter as a pre-check to
     *                                                                       verify that the HSM bootloader software is compatible with the
     *                                                                       host bootloader software. Not evaluated by HSM.
     *  <tr><td> HSM Bootloader/Core App. compat. ID <td>   2           <td> The HSM bootloader uses this parameter as a pre-check to verify
                                                                             that the HSM application software is compatible with the HSM
                                                                             bootloader software prior to installing the core application.
     *  <tr><td> ECU name                            <td>   8           <td> ASCII representation of the ECU Name.
     *  <tr><td> ECU ID                              <td>  16           <td> ECU identity.
     *  <tr><td> ECU ID extension                    <td>  16           <td> ECU identity extension.
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> HSM not-before-ID                   <td>   2           <td> SM software-Not Before Identifier. This parameter is intended
     *                                                                       to prevent roll back to a previous software version. The HSM
     *                                                                       bootloader and application shall compare the HSM-NBID in this
     *                                                                       field to the currently stored HSM-NBID. The bootloader and
     *                                                                       application shall reject the update if the HSM-NBID in this
     *                                                                       field is less than the current value of the HSM-NBID programmed
     *                                                                       in flash (this ensures a failed update can be tried again).
     *  <tr><td> HSM SW Location Info                <td>  20           <td> The HSM SW Location Info is a structure that contains information about the
     *                                                                       size of the HSM software and its location in the host code flash memory.
     *                                                                       <table>
     *                                                                         <tr><th> Size <th> Description
     *                                                                         <tr><td>   2  <td> Number of regions, @note must currently be 0x02
     *                                                                         <tr><td>   4  <td> Start address of HSM config area and bootloader on host flash
     *                                                                         <tr><td>   4  <td> Size of HSM config area and bootloader
     *                                                                         <tr><td>   4  <td> Start address of HSM core application on host flash
     *                                                                         <tr><td>   4  <td> Size of core application
     *                                                                       </table>
     *  <tr><td> Update container message digest     <td>  32           <td> This message digest is a SHA256 security parameter that is
     *                                                                       primarily used to validate the integrity of the entire HSM
     *                                                                       update container prior to decrypting and programming it into the HSM
     *  <tr><td> Header signer info                  <td> 538           <td> Structure describing the public key to be used for verification
     *                                                                       of the signed header
     *                                                                       <table>
     *                                                                         <tr><th> Size <th> Description
     *                                                                         <tr><td>  16  <td> It is an ECU family name which is embedded in the subject
     *                                                                                            name field of the signing certificate. It identifies group
     *                                                                                            of ECUs for which the Signer Info is applicable. It is
     *                                                                                            used during the programming process to determine if the
     *                                                                                            Signer Info is compatible with the target.
     *                                                                         <tr><td>   8  <td> Unique ID for the entire Signer Info. It is used to select
     *                                                                                            the appropriate signing certificate and key to sign update
     *                                                                                            container.
     *                                                                         <tr><td>   2  <td> Key-Not Before ID. This parameter is intended to prevent
     *                                                                                            roll back to a previous key. HSM bootloader and HSM core
     *                                                                                            application shall reject the update if this value is less
     *                                                                                            than a reference stored in the configuration area.
     *                                                                         <tr><td> 256  <td> RSA-2048 bit or EdDSA key that shall be that shall be used
     *                                                                                            for verification of the signature of the signed header.
     *                                                                         <tr><td> 256  <td> RSA-PKCS 1.5 2048 or Ed25519 signature of the Signer info
     *                                                                                            generated using the root private key.
     *                                                                       </table>
     *  <tr><td> HSM header signature                <td> 256           <td> Signature over all preceding signed header fields
     * </table>
     */
    ecy_hsm_CSAI_SIGNED_HEADER_STANDARD = 1u,

    /**
     * @brief Standard signed header for host application update purposes.
     *
     * @details
     * <table>
     *  <caption>ecy_hsm_CSAI_HOST_APP_SIGNED_HEADER_STANDARD data structure</caption>
     *  <tr><th> Field                               <th> Size [bytes]  <th> Description
     *  <tr><td> Module ID                           <td>   2           <td> Module ID
     *  <tr><td> Software Compatibility ID.          <td>   2           <td> Software Compatibility ID. The host bootloader uses this parameter as
     *                                                                       a pre-check to verify if the application software is compatible
     *                                                                       with the bootloader software.
     *  <tr><td> ECU name                            <td>   8           <td> ASCII representation of the ECU Name.
     *  <tr><td> ECU ID                              <td>  16           <td> ECU identity.
     *                                                                       If the module is intended for a specific ECU then this parameter shall be equal
     *                                                                       to the specific ECU ID with a specific module region code.
     *                                                                       If the module is intended for all ECUs then this parameter shall be equal
     *                                                                       to all zero (0's), excluding the region code within the ECU ID.
     *  <tr><td> ECU ID extension                    <td>  16           <td> ECU identity extension.
     *                                                                       If the module is intended for a specific ECU, this parameter will be valid.
     *                                                                       If the module is for all ECUs, this parameter shall be equal to all zero (0's)
     *                                                                       and this parameter could be ignored.
     *  <tr><td> App-NBID                            <td>  16           <td> Application software- Not Before Identifier.
     *                                                                       This parameter is intended to prevent roll back to a previous software version,
     *                                                                       if it is determined that the new software version includes security fixes.
     *                                                                       The bootloader shall compare the App-NBID in this field to the current App-NBID
     *                                                                       as known to the bootloader. The bootloader shall reject the software
     *                                                                       if the App-NBID in this field is less than the current value of the
     *                                                                       application software App-NBID programmed in the flash.
     *  <tr><td> App SW Location Info                <td>  20           <td> The App SW Location Info is a structure that contains information
     *                                                                       about the application software location in memory.
     *                                                                       <table>
     *                                                                         <tr><th> Size <th> Description
     *                                                                         <tr><td>   2     <td> Number of regions, n.
     *                                                                         <tr><td>   4*n   <td> App SW region Start address of HSM config area and bootloader on host flash
     *                                                                         <tr><td>   4*n   <td> Size of the SW region
     *                                                                       </table>
     *  <tr><td> Host SW App. message digest        <td>  32            <td> The Message Digest is a SHA256 security parameter that is primary used to validate
     *                                                                       the integrity of the application software image after it is programmed into the flash memory.
     *  <tr><td> Header signer info                 <td> 538            <td> Structure describing the public key to be used for verification
     *                                                                       of the signed header
     *                                                                       <table>
     *                                                                         <tr><th> Size <th> Description
     *                                                                         <tr><td>  16  <td> It is an ECU family name which is embedded in the subject
     *                                                                                            name field of the signing certificate. It identifies group
     *                                                                                            of ECUs for which the Signer Info is applicable. It is
     *                                                                                            used during the programming process to determine if the
     *                                                                                            Signer Info is compatible with the target.
     *                                                                         <tr><td>   8  <td> Unique ID for the entire Signer Info. It is used to select
     *                                                                                            the appropriate signing certificate and key to sign update
     *                                                                                            container.
     *                                                                         <tr><td>   2  <td> Key-Not Before ID. This parameter is intended to prevent
     *                                                                                            roll back to a previous key. HSM bootloader and HSM core
     *                                                                                            application shall reject the update if this value is less
     *                                                                                            than a reference stored in the configuration area.
     *                                                                         <tr><td> 256  <td> RSA-2048 bit or EdDSA key that shall be that shall be used
     *                                                                                            for verification of the signature of the signed header.
     *                                                                         <tr><td> 256  <td> RSA-PKCS 1.5 2048 or Ed25519 signature of the Signer info
     *                                                                                            generated using the root private key.
     *                                                                       </table>
     *  <tr><td> Host App header signature          <td> 256            <td> Signature over all preceding signed header fields
     * </table>
     */
    ecy_hsm_CSAI_HOST_APP_SIGNED_HEADER_STANDARD = 2u,

    /**
     * @brief Regional bit-difference signed header for host application update purposes.
     *
     * @details
     * <table>
     *  <caption>ecy_hsm_CSAI_HOST_APP_SIGNED_HEADER_BIT_DIFFERENCE data structure</caption>
     *  <tr><th> Field                               <th> Size [bytes]  <th> Description
     *  <tr><td> Module ID                           <td>   2           <td> Module ID
     *  <tr><td> Msg Digest of Full "To Be" Raw Data <td>   32           <td> The Message Digest is a SHA256 security parameter that is primary used
     *                                                                       to validate the integrity of the application software image after
     *                                                                       it is programmed into the flash memory.
     *  <tr><td> Software Compatibility ID.          <td>   2           <td> Software Compatibility ID. The host bootloader uses this parameter as
     *                                                                       a pre-check to verify if the application software is compatible
     *                                                                       with the bootloader software.
     *  <tr><td> ECU name                            <td>   8           <td> ASCII representation of the ECU Name.
     *  <tr><td> ECU ID                              <td>  16           <td> ECU identity.
     *                                                                       If the module is intended for a specific ECU then this parameter shall be equal
     *                                                                       to the specific ECU ID with a specific module region code.
     *                                                                       If the module is intended for all ECUs then this parameter shall be equal
     *                                                                       to all zero (0's), excluding the region code within the ECU ID.
     *  <tr><td> ECU ID extension                    <td>  16           <td> ECU identity extension.
     *                                                                       If the module is intended for a specific ECU, this parameter will be valid.
     *                                                                       If the module is for all ECUs, this parameter shall be equal to all zero (0's)
     *                                                                       and this parameter could be ignored.
     *  <tr><td> App-NBID                            <td>  16           <td> Application software- Not Before Identifier.
     *                                                                       This parameter is intended to prevent roll back to a previous software version,
     *                                                                       if it is determined that the new software version includes security fixes.
     *                                                                       The bootloader shall compare the App-NBID in this field to the current App-NBID
     *                                                                       as known to the bootloader. The bootloader shall reject the software
     *                                                                       if the App-NBID in this field is less than the current value of the
     *                                                                       application software App-NBID programmed in the flash.
     *  <tr><td> App SW Location Info                <td>  20           <td> The App SW Location Info is a structure that contains information
     *                                                                       about the application software location in memory.
     *                                                                       <table>
     *                                                                         <tr><th> Size <th> Description
     *                                                                         <tr><td>   2     <td> Number of regions, n.
     *                                                                         <tr><td>   4*n   <td> App SW region Start address of HSM config area and bootloader on host flash
     *                                                                         <tr><td>   4*n   <td> Size of the SW region
     *                                                                       </table>
     *  <tr><td> Msg Digest of Bit-diff Envelope    <td>  32            <td> The Message Digest is a SHA256 security parameter that is primary used
     *                                                                       to validate the integrity of the bit-difference data in an envelope
     *                                                                       sent to the bootloader.
     *  <tr><td> Header signer info                 <td> 538            <td> Structure describing the public key to be used for verification
     *                                                                       of the signed header
     *                                                                       <table>
     *                                                                         <tr><th> Size <th> Description
     *                                                                         <tr><td>  16  <td> It is an ECU family name which is embedded in the subject
     *                                                                                            name field of the signing certificate. It identifies group
     *                                                                                            of ECUs for which the Signer Info is applicable. It is
     *                                                                                            used during the programming process to determine if the
     *                                                                                            Signer Info is compatible with the target.
     *                                                                         <tr><td>   8  <td> Unique ID for the entire Signer Info. It is used to select
     *                                                                                            the appropriate signing certificate and key to sign update
     *                                                                                            container.
     *                                                                         <tr><td>   2  <td> Key-Not Before ID. This parameter is intended to prevent
     *                                                                                            roll back to a previous key. HSM bootloader and HSM core
     *                                                                                            application shall reject the update if this value is less
     *                                                                                            than a reference stored in the configuration area.
     *                                                                         <tr><td> 256  <td> RSA-2048 bit or EdDSA key that shall be that shall be used
     *                                                                                            for verification of the signature of the signed header.
     *                                                                         <tr><td> 256  <td> RSA-PKCS 1.5 2048 or Ed25519 signature of the Signer info
     *                                                                                            generated using the root private key.
     *                                                                       </table>
     *  <tr><td> Host App header signature          <td> 256            <td> Signature over all preceding signed header fields
     * </table>
     */
    ecy_hsm_CSAI_HOST_APP_SIGNED_HEADER_BIT_DIFFERENCE = 3u,

    /**
     * @brief Standard signed header for host calibration data update purposes.
     *
     * @details
     * <table>
     *  <caption>ecy_hsm_CSAI_HOST_CALIB_DATA_SIGNED_HEADER_STANDARD data structure</caption>
     *  <tr><th> Field                               <th> Size [bytes]  <th> Description
     *  <tr><td> Module ID                           <td>   2           <td> Module ID
     *  <tr><td> Calibration data Compatibility ID   <td>   2           <td>  Calibration Compatibility ID.
     *                                                                       The bootloader uses this parameter as a pre-check to verify whether
     *                                                                       the calibration data is compatible with the programmed application software.
     *  <tr><td> ECU name                            <td>   8           <td> ASCII representation of the ECU Name.
     *  <tr><td> ECU ID                              <td>  16           <td> ECU identity.
     *                                                                       If the module is intended for a specific ECU then this parameter shall be equal
     *                                                                       to the specific ECU ID with a specific module region code.
     *                                                                       If the module is intended for all ECUs then this parameter shall be equal
     *                                                                       to all zero (0's), excluding the region code within the ECU ID.
     *  <tr><td> ECU ID extension                    <td>  16           <td> ECU identity extension.
     *                                                                       If the module is intended for a specific ECU, this parameter will be valid.
     *                                                                       If the module is for all ECUs, this parameter shall be equal to all zero (0's)
     *                                                                       and this parameter could be ignored.
     *  <tr><td> Calibration data message digest     <td>  32           <td> The Message Digest is a SHA256 security parameter that is primary used to validate
     *                                                                       the integrity of the calibration data after it is programmed into the flash memory.
     *  <tr><td> Header signer info                  <td> 538           <td> Structure describing the public key to be used for verification
     *                                                                       of the signed header
     *                                                                       <table>
     *                                                                         <tr><th> Size <th> Description
     *                                                                         <tr><td>  16  <td> It is an ECU family name which is embedded in the subject
     *                                                                                            name field of the signing certificate. It identifies group
     *                                                                                            of ECUs for which the Signer Info is applicable. It is
     *                                                                                            used during the programming process to determine if the
     *                                                                                            Signer Info is compatible with the target.
     *                                                                         <tr><td>   8  <td> Unique ID for the entire Signer Info. It is used to select
     *                                                                                            the appropriate signing certificate and key to sign update
     *                                                                                            container.
     *                                                                         <tr><td>   2  <td> Key-Not Before ID. This parameter is intended to prevent
     *                                                                                            roll back to a previous key. HSM bootloader and HSM core
     *                                                                                            application shall reject the update if this value is less
     *                                                                                            than a reference stored in the configuration area.
     *                                                                         <tr><td> 256  <td> RSA-2048 bit or EdDSA key that shall be that shall be used
     *                                                                                            for verification of the signature of the signed header.
     *                                                                         <tr><td> 256  <td> RSA-PKCS 1.5 2048 or Ed25519 signature of the Signer info
     *                                                                                            generated using the root private key.
     *                                                                       </table>
     *  <tr><td> Calibration data header signature   <td> 256            <td> Signature over all preceding signed header fields
     * </table>
     */
    ecy_hsm_CSAI_HOST_CALIB_DATA_SIGNED_HEADER_STANDARD = 4u,

    /**
     * @brief Regional bit-difference signed header for host calibration data update purposes.
     *
     * @details
     * <table>
     *  <caption>ecy_hsm_CSAI_HOST_CALIB_DATA_SIGNED_HEADER_BIT_DIFFERENCE data structure</caption>
     *  <tr><th> Field                               <th> Size [bytes]  <th> Description
     *  <tr><td> Module ID                           <td>   2           <td> Module ID
     *  <tr><td> Msg Digest of Full "To Be" Raw Data <td>   32          <td> The Message Digest is a SHA256 security parameter that is primary used
     *                                                                       to validate the integrity of the application software image after
     *                                                                       it is programmed into the flash memory.
     *  <tr><td> Calibration data Compatibility ID   <td>   2           <td>  Calibration Compatibility ID.
     *                                                                       The bootloader uses this parameter as a pre-check to verify whether
     *                                                                       the calibration data is compatible with the programmed application software.
     *  <tr><td> ECU name                            <td>   8           <td> ASCII representation of the ECU Name.
     *  <tr><td> ECU ID                              <td>  16           <td> ECU identity.
     *                                                                       If the module is intended for a specific ECU then this parameter shall be equal
     *                                                                       to the specific ECU ID with a specific module region code.
     *                                                                       If the module is intended for all ECUs then this parameter shall be equal
     *                                                                       to all zero (0's), excluding the region code within the ECU ID.
     *  <tr><td> ECU ID extension                    <td>  16           <td> ECU identity extension.
     *                                                                       If the module is intended for a specific ECU, this parameter will be valid.
     *                                                                       If the module is for all ECUs, this parameter shall be equal to all zero (0's)
     *                                                                       and this parameter could be ignored.
     *  <tr><td> Msg Digest of Bit-diff Envelope    <td>  32            <td> The Message Digest is a SHA256 security parameter that is primary used
     *                                                                       to validate the integrity of the bit-difference data in an envelope
     *                                                                       sent to the bootloader.
     *  <tr><td> Header signer info                 <td> 538            <td> Structure describing the public key to be used for verification
     *                                                                       of the signed header
     *                                                                       <table>
     *                                                                         <tr><th> Size <th> Description
     *                                                                         <tr><td>  16  <td> It is an ECU family name which is embedded in the subject
     *                                                                                            name field of the signing certificate. It identifies group
     *                                                                                            of ECUs for which the Signer Info is applicable. It is
     *                                                                                            used during the programming process to determine if the
     *                                                                                            Signer Info is compatible with the target.
     *                                                                         <tr><td>   8  <td> Unique ID for the entire Signer Info. It is used to select
     *                                                                                            the appropriate signing certificate and key to sign update
     *                                                                                            container.
     *                                                                         <tr><td>   2  <td> Key-Not Before ID. This parameter is intended to prevent
     *                                                                                            roll back to a previous key. HSM bootloader and HSM core
     *                                                                                            application shall reject the update if this value is less
     *                                                                                            than a reference stored in the configuration area.
     *                                                                         <tr><td> 256  <td> RSA-2048 bit or EdDSA key that shall be that shall be used
     *                                                                                            for verification of the signature of the signed header.
     *                                                                         <tr><td> 256  <td> RSA-PKCS 1.5 2048 or Ed25519 signature of the Signer info
     *                                                                                            generated using the root private key.
     *                                                                       </table>
     *  <tr><td> Region bit-diff calibration data header signature  <td> 256            <td> Signature over all preceding signed header fields
     * </table>
     */
    ecy_hsm_CSAI_HOST_CALIB_DATA_SIGNED_HEADER_BIT_DIFFERENCE = 5u,

    /**
     * @brief Standard signed header for Signature Bypass Authorization Tickets
     *
     * @details
     * <table>
     *  <caption>ecy_hsm_CSAI_SBAT_SIGNED_HEADER_STANDARD data structure</caption>
     *  <tr><th> Field                               <th> Size [bytes]  <th> Description
     *  <tr><td> Module ID                           <td>   2           <td> Module ID, must match entry in HSM Info Block
     *  <tr><td> ECU name                            <td>   8           <td> ASCII representation of the ECU Name.
     *  <tr><td> ECU ID                              <td>  16           <td> ECU identity.
     *  <tr><td> ECU ID extension                    <td>  16           <td> ECU identity extension.
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> SBAT Creation Count                 <td>   4           <td> Back-office counter that increments every 0.5 minute. This is used for
     *                                                                       One Time Use SBAT (ECU stores Free Running Counter from Last Valid SBAT)
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> SBAT Expiration Count               <td>   4           <td> Back-office counter that results in the SBAT no longer being valid.
     *                                                                       Value of 0 means no expiration based on free running counter
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> App.-NBID                           <td>   2           <td> App-NBID value in the SBAT. The ECU rejects SBAT if this value is less
     *                                                                       than the stored value in the ECU
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> HSM-NBID                            <td>   2           <td> HSM-NBID value in the SBAT. The ECU rejects SBAT if this value is less
     *                                                                       than the stored value in the ECU
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> HSM Bootloader compat. ID           <td>   2           <td> Bootloader Compatibility ID value in the SBAT. The ECU rejects SBAT if
     *                                                                       this value is not equal to the current BCID value in the ECU
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> Security Controls Adjusted          <td>   2           <td> Values that are bit-mapped to enable bypassing of 16 different security controls
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> Unlock Levels Opened                <td>   2           <td> Values that are bit-mapped to enable unlocking of 16 different levels
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> Module Ids Enabled                  <td>   6           <td> Values that restrict secure programming bypass for up to 3 Module IDs
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> Options                             <td>   2           <td> Defines the usage of the SBAT and determines if the SBAT will be
     *                                                                       erased/rejected based on the MEC (Manufacturing Enable Count)
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> Erase Ignition Count                <td>   2           <td> Maximum number of ignition cycles allowed after the SBAT is installed
     *                                                                       before the SBAT is erased. Value of 0x0000 means the SBAT will never be
     *                                                                       erased based on ignition cycles
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> Reserved                            <td>  32           <td> Reserved for future use
     *                                                                       @note field must not be present if Applet FSKA is disabled
     *  <tr><td> Header signer info                  <td> 538           <td> Structure describing the public key to be used for verification
     *                                                                       of the signed header
     *                                                                       <table>
     *                                                                         <tr><th> Size <th> Description
     *                                                                         <tr><td>  16  <td> It is an ECU family name which is embedded in the subject
     *                                                                                            name field of the signing certificate. It identifies group
     *                                                                                            of ECUs for which the Signer Info is applicable. It is
     *                                                                                            used during the programming process to determine if the
     *                                                                                            Signer Info is compatible with the target.
     *                                                                         <tr><td>   8  <td> Unique ID for the entire Signer Info. It is used to select
     *                                                                                            the appropriate signing certificate and key to sign update
     *                                                                                            container.
     *                                                                         <tr><td>   2  <td> Key-Not Before ID. This parameter is intended to prevent
     *                                                                                            roll back to a previous key. HSM bootloader and HSM core
     *                                                                                            application shall reject the update if this value is less
     *                                                                                            than a reference stored in the configuration area.
     *                                                                         <tr><td> 256  <td> RSA-2048 bit or EdDSA key that shall be that shall be used
     *                                                                                            for verification of the signature of the signed header.
     *                                                                         <tr><td> 256  <td> RSA-PKCS 1.5 2048 or Ed25519 signature of the Signer info
     *                                                                                            generated using the root private key.
     *                                                                       </table>
     *  <tr><td> Ticket header signature             <td> 256           <td> Signature over all preceding signed header fields
     *  <tr><td> Ticket header MAC                   <td> 32            <td> MAC over all preceding signed header fields
     *                                                                       @note field must not be present if Applet FSKA is disabled
     * </table>
     */
    ecy_hsm_CSAI_SBAT_SIGNED_HEADER_STANDARD  = 6u,

    /** Value defined to use memory size of uint32 for enums */
    ecy_hsm_CSAI_SIGNED_HEADER_TYPE_RESERVED  = 0x7fffffffu
} ecy_hsm_Csai_SignedHeaderTypeT;

/**
 * Defines a generic signed header that can be used for any signed header type
 */
typedef struct ecy_hsm_Csai_SignedHeaderRef
{
    ecy_hsm_Csai_SignedHeaderTypeT type;          /**< Specifies the type of the signed header below */
    const void*                    pSignedHeader; /**< Signed header */
} ecy_hsm_Csai_SignedHeaderRefT;

/**
 * Defines supported parameter types to be passed to @ref ecy_hsm_Csai_SecFlash_UpdateFromDataContainer
 */
typedef enum ecy_hsm_Csai_UpdateContainerParamType
{
    ecy_hsm_CSAI_UPDATE_FROM_CONTAINER_PARAM_NONE = 0U,     /**< No parameters get passed, the parameters must
                                                                 be set to null pointer */
    ecy_hsm_CSAI_SIGNED_HEADER_PARAM_RESERVED = 0x7fffffffU /**< Value defined to use memory size of uint32 for
                                                                 enums */
} ecy_hsm_Csai_UpdateContainerParamTypeT;

typedef struct ecy_hsm_Csai_UpdateContainerParam
{
    ecy_hsm_Csai_UpdateContainerParamTypeT type;       /**< type of the parameters to be passed */
    void*                                  pCustParam; /**< Custom parameters; currently, it is always a null
                                                            pointer */
} ecy_hsm_Csai_UpdateContainerParamT;

/**
 * Defines the states for the flag used for synchronization between the host bootloader and CycurHSM during update.
 * The underlaying mechanism is required to prevent parallel access of the flash on single-bank targets.
 */
typedef enum ecy_hsm_Csai_SyncFlashAccessUpdate
{
    ecy_hsm_CSAI_UPDATE_FROM_CONTAINER_IDLE = 0x00U,          /**< Host bootloader executes from PFLASH, CycurHSM
                                                                   idles in bootloader RAM-OS and must not perform
                                                                   any write operations to PFLASH */
    ecy_hsm_CSAI_UPDATE_FROM_CONTAINER_START = 0x01U,         /**< Host bootloader executes from RAM, CycurHSM shall
                                                                   continue with the update procedure and start to
                                                                   execute the update state machine */
    ecy_hsm_CSAI_UPDATE_FROM_CONTAINER_FINISHED = 0x02U,      /**< CycurHSM finished installation of the new firmare
                                                                   from the update container in host's memory. The
                                                                   host now can exit the RAM mode and access PFLASH
                                                                   again */
    ecy_hsm_CSAI_UPDATE_FROM_CONTAINER_RESERVED = 0x7fffffffU /**< Defined to use memory size of uint32 for enums */
} ecy_hsm_Csai_SyncFlashAccessUpdateT;

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * [$DD 954]
 * @brief Initialize secure HSM flash programming operation
 * [$Satisfies $ARCH 175] [$Satisfies $ARCH 796]
 * [$Satisfies $SW_ARCH 948] [$Satisfies $SW_ARCH 949] [$Satisfies $SW_ARCH 950]
 * [$Satisfies $SW_ARCH 951]  [$Satisfies $ARCH 947] [$Satisfies $SW_ARCH 952]
 * [$Satisfies $SW_ARCH 945] [$Satisfies $ARCH 953] [$Satisfies $ARCH 447]
 * [$Satisfies $SW_ARCH 5FDF56DC] [$Satisfies $SW_ARCH 66D0DDBD] [$Satisfies $SW_ARCH 48A561FC]
 * [$Satisfies $SW_ARCH F785ADE3]
 *
 * @details This function initializes the secure HSM flash programming operation
 * * check granted user permissions for erase/write access to specified memory region(s)
 * * if access granted:
 *   * unlock read/write protections for specified memory region
 *   * change HSM to RAM-OS operation, since HSM has to run in RAM during flash programming
 *   * wait synchronously for a specified maximum time until the HSM is switched to RAM mode.
 *
 * If the target has bank swap active, but is not a "bankswap only target" (only supported on TC3Hx(_SE) and CYT2BL), an update of both p-flash banks will
 * be initiated if the interface is called with @ref ecy_hsm_CSAI_SECFLASH_OPT_NONE.
 *
 * If the target has bank swap active (only supported on TC3Hx(_SE), ST STSR6, RH850 Dual Map and CYT2BL), it is also possible to call this interface
 * with
 * @ref ecy_hsm_CSAI_SECFLASH_OPT_SOTA to perform an update only on the inactive bank or
 * @ref ecy_hsm_CSAI_SECFLASH_OPT_SYNC to synchronize the inactive bank with the active bank.
 *
 * If the target has independent bank swap (only supported on STSR6) only the inactive bank can be updated, it is only possible to call this interface
 * with
 * @ref ecy_hsm_CSAI_SECFLASH_OPT_SOTA to perform an update only on the inactive bank or
 * @ref ecy_hsm_CSAI_SECFLASH_OPT_SYNC to synchronize the inactive bank with the active bank or
 * @ref ecy_hsm_CSAI_SECFLASH_OPT_SOTA | @ref ecy_hsm_CSAI_SECFLASH_OPT_SWAP to perform an update only on the inactive bank and swap the bank or
 * @ref ecy_hsm_CSAI_SECFLASH_OPT_SOTA | @ref ecy_hsm_CSAI_SECFLASH_OPT_SWAP | @ref ecy_hsm_CSAI_SECFLASH_OPT_HSMCFG to perform an update included HSM
 * config only on the inactive bank and swap the bank.
 * @ref ecy_hsm_CSAI_SECFLASH_OPT_SWAP to swap the bank without making an update at the same time.
 *
 * If the lifecycle state is restricted for configuration area update, it is also required for HSM Firmware Update.
 * When the lifecycle state is not @ref ecy_hsm_CSAI_LC_STATE_PRIVMODEDEV, the HSM Firmware Update component SHALL
 * abort the current update and return @ref ecy_hsm_CSAI_ERR_PRIVILEGE_MISSING.
 * @note Strictly checking lifecycle state when the MW_UPDATE_CONFIGURATION_AREA_ENFORCE_PRIVMODEDEV has been activated.
 * @note This feature is based on Bosch configuration area update, it is only supported for TC3Hx(_SE) and STSR6 targets.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 *                                  In CycurHSM bootloader TC23x supports session 0 only while all other targets support session 0 and 1.
 *                                  This interface must not be called with any other session, even if being in core application
 *                                  mode. Otherwise, after calling this interface, the host might poll for a session the bootloader does not have
 *                                  access to.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 * @note
 * Operation will always be executed on low priority.
 * Parameter will be overridden by implementation.
 * @param[in]   sigScheme           Specification of the @ref ecy_hsm_Csai_SignatureSchemeT to use.
 *                                  (HSM re-programming: ignored, shall be @ref ecy_hsm_CSAI_SIG_NONE)
 * @param[in]   pMemRangeStart      Physical start address of SW memory range to be programmed
 * @param[in]   numBytesMemRange    @deprecated Length of memory range to be programmed (in bytes).
 * @param[in]   bmFlashOptions      Bit mask of secure flashing option bits. @ref GROUP_CSAI_SECFLASH_OPTIONS
 * @param[in]   numMsTimeout        Timeout[ms] when waiting for HSM to run in RAM-mode.
 *                                  if this is 0, no timeout check is done (i.e. endless waiting)
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. HSM is ready for programming sequence.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following error may be returned by a subsequent call to @ref ecy_HSM_GetCounterValue or
 * ecy_HSM_GetElapsedCounterValue
 * - @ref ecy_hsm_CSAI_ERR_NULL_CALLOUT                 At least one of the callouts
 *                                                      @ref ecy_hsm_pCalloutGetCounterValue or
 *                                                      @ref ecy_hsm_pCalloutGetElapsedCounterValue is not set
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                    A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED                   The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED              There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT                An address or pointer parameter was not four-byte aligned
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1                 The AES Accelerator reports an error.
 * - @ref ecy_hsm_CSAI_ERR_PRIVILEGE_MISSING                session/user privilege(s) missing for privileged operation
 *                                                          previous security access did not provide required privileges
 * - @ref ecy_hsm_CSAI_ERR_MEM_PROTECTION                   Memory protection could not be unlocked
 * - @ref ecy_hsm_CSAI_ERR_SECFUNC_LOCKED                   Security critical functions are currently disabled
 *                                                          (see @ref ecy_hsm_Csai_Protection_DisableSecCritFunctions)
 * - @ref ecy_hsm_CSAI_ERR_BANK_SWAP_NOT_SUPPORTED          The context HW feature is disabled
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_Init(ecy_hsm_Csai_SessionHandleT       hSession,
                                                                                       ecy_hsm_Csai_JobPriorityT         priority,
                                                                                       ecy_hsm_Csai_SignatureSchemeT     sigScheme,
                                                                                       uint8 const*                      pMemRangeStart,
                                                                                       uint32                            numBytesMemRange,
                                                                                       ecy_hsm_Csai_SecFlash_FlashOptBmT bmFlashOptions,
                                                                                       uint32                            numMsTimeout,
                                                                                       ecy_hsm_Csai_JobHandleT*          phJob);

/**
 * [$DD 955]
 * [$Satisfies $ARCH 176]
 * @brief Update a running HSM flash programming with another chunk of data.
 *
 * HSM (internally) updates hash and / or CMAC with the new chunk of data
 *
 * @note
 * This function is called asynchronously. It may return @ref ecy_hsm_CSAI_SUCCESS or
 * @ref ecy_hsm_CSAI_FC_BUSY, an expected flow control value.
 * In the latter case, the HSM is still busy in processing
 * the previous chunk and cannot queue more data at the moment.
 * Try again later.
 *
 * @param[in]   hJob            Handle to the initialized job
 * @param[in]   data            Pointer to next chunk of raw data to be programmed.
 * @param[in]   numBytesData    Length (in bytes) of raw data to be programmed.
 *
 * @note
 * This function may to be called once with total length, or multiple times with
 * data chunks.
 *
 * Finalization and result query:
 * The caller finalizes and polls for the result of the digital signature scheme using
 * @ref ecy_hsm_Csai_SecFlash_Finalize.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                The given digital signature scheme is not supported by this HSM
 *                                                      build or @ref ecy_hsm_Csai_SecFlash_Init was called with the
 *                                                      invalid @p bmFlashOptions
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED              The Job is in the wrong state to perform this operation
 * - @ref ecy_hsm_CSAI_ERR_CYCURLIB                     CycurLib returned an error.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 * - @ref ecy_hsm_CSAI_ERR_BANK_SWAP_PATTERNS_FAILED    The patterns could not be written correctly for the bank swap
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_Update(ecy_hsm_Csai_JobHandleT hJob,
                                                                                         const uint8             data[],
                                                                                         uint32                  numBytesData);

/**
 * [$DD 956]
 * @brief Finalize secure HSM flash programming
 * [$Satisfies $ARCH 177] [$Satisfies $SW_ARCH 945]
 *
 * This function finishes a secure HSM flash programming operation.
 *
 * For HSM re-programming the parameters for signature are ignored, since HSM performs internal signature checks
 * using HSM internal keys.
 *
 * * CMAC table for secure-/authentic boot and RTMD function is updated.
 *
 * If the target has bank swap (only supported on TC3Hx(_SE), RH850 U2A Dual Map and CYT2BL) active and @ref ecy_hsm_Csai_SecFlash_Init has been
 * called with with @ref ecy_hsm_CSAI_SECFLASH_OPT_NONE, a synchronization of the inactive bank with the active bank will be performed.
 *
 * @param[in]   hJob                Handle to the initialized job
 * @param[in]   pSigData            Pointer to expected signature buffer
 *                                  (HSM re-programming: ignored, shall be NULL_PTR)
 * @param[in]   numBytesSig         Number of bytes to expected signature
 *                                  (HSM re-programming: ignored, shall be 0)
 * @param[in]   hKey                Key handle for the job, OR a keyId
 *                                  (HSM re-programming: ignored, shall be 0)
 * @param[out]  pResultFlag         Pointer to a buffer to receive the result of the verify operation.
 *                                  0: Verification OK, !=0: Verification Failure
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 * - @ref ecy_hsm_CSAI_ERR_POINTER_ALIGNMENT            An address or pointer parameter was not four-byte aligned
 * - @ref ecy_hsm_CSAI_ERR_AES_ACCELERATOR1             The AES Accelerator reports an error.
 * - @ref ecy_hsm_CSAI_ERR_BANK_SWAP_PATTERNS_FAILED    The patterns could not be written correctly for the bank swap
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_Finalize(ecy_hsm_Csai_JobHandleT hJob,
                                                                                           uint8 const*            pSigData,
                                                                                           uint32                  numBytesSig,
                                                                                           ecy_hsm_Csai_KeyHandleT hKey,
                                                                                           uint32*                 pResultFlag);

/**
 * @brief Cancel secure HSM flash programming job
 *
 * This function cancels a secure HSM flash programming operation.
 *
 * @warning
 * Cancellation of a HSM re-programming session will leave the HSM module in a state where it is not fully operable.
 * The only functions which are available after a cancelled programming job are the necessary
 * functions to do a HSM re-programming again.
 *
 * @param[in]   hJob                Handle to the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                A parameter was invalid
 * - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED               The session was found to be closed
 * - @ref ecy_hsm_CSAI_ERR_JOB_ALREADY_STARTED          There was another job already in progress in the session
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_Cancel(ecy_hsm_Csai_JobHandleT hJob);

/**
 * [$DD 2538]
 * [$Satisfies $SW_ARCH 883]
 * @brief Verifies the signed header before applying an update
 *
 * In general, the signed header is a structure containing the hashes of bootloader, core application and if required
 * also of the configuration area. The signed header gets provisioned to CycurHSM before applying an update. The entire
 * content of the signed header is protected with a signature so after verifying its authenticity, the flashed artifact
 * such as the bootloader gets verified by comparing its intermediately calculated hash with its reference from the
 * signed header.
 *
 * This interface can be used before a non-streaming update scheme, i.e. it must be called before calling
 * @ref ecy_hsm_Csai_SecFlash_UpdateFromDataContainer
 *
 * Further, depending on the definition and the content of the signed header following use cases can be achieved as
 * well:
 * - downgrade protection before modifying the already installed firmware
 * - checking if the firmware to be installed is the same as the already installed one; if this is the case, the
 *   update will not be started
 * - verification of the authenticity and integrity of the full update container, before starting the update operation
 *   (non-streaming update scheme only)
 *
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 *                                  Since in CycurHSM bootloader only sessions 0 and 1 are
 *                                  available, this interface must not be called with any
 *                                  another session, even if being in core application mode.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 *                                  @note Operation is only allowed to run with priority
 *                                  @ref ecy_hsm_CSAI_PRIO_BACKGROUND or @ref ecy_hsm_CSAI_PRIO_LOW
 * @param[in]   pSignedHeaderRef    Signed header to be verified and to be used for the upcoming update
 *                                  cycle.
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. HSM will start verifying the signed header.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_PRIORITY_NOT_ALLOWED       Function was called with prohibited priority.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_SUCCESS                                      Verification of Signer Info Certificate was successful.
 * - @ref ecy_hsm_CSAI_ERR_DATASTORE                                The required core or HSM info containers could not be
 *                                                                  read from the PFLASH.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_MODULE_ID                         The stored module ID in the HSM core info container (PFLASH)
 *                                                                  does not match with the module ID in the incoming signed
 *                                                                  header.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_ECU_NAME                          The ECU name in the HSM info container (PFLASH)
 *                                                                  does not match with the ECU ID in the incoming signed
 *                                                                  header.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_SUBJECT_NAME                      The Subject Name in the Signed Header does not match the
 *                                                                  expected Subject Name stored in the HSM Info block.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_KEY_NBID                          The Signer Info certificate has an older security version
 *                                                                  than the previously used one known to the HSM.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_SIGNERINFO_ROOT_SIG_VERIFICATION  The Signer Info certificate has an invalid signature
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_DOWNGRADE_ATTEMPT                 The signed header refers to an update that has a lower
 *                                                                  version than the installed firmware
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                            An unsupported header type was passed
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                            Invalid session, or null pointer was passed
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_VerifySignedHeader(ecy_hsm_Csai_SessionHandleT    hSession,
                                                                                                     ecy_hsm_Csai_JobPriorityT      priority,
                                                                                                     ecy_hsm_Csai_SignedHeaderRefT* pSignedHeaderRef,
                                                                                                     ecy_hsm_Csai_JobHandleT*       phJob);

/**
 * [$DD 2758]
 * @brief Verifies the host application signed header, regional bit-difference host application signed header,
 *        host calibration data signed header or regional bit-difference host calibration data signed header,
 *        prior to the host application software being updated by the host bootloader.
 *
 * Prior to the host application software being updated by the host bootloader the host bootloader
 * will receive an Application Signed Header from the tester and provide it to the HSM for
 * verification according to GB6002 specification.
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed.
 *                                  Since in CycurHSM bootloader only sessions 0 and 1 are
 *                                  available, this interface must not be called with any
 *                                  another session, even if being in core application mode.
 * @param[in]   priority            Requested scheduling priority for this job on the HSM.
 *                                  @note Operation is only allowed to run with priority
 *                                  @ref ecy_hsm_CSAI_PRIO_BACKGROUND or @ref ecy_hsm_CSAI_PRIO_LOW
 * @param[in]   pSignedHeaderRef    Signed header to be verified and to be used for the upcoming update
 *                                  cycle.
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. HSM will start verifying the signed header.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_PRIORITY_NOT_ALLOWED       Function was called with prohibited priority.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_SUCCESS                                      Verification of Signer Info Certificate was successful.
 * - @ref ecy_hsm_CSAI_ERR_DATASTORE                                The required core or HSM info containers could not be
 *                                                                  read from the PFLASH.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_ECU_NAME                          The ECU name in the HSM info container (PFLASH)
 *                                                                  does not match with the ECU ID in the incoming signed
 *                                                                  header.
 * - @ref ecy_hsm_CSAI_GM_ERR_UPDATE_ECU_ID                            The signed header contains a non-zero ECU ID that does not match the ECU ID
 *                                                                  stored in HSM or host flash memory.
 * - @ref ecy_hsm_CSAI_GM_ERR_UPDATE_ECU_ID_EXT                        The flash file contains a non-zero ECU ID Ext that does not match the ECU ID Ext
 *                                                                  stored in HSM.
 * - @ref ecy_hsm_CSAI_GM_ERR_UPDATE_INVALID_REGION_INFO               Indicates ECU having an unknown or invalid region.
 *                                                                  Regional root public key provisioning is required to re-green and assign
 *                                                                  a new region prior to App or Cal programming.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_SUBJECT_NAME                      The Subject Name in the Signed Header does not match the
 *                                                                  expected Subject Name stored in the HSM Info block.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_KEY_NBID                          The Signer Info certificate has an older security version
 *                                                                  than the previously used one known to the HSM.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_SIGNERINFO_ROOT_SIG_VERIFICATION  The Signer Info certificate has an invalid signature
 * - @ref ecy_hsm_CSAI_GM_ERR_UPDATE_APP_NBID                          The signed header has an older Host Application SW security version
 *                                                                  than the current programmed version.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_SIGNED_HEADER_VER                 The signature on the header is invalid
 * - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED                            An unsupported header type was passed
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                            Invalid session, or null pointer was passed
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT
ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_VerifyHostSignedHeader( ecy_hsm_Csai_SessionHandleT hSession,
                                                                ecy_hsm_Csai_JobPriorityT priority,
                                                                ecy_hsm_Csai_SignedHeaderRefT *pSignedHeaderRef,
                                                                ecy_hsm_Csai_JobHandleT* phJob );

/**
 * @brief Allows the Host to provide a MAC over the signed header to be used for subsequent signed header verifications.
 *
 * @note Only available in bootloader mode.
 *
 * @param[in]  hSession            Handle to the session in which the job will be placed
 * @param[in]  priority            Requested scheduling priority for this job in the HSM.
 * @param[in]  pHeaderMac          MAC over the Signed Header that was previously received from the HSM
 * @param[in]  headerMacLength     Length of the MAC in bytes
 * @param[out] phJob               Receives the job handle of the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              Invalid session, or null pointer or invalid MAC length was passed
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED            Function was called in core mode or feature is not enabled
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_SetSignedHeaderMac(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                     ecy_hsm_Csai_JobPriorityT   priority,
                                                                                                     const uint8                 pHeaderMac[],
                                                                                                     uint32                      headerMacLength,
                                                                                                     ecy_hsm_Csai_JobHandleT*    phJob);
/**
 * [$DD 2386]
 * @brief Allows the Host to retrieve the MAC computed in the HSM over a given signed header.
 * [$Satisfies $SW_ARCH 883]
 *
 * @note Only available in bootloader mode.
 * @note Currently the priority is set to: ecy_hsm_CSAI_PRIO_UNCHANGED
 *
 * @param[in]   hSession            Handle to the session in which the job will be placed
 * @param[out]  pHeaderMac          MAC over the Signed Header that was generated on the HSM
 * @param[out]  pHeaderMacLength    Pointer to return the length of the MAC in bytes
 * @param[out]  phJob               Receives the job handle of the initialized job.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              Invalid session, or null pointer or invalid MAC length was passed
 *   - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED            Function was called in core mode or feature is not enabled
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_RetrieveSignedHeaderMac(ecy_hsm_Csai_SessionHandleT hSession,
                                                                                                          uint8                       pHeaderMac[],
                                                                                                          uint32*                  pHeaderMacLength,
                                                                                                          ecy_hsm_Csai_JobHandleT* phJob);

/**
 * [$DD 2539]
 * [$Satisfies $SW_ARCH 883]
 * @brief Performs full secure HSM flash programming operation for configuration area, bootloader and core application
 * by downloading and installing the update container from host memory.
 *
 * The location of the update container is derived from the previously passed signed header via
 * @ref ecy_hsm_Csai_SecFlash_VerifySignedHeader. In case, a signed header was passed to CycurHSM and it could be
 * verified successfully beforehand, this function performs the secure HSM flash programming operation by:
 *
 * - switching into bootloader RAM-OS operation
 * - performing signed header dependent checks such as certification of a hash of the entire update container file
 * - check granted user permissions for erase/write access to specified memory region(s)
 *   if access granted, unlock read/write protections for specified memory region
 * - parsing the update container that resides in host memory
 * - downloading, decrypting (if required) and flashing the data in chunk-wise manner
 * - after flashing of an entire artifact (config area, boot or core), a hash gets calculated that will be compared with
 *  its reference from the signed header.
 *
 * @param[in]   hJob                        Job handle that was returned by
 *                                          @ref ecy_hsm_Csai_SecFlash_VerifySignedHeader.
 * @param[in]   priority                    Requested scheduling priority for this job on the HSM.
 *                                          @note Operation is only allowed to run with priority
 *                                          @ref ecy_hsm_CSAI_PRIO_BACKGROUND or @ref ecy_hsm_CSAI_PRIO_LOW
 * @param[in,out]   pFlashUsageSyncHost     The user can choose between two synchronization mechanisms in the update
 *                                          process. If @p pFlashUsageSyncHost is a null pointer the update process
 *                                          starts immediately with calling
 *                                          @ref ecy_hsm_Csai_SecFlash_UpdateFromDataContainer. Subsequent calls to
 *                                          @ref ecy_hsm_Csai_PollHandle will indicate the status of the update.
 *
 *                                          Otherwise, a pointer to a synchronization flag can be passed in shared RAM,
 *                                          which is used by the host bootloader and HSM to ensure that the host
 *                                          bootloader does not execute from the flash bank while the HSM is updating
 *                                          the flash bank. The synchronization mechanism is required because of single
 *                                          bank targets and works as follows:
 *                                          1.  Initially the value @ref ecy_hsm_CSAI_UPDATE_FROM_CONTAINER_IDLE must be
 *                                              set by the host bootloader. In this case, CycurHSM idles in bootloader
 *                                              and does not perform any write operations to PFLASH.
 *                                          2.  As soon as the host allows CycurHSM to write its PFLASH by changing the
 *                                              value to @ref ecy_hsm_CSAI_UPDATE_FROM_CONTAINER_START, CycurHSM will
 *                                              continue and update the firmware in PFLASH.
 *                                          3.  After finishing the entire update operation, CycurHSM will notify the
 *                                              host bootloader by setting the value to
 *                                              @ref ecy_hsm_CSAI_UPDATE_FROM_CONTAINER_FINISH.
 * @param[in]   pCustomParam                Use-case specific parameters whose type is specified by
 *                                          @ref ecy_hsm_Csai_UpdateContainerParamTypeT. If type is:
 *                                          - @ref ecy_hsm_CSAI_UPDATE_FROM_CONTAINER_PARAM_NONE, @p pCustParam must
 *                                            be a null pointer
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. HSM is ready for programming sequence.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *   - @ref ecy_hsm_CSAI_ERR_PRIORITY_NOT_ALLOWED       Function was called with prohibited priority.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_SUCCESS                              Update was successful.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                    Invalid job, or null pointer was passed.
 * - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED                  @ref ecy_hsm_Csai_SecFlash_VerifySignedHeader was not called
 *                                                          beforehand or it failed.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_CORE_VER                  Application hash is invalid.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_BOOT_VER                  Bootloader hash is invalid.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_MD_FULL                   Hash of full update container is invalid.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_CORE_BOOT_COMPAT          HSM bootloader is not compatible to HSM application.
 * - @ref ecy_hsm_CSAI_ERR_UPDATE_UNSPECIFIED_ERROR         Another error occurred.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_SecFlash_UpdateFromDataContainer(ecy_hsm_Csai_JobHandleT              hJob,
                                              ecy_hsm_Csai_JobPriorityT            priority,
                                              ecy_hsm_Csai_SyncFlashAccessUpdateT* pFlashUsageSyncHost,
                                              ecy_hsm_Csai_UpdateContainerParamT*  pCustomParam);

/**
 * [$DD 1469]
 * @brief Provide the data of the active p-flash bank to the hsm update state machine to synchronize the inactive bank.
 * [$Satisfies $SW_ARCH 951] [$Satisfies $SW_ARCH 952] [$Satisfies $SW_ARCH 49E75CCC]
 *
 * @details This function is used when SecFlash is needed in a bank swap use case. All available p-flash banks
 * are split into two groups: Bank(group) A and B. Each bank contains a HSM image and the user can determine from which
 * bank it should be executed using UCB Registers. This interface will always update the currently inactive bank with
 * the data of the active bank no matter which bank is active. The HSM recognizes the active/inactive bank by evaluating
 * the @c SCU.STMEM1 register.
 *
 * The user needs to call @ref ecy_hsm_Csai_SecFlash_Init with @p bmFlashOptions=ecy_hsm_CSAI_SECFLASH_OPT_SYNC in
 * advance to enable the synchronization step.
 * He also finalizes the process with @ref ecy_hsm_Csai_SecFlash_Finalize to verify the content of the inactive bank.
 *
 * @note
 * This function shall be called once. A streaming like in @ref ecy_hsm_Csai_SecFlash_Update is not possible.
 *
 * @param[in]   hJob                                    Handle to the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given job handle is invalid. @ref ecy_hsm_Csai_SecFlash_Init
 *                                                      was not called before
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The synchronization was successful.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              A parameter was invalid
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             The session was found to be closed
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given digital signature scheme is not supported by this HSM
 *                                                      build or @ref ecy_hsm_Csai_SecFlash_Init was called with the
 *                                                      invalid @p bmFlashOptions
 *   - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED            The Job is in the wrong state to perform this operation
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                   CycurLib returned an error.
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_SyncInactiveBank(ecy_hsm_Csai_JobHandleT hJob);

/**
 * [$DD 2590]
 *
 * @brief Perform a stand-alone HSM independent bank swap.
 * [$Satisfies $SW_ARCH E88C5A2C]
 *
 * @details This function is used when SecFlash is needed in a HSM independent bank swap use case. This requires
 *          hardware support for independent bank swap for host and HSM. This interface will always performs a
 *          verification of the inactive bank and only if the inactive bank has been successfully validated, the
 *          bank swap is set up for the HSM. The HSM recognizes the active/inactive bank by evaluating a
 *          specific register.
 *
 * The process must be initialized by calling @ref ecy_hsm_Csai_SecFlash_Init with
 * @p bmFlashOptions=ecy_hsm_CSAI_SECFLASH_OPT_SWAP to enable the bank swap steps.
 * The process must be finalized by calling @ref ecy_hsm_Csai_SecFlash_Finalize to verify the content of the inactive bank.
 *
 * @param[in]   hJob                                    Handle to the initialized job
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE             The given job handle is invalid. @ref ecy_hsm_Csai_SecFlash_Init
 *                                                      was not called before
 *   - @ref ecy_hsm_CSAI_FC_BUSY                        Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 *   - @ref ecy_hsm_CSAI_SUCCESS                        The setup for the bank swap was successfully.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM              A parameter was invalid
 *   - @ref ecy_hsm_CSAI_ERR_SESSION_CLOSED             The session was found to be closed
 *   - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED              The given digital signature scheme is not supported by this HSM
 *                                                      build or @ref ecy_hsm_Csai_SecFlash_Init was called with the
 *                                                      invalid @p bmFlashOptions
 *   - @ref ecy_hsm_CSAI_ERR_JOB_NOT_STARTED            The Job is in the wrong state to perform this operation
 *   - @ref ecy_hsm_CSAI_ERR_CYCURLIB                   CycurLib returned an error.
 *   - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION          There has been an attempt to access HSM ram address via the CSAI
 *                                                      interface
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_SecFlash_BankSwap(ecy_hsm_Csai_JobHandleT hJob);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */

/** @} */ // GROUP_SECFLASH_SEQUENCE
/** @} */ // GROUP_SECFLASH
#endif    /* ECY_HSM_CSAI_SECFLASH */
