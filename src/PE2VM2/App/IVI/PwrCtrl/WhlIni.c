/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "WhlIni.h"

#include "ivdsh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define WHLINI_SEQ_IDLE                 (0U)
#define WHLINI_SEQ_CLEAR_START          (1U)
#define WHLINI_SEQ_CLEAR_COMPLETE       (2U)
#define WHLINI_SEQ_REQUEST_START        (3U)
#define WHLINI_SEQ_REQUEST_END          (4U)
#define WHLINI_SEQ_SEND_START           (5U)
#define WHLINI_SEQ_SEND_END             (6U)
#define WHLINI_SEQ_WAIT_START_REJECT    (7U)
#define WHLINI_SEQ_WAIT_END_REJECT      (8U)
#define WHLINI_SEQ_SEND_VM1_WRITE1_REQ  (9U)
#define WHLINI_SEQ_WAIT_VM1_WRITE1_RES  (10U)
#define WHLINI_SEQ_SEND_VM1_WRITE0_REQ  (11U)
#define WHLINI_SEQ_WAIT_VM1_WRITE0_RES  (12U)

#define WHLINI_MASK_BYTE                (0xFFU)
#define WHLINI_SHIFT_1BYTE              (8U)
#define WHLINI_SHIFT_2BYTE              (16U)

#define WHLINI_VMCOM_WORD_1             (1U)

#define WHLINI_OSCMD_REQ_NONE           (0U)
/* FIFOサイズ */
#define WHLINI_SOCREQ_FIFO_SIZE         (8U)

#define WHLINI_REQSTS_NOT_STARTED       (0U)
#define WHLINI_REQSTS_STARTED           (1U)
#define WHLINI_REQSTS_ENDED             (2U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_whlini_state;                                /* WHLINI Sequence State */
static U1 u1_s_whlini_req;                                  /* WHLINI Wholly Initialization Request */
static U4 u4_s_vmcom_req_vm3;                               /* VM2->VM3 WHLINI info/request word (contains REQ/CMP fields) */
static U4 u4_s_whlini_req;                                  /* （provisional）WHLINI Request */
#if 0  /* （provisional）VM1未対応のため無効化 */
static U4 u4_s_vmcom_req_vm1;                               /* VM2->VM1 WHLINI request word (WRITE1/WRITE0/NON) */
#endif

/* FIFO本体（START/END の要求コードをそのまま格納） */
static U1 u1_s_socreq_fifo[WHLINI_SOCREQ_FIFO_SIZE];
static U1 u1_s_socreq_fifo_head; /* 次にpopする位置 */
static U1 u1_s_socreq_fifo_tail; /* 次にpushする位置 */
static U1 u1_s_socreq_fifo_num ; /* 格納件数 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_Whlini_SoCReq_Fifo_Push(U1 u1_a_req);
static U1 u1_s_Whlini_SocReq_Fifo_Pop(U1 *u1_ap_req);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*  void    vd_g_WhlIni_Init(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_WhlIni_Init(void)
{
    U1 u1_t_cnt;

    u1_s_whlini_state = (U1)WHLINI_SEQ_IDLE;
    u1_s_whlini_req = (U1)WHLINI_REQSTS_NOT_STARTED;

    u1_s_socreq_fifo_head = (U1)0U;
    u1_s_socreq_fifo_tail = (U1)0U;
    u1_s_socreq_fifo_num  = (U1)0U;

    for (u1_t_cnt = 0U; u1_t_cnt < (U1)WHLINI_SOCREQ_FIFO_SIZE; u1_t_cnt++) {
        u1_s_socreq_fifo[u1_t_cnt] = (U1)0U;
    }

    /* （provisional）WHLINI Request */
    u4_s_whlini_req = (U4)FALSE;

    u4_s_vmcom_req_vm3 = (U4)0U;
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_WHLINI_INF, &u4_s_vmcom_req_vm3, (U2)WHLINI_VMCOM_WORD_1);
#if 0  /* （provisional）VM1未対応のため無効化 */
    u4_s_vmcom_req_vm1 = (U4)0U;
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_WHLINI_REQ, &u4_s_vmcom_req_vm1, (U2)WHLINI_VMCOM_WORD_1);
#endif
}

