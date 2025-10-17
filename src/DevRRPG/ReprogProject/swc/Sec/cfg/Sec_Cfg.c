/* Sec_Cfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Sec/Cfg/CODE                                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Sec.h>
#include "Sec_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SEC_CFG_KEY_PREREGISTERED   (STD_OFF)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SEC_START_SEC_CST_KEY
#include <Sec_MemMap.h>

#if (SEC_CFG_KEY_PREREGISTERED == STD_OFF)
static CONST(uint8, SEC_CONFIG_DATA) Sec_ToolAuthKeyValConfig[SEC_CFG_TOOLAUTHKEY_SIZE] = {
    0xF0U, 0xE1U, 0xD2U, 0xC3U,
    0xB4U, 0xA5U, 0x96U, 0x87U,
    0x78U, 0x69U, 0x5AU, 0x4BU,
    0x3CU, 0x2DU, 0x1EU, 0x0FU
};
#endif

#define SEC_STOP_SEC_CST_KEY
#include <Sec_MemMap.h>

#define SEC_START_SEC_CST
#include <Sec_MemMap.h>

CONST(Sec_ToolAuthKeyConfigType, SEC_CONFIG_DATA) Sec_ToolAuthKeyConfig = {
#if (SEC_CFG_KEY_PREREGISTERED == STD_OFF)
    &Sec_ToolAuthKeyValConfig[0],
#else
    NULL_PTR,
#endif
    SEC_CFG_TOOLAUTHKEY_SIZE,
    1UL,
    0UL,
    SEC_CFG_KEY_PREREGISTERED
};

#define SEC_STOP_SEC_CST
#include <Sec_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
/**** End of File *************************************************************/

