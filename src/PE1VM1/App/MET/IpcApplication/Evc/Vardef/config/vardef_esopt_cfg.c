/* 2.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Vadef Electrical System Option.                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_ESOPT_CFG_C_MAJOR                 (2)
#define VARDEF_ESOPT_CFG_C_MINOR                 (5)
#define VARDEF_ESOPT_CFG_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_esopt_cfg_private.h"
#include "vardef_esopt_rx.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_ESOPT_CFG_C_MAJOR != VARDEF_ESOPT_CFG_H_MAJOR) || \
     (VARDEF_ESOPT_CFG_C_MINOR != VARDEF_ESOPT_CFG_H_MINOR) || \
     (VARDEF_ESOPT_CFG_C_PATCH != VARDEF_ESOPT_CFG_H_PATCH))
#error "vardef_esopt_cfg.c and vardef_esopt_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_ESOPT_CFG_C_MAJOR != VARDEF_ESOPT_CHANNEL_H_MAJOR) || \
     (VARDEF_ESOPT_CFG_C_MINOR != VARDEF_ESOPT_CHANNEL_H_MINOR) || \
     (VARDEF_ESOPT_CFG_C_PATCH != VARDEF_ESOPT_CHANNEL_H_PATCH))
#error "vardef_esopt_cfg.c and vardef_esopt_channel.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_ESO_NUM_RX                           (178U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
ST_VDF_ESO_RX          st_gp_vdf_eso_rx[VDF_ESO_NUM_RX];                        /* The size is equal to u2_g_VDF_ESO_NUM_RX          */
U4                     u4_gp_vdf_eso_ava[VDF_ESO_NOW_AVA];                      /* The size is equal to u1_g_VDF_ESO_NOW_AVA         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_VDF_ESO_CH    st_gp_VDF_ESO_CH[VDF_ESO_NUM_RX] = {
    {
        &u1_g_VdfEsoRx_INDSPDALT,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_INDSPDALT,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BDB1S08_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_CNTR_DISP,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_CNTR_DISP,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_AVN1S30,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0008U,                            /* u2_vom_act          */
        ((U2)10000U / (U2)VDF_MAIN_TICK),       /* u2_rxc_peri         */
        {
            (U2)0U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_AUDIO,                   /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CXPI,            /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */ /*@@@ 19pvf CANFDItem OXCAN_PDU_RX_CXP_AUD1S01  @@@*/
        (U2)0x0008U,                            /* u2_vom_act          */
        ((U2)5000U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_RARCLCK,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CXPI,            /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */ /*@@@ 19pvf CANFDItem OXCAN_PDU_RX_CXP_RCK1S01  @@@*/
        (U2)0x0008U,                            /* u2_vom_act          */
        ((U2)5000U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_D_DPTZ,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_D_DPTZ,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ABG1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_P_DPTZ,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_P_DPTZ,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ABG1S01_RXCH0,
        (U2)0x0002U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_TPMS,                    /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_TPMS,                    /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_TPM1S02_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_TPMSCHN,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_TPMSCHN,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_TPM1S02_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_VSC,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_VSC,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DDM1S17_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)700U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_BSM,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_BSM,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_FHL,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_FHL,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_DOA,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_DOA,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S02_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_RCD,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_RCD,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BCC1S06_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_CSR_TTR,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_CSR_TTR,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_CSR1S07_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ICS,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_ICS,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_PDA,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_PDA,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S51_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_PCS,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_PCS,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F02_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_LTA,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_LTA,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_DS1_LDA,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_DS1_LDA,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_RSA,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_RSA,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_AHB,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_AHB,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ACC,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_ACC,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S39_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_LCS,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_LCS,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS11S37_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_LCS,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_LCS,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS11S37_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_TMN,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_TMN,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_LVN1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_LVN,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_LVN,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_LVN1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ISA,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_ISA,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_DSC,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_DSC,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ENG1S60_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_AUTOP,                   /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_AUTOP,                   /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_IPA1S05_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_RCTA,                    /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_RCTA,                    /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_BRKHLD,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_BRKHLD,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_VSC1S95,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)700U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_CXSWS1S02,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CXPI,            /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CXP_SWS1S02,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0080U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)3U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_PDA,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PDA,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S51_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_CXSWS1S04,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CXPI,            /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */ /*@@@ 19pvf CANFDItem OXCAN_PDU_RX_CXP_SWS1S04 @@@*/
        (U2)0x0080U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)3U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_CXMPS1S01,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CXPI,            /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */ /*@@@ 19pvf CANFDItem OXCAN_PDU_RX_CXP_MPS1S01 @@@*/
        (U2)0x0080U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)3U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_AISMM,                   /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_AISMM,                   /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_AVNMC08,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_NE_MET,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_NE_MET,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_ENG1S98,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)200U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_HV_NE,                   /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_EHV1F04_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)200U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_MM_AUDIO,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_MM_AUDIO,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_AVNMS47,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0001U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_MM_TEL,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_MM_TEL,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_AVNMS31,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0001U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_MM_NAVI,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_MM_NAVI,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_AVNMS57,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0001U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_OILMNT,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_OILMNT,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,     /* u2_msg_rx           */
        (U2)0x0010U,                            /* u2_vom_act          */
        ((U2)3200U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_BSM,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_BSM,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_CSR,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_CSR,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_NAVI_TAB,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_NAVI_TAB,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_AVNMS57,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0001U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PBDHND,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PBDHND,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BKD1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PBD,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PBD,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BKD1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PBDFLLOPN,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PBDFLLOPN,            /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BKD1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PBDVOL,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PBDVOL,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BKD1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_DMC,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_DMC,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_INFRAEMGSET,          /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_INFRAEMGSET,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ITS1S04_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_LCA,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_LCA,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS11S37_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RTAN,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RTAN,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RTANSUP,              /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RTANSUP,              /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_SEASNS,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_SEASNS,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S02_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_SEA,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_SEA,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S02_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_TSGTM,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_TSGTM,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ITS1S04_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_LDA,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_LDA,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_ALTOPT_VB,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ALTOPT_VB,            /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_ALTOPT_BOF,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ALTOPT_BOF,           /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_ALTOPT_VBOF,          /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ALTOPT_VBOF,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_LDWTEXT,              /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_LDWTEXT,              /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_SWSEXIST,             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_SWSEXIST,             /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_BSD_ITCR,             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_BSD_ITCR,             /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_BSD_ILCR,             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_BSD_ILCR,             /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RCTA,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RCTA,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RCD,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RCD,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BCC1S06_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PKSB,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PKSB,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_ACCCRS,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ACCCRS,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_ACCAPP,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ACCAPP,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_ACCCURV,              /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ACCCURV,              /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_FCTA,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_FCTA,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS11S40_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RSR,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RSR,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BDB1S03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_THESEN,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_THESEN,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BDB1F01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_TPMS,                    /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_TPMS_VAR,             /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_TPM1S02_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_BATCSW,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_BATCSW,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_OTHER,           /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)0U,                             /* u2_rxc_min[MIN_INA] */
            (U2)0U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_PEDPRO,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_PEDPRO,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_PDS1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_DRS,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ARS1S90_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)630U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_LTA,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_LTA,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S92_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_LTA_NA,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_LTA_NA,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S92_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_GPF,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_GPF,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_ENG1G97,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0010U,                            /* u2_vom_act          */
        ((U2)2200U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_MWL,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_MWL,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S70_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_CVRS,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_CVRS,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S02_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_BATWSW,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_BATWSW,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BAT1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PERSET,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PERSET,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_AVN1S98,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)U2_MAX                          /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_CXCMB1S05,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CXPI,            /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */ /*@@@ 19pvf CANFDItem OXCAN_PDU_RX_CXP_CMB1S05 @@@*/
        (U2)0x0080U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)3U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_CXCMB1S06,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CXPI,            /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */ /*@@@ 19pvf CANFDItem OXCAN_PDU_RX_CXP_CMB1S06 @@@*/
        (U2)0x0080U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)3U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ISA,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ACCDYNM,              /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_LTA_HOFDI,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_LTA_HOFDI,            /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S92_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PDASA,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PDASA,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PDADA,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PDADA,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PDAOAA,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PDAOAA,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RSA_TSRSWEXT,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RSA_TSRSWEXT,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RSA_NTFLVEXT,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RSA_NTFLVEXT,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RSA_XSSPDEXT,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RSA_XSSPDEXT,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_GVIF,                    /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_GVIF2,                   /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_OTHER,           /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */
        (U2)0x0080U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)0U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ETH_AUDIO,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_ETH_AUDIO,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_ETH,             /* u1_input_type       */
        (U2)HMIVARDEF_FLM_MM2C100N,             /* u2_msg_rx           */
        (U2)0x0001U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ETH_TEL,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_ETH_TEL,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_ETH,             /* u1_input_type       */
        (U2)HMIVARDEF_FLM_MM2C107N,             /* u2_msg_rx           */
        (U2)0x0001U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ETH_NAVI,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_ETH_NAVI,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_ETH,             /* u1_input_type       */
        (U2)HMIVARDEF_FLM_MM2C112N,             /* u2_msg_rx           */
        (U2)0x0001U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ETH_NAVI_TAB,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_ETH_NAVI_TAB,            /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_ETH,             /* u1_input_type       */
        (U2)HMIVARDEF_FLM_MM2C112N,             /* u2_msg_rx           */
        (U2)0x0001U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RTWUCT,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RTWUCT,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F02_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RSA_SPBZEXT,          /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RSA_SPBZEXT,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_BSM_BSDDISP1,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_BSM_BSDDISP1,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_BSM_BSDDISP2,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_BSM_BSDDISP2,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_AVS,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_AVS,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PNCCUS,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PNCCUS,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_PLG1S21_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_LCKCUS_UNLOCK,        /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_LCKCUS_UNLOCK,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_IDT1S07_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_LCKCUS_AUTOLOCK,      /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_LCKCUS_AUTOLOCK,      /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_IDT1S07_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_EDSS,                    /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_EDSS,                    /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_CC,                      /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_CC,                      /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_4WDSYS,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_4WDSYS,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FWD1S10_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)300U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ERM,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_ERM,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_TM,                      /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_TM,                      /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S52_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_FCTA,                    /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_FCTA,                    /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS11S40_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SWS,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SWS,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_PMAR,                    /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_PMAR,                    /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_AC100V_TESTMODE,      /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_AC100V_TESTMODE,      /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_EHV1S97_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_SRPCUS,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_SRPCUS,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S70_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_DEPARTURE_PREVENT,    /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_DEPARTURE_PREVENT,    /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_PCS,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PCSEXIST,             /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_DS12F02_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_NOETY,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_NOETY,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_ADAS,                    /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_ADU1S08,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0002U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_PTS_MILREQ,              /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_PTS_MILREQ,              /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ENG1G13_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)1U,                             /* u2_rxc_min[MIN_INA] */
            (U2)1U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_AVSEXT,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_AVSEXT,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_SCS1S14_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)4200U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_OILLVG,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_OILLVG,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ENG1S99_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)3200U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_EPSSA,                   /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_EPS1S11_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)200U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_TRLR_EQ,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_TRLR_EQ,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_GERPOS,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_GERPOS,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_OTHER,           /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */
        (U2)0x0080U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)0U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_PTL,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PTL,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BKD1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SOHDSP,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SOHDSP,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BAT1S11_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)210U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_HVSYSIND,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_HVSYSIND,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_OTHER,           /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)0U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_NOETY_RED,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_NOETY_RED,            /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S12_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_TRLR_EQ,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_TRAILLER,             /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_BSR1S03_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ACC,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ACCELERATION,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S39_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_ECORUNLEV,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ECORUNLEV,            /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_INTERSECTION,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_INTERSECTION,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_SWITCH_CC,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_SWITCH_CC,            /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_SPDLIM_OFFSET,        /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_SPDLIM_OFFSET,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S41_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_PMAR,                    /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_SAS,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_CSR1S04_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_LVN,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_PRECEDING_VEHCLE,     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_LVN1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_TMN,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_TRAFFIC_SIGNAL,       /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_LVN1S01_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_DM_CAMERA,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_DM_CAMERA,            /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ADU1S07_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_WRN_SEN,              /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_WRN_SEN,              /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ADU1S07_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_SWIVEL,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_SWIVEL,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S70_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_SHADING_AREA,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_SHADING_AREA,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_FCM1S70_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_ACINV_1500W,          /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ACINV_1500W,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_EHV1S97_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_ACINV_2400W,          /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ACINV_2400W,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_EHV1S97_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_ACINV_7200W,          /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_ACINV_7200W,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_EHV1S97_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_BRPADW,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_BRPADW,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
