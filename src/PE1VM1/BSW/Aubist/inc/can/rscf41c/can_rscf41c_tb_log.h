/* can_rscf41c_tb_log_h_v3-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF41C/TB/LOGICAL/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF41C_TB_LOG_H
#define     CAN_RSCF41C_TB_LOG_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_TB_HRHNUM \
   (  CAN_CFG_HRHNUM_0 \
    + CAN_CFG_HRHNUM_1 \
    + CAN_CFG_HRHNUM_2 \
    + CAN_CFG_HRHNUM_3 \
    + CAN_CFG_HRHNUM_4 \
    + CAN_CFG_HRHNUM_5 \
    + CAN_CFG_HRHNUM_6 \
    + CAN_CFG_HRHNUM_7 )

#define CAN_TB_HRHNUM_MAX               ( CAN_TB_HRHNUM )

#define CAN_TB_HTHNUM \
   (  CAN_CFG_HTHNUM_0 \
    + CAN_CFG_HTHNUM_1 \
    + CAN_CFG_HTHNUM_2 \
    + CAN_CFG_HTHNUM_3 \
    + CAN_CFG_HTHNUM_4 \
    + CAN_CFG_HTHNUM_5 \
    + CAN_CFG_HTHNUM_6 \
    + CAN_CFG_HTHNUM_7 )

#define CAN_TB_HTHNUM_MAX               ( CAN_TB_HTHNUM )

#define CAN_TB_HOHNUM                   ( CAN_TB_HRHNUM + CAN_TB_HTHNUM )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint8  u1ControllerActivation;
    uint8  u1ControllerUse;
    uint8  u1BusoffProcessing;
    uint8  u1BusoffRecovery;
} CanTbControllerConfigType;

typedef struct
{
    uint16 u2HthOffset;
    uint16 u2HrhOffset;
    uint8  u1HthNum;
    uint8  u1HrhNum;
    uint8  u1HthMbOffset;
    uint8  u1HrhMbOffset;
} CanTbHohMbAllocType;

typedef struct
{
    uint8  u1UTxMbOffset;
    uint8  u1UTxMbNum;
} CanTbUTxMbAllocType;

typedef struct
{
    uint8  u1ControllerID;
    uint8  u1MboxNo;
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
extern CanConst CanTbControllerConfigType Can_tb_stControllerCfgTbl[ CAN_CFG_CONTROLLERNUM_MAX ];

extern CanConst CanTbHohMbAllocType Can_tb_stHohMbAlloc[ CAN_CFG_CONTROLLERNUM_MAX ];

#if (CAN_CFG_TRANSMIT == CAN_USE)
extern CanConst CanHohCfgType Can_stHohCfgTbl[ CAN_TB_HOHNUM ];
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */

extern CanConst CanHohCfgType * CanConst Can_tb_ptHohCfgTbl;

extern CanConst uint8 Can_tb_u1RegChkNum;

extern CanConst uint8 Can_tb_u1ControllerNumMax;

extern CanConst uint16 Can_tb_u2HrhNumMax;

extern CanConst uint16 Can_tb_u2HthNumMax;

extern CanConst CanTbUTxMbAllocType Can_tb_stUTxMbAlloc[ CAN_CFG_CONTROLLERNUM_MAX ];


#endif  /* CAN_RSCF41C_TB_LOG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-1         :2022/03/09                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
