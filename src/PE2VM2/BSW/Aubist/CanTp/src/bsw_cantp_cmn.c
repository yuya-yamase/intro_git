/* bsw_cantp_cmn_c_v3-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/CMN/CODE                                        */
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

#if( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
#include <bswm_can/bsw_bswm_can.h>
#endif /* BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE */

#include <cantp/bsw_cantp.h>
#include <cantp/bsw_cantp_cbk.h>
#include <pdur/bsw_pdur.h>

#include "../cfg/CanTp_Cfg.h"
#include "../inc/bsw_cantp_cmn.h"

#include "../inc/bsw_cantp_config.h"

#include "../inc/bsw_cantp_st.h"
#include "../inc/bsw_cantp_rx.h"
#include "../inc/bsw_cantp_tx.h"
#include "../inc/bsw_cantp_snd.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANTP_u2CHGPARAM_VAL_MAX        ((uint16)256U)  /* ChangeParameter value max */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static BswConst Bsw_CanTp_RxNSduCfgType *   bsw_cantp_GetRxNSduCfgByRxPdu( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2RxNPduId, BswConstR uint8 * ptSduData );
static BswConst Bsw_CanTp_TxNSduCfgType *   bsw_cantp_GetTxNSduCfgByRxPdu( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2RxNPduId, BswConstR uint8 * ptSduData );
static BswConst Bsw_CanTp_RxNSduCfgType *   bsw_cantp_GetRxNSduCfgByTxPdu( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2TxNPduId );
static BswConst Bsw_CanTp_TxNSduCfgType *   bsw_cantp_GetTxNSduCfgByTxPdu( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2TxNPduId );
static void                                 bsw_cantp_RxIndForwardByNPCI( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo, uint16 u2RxNPduId );
#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
static Std_ReturnType                       bsw_cantp_ChangeParamCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2NSduId, uint8 u1Parameter, uint16 u2Value );
#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */
#if( BSW_CANTP_CFG_READ_RXPARAM == BSW_USE )
static uint16                               bsw_cantp_ReadParamCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2NSduId, uint8 u1Parameter );
#endif /* BSW_CANTP_CFG_READ_RXPARAM == BSW_USE */
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
uint8   bsw_cantp_cmn_u1TxBuffer[BSW_CANTP_u1CAN_DL_64];   /* Buffer for frame transmission */
uint8   bsw_cantp_cmn_u1ErrState;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
uint16  bsw_cantp_cmn_u2LatestRxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
BswConst uint8 bsw_cantp_cmn_u1PciOffSetTbl[BSW_CANTP_ADDRESSING_NUM] =
{
    (uint8)BSW_CANTP_OFFSET0,           /* 0:BSW_CANTP_STANDARD    */
    (uint8)BSW_CANTP_OFFSET0,           /* 1:BSW_CANTP_NORMALFIXED */
    (uint8)BSW_CANTP_OFFSET1,           /* 2:BSW_CANTP_MIXED       */
    (uint8)BSW_CANTP_OFFSET1,           /* 3:BSW_CANTP_MIXED29BIT  */
    (uint8)BSW_CANTP_OFFSET1            /* 4:BSW_CANTP_EXTENDED    */
};

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | bsw_cantp_cmn_Init                                       */
/* Description   | Initialize/Re-Initialize CANTP component                 */
/* Preconditions | None                                                     */
/* Parameters    | Bsw_CanTp_ConfigType : Pointer to configuration data     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : CanTp_Init                               */
/****************************************************************************/
void
bsw_cantp_cmn_Init( BswConst Bsw_CanTp_ConfigType * CfgPtr )
{
    /* Temporarily changes status to BSW_CANTP_OFF */
    bsw_cantp_st_ShutdownCore();

    bsw_cantp_st_InitCore( &bsw_cantp_stCfgTbl );

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_cmn_Shutdown                                   */
/* Description   | Shutdown CANTP component                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : CanTp_Shutdown                           */
/****************************************************************************/
void
bsw_cantp_cmn_Shutdown( void )
{

    bsw_cantp_st_ShutdownCore();

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_cmn_Transmit                                   */
/* Description   | Transmit Request                                         */
/* Preconditions | None                                                     */
/* Parameters    | CanTpTxSduId   : Transmission NSduId                     */
/*               | CanTpTxInfoPtr : Pointer to transmission information     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK          : Transmission request success            */
/*               |  E_NOT_OK      : Transmission request failure            */
/* Notes         | Supported API  : CanTp_Transmit                          */
/****************************************************************************/
Std_ReturnType
bsw_cantp_cmn_Transmit( PduIdType CanTpTxSduId, BswConstR PduInfoType * CanTpTxInfoPtr )
{
    BswConst Bsw_CanTp_CfgType *    pt_CfgTbl;          /* Pointer to CanTp configuration */
    uint16                          u2_MinTxNSduId;     /* Minimum TxNSduId               */
    Std_ReturnType                  u1_Ret;             /* Return value                   */

    u1_Ret = (Std_ReturnType)E_NOT_OK;

    /* Acquisition of pointer to configuration data structure */
    pt_CfgTbl = bsw_cantp_cmn_GetConfigTbl();
    if( pt_CfgTbl != NULL_PTR )
    {
        /* parameter check */
        u2_MinTxNSduId = pt_CfgTbl->u2MinTxNSduId;
        if( ( (uint16)CanTpTxSduId >= u2_MinTxNSduId )
        &&  ( (uint16)CanTpTxSduId <  (u2_MinTxNSduId + pt_CfgTbl->u2TotalTxNSduNum ) ) )
        {
            u1_Ret = bsw_cantp_tx_TransmitCore( pt_CfgTbl, (uint16)CanTpTxSduId, (uint32)CanTpTxInfoPtr->SduLength );
        }
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_cmn_CancelTransmit                             */
/* Description   | Transmit Cancel Request                                  */
/* Preconditions | None                                                     */
/* Parameters    | CanTpTxSduId   : Transmission cancellation NSduId        */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK          : Transmission cancellation success       */
/*               |  E_NOT_OK      : Transmission cancellation failure       */
/* Notes         | Supported API  : CanTp_CancelTransmit                    */
/****************************************************************************/
Std_ReturnType
bsw_cantp_cmn_CancelTransmit( PduIdType CanTpTxSduId )
{
    BswConst Bsw_CanTp_CfgType *    pt_CfgTbl;          /* Pointer to CanTp configuration */
    uint16                          u2_MinTxNSduId;     /* Minimum TxNSduId               */
    Std_ReturnType                  u1_Ret;             /* Return value                   */

    u1_Ret = (Std_ReturnType)E_NOT_OK;

    /* Acquisition of pointer to configuration data structure */
    pt_CfgTbl = bsw_cantp_cmn_GetConfigTbl();
    if( pt_CfgTbl != NULL_PTR )
    {
        /* parameter check */
        u2_MinTxNSduId = pt_CfgTbl->u2MinTxNSduId;
        if( ( (uint16)CanTpTxSduId >= u2_MinTxNSduId )
        &&  ( (uint16)CanTpTxSduId <  (u2_MinTxNSduId + pt_CfgTbl->u2TotalTxNSduNum ) ) )
        {
            u1_Ret = bsw_cantp_tx_CancelTransmitCore( pt_CfgTbl, (uint16)CanTpTxSduId );
        }
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_cmn_CancelReceive                              */
/* Description   | Receive Cancel Request                                   */
/* Preconditions | None                                                     */
/* Parameters    | CanTpRxSduId   : Cancel target RxNSdu-Id                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK          : Accept cancel request                   */
/*               |  E_NOT_OK      : Reject cancel request                   */
/* Notes         | Supported API  : CanTp_CancelReceiv                      */
/****************************************************************************/
Std_ReturnType
bsw_cantp_cmn_CancelReceive( PduIdType CanTpRxSduId )
{
    BswConst Bsw_CanTp_CfgType *    pt_CfgTbl;          /* Pointer to CanTp configuration */
    uint16                          u2_MinRxNSduId;     /* Minimum RxNSduId               */
    Std_ReturnType                  u1_Ret;             /* Return value                   */

    u1_Ret = (Std_ReturnType)E_NOT_OK;

    /* Acquisition of pointer to configuration data structure */
    pt_CfgTbl = bsw_cantp_cmn_GetConfigTbl();
    if( pt_CfgTbl != NULL_PTR )
    {
        /* parameter check */
        u2_MinRxNSduId = pt_CfgTbl->u2MinRxNSduId;
        if( ( (uint16)CanTpRxSduId >= u2_MinRxNSduId )
        &&  ( (uint16)CanTpRxSduId <  ( u2_MinRxNSduId + pt_CfgTbl->u2TotalRxNSduNum ) ) )
        {
            u1_Ret = bsw_cantp_rx_CancelReceiveCore( pt_CfgTbl, (uint16)CanTpRxSduId );
        }
    }

    return u1_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_cmn_MainFunction                               */
/* Description   | Periodical handling of CANTP                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : CanTp_MainFunction                       */
/****************************************************************************/
void
bsw_cantp_cmn_MainFunction( void )
{
    bsw_cantp_st_MainFunction_Mode();
    bsw_cantp_rx_MainFunction_Rx();
    bsw_cantp_tx_MainFunction_Tx();

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_cmn_RxIndication                               */
/* Description   | Receive indication from CANIF                            */
/* Preconditions | None                                                     */
/* Parameters    | RxPduId       : RxPduID                                  */
/*               | PduInfoPtr    : Pointer to PDU Information               */
/* Return Value  | None                                                     */
/* Notes         | Supported API : CanTp_RxIndication                       */
/****************************************************************************/
void
bsw_cantp_cmn_RxIndication( PduIdType RxPduId, BswConstR PduInfoType * PduInfoPtr )
{
    BswConst Bsw_CanTp_CfgType *    pt_CfgTbl;      /* Pointer to CanTp configuration */
    Bsw_CanTp_PduInfoType           st_TpPduInfo;   /* CanTp PDU data structure       */
    uint16                          u2_MinRxNPduId; /* Minimum RxNPduId               */

    /* CallBack Diag Message */
    bsw_cantp_rx_CbkRxIndication( RxPduId, PduInfoPtr );

    /* Acquisition of pointer to configuration data structure */
    pt_CfgTbl = bsw_cantp_cmn_GetConfigTbl();
    if( pt_CfgTbl != NULL_PTR )
    {
        /* parameter check */
        /* Note: The valid length of the PduInfoPtr->SduLength depends on the configuration. */
        /*       Therefore, this function does not check PduInfoPtr->SduLength.              */
        /*       PduInfoPtr->SduLength is checked in subsequent processing.                  */
        u2_MinRxNPduId = pt_CfgTbl->u2MinRxNPduId;
        if( ( (uint16)RxPduId >= u2_MinRxNPduId )
        &&  ( (uint16)RxPduId <  ( u2_MinRxNPduId + pt_CfgTbl->u2TotalRxNPduNum ) ) )
        {
            st_TpPduInfo.ptSduData   = PduInfoPtr->SduDataPtr;
            st_TpPduInfo.u4SduLength = (uint32)PduInfoPtr->SduLength;
            /* RxIndication forwarding by N_PCI type */
            bsw_cantp_RxIndForwardByNPCI( pt_CfgTbl, &st_TpPduInfo, (uint16)RxPduId );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_cmn_TxConfirmation                             */
/* Description   | Notice of transmission completion                        */
/* Preconditions | None                                                     */
/* Parameters    | TxPduId       : Transmission completion PduId            */
/*               | result        : Result of the transmission               */
/* Return Value  | None                                                     */
/* Notes         | Supported API : CanTp_TxConfirmation                     */
/****************************************************************************/
void
bsw_cantp_cmn_TxConfirmation( PduIdType TxPduId, Std_ReturnType result )
{
    BswConst Bsw_CanTp_CfgType *        pt_CfgTbl;          /* Pointer to CanTp configuration  */
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTbl;    /* Pointer to RxNSdu configuration */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTbl;    /* Pointer to TxNSdu configuration */
    uint16                              u2_MinTxNPduId;     /* Minimum TxNPduId                */

    /* Acquisition of pointer to configuration data structure */
    pt_CfgTbl = bsw_cantp_cmn_GetConfigTbl();
    if( pt_CfgTbl != NULL_PTR )
    {
        /* parameter check */
        u2_MinTxNPduId = pt_CfgTbl->u2MinTxNPduId;
        if( ( (uint16)TxPduId >= u2_MinTxNPduId )
        &&  ( (uint16)TxPduId <  ( u2_MinTxNPduId + pt_CfgTbl->u2TotalTxNPduNum ) ) )
        {
            /* Identification of SF/FF/CF confirmation or FC confirmation */

            pt_TxNSduCfgTbl = bsw_cantp_GetTxNSduCfgByTxPdu( pt_CfgTbl, (uint16)TxPduId );
            if( pt_TxNSduCfgTbl != NULL_PTR )
            {   /* SF/FF/CF confirmation */
                bsw_cantp_tx_TxConfTX( pt_TxNSduCfgTbl, result );
            }
            else
            {
                pt_RxNSduCfgTbl = bsw_cantp_GetRxNSduCfgByTxPdu( pt_CfgTbl, (uint16)TxPduId );
                if( pt_RxNSduCfgTbl != NULL_PTR )
                {   /* FC confirmation */
                    bsw_cantp_rx_TxConfRX( pt_RxNSduCfgTbl, result );
                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | bsw_cantp_cmn_GetConfigTbl                               */
/* Description   | Get pointer to ConfigTbl                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Bsw_CanTp_CfgType : Pointer to ConfigTbl                 */
/* Notes         | None                                                     */
/****************************************************************************/
BswConst
Bsw_CanTp_CfgType * bsw_cantp_cmn_GetConfigTbl( void )
{
    return &bsw_cantp_stCfgTbl;
}


/****************************************************************************/
/* Function Name | bsw_cantp_cmn_GetRxNSduCfgTbl                            */
/* Description   | Get pointer to RxNSduTbl                                 */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl            : Pointer to CanTp configration      */
/*               | u2RxNSduId          : RxNSduId                           */
/* Return Value  | Bsw_CanTp_RxNSduCfgType : Pointer to RxNSduCfgTbl        */
/* Notes         | None                                                     */
/****************************************************************************/
BswConst Bsw_CanTp_RxNSduCfgType *
bsw_cantp_cmn_GetRxNSduCfgTbl( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2RxNSduId )
{
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_Ret;             /* Return value                     */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTblTop;     /* Pointer to ChCfgTbl              */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTbl;        /* Pointer to channel configuration */
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTblTop; /* Pointer to RxNSdu configuration  */
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTbl;    /* Pointer to RxNSdu configuration  */
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_FirstRxNSduCfg;  /* Pointer to First RxNSdu Cfg      */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    uint16                              u2_MinRxNSduId;     /* Minimum RxNSduId                 */
    uint16                              u2_RxNSduIdx;       /* Index of RxNSdus                 */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    uint16                              u2_RxNSduNum;       /* Number of RxNSdus                */
    uint8                               u1_ChId;            /* Channel ID                       */
    uint8                               u1_ChNum;           /* Number of channels               */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */

    pt_Ret = NULL_PTR;

    u2_MinRxNSduId = ptCfgTbl->u2MinRxNSduId;
    if( ( u2RxNSduId >= u2_MinRxNSduId )
    &&  ( u2RxNSduId <  ( u2_MinRxNSduId + ptCfgTbl->u2TotalRxNSduNum ) ) )
    {
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        /* Loop for number of connection channels */
        u1_ChNum = ptCfgTbl->u1ChNum;
        for( u1_ChId = (uint8)0U; ( u1_ChId < u1_ChNum ) && ( pt_Ret == NULL_PTR ); u1_ChId++ )
        {
            pt_ChCfgTblTop  = ptCfgTbl->ptChCfgTbl;
            pt_ChCfgTbl     = &pt_ChCfgTblTop[u1_ChId];
            u2_RxNSduNum    = pt_ChCfgTbl->u2RxNSduNum;
            pt_RxNSduCfgTblTop = pt_ChCfgTbl->ptRxNSduCfgTbl;
            pt_RxNSduCfgTbl = &pt_RxNSduCfgTblTop[0U];
            for( u2_RxNSduIdx = (uint16)0U; u2_RxNSduIdx < u2_RxNSduNum; u2_RxNSduIdx++ )
            {
                if( u2RxNSduId == pt_RxNSduCfgTbl[u2_RxNSduIdx].u2NSduId )
                {
                    pt_Ret = &(pt_RxNSduCfgTbl[u2_RxNSduIdx]);
                    break;
                }
            }
        }
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u2_RxNSduIdx = u2RxNSduId - u2_MinRxNSduId;
        
        /* Note: In order to get the start address of the NSdu configuration table, refer to 0CH and the 0th NSdu.                          */
        /*       To access NSdu configuration table using NSduId as a key, the start address of the NSdu configuration table is required.   */
        pt_FirstRxNSduCfg = &(ptCfgTbl->ptChCfgTbl[0U].ptRxNSduCfgTbl[0U]);
        pt_Ret = &(pt_FirstRxNSduCfg[u2_RxNSduIdx]);
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    }

    return pt_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_cmn_GetTxNSduCfgTbl                            */
/* Description   | Get pointer to TxNSduTbl                                 */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl            : Pointer to CanTp configration      */
/*               | u2TxNSduId          : TxNSduId                           */
/* Return Value  | Bsw_CanTp_TxNSduCfgType : Pointer to TxNSduTbl           */
/* Notes         | None                                                     */
/****************************************************************************/
BswConst Bsw_CanTp_TxNSduCfgType *
bsw_cantp_cmn_GetTxNSduCfgTbl( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2TxNSduId )
{
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_Ret;             /* Return value                     */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTblTop;     /* Pointer to ChCfgTbl              */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTbl;        /* Pointer to channel configuration */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTblTop; /* Pointer to TxNSdu configuration  */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTbl;    /* Pointer to TxNSdu configuration  */
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_FirstTxNSduCfg;  /* Pointer to First TxNSdu Cfg      */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    uint16                              u2_MinTxNSduId;     /* Minimum TxNSduId                 */
    uint16                              u2_TxNSduIdx;       /* Index of TxNSdus                 */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    uint16                              u2_TxNSduNum;       /* Number of TxNSdus                */
    uint8                               u1_ChId;            /* Channel ID                       */
    uint8                               u1_ChNum;           /* Number of channels               */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */

    pt_Ret = NULL_PTR;

    u2_MinTxNSduId = ptCfgTbl->u2MinTxNSduId;
    if( ( u2TxNSduId >= u2_MinTxNSduId )
    &&  ( u2TxNSduId <  (u2_MinTxNSduId + ptCfgTbl->u2TotalTxNSduNum ) ) )
    {
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        /* Loop for number of connection channels */
        u1_ChNum = ptCfgTbl->u1ChNum;
        for( u1_ChId = (uint8)0U; ( u1_ChId < u1_ChNum ) && ( pt_Ret == NULL_PTR ); u1_ChId++ )
        {
            pt_ChCfgTblTop  = ptCfgTbl->ptChCfgTbl;
            pt_ChCfgTbl     = &pt_ChCfgTblTop[u1_ChId];
            u2_TxNSduNum    = pt_ChCfgTbl->u2TxNSduNum;
            pt_TxNSduCfgTblTop = pt_ChCfgTbl->ptTxNSduCfgTbl;
            pt_TxNSduCfgTbl = &pt_TxNSduCfgTblTop[0U];
            for( u2_TxNSduIdx = (uint16)0U; u2_TxNSduIdx < u2_TxNSduNum; u2_TxNSduIdx++ )
            {
                if( u2TxNSduId == pt_TxNSduCfgTbl[u2_TxNSduIdx].u2NSduId )
                {
                    pt_Ret = &(pt_TxNSduCfgTbl[u2_TxNSduIdx]);
                    break;
                }
            }
        }
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u2_TxNSduIdx = u2TxNSduId - u2_MinTxNSduId;
        
        /* Note: In order to get the start address of the NSdu configuration table, refer to 0CH and the 0th NSdu.                          */
        /*       To access NSdu configuration table using NSduId as a key, the start address of the NSdu configuration table is required.   */
        pt_FirstTxNSduCfg = &(ptCfgTbl->ptChCfgTbl[0U].ptTxNSduCfgTbl[0U]);
        pt_Ret = &(pt_FirstTxNSduCfg[u2_TxNSduIdx]);
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    }

    return pt_Ret;
}


#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_cantp_cmn_GetOptimizedCanDl                          */
/* Description   | Get optimized CAN_DL                                     */
/* Preconditions | None                                                     */
/* Parameters    | u1SduLen               : Requirement size                */
/* Return Value  | uint8                                                    */
/*               |  BSW_CANTP_u1CAN_DL_INVAL  : Incorrect u1SduLen          */
/*               |  !BSW_CANTP_u1CAN_DL_INVAL : Optimized FD CAN_DL         */
/* Notes         | none                                                     */
/****************************************************************************/
uint8
bsw_cantp_cmn_GetOptimizedCanDl( uint8 u1SduLen )
{
    uint8   u1_Ret;     /* Return value */

    u1_Ret = BSW_CANTP_u1CAN_DL_INVAL;
    if( u1SduLen < BSW_CANTP_u1CAN_DL_65 )
    {
        u1_Ret = bsw_cantp_u1OptimizedCanDlTbl[u1SduLen];
    }

    return u1_Ret;
}
#endif /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */


#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_cantp_cmn_ChangeParameter                            */
/* Description   | Set parameter BS/STmin to target RxNSduId                */
/* Preconditions | None                                                     */
/* Parameters    | id            : Target Rx NSdu-Id                        */
/*               | parameter     : Type of change parameter                 */
/*               | value         : Value of parameter                       */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Accept change request                    */
/*               |  E_NOT_OK     : Reject change request                    */
/* Notes         | Supported API : CanTp_ChangeParameter                    */
/****************************************************************************/
Std_ReturnType
bsw_cantp_cmn_ChangeParameter( PduIdType id, TPParameterType parameter, uint16 value )
{
    BswConst Bsw_CanTp_CfgType *    pt_CfgTbl;          /* Pointer to CanTp configuration */
    uint16                          u2_MinRxNSduId;     /* Minimum RxNSduId               */
    Std_ReturnType                  u1_Ret;             /* Return value                   */

    u1_Ret = (Std_ReturnType)E_NOT_OK;

    /* Acquisition of pointer to configuration data structure */
    pt_CfgTbl = bsw_cantp_cmn_GetConfigTbl();
    if( pt_CfgTbl != NULL_PTR )
    {
        /* parameter check */
        u2_MinRxNSduId = pt_CfgTbl->u2MinRxNSduId;
        if( ( (uint16)id >= u2_MinRxNSduId )
        &&  ( (uint16)id <  ( u2_MinRxNSduId + pt_CfgTbl->u2TotalRxNSduNum ) ) )
        {
            if( ( parameter == (TPParameterType)TP_BS )
            ||  ( parameter == (TPParameterType)TP_STMIN ) )
            {
                if( value < BSW_CANTP_u2CHGPARAM_VAL_MAX )
                {
                    u1_Ret = bsw_cantp_ChangeParamCore( pt_CfgTbl, (uint16)id, (uint8)parameter, value );
                }
            }
        }
    }

    return u1_Ret;

}
#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */


#if( BSW_CANTP_CFG_READ_RXPARAM == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_cantp_cmn_ReadParameter                              */
/* Description   | Read selected parameter of RxNSduId                      */
/* Preconditions | None                                                     */
/* Parameters    | id                  : Target RxNSduId                    */
/*               | parameter           : Type of read parameter             */
/*               | value               : Stote pointer to parameter value   */
/* Return Value  | Std_ReturnType                                           */
/*               |  BSW_CANTP_E_OK     : Accept read request                */
/*               |  BSW_CANTP_E_NOT_OK : Reject read request                */
/* Notes         | Supported API       : CanTp_ReadParameter                */
/****************************************************************************/
Std_ReturnType
bsw_cantp_cmn_ReadParameter( PduIdType id, TPParameterType parameter, uint16 * value )
{
    BswConst Bsw_CanTp_CfgType *    pt_CfgTbl;      /* Pointer to CanTp configuration */
    uint16                          u2_MinRxNSduId; /* Minimum RxNSduId               */
    Std_ReturnType                  u1_Ret;         /* Return value                   */

    u1_Ret = (Std_ReturnType)E_NOT_OK;

    /* Acquisition of pointer to configuration data structure */
    pt_CfgTbl = bsw_cantp_cmn_GetConfigTbl();
    if( pt_CfgTbl != NULL_PTR )
    {
        /* parameter check */
        u2_MinRxNSduId = pt_CfgTbl->u2MinRxNSduId;
        if( ( (uint16)id >= u2_MinRxNSduId )
        &&  ( (uint16)id <  ( u2_MinRxNSduId + pt_CfgTbl->u2TotalRxNSduNum ) ) )
        {
            if( ( parameter == (TPParameterType)TP_BS )
            ||  ( parameter == (TPParameterType)TP_STMIN ) )
            {
                *value = bsw_cantp_ReadParamCore( pt_CfgTbl, (uint16)id, (uint8)parameter );
                u1_Ret = (Std_ReturnType)E_OK;
            }
        }
    }

    return u1_Ret;
}
#endif /* BSW_CANTP_CFG_READ_RXPARAM == BSW_USE */


#if( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
/****************************************************************************/
/* Function Name | bsw_cantp_cmn_CheckRam                                   */
/* Description   | Check CanTp in RAM                                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : CanTp_CheckRam                           */
/****************************************************************************/
void
bsw_cantp_cmn_CheckRam( void )
{
    bsw_cantp_snd_CheckRam_Snd();

    if( bsw_cantp_cmn_u1ErrState != BSW_CANTP_u1ERRNONE )
    {   /* RAM broken    */
        /* Unrecoverable */
        bsw_cantp_st_ShutdownCore();
        BswM_Can_DetectFail();
    }

    return;
}
#endif /* BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | bsw_cantp_GetRxNSduCfgByRxPdu                            */
/* Description   | Get RxNSdu configuration pointer to received RxNPdu      */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl    : Pointer to CanTp configration              */
/*               | u2RxNPduId  : Notified Rx NPdu-ID                        */
/*               | ptSduData   : Pointer to received sdu data               */
/* Return Value  | Bsw_CanTp_RxNSduCfgType                                  */
/*               |  !NULL_PTR  : Pointer to RxNSdu                          */
/*               |  NULL_PTR   : RxNSdu does not exist on this config       */
/* Notes         | None                                                     */
/****************************************************************************/
static BswConst Bsw_CanTp_RxNSduCfgType *
bsw_cantp_GetRxNSduCfgByRxPdu( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2RxNPduId, BswConstR uint8 * ptSduData )
{
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTbl;    /* Pointer to RxNSdu configuration  */
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_Ret;             /* Return value                     */
    uint16                              u2_RxNSduIdx;       /* Index of RxNSdus                 */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTblTop; /* Pointer to RxNSdu configuration  */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTblTop;     /* Pointer to ChCfgTbl              */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTbl;        /* Pointer to channel configuration */
    uint16                              u2_RxNSduNum;       /* Number of RxNSdus                */
    uint8                               u1_ChId;            /* Channel ID                       */
    uint8                               u1_ChNum;           /* Number of channels               */
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_FirstRxNSduCfg;  /* Pointer to First RxNSdu Cfg      */
    uint16                              u2_LatestRxNSduId;  /* Latest Rx NSdu-Id                */
    uint16                              u2_MinRxNSduId;     /* Minimum RxNSduId                 */
    uint16                              u2_MaxRxNSduNum;    /* Number of Max RxNSdus            */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    uint8                               u1_AddressFormat;   /* Addressing format                */

    pt_Ret = NULL_PTR;

#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    /* Loop for number of connection channels */
    u1_ChNum = ptCfgTbl->u1ChNum;
    for( u1_ChId = (uint8)0U; ( u1_ChId < u1_ChNum ) && ( pt_Ret == NULL_PTR ); u1_ChId++ )
    {
        pt_ChCfgTblTop = ptCfgTbl->ptChCfgTbl;
        pt_ChCfgTbl = &pt_ChCfgTblTop[u1_ChId];

        /* Loop for number of RxNSdus used in a connection channel */
        u2_RxNSduNum = pt_ChCfgTbl->u2RxNSduNum;
        for( u2_RxNSduIdx = (uint16)0U; ( u2_RxNSduIdx < u2_RxNSduNum ) && ( pt_Ret == NULL_PTR ); u2_RxNSduIdx++ )
        {
            pt_RxNSduCfgTblTop = pt_ChCfgTbl->ptRxNSduCfgTbl;
            pt_RxNSduCfgTbl = &pt_RxNSduCfgTblTop[u2_RxNSduIdx];

            if( u2RxNPduId == pt_RxNSduCfgTbl->u2NPduId )
            {
                u1_AddressFormat = pt_RxNSduCfgTbl->u1AddressFormat;
                if( ( u1_AddressFormat == (uint8)BSW_CANTP_STANDARD )
                ||  ( u1_AddressFormat == (uint8)BSW_CANTP_NORMALFIXED ) )
                {   /* Normal/Normal fixed addressing format */
                    pt_Ret = pt_RxNSduCfgTbl;
                }
                else if( u1_AddressFormat == (uint8)BSW_CANTP_EXTENDED )
                {   /* Extended addressing format */

                    /* in RxNSdu       */
                    /*    N_TA: Server */
                    /*    N_SA: Client */

                    if( ptSduData[0U] == pt_RxNSduCfgTbl->u1NTa )
                    {
                        pt_Ret = pt_RxNSduCfgTbl;
                    }
                }
                else
                {   /* Mixed addressing format */

                    if( ptSduData[0U] == pt_RxNSduCfgTbl->u1NAe )
                    {
                        pt_Ret = pt_RxNSduCfgTbl;
                    }
                }
            }
        }
    }
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    /* Note: In order to get the start address of the NSdu configuration table, refer to 0CH and the 0th NSdu.                          */
    /*       To access NSdu configuration table using NSduId as a key, the start address of the NSdu configuration table is required.   */
    pt_FirstRxNSduCfg = &(ptCfgTbl->ptChCfgTbl[0U].ptRxNSduCfgTbl[0U]);
    u2_LatestRxNSduId = bsw_cantp_cmn_u2LatestRxNSduId;
    u2_MinRxNSduId    = ptCfgTbl->u2MinRxNSduId;
    if( ( u2_LatestRxNSduId >= u2_MinRxNSduId )
    &&  ( u2_LatestRxNSduId <  ( u2_MinRxNSduId + ptCfgTbl->u2TotalRxNSduNum ) ) )
    {
        u2_RxNSduIdx = u2_LatestRxNSduId - u2_MinRxNSduId;
        pt_RxNSduCfgTbl = &(pt_FirstRxNSduCfg[u2_RxNSduIdx]);
        if( u2RxNPduId == pt_RxNSduCfgTbl->u2NPduId )
        {
            u1_AddressFormat = pt_RxNSduCfgTbl->u1AddressFormat;
            if( ( u1_AddressFormat == (uint8)BSW_CANTP_STANDARD )
            ||  ( u1_AddressFormat == (uint8)BSW_CANTP_NORMALFIXED ) )
            {   /* Normal/Normal fixed addressing format */
                pt_Ret = pt_RxNSduCfgTbl;
            }
            else if( u1_AddressFormat == (uint8)BSW_CANTP_EXTENDED )
            {   /* Extended addressing format */

                /* in RxNSdu       */
                /*    N_TA: Server */
                /*    N_SA: Client */

                if( ptSduData[0U] == pt_RxNSduCfgTbl->u1NTa )
                {
                    pt_Ret = pt_RxNSduCfgTbl;
                }
            }
            else
            {   /* Mixed addressing format */

                if( ptSduData[0U] == pt_RxNSduCfgTbl->u1NAe )
                {
                    pt_Ret = pt_RxNSduCfgTbl;
                }
            }
        }
    }
    u2_MaxRxNSduNum = bsw_cantp_u2MaxRxNSduNum;
    for( u2_RxNSduIdx = (uint16)0U; ( u2_RxNSduIdx < u2_MaxRxNSduNum ) && ( pt_Ret == NULL_PTR ); u2_RxNSduIdx++ )
    {
        pt_RxNSduCfgTbl = &(pt_FirstRxNSduCfg[u2_RxNSduIdx]);
        if( u2RxNPduId == pt_RxNSduCfgTbl->u2NPduId )
        {
            u1_AddressFormat = pt_RxNSduCfgTbl->u1AddressFormat;
            if( ( u1_AddressFormat == (uint8)BSW_CANTP_STANDARD )
            ||  ( u1_AddressFormat == (uint8)BSW_CANTP_NORMALFIXED ) )
            {   /* Normal/Normal fixed addressing format */
                pt_Ret = pt_RxNSduCfgTbl;
            }
            else if( u1_AddressFormat == (uint8)BSW_CANTP_EXTENDED )
            {   /* Extended addressing format */

                /* in RxNSdu       */
                /*    N_TA: Server */
                /*    N_SA: Client */

                if( ptSduData[0U] == pt_RxNSduCfgTbl->u1NTa )
                {
                    pt_Ret = pt_RxNSduCfgTbl;
                }
            }
            else
            {   /* Mixed addressing format */

                if( ptSduData[0U] == pt_RxNSduCfgTbl->u1NAe )
                {
                    pt_Ret = pt_RxNSduCfgTbl;
                }
            }
            if( pt_Ret != NULL_PTR )
            {
                bsw_cantp_cmn_u2LatestRxNSduId = u2_RxNSduIdx + u2_MinRxNSduId;
            }
        }
    }
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    return pt_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_GetTxNSduCfgByRxPdu                            */
/* Description   | Get TxNSdu configuration pointer to received RxNPdu      */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl    : Pointer to CanTp configration              */
/*               | u2RxNPduId  : Notified Rx NPdu-ID                        */
/*               | ptSduData   : Pointer to received sdu data               */
/* Return Value  | Bsw_CanTp_TxNSduCfgType                                  */
/*               |  !NULL_PTR  : Pointer to TxNSdu                          */
/*               |  NULL_PTR   : TxNSdu does not exist on this config       */
/* Notes         | None                                                     */
/****************************************************************************/
static BswConst Bsw_CanTp_TxNSduCfgType *
bsw_cantp_GetTxNSduCfgByRxPdu( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2RxNPduId, BswConstR uint8 * ptSduData )
{
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTbl;    /* Pointer to TxNSdu configuration  */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_Ret;             /* Return value                     */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTblTop; /* Pointer to TxNSdu configuration  */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTblTop;     /* Pointer to ChCfgTbl              */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTbl;        /* Pointer to channel configuration */
    uint16                              u2_TxNSduNum;       /* Number of TxNSdus                */
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_FirstTxNSduCfg;  /* Pointer to First TxNSdu Cfg      */
    uint16                              u2_SenderNSduId;    /* Sender Processing NSdu-Id        */
    uint16                              u2_MinTxNSduId;     /* Minimum TxNSduId                 */
    uint16                              u2_TotalTxNSduNum;  /* Total TxNSdu Num                 */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    uint16                              u2_TxNSduIdx;       /* Index of TxNSdus                 */
    uint8                               u1_ChId;            /* Channel ID                       */
    uint8                               u1_ChNum;           /* Number of channels               */
    uint8                               u1_AddressFormat;   /* Addressing format                */

    pt_Ret = NULL_PTR;

    /* Loop for number of connection channels */
    u1_ChNum = ptCfgTbl->u1ChNum;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    u2_MinTxNSduId    = ptCfgTbl->u2MinTxNSduId;
    u2_TotalTxNSduNum = ptCfgTbl->u2TotalTxNSduNum;
    /* Note: In order to get the start address of the NSdu configuration table, refer to 0CH and the 0th NSdu.                          */
    /*       To access NSdu configuration table using NSduId as a key, the start address of the NSdu configuration table is required.   */
    pt_FirstTxNSduCfg = &(ptCfgTbl->ptChCfgTbl[0U].ptTxNSduCfgTbl[0U]);
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    for( u1_ChId = (uint8)0U; ( u1_ChId < u1_ChNum ) && ( pt_Ret == NULL_PTR ); u1_ChId++ )
    {
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        pt_ChCfgTblTop = ptCfgTbl->ptChCfgTbl;
        pt_ChCfgTbl = &pt_ChCfgTblTop[u1_ChId];
        /* Loop for number of TxNSdus used in a connection channel */
        u2_TxNSduNum = pt_ChCfgTbl->u2TxNSduNum;
        for( u2_TxNSduIdx = (uint16)0U; ( u2_TxNSduIdx < u2_TxNSduNum ) && ( pt_Ret == NULL_PTR ); u2_TxNSduIdx++ )
        {
            pt_TxNSduCfgTblTop = pt_ChCfgTbl->ptTxNSduCfgTbl;
            pt_TxNSduCfgTbl = &pt_TxNSduCfgTblTop[u2_TxNSduIdx];

            if( u2RxNPduId == pt_TxNSduCfgTbl->u2FcNPduId )
            {
                u1_AddressFormat = pt_TxNSduCfgTbl->u1AddressFormat;
                if( ( u1_AddressFormat == (uint8)BSW_CANTP_STANDARD )
                ||  ( u1_AddressFormat == (uint8)BSW_CANTP_NORMALFIXED ) )
                {   /* Normal/Normal fixed addressing format */
                    pt_Ret = pt_TxNSduCfgTbl;
                }
                else if( u1_AddressFormat == (uint8)BSW_CANTP_EXTENDED )
                {   /* Extended addressing format */

                    /* in TxNSdu       */
                    /*    N_TA: Client */
                    /*    N_SA: Server */

                    if( ptSduData[0U] == pt_TxNSduCfgTbl->u1NSa )
                    {
                        pt_Ret = pt_TxNSduCfgTbl;
                    }
                }
                else
                {   /* Mixed addressing format */

                    if( ptSduData[0U] == pt_TxNSduCfgTbl->u1NAe )
                    {
                        pt_Ret = pt_TxNSduCfgTbl;
                    }
                }
            }
        }
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u2_SenderNSduId = bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl.u2SenderNSduId;
        if( ( u2_SenderNSduId >= u2_MinTxNSduId )
        &&  ( u2_SenderNSduId <  ( u2_MinTxNSduId + u2_TotalTxNSduNum ) ) )
        {
            u2_TxNSduIdx = u2_SenderNSduId - u2_MinTxNSduId;
            pt_TxNSduCfgTbl = &(pt_FirstTxNSduCfg[u2_TxNSduIdx]);
            if( u2RxNPduId == pt_TxNSduCfgTbl->u2FcNPduId )
            {
                u1_AddressFormat = pt_TxNSduCfgTbl->u1AddressFormat;
                if( ( u1_AddressFormat == (uint8)BSW_CANTP_STANDARD )
                ||  ( u1_AddressFormat == (uint8)BSW_CANTP_NORMALFIXED ) )
                {   /* Normal/Normal fixed addressing format */
                    pt_Ret = pt_TxNSduCfgTbl;
                }
                else if( u1_AddressFormat == (uint8)BSW_CANTP_EXTENDED )
                {   /* Extended addressing format */

                    /* in TxNSdu       */
                    /*    N_TA: Client */
                    /*    N_SA: Server */

                    if( ptSduData[0U] == pt_TxNSduCfgTbl->u1NSa )
                    {
                        pt_Ret = pt_TxNSduCfgTbl;
                    }
                }
                else
                {   /* Mixed addressing format */

                    if( ptSduData[0U] == pt_TxNSduCfgTbl->u1NAe )
                    {
                        pt_Ret = pt_TxNSduCfgTbl;
                    }
                }
            }
        }
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    }

    return pt_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_GetRxNSduCfgByTxPdu                            */
/* Description   | Get RxNSdu configuration pointer to received TxNPdu      */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl    : Pointer to CanTp configration              */
/*               | u2TxNPduId  : Notified Tx NPdu-ID                        */
/* Return Value  | Bsw_CanTp_RxNSduCfgType                                  */
/*               |  !NULL_PTR  : Pointer to RxNSdu                          */
/*               |  NULL_PTR   : RxNSdu does not exist on this config       */
/* Notes         | None                                                     */
/****************************************************************************/
static BswConst Bsw_CanTp_RxNSduCfgType *
bsw_cantp_GetRxNSduCfgByTxPdu( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2TxNPduId )
{
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTbl;    /* Pointer to RxNSdu configuration  */
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_Ret;             /* Return value                     */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTblTop; /* Pointer to RxNSdu configuration  */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTblTop;     /* Pointer to ChCfgTbl              */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTbl;        /* Pointer to channel configuration */
    uint16                              u2_RxNSduNum;       /* Number of RxNSdus                */
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_FirstRxNSduCfg;  /* Pointer to First RxNSdu Cfg      */
    uint16                              u2_LatestRxNSduId;  /* Latest Rx NSdu-Id                */
    uint16                              u2_MinRxNSduId;     /* Minimum RxNSduId                 */
    uint16                              u2_TotalRxNSduNum;  /* Total RxNSdu Num                 */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    uint16                              u2_ReceiverNSduId;  /* Receiver Processing NSdu-Id      */
    uint16                              u2_RxNSduIdx;       /* Index of RxNSdus                 */
    uint8                               u1_ChId;            /* Channel ID                       */
    uint8                               u1_ChNum;           /* Number of channels               */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint8                               u1_ParentChId;      /* Connection channel ID            */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

    pt_Ret = NULL_PTR;

#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    /* Note: In order to get the start address of the NSdu configuration table, refer to 0CH and the 0th NSdu.                          */
    /*       To access NSdu configuration table using NSduId as a key, the start address of the NSdu configuration table is required.   */
    pt_FirstRxNSduCfg = &(ptCfgTbl->ptChCfgTbl[0U].ptRxNSduCfgTbl[0U]);
    u2_LatestRxNSduId = bsw_cantp_cmn_u2LatestRxNSduId;
    u2_MinRxNSduId    = ptCfgTbl->u2MinRxNSduId;
    u2_TotalRxNSduNum = ptCfgTbl->u2TotalRxNSduNum;
    if( ( u2_LatestRxNSduId >= u2_MinRxNSduId )
    &&  ( u2_LatestRxNSduId <  ( u2_MinRxNSduId + u2_TotalRxNSduNum ) ) )
    {
        u2_RxNSduIdx = u2_LatestRxNSduId - u2_MinRxNSduId;
        pt_RxNSduCfgTbl = &(pt_FirstRxNSduCfg[u2_RxNSduIdx]);
        u1_ParentChId = pt_RxNSduCfgTbl->u1ParentChId;
        u2_ReceiverNSduId = bsw_cantp_st_stChStatTbl[u1_ParentChId].stReceiverStatTbl.u2ReceiverNSduId;
        if( u2_ReceiverNSduId == u2_LatestRxNSduId )
        {
            if( u2TxNPduId == pt_RxNSduCfgTbl->u2CanIf_FcPduId )
            {
                pt_Ret = pt_RxNSduCfgTbl;
            }
        }
    }
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    /* Loop for number of connection channels */
    u1_ChNum = ptCfgTbl->u1ChNum;
    for( u1_ChId = (uint8)0U; ( u1_ChId < u1_ChNum ) && ( pt_Ret == NULL_PTR ); u1_ChId++ )
    {
        u2_ReceiverNSduId = bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl.u2ReceiverNSduId;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        if( u2_ReceiverNSduId != BSW_CANTP_u2NSDUID_NA )
        {
            pt_ChCfgTblTop = ptCfgTbl->ptChCfgTbl;
            pt_ChCfgTbl = &pt_ChCfgTblTop[u1_ChId];

            u2_RxNSduNum = pt_ChCfgTbl->u2RxNSduNum;
            for( u2_RxNSduIdx = (uint16)0U; u2_RxNSduIdx < u2_RxNSduNum; u2_RxNSduIdx++ )
            {
                pt_RxNSduCfgTblTop = pt_ChCfgTbl->ptRxNSduCfgTbl;
                pt_RxNSduCfgTbl = &pt_RxNSduCfgTblTop[u2_RxNSduIdx];
                if( ( u2TxNPduId        == pt_RxNSduCfgTbl->u2FcNPduId )
                &&  ( u2_ReceiverNSduId == pt_RxNSduCfgTbl->u2NSduId ) )
                {
                    pt_Ret = pt_RxNSduCfgTbl;
                    break;
                }
            }
        }
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        if( ( u2_ReceiverNSduId >= u2_MinRxNSduId )
        &&  ( u2_ReceiverNSduId <  ( u2_MinRxNSduId + u2_TotalRxNSduNum ) ) )
        {
            u2_RxNSduIdx = u2_ReceiverNSduId - u2_MinRxNSduId;
            pt_RxNSduCfgTbl = &(pt_FirstRxNSduCfg[u2_RxNSduIdx]);
            if( u2TxNPduId == pt_RxNSduCfgTbl->u2CanIf_FcPduId )
            {
                pt_Ret = pt_RxNSduCfgTbl;
            }
        }
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    }

    return pt_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_GetTxNSduCfgByTxPdu                            */
/* Description   | Get TxNSdu configuration pointer to received TxNPdu      */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl    : Pointer to CanTp configration              */
/*               | u2TxNPduId  : Notified Tx NPdu-ID                        */
/* Return Value  | Bsw_CanTp_TxNSduCfgType                                  */
/*               |  !NULL_PTR  : Pointer to TxNSdu                          */
/*               |  NULL_PTR   : TxNSdu does not exist on this config       */
/* Notes         | None                                                     */
/****************************************************************************/
static BswConst Bsw_CanTp_TxNSduCfgType *
bsw_cantp_GetTxNSduCfgByTxPdu( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2TxNPduId )
{
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTbl;    /* Pointer to TxNSdu configuration  */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_Ret;             /* Return value                     */
    uint16                              u2_SenderNSduId;    /* Sender Processing NSdu-Id        */
    uint16                              u2_TxNSduIdx;       /* Index of TxNSdus                 */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTblTop; /* Pointer to TxNSdu configuration  */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTblTop;     /* Pointer to ChCfgTbl              */
    BswConst Bsw_CanTp_ChCfgType *      pt_ChCfgTbl;        /* Pointer to channel configuration */
    uint16                              u2_TxNSduNum;       /* Number of TxNSdus                */
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_FirstTxNSduCfg;  /* Pointer to First TxNSdu Cfg      */
    uint16                              u2_MinTxNSduId;     /* Minimum TxNSduId                 */
    uint16                              u2_TotalTxNSduNum;  /* Total TxNSdu Num                 */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    uint8                               u1_ChId;            /* Channel ID                       */
    uint8                               u1_ChNum;           /* Number of channels               */

    pt_Ret = NULL_PTR;

    /* Loop for number of connection channels */
    u1_ChNum = ptCfgTbl->u1ChNum;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    u2_MinTxNSduId = ptCfgTbl->u2MinTxNSduId;
    u2_TotalTxNSduNum = ptCfgTbl->u2TotalTxNSduNum;

    /* Note: In order to get the start address of the NSdu configuration table, refer to 0CH and the 0th NSdu.                          */
    /*       To access NSdu configuration table using NSduId as a key, the start address of the NSdu configuration table is required.   */
    pt_FirstTxNSduCfg = &(ptCfgTbl->ptChCfgTbl[0U].ptTxNSduCfgTbl[0U]);
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    for( u1_ChId = (uint8)0U; ( u1_ChId < u1_ChNum ) && ( pt_Ret == NULL_PTR ); u1_ChId++ )
    {
        u2_SenderNSduId = bsw_cantp_st_stChStatTbl[u1_ChId].stSenderStatTbl.u2SenderNSduId;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        if( u2_SenderNSduId != BSW_CANTP_u2NSDUID_NA )
        {
            pt_ChCfgTblTop = ptCfgTbl->ptChCfgTbl;
            pt_ChCfgTbl = &pt_ChCfgTblTop[u1_ChId];

            u2_TxNSduNum = pt_ChCfgTbl->u2TxNSduNum;
            for( u2_TxNSduIdx = (uint16)0U; u2_TxNSduIdx < u2_TxNSduNum; u2_TxNSduIdx++ )
            {
                pt_TxNSduCfgTblTop = pt_ChCfgTbl->ptTxNSduCfgTbl;
                pt_TxNSduCfgTbl = &pt_TxNSduCfgTblTop[u2_TxNSduIdx];

                if( ( u2TxNPduId      == pt_TxNSduCfgTbl->u2NPduId )
                &&  ( u2_SenderNSduId == pt_TxNSduCfgTbl->u2NSduId ) )
                {
                    pt_Ret = pt_TxNSduCfgTbl;
                    break;
                }
            }
        }
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        if( ( u2_SenderNSduId >= u2_MinTxNSduId )
        &&  ( u2_SenderNSduId <  ( u2_MinTxNSduId + u2_TotalTxNSduNum ) ) )
        {
            u2_TxNSduIdx = u2_SenderNSduId - u2_MinTxNSduId;
            pt_TxNSduCfgTbl = &(pt_FirstTxNSduCfg[u2_TxNSduIdx]);
            if( u2TxNPduId == pt_TxNSduCfgTbl->u2CanIf_PduId )
            {
                pt_Ret = pt_TxNSduCfgTbl;
            }
        }
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
    }

    return pt_Ret;
}


/****************************************************************************/
/* Function Name | bsw_cantp_RxIndForwardByNPCI                             */
/* Description   | RxIndication forwarding by N_PCI type                    */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl    : Pointer to CanTp configuration             */
/*               | ptTpPduInfo : Pointer to PDU information                 */
/*               | u2RxNPduId  : Notified Rx NPdu-ID                        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_cantp_RxIndForwardByNPCI( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo, uint16 u2RxNPduId )
{
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTbl;    /* Pointer to RxNSdu configuration */
    BswConst Bsw_CanTp_TxNSduCfgType *  pt_TxNSduCfgTbl;    /* Pointer to TxNSdu configuration */
    uint8                               u1_PciOffset;       /* Offset to N_PCI address         */
    uint8                               u1_PciType;         /* N_PCI Type                      */
    uint8                               u1_AddressFormat;   /* Addressing format               */

    /* Check of minimum data length required to identify N_PCI */
    if( ptTpPduInfo->u4SduLength >= (uint32)BSW_CANTP_u1CAN_DL_02 )
    {
        /*-------------------------------*/
        /* NSdu Search Order             */
        /* 1.Rx NSdu(SF/FF/CF reception) */
        /* 2.Tx NSdu(FC       reception) */
        /*-------------------------------*/

        u1_PciType = BSW_CANTP_u1PCI_UNKNOWN;

        /* Search the N_AI(N_SduId & N_TA,N_AE field) matches the local configuration of CAN (FD) */
        pt_RxNSduCfgTbl = bsw_cantp_GetRxNSduCfgByRxPdu( ptCfgTbl, u2RxNPduId, ptTpPduInfo->ptSduData );
        if( pt_RxNSduCfgTbl != NULL_PTR )
        {

            u1_AddressFormat = pt_RxNSduCfgTbl->u1AddressFormat;
            u1_PciOffset = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];
            u1_PciType = ptTpPduInfo->ptSduData[u1_PciOffset] & BSW_CANTP_u1MASK_PCI;

            if( u1_PciType == BSW_CANTP_u1PCI_SF )
            {   /* SF */
                bsw_cantp_rx_RxIndSF( ptCfgTbl, pt_RxNSduCfgTbl, ptTpPduInfo );
            }
            else if( u1_PciType == BSW_CANTP_u1PCI_FF )
            {   /* FF */
                bsw_cantp_rx_RxIndFF( ptCfgTbl, pt_RxNSduCfgTbl, ptTpPduInfo );
            }
            else if( u1_PciType == BSW_CANTP_u1PCI_CF )
            {   /* CF */
                bsw_cantp_rx_RxIndCF( ptCfgTbl, pt_RxNSduCfgTbl, ptTpPduInfo );
            }
            else
            {   /* FC or unknown PCI or configuration data is incorrect */
                u1_PciType = BSW_CANTP_u1PCI_UNKNOWN;
            }
        }

        if( u1_PciType == BSW_CANTP_u1PCI_UNKNOWN )
        {
            /* Search the N_AI(N_SduId & N_TA,N_AE field) matches the local configuration of CAN (FD) */
            pt_TxNSduCfgTbl = bsw_cantp_GetTxNSduCfgByRxPdu( ptCfgTbl, u2RxNPduId, ptTpPduInfo->ptSduData );
            if( pt_TxNSduCfgTbl != NULL_PTR )
            {
                u1_AddressFormat = pt_TxNSduCfgTbl->u1AddressFormat;
                u1_PciOffset = bsw_cantp_cmn_u1PciOffSetTbl[u1_AddressFormat];
                u1_PciType = ptTpPduInfo->ptSduData[u1_PciOffset] & BSW_CANTP_u1MASK_PCI;

                if( u1_PciType == BSW_CANTP_u1PCI_FC )
                {   /* FC */
                    bsw_cantp_tx_RxIndFC( pt_TxNSduCfgTbl, ptTpPduInfo );
                }
            }
        }
    }

    return;
}


#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_cantp_ChangeParamCore                                */
/* Description   | Set parameter BS/STmin to target RxNSduId core procedure */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl    : Pointer to CanTp configuration             */
/*               | u2NSduId    : Target Rx NSdu-Id                          */
/*               | u1Parameter : Type of change parameter                   */
/*               | u2Value     : Value of parameter                         */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Accept change request                        */
/*               |  E_NOT_OK : Reject change request                        */
/* Notes         | None                                                     */
/****************************************************************************/
static Std_ReturnType
bsw_cantp_ChangeParamCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2NSduId, uint8 u1Parameter, uint16 u2Value )
{
    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTbl;    /* Pointer to RxNSdu configuration */
    Bsw_CanTp_st_ReceiverStatType *     pt_ReceiverStatTbl; /* Pointer to receiver status info */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint16                              u2_RxNSduIdx;       /* Index of RxNSdus                */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    uint8                               u1_ChId;            /* Channel ID                      */
    Std_ReturnType                      u1_Ret;             /* Return value                    */

    u1_Ret             = (Std_ReturnType)E_NOT_OK;
    pt_RxNSduCfgTbl    = bsw_cantp_cmn_GetRxNSduCfgTbl( ptCfgTbl, u2NSduId );
    u1_ChId            = pt_RxNSduCfgTbl->u1ParentChId;
    pt_ReceiverStatTbl = &(bsw_cantp_st_stChStatTbl[u1_ChId].stReceiverStatTbl);

    /********************************************/
    /*******  Start of exclusive section  *******/

    /* The change parameter API is acceptable only when the requested NSduId is not in reception */
    if( u2NSduId != pt_ReceiverStatTbl->u2ReceiverNSduId )
    {
#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
        if( u1Parameter == (uint8)TP_BS )
        {
            bsw_cantp_rx_ChangeParamBS( pt_RxNSduCfgTbl, u2Value );
        }
        else
        {   /* u1Parameter == (uint8)TP_STMIN */
            bsw_cantp_rx_ChangeParamSTmin( pt_RxNSduCfgTbl, u2Value );
        }
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
        u2_RxNSduIdx = u2NSduId - ptCfgTbl->u2MinRxNSduId;
        if( u1Parameter == (uint8)TP_BS )
        {
            bsw_cantp_rx_ChangeParamBSByIdx( u2_RxNSduIdx, u2Value );
        }
        else
        {   /* u1Parameter == (uint8)TP_STMIN */
            bsw_cantp_rx_ChgParamSTminByIdx( u2_RxNSduIdx, u2Value );
        }
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */
        u1_Ret = (Std_ReturnType)E_OK;
    }

    /*******   End of exclusive section   *******/
    /********************************************/

    return u1_Ret;
}
#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */


#if( BSW_CANTP_CFG_READ_RXPARAM == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_cantp_ReadParamCore                                  */
/* Description   | Read selected parameter of RxNSduId core procedure       */
/* Preconditions | None                                                     */
/* Parameters    | ptCfgTbl    : Pointer to CanTp configuration             */
/*               | u2NSduId    : Target Rx NSdu-Id                          */
/*               | u1Parameter : Type of change parameter                   */
/* Return Value  | uint16      : Read value                                 */
/* Notes         | None                                                     */
/****************************************************************************/
static uint16
bsw_cantp_ReadParamCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2NSduId, uint8 u1Parameter )
{

    BswConst Bsw_CanTp_RxNSduCfgType *  pt_RxNSduCfgTbl;    /* Pointer to RxNSdu configuration */
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
    uint16                              u2_RxNSduIdx;       /* Index of RxNSdus                */
    uint8                               u1_RxParamPtn;      /* Rx Parameter Pattern            */
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    uint16                              u2_Ret;             /* Return value                    */

#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
    pt_RxNSduCfgTbl = bsw_cantp_cmn_GetRxNSduCfgTbl( ptCfgTbl, u2NSduId );
    if( u1Parameter == (uint8)TP_BS )
    {   /* BS */
        u2_Ret = bsw_cantp_rx_ReadParamBS( pt_RxNSduCfgTbl );
    }
    else
    {   /* STMIN */
        u2_Ret = bsw_cantp_rx_ReadParamSTmin( pt_RxNSduCfgTbl );
    }
#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
    u2_RxNSduIdx    = u2NSduId - ptCfgTbl->u2MinRxNSduId;
    pt_RxNSduCfgTbl = bsw_cantp_cmn_GetRxNSduCfgTbl( ptCfgTbl, u2NSduId );
    u1_RxParamPtn   = pt_RxNSduCfgTbl->u1RxParamPtn;
    if( u1Parameter == (uint8)TP_BS )
    {
        u2_Ret = bsw_cantp_rx_ReadParamBSByIdx( u2_RxNSduIdx, u1_RxParamPtn );
    }
    else
    {   /* u1Parameter == (uint8)TP_STMIN */
        u2_Ret = bsw_cantp_rx_ReadParaSTminByIdx( u2_RxNSduIdx,u1_RxParamPtn );
    }
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */

    return u2_Ret;
}
#endif /* BSW_CANTP_CFG_READ_RXPARAM == BSW_USE */


#endif /* BSW_BSWM_CS_FUNC_CANTP == BSW_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/25                                             */
/*  v1-1-0          :2018/12/26                                             */
/*  v1-2-0          :2020/02/13                                             */
/*  v2-0-0          :2021/09/07                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
