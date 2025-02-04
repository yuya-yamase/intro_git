/* CanSM_Ucfg_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanSM/Ucfg/HEADER                                           */
/******************************************************************************/

#ifndef CANSM_UCFG_H
#define CANSM_UCFG_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CANSM_UCFG_NETWORK_NUM      (1U)

#define CANSM_UCFG_NETWORKID_0      (0U)

#define CANSM_UCFG_CONTROLLER_NUM_0 (1U)

#define CANSM_UCFG_CONTROLLERID_0   (5U)

#define CANSM_UCFG_PDUID_NUM        (4U)                      /* ^^^ */

#define CANSM_UCFG_IPDUID_0         (0U)
#define CANSM_UCFG_IPDUID_1         (1U)
#define CANSM_UCFG_IPDUID_2         (2U)                      /* ^^^ */
#define CANSM_UCFG_IPDUID_3         (3U)                      /* ^^^ */

#define CANSM_UCFG_CANID_0          (0x18DA17E0UL)            /* ^^^ */
#define CANSM_UCFG_CANID_1          (0x18DBEFE0UL)            /* ^^^ */
#define CANSM_UCFG_CANID_2          (0x18DA17E0UL)            /* ^^^ */
#define CANSM_UCFG_CANID_3          (0x18DBEFE0UL)            /* ^^^ */

#define CANSM_UCFG_BAUDRATE_NUM     (1U)

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CANSM_START_SEC_CST
#include <CanSM_MemMap.h>

extern CONST(CanSM_NetworkSettingConfigType, CANSM_CONFIG_DATA) CanSM_Ucfg_NetworkSetting_Data[CANSM_UCFG_NETWORK_NUM];

extern CONST(CanSM_PduIdSettingConfigType, CANSM_CONFIG_DATA) CanSM_Ucfg_PduIdSetting_Data[CANSM_UCFG_PDUID_NUM];

extern CONST(CanSM_BaudrateSettingConfigType, CANSM_CONFIG_DATA) CanSM_Ucfg_BaudrateSettingConfig[CANSM_UCFG_BAUDRATE_NUM];

#define CANSM_STOP_SEC_CST
#include <CanSM_MemMap.h>


#endif /* CANSM_UCFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

