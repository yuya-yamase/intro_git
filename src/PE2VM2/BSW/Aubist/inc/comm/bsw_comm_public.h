/* bsw_comm_public_h_v3-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COMM/PUBLIC/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_COMM_PUBLIC_H
#define BSW_COMM_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* ComM Initialization State */
#define BSW_COMM_UNINIT                             (0U)
#define BSW_COMM_INIT                               (1U)

/* ComM Mode */
#define BSW_COMM_NO_COMMUNICATION                   (0U)
#define BSW_COMM_SILENT_COMMUNICATION               (1U)
#define BSW_COMM_FULL_COMMUNICATION                 (2U)
#define BSW_COMM_FULL_COM_WITH_WKUP_REQ             (3U)

/* ComM State */
#define BSW_COMM_NO_COM_NO_PENDING_REQUEST              (0U)
#define BSW_COMM_NO_COM_REQUEST_PENDING             (1U)
#define BSW_COMM_FULL_COM_NETWORK_REQUESTED              (2U)
#define BSW_COMM_FULL_COM_READY_SLEEP               (3U)
#define BSW_COMM_SILENT_COM                         (4U)
#define BSW_COMM_INVALID_COM                        (5U)

/* ComM PNC State */
#define BSW_COMM_PNC_REQUESTED                      (0U)
#define BSW_COMM_PNC_READY_SLEEP                    (1U)
#define BSW_COMM_PNC_PREPARE_SLEEP                  (2U)
#define BSW_COMM_PNC_NO_COMMUNICATION               (3U)

/* Channel Power Supply Judgment */
#define BSW_COMM_PWSUPPLY_OFF                       (0U)
#define BSW_COMM_PWSUPPLY_ON                        (1U)

/* Channel Driving State */
#define BSW_COMM_DRVST_STOP                         (0U)
#define BSW_COMM_DRVST_START                        (1U)

/* Power Supply State */
#define BSW_COMM_PWSTAT_NONE                        (0x00000000UL)
#define BSW_COMM_PWSTAT_BAT                         (0x00000001UL)
#define BSW_COMM_PWSTAT_ACC                         (0x00000002UL)
#define BSW_COMM_PWSTAT_IG                          (0x00000004UL)
#define BSW_COMM_PWSTAT_USER1                       (0x00000008UL)
#define BSW_COMM_PWSTAT_USER2                       (0x00000010UL)
#define BSW_COMM_PWSTAT_USER3                       (0x00000020UL)
#define BSW_COMM_PWSTAT_USER4                       (0x00000040UL)
#define BSW_COMM_PWSTAT_USER5                       (0x00000080UL)
#define BSW_COMM_PWSTAT_USER6                       (0x00000100UL)
#define BSW_COMM_PWSTAT_USER7                       (0x00000200UL)
#define BSW_COMM_PWSTAT_USER8                       (0x00000400UL)
#define BSW_COMM_PWSTAT_USER9                       (0x00000800UL)
#define BSW_COMM_PWSTAT_USER10                      (0x00001000UL)
#define BSW_COMM_PWSTAT_USER11                      (0x00002000UL)
#define BSW_COMM_PWSTAT_USER12                      (0x00004000UL)
#define BSW_COMM_PWSTAT_USER13                      (0x00008000UL)
#define BSW_COMM_PWSTAT_USER14                      (0x00010000UL)
#define BSW_COMM_PWSTAT_USER15                      (0x00020000UL)
#define BSW_COMM_PWSTAT_USER16                      (0x00040000UL)
#define BSW_COMM_PWSTAT_USER17                      (0x00080000UL)
#define BSW_COMM_PWSTAT_USER18                      (0x00100000UL)
#define BSW_COMM_PWSTAT_USER19                      (0x00200000UL)
#define BSW_COMM_PWSTAT_USER20                      (0x00400000UL)
#define BSW_COMM_PWSTAT_USER21                      (0x00800000UL)
#define BSW_COMM_PWSTAT_USER22                      (0x01000000UL)
#define BSW_COMM_PWSTAT_USER23                      (0x02000000UL)
#define BSW_COMM_PWSTAT_USER24                      (0x04000000UL)
#define BSW_COMM_PWSTAT_USER25                      (0x08000000UL)
#define BSW_COMM_PWSTAT_USER26                      (0x10000000UL)
#define BSW_COMM_PWSTAT_USER27                      (0x20000000UL)
#define BSW_COMM_PWSTAT_USER28                      (0x40000000UL)
#define BSW_COMM_PWSTAT_USER29                      (0x80000000UL)
#define BSW_COMM_PWSTAT_USER30                      (0x00000001UL)
#define BSW_COMM_PWSTAT_USER31                      (0x00000002UL)
#define BSW_COMM_PWSTAT_USER32                      (0x00000004UL)
#define BSW_COMM_PWSTAT_USER33                      (0x00000008UL)
#define BSW_COMM_PWSTAT_USER34                      (0x00000010UL)
#define BSW_COMM_PWSTAT_USER35                      (0x00000020UL)
#define BSW_COMM_PWSTAT_USER36                      (0x00000040UL)
#define BSW_COMM_PWSTAT_USER37                      (0x00000080UL)
#define BSW_COMM_PWSTAT_USER38                      (0x00000100UL)
#define BSW_COMM_PWSTAT_USER39                      (0x00000200UL)
#define BSW_COMM_PWSTAT_USER40                      (0x00000400UL)
#define BSW_COMM_PWSTAT_USER41                      (0x00000800UL)
#define BSW_COMM_PWSTAT_USER42                      (0x00001000UL)
#define BSW_COMM_PWSTAT_USER43                      (0x00002000UL)
#define BSW_COMM_PWSTAT_USER44                      (0x00004000UL)
#define BSW_COMM_PWSTAT_USER45                      (0x00008000UL)
#define BSW_COMM_PWSTAT_USER46                      (0x00010000UL)
#define BSW_COMM_PWSTAT_USER47                      (0x00020000UL)
#define BSW_COMM_PWSTAT_USER48                      (0x00040000UL)
#define BSW_COMM_PWSTAT_USER49                      (0x00080000UL)
#define BSW_COMM_PWSTAT_USER50                      (0x00100000UL)
#define BSW_COMM_PWSTAT_USER51                      (0x00200000UL)
#define BSW_COMM_PWSTAT_USER52                      (0x00400000UL)
#define BSW_COMM_PWSTAT_USER53                      (0x00800000UL)
#define BSW_COMM_PWSTAT_USER54                      (0x01000000UL)
#define BSW_COMM_PWSTAT_USER55                      (0x02000000UL)
#define BSW_COMM_PWSTAT_USER56                      (0x04000000UL)
#define BSW_COMM_PWSTAT_USER57                      (0x08000000UL)
#define BSW_COMM_PWSTAT_USER58                      (0x10000000UL)
#define BSW_COMM_PWSTAT_USER59                      (0x20000000UL)
#define BSW_COMM_PWSTAT_USER60                      (0x40000000UL)
#define BSW_COMM_PWSTAT_USER61                      (0x80000000UL)

