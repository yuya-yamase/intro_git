/* ADCDIAG-r04-303 */
/***************************************************************************************************/
/*                                                                                                 */
/*      ADC DIAG Driver : Low Driver layer for RH850U2A/U2B                                        */
/*                                                                                                 */
/*      Copyright : DENSO CORPORATION                                                              */
/*                                                                                                 */
/***************************************************************************************************/
/*=================================================================================================*/
/* include files                                                                                   */
/*=================================================================================================*/
#include    "Std_Types.h"
#include    "Mcal_SpalCmn.h"
#include    "McalCommon_lib.h"

#include    "AdcDiag_Pil.h"
#include    "Reg_Adc.h"
#include    "Reg_Stbc.h"
#include    "Reg_Reset.h"
/*=================================================================================================*/
/* prototypes                                                                                      */
/*=================================================================================================*/
extern void __SYNCP(void);
/*=================================================================================================*/
/* defines / data types / structs / unions  / macros                                               */
/*=================================================================================================*/
#define     Bswlib_Sync_Pipeline_4( data )                                                         \
    do                                                                                             \
    {                                                                                              \
        volatile    uint32  t_u4BswLibDummy;                                                       \
        t_u4BswLibDummy = (data);                                                                  \
        __SYNCP();                                                                                 \
    }   while(0)

#define     Bswlib_Sync_Pipeline_2( data )                                                         \
    do                                                                                             \
    {                                                                                              \
        volatile    uint16  t_u2BswLibDummy;                                                       \
        t_u2BswLibDummy = (data);                                                                  \
        __SYNCP();                                                                                 \
    }   while(0)

#define     Bswlib_Sync_Pipeline_1( data )                                                         \
    do                                                                                             \
    {                                                                                              \
        volatile    uint16  t_u1BswLibDummy;                                                       \
        t_u1BswLibDummy = (data);                                                                  \
        __SYNCP();                                                                                 \
    }   while(0)

#define ADCDIAG_PIL_ADVAL_AAA_VALUE                             (0U)
#define ADCDIAG_PIL_ADVAL_555_VALUE                             (1U)

#define u1ADCDIAG_PIL_SCAN_COUNT       		     ((uint8)0U)

#define u1ADCADIAG_PIL_TDCR_DEFAULT_VALUE		 (uint8)( (uint8)( ADC_TDCR_THSDE_ENABLE * ADC_TDCR_THSDE) \
                                                        + (uint8)( ADC_TDCR_TDLV_LEVEL0   * ADC_TDCR_TDLV_0 ) )

#define u1ADCADIAG_PIL_TOCCR_DEFAULT_VALUE        (uint8)( ADC_TOCCR_TOCE_DISABLE * ADC_TOCCR_TOCE )
#define u1ADCADIAG_PIL_TOCCR_TRG_OVERLAP_EN		  (uint8)( ADC_TOCCR_TOCE_ENABLE * ADC_TOCCR_TOCE )

#define u1ADCADIAG_PIL_THCR_DEFAULT_VALUE         (uint8)( ADC_THCR_ASMPMSK_AUTO * ADC_THCR_ASMPMSK )

#define u4ADCADIAG_PIL_FIRST_VCR_ADVAL		      (uint32)( (uint32)( ADC_VCR_CNVCLS_DATAPATH_DIAG * ADC_VCR_CNVCLS_0 ) \
                                                          + (uint32)( ADCDIAG_PIL_ADVAL_AAA_VALUE  * ADC_VCR_GCTRL_0 ) )

#define u4ADCADIAG_PIL_SECOND_VCR_ADVAL           (uint32)( (uint32)( (uint32)ADC_VCR_CNVCLS_DATAPATH_DIAG * (uint32)ADC_VCR_CNVCLS_0 ) \
                                                           + (uint32)( (uint32)ADCDIAG_PIL_ADVAL_555_VALUE  * (uint32)ADC_VCR_GCTRL_0 ) )

#define u1ADCADIAG_PIL_ADCR1_SUSMTD_ASYNC 		  (uint8)( ADC_ADCR1_SUSMTD_ASYNC * ADC_ADCR1_SUSMTD_0 )
#define u1ADCADIAG_PIL_THCR_AUTO_SMP_MSK		  (uint8)( ADC_THCR_ASMPMSK_AUTO * ADC_THCR_ASMPMSK)

#if ( MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B )
#define u2ADCADIAG_PIL_THGSR_GROUP_A_SEL		  (uint16)( (uint16)( (uint16)ADC_THGSR_TH5GS_SELECTED_A * (uint16)ADC_THGSR_TH5GS )  \
														  + (uint16)( (uint16)ADC_THGSR_TH4GS_SELECTED_A * (uint16)ADC_THGSR_TH4GS )  \
														  + (uint16)( (uint16)ADC_THGSR_TH3GS_SELECTED_A * (uint16)ADC_THGSR_TH3GS )  \
                                                          + (uint16)( (uint16)ADC_THGSR_TH2GS_SELECTED_A * (uint16)ADC_THGSR_TH2GS )  \
                                                          + (uint16)( (uint16)ADC_THGSR_TH1GS_SELECTED_A * (uint16)ADC_THGSR_TH1GS )  \
                                                          + (uint16)( (uint16)ADC_THGSR_TH0GS_SELECTED_A * (uint16)ADC_THGSR_TH0GS ) )
#endif /* ( MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B ) - */

#define u1ADCADIAG_PIL_THSMPSTCR_START_SMP		  (uint8)( ADC_THSMPSTCR_SMPST * ADC_THSMPSTCR_SMPST_START )
#define u1ADCADIAG_PIL_THAHLDSTCR_START_HOLD      (uint8)( ADC_THAHLDSTCR_HLDST * ADC_THAHLDSTCR_HLDST_START )
#define u1ADCADIAG_PIL_SGSTCR_START_SCAN     	  (uint8)( ADC_SGSTCR_SGST_SCAN_START & ADC_SGSTCR_SGST )
#define u1ADCADIAG_PIL_SGMCYCR_SCAN_COUNT     	  (uint8)( u1ADCDIAG_PIL_SCAN_COUNT * (uint8)ADC_SGMCYCR_MCYC_0 )

/* Enable Trigger Overlap Check Interrupt
 * Enable ID Error Interrupt
 * Enable Parity Error Interrupt */
#define u1ADCDIAG_PIL_SFTCR 					  (uint8)( (uint8)( ADC_SFTCR_TOCEIE_ENABLE   * ADC_SFTCR_TOCEIE )            \
														 + (uint8)( ADC_SFTCR_PEIE_ENABLE     * ADC_SFTCR_PEIE )              \
														 + (uint8)( ADC_SFTCR_IDEIE_ENABLE    * ADC_SFTCR_IDEIE ) )

#define u2ADCADIAG_PIL_ODCR_DEFAULT_VALUE		  (uint16)( (uint16)( ADC_ODCR_ODPW_STATE1 * ADC_ODCR_ODPW_0 ) \
														 + (uint16)( ADC_ODCR_WADDE_NORMAL * ADC_ODCR_WADDE ) )

#if ( MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A )
#define u2ADCADIAG_PIL_CLEAR_TRIG_OVERLAP_FLAG    (uint16)((uint16)ADC_ECR_TOCESGC * (uint16)ADC_ECR_TOCESGC_CLR)
#elif (MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)
#define u2ADCADIAG_PIL_CLEAR_TRIG_OVERLAP_FLAG    (uint16)( (uint16)((uint16)ADC_ECR_TOCESGC * (uint16)ADC_ECR_TOCESGC_CLR) \
                                                          + (uint16)((uint16)ADC_ECR_TOCESDC * (uint16)ADC_ECR_TOCESDC_CLR) )
#define u4ADCDIAG_PIL_U2B_RESET_VALUE_MASK				((uint32)(0xFFU))
#endif /* ( MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A ) - */

#define u1ADCDIAG_PIL_TH_VIRTUAL_CHANNELS_NOT_USED      ((uint8)(2U))

#define u1ADCADIAG_PIL_SGCR_TRGMD			            (uint8)( (uint8)( ADC_SGCR_ADSTARTE * ADC_SGCR_ADSTARTE_DISABLE ) \
                                                               + (uint8)( ADC_SGCR_TRGMD_SG0_2 * ADC_SGCR_TRGMD_HARD ) )
#if ( MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A )
#define u1ADCADIAG_PIL_VCR_GTMTAG_DEFAULT_VALUE	        ((uint8)(0U))
#define u1ADCADIAG_PIL_VCR_MPXV_DEFAULT_VALUE	        ((uint8)(0U))
#define u1ADCADIAG_PIL_SGVCPR_VCSP_DEFAULT_VALUE        ((uint8)(0U))
#define u1ADCADIAG_PIL_SGVCPR_VCEP_DEFAULT_VALUE        ((uint8)(0U))
#define u4ADCADIAG_PIL_ADTIP_DEFAULT_VALUE              ((uint32)(0x00000000U))
#define u4ADCADIAG_PIL_ADTPR_DEFAULT_VALUE              ((uint32)(0x001FFFFFU))
#define u1ADCADIAG_PIL_MPXCMD_INFO_DEFAULT_VALUE 		((uint8)(0U))
#define u1ADCADIAG_PIL_ADENDP_VCP_DEFAULT_VALUE 		((uint8)(0U))
#define u2ADCADIAG_PIL_WAITTR_WAIT_TIME_DEFAULT_VALUE 	((uint16)(0x0000U))
#define u1ADCDIAG_PIL_SGCR_TRGMD_SG3_4_0                ((uint8)(BIT0))
#define u4ADCDIAG_PIL_U2A_RESET_VALUE_MASK				((uint32)(0x3U))
#define u1ADCADIAG_PIL_SG_NUM_012						((uint8)(3U))
#define u4ADCDIAG_PIL_ADCJ2_RESET_VALUE_MASK			((uint32)(BIT2))

