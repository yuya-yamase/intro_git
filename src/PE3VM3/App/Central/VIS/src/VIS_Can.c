/************************************************************************************************/
/* file Name        : VIS_Can.c                                                                 */
/* contents         : CAN module source                                                         */
/* maker            : NCOS                                                                      */
/* change history   :                                                                           */
/* ---------------------------------------------------------------------------------------------*/
/* ver   | Comments                                                                             */
/* ---------------------------------------------------------------------------------------------*/
/* v1.00 | New created                                                                          */
/************************************************************************************************/

#include <Std_Types.h>
#include <ComStack_Types.h>
#include <Com.h>
#include <Com_Cfg.h>
#include "VIS.h"
#include "VIS_Can.h"
#include "LIB.h"
/* 26.2.16 doza Team-B edit sta */
/*#include "chipcom.h"*/
/*#include "chipcom_config.h"*/
#include "ChipCom.h"
#include "ChipCom_Cfg.h"
/* 26.2.16 doza Team-B edit end */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* #define VIS_START_SEC_VAR                                                  */
/* #include <VIS_MemMap.h>                                                    */
/* -------------------------------------------------------------------------- */
static ST_VIS_UTC       st_s_vis_can_utcdata;                   /* UTC時刻情報 */
static U4               u4_s_vis_can_ododata;                   /* オドメータ情報 */
static U2               u2_s_vis_can_tripcnt;                   /* Tripカウンタ情報 */
static U1               u1_s_vis_can_sync;                      /* マスタ同期情報 */
static U1               u1_s_vis_can_spddata;                   /* 現在車両速度 */
static U1               u1_s_vis_can_rdystsdata;                /* 電動システム起動状態 */
static U1               u1_sp_vis_can_vindata[VIS_VIN_MAX_NM];  /* VINデータ */
static U1               u1_s_vis_can_otaswact;                  /* OTASWACT */
static U1               u1_s_vis_can_pwrerrst;                  /* PWRERRST */
static U1               u1_s_vis_can_crlyof;                    /* CRLYOF */
static U1               u1_s_vis_vin_responsestate;             /* VINデータ受信状態 */
static U1               u1_s_vis_otaswact_responsestate;        /* OTASWACT受信状態 */
static U1               u1_s_vis_pwrerrst_responsestate;        /* PWRERRST受信状態 */
static U1               u1_s_vis_crlyof_responsestate;          /* CRLYOF受信状態 */
/* -------------------------------------------------------------------------- */
/* #define VIS_STOP_SEC_VAR                                                   */
/* #include <VIS_MemMap.h>                                                    */
/* -------------------------------------------------------------------------- */
/* #define VIS_START_SEC_COD                                                  */
/* #include <VIS_MemMap.h>                                                    */
/* -------------------------------------------------------------------------- */
static void vd_s_VISCanGetUtc(void);
static void vd_s_VISCanGetOdo(void);
static void vd_s_VISCanGetTripCnt(void);
static void vd_s_VISCanGetSpd(void);
static void vd_s_VISCanGetRdySts(void);
static void vd_s_VISCanGetVin(void);
static void vd_s_VISCanGetOtaswact(void);
static void vd_s_VISCanGetPwrerrst(void);
static void vd_s_VISCanGetCrlyof(void);

