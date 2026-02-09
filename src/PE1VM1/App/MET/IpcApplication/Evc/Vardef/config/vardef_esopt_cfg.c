/* 2.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Vardef Electrical System Option.                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_ESOPT_CFG_C_MAJOR                 (2)
#define VARDEF_ESOPT_CFG_C_MINOR                 (6)
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
#define VDF_ESO_NUM_RX                           (95U)

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
        (U2)OXCAN_RXD_PDU_CAN_BDB1S08_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_D_DPTZ,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_D_DPTZ,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ABG1S01_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ABG1S01_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_TPM1S02_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_TPM1S02_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_BSR1S01_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_BSR1S01_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_BSR1S02_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_BCC1S06_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_CSR1S07_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_CSR1S04_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_FCM1S51_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_DS12F02_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_DS12F03_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_DS12F03_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_FCM1S12_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_FCM1S52_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_FCM1S39_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_DS11S37_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_LVN1S01_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_LVN1S01_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_FCM1S41_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_BDC1SV1_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_BSR1S01_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_DDM1S17_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)700U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_DMC,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_DMC,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_FCM1S52_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_PEDPRO,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_PEDPRO,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_PDS1S01_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_DRS,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_DRS,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ARS1S90_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ADC1S17_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_MWL,                     /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_MWL,                     /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_FCM1S70_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_BSR1S01_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_FCM1S52_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_FCM1S52_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_FWD1S10_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_FCM1S52_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ADC1S14_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_DS11S40_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_DS12F03_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_CSR1S04_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_ADIEXIST,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_ADASTT,              /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ADU1S07_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_AVSEXT,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_AVSEXT,                  /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_SCS1S14_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)4200U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_TRLR_EQ,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_TRLR_EQ,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_BSR1S03_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_VSC1G96_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_EVMIL_RED,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_EVMIL_RED,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_EHV1S99_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_EHV1S99_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_PERSET,                  /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_PERSET,              /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_UCB1S01_CH0,      /* u2_msg_rx           */
        (U2)0x0080U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_TITE,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_TITE,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        vdp_PTR_NA,                             /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_EPS_EPSSBW,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_EPS1S11_CH0,      /* u2_msg_rx           */
        (U2)0x0080U,                            /* u2_vom_act          */
        ((U2)200U / (U2)VDF_MAIN_TICK),         /* u2_rxc_peri         */
        {
            (U2)U2_MAX,                         /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_HEDLMP_AUT,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_HEDLMP_AUT,           /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S26_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S26_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S26_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S26_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S26_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S26_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SYS_SW_CAMERA_WASHER,    /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_SW_CAMERA_WASHER,    /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ZN11S26_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_WIPER_DEICER,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_WIPER_DEICER,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ACN1S04_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_SOL1S02_CH0,      /* u2_msg_rx           */
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
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SYS_SW_OBBPBD,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_SW_OBBPBD,           /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ZN11S19_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_VHCOBBSD,                /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_VHCOBBSD,                /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_SCS1S11_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)4200U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_OBBMODE,              /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_OBBMODE,              /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_FCM1S39_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_OBBSAV,               /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_OBBSAV,               /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ADC1S14_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_DPM1,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_DPM1,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_BDB1F02_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_DPM2,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_DPM2,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_BDB1F02_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_DPM3,                 /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SW_DPM3,                 /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_BDB1F02_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SYS_ADDOT_TT,            /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_ADDOT_TT,            /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ADC1S14_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_MSBBSW_NORMAL,        /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_MSBBSW_NORMAL,       /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_MSBBSW_SPORT,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_MSBBSW_SPORT,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_MSBBSW_ECO,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_MSBBSW_ECO,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_MSBBSW_CUSTOM,        /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_MSBBSW_CUSTOM,       /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_MSBBSW_RANGE,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_MSBBSW_RANGE,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_MSBBSW_RCMFRT,        /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_MSBBSW_RCMFRT,       /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_MSBBSW_SNOW,          /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_MSBBSW_SNOW,         /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_MSBBSW_TRACK,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_MSBBSW_TRACK,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_MSBBSW_TRAIL,         /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_MSBBSW_TRAIL,        /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_ENG1S60_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SW_MSBBSW_DAC,           /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_MSBBSW_DAC,          /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)OXCAN_RXD_PDU_CAN_VSC1G96_CH0,      /* u2_msg_rx           */
        (U2)0x0002U,                            /* u2_vom_act          */
        ((U2)2100U / (U2)VDF_MAIN_TICK),        /* u2_rxc_peri         */
        {
            (U2)2U,                             /* u2_rxc_min[MIN_INA] */
            (U2)2U                              /* u2_rxc_min[MIN_ACT] */
        }
    },
    {
        &u1_g_VdfEsoRx_SYS_4WDSYS_DISCON,       /* fp_u1_AVA_RX        */
        (U2)VDF_ESO_CH_SYS_4WDSYS_DISCON,       /* u2_eso_ch           */
        (U1)VDF_ESO_INPUT_TYPE_CAN,             /* u1_input_type       */
        (U2)U2_MAX,                             /* u2_msg_rx           */
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
        (U4)0x00000000U,                           /* u4_unk */
        (U4)0xF7FFCE31U,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W0,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W0                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W1,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W1,                        /* u4_nvm */
        (U4)0x00000000U,                           /* u4_unk */
        (U4)0x0000002DU,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W1,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W1                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W2,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W2,                        /* u4_nvm */
        (U4)0x00000000U,                           /* u4_unk */
        (U4)0x00000100U,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W2,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W2                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W3,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W3,                        /* u4_nvm */
        (U4)0x008C0000U,                           /* u4_unk */
        (U4)0x048C0000U,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W3,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W3                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W4,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W4,                        /* u4_nvm */
        (U4)0x00000000U,                           /* u4_unk */
        (U4)0x10000000U,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W4,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W4                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W5,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W5,                        /* u4_nvm */
        (U4)0x00000020U,                           /* u4_unk */
        (U4)0x0244077CU,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W5,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W5                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W6,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W6,                        /* u4_nvm */
        (U4)0x3E800000U,                           /* u4_unk */
        (U4)0x3F808000U,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W6,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W6                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W7,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W7,                        /* u4_nvm */
        (U4)0xBFEFFD00U,                           /* u4_unk */
        (U4)0xFFEFFF80U,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W7,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W7                    /* u2_bid */
    },
    {
        (U4)VDF_ESO_INI_W8,                        /* u4_ini */
        (U4)VDF_ESO_NVM_W8,                        /* u4_nvm */
        (U4)0x007FE715U,                           /* u4_unk */
        (U4)0x00FFF717U,                           /* u4_rx  */

        (U2)NVMCID_U4_VDF_ESO_W8,                  /* u2_nid */
        (U2)RIMID_U4_VDF_ESO_W8                    /* u2_bid */
    }
};
const U1               u1_g_VDF_ESO_NOW_AVA = (U1)VDF_ESO_NOW_AVA;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2               u2_g_VDF_ESO_RES_TOUT = (U2)5000U / (U2)VDF_MAIN_TICK;  /* 5 seconds */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1               u1_g_VDF_ESO_RXC_INT = (U1)OXCAN_RXD_EVC_UNK;
const U1               u1_g_VDF_ESO_RXC_MAX = (U1)OXCAN_RXD_EVC_MAX;

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

    u1_t_rxev_cnt = u1_g_oXCANRxdEvcnt(u2_a_MSG_ID);

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

