/* bsw_bswm_cs_ctrl_c_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/CTRL/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_bswm_cs_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../inc/bsw_bswm_cs_config.h"
#if ( BSW_BSWM_CS_FUNC_BSWMCS == BSW_USE )

#include <nm/bsw_nm.h>
#include <com/bsw_com.h>

#include "../inc/bsw_bswm_cs_status.h"
#include "../inc/bsw_bswm_cs_ctrl.h"
#include "../inc/bsw_bswm_cs_ctrl_bswmeth.h"
#include "../inc/bsw_bswm_cs_ctrl_bswmlin.h"
#include "../inc/bsw_bswm_cs_ctrl_xcp.h"
#include "../inc/bsw_bswm_cs_connector.h"

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#include "../../Com/inc/bsw_com_config.h"
#endif

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
#include <bswm_can/bsw_bswm_can.h>
#endif

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

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_Init                                    */
/* Description   | Initialize the channel control unit                      */
/* Preconditions | When initializing, wake-up initialization, and resetting */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | NONE                                                     */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_Init( void )
{
    BswU1 u1Ch;
    BswU1 u1ChNum;

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#if ( BSW_COM_EVENTAWAKE_USE == BSW_USE )
    bsw_bswm_cs_ctrl_Init_EvtAwake();
#endif
#if ( BSW_COM_EVENTWAKEUPFRAME_USE == BSW_USE )
    bsw_bswm_cs_ctrl_Init_WkupEvt();
#endif
#endif

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    for( u1Ch = (BswU1)0U; u1Ch < u1ChNum; u1Ch++ )
    {
        bsw_bswm_cs_ctrl_u1TRXStatus[u1Ch] = (BswU1)BSW_BSWM_CS_TRXST_TRX_DISABLE;
    }

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
    /* Initialize channel power state */
    bsw_bswm_cs_ctrl_InitChPwStat();
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_CheckAwake                              */
/* Description   | Get CPUAwake factor                                      */
/* Preconditions | When processing is requested                             */
/* Parameters    | NONE                                                     */
/* Return Value  | CPUAwake factor                                          */
/*               |  BSW_BSWM_CS_AWAKE_NONE :No CPUAwake factor              */
/*               |  BSW_BSWM_CS_AWAKE_EXIST:CPUAwake factor exists          */
/* Notes         | Supported API : BswM_CS_CheckAwake                       */
/****************************************************************************/
uint8
bsw_bswm_cs_ctrl_CheckAwake( void )
{
    BswU1           u1Awake;
    BswU1           u1Channel;
    BswU1           u1ChannelNum;
    BswU1           u1TmpAwake;

    u1Awake = (BswU1)BSW_BSWM_CS_AWAKE_NONE;

    if( bsw_bswm_cs_st_u2CSStatus == BSW_BSWM_CS_u2PVTST_RUN )
    {
        /* Collect user Awake factors */
        bsw_bswm_cs_user_CbkSetBusAwake();

        u1ChannelNum = bsw_bswm_cs_ctrl_u1ChNum;
        for( u1Channel = (BswU1)0U; u1Channel < u1ChannelNum; u1Channel++ )
        {
            /* Check bus Awake factor */
            u1TmpAwake = ComM_GetBusAwakeKind( u1Channel );
            if( u1TmpAwake != (BswU1)COMM_BUSAWAKE_KIND_NONE )
            {
                u1Awake = (BswU1)BSW_BSWM_CS_AWAKE_EXIST;
                break;
            }
        }
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
        if( u1Awake == (BswU1)BSW_BSWM_CS_AWAKE_NONE )
        {
            u1Awake = BswM_Can_CheckAwake();
        }
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
        if( u1Awake == (BswU1)BSW_BSWM_CS_AWAKE_NONE )
        {
            u1Awake = bsw_bswm_cs_ctrl_BswMEthChkAwk();
        }
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
        if( u1Awake == (BswU1)BSW_BSWM_CS_AWAKE_NONE )
        {
            u1Awake = bsw_bswm_cs_ctrl_BswMLinChkAwk();
        }
#endif
    }
    return u1Awake;
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_DisableTx                               */
/* Description   | Disable Transmission                                     */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_DisableTx                        */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_DisableTx( NetworkHandleType Network )
{
    BswU1 u1ChNum;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        bsw_bswm_cs_ctrl_u1TRXStatus[Network] = (BswU1)BSW_BSWM_CS_TRXST_RX_ENABLE;

        bsw_bswm_cs_user_CbkDisableTx( Network );
    }
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_EnableTx                                */
/* Description   | Enable Transmission                                      */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_EnableTx                         */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_EnableTx( NetworkHandleType Network )
{
    BswU1 u1ChNum;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        bsw_bswm_cs_ctrl_u1TRXStatus[Network] = (BswU1)BSW_BSWM_CS_TRXST_TRX_ENABLE;

        bsw_bswm_cs_user_CbkEnableTx( Network );
    }
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_StopNetwork                             */
/* Description   | Stoped Communication                                     */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_StopNetwork                      */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_StopNetwork( NetworkHandleType Network )
{
    BswU1 u1ChNum;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        bsw_bswm_cs_ctrl_u1TRXStatus[Network] = (BswU1)BSW_BSWM_CS_TRXST_TRX_DISABLE;

#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
        bsw_bswm_cs_ctrl_XcpSuspend( Network );
#endif
        bsw_bswm_cs_user_CbkNetworkStop( Network );
    }
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_StartNetwork                            */
/* Description   | Start communication                                      */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_StartNetwork                     */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_StartNetwork( NetworkHandleType Network )
{
    BswU1 u1ChNum;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        bsw_bswm_cs_ctrl_u1TRXStatus[Network] = (BswU1)BSW_BSWM_CS_TRXST_RX_ENABLE;

#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
        bsw_bswm_cs_ctrl_XcpDrive( Network );
#endif
        bsw_bswm_cs_user_CbkNetworkStrt( Network );
    }
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_DetectChFail                            */
/* Description   | Processing when a channel failure is detected            */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_DetectChFail                     */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_DetectChFail( NetworkHandleType Network )
{
    BswU1 u1ChNum;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
        Com_ClearTxIpdu( Network, (Com_TxModeType)COM_TX_MODE_ALL );
#if ( BSW_COM_EVENTWAKEUPFRAME_USE == BSW_USE )
        bsw_cs_DI()
        bsw_bswm_cs_ctrl_EvtWkupClear( Network );
        Nm_CancelEvtWakeup( Network );
        bsw_cs_EI()
#endif
#endif
#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
        bsw_bswm_cs_ctrl_XcpClearTxReq( Network );
#endif
    }
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_ReleaseChFail                           */
/* Description   | Processing when a channel failure is recovered           */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_ReleaseChFail                    */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_ReleaseChFail( NetworkHandleType Network )
{
    BswU1          u1ChNum;
    Std_ReturnType u1Ret;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        u1Ret = bsw_bswm_cs_user_CbkPrFailClrEv( Network );
        if ( u1Ret == (Std_ReturnType)E_OK )
        {
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
            Com_ClearTxIpdu( Network, (Com_TxModeType)COM_TX_MODE_ALL );
#if ( BSW_COM_EVENTWAKEUPFRAME_USE == BSW_USE )
            bsw_cs_DI()
            bsw_bswm_cs_ctrl_EvtWkupClear( Network );
            Nm_CancelEvtWakeup( Network );
            bsw_cs_EI()
#endif
#endif
        }
        else
        {
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
            Com_ClearTxIpdu( Network, (Com_TxModeType)COM_TX_MODE_PERIODIC );
#endif
        }

#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
        bsw_bswm_cs_ctrl_XcpClearTxReq( Network );
#endif
    }
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_SetTxControl                            */
/* Description   | Set the event/periodic transmission status               */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/*               | uint8 TxStatus: Transmission enabled state               */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_SetTxControl                     */
/*               | Called on the DI state                                   */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_SetTxControl( NetworkHandleType Network, uint8 TxStatus )
{
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    Com_TxStatusType    u1TmpTxStatus;
    BswU1 u1ChNum;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        u1TmpTxStatus = (Com_TxStatusType)COM_TX_DISABLE;

        if( (TxStatus & (BswU1)BSW_BSWM_CS_COM_EV_TX_ENABLE) == (BswU1)BSW_BSWM_CS_COM_EV_TX_ENABLE )
        {
            u1TmpTxStatus |= (Com_TxStatusType)COM_EVENT_TX_ENABLE;
        }
        if( (TxStatus & (BswU1)BSW_BSWM_CS_COM_PERI_TX_ENABLE) == (BswU1)BSW_BSWM_CS_COM_PERI_TX_ENABLE )
        {
            u1TmpTxStatus |= (Com_TxStatusType)COM_PERIODIC_TX_ENABLE;
        }

        Com_SetTxStatus( Network, u1TmpTxStatus );
    }
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_ResetPeriTx                             */
/* Description   | Request a periodic transmission reset                    */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/*               | uint8 ResetReason: Periodic tx reset reason              */
/*               |               BSW_BSWM_CS_RSTR_BUSWAKEUP:Bus Wakeup      */
/*               |               BSW_BSWM_CS_RSTR_RESUMETX :Resume Tx       */
/*               | uint16 Offset            : Offset time                   */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_ResetPeriodicTx                  */
/*               | Called on the DI state                                   */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_ResetPeriTx( NetworkHandleType Network, uint8 ResetReason, uint16 offset )
{
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    BswU1 u1ChNum;
    uint8 u1TmpResetReason;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        if( ResetReason == (BswU1)BSW_BSWM_CS_RSTR_BUSWAKEUP )
        {
            u1TmpResetReason = (BswU1)COM_RSTR_BUSWAKEUP;
        }
        else
        {
            u1TmpResetReason = (BswU1)COM_RSTR_RESUMETX;
        }
        Com_ResetPeriodicTx( Network, u1TmpResetReason, offset );
    }
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_ClrNoAwkEvtPdu                          */
/* Description   | Clear the Awake non-target event transmission request    */
/* Preconditions | NONE                                                     */
/* Parameters    | NetworkHandleType Network: Channel                       */
/*               | uint32 NonBusAwakePw      :Non-bus Awake power           */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_ClearNonAwakeEvtIpdu             */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_ClrNoAwkEvtPdu( NetworkHandleType Network, BswConstR uint32* NonBusAwakePw )
{
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    BswU1 u1ChNum;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
        Com_ClearNonAwakeEvtTxIpdu( Network, NonBusAwakePw );
#endif
    }
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_ClearTxPdu                              */
/* Description   | Clear the message transmission request                   */
/* Preconditions | NONE                                                     */
/* Parameters    | NetworkHandleType Network: Channel                       */
/*               | mode         :Target of transmission request clearing    */
/*               |  BSW_BSWM_CS_COM_TX_MODE_PERIODIC :Periodic transmission */
/*               |  BSW_BSWM_CS_COM_TX_MODE_EVENT    :Event transmission    */
/*               |  BSW_BSWM_CS_COM_TX_MODE_ALL      :Event transmission + Periodic transmission*/
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_ClearTxPdu                       */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_ClearTxPdu( NetworkHandleType Network, uint8 clrTxMode )
{
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    BswU1 u1ChNum;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        if( clrTxMode == (uint8)BSW_BSWM_CS_COM_TX_MODE_ALL )
        {
            Com_ClearTxIpdu(Network, (Com_TxModeType)COM_TX_MODE_ALL);
        }
        else if( clrTxMode == (uint8)BSW_BSWM_CS_COM_TX_MODE_EVENT )
        {
            Com_ClearTxIpdu(Network, (Com_TxModeType)COM_TX_MODE_EVENT);
        }
        else if( clrTxMode == (uint8)BSW_BSWM_CS_COM_TX_MODE_PERIODIC )
        {
            Com_ClearTxIpdu(Network, (Com_TxModeType)COM_TX_MODE_PERIODIC);
        }
        else /* MISRA DEVIATION: no process */
        {
            /* no process */
        }
    }
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_SetXcpTxMode                            */
/* Description   | Set XCP mode                                             */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/*               | uint8 TxMode             : Transmit mode                 */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_SetXcpTxMode                     */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_SetXcpTxMode( NetworkHandleType Network, uint8 TxMode )
{
#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
    BswU1 u1ChNum;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        bsw_bswm_cs_ctrl_XcpSetTrnsMode( Network, TxMode );
    }
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_SetFirstTxStat                          */
/* Description   | Set first transmission status                            */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_SetFirstTxStatus                 */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_SetFirstTxStat( NetworkHandleType Network )
{
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    BswU1 u1ChNum;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        Com_SetFirstTxStatus( Network );
    }
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_BusWakeup                               */
/* Description   | Notify bus wake-up                                       */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NetworkHandleType Network: Channel                       */
/*               | uint8 WakeupKind: Wakeup Type                            */
/*               |                   BSW_BSWM_CS_WKUP_PWON:Power ON         */
/*               |                   BSW_BSWM_CS_WKUP_BS  :Bus Wakeup       */
/*               | uint16 DisableSend: DisableSend[Com Tick]                */
/*               | uint16 EnablePeriodic: EnablePeriodic[Com Tick]          */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_BusWakeup                        */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_BusWakeup( NetworkHandleType Network, uint8 WakeupKind, uint16 DisableSend, uint16 EnablePeriodic )
{
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    BswU1 u1ChNum;
    uint8 u1TmpWakeupKind;

    u1ChNum = bsw_bswm_cs_ctrl_u1ChNum;
    if( Network < u1ChNum )
    {
        if( WakeupKind == (BswU1)BSW_BSWM_CS_WKUP_BS )
        {
            u1TmpWakeupKind = (BswU1)COM_WKUP_BS;
        }
        else
        {
            u1TmpWakeupKind = (BswU1)COM_WKUP_PWON;
        }
        Com_BusWakeup( Network, u1TmpWakeupKind, DisableSend, EnablePeriodic );
    }
#endif
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* ( BSW_BSWM_CS_FUNC_BSWMCS == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-1-0          :2018/12/12                                             */
/*  v1-2-0          :2020/04/15                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-2-0          :2023/05/23                                             */
/*  v3-0-0          :2025/02/05                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