#if 0   /* BEV BSW provisionally */
        (U2)OXCAN_PDU_RX_CAN_VSC1S96,           /* u2_msg_rx           */
#else
        (U2)U2_MAX,                             /* u2_msg_rx           */
#endif
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)700U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_GVIF_METDISP,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_GVIF2_METDISP,           /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_OTHER,           /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */
        (U2)0x0080U,                            /* u2_vom_act          */
        (U2)U2_MAX,                             /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)0U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SGAUGE,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SGAUGE,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ENG1G13_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)600U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_EVMIL_RED,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_EVMIL_RED,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_EHV1S99_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_EVMIL_AMBER,             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_EVMIL_AMBER,             /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_EHV1S99_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_OMRBB,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_OMRBB,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_OMRBB_MLRSEL,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_OMRBB_MLRSEL,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_OMRBB_REVERSE,        /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_OMRBB_REVERSE,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_OMRBB_AUTO,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_OMRBB_AUTO,           /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_OMRBB_NONAUTO,        /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_OMRBB_NONAUTO,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ADIEXIST,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_ADIEXIST,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ADU1S07_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_HEDLMP_AUT,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_HEDLMP_AUT,           /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_HEDLMP_HED,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_HEDLMP_HED,           /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_HEDLMP_TAL,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_HEDLMP_TAL,           /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_HEDLMP_TAL_DBL,       /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_HEDLMP_TAL_DBL,       /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_HEDLMP_DRLOFF,        /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_HEDLMP_DRLOFF,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_HEDLMP_OFF,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_HEDLMP_OFF,           /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_HEDLMP_OFF_DBL,       /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_HEDLMP_OFF_DBL,       /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_HEDLMP_DRL,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_HEDLMP_DRL,           /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_FRONT_FOG,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_FRONT_FOG,            /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_REAR_FOG,             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_REAR_FOG,             /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_RAINDROP_SENSOR,      /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_RAINDROP_SENSOR,      /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S26_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_INTTIME_AJUST,        /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_INTTIME_AJUST,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S26_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_REAR_WIPER,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_REAR_WIPER_OFF,       /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S26_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_REAR_WIPER,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_REAR_WIPER_LO,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S26_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_REAR_WIPER_INT,       /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_REAR_WIPER_INT,       /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S26_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_REAR_WASHER,          /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_REAR_WASHER,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S26_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_SERVICE_POS,          /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_SERVICE_POS,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SOLCHG,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SOLCHG,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_SOL1S02_RXCH0,           /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_OBBPWL,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_OBBPWL,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_PDU_RX_CAN_ZN11S19_RXCH0,     /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    }
};

