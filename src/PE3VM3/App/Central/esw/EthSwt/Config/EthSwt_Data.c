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
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_ID                        ETHSWT_SWIC_IDX

#define D_ETHSWT_SWIC_ADC_PORT_ID               (0U)
#define D_ETHSWT_SWIC_DCM_PORT_ID               (1U)
#define D_ETHSWT_SWIC_SAIL_PORT_ID              (4U)
#define D_ETHSWT_SWIC_TOOL_PORT_ID              (5U)
#define D_ETHSWT_SWIC_LINUX_PORT_ID             (6U)
#define D_ETHSWT_SWIC_ANDROID_PORT_ID           (7U)

/* -------------------------------------------------------------------------- */
// static const uint8 S_ETHSWT_DATA_IDX_TABLE[D_ETHSWT_DATA_USE_PORT_NUM] =
// {
//     D_ETHSWT_SWIC_ADC_PORT_ID
// ,   D_ETHSWT_SWIC_DCM_PORT_ID
// ,   D_ETHSWT_SWIC_SAIL_PORT_ID
// ,   D_ETHSWT_SWIC_TOOL_PORT_ID
// ,   D_ETHSWT_SWIC_LINUX_PORT_ID
// ,   D_ETHSWT_SWIC_ANDROID_PORT_ID
// };
/* -------------------------------------------------------------------------- */
// static S_ETHSWT_DATA_CHIPCOM G_ETHSWT_DATA;

static S_ETHSWT_DATA_LINK       G_ETHSWT_DATA_LINK;
static S_ETHSWT_DATA_MIB        G_ETHSWT_DATA_MIB;
static S_ETHSWT_DATA_SQI        G_ETHSWT_DATA_SQI;
static S_ETHSWT_DATA_QCI        G_ETHSWT_DATA_QCI;
/* -------------------------------------------------------------------------- */
static void ethswt_data_set_link(void);
static void ethswt_data_set_mib(void);
static void ethswt_data_set_sqi(void);
static void ethswt_data_set_qci(void);
static void ethswt_data_set_state(void);
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void)
{
    // LIB_memset((uint8*)&G_ETHSWT_DATA, 0, sizeof(G_ETHSWT_DATA));

    LIB_memset((uint8*)&G_ETHSWT_DATA_LINK, 0, sizeof(G_ETHSWT_DATA_LINK));
    LIB_memset((uint8*)&G_ETHSWT_DATA_MIB, 0, sizeof(G_ETHSWT_DATA_MIB));
    LIB_memset((uint8*)&G_ETHSWT_DATA_SQI, 0, sizeof(G_ETHSWT_DATA_SQI));
    LIB_memset((uint8*)&G_ETHSWT_DATA_QCI, 0, sizeof(G_ETHSWT_DATA_QCI));

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_LoProc(void)
{
    ethswt_data_set_link();
    
    // (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_MCUINFO, sizeof(G_ETHSWT_DATA), (uint8*)&G_ETHSWT_DATA);

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_set_link(void)
{
    // uint8                   idx;
    // EthTrcv_LinkStateType   status;
    // Std_ReturnType          getResult;

    // for(idx = 0; idx < D_ETHSWT_DATA_USE_PORT_NUM; idx++) {
    //     getResult = EthSwt_SWIC_GetLinkState(D_ETHSWT_SWIC_ID, S_ETHSWT_DATA_IDX_TABLE[idx], &status);
    //     G_ETHSWT_DATA.portData[idx].linkStatus = status;
    //     G_ETHSWT_DATA.portData[idx].linkGetResult = getResult;
    // }

    return;
}
/* -------------------------------------------------------------------------- */
