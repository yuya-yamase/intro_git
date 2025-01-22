/* bsw_cantp_snd_c_v3-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/SND/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_cantp_MemMap.h"

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"

#if( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
#include <canif/bsw_canif.h>
#include <cantp/bsw_cantp.h>
#include <pdur/bsw_pdur.h>

#include "../cfg/CanTp_Cfg.h"
#include "../inc/bsw_cantp_cmn.h"

#include "../inc/bsw_cantp_config.h"

#include "../inc/bsw_cantp_snd.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Max Network Handle */
#define BSW_CANTP_SND_u1MAX_NETWORKNUM          ((uint8)32U)

/* Transmission state */
#define BSW_CANTP_SND_u1TXENABLE                ((uint8)0x5AU)
#define BSW_CANTP_SND_u1TXDISABLE               ((uint8)0xA5U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#if( BSW_CANTP_CFG_DISABLE_TX == BSW_USE )
static uint8 bsw_cantp_snd_GetTxState( PduIdType u2CanIfTxPduId );
#endif  /* BSW_CANTP_CFG_DISABLE_TX == BSW_USE */

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#if( BSW_CANTP_CFG_DISABLE_TX == BSW_USE )
static uint8 bsw_cantp_snd_u1SendState[BSW_CANTP_SND_u1MAX_NETWORKNUM];

