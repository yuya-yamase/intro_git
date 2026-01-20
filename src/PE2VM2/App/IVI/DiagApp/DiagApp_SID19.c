/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  IVI DiagApp_SID19 Function                                                                                                      */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIAGAPP_SID19_C_MAJOR          (0)
#define DIAGAPP_SID19_C_MINOR          (0)
#define DIAGAPP_SID19_C_PATCH          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include       "DiagApp_private.h"
#include       "DiagApp_SID19.h"
#include       "x_spi_ivi_sub0_SID19.h"
#include       "Dcm.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DIAGAPP_SID19_C_MAJOR != DIAGAPP_SID19_H_MAJOR) || \
     (DIAGAPP_SID19_C_MINOR != DIAGAPP_SID19_H_MINOR) || \
     (DIAGAPP_SID19_C_PATCH != DIAGAPP_SID19_H_PATCH))
#error "DiagApp_SID19.c and DiagApp_SID19.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIAGAPP_SID19_MIN_REQ_SIZE              ((U1)1U)        /* MIN Request Data Size */
#define DIAGAPP_SID19_SF_RES_SIZE               ((U1)1U)        /* Sub Function Data Size*/
#define DIAGAPP_SID19_SF                        ((U1)0U)        /* Sub Function Position */
#define DIAGAPP_SID19_SF_02                     ((U1)0x02)      /* Sub Fubction:0x02     */
#define DIAGAPP_SID19_SF_03                     ((U1)0x03)      /* Sub Fubction:0x03     */
#define DIAGAPP_SID19_SF_04                     ((U1)0x04)      /* Sub Fubction:0x04     */
#define DIAGAPP_SID19_SF_06                     ((U1)0x06)      /* Sub Fubction:0x06     */
#define DIAGAPP_SID19_SF_17                     ((U1)0x17)      /* Sub Fubction:0x17     */
#define DIAGAPP_SID19_SF_18                     ((U1)0x18)      /* Sub Fubction:0x18     */
#define DIAGAPP_SID19_SF_19                     ((U1)0x19)      /* Sub Fubction:0x19     */
#define DIAGAPP_SID19_SF_1A                     ((U1)0x1A)      /* Sub Fubction:0x1A     */

/*****************************************************Request*************************************************************************/

#define DIAGAPP_SID19_SF02_REQ_DTC_STATUS_MASK        (1U)      /* [Sub02][request]DTCStatusMask Bufpos  */

#define DIAGAPP_SID19_SF04_REQ_DTC_HIGH               (1U)      /* [Sub04][request]DTC High Bufpos       */
#define DIAGAPP_SID19_SF04_REQ_DTC_MIDDLE             (2U)      /* [Sub04][request]DTC Middle Bufpos     */
#define DIAGAPP_SID19_SF04_REQ_DTC_LOW                (3U)      /* [Sub04][request]DTC Low bufpos        */
#define DIAGAPP_SID19_SF04_REQ_RECORD_NUMBER          (4U)      /* [Sub04][request]RecordNumber Bufpos   */

#define DIAGAPP_SID19_SF06_REQ_DTC_HIGH               (1U)      /* [Sub06][request]DTC High Bufpos       */
#define DIAGAPP_SID19_SF06_REQ_DTC_MIDDLE             (2U)      /* [Sub06][request]DTC Middle Bufpos     */
#define DIAGAPP_SID19_SF06_REQ_DTC_LOW                (3U)      /* [Sub06][request]DTC Low bufpos        */
#define DIAGAPP_SID19_SF06_REQ_RECORD_NUMBER          (4U)      /* [Sub06][request]RecordNumber Bufpos   */

#define DIAGAPP_SID19_SF17_REQ_DTC_STATUS_MASK        (1U)      /* [Sub17][request]DTCStatusMask Bufpos  */
#define DIAGAPP_SID19_SF17_REQ_MEMORY_SELECTION       (2U)      /* [Sub17][request]MemorySelection Bufpos*/

#define DIAGAPP_SID19_SF18_REQ_DTC_HIGH               (1U)      /* [Sub18][request]DTC High Bufpos       */
#define DIAGAPP_SID19_SF18_REQ_DTC_MIDDLE             (2U)      /* [Sub18][request]DTC Middle Bufpos     */
#define DIAGAPP_SID19_SF18_REQ_DTC_LOW                (3U)      /* [Sub18][request]DTC Low bufpos        */
#define DIAGAPP_SID19_SF18_REQ_RECORD_NUMBER          (4U)      /* [Sub18][request]RecordNumber Bufpos   */
#define DIAGAPP_SID19_SF18_REQ_MEMORY_SELECTION       (5U)      /* [Sub18][request]MemorySelection Bufpos*/

#define DIAGAPP_SID19_SF19_REQ_DTC_HIGH               (1U)      /* [Sub19][request]DTC High Bufpos       */
#define DIAGAPP_SID19_SF19_REQ_DTC_MIDDLE             (2U)      /* [Sub19][request]DTC Middle Bufpos     */
#define DIAGAPP_SID19_SF19_REQ_DTC_LOW                (3U)      /* [Sub19][request]DTC Low bufpos        */
#define DIAGAPP_SID19_SF19_REQ_RECORD_NUMBER          (4U)      /* [Sub19][request]RecordNumber Bufpos   */
#define DIAGAPP_SID19_SF19_REQ_MEMORY_SELECTION       (5U)      /* [Sub19][request]MemorySelection Bufpos*/

#define DIAGAPP_SID19_SF1A_REQ_RECORD                 (1U)      /* [Sub1A][request]RecordNumber Bufpos   */


#define DIAGAPP_SID19_SF02_REQ_DATA_LENGTH            (2U)
#define DIAGAPP_SID19_SF03_REQ_DATA_LENGTH            (1U)
#define DIAGAPP_SID19_SF04_REQ_DATA_LENGTH            (5U)
#define DIAGAPP_SID19_SF06_REQ_DATA_LENGTH            (5U)
#define DIAGAPP_SID19_SF17_REQ_DATA_LENGTH            (3U)
#define DIAGAPP_SID19_SF18_REQ_DATA_LENGTH            (6U)
#define DIAGAPP_SID19_SF19_REQ_DATA_LENGTH            (6U)
#define DIAGAPP_SID19_SF1A_REQ_DATA_LENGTH            (2U)

