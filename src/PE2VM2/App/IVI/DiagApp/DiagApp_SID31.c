/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  IVI DiagApp_SID31 Function                                                                                                      */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIAGAPP_SID31_C_MAJOR          (0)
#define DIAGAPP_SID31_C_MINOR          (0)
#define DIAGAPP_SID31_C_PATCH          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include       "DiagApp_private.h"
#include       "DiagApp_SID31.h"
#include       "x_spi_ivi_sub0_SID31.h"
#include       "Dcm.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DIAGAPP_SID31_C_MAJOR != DIAGAPP_SID31_H_MAJOR) || \
     (DIAGAPP_SID31_C_MINOR != DIAGAPP_SID31_H_MINOR) || \
     (DIAGAPP_SID31_C_PATCH != DIAGAPP_SID31_H_PATCH))
#error "DiagApp_SID31.c and DiagApp_SID31.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIAGAPP_SID31_MIN_REQ_SIZE      (3U)

#define DIAGAPP_SID31_POSRES            (0U)
#define DIAGAPP_SID31_NRC_7F            (0x7FU)

#define DIAGAPP_SID31_SF                (0U)        /* Sub Function Position */
#define DIAGAPP_SID31_SF_01             (0x01)      /* Sub Fubction:0x01     */
#define DIAGAPP_SID31_SF_02             (0x02)      /* Sub Fubction:0x02     */
#define DIAGAPP_SID31_SF_03             (0x03)      /* Sub Fubction:0x03     */
#define DIAGAPP_SID31_SF_MASK           (0x7FU)
#define DIAGAPP_SID31_RID_HIGH_POS      (1U)
#define DIAGAPP_SID31_RID_LOW_POS       (2U)
/*request buf position*/
#define DIAGAPP_SID31_RID_DATA_POS      (3U)
/*response buf position*/
#define DIAGAPP_SID31_ROUTINEINFO_POS   (3U)
#define DIAGAPP_SID31_RES_RID_DATA_POS  (4U)

#define DIAGAPP_SID31_SF_OFFSET         (0x03)
#define DIAGAPP_SID31_SF_DATA_OFFSET    (0x01)

/* On-Board Support RID */
#define DIAGAPP_SID31_RID_D000          (0xD000U)
/* Function Adrress Support RID */
#define DIAGAPP_SID31_RID_DA00          (0xDA00U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_OXDC_ANS st_s_diagapp_sid31_ans;
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
void            vd_g_DiagAppSID31Init(void)
{
    u1_s_diagapp_nrc = (U1)DIAGAPP_NRC_INIT;
}

