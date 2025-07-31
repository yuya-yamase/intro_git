/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 *【ファイル名】    rprg_if_request.c
 *【モジュール名】  Reprog Interface
 *【機能】
 *【備考】
 ****************************************************************************/
/*----------------------------------------------------------------------------
 *		ヘッダインクルード
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>

#include <Ecu_Memmap_SdaDisableB_env.h>

#include <Ecu_Int.h>

/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/
#define REG_u4SWSRESA                (*(volatile uint32 *)((uint32)0xFF98840CUL)) /* SWSRESA */
#define REG_u4RESKCPROT0             (*(volatile uint32 *)((uint32)0xFF980F00UL)) /* RESKCPROT0 */
#define VAL_u4RESKCPROT0_KCE_ENABLE  (0xA5A5A501UL)
#define VAL_u4RESKCPROT0_KCE_DISABLE (0xA5A5A500UL)

/* BSEQ0CTL - BIST Skip Control Register for FBIST0 */
#define APL_REG_BSEQ0CTL            (*(volatile uint32 *)0xFF988400UL)
#define APL_BSEQ0CTL_BIST_SKIP_SET  (0x00000002UL)

/* RESFC - Reset Factor Clear Register */
#define APL_REG_RESFC               (*(volatile uint32 *)0xFF980C00UL)
#define APL_RESFC_ALL_CLEAR         (0x0000F5DDUL)

#define RPRG_APL_RPGFLAGADDR        (0xFE800000UL)  /* ECU Software Launch Request Address */
#define RPRG_APL_RPGDATAADDR        (0xFE800004UL)  /* Launch Request Parameter Address */
#define RPRG_APL_SIDDATAADDR        (0xFE800024UL)  /* SID Information Address */

#define RIM_KEYWORD_SIZE            (12U)

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/

#include <Ecu_Memmap_SdaDisableE_env.h>

extern uint32 __ghsbegin_rodata_SHARE_ROM_RIM_KEYWORD_top;

/*----------------------------------------------------------------------------
 *      プロトタイプ宣言
 *--------------------------------------------------------------------------*/
#define RH850_G4MH_SYNCP_WORD  /* static inline void  vd_s_SYNCP_W(const volatile U4 * const u4_ap_RDBK) */
#include "rh850_g4mh.h"

