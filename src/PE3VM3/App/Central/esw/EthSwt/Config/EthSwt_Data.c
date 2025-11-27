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
#define D_ETHSWT_SWIC_ID                            ETHSWT_SWIC_IDX

#define D_ETHSWT_DATA_FAILED                        (0xFF)                      /* 未使用ポート用 */

#define D_ETHSWT_DATA_UPDATE_ADC                    (1U << 0U)                  /* 0b00000001：A-DCポート更新ビット     */
#define D_ETHSWT_DATA_UPDATE_DCM                    (1U << 1U)                  /* 0b00000010：DCMポート更新ビット      */
#define D_ETHSWT_DATA_UPDATE_SAIL                   (1U << 2U)                  /* 0b00000100：SAILポート更新ビット     */
#define D_ETHSWT_DATA_UPDATE_TOOL                   (1U << 3U)                  /* 0b00001000：Toolポート更新ビット     */
#define D_ETHSWT_DATA_UPDATE_LINUX                  (1U << 4U)                  /* 0b00010000：Linuxポート更新ビット    */
#define D_ETHSWT_DATA_UPDATE_ANDROID                (1U << 5U)                  /* 0b00100000：Androidポート更新ビット  */

#define D_ETHSWT_DATA_UPDATE_QCI0                   (1U << 0U)                  /* 0b00000001：DCM(TCP)更新ビット       */
#define D_ETHSWT_DATA_UPDATE_QCI1                   (1U << 1U)                  /* 0b00000010：DCM(UDP)更新ビット       */
#define D_ETHSWT_DATA_UPDATE_QCI2                   (1U << 2U)                  /* 0b00000100：DCM(ICMP)更新ビット      */
#define D_ETHSWT_DATA_UPDATE_QCI3                   (1U << 3U)                  /* 0b00001000：Tool(TCP)更新ビット      */
#define D_ETHSWT_DATA_UPDATE_QCI4                   (1U << 4U)                  /* 0b00010000：Tool(UDP)更新ビット      */

/* リンク状態読み出し対象は、A-DC, DCM, Tool, Linux, Android ポート */
#define D_ETHSWT_DATA_LINK_TARGET                   (D_ETHSWT_DATA_UPDATE_ADC | D_ETHSWT_DATA_UPDATE_DCM | D_ETHSWT_DATA_UPDATE_TOOL | D_ETHSWT_DATA_UPDATE_LINUX | D_ETHSWT_DATA_UPDATE_ANDROID)

/* MIB読み出し対象は、A-DC, DCM, SAIL, Tool, Linux, Android ポート */
#define D_ETHSWT_DATA_MIB_TARGET                    (D_ETHSWT_DATA_UPDATE_ADC | D_ETHSWT_DATA_UPDATE_DCM | D_ETHSWT_DATA_UPDATE_SAIL | D_ETHSWT_DATA_UPDATE_TOOL | D_ETHSWT_DATA_UPDATE_LINUX | D_ETHSWT_DATA_UPDATE_ANDROID)

/* SQI読み出し対象は、A-DC, DCM ポート */
#define D_ETHSWT_DATA_SQI_TARGET                    (D_ETHSWT_DATA_UPDATE_ADC | D_ETHSWT_DATA_UPDATE_DCM)

/* Qci取得対象は、QciID = 0, 1, 2, 3, 4 */
#define D_ETHSWT_DATA_QCI_TARGET                    (D_ETHSWT_DATA_UPDATE_QCI0 | D_ETHSWT_DATA_UPDATE_QCI1 | D_ETHSWT_DATA_UPDATE_QCI2 | D_ETHSWT_DATA_UPDATE_QCI3 | D_ETHSWT_DATA_UPDATE_QCI4)

/* レジスタアクセス取得対象は、SAIL */
#define D_ETHSWT_DATA_REGACCESS_TARGET              (D_ETHSWT_DATA_UPDATE_SAIL)

