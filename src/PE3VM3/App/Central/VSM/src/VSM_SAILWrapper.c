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
#include "chipcom.h"

/****************************************************************/
/* VARIABLE                                                     */
/****************************************************************/
static U1   u1_s_vsm_sailsleepsts;      /* SAILスリープ可否情報 */

/****************************************************************/
/* 関数宣言                                                     */
/****************************************************************/

/********************************************************************/
/*    Function    :vd_g_VSM_SAILWrapper_Init                        */
/********************************************************************/
void vd_g_VSM_SAILWrapper_Init(void)
{
    u1_s_vsm_sailsleepsts = (U1)VSM_SLEEPOK;
    
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

    u1_t_ret = ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VSM_SLEEPNG, &u2_t_len, &u1_t_data, &u4_t_counter);

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

    return;
}