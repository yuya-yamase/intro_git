/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN Service Application Layer / Deletion of In-vehicle Personal and Privacy Information                                      */
/*                                      ^           ^          ^            ^       ^                                                */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DIPPI_C_MAJOR                    (1)
#define TYDOCAN_DIPPI_C_MINOR                    (1)
#define TYDOCAN_DIPPI_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "tydocan_dippi.h"
#include "tydocan_sal.h"
#include "oxdocan_cfg_private.h"

#include "tripcom.h"
#include "tripcom_ms.h"
#include "avggrph.h"
#if 0    /* BEV Diag provisionally */
#include "mcst.h"
#endif    /* BEV Diag provisionally */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DIPPI_DEL_NON                   (0x00000000U)
#define TYDOCAN_DIPPI_DEL_RQ                    (0xa55aa55aU)

#define TYDOCAN_DIPPI_EVT_NON                   (0x00U)
#define TYDOCAN_DIPPI_EVT_DIAGON                (0x01U)
#define TYDOCAN_DIPPI_EVT_DELSTS_OTH            (0x00U)         /* return from u1_s_TyDoCANDippiDeleteChk */
#define TYDOCAN_DIPPI_EVT_DELSTS_SUC            (0x02U)         /* return from u1_s_TyDoCANDippiDeleteChk */
#define TYDOCAN_DIPPI_EVT_DELSTS_FAI            (0x04U)         /* return from u1_s_TyDoCANDippiDeleteChk */
#define TYDOCAN_DIPPI_EVT_NOREQ_NUM             (8U)
#define TYDOCAN_DIPPI_EVT_DELREQ                (0x08U)

#define TYDOCAN_DIPPI_BIT_TIM_CLR               (0x0100U)
#define TYDOCAN_DIPPI_BIT_DEL_EXE               (0x0200U)
#define TYDOCAN_DIPPI_BIT_STS_MASK              (0x00FFU)

#define TYDOCAN_DIPPI_ACT_INI_C_N               (TYDOCAN_DIPPI_STS_INI | TYDOCAN_DIPPI_BIT_TIM_CLR                            )
#define TYDOCAN_DIPPI_ACT_RUN_C_E               (TYDOCAN_DIPPI_STS_RUN | TYDOCAN_DIPPI_BIT_TIM_CLR | TYDOCAN_DIPPI_BIT_DEL_EXE)
#define TYDOCAN_DIPPI_ACT_RUN_N_N               (TYDOCAN_DIPPI_STS_RUN                                                        )
#define TYDOCAN_DIPPI_ACT_SUC_C_N               (TYDOCAN_DIPPI_STS_SUC | TYDOCAN_DIPPI_BIT_TIM_CLR                            )
#define TYDOCAN_DIPPI_ACT_FAI_C_N               (TYDOCAN_DIPPI_STS_FAI | TYDOCAN_DIPPI_BIT_TIM_CLR                            )
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1      (* const fp_u1_RSLT)(const U1 u1_a_CH);
    U1               u1_ch;
} ST_TYDOCAN_DIPPI_TRIPCHK;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4       u4_s_tydc_dippi_delrq;
static U2       u2_s_tydc_dippi_timer;
static U1       u1_s_tydc_dippi_sts;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_TyDoCANDippiTrnsit(const U1 u1_a_EVT);

static U1       u1_s_TyDoCANDippiCfgDeleteChk(void);
static U1       u1_s_TyDoCANDippiCfgDelTripcomChk(void);
static U1       u1_s_TyDoCANDippiCfgDelTriphisChk(void);
static U1       u1_s_TyDoCANDippiCfgDelNicknameChk(void);