/* User Awake Factor */
#define BSW_COMM_USERAWAKE_NONE                     (0x00000000UL)
#define BSW_COMM_USERAWAKE_1                        (0x00000001UL)
#define BSW_COMM_USERAWAKE_2                        (0x00000002UL)
#define BSW_COMM_USERAWAKE_3                        (0x00000004UL)
#define BSW_COMM_USERAWAKE_4                        (0x00000008UL)
#define BSW_COMM_USERAWAKE_5                        (0x00000010UL)
#define BSW_COMM_USERAWAKE_6                        (0x00000020UL)
#define BSW_COMM_USERAWAKE_7                        (0x00000040UL)
#define BSW_COMM_USERAWAKE_8                        (0x00000080UL)
#define BSW_COMM_USERAWAKE_9                        (0x00000100UL)
#define BSW_COMM_USERAWAKE_10                       (0x00000200UL)
#define BSW_COMM_USERAWAKE_11                       (0x00000400UL)
#define BSW_COMM_USERAWAKE_12                       (0x00000800UL)
#define BSW_COMM_USERAWAKE_13                       (0x00001000UL)
#define BSW_COMM_USERAWAKE_14                       (0x00002000UL)
#define BSW_COMM_USERAWAKE_15                       (0x00004000UL)
#define BSW_COMM_USERAWAKE_16                       (0x00008000UL)
#define BSW_COMM_USERAWAKE_17                       (0x00010000UL)
#define BSW_COMM_USERAWAKE_18                       (0x00020000UL)
#define BSW_COMM_USERAWAKE_19                       (0x00040000UL)
#define BSW_COMM_USERAWAKE_20                       (0x00080000UL)
#define BSW_COMM_USERAWAKE_21                       (0x00100000UL)
#define BSW_COMM_USERAWAKE_22                       (0x00200000UL)
#define BSW_COMM_USERAWAKE_23                       (0x00400000UL)
#define BSW_COMM_USERAWAKE_24                       (0x00800000UL)
#define BSW_COMM_USERAWAKE_25                       (0x01000000UL)
#define BSW_COMM_USERAWAKE_26                       (0x02000000UL)
#define BSW_COMM_USERAWAKE_27                       (0x04000000UL)
#define BSW_COMM_USERAWAKE_28                       (0x08000000UL)
#define BSW_COMM_USERAWAKE_29                       (0x10000000UL)
#define BSW_COMM_USERAWAKE_30                       (0x20000000UL)
#define BSW_COMM_USERAWAKE_31                       (0x40000000UL)
#define BSW_COMM_USERAWAKE_32                       (0x80000000UL)

