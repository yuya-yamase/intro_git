#ifndef ETHSWT_H
#define ETHSWT_H
#include <Std_Types.h>


typedef void	EthSwt_ConfigType;

/********************************************************************************/
/* Structure definitions														*/
/********************************************************************************/
#include "EthSwt_SWIC.h"


/*SwitchIdx*/
#define ETHSWT_SWIC_IDX							((uint8)0)
#define ETHSWT_RSW2_IDX							((uint8)1)

#define EthSwt_Init								EthSwt_SWIC_Init
#define EthSwt_DeInit							EthSwt_SWIC_DeInit
#define EthSwt_SetSwitchPortMode				EthSwt_SWIC_SetSwitchPortMode
#define EthSwt_GetSwitchPortMode				EthSwt_SWIC_GetSwitchPortMode
#define EthSwt_StartSwitchPortAutoNegotiation	EthSwt_SWIC_StartSwitchPortAutoNegotiation
#define EthSwt_CheckWakeup						EthSwt_SWIC_CheckWakeup
#define EthSwt_GetSwitchPortWakeupReason		EthSwt_SWIC_GetSwitchPortWakeupReason
#define EthSwt_GetLinkState						EthSwt_SWIC_GetLinkState
#define EthSwt_GetBaudRate						EthSwt_SWIC_GetBaudRate
#define EthSwt_GetDuplexMode					EthSwt_SWIC_GetDuplexMode
#define EthSwt_GetPortMacAddr					EthSwt_SWIC_GetPortMacAddr
#define EthSwt_GetArlTable						EthSwt_SWIC_GetArlTable
#define EthSwt_GetCounterValues					EthSwt_SWIC_GetCounterValues
#define EthSwt_GetRxStats						EthSwt_SWIC_GetRxStats
#define EthSwt_GetTxStats						EthSwt_SWIC_GetTxStats
#define EthSwt_GetTxErrorCounterValues			EthSwt_SWIC_GetTxErrorCounterValues
#define EthSwt_GetSwitchReg						EthSwt_SWIC_GetSwitchReg
#define EthSwt_SetSwitchReg						EthSwt_SWIC_SetSwitchReg
#define EthSwt_ReadTrcvRegister					EthSwt_SWIC_ReadTrcvRegister
#define EthSwt_WriteTrcvRegister				EthSwt_SWIC_WriteTrcvRegister
#define EthSwt_EnableVlan						EthSwt_SWIC_EnableVlan
#define EthSwt_StoreConfiguration				EthSwt_SWIC_StoreConfiguration
#define EthSwt_ResetConfiguration				EthSwt_SWIC_ResetConfiguration
#define EthSwt_SetMacLearningMode				EthSwt_SWIC_SetMacLearningMode
#define EthSwt_GetMacLearningMode				EthSwt_SWIC_GetMacLearningMode
#define EthSwt_NvmSingleBlockCallback			EthSwt_SWIC_NvmSingleBlockCallback
#define EthSwt_GetVersionInfo					EthSwt_SWIC_GetVersionInfo
#define EthSwt_SetMgmtInfo						EthSwt_SWIC_SetMgmtInfo
#define EthSwt_PortEnableTimeStamp				EthSwt_SWIC_PortEnableTimeStamp
#define EthSwt_VerifyConfig						EthSwt_SWIC_VerifyConfig
#define EthSwt_SetForwardingMode				EthSwt_SWIC_SetForwardingMode
#define EthSwt_GetPortSignalQuality				EthSwt_SWIC_GetPortSignalQuality
#define EthSwt_GetPortIdentifier				EthSwt_SWIC_GetPortIdentifier
#define EthSwt_GetSwitchIdentifier				EthSwt_SWIC_GetSwitchIdentifier
#define EthSwt_WritePortMirrorConfiguration		EthSwt_SWIC_WritePortMirrorConfiguration
#define EthSwt_ReadPortMirrorConfiguration		EthSwt_SWIC_ReadPortMirrorConfiguration
#define EthSwt_DeletePortMirrorConfiguration	EthSwt_SWIC_DeletePortMirrorConfiguration
#define EthSwt_GetPortMirrorState				EthSwt_SWIC_GetPortMirrorState
#define EthSwt_SetPortMirrorState				EthSwt_SWIC_SetPortMirrorState
#define EthSwt_SetPortTestMode					EthSwt_SWIC_SetPortTestMode
#define EthSwt_SetPortLoopbackMode				EthSwt_SWIC_SetPortLoopbackMode
#define EthSwt_SetPortTxMode					EthSwt_SWIC_SetPortTxMode
#define EthSwt_RunPortCableDiagnostic			EthSwt_SWIC_RunPortCableDiagnostic
#define EthSwt_GetPortCableDiagnosticsResult	EthSwt_SWIC_GetPortCableDiagnosticsResult
#define EthSwt_GetCfgDataRaw					EthSwt_SWIC_GetCfgDataRaw
#define EthSwt_GetCfgDataInfo					EthSwt_SWIC_GetCfgDataInfo
#define EthSwt_PortLinkStateRequest				EthSwt_SWIC_PortLinkStateRequest
#define EthSwt_GetMaxFIFOBufferFillLevel		EthSwt_SWIC_GetMaxFIFOBufferFillLevel
#define EthSwt_GetRxMgmtObject					EthSwt_SWIC_GetRxMgmtObject
#define EthSwt_GetTxMgmtObject					EthSwt_SWIC_GetTxMgmtObject
#define EthSwt_MainFunction						EthSwt_SWIC_MainFunction
#define EthSwt_BackgroundTask					EthSwt_SWIC_BackgroundTask

#endif /*ETHSWT_H*/
