/* 1.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* Sound Middleware (CRI) Control                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SOUND_CRI_MGR_C_MAJOR                        (1)
#define SOUND_CRI_MGR_C_MINOR                        (7)
#define SOUND_CRI_MGR_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "sound_cri_mgr.h"

#include "wchime.h"
#if 0   /* BEV Rebase provisionally */ /* for xm-authentication */
#include "vardef.h"
#endif   /* BEV Rebase provisionally */ /* for xm-authentication */

/* CRI header file */
#include "cri_xpt.h"
#include "cri_atom_at_def.h"
#include "cri_sfr_config_rh850u2a.h"
#include "ADXAT_Data_TYT.h"
#include "ADXAT_Data_LEX.h"

/* CRI driver header file */
#include "sound_cri_drv.h"

/* calibration header file */
#include "calibration.h"
#include "vardef.h"

#include "reg_dma.h"

#include "Port.h"
#include "Dio.h"
#include "trpl_rdndnt.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((SOUND_CRI_MGR_C_MAJOR != SOUND_CRI_MGR_H_MAJOR) || \
     (SOUND_CRI_MGR_C_MINOR != SOUND_CRI_MGR_H_MINOR) || \
     (SOUND_CRI_MGR_C_PATCH != SOUND_CRI_MGR_H_PATCH))
#error "sound_cri_mgr.c and sound_cri_mgr.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SOUND_CRI_TIMER_FREQUENCY              (80U * 1000U * 1000U)       /* TAUJ 80Mhz                                             */
#define SOUND_CRI_CLKFIX_CLK                   (80U * 1000U * 1000U)       /* CLKFIX 80Mhz                                           */
#define SOUND_CRI_INIT_WORK_SIZE               (16028U)                    /* Size of work-space for library initialization          */
#define SOUND_CRI_MAX_VIRTUAL_VOICES           (15)                        /* Number of Max virtual voices                           */
#define SOUND_CRI_MAX_TRACKS                   (8U)                        /* Number of Max playing tracks                           */
#define SOUND_CRI_MAX_TRACK_ITEMS              (10U)                       /* Number of Max playing track items                      */
#define SOUND_CRI_MAX_SEQUENCES                (0)                         /* Number of Max playing sequences                        */

#define SOUND_ACFDATA_SIZE                     (84U)                       /* Size of work-space for on-memory ACF data registration */
#define SOUND_AWBDATA_SIZE                     (32U)                       /* Size of work-space for on-memory AWB handle creation   */
#define SOUND_ACBDATA_SIZE                     (640U)                      /* Size of work-space for on-memory ACB data loading      */
#define SOUND_OVERLAP_ADX_NUM                  (5)                         /* Number of play voices at the same time in ADX          */
#define SOUND_VOICEPOOLADXDATA_SIZE            (15404U)                    /* Size of work-space for ADX voice-pool creation         */
#define SOUND_PLAYER_SIZE                      (108U)                      /* Size of work-space for AtomEx player creation          */

#define SOUND_GROUP1                           (0U)                        /* Sound CH Group No.1 */
#define SOUND_GROUP2                           (1U)                        /* Sound CH Group No.2 */
#define SOUND_GROUP3                           (2U)                        /* Sound CH Group No.3 */
#define SOUND_GROUP4                           (3U)                        /* Sound CH Group No.4 */
#define SOUND_GROUP5                           (4U)                        /* Sound CH Group No.5 */
#define SOUND_GROUP_NUM                        (5U)                        /* maximum number of sound groups                         */
                                                                           /* Caution!:Include sound NON.                            */
                                                                           /*      Therefore the values must be more than 1.(>=1)    */

#define SOUND_CYCLETIME_MAX                    (0xFFFEU)                   /* Maximum of sound cycle time                            */

#define SOUND_CUEID_INVALID                    (U2_MAX)                    /* Invalid timbre cue ID                                  */

#define SOUND_VOLUMEID_DEFAULT_TYT             (WCHIME_VOL_BASE_NOTICE1_MID) /* Default volume ID : BASE_NOTICE1_MID                 */
#define SOUND_VOLUMEID_DEFAULT_LEX             (WCHIME_VOL_BASE_NOTICE1_MID) /* Default volume ID : BASE_NOTICE1_MID                 */
#define SOUND_NUM_VOL_TYT                      (WCHIME_NUM_VOL)
#define SOUND_NUM_VOL_LEX                      (WCHIME_NUM_VOL)

#define SOUND_CUEVOLUME_MUTE                   (0.0F)                      /* Cue volume : Mute                                      */

#define SOUND_CSR_BRG_REQ_NUM                  (6U)                        /* Number of clearance sonar buzzer IDs bridging to CH5   */
#define SOUND_CSR_FRRR_REQ_NUM                 (3U)                        /* Number of clearance sonar Fr+Rr buzzer ID              */
#define SOUND_CSR_FRRR_VOL_NUM                 (SOUND_CSR_FRRR_REQ_NUM * 8U) /* Number of clearance sonar Fr+Rr volume               */

#define SOUND_OW_TYPE_CONT                     (0U)                        /* Active test type : Continuance type                    */
#define SOUND_OW_TYPE_EVENT                    (1U)                        /* Active test type : Event type                          */

#define SOUND_OW_TIMEOUT                       (5000U / 10U)               /* Active test timeout (5000ms/Task cycle)                */

#define SOUND_OW_CTRL_STA                      (0U)                        /* Active test status : Test start                        */
#define SOUND_OW_CTRL_RUN                      (1U)                        /* Active test status : Test running                      */
#define SOUND_OW_CTRL_CNT                      (2U)                        /* Active test status : Test continuation                 */
#define SOUND_OW_CTRL_INA                      (3U)                        /* Active test status : Test inactive                     */

#define SOUND_CALIBVOLUME_CHANGE_LSB           (1000)                      /* Type Unsigned char to Float                            */
#define SOUND_VOL_MULTI_CH_PLAY_RATE_1         (1000U)                     /* Single channel playing(Fixed at 100%)                  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SOUND_DRV_MODESET                      (0U)
#define SOUND_DRV_ERRCHECK_WAIT                (1U)
#define SOUND_DRV_ERRCHECK                     (2U)

#define SOUND_DRV_MODESET_END_TIM              (3U)
#define SOUND_DRV_ERRCHECK_WAIT_TIM            (55U)

#define SOUND_DRV_INITIAL_MATCH_NUM            (4U)
#define SOUND_DRV_INITIAL                      (0x00U)
#define SOUND_DRV_INITIAL_END                  (0xFFU)

#define SOUND_IC_ERROR_COUNT                   (6U)

#define SOUND_ACTIVE_TIME_RDN_NUM              (3U)
#define SOUND_ACTIVE_TIME_RDN_1ST              (0U)
#define SOUND_ACTIVE_TIME_RDN_2ND              (1U)
#define SOUND_ACTIVE_TIME_RDN_3RD              (2U)
#define SOUND_ACTIVE_TIME_DEF                  (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* For measuring the memory size used by CRI library     TRUE : At measurement / FALSE : Other cases */
#define SOUND_CRI_DEBUGMODE                    (FALSE)

/* Number of arrays */
#define u4_s_SoundCriMgrArrayNum(array)        ((U4)(sizeof(array) / sizeof((array)[0U])))

/* Array size */
#define s4_s_SoundCriMgrArraySize(array)       ((S4)(u4_s_SoundCriMgrArrayNum(array) * sizeof((array)[0U])))

/* For QAC countermeasure */
#ifndef vd_s_SoundCriMgrUnusedParam
#define vd_s_SoundCriMgrUnusedParam(prm)       { if (&(prm) == &(prm)) {} }
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Bridge buzzer ID data to Sound CH Group No.5 */
typedef struct{
    U1                  u1_reqid;                                          /* Requested buzzer ID                                    */
    U1                  u1_setid_grp3;                                     /* Bridged buzzer ID for Sound CH Group No.3              */
    U1                  u1_setid_grp5;                                     /* Bridged buzzer ID for Sound CH Group No.5              */
}ST_SOUND_CSR_BRG_REQ;

/* Bridge volume ID data to Sound CH Group No.5 for clearance sonar Fr+Rr buzzer */
typedef struct{
    U1                  u1_reqvol;                                         /* Requested volume ID                                    */
    U1                  u1_setvol;                                         /* Bridged volume ID                                      */
}ST_SOUND_CSR_FRRR_VOL;

/* Active test control data */
typedef struct{
    U2                  u2_ow_tocnt;                                       /* Buzzer sounding elapsed time                           */
    U1                  u1_ow_sts;                                         /* Active test control status                             */
}ST_SOUND_OW_CTRL;

/* Buzzer information for the active test */
typedef struct{
    U2                  u2_cueid[SOUND_GROUP_NUM];                         /* Cue ID of the requested buzzer                         */
    U1                  u1_cuevol[SOUND_GROUP_NUM];                        /* Volume ID of the requested buzzer                      */
    U1                  u1_type;                                           /* Active test type of the requested buzzer               */
}ST_SOUND_OW_BUZ_INFO;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                   u1_s_sound_drv_active_time_val1;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static CriSint32            s4_s_initialize_size;                                                                       /* Size of work-space for library initialization              */
static CriSint32            s4_s_acfdata_size;                                                                          /* Size of work-space for on-memory ACF data registration     */
static CriSint32            s4_s_awbdata_size;                                                                          /* Size of work-space for on-memory AWB handle creation       */
static CriSint32            s4_s_acbdata_size;                                                                          /* Size of work-space for on-memory ACB data loading          */
static CriSint32            s4_s_voicepooladxdata_size;                                                                 /* Size of work-space for ADX voice-pool creation             */
static CriSint32            s4_s_player_size;                                                                           /* Size of work-space for AtomEx player creation              */

static CriChar8             s1_sp_sound_cri_init_work[SOUND_CRI_INIT_WORK_SIZE]            __attribute__((aligned(4))); /* Work-space for library initialization                      */

static U1                   u1_sp_sound_acfdata_alloc[SOUND_ACFDATA_SIZE]                  __attribute__((aligned(4))); /* Work-space for on-memory ACF data registration             */
static U1                   u1_sp_sound_awbdata_alloc[SOUND_AWBDATA_SIZE]                  __attribute__((aligned(4))); /* Work-space for on-memory AWB handle creation               */
static U1                   u1_sp_sound_acbdata_alloc[SOUND_ACBDATA_SIZE]                  __attribute__((aligned(4))); /* Work-space for on-memory ACB data loading                  */
static U1                   u1_sp_sound_voicepooladx_alloc[SOUND_VOICEPOOLADXDATA_SIZE]    __attribute__((aligned(4))); /* Work-space for ADX voice-pool creation                     */
static U1                   u1_sp2_sound_player_alloc[SOUND_GROUP_NUM][SOUND_PLAYER_SIZE]  __attribute__((aligned(4))); /* Work-space for AtomEx player creation                      */

static CriAtomAwbHn         stp_s_sound_awb_hn;                                                                         /* On-memory AWB handle                                       */
static CriAtomExAcbHn       stp_s_sound_acb_hn;                                                                         /* On-memory ACB handle                                       */
static CriAtomExVoicePoolHn stp_s_sound_voicepooladx_hn;                                                                /* ADX voice-pool handle                                      */
static CriAtomExPlayerHn    stp_sp_sound_player_hn_gp[SOUND_GROUP_NUM];                                                 /* AtomEx player handle                                       */

static U1                   u1_sp_sound_pre_reqidx[SOUND_GROUP_NUM];                                                    /* Index of requested sound in previous task-cycle            */
static U1                   u1_sp_sound_pre_reqvol[SOUND_GROUP_NUM];                                                    /* Index of requested volume in previous task-cycle           */

static U2                   u2_sp_sound_cur_cycletim[SOUND_GROUP_NUM];                                                  /* Sound cycle of current sounding buzzer                     */
static U2                   u2_sp_sound_cycle_cnt[SOUND_GROUP_NUM];                                                     /* Counter of sound cycle                                     */

static U1                   u1_s_sound_csrbz_reqbrg;                                                                    /* Request bridge ch3 to ch5 for Clearance sonar Fr+Rr buzzer */
static U1                   u1_s_sound_csrbz_volbrg;                                                                    /* Volume bridge ch3 to ch5 for Clearance sonar Fr+Rr buzzer  */

