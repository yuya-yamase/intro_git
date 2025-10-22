/**
 * @file ecy_hsm_host_storage.h
 ***********************************************************************************************
 * @brief This header file defines the public interface for managing host storage for CycurHSM
 *
 * @addtogroup GROUP_HSM_HOST_STORAGE_API
 * @{
 *
 * @details
 *
 * The HostStorage feature relies on the host application (outside CycurHSM scope) to provide
 * the routines for storing to / retrieving from non-volatile memory (e.g. flash) data used
 * by CycurHSM. The interface to connect a host application with the HSM is provided here.
 * The data is stored in the HostStorage module in a RAM cache which is organized into sections
 * of fixed size. Sections are identified by a number starting at zero up to a maximum number
 * of supported sections configured for the system (check user manual / porting guide).
 *
 * The operation relies on callouts that are used to:
 *   - inform the host application of the need to provide data to the HostStorage module to
 *     load it into the HostStorage cache
 *   - retrieve data from the HostStorage cache for the data to be stored on the host
 *     application's non-volatile memory medium
 *
 * The callouts are registered during the initialization of the module. The host application
 * must be able to successfully handle any of the callouts from the moment the initialization
 * function (@ref ecy_hsm_HostStorage_Init()) is called, even if it has not returned yet (i.e.
 * the callout may be triggered from within the init function).
 *
 * When the HostStorage module requires data from the non-volatile memory on the host application,
 * it will call the @ref ecy_hsm_pFunctionInitSectionT callout to inform the host of this request.
 * The host application shall call the @ref ecy_hsm_HostStorage_InitSection() function with the
 * relevant data it retrieved from its non-volatile memory. The section number provided to
 * @ref ecy_hsm_HostStorage_InitSection() as argument must be the same as the section number
 * provided as argument to the callout. The @ref ecy_hsm_HostStorage_InitSection() function
 * can be called from within the callout or at a later point.
 *
 * If the host does not have the data available (e.g. it was corrupted or it is the first time
 * the system is starting up and no data exists yet), the host application must still call
 * the @ref ecy_hsm_HostStorage_InitSection(), setting the parameters of this function as
 * specified in the corresponding documentation to signal that data is not available.
 *
 * When the @ref ecy_hsm_pFunctionInitSectionT callout is invoked for a given section, the host
 * application must call the @ref ecy_hsm_HostStorage_InitSection() function to provide the
 * data for the requested section.
 *
 * When the HostStorage module requires data to be persisted by the host application to
 * non-volatile memory, it will call the @ref ecy_hsm_pFunctionPersistSectionT callout to inform
 * the host application of this request. The host application must call the
 * @ref ecy_hsm_HostStorage_ReadSection() function to retrieve the data from the HostStorage
 * module. The host application is responsible for storing the data in non-volatile memory.
 * The section number provided to @ref ecy_hsm_HostStorage_ReadSection() as argument must be
 * the same as the section number provided as argument to the callout.
 *
 * Each time the @ref ecy_hsm_pFunctionPersistSectionT callout is invoked for a given section, it
 * indicates that the content for that section has changed and therefore another
 * @ref ecy_hsm_HostStorage_ReadSection() call must be made to fetch the updated content.
 * Obviously, non-volatile memory writes do not need to be queued; only the latest data needs
 * to be written.
 *
 * The need to persist data to the host application's non-volatile memory is detected by
 * the maintenance routine @ref ecy_hsm_HostStorage_Main(), which shall be called periodically
 * by the host application after the HostStorage module has been initialized. If there is a
 * need to persist data, the registered @ref ecy_hsm_pFunctionPersistSectionT callout will be
 * called and the process previously described shall take place.
 *
 * @note Once the host application has read the data to be persisted, the host application is
 *       responsible to make sure the data gets written to non-volatile memory. The HostStorage
 *       module assumes that this will happen. No notification of write completion is expected
 *       by the HostStorage module.
 *
 * @remarks Unless otherwise noted in any of the interface functions, none of the functions shall
 *          be called concurrently with themselves or other HostStorage functions.
 *
 * @}
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2019, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_HOST_STORAGE_H
#define ECY_HSM_HOST_STORAGE_H

/**
 * @addtogroup GROUP_HSM_HOST_STORAGE_API
 * @{
 */

/* *** includes *******************************************************************************/
#include "Std_Types.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_service.h"

/* *** defines ********************************************************************************/

/** Size of the host storage cache image */
#define HSM_HOST_STORAGE_CACHE_SIZE (HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS * HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION)

/* *** function prototypes ********************************************************************/
/**
 * @brief Callout to signal the host application to initialize a section with data
 *
 * param[in] section Number identifying the section that shall be initialized. Range [0, max sections)
 *
 * @note It is allowed to call the @ref ecy_hsm_HostStorage_InitSection() function from within
 *       this callout.
 *
 * @see @ref ecy_hsm_HostStorage_InitSection()
 */
