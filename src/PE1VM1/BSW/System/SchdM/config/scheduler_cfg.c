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
#define SCHDLR_CFG_C_MAJOR                       (2)
#define SCHDLR_CFG_C_MINOR                       (7)
#define SCHDLR_CFG_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
#include "xspi.h"

/*---------------------------------------------------------------------------*/
/* Platform Header                                                           */
/*---------------------------------------------------------------------------*/
#include "SS.h"
#include "Os.h"             /* for ActivateTask */

#include "iohw_adc.h"
#include "iohw_diflt.h"

#include "veh_opemd.h"

#include "rim_ctl.h"
#include "run_m.h"
#include "nvmc_mgr.h"
#include "oxcan.h"
#include "ivdsh.h"

#include "gpt_drv_ost.h"
#include "wdg_drv.h"

/*---------------------------------------------------------------------------*/
/* Application Header                                                        */
/*---------------------------------------------------------------------------*/
#include "dimmer.h"
#include "illumi.h"
#include "thblnkr.h"
#include "vehspd_kmph.h"
#include "vptran_sel.h"
#if 0   /* BEV Rebase provisionally */
#include "ptsctmp_cel.h"
#endif   /* BEV Rebase provisionally */
#include "alert.h"
#include "sbltwrn.h"
#if 0   /* BEV Rebase provisionally */
#include "engspd_rpm.h"
#include "engspd_det_rpm.h"
#endif   /* BEV Rebase provisionally */
#include "odo_km.h"
#include "tripsnsr.h"
#include "tripcom.h"
#include "tripcom_comtx.h"
#include "ambtmp.h"
#if 0   /* BEV Rebase provisionally */
#include "mulmed_color.h"
#include "mulmed_mulfr.h"
#endif   /* BEV Rebase provisionally */
#include "rcmmui.h"
#if 0   /* BEV Rebase provisionally */
#include "telltale.h"
#endif   /* BEV Rebase provisionally */
#include "wchime.h"
#include "gauge.h"
#if 0   /* BEV Rebase provisionally */
#include "sbltsync.h"
#endif   /* BEV Rebase provisionally */
#include "locale.h"
#include "vardef.h"
#if 0   /* BEV Rebase provisionally */
#include "hud_ca.h"
#endif   /* BEV Rebase provisionally */
#include "hmiproxy.h"
#if 0   /* BEV Rebase provisionally */
#include "drvind_pwr_pct.h"
#include "drvind_eco.h"
#include "drvind_hv_pct.h"
#include "oilmil.h"
#endif   /* BEV Rebase provisionally */
#include "hdimmgr.h"
#include "himgadj.h"
#if 0   /* BEV Rebase provisionally */
#include "mmlang.h"
#include "vmmunit.h"
#include "fspomgr.h"
#include "attmp_cel.h"
#include "mmvar.h"
#include "mmappctrl.h"
#include "evschg.h"
#include "datesi_met.h"
/*---------------------------------------------------------------------------*/
/* Platform Header                                                           */
/*---------------------------------------------------------------------------*/
#include "drec_tx.h"
#include "nwcm.h"
#include "dio_if.h"
#endif   /* BEV Rebase provisionally */
#include "sound_cri_mgr.h"
#if 0   /* BEV Rebase provisionally */
#include "gateway_cxpi.h"
#include "gateway_mm.h"
#endif   /* BEV Rebase provisionally */
#include "xspi_met.h"

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
#define SCHDLR_TASK_CYCL_MAX                     (100U)

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
static void    vd_s_SchdlrCfgIdleChkptRchd(void);
static void    vd_s_SchdlrCfgWdgTimRestart(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4               u4_gp_SCHDLR_TASK_CYCL_CFG[SCHDLR_TASK_CYCL_MAX] = {
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A | SCHDLR_TASKBIT__20MS_A | SCHDLR_TASKBIT__50MS_A | SCHDLR_TASKBIT_100MS_A),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A | SCHDLR_TASKBIT__20MS_B | SCHDLR_TASKBIT__50MS_B | SCHDLR_TASKBIT_100MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A | SCHDLR_TASKBIT__20MS_A | SCHDLR_TASKBIT__50MS_C | SCHDLR_TASKBIT_100MS_C),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A | SCHDLR_TASKBIT__20MS_B | SCHDLR_TASKBIT__50MS_D | SCHDLR_TASKBIT_100MS_D),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A | SCHDLR_TASKBIT__20MS_A | SCHDLR_TASKBIT__50MS_E | SCHDLR_TASKBIT_100MS_E),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A | SCHDLR_TASKBIT__20MS_B | SCHDLR_TASKBIT__50MS_A | SCHDLR_TASKBIT_100MS_F),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A | SCHDLR_TASKBIT__20MS_A | SCHDLR_TASKBIT__50MS_B | SCHDLR_TASKBIT_100MS_G),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A | SCHDLR_TASKBIT__20MS_B | SCHDLR_TASKBIT__50MS_C | SCHDLR_TASKBIT_100MS_H),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A | SCHDLR_TASKBIT__20MS_A | SCHDLR_TASKBIT__50MS_D | SCHDLR_TASKBIT_100MS_I),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A | SCHDLR_TASKBIT__20MS_B | SCHDLR_TASKBIT__50MS_E | SCHDLR_TASKBIT_100MS_J),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)(SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_B),
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U,
    (U4)0x00000000U
};
const U2               u2_g_SCHDLR_TASK_CYCL_START = (U2)0U;
const U2               u2_g_SCHDLR_TASK_CYCL_MAX   = (U2)SCHDLR_TASK_CYCL_MAX;

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

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  10ms A Platform Pre Task                                         */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_s_SchdlrCfgWdgTimRestart,      (U4)SCHDLR_TASKBIT__10MS_A  },
//    {&vd_g_EsmMStkmMainTask,            (U4)SCHDLR_TASKBIT__10MS_A  },

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*   5ms Platform Pre Task                                           */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_iVDshMainReaTask,            (U4)SCHDLR_TASKBIT___5MS    },
    {&vd_g_XSpiMETPduRx,                (U4)SCHDLR_TASKBIT___5MS    },
    {&vd_g_oXCANMainPreTask,            (U4)SCHDLR_TASKBIT___5MS    },
    {&vd_g_VehopemdMainTask,            (U4)SCHDLR_TASKBIT___5MS    }, /* In case of toyota product, vd_g_VehopemdMainTask shall be    */
                                                                       /* called after vd_g_IoHwDifltSmplgTask                         */ 

    {&vd_g_Nvmc_Task,                   (U4)SCHDLR_TASKBIT___5MS    },

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  10ms A Non-Platform Task                                         */
    /*                                                                   */
    /*-------------------------------------------------------------------*/

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  20ms B Task                                                      */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_Nvmc_PeriodicTask,           (U4)SCHDLR_TASKBIT__20MS_B  },

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*   5ms Platform Post Task                                          */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_oXCANMainPosTask,           (U4)SCHDLR_TASKBIT___5MS    },
    {&vd_g_iVDshMainWriTask,           (U4)SCHDLR_TASKBIT___5MS    },

    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  10ms A Platform Post Task                                        */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_Rim_Task,                    (U4)SCHDLR_TASKBIT__10MS_A  },
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  Platform Pre Task                                                */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_SoundCriMgrMainTask,         (U4)SCHDLR_TASKBIT__10MS_A  },
#if 0   /* BEV Rebase provisionally */
    {&vd_g_DioIfMainIn,                 (U4)SCHDLR_TASKBIT__10MS_A  },
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*                                                                   */
    /*  Evc : Variation and Configuration                                */
    /*                                                                   */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
