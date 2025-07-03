/* cansm_cfg_h_v3-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANSM/CFG/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANSM_CFG_H
#define BSW_CANSM_CFG_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/**************************/
/* General                */
/**************************/
/* Tx/Rx Indication State */
#define BSW_CANSM_CFG_TXRX_INDSTATE                  (BSW_NOUSE)

#define BSW_CANSM_CFG_ICOM                           (BSW_NOUSE)
#define BSW_CANSM_CFG_PNC                            (BSW_USE)
#define BSW_CANSM_CFG_SET_BAUDRATE                   (BSW_NOUSE)
#define BSW_CANSM_CFG_ECU_PASSIVE                    (BSW_NOUSE)

/**************************/
/* Channel                */
/**************************/
/* BusOff Recovery Time */
#define BSW_CANSM_CFG_BOR_TIME_L1_0                  (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_1                  (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_2                  (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_3                  (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_4                  (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_5                  (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_6                  (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_7                  (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_8                  (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_9                  (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_10                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_11                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_12                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_13                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_14                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_15                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_16                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_17                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_18                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_19                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_20                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_21                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_22                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_23                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_24                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_25                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_26                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_27                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_28                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_29                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_30                 (0U)
#define BSW_CANSM_CFG_BOR_TIME_L1_31                 (0U)

/* Send Lock Recovery Time */
#define BSW_CANSM_CFG_SNDLCK_RESTART_0               (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_1               (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_2               (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_3               (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_4               (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_5               (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_6               (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_7               (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_8               (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_9               (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_10              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_11              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_12              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_13              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_14              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_15              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_16              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_17              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_18              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_19              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_20              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_21              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_22              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_23              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_24              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_25              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_26              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_27              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_28              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_29              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_30              (0U)
#define BSW_CANSM_CFG_SNDLCK_RESTART_31              (0U)

/* BusOff Recovery Type */
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_0              (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_1              (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_2              (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_3              (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_4              (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_5              (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_6              (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_7              (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_8              (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_9              (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_10             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_11             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_12             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_13             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_14             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_15             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_16             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_17             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_18             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_19             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_20             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_21             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_22             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_23             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_24             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_25             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_26             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_27             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_28             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_29             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_30             (BSW_CANSM_BUSOFF_RESET)
#define BSW_CANSM_CFG_BUSOFF_RECOVERY_31             (BSW_CANSM_BUSOFF_RESET)

/* Transceiver Transition Wait Time */
#define BSW_CANSM_CFG_TRCV_WAITTIME_0                (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_1                (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_2                (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_3                (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_4                (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_5                (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_6                (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_7                (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_8                (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_9                (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_10               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_11               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_12               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_13               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_14               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_15               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_16               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_17               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_18               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_19               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_20               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_21               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_22               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_23               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_24               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_25               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_26               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_27               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_28               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_29               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_30               (0U)
#define BSW_CANSM_CFG_TRCV_WAITTIME_31               (0U)

/* Wait for CAN controller to start */
#define BSW_CANSM_CFG_CTRLSTART_WAIT_0               (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_1               (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_2               (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_3               (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_4               (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_5               (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_6               (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_7               (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_8               (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_9               (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_10              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_11              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_12              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_13              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_14              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_15              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_16              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_17              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_18              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_19              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_20              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_21              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_22              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_23              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_24              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_25              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_26              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_27              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_28              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_29              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_30              (BSW_NOUSE)
#define BSW_CANSM_CFG_CTRLSTART_WAIT_31              (BSW_NOUSE)


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

#endif /* BSW_CANSM_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/11/15                                             */
/*  v2-0-0          :2021/08/06                                             */
/*  v2-1-0          :2022/09/01                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