#endif  /* BSW_CANTP_CFG_DISABLE_TX == BSW_USE */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | bsw_cantp_snd_EnableTx                                   */
/* Description   | Allow transmission                                       */
/* Preconditions | None                                                     */
/* Parameters    | network       : Network Handle                           */
/* Return Value  | None                                                     */
/* Notes         | Supported API : CanTp_EnableTx                           */
/****************************************************************************/
void
bsw_cantp_snd_EnableTx( NetworkHandleType network )
{
#if( BSW_CANTP_CFG_DISABLE_TX == BSW_USE )
    uint8   u1_NetId;   /* Network ID */

    u1_NetId = (uint8)network;
    if( u1_NetId < BSW_CANTP_SND_u1MAX_NETWORKNUM )
    {
        bsw_cantp_snd_u1SendState[u1_NetId] = BSW_CANTP_SND_u1TXENABLE;
        bsw_cantp_snd_CbkEnableTx( network );
    }
#endif  /* BSW_CANTP_CFG_DISABLE_TX == BSW_USE */

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_snd_DisableTx                                  */
/* Description   | Prohibit transmission                                    */
/* Preconditions | None                                                     */
/* Parameters    | network       : Network Handle                           */
/* Return Value  | None                                                     */
/* Notes         | Supported API : CanTp_DisableTx                          */
/****************************************************************************/
void
bsw_cantp_snd_DisableTx( NetworkHandleType network )
{
#if( BSW_CANTP_CFG_DISABLE_TX == BSW_USE )
    uint8   u1_NetId;   /* Network ID */

    u1_NetId = (uint8)network;
    if( u1_NetId < BSW_CANTP_SND_u1MAX_NETWORKNUM )
    {
        bsw_cantp_snd_u1SendState[u1_NetId] = BSW_CANTP_SND_u1TXDISABLE;
        bsw_cantp_snd_CbkDisableTx( network );
    }
#endif  /* BSW_CANTP_CFG_DISABLE_TX == BSW_USE */

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_snd_InitSnd                                    */
/* Description   | Initialization of Snd                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_snd_InitSnd( void )
{
#if( BSW_CANTP_CFG_DISABLE_TX == BSW_USE )
    uint8   u1_NetId;   /* Network ID */

    for( u1_NetId = (uint8)0U; u1_NetId < BSW_CANTP_SND_u1MAX_NETWORKNUM; u1_NetId++ )
    {
        bsw_cantp_snd_u1SendState[u1_NetId] = BSW_CANTP_SND_u1TXDISABLE;
    }
#endif  /* BSW_CANTP_CFG_DISABLE_TX == BSW_USE */

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_snd_CheckRam_Snd                               */
/* Description   | Check transmission state                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_snd_CheckRam_Snd( void )
{
#if( BSW_CANTP_CFG_DISABLE_TX == BSW_USE )
    uint8   u1_NetId;       /* Network ID          */
    uint8   u1_SendState;   /* SendState           */

    for( u1_NetId = (uint8)0U; u1_NetId < BSW_CANTP_SND_u1MAX_NETWORKNUM; u1_NetId++ )
    {
        u1_SendState = bsw_cantp_snd_u1SendState[u1_NetId];

        if( ( u1_SendState != BSW_CANTP_SND_u1TXENABLE )
        &&  ( u1_SendState != BSW_CANTP_SND_u1TXDISABLE ) )
        {
            /* Fatal */
            bsw_cantp_cmn_u1ErrState = BSW_CANTP_u1RAMERR;
            break;
        }
    }

#endif  /* BSW_CANTP_CFG_DISABLE_TX == BSW_USE */

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_snd_SendMessage                                */
/* Description   | Send message control                                     */
/* Preconditions | None                                                     */
/* Parameters    | u2CanIfTxPduId : CanIf Tx PduId                          */
/*               | ptTpPduInfo    : Pointer to transmission information     */
/* Return Value  | Bsw_CanTp_ReturnType                                     */
/*               |  BSW_CANTP_E_OK     : valid                              */
/*               |  BSW_CANTP_E_NOT_OK : invalid                            */
/* Notes         | None                                                     */
/****************************************************************************/
Bsw_CanTp_ReturnType
bsw_cantp_snd_SendMessage( PduIdType CanIfTxPduId, BswConstR PduInfoType * ptTpPduInfo )
{
    Std_ReturnType              u1_CanIfTxRet;     /* Result of CanIf_Transmit */
    Bsw_CanTp_PreSendReturnType u1_SendCtrlRet;    /* Result of USendControl   */
#if ( BSW_CANTP_CFG_DISABLE_TX == BSW_USE )
    uint8                       u1_TxEnableRet;    /* Result of TxState        */
#endif /* BSW_CANTP_CFG_DISABLE_TX == BSW_USE */
    Bsw_CanTp_ReturnType        u1_Ret;            /* Return value             */

    u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_NOT_OK;

    /* Check TxEnable */
#if ( BSW_CANTP_CFG_DISABLE_TX == BSW_USE )
    u1_TxEnableRet = bsw_cantp_snd_GetTxState( CanIfTxPduId );
    if( u1_TxEnableRet == BSW_CANTP_SND_u1TXENABLE )
#endif /* BSW_CANTP_CFG_DISABLE_TX == BSW_USE */
    {
        /* Check SendControl by user */
        u1_SendCtrlRet = bsw_cantp_tx_CbkPreSendControl( CanIfTxPduId, ptTpPduInfo );
        if( u1_SendCtrlRet == (Bsw_CanTp_PreSendReturnType)BSW_CANTP_PRESEND_TP )
        {
            /* Send message to CanIf */
            u1_CanIfTxRet = CanIf_Transmit( CanIfTxPduId, ptTpPduInfo );
            if( u1_CanIfTxRet == (Std_ReturnType)E_OK )
            {
                u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
            }
        }
        else
        {
            if( u1_SendCtrlRet == (Bsw_CanTp_PreSendReturnType)BSW_CANTP_PRESEND_USER_OK )
            {
                u1_Ret = (Bsw_CanTp_ReturnType)BSW_CANTP_E_OK;
            }
        }
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_snd_AbortSend                                  */
/* Description   | Transmission abort                                       */
/* Preconditions | None                                                     */
/* Parameters    | u2CanIfTxPduId : CanIf Tx PduId                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_cantp_snd_AbortSend( uint16 u2CanIfTxPduId )
{
#if( BSW_CANTP_CFG_ABORT_TX == BSW_USE )
    Std_ReturnType  u1_AbortSendCtrlRet;    /* Result of UAbortSendControl */

    /* Check AbortSendControl by user */
    u1_AbortSendCtrlRet = bsw_cantp_tx_CbkPreAbrtSndCtrl( u2CanIfTxPduId );
    if( u1_AbortSendCtrlRet == (Std_ReturnType)E_OK )
    {
        (void)CanIf_CancelTransmit( (PduIdType)u2CanIfTxPduId );    /* MISRA DEVIATION: no return check required */
    }

#endif  /* BSW_CANTP_CFG_ABORT_TX == BSW_USE */

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if( BSW_CANTP_CFG_DISABLE_TX == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_cantp_snd_GetTxState                                 */
/* Description   | Get transmission enable state                            */
/* Preconditions | None                                                     */
/* Parameters    | u2CanIfTxPduId : CanIf Tx PduId                          */
/* Return Value  | uint8                                                    */
/*               |  BSW_CANTP_SND_u1TXENABLE  : enable                      */
/*               |  BSW_CANTP_SND_u1TXDISABLE : disable                     */
/* Notes         | None                                                     */
/****************************************************************************/
static uint8
bsw_cantp_snd_GetTxState( PduIdType u2CanIfTxPduId )
{
    uint8   u1_NetId;   /* Network Hanble Id */
    uint8   u1_Ret;     /* Return value      */

    u1_NetId = CanIf_GetTxControllerId( u2CanIfTxPduId );
    u1_Ret   = bsw_cantp_snd_u1SendState[u1_NetId];

    return u1_Ret;
}
#endif  /* BSW_CANTP_CFG_DISABLE_TX == BSW_USE */


#endif /* BSW_BSWM_CS_FUNC_CANTP == BSW_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-1-0          :2019/01/15                                             */
/*  v1-2-0          :2020/01/23                                             */
/*  v2-0-0          :2022/01/14                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
