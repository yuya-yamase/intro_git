/* -------------------------------------------------------------------------- */
/* file name  :  VIS_Stub.c													  */
/* -------------------------------------------------------------------------- */
#include "VIS.h"
#include "VIS_CAN.h"
#include "VIS_Stub.h"
/* -------------------------------------------------------------------------- */
/* #define VIS_START_SEC_CODE */
/* #include <VIS_MemMap.h> */
/* -------------------------------------------------------------------------- */
void stub_getcyc(void)
{
	ST_VIS_UTC utcdata;
	U4 ododata;
	U1 spddata;
	U1 rdysts;
	U1 batvolt;
	
	(void)u1_g_VISCanUTCGetData (&utcdata);
	(void)u1_g_VISCanOdoGetData (&ododata);
	(void)u1_g_VISCanSpdGetData (&spddata);
	(void)u1_g_VISCanEPwrCtrlSysRdystsGetData (&rdysts);
	batvolt = (U1)u1_g_VISPwrBatVoltGet();
	
	return;
}
/* -------------------------------------------------------------------------- */
/* define VIS_STOP_SEC_CODE */
/* #include "VIS_MemMap.h> */
/* -------------------------------------------------------------------------- */
