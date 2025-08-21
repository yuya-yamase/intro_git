/************************************************************************************************/
/* file Name        : VIS_Pwr.c                                                                 */
/* contents         : PWR module source                                                         */
/* maker            : NCOS                                                                      */
/* change history   :                                                                           */
/* ---------------------------------------------------------------------------------------------*/
/* ver   | Comments                                                                             */
/* ---------------------------------------------------------------------------------------------*/
/* v1.00 | New created                                                                          */
/************************************************************************************************/

/*==============================================================================================*/
/* Header Files                                                                                 */
/*==============================================================================================*/
#include <Com.h>
#include <Com_Cfg.h>
#include "VIS.h"
#include "VIS_Pwr.h"
#include "VIS_Pwrcfg.h"
#include "chipcom_config.h"
#include "chipcom.h"
#include "iohw_adc.h"

/*==============================================================================================*/
/* define                                                                                       */
/*==============================================================================================*/
/*==============================================================================================*/
/* Variable Definition                                                                          */
/*==============================================================================================*/
/* #define VIS_START_SEC_VAR */
/* #include <VIS_MemMap.h> */

static U1   u1_s_vis_pwr_batvolt;                   /* +B電圧 */
static U1   u1_s_vis_pwr_batvolt_polltimcnt;        /* +B-MONITOR端子ポーリングタイマカウンタ */
static U1   u1_s_vispwr_basicstate;                 /* 車両電源ステート(基本ステート) */
static U1   u1_s_vispwr_specialstate;               /* 車両電源ステート(特殊ステート) */
static U1   u1_s_vispwr_transflg;                   /* 車両電源(特殊)ステート遷移中フラグ */
static U1   u1_s_vispwr_vpsinfo_responsestate;      /* 車両電源ステート(基本ステート)受信状態 */
static U1   u1_s_vispwr_vpsinfos_responsestate;     /* 車両電源ステート(特殊ステート)受信状態 */
static U1   u1_s_vispwr_vpscng_responsestate;       /* 車両電源(特殊)ステート遷移中フラグ受信状態 */
static U1   u1_s_vispwr_ch_compwr;                  /* チャネル通信起動電源状態 */
static U2   u2_s_vispwr_tm_passive_on;              /* パッシブ起動条件成立保持タイマ */
static U2   u2_s_vispwr_tm_ch_off;                  /* チャネル通信起動電源 OFFタイマ */
static U1   u1_s_vispwr_apofrq;                     /* 見た目OFF制御要求 */

/* #define VIS_STOP_SEC_VAR */
/* #include <VIS_MemMap.h> */

/*==============================================================================================*/
/* Function Definition                                                                          */
/*==============================================================================================*/
/* #define VIS_START_SEC_CODE */
/* #include <VIS_MemMap.h> */

static void vd_s_VISPwrGetBatVolt(void);
static U1 u1_s_VISPwrBatVoltADCnv(const U2 u2_a_digitalbatvolt);
static void vd_s_VISPwrJudgeBasicState(void);
static void vd_s_VISPwrJudgeSpecialState(void);
static void vd_s_VISPwrJudgeTransFlg(void);
static U1 u1_s_VISPwrJudgeEthActiveStartup(void);
static U1 u1_s_VISPwrJudgeEthPassiveStartup(void);
static void vd_s_VISPwrJudgeEthChComPwr(void);
static void vd_s_VISPwrJudgeApofrq(void);