typedef void (*ecy_hsm_pFunctionInitSectionT)(uint32 section);

/**
 * @brief Callout to signal the host application to persist a section to non-volatile storage
 *
 * param[in] section Number identifying the section that shall be persisted. Range [0, max sections)
 *
 * @note It is allowed to call the @ref ecy_hsm_HostStorage_ReadSection() function from within
 *       this callout.
 *
 * @see @ref ecy_hsm_HostStorage_ReadSection()
 */
typedef void (*ecy_hsm_pFunctionPersistSectionT)(uint32 section);

/** @brief Structure containing callouts for the HSM HostStorage service */
typedef struct HSM_HostStorageCalloutTag {
    ecy_hsm_pFunctionInitSectionT pFunctionInitSection;         /**< Callout to init a cache section */
    ecy_hsm_pFunctionPersistSectionT pFunctionPersistSection;   /**< Callout to persist a cache section */
} HSM_HostStorageCalloutT;

/* *** function prototypes ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * @brief Initialize the HostStorage service.
 * This function will initialize internal parameters, configure callouts,
 * and sequentially signal the client to populate each cache section with HSM data.
 *
 * @note
 * The client must be ready to accept initialization requests signalled via the ecy_hsm_pFunctionInitSectionT callout.
 *
 * @internal
 * Link to detailed description: @ref host_storage_dd_ecy_hsm_HostStorage_Init
 * @endinternal
 *
 * @param[in]   pFunctionInitSection        Callout used to notify the user of this module that a section needs
 *                                          to be initialized. The function pointer must remain valid and callable
 *                                          after the return from this init function
 *
 * @param[in]   pFunctionPersistSection     Callout used to notify the user of this module that a section needs
 *                                          to be persisted. The function pointer must remain valid and callable
 *                                          after the return from this init function
 *
 * @return      ecy_hsm_Csai_ErrorT                             Error/Status code indicating success or failure
 * @retval      ecy_hsm_CSAI_ERR_NULL_CALLOUT                   Callout NULL_PTR (one or more)
 * @retval      ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID     Host storage cache is invalid
 * @retval      ecy_hsm_CSAI_SUCCESS                            Initialization successful
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HostStorage_Init(ecy_hsm_pFunctionInitSectionT    pFunctionInitSection,
                                             ecy_hsm_pFunctionPersistSectionT pFunctionPersistSection);

/**
 * @brief Initialize a section within the HostStorage cache with data.
 *
 * This @ref ecy_hsm_HostStorage_InitSection() function shall be called to initialize a section of the HostStorage
 * cache. If a section is not available (e.g. corruption on caller's storage media), this function shall still be
 * called providing a NULL_PTR as argument for the @p pBuffer parameter to signal the section is not available.
 * In such case the initialization for the section will still be considered complete.
 * If all sections have been initialized, no further initialization will be allowed and the function will fail
 * with a failure-specific error code.
 *
 * @internal
 * Link to detailed description: @ref host_storage_dd_ecy_hsm_HostStorage_InitSection
 * @endinternal
 *
 * @remarks This function can be called from within the callout (@ref ecy_hsm_pFunctionInitSectionT) or from outside
 *          of it. In any other circumstance, this function shall not be called concurrently with itself or other
 *          HostStorage functions to avoid race conditions.
 *
 * @param[in] section       The section to be initialized (as provided to @ref ecy_hsm_pFunctionInitSectionT callout).
 *
 * @param[in] pBuffer       If not a NULL_PTR, it is a pointer to the memory containing the section data that shall be
 *                          used to initialize the cache.
 *                          If NULL_PTR, the HostStorage module will consider that the data is not available.
 *
 * @param[in] bufferLength  Length, in bytes, of the buffer containing the section. If @p pBuffer is NULL_PTR, this
 *                          parameter is ignored.
 *
 * @retval ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID          This module was not yet initialized (@ref
 *                                                              ecy_hsm_HostStorage_Init() not called),
 * @retval ecy_hsm_CSAI_ERR_HOST_STORAGE_ALREADY_INITIALIZED    The initialization of the provided section was already
 *                                                              completed and no further initialization is allowed.
 * @retval ecy_hsm_CSAI_ERR_INVALID_PARAM                       The @p section number or @p bufferLength are out of
 *                                                              range.
 * @retval ecy_hsm_CSAI_SUCCESS                                 The operation completed successfully and the section is
 *                                                              considered initialized.
 *
 * @see ecy_hsm_HostStorage_Init
 * @see ecy_hsm_pFunctionInitSectionT
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HostStorage_InitSection(uint32 section, const uint8 * pBuffer, uint32 bufferLength);

/**
 * @brief Reads a section from the HostStorage cache
 *
 * This @ref ecy_hsm_HostStorage_ReadSection() function shall be called to retrieve a section from the HostStorage
 * cache. The intended use case is for the caller to store the section in non-volatile memory.
 *
 * @internal
 * Link to detailed description: @ref host_storage_dd_ecy_hsm_HostStorage_ReadSection
 * @endinternal
 *
 * @remarks This function can be called from within the callout (@ref ecy_hsm_pFunctionPersistSectionT) or from outside
 *          of it. In any other circumstance, this function shall not be called concurrently with itself or other
 *          HostStorage functions to avoid race conditions.
 *
 * @param[in]  section        The section to be read (as provided to @ref ecy_hsm_pFunctionPersistSectionT callout).
 *
 * @param[in]  pBuffer        Pointer to memory where the read section shall be stored.
 *
 * @param[in]  bufferLength   Length, in bytes, of the buffer where the read section shall be stored.
 *
 * @param[out] pSectionLength Pointer to memory where the number of bytes read is stored upon successful completion of
 *                            this function call. This parameter can be NULL_PTR, in which case number of bytes read
 *                            will not be returned.
 *
 * @retval ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID This module was not initialized yet (@ref
 *                                                     ecy_hsm_HostStorage_Init() not called).
 * @retval ecy_hsm_CSAI_ERR_INVALID_PARAM              The @p section number is out of range or @p pBuffer is a
 *                                                     NULL_PTR.
 * @retval ecy_hsm_CSAI_ERR_BUFFER_TOO_SMALL           The @p bufferLength is to small to allow a complete section
 *                                                     to be stored in the buffer.
 * @retval ecy_hsm_CSAI_SUCCESS                        The operation completed successfully and the section was
 *                                                     successfully read.
 *
 * @see ecy_hsm_HostStorage_Main
 * @see ecy_hsm_pFunctionPersistSectionT
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HostStorage_ReadSection(uint32 section, uint8 * pBuffer, uint32 bufferLength, uint32 * pSectionLength);

/**
 * @brief Verify that all sections are initialized
 *
 * @internal
 * Link to detailed description: @ref host_storage_dd_ecy_hsm_HostStorage_IsInitialized
 * @endinternal
 *
 * @return      boolean
 * @retval      TRUE               All the section have the init status set to TRUE
 * @retval      FALSE              There is at least one section whose init status is set to FALSE
 */
