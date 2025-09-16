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



#define D_ETHSWT_SWIC_GET_LINK_TIME             (D_ETHSWT_DATA_GET_LINK_CYCLE / D_ETHSWT_DATA_CYCLE)
#define D_ETHSWT_SWIC_GET_MIB_TIME              (D_ETHSWT_DATA_GET_MIB_CYCLE / D_ETHSWT_DATA_CYCLE)
#define D_ETHSWT_SWIC_GET_SQI_TIME              (D_ETHSWT_DATA_GET_SQI_CYCLE / D_ETHSWT_DATA_CYCLE)
#define D_ETHSWT_DATA_GET_QCI_TIME              (D_ETHSWT_DATA_GET_QCI_CYCLE / D_ETHSWT_DATA_CYCLE)
/* -------------------------------------------------------------------------- */
static const uint8 S_ETHSWT_DATA_IDX_TABLE[D_ETHSWT_DATA_USE_PORT_NUM] =
{
    D_ETHSWT_SWIC_ADC_PORT_ID
,   D_ETHSWT_SWIC_DCM_PORT_ID
,   D_ETHSWT_SWIC_SAIL_PORT_ID
,   D_ETHSWT_SWIC_TOOL_PORT_ID
,   D_ETHSWT_SWIC_LINUX_PORT_ID
,   D_ETHSWT_SWIC_ANDROID_PORT_ID
};
/* -------------------------------------------------------------------------- */
// static S_ETHSWT_DATA_CHIPCOM G_ETHSWT_DATA;

static S_ETHSWT_DATA_LINK       G_ETHSWT_DATA_LINK;
static S_ETHSWT_DATA_MIB        G_ETHSWT_DATA_MIB;
static S_ETHSWT_DATA_SQI        G_ETHSWT_DATA_SQI;
static S_ETHSWT_DATA_QCI        G_ETHSWT_DATA_QCI;

static uint32                   G_ETHSWT_DATA_LINK_COUNT;
static uint32                   G_ETHSWT_DATA_MIB_COUNT;
static uint32                   G_ETHSWT_DATA_SQI_COUNT;
static uint32                   G_ETHSWT_DATA_QCI_COUNT;

static uint32                   G_ETHSWT_DATA_LINK_ID;
static uint32                   G_ETHSWT_DATA_MIB_ID;
static uint32                   G_ETHSWT_DATA_SQI_ID;
static uint32                   G_ETHSWT_DATA_QCI_ID;
/* -------------------------------------------------------------------------- */
static void ethswt_data_set_link(void);
static void ethswt_data_set_mib(void);
static void ethswt_data_set_sqi(void);
static void ethswt_data_set_qci(void);
static void ethswt_data_set_state(void);
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void)
{
    LIB_memset((uint8*)&G_ETHSWT_DATA_LINK, 0, sizeof(G_ETHSWT_DATA_LINK));
    LIB_memset((uint8*)&G_ETHSWT_DATA_MIB, 0, sizeof(G_ETHSWT_DATA_MIB));
    LIB_memset((uint8*)&G_ETHSWT_DATA_SQI, 0, sizeof(G_ETHSWT_DATA_SQI));
    LIB_memset((uint8*)&G_ETHSWT_DATA_QCI, 0, sizeof(G_ETHSWT_DATA_QCI));

    G_ETHSWT_DATA_LINK_COUNT = 0;
    G_ETHSWT_DATA_MIB_COUNT = 0;
    G_ETHSWT_DATA_SQI_COUNT = 0;
    G_ETHSWT_DATA_QCI_COUNT = 0;

    G_ETHSWT_DATA_LINK_ID = 0;
    G_ETHSWT_DATA_MIB_ID = 0;
    G_ETHSWT_DATA_SQI_ID = 0;
    G_ETHSWT_DATA_QCI_ID = 0;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_LoProc(void)
{
    ethswt_data_set_link();
    ethswt_data_set_mib();
    ethswt_data_set_sqi();
    ethswt_data_set_qci();
    ethswt_data_set_state();
    
    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_set_link(void)
{
    uint8                   idx;
    EthTrcv_LinkStateType   status;
    Std_ReturnType          getResult;

    G_ETHSWT_DATA_LINK_COUNT++;
    if(G_ETHSWT_DATA_LINK_COUNT >= D_ETHSWT_SWIC_GET_LINK_TIME)
    {
        G_ETHSWT_DATA_LINK_COUNT = 0;

        for(idx = 0; idx < D_ETHSWT_DATA_USE_PORT_NUM; idx++) {
            getResult = EthSwt_SWIC_GetLinkState(D_ETHSWT_SWIC_ID, S_ETHSWT_DATA_IDX_TABLE[idx], &status);
            G_ETHSWT_DATA_LINK.link[idx].linkStatus = status;
            G_ETHSWT_DATA_LINK.link[idx].linkGetResult = getResult;
        }
        G_ETHSWT_DATA_LINK.id = G_ETHSWT_DATA_LINK_ID;

        if(G_ETHSWT_DATA_LINK_ID > 0xFFFFFFFF) {
            G_ETHSWT_DATA_LINK_ID = 0;
        } else {
            G_ETHSWT_DATA_LINK_ID++;
        }
    }

    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_LINKINFO, sizeof(G_ETHSWT_DATA_LINK), (uint8*)&G_ETHSWT_DATA_LINK);

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_set_mib(void)
{
    uint8                   idx;
    uint8                   mibIdx;
    Std_ReturnType          getResult;
    S_ETHSWT_SWIC_MIB_COUNT mibCount;
    
    G_ETHSWT_DATA_MIB_COUNT++;
    if(G_ETHSWT_DATA_MIB_COUNT >= D_ETHSWT_SWIC_GET_MIB_TIME)
    {
        G_ETHSWT_DATA_MIB_COUNT = 0;

        for(idx = 0; idx < D_ETHSWT_DATA_USE_PORT_NUM; idx++) {
            for(mibIdx = 0; mibIdx < D_ETHSWT_SWIC_MIB_NUM; mibIdx++) {
                getResult = EthSwt_SWIC_GetMIB(D_ETHSWT_SWIC_ID, S_ETHSWT_DATA_IDX_TABLE[idx], mibIdx, &mibCount);
                if(getResult == E_OK) {
                    G_ETHSWT_DATA_MIB.mib[idx][mibIdx] = mibCount.IngressCount;
                }
            }
        }
    }
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_set_sqi(void)
{

}
/* -------------------------------------------------------------------------- */
static void ethswt_data_set_qci(void)
{

}
/* -------------------------------------------------------------------------- */
static void ethswt_data_set_state(void)
{

}
