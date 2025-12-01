/* can_rscf3c_tb_log_h_v3-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF3C/TB/LOGICAL/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF3C_TB_LOG_H
#define     CAN_RSCF3C_TB_LOG_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*======================================*/
/* HOH 配置情報                         */
/*======================================*/
/* 総HRH数 */
#define CAN_TB_HRHNUM \
   (  CAN_CFG_HRHNUM_0 \
    + CAN_CFG_HRHNUM_1 \
    + CAN_CFG_HRHNUM_2 \
    + CAN_CFG_HRHNUM_3 \
    + CAN_CFG_HRHNUM_4 \
    + CAN_CFG_HRHNUM_5 \
    + CAN_CFG_HRHNUM_6 \
    + CAN_CFG_HRHNUM_7 )

/* 総HRH数最大値 */
/* 現状はコンフィグセット0固定のため、総HRH数を設定する。                                      */
/* 将来コンフィグセット複数対応する場合、コンフィグセット毎のHRH数の内の最大値を指定すること。 */
#define CAN_TB_HRHNUM_MAX               ( CAN_TB_HRHNUM )

/* 総HTH数 */
#define CAN_TB_HTHNUM \
   (  CAN_CFG_HTHNUM_0 \
    + CAN_CFG_HTHNUM_1 \
    + CAN_CFG_HTHNUM_2 \
    + CAN_CFG_HTHNUM_3 \
    + CAN_CFG_HTHNUM_4 \
    + CAN_CFG_HTHNUM_5 \
    + CAN_CFG_HTHNUM_6 \
    + CAN_CFG_HTHNUM_7 )

/* 総HTH数最大値 */
/* 現状はコンフィグセット0固定のため、総HTH数を設定する。                                      */
/* 将来コンフィグセット複数対応する場合、コンフィグセット毎のHTH数の内の最大値を指定すること。 */
#define CAN_TB_HTHNUM_MAX               ( CAN_TB_HTHNUM )

/* 総HOH数 */
#define CAN_TB_HOHNUM                   ( CAN_TB_HRHNUM + CAN_TB_HTHNUM )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* コントローラ設定型 */
typedef struct
{
    uint8  u1ControllerActivation;          /* コントローラ別制御対象/対象外          */
    uint8  u1ControllerUse;                 /* コントローラ別使用/未使用              */
    uint8  u1BusoffProcessing;              /* コントローラ別バスオフ検出方法         */
    uint8  u1BusoffRecovery;                /* コントローラ別バスオフ復帰方法         */
} CanTbControllerConfigType;


/* HOH-MBOX配置情報型 */
typedef struct
{
    uint16 u2HthOffset;                     /* コントローラ毎HTH開始位置              */
    uint16 u2HrhOffset;                     /* コントローラ毎HRH開始位置              */
    uint8  u1HthNum;                        /* コントローラ毎HTH数                    */
    uint8  u1HrhNum;                        /* コントローラ毎HRH数                    */
    uint8  u1HthMbOffset;                   /* コントローラ毎HTH配置MBOX開始位置      */
    uint8  u1HrhMbOffset;                   /* コントローラ毎HRH配置MBOX開始位置      */
} CanTbHohMbAllocType;


/* ユーザ送信用MBOX配置情報型 */
typedef struct
{
    uint8  u1UTxMbOffset;                   /* コントローラ毎ユーザ送信用MBOX開始位置 */
    uint8  u1UTxMbNum;                      /* コントローラ毎ユーザ送信用MBOX数       */
} CanTbUTxMbAllocType;


/* HOHコンフィグ情報型 */
typedef struct
{
    uint8  u1ControllerID;                  /* コントローラID   */
    uint8  u1MboxNo;                        /* MBOX番号         */
} CanHohCfgType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* コントローラ設定テーブル */
extern CanConst CanTbControllerConfigType Can_tb_stControllerCfgTbl[ CAN_CFG_CONTROLLERNUM_MAX ];

/* HOH-MBOX配置情報テーブル */
extern CanConst CanTbHohMbAllocType Can_tb_stHohMbAlloc[ CAN_CFG_CONTROLLERNUM_MAX ];

/* HOHコンフィグ情報テーブル */
#if (CAN_CFG_TRANSMIT == CAN_USE)
extern CanConst CanHohCfgType Can_stHohCfgTbl[ CAN_TB_HOHNUM ];
#endif /*  (CAN_CFG_TRANSMIT == CAN_USE) */

/* HOHコンフィグ情報テーブル参照ポインタ */
extern CanConst CanHohCfgType * CanConst Can_tb_ptHohCfgTbl;

/* レジスタ固着チェック分割回数 */
extern CanConst uint8 Can_tb_u1RegChkNum;

/* 搭載CANコントローラ数 */
extern CanConst uint8 Can_tb_u1ControllerNumMax;

/* 総HRH数最大値 */
extern CanConst uint16 Can_tb_u2HrhNumMax;

/* 総HTH数最大値 */
extern CanConst uint16 Can_tb_u2HthNumMax;

/* ユーザ送信用MBOX配置情報テーブル */
extern CanConst CanTbUTxMbAllocType Can_tb_stUTxMbAlloc[ CAN_CFG_CONTROLLERNUM_MAX ];


#endif  /* CAN_RSCF3C_TB_LOG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
