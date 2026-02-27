/**
 * @file ecy_hsm_cfgdata_types.h
 ***********************************************************************************************
 * @brief Configuration defines and global data types
 *
 ***********************************************************************************************
 * Copyright (C) 2021 ESCRYPT GmbH - All Rights Reserved
 * www.escrypt.com
 **********************************************************************************************/

#ifndef ECY_HSM_CFGDATA_TYPES_H
#define ECY_HSM_CFGDATA_TYPES_H

/* *** prologue  ******************************************************************************/

/* *** includes *******************************************************************************/

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/* *** global data types **********************************************************************/

/**
 * Location of storage
 */
typedef enum ecy_hsm_Csai_StorageLocationTag
{
  ecy_hsm_CSAI_LOCATION_RAM = 0,                        /**< RAM injected data */
  ecy_hsm_CSAI_LOCATION_PFLASH,                         /**< Data stored in PFLASH */
  ecy_hsm_CSAI_LOCATION_DFLASH,                         /**< Data stored in DFLASH */
  ecy_hsm_CSAI_LOCATION_HOST_PFLASH,                    /**< Data stored in HOST PFLASH */

  ecy_hsm_CSAI_STORAGE_LOCATION_RESERVED = 0x7FFFFFFFU  /**< Value defined to use memory size of uint32 for enums   */
} ecy_hsm_Csai_StorageLocationT;

/* *** exported interfaces ********************************************************************/

#endif /* Multiple inclusion lock  */