/*===================================================================================================================================*/
/*  void    vd_g_WhlIni_Routine(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_WhlIni_Routine(void)
{
    U1  u1_t_vmcom_sts;
    U4  u4_t_vmcom_rcv_sts_vm3;
#if 0  /* （provisional）VM1未対応のため無効化 */
    U4  u4_t_vmcom_rcv_sts_vm1;
#endif
    U1  u1_t_vmcom_rcv_sts;
    U1  u1_t_socreq;

    switch(u1_s_whlini_state){
        case WHLINI_SEQ_IDLE:
            /* Pop SoC requests until an executable one arrives; reply no-op ACCEPT for non-executable requests. */
            while (u1_s_Whlini_SocReq_Fifo_Pop(&u1_t_socreq) == (U1)TRUE){
                if (u1_t_socreq == (U1)WHLINI_OSCMD_REQ_START){
                    /* START request: execute if not STARTED, otherwise reply no-op ACCEPT. */
                    if (u1_s_whlini_req == (U1)WHLINI_REQSTS_STARTED){
                        /* Already started: reply ACCEPT only (no operation). */
                        u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_START,(U1)WHLINI_OSCMD_RES_ACCEPT);
                    }
                    else{
                        /* Not started or already ended: start START sequence. */
                        u1_s_whlini_state = (U1)WHLINI_SEQ_SEND_START;
                        break;
                    }
                }
                else if (u1_t_socreq == (U1)WHLINI_OSCMD_REQ_END){
                    /* END request: execute if not ENDED, otherwise reply no-op ACCEPT. */
                    if (u1_s_whlini_req == (U1)WHLINI_REQSTS_ENDED){
                        /* Already ended: reply ACCEPT only (no operation). */
                        u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_END,(U1)WHLINI_OSCMD_RES_ACCEPT);
                    }
                    else{
                        /* Not ended: start END sequence. */
                        u1_s_whlini_state = (U1)WHLINI_SEQ_SEND_END;
                        break;
                    }
                }
                else{
                    /* Nothing */
                }
            }
            break;
        case WHLINI_SEQ_CLEAR_START:
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO2_WHLINI_INF, &u4_t_vmcom_rcv_sts_vm3, (U2)WHLINI_VMCOM_WORD_1);
            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                u1_t_vmcom_rcv_sts = (U1)((u4_t_vmcom_rcv_sts_vm3 >> WHLINI_SHIFT_1BYTE) & (U4)WHLINI_MASK_BYTE);
                if(u1_t_vmcom_rcv_sts == (U1)WHLINI_VMCOM_FROMVM3_STA_START){
                    /* （provisional）Initialize all RIM and DTF */

                    /* VM communication: Set Wholly Initialization completion status to SUCCESS */
                    u4_s_vmcom_req_vm3 &= ~((U4)WHLINI_MASK_BYTE << WHLINI_SHIFT_1BYTE);
                    u4_s_vmcom_req_vm3 |=  ((U4)WHLINI_VMCOM_TOVM3_CMP_SUCCESS << WHLINI_SHIFT_1BYTE);
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_WHLINI_INF, &u4_s_vmcom_req_vm3, (U2)WHLINI_VMCOM_WORD_1);
                    u1_s_whlini_state = (U1)WHLINI_SEQ_CLEAR_COMPLETE;

                    /* （provisional）Initialization failure */
                }
            }
            break;
        case WHLINI_SEQ_CLEAR_COMPLETE:
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO2_WHLINI_INF, &u4_t_vmcom_rcv_sts_vm3, (U2)WHLINI_VMCOM_WORD_1);

            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                u1_t_vmcom_rcv_sts = (U1)((u4_t_vmcom_rcv_sts_vm3 >> WHLINI_SHIFT_1BYTE) & (U4)WHLINI_MASK_BYTE);
                if(u1_t_vmcom_rcv_sts == (U1)WHLINI_VMCOM_FROMVM3_STA_NON){
                    /* VM Communication : Clear Wholly Initialization completion status */
                    u4_s_vmcom_req_vm3 &= ~((U4)WHLINI_MASK_BYTE << WHLINI_SHIFT_1BYTE);
                    u4_s_vmcom_req_vm3 |=  ((U4)WHLINI_VMCOM_TOVM3_CMP_NON  << WHLINI_SHIFT_1BYTE);
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_WHLINI_INF, &u4_s_vmcom_req_vm3, (U2)WHLINI_VMCOM_WORD_1);
                    u1_s_whlini_state = (U1)WHLINI_SEQ_IDLE;
                }
            }
            break;
        case WHLINI_SEQ_REQUEST_START:
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO2_WHLINI_INF, &u4_t_vmcom_rcv_sts_vm3, (U2)WHLINI_VMCOM_WORD_1);

            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                u1_t_vmcom_rcv_sts = (U1)(u4_t_vmcom_rcv_sts_vm3 & (U4)WHLINI_MASK_BYTE);
                if(u1_t_vmcom_rcv_sts == (U1)WHLINI_VMCOM_FROMVM3_RES_START_ACCEPT){
                    /* （provisional）Store the Wholly Initialization request in RAM */
                    u4_s_whlini_req = (U4)TRUE;

                    /* VM Communication : Clear REQ command field */
                    u4_s_vmcom_req_vm3 &= ~((U4)WHLINI_MASK_BYTE);
                    u4_s_vmcom_req_vm3 |= (U4)WHLINI_VMCOM_TOVM3_REQ_NON;
                    /* （provisional）VM Communication : Update request-notification flag from RAM state */
                    u4_s_vmcom_req_vm3 &= ~((U4)WHLINI_MASK_BYTE << WHLINI_SHIFT_2BYTE);
                    u4_s_vmcom_req_vm3 |=  u4_s_whlini_req << WHLINI_SHIFT_2BYTE;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_WHLINI_INF, &u4_s_vmcom_req_vm3, (U2)WHLINI_VMCOM_WORD_1);

