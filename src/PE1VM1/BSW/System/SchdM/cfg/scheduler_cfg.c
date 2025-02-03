/* 2.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Scheduler                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SCHDLR_CFG_C_MAJOR (3)
#define SCHDLR_CFG_C_MINOR (0)
#define SCHDLR_CFG_C_PATCH (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include <Std_Types.h>
#include "scheduler.h"
#include "scheduler_taskdef.h"
#include "scheduler_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Include Files for Reguler/Idle Task Prototypes                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Application Header                                                        */
/*---------------------------------------------------------------------------*/
#include "stub.h"

/*---------------------------------------------------------------------------*/
/* Platform Header                                                           */
/*---------------------------------------------------------------------------*/
#if 0
/* #include "int_drv.h" */ /* include in scheduler_cfg_private.h */
#include "gpt_drv_ost.h"
#include "port_drv.h"

#include "int_handler.h"
#include "int_handler_irq.h"

#include "rim_ctl.h"

#include "date_clk.h"
#include "veh_opemd.h"
#include "fflv_capt.h"
#include "xpd_init.h" a

#include "iohw_adc.h"
#include "iohw_diflt.h"

#include "nvmc_mgr.h"
#include "esm_m_stkm.h"
#include "esm_m_tpm.h"
#endif

#include "rim_ctl.h"
#include "bsw_m.h"
#include "nvmc_mgr.h"
/*---------------------------------------------------------------------------*/
/* Application Header                                                        */
/*---------------------------------------------------------------------------*/
#include "dimmer.h"
#include "illumi.h"
#include "thblnkr.h"
#include "vehspd_kmph.h"
#include "vptran_sel.h"
#include "ptsctmp_cel.h"
#include "alert.h"
#include "sbltwrn.h"
#include "engspd_rpm.h"
#include "engspd_det_rpm.h"
#include "odo_km.h"
#include "tripsnsr.h"
#include "tripcom.h"
#include "tripcom_comtx.h"
#include "ambtmp.h"
#include "datesi.h"
#include "mulmed_color.h"
#include "mulmed_mulfr.h"
#include "rcmmui.h"
#include "telltale.h"
#include "wchime.h"
#include "gauge.h"
#include "sbltsync.h"
#include "locale.h"
#include "vardef.h"
#include "hud_ca.h"
#include "mcst.h"
#include "vds_ci.h"
#include "hmiproxy.h"
#include "battpow.h"
#include "drvind_pwr_pct.h"
#include "drvind_eco.h"
#include "drvind_hv_pct.h"
#include "oilmil.h"
#include "hdimmgr.h"
#include "himgadj.h"
#include "mmlang.h"
#include "vmmunit.h"
#include "fspomgr.h"
#include "ecojdg.h"
#include "attmp_cel.h"
#include "mmvar.h"
#include "mmappctrl.h"
#include "evschg.h"
#include "batcare.h"
/*---------------------------------------------------------------------------*/
/* Platform Header                                                           */
/*---------------------------------------------------------------------------*/
#include "drec_tx.h"
#include "nwcm.h"
#include "dio_if.h"
#include "sound_cri_mgr.h"
#include "gateway_cxpi.h"
#include "gateway_mm.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((SCHDLR_CFG_C_MAJOR != SCHDLR_H_MAJOR) || \
     (SCHDLR_CFG_C_MINOR != SCHDLR_H_MINOR))
#error "scheduler_cfg.c and scheduler.h : source and header files are inconsistent!"
#endif

#if ((SCHDLR_CFG_C_MAJOR != SCHDLR_CFG_H_MAJOR) || \
     (SCHDLR_CFG_C_MINOR != SCHDLR_CFG_H_MINOR))
