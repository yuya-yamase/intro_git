/* bsw_bswm_can_connector_c_v2-0-0                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CAN/CONNECTOR/CODE                               */
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

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#include <cansm/bsw_cansm.h>
#include <cs/bsw_cs_system_memmap_post.h>

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
#include "../cfg/BswM_Can_Connector_Cfg.h"
#endif /* ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE ) */

#include <cs/bsw_cs_system_memmap_pre.h>
#include <cantp/bsw_cantp.h>
#include <cantp/bsw_cantp_cbk.h>
#include "../inc/bsw_bswm_can_connector.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* User defined function */
#define bsw_bswm_can_UCanSMCrntState          (BSW_BSWM_CAN_CFG_FN_BSWM_CANSM)

#define bsw_bswm_can_UCdd1TxConfirm           (BSW_BSWM_CAN_CFG_FN_CDD1_TC)
#define bsw_bswm_can_UCdd1RxIndication        (BSW_BSWM_CAN_CFG_FN_CDD1_RI)
#define bsw_bswm_can_UCdd2TxConfirm           (BSW_BSWM_CAN_CFG_FN_CDD2_TC)
#define bsw_bswm_can_UCdd2RxIndication        (BSW_BSWM_CAN_CFG_FN_CDD2_RI)

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
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )

BswConst Bsw_BswmCan_BswMFuncTblType  bsw_bswm_can_cnct_BswM_Func = {
   &bsw_bswm_can_UCanSMCrntState
};
#endif /* ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE ) */

#if(BSW_BSWM_CS_FUNC_CANCDD1 == BSW_USE)
BswConst Bsw_BswmCan_CddFuncTblType bsw_bswm_can_cnct_Cdd1_Func =
{
     &bsw_bswm_can_UCdd1TxConfirm
    ,&bsw_bswm_can_UCdd1RxIndication
};
#endif /* (BSW_BSWM_CS_FUNC_CANCDD1 == BSW_USE) */

#if(BSW_BSWM_CS_FUNC_CANCDD2 == BSW_USE)
BswConst Bsw_BswmCan_CddFuncTblType bsw_bswm_can_cnct_Cdd2_Func =
{
     &bsw_bswm_can_UCdd2TxConfirm
    ,&bsw_bswm_can_UCdd2RxIndication
};
#endif /* (BSW_BSWM_CS_FUNC_CANCDD2 == BSW_USE) */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#if ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE )
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpInit                                   */
/* Description   | CanTp Initialize                                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_can_CanTpInit(void)
{
    CanTp_Init(NULL_PTR);
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpShutdown                               */
/* Description   | CanTp Shutdown                                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_can_CanTpShutdown(void)
{
     CanTp_Shutdown();
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpMainFunction                           */
/* Description   | CanTp Periodic Processing                                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_can_CanTpMainFunction(void)
{
    CanTp_MainFunction();
}

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpCheckRam                               */
/* Description   | Check for CanTpRAM corruption                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_can_CanTpCheckRam( void )
{
    CanTp_CheckRam();
}
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */

/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpEnableTx                               */
/* Description   | Set the diagnostic transmission frame transmission enable                             */
/* Preconditions | When processing medium-priority periodic process                                           */
/* Parameters    | NetworkHandleType Network: Channel                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_can_CanTpEnableTx( NetworkHandleType Network )
{
    CanTp_EnableTx( Network );
}
    
/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpDisableTx                              */
/* Description   | Set the diagnostic transmission frame transmission disable                             */
/* Preconditions | When processing medium-priority periodic process                                           */
/* Parameters    | NetworkHandleType Network: Channel                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_can_CanTpDisableTx( NetworkHandleType Network )
{
    CanTp_DisableTx( Network );
}
#endif /* ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE ) */

#if ( BSW_BSWM_CS_FUNC_CANIF == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpTxConfirmation                         */
/* Description   | Complete Tp transmission                                               */
/* Preconditions | None                                                     */
/* Parameters    | PduIdType TxPduId                                        */
/*               | Std_ReturnType result                                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_can_CanTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    CanTp_TxConfirmation( TxPduId, result );
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpRxIndication                           */
/* Description   | Notify Tp reception                                               */
/* Preconditions | None                                                     */
/* Parameters    | PduIdType RxPduId                                        */
/*               | BswConstR PduInfoType* PduInfoPtr                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_can_CanTpRxIndication(PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr)
{
    CanTp_RxIndication( RxPduId, PduInfoPtr );
}
#endif /* ( BSW_BSWM_CS_FUNC_CANIF == BSW_USE ) */

#if ( BSW_BSWM_CS_FUNC_PDUR == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpTransmit                               */
/* Description   | Request to send Tp                                               */
/* Preconditions | None                                                     */
/* Parameters    | PduIdType TxPduId                                        */
/*               | BswConstR PduInfoType* PduInfoPtr                        */
/* Return Value  | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/* Notes         | None                                                     */
/****************************************************************************/
Std_ReturnType
bsw_bswm_can_CanTpTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr )
{
    Std_ReturnType u1Ret;
    
    u1Ret = CanTp_Transmit( TxPduId, PduInfoPtr );
     
    return u1Ret;
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpCancelTransmit                         */
/* Description   | CanTp Interrupt transmission                                            */
/* Preconditions | None                                                     */
/* Parameters    | PduIdType TxPduId                                        */
/* Return Value  | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/* Notes         | None                                                     */
/****************************************************************************/
Std_ReturnType
bsw_bswm_can_CanTpCancelTransmit( PduIdType TxPduId )
{
    Std_ReturnType u1Ret;
    
    u1Ret = CanTp_CancelTransmit( TxPduId );

    return u1Ret;
}

/****************************************************************************/
/* Function Name | bsw_bswm_can_CanTpCancelReceive                          */
/* Description   | CanTp Interrupt reception                                            */
/* Preconditions | None                                                     */
/* Parameters    | PduIdType RxPduId                                        */
/* Return Value  | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/* Notes         | None                                                     */
/****************************************************************************/
Std_ReturnType
bsw_bswm_can_CanTpCancelReceive( PduIdType RxPduId )
{
    Std_ReturnType u1Ret;
    
    u1Ret = CanTp_CancelReceive( RxPduId );

    return u1Ret;
}

#endif /* ( BSW_BSWM_CS_FUNC_PDUR == BSW_USE ) */
#endif /* ( BSW_BSWM_CS_FUNC_CANTP == BSW_USE ) */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#include <cs/bsw_cs_system_memmap_post.h>

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-0-1          :2018/01/30                                             */
/*  v1-1-0          :2018/12/17                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
