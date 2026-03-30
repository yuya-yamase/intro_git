/* VCanAck_c_v1-0-0                                                         */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | VCanAck/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "VCanAck.h"
#include "VCanAck_Lcfg.h"
#include "VCanAck_Connector.h"
#include "ehvm.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define VCANACK_BUFFSIZE                        (4U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void VCanAck_Receive( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define VCANACK_START_SEC_VAR_CLEARED_32
#include <VCanAck_MemMap.h>
#define VCANACK_STOP_SEC_VAR_CLEARED_32
#include <VCanAck_MemMap.h>

#define VCANACK_START_SEC_VAR_POWER_ON_CLEARED_32
#include <VCanAck_MemMap.h>
#define VCANACK_STOP_SEC_VAR_POWER_ON_CLEARED_32
#include <VCanAck_MemMap.h>

#define VCANACK_START_SEC_VAR_INIT_32
#include <VCanAck_MemMap.h>
#define VCANACK_STOP_SEC_VAR_INIT_32
#include <VCanAck_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define VCANACK_START_SEC_CONST
#include <VCanAck_MemMap.h>
#define VCANACK_STOP_SEC_CONST
#include <VCanAck_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
#define VCANACK_START_SEC_CODE
#include <VCanAck_MemMap.h>
/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/**---------------------------------------------------------------------------
 * [Description] Initialize this module.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
FUNC(void, VCANACK_CODE)
VCanAck_Init( void )
{
    uint16 t_u2RxVccChCnt;

    /* Clear vcc tx channel */
    (void)ehvm_vcc_clear_channel( cu4VCanAck_TxVccCh ); /* Return value Unreferenced, because errors can only be caused by misconfiguration */

    /* Clear vcc rx channels */
    for ( t_u2RxVccChCnt = (uint16)0U; t_u2RxVccChCnt < cu2VCanAck_RxVccChNum; t_u2RxVccChCnt++ )
    {
        (void)ehvm_vcc_clear_channel( cu4VCanAck_RxVccChTbl[t_u2RxVccChCnt] ); /* Return value Unreferenced, because errors can only be caused by misconfiguration */
    }

    return;
}

/**---------------------------------------------------------------------------
 * [Description] Performs the processing of this module.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
FUNC(void, VCANACK_CODE)
VCanAck_MainFunction( void )
{
    /* Receive acknowledgement */
    VCanAck_Receive();

    return;
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**---------------------------------------------------------------------------
 * [Description] Transmit acknowledgement.
 * [Arguments]   t_u4CanId      : CAN ID
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
FUNC(void, VCANACK_CODE)
VCanAck_Transmit( VAR(Can_IdType, AUTOMATIC) t_u4CanId )
{
    /* Transmit acknowledgement */
    (void)ehvm_vcc_transmit( cu4VCanAck_TxVccCh, &t_u4CanId, (uint32)VCANACK_BUFFSIZE );

    return;
}

/****************************************************************************/
/* Callback Functions and Notifications                                     */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/**---------------------------------------------------------------------------
 * [Description] Receive acknowledgement.
 * [Arguments]   None
 * [Return]      None
 * [Notes]       None
 *--------------------------------------------------------------------------*/
static void VCanAck_Receive( void )
{
    uint32 t_u4CanId;
    uint32 t_u4RcvDataSize;
    uint16 t_u2RxVccChCnt;
    uint16 t_u2RxCnt;
    ehvm_std_return_t t_u1Ret;

    /* Loop vcc rx channels */
    for ( t_u2RxVccChCnt = (uint16)0U; t_u2RxVccChCnt < cu2VCanAck_RxVccChNum; t_u2RxVccChCnt++ )
    {
        for ( t_u2RxCnt = (uint16)0U; t_u2RxCnt < cu2VCanAck_RxLimit; t_u2RxCnt++ )
        {
            /* Recieve */
            t_u1Ret = ehvm_vcc_receive( cu4VCanAck_RxVccChTbl[t_u2RxVccChCnt], &t_u4CanId, (uint32)VCANACK_BUFFSIZE, &t_u4RcvDataSize );    /* MISRA DEVIATION: Not referenced before assignment by callee */
            if ( t_u1Ret == E_EHVM_RECEIVE_QUEUE_EMPTY )
            {
                break;
            }
            else if ( ( t_u1Ret == E_EHVM_OK )
                   && ( t_u4RcvDataSize == (uint32)VCANACK_BUFFSIZE ) )
            {
                /* Indicate to uppuer SW-C */
                VCanAck_Indication( t_u4CanId );
            }
            else
            {
                /* do nothing */
            }
        }
    }

    return;
}

#define VCANACK_STOP_SEC_CODE
#include <VCanAck_MemMap.h>

/**** End of File ***********************************************************/
