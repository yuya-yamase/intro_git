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
#define IVDSH_WA_NWORD_WRI                       (15U)
#define IVDSH_WA_NWORD_REA_0                     (6U)
#define IVDSH_WA_NWORD_REA_1                     (14U)
#define IVDSH_WA_NWORD_REA_2                     (7U)

#define IVDSH_WA_NWORD                           (69U)

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
    {(U2)0U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_003         */
    {(U2)1U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_009         */
    {(U2)2U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_011         */
    {(U2)3U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_013         */
    {(U2)4U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_015         */
    {(U2)5U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_017         */
    {(U2)6U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_019         */
    {(U2)7U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_020         */
    {(U2)8U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_024         */
    {(U2)9U,        (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_025         */
    {(U2)10U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_027         */
    {(U2)11U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_042         */
    {(U2)12U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_046         */
    {(U2)13U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_CPREQ_047         */
    {(U2)14U,       (U2)1U,         (U2)IVDSH_FQ_CH_WRI  },     /* IVDSH_DID_WRI_GPS_REQ           */
    /*------------------------------------------------------------------*/
    /* Read from VM#0                                                   */
    /*------------------------------------------------------------------*/
    {(U2)0U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_0},     /* IVDSH_DID_REA_CPREQ_006         */
    {(U2)1U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_0},     /* IVDSH_DID_REA_CPREQ_008         */
    {(U2)2U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_0},     /* IVDSH_DID_REA_CPREQ_029         */
    {(U2)3U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_0},     /* IVDSH_DID_REA_CPREQ_032         */
    {(U2)4U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_0},     /* IVDSH_DID_REA_CPREQ_035         */
    {(U2)5U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_0},     /* IVDSH_DID_REA_CPREQ_038         */
    /*------------------------------------------------------------------*/
    /* Read from VM#1                                                   */
    /*------------------------------------------------------------------*/
    {(U2)1U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_004         */
    {(U2)2U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_010         */
    {(U2)3U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_012         */
    {(U2)4U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_014         */
    {(U2)5U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_016         */
    {(U2)6U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_018         */
    {(U2)7U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_021         */
    {(U2)8U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_022         */
    {(U2)10U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_026         */
    {(U2)11U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_028         */
    {(U2)12U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_VM1TO2_FLYNOP     */
    {(U2)13U,       (U2)1U,         (U2)IVDSH_FQ_CH_REA_1},     /* IVDSH_DID_REA_CPREQ_044         */
    /*------------------------------------------------------------------*/
    /* Read from VM#3                                                   */
    /*------------------------------------------------------------------*/
    {(U2)0U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_CPREQ_005         */
    {(U2)1U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_CPREQ_007         */
    {(U2)2U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_CPREQ_043         */
    {(U2)3U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_CPREQ_045         */
    {(U2)4U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_CPREQ_048         */
    {(U2)5U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2},     /* IVDSH_DID_REA_CPREQ_049         */
    {(U2)6U,        (U2)1U,         (U2)IVDSH_FQ_CH_REA_2}      /* IVDSH_DID_REA_GPS_STS           */
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