#error "scheduler_cfg.c and scheduler_cfg_private.h : source and parameter files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SCHDLR_TASK_CYCL_MAX                     (20U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_g_dummy10ms_A(void);
static void vd_g_dummy10ms_B(void);
static void vd_g_dummy20ms_B(void);
static void vd_g_dummy50ms_D(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const uint16 u2_g_SCHDLR_TASK_CYCL_START = (uint16)0U;
const uint16 u2_g_SCHDLR_TASK_CYCL_MAX   = (uint16)20U;
const uint32 u4_gp_SCHDLR_TASK_CYCL_CFG[SCHDLR_TASK_CYCL_MAX] = {
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_A | (uint32)SCHDLR_TASKBIT__20MS_A | (uint32)SCHDLR_TASKBIT__50MS_A | (uint32)SCHDLR_TASKBIT_100MS_A ),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_B),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_A | (uint32)SCHDLR_TASKBIT__20MS_B | (uint32)SCHDLR_TASKBIT__50MS_B | (uint32)SCHDLR_TASKBIT_100MS_B ),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_B),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_A | (uint32)SCHDLR_TASKBIT__20MS_A | (uint32)SCHDLR_TASKBIT__50MS_C | (uint32)SCHDLR_TASKBIT_100MS_C ),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_B),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_A | (uint32)SCHDLR_TASKBIT__20MS_B | (uint32)SCHDLR_TASKBIT__50MS_D | (uint32)SCHDLR_TASKBIT_100MS_D ),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_B),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_A | (uint32)SCHDLR_TASKBIT__20MS_A | (uint32)SCHDLR_TASKBIT__50MS_E | (uint32)SCHDLR_TASKBIT_100MS_E ),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_B),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_A | (uint32)SCHDLR_TASKBIT__20MS_B | (uint32)SCHDLR_TASKBIT__50MS_A | (uint32)SCHDLR_TASKBIT_100MS_F ),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_B),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_A | (uint32)SCHDLR_TASKBIT__20MS_A | (uint32)SCHDLR_TASKBIT__50MS_B | (uint32)SCHDLR_TASKBIT_100MS_G ),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_B),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_A | (uint32)SCHDLR_TASKBIT__20MS_B | (uint32)SCHDLR_TASKBIT__50MS_C | (uint32)SCHDLR_TASKBIT_100MS_H ),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_B),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_A | (uint32)SCHDLR_TASKBIT__20MS_A | (uint32)SCHDLR_TASKBIT__50MS_D | (uint32)SCHDLR_TASKBIT_100MS_I ),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_B),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_A | (uint32)SCHDLR_TASKBIT__20MS_B | (uint32)SCHDLR_TASKBIT__50MS_E | (uint32)SCHDLR_TASKBIT_100MS_J ),
    ((uint32)SCHDLR_TASKBIT___5MS | (uint32)SCHDLR_TASKBIT__10MS_B)
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Regular Task Configuration                                                                                                       */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  WARNING : vdp_PTR_NA shall NOT be set to ST_SCHDLR_RGLR.fp_vd_TASK.                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_SCHDLR_RGLR st_gp_SCHDLR_RGLR_TASK[] = {
#if 0
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  10ms A Platform Pre Task                                         */
/*                                                                   */
/*-------------------------------------------------------------------*/
#ifdef DATE_CLK_H
    {&vd_g_DateclkMainTask, (U4)SCHDLR_TASKBIT__10MS_A}, /* vd_g_DateclkMainTask expects to be invoked before the tasks  */
#endif /* which vd_g_DateclkSet is executed.                           */

#if ((defined(__AIP_DEBUG_SIM__)) && (__AIP_DEBUG_SIM__ == 1))
#else
    {&vd_g_WdgM_MainTask, (U4)SCHDLR_TASKBIT__10MS_A},
#endif /* #if ((defined(__AIP_DEBUG_SIM__)) && (__AIP_DEBUG_SIM__==1)) */

    {&vd_s_SchdlrCfgIoRefresh, (U4)SCHDLR_TASKBIT__10MS_A},
    {&vd_g_XpdiMainTask, (U4)SCHDLR_TASKBIT__10MS_A},
    {&vd_g_EsmMStkmMainTask, (U4)SCHDLR_TASKBIT__10MS_A},

    {&vd_g_IoHwAdcMainTask, (U4)SCHDLR_TASKBIT__10MS_A},
    {&vd_g_FFLvCaptMainTask, (U4)SCHDLR_TASKBIT__10MS_A},
    {&vd_g_IoHwDifltMainTask, (U4)SCHDLR_TASKBIT__10MS_A},
    {&vd_g_VehopemdMainTask, (U4)SCHDLR_TASKBIT__10MS_A}, /* In case of toyota product, vd_g_VehopemdMainTask shall be    */
                                                          /* called after vd_g_IoHwDifltSmplgTask                         */

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*   5ms Task                                                        */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_Nvmc_Task, (U4)SCHDLR_TASKBIT___5MS},

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  10ms A Non-Platform Task                                         */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_Stub10msTask, (U4)SCHDLR_TASKBIT__10MS_A},

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  20ms B Task                                                      */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_Nvmc_PeriodicTask, (U4)SCHDLR_TASKBIT__20MS_B},

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  50ms C Task                                                      */
    /*                                                                   */
    /*-------------------------------------------------------------------*/

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /* 100ms A Task                                                      */
    /*                                                                   */
    /*-------------------------------------------------------------------*/

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /* 100ms B Task                                                      */
    /*                                                                   */
    /*-------------------------------------------------------------------*/

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  10ms A Platform Post Task                                        */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_Rim_Task, (U4)SCHDLR_TASKBIT__10MS_A},

    /*-------------------------------------------------------------------*/
    /*  WARNING "DO NOT EXECUTE APPLICATION AT HERE"                     */
    /*-------------------------------------------------------------------*/

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  20ms B Post Task                                                 */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_BswMMainTask, (U4)SCHDLR_TASKBIT__20MS_B} /* vd_g_BswMMainTask shall be called at end   */
                                                     /* of regular task                            */