/* User Handle */
#define BSW_COMM_USERHANDLE_PW_BAT                  (0U)
#define BSW_COMM_USERHANDLE_PW_ACC                  (1U)
#define BSW_COMM_USERHANDLE_PW_IG                   (2U)
#define BSW_COMM_USERHANDLE_PW_USR1                 (3U)
#define BSW_COMM_USERHANDLE_PW_USR2                 (4U)
#define BSW_COMM_USERHANDLE_PW_USR3                 (5U)
#define BSW_COMM_USERHANDLE_PW_USR4                 (6U)
#define BSW_COMM_USERHANDLE_PW_USR5                 (7U)
#define BSW_COMM_USERHANDLE_PW_USR6                 (8U)
#define BSW_COMM_USERHANDLE_PW_USR7                 (9U)
#define BSW_COMM_USERHANDLE_PW_USR8                 (10U)
#define BSW_COMM_USERHANDLE_PW_USR9                 (11U)
#define BSW_COMM_USERHANDLE_PW_USR10                (12U)
#define BSW_COMM_USERHANDLE_PW_USR11                (13U)
#define BSW_COMM_USERHANDLE_PW_USR12                (14U)
#define BSW_COMM_USERHANDLE_PW_USR13                (15U)
#define BSW_COMM_USERHANDLE_PW_USR14                (16U)
#define BSW_COMM_USERHANDLE_PW_USR15                (17U)
#define BSW_COMM_USERHANDLE_PW_USR16                (18U)
#define BSW_COMM_USERHANDLE_PW_USR17                (19U)
#define BSW_COMM_USERHANDLE_PW_USR18                (20U)
#define BSW_COMM_USERHANDLE_PW_USR19                (21U)
#define BSW_COMM_USERHANDLE_PW_USR20                (22U)
#define BSW_COMM_USERHANDLE_PW_USR21                (23U)
#define BSW_COMM_USERHANDLE_PW_USR22                (24U)
#define BSW_COMM_USERHANDLE_PW_USR23                (25U)
#define BSW_COMM_USERHANDLE_PW_USR24                (26U)
#define BSW_COMM_USERHANDLE_PW_USR25                (27U)
#define BSW_COMM_USERHANDLE_PW_USR26                (28U)
#define BSW_COMM_USERHANDLE_PW_USR27                (29U)
#define BSW_COMM_USERHANDLE_PW_USR28                (30U)
#define BSW_COMM_USERHANDLE_PW_USR29                (31U)
#define BSW_COMM_USERHANDLE_PW_USR30                (32U)
#define BSW_COMM_USERHANDLE_PW_USR31                (33U)
#define BSW_COMM_USERHANDLE_PW_USR32                (34U)
#define BSW_COMM_USERHANDLE_PW_USR33                (35U)
#define BSW_COMM_USERHANDLE_PW_USR34                (36U)
#define BSW_COMM_USERHANDLE_PW_USR35                (37U)
#define BSW_COMM_USERHANDLE_PW_USR36                (38U)
#define BSW_COMM_USERHANDLE_PW_USR37                (39U)
#define BSW_COMM_USERHANDLE_PW_USR38                (40U)
#define BSW_COMM_USERHANDLE_PW_USR39                (41U)
#define BSW_COMM_USERHANDLE_PW_USR40                (42U)
#define BSW_COMM_USERHANDLE_PW_USR41                (43U)
#define BSW_COMM_USERHANDLE_PW_USR42                (44U)
#define BSW_COMM_USERHANDLE_PW_USR43                (45U)
#define BSW_COMM_USERHANDLE_PW_USR44                (46U)
#define BSW_COMM_USERHANDLE_PW_USR45                (47U)
#define BSW_COMM_USERHANDLE_PW_USR46                (48U)
#define BSW_COMM_USERHANDLE_PW_USR47                (49U)
#define BSW_COMM_USERHANDLE_PW_USR48                (50U)
#define BSW_COMM_USERHANDLE_PW_USR49                (51U)
#define BSW_COMM_USERHANDLE_PW_USR50                (52U)
#define BSW_COMM_USERHANDLE_PW_USR51                (53U)
#define BSW_COMM_USERHANDLE_PW_USR52                (54U)
#define BSW_COMM_USERHANDLE_PW_USR53                (55U)
#define BSW_COMM_USERHANDLE_PW_USR54                (56U)
#define BSW_COMM_USERHANDLE_PW_USR55                (57U)
#define BSW_COMM_USERHANDLE_PW_USR56                (58U)
#define BSW_COMM_USERHANDLE_PW_USR57                (59U)
#define BSW_COMM_USERHANDLE_PW_USR58                (60U)
#define BSW_COMM_USERHANDLE_PW_USR59                (61U)
#define BSW_COMM_USERHANDLE_PW_USR60                (62U)
#define BSW_COMM_USERHANDLE_PW_USR61                (63U)

