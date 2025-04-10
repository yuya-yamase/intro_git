/* ComM_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | ComM/HEADER                                                 */
/******************************************************************************/

#ifndef COMM_H
#define COMM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComStack_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define COMM_NO_COMMUNICATION            ((ComM_ModeType)0x00U)
#define COMM_SILENT_COMMUNICATION        ((ComM_ModeType)0x01U)
#define COMM_FULL_COMMUNICATION          ((ComM_ModeType)0x02U)

#define COMM_USER_ID_0                   ((ComM_UserHandleType)0x00U)

#define COMM_BUS_TYPE_CAN                (0x00U)
#define COMM_BUS_TYPE_CDD1               (0x01U)
#define COMM_BUS_TYPE_CDD2               (0x02U)
#define COMM_BUS_TYPE_ETH                (0x03U)
#define COMM_BUS_TYPE_LIN                (0x04U)

#define COMM_API_ID_INIT                 (0x00U)
#define COMM_API_ID_DEINIT               (0x01U)
#define COMM_API_ID_REQUESTCOMMODE       (0x02U)
#define COMM_API_ID_BUSSM_MODEINDICATION (0x03U)
#if (REPROG_CFG_ETH_USE == STD_ON)
#define COMM_API_ID_COMM_ALLOWED         (0x04U)
#define COMM_API_ID_COMM_TIME            (0x05U)
#endif

#define COMM_E_NOT_INITED                (0x00U)
#define COMM_E_WRONG_PARAMETERS          (0x01U)
#define COMM_E_PARAM_POINTER             (0x02U)
#define COMM_E_STATUS                    (0x03U)
#if (REPROG_CFG_ETH_USE == STD_ON)
#define COMM_E_TIMEOUT                   (0x04U)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8 ComM_BusType;
typedef uint8 ComM_UserHandleType;
typedef uint8 ComM_ModeType;

typedef struct {
    ComM_BusType Bus;
    NetworkHandleType NetworkId;
} ComM_NetworkSettingConfigType;

typedef struct {
    P2CONST(ComM_NetworkSettingConfigType, TYPEDEF, COMM_APPL_CONST) NetworkSettingTbl;
    uint8 NetworkNum;
} ComM_NetworkConfigType;

#if (REPROG_CFG_ETH_USE == STD_ON)
typedef struct {
    uint32 SendRcvStartWaitCount;
    uint32 SendRcvStopTimeout;
    uint32 SendRcvComStartTimeout;
} ComM_TimerConfigType;
#endif

typedef struct {
    P2CONST(ComM_NetworkConfigType, TYPEDEF, COMM_APPL_CONST) NetworkInfoTbl;
#if (REPROG_CFG_ETH_USE == STD_ON)
    P2CONST(ComM_TimerConfigType, TYPEDEF, COMM_APPL_CONST) TimerData;
#endif
} ComM_ConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, COMM_CODE_SLOW) ComM_Init
(
    P2CONST(ComM_ConfigType, AUTOMATIC, COMM_APPL_CONST) ConfigPtr
);

FUNC(void, COMM_CODE_SLOW) ComM_DeInit (void);

FUNC(Std_ReturnType, COMM_CODE_SLOW) ComM_RequestComMode
(
    VAR(ComM_UserHandleType, AUTOMATIC) User,
    VAR(ComM_ModeType, AUTOMATIC) ComMode
);

#if (REPROG_CFG_ETH_USE == STD_ON)
FUNC(void, COMM_CODE_SLOW) ComM_CommunicationAllowed
(
    VAR(NetworkHandleType, AUTOMATIC) Channel,
    VAR(boolean, AUTOMATIC) Allowed
);

FUNC(void, COMM_CODE_SLOW) ComM_NotifyCommunicationStart (void);

FUNC(void, COMM_CODE_SLOW) ComM_Time (void);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define COMM_START_SEC_CST
#include <ComM_MemMap.h>

extern CONST(ComM_ConfigType, COMM_CONFIG_DATA) ComM_Cfg_Data;

#define COMM_STOP_SEC_CST
#include <ComM_MemMap.h>


#endif /* COMM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

