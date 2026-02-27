/**
 * @file
 ***********************************************************************************************
 * @brief CSAI HwCsp APIs.
 * This header file is part of the Cryptographic Service Application Interface and specifies
 * functions to control HSM external hardware crypto service providers.
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2023, all rights reserved.
 **********************************************************************************************/
/* [$Satisfies $COMPONENT HWCSP_CSAI] */

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_CSAI_HWCSP_H
# define ECY_HSM_CSAI_HWCSP_H

/**
 * @addtogroup GROUP_CSAI_HWCSP
 * @{
 */

/* *** includes *******************************************************************************/
# include "ecy_hsm_cfgdata_types.h"
# include "ecy_hsm_csai.h"
# include "ecy_hsm_hwcsp_cfg.h"

/* Macros to create workspace bit masks. */
# if (ECY_HSM_VMS_FS_APPLETHWCSP == ENABLED)
/** Macro that creates a bit mask for all workspaces. */
#  define ecy_hsm_CSAI_HWCSP_ALL_WKSPS (ecy_hsm_HwCsp_ALL_WORKSPACES_MASK)
# else
#  define ecy_hsm_CSAI_HWCSP_ALL_WKSPS (0xFFFFFFFFU)
# endif
/** Macro that creates a bit mask for a single workspace. */
# define ecy_hsm_CSAI_HWCSP_WKSP(wksp)                        (1U << (wksp))
/** Macro that creates a bit mask for two workspaces. */
# define ecy_hsm_CSAI_HWCSP_WKSP2(wksp1, wksp2)               (1U << (wksp1)) | (1U << (wksp2))
/** Macro that creates a bit mask for three workspaces. */
# define ecy_hsm_CSAI_HWCSP_WKSP3(wksp1, wksp2, wksp3)        (1U << (wksp1)) | (1U << (wksp2)) | (1U << (wksp3))
/** Macro that creates a bit mask for four workspaces. */
# define ecy_hsm_CSAI_HWCSP_WKSP4(wksp1, wksp2, wksp3, wksp4) (1U << (wksp1)) | (1U << (wksp2)) | (1U << (wksp3)) | (1U << (wksp4))

/** LoadKey parameter struct version 0.*/
typedef struct ecy_hsm_Csai_HwCsp_LoadKey_V0Tag
{
    ecy_hsm_Csai_KeyHandleT      hKey;      /**< [in] HSM key handle or key ID that shall be loaded to the HwCsp keystore. */
    ecy_hsm_Csai_WorkspacesMaskT hostWksps; /**< [in] Bit Mask of the workspaces the key shall be loaded in. */
    ecy_hsm_Csai_HostKeyHandleT* phHostKey; /**< [out] Buffer to store the host key handle. */
} ecy_hsm_Csai_HwCsp_LoadKey_V0T;

/** LoadKey parameter struct version identifiers.*/
typedef enum ecy_hsm_Csai_HwCsp_LoadKey_ParamSetVersion
{
    ecy_hsm_Csai_HwCsp_LoadKey_VID_0    = 0, /**< Version 0 param struct identifier. */
    ecy_hsm_Csai_HwCsp_LoadKey_RESERVED = 0x7FFFFFFF,
} ecy_hsm_Csai_HwCsp_LoadKey_ParamSetVersionT;

/** LoadKey parameter struct union.*/
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_HwCsp_LoadKey_ParamSetUnionTag
{
    ecy_hsm_Csai_HwCsp_LoadKey_V0T paramSet_V0; /**< Version 0 of the parameter struct. */
} ecy_hsm_Csai_HwCsp_LoadKey_ParamSetUnionT;

/** Load Key wrapper structure for interface parameter extensibility. */
typedef struct ecy_hsm_Csai_HwCsp_LoadKey_ParamSetAndVersionTag
{
    ecy_hsm_Csai_HwCsp_LoadKey_ParamSetVersionT paramSetVersion; /**< Param set version identifier. */
    ecy_hsm_Csai_HwCsp_LoadKey_ParamSetUnionT   paramSet;        /**< Param set union. */
} ecy_hsm_Csai_HwCsp_LoadKey_ParamSetAndVersionT;

