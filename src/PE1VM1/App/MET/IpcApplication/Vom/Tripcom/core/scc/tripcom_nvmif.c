/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Tripcom Non-Volatile Memory Interface                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NVMIF_C_MAJOR                (2)
#define TRIPCOM_NVMIF_C_MINOR                (1)
#define TRIPCOM_NVMIF_C_PATCH                (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_nvmif_cfg_private.h"
#include "tripcom.h"
#include "lsbsrch.h"
#include "tripcom_calc.h"
#include "tripcom_ms.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPCOM_NVMIF_C_MAJOR != TRIPCOM_NVMIF_H_MAJOR) || \
     (TRIPCOM_NVMIF_C_MINOR != TRIPCOM_NVMIF_H_MINOR) || \
     (TRIPCOM_NVMIF_C_PATCH != TRIPCOM_NVMIF_H_PATCH))
#error "tripcom_nvmif.c and tripcom_nvmif.h : source and header files are inconsistent!"
#endif

#if ((TRIPCOM_NVMIF_C_MAJOR != TRIPCOM_NVMIF_CFG_H_MAJOR) || \
     (TRIPCOM_NVMIF_C_MINOR != TRIPCOM_NVMIF_CFG_H_MINOR) || \
     (TRIPCOM_NVMIF_C_PATCH != TRIPCOM_NVMIF_CFG_H_PATCH))
#error "tripcom_nvmif.c and tripcom_nvmif_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NVMIF_RW_NUM_STS                (4U)
#define TRIPCOM_NVMIF_RW_REQ_NEXT               (0U)
#define TRIPCOM_NVMIF_RW_WRI_NEXT               (1U)
#define TRIPCOM_NVMIF_RW_CMP_NEXT               (2U)
#define TRIPCOM_NVMIF_RW_SYN_LAST               (3U)
#define TRIPCOM_NVMIF_RW_SYN_INIT               (TRIPCOM_NVMIF_RW_NUM_STS)

#define TRIPCOM_NVMIF_CHK_SEQ_ABORT             (0x08U)
#define TRIPCOM_NVMIF_CHK_OPE_CMPLT             (0x04U)
#define TRIPCOM_NVMIF_CHK_REC_NEXT              (0x03U)
#define TRIPCOM_NVMIF_CHK_REC_VALID             (0x02U)
#define TRIPCOM_NVMIF_CHK_REC_INVAL             (0x01U)

#define TRIPCOM_NVMIF_ACT_TO_SEQ_CMPLT          (0U)
#define TRIPCOM_NVMIF_ACT_TO_REQ_NEXT           (1U)
#define TRIPCOM_NVMIF_ACT_TO_CBK_NEXT           (2U)
#define TRIPCOM_NVMIF_ACT_TO_SYN_CMPLT          (3U)
#define TRIPCOM_NVMIF_ACT_WRI_NEXT              (4U)
#define TRIPCOM_NVMIF_ACT_TO_WRI_NEXT           (5U)
#define TRIPCOM_NVMIF_ACT_CMP_NEXT              (6U)
#define TRIPCOM_NVMIF_ACT_TO_CMP_NEXT           (7U)
#define TRIPCOM_NVMIF_ACT_SYN_LAST              (8U)
#define TRIPCOM_NVMIF_ACT_TO_SYN_LAST           (9U)

#define TRIPCOM_NVMIF_FIFO_MAX                  (TRIPCOM_NVMIF_CH_NUM)
#define TRIPCOM_NVMIF_RW_RTRY_MAX               (2U)

#define TRIPCOM_NVMIF_CMPR_A_EQ_B               (0U)
#define TRIPCOM_NVMIF_CMPR_A_GT_B               (1U)
#define TRIPCOM_NVMIF_CMPR_A_LT_B               (2U)
#define TRIPCOM_NVMIF_CMPR_UNK                  (3U)

#define TRIPCOM_NVMIF_CRC32_INIT                (0xEA0744F0U)

#define TRIPCOM_NVMIF_SFT_DIV32                 (5U)
#define TRIPCOM_NVMIF_MSK_MOD32                 (0x1FU)
#define TRIPCOM_NVMIF_U4_BITLEN                 (32U)
#define TRIPCOM_NVMIF_CMPRCHK_SIZE              (((TRIPCOM_NVMIF_CH_NUM * TRIPCOM_NVMIF_NUM_REC) / TRIPCOM_NVMIF_U4_BITLEN) + 1U)

#define TRIPCOM_NVMIF_DIAG_CTRL_CMP             (0x00U)
#define TRIPCOM_NVMIF_DIAG_CTRL_WRI             (0x01U)
#define TRIPCOM_NVMIF_DIAG_CTRL_FIN             (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_TRIPCOM_NVMDATA         st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_NUM];
static ST_TRIPCOM_NVMIF_RW_CTRL   st_s_tripcom_nvmif_rw_ctrl;
static U1                         u1_s_tripcom_nvmif_rdbk_cnt;
static U4                         u4_sp_tripcom_nvmif_wrt_cnt[TRIPCOM_NVMIF_CH_NUM];
static U4                         u4_s_tripcom_nvmif_sync_reqbit;
static U1                         u1_s_tripcom_nvmif_diag_ctrl;
static U1                         u1_s_tripcom_nvmif_diag_req;
static U1                         u1_s_tripcom_nvmif_diag_idx;
static U4                         u4_s_tripcom_nvmif_diag_cmprchk[TRIPCOM_NVMIF_CMPRCHK_SIZE];

static ST_TRIPCOM_NVMDATA         st_sp_tripcom_nvmif_fifo_data[TRIPCOM_NVMIF_FIFO_MAX];
static U1                         u1_sp_tripcom_nvmif_fifo_ch[TRIPCOM_NVMIF_FIFO_MAX];
static ST_TRIPCOM_NVMIF_FIFO_CTRL st_s_tripcom_nvmif_fifo_ctrl;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_TripcomNvmIfSynInit(void);

static U1      u1_s_TripcomNvmIfAbortchk(void);
static U1      u1_s_TripcomNvmIfReqchk(void);
static U1      u1_s_TripcomNvmIfWrichk(void);
static U1      u1_s_TripcomNvmIfCmpchk(void);
static U1      u1_s_TripcomNvmIfSynchk(void);

static void    vd_s_TripcomNvmIfActToSeqCmplt(void);
static void    vd_s_TripcomNvmIfActToReqNext(void);
static void    vd_s_TripcomNvmIfActToCbkNext(void);
static void    vd_s_TripcomNvmIfActToSynCmplt(void);
static void    vd_s_TripcomNvmIfActWriNext(void);
static void    vd_s_TripcomNvmIfActToWriNext(void);
static void    vd_s_TripcomNvmIfActReaNext(void);
static void    vd_s_TripcomNvmIfActToCmpNext(void);
static void    vd_s_TripcomNvmIfActToSynLast(void);

static U1      u1_s_TripcomNvmIfFifoPosIn(ST_TRIPCOM_NVMIF_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX);
static U1      u1_s_TripcomNvmIfFifoPosOut(ST_TRIPCOM_NVMIF_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX);

static void    vd_s_TripcomNvmIfWrite(const ST_TRIPCOM_NVMIF_REC_DATA * st_ap_REC_DATA,
                                      const ST_TRIPCOM_NVMIF_RW_CTRL * st_ap_CTRL,
                                      const U1 * u1_ap_DATA);
static void    vd_s_TripcomNvmIfRead(const ST_TRIPCOM_NVMIF_REC_DATA * st_ap_REC_DATA,
                                     const ST_TRIPCOM_NVMIF_RW_CTRL * st_ap_CTRL);

static U1      u1_s_TripcomNvmIfUnk(const ST_TRIPCOM_NVMDATA * st_ap_DATA);
static U1      u1_s_TripcomNvmIfCmprAwB(const ST_TRIPCOM_NVMDATA * st_ap_CMPR_A,
                                        const ST_TRIPCOM_NVMDATA * st_ap_CMPR_B);

