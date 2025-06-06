#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include "EthSwt_Data.h"
#include <EthSwt_BSW_define.h>
#include <EthSwt_SWIC.h>
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_DATA_USE_PORT_NUM          (6U)
/* -------------------------------------------------------------------------- */
typedef struct {
    Eth_ModeType            portMode;
    uint8                   indMode;
    EthTrcv_LinkStateType   linkStatus;
    Std_ReturnType          linkGetResult;
    uint8                   frameDiscardFactor[5];
    uint32                  ingressDiscardNum;
    uint32                  egressDiscardNum;
    uint8                   tcamInfo[4];
    uint8                   flowMeterInfo[4];
    uint8                   sqiValue;
    uint8                   sqiGetResult;
} S_ETHSWT_DATA_FOR_PORT;

typedef struct {
    EthSwt_StateType        ethswtStatus;
    S_ETHSWT_DATA_FOR_PORT  portData[D_ETHSWT_DATA_USE_PORT_NUM];
} S_ETHSWT_DATA_CHIPCOM;

typedef struct {
    uint8                   dataIdx;    /* S_ETHSWT_DATA_FOR_PORTÇÃIdx */
    uint8                   portIdx;    /* EthSwtÇ≈éùÇ¡ÇƒÇ¢ÇÈIdx        */
} S_ETHSWT_DATA_COMB;
static const S_ETHSWT_DATA_COMB S_ETHSWT_DATA_IDX_TABLE[D_ETHSWT_DATA_USE_PORT_NUM] =
/*                      dataIdx , portIdx   */
/* A-DC     */  {   {   0       , 1         }
/* DCM      */  ,   {   1       , 2         }
/* SAIL     */  ,   {   2       , 5         }
/* Tool     */  ,   {   3       , 6         }
/* Linux    */  ,   {   4       , 7         }
/* Android  */  ,   {   5       , 8         }
                };
/* -------------------------------------------------------------------------- */
static S_ETHSWT_DATA_CHIPCOM G_ETHSWT_DATA;
/* -------------------------------------------------------------------------- */
static void ethswt_data_get_linkStatus(void);
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void)
{
    // LIB_memset(((uint8*)&G_ETHSWT_DATA, 0, sizeof(G_ETHSWT_DATA)));

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_LoProc(void)
{
    ethswt_data_get_linkStatus();
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_get_linkStatus(void)
{
    uint8                   idx;
    EthTrcv_LinkStateType   status;
    Std_ReturnType          getResult;

    for(idx = 0; idx < D_ETHSWT_DATA_USE_PORT_NUM; idx++) {
        getResult = EthSwt_SWIC_GetLinkState(0, S_ETHSWT_DATA_IDX_TABLE[idx].portIdx, &status);
        G_ETHSWT_DATA.portData[idx].linkStatus = status;
        G_ETHSWT_DATA.portData[idx].linkGetResult = getResult;
    }

    return;
}