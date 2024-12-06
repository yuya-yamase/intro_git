/* Mcu_PwrCtrl_c_v1-0-0                                                     */
/****************************************************************************/
/* Copyright (C) 2023 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Mcu_PwrCtrl/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Ecu_Intg.h>
#include <Ecu_IntgHAL.h>

#include "Mcu_Common.h"
#include "Mcu_PwrCtrl.h"
#include "Mcu_Sip_Pwr.h"
#include "Mcu_Main.h"
#include "Mcu_Sys_Pwr.h"
#include "Mcu_Noredun_PwrCtrl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* SYS電源状態 */
#define MCU_PWRCTRL_SYS_STS_INIT       (0x00)  /* 初期状態 */
#define MCU_PWRCTRL_SYS_STS_INPRC      (0x01)  /* 実行中 */
#define MCU_PWRCTRL_SYS_STS_COMP       (0x02)  /* 完了 */
#define MCU_PWRCTRL_SYS_STS_WAITDEV    (0x03)  /* SYSデバイス終了待ち */

/* 非冗長電源状態 */
#define MCU_PWRCTRL_NRD_STS_INIT       (0x00)  /* 初期状態 */
#define MCU_PWRCTRL_NRD_STS_INPRC      (0x01)  /* 実行中 */
#define MCU_PWRCTRL_NRD_STS_COMP       (0x02)  /* 完了*/

/* SiP電源状態 */
#define MCU_PWRCTRL_SIP_STS_INIT       (0x00)  /* 初期状態 */
#define MCU_PWRCTRL_SIP_STS_INPRC      (0x01)  /* 実行中 */
#define MCU_PWRCTRL_SIP_STS_COMP       (0x02)  /* 完了 */
#define MCU_PWRCTRL_SIP_STS_CHK_MMSTBY (0x03)  /* MM_STBY_N変化待ち */
#define MCU_PWRCTRL_SIP_STS_CHK_AOSS   (0x04)  /* AOSS_SLEEP_ENTRY_EXIT変化待ち */

/* Dio端子監視結果 */
#define MCU_PWRCTRL_DIO_READ_CHK_INIT    (0x00) /* 状態監視初期状態 */
#define MCU_PWRCTRL_DIO_READ_CHK_OK      (0x01) /* 指定時間内に正常応答 */
#define MCU_PWRCTRL_DIO_READ_CHK_NG      (0xFF) /* 時間超過or異常応答 */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void vd_s_Mcu_PwrCtrl_Start_Set(void);
static void vd_s_Mcu_PwrCtrl_Bon_Seq(void);
static void vd_s_Mcu_PwrCtrl_WakeUp_Seq(void);
static void vd_s_Mcu_PwrCtrl_SipOff_McuStandby_Seq(void);
static void vd_s_Mcu_PwrCtrl_Standby_Seq(void);
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static uint8 u1_s_Mcu_PwrCtrl_Sts;                        /* 電源制御状態   */
static uint8 u1_s_Mcu_PwrCtrl_SysPwrSts;                  /* SYS電源状態    */
static uint8 u1_s_Mcu_PwrCtrl_NonRednPwrSts;              /* 非冗長電源状態 */
static uint8 u1_s_Mcu_PwrCtrl_SipPwrSts;                  /* SiP電源状態    */
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/*****************************************************************************
  Function      : vd_g_Mcu_PwrCtrl_Bon_Wakeup_Req
  Description   : +B-ON,ウェイクアップシーケンス要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_Mcu_PwrCtrl_Bon_Wakeup_Req(Ecu_Intg_BootCauseType u4BootCause) /* 暫定BSW_BEVCDCFD-429 */
{
#if 0
    switch(u4BootCause)
    {
    case ECU_INTG_u4BTCAUSE_PON:            /* +B ON */
#endif
        Mcu_Main_Bon_Init();                /* SYS電源 非常長電源 +B初期化要求 */
        Mcu_Sip_Bon_Init();                 /* SiP電源状態+B初期化要求 */
        /* +B-ONシーケンス実施要求 */
        u1_s_Mcu_PwrCtrl_Sts = MCU_PWRCTRL_BON_REQ;
        vd_s_Mcu_PwrCtrl_Start_Set();
#if 0
        break;
    case ECU_INTG_u4BTCAUSE_RESET:         /* リセット */
    case ECU_INTG_u4BTCAUSE_WKUP_ANY:      /* Wakeup */
    case ECU_INTG_u4BTCAUSE_WKUP_TMR:      /* Wakeup */
    case ECU_INTG_u4BTCAUSE_WKUP_OTHS:     /* 上記以外リセット */
    default:                                /* 異常ルート */
        Mcu_Main_Wkup_Init();               /* SYS電源 非常長電源 Wakeup初期化要求 */
        Mcu_Sip_Wkup_Init();                /* SiP電源状態Wakeup初期化要求 */
        /* ウェイクアップシーケンス実施要求 */
        u1_s_Mcu_PwrCtrl_Sts = MCU_PWRCTRL_WAKEUP_REQ;
        vd_s_Mcu_PwrCtrl_Start_Set();
        break;
    }
#endif
    return;
}

