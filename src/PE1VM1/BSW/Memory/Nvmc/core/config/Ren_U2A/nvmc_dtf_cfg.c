/* 1.4.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr DataFlash                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_DTF_CFG_C_MAJOR                     (1U)
#define NVMC_DTF_CFG_C_MINOR                     (4U)
#define NVMC_DTF_CFG_C_PATCH                     (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "nvmc_mgr_cfg_private.h"   /* #include "aip_common.h"               */
                                    /* #include "nvmc_mgr_private.h"         */
                                    /* #include "nvmc_mgr.h"                 */
                                    /* #include "nvmc_mgr_cfg.h"             */
                                    /* #include "nvmc_mgr_acstask_private.h" */
                                    /* #include "rim_ctl.h"                  */
                                    /* #include "rim_ctl_cfg.h"              */
#include "NvM.h"
#include "NvM_Ext.h"
#include "Mscd.h"
#include "Fee.h"

#include "nvmc_dtf_private.h"
#include "nvmc_dtf_cfg.h"
#include "nvmc_dtf_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_DTF_CFG_C_MAJOR != NVMC_DTF_PRIVATE_H_MAJOR) || \
     (NVMC_DTF_CFG_C_MINOR != NVMC_DTF_PRIVATE_H_MINOR) || \
     (NVMC_DTF_CFG_C_PATCH != NVMC_DTF_PRIVATE_H_PATCH))
#error "nvmc_dtf_cfg.c and nvmc_dtf_private.h : source and header files are inconsistent!"
#endif

#if ((NVMC_DTF_CFG_C_MAJOR != NVMC_DTF_CFG_H_MAJOR) || \
     (NVMC_DTF_CFG_C_MINOR != NVMC_DTF_CFG_H_MINOR) || \
     (NVMC_DTF_CFG_C_PATCH != NVMC_DTF_CFG_H_PATCH))
#error "nvmc_dtf_cfg.c and nvmc_dtf_cfg.h : source and config files are inconsistent!"
#endif

#if ((NVMC_DTF_CFG_C_MAJOR != NVMC_DTF_CFG_PRIVATE_H_MAJOR) || \
     (NVMC_DTF_CFG_C_MINOR != NVMC_DTF_CFG_PRIVATE_H_MINOR) || \
     (NVMC_DTF_CFG_C_PATCH != NVMC_DTF_CFG_PRIVATE_H_PATCH))