#define BSW_COMM_USERHANDLE_USRAWK1                 (64U)
#define BSW_COMM_USERHANDLE_USRAWK2                 (65U)
#define BSW_COMM_USERHANDLE_USRAWK3                 (66U)
#define BSW_COMM_USERHANDLE_USRAWK4                 (67U)
#define BSW_COMM_USERHANDLE_USRAWK5                 (68U)
#define BSW_COMM_USERHANDLE_USRAWK6                 (69U)
#define BSW_COMM_USERHANDLE_USRAWK7                 (70U)
#define BSW_COMM_USERHANDLE_USRAWK8                 (71U)
#define BSW_COMM_USERHANDLE_USRAWK9                 (72U)
#define BSW_COMM_USERHANDLE_USRAWK10                (73U)
#define BSW_COMM_USERHANDLE_USRAWK11                (74U)
#define BSW_COMM_USERHANDLE_USRAWK12                (75U)
#define BSW_COMM_USERHANDLE_USRAWK13                (76U)
#define BSW_COMM_USERHANDLE_USRAWK14                (77U)
#define BSW_COMM_USERHANDLE_USRAWK15                (78U)
#define BSW_COMM_USERHANDLE_USRAWK16                (79U)
#define BSW_COMM_USERHANDLE_USRAWK17                (80U)
#define BSW_COMM_USERHANDLE_USRAWK18                (81U)
#define BSW_COMM_USERHANDLE_USRAWK19                (82U)
#define BSW_COMM_USERHANDLE_USRAWK20                (83U)
#define BSW_COMM_USERHANDLE_USRAWK21                (84U)
#define BSW_COMM_USERHANDLE_USRAWK22                (85U)
#define BSW_COMM_USERHANDLE_USRAWK23                (86U)
#define BSW_COMM_USERHANDLE_USRAWK24                (87U)
#define BSW_COMM_USERHANDLE_USRAWK25                (88U)
#define BSW_COMM_USERHANDLE_USRAWK26                (89U)
#define BSW_COMM_USERHANDLE_USRAWK27                (90U)
#define BSW_COMM_USERHANDLE_USRAWK28                (91U)
#define BSW_COMM_USERHANDLE_USRAWK29                (92U)
#define BSW_COMM_USERHANDLE_USRAWK30                (93U)
#define BSW_COMM_USERHANDLE_USRAWK31                (94U)
#define BSW_COMM_USERHANDLE_USRAWK32                (95U)