/*----------------------------------------------------------------------------
 *		プログラム
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		void vd_g_RprgIfRequestReprog(void)
 * [Function]	Reprog Request
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void vd_g_RprgIfRequestReprog(void)     /* @@@ */
{
    uint32 *papl_rpgparamByte;
    uint32 *papl_sidparamByte;
    uint32 *papl_rpgflag;
    uint32 u4_t_lpcnt;
    volatile uint32* u4_tp_word;
    
    papl_rpgparamByte = (uint32 *)RPRG_APL_RPGDATAADDR;
    papl_sidparamByte = (uint32 *)RPRG_APL_SIDDATAADDR;
    papl_rpgflag = (uint32 *)RPRG_APL_RPGFLAGADDR;
    
    papl_rpgparamByte[0] = (uint32)0x17DA1805UL;
    papl_rpgparamByte[1] = (uint32)0x020000E0UL;
    papl_rpgparamByte[2] = (uint32)0x240080FEUL;
    papl_rpgparamByte[3] = (uint32)0x00000000UL;
    papl_rpgparamByte[4] = (uint32)0x45230100UL;
    papl_rpgparamByte[5] = (uint32)0xCDAB8967UL;
    papl_rpgparamByte[6] = (uint32)0x543210EFUL;
    papl_rpgparamByte[7] = (uint32)0xDCBA9876UL;
   
    papl_sidparamByte[0] = (uint32)0xFFFF0210UL;

#if 0
    papl_rpgparamByte[0] = (uint8)0x05U;        /* Receive channel */       /* ^^^ */
    papl_rpgparamByte[1] = (uint8)0x18U;        /* Incoming CAN ID #0 */
    papl_rpgparamByte[2] = (uint8)0xDAU;        /* Incoming CAN ID #1 */
    papl_rpgparamByte[3] = (uint8)0x17U;        /* Incoming CAN ID #2 */    /* ^^^ */
    papl_rpgparamByte[4] = (uint8)0xE0U;        /* Incoming CAN ID #3 */    /* ^^^ */
    papl_rpgparamByte[5] = (uint8)0x00U;        /* SubMicon Type */
    papl_rpgparamByte[6] = (uint8)0x00U;        /* Message size #0 */
    papl_rpgparamByte[7] = (uint8)0x02U;        /* Message size #1 */
    papl_rpgparamByte[8] = (uint8)((RPRG_APL_SIDDATAADDR >> 24U) & 0x000000FFUL);   /* Message address #0 */
    papl_rpgparamByte[9] = (uint8)((RPRG_APL_SIDDATAADDR >> 16U) & 0x000000FFUL);   /* Message address #1 */
    papl_rpgparamByte[10] = (uint8)((RPRG_APL_SIDDATAADDR >> 8U) & 0x000000FFUL);   /* Message address #2 */
    papl_rpgparamByte[11] = (uint8)(RPRG_APL_SIDDATAADDR & 0x000000FFUL);           /* Message address #3 */
    papl_rpgparamByte[12] = (uint8)0x00U;       /* Reserve */
    papl_rpgparamByte[13] = (uint8)0x00U;       /* Reserve */
    papl_rpgparamByte[14] = (uint8)0x00U;       /* Reserve */
    papl_rpgparamByte[15] = (uint8)0x00U;       /* Reserve */
    papl_rpgparamByte[16] = (uint8)0x00U;       /* Reserve */
    papl_rpgparamByte[17] = (uint8)0x01U;       /* User Optional */
    papl_rpgparamByte[18] = (uint8)0x23U;       /* User Optional */
    papl_rpgparamByte[19] = (uint8)0x45U;       /* User Optional */
    papl_rpgparamByte[20] = (uint8)0x67U;       /* User Optional */
    papl_rpgparamByte[21] = (uint8)0x89U;       /* User Optional */
    papl_rpgparamByte[22] = (uint8)0xABU;       /* User Optional */
    papl_rpgparamByte[23] = (uint8)0xCDU;       /* User Optional */
    papl_rpgparamByte[24] = (uint8)0xEFU;       /* User Optional */
    papl_rpgparamByte[25] = (uint8)0x10U;       /* User Optional */
    papl_rpgparamByte[26] = (uint8)0x32U;       /* User Optional */
    papl_rpgparamByte[27] = (uint8)0x54U;       /* User Optional */
    papl_rpgparamByte[28] = (uint8)0x76U;       /* User Optional */
    papl_rpgparamByte[29] = (uint8)0x98U;       /* User Optional */
    papl_rpgparamByte[30] = (uint8)0xBAU;       /* User Optional */
    papl_rpgparamByte[31] = (uint8)0xDCU;       /* User Optional */

    /* set SID Information - BSC ADD */
    papl_sidparamByte[0] = (uint8)0x10U;        /* SID */
    papl_sidparamByte[1] = (uint8)0x02U;        /* Subfunction */
    papl_sidparamByte[2] = (uint8)0xFFU;
    papl_sidparamByte[3] = (uint8)0xFFU;
#endif

    *papl_rpgflag = 0x5AA5A55AUL;

    APL_REG_RESFC = APL_RESFC_ALL_CLEAR;        /* Reset Factor Clear */

    /* LBIST Only */
    REG_u4RESKCPROT0 = VAL_u4RESKCPROT0_KCE_ENABLE;
    APL_REG_BSEQ0CTL = APL_BSEQ0CTL_BIST_SKIP_SET;
    REG_u4RESKCPROT0 = VAL_u4RESKCPROT0_KCE_DISABLE;

    u4_tp_word = (volatile uint32*)&__ghsbegin_rodata_SHARE_ROM_RIM_KEYWORD_top;
    for (u4_t_lpcnt = (uint32)0U; u4_t_lpcnt < (uint32)RIM_KEYWORD_SIZE; u4_t_lpcnt++) {
        *((volatile uint32 *)(u4_tp_word[u4_t_lpcnt])) = (uint32)0x00000000U;
    }

    vd_s_SYNCP_W(&u4_tp_word[(uint8)RIM_KEYWORD_SIZE - (uint8)1U]);

    Ecu_Int_performReset();

    return;
}
