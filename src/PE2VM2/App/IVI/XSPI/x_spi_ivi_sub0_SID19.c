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
#define XSPI_IVI_SUB0_SID19_C_MAJOR                   (0)
#define XSPI_IVI_SUB0_SID19_C_MINOR                   (0)
#define XSPI_IVI_SUB0_SID19_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub0_private.h"
#include    "x_spi_ivi_sub0_SID19.h"
#include    "DiagApp.h"
#include    "DiagApp_SID19.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB0_SID19_C_MAJOR != XSPI_IVI_SUB0_SID19_H_MAJOR) || \
     (XSPI_IVI_SUB0_SID19_C_MINOR != XSPI_IVI_SUB0_SID19_H_MINOR) || \
     (XSPI_IVI_SUB0_SID19_C_PATCH != XSPI_IVI_SUB0_SID19_H_PATCH))
#error "x_spi_ivi_sub0_SID19.c and x_spi_ivi_sub0_SID19.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SID19_OPC_1901         (0x1901U)
#define XSPI_IVI_SID19_OPC_1902         (0x1902U)
#define XSPI_IVI_SID19_OPC_1903         (0x1903U)
#define XSPI_IVI_SID19_OPC_1904         (0x1904U)
#define XSPI_IVI_SID19_OPC_1905         (0x1905U)
#define XSPI_IVI_SID19_OPC_1906         (0x1906U)
#define XSPI_IVI_SID19_OPC_1907         (0x1907U)
#define XSPI_IVI_SID19_OPC_1908         (0x1908U)
#define XSPI_IVI_SID19_OPC_190D         (0x190DU)
#define XSPI_IVI_SID19_OPC_190E         (0x190EU)
#define XSPI_IVI_SID19_OPC_190F         (0x190FU)
#define XSPI_IVI_SID19_OPC_1910         (0x1910U)
#define XSPI_IVI_SID19_OPC_1911         (0x1911U)
#define XSPI_IVI_SID19_OPC_1912         (0x1912U)
#define XSPI_IVI_SID19_OPC_1913         (0x1913U)
#define XSPI_IVI_SID19_OPC_1914         (0x1914U)

#define XSPI_IVI_DIAG_1901_SIZE         (3U)
#define XSPI_IVI_DIAG_1903_SIZE         (2U)
#define XSPI_IVI_DIAG_1905_SIZE         (6U)
#define XSPI_IVI_DIAG_1907_SIZE         (6U)
#define XSPI_IVI_DIAG_190D_SIZE         (4U)
#define XSPI_IVI_DIAG_190F_SIZE         (7U)
#define XSPI_IVI_DIAG_1911_SIZE         (7U)
#define XSPI_IVI_DIAG_1913_SIZE         (3U)

