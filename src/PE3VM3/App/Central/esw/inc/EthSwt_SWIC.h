#ifndef ETHSWT_SWIC_H
#define ETHSWT_SWIC_H
#include <Std_Types.h>
#include <EthSwt.h>

typedef struct {				/* フレーム廃棄情報 */
	uint32	Factor;				/* フレーム破棄要因 */
	uint32	IngressCount;		/* ingressフレーム破棄数 */
	uint32	EgressCount;		/* egressフレーム破棄数 */
}	EthSwt_DiscardInfoType;

typedef uint8 EthSwt_StateType;
#define ETHSWT_STATE_UNINIT                     ((EthSwt_StateType)0x00U)
#define ETHSWT_STATE_INIT                       ((EthSwt_StateType)0x01U)
#define ETHSWT_STATE_ACTIVE                     ((EthSwt_StateType)0x03U)

typedef uint32 Eth_ModeType;
#define ETH_MODE_DOWN                           ((Eth_ModeType)0U)
#define ETH_MODE_ACTIVE                         ((Eth_ModeType)1U)
#define ETH_MODE_ACTIVE_WITH_WAKEUP_REQUEST     ((Eth_ModeType)2U)

typedef uint8 EthTrcv_LinkStateType;
#define ETHTRCV_LINK_STATE_DOWN                 ((EthTrcv_LinkStateType)0U)
#define ETHTRCV_LINK_STATE_ACTIVE               ((EthTrcv_LinkStateType)1U)

void EthSwt_SWIC_Init(const EthSwt_ConfigType *CfgPtr);
#if 0    /* VN-HILSとしては不要なため無効化 */
Std_ReturnType EthSwt_SWIC_GetLinkState(uint8 SwitchIdx, uint8 SwitchPortIdx, EthTrcv_LinkStateType *LinkStatePtr);
#endif    /* VN-HILSとしては不要なため無効化 */
void EthSwt_SWIC_MainFunction1MS(void);
void EthSwt_SWIC_MainFunction5MS(void);
void EthSwt_SWIC_BackgroundTask(void);
#if 0    /* VN-HILSとしては不要なため無効化 */
EthSwt_StateType EthSwt_SWIC_GetState(void);
Std_ReturnType EthSwt_SWIC_ClearFrameInfo(const uint8 SwitchIdx, const uint8 SwitchPortIdx);
Std_ReturnType EthSwt_SWIC_GetDiscardInfo(const uint8 SwitchIdx, const uint8 SwitchPortIdx, EthSwt_DiscardInfoType *const DiscardInfoPtr);

Std_ReturnType EthSwt_SWIC_GetIDS_TcamInfo(const uint8 SwitchIdx, const uint8 SwitchPortIdx, uint32 *const IDSInfo);
Std_ReturnType EthSwt_SWIC_GetIDS_FiltFrmInfo(const uint8 SwitchIdx, const uint8 SwitchPortIdx, uint32 *const IDSInfo);
#endif    /* VN-HILSとしては不要なため無効化 */
#if 0    /* VN-HILSでは、SWICのログ記録を行わない想定のため、実装しない。シス検以降で使用するかは検討が必要。 */
void EthSwt_SWIC_Log_Init(void);
#endif    /* VN-HILSでは、SWICのログ記録を行わない想定のため、実装しない。シス検以降で使用するかは検討が必要。 */
void EthSwt_SWIC_SpiRegChkNotify(uint32 status);
#endif /*ETHSWT_SWIC_H*/