static void     vd_s_TyDoCANDippiCfgDeleteExe(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDippiInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDippiInit(void)
{
    u4_s_tydc_dippi_delrq = (U4)TYDOCAN_DIPPI_DEL_NON;
    u2_s_tydc_dippi_timer = (U2)0U;
    u1_s_tydc_dippi_sts   = (U1)TYDOCAN_DIPPI_STS_INI;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDippiMainTask(const U1 u1_a_EOM, const U2 u2_a_SLOT)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDippiMainTask(const U1 u1_a_EOM, const U2 u2_a_SLOT)
{
    static const U2 u2_s_TYDOCAN_DIPPI_CHKSLOT = (U2)OXDC_TSLOT_BIT_4;      /* 100ms E */
    static const U2 u2_s_TYDOCAN_DIPPI_CHKWAIT = (U2)100U;                  /* 1000ms (1-65535) */

    U1          u1_t_diag_on;
    U1          u1_t_evt;
    U2          u2_t_chk;

    u1_t_evt = (U1)TYDOCAN_DIPPI_EVT_NON;

    /* bit0 */
    u1_t_diag_on = u1_a_EOM & (U1)OXDC_EOM_DIAG_ON;
    if(u1_t_diag_on != (U1)0x00U){
        u1_t_evt = (U1)TYDOCAN_DIPPI_EVT_DIAGON;
    }

    /* bit1,2 */
    if(u2_s_tydc_dippi_timer < (U2)U2_MAX){
        u2_s_tydc_dippi_timer++;
    }
    u2_t_chk = u2_a_SLOT & (U2)u2_s_TYDOCAN_DIPPI_CHKSLOT;
    if((u2_t_chk              != (U2)0x0000U               ) &&
       (u2_s_tydc_dippi_timer  > u2_s_TYDOCAN_DIPPI_CHKWAIT)){              /* Waiting for application task execution */
        u1_t_evt |= u1_s_TyDoCANDippiCfgDeleteChk();
    }

    /* bit3 */
    if(u4_s_tydc_dippi_delrq == (U4)TYDOCAN_DIPPI_DEL_RQ){
        u1_t_evt |= (U1)TYDOCAN_DIPPI_EVT_DELREQ;
    }
    u4_s_tydc_dippi_delrq = (U4)TYDOCAN_DIPPI_DEL_NON;
 
    vd_s_TyDoCANDippiTrnsit(u1_t_evt);
}
/*===================================================================================================================================*/
/*  static void vd_s_TyDoCANDippiTrnsit(const U1 u1_a_EVT)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_TyDoCANDippiTrnsit(const U1 u1_a_EVT)
{
    /* [sts]_[timer]_[reset] C:Clear, N:Non, E:Execute */
    static const U2 u2_sp_TYDOCAN_DIPPI_TRNST_00TO07[TYDOCAN_DIPPI_EVT_NOREQ_NUM][TYDOCAN_DIPPI_STS_NUM]={
        /*   INI                            RUN                            SUC                            FAI */
        {(U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_RUN_N_N, (U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_INI_C_N},
        {(U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_RUN_N_N, (U2)TYDOCAN_DIPPI_ACT_SUC_C_N, (U2)TYDOCAN_DIPPI_ACT_FAI_C_N},
        {(U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_SUC_C_N, (U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_INI_C_N},
        {(U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_SUC_C_N, (U2)TYDOCAN_DIPPI_ACT_SUC_C_N, (U2)TYDOCAN_DIPPI_ACT_FAI_C_N},
        {(U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_FAI_C_N, (U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_INI_C_N},
        {(U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_FAI_C_N, (U2)TYDOCAN_DIPPI_ACT_SUC_C_N, (U2)TYDOCAN_DIPPI_ACT_FAI_C_N},
        {(U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_RUN_N_N, (U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_INI_C_N},
        {(U2)TYDOCAN_DIPPI_ACT_INI_C_N, (U2)TYDOCAN_DIPPI_ACT_RUN_N_N, (U2)TYDOCAN_DIPPI_ACT_SUC_C_N, (U2)TYDOCAN_DIPPI_ACT_FAI_C_N}
    };
    static const U2 u2_sp_TYDOCAN_DIPPI_TRNST_08TO15[TYDOCAN_DIPPI_STS_NUM]={
        /*   INI                            RUN                            SUC                            FAI */
         (U2)TYDOCAN_DIPPI_ACT_RUN_C_E, (U2)TYDOCAN_DIPPI_ACT_RUN_N_N, (U2)TYDOCAN_DIPPI_ACT_RUN_C_E, (U2)TYDOCAN_DIPPI_ACT_RUN_C_E
    };

    U2          u2_t_act;

    u2_t_act = (U2)TYDOCAN_DIPPI_ACT_INI_C_N;
    if(u1_s_tydc_dippi_sts < (U1)TYDOCAN_DIPPI_STS_NUM){
        if(u1_a_EVT < (U1)TYDOCAN_DIPPI_EVT_NOREQ_NUM){
            u2_t_act = u2_sp_TYDOCAN_DIPPI_TRNST_00TO07[u1_a_EVT][u1_s_tydc_dippi_sts];
        }
        else{
            u2_t_act = u2_sp_TYDOCAN_DIPPI_TRNST_08TO15[u1_s_tydc_dippi_sts];
        }
    }

    /*-----------------------------------------------------------------------*/
    u1_s_tydc_dippi_sts = (U1)(u2_t_act & (U2)TYDOCAN_DIPPI_BIT_STS_MASK);

    if((u2_t_act & (U2)TYDOCAN_DIPPI_BIT_TIM_CLR) != (U2)0x0000U){
        u2_s_tydc_dippi_timer = (U2)0U;
    }

    if((u2_t_act & (U2)TYDOCAN_DIPPI_BIT_DEL_EXE) != (U2)0x0000U){
        vd_s_TyDoCANDippiCfgDeleteExe();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDippiDeleteRq(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDippiDeleteRq(void)
{
    u2_s_tydc_dippi_timer = (U2)0U;
    u4_s_tydc_dippi_delrq = (U4)TYDOCAN_DIPPI_DEL_RQ;
}
/*===================================================================================================================================*/
/*  void    u1_g_TyDoCANDippiDeleteRslt(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDippiDeleteRslt(void)
{
    return(u1_s_tydc_dippi_sts);
}
/*===================================================================================================================================*/
/*  static U1   u1_s_TyDoCANDippiCfgDeleteChk(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_TyDoCANDippiCfgDeleteChk(void)
{
    U1          u1_t_evt;

    /* Tripcom */
    u1_t_evt = u1_s_TyDoCANDippiCfgDelTripcomChk();
    if(u1_t_evt == (U1)TYDOCAN_DIPPI_EVT_DELSTS_SUC){
        u1_t_evt = u1_s_TyDoCANDippiCfgDelTriphisChk();
    }

    /* NickName */
    if(u1_t_evt == (U1)TYDOCAN_DIPPI_EVT_DELSTS_SUC){
        u1_t_evt = u1_s_TyDoCANDippiCfgDelNicknameChk();
    }
    return(u1_t_evt);
}
/*===================================================================================================================================*/
/*  static U1   u1_s_TyDoCANDippiCfgDelTripcomChk(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_TyDoCANDippiCfgDelTripcomChk(void)
{
#if 0    /* BEV Diag provisionally */
    static const ST_TYDOCAN_DIPPI_TRIPCHK st_sp_TYDOCAN_DIPPI_TRIPCOM_CHK[]={
        { &u1_g_AvgFeRstImmwRslt,           (U1)AVGFE_CNTT_TA           },   /* 01.Total Average Fuel Economy           */
        { &u1_g_AvgFeRstImmwRslt,           (U1)AVGFE_CNTT_RF           },   /* 02.After Refuel Average Fuel Economy    */
        { &u1_g_AvgVehspdRstImmwRslt,       (U1)AVGVEHSPD_CNTT_TA       },   /* 03.Total  Average Vehicle Speed         */
        { &u1_g_AvgVehspdRstImmwRslt,       (U1)AVGVEHSPD_CNTT_TR_A     },   /*    Trip A Average Vehicle Speed         */
        { &u1_g_AvgVehspdRstImmwRslt,       (U1)AVGVEHSPD_CNTT_TR_B     },   /*    Trip B Average Vehicle Speed         */
        { &u1_g_PtsRunTmRstImmwRslt,        (U1)PTSRUNTM_CNTT_LC        },   /* 05.Lif Cycle Powertrain run time        */
        { &u1_g_PtsRunTmRstImmwRslt,        (U1)PTSRUNTM_CNTT_TR_A      },   /*    Trip A    Powertrain run time        */
        { &u1_g_PtsRunTmRstImmwRslt,        (U1)PTSRUNTM_CNTT_TR_B      },   /*    Trip B    Powertrain run time        */
        { &u1_g_DteEdRstImmwRslt,           (U1)DTE_ED_CNTT_FU          },   /* 04.CG of Distance To Empty              */
                                                                             /* 06.Distance To Empty                    */
        { &u1_g_AvgEeRstImmwRslt,           (U1)AVGEE_CNTT_TA           }    /* 09.Total Average Electric Economy       */
    };
    static const U1 u1_s_TYDOCAN_DIPPI_TRIPCOM_NUM = (U1)(sizeof(st_sp_TYDOCAN_DIPPI_TRIPCOM_CHK) / 
                                                          sizeof(st_sp_TYDOCAN_DIPPI_TRIPCOM_CHK[0]));

    const ST_TYDOCAN_DIPPI_TRIPCHK * st_tp_CHK;
    U4                               u4_t_loop;
    U1                               u1_t_evt;
    U1                               u1_t_rslt;
    U1                               u1_t_sucrslt;
    U1                               u1_t_fairslt;
    U1                               u1_t_tmprslt;

    u1_t_evt  = (U1)TYDOCAN_DIPPI_EVT_DELSTS_SUC;

    u1_t_rslt = (U1)TRIPCOM_RSTIMMW_SUC;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_s_TYDOCAN_DIPPI_TRIPCOM_NUM; u4_t_loop++){
        st_tp_CHK = &st_sp_TYDOCAN_DIPPI_TRIPCOM_CHK[u4_t_loop];
        if(st_tp_CHK->fp_u1_RSLT != vdp_PTR_NA){
            u1_t_tmprslt = st_tp_CHK->fp_u1_RSLT(st_tp_CHK->u1_ch);
            u1_t_sucrslt = (U1)((u1_t_rslt & u1_t_tmprslt) & (U1)TRIPCOM_RSTIMMW_SUC);
            u1_t_fairslt = (U1)((u1_t_rslt | u1_t_tmprslt) & (U1)TRIPCOM_RSTIMMW_FAI);
            u1_t_rslt    = u1_t_sucrslt | u1_t_fairslt;
        }
    }

    /*-----------------------------------------------------------------------*/
    if((u1_t_rslt & (U1)TRIPCOM_RSTIMMW_SUC) != (U1)0x00U){
        /* nothing */
    }
    else if((u1_t_rslt & (U1)TRIPCOM_RSTIMMW_FAI) != (U1)0x00U){
        u1_t_evt = (U1)TYDOCAN_DIPPI_EVT_DELSTS_FAI;
    }
    else{
        u1_t_evt = (U1)TYDOCAN_DIPPI_EVT_DELSTS_OTH;
    }
    return(u1_t_evt);
#else    /* BEV Diag provisionally */
    return((U1)TYDOCAN_DIPPI_EVT_DELSTS_FAI);
#endif    /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*  static U1   u1_s_TyDoCANDippiCfgDelTripchisChk(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_TyDoCANDippiCfgDelTriphisChk(void)
{
#if 0    /* BEV Diag provisionally */
    U1          u1_t_evt;
    U1          u1_t_rslt;
    U1          u1_t_sucrslt;
    U1          u1_t_fairslt;
    U1          u1_t_tmprslt;

    u1_t_evt = (U1)TYDOCAN_DIPPI_EVT_DELSTS_SUC;

    /* 07.XXX Economy Histroy Grpash           */
    u1_t_rslt    = u1_g_AvgGrphDiagRslt((U1)AVGGRPH_CNTT_1MFE);
    
    u1_t_tmprslt = u1_g_AvgGrphDiagRslt((U1)AVGGRPH_CNTT_1MEE);
    u1_t_sucrslt = (U1)((u1_t_rslt & u1_t_tmprslt) & (U1)TRIPCOM_MS_NVMSTS_SUC);
    u1_t_fairslt = (U1)((u1_t_rslt | u1_t_tmprslt) & (U1)TRIPCOM_MS_NVMSTS_FAIL);
    u1_t_rslt    = u1_t_sucrslt | u1_t_fairslt;

    u1_t_tmprslt = u1_g_AvgGrphDiagRslt((U1)AVGGRPH_CNTT_TAFE);
    u1_t_sucrslt = (U1)((u1_t_rslt & u1_t_tmprslt) & (U1)TRIPCOM_MS_NVMSTS_SUC);
    u1_t_fairslt = (U1)((u1_t_rslt | u1_t_tmprslt) & (U1)TRIPCOM_MS_NVMSTS_FAIL);
    u1_t_rslt    = u1_t_sucrslt | u1_t_fairslt;

    u1_t_tmprslt = u1_g_AvgGrphDiagRslt((U1)AVGGRPH_CNTT_TAEE);
    u1_t_sucrslt = (U1)((u1_t_rslt & u1_t_tmprslt) & (U1)TRIPCOM_MS_NVMSTS_SUC);
    u1_t_fairslt = (U1)((u1_t_rslt | u1_t_tmprslt) & (U1)TRIPCOM_MS_NVMSTS_FAIL);
    u1_t_rslt    = u1_t_sucrslt | u1_t_fairslt;

    if((u1_t_rslt & (U1)TRIPCOM_MS_NVMSTS_SUC) != (U1)0x00U){
        /* nothing */
    }
    else if((u1_t_rslt & (U1)TRIPCOM_MS_NVMSTS_FAIL) != (U1)0x00U){
        u1_t_evt = (U1)TYDOCAN_DIPPI_EVT_DELSTS_FAI;
    }
    else{
        u1_t_evt = (U1)TYDOCAN_DIPPI_EVT_DELSTS_OTH;
    }
    return(u1_t_evt);
#else    /* BEV Diag provisionally */
    return((U1)TYDOCAN_DIPPI_EVT_DELSTS_FAI);
#endif    /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*  static U1   u1_s_TyDoCANDippiCfgDelNicknameChk(void)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_TyDoCANDippiCfgDelNicknameChk(void)
{
#if 0    /* BEV Diag provisionally */
    U1          u1_t_evt;
    U1          u1_t_res;

    u1_t_evt = (U1)TYDOCAN_DIPPI_EVT_DELSTS_SUC;

    /* 10.NickName                             */
    u1_t_res = u1_g_McstNickNameAllRstChk();
    if(u1_t_res == (U1)MCST_RES_SUC){
        /* nothing */
    }
    else if(u1_t_res == (U1)MCST_RES_FAI){
        u1_t_evt = (U1)TYDOCAN_DIPPI_EVT_DELSTS_FAI;
    }
    else{
        u1_t_evt = (U1)TYDOCAN_DIPPI_EVT_DELSTS_OTH;
    }
    return(u1_t_evt);
#else    /* BEV Diag provisionally */
    return((U1)TYDOCAN_DIPPI_EVT_DELSTS_FAI);
#endif    /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*  static void vd_s_TyDoCANDippiCfgDeleteExe(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_TyDoCANDippiCfgDeleteExe(void)
{
#if 0    /* BEV Diag provisionally */
    static const U2 u2_s_TYDOCAN_DIPPI_TRIPITEM_RSTBIT = (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_TA |        /* 01    */
                                                         (U2)TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TA |      /* 03-1  */
                                                         (U2)TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_A |    /*   -2  */
                                                         (U2)TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_B |    /*   -3  */
                                                         (U2)TRIPCOM_RSTRQBIT_M_PTSRUNTM_LC |       /* 05-1  */
                                                         (U2)TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_A |     /*   -2  */
                                                         (U2)TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_B |     /*   -3  */
                                                         (U2)TRIPCOM_RSTRQBIT_M_DTE_RF |            /* 04,06 */
                                                         (U2)TRIPCOM_RSTRQBIT_M_AVGEE_TA;           /* 09    */

    static const U2 u2_s_TYDOCAN_DIPPI_TRIPHIST_RSTBIT = (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_ONEM |      /* 07    */
                                                         (U2)TRIPCOM_RSTRQBIT_M_AVGEE_ONEM |
                                                         (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_TA |
                                                         (U2)TRIPCOM_RSTRQBIT_M_AVGEE_TA;

    /* 01.Total Average Fuel Economy           */
    /* 03.Total  Average Vehicle Speed         */
    /*    Trip A Average Vehicle Speed         */
    /*    Trip B Average Vehicle Speed         */
    /* 05.Lif Cycle Powertrain run time        */
    /*    Trip A    Powertrain run time        */
    /*    Trip B    Powertrain run time        */
    /* 04.CG of Distance To Empty              */
    /* 06.Distance To Empty                    */
    /* 09.Total Average Electric Economy       */
    vd_g_TripcomRstRqImmWr(u2_s_TYDOCAN_DIPPI_TRIPITEM_RSTBIT);

    /* 02.After Refuel Average Fuel Economy    */
    vd_g_TripcomFrcRefuelEvImmWr();

    /* 07.XXX Economy Histroy Grpash           */
    vd_g_TripcomGrphRstRq(u2_s_TYDOCAN_DIPPI_TRIPHIST_RSTBIT);

    /* 08.EV Ration                            */
    /*    No implementation required, because this feature is automatically reset by Ready-ON */

    /* 10.NickName                             */
    vd_g_McstNickNameAllRstRq();
#endif    /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    01/21/2025  MaO(M)   New.                                                                                               */
/*  1.0.1    05/20/2025  KM       Change u1_g_AvgGrphRslt() IF.                                                                      */
/*  1.1.0    04/02/2026  TK       Change EOM monitoring target from IGN to Diag Power.                                               */
/*                                                                                                                                   */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*    KM     = Keisuke Mashita, Denso Techno                                                                                         */
/*    TK     = Tamao Kamiya, Denso Techno                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