#define DIAGAPP_SID19_MEMSEL_OCCDTC                   (0x11U)   /* Memory Selection OccurrenceDTC(0x11)    */
#define DIAGAPP_SID19_MEMSEL_MNTDTC                   (0x12U)   /* Memory Selection MaintenanceDTC(0x12)   */
#define DIAGAPP_SID19_MEMSEL_SECDTC                   (0x14U)   /* Memory Selection SecurityEventDTC(0x14) */

/*****************************************************Response************************************************************************/
#define DIAGAPP_SID19_RES_DTC_MASK                    (0xFF)    /* [Response]DTC Mask                      */

#define DIAGAPP_SID19_SF02_RES_NO_DATA_SIZE           (1U)      /* [Sub02][Response]Non Data Length        */
#define DIAGAPP_SID19_SF02_RES_DTC_STATUS_MASK        (1U)      /* [Sub02][Response]DTCStatusMask Bufpos   */
#define DIAGAPP_SID19_SF02_RES_RECORD                 (2U)      /* [Sub02][Response]Record Bufpos          */

#define DIAGAPP_SID19_SF03_RES_NO_DATA_SIZE           (0U)      /* [Sub03][Response]Non Data Length        */
#define DIAGAPP_SID19_SF03_RES_RECORD                 (1U)      /* [Sub03][Response]Record Bufpos          */

#define DIAGAPP_SID19_SF04_RES_NO_DATA_SIZE           (4U)      /* [Sub04][Response]Non Data Length        */
#define DIAGAPP_SID19_SF04_RES_DTC_HIGH               (1U)      /* [Sub04][Response]DTC High Bufpos        */
#define DIAGAPP_SID19_SF04_RES_DTC_MIDDLE             (2U)      /* [Sub04][Response]DTC Middle Bufpos      */
#define DIAGAPP_SID19_SF04_RES_DTC_LOW                (3U)      /* [Sub04][Response]DTC Low Bufppos        */
#define DIAGAPP_SID19_SF04_RES_STATUS_OF_DTC          (4U)      /* [Sub04][Response]StatusOfDTC Bufpos     */
#define DIAGAPP_SID19_SF04_RES_RECORD                 (5U)      /* [Sub04][Response]Record Bufpos          */

#define DIAGAPP_SID19_SF06_RES_NO_DATA_SIZE           (4U)      /* [Sub06][Response]Non Data Length        */
#define DIAGAPP_SID19_SF06_RES_DTC_HIGH               (1U)      /* [Sub06][Response]DTC High Bufpos        */
#define DIAGAPP_SID19_SF06_RES_DTC_MIDDLE             (2U)      /* [Sub06][Response]DTC Middle Bufpos      */
#define DIAGAPP_SID19_SF06_RES_DTC_LOW                (3U)      /* [Sub06][Response]DTC Low Bufpos         */
#define DIAGAPP_SID19_SF06_RES_STATUS_OF_DTC          (4U)      /* [Sub06][Response]StatusOfDTC Bufpos     */
#define DIAGAPP_SID19_SF06_RES_RECORD                 (5U)      /* [Sub06][Response]Record Bufpos          */

#define DIAGAPP_SID19_SF17_RES_NO_DATA_SIZE           (2U)      /* [Sub17][Response]Non Data Length        */
#define DIAGAPP_SID19_SF17_RES_MEMORY_SELECTION       (1U)      /* [Sub17][Response]MemorySelection Bufpos */
#define DIAGAPP_SID19_SF17_RES_DTC_STATUS_MASK        (2U)      /* [Sub17][Response]DTCStatusMask Bufpos   */
#define DIAGAPP_SID19_SF17_RES_RECORD                 (3U)      /* [Sub17][Response]DTCAndStatusRecord Bufpos */

#define DIAGAPP_SID19_SF18_RES_NO_DATA_SIZE           (5U)      /* [Sub18][Response]Non Data Length        */
#define DIAGAPP_SID19_SF18_RES_MEMORY_SELECTION       (1U)      /* [Sub18][Response]MemorySelection Bufpos */
#define DIAGAPP_SID19_SF18_RES_DTC_HIGH               (2U)      /* [Sub18][Response]DTC High Bufpos        */
#define DIAGAPP_SID19_SF18_RES_DTC_MIDDLE             (3U)      /* [Sub18][Response]DTC Middle Bufpos      */
#define DIAGAPP_SID19_SF18_RES_DTC_LOW                (4U)      /* [Sub18][Response]DTC Low Bufpos         */
#define DIAGAPP_SID19_SF18_RES_STATUS_OF_DTC          (5U)      /* [Sub18][Response]StatusOfDTC Bufpos     */
#define DIAGAPP_SID19_SF18_RES_RECORD                 (6U)      /* [Sub18][Response]Record Bufpos          */

#define DIAGAPP_SID19_SF19_RES_NO_DATA_SIZE           (5U)      /* [Sub19][Response]Non Data Length        */
#define DIAGAPP_SID19_SF19_RES_MEMORY_SELECTION       (1U)      /* [Sub19][Response]MemorySelection Bufpos */
#define DIAGAPP_SID19_SF19_RES_DTC_HIGH               (2U)      /* [Sub19][Response]DTC Bufpos             */
#define DIAGAPP_SID19_SF19_RES_DTC_MIDDLE             (3U)      /* [Sub19][Response]DTC Middle Bufpos      */
#define DIAGAPP_SID19_SF19_RES_DTC_LOW                (4U)      /* [Sub19][Response]DTC Low Bufpos         */
#define DIAGAPP_SID19_SF19_RES_STATUS_OF_DTC          (5U)      /* [Sub19][Response]StatusOfDTC Bufpos     */
#define DIAGAPP_SID19_SF19_RES_RECORD                 (6U)      /* [Sub19][Response]Record Bufpos          */

