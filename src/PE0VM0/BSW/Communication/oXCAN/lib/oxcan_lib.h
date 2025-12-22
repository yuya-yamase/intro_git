/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of CAN : oXCAN Library Interface Definitions                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXCAN_LIB_H
#define OXCAN_LIB_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_LIB_NMC_H_MAJOR                    (2U)
#define OXCAN_LIB_NMC_H_MINOR                    (0U)
#define OXCAN_LIB_NMC_H_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_LIB_RXD_H_MAJOR                    (2U)
#define OXCAN_LIB_RXD_H_MINOR                    (0U)
#define OXCAN_LIB_RXD_H_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_LIB_SYSEA_H_MAJOR                  (2U)
#define OXCAN_LIB_SYSEA_H_MINOR                  (0U)
#define OXCAN_LIB_SYSEA_H_PATCH                  (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_LIB_VCT_H_MAJOR                    (2U)
#define OXCAN_LIB_VCT_H_MINOR                    (0U)
#define OXCAN_LIB_VCT_H_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_LIB_WRH_H_MAJOR                    (2U)
#define OXCAN_LIB_WRH_H_MINOR                    (0U)
#define OXCAN_LIB_WRH_H_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_lib_cfg.h"

#if (OXCAN_LIB_CFG_EN_RXD == 1U)
#include "oxcan_rxd_def.h"
#endif /* #if (OXCAN_LIB_CFG_EN_RXD == 1U) */

#if (OXCAN_LIB_CFG_EN_WRH == 1U)
#include "oxcan_wrh_rqh.h"
#endif /* #if (OXCAN_LIB_CFG_EN_WRH == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_MAIN_TICK                          (BSW_BSWM_CS_CFG_TICKTIME_MID)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Return of u1_g_oXCANRxdEvcnt                                                                                                      */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Attention :                                                                                                                       */
/* OXCAN_RXD_EVC_INI is used as initial value at vd_g_oXCANRstInit and vd_g_oXCANWkupInit                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RXD_EVC_MAX                        (0x7fU)
#define OXCAN_RXD_EVC_UNK                        (0xffU)
#define OXCAN_RXD_EVC_INI                        (0x00U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Return of u1_g_oXCANRxdStat                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ./inc/Com.h:54:#define COM_NO_RX                       (0x01U) */
/* ./inc/Com.h:53:#define COM_TIMEOUT                     (0x02U) */
#define OXCAN_RXD_TOC_EN                         (0x10U)           /* TimeOut Count is ENabled    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_SYSEA_EAGR_1ST                     (0U)              /* Event Action Group 1st executed at vd_g_oXCANMainPreTask */
                                                                   /*                              or at vd_g_oXCANVomEvhk     */
#define OXCAN_SYSEA_EAGR_2ND                     (1U)              /* Event Action Group 2nd executed at vd_g_oXCANMainPosTask */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u2_OXCAN_RXTO_THRSH(MSEC)                ((U2)(((U4)(MSEC) + (U4)(OXCAN_MAIN_TICK - 1U)) / (U4)OXCAN_MAIN_TICK))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_LIB_CFG_EN_RXD == 1U)

U1      u1_g_oXCANRxdStat(const U2 u2_a_RXD, const U4 u4_a_SYS_CHK, const U2 u2_a_RXTO_THRSH);
                                                             /* u2_a_RXD : OXCAN_RXD_PDU_XXX defined in oxcan_rxd_pdu.h              */
                                                             /* Return   : COM_NO_RX, COM_TIMEOUT defined in Com.h                   */
U1      u1_g_oXCANRxdEvcnt(const U2 u2_a_RXD);
                                                             /* u2_a_RXD : OXCAN_RXD_PDU_XXX defined in oxcan_rxd_pdu.h              */

#endif /* #if (OXCAN_LIB_CFG_EN_RXD == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_LIB_CFG_EN_VCT == 1U)

