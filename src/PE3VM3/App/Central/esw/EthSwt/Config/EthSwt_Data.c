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
/* ˆÈ‰ºAŽb’è */
static EthSwt_StateType         G_ETHSWT_DATA_STATE[181];
/* ˆÈãAŽb’è */
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
static void ethswt_data_setLinkData(void);
static void ethswt_data_setMIBData(void);
static uint32 ehtswt_data_getTargetMib(uint8 targetPort, uint8 targetMIB);
static void ethswt_data_setSQIData(void);
static void ethswt_data_setQciData(void);
static uint32 ethswt_data_getTargetQci(uint8 targetQciId);
static void ethswt_data_setEthSwtStateData(void);
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void)
{
    LIB_memset((uint8*)&G_ETHSWT_DATA_STATE, 0, sizeof(G_ETHSWT_DATA_STATE));
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
    ethswt_data_setLinkData();
    ethswt_data_setMIBData();
    ethswt_data_setSQIData();
    ethswt_data_setQciData();
    ethswt_data_setEthSwtStateData();
    
    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_setLinkData(void)
{
    uint8                   idx;
    EthTrcv_LinkStateType   status = ETHTRCV_LINK_STATE_DOWN;
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

        if(G_ETHSWT_DATA_LINK_ID >= 0xFFFFFFFF) {
            G_ETHSWT_DATA_LINK_ID = 0;
        } else {
            G_ETHSWT_DATA_LINK_ID++;
        }
    }

    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_LINKINFO, sizeof(G_ETHSWT_DATA_LINK), (uint8*)&G_ETHSWT_DATA_LINK);

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_setMIBData(void)
{
    uint8                   idx;

    G_ETHSWT_DATA_MIB_COUNT++;
    if(G_ETHSWT_DATA_MIB_COUNT >= D_ETHSWT_SWIC_GET_MIB_TIME)
    {
        G_ETHSWT_DATA_MIB_COUNT = 0;

        for(idx = 0; idx < D_ETHSWT_DATA_USE_PORT_NUM; idx++) {
            G_ETHSWT_DATA_MIB.mib[idx].InFCSErr = ehtswt_data_getTargetMib(S_ETHSWT_DATA_IDX_TABLE[idx], D_ETHSWT_SWIC_MIB_INFCSERR);
            G_ETHSWT_DATA_MIB.mib[idx].InDiscards = ehtswt_data_getTargetMib(S_ETHSWT_DATA_IDX_TABLE[idx], D_ETHSWT_SWIC_MIB_INDISCARDS);
            G_ETHSWT_DATA_MIB.mib[idx].InFiltered = ehtswt_data_getTargetMib(S_ETHSWT_DATA_IDX_TABLE[idx], D_ETHSWT_SWIC_MIB_INFILTERED);
            G_ETHSWT_DATA_MIB.mib[idx].InOversize = ehtswt_data_getTargetMib(S_ETHSWT_DATA_IDX_TABLE[idx], D_ETHSWT_SWIC_MIB_INOVERSIZE);
            G_ETHSWT_DATA_MIB.mib[idx].InUndersize = ehtswt_data_getTargetMib(S_ETHSWT_DATA_IDX_TABLE[idx], D_ETHSWT_SWIC_MIB_INUNDERSIZE);
            G_ETHSWT_DATA_MIB.mib[idx].Tcam0 = ehtswt_data_getTargetMib(S_ETHSWT_DATA_IDX_TABLE[idx], D_ETHSWT_SWIC_MIB_TCAM0);
            G_ETHSWT_DATA_MIB.mib[idx].Tcam1 = ehtswt_data_getTargetMib(S_ETHSWT_DATA_IDX_TABLE[idx], D_ETHSWT_SWIC_MIB_TCAM1);
            G_ETHSWT_DATA_MIB.mib[idx].Tcam2 = ehtswt_data_getTargetMib(S_ETHSWT_DATA_IDX_TABLE[idx], D_ETHSWT_SWIC_MIB_TCAM2);
            G_ETHSWT_DATA_MIB.mib[idx].Tcam3 = ehtswt_data_getTargetMib(S_ETHSWT_DATA_IDX_TABLE[idx], D_ETHSWT_SWIC_MIB_TCAM3);
        }

        G_ETHSWT_DATA_MIB.id = G_ETHSWT_DATA_MIB_ID;

        if (G_ETHSWT_DATA_MIB_ID >= 0xFFFFFFFF) {
            G_ETHSWT_DATA_MIB_ID = 0;
        } else {
            G_ETHSWT_DATA_MIB_ID++;
        }
    }

    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_MIB, sizeof(G_ETHSWT_DATA_MIB), (uint8*)&G_ETHSWT_DATA_MIB);

    return;
}
/* -------------------------------------------------------------------------- */
static uint32 ehtswt_data_getTargetMib(uint8 targetPort, uint8 targetMIB)
{
    uint32                  mibCounter = 0;

    (void)EthSwt_SWIC_GetMIB(D_ETHSWT_SWIC_ID, targetPort, targetMIB, &mibCounter);

    return mibCounter;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_setSQIData(void)
{
    G_ETHSWT_DATA_SQI_COUNT++;
    if(G_ETHSWT_DATA_SQI_COUNT >= D_ETHSWT_SWIC_GET_SQI_TIME)
    {
        G_ETHSWT_DATA_SQI_COUNT = 0;

        /* Œã‚É‘Î‰ž */

        G_ETHSWT_DATA_SQI.id = G_ETHSWT_DATA_SQI_ID;

        if (G_ETHSWT_DATA_SQI_ID >= 0xFFFFFFFF) {
            G_ETHSWT_DATA_SQI_ID = 0;
        } else {
            G_ETHSWT_DATA_SQI_ID++;
        }
    }

    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_SQI, sizeof(G_ETHSWT_DATA_SQI), (uint8*)&G_ETHSWT_DATA_SQI);
    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_setQciData(void)
{
    G_ETHSWT_DATA_QCI_COUNT++;
    if(G_ETHSWT_DATA_QCI_COUNT >= D_ETHSWT_DATA_GET_QCI_TIME)
    {
        G_ETHSWT_DATA_QCI_COUNT = 0;
        
        G_ETHSWT_DATA_QCI.qciCount[D_ETHSWT_DATA_QCI_DCM_TCP_ID] = ethswt_data_getTargetQci(D_ETHSWT_SWIC_QCI_ID_DCM_TCP);
        G_ETHSWT_DATA_QCI.qciCount[D_ETHSWT_DATA_QCI_DCM_UDP_ID] = ethswt_data_getTargetQci(D_ETHSWT_SWIC_QCI_ID_DCM_UDP);
        G_ETHSWT_DATA_QCI.qciCount[D_ETHSWT_DATA_QCI_DCM_ICMP_ID] = ethswt_data_getTargetQci(D_ETHSWT_SWIC_QCI_ID_DCM_ICMP);
        G_ETHSWT_DATA_QCI.qciCount[D_ETHSWT_DATA_QCI_DLC_TCP_ID] = ethswt_data_getTargetQci(D_ETHSWT_SWIC_QCI_ID_DLC_TCP);
        G_ETHSWT_DATA_QCI.qciCount[D_ETHSWT_DATA_QCI_DLC_UDP_ID] = ethswt_data_getTargetQci(D_ETHSWT_SWIC_QCI_ID_DLC_UDP);
        
        G_ETHSWT_DATA_QCI.id = G_ETHSWT_DATA_QCI_ID;

        if (G_ETHSWT_DATA_QCI_ID >= 0xFFFFFFFF) {
            G_ETHSWT_DATA_QCI_ID = 0;
        } else {
            G_ETHSWT_DATA_QCI_ID++;
        }
    }

    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_SWIC_DATAUSAGEEXCEED, sizeof(G_ETHSWT_DATA_QCI), (uint8*)&G_ETHSWT_DATA_QCI);

    return;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_data_getTargetQci(uint8 targetQciId)
{
    uint32                  qciData = 0;

    (void)EthSwt_SWIC_GetQci(D_ETHSWT_SWIC_ID, targetQciId, &qciData);
    
    return qciData;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_setEthSwtStateData(void)
{
    G_ETHSWT_DATA_STATE[0] = EthSwt_SWIC_GetEthSwtState(D_ETHSWT_SWIC_ID);

    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_MCUINFO, sizeof(G_ETHSWT_DATA_STATE), (uint8*)&G_ETHSWT_DATA_STATE);

    return;
}