#define DIAGAPP_SID19_SF1A_RES_NO_DATA_SIZE           (2U)      /* [Sub1A][Response]Non Data Length        */
#define DIAGAPP_SID19_SF1A_RES_DTC_MASK               (1U)      /* [Sub1A][Response]DTCAndStatusMask Bufpos */
#define DIAGAPP_SID19_SF1A_RES_RECORD_NUMBER          (2U)      /* [Sub1A][Response]RecordNumber Bufpos    */
#define DIAGAPP_SID19_SF1A_RES_RECORD                 (3U)      /* [Sub1A][Response]Record Bufpos          */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef void(*SID19_SUB_FUNCTION)(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId);

typedef struct
{
    Dcm_MsgLenType     reqDataLength;
    SID19_SUB_FUNCTION pFunc;
} ST_DIAGAPP_SID19_SF_DATA;

typedef enum {
    SID19_SF02 = 0,
    SID19_SF03,
    SID19_SF04,
    SID19_SF06,
    SID19_SF17,
    SID19_SF18,
    SID19_SF19,
    SID19_SF1A,

    SID19_SF_MAX,
} EN_DIAGAPP_SID19_SF;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_OXDC_ANS st_s_diagapp_sid19_ans;
static U1   u1_s_diagapp_nrc;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_DiagAppSID19Request_Sub02(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId);
static void    vd_s_DiagAppSID19Request_Sub03(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId);
static void    vd_s_DiagAppSID19Request_Sub04(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId);
static void    vd_s_DiagAppSID19Request_Sub06(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId);
static void    vd_s_DiagAppSID19Request_Sub17(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId);
static void    vd_s_DiagAppSID19Request_Sub18(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId);
static void    vd_s_DiagAppSID19Request_Sub19(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId);
static void    vd_s_DiagAppSID19Request_Sub1A(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId);

