/* Mcu_Sys_Pwr_c_v1-0-0                                                     */
/****************************************************************************/
/* Copyright (C) 2023 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Mcu_Sys_Pwr/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Mcu_Main.h"
#include "Mcu_Sys_Pwr.h"
#include "Mcu_NoRedun_PwrCtrl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
void Mcu_Sys_PwrOn_Bu_Dd_Mode( void );
void Mcu_Sys_PwrOn_DisCharge( void );
void Mcu_Sys_PwrOn_Boost_Dcdc( void );
void Mcu_Sys_PwrOn_Boost_Asil_Dcdc( void );
void Mcu_Sys_PwrOn_Dd_Freq( void );
void Mcu_Sys_PwrOn_Boost_Asil_Freq( void );
void Mcu_Sys_PwrOn_V33_Peri( void );
void Mcu_Sys_PwrOn_V33_Asil( void );
void Mcu_Sys_PwrOn_V18( void );
void Mcu_Sys_PwrOn_V18_Asil( void );
void Mcu_Sys_PwrOn_Audio( void );
void Mcu_Sys_PwrOn_V11_Asil( void );
void Mcu_Sys_PwrOn_Eizo( void );
void Mcu_Sys_PwrOff_flw( void );

/* デバイスON制御 */
uint8   Mcu_Dev_Pwron_TimChk( uint8 mcu_tim_cnt, uint8 mcu_tim_fim );
void    Mcu_Dev_Pwron_Polling_V33PERI( void );
void    Mcu_Dev_Pwron_Polling_EIZO( void );
void    Mcu_Dev_Pwron_Polling_AUDIO( void );
void    Mcu_Dev_Pwron_USB( void );
void    Mcu_Dev_Pwron_PictIC( void );
void    Mcu_Dev_Pwron_GVIFRx( void );
void    Mcu_Dev_Pwron_GVIFTx_CDisp( void );
void    Mcu_Dev_Pwron_Mic( void );
void    Mcu_Dev_Pwron_Ant( void );

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

static uint8 Mcu_Dio_Port_Level[MCU_PORT_NUM];
static uint8 Mcu_Dio_Port_level_Pre[MCU_PORT_NUM];

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* CentralからのON/OFFシーケンス起動要求 */
static uint8    Mcu_PwrOn_Start;
static uint8    Mcu_PwrOff_Start;

static uint8    Mcu_PwrOn_Step;
static uint8    Mcu_PwrOff_Step;

static uint8    Mcu_Bu_Dd_Mode_Time;
static uint8    Mcu_DisCharge_Time;
static uint8    Mcu_Boost_Dcdc_Time;
static uint8    Mcu_Boost_Asil_Dcdc_Time;
static uint8    Mcu_Dd_Freq_Time;
static uint8    Mcu_Boost_Asil_Freq_Time;
static uint8    Mcu_V33_Peri_Time;
static uint8    Mcu_V33_Asil_Time;
static uint8    Mcu_V18_Time;
static uint8    Mcu_V18_Asil_Time;
static uint8    Mcu_Audio_Time;
static uint8    Mcu_V11_Asil_Time;
static uint8    Mcu_Eizo_Time;

static uint8    Mcu_Off_Time;

/* デバイス起動用カウンタ */
static uint8   Mcu_Polling_V33PERI;
static uint8   Mcu_Polling_EIZO;
static uint8   Mcu_Polling_AUDIO;

static uint8   Mcu_Polling_VIcRst;
static uint8   Mcu_Polling_GvifRxRst;
static uint8   Mcu_Polling_GvifTxRst;
static uint16  Mcu_Gvif_LinkTimer;    /* CDC起動からのタイマ→本来はもっと別の場所で管理？ */
static uint8   mcu_gvif_restart_sts;



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
  Function      : Mcu_Sys_Pwr_Init
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_Init( void )
{
    /* CentralからのON/OFFシーケンス起動要求の初期化 */
    Mcu_PwrOn_Start             = (uint8)MCU_SYS_CENTRAL_NON;
    Mcu_PwrOff_Start            = (uint8)MCU_SYS_CENTRAL_NON;

    /* 現在起動ステップの初期化 */
    Mcu_PwrOn_Step              = (uint8)MCU_SYS_STEP1;
    Mcu_PwrOff_Step             = (uint8)MCU_SYS_STEP1;
    
    /* 待機時間測定用RAMの初期化 */
    Mcu_Bu_Dd_Mode_Time         = (uint8)0U;
    Mcu_DisCharge_Time          = (uint8)0U;
    Mcu_Boost_Dcdc_Time         = (uint8)0U;
    Mcu_Boost_Asil_Dcdc_Time    = (uint8)0U;
    Mcu_Dd_Freq_Time            = (uint8)0U;
    Mcu_Boost_Asil_Freq_Time    = (uint8)0U;
    Mcu_V33_Peri_Time           = (uint8)0U;
    Mcu_V33_Asil_Time           = (uint8)0U;
    Mcu_V18_Time                = (uint8)0U;
    Mcu_V18_Asil_Time           = (uint8)0U;
    Mcu_Audio_Time              = (uint8)0U;
    Mcu_V11_Asil_Time           = (uint8)0U;
    Mcu_Eizo_Time               = (uint8)0U;
    Mcu_Off_Time                = (uint8)0U;

    /* デバイス起動用カウンタの初期化 */
    Mcu_Polling_V33PERI         = (uint8)0U;
    Mcu_Polling_EIZO            = (uint8)0U;
    Mcu_Polling_AUDIO           = (uint8)0U;

    Mcu_Polling_VIcRst          = (uint8)0U;
    Mcu_Polling_GvifRxRst       = (uint8)0U;
    Mcu_Polling_GvifTxRst       = (uint8)0U;
    mcu_gvif_restart_sts        = (uint8)0U;

    for(uint8 cnt = 0; cnt < MCU_PORT_NUM; cnt++){
        Mcu_Dio_Port_Level[cnt] = 0;
        Mcu_Dio_Port_level_Pre[cnt] = 0;
    }
   
}