boolean ecy_hsm_HostStorage_IsInitialized(void);

/**
 * @brief Scan for updates and notifies host when changed sections are detected
 *
 * @internal
 * Link to detailed description: @ref host_storage_dd_ecy_hsm_HostStorage_Main
 * @endinternal
 *
 * @retval ecy_hsm_CSAI_ERR_HOST_STORAGE_STATE_INVALID          This module was not initialized yet (@ref
 *                                                              ecy_hsm_HostStorage_Init() not called).
 * @retval ecy_hsm_CSAI_SUCCESS                                 The operation completed successfully and the
 *                                                              host has been informed about the
 *                                                              need to read the content of one or more sections
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HostStorage_Main(void);

/**
 * @brief Configure HostStorage callouts.
 * This function allows the callouts to be re-configured at each boot stage (e.g boot_manager, application).
 *
 * @note
 * The first boot stage must call @ref ecy_hsm_HostStorage_Init to correctly initialize the host storage cache.
 *
 * @internal
 * Link to detailed description: @ref host_storage_dd_ecy_hsm_HostStorage_ConfigureCallouts
 * @endinternal
 *
 * @param[in]   pFunctionInitSection        Callout used to notify the user that a section needs
 *                                          to be initialized. The function pointer must remain valid and callable
 *                                          after returning from this function
 *
 * @param[in]   pFunctionPersistSection     Callout used to notify the user that a section needs
 *                                          to be persisted. The function pointer must remain valid and callable
 *                                          after returning from this function
 *
 * @return      ecy_hsm_Csai_ErrorT                             Error/Status code indicating success or failure
 * @retval      ecy_hsm_CSAI_ERR_NULL_CALLOUT                   Callout NULL_PTR (one or more)
 * @retval      ecy_hsm_CSAI_SUCCESS                            Callouts re-configured successfully
 */
ecy_hsm_Csai_ErrorT ecy_hsm_HostStorage_ConfigureCallouts(ecy_hsm_pFunctionInitSectionT    pFunctionInitSection,
                                                          ecy_hsm_pFunctionPersistSectionT pFunctionPersistSection);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    } /* extern "C" */
#endif
/* *INDENT-ON* */

/**
 * @}
 */
#endif /* Multiple inclusion lock  */