static void    vd_s_TripcomNvmIfCmprNvmDflt(const U1 u1_a_REC_IDX);
static U1      u1_s_TripcomNvmIfLsbSrch(const U4 * u4_ap_SRCH, const U1 u1_a_BITLEN);
static void    vd_s_TripcomNvmCrcChk(ST_TRIPCOM_NVMDATA * st_a_rdbk);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_TRIPCOM_NVMDATA    st_s_TRIPCOM_NVMDFLT = {
    (U4)0x00000000U,                /* u4_value   */
    (U4)0x00000000U,                /* u4_wrt_cnt */
    (U4)TRIPCOM_NVMIF_CRC32_INIT    /* u4_crc32   */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfInit(const U1 u1_a_SYNC)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TripcomNvmIfInit(const U1 u1_a_SYNC)
{
    U4                      u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_RW_DAT_NUM; u4_t_lpcnt++){
        st_sp_tripcom_nvmif_rw_data[u4_t_lpcnt].u4_value   = (U4)TRIPCOM_NVMIF_UNK;
        st_sp_tripcom_nvmif_rw_data[u4_t_lpcnt].u4_wrt_cnt = (U4)TRIPCOM_NVMIF_UNK;
        st_sp_tripcom_nvmif_rw_data[u4_t_lpcnt].u4_crc32   = (U4)TRIPCOM_NVMIF_UNK;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_CH_NUM; u4_t_lpcnt++){
        u4_sp_tripcom_nvmif_wrt_cnt[u4_t_lpcnt] = (U4)TRIPCOM_NVMIF_UNK;
    }

    st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx  = (U1)U1_MAX;
    st_s_tripcom_nvmif_rw_ctrl.u1_rec_mrk  = (U1)U1_MAX;
    st_s_tripcom_nvmif_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt  = (U1)0U;

    st_s_tripcom_nvmif_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_RW_SYN_INIT;
    st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt = (U2)1U;
    st_s_tripcom_nvmif_rw_ctrl.u4_crc32    = (U4)0U;

    u1_s_tripcom_nvmif_rdbk_cnt            = (U1)0U;
    u1_s_tripcom_nvmif_diag_ctrl           = (U1)TRIPCOM_NVMIF_DIAG_CTRL_FIN;
    u1_s_tripcom_nvmif_diag_req            = (U1)U1_MAX;
    u1_s_tripcom_nvmif_diag_idx            = (U1)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_FIFO_MAX; u4_t_lpcnt++){
        st_sp_tripcom_nvmif_fifo_data[u4_t_lpcnt].u4_value   = (U4)TRIPCOM_NVMIF_UNK;
        st_sp_tripcom_nvmif_fifo_data[u4_t_lpcnt].u4_wrt_cnt = (U4)TRIPCOM_NVMIF_UNK;
        st_sp_tripcom_nvmif_fifo_data[u4_t_lpcnt].u4_crc32   = (U4)TRIPCOM_NVMIF_UNK;
        u1_sp_tripcom_nvmif_fifo_ch[u4_t_lpcnt]              = (U1)U1_MAX;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TRIPCOM_NVMIF_CMPRCHK_SIZE; u4_t_lpcnt++){
        u4_s_tripcom_nvmif_diag_cmprchk[u4_t_lpcnt] = (U4)0U;
    }

    st_s_tripcom_nvmif_fifo_ctrl.u2_len     = (U2)0U;
    st_s_tripcom_nvmif_fifo_ctrl.u1_pos_in  = (U1)0U;
    st_s_tripcom_nvmif_fifo_ctrl.u1_pos_out = (U1)0U;

    if(u1_a_SYNC == (U1)TRUE){
        u4_s_tripcom_nvmif_sync_reqbit = (U4)0U;
        vd_s_TripcomNvmIfSynInit();
    }
    else{
        u4_s_tripcom_nvmif_sync_reqbit = ((U4)1U << TRIPCOM_NVMIF_CH_NUM) - (U4)1U;
        vd_g_TripcomNvmIfRWAct();
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_TripcomNvmIfRWRqst(const U1 u1_a_CH, const U4 * u4_ap_NEXT)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TripcomNvmIfRWRqst(const U1 u1_a_CH, const U4 * u4_ap_NEXT)
{
    ST_TRIPCOM_NVMDATA *    st_tp_next;

    U1                      u1_t_fifo_in;
    U1                      u1_t_accpt;

    u1_t_fifo_in = u1_s_TripcomNvmIfFifoPosIn(&st_s_tripcom_nvmif_fifo_ctrl, (U1)TRIPCOM_NVMIF_FIFO_MAX);
    if((u1_t_fifo_in < (U1)TRIPCOM_NVMIF_FIFO_MAX) &&
       (u1_a_CH      < (U1)TRIPCOM_NVMIF_CH_NUM  )){

        u1_sp_tripcom_nvmif_fifo_ch[u1_t_fifo_in] = u1_a_CH;

        st_tp_next = &st_sp_tripcom_nvmif_fifo_data[u1_t_fifo_in];
        if((u4_ap_NEXT                           == vdp_PTR_NA           ) ||
           (u4_sp_tripcom_nvmif_wrt_cnt[u1_a_CH] == (U4)TRIPCOM_NVMIF_UNK)){
            st_tp_next->u4_value   = (U4)TRIPCOM_NVMIF_UNK;
            st_tp_next->u4_wrt_cnt = (U4)TRIPCOM_NVMIF_UNK;
            st_tp_next->u4_crc32   = (U4)TRIPCOM_NVMIF_UNK;
        }
        else{
            st_tp_next->u4_value   = (* u4_ap_NEXT);
            st_tp_next->u4_wrt_cnt = u4_sp_tripcom_nvmif_wrt_cnt[u1_a_CH];
            st_tp_next->u4_crc32   = u4_g_TripcomNvmIfCrc32((const U1 *)st_tp_next,
                                                            ((U4)sizeof(ST_TRIPCOM_NVMDATA) - (U4)TRIPCOM_NVMIF_NBYTE_CRC_32));
        }

        u4_s_tripcom_nvmif_sync_reqbit |= ((U4)1U << u1_a_CH);
        vd_g_TripcomNvmIfRWAct();

        u1_t_accpt = (U1)TRUE;
    }
    else{
        u1_t_accpt = (U1)FALSE;
    }

    return(u1_t_accpt);
}
/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfRWTask(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TripcomNvmIfRWTask(void)
{
    static U1 ( * const     fp_sp_u1_TRIPCOM_NVMIF_CHK[TRIPCOM_NVMIF_RW_NUM_STS])(void) = {
        &u1_s_TripcomNvmIfReqchk,
        &u1_s_TripcomNvmIfWrichk,
        &u1_s_TripcomNvmIfCmpchk,
        &u1_s_TripcomNvmIfSynchk
    };

    static const U1         u1_sp_TRIPCOM_NVMIF_RW_STM[] = {
        (U1)TRIPCOM_NVMIF_ACT_TO_REQ_NEXT,  (U1)TRIPCOM_NVMIF_ACT_WRI_NEXT,
        (U1)TRIPCOM_NVMIF_ACT_CMP_NEXT,     (U1)TRIPCOM_NVMIF_ACT_SYN_LAST,
        (U1)TRIPCOM_NVMIF_ACT_TO_SYN_LAST,  (U1)TRIPCOM_NVMIF_ACT_WRI_NEXT,
        (U1)TRIPCOM_NVMIF_ACT_CMP_NEXT,     (U1)TRIPCOM_NVMIF_ACT_SYN_LAST,
        (U1)TRIPCOM_NVMIF_ACT_TO_WRI_NEXT,  (U1)TRIPCOM_NVMIF_ACT_WRI_NEXT,
        (U1)TRIPCOM_NVMIF_ACT_CMP_NEXT,     (U1)TRIPCOM_NVMIF_ACT_SYN_LAST,
        (U1)TRIPCOM_NVMIF_ACT_TO_REQ_NEXT,  (U1)TRIPCOM_NVMIF_ACT_WRI_NEXT,
        (U1)TRIPCOM_NVMIF_ACT_CMP_NEXT,     (U1)TRIPCOM_NVMIF_ACT_SYN_LAST,
        (U1)TRIPCOM_NVMIF_ACT_TO_SEQ_CMPLT, (U1)TRIPCOM_NVMIF_ACT_TO_CMP_NEXT,
        (U1)TRIPCOM_NVMIF_ACT_TO_REQ_NEXT,  (U1)TRIPCOM_NVMIF_ACT_TO_SYN_CMPLT,
        (U1)TRIPCOM_NVMIF_ACT_TO_SEQ_CMPLT, (U1)TRIPCOM_NVMIF_ACT_TO_CMP_NEXT,
        (U1)TRIPCOM_NVMIF_ACT_CMP_NEXT,     (U1)TRIPCOM_NVMIF_ACT_TO_SYN_CMPLT,
        (U1)TRIPCOM_NVMIF_ACT_TO_SEQ_CMPLT, (U1)TRIPCOM_NVMIF_ACT_TO_CMP_NEXT,
        (U1)TRIPCOM_NVMIF_ACT_TO_CBK_NEXT,  (U1)TRIPCOM_NVMIF_ACT_TO_SYN_CMPLT,
        (U1)TRIPCOM_NVMIF_ACT_TO_SEQ_CMPLT, (U1)TRIPCOM_NVMIF_ACT_TO_CMP_NEXT,
        (U1)TRIPCOM_NVMIF_ACT_TO_REQ_NEXT,  (U1)TRIPCOM_NVMIF_ACT_TO_SYN_CMPLT
    };

    static void ( * const   fp_vd_TRIPCOM_NVMIF_ACT[])(void) = {
        &vd_s_TripcomNvmIfActToSeqCmplt,                  /* TRIPCOM_NVMIF_ACT_TO_SEQ_CMPLT (0U) */
        &vd_s_TripcomNvmIfActToReqNext,                   /* TRIPCOM_NVMIF_ACT_TO_REQ_NEXT  (1U) */
        &vd_s_TripcomNvmIfActToCbkNext,                   /* TRIPCOM_NVMIF_ACT_TO_CBK_NEXT  (2U) */
        &vd_s_TripcomNvmIfActToSynCmplt,                  /* TRIPCOM_NVMIF_ACT_TO_SYN_CMPLT (3U) */
        &vd_s_TripcomNvmIfActWriNext,                     /* TRIPCOM_NVMIF_ACT_WRI_NEXT     (4U) */
        &vd_s_TripcomNvmIfActToWriNext,                   /* TRIPCOM_NVMIF_ACT_TO_WRI_NEXT  (5U) */
        &vd_s_TripcomNvmIfActReaNext,                     /* TRIPCOM_NVMIF_ACT_CMP_NEXT     (6U) */
        &vd_s_TripcomNvmIfActToCmpNext,                   /* TRIPCOM_NVMIF_ACT_TO_CMP_NEXT  (7U) */
        &vd_s_TripcomNvmIfActReaNext,                     /* TRIPCOM_NVMIF_ACT_SYN_LAST     (8U) */
        &vd_s_TripcomNvmIfActToSynLast                    /* TRIPCOM_NVMIF_ACT_TO_SYN_LAST  (9U) */
    };

    U4                      u4_t_crc32;
    U2                      u2_t_rw_act;
    U2                      u2_t_rw_ctrl;
    U1                      u1_t_sts_chk;

    u1_t_sts_chk = u1_s_TripcomNvmIfAbortchk();
    if(u1_t_sts_chk == (U1)0U){

        u2_t_rw_ctrl = st_s_tripcom_nvmif_rw_ctrl.u2_rw_ctrl;
        u1_t_sts_chk = (fp_sp_u1_TRIPCOM_NVMIF_CHK[u2_t_rw_ctrl])();
        u2_t_rw_act  = ((U2)u1_t_sts_chk * (U2)TRIPCOM_NVMIF_RW_NUM_STS) + u2_t_rw_ctrl;
        u2_t_rw_act  = (U2)u1_sp_TRIPCOM_NVMIF_RW_STM[u2_t_rw_act];
    }
    else{
        u2_t_rw_act  = (U2)TRIPCOM_NVMIF_ACT_TO_SYN_LAST;
    }

    (*fp_vd_TRIPCOM_NVMIF_ACT[u2_t_rw_act])();

    u4_t_crc32 = u4_g_TripcomNvmIfCrc32((U1 *)&st_s_tripcom_nvmif_rw_ctrl,
                                        ((U4)sizeof(ST_TRIPCOM_NVMIF_RW_CTRL) - (U4)TRIPCOM_NVMIF_NBYTE_CRC_32));
    st_s_tripcom_nvmif_rw_ctrl.u4_crc32 = u4_t_crc32;
}
/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfRWFinhk(const U2 u2_a_BLOCKID,                                                                          */
/*                                   const U1 u1_a_REQUEST_TYPE,                                                                     */
/*                                   const U1 u1_a_RESULT,                                                                           */
/*                                   const U1 * const u1_ap_DATA,                                                                    */
/*                                   const U2 u2_a_SIZE)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TripcomNvmIfRWFinhk(const U2 u2_a_BLOCKID,
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

    u1_t_rec_nblock = st_g_TRIPCOM_NVMIF_REC_DATA.u1_rec_nblock;
    u1_t_blo_nbyte  = st_g_TRIPCOM_NVMIF_REC_DATA.u1_blo_nbyte;
    u1_t_blo_cnt    = st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt;

    if((u1_a_REQUEST_TYPE == (U1)TRIPCOM_NVMIF_REQ_TYPE_READ) &&
       (u1_a_RESULT       == (U1)TRIPCOM_NVMIF_JOB_RESULT_OK) &&
       (u1_ap_DATA        != vdp_PTR_NA                     ) &&
       (u2_a_SIZE         == (U2)u1_t_blo_nbyte             ) &&
       (u1_t_blo_cnt      <  u1_t_rec_nblock                )){

        u2_t_rdbk_offset = (U2)u1_t_blo_cnt * (U2)u1_t_blo_nbyte;
        u1_tp_dst        = (U1 *)&st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_RDBK];
        u1_tp_dst        = &u1_tp_dst[u2_t_rdbk_offset];
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_t_blo_nbyte; u4_t_lpcnt++){
            u1_tp_dst[u4_t_lpcnt] = u1_ap_DATA[u4_t_lpcnt];
        }

        if((u1_s_tripcom_nvmif_diag_ctrl != (U1)TRIPCOM_NVMIF_DIAG_CTRL_CMP            ) &&
           (st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_RDBK].u4_crc32   == (U4)0U) &&
           (st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_RDBK].u4_wrt_cnt == (U4)0U) &&
           (st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_RDBK].u4_value   == (U4)0U)){
            st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_RDBK].u4_crc32 = (U4)TRIPCOM_NVMIF_CRC32_INIT;
        }

        if(u1_s_tripcom_nvmif_rdbk_cnt < (U1)U1_MAX){
            u1_s_tripcom_nvmif_rdbk_cnt++;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfDiagStart(const U1 u1_a_REQ)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TripcomNvmIfDiagStart(const U1 u1_a_REQ)
{
    U4                      u4_t_loop;

    if(u1_s_tripcom_nvmif_diag_ctrl >= (U1)TRIPCOM_NVMIF_DIAG_CTRL_FIN){
        u1_s_tripcom_nvmif_diag_req  = u1_a_REQ;
        u1_s_tripcom_nvmif_diag_ctrl = (U1)TRIPCOM_NVMIF_DIAG_CTRL_CMP;

        for(u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_CMPRCHK_SIZE; u4_t_loop++){
            u4_s_tripcom_nvmif_diag_cmprchk[u4_t_loop] = (U4)0U;
        }

        for(u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_CH_NUM; u4_t_loop++){
            (void)u1_g_TripcomNvmIfRWRqst((U1)u4_t_loop, vdp_PTR_NA);
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfSynInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfSynInit(void)
{
    const U2 *              u2_tp_BLOCK;
    ST_TRIPCOM_NVMDATA *    st_tp_last;

    ST_TRIPCOM_NVMDATA      st_t_rdbk;
    U1 *                    u1_tp_rdbk;

    U4                      u4_t_num_rec;
    U4                      u4_t_rec_nblock;
    U4                      u4_t_rec_idx;
    U4                      u4_t_rec_mrk;
    U4                      u4_t_rec_end;

    U4                      u4_t_blo_idx;
    U4                      u4_t_blo_end;

    U4                      u4_t_rtry_cnt;
    U4                      u4_t_crc32;

    U2                      u2_t_blo_nbyte;
    U2                      u2_t_rdbk_offset;

    U1                      u1_t_dev_idx;
    U1                      u1_t_rdrslt;
    U1                      u1_t_unk;
    U1                      u1_t_cmpr;

    U4                      u4_t_ch;

    st_tp_last           = &st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST];

    st_t_rdbk.u4_value   = (U4)TRIPCOM_NVMIF_UNK;
    st_t_rdbk.u4_wrt_cnt = (U4)TRIPCOM_NVMIF_UNK;
    st_t_rdbk.u4_crc32   = (U4)TRIPCOM_NVMIF_UNK;
    u1_tp_rdbk           = (U1 *)&st_t_rdbk;

    u4_t_rec_mrk         = (U4)U4_MAX;

    u2_tp_BLOCK          = st_g_TRIPCOM_NVMIF_REC_DATA.u2p_BLOCK;
    u4_t_num_rec         = (U4)st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec;
    u4_t_rec_nblock      = (U4)st_g_TRIPCOM_NVMIF_REC_DATA.u1_rec_nblock;
    u2_t_blo_nbyte       = (U2)st_g_TRIPCOM_NVMIF_REC_DATA.u1_blo_nbyte;
    u1_t_dev_idx         = st_g_TRIPCOM_NVMIF_REC_DATA.u1_dev_idx;

    u4_t_rec_idx         = (U4)0U;
    u4_t_rec_end         = (U4)TRIPCOM_NVMIF_NUM_REC;
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
            u1_t_rdrslt = u1_g_TripcomNvmIfSyncBlock(u1_t_dev_idx,
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

            if(u1_t_rdrslt == (U1)TRIPCOM_NVMIF_JOB_RESULT_OK){
                u4_t_blo_idx++;
                /* The value of u4_t_blo_idx is determined whether it is smaller than u4_t_blo_end within the while condition.       */
                /* The max value of u4_t_blo_end is 65280, , therefor it is not necessary to check the wraparound.                   */
            }
            else{
                u4_t_blo_idx = (U4)U4_MAX;
            }
        }
        while(u4_t_blo_idx < u4_t_blo_end);

        vd_s_TripcomNvmCrcChk(&st_t_rdbk);

        u1_t_unk = u1_s_TripcomNvmIfUnk(&st_t_rdbk);
        if((u4_t_blo_idx == u4_t_blo_end) &&
           (u1_t_unk     == (U1)FALSE   )){

            u1_t_cmpr = u1_s_TripcomNvmIfCmprAwB(&st_t_rdbk, st_tp_last);
            if((u4_t_rec_mrk >= u4_t_num_rec                 ) ||
            /* u1_t_cmpr == TRIPCOM_NVMIF_CMPR_A_GT_B or TRIPCOM_NVMIF_CMPR_A_EQ_B */
               (u1_t_cmpr    <= (U1)TRIPCOM_NVMIF_CMPR_A_GT_B)){

               u4_t_rec_mrk = u4_t_rec_idx;

               st_tp_last->u4_value   = st_t_rdbk.u4_value;
               st_tp_last->u4_wrt_cnt = st_t_rdbk.u4_wrt_cnt;
               st_tp_last->u4_crc32   = st_t_rdbk.u4_crc32;
            }

            u4_t_rec_idx++;
            /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.           */
            /* The source of u4_t_num_rec is st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec, so the max value of u4_t_num_rec is 255.        */
            /* Therefor it is not necessary to check the wraparound.                                                                 */

            u4_t_rtry_cnt = (U4)1U;
        }
        else if(u4_t_rtry_cnt >= (U4)TRIPCOM_NVMIF_RW_RTRY_MAX){
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
                u4_sp_tripcom_nvmif_wrt_cnt[u4_t_ch] = u4_g_TripcomCalcAddU4U4(st_tp_last->u4_wrt_cnt, (U4)1U);
                vd_g_TripcomNvmIfCbkData((U1)u4_t_ch, st_tp_last->u4_value);
            }
            else{
                u4_sp_tripcom_nvmif_wrt_cnt[u4_t_ch]  = (U4)0U;
                vd_g_TripcomNvmIfCbkData((U1)u4_t_ch, (U4)0U);
            }

            if(u4_t_rec_idx < u4_t_num_rec){
                u4_t_ch++;
                /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.       */
                /* The source of u4_t_num_rec is st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec, so the max value of u4_t_num_rec is 255.    */
                /* This also occurs up to 255 times, so the maximum value is 255.                                                    */
                /* Therefor it is not necessary to check the wraparound.                                                             */
                u4_t_rec_mrk  = (U4)U4_MAX;
                u4_t_rec_end += (U4)TRIPCOM_NVMIF_NUM_REC;
                /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.       */
                /* The source of u4_t_num_rec is st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec, so the max value of u4_t_num_rec is 255.    */
                /* This also occurs up to 255 times, so the maximum value is 6*255 = 1530.                                           */
                /* Therefor it is not necessary to check the wraparound.                                                             */
            }
        }
    }
    while(u4_t_rec_idx < u4_t_num_rec);

    vd_g_TripcomNvmIfSyncCmplt();

    st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx = (U1)u4_t_rec_mrk;
    st_s_tripcom_nvmif_rw_ctrl.u2_rw_ctrl = (U2)TRIPCOM_NVMIF_RW_REQ_NEXT;

    u4_t_crc32 = u4_g_TripcomNvmIfCrc32((const U1 *)&st_s_tripcom_nvmif_rw_ctrl,
                                        ((U4)sizeof(ST_TRIPCOM_NVMIF_RW_CTRL) - (U4)TRIPCOM_NVMIF_NBYTE_CRC_32));
    st_s_tripcom_nvmif_rw_ctrl.u4_crc32 = u4_t_crc32;
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfAbortchk(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfAbortchk(void)
{
    ST_TRIPCOM_NVMDATA *    st_tp_last;

    U4                      u4_t_crc32;

    U2                      u2_t_rw_ctrl;

    U1                      u1_t_num_rec;
    U1                      u1_t_rec_nblock;
    U1                      u1_t_rec_idx;
    U1                      u1_t_blo_cnt;
    U1                      u1_t_unk;
    U1                      u1_t_sts_chk;

    u1_t_sts_chk = (U1)0x00U;

    u4_t_crc32   = u4_g_TripcomNvmIfCrc32((U1 *)&st_s_tripcom_nvmif_rw_ctrl,
                                          ((U4)sizeof(ST_TRIPCOM_NVMIF_RW_CTRL) - (U4)TRIPCOM_NVMIF_NBYTE_CRC_32));

    u1_t_num_rec    = st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec;
    u1_t_rec_nblock = st_g_TRIPCOM_NVMIF_REC_DATA.u1_rec_nblock;

    u1_t_rec_idx    = st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx;
    u1_t_blo_cnt    = st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt;
    u2_t_rw_ctrl    = st_s_tripcom_nvmif_rw_ctrl.u2_rw_ctrl;

    if((st_s_tripcom_nvmif_rw_ctrl.u4_crc32 != u4_t_crc32                  ) ||
       (u2_t_rw_ctrl                        >= (U2)TRIPCOM_NVMIF_RW_NUM_STS) ||
       (u1_t_rec_idx                        >= u1_t_num_rec                ) ||
       (u1_t_blo_cnt                        >= u1_t_rec_nblock             )){

        u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_SEQ_ABORT;
    }
    else if((u2_t_rw_ctrl                 <  (U2)TRIPCOM_NVMIF_RW_SYN_LAST  ) &&
            (u1_s_tripcom_nvmif_diag_ctrl != (U1)TRIPCOM_NVMIF_DIAG_CTRL_WRI)){

        st_tp_last = &st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST];
        u1_t_unk   = u1_s_TripcomNvmIfUnk(st_tp_last);
        if(u1_t_unk != (U1)FALSE){
            
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_SEQ_ABORT;
        }
    }
    else{
        /* do nothing */
    }

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfReqchk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfReqchk(void)
{
    ST_TRIPCOM_NVMDATA *    st_tp_last;
    ST_TRIPCOM_NVMDATA *    st_tp_next;

    U1                      u1_t_rec_idx;
    U1                      u1_t_ch;
    U1                      u1_t_num_rec;

    U1                      u1_t_fifo_out;
    U1                      u1_t_unk;

    U1                      u1_t_sts_chk;

    U1                      u1_t_ary_pos;
    U1                      u1_t_bit_pos;
    U1                      u1_t_diag_idx;
    U1                      u1_t_mul;


    u1_t_fifo_out = u1_s_TripcomNvmIfFifoPosOut(&st_s_tripcom_nvmif_fifo_ctrl, (U1)TRIPCOM_NVMIF_FIFO_MAX);
    if(u1_t_fifo_out >= (U1)TRIPCOM_NVMIF_FIFO_MAX){
        u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_OPE_CMPLT;
    }
    else{

        st_tp_last = &st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST];
        st_tp_next = &st_sp_tripcom_nvmif_fifo_data[u1_t_fifo_out];
        u1_t_ch    = u1_sp_tripcom_nvmif_fifo_ch[u1_t_fifo_out];

        u1_t_unk = u1_s_TripcomNvmIfUnk(st_tp_next);

        if(u1_s_tripcom_nvmif_diag_ctrl == (U1)TRIPCOM_NVMIF_DIAG_CTRL_WRI){

            st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx = u1_s_tripcom_nvmif_diag_idx;

            st_tp_last->u4_value   = st_s_TRIPCOM_NVMDFLT.u4_value;
            st_tp_last->u4_wrt_cnt = st_s_TRIPCOM_NVMDFLT.u4_wrt_cnt;
            st_tp_last->u4_crc32   = st_s_TRIPCOM_NVMDFLT.u4_crc32;

            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_REC_VALID;

            /* reset cmprchk flag */
            u1_t_rec_idx = u1_s_tripcom_nvmif_diag_idx;
            u1_t_ary_pos = u1_t_rec_idx >> TRIPCOM_NVMIF_SFT_DIV32;
            u1_t_bit_pos = u1_t_rec_idx  & (U1)TRIPCOM_NVMIF_MSK_MOD32;
            u4_s_tripcom_nvmif_diag_cmprchk[u1_t_ary_pos] &= ((U4)U4_MAX ^ ((U4)1U << u1_t_bit_pos));

            /* search next idx */
            u1_t_num_rec  = st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec;
            u1_t_diag_idx = u1_s_TripcomNvmIfLsbSrch(&u4_s_tripcom_nvmif_diag_cmprchk[0], u1_t_num_rec);
            if(u1_t_diag_idx < u1_t_num_rec){
                u1_s_tripcom_nvmif_diag_idx = u1_t_diag_idx;
                /* dummy request to continue diag nvm writting */
                (void)u1_s_TripcomNvmIfFifoPosIn(&st_s_tripcom_nvmif_fifo_ctrl, (U1)TRIPCOM_NVMIF_FIFO_MAX);
            }
            else{
                vd_g_TripcomNvmIfDiagFinish((U1)TRUE);
                u1_s_tripcom_nvmif_diag_ctrl = (U1)TRIPCOM_NVMIF_DIAG_CTRL_FIN;
            }
        }
        else if(u1_t_unk != (U1)FALSE){
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_REC_INVAL;
        }
        else if(u1_t_ch < (U1)TRIPCOM_NVMIF_CH_NUM){

            u1_t_rec_idx = (U1)(st_tp_next->u4_wrt_cnt % (U4)TRIPCOM_NVMIF_NUM_REC);
            u1_t_mul     = u1_g_TripcomCalcMulU1U1(u1_t_ch, (U1)TRIPCOM_NVMIF_NUM_REC);
            u1_t_rec_idx = u1_g_TripcomCalcAddU1U1(u1_t_rec_idx, u1_t_mul);

            st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx = u1_t_rec_idx;

            st_tp_last->u4_value   = st_tp_next->u4_value;
            st_tp_last->u4_wrt_cnt = st_tp_next->u4_wrt_cnt;
            st_tp_last->u4_crc32   = st_tp_next->u4_crc32;

            if(u4_sp_tripcom_nvmif_wrt_cnt[u1_t_ch] < (U4)U4_MAX){
                u4_sp_tripcom_nvmif_wrt_cnt[u1_t_ch]++;
            }

            st_tp_next->u4_value   = (U4)TRIPCOM_NVMIF_UNK;
            st_tp_next->u4_wrt_cnt = (U4)TRIPCOM_NVMIF_UNK;
            st_tp_next->u4_crc32   = (U4)TRIPCOM_NVMIF_UNK;

            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_REC_VALID;
        }
        else{
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_REC_NEXT;
        }
    }

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfWrichk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfWrichk(void)
{
    U1                      u1_t_rec_nblock;
    U1                      u1_t_blo_next;
    U1                      u1_t_sts_chk;

    u1_t_rec_nblock = st_g_TRIPCOM_NVMIF_REC_DATA.u1_rec_nblock;
    u1_t_blo_next   = st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt + (U1)1U;

    if(u1_t_blo_next >= u1_t_rec_nblock){
        u1_t_sts_chk  = (U1)TRIPCOM_NVMIF_CHK_OPE_CMPLT;
        u1_t_blo_next = (U1)0U;
    }
    else{
        u1_t_sts_chk = (U1)0x00U;
    }

    st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt  = u1_t_blo_next;

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfCmpchk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfCmpchk(void)
{
    ST_TRIPCOM_NVMDATA *    st_tp_last;
    ST_TRIPCOM_NVMDATA *    st_tp_rdbk;

    U2                      u2_t_rtry_cnt;

    U1                      u1_t_rec_nblock;
    U1                      u1_t_blo_next;
    U1                      u1_t_cmpr;
    U1                      u1_t_sts_chk;

    u1_t_rec_nblock = st_g_TRIPCOM_NVMIF_REC_DATA.u1_rec_nblock;
    u1_t_blo_next   = st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt + (U1)1U;
    u2_t_rtry_cnt   = st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt;

    if(u1_t_blo_next >= u1_t_rec_nblock){

        st_tp_last = &st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST];
        st_tp_rdbk = &st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_RDBK];
        u1_t_cmpr  = u1_s_TripcomNvmIfCmprAwB(st_tp_rdbk, st_tp_last);

        if((u1_t_rec_nblock == u1_s_tripcom_nvmif_rdbk_cnt  ) &&
           (u1_t_cmpr       == (U1)TRIPCOM_NVMIF_CMPR_A_EQ_B)){
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_OPE_CMPLT | (U1)TRIPCOM_NVMIF_CHK_REC_VALID;
            vd_g_TripcomMsSetNvmRslt(st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx / (U1)TRIPCOM_NVMIF_NUM_REC,
                                     (U1)TRIPCOM_MS_NVMSTS_SUC);
        }
        else if(u2_t_rtry_cnt >= (U2)TRIPCOM_NVMIF_RW_RTRY_MAX){
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_OPE_CMPLT | (U1)TRIPCOM_NVMIF_CHK_REC_NEXT;
            vd_g_TripcomMsSetNvmRslt(st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx / (U1)TRIPCOM_NVMIF_NUM_REC,
                                     (U1)TRIPCOM_MS_NVMSTS_FAIL);
        }
        else{
            u2_t_rtry_cnt++;
            /* The value of u4_t_rtry_cnt is determined whether it is larger than TRIPCOM_NVMIF_RW_RTRY_MAX within the if condition. */
            /* Therefor it is not necessary to check the wraparound.                                                                 */
            u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_OPE_CMPLT | (U1)TRIPCOM_NVMIF_CHK_REC_INVAL;
        }

        u1_t_blo_next               = (U1)0U;
        u1_s_tripcom_nvmif_rdbk_cnt = (U1)0U;
    }
    else{
        u1_t_sts_chk = (U1)0x00U;
    }

    st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt  = u1_t_blo_next;
    st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt = u2_t_rtry_cnt;

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfSynchk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfSynchk(void)
{
    ST_TRIPCOM_NVMDATA *    st_tp_last;
    ST_TRIPCOM_NVMDATA *    st_tp_rdbk;

    U2                      u2_t_rtry_cnt;

    U1                      u1_t_num_rec;
    U1                      u1_t_rec_nblock;
    U1                      u1_t_blo_next;
    U1                      u1_t_rec_idx;
    U1                      u1_t_rec_end;
    U1                      u1_t_rec_mrk;
    U1                      u1_t_unk;
    U1                      u1_t_cmpr;
    U1                      u1_t_sts_chk;
    U1                      u1_t_ch;
    U1                      u1_t_ch_next;

    u1_t_sts_chk    = (U1)0x00U;

    u1_t_num_rec    = st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec;
    u1_t_rec_nblock = st_g_TRIPCOM_NVMIF_REC_DATA.u1_rec_nblock;

    u1_t_rec_idx    = st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx;
    u1_t_rec_mrk    = st_s_tripcom_nvmif_rw_ctrl.u1_rec_mrk;
    u1_t_blo_next   = st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt + (U1)1U;
    u2_t_rtry_cnt   = st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt;

    u1_t_ch         = u1_t_rec_idx / (U1)TRIPCOM_NVMIF_NUM_REC;
    u1_t_rec_end    = (u1_t_ch + (U1)1U) * (U1)TRIPCOM_NVMIF_NUM_REC;

    if(u1_t_blo_next >= u1_t_rec_nblock){

        st_tp_last = &st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST];
        st_tp_rdbk = &st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_RDBK];
        u1_t_unk   = u1_s_TripcomNvmIfUnk(st_tp_rdbk);

        if((u1_t_rec_nblock == u1_s_tripcom_nvmif_rdbk_cnt) &&
           (u1_t_unk        == (U1)FALSE                  )){

            u1_t_cmpr  = u1_s_TripcomNvmIfCmprAwB(st_tp_rdbk, st_tp_last);
            if((u1_t_rec_mrk >= u1_t_num_rec                 ) ||
             /* u1_t_cmpr == TRIPCOM_NVMIF_CMPR_A_GT_B or TRIPCOM_NVMIF_CMPR_A_EQ_B */
               (u1_t_cmpr    <= (U1)TRIPCOM_NVMIF_CMPR_A_GT_B)){

                u1_t_rec_mrk = u1_t_rec_idx;

                st_tp_last->u4_value   = st_tp_rdbk->u4_value;
                st_tp_last->u4_wrt_cnt = st_tp_rdbk->u4_wrt_cnt;
                st_tp_last->u4_crc32   = st_tp_rdbk->u4_crc32;

                u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_REC_VALID;
            }
            else{
                u1_t_sts_chk = (U1)TRIPCOM_NVMIF_CHK_REC_NEXT;
            }

            if(u1_s_tripcom_nvmif_diag_ctrl == (U1)TRIPCOM_NVMIF_DIAG_CTRL_CMP){
                vd_s_TripcomNvmIfCmprNvmDflt(u1_t_rec_idx);
            }

            if(u1_t_rec_idx < (U1)U1_MAX){
                u1_t_rec_idx++;
            }
            u2_t_rtry_cnt = (U2)1U;
        }
        else if(u2_t_rtry_cnt >= (U2)TRIPCOM_NVMIF_RW_RTRY_MAX){
            if(u1_t_rec_idx < (U1)U1_MAX){
                u1_t_rec_idx++;
            }
            u2_t_rtry_cnt = (U2)1U;
            u1_t_sts_chk  = (U1)TRIPCOM_NVMIF_CHK_REC_NEXT;
        }
        else{
            u2_t_rtry_cnt++;
            /* Since u2_t_rtry_cnt is determined whether it is larger than TRIPCOM_NVMIF_RW_RTRY_MAX within the if condition,        */
            /* it is not necessary to check the wraparound.                                                                          */
            u1_t_sts_chk  = (U1)TRIPCOM_NVMIF_CHK_REC_INVAL;
        }

        if(u1_t_rec_idx >= u1_t_rec_end){
            if(u1_t_rec_mrk != (U1)U1_MAX){
                u4_sp_tripcom_nvmif_wrt_cnt[u1_t_ch] = u4_g_TripcomCalcAddU4U4(st_tp_last->u4_wrt_cnt, (U4)1U);
                vd_g_TripcomNvmIfCbkData(u1_t_ch, st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST].u4_value);
            }
            else{
                u4_sp_tripcom_nvmif_wrt_cnt[u1_t_ch] = (U4)0U;
                vd_g_TripcomNvmIfCbkData(u1_t_ch, (U4)0U);
            }
            u4_s_tripcom_nvmif_sync_reqbit &= ((U4)U4_MAX ^ ((U4)1U << u1_t_ch));

            u1_t_ch_next = u1_g_LsbSrch(u4_s_tripcom_nvmif_sync_reqbit);
            if(u1_t_ch_next < (U1)TRIPCOM_NVMIF_CH_NUM){
                u1_t_rec_idx = u1_t_ch_next * (U1)TRIPCOM_NVMIF_NUM_REC;
                u1_t_rec_mrk = (U1)U1_MAX;
            }
            else{
                u1_t_rec_idx = u1_t_rec_mrk;
                u1_t_sts_chk |= (U1)TRIPCOM_NVMIF_CHK_OPE_CMPLT;
                vd_g_TripcomNvmIfSyncCmplt();
            }
        }

        u1_t_blo_next               = (U1)0U;
        u1_s_tripcom_nvmif_rdbk_cnt = (U1)0U;
    }

    st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx  = u1_t_rec_idx;
    st_s_tripcom_nvmif_rw_ctrl.u1_rec_mrk  = u1_t_rec_mrk;
    st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt  = u1_t_blo_next;
    st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt = u2_t_rtry_cnt;

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfActToSeqCmplt(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfActToSeqCmplt(void)
{
    vd_g_TripcomNvmIfRWDeAct();
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfActToReqNext(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfActToReqNext(void)
{
    st_s_tripcom_nvmif_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_RW_REQ_NEXT;
    st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt = (U2)1U;

    u1_s_tripcom_nvmif_rdbk_cnt            = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfActToCbkNext(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfActToCbkNext(void)
{
    U1                      u1_t_ch;

    u1_t_ch = st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx / (U1)TRIPCOM_NVMIF_NUM_REC;
    vd_g_TripcomNvmIfCbkData(u1_t_ch, st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST].u4_value);

    st_s_tripcom_nvmif_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_RW_REQ_NEXT;
    st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt = (U2)1U;

    u1_s_tripcom_nvmif_rdbk_cnt            = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfActToSynCmplt(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfActToSynCmplt(void)
{
    U1                      u1_t_ch;
    U1                      u1_t_diag_idx;
    U1                      u1_t_num_rec;

    u1_t_ch = st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx / (U1)TRIPCOM_NVMIF_NUM_REC;
    vd_g_TripcomNvmIfCbkData(u1_t_ch, st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST].u4_value);

    st_s_tripcom_nvmif_fifo_ctrl.u2_len     = (U2)0U;
    st_s_tripcom_nvmif_fifo_ctrl.u1_pos_in  = (U1)0U;
    st_s_tripcom_nvmif_fifo_ctrl.u1_pos_out = (U1)0U;

    st_s_tripcom_nvmif_rw_ctrl.u1_rec_chk   = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt   = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u2_rw_ctrl   = (U2)TRIPCOM_NVMIF_RW_REQ_NEXT;
    st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt  = (U2)1U;

    u1_s_tripcom_nvmif_rdbk_cnt             = (U1)0U;

    vd_g_TripcomNvmIfRWDeAct();

    /* diag compare finished */
    if(u1_s_tripcom_nvmif_diag_ctrl == (U1)TRIPCOM_NVMIF_DIAG_CTRL_CMP){
        if(u1_s_tripcom_nvmif_diag_req == (U1)TRIPCOM_NVMIF_DIAG_REQ_CMP){
            u1_t_num_rec  = st_g_TRIPCOM_NVMIF_REC_DATA.u1_num_rec;
            u1_t_diag_idx = u1_s_TripcomNvmIfLsbSrch(&u4_s_tripcom_nvmif_diag_cmprchk[0], u1_t_num_rec);
            if(u1_t_diag_idx >= u1_t_num_rec){
                vd_g_TripcomNvmIfDiagFinish((U1)TRUE);
            }
            else{
                vd_g_TripcomNvmIfDiagFinish((U1)FALSE);
            }

            u1_s_tripcom_nvmif_diag_ctrl = (U1)TRIPCOM_NVMIF_DIAG_CTRL_FIN;
        }
        /* u1_s_tripcom_nvmif_diag_req == (U1)TRIPCOM_NVMIF_DIAG_REQ_WRI */
        else{
            /* dummy request to start diag nvm writting */
            (void)u1_g_TripcomNvmIfRWRqst((U1)0U, vdp_PTR_NA);
            u1_s_tripcom_nvmif_diag_idx  = (U1)0U;
            u1_s_tripcom_nvmif_diag_ctrl = (U1)TRIPCOM_NVMIF_DIAG_CTRL_WRI;
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfActWriNext(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfActWriNext(void)
{
    vd_s_TripcomNvmIfWrite(&st_g_TRIPCOM_NVMIF_REC_DATA, &st_s_tripcom_nvmif_rw_ctrl,
                           (U1 *)&st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfActToWriNext(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfActToWriNext(void)
{
    st_s_tripcom_nvmif_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_RW_WRI_NEXT;
    st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt = (U2)1U;

    u1_s_tripcom_nvmif_rdbk_cnt            = (U1)0U;

    vd_s_TripcomNvmIfWrite(&st_g_TRIPCOM_NVMIF_REC_DATA, &st_s_tripcom_nvmif_rw_ctrl,
                           (U1 *)&st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfActReaNext(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfActReaNext(void)
{
    vd_s_TripcomNvmIfRead(&st_g_TRIPCOM_NVMIF_REC_DATA, &st_s_tripcom_nvmif_rw_ctrl);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfActToCmpNext(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfActToCmpNext(void)
{
    st_s_tripcom_nvmif_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_RW_CMP_NEXT;
    st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt = (U2)1U;

    vd_s_TripcomNvmIfRead(&st_g_TRIPCOM_NVMIF_REC_DATA, &st_s_tripcom_nvmif_rw_ctrl);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfActToSynLast(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfActToSynLast(void)
{
    ST_TRIPCOM_NVMDATA *    st_tp_last;
    U1                      u1_t_rec_idx;
    U1                      u1_t_ch;

    st_tp_last = &st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_LAST];
    st_tp_last->u4_value                   = (U4)TRIPCOM_NVMIF_UNK;
    st_tp_last->u4_wrt_cnt                 = (U4)TRIPCOM_NVMIF_UNK;
    st_tp_last->u4_crc32                   = (U4)TRIPCOM_NVMIF_UNK;

    u1_t_rec_idx = (U1)0U;
    u1_t_ch      = u1_g_LsbSrch(u4_s_tripcom_nvmif_sync_reqbit);
    if(u1_t_ch < (U1)TRIPCOM_NVMIF_CH_NUM){
        u1_t_rec_idx = u1_t_ch * (U1)TRIPCOM_NVMIF_NUM_REC;
    }
    st_s_tripcom_nvmif_rw_ctrl.u1_rec_idx  = (U1)u1_t_rec_idx;
    st_s_tripcom_nvmif_rw_ctrl.u1_rec_mrk  = (U1)U1_MAX;

    st_s_tripcom_nvmif_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u1_blo_cnt  = (U1)0U;
    st_s_tripcom_nvmif_rw_ctrl.u2_rw_ctrl  = (U2)TRIPCOM_NVMIF_RW_SYN_LAST;
    st_s_tripcom_nvmif_rw_ctrl.u2_rtry_cnt = (U2)1U;

    u1_s_tripcom_nvmif_rdbk_cnt            = (U1)0U;

    vd_s_TripcomNvmIfRead(&st_g_TRIPCOM_NVMIF_REC_DATA, &st_s_tripcom_nvmif_rw_ctrl);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_TripcomNvmIfFifoPosIn(ST_TRIPCOM_NVMIF_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfFifoPosIn(ST_TRIPCOM_NVMIF_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)
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
/*  static U1      u1_s_TripcomNvmIfFifoPosOut(ST_TRIPCOM_NVMIF_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfFifoPosOut(ST_TRIPCOM_NVMIF_FIFO_CTRL * st_ap_ctrl, const U1 u1_a_MAX)
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
/*  static void    vd_s_TripcomNvmIfWrite(const ST_TRIPCOM_NVMIF_REC_DATA * st_ap_REC_DATA,                                          */
/*                                        const ST_TRIPCOM_NVMIF_RW_CTRL * st_ap_CTRL,                                               */
/*                                        const U1 * u1_ap_DATA)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfWrite(const ST_TRIPCOM_NVMIF_REC_DATA * st_ap_REC_DATA,
                                      const ST_TRIPCOM_NVMIF_RW_CTRL * st_ap_CTRL,
                                      const U1 * u1_ap_DATA)
{
    const U2 *              u2_tp_BLOCK;
    U2                      u2_t_blo_next;
    U2                      u2_t_src_offset;

    u2_tp_BLOCK     = st_ap_REC_DATA->u2p_BLOCK;
    u2_t_blo_next   = ((U2)st_ap_CTRL->u1_rec_idx * (U2)st_ap_REC_DATA->u1_rec_nblock) + (U2)st_ap_CTRL->u1_blo_cnt;
    u2_t_src_offset = (U2)st_ap_CTRL->u1_blo_cnt * (U2)st_ap_REC_DATA->u1_blo_nbyte;
    vd_g_TripcomNvmIfWriteBlock(st_ap_REC_DATA->u1_dev_idx,
                                u2_tp_BLOCK[u2_t_blo_next],
                                &u1_ap_DATA[u2_t_src_offset],
                                (U2)st_ap_REC_DATA->u1_blo_nbyte);
}
/*===================================================================================================================================*/
/*  static void    vd_s_TripcomNvmIfRead(const ST_TRIPCOM_NVMIF_REC_DATA * st_ap_REC_DATA,                                           */
/*                                       const ST_TRIPCOM_NVMIF_RW_CTRL * st_ap_CTRL)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfRead(const ST_TRIPCOM_NVMIF_REC_DATA * st_ap_REC_DATA,
                                     const ST_TRIPCOM_NVMIF_RW_CTRL * st_ap_CTRL)
{
    const U2 *              u2_tp_BLOCK;
    U2                      u2_t_blo_next;

    u2_tp_BLOCK   = st_ap_REC_DATA->u2p_BLOCK;
    u2_t_blo_next = ((U2)st_ap_CTRL->u1_rec_idx * (U2)st_ap_REC_DATA->u1_rec_nblock) + (U2)st_ap_CTRL->u1_blo_cnt;
    vd_g_TripcomNvmIfReadBlock(st_ap_REC_DATA->u1_dev_idx, u2_tp_BLOCK[u2_t_blo_next]);
}
/*===================================================================================================================================*/
/* U1      u1_s_TripcomNvmIfUnk(const ST_TRIPCOM_NVMDATA * st_ap_DATA)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfUnk(const ST_TRIPCOM_NVMDATA * st_ap_DATA)
{
    U4                      u4_t_crc32;
    U1                      u1_t_unk;

    u1_t_unk = (U1)TRUE;
    if(st_ap_DATA->u4_wrt_cnt != (U4)TRIPCOM_NVMIF_UNK){

        u4_t_crc32 = u4_g_TripcomNvmIfCrc32((const U1 *)st_ap_DATA, ((U4)sizeof(ST_TRIPCOM_NVMDATA) - (U4)TRIPCOM_NVMIF_NBYTE_CRC_32));
        if(u4_t_crc32 == st_ap_DATA->u4_crc32){
            u1_t_unk = (U1)FALSE;
        }
    }

    return(u1_t_unk);
}
/*===================================================================================================================================*/
/* U1      u1_s_TripcomNvmIfCmprAwB(const ST_TRIPCOM_NVMDATA * st_ap_CMPR_A, const ST_TRIPCOM_NVMDATA * st_ap_CMPR_B)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfCmprAwB(const ST_TRIPCOM_NVMDATA * st_ap_CMPR_A, const ST_TRIPCOM_NVMDATA * st_ap_CMPR_B)
{
    U1                      u1_t_cmpr;
    U4                      u4_t_crc32_a;
    U4                      u4_t_crc32_b;

    u4_t_crc32_a = st_ap_CMPR_A->u4_crc32;                /* Don't judge volatile variables for QAC */
    u4_t_crc32_b = st_ap_CMPR_B->u4_crc32;

    if(st_ap_CMPR_A->u4_wrt_cnt > st_ap_CMPR_B->u4_wrt_cnt){
        u1_t_cmpr = (U1)TRIPCOM_NVMIF_CMPR_A_GT_B;
    }
    else if(st_ap_CMPR_A->u4_wrt_cnt < st_ap_CMPR_B->u4_wrt_cnt){
        u1_t_cmpr = (U1)TRIPCOM_NVMIF_CMPR_A_LT_B;
    }
    else if((st_ap_CMPR_A->u4_value == st_ap_CMPR_B->u4_value) &&
            (u4_t_crc32_a           == u4_t_crc32_b          )){
        u1_t_cmpr = (U1)TRIPCOM_NVMIF_CMPR_A_EQ_B;
    }
    else{
        u1_t_cmpr = (U1)TRIPCOM_NVMIF_CMPR_UNK;
    }

    return(u1_t_cmpr);
}
/*===================================================================================================================================*/
/* void    vd_s_TripcomNvmIfCmprNvmDflt(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmIfCmprNvmDflt(const U1 u1_a_REC_IDX)
{
    ST_TRIPCOM_NVMDATA *    st_tp_rdbk;
    U1                      u1_t_ary_pos;
    U1                      u1_t_bit_pos;
    U4                      u4_t_crc32_a;
    U4                      u4_t_crc32_b;

    st_tp_rdbk   = &st_sp_tripcom_nvmif_rw_data[TRIPCOM_NVMIF_RW_DAT_RDBK];
    u4_t_crc32_a = st_tp_rdbk->u4_crc32;                /* Don't judge volatile variables for QAC */
    u4_t_crc32_b = st_s_TRIPCOM_NVMDFLT.u4_crc32;

    if((st_tp_rdbk->u4_value   == st_s_TRIPCOM_NVMDFLT.u4_value  ) &&
       (st_tp_rdbk->u4_wrt_cnt == st_s_TRIPCOM_NVMDFLT.u4_wrt_cnt) &&
       (u4_t_crc32_a           == u4_t_crc32_b                   )){
        /* cmpr success : do nothing */
    }
    else{
        /* cmpr failed */
        u1_t_ary_pos = u1_a_REC_IDX >> TRIPCOM_NVMIF_SFT_DIV32;
        u1_t_bit_pos = u1_a_REC_IDX  & (U1)TRIPCOM_NVMIF_MSK_MOD32;
        u4_s_tripcom_nvmif_diag_cmprchk[u1_t_ary_pos] |= ((U4)1U << u1_t_bit_pos);
    }
}
/*===================================================================================================================================*/
/* U1      u1_s_TripcomNvmIfLsbSrch(const U4 * u4_ap_SRCH, const U1 u1_a_BITLEN)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TripcomNvmIfLsbSrch(const U4 * u4_ap_SRCH, const U1 u1_a_BITLEN)
{
    U1                      u1_t_ary_pos;
    U1                      u1_t_ary_siz;
    U1                      u1_t_ret;

    u1_t_ary_siz = (u1_a_BITLEN / (U1)TRIPCOM_NVMIF_U4_BITLEN) + (U1)1U;

    u1_t_ary_pos = (U1)0U;
    while((u1_t_ary_pos             <  (U1)u1_t_ary_siz) &&
          (u4_ap_SRCH[u1_t_ary_pos] == (U4)0U          )){
        u1_t_ary_pos++;
    }

    if(u1_t_ary_pos < u1_t_ary_siz){
        u1_t_ret  = u1_t_ary_pos * (U1)TRIPCOM_NVMIF_U4_BITLEN;
        u1_t_ret  = u1_g_TripcomCalcAddU1U1(u1_t_ret, u1_g_LsbSrch(u4_s_tripcom_nvmif_diag_cmprchk[u1_t_ary_pos]));
    }
    else{
        u1_t_ret  = (U1)LSB_SRCH_NOT_FOUND;
    }
    
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* static void    vd_s_TripcomNvmCrcChk(ST_TRIPCOM_NVMDATA * st_a_rdbk)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TripcomNvmCrcChk(ST_TRIPCOM_NVMDATA * st_a_rdbk)
{
    if((st_a_rdbk->u4_crc32   == (U4)0U) &&
       (st_a_rdbk->u4_wrt_cnt == (U4)0U) &&
       (st_a_rdbk->u4_value   == (U4)0U)){
        st_a_rdbk->u4_crc32 = (U4)TRIPCOM_NVMIF_CRC32_INIT;
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
/*  1.0.0     4/26/2021  YA       New.                                                                                               */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/25/2021  TA(M)    Supports TripA and TripB.                                                                          */
/*  2.0.3    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.1.0    02/25/2022  TA(M)    Add vd_g_TripcomNvmIfSyncCmplt and                                                                 */
/*                                  a process to call vd_g_TripcomNvmIfSyncCmplt when reading non-volatile memory data is completed. */
/*                                                                                                                                   */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
