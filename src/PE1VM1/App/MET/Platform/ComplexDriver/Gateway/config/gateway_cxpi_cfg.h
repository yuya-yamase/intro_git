/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota CXPI Gateway                                                                                                              */
/*===================================================================================================================================*/

#ifndef GATEWAY_CXPI_CFG_H
#define GATEWAY_CXPI_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GATEWAY_CXPI_CFG_H_MAJOR                     (1)
#define GATEWAY_CXPI_CFG_H_MINOR                     (0)
#define GATEWAY_CXPI_CFG_H_PATCH                     (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gateway_cxpi.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif
#include "vardef.h"
/* #include "hmimcst.h" */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GATEWAY_CXPICFG_APP_TASK                          (10U)                       /* Task Cycle                    */

#define GATEWAY_CXPICFG_MSG_CXSWS1S01                     (1U)                        /* Message CXSWS1S01             */
#define GATEWAY_CXPICFG_MSG_CXSWS1S02                     (2U)                        /* Message CXSWS1S02             */
#define GATEWAY_CXPICFG_MSG_CXSWS1S03                     (3U)                        /* Message CXSWS1S03             */
#define GATEWAY_CXPICFG_MSG_CXSWS1S04                     (4U)                        /* Message CXSWS1S04             */

/** MET1S44 **/
#define GATEWAY_CXPICFG_CXPICOM_NORM                      (0U)                        /* Normal                        */
#define GATEWAY_CXPICFG_CXPICOM_ERR                       (1U)                        /* Com Error                     */

#define GATEWAY_CXPICFG_ERRCHKTASK_NUM                    (1U)                        /*  Cxpi Err Check Number        */
#define GATEWAY_CXPICFG_PRETASK_CXPIERRCHK                (0U)                        /*  Cxpi Err Check               */

#define GATEWAY_CXPICFG_WRTMSG_NUM                        (1U)                       /*  Gateway Write Message Number */
#define GATEWAY_CXPICFG_WRTMSG_CXMET1S01                  (0U)                        /*  CXMET1S01                    */
#define GATEWAY_CXPICFG_WRTMSG_CXMET1S03                  (1U)                        /*  CXMET1S03                    */
#define GATEWAY_CXPICFG_WRTMSG_CXMET1S04                  (2U)                        /*  CXMET1S04                    */
#define GATEWAY_CXPICFG_WRTMSG_CXMET1S05                  (3U)                        /*  CXMET1S05                    */
#define GATEWAY_CXPICFG_WRTMSG_CXMET1S06                  (4U)                        /*  CXMET1S06                    */
#define GATEWAY_CXPICFG_WRTMSG_MET1S41                    (5U)                        /*  MET1S41                      */
#define GATEWAY_CXPICFG_WRTMSG_MET1S43                    (6U)                        /*  MET1S43                      */
#define GATEWAY_CXPICFG_WRTMSG_MET1S44                    (7U)                        /*  MET1S44                      */
#define GATEWAY_CXPICFG_WRTMSG_MET1S45                    (8U)                        /*  MET1S45                      */
#define GATEWAY_CXPICFG_WRTMSG_CMB1S05                    (9U)                        /*  CMB1S05                      */
#define GATEWAY_CXPICFG_WRTMSG_CMB1S06                    (10U)                       /*  CMB1S06                      */

#define u2_GATEWAY_RXTO_THRSH                             u2_OXCAN_RXTO_THRSH(3000U)  /* RX Timeout 3000ms             */
#define u2_GATEWAY_BDB1S22_THRSH                          u2_OXCAN_RXTO_THRSH(2000U)  /* RX Timeout 2000ms             */
#define u2_GATEWAY_WIP1S01_THRSH                          u2_OXCAN_RXTO_THRSH(2000U)  /* RX Timeout 2000ms             */

/* #define GATEWAY_CXPICFG_T_LOGI_SUP  */                                             /* Comment out when unsupported  */
/* #define GATEWAY_CXPICFG_EL_SENS_SUP */                                             /* Comment out when unsupported  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_GatewayCxpiCfgInit(void);

#endif /* GATEWAY_CXPI_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History : see gateway_cxpi_cfg.c                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
