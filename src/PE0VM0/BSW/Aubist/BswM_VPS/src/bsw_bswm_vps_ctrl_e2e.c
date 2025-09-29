/* bsw_bswm_vps_ctrl_e2e_c_v3-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/VPS/CTRL/E2E/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <cs/bsw_cs_system_memmap_pre.h>
#include <ComStack_Types.h>

#include <comm/bsw_comm.h>
#include <bswm_cs/bsw_bswm_cs.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#include <cs/bsw_cs_system_memmap_post.h>

#if( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
#include <cs/bsw_cs_system_memmap_pre.h>
#include <bswm_vps/bsw_bswm_vps.h>
#include "../inc/bsw_bswm_vps_ctrl.h"
#include "../inc/bsw_bswm_vps_config.h"
#include <cs/bsw_cs_system_memmap_post.h>

#if( BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE )
#include <E2E.h>
#include <cs/bsw_cs_system_memmap_pre.h>
#include "../inc/bsw_bswm_vps_ctrl_e2e.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_VPS_BITIND_BYTEPOS_SHIFT    (3U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static uint8 bsw_bswm_vps_ctrl_E2ECheck(uint8 u1RxIdx, BswConstR uint8* DataPtr);

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
/* Function Name | bsw_bswm_vps_InitE2E                                     */
/* Description   | Initialize                                               */
/* Preconditions | Caller:BswM/CS, User                                     */
/*               | Timing:At startup                                        */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | NONE                                                     */
/****************************************************************************/
void
bsw_bswm_vps_ctrl_E2EInit( void )
{
    BswU1 u1CfgE2EProtectTxMsgNum;
    BswU1 u1CfgE2EProtectRxMsgNum;
    BswU1 u1MsgIdx;
    
    /* E2E initialize */
    u1CfgE2EProtectTxMsgNum = bsw_bswm_vps_u1E2EProtectTxMsgNum;
    u1CfgE2EProtectRxMsgNum = bsw_bswm_vps_u1E2EProtectRxMsgNum;
    /* Tx Message */
    for (u1MsgIdx = (BswU1)0U; u1MsgIdx < u1CfgE2EProtectTxMsgNum; u1MsgIdx++)
    {
        (void)E2E_P05ProtectInit( &bsw_bswm_vps_stTxProtectState[u1MsgIdx] ); /* MISRA DEVIATION: no return check required */
    }
    /* Rx Message */
    for (u1MsgIdx = (BswU1)0U; u1MsgIdx < u1CfgE2EProtectRxMsgNum; u1MsgIdx++)
    {
        (void)E2E_P05CheckInit( &bsw_bswm_vps_stRxCheckState[u1MsgIdx] ); /* MISRA DEVIATION: no return check required */
    }
}

/****************************************************************************/
/* Function Name | bsw_bswm_vps_E2ETxProtect                                */
/* Description   | E2E Tx Protection                                        */
/* Preconditions | Caller:Com                                               */
/*               | Timing:Transmission period processing                    */
/* Parameters    | u1TxIdx:Transmission Message Index                       */
/*               | DataPtr:Transmission Data                                */
/* Return Value  | NONE                                                     */
/* Notes         | NONE                                                     */
/****************************************************************************/
void
bsw_bswm_vps_ctrl_E2ETxProtect(uint8 u1TxIdx, uint8* DataPtr)
{
    BswU2              u2Length;
    BswU2              u2TmpLength;
    E2E_P05ConfigType  stTxE2EMsgTbl;
    BswConst E2E_P05ConfigType* ptTmpTxE2EMsgTbl;

    ptTmpTxE2EMsgTbl              = &(bsw_bswm_vps_stTxE2EMsgInfoTbl[u1TxIdx]);
    u2TmpLength                   = ptTmpTxE2EMsgTbl->DataLength;
    stTxE2EMsgTbl.Offset          = ptTmpTxE2EMsgTbl->Offset;
    stTxE2EMsgTbl.DataLength      = u2TmpLength;
    stTxE2EMsgTbl.DataID          = ptTmpTxE2EMsgTbl->DataID;
    stTxE2EMsgTbl.MaxDeltaCounter = ptTmpTxE2EMsgTbl->MaxDeltaCounter;
    u2Length                      = (BswU2)( u2TmpLength >> BSW_BSWM_VPS_BITIND_BYTEPOS_SHIFT );
    (void)E2E_P05Protect( &stTxE2EMsgTbl, &bsw_bswm_vps_stTxProtectState[u1TxIdx], DataPtr, u2Length ); /* MISRA DEVIATION: no return check required */

    return;
}