#if 0  /* （provisional）VM1未対応のため無効化 */
                    u1_s_whlini_state = (U1)WHLINI_SEQ_SEND_VM1_WRITE1_REQ;
#else
                    /* OS Command : Wholly Initialization Response */
                    u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_START,(U1)WHLINI_OSCMD_RES_ACCEPT);
                    u1_s_whlini_req = (U1)WHLINI_REQSTS_STARTED;
                    u1_s_whlini_state = (U1)WHLINI_SEQ_CLEAR_START;
#endif
                }
                else if(u1_t_vmcom_rcv_sts == (U1)WHLINI_VMCOM_FROMVM3_RES_START_REJECT){
                    /* VM Communication : Clear REQ command field */
                    u4_s_vmcom_req_vm3 &= ~((U4)WHLINI_MASK_BYTE);
                    u4_s_vmcom_req_vm3 |= (U4)WHLINI_VMCOM_TOVM3_REQ_NON;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_WHLINI_INF, &u4_s_vmcom_req_vm3, (U2)WHLINI_VMCOM_WORD_1);

                    /* OS Command : Wholly Initialization Response */
                    u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_START, (U1)WHLINI_OSCMD_RES_REJECT);
                    u1_s_whlini_state = (U1)WHLINI_SEQ_WAIT_START_REJECT;
                }
                else{
                    /* Nothing */
                }
            }
            break;
        case WHLINI_SEQ_REQUEST_END:
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO2_WHLINI_INF, &u4_t_vmcom_rcv_sts_vm3, (U2)WHLINI_VMCOM_WORD_1);

            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                u1_t_vmcom_rcv_sts = (U1)(u4_t_vmcom_rcv_sts_vm3 & (U4)WHLINI_MASK_BYTE);
                if(u1_t_vmcom_rcv_sts == (U1)WHLINI_VMCOM_FROMVM3_RES_END_ACCEPT){
                    /* （provisional）Delete the Wholly Initialization request from RAM */
                    u4_s_whlini_req = (U4)FALSE;

                    /* VM Communication : Clear REQ command field */
                    u4_s_vmcom_req_vm3 &= ~((U4)WHLINI_MASK_BYTE);
                    u4_s_vmcom_req_vm3 |= (U4)WHLINI_VMCOM_TOVM3_REQ_NON;
                    /* （provisional）VM Communication : Update request-notification flag from RAM state */
                    u4_s_vmcom_req_vm3 &= ~((U4)WHLINI_MASK_BYTE << WHLINI_SHIFT_2BYTE);
                    u4_s_vmcom_req_vm3 |=  u4_s_whlini_req << WHLINI_SHIFT_2BYTE;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_WHLINI_INF, &u4_s_vmcom_req_vm3, (U2)WHLINI_VMCOM_WORD_1);