#define BSW_COMM_USERHANDLE_PNCUSER0                (0x80U)
#define BSW_COMM_USERHANDLE_PNCUSER1                (0x81U)
#define BSW_COMM_USERHANDLE_PNCUSER2                (0x82U)
#define BSW_COMM_USERHANDLE_PNCUSER3                (0x83U)
#define BSW_COMM_USERHANDLE_PNCUSER4                (0x84U)
#define BSW_COMM_USERHANDLE_PNCUSER5                (0x85U)
#define BSW_COMM_USERHANDLE_PNCUSER6                (0x86U)
#define BSW_COMM_USERHANDLE_PNCUSER7                (0x87U)
#define BSW_COMM_USERHANDLE_PNCUSER8                (0x88U)
#define BSW_COMM_USERHANDLE_PNCUSER9                (0x89U)
#define BSW_COMM_USERHANDLE_PNCUSER10               (0x8AU)
#define BSW_COMM_USERHANDLE_PNCUSER11               (0x8BU)
#define BSW_COMM_USERHANDLE_PNCUSER12               (0x8CU)
#define BSW_COMM_USERHANDLE_PNCUSER13               (0x8DU)
#define BSW_COMM_USERHANDLE_PNCUSER14               (0x8EU)
#define BSW_COMM_USERHANDLE_PNCUSER15               (0x8FU)
#define BSW_COMM_USERHANDLE_PNCUSER16               (0x90U)
#define BSW_COMM_USERHANDLE_PNCUSER17               (0x91U)
#define BSW_COMM_USERHANDLE_PNCUSER18               (0x92U)
#define BSW_COMM_USERHANDLE_PNCUSER19               (0x93U)
#define BSW_COMM_USERHANDLE_PNCUSER20               (0x94U)
#define BSW_COMM_USERHANDLE_PNCUSER21               (0x95U)
#define BSW_COMM_USERHANDLE_PNCUSER22               (0x96U)
#define BSW_COMM_USERHANDLE_PNCUSER23               (0x97U)
#define BSW_COMM_USERHANDLE_PNCUSER24               (0x98U)
#define BSW_COMM_USERHANDLE_PNCUSER25               (0x99U)
#define BSW_COMM_USERHANDLE_PNCUSER26               (0x9AU)
#define BSW_COMM_USERHANDLE_PNCUSER27               (0x9BU)
#define BSW_COMM_USERHANDLE_PNCUSER28               (0x9CU)
#define BSW_COMM_USERHANDLE_PNCUSER29               (0x9DU)
#define BSW_COMM_USERHANDLE_PNCUSER30               (0x9EU)
#define BSW_COMM_USERHANDLE_PNCUSER31               (0x9FU)
#define BSW_COMM_USERHANDLE_PNCUSER32               (0xA0U)
#define BSW_COMM_USERHANDLE_PNCUSER33               (0xA1U)
#define BSW_COMM_USERHANDLE_PNCUSER34               (0xA2U)
#define BSW_COMM_USERHANDLE_PNCUSER35               (0xA3U)
#define BSW_COMM_USERHANDLE_PNCUSER36               (0xA4U)
#define BSW_COMM_USERHANDLE_PNCUSER37               (0xA5U)
#define BSW_COMM_USERHANDLE_PNCUSER38               (0xA6U)
#define BSW_COMM_USERHANDLE_PNCUSER39               (0xA7U)
#define BSW_COMM_USERHANDLE_PNCUSER40               (0xA8U)
#define BSW_COMM_USERHANDLE_PNCUSER41               (0xA9U)
#define BSW_COMM_USERHANDLE_PNCUSER42               (0xAAU)
#define BSW_COMM_USERHANDLE_PNCUSER43               (0xABU)
#define BSW_COMM_USERHANDLE_PNCUSER44               (0xACU)
#define BSW_COMM_USERHANDLE_PNCUSER45               (0xADU)
#define BSW_COMM_USERHANDLE_PNCUSER46               (0xAEU)
#define BSW_COMM_USERHANDLE_PNCUSER47               (0xAFU)
#define BSW_COMM_USERHANDLE_PNCUSER48               (0xB0U)
#define BSW_COMM_USERHANDLE_PNCUSER49               (0xB1U)
#define BSW_COMM_USERHANDLE_PNCUSER50               (0xB2U)
#define BSW_COMM_USERHANDLE_PNCUSER51               (0xB3U)
#define BSW_COMM_USERHANDLE_PNCUSER52               (0xB4U)
#define BSW_COMM_USERHANDLE_PNCUSER53               (0xB5U)
#define BSW_COMM_USERHANDLE_PNCUSER54               (0xB6U)
#define BSW_COMM_USERHANDLE_PNCUSER55               (0xB7U)
#define BSW_COMM_USERHANDLE_PNCUSER56               (0xB8U)
#define BSW_COMM_USERHANDLE_PNCUSER57               (0xB9U)
#define BSW_COMM_USERHANDLE_PNCUSER58               (0xBAU)
#define BSW_COMM_USERHANDLE_PNCUSER59               (0xBBU)
#define BSW_COMM_USERHANDLE_PNCUSER60               (0xBCU)
#define BSW_COMM_USERHANDLE_PNCUSER61               (0xBDU)
#define BSW_COMM_USERHANDLE_PNCUSER62               (0xBEU)
#define BSW_COMM_USERHANDLE_PNCUSER63               (0xBFU)

/* Bus Awake Factor */
#define BSW_COMM_BUSAWAKE_NONE                      (0U)
#define BSW_COMM_BUSAWAKE_EXIST                     (1U)

/* Bus Awake Kind */
#define BSW_COMM_BUSAWAKE_KIND_NONE                 (0x00U)
#define BSW_COMM_BUSAWAKE_KIND_OTHER                (0x01U)
#define BSW_COMM_BUSAWAKE_KIND_ECU                  (0x02U)
#define BSW_COMM_BUSAWAKE_KIND_OWN                  (0x04U)
#define BSW_COMM_BUSAWAKE_KIND_CO                   (0x08U)

/* Bus Type */
#define BSW_COMM_BUS_TYPE_CAN                       (0U)
#define BSW_COMM_BUS_TYPE_ETH                       (3U)
#define BSW_COMM_BUS_TYPE_LIN                       (4U)
#define BSW_COMM_BUS_TYPE_INVALID                   (255U)

/* Channel Attribute */
#define BSW_COMM_CH_ATTRBT_PHYSICAL                 (0U)
#define BSW_COMM_CH_ATTRBT_VIRTUAL                  (1U)

