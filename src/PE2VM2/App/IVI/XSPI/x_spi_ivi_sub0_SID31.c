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
#define XSPI_IVI_SUB0_SID31_C_MAJOR                   (0)
#define XSPI_IVI_SUB0_SID31_C_MINOR                   (0)
#define XSPI_IVI_SUB0_SID31_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub0_private.h"
#include    "x_spi_ivi_sub0_SID31.h"
#include    "DiagApp.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB0_SID31_C_MAJOR != XSPI_IVI_SUB0_SID31_H_MAJOR) || \
     (XSPI_IVI_SUB0_SID31_C_MINOR != XSPI_IVI_SUB0_SID31_H_MINOR) || \
     (XSPI_IVI_SUB0_SID31_C_PATCH != XSPI_IVI_SUB0_SID31_H_PATCH))
#error "x_spi_ivi_sub0_SID31.c and x_spi_ivi_sub0_SID31.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SID31_OPC_3101         (0x3101U)
#define XSPI_IVI_SID31_OPC_3102         (0x3102U)
#define XSPI_IVI_SID31_OPC_3103         (0x3103U)
#define XSPI_IVI_SID31_OPC_3104         (0x3104U)
#define XSPI_IVI_SID31_OPC_3105         (0x3105U)
#define XSPI_IVI_SID31_OPC_3106         (0x3106U)

