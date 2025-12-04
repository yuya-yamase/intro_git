/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  IVI DiagApp_SID22 Function                                                                                                      */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIAGAPP_SID22_C_MAJOR          (0)
#define DIAGAPP_SID22_C_MINOR          (0)
#define DIAGAPP_SID22_C_PATCH          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include       "DiagApp_private.h"
#include       "DiagApp_SID22.h"
#include       "x_spi_ivi_sub0_SID22.h"
#include       "Dcm.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DIAGAPP_SID22_C_MAJOR != DIAGAPP_SID22_H_MAJOR) || \
     (DIAGAPP_SID22_C_MINOR != DIAGAPP_SID22_H_MINOR) || \
     (DIAGAPP_SID22_C_PATCH != DIAGAPP_SID22_H_PATCH))
#error "DiagApp_SID22.c and DiagApp_SID22.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIAGAPP_SID22_MIN_REQ_SIZE      (2U)

#define DIAGAPP_SID22_DID_MAXNUM_PHY    (6U)
#define DIAGAPP_SID22_DID_MAXNUM_FUNC   (3U)

#define DIAGAPP_SID22_FORMAT_CHK        (1U)

#define DIAGAPP_SID22_POSRES            (0U)
#define DIAGAPP_SID22_DID_SIZE          (2U)

#define DIAGAPP_SID22_SUPPORT_DID_0101  (0x0101U)
#define DIAGAPP_SID22_SUPPORT_DID_0121  (0x0121U)
#define DIAGAPP_SID22_SUPPORT_DID_A001  (0xA001U)
#define DIAGAPP_SID22_SUPPORT_DID_F1A0  (0xF1A0U)
#define DIAGAPP_SID22_SUPPORT_DID_1010  (0x1010U)
#define DIAGAPP_SID22_SUPPORT_DID_10F2  (0x10F2U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_OXDC_ANS st_s_diagapp_sid22_ans;
static U1   u1_s_diagapp_nrc;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_DiagAppInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    Initial Function                                                                                                 */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppSID22Init(void)
{
    u1_s_diagapp_nrc = (U1)DIAGAPP_NRC_INIT;
}

