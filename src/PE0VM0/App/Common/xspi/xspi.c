/****************************************************************************/
/*【ファイル名】xspi.c                                                 */
/*【モジュール名】XSPIドライバ			                                	*/
/****************************************************************************/
#include "xspi.h"

/* VN-HILS向け CPU1コア 3チャンネル対応 */

void	xspi_Init_ivi(uint8 ch);
void	xspi_Init_meter(uint8 ch);
void	xspi_Init_central(uint8 ch);
void	xspi_DeInit_ivi(uint8 ch);
void	xspi_DeInit_meter(uint8 ch);
void	xspi_DeInit_central(uint8 ch);
uint8	xspi_GetCondition_ivi(uint8 ch);
uint8	xspi_GetCondition_meter(uint8 ch);
uint8	xspi_GetCondition_central(uint8 ch);
uint8	xspi_Write_ivi(uint8 ch, const uint8* addr, uint32 size );
uint8	xspi_Write_meter(uint8 ch, const uint8* addr, uint32 size );
uint8	xspi_Write_central(uint8 ch, const uint8* addr, uint32 size );
uint8	xspi_Read_ivi(uint8 ch, uint8* addr, uint32 size );
uint8	xspi_Read_meter(uint8 ch, uint8* addr, uint32 size );
uint8	xspi_Read_central(uint8 ch, uint8* addr, uint32 size );
void	xspi_Main_ivi(uint8 ch);
void	xspi_Main_meter(uint8 ch);
void	xspi_Main_central(uint8 ch);
uint8	xspi_GetErrInfo_ivi(uint8 ch);
uint8	xspi_GetErrInfo_meter(uint8 ch);
uint8	xspi_GetErrInfo_central(uint8 ch);

void	xspi_Init(
	uint8	ch
)
{
	switch(ch)
	{
		case XSPI_CH_01:
			xspi_Init_ivi(ch);
			break;
		case XSPI_CH_02:
			xspi_Init_meter(ch);
			break;
		case XSPI_CH_03:
			xspi_Init_central(ch);
			break;
		default:
			break;
	}
}

void	xspi_DeInit(
	uint8	ch
)
{
	switch(ch)
	{
		case XSPI_CH_01:
			xspi_DeInit_ivi(ch);
			break;
		case XSPI_CH_02:
			xspi_DeInit_meter(ch);
			break;
		case XSPI_CH_03:
			xspi_DeInit_central(ch);
			break;
		default:
			break;
	}
}

uint8	xspi_GetCondition(
	uint8 ch
)
{
	uint8 ret = XSPI_DCOND_INIT;

	switch(ch)
	{
		case XSPI_CH_01:
			ret = xspi_GetCondition_ivi(ch);
			break;
		case XSPI_CH_02:
			ret = xspi_GetCondition_meter(ch);
			break;
		case XSPI_CH_03:
			ret = xspi_GetCondition_central(ch);
			break;
		default:
			break;
	}

	return( ret );
}

uint8	xspi_Write(
	uint8 ch,	const uint8* addr,	uint32 size
)
{
	uint8 result = XSPI_NG;

	switch(ch)
	{
		case XSPI_CH_01:
			result = xspi_Write_ivi(ch, addr, size);
			break;
		case XSPI_CH_02:
			result = xspi_Write_meter(ch, addr, size);
			break;
		case XSPI_CH_03:
			result = xspi_Write_central(ch, addr, size);
			break;
		default:
			result = XSPI_NG;
			break;
	}

	return( result );
}

uint8	xspi_Read(
	uint8 ch,	uint8* addr,	uint32 size
)
{
	uint8 result = XSPI_NG;

	switch(ch)
	{
		case XSPI_CH_01:
			result = xspi_Read_ivi(ch, addr, size);
			break;
		case XSPI_CH_02:
			result = xspi_Read_meter(ch, addr, size);
			break;
		case XSPI_CH_03:
			result = xspi_Read_central(ch, addr, size);
			break;
		default:
			result = XSPI_NG;
			break;
	}

	return( result );
}

void	xspi_Main(
	uint8	ch
)
{
	switch(ch)
	{
		case XSPI_CH_01:
			xspi_Main_ivi(ch);
			break;
		case XSPI_CH_02:
			xspi_Main_meter(ch);
			break;
		case XSPI_CH_03:
			xspi_Main_central(ch);
			break;
		default:
			break;
	}
}

uint8	xspi_GetErrInfo(
	uint8	ch
)
{
	uint8 ret = XSPI_ERR_KIND_NONE;

	switch(ch)
	{
		case XSPI_CH_01:
			ret = xspi_GetErrInfo_ivi(ch);
			break;
		case XSPI_CH_02:
			ret = xspi_GetErrInfo_meter(ch);
			break;
		case XSPI_CH_03:
			ret = xspi_GetErrInfo_central(ch);
			break;
		default:
			break;
	}

	return( ret );
}
