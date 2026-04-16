/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  ASIL Telltale Drawing Monitoring Check                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ASILCHK_CFG_C_MAJOR                     (1)
#define ASILCHK_CFG_C_MINOR                     (0)
#define ASILCHK_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "asilchk_cfg_private.h"

#include "vardef.h"
#include "hmitt.h"
#include "alert.h"
#include "calibration.h"

#include "ivdsh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ASILCHK_CFG_C_MAJOR != ASILCHK_H_MAJOR) || \
     (ASILCHK_CFG_C_MINOR != ASILCHK_H_MINOR) || \
     (ASILCHK_CFG_C_PATCH != ASILCHK_H_PATCH))
#error "asilchk_cfg.c and asilchk.h : source and header files are inconsistent!"
#endif

#if ((ASILCHK_CFG_C_MAJOR != ASILCHK_CFG_H_MAJOR) || \
     (ASILCHK_CFG_C_MINOR != ASILCHK_CFG_H_MINOR) || \
     (ASILCHK_CFG_C_PATCH != ASILCHK_CFG_H_PATCH))
#error "asilchk_cfg.c and asilchk_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    ASILCHK_VM_1WORD                                  (1U)

#define    ASILCHK_DAV_ACT_FLG_ON                            (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4   u4_sp_asilchk_hmitt_buf[HMITT_ASIL_NUM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_AsilChkCfgAirbagReq(void);
static U4 u4_s_AsilChkCfgAirbagOnCrc(void);

static U1 u1_s_AsilChkCfgPedproReq(void);
static U4 u4_s_AsilChkCfgPedproOnCrc(void);

static U1 u1_s_AsilChkCfgAbsReq(void);
static U4 u4_s_AsilChkCfgAbsOnCrc(void);

static U1 u1_s_AsilChkCfgBrkhldReq(void);
static U1 u1_s_AsilChkCfgBrkhldCycTime(void);
static U4 u4_s_AsilChkCfgBrkhldOnCrc(void);

static U1 u1_s_AsilChkCfgEcbReq(void);
static U4 u4_s_AsilChkCfgEcbOnCrc(void);

static U1 u1_s_AsilChkCfgEpbReq(void);
static U1 u1_s_AsilChkCfgEpbCycTime(void);
static U4 u4_s_AsilChkCfgEpbOnCrc(void);

static U1 u1_s_AsilChkCfgSlipReq(void);
static U4 u4_s_AsilChkCfgSlipOnCrc(void);

static U1 u1_s_AsilChkCfgVscoffReq(void);
static U4 u4_s_AsilChkCfgVscoffOnCrc(void);

static U1 u1_s_AsilChkCfgAddotttReq(void);
static U4 u4_s_AsilChkCfgAddotttOnCrc(void);

static U1 u1_s_AsilChkCfgBrkReq(void);
static U4 u4_s_AsilChkCfgBrkOnCrc(void);