/*===================================================================================================================================*/
/*  void            vd_g_DiagAppSID22Request(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$22 Request Recieve                                                                                           */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void           vd_g_DiagAppSID22Request(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    U1 u1_t_datanum;            /* Data Num        */
    U1 u1_t_NRC;                /* NRC             */
    U1 u1_t_requestId;          /* RequetID        */
    U1 u1_t_maxnum;             /* Data Max Num    */
    U1 u1_t_result;
    U2 u2_tp_did[DIAGAPP_SID22_DID_MAXNUM_PHY];
    U4 u4_t_lpcnt;
    U1 u1_t_did_bufpos;
    U1 u1_t_did_supnum;
    U2 u2_t_chk_did;

    /* Data Length */
    u1_t_datanum = (U1)(st_ap_REQ->u4_nbyte / (U4)2U);
    u1_t_NRC = (U1)0U;

    if (st_ap_REQ->u2_tim_elpsd == (U2)0U) {
        /* Get Request ID */
#warning "BEVCDCFD-2209"
#if 0 /* BEVCDCFD-2209 */
        u1_t_requestId = u1_g_DiagAppConvPduIdToRequestId(st_ap_REQ->u1_req_type);
#else /* BEVCDCFD-2209 */
        u1_t_requestId = u1_g_DiagAppConvPduIdToRequestId(st_ap_REQ->u1_pdu_rx);
#endif /* BEVCDCFD-2209 */
        if(u1_t_requestId == (U1)DIAGAPP_REQUESTID_FUNCOFF) {
            vd_g_DiagAppAnsTxNRC((U1)DIAGAPP_NRC_NONSUP);
            return;
        }
        st_s_diagapp_sid22_ans.u1p_tx = st_ap_ans->u1p_tx;
        st_s_diagapp_sid22_ans.u4_nbyte = st_ap_ans->u4_nbyte;
        /* Under Minimum Request Data */
        if(st_ap_REQ->u4_nbyte < (U4)DIAGAPP_SID22_MIN_REQ_SIZE) {
            /* NRC:0x13 */
            vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_13);
            return;
        }

        /*Format check*/
        if((st_ap_REQ->u4_nbyte & (U4)DIAGAPP_SID22_FORMAT_CHK) == (U4)DIAGAPP_SID22_FORMAT_CHK){
            /* NRC:0x13 */
            vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_13);
            return;
        }

        /* Over Number of DID */
        if((u1_t_requestId == (U1)DIAGAPP_REQUESTID_PHYOFF) ||
           (u1_t_requestId == (U1)DIAGAPP_REQUESTID_PHYON)) {
            u1_t_maxnum = (U1)DIAGAPP_SID22_DID_MAXNUM_PHY;
        } else {
            u1_t_maxnum = (U1)DIAGAPP_SID22_DID_MAXNUM_FUNC;
        }

        if(u1_t_datanum > u1_t_maxnum) {
            /* NRC:0x13 */
            vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_13);
            return;
        } else {
            
        }

        u1_t_did_supnum = (U1)0U;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u1_t_datanum; u4_t_lpcnt++) {
            u1_t_did_bufpos = (U1)(u4_t_lpcnt * (U4)2U);
            u2_t_chk_did = (U2)((st_ap_REQ->u1p_RX[u1_t_did_bufpos] << DIAGAPP_SFT_08) | st_ap_REQ->u1p_RX[u1_t_did_bufpos + 1U]);
            switch(u1_t_requestId) {
                case DIAGAPP_REQUESTID_PHYOFF:
                    u2_tp_did[u1_t_did_supnum] = u2_t_chk_did;
                    u1_t_did_supnum++;
                    break;
                case DIAGAPP_REQUESTID_PHYON:
                case DIAGAPP_REQUESTID_FUNCON:
                    if(((u2_t_chk_did >= (U2)DIAGAPP_SID22_SUPPORT_DID_0101) && (u2_t_chk_did <= (U2)DIAGAPP_SID22_SUPPORT_DID_0121)) ||
                       ((u2_t_chk_did >= (U2)DIAGAPP_SID22_SUPPORT_DID_A001) && (u2_t_chk_did <= (U2)DIAGAPP_SID22_SUPPORT_DID_F1A0)) ||
                       ((u2_t_chk_did >= (U2)DIAGAPP_SID22_SUPPORT_DID_1010) && (u2_t_chk_did <= (U2)DIAGAPP_SID22_SUPPORT_DID_10F2))) {
                        u2_tp_did[u1_t_did_supnum] = u2_t_chk_did;
                        u1_t_did_supnum++;
                    }
                    break;
                default:
                    vd_g_DiagAppAnsTxNRC((U1)DIAGAPP_NRC_NONSUP);
                    return;
            }
        }

        if(u1_t_did_supnum != (U1)0U) {
            u1_t_result = u1_g_XspiIviSub0Request_Sid22(u1_t_requestId, u1_t_did_supnum, &u2_tp_did[0], &u1_t_NRC);
        } else {
            vd_g_DiagAppAnsTxNRC(OXDC_SAL_PROC_NR_31);
            return;
        }

        if (u1_t_result == (U1)E_NOT_OK) {
            /* NRC */
            vd_g_DiagAppAnsTxNRC(u1_t_NRC);
        }
        else {
            /* E_OK : Do Nothing */
        }
    } else {
        if(u1_s_diagapp_nrc == (U1)DIAGAPP_NRC_POSRES) {
            vd_g_DiagAppAnsTx(&st_s_diagapp_sid22_ans);
        } else if(u1_s_diagapp_nrc != (U1)DIAGAPP_NRC_INIT) {
            vd_g_DiagAppAnsTxNRC(u1_s_diagapp_nrc);
        } else {
            /*Do Nothing*/
        }
        u1_s_diagapp_nrc = (U1)DIAGAPP_NRC_INIT;
    }
}

