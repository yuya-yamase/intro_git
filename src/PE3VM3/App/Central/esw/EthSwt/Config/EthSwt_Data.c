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
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_ADC_PORT_ID               (0U)
#define D_ETHSWT_SWIC_DCM_PORT_ID               (1U)
#define D_ETHSWT_SWIC_SAIL_PORT_ID              (4U)
#define D_ETHSWT_SWIC_TOOL_PORT_ID              (5U)
#define D_ETHSWT_SWIC_LINUX_PORT_ID             (6U)
#define D_ETHSWT_SWIC_ANDROID_PORT_ID           (7U)

/* -------------------------------------------------------------------------- */
// typedef struct {
//     uint8                   dataIdx;    /* S_ETHSWT_DATA_FOR_PORTÇÃIdx */
//     uint8                   portIdx;    /* EthSwtÇ≈éùÇ¡ÇƒÇ¢ÇÈIdx        */
// } S_ETHSWT_DATA_COMB;
// static const S_ETHSWT_DATA_COMB S_ETHSWT_DATA_IDX_TABLE[D_ETHSWT_DATA_USE_PORT_NUM] =
// /*                      dataIdx , portIdx   */
// /* A-DC     */  {   {   0       , D_ETHSWT_SWIC_ADC_PORT_ID         }
// /* DCM      */  ,   {   1       , D_ETHSWT_SWIC_DCM_PORT_ID         }
// /* SAIL     */  ,   {   2       , D_ETHSWT_SWIC_SAIL_PORT_ID        }
// /* Tool     */  ,   {   3       , D_ETHSWT_SWIC_TOOL_PORT_ID        }
// /* Linux    */  ,   {   4       , D_ETHSWT_SWIC_LINUX_PORT_ID       }
// /* Android  */  ,   {   5       , D_ETHSWT_SWIC_ANDROID_PORT_ID     }
//                 };

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
static S_ETHSWT_DATA_CHIPCOM G_ETHSWT_DATA;
/* -------------------------------------------------------------------------- */
static void ethswt_data_get_linkStatus(void);

/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void)
{
    LIB_memset((uint8*)&G_ETHSWT_DATA, 0, sizeof(G_ETHSWT_DATA));

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_LoProc(void)
{
    ethswt_data_get_linkStatus();
    
    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_MCUINFO, sizeof(G_ETHSWT_DATA), (uint8*)&G_ETHSWT_DATA);

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_get_linkStatus(void)
{
    uint8                   idx;
    EthTrcv_LinkStateType   status;
    Std_ReturnType          getResult;

    for(idx = 0; idx < D_ETHSWT_DATA_USE_PORT_NUM; idx++) {
        getResult = EthSwt_SWIC_GetLinkState(0, S_ETHSWT_DATA_IDX_TABLE[idx], &status);
        G_ETHSWT_DATA.portData[idx].linkStatus = status;
        G_ETHSWT_DATA.portData[idx].linkGetResult = getResult;
    }

    return;
}
/* -------------------------------------------------------------------------- */
