/* 0.0.0 */
/*===================================================================================================================================*/
/*  Firmware Update Proxy (VM2 -> VM1)                                                                                               */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fwupx.h"

#include "ivdsh.h"

#include "memfill_u4.h"
#include "memfill_u1.h"
#include "memcpy_u1.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                u1_s_fwupx_req_seqcnt;
static U1                u1_sp_fwupx_reqdata[FWUPX_WRI_DATA_SIZE_MAX];
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_FwupxInit(void)
{
    vd_g_MemfillU1(&u1_sp_fwupx_reqdata[0], (U4)0U, (U4)FWUPX_WRI_DATA_SIZE_MAX);
    u1_s_fwupx_req_seqcnt = (U1)0U;
}

void            vd_g_FwupxMainTask(void)
{
    /* Ack monitoring to be implemented in later phase */
}

/*===================================================================================================================================*/
/*  void            u1_g_FwupxResData(U1 * u1_ap_resdata, U1 u1_a_len)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    サブフレーム1 Repro Data 解析 受信処理                                                                             */
/*  Arguments:      u1_ap_resdata : サブフレーム1 Repro Data開始位置                                                                   */
/*                  u1_a_len      : 有効データ長                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_FwupxResData(U1 * u1_ap_resdata, U1 u1_a_len)
{
    U4  u4_tp_data[FWUPX_READ_WORDS];
    U4  u4_tp_head[FWUPX_WRI_HEAD_WORDS];
    U1  u1_t_read_ok;
    U1  u1_t_ret;
    U1  u1_t_idx;
    U1  u1_t_pos;
    U1  u1_t_shift;
    U2  u2_t_run_offset;

    u1_t_ret = (U1)FALSE;
    u1_t_read_ok = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_FWUPXRES, &u4_tp_data[0], (U2)FWUPX_READ_WORDS);
    if(u1_t_read_ok != (U1)IVDSH_NO_REA){
        u1_t_ret = (U1)TRUE;
        for(u1_t_idx = (U1)0U; u1_t_idx < u1_a_len; u1_t_idx++) {
            u1_t_pos = (U1)(u1_t_idx / FWUPX_WORD_SIZE);
            u1_t_shift = (U1)(u1_t_idx % FWUPX_WORD_SIZE);
            u1_ap_resdata[u1_t_idx] = (U1)((u4_tp_data[u1_t_pos] >> (U4)(u1_t_shift * (U1)FWUPX_SHIFT_BIT)) & (U4)0xFFU);
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void            vd_g_FwupxPutReqData(const U1 * u1_ap_SUB4_ADD, const U2 u2_a_DTLEN)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    サブフレーム1/4 Repro Data 解析 送信処理                                                                           */
/*  Arguments:      u1_ap_SUB4_ADD : サブフレーム1/4 Repro Data開始位置                                                                */
/*                  u2_a_DTLEN     : 有効データ長                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_FwupxPutReqData(const U1 * u1_ap_SUB4_ADD, const U2 u2_a_DTLEN)
{
    U4          u4_tp_head[FWUPX_WRI_HEAD_WORDS];
    U4          u4_t_data_adr;
    U4          u4_t_loop;

    vd_g_MemfillU4(&u4_tp_head[0], (U4)0U, (U4)FWUPX_WRI_HEAD_WORDS);


    if (u1_s_fwupx_req_seqcnt < (U1)0xFFU) {
        u1_s_fwupx_req_seqcnt++;
    }
    else {
        u1_s_fwupx_req_seqcnt = (U1)0U;  /* Reset sequence count */
    }
    switch (u1_ap_SUB4_ADD[0]) {
        case (U1)FWUPX_SUBTYPE_REQ_PREP:
                /* Prepare request */
                u4_tp_head[0]  = (U4)u1_ap_SUB4_ADD[0];                 /* SubType */
                u4_tp_head[0] |= (U4)(u1_ap_SUB4_ADD[1] << (U4)8U);     /* logical block */
                u4_tp_head[0] |= (U4)(u1_ap_SUB4_ADD[2] << (U4)16U);    /* total logical block */
                u4_tp_head[1]  = (U4)(u1_s_fwupx_req_seqcnt << (U4)24U);    /* SEQ_CNT */

                for(u4_t_loop = (U4)0U; u4_t_loop < (U4)FWUPX_WRI_PREP_DATA_SIZE; u4_t_loop++) {
                    u1_sp_fwupx_reqdata[u4_t_loop] = (U4)u1_ap_SUB4_ADD[u4_t_loop + FWUPX_WRI_PREP_DATA_START];
                }
                u4_t_data_adr = (U4)&u1_sp_fwupx_reqdata[0];
                vd_g_iVDshWribyDid(IVDSH_DID_WRI_FWUPXREQ_H, &u4_tp_head[0], (U2)FWUPX_WRI_HEAD_WORDS);
                vd_g_iVDshWribyDid(IVDSH_DID_WRI_FWUPXREQ_D, &u4_t_data_adr, (U2)FWUPX_WRI_DATA_ADR_WORDS);
            break;
        case (U1)FWUPX_SUBTYPE_REQ_RUN:
                /* Run request */
                u4_tp_head[0]  = (U4)u1_ap_SUB4_ADD[0];                   /* SubType */
                u4_tp_head[0] |= (U4)(u1_ap_SUB4_ADD[1] << (U4)8U);       /* logical block */
                u4_tp_head[0] |= (U4)(u1_ap_SUB4_ADD[2] << (U4)24U);      /* block offset */
                u4_tp_head[1]  = (U4)(u1_ap_SUB4_ADD[3]);                 /* block offset */
                u4_tp_head[1] |= (U4)(u1_s_fwupx_req_seqcnt << (U4)24U);      /* SEQ_CNT */

                for(u4_t_loop = (U4)0U; u4_t_loop < (U4)FWUPX_WRI_RUN_DATA_SIZE; u4_t_loop++) {
                    u1_sp_fwupx_reqdata[u4_t_loop] = (U4)u1_ap_SUB4_ADD[u4_t_loop + FWUPX_WRI_RUN_DATA_START];
                }
                u4_t_data_adr = (U4)&u1_sp_fwupx_reqdata[0];
                vd_g_iVDshWribyDid(IVDSH_DID_WRI_FWUPXREQ_H, &u4_tp_head[0], (U2)FWUPX_WRI_HEAD_WORDS);
                vd_g_iVDshWribyDid(IVDSH_DID_WRI_FWUPXREQ_D, &u4_t_data_adr, (U2)FWUPX_WRI_DATA_ADR_WORDS);
            break;
        default:  /* FWUPX_SUBTYPE_REQ_VERI,FWUPX_SUBTYPE_REQ_PHASE,FWUPX_SUBTYPE_REQ_CANCEL */
                /* Verification request */
                u4_tp_head[0]  = (U4)u1_ap_SUB4_ADD[0];                   /* SubType */
                if (u2_a_DTLEN > (U1)1U) {
                    u4_tp_head[0] |= (U4)(u1_ap_SUB4_ADD[1] << (U4)8U);       /* logical block */
                }
                u4_tp_head[1]  = (U4)(u1_s_fwupx_req_seqcnt << (U4)24U);      /* SEQ_CNT */
                vd_g_iVDshWribyDid(IVDSH_DID_WRI_FWUPXREQ_H, &u4_tp_head[0], (U2)FWUPX_WRI_HEAD_WORDS);
            break;
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
/*  0.1.0    10/23/2025  GPT      Initial implementation.                                                                            */
/*  0.2.0    10/24/2025  GPT      Forward raw Type40 frame without CTRL/META segmentation.                                           */
/*  0.3.0    10/24/2025  GPT      Segment FWU frame into 64-word IVDsh partitions.                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