#error "nvmc_dtf_cfg.c and nvmc_dtf_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2 u2_dp_NVMC_DTF_ID_CONV_TBL[NVMC_DTF_ID_NUM] = {
/* START : ##TOOL_OUT#NVMC_DTF_ID_CONV_TBL## */
    ((U2)NVMC_ACCSS_TYPE_INAPP | (U2)0U  ),  /* ODO                    */
    ((U2)NVMC_ACCSS_TYPE_INAPP | (U2)1U  ),  /* ODO_TRIP               */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)0U  ),  /* TOEC_OC                */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)1U  ),  /* TOEC_EU                */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)2U  ),  /* TOSP_OC                */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)3U  ),  /* TOSP_ET                */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)4U  ),  /* TOTM_ET                */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)5U  ),  /* TODT_OC                */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)6U  ),  /* TR_A_SP_OC             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)7U  ),  /* TR_A_SP_ET             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)8U  ),  /* TR_B_SP_OC             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)9U  ),  /* TR_B_SP_ET             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)10U ),  /* TR_A_TM_ET             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)11U ),  /* TR_B_TM_ET             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)12U ),  /* TR_A_DT_OC             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)13U ),  /* TR_B_DT_OC             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)14U ),  /* GRPH_TAEE_ECON         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)15U ),  /* GRPH_TAEE_DATE         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)16U ),  /* MCST_IDX_USER1_1       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)17U ),  /* MCST_IDX_USER1_2       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)18U ),  /* MCST_IDX_USER2_1       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)19U ),  /* MCST_IDX_USER2_2       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)20U ),  /* MCST_IDX_USER3_1       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)21U ),  /* MCST_IDX_USER3_2       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)22U ),  /* MCST_IDX_GUEST_1       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)23U ),  /* MCST_IDX_GUEST_2       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)24U ),  /* DRVPS_MRRPOS01         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)25U ),  /* DRVPS_MRRPOS02         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)26U ),  /* DRVPS_MRRPOS03         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)27U ),  /* DRVPS_MRRPOS04         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)28U ),  /* DRVPS_MRRPOS05         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)29U ),  /* DRVPS_MRRPOS06         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)30U ),  /* DRVPS_MRRPOS07         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)31U ),  /* DRVPS_MRRPOS08         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)32U ),  /* DRVPS_MRRPOS09         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)33U ),  /* DRVPS_MRRPOS10         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)34U ),  /* DRVPS_MRRPOS11         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)35U ),  /* DRVPS_MRRPOS12         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)36U ),  /* DRVPS_MRRPOS13         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)37U ),  /* DRVPS_MRRPOS14         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)38U ),  /* DRVPS_MRRPOS15         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)39U ),  /* MET_RESERVE_0          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)40U ),  /* MET_RESERVE_1          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)41U ),  /* MET_RESERVE_2          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)42U ),  /* MET_RESERVE_3          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)43U ),  /* MET_RESERVE_4          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)44U ),  /* MET_RESERVE_5          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)45U ),  /* MET_RESERVE_6          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)46U ),  /* MET_RESERVE_7          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)47U ),  /* MET_RESERVE_8          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)48U ),  /* MET_RESERVE_9          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)49U ),  /* BSW_SECOC_TRIP_CNT     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)50U ),  /* OXDC_TMSTP             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)51U ),  /* OXDC_DTC_LOGRX1        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)52U ),  /* OXDC_DTC_EVENT001      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)53U ),  /* OXDC_DTC_EVENT002      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)54U ),  /* OXDC_DTC_EVENT003      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)55U ),  /* OXDC_DTC_EVENT004      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)56U ),  /* OXDC_DTC_EVENT005      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)57U ),  /* OXDC_DTC_EVENT006      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)58U ),  /* OXDC_DTC_EVENT007      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)59U ),  /* OXDC_DTC_EVENT008      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)60U ),  /* OXDC_DTC_EVENT009      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)61U ),  /* OXDC_DTC_EVENT010      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)62U ),  /* OXDC_DTC_EVENT011      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)63U ),  /* OXDC_DTC_EVENT012      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)64U ),  /* OXDC_DTC_EVENT013      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)65U ),  /* OXDC_DTC_EVENT014      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)66U ),  /* OXDC_DTC_EVENT015      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)67U ),  /* OXDC_DTC_EVENT016      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)68U ),  /* OXDC_DTC_EVENT017      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)69U ),  /* OXDC_DTC_EVENT018      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)70U ),  /* OXDC_DTC_EVENT019      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)71U ),  /* OXDC_DTC_EVENT020      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)72U ),  /* OXDC_DTC_EVENT021      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)73U ),  /* OXDC_DTC_FAULT001      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)74U ),  /* OXDC_DTC_FAULT002      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)75U ),  /* OXDC_DTC_FAULT003      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)76U ),  /* OXDC_DTC_FAULT004      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)77U ),  /* OXDC_DTC_FAULT005      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)78U ),  /* OXDC_DTC_FAULT006      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)79U ),  /* OXDC_DTC_FAULT007      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)80U ),  /* OXDC_DTC_FAULT008      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)81U ),  /* OXDC_DTC_FAULT009      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)82U ),  /* OXDC_DTC_FAULT010      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)83U ),  /* OXDC_DTC_FAULT011      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)84U ),  /* OXDC_DTC_FAULT012      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)85U ),  /* OXDC_DTC_FAULT013      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)86U ),  /* OXDC_DTC_FAULT014      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)87U ),  /* OXDC_DTC_FAULT015      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)88U ),  /* OXDC_DTC_FAULT016      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)89U ),  /* OXDC_DTC_FAULT017      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)90U ),  /* OXDC_DTC_FAULT018      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)91U ),  /* OXDC_DTC_FAULT019      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)92U ),  /* OXDC_DTC_FAULT020      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)93U ),  /* OXDC_DTC_FAULT021      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)94U ),  /* OXDC_DTC_FFD001        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)95U ),  /* OXDC_DTC_FFD002        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)96U ),  /* OXDC_DTC_FFD003        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)97U ),  /* OXDC_DTC_FFD004        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)98U ),  /* OXDC_DTC_FFD005        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)99U ),  /* OXDC_DTC_FFD006        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)100U),  /* OXDC_DTC_FFD007        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)101U),  /* OXDC_DTC_FFD008        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)102U),  /* OXDC_DTC_FFD009        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)103U),  /* OXDC_DTC_FFD010        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)104U),  /* OXDC_DTC_FFD011        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)105U),  /* OXDC_DTC_FFD012        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)106U),  /* OXDC_DTC_FFD013        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)107U),  /* OXDC_DTC_FFD014        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)108U),  /* OXDC_DTC_FFD015        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)109U),  /* OXDC_DTC_FFD016        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)110U),  /* OXDC_DTC_FFD017        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)111U),  /* OXDC_DTC_FFD018        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)112U),  /* OXDC_DTC_FFD019        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)113U),  /* OXDC_DTC_FFD020        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)114U),  /* OXDC_DTC_FFD021        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)115U),  /* OXDC_DTC_CLEARINFO     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)116U),  /* OXDC_UDTC11_EVENT001   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)117U),  /* OXDC_UDTC11_EVENT002   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)118U),  /* OXDC_UDTC11_EVENT003   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)119U),  /* OXDC_UDTC11_EVENT004   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)120U),  /* OXDC_UDTC11_EVENT005   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)121U),  /* OXDC_UDTC11_EVENT006   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)122U),  /* OXDC_UDTC12_EVENT001   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)123U),  /* OXDC_UDTC12_EVENT002   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)124U),  /* OXDC_UDTC12_EVENT003   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)125U),  /* OXDC_UDTC13_EVENT001   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)126U),  /* OXDC_UDTC13_EVENT002   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)127U),  /* OXDC_UDTC11_FAULT001   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)128U),  /* OXDC_UDTC11_FAULT002   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)129U),  /* OXDC_UDTC11_FAULT003   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)130U),  /* OXDC_UDTC11_FAULT004   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)131U),  /* OXDC_UDTC11_FAULT005   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)132U),  /* OXDC_UDTC11_FAULT006   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)133U),  /* OXDC_UDTC12_FAULT001   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)134U),  /* OXDC_UDTC12_FAULT002   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)135U),  /* OXDC_UDTC12_FAULT003   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)136U),  /* OXDC_UDTC13_FAULT001   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)137U),  /* OXDC_UDTC13_FAULT002   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)138U),  /* OXDC_UDTC11_FFD001     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)139U),  /* OXDC_UDTC11_FFD002     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)140U),  /* OXDC_UDTC11_FFD003     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)141U),  /* OXDC_UDTC11_FFD004     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)142U),  /* OXDC_UDTC11_FFD005     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)143U),  /* OXDC_UDTC11_FFD006     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)144U),  /* OXDC_UDTC11_FFD007     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)145U),  /* OXDC_UDTC11_FFD008     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)146U),  /* OXDC_UDTC11_FFD009     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)147U),  /* OXDC_UDTC11_FFD010     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)148U),  /* OXDC_UDTC11_FFD011     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)149U),  /* OXDC_UDTC11_FFD012     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)150U),  /* OXDC_UDTC11_FFD013     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)151U),  /* OXDC_UDTC11_FFD014     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)152U),  /* OXDC_UDTC11_FFD015     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)153U),  /* OXDC_UDTC11_FFD016     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)154U),  /* OXDC_UDTC11_FFD017     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)155U),  /* OXDC_UDTC11_FFD018     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)156U),  /* OXDC_UDTC11_FFD019     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)157U),  /* OXDC_UDTC11_FFD020     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)158U),  /* OXDC_UDTC11_FFD021     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)159U),  /* OXDC_UDTC11_FFD022     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)160U),  /* OXDC_UDTC11_FFD023     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)161U),  /* OXDC_UDTC11_FFD024     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)162U),  /* OXDC_UDTC11_FFD025     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)163U),  /* OXDC_UDTC11_FFD026     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)164U),  /* OXDC_UDTC11_FFD027     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)165U),  /* OXDC_UDTC11_FFD028     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)166U),  /* OXDC_UDTC11_FFD029     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)167U),  /* OXDC_UDTC11_FFD030     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)168U),  /* OXDC_UDTC11_FFD031     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)169U),  /* OXDC_UDTC11_FFD032     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)170U),  /* OXDC_UDTC11_FFD033     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)171U),  /* OXDC_UDTC11_FFD034     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)172U),  /* OXDC_UDTC11_FFD035     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)173U),  /* OXDC_UDTC11_FFD036     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)174U),  /* OXDC_UDTC11_FFD037     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)175U),  /* OXDC_UDTC11_FFD038     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)176U),  /* OXDC_UDTC11_FFD039     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)177U),  /* OXDC_UDTC11_FFD040     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)178U),  /* OXDC_UDTC11_FFD041     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)179U),  /* OXDC_UDTC11_FFD042     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)180U),  /* OXDC_UDTC11_FFD043     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)181U),  /* OXDC_UDTC11_FFD044     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)182U),  /* OXDC_UDTC11_FFD045     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)183U),  /* OXDC_UDTC11_FFD046     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)184U),  /* OXDC_UDTC11_FFD047     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)185U),  /* OXDC_UDTC11_FFD048     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)186U),  /* OXDC_UDTC11_FFD049     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)187U),  /* OXDC_UDTC11_FFD050     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)188U),  /* OXDC_UDTC11_FFD051     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)189U),  /* OXDC_UDTC11_FFD052     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)190U),  /* OXDC_UDTC11_FFD053     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)191U),  /* OXDC_UDTC11_FFD054     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)192U),  /* OXDC_UDTC12_FFD001     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)193U),  /* OXDC_UDTC12_FFD002     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)194U),  /* OXDC_UDTC12_FFD003     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)195U),  /* OXDC_UDTC13_FFD001     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)196U),  /* OXDC_UDTC13_FFD002     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)197U),  /* OXDC_UDTC13_FFD003     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)198U),  /* OXDC_UDTC13_FFD004     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)199U),  /* OXDC_ROE_A005          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)200U),  /* OXDC_SSR_22_10A1_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)201U),  /* OXDC_SSR_22_10A1_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)202U),  /* OXDC_SSR_22_10A1_2     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)203U),  /* OXDC_SSR_22_10A3_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)204U),  /* OXDC_SSR_22_10A3_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)205U),  /* OXDC_SSR_22_10A3_2     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)206U),  /* OXDC_SSR_22_10AB_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)207U),  /* OXDC_SSR_22_10AB_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)208U),  /* OXDC_SSR_22_10AB_2     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)209U),  /* OXDC_SSR_22_10AF_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)210U),  /* OXDC_SSR_22_10AF_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)211U),  /* OXDC_SSR_22_10AF_2     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)212U),  /* OXDC_SSR_22_10B6_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)213U),  /* OXDC_SSR_22_10B6_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)214U),  /* OXDC_SSR_22_10B6_2     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)215U),  /* OXDC_2E_2002           */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)216U),  /* OXDC_2E_2003           */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)217U),  /* OXDC_2E_2041           */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)218U),  /* OXDC_2E_20C2           */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)219U),  /* OXDC_2E_220E_0         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)220U),  /* OXDC_2E_220E_1         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)221U),  /* OXDC_2E_220E_2         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)222U),  /* OXDC_2E_220E_3         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)223U),  /* OXDC_2E_220E_4         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)224U),  /* OXDC_2E_220E_5         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)225U),  /* OXDC_2E_220E_6         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)226U),  /* OXDC_2E_220E_7         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)227U),  /* OXDC_2E_220E_8         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)228U),  /* OXDC_2E_220E_9         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)229U),  /* OXDC_2E_220E_10        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)230U),  /* OXDC_2E_220E_11        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)231U),  /* OXDC_2E_220E_12        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)232U),  /* OXDC_2E_220E_13        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)233U),  /* OXDC_2E_220E_14        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)234U),  /* OXDC_2E_220E_15        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)235U),  /* OXDC_2E_220E_16        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)236U),  /* OXDC_2E_220E_17        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)237U),  /* OXDC_2E_220E_18        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)238U),  /* OXDC_2E_220E_19        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)239U),  /* OXDC_SSR_BA_D1L1_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)240U),  /* OXDC_SSR_BA_D1L1_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)241U),  /* OXDC_SSR_BA_D1L1_2     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)242U),  /* OXDC_SSR_BA_D1L1_3     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)243U),  /* OXDC_SSR_BA_D1L1_4     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)244U),  /* OXDC_SSR_BA_RCAR_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)245U),  /* OXDC_SSR_BA_RCAR_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)246U),  /* OXDC_SSR_BA_RCAR_2     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)247U),  /* OXDC_SSR_BA_RCAR_3     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)248U),  /* OXDC_SSR_BA_RCAR_4     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)249U),  /* MET_RESERVE_10         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)250U),  /* MET_RESERVE_11         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)251U),  /* MET_RESERVE_12         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)252U),  /* MET_RESERVE_13         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)253U),  /* MET_RESERVE_14         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)254U),  /* MET_RESERVE_15         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)255U),  /* MET_RESERVE_16         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)256U),  /* MET_RESERVE_17         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)257U),  /* MET_RESERVE_18         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)258U),  /* MET_RESERVE_19         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)259U),  /* VDF_ESO_W0             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)260U),  /* VDF_ESO_W1             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)261U),  /* VDF_ESO_W2             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)262U),  /* VDF_ESO_W3             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)263U),  /* VDF_ESO_W4             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)264U),  /* VDF_ESO_W5             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)265U),  /* VDF_ESO_W6             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)266U),  /* VDF_ESO_W7             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)267U),  /* VDF_ESO_W8             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)268U),  /* ODO_INHERIT_FLG        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)269U),  /* FWUSH_FSWASTAT_0_INFO  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)270U),  /* FWUSH_VERIFY_LBN_COMP  */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)271U),  /* FWUSH_SEQ_PROGRESS     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)272U),  /* MET_RESERVE_20         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)273U),  /* MET_RESERVE_21         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)274U),  /* MET_RESERVE_22         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)275U),  /* MET_RESERVE_23         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)276U),  /* MET_RESERVE_24         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)277U),  /* MET_RESERVE_25         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)278U),  /* MET_RESERVE_26         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)279U),  /* MET_RESERVE_27         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)280U),  /* MET_RESERVE_28         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)281U),  /* MET_RESERVE_29         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)282U),  /* OXDC_22_F18A           */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)283U),  /* OXDC_22_SERI_N_10B     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)284U),  /* OXDC_22_ECU_PN_10B     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)285U),  /* OXDC_BA_NUO_DI         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)286U),  /* OXDC_BA_SAFEKEY_NUM    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)287U),  /* MET_RESERVE_30         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)288U),  /* MET_RESERVE_31         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)289U),  /* MET_RESERVE_32         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)290U),  /* MET_RESERVE_33         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)291U),  /* MET_RESERVE_34         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)292U),  /* MET_RESERVE_35         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)293U),  /* MET_RESERVE_36         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)294U),  /* MET_RESERVE_37         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)295U),  /* MET_RESERVE_38         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)296U),  /* MET_RESERVE_39         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)297U),  /* MET_RESERVE_40         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)298U),  /* MET_RESERVE_41         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)299U),  /* MET_RESERVE_42         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)300U),  /* MET_RESERVE_43         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)301U),  /* MET_RESERVE_44         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)302U),  /* MET_RESERVE_45         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)303U),  /* MET_RESERVE_46         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)304U),  /* MET_RESERVE_47         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)305U),  /* MET_RESERVE_48         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)306U),  /* MET_RESERVE_49         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)307U),  /* DATESI_CALENDAR        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)308U),  /* DATESI_OFFSET          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)309U),  /* PICT_MAVTYPE           */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)310U),  /* PICT_RCROP0            */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)311U),  /* PICT_STRGWHL           */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)312U),  /* POWER_DEST_LOG         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)313U),  /* WHLINI_REQ             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)314U),  /* DIREC_INDEX            */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)315U),  /* DIREC_000              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)316U),  /* DIREC_001              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)317U),  /* DIREC_002              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)318U),  /* DIREC_003              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)319U),  /* DIREC_004              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)320U),  /* DIREC_005              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)321U),  /* DIREC_006              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)322U),  /* DIREC_007              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)323U),  /* DIREC_008              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)324U),  /* DIREC_009              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)325U),  /* DIREC_010              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)326U),  /* DIREC_011              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)327U),  /* DIREC_012              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)328U),  /* DIREC_013              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)329U),  /* DIREC_014              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)330U),  /* DIREC_015              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)331U),  /* DIREC_016              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)332U),  /* DIREC_017              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)333U),  /* DIREC_018              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)334U),  /* DIREC_019              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)335U),  /* DIREC_020              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)336U),  /* DIREC_021              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)337U),  /* DIREC_022              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)338U),  /* DIREC_023              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)339U),  /* DIREC_024              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)340U),  /* DIREC_025              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)341U),  /* DIREC_026              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)342U),  /* DIREC_027              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)343U),  /* DIREC_028              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)344U),  /* DIREC_029              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)345U),  /* DIREC_030              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)346U),  /* DIREC_031              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)347U),  /* DIREC_032              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)348U),  /* DIREC_033              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)349U),  /* DIREC_034              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)350U),  /* DIREC_035              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)351U),  /* DIREC_036              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)352U),  /* DIREC_037              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)353U),  /* DIREC_038              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)354U),  /* DIREC_039              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)355U),  /* DIREC_040              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)356U),  /* DIREC_041              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)357U),  /* DIREC_042              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)358U),  /* DIREC_043              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)359U),  /* DIREC_044              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)360U),  /* DIREC_045              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)361U),  /* DIREC_046              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)362U),  /* DIREC_047              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)363U),  /* DIREC_048              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)364U),  /* DIREC_049              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)365U),  /* DIREC_050              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)366U),  /* DIREC_051              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)367U),  /* DIREC_052              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)368U),  /* DIREC_053              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)369U),  /* DIREC_054              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)370U),  /* DIREC_055              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)371U),  /* DIREC_056              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)372U),  /* DIREC_057              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)373U),  /* DIREC_058              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)374U),  /* DIREC_059              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)375U),  /* DIREC_060              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)376U),  /* DIREC_061              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)377U),  /* DIREC_062              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)378U),  /* DIREC_063              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)379U),  /* DIREC_064              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)380U),  /* DIREC_065              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)381U),  /* DIREC_066              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)382U),  /* DIREC_067              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)383U),  /* DIREC_068              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)384U),  /* DIREC_069              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)385U),  /* DIREC_070              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)386U),  /* DIREC_071              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)387U),  /* DIREC_072              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)388U),  /* DIREC_073              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)389U),  /* DIREC_074              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)390U),  /* DIREC_075              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)391U),  /* DIREC_076              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)392U),  /* DIREC_077              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)393U),  /* DIREC_078              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)394U),  /* DIREC_079              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)395U),  /* DIREC_080              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)396U),  /* DIREC_081              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)397U),  /* DIREC_082              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)398U),  /* DIREC_083              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)399U),  /* DIREC_084              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)400U),  /* DIREC_085              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)401U),  /* DIREC_086              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)402U),  /* DIREC_087              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)403U),  /* DIREC_088              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)404U),  /* DIREC_089              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)405U),  /* DIREC_090              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)406U),  /* DIREC_091              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)407U),  /* DIREC_092              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)408U),  /* DIREC_093              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)409U),  /* DIREC_094              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)410U),  /* DIREC_095              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)411U),  /* DIREC_096              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)412U),  /* DIREC_097              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)413U),  /* DIREC_098              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)414U),  /* DIREC_099              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)415U),  /* DIREC_100              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)416U),  /* DIREC_101              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)417U),  /* DIREC_102              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)418U),  /* DIREC_103              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)419U),  /* DIREC_104              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)420U),  /* DIREC_105              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)421U),  /* DIREC_106              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)422U),  /* DIREC_107              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)423U),  /* DIREC_108              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)424U),  /* DIREC_109              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)425U),  /* DIREC_110              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)426U),  /* DIREC_111              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)427U),  /* DIREC_112              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)428U),  /* DIREC_113              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)429U),  /* DIREC_114              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)430U),  /* DIREC_115              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)431U),  /* DIREC_116              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)432U),  /* DIREC_117              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)433U),  /* DIREC_118              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)434U),  /* DIREC_119              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)435U),  /* DIREC_120              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)436U),  /* DIREC_121              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)437U),  /* DIREC_122              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)438U),  /* DIREC_123              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)439U),  /* DIREC_124              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)440U),  /* DIREC_125              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)441U),  /* DIREC_126              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)442U),  /* DIREC_127              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)443U),  /* DIREC_128              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)444U),  /* DIREC_129              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)445U),  /* DIREC_130              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)446U),  /* DIREC_131              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)447U),  /* DIREC_132              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)448U),  /* DIREC_133              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)449U),  /* DIREC_134              */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)450U),  /* IVI_RESERVE_0          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)451U),  /* IVI_RESERVE_1          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)452U),  /* IVI_RESERVE_2          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)453U),  /* IVI_RESERVE_3          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)454U),  /* IVI_RESERVE_4          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)455U),  /* IVI_RESERVE_5          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)456U),  /* IVI_RESERVE_6          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)457U),  /* IVI_RESERVE_7          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)458U),  /* IVI_RESERVE_8          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)459U),  /* IVI_RESERVE_9          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)460U),  /* PWLOG_ERR_COUNT        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)461U),  /* PWLOG_BASIC_SEQ_00     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)462U),  /* PWLOG_BASIC_SEQ_01     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)463U),  /* PWLOG_BASIC_SEQ_02     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)464U),  /* PWLOG_BASIC_SEQ_03     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)465U),  /* PWLOG_BASIC_SEQ_04     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)466U),  /* PWLOG_BASIC_SEQ_05     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)467U),  /* PWLOG_BASIC_SEQ_06     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)468U),  /* PWLOG_BASIC_SEQ_07     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)469U),  /* PWLOG_BASIC_SEQ_08     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)470U),  /* PWLOG_BASIC_SEQ_09     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)471U),  /* PWLOG_BASIC_SEQ_10     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)472U),  /* PWLOG_BASIC_SEQ_11     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)473U),  /* PWLOG_BASIC_SEQ_12     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)474U),  /* PWLOG_BASIC_SEQ_13     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)475U),  /* PWLOG_BASIC_SEQ_14     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)476U),  /* PWLOG_BASIC_SEQ_15     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)477U),  /* PWLOG_BASIC_SEQ_16     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)478U),  /* PWLOG_BASIC_SEQ_17     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)479U),  /* PWLOG_BASIC_SEQ_18     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)480U),  /* PWLOG_BASIC_SEQ_19     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)481U),  /* PWLOG_BASIC_SEQ_WP     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)482U),  /* PWLOG_OBS_SEQ_00_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)483U),  /* PWLOG_OBS_SEQ_00_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)484U),  /* PWLOG_OBS_SEQ_01_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)485U),  /* PWLOG_OBS_SEQ_01_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)486U),  /* PWLOG_OBS_SEQ_02_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)487U),  /* PWLOG_OBS_SEQ_02_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)488U),  /* PWLOG_OBS_SEQ_03_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)489U),  /* PWLOG_OBS_SEQ_03_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)490U),  /* PWLOG_OBS_SEQ_04_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)491U),  /* PWLOG_OBS_SEQ_04_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)492U),  /* PWLOG_OBS_SEQ_05_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)493U),  /* PWLOG_OBS_SEQ_05_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)494U),  /* PWLOG_OBS_SEQ_06_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)495U),  /* PWLOG_OBS_SEQ_06_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)496U),  /* PWLOG_OBS_SEQ_07_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)497U),  /* PWLOG_OBS_SEQ_07_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)498U),  /* PWLOG_OBS_SEQ_08_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)499U),  /* PWLOG_OBS_SEQ_08_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)500U),  /* PWLOG_OBS_SEQ_09_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)501U),  /* PWLOG_OBS_SEQ_09_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)502U),  /* PWLOG_OBS_SEQ_10_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)503U),  /* PWLOG_OBS_SEQ_10_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)504U),  /* PWLOG_OBS_SEQ_11_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)505U),  /* PWLOG_OBS_SEQ_11_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)506U),  /* PWLOG_OBS_SEQ_12_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)507U),  /* PWLOG_OBS_SEQ_12_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)508U),  /* PWLOG_OBS_SEQ_13_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)509U),  /* PWLOG_OBS_SEQ_13_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)510U),  /* PWLOG_OBS_SEQ_14_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)511U),  /* PWLOG_OBS_SEQ_14_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)512U),  /* PWLOG_OBS_SEQ_15_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)513U),  /* PWLOG_OBS_SEQ_15_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)514U),  /* PWLOG_OBS_SEQ_16_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)515U),  /* PWLOG_OBS_SEQ_16_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)516U),  /* PWLOG_OBS_SEQ_17_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)517U),  /* PWLOG_OBS_SEQ_17_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)518U),  /* PWLOG_OBS_SEQ_18_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)519U),  /* PWLOG_OBS_SEQ_18_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)520U),  /* PWLOG_OBS_SEQ_19_0     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)521U),  /* PWLOG_OBS_SEQ_19_1     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)522U),  /* PWLOG_OBS_SEQ_WP       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)523U),  /* PWLOG_OTA_SEQ_00       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)524U),  /* PWLOG_OTA_SEQ_01       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)525U),  /* PWLOG_OTA_SEQ_02       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)526U),  /* PWLOG_OTA_SEQ_03       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)527U),  /* PWLOG_OTA_SEQ_04       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)528U),  /* PWLOG_OTA_SEQ_WP       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)529U),  /* PWLOG_MCU_PMIC_00_0    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)530U),  /* PWLOG_MCU_PMIC_00_1    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)531U),  /* PWLOG_MCU_PMIC_01_0    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)532U),  /* PWLOG_MCU_PMIC_01_1    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)533U),  /* PWLOG_MCU_PMIC_02_0    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)534U),  /* PWLOG_MCU_PMIC_02_1    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)535U),  /* PWLOG_MCU_PMIC_03_0    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)536U),  /* PWLOG_MCU_PMIC_03_1    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)537U),  /* PWLOG_MCU_PMIC_04_0    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)538U),  /* PWLOG_MCU_PMIC_04_1    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)539U),  /* PWLOG_MCU_PMIC_WP      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)540U),  /* PWLOG_SELFTEST_00      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)541U),  /* PWLOG_SELFTEST_01      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)542U),  /* PWLOG_SELFTEST_02      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)543U),  /* PWLOG_SELFTEST_03      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)544U),  /* PWLOG_SELFTEST_04      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)545U),  /* PWLOG_SELFTEST_05      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)546U),  /* PWLOG_SELFTEST_06      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)547U),  /* PWLOG_SELFTEST_07      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)548U),  /* PWLOG_SELFTEST_08      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)549U),  /* PWLOG_SELFTEST_09      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)550U),  /* PWLOG_SELFTEST_10      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)551U),  /* PWLOG_SELFTEST_11      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)552U),  /* PWLOG_SELFTEST_12      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)553U),  /* PWLOG_SELFTEST_13      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)554U),  /* PWLOG_SELFTEST_14      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)555U),  /* PWLOG_SELFTEST_15      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)556U),  /* PWLOG_SELFTEST_16      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)557U),  /* PWLOG_SELFTEST_17      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)558U),  /* PWLOG_SELFTEST_18      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)559U),  /* PWLOG_SELFTEST_19      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)560U),  /* PWLOG_SELFTEST_WP      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)561U),  /* PWLOG_BIST_INIT_00_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)562U),  /* PWLOG_BIST_INIT_00_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)563U),  /* PWLOG_BIST_INIT_01_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)564U),  /* PWLOG_BIST_INIT_01_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)565U),  /* PWLOG_BIST_INIT_02_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)566U),  /* PWLOG_BIST_INIT_02_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)567U),  /* PWLOG_BIST_INIT_03_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)568U),  /* PWLOG_BIST_INIT_03_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)569U),  /* PWLOG_BIST_INIT_04_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)570U),  /* PWLOG_BIST_INIT_04_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)571U),  /* PWLOG_BIST_INIT_05_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)572U),  /* PWLOG_BIST_INIT_05_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)573U),  /* PWLOG_BIST_INIT_06_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)574U),  /* PWLOG_BIST_INIT_06_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)575U),  /* PWLOG_BIST_INIT_07_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)576U),  /* PWLOG_BIST_INIT_07_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)577U),  /* PWLOG_BIST_INIT_08_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)578U),  /* PWLOG_BIST_INIT_08_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)579U),  /* PWLOG_BIST_INIT_09_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)580U),  /* PWLOG_BIST_INIT_09_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)581U),  /* PWLOG_BIST_INIT_10_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)582U),  /* PWLOG_BIST_INIT_10_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)583U),  /* PWLOG_BIST_INIT_11_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)584U),  /* PWLOG_BIST_INIT_11_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)585U),  /* PWLOG_BIST_INIT_12_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)586U),  /* PWLOG_BIST_INIT_12_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)587U),  /* PWLOG_BIST_INIT_13_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)588U),  /* PWLOG_BIST_INIT_13_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)589U),  /* PWLOG_BIST_INIT_14_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)590U),  /* PWLOG_BIST_INIT_14_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)591U),  /* PWLOG_BIST_INIT_15_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)592U),  /* PWLOG_BIST_INIT_15_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)593U),  /* PWLOG_BIST_INIT_16_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)594U),  /* PWLOG_BIST_INIT_16_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)595U),  /* PWLOG_BIST_INIT_17_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)596U),  /* PWLOG_BIST_INIT_17_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)597U),  /* PWLOG_BIST_INIT_18_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)598U),  /* PWLOG_BIST_INIT_18_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)599U),  /* PWLOG_BIST_INIT_19_0   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)600U),  /* PWLOG_BIST_INIT_19_1   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)601U),  /* PWLOG_BIST_INIT_WP     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)602U),  /* PWLOG_RESERVE_00       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)603U),  /* PWLOG_RESERVE_01       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)604U),  /* PWLOG_RESERVE_02       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)605U),  /* PWLOG_RESERVE_03       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)606U),  /* PWLOG_RESERVE_04       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)607U),  /* PWLOG_RESERVE_05       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)608U),  /* PWLOG_RESERVE_06       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)609U),  /* PWLOG_RESERVE_07       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)610U),  /* PWLOG_RESERVE_08       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)611U),  /* PWLOG_RESERVE_09       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)612U),  /* PWLOG_RESERVE_10       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)613U),  /* PWLOG_RESERVE_11       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)614U),  /* PWLOG_RESERVE_12       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)615U),  /* PWLOG_RESERVE_13       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)616U),  /* PWLOG_RESERVE_14       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)617U),  /* PWLOG_RESERVE_15       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)618U),  /* PWLOG_RESERVE_16       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)619U),  /* PWLOG_RESERVE_17       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)620U),  /* PWLOG_RESERVE_18       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)621U),  /* PWLOG_RESERVE_19       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)622U),  /* PWLOG_RESERVE_WP       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)623U),  /* PWCTRL_OTAACT_REQ      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)624U),  /* ETH_GLOBAL_MAC_ADDRESS */
    ((U2)NVMC_ACCSS_TYPE_INAPP | (U2)2U  )   /* Recovery               */