/************************************************************************************************/
/* Function Name     : vd_g_VISPwrInit                                                          */
/************************************************************************************************/
void vd_g_VISPwrInit(void)
{
    
    u1_s_vis_pwr_batvolt = VIS_PWR_BAT_FAIL;
    u1_s_vis_pwr_batvolt_polltimcnt = VIS_PWR_BMONI_POLLINGINIT;
    u1_s_vispwr_basicstate = VIS_BASICSTATE_PARKING;
    u1_s_vispwr_specialstate = VIS_SPECIALSTATE_NOTSET;
    u1_s_vispwr_transflg = (U1)STD_OFF;
    u1_s_vispwr_vpsinfo_responsestate = VIS_NORESPONSE;
    u1_s_vispwr_vpsinfos_responsestate = VIS_NORESPONSE;
    u1_s_vispwr_vpscng_responsestate = VIS_NORESPONSE;
    u1_s_vispwr_ch_compwr = (U1)STD_OFF;
    u2_s_vispwr_tm_passive_on = VIS_PWR_JUDGE_PASSIVEON_TM;
    u2_s_vispwr_tm_ch_off = VIS_PWR_JUDGE_CH_POWEROFF_TM;
    u1_s_vispwr_apofrq = (U1)STD_OFF;
    
    return;
}

/************************************************************************************************/
/* Function Name     : vd_g_VISPwrCyc                                                           */
/************************************************************************************************/
void vd_g_VISPwrCyc(void)
{
    vd_s_VISPwrGetBatVolt();
    vd_s_VISPwrJudgeBasicState();
    vd_s_VISPwrJudgeSpecialState();
    vd_s_VISPwrJudgeTransFlg();
    vd_s_VISPwrJudgeEthChComPwr();
    vd_s_VISPwrJudgeApofrq();

    return;
}