/*===================================================================================================================================*/
/*  void            vd_g_DiagAppSID31Request(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$31 Request Recieve                                                                                           */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void           vd_g_DiagAppSID31Request(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    static U1 (*const fp_sp_SID31FUNC[])(const U1 u1_a_REQID, const U2 u2_a_RID,const U2 u2_a_DTLEN,
                                         const U1 * u1_ap_DATA, U1 * u1_ap_NegativeResponseCode) = {
        &u1_g_XspiIviSub0Request_Sid31sf01,
        &u1_g_XspiIviSub0Request_Sid31sf02,
        &u1_g_XspiIviSub0Request_Sid31sf03,
    };

    U1 u1_t_nrc;                /* NRC             */
    U1 u1_t_requestId;          /* RequetID        */
    U1 u1_t_result;
    U1 u1_subfunction;
    U2 u2_t_rid;
    U2 u2_t_dtlen;

    u1_t_nrc = (U1)0U;

    if (st_ap_REQ->u2_tim_elpsd == (U2)0U) {
        st_s_diagapp_sid31_ans.u1p_tx = st_ap_ans->u1p_tx;
        st_s_diagapp_sid31_ans.u4_nbyte = st_ap_ans->u4_nbyte;

        /* Get Request ID */
        u1_t_requestId = u1_g_DiagAppConvPduIdToRequestId(st_ap_REQ->u1_req_type);

        u2_t_rid = (U2)(((U2)st_ap_REQ->u1p_RX[DIAGAPP_SID31_RID_HIGH_POS] << DIAGAPP_SFT_08) 
                 | (U2)st_ap_REQ->u1p_RX[DIAGAPP_SID31_RID_LOW_POS]);
        u2_t_dtlen = (U2)(st_ap_REQ->u4_nbyte - (U4)DIAGAPP_SID31_SF_OFFSET);

        /* Under Minimum Request Data */
        if(st_ap_REQ->u4_nbyte < (U4)DIAGAPP_SID31_MIN_REQ_SIZE) {
            /* NRC:0x13 */
            vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_13);
            return;
        }

        u1_subfunction = st_ap_REQ->u1p_RX[DIAGAPP_SID31_SF] & (U1)DIAGAPP_SID31_SF_MASK;

        if((u1_subfunction == (U1)DIAGAPP_SID31_SF_01) ||
          (u1_subfunction == (U1)DIAGAPP_SID31_SF_02)||
          (u1_subfunction == (U1)DIAGAPP_SID31_SF_03)){
            /*Do Noting*/
        } else {
            vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_12);
            return;
        }

        /* Function Address No Support */
        switch(u1_t_requestId) {
            case DIAGAPP_REQUESTID_FUNCOFF:
                if(u2_t_rid != (U2)DIAGAPP_SID31_RID_DA00){
                    vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_31);
                    return;
                }
                break;
            case DIAGAPP_REQUESTID_PHYON:
            case DIAGAPP_REQUESTID_FUNCON:
                if(u2_t_rid != (U2)DIAGAPP_SID31_RID_D000){
                    vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_31);
                    return;
                }
                break;
            default:
                break;
        }

        if(u1_subfunction <= (U1)DIAGAPP_SID31_SF_03){
            u1_t_result = (*fp_sp_SID31FUNC[u1_subfunction - 1U])(u1_t_requestId, u2_t_rid, u2_t_dtlen, &st_ap_REQ->u1p_RX[DIAGAPP_SID31_RID_DATA_POS], &u1_t_nrc);
        }
        if (u1_t_result == (U1)E_NOT_OK) {
            /* NRC */
            vd_g_DiagAppAnsTxNRC(u1_t_nrc);
        }
        else {
            /* E_OK : Do Nothing */
        }
    } else {
        if(u1_s_diagapp_nrc == (U1)DIAGAPP_NRC_POSRES) {
            vd_g_DiagAppAnsTx(&st_s_diagapp_sid31_ans);
        } else if(u1_s_diagapp_nrc != (U1)DIAGAPP_NRC_INIT) {
            vd_g_DiagAppAnsTxNRC(u1_s_diagapp_nrc);
        } else {
            /*Do Nothing*/
        }
        u1_s_diagapp_nrc = (U1)DIAGAPP_NRC_INIT;
    }
}