const U2               u2_g_VDF_ESO_NUM_RX        = (U2)VDF_ESO_NUM_RX;
const U2               u2_g_VDF_ESO_NUM_RX_BY_RUN = (U2)(((U4)VDF_ESO_NUM_RX + ((U4)VDF_NUM_TSLOT - (U4)1U)) / (U4)VDF_NUM_TSLOT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_VDF_ESO_AVA   st_gp_VDF_ESO_AVA[VDF_ESO_NOW_AVA] = {
    {
        (U4)VDF_ESO_INI_W0,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W0,                        /* u4_nvm */
        (U4)0x08000000U,                           /* u4_unk */
        (U4)0xFFFFCE3FU,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W0,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W0                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W1,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W1,                        /* u4_nvm */
        (U4)0x30000100U,                           /* u4_unk */
        (U4)0xBC00FFADU,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W1,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W1                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W2,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W2,                        /* u4_nvm */
        (U4)0x3FA3D068U,                           /* u4_unk */
        (U4)0x3FB3D569U,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W2,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W2                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W3,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W3,                        /* u4_nvm */
        (U4)0x098D0CBAU,                           /* u4_unk */
        (U4)0x1F8FACBAU,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W3,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W3                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W4,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W4,                        /* u4_nvm */
        (U4)0x407815F8U,                           /* u4_unk */
        (U4)0x507FB5FFU,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W4,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W4                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W5,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W5,                        /* u4_nvm */
        (U4)0xC000E000U,                           /* u4_unk */
        (U4)0xFFF0FF7FU,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W5,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W5                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W6,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W6,                        /* u4_nvm */
        (U4)0x3E800FFFU,                           /* u4_unk */
        (U4)0x3FA4FFFFU,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W6,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W6                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W7,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W7,                        /* u4_nvm */
        (U4)0x8FEFFC00U,                           /* u4_unk */
        (U4)0xCFEFFC40U,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W7,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W7                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W8,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W8,                        /* u4_nvm */
        (U4)0x00000000U,                           /* u4_unk */
        (U4)0x00000000U,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W8,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W8                    /* u2_bid */
    }
};
const U1               u1_g_VDF_ESO_NOW_AVA = (U1)VDF_ESO_NOW_AVA;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2               u2_g_VDF_ESO_RES_TOUT = (U2)5000U / (U2)VDF_MAIN_TICK;  /* 5 seconds */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1               u1_g_VDF_ESO_RXC_INT = (U1)OXCAN_RX_RXEV_CNT_UNK;
const U1               u1_g_VDF_ESO_RXC_MAX = (U1)OXCAN_RX_RXEV_CNT_MAX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VardefEsOptCfgInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefEsOptCfgInit(void)
{
    vd_g_VardefEsOptCfgABG1S01Init();
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefEsOptCfgCanRxEvcnt(const U2 u2_a_MSG_ID)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefEsOptCfgCanRxEvcnt(const U2 u2_a_MSG_ID)
{
    U1    u1_t_rxev_cnt;

    u1_t_rxev_cnt = u1_g_oXCANRxEvcnt(u2_a_MSG_ID);

    return(u1_t_rxev_cnt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefEsOptCfgEthRxEvcnt(const U2 u2_a_MSG_ID)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefEsOptCfgEthRxEvcnt(const U2 u2_a_MSG_ID)
{
    U1    u1_t_rxev_cnt;

    u1_t_rxev_cnt = u1_g_HmiVardefRcvCnt((U1)u2_a_MSG_ID);

    return(u1_t_rxev_cnt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefEsOptCfgAvaByAVN(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefEsOptCfgAvaByAVN(void)
{
    U1    u1_t_ava;

    u1_t_ava  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MM_NAVI);
    u1_t_ava |= u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_ETH_NAVI);

    return(u1_t_ava);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/22/2019  YI       NEW!                                                                                               */
/*  1.1.0     4/ 2/2019  YI       vardef_esopt.c v1.0.0 -> v1.1.0                                                                    */
/*  1.2.0     7/ 3/2019  YI       vardef_esopt.c v1.1.0 -> v1.2.0                                                                    */
/*  1.3.0    10/25/2019  YI       vardef_esopt.c v1.2.0 -> v1.3.0                                                                    */
/*  1.4.0    11/ 7/2019  YI       vardef_esopt.c v1.3.0 -> v1.4.0                                                                    */
/*  1.5.0     1/ 8/2020  YI       vardef_esopt.c v1.4.0 -> v1.5.0                                                                    */
/*  2.0.0     3/ 2/2020  TN       vardef_esopt.c v1.5.0 -> v2.0.0                                                                    */
/*  2.1.0     9/28/2020  SF       vardef_esopt.c v2.0.0 -> v2.1.0                                                                    */
/*  2.1.0     1/25/2021  SF       vardef_esopt.c v2.1.0 -> v2.2.0                                                                    */
/*  2.3.0    11/15/2021  RO       vardef_esopt.c v2.2.0 -> v2.3.0                                                                    */
/*  2.4.0     3/15/2022  RO       vardef_esopt.c v2.3.0 -> v2.4.0                                                                    */
/*  2.5.0    11/25/2024  KO       vardef_esopt.c v2.4.0 -> v2.5.0                                                                    */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1    9/28/2020  SF       Change config for 800B CV-R                                                                        */
/*  800B-2    1/25/2021  SF       Change config for 800B 1A                                                                          */
/*  840B-1    5/10/2021  AT       Change config for 840B CV                                                                          */
/*  893B-1    6/14/2021  RO       Change config for 893B CV                                                                          */
/*  178D-1    7/19/2021  RO       Change config for 178D CV                                                                          */
/*  893B-2   11/23/2021  RO       Change config for 893B 1A                                                                          */
/*  893B-3    1/31/2022  HA       Change config for 893B MPT                                                                         */
/*  893B-4    3/15/2022  RO       Change config for 893B QCS                                                                         */
/*  200D-1    7/01/2022  RO       Change config for 200D 970B Pre1A                                                                  */
/*  200D-2    9/20/2022  MG       Change config for 200D 1A                                                                          */
/*  200D-3   11/ 1/2022  MG       Change config for 200D MPT                                                                         */
/*  200D-4   11/15/2022  MG       Change config for 200D MPT                                                                         */
/*  19PFv3   10/11/2023  KH       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-2 11/03/2023  TH       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-3 11/16/2023  HF       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-4 12/ 7/2023  DR       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-5 12/26/2023  RO       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-6  1/31/2024  SW       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-7  2/ 8/2024  SW       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-8  2/29/2024  SW       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-9  4/15/2024  SN       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-10 5/07/2024  TR       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-11 5/24/2024  SW       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-12 6/20/2024  YR       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-13 6/20/2024  PG       Change config for 19PFv3 R1.2                                                                      */
/*  19PFv3-14 7/08/2024  YR       Change config for 19PFv3 R1.2                                                                      */
/*  19PFv3-15 8/01/2024  SN       Change config for 19PFv3 R1.2                                                                      */
/*  BEV-1     10/10/2024  KT      Change config for BEV System_Consideration_1.(MET-B_OMRBB-CSTD-0-)                                 */
/*  BEV-2     11/25/2024  KO      Change config for BEV System_Consideration_1.(MET-C_ECB-CSTD-1-/MET-C_EPB-CSTD-1-)                 */
/*  BEV-3     12/20/2024  KO      Change config for BEV System_Consideration_1.(MET-H_ZMILREQ-CSTD-1)                                */
/*  BEV-4     01/13/2025  KO      Change config for BEV System_Consideration_1.(MET-H_SOLCHG-CSTD-1)                                 */
/*  BEV-5     01/30/2025  KO      Change config for BEV System_Consideration_1.(MET-C_HCS-CSTD-0)                                    */
/*  BEV-6     02/05/2025  SF      Change config for BEV System_Consideration_1.(MET-M_ONOFF-CSTD-1-02-A-C0)                          */
/*  BEV-7     02/10/2025  HY      Change config for BEV System_Consideration_1.(MET-B_PWLBB-CSTD-0-)                                 */
/*  BEV-8     02/10/2025  HT      Change config for BEV System_Consideration_1.(MET-B_WPBB-CSTD-0-)                                  */
/*  BEV-9     02/10/2025  RO      Change config for BEV System_Consideration_1.(MET-S_ADMID-CSTD-0-)                                 */
/*  BEV-10    02/10/2025  RO      Change config for BEV System_Consideration_1.(MET-S_ADTT-CSTD-0-)                                  */
/*  BEV-11    02/10/2025  HF      Change config for BEV System_Consideration_1.(MET-D_SFTPOS-CSTD-1-)                                */
/*  BEV-12    02/10/2025  HF      Change config for BEV System_Consideration_1.(MET-B_LMPBB-CSTD-0-)                                 */
/*                                                                                                                                   */
/*  * YI   = Yoshiki Iwata, Denso                                                                                                    */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * SF   = Seiya Fukutome, Denso Techno                                                                                            */
/*  * AT   = Ayano Tomimoto, KSE                                                                                                     */
/*  * RO   = Reiya Okuda, KSE                                                                                                        */
/*  * HA   = Hiroki Asano, PRD                                                                                                       */
/*  * MG   = Mei Godo, KSE                                                                                                           */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * TR   = Tebs Ramos, DTPH                                                                                                        */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*  * SF   = Shiro Furui, Denso Techno                                                                                               */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * HT   = Hibiki Tanii, KSE                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