static const ST_DIAGAPP_SID19_SF_DATA st_sp_DIAGAPP_SFDATAMNG[SID19_SF_MAX] =
{
    /* Sub02 */
    { (Dcm_MsgLenType)DIAGAPP_SID19_SF02_REQ_DATA_LENGTH, vd_s_DiagAppSID19Request_Sub02 },
    /* Sub03 */
    { (Dcm_MsgLenType)DIAGAPP_SID19_SF03_REQ_DATA_LENGTH, vd_s_DiagAppSID19Request_Sub03 },
    /* Sub04 */
    { (Dcm_MsgLenType)DIAGAPP_SID19_SF04_REQ_DATA_LENGTH, vd_s_DiagAppSID19Request_Sub04 },
    /* Sub06 */
    { (Dcm_MsgLenType)DIAGAPP_SID19_SF06_REQ_DATA_LENGTH, vd_s_DiagAppSID19Request_Sub06 },
    /* Sub17 */
    { (Dcm_MsgLenType)DIAGAPP_SID19_SF17_REQ_DATA_LENGTH, vd_s_DiagAppSID19Request_Sub17 },
    /* Sub18 */
    { (Dcm_MsgLenType)DIAGAPP_SID19_SF18_REQ_DATA_LENGTH, vd_s_DiagAppSID19Request_Sub18 },
    /* Sub19 */
    { (Dcm_MsgLenType)DIAGAPP_SID19_SF19_REQ_DATA_LENGTH, vd_s_DiagAppSID19Request_Sub19 },
    /* Sub1A */
    { (Dcm_MsgLenType)DIAGAPP_SID19_SF1A_REQ_DATA_LENGTH, vd_s_DiagAppSID19Request_Sub1A },
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
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
void            vd_g_DiagAppSID19Init(void)
{
    u1_s_diagapp_nrc = (U1)DIAGAPP_NRC_INIT;
}

/*===================================================================================================================================*/
/*  void            vd_g_DiagAppSID19Request(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$19 Request Recieve                                                                                           */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppSID19Request(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    U4 u4_t_dataLength;             /* Data Length  */
    EN_DIAGAPP_SID19_SF en_t_sf;    /* Sub Function */
    U1 u1_t_requestId;              /* RequestID    */

    /* Data Length */
    u4_t_dataLength = st_ap_REQ->u4_nbyte;

    if (st_ap_REQ->u2_tim_elpsd == (U2)0U) {
        /* Get Request ID */
        u1_t_requestId = u1_g_DiagAppConvPduIdToRequestId(st_ap_REQ->u1_pdu_rx);

        if(u1_t_requestId == (U1)DIAGAPP_REQUESTID_FUNCOFF) {
            vd_g_DiagAppAnsTxNRC((U1)DIAGAPP_NRC_NONSUP);
            return;
        }
        st_s_diagapp_sid19_ans.u1p_tx = st_ap_ans->u1p_tx;
        st_s_diagapp_sid19_ans.u4_nbyte = st_ap_ans->u4_nbyte;
        /* Data Length < minimun request size */
        if (u4_t_dataLength < (U4)DIAGAPP_SID19_MIN_REQ_SIZE)
        {
            /* NRC:0x13 */
            vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_13);
            return;
        }
        switch (st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF])
        {
        case DIAGAPP_SID19_SF_02:
            en_t_sf = SID19_SF02;
            break;

        case DIAGAPP_SID19_SF_03:
            en_t_sf = SID19_SF03;
            break;

        case DIAGAPP_SID19_SF_04:
            en_t_sf = SID19_SF04;
            break;

        case DIAGAPP_SID19_SF_06:
            en_t_sf = SID19_SF06;
            break;

        case DIAGAPP_SID19_SF_17:
            en_t_sf = SID19_SF17;
            break;

        case DIAGAPP_SID19_SF_18:
            en_t_sf = SID19_SF18;
            break;

        case DIAGAPP_SID19_SF_19:
            en_t_sf = SID19_SF19;
            break;

        case DIAGAPP_SID19_SF_1A:
            en_t_sf = SID19_SF1A;
            break;

        default:
            /* Not Support */
            /* NRC:0x12 */
            vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_12);
            return;
        }

        /* Data Length Check */
        if ((st_sp_DIAGAPP_SFDATAMNG[en_t_sf].reqDataLength) != u4_t_dataLength) {
            /* MSG Length Mismatch */
            /* NRC:0x13 */
            vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_13);
            return;
        }

        /* SubFunction Run */
        st_sp_DIAGAPP_SFDATAMNG[en_t_sf].pFunc(st_ap_REQ, st_ap_ans, u1_t_requestId);

    } else {
        if(u1_s_diagapp_nrc == (U1)DIAGAPP_NRC_POSRES) {
            vd_g_DiagAppAnsTx(&st_s_diagapp_sid19_ans);
        } else if(u1_s_diagapp_nrc != (U1)DIAGAPP_NRC_INIT) {
            vd_g_DiagAppAnsTxNRC(u1_s_diagapp_nrc);
        } else {
            /*Do Nothing*/
        }
        u1_s_diagapp_nrc = (U1)DIAGAPP_NRC_INIT;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DiagAppSID19Request_Sub02(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFunction02 Request                                                                                            */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*                  u1_a_RequestId : Request ID                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DiagAppSID19Request_Sub02(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U1 u1_a_REQID)
{
    U1 u1_a_DTCStatusMask;      /* DTC    */
    U1 u1_t_NRC;                /* NRC    */
    U1 u1_t_result;             /* Return */

    u1_t_NRC = (U1)0U;
    u1_a_DTCStatusMask = st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF02_REQ_DTC_STATUS_MASK];
    u1_t_result = u1_g_XspiIviSub0Request_SID19sf02(u1_a_REQID, u1_a_DTCStatusMask, &u1_t_NRC);

    if (u1_t_result == (U1)E_NOT_OK) {
        /* NRC */
        vd_g_DiagAppAnsTxNRC(u1_t_NRC);
    }
    else {
        /* E_OK : Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DiagAppSID19Request_Sub03(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFunction03 Request                                                                                            */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*                  u1_a_RequestId : Request ID                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DiagAppSID19Request_Sub03(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U1 u1_a_REQID)
{
    U1 u1_t_NRC;                /* NRC    */
    U1 u1_t_result;             /* Return */

    u1_t_NRC = (U1)0U;
    u1_t_result = u1_g_XspiIviSub0Request_SID19sf03(u1_a_REQID, &u1_t_NRC);

    if (u1_t_result == (U1)E_NOT_OK) {
        /* NRC */
        vd_g_DiagAppAnsTxNRC(u1_t_NRC);
    }
    else {
        /* E_OK : Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DiagAppSID19Request_Sub04(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFunction04 Request                                                                                            */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*                  u1_a_RequestId : Request ID                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DiagAppSID19Request_Sub04(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U1 u1_a_REQID)
{
    U4 u4_t_DTCMaskRecord;
    U1 u1_t_DTCSnapshotRecordNumber;
    U1 u1_t_NRC;
    U1 u1_t_result;

    u1_t_NRC = (U1)0U;
    u4_t_DTCMaskRecord = (((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF04_REQ_DTC_HIGH]) << DIAGAPP_SFT_16) |
                         (((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF04_REQ_DTC_MIDDLE]) << DIAGAPP_SFT_08) |
                         ((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF04_REQ_DTC_LOW]);
    u1_t_DTCSnapshotRecordNumber = st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF04_REQ_RECORD_NUMBER];

    u1_t_result = u1_g_XspiIviSub0Request_SID19sf04(u1_a_REQID, u4_t_DTCMaskRecord, u1_t_DTCSnapshotRecordNumber, &u1_t_NRC);

    if (u1_t_result == (U1)E_NOT_OK) {
        /* NRC */
        vd_g_DiagAppAnsTxNRC(u1_t_NRC);
    }
    else {
        /* E_OK : Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DiagAppSID19Request_Sub06(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFunction06 Request                                                                                            */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*                  u1_a_RequestId : Request ID                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DiagAppSID19Request_Sub06(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U1 u1_a_REQID)
{
    U4 u4_t_DTCMaskRecord;
    U1 u1_t_DTCExtDataRecordNumber;
    U1 u1_t_NRC;
    U1 u1_t_result;

    u1_t_NRC = (U1)0U;
    u4_t_DTCMaskRecord = (((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF06_REQ_DTC_HIGH]) << DIAGAPP_SFT_16) |
                         (((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF06_REQ_DTC_MIDDLE]) << DIAGAPP_SFT_08) |
                         ((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF06_REQ_DTC_LOW]);
    u1_t_DTCExtDataRecordNumber = st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF06_REQ_RECORD_NUMBER];

    u1_t_result = u1_g_XspiIviSub0Request_SID19sf06(u1_a_REQID, u4_t_DTCMaskRecord, u1_t_DTCExtDataRecordNumber, &u1_t_NRC);

    if (u1_t_result == (U1)E_NOT_OK) {
        /* NRC */
        vd_g_DiagAppAnsTxNRC(u1_t_NRC);
    }
    else {
        /* E_OK : Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DiagAppSID19Request_Sub17(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFunction17 Request                                                                                            */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*                  u1_a_RequestId : Request ID                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DiagAppSID19Request_Sub17(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U1 u1_a_REQID)
{
    U1 u1_t_MemorySelection;
    U1 u1_t_DTCStatusMask;
    U1 u1_t_NRC;
    U1 u1_t_result;

    u1_t_NRC = (U1)0U;
    u1_t_MemorySelection = st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF17_REQ_MEMORY_SELECTION];
    u1_t_DTCStatusMask = st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF17_REQ_DTC_STATUS_MASK];

    if((u1_t_MemorySelection != (U1)DIAGAPP_SID19_MEMSEL_OCCDTC) &&
       (u1_t_MemorySelection != (U1)DIAGAPP_SID19_MEMSEL_MNTDTC) &&
       (u1_t_MemorySelection != (U1)DIAGAPP_SID19_MEMSEL_SECDTC)) {
        vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_31);
    } else {
        u1_t_result = u1_g_XspiIviSub0Request_SID19sf17(u1_a_REQID, u1_t_DTCStatusMask, u1_t_MemorySelection, &u1_t_NRC);

        if (u1_t_result == (U1)E_NOT_OK) {
            /* NRC */
            vd_g_DiagAppAnsTxNRC(u1_t_NRC);
        }
        else {
            /* E_OK : Do Nothing */
        }
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DiagAppSID19Request_Sub18(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFunction18 Request                                                                                            */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*                  u1_a_RequestId : Request ID                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DiagAppSID19Request_Sub18(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U1 u1_a_REQID)
{
    U1 u1_t_MemorySelection;
    U4 u4_t_DTCMaskRecord;
    U1 u1_t_DTCSnapshotRecordNumber;
    U1 u1_t_NRC;
    U1 u1_t_result;

    u1_t_NRC = (U1)0U;
    u1_t_MemorySelection = st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF18_REQ_MEMORY_SELECTION];
    u4_t_DTCMaskRecord = (((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF18_REQ_DTC_HIGH]) << DIAGAPP_SFT_16) |
                         (((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF18_REQ_DTC_MIDDLE]) << DIAGAPP_SFT_08) |
                          ((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF18_REQ_DTC_LOW]);
    u1_t_DTCSnapshotRecordNumber = st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF18_REQ_RECORD_NUMBER];

    if((u1_t_MemorySelection != (U1)DIAGAPP_SID19_MEMSEL_OCCDTC) &&
       (u1_t_MemorySelection != (U1)DIAGAPP_SID19_MEMSEL_MNTDTC) &&
       (u1_t_MemorySelection != (U1)DIAGAPP_SID19_MEMSEL_SECDTC)) {
        vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_31);
    } else {
        u1_t_result = u1_g_XspiIviSub0Request_SID19sf18(u1_a_REQID, u4_t_DTCMaskRecord, u1_t_DTCSnapshotRecordNumber, u1_t_MemorySelection, &u1_t_NRC);

        if (u1_t_result == (U1)E_NOT_OK) {
            /* NRC */
            vd_g_DiagAppAnsTxNRC(u1_t_NRC);
        }
        else {
            /* E_OK : Do Nothing */
        }
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DiagAppSID19Request_Sub19(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFunction19 Request                                                                                            */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*                  u1_a_RequestId : Request ID                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DiagAppSID19Request_Sub19(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U1 u1_a_REQID)
{
    U1 u1_t_MemorySelection;
    U4 u4_t_DTCMaskRecord;
    U1 u1_t_DTCExtDataRecordNumber;
    U1 u1_t_NRC;
    U1 u1_t_result;

    u1_t_NRC = (U1)0U;
    u1_t_MemorySelection = st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF19_REQ_MEMORY_SELECTION];
    u4_t_DTCMaskRecord = (((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF19_REQ_DTC_HIGH]) << DIAGAPP_SFT_16) |
                         (((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF19_REQ_DTC_MIDDLE]) << DIAGAPP_SFT_08) |
                          ((U4)st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF19_REQ_DTC_LOW]);
    u1_t_DTCExtDataRecordNumber = st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF19_REQ_RECORD_NUMBER];

    if((u1_t_MemorySelection != (U1)DIAGAPP_SID19_MEMSEL_OCCDTC) &&
       (u1_t_MemorySelection != (U1)DIAGAPP_SID19_MEMSEL_MNTDTC) &&
       (u1_t_MemorySelection != (U1)DIAGAPP_SID19_MEMSEL_SECDTC)) {
        vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_31);
    } else {
        u1_t_result = u1_g_XspiIviSub0Request_SID19sf19(u1_a_REQID, u4_t_DTCMaskRecord, u1_t_DTCExtDataRecordNumber, u1_t_MemorySelection, &u1_t_NRC);

        if (u1_t_result == (U1)E_NOT_OK) {
            /* NRC */
            vd_g_DiagAppAnsTxNRC(u1_t_NRC);
        }
        else {
            /* E_OK : Do Nothing */
        }
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DiagAppSID19Request_Sub1A(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, U1 u1_a_RequestId)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFunction1A Request                                                                                            */
/*  Arguments:      st_ap_REQ : Request Data                                                                                         */
/*                  st_ap_ans : Response Data                                                                                        */
/*                  u1_a_RequestId : Request ID                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DiagAppSID19Request_Sub1A(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U1 u1_a_REQID)
{

    U1 u1_t_DTCExtDataRecordNumber;
    U1 u1_t_NRC;
    U1 u1_t_result;

    u1_t_NRC = (U1)0U;
    u1_t_DTCExtDataRecordNumber = st_ap_REQ->u1p_RX[DIAGAPP_SID19_SF1A_REQ_RECORD];

    u1_t_result = u1_g_XspiIviSub0Request_SID19sf1A(u1_a_REQID, u1_t_DTCExtDataRecordNumber, &u1_t_NRC);

    if (u1_t_result == (U1)E_NOT_OK) {
        /* NRC */
        vd_g_DiagAppAnsTxNRC(u1_t_NRC);
    }
    else {
        /* E_OK : Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  void       vd_g_DiagAppResponse_Sid19sf02(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 u1_a_DTCMSK, const U1 * u1_ap_DATA)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$19 SubFunction02 Response Recieve                                                                            */
/*  Arguments:      u1_a_NRC : Negative Response Code                                                                                */
/*                  u2_a_LEN : Data Length                                                                                           */
/*                  u1_a_DTCMSK : DTCStatusAvailabilityMask                                                                          */
/*                  u1_ap_DATA : Response Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppResponse_Sid19sf02(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 u1_a_DTCMSK, const U1 * u1_ap_DATA)
{
    U4  u4_t_dtlen;
    U4  u4_t_cpylen;

    u4_t_dtlen = (U4)0U;
    u4_t_cpylen = (U4)0U;

    if (u1_a_NRC == (U1)0U) {
        /* SubFunction */
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF] = (U1)DIAGAPP_SID19_SF_02;
        /* DTCStatusMask */
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF02_RES_DTC_STATUS_MASK] = u1_a_DTCMSK;

        if(u2_a_LEN >= (U2)DIAGAPP_SID19_SF02_RES_NO_DATA_SIZE) {
            u4_t_cpylen = (U4)(u2_a_LEN - (U2)DIAGAPP_SID19_SF02_RES_NO_DATA_SIZE);

            if(u4_t_cpylen <= (U4)DIAGAPP_MAX_DATA_SIZE - (U4)DIAGAPP_SID19_SF02_RES_RECORD) {
                vd_g_MemcpyU1(&st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF02_RES_RECORD], &u1_ap_DATA[0], u4_t_cpylen);
            }
        }
        u4_t_dtlen = (U4)(u2_a_LEN + (U2)DIAGAPP_SID19_SF_RES_SIZE);

        st_s_diagapp_sid19_ans.u4_nbyte = u4_t_dtlen;
    }
    u1_s_diagapp_nrc = u1_a_NRC;
}