static U1 u1_s_VISCanUtcCheckLimit(const U1 u1_a_DATA, const U1 u1_a_MIN, const U1 u1_a_MAX);
static U1 u1_s_VISCanUtcCheckVal(const ST_VIS_UTC * const st_ap_UTCDATA);
/* -------------------------------------------------------------------------- */
void vd_g_VISCanInit(void)
{
    LIB_memset((U1*)&st_s_vis_can_utcdata, VIS_CAN_UTC_FAIL, sizeof(st_s_vis_can_utcdata));
    u4_s_vis_can_ododata = VIS_CAN_ODO_FAIL;
    u2_s_vis_can_tripcnt = VIS_CAN_TRIP_FAIL;
    u1_s_vis_can_sync = VIS_CAN_TRIP_ASYNC;
    u1_s_vis_can_spddata = VIS_CAN_SPD_FAIL;
    u1_s_vis_can_rdystsdata = VIS_CAN_E_PWRCTRLSYS_RDYSTS_OFF;
    
    u1_s_vis_can_otaswact = (U1)STD_OFF;
    u1_s_vis_can_pwrerrst = VIS_NORMAL_USERDRIVEN;
    u1_s_vis_can_crlyof = (U1)STD_OFF;
    u1_s_vis_vin_responsestate = VIS_NORESPONSE;
    u1_s_vis_otaswact_responsestate = VIS_NORESPONSE;
    u1_s_vis_pwrerrst_responsestate = VIS_NORESPONSE;
    u1_s_vis_crlyof_responsestate = VIS_NORESPONSE;

    /* VINデータ初期化 */
    U1 u1_t_datacnt;
    for (u1_t_datacnt = VIS_CAN_VIN0_NM; u1_t_datacnt < VIS_VIN_MAX_NM; u1_t_datacnt++) {
        u1_sp_vis_can_vindata[u1_t_datacnt] = VIS_VIN_INIT_VAL;
    }

    return;
}
/* -------------------------------------------------------------------------- */
void vd_g_VISCanMidCyc(void)
{
    vd_s_VISCanGetUtc();
    vd_s_VISCanGetOdo();
    vd_s_VISCanGetTripCnt();
    vd_s_VISCanGetSpd();
    vd_s_VISCanGetRdySts();
    vd_s_VISCanGetVin();
    vd_s_VISCanGetOtaswact();
    vd_s_VISCanGetPwrerrst();
    vd_s_VISCanGetCrlyof();
    
    return;
}