static U4                   u4_s_sound_ow_unlock;                                                                       /* Active test unlock key                                     */
static U1                   u1_s_sound_ow_reqid;                                                                        /* Active test request ID                                     */
static ST_SOUND_OW_CTRL     st_sp_sound_ow_ctrl[SOUND_GROUP_NUM];                                                       /* Active test control data                                   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                   u1_s_sound_drv_active_time_val2;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                   u1_s_sound_ic_fltb_befor;
static U1                   u1_s_sound_ic_fltb_count;
static U1                   u1_s_sound_ic_fltb_initial;
static U1                   u1_s_sound_ic_error;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                   u1_s_sound_drv_active_time_val3;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U1      u1_s_SoundCriMgrWavNext(void);
static        U1      u1_s_SoundCriMgrUpdtNext(const U1 u1_a_GRP_NO, const U1 u1_a_REQIDX, U1 * u1p_a_reqvol);
static        U1      u1_s_SoundCriMgrGetCsrRrVolume(const U1 u1_a_REQVOL);

static        void    vd_s_SoundCriMgrUpdtLib(const U1 u1_a_PLAYNUM);

static        U1      u1_s_SoundCriMgrOwChk(const U1 u1_a_GRP_NO, const U1 u1_a_CYCLCHK, U2 * u2p_a_cueid, U1 * u1p_a_cuevol);
static        U1      u1_s_SoundCriMgrOwStsChk(const U1 u1_a_CYCLCHK, const U1 u1_a_OWTYPE, ST_SOUND_OW_CTRL * stp_a_ow_ctrl);

static        void    vd_s_SoundCriMgrSetVolume(const U1 u1_a_GRP_NO, const U1 u1_a_REQ_VOL, const U1 u1_a_PLAYNUM);
static        void    vd_s_SoundCriMgrStartByCueId(const U1 u1_a_GRP_NO, const U2 u2_a_CUE_ID);
static        void    vd_s_SoundCriMgrStop(const U1 u1_a_GRP_NO);


static        void    vd_s_SoundCriMgrTYTSetUp(void);
static        void    vd_s_SoundCriMgrLEXSetUp(void);
#if (SOUND_CRI_DEBUGMODE == TRUE)
static        void    vd_s_SoundCriMgrErrorCallback(const CriChar8 * s1p_a_ERRID, const CriUint32 u4_a_P1, const CriUint32 u4_a_P2, CriUint32 * u4p_a_parray);
#endif /* SOUND_CRI_DEBUGMODE */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        void    vd_s_SoundCriMgrStartup(void);
static        U1      u1_s_SoundDiagnosis(void);
static        U1      u1_s_SoundGetActiveTime(void);
static        U1      u1_s_SoundCriMgr_InitialCheck(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CRI_CUESHEET_0_TYT_CUENUM_ADX          (CRI_CUESHEET_0_TYT_CUENUM - 1U)
/* ACF data table */
static const CriUint32 u4_sp_SOUND_ACF_DATA_TYT[] = {
    #include "ADXAT_Data_acf_TYT.h"
};
static const CriSint32 s4_s_SOUND_ACF_DATA_SIZE_TYT = s4_s_SoundCriMgrArraySize(u4_sp_SOUND_ACF_DATA_TYT);

/* AWB data table */
static const CriUint32 u4_sp_SOUND_AWB_DATA_TYT[] = {
    #include "ADXAT_Data_awb_TYT.h"
};
static const CriSint32 s4_s_SOUND_AWB_DATA_SIZE_TYT = s4_s_SoundCriMgrArraySize(u4_sp_SOUND_AWB_DATA_TYT);

/* ACB data table */
static const CriUint32 u4_sp_SOUND_ACB_DATA_TYT[] = {
    #include "ADXAT_Data_c_acb_TYT.h"
};
static const CriSint32 s4_s_SOUND_ACB_DATA_SIZE_TYT = s4_s_SoundCriMgrArraySize(u4_sp_SOUND_ACB_DATA_TYT);

#define CRI_CUESHEET_0_LEX_CUENUM_ADX          (CRI_CUESHEET_0_LEX_CUENUM - 1U)
/* ACF data table */
static const CriUint32 u4_sp_SOUND_ACF_DATA_LEX[] = {
    #include "ADXAT_Data_acf_LEX.h"
};
static const CriSint32 s4_s_SOUND_ACF_DATA_SIZE_LEX = s4_s_SoundCriMgrArraySize(u4_sp_SOUND_ACF_DATA_LEX);

/* AWB data table */
static const CriUint32 u4_sp_SOUND_AWB_DATA_LEX[] = {
    #include "ADXAT_Data_awb_LEX.h"
};
static const CriSint32 s4_s_SOUND_AWB_DATA_SIZE_LEX = s4_s_SoundCriMgrArraySize(u4_sp_SOUND_AWB_DATA_LEX);

/* ACB data table */
static const CriUint32 u4_sp_SOUND_ACB_DATA_LEX[] = {
    #include "ADXAT_Data_c_acb_LEX.h"
};
static const CriSint32 s4_s_SOUND_ACB_DATA_SIZE_LEX = s4_s_SoundCriMgrArraySize(u4_sp_SOUND_ACB_DATA_LEX);

/* Table of sound cycle every timbre */
static const U2 u2_sp_SOUND_WAV_CYCLETIME_TYT[CRI_CUESHEET_0_TYT_CUENUM_ADX] = {
    (U2)90U,               /* CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01           */
    (U2)20U,               /* CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE2_0_01           */
    (U2)20U,               /* CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01            */
    (U2)26U,               /* CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01           */
    (U2)70U,               /* CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01          */
    (U2)40U,               /* CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01          */
    (U2)14U,               /* CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNH_0_01          */
    (U2)U2_MAX,            /* CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01          */
    (U2)100U,              /* CRI_CUESHEET_0_TYT_DAN_MET_TBZ_REVERSE_INT_24_01           */
    (U2)120U,              /* CRI_CUESHEET_0_TYT_DAN_MET_TBZ_SEAREM_LV1_24_01            */
    (U2)40U,               /* CRI_CUESHEET_0_TYT_DAN_MET_TBZ_SEAREM_LV2_24_01            */
    (U2)120U,              /* CRI_CUESHEET_0_TYT_TAN_MET_TBZ_SEAREM_LV1_24_01            */
    (U2)36U,               /* CRI_CUESHEET_0_TYT_TAN_MET_TBZ_MMTURHAZ_FLA1_24_01         */
    (U2)36U,               /* CRI_CUESHEET_0_TYT_TAN_MET_TBZ_MMTURHAZ_FLA2_24_01         */
    (U2)U2_MAX,            /* CRI_CUESHEET_0_TYT_REN_MET_TBZ_CLESON_FRS_24_01            */
    (U2)20U,               /* CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRM_24_01            */
    (U2)50U,               /* CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRL_24_01            */
    (U2)70U,               /* CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRF_24_01            */
    (U2)20U,               /* CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRM_24_00            */
    (U2)50U,               /* CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRL_24_00            */
    (U2)70U,               /* CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRF_24_00            */
    (U2)200U,              /* CRI_CUESHEET_0_TYT_DAN_MET_CBZ_AD_DOT_0_00                 */
    (U2)42U                /* CRI_CUESHEET_0_TYT_3REN_MET_CBZ_BASE_INTWARNH_0_01         */
};

/* Table of sound cycle every timbre */
static const U2 u2_sp_SOUND_WAV_CYCLETIME_LEX[CRI_CUESHEET_0_LEX_CUENUM_ADX] = {
    (U2)90U,               /* CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01           */
    (U2)20U,               /* CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE2_0_01           */
    (U2)20U,               /* CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01            */
    (U2)26U,               /* CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01           */
    (U2)70U,               /* CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01          */
    (U2)40U,               /* CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01          */
    (U2)14U,               /* CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNH_0_01          */
    (U2)U2_MAX,            /* CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01          */
    (U2)100U,              /* CRI_CUESHEET_0_LEX_DAN_MET_LBZ_REVERSE_INT_24_01           */
    (U2)200U,              /* CRI_CUESHEET_0_LEX_DAN_MET_LBZ_SEAREM_LV1_24_02            */
    (U2)144U,              /* CRI_CUESHEET_0_LEX_DAN_MET_LBZ_SEAREM_LV2_24_02            */
    (U2)200U,              /* CRI_CUESHEET_0_LEX_TAN_MET_LBZ_SEAREM_LV1_24_02            */
    (U2)36U,               /* CRI_CUESHEET_0_LEX_TAN_MET_LBZ_MMTURHAZ_FLA1_24_02         */
    (U2)36U,               /* CRI_CUESHEET_0_LEX_TAN_MET_LBZ_MMTURHAZ_FLA2_24_02         */
    (U2)U2_MAX,            /* CRI_CUESHEET_0_LEX_REN_MET_LBZ_CLESON_FRS_24_00            */
    (U2)20U,               /* CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRM_24_01            */
    (U2)50U,               /* CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRL_24_01            */
    (U2)70U,               /* CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRF_24_02            */
    (U2)20U,               /* CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRM_24_01            */
    (U2)50U,               /* CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRL_24_01            */
    (U2)70U,               /* CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRF_24_02            */
    (U2)200U,              /* CRI_CUESHEET_0_LEX_DAN_MET_CBZ_AD_DOT_0_00                 */
    (U2)42U                /* CRI_CUESHEET_0_LEX_3REN_MET_CBZ_BASE_INTWARNH_0_01         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_SoundCriMgrInitialize(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SoundCriMgrInitialize(void)
{
    u1_s_sound_drv_active_time_val1 = (U1)0U;
    u1_s_sound_drv_active_time_val2 = (U1)0U;
    u1_s_sound_drv_active_time_val3 = (U1)0U;

    u1_s_sound_ic_fltb_befor        = (U1)STD_HIGH;
    u1_s_sound_ic_fltb_count        = (U1)0U;
    u1_s_sound_ic_fltb_initial      = (U1)SOUND_DRV_INITIAL;
    u1_s_sound_ic_error             = (U1)SOUND_IC_NORMAL;

    s4_s_initialize_size            = (CriSint32)0;
    s4_s_acfdata_size               = (CriSint32)0;
    s4_s_awbdata_size               = (CriSint32)0;
    s4_s_acbdata_size               = (CriSint32)0;
    s4_s_voicepooladxdata_size      = (CriSint32)0;
    s4_s_player_size                = (CriSint32)0;

    Dio_WriteChannel((U1)DIO_ID_PORT20_CH1, (U1)STD_HIGH);
    Dio_WriteChannel((U1)DIO_ID_PORT20_CH2, (U1)STD_HIGH);
    Dio_WriteChannel((U1)DIO_ID_PORT0_CH5, (U1)STD_HIGH);
}

/*===================================================================================================================================*/
/*  void    vd_s_SoundCriMgrStartup(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_SoundCriMgrStartup(void)
{
    CriAtomExConfig_Rh850u2a                st_t_config_rh850u2a;             /* Configuration structure for library initialization  */
    CriAtomExPlayerConfig                   st_t_sound_player_config;         /* Configuration structure for AtomEx player creation  */
    U1                                      u1_t_grp_no;                      /* Sound group number                                  */
    U1                                      u1_t_brand;                       /* From MCUCONST Brand Info                            */

    criAtomEx_PreInitialize_Rh850u2a();

    vd_g_SoundCriDrvInitialize();
    u1_t_brand           = u1_g_VardefOmusMCUID0024();

    __DI();
    Dma_SetInterrupt( (U1)DMA_CH_DATA_ID_3, (U1)OFF, (U1)ON );
    __EI();

#if (SOUND_CRI_DEBUGMODE == TRUE)
    criErr_SetCallback(vd_s_SoundCriMgrErrorCallback);
#endif /* SOUND_CRI_DEBUGMODE */

    /* Set configuration structure for library initialization in default value */
    criAtomEx_SetDefaultConfig_Rh850u2a(&st_t_config_rh850u2a);

    st_t_config_rh850u2a.drv.timer_start_func                = vd_g_SoundCriDrvTimerInitialize;
    st_t_config_rh850u2a.drv.timer_stop_func                 = vd_g_SoundCriDrvTimerFinalize;
    st_t_config_rh850u2a.drv.timer_get_count_func            = u4_g_SoundCriDrvTimerGetCount;
    st_t_config_rh850u2a.drv.timer_frequency                 = (CriUint32)SOUND_CRI_TIMER_FREQUENCY;

    st_t_config_rh850u2a.sfr_config.taud_clk                 = (CriUint32)SOUND_CRI_CLKFIX_CLK;
    st_t_config_rh850u2a.sfr_config.drv.dmac_start_func        = vd_g_SoundCriDrvDmacStart;
    st_t_config_rh850u2a.sfr_config.drv.dmac_intr_func         = vd_g_SoundCriDrvDmacIntr;
    st_t_config_rh850u2a.sfr_config.drv.dmac_stop_func         = vd_g_SoundCriDrvDmacStop;
    st_t_config_rh850u2a.sfr_config.drv.dmac_disable_intr_func = vd_g_SoundCriDrvDmaDisableIntr;
    st_t_config_rh850u2a.sfr_config.drv.dmac_enable_intr_func  = vd_g_SoundCriDrvDmaEnableIntr;
    st_t_config_rh850u2a.sfr_config.drv.taud_start_func        = vd_g_SoundCriDrvTaudStart;
    st_t_config_rh850u2a.sfr_config.drv.taud_stop_func         = vd_g_SoundCriDrvTaudStop;

    st_t_config_rh850u2a.atom_ex.max_virtual_voices          = (CriSint32)SOUND_CRI_MAX_VIRTUAL_VOICES;
    st_t_config_rh850u2a.atom_ex.max_tracks                  = (CriUint32)SOUND_CRI_MAX_TRACKS;
    st_t_config_rh850u2a.atom_ex.max_track_items             = (CriUint32)SOUND_CRI_MAX_TRACK_ITEMS;
    st_t_config_rh850u2a.atom_ex.max_sequences               = (CriSint32)SOUND_CRI_MAX_SEQUENCES;

#if (SOUND_CRI_DEBUGMODE == TRUE)
    s4_s_initialize_size = (CriSint32)criAtomEx_CalculateWorkSize_Rh850u2a(&st_t_config_rh850u2a);
    s4_s_initialize_size = s4_s_initialize_size;                          /* QAC countermeasure */
#else
    s4_s_initialize_size = (CriSint32)SOUND_CRI_INIT_WORK_SIZE;
#endif /* SOUND_CRI_DEBUGMODE */

    /* Library initialization */
    criAtomEx_Initialize_Rh850u2a(&st_t_config_rh850u2a, s1_sp_sound_cri_init_work, (CriSint32)SOUND_CRI_INIT_WORK_SIZE);

    if(u1_t_brand == (U1)CALIB_MCUID0024_LEXUS){
        vd_s_SoundCriMgrLEXSetUp();
    }
    else{
        vd_s_SoundCriMgrTYTSetUp();
    }

    /* Set configuration structure for AtomEx player creation in default value */
    criAtomExPlayer_SetDefaultConfig(&st_t_sound_player_config);
#if (SOUND_CRI_DEBUGMODE == TRUE)
    s4_s_player_size = (CriSint32)criAtomExPlayer_CalculateWorkSize(&st_t_sound_player_config);
    s4_s_player_size = s4_s_player_size;                                  /* QAC countermeasure */
#else
    s4_s_player_size = (CriSint32)SOUND_PLAYER_SIZE;
#endif /* SOUND_CRI_DEBUGMODE */

    for(u1_t_grp_no = (U1)SOUND_GROUP1; u1_t_grp_no < (U1)SOUND_GROUP_NUM; u1_t_grp_no++){
        /* AtomEx player creation every CH */
        stp_sp_sound_player_hn_gp[u1_t_grp_no] = criAtomExPlayer_Create(&st_t_sound_player_config,
                                                                        u1_sp2_sound_player_alloc[u1_t_grp_no],
                                                                        (CriSint32)SOUND_PLAYER_SIZE);

        u2_sp_sound_cur_cycletim[u1_t_grp_no]        = (U2)0U;
        u2_sp_sound_cycle_cnt[u1_t_grp_no]           = (U2)U2_MAX;
        u1_sp_sound_pre_reqidx[u1_t_grp_no]          = (U1)U1_MAX;
        u1_sp_sound_pre_reqvol[u1_t_grp_no]          = (U1)U1_MAX;

        st_sp_sound_ow_ctrl[u1_t_grp_no].u1_ow_sts   = (U1)SOUND_OW_CTRL_INA;
        st_sp_sound_ow_ctrl[u1_t_grp_no].u2_ow_tocnt = (U2)U2_MAX;
    }

    u1_s_sound_csrbz_reqbrg = (U1)U1_MAX;
    u1_s_sound_csrbz_volbrg = (U1)U1_MAX;

    u4_s_sound_ow_unlock    = (U4)0U;
    u1_s_sound_ow_reqid     = (U1)U1_MAX;
    Port_SetPinMode((U2)PORT_ID_PORT20_PIN1,   (U4)PORT_MODE_CFG_P20_1_TAUD1O1); 
    Port_SetPinMode((U2)PORT_ID_PORT20_PIN2,   (U4)PORT_MODE_CFG_P20_2_TAUD1O2);
}

/*===================================================================================================================================*/
/*  static  void    vd_s_SoundCriMgrTYTSetUp(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SoundCriMgrTYTSetUp(void)
{
    CriAtomExAdxVoicePoolConfig             st_t_sound_voice_pool_config_adx; /* Configuration structure for ADX voice-pool creation */

#if (SOUND_CRI_DEBUGMODE == TRUE)
    s4_s_acfdata_size = (CriSint32)criAtomEx_CalculateWorkSizeForRegisterAcfDataAt((void *)u4_sp_SOUND_ACF_DATA_TYT, s4_s_SOUND_ACF_DATA_SIZE_TYT);
    s4_s_acfdata_size = s4_s_acfdata_size;                                /* QAC countermeasure */
#else
    s4_s_acfdata_size = (CriSint32)SOUND_ACFDATA_SIZE;
#endif /* SOUND_CRI_DEBUGMODE */
    /* On-memory ACF data registration */
    criAtomEx_RegisterAcfDataAt((void *)u4_sp_SOUND_ACF_DATA_TYT,
                              s4_s_SOUND_ACF_DATA_SIZE_TYT,
                              u1_sp_sound_acfdata_alloc,
                              (CriSint32)SOUND_ACFDATA_SIZE);

#if (SOUND_CRI_DEBUGMODE == TRUE)
    s4_s_awbdata_size = (CriSint32)CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORYAT;
    s4_s_awbdata_size = s4_s_awbdata_size;                                /* QAC countermeasure */
#else
    s4_s_awbdata_size = (CriSint32)SOUND_AWBDATA_SIZE;
#endif /* SOUND_CRI_DEBUGMODE */
    /* On-memory AWB handle creation */
    stp_s_sound_awb_hn = criAtomAwb_LoadFromMemoryAt(u4_sp_SOUND_AWB_DATA_TYT,
                                                     s4_s_SOUND_AWB_DATA_SIZE_TYT,
                                                     u1_sp_sound_awbdata_alloc,
                                                     (CriSint32)SOUND_AWBDATA_SIZE);

#if (SOUND_CRI_DEBUGMODE == TRUE)
    s4_s_acbdata_size = (CriSint32)criAtomExAcb_CalculateWorkSizeForLoadAcbDataWithAwbHnAt((void *)u4_sp_SOUND_ACB_DATA_TYT, s4_s_SOUND_ACB_DATA_SIZE_TYT, stp_s_sound_awb_hn);
    s4_s_acbdata_size = s4_s_acbdata_size;                                /* QAC countermeasure */
#else
    s4_s_acbdata_size = (CriSint32)SOUND_ACBDATA_SIZE;
#endif /* SOUND_CRI_DEBUGMODE */
    /* On-memory ACB data loading */
    stp_s_sound_acb_hn = criAtomExAcb_LoadAcbDataWithAwbHnAt((void *)u4_sp_SOUND_ACB_DATA_TYT,
                                                           s4_s_SOUND_ACB_DATA_SIZE_TYT,
                                                           stp_s_sound_awb_hn,
                                                           u1_sp_sound_acbdata_alloc,
                                                           (CriSint32)SOUND_ACBDATA_SIZE);

    /* Set configuration structure for ADX voice-pool creation in default value */
    criAtomExVoicePool_SetDefaultConfigForAdxVoicePool(&st_t_sound_voice_pool_config_adx);
    st_t_sound_voice_pool_config_adx.num_voices = (CriSint32)SOUND_OVERLAP_ADX_NUM;     /* Assign number of play voices at the same time in this codec */
#if (SOUND_CRI_DEBUGMODE == TRUE)
    s4_s_voicepooladxdata_size = (CriSint32)criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool(&st_t_sound_voice_pool_config_adx);
    s4_s_voicepooladxdata_size = s4_s_voicepooladxdata_size;              /* QAC countermeasure */
#else
    s4_s_voicepooladxdata_size = (CriSint32)SOUND_VOICEPOOLADXDATA_SIZE;
#endif /* SOUND_CRI_DEBUGMODE */
    /* ADX voice-pool creation */
    stp_s_sound_voicepooladx_hn = criAtomExVoicePool_AllocateAdxVoicePool(&st_t_sound_voice_pool_config_adx,
                                                                          u1_sp_sound_voicepooladx_alloc,
                                                                          (CriSint32)SOUND_VOICEPOOLADXDATA_SIZE);
}

/*===================================================================================================================================*/
/*  static        void    vd_s_SoundCriMgrLEXSetUp(void)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static        void    vd_s_SoundCriMgrLEXSetUp(void)
{
    CriAtomExAdxVoicePoolConfig             st_t_sound_voice_pool_config_adx; /* Configuration structure for ADX voice-pool creation */

#if (SOUND_CRI_DEBUGMODE == TRUE)
    s4_s_acfdata_size = (CriSint32)criAtomEx_CalculateWorkSizeForRegisterAcfDataAt((void *)u4_sp_SOUND_ACF_DATA_LEX, s4_s_SOUND_ACF_DATA_SIZE_LEX);
    s4_s_acfdata_size = s4_s_acfdata_size;                                /* QAC countermeasure */
#else
    s4_s_acfdata_size = (CriSint32)SOUND_ACFDATA_SIZE;
#endif /* SOUND_CRI_DEBUGMODE */
    /* On-memory ACF data registration */
    criAtomEx_RegisterAcfDataAt((void *)u4_sp_SOUND_ACF_DATA_LEX,
                              s4_s_SOUND_ACF_DATA_SIZE_LEX,
                              u1_sp_sound_acfdata_alloc,
                              (CriSint32)SOUND_ACFDATA_SIZE);

#if (SOUND_CRI_DEBUGMODE == TRUE)
    s4_s_awbdata_size = (CriSint32)CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORYAT;
    s4_s_awbdata_size = s4_s_awbdata_size;                                /* QAC countermeasure */
#else
    s4_s_awbdata_size = (CriSint32)SOUND_AWBDATA_SIZE;
#endif /* SOUND_CRI_DEBUGMODE */
    /* On-memory AWB handle creation */
    stp_s_sound_awb_hn = criAtomAwb_LoadFromMemoryAt(u4_sp_SOUND_AWB_DATA_LEX,
                                                     s4_s_SOUND_AWB_DATA_SIZE_LEX,
                                                     u1_sp_sound_awbdata_alloc,
                                                     (CriSint32)SOUND_AWBDATA_SIZE);

#if (SOUND_CRI_DEBUGMODE == TRUE)
    s4_s_acbdata_size = (CriSint32)criAtomExAcb_CalculateWorkSizeForLoadAcbDataWithAwbHnAt((void *)u4_sp_SOUND_ACB_DATA_LEX, s4_s_SOUND_ACB_DATA_SIZE_LEX, stp_s_sound_awb_hn);
    s4_s_acbdata_size = s4_s_acbdata_size;                                /* QAC countermeasure */
#else
    s4_s_acbdata_size = (CriSint32)SOUND_ACBDATA_SIZE;
#endif /* SOUND_CRI_DEBUGMODE */
    /* On-memory ACB data loading */
    stp_s_sound_acb_hn = criAtomExAcb_LoadAcbDataWithAwbHnAt((void *)u4_sp_SOUND_ACB_DATA_LEX,
                                                           s4_s_SOUND_ACB_DATA_SIZE_LEX,
                                                           stp_s_sound_awb_hn,
                                                           u1_sp_sound_acbdata_alloc,
                                                           (CriSint32)SOUND_ACBDATA_SIZE);

    /* Set configuration structure for ADX voice-pool creation in default value */
    criAtomExVoicePool_SetDefaultConfigForAdxVoicePool(&st_t_sound_voice_pool_config_adx);
    st_t_sound_voice_pool_config_adx.num_voices = (CriSint32)SOUND_OVERLAP_ADX_NUM;     /* Assign number of play voices at the same time in this codec */
#if (SOUND_CRI_DEBUGMODE == TRUE)
    s4_s_voicepooladxdata_size = (CriSint32)criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool(&st_t_sound_voice_pool_config_adx);
    s4_s_voicepooladxdata_size = s4_s_voicepooladxdata_size;              /* QAC countermeasure */
#else
    s4_s_voicepooladxdata_size = (CriSint32)SOUND_VOICEPOOLADXDATA_SIZE;
#endif /* SOUND_CRI_DEBUGMODE */
    /* ADX voice-pool creation */
    stp_s_sound_voicepooladx_hn = criAtomExVoicePool_AllocateAdxVoicePool(&st_t_sound_voice_pool_config_adx,
                                                                          u1_sp_sound_voicepooladx_alloc,
                                                                          (CriSint32)SOUND_VOICEPOOLADXDATA_SIZE);
}

/*===================================================================================================================================*/
/*  void    vd_g_SoundCriMgrFinalize(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SoundCriMgrFinalize(void)
{
    U1  u1_t_grp_no;                                                                        /* Sound group number                    */

    /* Release library functions */
    for(u1_t_grp_no = (U1)SOUND_GROUP1; u1_t_grp_no < (U1)SOUND_GROUP_NUM; u1_t_grp_no++){
        criAtomExPlayer_Destroy(stp_sp_sound_player_hn_gp[u1_t_grp_no]);
    }
    criAtomExVoicePool_Free(stp_s_sound_voicepooladx_hn);
    criAtomExAcb_Release(stp_s_sound_acb_hn);
    criAtomAwb_Release(stp_s_sound_awb_hn);
    criAtomEx_UnregisterAcf();
    criAtomEx_Finalize_Rh850u2a();

    s4_s_initialize_size       = (CriSint32)0;
    s4_s_acfdata_size          = (CriSint32)0;
    s4_s_awbdata_size          = (CriSint32)0;
    s4_s_acbdata_size          = (CriSint32)0;
    s4_s_voicepooladxdata_size = (CriSint32)0;
    s4_s_player_size           = (CriSint32)0;
}