static U1 u1_s_AsilChkCfgEpsReq(void);
static U4 u4_s_AsilChkCfgEpsOnCrc(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ASILCHK_TTCRC st_gp_ASILCHK_TT_TABLE[ASILCHK_TT_NUM] = {
    /*  fp_u1_req               fp_u1_cyctime                 fp_u4_oncrc                                                  */
    {u1_s_AsilChkCfgAirbagReq,  vdp_PTR_NA,                   u4_s_AsilChkCfgAirbagOnCrc      },  /* CRC00 : TT_AIRBAG     */
    {u1_s_AsilChkCfgPedproReq,  vdp_PTR_NA,                   u4_s_AsilChkCfgPedproOnCrc      },  /* CRC01 : TT_PEDPRO     */
    {u1_s_AsilChkCfgAbsReq,     vdp_PTR_NA,                   u4_s_AsilChkCfgAbsOnCrc         },  /* CRC02 : TT_ABS        */
    {u1_s_AsilChkCfgBrkhldReq,  u1_s_AsilChkCfgBrkhldCycTime, u4_s_AsilChkCfgBrkhldOnCrc      },  /* CRC03 : TT_BRKHLD_YEL */
    {u1_s_AsilChkCfgEcbReq,     vdp_PTR_NA,                   u4_s_AsilChkCfgEcbOnCrc         },  /* CRC04 : TT_EPB_BRK    */
    {u1_s_AsilChkCfgEpbReq,     u1_s_AsilChkCfgEpbCycTime,    u4_s_AsilChkCfgEpbOnCrc         },  /* CRC05 : TT_EPB_PARK   */
    {u1_s_AsilChkCfgSlipReq,    vdp_PTR_NA,                   u4_s_AsilChkCfgSlipOnCrc        },  /* CRC06 : TT_SLIP       */
    {u1_s_AsilChkCfgVscoffReq,  vdp_PTR_NA,                   u4_s_AsilChkCfgVscoffOnCrc      },  /* CRC07 : TT_VSCOFF     */
    {u1_s_AsilChkCfgAddotttReq, vdp_PTR_NA,                   u4_s_AsilChkCfgAddotttOnCrc     },  /* CRC08 : TT_ADDOTTT    */
    {u1_s_AsilChkCfgBrkReq,     vdp_PTR_NA,                   u4_s_AsilChkCfgBrkOnCrc         },  /* CRC09 : TT_BRAKE      */
    {u1_s_AsilChkCfgEpsReq,     vdp_PTR_NA,                   u4_s_AsilChkCfgEpsOnCrc         },  /* CRC10 : TT_EPS        */
    {vdp_PTR_NA,                vdp_PTR_NA,                   vdp_PTR_NA                      },  /* CRC11                 */
    {vdp_PTR_NA,                vdp_PTR_NA,                   vdp_PTR_NA                      },  /* CRC12                 */
    {vdp_PTR_NA,                vdp_PTR_NA,                   vdp_PTR_NA                      },  /* CRC13                 */
    {vdp_PTR_NA,                vdp_PTR_NA,                   vdp_PTR_NA                      },  /* CRC14                 */
    {vdp_PTR_NA,                vdp_PTR_NA,                   vdp_PTR_NA                      }   /* CRC15                 */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AsilChkCfgInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AsilChkCfgInit(void)
{
    static const U4     u4_s_TX_SPIFAIL_OK  = (U4)0U;
    U4                  u4_t_tx_data;
    U4                  u4_t_loop;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMITT_ASIL_NUM ; u4_t_loop++){
        u4_sp_asilchk_hmitt_buf[u4_t_loop] = (U4)0x00000000U;
    }

    u4_t_tx_data = u4_s_TX_SPIFAIL_OK;
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM1TO3_SPI_FAIL, &u4_t_tx_data, (U2)ASILCHK_VM_1WORD);
}