/* -------------------------------------------------------------------------- */
static void vd_s_VISCanGetUtc(void)
{
    U1 u1_t_responsestate;                          /* 車両電源ステート受信状態 */
    U1 u1_t_basicstate = VIS_BASICSTATE_CHECKING;   /* 車両電源ステート */
    U1 u1_t_ret;                                    /* 時刻範囲チェック結果 */
    U1 u1_t_msgsts;                                 /* 受信フレームの状態 */
    U1 u1_tp_rx[VIS_CAN_UTC_RX_NBYTE];
    U1 u1_tp_utcdata[VIS_CAN_TRANSREQ_DATA_UTCNUM];

    /* 格納先の初期化 */
    LIB_memset(u1_tp_rx, VIS_CAN_INIT_0, sizeof(u1_tp_rx));
    
    /* UTC時刻情報取得 */
    /* ★車両電源ステート(基本ステート)情報を取得 */
    u1_t_responsestate = u1_g_VISPwrGetBasicState(&u1_t_basicstate);
    /* 車両電源ステート受信状態が正常受信の場合 */
    if(u1_t_responsestate == VIS_COMMUNICATION_OK){
        /* 車両電源ステートがPowerON通常、PowerON緊急停止の場合 */
        if((u1_t_basicstate == VIS_BASICSTATE_POWERON_NORMAL) || (u1_t_basicstate == VIS_BASICSTATE_POWERON_EMERGENCY)){
        /* RSE1G20メッセージの状態取得 */
            u1_t_msgsts = (U1)Com_GetIPDUStatus(MSG_RSE1G20_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
            /* RSE1G20 正常受信の場合 */
            if(u1_t_msgsts == VIS_CAN_COM_IPDUST_OK){
                /* RSE1G20取得 */
                (void)Com_ReadIPDU(MSG_RSE1G20_RXCH0, u1_tp_rx);
                st_s_vis_can_utcdata.u1_year   = u1_tp_rx[VIS_CAN_UTC_RX_YEAR];
                st_s_vis_can_utcdata.u1_month  = u1_tp_rx[VIS_CAN_UTC_RX_MONTH];
                st_s_vis_can_utcdata.u1_day    = u1_tp_rx[VIS_CAN_UTC_RX_DAY];
                st_s_vis_can_utcdata.u1_hour   = u1_tp_rx[VIS_CAN_UTC_RX_HOUR];
                st_s_vis_can_utcdata.u1_minute = u1_tp_rx[VIS_CAN_UTC_RX_MIN];
                st_s_vis_can_utcdata.u1_second = u1_tp_rx[VIS_CAN_UTC_RX_SEC];
                /* 時刻範囲チェック */
                u1_t_ret = u1_s_VISCanUtcCheckVal(&st_s_vis_can_utcdata);
                /* UTC時刻情報が範囲外の場合 */
                if (u1_t_ret != (U1)E_OK){
                    LIB_memset((U1*)&st_s_vis_can_utcdata, VIS_CAN_UTC_FAIL, sizeof(st_s_vis_can_utcdata));
                }
            }
            /* RSE1G20 未受信もしくは通信途絶の場合 */
            else{
                LIB_memset((U1*)&st_s_vis_can_utcdata, VIS_CAN_UTC_FAIL, sizeof(st_s_vis_can_utcdata));
            }
        }
        /* 車両電源ステートが乗車中以下の場合 */
        else{
            LIB_memset((U1*)&st_s_vis_can_utcdata, VIS_CAN_UTC_FAIL, sizeof(st_s_vis_can_utcdata));
        }
    }
    /* 車両電源ステート受信状態が正常受信以外の場合 */
    else{
        LIB_memset((U1*)&st_s_vis_can_utcdata, VIS_CAN_UTC_FAIL, sizeof(st_s_vis_can_utcdata));
    }
    
    u1_tp_utcdata[VIS_CAN_TRANSREQ_DATA_YEAR] = st_s_vis_can_utcdata.u1_year;
    u1_tp_utcdata[VIS_CAN_TRANSREQ_DATA_MONT] = st_s_vis_can_utcdata.u1_month;
    u1_tp_utcdata[VIS_CAN_TRANSREQ_DATA_DAY] = st_s_vis_can_utcdata.u1_day;
    u1_tp_utcdata[VIS_CAN_TRANSREQ_DATA_HOUR] = st_s_vis_can_utcdata.u1_hour;
    u1_tp_utcdata[VIS_CAN_TRANSREQ_DATA_MIN] = st_s_vis_can_utcdata.u1_minute;
    u1_tp_utcdata[VIS_CAN_TRANSREQ_DATA_SEC] = st_s_vis_can_utcdata.u1_second;
    
    /* チップ間通信定期送信要求 */
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_UTC, sizeof(u1_tp_utcdata), u1_tp_utcdata);
    
    return;
}
/* -------------------------------------------------------------------------- */
static void vd_s_VISCanGetOdo(void)
{
    U1 u1_t_msgsts;                             /* 受信フレームの状態 */
    U1 u1_t_odounit = VIS_CAN_ODO_UNIT_NON;     /* オドメータ単位情報 */
    U4 u4_t_odo = VIS_CAN_ODO_FAIL;             /* オドメータ情報 */
    U1 u1_tp_rx[VIS_CAN_ODO_RX_NBYTE];
    U1 u1_tp_ododata[VIS_CAN_TRANSREQ_DATA_ODONUM];

    /* 格納先の初期化 */
    LIB_memset(u1_tp_rx, VIS_CAN_INIT_0, sizeof(u1_tp_rx));

    /* オド情報取得 */
    /* MET1S02メッセージの状態取得 */
    u1_t_msgsts = (U1)Com_GetIPDUStatus(MSG_MET1S02_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    /* MET1S02 正常受信の場合 */
    if(u1_t_msgsts == VIS_CAN_COM_IPDUST_OK){
        /* MET1S02取得 */
        (void)Com_ReadIPDU(MSG_MET1S02_RXCH0, u1_tp_rx);
        u1_t_odounit = (u1_tp_rx[VIS_CAN_ODO_RX_UNIT] & VIS_CAN_ODO_UNITMASK) >> VIS_CAN_SHIFT_4BIT;
        u4_t_odo = (((U4)u1_tp_rx[VIS_CAN_ODO_RX_POS1] << VIS_CAN_SHIFT_3BYTE) |
                    ((U4)u1_tp_rx[VIS_CAN_ODO_RX_POS2] << VIS_CAN_SHIFT_2BYTE) |
                    ((U4)u1_tp_rx[VIS_CAN_ODO_RX_POS3] << VIS_CAN_SHIFT_1BYTE) |
                     (U4)u1_tp_rx[VIS_CAN_ODO_RX_POS4]);
        
        /* オド単位がkmの場合 */
        if(u1_t_odounit == VIS_CAN_ODO_UNIT_KM){
            /* 最大値を超える場合 */
            if(u4_t_odo > VIS_CAN_ODO_MAX_KM){
                u4_s_vis_can_ododata = VIS_CAN_ODO_FAIL;
            }
            /* 最大値以下の場合 */
            else{
                /* LSB変換 */
                u4_s_vis_can_ododata = u4_t_odo * VIS_CAN_ODO_LSB;
            }
        }
        /* オド単位がMileの場合 */
        else if(u1_t_odounit == VIS_CAN_ODO_UNIT_MILE){
            /* 最大値を超える場合 */
            if(u4_t_odo > VIS_CAN_ODO_MAX_MILE){
                u4_s_vis_can_ododata = VIS_CAN_ODO_FAIL;
            }
            /* 最大値以下の場合 */
            else{
                /* 単位変換(1mile =1.61km) LSB変換 */
                u4_s_vis_can_ododata = (u4_t_odo * VIS_CAN_ODO_MILE_TO_KM) / VIS_CAN_ODO_LSB;
            }
        }
        /* オド単位が異常の場合 */
        else{
            u4_s_vis_can_ododata = VIS_CAN_ODO_FAIL;
        }
    }
    /* MET1S02 正常受信していない場合 */
    else{
        u4_s_vis_can_ododata = VIS_CAN_ODO_FAIL;
    }
    
    u1_tp_ododata[VIS_CAN_TRANSREQ_DATA_ODOPOS1] = (U1)( u4_s_vis_can_ododata & VIS_CAN_4BYTEMASK_1BYTE);
    u1_tp_ododata[VIS_CAN_TRANSREQ_DATA_ODOPOS2] = (U1)((u4_s_vis_can_ododata & VIS_CAN_4BYTEMASK_2BYTE) >> VIS_CAN_SHIFT_1BYTE);
    u1_tp_ododata[VIS_CAN_TRANSREQ_DATA_ODOPOS3] = (U1)((u4_s_vis_can_ododata & VIS_CAN_4BYTEMASK_3BYTE) >> VIS_CAN_SHIFT_2BYTE);
    u1_tp_ododata[VIS_CAN_TRANSREQ_DATA_ODOPOS4] = (U1)((u4_s_vis_can_ododata & VIS_CAN_4BYTEMASK_4BYTE) >> VIS_CAN_SHIFT_3BYTE);
    
    /* チップ間通信定期送信要求 */
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_ODO, sizeof(u1_tp_ododata), u1_tp_ododata);
    
    return;
}
/* -------------------------------------------------------------------------- */
static void vd_s_VISCanGetTripCnt(void)
{
    U1 u1_t_msgsts;     /* 受信フレームの状態 */
    U1 u1_tp_tripcnt[VIS_CAN_TRANSREQ_DATA_TRIPNUM];

    
    /* Tripカウンタ情報取得 */
    /* BDB1F03メッセージの状態取得 */
    u1_t_msgsts = (U1)Com_GetIPDUStatus(MSG_BDB1F03_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    /* BDB1F03 正常受信の場合 */
    if(u1_t_msgsts == VIS_CAN_COM_IPDUST_OK){
        /* Tripカウンタ値取得 */
        (void)Com_ReceiveSignal(ComConf_ComSignal_TRIP_CNT, &u2_s_vis_can_tripcnt);
        /* Tripカウンタ値がFail値ではない場合*/
        if(u2_s_vis_can_tripcnt != VIS_CAN_TRIP_FAIL){
            u1_s_vis_can_sync = VIS_CAN_TRIP_SYNC;
        }
    }
    /* BDB1F03 通信途絶の場合 */
    else if(u1_t_msgsts == (U1)COM_TIMEOUT){
        u1_s_vis_can_sync = VIS_CAN_TRIP_ASYNC;
    }
    else{
        /* do nothing */
    }
    
    u1_tp_tripcnt[VIS_CAN_TRANSREQ_DATA_TRIPPOS1] = (U1)( u2_s_vis_can_tripcnt & VIS_CAN_2BYTEMASK_LOW);
    u1_tp_tripcnt[VIS_CAN_TRANSREQ_DATA_TRIPPOS2] = (U1)((u2_s_vis_can_tripcnt & VIS_CAN_2BYTEMASK_HIGH) >> VIS_CAN_SHIFT_1BYTE);
    u1_tp_tripcnt[VIS_CAN_TRANSREQ_DATA_SYNC] = u1_s_vis_can_sync;
    
    /* チップ間通信定期送信要求 */
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_TRIP, sizeof(u1_tp_tripcnt), u1_tp_tripcnt);
    
    return;
}
/* -------------------------------------------------------------------------- */
static void vd_s_VISCanGetSpd(void)
{
    U1 u1_t_responsestate;                          /* 車両電源ステート受信状態 */
    U1 u1_t_basicstate = VIS_BASICSTATE_CHECKING;   /* 車両電源ステート */
    U1 u1_t_msgsts;                                 /* 受信フレームの状態 */
    U2 u2_t_gvspd = VIS_CAN_SPD_FAIL;               /* "GVSPD信号"推定車体速 */
    
    /* 車速情報取得 */
    /* ★車両電源ステート(基本ステート)情報を取得 */
    u1_t_responsestate = u1_g_VISPwrGetBasicState(&u1_t_basicstate);
    /* 車両電源ステート受信状態が正常受信の場合 */
    if(u1_t_responsestate == VIS_COMMUNICATION_OK){
        /* 車両電源ステートがPowerON通常、PowerON緊急停止の場合 */
        if((u1_t_basicstate == VIS_BASICSTATE_POWERON_NORMAL) || (u1_t_basicstate == VIS_BASICSTATE_POWERON_EMERGENCY)){
            /* VSC1G13メッセージの状態取得 */
            u1_t_msgsts = (U1)Com_GetIPDUStatus(MSG_VSC1G13_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
            /* VSC1G13 正常受信の場合 */
            if(u1_t_msgsts == VIS_CAN_COM_IPDUST_OK){
                /* GVSPD信号取得 */
                (void)Com_ReceiveSignal(ComConf_ComSignal_GVSPD, &u2_t_gvspd);
                /* LSBを0.01km/hから1km/hに変換 */
                u2_t_gvspd = u2_t_gvspd / VIS_CAN_SPD_LSB;
                /* 車速値を更新 */
                if(u2_t_gvspd > VIS_CAN_SPD_MAX){
                    /* 最大値でガード */
                    u1_s_vis_can_spddata = (U1)VIS_CAN_SPD_MAX;
                }
                else{
                    u1_s_vis_can_spddata = (U1)u2_t_gvspd;
                }
            }
            /* VSC1G13 正常受信していない場合 */
            else{
                u1_s_vis_can_spddata = VIS_CAN_SPD_FAIL;
            }
        }
        /* 車両電源ステートが乗車中以下の場合 */
        else{
            u1_s_vis_can_spddata = VIS_CAN_SPD_FAIL;
        }
    }
    /* 車両電源ステート受信状態が正常受信以外の場合 */
    else{
        u1_s_vis_can_spddata = VIS_CAN_SPD_FAIL;
    }
    
    /* チップ間通信定期送信要求 */
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_SPD, VIS_CAN_TRANSREQ_DATA_LENGTH_1, &u1_s_vis_can_spddata);
    
    return;
}
/* -------------------------------------------------------------------------- */
static void vd_s_VISCanGetRdySts(void)
{
    U1 u1_t_responsestate;                          /* 車両電源ステート受信状態 */
    U1 u1_t_basicstate = VIS_BASICSTATE_CHECKING;   /* 車両電源ステート */
    U1 u1_t_msgsts;                                 /* 受信フレームの状態 */
    U1 u1_t_drdysts = VIS_CAN_DRDYSTS_NON;          /* "Ready"インジケータの表示状態 */
    
    /* 電動システム起動状態取得 */
    /* ★車両電源ステート(基本ステート)情報を取得 */
    u1_t_responsestate = u1_g_VISPwrGetBasicState(&u1_t_basicstate);
    /* 車両電源ステート受信状態が正常受信の場合 */
    if(u1_t_responsestate == VIS_COMMUNICATION_OK){
        /* 車両電源ステートがPowerON通常、PowerON緊急停止の場合 */
        if((u1_t_basicstate == VIS_BASICSTATE_POWERON_NORMAL) || (u1_t_basicstate == VIS_BASICSTATE_POWERON_EMERGENCY)){
            /* ECT1S93 メッセージの状態取得 */
            u1_t_msgsts = (U1)Com_GetIPDUStatus(MSG_ECT1S93_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
            /* ECT1S93 正常受信の場合 */
            if(u1_t_msgsts == VIS_CAN_COM_IPDUST_OK){
                /* "Ready"インジケータの表示状態取得 */
                (void)Com_ReceiveSignal(ComConf_ComSignal_DRDYSTS, &u1_t_drdysts);
                /* "Ready"インジケータの表示状態が「点灯」の場合 */
                if(u1_t_drdysts == (U1)VIS_CAN_DRDYSTS_LIGHT){
                    u1_s_vis_can_rdystsdata = VIS_CAN_E_PWRCTRLSYS_RDYSTS_ON;
                }
                else{
                    u1_s_vis_can_rdystsdata = VIS_CAN_E_PWRCTRLSYS_RDYSTS_OFF;
                }
            }
            /* ECT1S93 正常受信していない場合 */
            else{
                u1_s_vis_can_rdystsdata = VIS_CAN_E_PWRCTRLSYS_RDYSTS_OFF;
            }
        }
        /* 車両電源ステートが乗車中以下の場合 */
        else{
            u1_s_vis_can_rdystsdata = VIS_CAN_E_PWRCTRLSYS_RDYSTS_OFF;
        }
    }
    /* 車両電源ステート受信状態が正常受信以外の場合 */
    else{
        u1_s_vis_can_rdystsdata = VIS_CAN_E_PWRCTRLSYS_RDYSTS_OFF;
    }

    /* チップ間通信定期送信要求 */
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_RDYSTS, VIS_CAN_TRANSREQ_DATA_LENGTH_1, &u1_s_vis_can_rdystsdata);

    return;
}

