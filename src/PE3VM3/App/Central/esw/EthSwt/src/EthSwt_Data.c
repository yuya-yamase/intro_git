/* -------------------------------------------------------------------------- */
/* file name   : EthSwt_Data.c                                                */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include "EthSwt_Data.h"
#include "EthSwt_SWIC.h"
#include "LIB.h"
#include "EthSwt_BSW_define.h"
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_DATA_PORT_NUM          (9U)
/* -------------------------------------------------------------------------- */
typedef struct {
    uint32          portMode;
    uint8           indMode;
    uint8           linkState;
    uint8           linkGetResult;
    uint8           frameDiscardFactor[5];
    uint32          ingressDiscardNum;
    uint32          egressDiscardNum;
    uint8           tcamInfo[4];
    uint8           flowMeterInfo[4];
    uint8           sqiValue;
    uint8           sqiGetResult;
} S_PORT_DATA;

typedef struct {
    uint8           ethswtState;
    S_PORT_DATA     portData[6];
} S_DATA_FOR_SAIL;

typedef struct {
    uint8           enable;
    uint8           portDataIdx;
    uint8           switchIdx;
    uint8           switchPortIdx;
} S_PORT_CFG;
/* -------------------------------------------------------------------------- */
static S_DATA_FOR_SAIL  dataForSAIL;
static const S_PORT_CFG portDataDict[D_ETHSWT_DATA_PORT_NUM] =
/*                          Enable,     portDataIdx,    switchIdx,  swichPortIdx    }   */
/* 9: nouse     */ {    {   FALSE,      0,              0,          9               }
/* 1: A-DC      */ ,    {   TRUE,       0,              0,          1               }
/* 2: DCM       */ ,    {   TRUE,       1,              0,          2               }
/* 3: nouse     */ ,    {   FALSE,      0,              0,          3               }
/* 4: nouse     */ ,    {   FALSE,      0,              0,          4               }
/* 5: SAIL      */ ,    {   TRUE,       2,              0,          5               }
/* 6: Tool      */ ,    {   TRUE,       3,              0,          6               }
/* 7: Linux/QNX */ ,    {   TRUE,       4,              0,          7               }
/* 8: Android   */ ,    {   TRUE,       5,              0,          8               }
};
/* -------------------------------------------------------------------------- */
static void ethswt_data_set_linkState(void);
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void)
{
    LIB_memset((uint8*)&dataForSAIL, 0, sizeof(dataForSAIL));

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Data_MidProc(void)
{
    ethswt_data_set_linkState();

    /* ChipComに送信データセット */

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_data_set_linkState(void)
{
    uint8                   idx;
    Std_ReturnType          result;
    EthTrcv_LinkStateType   state;

    for (idx = 0; idx < D_ETHSWT_DATA_PORT_NUM; idx++)
    {
        if (portDataDict[idx].enable == TRUE)
        {
            result = EthSwt_SWIC_GetLinkState(portDataDict[idx].switchIdx, portDataDict[idx].switchPortIdx, &state);
            dataForSAIL.portData[portDataDict[idx].portDataIdx].linkGetResult = (uint8)result;
            dataForSAIL.portData[portDataDict[idx].portDataIdx].linkState = (uint8)state;
        }
    }
    return;
}