/* -------------------------------------------------------------------------- */
typedef struct {
    uint8 arrayID;                                                              /* 送信用データIndex        */
    uint8 flagPosition;                                                         /* 送信判定用更新ビット     */
} S_ETHSWT_DATA_FOR_UPDATE;

/* リンク状態送信用「SWIC物理ポート番号Index(行) -> 送信用データIndex(列)」変換テーブル */
static const S_ETHSWT_DATA_FOR_UPDATE S_ETHSWT_DATA_LINK_ID_TABLE[D_ETHSWT_SWIC_PORT_NUM] =
{   /* 送信用データIndex             , 送信用判定用更新ビット         */
    {D_ETHSWT_DATA_LINK_ADC_ID      , D_ETHSWT_DATA_UPDATE_ADC      }           /* Port1: A-DC      */
,   {D_ETHSWT_DATA_LINK_DCM_ID      , D_ETHSWT_DATA_UPDATE_DCM      }           /* Port2: DCM       */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port3: no use    */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port4: no use    */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port5: SAIL(リンク読み出し対象外)    */
,   {D_ETHSWT_DATA_LINK_TOOL_ID     , D_ETHSWT_DATA_UPDATE_TOOL     }           /* Port6: DLC       */
,   {D_ETHSWT_DATA_LINK_LINUX_ID    , D_ETHSWT_DATA_UPDATE_LINUX    }           /* Port7: Linux     */
,   {D_ETHSWT_DATA_LINK_ANDROID_ID  , D_ETHSWT_DATA_UPDATE_ANDROID  }           /* Port8: Android   */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port9: no use    */
};

