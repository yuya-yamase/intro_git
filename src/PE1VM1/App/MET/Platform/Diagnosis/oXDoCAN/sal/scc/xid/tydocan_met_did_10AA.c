/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* TyDoCAN Service Application Layer / DID 0x10AA                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_MET_DID_10AA_C_MAJOR             (1)
#define TYDOCAN_MET_DID_10AA_C_MINOR             (0)
#define TYDOCAN_MET_DID_10AA_C_PATCH             (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "tydocan_sal.h"
#include "oxdocan_saif.h"

#include "mcst.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define        TYDC_10AA_L1_NBYTE           (8U)
#define        TYDC_10AA_L2_NBYTE           (4U)

#define        TYDC_10AA_L2_LFT_B08         (8U)
#define        TYDC_10AA_L2_RHT_B12         (12U)
#define        TYDC_10AA_L1_LFT_B16         (16U)
#define        TYDC_10AA_L1_LFT_B17         (17U)
#define        TYDC_10AA_L1_LFT_B18         (18U)
#define        TYDC_10AA_L1_RHT_B19         (19U)
#define        TYDC_10AA_L1_RHT_B20         (20U)
#define        TYDC_10AA_L1_RHT_B21         (21U)

#define        TYDC_10AA_AUD_MODE           (0x01U)
#define        TYDC_10AA_AUD_PWR            (0x02U)
#define        TYDC_10AA_AUD_SEEK           (0x03U)
#define        TYDC_10AA_AUD_VOL            (0x04U)
#define        TYDC_10AA_AUD_TEL            (0x05U)
#define        TYDC_10AA_AUD_VR             (0x06U)
#define        TYDC_10AA_AC_TEMP            (0x07U)
#define        TYDC_10AA_AC_AIR             (0x08U)
#define        TYDC_10AA_AC_INOUT           (0x09U)
#define        TYDC_10AA_AC_DIR             (0x0AU)
#define        TYDC_10AA_AC_AUTO            (0x0BU)
#define        TYDC_10AA_AC_OFF             (0x0CU)
#define        TYDC_10AA_AC_ON              (0x0DU)
#define        TYDC_10AA_MET_DISP           (0x0EU)
#define        TYDC_10AA_HUD_POS            (0x0FU)
#define        TYDC_10AA_HUD_DIM            (0x10U)
#define        TYDC_10AA_HUD_ONOFF          (0x2BU)
#define        TYDC_10AA_HUD_MODE           (0x2CU)
#define        TYDC_10AA_DRV_NORMAL         (0x11U)
#define        TYDC_10AA_DRV_SPORT          (0x12U)
#define        TYDC_10AA_DRV_SPORT_S        (0x13U)
#define        TYDC_10AA_DRV_SPORT_S_P      (0x14U)
#define        TYDC_10AA_DRV_ECO            (0x15U)
#define        TYDC_10AA_DRV_COMFORT        (0x16U)
#define        TYDC_10AA_DRV_CUSTOM         (0x17U)
#define        TYDC_10AA_DRV_PWR            (0x18U)
#define        TYDC_10AA_DRV_SNOW           (0x19U)
#define        TYDC_10AA_EV_HV              (0x1AU)
#define        TYDC_10AA_EV_CHG             (0x1BU)
#define        TYDC_10AA_EV_PHV             (0x1CU)
#define        TYDC_10AA_CRS_MAIN           (0x1DU)
#define        TYDC_10AA_CRS_LTA            (0x1EU)
#define        TYDC_10AA_CRS_RES            (0x1FU)
#define        TYDC_10AA_CRS_PLUS           (0x20U)
#define        TYDC_10AA_CRS_SET            (0x21U)
#define        TYDC_10AA_CRS_MIN            (0x22U)
#define        TYDC_10AA_CRS_DIST           (0x23U)
#define        TYDC_10AA_CRS_MODE           (0x24U)
#define        TYDC_10AA_CRS_CANCEL         (0x25U)
#define        TYDC_10AA_MSC_PVM            (0x26U)
#define        TYDC_10AA_MSC_MTM            (0x27U)
#define        TYDC_10AA_MSC_SDM            (0x28U)
#define        TYDC_10AA_MSC_SS             (0x29U)
#define        TYDC_10AA_MSC_MORE           (0x2AU)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1        u1_mcst;
    U1        u1_id;
}ST_TYDC_10AA_ID;

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
/*  U1      u1_g_oXDoCANDidSup_10AA(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_10AA(void)
{
    return((U1)OXDC_XID_SUP_PRI);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_10AA(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_10AA(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    static const U1 u1_sp_TYDC_10AA_L1[TYDC_10AA_L1_NBYTE] = {
        (U1)TYDC_10AA_AUD_TEL ,          /* TEL      */
        (U1)TYDC_10AA_AUD_VR  ,          /* VR       */
        (U1)TYDC_10AA_AUD_SEEK,          /* SEEKUP   */
        (U1)TYDC_10AA_AUD_SEEK,          /* SEEKDOWN */

        (U1)TYDC_10AA_CRS_RES ,          /* RES      */
        (U1)TYDC_10AA_CRS_SET ,          /* SET      */
        (U1)TYDC_10AA_CRS_DIST,          /* DISTANCE */
        (U1)TYDC_10AA_CRS_CANCEL         /* CANCEL   */
    };

    static const U1 u1_sp_TYDC_L2_ID_LFT[TYDC_10AA_L2_NBYTE] = {
        (U1)MCST_BFI_STSWLH_UP   , 
        (U1)MCST_BFI_STSWLH_DOWN ,
        (U1)MCST_BFI_STSWLH_LEFT ,
        (U1)MCST_BFI_STSWLH_RIGHT
    };

    static const U1 u1_sp_TYDC_L2_ID_RHT[TYDC_10AA_L2_NBYTE] = {
        (U1)MCST_BFI_STSWRH_UP   , 
        (U1)MCST_BFI_STSWRH_DOWN , 
        (U1)MCST_BFI_STSWRH_LEFT , 
        (U1)MCST_BFI_STSWRH_RIGHT     
    };

    static const ST_TYDC_10AA_ID st_sp_TYDC_10AA_L2_LFT[] = {
        /* u1_mcst,                              u1_id                      */   
        { (U1)MCST_STSWLH_UP_AUDIO_SEL      ,    (U1)TYDC_10AA_AUD_MODE     },
        { (U1)MCST_STSWLH_UP_AUDIO_PWR      ,    (U1)TYDC_10AA_AUD_PWR      },
        { (U1)MCST_STSWLH_UP_TMP_SET        ,    (U1)TYDC_10AA_AC_TEMP      },
        { (U1)MCST_STSWLH_UP_AIRCDT_INOUT   ,    (U1)TYDC_10AA_AC_INOUT     },
        { (U1)MCST_STSWLH_UP_AIRCDT_OUTLET  ,    (U1)TYDC_10AA_AC_DIR       },
        { (U1)MCST_STSWLH_UP_AIRCDT_AUTO    ,    (U1)TYDC_10AA_AC_AUTO      },
        { (U1)MCST_STSWLH_UP_AIRCDT_OFF     ,    (U1)TYDC_10AA_AC_OFF       },
        { (U1)MCST_STSWLH_UP_AIRCDT_ON      ,    (U1)TYDC_10AA_AC_ON        }
    };
    static const U1 u1_s_TYDC_NUM_L2_LFT = ((U1)sizeof(st_sp_TYDC_10AA_L2_LFT) / (U1)sizeof(ST_TYDC_10AA_ID));

    static const ST_TYDC_10AA_ID st_sp_TYDC_10AA_L2_RHT[] = {
        /* u1_mcst,                              u1_id                      */   
        { (U1)MCST_STSWRH_UP_DRVMODE_NMR    ,   (U1)TYDC_10AA_DRV_NORMAL    },
        { (U1)MCST_STSWRH_UP_DRVMODE_SPRT   ,   (U1)TYDC_10AA_DRV_SPORT     },
        { (U1)MCST_STSWRH_UP_DRVMODE_SPRT_S ,   (U1)TYDC_10AA_DRV_SPORT_S   },
        { (U1)MCST_STSWRH_UP_DRVMODE_SPRT_SP,   (U1)TYDC_10AA_DRV_SPORT_S_P },
        { (U1)MCST_STSWRH_UP_DRVMODE_ECO    ,   (U1)TYDC_10AA_DRV_ECO       },
        { (U1)MCST_STSWRH_UP_DRVMODE_CMFRT  ,   (U1)TYDC_10AA_DRV_COMFORT   },
        { (U1)MCST_STSWRH_UP_DRVMODE_CSTM   ,   (U1)TYDC_10AA_DRV_CUSTOM    },
        { (U1)MCST_STSWRH_UP_DRVMODE_PWR    ,   (U1)TYDC_10AA_DRV_PWR       },
        { (U1)MCST_STSWRH_UP_SNOWMODE       ,   (U1)TYDC_10AA_DRV_SNOW      },
        { (U1)MCST_STSWRH_UP_PNRM_VIEWMONI  ,   (U1)TYDC_10AA_MSC_PVM       },
        { (U1)MCST_STSWRH_UP_MLT_TRRNMONI   ,   (U1)TYDC_10AA_MSC_MTM       },
        { (U1)MCST_STSWRH_UP_SIDEMONI       ,   (U1)TYDC_10AA_MSC_SDM       },
        { (U1)MCST_STSWRH_UP_STP_STRT       ,   (U1)TYDC_10AA_MSC_SS        },
        { (U1)MCST_STSWRH_LEFT_MET_DSP      ,   (U1)TYDC_10AA_MET_DISP      },
        { (U1)MCST_STSWRH_UP_HUDPOS         ,   (U1)TYDC_10AA_HUD_POS       },
        { (U1)MCST_STSWRH_LEFT_HUDILL       ,   (U1)TYDC_10AA_HUD_DIM       },
        { (U1)MCST_STSWRH_UP_HUD_ONOFF      ,   (U1)TYDC_10AA_HUD_ONOFF     },
        { (U1)MCST_STSWRH_UP_HUD_MODE       ,   (U1)TYDC_10AA_HUD_MODE      }
    };
    static const U1 u1_s_TYDC_NUM_L2_RHT = ((U1)sizeof(st_sp_TYDC_10AA_L2_RHT) / (U1)sizeof(ST_TYDC_10AA_ID));
    U4      u4_t_lpcnt;
    U4      u4_t_idx;
    U1      u1_bf;

    /* LAYER 1 */
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_10AA_L1_NBYTE; u4_t_lpcnt++){
        u1_ap_ans[u4_t_lpcnt] = u1_sp_TYDC_10AA_L1[u4_t_lpcnt];
    }
    
    /* LAYER 2 */
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_10AA_L2_NBYTE; u4_t_lpcnt++){

        u1_ap_ans[u4_t_lpcnt + (U4)TYDC_10AA_L2_LFT_B08] = (U1)0U;
        u1_ap_ans[u4_t_lpcnt + (U4)TYDC_10AA_L2_RHT_B12] = (U1)0U;

        u4_t_idx = (U4)0U;
        u1_bf    = u1_g_McstBf(u1_sp_TYDC_L2_ID_LFT[u4_t_lpcnt]);
        while(u4_t_idx < (U4)u1_s_TYDC_NUM_L2_LFT){
            if(u1_bf == st_sp_TYDC_10AA_L2_LFT[u4_t_idx].u1_mcst){
                u1_ap_ans[u4_t_lpcnt + (U4)TYDC_10AA_L2_LFT_B08] = st_sp_TYDC_10AA_L2_LFT[u4_t_idx].u1_id;
                break;
            }
            u4_t_idx++;
        }

        u4_t_idx = (U4)0U;
        u1_bf    = u1_g_McstBf(u1_sp_TYDC_L2_ID_RHT[u4_t_lpcnt]);
        while(u4_t_idx < (U4)u1_s_TYDC_NUM_L2_RHT){
            if(u1_bf == st_sp_TYDC_10AA_L2_RHT[u4_t_idx].u1_mcst){
                u1_ap_ans[u4_t_lpcnt + (U4)TYDC_10AA_L2_RHT_B12] = st_sp_TYDC_10AA_L2_RHT[u4_t_idx].u1_id;
                break;
            }
            u4_t_idx++;
        }
    }

    /* MISC */
    u1_ap_ans[TYDC_10AA_L1_LFT_B16] = (U1)TYDC_10AA_AUD_VOL;
    u1_ap_ans[TYDC_10AA_L1_LFT_B17] = (U1)TYDC_10AA_AUD_VOL;
    u1_ap_ans[TYDC_10AA_L1_LFT_B18] = (U1)TYDC_10AA_MSC_MORE;
    u1_ap_ans[TYDC_10AA_L1_RHT_B19] = (U1)TYDC_10AA_CRS_MAIN;
    u1_ap_ans[TYDC_10AA_L1_RHT_B20] = (U1)TYDC_10AA_CRS_LTA;
    u1_ap_ans[TYDC_10AA_L1_RHT_B21] = (U1)TYDC_10AA_MSC_MORE;

    return((U1)OXDC_SAL_PROC_FIN);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     8/03/2020  AS       New.                                                                                               */
/*                                                                                                                                   */
/*  * AS = Atsunori Sugita, DENSO-TECHNO                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
