/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  BootLogCtl                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "BootLogCtl.h"
#include "SysEcDrc.h"
#include "x_spi_ivi_sub1_power.h"
#include "memfill_u1.h"
#include "memfill_u4.h"
#include "memcpy_u1.h"
#include "Dio.h"
#include "ivdsh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define BOOTLOGCTL_POINT_NUM                    (6U)
#define BOOTLOGCTL_POINT_WKUP                   (0U)
#define BOOTLOGCTL_POINT_WKFCTDTCT              (1U)
#define BOOTLOGCTL_POINT_SOCWAKE                (2U)
#define BOOTLOGCTL_POINT_STRWAKE                (3U)
#define BOOTLOGCTL_POINT_ETHLINKUP              (4U)
#define BOOTLOGCTL_POINT_RXREQ                  (5U)

#define BOOTLOGCTL_STS_WKUPDTC                  (0x01U)
#define BOOTLOGCTL_STS_WAKEFACT                 (0x02U)
#define BOOTLOGCTL_STS_SOCWAKE                  (0x04U)
#define BOOTLOGCTL_STS_STRWAKE                  (0x08U)
#define BOOTLOGCTL_STS_ETHLINKUP                (0x10U)
#define BOOTLOGCTL_STS_RXREQ                    (0x20U)

#define BOOTLOGCTL_FLG1_RXREQ                   (0x01U)
#define BOOTLOGCTL_FLG1_WKUPDTC                 (0x02U)
#define BOOTLOGCTL_FLG1_WKUP                    (0x04U)
#define BOOTLOGCTL_FLG1_WAKEFACT                (0x08U)
#define BOOTLOGCTL_FLG1_PWRFACT                 (0x10U)
#define BOOTLOGCTL_FLG1_WKFCTDTCT               (0x20U)
#define BOOTLOGCTL_FLG1_SOCWAKE                 (0x40U)
#define BOOTLOGCTL_FLG1_STRWAKE                 (0x80U)
#define BOOTLOGCTL_FLG2_ETHLINKUP               (0x01U)

#define BOOTLOGCTL_BUFF_NUM                     (35U)
#define BOOTLOGCTL_BUFF_FLG1INFO                (0U)
#define BOOTLOGCTL_BUFF_RXREQ                   (1U)
#define BOOTLOGCTL_BUFF_WKUPDTCT                (5U)
#define BOOTLOGCTL_BUFF_WKUP                    (9U)
#define BOOTLOGCTL_BUFF_WAKEFACT                (13U)
#define BOOTLOGCTL_BUFF_PWRFACT                 (14U)
#define BOOTLOGCTL_BUFF_WKFCTDTC                (18U)
#define BOOTLOGCTL_BUFF_SOCWAKE                 (22U)
#define BOOTLOGCTL_BUFF_STRWAKE                 (26U)
#define BOOTLOGCTL_BUFF_FLG2INFO                (30U)
#define BOOTLOGCTL_BUFF_ETHLINKUP               (31U)

#define BOOTLOGCTL_FACT_UNKNOWN                 (0U)
#define BOOTLOGCTL_FACT_WKUP                    (1U)
#define BOOTLOGCTL_FACT_STRRESUME               (2U)

#define BOOTLOGCTL_PMPWREN_INI                  (0xFFU)

#define BOOTLOGCTL_PWRINFO_NUM                  (4U)

#define BOOTLOGCTL_TIMSIZ                       (4U)
#define BOOTLOGCTL_TIMBUFF0                     (0U)
#define BOOTLOGCTL_TIMBUFF1                     (1U)
#define BOOTLOGCTL_TIMBUFF2                     (2U)
#define BOOTLOGCTL_TIMBUFF3                     (3U)

#define BOOTLOGCTL_MASK_1BYTE                   (0x000000FFU)
#define BOOTLOGCTL_MASK_2BYTE                   (0x0000FF00U)
#define BOOTLOGCTL_MASK_3BYTE                   (0x00FF0000U)
#define BOOTLOGCTL_MASK_4BYTE                   (0xFF000000U)

#define BOOTLOGCTL_SHIF_1BYTE                   (8U)
#define BOOTLOGCTL_SHIF_2BYTE                   (16U)
#define BOOTLOGCTL_SHIF_3BYTE                   (24U)

#define BOOTLOGCTL_VM_1WORD                     (1U)

