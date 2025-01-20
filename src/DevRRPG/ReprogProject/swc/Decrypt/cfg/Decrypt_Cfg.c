/* Decrypt_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Decrypt/Cfg/CODE                                            */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Decrypt.h>
#include "Decrypt_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DECRYPT_CFG_KEY_PREREGISTERED   (STD_OFF)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DECRYPT_START_SEC_CST_KEY
#include <Decrypt_MemMap.h>

#if (DECRYPT_CFG_KEY_PREREGISTERED == STD_OFF)
static CONST(uint8, DECRYPT_CONFIG_DATA) Decrypt_SystemKeyValConfig[DECRYPT_CFG_SYSTEMKEY_SIZE] = {
    0x01U, 0x23U, 0x45U, 0x67U,
    0x89U, 0xABU, 0xCDU, 0xEFU,
    0xFEU, 0xDCU, 0xBAU, 0x98U,
    0x76U, 0x54U, 0x32U, 0x10U
};
#endif

#define DECRYPT_STOP_SEC_CST_KEY
#include <Decrypt_MemMap.h>

#define DECRYPT_START_SEC_CST
#include <Decrypt_MemMap.h>

CONST(Decrypt_SystemKeyConfigType, DECRYPT_CONFIG_DATA) Decrypt_SystemKeyConfig = {
#if (DECRYPT_CFG_KEY_PREREGISTERED == STD_OFF)
    &Decrypt_SystemKeyValConfig[0],
#else
    NULL_PTR,
#endif
    DECRYPT_CFG_SYSTEMKEY_SIZE,
    2UL,
    1UL,
    DECRYPT_CFG_KEY_PREREGISTERED
};

#define DECRYPT_STOP_SEC_CST
#include <Decrypt_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

