/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Tripcom Non-Volatile Memory Interface for M_DMGRPH                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NVMIF_GRPH_C_MAJOR              (1)
#define TRIPCOM_NVMIF_GRPH_C_MINOR              (0)
#define TRIPCOM_NVMIF_GRPH_C_PATCH              (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_cfg_private.h"
#include "tripcom_nvmif_grph_cfg_private.h"
#include "tripcom.h"
#include "lsbsrch.h"
#include "tripcom_calc.h"
#include "tripcom_ms.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPCOM_NVMIF_GRPH_C_MAJOR != TRIPCOM_NVMIF_GRPH_H_MAJOR) || \
     (TRIPCOM_NVMIF_GRPH_C_MINOR != TRIPCOM_NVMIF_GRPH_H_MINOR) || \
     (TRIPCOM_NVMIF_GRPH_C_PATCH != TRIPCOM_NVMIF_GRPH_H_PATCH))
#error "tripcom_nvmif_grph.c and tripcom_nvmif_grph.h : source and header files are inconsistent!"
#endif

#if ((TRIPCOM_NVMIF_GRPH_C_MAJOR != TRIPCOM_NVMIF_GRPH_CFG_H_MAJOR) || \
     (TRIPCOM_NVMIF_GRPH_C_MINOR != TRIPCOM_NVMIF_GRPH_CFG_H_MINOR) || \
     (TRIPCOM_NVMIF_GRPH_C_PATCH != TRIPCOM_NVMIF_GRPH_CFG_H_PATCH))
#error "tripcom_nvmif_grph.c and tripcom_nvmif_grph_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NVMIF_GRPH_RW_NUM_STS           (4U)
#define TRIPCOM_NVMIF_GRPH_RW_REQ_NEXT          (0U)
#define TRIPCOM_NVMIF_GRPH_RW_WRI_NEXT          (1U)
#define TRIPCOM_NVMIF_GRPH_RW_CMP_NEXT          (2U)
#define TRIPCOM_NVMIF_GRPH_RW_SYN_LAST          (3U)
#define TRIPCOM_NVMIF_GRPH_RW_SYN_INIT          (TRIPCOM_NVMIF_GRPH_RW_NUM_STS)

#define TRIPCOM_NVMIF_GRPH_CHK_SEQ_ABORT        (0x08U)
#define TRIPCOM_NVMIF_GRPH_CHK_OPE_CMPLT        (0x04U)
#define TRIPCOM_NVMIF_GRPH_CHK_REC_NEXT         (0x03U)
#define TRIPCOM_NVMIF_GRPH_CHK_REC_VALID        (0x02U)
#define TRIPCOM_NVMIF_GRPH_CHK_REC_INVAL        (0x01U)

#define TRIPCOM_NVMIF_GRPH_ACT_TO_SEQ_CMPLT     (0U)
#define TRIPCOM_NVMIF_GRPH_ACT_TO_REQ_NEXT      (1U)
#define TRIPCOM_NVMIF_GRPH_ACT_TO_CBK_NEXT      (2U)
#define TRIPCOM_NVMIF_GRPH_ACT_TO_SYN_CMPLT     (3U)
#define TRIPCOM_NVMIF_GRPH_ACT_WRI_NEXT         (4U)
#define TRIPCOM_NVMIF_GRPH_ACT_TO_WRI_NEXT      (5U)
#define TRIPCOM_NVMIF_GRPH_ACT_CMP_NEXT         (6U)
#define TRIPCOM_NVMIF_GRPH_ACT_TO_CMP_NEXT      (7U)
#define TRIPCOM_NVMIF_GRPH_ACT_SYN_LAST         (8U)
#define TRIPCOM_NVMIF_GRPH_ACT_TO_SYN_LAST      (9U)

#define TRIPCOM_NVMIF_GRPH_FIFO_MAX             (TRIPCOM_NVMIF_GRPH_CH_NUM)
#define TRIPCOM_NVMIF_GRPH_RW_RTRY_MAX          (2U)

#define TRIPCOM_NVMIF_GRPH_CMPR_A_EQ_B          (0U)
#define TRIPCOM_NVMIF_GRPH_CMPR_A_GT_B          (1U)
#define TRIPCOM_NVMIF_GRPH_CMPR_A_LT_B          (2U)
#define TRIPCOM_NVMIF_GRPH_CMPR_UNK             (3U)

#define TRIPCOM_NVMIF_GRPH_CRC32_INIT           (0xC410C712U)

#define TRIPCOM_NVMIF_GRPH_SFT_DIV32            (5U)
#define TRIPCOM_NVMIF_GRPH_MSK_MOD32            (0x1FU)
#define TRIPCOM_NVMIF_GRPH_U4_BITLEN            (32U)
#define TRIPCOM_NVMIF_GRPH_CMPRCHK_SIZE         (((TRIPCOM_NVMIF_GRPH_CH_NUM * TRIPCOM_NVMIF_GRPH_NUM_REC) / TRIPCOM_NVMIF_GRPH_U4_BITLEN) + 1U)

#define TRIPCOM_NVMIF_GRPH_DIAG_CTRL_CMP        (0x00U)
#define TRIPCOM_NVMIF_GRPH_DIAG_CTRL_WRI        (0x01U)
#define TRIPCOM_NVMIF_GRPH_DIAG_CTRL_FIN        (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_TRIPCOM_GRPH_NVMDATA          st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_NUM];
static ST_TRIPCOM_NVMIF_GRPH_RW_CTRL    st_s_tripcom_nvmif_grph_rw_ctrl;
static U1                               u1_s_tripcom_nvmif_grph_rdbk_cnt;
static U4                               u4_sp_tripcom_nvmif_grph_wrt_cnt[TRIPCOM_NVMIF_GRPH_CH_NUM];
static U4                               u4_s_tripcom_nvmif_grph_sync_reqbit;
static U1                               u1_s_tripcom_nvmif_grph_diag_ctrl;
static U1                               u1_s_tripcom_nvmif_grph_diag_req;
static U1                               u1_s_tripcom_nvmif_grph_diag_idx;
static U4                               u4_s_tripcom_nvmif_grph_diag_cmprchk[TRIPCOM_NVMIF_GRPH_CMPRCHK_SIZE];

static ST_TRIPCOM_GRPH_NVMDATA          st_sp_tripcom_nvmif_grph_fifo_data[TRIPCOM_NVMIF_GRPH_FIFO_MAX];
static U1                               u1_sp_tripcom_nvmif_grph_fifo_ch[TRIPCOM_NVMIF_GRPH_FIFO_MAX];
static ST_TRIPCOM_NVMIF_GRPH_FIFO_CTRL  st_s_tripcom_nvmif_grph_fifo_ctrl;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_TripcomNvmIfGrphSynInit(void);

static U1      u1_s_TripcomNvmIfGrphAbortchk(void);
static U1      u1_s_TripcomNvmIfGrphReqchk(void);
static U1      u1_s_TripcomNvmIfGrphWrichk(void);
static U1      u1_s_TripcomNvmIfGrphCmpchk(void);
static U1      u1_s_TripcomNvmIfGrphSynchk(void);

static void    vd_s_TripcomNvmIfGrphActToSeqCmplt(void);
static void    vd_s_TripcomNvmIfGrphActToReqNext(void);
static void    vd_s_TripcomNvmIfGrphActToCbkNext(void);
static void    vd_s_TripcomNvmIfGrphActToSynCmplt(void);
static void    vd_s_TripcomNvmIfGrphActWriNext(void);
static void    vd_s_TripcomNvmIfGrphActToWriNext(void);
static void    vd_s_TripcomNvmIfGrphActReaNext(void);
static void    vd_s_TripcomNvmIfGrphActToCmpNext(void);
static void    vd_s_TripcomNvmIfGrphActToSynLast(void);

static U1      u1_s_TripcomNvmIfGrphFifoPosIn(ST_TRIPCOM_NVMIF_GRPH_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX);
static U1      u1_s_TripcomNvmIfGrphFifoPosOut(ST_TRIPCOM_NVMIF_GRPH_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX);

static void    vd_s_TripcomNvmIfGrphWrite(const ST_TRIPCOM_NVMIF_GRPH_REC_DATA * st_ap_REC_DATA,
                                          const ST_TRIPCOM_NVMIF_GRPH_RW_CTRL * st_ap_CTRL,
                                          const U1 * u1_ap_DATA);
static void    vd_s_TripcomNvmIfGrphRead(const ST_TRIPCOM_NVMIF_GRPH_REC_DATA * st_ap_REC_DATA,
                                         const ST_TRIPCOM_NVMIF_GRPH_RW_CTRL * st_ap_CTRL);

static U1      u1_s_TripcomNvmIfGrphUnk(const ST_TRIPCOM_GRPH_NVMDATA * st_ap_DATA);
static U1      u1_s_TripcomNvmIfGrphCmprAwB(const ST_TRIPCOM_GRPH_NVMDATA * st_ap_CMPR_A,
                                            const ST_TRIPCOM_GRPH_NVMDATA * st_ap_CMPR_B);

