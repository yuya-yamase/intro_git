/* bsw_cannm_a_osek_h_v2-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/OSEK/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANNM_A_OSEK_H
#define BSW_CANNM_A_OSEK_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*** OSEK-NM STATE NUMBER ***/
#define BSW_CANNM_A_OSEKNM_STATE_NUM        (8U)        /* Number of OSEK-NM states                         */
#define BSW_CANNM_A_ONM_STNM_OFF            (0U)        /* OSEK-NM state number:OFF        (0)       */
#define BSW_CANNM_A_ONM_STNM_RESETWAIT      (1U)        /* OSEK-NM state number:RESETWAIT  (1)       */
#define BSW_CANNM_A_ONM_STNM_NORMAL         (2U)        /* OSEK-NM state number:NORMAL     (2)       */
#define BSW_CANNM_A_ONM_STNM_TWBSNORMAL     (3U)        /* OSEK-NM state number:TWBSNORMAL (3)       */
#define BSW_CANNM_A_ONM_STNM_BUSSLEEP       (4U)        /* OSEK-NM state number:BUSSLEEP   (4)       */
#define BSW_CANNM_A_ONM_STNM_LIMPHOME       (5U)        /* OSEK-NM state number:LIMPHOME   (5)       */
#define BSW_CANNM_A_ONM_STNM_TWBSLMPHOM     (6U)        /* OSEK-NM state number:TWBSLMPHOM (6)       */
#define BSW_CANNM_A_ONM_STNM_INVALID        (7U)        /* OSEK-NM state number:INVALID    (7)       */

/*** OSEK-NM LOCAL STATE ****/
#define BSW_CANNM_A_ONM_NM_OFF              (0x11U)     /* OSEK-NM status:OFF                      */
#define BSW_CANNM_A_ONM_NM_RESETWAIT        (0x21U)     /* OSEK-NM status:RESETWAIT                */
#define BSW_CANNM_A_ONM_NM_NORMAL           (0x22U)     /* OSEK-NM status:NORMAL                   */
#define BSW_CANNM_A_ONM_NM_TWBSNORMAL       (0x41U)     /* OSEK-NM status:TWBSNORMAL               */
#define BSW_CANNM_A_ONM_NM_BUSSLEEP         (0x44U)     /* OSEK-NM status:BUSSLEEP                 */
#define BSW_CANNM_A_ONM_NM_LIMPHOME         (0x24U)     /* OSEK-NM status:LIMPHOME                 */
#define BSW_CANNM_A_ONM_NM_TWBSLIMPHOME     (0x42U)     /* OSEK-NM status:TWBSLIMPHOME             */
#define BSW_CANNM_A_ONM_NM_INVALID          (0x81U)     /* OSEK-NM status:INVALID                  */

#define BSW_CANNM_A_OSEKST_INVALID          (0x00U)     /* OSEK status:failure                        */
#define BSW_CANNM_A_OSEKST_OFF              (0x01U)     /* OSEK status:NMOff                       */
#define BSW_CANNM_A_OSEKST_RESET            (0x02U)     /* OSEK status:NMReset                     */
#define BSW_CANNM_A_OSEKST_NORMAL           (0x04U)     /* OSEK status:NMNormal                    */
#define BSW_CANNM_A_OSEKST_TWBSNORMAL       (0x08U)     /* OSEK status:NMTwbsNormal                */
#define BSW_CANNM_A_OSEKST_BUSSLEEP         (0x10U)     /* OSEK status:NMBusSleep                  */
#define BSW_CANNM_A_OSEKST_LIMPHOME         (0x20U)     /* OSEK status:NMLimpHome                  */
#define BSW_CANNM_A_OSEKST_TWBSLIMPHOME     (0x40U)     /* OSEK status:NMTwbsLimpHome              */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    BswU1  u1Local;
    BswU1  u1Osek;
} Bsw_CanNmA_STOsekStateTableType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void  bsw_cannm_a_oseknm_SetState(BswU1 u1NetID, BswU1 u1StateNum);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst Bsw_CanNmA_STOsekStateTableType  bsw_cannm_a_oseknm_stOsekStTbl[BSW_CANNM_A_OSEKNM_STATE_NUM];


#endif  /* BSW_CANNM_A_OSEK_H */
/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
