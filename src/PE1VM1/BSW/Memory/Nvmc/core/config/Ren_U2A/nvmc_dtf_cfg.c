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
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)0U  ),  /* SAMPLE_U1             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)1U  ),  /* SAMPLE_U2             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)2U  ),  /* SAMPLE_U4             */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)3U  ),  /* SAMPLE_OTR32          */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)4U  ),  /* SAMPLE_OTR32CS        */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)5U  ),  /* BSW_SECOC_TRIP_CNT    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)6U  ),  /* OXDC_TMSTP            */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)7U  ),  /* OXDC_ROE_A005         */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)8U  ),  /* OXDC_DTC_EVENT001     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)9U  ),  /* OXDC_DTC_EVENT002     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)10U ),  /* OXDC_DTC_EVENT003     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)11U ),  /* OXDC_DTC_EVENT004     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)12U ),  /* OXDC_DTC_EVENT005     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)13U ),  /* OXDC_DTC_EVENT006     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)14U ),  /* OXDC_DTC_EVENT007     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)15U ),  /* OXDC_DTC_EVENT008     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)16U ),  /* OXDC_DTC_EVENT009     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)17U ),  /* OXDC_DTC_EVENT010     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)18U ),  /* OXDC_DTC_EVENT011     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)19U ),  /* OXDC_DTC_EVENT012     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)20U ),  /* OXDC_DTC_EVENT013     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)21U ),  /* OXDC_DTC_EVENT014     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)22U ),  /* OXDC_DTC_EVENT015     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)23U ),  /* OXDC_DTC_EVENT016     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)24U ),  /* OXDC_DTC_EVENT017     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)25U ),  /* OXDC_DTC_EVENT018     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)26U ),  /* OXDC_DTC_EVENT019     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)27U ),  /* OXDC_DTC_EVENT020     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)28U ),  /* OXDC_DTC_EVENT021     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)29U ),  /* OXDC_DTC_FAULT001     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)30U ),  /* OXDC_DTC_FAULT002     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)31U ),  /* OXDC_DTC_FAULT003     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)32U ),  /* OXDC_DTC_FAULT004     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)33U ),  /* OXDC_DTC_FAULT005     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)34U ),  /* OXDC_DTC_FAULT006     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)35U ),  /* OXDC_DTC_FAULT007     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)36U ),  /* OXDC_DTC_FAULT008     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)37U ),  /* OXDC_DTC_FAULT009     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)38U ),  /* OXDC_DTC_FAULT010     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)39U ),  /* OXDC_DTC_FAULT011     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)40U ),  /* OXDC_DTC_FAULT012     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)41U ),  /* OXDC_DTC_FAULT013     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)42U ),  /* OXDC_DTC_FAULT014     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)43U ),  /* OXDC_DTC_FAULT015     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)44U ),  /* OXDC_DTC_FAULT016     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)45U ),  /* OXDC_DTC_FAULT017     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)46U ),  /* OXDC_DTC_FAULT018     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)47U ),  /* OXDC_DTC_FAULT019     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)48U ),  /* OXDC_DTC_FAULT020     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)49U ),  /* OXDC_DTC_FAULT021     */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)50U ),  /* OXDC_DTC_FFD001       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)51U ),  /* OXDC_DTC_FFD002       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)52U ),  /* OXDC_DTC_FFD003       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)53U ),  /* OXDC_DTC_FFD004       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)54U ),  /* OXDC_DTC_FFD005       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)55U ),  /* OXDC_DTC_FFD006       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)56U ),  /* OXDC_DTC_FFD007       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)57U ),  /* OXDC_DTC_FFD008       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)58U ),  /* OXDC_DTC_FFD009       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)59U ),  /* OXDC_DTC_FFD010       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)60U ),  /* OXDC_DTC_FFD011       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)61U ),  /* OXDC_DTC_FFD012       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)62U ),  /* OXDC_DTC_FFD013       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)63U ),  /* OXDC_DTC_FFD014       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)64U ),  /* OXDC_DTC_FFD015       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)65U ),  /* OXDC_DTC_FFD016       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)66U ),  /* OXDC_DTC_FFD017       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)67U ),  /* OXDC_DTC_FFD018       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)68U ),  /* OXDC_DTC_FFD019       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)69U ),  /* OXDC_DTC_FFD020       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)70U ),  /* OXDC_DTC_FFD021       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)71U ),  /* OXDC_DTC_CLEARINFO    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)72U ),  /* OXDC_DTC_LOGRX1       */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)73U ),  /* OXDC_OCC2_NM_EVENT001 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)74U ),  /* OXDC_OCC2_NM_EVENT002 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)75U ),  /* OXDC_OCC2_NM_EVENT003 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)76U ),  /* OXDC_OCC2_NM_EVENT004 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)77U ),  /* OXDC_OCC3_NM_EVENT005 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)78U ),  /* OXDC_OCC7_NM_EVENT006 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)79U ),  /* OXDC_OCC2_NM_FAULT001 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)80U ),  /* OXDC_OCC2_NM_FAULT002 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)81U ),  /* OXDC_OCC2_NM_FAULT003 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)82U ),  /* OXDC_OCC2_NM_FAULT004 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)83U ),  /* OXDC_OCC3_NM_FAULT005 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)84U ),  /* OXDC_OCC7_NM_FAULT006 */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)85U ),  /* OXDC_OCC2_NM_FFD001   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)86U ),  /* OXDC_OCC2_NM_FFD002   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)87U ),  /* OXDC_OCC2_NM_FFD003   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)88U ),  /* OXDC_OCC2_NM_FFD004   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)89U ),  /* OXDC_OCC2_NM_FFD005   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)90U ),  /* OXDC_OCC2_NM_FFD006   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)91U ),  /* OXDC_OCC2_NM_FFD007   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)92U ),  /* OXDC_OCC2_NM_FFD008   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)93U ),  /* OXDC_OCC2_NM_FFD009   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)94U ),  /* OXDC_OCC2_NM_FFD010   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)95U ),  /* OXDC_OCC2_NM_FFD011   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)96U ),  /* OXDC_OCC2_NM_FFD012   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)97U ),  /* OXDC_OCC2_NM_FFD013   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)98U ),  /* OXDC_OCC2_NM_FFD014   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)99U ),  /* OXDC_OCC2_NM_FFD015   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)100U),  /* OXDC_OCC2_NM_FFD016   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)101U),  /* OXDC_OCC2_NM_FFD017   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)102U),  /* OXDC_OCC2_NM_FFD018   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)103U),  /* OXDC_OCC2_NM_FFD019   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)104U),  /* OXDC_OCC2_NM_FFD020   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)105U),  /* OXDC_OCC2_NM_FFD021   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)106U),  /* OXDC_OCC2_NM_FFD022   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)107U),  /* OXDC_OCC2_NM_FFD023   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)108U),  /* OXDC_OCC2_NM_FFD024   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)109U),  /* OXDC_OCC3_NM_FFD025   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)110U),  /* OXDC_OCC3_NM_FFD026   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)111U),  /* OXDC_OCC3_NM_FFD027   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)112U),  /* OXDC_OCC3_NM_FFD028   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)113U),  /* OXDC_OCC3_NM_FFD029   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)114U),  /* OXDC_OCC3_NM_FFD030   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)115U),  /* OXDC_OCC3_NM_FFD031   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)116U),  /* OXDC_OCC3_NM_FFD032   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)117U),  /* OXDC_OCC3_NM_FFD033   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)118U),  /* OXDC_OCC7_NM_FFD034   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)119U),  /* OXDC_OCC7_NM_FFD035   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)120U),  /* OXDC_OCC7_NM_FFD036   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)121U),  /* OXDC_OCC7_NM_FFD037   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)122U),  /* OXDC_OCC7_NM_FFD038   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)123U),  /* OXDC_OCC7_NM_FFD039   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)124U),  /* OXDC_OCC7_NM_FFD040   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)125U),  /* OXDC_OCC7_NM_FFD041   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)126U),  /* OXDC_OCC7_NM_FFD042   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)127U),  /* OXDC_OCC7_NM_FFD043   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)128U),  /* OXDC_OCC7_NM_FFD044   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)129U),  /* OXDC_OCC7_NM_FFD045   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)130U),  /* OXDC_OCC7_NM_FFD046   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)131U),  /* OXDC_OCC7_NM_FFD047   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)132U),  /* OXDC_OCC7_NM_FFD048   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)133U),  /* OXDC_OCC7_NM_FFD049   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)134U),  /* OXDC_OCC7_NM_FFD050   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)135U),  /* OXDC_OCC7_NM_FFD051   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)136U),  /* OXDC_OCC7_NM_FFD052   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)137U),  /* OXDC_OCC7_NM_FFD053   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)138U),  /* OXDC_OCC7_NM_FFD054   */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)139U),  /* OXDC_MAT1_EVENT001    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)140U),  /* OXDC_MAT1_EVENT002    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)141U),  /* OXDC_MAT1_FAULT001    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)142U),  /* OXDC_MAT1_FAULT002    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)143U),  /* OXDC_MAT1_FFD001      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)144U),  /* OXDC_MAT1_FFD002      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)145U),  /* OXDC_SOP2_EVENT001    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)146U),  /* OXDC_SOP2_EVENT002    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)147U),  /* OXDC_SOP2_FAULT001    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)148U),  /* OXDC_SOP2_FAULT002    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)149U),  /* OXDC_SOP2_FFD001      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)150U),  /* OXDC_SOP2_FFD002      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)151U),  /* OXDC_SOP2_FFD003      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)152U),  /* OXDC_SOP2_FFD004      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)153U),  /* OXDC_OCC1_EVENT007    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)154U),  /* OXDC_OCC1_EVENT008    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)155U),  /* OXDC_OCC1_EVENT009    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)156U),  /* OXDC_OCC1_EVENT010    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)157U),  /* OXDC_OCC1_EVENT011    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)158U),  /* OXDC_OCC1_EVENT012    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)159U),  /* OXDC_OCC1_EVENT013    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)160U),  /* OXDC_OCC1_EVENT014    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)161U),  /* OXDC_OCC1_EVENT015    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)162U),  /* OXDC_OCC1_EVENT016    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)163U),  /* OXDC_OCC1_EVENT017    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)164U),  /* OXDC_OCC1_EVENT018    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)165U),  /* OXDC_OCC1_EVENT019    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)166U),  /* OXDC_OCC1_EVENT020    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)167U),  /* OXDC_OCC1_EVENT021    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)168U),  /* OXDC_OCC1_EVENT022    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)169U),  /* OXDC_OCC1_EVENT023    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)170U),  /* OXDC_OCC1_EVENT024    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)171U),  /* OXDC_OCC1_EVENT025    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)172U),  /* OXDC_OCC2_EVENT026    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)173U),  /* OXDC_OCC1_FAULT007    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)174U),  /* OXDC_OCC1_FAULT008    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)175U),  /* OXDC_OCC1_FAULT009    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)176U),  /* OXDC_OCC1_FAULT010    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)177U),  /* OXDC_OCC1_FAULT011    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)178U),  /* OXDC_OCC1_FAULT012    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)179U),  /* OXDC_OCC1_FAULT013    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)180U),  /* OXDC_OCC1_FAULT014    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)181U),  /* OXDC_OCC1_FAULT015    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)182U),  /* OXDC_OCC1_FAULT016    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)183U),  /* OXDC_OCC1_FAULT017    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)184U),  /* OXDC_OCC1_FAULT018    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)185U),  /* OXDC_OCC1_FAULT019    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)186U),  /* OXDC_OCC1_FAULT020    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)187U),  /* OXDC_OCC1_FAULT021    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)188U),  /* OXDC_OCC1_FAULT022    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)189U),  /* OXDC_OCC1_FAULT023    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)190U),  /* OXDC_OCC1_FAULT024    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)191U),  /* OXDC_OCC1_FAULT025    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)192U),  /* OXDC_OCC2_FAULT026    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)193U),  /* OXDC_OCC1_FFD055      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)194U),  /* OXDC_OCC1_FFD056      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)195U),  /* OXDC_OCC1_FFD057      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)196U),  /* OXDC_OCC1_FFD058      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)197U),  /* OXDC_OCC1_FFD059      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)198U),  /* OXDC_OCC1_FFD060      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)199U),  /* OXDC_OCC1_FFD061      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)200U),  /* OXDC_OCC1_FFD062      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)201U),  /* OXDC_OCC1_FFD063      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)202U),  /* OXDC_OCC1_FFD064      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)203U),  /* OXDC_OCC1_FFD065      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)204U),  /* OXDC_OCC1_FFD066      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)205U),  /* OXDC_OCC1_FFD067      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)206U),  /* OXDC_OCC1_FFD068      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)207U),  /* OXDC_OCC1_FFD069      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)208U),  /* OXDC_OCC1_FFD070      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)209U),  /* OXDC_OCC1_FFD071      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)210U),  /* OXDC_OCC1_FFD072      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)211U),  /* OXDC_OCC1_FFD073      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)212U),  /* OXDC_OCC1_FFD074      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)213U),  /* OXDC_OCC1_FFD075      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)214U),  /* OXDC_OCC1_FFD076      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)215U),  /* OXDC_OCC1_FFD077      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)216U),  /* OXDC_OCC1_FFD078      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)217U),  /* OXDC_OCC1_FFD079      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)218U),  /* OXDC_OCC1_FFD080      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)219U),  /* OXDC_OCC1_FFD081      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)220U),  /* OXDC_OCC1_FFD082      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)221U),  /* OXDC_OCC1_FFD083      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)222U),  /* OXDC_OCC1_FFD084      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)223U),  /* OXDC_OCC1_FFD085      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)224U),  /* OXDC_OCC1_FFD086      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)225U),  /* OXDC_OCC1_FFD087      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)226U),  /* OXDC_OCC1_FFD088      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)227U),  /* OXDC_OCC1_FFD089      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)228U),  /* OXDC_OCC1_FFD090      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)229U),  /* OXDC_OCC1_FFD091      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)230U),  /* OXDC_OCC1_FFD092      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)231U),  /* OXDC_OCC1_FFD093      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)232U),  /* OXDC_OCC1_FFD094      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)233U),  /* OXDC_OCC1_FFD095      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)234U),  /* OXDC_OCC1_FFD096      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)235U),  /* OXDC_OCC1_FFD097      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)236U),  /* OXDC_OCC1_FFD098      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)237U),  /* OXDC_OCC1_FFD099      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)238U),  /* OXDC_OCC1_FFD100      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)239U),  /* OXDC_OCC1_FFD101      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)240U),  /* OXDC_OCC1_FFD102      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)241U),  /* OXDC_OCC1_FFD103      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)242U),  /* OXDC_OCC1_FFD104      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)243U),  /* OXDC_OCC1_FFD105      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)244U),  /* OXDC_OCC1_FFD106      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)245U),  /* OXDC_OCC1_FFD107      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)246U),  /* OXDC_OCC1_FFD108      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)247U),  /* OXDC_OCC1_FFD109      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)248U),  /* OXDC_OCC1_FFD110      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)249U),  /* OXDC_OCC1_FFD111      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)250U),  /* OXDC_OCC2_FFD112      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)251U),  /* OXDC_OCC2_FFD113      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)252U),  /* OXDC_OCC2_FFD114      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)253U),  /* OXDC_OCC2_FFD115      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)254U),  /* OXDC_OCC2_FFD116      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)255U),  /* OXDC_OCC2_FFD117      */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)256U),  /* OXDC_MAT1_EVENT003    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)257U),  /* OXDC_MAT1_FAULT003    */
    ((U2)NVMC_ACCSS_TYPE_INNVM | (U2)258U),  /* OXDC_MAT1_FFD003      */
    ((U2)NVMC_ACCSS_TYPE_INAPP | (U2)0U  )   /* Recovery              */
