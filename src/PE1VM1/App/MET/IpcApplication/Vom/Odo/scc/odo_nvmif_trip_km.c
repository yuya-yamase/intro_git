/* 2.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Odo Non-Volatile Memory Interface                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_NVMIF_TRIP_KM_C_MAJOR                (2)
#define ODO_NVMIF_TRIP_KM_C_MINOR                (0)
#define ODO_NVMIF_TRIP_KM_C_PATCH                (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "odo_nvmif_cfg_private.h"
#include "odo_nvmif_km.h"
#include "odo_nvmif_util.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ODO_NVMIF_TRIP_KM_C_MAJOR != ODO_NVMIF_H_MAJOR) || \
     (ODO_NVMIF_TRIP_KM_C_MINOR != ODO_NVMIF_H_MINOR) || \
     (ODO_NVMIF_TRIP_KM_C_PATCH != ODO_NVMIF_H_PATCH))
#error "odo_nvmif_trip_km.c and odo_nvmif.h : source and header files are inconsistent!"
#endif

#if ((ODO_NVMIF_TRIP_KM_C_MAJOR != ODO_NVMIF_CFG_H_MAJOR) || \
     (ODO_NVMIF_TRIP_KM_C_MINOR != ODO_NVMIF_CFG_H_MINOR) || \
     (ODO_NVMIF_TRIP_KM_C_PATCH != ODO_NVMIF_CFG_H_PATCH))
#error "odo_nvmif_trip_km.c and odo_nvmif_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((ODO_NVMIF_TRIP_KM_C_MAJOR != ODO_NVMIF_KM_H_MAJOR) || \
     (ODO_NVMIF_TRIP_KM_C_MINOR != ODO_NVMIF_KM_H_MINOR) || \
     (ODO_NVMIF_TRIP_KM_C_PATCH != ODO_NVMIF_KM_H_PATCH))
#error "odo_nvmif_trip_km.c and odo_nvmif_km.h : source and header files are inconsistent!"
#endif

#if ((ODO_NVMIF_TRIP_KM_C_MAJOR != ODO_NVMIF_UTIL_H_MAJOR) || \
     (ODO_NVMIF_TRIP_KM_C_MINOR != ODO_NVMIF_UTIL_H_MINOR) || \
     (ODO_NVMIF_TRIP_KM_C_PATCH != ODO_NVMIF_UTIL_H_PATCH))
#error "odo_nvmif_trip_km.c and odo_nvmif_util.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_NVMIF_TRIP_RW_NUM_STS                (5U)
#define ODO_NVMIF_TRIP_RW_REQ_NEXT               (0U)
#define ODO_NVMIF_TRIP_RW_WRI_NEXT               (1U)
#define ODO_NVMIF_TRIP_RW_CMP_NEXT               (2U)
#define ODO_NVMIF_TRIP_RW_SYN_LAST               (3U)
#define ODO_NVMIF_TRIP_RW_SYN_INIT               (4U)

#define ODO_NVMIF_TRIP_CHK_SEQ_ABORT             (0x08U)
#define ODO_NVMIF_TRIP_CHK_OPE_CMPLT             (0x04U)
#define ODO_NVMIF_TRIP_CHK_REC_NEXT              (0x03U)
#define ODO_NVMIF_TRIP_CHK_REC_VALID             (0x02U)
#define ODO_NVMIF_TRIP_CHK_REC_INVAL             (0x01U)

#define ODO_NVMIF_TRIP_ACT_TO_SEQ_CMPLT          (0U)
#define ODO_NVMIF_TRIP_ACT_TO_REQ_NEXT           (1U)
#define ODO_NVMIF_TRIP_ACT_TO_CBK_NEXT           (2U)
#define ODO_NVMIF_TRIP_ACT_TO_CBK_UNK            (3U)
#define ODO_NVMIF_TRIP_ACT_WRI_NEXT              (4U)
#define ODO_NVMIF_TRIP_ACT_TO_WRI_NEXT           (5U)
#define ODO_NVMIF_TRIP_ACT_TO_WRI_RTRY           (6U)
#define ODO_NVMIF_TRIP_ACT_CMP_NEXT              (7U)
#define ODO_NVMIF_TRIP_ACT_TO_CMP_NEXT           (8U)
#define ODO_NVMIF_TRIP_ACT_SYN_LAST              (9U)
#define ODO_NVMIF_TRIP_ACT_TO_SYN_LAST           (10U)
#define ODO_NVMIF_TRIP_ACT_TO_SYN_ABORT          (11U)

#define ODO_NVMIF_TRIP_FIFO_MAX                  (4U)

#define ODO_NVMIF_TRIP_SYN_RTRY_MAX              (2U)
#define ODO_NVMIF_TRIP_RW_RTRY_MAX               (4U)

#define ODO_NVMIF_TRIP_CMP_NUM_CHK               (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_ODO_KM                  st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_NUM_KM];
static ST_ODO_NVMIF_RW_CTRL       st_s_odo_nvmif_trip_rw_ctrl;
static U1                         u1_s_odo_nvmif_trip_rdbk_cnt;

static ST_ODO_KM                  st_sp_odo_nvmif_trip_fifo_km[ODO_NVMIF_TRIP_FIFO_MAX];
static U1                         u1_sp_odo_nvmif_trip_fifo_ch[ODO_NVMIF_TRIP_FIFO_MAX];
static ST_ODO_NVMIF_FIFO_CTRL     st_s_odo_nvmif_trip_fifo_ctrl;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_OdoNvmIfTripSynInit(void);

static U1      u1_s_OdoNvmIfTripAbortchk(void);
static U1      u1_s_OdoNvmIfTripReqchk(void);
static U1      u1_s_OdoNvmIfTripWrichk(void);
static U1      u1_s_OdoNvmIfTripCmpchk(void);
static U1      u1_s_OdoNvmIfTripSynchk(void);

static void    vd_s_OdoNvmIfTripActToSeqCmplt(void);
static void    vd_s_OdoNvmIfTripActToReqNext(void);
static void    vd_s_OdoNvmIfTripActToCbkNext(void);
static void    vd_s_OdoNvmIfTripActToCbkUnk(void);
static void    vd_s_OdoNvmIfTripActWriNext(void);
static void    vd_s_OdoNvmIfTripActToWriNext(void);
static void    vd_s_OdoNvmIfTripActToWriRtry(void);
static void    vd_s_OdoNvmIfTripActReaNext(void);
static void    vd_s_OdoNvmIfTripActToCmpNext(void);
static void    vd_s_OdoNvmIfTripActToSynLast(void);
static void    vd_s_OdoNvmIfTripActToSynAbort(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_ODO_KM            st_s_ODO_NVMIF_TRIP_UNK = {
    (U4)ODO_KM_UNK,
    (U4)ODO_KM_UNK,
    (U4)ODO_KM_UNK
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_OdoNvmIfTripInit(const U1 u1_a_SYNC)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoNvmIfTripInit(const U1 u1_a_SYNC)
{
    const U2 *              u2_tp_BLOCK;
    U4                      u4_t_lpcnt;
    U4                      u4_t_crc32;
    U1                      u1_t_num_rec;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ODO_NVMIF_RW_NUM_KM; u4_t_lpcnt++){
        st_sp_odo_nvmif_trip_rw_km[u4_t_lpcnt].u4_ge_m  = (U4)ODO_KM_UNK;
        st_sp_odo_nvmif_trip_rw_km[u4_t_lpcnt].u4_lt_m  = (U4)ODO_KM_UNK;
        st_sp_odo_nvmif_trip_rw_km[u4_t_lpcnt].u4_crc32 = (U4)ODO_KM_UNK;
    }

    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx  = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk  = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk  = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt  = (U1)0U;

    st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl  = (U2)ODO_NVMIF_TRIP_RW_SYN_INIT;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt = (U2)1U;

    u4_t_crc32 = u4_g_OdoNvmIfCrc32((U1 *)&st_s_odo_nvmif_trip_rw_ctrl,
                                    ((U4)sizeof(ST_ODO_NVMIF_RW_CTRL) - (U4)ODO_NVMIF_NBYTE_CRC_32));
    st_s_odo_nvmif_trip_rw_ctrl.u4_crc32    = u4_t_crc32;

    u1_s_odo_nvmif_trip_rdbk_cnt            = (U1)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ODO_NVMIF_TRIP_FIFO_MAX; u4_t_lpcnt++){

        st_sp_odo_nvmif_trip_fifo_km[u4_t_lpcnt].u4_ge_m  = (U4)ODO_KM_UNK;
        st_sp_odo_nvmif_trip_fifo_km[u4_t_lpcnt].u4_lt_m  = (U4)ODO_KM_UNK;
        st_sp_odo_nvmif_trip_fifo_km[u4_t_lpcnt].u4_crc32 = (U4)ODO_KM_UNK;

        u1_sp_odo_nvmif_trip_fifo_ch[u4_t_lpcnt]          = (U1)U1_MAX;
    }

    st_s_odo_nvmif_trip_fifo_ctrl.u2_len     = (U2)0U;
    st_s_odo_nvmif_trip_fifo_ctrl.u1_pos_in  = (U1)0U;
    st_s_odo_nvmif_trip_fifo_ctrl.u1_pos_out = (U1)0U;

    u2_tp_BLOCK  = st_g_ODO_NVMIF_REC_TRIP_KM.u2p_BLOCK;
    u1_t_num_rec = st_g_ODO_NVMIF_REC_TRIP_KM.u1_num_rec;
    if((u2_tp_BLOCK  == vdp_PTR_NA) ||
       (u1_t_num_rec == (U1)0U    )){
    }
    else if(u1_a_SYNC == (U1)TRUE){
        vd_s_OdoNvmIfTripSynInit();
    }
    else{
        vd_g_OdoNvmIfTripRWAct();
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_OdoNvmIfTripRWRqst(const U1 u1_a_CH, const ST_ODO_KM * st_ap_KM_NEXT)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OdoNvmIfTripRWRqst(const U1 u1_a_CH, const ST_ODO_KM * st_ap_KM_NEXT)
{
    const U2 *              u2_tp_BLOCK;

    ST_ODO_KM *             st_tp_km_next;

    U2                      u2_t_rec_ch;
    U2                      u2_t_num_rec;

    U1                      u1_t_fifo_in;
    U1                      u1_t_accpt;

    u1_t_accpt = (U1)FALSE;

    u2_tp_BLOCK  = st_g_ODO_NVMIF_REC_TRIP_KM.u2p_BLOCK;
    u2_t_num_rec = (U2)st_g_ODO_NVMIF_REC_TRIP_KM.u1_num_rec;
    u2_t_rec_ch  = (U2)((U2)u1_a_CH << 1U) + (U2)ODO_NVMIF_TRIP_NUM_REC;
    if((u2_tp_BLOCK  == vdp_PTR_NA) ||
       (u2_t_num_rec == (U2)0U    )){
        vd_g_OdoNvmIfTripRWDeAct();
    }
    else if((st_ap_KM_NEXT == vdp_PTR_NA) ||
            (u2_t_rec_ch   >  u2_t_num_rec           )){
    }
    else{

        u1_t_fifo_in = u1_g_OdoNvmIfFifoPosIn(&st_s_odo_nvmif_trip_fifo_ctrl, (U1)ODO_NVMIF_TRIP_FIFO_MAX);
        if(u1_t_fifo_in < (U1)ODO_NVMIF_TRIP_FIFO_MAX){

            u1_sp_odo_nvmif_trip_fifo_ch[u1_t_fifo_in] = u1_a_CH;

            st_tp_km_next = &st_sp_odo_nvmif_trip_fifo_km[u1_t_fifo_in];
            st_tp_km_next->u4_ge_m  = st_ap_KM_NEXT->u4_ge_m;
            st_tp_km_next->u4_lt_m  = st_ap_KM_NEXT->u4_lt_m;
            st_tp_km_next->u4_crc32 = st_ap_KM_NEXT->u4_crc32;

            vd_g_OdoNvmIfTripRWAct();

            u1_t_accpt = (U1)TRUE;
        }
    }

    return(u1_t_accpt);
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoNvmIfTripRWTask(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoNvmIfTripRWTask(void)
{
    static U1 ( * const     fp_sp_u1_ODO_NVMIF_TRIP_CHK[])(void) = {
        &u1_s_OdoNvmIfTripReqchk,
        &u1_s_OdoNvmIfTripWrichk,
        &u1_s_OdoNvmIfTripCmpchk,
        &u1_s_OdoNvmIfTripSynchk
    };

    static const U1         u1_sp_ODO_NVMIF_TRIP_RW_STM[] = {
        (U1)ODO_NVMIF_TRIP_ACT_TO_REQ_NEXT,  (U1)ODO_NVMIF_TRIP_ACT_WRI_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_CMP_NEXT,     (U1)ODO_NVMIF_TRIP_ACT_SYN_LAST,
        (U1)ODO_NVMIF_TRIP_ACT_TO_REQ_NEXT,  (U1)ODO_NVMIF_TRIP_ACT_WRI_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_CMP_NEXT,     (U1)ODO_NVMIF_TRIP_ACT_SYN_LAST,
        (U1)ODO_NVMIF_TRIP_ACT_TO_WRI_NEXT,  (U1)ODO_NVMIF_TRIP_ACT_WRI_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_CMP_NEXT,     (U1)ODO_NVMIF_TRIP_ACT_SYN_LAST,
        (U1)ODO_NVMIF_TRIP_ACT_TO_REQ_NEXT,  (U1)ODO_NVMIF_TRIP_ACT_WRI_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_CMP_NEXT,     (U1)ODO_NVMIF_TRIP_ACT_SYN_LAST,
        (U1)ODO_NVMIF_TRIP_ACT_TO_SEQ_CMPLT, (U1)ODO_NVMIF_TRIP_ACT_TO_CMP_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_TO_WRI_RTRY,  (U1)ODO_NVMIF_TRIP_ACT_TO_REQ_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_TO_SEQ_CMPLT, (U1)ODO_NVMIF_TRIP_ACT_TO_CMP_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_TO_CMP_NEXT,  (U1)ODO_NVMIF_TRIP_ACT_TO_REQ_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_TO_SEQ_CMPLT, (U1)ODO_NVMIF_TRIP_ACT_TO_CMP_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_TO_CBK_NEXT,  (U1)ODO_NVMIF_TRIP_ACT_TO_REQ_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_TO_SEQ_CMPLT, (U1)ODO_NVMIF_TRIP_ACT_TO_CMP_NEXT,
        (U1)ODO_NVMIF_TRIP_ACT_TO_CBK_UNK,   (U1)ODO_NVMIF_TRIP_ACT_TO_REQ_NEXT
    };

    static void ( * const   fp_vd_ODO_NVMIF_TRIP_ACT[])(void) = {
        &vd_s_OdoNvmIfTripActToSeqCmplt,                       /* ODO_NVMIF_TRIP_ACT_TO_SEQ_CMPLT (0U)  */
        &vd_s_OdoNvmIfTripActToReqNext,                        /* ODO_NVMIF_TRIP_ACT_TO_REQ_NEXT  (1U)  */
        &vd_s_OdoNvmIfTripActToCbkNext,                        /* ODO_NVMIF_TRIP_ACT_TO_CBK_NEXT  (2U)  */
        &vd_s_OdoNvmIfTripActToCbkUnk,                         /* ODO_NVMIF_TRIP_ACT_TO_CBK_UNK   (3U)  */
        &vd_s_OdoNvmIfTripActWriNext,                          /* ODO_NVMIF_TRIP_ACT_WRI_NEXT     (4U)  */
        &vd_s_OdoNvmIfTripActToWriNext,                        /* ODO_NVMIF_TRIP_ACT_TO_WRI_NEXT  (5U)  */
        &vd_s_OdoNvmIfTripActToWriRtry,                        /* ODO_NVMIF_TRIP_ACT_TO_WRI_RTRY  (6U)  */
        &vd_s_OdoNvmIfTripActReaNext,                          /* ODO_NVMIF_TRIP_ACT_CMP_NEXT     (7U)  */
        &vd_s_OdoNvmIfTripActToCmpNext,                        /* ODO_NVMIF_TRIP_ACT_TO_CMP_NEXT  (8U)  */
        &vd_s_OdoNvmIfTripActReaNext,                          /* ODO_NVMIF_TRIP_ACT_SYN_LAST     (9U)  */
        &vd_s_OdoNvmIfTripActToSynLast,                        /* ODO_NVMIF_TRIP_ACT_TO_SYN_LAST  (10U) */
        &vd_s_OdoNvmIfTripActToSynAbort                        /* ODO_NVMIF_TRIP_ACT_TO_SYN_ABORT (11U) */
    };

    U4                      u4_t_crc32;
    U2                      u2_t_rw_act;
    U2                      u2_t_rw_ctrl;

    U1                      u1_t_sts_chk;

    u2_t_rw_ctrl = st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl;
    u1_t_sts_chk = u1_s_OdoNvmIfTripAbortchk();
    if(u1_t_sts_chk != (U1)0U){
        u2_t_rw_act  = (U2)ODO_NVMIF_TRIP_ACT_TO_SYN_ABORT;
    }
    else if(u2_t_rw_ctrl >= (U2)ODO_NVMIF_TRIP_RW_SYN_INIT){
        u2_t_rw_act  = (U2)ODO_NVMIF_TRIP_ACT_TO_SYN_LAST;
    }
    else{
        u1_t_sts_chk = (fp_sp_u1_ODO_NVMIF_TRIP_CHK[u2_t_rw_ctrl])();
        u2_t_rw_act  = ((U2)u1_t_sts_chk * (U2)ODO_NVMIF_TRIP_RW_SYN_INIT) + u2_t_rw_ctrl;
        u2_t_rw_act  = (U2)u1_sp_ODO_NVMIF_TRIP_RW_STM[u2_t_rw_act];
    }

    (*fp_vd_ODO_NVMIF_TRIP_ACT[u2_t_rw_act])();

    u4_t_crc32 = u4_g_OdoNvmIfCrc32((U1 *)&st_s_odo_nvmif_trip_rw_ctrl,
                                    ((U4)sizeof(ST_ODO_NVMIF_RW_CTRL) - (U4)ODO_NVMIF_NBYTE_CRC_32));
    st_s_odo_nvmif_trip_rw_ctrl.u4_crc32 = u4_t_crc32;
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoNvmIfTripRWFinhk(const U2 u2_a_BLOCKID,                                                                          */
/*                                   const U1 u1_a_REQUEST_TYPE,                                                                     */
/*                                   const U1 u1_a_RESULT,                                                                           */
/*                                   const U1 * const u1_ap_DATA,                                                                    */
/*                                   const U2 u2_a_SIZE)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoNvmIfTripRWFinhk(const U2 u2_a_BLOCKID,
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

    u1_t_rec_nblock = st_g_ODO_NVMIF_REC_TRIP_KM.u1_rec_nblock;
    u1_t_blo_nbyte  = st_g_ODO_NVMIF_REC_TRIP_KM.u1_blo_nbyte;
    u1_t_blo_cnt    = st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt;

    if((u1_a_REQUEST_TYPE == (U1)ODO_NVMIF_REQ_TYPE_READ) &&
       (u1_a_RESULT       == (U1)ODO_NVMIF_JOB_RESULT_OK) &&
       (u1_ap_DATA        != vdp_PTR_NA                 ) &&
       (u2_a_SIZE         == (U2)u1_t_blo_nbyte         ) &&
       (u1_t_blo_cnt      <  u1_t_rec_nblock            )){

        u2_t_rdbk_offset = (U2)u1_t_blo_cnt * (U2)u1_t_blo_nbyte;
        u1_tp_dst        = (U1 *)&st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_KM_RDBK];
        u1_tp_dst        = &u1_tp_dst[u2_t_rdbk_offset];
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_t_blo_nbyte; u4_t_lpcnt++){
            u1_tp_dst[u4_t_lpcnt] = u1_ap_DATA[u4_t_lpcnt];
        }
        if(u1_s_odo_nvmif_trip_rdbk_cnt < (U1)U1_MAX){
            u1_s_odo_nvmif_trip_rdbk_cnt++;
	    }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripSynInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripSynInit(void)
{
    const U2 *              u2_tp_BLOCK;

    ST_ODO_KM               st_t_km_rdbk;
    U1 *                    u1_tp_rdbk;

    U4                      u4_t_num_rec;
    U4                      u4_t_rec_nblock;
    U4                      u4_t_rec_idx;
    U4                      u4_t_rec_begin;

    U4                      u4_t_blo_idx;
    U4                      u4_t_blo_end;

    U4                      u4_t_rtry_cnt;
    U4                      u4_t_crc32;

    U2                      u2_t_blo_nbyte;
    U2                      u2_t_rdbk_offset;

    U1                      u1_t_dev_idx;
    U1                      u1_t_rdrslt;
    U1                      u1_t_unk;

    st_t_km_rdbk.u4_ge_m  = (U4)ODO_KM_UNK;
    st_t_km_rdbk.u4_lt_m  = (U4)ODO_KM_UNK;
    st_t_km_rdbk.u4_crc32 = (U4)ODO_KM_UNK;
    u1_tp_rdbk            = (U1 *)&st_t_km_rdbk;

    u2_tp_BLOCK           = st_g_ODO_NVMIF_REC_TRIP_KM.u2p_BLOCK;
    u4_t_num_rec          = (U4)st_g_ODO_NVMIF_REC_TRIP_KM.u1_num_rec;
    u4_t_rec_nblock       = (U4)st_g_ODO_NVMIF_REC_TRIP_KM.u1_rec_nblock;
    u2_t_blo_nbyte        = (U2)st_g_ODO_NVMIF_REC_TRIP_KM.u1_blo_nbyte;
    u1_t_dev_idx          = st_g_ODO_NVMIF_REC_TRIP_KM.u1_dev_idx;

    u4_t_rec_idx    = (U4)0U;
    u4_t_rec_begin  = (U4)0U;
    u4_t_rtry_cnt   = (U4)1U;
    do{

        u4_t_blo_idx     = u4_t_rec_idx * u4_t_rec_nblock;
        /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.               */
        /* The source of u4_t_num_rec is st_g_ODO_NVMIF_REC_ODO_KM.u1_num_rec, so the max value of u4_t_num_rec is 255.              */
        /* Therefor the max value u4_t_rec_idx is 255                                                                                */
        /* The source of u4_t_rec_nblock is st_g_ODO_NVMIF_REC_ODO_KM.u1_rec_nblock, so the max value of u4_t_rec_nblock is 255.     */
        /* The max value of (u4_t_rec_idx * u4_t_rec_nblock) is 255*255=65025, therefor it is not necessary to check the wraparound. */

        u4_t_blo_end     = u4_t_blo_idx + u4_t_rec_nblock;
        /* The max value of u4_t_blo_idx is 255*255 = 65025                                                                          */
        /* The source of u4_t_rec_nblock is st_g_ODO_NVMIF_REC_ODO_KM.u1_rec_nblock, so the max value of u4_t_rec_nblock is 255.     */
        /* The max value of (u4_t_blo_idx + u4_t_rec_nblock) is 65025+255=65280, therefor it is not necessary to check the wraparound.*/

        u2_t_rdbk_offset = (U2)0U;
        do{
            u1_t_rdrslt = u1_g_OdoNvmIfSyncBlock(u1_t_dev_idx,
                                                 u2_tp_BLOCK[u4_t_blo_idx],
                                                 &u1_tp_rdbk[u2_t_rdbk_offset],
                                                 u2_t_blo_nbyte);

            u2_t_rdbk_offset += u2_t_blo_nbyte;
            /* The source of u2_t_blo_nbyte is st_g_ODO_NVMIF_REC_ODO_KM.u1_blo_nbyte, so the max value of u2_t_blo_nbyte is 255.    */
            /* The number of times u2_t_blo_nbyte is accumulated is (u4_t_blo_end - u4_t_blo_idx) times.                             */
            /* u4_t_blo_end - u4_t_blo_idx = u4_t_blo_idx + u4_t_rec_nblock - u4_t_blo_idx = u4_t_rec_nblock.                        */
            /* The source of u4_t_rec_nblock is st_g_ODO_NVMIF_REC_ODO_KM.u1_rec_nblock, so the max value of u4_t_rec_nblock is 255. */
            /* In other words, 255(=u2_t_blo_nbyte) will be accumulated 255(= (u4_t_blo_end - u4_t_blo_idx)) times at the maximum,   */
            /* The maximum value of u2_t_rdbk_offset is 65025, therefor it is not necessary to check the wraparound.                 */

            if(u1_t_rdrslt == (U1)ODO_NVMIF_JOB_RESULT_OK){
                u4_t_blo_idx++;
                /* The value of u4_t_blo_idx is determined whether it is smaller than u4_t_blo_end within the while condition.       */
                /* The max value of u4_t_blo_end is 65280, , therefor it is not necessary to check the wraparound.                   */
            }
            else{
                u4_t_blo_idx = (U4)U4_MAX;
            }
        }
        while(u4_t_blo_idx < u4_t_blo_end);

        u1_t_unk = u1_g_OdoNvmIfKmUnk(&st_t_km_rdbk);
        if((u4_t_blo_idx == u4_t_blo_end) &&
           (u1_t_unk     == (U1)FALSE   )){

            vd_g_OdoNvmIfCbkTripKm((U1)TRUE, (U1)(u4_t_rec_begin >> 1U), &st_t_km_rdbk);

            u4_t_rec_begin += (U4)ODO_NVMIF_TRIP_NUM_REC;
            /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.           */
            /* The source of u4_t_num_rec is st_g_ODO_NVMIF_REC_ODO_KM.u1_num_rec, so the max value of u4_t_num_rec is 255.          */
            /* Therefor the max value u4_t_rec_idx is 255                                                                            */
            /* 2(=ODO_NVMIF_TRIP_NUM_REC) will be accumulated 255(= u4_t_rec_idx) times at the maximum,                              */
            /* The maximum value of u4_t_rec_begin is 510, therefor it is not necessary to check the wraparound.                     */
            u4_t_rec_idx    = u4_t_rec_begin;
            u4_t_rtry_cnt   = (U4)1U;
        }
        else if(u4_t_rec_idx == u4_t_rec_begin){
            u4_t_rec_idx++;
            /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.   */
            /* The source of u4_t_num_rec is st_g_ODO_NVMIF_REC_ODO_KM.u1_num_rec, so the max value of u4_t_num_rec is 255.  */
            /* Therefor it is not necessary to check the wraparound.                                                         */
        }
        else if(u4_t_rtry_cnt >= (U4)ODO_NVMIF_TRIP_SYN_RTRY_MAX){

            vd_g_OdoNvmIfCbkTripKm((U1)TRUE, (U1)(u4_t_rec_begin >> 1U), &st_s_ODO_NVMIF_TRIP_UNK);

            u4_t_rec_begin += (U4)ODO_NVMIF_TRIP_NUM_REC;
            /* The value of u4_t_rec_idx is determined whether it is smaller than u4_t_num_rec within the while condition.           */
            /* The source of u4_t_num_rec is st_g_ODO_NVMIF_REC_ODO_KM.u1_num_rec, so the max value of u4_t_num_rec is 255.          */
            /* Therefor the max value u4_t_rec_idx is 255                                                                            */
            /* 2(=ODO_NVMIF_TRIP_NUM_REC) will be accumulated 255(= u4_t_rec_idx) times at the maximum,                              */
            /* The maximum value of u4_t_rec_begin is 510, therefor it is not necessary to check the wraparound.                     */
            u4_t_rec_idx    = u4_t_rec_begin;
            u4_t_rtry_cnt   = (U4)1U;
        }
        else{
            u4_t_rec_idx    = u4_t_rec_begin;
            u4_t_rtry_cnt++;
            /* The value of u4_t_rtry_cnt is determined whether it is larger than ODO_NVMIF_ODO_RW_RTRY_MAX within the if condition. */
            /* Therefor it is not necessary to check the wraparound.                                                                 */
        }
    }
    while(u4_t_rec_idx < u4_t_num_rec);

    st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl = (U2)ODO_NVMIF_TRIP_RW_REQ_NEXT;

    u4_t_crc32 = u4_g_OdoNvmIfCrc32((U1 *)&st_s_odo_nvmif_trip_rw_ctrl,
                                    ((U4)sizeof(ST_ODO_NVMIF_RW_CTRL) - (U4)ODO_NVMIF_NBYTE_CRC_32));
    st_s_odo_nvmif_trip_rw_ctrl.u4_crc32 = u4_t_crc32;
}
/*===================================================================================================================================*/
/*  static U1      u1_s_OdoNvmIfTripAbortchk(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_OdoNvmIfTripAbortchk(void)
{
    ST_ODO_KM *             st_tp_km_last;

    U4                      u4_t_crc32;

    U2                      u2_t_rw_ctrl;

    U1                      u1_t_num_rec;
    U1                      u1_t_rec_nblock;
    U1                      u1_t_rec_idx;
    U1                      u1_t_rec_begin;
    U1                      u1_t_rec_end;
    U1                      u1_t_rec_bit;

    U1                      u1_t_blo_cnt;
    U1                      u1_t_unk;
    U1                      u1_t_sts_chk;

    u1_t_sts_chk = (U1)0x00U;

    u4_t_crc32 = u4_g_OdoNvmIfCrc32((U1 *)&st_s_odo_nvmif_trip_rw_ctrl,
                                    ((U4)sizeof(ST_ODO_NVMIF_RW_CTRL) - (U4)ODO_NVMIF_NBYTE_CRC_32));

    u1_t_num_rec    = st_g_ODO_NVMIF_REC_TRIP_KM.u1_num_rec;
    u1_t_rec_nblock = st_g_ODO_NVMIF_REC_TRIP_KM.u1_rec_nblock;

    u1_t_rec_idx    = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx;
    u1_t_rec_begin  = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk;
    u1_t_rec_end    = u1_t_rec_begin + (U1)ODO_NVMIF_TRIP_NUM_REC;
    u1_t_rec_bit    = u1_t_rec_begin & (U1)0x01U;

    u1_t_blo_cnt    = st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt;
    u2_t_rw_ctrl    = st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl;

    if((st_s_odo_nvmif_trip_rw_ctrl.u4_crc32 != u4_t_crc32                   ) ||
       (u2_t_rw_ctrl                         >= (U2)ODO_NVMIF_TRIP_RW_NUM_STS) ||
       (u1_t_rec_idx                         >= u1_t_num_rec                 ) ||
       (u1_t_rec_idx                         <  u1_t_rec_begin               ) ||
       (u1_t_rec_idx                         >= u1_t_rec_end                 ) ||
       (u1_t_rec_bit                         != (U1)0x00U                    ) ||
       (u1_t_blo_cnt                         >= u1_t_rec_nblock              )){

        u1_t_sts_chk = (U1)ODO_NVMIF_TRIP_CHK_SEQ_ABORT;
    }
    else if((u2_t_rw_ctrl == (U2)ODO_NVMIF_TRIP_RW_WRI_NEXT) ||
            (u2_t_rw_ctrl == (U2)ODO_NVMIF_TRIP_RW_CMP_NEXT)){

        st_tp_km_last = &st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_KM_LAST];
        u1_t_unk      = u1_g_OdoNvmIfKmUnk(st_tp_km_last);
        if(u1_t_unk != (U1)FALSE){

            u1_t_sts_chk = (U1)ODO_NVMIF_TRIP_CHK_SEQ_ABORT;
        }
    }
    else{
        /* do nothing */
    }

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_OdoNvmIfTripReqchk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_OdoNvmIfTripReqchk(void)
{
    ST_ODO_KM *             st_tp_km_last;
    ST_ODO_KM *             st_tp_km_next;

    U1                      u1_t_num_rec;
    U1                      u1_t_rec_begin;
    U1                      u1_t_rec_end;

    U1                      u1_t_fifo_out;
    U1                      u1_t_unk;

    U1                      u1_t_sts_chk;

    u1_t_fifo_out = u1_g_OdoNvmIfFifoPosOut(&st_s_odo_nvmif_trip_fifo_ctrl, (U1)ODO_NVMIF_TRIP_FIFO_MAX);
    if(u1_t_fifo_out >= (U1)ODO_NVMIF_TRIP_FIFO_MAX){
        u1_t_sts_chk = (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT;
    }
    else{

        u1_t_num_rec   = st_g_ODO_NVMIF_REC_TRIP_KM.u1_num_rec;
        u1_t_rec_begin = u1_sp_odo_nvmif_trip_fifo_ch[u1_t_fifo_out] << 1U;
        u1_t_rec_end   = u1_t_rec_begin + (U1)ODO_NVMIF_TRIP_NUM_REC;

        st_tp_km_last  = &st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_KM_LAST];
        st_tp_km_next  = &st_sp_odo_nvmif_trip_fifo_km[u1_t_fifo_out];
        u1_t_unk       = u1_g_OdoNvmIfKmUnk(st_tp_km_next);
        if((u1_t_rec_end <= u1_t_num_rec) &&
           (u1_t_unk     == (U1)FALSE   )){

            st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk = u1_t_rec_begin;

            st_tp_km_last->u4_ge_m  = st_tp_km_next->u4_ge_m;
            st_tp_km_last->u4_lt_m  = st_tp_km_next->u4_lt_m;
            st_tp_km_last->u4_crc32 = st_tp_km_next->u4_crc32;

            u1_sp_odo_nvmif_trip_fifo_ch[u1_t_fifo_out] = (U1)U1_MAX;

            st_tp_km_next->u4_ge_m  = (U4)ODO_KM_UNK;
            st_tp_km_next->u4_lt_m  = (U4)ODO_KM_UNK;
            st_tp_km_next->u4_crc32 = (U4)ODO_KM_UNK;

            u1_t_sts_chk = (U1)ODO_NVMIF_TRIP_CHK_REC_VALID;
        }
        else{
            u1_t_sts_chk = (U1)ODO_NVMIF_TRIP_CHK_REC_NEXT;
        }
    }

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_OdoNvmIfTripWrichk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_OdoNvmIfTripWrichk(void)
{
    U1                      u1_t_rec_nblock;
    U1                      u1_t_rec_idx;
    U1                      u1_t_rec_begin;
    U1                      u1_t_blo_next;

    U1                      u1_t_sts_chk;

    u1_t_rec_nblock = st_g_ODO_NVMIF_REC_TRIP_KM.u1_rec_nblock;

    u1_t_rec_idx    = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx;
    u1_t_rec_begin  = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk;
    u1_t_blo_next   = st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt + (U1)1U;

    if(u1_t_blo_next >= u1_t_rec_nblock){

        u1_t_blo_next = (U1)0U;

        if(u1_t_rec_idx == u1_t_rec_begin){
            if(u1_t_rec_idx < (U1)U1_MAX){
                u1_t_rec_idx++;
            }
            u1_t_sts_chk = (U1)ODO_NVMIF_TRIP_CHK_REC_NEXT;
        }
        else{
            u1_t_sts_chk = (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT;
        }
    }
    else{
        u1_t_sts_chk = (U1)0x00U;
    }

    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx  = u1_t_rec_idx;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt  = u1_t_blo_next;

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_OdoNvmIfTripCmpchk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_OdoNvmIfTripCmpchk(void)
{
    static const U1         u1_sp_ODO_NVMIF_TRIP_CMP_CHK[] = {
        /* st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt = 0 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_NEXT  | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 0 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_NEXT  | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 1 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_NEXT  | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 2 */

        /* st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt = 1 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_INVAL | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 0 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_INVAL | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 1 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_VALID | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 2 */

        /* st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt = 2 */
        (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT,                                      /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 0 */
        (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT,                                      /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 1 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_VALID | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 2 */

        /* st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt = 3 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_INVAL | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 0 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_INVAL | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 1 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_VALID | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 2 */

        /* st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt = 4 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_NEXT  | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 0 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_VALID | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT), /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 1 */
        ((U1)ODO_NVMIF_TRIP_CHK_REC_VALID | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT)  /* st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk = 2 */
    };

    ST_ODO_KM *             st_tp_km_last;
    ST_ODO_KM *             st_tp_km_rdbk;

    U2                      u2_t_rtry_cnt;
    U2                      u2_t_cmpr_chk;

    U1                      u1_t_rec_nblock;
    U1                      u1_t_rec_idx;
    U1                      u1_t_rec_begin;
    U1                      u1_t_rec_chk;
    U1                      u1_t_blo_next;
    U1                      u1_t_cmpr;
    U1                      u1_t_sts_chk;

    u1_t_sts_chk    = (U1)0x00U;

    u1_t_rec_nblock = st_g_ODO_NVMIF_REC_TRIP_KM.u1_rec_nblock;

    u1_t_rec_idx    = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx;
    u1_t_rec_begin  = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk;
    u1_t_rec_chk    = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk;
    u1_t_blo_next   = st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt + (U1)1U;
    u2_t_rtry_cnt   = st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt;

    if(u1_t_blo_next >= u1_t_rec_nblock){

        st_tp_km_last = &st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_KM_LAST];
        st_tp_km_rdbk = &st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_KM_RDBK];
        u1_t_cmpr     = u1_g_OdoNvmIfCmprAwB(st_tp_km_rdbk, st_tp_km_last);

        if((u1_t_rec_nblock == u1_s_odo_nvmif_trip_rdbk_cnt) &&
           (u1_t_cmpr       == (U1)ODO_KM_CMPR_A_EQ_B      )){
            if(u1_t_rec_chk < (U1)U1_MAX){
                u1_t_rec_chk++;
            }
        }

        if(u1_t_rec_idx == u1_t_rec_begin){
            if(u1_t_rec_idx < (U1)U1_MAX){
                u1_t_rec_idx++;
            }
        }
        else if((u1_t_rec_chk  > (U1)ODO_NVMIF_TRIP_NUM_REC    ) ||
                (u2_t_rtry_cnt > (U2)ODO_NVMIF_TRIP_RW_RTRY_MAX)){

            u1_t_sts_chk  = (U1)ODO_NVMIF_TRIP_CHK_REC_NEXT | (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT;
        }
        else{
            u2_t_cmpr_chk = (u2_t_rtry_cnt * (U2)ODO_NVMIF_TRIP_CMP_NUM_CHK) + (U2)u1_t_rec_chk;
            u1_t_sts_chk  = u1_sp_ODO_NVMIF_TRIP_CMP_CHK[u2_t_cmpr_chk];
            u2_t_rtry_cnt++;
            /* Since u2_t_rtry_cnt is determined whether it is larger than ODO_NVMIF_ODO_RW_RTRY_MAX within the if condition,   */
            /* it is not necessary to check the wraparound.                                                                     */
        }

        u1_t_blo_next                = (U1)0U;
        u1_s_odo_nvmif_trip_rdbk_cnt = (U1)0U;
    }

    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx  = u1_t_rec_idx;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk  = u1_t_rec_chk;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt  = u1_t_blo_next;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt = u2_t_rtry_cnt;

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripSynLast(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_OdoNvmIfTripSynchk(void)
{
    ST_ODO_KM *             st_tp_km_rdbk;

    U2                      u2_t_rtry_cnt;

    U1                      u1_t_num_rec;
    U1                      u1_t_rec_nblock;
    U1                      u1_t_rec_idx;
    U1                      u1_t_rec_begin;
    U1                      u1_t_blo_next;
    U1                      u1_t_unk;
    U1                      u1_t_sts_chk;

    u1_t_sts_chk    = (U1)0x00U;

    u1_t_num_rec    = st_g_ODO_NVMIF_REC_TRIP_KM.u1_num_rec;
    u1_t_rec_nblock = st_g_ODO_NVMIF_REC_TRIP_KM.u1_rec_nblock;

    u1_t_rec_idx    = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx;
    u1_t_rec_begin  = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk;
    u1_t_blo_next   = st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt + (U1)1U;
    u2_t_rtry_cnt   = st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt;

    if(u1_t_blo_next >= u1_t_rec_nblock){

        st_tp_km_rdbk = &st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_KM_RDBK];
        u1_t_unk      = u1_g_OdoNvmIfKmUnk(st_tp_km_rdbk);

        if((u1_t_rec_nblock == u1_s_odo_nvmif_trip_rdbk_cnt) &&
           (u1_t_unk        == (U1)FALSE                  )){

            vd_g_OdoNvmIfCbkTripKm((U1)FALSE, (U1)(u1_t_rec_begin >> 1U), st_tp_km_rdbk);

            if(((U1)U1_MAX - (U1)ODO_NVMIF_TRIP_NUM_REC) > u1_t_rec_begin){
                u1_t_rec_begin += (U1)ODO_NVMIF_TRIP_NUM_REC;
                /* No action is required because the IF statement immediately before is checked to see if wraparound is possible.    */
                /* Judged as over-detection                                                                                          */
            }
            else{
                u1_t_rec_begin = (U1)U1_MAX;
            }
            u1_t_rec_idx    = u1_t_rec_begin;
            u2_t_rtry_cnt   = (U2)1U;
        }
        else if(u1_t_rec_begin == u1_t_rec_idx){
            if(u1_t_rec_idx < (U1)U1_MAX){
                u1_t_rec_idx++;
            }
        }
        else if(u2_t_rtry_cnt >= (U2)ODO_NVMIF_TRIP_SYN_RTRY_MAX){

            vd_g_OdoNvmIfCbkTripKm((U1)FALSE, (U1)(u1_t_rec_begin >> 1U), &st_s_ODO_NVMIF_TRIP_UNK);

            if(((U1)U1_MAX - (U1)ODO_NVMIF_TRIP_NUM_REC) > u1_t_rec_begin){
                u1_t_rec_begin += (U1)ODO_NVMIF_TRIP_NUM_REC;
                /* No action is required because the IF statement immediately before is checked to see if wraparound is possible.    */
                /* Judged as over-detection                                                                                          */
            }
            else{
                u1_t_rec_begin = (U1)U1_MAX;
            }
            u1_t_rec_idx    = u1_t_rec_begin;
            u2_t_rtry_cnt   = (U2)1U;
        }
        else{
            u1_t_rec_idx    = u1_t_rec_begin;
            u2_t_rtry_cnt++;
            /* Since u2_t_rtry_cnt is determined whether it is larger than ODO_NVMIF_ODO_RW_RTRY_MAX within the if condition,   */
            /* it is not necessary to check the wraparound.                                                                     */
        }

        if(u1_t_rec_begin >= u1_t_num_rec){
            u1_t_sts_chk = (U1)ODO_NVMIF_TRIP_CHK_OPE_CMPLT;
        }

        u1_t_blo_next                = (U1)0U;
        u1_s_odo_nvmif_trip_rdbk_cnt = (U1)0U;
    }

    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx  = u1_t_rec_idx;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk  = u1_t_rec_begin;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt  = u1_t_blo_next;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt = u2_t_rtry_cnt;

    return(u1_t_sts_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActToSeqCmplt(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActToSeqCmplt(void)
{
    vd_g_OdoNvmIfTripRWDeAct();
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActToReqNext(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActToReqNext(void)
{
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl   = (U2)ODO_NVMIF_TRIP_RW_REQ_NEXT;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt  = (U2)1U;

    u1_s_odo_nvmif_trip_rdbk_cnt             = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActToCbkNext(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActToCbkNext(void)
{
    U1                      u1_t_ch;

    u1_t_ch = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk >> 1U;
    vd_g_OdoNvmIfCbkTripKm((U1)FALSE, u1_t_ch, &st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_KM_LAST]);

    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl   = (U2)ODO_NVMIF_TRIP_RW_REQ_NEXT;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt  = (U2)1U;

    u1_s_odo_nvmif_trip_rdbk_cnt             = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActToCbkUnk(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActToCbkUnk(void)
{
    U1                      u1_t_ch;

    u1_t_ch = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk >> 1U;
    vd_g_OdoNvmIfCbkTripKm((U1)FALSE, u1_t_ch, &st_s_ODO_NVMIF_TRIP_UNK);

    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl   = (U2)ODO_NVMIF_TRIP_RW_REQ_NEXT;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt  = (U2)1U;

    u1_s_odo_nvmif_trip_rdbk_cnt             = (U1)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActWriNext(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActWriNext(void)
{
    vd_g_OdoNvmIfWriKmBlock(&st_g_ODO_NVMIF_REC_TRIP_KM, &st_s_odo_nvmif_trip_rw_ctrl,
                            (U1 *)&st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_KM_LAST]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActToWriNext(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActToWriNext(void)
{
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx   = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk;

    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl   = (U2)ODO_NVMIF_TRIP_RW_WRI_NEXT;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt  = (U2)1U;

    u1_s_odo_nvmif_trip_rdbk_cnt             = (U1)0U;

    vd_g_OdoNvmIfWriKmBlock(&st_g_ODO_NVMIF_REC_TRIP_KM, &st_s_odo_nvmif_trip_rw_ctrl,
                            (U1 *)&st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_KM_LAST]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActToWriRtry(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActToWriRtry(void)
{
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx   = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk;

    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl   = (U2)ODO_NVMIF_TRIP_RW_WRI_NEXT;
 /* st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt  = (U2)1U; */

    u1_s_odo_nvmif_trip_rdbk_cnt             = (U1)0U;

    vd_g_OdoNvmIfWriKmBlock(&st_g_ODO_NVMIF_REC_TRIP_KM, &st_s_odo_nvmif_trip_rw_ctrl,
                            (U1 *)&st_sp_odo_nvmif_trip_rw_km[ODO_NVMIF_RW_KM_LAST]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActReaNext(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActReaNext(void)
{
    vd_g_OdoNvmIfReaKmBlock(&st_g_ODO_NVMIF_REC_TRIP_KM, &st_s_odo_nvmif_trip_rw_ctrl);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActToCmpNext(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActToCmpNext(void)
{
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx   = st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk;

    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl   = (U2)ODO_NVMIF_TRIP_RW_CMP_NEXT;
 /* st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt  = (U2)1U; */

    u1_s_odo_nvmif_trip_rdbk_cnt             = (U1)0U;

    vd_g_OdoNvmIfReaKmBlock(&st_g_ODO_NVMIF_REC_TRIP_KM, &st_s_odo_nvmif_trip_rw_ctrl);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActToSynLast(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActToSynLast(void)
{
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl   = (U2)ODO_NVMIF_TRIP_RW_SYN_LAST;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt  = (U2)1U;

    u1_s_odo_nvmif_trip_rdbk_cnt             = (U1)0U;

    vd_g_OdoNvmIfReaKmBlock(&st_g_ODO_NVMIF_REC_TRIP_KM, &st_s_odo_nvmif_trip_rw_ctrl);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmIfTripActToSynAbort(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmIfTripActToSynAbort(void)
{
    st_s_odo_nvmif_trip_fifo_ctrl.u2_len     = (U2)0U;
    st_s_odo_nvmif_trip_fifo_ctrl.u1_pos_in  = (U1)0U;
    st_s_odo_nvmif_trip_fifo_ctrl.u1_pos_out = (U1)0U;

    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_idx   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_mrk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_rec_chk   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u1_blo_cnt   = (U1)0U;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rw_ctrl   = (U2)ODO_NVMIF_TRIP_RW_SYN_LAST;
    st_s_odo_nvmif_trip_rw_ctrl.u2_rtry_cnt  = (U2)1U;

    u1_s_odo_nvmif_trip_rdbk_cnt             = (U1)0U;

    vd_g_OdoNvmIfReaKmBlock(&st_g_ODO_NVMIF_REC_TRIP_KM, &st_s_odo_nvmif_trip_rw_ctrl);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     9/18/2018  TN       New.                                                                                               */
/*  1.1.0     5/31/2019  TN       u1_g_OdoNvmIfTripRWRqst was optimized.                                                             */
/*  1.2.0    12/20/2019  TN       odo_nvmif_odo_km.c v1.1.0 -> v1.2.0.                                                               */
/*  1.2.1    05/14/2020  YN       No processing is specified in the last else statement.                                             */
/*  1.3.0     8/20/2020  TN       odo_km.c v1.2.0 -> v1.3.0.                                                                         */
/*  1.3.1    07/27/2020  YN       odo_km.c & odo_nvmif_odo_km.c v1.2.1 -> v1.3.1.                                                    */
/*  1.3.2    08/18/2020  YN       odo_nvmif_km.c v1.3.1 -> v1.3.2                                                                    */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * YN   = Yasuhiro Nakamura, Denso Techno                                                                                         */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