U4      u4_g_oXCANvCtWrqRx(void);                            /* Return : OXCAN_SYS_### defined oxcan_sys_def.h                       */

#endif /* #if (OXCAN_LIB_CFG_EN_VCT == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_LIB_CFG_EN_WRH == 1U)

void    vd_g_oXCANWrhReqHch(const U1 u1_a_HCH, const U4 u4_a_REQ);           /* u4_a_REQ : see oxcan_sys_def.h OXCAN_SYS_NET         */
U4      u4_g_oXCANWrhWrqAct(void);                                           /* Return   : see oxcan_wrh_rqh.h OXCAN_WRH_RQBIT_XXX   */

#endif /* #if (OXCAN_LIB_CFG_EN_WRH == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((defined(OXCAN_C_MAJOR)            ) || \
     (defined(OXCAN_NMC_C_MAJOR)        ) || \
     (defined(OXCAN_RXD_C_MAJOR)        ) || \
     (defined(OXCAN_SYSEA_C_MAJOR)      ) || \
     (defined(OXCAN_WRH_C_MAJOR)        ) || \
     (defined(OXCAN_AUBIF_COM_C_MAJOR)  ) || \
     (defined(OXCAN_AUBIF_CANNM_C_MAJOR)) || \
     (defined(OXCAN_AUBIF_VCAN_C_MAJOR) ))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_LIB_CFG_EN_NMC == 1)

void    vd_g_oXCANNmcInit(void);
void    vd_g_oXCANNmcRxAck(const U1 u1_a_CH, const U1 * const u1_ap_SDU_RX, const U4 u4_a_DLEN);
void    vd_g_oXCANNmcCoord(void);

#endif /* #if (OXCAN_LIB_CFG_EN_NMC == 1) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_LIB_CFG_EN_RXD == 1U)

void    vd_g_oXCANRxdInit(void);
void    vd_g_oXCANRxdSysEvhk(const U4 u4_a_SYS_ACT);
void    vd_g_oXCANRxdMainTask(const U4 u4_a_SYS_ACT);
void    vd_g_oXCANRxdPduAck(const U1 u1_a_GR, const U2 u2_a_PDU_ACK);

#endif /* #if (OXCAN_LIB_CFG_EN_RXD == 1) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_LIB_CFG_EN_SEA == 1)

void    vd_g_oXCANSysEaInit(void);
void    vd_g_oXCANSysEaSysEvhk(const U4 u4_a_SYS_ACT);
void    vd_g_oXCANSysEaTimElpsd(const U4 u4_a_SYS_ACT);
void    vd_g_oXCANSysEaEvAct(const U1 u1_a_EAGR);

#endif /* #if (OXCAN_LIB_CFG_EN_SEA == 1) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_LIB_CFG_EN_VCT == 1U)

void    vd_g_oXCANvCtInit(void);
void    vd_g_oXCANvCtMainRx(void);
void    vd_g_oXCANvCtMainTx(const U4 u4_a_SYSBIT);
U4      u4_g_oXCANvCtWrqbyCt(const U1 u1_a_CTRLR, const U1 u1_a_CLR);
void    vd_g_oXCANvCtWrqDet(const U1 u1_a_CTRLR, const U1 u1_a_ENA);

#endif /* #if (OXCAN_LIB_CFG_EN_VCT == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_LIB_CFG_EN_WRH == 1U)

void    vd_g_oXCANWrhInit(const U1 u1_a_RST_INIT);
void    vd_g_oXCANWrhMainTask(const U4 u4_a_SYS_ACT);
U1      u1_g_oXCANWrhShtdwnOk(void);

#endif /* #if (OXCAN_LIB_CFG_EN_WRH == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#endif /* #if ((defined(OXCAN_C_MAJOR)  ) ||  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* OXCAN_LIB_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  oxcan_nmc.c, oxcan_rxd.c and oxcan_sysea.c, oxcan_vct.c, oxcan_wrh.c                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