/************************************************************************************************/
/* Function Name     : vd_s_VISPwrGetBatVolt                                                    */
/************************************************************************************************/
static void vd_s_VISPwrGetBatVolt(void)
{
    U2 u2_t_bat1volt = VIS_PWR_BAT_FAIL;    /* +B1電圧値(デジタル値) */
    U2 u2_t_bat2volt = VIS_PWR_BAT_FAIL;    /* +B2電圧値(デジタル値) */
    U2 u2_t_digitalbatvolt;                 /* +B電圧値 (デジタル値) */
    U1 u1_t_bat1ret;
    U1 u1_t_bat2ret;
    U2 u2_t_len = sizeof(u1_s_vis_pwr_batvolt);
    
    if(u1_s_vis_pwr_batvolt_polltimcnt > (U1)0U){
        u1_s_vis_pwr_batvolt_polltimcnt --;
    }
    
    /* 100ms経過した場合 */
    if(u1_s_vis_pwr_batvolt_polltimcnt <= (U1)0U){
        /* +B-MONITOR1電圧値取得 */
        u1_t_bat1ret = u1_g_IoHwAdcRead(ADC_CH_B_MON1, &u2_t_bat1volt);
        /* +B-MONITOR2電圧値取得 */
        u1_t_bat2ret = u1_g_IoHwAdcRead(ADC_CH_B_MON2, &u2_t_bat2volt);
        
        /* +B1電圧値が正しく取得できなかった場合 */
        if(u1_t_bat1ret == FALSE){
            /* Fail値を設定 */
            u2_t_bat1volt = VIS_PWR_BAT_FAIL;
        }
        
        /* +B2電圧値が正しく取得できなかった場合 */
        if(u1_t_bat2ret == FALSE){
            /* Fail値を設定 */
            u2_t_bat2volt = VIS_PWR_BAT_FAIL;
        }
        
        /* +B1電圧値が+B2電圧値以上の場合 */
        if (u2_t_bat1volt >= u2_t_bat2volt){
            /* +B1電圧値を設定 */
            u2_t_digitalbatvolt = u2_t_bat1volt;
        }
        /* +B2電圧値が+B1電圧値より大きい場合 */
        else {
            /* +B2電圧値を設定 */
            u2_t_digitalbatvolt = u2_t_bat2volt;
        }
        
        /* +B電圧(LSB：0.1V)のアナログ値に変換 */
        u1_s_vis_pwr_batvolt = u1_s_VISPwrBatVoltADCnv(u2_t_digitalbatvolt);
        /* ポーリングタイマを初期化 */
        u1_s_vis_pwr_batvolt_polltimcnt = VIS_PWR_BMONI_POLLINGCNT;
    }
    
    /* チップ間通信定期送信要求 */
    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_VOLT, u2_t_len, &u1_s_vis_pwr_batvolt);
    
    return;
}
/************************************************************************************************/
/* Function Name     : u1_s_VISPwrBatVoltADCnv(LSB:0.1)                                         */
/************************************************************************************************/
static U1 u1_s_VISPwrBatVoltADCnv(const U2 u2_a_digitalbatvolt)
{
    U1 u1_t_idx;
    U1 u1_t_analogbatvolt;
    U1 u1_t_adcnvchk;
    
    u1_t_adcnvchk = VIS_PWR_ADCNVCHK_NOTOK;
    for(u1_t_idx = (U1)0U; u1_t_idx < VIS_PWRCFG_TABLE_NUM; u1_t_idx++){
        /* A/Dテーブル判定範囲の最大値以下の場合 */
        if(u2_a_digitalbatvolt <= st_gp_VIS_PWRCFG_ADTABLE[u1_t_idx].u2_batvoltmax){
            /* +B電圧(LSB:0.1V)のアナログ値を設定 */
            u1_t_analogbatvolt = st_gp_VIS_PWRCFG_ADTABLE[u1_t_idx].u1_batvolt;
            u1_t_adcnvchk = VIS_PWR_ADCNVCHK_OK;
            break;
        }
    }
    /* ADテーブル変換失敗時の処理 */
    if(u1_t_adcnvchk != VIS_PWR_ADCNVCHK_OK){
        u1_t_analogbatvolt = VIS_PWR_BAT_FAIL;
    }
    
    /* アナログ値を出力 */
    return u1_t_analogbatvolt;
}
/************************************************************************************************/
/* Function Name     : vd_s_VISPwrJudgeBasicState                                               */
/************************************************************************************************/
static void vd_s_VISPwrJudgeBasicState(void)
{
    U1 u1_t_recv = VIS_PWR_RCV_UNDEFINED_VALUE;
    U1 u1_t_vpsinfo1 = VIS_PWR_INIT;
    U1 u1_t_vpsinfo2 = VIS_PWR_INIT;
    U1 u1_t_vpsinfo3 = VIS_PWR_INIT;
    U1 u1_t_vpsinfo4 = VIS_PWR_INIT;
    U1 u1_t_vpsinfo5 = VIS_PWR_INIT;
    U1 u1_t_vpsinfo6 = VIS_PWR_INIT;
    U1 u1_t_vpsinfo7 = VIS_PWR_INIT;
    U1 u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_LENGTH_2];
    U1 u1_t_ipdu_st;

    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S81_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if (VIS_PWR_COM_IPDUST_OK == u1_t_ipdu_st){
        /* VPSINFO1~7を取得 */
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO1, &u1_t_vpsinfo1);
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO2, &u1_t_vpsinfo2);
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO3, &u1_t_vpsinfo3);
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO4, &u1_t_vpsinfo4);
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO5, &u1_t_vpsinfo5);
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO6, &u1_t_vpsinfo6);
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO7, &u1_t_vpsinfo7);
        
        u1_s_vispwr_vpsinfo_responsestate = VIS_COMMUNICATION_OK;           /* CANメッセージ受信状態：正常受信 */

        if ((VIS_PWR_RCVCHK_VAL >= u1_t_vpsinfo1)
            && (VIS_PWR_RCVCHK_VAL >= u1_t_vpsinfo2)
            && (VIS_PWR_RCVCHK_VAL >= u1_t_vpsinfo3)
            && (VIS_PWR_RCVCHK_VAL >= u1_t_vpsinfo4)
            && (VIS_PWR_RCVCHK_VAL >= u1_t_vpsinfo5)
            && (VIS_PWR_RCVCHK_VAL >= u1_t_vpsinfo6)
            && (VIS_PWR_RCVCHK_VAL >= u1_t_vpsinfo7))
        {
            /* 受信値を1byteデータに結合する */
            u1_t_recv = u1_t_vpsinfo1;
            u1_t_recv |= (U1)(u1_t_vpsinfo2 << VIS_PWR_BITSHIFT_1);
            u1_t_recv |= (U1)(u1_t_vpsinfo3 << VIS_PWR_BITSHIFT_2);
            u1_t_recv |= (U1)(u1_t_vpsinfo4 << VIS_PWR_BITSHIFT_3);
            u1_t_recv |= (U1)(u1_t_vpsinfo5 << VIS_PWR_BITSHIFT_4);
            u1_t_recv |= (U1)(u1_t_vpsinfo6 << VIS_PWR_BITSHIFT_5);
            u1_t_recv |= (U1)(u1_t_vpsinfo7 << VIS_PWR_BITSHIFT_6);
        }
        /* 車両電源ステート(基本ステート)を判定する */
        switch (u1_t_recv) {
        case VIS_PWR_RCV_CHECKING:
            u1_s_vispwr_vpsinfo_responsestate = VIS_BASICSTATE_CHECKING;
            break;
        case VIS_PWR_RCV_PARKING:
            u1_s_vispwr_basicstate = VIS_BASICSTATE_PARKING;
            break;
        case VIS_PWR_RCV_RIDING:
            u1_s_vispwr_basicstate = VIS_BASICSTATE_RIDING;
            break;
        case VIS_PWR_RCV_POWERON_NORMAL:
            u1_s_vispwr_basicstate = VIS_BASICSTATE_POWERON_NORMAL;
            break;
        case VIS_PWR_RCV_POWERON_EMERGENCY:
            u1_s_vispwr_basicstate = VIS_BASICSTATE_POWERON_EMERGENCY;
            break;
        case VIS_PWR_RCV_PARKING_HIGHVOL:
            u1_s_vispwr_basicstate = VIS_BASICSTATE_PARKING_HIGHVOL;
            break;
        case VIS_PWR_RCV_PARKING_HIGHVOLHEATCOND:
            u1_s_vispwr_basicstate = VIS_BASICSTATE_PARKING_HIGHVOLHEATCOND;
            break;
        default:
            /* 未定義値の場合は前回値を保持する */
            u1_s_vispwr_vpsinfo_responsestate = VIS_UNDEFINED_VALUE;            /* CANメッセージ受信状態：範囲外 */
            break;
        }

    }
    else if ((U1)COM_TIMEOUT == u1_t_ipdu_st){
        u1_s_vispwr_vpsinfo_responsestate = VIS_COMMUNICATION_ERROR;            /* CANメッセージ受信状態：途絶 */
    }
    else{
        /* do nothing */
    }
    
    /* チップ間通信_送信要求 */
    u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_RECEIVEVAL] = u1_s_vispwr_basicstate;
    u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_RETURNVAL] = u1_s_vispwr_vpsinfo_responsestate;
    
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_BASICSTATE,VIS_PWR_TRANSREQ_DATA_LENGTH_2,u1_tp_transreq_data);

    return;
}
/************************************************************************************************/
/* Function Name     : vd_s_VISPwrJudgeSpecialState                                             */
/************************************************************************************************/
static void vd_s_VISPwrJudgeSpecialState(void)
{
    U1 u1_t_vpsinfos = VIS_PWR_SPECIALSTATE_INIT;
    U1 u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_LENGTH_2];
    U1 u1_t_ipdu_st;

    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S81_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if (VIS_PWR_COM_IPDUST_OK == u1_t_ipdu_st){
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFOS, &u1_t_vpsinfos);
        u1_s_vispwr_vpsinfos_responsestate = VIS_COMMUNICATION_OK;              /* CANメッセージ受信状態：正常受信 */
        
        /* 車両電源ステート(特殊ステート)を判定する */
        switch (u1_t_vpsinfos){
        case VIS_SPECIALSTATE_NOTSET:
        case VIS_SPECIALSTATE_PRE_DELIVERY:
        case VIS_SPECIALSTATE_OTA:
        case VIS_SPECIALSTATE_WIRED_REPRO:
        case VIS_SPECIALSTATE_EMERGENCY_STOP:
        case VIS_SPECIALSTATE_POWEROFF_ALL:
        case VIS_SPECIALSTATE_SERVICE_LLC:
            u1_s_vispwr_specialstate = u1_t_vpsinfos;
            break;
        default:
            /* 未定義値の場合は前回値を保持する */
            u1_s_vispwr_vpsinfos_responsestate = VIS_UNDEFINED_VALUE;           /* CANメッセージ受信状態：範囲外 */
            break;
        }
    }
    else if ((U1)COM_TIMEOUT == u1_t_ipdu_st){
        u1_s_vispwr_vpsinfos_responsestate = VIS_COMMUNICATION_ERROR;           /* CANメッセージ受信状態：途絶 */
    }
    else{
        /* do nothing */
    }

    /* チップ間通信_送信要求 */
    u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_RECEIVEVAL] = u1_s_vispwr_specialstate;
    u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_RETURNVAL] = u1_s_vispwr_vpsinfos_responsestate;
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_SPECIALSTATE,VIS_PWR_TRANSREQ_DATA_LENGTH_2,u1_tp_transreq_data);

    return;
}