/* PNC Awake Factor */
#define BSW_COMM_PNCAWAKE_NONE                      (0x00000000UL)
#define BSW_COMM_PNCAWAKE_0                         (0x00000001UL)
#define BSW_COMM_PNCAWAKE_1                         (0x00000002UL)
#define BSW_COMM_PNCAWAKE_2                         (0x00000004UL)
#define BSW_COMM_PNCAWAKE_3                         (0x00000008UL)
#define BSW_COMM_PNCAWAKE_4                         (0x00000010UL)
#define BSW_COMM_PNCAWAKE_5                         (0x00000020UL)
#define BSW_COMM_PNCAWAKE_6                         (0x00000040UL)
#define BSW_COMM_PNCAWAKE_7                         (0x00000080UL)
#define BSW_COMM_PNCAWAKE_8                         (0x00000100UL)
#define BSW_COMM_PNCAWAKE_9                         (0x00000200UL)
#define BSW_COMM_PNCAWAKE_10                        (0x00000400UL)
#define BSW_COMM_PNCAWAKE_11                        (0x00000800UL)
#define BSW_COMM_PNCAWAKE_12                        (0x00001000UL)
#define BSW_COMM_PNCAWAKE_13                        (0x00002000UL)
#define BSW_COMM_PNCAWAKE_14                        (0x00004000UL)
#define BSW_COMM_PNCAWAKE_15                        (0x00008000UL)
#define BSW_COMM_PNCAWAKE_16                        (0x00010000UL)
#define BSW_COMM_PNCAWAKE_17                        (0x00020000UL)
#define BSW_COMM_PNCAWAKE_18                        (0x00040000UL)
#define BSW_COMM_PNCAWAKE_19                        (0x00080000UL)
#define BSW_COMM_PNCAWAKE_20                        (0x00100000UL)
#define BSW_COMM_PNCAWAKE_21                        (0x00200000UL)
#define BSW_COMM_PNCAWAKE_22                        (0x00400000UL)
#define BSW_COMM_PNCAWAKE_23                        (0x00800000UL)
#define BSW_COMM_PNCAWAKE_24                        (0x01000000UL)
#define BSW_COMM_PNCAWAKE_25                        (0x02000000UL)
#define BSW_COMM_PNCAWAKE_26                        (0x04000000UL)
#define BSW_COMM_PNCAWAKE_27                        (0x08000000UL)
#define BSW_COMM_PNCAWAKE_28                        (0x10000000UL)
#define BSW_COMM_PNCAWAKE_29                        (0x20000000UL)
#define BSW_COMM_PNCAWAKE_30                        (0x40000000UL)
#define BSW_COMM_PNCAWAKE_31                        (0x80000000UL)
#define BSW_COMM_PNCAWAKE_32                        (0x00000001UL)
#define BSW_COMM_PNCAWAKE_33                        (0x00000002UL)
#define BSW_COMM_PNCAWAKE_34                        (0x00000004UL)
#define BSW_COMM_PNCAWAKE_35                        (0x00000008UL)
#define BSW_COMM_PNCAWAKE_36                        (0x00000010UL)
#define BSW_COMM_PNCAWAKE_37                        (0x00000020UL)
#define BSW_COMM_PNCAWAKE_38                        (0x00000040UL)
#define BSW_COMM_PNCAWAKE_39                        (0x00000080UL)
#define BSW_COMM_PNCAWAKE_40                        (0x00000100UL)
#define BSW_COMM_PNCAWAKE_41                        (0x00000200UL)
#define BSW_COMM_PNCAWAKE_42                        (0x00000400UL)
#define BSW_COMM_PNCAWAKE_43                        (0x00000800UL)
#define BSW_COMM_PNCAWAKE_44                        (0x00001000UL)
#define BSW_COMM_PNCAWAKE_45                        (0x00002000UL)
#define BSW_COMM_PNCAWAKE_46                        (0x00004000UL)
#define BSW_COMM_PNCAWAKE_47                        (0x00008000UL)
#define BSW_COMM_PNCAWAKE_48                        (0x00010000UL)
#define BSW_COMM_PNCAWAKE_49                        (0x00020000UL)
#define BSW_COMM_PNCAWAKE_50                        (0x00040000UL)
#define BSW_COMM_PNCAWAKE_51                        (0x00080000UL)
#define BSW_COMM_PNCAWAKE_52                        (0x00100000UL)
#define BSW_COMM_PNCAWAKE_53                        (0x00200000UL)
#define BSW_COMM_PNCAWAKE_54                        (0x00400000UL)
#define BSW_COMM_PNCAWAKE_55                        (0x00800000UL)
#define BSW_COMM_PNCAWAKE_56                        (0x01000000UL)
#define BSW_COMM_PNCAWAKE_57                        (0x02000000UL)
#define BSW_COMM_PNCAWAKE_58                        (0x04000000UL)
#define BSW_COMM_PNCAWAKE_59                        (0x08000000UL)
#define BSW_COMM_PNCAWAKE_60                        (0x10000000UL)
#define BSW_COMM_PNCAWAKE_61                        (0x20000000UL)
#define BSW_COMM_PNCAWAKE_62                        (0x40000000UL)
#define BSW_COMM_PNCAWAKE_63                        (0x80000000UL)

/* PNC Interface Type */
#define BSW_COMM_PNC_IF_TYPE_AR_COMPLIANCE          (0U)
#define BSW_COMM_PNC_IF_TYPE_AR_EXTEND              (1U)

/* Maximum number of PNC */
#define BSW_COMM_PNCMAXNUM                          (64U)

/* Number of PNCIDs when PNC is not used */
#define BSW_COMM_PNCNUM_NONE                        (0U)

/* Maximum number of power supply */
#define BSW_COMM_SYSSTATMAXNUM                      (64U)
#define BSW_COMM_SYSSTATTBLNUM                      (BSW_COMM_SYSSTATMAXNUM >> 5U)

