/* IntHndlr_Local_h_Revision(v4.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | IntHndlr/Local/HEADER                                       */
/******************************************************************************/
#ifndef INTHNDLR_LOCAL_H
#define INTHNDLR_LOCAL_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include "IntHndlr_Cfg.h"
#include "IntHndlr_Ucfg.h"

#if (REPROG_CFG_CXPI_USE == STD_ON)
#include "IntHndlr_Cxpi_Local.h"
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32  CanChannelNo;
    uint32  CanIntRxCode;
    uint32  CanIntRxCodeNotify;
    uint32  CanIntTxCode;
    uint32  CanIntTxCodeNotify;
} IntHndlr_CanInfoConfigType;

typedef struct {
    uint32  CanNum;
    P2CONST(IntHndlr_CanInfoConfigType, TYPEDEF, INTHNDLR_APPL_CONST) CanInfoPtr;
} IntHndlr_CanConfigType;

typedef struct {
    uint32  Gpt0IntCode;
    uint32  Gpt1IntCode;
} IntHndlr_GptConfigType;

typedef struct {
    uint32  UsrIntCode;
} IntHndlr_UsrInfoConfigType;

typedef struct {
    uint32  UsrNum;
    P2CONST(IntHndlr_UsrInfoConfigType, TYPEDEF, INTHNDLR_APPL_CONST) UsrInfoPtr;
} IntHndlr_UsrConfigType;

typedef struct {
    P2CONST(IntHndlr_CanConfigType, TYPEDEF, INTHNDLR_APPL_CONST) CanDataPtr;
    P2CONST(IntHndlr_GptConfigType, TYPEDEF, INTHNDLR_APPL_CONST) GptDataPtr;
#if (REPROG_CFG_CXPI_USE == STD_ON)
    P2CONST(IntHndlr_CxpiConfigType, TYPEDEF, INTHNDLR_APPL_CONST) CxpiDataPtr;
#endif
    P2CONST(IntHndlr_UsrConfigType, TYPEDEF, INTHNDLR_APPL_CONST) UsrDataPtr;
} IntHndlr_ConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, INTHNDLR_CODE_FAST) IntHndlr_EIINT_Sub
(
    VAR(uint32, AUTOMATIC) Eiic
);
#if (REPROG_CFG_CXPI_USE == STD_ON)
FUNC(Std_ReturnType, INTHNDLR_CODE_FAST) IntHndlr_Notification_Cxpi
(
    VAR(uint32, AUTOMATIC) Eiic
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define INTHNDLR_START_SEC_CST
#include <IntHndlr_MemMap.h>

extern CONST(IntHndlr_ConfigType, INTHNDLR_CONFIG_DATA) IntHndlr_Cfg_Data;
extern CONST(IntHndlr_CanInfoConfigType, INTHNDLR_CONFIG_DATA) IntHndlr_Ucfg_CanInfo[INTHNDLR_UCFG_CAN_CH_USE_NUM];
extern CONST(IntHndlr_UsrInfoConfigType, INTHNDLR_CONFIG_DATA) IntHndlr_Ucfg_UsrInfo[INTHNDLR_CFG_USR_USE_NUM];

#define INTHNDLR_STOP_SEC_CST
#include <IntHndlr_MemMap.h>


#endif /* INTHNDLR_LOCAL_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/02/13 :Update                                rel.AUBASS */
/*  v3.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v4.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

