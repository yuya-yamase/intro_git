/* PwrCtrl_Sys_Pwr_c_v1-0-0                                                 */
/****************************************************************************/
/* Copyright (C) 2023 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PwrCtrl_Sys_Pwr/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "PwrCtrl_cfg_private.h"

#include "PwrCtlSup.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* GNSS����d�l */
#define MCU_STEP_GNSS_PRE               (1U)
#define MCU_STEP_GNSS_INI_CHK           (2U)
#define MCU_STEP_GNSS_PRECHK            (3U)
#define MCU_STEP_GNSS_POSTCHK           (4U)
#define MCU_STEP_GNSS_POLING            (5U)
#define MCU_STEP_GNSS_FIN               (6U)
#define MCU_STEP_GNSS_WAIT              (7U)

#define PWRCTRL_WAIT_GNSS_400MS         (400U / PWRCTRL_CFG_TASK_TIME)
#define PWRCTRL_WAIT_GNSS_550MS         (550U / PWRCTRL_CFG_TASK_TIME)

#define PWRCTRL_WAIT_POWERIC_100MS      (100U   / PWRCTRL_CFG_TASK_TIME)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void vd_s_PwrCtrlSysPwrOnBuDdMode( void );
static void vd_s_PwrCtrlSysPwrOnDisCharge( void );
static void vd_s_PwrCtrlSysPwrOnBoostDcdc( void );
static void vd_s_PwrCtrlSysPwrOnBoostAsilDcdc( void );
static void vd_s_PwrCtrlSysPwrOnDdFreq( void );
static void vd_s_PwrCtrlSysPwrOnBoostAsilFreq( void );
static void vd_s_PwrCtrlSysPwrOnV33Peri( void );
static void vd_s_PwrCtrlSysPwrOnV33Asil( void );
static void vd_s_PwrCtrlSysPwrOnV18( void );
static void vd_s_PwrCtrlSysPwrOnV18Asil( void );
static void vd_s_PwrCtrlSysPwrOnAudio( void );
static void vd_s_PwrCtrlSysPwrOnV11Asil( void );
static void vd_s_PwrCtrlSysPwrOnEizo( void );
static void vd_s_PwrCtrlSysPwrOffflw( void );

/* �f�o�C�XON���� */
static U1       u1_t_Pwron_TimChk(const U4 u1_a_TIMCNT, const U4 u1_a_TIMFIN);
static void     vd_s_McuDev_Polling_V33PERI(void);
static void     vd_s_McuDev_Polling_EIZO( void );
static void     vd_s_McuDev_Polling_AUDIO( void );
static void     vd_s_McuDev_Pwron_USB(const U1 u1_a_PWR);
static void     vd_s_McuDev_Pwron_PictIC(const U1 u1_a_PWR);
static void     vd_s_McuDev_Pwron_GVIFRx(void);
static void     vd_s_McuDev_Pwron_GVIFTx_CDisp(const U1 u1_a_PWR);
static void     vd_s_McuDev_Pwron_Mic(const U1 u1_a_PWR);
static void     vd_s_McuDev_Pwron_Ant(const U1 u1_a_PWR);
static void     vd_s_McuDev_SoundMUTE(void);
static void     vd_s_McuDev_Pwron_Most(const U1 u1_a_PWR);
static void     vd_s_McuDev_Pwron_XMTuner(void);
static void     vd_s_McuDev_Pwron_PowerIc(const U1 u1_a_PWR);
void    Mcu_Dev_Pwron_GNSS( void );
static void    vd_s_McuDev_Pwron_Gyro(void);

void    Mcu_Dev_Pwron_EizoIc_Init( void );
void    Mcu_Dev_Pwron_GvifRcvr_Init( void );
void    Mcu_Dev_Pwron_GvifSndr_Init( void );
void    Mcu_Dev_Pwron_EizoIc_RegSetting( void );
void    Mcu_Dev_Pwron_EizoIc_SetReg( void );
void    Mcu_Dev_Pwron_EizoIc_PctDspSetting( void );
void    Mcu_Dev_Pwron_EizoIc_CamDspSetting( void );

void    Mcu_Dev_Pwron_EizoIc_Polling_VIcRst( void );
void    Mcu_Dev_Pwron_GvifRx_Polling_Rst( void );
void    Mcu_Dev_Pwron_GvifRx_RegSetting( void );

void    Mcu_Dev_Pwron_GvifTx_Polling_Rst( void );
void    Mcu_Dev_Pwron_GvifTx_RegSetting( void );
void    Mcu_Dev_Pwron_GvifTx_OutputSetting( void );

void    Mcu_Dev_Pwron_GvifRx_SetReg( void );
void    Mcu_Dev_Pwron_GvifTx_SetReg( void );
void    Mcu_Dev_Pwron_GvifTx_LnkChk( void );

static U1 Mcu_Dio_Port_Level[MCU_PORT_NUM];
static U1 Mcu_Dio_Port_level_Pre[MCU_PORT_NUM];

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* �t���[�����^�C�} */
static U4 Mcu_frt_stamp[GPT_FRT_USELPSD_NUM_PARAM];

/* ON/OFF�V�[�P���X�N���v�� */
static U1 u1_s_PwrCtrl_Sys_Pwr_Sts;

static U1 u1_s_PwrCtrl_Sys_PwrOn_Step;
static U1 u1_s_PwrCtrl_Sys_PwrOff_Step;
static U1 u1_s_PwrCtrl_Sys_Off_SubStep;

static U4 u4_s_PwrCtrl_Sys_Bu_Dd_Mode_Time;
static U4 u4_s_PwrCtrl_Sys_DisCharge_Time;
static U4 u4_s_PwrCtrl_Sys_Boost_Dcdc_Time;
static U4 u4_s_PwrCtrl_Sys_Boost_Asil_Dcdc_Time;
static U4 u4_s_PwrCtrl_Sys_Dd_Freq_Time;
static U4 u4_s_PwrCtrl_Sys_Boost_Asil_Freq_Time;
static U4 u4_s_PwrCtrl_Sys_V33_Peri_Time;
static U4 u4_s_PwrCtrl_Sys_V33_Asil_Time;
static U4 u4_s_PwrCtrl_Sys_V18_Time;
static U4 u4_s_PwrCtrl_Sys_V18_Asil_Time;
static U4 u4_s_PwrCtrl_Sys_Audio_Time;
static U4 u4_s_PwrCtrl_Sys_V11_Asil_Time;
static U4 u4_s_PwrCtrl_Sys_Eizo_Time;

/* �f�o�C�X�N���p�J�E���^ */
static U4 u4_s_PwrCtrl_Polling_V33PERI;
static U4 u4_s_PwrCtrl_Polling_EIZO;
static U4 u4_s_PwrCtrl_Polling_AUDIO;

static U4 u4_s_PwrCtrl_waittim_usb;
static U4 u4_s_PwrCtrl_waittim_pictic;

static U2 u2_s_PwrCtrl_Polling_VIcRst;
static U2 u2_s_PwrCtrl_Polling_GvifRxRst;
static U2 u2_s_PwrCtrl_Polling_GvifTxRst;

/* GNSS����d�l */
static uint8    Mcu_OnStep_GNSS;                /* 4����V�[�P���X */
static uint32   Mcu_GNSS_LinkTimer;             /* GNSS Wati�����p�^�C�} */
static uint8    Mcu_Fail_GNSS;                  /* GNSS PMONI Low ���m�J�E���^ (2��ڌ��m�łk�����p��) */

static uint16  Mcu_Gvif_LinkTimer;    /* CDC�N������̃^�C�}���{���͂����ƕʂ̏ꏊ�ŊǗ��H */
/* �W���C���E�����x�Z���T����d�l */
static uint8   mcu_gvif_restart_sts;

