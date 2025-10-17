/**
 * @file
 ***********************************************************************************************
 * @brief CSAI Interface for the CMAC Generation and Verification on the Host side using the Hardware Crypto Service Provider.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2023, all rights reserved
 ***********************************************************************************************/
/* [$Satisfies $COMPONENT Host_HWCSP_CSAI] */

/* *** prologue  ******************************************************************************/
#ifndef ECY_HSM_CSAI_HOST_HWCSP_MAC_H
#define ECY_HSM_CSAI_HOST_HWCSP_MAC_H

/**
 * @addtogroup GROUP_CSAI_HOST_HWCSP
 * @{
 */

/* *** includes *******************************************************************************/
#include "ecy_hsm_csai_mac.h"
/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/** Structure of extendable parameters for Host Mac Generation V0 */
typedef struct ecy_hsm_Csai_HostHwCsp_MacGen_ParamSet_V0Tag
{
    /** In: Mode of operation (synchronous/asynchronous/quickroute) */
    ecy_hsm_Csai_InterfaceModeT interfaceMode;
    /** In: Mode of operation of the driver (CPU/DMA) */
    ecy_hsm_Csai_HardwareModeT hardwareMode;
    /** In: Message Authentication Code (MAC) algorithms supported by the HostHwCsp */
    ecy_hsm_Csai_MACAlgorithmT algorithm;
    /** In: Handle to a host key available in the HwCsp keystore */
    ecy_hsm_Csai_HostKeyHandleT hKey;
    /** In: Message to generate MAC for. Buffer should be 32-Bit aligned for performance reasons. */
    const uint8* msg;
    /** In: Length of the provided message in bytes */
    uint32 msgLength;
    /** Out: Length of the MAC to generate in bits */
    uint32 macBitLength;
    /** In: Pointer to space where the HostHwCsp can store the result. The length of the buffer must be sufficiently large to hold the number
     * of bits given in the parameter @c macBitLength rounded up to the next multiple of 8. */
    uint8* pMac;
} ecy_hsm_Csai_HostHwCsp_MacGen_ParamSet_V0T;

/* PRQA S 0750 3 */ /* <Deviation: definition of union is appropriate here */
/** Union of extendable data structures */
typedef union ecy_hsm_Csai_HostHwCsp_MacGen_ParamSetTag
{
    /** Data structure for Mac Generation V0 */
    ecy_hsm_Csai_HostHwCsp_MacGen_ParamSet_V0T paramV0;
} ecy_hsm_Csai_HostHwCsp_MacGen_ParamSetT;

/**
 * Enum for versioning the parameter set used by HostHwCsp_MacGenerate CSAI.
 * New IDs for future structures shall be added here.
 */
typedef enum ecy_hsm_Csai_HostHwCsp_MacGen_ParamSetVersionTag
{
    ecy_hsm_CSAI_HOST_HWCSP_MAC_GENERATE_V0  = 0,           /**< Mac Generation V0 */
    ecy_hsm_CSAI_HOST_HWCSP_MAC_GENERATE_MAX = 0x7FFFFFFFUL /**< Reserved to enforce long enums */
} ecy_hsm_Csai_HostHwCsp_MacGen_ParamSetVersionT;

/**
 * Structure of parameter set union and its version for HostHwCsp_MacGenerate CSAI
 */
typedef struct ecy_hsm_Csai_HostHwCsp_MacGen_ParamSetAndVersionTag
{
    /** In:version of the selected structure */
    ecy_hsm_Csai_HostHwCsp_MacGen_ParamSetVersionT paramSetVersion;
    /** In/Out: Union of extendable parameters */
    ecy_hsm_Csai_HostHwCsp_MacGen_ParamSetT hostHwCspMacGenParam;
} ecy_hsm_Csai_HostHwCsp_MacGen_ParamSetAndVersionT;

