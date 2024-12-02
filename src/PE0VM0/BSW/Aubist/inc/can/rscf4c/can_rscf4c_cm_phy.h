/* can_rscf4c_cm_phy_h_m10700_v2-2-1                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4C/CM/PHYSICAL/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CAN_RSCF4C_CM_PHY_H
#define CAN_RSCF4C_CM_PHY_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_u4BIT_NONE                  (0x00000000UL)
#define CAN_u4BIT0                      (0x00000001UL)
#define CAN_u4BIT31                     (0x80000000UL)

#define CAN_SFT_0                       (0U)
#define CAN_SFT_1                       (1U)
#define CAN_SFT_2                       (2U)
#define CAN_SFT_3                       (3U)
#define CAN_SFT_4                       (4U)
#define CAN_SFT_5                       (5U)
#define CAN_SFT_6                       (6U)
#define CAN_SFT_7                       (7U)
#define CAN_SFT_8                       (8U)
#define CAN_SFT_9                       (9U)
#define CAN_SFT_10                      (10U)
#define CAN_SFT_11                      (11U)
#define CAN_SFT_12                      (12U)
#define CAN_SFT_13                      (13U)
#define CAN_SFT_14                      (14U)
#define CAN_SFT_15                      (15U)
#define CAN_SFT_16                      (16U)
#define CAN_SFT_17                      (17U)
#define CAN_SFT_18                      (18U)
#define CAN_SFT_19                      (19U)
#define CAN_SFT_20                      (20U)
#define CAN_SFT_21                      (21U)
#define CAN_SFT_22                      (22U)
#define CAN_SFT_23                      (23U)
#define CAN_SFT_24                      (24U)
#define CAN_SFT_25                      (25U)
#define CAN_SFT_26                      (26U)
#define CAN_SFT_27                      (27U)
#define CAN_SFT_28                      (28U)
#define CAN_SFT_29                      (29U)
#define CAN_SFT_30                      (30U)
#define CAN_SFT_31                      (31U)

#define CAN_DATA_ARYSIZE_4BYTE          (16U)
#define CAN_DATA_ARYSIZE_1BYTE          (64U)

#define CAN_MBSFT_MSK                   (0x1FU)

#define CAN_CLK_CLKC                    (0U)
#define CAN_CLK_XINCAN                  (1U)

#define CAN_NUM_FIFO_RCV                (8U)
#define CAN_NUM_BUF_SND_PER_CH          (CAN_CFG_TXBUF_NUM)
#define CAN_NUM_BUF_SND_PER_REG         (32U)

#define CAN_NUM_RULETABLE_PER_PAGE      (16U)
#define CAN_NUM_RULETABLE_PER_PAGE_MSK  (0x0FU)
#define CAN_NUM_RULETABLE_PER_PAGE_SFT  (0x4U)

#define CAN_TRX_FIFO_0                  (0U)
#define CAN_TRX_FIFO_1                  (1U)
#define CAN_TRX_FIFO_2                  (2U)

#define CAN_CFTYPE_RX_INT               (CAN_TRX_FIFO_0)
#define CAN_CFTYPE_RX_POLL              (CAN_TRX_FIFO_1)

#define CAN_GMODE_RST2STP_CYCLE         (3U)
#define CAN_GMODE_RST2TST_CYCLE         (10U)
#define CAN_GMODE_RST2COM_CYCLE         (10U)
#define CAN_CMODE_RST2STP_CYCLE         (3U)

#define CAN_RAMCHK_MASK_LOWERHALFBYTE   (0x0FU)
#define CAN_RAMCHK_VALUE_LOWERHALFBYTE  (0x0FU)

#define CAN_USER_BAUDRATE               (CAN_TB_USER_BAUDRATE )
#define CAN_125KBPS_2M_PTN1             (CAN_TB_125K_2M_PTN1  )
#define CAN_125KBPS_2P5M_PTN1           (CAN_TB_125K_2P5M_PTN1)
#define CAN_250KBPS_4M_PTN1             (CAN_TB_250K_4M_PTN1  )
#define CAN_250KBPS_4M_PTN2             (CAN_TB_250K_4M_PTN2  )
#define CAN_250KBPS_5M_PTN1             (CAN_TB_250K_5M_PTN1  )
#define CAN_250KBPS_5M_PTN2             (CAN_TB_250K_5M_PTN2  )
#define CAN_500KBPS_8M_PTN1             (CAN_TB_500K_8M_PTN1  )
#define CAN_500KBPS_8M_PTN2             (CAN_TB_500K_8M_PTN2  )
#define CAN_500KBPS_8M_PTN3             (CAN_TB_500K_8M_PTN3  )
#define CAN_500KBPS_8M_PTN4             (CAN_TB_500K_8M_PTN4  )
#define CAN_500KBPS_8M_PTN5             (CAN_TB_500K_8M_PTN5  )
#define CAN_500KBPS_10M_PTN1            (CAN_TB_500K_10M_PTN1 )
#define CAN_500KBPS_10M_PTN2            (CAN_TB_500K_10M_PTN2 )
#define CAN_500KBPS_10M_PTN3            (CAN_TB_500K_10M_PTN3 )
#define CAN_500KBPS_10M_PTN4            (CAN_TB_500K_10M_PTN4 )
#define CAN_500KBPS_10M_PTN5            (CAN_TB_500K_10M_PTN5 )
#define CAN_500KBPS_20M_PTN1            (CAN_TB_500K_20M_PTN1 )
#define CAN_500KBPS_32M_PTN1            (CAN_TB_500K_32M_PTN1 )
#define CAN_500KBPS_40M_PTN1            (CAN_TB_500K_40M_PTN1 )
#define CAN_500KBPS_40M_PTN2            (CAN_TB_500K_40M_PTN2 )
#define CAN_500KBPS_80M_PTN1            (CAN_TB_500K_80M_PTN1 )

#define CAN_USER_DATABAUDRATE           (CAN_TB_USER_DATABAUDRATE)
#define CAN_DB_125KBPS_2M_PTN1          (CAN_TB_DB_125K_2M_PTN1  )
#define CAN_DB_125KBPS_2P5M_PTN1        (CAN_TB_DB_125K_2P5M_PTN1)
#define CAN_DB_250KBPS_4M_PTN1          (CAN_TB_DB_250K_4M_PTN1  )
#define CAN_DB_250KBPS_4M_PTN2          (CAN_TB_DB_250K_4M_PTN2  )
#define CAN_DB_250KBPS_5M_PTN1          (CAN_TB_DB_250K_5M_PTN1  )
#define CAN_DB_250KBPS_5M_PTN2          (CAN_TB_DB_250K_5M_PTN2  )
#define CAN_DB_500KBPS_8M_PTN1          (CAN_TB_DB_500K_8M_PTN1  )
#define CAN_DB_500KBPS_8M_PTN2          (CAN_TB_DB_500K_8M_PTN2  )
#define CAN_DB_500KBPS_8M_PTN3          (CAN_TB_DB_500K_8M_PTN3  )
#define CAN_DB_500KBPS_8M_PTN4          (CAN_TB_DB_500K_8M_PTN4  )
#define CAN_DB_500KBPS_8M_PTN5          (CAN_TB_DB_500K_8M_PTN5  )
#define CAN_DB_500KBPS_10M_PTN1         (CAN_TB_DB_500K_10M_PTN1 )
#define CAN_DB_500KBPS_10M_PTN2         (CAN_TB_DB_500K_10M_PTN2 )
#define CAN_DB_500KBPS_10M_PTN3         (CAN_TB_DB_500K_10M_PTN3 )
#define CAN_DB_500KBPS_10M_PTN4         (CAN_TB_DB_500K_10M_PTN4 )
#define CAN_DB_500KBPS_10M_PTN5         (CAN_TB_DB_500K_10M_PTN5 )
#define CAN_DB_500KBPS_20M_PTN1         (CAN_TB_DB_500K_20M_PTN1 )
#define CAN_DB_500KBPS_32M_PTN1         (CAN_TB_DB_500K_32M_PTN1 )
#define CAN_DB_500KBPS_40M_PTN1         (CAN_TB_DB_500K_40M_PTN1 )
#define CAN_DB_500KBPS_40M_PTN2         (CAN_TB_DB_500K_40M_PTN2 )
#define CAN_DB_500KBPS_80M_PTN1         (CAN_TB_DB_500K_80M_PTN1 )
#define CAN_DB_2MBPS_20M_PTN1           (CAN_TB_DB_2M_20M_PTN1   )
#define CAN_DB_2MBPS_32M_PTN1           (CAN_TB_DB_2M_32M_PTN1   )
#define CAN_DB_2MBPS_40M_PTN1           (CAN_TB_DB_2M_40M_PTN1   )
#define CAN_DB_2MBPS_40M_PTN2           (CAN_TB_DB_2M_40M_PTN2   )
#define CAN_DB_2MBPS_80M_PTN1           (CAN_TB_DB_2M_80M_PTN1   )
#define CAN_DB_5MBPS_80M_PTN1           (CAN_TB_DB_5M_80M_PTN1   )

#define CAN_BAUDRATEINFO_1_1            (CAN_TB_SSPOFFSET_NOUSE      )
#define CAN_BAUDRATEINFO_1_2            (CAN_TB_SSPOFFSET_2M_20M_PTN1)
#define CAN_BAUDRATEINFO_1_3            (CAN_TB_SSPOFFSET_2M_32M_PTN1)
#define CAN_BAUDRATEINFO_1_4            (CAN_TB_SSPOFFSET_2M_40M_PTN1)
#define CAN_BAUDRATEINFO_1_5            (CAN_TB_SSPOFFSET_2M_40M_PTN2)
#define CAN_BAUDRATEINFO_1_6            (CAN_TB_SSPOFFSET_2M_80M_PTN1)
#define CAN_BAUDRATEINFO_1_7            (CAN_TB_SSPOFFSET_5M_80M_PTN1)

#define CAN_BAUDRATEINFO_2_1            (CAN_NOUSE)
#define CAN_BAUDRATEINFO_2_2            (CAN_USE  )

#define CAN_BAUDRATEINFO_3_1            (0x00000000UL)


#define CAN_u4CMNCFG_INIT               (0x00000000UL)
#define CAN_u4CMCTR_INIT                (0x00000001UL)
#define CAN_u4GCFG_INIT                 (0x00000000UL)
#define CAN_u4GCTR_INIT                 (0x00000000UL)
#define CAN_u4GFDCFG_INIT               (0x00000000UL)
#define CAN_u4GAFLCFGV_INIT             (0x00000000UL)
#define CAN_u4GAFLIDJ_INIT              (0xFFFFFFFFUL)
#define CAN_u4GAFLMJ_INIT               (0xDFFFFFFFUL)
#define CAN_u4GAFLP0J_INIT              (0x00000000UL)
#define CAN_u4GAFLP1J_INIT              (0x00000000UL)
#define CAN_u4RMNB_INIT                 (0x00000000UL)
#define CAN_u4RFCCX_INIT                (0x00000000UL)
#define CAN_u4CFCCK_INIT                (0x00000000UL)
#define CAN_u4CFCCEK_INIT               (0x00010000UL)
#define CAN_u4TMIDP_INIT                (0x9FFFFFFFUL)
#define CAN_u4TMIECY_INIT               (0x00000000UL)
#define CAN_u4TXQCC0M_INIT              (0x00000000UL)
#define CAN_u4TXQCC1M_INIT              (0x00000000UL)
#define CAN_u4TXQCC2M_INIT              (0x00000000UL)
#define CAN_u4TXQCC3M_INIT              (0x00000000UL)
#define CAN_u4THLCCM_INIT               (0x00000000UL)
#define CAN_u4CDTCT_INIT                (0x00000000UL)
#define CAN_u4CMDCFG_INIT               (0x00000000UL)
#define CAN_u4CMFDCFG_INIT              (0x00000000UL)
#define CAN_u4CDTTCT_INIT               (0x00000000UL)
#define CAN_u4GRSTC_INIT                (0x0000C400UL)
#define CAN_u4GFCMC_INIT                (0x00000000UL)
#define CAN_u4GFTBAC_INIT               (0x00000000UL)


#define CAN_u4CMCTR_CHMDC_COMM_SET      (0x00000000UL)
#define CAN_u4CMCTR_CHMDC_RESET_SET     (0x00000001UL)
#define CAN_u4CMCTR_CSLPR_STOP_SET      (0x00000004UL)

#define CAN_u4CMSTS_CMODE_COMM          (0x00000000UL)
#define CAN_u4CMSTS_CMODE_RESET         (0x00000001UL)
#define CAN_u4CMSTS_CMODE_STOP          (0x00000005UL)

#define CAN_u4CMERFL_CLEARALL           (0x00000000UL)
#define CAN_u4CMERFL_BOEF_BUSOFF        (0x00000008UL)
#define CAN_u4CMERFL_BOEF_CLR           (0x00007FF7UL)

#define CAN_u4CMFDCFG_TDCE_SET          (0x00000200UL)
#define CAN_u4CMFDCFG_TDCE_CLR          (0xFFFFFDFFUL)

#define CAN_u4CMFDSTS_CLEARALL          (0x00000000UL)

#define CAN_u4GCTR_GMDC_COMM_SET        (0x00000000UL)
#define CAN_u4GCTR_GMDC_RESET_SET       (0x00000001UL)
#define CAN_u4GCTR_GMDC_TEST_SET        (0x00000002UL)
#define CAN_u4GCTR_GSLPR_STOP_SET       (0x00000004UL)

#define CAN_u4GSTS_GMODE_COMM           (0x00000000UL)
#define CAN_u4GSTS_GMODE_RESET          (0x00000001UL)
#define CAN_u4GSTS_GMODE_TEST           (0x00000002UL)
#define CAN_u4GSTS_GMODE_STOP           (0x00000005UL)
#define CAN_u4GSTS_GRAMINIT             (0x00000008UL)

#define CAN_u4GERFL_CLEARALL            (0x00000000UL)

#define CAN_u4GAFLECTR_AFLDAE_ENA       (0x00000100UL)
#define CAN_u4GAFLECTR_AFLDAE_DIS       (0x00000000UL)

#define CAN_u4GAFLMJ_STDIDMSK_NOUSE     (0xC00007FFUL)
#define CAN_u4GAFLMJ_EXTIDMSK_NOUSE     (0xDFFFFFFFUL)
#define CAN_u4GAFLMJ_GAFLIDEM_SET       (0x80000000UL)
#define CAN_u4GAFLMJ_GAFLRTRM_SET       (0x40000000UL)
#define CAN_u4RMNB_CLEARALL             (0x00000000UL)

#define CAN_u4RFSTSX_CLEARALL           (0x00000001UL)

#define CAN_u4CFCCK_CFRXIE_DIS          (0xFFFFFFFDUL)
#define CAN_u4CFCCK_CFE_NOUSE           (0xFFFFFFFEUL)

#define CAN_u4CFSTSK_CLEARALL           (0x00000001UL)
#define CAN_u4CFSTSK_CFRXIF_CLR         (0x01070015UL)
#define CAN_u4CFSTSK_CFRXIF_EXC_CLR     (0x00000009UL)

#define CAN_u4CFFDCSTSK_CFFDF_CANFD     (0x00000004UL)

#define CAN_u4CFPCTRK_CFPC_SET          (0x000000FFUL)

#define CAN_u1TMCP_TMTR_SET             ((uint8)0x01U)
#define CAN_u1TMCP_TMTAR_SET            ((uint8)0x02U)

#define CAN_u1TMSTSP_TXFREE             ((uint8)0x00U)
#define CAN_u1TMSTSP_ABORTED            ((uint8)0x02U)
#define CAN_u1TMSTSP_TMTRF_CLR          ((uint8)0x00U)

#define CAN_u4TMPTRP_CLEARALL           (0x00000000UL)

#define CAN_u4TMFDCTRP_CLEARALL         (0x00000000UL)
#define CAN_u4TMFDCTRP_FDF_CAN          (0x00000000UL)
#define CAN_u4TMFDCTRP_FDF_CANFD        (0x00000004UL)
#define CAN_u4TMFDCTRP_BRS_OFF          (0x00000000UL)
#define CAN_u4TMFDCTRP_BRS_ON           (0x00000002UL)
#define CAN_u4TMFDCTRP_ESI_E_ACT        (0x00000000UL)
#define CAN_u4TMFDCTRP_ESI_E_PCV        (0x00000001UL)

#define CAN_u4TMDFBP_CLEARALL           (0x00000000UL)

#define CAN_u4TXQSTS0M_CLEARALL         (0x00000001UL)
#define CAN_u4TXQSTS1M_CLEARALL         (0x00000001UL)
#define CAN_u4TXQSTS2M_CLEARALL         (0x00000001UL)
#define CAN_u4TXQSTS3M_CLEARALL         (0x00000001UL)

#define CAN_u4THLSTSM_CLEARALL          (0x00000001UL)

#define CAN_u4GTSTCFG_ICBCE_DIS         (0x00000000UL)

#define CAN_u4GTSTCTR_RTME_ENA          (0x00000004UL)
#define CAN_u4GTSTCTR_RTME_DIS          (0x00000000UL)
#define CAN_u4GTSTCTR_ICBCTME_DIS       (0x00000000UL)

#define CAN_u4GLOCKK_LOCK_RELKEY1       (0x00007575UL)
#define CAN_u4GLOCKK_LOCK_RELKEY2       (0x00008A8AUL)


#define CAN_u4CMSTS_MODEALL_MSK         (0x00000007UL)
#define CAN_u4CMERFL_BOEF_MSK           (0x00000008UL)
#define CAN_u4CMFDCFG_TDCO_MSK          (0x00FF0000UL)
#define CAN_u4GSTS_GRAMINIT_MSK         (0x00000008UL)
#define CAN_u4GSTS_MODEALL_MSK          (0x0000000FUL)
#define CAN_u4GAFLECTR_USEDBIT_MSK      (0x00000100UL)
#define CAN_u4GAFLECTR_AFLPN_MSK        (0x0000007FUL)
#define CAN_u4GAFLMJ_GAFLIDM_STD_MSK    (0x000007FFUL)
#define CAN_u4GAFLMJ_GAFLIDM_EXT_MSK    (0x1FFFFFFFUL)
#define CAN_u4CFSTSK_CFMC_MSK           (0x0000FF00UL)
#define CAN_u4CFIDK_EID_MSK             (0x9FFFFFFFUL)
#define CAN_u4CFPTRK_CFDLC_MSK          (0xF0000000UL)
#define CAN_u4CFFDCSTSK_CFPTR_MSK       (0xFFFF0000UL)
#define CAN_u4CDTCT_USEDBIT_MSK         (0x0000FFFFUL)
#define CAN_u1TMSTSP_REQ_RES_MSK        ((uint8)0x1EU)
#define CAN_u4TMIDP_SID_MSK             (0x000007FFUL)
#define CAN_u4TMIDP_EID_MSK             (0x9FFFFFFFUL)
#define CAN_u4TXQCC0M_USEDBIT_MSK       (0x00071FA7UL)
#define CAN_u4TXQCC1M_USEDBIT_MSK       (0x00071FA7UL)
#define CAN_u4TXQCC2M_USEDBIT_MSK       (0x00071FA7UL)
#define CAN_u4TXQCC3M_USEDBIT_MSK       (0x00041FA5UL)
#define CAN_u4THLCCM_USEDBIT_MSK        (0x00000F01UL)
#define CAN_u4GTSTCFG_USEDBIT_MSK       (0x000000FFUL)
#define CAN_u4GTSTCFG_RTMPS_MSK         (0x03FF0000UL)
#define CAN_u4GTSTCTR_USEDBIT_MSK       (0x00000005UL)
#define CAN_u4GTSTCTR_RTME_MSK          (0x00000004UL)
#define CAN_u4RMNB_USEDBIT_MSK          (0x000007FFUL)
#define CAN_u4CFCCK_USEDBIT_MSK         (0xFFFFFF77UL)
#define CAN_u4CFCCK_GCHKBIT_MSK         (0x00FFF370UL)
#define CAN_u4CFCCEK_USEDBIT_MSK        (0x00010107UL)
#define CAN_u4CFFDCSTSK_CFFDF_MSK       (0x00000004UL)
#define CAN_u4CMCTR_USEDBIT_MSK         (0xC7EFFF0FUL)
#define CAN_u4CMCTR_MODEALL_MSK         (0x00000007UL)
#define CAN_u4GCFG_USEDBIT_MSK          (0x0000003FUL)
#define CAN_u4GCFG_DCS_MSK              (0x00000010UL)
#define CAN_u4GCTR_USEDBIT_MSK          (0x0000DF07UL)
#define CAN_u4GFDCFG_USEDBIT_MSK        (0x00000001UL)
#define CAN_u4CDTTCT_USEDBIT_MSK        (0x00FFFFFFUL)
#define CAN_u4GRSTC_USEDBIT_MSK         (0x00000001UL)
#define CAN_u4GFCMC_USEDBIT_MSK         (0x0000000FUL)
#define CAN_u4GFTBAC_USEDBIT_MSK        (0x0F0F0F0FUL)


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


#endif  /* CAN_RSCF4C_CM_PHY_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2021/12/15                                              */
/*  v2-2-1         :2022/07/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