#if 0  /* （provisional）VM1未対応のため無効化 */
                    u1_s_whlini_state = (U1)WHLINI_SEQ_SEND_VM1_WRITE0_REQ;
#else
                    /* OS Command : Wholly Initialization Response */
                    u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_END,(U1)WHLINI_OSCMD_RES_ACCEPT);
                    u1_s_whlini_req = (U1)WHLINI_REQSTS_ENDED;
                    u1_s_whlini_state = (U1)WHLINI_SEQ_IDLE;
#endif
                }
                else if(u1_t_vmcom_rcv_sts == (U1)WHLINI_VMCOM_FROMVM3_RES_END_REJECT){
                    /* VM Communication : Clear REQ command field */
                    u4_s_vmcom_req_vm3 &= ~((U4)WHLINI_MASK_BYTE);
                    u4_s_vmcom_req_vm3 |= (U4)WHLINI_VMCOM_TOVM3_REQ_NON;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_WHLINI_INF, &u4_s_vmcom_req_vm3, (U2)WHLINI_VMCOM_WORD_1);

                    /* OS Command : Wholly Initialization Response */
                    u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_END, (U1)WHLINI_OSCMD_RES_REJECT);
                    u1_s_whlini_state = (U1)WHLINI_SEQ_WAIT_END_REJECT;
                }
                else{
                    /* Nothing */
                }
            }
            break;
        case WHLINI_SEQ_SEND_START:
            u4_s_vmcom_req_vm3 &= ~((U4)WHLINI_MASK_BYTE);
            u4_s_vmcom_req_vm3 |= (U4)WHLINI_VMCOM_TOVM3_REQ_START;
            vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_WHLINI_INF, &u4_s_vmcom_req_vm3, (U2)WHLINI_VMCOM_WORD_1);
            u1_s_whlini_state = (U1)WHLINI_SEQ_REQUEST_START;
            break;
        case WHLINI_SEQ_SEND_END:
            u4_s_vmcom_req_vm3 &= ~((U4)WHLINI_MASK_BYTE);
            u4_s_vmcom_req_vm3 |= (U4)WHLINI_VMCOM_TOVM3_REQ_END;
            vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_WHLINI_INF, &u4_s_vmcom_req_vm3, (U2)WHLINI_VMCOM_WORD_1);
            u1_s_whlini_state = (U1)WHLINI_SEQ_REQUEST_END;
            break;
        case WHLINI_SEQ_WAIT_START_REJECT:
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO2_WHLINI_INF,&u4_t_vmcom_rcv_sts_vm3,(U2)WHLINI_VMCOM_WORD_1);

            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                /* No request */
                u1_t_vmcom_rcv_sts = (U1)(u4_t_vmcom_rcv_sts_vm3 & (U4)WHLINI_MASK_BYTE);
                if(u1_t_vmcom_rcv_sts == (U1)WHLINI_VMCOM_FROMVM3_RES_NON){
                    u1_s_whlini_state = (U1)WHLINI_SEQ_IDLE;
                }
            }
            break;
        case WHLINI_SEQ_WAIT_END_REJECT:
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO2_WHLINI_INF,&u4_t_vmcom_rcv_sts_vm3,(U2)WHLINI_VMCOM_WORD_1);

            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                /* No request */
                u1_t_vmcom_rcv_sts = (U1)(u4_t_vmcom_rcv_sts_vm3 & (U4)WHLINI_MASK_BYTE);
                if(u1_t_vmcom_rcv_sts == (U1)WHLINI_VMCOM_FROMVM3_RES_NON){
                    u1_s_whlini_state = (U1)WHLINI_SEQ_IDLE;
                }
            }
            break;