/* Network management function action type */
#define BSW_COMM_NM_ACT_TYPE_BSSLP                  (0U)
#define BSW_COMM_NM_ACT_TYPE_NO_BSSLP               (1U)

/* Vendor ID */
#define BSW_COMM_VENDOR_ID                          (83U)

/* Module ID */
#define BSW_COMM_MODULE_ID                          (12U)

/* AUTOSAR Release Version */
#define BSW_COMM_AR_RELEASE_MAJOR_VERSION           (4U)
#define BSW_COMM_AR_RELEASE_MINOR_VERSION           (5U)
#define BSW_COMM_AR_RELEASE_REVISION_VERSION        (0U)

/* Vendor Specification Version */
#define BSW_COMM_SW_MAJOR_VERSION                   (4U)
#define BSW_COMM_SW_MINOR_VERSION                   (5U)
#define BSW_COMM_SW_PATCH_VERSION                   (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------*/
/* Unit:ctrl                            */
/*--------------------------------------*/
typedef uint8   Bsw_ComM_UserHandleType;            /* User Handle Type                */
typedef uint8   Bsw_ComM_ModeType;                  /* ComM Mode Type                  */
typedef uint8   Bsw_ComM_StateType;                 /* ComM State Type                 */
typedef uint8   Bsw_ComM_InitStatusType;            /* ComM Initialization Status Type */
typedef uint8   Bsw_ComM_InhibitionStatusType;      /* ComM Inhibition Status Type     */

typedef uint8   Bsw_ComM_PncModeType;               /* ComM PncMode Type               */

/* Config Type Structure */
typedef struct
{
    uint8 Dummy;   /* dummy */
} Bsw_ComM_ConfigType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------*/
/* Unit:ctrl                            */
/*--------------------------------------*/
void                  bsw_comm_ctrl_Init( BswConst Bsw_ComM_ConfigType* ConfigPtr );
void                  bsw_comm_ctrl_DeInit( void );
Std_ReturnType        bsw_comm_ctrl_GetState( NetworkHandleType Channel, Bsw_ComM_StateType* State );
Bsw_ComM_StateType    bsw_comm_ctrl_GetStateFixed( NetworkHandleType Channel );
Std_ReturnType        bsw_comm_ctrl_GetStatus( Bsw_ComM_InitStatusType* Status);
Std_ReturnType        bsw_comm_ctrl_RequestComMode( Bsw_ComM_UserHandleType User, Bsw_ComM_ModeType ComMode );
Std_ReturnType        bsw_comm_ctrl_GetMaxComMode( Bsw_ComM_UserHandleType User, Bsw_ComM_ModeType* ComMode );
Std_ReturnType        bsw_comm_ctrl_GetReqComMode( Bsw_ComM_UserHandleType User, Bsw_ComM_ModeType* ComMode );
Std_ReturnType        bsw_comm_ctrl_GetCurComMode( Bsw_ComM_UserHandleType User, Bsw_ComM_ModeType* ComMode );
void                  bsw_comm_ctrl_ComAllowed( NetworkHandleType Channel, boolean Allowed );
void                  bsw_comm_ctrl_MainFunction( void );
void                  bsw_comm_ctrl_MainFunctionEira( void );
void                  bsw_comm_ctrl_GetChPowSupply( NetworkHandleType Channel, uint32* ChPowSupply );
void                  bsw_comm_ctrl_GetBusAwakePower( NetworkHandleType Channel, uint32* BusAwakePower );
uint8                 bsw_comm_ctrl_JudgeChPowSupply( NetworkHandleType Channel );
uint8                 bsw_comm_ctrl_GetDriverStatus( NetworkHandleType Channel );
Std_ReturnType        bsw_comm_ctrl_SetCoBusAwake( NetworkHandleType Channel ,uint8 CoBusAwake);
uint8                 bsw_comm_ctrl_GetBusAwakeExcCo( NetworkHandleType Channel );
void                  bsw_comm_ctrl_ClrAllCoBusAwake( void );
void                  bsw_comm_ctrl_SetEventAwake( NetworkHandleType Channel );
void                  bsw_comm_ctrl_ClearEventAwake( NetworkHandleType Channel );
void                  bsw_comm_ctrl_SetBusAwake( NetworkHandleType Channel );
void                  bsw_comm_ctrl_ClearBusAwake( NetworkHandleType Channel );
Std_ReturnType        bsw_comm_ctrl_GetInhibitStatus( NetworkHandleType Channel, Bsw_ComM_InhibitionStatusType* Status );
Std_ReturnType        bsw_comm_ctrl_PreventWakeUp( NetworkHandleType Channel, boolean Status );
Std_ReturnType        bsw_comm_ctrl_LimChNoComMode(NetworkHandleType Channel, boolean Status );
Std_ReturnType        bsw_comm_ctrl_LimECUNoComMode(boolean Status );
Std_ReturnType        bsw_comm_ctrl_ReadInhibitCnt( uint16* CounterValue );
Std_ReturnType        bsw_comm_ctrl_ResetInhibitCnt( void );
Std_ReturnType        bsw_comm_ctrl_SetECUGroupClass( Bsw_ComM_InhibitionStatusType Status );
void                  bsw_comm_ctrl_GetVersionInfo( Std_VersionInfoType* Versioninfo );
void                  bsw_comm_ctrl_ChkRam( void );
uint8                 bsw_comm_ctrl_GetBusAwakeKind( NetworkHandleType Channel );
Std_ReturnType        bsw_comm_ctrl_SetPnEira( NetworkHandleType Channel, BswConstR uint8* EiraDataPtr );
Std_ReturnType        bsw_comm_ctrl_GetPnIntRequest( NetworkHandleType Channel, uint8* PncAwakePtr );
Std_ReturnType        bsw_comm_ctrl_GetPncAwake( NetworkHandleType Channel, uint32* PncAwakeLo, uint32* PncAwakeUp );
Std_ReturnType        bsw_comm_ctrl_SetCoPncAwake( NetworkHandleType Channel, uint32 PncAwakeLo, uint32 PncAwakeUp );
Std_ReturnType        bsw_comm_ctrl_SetCoPncAwakeNoReq( NetworkHandleType Channel, uint32 PncAwakeLo, uint32 PncAwakeUp );
Std_ReturnType        bsw_comm_ctrl_GetPncMode( PNCHandleType PNC, Bsw_ComM_PncModeType* RequestedMode );
Std_ReturnType        bsw_comm_ctrl_GetChPncMode( NetworkHandleType Channel, PNCHandleType PNC, Bsw_ComM_PncModeType* RequestedMode );
Std_ReturnType        bsw_comm_ctrl_ReqChPNCComMode( NetworkHandleType Channel, Bsw_ComM_UserHandleType User, Bsw_ComM_ModeType ComMode );
Std_ReturnType        bsw_comm_ctrl_GetPncAwakeFixed( NetworkHandleType Channel, uint32* PncAwakeLo, uint32* PncAwakeUp );
Std_ReturnType        bsw_comm_ctrl_GetPnEiraFixed( NetworkHandleType Channel, uint32* EiraDataLo, uint32* EiraDataUp );
void                  bsw_comm_ctrl_GetPncReqRdyStat( NetworkHandleType Channel, uint32* PncIndexLo, uint32* PncIndexUp );
void                  bsw_comm_ctrl_GetPncPrepSlpStat( NetworkHandleType Channel, uint32* PncIndexLo, uint32* PncIndexUp );
void                  bsw_comm_ctrl_GetPncEnableTxSt( NetworkHandleType Channel, uint32* PncIndexLo, uint32* PncIndexUp );
Std_ReturnType        bsw_comm_ctrl_SetChBusAwake( NetworkHandleType Channel, uint8 ChBusAwake );
void                  bsw_comm_ctrl_UpdateChBusAwake( void );

