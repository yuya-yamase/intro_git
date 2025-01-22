#include <Std_Types.h>
#include <EthSwt.h>
#include "EthSwt_SWIC_Org.h"
#include <Dio_Symbols.h>
#include <Dio.h>
#include <gpt_drv_frt.h>
#include <Port_Cfg.h>
#include <Port.h>

#define ETHSWT_SWIC_RST_ON  ((void)Dio_WriteChannel( DIO_ID_APORT4_CH1, STD_LOW))
#define ETHSWT_SWIC_RST_OFF ((void)Dio_WriteChannel( DIO_ID_APORT4_CH1, STD_HIGH))

#define ETHSWT_SWIC_PORT_SPISTATE_NOTAVAILABLE   (0U)
#define ETHSWT_SWIC_PORT_SPISTATE_AVAILABLE      (1U)
#define ETHSWT_SWIC_PORT_DAT_0                   (0U)
#define ETHSWT_SWIC_PORT_DAT_MAX                 (0xFFU)
#define ETHSWT_SWIC_PORT_T8_T9_TIME              (17U)   /* 85ms(5ms*17) */
#define ETHSWT_SWIC_PORT_MODE_SPI                (0U)
#define ETHSWT_SWIC_PORT_MODE_GPO                (1U)

static U1 u1_s_Port_TaskCounter;
static U1 u1_s_Port_SpiSts;
static void EthSwt_SWIC_Org_Port_SetSpiPortMode( uint8 u1SetModeIndex );

#define	ETHSWT_START_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
void EthSwt_SWIC_Org_WaitMS(const uint32 tmo)
{ /* 最大10ms待ちまで対応 */
	uint32	i;
	uint32	StartTime = 0u;
	uint32	EndTime = 0u;

	StartTime = u4_g_Gpt_FrtGetUsElapsed(((void *)0));
    /* ★暫定 BSWの変更により命令数に差分があるため見直しが必要 */
	for (i = 0u; i < 100000u; i++) {		/* CPU：400MHz 10ms / (40命令*2.5ns) = 100000 */
		EndTime = u4_g_Gpt_FrtGetUsElapsed(((void *)0));
		if (((uint32)EndTime - (uint32)StartTime) >= (tmo * 80000u)) {  /* LSB 0.0125usのためtmo*80000で判定 */
			break;
		}
	}
	return;
}
void EthSwt_SWIC_Org_WaitSPI(void)
{ /* SPIモード設定完了まで待ち */
	uint32	i;
    /* ★暫定 BSWの変更により命令数に差分があるため見直しが必要 */
	for (i = 0u; i < 8000000u; i++) {		/* CPU：400MHz 100ms / (5命令 * 2.5ns) =8000000 */
		if (u1_s_Port_SpiSts == (uint8)ETHSWT_SWIC_PORT_SPISTATE_AVAILABLE) {
			break;
		}
	}
	return;
}
void EthSwt_SWIC_Org_Reset(void)
{
	ETHSWT_SWIC_RST_ON;			/* SW-IC RESETNアサート */
	EthSwt_SWIC_Org_WaitMS(1);	/* T1時間Wait */
	ETHSWT_SWIC_RST_OFF;		/* SW-IC RESETNディアサート */
	EthSwt_SWIC_Org_WaitMS(5);	/* T2時間Wait */
}
Std_ReturnType EthSwt_SWIC_Org_INTN(void)
{
	Dio_LevelType u1Level = STD_HIGH;
	u1Level=Dio_ReadChannel(DIO_ID_APORT4_CH0);
	return (u1Level == STD_LOW) ? E_NOT_OK : E_OK;
}
void EthSwt_SWIC_Org_ResetSig_Hi(void)
{
    ETHSWT_SWIC_RST_OFF;
    return;
}
void EthSwt_SWIC_Org_ResetSig_Lo(void)
{
    ETHSWT_SWIC_RST_ON;
    return;
}
void EthSwt_SWIC_Org_Init(void){
	u1_s_Port_TaskCounter = (uint8)ETHSWT_SWIC_PORT_DAT_0;
	EthSwt_SWIC_Org_Port_SetSpiPortMode( (uint8)ETHSWT_SWIC_PORT_MODE_GPO );
	u1_s_Port_SpiSts     = (uint8)ETHSWT_SWIC_PORT_SPISTATE_NOTAVAILABLE;
}
void EthSwt_SWIC_Org_MainFunction(void)  /* 5ms定期 */
{
    if ( u1_s_Port_TaskCounter < (uint8)ETHSWT_SWIC_PORT_DAT_MAX )
    {
        u1_s_Port_TaskCounter++;
    }

    if ( u1_s_Port_TaskCounter >= (uint8)ETHSWT_SWIC_PORT_T8_T9_TIME )
    {
        (void)EthSwt_SWIC_Org_Port_SetSpiPortMode( (uint8)ETHSWT_SWIC_PORT_MODE_SPI );
        u1_s_Port_SpiSts = (uint8)ETHSWT_SWIC_PORT_SPISTATE_AVAILABLE;
    }

    return;
}
static void EthSwt_SWIC_Org_Port_SetSpiPortMode( uint8 u1SetModeIndex )
{
    /* SPI mode */
    if( u1SetModeIndex == ETHSWT_SWIC_PORT_MODE_SPI ){
        Port_SetPinMode( PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_0 );
        Port_SetPinMode( PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_1 );
        Port_SetPinMode( PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_2 );
        Port_SetPinMode( PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_3 );
    }
    /* GPIO mode */
    else{
#if 0   /* ★PortConfigのMode定義対応待ち */
        Port_SetPinMode( PORT_ID_PORT2_PIN11, **** );
        Port_SetPinMode( PORT_ID_PORT2_PIN12, **** );
        Port_SetPinMode( PORT_ID_PORT2_PIN13, **** );
        Port_SetPinMode( PORT_ID_PORT2_PIN14, **** );
#endif
    }
}

#define	ETHSWT_STOP_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
