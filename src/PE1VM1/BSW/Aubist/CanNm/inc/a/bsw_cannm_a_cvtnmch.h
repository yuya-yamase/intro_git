/* bsw_cannm_a_cvtnmch_h_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/CVTNMCH/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANNM_A_CVTNMCH_H
#define BSW_CANNM_A_CVTNMCH_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*** CVT-NM STATUS ***/
#define BSW_CANNM_A_CVTST_POW_ON_INIT       (0x11U)     /* CVT-NM status:Waiting for driver initialization after initialization            */
#define BSW_CANNM_A_CVTST_POW_ON_WAIT       (0x12U)     /* CVT-NM status:Wait for start after initialization                      */
#define BSW_CANNM_A_CVTST_POW_ON_SLEEP      (0x14U)     /* CVT-NM status:Waiting for bus sleep after initialization              */
#define BSW_CANNM_A_CVTST_RUN               (0x21U)     /* CVT-NM status:Normal operation                              */
#define BSW_CANNM_A_CVTST_SLEEPWAIT         (0x22U)     /* CVT-NM status:Prepare bus-sleep                      */
#define BSW_CANNM_A_CVTST_SLEEP             (0x41U)     /* CVT-NM status:Bus-sleep                          */
#define BSW_CANNM_A_CVTST_WAKE_UP_WAIT      (0x44U)     /* CVT-NM status:Waiting for start after bus wake-up          */
#define BSW_CANNM_A_CVTST_INVALID           (0x81U)     /* CVT-NM status:Invalid                                  */

#define BSW_CANNM_A_WKUPINIT_CLR            (0x00U)     /* WKUP,INIT state:Cleared               */
#define BSW_CANNM_A_WKUPINIT_INIT           (0x10U)     /* WKUP,INIT state:INIT bit           */
#define BSW_CANNM_A_WKUPINIT_WKUP           (0x80U)     /* WKUP,INIT state:WKUP Bit           */
#define BSW_CANNM_A_WKUPINIT_WKUPINIT       (0x90U)     /* WKUP,INIT state:WKUP,INIT bit      */
#define BSW_CANNM_A_WKUPINIT_CLR_MIRR       (0xffU)     /* WKUP,INIT state:Clear inverted value         */
#define BSW_CANNM_A_WKUPINIT_INIT_MIRR      (0xefU)     /* WKUP,INIT state:INIT bit inverted value     */
#define BSW_CANNM_A_WKUPINIT_WKUP_MIRR      (0x7fU)     /* WKUP,INIT state:WKUP bit inverted value     */
#define BSW_CANNM_A_WKUPINIT_WUINIT_MRR     (0x6fU)     /* WKUP,INIT state:WKUP, INIT bit inverted value*/

/* Control message transmission enable/disable */
#define BSW_CANNM_A_u1IPDUSND_DISABLE       ((BswU1)0x1FU)       /* Disable Transmission              */
#define BSW_CANNM_A_u1IPDUSND_EN_EV         ((BswU1)0x2EU)       /* Enable event transmission      */
#define BSW_CANNM_A_u1IPDUSND_EN_ALL        ((BswU1)0x4CU)       /* Allow event + periodic transmission */

/* Unit internal public definition */
#define BSW_CANNM_A_WKUPFCT_NONE            (0xe1U)     /* WakeupFact at startup:None              */
#define BSW_CANNM_A_WKUPFCT_EXIST           (0xd2U)     /* WakeupFact at startup:Exist              */
#define BSW_CANNM_A_BWKIND_NORMAL           (0xe1U)     /* Enable TransmissionTiming at BusWakeup:Normal operation */
#define BSW_CANNM_A_BWKIND_ASSOON           (0xd2U)     /* Enable TransmissionTiming at BusWakeup:Immediate */

#define BSW_CANNM_A_u1CHPW_ON               ((BswU1)0xE1U)    /* Channel power supply:Satisfaction   */
#define BSW_CANNM_A_u1CHPW_OFF              ((BswU1)0xF0U)    /* Channel power supply:Dissatisfaction */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
BswU2 bsw_cannm_a_cvtnm_GetCvtEvent(BswU1 u1NetID);
void  bsw_cannm_a_cvtnm_TransCvtEvt(BswU1 u1NetID, BswU2 u2EventNo);
void  bsw_cannm_a_cvtnm_ResetInit(BswU1 u1NetID);
void  bsw_cannm_a_cvtnm_MpuWakeUpInit(BswU1 u1NetID);
void  bsw_cannm_a_cvtnm_ClrWkupIntBit(BswU1 u1NetID);
BswU1 bsw_cannm_a_cvtnm_GetWkupIntBit(BswU1 u1NetID);
BswU1 bsw_cannm_a_cvtnm_GetCvtStatus(BswU1 u1NetID);
void  bsw_cannm_a_cvtnm_SetState(BswU1 u1NetID, BswU1 u1State);
void  bsw_cannm_a_cvtnm_SetComMsgSt(BswU1 u1NetID, BswU1 u1ComSt );
uint8 bsw_cannm_a_cvtnm_GetIPDUState( NetworkHandleType nmChannelHandle );
void  bsw_cannm_a_cvtnm_CheckRam(BswU1 u1NetID);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANNM_A_CVTNMCH_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/03/16                                             */
/*  v2-0-0          :2021/12/03                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