/*****************************************************************************
  Function      : vd_g_Mcu_PwrCtrl_SipOffMcuStandby_Req
  Description   : SIP電源OFF&MCUスタンバイシーケンス要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_Mcu_PwrCtrl_SipOffMcuStandby_Req(void)
{
	/* ★要検討★処理実行中は要求を受け付けない */
	if(u1_s_Mcu_PwrCtrl_Sts == MCU_PWRCTRL_NO_REQ){
		u1_s_Mcu_PwrCtrl_Sts = MCU_PWRCTRL_SIPOFF_MCUSTANDBY_REQ;
        vd_s_Mcu_PwrCtrl_Start_Set();
	}
}

/*****************************************************************************
  Function      : vd_g_Mcu_PwrCtrl_Standby_Req
  Description   : スタンバイシーケンス要求
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_Mcu_PwrCtrl_Standby_Req(void)
{
	/* ★要検討★処理実行中は要求を受け付けない */
	if(u1_s_Mcu_PwrCtrl_Sts == MCU_PWRCTRL_NO_REQ){
		u1_s_Mcu_PwrCtrl_Sts = MCU_PWRCTRL_STANDBY_REQ;
        vd_s_Mcu_PwrCtrl_Start_Set();
	}
}

/*****************************************************************************
  Function      : vd_g_Mcu_PwrCtrl_Task1ms
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_Mcu_PwrCtrl_Task1ms( void )
{
    
    switch (u1_s_Mcu_PwrCtrl_Sts)
    {
    case MCU_PWRCTRL_BON_REQ:           /* +B起動シーケンス */
        vd_s_Mcu_PwrCtrl_Bon_Seq();
        break;
    case MCU_PWRCTRL_WAKEUP_REQ:        /* ウェイクアップシーケンス */
        vd_s_Mcu_PwrCtrl_WakeUp_Seq();
        break;
    case MCU_PWRCTRL_SIPOFF_MCUSTANDBY_REQ: /* SIP電源OFF&MCUスタンバイシーケンス */
        /* ★要検討：Sleep系のタスク(ポストタスク)に配置が必要？★ */
        vd_s_Mcu_PwrCtrl_SipOff_McuStandby_Seq();
        break;
        /* ★要検討：Sleep系のタスク(ポストタスク)に配置が必要？★ */
    case MCU_PWRCTRL_STANDBY_REQ:       /* スタンバイシーケンス */
        vd_s_Mcu_PwrCtrl_Standby_Seq();
        break;
    default:
        break;
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_Mcu_PwrCtrl_Start_Set
  Description   : シーケンス開始処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_Mcu_PwrCtrl_Start_Set( void )
{
    u1_s_Mcu_PwrCtrl_SysPwrSts     = MCU_PWRCTRL_SYS_STS_INIT;      /* SYS電源：初期状態 */
    u1_s_Mcu_PwrCtrl_NonRednPwrSts = MCU_PWRCTRL_NRD_STS_INIT;      /* 非冗長電源：初期状態 */
    u1_s_Mcu_PwrCtrl_SipPwrSts     = MCU_PWRCTRL_SIP_STS_INIT;      /* SiP電源状態：初期状態 */
#if (MCU_ERR_CHK == 1U)
    /* 異常系確認用RAMの初期化 */
    u1_s_Mcu_Err_dbg_state = (uint8)MCU_ERR_NON; /* TP */
    /* 異常系確認用RAMの初期化 */
#endif
    return;

}

