/* bsw_bswm_cs_status_h_v2-2-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/STATUS/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_BSWM_CS_STATUS_H
#define     BSW_BSWM_CS_STATUS_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_CS_u2PVTST_RUN             ((BswU2)0xFE01U) /* BSWM/CS operation state : Normal operation      */
#define BSW_BSWM_CS_u2PVTST_UNINIT          ((BswU2)0xFD02U) /* BSWM/CS operation state : Uninitialized         */
#define BSW_BSWM_CS_u2PVTST_FATAL           ((BswU2)0x5580U) /* BSWM/CS operation state : failure               */

#define BSW_BSWM_CS_u1CLOCKPROV_ON          ((BswU1)0x0FU)   /* Clock supply log:Exist                          */
#define BSW_BSWM_CS_u1CLOCKPROV_OFF         ((BswU1)0x1EU)   /* Clock supply log:None                           */

#define BSW_BSWM_CS_u1RESULT_OK             ((BswU1)0U)      /* Result:Normal                                   */
#define BSW_BSWM_CS_u1RESULT_NG             ((BswU1)1U)      /* Result:failure                                  */

#define BSW_BSWM_CS_u1TMGTYP_NORMAL         ((BswU1)0x00U)   /* processing timing type:Normal condition         */
#define BSW_BSWM_CS_u1TMGTYP_WAKEUP         ((BswU1)0x01U)   /* processing timing type:At wake-up               */

#define BSW_BSWM_CS_PNCMAXNUM               (64U)                           /* Maximum number of PNCs           */
#define BSW_BSWM_CS_PNC_REQNUM              (BSW_BSWM_CS_PNCMAXNUM >> 5U)   /* Number of 4 bytes for PNC (bit)  */
#define BSW_BSWM_CS_u4PNCSTAT_NONE          (0x00000000UL)
#define BSW_BSWM_CS_u4PNCSTAT_ALLON         (0xFFFFFFFFUL)

#define BSW_BSWM_CS_u2PNCVECT_INDEX0        ((BswU2)0U)
#define BSW_BSWM_CS_u2PNCVECT_INDEX1        ((BswU2)1U)

#define BSW_BSWM_CS_u1INDEX_0               ((BswU1)0U)      /* Index for array access                          */
#define BSW_BSWM_CS_u1INDEX_1               ((BswU1)1U)      /* Index for array access                          */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
BswU1 bsw_bswm_cs_st_ChkU2Dat( BswU2 u2Val );
void  bsw_bswm_cs_st_CtrlPrvClkTiming( void );
void  bsw_bswm_cs_st_NotifyPrvClkWkup( BswU1 u1TmgTyp );
void  bsw_bswm_cs_st_UpdPncIpduStat( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern BswU2    bsw_bswm_cs_st_u2CSStatus;
extern BswU1    bsw_bswm_cs_st_u1Clock;

extern BswU1    bsw_bswm_cs_st_u1IpduGrpVect[];
extern BswU1    bsw_bswm_cs_st_u1DmIpduGrpVect[];
extern BswU1    bsw_bswm_cs_st_u1WkupIpduGrVct[];

extern BswU4    bsw_bswm_cs_st_u4PncIpduGrpVect[];
extern BswU4    bsw_bswm_cs_st_u4PncDmIpduGrVct[];
extern BswU4    bsw_bswm_cs_st_u4PncTxStatusVct[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1     bsw_bswm_cs_st_u1IpduGrpVctSz;
extern BswConst BswU1     bsw_bswm_cs_st_u1PncIpduRx[];

#endif  /* BSW_BSWM_CS_STATUS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/09/12                                             */
/*  v2-0-0          :2021/12/09                                             */
/*  v2-1-0          :2022/06/08                                             */
/*  v2-2-0          :2023/05/09                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