static void    vd_s_TripcomNvmIfGrphCmprNvmDflt(const U1 u1_a_REC_IDX);
static U1      u1_s_TripcomNvmIfGrphLsbSrch(const U4 * u4_ap_SRCH, const U1 u1_a_BITLEN);
static void    vd_s_TripcomNvmGrphCrcChk(ST_TRIPCOM_GRPH_NVMDATA * st_a_rdbk);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_TRIPCOM_GRPH_NVMDATA    st_s_TRIPCOM_GRPH_NVMDFLT = {
    {(U4)0xFFFFFFFFU,                       /* u4_value[0] */
     (U4)0xFFFFFFFFU,                       /* u4_value[1] */
     (U4)0xFFFFFFFFU,                       /* u4_value[2] */
     (U4)0xFFFFFFFFU,                       /* u4_value[3] */
     (U4)0xFFFFFFFFU,                       /* u4_value[4] */
     (U4)0xFFFFFFFFU},                      /* u4_value[5] */
    (U4)0x00000000U,                        /* u4_wrt_cnt  */
    (U4)TRIPCOM_NVMIF_GRPH_CRC32_INIT       /* u4_crc32    */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfGrphInit(const U1 u1_a_SYNC)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TripcomNvmIfGrphInit(const U1 u1_a_SYNC)
{
    U4                      u4_t_lpcnt;
    U4                      u4_t_lpcnt2;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_RW_DAT_NUM; u4_t_lpcnt++){
        for(u4_t_lpcnt2 = (U4)0U; u4_t_lpcnt2 < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt2++){
            st_sp_tripcom_nvmif_grph_rw_data[u4_t_lpcnt].u4_value[u4_t_lpcnt2] = (U4)TRIPCOM_NVMIF_GRPH_UNK;
        }
        st_sp_tripcom_nvmif_grph_rw_data[u4_t_lpcnt].u4_wrt_cnt = (U4)TRIPCOM_NVMIF_GRPH_UNK;
        st_sp_tripcom_nvmif_grph_rw_data[u4_t_lpcnt].u4_crc32   = (U4)TRIPCOM_NVMIF_GRPH_UNK;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_CH_NUM; u4_t_lpcnt++){
        u4_sp_tripcom_nvmif_grph_wrt_cnt[u4_t_lpcnt] = (U4)TRIPCOM_NVMIF_GRPH_UNK;
    }

    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx  = (U1)U1_MAX;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_mrk  = (U1)U1_MAX;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt  = (U1)0U;

    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_GRPH_RW_SYN_INIT;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt = (U2)1U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u4_crc32    = (U4)0U;

    u1_s_tripcom_nvmif_grph_rdbk_cnt            = (U1)0U;
    u1_s_tripcom_nvmif_grph_diag_ctrl           = (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_FIN;
    u1_s_tripcom_nvmif_grph_diag_req            = (U1)U1_MAX;
    u1_s_tripcom_nvmif_grph_diag_idx            = (U1)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_FIFO_MAX; u4_t_lpcnt++){
        for(u4_t_lpcnt2 = (U4)0U; u4_t_lpcnt2 < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt2++){
            st_sp_tripcom_nvmif_grph_fifo_data[u4_t_lpcnt].u4_value[u4_t_lpcnt2] = (U4)TRIPCOM_NVMIF_GRPH_UNK;
        }
        st_sp_tripcom_nvmif_grph_fifo_data[u4_t_lpcnt].u4_wrt_cnt = (U4)TRIPCOM_NVMIF_GRPH_UNK;
        st_sp_tripcom_nvmif_grph_fifo_data[u4_t_lpcnt].u4_crc32   = (U4)TRIPCOM_NVMIF_GRPH_UNK;
        u1_sp_tripcom_nvmif_grph_fifo_ch[u4_t_lpcnt]              = (U1)U1_MAX;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_CMPRCHK_SIZE; u4_t_lpcnt++){
        u4_s_tripcom_nvmif_grph_diag_cmprchk[u4_t_lpcnt] = (U4)0U;
    }

    st_s_tripcom_nvmif_grph_fifo_ctrl.u2_len     = (U2)0U;
    st_s_tripcom_nvmif_grph_fifo_ctrl.u1_pos_in  = (U1)0U;
    st_s_tripcom_nvmif_grph_fifo_ctrl.u1_pos_out = (U1)0U;

    if(u1_a_SYNC == (U1)TRUE){
        u4_s_tripcom_nvmif_grph_sync_reqbit = (U4)0U;
        vd_s_TripcomNvmIfGrphSynInit();
    }
    else{
        u4_s_tripcom_nvmif_grph_sync_reqbit = ((U4)1U << TRIPCOM_NVMIF_GRPH_CH_NUM) - (U4)1U;
        vd_g_TripcomNvmIfGrphRWAct();
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_TripcomNvmIfGrphRWRqst(const U1 u1_a_CH, const U4 * u4_ap_NEXT)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TripcomNvmIfGrphRWRqst(const U1 u1_a_CH, const U4 * u4_ap_NEXT)
{
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_next;

    U1                        u1_t_fifo_in;
    U1                        u1_t_accpt;
    U4                        u4_t_lpcnt;

    u1_t_fifo_in = u1_s_TripcomNvmIfGrphFifoPosIn(&st_s_tripcom_nvmif_grph_fifo_ctrl, (U1)TRIPCOM_NVMIF_GRPH_FIFO_MAX);
    if((u1_t_fifo_in < (U1)TRIPCOM_NVMIF_GRPH_FIFO_MAX) &&
       (u1_a_CH      < (U1)TRIPCOM_NVMIF_GRPH_CH_NUM  )){

        u1_sp_tripcom_nvmif_grph_fifo_ch[u1_t_fifo_in] = u1_a_CH;

        st_tp_next = &st_sp_tripcom_nvmif_grph_fifo_data[u1_t_fifo_in];
        if((u4_ap_NEXT                                == vdp_PTR_NA                ) ||
           (u4_sp_tripcom_nvmif_grph_wrt_cnt[u1_a_CH] == (U4)TRIPCOM_NVMIF_GRPH_UNK)){
            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
                st_tp_next->u4_value[u4_t_lpcnt] = (U4)TRIPCOM_NVMIF_GRPH_UNK;
            }
            st_tp_next->u4_wrt_cnt = (U4)TRIPCOM_NVMIF_GRPH_UNK;
            st_tp_next->u4_crc32   = (U4)TRIPCOM_NVMIF_GRPH_UNK;
        }
        else{
            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
                st_tp_next->u4_value[u4_t_lpcnt] = (* u4_ap_NEXT);
                u4_ap_NEXT++;
            }
            st_tp_next->u4_wrt_cnt = u4_sp_tripcom_nvmif_grph_wrt_cnt[u1_a_CH];
            st_tp_next->u4_crc32   = u4_g_TripcomNvmIfGrphCrc32((const U1 *)st_tp_next,
                                                                ((U4)sizeof(ST_TRIPCOM_GRPH_NVMDATA) - (U4)TRIPCOM_NVMIF_GRPH_NBYTE_CRC_32));
        }

        u4_s_tripcom_nvmif_grph_sync_reqbit |= ((U4)1U << u1_a_CH);
        vd_g_TripcomNvmIfGrphRWAct();

        u1_t_accpt = (U1)TRUE;
    }
    else{
        u1_t_accpt = (U1)FALSE;
    }

    return(u1_t_accpt);
}
/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfGrphRWTask(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TripcomNvmIfGrphRWTask(void)
{
    static U1 ( * const     fp_sp_u1_TRIPCOM_NVMIF_GRPH_CHK[TRIPCOM_NVMIF_GRPH_RW_NUM_STS])(void) = {
        &u1_s_TripcomNvmIfGrphReqchk,
        &u1_s_TripcomNvmIfGrphWrichk,
        &u1_s_TripcomNvmIfGrphCmpchk,
        &u1_s_TripcomNvmIfGrphSynchk
    };

    static const U1         u1_sp_TRIPCOM_NVMIF_GRPH_RW_STM[] = {
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_REQ_NEXT,  (U1)TRIPCOM_NVMIF_GRPH_ACT_WRI_NEXT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_CMP_NEXT,     (U1)TRIPCOM_NVMIF_GRPH_ACT_SYN_LAST,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_SYN_LAST,  (U1)TRIPCOM_NVMIF_GRPH_ACT_WRI_NEXT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_CMP_NEXT,     (U1)TRIPCOM_NVMIF_GRPH_ACT_SYN_LAST,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_WRI_NEXT,  (U1)TRIPCOM_NVMIF_GRPH_ACT_WRI_NEXT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_CMP_NEXT,     (U1)TRIPCOM_NVMIF_GRPH_ACT_SYN_LAST,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_REQ_NEXT,  (U1)TRIPCOM_NVMIF_GRPH_ACT_WRI_NEXT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_CMP_NEXT,     (U1)TRIPCOM_NVMIF_GRPH_ACT_SYN_LAST,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_SEQ_CMPLT, (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_CMP_NEXT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_REQ_NEXT,  (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_SYN_CMPLT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_SEQ_CMPLT, (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_CMP_NEXT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_CMP_NEXT,     (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_SYN_CMPLT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_SEQ_CMPLT, (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_CMP_NEXT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_CBK_NEXT,  (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_SYN_CMPLT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_SEQ_CMPLT, (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_CMP_NEXT,
        (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_REQ_NEXT,  (U1)TRIPCOM_NVMIF_GRPH_ACT_TO_SYN_CMPLT
    };

    static void ( * const   fp_vd_TRIPCOM_NVMIF_GRPH_ACT[])(void) = {
        &vd_s_TripcomNvmIfGrphActToSeqCmplt,                  /* TRIPCOM_NVMIF_ACT_TO_SEQ_CMPLT (0U) */
        &vd_s_TripcomNvmIfGrphActToReqNext,                   /* TRIPCOM_NVMIF_ACT_TO_REQ_NEXT  (1U) */
        &vd_s_TripcomNvmIfGrphActToCbkNext,                   /* TRIPCOM_NVMIF_ACT_TO_CBK_NEXT  (2U) */
        &vd_s_TripcomNvmIfGrphActToSynCmplt,                  /* TRIPCOM_NVMIF_ACT_TO_SYN_CMPLT (3U) */
        &vd_s_TripcomNvmIfGrphActWriNext,                     /* TRIPCOM_NVMIF_ACT_WRI_NEXT     (4U) */
        &vd_s_TripcomNvmIfGrphActToWriNext,                   /* TRIPCOM_NVMIF_ACT_TO_WRI_NEXT  (5U) */
        &vd_s_TripcomNvmIfGrphActReaNext,                     /* TRIPCOM_NVMIF_ACT_CMP_NEXT     (6U) */
        &vd_s_TripcomNvmIfGrphActToCmpNext,                   /* TRIPCOM_NVMIF_ACT_TO_CMP_NEXT  (7U) */
        &vd_s_TripcomNvmIfGrphActReaNext,                     /* TRIPCOM_NVMIF_ACT_SYN_LAST     (8U) */
        &vd_s_TripcomNvmIfGrphActToSynLast                    /* TRIPCOM_NVMIF_ACT_TO_SYN_LAST  (9U) */
    };

    U4                      u4_t_crc32;
    U2                      u2_t_rw_act;
    U2                      u2_t_rw_ctrl;
    U1                      u1_t_sts_chk;

    u1_t_sts_chk = u1_s_TripcomNvmIfGrphAbortchk();
    if(u1_t_sts_chk == (U1)0U){

        u2_t_rw_ctrl = st_s_tripcom_nvmif_grph_rw_ctrl.u2_rw_ctrl;
        u1_t_sts_chk = (fp_sp_u1_TRIPCOM_NVMIF_GRPH_CHK[u2_t_rw_ctrl])();
        u2_t_rw_act  = ((U2)u1_t_sts_chk * (U2)TRIPCOM_NVMIF_GRPH_RW_NUM_STS) + u2_t_rw_ctrl;
        u2_t_rw_act  = (U2)u1_sp_TRIPCOM_NVMIF_GRPH_RW_STM[u2_t_rw_act];
    }
    else{
        u2_t_rw_act  = (U2)TRIPCOM_NVMIF_GRPH_ACT_TO_SYN_LAST;
    }

    (*fp_vd_TRIPCOM_NVMIF_GRPH_ACT[u2_t_rw_act])();

    u4_t_crc32 = u4_g_TripcomNvmIfGrphCrc32((U1 *)&st_s_tripcom_nvmif_grph_rw_ctrl,
                                            ((U4)sizeof(ST_TRIPCOM_NVMIF_GRPH_RW_CTRL) - (U4)TRIPCOM_NVMIF_GRPH_NBYTE_CRC_32));
    st_s_tripcom_nvmif_grph_rw_ctrl.u4_crc32 = u4_t_crc32;
}
/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfGrphRWFinhk(const U2 u2_a_BLOCKID,                                                                      */
/*                                       const U1 u1_a_REQUEST_TYPE,                                                                 */
/*                                       const U1 u1_a_RESULT,                                                                       */
/*                                       const U1 * const u1_ap_DATA,                                                                */
/*                                       const U2 u2_a_SIZE)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TripcomNvmIfGrphRWFinhk(const U2 u2_a_BLOCKID,
                                     const U1 u1_a_REQUEST_TYPE,
                                     const U1 u1_a_RESULT,
                                     const U1 * const u1_ap_DATA,
                                     const U2 u2_a_SIZE)
{
    U1 *                    u1_tp_dst;

    U4                      u4_t_lpcnt;

    U2                      u2_t_rdbk_offset;

    U1                      u1_t_rec_nblock;
    U1                      u1_t_blo_nbyte;
    U1                      u1_t_blo_cnt;
    U4                      u4_t_value;

    u1_t_rec_nblock = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_rec_nblock;
    u1_t_blo_nbyte  = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_blo_nbyte;
    u1_t_blo_cnt    = st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt;

    if((u1_a_REQUEST_TYPE == (U1)TRIPCOM_NVMIF_GRPH_REQ_TYPE_READ) &&
       (u1_a_RESULT       == (U1)TRIPCOM_NVMIF_GRPH_JOB_RESULT_OK) &&
       (u1_ap_DATA        != vdp_PTR_NA                          ) &&
       (u2_a_SIZE         == (U2)u1_t_blo_nbyte                  ) &&
       (u1_t_blo_cnt      <  u1_t_rec_nblock                     )){

        u2_t_rdbk_offset = (U2)u1_t_blo_cnt * (U2)u1_t_blo_nbyte;
        u1_tp_dst        = (U1 *)&st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_RDBK];
        u1_tp_dst        = &u1_tp_dst[u2_t_rdbk_offset];
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_t_blo_nbyte; u4_t_lpcnt++){
            u1_tp_dst[u4_t_lpcnt] = u1_ap_DATA[u4_t_lpcnt];
        }

        u4_t_value = (U4)0U;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
            u4_t_value |= st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_RDBK].u4_value[u4_t_lpcnt];
        }
        if((u1_s_tripcom_nvmif_grph_diag_ctrl != (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_CMP            ) &&
           (st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_RDBK].u4_crc32   == (U4)0U) &&
           (st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_RDBK].u4_wrt_cnt == (U4)0U) &&
           (u4_t_value                                                                  == (U4)0U)){
            st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_RDBK].u4_crc32 = (U4)TRIPCOM_NVMIF_GRPH_CRC32_INIT;
        }

        if(u1_s_tripcom_nvmif_grph_rdbk_cnt < (U1)U1_MAX){
            u1_s_tripcom_nvmif_grph_rdbk_cnt++;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfGrphDiagStart(const U1 u1_a_REQ)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TripcomNvmIfGrphDiagStart(const U1 u1_a_REQ)
{
    U4                      u4_t_loop;

    if(u1_s_tripcom_nvmif_grph_diag_ctrl >= (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_FIN){
        u1_s_tripcom_nvmif_grph_diag_req  = u1_a_REQ;
        u1_s_tripcom_nvmif_grph_diag_ctrl = (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_CMP;

        for(u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_GRPH_CMPRCHK_SIZE; u4_t_loop++){
            u4_s_tripcom_nvmif_grph_diag_cmprchk[u4_t_loop] = (U4)0U;
        }

        for(u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_GRPH_CH_NUM; u4_t_loop++){
            (void)u1_g_TripcomNvmIfGrphRWRqst((U1)u4_t_loop, vdp_PTR_NA);
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphSynInit(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphSynInit(void)
{
    const U2 *                u2_tp_BLOCK;
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_last;

    ST_TRIPCOM_GRPH_NVMDATA   st_t_rdbk;
    U1 *                      u1_tp_rdbk;

    U4                        u4_t_num_rec;
    U4                        u4_t_rec_nblock;
    U4                        u4_t_rec_idx;
    U4                        u4_t_rec_mrk;
    U4                        u4_t_rec_end;

    U4                        u4_t_blo_idx;
    U4                        u4_t_blo_end;

    U4                        u4_t_rtry_cnt;
    U4                        u4_t_crc32;

    U2                        u2_t_blo_nbyte;
    U2                        u2_t_rdbk_offset;

    U1                        u1_t_dev_idx;
    U1                        u1_t_rdrslt;
    U1                        u1_t_unk;
    U1                        u1_t_cmpr;

    U4                        u4_t_ch;
    U4                        u4_t_lpcnt;

    st_tp_last           = &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST];

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
        st_t_rdbk.u4_value[u4_t_lpcnt] = (U4)TRIPCOM_NVMIF_GRPH_UNK;
    }
    st_t_rdbk.u4_wrt_cnt = (U4)TRIPCOM_NVMIF_GRPH_UNK;
    st_t_rdbk.u4_crc32   = (U4)TRIPCOM_NVMIF_GRPH_UNK;
    u1_tp_rdbk           = (U1 *)&st_t_rdbk;

    u4_t_rec_mrk         = (U4)U4_MAX;

    u2_tp_BLOCK          = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u2p_BLOCK;
    u4_t_num_rec         = (U4)st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_num_rec;
    u4_t_rec_nblock      = (U4)st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_rec_nblock;
    u2_t_blo_nbyte       = (U2)st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_blo_nbyte;
    u1_t_dev_idx         = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_dev_idx;

    u4_t_rec_idx         = (U4)0U;
    u4_t_rec_end         = (U4)TRIPCOM_NVMIF_GRPH_NUM_REC;
    u4_t_rtry_cnt        = (U4)1U;
    u4_t_ch              = (U1)0U;

    do{

        u4_t_blo_idx     = u4_t_rec_idx * u4_t_rec_nblock;
        /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.               */
        /* The source of u4_t_num_rec is st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec, so the max value of u4_t_num_rec is 255.            */
        /* Therefor the max value u4_t_rec_idx is 255                                                                                */
        /* The source of u4_t_rec_nblock is st_g_TRIPCOM_NVMIF_REC_DATA.u1_rec_nblock, so the max value of u4_t_rec_nblock is 255.   */
        /* The max value of (u4_t_rec_idx * u4_t_rec_nblock) is 255*255=65025, therefor it is not necessary to check the wraparound. */

        u4_t_blo_end     = u4_t_blo_idx + u4_t_rec_nblock;
        /* The max value of u4_t_blo_idx is 255*255 = 65025                                                                          */
        /* The source of u4_t_rec_nblock is st_g_TRIPCOM_NVMIF_REC_DATA.u1_rec_nblock, so the max value of u4_t_rec_nblock is 255.   */
        /* The max value of (u4_t_blo_idx + u4_t_rec_nblock) is 65025+255=65280, therefor it is not necessary to check the wraparound.*/

        u2_t_rdbk_offset = (U2)0U;

        do{
            u1_t_rdrslt = u1_g_TripcomNvmIfGrphSyncBlock(u1_t_dev_idx,
                                                         u2_tp_BLOCK[u4_t_blo_idx],
                                                         &u1_tp_rdbk[u2_t_rdbk_offset],
                                                         u2_t_blo_nbyte);

            u2_t_rdbk_offset += u2_t_blo_nbyte;
            /* The source of u2_t_blo_nbyte is st_g_TRIPCOM_NVMIF_REC_DATA.u1_blo_nbyte, so the max value of u2_t_blo_nbyte is 255.  */
            /* The number of times u2_t_blo_nbyte is accumulated is (u4_t_blo_end - u4_t_blo_idx) times.                             */
            /* u4_t_blo_end - u4_t_blo_idx = u4_t_blo_idx + u4_t_rec_nblock - u4_t_blo_idx = u4_t_rec_nblock.                        */
            /* The source of u4_t_rec_nblock is st_g_TRIPCOM_NVMIF_REC_DATA.u1_rec_nblock, so the max value of u4_t_rec_nblock is 255.*/
            /* In other words, 255(=u2_t_blo_nbyte) will be accumulated 255(= (u4_t_blo_end - u4_t_blo_idx)) times at the maximum,   */
            /* The maximum value of u2_t_rdbk_offset is 65025, therefor it is not necessary to check the wraparound.                 */

            if(u1_t_rdrslt == (U1)TRIPCOM_NVMIF_GRPH_JOB_RESULT_OK){
                u4_t_blo_idx++;
                /* The value of u4_t_blo_idx is determined whether it is smaller than u4_t_blo_end within the while condition.       */
                /* The max value of u4_t_blo_end is 65280, , therefor it is not necessary to check the wraparound.                   */
            }
            else{
                u4_t_blo_idx = (U4)U4_MAX;
            }
        }
        while(u4_t_blo_idx < u4_t_blo_end);

        vd_s_TripcomNvmGrphCrcChk(&st_t_rdbk);

        u1_t_unk = u1_s_TripcomNvmIfGrphUnk(&st_t_rdbk);
        if((u4_t_blo_idx == u4_t_blo_end) &&
           (u1_t_unk     == (U1)FALSE   )){

            u1_t_cmpr = u1_s_TripcomNvmIfGrphCmprAwB(&st_t_rdbk, st_tp_last);
            if((u4_t_rec_mrk >= u4_t_num_rec                 ) ||
            /* u1_t_cmpr == TRIPCOM_NVMIF_CMPR_A_GT_B or TRIPCOM_NVMIF_CMPR_A_EQ_B */
               (u1_t_cmpr    <= (U1)TRIPCOM_NVMIF_GRPH_CMPR_A_GT_B)){

               u4_t_rec_mrk = u4_t_rec_idx;

               for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
                   st_tp_last->u4_value[u4_t_lpcnt] = st_t_rdbk.u4_value[u4_t_lpcnt];
               }
               st_tp_last->u4_wrt_cnt = st_t_rdbk.u4_wrt_cnt;
               st_tp_last->u4_crc32   = st_t_rdbk.u4_crc32;
            }

            u4_t_rec_idx++;
            /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.           */
            /* The source of u4_t_num_rec is st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec, so the max value of u4_t_num_rec is 255.        */
            /* Therefor it is not necessary to check the wraparound.                                                                 */

            u4_t_rtry_cnt = (U4)1U;
        }
        else if(u4_t_rtry_cnt >= (U4)TRIPCOM_NVMIF_GRPH_RW_RTRY_MAX){
            u4_t_rec_idx++;
            /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.           */
            /* The source of u4_t_num_rec is st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec, so the max value of u4_t_num_rec is 255.        */
            /* Therefor it is not necessary to check the wraparound.                                                                 */

            u4_t_rtry_cnt = (U4)1U;
        }
        else{
            u4_t_rtry_cnt++;
            /* The value of u4_t_rtry_cnt is determined whether it is larger than TRIPCOM_NVMIF_RW_RTRY_MAX within the if condition. */
            /* Therefor it is not necessary to check the wraparound.                                                                 */
        }

        if(u4_t_rec_idx >= u4_t_rec_end){
            if(u4_t_rec_mrk != (U4)U4_MAX){
                u4_sp_tripcom_nvmif_grph_wrt_cnt[u4_t_ch] = u4_g_TripcomCalcAddU4U4(st_tp_last->u4_wrt_cnt, (U4)1U);
                vd_g_TripcomNvmIfGrphCbkData((U1)u4_t_ch, st_tp_last);
            }
            else{
                u4_sp_tripcom_nvmif_grph_wrt_cnt[u4_t_ch]  = (U4)0U;
                vd_g_TripcomNvmIfGrphCbkData((U1)u4_t_ch, vdp_PTR_NA);
            }

            if(u4_t_rec_idx < u4_t_num_rec){
                u4_t_ch++;
                /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.       */
                /* The source of u4_t_num_rec is st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec, so the max value of u4_t_num_rec is 255.    */
                /* This also occurs up to 255 times, so the maximum value is 255.                                                    */
                /* Therefor it is not necessary to check the wraparound.                                                             */
                u4_t_rec_mrk  = (U4)U4_MAX;
                u4_t_rec_end += (U4)TRIPCOM_NVMIF_GRPH_NUM_REC;
                /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.       */
                /* The source of u4_t_num_rec is st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec, so the max value of u4_t_num_rec is 255.    */
                /* This also occurs up to 255 times, so the maximum value is 6*255 = 1530.                                           */
                /* Therefor it is not necessary to check the wraparound.                                                             */
            }
        }
    }
    while(u4_t_rec_idx < u4_t_num_rec);

    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx = (U1)u4_t_rec_mrk;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rw_ctrl = (U2)TRIPCOM_NVMIF_GRPH_RW_REQ_NEXT;

    u4_t_crc32 = u4_g_TripcomNvmIfGrphCrc32((const U1 *)&st_s_tripcom_nvmif_grph_rw_ctrl,
                                            ((U4)sizeof(ST_TRIPCOM_NVMIF_GRPH_RW_CTRL) - (U4)TRIPCOM_NVMIF_GRPH_NBYTE_CRC_32));
    st_s_tripcom_nvmif_grph_rw_ctrl.u4_crc32 = u4_t_crc32;
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfGrphAbortchk(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfGrphAbortchk(void)
{
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_last;

    U4                        u4_t_crc32;

    U2                        u2_t_rw_ctrl;

    U1                        u1_t_num_rec;
    U1                        u1_t_rec_nblock;
    U1                        u1_t_rec_idx;
    U1                        u1_t_blo_cnt;
    U1                        u1_t_unk;
    U1                        u1_t_sts_chk;

    u1_t_sts_chk = (U1)0x00U;

    u4_t_crc32   = u4_g_TripcomNvmIfGrphCrc32((U1 *)&st_s_tripcom_nvmif_grph_rw_ctrl,
                                              ((U4)sizeof(ST_TRIPCOM_NVMIF_GRPH_RW_CTRL) - (U4)TRIPCOM_NVMIF_GRPH_NBYTE_CRC_32));

    u1_t_num_rec    = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_num_rec;
    u1_t_rec_nblock = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_rec_nblock;

    u1_t_rec_idx    = st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx;
    u1_t_blo_cnt    = st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt;
    u2_t_rw_ctrl    = st_s_tripcom_nvmif_grph_rw_ctrl.u2_rw_ctrl;

    if((st_s_tripcom_nvmif_grph_rw_ctrl.u4_crc32 != u4_t_crc32                       ) ||
       (u2_t_rw_ctrl                             >= (U2)TRIPCOM_NVMIF_GRPH_RW_NUM_STS) ||
       (u1_t_rec_idx                             >= u1_t_num_rec                     ) ||
       (u1_t_blo_cnt                             >= u1_t_rec_nblock                  )){

        u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_SEQ_ABORT;
    }
    else if((u2_t_rw_ctrl                      <  (U2)TRIPCOM_NVMIF_GRPH_RW_SYN_LAST  ) &&
            (u1_s_tripcom_nvmif_grph_diag_ctrl != (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_WRI)){

        st_tp_last = &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST];
        u1_t_unk   = u1_s_TripcomNvmIfGrphUnk(st_tp_last);
        if(u1_t_unk != (U1)FALSE){
            
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_SEQ_ABORT;
        }
    }
    else{
        /* do nothing */
    }

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfGrphReqchk(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfGrphReqchk(void)
{
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_last;
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_next;

    U1                        u1_t_rec_idx;
    U1                        u1_t_ch;
    U1                        u1_t_num_rec;

    U1                        u1_t_fifo_out;
    U1                        u1_t_unk;

    U1                        u1_t_sts_chk;

    U1                        u1_t_ary_pos;
    U1                        u1_t_bit_pos;
    U1                        u1_t_diag_idx;
    U1                        u1_t_mul;

    U4                        u4_t_lpcnt;


    u1_t_fifo_out = u1_s_TripcomNvmIfGrphFifoPosOut(&st_s_tripcom_nvmif_grph_fifo_ctrl, (U1)TRIPCOM_NVMIF_GRPH_FIFO_MAX);
    if(u1_t_fifo_out >= (U1)TRIPCOM_NVMIF_GRPH_FIFO_MAX){
        u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_OPE_CMPLT;
    }
    else{

        st_tp_last = &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST];
        st_tp_next = &st_sp_tripcom_nvmif_grph_fifo_data[u1_t_fifo_out];
        u1_t_ch    = u1_sp_tripcom_nvmif_grph_fifo_ch[u1_t_fifo_out];

        u1_t_unk = u1_s_TripcomNvmIfGrphUnk(st_tp_next);

        if(u1_s_tripcom_nvmif_grph_diag_ctrl == (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_WRI){

            st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx = u1_s_tripcom_nvmif_grph_diag_idx;

            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
                st_tp_last->u4_value[u4_t_lpcnt] = st_s_TRIPCOM_GRPH_NVMDFLT.u4_value[u4_t_lpcnt];
            }
            st_tp_last->u4_wrt_cnt = st_s_TRIPCOM_GRPH_NVMDFLT.u4_wrt_cnt;
            st_tp_last->u4_crc32   = st_s_TRIPCOM_GRPH_NVMDFLT.u4_crc32;

            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_VALID;

            /* reset cmprchk flag */
            u1_t_rec_idx = u1_s_tripcom_nvmif_grph_diag_idx;
            u1_t_ary_pos = u1_t_rec_idx >> TRIPCOM_NVMIF_GRPH_SFT_DIV32;
            u1_t_bit_pos = u1_t_rec_idx  & (U1)TRIPCOM_NVMIF_GRPH_MSK_MOD32;
            u4_s_tripcom_nvmif_grph_diag_cmprchk[u1_t_ary_pos] &= ((U4)U4_MAX ^ ((U4)1U << u1_t_bit_pos));

            /* search next idx */
            u1_t_num_rec  = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_num_rec;
            u1_t_diag_idx = u1_s_TripcomNvmIfGrphLsbSrch(&u4_s_tripcom_nvmif_grph_diag_cmprchk[0], u1_t_num_rec);
            if(u1_t_diag_idx < u1_t_num_rec){
                u1_s_tripcom_nvmif_grph_diag_idx = u1_t_diag_idx;
                /* dummy request to continue diag nvm writting */
                (void)u1_s_TripcomNvmIfGrphFifoPosIn(&st_s_tripcom_nvmif_grph_fifo_ctrl, (U1)TRIPCOM_NVMIF_GRPH_FIFO_MAX);
            }
            else{
                vd_g_TripcomNvmIfGrphDiagFinish((U1)TRUE);
                u1_s_tripcom_nvmif_grph_diag_ctrl = (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_FIN;
            }
        }
        else if(u1_t_unk != (U1)FALSE){
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_INVAL;
        }
        else if(u1_t_ch < (U1)TRIPCOM_NVMIF_GRPH_CH_NUM){

            u1_t_rec_idx = (U1)(st_tp_next->u4_wrt_cnt % (U4)TRIPCOM_NVMIF_GRPH_NUM_REC);
            u1_t_mul     = u1_g_TripcomCalcMulU1U1(u1_t_ch, (U1)TRIPCOM_NVMIF_GRPH_NUM_REC);
            u1_t_rec_idx = u1_g_TripcomCalcAddU1U1(u1_t_rec_idx, u1_t_mul);

            st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx = u1_t_rec_idx;

            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
                st_tp_last->u4_value[u4_t_lpcnt] = st_tp_next->u4_value[u4_t_lpcnt];
            }
            st_tp_last->u4_wrt_cnt = st_tp_next->u4_wrt_cnt;
            st_tp_last->u4_crc32   = st_tp_next->u4_crc32;

            if(u4_sp_tripcom_nvmif_grph_wrt_cnt[u1_t_ch] < (U4)U4_MAX){
                u4_sp_tripcom_nvmif_grph_wrt_cnt[u1_t_ch]++;
            }

            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
                st_tp_next->u4_value[u4_t_lpcnt] = (U4)TRIPCOM_NVMIF_GRPH_UNK;
            }
            st_tp_next->u4_wrt_cnt = (U4)TRIPCOM_NVMIF_GRPH_UNK;
            st_tp_next->u4_crc32   = (U4)TRIPCOM_NVMIF_GRPH_UNK;

            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_VALID;
        }
        else{
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_NEXT;
        }
    }

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfGrphWrichk(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfGrphWrichk(void)
{
    U1                      u1_t_rec_nblock;
    U1                      u1_t_blo_next;
    U1                      u1_t_sts_chk;

    u1_t_rec_nblock = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_rec_nblock;
    u1_t_blo_next   = st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt + (U1)1U;

    if(u1_t_blo_next >= u1_t_rec_nblock){
        u1_t_sts_chk  = (U1)TRIPCOM_NVMIF_GRPH_CHK_OPE_CMPLT;
        u1_t_blo_next = (U1)0U;
    }
    else{
        u1_t_sts_chk = (U1)0x00U;
    }

    st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt  = u1_t_blo_next;

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfGrphCmpchk(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfGrphCmpchk(void)
{
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_last;
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_rdbk;

    U2                        u2_t_rtry_cnt;

    U1                        u1_t_rec_nblock;
    U1                        u1_t_blo_next;
    U1                        u1_t_cmpr;
    U1                        u1_t_sts_chk;

    u1_t_rec_nblock = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_rec_nblock;
    u1_t_blo_next   = st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt + (U1)1U;
    u2_t_rtry_cnt   = st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt;

    if(u1_t_blo_next >= u1_t_rec_nblock){

        st_tp_last = &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST];
        st_tp_rdbk = &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_RDBK];
        u1_t_cmpr  = u1_s_TripcomNvmIfGrphCmprAwB(st_tp_rdbk, st_tp_last);

        if((u1_t_rec_nblock == u1_s_tripcom_nvmif_grph_rdbk_cnt) &&
           (u1_t_cmpr       == (U1)TRIPCOM_NVMIF_GRPH_CMPR_A_EQ_B)){
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_OPE_CMPLT | (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_VALID;
            vd_g_TripcomMsSetNvmGrphRslt(st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx / (U1)TRIPCOM_NVMIF_GRPH_NUM_REC,
                                         (U1)TRIPCOM_MS_NVMSTS_SUC);
        }
        else if(u2_t_rtry_cnt >= (U2)TRIPCOM_NVMIF_GRPH_RW_RTRY_MAX){
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_OPE_CMPLT | (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_NEXT;
            vd_g_TripcomMsSetNvmGrphRslt(st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx / (U1)TRIPCOM_NVMIF_GRPH_NUM_REC,
                                         (U1)TRIPCOM_MS_NVMSTS_FAIL);
        }
        else{
            u2_t_rtry_cnt++;
            /* The value of u4_t_rtry_cnt is determined whether it is larger than TRIPCOM_NVMIF_RW_RTRY_MAX within the if condition. */
            /* Therefor it is not necessary to check the wraparound.                                                                 */
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_OPE_CMPLT | (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_INVAL;
        }

        u1_t_blo_next                    = (U1)0U;
        u1_s_tripcom_nvmif_grph_rdbk_cnt = (U1)0U;
    }
    else{
        u1_t_sts_chk = (U1)0x00U;
    }

    st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt  = u1_t_blo_next;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt = u2_t_rtry_cnt;

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfGrphSynchk(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfGrphSynchk(void)
{
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_last;
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_rdbk;

    U2                        u2_t_rtry_cnt;

    U1                        u1_t_num_rec;
    U1                        u1_t_rec_nblock;
    U1                        u1_t_blo_next;
    U1                        u1_t_rec_idx;
    U1                        u1_t_rec_end;
    U1                        u1_t_rec_mrk;
    U1                        u1_t_unk;
    U1                        u1_t_cmpr;
    U1                        u1_t_sts_chk;
    U1                        u1_t_ch;
    U1                        u1_t_ch_next;

    U4                        u4_t_lpcnt;

    u1_t_sts_chk    = (U1)0x00U;

    u1_t_num_rec    = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_num_rec;
    u1_t_rec_nblock = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_rec_nblock;

    u1_t_rec_idx    = st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx;
    u1_t_rec_mrk    = st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_mrk;
    u1_t_blo_next   = st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt + (U1)1U;
    u2_t_rtry_cnt   = st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt;

    u1_t_ch         = u1_t_rec_idx / (U1)TRIPCOM_NVMIF_GRPH_NUM_REC;
    u1_t_rec_end    = (u1_t_ch + (U1)1U) * (U1)TRIPCOM_NVMIF_GRPH_NUM_REC;

    if(u1_t_blo_next >= u1_t_rec_nblock){

        st_tp_last = &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST];
        st_tp_rdbk = &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_RDBK];
        u1_t_unk   = u1_s_TripcomNvmIfGrphUnk(st_tp_rdbk);

        if((u1_t_rec_nblock == u1_s_tripcom_nvmif_grph_rdbk_cnt) &&
           (u1_t_unk        == (U1)FALSE                  )){

            u1_t_cmpr  = u1_s_TripcomNvmIfGrphCmprAwB(st_tp_rdbk, st_tp_last);
            if((u1_t_rec_mrk >= u1_t_num_rec                 ) ||
             /* u1_t_cmpr == TRIPCOM_NVMIF_CMPR_A_GT_B or TRIPCOM_NVMIF_CMPR_A_EQ_B */
               (u1_t_cmpr    <= (U1)TRIPCOM_NVMIF_GRPH_CMPR_A_GT_B)){

                u1_t_rec_mrk = u1_t_rec_idx;

                for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
                    st_tp_last->u4_value[u4_t_lpcnt] = st_tp_rdbk->u4_value[u4_t_lpcnt];
                }
                st_tp_last->u4_wrt_cnt = st_tp_rdbk->u4_wrt_cnt;
                st_tp_last->u4_crc32   = st_tp_rdbk->u4_crc32;

                u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_VALID;
            }
            else{
                u1_t_sts_chk = (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_NEXT;
            }

            if(u1_s_tripcom_nvmif_grph_diag_ctrl == (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_CMP){
                vd_s_TripcomNvmIfGrphCmprNvmDflt(u1_t_rec_idx);
            }

            if(u1_t_rec_idx < (U1)U1_MAX){
                u1_t_rec_idx++;
            }
            u2_t_rtry_cnt = (U2)1U;
        }
        else if(u2_t_rtry_cnt >= (U2)TRIPCOM_NVMIF_GRPH_RW_RTRY_MAX){
            if(u1_t_rec_idx < (U1)U1_MAX){
                u1_t_rec_idx++;
            }
            u2_t_rtry_cnt = (U2)1U;
            u1_t_sts_chk  = (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_NEXT;
        }
        else{
            u2_t_rtry_cnt++;
            /* Since u2_t_rtry_cnt is determined whether it is larger than TRIPCOM_NVMIF_RW_RTRY_MAX within the if condition,        */
            /* it is not necessary to check the wraparound.                                                                          */
            u1_t_sts_chk  = (U1)TRIPCOM_NVMIF_GRPH_CHK_REC_INVAL;
        }

        if(u1_t_rec_idx >= u1_t_rec_end){
            if(u1_t_rec_mrk != (U1)U1_MAX){
                u4_sp_tripcom_nvmif_grph_wrt_cnt[u1_t_ch] = u4_g_TripcomCalcAddU4U4(st_tp_last->u4_wrt_cnt, (U4)1U);
                vd_g_TripcomNvmIfGrphCbkData(u1_t_ch, &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST]);
            }
            else{
                u4_sp_tripcom_nvmif_grph_wrt_cnt[u1_t_ch] = (U4)0U;
                vd_g_TripcomNvmIfGrphCbkData(u1_t_ch, vdp_PTR_NA);
            }
            u4_s_tripcom_nvmif_grph_sync_reqbit &= ((U4)U4_MAX ^ ((U4)1U << u1_t_ch));

            u1_t_ch_next = u1_g_LsbSrch(u4_s_tripcom_nvmif_grph_sync_reqbit);
            if(u1_t_ch_next < (U1)TRIPCOM_NVMIF_GRPH_CH_NUM){
                u1_t_rec_idx = u1_t_ch_next * (U1)TRIPCOM_NVMIF_GRPH_NUM_REC;
                u1_t_rec_mrk = (U1)U1_MAX;
            }
            else{
                u1_t_rec_idx = u1_t_rec_mrk;
                u1_t_sts_chk |= (U1)TRIPCOM_NVMIF_GRPH_CHK_OPE_CMPLT;
                vd_g_TripcomNvmIfGrphSyncCmplt();
            }
        }

        u1_t_blo_next                    = (U1)0U;
        u1_s_tripcom_nvmif_grph_rdbk_cnt = (U1)0U;
    }

    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx  = u1_t_rec_idx;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_mrk  = u1_t_rec_mrk;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt  = u1_t_blo_next;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt = u2_t_rtry_cnt;

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphActToSeqCmplt(void)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphActToSeqCmplt(void)
{
    vd_g_TripcomNvmIfGrphRWDeAct();
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphActToReqNext(void)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphActToReqNext(void)
{
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_GRPH_RW_REQ_NEXT;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt = (U2)1U;

    u1_s_tripcom_nvmif_grph_rdbk_cnt            = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphActToCbkNext(void)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphActToCbkNext(void)
{
    U1                      u1_t_ch;

    u1_t_ch = st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx / (U1)TRIPCOM_NVMIF_GRPH_NUM_REC;
    vd_g_TripcomNvmIfGrphCbkData(u1_t_ch, &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST]);

    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_GRPH_RW_REQ_NEXT;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt = (U2)1U;

    u1_s_tripcom_nvmif_grph_rdbk_cnt            = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphActToSynCmplt(void)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphActToSynCmplt(void)
{
    U1                      u1_t_ch;
    U1                      u1_t_diag_idx;
    U1                      u1_t_num_rec;

    u1_t_ch = st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx / (U1)TRIPCOM_NVMIF_GRPH_NUM_REC;
    vd_g_TripcomNvmIfGrphCbkData(u1_t_ch, &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST]);

    st_s_tripcom_nvmif_grph_fifo_ctrl.u2_len     = (U2)0U;
    st_s_tripcom_nvmif_grph_fifo_ctrl.u1_pos_in  = (U1)0U;
    st_s_tripcom_nvmif_grph_fifo_ctrl.u1_pos_out = (U1)0U;

    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_chk   = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt   = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rw_ctrl   = (U2)TRIPCOM_NVMIF_GRPH_RW_REQ_NEXT;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt  = (U2)1U;

    u1_s_tripcom_nvmif_grph_rdbk_cnt             = (U1)0U;

    vd_g_TripcomNvmIfGrphRWDeAct();

    /* diag compare finished */
    if(u1_s_tripcom_nvmif_grph_diag_ctrl == (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_CMP){
        if(u1_s_tripcom_nvmif_grph_diag_req == (U1)TRIPCOM_NVMIF_GRPH_DIAG_REQ_CMP){
            u1_t_num_rec  = st_g_TRIPCOM_NVMIF_GRPH_REC_DATA.u1_num_rec;
            u1_t_diag_idx = u1_s_TripcomNvmIfGrphLsbSrch(&u4_s_tripcom_nvmif_grph_diag_cmprchk[0], u1_t_num_rec);
            if(u1_t_diag_idx >= u1_t_num_rec){
                vd_g_TripcomNvmIfGrphDiagFinish((U1)TRUE);
            }
            else{
                vd_g_TripcomNvmIfGrphDiagFinish((U1)FALSE);
            }

            u1_s_tripcom_nvmif_grph_diag_ctrl = (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_FIN;
        }
        /* u1_s_tripcom_nvmif_diag_req == (U1)TRIPCOM_NVMIF_DIAG_REQ_WRI */
        else{
            /* dummy request to start diag nvm writting */
            (void)u1_g_TripcomNvmIfGrphRWRqst((U1)0U, vdp_PTR_NA);
            u1_s_tripcom_nvmif_grph_diag_idx  = (U1)0U;
            u1_s_tripcom_nvmif_grph_diag_ctrl = (U1)TRIPCOM_NVMIF_GRPH_DIAG_CTRL_WRI;
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphActWriNext(void)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphActWriNext(void)
{
    vd_s_TripcomNvmIfGrphWrite(&st_g_TRIPCOM_NVMIF_GRPH_REC_DATA, &st_s_tripcom_nvmif_grph_rw_ctrl,
                               (U1 *)&st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphActToWriNext(void)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphActToWriNext(void)
{
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_GRPH_RW_WRI_NEXT;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt = (U2)1U;

    u1_s_tripcom_nvmif_grph_rdbk_cnt            = (U1)0U;

    vd_s_TripcomNvmIfGrphWrite(&st_g_TRIPCOM_NVMIF_GRPH_REC_DATA, &st_s_tripcom_nvmif_grph_rw_ctrl,
                               (U1 *)&st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphActReaNext(void)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphActReaNext(void)
{
    vd_s_TripcomNvmIfGrphRead(&st_g_TRIPCOM_NVMIF_GRPH_REC_DATA, &st_s_tripcom_nvmif_grph_rw_ctrl);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphActToCmpNext(void)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphActToCmpNext(void)
{
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_GRPH_RW_CMP_NEXT;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt = (U2)1U;

    vd_s_TripcomNvmIfGrphRead(&st_g_TRIPCOM_NVMIF_GRPH_REC_DATA, &st_s_tripcom_nvmif_grph_rw_ctrl);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphActToSynLast(void)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphActToSynLast(void)
{
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_last;
    U1                        u1_t_rec_idx;
    U1                        u1_t_ch;
    U4                        u4_t_lpcnt;

    st_tp_last = &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_LAST];
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
        st_tp_last->u4_value[u4_t_lpcnt]   = (U4)TRIPCOM_NVMIF_GRPH_UNK;
    }
    st_tp_last->u4_wrt_cnt                 = (U4)TRIPCOM_NVMIF_GRPH_UNK;
    st_tp_last->u4_crc32                   = (U4)TRIPCOM_NVMIF_GRPH_UNK;

    u1_t_rec_idx = (U1)0U;
    u1_t_ch      = u1_g_LsbSrch(u4_s_tripcom_nvmif_grph_sync_reqbit);
    if(u1_t_ch < (U1)TRIPCOM_NVMIF_GRPH_CH_NUM){
        u1_t_rec_idx = u1_t_ch * (U1)TRIPCOM_NVMIF_GRPH_NUM_REC;
    }
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_idx  = (U1)u1_t_rec_idx;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_mrk  = (U1)U1_MAX;

    st_s_tripcom_nvmif_grph_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u1_blo_cnt  = (U1)0U;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_GRPH_RW_SYN_LAST;
    st_s_tripcom_nvmif_grph_rw_ctrl.u2_rtry_cnt = (U2)1U;

    u1_s_tripcom_nvmif_grph_rdbk_cnt            = (U1)0U;

    vd_s_TripcomNvmIfGrphRead(&st_g_TRIPCOM_NVMIF_GRPH_REC_DATA, &st_s_tripcom_nvmif_grph_rw_ctrl);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfGrphFifoPosIn(ST_TRIPCOM_NVMIF_GRPH_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfGrphFifoPosIn(ST_TRIPCOM_NVMIF_GRPH_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)
{
    U2                      u2_t_fifo_len;
    U1                      u1_t_fifo_in;
    U1                      u1_t_fifo_out;
    U1                      u1_t_fifo_next;

    u2_t_fifo_len = st_ap_ctrl->u2_len;
    u1_t_fifo_in  = st_ap_ctrl->u1_pos_in;
    u1_t_fifo_out = st_ap_ctrl->u1_pos_out;

    if((u2_t_fifo_len                   == (U2)0U                         ) ||
       (u2_t_fifo_len                   >  (U2)u1_a_MAX                   ) ||
       ((u2_t_fifo_len == (U2)u1_a_MAX) && (u1_t_fifo_out != u1_t_fifo_in)) ||
       (u1_t_fifo_in                    >= u1_a_MAX                       )){

        u2_t_fifo_len = (U2)0U;
        u1_t_fifo_in  = (U1)0U;
        u1_t_fifo_out = (U1)0U;
    }

    if(u2_t_fifo_len < (U2)u1_a_MAX){

        u1_t_fifo_next = u1_t_fifo_in + (U1)1U;
        if(u1_t_fifo_next >= u1_a_MAX){
            u1_t_fifo_next = (U1)0U;
        }
        u2_t_fifo_len++;

        st_ap_ctrl->u2_len     = u2_t_fifo_len; 
        st_ap_ctrl->u1_pos_in  = u1_t_fifo_next;
        st_ap_ctrl->u1_pos_out = u1_t_fifo_out;
    }
    else{
        u1_t_fifo_in = (U1)U1_MAX;
    }

    return(u1_t_fifo_in);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfGrphFifoPosOut(ST_TRIPCOM_NVMIF_GRPH_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfGrphFifoPosOut(ST_TRIPCOM_NVMIF_GRPH_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)
{
    U2                      u2_t_fifo_len;
    U1                      u1_t_fifo_in;
    U1                      u1_t_fifo_out;
    U1                      u1_t_fifo_next;

    u2_t_fifo_len = st_ap_ctrl->u2_len;
    u1_t_fifo_in  = st_ap_ctrl->u1_pos_in;
    u1_t_fifo_out = st_ap_ctrl->u1_pos_out;

    if((u2_t_fifo_len                   == (U2)0U                         ) ||
       (u2_t_fifo_len                   >  (U2)u1_a_MAX                   ) ||
       ((u2_t_fifo_len == (U2)u1_a_MAX) && (u1_t_fifo_out != u1_t_fifo_in)) ||
       (u1_t_fifo_out                   >= u1_a_MAX                       )){

        st_ap_ctrl->u2_len     = (U2)0U;
        st_ap_ctrl->u1_pos_in  = (U1)0U;
        st_ap_ctrl->u1_pos_out = (U1)0U;

        u1_t_fifo_out          = (U1)U1_MAX;
    }
    else{

        u1_t_fifo_next = u1_t_fifo_out + (U1)1U;
        if(u1_t_fifo_next >= u1_a_MAX){
            u1_t_fifo_next = (U1)0U;
        }
        u2_t_fifo_len--;

        st_ap_ctrl->u2_len     = u2_t_fifo_len;
        st_ap_ctrl->u1_pos_out = u1_t_fifo_next;
    }

    return(u1_t_fifo_out);
}

/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphWrite(const ST_TRIPCOM_NVMIF_GRPH_REC_DATA * st_ap_REC_DATA,                                 */
/*                                            const ST_TRIPCOM_NVMIF_GRPH_RW_CTRL * st_ap_CTRL,                                      */
/*                                            const U1 * u1_ap_DATA)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphWrite(const ST_TRIPCOM_NVMIF_GRPH_REC_DATA * st_ap_REC_DATA,
                                          const ST_TRIPCOM_NVMIF_GRPH_RW_CTRL * st_ap_CTRL,
                                          const U1 * u1_ap_DATA)
{
    const U2 *              u2_tp_BLOCK;
    U2                      u2_t_blo_next;
    U2                      u2_t_src_offset;

    u2_tp_BLOCK     = st_ap_REC_DATA->u2p_BLOCK;
    u2_t_blo_next   = ((U2)st_ap_CTRL->u1_rec_idx * (U2)st_ap_REC_DATA->u1_rec_nblock) + (U2)st_ap_CTRL->u1_blo_cnt;
    u2_t_src_offset = (U2)st_ap_CTRL->u1_blo_cnt * (U2)st_ap_REC_DATA->u1_blo_nbyte;
    vd_g_TripcomNvmIfGrphWriteBlock(st_ap_REC_DATA->u1_dev_idx,
                                    u2_tp_BLOCK[u2_t_blo_next],
                                    &u1_ap_DATA[u2_t_src_offset],
                                    (U2)st_ap_REC_DATA->u1_blo_nbyte);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfGrphRead(const ST_TRIPCOM_NVMIF_GRPH_REC_DATA * st_ap_REC_DATA,                                  */
/*                                           const ST_TRIPCOM_NVMIF_GRPH_RW_CTRL * st_ap_CTRL)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphRead(const ST_TRIPCOM_NVMIF_GRPH_REC_DATA * st_ap_REC_DATA,
                                         const ST_TRIPCOM_NVMIF_GRPH_RW_CTRL * st_ap_CTRL)
{
    const U2 *              u2_tp_BLOCK;
    U2                      u2_t_blo_next;

    u2_tp_BLOCK   = st_ap_REC_DATA->u2p_BLOCK;
    u2_t_blo_next = ((U2)st_ap_CTRL->u1_rec_idx * (U2)st_ap_REC_DATA->u1_rec_nblock) + (U2)st_ap_CTRL->u1_blo_cnt;
    vd_g_TripcomNvmIfGrphReadBlock(st_ap_REC_DATA->u1_dev_idx, u2_tp_BLOCK[u2_t_blo_next]);
}
/*===================================================================================================================================*/
/* U1      u1_s_TripcomNvmIfGrphUnk(const ST_TRIPCOM_GRPH_NVMDATA * st_ap_DATA)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfGrphUnk(const ST_TRIPCOM_GRPH_NVMDATA * st_ap_DATA)
{
    U4                      u4_t_crc32;
    U1                      u1_t_unk;

    u1_t_unk = (U1)TRUE;
    if(st_ap_DATA->u4_wrt_cnt != (U4)TRIPCOM_NVMIF_GRPH_UNK){

        u4_t_crc32 = u4_g_TripcomNvmIfGrphCrc32((const U1 *)st_ap_DATA, ((U4)sizeof(ST_TRIPCOM_GRPH_NVMDATA) - (U4)TRIPCOM_NVMIF_GRPH_NBYTE_CRC_32));
        if(u4_t_crc32 == st_ap_DATA->u4_crc32){
            u1_t_unk = (U1)FALSE;
        }
    }

    return(u1_t_unk);
}
/*===================================================================================================================================*/
/* U1      u1_s_TripcomNvmIfGrphCmprAwB(const ST_TRIPCOM_GRPH_NVMDATA * st_ap_CMPR_A, const ST_TRIPCOM_GRPH_NVMDATA * st_ap_CMPR_B)  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfGrphCmprAwB(const ST_TRIPCOM_GRPH_NVMDATA * st_ap_CMPR_A, const ST_TRIPCOM_GRPH_NVMDATA * st_ap_CMPR_B)
{
    U1                      u1_t_cmpr;
    U4                      u4_t_crc32_a;
    U4                      u4_t_crc32_b;
    U1                      u1_t_chk;
    U4                      u4_t_lpcnt;

    u4_t_crc32_a = st_ap_CMPR_A->u4_crc32;                /* Don't judge volatile variables for QAC */
    u4_t_crc32_b = st_ap_CMPR_B->u4_crc32;

    if(st_ap_CMPR_A->u4_wrt_cnt > st_ap_CMPR_B->u4_wrt_cnt){
        u1_t_cmpr = (U1)TRIPCOM_NVMIF_GRPH_CMPR_A_GT_B;
    }
    else if(st_ap_CMPR_A->u4_wrt_cnt < st_ap_CMPR_B->u4_wrt_cnt){
        u1_t_cmpr = (U1)TRIPCOM_NVMIF_GRPH_CMPR_A_LT_B;
    }
    else if(u4_t_crc32_a == u4_t_crc32_b){
        u1_t_chk = (U1)TRUE;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
            if(st_ap_CMPR_A->u4_value[u4_t_lpcnt] != st_ap_CMPR_B->u4_value[u4_t_lpcnt]){
                u1_t_chk = (U1)FALSE;
                break;
            }
        }
        if(u1_t_chk == (U1)TRUE){
            u1_t_cmpr = (U1)TRIPCOM_NVMIF_GRPH_CMPR_A_EQ_B;
        }
        else{
            u1_t_cmpr = (U1)TRIPCOM_NVMIF_GRPH_CMPR_UNK;
        }
    }
    else{
        u1_t_cmpr = (U1)TRIPCOM_NVMIF_GRPH_CMPR_UNK;
    }

    return(u1_t_cmpr);
}
/*===================================================================================================================================*/
/* void    vd_s_TripcomNvmIfGrphCmprNvmDflt(const U1 u1_a_REC_IDX)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfGrphCmprNvmDflt(const U1 u1_a_REC_IDX)
{
    ST_TRIPCOM_GRPH_NVMDATA * st_tp_rdbk;
    U1                        u1_t_ary_pos;
    U1                        u1_t_bit_pos;
    U4                        u4_t_crc32_a;
    U4                        u4_t_crc32_b;
    U1                        u1_t_chk;
    U4                        u4_t_lpcnt;

    st_tp_rdbk   = &st_sp_tripcom_nvmif_grph_rw_data[TRIPCOM_NVMIF_GRPH_RW_DAT_RDBK];
    u4_t_crc32_a = st_tp_rdbk->u4_crc32;                /* Don't judge volatile variables for QAC */
    u4_t_crc32_b = st_s_TRIPCOM_GRPH_NVMDFLT.u4_crc32;

    u1_t_chk = (U1)TRUE;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
        if(st_tp_rdbk->u4_value[u4_t_lpcnt] != st_s_TRIPCOM_GRPH_NVMDFLT.u4_value[u4_t_lpcnt]){
            u1_t_chk = (U1)FALSE;
            break;
         }
    }
    if((u1_t_chk               == (U1)TRUE                            ) &&
       (st_tp_rdbk->u4_wrt_cnt == st_s_TRIPCOM_GRPH_NVMDFLT.u4_wrt_cnt) &&
       (u4_t_crc32_a           == u4_t_crc32_b                        )){
        /* cmpr success : do nothing */
    }
    else{
        /* cmpr failed */
        u1_t_ary_pos = u1_a_REC_IDX >> TRIPCOM_NVMIF_GRPH_SFT_DIV32;
        u1_t_bit_pos = u1_a_REC_IDX  & (U1)TRIPCOM_NVMIF_GRPH_MSK_MOD32;
        u4_s_tripcom_nvmif_grph_diag_cmprchk[u1_t_ary_pos] |= ((U4)1U << u1_t_bit_pos);
    }
}
/*===================================================================================================================================*/
/* U1      u1_s_TripcomNvmIfGrphLsbSrch(const U4 * u4_ap_SRCH, const U1 u1_a_BITLEN)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfGrphLsbSrch(const U4 * u4_ap_SRCH, const U1 u1_a_BITLEN)
{
    U1                      u1_t_ary_pos;
    U1                      u1_t_ary_siz;
    U1                      u1_t_ret;

    u1_t_ary_siz = (u1_a_BITLEN / (U1)TRIPCOM_NVMIF_GRPH_U4_BITLEN) + (U1)1U;

    u1_t_ary_pos = (U1)0U;
    while((u1_t_ary_pos             <  (U1)u1_t_ary_siz) &&
          (u4_ap_SRCH[u1_t_ary_pos] == (U4)0U          )){
        u1_t_ary_pos++;
    }

    if(u1_t_ary_pos < u1_t_ary_siz){
        u1_t_ret  = u1_t_ary_pos * (U1)TRIPCOM_NVMIF_GRPH_U4_BITLEN;
        u1_t_ret  = u1_g_TripcomCalcAddU1U1(u1_t_ret, u1_g_LsbSrch(u4_s_tripcom_nvmif_grph_diag_cmprchk[u1_t_ary_pos]));
    }
    else{
        u1_t_ret  = (U1)LSB_SRCH_NOT_FOUND;
    }
    
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static void    vd_s_TripcomNvmGrphCrcChk(ST_TRIPCOM_GRPH_NVMDATA * st_a_rdbk)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmGrphCrcChk(ST_TRIPCOM_GRPH_NVMDATA * st_a_rdbk)
{
    U4                      u4_t_value;
    U4                      u4_t_lpcnt;

    u4_t_value = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_lpcnt++){
        u4_t_value |= st_a_rdbk->u4_value[u4_t_lpcnt];
    }
    if((st_a_rdbk->u4_crc32   == (U4)0U) &&
       (st_a_rdbk->u4_wrt_cnt == (U4)0U) &&
       (u4_t_value            == (U4)0U)){
        st_a_rdbk->u4_crc32 = (U4)TRIPCOM_NVMIF_GRPH_CRC32_INIT;
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     1/10/2024  TH       New.                                                                                               */
/*                                                                                                                                   */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