/************************************************************************************************/
/* Function Name     : vd_s_VISPwrJudgeTransFlg                                                 */
/************************************************************************************************/
static void vd_s_VISPwrJudgeTransFlg(void)
{
    U1 u1_t_transflg = (U1)STD_OFF;
    U1 u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_LENGTH_2];
    U1 u1_t_ipdu_st;

    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S81_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if (VIS_PWR_COM_IPDUST_OK == u1_t_ipdu_st){
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSCNG, &u1_t_transflg);

        u1_s_vispwr_vpscng_responsestate = VIS_COMMUNICATION_OK;            /* CANメッセージ受信状態：正常受信 */

        if (VIS_PWR_RCVCHK_VAL >= u1_t_transflg) {
            u1_s_vispwr_transflg = u1_t_transflg;
        }
        else {
            u1_s_vispwr_vpscng_responsestate = VIS_UNDEFINED_VALUE;         /* CANメッセージ受信状態：範囲外 */
        }
    }
    else if ((U1)COM_TIMEOUT == u1_t_ipdu_st){
        u1_s_vispwr_vpscng_responsestate = VIS_COMMUNICATION_ERROR;         /* CANメッセージ受信状態：途絶 */
    }
    else{
        /* do nothing */
    }
    
    /* チップ間通信_送信要求 */
    u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_RECEIVEVAL] = u1_s_vispwr_transflg;
    u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_RETURNVAL] = u1_s_vispwr_vpscng_responsestate;
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_TRANSFLG,VIS_PWR_TRANSREQ_DATA_LENGTH_2,u1_tp_transreq_data);
    
    return;
}

