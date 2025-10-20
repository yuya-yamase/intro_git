/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  IVI DiagApp_SID14 Function                                                                                                      */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIAGAPP_SID14_C_MAJOR          (0)
#define DIAGAPP_SID14_C_MINOR          (0)
#define DIAGAPP_SID14_C_PATCH          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include       "DiagApp_private.h"
#include       "DiagApp_SID14.h"
#include       "x_spi_ivi_sub0_SID14.h"
#include       "Dcm.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DIAGAPP_SID14_C_MAJOR != DIAGAPP_SID14_H_MAJOR) || \
     (DIAGAPP_SID14_C_MINOR != DIAGAPP_SID14_H_MINOR) || \
     (DIAGAPP_SID14_C_PATCH != DIAGAPP_SID14_H_PATCH))
#error "DiagApp_SID14.c and DiagApp_SID14.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIAGAPP_SID14_REQ_DATA_LENGTH           ((uint8)3U)     /* Data Length            */
#define DIAGAPP_SID14_SHIFT_DTC_HIGH            (16U)           /* DTC High Shift         */
#define DIAGAPP_SID14_SHIFT_DTC_MIDDLE          (8U)            /* DTC Middle Shift       */
#define DIAGAPP_SID14_DTC_HIGH                  (0U)            /* DTC High Bufpos        */
#define DIAGAPP_SID14_DTC_MIDDLE                (1U)            /* DTC Middle Bufpos      */
#define DIAGAPP_SID14_DTC_LOW                   (2U)            /* DTC Low Bufpos         */
#define DIAGAPP_SID14_ENABLE_DTC                (0xFFFFFFU)     /* GroupOfDTC             */
#define DIAGAPP_SID14_MEMSEL_OCCDTC             (0x11U)         /* Memory Selection OccurrenceDTC(0x11)    */
#define DIAGAPP_SID14_MEMSEL_MNTDTC             (0x12U)         /* Memory Selection MaintenanceDTC(0x12)   */
#define DIAGAPP_SID14_MEMSEL_SECDTC             (0x14U)         /* Memory Selection SecurityEventDTC(0x14) */

#define DIAGAPP_SID14_REQ_OFF_MEMSEL            ((uint8)3U)     /* MemorySelection Bufpos */
#define DIAGAPP_SID14_REQ_MEMSEL_LEN            ((uint8)1U)     /* MemorySelection Size   */
/* リクエストデータのMemorySelection有りのデータサイズ */
#define DIAGAPP_SID14_REQ_DATA_AND_MEMSEL_LEN   ((uint32)(DIAGAPP_SID14_REQ_DATA_LENGTH + DIAGAPP_SID14_REQ_MEMSEL_LEN))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_OXDC_ANS st_s_diagapp_sid14_ans;
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
void            vd_g_DiagAppSID14Init(void)
{
    u1_s_diagapp_nrc = (U1)DIAGAPP_NRC_INIT;
}