/* -------------------------------------------------------------------------- */
static void vd_s_VISCanGetVin(void)
{
    U1 u1_tp_rx[VIS_CAN_VIN_RX_NBYTE];
    U1 u1_tp_transreq_data[VIS_CAN_TRANSREQ_DATA_LENGTH_18];
    U1 u1_t_datacnt;
    U1 u1_t_ipdu_st;

    /* 格納先の初期化 */
    LIB_memset(u1_tp_rx, VIS_VIN_INIT_VAL, sizeof(u1_tp_rx));

    /* ENG1S51メッセージ状態取得 */
    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_ENG1S51_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if (VIS_CAN_COM_IPDUST_OK == u1_t_ipdu_st){
        /* ENG1S51メッセージ読み出し */
        (void)Com_ReadIPDU((U2)MSG_ENG1S51_RXCH0, &u1_tp_rx[VIS_CAN_VIN0_NM]);

        u1_s_vis_vin_responsestate = VIS_COMMUNICATION_OK;              /* CANメッセージ受信状態：正常受信 */
        
        /* VINデータ設定 */
        for (u1_t_datacnt = VIS_CAN_VIN0_NM; u1_t_datacnt < VIS_VIN_MAX_NM; u1_t_datacnt++) {
            u1_sp_vis_can_vindata[u1_t_datacnt] = u1_tp_rx[u1_t_datacnt];
        }
    }
    else if ((U1)COM_TIMEOUT == u1_t_ipdu_st){
        u1_s_vis_vin_responsestate = VIS_COMMUNICATION_ERROR;           /* CANメッセージ受信状態：途絶 */
    }
    else{
        /* do nothing */
    }

    /* チップ間通信_送信要求 */
    for (u1_t_datacnt = VIS_CAN_VIN0_NM; u1_t_datacnt < VIS_VIN_MAX_NM; u1_t_datacnt++){
            u1_tp_transreq_data[u1_t_datacnt] = u1_sp_vis_can_vindata[u1_t_datacnt];
    }
    u1_tp_transreq_data[VIS_CAN_TRANSREQ_VINDATA_RETURNVAL] = u1_s_vis_vin_responsestate;

    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_VIN,VIS_CAN_TRANSREQ_DATA_LENGTH_18,u1_tp_transreq_data);

    return;
}