/* END : ##TOOL_OUT#NVMC_DTF_ID_CONV_TBL## */
};

const ST_NVMC_CFGDATA    st_dp_NVMC_DTF_DATA_CFG_TBL[NVMC_DTF_INNVM_NUM] = {
/* START : ##TOOL_OUT#NVMC_DTF_DATA_CFG_TBL## */
/*                             u2_addr                               u2_offset    u2_rimid_wdata                     u2_rimid_nvmsts               u1_map                              u1_rangeretry  u1_verifyretry  u1_mgr_bit_cfg  u4_module_bit_cfg   DEF              MIN              MAX           */ 
/* TOEC_OC                */ {(U2)DTF_BID_TOEC_OC_0,                (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_000,  (U2)RIMID_U1_NVMC_ST_DTF_000, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TOEC_EU                */ {(U2)DTF_BID_TOEC_EU_0,                (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_001,  (U2)RIMID_U1_NVMC_ST_DTF_001, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TOSP_OC                */ {(U2)DTF_BID_TOSP_OC_0,                (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_002,  (U2)RIMID_U1_NVMC_ST_DTF_002, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TOSP_ET                */ {(U2)DTF_BID_TOSP_ET_0,                (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_003,  (U2)RIMID_U1_NVMC_ST_DTF_003, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TOTM_ET                */ {(U2)DTF_BID_TOTM_ET_0,                (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_004,  (U2)RIMID_U1_NVMC_ST_DTF_004, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TODT_OC                */ {(U2)DTF_BID_TODT_OC_0,                (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_005,  (U2)RIMID_U1_NVMC_ST_DTF_005, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TR_A_SP_OC             */ {(U2)DTF_BID_TR_A_SP_OC_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_006,  (U2)RIMID_U1_NVMC_ST_DTF_006, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TR_A_SP_ET             */ {(U2)DTF_BID_TR_A_SP_ET_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_007,  (U2)RIMID_U1_NVMC_ST_DTF_007, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TR_B_SP_OC             */ {(U2)DTF_BID_TR_B_SP_OC_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_008,  (U2)RIMID_U1_NVMC_ST_DTF_008, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TR_B_SP_ET             */ {(U2)DTF_BID_TR_B_SP_ET_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_009,  (U2)RIMID_U1_NVMC_ST_DTF_009, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TR_A_TM_ET             */ {(U2)DTF_BID_TR_A_TM_ET_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_010,  (U2)RIMID_U1_NVMC_ST_DTF_010, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TR_B_TM_ET             */ {(U2)DTF_BID_TR_B_TM_ET_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_011,  (U2)RIMID_U1_NVMC_ST_DTF_011, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TR_A_DT_OC             */ {(U2)DTF_BID_TR_A_DT_OC_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_012,  (U2)RIMID_U1_NVMC_ST_DTF_012, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* TR_B_DT_OC             */ {(U2)DTF_BID_TR_B_DT_OC_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_013,  (U2)RIMID_U1_NVMC_ST_DTF_013, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* GRPH_TAEE_ECON         */ {(U2)DTF_BID_GRPH_TAEE_ECON_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_014, (U2)RIMID_U1_NVMC_ST_DTF_014, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_24, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* GRPH_TAEE_DATE         */ {(U2)DTF_BID_GRPH_TAEE_DATE_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_015, (U2)RIMID_U1_NVMC_ST_DTF_015, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_12, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER1_1       */ {(U2)DTF_BID_MCST_IDX_USER1_1_0,       (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_016, (U2)RIMID_U1_NVMC_ST_DTF_016, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER1_2       */ {(U2)DTF_BID_MCST_IDX_USER1_2_0,       (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_017, (U2)RIMID_U1_NVMC_ST_DTF_017, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER2_1       */ {(U2)DTF_BID_MCST_IDX_USER2_1_0,       (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_018, (U2)RIMID_U1_NVMC_ST_DTF_018, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER2_2       */ {(U2)DTF_BID_MCST_IDX_USER2_2_0,       (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_019, (U2)RIMID_U1_NVMC_ST_DTF_019, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER3_1       */ {(U2)DTF_BID_MCST_IDX_USER3_1_0,       (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_020, (U2)RIMID_U1_NVMC_ST_DTF_020, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_USER3_2       */ {(U2)DTF_BID_MCST_IDX_USER3_2_0,       (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_021, (U2)RIMID_U1_NVMC_ST_DTF_021, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_GUEST_1       */ {(U2)DTF_BID_MCST_IDX_GUEST_1_0,       (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_022, (U2)RIMID_U1_NVMC_ST_DTF_022, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MCST_IDX_GUEST_2       */ {(U2)DTF_BID_MCST_IDX_GUEST_2_0,       (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_023, (U2)RIMID_U1_NVMC_ST_DTF_023, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* DRVPS_MRRPOS01         */ {(U2)DTF_BID_DRVPS_MRRPOS01_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_024,  (U2)RIMID_U1_NVMC_ST_DTF_024, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS02         */ {(U2)DTF_BID_DRVPS_MRRPOS02_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_025,  (U2)RIMID_U1_NVMC_ST_DTF_025, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS03         */ {(U2)DTF_BID_DRVPS_MRRPOS03_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_026,  (U2)RIMID_U1_NVMC_ST_DTF_026, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS04         */ {(U2)DTF_BID_DRVPS_MRRPOS04_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_027,  (U2)RIMID_U1_NVMC_ST_DTF_027, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS05         */ {(U2)DTF_BID_DRVPS_MRRPOS05_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_028,  (U2)RIMID_U1_NVMC_ST_DTF_028, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS06         */ {(U2)DTF_BID_DRVPS_MRRPOS06_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_029,  (U2)RIMID_U1_NVMC_ST_DTF_029, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS07         */ {(U2)DTF_BID_DRVPS_MRRPOS07_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_030,  (U2)RIMID_U1_NVMC_ST_DTF_030, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS08         */ {(U2)DTF_BID_DRVPS_MRRPOS08_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_031,  (U2)RIMID_U1_NVMC_ST_DTF_031, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS09         */ {(U2)DTF_BID_DRVPS_MRRPOS09_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_032,  (U2)RIMID_U1_NVMC_ST_DTF_032, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS10         */ {(U2)DTF_BID_DRVPS_MRRPOS10_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_033,  (U2)RIMID_U1_NVMC_ST_DTF_033, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS11         */ {(U2)DTF_BID_DRVPS_MRRPOS11_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_034,  (U2)RIMID_U1_NVMC_ST_DTF_034, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS12         */ {(U2)DTF_BID_DRVPS_MRRPOS12_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_035,  (U2)RIMID_U1_NVMC_ST_DTF_035, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS13         */ {(U2)DTF_BID_DRVPS_MRRPOS13_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_036,  (U2)RIMID_U1_NVMC_ST_DTF_036, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS14         */ {(U2)DTF_BID_DRVPS_MRRPOS14_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_037,  (U2)RIMID_U1_NVMC_ST_DTF_037, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DRVPS_MRRPOS15         */ {(U2)DTF_BID_DRVPS_MRRPOS15_0,         (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_038,  (U2)RIMID_U1_NVMC_ST_DTF_038, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* MET_RESERVE_0          */ {(U2)DTF_BID_MET_RESERVE_0_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_039,  (U2)RIMID_U1_NVMC_ST_DTF_039, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_1          */ {(U2)DTF_BID_MET_RESERVE_1_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_040,  (U2)RIMID_U1_NVMC_ST_DTF_040, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_2          */ {(U2)DTF_BID_MET_RESERVE_2_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_041,  (U2)RIMID_U1_NVMC_ST_DTF_041, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_3          */ {(U2)DTF_BID_MET_RESERVE_3_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_042,  (U2)RIMID_U1_NVMC_ST_DTF_042, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_4          */ {(U2)DTF_BID_MET_RESERVE_4_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_043,  (U2)RIMID_U1_NVMC_ST_DTF_043, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_5          */ {(U2)DTF_BID_MET_RESERVE_5_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_044,  (U2)RIMID_U1_NVMC_ST_DTF_044, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_6          */ {(U2)DTF_BID_MET_RESERVE_6_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_045,  (U2)RIMID_U1_NVMC_ST_DTF_045, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_7          */ {(U2)DTF_BID_MET_RESERVE_7_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_046,  (U2)RIMID_U1_NVMC_ST_DTF_046, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_8          */ {(U2)DTF_BID_MET_RESERVE_8_0,          (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_047, (U2)RIMID_U1_NVMC_ST_DTF_047, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_9          */ {(U2)DTF_BID_MET_RESERVE_9_0,          (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_048, (U2)RIMID_U1_NVMC_ST_DTF_048, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* BSW_SECOC_TRIP_CNT     */ {(U2)DTF_BID_BSW_SECOC_TRIP_CNT_0,     (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_049,  (U2)RIMID_U1_NVMC_ST_DTF_049, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_TMSTP             */ {(U2)DTF_BID_TMSTP,                    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_050, (U2)RIMID_U1_NVMC_ST_DTF_050, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_LOGRX1        */ {(U2)DTF_BID_DTC_LOGRX1_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_051,  (U2)RIMID_U1_NVMC_ST_DTF_051, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_DTC_EVENT001      */ {(U2)DTF_BID_DTC_EVENT001,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_052, (U2)RIMID_U1_NVMC_ST_DTF_052, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT002      */ {(U2)DTF_BID_DTC_EVENT002,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_053, (U2)RIMID_U1_NVMC_ST_DTF_053, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT003      */ {(U2)DTF_BID_DTC_EVENT003,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_054, (U2)RIMID_U1_NVMC_ST_DTF_054, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT004      */ {(U2)DTF_BID_DTC_EVENT004,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_055, (U2)RIMID_U1_NVMC_ST_DTF_055, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT005      */ {(U2)DTF_BID_DTC_EVENT005,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_056, (U2)RIMID_U1_NVMC_ST_DTF_056, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT006      */ {(U2)DTF_BID_DTC_EVENT006,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_057, (U2)RIMID_U1_NVMC_ST_DTF_057, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT007      */ {(U2)DTF_BID_DTC_EVENT007,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_058, (U2)RIMID_U1_NVMC_ST_DTF_058, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT008      */ {(U2)DTF_BID_DTC_EVENT008,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_059, (U2)RIMID_U1_NVMC_ST_DTF_059, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT009      */ {(U2)DTF_BID_DTC_EVENT009,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_060, (U2)RIMID_U1_NVMC_ST_DTF_060, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT010      */ {(U2)DTF_BID_DTC_EVENT010,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_061, (U2)RIMID_U1_NVMC_ST_DTF_061, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT011      */ {(U2)DTF_BID_DTC_EVENT011,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_062, (U2)RIMID_U1_NVMC_ST_DTF_062, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT012      */ {(U2)DTF_BID_DTC_EVENT012,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_063, (U2)RIMID_U1_NVMC_ST_DTF_063, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT013      */ {(U2)DTF_BID_DTC_EVENT013,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_064, (U2)RIMID_U1_NVMC_ST_DTF_064, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT014      */ {(U2)DTF_BID_DTC_EVENT014,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_065, (U2)RIMID_U1_NVMC_ST_DTF_065, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT015      */ {(U2)DTF_BID_DTC_EVENT015,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_066, (U2)RIMID_U1_NVMC_ST_DTF_066, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT016      */ {(U2)DTF_BID_DTC_EVENT016,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_067, (U2)RIMID_U1_NVMC_ST_DTF_067, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT017      */ {(U2)DTF_BID_DTC_EVENT017,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_068, (U2)RIMID_U1_NVMC_ST_DTF_068, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT018      */ {(U2)DTF_BID_DTC_EVENT018,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_069, (U2)RIMID_U1_NVMC_ST_DTF_069, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT019      */ {(U2)DTF_BID_DTC_EVENT019,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_070, (U2)RIMID_U1_NVMC_ST_DTF_070, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT020      */ {(U2)DTF_BID_DTC_EVENT020,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_071, (U2)RIMID_U1_NVMC_ST_DTF_071, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT021      */ {(U2)DTF_BID_DTC_EVENT021,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_072, (U2)RIMID_U1_NVMC_ST_DTF_072, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT001      */ {(U2)DTF_BID_DTC_FAULT001,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_073, (U2)RIMID_U1_NVMC_ST_DTF_073, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT002      */ {(U2)DTF_BID_DTC_FAULT002,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_074, (U2)RIMID_U1_NVMC_ST_DTF_074, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT003      */ {(U2)DTF_BID_DTC_FAULT003,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_075, (U2)RIMID_U1_NVMC_ST_DTF_075, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT004      */ {(U2)DTF_BID_DTC_FAULT004,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_076, (U2)RIMID_U1_NVMC_ST_DTF_076, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT005      */ {(U2)DTF_BID_DTC_FAULT005,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_077, (U2)RIMID_U1_NVMC_ST_DTF_077, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT006      */ {(U2)DTF_BID_DTC_FAULT006,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_078, (U2)RIMID_U1_NVMC_ST_DTF_078, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT007      */ {(U2)DTF_BID_DTC_FAULT007,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_079, (U2)RIMID_U1_NVMC_ST_DTF_079, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT008      */ {(U2)DTF_BID_DTC_FAULT008,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_080, (U2)RIMID_U1_NVMC_ST_DTF_080, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT009      */ {(U2)DTF_BID_DTC_FAULT009,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_081, (U2)RIMID_U1_NVMC_ST_DTF_081, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT010      */ {(U2)DTF_BID_DTC_FAULT010,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_082, (U2)RIMID_U1_NVMC_ST_DTF_082, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT011      */ {(U2)DTF_BID_DTC_FAULT011,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_083, (U2)RIMID_U1_NVMC_ST_DTF_083, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT012      */ {(U2)DTF_BID_DTC_FAULT012,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_084, (U2)RIMID_U1_NVMC_ST_DTF_084, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT013      */ {(U2)DTF_BID_DTC_FAULT013,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_085, (U2)RIMID_U1_NVMC_ST_DTF_085, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT014      */ {(U2)DTF_BID_DTC_FAULT014,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_086, (U2)RIMID_U1_NVMC_ST_DTF_086, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT015      */ {(U2)DTF_BID_DTC_FAULT015,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_087, (U2)RIMID_U1_NVMC_ST_DTF_087, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT016      */ {(U2)DTF_BID_DTC_FAULT016,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_088, (U2)RIMID_U1_NVMC_ST_DTF_088, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT017      */ {(U2)DTF_BID_DTC_FAULT017,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_089, (U2)RIMID_U1_NVMC_ST_DTF_089, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT018      */ {(U2)DTF_BID_DTC_FAULT018,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_090, (U2)RIMID_U1_NVMC_ST_DTF_090, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT019      */ {(U2)DTF_BID_DTC_FAULT019,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_091, (U2)RIMID_U1_NVMC_ST_DTF_091, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT020      */ {(U2)DTF_BID_DTC_FAULT020,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_092, (U2)RIMID_U1_NVMC_ST_DTF_092, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT021      */ {(U2)DTF_BID_DTC_FAULT021,             (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_093, (U2)RIMID_U1_NVMC_ST_DTF_093, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD001        */ {(U2)DTF_BID_DTC_FFD001,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_094, (U2)RIMID_U1_NVMC_ST_DTF_094, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD002        */ {(U2)DTF_BID_DTC_FFD002,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_095, (U2)RIMID_U1_NVMC_ST_DTF_095, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD003        */ {(U2)DTF_BID_DTC_FFD003,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_096, (U2)RIMID_U1_NVMC_ST_DTF_096, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD004        */ {(U2)DTF_BID_DTC_FFD004,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_097, (U2)RIMID_U1_NVMC_ST_DTF_097, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD005        */ {(U2)DTF_BID_DTC_FFD005,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_098, (U2)RIMID_U1_NVMC_ST_DTF_098, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD006        */ {(U2)DTF_BID_DTC_FFD006,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_099, (U2)RIMID_U1_NVMC_ST_DTF_099, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD007        */ {(U2)DTF_BID_DTC_FFD007,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_100, (U2)RIMID_U1_NVMC_ST_DTF_100, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD008        */ {(U2)DTF_BID_DTC_FFD008,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_101, (U2)RIMID_U1_NVMC_ST_DTF_101, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD009        */ {(U2)DTF_BID_DTC_FFD009,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_102, (U2)RIMID_U1_NVMC_ST_DTF_102, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD010        */ {(U2)DTF_BID_DTC_FFD010,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_103, (U2)RIMID_U1_NVMC_ST_DTF_103, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD011        */ {(U2)DTF_BID_DTC_FFD011,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_104, (U2)RIMID_U1_NVMC_ST_DTF_104, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD012        */ {(U2)DTF_BID_DTC_FFD012,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_105, (U2)RIMID_U1_NVMC_ST_DTF_105, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD013        */ {(U2)DTF_BID_DTC_FFD013,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_106, (U2)RIMID_U1_NVMC_ST_DTF_106, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD014        */ {(U2)DTF_BID_DTC_FFD014,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_107, (U2)RIMID_U1_NVMC_ST_DTF_107, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD015        */ {(U2)DTF_BID_DTC_FFD015,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_108, (U2)RIMID_U1_NVMC_ST_DTF_108, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD016        */ {(U2)DTF_BID_DTC_FFD016,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_109, (U2)RIMID_U1_NVMC_ST_DTF_109, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD017        */ {(U2)DTF_BID_DTC_FFD017,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_110, (U2)RIMID_U1_NVMC_ST_DTF_110, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD018        */ {(U2)DTF_BID_DTC_FFD018,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_111, (U2)RIMID_U1_NVMC_ST_DTF_111, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD019        */ {(U2)DTF_BID_DTC_FFD019,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_112, (U2)RIMID_U1_NVMC_ST_DTF_112, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD020        */ {(U2)DTF_BID_DTC_FFD020,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_113, (U2)RIMID_U1_NVMC_ST_DTF_113, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD021        */ {(U2)DTF_BID_DTC_FFD021,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_114, (U2)RIMID_U1_NVMC_ST_DTF_114, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_CLEARINFO     */ {(U2)DTF_BID_DTC_CLEARINFO,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_115, (U2)RIMID_U1_NVMC_ST_DTF_115, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_EVENT001   */ {(U2)DTF_BID_UDTC11_EVENT001,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_116,  (U2)RIMID_U1_NVMC_ST_DTF_116, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC11_EVENT002   */ {(U2)DTF_BID_UDTC11_EVENT002,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_117,  (U2)RIMID_U1_NVMC_ST_DTF_117, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC11_EVENT003   */ {(U2)DTF_BID_UDTC11_EVENT003,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_118,  (U2)RIMID_U1_NVMC_ST_DTF_118, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC11_EVENT004   */ {(U2)DTF_BID_UDTC11_EVENT004,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_119,  (U2)RIMID_U1_NVMC_ST_DTF_119, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC11_EVENT005   */ {(U2)DTF_BID_UDTC11_EVENT005,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_120,  (U2)RIMID_U1_NVMC_ST_DTF_120, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC11_EVENT006   */ {(U2)DTF_BID_UDTC11_EVENT006,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_121,  (U2)RIMID_U1_NVMC_ST_DTF_121, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC12_EVENT001   */ {(U2)DTF_BID_UDTC12_EVENT001,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_122,  (U2)RIMID_U1_NVMC_ST_DTF_122, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC12_EVENT002   */ {(U2)DTF_BID_UDTC12_EVENT002,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_123,  (U2)RIMID_U1_NVMC_ST_DTF_123, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC12_EVENT003   */ {(U2)DTF_BID_UDTC12_EVENT003,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_124,  (U2)RIMID_U1_NVMC_ST_DTF_124, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC13_EVENT001   */ {(U2)DTF_BID_UDTC13_EVENT001,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_125,  (U2)RIMID_U1_NVMC_ST_DTF_125, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC13_EVENT002   */ {(U2)DTF_BID_UDTC13_EVENT002,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_126,  (U2)RIMID_U1_NVMC_ST_DTF_126, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_UDTC11_FAULT001   */ {(U2)DTF_BID_UDTC11_FAULT001,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_127, (U2)RIMID_U1_NVMC_ST_DTF_127, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FAULT002   */ {(U2)DTF_BID_UDTC11_FAULT002,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_128, (U2)RIMID_U1_NVMC_ST_DTF_128, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FAULT003   */ {(U2)DTF_BID_UDTC11_FAULT003,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_129, (U2)RIMID_U1_NVMC_ST_DTF_129, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FAULT004   */ {(U2)DTF_BID_UDTC11_FAULT004,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_130, (U2)RIMID_U1_NVMC_ST_DTF_130, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FAULT005   */ {(U2)DTF_BID_UDTC11_FAULT005,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_131, (U2)RIMID_U1_NVMC_ST_DTF_131, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FAULT006   */ {(U2)DTF_BID_UDTC11_FAULT006,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_132, (U2)RIMID_U1_NVMC_ST_DTF_132, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC12_FAULT001   */ {(U2)DTF_BID_UDTC12_FAULT001,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_133, (U2)RIMID_U1_NVMC_ST_DTF_133, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC12_FAULT002   */ {(U2)DTF_BID_UDTC12_FAULT002,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_134, (U2)RIMID_U1_NVMC_ST_DTF_134, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC12_FAULT003   */ {(U2)DTF_BID_UDTC12_FAULT003,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_135, (U2)RIMID_U1_NVMC_ST_DTF_135, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC13_FAULT001   */ {(U2)DTF_BID_UDTC13_FAULT001,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_136, (U2)RIMID_U1_NVMC_ST_DTF_136, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC13_FAULT002   */ {(U2)DTF_BID_UDTC13_FAULT002,          (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_137, (U2)RIMID_U1_NVMC_ST_DTF_137, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD001     */ {(U2)DTF_BID_UDTC11_FFD001,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_138, (U2)RIMID_U1_NVMC_ST_DTF_138, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD002     */ {(U2)DTF_BID_UDTC11_FFD002,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_139, (U2)RIMID_U1_NVMC_ST_DTF_139, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD003     */ {(U2)DTF_BID_UDTC11_FFD003,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_140, (U2)RIMID_U1_NVMC_ST_DTF_140, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD004     */ {(U2)DTF_BID_UDTC11_FFD004,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_141, (U2)RIMID_U1_NVMC_ST_DTF_141, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD005     */ {(U2)DTF_BID_UDTC11_FFD005,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_142, (U2)RIMID_U1_NVMC_ST_DTF_142, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD006     */ {(U2)DTF_BID_UDTC11_FFD006,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_143, (U2)RIMID_U1_NVMC_ST_DTF_143, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD007     */ {(U2)DTF_BID_UDTC11_FFD007,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_144, (U2)RIMID_U1_NVMC_ST_DTF_144, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD008     */ {(U2)DTF_BID_UDTC11_FFD008,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_145, (U2)RIMID_U1_NVMC_ST_DTF_145, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD009     */ {(U2)DTF_BID_UDTC11_FFD009,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_146, (U2)RIMID_U1_NVMC_ST_DTF_146, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD010     */ {(U2)DTF_BID_UDTC11_FFD010,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_147, (U2)RIMID_U1_NVMC_ST_DTF_147, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD011     */ {(U2)DTF_BID_UDTC11_FFD011,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_148, (U2)RIMID_U1_NVMC_ST_DTF_148, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD012     */ {(U2)DTF_BID_UDTC11_FFD012,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_149, (U2)RIMID_U1_NVMC_ST_DTF_149, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD013     */ {(U2)DTF_BID_UDTC11_FFD013,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_150, (U2)RIMID_U1_NVMC_ST_DTF_150, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD014     */ {(U2)DTF_BID_UDTC11_FFD014,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_151, (U2)RIMID_U1_NVMC_ST_DTF_151, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD015     */ {(U2)DTF_BID_UDTC11_FFD015,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_152, (U2)RIMID_U1_NVMC_ST_DTF_152, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD016     */ {(U2)DTF_BID_UDTC11_FFD016,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_153, (U2)RIMID_U1_NVMC_ST_DTF_153, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD017     */ {(U2)DTF_BID_UDTC11_FFD017,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_154, (U2)RIMID_U1_NVMC_ST_DTF_154, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD018     */ {(U2)DTF_BID_UDTC11_FFD018,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_155, (U2)RIMID_U1_NVMC_ST_DTF_155, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD019     */ {(U2)DTF_BID_UDTC11_FFD019,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_156, (U2)RIMID_U1_NVMC_ST_DTF_156, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD020     */ {(U2)DTF_BID_UDTC11_FFD020,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_157, (U2)RIMID_U1_NVMC_ST_DTF_157, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD021     */ {(U2)DTF_BID_UDTC11_FFD021,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_158, (U2)RIMID_U1_NVMC_ST_DTF_158, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD022     */ {(U2)DTF_BID_UDTC11_FFD022,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_159, (U2)RIMID_U1_NVMC_ST_DTF_159, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD023     */ {(U2)DTF_BID_UDTC11_FFD023,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_160, (U2)RIMID_U1_NVMC_ST_DTF_160, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD024     */ {(U2)DTF_BID_UDTC11_FFD024,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_161, (U2)RIMID_U1_NVMC_ST_DTF_161, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD025     */ {(U2)DTF_BID_UDTC11_FFD025,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_162, (U2)RIMID_U1_NVMC_ST_DTF_162, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD026     */ {(U2)DTF_BID_UDTC11_FFD026,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_163, (U2)RIMID_U1_NVMC_ST_DTF_163, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD027     */ {(U2)DTF_BID_UDTC11_FFD027,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_164, (U2)RIMID_U1_NVMC_ST_DTF_164, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD028     */ {(U2)DTF_BID_UDTC11_FFD028,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_165, (U2)RIMID_U1_NVMC_ST_DTF_165, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD029     */ {(U2)DTF_BID_UDTC11_FFD029,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_166, (U2)RIMID_U1_NVMC_ST_DTF_166, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD030     */ {(U2)DTF_BID_UDTC11_FFD030,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_167, (U2)RIMID_U1_NVMC_ST_DTF_167, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD031     */ {(U2)DTF_BID_UDTC11_FFD031,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_168, (U2)RIMID_U1_NVMC_ST_DTF_168, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD032     */ {(U2)DTF_BID_UDTC11_FFD032,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_169, (U2)RIMID_U1_NVMC_ST_DTF_169, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD033     */ {(U2)DTF_BID_UDTC11_FFD033,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_170, (U2)RIMID_U1_NVMC_ST_DTF_170, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD034     */ {(U2)DTF_BID_UDTC11_FFD034,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_171, (U2)RIMID_U1_NVMC_ST_DTF_171, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD035     */ {(U2)DTF_BID_UDTC11_FFD035,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_172, (U2)RIMID_U1_NVMC_ST_DTF_172, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD036     */ {(U2)DTF_BID_UDTC11_FFD036,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_173, (U2)RIMID_U1_NVMC_ST_DTF_173, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD037     */ {(U2)DTF_BID_UDTC11_FFD037,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_174, (U2)RIMID_U1_NVMC_ST_DTF_174, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD038     */ {(U2)DTF_BID_UDTC11_FFD038,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_175, (U2)RIMID_U1_NVMC_ST_DTF_175, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD039     */ {(U2)DTF_BID_UDTC11_FFD039,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_176, (U2)RIMID_U1_NVMC_ST_DTF_176, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD040     */ {(U2)DTF_BID_UDTC11_FFD040,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_177, (U2)RIMID_U1_NVMC_ST_DTF_177, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD041     */ {(U2)DTF_BID_UDTC11_FFD041,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_178, (U2)RIMID_U1_NVMC_ST_DTF_178, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD042     */ {(U2)DTF_BID_UDTC11_FFD042,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_179, (U2)RIMID_U1_NVMC_ST_DTF_179, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD043     */ {(U2)DTF_BID_UDTC11_FFD043,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_180, (U2)RIMID_U1_NVMC_ST_DTF_180, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD044     */ {(U2)DTF_BID_UDTC11_FFD044,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_181, (U2)RIMID_U1_NVMC_ST_DTF_181, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD045     */ {(U2)DTF_BID_UDTC11_FFD045,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_182, (U2)RIMID_U1_NVMC_ST_DTF_182, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD046     */ {(U2)DTF_BID_UDTC11_FFD046,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_183, (U2)RIMID_U1_NVMC_ST_DTF_183, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD047     */ {(U2)DTF_BID_UDTC11_FFD047,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_184, (U2)RIMID_U1_NVMC_ST_DTF_184, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD048     */ {(U2)DTF_BID_UDTC11_FFD048,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_185, (U2)RIMID_U1_NVMC_ST_DTF_185, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD049     */ {(U2)DTF_BID_UDTC11_FFD049,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_186, (U2)RIMID_U1_NVMC_ST_DTF_186, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD050     */ {(U2)DTF_BID_UDTC11_FFD050,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_187, (U2)RIMID_U1_NVMC_ST_DTF_187, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD051     */ {(U2)DTF_BID_UDTC11_FFD051,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_188, (U2)RIMID_U1_NVMC_ST_DTF_188, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD052     */ {(U2)DTF_BID_UDTC11_FFD052,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_189, (U2)RIMID_U1_NVMC_ST_DTF_189, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD053     */ {(U2)DTF_BID_UDTC11_FFD053,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_190, (U2)RIMID_U1_NVMC_ST_DTF_190, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC11_FFD054     */ {(U2)DTF_BID_UDTC11_FFD054,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_191, (U2)RIMID_U1_NVMC_ST_DTF_191, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC12_FFD001     */ {(U2)DTF_BID_UDTC12_FFD001,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_192, (U2)RIMID_U1_NVMC_ST_DTF_192, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC12_FFD002     */ {(U2)DTF_BID_UDTC12_FFD002,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_193, (U2)RIMID_U1_NVMC_ST_DTF_193, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC12_FFD003     */ {(U2)DTF_BID_UDTC12_FFD003,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_194, (U2)RIMID_U1_NVMC_ST_DTF_194, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC13_FFD001     */ {(U2)DTF_BID_UDTC13_FFD001,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_195, (U2)RIMID_U1_NVMC_ST_DTF_195, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC13_FFD002     */ {(U2)DTF_BID_UDTC13_FFD002,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_196, (U2)RIMID_U1_NVMC_ST_DTF_196, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC13_FFD003     */ {(U2)DTF_BID_UDTC13_FFD003,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_197, (U2)RIMID_U1_NVMC_ST_DTF_197, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_UDTC13_FFD004     */ {(U2)DTF_BID_UDTC13_FFD004,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_198, (U2)RIMID_U1_NVMC_ST_DTF_198, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_ROE_A005          */ {(U2)DTF_BID_ROE_A005,                 (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_199, (U2)RIMID_U1_NVMC_ST_DTF_199, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10A1_0     */ {(U2)DTF_BID_SSR_22_10A1_0,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_200, (U2)RIMID_U1_NVMC_ST_DTF_200, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10A1_1     */ {(U2)DTF_BID_SSR_22_10A1_1,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_201, (U2)RIMID_U1_NVMC_ST_DTF_201, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10A1_2     */ {(U2)DTF_BID_SSR_22_10A1_2,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_202, (U2)RIMID_U1_NVMC_ST_DTF_202, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10A3_0     */ {(U2)DTF_BID_SSR_22_10A3_0,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_203, (U2)RIMID_U1_NVMC_ST_DTF_203, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10A3_1     */ {(U2)DTF_BID_SSR_22_10A3_1,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_204, (U2)RIMID_U1_NVMC_ST_DTF_204, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10A3_2     */ {(U2)DTF_BID_SSR_22_10A3_2,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_205, (U2)RIMID_U1_NVMC_ST_DTF_205, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10AB_0     */ {(U2)DTF_BID_SSR_22_10AB_0,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_206, (U2)RIMID_U1_NVMC_ST_DTF_206, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10AB_1     */ {(U2)DTF_BID_SSR_22_10AB_1,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_207, (U2)RIMID_U1_NVMC_ST_DTF_207, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10AB_2     */ {(U2)DTF_BID_SSR_22_10AB_2,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_208, (U2)RIMID_U1_NVMC_ST_DTF_208, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10AF_0     */ {(U2)DTF_BID_SSR_22_10AF_0,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_209, (U2)RIMID_U1_NVMC_ST_DTF_209, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10AF_1     */ {(U2)DTF_BID_SSR_22_10AF_1,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_210, (U2)RIMID_U1_NVMC_ST_DTF_210, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10AF_2     */ {(U2)DTF_BID_SSR_22_10AF_2,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_211, (U2)RIMID_U1_NVMC_ST_DTF_211, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10B6_0     */ {(U2)DTF_BID_SSR_22_10B6_0,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_212, (U2)RIMID_U1_NVMC_ST_DTF_212, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10B6_1     */ {(U2)DTF_BID_SSR_22_10B6_1,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_213, (U2)RIMID_U1_NVMC_ST_DTF_213, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_22_10B6_2     */ {(U2)DTF_BID_SSR_22_10B6_2,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_214, (U2)RIMID_U1_NVMC_ST_DTF_214, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_2002           */ {(U2)DTF_BID_2E_2002_0,                (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_215,  (U2)RIMID_U1_NVMC_ST_DTF_215, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0xFFFFFFFFU, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_2E_2003           */ {(U2)DTF_BID_2E_2003_0,                (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_216,  (U2)RIMID_U1_NVMC_ST_DTF_216, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0xFFFFFFFFU, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_2E_2041           */ {(U2)DTF_BID_2E_2041_0,                (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_217,  (U2)RIMID_U1_NVMC_ST_DTF_217, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0xFFFFFFFFU, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_2E_20C2           */ {(U2)DTF_BID_2E_20C2_0,                (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_218,  (U2)RIMID_U1_NVMC_ST_DTF_218, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0xFFFFFFFFU, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_2E_220E_0         */ {(U2)DTF_BID_2E_220E_0,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_219, (U2)RIMID_U1_NVMC_ST_DTF_219, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_1         */ {(U2)DTF_BID_2E_220E_1,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_220, (U2)RIMID_U1_NVMC_ST_DTF_220, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_2         */ {(U2)DTF_BID_2E_220E_2,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_221, (U2)RIMID_U1_NVMC_ST_DTF_221, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_3         */ {(U2)DTF_BID_2E_220E_3,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_222, (U2)RIMID_U1_NVMC_ST_DTF_222, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_4         */ {(U2)DTF_BID_2E_220E_4,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_223, (U2)RIMID_U1_NVMC_ST_DTF_223, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_5         */ {(U2)DTF_BID_2E_220E_5,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_224, (U2)RIMID_U1_NVMC_ST_DTF_224, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_6         */ {(U2)DTF_BID_2E_220E_6,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_225, (U2)RIMID_U1_NVMC_ST_DTF_225, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_7         */ {(U2)DTF_BID_2E_220E_7,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_226, (U2)RIMID_U1_NVMC_ST_DTF_226, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_8         */ {(U2)DTF_BID_2E_220E_8,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_227, (U2)RIMID_U1_NVMC_ST_DTF_227, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_9         */ {(U2)DTF_BID_2E_220E_9,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_228, (U2)RIMID_U1_NVMC_ST_DTF_228, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_10        */ {(U2)DTF_BID_2E_220E_10,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_229, (U2)RIMID_U1_NVMC_ST_DTF_229, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_11        */ {(U2)DTF_BID_2E_220E_11,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_230, (U2)RIMID_U1_NVMC_ST_DTF_230, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_12        */ {(U2)DTF_BID_2E_220E_12,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_231, (U2)RIMID_U1_NVMC_ST_DTF_231, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_13        */ {(U2)DTF_BID_2E_220E_13,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_232, (U2)RIMID_U1_NVMC_ST_DTF_232, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_14        */ {(U2)DTF_BID_2E_220E_14,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_233, (U2)RIMID_U1_NVMC_ST_DTF_233, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_15        */ {(U2)DTF_BID_2E_220E_15,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_234, (U2)RIMID_U1_NVMC_ST_DTF_234, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_16        */ {(U2)DTF_BID_2E_220E_16,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_235, (U2)RIMID_U1_NVMC_ST_DTF_235, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_17        */ {(U2)DTF_BID_2E_220E_17,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_236, (U2)RIMID_U1_NVMC_ST_DTF_236, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_18        */ {(U2)DTF_BID_2E_220E_18,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_237, (U2)RIMID_U1_NVMC_ST_DTF_237, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_2E_220E_19        */ {(U2)DTF_BID_2E_220E_19,               (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_238, (U2)RIMID_U1_NVMC_ST_DTF_238, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0xD0U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_BA_D1L1_0     */ {(U2)DTF_BID_SSR_BA_D1L1_0,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_239, (U2)RIMID_U1_NVMC_ST_DTF_239, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_BA_D1L1_1     */ {(U2)DTF_BID_SSR_BA_D1L1_1,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_240, (U2)RIMID_U1_NVMC_ST_DTF_240, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_BA_D1L1_2     */ {(U2)DTF_BID_SSR_BA_D1L1_2,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_241, (U2)RIMID_U1_NVMC_ST_DTF_241, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_BA_D1L1_3     */ {(U2)DTF_BID_SSR_BA_D1L1_3,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_242, (U2)RIMID_U1_NVMC_ST_DTF_242, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_BA_D1L1_4     */ {(U2)DTF_BID_SSR_BA_D1L1_4,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_243, (U2)RIMID_U1_NVMC_ST_DTF_243, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_BA_RCAR_0     */ {(U2)DTF_BID_SSR_BA_RCAR_0,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_244, (U2)RIMID_U1_NVMC_ST_DTF_244, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_BA_RCAR_1     */ {(U2)DTF_BID_SSR_BA_RCAR_1,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_245, (U2)RIMID_U1_NVMC_ST_DTF_245, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_BA_RCAR_2     */ {(U2)DTF_BID_SSR_BA_RCAR_2,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_246, (U2)RIMID_U1_NVMC_ST_DTF_246, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_BA_RCAR_3     */ {(U2)DTF_BID_SSR_BA_RCAR_3,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_247, (U2)RIMID_U1_NVMC_ST_DTF_247, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SSR_BA_RCAR_4     */ {(U2)DTF_BID_SSR_BA_RCAR_4,            (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_248, (U2)RIMID_U1_NVMC_ST_DTF_248, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* MET_RESERVE_10         */ {(U2)DTF_BID_MET_RESERVE_10_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_249,  (U2)RIMID_U1_NVMC_ST_DTF_249, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_11         */ {(U2)DTF_BID_MET_RESERVE_11_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_250,  (U2)RIMID_U1_NVMC_ST_DTF_250, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_12         */ {(U2)DTF_BID_MET_RESERVE_12_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_251,  (U2)RIMID_U1_NVMC_ST_DTF_251, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_13         */ {(U2)DTF_BID_MET_RESERVE_13_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_252,  (U2)RIMID_U1_NVMC_ST_DTF_252, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_14         */ {(U2)DTF_BID_MET_RESERVE_14_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_253,  (U2)RIMID_U1_NVMC_ST_DTF_253, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_15         */ {(U2)DTF_BID_MET_RESERVE_15_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_254,  (U2)RIMID_U1_NVMC_ST_DTF_254, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_16         */ {(U2)DTF_BID_MET_RESERVE_16_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_255,  (U2)RIMID_U1_NVMC_ST_DTF_255, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_17         */ {(U2)DTF_BID_MET_RESERVE_17_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_256,  (U2)RIMID_U1_NVMC_ST_DTF_256, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_18         */ {(U2)DTF_BID_MET_RESERVE_18_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_257, (U2)RIMID_U1_NVMC_ST_DTF_257, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_19         */ {(U2)DTF_BID_MET_RESERVE_19_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_258, (U2)RIMID_U1_NVMC_ST_DTF_258, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W0             */ {(U2)DTF_BID_VDF_ESO_W0_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_259,  (U2)RIMID_U1_NVMC_ST_DTF_259, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W1             */ {(U2)DTF_BID_VDF_ESO_W1_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_260,  (U2)RIMID_U1_NVMC_ST_DTF_260, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W2             */ {(U2)DTF_BID_VDF_ESO_W2_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_261,  (U2)RIMID_U1_NVMC_ST_DTF_261, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W3             */ {(U2)DTF_BID_VDF_ESO_W3_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_262,  (U2)RIMID_U1_NVMC_ST_DTF_262, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W4             */ {(U2)DTF_BID_VDF_ESO_W4_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_263,  (U2)RIMID_U1_NVMC_ST_DTF_263, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W5             */ {(U2)DTF_BID_VDF_ESO_W5_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_264,  (U2)RIMID_U1_NVMC_ST_DTF_264, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W6             */ {(U2)DTF_BID_VDF_ESO_W6_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_265,  (U2)RIMID_U1_NVMC_ST_DTF_265, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W7             */ {(U2)DTF_BID_VDF_ESO_W7_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_266,  (U2)RIMID_U1_NVMC_ST_DTF_266, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* VDF_ESO_W8             */ {(U2)DTF_BID_VDF_ESO_W8_0,             (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_267,  (U2)RIMID_U1_NVMC_ST_DTF_267, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* ODO_INHERIT_FLG        */ {(U2)DTF_BID_ODO_INHERIT_FLG_0,        (U2)0x0001U, (U2)RIMID_U1_NVMC_DA_DTF_WRI_268,  (U2)RIMID_U1_NVMC_ST_DTF_268, (U1)NVMC_MODULE_U1_P1_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x000000FFU}},
/* FWUSH_FSWASTAT_0_INFO  */ {(U2)DTF_BID_FWUSH_FSWASTAT_0_INFO_0,  (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_269,  (U2)RIMID_U1_NVMC_ST_DTF_269, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* FWUSH_VERIFY_LBN_COMP  */ {(U2)DTF_BID_FWUSH_VERIFY_LBN_COMP_0,  (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_270,  (U2)RIMID_U1_NVMC_ST_DTF_270, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* FWUSH_SEQ_PROGRESS     */ {(U2)DTF_BID_FWUSH_SEQ_PROGRESS_0,     (U2)0x0001U, (U2)RIMID_U1_NVMC_DA_DTF_WRI_271,  (U2)RIMID_U1_NVMC_ST_DTF_271, (U1)NVMC_MODULE_U1_P1_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x000000FFU}},
/* MET_RESERVE_20         */ {(U2)DTF_BID_MET_RESERVE_20_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_272,  (U2)RIMID_U1_NVMC_ST_DTF_272, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_21         */ {(U2)DTF_BID_MET_RESERVE_21_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_273,  (U2)RIMID_U1_NVMC_ST_DTF_273, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_22         */ {(U2)DTF_BID_MET_RESERVE_22_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_274,  (U2)RIMID_U1_NVMC_ST_DTF_274, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_23         */ {(U2)DTF_BID_MET_RESERVE_23_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_275,  (U2)RIMID_U1_NVMC_ST_DTF_275, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_24         */ {(U2)DTF_BID_MET_RESERVE_24_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_276,  (U2)RIMID_U1_NVMC_ST_DTF_276, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_25         */ {(U2)DTF_BID_MET_RESERVE_25_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_277,  (U2)RIMID_U1_NVMC_ST_DTF_277, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_26         */ {(U2)DTF_BID_MET_RESERVE_26_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_278,  (U2)RIMID_U1_NVMC_ST_DTF_278, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_27         */ {(U2)DTF_BID_MET_RESERVE_27_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_279,  (U2)RIMID_U1_NVMC_ST_DTF_279, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_28         */ {(U2)DTF_BID_MET_RESERVE_28_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_280, (U2)RIMID_U1_NVMC_ST_DTF_280, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_29         */ {(U2)DTF_BID_MET_RESERVE_29_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_281, (U2)RIMID_U1_NVMC_ST_DTF_281, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_22_F18A           */ {(U2)DTF_BID_22_F18A_0,                (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_282, (U2)RIMID_U1_NVMC_ST_DTF_282, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_8,  (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01033333U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_22_SERI_N_10B     */ {(U2)DTF_BID_22_SERI_N_10B_0,          (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_283, (U2)RIMID_U1_NVMC_ST_DTF_283, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_12, (U1)0x01U,     (U1)0x01U,      (U1)0x24U,      (U4)0x01033333U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_22_ECU_PN_10B     */ {(U2)DTF_BID_22_ECU_PN_10B_0,          (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_284, (U2)RIMID_U1_NVMC_ST_DTF_284, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_12, (U1)0x01U,     (U1)0x01U,      (U1)0x24U,      (U4)0x01033333U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_BA_NUO_DI         */ {(U2)DTF_BID_BA_NUO_DI_0,              (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_285,  (U2)RIMID_U1_NVMC_ST_DTF_285, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01033333U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_BA_SAFEKEY_NUM    */ {(U2)DTF_BID_BA_SAFEKEY_NUM_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_286, (U2)RIMID_U1_NVMC_ST_DTF_286, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_16, (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_30         */ {(U2)DTF_BID_MET_RESERVE_30_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_287,  (U2)RIMID_U1_NVMC_ST_DTF_287, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_31         */ {(U2)DTF_BID_MET_RESERVE_31_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_288,  (U2)RIMID_U1_NVMC_ST_DTF_288, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_32         */ {(U2)DTF_BID_MET_RESERVE_32_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_289,  (U2)RIMID_U1_NVMC_ST_DTF_289, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_33         */ {(U2)DTF_BID_MET_RESERVE_33_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_290,  (U2)RIMID_U1_NVMC_ST_DTF_290, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_34         */ {(U2)DTF_BID_MET_RESERVE_34_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_291,  (U2)RIMID_U1_NVMC_ST_DTF_291, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_35         */ {(U2)DTF_BID_MET_RESERVE_35_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_292,  (U2)RIMID_U1_NVMC_ST_DTF_292, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_36         */ {(U2)DTF_BID_MET_RESERVE_36_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_293,  (U2)RIMID_U1_NVMC_ST_DTF_293, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_37         */ {(U2)DTF_BID_MET_RESERVE_37_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_294,  (U2)RIMID_U1_NVMC_ST_DTF_294, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_38         */ {(U2)DTF_BID_MET_RESERVE_38_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_295, (U2)RIMID_U1_NVMC_ST_DTF_295, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_39         */ {(U2)DTF_BID_MET_RESERVE_39_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_296, (U2)RIMID_U1_NVMC_ST_DTF_296, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_40         */ {(U2)DTF_BID_MET_RESERVE_40_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_297,  (U2)RIMID_U1_NVMC_ST_DTF_297, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_41         */ {(U2)DTF_BID_MET_RESERVE_41_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_298,  (U2)RIMID_U1_NVMC_ST_DTF_298, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_42         */ {(U2)DTF_BID_MET_RESERVE_42_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_299,  (U2)RIMID_U1_NVMC_ST_DTF_299, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_43         */ {(U2)DTF_BID_MET_RESERVE_43_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_300,  (U2)RIMID_U1_NVMC_ST_DTF_300, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_44         */ {(U2)DTF_BID_MET_RESERVE_44_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_301,  (U2)RIMID_U1_NVMC_ST_DTF_301, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_45         */ {(U2)DTF_BID_MET_RESERVE_45_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_302,  (U2)RIMID_U1_NVMC_ST_DTF_302, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_46         */ {(U2)DTF_BID_MET_RESERVE_46_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_303,  (U2)RIMID_U1_NVMC_ST_DTF_303, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_47         */ {(U2)DTF_BID_MET_RESERVE_47_0,         (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_304,  (U2)RIMID_U1_NVMC_ST_DTF_304, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_48         */ {(U2)DTF_BID_MET_RESERVE_48_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_305, (U2)RIMID_U1_NVMC_ST_DTF_305, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* MET_RESERVE_49         */ {(U2)DTF_BID_MET_RESERVE_49_0,         (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_306, (U2)RIMID_U1_NVMC_ST_DTF_306, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* DATESI_CALENDAR        */ {(U2)DTF_BID_DATESI_CALENDAR_0,        (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_307,  (U2)RIMID_U1_NVMC_ST_DTF_307, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x0000FFFFU, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* DATESI_OFFSET          */ {(U2)DTF_BID_DATESI_OFFSET_0,          (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_308,  (U2)RIMID_U1_NVMC_ST_DTF_308, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x0000FFFFU}},
/* PICT_MAVTYPE           */ {(U2)DTF_BID_PICT_MAVTYPE,             (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_309,  (U2)RIMID_U1_NVMC_ST_DTF_309, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PICT_RCROP0            */ {(U2)DTF_BID_PICT_RCROP0,              (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_310,  (U2)RIMID_U1_NVMC_ST_DTF_310, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PICT_STRGWHL           */ {(U2)DTF_BID_PICT_STRGWHL,             (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_311,  (U2)RIMID_U1_NVMC_ST_DTF_311, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* POWER_DEST_LOG         */ {(U2)DTF_BID_POWER_DEST_LOG_0,         (U2)0x0001U, (U2)RIMID_U1_NVMC_DA_DTF_WRI_312,  (U2)RIMID_U1_NVMC_ST_DTF_312, (U1)NVMC_MODULE_U1_P3_TRPL,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x000000FFU}},
/* WHLINI_REQ             */ {(U2)DTF_BID_WHLINI_REQ,               (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_313,  (U2)RIMID_U1_NVMC_ST_DTF_313, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* DIREC_INDEX            */ {(U2)DTF_BID_DIREC_INDEX,              (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_314,  (U2)RIMID_U1_NVMC_ST_DTF_314, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* DIREC_000              */ {(U2)DTF_BID_DIREC_000,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_315, (U2)RIMID_U1_NVMC_ST_DTF_315, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_001              */ {(U2)DTF_BID_DIREC_001,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_316, (U2)RIMID_U1_NVMC_ST_DTF_316, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_002              */ {(U2)DTF_BID_DIREC_002,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_317, (U2)RIMID_U1_NVMC_ST_DTF_317, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_003              */ {(U2)DTF_BID_DIREC_003,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_318, (U2)RIMID_U1_NVMC_ST_DTF_318, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_004              */ {(U2)DTF_BID_DIREC_004,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_319, (U2)RIMID_U1_NVMC_ST_DTF_319, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_005              */ {(U2)DTF_BID_DIREC_005,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_320, (U2)RIMID_U1_NVMC_ST_DTF_320, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_006              */ {(U2)DTF_BID_DIREC_006,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_321, (U2)RIMID_U1_NVMC_ST_DTF_321, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_007              */ {(U2)DTF_BID_DIREC_007,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_322, (U2)RIMID_U1_NVMC_ST_DTF_322, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_008              */ {(U2)DTF_BID_DIREC_008,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_323, (U2)RIMID_U1_NVMC_ST_DTF_323, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_009              */ {(U2)DTF_BID_DIREC_009,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_324, (U2)RIMID_U1_NVMC_ST_DTF_324, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_010              */ {(U2)DTF_BID_DIREC_010,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_325, (U2)RIMID_U1_NVMC_ST_DTF_325, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_011              */ {(U2)DTF_BID_DIREC_011,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_326, (U2)RIMID_U1_NVMC_ST_DTF_326, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_012              */ {(U2)DTF_BID_DIREC_012,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_327, (U2)RIMID_U1_NVMC_ST_DTF_327, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_013              */ {(U2)DTF_BID_DIREC_013,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_328, (U2)RIMID_U1_NVMC_ST_DTF_328, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_014              */ {(U2)DTF_BID_DIREC_014,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_329, (U2)RIMID_U1_NVMC_ST_DTF_329, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_015              */ {(U2)DTF_BID_DIREC_015,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_330, (U2)RIMID_U1_NVMC_ST_DTF_330, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_016              */ {(U2)DTF_BID_DIREC_016,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_331, (U2)RIMID_U1_NVMC_ST_DTF_331, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_017              */ {(U2)DTF_BID_DIREC_017,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_332, (U2)RIMID_U1_NVMC_ST_DTF_332, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_018              */ {(U2)DTF_BID_DIREC_018,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_333, (U2)RIMID_U1_NVMC_ST_DTF_333, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_019              */ {(U2)DTF_BID_DIREC_019,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_334, (U2)RIMID_U1_NVMC_ST_DTF_334, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_020              */ {(U2)DTF_BID_DIREC_020,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_335, (U2)RIMID_U1_NVMC_ST_DTF_335, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_021              */ {(U2)DTF_BID_DIREC_021,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_336, (U2)RIMID_U1_NVMC_ST_DTF_336, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_022              */ {(U2)DTF_BID_DIREC_022,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_337, (U2)RIMID_U1_NVMC_ST_DTF_337, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_023              */ {(U2)DTF_BID_DIREC_023,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_338, (U2)RIMID_U1_NVMC_ST_DTF_338, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_024              */ {(U2)DTF_BID_DIREC_024,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_339, (U2)RIMID_U1_NVMC_ST_DTF_339, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_025              */ {(U2)DTF_BID_DIREC_025,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_340, (U2)RIMID_U1_NVMC_ST_DTF_340, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_026              */ {(U2)DTF_BID_DIREC_026,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_341, (U2)RIMID_U1_NVMC_ST_DTF_341, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_027              */ {(U2)DTF_BID_DIREC_027,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_342, (U2)RIMID_U1_NVMC_ST_DTF_342, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_028              */ {(U2)DTF_BID_DIREC_028,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_343, (U2)RIMID_U1_NVMC_ST_DTF_343, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_029              */ {(U2)DTF_BID_DIREC_029,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_344, (U2)RIMID_U1_NVMC_ST_DTF_344, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_030              */ {(U2)DTF_BID_DIREC_030,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_345, (U2)RIMID_U1_NVMC_ST_DTF_345, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_031              */ {(U2)DTF_BID_DIREC_031,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_346, (U2)RIMID_U1_NVMC_ST_DTF_346, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_032              */ {(U2)DTF_BID_DIREC_032,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_347, (U2)RIMID_U1_NVMC_ST_DTF_347, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_033              */ {(U2)DTF_BID_DIREC_033,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_348, (U2)RIMID_U1_NVMC_ST_DTF_348, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_034              */ {(U2)DTF_BID_DIREC_034,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_349, (U2)RIMID_U1_NVMC_ST_DTF_349, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_035              */ {(U2)DTF_BID_DIREC_035,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_350, (U2)RIMID_U1_NVMC_ST_DTF_350, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_036              */ {(U2)DTF_BID_DIREC_036,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_351, (U2)RIMID_U1_NVMC_ST_DTF_351, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_037              */ {(U2)DTF_BID_DIREC_037,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_352, (U2)RIMID_U1_NVMC_ST_DTF_352, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_038              */ {(U2)DTF_BID_DIREC_038,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_353, (U2)RIMID_U1_NVMC_ST_DTF_353, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_039              */ {(U2)DTF_BID_DIREC_039,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_354, (U2)RIMID_U1_NVMC_ST_DTF_354, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_040              */ {(U2)DTF_BID_DIREC_040,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_355, (U2)RIMID_U1_NVMC_ST_DTF_355, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_041              */ {(U2)DTF_BID_DIREC_041,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_356, (U2)RIMID_U1_NVMC_ST_DTF_356, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_042              */ {(U2)DTF_BID_DIREC_042,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_357, (U2)RIMID_U1_NVMC_ST_DTF_357, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_043              */ {(U2)DTF_BID_DIREC_043,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_358, (U2)RIMID_U1_NVMC_ST_DTF_358, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_044              */ {(U2)DTF_BID_DIREC_044,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_359, (U2)RIMID_U1_NVMC_ST_DTF_359, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_045              */ {(U2)DTF_BID_DIREC_045,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_360, (U2)RIMID_U1_NVMC_ST_DTF_360, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_046              */ {(U2)DTF_BID_DIREC_046,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_361, (U2)RIMID_U1_NVMC_ST_DTF_361, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_047              */ {(U2)DTF_BID_DIREC_047,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_362, (U2)RIMID_U1_NVMC_ST_DTF_362, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_048              */ {(U2)DTF_BID_DIREC_048,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_363, (U2)RIMID_U1_NVMC_ST_DTF_363, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_049              */ {(U2)DTF_BID_DIREC_049,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_364, (U2)RIMID_U1_NVMC_ST_DTF_364, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_050              */ {(U2)DTF_BID_DIREC_050,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_365, (U2)RIMID_U1_NVMC_ST_DTF_365, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_051              */ {(U2)DTF_BID_DIREC_051,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_366, (U2)RIMID_U1_NVMC_ST_DTF_366, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_052              */ {(U2)DTF_BID_DIREC_052,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_367, (U2)RIMID_U1_NVMC_ST_DTF_367, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_053              */ {(U2)DTF_BID_DIREC_053,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_368, (U2)RIMID_U1_NVMC_ST_DTF_368, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_054              */ {(U2)DTF_BID_DIREC_054,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_369, (U2)RIMID_U1_NVMC_ST_DTF_369, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_055              */ {(U2)DTF_BID_DIREC_055,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_370, (U2)RIMID_U1_NVMC_ST_DTF_370, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_056              */ {(U2)DTF_BID_DIREC_056,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_371, (U2)RIMID_U1_NVMC_ST_DTF_371, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_057              */ {(U2)DTF_BID_DIREC_057,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_372, (U2)RIMID_U1_NVMC_ST_DTF_372, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_058              */ {(U2)DTF_BID_DIREC_058,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_373, (U2)RIMID_U1_NVMC_ST_DTF_373, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_059              */ {(U2)DTF_BID_DIREC_059,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_374, (U2)RIMID_U1_NVMC_ST_DTF_374, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_060              */ {(U2)DTF_BID_DIREC_060,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_375, (U2)RIMID_U1_NVMC_ST_DTF_375, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_061              */ {(U2)DTF_BID_DIREC_061,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_376, (U2)RIMID_U1_NVMC_ST_DTF_376, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_062              */ {(U2)DTF_BID_DIREC_062,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_377, (U2)RIMID_U1_NVMC_ST_DTF_377, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_063              */ {(U2)DTF_BID_DIREC_063,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_378, (U2)RIMID_U1_NVMC_ST_DTF_378, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_064              */ {(U2)DTF_BID_DIREC_064,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_379, (U2)RIMID_U1_NVMC_ST_DTF_379, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_065              */ {(U2)DTF_BID_DIREC_065,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_380, (U2)RIMID_U1_NVMC_ST_DTF_380, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_066              */ {(U2)DTF_BID_DIREC_066,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_381, (U2)RIMID_U1_NVMC_ST_DTF_381, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_067              */ {(U2)DTF_BID_DIREC_067,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_382, (U2)RIMID_U1_NVMC_ST_DTF_382, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_068              */ {(U2)DTF_BID_DIREC_068,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_383, (U2)RIMID_U1_NVMC_ST_DTF_383, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_069              */ {(U2)DTF_BID_DIREC_069,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_384, (U2)RIMID_U1_NVMC_ST_DTF_384, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_070              */ {(U2)DTF_BID_DIREC_070,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_385, (U2)RIMID_U1_NVMC_ST_DTF_385, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_071              */ {(U2)DTF_BID_DIREC_071,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_386, (U2)RIMID_U1_NVMC_ST_DTF_386, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_072              */ {(U2)DTF_BID_DIREC_072,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_387, (U2)RIMID_U1_NVMC_ST_DTF_387, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_073              */ {(U2)DTF_BID_DIREC_073,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_388, (U2)RIMID_U1_NVMC_ST_DTF_388, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_074              */ {(U2)DTF_BID_DIREC_074,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_389, (U2)RIMID_U1_NVMC_ST_DTF_389, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_075              */ {(U2)DTF_BID_DIREC_075,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_390, (U2)RIMID_U1_NVMC_ST_DTF_390, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_076              */ {(U2)DTF_BID_DIREC_076,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_391, (U2)RIMID_U1_NVMC_ST_DTF_391, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_077              */ {(U2)DTF_BID_DIREC_077,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_392, (U2)RIMID_U1_NVMC_ST_DTF_392, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_078              */ {(U2)DTF_BID_DIREC_078,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_393, (U2)RIMID_U1_NVMC_ST_DTF_393, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_079              */ {(U2)DTF_BID_DIREC_079,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_394, (U2)RIMID_U1_NVMC_ST_DTF_394, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_080              */ {(U2)DTF_BID_DIREC_080,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_395, (U2)RIMID_U1_NVMC_ST_DTF_395, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_081              */ {(U2)DTF_BID_DIREC_081,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_396, (U2)RIMID_U1_NVMC_ST_DTF_396, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_082              */ {(U2)DTF_BID_DIREC_082,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_397, (U2)RIMID_U1_NVMC_ST_DTF_397, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_083              */ {(U2)DTF_BID_DIREC_083,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_398, (U2)RIMID_U1_NVMC_ST_DTF_398, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_084              */ {(U2)DTF_BID_DIREC_084,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_399, (U2)RIMID_U1_NVMC_ST_DTF_399, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_085              */ {(U2)DTF_BID_DIREC_085,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_400, (U2)RIMID_U1_NVMC_ST_DTF_400, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_086              */ {(U2)DTF_BID_DIREC_086,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_401, (U2)RIMID_U1_NVMC_ST_DTF_401, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_087              */ {(U2)DTF_BID_DIREC_087,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_402, (U2)RIMID_U1_NVMC_ST_DTF_402, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_088              */ {(U2)DTF_BID_DIREC_088,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_403, (U2)RIMID_U1_NVMC_ST_DTF_403, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_089              */ {(U2)DTF_BID_DIREC_089,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_404, (U2)RIMID_U1_NVMC_ST_DTF_404, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_090              */ {(U2)DTF_BID_DIREC_090,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_405, (U2)RIMID_U1_NVMC_ST_DTF_405, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_091              */ {(U2)DTF_BID_DIREC_091,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_406, (U2)RIMID_U1_NVMC_ST_DTF_406, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_092              */ {(U2)DTF_BID_DIREC_092,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_407, (U2)RIMID_U1_NVMC_ST_DTF_407, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_093              */ {(U2)DTF_BID_DIREC_093,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_408, (U2)RIMID_U1_NVMC_ST_DTF_408, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_094              */ {(U2)DTF_BID_DIREC_094,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_409, (U2)RIMID_U1_NVMC_ST_DTF_409, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_095              */ {(U2)DTF_BID_DIREC_095,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_410, (U2)RIMID_U1_NVMC_ST_DTF_410, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_096              */ {(U2)DTF_BID_DIREC_096,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_411, (U2)RIMID_U1_NVMC_ST_DTF_411, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_097              */ {(U2)DTF_BID_DIREC_097,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_412, (U2)RIMID_U1_NVMC_ST_DTF_412, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_098              */ {(U2)DTF_BID_DIREC_098,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_413, (U2)RIMID_U1_NVMC_ST_DTF_413, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_099              */ {(U2)DTF_BID_DIREC_099,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_414, (U2)RIMID_U1_NVMC_ST_DTF_414, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_100              */ {(U2)DTF_BID_DIREC_100,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_415, (U2)RIMID_U1_NVMC_ST_DTF_415, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_101              */ {(U2)DTF_BID_DIREC_101,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_416, (U2)RIMID_U1_NVMC_ST_DTF_416, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_102              */ {(U2)DTF_BID_DIREC_102,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_417, (U2)RIMID_U1_NVMC_ST_DTF_417, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_103              */ {(U2)DTF_BID_DIREC_103,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_418, (U2)RIMID_U1_NVMC_ST_DTF_418, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_104              */ {(U2)DTF_BID_DIREC_104,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_419, (U2)RIMID_U1_NVMC_ST_DTF_419, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_105              */ {(U2)DTF_BID_DIREC_105,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_420, (U2)RIMID_U1_NVMC_ST_DTF_420, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_106              */ {(U2)DTF_BID_DIREC_106,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_421, (U2)RIMID_U1_NVMC_ST_DTF_421, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_107              */ {(U2)DTF_BID_DIREC_107,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_422, (U2)RIMID_U1_NVMC_ST_DTF_422, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_108              */ {(U2)DTF_BID_DIREC_108,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_423, (U2)RIMID_U1_NVMC_ST_DTF_423, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_109              */ {(U2)DTF_BID_DIREC_109,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_424, (U2)RIMID_U1_NVMC_ST_DTF_424, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_110              */ {(U2)DTF_BID_DIREC_110,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_425, (U2)RIMID_U1_NVMC_ST_DTF_425, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_111              */ {(U2)DTF_BID_DIREC_111,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_426, (U2)RIMID_U1_NVMC_ST_DTF_426, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_112              */ {(U2)DTF_BID_DIREC_112,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_427, (U2)RIMID_U1_NVMC_ST_DTF_427, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_113              */ {(U2)DTF_BID_DIREC_113,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_428, (U2)RIMID_U1_NVMC_ST_DTF_428, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_114              */ {(U2)DTF_BID_DIREC_114,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_429, (U2)RIMID_U1_NVMC_ST_DTF_429, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_115              */ {(U2)DTF_BID_DIREC_115,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_430, (U2)RIMID_U1_NVMC_ST_DTF_430, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_116              */ {(U2)DTF_BID_DIREC_116,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_431, (U2)RIMID_U1_NVMC_ST_DTF_431, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_117              */ {(U2)DTF_BID_DIREC_117,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_432, (U2)RIMID_U1_NVMC_ST_DTF_432, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_118              */ {(U2)DTF_BID_DIREC_118,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_433, (U2)RIMID_U1_NVMC_ST_DTF_433, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_119              */ {(U2)DTF_BID_DIREC_119,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_434, (U2)RIMID_U1_NVMC_ST_DTF_434, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_120              */ {(U2)DTF_BID_DIREC_120,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_435, (U2)RIMID_U1_NVMC_ST_DTF_435, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_121              */ {(U2)DTF_BID_DIREC_121,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_436, (U2)RIMID_U1_NVMC_ST_DTF_436, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_122              */ {(U2)DTF_BID_DIREC_122,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_437, (U2)RIMID_U1_NVMC_ST_DTF_437, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_123              */ {(U2)DTF_BID_DIREC_123,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_438, (U2)RIMID_U1_NVMC_ST_DTF_438, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_124              */ {(U2)DTF_BID_DIREC_124,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_439, (U2)RIMID_U1_NVMC_ST_DTF_439, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_125              */ {(U2)DTF_BID_DIREC_125,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_440, (U2)RIMID_U1_NVMC_ST_DTF_440, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_126              */ {(U2)DTF_BID_DIREC_126,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_441, (U2)RIMID_U1_NVMC_ST_DTF_441, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_127              */ {(U2)DTF_BID_DIREC_127,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_442, (U2)RIMID_U1_NVMC_ST_DTF_442, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_128              */ {(U2)DTF_BID_DIREC_128,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_443, (U2)RIMID_U1_NVMC_ST_DTF_443, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_129              */ {(U2)DTF_BID_DIREC_129,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_444, (U2)RIMID_U1_NVMC_ST_DTF_444, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_130              */ {(U2)DTF_BID_DIREC_130,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_445, (U2)RIMID_U1_NVMC_ST_DTF_445, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_131              */ {(U2)DTF_BID_DIREC_131,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_446, (U2)RIMID_U1_NVMC_ST_DTF_446, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_132              */ {(U2)DTF_BID_DIREC_132,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_447, (U2)RIMID_U1_NVMC_ST_DTF_447, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_133              */ {(U2)DTF_BID_DIREC_133,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_448, (U2)RIMID_U1_NVMC_ST_DTF_448, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* DIREC_134              */ {(U2)DTF_BID_DIREC_134,                (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_449, (U2)RIMID_U1_NVMC_ST_DTF_449, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* IVI_RESERVE_0          */ {(U2)DTF_BID_IVI_RESERVE_0_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_450,  (U2)RIMID_U1_NVMC_ST_DTF_450, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* IVI_RESERVE_1          */ {(U2)DTF_BID_IVI_RESERVE_1_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_451,  (U2)RIMID_U1_NVMC_ST_DTF_451, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* IVI_RESERVE_2          */ {(U2)DTF_BID_IVI_RESERVE_2_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_452,  (U2)RIMID_U1_NVMC_ST_DTF_452, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* IVI_RESERVE_3          */ {(U2)DTF_BID_IVI_RESERVE_3_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_453,  (U2)RIMID_U1_NVMC_ST_DTF_453, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* IVI_RESERVE_4          */ {(U2)DTF_BID_IVI_RESERVE_4_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_454,  (U2)RIMID_U1_NVMC_ST_DTF_454, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* IVI_RESERVE_5          */ {(U2)DTF_BID_IVI_RESERVE_5_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_455,  (U2)RIMID_U1_NVMC_ST_DTF_455, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* IVI_RESERVE_6          */ {(U2)DTF_BID_IVI_RESERVE_6_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_456,  (U2)RIMID_U1_NVMC_ST_DTF_456, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* IVI_RESERVE_7          */ {(U2)DTF_BID_IVI_RESERVE_7_0,          (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_457,  (U2)RIMID_U1_NVMC_ST_DTF_457, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* IVI_RESERVE_8          */ {(U2)DTF_BID_IVI_RESERVE_8_0,          (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_458, (U2)RIMID_U1_NVMC_ST_DTF_458, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* IVI_RESERVE_9          */ {(U2)DTF_BID_IVI_RESERVE_9_0,          (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_459, (U2)RIMID_U1_NVMC_ST_DTF_459, (U1)NVMC_MODULE_OTHDBL_24,          (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_ERR_COUNT        */ {(U2)DTF_BID_PWLOG_ERR_COUNT,          (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_460,  (U2)RIMID_U1_NVMC_ST_DTF_460, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BASIC_SEQ_00     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_00,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_461, (U2)RIMID_U1_NVMC_ST_DTF_461, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_01     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_01,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_462, (U2)RIMID_U1_NVMC_ST_DTF_462, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_02     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_02,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_463, (U2)RIMID_U1_NVMC_ST_DTF_463, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_03     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_03,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_464, (U2)RIMID_U1_NVMC_ST_DTF_464, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_04     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_04,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_465, (U2)RIMID_U1_NVMC_ST_DTF_465, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_05     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_05,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_466, (U2)RIMID_U1_NVMC_ST_DTF_466, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_06     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_06,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_467, (U2)RIMID_U1_NVMC_ST_DTF_467, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_07     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_07,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_468, (U2)RIMID_U1_NVMC_ST_DTF_468, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_08     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_08,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_469, (U2)RIMID_U1_NVMC_ST_DTF_469, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_09     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_09,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_470, (U2)RIMID_U1_NVMC_ST_DTF_470, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_10     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_10,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_471, (U2)RIMID_U1_NVMC_ST_DTF_471, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_11     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_11,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_472, (U2)RIMID_U1_NVMC_ST_DTF_472, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_12     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_12,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_473, (U2)RIMID_U1_NVMC_ST_DTF_473, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_13     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_13,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_474, (U2)RIMID_U1_NVMC_ST_DTF_474, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_14     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_14,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_475, (U2)RIMID_U1_NVMC_ST_DTF_475, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_15     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_15,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_476, (U2)RIMID_U1_NVMC_ST_DTF_476, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_16     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_16,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_477, (U2)RIMID_U1_NVMC_ST_DTF_477, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_17     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_17,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_478, (U2)RIMID_U1_NVMC_ST_DTF_478, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_18     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_18,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_479, (U2)RIMID_U1_NVMC_ST_DTF_479, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_19     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_19,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_480, (U2)RIMID_U1_NVMC_ST_DTF_480, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BASIC_SEQ_WP     */ {(U2)DTF_BID_PWLOG_BASIC_SEQ_WP,       (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_481,  (U2)RIMID_U1_NVMC_ST_DTF_481, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_OBS_SEQ_00_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_00_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_482, (U2)RIMID_U1_NVMC_ST_DTF_482, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_00_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_00_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_483, (U2)RIMID_U1_NVMC_ST_DTF_483, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_01_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_01_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_484, (U2)RIMID_U1_NVMC_ST_DTF_484, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_01_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_01_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_485, (U2)RIMID_U1_NVMC_ST_DTF_485, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_02_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_02_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_486, (U2)RIMID_U1_NVMC_ST_DTF_486, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_02_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_02_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_487, (U2)RIMID_U1_NVMC_ST_DTF_487, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_03_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_03_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_488, (U2)RIMID_U1_NVMC_ST_DTF_488, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_03_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_03_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_489, (U2)RIMID_U1_NVMC_ST_DTF_489, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_04_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_04_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_490, (U2)RIMID_U1_NVMC_ST_DTF_490, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_04_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_04_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_491, (U2)RIMID_U1_NVMC_ST_DTF_491, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_05_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_05_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_492, (U2)RIMID_U1_NVMC_ST_DTF_492, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_05_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_05_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_493, (U2)RIMID_U1_NVMC_ST_DTF_493, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_06_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_06_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_494, (U2)RIMID_U1_NVMC_ST_DTF_494, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_06_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_06_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_495, (U2)RIMID_U1_NVMC_ST_DTF_495, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_07_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_07_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_496, (U2)RIMID_U1_NVMC_ST_DTF_496, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_07_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_07_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_497, (U2)RIMID_U1_NVMC_ST_DTF_497, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_08_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_08_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_498, (U2)RIMID_U1_NVMC_ST_DTF_498, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_08_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_08_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_499, (U2)RIMID_U1_NVMC_ST_DTF_499, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_09_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_09_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_500, (U2)RIMID_U1_NVMC_ST_DTF_500, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_09_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_09_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_501, (U2)RIMID_U1_NVMC_ST_DTF_501, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_10_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_10_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_502, (U2)RIMID_U1_NVMC_ST_DTF_502, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_10_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_10_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_503, (U2)RIMID_U1_NVMC_ST_DTF_503, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_11_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_11_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_504, (U2)RIMID_U1_NVMC_ST_DTF_504, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_11_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_11_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_505, (U2)RIMID_U1_NVMC_ST_DTF_505, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_12_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_12_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_506, (U2)RIMID_U1_NVMC_ST_DTF_506, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_12_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_12_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_507, (U2)RIMID_U1_NVMC_ST_DTF_507, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_13_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_13_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_508, (U2)RIMID_U1_NVMC_ST_DTF_508, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_13_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_13_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_509, (U2)RIMID_U1_NVMC_ST_DTF_509, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_14_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_14_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_510, (U2)RIMID_U1_NVMC_ST_DTF_510, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_14_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_14_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_511, (U2)RIMID_U1_NVMC_ST_DTF_511, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_15_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_15_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_512, (U2)RIMID_U1_NVMC_ST_DTF_512, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_15_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_15_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_513, (U2)RIMID_U1_NVMC_ST_DTF_513, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_16_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_16_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_514, (U2)RIMID_U1_NVMC_ST_DTF_514, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_16_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_16_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_515, (U2)RIMID_U1_NVMC_ST_DTF_515, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_17_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_17_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_516, (U2)RIMID_U1_NVMC_ST_DTF_516, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_17_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_17_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_517, (U2)RIMID_U1_NVMC_ST_DTF_517, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_18_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_18_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_518, (U2)RIMID_U1_NVMC_ST_DTF_518, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_18_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_18_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_519, (U2)RIMID_U1_NVMC_ST_DTF_519, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_19_0     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_19_0,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_520, (U2)RIMID_U1_NVMC_ST_DTF_520, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_19_1     */ {(U2)DTF_BID_PWLOG_OBS_SEQ_19_1,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_521, (U2)RIMID_U1_NVMC_ST_DTF_521, (U1)NVMC_MODULE_OTHSNGL_16,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OBS_SEQ_WP       */ {(U2)DTF_BID_PWLOG_OBS_SEQ_WP,         (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_522,  (U2)RIMID_U1_NVMC_ST_DTF_522, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_OTA_SEQ_00       */ {(U2)DTF_BID_PWLOG_OTA_SEQ_00,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_523, (U2)RIMID_U1_NVMC_ST_DTF_523, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OTA_SEQ_01       */ {(U2)DTF_BID_PWLOG_OTA_SEQ_01,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_524, (U2)RIMID_U1_NVMC_ST_DTF_524, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OTA_SEQ_02       */ {(U2)DTF_BID_PWLOG_OTA_SEQ_02,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_525, (U2)RIMID_U1_NVMC_ST_DTF_525, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OTA_SEQ_03       */ {(U2)DTF_BID_PWLOG_OTA_SEQ_03,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_526, (U2)RIMID_U1_NVMC_ST_DTF_526, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OTA_SEQ_04       */ {(U2)DTF_BID_PWLOG_OTA_SEQ_04,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_527, (U2)RIMID_U1_NVMC_ST_DTF_527, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_OTA_SEQ_WP       */ {(U2)DTF_BID_PWLOG_OTA_SEQ_WP,         (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_528,  (U2)RIMID_U1_NVMC_ST_DTF_528, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_MCU_PMIC_00_0    */ {(U2)DTF_BID_PWLOG_MCU_PMIC_00_0,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_529, (U2)RIMID_U1_NVMC_ST_DTF_529, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_MCU_PMIC_00_1    */ {(U2)DTF_BID_PWLOG_MCU_PMIC_00_1,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_530, (U2)RIMID_U1_NVMC_ST_DTF_530, (U1)NVMC_MODULE_OTHSNGL_20,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_MCU_PMIC_01_0    */ {(U2)DTF_BID_PWLOG_MCU_PMIC_01_0,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_531, (U2)RIMID_U1_NVMC_ST_DTF_531, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_MCU_PMIC_01_1    */ {(U2)DTF_BID_PWLOG_MCU_PMIC_01_1,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_532, (U2)RIMID_U1_NVMC_ST_DTF_532, (U1)NVMC_MODULE_OTHSNGL_20,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_MCU_PMIC_02_0    */ {(U2)DTF_BID_PWLOG_MCU_PMIC_02_0,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_533, (U2)RIMID_U1_NVMC_ST_DTF_533, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_MCU_PMIC_02_1    */ {(U2)DTF_BID_PWLOG_MCU_PMIC_02_1,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_534, (U2)RIMID_U1_NVMC_ST_DTF_534, (U1)NVMC_MODULE_OTHSNGL_20,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_MCU_PMIC_03_0    */ {(U2)DTF_BID_PWLOG_MCU_PMIC_03_0,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_535, (U2)RIMID_U1_NVMC_ST_DTF_535, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_MCU_PMIC_03_1    */ {(U2)DTF_BID_PWLOG_MCU_PMIC_03_1,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_536, (U2)RIMID_U1_NVMC_ST_DTF_536, (U1)NVMC_MODULE_OTHSNGL_20,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_MCU_PMIC_04_0    */ {(U2)DTF_BID_PWLOG_MCU_PMIC_04_0,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_537, (U2)RIMID_U1_NVMC_ST_DTF_537, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_MCU_PMIC_04_1    */ {(U2)DTF_BID_PWLOG_MCU_PMIC_04_1,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_538, (U2)RIMID_U1_NVMC_ST_DTF_538, (U1)NVMC_MODULE_OTHSNGL_20,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_MCU_PMIC_WP      */ {(U2)DTF_BID_PWLOG_MCU_PMIC_WP,        (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_539,  (U2)RIMID_U1_NVMC_ST_DTF_539, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_SELFTEST_00      */ {(U2)DTF_BID_PWLOG_SELFTEST_00,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_540, (U2)RIMID_U1_NVMC_ST_DTF_540, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_01      */ {(U2)DTF_BID_PWLOG_SELFTEST_01,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_541, (U2)RIMID_U1_NVMC_ST_DTF_541, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_02      */ {(U2)DTF_BID_PWLOG_SELFTEST_02,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_542, (U2)RIMID_U1_NVMC_ST_DTF_542, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_03      */ {(U2)DTF_BID_PWLOG_SELFTEST_03,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_543, (U2)RIMID_U1_NVMC_ST_DTF_543, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_04      */ {(U2)DTF_BID_PWLOG_SELFTEST_04,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_544, (U2)RIMID_U1_NVMC_ST_DTF_544, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_05      */ {(U2)DTF_BID_PWLOG_SELFTEST_05,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_545, (U2)RIMID_U1_NVMC_ST_DTF_545, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_06      */ {(U2)DTF_BID_PWLOG_SELFTEST_06,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_546, (U2)RIMID_U1_NVMC_ST_DTF_546, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_07      */ {(U2)DTF_BID_PWLOG_SELFTEST_07,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_547, (U2)RIMID_U1_NVMC_ST_DTF_547, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_08      */ {(U2)DTF_BID_PWLOG_SELFTEST_08,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_548, (U2)RIMID_U1_NVMC_ST_DTF_548, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_09      */ {(U2)DTF_BID_PWLOG_SELFTEST_09,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_549, (U2)RIMID_U1_NVMC_ST_DTF_549, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_10      */ {(U2)DTF_BID_PWLOG_SELFTEST_10,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_550, (U2)RIMID_U1_NVMC_ST_DTF_550, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_11      */ {(U2)DTF_BID_PWLOG_SELFTEST_11,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_551, (U2)RIMID_U1_NVMC_ST_DTF_551, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_12      */ {(U2)DTF_BID_PWLOG_SELFTEST_12,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_552, (U2)RIMID_U1_NVMC_ST_DTF_552, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_13      */ {(U2)DTF_BID_PWLOG_SELFTEST_13,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_553, (U2)RIMID_U1_NVMC_ST_DTF_553, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_14      */ {(U2)DTF_BID_PWLOG_SELFTEST_14,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_554, (U2)RIMID_U1_NVMC_ST_DTF_554, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_15      */ {(U2)DTF_BID_PWLOG_SELFTEST_15,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_555, (U2)RIMID_U1_NVMC_ST_DTF_555, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_16      */ {(U2)DTF_BID_PWLOG_SELFTEST_16,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_556, (U2)RIMID_U1_NVMC_ST_DTF_556, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_17      */ {(U2)DTF_BID_PWLOG_SELFTEST_17,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_557, (U2)RIMID_U1_NVMC_ST_DTF_557, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_18      */ {(U2)DTF_BID_PWLOG_SELFTEST_18,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_558, (U2)RIMID_U1_NVMC_ST_DTF_558, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_19      */ {(U2)DTF_BID_PWLOG_SELFTEST_19,        (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_559, (U2)RIMID_U1_NVMC_ST_DTF_559, (U1)NVMC_MODULE_OTHSNGL_28,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_SELFTEST_WP      */ {(U2)DTF_BID_PWLOG_SELFTEST_WP,        (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_560,  (U2)RIMID_U1_NVMC_ST_DTF_560, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_00_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_00_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_561, (U2)RIMID_U1_NVMC_ST_DTF_561, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_00_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_00_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_562,  (U2)RIMID_U1_NVMC_ST_DTF_562, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_01_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_01_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_563, (U2)RIMID_U1_NVMC_ST_DTF_563, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_01_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_01_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_564,  (U2)RIMID_U1_NVMC_ST_DTF_564, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_02_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_02_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_565, (U2)RIMID_U1_NVMC_ST_DTF_565, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_02_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_02_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_566,  (U2)RIMID_U1_NVMC_ST_DTF_566, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_03_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_03_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_567, (U2)RIMID_U1_NVMC_ST_DTF_567, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_03_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_03_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_568,  (U2)RIMID_U1_NVMC_ST_DTF_568, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_04_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_04_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_569, (U2)RIMID_U1_NVMC_ST_DTF_569, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_04_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_04_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_570,  (U2)RIMID_U1_NVMC_ST_DTF_570, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_05_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_05_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_571, (U2)RIMID_U1_NVMC_ST_DTF_571, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_05_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_05_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_572,  (U2)RIMID_U1_NVMC_ST_DTF_572, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_06_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_06_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_573, (U2)RIMID_U1_NVMC_ST_DTF_573, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_06_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_06_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_574,  (U2)RIMID_U1_NVMC_ST_DTF_574, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_07_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_07_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_575, (U2)RIMID_U1_NVMC_ST_DTF_575, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_07_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_07_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_576,  (U2)RIMID_U1_NVMC_ST_DTF_576, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_08_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_08_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_577, (U2)RIMID_U1_NVMC_ST_DTF_577, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_08_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_08_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_578,  (U2)RIMID_U1_NVMC_ST_DTF_578, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_09_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_09_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_579, (U2)RIMID_U1_NVMC_ST_DTF_579, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_09_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_09_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_580,  (U2)RIMID_U1_NVMC_ST_DTF_580, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_10_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_10_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_581, (U2)RIMID_U1_NVMC_ST_DTF_581, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_10_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_10_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_582,  (U2)RIMID_U1_NVMC_ST_DTF_582, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_11_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_11_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_583, (U2)RIMID_U1_NVMC_ST_DTF_583, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_11_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_11_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_584,  (U2)RIMID_U1_NVMC_ST_DTF_584, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_12_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_12_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_585, (U2)RIMID_U1_NVMC_ST_DTF_585, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_12_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_12_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_586,  (U2)RIMID_U1_NVMC_ST_DTF_586, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_13_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_13_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_587, (U2)RIMID_U1_NVMC_ST_DTF_587, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_13_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_13_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_588,  (U2)RIMID_U1_NVMC_ST_DTF_588, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_14_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_14_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_589, (U2)RIMID_U1_NVMC_ST_DTF_589, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_14_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_14_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_590,  (U2)RIMID_U1_NVMC_ST_DTF_590, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_15_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_15_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_591, (U2)RIMID_U1_NVMC_ST_DTF_591, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_15_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_15_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_592,  (U2)RIMID_U1_NVMC_ST_DTF_592, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_16_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_16_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_593, (U2)RIMID_U1_NVMC_ST_DTF_593, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_16_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_16_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_594,  (U2)RIMID_U1_NVMC_ST_DTF_594, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_17_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_17_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_595, (U2)RIMID_U1_NVMC_ST_DTF_595, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_17_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_17_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_596,  (U2)RIMID_U1_NVMC_ST_DTF_596, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_18_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_18_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_597, (U2)RIMID_U1_NVMC_ST_DTF_597, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_18_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_18_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_598,  (U2)RIMID_U1_NVMC_ST_DTF_598, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_19_0   */ {(U2)DTF_BID_PWLOG_BIST_INIT_19_0,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_599, (U2)RIMID_U1_NVMC_ST_DTF_599, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_BIST_INIT_19_1   */ {(U2)DTF_BID_PWLOG_BIST_INIT_19_1,     (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_600,  (U2)RIMID_U1_NVMC_ST_DTF_600, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_BIST_INIT_WP     */ {(U2)DTF_BID_PWLOG_BIST_INIT_WP,       (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_601,  (U2)RIMID_U1_NVMC_ST_DTF_601, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWLOG_RESERVE_00       */ {(U2)DTF_BID_PWLOG_RESERVE_00,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_602, (U2)RIMID_U1_NVMC_ST_DTF_602, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_01       */ {(U2)DTF_BID_PWLOG_RESERVE_01,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_603, (U2)RIMID_U1_NVMC_ST_DTF_603, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_02       */ {(U2)DTF_BID_PWLOG_RESERVE_02,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_604, (U2)RIMID_U1_NVMC_ST_DTF_604, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_03       */ {(U2)DTF_BID_PWLOG_RESERVE_03,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_605, (U2)RIMID_U1_NVMC_ST_DTF_605, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_04       */ {(U2)DTF_BID_PWLOG_RESERVE_04,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_606, (U2)RIMID_U1_NVMC_ST_DTF_606, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_05       */ {(U2)DTF_BID_PWLOG_RESERVE_05,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_607, (U2)RIMID_U1_NVMC_ST_DTF_607, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_06       */ {(U2)DTF_BID_PWLOG_RESERVE_06,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_608, (U2)RIMID_U1_NVMC_ST_DTF_608, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_07       */ {(U2)DTF_BID_PWLOG_RESERVE_07,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_609, (U2)RIMID_U1_NVMC_ST_DTF_609, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_08       */ {(U2)DTF_BID_PWLOG_RESERVE_08,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_610, (U2)RIMID_U1_NVMC_ST_DTF_610, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_09       */ {(U2)DTF_BID_PWLOG_RESERVE_09,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_611, (U2)RIMID_U1_NVMC_ST_DTF_611, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_10       */ {(U2)DTF_BID_PWLOG_RESERVE_10,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_612, (U2)RIMID_U1_NVMC_ST_DTF_612, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_11       */ {(U2)DTF_BID_PWLOG_RESERVE_11,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_613, (U2)RIMID_U1_NVMC_ST_DTF_613, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_12       */ {(U2)DTF_BID_PWLOG_RESERVE_12,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_614, (U2)RIMID_U1_NVMC_ST_DTF_614, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_13       */ {(U2)DTF_BID_PWLOG_RESERVE_13,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_615, (U2)RIMID_U1_NVMC_ST_DTF_615, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_14       */ {(U2)DTF_BID_PWLOG_RESERVE_14,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_616, (U2)RIMID_U1_NVMC_ST_DTF_616, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_15       */ {(U2)DTF_BID_PWLOG_RESERVE_15,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_617, (U2)RIMID_U1_NVMC_ST_DTF_617, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_16       */ {(U2)DTF_BID_PWLOG_RESERVE_16,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_618, (U2)RIMID_U1_NVMC_ST_DTF_618, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_17       */ {(U2)DTF_BID_PWLOG_RESERVE_17,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_619, (U2)RIMID_U1_NVMC_ST_DTF_619, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_18       */ {(U2)DTF_BID_PWLOG_RESERVE_18,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_620, (U2)RIMID_U1_NVMC_ST_DTF_620, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_19       */ {(U2)DTF_BID_PWLOG_RESERVE_19,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_621, (U2)RIMID_U1_NVMC_ST_DTF_621, (U1)NVMC_MODULE_OTHSNGL_24,         (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* PWLOG_RESERVE_WP       */ {(U2)DTF_BID_PWLOG_RESERVE_WP,         (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_622,  (U2)RIMID_U1_NVMC_ST_DTF_622, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* PWCTRL_OTAACT_REQ      */ {(U2)DTF_BID_PWCTRL_OTAACT_REQ_0,      (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_623,  (U2)RIMID_U1_NVMC_ST_DTF_623, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* ETH_GLOBAL_MAC_ADDRESS */ {(U2)DTF_BID_ETH_GLOBAL_MAC_ADDRESS_0, (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_624, (U2)RIMID_U1_NVMC_ST_DTF_624, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_8,  (U1)0x01U,     (U1)0x01U,      (U1)0x40U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}} 
/* END : ##TOOL_OUT#NVMC_DTF_DATA_CFG_TBL## */
};

/* START : ##TOOL_OUT#NVMC_AREA_NUM## */
#define NVMC_AREA_NUM                            (0U)
/* END : ##TOOL_OUT#NVMC_AREA_NUM## */

/* START : ##TOOL_OUT#NVMC_DTF_BON_DUMMY_READ_NUM## */
#define NVMC_DTF_BON_DUMMY_READ_NUM              (5U)
/* END : ##TOOL_OUT#NVMC_DTF_BON_DUMMY_READ_NUM## */
/* START : ##TOOL_OUT#NVMC_DTF_WKUP_DUMMY_READ_NUM## */
#define NVMC_DTF_WKUP_DUMMY_READ_NUM             (5U)
/* END : ##TOOL_OUT#NVMC_DTF_WKUP_DUMMY_READ_NUM## */

const U1 u1_d_NVMC_DTF_DEVICE_TYPE    = (U1)NVMC_DEVICE_TYPE_DTF;
const U2 u2_d_NVMC_NUM_OF_NVRAMBLOCKS = (U2)NVM_NUM_OF_NVRAMBLOCKS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void vd_g_Nvmc_DTF_ErrorFactorHook(const U4 u4_a_ERRORFACTOR)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u4_a_ERRORFACTOR : Error Factor                                                                              */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_DTF_ErrorFactorHook(const U4 u4_a_ERRORFACTOR)
{
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_DTF_StateErrorHook(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_DTF_StateErrorHook(void)
{
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_MemAcc_JobEndHook(const U2 u2_a_AREAID, const U1 u1_a_JOBRESULT)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_AREAID    : Address Area Id                                                                             */
/*                      u1_a_JOBRESULT : Job Result                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_MemAcc_JobEndHook(const U2 u2_a_AREAID, const U1 u1_a_JOBRESULT)
{
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Static Functions                                                                                                                 */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0            8/26/2015  KM      New.                                                                                         */
/*  1.0.1            9/29/2015  KM      Updated.                                                                                     */
/*  1.1.0           10/16/2015  KS      Keywords for tool were inserted.                                                             */
/*  1.1.1           10/21/2015  MH      Fixed QAC issue.                                                                             */
/*  1.1.2           10/29/2015  KS      Keywords for tool were inserted.                                                             */
/*  1.1.3           11/02/2015  KS      Version updated.                                                                             */
/*  1.1.4           11/18/2015  KS      Version updated.                                                                             */
/*  1.1.5           12/10/2015  KM      Version updated.                                                                             */
/*  1.1.6            1/ 6/2016  KM      Version updated.                                                                             */
/*  1.1.7            1/ 8/2016  KM      Fixed u2_dp_NVMC_DTF_DUMMY_READ_TIMEOUT.                                                     */
/*                                      Supported debug simulatior.                                                                  */
/*  1.1.8            1/11/2016  KM      Fixed Keywords for tool.                                                                     */
/*  1.1.9            2/26/2016  KM      Fixed Version Check.                                                                         */
/*  1.1.10           4/ 4/2016  KM      Version updated.                                                                             */
/*  1.1.11           4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.1.12           4/12/2016  KM      Deleted unnecessary include.                                                                 */
/*  1.1.13           4/15/2016  KM      Fixed READ_BUFFER_SIZE                                                                       */
/*  1.1.14           6/ 1/2016  KM      Version updated.                                                                             */
/*  1.1.15          10/24/2016  HK      Changed that user can disable DTF configuration.                                             */
/*                                      Fixed DTF issue : Second argment of bswd_ms_NvM_ReadBlock changed NULL to BSWD_NULL          */
/*  1.2.0           10/28/2016  HK      Changed with the small sector correspondence.                                                */
/*                                      Fixed AIP3GBSW-12, 16 issue.                                                                 */
/*  1.3.0           03/31/2017  HK      Changed from 15BSW DTF to 19BSW DTF.                                                         */
/*  1.3.1           06/09/2017  HK      Add Common Read/Write Callback api of DTF Mirror config.                                     */
/*                                      Changed u1_g_Nvmc_DTF_Hook by DTFDriver update.                                              */
/*  1.3.2           07/05/2017  MH      Remove unnecessary "#include" file.                                                          */
/*  1.3.3           08/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.3.4           09/21/2017  HK      Fixed AIP3GBSW-167 issue.                                                                    */
/*  1.3.5           11/21/2017  HK      Fixed AIP3GBSW-203 issue.                                                                    */
/*                                      Fixed AIP3GBSW-204 issue.                                                                    */
/*  1.3.6           01/19/2018  HK      Fixed AIP3GBSW-241 issue.                                                                    */
/*  1.3.7           03/20/2018  HK      Fixed AIP3GBSW-266 issue.                                                                    */
/*  1.4.0           10/ 4/2021  TN      nvmc_dtf.c v1.3.7 -> v1.4.0.                                                                 */
/*  1.4.1           29/ 7/2022  ST      nvmc_dtf.c v1.4.0 -> v1.4.1.                                                                 */
/*  1.4.2           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * KS      = Kenichi Sakai,   Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, DENSO                                                                                                 */
/*  * ST      = Shohei Takada, DENSO                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