/** Structure of extendable parameters for Host Mac Verify V0 */
typedef struct ecy_hsm_Csai_HostHwCsp_MacVer_ParamSet_V0Tag
{
    /** In: Mode of operation (synchronous/asynchronous/quickroute) */
    ecy_hsm_Csai_InterfaceModeT interfaceMode;
    /** In: Mode of operation of the driver (CPU/DMA) */
    ecy_hsm_Csai_HardwareModeT hardwareMode;
    /** In: Message Authentication Code (MAC) algorithms supported by the HostHwCsp */
    ecy_hsm_Csai_MACAlgorithmT algorithm;
    /** In: Handle to a host key available in the HwCsp keystore */
    ecy_hsm_Csai_HostKeyHandleT hKey;
    /** In: Message for which to verify the MAC. Buffer should be 32-Bit aligned for performance reasons. */
    const uint8* msg;
    /** In: Length of the provided message in bytes */
    uint32 msgLength;
    /** In: Length of the MAC to verify in bits */
    uint32 macBitLength;
    /** In: Pointer to expected MAC for verification */
    const uint8* pExpectedMac;
    /** Out: Result of the MAC verify operation. Value 0u(FALSE) means MAC does not match and 1u(TRUE) means MAC matches.
     *  @warning
     *  This value is only valid if the return code of the called function is ecy_hsm_CSAI_SUCCESS.
     */
    uint32* pResultFlag;
} ecy_hsm_Csai_HostHwCsp_MacVer_ParamSet_V0T;

/* PRQA S 0750 3 */ /* <Deviation: definition of union is appropriate here */
/** Union of extendable data structures */
typedef union ecy_hsm_Csai_HostHwCsp_MacVer_ParamSetTag
{
    /** Data structure for Mac Verification V0 */
    ecy_hsm_Csai_HostHwCsp_MacVer_ParamSet_V0T paramV0;
} ecy_hsm_Csai_HostHwCsp_MacVer_ParamSetT;

/**
 * Enum for versioning the parameter set used by HostHwCsp_MacVerify CSAI.
 * New IDs for future structures shall be added here.
 */
typedef enum ecy_hsm_Csai_HostHwCsp_MacVer_ParamSetVersionTag
{
    ecy_hsm_CSAI_HOST_HWCSP_MAC_VERIFY_V0  = 0,           /* Mac Verification V0 */
    ecy_hsm_CSAI_HOST_HWCSP_MAC_VERIFY_MAX = 0x7FFFFFFFUL /* Reserved to enforce long enums */
} ecy_hsm_Csai_HostHwCsp_MacVer_ParamSetVersionT;

/**
 * Structure of parameter set union and its version for HostHwCsp_MacVerify CSAI
 */
typedef struct ecy_hsm_Csai_HostHwCsp_MacVer_ParamSetAndVersionTag
{
    /** In: version of the selected structure */
    ecy_hsm_Csai_HostHwCsp_MacVer_ParamSetVersionT paramSetVersion;
    /** In/Out: Union of extendable parameters */
    ecy_hsm_Csai_HostHwCsp_MacVer_ParamSetT hostHwCspMacVerParam;
} ecy_hsm_Csai_HostHwCsp_MacVer_ParamSetAndVersionT;

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * [$DD 2608]
 * @brief
 * Do a complete non-streaming MAC generation on the HostHwCsp.
 * @note Currently only Quickroute/CPU/CMAC is implemented
 *
 * [$Satisfies $SW_ARCH 1155][$Satisfies $SW_ARCH 1220][$Satisfies $SW_ARCH 1179]
 *
 * @param[in]       hostWksp            Host Workspace determines the channel/instance of the HostHwCsp to be used
 * @param[out]      phJob               Receives the job handle of the initialized job. Only used in asynchronous mode, otherwise it must be
 *                                      nullpointer.
 * @param[inout]    pParamSetAndVersion Function specific parameters, see struct declaration
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded.
 *  - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID          Key was not found in HwCsp keystore.
 *  - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED         Invalid Interface mode. Currently only ecy_hsm_CSAI_INTERFACE_MODE_QUICKROUTE is supported
 *  - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED           This combination of Hardware and Interface mode is not supported. IF mode Quickroute needs HW mode
 *                                                  CPU. May also mean MAC Algorithm not supported. Currently only ecy_hsm_CSAI_AES_CMAC is supported.
 *                                                  May also mean that the version ID in pParamSetAndVersion is not supported.
 *                                                  May also mean that this function is not enabled in VMS.
 *  - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE          The hardware found something wrong with the key. The key may not have the appropriate attributes
 *                                                  (CMAC Generation, Validity, Workspace) set.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           A parameter or the whole parameter struct is invalid (nullpointer or out of range).
 *                                                  For Quickroute: phJob was not nullpointer.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HostHwCsp is busy with another job. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT                 HostHwCsp timed out.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE           Unexpected state of the Hardware, for example Overflow flag.
 *  - @ref ecy_hsm_CSAI_ERR_HWCSP                   Hardware reports a problem not covered with the above options
 *  - @ref ecy_hsm_CSAI_ERR_HWCSP_RESOURCE_LOCKED   Concurrent Access attempted, Get() Callout function could not lock resource
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_HostHwCsp_MacGenerate(ecy_hsm_Csai_WorkspaceIdT                          hostWksp,
                                   ecy_hsm_Csai_JobHandleT*                           phJob,
                                   ecy_hsm_Csai_HostHwCsp_MacGen_ParamSetAndVersionT* pParamSetAndVersion);

