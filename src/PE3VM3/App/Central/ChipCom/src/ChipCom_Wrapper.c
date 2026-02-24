/* ChipCom_Wrapper_c_v1-0-0                                                 */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | ChipCom/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "ChipCom.h"
#include "ChipCom_Lcfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>

#define CHIPCOM_START_SEC_VAR_POWER_ON_CLEARED_32
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_VAR_POWER_ON_CLEARED_32
#include <ChipCom_MemMap.h>

#define CHIPCOM_START_SEC_VAR_INIT_32
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_VAR_INIT_32
#include <ChipCom_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_CONST
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_CONST
#include <ChipCom_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_CODE
#include <ChipCom_MemMap.h>

/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**---------------------------------------------------------------------------
 * ChipCom_SetPeriodicTxData
 *--------------------------------------------------------------------------*/
Std_ReturnType ChipCom_SetPeriodicTxData( const uint8 periodic_id, const uint16 trans_len, const uint8* const trans_data )
{
#if CHIPCOM_TEST_MD == CHIPCOM_TEST_MD_DRV
	return (Std_ReturnType)E_OK;
#else
	Std_ReturnType t_u1Rtn;
	uint16 t_u2SignalId;

	t_u2SignalId = (uint16)periodic_id;
	t_u1Rtn = ChipCom_SendSignal( t_u2SignalId, (const void*)trans_data );

	return t_u1Rtn;
#endif
}

/**---------------------------------------------------------------------------
 * ChipCom_GetPeriodicRxData
 *--------------------------------------------------------------------------*/
Std_ReturnType ChipCom_GetPeriodicRxData( const uint8 periodic_id, uint16* receive_len, uint8* receive_data, uint32* receive_counter )
{
#if CHIPCOM_TEST_MD == CHIPCOM_TEST_MD_DRV
	return (Std_ReturnType)E_OK;
#else
	Std_ReturnType t_u1Rtn;
	uint16 t_u2SignalId;
	uint16 t_u2SignalIdSeq;
	uint16 t_u2MsgId;
	uint32 t_u4SeqNo;

	t_u2SignalId = (uint16)periodic_id;

	t_u1Rtn = ChipCom_ReceiveSignal( t_u2SignalId, (void*)receive_data );

	if ( t_u1Rtn == (Std_ReturnType)E_OK )
	{
		t_u2MsgId = ChipCom_cu2DataHdl2MsgHdlTbl[t_u2SignalId];
		t_u2SignalIdSeq = ChipCom_cu2MsdId2SeqDataId[t_u2MsgId];

		t_u1Rtn = ChipCom_ReceiveSignal( t_u2SignalIdSeq, (void*)&t_u4SeqNo );
	}

	*receive_counter = t_u4SeqNo;

	return t_u1Rtn;
#endif
}

/**---------------------------------------------------------------------------
 * ChipCom_GetIPDUStatus
 *--------------------------------------------------------------------------*/
ChipCom_IpduStatusType ChipCom_GetIPDUStatus( ChipCom_PduIdType ChipCom_PduId )
{
	ChipCom_IpduStatusType t_u1Sts;

	t_u1Sts = ChipCom_GetSignalStatus( (Com_SignalIdType)ChipCom_PduId );

	return t_u1Sts;
}

/****************************************************************************/
/* Callback Functions and Notifications                                     */
/****************************************************************************/

#define CHIPCOM_STOP_SEC_CODE
#include <ChipCom_MemMap.h>

/**** End of File ***********************************************************/