/************************************************************************************************/
/* Function Name     :  u1_s_VISPwrJudgeEthActiveStartup                                        */
/************************************************************************************************/
/* Ethernet通信アクティブ起動条件判定 */
static U1 u1_s_VISPwrJudgeEthActiveStartup(void)
{
    U1 u1_t_app_comcond = (U1)STD_OFF;      /* 自ECU内のEthernet通信するアプリの通信起動条件成立状態 */
    U1 u1_t_nm_awakepwr = (U1)STD_OFF;      /* NMアウェイク電源 */
    U1 u1_t_active_startup = (U1)STD_OFF;   /* Ethernet通信アクティブ起動条件成立状態 */
    U1 u1_t_ethwu_21 = (U1)STD_OFF;     /* ETHWU_21:通信継続メッセージ(From:CDC) */
    U1 u1_t_ethwu_23 = (U1)STD_OFF;     /* ETHWU_23:通信継続メッセージ(From:CDC) */
    U1 u1_t_ipdu_st;

    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_CDC1S04_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if (VIS_PWR_COM_IPDUST_OK == u1_t_ipdu_st){
        (void)Com_ReceiveSignal(ComConf_ComSignal_ETHWU_21, &u1_t_ethwu_21);
        (void)Com_ReceiveSignal(ComConf_ComSignal_ETHWU_23, &u1_t_ethwu_23);
        
        if (((U1)STD_ON == u1_t_ethwu_21) ||((U1)STD_ON == u1_t_ethwu_23)){
            u1_t_app_comcond = (U1)STD_ON;
        }
    }

    /* NMアウェイク電源判定 */
    switch (u1_s_vispwr_basicstate) {               /* 車両電源ステート(基本ステート) */
    case VIS_BASICSTATE_RIDING:                     /* 乗車中 */
    case VIS_BASICSTATE_POWERON_NORMAL:             /* PowerON通常 */
    case VIS_BASICSTATE_POWERON_EMERGENCY:          /* PowerON緊急停止 */
        u1_t_nm_awakepwr = (U1)STD_ON;                  
        break;
    default:
        /* Do Nothing */
        break;
    }

    /* Ethernet通信アクティブ起動条件判定 */
    if (((U1)STD_ON == u1_t_app_comcond) || ((U1)STD_ON == u1_t_nm_awakepwr)) {
        u1_t_active_startup = (U1)STD_ON;
    }

    return u1_t_active_startup;
}