/* END : ##TOOL_OUT#NVMC_DTF_ID_CONV_TBL## */
};

const ST_NVMC_CFGDATA    st_dp_NVMC_DTF_DATA_CFG_TBL[NVMC_DTF_INNVM_NUM] = {
/* START : ##TOOL_OUT#NVMC_DTF_DATA_CFG_TBL## */
/*                            u2_addr                       u2_offset    u2_rimid_wdata                     u2_rimid_nvmsts               u1_map                              u1_rangeretry  u1_verifyretry  u1_mgr_bit_cfg  u4_module_bit_cfg   DEF              MIN              MAX           */ 
/* SAMPLE_U1             */ {(U2)BlockDescriptor_00002,    (U2)0x0001U, (U2)RIMID_U1_NVMC_DA_DTF_WRI_000,  (U2)RIMID_U1_NVMC_ST_DTF_000, (U1)NVMC_MODULE_U1_P1_TRPL,         (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01002004U,   {(U4)0x77U,       (U4)0x00U,       (U4)0xFFU      }},
/* SAMPLE_U2             */ {(U2)BlockDescriptor_00005,    (U2)0x0001U, (U2)RIMID_U2_NVMC_DA_DTF_WRI_001,  (U2)RIMID_U1_NVMC_ST_DTF_001, (U1)NVMC_MODULE_U2_LO_TRPL,         (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01002004U,   {(U4)0x7777U,     (U4)0x1111U,     (U4)0xEEEEU    }},
/* SAMPLE_U4             */ {(U2)BlockDescriptor_00008,    (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_002,  (U2)RIMID_U1_NVMC_ST_DTF_002, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01002004U,   {(U4)0x77777777U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* SAMPLE_OTR32          */ {(U2)BlockDescriptor_00011,    (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_003, (U2)RIMID_U1_NVMC_ST_DTF_003, (U1)NVMC_MODULE_OTHDBL_32,          (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01003534U,   {(U4)0x77777777U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* SAMPLE_OTR32CS        */ {(U2)BlockDescriptor_00013,    (U2)0x0001U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_004, (U2)RIMID_U1_NVMC_ST_DTF_004, (U1)NVMC_MODULE_OTHDBL_SUM_SMLL_28, (U1)0x01U,     (U1)0x00U,      (U1)0x21U,      (U4)0x01003534U,   {(U4)0x77777777U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* BSW_SECOC_TRIP_CNT    */ {(U2)DTF_BID_TRIP_CNT001,      (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_005,  (U2)RIMID_U1_NVMC_ST_DTF_005, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_TMSTP            */ {(U2)DTF_BID_TRIP_TMSTP,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_006, (U2)RIMID_U1_NVMC_ST_DTF_006, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_ROE_A005         */ {(U2)DTF_BID_ROE_A005,         (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_007, (U2)RIMID_U1_NVMC_ST_DTF_007, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT001     */ {(U2)DTF_BID_DTC_EVENT001,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_008, (U2)RIMID_U1_NVMC_ST_DTF_008, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT002     */ {(U2)DTF_BID_DTC_EVENT002,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_009, (U2)RIMID_U1_NVMC_ST_DTF_009, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT003     */ {(U2)DTF_BID_DTC_EVENT003,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_010, (U2)RIMID_U1_NVMC_ST_DTF_010, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT004     */ {(U2)DTF_BID_DTC_EVENT004,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_011, (U2)RIMID_U1_NVMC_ST_DTF_011, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT005     */ {(U2)DTF_BID_DTC_EVENT005,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_012, (U2)RIMID_U1_NVMC_ST_DTF_012, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT006     */ {(U2)DTF_BID_DTC_EVENT006,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_013, (U2)RIMID_U1_NVMC_ST_DTF_013, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT007     */ {(U2)DTF_BID_DTC_EVENT007,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_014, (U2)RIMID_U1_NVMC_ST_DTF_014, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT008     */ {(U2)DTF_BID_DTC_EVENT008,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_015, (U2)RIMID_U1_NVMC_ST_DTF_015, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT009     */ {(U2)DTF_BID_DTC_EVENT009,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_016, (U2)RIMID_U1_NVMC_ST_DTF_016, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT010     */ {(U2)DTF_BID_DTC_EVENT010,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_017, (U2)RIMID_U1_NVMC_ST_DTF_017, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT011     */ {(U2)DTF_BID_DTC_EVENT011,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_018, (U2)RIMID_U1_NVMC_ST_DTF_018, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT012     */ {(U2)DTF_BID_DTC_EVENT012,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_019, (U2)RIMID_U1_NVMC_ST_DTF_019, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT013     */ {(U2)DTF_BID_DTC_EVENT013,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_020, (U2)RIMID_U1_NVMC_ST_DTF_020, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT014     */ {(U2)DTF_BID_DTC_EVENT014,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_021, (U2)RIMID_U1_NVMC_ST_DTF_021, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT015     */ {(U2)DTF_BID_DTC_EVENT015,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_022, (U2)RIMID_U1_NVMC_ST_DTF_022, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT016     */ {(U2)DTF_BID_DTC_EVENT016,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_023, (U2)RIMID_U1_NVMC_ST_DTF_023, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT017     */ {(U2)DTF_BID_DTC_EVENT017,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_024, (U2)RIMID_U1_NVMC_ST_DTF_024, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT018     */ {(U2)DTF_BID_DTC_EVENT018,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_025, (U2)RIMID_U1_NVMC_ST_DTF_025, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT019     */ {(U2)DTF_BID_DTC_EVENT019,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_026, (U2)RIMID_U1_NVMC_ST_DTF_026, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT020     */ {(U2)DTF_BID_DTC_EVENT020,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_027, (U2)RIMID_U1_NVMC_ST_DTF_027, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_EVENT021     */ {(U2)DTF_BID_DTC_EVENT021,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_028, (U2)RIMID_U1_NVMC_ST_DTF_028, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT001     */ {(U2)DTF_BID_DTC_FAULT001,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_029, (U2)RIMID_U1_NVMC_ST_DTF_029, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT002     */ {(U2)DTF_BID_DTC_FAULT002,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_030, (U2)RIMID_U1_NVMC_ST_DTF_030, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT003     */ {(U2)DTF_BID_DTC_FAULT003,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_031, (U2)RIMID_U1_NVMC_ST_DTF_031, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT004     */ {(U2)DTF_BID_DTC_FAULT004,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_032, (U2)RIMID_U1_NVMC_ST_DTF_032, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT005     */ {(U2)DTF_BID_DTC_FAULT005,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_033, (U2)RIMID_U1_NVMC_ST_DTF_033, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT006     */ {(U2)DTF_BID_DTC_FAULT006,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_034, (U2)RIMID_U1_NVMC_ST_DTF_034, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT007     */ {(U2)DTF_BID_DTC_FAULT007,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_035, (U2)RIMID_U1_NVMC_ST_DTF_035, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT008     */ {(U2)DTF_BID_DTC_FAULT008,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_036, (U2)RIMID_U1_NVMC_ST_DTF_036, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT009     */ {(U2)DTF_BID_DTC_FAULT009,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_037, (U2)RIMID_U1_NVMC_ST_DTF_037, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT010     */ {(U2)DTF_BID_DTC_FAULT010,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_038, (U2)RIMID_U1_NVMC_ST_DTF_038, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT011     */ {(U2)DTF_BID_DTC_FAULT011,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_039, (U2)RIMID_U1_NVMC_ST_DTF_039, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT012     */ {(U2)DTF_BID_DTC_FAULT012,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_040, (U2)RIMID_U1_NVMC_ST_DTF_040, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT013     */ {(U2)DTF_BID_DTC_FAULT013,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_041, (U2)RIMID_U1_NVMC_ST_DTF_041, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT014     */ {(U2)DTF_BID_DTC_FAULT014,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_042, (U2)RIMID_U1_NVMC_ST_DTF_042, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT015     */ {(U2)DTF_BID_DTC_FAULT015,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_043, (U2)RIMID_U1_NVMC_ST_DTF_043, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT016     */ {(U2)DTF_BID_DTC_FAULT016,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_044, (U2)RIMID_U1_NVMC_ST_DTF_044, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT017     */ {(U2)DTF_BID_DTC_FAULT017,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_045, (U2)RIMID_U1_NVMC_ST_DTF_045, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT018     */ {(U2)DTF_BID_DTC_FAULT018,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_046, (U2)RIMID_U1_NVMC_ST_DTF_046, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT019     */ {(U2)DTF_BID_DTC_FAULT019,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_047, (U2)RIMID_U1_NVMC_ST_DTF_047, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT020     */ {(U2)DTF_BID_DTC_FAULT020,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_048, (U2)RIMID_U1_NVMC_ST_DTF_048, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FAULT021     */ {(U2)DTF_BID_DTC_FAULT021,     (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_049, (U2)RIMID_U1_NVMC_ST_DTF_049, (U1)NVMC_MODULE_OTHSNGL_12,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD001       */ {(U2)DTF_BID_DTC_FFD001,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_050, (U2)RIMID_U1_NVMC_ST_DTF_050, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD002       */ {(U2)DTF_BID_DTC_FFD002,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_051, (U2)RIMID_U1_NVMC_ST_DTF_051, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD003       */ {(U2)DTF_BID_DTC_FFD003,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_052, (U2)RIMID_U1_NVMC_ST_DTF_052, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD004       */ {(U2)DTF_BID_DTC_FFD004,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_053, (U2)RIMID_U1_NVMC_ST_DTF_053, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD005       */ {(U2)DTF_BID_DTC_FFD005,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_054, (U2)RIMID_U1_NVMC_ST_DTF_054, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD006       */ {(U2)DTF_BID_DTC_FFD006,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_055, (U2)RIMID_U1_NVMC_ST_DTF_055, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD007       */ {(U2)DTF_BID_DTC_FFD007,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_056, (U2)RIMID_U1_NVMC_ST_DTF_056, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD008       */ {(U2)DTF_BID_DTC_FFD008,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_057, (U2)RIMID_U1_NVMC_ST_DTF_057, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD009       */ {(U2)DTF_BID_DTC_FFD009,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_058, (U2)RIMID_U1_NVMC_ST_DTF_058, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD010       */ {(U2)DTF_BID_DTC_FFD010,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_059, (U2)RIMID_U1_NVMC_ST_DTF_059, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD011       */ {(U2)DTF_BID_DTC_FFD011,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_060, (U2)RIMID_U1_NVMC_ST_DTF_060, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD012       */ {(U2)DTF_BID_DTC_FFD012,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_061, (U2)RIMID_U1_NVMC_ST_DTF_061, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD013       */ {(U2)DTF_BID_DTC_FFD013,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_062, (U2)RIMID_U1_NVMC_ST_DTF_062, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD014       */ {(U2)DTF_BID_DTC_FFD014,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_063, (U2)RIMID_U1_NVMC_ST_DTF_063, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD015       */ {(U2)DTF_BID_DTC_FFD015,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_064, (U2)RIMID_U1_NVMC_ST_DTF_064, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD016       */ {(U2)DTF_BID_DTC_FFD016,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_065, (U2)RIMID_U1_NVMC_ST_DTF_065, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD017       */ {(U2)DTF_BID_DTC_FFD017,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_066, (U2)RIMID_U1_NVMC_ST_DTF_066, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD018       */ {(U2)DTF_BID_DTC_FFD018,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_067, (U2)RIMID_U1_NVMC_ST_DTF_067, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD019       */ {(U2)DTF_BID_DTC_FFD019,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_068, (U2)RIMID_U1_NVMC_ST_DTF_068, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD020       */ {(U2)DTF_BID_DTC_FFD020,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_069, (U2)RIMID_U1_NVMC_ST_DTF_069, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_FFD021       */ {(U2)DTF_BID_DTC_FFD021,       (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_070, (U2)RIMID_U1_NVMC_ST_DTF_070, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_CLEARINFO    */ {(U2)DTF_BID_DTC_CLEARINFO,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_071, (U2)RIMID_U1_NVMC_ST_DTF_071, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_DTC_LOGRX1       */ {(U2)DTF_BID_DTC_LOGRX1_1,     (U2)0x0001U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_072,  (U2)RIMID_U1_NVMC_ST_DTF_072, (U1)NVMC_MODULE_U4_TRPL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x00044044U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC2_NM_EVENT001 */ {(U2)DTF_BID_OCC2_NM_EVENT001, (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_073,  (U2)RIMID_U1_NVMC_ST_DTF_073, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC2_NM_EVENT002 */ {(U2)DTF_BID_OCC2_NM_EVENT002, (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_074,  (U2)RIMID_U1_NVMC_ST_DTF_074, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC2_NM_EVENT003 */ {(U2)DTF_BID_OCC2_NM_EVENT003, (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_075,  (U2)RIMID_U1_NVMC_ST_DTF_075, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC2_NM_EVENT004 */ {(U2)DTF_BID_OCC2_NM_EVENT004, (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_076,  (U2)RIMID_U1_NVMC_ST_DTF_076, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC3_NM_EVENT005 */ {(U2)DTF_BID_OCC3_NM_EVENT005, (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_077,  (U2)RIMID_U1_NVMC_ST_DTF_077, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC7_NM_EVENT006 */ {(U2)DTF_BID_OCC7_NM_EVENT006, (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_078,  (U2)RIMID_U1_NVMC_ST_DTF_078, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC2_NM_FAULT001 */ {(U2)DTF_BID_OCC2_NM_FAULT001, (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_079, (U2)RIMID_U1_NVMC_ST_DTF_079, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FAULT002 */ {(U2)DTF_BID_OCC2_NM_FAULT002, (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_080, (U2)RIMID_U1_NVMC_ST_DTF_080, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FAULT003 */ {(U2)DTF_BID_OCC2_NM_FAULT003, (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_081, (U2)RIMID_U1_NVMC_ST_DTF_081, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FAULT004 */ {(U2)DTF_BID_OCC2_NM_FAULT004, (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_082, (U2)RIMID_U1_NVMC_ST_DTF_082, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC3_NM_FAULT005 */ {(U2)DTF_BID_OCC3_NM_FAULT005, (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_083, (U2)RIMID_U1_NVMC_ST_DTF_083, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FAULT006 */ {(U2)DTF_BID_OCC7_NM_FAULT006, (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_084, (U2)RIMID_U1_NVMC_ST_DTF_084, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD001   */ {(U2)DTF_BID_OCC2_NM_FFD001,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_085, (U2)RIMID_U1_NVMC_ST_DTF_085, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD002   */ {(U2)DTF_BID_OCC2_NM_FFD002,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_086, (U2)RIMID_U1_NVMC_ST_DTF_086, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD003   */ {(U2)DTF_BID_OCC2_NM_FFD003,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_087, (U2)RIMID_U1_NVMC_ST_DTF_087, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD004   */ {(U2)DTF_BID_OCC2_NM_FFD004,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_088, (U2)RIMID_U1_NVMC_ST_DTF_088, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD005   */ {(U2)DTF_BID_OCC2_NM_FFD005,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_089, (U2)RIMID_U1_NVMC_ST_DTF_089, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD006   */ {(U2)DTF_BID_OCC2_NM_FFD006,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_090, (U2)RIMID_U1_NVMC_ST_DTF_090, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD007   */ {(U2)DTF_BID_OCC2_NM_FFD007,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_091, (U2)RIMID_U1_NVMC_ST_DTF_091, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD008   */ {(U2)DTF_BID_OCC2_NM_FFD008,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_092, (U2)RIMID_U1_NVMC_ST_DTF_092, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD009   */ {(U2)DTF_BID_OCC2_NM_FFD009,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_093, (U2)RIMID_U1_NVMC_ST_DTF_093, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD010   */ {(U2)DTF_BID_OCC2_NM_FFD010,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_094, (U2)RIMID_U1_NVMC_ST_DTF_094, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD011   */ {(U2)DTF_BID_OCC2_NM_FFD011,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_095, (U2)RIMID_U1_NVMC_ST_DTF_095, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD012   */ {(U2)DTF_BID_OCC2_NM_FFD012,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_096, (U2)RIMID_U1_NVMC_ST_DTF_096, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD013   */ {(U2)DTF_BID_OCC2_NM_FFD013,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_097, (U2)RIMID_U1_NVMC_ST_DTF_097, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD014   */ {(U2)DTF_BID_OCC2_NM_FFD014,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_098, (U2)RIMID_U1_NVMC_ST_DTF_098, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD015   */ {(U2)DTF_BID_OCC2_NM_FFD015,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_099, (U2)RIMID_U1_NVMC_ST_DTF_099, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD016   */ {(U2)DTF_BID_OCC2_NM_FFD016,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_100, (U2)RIMID_U1_NVMC_ST_DTF_100, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD017   */ {(U2)DTF_BID_OCC2_NM_FFD017,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_101, (U2)RIMID_U1_NVMC_ST_DTF_101, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD018   */ {(U2)DTF_BID_OCC2_NM_FFD018,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_102, (U2)RIMID_U1_NVMC_ST_DTF_102, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD019   */ {(U2)DTF_BID_OCC2_NM_FFD019,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_103, (U2)RIMID_U1_NVMC_ST_DTF_103, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD020   */ {(U2)DTF_BID_OCC2_NM_FFD020,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_104, (U2)RIMID_U1_NVMC_ST_DTF_104, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD021   */ {(U2)DTF_BID_OCC2_NM_FFD021,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_105, (U2)RIMID_U1_NVMC_ST_DTF_105, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD022   */ {(U2)DTF_BID_OCC2_NM_FFD022,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_106, (U2)RIMID_U1_NVMC_ST_DTF_106, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD023   */ {(U2)DTF_BID_OCC2_NM_FFD023,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_107, (U2)RIMID_U1_NVMC_ST_DTF_107, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_NM_FFD024   */ {(U2)DTF_BID_OCC2_NM_FFD024,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_108, (U2)RIMID_U1_NVMC_ST_DTF_108, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC3_NM_FFD025   */ {(U2)DTF_BID_OCC3_NM_FFD025,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_109, (U2)RIMID_U1_NVMC_ST_DTF_109, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC3_NM_FFD026   */ {(U2)DTF_BID_OCC3_NM_FFD026,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_110, (U2)RIMID_U1_NVMC_ST_DTF_110, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC3_NM_FFD027   */ {(U2)DTF_BID_OCC3_NM_FFD027,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_111, (U2)RIMID_U1_NVMC_ST_DTF_111, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC3_NM_FFD028   */ {(U2)DTF_BID_OCC3_NM_FFD028,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_112, (U2)RIMID_U1_NVMC_ST_DTF_112, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC3_NM_FFD029   */ {(U2)DTF_BID_OCC3_NM_FFD029,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_113, (U2)RIMID_U1_NVMC_ST_DTF_113, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC3_NM_FFD030   */ {(U2)DTF_BID_OCC3_NM_FFD030,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_114, (U2)RIMID_U1_NVMC_ST_DTF_114, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC3_NM_FFD031   */ {(U2)DTF_BID_OCC3_NM_FFD031,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_115, (U2)RIMID_U1_NVMC_ST_DTF_115, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC3_NM_FFD032   */ {(U2)DTF_BID_OCC3_NM_FFD032,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_116, (U2)RIMID_U1_NVMC_ST_DTF_116, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC3_NM_FFD033   */ {(U2)DTF_BID_OCC3_NM_FFD033,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_117, (U2)RIMID_U1_NVMC_ST_DTF_117, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD034   */ {(U2)DTF_BID_OCC7_NM_FFD034,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_118, (U2)RIMID_U1_NVMC_ST_DTF_118, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD035   */ {(U2)DTF_BID_OCC7_NM_FFD035,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_119, (U2)RIMID_U1_NVMC_ST_DTF_119, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD036   */ {(U2)DTF_BID_OCC7_NM_FFD036,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_120, (U2)RIMID_U1_NVMC_ST_DTF_120, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD037   */ {(U2)DTF_BID_OCC7_NM_FFD037,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_121, (U2)RIMID_U1_NVMC_ST_DTF_121, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD038   */ {(U2)DTF_BID_OCC7_NM_FFD038,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_122, (U2)RIMID_U1_NVMC_ST_DTF_122, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD039   */ {(U2)DTF_BID_OCC7_NM_FFD039,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_123, (U2)RIMID_U1_NVMC_ST_DTF_123, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD040   */ {(U2)DTF_BID_OCC7_NM_FFD040,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_124, (U2)RIMID_U1_NVMC_ST_DTF_124, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD041   */ {(U2)DTF_BID_OCC7_NM_FFD041,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_125, (U2)RIMID_U1_NVMC_ST_DTF_125, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD042   */ {(U2)DTF_BID_OCC7_NM_FFD042,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_126, (U2)RIMID_U1_NVMC_ST_DTF_126, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD043   */ {(U2)DTF_BID_OCC7_NM_FFD043,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_127, (U2)RIMID_U1_NVMC_ST_DTF_127, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD044   */ {(U2)DTF_BID_OCC7_NM_FFD044,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_128, (U2)RIMID_U1_NVMC_ST_DTF_128, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD045   */ {(U2)DTF_BID_OCC7_NM_FFD045,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_129, (U2)RIMID_U1_NVMC_ST_DTF_129, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD046   */ {(U2)DTF_BID_OCC7_NM_FFD046,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_130, (U2)RIMID_U1_NVMC_ST_DTF_130, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD047   */ {(U2)DTF_BID_OCC7_NM_FFD047,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_131, (U2)RIMID_U1_NVMC_ST_DTF_131, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD048   */ {(U2)DTF_BID_OCC7_NM_FFD048,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_132, (U2)RIMID_U1_NVMC_ST_DTF_132, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD049   */ {(U2)DTF_BID_OCC7_NM_FFD049,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_133, (U2)RIMID_U1_NVMC_ST_DTF_133, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD050   */ {(U2)DTF_BID_OCC7_NM_FFD050,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_134, (U2)RIMID_U1_NVMC_ST_DTF_134, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD051   */ {(U2)DTF_BID_OCC7_NM_FFD051,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_135, (U2)RIMID_U1_NVMC_ST_DTF_135, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD052   */ {(U2)DTF_BID_OCC7_NM_FFD052,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_136, (U2)RIMID_U1_NVMC_ST_DTF_136, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD053   */ {(U2)DTF_BID_OCC7_NM_FFD053,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_137, (U2)RIMID_U1_NVMC_ST_DTF_137, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC7_NM_FFD054   */ {(U2)DTF_BID_OCC7_NM_FFD054,   (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_138, (U2)RIMID_U1_NVMC_ST_DTF_138, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_MAT1_EVENT001    */ {(U2)DTF_BID_MAT1_EVENT001,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_139,  (U2)RIMID_U1_NVMC_ST_DTF_139, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_MAT1_EVENT002    */ {(U2)DTF_BID_MAT1_EVENT002,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_140,  (U2)RIMID_U1_NVMC_ST_DTF_140, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_MAT1_FAULT001    */ {(U2)DTF_BID_MAT1_FAULT001,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_141, (U2)RIMID_U1_NVMC_ST_DTF_141, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_MAT1_FAULT002    */ {(U2)DTF_BID_MAT1_FAULT002,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_142, (U2)RIMID_U1_NVMC_ST_DTF_142, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_MAT1_FFD001      */ {(U2)DTF_BID_MAT1_FFD001,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_143, (U2)RIMID_U1_NVMC_ST_DTF_143, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_MAT1_FFD002      */ {(U2)DTF_BID_MAT1_FFD002,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_144, (U2)RIMID_U1_NVMC_ST_DTF_144, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SOP2_EVENT001    */ {(U2)DTF_BID_SOP2_EVENT001,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_145,  (U2)RIMID_U1_NVMC_ST_DTF_145, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_SOP2_EVENT002    */ {(U2)DTF_BID_SOP2_EVENT002,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_146,  (U2)RIMID_U1_NVMC_ST_DTF_146, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_SOP2_FAULT001    */ {(U2)DTF_BID_SOP2_FAULT001,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_147, (U2)RIMID_U1_NVMC_ST_DTF_147, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SOP2_FAULT002    */ {(U2)DTF_BID_SOP2_FAULT002,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_148, (U2)RIMID_U1_NVMC_ST_DTF_148, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SOP2_FFD001      */ {(U2)DTF_BID_SOP2_FFD001,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_149, (U2)RIMID_U1_NVMC_ST_DTF_149, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SOP2_FFD002      */ {(U2)DTF_BID_SOP2_FFD002,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_150, (U2)RIMID_U1_NVMC_ST_DTF_150, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SOP2_FFD003      */ {(U2)DTF_BID_SOP2_FFD003,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_151, (U2)RIMID_U1_NVMC_ST_DTF_151, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_SOP2_FFD004      */ {(U2)DTF_BID_SOP2_FFD004,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_152, (U2)RIMID_U1_NVMC_ST_DTF_152, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_EVENT007    */ {(U2)DTF_BID_OCC1_EVENT007,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_153,  (U2)RIMID_U1_NVMC_ST_DTF_153, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT008    */ {(U2)DTF_BID_OCC1_EVENT008,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_154,  (U2)RIMID_U1_NVMC_ST_DTF_154, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT009    */ {(U2)DTF_BID_OCC1_EVENT009,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_155,  (U2)RIMID_U1_NVMC_ST_DTF_155, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT010    */ {(U2)DTF_BID_OCC1_EVENT010,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_156,  (U2)RIMID_U1_NVMC_ST_DTF_156, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT011    */ {(U2)DTF_BID_OCC1_EVENT011,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_157,  (U2)RIMID_U1_NVMC_ST_DTF_157, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT012    */ {(U2)DTF_BID_OCC1_EVENT012,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_158,  (U2)RIMID_U1_NVMC_ST_DTF_158, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT013    */ {(U2)DTF_BID_OCC1_EVENT013,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_159,  (U2)RIMID_U1_NVMC_ST_DTF_159, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT014    */ {(U2)DTF_BID_OCC1_EVENT014,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_160,  (U2)RIMID_U1_NVMC_ST_DTF_160, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT015    */ {(U2)DTF_BID_OCC1_EVENT015,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_161,  (U2)RIMID_U1_NVMC_ST_DTF_161, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT016    */ {(U2)DTF_BID_OCC1_EVENT016,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_162,  (U2)RIMID_U1_NVMC_ST_DTF_162, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT017    */ {(U2)DTF_BID_OCC1_EVENT017,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_163,  (U2)RIMID_U1_NVMC_ST_DTF_163, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT018    */ {(U2)DTF_BID_OCC1_EVENT018,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_164,  (U2)RIMID_U1_NVMC_ST_DTF_164, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT019    */ {(U2)DTF_BID_OCC1_EVENT019,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_165,  (U2)RIMID_U1_NVMC_ST_DTF_165, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT020    */ {(U2)DTF_BID_OCC1_EVENT020,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_166,  (U2)RIMID_U1_NVMC_ST_DTF_166, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT021    */ {(U2)DTF_BID_OCC1_EVENT021,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_167,  (U2)RIMID_U1_NVMC_ST_DTF_167, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT022    */ {(U2)DTF_BID_OCC1_EVENT022,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_168,  (U2)RIMID_U1_NVMC_ST_DTF_168, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT023    */ {(U2)DTF_BID_OCC1_EVENT023,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_169,  (U2)RIMID_U1_NVMC_ST_DTF_169, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT024    */ {(U2)DTF_BID_OCC1_EVENT024,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_170,  (U2)RIMID_U1_NVMC_ST_DTF_170, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_EVENT025    */ {(U2)DTF_BID_OCC1_EVENT025,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_171,  (U2)RIMID_U1_NVMC_ST_DTF_171, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC2_EVENT026    */ {(U2)DTF_BID_OCC2_EVENT026,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_172,  (U2)RIMID_U1_NVMC_ST_DTF_172, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_OCC1_FAULT007    */ {(U2)DTF_BID_OCC1_FAULT007,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_173, (U2)RIMID_U1_NVMC_ST_DTF_173, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT008    */ {(U2)DTF_BID_OCC1_FAULT008,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_174, (U2)RIMID_U1_NVMC_ST_DTF_174, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT009    */ {(U2)DTF_BID_OCC1_FAULT009,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_175, (U2)RIMID_U1_NVMC_ST_DTF_175, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT010    */ {(U2)DTF_BID_OCC1_FAULT010,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_176, (U2)RIMID_U1_NVMC_ST_DTF_176, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT011    */ {(U2)DTF_BID_OCC1_FAULT011,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_177, (U2)RIMID_U1_NVMC_ST_DTF_177, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT012    */ {(U2)DTF_BID_OCC1_FAULT012,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_178, (U2)RIMID_U1_NVMC_ST_DTF_178, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT013    */ {(U2)DTF_BID_OCC1_FAULT013,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_179, (U2)RIMID_U1_NVMC_ST_DTF_179, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT014    */ {(U2)DTF_BID_OCC1_FAULT014,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_180, (U2)RIMID_U1_NVMC_ST_DTF_180, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT015    */ {(U2)DTF_BID_OCC1_FAULT015,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_181, (U2)RIMID_U1_NVMC_ST_DTF_181, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT016    */ {(U2)DTF_BID_OCC1_FAULT016,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_182, (U2)RIMID_U1_NVMC_ST_DTF_182, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT017    */ {(U2)DTF_BID_OCC1_FAULT017,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_183, (U2)RIMID_U1_NVMC_ST_DTF_183, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT018    */ {(U2)DTF_BID_OCC1_FAULT018,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_184, (U2)RIMID_U1_NVMC_ST_DTF_184, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT019    */ {(U2)DTF_BID_OCC1_FAULT019,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_185, (U2)RIMID_U1_NVMC_ST_DTF_185, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT020    */ {(U2)DTF_BID_OCC1_FAULT020,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_186, (U2)RIMID_U1_NVMC_ST_DTF_186, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT021    */ {(U2)DTF_BID_OCC1_FAULT021,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_187, (U2)RIMID_U1_NVMC_ST_DTF_187, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT022    */ {(U2)DTF_BID_OCC1_FAULT022,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_188, (U2)RIMID_U1_NVMC_ST_DTF_188, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT023    */ {(U2)DTF_BID_OCC1_FAULT023,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_189, (U2)RIMID_U1_NVMC_ST_DTF_189, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT024    */ {(U2)DTF_BID_OCC1_FAULT024,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_190, (U2)RIMID_U1_NVMC_ST_DTF_190, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FAULT025    */ {(U2)DTF_BID_OCC1_FAULT025,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_191, (U2)RIMID_U1_NVMC_ST_DTF_191, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_FAULT026    */ {(U2)DTF_BID_OCC2_FAULT026,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_192, (U2)RIMID_U1_NVMC_ST_DTF_192, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD055      */ {(U2)DTF_BID_OCC1_FFD055,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_193, (U2)RIMID_U1_NVMC_ST_DTF_193, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD056      */ {(U2)DTF_BID_OCC1_FFD056,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_194, (U2)RIMID_U1_NVMC_ST_DTF_194, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD057      */ {(U2)DTF_BID_OCC1_FFD057,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_195, (U2)RIMID_U1_NVMC_ST_DTF_195, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD058      */ {(U2)DTF_BID_OCC1_FFD058,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_196, (U2)RIMID_U1_NVMC_ST_DTF_196, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD059      */ {(U2)DTF_BID_OCC1_FFD059,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_197, (U2)RIMID_U1_NVMC_ST_DTF_197, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD060      */ {(U2)DTF_BID_OCC1_FFD060,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_198, (U2)RIMID_U1_NVMC_ST_DTF_198, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD061      */ {(U2)DTF_BID_OCC1_FFD061,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_199, (U2)RIMID_U1_NVMC_ST_DTF_199, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD062      */ {(U2)DTF_BID_OCC1_FFD062,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_200, (U2)RIMID_U1_NVMC_ST_DTF_200, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD063      */ {(U2)DTF_BID_OCC1_FFD063,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_201, (U2)RIMID_U1_NVMC_ST_DTF_201, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD064      */ {(U2)DTF_BID_OCC1_FFD064,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_202, (U2)RIMID_U1_NVMC_ST_DTF_202, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD065      */ {(U2)DTF_BID_OCC1_FFD065,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_203, (U2)RIMID_U1_NVMC_ST_DTF_203, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD066      */ {(U2)DTF_BID_OCC1_FFD066,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_204, (U2)RIMID_U1_NVMC_ST_DTF_204, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD067      */ {(U2)DTF_BID_OCC1_FFD067,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_205, (U2)RIMID_U1_NVMC_ST_DTF_205, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD068      */ {(U2)DTF_BID_OCC1_FFD068,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_206, (U2)RIMID_U1_NVMC_ST_DTF_206, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD069      */ {(U2)DTF_BID_OCC1_FFD069,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_207, (U2)RIMID_U1_NVMC_ST_DTF_207, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD070      */ {(U2)DTF_BID_OCC1_FFD070,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_208, (U2)RIMID_U1_NVMC_ST_DTF_208, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD071      */ {(U2)DTF_BID_OCC1_FFD071,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_209, (U2)RIMID_U1_NVMC_ST_DTF_209, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD072      */ {(U2)DTF_BID_OCC1_FFD072,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_210, (U2)RIMID_U1_NVMC_ST_DTF_210, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD073      */ {(U2)DTF_BID_OCC1_FFD073,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_211, (U2)RIMID_U1_NVMC_ST_DTF_211, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD074      */ {(U2)DTF_BID_OCC1_FFD074,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_212, (U2)RIMID_U1_NVMC_ST_DTF_212, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD075      */ {(U2)DTF_BID_OCC1_FFD075,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_213, (U2)RIMID_U1_NVMC_ST_DTF_213, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD076      */ {(U2)DTF_BID_OCC1_FFD076,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_214, (U2)RIMID_U1_NVMC_ST_DTF_214, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD077      */ {(U2)DTF_BID_OCC1_FFD077,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_215, (U2)RIMID_U1_NVMC_ST_DTF_215, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD078      */ {(U2)DTF_BID_OCC1_FFD078,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_216, (U2)RIMID_U1_NVMC_ST_DTF_216, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD079      */ {(U2)DTF_BID_OCC1_FFD079,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_217, (U2)RIMID_U1_NVMC_ST_DTF_217, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD080      */ {(U2)DTF_BID_OCC1_FFD080,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_218, (U2)RIMID_U1_NVMC_ST_DTF_218, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD081      */ {(U2)DTF_BID_OCC1_FFD081,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_219, (U2)RIMID_U1_NVMC_ST_DTF_219, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD082      */ {(U2)DTF_BID_OCC1_FFD082,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_220, (U2)RIMID_U1_NVMC_ST_DTF_220, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD083      */ {(U2)DTF_BID_OCC1_FFD083,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_221, (U2)RIMID_U1_NVMC_ST_DTF_221, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD084      */ {(U2)DTF_BID_OCC1_FFD084,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_222, (U2)RIMID_U1_NVMC_ST_DTF_222, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD085      */ {(U2)DTF_BID_OCC1_FFD085,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_223, (U2)RIMID_U1_NVMC_ST_DTF_223, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD086      */ {(U2)DTF_BID_OCC1_FFD086,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_224, (U2)RIMID_U1_NVMC_ST_DTF_224, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD087      */ {(U2)DTF_BID_OCC1_FFD087,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_225, (U2)RIMID_U1_NVMC_ST_DTF_225, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD088      */ {(U2)DTF_BID_OCC1_FFD088,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_226, (U2)RIMID_U1_NVMC_ST_DTF_226, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD089      */ {(U2)DTF_BID_OCC1_FFD089,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_227, (U2)RIMID_U1_NVMC_ST_DTF_227, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD090      */ {(U2)DTF_BID_OCC1_FFD090,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_228, (U2)RIMID_U1_NVMC_ST_DTF_228, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD091      */ {(U2)DTF_BID_OCC1_FFD091,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_229, (U2)RIMID_U1_NVMC_ST_DTF_229, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD092      */ {(U2)DTF_BID_OCC1_FFD092,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_230, (U2)RIMID_U1_NVMC_ST_DTF_230, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD093      */ {(U2)DTF_BID_OCC1_FFD093,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_231, (U2)RIMID_U1_NVMC_ST_DTF_231, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD094      */ {(U2)DTF_BID_OCC1_FFD094,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_232, (U2)RIMID_U1_NVMC_ST_DTF_232, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD095      */ {(U2)DTF_BID_OCC1_FFD095,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_233, (U2)RIMID_U1_NVMC_ST_DTF_233, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD096      */ {(U2)DTF_BID_OCC1_FFD096,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_234, (U2)RIMID_U1_NVMC_ST_DTF_234, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD097      */ {(U2)DTF_BID_OCC1_FFD097,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_235, (U2)RIMID_U1_NVMC_ST_DTF_235, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD098      */ {(U2)DTF_BID_OCC1_FFD098,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_236, (U2)RIMID_U1_NVMC_ST_DTF_236, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD099      */ {(U2)DTF_BID_OCC1_FFD099,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_237, (U2)RIMID_U1_NVMC_ST_DTF_237, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD100      */ {(U2)DTF_BID_OCC1_FFD100,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_238, (U2)RIMID_U1_NVMC_ST_DTF_238, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD101      */ {(U2)DTF_BID_OCC1_FFD101,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_239, (U2)RIMID_U1_NVMC_ST_DTF_239, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD102      */ {(U2)DTF_BID_OCC1_FFD102,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_240, (U2)RIMID_U1_NVMC_ST_DTF_240, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD103      */ {(U2)DTF_BID_OCC1_FFD103,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_241, (U2)RIMID_U1_NVMC_ST_DTF_241, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD104      */ {(U2)DTF_BID_OCC1_FFD104,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_242, (U2)RIMID_U1_NVMC_ST_DTF_242, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD105      */ {(U2)DTF_BID_OCC1_FFD105,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_243, (U2)RIMID_U1_NVMC_ST_DTF_243, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD106      */ {(U2)DTF_BID_OCC1_FFD106,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_244, (U2)RIMID_U1_NVMC_ST_DTF_244, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD107      */ {(U2)DTF_BID_OCC1_FFD107,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_245, (U2)RIMID_U1_NVMC_ST_DTF_245, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD108      */ {(U2)DTF_BID_OCC1_FFD108,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_246, (U2)RIMID_U1_NVMC_ST_DTF_246, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD109      */ {(U2)DTF_BID_OCC1_FFD109,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_247, (U2)RIMID_U1_NVMC_ST_DTF_247, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD110      */ {(U2)DTF_BID_OCC1_FFD110,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_248, (U2)RIMID_U1_NVMC_ST_DTF_248, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC1_FFD111      */ {(U2)DTF_BID_OCC1_FFD111,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_249, (U2)RIMID_U1_NVMC_ST_DTF_249, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_FFD112      */ {(U2)DTF_BID_OCC2_FFD112,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_250, (U2)RIMID_U1_NVMC_ST_DTF_250, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_FFD113      */ {(U2)DTF_BID_OCC2_FFD113,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_251, (U2)RIMID_U1_NVMC_ST_DTF_251, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_FFD114      */ {(U2)DTF_BID_OCC2_FFD114,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_252, (U2)RIMID_U1_NVMC_ST_DTF_252, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_FFD115      */ {(U2)DTF_BID_OCC2_FFD115,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_253, (U2)RIMID_U1_NVMC_ST_DTF_253, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_FFD116      */ {(U2)DTF_BID_OCC2_FFD116,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_254, (U2)RIMID_U1_NVMC_ST_DTF_254, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_OCC2_FFD117      */ {(U2)DTF_BID_OCC2_FFD117,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_255, (U2)RIMID_U1_NVMC_ST_DTF_255, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_MAT1_EVENT003    */ {(U2)DTF_BID_MAT1_EVENT003,    (U2)0x0000U, (U2)RIMID_U4_NVMC_DA_DTF_WRI_256,  (U2)RIMID_U1_NVMC_ST_DTF_256, (U1)NVMC_MODULE_U4_SNGL,            (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0xFFFFFFFFU}},
/* OXDC_MAT1_FAULT003    */ {(U2)DTF_BID_MAT1_FAULT003,    (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_257, (U2)RIMID_U1_NVMC_ST_DTF_257, (U1)NVMC_MODULE_OTHSNGL_8,          (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}},
/* OXDC_MAT1_FFD003      */ {(U2)DTF_BID_MAT1_FFD003,      (U2)0x0000U, (U2)RIMID_OTR_NVMC_DA_DTF_WRI_258, (U2)RIMID_U1_NVMC_ST_DTF_258, (U1)NVMC_MODULE_OTHSNGL_32,         (U1)0x01U,     (U1)0x01U,      (U1)0x20U,      (U4)0x01000000U,   {(U4)0x00000000U, (U4)0x00000000U, (U4)0x00000000U}} 
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
