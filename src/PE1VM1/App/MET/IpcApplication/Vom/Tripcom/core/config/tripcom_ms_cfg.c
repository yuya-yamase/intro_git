/* 2.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Trip Computer                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_MS_CFG_C_MAJOR                  (2)
#define TRIPCOM_MS_CFG_C_MINOR                  (2)
#define TRIPCOM_MS_CFG_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_ms_cfg_private.h"
#include "rim_ctl.h"
#if 0   /* BEV Rebase provisionally */
#include "es_inspect.h"
#endif   /* BEV Rebase provisionally */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPCOM_MS_CFG_C_MAJOR != TRIPCOM_MS_CFG_H_MAJOR) || \
     (TRIPCOM_MS_CFG_C_MINOR != TRIPCOM_MS_CFG_H_MINOR) || \
     (TRIPCOM_MS_CFG_C_PATCH != TRIPCOM_MS_CFG_H_PATCH))
#error "tripcom_ms_cfg.c and tripcom_ms_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
static U1   u1_s_TripcomMsNvmcRead(const U2 u2_a_NVMCID, U4 * u4p_a_value);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const           ST_TRIPCOM_MS_MEM               st_gp_TRIPCOM_MS_MEM_CFG[TRIPCOM_MS_NUM_ID]     = {
    {   (U2)RIMID_U4_TRIPCOM_AVGEE_TA_EE,       (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  00 TRIPCOM_MS_ID_AVGEE_TA_EE         */
    {   (U2)NVMCID_U4_TOEC_EU,                  (U1)TRIPCOM_MS_DEV_NVM      },                  /*  01 TRIPCOM_MS_ID_AVGEE_TA_EU         */
    {   (U2)NVMCID_U4_TOEC_OC,                  (U1)TRIPCOM_MS_DEV_NVM      },                  /*  02 TRIPCOM_MS_ID_AVGEE_TA_OC         */
    {   (U2)RIMID_U4_TRIPCOM_AVGEE_DC_EE,       (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  03 TRIPCOM_MS_ID_AVGEE_DC_EE         */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  04 TRIPCOM_MS_ID_AVGEE_DC_EU         */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  05 TRIPCOM_MS_ID_AVGEE_DC_OC         */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  06 TRIPCOM_MS_ID_AVGEE_ONEM_EE       */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  07 TRIPCOM_MS_ID_AVGEE_ONEM_EU       */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  08 TRIPCOM_MS_ID_AVGEE_ONEM_OC       */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  09 TRIPCOM_MS_ID_AVGEE_FIVEM_EE      */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  10 TRIPCOM_MS_ID_AVGEE_FIVEM_EU      */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  11 TRIPCOM_MS_ID_AVGEE_FIVEM_OC      */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  12 TRIPCOM_MS_ID_INSTEE_EE           */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  13 TRIPCOM_MS_ID_INSTEE_EU           */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  14 TRIPCOM_MS_ID_INSTEE_OC           */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  15 TRIPCOM_MS_ID_INSTEE_DV           */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  16 TRIPCOM_MS_ID_EVDTE_OC            */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  17 TRIPCOM_MS_ID_EVDTE_PCT           */
    {   (U2)RIMID_U4_TRIPCOM_AVGVEHSPD_TA_SP,   (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  18 TRIPCOM_MS_ID_AVGVEHSPD_TA_SP     */
    {   (U2)NVMCID_U4_TOSP_OC,                  (U1)TRIPCOM_MS_DEV_NVM      },                  /*  19 TRIPCOM_MS_ID_AVGVEHSPD_TA_OC     */
    {   (U2)NVMCID_U4_TOSP_ET,                  (U1)TRIPCOM_MS_DEV_NVM      },                  /*  20 TRIPCOM_MS_ID_AVGVEHSPD_TA_ET     */
    {   (U2)RIMID_U4_TRIPCOM_AVGVEHSPD_DC_SP,   (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  21 TRIPCOM_MS_ID_AVGVEHSPD_DC_SP     */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  22 TRIPCOM_MS_ID_AVGVEHSPD_DC_OC     */
    {   (U2)U2_MAX,                             (U1)0xFFU                   },                  /*  23 TRIPCOM_MS_ID_AVGVEHSPD_DC_ET     */
    {   (U2)RIMID_U4_TRIPCOM_AVGSPD_TR_A_SP,    (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  24 TRIPCOM_MS_ID_AVGVEHSPD_TR_A_SP   */
    {   (U2)NVMCID_U4_TR_A_SP_OC,               (U1)TRIPCOM_MS_DEV_NVM      },                  /*  25 TRIPCOM_MS_ID_AVGVEHSPD_TR_A_OC   */
    {   (U2)NVMCID_U4_TR_A_SP_ET,               (U1)TRIPCOM_MS_DEV_NVM      },                  /*  26 TRIPCOM_MS_ID_AVGVEHSPD_TR_A_ET   */
    {   (U2)RIMID_U4_TRIPCOM_AVGSPD_TR_B_SP,    (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  27 TRIPCOM_MS_ID_AVGVEHSPD_TR_B_SP   */
    {   (U2)NVMCID_U4_TR_B_SP_OC,               (U1)TRIPCOM_MS_DEV_NVM      },                  /*  28 TRIPCOM_MS_ID_AVGVEHSPD_TR_B_OC   */
    {   (U2)NVMCID_U4_TR_B_SP_ET,               (U1)TRIPCOM_MS_DEV_NVM      },                  /*  29 TRIPCOM_MS_ID_AVGVEHSPD_TR_B_ET   */
    {   (U2)NVMCID_U4_TOTM_ET,                  (U1)TRIPCOM_MS_DEV_NVM      },                  /*  30 TRIPCOM_MS_ID_PTSRUNTM_LC_ET      */
    {   (U2)RIMID_U4_TRIPCOM_PTSRUNTM_DC_ET,    (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  31 TRIPCOM_MS_ID_PTSRUNTM_DC_ET      */
    {   (U2)NVMCID_U4_TR_A_TM_ET,               (U1)TRIPCOM_MS_DEV_NVM      },                  /*  32 TRIPCOM_MS_ID_PTSRUNTM_TR_A_ET    */
    {   (U2)NVMCID_U4_TR_B_TM_ET,               (U1)TRIPCOM_MS_DEV_NVM      },                  /*  33 TRIPCOM_MS_ID_PTSRUNTM_TR_B_ET    */
    {   (U2)NVMCID_U4_TODT_OC,                  (U1)TRIPCOM_MS_DEV_NVM      },                  /*  34 TRIPCOM_MS_ID_PTSRUNDIST_LC_OC    */
    {   (U2)RIMID_U4_TRIPCOM_PTSRUNDIST_DC_OC,  (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  35 TRIPCOM_MS_ID_PTSRUNDIST_DC_OC    */
    {   (U2)NVMCID_U4_TR_A_DT_OC,               (U1)TRIPCOM_MS_DEV_NVM      },                  /*  36 TRIPCOM_MS_ID_PTSRUNDIST_TR_A_OC  */
    {   (U2)NVMCID_U4_TR_B_DT_OC,               (U1)TRIPCOM_MS_DEV_NVM      },                  /*  37 TRIPCOM_MS_ID_PTSRUNDIST_TR_B_OC  */
    {   (U2)NVMCID_OTR_GRPH_TAEE_ECON,          (U1)TRIPCOM_MS_DEV_NVM_O    },                  /*  38 TRIPCOM_MS_ID_AVGGRPH_TAEE_ECON   */
    {   (U2)NVMCID_OTR_GRPH_TAEE_DATE,          (U1)TRIPCOM_MS_DEV_NVM_O    },                  /*  39 TRIPCOM_MS_ID_AVGGRPH_TAEE_DATE   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE00,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  40 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE00   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE01,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  41 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE01   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE02,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  42 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE02   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE03,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  43 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE03   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE04,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  44 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE04   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE05,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  45 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE05   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE06,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  46 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE06   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE07,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  47 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE07   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE08,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  48 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE08   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE09,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  49 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE09   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE10,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  50 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE10   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE11,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  51 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE11   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE12,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  52 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE12   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE13,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  53 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE13   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE14,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  54 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE14   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE15,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  55 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE15   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE16,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  56 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE16   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE17,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  57 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE17   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE18,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  58 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE18   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE19,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  59 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE19   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE20,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  60 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE20   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE21,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  61 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE21   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE22,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  62 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE22   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE23,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  63 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE23   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE24,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  64 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE24   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE25,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  65 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE25   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE26,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  66 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE26   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE27,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  67 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE27   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE28,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  68 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE28   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE29,         (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  69 TRIPCOM_MS_ID_AVGGRPH_1MEE_EE29   */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_LTST,         (U1)TRIPCOM_MS_DEV_BR_Z     }                   /*  70 TRIPCOM_MS_ID_AVGGRPH_1MEE_LTST   */
};

const           ST_TRIPCOM_MS_RDIF              st_gp_TRIPCOM_MS_RDIF[TRIPCOM_MS_NUM_DEV]       = {
    {   &u1_g_Rim_ReadU4withStatus    },
    {   &u1_g_Rim_ReadU4withStatus    },
    {   &u1_s_TripcomMsNvmcRead       },
    {   vdp_PTR_NA                    }
};
void            (* const                        fp_gp_TRIPCOM_MS_WRIF[TRIPCOM_MS_NUM_DEV])(const U2 u2_a_ID, const U4 u4_a_VALUE)  = {
    &vd_g_Rim_WriteU4,     /* TRIPCOM_MS_DEV_BR_Z  (0U) */
    &vd_g_Rim_WriteU4,     /* TRIPCOM_MS_DEV_BR_M  (1U) */
    &vd_g_Nvmc_WriteU4,    /* TRIPCOM_MS_DEV_NVM   (2U) */
    vdp_PTR_NA             /* TRIPCOM_MS_DEV_NVM_O (3U) */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* U1              u1_g_TripcomMsEsichk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomMsEsichk(void)
{
#if 0   /* BEV Rebase provisionally */
    return (u1_g_ESInspectMdBfield());
#else   /* BEV Rebase provisionally */
    return ((U1)0U);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/* static U1   u1_s_TripcomMsNvmcRead(const U2 u2_a_NVMCID, U4 * u4p_a_value)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_TripcomMsNvmcRead(const U2 u2_a_NVMCID, U4 * u4p_a_value)
{
    U1  u1_t_nvm_chk;
    U1  u1_t_nvm_sts;

    u1_t_nvm_sts = (U1)TRIPCOM_STSBIT_VALID;
    u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts(u2_a_NVMCID , u4p_a_value);
    if((u1_t_nvm_chk >= (U1)NVMC_STATUS_NG        ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_ERRCOMP   ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_CACHE_NG  )){
           u1_t_nvm_sts   = (U1)TRIPCOM_STSBIT_INVALID;
           (*u4p_a_value) = (U4)0U;
    }
    return(u1_t_nvm_sts);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    11/07/2018  HY       New.                                                                                               */
/*  1.0.1    03/11/2020  YA       Change for 800B CV                                                                                 */
/*  1.0.2    07/13/2020  YA       Delete Display Value Definition                                                                    */
/*                                Add Initial Value Selection                                                                        */
/*  1.0.3    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    07/28/2022  TA(M)    tripcom_ms.c v2.0.1 -> v2.0.2.                                                                     */
/*  2.0.3    07/28/2022  YI       tripcom_ms.c v2.0.2 -> v2.0.3.                                                                     */
/*  2.1.0    01/10/2024  TH       tripcom_ms.c v2.0.3 -> v2.1.0.                                                                     */
/*  2.1.1    06/24/2024  SM       tripcom_ms.c v2.1.0 -> v2.1.1.                                                                     */
/*  2.1.2    02/18/2025  MaO(M)   tripcom_ms.c v2.1.1 -> v2.1.2.                                                                     */
/*  2.2.0    02/19/2029  PG       tripcom_ms.c v2.1.3 -> v2.2.0.                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * SM   = Shota Maegawa, Denso Techno                                                                                             */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
