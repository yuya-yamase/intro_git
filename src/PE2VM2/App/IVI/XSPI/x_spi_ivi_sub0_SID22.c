/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Transmission and reception processing of subframe 0 in XSPI communication.                                                       */
/*  Handled data: DiagCAN Data                                                                                                       */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SUB0_SID22_C_MAJOR                   (0)
#define XSPI_IVI_SUB0_SID22_C_MINOR                   (0)
#define XSPI_IVI_SUB0_SID22_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub0_private.h"
#include    "x_spi_ivi_sub0_SID22.h"
#include    "DiagApp.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB0_SID22_C_MAJOR != XSPI_IVI_SUB0_SID22_H_MAJOR) || \
     (XSPI_IVI_SUB0_SID22_C_MINOR != XSPI_IVI_SUB0_SID22_H_MINOR) || \
     (XSPI_IVI_SUB0_SID22_C_PATCH != XSPI_IVI_SUB0_SID22_H_PATCH))
#error "x_spi_ivi_sub0_SID22.c and x_spi_ivi_sub0_SID22.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SID22_OPC_2201         (0x2201U)
#define XSPI_IVI_SID22_OPC_2202         (0x2202U)
#define XSPI_IVI_SID22_OPC_2203         (0x2203U)
#define XSPI_IVI_SID22_OPC_2204         (0x2204U)
#define XSPI_IVI_SID22_OPC_2205         (0x2205U)
#define XSPI_IVI_SID22_OPC_2206         (0x2206U)

#define XSPI_IVI_DIAG_OPC_2201_SIZE     (4U)
#define XSPI_IVI_DIAG_OPC_2203_SIZE     (4U)
#define XSPI_IVI_DIAG_OPC_2205_SIZE     (4U)

#define XSPI_IVI_DIAG_SID22_NODATA_SIZE (5U)

#define XSPI_IVI_DIAG_SID22_NRC_UNKNOWN (0xFFU)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_DIAG_DID st_sp_XspiIviSub0DiagSid22Did[DIAGAPP_SID22_DID_MAXNUM];
static U1   u1_s_XspiIviSub0DidNum;
static U1   u1_s_XspiIviSub0DidBuf;
static U1   u1_sp_XspiIviSub0DidResultChk[DIAGAPP_SID22_DID_MAXNUM];
static U1   u1_s_XspiIviSub0DidResultOKNum;
static U1   u1_s_XspiIviSub0Sid22ReqID;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_XspiIviSub0Request_OPC2201(void);
static void     vd_s_XspiIviSub0Request_OPC2205(void);

