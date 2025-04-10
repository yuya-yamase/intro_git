/* bsw_com_rx_h_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COM/RX/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_COM_RX_H
#define BSW_COM_RX_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_COM_u2JITTER_IMM_COUNT     ((BswU2)1U)

#define BSW_COM_RXMSG_MASK             (0x04U)
#define BSW_COM_PRESTORE_MASK          (0x08U)

#define BSW_COM_u1RXIPDU_NONE          ((BswU1)0U)
#define BSW_COM_u1RXIPDU_START         ((BswU1)1U)
#define BSW_COM_u1RXIPDU_STOP          ((BswU1)2U)
#define BSW_COM_u1RXIPDU_STOP_CLRTIME  ((BswU1)3U)
#define BSW_COM_u1RXIPDU_CLRTIME       ((BswU1)4U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                bsw_com_rx_InitTimeOutSub( Bsw_Com_NetworkType u1Network );
void                bsw_com_rx_InitComRxStat( NetworkHandleType Network, BswU4* ptIpduGrpStat );
void                bsw_com_rx_ShutdownComRxStat( void );
BswU1               bsw_com_rx_GetPncIpduRxSt( NetworkHandleType Network, PduIdType u2PduId );
BswU1               bsw_com_rx_GetPncIpduRxStNone( NetworkHandleType Network, PduIdType u2PduId );

/* Unit internal public definition */
void                bsw_com_rx_InitPncRxStat( void );
void                bsw_com_rx_InitPncRxStatNone( void );
void                bsw_com_rx_ShutdownPncRxSt( void );
void                bsw_com_rx_ShutdownPncRxStNone( void );
BswU1               bsw_com_rx_GetPncIpduRxDMSt( NetworkHandleType Network, PduIdType u2PduId );
BswU1               bsw_com_rx_GetPncIpduRxDMStNone( NetworkHandleType Network, PduIdType u2PduId );
void                bsw_com_rx_VPSRxIndicationNone( PduIdType PduId );
void                bsw_com_rx_UpdateRxStatus( BswU1 u1Ch );
void                bsw_com_rx_UpdateRxStatusPnc( BswU1 u1Ch );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern  BswU4       bsw_com_rx_u4RxIpduGrpReqStat[][BSW_COM_SYSSTATTBLNUM]; /* Receive I-PDU group state (Request)      */
extern  BswU4       bsw_com_rx_u4RxIpduGrpStat[][BSW_COM_SYSSTATTBLNUM];    /* Receive I-PDU group state                */
extern  BswU4       bsw_com_rx_u4PncRxIpduGrReqStat[][BSW_COM_PNC_REQNUM];  /* PNC receive I-PDU group state (Request)  */
extern  BswU4       bsw_com_rx_u4PncRxIpduGrStat[][BSW_COM_PNC_REQNUM];     /* PNC receive I-PDU group state            */

/* Unit internal public definition */
extern  PduIdType   bsw_com_rx_u2FireHandler[];                              /* Periodic transmission time elapsed message ID     */
extern  BswU2       bsw_com_rx_u2DLine[];                                    /* Timeout timer                                     */
extern  BswU4       bsw_com_rx_u4RxDmReqStat[][BSW_COM_SYSSTATTBLNUM];       /* Receive disconnection monitoring state (Request)  */
extern  BswU4       bsw_com_rx_u4RxDmStat[][BSW_COM_SYSSTATTBLNUM];          /* Receive disconnection monitoring state            */
extern  BswU4       bsw_com_rx_u4WkupMskSetReqStat[][BSW_COM_SYSSTATTBLNUM]; /* WAKEUP_MASK setting state(request)                */
extern  BswU4       bsw_com_rx_u4WkupMskSetStat[][BSW_COM_SYSSTATTBLNUM];    /* WAKEUP_MASK setting state                         */
extern  BswU4       bsw_com_rx_u4PncRxDmReqStat[][BSW_COM_PNC_REQNUM];       /* PNC Receive disconnection monitoring state (Request) */
extern  BswU4       bsw_com_rx_u4PncRxDmStat[][BSW_COM_PNC_REQNUM];          /* PNC Receive disconnection monitoring state           */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern  BswU1           (* BswConst bsw_com_rom_ptGetPncIpduRxStFunc)( NetworkHandleType Network, PduIdType u2PduId );

/* Unit internal public definition */
extern BswConst Bsw_Com_NetInfoType       bsw_com_stNetInfoRxMsgTbl[];       /* Received message ID index table         */
extern BswConst Bsw_Com_TickTimeType      bsw_com_u2PwonMsk[];               /* PWON_MASK table                         */
extern BswConst Bsw_Com_TickTimeType      bsw_com_u2WakeupMsk[];             /* WKUP_MASK table                         */
extern BswConst Bsw_Com_TickTimeType      bsw_com_u2PnconMsk[];              /* PNCON_MASK table                        */
extern BswConst BswU1                     bsw_com_rom_u1RxTimeOutMskStop[];  /* Use/Unuse table of the function to stop PWON_MASK measurement in progress by Rx message */

extern  Std_ReturnType  (* BswConst bsw_com_rom_ptAlvCntrFuncRx[])( PduIdType u2PduId, BswConstR PduInfoType *ptCanRcvMsg, BswU1 *ptPreviousCounter, BswU1 *ptReceivedCounter );
extern  void            (* BswConst bsw_com_rom_ptInitPncRxStatFunc)( void );
extern  void            (* BswConst bsw_com_rom_ptDeInitPncRxStFunc)( void );
extern  BswU1           (* BswConst bsw_com_rom_ptGetPncIpduRxDMStFunc)( NetworkHandleType Network, PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptVpsRxIndictionFunc)( PduIdType PduId );
extern  void            (* BswConst bsw_com_rom_ptUpdateRxStsFunc[])( BswU1 u1Ch );

#endif /* BSW_COM_RX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-1-0          :2022/11/18                                             */
/*  v3-0-0          :2024/11/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