#endif
    {&vd_g_dummy10ms_A, (uint32)SCHDLR_TASKBIT__10MS_A_CAL},
    {&vd_g_dummy10ms_B, (uint32)SCHDLR_TASKBIT__10MS_B_CAL},
    {&vd_g_dummy20ms_B, (uint32)SCHDLR_TASKBIT__20MS_B_CAL},
    {&vd_g_dummy50ms_D, (uint32)SCHDLR_TASKBIT__50MS_D_CAL},

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*   5ms Task                                                        */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_Nvmc_Task, (U4)SCHDLR_TASKBIT___5MS_CAL},

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  10ms A Non-Platform Task                                         */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_Stub10msTask, (U4)SCHDLR_TASKBIT__10MS_A_CAL},

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  20ms B Task                                                      */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_Nvmc_PeriodicTask, (U4)SCHDLR_TASKBIT__20MS_B_CAL},

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  10ms A Platform Post Task                                        */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_Rim_Task,     (uint32)SCHDLR_TASKBIT__10MS_A_CAL},

    {&vd_g_BswMMainTask, (uint32)SCHDLR_TASKBIT___5MS_CAL},
	/*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  Platform Pre Task                                                */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_SoundCriMgrMainTask,         (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_DioIfMainIn,                 (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*                                                                   */
    /*  Evc : Variation and Configuration                                */
    /*                                                                   */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_VardefMainTask,              (U4)SCHDLR_TASKBIT__20MS_B_CAL  },
    {&vd_g_HudCaMainTask,               (U4)SCHDLR_TASKBIT__20MS_B_CAL  },
    {&vd_g_McstMainTask,                (U4)SCHDLR_TASKBIT__20MS_B_CAL  },
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*                                                                   */
    /*  Vom : Vehicle Operation Model                                    */
    /*                                                                   */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_MmLangCstmzTask,             (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_VardefMmUnitCstmzTask,       (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_LocaleMainTask,              (U4)SCHDLR_TASKBIT__20MS_B_CAL  },
    {&vd_g_VdsCIMainTask,               (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_DimMainTask,                 (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_VehspdMainTask,              (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_EngspdMainTask,              (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_EngspdDetMainTask,           (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_PtsctmpMainTask,             (U4)SCHDLR_TASKBIT_100MS_A_CAL  },
    {&vd_g_VptranMainTask,              (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_OdoMainTask,                 (U4)SCHDLR_TASKBIT__50MS_C_CAL  },
    {&vd_g_EvschgMainTask,              (U4)SCHDLR_TASKBIT__50MS_E_CAL  },
    {&vd_g_Evschg10msTask,              (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_AlertMainTask,               (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_SbltwrnMainTask,             (U4)SCHDLR_TASKBIT__50MS_C_CAL  },
    {&vd_g_TripsnsrSmplngTask,          (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_TripcomMainTask,             (U4)SCHDLR_TASKBIT__50MS_E_CAL  },
    {&vd_g_TripcomComTxTask,            (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_TripcomSmoothingTask,        (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_AmbtmpMainTask,              (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_DateSIMainTask,              (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_MulmedColorMainTask,         (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_MulmedMulfrMainTask,         (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_RcmmUIMainTask,              (U4)SCHDLR_TASKBIT__20MS_B_CAL  },
    {&vd_g_BattpowMainTask,             (U4)SCHDLR_TASKBIT_100MS_E_CAL  },
    {&vd_g_DrvIndPwrMainTask,           (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_DrvIndEcoMainTask,           (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_DrvIndHvMainTask,            (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_OilmilMainTask,              (U4)SCHDLR_TASKBIT__50MS_E_CAL  },
    {&vd_g_HdimmgrRoutine,              (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_HudImgAdjMainTask,           (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_Fsposnsr10msTask,            (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_FspomgrRoutine,              (U4)SCHDLR_TASKBIT__50MS_E_CAL  },
    {&vd_g_EcoJdgMainTask,              (U4)SCHDLR_TASKBIT__50MS_E_CAL  },
    {&vd_g_AttmpMainTask,               (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_MMVarTask,                   (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_MMAppCtrlTask,               (U4)SCHDLR_TASKBIT__50MS_E_CAL  },
    {&vd_g_BatcareMainTask,             (U4)SCHDLR_TASKBIT__50MS_B_CAL  },
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*                                                                   */
    /*  Hmi : Human Machine Interface                                    */
    /*                                                                   */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_HmiProxyMainTask,            (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*                                                                   */
    /*  Vsv : Vehicle Status Viewer                                      */
    /*                                                                   */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_IllumiMainTask,              (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_GaugeMainTask,               (U4)SCHDLR_TASKBIT__20MS_A_CAL  },
    {&vd_g_SbltsyncMainTask,            (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_TelltaleMainTask,            (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_ThblnkrMainTask,             (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_wChimeMainTask,              (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  Platform Post Task                                               */
    /*                                                                   */
    /*  WARNING "DO NOT EXECUTE APPLICATION AT HERE"                     */
    /*-------------------------------------------------------------------*/
    {&vd_g_DioIfMainOut,                (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_NWCMMainTask,                (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_DrectxMainTask,              (U4)SCHDLR_TASKBIT__50MS_A_CAL  },
    {&vd_g_GatewayCxpiMainTask,         (U4)SCHDLR_TASKBIT__10MS_A_CAL  },
    {&vd_g_GatewaymmMainTask,           (U4)SCHDLR_TASKBIT__10MS_A_CAL  }

};
const uint16 u2_g_SCHDLR_RGLR_NUM_TASK = (uint16)(sizeof(st_gp_SCHDLR_RGLR_TASK) / sizeof(ST_SCHDLR_RGLR));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_SchdlrCfgMainTick(const uint32 u4_a_TRGBIT)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if 0
void vd_g_SchdlrCfgMainTick(const uint32 u4_a_TRGBIT)
{

    U4 u4_t_jdgbit;

    vd_g_IntHndlrIRQCtrlCh((U2)INT_HNDLR_IRQ_CH_SCHD_MT, (U1)INT_HNDLR_IRQ_CTRL_TRG_SWI);

    u4_t_jdgbit = u4_a_TRGBIT & (U4)SCHDLR_TASKBIT__10MS_B;
    if (u4_t_jdgbit != (U4)0U)
    {
        vd_g_IoHwAdcSeqAct((U1)FALSE);
        vd_g_IoHwAdcCvstStart();
    }
    else
    {
        vd_g_IoHwAdcCvstFinish();
    }

    u4_t_jdgbit = u4_a_TRGBIT & (U4)SCHDLR_TASKBIT_100MS_D;
    if (u4_t_jdgbit != (U4)0U)
    {
        vd_g_FFLvCaptStart();
    }

    u4_t_jdgbit = u4_a_TRGBIT & (U4)SCHDLR_TASKBIT_100MS_E;
    if (u4_t_jdgbit != (U4)0U)
    {
        vd_g_FFLvCaptFinish();
    }
}
#endif
static void vd_g_dummy10ms_A(void)
{
}
static void vd_g_dummy10ms_B(void) {}
static void vd_g_dummy20ms_B(void) {}
static void vd_g_dummy50ms_D(void) {}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     9/ 5/2014  TN       New.                                                                                               */
/*  1.1.0     3/16/2015  TN       "volatile" was added into "u4_s_schdlr_taskbit_trgrd" and u4_s_schdlr_taskbit_exect.               */
/*  1.2.0     3/31/2015  TN       vd_g_SchdlrMainTickIsr -> vd_g_SchdlrMainTick.                                                     */
/*                                vd_g_SchdlrCfgMainTick(u4_t_trgrd) was implemented.                                                */
/*  1.3.0     6/24/2015  TN       scheduler.c v1.2.0 -> v1.3.0.                                                                      */
/*  2.0.0    10/ 9/2015  TN       scheduler v1.3.0 -> v2.0.0 : soft/hard-preemtive architectures were supported.                     */
/*  2.1.0    10/14/2015  TN       scheduler v2.0.0 -> v2.1.0.                                                                        */
/*  2.2.0     1/14/2016  TN       scheduler v2.1.0 -> v2.2.0.                                                                        */
/*  2.3.0     1/20/2016  TN       scheduler v2.2.0 -> v2.3.0.                                                                        */
/*  2.4.0     2/ 1/2016  TN       scheduler v2.3.0 -> v2.4.0.                                                                        */
/*  2.5.0     9/21/2016  TN       scheduler v2.4.0 -> v2.5.0.                                                                        */
/*  2.6.0     4/10/2017  TN       scheduler v2.5.0 -> v2.6.0.                                                                        */
/*            8/29/2017  AM       QAC warining was fixed.                                                                            */
/*  2.6.1     9/ 7/2021  TN       scheduler v2.6.0 -> v2.6.1.                                                                        */
/*  2.7.0     9/15/2021  TN       scheduler v2.6.1 -> v2.7.0.                                                                        */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * AM      = Akira Motomatsu, Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
