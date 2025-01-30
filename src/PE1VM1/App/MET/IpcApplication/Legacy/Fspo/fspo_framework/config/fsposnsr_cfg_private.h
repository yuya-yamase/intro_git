/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  F-spo Sensor                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
#ifndef FSPOSNSR_CFG_H
#define FSPOSNSR_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FSPOSNSR_CFG_H_MAJOR                     (2)
#define FSPOSNSR_CFG_H_MINOR                     (1)
#define FSPOSNSR_CFG_H_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include File                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif

#include "veh_opemd.h"

#include "vardef.h"
#include "fspomgr.h"
#include "fsposnsr.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#define FSPOSNSR_COM_TIMEOUT                     (COM_TIMEOUT)
#define FSPOSNSR_COM_NO_RX                       (COM_NO_RX)

#define u1_FSPOSNSR_IG_ISON()                    (u1_g_VehopemdIgnOn())

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_FSPOSNSR_RXMSG_ENG1G17STS(time)       (u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G17_RXCH0   , \
                                                  (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR, \
                                                  (time)))
#define vd_FSPOSNSR_RXMSG_B_POM(sgnl)            ((void)Com_ReceiveSignal(ComConf_ComSignal_B_POM_3,  (sgnl)))
#define vd_FSPOSNSR_RXMSG_B_THOE(sgnl)           ((void)Com_ReceiveSignal(ComConf_ComSignal_B_THOE_3, (sgnl)))

#define u1_FSPOSNSR_RXMSG_VSC1G12STS()           ((U1)Com_GetIPDUStatus(MSG_VSC1G12_RXCH0))
#define vd_FSPOSNSR_RXMSG_V_GXHR0(sgnl)          ((void)Com_ReceiveSignal(ComConf_ComSignal_V_GXHR0,  (sgnl)))
#define vd_FSPOSNSR_RXMSG_V_GYHR0(sgnl)          ((void)Com_ReceiveSignal(ComConf_ComSignal_V_GYHR0,  (sgnl)))
#define vd_FSPOSNSR_RXMSG_VSC_GXF(sgnl)          ((void)Com_ReceiveSignal(ComConf_ComSignal_VSC_GXF,  (sgnl)))
#define vd_FSPOSNSR_RXMSG_VSC_GYF(sgnl)          ((void)Com_ReceiveSignal(ComConf_ComSignal_VSC_GYF,  (sgnl)))
#define vd_FSPOSNSR_RXMSG_VSC_GXIV(sgnl)         ((void)Com_ReceiveSignal(ComConf_ComSignal_VSC_GXIV, (sgnl)))
#define vd_FSPOSNSR_RXMSG_VSC_GYIV(sgnl)         ((void)Com_ReceiveSignal(ComConf_ComSignal_VSC_GYIV, (sgnl)))

#define u1_FSPOSNSR_RXMSG_VSC1G30STS()           ((U1)Com_GetIPDUStatus(MSG_VSC1G30_RXCH0))
#define vd_FSPOSNSR_RXMSG_FBKDRSYS(sgnl)         ((void)Com_ReceiveSignal(ComConf_ComSignal_FBKDRSYS, (sgnl)))
#define vd_FSPOSNSR_RXMSG_FBKDR_AX(sgnl)         ((void)Com_ReceiveSignal(ComConf_ComSignal_FBKDR_AX, (sgnl)))

#define vd_FSPOSNSR_EVTINC(a)                    (vd_g_FspomgrEventInc(a))      /* accumulated event                                 */

#define vd_FSPOSNSR_BRAMWRT_U2(sigsts)           (vd_g_Rim_WriteU2((U2)RIMID_U2_FSPO_SNSR_SIGSTS, (sigsts)))
#define u1_FSPOSNSR_BRAMREAD(sigsts)             (u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_FSPO_SNSR_SIGSTS, (sigsts)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* FSPOSNSR_PRM */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  fsposnsr.c                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
