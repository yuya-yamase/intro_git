/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/****************************************************************************/
/*  Renesas RH850/U2A : MCU Driver                                          */
/*                                                                          */
/****************************************************************************/
/*----------------------------------------------------------------------------
 *		ヘッダインクルード
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>

#include "int_drv.h"
#include "gpt_drv_frt.h"
#include "mcu_drv.h"

#include <Ecu_Memmap_SdaDisableB_env.h>

/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/
#define REG_u4SWSRESA                (*(volatile U4 *)((U4)0xFF98840CUL)) /* SWSRESA */
#define VAL_u4SWSRESA_SYSTEM_RESET2  (0x00000001UL)                               /* R_SWRESET */
#define REG_u4RESKCPROT0             (*(volatile U4 *)((U4)0xFF980F00UL)) /* RESKCPROT0 */
#define VAL_u4RESKCPROT0_KCE_ENABLE  (0xA5A5A501UL)
#define VAL_u4RESKCPROT0_KCE_DISABLE (0xA5A5A500UL)

/* RESFC - Reset Factor Clear Register */
#define APL_REG_RESFC               (*(volatile U4 *)0xFF980C00UL)
#define APL_RESFC_ALL_CLEAR         (0x0000F5DDUL)

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/

#include <Ecu_Memmap_SdaDisableE_env.h>

volatile const U4 * u4p_g_MCU_RRAMTOP_VM0 = (volatile const U4 *)0xFE808000UL;
volatile static U4 u4_s_time_clearburam;

/*----------------------------------------------------------------------------
 *      プロトタイプ宣言
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		プログラム
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		void vd_g_Mcu_PerformReset(const U1 u1_a_TYPE)
 * [Function]	PerformReset
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void vd_g_Mcu_PerformReset(const U1 u1_a_TYPE)
{
    (void)u1_a_TYPE;                            /* unused parameter, will be fixed in later version */

    U4  u4_t_sta_clearburam;
    APL_REG_RESFC = APL_RESFC_ALL_CLEAR;        /* Reset Factor Clear */

    /* Disable interrupt */
    (void)u4_g_IRQ_DI();

    u4_t_sta_clearburam = u4_g_Gpt_FrtGetUsElapsed((void *)0) & (U4)0x7fffffffU;
    /* Clear Retention RAM area from 0xFE808000(VM0 start) to 0xFE828000(VM3 end) */
    (void)SS_Memory_set((U4 *)u4p_g_MCU_RRAMTOP_VM0, 0UL, (U4)0x20000U);
    u4_s_time_clearburam = (U4)((u4_g_Gpt_FrtGetUsElapsed((void *)0) - u4_t_sta_clearburam) & (U4)0x7fffffffU);

    while(1)
    {
        REG_u4RESKCPROT0 = VAL_u4RESKCPROT0_KCE_ENABLE;
        REG_u4SWSRESA    = VAL_u4SWSRESA_SYSTEM_RESET2;
        REG_u4RESKCPROT0 = VAL_u4RESKCPROT0_KCE_DISABLE;
    }
}
