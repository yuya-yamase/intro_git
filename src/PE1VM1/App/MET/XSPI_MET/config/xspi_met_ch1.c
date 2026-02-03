/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Local Communication SPI                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_CH1_C_MAJOR                     (0U)
#define XSPI_CH1_C_MINOR                     (0U)
#define XSPI_CH1_C_PATCH                     (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "xspi_met.h"
#include "xspi_met_ch1.h"

#include "cantxapp_mettx.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_CH1_C_MAJOR != XSPI_CFG_H_MAJOR) || \
     (XSPI_CH1_C_MINOR != XSPI_CFG_H_MINOR) || \
     (XSPI_CH1_C_PATCH != XSPI_CFG_H_PATCH))
#error "xspi_ch1.c and xspi_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((XSPI_CH1_C_MAJOR != XSPI_CH_H_MAJOR) || \
     (XSPI_CH1_C_MINOR != XSPI_CH_H_MINOR) || \
     (XSPI_CH1_C_PATCH != XSPI_CH_H_PATCH))
#error "xspi_ch1.c and xspi_ch_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_XSPI_MET_READ__BIT(u4_buf , u1_pos , u1_len) ((U1)((U1)((u4_buf)  >> (u1_pos)) & (U1)((1U << (u1_len)) - 1U)))
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline void    vd_s_XSpiCanTx_AVN1S03(const U4* u4_ap_tx_data);
static inline void    vd_s_XSpiCanTx_MET1S02(const U4* u4_ap_tx_data);
static inline void    vd_s_XSpiCanTx_MET1S27(const U4* u4_ap_tx_data);
static inline void    vd_s_XSpiCanTx_MET1S29(const U4* u4_ap_tx_data);
static inline void    vd_s_XSpiCanTx_MET1S30(const U4* u4_ap_tx_data);
static inline void    vd_s_XSpiCanTx_MET1S62(const U4* u4_ap_tx_data);
static inline void    vd_s_XSpiCanTx_MET1S70(const U4* u4_ap_tx_data);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_XSpiCfgInitCh1(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCfgInitCh1(void)
{
}

/*===================================================================================================================================*/
/*  void    vd_g_XSpiCfgPduRxCh1(const U4 * u4_ap_PDU_RX)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCfgPduRxCh1(const U4 * u4_ap_PDU_RX)
{
    vd_s_XSpiCanTx_AVN1S03(&u4_ap_PDU_RX[47]);
    vd_s_XSpiCanTx_MET1S02(&u4_ap_PDU_RX[69]);
    vd_s_XSpiCanTx_MET1S27(&u4_ap_PDU_RX[21]);
    vd_s_XSpiCanTx_MET1S29(&u4_ap_PDU_RX[23]);
    vd_s_XSpiCanTx_MET1S30(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_MET1S62(&u4_ap_PDU_RX[37]);
    vd_s_XSpiCanTx_MET1S70(&u4_ap_PDU_RX[39]);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Rx Functions                                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_AVN1S03(const U4 * u4_ap_tx_data)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_tx_data                                                                                                     */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_AVN1S03(const U4 * u4_ap_tx_data)
{
    U1 u1_t_txsts;

    u1_t_txsts = u1_g_XSpiMETRxRdAccessSts((U1)XSPI_MET_XSPI_RX_AGLBE);

    if (u1_t_txsts == (U1)XSPI_MET_XSPI_RX_READ_VALID) {
        vd_g_CanTxAppAVN1S03_Put(&u4_ap_tx_data[0], (U1)XSPI_CANTX_BUFSIZE8);
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_MET1S02(const U4 * u4_ap_tx_data)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_tx_data                                                                                                     */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_MET1S02(const U4 * u4_ap_tx_data)
{
    U1 u1_t_txsts;

    u1_t_txsts = u1_g_XSpiMETRxRdAccessSts((U1)XSPI_MET_XSPI_RX_AGLBE);

    if (u1_t_txsts == (U1)XSPI_MET_XSPI_RX_READ_VALID) {
        vd_g_CanTxAppMET1S02_Put(&u4_ap_tx_data[0], (U1)XSPI_CANTX_BUFSIZE2);
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_MET1S27(const U4 * u4_ap_tx_data)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_tx_data                                                                                                     */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_MET1S27(const U4 * u4_ap_tx_data)
{
    U1 u1_t_txsts;

    u1_t_txsts = u1_g_XSpiMETRxRdAccessSts((U1)XSPI_MET_XSPI_RX_AGLBE);

    if (u1_t_txsts == (U1)XSPI_MET_XSPI_RX_READ_VALID) {
        vd_g_CanTxAppMET1S27_Put(&u4_ap_tx_data[0], (U1)XSPI_CANTX_BUFSIZE2);
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_MET1S29(const U4 * u4_ap_tx_data)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_tx_data                                                                                                     */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_MET1S29(const U4 * u4_ap_tx_data)
{
    U1 u1_t_txsts;

    u1_t_txsts = u1_g_XSpiMETRxRdAccessSts((U1)XSPI_MET_XSPI_RX_AGLBE);

    if (u1_t_txsts == (U1)XSPI_MET_XSPI_RX_READ_VALID) {
        vd_g_CanTxAppMET1S29_Put(&u4_ap_tx_data[0], (U1)XSPI_CANTX_BUFSIZE2);
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_MET1S30(const U4 * u4_ap_tx_data)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_tx_data                                                                                                     */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_MET1S30(const U4 * u4_ap_tx_data)
{
    U1 u1_t_txsts;

    u1_t_txsts = u1_g_XSpiMETRxRdAccessSts((U1)XSPI_MET_XSPI_RX_AGLBE);

    if (u1_t_txsts == (U1)XSPI_MET_XSPI_RX_READ_VALID) {
        vd_g_CanTxAppMET1S30_Put(&u4_ap_tx_data[0], (U1)XSPI_CANTX_BUFSIZE8);
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_MET1S62(const U4 * u4_ap_tx_data)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_tx_data                                                                                                     */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_MET1S62(const U4 * u4_ap_tx_data)
{
    U1 u1_t_txsts;

    u1_t_txsts = u1_g_XSpiMETRxRdAccessSts((U1)XSPI_MET_XSPI_RX_AGLBE);

    if (u1_t_txsts == (U1)XSPI_MET_XSPI_RX_READ_VALID) {
        vd_g_CanTxAppMET1S62_Put(&u4_ap_tx_data[0], (U1)XSPI_CANTX_BUFSIZE2);
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_MET1S70(const U4 * u4_ap_tx_data)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_tx_data                                                                                                     */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_MET1S70(const U4 * u4_ap_tx_data)
{
    U1 u1_t_txsts;

    u1_t_txsts = u1_g_XSpiMETRxRdAccessSts((U1)XSPI_MET_XSPI_RX_AGLBE);

    if (u1_t_txsts == (U1)XSPI_MET_XSPI_RX_READ_VALID) {
        vd_g_CanTxAppMET1S70_Put(&u4_ap_tx_data[0], (U1)XSPI_CANTX_BUFSIZE8);
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
/*  1.0.0     8/22/2018  TA       New.                                                                                               */
/*  1.3.0    10/05/2020  KM       Change for 800B CV-R.                                                                              */
/*  1.4.0    12/21/2020  TN       Change for 800B 1A                                                                                 */
/*  1.5.0    05/17/2021  TN       Change for 300D/178D/893B CV.                                                                      */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  970B/200D/220D                                                                                                                   */
/*           07/18/2022  TN       New for 970B/200D/220D Pre1A base on 178D.                                                         */
/*  115D/117D/200D                                                                                                                   */
/*           08/30/2022  TN       Change for 115D/117D/200D 1A                                                                       */
/*  970B/850B                                                                                                                        */
/*           08/30/2022  TN       Change for 970B/850B 1A. HOFDIOPE Gateway Add.                                                     */
/*  130D HEV                                                                                                                         */
/*           04/04/2023  TN       DCLV Add. Change for 130D HEV MPT.                                                                 */
/*  19PFv3                                                                                                                           */
/*           02/19/2024  DR       Change for 19PFv3 TIMCHG                                                                           */
/*           02/20/2024  GM       Change config for 19PFv3 CV                                                                        */
/*           03/13/2024  PG       Delete vd_s_LcomSpiCfgTxSCL                                                                        */
/*           04/15/2024  SN       Change for 19PFv3 ADASCS                                                                           */
/*           04/23/2024  TR       Delete LCOM config functions of DK_DLSCT, SW_ITS01,                                                */
/*                                SW_ITS02, EMGONSW, CACONSW, SW_RSA01 and TSR_OSM                                                   */
/*           05/07/2024  TR       Delete LCOM config functions of DK_METDL and DK_DLCNL                                              */
/*           07/10/2024  YR       Added config for 19PFv3 HCS                                                                        */
/*  BEV                                                                                                                              */
/*           10/10/2024  KT       Change for BEV System_Consideration_1.(MET-B_OMRBB-CSTD-0-)                                        */
/*           01/30/2025  KO       Change for BEV System_Consideration_1.(MET-C_HCS-CSTD-0-)                                          */
/*           01/31/2025  MN       Change for BEV System_Consideration_1.(MET-B_PWLBB-CSTD-0-)                                        */
/*           01/31/2025  HY       Change for BEV System_Consideration_1.(MET-B_WPBB-CSTD-0-)                                         */
/*           02/10/2024  RO       Change for BEV System_Consideration_1.(MET-S_ADMID-CSTD-0-)                                        */
/*           02/10/2024  RO       Change for BEV System_Consideration_1.(MET-S_ADVMID-CSTD-0-)                                       */
/*           02/10/2025  HF       Change for BEV System_Consideration_1.(MET-B_LMPBB-CSTD-0-)                                        */
/*           02/10/2025  SF       Change for BEV System_Consideration_1.(MET-M_ONOFF-CSTD-1-02-A-C0)                                 */
/*           03/06/2025  HT       Change for BEV System_Consideration_1.(MET-B_WDICBB-CSTD-0-01-A-C0)                                */
/*           03/06/2025  HT       Change for BEV System_Consideration_1.(MET-B_TITEBB-CSTD-0-00-A-C0)                                */
/*           03/06/2025  HT       Change for BEV System_Consideration_1.(MET-B_MWBB-CSTD-0-00-A-C0)                                  */
/*           03/06/2025  HT       Change for BEV System_Consideration_1.(MET-S_ADBB-CSTD-0-01-A-C0)                                  */
/*           03/06/2025  HT       Change for BEV System_Consideration_1.(MET-C_HCSBSW-CSTD-0-01-A-C0)                                */
/*           05/14/2025  RO       Change for BEV EMC R.(MET-S_ADMID-CSTD-0-02-A-C0)                                                  */
/*           05/30/2025  SN(K)    Change for BEV System_Consideration_2.(MET-S_ADBB-CSTD-0-01-A-C0)                                  */
/*           06/13/2025  KO       Change for BEV System_Consideration_2.(MET-B_DRPBB-CSTD-0-01-A-C0)                                 */
/*           06/30/2025  KT       Change for BEV System_Consideration_2.(BEV3CDCMET-547/BEV3CDCMET-549)                              */
/*           07/07/2025  KT       Change for BEV System_Consideration_2.(CAN V7.3)                                                   */
/*           07/08/2025  TH       Change for BEV System_Consideration_2.(MET-C_HCSBSW-CSTD-0-02-A-C0)                                */
/*           10/22/2025  TS       Change for BEV rebase.                                                                             */
/*           11/13/2025  YN       Change for BEV rebase.(Add CanTxApp)                                                               */
/*           12/08/2025  YN       Change for BEV rebase.(Add CanTxApp_2)                                                             */
/*           01/30/2026  TN       Fix initial value issue (BEV3CDCMET-3693).                                                         */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * KM   = Keisuke Mashita, Denso Techno                                                                                           */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * TR   = Tebs Ramos,     DTPH                                                                                                    */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*  * SF   = Shiro Furui, Denso Techno                                                                                               */
/*  * HT   = Hibiki Tanii, KSE                                                                                                       */
/*  * SN(K)= Shizuka Nakajima, KSE                                                                                                   */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * TS   = Takuo Suganuma, Denso Techno                                                                                            */
/*  * YN   = Yujiro Nagaya, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