/****************************************************************************/
/* Function Name | bsw_bswm_vps_ctrl_E2ERxCheck                             */
/* Description   | E2E Rx Check                                             */
/* Preconditions | Caller:BswM/VPS                                          */
/*               | Timing:Processing in the period                          */
/* Parameters    | u1RxIdx:Receive Message Index                            */
/*               | DataPtr:Receive Data                                     */
/* Return Value  | TRUE :Receive success                                    */
/*               | FALSE:Receive false                                      */
/* Notes         | None                                                     */
/****************************************************************************/
boolean
bsw_bswm_vps_ctrl_E2ERxCheck( uint8 u1RxIdx, BswConstR uint8* DataPtr )
{
    boolean bE2ERxChkRet;
    BswU1   u1E2ERet;
    BswU1   u1CfgE2ERxCntError;
    BswU1   u1RxStatus;
    
    u1E2ERet = bsw_bswm_vps_ctrl_E2ECheck( u1RxIdx, DataPtr );
    if( u1E2ERet == BSW_BSWM_VPS_u1_E2E_CHK_OK )
    {
        bE2ERxChkRet = (boolean)TRUE;
        bsw_bswm_vps_u1RxStatus[u1RxIdx] = BSW_BSWM_VPS_u1RXSTATUS_EXIST;
    }
    else if( u1E2ERet == BSW_BSWM_VPS_u1_E2E_CHK_CNTERR )
    {
        u1RxStatus         = bsw_bswm_vps_u1RxStatus[u1RxIdx];
        u1CfgE2ERxCntError = bsw_bswm_vps_u1E2ERxCntError;
        if( (u1RxStatus == BSW_BSWM_VPS_u1RXSTATUS_NONE) && (u1CfgE2ERxCntError == (BswU1)BSW_USE) )
        {
            bE2ERxChkRet = (boolean)TRUE;
        }
        else
        {
            bE2ERxChkRet = (boolean)FALSE;
        }
        bsw_bswm_vps_u1RxStatus[u1RxIdx] = BSW_BSWM_VPS_u1RXSTATUS_EXIST;
    }
    else /* u1E2ERet == BSW_BSWM_VPS_u1_E2E_CHK_FAIL */
    {
        bE2ERxChkRet = (boolean)FALSE;
    }

    return bE2ERxChkRet;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | bsw_bswm_vps_E2ERxCheck                                  */
/* Description   | E2E Rx Check                                             */
/* Preconditions | Caller:BswM/VPS                                          */
/*               | Timing:Processing in the period                          */
/* Parameters    | u1RxEvntIdx:Receive Message Index                        */
/*               | SduDataPtr:Receive Data                                  */
/* Return Value  | BSW_BSWM_VPS_u1_E2E_CHK_OK                               */
/*               | BSW_BSWM_VPS_u1_E2E_CHK_CNTERR                           */
/*               | BSW_BSWM_VPS_u1_E2E_CHK_FAIL                             */
/* Notes         | NONE                                                     */
/****************************************************************************/
static uint8
bsw_bswm_vps_ctrl_E2ECheck(uint8 u1RxIdx, BswConstR uint8* DataPtr)
{
    Std_ReturnType       u1RetCheck;
    E2E_PCheckStatusType u1Checkstate;
    E2E_P05CheckStateType* ptRxChkStat;
    E2E_P05ConfigType  stRxE2EMsgTbl;
    BswConst E2E_P05ConfigType* ptTmpRxE2EMsgTbl;
    BswU2 u2Length;
    BswU2 u2TmpLength;
    BswU1 u1Ret;

    ptTmpRxE2EMsgTbl = &(bsw_bswm_vps_stRxE2EMsgInfoTbl[u1RxIdx]);
    u2TmpLength                   = ptTmpRxE2EMsgTbl->DataLength;
    stRxE2EMsgTbl.Offset          = ptTmpRxE2EMsgTbl->Offset;
    stRxE2EMsgTbl.DataLength      = ptTmpRxE2EMsgTbl->DataLength;
    stRxE2EMsgTbl.DataID          = ptTmpRxE2EMsgTbl->DataID;
    stRxE2EMsgTbl.MaxDeltaCounter = ptTmpRxE2EMsgTbl->MaxDeltaCounter;
    u2Length      = (BswU2)( u2TmpLength >> BSW_BSWM_VPS_BITIND_BYTEPOS_SHIFT );
    ptRxChkStat   = &(bsw_bswm_vps_stRxCheckState[u1RxIdx]);
    u1RetCheck    = E2E_P05Check( &stRxE2EMsgTbl, ptRxChkStat, DataPtr, u2Length );
    u1Checkstate  = E2E_P05MapStatusToSM(u1RetCheck, ptRxChkStat->Status);
    if( u1Checkstate == (BswU1)E2E_P_OK )
    {
        u1Ret = BSW_BSWM_VPS_u1_E2E_CHK_OK;
    }
    else if( (u1Checkstate == (BswU1)E2E_P_WRONGSEQUENCE) || (u1Checkstate == (BswU1)E2E_P_REPEATED) )
    {
        u1Ret = BSW_BSWM_VPS_u1_E2E_CHK_CNTERR;
    }
    else
    {
        u1Ret = BSW_BSWM_VPS_u1_E2E_CHK_FAIL;
    }

    return  u1Ret;
}

#include <cs/bsw_cs_system_memmap_post.h>

#endif /* BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE */
#endif /* BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v3-0-0          :2025/02/24                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
