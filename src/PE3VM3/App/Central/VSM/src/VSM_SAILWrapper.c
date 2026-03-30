/****************************************************************************/
/*                                                                          */
/*    FILE NAME     :    VSM_SAILWrapper.c                                  */
/*    FUNCTION      :    CPU SleepWakeup                                    */
/*                       Data Select Layer                                  */
/*                                                                          */
/*    DEPARTMENT    :    DNJP                                               */
/*    AUTHOR        :                                                       */
/*                                                                          */
/****************************************************************************/
#include "VSM.h"
/* 26.2.16 doza Team-B edit sta */
/*#include "chipcom.h"*/
#include "ChipCom.h"
#include "ChipCom_Cfg.h"
/* 26.2.16 doza Team-B edit end */

/* Debug Code */
#define ARRAY_SIZE  (200U)
#define INVLID_DATA (0xFFU)
/* Debug Code */

/****************************************************************/
/* VARIABLE                                                     */
/****************************************************************/
static U1   u1_s_vsm_sailsleepsts;      /* SAILスリープ可否情報 */
/* Debug Code */
static volatile U1   u1_s_vsm_sailsleepsts_array[ARRAY_SIZE];
static U1   u1_s_vsm_cnt;
/* Debug Code */

/****************************************************************/
/* 関数宣言                                                     */
/****************************************************************/

/********************************************************************/
/*    Function    :vd_g_VSM_SAILWrapper_Init                        */
/********************************************************************/
void vd_g_VSM_SAILWrapper_Init(void)
{
    u1_s_vsm_sailsleepsts = (U1)VSM_SLEEPOK;
    /* Debug Code */
    for(U1 i = 0; i < ARRAY_SIZE; i++){
        u1_s_vsm_sailsleepsts_array[i] = INVLID_DATA;
    }
    u1_s_vsm_cnt = 0U;
    /* Debug Code */

    return;
}

/********************************************************************/
/*    Function    :vd_g_VSM_SAILWrapper                             */
/********************************************************************/
void vd_g_VSM_SAILWrapper(void)
{
    U1 u1_t_ret;
    U2 u2_t_len = (U2)0U;
    U1 u1_t_data = (U1)VSM_SLEEPOK;
    U4 u4_t_counter = 0U;

    u1_t_ret = ChipCom_GetPeriodicRxData((U1)CHIPCOM_PERIODICID_VSM_SLEEPNG, &u2_t_len, &u1_t_data, &u4_t_counter);

    if(u1_t_ret == (U1)E_OK){
        if(u1_t_data == (U1)VSM_SLEEPNG){
            u1_s_vsm_sailsleepsts = (U1)VSM_SLEEPNG;
        }
        else if(u1_t_data == (U1)VSM_SLEEPOK){
            u1_s_vsm_sailsleepsts = (U1)VSM_SLEEPOK;
        }
        else{
            /* do nothing */
        }
    }
    
    PutCnSleepNG_SAIL(u1_s_vsm_sailsleepsts);

    /* Debug Code */
    if (u1_s_vsm_cnt < ARRAY_SIZE) {
        u1_s_vsm_sailsleepsts_array[u1_s_vsm_cnt] = u1_s_vsm_sailsleepsts;
        u1_s_vsm_cnt++;
    }

    if (u1_s_vsm_cnt == ARRAY_SIZE) {
        u1_s_vsm_cnt = 0U;
    }
    /* Debug Code */

    return;
}
