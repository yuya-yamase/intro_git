/* -------------------------------------------------------------------------- */
/* file name   : EthSwt_Stub.c                                                */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <LIB.h>
#include <Dio.h>
#include <Dio_Symbols.h>
#include "EthSwt_Stub.h"
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_STUB_SAIL_ON_FILTER        (3U)
#define D_ETHSWT_STUB_SAIL_OFF_FILTER       (3U)
#define D_ETHSWT_STUB_AOSS_ON_FILTER        (3U)
#define D_ETHSWT_STUB_AOSS_OFF_FILTER       (3U)
/* -------------------------------------------------------------------------- */
typedef struct
{
    uint8   Status;
    uint32  OnCount;
    uint32  OffCount;
} S_ETHSWT_STUB_COUNT;
/* -------------------------------------------------------------------------- */
static S_ETHSWT_STUB_COUNT  G_ETHSWT_STUB_SAIL;
static S_ETHSWT_STUB_COUNT  G_ETHSWT_STUB_AOSS;
/* -------------------------------------------------------------------------- */
static void ethswt_stub_SAILCount(uint8 status);
static void ethswt_stub_AOSSCount(uint8 status);
static void ethswt_stub_SAILDecisionStatus(void);
static void ethswt_stub_AOSSDecisionStatus(void);
/* -------------------------------------------------------------------------- */
void EthSwt_Stub_Init(void)
{
    G_ETHSWT_STUB_SAIL.Status = 0xFF;
    G_ETHSWT_STUB_SAIL.OnCount = 0u;
    G_ETHSWT_STUB_SAIL.OffCount = 0u;

    G_ETHSWT_STUB_AOSS.Status = 0xFF;
    G_ETHSWT_STUB_AOSS.OnCount = 0u;
    G_ETHSWT_STUB_AOSS.OffCount = 0u;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_Stub_Observe(void)
{
    uint8   SAILStatus;
    uint8   AOSSStatus;

    SAILStatus = Dio_ReadChannel(DIO_ID_PORT8_CH8);
    AOSSStatus = Dio_ReadChannel(DIO_ID_PORT17_CH0);

    ethswt_stub_SAILCount(SAILStatus);
    ethswt_stub_AOSSCount(AOSSStatus);

    ethswt_stub_SAILDecisionStatus();
    ethswt_stub_AOSSDecisionStatus();

    return;
}
/* -------------------------------------------------------------------------- */
uint8 EthSwt_Stub_GetSAIL(void)
{
    uint8   status;

    LIB_DI();
    status = G_ETHSWT_STUB_SAIL.Status;
    LIB_EI();

    return status;
}
/* -------------------------------------------------------------------------- */
uint8 EthSwt_Stub_GetAOSSS(void)
{
    uint8   status;

    LIB_DI();
    status = G_ETHSWT_STUB_AOSS.Status;
    LIB_EI();

    return status;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_Stub_GetDIN2(void)
{
    return STD_ON;
}
/* -------------------------------------------------------------------------- */
static void ethswt_stub_SAILCount(uint8 status)
{
    if (status == STD_LOW)
    {
        G_ETHSWT_STUB_SAIL.OnCount = 0u;
        G_ETHSWT_STUB_SAIL.OffCount++;
    }
    else
    {
        G_ETHSWT_STUB_SAIL.OnCount++;
        G_ETHSWT_STUB_SAIL.OffCount = 0u;
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_stub_AOSSCount(uint8 status)
{
    if (status == STD_LOW)
    {
        G_ETHSWT_STUB_AOSS.OnCount = 0u;
        G_ETHSWT_STUB_AOSS.OffCount++;;
    }
    else
    {
        G_ETHSWT_STUB_AOSS.OnCount++;
        G_ETHSWT_STUB_AOSS.OffCount = 0u;
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_stub_SAILDecisionStatus(void)
{
    if (G_ETHSWT_STUB_SAIL.OffCount >= D_ETHSWT_STUB_SAIL_OFF_FILTER)
    {
        G_ETHSWT_STUB_SAIL.Status = STD_LOW;
        G_ETHSWT_STUB_SAIL.OffCount = D_ETHSWT_STUB_SAIL_OFF_FILTER;
    } else
    if (G_ETHSWT_STUB_SAIL.OnCount >= D_ETHSWT_STUB_SAIL_ON_FILTER)
    {
        G_ETHSWT_STUB_SAIL.Status = STD_HIGH;
        G_ETHSWT_STUB_SAIL.OnCount = D_ETHSWT_STUB_SAIL_ON_FILTER;
    }
    else
    {
        /* do nothing */
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_stub_AOSSDecisionStatus(void)
{
    if (G_ETHSWT_STUB_AOSS.OffCount >= D_ETHSWT_STUB_AOSS_OFF_FILTER)
    {
        G_ETHSWT_STUB_AOSS.Status = STD_LOW;
        G_ETHSWT_STUB_AOSS.OffCount = D_ETHSWT_STUB_AOSS_OFF_FILTER;
    } else
    if (G_ETHSWT_STUB_AOSS.OnCount >= D_ETHSWT_STUB_AOSS_ON_FILTER)
    {
        G_ETHSWT_STUB_AOSS.Status = STD_HIGH;
        G_ETHSWT_STUB_AOSS.OnCount = D_ETHSWT_STUB_AOSS_ON_FILTER;
    }
    else
    {
        /* do nothing */
    }

    return;
}