/*===================================================================================================================================*/
/*  void            vd_g_DiagAppSID14Request(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$14 Request Recieve                                                                                           */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void           vd_g_DiagAppSID14Request(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    U1 u1_t_dataLength;         /* Data Length     */
    U4 u4_t_groupOfDTC;         /* DTC             */
    U1 u1_t_memorySelection;    /* MemorySelection */
    U1 u1_t_NRC;                /* NRC             */
    U1 u1_t_requestId;          /* RequetID        */
    U1 u1_t_result;

    /* Data Length */
    u1_t_dataLength = (U1)st_ap_REQ->u4_nbyte;
    u1_t_NRC = (U1)0U;

    if (st_ap_REQ->u2_tim_elpsd == (U2)0U) {
        st_s_diagapp_sid14_ans.u1p_tx = st_ap_ans->u1p_tx;
        st_s_diagapp_sid14_ans.u4_nbyte = st_ap_ans->u4_nbyte;
        /* RequestID */
        u1_t_requestId = u1_g_DiagAppConvPduIdToRequestId(st_ap_REQ->u1_req_type);
        if((u1_t_requestId == (U1)DIAGAPP_REQUESTID_PHYON) ||
           (u1_t_requestId == (U1)DIAGAPP_REQUESTID_FUNCON)) {
            vd_g_DiagAppAnsTxNRC((U1)DIAGAPP_NRC_NONSUP);
            return;
        }
        /* Data Length Check */
        if ((u1_t_dataLength == (U1)DIAGAPP_SID14_REQ_DATA_LENGTH) ||
            (u1_t_dataLength == (U1)DIAGAPP_SID14_REQ_DATA_AND_MEMSEL_LEN)) {
            /* DTC group */
            u4_t_groupOfDTC = (((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID14_DTC_HIGH]) << DIAGAPP_SID14_SHIFT_DTC_HIGH) |
            (((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID14_DTC_MIDDLE]) << DIAGAPP_SID14_SHIFT_DTC_MIDDLE) |
            ((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID14_DTC_LOW]);

            /* Memory Selection*/
            if (u1_t_dataLength == (U1)DIAGAPP_SID14_REQ_DATA_AND_MEMSEL_LEN) {
                u1_t_memorySelection = st_ap_REQ->u1p_RX[DIAGAPP_SID14_REQ_OFF_MEMSEL];
            }
            else {
                /* Not MemorySelection */
                u1_t_memorySelection = 0;
            }

            if (u4_t_groupOfDTC != (U4)DIAGAPP_SID14_ENABLE_DTC) {
                /* --- error --- */
                /* Group Of DTC */
                /* NRC:0x31 */
                vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_31);
            }
            else if((u1_t_dataLength == (U1)DIAGAPP_SID14_REQ_DATA_AND_MEMSEL_LEN) &&
                   ((u1_t_memorySelection != (U1)DIAGAPP_SID14_MEMSEL_OCCDTC) &&
                    (u1_t_memorySelection != (U1)DIAGAPP_SID14_MEMSEL_MNTDTC) &&
                    (u1_t_memorySelection != (U1)DIAGAPP_SID14_MEMSEL_SECDTC))) {
                /* --- error --- */
                /* Memory Selection */
                /* NRC:0x31 */
                vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_31);
            }
            else {
                /* DTC Clear Request */
                u1_t_result = u1_g_XspiIviSub0Request_Sid14(u1_t_requestId, u1_t_dataLength, u4_t_groupOfDTC, u1_t_memorySelection, &u1_t_NRC);
                if (u1_t_result == (U1)E_NOT_OK) {
                    /* NRC */
                    vd_g_DiagAppAnsTxNRC(u1_t_NRC);
                }
                else {
                    /* E_OK: Do Nothing */
                }
            }
        }
        else {
            /* --- Data Length error --- */
            /* NRC:0x13 */
            vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_13);
        }
    } else {
        if(u1_s_diagapp_nrc == (U1)DIAGAPP_NRC_POSRES) {
            vd_g_DiagAppAnsTx(&st_s_diagapp_sid14_ans);
        } else if(u1_s_diagapp_nrc != (U1)DIAGAPP_NRC_INIT) {
            vd_g_DiagAppAnsTxNRC(u1_s_diagapp_nrc);
        } else {
            /*Do Nothing*/
        }
        u1_s_diagapp_nrc = (U1)DIAGAPP_NRC_INIT;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_DiagAppResponse_Sid14(const U1 u1_a_NRC)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$14 Request Recieve                                                                                           */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppResponse_Sid14(const U1 u1_a_NRC)
{
    if(u1_a_NRC == (U1)0U) {
        st_s_diagapp_sid14_ans.u4_nbyte = (U4)0U;
        st_s_diagapp_sid14_ans.u1p_tx[0] = (U1)0U;
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
/*  0.0.0    07/17/2024  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