/* -------------------------------------------------------------------------- */
static void vd_s_VISCanGetOtaswact(void)
{
    U1 u1_t_otaswact_data = (U1)STD_OFF;
    U1 u1_tp_transreq_data[VIS_CAN_TRANSREQ_DATA_LENGTH_2];
    U1 u1_t_ipdu_st;
    
    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_AVN1S95_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if (VIS_CAN_COM_IPDUST_OK == u1_t_ipdu_st){
        (void)Com_ReceiveSignal(ComConf_ComSignal_OTASWACT, &u1_t_otaswact_data);

        u1_s_vis_otaswact_responsestate = VIS_COMMUNICATION_OK;             /* CANメッセージ受信状態：正常受信 */

        if (VIS_CAN_RCV_CHK >= u1_t_otaswact_data) {
            u1_s_vis_can_otaswact = u1_t_otaswact_data;
        }
        else {
            u1_s_vis_otaswact_responsestate = VIS_UNDEFINED_VALUE;          /* CANメッセージ受信状態：範囲外 */
        }
    }
    else if ((U1)COM_TIMEOUT == u1_t_ipdu_st){
        u1_s_vis_otaswact_responsestate = VIS_COMMUNICATION_ERROR;          /* CANメッセージ受信状態：途絶 */
    }
    else{
        /* do nothing */
    }

    /* チップ間通信_送信要求 */
    u1_tp_transreq_data[VIS_CAN_TRANSREQ_DATA_RECEIVEVAL] = u1_s_vis_can_otaswact;
    u1_tp_transreq_data[VIS_CAN_TRANSREQ_DATA_RETURNVAL] = u1_s_vis_otaswact_responsestate;
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_OTASWACT,VIS_CAN_TRANSREQ_DATA_LENGTH_2,u1_tp_transreq_data);
    
    return;
}

