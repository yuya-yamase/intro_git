/****************************************************************************/
/*                                                                          */
/*    FILE NAME     :    VSM.c                                              */
/*    FUNCTION      :    CPU SleepWakeup                                    */
/*                       Data Select Layer                                  */
/*                                                                          */
/*    DEPARTMENT    :    DNJP                                               */
/*    AUTHOR        :                                                       */
/*                                                                          */
/****************************************************************************/
#include "VSM.h"
/* ★未実装のため蓋閉じ */
/* #include "PwrCtrl_Observe.h" */

/****************************************************************/
/* VARIABLE                                                     */
/****************************************************************/
static U1 CN_SAIL_SLEEPNG_FT;

#define APL_00_SLEEP_NG         (State_SleepNg0.bitdata.b1_0.bit0)    /* CPUスリープNG判断(SAIL) */
#define APL_01_SLEEP_NG         (State_SleepNg0.bitdata.b1_0.bit1)
#define APL_02_SLEEP_NG         (State_SleepNg0.bitdata.b1_0.bit2)
#define APL_03_SLEEP_NG         (State_SleepNg0.bitdata.b1_0.bit3)
#define APL_04_SLEEP_NG         (State_SleepNg0.bitdata.b1_0.bit4)
#define APL_05_SLEEP_NG         (State_SleepNg0.bitdata.b1_0.bit5)
#define APL_06_SLEEP_NG         (State_SleepNg0.bitdata.b1_0.bit6)
#define APL_07_SLEEP_NG         (State_SleepNg0.bitdata.b1_0.bit7)
#define APL_08_SLEEP_NG         (State_SleepNg0.bitdata.b1_1.bit0)
#define APL_09_SLEEP_NG         (State_SleepNg0.bitdata.b1_1.bit1)
#define APL_10_SLEEP_NG         (State_SleepNg0.bitdata.b1_1.bit2)
#define APL_11_SLEEP_NG         (State_SleepNg0.bitdata.b1_1.bit3)
#define APL_12_SLEEP_NG         (State_SleepNg0.bitdata.b1_1.bit4)
#define APL_13_SLEEP_NG         (State_SleepNg0.bitdata.b1_1.bit5)
#define APL_14_SLEEP_NG         (State_SleepNg0.bitdata.b1_1.bit6)
#define APL_15_SLEEP_NG         (State_SleepNg0.bitdata.b1_1.bit7)
#define APL_16_SLEEP_NG         (State_SleepNg0.bitdata.b1_2.bit0)
#define APL_17_SLEEP_NG         (State_SleepNg0.bitdata.b1_2.bit1)
#define APL_18_SLEEP_NG         (State_SleepNg0.bitdata.b1_2.bit2)
#define APL_19_SLEEP_NG         (State_SleepNg0.bitdata.b1_2.bit3)
#define APL_20_SLEEP_NG         (State_SleepNg0.bitdata.b1_2.bit4)
#define APL_21_SLEEP_NG         (State_SleepNg0.bitdata.b1_2.bit5)
#define APL_22_SLEEP_NG         (State_SleepNg0.bitdata.b1_2.bit6)
#define APL_23_SLEEP_NG         (State_SleepNg0.bitdata.b1_2.bit7)
#define APL_24_SLEEP_NG         (State_SleepNg0.bitdata.b1_3.bit0)
#define APL_25_SLEEP_NG         (State_SleepNg0.bitdata.b1_3.bit1)
#define APL_26_SLEEP_NG         (State_SleepNg0.bitdata.b1_3.bit2)
#define APL_27_SLEEP_NG         (State_SleepNg0.bitdata.b1_3.bit3)
#define APL_28_SLEEP_NG         (State_SleepNg0.bitdata.b1_3.bit4)
#define APL_29_SLEEP_NG         (State_SleepNg0.bitdata.b1_3.bit5)
#define APL_30_SLEEP_NG         (State_SleepNg0.bitdata.b1_3.bit6)
#define APL_31_SLEEP_NG         (State_SleepNg0.bitdata.b1_3.bit7)

/****************************************************************/
/* 関数宣言                                                     */
/****************************************************************/
#define State_enableSleep(id)       do { (id) = TYPE_CLR; } while(0)
#define State_disableSleep(id)      do { (id) = TYPE_SET; } while(0)

#define GetCnSAILSleepNGFt()        (CN_SAIL_SLEEPNG_FT)

/********************************************************************/
/*    Function    :vd_g_VSM_Init                                    */
/********************************************************************/
void vd_g_VSM_Init(void)
{
    CN_SAIL_SLEEPNG_FT = (U1)VSM_SLEEPOK;
}

/********************************************************************/
/*    Function    :App_VSM_Main                                     */
/********************************************************************/
void App_VSM_Main(void)
{
    static TYPE_U4DATA State_SleepNg0;

    /* CPUスリープNG判断(SAIL) */
    if ( (U4)GetCnSAILSleepNGFt() != (U4)VSM_SLEEPOK ) {
        State_disableSleep( APL_00_SLEEP_NG );
    }
    else{
        State_enableSleep( APL_00_SLEEP_NG );
    }

    /* CPUスリープNG通知 */
    if ( State_SleepNg0.u4data == (U4)0x00000000UL ) {
        /* ★未実装のため蓋閉じ */
        /* vd_g_PwrCtrlObserveProhibitSleep(PWRCTRL_OBSERVE_PROHIBITSLEEP_OFF); */
    }
    else {
        /* ★未実装のため蓋閉じ */
        /* vd_g_PwrCtrlObserveProhibitSleep(PWRCTRL_OBSERVE_PROHIBITSLEEP_ON); */
    }

    return;
}

/********************************************************************/
/*    Function    :PutCnSleepNG_SAIL                                */
/********************************************************************/
void PutCnSleepNG_SAIL( const U1 SleepNG )
{
    CN_SAIL_SLEEPNG_FT = SleepNG;

    return;
}
