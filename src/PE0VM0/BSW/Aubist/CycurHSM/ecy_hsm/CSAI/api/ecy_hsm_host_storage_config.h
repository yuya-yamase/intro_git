/**
 * @file
 ***********************************************************************************************
 * @brief Configuration file for the CycurHSM host storage service.
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2019, all rights reserved
 **********************************************************************************************/

#include "ecy_hsm_basicsrvs.h"
#include "ecy_hsm_csai_vms_pub_hoststorage.h"

/**
 * @addtogroup GROUP_HSM_HOST_STORAGE_API
 * @{
 */

#ifndef HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION
  /** Host storage configuration macro for the number of bytes per cache image section */
  #define HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION 256U
#endif

#ifndef HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS
  /** Host storage configuration macro for the number of cache image sections */
  #define HSM_HOST_STORAGE_CACHE_IMAGE_SECTIONS    ecy_hsm_CEILING(HOST_STORAGE_SIZE, HSM_HOST_STORAGE_CACHE_BYTES_PER_SECTION)
#endif

/**
 * @}
 */