/**
 * [$DD 2609]
 * @brief
 * Do a complete non-streaming MAC verification on the HostHwCsp.
 * @note Currently only Quickroute is implemented
 *
 * [$Satisfies $SW_ARCH 1157][$Satisfies $SW_ARCH 1220][$Satisfies $SW_ARCH 1179]
 *
 * @param[in]   hostWksp            Host Workspace determines the channel/instance of the HostHwCsp to be used
 * @param[out]  phJob               Receives the job handle of the initialized job. Only used in asynchronous mode, otherwise it must be nullpointer.
 * @param[in]   pParamSetAndVersion Function specific parameters, see struct declaration
 *
 * @return
 *  - @ref ecy_hsm_CSAI_SUCCESS                     The call succeeded.
 *  - @ref ecy_hsm_CSAI_ERR_KEY_ID_INVALID          Key was not found in HwCsp keystore.
 *  - @ref ecy_hsm_CSAI_ERR_NOT_IMPLEMENTED         Invalid Interface mode. Currently only ecy_hsm_CSAI_INTERFACE_MODE_QUICKROUTE is supported
 *  - @ref ecy_hsm_CSAI_ERR_NOT_SUPPORTED           This combination of Hardware and Interface mode is not supported. IF mode Quickroute needs HW mode
 *                                                  CPU. May also mean MAC Algorithm not supported. Currently only ecy_hsm_CSAI_AES_CMAC is supported.
 *                                                  May also mean that the version ID in pParamSetAndVersion is not supported.
 *                                                  May also mean that this function is not enabled in VMS.
 *  - @ref ecy_hsm_CSAI_ERR_WRONG_KEY_TYPE          The hardware found something wrong with the key. The key may not have the appropriate attributes
 *                                                  (CMAC Verification, Validity, Workspace) set.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM           A parameter or the whole parameter struct is invalid (nullpointer or out of range).
 *                                                  For Quickroute: phJob was not nullpointer.
 *  - @ref ecy_hsm_CSAI_FC_BUSY                     The HostHwCsp is busy with another job. Please call again later.
 *  - @ref ecy_hsm_CSAI_ERR_TIMEOUT                 HostHwCsp timed out.
 *  - @ref ecy_hsm_CSAI_ERR_INVALID_STATE           Unexpected state of the Hardware, for example Overflow flag.
 *  - @ref ecy_hsm_CSAI_ERR_HWCSP                   Hardware reports a problem not covered with the above options
 *  - @ref ecy_hsm_CSAI_ERR_HWCSP_RESOURCE_LOCKED   Concurrent Access attempted, Get() Callout function could not lock resource
 *
 * @note
 * The return code only provides information about whether the call succeeded. SUCCESS does not mean that the expected MAC matches the
 * calculated MAC, this is encoded in pResultFlag inside the parameter struct.
 *
 * @warning pResultFlag (inside parameter struct) is only valid if the return code was ecy_hsm_CSAI_SUCCESS.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL
ecy_hsm_Csai_HostHwCsp_MacVerify(ecy_hsm_Csai_WorkspaceIdT                          hostWksp,
                                 ecy_hsm_Csai_JobHandleT*                           phJob,
                                 ecy_hsm_Csai_HostHwCsp_MacVer_ParamSetAndVersionT* pParamSetAndVersion);

/** @} */ // GROUP_CSAI_HOST_HWCSP

#endif /* ECY_HSM_CSAI_HOST_HWCSP_MAC_H */