#define u4ADCADIAG_PIL_VCR_DEFAULT_VALUE    	      (uint32)( (uint32)((uint32)ADC_VCR_VCULLMTBS_0 * (uint32)ADC_VCR_VCULLMTBS_DISABLED) \
                                                          + (uint32)((uint32)ADC_VCR_WTTS_0 	 * (uint32)ADC_VCR_WTTS_DISABLED) \
                                                          + (uint32)((uint32)ADC_VCR_GTMENT 	 * (uint32)ADC_VCR_GTMENT_DISABLED) \
        												  + (uint32)((uint32)ADC_VCR_GTMTAG_0 	 * (uint32)u1ADCADIAG_PIL_VCR_GTMTAG_DEFAULT_VALUE) \
														  + (uint32)((uint32)ADC_VCR_CNVCLS_0 	 * (uint32)ADC_VCR_CNVCLS_NORMAL) \
														  + (uint32)((uint32)ADC_VCR_MPXV_0		 * (uint32)u1ADCADIAG_PIL_VCR_MPXV_DEFAULT_VALUE) \
														  + (uint32)((uint32)ADC_VCR_ADIE 		 * (uint32)ADC_VCR_ADIE_NOTOUTPUT) \
														  + (uint32)((uint32)ADC_VCR_GCTRL_0 	 * (uint32)ADC_VCR_GCTRL_AN000) )

#define u1ADCADIAG_PIL_SGCR0_2_DEFAULT_VALUE    	  (uint8)( (uint8)((uint8)ADC_SGCR_ADSTARTE  * (uint8)ADC_SGCR_ADSTARTE_DISABLE) \
                                                          + (uint8)((uint8)ADC_SGCR_SCANMD 		 * (uint8)ADC_SGCR_SCANMD_MULTI_CYCLE) \
        												  + (uint8)((uint8)ADC_SGCR_ADIE 		 * (uint8)ADC_SGCR_ADIE_DISABLE) \
														  + (uint8)((uint8)ADC_SGCR_TRGMD_SG0_2  * (uint8)ADC_SGCR_TRGMD_SOFT) )

#define u1ADCADIAG_PIL_SGCR3_4_DEFAULT_VALUE    	  (uint8)( (uint8)((uint8)ADC_SGCR_ADTSTARTE * (uint8)ADC_SGCR_ADTSTARTE_DISABLE) \
														  + (uint8)((uint8)ADC_SGCR_ADSTARTE 	 * (uint8)ADC_SGCR_ADSTARTE_DISABLE) \
                                                          + (uint8)((uint8)ADC_SGCR_SCANMD 		 * (uint8)ADC_SGCR_SCANMD_MULTI_CYCLE) \
        												  + (uint8)((uint8)ADC_SGCR_ADIE 		 * (uint8)ADC_SGCR_ADIE_DISABLE) \
														  + (uint8)((uint8)u1ADCDIAG_PIL_SGCR_TRGMD_SG3_4_0  * (uint8)ADC_SGCR_TRGMD_SOFT) )

#define u2ADCADIAG_PIL_SGVCPR_DEFAULT_VALUE			  (uint16) ( (uint16)( (uint16)u1ADCADIAG_PIL_SGVCPR_VCSP_DEFAULT_VALUE * (uint16)ADC_SGVCPR_VCSP_0 ) \
                                                          + (uint16)( (uint16)u1ADCADIAG_PIL_SGVCPR_VCEP_DEFAULT_VALUE      * (uint16)ADC_SGVCPR_VCEP_0 ) )

#define u1ADCADIAG_PIL_SGMCYCR_DEFAULT_VALUE     	  (uint8)( (uint8)u1ADCDIAG_PIL_SCAN_COUNT * (uint8)ADC_SGMCYCR_MCYC_0 )
#define u4ADCADIAG_PIL_ADTIPR_DEFAULT_VALUE     	  (uint32)( (uint32)u4ADCADIAG_PIL_ADTIP_DEFAULT_VALUE * (uint32)ADC_ADTIPR_ADTIP_0 )
#define u4ADCADIAG_PIL_ADTPRR_DEFAULT_VALUE     	  (uint32)( (uint32)u4ADCADIAG_PIL_ADTPR_DEFAULT_VALUE * (uint32)ADC_ADTPRR_ADTPR_0 )
#define u1ADCADIAG_PIL_PWDCR_DEFAULT_VALUE        	  (uint8)( (uint8)ADC_PWDCR_PWE_DISABLE * (uint8)ADC_PWDCR_PWE )
#define u1ADCADIAG_PIL_PWDSGCR_DEFAULT_VALUE          (uint8)( (uint8)ADC_PWDSGCR_TRGMD_SOFT * (uint8)ADC_PWDSGCR_TRGMD )

#define u4ADCADIAG_PIL_SGTSEL_DEFAULT_VALUE           (uint32)(( (uint32)ADC_SGTSELX_TXSEL_SOFT * (uint32)ADC_SGTSELX_TXSEL_0 ) \
														  + (uint32)((uint32)ADC_SGTSELX_TXSEL_SOFT * (uint32)ADC_SGTSELX_TXSEL_1 ) \
														  + (uint32)((uint32)ADC_SGTSELX_TXSEL_SOFT * (uint32)ADC_SGTSELX_TXSEL_2 ) \
														  + (uint32)((uint32)ADC_SGTSELX_TXSEL_SOFT * (uint32)ADC_SGTSELX_TXSEL_3 ) \
														  + (uint32)((uint32)ADC_SGTSELX_TXSEL_SOFT * (uint32)ADC_SGTSELX_TXSEL_4 ) \
														  + (uint32)((uint32)ADC_SGTSELX_TXSEL_SOFT * (uint32)ADC_SGTSELX_TXSEL_5 ) )


#define u1ADCADIAG_PIL_ADCR1_DEFAULT_VALUE            (uint8)( (uint8)ADC_ADCR1_SUSMTD_SYNC * (uint8)ADC_ADCR1_SUSMTD_0 )
#define u1ADCADIAG_PIL_ADCR2_DEFAULT_VALUE            (uint8)(( (uint8)ADC_ADCR2_DFMT_12BIT_FIXED_POINT * (uint8)ADC_ADCR2_DFMT_0 ) \
													      + (uint8)((uint8)ADC_ADCR2_ADDNT_2TIMES * (uint8)ADC_ADCR2_ADDNT ) )

#define u4ADCADIAG_PIL_SMPCR_DEFAULT_VALUE            (uint32)( (uint32)( (uint32)ADC_SMPCR_EXSMPT_60STATES * (uint32)ADC_SMPCR_EXSMPT_0 ) \
                                                          + (uint32)( (uint32)ADC_SMPCR_BUFAMPD_ENABLE  * (uint32)ADC_SMPCR_BUFAMPD ) \
                                                          + (uint32)( (uint32)ADC_SMPCR_SMPTS_DISABLE   * (uint32)ADC_SMPCR_SMPTS ) \
                                                          + (uint32)( (uint32)ADC_SMPCR_SMPT_18STATES   * (uint32)ADC_SMPCR_SMPT_0 ))

#define u1ADCADIAG_PIL_MPXCURCR_DEFAULT_VALUE         (uint8)( (uint8)ADC_MPXCURCR_MSKCFMT_MSKC0 * (uint8)ADC_MPXCURCR_MSKCFMT_0 )
#define u1ADCADIAG_PIL_MPXINTER_DEFAULT_VALUE         (uint8)( (uint8)ADC_MPXINTER_ADMPXIE_NOTOUTPUT * (uint8)ADC_MPXINTER_ADMPXIE )
#define u1ADCADIAG_PIL_MPXCMDR_DEFAULT_VALUE          (uint8)( (uint8)u1ADCADIAG_PIL_MPXCMD_INFO_DEFAULT_VALUE * (uint8)ADC_MPXCMDR_MPXCMD_0 )
#define u1ADCADIAG_PIL_ADENDP_DEFAULT_VALUE           (uint8)( (uint8)u1ADCADIAG_PIL_ADENDP_VCP_DEFAULT_VALUE * (uint8)ADC_ADENDP_ENDP_0 )

#define u2ADCADIAG_PIL_WAITTR_DEFAULT_VALUE           (uint16)( (uint16)u2ADCADIAG_PIL_WAITTR_WAIT_TIME_DEFAULT_VALUE * (uint16)ADC_WAITTR_WAITTIME_0 )

#define u1ADCADIAG_PIL_TDCR_U2A_DEFAULT_VALUE	      (uint8)( (uint8)( (uint8)ADC_TDCR_THSDE_DISABLE * (uint8)ADC_TDCR_THSDE) \
                                                        + (uint8)((uint8)ADC_TDCR_TDLV_LEVEL0   * (uint8)ADC_TDCR_TDLV_0 ) )

#define u1ADCDIAG_PIL_SFTCR_DEFAULT_VALUE 			  (uint8)( (uint8)( ADC_SFTCR_TOCEIE_DISABLE   * ADC_SFTCR_TOCEIE ) \
														 + (uint8)( ADC_SFTCR_PEIE_DISABLE     * ADC_SFTCR_PEIE ) \
														 + (uint8)( ADC_SFTCR_RDCLRE_DR_NOCLR     * ADC_SFTCR_RDCLRE ) \
														 + (uint8)( ADC_SFTCR_OWEIE_DISABLE     * ADC_SFTCR_OWEIE ) \
														 + (uint8)( ADC_SFTCR_IDEIE_DISABLE    * ADC_SFTCR_IDEIE ) )

#define u2ADCDIAG_PIL_ECR_DEFAULT_VALUE 			  (uint16)( (uint16)( ADC_ECR_TOCESGC_CLR   * ADC_ECR_TOCESGC_0 ) \
														 + (uint16)( ADC_ECR_TOCESGC_CLR   * ADC_ECR_TOCESGC_1 ) \
														 + (uint16)( ADC_ECR_TOCESGC_CLR   * ADC_ECR_TOCESGC_2 ) \
														 + (uint16)( ADC_ECR_TOCESGC_CLR   * ADC_ECR_TOCESGC_3 ) \
														 + (uint16)( ADC_ECR_TOCESGC_CLR   * ADC_ECR_TOCESGC_4 ) \
														 + (uint16)( ADC_ECR_OWEC_CLR      * ADC_ECR_OWEC ) \
														 + (uint16)( ADC_ECR_PEC_CLR       * ADC_ECR_PEC ) \
														 + (uint16)( ADC_ECR_IDEC_CLR      * ADC_ECR_IDEC ) )