/*===================================================================================================================================*/
/*  void       vd_g_DiagAppResponse_Sid19sf03(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 * u1_ap_DATA)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$19 SubFunction03 Response Recieve                                                                            */
/*  Arguments:      u1_a_NRC : Negative Response Code                                                                                */
/*                  u2_a_LEN : Data Length                                                                                           */
/*                  u1_ap_DATA : Response Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppResponse_Sid19sf03(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 * u1_ap_DATA)
{
    U4  u4_t_dtlen;

    u4_t_dtlen = (U4)0U;

    if (u1_a_NRC == (U1)0U) {
        /* SubFunction */
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF] = (U1)DIAGAPP_SID19_SF_03;

        if(u2_a_LEN <= (U2)DIAGAPP_MAX_DATA_SIZE - (U2)DIAGAPP_SID19_SF03_RES_RECORD) {
            vd_g_MemcpyU1(&st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF03_RES_RECORD], &u1_ap_DATA[0], (U4)u2_a_LEN);
        }

        u4_t_dtlen = (U4)(u2_a_LEN + (U2)DIAGAPP_SID19_SF_RES_SIZE);

        st_s_diagapp_sid19_ans.u4_nbyte = u4_t_dtlen;
    }
    u1_s_diagapp_nrc = u1_a_NRC;
}