/*===================================================================================================================================*/
/*  void    vd_g_SoundCriMgrMainTask(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SoundCriMgrMainTask(void)
{
    U1          u1_t_playnum;                                                               /* Number of playing sound groups        */
    U1          u1_t_errsts;
    U1          u1_t_mode;
    U1          u1_t_initstate;

    u1_t_mode = u1_s_SoundDiagnosis();

    if (u1_t_mode != (U1)SOUND_DRV_MODESET) {
        u1_t_initstate = u1_s_SoundCriMgr_InitialCheck();
        if (u1_t_initstate != (U1)SOUND_DRV_INITIAL_END) {
            vd_s_SoundCriMgrStartup();
        }
        else {
            u1_t_errsts  = (U1)Dma_CheckDmaError((U1)DMA_CH_DATA_ID_2);
            u1_t_errsts |= (U1)Dma_CheckDmaError((U1)DMA_CH_DATA_ID_3);
            u1_t_errsts |= (U1)Dma_CheckDmaError((U1)DMA_CH_DATA_ID_4);

            if(u1_t_errsts == (U1)DMA_DTSER_DTSER_ERR){
                Dma_ClearDmaError((U1)DMA_CH_DATA_ID_2);
                Dma_ClearDmaError((U1)DMA_CH_DATA_ID_3);
                Dma_ClearDmaError((U1)DMA_CH_DATA_ID_4);

                vd_g_SoundCriMgrFinalize();
                vd_s_SoundCriMgrStartup();
            }
        }

        u1_t_playnum = u1_s_SoundCriMgrWavNext();                                           /* Control buzzer sounding every CH      */
        vd_s_SoundCriMgrUpdtLib(u1_t_playnum);                                              /* Library periodic process              */
    }
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SoundCriMgrWavNext(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SoundCriMgrWavNext(void)
{
    /* Table to convert the requested buzzer ID to the cue ID */
    static const U2 u2_sp_SOUND_REQ_TO_WAV_TYT[WCHIME_NUM_REQ] = {
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_PCS_TSTMD1              */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_PCS_TSTMD5              */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_PCS_TSTMD6              */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_FRRADA_CMP              */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_FRRADA_ERR              */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE2_0_01,                                 /* WCHIME_REQ_SI_PTS_RDY                 */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_PCS                     */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_ACC                     */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_STEER_UNDRIVE           */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_LCS_APR                 */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI8          */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_DOA                     */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_TBZ_CLESON_FRS_24_01,                                  /* WCHIME_REQ_CO_CSR_FR_SD               */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRM_24_01,                                  /* WCHIME_REQ_IN_CSR_FR_MD               */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_TBZ_CLESON_FRS_24_01,                                  /* WCHIME_REQ_CO_CSR_RR_SD               */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRM_24_00,                                  /* WCHIME_REQ_IN_CSR_RR_MD               */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_TBZ_CLESON_FRS_24_01,                                  /* WCHIME_REQ_CO_CSR_FRRR_SD             */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRM_24_01,                                  /* WCHIME_REQ_IN_CSR_FRRR_MD             */
        (U2)CRI_CUESHEET_0_TYT_3REN_MET_CBZ_BASE_INTWARNH_0_01,                               /* WCHIME_REQ_IN_CSR_RCTA                */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_SYSMAL_REMDST_0M        */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TCW_BUZ                 */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_PCS_PED                 */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_FCTA_STEP_STOP          */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_EDSS_R04                */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRL_24_01,                                  /* WCHIME_REQ_IN_CSR_FR_LD               */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRL_24_00,                                  /* WCHIME_REQ_IN_CSR_RR_LD               */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRL_24_01,                                  /* WCHIME_REQ_IN_CSR_FRRR_LD             */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_DA                      */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TCHAR_CYCL2             */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI7          */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_EDSS_R03                */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI6P5        */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_EIGCON_EG_PWROFF        */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BATTRW                  */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_SCB                     */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BSM                     */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_LDA                     */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_INFRA_INT               */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_SMASTA_INT3             */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRF_24_01,                                  /* WCHIME_REQ_IN_CSR_FR_FD               */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRF_24_00,                                  /* WCHIME_REQ_IN_CSR_RR_FD               */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRF_24_01,                                  /* WCHIME_REQ_IN_CSR_FRRR_FD             */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TCHAR_CYCL1             */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_FLDLEAK             */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_STEER_STP               */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI6          */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_SEAREM_LV1_24_01,                                  /* WCHIME_REQ_IN_SBLT_FMV                */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_ACC_BRKREQ              */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_SBW_RJCT                */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_NACCON                  */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_PEXI_HV_NDBW            */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_ACCHOL                  */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_SBW_AUTOP               */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_RSA_SIGN_CAUTION2       */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_ESWUOC_REL              */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_PMAR                    */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BRK_APP6                */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_SYSMAL_RNG_P            */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_CHAMAL_BAT_FAIL         */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_SYSMAL_REQSTP           */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_APP4                */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI5         */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI5          */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_EPB                     */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_EIGCON_IGOFF            */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_ACC_LSPDCNSL            */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_LTA_CNCL                */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_LCS_CNCL                */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI4P5        */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI4P5        */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI4P5        */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_SFTPOS_NML              */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_APP_DIS_ASSIST          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_APP_CMPLT               */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_DCLDSP_OPERJCT          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_LCS_ACK                 */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BSTMOD_RJCT             */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_DOA_RJCT                */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_MET_WRN_VOL_CSTM        */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_SBW_SPL_STATE           */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_EDSS_WRN_BUZ            */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_DMC_LV2                 */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_REVERSE_INT_24_01,                                 /* WCHIME_REQ_IN_SFTPOS_REV              */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_SMASTA_INT2             */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_SMASTA_CON              */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_SEAREM_LV2_24_01,                                  /* WCHIME_REQ_IN_SBLT_LV2                */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_ACC_OVERSPD             */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_ACC_SHIFTREQ            */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TPMS_CYCL               */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_SWS                     */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_MINDSPWR_LV2            */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_BGLFSPD                 */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_DR_OPN                  */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_SYS_MAL             */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_SYS_NOOPE2          */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_BRK_SYS_NOOPE1          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_STEER_LMT               */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_SBW_MAL                 */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_SBW_MAL                 */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_SYSMAL_REMDST_500M      */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_SYSMAL_REMDST_1KM       */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_LTA_PTN2                */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_LTA_PTN3                */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI4          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI4          */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI4          */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI4         */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI4          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_MINDSPWR_LV1            */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_SEAREM_LV1_24_01,                                  /* WCHIME_REQ_IN_SBLT_LV1                */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_SEAREM_LV1_24_01,                                  /* WCHIME_REQ_IN_SBLT_MISUSE             */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_TBZ_SEAREM_LV1_24_01,                                  /* WCHIME_REQ_SI_SBLT                    */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_RSA_SIGN_CTN1           */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_DMC_LV1                 */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_SYSMAL_FAIL             */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_PDSMAL                  */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_LTA_PTN1                */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_INFRA_SNGL              */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_MLT_MSG                 */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI3          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI3          */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI3          */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI3         */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI3          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_ACC_AUTOSTART           */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_LIGHT                   */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_SBW_RCPT                */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_AD_DOT_0_00,                                       /* WCHIME_REQ_IN_TMBZR_DOHREQ            */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_LDA_HFCT                */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_BATINS                  */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TPMS_SINGLE             */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TCHAR_SNGL              */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_LDA_WARN                */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_SMASTA_SNGL             */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TOWWAR                  */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMN_LVN                 */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI2          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI2          */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI2          */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI2         */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI2          */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_SMASTA_INT1             */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BRK_APP3                */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_APP1                */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_APP2                */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTACT_R16        */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTREL            */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTACT_R07        */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTACT_R08        */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTACT_R17        */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_REL_R10           */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_REL_R11           */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTACT_R13        */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI1          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI1          */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI1          */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI1         */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI1          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_BRK_APP5                */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE2_0_01,                                 /* WCHIME_REQ_SI_RSA_CHG_SPLDLMT         */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_ACC_APPRVLSTART         */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_FMSEAT_MEM_SCS          */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_FMSEAT_MEM_REJ          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_FMSEAT_ERS_INFO         */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_FMSEAT_MEM_CALL         */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_ESWUOC_RJCT             */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_SMASTA_SNGL2            */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_TBZ_MMTURHAZ_FLA1_24_01,                               /* WCHIME_REQ_SI_TURHAZ_STA_LS           */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_TBZ_MMTURHAZ_FLA1_24_01,                               /* WCHIME_REQ_SI_TURHAZ_STA_MS           */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_TBZ_MMTURHAZ_FLA1_24_01,                               /* WCHIME_REQ_SI_TURHAZ_STA_HS           */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_TBZ_MMTURHAZ_FLA2_24_01,                               /* WCHIME_REQ_SI_TURHAZ_FIN_LS           */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_TBZ_MMTURHAZ_FLA2_24_01,                               /* WCHIME_REQ_SI_TURHAZ_FIN_MS           */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_TBZ_MMTURHAZ_FLA2_24_01,                               /* WCHIME_REQ_SI_TURHAZ_FIN_HS           */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI0          */
        (U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI0          */
        (U2)CRI_CUESHEET_0_TYT_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI0          */
        (U2)CRI_CUESHEET_0_TYT_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI0         */
        (U2)CRI_CUESHEET_0_TYT_DAN_MET_CBZ_BASE_INTWARNL_0_01                                 /* WCHIME_REQ_IN_TMBZR_TEN_PRI0          */
    };

    static const U2 u2_sp_SOUND_REQ_TO_WAV_LEX[WCHIME_NUM_REQ] = {
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_PCS_TSTMD1              */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_PCS_TSTMD5              */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_PCS_TSTMD6              */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_FRRADA_CMP              */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_FRRADA_ERR              */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE2_0_01,                                 /* WCHIME_REQ_SI_PTS_RDY                 */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_PCS                     */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_ACC                     */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_STEER_UNDRIVE           */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_LCS_APR                 */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI8          */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_DOA                     */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_LBZ_CLESON_FRS_24_00,                                  /* WCHIME_REQ_CO_CSR_FR_SD               */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRM_24_01,                                  /* WCHIME_REQ_IN_CSR_FR_MD               */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_LBZ_CLESON_FRS_24_00,                                  /* WCHIME_REQ_CO_CSR_RR_SD               */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRM_24_01,                                  /* WCHIME_REQ_IN_CSR_RR_MD               */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_LBZ_CLESON_FRS_24_00,                                  /* WCHIME_REQ_CO_CSR_FRRR_SD             */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRM_24_01,                                  /* WCHIME_REQ_IN_CSR_FRRR_MD             */
        (U2)CRI_CUESHEET_0_LEX_3REN_MET_CBZ_BASE_INTWARNH_0_01,                               /* WCHIME_REQ_IN_CSR_RCTA                */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_SYSMAL_REMDST_0M        */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TCW_BUZ                 */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_PCS_PED                 */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_FCTA_STEP_STOP          */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNH_0_01,                                /* WCHIME_REQ_IN_EDSS_R04                */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRL_24_01,                                  /* WCHIME_REQ_IN_CSR_FR_LD               */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRL_24_01,                                  /* WCHIME_REQ_IN_CSR_RR_LD               */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRL_24_01,                                  /* WCHIME_REQ_IN_CSR_FRRR_LD             */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_DA                      */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TCHAR_CYCL2             */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI7          */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_EDSS_R03                */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI6P5        */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_EIGCON_EG_PWROFF        */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BATTRW                  */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_SCB                     */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BSM                     */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_LDA                     */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_INFRA_INT               */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_SMASTA_INT3             */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRF_24_02,                                  /* WCHIME_REQ_IN_CSR_FR_FD               */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRF_24_02,                                  /* WCHIME_REQ_IN_CSR_RR_FD               */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRF_24_02,                                  /* WCHIME_REQ_IN_CSR_FRRR_FD             */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TCHAR_CYCL1             */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_FLDLEAK             */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_STEER_STP               */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI6          */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_SEAREM_LV1_24_02,                                  /* WCHIME_REQ_IN_SBLT_FMV                */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_ACC_BRKREQ              */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_SBW_RJCT                */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_NACCON                  */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_PEXI_HV_NDBW            */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_ACCHOL                  */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_SBW_AUTOP               */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_RSA_SIGN_CAUTION2       */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_ESWUOC_REL              */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_PMAR                    */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BRK_APP6                */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_SYSMAL_RNG_P            */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_CHAMAL_BAT_FAIL         */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_SYSMAL_REQSTP           */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_APP4                */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI5         */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI5          */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_EPB                     */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_EIGCON_IGOFF            */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_ACC_LSPDCNSL            */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_LTA_CNCL                */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_LCS_CNCL                */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI4P5        */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI4P5        */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI4P5        */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_SFTPOS_NML              */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_APP_DIS_ASSIST          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_APP_CMPLT               */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_DCLDSP_OPERJCT          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_LCS_ACK                 */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BSTMOD_RJCT             */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_DOA_RJCT                */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_MET_WRN_VOL_CSTM        */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_SBW_SPL_STATE           */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_EDSS_WRN_BUZ            */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_DMC_LV2                 */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_REVERSE_INT_24_01,                                 /* WCHIME_REQ_IN_SFTPOS_REV              */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_SMASTA_INT2             */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_SMASTA_CON              */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_SEAREM_LV2_24_02,                                  /* WCHIME_REQ_IN_SBLT_LV2                */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_ACC_OVERSPD             */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_ACC_SHIFTREQ            */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TPMS_CYCL               */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_SWS                     */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_MINDSPWR_LV2            */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_BGLFSPD                 */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_DR_OPN                  */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_SYS_MAL             */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_SYS_NOOPE2          */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_BRK_SYS_NOOPE1          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_STEER_LMT               */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_SBW_MAL                 */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_SBW_MAL                 */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_SYSMAL_REMDST_500M      */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_SYSMAL_REMDST_1KM       */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_LTA_PTN2                */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_LTA_PTN3                */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI4          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI4          */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI4          */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI4         */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI4          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_MINDSPWR_LV1            */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_SEAREM_LV1_24_02,                                  /* WCHIME_REQ_IN_SBLT_LV1                */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_SEAREM_LV1_24_02,                                  /* WCHIME_REQ_IN_SBLT_MISUSE             */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_LBZ_SEAREM_LV1_24_02,                                  /* WCHIME_REQ_SI_SBLT                    */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_RSA_SIGN_CTN1           */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_DMC_LV1                 */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_SYSMAL_FAIL             */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_PDSMAL                  */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_LTA_PTN1                */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_INFRA_SNGL              */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_MLT_MSG                 */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI3          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI3          */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI3          */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI3         */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI3          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_ACC_AUTOSTART           */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_LIGHT                   */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_SBW_RCPT                */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_AD_DOT_0_00,                                       /* WCHIME_REQ_IN_TMBZR_DOHREQ            */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_LDA_HFCT                */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_BATINS                  */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TPMS_SINGLE             */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TCHAR_SNGL              */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_LDA_WARN                */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_SMASTA_SNGL             */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_TOWWAR                  */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMN_LVN                 */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI2          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI2          */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI2          */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI2         */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI2          */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_SMASTA_INT1             */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BRK_APP3                */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_APP1                */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNM_0_01,                                /* WCHIME_REQ_IN_BRK_APP2                */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTACT_R16        */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTREL            */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTACT_R07        */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTACT_R08        */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTACT_R17        */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_REL_R10           */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_REL_R11           */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_BKHLD_NOTACT_R13        */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI1          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI1          */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI1          */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI1         */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01,                                /* WCHIME_REQ_IN_TMBZR_TEN_PRI1          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_BRK_APP5                */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE2_0_01,                                 /* WCHIME_REQ_SI_RSA_CHG_SPLDLMT         */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_ACC_APPRVLSTART         */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_FMSEAT_MEM_SCS          */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_FMSEAT_MEM_REJ          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_FMSEAT_ERS_INFO         */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_FMSEAT_MEM_CALL         */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_ESWUOC_RJCT             */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_SMASTA_SNGL2            */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_LBZ_MMTURHAZ_FLA1_24_02,                               /* WCHIME_REQ_SI_TURHAZ_STA_LS           */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_LBZ_MMTURHAZ_FLA1_24_02,                               /* WCHIME_REQ_SI_TURHAZ_STA_MS           */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_LBZ_MMTURHAZ_FLA1_24_02,                               /* WCHIME_REQ_SI_TURHAZ_STA_HS           */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_LBZ_MMTURHAZ_FLA2_24_02,                               /* WCHIME_REQ_SI_TURHAZ_FIN_LS           */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_LBZ_MMTURHAZ_FLA2_24_02,                               /* WCHIME_REQ_SI_TURHAZ_FIN_MS           */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_LBZ_MMTURHAZ_FLA2_24_02,                               /* WCHIME_REQ_SI_TURHAZ_FIN_HS           */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,                                 /* WCHIME_REQ_SI_TMBZR_ANN_PRI0          */
        (U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_ACCEPT_0_01,                                  /* WCHIME_REQ_SI_TMBZR_RCV_PRI0          */
        (U2)CRI_CUESHEET_0_LEX_2REN_MET_CBZ_BASE_REJECT_0_01,                                 /* WCHIME_REQ_SI_TMBZR_RJT_PRI0          */
        (U2)CRI_CUESHEET_0_LEX_REN_MET_CBZ_BASE_CONTWARN_0_01,                                /* WCHIME_REQ_CO_TMBZR_CONT_PRI0         */
        (U2)CRI_CUESHEET_0_LEX_DAN_MET_CBZ_BASE_INTWARNL_0_01                                 /* WCHIME_REQ_IN_TMBZR_TEN_PRI0          */
    };

    const U2    * u2_tp_wav_cycletime;                                                     /* Sound cycle for each brand            */
    U2          u2_t_cri_cuemax;                                                           /* CueMax from CRI                       */
    U2          u2_t_curcueid;                                                             /* Current sounding timbre cue ID        */
    U1          u1_t_playnum;                                                              /* Number of playing sound groups        */
    U1          u1_t_grp_no;                                                               /* Sound group number                    */
    U1          u1_t_reqidx;                                                               /* Index of requested sound              */
    U1          u1_t_reqvol;                                                               /* Index of requested volume             */
    U1          u1_t_cyclchk;                                                              /* Sound cycle complete check            */
    U1          u1_t_ow_sts;                                                               /* Active test current status            */
    U1          u1_t_brand;                                                                /* MCUCONST brand                        */

    u1_t_playnum = (U1)0U;
    u1_t_brand = u1_g_VardefOmusMCUID0024();

    if(u1_t_brand == (U1)CALIB_MCUID0024_LEXUS){
        u2_t_cri_cuemax = (U2)CRI_CUESHEET_0_LEX_CUENUM_ADX;
        u2_tp_wav_cycletime = &u2_sp_SOUND_WAV_CYCLETIME_LEX[0];
    }
    else{
        u2_t_cri_cuemax = (U2)CRI_CUESHEET_0_TYT_CUENUM_ADX;
        u2_tp_wav_cycletime = &u2_sp_SOUND_WAV_CYCLETIME_TYT[0];
    }

    for(u1_t_grp_no = (U1)SOUND_GROUP1; u1_t_grp_no < (U1)SOUND_GROUP_NUM; u1_t_grp_no++){
        /* Count sound cycle */
        if(u2_sp_sound_cycle_cnt[u1_t_grp_no] < (U2)SOUND_CYCLETIME_MAX){
            u2_sp_sound_cycle_cnt[u1_t_grp_no]++;
        }
        /* Check sound cycle complete */
        if(u2_sp_sound_cycle_cnt[u1_t_grp_no] >= u2_sp_sound_cur_cycletim[u1_t_grp_no]){
            u1_t_cyclchk = (U1)TRUE;
        }
        else{
            u1_t_cyclchk = (U1)FALSE;
        }

        /* Control sounding buzzer */
        u1_t_reqidx   = (U1)U1_MAX;
        u2_t_curcueid = (U2)SOUND_CUEID_INVALID;
        u1_t_reqvol   = (U1)U1_MAX;

        u1_t_ow_sts   = u1_s_SoundCriMgrOwChk(u1_t_grp_no, u1_t_cyclchk, &u2_t_curcueid, &u1_t_reqvol);
        if(u1_t_ow_sts == (U1)SOUND_OW_CTRL_INA){
            u1_t_reqidx = u1_g_wChimeReqSel(u1_t_grp_no, &u1_t_reqvol);
            u1_t_reqidx = u1_s_SoundCriMgrUpdtNext(u1_t_grp_no, u1_t_reqidx, &u1_t_reqvol);

            if(u1_t_reqidx < (U1)WCHIME_NUM_REQ){
                if(u1_t_brand == (U1)CALIB_MCUID0024_LEXUS){
                    u2_t_curcueid = u2_sp_SOUND_REQ_TO_WAV_LEX[u1_t_reqidx];
                }
                else{
                    u2_t_curcueid = u2_sp_SOUND_REQ_TO_WAV_TYT[u1_t_reqidx];
                }
            }
        }
        if(u2_t_curcueid < u2_t_cri_cuemax){
            u1_t_playnum++;
            u2_sp_sound_cur_cycletim[u1_t_grp_no] = u2_tp_wav_cycletime[u2_t_curcueid];
            /* Check clear counter of sound cycle */
            if((u1_t_reqidx  != u1_sp_sound_pre_reqidx[u1_t_grp_no]) ||
               (u1_t_reqvol  != u1_sp_sound_pre_reqvol[u1_t_grp_no]) ||
               (u1_t_cyclchk == (U1)TRUE                           ) ||
               (u1_t_ow_sts  == (U1)SOUND_OW_CTRL_STA              )){
                vd_s_SoundCriMgrStartByCueId(u1_t_grp_no, u2_t_curcueid);
                u2_sp_sound_cycle_cnt[u1_t_grp_no] = (U2)0U;
            }
            u1_sp_sound_pre_reqidx[u1_t_grp_no] = u1_t_reqidx;
            u1_sp_sound_pre_reqvol[u1_t_grp_no] = u1_t_reqvol;
        }
        else{
            vd_s_SoundCriMgrStop(u1_t_grp_no);
            u2_sp_sound_cur_cycletim[u1_t_grp_no] = (U2)0U;
            u2_sp_sound_cycle_cnt[u1_t_grp_no]    = (U2)U2_MAX;
            u1_sp_sound_pre_reqidx[u1_t_grp_no]   = (U1)U1_MAX;
            u1_sp_sound_pre_reqvol[u1_t_grp_no]   = (U1)U1_MAX;
        }
    }

    return(u1_t_playnum);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SoundCriMgrUpdtNext(const U1 u1_a_GRP_NO, const U1 u1_a_REQIDX, U1 * u1p_a_reqvol)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SoundCriMgrUpdtNext(const U1 u1_a_GRP_NO, const U1 u1_a_REQIDX, U1 * u1p_a_reqvol)
{
    /* Table to convert the requested buzzer ID of clearance sonar to the bridge buzzer ID */
    static const ST_SOUND_CSR_BRG_REQ  st_sp_SOUND_CSR_BRG_LIST[SOUND_CSR_BRG_REQ_NUM] = {
        {(U1)WCHIME_REQ_IN_CSR_RR_MD,   (U1)U1_MAX,                  (U1)WCHIME_REQ_IN_CSR_RR_MD},
        {(U1)WCHIME_REQ_IN_CSR_RR_LD,   (U1)U1_MAX,                  (U1)WCHIME_REQ_IN_CSR_RR_LD},
        {(U1)WCHIME_REQ_IN_CSR_RR_FD,   (U1)U1_MAX,                  (U1)WCHIME_REQ_IN_CSR_RR_FD},
        {(U1)WCHIME_REQ_IN_CSR_FRRR_MD, (U1)WCHIME_REQ_IN_CSR_FR_MD, (U1)WCHIME_REQ_IN_CSR_RR_MD},
        {(U1)WCHIME_REQ_IN_CSR_FRRR_LD, (U1)WCHIME_REQ_IN_CSR_FR_LD, (U1)WCHIME_REQ_IN_CSR_RR_LD},
        {(U1)WCHIME_REQ_IN_CSR_FRRR_FD, (U1)WCHIME_REQ_IN_CSR_FR_FD, (U1)WCHIME_REQ_IN_CSR_RR_FD}
    };

    U1          u1_t_updtdreq;
    U4          u4_t_loop;

    u1_t_updtdreq = u1_a_REQIDX;

    /* Bridge the clearance sonar Rr buzzer to CH5 */
    if(u1_a_GRP_NO == (U1)SOUND_GROUP3){
        u1_s_sound_csrbz_reqbrg = (U1)U1_MAX;
        u1_s_sound_csrbz_volbrg = (U1)U1_MAX;
        for(u4_t_loop = (U4)0U; u4_t_loop < (U4)SOUND_CSR_BRG_REQ_NUM; u4_t_loop++){
            if(u1_a_REQIDX == st_sp_SOUND_CSR_BRG_LIST[u4_t_loop].u1_reqid){
                u1_s_sound_csrbz_reqbrg = st_sp_SOUND_CSR_BRG_LIST[u4_t_loop].u1_setid_grp5;
                u1_s_sound_csrbz_volbrg = u1_s_SoundCriMgrGetCsrRrVolume(*u1p_a_reqvol);

                u1_t_updtdreq           = st_sp_SOUND_CSR_BRG_LIST[u4_t_loop].u1_setid_grp3;
                if(u1_t_updtdreq == (U1)U1_MAX){
                    (*u1p_a_reqvol) = (U1)U1_MAX;
                }
                break;
            }
        }
    }

    if(u1_a_GRP_NO == (U1)SOUND_GROUP5){
        u1_t_updtdreq   = u1_s_sound_csrbz_reqbrg;
        (*u1p_a_reqvol) = u1_s_sound_csrbz_volbrg;
    }

    return(u1_t_updtdreq);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SoundCriMgrGetCsrRrVolume(const U1 u1_a_REQVOL)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SoundCriMgrGetCsrRrVolume(const U1 u1_a_REQVOL)
{
    /* Table to convert the requested volume ID to the bridged volume ID */
    static const ST_SOUND_CSR_FRRR_VOL  st_sp_SOUND_CSR_FRRR_VOL[SOUND_CSR_FRRR_VOL_NUM] = {
        {(U1)WCHIME_VOL_CSR_FRRR_MD_FR_0, (U1)WCHIME_VOL_CSR_FRRR_MD_RR_0},
        {(U1)WCHIME_VOL_CSR_FRRR_MD_FR_1, (U1)WCHIME_VOL_CSR_FRRR_MD_RR_1},
        {(U1)WCHIME_VOL_CSR_FRRR_MD_FR_2, (U1)WCHIME_VOL_CSR_FRRR_MD_RR_2},
        {(U1)WCHIME_VOL_CSR_FRRR_MD_FR_3, (U1)WCHIME_VOL_CSR_FRRR_MD_RR_3},
        {(U1)WCHIME_VOL_CSR_FRRR_MD_FR_4, (U1)WCHIME_VOL_CSR_FRRR_MD_RR_4},
        {(U1)WCHIME_VOL_CSR_FRRR_MD_FR_5, (U1)WCHIME_VOL_CSR_FRRR_MD_RR_5},
        {(U1)WCHIME_VOL_CSR_FRRR_MD_FR_6, (U1)WCHIME_VOL_CSR_FRRR_MD_RR_6},
        {(U1)WCHIME_VOL_CSR_FRRR_MD_FR_7, (U1)WCHIME_VOL_CSR_FRRR_MD_RR_7},
        {(U1)WCHIME_VOL_CSR_FRRR_LD_FR_0, (U1)WCHIME_VOL_CSR_FRRR_LD_RR_0},
        {(U1)WCHIME_VOL_CSR_FRRR_LD_FR_1, (U1)WCHIME_VOL_CSR_FRRR_LD_RR_1},
        {(U1)WCHIME_VOL_CSR_FRRR_LD_FR_2, (U1)WCHIME_VOL_CSR_FRRR_LD_RR_2},
        {(U1)WCHIME_VOL_CSR_FRRR_LD_FR_3, (U1)WCHIME_VOL_CSR_FRRR_LD_RR_3},
        {(U1)WCHIME_VOL_CSR_FRRR_LD_FR_4, (U1)WCHIME_VOL_CSR_FRRR_LD_RR_4},
        {(U1)WCHIME_VOL_CSR_FRRR_LD_FR_5, (U1)WCHIME_VOL_CSR_FRRR_LD_RR_5},
        {(U1)WCHIME_VOL_CSR_FRRR_LD_FR_6, (U1)WCHIME_VOL_CSR_FRRR_LD_RR_6},
        {(U1)WCHIME_VOL_CSR_FRRR_LD_FR_7, (U1)WCHIME_VOL_CSR_FRRR_LD_RR_7},
        {(U1)WCHIME_VOL_CSR_FRRR_FD_FR_0, (U1)WCHIME_VOL_CSR_FRRR_FD_RR_0},
        {(U1)WCHIME_VOL_CSR_FRRR_FD_FR_1, (U1)WCHIME_VOL_CSR_FRRR_FD_RR_1},
        {(U1)WCHIME_VOL_CSR_FRRR_FD_FR_2, (U1)WCHIME_VOL_CSR_FRRR_FD_RR_2},
        {(U1)WCHIME_VOL_CSR_FRRR_FD_FR_3, (U1)WCHIME_VOL_CSR_FRRR_FD_RR_3},
        {(U1)WCHIME_VOL_CSR_FRRR_FD_FR_4, (U1)WCHIME_VOL_CSR_FRRR_FD_RR_4},
        {(U1)WCHIME_VOL_CSR_FRRR_FD_FR_5, (U1)WCHIME_VOL_CSR_FRRR_FD_RR_5},
        {(U1)WCHIME_VOL_CSR_FRRR_FD_FR_6, (U1)WCHIME_VOL_CSR_FRRR_FD_RR_6},
        {(U1)WCHIME_VOL_CSR_FRRR_FD_FR_7, (U1)WCHIME_VOL_CSR_FRRR_FD_RR_7}
    };

    U1          u1_t_updtdvol;
    U4          u4_t_loop;

    u1_t_updtdvol = u1_a_REQVOL;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)SOUND_CSR_FRRR_VOL_NUM; u4_t_loop++){
        if(u1_a_REQVOL == st_sp_SOUND_CSR_FRRR_VOL[u4_t_loop].u1_reqvol){
            u1_t_updtdvol = st_sp_SOUND_CSR_FRRR_VOL[u4_t_loop].u1_setvol;
            break;
        }
    }

    return(u1_t_updtdvol);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SoundCriMgrUpdtLib(const U1 u1_a_PLAYNUM)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SoundCriMgrUpdtLib(const U1 u1_a_PLAYNUM)
{
    U1  u1_t_grp_no;                                                                        /* Sound group number                    */

    /* Update library function */
    for(u1_t_grp_no = (U1)SOUND_GROUP1; u1_t_grp_no < (U1)SOUND_GROUP_NUM; u1_t_grp_no++){
        vd_s_SoundCriMgrSetVolume(u1_t_grp_no, u1_sp_sound_pre_reqvol[u1_t_grp_no], u1_a_PLAYNUM);
        criAtomExPlayer_UpdateAll(stp_sp_sound_player_hn_gp[u1_t_grp_no]);
    }

    criAtomEx_ExecuteMain();
}

/*===================================================================================================================================*/
/*  U1      u1_g_SoundCriMgrShtdwnOk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_SoundCriMgrShtdwnOk(void)
{
    U1                    u1_t_sleep;                                                       /* Sleep check                           */
    CriAtomExPlayerStatus u1_t_sound_sts;                                                   /* AtomEx player status                  */
    U1                    u1_t_grp_no;                                                      /* Sound group number                    */

    u1_t_sleep = (U1)TRUE;                                                                  /* Temporary, Set permission sleep check */

    for(u1_t_grp_no = (U1)SOUND_GROUP1; u1_t_grp_no < (U1)SOUND_GROUP_NUM; u1_t_grp_no++){
        u1_t_sound_sts = criAtomExPlayer_GetStatus(stp_sp_sound_player_hn_gp[u1_t_grp_no]); /* Get AtomEx player status              */

        if((u1_t_sound_sts == (CriAtomExPlayerStatus)CRIATOMEXPLAYER_STATUS_PREP   ) ||     /* Player is preparing condition         */
           (u1_t_sound_sts == (CriAtomExPlayerStatus)CRIATOMEXPLAYER_STATUS_PLAYING)){      /* Player is playing condition           */
            u1_t_sleep = (U1)FALSE;                                                         /* Set prohibition sleep check           */

            break;
        }
    }

    return(u1_t_sleep);
}

/*===================================================================================================================================*/
/*  U2      u2_g_SoundCriMgrGetTimRemained(const U1 u1_a_SO_MDL_CH)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_SoundCriMgrGetTimRemained(const U1 u1_a_SO_MDL_CH)
{
    U2 u2_t_remained;                                                                       /* Sound time of remains                 */
    U1 u1_t_so_mdl_ch;

    u2_t_remained  = (U2)0U;
    u1_t_so_mdl_ch = u1_a_SO_MDL_CH;

    if((u1_a_SO_MDL_CH      <  (U1)SOUND_GROUP_NUM     ) &&
       (u1_s_sound_ow_reqid >= (U1)SOUND_OW_WAV_IDX_NUM)){

        /* In case of the clearance sonar Rr buzzer is sounding */
        if((u1_t_so_mdl_ch          == (U1)SOUND_GROUP3  ) &&
           (u1_s_sound_csrbz_reqbrg <  (U1)WCHIME_NUM_REQ)){
            u1_t_so_mdl_ch = (U1)SOUND_GROUP5;
        }

        /* Calculate sound time of remains in sounding buzzer */
        if(u2_sp_sound_cycle_cnt[u1_t_so_mdl_ch] < u2_sp_sound_cur_cycletim[u1_t_so_mdl_ch]){
            u2_t_remained = u2_sp_sound_cur_cycletim[u1_t_so_mdl_ch] - u2_sp_sound_cycle_cnt[u1_t_so_mdl_ch];
        }
    }

    return(u2_t_remained);
}

/*===================================================================================================================================*/
/*  void    vd_g_SoundCriMgrOwUnlock(const U4 u4_a_KEY)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SoundCriMgrOwUnlock(const U4 u4_a_KEY)
{
    u4_s_sound_ow_unlock = u4_a_KEY;
}

/*===================================================================================================================================*/
/*  void    vd_g_SoundCriMgrOwAct(const U1 u1_a_SO_MDL_CH, const U1 u1_a_WAV_IDX)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SoundCriMgrOwAct(const U1 u1_a_SO_MDL_CH, const U1 u1_a_WAV_IDX)
{
    U1 u1_t_grp_no;                                                                        /* Sound group number                    */
    U1 u1_t_ow_sts;                                                                        /* Test status                           */

    if((u1_a_WAV_IDX         <  (U1)SOUND_OW_WAV_IDX_NUM   ) &&
       (u4_s_sound_ow_unlock == (U4)SOUND_CRI_MNG_OW_UNLOCK)){
        if(u1_s_sound_ow_reqid == u1_a_WAV_IDX){
            u1_t_ow_sts = (U1)SOUND_OW_CTRL_CNT;
        }
        else{
            u1_t_ow_sts = (U1)SOUND_OW_CTRL_STA;
        }
        for(u1_t_grp_no = (U1)SOUND_GROUP1; u1_t_grp_no < (U1)SOUND_GROUP_NUM; u1_t_grp_no++){
            st_sp_sound_ow_ctrl[u1_t_grp_no].u1_ow_sts = u1_t_ow_sts;
        }

        u1_s_sound_ow_reqid = u1_a_WAV_IDX;
    }
    u4_s_sound_ow_unlock = (U4)0U;
}

/*===================================================================================================================================*/
/*  void    vd_g_SoundCriMgrOwDeAct(const U1 u1_a_SO_MDL_CH)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SoundCriMgrOwDeAct(const U1 u1_a_SO_MDL_CH)
{
    u1_s_sound_ow_reqid  = (U1)U1_MAX;
    u4_s_sound_ow_unlock = (U4)0U;
}

/*===================================================================================================================================*/
/*  static  U1      u1_s_SoundCriMgrOwChk(const U1 u1_a_GRP_NO, const U1 u1_a_CYCLCHK, U2 * u2p_a_cueid, U1 * u1p_a_cuevol)          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SoundCriMgrOwChk(const U1 u1_a_GRP_NO, const U1 u1_a_CYCLCHK, U2 * u2p_a_cueid, U1 * u1p_a_cuevol)
{
    /* Table to control the active test */
    static const ST_SOUND_OW_BUZ_INFO st_sp_SOUND_OW_BUZ_INFO_TYT[SOUND_OW_WAV_IDX_NUM] = {
        {   /* SOUND_AT_CLESON_FRS */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_REN_MET_TBZ_CLESON_FRS_24_01,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_SD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRM */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRM_24_01,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_MD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRL */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRL_24_01,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_LD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRF */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRF_24_01,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_FD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_RRS */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_REN_MET_TBZ_CLESON_FRS_24_01,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_SD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_RRM */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRM_24_00   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_MD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_RRL */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRL_24_00   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_LD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_RRF */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRF_24_00   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_FD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRRRS */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_REN_MET_TBZ_CLESON_FRS_24_01,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_SD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRRRM */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRM_24_01,    (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRM_24_00   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_MD_3,                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_MD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRRRL */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRL_24_01,    (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRL_24_00   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_LD_3,                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_LD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRRRF */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_FRF_24_01,    (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_CLESON_RRF_24_00   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_FD_3,                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_FD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_SBW_REVERSE_IN */
            {(U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_REVERSE_INT_24_01,   (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)WCHIME_VOL_REVERSE_IN_MID,                          (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_SEAREM_FMV */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_SEAREM_LV1_24_01,    (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_SEAREM_FMV_MID,                          (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_SEAREM_LV2 */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_SEAREM_LV2_24_01,    (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_SEAREM_LV2_MID,                          (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_SEAREM_LV1 */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_DAN_MET_TBZ_SEAREM_LV1_24_01,    (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_SEAREM_LV1_MID,                          (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_SEAREM_SI */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_TAN_MET_TBZ_SEAREM_LV1_24_01,    (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_SEAREM_SI_MID,                           (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_EVENT                                                                                                                                                                                                                                                                   /* TYPE    */
        },
        {   /* SOUND_AT_MET_CBZ_BASE_NOTICE1 */
            {(U2)CRI_CUESHEET_0_TYT_TAN_MET_CBZ_BASE_NOTICE1_0_01,   (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)WCHIME_VOL_BASE_NOTICE1_MID,                        (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_EVENT                                                                                                                                                                                                                                                                   /* TYPE    */
        },
        {   /* SOUND_AT_MMTURHAZ_STA */
            {(U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_TAN_MET_TBZ_MMTURHAZ_FLA1_24_01, (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)WCHIME_VOL_TURHAZ_STA_MCSTM_MSPD,                   (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_EVENT                                                                                                                                                                                                                                                                   /* TYPE    */
        },
        {   /* SOUND_AT_MMTURHAZ_FIN */
            {(U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_TYT_TAN_MET_TBZ_MMTURHAZ_FLA2_24_01, (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)WCHIME_VOL_TURHAZ_FIN_MCSTM_MSPD,                   (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_EVENT                                                                                                                                                                                                                                                                   /* TYPE    */
        }
    };

    static const ST_SOUND_OW_BUZ_INFO st_sp_SOUND_OW_BUZ_INFO_LEX[SOUND_OW_WAV_IDX_NUM] = {
        {   /* SOUND_AT_CLESON_FRS */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_REN_MET_LBZ_CLESON_FRS_24_00,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_SD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRM */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRM_24_01,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_MD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRL */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRL_24_01,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_LD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRF */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRF_24_02,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_FD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_RRS */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_REN_MET_LBZ_CLESON_FRS_24_00,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_SD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_RRM */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRM_24_01   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_MD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_RRL */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRL_24_01   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_LD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_RRF */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRF_24_02   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_FD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRRRS */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_REN_MET_LBZ_CLESON_FRS_24_00,    (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_SD_3,                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRRRM */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRM_24_01,    (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRM_24_01   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_MD_3,                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_MD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRRRL */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRL_24_01,    (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRL_24_01   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_LD_3,                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_LD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_CLESON_FRRRF */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_FRF_24_02,    (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_CLESON_RRF_24_02   }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_FR_FD_3,                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_CSR_RR_FD_3                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_SBW_REVERSE_IN */
            {(U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_REVERSE_INT_24_01,   (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)WCHIME_VOL_REVERSE_IN_MID,                          (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_SEAREM_FMV */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_SEAREM_LV1_24_02,    (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_SEAREM_FMV_MID,                          (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_SEAREM_LV2 */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_SEAREM_LV2_24_02,    (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_SEAREM_LV2_MID,                          (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_SEAREM_LV1 */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_DAN_MET_LBZ_SEAREM_LV1_24_02,    (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_SEAREM_LV1_MID,                          (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_CONT                                                                                                                                                                                                                                                                    /* TYPE    */
        },
        {   /* SOUND_AT_SEAREM_SI */
            {(U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_TAN_MET_LBZ_SEAREM_LV1_24_02,    (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)WCHIME_VOL_SEAREM_SI_MID,                           (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_EVENT                                                                                                                                                                                                                                                                   /* TYPE    */
        },
        {   /* SOUND_AT_MET_CBZ_BASE_NOTICE1 */
            {(U2)CRI_CUESHEET_0_LEX_TAN_MET_CBZ_BASE_NOTICE1_0_01,   (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)WCHIME_VOL_BASE_NOTICE1_MID,                        (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_EVENT                                                                                                                                                                                                                                                                   /* TYPE    */
        },
        {   /* SOUND_AT_MMTURHAZ_STA */
            {(U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_TAN_MET_LBZ_MMTURHAZ_FLA1_24_02, (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)WCHIME_VOL_TURHAZ_STA_MCSTM_HSPD,                   (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_EVENT                                                                                                                                                                                                                                                                   /* TYPE    */
        },
        {   /* SOUND_AT_MMTURHAZ_FIN */
            {(U2)U2_MAX,                                             (U2)CRI_CUESHEET_0_LEX_TAN_MET_LBZ_MMTURHAZ_FLA2_24_02, (U2)U2_MAX,                                             (U2)U2_MAX,                                             (U2)U2_MAX                                            }, /* CUE_ID  */
            {(U1)U1_MAX,                                             (U1)WCHIME_VOL_TURHAZ_FIN_MCSTM_HSPD,                   (U1)U1_MAX,                                             (U1)U1_MAX,                                             (U1)U1_MAX                                            }, /* CUE_VOL */
            (U1)SOUND_OW_TYPE_EVENT                                                                                                                                                                                                                                                                   /* TYPE    */
        }
    };

    const ST_SOUND_OW_BUZ_INFO * stp_t_OW_BUZ_INFO;
    ST_SOUND_OW_CTRL           * stp_t_ow_ctrl;
    U2                           u2_t_cuemax;
    U2                           u2_t_cueid;
    U1                           u1_t_ow_sts;
    U1                           u1_t_brand;

    u1_t_ow_sts          = (U1)SOUND_OW_CTRL_INA;
    u4_s_sound_ow_unlock = (U4)0U;
    u1_t_brand           = u1_g_VardefOmusMCUID0024();

    if(u1_a_GRP_NO < (U1)SOUND_GROUP_NUM){
        stp_t_ow_ctrl        = &st_sp_sound_ow_ctrl[u1_a_GRP_NO];
        if(u1_s_sound_ow_reqid < (U1)SOUND_OW_WAV_IDX_NUM){
            if(u1_t_brand == (U1)CALIB_MCUID0024_LEXUS){
                stp_t_OW_BUZ_INFO = &st_sp_SOUND_OW_BUZ_INFO_LEX[u1_s_sound_ow_reqid];
                u2_t_cuemax = (U2)CRI_CUESHEET_0_LEX_CUENUM_ADX;
            }
            else{
                stp_t_OW_BUZ_INFO = &st_sp_SOUND_OW_BUZ_INFO_TYT[u1_s_sound_ow_reqid];
                u2_t_cuemax = (U2)CRI_CUESHEET_0_TYT_CUENUM_ADX;
            }
            u2_t_cueid        = stp_t_OW_BUZ_INFO->u2_cueid[u1_a_GRP_NO];
            if(u2_t_cueid < u2_t_cuemax){
                u1_t_ow_sts = u1_s_SoundCriMgrOwStsChk(u1_a_CYCLCHK, stp_t_OW_BUZ_INFO->u1_type, stp_t_ow_ctrl);
                if((u1_t_ow_sts == (U1)SOUND_OW_CTRL_RUN) ||
                (u1_t_ow_sts == (U1)SOUND_OW_CTRL_STA)) {
                    (*u2p_a_cueid)  = u2_t_cueid;
                    (*u1p_a_cuevol) = stp_t_OW_BUZ_INFO->u1_cuevol[u1_a_GRP_NO];
                }
            }
            else{
                /* Set "RUN" since another CH is sounding. */
                u1_t_ow_sts = (U1)SOUND_OW_CTRL_RUN;
            }
        }
        else{
            stp_t_ow_ctrl->u1_ow_sts   = (U1)SOUND_OW_CTRL_INA;
            stp_t_ow_ctrl->u2_ow_tocnt = (U2)U2_MAX;
        }
    }

    return(u1_t_ow_sts);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SoundCriMgrOwStsChk(const U1 u1_a_CYCLCHK, const U1 u1_a_OWTYPE, ST_SOUND_OW_CTRL * stp_a_ow_ctrl)           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SoundCriMgrOwStsChk(const U1 u1_a_CYCLCHK, const U1 u1_a_OWTYPE, ST_SOUND_OW_CTRL * stp_a_ow_ctrl)
{
    U1 u1_t_ow_sts;

    u1_t_ow_sts = (U1)SOUND_OW_CTRL_INA;

    switch(stp_a_ow_ctrl->u1_ow_sts){
        case (U1)SOUND_OW_CTRL_STA:
            /* In case of the first request, set "STA" to start the buzzer. */
            u1_t_ow_sts                = (U1)SOUND_OW_CTRL_STA;

            stp_a_ow_ctrl->u1_ow_sts   = (U1)SOUND_OW_CTRL_RUN;
            stp_a_ow_ctrl->u2_ow_tocnt = (U2)0U;
            break;
        case (U1)SOUND_OW_CTRL_CNT:
            /* In case of the subsequent request, set "RUN" to continue the buzzer. */
            u1_t_ow_sts                = (U1)SOUND_OW_CTRL_RUN;

            stp_a_ow_ctrl->u1_ow_sts   = (U1)SOUND_OW_CTRL_RUN;
            stp_a_ow_ctrl->u2_ow_tocnt = (U2)0U;
            break;
        case (U1)SOUND_OW_CTRL_RUN:
            if(u1_a_OWTYPE == (U1)SOUND_OW_TYPE_CONT){
                stp_a_ow_ctrl->u2_ow_tocnt++;
                if(stp_a_ow_ctrl->u2_ow_tocnt < (U2)SOUND_OW_TIMEOUT){
                    u1_t_ow_sts = (U1)SOUND_OW_CTRL_RUN;
                }
                else{
                    stp_a_ow_ctrl->u2_ow_tocnt = (U2)SOUND_OW_TIMEOUT;
                }
            }
            else{
                if(u1_a_CYCLCHK == (U1)FALSE){
                    u1_t_ow_sts = (U1)SOUND_OW_CTRL_RUN;
                }
            }

            if(u1_t_ow_sts != (U1)SOUND_OW_CTRL_RUN){
                stp_a_ow_ctrl->u1_ow_sts   = (U1)SOUND_OW_CTRL_INA;
                stp_a_ow_ctrl->u2_ow_tocnt = (U2)U2_MAX;

                u1_s_sound_ow_reqid        = (U1)U1_MAX;
            }
            break;
        default:
            stp_a_ow_ctrl->u1_ow_sts   = (U1)SOUND_OW_CTRL_INA;
            stp_a_ow_ctrl->u2_ow_tocnt = (U2)U2_MAX;

            u1_s_sound_ow_reqid        = (U1)U1_MAX;
            break;
    }

    return(u1_t_ow_sts);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SoundCriMgrSetVolume(const U1 u1_a_GRP_NO, const U1 u1_a_REQ_VOL, const U1 u1_a_PLAYNUM)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SoundCriMgrSetVolume(const U1 u1_a_GRP_NO, const U1 u1_a_REQ_VOL, const U1 u1_a_PLAYNUM)
{
    static volatile const U2 u2_s_VOL_MULTI_CH_PLAY_RATE_1 = (U2)SOUND_VOL_MULTI_CH_PLAY_RATE_1;

    static volatile const U2 *const u2p_sp_SOUND_VOL_TYT[SOUND_NUM_VOL_TYT] = {
        &u2_CALIB_MCUID0029_REV_IN_MID,                     /* WCHIME_VOL_REVERSE_IN_MID                                             */
        &u2_CALIB_MCUID0746_REV_IN_MAX,                     /* WCHIME_VOL_REVERSE_IN_MAX                                             */
        &u2_CALIB_MCUID0030_SBELT_FMV_MID,                  /* WCHIME_VOL_SEAREM_FMV_MID                                             */
        &u2_CALIB_MCUID0747_SBELT_FMV_MAX,                  /* WCHIME_VOL_SEAREM_FMV_MAX                                             */
        &u2_CALIB_MCUID0031_SBELT_LV1_MID,                  /* WCHIME_VOL_SEAREM_LV1_MID                                             */
        &u2_CALIB_MCUID0748_SBELT_LV1_MAX,                  /* WCHIME_VOL_SEAREM_LV1_MAX                                             */
        &u2_CALIB_MCUID0032_SBELT_LV2_MID,                  /* WCHIME_VOL_SEAREM_LV2_MID                                             */
        &u2_CALIB_MCUID0749_SBELT_LV2_MAX,                  /* WCHIME_VOL_SEAREM_LV2_MAX                                             */
        &u2_CALIB_MCUID0033_SBELT_SI_MID,                   /* WCHIME_VOL_SEAREM_SI_MID                                              */
        &u2_CALIB_MCUID0750_SBELT_SI_MAX,                   /* WCHIME_VOL_SEAREM_SI_MAX                                              */
        &u2_CALIB_MCUID0067_CSR_FRSD0,                      /* WCHIME_VOL_CSR_FR_SD_0                                                */
        &u2_CALIB_MCUID0068_CSR_FRSD1,                      /* WCHIME_VOL_CSR_FR_SD_1                                                */
        &u2_CALIB_MCUID0069_CSR_FRSD2,                      /* WCHIME_VOL_CSR_FR_SD_2                                                */
        &u2_CALIB_MCUID0070_CSR_FRSD3,                      /* WCHIME_VOL_CSR_FR_SD_3                                                */
        &u2_CALIB_MCUID0071_CSR_FRSD4,                      /* WCHIME_VOL_CSR_FR_SD_4                                                */
        &u2_CALIB_MCUID0072_CSR_FRSD5,                      /* WCHIME_VOL_CSR_FR_SD_5                                                */
        &u2_CALIB_MCUID0073_CSR_FRSD6,                      /* WCHIME_VOL_CSR_FR_SD_6                                                */
        &u2_CALIB_MCUID0074_CSR_FRSD7,                      /* WCHIME_VOL_CSR_FR_SD_7                                                */
        &u2_CALIB_MCUID0075_CSR_FRMD0,                      /* WCHIME_VOL_CSR_FR_MD_0                                                */
        &u2_CALIB_MCUID0076_CSR_FRMD1,                      /* WCHIME_VOL_CSR_FR_MD_1                                                */
        &u2_CALIB_MCUID0077_CSR_FRMD2,                      /* WCHIME_VOL_CSR_FR_MD_2                                                */
        &u2_CALIB_MCUID0078_CSR_FRMD3,                      /* WCHIME_VOL_CSR_FR_MD_3                                                */
        &u2_CALIB_MCUID0079_CSR_FRMD4,                      /* WCHIME_VOL_CSR_FR_MD_4                                                */
        &u2_CALIB_MCUID0080_CSR_FRMD5,                      /* WCHIME_VOL_CSR_FR_MD_5                                                */
        &u2_CALIB_MCUID0081_CSR_FRMD6,                      /* WCHIME_VOL_CSR_FR_MD_6                                                */
        &u2_CALIB_MCUID0082_CSR_FRMD7,                      /* WCHIME_VOL_CSR_FR_MD_7                                                */
        &u2_CALIB_MCUID0083_CSR_FRLD0,                      /* WCHIME_VOL_CSR_FR_LD_0                                                */
        &u2_CALIB_MCUID0084_CSR_FRLD1,                      /* WCHIME_VOL_CSR_FR_LD_1                                                */
        &u2_CALIB_MCUID0085_CSR_FRLD2,                      /* WCHIME_VOL_CSR_FR_LD_2                                                */
        &u2_CALIB_MCUID0086_CSR_FRLD3,                      /* WCHIME_VOL_CSR_FR_LD_3                                                */
        &u2_CALIB_MCUID0087_CSR_FRLD4,                      /* WCHIME_VOL_CSR_FR_LD_4                                                */
        &u2_CALIB_MCUID0088_CSR_FRLD5,                      /* WCHIME_VOL_CSR_FR_LD_5                                                */
        &u2_CALIB_MCUID0089_CSR_FRLD6,                      /* WCHIME_VOL_CSR_FR_LD_6                                                */
        &u2_CALIB_MCUID0090_CSR_FRLD7,                      /* WCHIME_VOL_CSR_FR_LD_7                                                */
        &u2_CALIB_MCUID0091_CSR_FRFD0,                      /* WCHIME_VOL_CSR_FR_FD_0                                                */
        &u2_CALIB_MCUID0092_CSR_FRFD1,                      /* WCHIME_VOL_CSR_FR_FD_1                                                */
        &u2_CALIB_MCUID0093_CSR_FRFD2,                      /* WCHIME_VOL_CSR_FR_FD_2                                                */
        &u2_CALIB_MCUID0094_CSR_FRFD3,                      /* WCHIME_VOL_CSR_FR_FD_3                                                */
        &u2_CALIB_MCUID0095_CSR_FRFD4,                      /* WCHIME_VOL_CSR_FR_FD_4                                                */
        &u2_CALIB_MCUID0096_CSR_FRFD5,                      /* WCHIME_VOL_CSR_FR_FD_5                                                */
        &u2_CALIB_MCUID0097_CSR_FRFD6,                      /* WCHIME_VOL_CSR_FR_FD_6                                                */
        &u2_CALIB_MCUID0098_CSR_FRFD7,                      /* WCHIME_VOL_CSR_FR_FD_7                                                */
        &u2_CALIB_MCUID0099_CSR_RRSD0,                      /* WCHIME_VOL_CSR_RR_SD_0                                                */
        &u2_CALIB_MCUID0100_CSR_RRSD1,                      /* WCHIME_VOL_CSR_RR_SD_1                                                */
        &u2_CALIB_MCUID0101_CSR_RRSD2,                      /* WCHIME_VOL_CSR_RR_SD_2                                                */
        &u2_CALIB_MCUID0102_CSR_RRSD3,                      /* WCHIME_VOL_CSR_RR_SD_3                                                */
        &u2_CALIB_MCUID0103_CSR_RRSD4,                      /* WCHIME_VOL_CSR_RR_SD_4                                                */
        &u2_CALIB_MCUID0104_CSR_RRSD5,                      /* WCHIME_VOL_CSR_RR_SD_5                                                */
        &u2_CALIB_MCUID0105_CSR_RRSD6,                      /* WCHIME_VOL_CSR_RR_SD_6                                                */
        &u2_CALIB_MCUID0106_CSR_RRSD7,                      /* WCHIME_VOL_CSR_RR_SD_7                                                */
        &u2_CALIB_MCUID0107_CSR_RRMD0,                      /* WCHIME_VOL_CSR_RR_MD_0                                                */
        &u2_CALIB_MCUID0108_CSR_RRMD1,                      /* WCHIME_VOL_CSR_RR_MD_1                                                */
        &u2_CALIB_MCUID0109_CSR_RRMD2,                      /* WCHIME_VOL_CSR_RR_MD_2                                                */
        &u2_CALIB_MCUID0110_CSR_RRMD3,                      /* WCHIME_VOL_CSR_RR_MD_3                                                */
        &u2_CALIB_MCUID0111_CSR_RRMD4,                      /* WCHIME_VOL_CSR_RR_MD_4                                                */
        &u2_CALIB_MCUID0112_CSR_RRMD5,                      /* WCHIME_VOL_CSR_RR_MD_5                                                */
        &u2_CALIB_MCUID0113_CSR_RRMD6,                      /* WCHIME_VOL_CSR_RR_MD_6                                                */
        &u2_CALIB_MCUID0114_CSR_RRMD7,                      /* WCHIME_VOL_CSR_RR_MD_7                                                */
        &u2_CALIB_MCUID0115_CSR_RRLD0,                      /* WCHIME_VOL_CSR_RR_LD_0                                                */
        &u2_CALIB_MCUID0116_CSR_RRLD1,                      /* WCHIME_VOL_CSR_RR_LD_1                                                */
        &u2_CALIB_MCUID0117_CSR_RRLD2,                      /* WCHIME_VOL_CSR_RR_LD_2                                                */
        &u2_CALIB_MCUID0118_CSR_RRLD3,                      /* WCHIME_VOL_CSR_RR_LD_3                                                */
        &u2_CALIB_MCUID0119_CSR_RRLD4,                      /* WCHIME_VOL_CSR_RR_LD_4                                                */
        &u2_CALIB_MCUID0120_CSR_RRLD5,                      /* WCHIME_VOL_CSR_RR_LD_5                                                */
        &u2_CALIB_MCUID0121_CSR_RRLD6,                      /* WCHIME_VOL_CSR_RR_LD_6                                                */
        &u2_CALIB_MCUID0122_CSR_RRLD7,                      /* WCHIME_VOL_CSR_RR_LD_7                                                */
        &u2_CALIB_MCUID0123_CSR_RRFD0,                      /* WCHIME_VOL_CSR_RR_FD_0                                                */
        &u2_CALIB_MCUID0124_CSR_RRFD1,                      /* WCHIME_VOL_CSR_RR_FD_1                                                */
        &u2_CALIB_MCUID0125_CSR_RRFD2,                      /* WCHIME_VOL_CSR_RR_FD_2                                                */
        &u2_CALIB_MCUID0126_CSR_RRFD3,                      /* WCHIME_VOL_CSR_RR_FD_3                                                */
        &u2_CALIB_MCUID0127_CSR_RRFD4,                      /* WCHIME_VOL_CSR_RR_FD_4                                                */
        &u2_CALIB_MCUID0128_CSR_RRFD5,                      /* WCHIME_VOL_CSR_RR_FD_5                                                */
        &u2_CALIB_MCUID0129_CSR_RRFD6,                      /* WCHIME_VOL_CSR_RR_FD_6                                                */
        &u2_CALIB_MCUID0130_CSR_RRFD7,                      /* WCHIME_VOL_CSR_RR_FD_7                                                */
        &u2_CALIB_MCUID0131_CSR_FRRRSD0,                    /* WCHIME_VOL_CSR_FRRR_SD_0                                              */
        &u2_CALIB_MCUID0132_CSR_FRRRSD1,                    /* WCHIME_VOL_CSR_FRRR_SD_1                                              */
        &u2_CALIB_MCUID0133_CSR_FRRRSD2,                    /* WCHIME_VOL_CSR_FRRR_SD_2                                              */
        &u2_CALIB_MCUID0134_CSR_FRRRSD3,                    /* WCHIME_VOL_CSR_FRRR_SD_3                                              */
        &u2_CALIB_MCUID0135_CSR_FRRRSD4,                    /* WCHIME_VOL_CSR_FRRR_SD_4                                              */
        &u2_CALIB_MCUID0136_CSR_FRRRSD5,                    /* WCHIME_VOL_CSR_FRRR_SD_5                                              */
        &u2_CALIB_MCUID0137_CSR_FRRRSD6,                    /* WCHIME_VOL_CSR_FRRR_SD_6                                              */
        &u2_CALIB_MCUID0138_CSR_FRRRSD7,                    /* WCHIME_VOL_CSR_FRRR_SD_7                                              */
        &u2_CALIB_MCUID0139_CSR_FRRRMD0,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_0                                           */
        &u2_CALIB_MCUID0140_CSR_FRRRMD1,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_1                                           */
        &u2_CALIB_MCUID0141_CSR_FRRRMD2,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_2                                           */
        &u2_CALIB_MCUID0142_CSR_FRRRMD3,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_3                                           */
        &u2_CALIB_MCUID0143_CSR_FRRRMD4,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_4                                           */
        &u2_CALIB_MCUID0144_CSR_FRRRMD5,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_5                                           */
        &u2_CALIB_MCUID0145_CSR_FRRRMD6,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_6                                           */
        &u2_CALIB_MCUID0146_CSR_FRRRMD7,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_7                                           */
        &u2_CALIB_MCUID0139_CSR_FRRRMD0,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_0                                           */
        &u2_CALIB_MCUID0140_CSR_FRRRMD1,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_1                                           */
        &u2_CALIB_MCUID0141_CSR_FRRRMD2,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_2                                           */
        &u2_CALIB_MCUID0142_CSR_FRRRMD3,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_3                                           */
        &u2_CALIB_MCUID0143_CSR_FRRRMD4,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_4                                           */
        &u2_CALIB_MCUID0144_CSR_FRRRMD5,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_5                                           */
        &u2_CALIB_MCUID0145_CSR_FRRRMD6,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_6                                           */
        &u2_CALIB_MCUID0146_CSR_FRRRMD7,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_7                                           */
        &u2_CALIB_MCUID0155_CSR_FRRRLD0,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_0                                           */
        &u2_CALIB_MCUID0156_CSR_FRRRLD1,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_1                                           */
        &u2_CALIB_MCUID0157_CSR_FRRRLD2,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_2                                           */
        &u2_CALIB_MCUID0158_CSR_FRRRLD3,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_3                                           */
        &u2_CALIB_MCUID0159_CSR_FRRRLD4,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_4                                           */
        &u2_CALIB_MCUID0160_CSR_FRRRLD5,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_5                                           */
        &u2_CALIB_MCUID0161_CSR_FRRRLD6,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_6                                           */
        &u2_CALIB_MCUID0162_CSR_FRRRLD7,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_7                                           */
        &u2_CALIB_MCUID0155_CSR_FRRRLD0,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_0                                           */
        &u2_CALIB_MCUID0156_CSR_FRRRLD1,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_1                                           */
        &u2_CALIB_MCUID0157_CSR_FRRRLD2,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_2                                           */
        &u2_CALIB_MCUID0158_CSR_FRRRLD3,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_3                                           */
        &u2_CALIB_MCUID0159_CSR_FRRRLD4,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_4                                           */
        &u2_CALIB_MCUID0160_CSR_FRRRLD5,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_5                                           */
        &u2_CALIB_MCUID0161_CSR_FRRRLD6,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_6                                           */
        &u2_CALIB_MCUID0162_CSR_FRRRLD7,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_7                                           */
        &u2_CALIB_MCUID0171_CSR_FRRRFD0,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_0                                           */
        &u2_CALIB_MCUID0172_CSR_FRRRFD1,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_1                                           */
        &u2_CALIB_MCUID0173_CSR_FRRRFD2,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_2                                           */
        &u2_CALIB_MCUID0174_CSR_FRRRFD3,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_3                                           */
        &u2_CALIB_MCUID0175_CSR_FRRRFD4,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_4                                           */
        &u2_CALIB_MCUID0176_CSR_FRRRFD5,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_5                                           */
        &u2_CALIB_MCUID0177_CSR_FRRRFD6,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_6                                           */
        &u2_CALIB_MCUID0178_CSR_FRRRFD7,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_7                                           */
        &u2_CALIB_MCUID0171_CSR_FRRRFD0,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_0                                           */
        &u2_CALIB_MCUID0172_CSR_FRRRFD1,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_1                                           */
        &u2_CALIB_MCUID0173_CSR_FRRRFD2,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_2                                           */
        &u2_CALIB_MCUID0174_CSR_FRRRFD3,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_3                                           */
        &u2_CALIB_MCUID0175_CSR_FRRRFD4,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_4                                           */
        &u2_CALIB_MCUID0176_CSR_FRRRFD5,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_5                                           */
        &u2_CALIB_MCUID0177_CSR_FRRRFD6,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_6                                           */
        &u2_CALIB_MCUID0178_CSR_FRRRFD7,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_7                                           */
        &u2_CALIB_MCUID0187_FLSTA_LOLO,                     /* WCHIME_VOL_TURHAZ_STA_LCSTM_LSPD                                      */
        &u2_CALIB_MCUID0188_FLSTA_LOMI,                     /* WCHIME_VOL_TURHAZ_STA_LCSTM_MSPD                                      */
        &u2_CALIB_MCUID0189_FLSTA_LOHI,                     /* WCHIME_VOL_TURHAZ_STA_LCSTM_HSPD                                      */
        &u2_CALIB_MCUID0190_FLSTA_MILO,                     /* WCHIME_VOL_TURHAZ_STA_MCSTM_LSPD                                      */
        &u2_CALIB_MCUID0191_FLSTA_MIMI,                     /* WCHIME_VOL_TURHAZ_STA_MCSTM_MSPD                                      */
        &u2_CALIB_MCUID0192_FLSTA_MIHI,                     /* WCHIME_VOL_TURHAZ_STA_MCSTM_HSPD                                      */
        &u2_CALIB_MCUID0193_FLSTA_HILO,                     /* WCHIME_VOL_TURHAZ_STA_HCSTM_LSPD                                      */
        &u2_CALIB_MCUID0194_FLSTA_HIMI,                     /* WCHIME_VOL_TURHAZ_STA_HCSTM_MSPD                                      */
        &u2_CALIB_MCUID0195_FLSTA_HIHI,                     /* WCHIME_VOL_TURHAZ_STA_HCSTM_HSPD                                      */
        &u2_CALIB_MCUID0196_FLFIN_LOLO,                     /* WCHIME_VOL_TURHAZ_FIN_LCSTM_LSPD                                      */
        &u2_CALIB_MCUID0197_FLFIN_LOMI,                     /* WCHIME_VOL_TURHAZ_FIN_LCSTM_MSPD                                      */
        &u2_CALIB_MCUID0198_FLFIN_LOHI,                     /* WCHIME_VOL_TURHAZ_FIN_LCSTM_HSPD                                      */
        &u2_CALIB_MCUID0199_FLFIN_MILO,                     /* WCHIME_VOL_TURHAZ_FIN_MCSTM_LSPD                                      */
        &u2_CALIB_MCUID0200_FLFIN_MIMI,                     /* WCHIME_VOL_TURHAZ_FIN_MCSTM_MSPD                                      */
        &u2_CALIB_MCUID0201_FLFIN_MIHI,                     /* WCHIME_VOL_TURHAZ_FIN_MCSTM_HSPD                                      */
        &u2_CALIB_MCUID0202_FLFIN_HILO,                     /* WCHIME_VOL_TURHAZ_FIN_HCSTM_LSPD                                      */
        &u2_CALIB_MCUID0203_FLFIN_HIMI,                     /* WCHIME_VOL_TURHAZ_FIN_HCSTM_MSPD                                      */
        &u2_CALIB_MCUID0204_FLFIN_HIHI,                     /* WCHIME_VOL_TURHAZ_FIN_HCSTM_HSPD                                      */
        &u2_CALIB_MCUID0915_CSR_RCTA_0,                     /* WCHIME_VOL_CSR_RCTA_0                                                 */
        &u2_CALIB_MCUID0916_CSR_RCTA_1,                     /* WCHIME_VOL_CSR_RCTA_1                                                 */
        &u2_CALIB_MCUID0917_CSR_RCTA_2,                     /* WCHIME_VOL_CSR_RCTA_2                                                 */
        &u2_CALIB_MCUID0918_CSR_RCTA_3,                     /* WCHIME_VOL_CSR_RCTA_3                                                 */
        &u2_CALIB_MCUID0919_CSR_RCTA_4,                     /* WCHIME_VOL_CSR_RCTA_4                                                 */
        &u2_CALIB_MCUID0920_CSR_RCTA_5,                     /* WCHIME_VOL_CSR_RCTA_5                                                 */
        &u2_CALIB_MCUID0921_CSR_RCTA_6,                     /* WCHIME_VOL_CSR_RCTA_6                                                 */
        &u2_CALIB_MCUID0922_CSR_RCTA_7,                     /* WCHIME_VOL_CSR_RCTA_7                                                 */
        &u2_CALIB_MCUID3002_ANUNC_MID,                      /* WCHIME_VOL_BASE_NOTICE1_MID                                           */
        &u2_CALIB_MCUID3011_ANUNC_MAX,                      /* WCHIME_VOL_BASE_NOTICE1_MAX                                           */
        &u2_CALIB_MCUID3003_ANUNC_SP_MID,                   /* WCHIME_VOL_BASE_NOTICE2_MID                                           */
        &u2_CALIB_MCUID3012_ANUNC_SP_MAX,                   /* WCHIME_VOL_BASE_NOTICE2_MAX                                           */
        &u2_CALIB_MCUID3004_RECEP_MID,                      /* WCHIME_VOL_BASE_ACCEPT_MID                                            */
        &u2_CALIB_MCUID3013_RECEP_MAX,                      /* WCHIME_VOL_BASE_ACCEPT_MAX                                            */
        &u2_CALIB_MCUID3005_REJECT_MID,                     /* WCHIME_VOL_BASE_REJECT_MID                                            */
        &u2_CALIB_MCUID3014_REJECT_MAX,                     /* WCHIME_VOL_BASE_REJECT_MAX                                            */
        &u2_CALIB_MCUID3006_URGEN_MIN_MID,                  /* WCHIME_VOL_BASE_INTWARNL_MID                                          */
        &u2_CALIB_MCUID3015_URGEN_MIN_MAX,                  /* WCHIME_VOL_BASE_INTWARNL_MAX                                          */
        &u2_CALIB_MCUID3007_URGEN_MID_MID,                  /* WCHIME_VOL_BASE_INTWARNM_MID                                          */
        &u2_CALIB_MCUID3016_URGEN_MID_MAX,                  /* WCHIME_VOL_BASE_INTWARNM_MAX                                          */
        &u2_CALIB_MCUID3008_URGEN_MAX_MID,                  /* WCHIME_VOL_BASE_INTWARNH_MID                                          */
        &u2_CALIB_MCUID3017_URGEN_MAX_MAX,                  /* WCHIME_VOL_BASE_INTWARNH_MAX                                          */
        &u2_CALIB_MCUID3009_CONTIN_MID,                     /* WCHIME_VOL_BASE_CONTWARN_MID                                          */
        &u2_CALIB_MCUID3018_CONTIN_MAX,                     /* WCHIME_VOL_BASE_CONTWARN_MAX                                          */
        &u2_CALIB_MCUID3010_PREDOT_MID,                     /* WCHIME_VOL_AD_DOT_MID                                                 */
        &u2_CALIB_MCUID3019_PREDOT_MAX,                     /* WCHIME_VOL_AD_DOT_MAX                                                 */
        &u2_CALIB_MCUID3021_SEA_MID,                        /* WCHIME_VOL_SEA_REJECT_MID                                             */
        &u2_CALIB_MCUID3022_SEA_MAX,                        /* WCHIME_VOL_SEA_REJECT_MAX                                             */
        &u2_CALIB_MCUID3023_PCS_MID,                        /* WCHIME_VOL_PCS_SEA_INTWARNH_MID                                       */
        &u2_CALIB_MCUID3024_PCS_MAX                         /* WCHIME_VOL_PCS_SEA_INTWARNH_MAX                                       */
    };
    static volatile const U2 *const u2p_sp_SOUND_VOL_LEX[SOUND_NUM_VOL_LEX] = {
        &u2_CALIB_MCUID0029_REV_IN_MID,                     /* WCHIME_VOL_REVERSE_IN_MID                                             */
        &u2_CALIB_MCUID0746_REV_IN_MAX,                     /* WCHIME_VOL_REVERSE_IN_MAX                                             */
        &u2_CALIB_MCUID0030_SBELT_FMV_MID,                  /* WCHIME_VOL_SEAREM_FMV_MID                                             */
        &u2_CALIB_MCUID0747_SBELT_FMV_MAX,                  /* WCHIME_VOL_SEAREM_FMV_MAX                                             */
        &u2_CALIB_MCUID0031_SBELT_LV1_MID,                  /* WCHIME_VOL_SEAREM_LV1_MID                                             */
        &u2_CALIB_MCUID0748_SBELT_LV1_MAX,                  /* WCHIME_VOL_SEAREM_LV1_MAX                                             */
        &u2_CALIB_MCUID0032_SBELT_LV2_MID,                  /* WCHIME_VOL_SEAREM_LV2_MID                                             */
        &u2_CALIB_MCUID0749_SBELT_LV2_MAX,                  /* WCHIME_VOL_SEAREM_LV2_MAX                                             */
        &u2_CALIB_MCUID0033_SBELT_SI_MID,                   /* WCHIME_VOL_SEAREM_SI_MID                                              */
        &u2_CALIB_MCUID0750_SBELT_SI_MAX,                   /* WCHIME_VOL_SEAREM_SI_MAX                                              */
        &u2_CALIB_MCUID0067_CSR_FRSD0,                      /* WCHIME_VOL_CSR_FR_SD_0                                                */
        &u2_CALIB_MCUID0068_CSR_FRSD1,                      /* WCHIME_VOL_CSR_FR_SD_1                                                */
        &u2_CALIB_MCUID0069_CSR_FRSD2,                      /* WCHIME_VOL_CSR_FR_SD_2                                                */
        &u2_CALIB_MCUID0070_CSR_FRSD3,                      /* WCHIME_VOL_CSR_FR_SD_3                                                */
        &u2_CALIB_MCUID0071_CSR_FRSD4,                      /* WCHIME_VOL_CSR_FR_SD_4                                                */
        &u2_CALIB_MCUID0072_CSR_FRSD5,                      /* WCHIME_VOL_CSR_FR_SD_5                                                */
        &u2_CALIB_MCUID0073_CSR_FRSD6,                      /* WCHIME_VOL_CSR_FR_SD_6                                                */
        &u2_CALIB_MCUID0074_CSR_FRSD7,                      /* WCHIME_VOL_CSR_FR_SD_7                                                */
        &u2_CALIB_MCUID0075_CSR_FRMD0,                      /* WCHIME_VOL_CSR_FR_MD_0                                                */
        &u2_CALIB_MCUID0076_CSR_FRMD1,                      /* WCHIME_VOL_CSR_FR_MD_1                                                */
        &u2_CALIB_MCUID0077_CSR_FRMD2,                      /* WCHIME_VOL_CSR_FR_MD_2                                                */
        &u2_CALIB_MCUID0078_CSR_FRMD3,                      /* WCHIME_VOL_CSR_FR_MD_3                                                */
        &u2_CALIB_MCUID0079_CSR_FRMD4,                      /* WCHIME_VOL_CSR_FR_MD_4                                                */
        &u2_CALIB_MCUID0080_CSR_FRMD5,                      /* WCHIME_VOL_CSR_FR_MD_5                                                */
        &u2_CALIB_MCUID0081_CSR_FRMD6,                      /* WCHIME_VOL_CSR_FR_MD_6                                                */
        &u2_CALIB_MCUID0082_CSR_FRMD7,                      /* WCHIME_VOL_CSR_FR_MD_7                                                */
        &u2_CALIB_MCUID0083_CSR_FRLD0,                      /* WCHIME_VOL_CSR_FR_LD_0                                                */
        &u2_CALIB_MCUID0084_CSR_FRLD1,                      /* WCHIME_VOL_CSR_FR_LD_1                                                */
        &u2_CALIB_MCUID0085_CSR_FRLD2,                      /* WCHIME_VOL_CSR_FR_LD_2                                                */
        &u2_CALIB_MCUID0086_CSR_FRLD3,                      /* WCHIME_VOL_CSR_FR_LD_3                                                */
        &u2_CALIB_MCUID0087_CSR_FRLD4,                      /* WCHIME_VOL_CSR_FR_LD_4                                                */
        &u2_CALIB_MCUID0088_CSR_FRLD5,                      /* WCHIME_VOL_CSR_FR_LD_5                                                */
        &u2_CALIB_MCUID0089_CSR_FRLD6,                      /* WCHIME_VOL_CSR_FR_LD_6                                                */
        &u2_CALIB_MCUID0090_CSR_FRLD7,                      /* WCHIME_VOL_CSR_FR_LD_7                                                */
        &u2_CALIB_MCUID0091_CSR_FRFD0,                      /* WCHIME_VOL_CSR_FR_FD_0                                                */
        &u2_CALIB_MCUID0092_CSR_FRFD1,                      /* WCHIME_VOL_CSR_FR_FD_1                                                */
        &u2_CALIB_MCUID0093_CSR_FRFD2,                      /* WCHIME_VOL_CSR_FR_FD_2                                                */
        &u2_CALIB_MCUID0094_CSR_FRFD3,                      /* WCHIME_VOL_CSR_FR_FD_3                                                */
        &u2_CALIB_MCUID0095_CSR_FRFD4,                      /* WCHIME_VOL_CSR_FR_FD_4                                                */
        &u2_CALIB_MCUID0096_CSR_FRFD5,                      /* WCHIME_VOL_CSR_FR_FD_5                                                */
        &u2_CALIB_MCUID0097_CSR_FRFD6,                      /* WCHIME_VOL_CSR_FR_FD_6                                                */
        &u2_CALIB_MCUID0098_CSR_FRFD7,                      /* WCHIME_VOL_CSR_FR_FD_7                                                */
        &u2_CALIB_MCUID0099_CSR_RRSD0,                      /* WCHIME_VOL_CSR_RR_SD_0                                                */
        &u2_CALIB_MCUID0100_CSR_RRSD1,                      /* WCHIME_VOL_CSR_RR_SD_1                                                */
        &u2_CALIB_MCUID0101_CSR_RRSD2,                      /* WCHIME_VOL_CSR_RR_SD_2                                                */
        &u2_CALIB_MCUID0102_CSR_RRSD3,                      /* WCHIME_VOL_CSR_RR_SD_3                                                */
        &u2_CALIB_MCUID0103_CSR_RRSD4,                      /* WCHIME_VOL_CSR_RR_SD_4                                                */
        &u2_CALIB_MCUID0104_CSR_RRSD5,                      /* WCHIME_VOL_CSR_RR_SD_5                                                */
        &u2_CALIB_MCUID0105_CSR_RRSD6,                      /* WCHIME_VOL_CSR_RR_SD_6                                                */
        &u2_CALIB_MCUID0106_CSR_RRSD7,                      /* WCHIME_VOL_CSR_RR_SD_7                                                */
        &u2_CALIB_MCUID0107_CSR_RRMD0,                      /* WCHIME_VOL_CSR_RR_MD_0                                                */
        &u2_CALIB_MCUID0108_CSR_RRMD1,                      /* WCHIME_VOL_CSR_RR_MD_1                                                */
        &u2_CALIB_MCUID0109_CSR_RRMD2,                      /* WCHIME_VOL_CSR_RR_MD_2                                                */
        &u2_CALIB_MCUID0110_CSR_RRMD3,                      /* WCHIME_VOL_CSR_RR_MD_3                                                */
        &u2_CALIB_MCUID0111_CSR_RRMD4,                      /* WCHIME_VOL_CSR_RR_MD_4                                                */
        &u2_CALIB_MCUID0112_CSR_RRMD5,                      /* WCHIME_VOL_CSR_RR_MD_5                                                */
        &u2_CALIB_MCUID0113_CSR_RRMD6,                      /* WCHIME_VOL_CSR_RR_MD_6                                                */
        &u2_CALIB_MCUID0114_CSR_RRMD7,                      /* WCHIME_VOL_CSR_RR_MD_7                                                */
        &u2_CALIB_MCUID0115_CSR_RRLD0,                      /* WCHIME_VOL_CSR_RR_LD_0                                                */
        &u2_CALIB_MCUID0116_CSR_RRLD1,                      /* WCHIME_VOL_CSR_RR_LD_1                                                */
        &u2_CALIB_MCUID0117_CSR_RRLD2,                      /* WCHIME_VOL_CSR_RR_LD_2                                                */
        &u2_CALIB_MCUID0118_CSR_RRLD3,                      /* WCHIME_VOL_CSR_RR_LD_3                                                */
        &u2_CALIB_MCUID0119_CSR_RRLD4,                      /* WCHIME_VOL_CSR_RR_LD_4                                                */
        &u2_CALIB_MCUID0120_CSR_RRLD5,                      /* WCHIME_VOL_CSR_RR_LD_5                                                */
        &u2_CALIB_MCUID0121_CSR_RRLD6,                      /* WCHIME_VOL_CSR_RR_LD_6                                                */
        &u2_CALIB_MCUID0122_CSR_RRLD7,                      /* WCHIME_VOL_CSR_RR_LD_7                                                */
        &u2_CALIB_MCUID0123_CSR_RRFD0,                      /* WCHIME_VOL_CSR_RR_FD_0                                                */
        &u2_CALIB_MCUID0124_CSR_RRFD1,                      /* WCHIME_VOL_CSR_RR_FD_1                                                */
        &u2_CALIB_MCUID0125_CSR_RRFD2,                      /* WCHIME_VOL_CSR_RR_FD_2                                                */
        &u2_CALIB_MCUID0126_CSR_RRFD3,                      /* WCHIME_VOL_CSR_RR_FD_3                                                */
        &u2_CALIB_MCUID0127_CSR_RRFD4,                      /* WCHIME_VOL_CSR_RR_FD_4                                                */
        &u2_CALIB_MCUID0128_CSR_RRFD5,                      /* WCHIME_VOL_CSR_RR_FD_5                                                */
        &u2_CALIB_MCUID0129_CSR_RRFD6,                      /* WCHIME_VOL_CSR_RR_FD_6                                                */
        &u2_CALIB_MCUID0130_CSR_RRFD7,                      /* WCHIME_VOL_CSR_RR_FD_7                                                */
        &u2_CALIB_MCUID0131_CSR_FRRRSD0,                    /* WCHIME_VOL_CSR_FRRR_SD_0                                              */
        &u2_CALIB_MCUID0132_CSR_FRRRSD1,                    /* WCHIME_VOL_CSR_FRRR_SD_1                                              */
        &u2_CALIB_MCUID0133_CSR_FRRRSD2,                    /* WCHIME_VOL_CSR_FRRR_SD_2                                              */
        &u2_CALIB_MCUID0134_CSR_FRRRSD3,                    /* WCHIME_VOL_CSR_FRRR_SD_3                                              */
        &u2_CALIB_MCUID0135_CSR_FRRRSD4,                    /* WCHIME_VOL_CSR_FRRR_SD_4                                              */
        &u2_CALIB_MCUID0136_CSR_FRRRSD5,                    /* WCHIME_VOL_CSR_FRRR_SD_5                                              */
        &u2_CALIB_MCUID0137_CSR_FRRRSD6,                    /* WCHIME_VOL_CSR_FRRR_SD_6                                              */
        &u2_CALIB_MCUID0138_CSR_FRRRSD7,                    /* WCHIME_VOL_CSR_FRRR_SD_7                                              */
        &u2_CALIB_MCUID0139_CSR_FRRRMD0,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_0                                           */
        &u2_CALIB_MCUID0140_CSR_FRRRMD1,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_1                                           */
        &u2_CALIB_MCUID0141_CSR_FRRRMD2,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_2                                           */
        &u2_CALIB_MCUID0142_CSR_FRRRMD3,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_3                                           */
        &u2_CALIB_MCUID0143_CSR_FRRRMD4,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_4                                           */
        &u2_CALIB_MCUID0144_CSR_FRRRMD5,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_5                                           */
        &u2_CALIB_MCUID0145_CSR_FRRRMD6,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_6                                           */
        &u2_CALIB_MCUID0146_CSR_FRRRMD7,                    /* WCHIME_VOL_CSR_FRRR_MD_FR_7                                           */
        &u2_CALIB_MCUID0139_CSR_FRRRMD0,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_0                                           */
        &u2_CALIB_MCUID0140_CSR_FRRRMD1,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_1                                           */
        &u2_CALIB_MCUID0141_CSR_FRRRMD2,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_2                                           */
        &u2_CALIB_MCUID0142_CSR_FRRRMD3,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_3                                           */
        &u2_CALIB_MCUID0143_CSR_FRRRMD4,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_4                                           */
        &u2_CALIB_MCUID0144_CSR_FRRRMD5,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_5                                           */
        &u2_CALIB_MCUID0145_CSR_FRRRMD6,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_6                                           */
        &u2_CALIB_MCUID0146_CSR_FRRRMD7,                    /* WCHIME_VOL_CSR_FRRR_MD_RR_7                                           */
        &u2_CALIB_MCUID0155_CSR_FRRRLD0,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_0                                           */
        &u2_CALIB_MCUID0156_CSR_FRRRLD1,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_1                                           */
        &u2_CALIB_MCUID0157_CSR_FRRRLD2,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_2                                           */
        &u2_CALIB_MCUID0158_CSR_FRRRLD3,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_3                                           */
        &u2_CALIB_MCUID0159_CSR_FRRRLD4,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_4                                           */
        &u2_CALIB_MCUID0160_CSR_FRRRLD5,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_5                                           */
        &u2_CALIB_MCUID0161_CSR_FRRRLD6,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_6                                           */
        &u2_CALIB_MCUID0162_CSR_FRRRLD7,                    /* WCHIME_VOL_CSR_FRRR_LD_FR_7                                           */
        &u2_CALIB_MCUID0155_CSR_FRRRLD0,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_0                                           */
        &u2_CALIB_MCUID0156_CSR_FRRRLD1,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_1                                           */
        &u2_CALIB_MCUID0157_CSR_FRRRLD2,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_2                                           */
        &u2_CALIB_MCUID0158_CSR_FRRRLD3,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_3                                           */
        &u2_CALIB_MCUID0159_CSR_FRRRLD4,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_4                                           */
        &u2_CALIB_MCUID0160_CSR_FRRRLD5,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_5                                           */
        &u2_CALIB_MCUID0161_CSR_FRRRLD6,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_6                                           */
        &u2_CALIB_MCUID0162_CSR_FRRRLD7,                    /* WCHIME_VOL_CSR_FRRR_LD_RR_7                                           */
        &u2_CALIB_MCUID0171_CSR_FRRRFD0,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_0                                           */
        &u2_CALIB_MCUID0172_CSR_FRRRFD1,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_1                                           */
        &u2_CALIB_MCUID0173_CSR_FRRRFD2,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_2                                           */
        &u2_CALIB_MCUID0174_CSR_FRRRFD3,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_3                                           */
        &u2_CALIB_MCUID0175_CSR_FRRRFD4,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_4                                           */
        &u2_CALIB_MCUID0176_CSR_FRRRFD5,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_5                                           */
        &u2_CALIB_MCUID0177_CSR_FRRRFD6,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_6                                           */
        &u2_CALIB_MCUID0178_CSR_FRRRFD7,                    /* WCHIME_VOL_CSR_FRRR_FD_FR_7                                           */
        &u2_CALIB_MCUID0171_CSR_FRRRFD0,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_0                                           */
        &u2_CALIB_MCUID0172_CSR_FRRRFD1,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_1                                           */
        &u2_CALIB_MCUID0173_CSR_FRRRFD2,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_2                                           */
        &u2_CALIB_MCUID0174_CSR_FRRRFD3,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_3                                           */
        &u2_CALIB_MCUID0175_CSR_FRRRFD4,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_4                                           */
        &u2_CALIB_MCUID0176_CSR_FRRRFD5,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_5                                           */
        &u2_CALIB_MCUID0177_CSR_FRRRFD6,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_6                                           */
        &u2_CALIB_MCUID0178_CSR_FRRRFD7,                    /* WCHIME_VOL_CSR_FRRR_FD_RR_7                                           */
        &u2_CALIB_MCUID0187_FLSTA_LOLO,                     /* WCHIME_VOL_TURHAZ_STA_LCSTM_LSPD                                      */
        &u2_CALIB_MCUID0188_FLSTA_LOMI,                     /* WCHIME_VOL_TURHAZ_STA_LCSTM_MSPD                                      */
        &u2_CALIB_MCUID0189_FLSTA_LOHI,                     /* WCHIME_VOL_TURHAZ_STA_LCSTM_HSPD                                      */
        &u2_CALIB_MCUID0190_FLSTA_MILO,                     /* WCHIME_VOL_TURHAZ_STA_MCSTM_LSPD                                      */
        &u2_CALIB_MCUID0191_FLSTA_MIMI,                     /* WCHIME_VOL_TURHAZ_STA_MCSTM_MSPD                                      */
        &u2_CALIB_MCUID0192_FLSTA_MIHI,                     /* WCHIME_VOL_TURHAZ_STA_MCSTM_HSPD                                      */
        &u2_CALIB_MCUID0193_FLSTA_HILO,                     /* WCHIME_VOL_TURHAZ_STA_HCSTM_LSPD                                      */
        &u2_CALIB_MCUID0194_FLSTA_HIMI,                     /* WCHIME_VOL_TURHAZ_STA_HCSTM_MSPD                                      */
        &u2_CALIB_MCUID0195_FLSTA_HIHI,                     /* WCHIME_VOL_TURHAZ_STA_HCSTM_HSPD                                      */
        &u2_CALIB_MCUID0196_FLFIN_LOLO,                     /* WCHIME_VOL_TURHAZ_FIN_LCSTM_LSPD                                      */
        &u2_CALIB_MCUID0197_FLFIN_LOMI,                     /* WCHIME_VOL_TURHAZ_FIN_LCSTM_MSPD                                      */
        &u2_CALIB_MCUID0198_FLFIN_LOHI,                     /* WCHIME_VOL_TURHAZ_FIN_LCSTM_HSPD                                      */
        &u2_CALIB_MCUID0199_FLFIN_MILO,                     /* WCHIME_VOL_TURHAZ_FIN_MCSTM_LSPD                                      */
        &u2_CALIB_MCUID0200_FLFIN_MIMI,                     /* WCHIME_VOL_TURHAZ_FIN_MCSTM_MSPD                                      */
        &u2_CALIB_MCUID0201_FLFIN_MIHI,                     /* WCHIME_VOL_TURHAZ_FIN_MCSTM_HSPD                                      */
        &u2_CALIB_MCUID0202_FLFIN_HILO,                     /* WCHIME_VOL_TURHAZ_FIN_HCSTM_LSPD                                      */
        &u2_CALIB_MCUID0203_FLFIN_HIMI,                     /* WCHIME_VOL_TURHAZ_FIN_HCSTM_MSPD                                      */
        &u2_CALIB_MCUID0204_FLFIN_HIHI,                     /* WCHIME_VOL_TURHAZ_FIN_HCSTM_HSPD                                      */
        &u2_CALIB_MCUID0915_CSR_RCTA_0,                     /* WCHIME_VOL_CSR_RCTA_0                                                 */
        &u2_CALIB_MCUID0916_CSR_RCTA_1,                     /* WCHIME_VOL_CSR_RCTA_1                                                 */
        &u2_CALIB_MCUID0917_CSR_RCTA_2,                     /* WCHIME_VOL_CSR_RCTA_2                                                 */
        &u2_CALIB_MCUID0918_CSR_RCTA_3,                     /* WCHIME_VOL_CSR_RCTA_3                                                 */
        &u2_CALIB_MCUID0919_CSR_RCTA_4,                     /* WCHIME_VOL_CSR_RCTA_4                                                 */
        &u2_CALIB_MCUID0920_CSR_RCTA_5,                     /* WCHIME_VOL_CSR_RCTA_5                                                 */
        &u2_CALIB_MCUID0921_CSR_RCTA_6,                     /* WCHIME_VOL_CSR_RCTA_6                                                 */
        &u2_CALIB_MCUID0922_CSR_RCTA_7,                     /* WCHIME_VOL_CSR_RCTA_7                                                 */
        &u2_CALIB_MCUID3002_ANUNC_MID,                      /* WCHIME_VOL_BASE_NOTICE1_MID                                           */
        &u2_CALIB_MCUID3011_ANUNC_MAX,                      /* WCHIME_VOL_BASE_NOTICE1_MAX                                           */
        &u2_CALIB_MCUID3003_ANUNC_SP_MID,                   /* WCHIME_VOL_BASE_NOTICE2_MID                                           */
        &u2_CALIB_MCUID3012_ANUNC_SP_MAX,                   /* WCHIME_VOL_BASE_NOTICE2_MAX                                           */
        &u2_CALIB_MCUID3004_RECEP_MID,                      /* WCHIME_VOL_BASE_ACCEPT_MID                                            */
        &u2_CALIB_MCUID3013_RECEP_MAX,                      /* WCHIME_VOL_BASE_ACCEPT_MAX                                            */
        &u2_CALIB_MCUID3005_REJECT_MID,                     /* WCHIME_VOL_BASE_REJECT_MID                                            */
        &u2_CALIB_MCUID3014_REJECT_MAX,                     /* WCHIME_VOL_BASE_REJECT_MAX                                            */
        &u2_CALIB_MCUID3006_URGEN_MIN_MID,                  /* WCHIME_VOL_BASE_INTWARNL_MID                                          */
        &u2_CALIB_MCUID3015_URGEN_MIN_MAX,                  /* WCHIME_VOL_BASE_INTWARNL_MAX                                          */
        &u2_CALIB_MCUID3007_URGEN_MID_MID,                  /* WCHIME_VOL_BASE_INTWARNM_MID                                          */
        &u2_CALIB_MCUID3016_URGEN_MID_MAX,                  /* WCHIME_VOL_BASE_INTWARNM_MAX                                          */
        &u2_CALIB_MCUID3008_URGEN_MAX_MID,                  /* WCHIME_VOL_BASE_INTWARNH_MID                                          */
        &u2_CALIB_MCUID3017_URGEN_MAX_MAX,                  /* WCHIME_VOL_BASE_INTWARNH_MAX                                          */
        &u2_CALIB_MCUID3009_CONTIN_MID,                     /* WCHIME_VOL_BASE_CONTWARN_MID                                          */
        &u2_CALIB_MCUID3018_CONTIN_MAX,                     /* WCHIME_VOL_BASE_CONTWARN_MAX                                          */
        &u2_CALIB_MCUID3010_PREDOT_MID,                     /* WCHIME_VOL_AD_DOT_MID                                                 */
        &u2_CALIB_MCUID3019_PREDOT_MAX,                     /* WCHIME_VOL_AD_DOT_MAX                                                 */
        &u2_CALIB_MCUID3021_SEA_MID,                        /* WCHIME_VOL_SEA_REJECT_MID                                             */
        &u2_CALIB_MCUID3022_SEA_MAX,                        /* WCHIME_VOL_SEA_REJECT_MAX                                             */
        &u2_CALIB_MCUID3023_PCS_MID,                        /* WCHIME_VOL_PCS_SEA_INTWARNH_MID                                       */
        &u2_CALIB_MCUID3024_PCS_MAX                         /* WCHIME_VOL_PCS_SEA_INTWARNH_MAX                                       */
    };

    static volatile const U2 * u2p_sp_MULTI_CH_PLAY_RATE[SOUND_GROUP_NUM] = {
        &u2_s_VOL_MULTI_CH_PLAY_RATE_1,                     /* SOUND_GROUP1                                                          */
        &u2_CALIB_MCUID0205_2CH,                            /* SOUND_GROUP2                                                          */
        &u2_CALIB_MCUID0206_3CH,                            /* SOUND_GROUP3                                                          */
        &u2_CALIB_MCUID0207_4CH,                            /* SOUND_GROUP4                                                          */
        &u2_CALIB_MCUID0208_5CH                             /* SOUND_GROUP5                                                          */
    };

    CriFloat32  f4_t_cuevol;                                                                /* Volume of current sounding cue ID     */
#if 0   /* BEV Rebase provisionally */ /* for xm-authentication */
    U4          u4_t_xmauth;
#endif   /* BEV Rebase provisionally */ /* for xm-authentication */
    U1          u1_t_reqvol;
    U2          u2_t_sound_vol;
    U2          u2_t_multi_ch_play_rate_reqvol;
    U4          u4_t_calc_buf;
    U1          u1_t_brand;

    u1_t_brand    = u1_g_VardefOmusMCUID0024();

#if 0   /* BEV Rebase provisionally */ /* for xm-authentication */
    u4_t_xmauth   = u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2021);
#endif   /* BEV Rebase provisionally */ /* for xm-authentication */
    u4_t_calc_buf = (U4)CALIB_SOUND_PRESS_RATE_MIN;
#if 0   /* BEV Rebase provisionally */ /* for xm-authentication */
    if((u4_t_xmauth & (U4)VDF_DS_2E_XM_MODE) == (U4)0U){
#endif   /* BEV Rebase provisionally */ /* for xm-authentication */
        u1_t_reqvol = u1_a_REQ_VOL;
        if(u1_t_brand == (U1)CALIB_MCUID0024_LEXUS){
            if(u1_a_REQ_VOL >= (U1)SOUND_NUM_VOL_LEX){
               u1_t_reqvol = (U1)SOUND_VOLUMEID_DEFAULT_LEX;
            }
            u2_t_sound_vol = *(u2p_sp_SOUND_VOL_LEX[u1_t_reqvol]);
        }
        else{
            if(u1_a_REQ_VOL >= (U1)SOUND_NUM_VOL_TYT){
               u1_t_reqvol = (U1)SOUND_VOLUMEID_DEFAULT_TYT;
            }
            u2_t_sound_vol = *(u2p_sp_SOUND_VOL_TYT[u1_t_reqvol]);
        }

        u4_t_calc_buf = (U4)u2_t_sound_vol;
        f4_t_cuevol = (CriFloat32)u4_t_calc_buf / (CriFloat32)SOUND_CALIBVOLUME_CHANGE_LSB;
#if 0   /* BEV Rebase provisionally */ /* for xm-authentication */
    }
    else{
        f4_t_cuevol = (CriFloat32)SOUND_CUEVOLUME_MUTE;
    }
#endif   /* BEV Rebase provisionally */ /* for xm-authentication */
    if((u1_a_PLAYNUM > (U1)0U) &&
       (u1_a_PLAYNUM <= (U1)SOUND_GROUP_NUM)){
        u2_t_multi_ch_play_rate_reqvol = *(u2p_sp_MULTI_CH_PLAY_RATE[(u1_a_PLAYNUM - (U1)1U)]);
        u4_t_calc_buf = (U4)u2_t_multi_ch_play_rate_reqvol;
        f4_t_cuevol *= ((CriFloat32)u4_t_calc_buf / (CriFloat32)SOUND_CALIBVOLUME_CHANGE_LSB);
        if(u1_a_GRP_NO < (U1)SOUND_GROUP_NUM){
            /* Set buzzer volume */
            criAtomExPlayer_SetVolume(stp_sp_sound_player_hn_gp[u1_a_GRP_NO], f4_t_cuevol);
        }
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_SoundCriMgrStartByCueId(const U1 u1_a_GRP_NO, const U2 u2_a_CUE_ID)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SoundCriMgrStartByCueId(const U1 u1_a_GRP_NO, const U2 u2_a_CUE_ID)
{
    /* Set playing buzzer */
    criAtomExPlayer_SetCueId(stp_sp_sound_player_hn_gp[u1_a_GRP_NO], stp_s_sound_acb_hn, (CriAtomExCueId)((U4)u2_a_CUE_ID));
    /* Start play */
    (void)criAtomExPlayer_Start(stp_sp_sound_player_hn_gp[u1_a_GRP_NO]);
}

/*===================================================================================================================================*/
/* static  void    vd_s_SoundCriMgrStop(const U1 u1_a_GRP_NO)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SoundCriMgrStop(const U1 u1_a_GRP_NO)
{
    /* Stop play */
    criAtomExPlayer_Stop(stp_sp_sound_player_hn_gp[u1_a_GRP_NO]);
}

#if (SOUND_CRI_DEBUGMODE == TRUE)
/*===================================================================================================================================*/
/* static  void    vd_s_SoundCriMgrErrorCallback(const CriChar8 * s1p_a_ERRID, const CriUint32 u4_a_P1, const CriUint32 u4_a_P2,     */
/*                                               CriUint32 * u4p_a_parray)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SoundCriMgrErrorCallback(const CriChar8 * s1p_a_ERRID, const CriUint32 u4_a_P1, const CriUint32 u4_a_P2, CriUint32 * u4p_a_parray)
{
    const CriChar8 * s1p_t_ERRMSG;                                                                     /* Error message              */

    /* Display an error message string */
    s1p_t_ERRMSG = criErr_ConvertIdToMessage(s1p_a_ERRID, u4_a_P1, u4_a_P2);

    vd_s_SoundCriMgrUnusedParam(u4p_a_parray);                            /* QAC countermeasure */
    vd_s_SoundCriMgrUnusedParam(s1p_t_ERRMSG);                            /* QAC countermeasure */
}
#endif /* SOUND_CRI_DEBUGMODE */

/*===================================================================================================================================*/
/*  static  U1  u1_s_SoundDiagnosis(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static  U1  u1_s_SoundDiagnosis(void)
{
    U1 u1_t_fltb;
    U1 u1_t_ret;
    U1 u1_t_time;

    u1_t_ret = (U1)SOUND_DRV_MODESET;

    u1_t_time  = u1_s_SoundGetActiveTime();

    if (u1_t_time < (U1)SOUND_DRV_MODESET_END_TIM) {
        u1_t_ret = (U1)SOUND_DRV_MODESET;
    }
    else if (u1_t_time == (U1)SOUND_DRV_MODESET_END_TIM) {
        Dio_WriteChannel((U1)DIO_ID_PORT20_CH1, (U1)STD_LOW);
        Dio_WriteChannel((U1)DIO_ID_PORT20_CH2, (U1)STD_LOW);
        u1_t_ret = (U1)SOUND_DRV_ERRCHECK_WAIT;
#if (SOUND_CRI_DEBUGMODE == TRUE)
        vd_s_SoundCriMgrStartup();
#endif /* SOUND_CRI_DEBUGMODE */
    }
    else if (u1_t_time <= (U1)SOUND_DRV_ERRCHECK_WAIT_TIM) {
        u1_t_ret = (U1)SOUND_DRV_ERRCHECK_WAIT;
    }
    else {
        u1_t_fltb = Dio_ReadChannel((U1)DIO_ID_PORT20_CH10);

        if (u1_s_sound_ic_fltb_befor != u1_t_fltb) {
            u1_s_sound_ic_fltb_count = (U1)0U;
        }

        if (u1_s_sound_ic_fltb_count < (U1)U1_MAX) {
            u1_s_sound_ic_fltb_count++;
        }

        if (u1_s_sound_ic_fltb_count >= (U1)SOUND_IC_ERROR_COUNT) {
            if (u1_t_fltb == (U1)STD_LOW) {
                if (u1_s_sound_ic_fltb_initial == (U1)SOUND_DRV_INITIAL) {
                    u1_s_sound_ic_error  = (U1)SOUND_IC_ERROR;
                }
            }
            u1_s_sound_ic_fltb_initial = (U1)SOUND_DRV_INITIAL_END;
        }

        u1_s_sound_ic_fltb_befor = u1_t_fltb;

        u1_t_ret = (U1)SOUND_DRV_ERRCHECK;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_SoundGetActiveTime(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_SoundGetActiveTime(void)
{
    U1 u1_t_chk;
    U4 u4_tp_time_val[SOUND_ACTIVE_TIME_RDN_NUM];
    U4 u4_t_rdnrslt;
    U1 u1_t_initstate;

    u4_tp_time_val[SOUND_ACTIVE_TIME_RDN_1ST] = (U4)u1_s_sound_drv_active_time_val1;
    u4_tp_time_val[SOUND_ACTIVE_TIME_RDN_2ND] = (U4)u1_s_sound_drv_active_time_val2;
    u4_tp_time_val[SOUND_ACTIVE_TIME_RDN_3RD] = (U4)u1_s_sound_drv_active_time_val3;
    u1_t_chk = u1_g_TrplRdndntchk(u4_tp_time_val, &u4_t_rdnrslt);
    if (u1_t_chk == (U1)0U) {
        /* Redundant data is all incorrect. */
        u4_t_rdnrslt = (U4)SOUND_ACTIVE_TIME_DEF;
        u1_t_initstate = u1_s_SoundCriMgr_InitialCheck();
        if (u1_t_initstate == (U1)SOUND_DRV_INITIAL_END) {
            vd_g_SoundCriMgrFinalize();
        }
    }

    if (u4_t_rdnrslt < (U4)U1_MAX) {
        u4_t_rdnrslt++;
    }
    else {
        u4_t_rdnrslt = (U4)U1_MAX;
    }

    u1_s_sound_drv_active_time_val1 = (U1)u4_t_rdnrslt;
    u1_s_sound_drv_active_time_val2 = (U1)u4_t_rdnrslt;
    u1_s_sound_drv_active_time_val3 = (U1)u4_t_rdnrslt;

    return ((U1)u4_t_rdnrslt);
}

/*===================================================================================================================================*/
/*  u1      u1_s_SoundCriMgr_InitialCheck(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_SoundCriMgr_InitialCheck(void)
{
#if (SOUND_CRI_DEBUGMODE != TRUE)
    U1      u1_t_match_count;
    U1      u1_t_ret;

    u1_t_match_count = (U1)0U;

    if (s4_s_initialize_size == (CriSint32)SOUND_CRI_INIT_WORK_SIZE) {
        u1_t_match_count++;
    }

    if (s4_s_acfdata_size == (CriSint32)SOUND_ACFDATA_SIZE) {
        u1_t_match_count++;
    }

    if (s4_s_awbdata_size == (CriSint32)SOUND_AWBDATA_SIZE) {
        u1_t_match_count++;
    }

    if (s4_s_acbdata_size == (CriSint32)SOUND_ACBDATA_SIZE) {
        u1_t_match_count++;
    }

    if (s4_s_voicepooladxdata_size == (CriSint32)SOUND_VOICEPOOLADXDATA_SIZE) {
        u1_t_match_count++;
    }

    if (s4_s_player_size == (CriSint32)SOUND_PLAYER_SIZE) {
        u1_t_match_count++;
    }

    if (u1_t_match_count >= (U1)SOUND_DRV_INITIAL_MATCH_NUM) {
        u1_t_ret = (U1)SOUND_DRV_INITIAL_END;
        s4_s_initialize_size       = (CriSint32)SOUND_CRI_INIT_WORK_SIZE;
        s4_s_acfdata_size          = (CriSint32)SOUND_ACFDATA_SIZE;
        s4_s_awbdata_size          = (CriSint32)SOUND_AWBDATA_SIZE;
        s4_s_acbdata_size          = (CriSint32)SOUND_ACBDATA_SIZE;
        s4_s_voicepooladxdata_size = (CriSint32)SOUND_VOICEPOOLADXDATA_SIZE;
        s4_s_player_size           = (CriSint32)SOUND_PLAYER_SIZE;
    }
    else {
        u1_t_ret = (U1)SOUND_DRV_INITIAL;
    }

    return(u1_t_ret);
#else
    return((U1)SOUND_DRV_INITIAL_END); /* vd_s_SoundCriMgrStartup is processed in u1_s_SoundDiagnosis */
#endif /* SOUND_CRI_DEBUGMODE */
}

/*===================================================================================================================================*/
/*  U1  u1_g_SoundIcErrorStatus(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_s_sound_ic_error                                                                                           */
/*===================================================================================================================================*/
U1  u1_g_SoundIcErrorStatus(void)
{
    return(u1_s_sound_ic_error);
}

/*===================================================================================================================================*/
/*  U1  vd_g_SoundIcClearErrorStatus(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_s_sound_ic_error                                                                                           */
/*===================================================================================================================================*/
void  vd_g_SoundIcClearErrorStatus(void)
{
    u1_s_sound_ic_error = (U1)SOUND_IC_NORMAL;
}

/*===================================================================================================================================*/
/*  void  vd_g_SoundCriMgr_DeInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_SoundCriMgr_DeInit(void)
{
    Dio_WriteChannel((U1)DIO_ID_PORT20_CH1, (U1)STD_LOW);
    Dio_WriteChannel((U1)DIO_ID_PORT20_CH2, (U1)STD_LOW);

    Port_SetPinMode((U2)PORT_ID_PORT20_PIN1,   (U4)PORT_MODE_CFG_P20_1_DO_LO); 
    Port_SetPinMode((U2)PORT_ID_PORT20_PIN2,   (U4)PORT_MODE_CFG_P20_2_DO_LO);

    Dio_WriteChannel((U1)DIO_ID_PORT0_CH5, (U1)STD_LOW);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     6/13/2019  YK       Create SoundMiddle based on TY3S soft.                                                             */
/*  1.0.1     6/20/2019  YK       The eSysTest1 Buzzer registration. Apply to coding rule.                                           */
/*  1.0.2     6/27/2019  YK       Apply to coding rule.                                                                              */
/*  1.0.3     7/26/2019  YK       The eSysTest2 Buzzer registration. Apply to CRI WARE's middle-ware type D1L1.                      */
/*  1.1.0     4/13/2020  TN       Apply 800B CV spec, and replace to CRI middleware & sound data for 800B CV spec.                   */
/*  1.2.0     7/24/2020  SK       Change the following:                                                                              */
/*                                  - Correct the QAC metrics(STMIF).                                                                */
/*                                  - Change how the playing volume is specified.                                                    */
/*                                  - Change the sound data to 800B CV-R spec.                                                       */
/*                                  - Apply 800B CV-R spec to the buzzer active test.                                                */
/*                                  - Implement to mute buzzer during XM authentication mode.                                        */
/*                                  - Replacement the CRI Library(Include countermeasure for noise issue)                            */
/*                                  - Add the CRI stoping operation before starting buzzer.                                          */
/*  1.3.0     1/20/2021  SK       Change the following:                                                                              */
/*                                  - Change to assign sound CH to each sounding group. (Clearance sonar Rr is assigned to CH5)      */
/*                                  - Change the sound CH for active test buzzer to the same CH as the normal buzzer.                */
/*                                  - Change the CUE ID type from CriAtomExCueId to U2 within this module.                           */
/*                                  - Replacement the CRI library and authoring data. (For 800B 1A)                                  */
/*                                  - Apply the sound pressure spec. for 800B 1A.                                                    */
/*                                  - Change to support active test types other than 2KHz single tone buzzers.                       */
/*                                  - Add the function adjust the volume during multi channels playing.                              */
/*  1.4.0     2/11/2021  SK       Change the reverse buzzer sound from ADX codec data to sound generator data.                       */
/*  1.5.0     7/26/2021  MG       Add CRI reset processing when DMA transfer error occurred.                                         */
/*  1.6.0    11/11/2021  MG       Change pwm_method setting in the CRI Library to HIGH_PRECISION to improve quantization errors.     */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  200D-1    7/19/2022  SK       Change the following:                                                                              */
/*                                  - Apply priority order list of buzzer for Pre1A.                                                 */
/*                                  - Apply the sound spec for Pre1A.                                                                */
/*  200D-2    9/27/2022  SK       Apply the sound spec for 200B 1A 7inch.                                                            */
/*  200D-3   10/18/2022  SK       Apply the sound spec for 200B 1A 12.3inch.                                                         */
/*  200D-4   12/13/2022  SK       Change sound pressure for single frequency buzzer.                                                 */
/*  330D-1    1/11/2023  YKu      Apply the sound spec for 330D CV-R 12.3inch.                                                       */
/*  330D-2    2/ 7/2023  SK       Apply the sound spec for 330D CV-R2 12.3inch.                                                      */
/*  330D-3    3/14/2023  SK       Apply the sound spec for 330D 1A 12.3inch.                                                         */
/*  330D-4    5/16/2023  SK       Change sound pressure for single frequency buzzer and SEAREM buzzer.                               */
/*  330D-5    6/ 1/2023  SK       Add BSM warning buzzer.                                                                            */
/*  19PFv3-1  9/22/2023  SH       Add vd_s_SoundCriMgrCalibDataRead() and a process to separate TURHAZ by brand                      */
/*  19PFv3-2 12/27/2023  SI       Add u1_sp_sound_vol index                                                                          */
/*                                add parameter of MET-M_MWVCUS-                                                                     */
/*  19PFv3-3  1/19/2024  YR       Remove buzzer request for BRKHLD                                                                   */
/*  19PFv3-4  2/16/2024  SH       Change MCUCONST v010->v012                                                                         */
/*  19PFv3-5  2/19/2024  JMH      Added Buzzer request for BKEY                                                                      */
/*  19PFv3-6  2/20/2024  GM       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-7  4/16/2024  SH       Add calibration guard                                                                              */
/*  19PFv3-8  4/18/2024  T.Nakano Change MCUCONST v012->v014                                                                         */
/*  19PFv3-9  5/13/2024  DR       Change volume to match speaker hardware specs                                                      */
/*  19PFv3-9  5/13/2024  SN       Add pinmode for ONOFF sequence                                                                     */
/*  19PFv3-10 7/04/2024  T.Nakano Change the Method of Referencing Calibration.                                                      */
/*  19PFv3-11 7/12/2024  T.Nakano Add Calibration Guard to Unify Vehicle Operation.                                                  */
/*  19PFv3-12 7/10/2024  TR       Add SBRDMB buzzer request                                                                          */
/*                                                                                                                                   */
/*  BEV-1     3/19/2025  SU                                                                                                          */
/*  BEV-1     3/21/2025  RO       Change for BEV System_Consideration_1.(MET-M_CONTBUZZ2-CSTD-0004-C1)                               */
/*  BEV-2     6/17/2025  JS       Change for BEV System_Consideration_2.(MET-C_BRKBZ-CSTD-2-00-B-C0)                                 */
/*  BEV-3     6/20/2025  KO       Change for BEV System_Consideration_2.(MET-O_PDSMAL-CSTD-0-00-A-C0)                                */
/*  BEV-4     6/24/2025  RO       Change for BEV System_Consideration_2.(MET-S_ADBZR-CSTD-0-02-A-C0)                                 */
/*  BEV-5     6/24/2025  RO       Change for BEV System_Consideration_2.(MET-M_CONTBUZZ2-CSTD-0004-C1)                               */
/*  BEV-6    11/11/2025  SH       Configured for CONTBUZZ2-CSTD-0008                                                                 */
/*  BEV-7    11/28/2025  HL       Change for BEV System_Consideration_ADAS.(MET-S_TMBZR-CSTD-0-01-A-C0)                              */
/*  BEV-8    12/10/2025  HY       Change sound file(CUE_ID) for RCTA buzzer                                                          */
/*  BEV-9    02/10/2026  SH       Change MCUID0024 from Calibration to OMUSVIID                                                      */
/*  BEV-10   03/10/2026  YH       Change config for BEV Full_Function_2.                                                             */
/*                                MET-P_BSTMOD-CSTD-0-00-A-C0                                                                        */
/*                                Add BOOST MODE reject buzzer request                                                               */
/*  BEV-11   03/17/2026  SN       Change for BEV Full_Function_2.                                                                    */
/*                                MET-B_OPTMON-CSTD-0-00-A-C0                                                                        */
/*                                Added Buzzer request for OPTMON                                                                    */
/*                                                                                                                                   */
/*  * YK       = Yuuki Kato, Denso Techno                                                                                            */
/*  * TN       = Toshiharu Nagata, Denso Techno                                                                                      */
/*  * SK       = Sakae Kitamura, Denso Techno                                                                                        */
/*  * MG       = Mei Godo, KSE                                                                                                       */
/*  * YKu      = Yuta Kusunoki, Denso Techno                                                                                         */
/*  * SH       = Sae Hirose, Denso Techno                                                                                            */
/*  * SI       = Shugo Ichinose, Denso Techno                                                                                        */
/*  * YR       = Yhana Regalario, Denso Techno Phil. Inc.                                                                            */
/*  * JMH      = James Michael Hilarion, DTPH                                                                                        */
/*  * GM       = Glen Monteposo, DTPH                                                                                                */
/*  * T.Nakano = Tetsushi Nakano, Denso Techno                                                                                       */
/*  * DR       = Dyan Reyes, DTPH                                                                                                    */
/*  * SN       = Shimon Nambu, Denso Techno                                                                                          */
/*  * TR       = Tebs Ramos, DTPH                                                                                                    */
/*  * SU       = Shin Uchida, Denso Techno                                                                                           */
/*  * RO       = Ryo Oohashi, Denso Techno                                                                                           */
/*  * JS       = Jun Sugiyama, KSE                                                                                                   */
/*  * KO       = Kazuto Oishi, Denso Techno                                                                                          */
/*  * HL       = Harry Lapiceros,  DTPH                                                                                              */
/*  * HY       = Hiroki You, Denso Techno                                                                                            */
/*  * YH       = Yuki Hatakeyama, KSE                                                                                                */
/*  * SN       = Shizuka Nakajima, KSE                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