/** ReleaseKey parameter struct version 0.*/
typedef struct ecy_hsm_Csai_HwCsp_ReleaseKey_V0Tag
{
    ecy_hsm_Csai_WorkspacesMaskT hostWksps; /**< [in] Bit Mask of the workspaces the key shall be released from. */
    ecy_hsm_Csai_HostKeyHandleT  hHostKey;  /**< [in] Host key that shall be released.  */
} ecy_hsm_Csai_HwCsp_ReleaseKey_V0T;

/** ReleaseKey parameter struct version identifiers.*/
typedef enum ecy_hsm_Csai_HwCsp_ReleaseKey_ParamSetVersion
{
    ecy_hsm_Csai_HwCsp_ReleaseKey_VID_0    = 0, /**< Version 0 param struct identifier. */
    ecy_hsm_Csai_HwCsp_ReleaseKey_RESERVED = 0x7FFFFFFF,
} ecy_hsm_Csai_HwCsp_ReleaseKey_ParamSetVersionT;

/** ReleaseKey parameter struct union.*/
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_HwCsp_ReleaseKey_ParamSetUnionTag
{
    ecy_hsm_Csai_HwCsp_ReleaseKey_V0T paramSet_V0; /**< Version 0 of the parameter struct. */
} ecy_hsm_Csai_HwCsp_ReleaseKey_ParamSetUnionT;

/** ReleaseKey wrapper structure for interface parameter extensibility. */
typedef struct ecy_hsm_Csai_HwCsp_ReleaseKey_ParamSetAndVersionTag
{
    ecy_hsm_Csai_HwCsp_ReleaseKey_ParamSetVersionT paramSetVersion; /**< Param set version identifier. */
    ecy_hsm_Csai_HwCsp_ReleaseKey_ParamSetUnionT   paramSet;        /**< Param set union. */
} ecy_hsm_Csai_HwCsp_ReleaseKey_ParamSetAndVersionT;

/** Init parameter struct version 0. (dummy type) */
typedef uint32 ecy_hsm_Csai_HwCsp_Init_V0T;

/**Init parameter struct version identifiers.*/
typedef enum ecy_hsm_Csai_HwCsp_Init_ParamSetVersion
{
    ecy_hsm_Csai_HwCsp_Init_VID_0    = 0, /**< Version 0 param struct identifier. */
    ecy_hsm_Csai_HwCsp_Init_RESERVED = 0x7FFFFFFF,
} ecy_hsm_Csai_HwCsp_Init_ParamSetVersionT;

/** Init parameter struct union.*/
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Csai_HwCsp_Init_ParamSetUnionTag
{
    ecy_hsm_Csai_HwCsp_Init_V0T paramSet_V0; /**< Version 0 of the parameter struct. */
} ecy_hsm_Csai_HwCsp_Init_ParamSetUnionT;

/** Init wrapper structure for interface parameter extensibility. */
typedef struct ecy_hsm_Csai_HwCsp_Init_ParamSetAndVersionTag
{
    ecy_hsm_Csai_HwCsp_Init_ParamSetVersionT paramSetVersion; /**< Param set version identifier. */
    ecy_hsm_Csai_HwCsp_Init_ParamSetUnionT   paramSet;        /**< Param set union. */
} ecy_hsm_Csai_HwCsp_Init_ParamSetAndVersionT;