/* MIB送信用「SWIC物理ポート番号Index(行) -> 送信用データIndex(列)」変換テーブル */
static const S_ETHSWT_DATA_FOR_UPDATE S_ETHSWT_DATA_MIB_ID_TABLE[D_ETHSWT_SWIC_PORT_NUM] =
{   /* 送信用データIndex             , 送信用判定用更新ビット         */
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

/* SQI値送信用「SWIC物理ポート番号Index(行) -> 送信用データIndex(列)」変換テーブル */
static const S_ETHSWT_DATA_FOR_UPDATE S_ETHSWT_DATA_SQI_ID_TABLE[D_ETHSWT_SWIC_PORT_NUM] =
{   /* 送信用データIndex             , 送信用判定用更新ビット         */
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

/* レジスタアクセスエラー送信用「SWIC物理ポート番号Index(行) -> 送信用データIndex(列)」変換テーブル */
static const S_ETHSWT_DATA_FOR_UPDATE S_ETHSWT_DATA_REGACCESS_ID_TABLE[D_ETHSWT_SWIC_PORT_NUM] =
{   /* 送信用データIndex             , 送信用判定用更新ビット         */
    {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port1: A-DC      */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port2: DCM       */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port3: no use    */
,   {D_ETHSWT_DATA_FAILED           , D_ETHSWT_DATA_FAILED          }           /* Port4: no use    */
,   {D_ETHSWT_DATA_REGAXSERR_SAIL_ID, D_ETHSWT_DATA_UPDATE_SAIL     }           /* Port5: SAIL      */
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
static S_ETHSWT_DATA_REGACCESS  G_ETHSWT_DATA_REGACCESS;

static uint32                   G_ETHSWT_DATA_LINK_ID;
static uint32                   G_ETHSWT_DATA_MIB_ID;
static uint32                   G_ETHSWT_DATA_SQI_ID;
static uint32                   G_ETHSWT_DATA_QCI_ID;
static uint32                   G_ETHSWT_DATA_REGACCESS_ID;
static uint32                   G_ETHSWT_DATA_SWICRESET_COUNT;

static uint8                    G_ETHSWT_DATA_LINK_UPDATE;
static uint8                    G_ETHSWT_DATA_MIB_UPDATE;
static uint8                    G_ETHSWT_DATA_SQI_UPDATE;
static uint8                    G_ETHSWT_DATA_QCI_UPDATE;
static uint8                    G_ETHSWT_DATA_REGACCESS_UPDATE;

/* -------------------------------------------------------------------------- */
static void ethswt_data_setEthSwtStateData(void);
static void ethswt_data_checkLinkUpdate(void);
static void ethswt_data_checkMIBUpdate(void);
static void ethswt_data_checkSQIUpdate(void);
static void ethswt_data_checkQciUpdate(void);
static void ethswt_data_checkRegAccessUpdate(void);
static void ethswt_data_checkSWICReset(void);
static void ethswt_data_incrementID(uint32 * const id);
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void)
{
    uint8   idx;

    LIB_memset((uint8*)&G_ETHSWT_DATA_STATE, 0, sizeof(G_ETHSWT_DATA_STATE));
    LIB_memset((uint8*)&G_ETHSWT_DATA_LINK, 0, sizeof(G_ETHSWT_DATA_LINK));
    LIB_memset((uint8*)&G_ETHSWT_DATA_MIB, 0, sizeof(G_ETHSWT_DATA_MIB));
    LIB_memset((uint8*)&G_ETHSWT_DATA_SQI, 0, sizeof(G_ETHSWT_DATA_SQI));
    LIB_memset((uint8*)&G_ETHSWT_DATA_QCI, 0, sizeof(G_ETHSWT_DATA_QCI));
    LIB_memset((uint8*)&G_ETHSWT_DATA_REGACCESS, 0, sizeof(G_ETHSWT_DATA_REGACCESS));

    for (idx = 0u; idx < D_ETHSWT_DATA_LINK_NUM; idx++) {
        G_ETHSWT_DATA_LINK.link[idx].linkGetResult = E_NOT_OK;
    }
    for (idx = 0u; idx < D_ETHSWT_DATA_SQI_NUM; idx++) {
        G_ETHSWT_DATA_SQI.sqi[idx].sqiGetResult = E_NOT_OK;
    }

    G_ETHSWT_DATA_LINK_ID = 0u;
    G_ETHSWT_DATA_MIB_ID = 0u;
    G_ETHSWT_DATA_SQI_ID = 0u;
    G_ETHSWT_DATA_QCI_ID = 0u;
    G_ETHSWT_DATA_REGACCESS_ID = 0u;
    G_ETHSWT_DATA_SWICRESET_COUNT = 0u;

    LIB_memset((uint8*)&G_ETHSWT_DATA_LINK_UPDATE, 0, sizeof(G_ETHSWT_DATA_LINK_UPDATE));
    LIB_memset((uint8*)&G_ETHSWT_DATA_MIB_UPDATE, 0, sizeof(G_ETHSWT_DATA_MIB_UPDATE));
    LIB_memset((uint8*)&G_ETHSWT_DATA_SQI_UPDATE, 0, sizeof(G_ETHSWT_DATA_SQI_UPDATE));
    LIB_memset((uint8*)&G_ETHSWT_DATA_QCI_UPDATE, 0, sizeof(G_ETHSWT_DATA_QCI_UPDATE));
    LIB_memset((uint8*)&G_ETHSWT_DATA_REGACCESS_UPDATE, 0, sizeof(G_ETHSWT_DATA_REGACCESS_UPDATE));
    
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
void EthSwt_Data_NotifyRegAccess(const Std_ReturnType getRegAccessResult, const swic_reg_data_t tbl[], const uint32 idx)
{
    do {

        LIB_DI();
        G_ETHSWT_DATA_REGACCESS.regAccess = getRegAccessResult;
        G_ETHSWT_DATA_REGACCESS.Paddr = tbl[idx].devAddr;
        G_ETHSWT_DATA_REGACCESS.Raddr = tbl[idx].regAddr;
        G_ETHSWT_DATA_REGACCESS.id = getRegAccessResult;
    	
        G_ETHSWT_DATA_REGACCESS_UPDATE |= S_ETHSWT_DATA_REGACCESS_ID_TABLE.flagPosition;
        LIB_EI();
    } while(0);

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_NotifySWICReset(void)
{
    if (G_ETHSWT_DATA_SWICRESET_COUNT == 0xFFFFFFFF) {
        G_ETHSWT_DATA_SWICRESET_COUNT = 0u;
    } else {
        G_ETHSWT_DATA_SWICRESET_COUNT++;
    }

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
    ethswt_data_checkRegAccessUpdate();
    ethswt_data_checkSWICReset();
    
    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_checkLinkUpdate(void)
{
    if (G_ETHSWT_DATA_LINK_UPDATE == D_ETHSWT_DATA_LINK_TARGET ) {
        G_ETHSWT_DATA_LINK_UPDATE = 0u;
        G_ETHSWT_DATA_LINK.id = G_ETHSWT_DATA_LINK_ID;
        (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_LINKINFO, sizeof(G_ETHSWT_DATA_LINK), (uint8*)&G_ETHSWT_DATA_LINK);
        ethswt_data_incrementID(&G_ETHSWT_DATA_LINK_ID);
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_checkMIBUpdate(void)
{
    if (G_ETHSWT_DATA_MIB_UPDATE == D_ETHSWT_DATA_MIB_TARGET ) {
        G_ETHSWT_DATA_MIB_UPDATE = 0u;
        G_ETHSWT_DATA_MIB.id = G_ETHSWT_DATA_MIB_ID;
        (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_MIB, sizeof(G_ETHSWT_DATA_MIB), (uint8*)&G_ETHSWT_DATA_MIB);
        ethswt_data_incrementID(&G_ETHSWT_DATA_MIB_ID);
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_checkSQIUpdate(void)
{
    if (G_ETHSWT_DATA_SQI_UPDATE == D_ETHSWT_DATA_SQI_TARGET ) {
        G_ETHSWT_DATA_SQI_UPDATE = 0u;
        G_ETHSWT_DATA_SQI.id = G_ETHSWT_DATA_SQI_ID;
        (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_SQI, sizeof(G_ETHSWT_DATA_SQI), (uint8*)&G_ETHSWT_DATA_SQI);
        ethswt_data_incrementID(&G_ETHSWT_DATA_SQI_ID);     
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_checkQciUpdate(void)
{
    if (G_ETHSWT_DATA_QCI_UPDATE == D_ETHSWT_DATA_QCI_TARGET ) {
        G_ETHSWT_DATA_QCI_UPDATE = 0u;
        G_ETHSWT_DATA_QCI.id = G_ETHSWT_DATA_QCI_ID;
        (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_DATAUSAGEEXCEED, sizeof(G_ETHSWT_DATA_QCI), (uint8*)&G_ETHSWT_DATA_QCI);
        ethswt_data_incrementID(&G_ETHSWT_DATA_QCI_ID);        
    }

    return;
}
static void ethswt_data_checkRegAccessUpdate(void)
{
    if (G_ETHSWT_DATA_REGACCESS_UPDATE == D_ETHSWT_DATA_REGACCESS_TARGET ) {
        G_ETHSWT_DATA_REGACCESS_UPDATE = 0u;
        G_ETHSWT_DATA_REGACCESS.id = G_ETHSWT_DATA_REGACCESS_ID;
        (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_REGERRSTS, sizeof(G_ETHSWT_DATA_REGACCESS), (uint8*)&G_ETHSWT_DATA_REGACCESS);
        ethswt_data_incrementID(&G_ETHSWT_DATA_REGACCESS_ID);        
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_checkSWICReset(void)
{
    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_RESETRESTART, sizeof(G_ETHSWT_DATA_SWICRESET_COUNT), (uint8*)&G_ETHSWT_DATA_SWICRESET_COUNT);

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
static void ethswt_data_incrementID(uint32 * const id)
{
    if (*id == 0xFFFFFFFF) {
        *id = (uint32)0;
    } else {
        *id = *id + (uint32)1;
    }

    return;
}
