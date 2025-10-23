/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Operational Mode Event Hooks                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_EVTHK_C_MAJOR                  (2)
#define VEH_OPEMD_EVTHK_C_MINOR                  (1)
#define VEH_OPEMD_EVTHK_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "veh_opemd_cfg_private.h"

#include "iohw_diflt.h"
#include "oxcan.h"

#include "vehspd_kmph.h"
#if 0   /* BEV Rebase provisionally */
#include "alert.h"
#endif   /* BEV Rebase provisionally */
#include "gauge.h"
#if 0   /* BEV Rebase provisionally */

#endif   /* BEV Rebase provisionally */
#include "vardef.h"
#if 0   /* BEV Rebase provisionally */
#include "fspomgr.h"
#endif   /* BEV Rebase provisionally */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VEH_OPEMD_EVTHK_C_MAJOR != VEH_OPEMD_CFG_H_MAJOR) || \
     (VEH_OPEMD_EVTHK_C_MINOR != VEH_OPEMD_CFG_H_MINOR) || \
     (VEH_OPEMD_EVTHK_C_PATCH != VEH_OPEMD_CFG_H_PATCH))
#error "veh_opemd_evthk.c and veh_opemd_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV Rebase provisionally */
#define VEH_OPEMD_NUM_EVHK                      (5U)
#else   /* BEV Rebase provisionally */
#define VEH_OPEMD_NUM_EVHK                      (3U)
#endif   /* BEV Rebase provisionally */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    void  (* const    fp_vd_HK)(const U4 u4_a_MDBIT, const U4 u4_a_EVBIT);
    U4                u4_evbit;
}ST_VEH_OPEMD_EVHK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VehopemdCfgEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVBIT)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehopemdCfgEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVBIT)
{
#if (VEH_OPEMD_NUM_EVHK > 0U)
    static const ST_VEH_OPEMD_EVHK   st_sp_VEH_OPEMD_EVHK[VEH_OPEMD_NUM_EVHK] = {
        {&vd_g_VehspdOpemdEvhk,         (U4)VEH_OPEMD_EVBIT_IG_R_TO_ON    },

#if 0   /* BEV Rebase provisionally */
        {&vd_g_PtsctmpOpemdEvhk,        ((U4)VEH_OPEMD_EVBIT_IG_R_TO_ON  |
                                         (U4)VEH_OPEMD_EVBIT_IG_R_TO_OFF) },

        {&vd_g_AlertOpemdEvhk,          ((U4)VEH_OPEMD_EVBIT_IG_R_TO_ON  |
                                         (U4)VEH_OPEMD_EVBIT_IG_R_TO_OFF) },

#endif   /* BEV Rebase provisionally */
        {&vd_g_GaugeOpemdEvhk,          ((U4)VEH_OPEMD_EVBIT_IG_R_TO_ON  |
                                         (U4)VEH_OPEMD_EVBIT_IG_R_TO_OFF) },
#if 0   /* BEV Rebase provisionally */

        {&vd_g_FspoOpemdEvhk,          ((U4)VEH_OPEMD_EVBIT_IG_R_TO_ON  |
                                         (U4)VEH_OPEMD_EVBIT_IG_R_TO_OFF) },
#endif   /* BEV Rebase provisionally */
        {&vd_g_VardefEsOptIgoffEvhk,    (U4)VEH_OPEMD_EVBIT_IG_R_TO_OFF   }
    };

    U4                                u4_t_cnt;
    U4                                u4_t_bit;

    vd_g_IoHwDifltSgnlInit(); /* DO NOT REMOVED */
    vd_g_oXCANVomEvhk();

    vd_g_VardefOpemdEvhk();

#ifdef DATE_CLK_H
    u4_t_jdgbit = u4_a_EVTBIT & (U4)VEH_OPEMD_EVBIT_IG_R_TO_OFF;
    if(u4_t_jdgbit != (U4)0U){
        vd_g_DateclkEtmStart((U1)DATE_CLK_ETM_CH_TMRWK, (U4)0U); /* zero start */
    }
#endif
    for(u4_t_cnt = (U4)0U; u4_t_cnt < (U4)VEH_OPEMD_NUM_EVHK; u4_t_cnt++){
        u4_t_bit = u4_a_EVBIT & st_sp_VEH_OPEMD_EVHK[u4_t_cnt].u4_evbit;
        if(u4_t_bit != (U4)0U){
            (st_sp_VEH_OPEMD_EVHK[u4_t_cnt].fp_vd_HK)(u4_a_MDBIT, u4_a_EVBIT);
        }
    }
#else
    vd_g_IoHwDifltSgnlInit(); /* DO NOT REMOVED */
    vd_g_oXCANVomEvhk();
#endif /* #if (VEH_OPEMD_NUM_EVHK > 0) */
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/ 3/2015  TN       New.                                                                                               */
/*  1.1.0     3/23/2015  TN       Timer Function was implemented                                                                     */
/*  1.2.0    11/ 2/2017  TN       veh_opemd v1.1.0 -> v1.2.0.                                                                        */
/*  1.2.1     6/23/2020  HU       veh_opemd v1.2.0 -> v1.2.1.                                                                        */
/*  1.3.0    12/ 7/2020  ST       veh_opemd v1.2.1 -> v1.3.0.                                                                        */
/*  2.0.0     2/ 3/2025  ST       Supported vehicle power state.                                                                     */
/*  2.1.0     2/ 7/2025  TN       veh_opemd v2.0.0 -> v2.1.0.                                                                        */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    10/22/2025  TS       Change for BEV rebase.                                                                             */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * HU   = Hayato Usui, Denso Create                                                                                               */
/*  * ST   = Satoshi Tanaka, Denso Create                                                                                            */
/*  * TS   = Takuo Suganuma, Denso Techno                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