static void     vd_s_XspiIviSub0Response_OPC2202(const U1 * u1_ap_DATA, const U2 u2_a_LEN);
static void     vd_s_XspiIviSub0Response_OPC2206(const U1 * u1_ap_DATA);
static void     vd_s_XspiIviSub0SID22Response(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0SID22Init(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub0SID22Init(void)
{
    U4  u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DIAGAPP_SID22_DID_MAXNUM; u4_t_lpcnt++) {
        st_sp_XspiIviSub0DiagSid22Did[u4_t_lpcnt].u2_DID = (U1)0U;
        st_sp_XspiIviSub0DiagSid22Did[u4_t_lpcnt].u2_DataLength = (U2)0U;
        vd_g_MemfillU1(&st_sp_XspiIviSub0DiagSid22Did[u4_t_lpcnt].u1_Data[0], (U1)0U, (U4)DIAGAPP_DID_MAXSIZE);

        u1_sp_XspiIviSub0DidResultChk[u4_t_lpcnt] = (U1)XSPI_IVI_DIAG_SID22_NRC_UNKNOWN;
    }
    u1_s_XspiIviSub0DidNum = (U1)0U;
    u1_s_XspiIviSub0DidBuf = (U1)0U;
    u1_s_XspiIviSub0Sid22ReqID = (U1)0U;
    u1_s_XspiIviSub0DidResultOKNum = (U1)0U;
}

/*===================================================================================================================================*/
/*  U1          u1_g_XspiIviSub0Request_Sid22(const U1 u1_a_REQID, const U1 u1_a_NUM                                                 */
/*                                          , const U2 * u2_ap_DID, U1 * u1_ap_NegativeResponseCode)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID22 Request                                                                                                    */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_Sid22(const U1 u1_a_REQID, const U1 u1_a_NUM, const U2 * u2_ap_DID, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U4  u4_t_lpcnt;

    u1_t_ret = (U1)E_OK;
    u1_t_power_sts = u1_g_XspiIviSub0PowerSts();
    u1_t_oscom_chk = u1_g_XspiIviSub0OSComBridge();

    if(u1_t_power_sts != (U1)POWER_MODE_STATE_APPON) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_22;
        u1_t_ret = (U1)E_NOT_OK;
    } else if(u1_t_oscom_chk == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_22;
        u1_t_ret = (U1)E_NOT_OK;
    } else {
        u1_s_XspiIviSub0Sid22ReqID = u1_a_REQID;
        u1_s_XspiIviSub0DidNum = u1_a_NUM;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_a_NUM; u4_t_lpcnt++) {
            st_sp_XspiIviSub0DiagSid22Did[u4_t_lpcnt].u2_DID = u2_ap_DID[u4_t_lpcnt];
        }
        vd_s_XspiIviSub0Request_OPC2205();
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void     vd_s_XspiIviSub0Request_OPC2201(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID22 OPC2201 Request                                                                                            */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_XspiIviSub0Request_OPC2201(void)
{
    U1  u1_tp_data[XSPI_IVI_DIAG_OPC_2201_SIZE];
    U2  u2_t_datalength;

    u2_t_datalength = (U2)XSPI_IVI_DIAG_OPC_2201_SIZE;
    u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID22_OPC_2201 >> XSPI_IVI_SFT_08) & 0x00FFU);
    u1_tp_data[1] = ((U1)XSPI_IVI_SID22_OPC_2201 & 0x00FFU);
    u1_tp_data[2] = (U1)((st_sp_XspiIviSub0DiagSid22Did[u1_s_XspiIviSub0DidBuf].u2_DID >> XSPI_IVI_SFT_08) & 0x00FFU);
    u1_tp_data[3] = (U1)(st_sp_XspiIviSub0DiagSid22Did[u1_s_XspiIviSub0DidBuf].u2_DID & 0x00FFU);

    vd_g_XspiIviSub0Request(u2_t_datalength,u1_s_XspiIviSub0Sid22ReqID,u1_tp_data,(U1)XSPI_IVI_SID22);
}

/*===================================================================================================================================*/
/*  static void     vd_s_XspiIviSub0Request_OPC2205(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID22 OPC2205 Request                                                                                            */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_XspiIviSub0Request_OPC2205(void)
{
    U1  u1_tp_data[XSPI_IVI_DIAG_OPC_2205_SIZE];
    U2  u2_t_datalength;

    u2_t_datalength = (U2)XSPI_IVI_DIAG_OPC_2205_SIZE;
    u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID22_OPC_2205 >> XSPI_IVI_SFT_08) & 0x00FFU);
    u1_tp_data[1] = ((U1)XSPI_IVI_SID22_OPC_2205 & 0x00FFU);
    u1_tp_data[2] = (U1)((st_sp_XspiIviSub0DiagSid22Did[u1_s_XspiIviSub0DidBuf].u2_DID >> XSPI_IVI_SFT_08) & 0x00FFU);
    u1_tp_data[3] = (U1)(st_sp_XspiIviSub0DiagSid22Did[u1_s_XspiIviSub0DidBuf].u2_DID & 0x00FFU);

    vd_g_XspiIviSub0Request(u2_t_datalength,u1_s_XspiIviSub0Sid22ReqID,u1_tp_data,(U1)XSPI_IVI_SID22);
}

