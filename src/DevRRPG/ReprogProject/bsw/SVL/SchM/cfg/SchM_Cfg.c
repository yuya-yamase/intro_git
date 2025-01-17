/* SchM_Cfg_c_Revision(v6.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | SchM/Cfg/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <SchM.h>
#include "SchM_Cfg.h"

#include <Rte.h>
#include <CanSM.h>
#include <Gdn.h>
#include <MemM.h>
#include <WdgM.h>
#include <CodeFlsIf.h>
#include <ExtCodeFlsIf.h>
#include <CodeRamIf.h>
#include <SubMiconIf.h>
#include <CodeFls.h>
#include <Can.h>

#if (REPROG_CFG_ETH_USE == STD_ON)
#include <BswM_Eth.h>
#include <ComM.h>
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
#include <CxpiWrap_FarcallWrapper.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define SCHM_RPRG_START_SEC_VAR
#include <SchM_Rprg_MemMap.h>

#define SCHM_RPRG_STOP_SEC_VAR
#include <SchM_Rprg_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SCHM_RPRG_START_SEC_CST
#include <SchM_Rprg_MemMap.h>

static CONST(SchM_MainFuncInfoConfigType, SCHM_CONFIG_DATA) SchM_Cfg_MainFuncInfo[] = {
     { &WdgM_MainFunction,                  STD_ON,     STD_ON  }
#if (REPROG_CFG_CAN_DISABLE != STD_ON)
    ,{ &Can_MainFunction_Mode,              STD_ON,     STD_OFF }
#endif
    ,{ &CanSM_MainFunction,                 STD_ON,     STD_OFF }
    ,{ &Rte_RpgLib_MainFunction,            STD_ON,     STD_OFF }
    ,{ &Gdn_MainFunction,                   STD_ON,     STD_OFF }
    ,{ &Rte_RpgMfr_MainFunction,            STD_ON,     STD_OFF }
    ,{ &Rte_RpgSpp_MainFunction,            STD_ON,     STD_OFF }
    ,{ &Rte_Sec_MainFunction,               STD_ON,     STD_OFF }
    ,{ &Rte_Decrypt_MainFunction,           STD_ON,     STD_OFF }
    ,{ &Rte_CmpDecmp_MainFunction,          STD_ON,     STD_OFF }
    ,{ &Rte_PrgChk_MainFunction,            STD_ON,     STD_OFF }
    ,{ &Rte_FscDtct_MainFunction,           STD_ON,     STD_OFF }
    ,{ &Rte_VehInf_MainFunction,            STD_ON,     STD_OFF }
    ,{ &CodeFls_MainFunction,               STD_OFF,    STD_ON  }
    ,{ &CodeFlsIf_MainFunction,             STD_ON,     STD_ON  }
    ,{ &ExtCodeFlsIf_MainFunction,          STD_ON,     STD_OFF }
    ,{ &CodeRamIf_MainFunction,             STD_ON,     STD_OFF }
    ,{ &MemM_MainFunction,                  STD_ON,     STD_OFF }
#if ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON))
    ,{ &SubMiconIf_MainFunction,            STD_ON,     STD_ON  }
#endif
    ,{ &Rte_RpgEvtHk_SchEvt_MainFunction,   STD_ON,     STD_ON  }
};

static CONST(SchM_MainFuncConfigType, SCHM_CONFIG_DATA) SchM_Cfg_MainFuncData = {
    SCHM_CFG_MAINFUNC_NUM,
    &SchM_Cfg_MainFuncInfo[0]
};

static CONST(SchM_TimeFuncInfoConfigType, SCHM_CONFIG_DATA) SchM_Cfg_Time0FuncInfo[] = {
     { &MemErrM_Time,                   STD_ON  }
    ,{ &Rte_RpgEvtHk_SchEvt_TimeHigh,   STD_ON  }
};

static CONST(SchM_TimeFuncConfigType, SCHM_CONFIG_DATA) SchM_Cfg_Time0FuncData = {
    SCHM_CFG_TIME0FUNC_NUM,
    &SchM_Cfg_Time0FuncInfo[0]
};

static CONST(SchM_TimeFuncInfoConfigType, SCHM_CONFIG_DATA) SchM_Cfg_Time1FuncInfo[] = {
     { &Rte_VehInf_Time,                STD_ON  }
    ,{ &Rte_RpgMfr_Time,                STD_ON  }
    ,{ &Rte_RpgSpp_Time,                STD_ON  }
    ,{ &Rte_Decrypt_Time,               STD_ON  }
    ,{ &Rte_CmpDecmp_Time,              STD_ON  }
    ,{ &Rte_FscDtct_Time,               STD_ON  }
    ,{ &Rte_Sec_Time,                   STD_ON  }
    ,{ &Rte_PrgChk_Time,                STD_ON  }
    ,{ &Rte_RpgLib_Time,                STD_ON  }
    ,{ &Gdn_Time,                       STD_ON  }
#if ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON))
    ,{ &SubMiconIf_Time,                STD_ON  }
#endif
    ,{ &Rte_RpgEvtHk_SchEvt_TimeLow,    STD_ON  }
#if (REPROG_CFG_ETH_USE == STD_ON)
    ,{ &ComM_Time,                      STD_ON  }
    ,{ &BswM_Eth_InitDriver,            STD_ON  }
    ,{ &BswM_Eth_MainFunctionHighIn,    STD_ON  }
    ,{ &BswM_Eth_MainFunctionMidCtrl,   STD_ON  }
    ,{ &BswM_Eth_MainFunctionHighOut,   STD_ON  }
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
    ,{ &CxpiWrap_MainFunction_In,       STD_ON  }
    ,{ &CxpiWrap_MainFunction_Prior,    STD_ON  }
    ,{ &CxpiWrap_MainFunction_Out,      STD_ON  }
#endif
};

static CONST(SchM_TimeFuncConfigType, SCHM_CONFIG_DATA) SchM_Cfg_Time1FuncData = {
    SCHM_CFG_TIME1FUNC_NUM,
    &SchM_Cfg_Time1FuncInfo[0]
};

CONST(SchM_ConfigType, SCHM_CONFIG_DATA) SchM_Cfg_Data = {
    &SchM_Cfg_MainFuncData,
    &SchM_Cfg_Time0FuncData,
    &SchM_Cfg_Time1FuncData
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
    ,SCHM_CFG_STAYINBOOT_TIME
#endif
#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
    ,SCHM_CFG_SUBMICON_FINEVT_TX_TIMEOUT
#endif
};

#define SCHM_RPRG_STOP_SEC_CST
#include <SchM_Rprg_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define SCHM_RPRG_START_SEC_CODE
#include <SchM_Rprg_MemMap.h>


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define SCHM_RPRG_STOP_SEC_CODE
#include <SchM_Rprg_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v4.00       :2019/07/16 :Update                                rel.AUBASS */
/*  v5.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v6.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