/*****************************************************************************
  Function      : vd_s_Mcu_PwrCtrl_Bon_Seq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_Mcu_PwrCtrl_Bon_Seq(void)
{
    uint8 u1_t_syson_seq;   /* SYS電源ONシーケンス状態問い合わせ結果 */
    uint8 u1_t_nrdon_seq;   /* 非冗長電源ONシーケンス状態問い合わせ結果 */
    uint8 u1_t_sipon_seq;   /* SiP電源ONシーケンス状態問い合わせ結果 */
    uint8 u1_t_read_lv;     /* MCU端子状態取得結果 */

/* SYS電源ON要求 */
    if(u1_s_Mcu_PwrCtrl_SysPwrSts == MCU_PWRCTRL_SYS_STS_INIT){
        u1_s_Mcu_PwrCtrl_SysPwrSts = MCU_PWRCTRL_SYS_STS_INPRC;             /* SYS電源状態:初期状態→実行中 */
        Mcu_Sys_PwrOn_Start();                                              /* SYS電源ON要求 */
    }

/* 非冗長電源ON要求 */
    if(u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INIT){
        u1_s_Mcu_PwrCtrl_NonRednPwrSts = MCU_PWRCTRL_NRD_STS_INPRC;         /* 非冗長電源状態:初期状態→実行中 */
        Mcu_Noredun_PwrOn_Start();                                          /* 非冗長電源ON要求 */
    }

/* MET/IVI定期処理(5ms) */
    if( (u1_s_Mcu_PwrCtrl_SysPwrSts     == MCU_PWRCTRL_SYS_STS_INPRC)         /* SYS電源状態:実行中 */
     || (u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INPRC) ){      /* または、非冗長電源状態:実行中 */
        Mcu_Main_Pwrsup_Function();                                           /* MET/IVI定期処理(5ms) */
    }

/* SYS電源ONシーケンス状態問い合わせ */
    if(u1_s_Mcu_PwrCtrl_SysPwrSts == MCU_PWRCTRL_SYS_STS_INPRC){
        u1_t_syson_seq = Mcu_Sys_PwrOn_GetSts();                            /* SYS電源ONシーケンス状態問い合わせ */
        if(u1_t_syson_seq == (uint8)TRUE ){                                 /* 処理完了 */
            u1_s_Mcu_PwrCtrl_SysPwrSts = MCU_PWRCTRL_SYS_STS_COMP;          /* SYS電源状態：実行中→完了 */
            u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_INPRC;         /* SiP電源状態：初期状態→実行中 */
            Mcu_Sip_PwrOn_Req();                                            /* SiP電源ON要求(+B ON) */
        }
    }

/* 非冗長電源ONシーケンス状態問い合わせ */
    if(u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INPRC){
        u1_t_nrdon_seq = Mcu_Noredun_PwrOn_GetSts();                        /* 非冗長電源ONシーケンス状態問い合わせ */
        if(u1_t_nrdon_seq == (uint8)TRUE){                                  /* 処理完了 */
            u1_s_Mcu_PwrCtrl_NonRednPwrSts = MCU_PWRCTRL_NRD_STS_COMP;      /* 非冗長電源状態：実行中→完了 */
        }
    }