/**
 * [$DD 2635]
 * Loads a key to the HwCsp's keystore.
 * [$Satisfies $SW_ARCH 3C4609D3]
 *
 * @param[in]  hSession     Handle to an open HSM session.
 * @param[in]  priority     Scheduling priority of the operation on the HSM.
 * @param[out] phJob        Receives the job handle of the initialized job.
 * @param[in, out] pParams  Pointer to the parameter struct .
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS.                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE.            The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY.                       Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                One ore more parameters are invalid.
 * - @ref ecy_hsm_CSAI_ERR_KEY_WRONG_SESSION            The required key has not been loaded into the session
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface.
 * - @ref ecy_hsm_CSAI_ERR_HWCSP                        The HwCsp reported an error.
 * - @ref ecy_hsm_CSAI_ERR_TIMEOUT                      An unexpected timeout occurred.
 * - @ref ecy_hsm_CSAI_ERR_HWCSP_UNINITIALIZED          HwCsp is not initialized.
 *
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_HwCsp_LoadKey(ecy_hsm_Csai_SessionHandleT                     hSession,
                                                                                       ecy_hsm_Csai_JobPriorityT                       priority,
                                                                                       ecy_hsm_Csai_JobHandleT*                        phJob,
                                                                                       ecy_hsm_Csai_HwCsp_LoadKey_ParamSetAndVersionT* pParams);

/**
 * [$DD 2636]
 * Releases a key from the HwCsp's keystore.
 * [$Satisfies $SW_ARCH 70E2AB24]
 *
 * @param[in]  hSession     Handle to an open HSM session.
 * @param[in]  priority     Scheduling priority of the operation on the HSM.
 * @param[out] phJob        Receives the job handle of the initialized job.
 * @param[in, out] pParams  Pointer to parameter struct.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS.                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE.            The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY.                       Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                One ore more parameters are invalid.
 * - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE               The host key handle is invalid
 * - @ref ecy_hsm_CSAI_ERR_KEY_WRONG_WORKSPACES         The key has not been loaded into these workspaces
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface.
 * - @ref ecy_hsm_CSAI_ERR_HWCSP                        The HwCsp reported an error.
 * - @ref ecy_hsm_CSAI_ERR_TIMEOUT                      An unexpected timeout occurred.
 * - @ref ecy_hsm_CSAI_ERR_HWCSP_UNINITIALIZED          HwCsp is not initialized.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_HwCsp_ReleaseKey(ecy_hsm_Csai_SessionHandleT                        hSession,
                                                                                          ecy_hsm_Csai_JobPriorityT                          priority,
                                                                                          ecy_hsm_Csai_JobHandleT*                           phJob,
                                                                                          ecy_hsm_Csai_HwCsp_ReleaseKey_ParamSetAndVersionT* pParams);

/**
 * [$DD 2634]
 * Initializes the HwCsp module.
 * [$Satisfies $SW_ARCH 3774E41A]
 *
 * @param[in] hSession      Handle to an open HSM session.
 * @param[in] priority      Scheduling priority of the operation on the HSM.
 * @param[out] phJob        Receives the job handle of the initialized job.
 * @param[in, out] pParams  Pointer to parameter struct.
 *
 * @return
 *   - @ref ecy_hsm_CSAI_SUCCESS.                       The call succeeded. The operation is pending on the HSM.
 *   - @ref ecy_hsm_CSAI_ERR_INVALID_HANDLE.            The given session handle is invalid.
 *   - @ref ecy_hsm_CSAI_FC_BUSY.                       Another job is still pending completion in this session.
 *                                                      Either finish the previous job or cancel the running job
 *                                                      using @ref ecy_hsm_Csai_CancelJob.
 *
 * @note
 * The following errors may be returned by a subsequent call to @ref ecy_hsm_Csai_PollHandle
 * - @ref ecy_hsm_CSAI_ERR_INVALID_PARAM                One ore more parameters are invalid.
 * - @ref ecy_hsm_CSAI_ERR_ADDRESS_VIOLATION            There has been an attempt to access HSM ram address via the
 *                                                      CSAI interface
 * - @ref ecy_hsm_CSAI_ERR_HWCSP                        The HwCsp reported an error.
 */
ecy_hsm_CSAI_DECLSPEC ecy_hsm_Csai_ErrorT ecy_hsm_CSAI_CALL ecy_hsm_Csai_HwCsp_Init(ecy_hsm_Csai_SessionHandleT                  hSession,
                                                                                    ecy_hsm_Csai_JobPriorityT                    priority,
                                                                                    ecy_hsm_Csai_JobHandleT*                     phJob,
                                                                                    ecy_hsm_Csai_HwCsp_Init_ParamSetAndVersionT* pParams);

#endif

/**
 * @}
 */
