#include <Std_Types.h>
#include "EthSwt_SWIC_Org.h"
#include <Dio_Symbols.h>
#include <Dio.h>
#include <gpt_drv_frt.h>

#define ETHSWT_SWIC_RST_ON  ((void)Dio_WriteChannel( DIO_ID_APORT4_CH1, STD_LOW))
#define ETHSWT_SWIC_RST_OFF ((void)Dio_WriteChannel( DIO_ID_APORT4_CH1, STD_HIGH))

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

void EthSwt_SWIC_Org_Reset(void)
{
	ETHSWT_SWIC_RST_ON;			/* SW-IC RESETNアサート */
	EthSwt_SWIC_Org_WaitMS(1);	/* T1時間Wait */
	ETHSWT_SWIC_RST_OFF;		/* SW-IC RESETNディアサート */
	EthSwt_SWIC_Org_WaitMS(5);	/* T2時間Wait */
}