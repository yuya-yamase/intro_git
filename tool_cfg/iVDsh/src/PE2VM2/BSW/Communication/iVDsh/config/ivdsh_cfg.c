/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Inter-Vm Data SHaring                                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_CFG_C_MAJOR                        (1)
#define IVDSH_CFG_C_MINOR                        (0)
#define IVDSH_CFG_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ivdsh_cfg_private.h"
#include "ehvm_cfg_pe2_vm0.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((IVDSH_CFG_C_MAJOR != IVDSH_H_MAJOR) || \
     (IVDSH_CFG_C_MINOR != IVDSH_H_MINOR) || \
     (IVDSH_CFG_C_PATCH != IVDSH_H_PATCH))
#error "ivdsh_cfg.c and ivdsh.h : source and header files are inconsistent!"
#endif

#if ((IVDSH_CFG_C_MAJOR != IVDSH_CFG_H_MAJOR) || \
     (IVDSH_CFG_C_MINOR != IVDSH_CFG_H_MINOR) || \
     (IVDSH_CFG_C_PATCH != IVDSH_CFG_H_PATCH))
#error "ivdsh_cfg.c and ivdsh_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_NUM_FQ_CH                          (4U)
#define IVDSH_NUM_FQ_REA                         (3U)
#define IVDSH_FQ_CH_REA_0                        (0U)
#define IVDSH_FQ_CH_REA_1                        (1U)
#define IVDSH_FQ_CH_REA_2                        (2U)
#define IVDSH_FQ_CH_WRI                          (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IVDSH_WA_NWORD_WRI                       (29U)
#define IVDSH_WA_NWORD_REA_0                     (4U)
#define IVDSH_WA_NWORD_REA_1                     (25U)
#define IVDSH_WA_NWORD_REA_2                     (15U)

#define IVDSH_WA_NWORD                           (117U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section bss=".IVDSH_BSS_VAR_NO_INIT"

U4                          u4_gp_ivdsh_buf_wa[IVDSH_WA_NWORD];

#if(IVDSH_NUM_FQ_REA > 0U)
ST_IVDSH_FQ_REA             st_gp_ivdsh_fq_rea[IVDSH_NUM_FQ_REA];
#else
ST_IVDSH_FQ_REA             st_gp_ivdsh_fq_rea[];
#endif

#pragma ghs section bss=default

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section rodata=".IVDSH_RODATA_CONST"