/* -------------------------------------------------------------------------- */
static void vd_s_VISCanGetPwrerrst(void)
{
    U1 u1_t_pwrerrst_data = VIS_NORMAL_USERDRIVEN;
    U1 u1_tp_transreq_data[VIS_CAN_TRANSREQ_DATA_LENGTH_2];
    U1 u1_t_ipdu_st;
    
    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S82_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if (VIS_CAN_COM_IPDUST_OK == u1_t_ipdu_st){
        (void)Com_ReceiveSignal(ComConf_ComSignal_PWRERRST, &u1_t_pwrerrst_data);

        u1_s_vis_pwrerrst_responsestate = VIS_COMMUNICATION_OK;             /* CANメッセージ受信状態：正常受信 */

        if (VIS_CAN_RCV_PWRERRST_CHK >= u1_t_pwrerrst_data) {
            u1_s_vis_can_pwrerrst = u1_t_pwrerrst_data;
        }
        else {
            u1_s_vis_pwrerrst_responsestate = VIS_UNDEFINED_VALUE;          /* CANメッセージ受信状態：範囲外 */
        }
    }
    else if ((U1)COM_TIMEOUT == u1_t_ipdu_st){
        u1_s_vis_pwrerrst_responsestate = VIS_COMMUNICATION_ERROR;          /* CANメッセージ受信状態：途絶 */
    }
    else{
        /* do nothing */
    }

    /* チップ間通信_送信要求 */
    u1_tp_transreq_data[VIS_CAN_TRANSREQ_DATA_RECEIVEVAL] = u1_s_vis_can_pwrerrst;
    u1_tp_transreq_data[VIS_CAN_TRANSREQ_DATA_RETURNVAL] = u1_s_vis_pwrerrst_responsestate;
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_PWRERRST,VIS_CAN_TRANSREQ_DATA_LENGTH_2,u1_tp_transreq_data);

    return;
}

