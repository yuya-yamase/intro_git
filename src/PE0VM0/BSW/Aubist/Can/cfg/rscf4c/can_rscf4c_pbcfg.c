/* can_rscf4c_pbcfg_c_m10700_v3-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4C/PBCFG/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>
#include "../../cfg/common/can_cv_cfg.h"
#include "../../cfg/rscf4c/can_rscf4c_cfg_ext.h"
#include "../../cfg/rscf4c/can_rscf4c_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_memmap.h>
#include <can/rscf4c/can_rscf4c.h>
#include <can/rscf4c/can_rscf4c_cm_phy.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf4c/can_rscf4c_tb_log.h>
#include <can/rscf4c/can_rscf4c_tb_phy.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*==================================================================*/
/* HOH Configuration Table                                          */
/*==================================================================*/
/* param1 : HOH Number                                              */
/* value  : HOH Configuration                                       */
/*   - u1ControllerID CAN Controller ID associated to HOH           */
/*   - u1MboxNo       MBOX Number associated to HOH                 */
/*------------------------------------------------------------------*/
#if (CAN_CFG_TRANSMIT == CAN_USE)
CanConst CanHohCfgType Can_stHohCfgTbl[ CAN_TB_HOHNUM ] =
{
  /*   u1ControllerID         , u1MboxNo          */
  /*========== User define Area [Start] ==========*/
  /*--- Reception --------------------------------*/
     { (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB002 }   /* [0] HOH228 */
    ,{ (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB003 }   /* [1] HOH229 */
    ,{ (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB004 }   /* [2] HOH230 */
  /*--- Transmission -----------------------------*/
    ,{ (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB001 }   /* [3] HOH233 */
  /*========== User define Area [End] ============*/
};
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/*==================================================================*/
/* Baudrate Switch Configuration Table                              */
/*==================================================================*/
/* param1 : Baudrate Switch Number                                  */
/* value  : Baudrate Switch Configuration                           */
/*   - u4Baudrate       Nominal Baudrate                            */
/*   - u4DataBaudrate   Data Baudrate                               */
/*   - u4BaudrateInfo_1 Baudrate Information1(Dependence on MCU)    */
/*   - u4BaudrateInfo_2 Baudrate Information2(Dependence on MCU)    */
/*   - u4BaudrateInfo_3 Baudrate Information3(Dependence on MCU)    */
/*------------------------------------------------------------------*/
CanConst CanBaudrateSwtCfgType Can_stBaudrateSwtCfgTbl[ CAN_CFG_BRSCFGTBL_SIZE ] =
{
  /* u4Baudrate                     , u4DataBaudrate                  , u4BaudrateInfo_1            , u4BaudrateInfo_2            , u4BaudrateInfo_3              */
  /*================================================================== User define Area [Start] ==================================================================*/
     { (uint32)CAN_500KBPS_10M_PTN2 , (uint32)CAN_DB_500KBPS_10M_PTN2 , (uint32)CAN_BAUDRATEINFO_1_1, (uint32)CAN_BAUDRATEINFO_2_1, (uint32)CAN_BAUDRATEINFO_3_1 }   /* [0] Baudrate Switch Number00 */
  /*================================================================== User define Area [End] ====================================================================*/
};


/* Number of Baudrate Switch Configuration Table Elements (No need to change) */
CanConst uint8 Can_stBRSwtCfgTbl_ARYSIZE = CAN_CFG_BRSCFGTBL_SIZE;


/******************************************************************************/
/*                      USER Configuration                                    */
/******************************************************************************/


/******************************************************************************/
/*                      Static Configuration Table                            */
/******************************************************************************/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