/* SiP電源定期処理 */
    if(u1_s_Mcu_PwrCtrl_SipPwrSts == MCU_PWRCTRL_SIP_STS_INPRC){
        Mcu_Sip_Pwr_MainFunction();                                         /* SiP電源 定期処理 */
        u1_t_sipon_seq = Mcu_Sip_PwrOn_GetSts();                            /* SiP電源ONシーケンス状態問い合わせ */
        if(u1_t_sipon_seq == (uint8)MCU_SIP_PWR_COMP){                      /* 処理完了 */
            /* BEVCDCFD-277 【暫定管理】1Sボード起動用のMCUパッチ充て */
            /* MM_STBYを確認するSTEPをスキップし、SIP電源起動完了を設定 */
            /* u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_CHK_MMSTBY; */   /* SiP電源状態：実行中→MM_STBY_N=Hi判定中 */
            u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_COMP;              /* SiP電源状態：実行中→完了 */
        }
    }
/* MM_STBY_N =Hi?(SOCメインドメインのQNX起動完了の確認) */
    if(u1_s_Mcu_PwrCtrl_SipPwrSts == MCU_PWRCTRL_SIP_STS_CHK_MMSTBY){
        u1_t_read_lv = Dio_ReadChannel(DIO_ID_PORT10_CH11);                 /* MM_STBY_N端子の状態を取得 */
        if (u1_t_read_lv == MCU_DIO_HIGH) {
            u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_COMP;          /* SiP電源状態：MM_STBY_N=Hi判定中→完了 */
        }
#if (MCU_ERR_CHK == 1U)
        u1_s_Mcu_Err_dbg_state = MCU_ERR_BON_MMSTBY; /* TP */
#endif
    }

/* 終了処理 */
    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if( (u1_s_Mcu_PwrCtrl_SysPwrSts     == MCU_PWRCTRL_SYS_STS_COMP)
     && (u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_COMP)
     && (u1_s_Mcu_PwrCtrl_SipPwrSts     == MCU_PWRCTRL_SIP_STS_COMP)){
        u1_s_Mcu_PwrCtrl_Sts = MCU_PWRCTRL_NO_REQ;                          /* 処理完了 */
#if (MCU_ERR_CHK == 1U)
        u1_s_Mcu_Err_dbg_state = (uint8)MCU_ERR_NON;                           /* 異常系エラーなし */
#endif

    }

    return;
}

/*****************************************************************************
  Function      : vd_s_Mcu_PwrCtrl_WakeUp_Seq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_Mcu_PwrCtrl_WakeUp_Seq(void)
{
    uint8 u1_t_syson_seq;   /* SYS電源ONシーケンス状態問い合わせ結果 */
    uint8 u1_t_nrdon_seq;   /* 非冗長電源ONシーケンス状態問い合わせ結果 */
    uint8 u1_t_sipon_seq;   /* SiPレジューム起動シーケンス状態問い合わせ結果 */
    uint8 u1_t_read_lv;     /* MCU端子状態取得結果 */

/* SYS電源ON要求 */
    if(u1_s_Mcu_PwrCtrl_SysPwrSts == MCU_PWRCTRL_SYS_STS_INIT){
        u1_s_Mcu_PwrCtrl_SysPwrSts = MCU_PWRCTRL_SYS_STS_INPRC;             /* SYS電源状態:初期状態→実行中 */
        Mcu_Sys_PwrOn_Start();                                              /* SYS電源ON要求 */
    }

/* 非冗長電源ON要求 */
    if(u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INIT){
        u1_s_Mcu_PwrCtrl_NonRednPwrSts = MCU_PWRCTRL_NRD_STS_INPRC;         /* 非冗長電源状態:初期状態→実行中 */
        Mcu_Noredun_PwrOn_Start();                                          /* 非冗長電源ON要求 */
    }

/* MET/IVI定期処理(5ms) */
    if( (u1_s_Mcu_PwrCtrl_SysPwrSts     == MCU_PWRCTRL_SYS_STS_INPRC)      /* SYS電源状態:実行中 */
     || (u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INPRC) ){   /* または、非冗長電源状態:実行中 */
        Mcu_Main_Pwrsup_Function();                                        /* MET/IVI定期処理(5ms) */
    }