#if 0  /* （provisional）VM1未対応のため無効化 */
        case WHLINI_SEQ_SEND_VM1_WRITE1_REQ:
            /* VM Communication : Write 1 */
            u4_s_vmcom_req_vm1 = (U4)WHLINI_VMCOM_TOVM1_REQ_WRITE1;
            vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_WHLINI_REQ,&u4_s_vmcom_req_vm1,(U2)WHLINI_VMCOM_WORD_1);

            u1_s_whlini_state = (U1)WHLINI_SEQ_WAIT_VM1_WRITE1_RES;
            break;
        case WHLINI_SEQ_WAIT_VM1_WRITE1_RES:
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM1TO2_WHLINI_RES,&u4_t_vmcom_rcv_sts_vm1,(U2)WHLINI_VMCOM_WORD_1);

            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                if(u4_t_vmcom_rcv_sts_vm1 == (U4)WHLINI_VMCOM_FROMVM1_RES_WRITE_FAIL){
                    /* OS Command : Wholly Initialization Response */
                    u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_START,(U1)WHLINI_OSCMD_RES_REJECT);
                    /* VM Communication : Write NON */
                    u4_s_vmcom_req_vm1 = (U4)WHLINI_VMCOM_TOVM1_REQ_NON;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_WHLINI_REQ,&u4_s_vmcom_req_vm1,(U2)WHLINI_VMCOM_WORD_1);

                    u1_s_whlini_state = (U1)WHLINI_SEQ_IDLE;
                }
                else if(u4_t_vmcom_rcv_sts_vm1 == (U4)WHLINI_VMCOM_FROMVM1_RES_WRITE_SUCCESS){
                    /* OS Command : Wholly Initialization Response */
                    u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_START,(U1)WHLINI_OSCMD_RES_ACCEPT);
                    /* VM Communication : Write NON */
                    u4_s_vmcom_req_vm1 = (U4)WHLINI_VMCOM_TOVM1_REQ_NON;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_WHLINI_REQ,&u4_s_vmcom_req_vm1,(U2)WHLINI_VMCOM_WORD_1);

                    u1_s_whlini_req = (U1)WHLINI_REQSTS_STARTED;
                    u1_s_whlini_state = (U1)WHLINI_SEQ_CLEAR_START;
                }
                else{
                    /* Nothing */
                }
            }
            break;
        case WHLINI_SEQ_SEND_VM1_WRITE0_REQ:
            /* VM Communication : Write 0 */
            u4_s_vmcom_req_vm1 = (U4)WHLINI_VMCOM_TOVM1_REQ_WRITE0;
            vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_WHLINI_REQ,&u4_s_vmcom_req_vm1,(U2)WHLINI_VMCOM_WORD_1);

            u1_s_whlini_state = (U1)WHLINI_SEQ_WAIT_VM1_WRITE0_RES;
            break;
        case WHLINI_SEQ_WAIT_VM1_WRITE0_RES:
            u1_t_vmcom_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM1TO2_WHLINI_RES,&u4_t_vmcom_rcv_sts_vm1,(U2)WHLINI_VMCOM_WORD_1);

            if(u1_t_vmcom_sts != (U1)IVDSH_NO_REA){
                if(u4_t_vmcom_rcv_sts_vm1 == (U4)WHLINI_VMCOM_FROMVM1_RES_WRITE_FAIL){
                    /* OS Command : Wholly Initialization Response */
                    u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_END,(U1)WHLINI_OSCMD_RES_REJECT);
                    /* VM Communication : Write NON */
                    u4_s_vmcom_req_vm1 = (U4)WHLINI_VMCOM_TOVM1_REQ_NON;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_WHLINI_REQ,&u4_s_vmcom_req_vm1,(U2)WHLINI_VMCOM_WORD_1);

                    u1_s_whlini_state = (U1)WHLINI_SEQ_IDLE;
                }
                else if(u4_t_vmcom_rcv_sts_vm1 == (U4)WHLINI_VMCOM_FROMVM1_RES_WRITE_SUCCESS){
                    /* OS Command : Wholly Initialization Response */
                    u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_END,(U1)WHLINI_OSCMD_RES_ACCEPT);
                    /* VM Communication : Write NON */
                    u4_s_vmcom_req_vm1 = (U4)WHLINI_VMCOM_TOVM1_REQ_NON;
                    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_WHLINI_REQ,&u4_s_vmcom_req_vm1,(U2)WHLINI_VMCOM_WORD_1);

                    u1_s_whlini_req = (U1)WHLINI_REQSTS_ENDED;
                    u1_s_whlini_state = (U1)WHLINI_SEQ_IDLE;
                }
                else{
                    /* Nothing */
                }
            }
            break;
