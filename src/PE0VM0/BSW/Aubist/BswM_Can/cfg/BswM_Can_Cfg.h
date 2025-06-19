/* bswm_can_cfg_h_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSWM/CAN/CFG/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_CAN_CFG_H
#define BSW_BSWM_CAN_CFG_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------*/
/* Register check                                   */
/*--------------------------------------------------*/
#define BSW_BSWM_CAN_CFG_RGSTCHK           (BSW_BSWM_CAN_RGSTCHK_NOTEVERY)
#define BSW_BSWM_CAN_CFG_WURGSTCHKSTART    (BSW_BSWM_CAN_WURGSTCHK_WAKEUP)

/*--------------------------------------------------*/
/* TxError Notification Function                    */
/*--------------------------------------------------*/
#define BSW_BSWM_CAN_CFG_FNC_TXERR_NTFY    (BSW_NOUSE)

/*--------------------------------------------------*/
/* Reception deadline monitoring period             */
/*--------------------------------------------------*/
#define BSW_BSWM_CAN_CFG_CH_DMPRD_0        (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_1        (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_2        (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_3        (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_4        (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_5        (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_6        (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_7        (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_8        (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_9        (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_10       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_11       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_12       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_13       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_14       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_15       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_16       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_17       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_18       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_19       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_20       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_21       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_22       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_23       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_24       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_25       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_26       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_27       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_28       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_29       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_30       (BSW_BSWM_CAN_DMPRD_NET_ALL)
#define BSW_BSWM_CAN_CFG_CH_DMPRD_31       (BSW_BSWM_CAN_DMPRD_NET_ALL)

/*------------------------------------------------------------------*/
/* Use/Nouse setting of the reception deadline monitoring function  */
/* when communication startup state only with cooperative bus Awake */
/*------------------------------------------------------------------*/
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_0      (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_1      (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_2      (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_3      (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_4      (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_5      (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_6      (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_7      (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_8      (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_9      (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_10     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_11     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_12     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_13     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_14     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_15     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_16     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_17     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_18     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_19     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_20     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_21     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_22     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_23     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_24     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_25     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_26     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_27     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_28     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_29     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_30     (BSW_NOUSE)
#define BSW_BSWM_CAN_CFG_CH_DMCOAWK_31     (BSW_NOUSE)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_BSWM_CAN_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/09/17                                             */
/*  v2-0-0          :2021/02/12                                             */
/*  v2-1-0          :2022/08/03                                             */
/*  v3-0-0          :2024/08/27                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