/*===================================================================================================================================*/
/*  void           vd_g_DiagAppResponse_Sid31sf01(const U2 u2_a_RID, const U2 u2_a_LEN, const U1 u1_a_INFO,                          */
/*                                        const U1 * u1_ap_DATA, const U1 u1_a_NRC)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$31 Request Recieve                                                                                           */
/*  Arguments:      u2_a_RID   : RID                                                                                                 */
/*                  u2_a_LEN   : Data Length                                                                                         */
/*                  u1_a_INFO  : Routine Info                                                                                        */
/*                  u1_ap_DATA : RID Data                                                                                            */
/*                  u1_a_NRC   : NRC                                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void           vd_g_DiagAppResponse_Sid31sf01(const U2 u2_a_RID, const U2 u2_a_LEN, const U1 u1_a_INFO, 
                                        const U1 * u1_ap_DATA, const U1 u1_a_NRC)
{
    U4  u4_t_cpylen;

    if (u1_a_NRC == (U1)0U) {
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_SF] = (U1)DIAGAPP_SID31_SF_01;
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_RID_HIGH_POS] = (U1)((u2_a_RID >> DIAGAPP_SFT_08) & 0x00FFU);
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_RID_LOW_POS] = (U1)(u2_a_RID & 0x00FFU);
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_ROUTINEINFO_POS] = u1_a_INFO;

        if(u2_a_LEN >= (U2)DIAGAPP_SID31_SF_DATA_OFFSET) {
            u4_t_cpylen = (U4)(u2_a_LEN - (U2)DIAGAPP_SID31_SF_DATA_OFFSET);
            if(u4_t_cpylen < (U4)DIAGAPP_MAX_DATA_SIZE - (U4)DIAGAPP_SID31_RES_RID_DATA_POS) {
                vd_g_MemcpyU1(&st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_RES_RID_DATA_POS], &u1_ap_DATA[0], u4_t_cpylen);
            }
        }

        st_s_diagapp_sid31_ans.u4_nbyte = (U4)(u2_a_LEN + (U2)DIAGAPP_SID31_SF_OFFSET);
    }
    u1_s_diagapp_nrc = u1_a_NRC;
}

/*===================================================================================================================================*/
/*  void           vd_g_DiagAppResponse_Sid31sf02(const U2 u2_a_RID, const U2 u2_a_LEN, const U1 u1_a_INFO,                          */
/*                                        const U1 * u1_ap_DATA, const U1 u1_a_NRC)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$31 Request Recieve                                                                                           */
/*  Arguments:      u2_a_RID   : RID                                                                                                 */
/*                  u2_a_LEN   : Data Length                                                                                         */
/*                  u1_a_INFO  : Routine Info                                                                                        */
/*                  u1_ap_DATA : RID Data                                                                                            */
/*                  u1_a_NRC   : NRC                                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void           vd_g_DiagAppResponse_Sid31sf02(const U2 u2_a_RID, const U2 u2_a_LEN, const U1 u1_a_INFO, 
                                        const U1 * u1_ap_DATA, const U1 u1_a_NRC)
{
    U4  u4_t_cpylen;

    if (u1_a_NRC == (U1)0U) {
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_SF] = (U1)DIAGAPP_SID31_SF_02;
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_RID_HIGH_POS] = (U1)((u2_a_RID >> DIAGAPP_SFT_08) & 0x00FFU);
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_RID_LOW_POS] = (U1)(u2_a_RID & 0x00FFU);
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_ROUTINEINFO_POS] = u1_a_INFO;

        if(u2_a_LEN >= (U2)DIAGAPP_SID31_SF_DATA_OFFSET) {
            u4_t_cpylen = (U4)(u2_a_LEN - (U2)DIAGAPP_SID31_SF_DATA_OFFSET);
            if(u4_t_cpylen < (U4)DIAGAPP_MAX_DATA_SIZE - (U4)DIAGAPP_SID31_RES_RID_DATA_POS) {
                vd_g_MemcpyU1(&st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_RES_RID_DATA_POS], &u1_ap_DATA[0], u4_t_cpylen);
            }
        }
        st_s_diagapp_sid31_ans.u4_nbyte = (U4)(u2_a_LEN + (U2)DIAGAPP_SID31_SF_OFFSET);
    }
    u1_s_diagapp_nrc = u1_a_NRC;
}

/*===================================================================================================================================*/
/*  void           vd_g_DiagAppResponse_Sid31sf03(const U2 u2_a_RID, const U2 u2_a_LEN, const U1 u1_a_INFO,                          */
/*                                        const U1 * u1_ap_DATA, const U1 u1_a_NRC)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$31 Request Recieve                                                                                           */
/*  Arguments:      u2_a_RID   : RID                                                                                                 */
/*                  u2_a_LEN   : Data Length                                                                                         */
/*                  u1_a_INFO  : Routine Info                                                                                        */
/*                  u1_ap_DATA : RID Data                                                                                            */
/*                  u1_a_NRC   : NRC                                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void           vd_g_DiagAppResponse_Sid31sf03(const U2 u2_a_RID, const U2 u2_a_LEN, const U1 u1_a_INFO, 
                                        const U1 * u1_ap_DATA, const U1 u1_a_NRC)
{
    U4  u4_t_cpylen;

    if (u1_a_NRC == (U1)0U) {
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_SF] = (U1)DIAGAPP_SID31_SF_03;
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_RID_HIGH_POS] = (U1)((u2_a_RID >> DIAGAPP_SFT_08) & 0x00FFU);
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_RID_LOW_POS] = (U1)(u2_a_RID & 0x00FFU);
        st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_ROUTINEINFO_POS] = u1_a_INFO;

        if(u2_a_LEN >= (U2)DIAGAPP_SID31_SF_DATA_OFFSET) {
            u4_t_cpylen = (U4)(u2_a_LEN - (U2)DIAGAPP_SID31_SF_DATA_OFFSET);
            if(u4_t_cpylen < (U4)DIAGAPP_MAX_DATA_SIZE - (U4)DIAGAPP_SID31_RES_RID_DATA_POS) {
                vd_g_MemcpyU1(&st_s_diagapp_sid31_ans.u1p_tx[DIAGAPP_SID31_RES_RID_DATA_POS], &u1_ap_DATA[0], u4_t_cpylen);
            }
        }
        st_s_diagapp_sid31_ans.u4_nbyte = (U4)(u2_a_LEN + (U2)DIAGAPP_SID31_SF_OFFSET);
    }
    u1_s_diagapp_nrc = u1_a_NRC;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    08/08/2024  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
