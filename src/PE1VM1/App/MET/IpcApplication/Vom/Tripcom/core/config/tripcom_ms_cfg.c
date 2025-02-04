/* 2.1.1 */
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
#define TRIPCOM_MS_CFG_C_MINOR                  (1)
#define TRIPCOM_MS_CFG_C_PATCH                  (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_ms_cfg_private.h"
#include "tripcom_nvmif_cfg_private.h"
#include "tripcom_nvmif_grph_cfg_private.h"
#include "tripcom_ms.h"
#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif
#if 0   /* BEV BSW provisionally */
#include "es_inspect.h"
#else
#include "es_inspect_STUB.h"
#endif

#include "dte_ed.h"

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
    {   (U2)RIMID_U4_TRIPCOM_AVGFE_TA_FE,           (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  00 TRIPCOM_MS_ID_AVGFE_TA_FE           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  01 TRIPCOM_MS_ID_AVGFE_TA_FU           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  02 TRIPCOM_MS_ID_AVGFE_TA_OC           */
    {   (U2)RIMID_U4_TRIPCOM_AVGFE_DC_FE,           (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  03 TRIPCOM_MS_ID_AVGFE_DC_FE           */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  04 TRIPCOM_MS_ID_AVGFE_DC_FU           */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  05 TRIPCOM_MS_ID_AVGFE_DC_OC           */
    {   (U2)RIMID_U4_TRIPCOM_AVGFE_RF_FE,           (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  06 TRIPCOM_MS_ID_AVGFE_RF_FE           */
    {   (U2)RIMID_U4_TRIPCOM_AVGFE_RF_FU,           (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  07 TRIPCOM_MS_ID_AVGFE_RF_FU           */
    {   (U2)RIMID_U4_TRIPCOM_AVGFE_RF_OC,           (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  08 TRIPCOM_MS_ID_AVGFE_RF_OC           */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  09 TRIPCOM_MS_ID_AVGFE_ONEM_FE         */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  10 TRIPCOM_MS_ID_AVGFE_ONEM_FU         */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  11 TRIPCOM_MS_ID_AVGFE_ONEM_OC         */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  12 TRIPCOM_MS_ID_AVGHE_TA_HE           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  13 TRIPCOM_MS_ID_AVGHE_TA_HU           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  14 TRIPCOM_MS_ID_AVGHE_TA_OC           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  15 TRIPCOM_MS_ID_AVGHE_DC_HE           */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  16 TRIPCOM_MS_ID_AVGHE_DC_HU           */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  17 TRIPCOM_MS_ID_AVGHE_DC_OC           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  18 TRIPCOM_MS_ID_AVGHE_RF_HE           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  19 TRIPCOM_MS_ID_AVGHE_RF_HU           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  20 TRIPCOM_MS_ID_AVGHE_RF_OC           */
    {   (U2)RIMID_U4_TRIPCOM_AVGEE_TA_EE,           (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  21 TRIPCOM_MS_ID_AVGEE_TA_EE           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  22 TRIPCOM_MS_ID_AVGEE_TA_EU           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  23 TRIPCOM_MS_ID_AVGEE_TA_OC           */
    {   (U2)RIMID_U4_TRIPCOM_AVGEE_DC_EE,           (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  24 TRIPCOM_MS_ID_AVGEE_DC_EE           */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  25 TRIPCOM_MS_ID_AVGEE_DC_EU           */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  26 TRIPCOM_MS_ID_AVGEE_DC_OC           */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  27 TRIPCOM_MS_ID_AVGEE_ONEM_EE         */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  28 TRIPCOM_MS_ID_AVGEE_ONEM_EU         */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  29 TRIPCOM_MS_ID_AVGEE_ONEM_OC         */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  30 TRIPCOM_MS_ID_AVGEE_FIVEM_EE        */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  31 TRIPCOM_MS_ID_AVGEE_FIVEM_EU        */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  32 TRIPCOM_MS_ID_AVGEE_FIVEM_OC        */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  33 TRIPCOM_MS_ID_INSTFE_FE             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  34 TRIPCOM_MS_ID_INSTFE_FU             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  35 TRIPCOM_MS_ID_INSTFE_OC             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  36 TRIPCOM_MS_ID_INSTFE_DV             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  37 TRIPCOM_MS_ID_INSTHE_HE             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  38 TRIPCOM_MS_ID_INSTHE_HU             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  39 TRIPCOM_MS_ID_INSTHE_OC             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  40 TRIPCOM_MS_ID_INSTHE_DV             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  41 TRIPCOM_MS_ID_INSTEE_EE             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  42 TRIPCOM_MS_ID_INSTEE_EU             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  43 TRIPCOM_MS_ID_INSTEE_OC             */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  44 TRIPCOM_MS_ID_INSTEE_DV             */
    {   (U2)RIMID_U4_TRIPCOM_DTE_OC,                (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  45 TRIPCOM_MS_ID_DTE_OC                */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  46 TRIPCOM_MS_ID_DTE_FE                */
    {   (U2)RIMID_U4_TRIPCOM_EVDTE_OC,              (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  47 TRIPCOM_MS_ID_EVDTE_OC              */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  48 TRIPCOM_MS_ID_EVDTE_PCT             */
    {   (U2)RIMID_U4_TRIPCOM_AVGVEHSPD_TA_SP,       (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  49 TRIPCOM_MS_ID_AVGVEHSPD_TA_SP       */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  50 TRIPCOM_MS_ID_AVGVEHSPD_TA_OC       */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  51 TRIPCOM_MS_ID_AVGVEHSPD_TA_ET       */
    {   (U2)RIMID_U4_TRIPCOM_AVGVEHSPD_DC_SP,       (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  52 TRIPCOM_MS_ID_AVGVEHSPD_DC_SP       */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  53 TRIPCOM_MS_ID_AVGVEHSPD_DC_OC       */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  54 TRIPCOM_MS_ID_AVGVEHSPD_DC_ET       */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  55 TRIPCOM_MS_ID_SAVEFS_LC_F           */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  56 TRIPCOM_MS_ID_SAVEFS_DC_F           */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  57 TRIPCOM_MS_ID_ECOSTPTM_LC_ET        */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  58 TRIPCOM_MS_ID_ECOSTPTM_DC_ET        */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  59 TRIPCOM_MS_ID_ECOSTPTM_ST_ET        */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  60 TRIPCOM_MS_ID_PTSRUNTM_LC_ET        */
    {   (U2)RIMID_U4_TRIPCOM_PTSRUNTM_DC_ET,        (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  61 TRIPCOM_MS_ID_PTSRUNTM_DC_ET        */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  62 TRIPCOM_MS_ID_PTSRUNDIST_LC_OC      */
    {   (U2)RIMID_U4_TRIPCOM_PTSRUNDIST_DC_OC,      (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  63 TRIPCOM_MS_ID_PTSRUNDIST_DC_OC      */
    {   (U2)RIMID_U4_TRIPCOM_EVRATIO_DT,            (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  64 TRIPCOM_MS_ID_EVRATIO_DT            */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  65 TRIPCOM_MS_ID_EVRATIO_DV            */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  66 TRIPCOM_MS_ID_EVRATIO_EV_ET         */
    {   (U2)U2_MAX,                                 (U1)0xFFU                   },                  /*  67 TRIPCOM_MS_ID_EVRATIO_NEV_ET        */
    {   (U2)RIMID_U4_TRIPCOM_AVGSPD_TR_A_SP,        (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  68 TRIPCOM_MS_ID_AVGVEHSPD_TR_A_SP     */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  69 TRIPCOM_MS_ID_AVGVEHSPD_TR_A_OC     */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  70 TRIPCOM_MS_ID_AVGVEHSPD_TR_A_ET     */
    {   (U2)RIMID_U4_TRIPCOM_AVGSPD_TR_B_SP,        (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  71 TRIPCOM_MS_ID_AVGVEHSPD_TR_B_SP     */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  72 TRIPCOM_MS_ID_AVGVEHSPD_TR_B_OC     */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  73 TRIPCOM_MS_ID_AVGVEHSPD_TR_B_ET     */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  74 TRIPCOM_MS_ID_PTSRUNTM_TR_A_ET      */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  75 TRIPCOM_MS_ID_PTSRUNTM_TR_B_ET      */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  76 TRIPCOM_MS_ID_PTSRUNDIST_TR_A_OC    */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  77 TRIPCOM_MS_ID_PTSRUNDIST_TR_B_OC    */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U1_CG_STS,      (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  78 TRIPCOM_MS_ID_DTE_ED_U1_CG_STS      */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  79 TRIPCOM_MS_ID_DTE_ED_U2_CRSCG       */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U4_SPDPLS_CG,   (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  80 TRIPCOM_MS_ID_DTE_ED_U4_SPDPLS_CG   */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U4_FCP_CG,      (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  81 TRIPCOM_MS_ID_DTE_ED_U4_FCP_CG      */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U4_CNSM_FUEL,   (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  82 TRIPCOM_MS_ID_DTE_ED_U4_CNSM_FUEL   */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U1_CRS_STS,     (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  83 TRIPCOM_MS_ID_DTE_ED_U1_CRS_STS     */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U4_KS_SPPLS,    (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  84 TRIPCOM_MS_ID_DTE_ED_U4_KS_SPPLS    */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U2_KH_1KM,      (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  85 TRIPCOM_MS_ID_DTE_ED_U2_KH_1KM      */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U2_KH_1MI,      (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  86 TRIPCOM_MS_ID_DTE_ED_U2_KH_1MI      */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U4_KF_SPPLS,    (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  87 TRIPCOM_MS_ID_DTE_ED_U4_KF_SPPLS    */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U2_KZ_10CC,     (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  88 TRIPCOM_MS_ID_DTE_ED_U2_KZ_10CC     */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U4_TC,          (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  89 TRIPCOM_MS_ID_DTE_ED_U4_TC          */
    {   (U2)RIMID_U4_TRIPCOM_DTE_ED_U2_BLWME_CNT,   (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  90 TRIPCOM_MS_ID_DTE_ED_U2_BLWME_CNT   */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  91 TRIPCOM_MS_ID_TAFE_FE00             */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  92 TRIPCOM_MS_ID_TAFE_FE01             */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  93 TRIPCOM_MS_ID_TAFE_FE02             */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  94 TRIPCOM_MS_ID_TAFE_FE03             */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  95 TRIPCOM_MS_ID_TAFE_FE04             */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  96 TRIPCOM_MS_ID_TAFE_FE05             */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  97 TRIPCOM_MS_ID_TAFE_DT00             */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  98 TRIPCOM_MS_ID_TAFE_DT01             */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  99 TRIPCOM_MS_ID_TAFE_DT02             */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  100 TRIPCOM_MS_ID_TAFE_DT03            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  101 TRIPCOM_MS_ID_TAFE_DT04            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  102 TRIPCOM_MS_ID_TAFE_DT05            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  103 TRIPCOM_MS_ID_TAFE_LTST            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  104 TRIPCOM_MS_ID_TAFE_MAX             */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE00,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  105 TRIPCOM_MS_ID_1MFE_FE00            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE01,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  106 TRIPCOM_MS_ID_1MFE_FE01            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE02,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  107 TRIPCOM_MS_ID_1MFE_FE02            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE03,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  108 TRIPCOM_MS_ID_1MFE_FE03            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE04,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  109 TRIPCOM_MS_ID_1MFE_FE04            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE05,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  110 TRIPCOM_MS_ID_1MFE_FE05            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE06,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  111 TRIPCOM_MS_ID_1MFE_FE06            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE07,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  112 TRIPCOM_MS_ID_1MFE_FE07            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE08,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  113 TRIPCOM_MS_ID_1MFE_FE08            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE09,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  114 TRIPCOM_MS_ID_1MFE_FE09            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE10,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  115 TRIPCOM_MS_ID_1MFE_FE10            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE11,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  116 TRIPCOM_MS_ID_1MFE_FE11            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE12,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  117 TRIPCOM_MS_ID_1MFE_FE12            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE13,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  118 TRIPCOM_MS_ID_1MFE_FE13            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE14,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  119 TRIPCOM_MS_ID_1MFE_FE14            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE15,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  120 TRIPCOM_MS_ID_1MFE_FE15            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE16,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  121 TRIPCOM_MS_ID_1MFE_FE16            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE17,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  122 TRIPCOM_MS_ID_1MFE_FE17            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE18,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  123 TRIPCOM_MS_ID_1MFE_FE18            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE19,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  124 TRIPCOM_MS_ID_1MFE_FE19            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE20,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  125 TRIPCOM_MS_ID_1MFE_FE20            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE21,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  126 TRIPCOM_MS_ID_1MFE_FE21            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE22,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  127 TRIPCOM_MS_ID_1MFE_FE22            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE23,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  128 TRIPCOM_MS_ID_1MFE_FE23            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE24,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  129 TRIPCOM_MS_ID_1MFE_FE24            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE25,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  130 TRIPCOM_MS_ID_1MFE_FE25            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE26,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  131 TRIPCOM_MS_ID_1MFE_FE26            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE27,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  132 TRIPCOM_MS_ID_1MFE_FE27            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE28,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  133 TRIPCOM_MS_ID_1MFE_FE28            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_FE29,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  134 TRIPCOM_MS_ID_1MFE_FE29            */
    {   (U2)RIMID_U4_TRIPCOM_1MFE_LTST,             (U1)TRIPCOM_MS_DEV_BR_Z     },                  /*  135 TRIPCOM_MS_ID_1MFE_LTST            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  136 TRIPCOM_MS_ID_TAEE_EE00            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  137 TRIPCOM_MS_ID_TAEE_EE01            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  138 TRIPCOM_MS_ID_TAEE_EE02            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  139 TRIPCOM_MS_ID_TAEE_EE03            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  140 TRIPCOM_MS_ID_TAEE_EE04            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  141 TRIPCOM_MS_ID_TAEE_EE05            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  142 TRIPCOM_MS_ID_TAEE_DT00            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  143 TRIPCOM_MS_ID_TAEE_DT01            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  144 TRIPCOM_MS_ID_TAEE_DT02            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  145 TRIPCOM_MS_ID_TAEE_DT03            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  146 TRIPCOM_MS_ID_TAEE_DT04            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  147 TRIPCOM_MS_ID_TAEE_DT05            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  148 TRIPCOM_MS_ID_TAEE_LTST            */
    {   (U2)U2_MAX,                                 (U1)TRIPCOM_MS_DEV_NVM      },                  /*  149 TRIPCOM_MS_ID_TAEE_MAX             */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE00,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  150 TRIPCOM_MS_ID_1MEE_EE00            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE01,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  151 TRIPCOM_MS_ID_1MEE_EE01            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE02,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  152 TRIPCOM_MS_ID_1MEE_EE02            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE03,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  153 TRIPCOM_MS_ID_1MEE_EE03            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE04,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  154 TRIPCOM_MS_ID_1MEE_EE04            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE05,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  155 TRIPCOM_MS_ID_1MEE_EE05            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE06,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  156 TRIPCOM_MS_ID_1MEE_EE06            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE07,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  157 TRIPCOM_MS_ID_1MEE_EE07            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE08,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  158 TRIPCOM_MS_ID_1MEE_EE08            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE09,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  159 TRIPCOM_MS_ID_1MEE_EE09            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE10,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  160 TRIPCOM_MS_ID_1MEE_EE10            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE11,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  161 TRIPCOM_MS_ID_1MEE_EE11            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE12,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  162 TRIPCOM_MS_ID_1MEE_EE12            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE13,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  163 TRIPCOM_MS_ID_1MEE_EE13            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE14,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  164 TRIPCOM_MS_ID_1MEE_EE14            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE15,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  165 TRIPCOM_MS_ID_1MEE_EE15            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE16,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  166 TRIPCOM_MS_ID_1MEE_EE16            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE17,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  167 TRIPCOM_MS_ID_1MEE_EE17            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE18,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  168 TRIPCOM_MS_ID_1MEE_EE18            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE19,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  169 TRIPCOM_MS_ID_1MEE_EE19            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE20,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  170 TRIPCOM_MS_ID_1MEE_EE20            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE21,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  171 TRIPCOM_MS_ID_1MEE_EE21            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE22,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  172 TRIPCOM_MS_ID_1MEE_EE22            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE23,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  173 TRIPCOM_MS_ID_1MEE_EE23            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE24,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  174 TRIPCOM_MS_ID_1MEE_EE24            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE25,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  175 TRIPCOM_MS_ID_1MEE_EE25            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE26,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  176 TRIPCOM_MS_ID_1MEE_EE26            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE27,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  177 TRIPCOM_MS_ID_1MEE_EE27            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE28,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  178 TRIPCOM_MS_ID_1MEE_EE28            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_EE29,             (U1)TRIPCOM_MS_DEV_BR_M     },                  /*  179 TRIPCOM_MS_ID_1MEE_EE29            */
    {   (U2)RIMID_U4_TRIPCOM_1MEE_LTST,             (U1)TRIPCOM_MS_DEV_BR_Z     }                   /*  180 TRIPCOM_MS_ID_1MEE_LTST            */
};


const           U1                              u1_gp_TRIPCOM_MS_CH2ID[TRIPCOM_NVMIF_CH_NUM]    = {
    (U1)TRIPCOM_MS_ID_AVGFE_TA_FU,                                                              /*  00 TRIPCOM_NVMIF_CH_TOFC_FU          */
    (U1)TRIPCOM_MS_ID_AVGFE_TA_OC,                                                              /*  01 TRIPCOM_NVMIF_CH_TOFC_OC          */
    (U1)TRIPCOM_MS_ID_AVGEE_TA_EU,                                                              /*  02 TRIPCOM_NVMIF_CH_TOEC_EU          */
    (U1)TRIPCOM_MS_ID_AVGEE_TA_OC,                                                              /*  03 TRIPCOM_NVMIF_CH_TOEC_OC          */
    (U1)TRIPCOM_MS_ID_DTE_FE,                                                                   /*  04 TRIPCOM_NVMIF_CH_DTE_FE           */
    (U1)TRIPCOM_MS_ID_AVGVEHSPD_TA_OC,                                                          /*  05 TRIPCOM_NVMIF_CH_TOSP_OC          */
    (U1)TRIPCOM_MS_ID_AVGVEHSPD_TA_ET,                                                          /*  06 TRIPCOM_NVMIF_CH_TOSP_ET          */
    (U1)TRIPCOM_MS_ID_PTSRUNTM_LC_ET,                                                           /*  07 TRIPCOM_NVMIF_CH_TOTM_ET          */
    (U1)TRIPCOM_MS_ID_PTSRUNDIST_LC_OC,                                                         /*  08 TRIPCOM_NVMIF_CH_TODT_OC          */
    (U1)TRIPCOM_MS_ID_AVGVEHSPD_TR_A_OC,                                                        /*  09 TRIPCOM_NVMIF_CH_TOSP_TR_A_SP_OC  */
    (U1)TRIPCOM_MS_ID_AVGVEHSPD_TR_A_ET,                                                        /*  10 TRIPCOM_NVMIF_CH_TOSP_TR_A_SP_ET  */
    (U1)TRIPCOM_MS_ID_AVGVEHSPD_TR_B_OC,                                                        /*  11 TRIPCOM_NVMIF_CH_TOSP_TR_B_SP_OC  */
    (U1)TRIPCOM_MS_ID_AVGVEHSPD_TR_B_ET,                                                        /*  12 TRIPCOM_NVMIF_CH_TOSP_TR_B_SP_ET  */
    (U1)TRIPCOM_MS_ID_PTSRUNTM_TR_A_ET,                                                         /*  13 TRIPCOM_NVMIF_CH_TOTM_TR_A_TM_ET  */
    (U1)TRIPCOM_MS_ID_PTSRUNTM_TR_B_ET,                                                         /*  14 TRIPCOM_NVMIF_CH_TOTM_TR_B_TM_ET  */
    (U1)TRIPCOM_MS_ID_PTSRUNDIST_TR_A_OC,                                                       /*  15 TRIPCOM_NVMIF_CH_TODT_TR_A_DT_OC  */
    (U1)TRIPCOM_MS_ID_PTSRUNDIST_TR_B_OC,                                                       /*  16 TRIPCOM_NVMIF_CH_TODT_TR_B_DT_OC  */
    (U1)TRIPCOM_MS_ID_DTE_ED_U2_CRSCG,                                                          /*  17 TRIPCOM_NVMIF_CH_DTE_ED_FE        */
    (U1)TRIPCOM_MS_ID_AVGGRPH_TAFE_LTST,                                                        /*  18 TRIPCOM_NVMIF_CH_TAFE_LTST        */
    (U1)TRIPCOM_MS_ID_AVGGRPH_TAFE_MAX,                                                         /*  19 TRIPCOM_NVMIF_CH_TAFE_MAX         */
    (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_LTST,                                                        /*  20 TRIPCOM_NVMIF_CH_TAEE_LTST        */
    (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_MAX                                                          /*  21 TRIPCOM_NVMIF_CH_TAEE_MAX         */
};

const           U1                              u1_gp_TRIPCOM_MS_GRPH_CH2ID[TRIPCOM_NVMIF_GRPH_CH_NUM]    = {
    (U1)TRIPCOM_MS_ID_AVGGRPH_TAFE_FE00,                                                        /*  0 TRIPCOM_NVMIF_CH_TAFE_FE           */
    (U1)TRIPCOM_MS_ID_AVGGRPH_TAFE_DT00,                                                        /*  1 TRIPCOM_NVMIF_CH_TAFE_DT           */
    (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_EE00,                                                        /*  2 TRIPCOM_NVMIF_CH_TAEE_EE           */
    (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_DT00                                                         /*  3 TRIPCOM_NVMIF_CH_TAEE_DT           */
};

const           ST_TRIPCOM_MS_RDIF              st_gp_TRIPCOM_MS_RDIF[TRIPCOM_MS_NUM_DEV]       = {
    {   &u1_g_Rim_ReadU4withStatus    },
    {   &u1_g_Rim_ReadU4withStatus    },
    {   &u1_s_TripcomMsNvmcRead       }
};
void            (* const                        fp_gp_TRIPCOM_MS_WRIF[TRIPCOM_MS_NUM_DEV])(const U2 u2_a_ID, const U4 u4_a_VALUE)  = {
    &vd_g_Rim_WriteU4,   /* TRIPCOM_MS_DEV_BR_Z (0U) */
    &vd_g_Rim_WriteU4,   /* TRIPCOM_MS_DEV_BR_M (1U) */
    &vd_g_Nvmc_WriteU4   /* TRIPCOM_MS_DEV_NVM  (2U) */
};

static const    U2               u2_sp_TRIPCOM_MS_DTF_BLOCK[]    = {
    /*  00 TRIPCOM_NVMIF_CH_TOFC_FU          */
    (U2)NVMC_BLOCKID_DTF_TOFC_FU_00,
    (U2)NVMC_BLOCKID_DTF_TOFC_FU_01,
    (U2)NVMC_BLOCKID_DTF_TOFC_FU_02,
    (U2)NVMC_BLOCKID_DTF_TOFC_FU_03,
    (U2)NVMC_BLOCKID_DTF_TOFC_FU_04,
    (U2)NVMC_BLOCKID_DTF_TOFC_FU_05,

    /*  01 TRIPCOM_NVMIF_CH_TOFC_OC          */
    (U2)NVMC_BLOCKID_DTF_TOFC_OC_00,
    (U2)NVMC_BLOCKID_DTF_TOFC_OC_01,
    (U2)NVMC_BLOCKID_DTF_TOFC_OC_02,
    (U2)NVMC_BLOCKID_DTF_TOFC_OC_03,
    (U2)NVMC_BLOCKID_DTF_TOFC_OC_04,
    (U2)NVMC_BLOCKID_DTF_TOFC_OC_05,

    /*  02 TRIPCOM_NVMIF_CH_TOEC_EU          */
    (U2)NVMC_BLOCKID_DTF_TOEC_EU_00,
    (U2)NVMC_BLOCKID_DTF_TOEC_EU_01,
    (U2)NVMC_BLOCKID_DTF_TOEC_EU_02,
    (U2)NVMC_BLOCKID_DTF_TOEC_EU_03,
    (U2)NVMC_BLOCKID_DTF_TOEC_EU_04,
    (U2)NVMC_BLOCKID_DTF_TOEC_EU_05,

    /*  03 TRIPCOM_NVMIF_CH_TOEC_OC          */
    (U2)NVMC_BLOCKID_DTF_TOEC_OC_00,
    (U2)NVMC_BLOCKID_DTF_TOEC_OC_01,
    (U2)NVMC_BLOCKID_DTF_TOEC_OC_02,
    (U2)NVMC_BLOCKID_DTF_TOEC_OC_03,
    (U2)NVMC_BLOCKID_DTF_TOEC_OC_04,
    (U2)NVMC_BLOCKID_DTF_TOEC_OC_05,

    /*  04 TRIPCOM_NVMIF_CH_DTE_FE           */
    (U2)NVMC_BLOCKID_DTF_RNGE_FE_00,
    (U2)NVMC_BLOCKID_DTF_RNGE_FE_01,
    (U2)NVMC_BLOCKID_DTF_RNGE_FE_02,
    (U2)NVMC_BLOCKID_DTF_RNGE_FE_03,
    (U2)NVMC_BLOCKID_DTF_RNGE_FE_04,
    (U2)NVMC_BLOCKID_DTF_RNGE_FE_05,

    /*  05 TRIPCOM_NVMIF_CH_TOSP_OC          */
    (U2)NVMC_BLOCKID_DTF_TOSP_OC_00,
    (U2)NVMC_BLOCKID_DTF_TOSP_OC_01,
    (U2)NVMC_BLOCKID_DTF_TOSP_OC_02,
    (U2)NVMC_BLOCKID_DTF_TOSP_OC_03,
    (U2)NVMC_BLOCKID_DTF_TOSP_OC_04,
    (U2)NVMC_BLOCKID_DTF_TOSP_OC_05,

    /*  06 TRIPCOM_NVMIF_CH_TOSP_ET          */
    (U2)NVMC_BLOCKID_DTF_TOSP_ET_00,
    (U2)NVMC_BLOCKID_DTF_TOSP_ET_01,
    (U2)NVMC_BLOCKID_DTF_TOSP_ET_02,
    (U2)NVMC_BLOCKID_DTF_TOSP_ET_03,
    (U2)NVMC_BLOCKID_DTF_TOSP_ET_04,
    (U2)NVMC_BLOCKID_DTF_TOSP_ET_05,

    /*  07 TRIPCOM_NVMIF_CH_TOTM_ET          */
    (U2)NVMC_BLOCKID_DTF_TOTM_ET_00,
    (U2)NVMC_BLOCKID_DTF_TOTM_ET_01,
    (U2)NVMC_BLOCKID_DTF_TOTM_ET_02,
    (U2)NVMC_BLOCKID_DTF_TOTM_ET_03,
    (U2)NVMC_BLOCKID_DTF_TOTM_ET_04,
    (U2)NVMC_BLOCKID_DTF_TOTM_ET_05,

    /*  08 TRIPCOM_NVMIF_CH_TODT_OC          */
    (U2)NVMC_BLOCKID_DTF_TODT_OC_00,
    (U2)NVMC_BLOCKID_DTF_TODT_OC_01,
    (U2)NVMC_BLOCKID_DTF_TODT_OC_02,
    (U2)NVMC_BLOCKID_DTF_TODT_OC_03,
    (U2)NVMC_BLOCKID_DTF_TODT_OC_04,
    (U2)NVMC_BLOCKID_DTF_TODT_OC_05,

    /*  09 TRIPCOM_NVMIF_CH_TOSP_TR_A_SP_OC       */
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_OC_00,
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_OC_01,
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_OC_02,
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_OC_03,
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_OC_04,
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_OC_05,

    /*  10 TRIPCOM_NVMIF_CH_TOSP_TR_A_SP_ET       */
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_ET_00,
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_ET_01,
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_ET_02,
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_ET_03,
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_ET_04,
    (U2)NVMC_BLOCKID_DTF_TR_A_SP_ET_05,

    /*  11 TRIPCOM_NVMIF_CH_TOSP_TR_B_SP_OC       */
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_OC_00,
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_OC_01,
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_OC_02,
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_OC_03,
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_OC_04,
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_OC_05,

    /*  12 TRIPCOM_NVMIF_CH_TOSP_TR_B_SP_ET       */
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_ET_00,
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_ET_01,
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_ET_02,
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_ET_03,
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_ET_04,
    (U2)NVMC_BLOCKID_DTF_TR_B_SP_ET_05,

    /*  13 TRIPCOM_NVMIF_CH_TOTM_TR_A_TM_ET       */
    (U2)NVMC_BLOCKID_DTF_TR_A_TM_ET_00,
    (U2)NVMC_BLOCKID_DTF_TR_A_TM_ET_01,
    (U2)NVMC_BLOCKID_DTF_TR_A_TM_ET_02,
    (U2)NVMC_BLOCKID_DTF_TR_A_TM_ET_03,
    (U2)NVMC_BLOCKID_DTF_TR_A_TM_ET_04,
    (U2)NVMC_BLOCKID_DTF_TR_A_TM_ET_05,

    /*  14 TRIPCOM_NVMIF_CH_TOTM_TR_B_TM_ET       */
    (U2)NVMC_BLOCKID_DTF_TR_B_TM_ET_00,
    (U2)NVMC_BLOCKID_DTF_TR_B_TM_ET_01,
    (U2)NVMC_BLOCKID_DTF_TR_B_TM_ET_02,
    (U2)NVMC_BLOCKID_DTF_TR_B_TM_ET_03,
    (U2)NVMC_BLOCKID_DTF_TR_B_TM_ET_04,
    (U2)NVMC_BLOCKID_DTF_TR_B_TM_ET_05,

    /*  15 TRIPCOM_NVMIF_CH_TODT_TR_A_DT_OC       */
    (U2)NVMC_BLOCKID_DTF_TR_A_DT_OC_00,
    (U2)NVMC_BLOCKID_DTF_TR_A_DT_OC_01,
    (U2)NVMC_BLOCKID_DTF_TR_A_DT_OC_02,
    (U2)NVMC_BLOCKID_DTF_TR_A_DT_OC_03,
    (U2)NVMC_BLOCKID_DTF_TR_A_DT_OC_04,
    (U2)NVMC_BLOCKID_DTF_TR_A_DT_OC_05,

    /*  16 TRIPCOM_NVMIF_CH_TODT_TR_B_DT_OC       */
    (U2)NVMC_BLOCKID_DTF_TR_B_DT_OC_00,
    (U2)NVMC_BLOCKID_DTF_TR_B_DT_OC_01,
    (U2)NVMC_BLOCKID_DTF_TR_B_DT_OC_02,
    (U2)NVMC_BLOCKID_DTF_TR_B_DT_OC_03,
    (U2)NVMC_BLOCKID_DTF_TR_B_DT_OC_04,
    (U2)NVMC_BLOCKID_DTF_TR_B_DT_OC_05,
    /*  17 TRIPCOM_NVMIF_CH_DTE_ED_FE             */
    (U2)NVMC_BLOCKID_DTF_RNGE_ED_FE_00,
    (U2)NVMC_BLOCKID_DTF_RNGE_ED_FE_01,
    (U2)NVMC_BLOCKID_DTF_RNGE_ED_FE_02,
    (U2)NVMC_BLOCKID_DTF_RNGE_ED_FE_03,
    (U2)NVMC_BLOCKID_DTF_RNGE_ED_FE_04,
    (U2)NVMC_BLOCKID_DTF_RNGE_ED_FE_05,
    /*  18 TRIPCOM_NVMIF_CH_TAFE_LTST             */
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_LTST_00,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_LTST_01,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_LTST_02,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_LTST_03,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_LTST_04,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_LTST_05,
    /*  19 TRIPCOM_NVMIF_CH_TAFE_MAX              */
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_MAX_00,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_MAX_01,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_MAX_02,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_MAX_03,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_MAX_04,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_MAX_05,
    /*  20 TRIPCOM_NVMIF_CH_TAEE_LTST             */
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_LTST_00,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_LTST_01,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_LTST_02,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_LTST_03,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_LTST_04,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_LTST_05,
    /*  21 TRIPCOM_NVMIF_CH_TAEE_MAX              */
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_MAX_00,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_MAX_01,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_MAX_02,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_MAX_03,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_MAX_04,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_MAX_05
};

const ST_TRIPCOM_NVMIF_REC_DATA  st_g_TRIPCOM_NVMIF_REC_DATA = {
    &u2_sp_TRIPCOM_MS_DTF_BLOCK[0],                                     /* u2p_BLOCK     */
    (U1)TRIPCOM_NVMIF_CH_NUM * (U1)TRIPCOM_NVMIF_NUM_REC,               /* u1_num_rec    */
    ((U1)sizeof(ST_TRIPCOM_NVMDATA) / (U1)TRIPCOM_NVMIF_BLO_NBYTE_12),  /* u1_rec_nblock */
    (U1)TRIPCOM_NVMIF_BLO_NBYTE_12,                                     /* u1_blo_nbyte  */
    (U1)NVMC_DEVICE_TYPE_DTF                                            /* u1_dev_idx    */
};
const U2 u2_g_TRIPCOM_NVMIF_NVMCID_DATA = (U2)NVMCID_APP_TRIPCOM;

static const    U2               u2_sp_TRIPCOM_MS_GRPH_DTF_BLOCK[]    = {
    /*  0 TRIPCOM_NVMIF_CH_TAFE_FE                */
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_FE_00,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_FE_01,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_FE_02,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_FE_03,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_FE_04,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_FE_05,
    /*  1 TRIPCOM_NVMIF_CH_TAFE_DT                */
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_DT_00,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_DT_01,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_DT_02,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_DT_03,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_DT_04,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAFE_DT_05,
    /*  2 TRIPCOM_NVMIF_CH_TAEE_EE                */
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_EE_00,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_EE_01,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_EE_02,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_EE_03,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_EE_04,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_EE_05,
    /*  3 TRIPCOM_NVMIF_CH_TAEE_DT                */
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_DT_00,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_DT_01,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_DT_02,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_DT_03,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_DT_04,
    (U2)NVMC_BLOCKID_DTF_GRPH_TAEE_DT_05
};

const ST_TRIPCOM_NVMIF_GRPH_REC_DATA  st_g_TRIPCOM_NVMIF_GRPH_REC_DATA = {
    &u2_sp_TRIPCOM_MS_GRPH_DTF_BLOCK[0],                                          /* u2p_BLOCK     */
    (U1)TRIPCOM_NVMIF_GRPH_CH_NUM * (U1)TRIPCOM_NVMIF_GRPH_NUM_REC,               /* u1_num_rec    */
    ((U1)sizeof(ST_TRIPCOM_GRPH_NVMDATA) / (U1)TRIPCOM_NVMIF_GRPH_BLO_NBYTE_32),  /* u1_rec_nblock */
    (U1)TRIPCOM_NVMIF_GRPH_BLO_NBYTE_32,                                          /* u1_blo_nbyte  */
    (U1)NVMC_DEVICE_TYPE_DTF                                                      /* u1_dev_idx    */
};
const U2 u2_g_TRIPCOM_NVMIF_GRPH_NVMCID_DATA = (U2)NVMCID_APP_TRIPCOM_GRPH;


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
#if 0   /* BEV BSW provisionally */
    return (u1_g_ESInspectMdBfield());
#else
    return ((U1)0U);
#endif
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
/* void            vd_g_TripcomMsSyncUpdtImm(const U1 u1_a_CH)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsSyncUpdtImm(const U1 u1_a_CH)
{
    if(u1_a_CH == (U1)TRIPCOM_NVMIF_CH_DTE_ED_FE){
         vd_g_DteEdInit();
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
/*                                                                                                                                   */
/*===================================================================================================================================*/