/*===================================================================================================================================*/
/*  void           vd_g_DiagAppResponse_Sid22(const U1 u1_a_NUM, const ST_DIAG_DID * st_ap_DID, const U1 * u1_ap_NRC)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$22 Request Recieve                                                                                           */
/*  Arguments:      u1_a_NUM : Number of DID                                                                                         */
/*                  st_ap_DID : DID Data                                                                                             */
/*                  u1_ap_NRC : NRC                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void           vd_g_DiagAppResponse_Sid22(const U1 u1_a_NUM, const ST_DIAG_DID * st_ap_DID, const U1 * u1_ap_NRC)
{
    U1  u1_t_nrc;
    U4  u4_t_lpcnt;
    U4  u4_t_buf;
    U2  u2_t_dtlen;
    U4  u4_t_lenchk;

    u4_t_buf = (U4)0U;
    u1_t_nrc = (U1)DAIAGAPP_NRC_INIT;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u1_a_NUM; u4_t_lpcnt++) {
        /*肯定応答の場合に応答データRAMにデータ格納*/
        u2_t_dtlen = st_ap_DID[u4_t_lpcnt].u2_DataLength;
        u4_t_lenchk = u4_t_buf + (U4)u2_t_dtlen + (U4)DIAGAPP_SID22_DID_SIZE;
        if(u4_t_lenchk > (U4)DIAGAPP_MAX_DATA_SIZE) {
            u1_t_nrc = (U1)OXDC_SAL_PROC_NR_14;
            break;
        } else {
            if(u1_ap_NRC[u4_t_lpcnt] == (U1)DIAGAPP_SID22_POSRES) {
                st_s_diagapp_sid22_ans.u1p_tx[u4_t_buf] = (U1)((st_ap_DID[u4_t_lpcnt].u2_DID >> DIAGAPP_SFT_08) & 0x00FFU);
                st_s_diagapp_sid22_ans.u1p_tx[u4_t_buf + 1] = (U1)(st_ap_DID[u4_t_lpcnt].u2_DID & 0x00FFU);
                if(u2_t_dtlen <= (U2)DIAGAPP_DID_MAXSIZE) {
                    vd_g_MemcpyU1(&st_s_diagapp_sid22_ans.u1p_tx[u4_t_buf + 2], &st_ap_DID[u4_t_lpcnt].u1_Data[0], (U4)u2_t_dtlen);
                }
                u4_t_buf += (U4)(u2_t_dtlen + (U2)DIAGAPP_SID22_DID_SIZE);
            }

            switch (u1_t_nrc) {
                case DAIAGAPP_NRC_INIT:
                case OXDC_SAL_PROC_NR_14:
                    u1_t_nrc = u1_ap_NRC[u4_t_lpcnt];
                    break;
                case OXDC_SAL_PROC_NR_31:
                    if((u1_ap_NRC[u4_t_lpcnt] == OXDC_SAL_PROC_NR_22) ||
                        (u1_ap_NRC[u4_t_lpcnt] == DIAGAPP_SID22_POSRES)) {
                            u1_t_nrc = u1_ap_NRC[u4_t_lpcnt];
                        }
                    break;
                case OXDC_SAL_PROC_NR_22:
                    if(u1_ap_NRC[u4_t_lpcnt] == (U1)DIAGAPP_SID22_POSRES) {
                        u1_t_nrc = u1_ap_NRC[u4_t_lpcnt];
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if(u4_t_buf > (U4)DIAGAPP_MAX_DATA_SIZE) {
        u1_t_nrc = (U1)OXDC_SAL_PROC_NR_14;
    }

    if(u1_t_nrc == (U1)DIAGAPP_SID22_POSRES) {
        st_s_diagapp_sid22_ans.u4_nbyte = u4_t_buf;
    }
    u1_s_diagapp_nrc = u1_t_nrc;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    07/31/2024  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
