/* 1.12.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Complex Driver : Date/Clock                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef DATE_CLK_H
#define DATE_CLK_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_CLK_H_MAJOR                         (1U)
#define DATE_CLK_H_MINOR                         (12U)
#define DATE_CLK_H_PATCH                         (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "rtime.h"
#include "date.h"

#include "date_clk_etm.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_CLK_HHMMSS_SWOT_LO                  (FALSE)
#define DATE_CLK_HHMMSS_SWOT_HI                  (TRUE)

#define DATE_CLK_ADJ_HHMMSS                      (0x01U)
#define DATE_CLK_ADJ_YYMMDD                      (0x02U)

#define DATE_CLK_FRT_UNK                         (0xffffffffU)
#define DATE_CLK_FRT_MAX                         (0x7fffffffU)

/* Elapsed Time Measurement */
#define DATE_CLK_ETM_UNK                         (0xffffffffU)
#define DATE_CLK_ETM_MAX                         (0x7b98a000U)    /* 24 days / 2073600 seconds             */
#define DATE_CLK_ETM_SEC                         (1000U)          /* res. : 1 second = 1000, 1 millisecond */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_DateclkTmrwkRqst(void);                            /* called by ecu_m_usrhk : u1_g_EcuMUsrhkWksrcTmrwk     */
void    vd_g_DateclkTmrwkInit(void);                            /* called by ecu_m_usrhk : vd_g_EcuMUsrhkStaTmrwk       */

void    vd_g_DateclkBonInit(void);                              /* called by ecu_m_usrhk : vd_g_EcuMUsrhkStaBonInit     */
void    vd_g_DateclkRstwkInit(void);                            /* called by ecu_m_usrhk : vd_g_EcuMUsrhkStaRstInit     */
                                                                /* called by ecu_m_usrhk : vd_g_EcuMUsrhkStaWkupInit    */
void    vd_g_DateclkImmdShtInit(void);                          /* called by ecu_m_usrhk : vd_g_EcuMUsrhkStaImmdShtInit */
U1      u1_g_DateclkShtLpmToTmrwk(void);                        /* called by ecu_m_usrhk : u1_g_EcuMUsrhkShtLpmToTmrwk  */

void    vd_g_DateclkMainTask(void);                             /* called by scheduler                                  */
U1      u1_g_DateclkShtdwnOk(void);                             /* called by bsw_m_cfg   : u1_g_BswMCfghkShtdwnchk2nd   */

/* ----------------------------------------------------------------------------------- */
/* Attention :                                                                         */
/* ----------------------------------------------------------------------------------- */
/* The returns of each Interface are always                                            */
/*                                                                                     */
/* u1_g_DateclkHhmmssSWOT / Return = DATE_CLK_HHMMSS_SWOT_LO                           */
/* u4_g_DateclkHhmmss24h  / Return = HHMMSS_UNKNWN                                     */
/* u4_g_DateclkYymmddwk   / Return = YYMMDDWK_UNKNWN                                   */
/* u1_g_DateclkAdjUnLock  / Return = FALSE                                             */
/*                                                                                     */
/* if those are invoded at                                                             */
/*                                                                                     */
/* ecu_m_usrhk : vd_g_EcuMUsrhkStaTmrwk                                                */
/* ecu_m_usrhk : u1_g_EcuMUsrhkWksrcTmrwk                                              */
/*                                                                                     */
/* ----------------------------------------------------------------------------------- */
U1      u1_g_DateclkHhmmssSWOT(void);
U4      u4_g_DateclkHhmmss24h(void);
U4      u4_g_DateclkYymmddwk(void);

U1      u1_g_DateclkAdjUnLock(const U1 u1_a_ADJ);               /* Return   : TRUE = unlocked else not                  */
                                                                /* u1_a_ADJ : DATE_CLK_ADJ_XXX bitfield                 */
void    vd_g_DateclkAdjLock(const U1 u1_a_ADJ);                 /* u1_a_ADJ : DATE_CLK_ADJ_XXX bitfield                 */
U1      u1_g_DateclkAdjHhmmss24h(const U4 u4_a_HHMMSS_24H);
U1      u1_g_DateclkAdjYymmdd(const U4 u4_a_YYMMDD);
void    vd_g_DateclkSet(void);

U1      u1_g_DateclkRtcSts(void);

/* ----------------------------------------------------------------------------------- */
/* Attention :                                                                         */
/* ----------------------------------------------------------------------------------- */
/* Following Interfaces can be invoded at                                              */
/*                                                                                     */
/* ecu_m_usrhk : vd_g_EcuMUsrhkStaTmrwk                                                */
/* ecu_m_usrhk : u1_g_EcuMUsrhkWksrcTmrwk                                              */
/*                                                                                     */
/* u4_g_DateclkFrt                                                                     */
/* vd_g_DateclkEtmStart                                                                */
/* u4_g_DateclkEtmElapsed                                                              */
/*                                                                                     */
/* ----------------------------------------------------------------------------------- */
U4      u4_g_DateclkFrt(void);

void    vd_g_DateclkEtmStart(const U1 u1_a_ETM_CH, const U4 u4_a_OFFSET);
U4      u4_g_DateclkEtmElapsed(const U1 u1_a_ETM_CH);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* DATE_CLK_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see date_clk.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