/*===================================================================================================================================*/
/*  U1    u1_g_AsilChkCfgGetPowSts(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_ret：(TRUE/FALSE)                                                                                           */
/*===================================================================================================================================*/
U1    u1_g_AsilChkCfgGetPowSts(void)
{
    static const U4     u4_s_SOC_POW_STS_POWERON = (U4)1U;
    U4                  u4_t_soc_pow_sts;
    U1                  u1_t_read_sts;
    U1                  u1_t_ret;

    u4_t_soc_pow_sts = u4_s_SOC_POW_STS_POWERON;
    u1_t_read_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM3TO1_SOC_POW_STS, &u4_t_soc_pow_sts, (U2)ASILCHK_VM_1WORD);
    if (u1_t_read_sts == (U1)IVDSH_NO_REA) {
        u4_t_soc_pow_sts = u4_s_SOC_POW_STS_POWERON;
    }

    u1_t_ret = (U1)FALSE;
    if (u4_t_soc_pow_sts == u4_s_SOC_POW_STS_POWERON) {
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_g_AsilChkCfgGetTtSts(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AsilChkCfgGetTtSts(void)
{
    vd_g_HmiAsilTt(&u4_sp_asilchk_hmitt_buf[0], HMITT_ASIL_NUM);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgAirbagReq(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgAirbagReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_tt_airbag;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_airbag     = (U1)((u4_sp_asilchk_hmitt_buf[0] >> 12) & 0x0000000f);
    if(u1_t_tt_airbag == (U1)HMITT_BLINK_CO_ON_____100P){
        u1_t_req       = (U1)ASILCHK_REQ_ASIL_LIGHT;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgAirbagOnCrc(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgAirbagOnCrc(void) 
{
    static const U4     u4_s_TTAIRBAG_CRC    = (U4)0xC65E2562;

    return(u4_s_TTAIRBAG_CRC);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgPedproReq(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgPedproReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_alert_req;
    U1  u1_t_tt_pedpro;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_pedpro     = (U1)((u4_sp_asilchk_hmitt_buf[0] >> 8) & 0x0000000f);
    if(u1_t_tt_pedpro == (U1)HMITT_BLINK_CO_ON_____100P){
        u1_t_alert_req = u1_g_AlertReqByCh((U2)ALERT_CH_B_PEDPRO);
        if(u1_t_alert_req == (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN){
            u1_t_req       = (U1)ASILCHK_REQ_ASIL_LIGHT;
        }
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgPedproOnCrc(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgPedproOnCrc(void) 
{
    static const U4     u4_s_TTPEDPRO_CRC    = (U4)0xA07FA113;

    return(u4_s_TTPEDPRO_CRC);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgAbsReq(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgAbsReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_alert_req;
    U1  u1_t_tt_abs;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_abs     = (U1)((u4_sp_asilchk_hmitt_buf[0] >> 24) & 0x0000000f);
    if(u1_t_tt_abs == (U1)HMITT_BLINK_CO_ON_____100P){
        u1_t_alert_req = u1_g_AlertReqByCh((U2)ALERT_CH_C_ABS_TT);
        if(u1_t_alert_req == (U1)ALERT_REQ_C_ABS_TT_ASIL_ON){
            u1_t_req       = (U1)ASILCHK_REQ_ASIL_LIGHT;
        }
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgAbsOnCrc(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgAbsOnCrc(void) 
{
    static const U4     u4_s_TTABS_CRC_NA    = (U4)0x36E6C247;
    static const U4     u4_s_TTABS_CRC_OTHER = (U4)0xA9FF3BB7;
    U4                  u4_t_crc;
    U1                  u1_t_dest;

    u1_t_dest = u1_g_VardefTtAbs();
    if(u1_t_dest == (U1)VDF_TTABS_NO6){
        u4_t_crc = u4_s_TTABS_CRC_NA;
    } else {
        u4_t_crc = u4_s_TTABS_CRC_OTHER;
    }

    return(u4_t_crc);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgBrkhldReq(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgBrkhldReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_tt_brkhld;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_brkhld     = (U1)((u4_sp_asilchk_hmitt_buf[1] >> 12) & 0x0000000f);
    if(u1_t_tt_brkhld == (U1)HMITT_BLINK_CO_2P00HZ__50P){
        u1_t_req    = (U1)ASILCHK_REQ_ASIL_BLINK;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgBrkhldCycTime(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_cyc：cycle time                                                                                             */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgBrkhldCycTime(void)
{
    static const U1     u1_s_TTBRKHLD_CYCTIME = (U1)(500U / ASILCHK_TASK_TIM); 

    return(u1_s_TTBRKHLD_CYCTIME);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgBrkhldOnCrc(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgBrkhldOnCrc(void) 
{
    static const U4     u4_s_TTBRKHLD_CRC    = (U4)0x6AA10F61;

    return(u4_s_TTBRKHLD_CRC);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgEcbReq(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgEcbReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_alert_req;
    U1  u1_t_tt_ecb;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_ecb     = (U1)(u4_sp_asilchk_hmitt_buf[0] & 0x0000000f);
    if(u1_t_tt_ecb == (U1)HMITT_BLINK_CO_ON_____100P){
        u1_t_alert_req = u1_g_AlertReqByCh((U2)ALERT_CH_C_ECB_TT);
        if(u1_t_alert_req == (U1)ALERT_REQ_C_ECB_TT_MALFUNC){
            u1_t_req       = (U1)ASILCHK_REQ_ASIL_LIGHT;
        }
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgEcbOnCrc(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgEcbOnCrc(void) 
{
    static const U4     u4_s_TTECB_CRC    = (U4)0x4E76F433;

    return(u4_s_TTECB_CRC);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgEpbReq(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgEpbReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_tt_epb;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_epb     = (U1)((u4_sp_asilchk_hmitt_buf[0] >> 20) & 0x0000000f);
    if(u1_t_tt_epb == (U1)HMITT_BLINK_CO_1P00HZ__50P){
        u1_t_req    = (U1)ASILCHK_REQ_ASIL_BLINK;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgEpbCycTime(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_cyc：cycle time                                                                                             */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgEpbCycTime(void)
{
    static const U1     u1_s_TTEPB_CYCLE  = (U1)(1000U / ASILCHK_TASK_TIM); 

    return(u1_s_TTEPB_CYCLE);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgEpbOnCrc(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgEpbOnCrc(void) 
{
    static const U4     u4_s_TTEPB_CRC_NA    = (U4)0x45767EF6;
    static const U4     u4_s_TTEPB_CRC_OTHER = (U4)0xCD751542;
    U4                  u4_t_crc;
    U1                  u1_t_dest;

    u1_t_dest = u1_g_VardefTtEpbPkb();
    if(u1_t_dest == (U1)VDF_TTEPBPKB_NO10){
        u4_t_crc = u4_s_TTEPB_CRC_NA;
    } else {
        u4_t_crc = u4_s_TTEPB_CRC_OTHER;
    }

    return(u4_t_crc);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgSlipReq(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgSlipReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_tt_slip;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_slip     = (U1)((u4_sp_asilchk_hmitt_buf[0] >> 4) & 0x0000000f);
    if(u1_t_tt_slip == (U1)HMITT_BLINK_CO_ON_____100P){
        u1_t_req     = (U1)ASILCHK_REQ_ASIL_LIGHT;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgSlipOnCrc(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgSlipOnCrc(void) 
{
    static const U4     u4_s_TTSLIP_CRC    = (U4)0xCAFA5FAA;

    return(u4_s_TTSLIP_CRC);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgVscoffReq(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgVscoffReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_tt_vscoff;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_vscoff     = (U1)((u4_sp_asilchk_hmitt_buf[0] >> 16) & 0x0000000f);
    if(u1_t_tt_vscoff == (U1)HMITT_BLINK_CO_ON_____100P){
        u1_t_req       = (U1)ASILCHK_REQ_ASIL_LIGHT;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgVscoffOnCrc(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgVscoffOnCrc(void) 
{
    static const U4     u4_s_TTVSCOFF_CRC    = (U4)0x32D75613;

    return(u4_s_TTVSCOFF_CRC);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgAddotttReq(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgAddotttReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_tt_addottt;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_addottt     = (U1)(u4_sp_asilchk_hmitt_buf[1] & 0x0000000f);
    if(u1_t_tt_addottt == (U1)HMITT_BLINK_CO_ON_____100P){
        u1_t_req        = (U1)ASILCHK_REQ_ASIL_LIGHT;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgAddotttOnCrc(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgAddotttOnCrc(void) 
{
    static const U4     u4_s_TTADDOTTT_CRC    = (U4)0x5E258A55;

    return(u4_s_TTADDOTTT_CRC);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgBrkReq(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgBrkReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_tt_brk;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_brk     = (U1)((u4_sp_asilchk_hmitt_buf[0] >> 28) & 0x0000000f);
    if(u1_t_tt_brk == (U1)HMITT_BLINK_CO_ON_____100P){
        u1_t_req    = (U1)ASILCHK_REQ_ASIL_LIGHT;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgBrkOnCrc(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgBrkOnCrc(void) 
{
    static const U4     u4_s_TTBRAKE_CRC_NA    = (U4)0x6E9EA782;
    static const U4     u4_s_TTBRAKE_CRC_OTHER = (U4)0xF3FDB466;
    U4                  u4_t_crc;
    U1                  u1_t_dest;

    u1_t_dest = u1_g_VardefTtBrake();
    if(u1_t_dest == (U1)VDF_TTBRAKE_NO4){
        u4_t_crc = u4_s_TTBRAKE_CRC_NA;
    } else {
        u4_t_crc = u4_s_TTBRAKE_CRC_OTHER;
    }

    return(u4_t_crc);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AsilChkCfgEpsReq(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_req：telltale request status                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AsilChkCfgEpsReq(void) 
{
    U1  u1_t_req;
    U1  u1_t_tt_eps_red;
    U1  u1_t_tt_eps_amber;

    u1_t_req = (U1)ASILCHK_REQ_OFF;

    u1_t_tt_eps_red     = (U1)((u4_sp_asilchk_hmitt_buf[1] >> 4) & 0x0000000f);
    u1_t_tt_eps_amber   = (U1)((u4_sp_asilchk_hmitt_buf[1] >> 8) & 0x0000000f);
    if((u1_t_tt_eps_red   == (U1)HMITT_BLINK_CO_ON_____100P) || 
       (u1_t_tt_eps_amber == (U1)HMITT_BLINK_CO_ON_____100P)){
        u1_t_req        = (U1)ASILCHK_REQ_ASIL_LIGHT;
    }

    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U4    u4_s_AsilChkCfgEpsOnCrc(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_crc：crc value                                                                                              */
/*===================================================================================================================================*/
static U4    u4_s_AsilChkCfgEpsOnCrc(void) 
{
    static const U4     u4_s_TTEPSRED_CRC    = (U4)0x5D54F349;
    static const U4     u4_s_TTEPSAMBER_CRC  = (U4)0x58447B6A;
    U4                  u4_t_crc;
    U1                  u1_t_tt_eps_amber;

    u4_t_crc           = u4_s_TTEPSRED_CRC;

    u1_t_tt_eps_amber  = (U1)((u4_sp_asilchk_hmitt_buf[1] >> 8) & 0x0000000f);
    if(u1_t_tt_eps_amber == (U1)HMITT_BLINK_CO_ON_____100P){
        u4_t_crc       = u4_s_TTEPSAMBER_CRC;
    } 

    return(u4_t_crc);
}

/*===================================================================================================================================*/
/*  void    vd_g_AsilChkCfgCrcFailAct(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AsilChkCfgCrcFailAct(void)
{
    static const U4     u4_s_TX_SPIFAIL_NG  = (U4)1U;
    U4                  u4_t_tx_data;
    U1                  u1_t_calib_flg;

    u1_t_calib_flg    = u1_CALIB_MCUIDXXXX_DAV_ACT;
    if(u1_t_calib_flg == (U1)ASILCHK_DAV_ACT_FLG_ON){
        /* Abnormal process of CRC value unmatch */
        u4_t_tx_data = u4_s_TX_SPIFAIL_NG;
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM1TO3_SPI_FAIL, &u4_t_tx_data, (U2)ASILCHK_VM_1WORD);
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_AsilChkCfgAliveCntFailAct(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AsilChkCfgAliveCntFailAct(void)
{
    static const U4     u4_s_TX_SPIFAIL_NG  = (U4)1U;
    U4                  u4_t_tx_data;
    U1                  u1_t_calib_flg;

    u1_t_calib_flg    = u1_CALIB_MCUIDXXXX_DAV_ACT;
    if(u1_t_calib_flg == (U1)ASILCHK_DAV_ACT_FLG_ON){
        /* Abnormal process of Alive Counter */
        u4_t_tx_data = u4_s_TX_SPIFAIL_NG;
        vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM1TO3_SPI_FAIL, &u4_t_tx_data, (U2)ASILCHK_VM_1WORD);
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    04/08/2026  KO       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    04/08/2026  KO       New.                                                                                               */
/*                                                                                                                                   */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
