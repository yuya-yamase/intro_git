/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_Data.c                                                */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include "EthSwt_Data.h"
#include <EthSwt_SWIC_Cfg.h>
#include <EthSwt_SWIC.h>
#include <LIB.h>
#include <chipcom.h>
#include <EthSwt.h>
#include <EthSwt_SWIC_MIB.h>
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_ID                        ETHSWT_SWIC_IDX

#define D_ETHSWT_DATA_FAILED                        (0xFF)

#define D_ETHSWT_DATA_UPDATE_ADC                    (1U << 0U)
#define D_ETHSWT_DATA_UPDATE_DCM                    (1U << 1U)
#define D_ETHSWT_DATA_UPDATE_SAIL                   (1U << 2U)
#define D_ETHSWT_DATA_UPDATE_TOOL                   (1U << 3U)
#define D_ETHSWT_DATA_UPDATE_LINUX                  (1U << 4U)
#define D_ETHSWT_DATA_UPDATE_ANDROID                (1U << 5U)

#define D_ETHSWT_DATA_UPDATE_QCI0                   (1U << 0U)
#define D_ETHSWT_DATA_UPDATE_QCI1                   (1U << 1U)
#define D_ETHSWT_DATA_UPDATE_QCI2                   (1U << 2U)
#define D_ETHSWT_DATA_UPDATE_QCI3                   (1U << 3U)
#define D_ETHSWT_DATA_UPDATE_QCI4                   (1U << 4U)
/* -------------------------------------------------------------------------- */
typedef struct {
    uint8 arrayID;
    uint8 flagPosition;
} S_ETHSWT_DATA_FOR_UPDATE;

static const S_ETHSWT_DATA_FOR_UPDATE S_ETHSWT_DATA_LINK_ID_TABLE[D_ETHSWT_SWIC_PORT_NUM] =
{
    {D_ETHSWT_DATA_LINK_ADC_ID      , D_ETHSWT_DATA_UPDATE_ADC      }           /* Port1: A-DC      */
,   {D_ETHSWT_DATA_LINK_DCM_ID      , D_ETHSWT_DATA_UPDATE_DCM      }           /* Port2: DCM       */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port3: no use    */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port4: no use    */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port5: SAIL(リンク読み出し対象外)  */
,   {D_ETHSWT_DATA_LINK_TOOL_ID     , D_ETHSWT_DATA_UPDATE_TOOL     }           /* Port6: DLC       */
,   {D_ETHSWT_DATA_LINK_LINUX_ID    , D_ETHSWT_DATA_UPDATE_LINUX    }           /* Port7: Linux     */
,   {D_ETHSWT_DATA_LINK_ANDROID_ID  , D_ETHSWT_DATA_UPDATE_ANDROID  }           /* Port8: Android   */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port9: no use    */
};

static const S_ETHSWT_DATA_FOR_UPDATE S_ETHSWT_DATA_MIB_ID_TABLE[D_ETHSWT_SWIC_PORT_NUM] =
{
    {D_ETHSWT_DATA_MIB_ADC_ID       , D_ETHSWT_DATA_UPDATE_ADC      }           /* Port1: A-DC      */
,   {D_ETHSWT_DATA_MIB_DCM_ID       , D_ETHSWT_DATA_UPDATE_DCM      }           /* Port2: DCM       */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port3: no use    */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port4: no use    */
,   {D_ETHSWT_DATA_MIB_SAIL_ID      , D_ETHSWT_DATA_UPDATE_SAIL     }           /* Port5: SAIL      */
,   {D_ETHSWT_DATA_MIB_TOOL_ID      , D_ETHSWT_DATA_UPDATE_TOOL     }           /* Port6: DLC       */
,   {D_ETHSWt_DATA_MIB_LINUX_ID     , D_ETHSWT_DATA_UPDATE_LINUX    }           /* Port7: Linux     */
,   {D_ETHSWT_DATA_MIB_ANDROID_ID   , D_ETHSWT_DATA_UPDATE_ANDROID  }           /* Port8: Android   */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port9: no use    */
};