#endif   /* BEV Rebase provisionally */
    {&vd_g_VardefMainTask,              (U4)SCHDLR_TASKBIT__20MS_B  },
#if 0   /* BEV Rebase provisionally */
    {&vd_g_HudCaMainTask,               (U4)SCHDLR_TASKBIT__20MS_B  },
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*                                                                   */
    /*  Vom : Vehicle Operation Model                                    */
    /*                                                                   */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_MmLangCstmzTask,             (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_VardefMmUnitCstmzTask,       (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_LocaleMainTask,              (U4)SCHDLR_TASKBIT__20MS_B  },
#endif   /* BEV Rebase provisionally */
    {&vd_g_DimMainTask,                 (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_VehspdMainTask,              (U4)SCHDLR_TASKBIT__20MS_A  },
#if 0   /* BEV Rebase provisionally */
    {&vd_g_EngspdMainTask,              (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_EngspdDetMainTask,           (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_PtsctmpMainTask,             (U4)SCHDLR_TASKBIT_100MS_A  },
#endif   /* BEV Rebase provisionally */
    {&vd_g_VptranMainTask,              (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_OdoMainTask,                 (U4)SCHDLR_TASKBIT__50MS_C  },
#if 0   /* BEV Rebase provisionally */
    {&vd_g_EvschgMainTask,              (U4)SCHDLR_TASKBIT__50MS_E  },
    {&vd_g_Evschg10msTask,              (U4)SCHDLR_TASKBIT__10MS_A  },
#endif   /* BEV Rebase provisionally */
    {&vd_g_AlertMainTask,               (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_SbltwrnMainTask,             (U4)SCHDLR_TASKBIT__50MS_C  },
    {&vd_g_TripsnsrSmplngTask,          (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_TripcomMainTask,             (U4)SCHDLR_TASKBIT__50MS_E  },
    {&vd_g_TripcomComTxTask,            (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_TripcomSmoothingTask,        (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_AmbtmpMainTask,              (U4)SCHDLR_TASKBIT__20MS_A  },
#if 0   /* BEV Rebase provisionally */
    {&vd_g_MulmedColorMainTask,         (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_MulmedMulfrMainTask,         (U4)SCHDLR_TASKBIT__10MS_A  },
#endif   /* BEV Rebase provisionally */
    {&vd_g_RcmmUIMainTask,              (U4)SCHDLR_TASKBIT__20MS_B  },
#if 0   /* BEV Rebase provisionally */
    {&vd_g_DrvIndPwrMainTask,           (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_DrvIndEcoMainTask,           (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_DrvIndHvMainTask,            (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_OilmilMainTask,              (U4)SCHDLR_TASKBIT__50MS_E  },
    #endif   /* BEV Rebase provisionally */
    {&vd_g_HdimmgrRoutine,              (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_HudImgAdjMainTask,           (U4)SCHDLR_TASKBIT__10MS_A  },
#if 0   /* BEV Rebase provisionally */
    {&vd_g_Fsposnsr10msTask,            (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_FspomgrRoutine,              (U4)SCHDLR_TASKBIT__50MS_E  },
    {&vd_g_AttmpMainTask,               (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_MMVarTask,                   (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_MMAppCtrlTask,               (U4)SCHDLR_TASKBIT__50MS_E  },
    {&vd_g_DateSIMETMainTask,           (U4)SCHDLR_TASKBIT___5MS    },
    #endif   /* BEV Rebase provisionally */
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*                                                                   */
    /*  Hmi : Human Machine Interface                                    */
    /*                                                                   */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_HmiProxyMainTask,            (U4)SCHDLR_TASKBIT__10MS_A  },
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*                                                                   */
    /*  Vsv : Vehicle Status Viewer                                      */
    /*                                                                   */
    /*                                                                   */
    /*-------------------------------------------------------------------*/
    {&vd_g_IllumiMainTask,              (U4)SCHDLR_TASKBIT__20MS_A  },
    {&vd_g_GaugeMainTask,               (U4)SCHDLR_TASKBIT__20MS_A  },
#if 0   /* BEV Rebase provisionally */
    {&vd_g_SbltsyncMainTask,            (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_TelltaleMainTask,            (U4)SCHDLR_TASKBIT__10MS_A  },
#endif   /* BEV Rebase provisionally */
    {&vd_g_ThblnkrMainTask,             (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_wChimeMainTask,              (U4)SCHDLR_TASKBIT__10MS_A  },
#if 0   /* BEV Rebase provisionally */
    /*-------------------------------------------------------------------*/
    /*                                                                   */
    /*  Platform Post Task                                               */
    /*                                                                   */
    /*  WARNING "DO NOT EXECUTE APPLICATION AT HERE"                     */
    /*-------------------------------------------------------------------*/
    {&vd_g_DioIfMainOut,                (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_NWCMMainTask,                (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_DrectxMainTask,              (U4)SCHDLR_TASKBIT__50MS_A  },
    {&vd_g_GatewayCxpiMainTask,         (U4)SCHDLR_TASKBIT__10MS_A  },
    {&vd_g_GatewaymmMainTask,           (U4)SCHDLR_TASKBIT__10MS_A  },
#endif   /* BEV Rebase provisionally */
    {&vd_g_XSpiMETPduTx,                (U4)SCHDLR_TASKBIT___5MS    },

    /*-------------------------------------------------------------------*/
    /*  WARNING "DO NOT EXECUTE APPLICATION AT HERE"                     */
    /*-------------------------------------------------------------------*/
    {&vd_g_RunMMainTask,                (U4)SCHDLR_TASKBIT___5MS    },             /* vd_g_RunMMainTask shall be called at next  */
                                                                                   /* of SS_Mm_mainFunction                      */
    {&SS_Mm_mainFunction,               (U4)SCHDLR_TASKBIT___5MS    }              /* SS_Mm_mainFunction shall be called at end  */
};
const U2               u2_g_SCHDLR_RGLR_NUM_TASK = (U2)(sizeof(st_gp_SCHDLR_RGLR_TASK) / sizeof(ST_SCHDLR_RGLR));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Idle Task Configuration                                                                                                          */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  WARNING : vdp_PTR_NA shall NOT be set to fp_gp_vd_SCHDLR_IDLE_TASK[].                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const FP_SCHDLR_IDLE   fp_gp_vd_SCHDLR_IDLE_TASK[] = {
    &vd_s_SchdlrCfgIdleChkptRchd
};
const U2               u2_g_SCHDLR_IDLE_NUM_TASK   = (U2)(sizeof(fp_gp_vd_SCHDLR_IDLE_TASK) / sizeof(FP_SCHDLR_IDLE));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4               u4_g_SCHDLR_IRQ_PREP_SHTDWN = (U4)0U;    /* This parameter not referenced because __SCHDLR_CFGHK_IDLE_FINISH__=0 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_SchdlrCfgMainTick(const U4 u4_a_TRGBIT)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SchdlrCfgMainTick(const U4 u4_a_TRGBIT)
{
    U4               u4_t_jdgbit;

    (void)ActivateTask(eMCOS_TASK_High);

    u4_t_jdgbit = u4_a_TRGBIT & (U4)SCHDLR_TASKBIT__10MS_B;
    if(u4_t_jdgbit != (U4)0U){
        (void)ActivateTask(eMCOS_TASK_Medium);
    }
    else if(u4_a_TRGBIT != (U4)0U){                 /* SCHDLR_TASKBIT___5MS | SCHDLR_TASKBIT__10MS_A ... etc */

        (void)ActivateTask(eMCOS_TASK_Medium);
    }
    else{
        /* do nothing */
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_SchdlrCfgIdleToRun(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SchdlrCfgIdleToRun(void)
{
    static const U4  u4_sp_SCHDLR_OST_START[GPT_OST_START_NUM_CFG] = {
        ((U4)GPT_OST_START_CTRL_BIT_IRQ_EN |
         (U4)GPT_OST_START_CTRL_BIT_TRG_ST),
        (U4)1000U * (U4)GPT_OST_1US                /*  GPT_OST_START_CMPR_THRSH : 1.0 [ms] */
    };

    /*------------------------------------------------------------------------------*/
    /* Warning:                                                                     */
    /*                                                                              */
    /* Because OSTMnCTL.OSTMnMD0="1" (1: Enables interrupts when counting starts),  */
    /* the MainTick interrupt is generated just after the vd_g_Gpt_OstStart call,   */
    /* and launching the initial task.                                              */
    /*------------------------------------------------------------------------------*/
    vd_g_Gpt_OstStart((U1)GPT_OST_CH_06_SCHDLR_TICK, &u4_sp_SCHDLR_OST_START[0]);

    SuspendAllInterrupts();
    xspi_Init( XSPI_CH_02 );
    ResumeAllInterrupts();
}
/*===================================================================================================================================*/
/*  static void    vd_s_SchdlrCfgIdleChkptRchd(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_SchdlrCfgIdleChkptRchd(void)
{
    // vd_g_WdgM_CheckpointReached((U2)WDG_M_SEID_IDLE_TASK, (U2)0U);
}
/*===================================================================================================================================*/
/*  static void    vd_s_SchdlrCfgWdgTimRestart(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_SchdlrCfgWdgTimRestart(void)
{
    vd_g_Wdg_SetTriggerCondition((U2)0U);
}
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