/*===================================================================================================================================*/
/*  void       vd_g_DiagAppResponse_Sid19sf04(const U1 u1_a_NRC, const U2 u2_a_LEN, const U4 u4_a_DTC                                */
/*                                          , const U1 u1_a_DTCSTS, const U1 * u1_ap_DATA)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$19 SubFunction04 Response Recieve                                                                            */
/*  Arguments:      u1_a_NRC : Negative Response Code                                                                                */
/*                  u2_a_LEN : Data Length                                                                                           */
/*                  u4_a_DTC : DTC Data                                                                                              */
/*                  u1_a_DTCSTS : status of DTC                                                                                      */
/*                  u1_ap_DATA : Response Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppResponse_Sid19sf04(const U1 u1_a_NRC, const U2 u2_a_LEN, const U4 u4_a_DTC
                                             , const U1 u1_a_DTCSTS, const U1 * u1_ap_DATA)
{
    U4  u4_t_dtlen;
    U4  u4_t_cpylen;

    u4_t_dtlen = (U4)0U;
    u4_t_cpylen = (U4)0U;

    if (u1_a_NRC == (U1)0U) {
        /* SubFunction */
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF] = (U1)DIAGAPP_SID19_SF_04;
        /*DTC*/
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF04_RES_DTC_HIGH] = (U1)((u4_a_DTC >> DIAGAPP_SFT_16) & DIAGAPP_SID19_RES_DTC_MASK);
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF04_RES_DTC_MIDDLE] = (U1)((u4_a_DTC >> DIAGAPP_SFT_08) & DIAGAPP_SID19_RES_DTC_MASK);
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF04_RES_DTC_LOW] = (U1)(u4_a_DTC & DIAGAPP_SID19_RES_DTC_MASK);
        /*Status of DTC*/
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF04_RES_STATUS_OF_DTC] = u1_a_DTCSTS;

        if(u2_a_LEN >= (U2)DIAGAPP_SID19_SF04_RES_NO_DATA_SIZE) {
            u4_t_cpylen = (U4)(u2_a_LEN - (U2)DIAGAPP_SID19_SF04_RES_NO_DATA_SIZE);

            if(u4_t_cpylen <= (U4)DIAGAPP_MAX_DATA_SIZE - (U4)DIAGAPP_SID19_SF04_RES_RECORD) {
                vd_g_MemcpyU1(&st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF04_RES_RECORD], &u1_ap_DATA[0], u4_t_cpylen);
            }
        }
        u4_t_dtlen = (U4)(u2_a_LEN + (U2)DIAGAPP_SID19_SF_RES_SIZE);

        st_s_diagapp_sid19_ans.u4_nbyte = u4_t_dtlen;
    }
    u1_s_diagapp_nrc = u1_a_NRC;
}