static const S_ETHSWT_DATA_FOR_UPDATE S_ETHSWT_DATA_SQI_ID_TABLE[D_ETHSWT_SWIC_PORT_NUM] =
{
    {D_ETHSWT_DATA_SQI_ADC_ID       , D_ETHSWT_DATA_UPDATE_ADC      }           /* Port1: A-DC      */
,   {D_ETHSWT_DATA_SQI_DCM_ID       , D_ETHSWT_DATA_UPDATE_DCM      }           /* Port2: DCM       */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port3: no use    */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port4: no use    */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port5: SAIL      */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port6: DLC       */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port7: Linux     */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port8: Android   */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port9: no use    */
};

/* -------------------------------------------------------------------------- */
/* 以下、暫定 */
static EthSwt_StateType         G_ETHSWT_DATA_STATE[181];
/* 以上、暫定 */
static S_ETHSWT_DATA_LINK       G_ETHSWT_DATA_LINK;
static S_ETHSWT_DATA_MIB        G_ETHSWT_DATA_MIB;
static S_ETHSWT_DATA_SQI        G_ETHSWT_DATA_SQI;
static S_ETHSWT_DATA_QCI        G_ETHSWT_DATA_QCI;

static uint32                   G_ETHSWT_DATA_LINK_ID;
static uint32                   G_ETHSWT_DATA_MIB_ID;
static uint32                   G_ETHSWT_DATA_SQI_ID;
static uint32                   G_ETHSWT_DATA_QCI_ID;

static uint8                    G_ETHSWT_DATA_LINK_UPDATE;
static uint8                    G_ETHSWT_DATA_MIB_UPDATE;
static uint8                    G_ETHSWT_DATA_SQI_UPDATE;
static uint8                    G_ETHSWT_DATA_QCI_UPDATE;