#define u4ADCADIAG_PIL_VCULLMTBR_DEFAULT_VALUE        (uint32)(((uint32)ADC_VCULLMTBR_VCLLMTB_0 * (uint32)0U ) + (uint32)((uint32)ADC_VCULLMTBR_VCULMTB_0 * (uint32)0x7FFF))

#define u4ADCADIAG_PIL_VCLMINTER1_DEFAULT_VALUE       (uint32)(((uint32)ADC_VCLMINTER1_ADUL00IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL01IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL02IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL03IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL04IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL05IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL06IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL07IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL08IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL09IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL10IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL11IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL12IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL13IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL14IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL15IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL16IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL17IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL18IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL19IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL20IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL21IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL22IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL23IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL24IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL25IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL26IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL27IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL28IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL29IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL30IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \
														+(uint32)((uint32)ADC_VCLMINTER1_ADUL31IE * (uint32)ADC_VCLMINTER1_ADULIE_NOTOUTPUT))

#define u1ADCADIAG_PIL_PWVCLMINTER_DEFAULT_VALUE      (uint8)((uint8)ADC_PWVCLMINTER_PWADULIE_NOTOUTPUT * (uint8)ADC_PWVCLMINTER_PWADULIE )

#define u4ADCADIAG_PIL_VCLMSCR1_DEFAULT_VALUE           (uint32)(((uint32)ADC_VCLMSCR1_VC00LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
													 	+(uint32)((uint32)ADC_VCLMSCR1_VC01LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC02LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC03LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC04LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC05LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC06LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC07LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC08LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC09LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC10LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC11LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC12LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC13LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC14LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC15LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC16LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC17LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC18LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC19LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC20LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC21LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC22LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC23LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC24LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC25LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC26LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC27LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC28LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC29LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC30LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR1_VC31LMSC * (uint32)ADC_VCLMSCR1_VCLMSC_CLR))

#define u4ADCADIAG_PIL_VCLMSCR2_DEFAULT_VALUE           (uint32)(((uint32)ADC_VCLMSCR2_VC32LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
													 	+(uint32)((uint32)ADC_VCLMSCR2_VC33LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC34LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC35LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC36LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC37LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC38LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC39LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC40LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC41LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC42LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC43LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC44LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC45LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC46LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC47LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC48LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC49LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC50LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC51LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC52LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC53LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC54LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC55LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC56LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC57LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC58LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC59LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC60LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC61LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC62LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR) \
														+(uint32)((uint32)ADC_VCLMSCR2_VC63LMSC * (uint32)ADC_VCLMSCR2_VCLMSC_CLR))

#define u1ADCADIAG_PIL_PWVCLMSCR_DEFAULT_VALUE       (uint8)((uint8)ADC_PWVCLMSCR_PWVCLMSC * (uint8)ADC_PWVCLMSCR_PWVCLMSC_CLR )

#define u1ADCADIAG_PIL_SGULCCR_DEFAULT_VALUE         (uint8)(((uint8)ADC_SGULCCR_SGULCC_0 * (uint8)ADC_SGULCCR_SGULCC_CLR ) \
														+(uint8)((uint8)ADC_SGULCCR_SGULCC_1 * (uint8)ADC_SGULCCR_SGULCC_CLR ) \
														+(uint8)((uint8)ADC_SGULCCR_SGULCC_2 * (uint8)ADC_SGULCCR_SGULCC_CLR ) \
														+(uint8)((uint8)ADC_SGULCCR_SGULCC_3 * (uint8)ADC_SGULCCR_SGULCC_CLR ) \
														+(uint8)((uint8)ADC_SGULCCR_SGULCC_4 * (uint8)ADC_SGULCCR_SGULCC_CLR ))

#define u1ADCADIAG_PIL_VCLMASCR_DEFAULT_VALUE        (uint8)((uint8)ADC_VCLMASCR_ALLMSC * (uint8)ADC_VCLMASCR_ALLMSC_CLR )
#endif /* ( MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2A ) - */

/*==================================================================================================*/
/* prototype for local functions                                                                    */
/*==================================================================================================*/
#define ADCDIAG_START_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_ADCJ2ModuleReset                                          */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          : None                                                                  */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Software Module Reset Assertion Register for ADCj2                    */
/****************************************************************************************************/
static FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_ADCJ2ModuleReset( void );
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) - */

#define ADCDIAG_STOP_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"
/*==================================================================================================*/
/* constants                                                                                        */
/*==================================================================================================*/
#define ADCDIAG_START_SEC_CONST_UNSPECIFIED
#include "AdcDiag_MemMap.h"

#define ADCDIAG_STOP_SEC_CONST_UNSPECIFIED
#include "AdcDiag_MemMap.h"
/*==================================================================================================*/
/* variables                                                                                        */
/*==================================================================================================*/
#define ADCDIAG_START_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include "AdcDiag_MemMap.h"

#define ADCDIAG_STOP_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include "AdcDiag_MemMap.h"

/*----------------------------------------------------------------------------------------------*/
/* API Functions                                                                                */
/*----------------------------------------------------------------------------------------------*/
#define ADCDIAG_START_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"
/************************************************************************************************/
/* Service name         : AdcDiag_Pil_Init                                                      */
/* Sync/Async           : Synchronous                                                           */
/* Reentrancy           : Non Reentrant                                                         */
/* Parameters (in)      :                                                                       */
/*  t_u1IndexHWUnit     : HW Unit Number                                                        */
/* Parameters (inout)   : None                                                                  */
/* Parameters (out)     : None                                                                  */
/* Return value         : None                                                                  */
/* Description          : Enable error interrupts                                               */
/************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_Init(
    CONST(uint8, ADCDIAG_CONST)    t_u1IndexHWUnit
)
{
    /* Enable error interrupts */
    cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u1SFTCR  = u1ADCDIAG_PIL_SFTCR;

    /* Enable Trigger Overlap Check Function */
    cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u1TOCCR  = u1ADCADIAG_PIL_TOCCR_TRG_OVERLAP_EN;
}

/********************************************************************************************************/
/* Service name                 : AdcDiag_Pil_GetErrorData                                              */
/* Sync/Async                   : Synchronous                                                           */
/* Reentrancy                   : Non Reentrant                                                         */
/* Parameters (in)              :                                                                       */
/*  t_u1IndexHWUnit             : HW Unit Number                                                        */
/*  t_udAdcDiag_Pil_AdcErrorType: Adc Error Type                                                        */
/* Parameters (inout)           : None                                                                  */
/* Parameters (out)             : None                                                                  */
/* Return value                 :                                                                       */
/*  t_u1ErrorData               : Informations about the error                                          */
/* Description                  : Provide more informations about the error                             */
/********************************************************************************************************/
FUNC(uint8, ADCDIAG_CODE) AdcDiag_Pil_GetErrorData(
    CONST(uint8, ADCDIAG_CONST)    t_u1IndexHWUnit,
    CONST(AdcDiag_Pil_ErrorType, ADCDIAG_CONST)   t_udAdcDiag_Pil_AdcErrorType
)
{
    VAR(uint8,  ADCDIAG_VAR_NO_INIT)                t_u1ErrorData;
    VAR(uint8,  ADCDIAG_VAR_NO_INIT)                t_u1RegValue;
    t_u1ErrorData = u1ADCDIAG_PIL_NO_ERROR;

    switch (t_udAdcDiag_Pil_AdcErrorType)
    {
        case ADCDIAG_PIL_OVERLAPERROR:
        	t_u1RegValue = cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u1TOCER;
        	if ( t_u1RegValue != (uint8)0U )
        	{
        		t_u1ErrorData = t_u1RegValue;
        	}
            break;
        case ADCDIAG_PIL_PARITYPERROR:
        	t_u1RegValue = cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u1PER;
        	if ( ( t_u1RegValue & (uint8)ADC_PER_PE ) != (uint8)0U )
        	{
        		/* Only PECAP[6:0] are needed to establish the virtual channel that has an error */
        		t_u1ErrorData = (uint8)( t_u1RegValue & (uint8)ADC_PER_PECAP );
        	}
            break;
        case ADCDIAG_PIL_IDERROR:
        	t_u1RegValue = cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u1IDER;
        	if ( ( t_u1RegValue & (uint8)ADC_IDER_IDE ) != (uint8)0U )
        	{
        		/* Only IDECAP[6:0] are needed to establish the virtual channel that has an error */
        		t_u1ErrorData = (uint8)( t_u1RegValue &(uint8)ADC_IDER_IDECAP );
        	}
            break;
        default:
           /* Do nothing */
        break;
    }

    return ( t_u1ErrorData );
}