/* -------------------------------------------------------------------------- */
static void vd_s_VISCanGetCrlyof(void)
{
    U1 u1_t_crlyof_data = (U1)STD_OFF;
    U1 u1_tp_transreq_data[VIS_CAN_TRANSREQ_DATA_LENGTH_2];
    U1 u1_t_ipdu_st;
    
    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S82_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if (VIS_CAN_COM_IPDUST_OK == u1_t_ipdu_st){
        (void)Com_ReceiveSignal(ComConf_ComSignal_CRLYOF, &u1_t_crlyof_data);

        u1_s_vis_crlyof_responsestate = VIS_COMMUNICATION_OK;               /* CANメッセージ受信状態：正常受信 */

        if (VIS_CAN_RCV_CHK >= u1_t_crlyof_data) {
            u1_s_vis_can_crlyof = u1_t_crlyof_data;
        }
        else {
            u1_s_vis_crlyof_responsestate = VIS_UNDEFINED_VALUE;            /* CANメッセージ受信状態：範囲外 */
        }
    }
    else if ((U1)COM_TIMEOUT == u1_t_ipdu_st){
        u1_s_vis_crlyof_responsestate = VIS_COMMUNICATION_ERROR;            /* CANメッセージ受信状態：途絶 */
    }
    else{
        /* do nothing */
    }

    /* チップ間通信_送信要求 */
    u1_tp_transreq_data[VIS_CAN_TRANSREQ_DATA_RECEIVEVAL] = u1_s_vis_can_crlyof;
    u1_tp_transreq_data[VIS_CAN_TRANSREQ_DATA_RETURNVAL] = u1_s_vis_crlyof_responsestate;
    (void)ChipCom_SetPeriodicTxData((U1)CHIPCOM_PERIODICID_VIS_CRLYOF,VIS_CAN_TRANSREQ_DATA_LENGTH_2,u1_tp_transreq_data);

    return;
}

