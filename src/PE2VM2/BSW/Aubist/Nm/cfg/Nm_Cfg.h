/* nm_cfg_h_v3-0-0                                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NM/CFG/HEADER                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_NM_CFG_H
#define BSW_NM_CFG_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* Switch for enabling the Communication Control support */
#define BSW_NM_CFG_COM_CONTROL         (BSW_NOUSE)

/* Switch for enabling the Node Detection */
#define BSW_NM_CFG_NODE_DETECTION      (BSW_NOUSE)

/* Enable/Disable setting of NMUserData */
#define BSW_NM_CFG_USER_DATA           (BSW_NOUSE)

/* Switch for enabling the source node identifier */
#define BSW_NM_CFG_NODE_ID             (BSW_NOUSE)

/* Switch for enabling support of Passive Mode */
#define BSW_NM_CFG_PASSIVE_MODE        (BSW_NOUSE)

/* Switch for enabling the Sleep Synchronization */
#define BSW_NM_CFG_SLEEPSYNC           (BSW_NOUSE)

/* Switch for enabling the PNC Shutdown Synchronization */
#define BSW_NM_CFG_SYNC_PNC_SHUTDOWN   (BSW_NOUSE)

/* Switch for enabling the Request of Bus Synchronization */
#define BSW_NM_CFG_REQ_BUS_SYNC_CH0    (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH1    (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH2    (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH3    (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH4    (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH5    (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH6    (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH7    (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH8    (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH9    (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH10   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH11   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH12   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH13   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH14   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH15   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH16   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH17   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH18   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH19   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH20   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH21   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH22   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH23   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH24   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH25   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH26   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH27   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH28   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH29   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH30   (BSW_NOUSE)
#define BSW_NM_CFG_REQ_BUS_SYNC_CH31   (BSW_NOUSE)

/* Shutdown time for Synchronization Sleep(LSB:ms) */
#define BSW_NM_CFG_SHUTDOWN_TIME_CH0   (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH1   (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH2   (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH3   (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH4   (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH5   (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH6   (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH7   (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH8   (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH9   (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH10  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH11  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH12  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH13  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH14  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH15  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH16  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH17  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH18  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH19  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH20  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH21  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH22  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH23  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH24  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH25  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH26  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH27  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH28  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH29  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH30  (0U)
#define BSW_NM_CFG_SHUTDOWN_TIME_CH31  (0U)

#endif /* BSW_NM_CFG_H */


/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v2-0-0          :2022/01/06                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
