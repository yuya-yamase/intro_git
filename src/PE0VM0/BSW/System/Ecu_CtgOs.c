/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_CtgOs.c
 * [Module]			CtgOs
 * [Function]		Cyclic Trigger for OS
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <stdint.h>
#include <Std_Types.h>

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_MemmapP.h>
#include <Ecu_CtgOs.h>
#include <Ecu_Internal.h>

#include <Ecu_Memmap_SdaDisableE_env.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

typedef struct REG_ST_OSTM
{
    uint32 u4CMP;         /* 0x00 */
    uint32 u4CNT;         /* 0x04 */
    uint8  u1TO;          /* 0x08 */
    uint8  u1dummyTO[3];  /* 0x09-0x0B */
    uint8  u1TOE;         /* 0x0C */
    uint8  u1dummyTOE[3]; /* 0x0D-0x0F */
    uint8  u1TE;          /* 0x10 */
    uint8  u1dummyTE[3];  /* 0x11-0x13 */
    uint8  u1TS;          /* 0x14 */
    uint8  u1dummyTS[3];  /* 0x15-0x17 */
    uint8  u1TT;          /* 0x18 */
    uint8  u1dummyTT[7];  /* 0x19-0x1F */
    uint8  u1CTL;         /* 0x20 */
} REG_ST_OSTM;

#define REG_u2IC0CKSEL8         (*(volatile uint16 *)((uintptr_t)0xFFBF08C0UL)) /* IC0CKSEL8 */
#define REG_u2IC0CKSEL9         (*(volatile uint16 *)((uintptr_t)0xFFBF09C0UL)) /* IC0CKSEL9 */
#define VAL_u2IC0CKSELX_INITIAL ((uint16)0x0000U)

#define ECU_OSTM_ENABLE  (0U)
#define ECU_OSTM_DISABLE (1U)

#if (ECU_TARGETDEVICE == ECU_U2A16)
#define ECU_OSTM6 ECU_OSTM_ENABLE
#define ECU_OSTM7 ECU_OSTM_ENABLE
#else
#define ECU_OSTM6 ECU_OSTM_DISABLE
#define ECU_OSTM7 ECU_OSTM_DISABLE
#endif

#define ECU_CTGOS_u4_OSTM_UNDEFINED (0xFFFFFFFFUL)
#define ECU_CTGOS_u4_OSTM0_BASE     (0xFFBF0000UL)
#define ECU_CTGOS_u4_OSTM1_BASE     (0xFFBF0100UL)
#define ECU_CTGOS_u4_OSTM2_BASE     (0xFFBF0200UL)
#define ECU_CTGOS_u4_OSTM3_BASE     (0xFFBF0300UL)
#define ECU_CTGOS_u4_OSTM4_BASE     (0xFFBF0400UL)
#define ECU_CTGOS_u4_OSTM5_BASE     (0xFFBF0500UL)
#if (ECU_OSTM6 == ECU_OSTM_ENABLE)
#define ECU_CTGOS_u4_OSTM6_BASE (0xFFBF0600UL)
#else
#define ECU_CTGOS_u4_OSTM6_BASE ECU_CTGOS_u4_OSTM_UNDEFINED
#endif
#if (ECU_OSTM7 == ECU_OSTM_ENABLE)
#define ECU_CTGOS_u4_OSTM7_BASE (0xFFBF0700UL)
#else
#define ECU_CTGOS_u4_OSTM7_BASE ECU_CTGOS_u4_OSTM_UNDEFINED
#endif
#define ECU_CTGOS_u4_OSTM8_BASE (0xFFBF0800UL)
#define ECU_CTGOS_u4_OSTM9_BASE (0xFFBF0900UL)

/* 1ms発火周期分のカウント数 クロックソースはCLK_HSB(80MHz) */
/* → 1[ms] ÷ 1000 * タイマ周波数[1000*1000Hz] */
#define VAL_u4OSTMnCMP (79999UL)

#define VAL_u1OSTMnCTL (0x80U)

/* TS・TTレジスタの設定用値 */
#define VAL_u1OSTMnTS (0x01U)
#define VAL_u1OSTMnTT (0x01U)

/* Timer Ch for TE */
#define VAL_u1OSTMnTE_DISABLE (0x00U)
#define VAL_u1OSTMnTE_ENABLE  (0x01U)
#define MSK_u1OSTMnTE         (0x01U)