/* Power-IC����d�l */
static U1 u1_s_PwrCtrl_PowerIc_OVRALL;      /* 4.����t���[ 4-1.�ʏ�N�� */
static uint16   Mcu_PowerIc_OffTime;        /* Power-IC Off Wait�����p�^�C�} */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/*****************************************************************************
  Function      : PwrCtrl_Sys_PwrOn_GetSts
  Description   : SYS�d����Ԗ₢���킹
  param[in/out] : none
  return        : FALSE(0)�FSYS�d���V�[�P���X���s��
                  TRUE(1) �FSYS�d���V�[�P���X����
  Note          : 
*****************************************************************************/
U1 u1_g_PwrCtrlSysGetSts( void )
{
    U1 u1_t_ret;

    u1_t_ret = (U1)FALSE; /* �������FSYS�d���V�[�P���X���s�� */

    if ( u1_s_PwrCtrl_Sys_Pwr_Sts == (U1)PWRCTRL_SYS_NON )
    {
        u1_t_ret = (U1)TRUE;
    }

    return ( u1_t_ret );
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSysPwrOnStart
  Description   : SYS�d��ON�v��
  param[in/out] : none
  return        : none
  Note          : SYS�d��ON���������{��������𖞂������ꍇ�ɃR�[������B
                  ���ۂ�ON����(�҂����킹�AHW�A�N�Z�X)��MET/IVI�������(5ms)�Ŏ��{���邱�ƁB
*****************************************************************************/
void vd_g_PwrCtrlSysPwrOnStart( void )
{
    u1_s_PwrCtrl_Sys_Pwr_Sts = (U1)PWRCTRL_SYS_ON;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSysPwrOffStart
  Description   : SYS�d��OFF�v��
  param[in/out] : none
  return        : none
  Note          : SYS�d��OFF�v���������{��������𖞂������ꍇ�ɃR�[������B
                  ���ۂ�OFF����(�҂����킹�AHW�A�N�Z�X)��MET/IVI�������(5ms)�Ŏ��{���邱�ƁB
*****************************************************************************/
void vd_g_PwrCtrlSysPwrOffStart( void )
{
    u1_s_PwrCtrl_Sys_Pwr_Sts = (U1)PWRCTRL_SYS_OFF;

    return;
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlSysShtdwnGetSts
  Description   : SYS�n�f�o�C�X�I����Ԗ₢���킹
  param[in/out] : none
  return        : FALSE(0)�FSYS�n�f�o�C�X�I���������s��
                  TRUE(1) �FSYS�n�f�o�C�X�I����������
  Note          : SiP�d��OFF������ɃR�[������B
                  HW����d�l����́A�Ώۂ͊e�f�o�C�X�̐���d�l���Q�ƂƂ̋L�ڂ���B
*****************************************************************************/
U1   u1_g_PwrCtrlSysShtdwnGetSts( void )
{
    U1 u1_t_ret;

    u1_t_ret  = (U1)FALSE; /* �������FSYS�d��ON�V�[�P���X���s�� */

    if(u2_g_PwrCtrl_OffSts == (U2)PWROFF_CONP_BIT){
        u1_t_ret  =   (U1)TRUE;
    }
    return(u1_t_ret);
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSysInit
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSysInit( void )
{
    /* �t���[�����^�C�}�p�z�񏉊��� */
    for(U4 cnt = 0; cnt < (U4)GPT_FRT_USELPSD_NUM_PARAM; cnt++){
        Mcu_frt_stamp[cnt] = 0;
    }

    /* ON/OFF�V�[�P���X�N���v���̏����� */
    u1_s_PwrCtrl_Sys_Pwr_Sts             = (U1)PWRCTRL_SYS_NON;

    /* ���݋N���X�e�b�v�̏����� */
    u1_s_PwrCtrl_Sys_PwrOn_Step              = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    u1_s_PwrCtrl_Sys_PwrOff_Step             = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    u1_s_PwrCtrl_Sys_Off_SubStep             = (U1)PWRCTRL_COMMON_PROCESS_STEP1;

    /* �ҋ@���ԑ���pRAM�̏����� */
    u4_s_PwrCtrl_Sys_Bu_Dd_Mode_Time         = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_DisCharge_Time          = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_Boost_Dcdc_Time         = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_Boost_Asil_Dcdc_Time    = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_Dd_Freq_Time            = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_Boost_Asil_Freq_Time    = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_V33_Peri_Time           = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_V33_Asil_Time           = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_V18_Time                = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_V18_Asil_Time           = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_Audio_Time              = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_V11_Asil_Time           = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
    u4_s_PwrCtrl_Sys_Eizo_Time               = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;

    /* �f�o�C�X�N���p�J�E���^�̏����� */
    u4_s_PwrCtrl_Polling_V33PERI         = (uint32)0U;
    u4_s_PwrCtrl_Polling_EIZO            = (uint32)0U;
    u4_s_PwrCtrl_Polling_AUDIO           = (uint32)0U;

    u4_s_PwrCtrl_waittim_usb            = (U4)0U; 
    u4_s_PwrCtrl_waittim_pictic         = (U4)0U;

    u2_s_PwrCtrl_Polling_VIcRst          = (uint32)0U;
    u2_s_PwrCtrl_Polling_GvifRxRst       = (uint32)0U;
    u2_s_PwrCtrl_Polling_GvifTxRst       = (uint32)0U;
    mcu_gvif_restart_sts        = (uint8)0U;

    /* Init���̃t���[�����^�C�}�擾 */
    /* �g�p��FGNSS,�W���C���E�����x�Z���T���� */
    Mcu_frt_stamp[GPT_FRT_USELPSD_BASE] = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);

    Mcu_OnStep_GNSS             = (uint8)MCU_STEP_GNSS_PRE;
    Mcu_GNSS_LinkTimer          = (uint32)0U;
    Mcu_Fail_GNSS               = (uint8)0U;

    u1_s_PwrCtrl_PowerIc_OVRALL = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
    Mcu_PowerIc_OffTime         = (uint16)0U;

    for(U1 cnt = 0; cnt < MCU_PORT_NUM; cnt++){
        Mcu_Dio_Port_Level[cnt] = 0;
        Mcu_Dio_Port_level_Pre[cnt] = 0;
    }
   
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSysPwrOnMainFunction
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSysPwrOnMainFunction( void )
{
    /* SYS�N���d��ON�v������ */
    if ( u1_s_PwrCtrl_Sys_Pwr_Sts == PWRCTRL_SYS_ON )
    {
        /* OFF����STEP�Ǘ�RAM,�^�C�}���N���A����OFF2�T�ڂ����s�ł���悤�ɂ��� */
        u1_s_PwrCtrl_Sys_PwrOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
        u1_s_PwrCtrl_Sys_Off_SubStep = (U1)PWRCTRL_COMMON_PROCESS_STEP1;

        switch ( u1_s_PwrCtrl_Sys_PwrOn_Step )
        {
            case (U1)PWRCTRL_COMMON_PROCESS_STEP1:
                vd_s_PwrCtrlSysPwrOnBuDdMode(); /* STEP1-2 */
                vd_s_PwrCtrlSysPwrOnDisCharge();  /* STEP1-1 */

                /* STEP1-1��STEP1-2���������Ă���Ύ���STEP�ɐi�߂� */
                if ( ( u4_s_PwrCtrl_Sys_Bu_Dd_Mode_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN )
                  && ( u4_s_PwrCtrl_Sys_DisCharge_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN ) )
                {
                    u1_s_PwrCtrl_Sys_PwrOn_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
                }
                break;

            case (U1)PWRCTRL_COMMON_PROCESS_STEP2:
                vd_s_PwrCtrlSysPwrOnBoostDcdc();      /* STEP2-1 */
                vd_s_PwrCtrlSysPwrOnBoostAsilDcdc();  /* STEP2-2 */

                /* STEP2-1��STEP2-2���������Ă���Ύ���STEP�ɐi�߂� */
                if ( ( u4_s_PwrCtrl_Sys_Boost_Dcdc_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN )
                  && ( u4_s_PwrCtrl_Sys_Boost_Asil_Dcdc_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN ) )
                {
                    u1_s_PwrCtrl_Sys_PwrOn_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP3;
                }
                break;

            case (U1)PWRCTRL_COMMON_PROCESS_STEP3:
                vd_s_PwrCtrlSysPwrOnDdFreq();        /* STEP3-1 */
                vd_s_PwrCtrlSysPwrOnBoostAsilFreq(); /* STEP3-2 */
                vd_s_PwrCtrlSysPwrOnV33Peri();       /* STEP3-3 */
                vd_s_PwrCtrlSysPwrOnV33Asil();       /* STEP3-4 */

                /* STEP3-1~STEP3-4���������Ă���Ύ���STEP�ɐi�߂� */
                if ( ( u4_s_PwrCtrl_Sys_Dd_Freq_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN )
                  && ( u4_s_PwrCtrl_Sys_Boost_Asil_Freq_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN )
                  && ( u4_s_PwrCtrl_Sys_V33_Peri_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN )
                  && ( u4_s_PwrCtrl_Sys_V33_Asil_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN ) )
                {
                    u1_s_PwrCtrl_Sys_PwrOn_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP4;
                }
                break;

            case (U1)PWRCTRL_COMMON_PROCESS_STEP4:
                vd_s_PwrCtrlSysPwrOnV18();     /* STEP4-1 */
                vd_s_PwrCtrlSysPwrOnV18Asil(); /* STEP4-2 */
                vd_s_PwrCtrlSysPwrOnAudio();   /* STEP4-3 */
                vd_s_PwrCtrlSysPwrOnV11Asil(); /* STEP4-4 */
                vd_s_PwrCtrlSysPwrOnEizo();    /* STEP4-5 */

                /* STEP4-1~STEP4-5���������Ă���ΐ���N����ݒ� */
                if ( ( u4_s_PwrCtrl_Sys_V18_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN )
                  && ( u4_s_PwrCtrl_Sys_V18_Asil_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN )
                  && ( u4_s_PwrCtrl_Sys_Audio_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN )
                  && ( u4_s_PwrCtrl_Sys_V11_Asil_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN )
                  && ( u4_s_PwrCtrl_Sys_Eizo_Time == (U4)PWRCTRL_SYS_COUNTTIME_FIN ) )
                {
                    /* ����N����ݒ� */
                    u1_s_PwrCtrl_Sys_PwrOn_Step  = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
                    /* �v�������� */
                    u1_s_PwrCtrl_Sys_Pwr_Sts = (U1)PWRCTRL_SYS_NON;
                }
                break;

            case (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
                /* ����N�����͉������Ȃ� */
                break;

            default:
                /* �ُ�n�͖��l�� */
                break;
        }

        /* Port�X�V���� */
        vd_g_McuDevPwronWritePort();
    }
    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlSysPwrOffMainFunction
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlSysPwrOffMainFunction( void )
{
    U1   u1_t_read_v33_peri;

    u1_t_read_v33_peri   = (U1)STD_HIGH;

    /* SYS�N���d��OFF�v������ */
    if ( u1_s_PwrCtrl_Sys_Pwr_Sts == (U1)PWRCTRL_SYS_OFF )
    {
        /* ON����STEP�Ǘ�RAM,�^�C�}���N���A����ON2�T�ڂ����s�ł���悤�ɂ��� */
        u1_s_PwrCtrl_Sys_PwrOn_Step           = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
        u4_s_PwrCtrl_Sys_Bu_Dd_Mode_Time      = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_DisCharge_Time       = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_Boost_Dcdc_Time      = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_Boost_Asil_Dcdc_Time = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_Dd_Freq_Time         = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_Boost_Asil_Freq_Time = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_V33_Peri_Time        = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_V33_Asil_Time        = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_V18_Time             = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_V18_Asil_Time        = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_Audio_Time           = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_V11_Asil_Time        = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Sys_Eizo_Time            = (U4)PWRCTRL_SYS_WAIT_TIME_INIT;
        u4_s_PwrCtrl_Polling_V33PERI      = (U4)0U;
        u4_s_PwrCtrl_Polling_EIZO         = (U4)0U;
        u4_s_PwrCtrl_Polling_AUDIO        = (U4)0U;
        u4_s_PwrCtrl_waittim_usb          = (U4)0U;
        u4_s_PwrCtrl_waittim_pictic       = (U4)0U;
        u2_s_PwrCtrl_Polling_VIcRst       = (U2)0U;
        u2_s_PwrCtrl_Polling_GvifRxRst    = (U2)0U;
        u2_s_PwrCtrl_Polling_GvifTxRst    = (U2)0U;
        Mcu_OnStep_GNSS                   = (uint8)MCU_STEP_GNSS_PRE;
        Mcu_GNSS_LinkTimer                = (uint32)0U;
        Mcu_Fail_GNSS                     = (uint8)0U;

        u1_s_PwrCtrl_PowerIc_OVRALL       = (U1)PWRCTRL_COMMON_PROCESS_STEP1;

        switch ( u1_s_PwrCtrl_Sys_PwrOff_Step )
        {
            case (U1)PWRCTRL_COMMON_PROCESS_STEP1:
                vd_s_PwrCtrlSysPwrOffflw();

                /* STEP1���������Ă���ΐ���N����ݒ� */
                if ( u1_s_PwrCtrl_Sys_Off_SubStep == (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT )
                {
                    u1_s_PwrCtrl_Sys_PwrOff_Step = (U1)PWRCTRL_COMMON_PROCESS_STEP2;     /* ����ԂɑJ�� */
                }
                break;

            case (U1)PWRCTRL_COMMON_PROCESS_STEP2:
                if ( Mcu_PowerIc_OffTime != PWRCTRL_NOREDUN_WAIT_TIME_FIN )
                {
                    Mcu_PowerIc_OffTime++;
                }

                u1_t_read_v33_peri = Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_V33_PERI]); /* V33-PERI-ON�ǂݏo�� */
                if ( u1_t_read_v33_peri == (U1)STD_HIGH )
                {
                    Mcu_PowerIc_OffTime = (uint16)0U;       /* V33-PERI-ON=High�̏ꍇ�������ւ̑J�ڂ�}������ */
                }

                if ( Mcu_PowerIc_OffTime >= PWRCTRL_WAIT_POWERIC_100MS )
                {
                    vd_g_McuDevPwronSetPort(MCU_PORT_PIC_POFF , MCU_DIO_LOW);     /* P-IC�d������ */
                    Mcu_PowerIc_OffTime = (uint16)0U;                           /* �^�C�}�N���A */
                    /* STEP2���������Ă���ΐ���N����ݒ� */
                    u1_s_PwrCtrl_Sys_PwrOff_Step     =   (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
                    /* �v�������� */
                    u1_s_PwrCtrl_Sys_Pwr_Sts = (U1)PWRCTRL_SYS_NON;
                }
                break;
            case (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
                /* ����I�����͉������Ȃ� */
                break;
            default:
                /* �ُ�n�͖��l�� */
                break;
        }
        
        /* Port�X�V���� */
        vd_g_McuDevPwronWritePort();
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnBuDdMode
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnBuDdMode( void )
{
    if(u4_s_PwrCtrl_Sys_Bu_Dd_Mode_Time == (U4)PWRCTRL_SYS_WAIT_BU_DD_MODE_TIME){
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_BU_DD_MODE, MCU_DIO_HIGH);
        u4_s_PwrCtrl_Sys_Bu_Dd_Mode_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_Bu_Dd_Mode_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_Bu_Dd_Mode_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnDisCharge
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnDisCharge( void )
{
    if(u4_s_PwrCtrl_Sys_DisCharge_Time == (U4)PWRCTRL_SYS_WAIT_DISCHARGE_TIME){ /* ���d�҂����Ԃ��o�߂����� */
        u4_s_PwrCtrl_Sys_DisCharge_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;        /* �o�߂��Ă���Όv��������ݒ� */
    }
    
    if(u4_s_PwrCtrl_Sys_DisCharge_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_DisCharge_Time++;
    }
    
    return;

}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnBoostDcdc
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnBoostDcdc( void )
{
    if(u4_s_PwrCtrl_Sys_Boost_Dcdc_Time == (U4)PWRCTRL_SYS_WAIT_BOOST_DCDC_TIME){    /* �E�F�C�g�^�C�����o�߂����� ��r�Ώۂ�0�ݒ�̂��߈�v�Ŋm�F */
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_BOOST_DCDC, MCU_DIO_HIGH);
        u4_s_PwrCtrl_Sys_Boost_Dcdc_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_Boost_Dcdc_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_Boost_Dcdc_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnBoostAsilDcdc
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnBoostAsilDcdc( void )
{
    if(u4_s_PwrCtrl_Sys_Boost_Asil_Dcdc_Time == (U4)PWRCTRL_SYS_WAIT_BOOST_ASIL_DCDC_TIME){    /* �E�F�C�g�^�C�����o�߂����� ��r�Ώۂ�0�ݒ�̂��߈�v�Ŋm�F */
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_ASIL_DCDC, MCU_DIO_HIGH);
        u4_s_PwrCtrl_Sys_Boost_Asil_Dcdc_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_Boost_Asil_Dcdc_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_Boost_Asil_Dcdc_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnDdFreq
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnDdFreq( void )
{
    U2 dd_freq_duty;

    if(u4_s_PwrCtrl_Sys_Dd_Freq_Time == (U4)PWRCTRL_SYS_WAIT_DD_FREQ_TIME){
        dd_freq_duty = PWRCTRL_SYS_PWM_DUTYCYCLE(5000U);    /* 50% */
        vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_00_DDC_FREQ, (U2)PWRCTRL_SYS_PWM_PERIOD, dd_freq_duty);
        u4_s_PwrCtrl_Sys_Dd_Freq_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_Dd_Freq_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_Dd_Freq_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnBoostAsilFreq
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnBoostAsilFreq( void )
{
    U2 boost_asil_duty;

    if(u4_s_PwrCtrl_Sys_Boost_Asil_Freq_Time == (U4)PWRCTRL_SYS_WAIT_BOOST_ASIL_FREQ_TIME){
        boost_asil_duty = PWRCTRL_SYS_PWM_DUTYCYCLE(5000U);    /* 50% */
        vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_02_DDC_ASIL_FREQ, (U2)PWRCTRL_SYS_PWM_PERIOD, boost_asil_duty);
        u4_s_PwrCtrl_Sys_Boost_Asil_Freq_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_Boost_Asil_Freq_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_Boost_Asil_Freq_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnV33Peri
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnV33Peri( void )
{
    if(u4_s_PwrCtrl_Sys_V33_Peri_Time == (U4)PWRCTRL_SYS_WAIT_V33_PERI_TIME){
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_V33_PERI, MCU_DIO_HIGH);
        u4_s_PwrCtrl_Sys_V33_Peri_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_V33_Peri_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_V33_Peri_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnV33Asil
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnV33Asil( void )
{
    if(u4_s_PwrCtrl_Sys_V33_Asil_Time == (U4)PWRCTRL_SYS_WAIT_V33_ASIL_TIME){ 
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_V33_ASIL, MCU_DIO_HIGH);
        u4_s_PwrCtrl_Sys_V33_Asil_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_V33_Asil_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_V33_Asil_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnV18
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnV18( void )
{
    if(u4_s_PwrCtrl_Sys_V18_Time == (U4)PWRCTRL_SYS_WAIT_V18_TIME){ 
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_V18, MCU_DIO_HIGH);
        u4_s_PwrCtrl_Sys_V18_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_V18_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_V18_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnV18Asil
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnV18Asil( void )
{
    if(u4_s_PwrCtrl_Sys_V18_Asil_Time == (U4)PWRCTRL_SYS_WAIT_V18_ASIL_TIME){ 
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_V18_ASIL, MCU_DIO_HIGH);
        u4_s_PwrCtrl_Sys_V18_Asil_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_V18_Asil_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_V18_Asil_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnAudio
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnAudio( void )
{
    if(u4_s_PwrCtrl_Sys_Audio_Time == (U4)PWRCTRL_SYS_WAIT_AUDIO_TIME){ 
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_AUDIO, MCU_DIO_HIGH);
        u4_s_PwrCtrl_Sys_Audio_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_Audio_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_Audio_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnV11Asil
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnV11Asil( void )
{
    if(u4_s_PwrCtrl_Sys_V11_Asil_Time == (U4)PWRCTRL_SYS_WAIT_V11_ASIL_TIME){ 
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_V11_ASIL, MCU_DIO_HIGH);
        u4_s_PwrCtrl_Sys_V11_Asil_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_V11_Asil_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_V11_Asil_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOnEizo
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOnEizo( void )
{
    if(u4_s_PwrCtrl_Sys_Eizo_Time == (U4)PWRCTRL_SYS_WAIT_EIZO_TIME){ 
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_EIZO, MCU_DIO_HIGH);
        u4_s_PwrCtrl_Sys_Eizo_Time = (U4)PWRCTRL_SYS_COUNTTIME_FIN;
    }
    
    if(u4_s_PwrCtrl_Sys_Eizo_Time != (U4)PWRCTRL_SYS_COUNTTIME_FIN){
        u4_s_PwrCtrl_Sys_Eizo_Time++;
    }
    
    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlSysPwrOffflw
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlSysPwrOffflw( void )
{
    switch (u1_s_PwrCtrl_Off_SubStep)
    {
    case PWRCTRL_COMMON_PROCESS_STEP1:
        /* ����[�q�̑O�ɒ[�qOFF����K�v��������� */
        vd_g_McuDevPwronSetPort(MCU_PORT_GVIF_CAN_RST                   , MCU_DIO_LOW); /* AUDIO-ON 1ms�O */
        vd_g_McuDevPwronSetPort(MCU_PORT_GVIF_CDISP_RST                 , MCU_DIO_LOW); /* AUDIO-ON 1ms�O */

        u1_s_PwrCtrl_Off_SubStep    = (U1)PWRCTRL_COMMON_PROCESS_STEP2;
        break;

    case PWRCTRL_COMMON_PROCESS_STEP2:
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_V18            , MCU_DIO_LOW);
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_V18_ASIL       , MCU_DIO_LOW);
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_AUDIO          , MCU_DIO_LOW);
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_V11_ASIL       , MCU_DIO_LOW);
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_EIZO           , MCU_DIO_LOW);
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_V33_PERI       , MCU_DIO_LOW);
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_V33_ASIL       , MCU_DIO_LOW);
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_BU_DD_MODE     , MCU_DIO_LOW);
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_BOOST_DCDC     , MCU_DIO_LOW);
        vd_g_McuDevPwronSetPort(PWRCTRL_CFG_PRIVATE_PORT_ASIL_DCDC      , MCU_DIO_LOW);

        vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_00_DDC_FREQ , (U2)PWRCTRL_SYS_PWM_PERIOD_OFF, (U2)0U);
        vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_02_DDC_ASIL_FREQ , (U2)PWRCTRL_SYS_PWM_PERIOD_OFF, (U2)0U);

        u1_s_PwrCtrl_Off_SubStep    = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
        break;

    case PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
        /* do nothing */
        break;

    default:
        u1_s_PwrCtrl_Off_SubStep = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
        break;
    }
}

/*****************************************************************************
  Function      : vd_g_McuDev_Pwron
  Description   : 
  param[in/out] : 
  return        : -
  Note          : �f�o�C�XON���� 
*****************************************************************************/
void            vd_g_McuDev_Pwron(void)
{
    U1      u1_t_pwr;

    if (u1_g_PwrCtrl_NoRedun_Pwr_Sts == (U1)PWRCTRL_NOREDUN_STS_ON) {
        /* �Ώۃ|�[�g�̃|�[�����O�ƃ^�C�}�J�E���g�J�n���f */
        vd_s_McuDev_Polling_V33PERI();
        vd_s_McuDev_Polling_EIZO();
        vd_s_McuDev_Polling_AUDIO();

        /* �d����Ԏ擾 */
        u1_t_pwr    = u1_g_PowerSup_ModeState();

        /* �A�v��ON���� */
        vd_s_McuDev_Pwron_USB(u1_t_pwr);            /* USB�A�_�v�^�ڑ����m */
        vd_s_McuDev_Pwron_PictIC(u1_t_pwr);         /* �f��IC(ML86294)���� */
        vd_s_McuDev_Pwron_GVIFRx();                 /* GVIF3��M(CXD4984ER)���� */
        vd_s_McuDev_Pwron_GVIFTx_CDisp(u1_t_pwr);   /* GVIF3���M(CXD4937/57)���� C-Disp */
        vd_s_McuDev_Pwron_Mic(u1_t_pwr);            /* �}�C�N�d������ */
        vd_s_McuDev_Pwron_Ant(u1_t_pwr);            /* �A���e�i�d������ */
        vd_s_McuDev_SoundMUTE();                    /* ����MUTE���� */
        vd_s_McuDev_Pwron_Most(u1_t_pwr);           /* MOST(v2)�V�X�e������ */
        vd_s_McuDev_Pwron_XMTuner();                /* XM TUNER���� */
        Mcu_Dev_Pwron_GNSS();                       /* GNSS���� */
        vd_s_McuDev_Pwron_PowerIc(u1_t_pwr);        /* Power-IC���� */
        vd_s_McuDev_Pwron_Gyro();                   /* �W���C���E�����x�Z���T(SMI230)���� */

        /* Port�X�V���� */
        vd_g_McuDevPwronWritePort();
    }
}

/*****************************************************************************
  Function      : u1_t_Pwron_TimChk
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
static U1       u1_t_Pwron_TimChk(const U4 u1_a_TIMCNT, const U4 u1_a_TIMFIN)
{
    U1   u1_t_ret;
    u1_t_ret =  (U1)FALSE;

    if(u1_a_TIMCNT  >  u1_a_TIMFIN){
        u1_t_ret =  (U1)TRUE;
    }

    return(u1_t_ret);
}

/*****************************************************************************
  Function      : vd_s_McuDev_Polling_V33PERI
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
static void     vd_s_McuDev_Polling_V33PERI(void)
{
    Dio_LevelType   dl_t_port;

    dl_t_port   = Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_V33_PERI]);

    if(dl_t_port == (Dio_LevelType)STD_LOW){
        u4_s_PwrCtrl_Polling_V33PERI    = (U4)0U;
    }
    else if((dl_t_port == (Dio_LevelType)STD_HIGH) &&
            (u4_s_PwrCtrl_Polling_V33PERI < (U4)PWRCTRL_SYS_COUNTTIME_FIN)){
        u4_s_PwrCtrl_Polling_V33PERI++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : vd_s_McuDev_Polling_EIZO
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
static void     vd_s_McuDev_Polling_EIZO(void)
{
    Dio_LevelType   dl_t_port;

    dl_t_port   = Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_EIZO]);

    if(dl_t_port == (Dio_LevelType)STD_LOW){
        u4_s_PwrCtrl_Polling_EIZO =   (U4)0U;
    }
    else if((dl_t_port == (Dio_LevelType)STD_HIGH) &&
            (u4_s_PwrCtrl_Polling_EIZO < (U4)PWRCTRL_SYS_COUNTTIME_FIN)){
        u4_s_PwrCtrl_Polling_EIZO++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : vd_s_McuDev_Polling_AUDIO
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
static void     vd_s_McuDev_Polling_AUDIO(void)
{
    Dio_LevelType   dl_t_port;

    dl_t_port   = Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_AUDIO]);

    if(dl_t_port == (Dio_LevelType)STD_LOW){
        u4_s_PwrCtrl_Polling_AUDIO =   (U4)0U;
    }
    else if((dl_t_port == (Dio_LevelType)STD_HIGH) &&
            (u4_s_PwrCtrl_Polling_AUDIO < (U4)PWRCTRL_SYS_COUNTTIME_FIN)){
        u4_s_PwrCtrl_Polling_AUDIO++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : vd_s_McuDev_Pwron_USB
  Description   : 
  param[in/out] : 
  return        : -
  Note          : "�X�^���o�C" �������� "�k�ޑ��s"�ȊO�֑J�ڌ�100ms�o�߂�USB-LED-ON = Hi
*****************************************************************************/
static void     vd_s_McuDev_Pwron_USB(const U1 u1_a_PWR)
{
    static const U4 u4_s_WAITTIME_USB   = (U4)(100U / PWRCTRL_CFG_TASK_TIME);

    U1      u1_t_timchk;

    if((u1_a_PWR != (U1)POWER_MODE_STATE_STANDBY) && (u1_a_PWR != (U1)POWER_MODE_STATE_EDS)){
        /* "�X�^���o�C" �������� "�k�ޑ��s"�ȊO�̓J�E���^�C���N�������g */
        if(u4_s_PwrCtrl_waittim_usb < U4_MAX){
            u4_s_PwrCtrl_waittim_usb++;
        }
    }
    else{
        /* �J�E���^�N���A */
        u4_s_PwrCtrl_waittim_usb    = (U4)0U;
    }

    u1_t_timchk     = u1_t_Pwron_TimChk(u4_s_PwrCtrl_waittim_usb, u4_s_WAITTIME_USB);

    if(u1_t_timchk ==  (U1)TRUE){
        vd_g_McuDevPwronSetPort(MCU_PORT_USB_LED_ON , MCU_DIO_HIGH);
        u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_USB_BIT;
    }
}

/*****************************************************************************
  Function      : vd_s_McuDev_Pwron_PictIC
  Description   : 
  param[in/out] : 
  return        : -
  Note          : EIZO-ON=H ���u�����ڃI�t�N���v�܂��́u�����ڃI���N���v�܂��́uOTA�v�֑J��
*****************************************************************************/
static void     vd_s_McuDev_Pwron_PictIC(const U1 u1_a_PWR)
{
    static const U4 u4_s_WAITTIME_PICTIC    = (U4)(40U / PWRCTRL_CFG_TASK_TIME);

    Dio_LevelType   dl_t_port;
    U1              u1_t_timchk;

    dl_t_port   = Dio_ReadChannel(Mcu_Dio_PortId[PWRCTRL_CFG_PRIVATE_PORT_EIZO]);

    if((dl_t_port == (Dio_LevelType)STD_HIGH) && 
       ((u1_a_PWR == (U1)POWER_MODE_STATE_APPON) || (u1_a_PWR == (U1)POWER_MODE_STATE_APPOFF))){
        /* EIZO-ON=H ���u�����ڃI�t�N���v�܂��́u�����ڃI���N���v�܂��́uOTA�v�ւŃJ�E���^�C���N�������g */
        if(u4_s_PwrCtrl_waittim_pictic < U4_MAX){
            u4_s_PwrCtrl_waittim_pictic++;
        }
    }
    else{
        /* �J�E���^�N���A */
        u4_s_PwrCtrl_waittim_pictic    = (U4)0U;
    }

    u1_t_timchk     = u1_t_Pwron_TimChk(u4_s_PwrCtrl_waittim_pictic, u4_s_WAITTIME_PICTIC);

    if(u1_t_timchk  == (U1)TRUE){
        vd_g_McuDevPwronSetPort(MCU_PORT_V_IC_RST , MCU_DIO_HIGH);
        u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_PICTIC_BIT;
    }

    /* [�f��IC�N������]�V�[�g�̏��������� �ɑ��� */
}

/*****************************************************************************
  Function      : vd_s_McuDev_Pwron_GVIFRx
  Description   : 
  param[in/out] : 
  return        : -
  Note          : AUDIO-ON = Hi����15ms��Ɂu/GVIF-RX(CAM)-RST = Hi�v
*****************************************************************************/
static void     vd_s_McuDev_Pwron_GVIFRx(void)
{
    static const U4 u4_s_WAITTIME_GVIFRX    = (U4)(15U / PWRCTRL_CFG_TASK_TIME);

    U1      u1_t_timchk;

    u1_t_timchk = u1_t_Pwron_TimChk(u4_s_PwrCtrl_Polling_AUDIO, u4_s_WAITTIME_GVIFRX);

    if(u1_t_timchk == (U1)TRUE){
        vd_g_McuDevPwronSetPort(MCU_PORT_GVIF_CAN_RST , MCU_DIO_HIGH);
        u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_GVIFRX_BIT;
    }
}

/*****************************************************************************
  Function      : vd_s_McuDev_Pwron_GVIFTx_CDisp
  Description   : 
  param[in/out] : 
  return        : -
  Note          : ���Z�b�g�����͉��L�������ׂĂ𖞑�����Ƃ��ɂɁu/GVIF-TX(C-DISP)-RST = Hi�v
                  �E�N�������Z�b�g�����^�C�~���O(t1)�ȏ�o�߂��Ă���
                  �E�ԗ��d���X�e�[�g��"�����ڃI���N��"�܂���"�����ڃI�t�N��"�܂���"OTA"�̏�ԂɑJ�ڂ����Ƃ�
*****************************************************************************/
static void     vd_s_McuDev_Pwron_GVIFTx_CDisp(const U1 u1_a_PWR)
{
    static const U4 u4_s_WAITTIME_GVIFTX    = (U4)(10U / PWRCTRL_CFG_TASK_TIME);

    U1          u1_t_timchk;

    u1_t_timchk     = u1_t_Pwron_TimChk(u4_s_PwrCtrl_Polling_AUDIO, u4_s_WAITTIME_GVIFTX);

    if((u1_t_timchk ==  (U1)TRUE) &&
       ((u1_a_PWR == (U1)POWER_MODE_STATE_APPON) || (u1_a_PWR == (U1)POWER_MODE_STATE_APPOFF))){
        vd_g_McuDevPwronSetPort(MCU_PORT_GVIF_CDISP_RST , MCU_DIO_HIGH);
        u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_GVIFTX_BIT;
    }
}

/*****************************************************************************
  Function      : vd_s_McuDev_Pwron_Mic
  Description   : 
  param[in/out] : 
  return        : -
  Note          : V33-PERI-ON = Hi ���� 100ms�� & �u"�X�^���o�C" �������� "�k�ޑ��s" �ȊO�v�ɑJ�ڌ�� MIC-ON = Hi
*****************************************************************************/
static void     vd_s_McuDev_Pwron_Mic(const U1 u1_a_PWR)
{
    static const U4 u4_s_WAITTIME_MIC   = (U4)(100U / PWRCTRL_CFG_TASK_TIME);

    U1      u1_t_timchk;

   u1_t_timchk  = u1_t_Pwron_TimChk(u4_s_PwrCtrl_Polling_V33PERI, u4_s_WAITTIME_MIC);

    if((u1_t_timchk ==  (U1)TRUE) && (u1_a_PWR != (U1)POWER_MODE_STATE_EDS)){
        vd_g_McuDevPwronSetPort(MCU_PORT_MIC_ON , MCU_DIO_HIGH);
        u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_MIC_BIT;
    }
}

/*****************************************************************************
  Function      : vd_s_McuDev_Pwron_Ant
  Description   : 
  param[in/out] : 
  return        : -
  Note          : V33-PERI-ON = Hi����100ms�� ���� �u��Ԓ�(������ON)/�t���N���v�ɑJ�ڌ��
                  AM/FM-ANT-ON,GPS-ANT-ON,DAB-ANT-ON = Hi
*****************************************************************************/
static void     vd_s_McuDev_Pwron_Ant(const U1 u1_a_PWR)
{
    static const U4 u4_s_WAITTIME_ANT   = (U4)(100U / PWRCTRL_CFG_TASK_TIME);

    U1      u1_t_timchk;

    u1_t_timchk     =   u1_t_Pwron_TimChk(u4_s_PwrCtrl_Polling_V33PERI, u4_s_WAITTIME_ANT);

    if(u1_t_timchk ==  (U1)TRUE){
        /* GNSS�A���e�i */
        vd_g_McuDevPwronSetPort(MCU_PORT_GPS_ANT_ON , MCU_DIO_HIGH);

        if(u1_a_PWR == (U1)POWER_MODE_STATE_APPON){
            /* AMFM���W�I */
            vd_g_McuDevPwronSetPort(MCU_PORT_AMFM_ANT_ON , MCU_DIO_HIGH);
            /* DAB�A���e�i(���{/�k�Ďd�����ȊO�̂�) */
#ifdef SYS_PWR_ANT_DAB
            vd_g_McuDevPwronSetPort(MCU_PORT_DAB_ANT_ON , MCU_DIO_HIGH);
#endif
            /* DTV�A���e�i(���{�d�����̂�) */
#ifdef SYS_PWR_ANT_DTV
            vd_g_McuDevPwronSetPort(MCU_PORT_DTV_ANT_ON , MCU_DIO_HIGH);
#endif
        }

        u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_ANT_BIT;
    }
}

/*****************************************************************************
  Function      : vd_s_McuDev_SoundMUTE
  Description   : 
  param[in/out] : 
  return        : -
  Note          : PowerIC�ŋN���������{�̂��ߏ����Ȃ� �\���݌v
*****************************************************************************/
static void     vd_s_McuDev_SoundMUTE(void)
{
}

/*****************************************************************************
  Function      : vd_s_McuDev_Pwron_Most
  Description   : 
  param[in/out] : 
  return        : -
  Note          : �����ڃI��/�I�t�N����MOST-WAKE-ON=Hi
                  MOST-WAKE-ON=Hi��0ms��SiP��MOST�N����Ԃ�ʒm
                  �b��Ή�����
*****************************************************************************/
static void     vd_s_McuDev_Pwron_Most(const U1 u1_a_PWR)
{
    if((u1_a_PWR == (U1)POWER_MODE_STATE_APPON) || (u1_a_PWR == (U1)POWER_MODE_STATE_APPOFF)){
        vd_g_McuDevPwronSetPort(MCU_PORT_MOST_WAKE_ON , MCU_DIO_HIGH);
        u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_MOST_BIT;
    }

    /* �b��Ή��FSPI�ʐM�n������(OS�ԒʐM�R�}���h�s���̂���) */
}

/*****************************************************************************
  Function      : vd_s_McuDev_Pwron_XMTuner
  Description   : 
  param[in/out] : 
  return        : -
  Note          : V33-PERI-ON=H��XM-ON,V33-PERI-ON=H����1010ms��XM-SHDN=H
                  �b��Ή�����
*****************************************************************************/
static void     vd_s_McuDev_Pwron_XMTuner(void)
{
    static const U4 u4_s_WAITTIME_XM_ON     = (U4)(PWRCTRL_CFG_TASK_TIME / PWRCTRL_CFG_TASK_TIME);
    static const U4 u4_s_WAITTIME_XM_SHDN   = (U4)(1010U / PWRCTRL_CFG_TASK_TIME);

    U1      u1_t_timchk_xmon;
    U1      u1_t_timchk_xmshdn;
    
    u1_t_timchk_xmon    = u1_t_Pwron_TimChk(u4_s_PwrCtrl_Polling_V33PERI, u4_s_WAITTIME_XM_ON);
    u1_t_timchk_xmshdn  = u1_t_Pwron_TimChk(u4_s_PwrCtrl_Polling_V33PERI, u4_s_WAITTIME_XM_SHDN);

    if(u1_t_timchk_xmon == (U1)TRUE){
        vd_g_McuDevPwronSetPort(MCU_PORT_XM_ON , MCU_DIO_HIGH);
    }
    if(u1_t_timchk_xmshdn == (U1)TRUE){
#ifdef SYS_PWR_ANT_XM_SHDN
        vd_g_McuDevPwronSetPort(MCU_PORT_XM_SHDN , MCU_DIO_HIGH);
#endif
        /* �b��Ή��FSPI�ʐM�n�͖�����(OS�ԃR�}���h�s��) */
    }
    if((u1_t_timchk_xmon == (U1)TRUE) && (u1_t_timchk_xmshdn == (U1)TRUE)){
        u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_XMTUNER_BIT;
    }
}
/*****************************************************************************
  Function      : vd_s_McuDev_Pwron_PowerIc
  Description   : 
  param[in/out] : 
  return        : -
  Note          : Power-IC�ʏ�N������
                  �b��Ή�����
*****************************************************************************/
static void     vd_s_McuDev_Pwron_PowerIc(const U1 u1_a_PWR)
{
    static const U4 u4_s_WAITTIME_POWERIC    = (U4)(PWRCTRL_CFG_TASK_TIME / PWRCTRL_CFG_TASK_TIME);

    U1              u1_t_logexi;        /* P-IC�j�󃍃O�L�� */
    U1              u1_t_timchk;        /* V33-PERI-ON=HI�o�ߎ��Ԕ��� */
    Dio_LevelType   dl_t_port;

    switch (u1_s_PwrCtrl_PowerIc_OVRALL) {
        case PWRCTRL_COMMON_PROCESS_STEP1:
            /* Power-IC�j�󃍃O�擾���� */
            /*****************************************************************************
            �b��Ή�
            P-IC�j�󃍃O�͏�ɖ������Ő��䂷��
            *****************************************************************************/
            u1_t_logexi = (U1)FALSE;

            if(u1_t_logexi == (U1)TRUE) {  /* P-IC�j�󃍃O���� */
                /* Power-IC�j��̃��O���c���Ă���ꍇ��Power-IC���N�������Ȃ� */
                u1_s_PwrCtrl_PowerIc_OVRALL = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;
            }
            else {  /* �j�󃍃O�Ȃ� */
                u1_s_PwrCtrl_PowerIc_OVRALL = (U1)PWRCTRL_COMMON_PROCESS_STEP2;  /* ����ԂɑJ�� */
            }
            break;

        case PWRCTRL_COMMON_PROCESS_STEP2:
            u1_t_timchk = u1_t_Pwron_TimChk(u4_s_PwrCtrl_Polling_V33PERI, u4_s_WAITTIME_POWERIC);  /* V33-PERI-ON=HI���� */

            if((u1_t_timchk == (U1)TRUE) && (u1_a_PWR == (U1)POWER_MODE_STATE_PARK)){
                vd_g_McuDevPwronSetPort(MCU_PORT_PIC_POFF , MCU_DIO_HIGH);          /* P-IC�d���������� */
                u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_POWERIC_BIT;
                u1_s_PwrCtrl_PowerIc_OVRALL = (U1)PWRCTRL_COMMON_PROCESS_STEP_CMPLT;     /* ����ԂɑJ�� */
            }
            break;

        case PWRCTRL_COMMON_PROCESS_STEP_CMPLT:
            /* PowerIC=OFF���m���� */
            dl_t_port   = Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_PIC_POFF]);
            if(dl_t_port == (Dio_LevelType)STD_LOW){
                u1_s_PwrCtrl_PowerIc_OVRALL = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
            }
            break;

        default:
            u1_s_PwrCtrl_PowerIc_OVRALL = (U1)PWRCTRL_COMMON_PROCESS_STEP1;
            break;
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GNSS
  Description   : 
  param[in/out] : 
  return        : -
  Note          : �V�X���b��Ή�����
*****************************************************************************/
void    Mcu_Dev_Pwron_GNSS( void ){
    static const uint32 MCU_PWRON_TIME_GNSS_T8  =   (uint32)(100U * GPT_FRT_1US);     /* typ 100ms /GPS-RST�̃��Z�b�g���ԕ� */
    static const uint8  MCU_PWRON_FAIL_MAX      =   (uint32)(2U);       /* PMONI Low 2��ڌ��m��Low�p�� */

    uint8   mcu_dio_ret;
    uint32  mcu_frt_elpsd;

    mcu_frt_elpsd   = (uint32)0U;
    mcu_dio_ret     = (uint8)STD_HIGH;

    switch (Mcu_OnStep_GNSS) {
        case MCU_STEP_GNSS_PRE:
            /* B-ON Init��MCU����̋N�_�Ƃ��t���[�����^�C�}�Ōo�ߎ��Ԃ��Ď����� */
            mcu_frt_elpsd = u4_g_Gpt_FrtGetUsElapsed(Mcu_frt_stamp);

            if(mcu_frt_elpsd > MCU_PWRON_TIME_GNSS_T8){
                vd_g_McuDevPwronSetPort(MCU_PORT_GPS_RST , MCU_DIO_HIGH);
                Mcu_OnStep_GNSS = MCU_STEP_GNSS_INI_CHK;        /* ����ԂɑJ�� */
            }
            break;
        case MCU_STEP_GNSS_INI_CHK:
            if(Mcu_GNSS_LinkTimer != (uint32)PWRCTRL_SYS_COUNTTIME_FIN){
                Mcu_GNSS_LinkTimer++;
            }
            if(Mcu_GNSS_LinkTimer >= (uint32)PWRCTRL_WAIT_GNSS_400MS){
                mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GPS_PMONI]);
                if(mcu_dio_ret == (uint8)STD_HIGH){
                    /* ���������s */
                    vd_g_McuDevPwronSetPort(MCU_PORT_GPS_RST , MCU_DIO_LOW);
                    Mcu_OnStep_GNSS = (uint8)MCU_STEP_GNSS_FIN;         /* ����ԂɑJ�� */
                    Mcu_GNSS_LinkTimer   = (uint32)0U;                       /* �^�C�}�N���A */
                }
                else {
                    /* ���������� Hibernate��� */
                    Mcu_OnStep_GNSS = (uint8)MCU_STEP_GNSS_PRECHK;      /* ����ԂɑJ�� */
                    Mcu_GNSS_LinkTimer   = (uint32)0U;                       /* �^�C�}�N���A */
                }
            }
            break;
        case MCU_STEP_GNSS_PRECHK:
            mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_MM_STBY_N]);    /* t3��min0ms�̂��߁Await�����������Ɏ����������{ */
            if(mcu_dio_ret == (uint8)STD_HIGH){
                /* �������O�`�F�b�N�̓��e�s���̂���skip */
                //if(�������O�`�F�b�N=OK){
                    vd_g_McuDevPwronSetPort(MCU_PORT_GPS_PCTL , MCU_DIO_HIGH);
                    Mcu_OnStep_GNSS = (uint8)MCU_STEP_GNSS_POSTCHK;         /* ����ԂɑJ�� */
                //}
            }
            break;
        case MCU_STEP_GNSS_POSTCHK:
            if(Mcu_GNSS_LinkTimer != (uint32)PWRCTRL_SYS_COUNTTIME_FIN){
                Mcu_GNSS_LinkTimer++;
            }
            if(Mcu_GNSS_LinkTimer >= (uint32)PWRCTRL_WAIT_GNSS_550MS){
                /* �N����`�F�b�N */
                mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GPS_PMONI]);
                if(mcu_dio_ret == (uint8)STD_HIGH){
                    /* �N����`�F�b�N�����F/GPS-RST=H�ێ� */
                    /* do nothing */
                }
                else {
                    /* �N����`�F�b�N���s�F/GPS-RST=H��L */
                    vd_g_McuDevPwronSetPort(MCU_PORT_GPS_RST , MCU_DIO_LOW);
                }
                u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_GNSS_BIT;
                Mcu_OnStep_GNSS = (uint8)MCU_STEP_GNSS_POLING;      /* ����ԂɑJ�� */
                Mcu_GNSS_LinkTimer   = (uint32)0U;                       /* �^�C�}�N���A */
            }
            break;
        case MCU_STEP_GNSS_POLING:
            mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_MM_STBY_N]);
            if(mcu_dio_ret == (U1)STD_LOW){
                Mcu_Fail_GNSS   = (U1)0U;
                Mcu_OnStep_GNSS = (uint8)MCU_STEP_GNSS_WAIT;
            }
            else{
                mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GPS_PMONI]);  /* ����I�Ƀ|�[�����O */
                if(mcu_dio_ret == (uint8)STD_LOW){
                    /* t17��min0ms�̂��߁Await�����������Ɏ����������{ */
                    /* /GPS-RST,GPS-PCTL��H��L */
                    vd_g_McuDevPwronSetPort(MCU_PORT_GPS_RST , MCU_DIO_LOW);
                    vd_g_McuDevPwronSetPort(MCU_PORT_GPS_PCTL , MCU_DIO_LOW);

                    /* ���s�񐔃J�E���g */
                    Mcu_Fail_GNSS++;

                    if(Mcu_Fail_GNSS >= MCU_PWRON_FAIL_MAX){    /* PMONI Low 2��ڌ��m��Low�p�� */
                        Mcu_OnStep_GNSS = (uint8)MCU_STEP_GNSS_FIN;         /* ����ԂɑJ�� */
                    }
                    else{
                        Mcu_OnStep_GNSS = (uint8)MCU_STEP_GNSS_PRE;         /* ����ԂɑJ�� */
                    }
                }
            }
            break;
        case MCU_STEP_GNSS_FIN:
            mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_MM_STBY_N]);
            if(mcu_dio_ret == (U1)STD_LOW){
                Mcu_OnStep_GNSS = (uint8)MCU_STEP_GNSS_WAIT;
            }
            break;
        case MCU_STEP_GNSS_WAIT:
            mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_MM_STBY_N]);
            if(mcu_dio_ret == (U1)STD_HIGH){
                Mcu_Fail_GNSS   = (U1)0U;
                Mcu_GNSS_LinkTimer  = (uint32)0U;
                Mcu_frt_stamp[GPT_FRT_USELPSD_BASE] = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
                Mcu_OnStep_GNSS = (uint8)MCU_STEP_GNSS_PRE;
            }
            break;
        default:
            /* do nothing */
            break;
    }
}

/*****************************************************************************
  Function      : vd_s_McuDev_Pwron_Gyro
  Description   : 
  param[in/out] : 
  return        : -
  Note          : VM2�Ŏ��{���邽�ߏ����Ȃ�
*****************************************************************************/
static void     vd_s_McuDev_Pwron_Gyro(void)
{
    Dio_LevelType dl_t_port;

    dl_t_port =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_SENSOR_ON]);
    if(dl_t_port == (Dio_LevelType)STD_HIGH){
        u2_g_PwrCtrl_OffSts &= ~(U2)PWROFF_GYRO_BIT;
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_Init
  Description   : 
  param[in/out] : 
  return        : -
  Note          : �f��IC�N������
*****************************************************************************/
void    Mcu_Dev_Pwron_EizoIc_Init( void ){
    /* ��ԑJ�ږ������̂��߉��R�[�h */
    /* [�f��IC�N������]�V�[�g�̏��������� */
    /* 6.2 ���������� */
    Mcu_Dev_Pwron_EizoIc_Polling_VIcRst();

    /* 7.���W�X�^�ݒ� */
    Mcu_Dev_Pwron_EizoIc_RegSetting();

    /* 6.3 SiP�f���\���Ɋւ��鏈�� */
    Mcu_Dev_Pwron_EizoIc_PctDspSetting();

    /* 6.5.1.1 �N�����̃J�����G�C�Y�\���Ɋւ���ݒ�t���[ */
    Mcu_Dev_Pwron_EizoIc_CamDspSetting();
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_Polling_VIcRst
  Description   : 
  param[in/out] : 
  return        : -
  Note          : /V-IC-RST=Hi �Ď�
*****************************************************************************/
void    Mcu_Dev_Pwron_EizoIc_Polling_VIcRst( void ){
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_V_IC_RST]);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        u2_s_PwrCtrl_Polling_VIcRst          = (uint32)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (u2_s_PwrCtrl_Polling_VIcRst < (uint32)PWRCTRL_SYS_COUNTTIME_FIN)){
        u2_s_PwrCtrl_Polling_VIcRst++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_RegSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 7.���W�X�^�ݒ�
*****************************************************************************/
void    Mcu_Dev_Pwron_EizoIc_RegSetting( void ){
    static const uint32 MCU_PWRON_TIME_EIZOIC  =   (PWRCTRL_CFG_TASK_TIME / PWRCTRL_CFG_TASK_TIME);    /* min:1ms */

    uint8   mcu_time_chk;

    mcu_time_chk    =   u1_t_Pwron_TimChk(u2_s_PwrCtrl_Polling_VIcRst, MCU_PWRON_TIME_EIZOIC);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_EizoIc_SetReg();
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_SetReg
  Description   : 
  param[in/out] : 
  return        : -
  Note          : �f��IC���������� ���W�X�^�ݒ�
*****************************************************************************/
void Mcu_Dev_Pwron_EizoIc_SetReg( void ){
    /* IF�s���̂��ߖ��ݒ� EizoIc_Init.h�ɒ�`�����萔�z��(Eizo_Init_RegAdd,Eizo_Init_RegSet)��p���Đݒ肷�� */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_PctDspSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 6.3 SiP�f���\���Ɋւ��鏈��
*****************************************************************************/
void Mcu_Dev_Pwron_EizoIc_PctDspSetting( void ){
    /* eDP-RX�ʏ퓮�샂�[�h�ֈڍs */
    /* 0x0760���W�X�^=0x01 */

    /* eDP�z�b�g�v���OON( DP0_HPD(V-IC)=Hi ) */
    /* 0x0403���W�X�^=0x41 */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_CamDspSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 6.5.1.1 �N�����̃J�����G�C�Y�\���Ɋւ���ݒ�t���[
*****************************************************************************/
void Mcu_Dev_Pwron_EizoIc_CamDspSetting( void ){
    /* MCU�Ƀo�b�N�A�b�v���Ă���u�J�����V�X�e����ʁv�Ɓu�J�����f���̐؂�o���T�C�Y �v�Ɋ�Â�
    �u6.5.2.1 �J�����f���\���Ɋւ���ݒ胊�X�g�v�e�t�����f�����Ƃ̐ݒ�����{ */

    /* ���s���ɂ�菈���쐬�X�L�b�v */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifRcvr_Init
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF��M�N������
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifRcvr_Init( void ){
    /* ��ԑJ�ږ������̂��߉��R�[�h */
    /* [6-1~6-4. �S�̃t���[]�V�[�g�̏��������� */
    /* 6.2 �����ݒ菈�� */
    Mcu_Dev_Pwron_GvifRx_Polling_Rst();

    /* 7.���W�X�^�ݒ� */
    Mcu_Dev_Pwron_GvifRx_RegSetting();
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifRx_Polling_Rst
  Description   : 
  param[in/out] : 
  return        : -
  Note          : /GVIF-RX(CAM)-RST=Hi �Ď�
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifRx_Polling_Rst( void ){
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GVIF_CAN_RST]);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        u2_s_PwrCtrl_Polling_GvifRxRst       = (uint32)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (u2_s_PwrCtrl_Polling_GvifRxRst < (uint32)PWRCTRL_SYS_COUNTTIME_FIN)){
        u2_s_PwrCtrl_Polling_GvifRxRst++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifRx_RegSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 7.���W�X�^�ݒ�
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifRx_RegSetting( void ){
    static const uint32 MCU_PWRON_TIME_GVIFRX  =   (uint16)(15U / PWRCTRL_CFG_TASK_TIME);    /* min:15ms */

    uint8   mcu_time_chk;

    mcu_time_chk    =   u1_t_Pwron_TimChk(u2_s_PwrCtrl_Polling_GvifRxRst, MCU_PWRON_TIME_GVIFRX);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_GvifRx_SetReg();
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifRx_SetReg
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF��M�@���������� ���W�X�^�ݒ�
*****************************************************************************/
void Mcu_Dev_Pwron_GvifRx_SetReg( void ){
    /* IF�s���̂��ߖ��ݒ�  �ɒ�`�����萔�z���p���Đݒ肷�� */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifSndr_Init
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF��M�N������
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifSndr_Init( void ){
    /* ��ԑJ�ږ������̂��߉��R�[�h */
    /* [(C-Disp)����t���[]�V�[�g�́u����Ď��t���[�v�O�܂� */
    /* 6.2 �����ݒ菈�� */
    Mcu_Dev_Pwron_GvifTx_Polling_Rst();

    /* �����ݒ� + eDP�ݒ� */
    Mcu_Dev_Pwron_GvifTx_RegSetting();

    /* �o�͐ݒ�t���[ +  */
    Mcu_Dev_Pwron_GvifTx_OutputSetting();

    /* HDCP�F�؃t���[(SiP�p�̃t���[�̂��ߏ�������) */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_Polling_Rst
  Description   : 
  param[in/out] : 
  return        : -
  Note          : /GVIF-RX(CAM)-RST=Hi �Ď�
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifTx_Polling_Rst( void ){
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GVIF_CDISP_RST]);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        u2_s_PwrCtrl_Polling_GvifTxRst       = (uint32)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (u2_s_PwrCtrl_Polling_GvifTxRst < (uint32)PWRCTRL_SYS_COUNTTIME_FIN)){
        u2_s_PwrCtrl_Polling_GvifTxRst++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_RegSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : (C-Disp)���W�X�^�ݒ�
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifTx_RegSetting( void ){
    static const uint8  MCU_PWRON_TIME_GVIFTX  =   (11U);    /* min:55ms 11�^�X�N�o�ߌ��ݒ� */

    uint8   mcu_time_chk;

    mcu_time_chk    =   u1_t_Pwron_TimChk(u2_s_PwrCtrl_Polling_GvifTxRst, MCU_PWRON_TIME_GVIFTX);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_GvifTx_SetReg();
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_SetReg
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF���M�@���������� ���W�X�^�ݒ�
*****************************************************************************/
void Mcu_Dev_Pwron_GvifTx_SetReg( void ){
    /* IF�s���̂��ߖ��ݒ�  �ɒ�`�����萔�z���p���Đݒ肷�� */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_OutputSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF���M�@ �o�͐ݒ�t���[
*****************************************************************************/
void Mcu_Dev_Pwron_GvifTx_OutputSetting( void ){

    if(mcu_gvif_restart_sts == MCU_GVIF_RESTRT_STS_1ST){
        /* I2C�ݒ� Display IC (ML86294) �f���o�͊J�n�ieDP�o�́j*/
        /* I2Cwrite �A�h���X�F0xFF, �ݒ�l:0x00 */

        Mcu_Dev_Pwron_GvifTx_LnkChk();
    }
    else if(mcu_gvif_restart_sts == MCU_GVIF_RESTRT_STS_2ND){
        Mcu_Dev_Pwron_GvifTx_LnkChk();
    }
    else{
        /* Do Nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_LnkChk
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF���M�@ �����N�m����ԊĎ�
*****************************************************************************/
void Mcu_Dev_Pwron_GvifTx_LnkChk( void ){
    uint8 mcu_gvif_linkchk;
    mcu_gvif_linkchk = 0;

    /* I2Cwrite �A�h���X�F0x60, �ݒ�l:0730 */
    /* 50mswait */
    mcu_gvif_linkchk = 0; /* I2C���W�X�^Read �A�h���X�F0x00 */
    mcu_gvif_linkchk = mcu_gvif_linkchk & 1; /* 0bit�ڂ̃f�[�^�m�F */
    Mcu_Gvif_LinkTimer = 6000U; /* �ǂ�������CDC�N������̎��Ԃ��擾 �b��ŋ����G���[���� */
    if(mcu_gvif_linkchk == MCU_GVIF_LNK_ACTIVE){
         Mcu_Gvif_LinkTimer = 0;
        /* I2Cwrite �A�h���X�F0xFF, �ݒ�l:0x07 */
        /* I2Cwrite �A�h���X�F0xFB, �ݒ�l:0x00 */
        /* I2Cwrite �A�h���X�F0xFF, �ݒ�l:0x00 */
        /* I2Cwrite �A�h���X�F0x2E, �ݒ�l:0x01 */
        /* I2Cwrite �A�h���X�F0x2E, �ݒ�l:0x00 */
        mcu_gvif_restart_sts = MCU_GVIF_RESTRT_STS_CMP;
    }
    else if(Mcu_Gvif_LinkTimer > MCU_GVIF_LNK_TIMEOUT){
        /* �����N�G���[���� �d�lTBD */
        mcu_gvif_restart_sts = MCU_GVIF_RESTRT_STS_CMP; /* �^�C���A�E�g�����N�G���[���͎b��Ŋ������ */
    }
    else{
        mcu_gvif_restart_sts = MCU_GVIF_RESTRT_STS_2ND; /* GVIF�o�͍Đݒ� */
    }
}

/*****************************************************************************
  Function      : vd_g_McuDevPwronWritePort
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
void vd_g_McuDevPwronWritePort( void ){
    for(uint8 cnt = 0; cnt < MCU_PORT_NUM; cnt++){
        if(Mcu_Dio_Port_Level[cnt] != Mcu_Dio_Port_level_Pre[cnt]){
            (void)Dio_WriteChannel(Mcu_Dio_PortId[cnt] , Mcu_Dio_Port_Level[cnt]);
        }
        Mcu_Dio_Port_level_Pre[cnt] = Mcu_Dio_Port_Level[cnt];
    }
 }

/*****************************************************************************
  Function      : vd_g_McuDevPwronSetPort
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
void vd_g_McuDevPwronSetPort( uint8 port_id, uint8 port_level){
    Mcu_Dio_Port_Level[port_id] = port_level;
 }

/**** End of File ***********************************************************/