/********************************************************************************************************/
/* Service name                 : AdcDiag_Pil_ClearErrorFlag                                            */
/* Sync/Async                   : Synchronous                                                           */
/* Reentrancy                   : Non Reentrant                                                         */
/* Parameters (in)              :                                                                       */
/*  t_u1IndexHWUnit             : HW Unit Number                                                        */
/*  t_udAdcDiag_Pil_AdcErrorType: Adc Error Type                                                        */
/* Parameters (inout)           : None                                                                  */
/* Parameters (out)             : None                                                                  */
/* Return value                 : None                                                                  */
/* Description                  : Clear the error flags                                                 */
/********************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_ClearErrorFlag(
    CONST(uint8, ADCDIAG_CONST)    t_u1IndexHWUnit,
    CONST(AdcDiag_Pil_ErrorType, ADCDIAG_CONST)   t_udAdcDiag_Pil_AdcErrorType
)
{
    switch (t_udAdcDiag_Pil_AdcErrorType)
    {
        case ADCDIAG_PIL_OVERLAPERROR:
            /* Clear Trigger Overlap Check Error */
            cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u2ECR = u2ADCADIAG_PIL_CLEAR_TRIG_OVERLAP_FLAG;
            Bswlib_Sync_Pipeline_2(cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u2ECR);
            break;
        case ADCDIAG_PIL_PARITYPERROR:
            /* Clear Parity Error */
            cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u2ECR = (uint16)((uint16)ADC_ECR_PEC * (uint16)ADC_ECR_PEC_CLR);
            Bswlib_Sync_Pipeline_2(cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u2ECR);
            break;
        case ADCDIAG_PIL_IDERROR:
            /* Clear ID Error */
            cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u2ECR = (uint16)((uint16)ADC_ECR_IDEC * (uint16)ADC_ECR_IDEC_CLR);
            Bswlib_Sync_Pipeline_2(cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u2ECR);
            break;
        default:
            /* Do nothing */
            break;
    }
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_GetCnvData                                                */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1IndexHWUnit     : HW Unit Number                                                        */
/*      t_u1VirtualChannel  : Virtual Channel                                                       */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             :                                                                       */
/*      uint16              : Conversion result                                                     */
/* Description              : Reads the group conversion result                                     */
/****************************************************************************************************/
FUNC(uint16, ADCDIAG_CODE) AdcDiag_Pil_GetCnvData(
    CONST(uint8, ADCDIAG_CONST)    t_u1IndexHWUnit,
    CONST(uint8, ADCDIAG_CONST)   t_u1VirtualChannel
)
{
    return ( (uint16)(cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u2DR[t_u1VirtualChannel]) );
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_ClearDIR                                                  */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1IndexHWUnit     : HW Unit Number                                                        */
/*      t_u1VirtualChannel  : Virtual Channel                                                       */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Clear Data Supplementary Information Register                         */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_ClearDIR(
    CONST(uint8, ADCDIAG_CONST)   t_u1IndexHWUnit,
    CONST(uint8, ADCDIAG_CONST)   t_u1VirtualChannel
)
{
    volatile	VAR(uint32,	ADC_VAR_NO_INIT)	t_u4DIR;

    t_u4DIR = cpstReg_Adc[t_u1IndexHWUnit]->stMODULE.u4DIR[t_u1VirtualChannel];
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_GetClocksUsed                                             */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          : None                                                                  */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             :                                                                       */
/*      uint32              : ADC clocks status                                                     */
/* Description              : Provide the status of ADC clocks                                      */
/****************************************************************************************************/
FUNC(uint32, ADCDIAG_CODE) AdcDiag_Pil_GetClocksUsed(void)
{
    VAR(uint32, ADCDIAG_VAR_NO_INIT)    t_u4RegisterBackupValue;

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
    t_u4RegisterBackupValue = (uint32)REG_STBC_ISO.u4MSR_ADCK_ISO;
#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
    t_u4RegisterBackupValue = (uint32)REG_STBC_ISO.u4MSR_ADCJ_ISO;
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */

    return ( t_u4RegisterBackupValue );
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_EnableClocks                                              */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*  t_u4ClocksUsed          : Backup value for ADC clocks that were enabled before reset            */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Re-enable only the ADC clocks that were supplied before reset         */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_EnableClocks(
    CONST(uint32, ADCDIAG_CONST)   t_u4ClocksUsed
)
{
    REG_STBC_ISO.u4MSRKCPROT = MCU_STBC_PROTECT_ENABLE;  /* Enable writing to protected registers */
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
    /* Re-enable only the ADC clocks that were supplied before resetting the whole peripheral */
    REG_STBC_ISO.u4MSR_ADCK_ISO = t_u4ClocksUsed;
#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
    /* Re-enable only the ADC clocks that were supplied before resetting the whole peripheral */
    REG_STBC_ISO.u4MSR_ADCJ_ISO = t_u4ClocksUsed;
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */
    REG_STBC_ISO.u4MSRKCPROT = MCU_STBC_PROTECT_DISABLE; /* Disable writing to protected registers */
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_ConfigureSampling                                         */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1HWUnit          : Hw Unit Number                                                        */
/*      t_u1Amplifier       : Value of Buffer Amplifier (RRAMP)                                     */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Configure sampling. Configure Buffer Amplifier (RRAMP)                */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_ConfigureSampling(
    CONST(uint8,  ADCDIAG_CONST)    t_u1HWUnit,
    CONST(uint8,  ADCDIAG_CONST)    t_u1Amplifier
)
{
    /* Write a value after to be used by the diagnostic function */
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u4SMPCR = (uint32)( /* (uint32)( (uint32)ADC_SMPCR_EXSMPT_60STATES * (uint32)ADC_SMPCR_EXSMPT_0 ) - ADC_SMPCR_EXSMPT_60STATES is zero*/
                                                        + (uint32)( (uint32)t_u1Amplifier  * (uint32)ADC_SMPCR_BUFAMPD ) /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
                                                        + (uint32)( (uint32)ADC_SMPCR_SMPTS_ENABLE   * (uint32)ADC_SMPCR_SMPTS ) /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
                                                     /* + (uint32)( (uint32)ADC_SMPCR_SMPT_18STATES -value is 0   * (uint32)ADC_SMPCR_SMPT_0 ) - value is BIT0 */);
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_SetMultiCycle                                             */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1HWUnit          : HW Unit Number                                                        */
/*      t_u1ScanGroup       : Scan Group                                                            */
/*      t_u1MutiCycleValue  : Scan count value                                                      */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Set the scan count in multicycle mode                                 */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_SetMultiCycle(
    CONST(uint8,  ADCDIAG_CONST)    t_u1HWUnit,
    CONST(uint8,  ADCDIAG_CONST)    t_u1ScanGroup,
    CONST(uint8,  ADCDIAG_CONST)    t_u1MutiCycleValue
)
{
    /* Set the scan count in multicycle mode */
    cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u1SGMCYCR = (uint8)( (uint8)t_u1MutiCycleValue /* * (uint8)ADC_SGMCYCR_MCYC_0 - value is BIT0 */ );
}

/********************************************************************************************************/
/* Service name                 : AdcDiag_Pil_SetChannelConfig                                          */
/* Sync/Async                   : Synchronous                                                           */
/* Reentrancy                   : Non Reentrant                                                         */
/* Parameters (in)              :                                                                       */
/*  t_u1HWUnit                  : HW Unit Number                                                        */
/*  t_pu1PhysicalChannels(Sync) : Pointer to list of physical channels                                  */
/*  t_u1PsysicalChannelIndex    : Index for list of physical channels                                   */
/*  t_u1VirtualChannel          : Virtual Channel                                                       */
/*  t_u1SelfDiagMode            : Diagnostic mode                                                       */
/* Parameters (inout)           : None                                                                  */
/* Parameters (out)             : None                                                                  */
/* Return value                 : None                                                                  */
/* Description                  : Configure VCR register for all diagnostic modes                       */
/********************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_SetChannelConfig(
    CONST(uint8,   ADCDIAG_CONST)        t_u1HWUnit,
    P2CONST(uint8,AUTOMATIC, ADCDIAG_CONST)    t_pu1PhysicalChannels,
    CONST(uint8,   ADCDIAG_CONST)        t_u1PsysicalChannelIndex,
    CONST(uint8,   ADCDIAG_CONST)        t_u1VirtualChannel,
    CONST(uint8,   ADCDIAG_CONST)        t_u1SelfDiagMode
)
{
    switch ( t_u1SelfDiagMode )
    {
        case u1ADCDIAG_PIL_SELF_WIRING_BREAK_DETECTION_MODE1:
            /* Only one physical channel is required for this diagnostic type */
            cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCR[t_u1VirtualChannel] = (uint32) ( (uint32)( (uint32)ADC_VCR_CNVCLS_BREAK1_DIAG * (uint32)ADC_VCR_CNVCLS_0 ) /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
                                                                                   + (uint32)( (uint32)t_pu1PhysicalChannels[t_u1PsysicalChannelIndex] /* * (uint32)ADC_VCR_GCTRL_0  - value is BIT0 */ ) ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
            break;
        case u1ADCDIAG_PIL_SELF_WIRING_BREAK_DETECTION_MODE2:
            /* Two physical channels are required for this diagnostic type,
             * according to UM first one need to have pull-down enabled, the second one pull-up */
            cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCR[t_u1VirtualChannel] = (uint32)( (uint32)( (uint32)ADC_VCR_CNVCLS_BREAK2_DOWN_DIAG * (uint32)ADC_VCR_CNVCLS_0 )	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
                                                                                  + (uint32)( (uint32)t_pu1PhysicalChannels[t_u1PsysicalChannelIndex] /* * (uint32)ADC_VCR_GCTRL_0  - value is BIT0 */ ) ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */

            /* Both virtual channels need to have same input */
            cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCR[t_u1VirtualChannel + (uint8)1U] = (uint32)( (uint32)( (uint32)ADC_VCR_CNVCLS_BREAK2_UP_DIAG * (uint32)ADC_VCR_CNVCLS_0 )
                                                                                       + (uint32)( (uint32)t_pu1PhysicalChannels[t_u1PsysicalChannelIndex] /* * (uint32)ADC_VCR_GCTRL_0  - value is BIT0 */ ) ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
            break;
        case u1ADCDIAG_PIL_WIRING_BREAK_DETECTION_MODE1:
            cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCR[t_u1VirtualChannel] = (uint32)( (uint32)( ADC_VCR_CNVCLS_BREAK1 * ADC_VCR_CNVCLS_0 )
                                                                                  + (uint32)( (uint32)t_pu1PhysicalChannels[t_u1PsysicalChannelIndex]  /* * (uint32)ADC_VCR_GCTRL_0  - value is BIT0 */ ) ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
            break;
        case u1ADCDIAG_PIL_WIRING_BREAK_DETECTION_MODE2:
            /* Only one physical channel is required for this diagnostic type */
            cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCR[t_u1VirtualChannel] = (uint32)( (uint32)( (uint32)ADC_VCR_CNVCLS_BREAK2_DOWN                      * (uint32)ADC_VCR_CNVCLS_0 )
                                                                                  + (uint32)( (uint32)t_pu1PhysicalChannels[t_u1PsysicalChannelIndex]  /* * (uint32)ADC_VCR_GCTRL_0  - value is BIT0 */ ) ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
            break;
        case u1ADCDIAG_PIL_AD_CORE:
            cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCR[t_u1VirtualChannel] = (uint32)( (uint32)ADC_VCR_CNVCLS_DIAG * (uint32)ADC_VCR_CNVCLS_0 );
            break;
        case u1ADCDIAG_PIL_PIN_LEVEL:
            cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCR[t_u1VirtualChannel] = (uint32)( (uint32)( (uint32)ADC_VCR_CNVCLS_PIN_DIAG                 * (uint32)ADC_VCR_CNVCLS_0 )
                                                                                  + (uint32)( (uint32)t_pu1PhysicalChannels[t_u1PsysicalChannelIndex]  /* * (uint32)ADC_VCR_GCTRL_0  - value is BIT0 */ ) ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
            break;
        default:
        	/* Do nothing */
            break;
    }
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_SetChannelPointer                                         */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1HWUnit          : HW Unit Number                                                        */
/*      t_u1ScanGroup       : Scan Group                                                            */
/*      t_u1StartPointer    : Start Pointer                                                         */
/*      t_u1StartPointer    : Stop Pointer                                                          */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Configure Start and Stop Pointer                                      */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_SetChannelPointer(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1ScanGroup,
    CONST(uint8, ADCDIAG_CONST)     t_u1StartPointer,
    CONST(uint8, ADCDIAG_CONST)     t_u1StopPointer
)
{
    cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u2SGVCPR = (uint16) ( (uint16)( (uint16)t_u1StartPointer /* * (uint16)ADC_SGVCPR_VCSP_0 - value is BIT0 */ )
                                                                              + (uint16)( (uint16)t_u1StopPointer  * (uint16)ADC_SGVCPR_VCEP_0 ) ) ; /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_SetRegWiringBreakDetectionMode1                           */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*t_u1HWUnit                : HW Unit Number                                                        */
/*t_u1ScanGroup             : Scan Group                                                            */
/*t_u1ConversionNo          : Scan count in multicycle scan mode                                    */
/*t_u2PulseWidthWiringBreak1: Wiring-Break Detection Pulse Width                                    */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Setting the registers used for Wiring-Break Detection for Mode 1      */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_SetRegWiringBreakDetectionMode1(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1ScanGroup,
    CONST(uint8, ADCDIAG_CONST)     t_u1ConversionNo,
    CONST(uint16, ADCDIAG_CONST)    t_u2PulseWidthWiringBreak1
)
{
    cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u1SGMCYCR = (uint8)(t_u1ConversionNo  /* * (uint8)ADC_SGMCYCR_MCYC_0 - value is BIT0 */ );
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u2ODCR = (uint16)( (uint16)( t_u2PulseWidthWiringBreak1   /* * (uint16)ADC_ODCR_ODPW_0 - value is BIT0 */ )
                                                       /* + (uint16)( (uint16)ADC_ODCR_WADDE_NORMAL - value is 0 * (uint16)ADC_ODCR_WADDE ) */ );
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_StartScan                                                 */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1HWUnit          : HW Unit Number                                                        */
/*      t_u1ScanGroup       : Scan Group                                                            */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Start A/D conversion                                                  */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_StartScan(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1ScanGroup
)
{
    cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u1SGSTCR = (uint8)( ADC_SGSTCR_SGST_SCAN_START & ADC_SGSTCR_SGST );
    Bswlib_Sync_Pipeline_1(cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u1SGSTCR);
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_GetScanStatus                                             */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1HWUnit          : HW Unit Number                                                        */
/*      t_u1ScanGroup       : Scan Group                                                            */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             :                                                                       */
/*      uint8               : Conversion status                                                     */
/* Description              : Reads scan group status                                               */
/****************************************************************************************************/
FUNC(uint8, ADCDIAG_CODE) AdcDiag_Pil_GetScanStatus(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1ScanGroup
)
{
    return ( (uint8) cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u1SGSR );
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_StartSelfDiagTH                                           */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*     t_udPilTHData(Sync)  : Pointer to T&H data structure                                         */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : boolean                                                               */
/*     TRUE                 : No timeout occurred                                                   */
/*     FALSE                : Timeout occurred                                                      */
/* Description              : Start Self-Diagnosis T&H                                              */
/****************************************************************************************************/
FUNC(boolean, ADCDIAG_CODE) AdcDiag_Pil_DoSelfDiagTH(
	CONSTP2VAR(AdcDiag_Pil_THData, AUTOMATIC, ADCDIAG_CONST)     t_udPilTHData
)
{
    VAR(uint8, ADCDIAG_VAR_NO_INIT)     t_u1IndexVirtualChannel;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)     t_u1Pos;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)     t_u1Index;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)     t_u1RegValue;
    VAR(boolean, ADCDIAG_VAR_NO_INIT)   t_u1IsConversionCompleted;

    /* Reg_AIR.u4AIRISELR0 = (uint32)0; - */

    /* A/D conversion of A/D conversion data path diagnosis (ADVAL mode) is selected */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u4VCR[t_udPilTHData->u1StartPointer] = u4ADCADIAG_PIL_FIRST_VCR_ADVAL;

    /* A/D conversion of A/D conversion data path diagnosis (ADVAL mode) is selected */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u4VCR[t_udPilTHData->u1StartPointer + (uint8)1U] = u4ADCADIAG_PIL_SECOND_VCR_ADVAL; /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
    t_u1IndexVirtualChannel = t_udPilTHData->u1StartPointer + u1ADCDIAG_PIL_TH_VIRTUAL_CHANNELS_NOT_USED;

    for ( t_u1Index = (uint8)0U; t_u1Index < t_udPilTHData->u1PhysicalChannelsNo; t_u1Index++ )
    {
        t_u1Pos = t_u1Index + t_u1IndexVirtualChannel;
        cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u4VCR[t_u1Pos] = (uint32)( (uint32)( (uint32)ADC_VCR_CNVCLS_HOLD                   * (uint32)ADC_VCR_CNVCLS_0 )
                                                                                + (uint32)( (uint32)t_udPilTHData->pu1PhysicalChannels[t_u1Index] /* * (uint32)ADC_VCR_GCTRL_0 - value is BIT0 */ ) ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
    }

    for ( t_u1Index = (uint8)0U; t_u1Index < t_udPilTHData->u1PhysicalChannelsNo; t_u1Index++ )
    {
        t_u1Pos = t_u1IndexVirtualChannel + t_udPilTHData->u1PhysicalChannelsNo + t_u1Index;
        cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u4VCR[t_u1Pos] = (uint32)( (uint32)( (uint32)ADC_VCR_CNVCLS_PIN_DIAG                            * (uint32)ADC_VCR_CNVCLS_0 )
                                                                   	   	   	    + (uint32)( (uint32)t_udPilTHData->pu1PhysicalChannels[t_udPilTHData->u1PhysicalChannelsNo - (uint8)1U - t_u1Index] /* * (uint32)ADC_VCR_GCTRL_0 - value is BIT0 */ ) ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
    }

    /*Asynchronous suspend is selected as Suspending Method */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u1ADCR1 |= u1ADCADIAG_PIL_ADCR1_SUSMTD_ASYNC;

    /* T&H Path Self-Diagnosis is enabled, voltage level for testing is set */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u1TDCR = (uint8)( (uint8)( ADC_TDCR_THSDE_ENABLE   * (uint8)ADC_TDCR_THSDE)
                                                      	  	+ (uint8)( t_udPilTHData->u1VoltageLevelAtStart  /* * (uint8)ADC_TDCR_TDLV_0 - value is BIT0 */ ) );

    /* Start sampling automatically at the end of hold value A/D conversion */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u1THCR = u1ADCADIAG_PIL_THCR_AUTO_SMP_MSK;

    /* Hold control is enabled  */
    /* Scan group used for T&H is 1. To select scan group 1 of T&H group A, u1THACR.SGS bit should be set to 0 */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u1THACR =(uint8)( (uint8)( ADC_THACR_HLDCTE_ENABLE * ADC_THACR_HLDCTE  ) \
                                                      + (uint8)( ADC_THACR_HLDTE_DISABLE * ADC_THACR_HLDTE ) \
                                                      + (uint8)( (uint8)( t_udPilTHData->u1ScanGroup - (uint8)1U ) /* * (uint8)ADC_THACR_SGS_0 - value is BIT0 */ ) );

	/* Enable track and hold operation of the T&H circuit */
    t_u1RegValue =(uint8) 0U;
    for ( t_u1Index = (uint8)0U; t_u1Index < t_udPilTHData->u1PhysicalChannelsNo; t_u1Index++ )
    {
    	t_u1RegValue |= (uint8)( /* (uint8)ADC_THER_THZE_ENABLE - value is 1 * */ ( (uint8)BIT0 << t_u1Index ) );
    }
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u1THER = t_u1RegValue;

#if ( MCAL_SPAL_TARGET != MCAL_TARGET_RH850U2A )
    /* Group A is selected for each T&H group */
    /* TH5GHS does not exist on ADCK3 on U2B6, but this is not as issue because the register is written with the reset value */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u2THGSR = u2ADCADIAG_PIL_THGSR_GROUP_A_SEL;
#endif /* ( MCAL_SPAL_TARGET != MCAL_TARGET_RH850U2A ) - */

    /* Start and End Channel Settings */
    AdcDiag_Pil_SetChannelPointer( t_udPilTHData->u1HWUnit, t_udPilTHData->u1ScanGroup, t_udPilTHData->u1StartPointer, t_udPilTHData->u1StopPointer );

    /* Set trigger mode */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.stSG[t_udPilTHData->u1ScanGroup].u1SGCR = u1ADCADIAG_PIL_SGCR_TRGMD;

    /* Set the scan count to one */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.stSG[t_udPilTHData->u1ScanGroup].u1SGMCYCR = u1ADCADIAG_PIL_SGMCYCR_SCAN_COUNT;

    /* Start T&H Sampling */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u1THSMPSTCR = u1ADCADIAG_PIL_THSMPSTCR_START_SMP;

    /* Wait for at least 0.45 μs */
    MCAL_LIB_Wait((uint32)1U);

    /* Start T&H hold processing */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.u1THAHLDSTCR = u1ADCADIAG_PIL_THAHLDSTCR_START_HOLD;

    /* Clear ADCnDIRj.WFLAG before starting a new conversion */
    AdcDiag_Pil_ClearDIR( t_udPilTHData->u1HWUnit, t_udPilTHData->u1StartPointer );
    AdcDiag_Pil_ClearDIR( t_udPilTHData->u1HWUnit, t_udPilTHData->u1StopPointer );

    /* Start scan of configured scan group */
    cpstReg_Adc[t_udPilTHData->u1HWUnit]->stMODULE.stSG[t_udPilTHData->u1ScanGroup].u1SGSTCR = u1ADCADIAG_PIL_SGSTCR_START_SCAN;

    /* Wait for the WFLAG to be set for first virtual channel */
    if ( AdcDiag_Pil_IsConversionCompleted( t_udPilTHData->u1HWUnit, t_udPilTHData->u1ScanGroup, t_udPilTHData->u4TimeoutValueA, (boolean)TRUE ) == (boolean)TRUE )
    {
        /* Change Pin-Level Self-Diagnosis Voltage Level after the first channel was converted */
        AdcDiag_Pil_Set3PointVoltageGenerator( t_udPilTHData->u1HWUnit, t_udPilTHData->u1VoltageLevelAfterChange );

        /* Wait for the WFLAG to be set for last virtual channel */
        t_u1IsConversionCompleted = AdcDiag_Pil_IsConversionCompleted( t_udPilTHData->u1HWUnit, t_udPilTHData->u1ScanGroup, t_udPilTHData->u4TimeoutValueB, (boolean)FALSE );
    }
    else
    {
        t_u1IsConversionCompleted = (boolean)FALSE;
    }
    return ( t_u1IsConversionCompleted );
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_Set3PointVoltageGenerator                                 */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*    t_u1HWUnit            : HW Unit Number                                                        */
/*    t_u1VoltageLevel      : Voltage Level                                                         */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Set voltage settings for the 3 point voltage generator                */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_Set3PointVoltageGenerator(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1VoltageLevel
)
{
    VAR(uint8, ADCDIAG_VAR_NO_INIT)    t_u1Temp;
    t_u1Temp = (uint8)( cpstReg_Adc[t_u1HWUnit]->stMODULE.u1TDCR & (uint8)~ADC_TDCR_TDLV );

    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1TDCR = (uint8)( t_u1Temp | (uint8)  ( t_u1VoltageLevel /* * (uint8)ADC_TDCR_TDLV_0 - value is BIT0 */ ) );
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_ChangeADCoreVoltageLevel                                  */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*    t_u1HWUnit            : HW Unit Number                                                        */
/*    t_u1VirtualChannel    : Virtual Channel                                                       */
/*    t_u1VoltageLevel      : Voltage Level                                                         */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Set AdCore voltage value                                              */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_ChangeADCoreVoltageLevel(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1VirtualChannel,
    CONST(uint8, ADCDIAG_CONST)     t_u1VoltageLevel
)
{
	VAR(uint32, ADCDIAG_VAR_NO_INIT)    t_u4Temp;
	t_u4Temp = (uint32)( cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCR[t_u1VirtualChannel] & (uint32)~(uint32)ADC_VCR_GCTRL );

    cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCR[t_u1VirtualChannel] = (uint32) ( t_u4Temp | (uint32)( (uint32)t_u1VoltageLevel /* * (uint32)ADC_VCR_GCTRL_0 - value is BIT0 */ ) );
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_InitialSettingFlow                                        */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*    t_u1HWUnit            : HW Unit ID                                                            */
/*    t_u1DataFormat        : Data Format	                                                        */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Settings according to the initial setting procedure                   */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_InitialSettingFlow(
    CONST(uint8, ADCDIAG_CONST) t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST) t_u1DataFormat
)
    /* Write a value after reset */
    /* for (t_u1Index = (uint8)0U; t_u1Index < (uint8)ADC_VCT_NUM; t_u1Index++ ) -
    {
        cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCULLMTBR[t_u1Index] = (uint32)(ADC_VCULLMTBR_VCLLMTB_0 * 0U ) + (uint32)(ADC_VCULLMTBR_VCULMTB_0 * 0x7FFF);-
    } */

    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCLMINTER1 = (uint32)(ADC_VCLMINTER1_ADUL00IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL01IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL02IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL03IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL04IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL05IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL06IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL07IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL08IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL09IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL10IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL11IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL12IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL13IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL14IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL15IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL16IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL17IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL18IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL19IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL20IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL21IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL22IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL23IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL24IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL25IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL26IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL27IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL28IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL29IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL30IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER1_ADUL31IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT); - */

    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCLMINTER2 = (uint32)(ADC_VCLMINTER2_ADUL32IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL33IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL34IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL35IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL36IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL37IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL38IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL39IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL40IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL41IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL42IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL43IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL44IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL45IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL46IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL47IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL48IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL49IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL50IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL51IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL52IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL53IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL54IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL55IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL56IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL57IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL58IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL59IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL60IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL61IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL62IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMINTER2_ADUL63IE * ADC_VCLMINTER1_ADULIE_NOTOUTPUT); - */

    /* Write a value after reset */
    /* #if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u1SDVCLMINTER = (uint8)(ADC_SDVCLMINTER_SDADULIE * ADC_SDVCLMINTER_SDADULIE_NOTOUTPUT); - */
    /* #endif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCLMINTER1 = (uint32)(ADC_VCLMSR1_VC00LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC01LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC02LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC03LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC04LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC05LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC06LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC07LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC08LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC09LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC10LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC11LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC12LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC13LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC14LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC15LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC16LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC17LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC18LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC20LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC21LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC22LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC23LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC24LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC25LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC26LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC27LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC28LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC29LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC30LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR1_VC31LMS * ADC_VCLMSR1_VCLMS_NOTOUTPUT); - */

    /* Write a value after reset */
   /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCLMINTER2 = (uint32)(ADC_VCLMSR2_VC32LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC33LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC34LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC35LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC36LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC37LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC38LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC39LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC40LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC41LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC42LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC43LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC44LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC45LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC46LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC47LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC48LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC49LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC50LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC51LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC52LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC53LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC54LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC55LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC56LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC57LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC58LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC59LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC60LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC61LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC62LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT) \ -
                                                    +(uint32)(ADC_VCLMSR2_VC63LMS * ADC_VCLMSR2_VCLMS_NOTOUTPUT); - */
{
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1ADCR1 = (uint8)((uint8)ADC_ADCR1_SUSMTD_0 * (uint8)ADC_ADCR1_SUSMTD_SYNC);       /* Mentioned in diagram */
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1ADCR2 = (uint8)( (uint8)((uint8)t_u1DataFormat * (uint8)ADC_ADCR2_DFMT_0 ) /* + (uint8)( (uint8)ADC_ADCR2_ADDNT_2TIMES - value is 0 * (uint8)ADC_ADCR2_ADDNT ) */ );       /* Mentioned in diagram */
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1SFTCR =  u1ADCDIAG_PIL_SFTCR; /* Mentioned in diagram */

    /* #if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) - */
    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.PWVCLMINTER = u1ADCADIAG_PIL_PWVCLMINTER_DEFAULT_VALUE; - */
    /* #endif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) */

    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u1VMONVDCR1 = 0; -  */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u1VMONVDCR2 = 0; -  */

    /* Set sampling period and set AMP disable */
    AdcDiag_Pil_ConfigureSampling( t_u1HWUnit, ADC_SMPCR_BUFAMPD_DISABLE );

    /* Write a value after reset */
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1TDCR = u1ADCADIAG_PIL_TDCR_DEFAULT_VALUE;

    /* Write a value after reset */
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u2ODCR = u2ADCADIAG_PIL_ODCR_DEFAULT_VALUE;

    /* #if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */
    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u1MPXCURCR = (uint8)(ADC_MPXCURCR_MSKCFMT_0 * ADC_MPXCURCR_MSKCFMT_MSKC0); - */

    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u1MPXCMDR = (uint8)(ADC_MPXCMDR_MPXCMD_0 * 0U); - */

    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u1MPXINTER = (uint8)(ADC_MPXINTER_ADMPXIE * ADC_MPXINTER_ADMPXIE_NOTOUTPUT); - */
    /* #endif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

    /* Write a value after reset */
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1TOCCR = u1ADCADIAG_PIL_TOCCR_DEFAULT_VALUE;

    /* Write a value after reset */
    /* #if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u2DFASENTSGER = (uint16)(ADC_DFASENTSGER_ASENTSG0E * ADC_DFASENTSGER_ASENTSG0E_DISABLE) \ -
                                                            + (uint16)(ADC_DFASENTSGER_ASENTSG1E * ADC_DFASENTSGER_ASENTSG1E_DISABLE) \ -
                                                            + (uint16)(ADC_DFASENTSGER_ASENTSG2E * ADC_DFASENTSGER_ASENTSG2E_DISABLE) \ -
                                                            + (uint16)(ADC_DFASENTSGER_ASENTSG3E * ADC_DFASENTSGER_ASENTSG3E_DISABLE) \ -
                                                            + (uint16)(ADC_DFASENTSGER_ASENTSG4E * ADC_DFASENTSGER_ASENTSG4E_DISABLE) \ -
                                                            + (uint16)(ADC_DFASENTSGER_DFENTSG0E * ADC_DFASENTSGER_DFENTSG0E_DISABLE) \ -
                                                            + (uint16)(ADC_DFASENTSGER_DFENTSG1E * ADC_DFASENTSGER_DFENTSG1E_DISABLE) \ -
                                                            + (uint16)(ADC_DFASENTSGER_DFENTSG2E * ADC_DFASENTSGER_DFENTSG2E_DISABLE) \ -
                                                            + (uint16)(ADC_DFASENTSGER_DFENTSG3E * ADC_DFASENTSGER_DFENTSG3E_DISABLE) \ -
                                                            + (uint16)(ADC_DFASENTSGER_DFENTSG4E * ADC_DFASENTSGER_DFENTSG4E_DISABLE); - */
    /* #elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) - */
    /* if ( t_u1HWUnit < (uint8)ADC_HWUNIT2 ) { - */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u2GTMENTSGER = u2ADCADIAG_PIL_GTMENTSGER_DEFAULT_VALUE; - */
    /* } */
    /* #endif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

    /* Write a value after reset */
    /* for (t_u1Index = (uint8)0U; t_u1Index < (uint8)5U; t_u1Index++ ) { - */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.stADENDP[t_u1Index].u1Data = (uint8)(ADC_ADENDP_ENDP_0 * 0U); - */
    /* } */
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
    /* Write a value after reset */
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1THCR = u1ADCADIAG_PIL_THCR_DEFAULT_VALUE;
#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
    /* Write a value after reset */
    if ( t_u1HWUnit < (uint8)ADC_HWUNIT2 ) {
        cpstReg_Adc[t_u1HWUnit]->stMODULE.u1THCR = u1ADCADIAG_PIL_THCR_DEFAULT_VALUE;
    }
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
    /* Write a value after reset */
     cpstReg_Adc[t_u1HWUnit]->stMODULE.u2THGSR =(uint16)(ADC_THGSR_TH0GS * ADC_THGSR_TH0GS_SELECTED_A) \
                                                    + (uint16)(ADC_THGSR_TH1GS * ADC_THGSR_TH1GS_SELECTED_A) \
                                                    + (uint16)(ADC_THGSR_TH2GS * ADC_THGSR_TH2GS_SELECTED_A) \
                                                    + (uint16)(ADC_THGSR_TH3GS * ADC_THGSR_TH3GS_SELECTED_A) \
                                                    + (uint16)(ADC_THGSR_TH4GS * ADC_THGSR_TH4GS_SELECTED_A) \
                                                    + (uint16)(ADC_THGSR_TH5GS * ADC_THGSR_TH5GS_SELECTED_A);
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
    /* Write a value after reset */
    if ( t_u1HWUnit < (uint8)ADC_HWUNIT2 ) {
        cpstReg_Adc[t_u1HWUnit]->stMODULE.u1THER =(uint8)(ADC_THER_TH0E * ADC_THER_THZE_DISABLE) \
                                                   + (uint8)(ADC_THER_TH1E * ADC_THER_THZE_DISABLE) \
                                                   + (uint8)(ADC_THER_TH2E * ADC_THER_THZE_DISABLE) \
                                                   + (uint8)(ADC_THER_TH3E * ADC_THER_THZE_DISABLE);
    }
#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
     /* Write a value after reset */
      cpstReg_Adc[t_u1HWUnit]->stMODULE.u1THER =(uint8)(ADC_THER_TH0E * ADC_THER_THZE_DISABLE) \
                                                   + (uint8)(ADC_THER_TH1E * ADC_THER_THZE_DISABLE) \
                                                   + (uint8)(ADC_THER_TH2E * ADC_THER_THZE_DISABLE) \
                                                   + (uint8)(ADC_THER_TH3E * ADC_THER_THZE_DISABLE) \
                                                   + (uint8)(ADC_THER_TH4E * ADC_THER_THZE_DISABLE) \
                                                   + (uint8)(ADC_THER_TH5E * ADC_THER_THZE_DISABLE);

#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) - */

    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[3].u4ADTIPR = (uint32)(ADC_ADTIPR_ADTIP_0 * 0U); - */

    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[4].u4ADTIPR = (uint32)(ADC_ADTIPR_ADTIP_0 * 0U); - */

    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[3].u4ADTPRR = (uint32)(ADC_ADTPRR_ADTPR_0 * 0x1FFFFF); - */

    /* Write a value after reset */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[4].u4ADTPRR = (uint32)(ADC_ADTPRR_ADTPR_0 * 0x1FFFFF); - */

    /* Write a value after reset */
    /*  for (t_u1Index = (uint8)0U; t_u1Index < (uint8)ADC_VCT_NUM; t_u1Index++ ) { -

        cpstReg_Adc[t_u1HWUnit]->stMODULE.stWAITTR[t_u1Index].u2Data = (uint16)(ADC_WAITTR_WAITTIME_0 * 0U) -;
    } */

    /* Write a value after reset */
    /* #if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u4SGDIAGPCCR0 = (uint32)( (uint32)( ADC_SGDIAGPCCR_SDPCE0  * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE1  * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE2  * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE3  * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE4  * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE5  * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE6  * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE7  * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE8  * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE9  * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE10 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE11 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE12 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE13 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE14 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE15 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE16 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE17 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE18 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE19 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE20 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE21 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE22 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE23 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE24 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE25 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE26 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE27 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE28 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE29 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE30 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) \ -
                                                              + (uint32)( ADC_SGDIAGPCCR_SDPCE31 * ADC_SGDIAGPCCR_SDPCEy_NOTCNV ) ); - */

    /* Write a value after reset */
    /*     for (t_u1Index = (uint8)0U; t_u1Index < ADC_SGDIAG_CHANNEL_NUM; t_u1Index++ ) { -

        cpstReg_Adc[t_u1HWUnit]->stMODULE.stSGDIAGVCR[t_u1Index].u1data = (uint8)(ADC_SGDIAGVCR_CNVCLS_0 * ADC_SGDIAGVCR_CNVCLS_NORMAL) -;
    } */
    /* #endif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
    /* Write a value after reset */
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1THACR = (uint8)(ADC_THACR_SGS_0 * ADC_THACR_SGS_SG1) \
                                                     + (uint8)(ADC_THACR_HLDTE * ADC_THACR_HLDTE_DISABLE) \
                                                     + (uint8)(ADC_THACR_HLDCTE * ADC_THACR_HLDCTE_DISABLE);
#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
    /* Write a value after reset */
    if ( t_u1HWUnit < (uint8)ADC_HWUNIT2 ) {
        cpstReg_Adc[t_u1HWUnit]->stMODULE.u1THACR = (uint8)(ADC_THACR_SGS_0 * ADC_THACR_SGS_SG1) \
                                                     + (uint8)(ADC_THACR_HLDTE * ADC_THACR_HLDTE_DISABLE) \
                                                     + (uint8)(ADC_THACR_HLDCTE * ADC_THACR_HLDCTE_DISABLE);
    }
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */
    /* Write a value after reset */
    /* #if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */
    /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u1THBCR = (uint8)(ADC_THBCR_SGS_0 * ADC_THBCR_SGS_SG1) \ -
                                                     + (uint8)(ADC_THBCR_HLDTE * ADC_THBCR_HLDTE_DISABLE) \ -
                                                     + (uint8)(ADC_THBCR_HLDCTE * ADC_THBCR_HLDCTE_DISABLE); - */

    /* Write a value after reset */
    /*
    for (t_u1Index = (uint8)0U; t_u1Index < ADC_SGDIAG_CHANNEL_NUM; t_u1Index++ ) { -

        cpstReg_Adc[t_u1HWUnit]->stMODULE.stSTPDCR[t_u1Index].u1Data = (uint8)(ADC_STPDCR_SPDE * ADC_STPDCR_SPDE_DISABLE) -;
    }
	#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) - */

	 /* Write a value after reset */
	 /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u1PWDCR = u1ADCADIAG_PIL_PWDCR_DEFAULT_VALUE; - */

     /* Write a value after reset */
	 /* cpstReg_Adc[t_u1HWUnit]->stMODULE.u1PWDSGCR = u1ADCADIAG_PIL_PWDSGCR_DEFAULT_VALUE; - */
     /* #endif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) */

}
/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_StopAllScan                                               */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*     t_u1HWUnit           : HW Unit Number                                                        */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : All Scan Groups of Module Scan Stop Function                          */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_StopAllScan(
    CONST(uint8, ADCDIAG_CONST)   t_u1HWUnit
)
{
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1ADHALTR = (uint8)( ADC_ADHALTR_HALT_SCAN_HALT * ADC_ADHALTR_HALT );
    Bswlib_Sync_Pipeline_1( cpstReg_Adc[t_u1HWUnit]->stMODULE.u1ADHALTR );
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_ModuleReset                                               */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*     t_u4TimeoutValue	    : Timeout value for reset                                               */
/*     t_u4ClocksUsed       : Which clock is supplied                                               */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : Std_ReturnType                                                        */
/*     E_OK                 : No timeout occurred                                                   */
/*     E_NOT_OK             : Timeout occurred                                                      */
/* Description              : Software Module Reset Assertion Register for ADC                      */
/****************************************************************************************************/
FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_Pil_ModuleReset(
    CONST(uint32, ADCDIAG_CONST)         t_u4TimeoutValue,
    CONST(uint32, ADCDIAG_CONST)         t_u4ClocksUsed
)
{
    VAR(uint32, ADCDIAG_VAR_NO_INIT)        t_u4CountVal;
    VAR(Std_ReturnType, ADCDIAG_VAR_NO_INIT)     t_udErrorStatus;

    t_udErrorStatus = (Std_ReturnType)E_OK;
    t_u4CountVal = (uint32)0U;
    REG_RESET_ISO.u4RESKCPROT0 = MCU_RESET_PROTECT_ENABLE;  /* Enable writing to protected registers */
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
    REG_RESET_ISO.u4SWMRESA_ADCJ_ISO = (uint32)((~(uint32)t_u4ClocksUsed) & u4ADCDIAG_PIL_U2A_RESET_VALUE_MASK);

    Bswlib_Sync_Pipeline_4(REG_RESET_ISO.u4SWMRESA_ADCJ_ISO);

    while( REG_RESET_ISO.u4SWMRESS_ADCJ_ISO != (uint32)0U ){

        t_u4CountVal ++; /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
        if ( t_u4CountVal == t_u4TimeoutValue )
        {
            t_udErrorStatus = (Std_ReturnType)E_NOT_OK;
            break;
        }
    }
    /* ADCJ2 Hw Unit should be reset only if it is used and clock are supplied */
    if ( ( t_udErrorStatus != (Std_ReturnType)E_NOT_OK ) &&
        ( (uint32)( t_u4ClocksUsed & u4ADCDIAG_PIL_ADCJ2_RESET_VALUE_MASK ) == (uint32)0U ) )
    {
        AdcDiag_Pil_ADCJ2ModuleReset();
    }
#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )

    REG_RESET_ISO.u4SWMRESA_ADCK_ISO = (uint32)((~(uint32)t_u4ClocksUsed) & u4ADCDIAG_PIL_U2B_RESET_VALUE_MASK);

    Bswlib_Sync_Pipeline_4(REG_RESET_ISO.u4SWMRESA_ADCK_ISO);

    while( REG_RESET_ISO.u4SWMRESS_ADCK_ISO != (uint32)0U ){

        t_u4CountVal ++; /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
        if ( t_u4CountVal == t_u4TimeoutValue )
        {
            t_udErrorStatus = (Std_ReturnType)E_NOT_OK;
            break;
        }
    }
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) - */
    REG_RESET_ISO.u4RESKCPROT0 = MCU_RESET_PROTECT_DISABLE; /* Disable writing to protected registers */
    return ( t_udErrorStatus );
}

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_IsConversionCompleted                                     */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/* 		t_cu1HWUnit	        : HW Unit Number														*/
/* 		t_cu1ScanGroup      : Scan Group Number														*/
/*      t_u4TimeoutValue	: Timeout value                                                         */
/*      t_cbUseStartPointer : Value to check which virtual channel pointer are used                 */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : boolean                                                               */
/*     TRUE                 : No timeout occurred                                                   */
/*     FALSE                : Timeout occurred                                                      */
/* Description              : Wait until the flag is set for the last or first virtual channel      */
/****************************************************************************************************/
FUNC(boolean, ADCDIAG_CODE) AdcDiag_Pil_IsConversionCompleted(
    CONST(uint8, ADCDIAG_CONST)	     t_cu1HWUnit,
    CONST(uint8, ADCDIAG_CONST)	     t_cu1ScanGroup,
    CONST(uint32, ADCDIAG_CONST)     t_cu4TimeoutValue,
    CONST(boolean, ADCDIAG_CONST)	 t_cbUseStartPointer
)
{
    VAR(uint32, ADCDIAG_VAR_NO_INIT)    t_u4CountVal;
    VAR(uint16,		ADC_VAR_NO_INIT)	t_u2VCRPosition;
    VAR(boolean,	ADC_VAR_NO_INIT)	t_u1IsConversionCompleted;

    /* Timeout will be reported to upper layer. */
    t_u4CountVal = (uint32)0U;
    t_u1IsConversionCompleted = (boolean)TRUE;

    if ( t_cbUseStartPointer == (boolean)TRUE )
    {
        /* First check for T&H should check first virtual channel */
        t_u2VCRPosition = (uint16) ( cpstReg_Adc[t_cu1HWUnit]->stMODULE.stSG[t_cu1ScanGroup].u2SGVCPR & (uint16)ADC_SGVCPR_VCSP );
    }
    else
    {
        /* Get the virtual channel end position */
        t_u2VCRPosition = (uint16) ( ( cpstReg_Adc[t_cu1HWUnit]->stMODULE.stSG[t_cu1ScanGroup].u2SGVCPR & (uint16)ADC_SGVCPR_VCEP ) >> (uint16)ADC_SGVCPR_VCEP_BITPOS );
    }
    /* Wait until Write Flag is set */
    while ( (uint32)( cpstReg_Adc[t_cu1HWUnit]->stMODULE.u4DIR[t_u2VCRPosition] & (uint32)ADC_DIR_WFLAG ) != (uint32)( (uint32)ADC_DIR_WFLAG_SET * (uint32)ADC_DIR_WFLAG ) )
    {
        t_u4CountVal ++; /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
        if ( t_u4CountVal == t_cu4TimeoutValue )
        {
            t_u1IsConversionCompleted = (boolean)FALSE;
            break;
        }
    }
    return ( t_u1IsConversionCompleted );
}

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_ADCJ2ModuleReset                                          */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          : None                                                                  */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Software Module Reset Assertion Register for ADCj2                    */
/****************************************************************************************************/
static FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_ADCJ2ModuleReset( void )
{
	volatile	P2VAR(Reg_Adc_SELB_Type,	AUTOMATIC,	ADC_VAR_NO_INIT)	t_pstSGTSELReg;
	VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1HWUnit;
	VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1VirtualChannel;
	VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1ScanGroup;
	VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1Index;

	t_u1HWUnit = (uint8)ADC_HWUNIT2;;
	t_pstSGTSELReg = cpstReg_SELB_Adc[0U];
	/* Reset all the registers for ADCJ2 to the reset value */
	for ( t_u1VirtualChannel = (uint8)0U; t_u1VirtualChannel < (uint8)ADC_CHANNEL_NUM; t_u1VirtualChannel++ )
	{
		cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCR[t_u1VirtualChannel] = u4ADCADIAG_PIL_VCR_DEFAULT_VALUE;
	}

	for ( t_u1ScanGroup = (uint8)0U; t_u1ScanGroup < (uint8)ADC_SG_NUM; t_u1ScanGroup++ )
	{
		cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u2SGVCPR = u2ADCADIAG_PIL_SGVCPR_DEFAULT_VALUE;
		cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u1SGMCYCR = u1ADCADIAG_PIL_SGMCYCR_DEFAULT_VALUE;
		t_pstSGTSELReg->u4SGTSEL[t_u1ScanGroup] = u4ADCADIAG_PIL_SGTSEL_DEFAULT_VALUE;
		cpstReg_Adc[t_u1HWUnit]->stMODULE.stADENDP[t_u1ScanGroup].u1Data = u1ADCADIAG_PIL_ADENDP_DEFAULT_VALUE;

		if ( t_u1ScanGroup < u1ADCADIAG_PIL_SG_NUM_012 )
		{
			cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u1SGCR = u1ADCADIAG_PIL_SGCR0_2_DEFAULT_VALUE;
		}
		else
		{
			cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u4ADTIPR = u4ADCADIAG_PIL_ADTIPR_DEFAULT_VALUE;
			cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u4ADTPRR = u4ADCADIAG_PIL_ADTPRR_DEFAULT_VALUE;
			cpstReg_Adc[t_u1HWUnit]->stMODULE.stSG[t_u1ScanGroup].u1SGCR = u1ADCADIAG_PIL_SGCR3_4_DEFAULT_VALUE;
		}
	}

	cpstReg_Adc[t_u1HWUnit]->stMODULE.u1PWDCR = u1ADCADIAG_PIL_PWDCR_DEFAULT_VALUE;
	cpstReg_Adc[t_u1HWUnit]->stMODULE.u1PWDSGCR = u1ADCADIAG_PIL_PWDSGCR_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1ADCR1 = u1ADCADIAG_PIL_ADCR1_DEFAULT_VALUE;
	cpstReg_Adc[t_u1HWUnit]->stMODULE.u1ADCR2 = u1ADCADIAG_PIL_ADCR2_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u4SMPCR = u4ADCADIAG_PIL_SMPCR_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1MPXCURCR = u1ADCADIAG_PIL_MPXCURCR_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1MPXINTER = u1ADCADIAG_PIL_MPXINTER_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1MPXCMDR = u1ADCADIAG_PIL_MPXCMDR_DEFAULT_VALUE;

    for ( t_u1Index = (uint8)0U; t_u1Index < (uint8)ADC_VCT_NUM; t_u1Index++ ) {

        cpstReg_Adc[t_u1HWUnit]->stMODULE.stWAITTR[t_u1Index].u2Data = u2ADCADIAG_PIL_WAITTR_DEFAULT_VALUE;
        cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCULLMTBR[t_u1Index] = u4ADCADIAG_PIL_VCULLMTBR_DEFAULT_VALUE;
    }
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1TDCR = u1ADCADIAG_PIL_TDCR_U2A_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u2ODCR = u2ADCADIAG_PIL_ODCR_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1SFTCR = u1ADCDIAG_PIL_SFTCR_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1TOCCR = u1ADCADIAG_PIL_TOCCR_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u2ECR = u2ADCDIAG_PIL_ECR_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCLMINTER1 = u4ADCADIAG_PIL_VCLMINTER1_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCLMINTER2 = u4ADCADIAG_PIL_VCLMINTER1_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1PWVCLMINTER = u1ADCADIAG_PIL_PWVCLMINTER_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCLMSCR1 = u4ADCADIAG_PIL_VCLMSCR1_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u4VCLMSCR2 = u4ADCADIAG_PIL_VCLMSCR2_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1PWVCLMSCR = u1ADCADIAG_PIL_PWVCLMSCR_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1SGULCCR = u1ADCADIAG_PIL_SGULCCR_DEFAULT_VALUE;
    cpstReg_Adc[t_u1HWUnit]->stMODULE.u1VCLMASCR = u1ADCADIAG_PIL_VCLMASCR_DEFAULT_VALUE;
}
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A ) - */

#define ADCDIAG_STOP_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"

/*------------------------------------ End Of File --------------------------------------------------*/