#if 0   /* BEV Rebase provisionally */
    u1_t_rxev_cnt = u1_g_HmiVardefRcvCnt((U1)u2_a_MSG_ID);
#else   /* BEV Rebase provisionally */
    u1_t_rxev_cnt = (U1)0U;
#endif   /* BEV Rebase provisionally */

    return(u1_t_rxev_cnt);
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
/*  2.5.0     8/26/2024  TN       vardef_esopt.c v2.4.0 -> v2.5.0                                                                    */
/*  2.6.0    12/25/2024  KM       vardef_esopt.c v2.5.0 -> v2.6.0                                                                    */
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
/*  19PFv3-16 8/02/2024  TN(DT)   Change config for 19PFv3 R1.3(Add Steering ECU Func)                                               */
/*  19PFv3-17 8/16/2024  TR       Change config for 19PFv3 R2                                                                        */
/*  19PFv3-18 10/24/2024 SW       Change config for 19PFv3 R2(delete SYS_SW_PADISEX)                                                 */
/*  19PFv3-19 11/ 7/2024 PG       Change config for 19PFv3 R2.2(delete SGAUGE)                                                       */
/*  19PFv3-20 11/ 7/2024 SI       Change config for 19PFv3 R2(Add MM-GVIF Func)                                                      */
/*  19PFv3-21 11/18/2024 SH       Change config for 19PFv3 R2(Delete NE_MET and HV_NE)                                               */
/*  19PFv3-22 11/19/2024 KH       Change config for 19PFv3 R2.2(Delete SW_ALTOPT_BOF, SW_ALTOPT_VBOF)                                */
/*  19PFv3-23 12/09/2024 SN       Change config for 19PFv3 R2.2(Add MM_MAP)                                                          */
/*  19PFv3-24 12/10/2024 PG       Change config for 19PFv3 R3.0(Add SYS_ADASCS_SPDLIM_RSA)                                           */
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
/*  BEV-13    05/21/2025  MN      Change config for BEV PreCV.(MET-M_CLKCTL-CSTD-0-)                                                 */
/*  BEV-14    05/30/2025  SN(K)   Change config for BEV System_Consideration_2.(MET-B_TITEBB-CSTD-0-)                                */
/*  BEV-15    05/30/2025  SN(K)   Change config for BEV System_Consideration_2.(MET-C_HCSBSW-CSTD-0-)                                */
/*  BEV-16    05/30/2025  SN(K)   Change config for BEV System_Consideration_2.(MET-S_ADBB-CSTD-0-)                                  */
/*  BEV-17    06/17/2025  JS      Change config for BEV System_Consideration_2.(MET-B_WDICBB-CSTD-0-)                                */
/*  BEV-18    06/18/2025  KO      Change config for BEV System_Consideration_2.(MET-B_DRPBB-CSTD-0-)                                 */
/*  BEV-19    10/15/2025  SN      Configured for BEVstep3_Rebase                                                                     */
/*  BEV-20    11/27/2025  PG      Change config for BEV System_Consideration_ADAS.(MET-S_TMTT-CSTD-0)                                */
/*  BEV-21    12/02/2025  MA      SW_TITE Function presence judgment processing changed to bidirectional.(MET-B_TITEBB-CSTD-0-)      */
/*  BEV-22    12/08/2025  TS      Change config for BEV System_Consideration_ADAS.(MET-S_ADVMID-CSTD-0)                              */
/*  BEV-23    12/12/2025  KN      Change config for BEV System_Consideration_ADAS.(MET-C_HCSBSW-CSTD-0-)                             */
/*  BEV-24    12/12/2025  MA      Added 10 function presence judgment processes.(MET-C_MSBBSW-CSTD-0-)                               */
/*  BEV-25    12/12/2025  KO      Change config for BEV System_Consideration_ADAS.(MET-S_ADBB-CSTD-0)                                */
/*  BEV-26    01/07/2026  YN      Change config for BEV FF2.(MET-B_CWHBB-CSTD-0-)                                                    */
/*  BEV-27    01/08/2026  MA      BRPADW function check time changed from 700ms to 2100ms.(MET-C_BRPADW-CSTD-A0-)                    */
/*  BEV-28    01/14/2026  TS      Change config for BEV FF2.(MET-C_DRS-CSTD-1)                                                       */
/*  BEV-29    01/16/2026  KEM     Update for BEV FF2. (B_PERSET)                                                                     */
/*  BEV-30    01/22/2026  MA      Change config for BEV FF2.(MET-B_PBDBB-CSTD-0-)                                                    */
/*  BEV-31    01/23/2026  YN      Change config for BEV FF2.(MET-D_4WDSYS-CSTD-2)                                                    */
/*  BEV-32    01/23/2026  RO      Change config for BEV Full_Function_2.                                                             */
/*                                MET-S_ADBB-CSTD-0-04-A-C0                                                                          */
/*                                Changed ERM function from disabled to enabled for NVM abnormality.                                 */
/*  BEV-33    01/23/2026  HY      Change config for BEV Full_Function_2.                                                             */
/*                                MET-C_GMN-CSTD-0-02-A-C1                                                                           */
/*                                Add the judgement of EPS & EPSSBW function.                                                        */
/*  BEV-34    02/09/2026  MA      Change config for BEV FF2(MET-P_TMNT-CSTD-1-00-B-C0)                                               */
/*                                                                                                                                   */
/*  * YI     = Yoshiki Iwata, Denso                                                                                                  */
/*  * TN     = Takashi Nagai, Denso                                                                                                  */
/*  * SF     = Seiya Fukutome, Denso Techno                                                                                          */
/*  * AT     = Ayano Tomimoto, KSE                                                                                                   */
/*  * RO     = Reiya Okuda, KSE                                                                                                      */
/*  * HA     = Hiroki Asano, PRD                                                                                                     */
/*  * MG     = Mei Godo, KSE                                                                                                         */
/*  * KH     = Kiko Huerte, DTPH                                                                                                     */
/*  * TH     = Taisuke Hirakawa, KSE                                                                                                 */
/*  * HF     = Hinari Fukamachi, KSE                                                                                                 */
/*  * DR     = Dyan Reyes, DTPH                                                                                                      */
/*  * RO     = Ryo Oohashi, KSE                                                                                                      */
/*  * SW     = Shun Watanabe, Denso Techno                                                                                           */
/*  * SN     = Shimon Nambu, Denso Techno                                                                                            */
/*  * TR     = Tebs Ramos, DTPH                                                                                                      */
/*  * YR     = Yhana Regalario, DTPH                                                                                                 */
/*  * PG     = Patrick Garcia, DTPH                                                                                                  */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*  * SI     = Shugo Ichinose, Denso Techno                                                                                          */
/*  * SH     = Sae Hirose, Denso Techno                                                                                              */
/*  * KM     = Kazuma Miyazawa, Denso Techno                                                                                         */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*  * SF   = Shiro Furui, Denso Techno                                                                                               */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * HT   = Hibiki Tanii, KSE                                                                                                       */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*  * SN(K)= Shizuka Nakajima, KSE                                                                                                   */
/*  * JS   = Jun Sugiyama, KSE                                                                                                       */
/*  * MA   = Misaki Aiki, Denso Techno                                                                                               */
/*  * TS   = Takuo Suganuma, Denso Techno                                                                                            */
/*  * KN   = kazuo Nishigaki, Denso Techno                                                                                           */
/*  * YN   = Yujiro Nagaya, Denso Techno                                                                                             */
/*  * KEM  = Kane Edward Malapo, DTPH                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