/*****************************************************************************
  Function      : Mcu_Sys_Pwr_mainFunction
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_MainFunction( void )
{
    /* CentralからのSYS起動電源ON要求あり */
    if(Mcu_PwrOn_Start == MCU_SYS_CENTRAL_ON){
        /* OFF側のSTEP管理RAM,タイマをクリアしてOFF2週目も実行できるようにする */
        Mcu_PwrOff_Step = (uint8)MCU_SYS_STEP1;
        Mcu_Off_Time    = (uint8)0U;

        switch (Mcu_PwrOn_Step) {
        case MCU_SYS_STEP1:
            Mcu_Sys_PwrOn_Bu_Dd_Mode(); /* STEP1-2 */
            Mcu_Sys_PwrOn_DisCharge();  /* STEP1-1 */
            
            /* STEP1-1とSTEP1-2が完了していれば次のSTEPに進める */
            if((Mcu_Bu_Dd_Mode_Time == MCU_SYS_WAIT_TIME_FIN)&&
              (Mcu_DisCharge_Time == MCU_SYS_WAIT_TIME_FIN)){
                Mcu_PwrOn_Step = (uint8)MCU_SYS_STEP2;
            }
            break;
            
        case MCU_SYS_STEP2:
            Mcu_Sys_PwrOn_Boost_Dcdc();      /* STEP2-1 */
            Mcu_Sys_PwrOn_Boost_Asil_Dcdc(); /* STEP2-2 */
            
            /* STEP2-1とSTEP2-2が完了していれば次のSTEPに進める */
            if((Mcu_Boost_Dcdc_Time == MCU_SYS_WAIT_TIME_FIN)&&
              (Mcu_Boost_Asil_Dcdc_Time == MCU_SYS_WAIT_TIME_FIN)){
                Mcu_PwrOn_Step = (uint8)MCU_SYS_STEP3;
              }
            break;
            
        case MCU_SYS_STEP3:
            Mcu_Sys_PwrOn_Dd_Freq();         /* STEP3-1 */
            Mcu_Sys_PwrOn_Boost_Asil_Freq(); /* STEP3-2 */
            Mcu_Sys_PwrOn_V33_Peri();        /* STEP3-3 */
            Mcu_Sys_PwrOn_V33_Asil();        /* STEP3-4 */
            
            /* STEP3-1~STEP3-4が完了していれば次のSTEPに進める */
            if((Mcu_Dd_Freq_Time == MCU_SYS_WAIT_TIME_FIN)&&
               (Mcu_Boost_Asil_Freq_Time == MCU_SYS_WAIT_TIME_FIN)&&
               (Mcu_V33_Peri_Time == MCU_SYS_WAIT_TIME_FIN)&&
               (Mcu_V33_Asil_Time == MCU_SYS_WAIT_TIME_FIN)){
                Mcu_PwrOn_Step = (uint8)MCU_SYS_STEP4;
              }
            break;
            
        case MCU_SYS_STEP4:
            Mcu_Sys_PwrOn_V18();       /* STEP4-1 */
            Mcu_Sys_PwrOn_V18_Asil();  /* STEP4-2 */
            Mcu_Sys_PwrOn_Audio();     /* STEP4-3 */
            Mcu_Sys_PwrOn_V11_Asil();  /* STEP4-4 */
            Mcu_Sys_PwrOn_Eizo();      /* STEP4-5 */
            
            /* STEP4-1~STEP4-5が完了していれば正常起動を設定 */
            if((Mcu_V18_Time == MCU_SYS_WAIT_TIME_FIN)&&
              (Mcu_V18_Asil_Time == MCU_SYS_WAIT_TIME_FIN)&&
              (Mcu_Audio_Time == MCU_SYS_WAIT_TIME_FIN)&&
              (Mcu_V11_Asil_Time == MCU_SYS_WAIT_TIME_FIN)&&
              (Mcu_Eizo_Time == MCU_SYS_WAIT_TIME_FIN)){
                /* 正常起動を設定 */
                Mcu_PwrOn_Step = (uint8)MCU_SYS_STEP_OK;
                /* Centralからの要求を初期化 */
                Mcu_PwrOn_Start    =   (uint8)MCU_SYS_CENTRAL_NON;
              }
            break;
            
        case MCU_SYS_STEP_OK:
            /* 正常起動時は何もしない */
            break;
            
        default:
            /* 異常系は未考慮 */
            break;
        }
        
    }
    else if(Mcu_PwrOff_Start == (uint8)MCU_SYS_CENTRAL_ON){ /* SYS起動電源OFFの場合 */
        /* ON側のSTEP管理RAM,タイマをクリアしてON2週目も実行できるようにする */
        Mcu_PwrOn_Step              = (uint8)MCU_SYS_STEP1;
        Mcu_Bu_Dd_Mode_Time         = (uint8)0U;
        Mcu_DisCharge_Time          = (uint8)0U;
        Mcu_Boost_Dcdc_Time         = (uint8)0U;
        Mcu_Boost_Asil_Dcdc_Time    = (uint8)0U;
        Mcu_Dd_Freq_Time            = (uint8)0U;
        Mcu_Boost_Asil_Freq_Time    = (uint8)0U;
        Mcu_V33_Peri_Time           = (uint8)0U;
        Mcu_V33_Asil_Time           = (uint8)0U;
        Mcu_V18_Time                = (uint8)0U;
        Mcu_V18_Asil_Time           = (uint8)0U;
        Mcu_Audio_Time              = (uint8)0U;
        Mcu_V11_Asil_Time           = (uint8)0U;
        Mcu_Eizo_Time               = (uint8)0U;
        Mcu_Polling_V33PERI         = (uint8)0U;
        Mcu_Polling_EIZO            = (uint8)0U;
        Mcu_Polling_AUDIO           = (uint8)0U;
        Mcu_Polling_VIcRst          = (uint8)0U;
        Mcu_Polling_GvifRxRst       = (uint8)0U;
        Mcu_Polling_GvifTxRst       = (uint8)0U;

        switch (Mcu_PwrOff_Step)
        {
        case MCU_SYS_STEP1:
        Mcu_Sys_PwrOff_flw();

        /* STEP1が完了していれば正常起動を設定 */
        if(Mcu_Off_Time == MCU_SYS_WAIT_TIME_FIN){
            Mcu_PwrOff_Step     =   (uint8)MCU_SYS_STEP_OK;
            /* Centralからの要求を初期化 */
            Mcu_PwrOff_Start    =   (uint8)MCU_SYS_CENTRAL_NON;
        }
        break;

        case MCU_SYS_STEP2:     /* fall through */
        case MCU_SYS_STEP3:     /* fall through */
        case MCU_SYS_STEP4:     /* fall through */
        case MCU_SYS_STEP_OK:
            /* 正常終了時は何もしない */
            break;
        default:
            /* 異常系は未考慮 */
            break;
        }
    }
    else {    /* 要求なし */
        /* do nothing */
    }    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_Bu_Dd_Mode
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_Bu_Dd_Mode( void )
{
    if(Mcu_Bu_Dd_Mode_Time == MCU_WAIT_BU_DD_MODE_TIME){
        Mcu_Dev_Pwron_SetPort(MCU_PORT_BU_DD_MODE, MCU_DIO_HIGH);
        Mcu_Bu_Dd_Mode_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_Bu_Dd_Mode_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_Bu_Dd_Mode_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_DisCharge
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_DisCharge( void )
{
    if(Mcu_DisCharge_Time == MCU_WAIT_DISCHARGE_TIME){ /* 放電待ち時間を経過したか */
        Mcu_DisCharge_Time = (uint8)MCU_SYS_WAIT_TIME_FIN; /* 経過していれば計測完了を設定 */
    }
    
    if(Mcu_DisCharge_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_DisCharge_Time++;
    }
    
    return;

}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_Boost_Dcdc
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_Boost_Dcdc( void )
{
    if(Mcu_Boost_Dcdc_Time == MCU_WAIT_BOOST_DCDC_TIME){    /* ウェイトタイムを経過したか 比較対象が0設定のため一致で確認 */
        Mcu_Dev_Pwron_SetPort(MCU_PORT_BOOST_DCDC, MCU_DIO_HIGH);
        Mcu_Boost_Dcdc_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_Boost_Dcdc_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_Boost_Dcdc_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_Boost_Asil_Dcdc
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_Boost_Asil_Dcdc( void )
{
    if(Mcu_Boost_Asil_Dcdc_Time == MCU_WAIT_BOOST_ASIL_DCDC_TIME){    /* ウェイトタイムを経過したか 比較対象が0設定のため一致で確認 */
        Mcu_Dev_Pwron_SetPort(MCU_PORT_BOOST_ASIL_DCDC, MCU_DIO_HIGH);
        Mcu_Boost_Asil_Dcdc_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_Boost_Asil_Dcdc_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_Boost_Asil_Dcdc_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_Dd_Freq
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_Dd_Freq( void )
{
    U2 dd_freq_duty;

    if(Mcu_Dd_Freq_Time == MCU_WAIT_DD_FREQ_TIME){
        dd_freq_duty = MCU_SYS_PWM_DUTYCYCLE(5000U);    /* 50% */
        vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_00_DDC_FREQ, (U2)MCU_SYS_PWM_PERIOD, dd_freq_duty);
        Mcu_Dd_Freq_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_Dd_Freq_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_Dd_Freq_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_Boost_Asil_Freq
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_Boost_Asil_Freq( void )
{
    U2 boost_asil_duty;

    if(Mcu_Boost_Asil_Freq_Time == MCU_WAIT_BOOST_ASIL_FREQ_TIME){
        boost_asil_duty = MCU_SYS_PWM_DUTYCYCLE(5000U);    /* 50% */
        vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_02_DDC_ASIL_FREQ, (U2)MCU_SYS_PWM_PERIOD, boost_asil_duty);
        Mcu_Boost_Asil_Freq_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_Boost_Asil_Freq_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_Boost_Asil_Freq_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_V33_Peri
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_V33_Peri( void )
{
    if(Mcu_V33_Peri_Time == MCU_WAIT_V33_PERI_TIME){
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V33_PERI, MCU_DIO_HIGH);
        Mcu_V33_Peri_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_V33_Peri_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_V33_Peri_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_V33_Asil
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_V33_Asil( void )
{
    if(Mcu_V33_Asil_Time == MCU_WAIT_V33_ASIL_TIME){ 
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V33_ASIL, MCU_DIO_HIGH);
        Mcu_V33_Asil_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_V33_Asil_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_V33_Asil_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_V18
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_V18( void )
{
    if(Mcu_V18_Time == MCU_WAIT_V18_TIME){ 
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V18, MCU_DIO_HIGH);
        Mcu_V18_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_V18_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_V18_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_V18_Asil
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_V18_Asil( void )
{
    if(Mcu_V18_Asil_Time == MCU_WAIT_V18_ASIL_TIME){ 
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V18_ASIL, MCU_DIO_HIGH);
        Mcu_V18_Asil_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_V18_Asil_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_V18_Asil_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_Audio
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_Audio( void )
{
    if(Mcu_Audio_Time == MCU_WAIT_AUDIO_TIME){ 
        Mcu_Dev_Pwron_SetPort(MCU_PORT_AUDIO, MCU_DIO_HIGH);
        Mcu_Audio_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_Audio_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_Audio_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_V11_Asil
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_V11_Asil( void )
{
    if(Mcu_V11_Asil_Time == MCU_WAIT_V11_ASIL_TIME){ 
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V11_ASIL, MCU_DIO_HIGH);
        Mcu_V11_Asil_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_V11_Asil_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_V11_Asil_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_Eizo
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOn_Eizo( void )
{
    if(Mcu_Eizo_Time == MCU_WAIT_EIZO_TIME){ 
        Mcu_Dev_Pwron_SetPort(MCU_PORT_EIZO, MCU_DIO_HIGH);
        Mcu_Eizo_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_Eizo_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_Eizo_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOff_flw
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void Mcu_Sys_PwrOff_flw( void )
{
    if(Mcu_Off_Time == MCU_WAIT_SYSOFF){    /* ウェイトタイムを経過したか 比較対象が0設定のため一致で確認 */
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V18             , MCU_DIO_LOW);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V18_ASIL        , MCU_DIO_LOW);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_AUDIO           , MCU_DIO_LOW);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V11_ASIL        , MCU_DIO_LOW);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_EIZO            , MCU_DIO_LOW);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V33_PERI        , MCU_DIO_LOW);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V33_ASIL        , MCU_DIO_LOW);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_BU_DD_MODE      , MCU_DIO_LOW);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_BOOST_DCDC      , MCU_DIO_LOW);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_BOOST_ASIL_DCDC , MCU_DIO_LOW);

        vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_00_DDC_FREQ , (U2)MCU_SYS_PWM_PERIOD_OFF, (U2)0U);
        vd_g_Pwm_SetPeriodAndDuty((U1)PWM_CH_02_DDC_ASIL_FREQ , (U2)MCU_SYS_PWM_PERIOD_OFF, (U2)0U);

        Mcu_Off_Time = (uint8)MCU_SYS_WAIT_TIME_FIN;
    }
    
    if(Mcu_Off_Time != MCU_SYS_WAIT_TIME_FIN){
        Mcu_Off_Time++;
    }
    
    return;
}
/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_GetStep
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
uint8 Mcu_Sys_PwrOn_GetStep( void )
{
    return Mcu_PwrOn_Step;
}

/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_Start
  Description   : SYS電源ON要求
  param[in/out] : none
  return        : none
  Note          : SYS電源ON処理を実施する条件を満たした場合に、Centralから一度だけコールする。
                  実際のON処理(待ち合わせ、HWアクセス)はMET/IVI定期処理(5ms)で実施すること。
*****************************************************************************/
void Mcu_Sys_PwrOn_Start( void )
{
    Mcu_PwrOn_Start     = (uint8)MCU_SYS_CENTRAL_ON;
    Mcu_PwrOff_Start    = (uint8)MCU_SYS_CENTRAL_NON;

    return;
}

/*****************************************************************************
  Function      : Mcu_Sys_PwrOff_Start
  Description   : SYS電源OFF要求
  param[in/out] : none
  return        : none
  Note          : SYS電源OFF要処理を実施する条件を満たした場合に、Centralから一度だけコールする。
                  実際のOFF処理(待ち合わせ、HWアクセス)はMET/IVI定期処理(5ms)で実施すること。
*****************************************************************************/
void Mcu_Sys_PwrOff_Start( void )
{
    Mcu_PwrOff_Start    = (uint8)MCU_SYS_CENTRAL_ON;
    Mcu_PwrOn_Start     = (uint8)MCU_SYS_CENTRAL_NON;

    return;
}

/*****************************************************************************
  Function      : Mcu_Sys_PwrOn_GetSts
  Description   : SYS電源ONシーケンス状態問い合わせ
  param[in/out] : none
  return        : FALSE(0)：SYS電源ONシーケンス実行中
                  TRUE(1) ：SYS電源ONシーケンス完了
  Note          : SYS電源ON要求～完了するまでの間、Centralからコールする。
*****************************************************************************/
uint8 Mcu_Sys_PwrOn_GetSts( void )
{  
    uint8 mcu_return;

    mcu_return  = (uint8)FALSE; /* 初期化：SYS電源ONシーケンス実行中 */

    if(Mcu_PwrOn_Step == (uint8)MCU_SYS_STEP_OK){
        mcu_return  =   (uint8)TRUE;
    }
    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Sys_PwrOff_GetSts
  Description   : SYS電源OFFシーケンス状態問い合わせ
  param[in/out] : none
  return        : FALSE(0)：SYS電源OFFシーケンス実行中
                  TRUE(1) ：SYS電源OFFシーケンス完了
  Note          : SYS電源OFF要求～完了するまでの間、Centralからコールする。
*****************************************************************************/
uint8 Mcu_Sys_PwrOff_GetSts( void )
{  
    uint8 mcu_return;

    mcu_return  = (uint8)FALSE; /* 初期化：SYS電源ONシーケンス実行中 */

    if(Mcu_PwrOff_Step == (uint8)MCU_SYS_STEP_OK){
        mcu_return  =   (uint8)TRUE;
    }
    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Sys_Shtdwn_GetSts
  Description   : SYS系デバイス終了状態問い合わせ
  param[in/out] : none
  return        : FALSE(0)：SYS系デバイス終了処理実行中
                  TRUE(1) ：SYS系デバイス終了処理完了
  Note          : SiP電源OFF完了後にCentralからコールする。
                  HW制御仕様書上は、対象は各デバイスの制御仕様書参照との記載あり。
*****************************************************************************/
uint8   Mcu_Sys_Shtdwn_GetSts( void )
{
    return((uint8)Mcu_Dev_Pwroff_Sts);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron
  Description   : 
  param[in/out] : 
  return        : -
  Note          : デバイスON制御 
*****************************************************************************/
void Mcu_Dev_Pwron( void ){
    if (Mcu_Pwr_Sts == (uint8)MCU_NOREDUN_CENTRAL_ON) {
        /* 対象ポートのポーリングとタイマカウント開始判断 */
        Mcu_Dev_Pwron_Polling_V33PERI();
        Mcu_Dev_Pwron_Polling_EIZO();
        Mcu_Dev_Pwron_Polling_AUDIO();


        Mcu_Dev_Pwron_USB();           /* USBアダプタ接続検知 */
        Mcu_Dev_Pwron_PictIC();        /* 映像IC(ML86294)制御 */
        Mcu_Dev_Pwron_GVIFRx();        /* GVIF3受信(CXD4984ER)制御 */
        Mcu_Dev_Pwron_GVIFTx_CDisp();  /* GVIF3送信(CXD4937/57)制御 C-Disp */
        Mcu_Dev_Pwron_Mic();           /* マイク電源制御 */
        Mcu_Dev_Pwron_Ant();           /* アンテナ電源制御 */

        Mcu_Dev_Pwron_EizoIc_Init();   /* 映像IC 起動処理 */
        Mcu_Dev_Pwron_GvifRcvr_Init(); /* GVIF受信機 起動処理 */
        Mcu_Dev_Pwron_GvifSndr_Init(); /* GVIF送信機 起動処理 */

        Mcu_Dev_Pwron_WritePort();	   /* Port更新処理 */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_TimChk
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
uint8 Mcu_Dev_Pwron_TimChk( uint8 mcu_tim_cnt, uint8 mcu_tim_fim){
    uint8   mcu_ret;
    mcu_ret =   (uint8)FALSE;

    if(mcu_tim_cnt  >  mcu_tim_fim){
        mcu_ret =   (uint8)TRUE;
    }

    return(mcu_ret);
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_Polling_V33PERI
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
void Mcu_Dev_Pwron_Polling_V33PERI( void ){
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_V33_PERI]);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_V33PERI =   (uint8)0U;
    }
    else if(mcu_dio_ret  ==  (uint8)STD_HIGH &&
        Mcu_Polling_V33PERI <   0xFFU){
        Mcu_Polling_V33PERI++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_Polling_EIZO
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
void Mcu_Dev_Pwron_Polling_EIZO( void ){
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_EIZO]);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_EIZO =   (uint8)0U;
    }
    else if(mcu_dio_ret  ==  (uint8)STD_HIGH &&
        Mcu_Polling_EIZO <   0xFFU){
        Mcu_Polling_EIZO++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_Polling_AUDIO
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
void Mcu_Dev_Pwron_Polling_AUDIO( void ){
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_AUDIO]);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_AUDIO =   (uint8)0U;
    }
    else if(mcu_dio_ret  ==  (uint8)STD_HIGH &&
        Mcu_Polling_AUDIO <   0xFFU){
        Mcu_Polling_AUDIO++;
    }
    else{
        /* do nothing */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_USB
  Description   : 
  param[in/out] : 
  return        : -
  Note          : V33-PERI-ON = Hiから100ms後にUSB-LED-ON = Hi
*****************************************************************************/
void    Mcu_Dev_Pwron_USB( void ){
    static const uint8  MCU_PWRON_TIME_USB  =   (100U / MCU_SYS_TASK_TIME);

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_V33PERI, MCU_PWRON_TIME_USB);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_SetPort(MCU_PORT_USB_LED_ON , MCU_DIO_HIGH);
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_PictIC
  Description   : 
  param[in/out] : 
  return        : -
  Note          : EIZO-ON=Hi から30ms後に/V-IC-RST = Hi、[映像IC起動処理]の初期化処理
*****************************************************************************/
void    Mcu_Dev_Pwron_PictIC( void ){
    static const uint8  MCU_PWRON_TIME_PICTIC  =   (30U / MCU_SYS_TASK_TIME);

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_EIZO, MCU_PWRON_TIME_PICTIC);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_SetPort(MCU_PORT_V_IC_RST , MCU_DIO_HIGH);
    }

    /* [映像IC起動処理]シートの初期化処理 に続く */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GVIFRx
  Description   : 
  param[in/out] : 
  return        : -
  Note          : AUDIO-ON = Hiから10ms後に「/GVIF-RX(CAM)-RST = Hi」
*****************************************************************************/
void    Mcu_Dev_Pwron_GVIFRx( void ){
    static const uint8  MCU_PWRON_TIME_GVIFRX  =   (10U / MCU_SYS_TASK_TIME);

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_AUDIO, MCU_PWRON_TIME_GVIFRX);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_SetPort(MCU_PORT_GVIF_CAN_RST , MCU_DIO_HIGH);
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GVIFTx_CDisp
  Description   : 
  param[in/out] : 
  return        : -
  Note          : AUDIO-ON = Hiから10ms後に「/GVIF-TX(C-DISP)-RST = Hi」
*****************************************************************************/
void    Mcu_Dev_Pwron_GVIFTx_CDisp( void ){
    static const uint8  MCU_PWRON_TIME_GVIFTX  =   (10U / MCU_SYS_TASK_TIME);

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_AUDIO, MCU_PWRON_TIME_GVIFTX);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_SetPort(MCU_PORT_GVIF_CDISP_RST , MCU_DIO_HIGH);
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_Mic
  Description   : 
  param[in/out] : 
  return        : -
  Note          : V33-PERI-ON = Hi から 100ms後 & 「乗車中(見た目ON)/フル起動」に遷移後に MIC-ON = Hi
*****************************************************************************/
void    Mcu_Dev_Pwron_Mic( void ){
    static const uint8  MCU_PWRON_TIME_MIC  =   (100U / MCU_SYS_TASK_TIME);

    uint8   mcu_time_chk;
    uint8   mcu_noredun_sts;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_V33PERI, MCU_PWRON_TIME_MIC);
    mcu_noredun_sts =   Mcu_Noredun_PwrOn_GetSts();

    if(mcu_time_chk ==  (uint8)TRUE &&
        mcu_noredun_sts ==  (uint8)TRUE ){
        Mcu_Dev_Pwron_SetPort(MCU_PORT_MIC_ON , MCU_DIO_HIGH);
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_Ant
  Description   : 
  param[in/out] : 
  return        : -
  Note          : V33-PERI-ON = Hiから100ms後 かつ 「乗車中(見た目ON)/フル起動」に遷移後に
                  AM/FM-ANT-ON,GPS-ANT-ON,DAB-ANT-ON = Hi
*****************************************************************************/
void    Mcu_Dev_Pwron_Ant( void ){
    static const uint8  MCU_PWRON_TIME_ANT  =   (100U / MCU_SYS_TASK_TIME);

    uint8   mcu_time_chk;
    uint8   mcu_noredun_sts;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_V33PERI, MCU_PWRON_TIME_ANT);
    mcu_noredun_sts =   Mcu_Noredun_PwrOn_GetSts();

    if(mcu_time_chk ==  (uint8)TRUE &&
        mcu_noredun_sts ==  (uint8)TRUE ){
        Mcu_Dev_Pwron_SetPort(MCU_PORT_AMFM_ANT_ON , MCU_DIO_HIGH);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_GPS_ANT_ON , MCU_DIO_HIGH);
        Mcu_Dev_Pwron_SetPort(MCU_PORT_DAB_ANT_ON , MCU_DIO_HIGH);
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_Init
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 映像IC起動処理
*****************************************************************************/
void    Mcu_Dev_Pwron_EizoIc_Init( void ){
    /* 状態遷移未検討のため仮コード */
    /* [映像IC起動処理]シートの初期化処理 */
    /* 6.2 初期化処理 */
    Mcu_Dev_Pwron_EizoIc_Polling_VIcRst();

    /* 7.レジスタ設定 */
    Mcu_Dev_Pwron_EizoIc_RegSetting();

    /* 6.3 SiP映像表示に関する処理 */
    Mcu_Dev_Pwron_EizoIc_PctDspSetting();

    /* 6.5.1.1 起動時のカメラエイズ表示に関する設定フロー */
    Mcu_Dev_Pwron_EizoIc_CamDspSetting();
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_Polling_VIcRst
  Description   : 
  param[in/out] : 
  return        : -
  Note          : /V-IC-RST=Hi 監視
*****************************************************************************/
void    Mcu_Dev_Pwron_EizoIc_Polling_VIcRst( void ){
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_V_IC_RST]);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_VIcRst =   (uint8)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (Mcu_Polling_VIcRst <   0xFFU)){
        Mcu_Polling_VIcRst++;
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
  Note          : 7.レジスタ設定
*****************************************************************************/
void    Mcu_Dev_Pwron_EizoIc_RegSetting( void ){
    static const uint8  MCU_PWRON_TIME_EIZOIC  =   (1U);    /* min:1ms 1タスク経過後を設定 */

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_VIcRst, MCU_PWRON_TIME_EIZOIC);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_EizoIc_SetReg();
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_SetReg
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 映像IC初期化処理 レジスタ設定
*****************************************************************************/
void Mcu_Dev_Pwron_EizoIc_SetReg( void ){
    /* IF不明のため未設定 EizoIc_Init.hに定義した定数配列(Eizo_Init_RegAdd,Eizo_Init_RegSet)を用いて設定する */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_PctDspSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 6.3 SiP映像表示に関する処理
*****************************************************************************/
void Mcu_Dev_Pwron_EizoIc_PctDspSetting( void ){
    /* eDP-RX通常動作モードへ移行 */
    /* 0x0760レジスタ=0x01 */

    /* eDPホットプラグON( DP0_HPD(V-IC)=Hi ) */
    /* 0x0403レジスタ=0x41 */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_EizoIc_CamDspSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 6.5.1.1 起動時のカメラエイズ表示に関する設定フロー
*****************************************************************************/
void Mcu_Dev_Pwron_EizoIc_CamDspSetting( void ){
    /* MCUにバックアップしている「カメラシステム種別」と「カメラ映像の切り出しサイズ 」に基づき
    「6.5.2.1 カメラ映像表示に関する設定リスト」各液晶モデルごとの設定を実施 */

    /* 情報不足により処理作成スキップ */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifRcvr_Init
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF受信起動処理
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifRcvr_Init( void ){
    /* 状態遷移未検討のため仮コード */
    /* [6-1~6-4. 全体フロー]シートの初期化処理 */
    /* 6.2 初期設定処理 */
    Mcu_Dev_Pwron_GvifRx_Polling_Rst();

    /* 7.レジスタ設定 */
    Mcu_Dev_Pwron_GvifRx_RegSetting();
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifRx_Polling_Rst
  Description   : 
  param[in/out] : 
  return        : -
  Note          : /GVIF-RX(CAM)-RST=Hi 監視
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifRx_Polling_Rst( void ){
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GVIF_CAN_RST]);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_GvifRxRst =   (uint8)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (Mcu_Polling_GvifRxRst <   0xFFU)){
        Mcu_Polling_GvifRxRst++;
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
  Note          : 7.レジスタ設定
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifRx_RegSetting( void ){
    static const uint8  MCU_PWRON_TIME_GVIFRX  =   (1U);    /* min:1ms 1タスク経過後を設定 */

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_GvifRxRst, MCU_PWRON_TIME_GVIFRX);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_GvifRx_SetReg();
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifRx_SetReg
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF受信機初期化処理 レジスタ設定
*****************************************************************************/
void Mcu_Dev_Pwron_GvifRx_SetReg( void ){
    /* IF不明のため未設定  に定義した定数配列を用いて設定する */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifSndr_Init
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF受信起動処理
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifSndr_Init( void ){
    /* 状態遷移未検討のため仮コード */
    /* [(C-Disp)制御フロー]シートの「定期監視フロー」前まで */
    /* 6.2 初期設定処理 */
    Mcu_Dev_Pwron_GvifTx_Polling_Rst();

    /* 初期設定 + eDP設定 */
    Mcu_Dev_Pwron_GvifTx_RegSetting();

    /* 出力設定フロー +  */
    Mcu_Dev_Pwron_GvifTx_OutputSetting();

    /* HDCP認証フロー(SiP用のフローのため処理無し) */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_Polling_Rst
  Description   : 
  param[in/out] : 
  return        : -
  Note          : /GVIF-RX(CAM)-RST=Hi 監視
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifTx_Polling_Rst( void ){
    uint8   mcu_dio_ret;

    mcu_dio_ret =   Dio_ReadChannel(Mcu_Dio_PortId[MCU_PORT_GVIF_CDISP_RST]);

    if(mcu_dio_ret  ==  (uint8)STD_LOW){
        Mcu_Polling_GvifTxRst =   (uint8)0U;
    }
    else if((mcu_dio_ret  ==  (uint8)STD_HIGH) &&
        (Mcu_Polling_GvifTxRst <   0xFFU)){
        Mcu_Polling_GvifTxRst++;
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
  Note          : (C-Disp)レジスタ設定
*****************************************************************************/
void    Mcu_Dev_Pwron_GvifTx_RegSetting( void ){
    static const uint8  MCU_PWRON_TIME_GVIFTX  =   (11U);    /* min:55ms 11タスク経過後を設定 */

    uint8   mcu_time_chk;

    mcu_time_chk    =   Mcu_Dev_Pwron_TimChk(Mcu_Polling_GvifTxRst, MCU_PWRON_TIME_GVIFTX);

    if(mcu_time_chk ==  (uint8)TRUE){
        Mcu_Dev_Pwron_GvifTx_SetReg();
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_SetReg
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機初期化処理 レジスタ設定
*****************************************************************************/
void Mcu_Dev_Pwron_GvifTx_SetReg( void ){
    /* IF不明のため未設定  に定義した定数配列を用いて設定する */
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_GvifTx_OutputSetting
  Description   : 
  param[in/out] : 
  return        : -
  Note          : GVIF送信機 出力設定フロー
*****************************************************************************/
void Mcu_Dev_Pwron_GvifTx_OutputSetting( void ){

    if(mcu_gvif_restart_sts == MCU_GVIF_RESTRT_STS_1ST){
        /* I2C設定 Display IC (ML86294) 映像出力開始（eDP出力）*/
        /* I2Cwrite アドレス：0xFF, 設定値:0x00 */

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
  Note          : GVIF送信機 リンク確立状態監視
*****************************************************************************/
void Mcu_Dev_Pwron_GvifTx_LnkChk( void ){
    uint8 mcu_gvif_linkchk;
    mcu_gvif_linkchk = 0;

    /* I2Cwrite アドレス：0x60, 設定値:0730 */
    /* 50mswait */
    mcu_gvif_linkchk = 0; /* I2CレジスタRead アドレス：0x00 */
    mcu_gvif_linkchk = mcu_gvif_linkchk & 1; /* 0bit目のデータ確認 */
    Mcu_Gvif_LinkTimer = 6000U; /* どこかからCDC起動からの時間を取得 暫定で強制エラー処理 */
    if(mcu_gvif_linkchk == MCU_GVIF_LNK_ACTIVE){
         Mcu_Gvif_LinkTimer = 0;
        /* I2Cwrite アドレス：0xFF, 設定値:0x07 */
        /* I2Cwrite アドレス：0xFB, 設定値:0x00 */
        /* I2Cwrite アドレス：0xFF, 設定値:0x00 */
        /* I2Cwrite アドレス：0x2E, 設定値:0x01 */
        /* I2Cwrite アドレス：0x2E, 設定値:0x00 */
        mcu_gvif_restart_sts = MCU_GVIF_RESTRT_STS_CMP;
    }
    else if(Mcu_Gvif_LinkTimer > MCU_GVIF_LNK_TIMEOUT){
        /* リンクエラー処理 仕様TBD */
        mcu_gvif_restart_sts = MCU_GVIF_RESTRT_STS_CMP; /* タイムアウトリンクエラー時は暫定で完了状態 */
    }
    else{
        mcu_gvif_restart_sts = MCU_GVIF_RESTRT_STS_2ND; /* GVIF出力再設定 */
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_WritePort
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
void Mcu_Dev_Pwron_WritePort( void ){
    for(uint8 cnt = 0; cnt < MCU_PORT_NUM; cnt++){
        if(Mcu_Dio_Port_Level[cnt] != Mcu_Dio_Port_level_Pre[cnt]){
            (void)Dio_WriteChannel(Mcu_Dio_PortId[cnt] , Mcu_Dio_Port_Level[cnt]);
        }
        Mcu_Dio_Port_level_Pre[cnt] = Mcu_Dio_Port_Level[cnt];
    }
 }

/*****************************************************************************
  Function      : Mcu_Dev_Pwron_SetPort
  Description   : 
  param[in/out] : 
  return        : -
  Note          : 
*****************************************************************************/
void Mcu_Dev_Pwron_SetPort( uint8 port_id, uint8 port_level){
    Mcu_Dio_Port_Level[port_id] = port_level;
 }

/**** End of File ***********************************************************/