/*===================================================================================================================================*/
/*  void         vd_g_XspiIviSub0Response_SID22(const U1 * u1_ap_DATA, const U2 u2_a_LEN)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void         vd_g_XspiIviSub0Response_SID22(const U1 * u1_ap_DATA, const U2 u2_a_LEN)
{
    U2  u2_t_opc;

    u2_t_opc = (U2)((u1_ap_DATA[0] << XSPI_IVI_SFT_08) | u1_ap_DATA[1]);

    switch(u2_t_opc) {
        case XSPI_IVI_SID22_OPC_2202:
            vd_s_XspiIviSub0Response_OPC2202(&u1_ap_DATA[0], u2_a_LEN);
            break;
        case XSPI_IVI_SID22_OPC_2206:
            vd_s_XspiIviSub0Response_OPC2206(&u1_ap_DATA[0]);
            break;
        default:
            break;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_XspiIviSub0Response_OPC2202(const U1 * u1_ap_DATA, const U2 u2_a_LEN)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID22 OPC2204 Response                                                                                           */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_XspiIviSub0Response_OPC2202(const U1 * u1_ap_DATA, const U2 u2_a_LEN)
{
    U2  u2_t_dtlen;

    u1_sp_XspiIviSub0DidResultChk[u1_s_XspiIviSub0DidBuf] = u1_ap_DATA[2];
    u2_t_dtlen = u2_a_LEN - (U2)XSPI_IVI_DIAG_SID22_NODATA_SIZE;

    if(u1_sp_XspiIviSub0DidResultChk[u1_s_XspiIviSub0DidBuf] == (U1)E_OK) {
        st_sp_XspiIviSub0DiagSid22Did[u1_s_XspiIviSub0DidBuf].u2_DataLength = u2_t_dtlen;
        if(u2_t_dtlen <= (U2)DIAGAPP_DID_MAXSIZE) {
            vd_g_MemcpyU1(&st_sp_XspiIviSub0DiagSid22Did[u1_s_XspiIviSub0DidBuf].u1_Data[0], &u1_ap_DATA[5], (U4)u2_t_dtlen);
        }
        u1_s_XspiIviSub0DidResultOKNum++;
    }

    if(u1_s_XspiIviSub0DidBuf < (U1)DIAGAPP_SID22_DID_MAXNUM) {
        u1_s_XspiIviSub0DidBuf++;
    }

    if(u1_s_XspiIviSub0DidBuf == u1_s_XspiIviSub0DidNum) {
        vd_s_XspiIviSub0SID22Response();
    } else {
        vd_s_XspiIviSub0Request_OPC2205();
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_XspiIviSub0Response_OPC2206(const U1 * u1_ap_DATA)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID22 OPC2206 Response                                                                                           */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_XspiIviSub0Response_OPC2206(const U1 * u1_ap_DATA)
{
    u1_sp_XspiIviSub0DidResultChk[u1_s_XspiIviSub0DidBuf] = u1_ap_DATA[2];

    if(u1_sp_XspiIviSub0DidResultChk[u1_s_XspiIviSub0DidBuf] == (U1)E_OK) {
        vd_s_XspiIviSub0Request_OPC2201();
    } else {
        if(u1_s_XspiIviSub0DidBuf < (U1)DIAGAPP_SID22_DID_MAXNUM) {
            u1_s_XspiIviSub0DidBuf++;
        }
        if(u1_s_XspiIviSub0DidBuf == u1_s_XspiIviSub0DidNum) {
            vd_s_XspiIviSub0SID22Response();
        } else {
            vd_s_XspiIviSub0Request_OPC2205();
        }
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_XspiIviSub0SID22Response(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID22 OPC2206 Response                                                                                           */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_XspiIviSub0SID22Response(void)
{
    vd_g_DiagAppResponse_Sid22(u1_s_XspiIviSub0DidNum,&st_sp_XspiIviSub0DiagSid22Did[0],&u1_sp_XspiIviSub0DidResultChk[0]);
    vd_g_XspiIviSub0SID22Init();
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    07/31/2025  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