#define ECU_CTGOS_OSTM_MAX (10U)
static const uint32 u4_OSTM_BASE[ECU_CTGOS_OSTM_MAX] = {ECU_CTGOS_u4_OSTM0_BASE, ECU_CTGOS_u4_OSTM1_BASE, ECU_CTGOS_u4_OSTM2_BASE, ECU_CTGOS_u4_OSTM3_BASE, ECU_CTGOS_u4_OSTM4_BASE,
                                                        ECU_CTGOS_u4_OSTM5_BASE, ECU_CTGOS_u4_OSTM6_BASE, ECU_CTGOS_u4_OSTM7_BASE, ECU_CTGOS_u4_OSTM8_BASE, ECU_CTGOS_u4_OSTM9_BASE};

/* Timeout value for updating the status registers of count enable status register for timer stop */
#define ECU_CTGOS_u4TIMEOUT_COUNT (240U)

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format]		void Ecu_CtgOs_start(uint8 u1TMResNo)
 * [Function]	Start CTG
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void Ecu_CtgOs_start(uint8 u1TMResNo)
{
    volatile uint8        u1Dummy;    /* ダミーリード用 */
    volatile REG_ST_OSTM *REG_ptOSTM; /* レジスタアドレス格納用のためREGから開始 */
    uint32                u4Time;

    if (u1TMResNo < ECU_CTGOS_OSTM_MAX)
    {
        if (u4_OSTM_BASE[u1TMResNo] != ECU_CTGOS_u4_OSTM_UNDEFINED)
        {
            REG_ptOSTM = (volatile REG_ST_OSTM *)((uintptr_t)u4_OSTM_BASE[u1TMResNo]);

            /* タイマ停止 */
            Ecu_CtgOs_stop(u1TMResNo);

            /* カウンタ周期設定 */
            REG_ptOSTM->u4CMP = VAL_u4OSTMnCMP;

            /* インターバルタイマモード、開始時の割り込み禁止 を指定 */
            REG_ptOSTM->u1CTL = VAL_u1OSTMnCTL;

            if (ECU_CTGOS_OSTM8 == u1TMResNo)
            {
                REG_u2IC0CKSEL8 = VAL_u2IC0CKSELX_INITIAL;
            }
            else if (ECU_CTGOS_OSTM9 == u1TMResNo)
            {
                REG_u2IC0CKSEL9 = VAL_u2IC0CKSELX_INITIAL;
            }
            else
            {
                /* Nothing To Do */
            }

            /* タイマ開始 */
            REG_ptOSTM->u1TS = VAL_u1OSTMnTS;

            /* ●ステータスレジスタ更新待ち */
            u4Time = 0UL;
            while ((u4Time < ECU_CTGOS_u4TIMEOUT_COUNT) && (VAL_u1OSTMnTE_ENABLE != (REG_ptOSTM->u1TE & MSK_u1OSTMnTE)))
            {
                u4Time++;
            }

            u1Dummy = REG_ptOSTM->u1TE;
            Ecu_CtgOs_syncp();
        }
        else
        {
            /* Nothing To Do */
        }
    }
    else
    {
        /* Nothing To Do */
    }
    return;
}
/**---------------------------------------------------------------------------
 * [Format]		void Ecu_Ctg_stop(uint8 u1TMResNo)
 * [Function]	Stop CTG
 * [Arguments]	None
 * [Return]		None
 * [Notes]		This Function must call in DI
 *--------------------------------------------------------------------------*/
void Ecu_CtgOs_stop(uint8 u1TMResNo)
{
    volatile uint8        u1Dummy;    /* ダミーリード用 */
    volatile REG_ST_OSTM *REG_ptOSTM; /* レジスタアドレス格納用のためREGから開始 */
    uint32                u4Time;

    if (u1TMResNo < ECU_CTGOS_OSTM_MAX)
    {
        if (u4_OSTM_BASE[u1TMResNo] != ECU_CTGOS_u4_OSTM_UNDEFINED)
        {
            REG_ptOSTM = (volatile REG_ST_OSTM *)((uintptr_t)u4_OSTM_BASE[u1TMResNo]);

            /* タイマ停止 */
            REG_ptOSTM->u1TT = VAL_u1OSTMnTT;

            /* ●ステータスレジスタ更新待ち */
            u4Time = 0UL;
            while ((u4Time < ECU_CTGOS_u4TIMEOUT_COUNT) && (VAL_u1OSTMnTE_DISABLE != (REG_ptOSTM->u1TE & MSK_u1OSTMnTE)))
            {
                u4Time++;
            }

            u1Dummy = REG_ptOSTM->u1TE;
            Ecu_CtgOs_syncp();
        }
        else
        {
            /* Nothing To Do */
        }
    }
    else
    {
        /* Nothing To Do */
    }
    return;
}