#define XSPI_IVI_DIAG_REQ_NONDATA_SIZE  (6U)
#define XSPI_IVI_DIAG_REQ_DATA_MAX_SIZE (XSPI_IVI_DIAG_MAX_SIZE - XSPI_IVI_DIAG_REQ_NONDATA_SIZE)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_XspiIviSub0Response_OPC3102(const U1 * u1_ap_DATA );
static void     vd_s_XspiIviSub0Response_OPC3104(const U1 * u1_ap_DATA );
static void     vd_s_XspiIviSub0Response_OPC3106(const U1 * u1_ap_DATA );
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0SID31Init(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub0SID31Init(void)
{
}

/*===================================================================================================================================*/
/*  U1          u1_g_XspiIviSub0Request_Sid31sf01(const U1 u1_a_REQID, const U2 u2_a_RID,const U2 u2_a_DTLEN,                        */
/*                                                const U1 * u1_ap_DATA, U1 * u1_ap_NegativeResponseCode)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID31 Request                                                                                                    */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_Sid31sf01(const U1 u1_a_REQID, const U2 u2_a_RID,const U2 u2_a_DTLEN,
                                             const U1 * u1_ap_DATA, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U2  u2_t_dtlen;
    U1  u1_tp_data[XSPI_IVI_DIAG_MAX_SIZE];

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
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID31_OPC_3101 >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID31_OPC_3101 & 0x00FFU);
        u1_tp_data[2] = (U1)((u2_a_RID >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[3] = (U1)(u2_a_RID & 0x00FFU);
        u1_tp_data[4] = (U1)((u2_a_DTLEN >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[5] = (U1)(u2_a_DTLEN & 0x00FFU);
        if(u2_a_DTLEN <= (U2)XSPI_IVI_DIAG_REQ_DATA_MAX_SIZE) {
            vd_g_MemcpyU1(&u1_tp_data[6], &u1_ap_DATA[0], (U4)u2_a_DTLEN);
            u2_t_dtlen = u2_a_DTLEN + (U2)XSPI_IVI_DIAG_REQ_NONDATA_SIZE;
            vd_g_XspiIviSub0Request(u2_t_dtlen,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID31);
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1          u1_g_XspiIviSub0Request_Sid31sf02(const U1 u1_a_REQID, const U2 u2_a_RID,const U2 u2_a_DTLEN,                        */
/*                                                const U1 * u1_ap_DATA, U1 * u1_ap_NegativeResponseCode)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID31 Request                                                                                                    */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_Sid31sf02(const U1 u1_a_REQID, const U2 u2_a_RID,const U2 u2_a_DTLEN,
                                             const U1 * u1_ap_DATA, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U2  u2_t_dtlen;
    U1  u1_tp_data[XSPI_IVI_DIAG_MAX_SIZE];

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
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID31_OPC_3103 >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID31_OPC_3103 & 0x00FFU);
        u1_tp_data[2] = (U1)((u2_a_RID >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[3] = (U1)(u2_a_RID & 0x00FFU);
        u1_tp_data[4] = (U1)((u2_a_DTLEN >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[5] = (U1)(u2_a_DTLEN & 0x00FFU);
        if(u2_a_DTLEN <= (U2)XSPI_IVI_DIAG_REQ_DATA_MAX_SIZE) {
            vd_g_MemcpyU1(&u1_tp_data[6], &u1_ap_DATA[0], (U4)u2_a_DTLEN);
            u2_t_dtlen = u2_a_DTLEN + (U2)XSPI_IVI_DIAG_REQ_NONDATA_SIZE;
            vd_g_XspiIviSub0Request(u2_t_dtlen,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID31);
        }
        
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1          u1_g_XspiIviSub0Request_Sid31sf03(const U1 u1_a_REQID, const U2 u2_a_RID,const U2 u2_a_DTLEN,                        */
/*                                                const U1 * u1_ap_DATA, U1 * u1_ap_NegativeResponseCode)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID31 Request                                                                                                    */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_Sid31sf03(const U1 u1_a_REQID, const U2 u2_a_RID,const U2 u2_a_DTLEN,
                                             const U1 * u1_ap_DATA, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U2  u2_t_dtlen;
    U1  u1_tp_data[XSPI_IVI_DIAG_MAX_SIZE];

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
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID31_OPC_3105 >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID31_OPC_3105 & 0x00FFU);
        u1_tp_data[2] = (U1)((u2_a_RID >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[3] = (U1)(u2_a_RID & 0x00FFU);
        u1_tp_data[4] = (U1)((u2_a_DTLEN >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[5] = (U1)(u2_a_DTLEN & 0x00FFU);
        if(u2_a_DTLEN <= (U2)XSPI_IVI_DIAG_REQ_DATA_MAX_SIZE) {
            vd_g_MemcpyU1(&u1_tp_data[6], &u1_ap_DATA[0], (U4)u2_a_DTLEN);
            u2_t_dtlen = u2_a_DTLEN + (U2)XSPI_IVI_DIAG_REQ_NONDATA_SIZE;
            vd_g_XspiIviSub0Request(u2_t_dtlen,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID31);
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void         vd_g_XspiIviSub0Response_SID31(const U1 * u1_ap_DATA)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void         vd_g_XspiIviSub0Response_SID31(const U1 * u1_ap_DATA)
{
    U2  u2_t_opc;

    u2_t_opc = (U2)((u1_ap_DATA[0] << XSPI_IVI_SFT_08) | u1_ap_DATA[1]);

    switch(u2_t_opc) {
        case XSPI_IVI_SID31_OPC_3102:
            vd_s_XspiIviSub0Response_OPC3102(&u1_ap_DATA[2]);
            break;
        case XSPI_IVI_SID31_OPC_3104:
            vd_s_XspiIviSub0Response_OPC3104(&u1_ap_DATA[2]);
            break;
        case XSPI_IVI_SID31_OPC_3106:
            vd_s_XspiIviSub0Response_OPC3106(&u1_ap_DATA[2]);
            break;
        default:
            break;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_XspiIviSub0Response_OPC3102(const U1 * u1_ap_DATA )                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID31 OPC3102 Response                                                                                           */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_XspiIviSub0Response_OPC3102(const U1 * u1_ap_DATA )
{
    U1  u1_t_nrc;
    U2  u2_t_rid;
    U2  u2_t_len;
    U1  u1_t_routininfo;

    u1_t_nrc = u1_ap_DATA[0];
    u2_t_rid = (U2)((u1_ap_DATA[1] << XSPI_IVI_SFT_08) | u1_ap_DATA[2]);
    u2_t_len = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);
    u1_t_routininfo = u1_ap_DATA[5];

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid31sf01(u2_t_rid, u2_t_len, u1_t_routininfo, &u1_ap_DATA[6], u1_t_nrc);
    } else {
        vd_g_DiagAppResponse_Sid31sf01(u2_t_rid, u2_t_len, u1_t_routininfo, vdp_PTR_NA, u1_t_nrc);
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_XspiIviSub0Response_OPC3104(const U1 * u1_ap_DATA )                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID31 OPC3104 Response                                                                                           */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_XspiIviSub0Response_OPC3104(const U1 * u1_ap_DATA )
{
    U1  u1_t_nrc;
    U2  u2_t_rid;
    U2  u2_t_len;
    U1  u1_t_routininfo;

    u1_t_nrc = u1_ap_DATA[0];
    u2_t_rid = (U2)((u1_ap_DATA[1] << XSPI_IVI_SFT_08) | u1_ap_DATA[2]);
    u2_t_len = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);
    u1_t_routininfo = u1_ap_DATA[5];

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid31sf02(u2_t_rid, u2_t_len, u1_t_routininfo, &u1_ap_DATA[6], u1_t_nrc);
    } else {
        vd_g_DiagAppResponse_Sid31sf02(u2_t_rid, u2_t_len, u1_t_routininfo, vdp_PTR_NA, u1_t_nrc);
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_XspiIviSub0Response_OPC3106(const U1 * u1_ap_DATA )                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID31 OPC3106 Response                                                                                           */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_XspiIviSub0Response_OPC3106(const U1 * u1_ap_DATA )
{
    U1  u1_t_nrc;
    U2  u2_t_rid;
    U2  u2_t_len;
    U1  u1_t_routininfo;

    u1_t_nrc = u1_ap_DATA[0];
    u2_t_rid = (U2)((u1_ap_DATA[1] << XSPI_IVI_SFT_08) | u1_ap_DATA[2]);
    u2_t_len = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);
    u1_t_routininfo = u1_ap_DATA[5];

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid31sf03(u2_t_rid, u2_t_len, u1_t_routininfo, &u1_ap_DATA[6], u1_t_nrc);
    } else {
        vd_g_DiagAppResponse_Sid31sf03(u2_t_rid, u2_t_len, u1_t_routininfo, vdp_PTR_NA, u1_t_nrc);
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
/*  0.0.0    08/08/2025  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