/*===================================================================================================================================*/
/*  void       vd_g_DiagAppResponse_Sid19sf06(const U1 u1_a_NRC, const U2 u2_a_LEN, const U4 u4_a_DTC                                */
/*                                          , const U1 u1_a_DTCSTS, const U1 * u1_ap_DATA)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$19 SubFunction06 Response Recieve                                                                            */
/*  Arguments:      u1_a_NRC : Negative Response Code                                                                                */
/*                  u2_a_LEN : Data Length                                                                                           */
/*                  u4_a_DTC : DTC Data                                                                                              */
/*                  u1_a_DTCSTS : status of DTC                                                                                      */
/*                  u1_ap_DATA : Response Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppResponse_Sid19sf06(const U1 u1_a_NRC, const U2 u2_a_LEN, const U4 u4_a_DTC
                                             , const U1 u1_a_DTCSTS, const U1 * u1_ap_DATA)
{
    U4  u4_t_dtlen;
    U4  u4_t_cpylen;

    u4_t_dtlen = (U4)0U;
    u4_t_cpylen = (U4)0U;

    if (u1_a_NRC == (U1)0U) {
        /* SubFunction */
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF] = (U1)DIAGAPP_SID19_SF_06;
        /*DTC*/
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF06_RES_DTC_HIGH] = (U1)((u4_a_DTC >> DIAGAPP_SFT_16) & DIAGAPP_SID19_RES_DTC_MASK);
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF06_RES_DTC_MIDDLE] = (U1)((u4_a_DTC >> DIAGAPP_SFT_08) & DIAGAPP_SID19_RES_DTC_MASK);
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF06_RES_DTC_LOW] = (U1)(u4_a_DTC & DIAGAPP_SID19_RES_DTC_MASK);
        /*Status of DTC*/
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF06_RES_STATUS_OF_DTC] = u1_a_DTCSTS;

        if(u2_a_LEN >= (U2)DIAGAPP_SID19_SF06_RES_NO_DATA_SIZE) {
            u4_t_cpylen = (U4)(u2_a_LEN - (U2)DIAGAPP_SID19_SF06_RES_NO_DATA_SIZE);

            if(u4_t_cpylen <= (U4)DIAGAPP_MAX_DATA_SIZE - (U4)DIAGAPP_SID19_SF06_RES_RECORD) {
                vd_g_MemcpyU1(&st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF06_RES_RECORD], &u1_ap_DATA[0], u4_t_cpylen);
            }
        }
        u4_t_dtlen = (U4)(u2_a_LEN + (U2)DIAGAPP_SID19_SF_RES_SIZE);

        st_s_diagapp_sid19_ans.u4_nbyte = u4_t_dtlen;
    }
    u1_s_diagapp_nrc = u1_a_NRC;
}

/*===================================================================================================================================*/
/*  void       vd_g_DiagAppResponse_Sid19sf17(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 u1_a_MEMSEL                             */
/*                                          , const U1 u1_a_DTCSTSMSK, const U1 * u1_ap_DATA)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$19 SubFunction17 Response Recieve                                                                            */
/*  Arguments:      u1_a_NRC : Negative Response Code                                                                                */
/*                  u2_a_LEN : Data Length                                                                                           */
/*                  u1_a_MEMSEL : Memory Selection                                                                                   */
/*                  u1_a_DTCSTSMSK : DTCStatusAvailabilityMask                                                                       */
/*                  u1_ap_DATA : Response Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppResponse_Sid19sf17(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 u1_a_MEMSEL
                                             , const U1 u1_a_DTCSTSMSK, const U1 * u1_ap_DATA)
{
    U4  u4_t_dtlen;
    U4  u4_t_cpylen;

    u4_t_dtlen = (U4)0U;
    u4_t_cpylen = (U4)0U;

    if (u1_a_NRC == (U1)0U) {
        /* SubFunction */
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF] = (U1)DIAGAPP_SID19_SF_17;

        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF17_RES_MEMORY_SELECTION] = u1_a_MEMSEL;
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF17_RES_DTC_STATUS_MASK] = u1_a_DTCSTSMSK;

        if(u2_a_LEN >= (U2)DIAGAPP_SID19_SF17_RES_NO_DATA_SIZE) {
            u4_t_cpylen = (U4)(u2_a_LEN - (U2)DIAGAPP_SID19_SF17_RES_NO_DATA_SIZE);

            if(u4_t_cpylen <= (U4)DIAGAPP_MAX_DATA_SIZE - (U4)DIAGAPP_SID19_SF17_RES_RECORD) {
                vd_g_MemcpyU1(&st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF17_RES_RECORD], &u1_ap_DATA[0], u4_t_cpylen);
            }
        }
        u4_t_dtlen = (U4)(u2_a_LEN + (U2)DIAGAPP_SID19_SF_RES_SIZE);

        st_s_diagapp_sid19_ans.u4_nbyte = u4_t_dtlen;
    }
    u1_s_diagapp_nrc = u1_a_NRC;
}

/*===================================================================================================================================*/
/*  void       vd_g_DiagAppResponse_Sid19sf18(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 u1_a_MEMSEL, const U4 u4_a_DTC          */
/*                                          , const U1 u1_a_DTCSTS, const U1 * u1_ap_DATA)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$19 SubFunction18 Response Recieve                                                                            */
/*  Arguments:      u1_a_NRC : Negative Response Code                                                                                */
/*                  u2_a_LEN : Data Length                                                                                           */
/*                  u1_a_MEMSEL : Memory Selection                                                                                   */
/*                  u4_a_DTC : DTC                                                                                                   */
/*                  u1_a_DTCSTS : statusOfDTC                                                                                        */
/*                  u1_ap_DATA : Response Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppResponse_Sid19sf18(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 u1_a_MEMSEL,const U4 u4_a_DTC
                                             , const U1 u1_a_DTCSTS, const U1 * u1_ap_DATA)
{
    U4  u4_t_dtlen;
    U4  u4_t_cpylen;

    u4_t_dtlen = (U4)0U;
    u4_t_cpylen = (U4)0U;

    if (u1_a_NRC == (U1)0U) {
        /* SubFunction */
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF] = (U1)DIAGAPP_SID19_SF_18;

        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF18_RES_MEMORY_SELECTION] = u1_a_MEMSEL;
        /*DTC*/
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF18_RES_DTC_HIGH] = (U1)((u4_a_DTC >> DIAGAPP_SFT_16) & DIAGAPP_SID19_RES_DTC_MASK);
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF18_RES_DTC_MIDDLE] = (U1)((u4_a_DTC >> DIAGAPP_SFT_08) & DIAGAPP_SID19_RES_DTC_MASK);
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF18_RES_DTC_LOW] = (U1)(u4_a_DTC & DIAGAPP_SID19_RES_DTC_MASK);

        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF18_RES_STATUS_OF_DTC] = u1_a_DTCSTS;

        if(u2_a_LEN >= (U2)DIAGAPP_SID19_SF18_RES_NO_DATA_SIZE) {
            u4_t_cpylen = (U4)(u2_a_LEN - (U2)DIAGAPP_SID19_SF18_RES_NO_DATA_SIZE);

            if(u4_t_cpylen <= (U4)DIAGAPP_MAX_DATA_SIZE - (U4)DIAGAPP_SID19_SF18_RES_RECORD) {
                vd_g_MemcpyU1(&st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF18_RES_RECORD], &u1_ap_DATA[0], u4_t_cpylen);
            }
        }
        u4_t_dtlen = (U4)(u2_a_LEN + (U2)DIAGAPP_SID19_SF_RES_SIZE);

        st_s_diagapp_sid19_ans.u4_nbyte = u4_t_dtlen;
    }
    u1_s_diagapp_nrc = u1_a_NRC;
}