const U4                    u4_g_IVDSH_WA_NWORD = (U4)IVDSH_WA_NWORD;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_IVDSH_WA           st_gp_IVDSH_WA_BY_DID[IVDSH_NUM_DID] =
{
    /* u2_begin,    u2_nword,       u2_fq_ch : FIFO/Queue Channel       */
    /*------------------------------------------------------------------*/
    /* Write                                                            */
    /*------------------------------------------------------------------*/
    {(U2)0U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO3_STBY       */
    {(U2)1U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_TIMOFST    */
    {(U2)2U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_TIMFMT     */
    {(U2)3U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_DSPTIM     */
    {(U2)4U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_DSPCAL     */
    {(U2)5U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_CAL        */
    {(U2)6U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_CAM_DIAP   */
    {(U2)7U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO3_WHLINI_INF */
    {(U2)8U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO3_STRMODE    */
    {(U2)9U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO3_OPESTS     */
    {(U2)10U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_GPS_REQ           */
    {(U2)11U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_WHLINI_REQ */
    {(U2)12U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO3_DIN2_STAT  */
    {(U2)13U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_DMS1S02    */
    {(U2)14U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_MET1S27    */
    {(U2)15U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_MET1S28    */
    {(U2)16U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_MET1S29    */
    {(U2)17U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_MET1S30    */
    {(U2)18U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_MET1S43    */
    {(U2)19U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_MET1S62    */
    {(U2)20U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_MET1S70    */
    {(U2)21U,       (U2)2U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_FWUPXREQ_H        */
    {(U2)23U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_FWUPXREQ_D        */
    {(U2)24U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO3_SIPERRCMP  */
    {(U2)25U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO3_VMRESET_REQ*/
    {(U2)26U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_DRC_ALVCNT */
    {(U2)27U,       (U2)2U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_VM2TO1_DRC_WRDATA */
    /*------------------------------------------------------------------*/
    /* Read from VM#0                                                   */
    /*------------------------------------------------------------------*/
    {(U2)0U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_0},     /* IVDSH_DID_REA_CANBUS_STS_2M1    */
    {(U2)1U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_0},     /* IVDSH_DID_REA_CANBUS_STS_5M     */
    {(U2)2U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_0},     /* IVDSH_DID_REA_CANBUS_STS_2M2    */
    {(U2)3U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_0},     /* IVDSH_DID_REA_CANBUS_STS_LCAN   */
    /*------------------------------------------------------------------*/
    /* Read from VM#1                                                   */
    /*------------------------------------------------------------------*/
    {(U2)1U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_TIMOFST    */
    {(U2)2U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_TIMFMT     */
    {(U2)3U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_CAL        */
    {(U2)4U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_CALDEF     */
    {(U2)5U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_CALMIN     */
    {(U2)7U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_CAM_DIAP   */
    {(U2)8U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_FLYNOP     */
    {(U2)9U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO23_FSLP      */
    {(U2)10U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_WHLINI_RES */
    {(U2)12U,       (U2)2U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_MET1D51    */
    {(U2)14U,       (U2)2U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_FWUPXRES          */
    {(U2)20U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_DRC_ALVCNT */
    {(U2)21U,       (U2)2U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_DRC_RDDATA */
    {(U2)23U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_DRC_FSTRD  */
    {(U2)24U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_DRC_WRINF  */
    /*------------------------------------------------------------------*/
    /* Read from VM#3                                                   */
    /*------------------------------------------------------------------*/
    {(U2)0U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_VM3TO2_SIPERR_INF */
    {(U2)1U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_VM3TO2_OTA_OFFSTS */
    {(U2)2U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_VM3TO2_BOOTLOG_INF*/
    {(U2)3U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_VM3TO12_RESTART   */
    {(U2)4U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_VM3TO2_BOOT_CNT   */
    {(U2)5U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_VM3TO2_BOOT_TIME  */
    {(U2)6U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_GPS_STS           */
    {(U2)7U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_VM3TO2_WHLINI_INF */
    {(U2)10U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_VM3TO2_WKUP_COND  */
    {(U2)11U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_VM3TO2_USRRST_MASK*/
    {(U2)12U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_VM3TO2_MONI_INF   */
    {(U2)13U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_2}      /* IVDSH_DID_REA_VM3TO2_VMRESET_RES*/
};
const U2                    u2_g_IVDSH_NUM_DID = (U2)IVDSH_NUM_DID;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_IVDSH_WA    st_sp_IVDSH_FQ_CH[IVDSH_NUM_FQ_CH] = {
    /* IVDSH_FQ_CH_REA_0 */
    {
        (U2)IVDSH_WA_NWORD_WRI,                                   /* u2_begin */
        (U2)IVDSH_WA_NWORD_REA_0,                                 /* u2_nword */
        (U2)EHVM_RX_VCCID_VCC_SHARED_TX_VM0                       /* u2_fq_ch */
    },
    /* IVDSH_FQ_CH_REA_1 */
    {
        ((U2)IVDSH_WA_NWORD_WRI          +                        /* u2_begin */
         ((U2)IVDSH_WA_NWORD_REA_0 << 1)),
        (U2)IVDSH_WA_NWORD_REA_1,                                 /* u2_nword */
        (U2)EHVM_RX_VCCID_VCC_SHARED_TX_VM1                       /* u2_fq_ch */
    },
    /* IVDSH_FQ_CH_REA_2 */
    {
        ((U2)IVDSH_WA_NWORD_WRI          +                        /* u2_begin */
         ((U2)IVDSH_WA_NWORD_REA_0 << 1) +
         ((U2)IVDSH_WA_NWORD_REA_1 << 1)),
        (U2)IVDSH_WA_NWORD_REA_2,                                 /* u2_nword */
        (U2)EHVM_RX_VCCID_VCC_SHARED_TX_VM3                       /* u2_fq_ch */
    },
    /* IVDSH_FQ_CH_WRI   */
    {
        (U2)0U,                                                   /* u2_begin */
        (U2)IVDSH_WA_NWORD_WRI,                                   /* u2_nword */
        (U2)EHVM_TX_VCCID_VCC_SHARED_TX_VM2                       /* u2_fq_ch */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_IVDSH_WA * const   stp_g_IVDSH_FQ_WRI    = &st_sp_IVDSH_FQ_CH[IVDSH_FQ_CH_WRI];
const ST_IVDSH_WA * const   stp_g_IVDSH_FQ_REA    = &st_sp_IVDSH_FQ_CH[IVDSH_FQ_CH_REA_0];
const U1                    u1_g_IVDSH_NUM_FQ_REA = (U1)IVDSH_NUM_FQ_REA;

#pragma ghs section rodata=default

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     6/23/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