#define XSPI_IVI_DIAG_1902_DATA_OFFSET  (1U)
#define XSPI_IVI_DIAG_1904_DATA_OFFSET  (0U)
#define XSPI_IVI_DIAG_1906_DATA_OFFSET  (4U)
#define XSPI_IVI_DIAG_1908_DATA_OFFSET  (4U)
#define XSPI_IVI_DIAG_190E_DATA_OFFSET  (2U)
#define XSPI_IVI_DIAG_1910_DATA_OFFSET  (5U)
#define XSPI_IVI_DIAG_1912_DATA_OFFSET  (5U)
#define XSPI_IVI_DIAG_1914_DATA_OFFSET  (2U)
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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void         vd_s_XspiIviSub0Response_SID19sf02(const U1 * u1_ap_DATA);
static void         vd_s_XspiIviSub0Response_SID19sf03(const U1 * u1_ap_DATA);
static void         vd_s_XspiIviSub0Response_SID19sf04(const U1 * u1_ap_DATA);
static void         vd_s_XspiIviSub0Response_SID19sf06(const U1 * u1_ap_DATA);
static void         vd_s_XspiIviSub0Response_SID19sf17(const U1 * u1_ap_DATA);
static void         vd_s_XspiIviSub0Response_SID19sf18(const U1 * u1_ap_DATA);
static void         vd_s_XspiIviSub0Response_SID19sf19(const U1 * u1_ap_DATA);
static void         vd_s_XspiIviSub0Response_SID19sf1A(const U1 * u1_ap_DATA);
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0SID19Init(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub0SID19Init(void)
{
}

/*===================================================================================================================================*/
/*  U1          u1_g_XspiIviSub0Request_SID19sf02(const U1 u1_a_REQID, const U1 u1_a_DTCSTSMASK, U1 * u1_ap_NegativeResponseCode)    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID19 SubFunction02 Request                                                                                      */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_SID19sf02(const U1 u1_a_REQID, const U1 u1_a_DTCSTSMASK, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U1  u1_tp_data[XSPI_IVI_DIAG_1901_SIZE];
    U2  u2_t_datalength;

    u1_t_ret = (U1)E_OK;
    u2_t_datalength = (U2)XSPI_IVI_DIAG_1901_SIZE;
    u1_t_power_sts = u1_g_VehopemdIgnOn();
    u1_t_oscom_chk = u1_g_XspiIviSub0OSComBridge();

    if(u1_t_power_sts == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else if(u1_t_oscom_chk == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else {
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID19_OPC_1901 >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID19_OPC_1901 & 0x00FFU);
        u1_tp_data[2] = u1_a_DTCSTSMASK;
        vd_g_XspiIviSub0Request(u2_t_datalength,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID19);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1          u1_g_XspiIviSub0Request_SID19sf03(const U1 u1_a_REQID, U1 * u1_ap_NegativeResponseCode)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID19 SubFunction03 Request                                                                                      */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_SID19sf03(const U1 u1_a_REQID, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U1  u1_tp_data[XSPI_IVI_DIAG_1903_SIZE];
    U2  u2_t_datalength;

    u1_t_ret = (U1)E_OK;
    u2_t_datalength = (U2)XSPI_IVI_DIAG_1903_SIZE;
    u1_t_power_sts = u1_g_VehopemdIgnOn();
    u1_t_oscom_chk = u1_g_XspiIviSub0OSComBridge();

    if(u1_t_power_sts == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else if(u1_t_oscom_chk == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else {
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID19_OPC_1903 >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID19_OPC_1903 & 0x00FFU);
        vd_g_XspiIviSub0Request(u2_t_datalength,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID19);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* U1          u1_g_XspiIviSub0Request_SID19sf04(const U1 u1_a_REQID, const U4 u4_a_MASKREC,                                         */
/*                                             const U1 u1_a_SSRECNUM, U1 * u1_ap_NegativeResponseCode)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID19 SubFunction04 Request                                                                                      */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_SID19sf04(const U1 u1_a_REQID, const U4 u4_a_MASKREC,
                                             const U1 u1_a_SSRECNUM, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U1  u1_tp_data[XSPI_IVI_DIAG_1905_SIZE];
    U2  u2_t_datalength;

    u1_t_ret = (U1)E_OK;
    u2_t_datalength = (U2)XSPI_IVI_DIAG_1905_SIZE;
    u1_t_power_sts = u1_g_VehopemdIgnOn();
    u1_t_oscom_chk = u1_g_XspiIviSub0OSComBridge();

    if(u1_t_power_sts == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else if(u1_t_oscom_chk == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else {
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID19_OPC_1905 >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID19_OPC_1905 & 0x00FFU);
        u1_tp_data[2] = (U1)((u4_a_MASKREC >> XSPI_IVI_SFT_16) & 0x000000FFU);
        u1_tp_data[3] = (U1)((u4_a_MASKREC >> XSPI_IVI_SFT_08) & 0x000000FFU);
        u1_tp_data[4] = (U1)(u4_a_MASKREC & 0x000000FFU);
        u1_tp_data[5] = u1_a_SSRECNUM;
        vd_g_XspiIviSub0Request(u2_t_datalength,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID19);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* U1          u1_g_XspiIviSub0Request_SID19sf06(const U1 u1_a_REQID, const U4 u4_a_MASKREC,                                         */
/*                                             const U1 u1_a_EXRECNUM, U1 * u1_ap_NegativeResponseCode)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID19 SubFunction06 Request                                                                                      */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_SID19sf06(const U1 u1_a_REQID, const U4 u4_a_MASKREC,
                                             const U1 u1_a_EXRECNUM, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U1  u1_tp_data[XSPI_IVI_DIAG_1907_SIZE];
    U2  u2_t_datalength;

    u1_t_ret = (U1)E_OK;
    u2_t_datalength = (U2)XSPI_IVI_DIAG_1907_SIZE;
    u1_t_power_sts = u1_g_VehopemdIgnOn();
    u1_t_oscom_chk = u1_g_XspiIviSub0OSComBridge();

    if(u1_t_power_sts == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else if(u1_t_oscom_chk == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else {
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID19_OPC_1907 >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID19_OPC_1907 & 0x00FFU);
        u1_tp_data[2] = (U1)((u4_a_MASKREC >> XSPI_IVI_SFT_16) & 0x000000FFU);
        u1_tp_data[3] = (U1)((u4_a_MASKREC >> XSPI_IVI_SFT_08) & 0x000000FFU);
        u1_tp_data[4] = (U1)(u4_a_MASKREC & 0x000000FFU);
        u1_tp_data[5] = u1_a_EXRECNUM;
        vd_g_XspiIviSub0Request(u2_t_datalength,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID19);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* U1          u1_g_XspiIviSub0Request_SID19sf17(const U1 u1_a_REQID, const U1 u1_a_DTCSTSMASK,                                      */
/*                                             const U1 u1_a_MEMSEL, U1 * u1_ap_NegativeResponseCode)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID19 SubFunction17 Request                                                                                      */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_SID19sf17(const U1 u1_a_REQID, const U1 u1_a_DTCSTSMASK,
                                             const U1 u1_a_MEMSEL, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U1  u1_tp_data[XSPI_IVI_DIAG_190D_SIZE];
    U2  u2_t_datalength;

    u1_t_ret = (U1)E_OK;
    u2_t_datalength = (U2)XSPI_IVI_DIAG_190D_SIZE;
    u1_t_power_sts = u1_g_VehopemdIgnOn();
    u1_t_oscom_chk = u1_g_XspiIviSub0OSComBridge();

    if(u1_t_power_sts == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else if(u1_t_oscom_chk == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else {
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID19_OPC_190D >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID19_OPC_190D & 0x00FFU);
        u1_tp_data[2] = u1_a_DTCSTSMASK;
        u1_tp_data[3] = u1_a_MEMSEL;
        vd_g_XspiIviSub0Request(u2_t_datalength,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID19);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* U1          u1_g_XspiIviSub0Request_SID19sf18(const U1 u1_a_REQID, const U4 u4_a_MASKREC, const U1 u1_a_SSRNUM,                   */
/*                                             const U1 u1_a_MEMSEL, U1 * u1_ap_NegativeResponseCode)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID19 SubFunction18 Request                                                                                      */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_SID19sf18(const U1 u1_a_REQID, const U4 u4_a_MASKREC, const U1 u1_a_SSRNUM,
                                             const U1 u1_a_MEMSEL, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U1  u1_tp_data[XSPI_IVI_DIAG_190F_SIZE];
    U2  u2_t_datalength;

    u1_t_ret = (U1)E_OK;
    u2_t_datalength = (U2)XSPI_IVI_DIAG_190F_SIZE;
    u1_t_power_sts = u1_g_VehopemdIgnOn();
    u1_t_oscom_chk = u1_g_XspiIviSub0OSComBridge();

    if(u1_t_power_sts == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else if(u1_t_oscom_chk == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else {
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID19_OPC_190F >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID19_OPC_190F & 0x00FFU);
        u1_tp_data[2] = (U1)((u4_a_MASKREC >> XSPI_IVI_SFT_16) & 0x000000FFU);
        u1_tp_data[3] = (U1)((u4_a_MASKREC >> XSPI_IVI_SFT_08) & 0x000000FFU);
        u1_tp_data[4] = (U1)(u4_a_MASKREC & 0x000000FFU);
        u1_tp_data[5] = u1_a_SSRNUM;
        u1_tp_data[6] = u1_a_MEMSEL;
        vd_g_XspiIviSub0Request(u2_t_datalength,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID19);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/* U1          u1_g_XspiIviSub0Request_SID19sf19(const U1 u1_a_REQID, const U4 u4_a_MASKREC, const U1 u1_a_EXRECNUM,                 */
/*                                             const U1 u1_a_MEMSEL, U1 * u1_ap_NegativeResponseCode)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID19 SubFunction19 Request                                                                                      */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_SID19sf19(const U1 u1_a_REQID, const U4 u4_a_MASKREC, const U1 u1_a_EXRECNUM,
                                             const U1 u1_a_MEMSEL, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U1  u1_tp_data[XSPI_IVI_DIAG_1911_SIZE];
    U2  u2_t_datalength;

    u1_t_ret = (U1)E_OK;
    u2_t_datalength = (U2)XSPI_IVI_DIAG_1911_SIZE;
    u1_t_power_sts = u1_g_VehopemdIgnOn();
    u1_t_oscom_chk = u1_g_XspiIviSub0OSComBridge();

    if(u1_t_power_sts == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else if(u1_t_oscom_chk == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else {
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID19_OPC_1911 >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID19_OPC_1911 & 0x00FFU);
        u1_tp_data[2] = (U1)((u4_a_MASKREC >> XSPI_IVI_SFT_16) & 0x000000FFU);
        u1_tp_data[3] = (U1)((u4_a_MASKREC >> XSPI_IVI_SFT_08) & 0x000000FFU);
        u1_tp_data[4] = (U1)(u4_a_MASKREC & 0x000000FFU);
        u1_tp_data[5] = u1_a_EXRECNUM;
        u1_tp_data[6] = u1_a_MEMSEL;
        vd_g_XspiIviSub0Request(u2_t_datalength,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID19);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1          u1_g_XspiIviSub0Request_SID19sf1A(const U1 u1_a_REQID, const U1 u1_a_EXRECNUM, U1 * u1_ap_NegativeResponseCode)      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SID19 SubFunction1A Request                                                                                      */
/*  Arguments:                                                                                                                       */
/*  Return:         u1_t_ret : positive or negative response                                                                         */
/*===================================================================================================================================*/
U1          u1_g_XspiIviSub0Request_SID19sf1A(const U1 u1_a_REQID, const U1 u1_a_EXRECNUM, U1 * u1_ap_NegativeResponseCode)
{
    U1  u1_t_ret;
    U1  u1_t_power_sts;
    U1  u1_t_oscom_chk;
    U1  u1_tp_data[XSPI_IVI_DIAG_1913_SIZE];
    U2  u2_t_datalength;

    u1_t_ret = (U1)E_OK;
    u2_t_datalength = (U2)XSPI_IVI_DIAG_1913_SIZE;
    u1_t_power_sts = u1_g_VehopemdIgnOn();
    u1_t_oscom_chk = u1_g_XspiIviSub0OSComBridge();

    if(u1_t_power_sts == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else if(u1_t_oscom_chk == (U1)FALSE) {
        *u1_ap_NegativeResponseCode = (U1)OXDC_SAL_PROC_NR_31;
        u1_t_ret = (U1)E_NOT_OK;
    } else {
        u1_tp_data[0] = (U1)(((U2)XSPI_IVI_SID19_OPC_1913 >> XSPI_IVI_SFT_08) & 0x00FFU);
        u1_tp_data[1] = ((U1)XSPI_IVI_SID19_OPC_1913 & 0x00FFU);
        u1_tp_data[2] = u1_a_EXRECNUM;
        vd_g_XspiIviSub0Request(u2_t_datalength,u1_a_REQID,u1_tp_data,(U1)XSPI_IVI_SID19);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0Response_SID19(const U1 * u1_ap_DATA)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void         vd_g_XspiIviSub0Response_SID19(const U1 * u1_ap_DATA)
{
    U2  u2_t_OPC;

    u2_t_OPC = (U2)((u1_ap_DATA[0] << XSPI_IVI_SFT_08) | u1_ap_DATA[1]);

    switch(u2_t_OPC) {
        case XSPI_IVI_SID19_OPC_1902:
            vd_s_XspiIviSub0Response_SID19sf02(&u1_ap_DATA[0]);
            break;
        case XSPI_IVI_SID19_OPC_1904:
            vd_s_XspiIviSub0Response_SID19sf03(&u1_ap_DATA[0]);
            break;
        case XSPI_IVI_SID19_OPC_1906:
            vd_s_XspiIviSub0Response_SID19sf04(&u1_ap_DATA[0]);
            break;
        case XSPI_IVI_SID19_OPC_1908:
            vd_s_XspiIviSub0Response_SID19sf06(&u1_ap_DATA[0]);
            break;
        case XSPI_IVI_SID19_OPC_190E:
            vd_s_XspiIviSub0Response_SID19sf17(&u1_ap_DATA[0]);
            break;
        case XSPI_IVI_SID19_OPC_1910:
            vd_s_XspiIviSub0Response_SID19sf18(&u1_ap_DATA[0]);
            break;
        case XSPI_IVI_SID19_OPC_1912:
            vd_s_XspiIviSub0Response_SID19sf19(&u1_ap_DATA[0]);
            break;
        case XSPI_IVI_SID19_OPC_1914:
            vd_s_XspiIviSub0Response_SID19sf1A(&u1_ap_DATA[0]);
            break;
        default:
            break;
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0Response_SID19sf02(const U1 * u1_ap_DATA)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0Response_SID19sf02(const U1 * u1_ap_DATA)
{
    U1  u1_t_nrc;
    U2  u2_t_dtlen;
    U1  u1_t_dtcmask;

    u1_t_nrc = u1_ap_DATA[2];
    u2_t_dtlen = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);
    u1_t_dtcmask = u1_ap_DATA[5];

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid19sf02(u1_t_nrc,u2_t_dtlen,u1_t_dtcmask,&u1_ap_DATA[6]);
    } else {
        vd_g_DiagAppResponse_Sid19sf02(u1_t_nrc,u2_t_dtlen,u1_t_dtcmask,vdp_PTR_NA);
    }
    
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0Response_SID19sf03(const U1 * u1_ap_DATA)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0Response_SID19sf03(const U1 * u1_ap_DATA)
{
    U1  u1_t_nrc;
    U2  u2_t_dtlen;

    u1_t_nrc = u1_ap_DATA[2];
    u2_t_dtlen = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid19sf03(u1_t_nrc,u2_t_dtlen,&u1_ap_DATA[5]);
    } else {
        vd_g_DiagAppResponse_Sid19sf03(u1_t_nrc,u2_t_dtlen,vdp_PTR_NA);
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0Response_SID19sf04(const U1 * u1_ap_DATA)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0Response_SID19sf04(const U1 * u1_ap_DATA)
{
    U1  u1_t_nrc;
    U2  u2_t_dtlen;
    U4  u4_t_dtc;
    U1  u1_t_dtcsts;


    u1_t_nrc = u1_ap_DATA[2];
    u2_t_dtlen = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);
    u4_t_dtc = (U4)((u1_ap_DATA[5] << XSPI_IVI_SFT_16) | (u1_ap_DATA[6] << XSPI_IVI_SFT_08) | u1_ap_DATA[7]);
    u1_t_dtcsts = u1_ap_DATA[8];

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid19sf04(u1_t_nrc,u2_t_dtlen,u4_t_dtc,u1_t_dtcsts,&u1_ap_DATA[9]);
    } else {
        vd_g_DiagAppResponse_Sid19sf04(u1_t_nrc,u2_t_dtlen,u4_t_dtc,u1_t_dtcsts,vdp_PTR_NA);
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0Response_SID19sf06(const U1 * u1_ap_DATA)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0Response_SID19sf06(const U1 * u1_ap_DATA)
{
    U1  u1_t_nrc;
    U2  u2_t_dtlen;
    U4  u4_t_dtc;
    U1  u1_t_dtcsts;

    u1_t_nrc = u1_ap_DATA[2];
    u2_t_dtlen = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);
    u4_t_dtc = (U4)((u1_ap_DATA[5] << XSPI_IVI_SFT_16) | (u1_ap_DATA[6] << XSPI_IVI_SFT_08) | u1_ap_DATA[7]);
    u1_t_dtcsts = u1_ap_DATA[8];

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid19sf06(u1_t_nrc,u2_t_dtlen,u4_t_dtc,u1_t_dtcsts,&u1_ap_DATA[9]);
    } else {
        vd_g_DiagAppResponse_Sid19sf06(u1_t_nrc,u2_t_dtlen,u4_t_dtc,u1_t_dtcsts,vdp_PTR_NA);
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0Response_SID19sf17(const U1 * u1_ap_DATA)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0Response_SID19sf17(const U1 * u1_ap_DATA)
{
    U1  u1_t_nrc;
    U2  u2_t_dtlen;
    U1  u1_t_memsel;
    U1  u1_t_dtcmsk;

    u1_t_nrc = u1_ap_DATA[2];
    u2_t_dtlen = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);
    u1_t_memsel = u1_ap_DATA[5];
    u1_t_dtcmsk = u1_ap_DATA[6];

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid19sf17(u1_t_nrc,u2_t_dtlen,u1_t_memsel,u1_t_dtcmsk,&u1_ap_DATA[7]);
    } else {
        vd_g_DiagAppResponse_Sid19sf17(u1_t_nrc,u2_t_dtlen,u1_t_memsel,u1_t_dtcmsk,vdp_PTR_NA);
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0Response_SID19sf18(const U1 * u1_ap_DATA)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0Response_SID19sf18(const U1 * u1_ap_DATA)
{
    U1  u1_t_nrc;
    U2  u2_t_dtlen;
    U1  u1_t_memsel;
    U4  u4_t_dtc;
    U1  u1_t_dtcsts;

    u1_t_nrc = u1_ap_DATA[2];
    u2_t_dtlen = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);
    u1_t_memsel = u1_ap_DATA[5];
    u4_t_dtc = (U4)((u1_ap_DATA[6] << XSPI_IVI_SFT_16) | (u1_ap_DATA[7] << XSPI_IVI_SFT_08) | u1_ap_DATA[8]);
    u1_t_dtcsts = u1_ap_DATA[9];

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid19sf18(u1_t_nrc,u2_t_dtlen,u1_t_memsel,u4_t_dtc,u1_t_dtcsts,&u1_ap_DATA[10]);
    } else {
        vd_g_DiagAppResponse_Sid19sf18(u1_t_nrc,u2_t_dtlen,u1_t_memsel,u4_t_dtc,u1_t_dtcsts,vdp_PTR_NA);
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0Response_SID19sf19(const U1 * u1_ap_DATA)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0Response_SID19sf19(const U1 * u1_ap_DATA)
{
    U1  u1_t_nrc;
    U2  u2_t_dtlen;
    U1  u1_t_memsel;
    U4  u4_t_dtc;
    U1  u1_t_dtcsts;

    u1_t_nrc = u1_ap_DATA[2];
    u2_t_dtlen = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);
    u1_t_memsel = u1_ap_DATA[5];
    u4_t_dtc = (U4)((u1_ap_DATA[6] << XSPI_IVI_SFT_16) | (u1_ap_DATA[7] << XSPI_IVI_SFT_08) | u1_ap_DATA[8]);
    u1_t_dtcsts = u1_ap_DATA[9];

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid19sf19(u1_t_nrc,u2_t_dtlen,u1_t_memsel,u4_t_dtc,u1_t_dtcsts,&u1_ap_DATA[10]);
    } else {
        vd_g_DiagAppResponse_Sid19sf19(u1_t_nrc,u2_t_dtlen,u1_t_memsel,u4_t_dtc,u1_t_dtcsts,vdp_PTR_NA);
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0Response_SID19sf1A(const U1 * u1_ap_DATA)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_DATA : SubFlame0 Data                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0Response_SID19sf1A(const U1 * u1_ap_DATA)
{
    U1  u1_t_nrc;
    U2  u2_t_dtlen;
    U1  u1_t_stsmsk;
    U1  u1_t_exrecnum;

    u1_t_nrc = u1_ap_DATA[2];
    u2_t_dtlen = (U2)((u1_ap_DATA[3] << XSPI_IVI_SFT_08) | u1_ap_DATA[4]);
    u1_t_stsmsk = u1_ap_DATA[5];
    u1_t_exrecnum = u1_ap_DATA[6];

    if(u1_t_nrc == (U1)XSPI_IVI_POSITIVE_RES) {
        vd_g_DiagAppResponse_Sid19sf1A(u1_t_nrc,u2_t_dtlen,u1_t_stsmsk,u1_t_exrecnum,&u1_ap_DATA[7]);
    } else {
        vd_g_DiagAppResponse_Sid19sf1A(u1_t_nrc,u2_t_dtlen,u1_t_stsmsk,u1_t_exrecnum,vdp_PTR_NA);
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
/*  0.0.0    07/29/2025  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