/************************************************************************************************/
/* Function Name     :  u1_s_VISPwrJudgeEthPassiveStartup                                       */
/************************************************************************************************/
/* Ethernet通信パッシブ起動条件判定 */
static U1 u1_s_VISPwrJudgeEthPassiveStartup(void)
{
    U1 u1_t_passive_startup = (U1)STD_OFF;      /* Ethernet通信パッシブ起動条件成立状態 */
    U1 u1_t_ethwu_12 = (U1)STD_OFF;         /* ETHWU_12:通信継続メッセージ(From:ADC) */
    U1 u1_t_ethwu_32 = (U1)STD_OFF;         /* ETHWU_32:通信継続メッセージ(From:DCM) */

    U1 u1_t_ipdu_st;

    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_ADC1S30_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if (VIS_PWR_COM_IPDUST_OK == u1_t_ipdu_st){
        (void)Com_ReceiveSignal(ComConf_ComSignal_ETHWU_12, &u1_t_ethwu_12);
    }
    
    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_DCM1S08_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if (VIS_PWR_COM_IPDUST_OK == u1_t_ipdu_st){
        (void)Com_ReceiveSignal(ComConf_ComSignal_ETHWU_32, &u1_t_ethwu_32);
    }
    
    if (((U1)STD_ON == u1_t_ethwu_12) || ((U1)STD_ON == u1_t_ethwu_32)) {
        u1_t_passive_startup = (U1)STD_ON;
        u2_s_vispwr_tm_passive_on = VIS_PWR_TIMEOUTINIT;
    }
    else if (VIS_PWR_JUDGE_PASSIVEON_TM > u2_s_vispwr_tm_passive_on) {
        u1_t_passive_startup = (U1)STD_ON;
        u2_s_vispwr_tm_passive_on++;
    }
    else {
        /* Do Nothing */
    }

    return u1_t_passive_startup;
}

