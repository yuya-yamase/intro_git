/* bsw_cantp_config_h_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/CONFIG/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANTP_CONFIG_H
#define BSW_CANTP_CONFIG_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* The total number of RxNSdus */
#define BSW_CANTP_RXNSDUNUM_0_7 \
   (  BSW_CANTP_CFG_RXNSDUNUM_CH00 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH01 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH02 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH03 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH04 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH05 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH06 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH07 )

#define BSW_CANTP_RXNSDUNUM_8_15 \
   (  BSW_CANTP_CFG_RXNSDUNUM_CH08 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH09 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH10 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH11 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH12 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH13 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH14 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH15 )

#define BSW_CANTP_RXNSDUNUM_16_23 \
   (  BSW_CANTP_CFG_RXNSDUNUM_CH16 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH17 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH18 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH19 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH20 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH21 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH22 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH23 )

#define BSW_CANTP_RXNSDUNUM_24_31 \
   (  BSW_CANTP_CFG_RXNSDUNUM_CH24 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH25 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH26 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH27 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH28 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH29 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH30 \
    + BSW_CANTP_CFG_RXNSDUNUM_CH31 )

#define BSW_CANTP_RXNSDUNUM ( BSW_CANTP_RXNSDUNUM_0_7 + BSW_CANTP_RXNSDUNUM_8_15 \
        + BSW_CANTP_RXNSDUNUM_16_23 + BSW_CANTP_RXNSDUNUM_24_31 )

/* The total number of TxNSdus */
#define BSW_CANTP_TXNSDUNUM_0_7 \
   (  BSW_CANTP_CFG_TXNSDUNUM_CH00 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH01 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH02 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH03 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH04 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH05 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH06 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH07 )

#define BSW_CANTP_TXNSDUNUM_8_15 \
   (  BSW_CANTP_CFG_TXNSDUNUM_CH08 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH09 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH10 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH11 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH12 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH13 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH14 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH15 )

#define BSW_CANTP_TXNSDUNUM_16_23 \
   (  BSW_CANTP_CFG_TXNSDUNUM_CH16 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH17 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH18 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH19 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH20 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH21 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH22 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH23 )

#define BSW_CANTP_TXNSDUNUM_24_31 \
   (  BSW_CANTP_CFG_TXNSDUNUM_CH24 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH25 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH26 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH27 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH28 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH29 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH30 \
    + BSW_CANTP_CFG_TXNSDUNUM_CH31 )

#define BSW_CANTP_TXNSDUNUM ( BSW_CANTP_TXNSDUNUM_0_7 + BSW_CANTP_TXNSDUNUM_8_15 \
        + BSW_CANTP_TXNSDUNUM_16_23 + BSW_CANTP_TXNSDUNUM_24_31 )

/* FD frame DLC encode table size */
#define BSW_CANTP_CAN_DL_PTN_NUM        (65U)

/* Multiplier */
#define BSW_CANTP_u4MULTIPLIER_1000     (1000UL)

/* Division function(ceiling) */
#define BSW_CANTP_u4DIV_CEILING(dividend, divisor) \
    (((dividend) + ((divisor) - 1UL)) / (divisor))

/* MainFunction Period[Tick]    */
#define BSW_CANTP_MAINFUNCTION_PERIOD   ((BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_HIGH) ? BSW_BSWM_CS_TICKTIME_HIGH : BSW_BSWM_CS_TICKTIME_MID)

/* Convert function of Millisecond to MainFunction cycle count */
#define BSW_CANTP_u2MS2MAINFUNC_CYCLE(ms) \
    ((uint16)(BSW_CANTP_u4DIV_CEILING(((uint32)(ms) * BSW_CANTP_u4MULTIPLIER_1000), ((uint32)BSW_CANTP_MAINFUNCTION_PERIOD * (uint32)BSW_BSWM_CS_MPU_TICKTIME))))

/* The max number of RxNSdus    */
#define BSW_CANTP_MAX_RXNSDUNUM        (BSW_CANTP_RXNSDUNUM)

/* The max number of Connection Channels */
#define BSW_CANTP_MAX_CH_CNT            (BSW_CANTP_CFG_CHNUM)

/* Tx cancel function */
#define BSW_CANTP_TXCANCELFUNC          (BSW_CANTP_CFG_CANCEL_TX)

/* Unexpected Rx function */
#define BSW_CANTP_UNEXPECTEDRXFUNC      (BSW_CANTP_CFG_NEWRX_IN_LASTTX)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#if( BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE )
extern Bsw_CanTp_BSSTminType    bsw_cantp_stBSSTminTbl[BSW_CANTP_MAX_RXNSDUNUM];
#endif /* BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst uint8                       bsw_cantp_u1PaddingByte;
#if( BSW_CANTP_CFG_DYNBSSTMIN_ADOPT == BSW_CANTP_FIXED_BSSTMIN )
extern BswConst uint8                       bsw_cantp_u1FixedBS;
extern BswConst uint8                       bsw_cantp_u1FixedSTmin;
#endif  /* BSW_CANTP_CFG_DYNBSSTMIN_ADOPT == BSW_CANTP_FIXED_BSSTMIN */

#if( (BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE) || (BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE) )
extern BswConst uint16                      bsw_cantp_u2MaxRxNSduNum;
#endif /* ( (BSW_CANTP_CFG_CHANGE_RXPARAM == BSW_USE) || (BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE) ) */

extern BswConst uint8                       bsw_cantp_u1MaxChCnt;
extern BswConst uint16                      bsw_cantp_u2TimerCycleMax;
extern BswConst uint32                      bsw_cantp_u4MaxPduLength;

#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
extern BswConst uint8                       bsw_cantp_u1TxCancelFunc;
extern BswConst uint8                       bsw_cantp_u1UnexpectedRxFunc;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
extern BswConst uint16                      bsw_cantp_u2FcWaitTxPeriodTime;
extern BswConst uint16                      bsw_cantp_u2FcTxTimeout;
extern BswConst uint16                      bsw_cantp_u2CfTxTimeout;

#if( BSW_CANTP_CFG_FDSUPPORT == BSW_USE )
extern BswConst uint8                       bsw_cantp_u1OptimizedCanDlTbl[BSW_CANTP_CAN_DL_PTN_NUM];
#endif  /* BSW_CANTP_CFG_FDSUPPORT == BSW_USE */
extern BswConst uint8                       bsw_cantp_u1STminCycleTbl[BSW_CANTP_STMIN_RANGE_SIZE];
extern BswConst Bsw_CanTp_RxNSduCfgType     bsw_cantp_stRxNSduCfgTbl[BSW_CANTP_RXNSDUNUM];
extern BswConst Bsw_CanTp_TxNSduCfgType     bsw_cantp_stTxNSduCfgTbl[BSW_CANTP_TXNSDUNUM];
extern BswConst Bsw_CanTp_CfgType           bsw_cantp_stCfgTbl;

#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
extern BswConst Bsw_CanTp_RxNSduParamType   bsw_cantp_stRxNSduParamTbl[BSW_CANTP_CFG_RXPARAMPTNNUM];
extern BswConst Bsw_CanTp_TxNSduParamType   bsw_cantp_stTxNSduParamTbl[BSW_CANTP_CFG_TXPARAMPTNNUM];
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

#endif  /* BSW_CANTP_CONFIG_H */


/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/25                                             */
/*  v1-1-0          :2018/12/13                                             */
/*  v1-2-0          :2020/02/16                                             */
/*  v2-0-0          :2021/08/06                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
