/* ComM_Cfg_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | ComM/Cfg/CODE                                               */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComM.h>
#include "ComM_Ucfg.h"
#if (REPROG_CFG_ETH_USE == STD_ON)
#include "ComM_Cfg.h"
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
#define COMM_START_SEC_VAR
#include <ComM_MemMap.h>


#define COMM_STOP_SEC_VAR
#include <ComM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define COMM_START_SEC_CST
#include <ComM_MemMap.h>

static CONST(ComM_NetworkConfigType, COMM_CONFIG_DATA) ComM_Cfg_Network_Data = {
    &ComM_Ucfg_NetworkSetting_Data[0],
    COMM_UCFG_NETWORK_NUM
};

#if (REPROG_CFG_ETH_USE == STD_ON)
static CONST(ComM_TimerConfigType, COMM_CONFIG_DATA) ComM_Cfg_TimerData = {
    COMM_CFG_SENDRCV_START_WAITCNT,
    COMM_CFG_SENDRCV_STOP_TIMEOUT,
    COMM_CFG_COMSTART_TIMEOUT
};
#endif

CONST(ComM_ConfigType, COMM_CONFIG_DATA) ComM_Cfg_Data = {
    &ComM_Cfg_Network_Data
#if (REPROG_CFG_ETH_USE == STD_ON)
    ,&ComM_Cfg_TimerData
#endif
};

#define COMM_STOP_SEC_CST
#include <ComM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define COMM_START_SEC_CODE
#include <ComM_MemMap.h>


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/


#define COMM_STOP_SEC_CODE
#include <ComM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