/************************************************************************************************/
/* Function Name     :  vd_s_VISPwrJudgeEthChComPwr                                             */
/************************************************************************************************/
/* Ethernetチャネル起動電源状態判定 */
static void vd_s_VISPwrJudgeEthChComPwr(void)
{
    U1 u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_LENGTH_1];
    U1 u1_t_active_startup = (U1)STD_OFF;
    U1 u1_t_passive_startup = (U1)STD_OFF;

    u1_t_active_startup = u1_s_VISPwrJudgeEthActiveStartup();
    u1_t_passive_startup = u1_s_VISPwrJudgeEthPassiveStartup();
    
    if ((U1)STD_OFF == u1_s_vispwr_ch_compwr) {
        if (((U1)STD_ON == u1_t_active_startup)                 
        || ((U1)STD_ON == u1_t_passive_startup)) {
            u1_s_vispwr_ch_compwr = (U1)STD_ON;
        }
        u2_s_vispwr_tm_ch_off = VIS_PWR_TIMEOUTINIT;
    }
    else{
        if (((U1)STD_OFF == u1_t_active_startup)
        && ((U1)STD_OFF == u1_t_passive_startup)) {
            if (VIS_PWR_JUDGE_CH_POWEROFF_TM <= u2_s_vispwr_tm_ch_off) {
                u1_s_vispwr_ch_compwr = (U1)STD_OFF;
            }
            else{
                u2_s_vispwr_tm_ch_off++;
            }
        }
        else {
            u2_s_vispwr_tm_ch_off = VIS_PWR_TIMEOUTINIT;
        }
    }
    
    /* チップ間通信_送信要求 */
    u1_tp_transreq_data[VIS_PWR_TRANSREQ_DATA_RECEIVEVAL] = u1_s_vispwr_ch_compwr;
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_COMPWR,VIS_PWR_TRANSREQ_DATA_LENGTH_1,u1_tp_transreq_data);

    return;
}

/************************************************************************************************/
/* Function Name     : vd_s_VISPwrJudgeApofrq                                                   */
/************************************************************************************************/
static void vd_s_VISPwrJudgeApofrq(void)
{
    U1 u1_t_apofrq = (U1)STD_OFF;
    U1 u1_t_ipdu_st;

    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S81_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if (VIS_PWR_COM_IPDUST_OK == u1_t_ipdu_st){
        (void)Com_ReceiveSignal(ComConf_ComSignal_APOFRQ, &u1_t_apofrq);

        if (VIS_PWR_RCVCHK_VAL >= u1_t_apofrq) {
            u1_s_vispwr_apofrq = u1_t_apofrq;
        }
        else {
            /* do nothing */
        }
    }
    else{
        /* do nothing */
    }

    return;
}

/************************************************************************************************/
/* Function Name     : u1_g_VISPwrGetBasicState                                                 */
/************************************************************************************************/
U1 u1_g_VISPwrGetBasicState (U1 * const u1_a_BASICSTATE)
{
    if (u1_a_BASICSTATE == NULL_PTR) { return VIS_INTERNAL_ERROR; }
    *u1_a_BASICSTATE = u1_s_vispwr_basicstate;
    return u1_s_vispwr_vpsinfo_responsestate;
}

/************************************************************************************************/
/* Function Name     : u1_g_VISPwrGetSpecialState                                               */
/************************************************************************************************/
U1 u1_g_VISPwrGetSpecialState (U1 * const u1_a_SPECIALSTATE)
{
    if (u1_a_SPECIALSTATE == NULL_PTR) { return VIS_INTERNAL_ERROR; }
    *u1_a_SPECIALSTATE = u1_s_vispwr_specialstate;
    return u1_s_vispwr_vpsinfos_responsestate;
}

/************************************************************************************************/
/* Function Name     : u1_g_VISPwrGetTransFlg                                                   */
/************************************************************************************************/
U1 u1_g_VISPwrGetTransFlg (U1 * const u1_a_TRANSFLG)
{
    if (u1_a_TRANSFLG == NULL_PTR) { return VIS_INTERNAL_ERROR; }
    *u1_a_TRANSFLG = u1_s_vispwr_transflg;
    return u1_s_vispwr_vpscng_responsestate;
}

/************************************************************************************************/
/* Function Name     :  u1_g_VISPwrGetEthChPwr                                                  */
/************************************************************************************************/
U1 u1_g_VISPwrGetEthChPwr (void)
{
    return u1_s_vispwr_ch_compwr;
}

/************************************************************************************************/
/* Function Name     :  u1_g_VISPwrGetApofrq                                                    */
/************************************************************************************************/
U1 u1_g_VISPwrGetApofrq (void)
{
    return u1_s_vispwr_apofrq;
}

/************************************************************************************************/
/* #define VIS_STOP_SEC_CODE */
/* #include <VIS_MemMap.h> */
