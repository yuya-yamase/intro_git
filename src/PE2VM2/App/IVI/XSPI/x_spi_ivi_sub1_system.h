/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Transmission and reception processing of subframe 4 in XSPI communication.                                                       */
/*  Handled data: CAN Data/Repro/LCAN Data                                                                                           */
/*===================================================================================================================================*/

#ifndef XSPI_IVI_SUB1_SYSTEM_H
#define XSPI_IVI_SUB1_SYSTEM_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SUB1_SYSTEM_H_MAJOR           (0)
#define XSPI_IVI_SUB1_SYSTEM_H_MINOR           (0)
#define XSPI_IVI_SUB1_SYSTEM_H_PATCH           (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_EXTSIG_NUM                  (17U)
#define XSPI_IVI_EXTSIG_TEST                 (0U)
#define XSPI_IVI_EXTSIG_BOOT                 (1U)
#define XSPI_IVI_EXTSIG_USB                  (2U)
#define XSPI_IVI_EXTSIG_MIC                  (3U)
#define XSPI_IVI_EXTSIG_MIC2                 (4U)
#define XSPI_IVI_EXTSIG_MIC3                 (5U)
#define XSPI_IVI_EXTSIG_MIC4                 (6U)
#define XSPI_IVI_EXTSIG_WIFI                 (7U)
#define XSPI_IVI_EXTSIG_WIFI2                (8U)
#define XSPI_IVI_EXTSIG_DTV                  (9U)
#define XSPI_IVI_EXTSIG_DTV2                 (10U)
#define XSPI_IVI_EXTSIG_DTV3                 (11U)
#define XSPI_IVI_EXTSIG_DTV4                 (12U)
#define XSPI_IVI_EXTSIG_GNSS                 (13U)
#define XSPI_IVI_EXTSIG_DAB                  (14U)
#define XSPI_IVI_EXTSIG_DAB2                 (15U)
#define XSPI_IVI_EXTSIG_PWR                  (16U)
#define XSPI_IVI_EXTSIG_SNDSIZ               (2 + XSPI_IVI_EXTSIG_NUM*2)

#define XSPI_IVI_TMUTE_UNDEF                 (0U)
#define XSPI_IVI_TMUTE_MUTE                  (1U)
#define XSPI_IVI_TMUTE_UNMUTE                (2U)

#define XSPI_IVI_SYSTEM_NUM                  (1U)
#define XSPI_IVI_SYSTEM_STRMODE              (0U)
#define XSPI_IVI_SYSTEM_SNDSIZE              (2U + XSPI_IVI_SYSTEM_NUM * 2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    /*Pulse Width Data*/
    U1                          u1_clock_freq;
    U4                          u4_sp_count;
}ST_XSPI_IVI_SP_CNT_DATA;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_XspiIviSub1SystemInit(void);
void            vd_g_XspiIviSub1SystemMainTask(void);
void            vd_g_XspiIviSub1SystemAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE);
void            vd_g_XspiIviSub1DDconSend(const U1 * u1_ap_DATA);
void            vd_g_XspiIviSub1GpsStsSend(void);
void            vd_g_XspiIviSub1GpsStsPut(const U1 u1_a_DATA);
void            vd_g_XspiIviSub1ExtSiGSend(void);
void            vd_g_XspiIviSub1ExtSgnlPut(const U1 u1_a_ID,const U1 u1_a_DATA);
void            vd_g_XspiIviSub1GpsOpeResPut(const U1 u1_a_DATA);
void            vd_g_XspiIviSub1VehspdCntSend(void);
void            vd_g_XspiIviSub1SpCntPut(const ST_XSPI_IVI_SP_CNT_DATA st_a_DATA);
void            vd_g_XspiIviSub1USBPowSupPut(const U2 u2_a_DATA);
void            vd_g_XspiIviSub1TmuteSend(void);
void            vd_g_XspiIviSub1TmuteDataPut(const U1 u1_a_DATA);
void            vd_g_XspiIviSub1SystemDataPut(const U1 u1_a_ID,const U1 u1_a_DATA);
void            vd_g_XspiIviSub1SystemData1stSend(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#endif /* XSPI_IVI_SUB1_SYSTEM_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  x_spi_ivi_sub1_system.c                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
