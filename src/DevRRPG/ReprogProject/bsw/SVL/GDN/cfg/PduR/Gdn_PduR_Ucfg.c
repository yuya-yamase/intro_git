/* Gdn_PduR_Ucfg_c_00_0003 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | PDUルータ（コンフィグ）                                      */
/* Notes       | 本モジュールはコンフィグツールにより自動生成される           */
/*             | ツールバージョン：GUARDIAN_218v41_MET_Tool217                */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     テンプレートの新規作成                    */
/*  00_0001   2018/02/13   AUBASS   リプログ対応                              */
/*  00_0002   2019/12/03   AUBASS   Update                                    */
/*  00_0003   2021/09/14   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn.h>
#include <Gdn_Ucfg.h>
#include "Gdn_PduR_Ucfg.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
    /* 下位Network層の受信ルーティングテーブルの生成マクロ */
#define GDN_PDUR_SetLoNwRxTbl( comp , id )                  \
{                                                           \
    (gdn_uint16)GDN_PDUR_RxDstCnt_LoNw_ ##comp##_##id ,     \
              &gdn_pdur_LoNwRxDestTbl_ ##comp##_##id [0]    \
}

#define GDN_PDUR_SetLoNwRxDst( comp , id , dst )                                \
{                                                                               \
    (Gdn_PduR_NwRxDstIfType)GDN_PDUR_UpLoDstIF_LoNw_ ##comp##_##id##_##dst ,    \
    GDN_PDUR_UpLoPduId_LoNw_                         ##comp##_##id##_##dst      \
}

    /* 下位Network層の送信ルーティングテーブルの生成マクロ */
    #if ( ( GDN_PDUR_TriggerTransmitApi_Nw == GDN_ON ) && \
          ( GDN_PDUR_TxConfirmationApi_Nw  != GDN_ON ) )
#define GDN_PDUR_SetLoNwTxTbl( comp , id )                                  \
{                                                                           \
    GDN_PDUR_LoTxPduId_LoNw_                             ##comp##_##id ,    \
    (Gdn_PduR_NwTxTrgIfType)GDN_PDUR_UpTrgIF_LoNw_       ##comp##_##id ,    \
    GDN_PDUR_UpTxPduId_LoNw_                             ##comp##_##id      \
}
    #elif ( ( GDN_PDUR_TriggerTransmitApi_Nw != GDN_ON ) && \
            ( GDN_PDUR_TxConfirmationApi_Nw  == GDN_ON ) )
#define GDN_PDUR_SetLoNwTxTbl( comp , id )                                  \
{                                                                           \
    GDN_PDUR_LoTxPduId_LoNw_                             ##comp##_##id ,    \
    (Gdn_PduR_NwTxConIfType)GDN_PDUR_UpConIF_LoNw_       ##comp##_##id ,    \
    GDN_PDUR_UpTxPduId_LoNw_                             ##comp##_##id      \
}
    #else
#define GDN_PDUR_SetLoNwTxTbl( comp , id )                                  \
{                                                                           \
    GDN_PDUR_LoTxPduId_LoNw_                             ##comp##_##id ,    \
    (Gdn_PduR_NwTxTrgIfType)GDN_PDUR_UpTrgIF_LoNw_       ##comp##_##id ,    \
    (Gdn_PduR_NwTxConIfType)GDN_PDUR_UpConIF_LoNw_       ##comp##_##id ,    \
    GDN_PDUR_UpTxPduId_LoNw_                             ##comp##_##id      \
}
    #endif

    /* 上位Network層の送信ルーティングテーブルの生成マクロ */
    #if ( GDN_PDUR_CancelTransmitApi_Nw == GDN_ON )
#define GDN_PDUR_SetUpNwTxTbl( comp , id )                                  \
{                                                                           \
    (Gdn_PduR_NwTxTransIfType)GDN_PDUR_LoTransIF_UpNw_   ##comp##_##id ,    \
    (Gdn_PduR_NwTxCancelIfType)GDN_PDUR_LoCancelIF_UpNw_ ##comp##_##id ,    \
    GDN_PDUR_LoTxPduId_UpNw_                             ##comp##_##id      \
}
    #else
#define GDN_PDUR_SetUpNwTxTbl( comp , id )                                  \
{                                                                           \
    (Gdn_PduR_NwTxTransIfType)GDN_PDUR_LoTransIF_UpNw_   ##comp##_##id ,    \
    GDN_PDUR_LoTxPduId_UpNw_                             ##comp##_##id      \
}
    #endif

    /* 下位Transport層の受信ルーティングテーブルの生成マクロ */