/* -------------------------------------------------------------------------- */
static U1 u1_s_VISCanUtcCheckLimit(const U1 u1_a_DATA, const U1 u1_a_MIN, const U1 u1_a_MAX)
{
    U1 u1_t_ret= (U1)E_OK;    /* 範囲チェック */
    
    if (u1_a_DATA < u1_a_MIN) { u1_t_ret = (U1)E_NOT_OK; }
    if (u1_a_DATA > u1_a_MAX) { u1_t_ret = (U1)E_NOT_OK; }
    
    return u1_t_ret;
}
/* -------------------------------------------------------------------------- */
static U1 u1_s_VISCanUtcCheckVal(const ST_VIS_UTC * const st_ap_UTCDATA)
{
    U1 u1_t_ret = (U1)E_OK;    /* 範囲チェック */
    
    if (u1_s_VISCanUtcCheckLimit(st_ap_UTCDATA->u1_year,  VIS_CAN_UTC_YEARMIN ,VIS_CAN_UTC_YEARMAX) == (U1)E_NOT_OK) { u1_t_ret = (U1)E_NOT_OK; }
    if (u1_s_VISCanUtcCheckLimit(st_ap_UTCDATA->u1_month, VIS_CAN_UTC_MONTMIN ,VIS_CAN_UTC_MONTMAX) == (U1)E_NOT_OK) { u1_t_ret = (U1)E_NOT_OK; }
    if (u1_s_VISCanUtcCheckLimit(st_ap_UTCDATA->u1_day,   VIS_CAN_UTC_DAYMIN  ,VIS_CAN_UTC_DAYMAX)  == (U1)E_NOT_OK) { u1_t_ret = (U1)E_NOT_OK; }
    if (u1_s_VISCanUtcCheckLimit(st_ap_UTCDATA->u1_hour,  VIS_CAN_UTC_HOURMIN ,VIS_CAN_UTC_HOURMAX) == (U1)E_NOT_OK) { u1_t_ret = (U1)E_NOT_OK; }
    if (u1_s_VISCanUtcCheckLimit(st_ap_UTCDATA->u1_minute,VIS_CAN_UTC_MINMIN  ,VIS_CAN_UTC_MINMAX)  == (U1)E_NOT_OK) { u1_t_ret = (U1)E_NOT_OK; }
    if (u1_s_VISCanUtcCheckLimit(st_ap_UTCDATA->u1_second,VIS_CAN_UTC_SECMIN  ,VIS_CAN_UTC_SECMAX)  == (U1)E_NOT_OK) { u1_t_ret = (U1)E_NOT_OK; }

    return u1_t_ret;
}

/* -------------------------------------------------------------------------- */
/* #define VIS_STOP_SEC_CODE */
/* #include <VIS_MemMap.h> */
/* -------------------------------------------------------------------------- */