/* -------------------------------------------------------------------------- */
static void ethswt_data_setEthSwtStateData(void);
static void ethswt_data_checkLinkUpdate(void);
static void ethswt_data_checkMIBUpdate(void);
static void ethswt_data_checkSQIUpdate(void);
static void ethswt_data_checkQciUpdate(void);
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void)
{
    uint8   idx;

    LIB_memset((uint8*)&G_ETHSWT_DATA_STATE, 0, sizeof(G_ETHSWT_DATA_STATE));
    LIB_memset((uint8*)&G_ETHSWT_DATA_LINK, 0, sizeof(G_ETHSWT_DATA_LINK));
    LIB_memset((uint8*)&G_ETHSWT_DATA_MIB, 0, sizeof(G_ETHSWT_DATA_MIB));
    LIB_memset((uint8*)&G_ETHSWT_DATA_SQI, 0, sizeof(G_ETHSWT_DATA_SQI));
    LIB_memset((uint8*)&G_ETHSWT_DATA_QCI, 0, sizeof(G_ETHSWT_DATA_QCI));

    for (idx = 0u; idx < D_ETHSWT_DATA_LINK_NUM; idx++) {
        G_ETHSWT_DATA_LINK.link[idx].linkGetResult = E_NOT_OK;
    }
    for (idx = 0u; idx < D_ETHSWT_DATA_SQI_NUM; idx++) {
        G_ETHSWT_DATA_SQI.sqi[idx].sqiGetResult = E_NOT_OK;
    }

    G_ETHSWT_DATA_LINK_ID = 0;
    G_ETHSWT_DATA_MIB_ID = 0;
    G_ETHSWT_DATA_SQI_ID = 0;
    G_ETHSWT_DATA_QCI_ID = 0;

    LIB_memset((uint8*)&G_ETHSWT_DATA_LINK_UPDATE, 0, sizeof(G_ETHSWT_DATA_LINK_UPDATE));
    LIB_memset((uint8*)&G_ETHSWT_DATA_MIB_UPDATE, 0, sizeof(G_ETHSWT_DATA_MIB_UPDATE));
    LIB_memset((uint8*)&G_ETHSWT_DATA_SQI_UPDATE, 0, sizeof(G_ETHSWT_DATA_SQI_UPDATE));
    LIB_memset((uint8*)&G_ETHSWT_DATA_QCI_UPDATE, 0, sizeof(G_ETHSWT_DATA_QCI_UPDATE));
    
    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_NotifyLink(const uint8 SwitchPortIdx, const Std_ReturnType getLinkResult, const EthTrcv_LinkStateType linkState)
{
    do {
        if (SwitchPortIdx >= D_ETHSWT_SWIC_PORT_NUM)                                    {break;}
        if (S_ETHSWT_DATA_LINK_ID_TABLE[SwitchPortIdx].arrayID == D_ETHSWT_DATA_FAILED) {break;}
        
        LIB_DI();
        G_ETHSWT_DATA_LINK.link[S_ETHSWT_DATA_LINK_ID_TABLE[SwitchPortIdx].arrayID].linkGetResult = getLinkResult;
        G_ETHSWT_DATA_LINK.link[S_ETHSWT_DATA_LINK_ID_TABLE[SwitchPortIdx].arrayID].linkStatus = linkState;
        G_ETHSWT_DATA_LINK_UPDATE |= S_ETHSWT_DATA_LINK_ID_TABLE[SwitchPortIdx].flagPosition;
        LIB_EI();
    } while(0);

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_NotifyMIB(const uint8 SwitchPortIdx, const uint32 *const MIBArray)
{
    uint8   idx;

    do {
        if (SwitchPortIdx >= D_ETHSWT_SWIC_PORT_NUM)                                    {break;}
        if (S_ETHSWT_DATA_MIB_ID_TABLE[SwitchPortIdx].arrayID == D_ETHSWT_DATA_FAILED)  {break;}

        LIB_DI();
        for(idx = 0; idx < D_ETHSWT_SWIC_MIB_NUM; idx++) {
            G_ETHSWT_DATA_MIB.mib[S_ETHSWT_DATA_MIB_ID_TABLE[SwitchPortIdx].arrayID][idx] = MIBArray[idx];
        }
        G_ETHSWT_DATA_MIB_UPDATE |= S_ETHSWT_DATA_MIB_ID_TABLE[SwitchPortIdx].flagPosition;
        LIB_EI();
    } while(0);

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_NotifySQI(const uint8 SwtichPortIdx, const Std_ReturnType getSQIResult, const uint8 SQIValue)
{
    do {
        if (SwtichPortIdx >= D_ETHSWT_SWIC_PORT_NUM)                                    {break;}
        if (S_ETHSWT_DATA_SQI_ID_TABLE[SwtichPortIdx].arrayID == D_ETHSWT_DATA_FAILED)  {break;}

        LIB_DI();
        G_ETHSWT_DATA_SQI.sqi[S_ETHSWT_DATA_SQI_ID_TABLE[SwtichPortIdx].arrayID].sqiGetResult = getSQIResult;
        G_ETHSWT_DATA_SQI.sqi[S_ETHSWT_DATA_SQI_ID_TABLE[SwtichPortIdx].arrayID].sqiValue = SQIValue;
        G_ETHSWT_DATA_SQI_UPDATE |= S_ETHSWT_DATA_SQI_ID_TABLE[SwtichPortIdx].flagPosition;
        LIB_EI();
    } while(0);

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_NotifyQci(const uint8 QciIdx, const uint32 QciCount)
{
    do {
        if (QciIdx >= D_ETHSWT_DATA_QCI_NUM)                                            {break;}

        LIB_DI();
        G_ETHSWT_DATA_QCI.qciCount[QciIdx] = QciCount;
        G_ETHSWT_DATA_QCI_UPDATE |= (1u << QciIdx);
        LIB_EI();
    } while(0);

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_LoProc(void)
{
    ethswt_data_setEthSwtStateData();
    ethswt_data_checkLinkUpdate();
    ethswt_data_checkMIBUpdate();
    ethswt_data_checkSQIUpdate();
    ethswt_data_checkQciUpdate();
    
    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_checkLinkUpdate(void)
{
    uint8   isUpdated = STD_OFF;

    /* リンク状態取得対象は、A-DC, DCM, Tool, Linux, Android ポート */
    if (G_ETHSWT_DATA_LINK_UPDATE == (D_ETHSWT_DATA_UPDATE_ADC | D_ETHSWT_DATA_UPDATE_DCM | D_ETHSWT_DATA_UPDATE_TOOL | D_ETHSWT_DATA_UPDATE_LINUX | D_ETHSWT_DATA_UPDATE_ANDROID) ) {
        isUpdated = STD_ON;
        G_ETHSWT_DATA_LINK.id = G_ETHSWT_DATA_LINK_ID;
    }
    
    if (isUpdated == STD_ON) {
        (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_LINKINFO, sizeof(G_ETHSWT_DATA_LINK), (uint8*)&G_ETHSWT_DATA_LINK);
        if (G_ETHSWT_DATA_LINK_ID == 0xFFFF) {
            G_ETHSWT_DATA_LINK_ID = 0u;
        } else {
            G_ETHSWT_DATA_LINK_ID++;
        }
        G_ETHSWT_DATA_LINK_UPDATE = 0u;
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_checkMIBUpdate(void)
{
    uint8   isUpdated = STD_OFF;

    /* MIB取得対象は、A-DC, DCM, SAIL, Tool, Linux, Android ポート */
    if (G_ETHSWT_DATA_MIB_UPDATE == (D_ETHSWT_DATA_UPDATE_ADC | D_ETHSWT_DATA_UPDATE_DCM | D_ETHSWT_DATA_UPDATE_SAIL | D_ETHSWT_DATA_UPDATE_TOOL | D_ETHSWT_DATA_UPDATE_LINUX | D_ETHSWT_DATA_UPDATE_ANDROID) ) {
        isUpdated = STD_ON;
        G_ETHSWT_DATA_MIB.id = G_ETHSWT_DATA_MIB_ID;
    }

    if (isUpdated == STD_ON) {
        (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_MIB, sizeof(G_ETHSWT_DATA_MIB), (uint8*)&G_ETHSWT_DATA_MIB);
        if (G_ETHSWT_DATA_MIB_ID == 0xFFFF) {
            G_ETHSWT_DATA_MIB_ID = 0u;
        } else {
            G_ETHSWT_DATA_MIB_ID++;
        }
        G_ETHSWT_DATA_MIB_UPDATE = 0u;
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_checkSQIUpdate(void)
{
    uint8   isUpdated = STD_OFF;

    /* SQI値取得対象は、A-DC, DCM ポート */
    if (G_ETHSWT_DATA_SQI_UPDATE == (D_ETHSWT_DATA_UPDATE_ADC | D_ETHSWT_DATA_UPDATE_DCM) ) {
        isUpdated = STD_ON;
        G_ETHSWT_DATA_SQI.id = G_ETHSWT_DATA_SQI_ID;
    }

    if (isUpdated == STD_ON) {
        (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_SQI, sizeof(G_ETHSWT_DATA_SQI), (uint8*)&G_ETHSWT_DATA_SQI);
        if (G_ETHSWT_DATA_SQI_ID == 0xFFFF) {
            G_ETHSWT_DATA_SQI_ID = 0u;
        } else {
            G_ETHSWT_DATA_SQI_ID++;
        }
        G_ETHSWT_DATA_SQI_UPDATE = 0u;
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_checkQciUpdate(void)
{
    uint8   isUpdated = STD_OFF;

    /* Qci取得対象は、QciID = 0, 1, 2, 3, 4 */
    if (G_ETHSWT_DATA_QCI_UPDATE == (D_ETHSWT_DATA_UPDATE_QCI0 | D_ETHSWT_DATA_UPDATE_QCI1 | D_ETHSWT_DATA_UPDATE_QCI2 | D_ETHSWT_DATA_UPDATE_QCI3 | D_ETHSWT_DATA_UPDATE_QCI4) ) {
        isUpdated = STD_ON;
        G_ETHSWT_DATA_QCI.id = G_ETHSWT_DATA_QCI_ID;
    }

    if (isUpdated == STD_ON) {
        (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_DATAUSAGEEXCEED, sizeof(G_ETHSWT_DATA_QCI), (uint8*)&G_ETHSWT_DATA_QCI);
        if (G_ETHSWT_DATA_QCI_ID == 0xFFFF) {
            G_ETHSWT_DATA_QCI_ID = 0u;
        } else {
            G_ETHSWT_DATA_QCI_ID++;
        }
        G_ETHSWT_DATA_QCI_UPDATE = 0u;
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_setEthSwtStateData(void)
{
    G_ETHSWT_DATA_STATE[0] = EthSwt_SWIC_GetEthSwtState(D_ETHSWT_SWIC_ID);

    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_MCUINFO, sizeof(G_ETHSWT_DATA_STATE), (uint8*)&G_ETHSWT_DATA_STATE);

    return;
}
/* -------------------------------------------------------------------------- */