/* SYS電源ONシーケンス状態問い合わせ */
    if(u1_s_Mcu_PwrCtrl_SysPwrSts == MCU_PWRCTRL_SYS_STS_INPRC){
        u1_t_syson_seq = Mcu_Sys_PwrOn_GetSts();                           /* SYS電源ONシーケンス状態問い合わせ */
        if(u1_t_syson_seq == (uint8)TRUE){                                 /* 処理完了 */
/* AOSS_SLEEP_ENTRY_EXIT＝Hi？(SIPがサスペンド状態であることを確認※1度のみ実施) */
            u1_t_read_lv = Dio_ReadChannel(DIO_ID_PORT17_CH0);             /* AOSS_SLEEP_ENTRY_EXIT端子の状態を取得    */
            if(u1_t_read_lv == MCU_DIO_HIGH){
                u1_s_Mcu_PwrCtrl_SysPwrSts = MCU_PWRCTRL_SYS_STS_COMP;     /* SYS電源状態：実行中→完了 */
                u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_INPRC;    /* SiP電源状態：初期状態→実行中 */
                Mcu_Sip_Resume_Req();                                      /* SiP電源ON要求(WakeUp) */
            }
            else{
               /* 異常内容保存 */
               /* +B-ONシーケンス実施(未実装) */
#if (MCU_ERR_CHK == 1U)
                u1_s_Mcu_Err_dbg_state = MCU_ERR_WAKE_AOSS_HI; /* TP */
#endif
            }
        }
    }

/* 非冗長電源ONシーケンス状態問い合わせ */
    if(u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INPRC){
        u1_t_nrdon_seq = Mcu_Noredun_PwrOn_GetSts();                        /* 非冗長電源ONシーケンス状態問い合わせ */
        if(u1_t_nrdon_seq == (uint8)TRUE){                                  /* 処理完了 */
            u1_s_Mcu_PwrCtrl_NonRednPwrSts = MCU_PWRCTRL_NRD_STS_COMP;      /* 非冗長電源状態：実行中→完了 */
        }
    }

/* SiP電源定期処理 */
    if(u1_s_Mcu_PwrCtrl_SipPwrSts == MCU_PWRCTRL_SIP_STS_INPRC){
        Mcu_Sip_Pwr_MainFunction();                                         /* SiP電源 定期処理 */
        u1_t_sipon_seq = Mcu_Sip_Resume_GetSts();                           /* SiPレジューム起動シーケンス状態問い合わせ */
        if(u1_t_sipon_seq == (uint8)MCU_SIP_PWR_COMP){                      /* 処理完了 */
            u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_CHK_AOSS;      /* SiP電源状態：実行中→AOSS_SLEEP_ENTRY_EXIT=Low判定中 */
        }
    }

/* AOSS_SLEEP_ENTRY_EXIT=Lo?(PMICからのSIP電源レジューム完了確認) */
    if(u1_s_Mcu_PwrCtrl_SipPwrSts == MCU_PWRCTRL_SIP_STS_CHK_AOSS){
        u1_t_read_lv = Dio_ReadChannel(DIO_ID_PORT17_CH0);                   /* AOSS_SLEEP_ENTRY_EXIT端子の状態を取得    */
        if(u1_t_read_lv == MCU_DIO_LOW){
            /* BEVCDCFD-277 【暫定管理】1Sボード起動用のMCUパッチ充て */
            /* MM_STBYを確認するSTEPをスキップし、SIPWake了を設定 */
            /* u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_CHK_MMSTBY; */    /* SiP電源状態：AOSS_SLEEP_ENTRY_EXIT=Low判定中→MM_STBY_N=Hi判定中 */
            u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_COMP;     /* SiP電源状態：AOSS_SLEEP_ENTRY_EXIT=Low判定中→完了 */
        }
#if (MCU_ERR_CHK == 1U)
        u1_s_Mcu_Err_dbg_state = MCU_ERR_WAKE_AOSS_LO; /* TP */
#endif
    }