#define GDN_PDUR_SetLoTpRxTbl( comp , id )                                                  \
{                                                                                           \
    (Gdn_PduR_TpRxStartIfType)GDN_PDUR_UpStartIF_LoTp_                ##comp##_##id ,       \
    (Gdn_PduR_TpRxCopyIfType)GDN_PDUR_UpCopyRxIF_LoTp_                ##comp##_##id ,       \
    (Gdn_PduR_TpRxIndIfType)GDN_PDUR_UpRxIndIF_LoTp_                  ##comp##_##id ,       \
    GDN_PDUR_UpRxPduId_LoTp_                                          ##comp##_##id ,       \
    (gdn_uint8)GDN_PDUR_GwDstCnt_LoTp_                                ##comp##_##id ,       \
    &((GdnConst Gdn_PduR_LoTpGatewayInfoType*)gdn_pdur_LoTpGwDestTbl_ ##comp##_##id )[0],   \
    (Gdn_PduLengthType)GDN_PDUR_GwBufSize_LoTp_                       ##comp##_##id ,       \
    &((gdn_uint8*)Gdn_PduR_LoTpGwBuffer_                              ##comp##_##id )[0]    \
}

#define GDN_PDUR_SetLoTpGwDst( comp , id , dst )                                    \
{                                                                                   \
    (Gdn_PduR_TpTxTransIfType)GDN_PDUR_LoTransIF_LoTp_ ##comp##_##id##_##dst ,      \
    GDN_PDUR_LoGwPduId_LoTp_                           ##comp##_##id##_##dst ,      \
    &Gdn_PduR_LoTpTxDataPtr_                           ##comp##_##id##[##dst ]      \
}

#if ( ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoTp_0 != 0U ) )
#define GDN_PDUR_DefineLoTpGwInfo( comp , id )                                                              \
static gdn_uint8 Gdn_PduR_LoTpGwBuffer_##comp##_##id##[GDN_PDUR_GwBufSize_LoTp_##comp##_##id ]         ;   \
static Gdn_PduLengthType Gdn_PduR_LoTpTxDataPtr_##comp##_##id##[GDN_PDUR_GwDstCnt_LoTp_##comp##_##id ] ;   \
static GdnConst Gdn_PduR_LoTpGatewayInfoType gdn_pdur_LoTpGwDestTbl_##comp##_##id##[GDN_PDUR_GwDstCnt_LoTp_##comp##_##id ]
#endif

#define GDN_PDUR_SetLoTpRxTblList( comp )                                               \
{                                                                                       \
    (gdn_uint8)GDN_PDUR_MaxRxPduIdCnt_LoTp_                               ##comp ,      \
    &((GdnConst Gdn_PduR_LoTpRxRoutingTblType*)gdn_pdur_LoTpRxRoutingTbl_ ##comp )[0],  \
    &((Gdn_PduLengthType*)Gdn_PduR_LoTpRxDataPtr_                         ##comp )[0]   \
}

    /* 下位Transport層の受信ルーティングテーブルの生成マクロ */
#define GDN_PDUR_SetLoTpTxTbl( comp , id )                                      \
{                                                                               \
    GDN_PDUR_LoTxPduId_LoTp_                                ##comp##_##id ,     \
    (Gdn_PduR_TpTxCopyIfType)GDN_PDUR_UpCopyTxIF_LoTp_      ##comp##_##id ,     \
    (Gdn_PduR_TpTxConIfType)GDN_PDUR_UpTxConIF_LoTp_        ##comp##_##id ,     \
    GDN_PDUR_UpTxPduId_LoTp_                                ##comp##_##id ,     \
    (gdn_uint8)GDN_PDUR_LoSrcCmpId_LoTp_                    ##comp##_##id ,     \
    GDN_PDUR_LoSrcPduId_LoTp_                               ##comp##_##id ,     \
    (gdn_uint8)GDN_PDUR_LoSrcGwIdx_LoTp_                    ##comp##_##id       \
}

    /* 上位Transport層の受信ルーティングテーブルの生成マクロ */
    #if ( ( GDN_PDUR_CancelReceiveApi_Tp   == GDN_ON ) && \
          ( GDN_PDUR_ChangeParameterApi_Tp != GDN_ON ) )
#define GDN_PDUR_SetUpTpRxTbl( comp , id )                                      \
{                                                                               \
    GDN_PDUR_UpRxPduId_UpTp_                                ##comp##_##id ,     \
    (Gdn_PduR_TpRxCancelIfType)GDN_PDUR_LoCancelRxIF_UpTp_  ##comp##_##id ,     \
    GDN_PDUR_LoRxPduId_UpTp_                                ##comp##_##id       \
}
    #elif ( ( GDN_PDUR_CancelReceiveApi_Tp   != GDN_ON ) && \
            ( GDN_PDUR_ChangeParameterApi_Tp == GDN_ON ) )
#define GDN_PDUR_SetUpTpRxTbl( comp , id )                                      \
{                                                                               \
    GDN_PDUR_UpRxPduId_UpTp_                                ##comp##_##id ,     \
    (Gdn_PduR_TpRxChgParIfType)GDN_PDUR_LoChgParaIF_UpTp_   ##comp##_##id ,     \
    GDN_PDUR_LoRxPduId_UpTp_                                ##comp##_##id       \
}
    #else
#define GDN_PDUR_SetUpTpRxTbl( comp , id )                                      \
{                                                                               \
    GDN_PDUR_UpRxPduId_UpTp_                                ##comp##_##id ,     \
    (Gdn_PduR_TpRxCancelIfType)GDN_PDUR_LoCancelRxIF_UpTp_  ##comp##_##id ,     \
    (Gdn_PduR_TpRxChgParIfType)GDN_PDUR_LoChgParaIF_UpTp_   ##comp##_##id ,     \
    GDN_PDUR_LoRxPduId_UpTp_                                ##comp##_##id       \
}
    #endif

    /* 上位Transport層の送信ルーティングテーブルの生成マクロ */
    #if ( GDN_PDUR_CancelTransmitApi_Tp == GDN_ON )
#define GDN_PDUR_SetUpTpTxTbl( comp , id )                                      \
{                                                                               \
    (Gdn_PduR_TpTxTransIfType)GDN_PDUR_LoTransIF_UpTp_      ##comp##_##id ,     \
    (Gdn_PduR_TpTxCancelIfType)GDN_PDUR_LoCancelTxIF_UpTp_  ##comp##_##id ,     \
    GDN_PDUR_LoTxPduId_UpTp_                                ##comp##_##id ,     \
}
    #else
#define GDN_PDUR_SetUpTpTxTbl( comp , id )                                      \
{                                                                               \
    (Gdn_PduR_TpTxTransIfType)GDN_PDUR_LoTransIF_UpTp_      ##comp##_##id ,     \
    GDN_PDUR_LoTxPduId_UpTp_                                ##comp##_##id ,     \
}
    #endif

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_PDUR_START_SEC_VAR
#include <Gdn_PduR_MemMap.h>

#if ( ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoTp_0 != 0U ) )
Gdn_PduLengthType Gdn_PduR_LoTpRxDataPtr_0[GDN_PDUR_MaxRxPduIdCnt_LoTp_0];
#else
#define Gdn_PduR_LoTpRxDataPtr_0      (GDN_NULL_PTR)
#endif

#define GDN_PDUR_STOP_SEC_VAR
#include <Gdn_PduR_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_PDUR_START_SEC_CST
#include <Gdn_PduR_MemMap.h>

    /*--------------------------------*/
    /* PDUR_下位Network層のコンフィグ */
    /*--------------------------------*/
      /********************/
      /* コンポーネント#0 */
      /********************/
#if ( ( GDN_PDUR_UseZeroCost_LoNw_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoNw_0 != 0U ) )
        /* 受信PDUIDの転送先情報 */
static GdnConst Gdn_PduR_LoNwRxDstInfoType gdn_pdur_LoNwRxDestTbl_0_0[GDN_PDUR_RxDstCnt_LoNw_0_0] = {
    /* 定義なし */
};

        /* 受信ルーティングテーブル */
GdnConst Gdn_PduR_LoNwRxRoutingTblType gdn_pdur_LoNwRxRoutingTbl_0[GDN_PDUR_MaxRxPduIdCnt_LoNw_0] = {
    /* 定義なし */
};
#endif

#if ( ( GDN_PDUR_UseZeroCost_LoNw_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_LoNw_0 != 0U ) )
        /* 送信ルーティングテーブル */
GdnConst Gdn_PduR_LoNwTxRoutingTblType gdn_pdur_LoNwTxRoutingTbl_0[GDN_PDUR_MaxTxPduIdCnt_LoNw_0] = {
    /* 定義なし */
};
#endif


    /*--------------------------------*/
    /* PDUR_上位Network層のコンフィグ */
    /*--------------------------------*/


    /*--------------------------------------*/
    /* PDUR_下位Transport層受信のコンフィグ */
    /*--------------------------------------*/
      /********************/
      /* コンポーネント#0 */
      /********************/
#if ( ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_LoTp_0 != 0U ) )
        /* 受信PDUID0のゲートウェイ先情報 */
    #if ( GDN_PDUR_GwDstCnt_LoTp_0_0 != 0U )
GDN_PDUR_DefineLoTpGwInfo( 0, 0 ) = {
    /* 定義なし */
};
    #else
#define Gdn_PduR_LoTpGwBuffer_0_0    (GDN_NULL_PTR)
#define gdn_pdur_LoTpGwDestTbl_0_0   (GDN_NULL_PTR)
    #endif
        /* 受信PDUID1のゲートウェイ先情報 */
    #if ( GDN_PDUR_GwDstCnt_LoTp_0_1 != 0U )
GDN_PDUR_DefineLoTpGwInfo( 0, 1 ) = {
    /* 定義なし */
};
    #else
#define Gdn_PduR_LoTpGwBuffer_0_1    (GDN_NULL_PTR)
#define gdn_pdur_LoTpGwDestTbl_0_1   (GDN_NULL_PTR)
    #endif

        /* 受信ルーティングテーブル */
GdnConst Gdn_PduR_LoTpRxRoutingTblType gdn_pdur_LoTpRxRoutingTbl_0[GDN_PDUR_MaxRxPduIdCnt_LoTp_0] = {
    GDN_PDUR_SetLoTpRxTbl( 0 , 0 ),
    GDN_PDUR_SetLoTpRxTbl( 0 , 1 )
};
#else
#define gdn_pdur_LoTpRxRoutingTbl_0   (GDN_NULL_PTR)
#endif


    /*-------------------------------------------------*/
    /* 下位Transport層受信ルーティングテーブルのリスト */
    /*-------------------------------------------------*/
#if ( ( GDN_PDUR_UsePduR_Tp == GDN_ON ) && ( GDN_PDUR_OnlyZeroCost_Tp != GDN_ON ) )
GdnConst Gdn_PduR_LoTpRxTableListType gdn_pdur_LoTpRxRoutingTableList[GDN_PDUR_MaxLoLayerCnt_Tp] = {
    GDN_PDUR_SetLoTpRxTblList( 0 )
};
#endif


    /*--------------------------------------*/
    /* PDUR_下位Transport層送信のコンフィグ */
    /*--------------------------------------*/
      /********************/
      /* コンポーネント#0 */
      /********************/
#if ( ( GDN_PDUR_UseZeroCost_LoTp_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_LoTp_0 != 0U ) )
        /* 送信ルーティングテーブル */
GdnConst Gdn_PduR_LoTpTxRoutingTblType gdn_pdur_LoTpTxRoutingTbl_0[GDN_PDUR_MaxTxPduIdCnt_LoTp_0] = {
    GDN_PDUR_SetLoTpTxTbl( 0 , 0 )
};
#endif


    /*----------------------------------*/
    /* PDUR_上位Transport層のコンフィグ */
    /*----------------------------------*/
      /********************/
      /* コンポーネント#0 */
      /********************/
#if ( ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_MaxRxPduIdCnt_UpTp_0 != 0U ) )
        /* 受信ルーティングテーブル */
GdnConst Gdn_PduR_UpTpRxRoutingTblType gdn_pdur_UpTpRxRoutingTbl_0[GDN_PDUR_MaxRxPduIdCnt_UpTp_0] = {
    /* 定義なし */
};
#endif

#if ( ( GDN_PDUR_UseZeroCost_UpTp_0 != GDN_ON ) && ( GDN_PDUR_MaxTxPduIdCnt_UpTp_0 != 0U ) )
        /* 送信ルーティングテーブル */
GdnConst Gdn_PduR_UpTpTxRoutingTblType gdn_pdur_UpTpTxRoutingTbl_0[GDN_PDUR_MaxTxPduIdCnt_UpTp_0] = {
    /* 定義なし */
};
#endif

#define GDN_PDUR_STOP_SEC_CST
#include <Gdn_PduR_MemMap.h>

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
/**** End of File *************************************************************/