void                  bsw_comm_ctrl_Nm_NetStartInd( NetworkHandleType Channel );
void                  bsw_comm_ctrl_Nm_NetworkMode( NetworkHandleType Channel );
void                  bsw_comm_ctrl_Nm_PreBusSlpMode( NetworkHandleType Channel );
void                  bsw_comm_ctrl_Nm_BusSleepMode( NetworkHandleType Channel );
void                  bsw_comm_ctrl_Nm_RestartInd( NetworkHandleType Channel );
void                  bsw_comm_ctrl_Nm_PreNetMode( NetworkHandleType Channel );
void                  bsw_comm_ctrl_SetSyncAwake( NetworkHandleType Channel );
void                  bsw_comm_ctrl_ClearSyncAwake( NetworkHandleType Channel );

void                  bsw_comm_ctrl_BusSM_ModeInd( NetworkHandleType Channel, Bsw_ComM_ModeType ComMode );

void                  bsw_comm_ctrl_DCM_ActiveDiag( NetworkHandleType Channel );
void                  bsw_comm_ctrl_DCM_InactiveDiag( NetworkHandleType Channel );

void                  bsw_comm_ctrl_EcuM_WakeUpInd( NetworkHandleType Channel );
void                  bsw_comm_ctrl_EcuM_PNCWakeUpInd( PNCHandleType PNCid );
void                  bsw_comm_ctrl_EcuM_ChPNCWkupInd( NetworkHandleType Channel, PNCHandleType PNCid );

void                  bsw_comm_ctrl_CbkPncModeChgNtf( NetworkHandleType Channel, PNCHandleType PNC, Bsw_ComM_PncModeType PreviousPncMode, Bsw_ComM_PncModeType CurrentPncMode);
void                  bsw_comm_ctrl_CbkSetChBusAwake( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_COMM_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/01/07                                             */
/*  v2-1-0          :2022/09/19                                             */
/*  v2-2-0          :2023/05/08                                             */
/*  v3-0-0          :2024/11/12                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