/* MM_STBY_N =Hi?(SOCメインドメインのQNX起動完了の確認) */
    if (u1_s_Mcu_PwrCtrl_SipPwrSts == MCU_PWRCTRL_SIP_STS_CHK_MMSTBY){
        u1_t_read_lv = Dio_ReadChannel(DIO_ID_PORT10_CH11);                  /* MM_STBY_N端子の状態を取得 */
        if(u1_t_read_lv == MCU_DIO_HIGH){
            u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_COMP;          /* SiP電源状態：MM_STBY_N=Hi判定中→完了 */
        }
#if (MCU_ERR_CHK == 1U)
        u1_s_Mcu_Err_dbg_state = MCU_ERR_WAKE_MMSTBY; /* TP */
#endif
    }

/* 終了処理 */
    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if( (u1_s_Mcu_PwrCtrl_SysPwrSts     == MCU_PWRCTRL_SYS_STS_COMP)
     && (u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_COMP)
     && (u1_s_Mcu_PwrCtrl_SipPwrSts     == MCU_PWRCTRL_SIP_STS_COMP)){
        u1_s_Mcu_PwrCtrl_Sts = MCU_PWRCTRL_NO_REQ;              /* 処理完了 */
#if (MCU_ERR_CHK == 1U)
        u1_s_Mcu_Err_dbg_state = (uint8)MCU_ERR_NON;               /* 異常系エラーなし */
#endif
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_Mcu_PwrCtrl_SipOff_McuStandby_Seq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_Mcu_PwrCtrl_SipOff_McuStandby_Seq(void)
{
    uint8 u1_t_sipoff_seq;   /* SiP電源OFFシーケンス状態問い合わせ結果 */
    uint8 u1_t_nrdoff_seq;   /* 非冗長電源OFFシーケンス状態問い合わせ結果 */
    uint8 u1_t_sysoff_seq;   /* SYS電源OFFシーケンス状態問い合わせ結果 */
    uint8 u1_t_devoff_seq;   /* SYS系デバイス終了状態問い合わせ結果 */

/* SiP電源OFF */
    if(u1_s_Mcu_PwrCtrl_SipPwrSts == MCU_PWRCTRL_SIP_STS_INIT){
        u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_INPRC;       /* SiP電源状態：開始→実行中 */
        Mcu_Sip_PwrOff_Req();                                         /* SiP電源OFF */
    }

    if(u1_s_Mcu_PwrCtrl_SipPwrSts == MCU_PWRCTRL_SIP_STS_INPRC){
        Mcu_Sip_Pwr_MainFunction();                                         /* SiP電源 定期処理 */

        /* SiP電源OFFシーケンス状態問い合わせ */
        u1_t_sipoff_seq = Mcu_Sip_PwrOff_GetSts();
        if(u1_t_sipoff_seq == (uint8)MCU_SIP_PWR_COMP){               /* 処理完了 */
            u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_COMP;    /* SiP電源状態：実行中→完了 */
            u1_s_Mcu_PwrCtrl_SysPwrSts = MCU_PWRCTRL_SYS_STS_WAITDEV; /* SYS電源状態：開始→SYSデバイス終了待ち */
        }
    }

/* 非冗長電源OFF要求 */
    if(u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INIT){
        u1_s_Mcu_PwrCtrl_NonRednPwrSts = MCU_PWRCTRL_NRD_STS_INPRC;      /* 非冗長電源状態:開始→実行中 */
        Mcu_Noredun_PwrOff_Start();                                      /* 非冗長電源OFF要求 */
    }

/* MET/IVI定期処理(5ms) */
    if( (u1_s_Mcu_PwrCtrl_SysPwrSts     == MCU_PWRCTRL_SYS_STS_INPRC)    /* SYS電源状態:実行中 */
     || (u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INPRC) ){ /* または、非冗長電源状態:実行中 */
        Mcu_Main_Pwrsup_Function();                                      /* MET/IVI定期処理(5ms) */
    }

/* SYS系デバイス終了状態問い合わせ */
    if(u1_s_Mcu_PwrCtrl_SysPwrSts == MCU_PWRCTRL_SYS_STS_WAITDEV){
        u1_t_devoff_seq = Mcu_Sys_Shtdwn_GetSts();                       /* SYS系デバイス終了状態問い合わせ */
        if(u1_t_devoff_seq == (uint8)TRUE){                              /* 処理完了 */
            u1_s_Mcu_PwrCtrl_SysPwrSts = MCU_PWRCTRL_SYS_STS_INPRC;      /* SYS電源状態:SYSデバイス終了待ち→実行中 */
/* SYS電源OFF要求 */
            Mcu_Sys_PwrOff_Start();                                      /* SYS電源OFF要求 */
        }
    }

/* 非冗長電源OFFシーケンス状態問い合わせ */
    if(u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INPRC){
        u1_t_nrdoff_seq = Mcu_Noredun_PwrOff_GetSts();                   /* 非冗長電源OFFシーケンス状態問い合わせ */
        if(u1_t_nrdoff_seq == (uint8)TRUE){                              /* 処理完了 */
            u1_s_Mcu_PwrCtrl_NonRednPwrSts = MCU_PWRCTRL_NRD_STS_COMP;   /* 非冗長電源状態：実行中→完了 */
        }
    }

/* SYS電源OFFシーケンス状態問い合わせ */
    if(u1_s_Mcu_PwrCtrl_SysPwrSts == MCU_PWRCTRL_SYS_STS_INPRC){
        u1_t_sysoff_seq = Mcu_Sys_PwrOff_GetSts();                       /* SYS電源OFFシーケンス状態問い合わせ */
        if(u1_t_sysoff_seq == (uint8)TRUE){                              /* 処理完了 */
            u1_s_Mcu_PwrCtrl_SysPwrSts = MCU_PWRCTRL_SYS_STS_COMP;       /* SYS電源状態：実行中→完了 */
        }
    }
/* 終了処理 */
    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if( (u1_s_Mcu_PwrCtrl_SysPwrSts     == MCU_PWRCTRL_SYS_STS_COMP)
     && (u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_COMP)
     && (u1_s_Mcu_PwrCtrl_SipPwrSts     == MCU_PWRCTRL_SIP_STS_COMP) ){
        u1_s_Mcu_PwrCtrl_Sts = MCU_PWRCTRL_NO_REQ;              /* 処理完了 */
#if (MCU_ERR_CHK == 1U)
        u1_s_Mcu_Err_dbg_state = (uint8)MCU_ERR_NON;               /* 異常系エラーなし */
#endif
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_Mcu_PwrCtrl_Standby_Seq(void)
  Description   : 
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_Mcu_PwrCtrl_Standby_Seq(void)
{
    uint8 u1_t_sipstb_seq;   /* SiPスタンバイシーケンス状態問い合わせ結果 */
    uint8 u1_t_nrdoff_seq;   /* 非冗長電源OFFシーケンス状態問い合わせ結果 */
    uint8 u1_t_sysoff_seq;   /* SYS電源OFFシーケンス状態問い合わせ結果 */
    uint8 u1_t_devoff_seq;   /* SYS系デバイス終了状態問い合わせ結果 */

/* SiP電源OFF */
    if(u1_s_Mcu_PwrCtrl_SipPwrSts == MCU_PWRCTRL_SIP_STS_INIT){
        u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_INPRC;       /* SiP電源状態：開始→実行中 */
        Mcu_Sip_Standby_Req();                                        /* SiPスタンバイ */
    }

    if(u1_s_Mcu_PwrCtrl_SipPwrSts == MCU_PWRCTRL_SIP_STS_INPRC){
        Mcu_Sip_Pwr_MainFunction();                                   /* SiP電源 定期処理 */

        /* SiPスタンバイシーケンス状態問い合わせ */
        u1_t_sipstb_seq = Mcu_Sip_Standby_GetSts();
        if(u1_t_sipstb_seq == (uint8)MCU_SIP_PWR_COMP){               /* 処理完了 */
            u1_s_Mcu_PwrCtrl_SipPwrSts = MCU_PWRCTRL_SIP_STS_COMP;    /* SiP電源状態：実行中→完了 */
            u1_s_Mcu_PwrCtrl_SysPwrSts = MCU_PWRCTRL_SYS_STS_WAITDEV; /* SYS電源状態：開始→SYSデバイス終了待ち */
        }
    }

/* 非冗長電源OFF要求 */
    if(u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INIT){
        u1_s_Mcu_PwrCtrl_NonRednPwrSts = MCU_PWRCTRL_NRD_STS_INPRC;      /* 非冗長電源状態:開始→実行中 */
        Mcu_Noredun_PwrOff_Start();                                      /* 非冗長電源OFF要求 */
    }

/* MET/IVI定期処理(5ms) */
    if( (u1_s_Mcu_PwrCtrl_SysPwrSts     == MCU_PWRCTRL_SYS_STS_INPRC)    /* SYS電源状態:実行中 */
     || (u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INPRC) ){ /* または、非冗長電源状態:実行中 */
        Mcu_Main_Pwrsup_Function();                                      /* MET/IVI定期処理(5ms) */
    }

/* SYS系デバイス終了状態問い合わせ */
    if(u1_s_Mcu_PwrCtrl_SysPwrSts == MCU_PWRCTRL_SYS_STS_WAITDEV){
        u1_t_devoff_seq = Mcu_Sys_Shtdwn_GetSts();                         /* SYS系デバイス終了状態問い合わせ */
        if(u1_t_devoff_seq ==(uint8)TRUE){                                 /* 処理完了 */
            u1_s_Mcu_PwrCtrl_SysPwrSts = MCU_PWRCTRL_SYS_STS_INPRC;        /* SYS電源状態:SYSデバイス終了待ち→実行中 */
/* SYS電源OFF要求 */
            Mcu_Sys_PwrOff_Start();                                        /* SYS電源OFF要求 */
        }
    }

/* 非冗長電源OFFシーケンス状態問い合わせ */
    if(u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_INPRC){
        u1_t_nrdoff_seq = Mcu_Noredun_PwrOff_GetSts();                      /* 非冗長電源OFFシーケンス状態問い合わせ */
        if(u1_t_nrdoff_seq == (uint8)TRUE){                                 /* 処理完了 */
            u1_s_Mcu_PwrCtrl_NonRednPwrSts = MCU_PWRCTRL_NRD_STS_COMP;      /* 非冗長電源状態：実行中→完了 */
        }
    }

/* SYS電源OFFシーケンス状態問い合わせ */
    if(u1_s_Mcu_PwrCtrl_SysPwrSts == MCU_PWRCTRL_SYS_STS_INPRC){
        u1_t_sysoff_seq = Mcu_Sys_PwrOff_GetSts();                           /* SYS電源OFFシーケンス状態問い合わせ */
        if(u1_t_sysoff_seq == (uint8)TRUE){                                  /* 処理完了 */
            u1_s_Mcu_PwrCtrl_SysPwrSts = MCU_PWRCTRL_SYS_STS_COMP;           /* SYS電源状態：実行中→完了 */
        }
    }
    /* ★要検討★：全部が完了したら、要求を落として処理完了状態にする */
    if( (u1_s_Mcu_PwrCtrl_SysPwrSts     == MCU_PWRCTRL_SYS_STS_COMP)
     && (u1_s_Mcu_PwrCtrl_NonRednPwrSts == MCU_PWRCTRL_NRD_STS_COMP)
     && (u1_s_Mcu_PwrCtrl_SipPwrSts     == MCU_PWRCTRL_SIP_STS_COMP) ){
        u1_s_Mcu_PwrCtrl_Sts = MCU_PWRCTRL_NO_REQ;              /* 処理完了 */
#if (MCU_ERR_CHK == 1U)
        u1_s_Mcu_Err_dbg_state = (uint8)MCU_ERR_NON;               /* 異常系エラーなし */
#endif
    }
    return;
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**** End of File ***********************************************************/