/*===================================================================================================================================*/
/*  void       vd_g_DiagAppResponse_Sid19sf19(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 u1_a_MEMSEL, const U4 u4_a_DTC          */
/*                                          , const U1 u1_a_DTCSTS, const U1 * u1_ap_DATA)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$19 SubFunction19 Response Recieve                                                                            */
/*  Arguments:      u1_a_NRC : Negative Response Code                                                                                */
/*                  u2_a_LEN : Data Length                                                                                           */
/*                  u1_a_MEMSEL : Memory Selection                                                                                   */
/*                  u4_a_DTC : DTC                                                                                                   */
/*                  u1_a_DTCSTS : statusOfDTC                                                                                        */
/*                  u1_ap_DATA : Response Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppResponse_Sid19sf19(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 u1_a_MEMSEL,const U4 u4_a_DTC
                                             , const U1 u1_a_DTCSTS, const U1 * u1_ap_DATA)
{
    U4  u4_t_dtlen;
    U4  u4_t_cpylen;

    u4_t_dtlen = (U4)0U;
    u4_t_cpylen = (U4)0U;

    if (u1_a_NRC == (U1)0U) {
        /* SubFunction */
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF] = (U1)DIAGAPP_SID19_SF_19;

        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF19_RES_MEMORY_SELECTION] = u1_a_MEMSEL;
        /*DTC*/
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF19_RES_DTC_HIGH] = (U1)((u4_a_DTC >> DIAGAPP_SFT_16) & DIAGAPP_SID19_RES_DTC_MASK);
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF19_RES_DTC_MIDDLE] = (U1)((u4_a_DTC >> DIAGAPP_SFT_08) & DIAGAPP_SID19_RES_DTC_MASK);
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF19_RES_DTC_LOW] = (U1)(u4_a_DTC & DIAGAPP_SID19_RES_DTC_MASK);

        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF19_RES_STATUS_OF_DTC] = u1_a_DTCSTS;

        if(u2_a_LEN >= (U2)DIAGAPP_SID19_SF19_RES_NO_DATA_SIZE) {
            u4_t_cpylen = (U4)(u2_a_LEN - (U2)DIAGAPP_SID19_SF19_RES_NO_DATA_SIZE);

            if(u4_t_cpylen <= (U4)DIAGAPP_MAX_DATA_SIZE - (U4)DIAGAPP_SID19_SF19_RES_RECORD) {
                vd_g_MemcpyU1(&st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF19_RES_RECORD], &u1_ap_DATA[0], u4_t_cpylen);
            }
        }
        u4_t_dtlen = (U4)(u2_a_LEN + (U2)DIAGAPP_SID19_SF_RES_SIZE);

        st_s_diagapp_sid19_ans.u4_nbyte = u4_t_dtlen;
    }
    u1_s_diagapp_nrc = u1_a_NRC;
}

/*===================================================================================================================================*/
/*  void       vd_g_DiagAppResponse_Sid19sf1A(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 u1_a_DTCSTSMSK                          */
/*                                          , const U1 u1_a_EXRECNUM, const U1 * u1_ap_DATA)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID$19 SubFunction1A Response Recieve                                                                            */
/*  Arguments:      u1_a_NRC : Negative Response Code                                                                                */
/*                  u2_a_LEN : Data Length                                                                                           */
/*                  u1_a_DTCSTSMSK : DTCStatusAvailabilityMask                                                                       */
/*                  u1_a_EXRECNUM : DTCExtDataRecordNumber                                                                           */
/*                  u1_ap_DATA : Response Data                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DiagAppResponse_Sid19sf1A(const U1 u1_a_NRC, const U2 u2_a_LEN, const U1 u1_a_DTCSTSMSK
                                             , const U1 u1_a_EXRECNUM, const U1 * u1_ap_DATA)
{
    U4  u4_t_dtlen;
    U4  u4_t_cpylen;

    u4_t_dtlen = (U4)0U;
    u4_t_cpylen = (U4)0U;

    if (u1_a_NRC == (U1)0U) {
        /* SubFunction */
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF] = (U1)DIAGAPP_SID19_SF_1A;
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF1A_RES_DTC_MASK] = u1_a_DTCSTSMSK;
        st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF1A_RES_RECORD_NUMBER] = u1_a_EXRECNUM;

        if(u2_a_LEN >= (U2)DIAGAPP_SID19_SF19_RES_NO_DATA_SIZE) {
            u4_t_cpylen = (U4)(u2_a_LEN - (U2)DIAGAPP_SID19_SF1A_RES_NO_DATA_SIZE);

            if(u4_t_cpylen <= (U4)DIAGAPP_MAX_DATA_SIZE - (U4)DIAGAPP_SID19_SF1A_RES_RECORD) {
                vd_g_MemcpyU1(&st_s_diagapp_sid19_ans.u1p_tx[DIAGAPP_SID19_SF1A_RES_RECORD], &u1_ap_DATA[0], u4_t_cpylen);
            }
        }
        u4_t_dtlen = (U4)(u2_a_LEN + (U2)DIAGAPP_SID19_SF_RES_SIZE);

        st_s_diagapp_sid19_ans.u4_nbyte = u4_t_dtlen;
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
/*  0.0.0    07/29/2024  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