#endif
        default:
            vd_g_WhlIni_Init();
            break;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_WhlIni_SoCReq(U1 u1_a_socreq)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_WhlIni_SoCReq(U1 u1_a_socreq)
{
    if((u1_a_socreq == (U1)WHLINI_OSCMD_REQ_START)
    || (u1_a_socreq == (U1)WHLINI_OSCMD_REQ_END)){
        if (u1_s_Whlini_SoCReq_Fifo_Push(u1_a_socreq) == (U1)FALSE) {
            /* fail */
            if (u1_a_socreq == (U1)WHLINI_OSCMD_REQ_START) {
                u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_START,(U1)WHLINI_OSCMD_RES_REJECT);
            }
            else {
                u1_WHLINI_OSCMD_SOC_RES((U1)WHLINI_OSCMD_RES_KIND_END,(U1)WHLINI_OSCMD_RES_REJECT);
            }
        }
    }
}

/*===================================================================================================================================*/
/*  void    u1_s_Whlini_SoCReq_Fifo_Push(U1 u1_a_req)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Whlini_SoCReq_Fifo_Push(U1 u1_a_req)
{
    U1 u1_t_return;

    u1_t_return = (U1)TRUE;

    if (u1_s_socreq_fifo_num >= (U1)WHLINI_SOCREQ_FIFO_SIZE) {
        u1_t_return = (U1)FALSE; /* overflow */
    }
    else{
        u1_s_socreq_fifo[u1_s_socreq_fifo_tail] = u1_a_req;
        if (u1_s_socreq_fifo_tail >= (U1)WHLINI_SOCREQ_FIFO_SIZE) {
            u1_s_socreq_fifo_tail = (U1)0U;
        }
        else{
            u1_s_socreq_fifo_tail = u1_s_socreq_fifo_tail + (U1)1U;
        }
        u1_s_socreq_fifo_num = u1_s_socreq_fifo_num + (U1)1U;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  void    u1_s_Whlini_SocReq_Fifo_Pop(U1 *u1_ap_req)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Whlini_SocReq_Fifo_Pop(U1 *u1_ap_req)
{
    U1 u1_t_return;

    u1_t_return = (U1)TRUE;

    if ((u1_s_socreq_fifo_num == (U1)0U)
    || (u1_ap_req == vdp_PTR_NA)){
        u1_t_return = (U1)FALSE; /* empty */
    }
    else{
        *u1_ap_req = u1_s_socreq_fifo[u1_s_socreq_fifo_head];
        if (u1_s_socreq_fifo_head >= (U1)WHLINI_SOCREQ_FIFO_SIZE) {
            u1_s_socreq_fifo_head = (U1)0U;
        }
        else{
            u1_s_socreq_fifo_head = u1_s_socreq_fifo_head + (U1)1U;
        }

        u1_s_socreq_fifo_num--;
    }
    return(u1_t_return);
}