#define BOOTLOGCTL_DETECT_OFF                   (0U)
#define BOOTLOGCTL_DETECT_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define BOOTLOGCTL_PORT_AOSS_SLEEP_ENTRY_EXIT   (DIO_ID_PORT17_CH0)

#define BOOTLOGCTL_MCULOG_WKUP                  (SYSECDRC_DREC_ID_1)
#define BOOTLOGCTL_MCULOG_WAKEFACT              (SYSECDRC_DREC_ID_2)
#define BOOTLOGCTL_MCULOG_SOCWAKE               (SYSECDRC_DREC_ID_3)
#define BOOTLOGCTL_MCULOG_STRWAKE               (SYSECDRC_DREC_ID_4)
#define BOOTLOGCTL_MCULOG_ETHLINKUP             (SYSECDRC_DREC_ID_5)
#define BOOTLOGCTL_MCULOG_RXREQ                 (SYSECDRC_DREC_ID_6)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4    u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_NUM];
static U1    u1_sp_bootlogctl_pwrstate[XSPI_IVI_POWER_01_BUFSIZ];
static U1    u1_s_bootlogctl_stsflg;
static U1    u1_s_bootlogctl_wakefact;
static U1    u1_s_bootlogctl_socwake_sts;
static U1    u1_s_bootlogctl_strwake_sts;
static U1    u1_s_bootlogctl_linkup_sts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_BootLogCtl_Init(void);
static void     vd_s_BootLogCtl_Clear(void);
static void     vd_s_BootLogCtl_WakeFactDetect(void);
static void     vd_s_BootLogCtl_ChkSocWake(const U1 u1_a_STS);
static void     vd_s_BootLogCtl_ChkStrWake(const U1 u1_a_STS);
static void     vd_s_BootLogCtl_ChkLinkUp(const U1 u1_a_STS);
static void     vd_s_BootLogCtl_SetTim_4(U4 u4_a_time, U1* u1p_a_buff);
static U4       u4_s_BootLogCtl_GetElpsdTim(const U4 u4_a_NEW, const U4 u4_a_BASE);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_s_BootLogCtl_Init(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_BootLogCtl_BonInit(void)
{
    vd_s_BootLogCtl_Init();
    
    u1_s_bootlogctl_wakefact = (U1)BOOTLOGCTL_FACT_WKUP;
    vd_s_BootLogCtl_WakeFactDetect();
}

/*===================================================================================================================================*/
/*  void    vd_g_BootLogCtl_WkupInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_BootLogCtl_WkupInit(void)
{
    U1 u1_t_port_sts;

    vd_s_BootLogCtl_Init();
    
    u1_t_port_sts = (U1)Dio_ReadChannel(BOOTLOGCTL_PORT_AOSS_SLEEP_ENTRY_EXIT);
    if(u1_t_port_sts == (U1)STD_HIGH){
        u1_s_bootlogctl_wakefact = (U1)BOOTLOGCTL_FACT_STRRESUME;
    }
    else{
        u1_s_bootlogctl_wakefact = (U1)BOOTLOGCTL_FACT_WKUP;
    }
    vd_s_BootLogCtl_WakeFactDetect();
}

/*===================================================================================================================================*/
/*  static void    vd_s_BootLogCtl_Init(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_BootLogCtl_Init(void)
{
    u1_s_bootlogctl_socwake_sts = (U1)BOOTLOGCTL_DETECT_OFF;
    u1_s_bootlogctl_strwake_sts = (U1)BOOTLOGCTL_DETECT_OFF;
    u1_s_bootlogctl_linkup_sts = (U1)BOOTLOGCTL_DETECT_OFF;
    vd_s_BootLogCtl_Clear();
}

/*===================================================================================================================================*/
/*  static void    vd_s_BootLogCtl_Clear(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_BootLogCtl_Clear(void)
{
    vd_g_MemfillU4(&u4_sp_bootlogctl_time[0], (U4)0U, (U4)BOOTLOGCTL_POINT_NUM);
    vd_g_MemfillU1(&u1_sp_bootlogctl_pwrstate[0], (U1)0U, (U4)XSPI_IVI_POWER_01_BUFSIZ);
    u1_s_bootlogctl_stsflg = (U1)0U;
    u1_s_bootlogctl_wakefact = (U1)BOOTLOGCTL_FACT_UNKNOWN;
    
    vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_BOOTLOG, (U1)BOOTLOGCTL_MCULOG_WKUP, (U1)0x00, (U1)0x00);
    u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_WKUP] = u4_g_SysEcDrc_GetSystime();
    u1_s_bootlogctl_stsflg |= (U1)BOOTLOGCTL_STS_WKUPDTC;
}

/*===================================================================================================================================*/
/*  static void    vd_s_BootLogCtl_WakeFactDetect(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_BootLogCtl_WakeFactDetect(void)
{
    vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_BOOTLOG, (U1)BOOTLOGCTL_MCULOG_WAKEFACT, (U1)u1_s_bootlogctl_wakefact, (U1)0x00);
    u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_WKFCTDTCT] = u4_g_SysEcDrc_GetSystime();
    vd_g_XspiIviSub1PowerGetSts(&u1_sp_bootlogctl_pwrstate[0]);
    u1_s_bootlogctl_stsflg |= (U1)BOOTLOGCTL_STS_WAKEFACT;
}

/*===================================================================================================================================*/
/*  void    vd_g_BootLogCtl_MainTask(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_BootLogCtl_MainTask(void)
{
    U1 u1_t_sts;
    U4 u4_t_read;
    U1 u1_t_socwake;
    U1 u1_t_strwake;
    U1 u1_t_linkup;

    u4_t_read = (U4)0U;
    u1_t_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO2_BOOTLOG_INF, &u4_t_read, (U2)BOOTLOGCTL_VM_1WORD);
    if(u1_t_sts != IVDSH_NO_REA){
        u1_t_socwake = (U1)(u4_t_read & (U4)BOOTLOGCTL_MASK_1BYTE);
        u1_t_strwake = (U1)((u4_t_read & (U4)BOOTLOGCTL_MASK_2BYTE) >> BOOTLOGCTL_SHIF_1BYTE);
        u1_t_linkup = (U1)((u4_t_read & (U4)BOOTLOGCTL_MASK_3BYTE) >> BOOTLOGCTL_SHIF_2BYTE);
        vd_s_BootLogCtl_ChkSocWake(u1_t_socwake);
        vd_s_BootLogCtl_ChkStrWake(u1_t_strwake);
        vd_s_BootLogCtl_ChkLinkUp(u1_t_linkup);
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_BootLogCtl_ChkSocWake(const U1 u1_a_STS)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_BootLogCtl_ChkSocWake(const U1 u1_a_STS)
{
    if((u1_a_STS == (U1)BOOTLOGCTL_DETECT_ON) && (u1_s_bootlogctl_socwake_sts == (U1)BOOTLOGCTL_DETECT_OFF)){
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_BOOTLOG, (U1)BOOTLOGCTL_MCULOG_SOCWAKE, (U1)0x00, (U1)0x00);
        u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_SOCWAKE] = u4_g_SysEcDrc_GetSystime();
        u1_s_bootlogctl_stsflg |= (U1)BOOTLOGCTL_STS_SOCWAKE;
    }
    if((u1_a_STS == (U1)BOOTLOGCTL_DETECT_OFF) && (u1_s_bootlogctl_socwake_sts == (U1)BOOTLOGCTL_DETECT_ON)){
        vd_s_BootLogCtl_Clear();
        u1_s_bootlogctl_wakefact = (U1)BOOTLOGCTL_FACT_WKUP;
        vd_s_BootLogCtl_WakeFactDetect();
    }
    u1_s_bootlogctl_socwake_sts = u1_a_STS;
}

/*===================================================================================================================================*/
/*  static void    vd_s_BootLogCtl_ChkStrWake(const U1 u1_a_STS)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_BootLogCtl_ChkStrWake(const U1 u1_a_STS)
{
    if((u1_a_STS == (U1)BOOTLOGCTL_DETECT_ON) && (u1_s_bootlogctl_strwake_sts == (U1)BOOTLOGCTL_DETECT_OFF)){
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_BOOTLOG, (U1)BOOTLOGCTL_MCULOG_STRWAKE, (U1)0x00, (U1)0x00);
        u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_STRWAKE] = u4_g_SysEcDrc_GetSystime();
        u1_s_bootlogctl_stsflg |= (U1)BOOTLOGCTL_STS_STRWAKE;
    }
    if((u1_a_STS == (U1)BOOTLOGCTL_DETECT_OFF) && (u1_s_bootlogctl_strwake_sts == (U1)BOOTLOGCTL_DETECT_ON)){
        vd_s_BootLogCtl_Clear();
        u1_s_bootlogctl_wakefact = (U1)BOOTLOGCTL_FACT_STRRESUME;
        vd_s_BootLogCtl_WakeFactDetect();
    }
    u1_s_bootlogctl_strwake_sts = u1_a_STS;
}

/*===================================================================================================================================*/
/*  static void    vd_s_BootLogCtl_ChkLinkUp(const U1 u1_a_STS)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_BootLogCtl_ChkLinkUp(const U1 u1_a_STS)
{
    if((u1_a_STS == (U1)BOOTLOGCTL_DETECT_ON) && (u1_s_bootlogctl_linkup_sts == (U1)BOOTLOGCTL_DETECT_OFF)){
        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_BOOTLOG, (U1)BOOTLOGCTL_MCULOG_ETHLINKUP, (U1)0x00, (U1)0x00);
        u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_ETHLINKUP] = u4_g_SysEcDrc_GetSystime();
        u1_s_bootlogctl_stsflg |= (U1)BOOTLOGCTL_STS_ETHLINKUP;
    }
    u1_s_bootlogctl_linkup_sts = u1_a_STS;
}

/*===================================================================================================================================*/
/*  void    vd_g_BootLogCtl_RxReq(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_BootLogCtl_RxReq(void)
{
    U4 u4_t_elpsd_time;
    U1 u1_t_sts;
    U1 u1_t_buff[BOOTLOGCTL_BUFF_NUM];
    
    vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_BOOTLOG, (U1)BOOTLOGCTL_MCULOG_RXREQ, (U1)0x00, (U1)0x00);
    u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_RXREQ] = u4_g_SysEcDrc_GetSystime();
    u1_s_bootlogctl_stsflg |= (U1)BOOTLOGCTL_STS_RXREQ;

    vd_g_MemfillU1(&u1_t_buff[0], (U1)0x00U, (U4)BOOTLOGCTL_BUFF_NUM);
    
    vd_s_BootLogCtl_SetTim_4(u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_RXREQ], &u1_t_buff[BOOTLOGCTL_BUFF_RXREQ]);
    u1_t_buff[BOOTLOGCTL_BUFF_FLG1INFO] |= (U1)BOOTLOGCTL_FLG1_RXREQ;
    
    u1_t_sts = u1_s_bootlogctl_stsflg & (U1)BOOTLOGCTL_STS_WKUPDTC;
    if(u1_t_sts == (U1)BOOTLOGCTL_STS_WKUPDTC){
        vd_s_BootLogCtl_SetTim_4(u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_WKUP], &u1_t_buff[BOOTLOGCTL_BUFF_WKUPDTCT]);
        u1_t_buff[BOOTLOGCTL_BUFF_FLG1INFO] |= (U1)BOOTLOGCTL_FLG1_WKUPDTC;
        
        u4_t_elpsd_time = u4_s_BootLogCtl_GetElpsdTim(u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_RXREQ], u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_WKUP]);
        vd_s_BootLogCtl_SetTim_4(u4_t_elpsd_time, &u1_t_buff[BOOTLOGCTL_BUFF_WKUP]);
        u1_t_buff[BOOTLOGCTL_BUFF_FLG1INFO] |= (U1)BOOTLOGCTL_FLG1_WKUP;
    }
    
    u1_t_sts = u1_s_bootlogctl_stsflg & (U1)BOOTLOGCTL_STS_WAKEFACT;
    if(u1_t_sts == (U1)BOOTLOGCTL_STS_WAKEFACT){
        u1_t_buff[BOOTLOGCTL_BUFF_WAKEFACT] = u1_s_bootlogctl_wakefact;
        u1_t_buff[BOOTLOGCTL_BUFF_FLG1INFO] |= (U1)BOOTLOGCTL_FLG1_WAKEFACT;
    
        vd_g_MemcpyU1(&u1_t_buff[BOOTLOGCTL_BUFF_PWRFACT], &u1_sp_bootlogctl_pwrstate[XSPI_IVI_POWER_01_BYTE2], (U4)BOOTLOGCTL_PWRINFO_NUM);
        u1_t_buff[BOOTLOGCTL_BUFF_FLG1INFO] |= (U1)BOOTLOGCTL_FLG1_PWRFACT;
    
        u4_t_elpsd_time = u4_s_BootLogCtl_GetElpsdTim(u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_RXREQ], u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_WKFCTDTCT]);
        vd_s_BootLogCtl_SetTim_4(u4_t_elpsd_time, &u1_t_buff[BOOTLOGCTL_BUFF_WKFCTDTC]);
        u1_t_buff[BOOTLOGCTL_BUFF_FLG1INFO] |= (U1)BOOTLOGCTL_FLG1_WKFCTDTCT;
    }
    
    u1_t_sts = u1_s_bootlogctl_stsflg & (U1)BOOTLOGCTL_STS_SOCWAKE;
    if(u1_t_sts == (U1)BOOTLOGCTL_STS_SOCWAKE){
        u4_t_elpsd_time = u4_s_BootLogCtl_GetElpsdTim(u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_RXREQ], u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_SOCWAKE]);
        vd_s_BootLogCtl_SetTim_4(u4_t_elpsd_time, &u1_t_buff[BOOTLOGCTL_BUFF_SOCWAKE]);
        u1_t_buff[BOOTLOGCTL_BUFF_FLG1INFO] |= (U1)BOOTLOGCTL_FLG1_SOCWAKE;
    }
    
    u1_t_sts = u1_s_bootlogctl_stsflg & (U1)BOOTLOGCTL_STS_STRWAKE;
    if(u1_t_sts == (U1)BOOTLOGCTL_STS_STRWAKE){
        u4_t_elpsd_time = u4_s_BootLogCtl_GetElpsdTim(u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_RXREQ], u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_STRWAKE]);
        vd_s_BootLogCtl_SetTim_4(u4_t_elpsd_time, &u1_t_buff[BOOTLOGCTL_BUFF_STRWAKE]);
        u1_t_buff[BOOTLOGCTL_BUFF_FLG1INFO] |= (U1)BOOTLOGCTL_FLG1_STRWAKE;
    }
    
    u1_t_sts = u1_s_bootlogctl_stsflg & (U1)BOOTLOGCTL_STS_ETHLINKUP;
    if(u1_t_sts == (U1)BOOTLOGCTL_STS_ETHLINKUP){
        u4_t_elpsd_time = u4_s_BootLogCtl_GetElpsdTim(u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_RXREQ], u4_sp_bootlogctl_time[BOOTLOGCTL_POINT_ETHLINKUP]);
        vd_s_BootLogCtl_SetTim_4(u4_t_elpsd_time, &u1_t_buff[BOOTLOGCTL_BUFF_ETHLINKUP]);
        u1_t_buff[BOOTLOGCTL_BUFF_FLG2INFO] |= (U1)BOOTLOGCTL_FLG2_ETHLINKUP;
    }
    vd_g_XspiIviSub1PowerBootLogResSend(&u1_t_buff[0]);
}

/*===================================================================================================================================*/
/*  static void vd_s_BootLogCtl_SetTim_4(U4 u4_a_time, U1* u1p_a_buff)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_BootLogCtl_SetTim_4(U4 u4_a_time, U1* u1p_a_buff)
{
    U1 u1_t_time[BOOTLOGCTL_TIMSIZ];
    
    u1_t_time[BOOTLOGCTL_TIMBUFF3] = (U1)(u4_a_time & (U4)BOOTLOGCTL_MASK_1BYTE);
    u1_t_time[BOOTLOGCTL_TIMBUFF2] = (U1)((u4_a_time & (U4)BOOTLOGCTL_MASK_2BYTE) >> BOOTLOGCTL_SHIF_1BYTE);
    u1_t_time[BOOTLOGCTL_TIMBUFF1] = (U1)((u4_a_time & (U4)BOOTLOGCTL_MASK_3BYTE) >> BOOTLOGCTL_SHIF_2BYTE);
    u1_t_time[BOOTLOGCTL_TIMBUFF0] = (U1)((u4_a_time & (U4)BOOTLOGCTL_MASK_4BYTE) >> BOOTLOGCTL_SHIF_3BYTE);
    
    if(u1p_a_buff != NULL_PTR){
        vd_g_MemcpyU1(&u1p_a_buff[0], &u1_t_time[0], (U4)BOOTLOGCTL_TIMSIZ);
    }
}

/*===================================================================================================================================*/
/*  static U4       u4_s_BootLogCtl_GetElpsdTim(const U4 u4_a_NEW, const U4 u4_a_BASE)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4       u4_s_BootLogCtl_GetElpsdTim(const U4 u4_a_NEW, const U4 u4_a_BASE)
{
    U4 u4_t_elpsd_time;
    
    if(u4_a_NEW >= u4_a_BASE){
        u4_t_elpsd_time = u4_a_NEW - u4_a_BASE;
    }
    else{
        u4_t_elpsd_time = ((U4)U4_MAX - u4_a_BASE) + u4_a_NEW;
    }
    
    return(u4_t_elpsd_time);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    09/22/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
