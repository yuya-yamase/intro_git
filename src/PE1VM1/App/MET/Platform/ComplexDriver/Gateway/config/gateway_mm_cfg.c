/* 1.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Multi Media Gateway                                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GATEWAY_MM_CFG_C_MAJOR                     (1)
#define GATEWAY_MM_CFG_C_MINOR                     (6)
#define GATEWAY_MM_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gateway_mm_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GATEWAY_MM_CFG_C_MAJOR != GATEWAY_MM_H_MAJOR) || \
     (GATEWAY_MM_CFG_C_MINOR != GATEWAY_MM_H_MINOR) || \
     (GATEWAY_MM_CFG_C_PATCH != GATEWAY_MM_H_PATCH))
#error "gateway_mm_cfg.c and gateway_mm.h : source and header files are inconsistent!"
#endif

#if ((GATEWAY_MM_CFG_C_MAJOR != GATEWAY_MM_CFG_PRIVATE_H_MAJOR) || \
     (GATEWAY_MM_CFG_C_MINOR != GATEWAY_MM_CFG_PRIVATE_H_MINOR) || \
     (GATEWAY_MM_CFG_C_PATCH != GATEWAY_MM_CFG_PRIVATE_H_PATCH))
#error "gateway_mm_cfg.c and gateway_mm_cfg_private.h : source and header files are inconsistent!"
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
#define GWMMCFG_SIG_NUM                          (114U)                   /*  Gateway Number           */

#define GWMMCFG_MSGBUF_NUM                       (34U)                    /*  Message Buf Number       */

#define GWMMCFG_MSG_MM_NUM                       (17U)                    /*  Message Number(MM-SUB)   */
#define GWMMCFG_MSG_AVNMC01                      (0U)                     /*  AVNMC01                  */
#define GWMMCFG_MSG_AVNMC02                      (1U)                     /*  AVNMC02                  */
#define GWMMCFG_MSG_AVNMC03                      (2U)                     /*  AVNMC03                  */
#define GWMMCFG_MSG_AVNMC04                      (3U)                     /*  AVNMC04                  */
#define GWMMCFG_MSG_AVNMC05                      (4U)                     /*  AVNMC05                  */
#define GWMMCFG_MSG_AVNMC06                      (5U)                     /*  AVNMC06                  */
#define GWMMCFG_MSG_AVNMC07                      (6U)                     /*  AVNMC07                  */
#define GWMMCFG_MSG_AVNMC08                      (7U)                     /*  AVNMC08                  */
#define GWMMCFG_MSG_AVNMC09                      (8U)                     /*  AVNMC09                  */
#define GWMMCFG_MSG_AVNMC10                      (9U)                     /*  AVNMC10                  */
#define GWMMCFG_MSG_AVNMC11                      (10U)                    /*  AVNMC11                  */
#define GWMMCFG_MSG_AVNMC12                      (11U)                    /*  AVNMC12                  */
#define GWMMCFG_MSG_AVNMC13                      (12U)                    /*  AVNMC13                  */
#define GWMMCFG_MSG_AVNMC14                      (13U)                    /*  AVNMC14                  */
#define GWMMCFG_MSG_AVNMC15                      (14U)                    /*  AVNMC15                  */
#define GWMMCFG_MSG_AVNMC16                      (15U)                    /*  AVNMC16                  */
#define GWMMCFG_MSG_AVNMC17                      (16U)                    /*  AVNMC17                  */

#define GWMMCFG_TMM_SIG_NUM                      (3U)                     /*  Gateway(toMM) Number     */

#define GWMMCFG_TMM_MSGBUF_NUM                   (2U)                     /*  Message Buf(toMM) Number */

#define GWMMCFG_TMM_MSG_MM_NUM                   (1U)                     /*  Message Number(toMM)     */
#define GWMMCFG_MSG_TBC1S01                      (0U)                     /*  TBC1S01                  */

#define GWMMCFG_MSGBYTESIZE                      (8U)                     /*  Can Message ByteSize     */
#define GWMMCFG_MSGBUF_LSB                       (2U)                     /*  Message Buf LSB          */
#define GWMMCFG_MSGBUF_DATASIZE                  (4U)                     /*  Message Buf DataSize     */
#define GWMMCFG_1BYTE_SHIFT                      (8U)                     /*  Can Message Shift 1byte  */



#define GWMMCFG_MMCKPT_SIGMAX                    (1U)                     /*  MMCKPT Signal MAX        */
#define GWMMCFG_L_TBC_FUNC_SIGMAX                (1U)                     /*  L_TBC_FUNC Signal MAX    */

typedef struct{
    U2      u2_msgid;       /*  Rx Frame            */
    U2      u2_failtim;     /*  Fail Judge Time     */
}ST_GWMM_RXMSG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4           u4_gp_gwmm_msgbuf[GWMMCFG_MSGBUF_NUM];                       /*  Message Buf              */
U1           u1_gp_gwmm_strsw_drvmd[GATEWAY_MM_DRVMD_NUM];                /*  SteeringSw DriveMode     */
U1           u1_gp_gwmm_strsw_cnt[GATEWAY_MM_DRVMD_NUM];                  /*  SteeringSw Tx Count      */
U4           u4_gp_gwmm_tmm_msgbuf[GWMMCFG_TMM_MSGBUF_NUM];               /*  Message(toMM) Buf        */
U1           u1_g_gwmm_tmnssw_sigbak;                                     /*  Message Buf(L_TMNSSW)    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4   u4_s_GwmmCfgGetBufData(const U1 *u1_ap_MSGBUF);
static void vd_s_GwmmCfgSend_SRPMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACINV_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_MINTRSOF(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SSMMODE(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TPINSEL(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TPINSELF(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TPINSELR(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TPUNTSET(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SW_AS02(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SW_AS01(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SW_AS05(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TBCSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TBWSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_MRMRQSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_MRMRQBK(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_PCSMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_LDASW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_CSRMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ICSMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_BSMMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_DOAM_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_RCTAMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SW_RCD01(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_IDAMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TSR_MAIN(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACCADPSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACCROSSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACCACLSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACCSPSW1(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACCSPSW2(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACCRACSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACCSSOSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACCPROSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACCSPMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ACCGCRSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ERMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_CCSMDMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SW_DEA01(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_LDAMCUS(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_FCMMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_LDALSMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_LDA_SFB(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_LDAAMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SW_LTC01(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_LCASGMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_DISSUISW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_PCSWDS1(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_DM_SW_A2(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_PCSMBSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_IDASESW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_CTAMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_CTAWDS1(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_BUZ_POS(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_RSR_TIM(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_BSMM_ILV(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_DOAINDSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_DOAM_TIM(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_RSCSW_OP(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_PMARSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_LVNMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TMNSMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TMNVTMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TMNVSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TSR_SNM(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SW_RSA01(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TSR_OSM(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TSR_OSL(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_RSA_NEM(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_RSA_LSM(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SW_ITS04(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SW_ITS01(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SW_ITS02(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_EMGONSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_CACONSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ITSSETSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TRA_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SLSSOSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_AHSSWVSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_AHSSDESW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ADINMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TRLC_ID(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TRLC_AC(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_TRLC_TY(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_NR_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_PW_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_EC_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_CS_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_PDAMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SDGMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_USMMAIN(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_HOFDIOPE(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_HOFCUS(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_DRECSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_DM_SW_AL(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_DM_SW_DR(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_RTWMSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_BSD_SMSB(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_BSD_SMSS(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_SPBZ_OPE(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_RTAN_MSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_RTAN_TIM(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_ADDS_MSW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_CH_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_RG_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_P1_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_R1_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_R2_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_R3_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_R4_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_R5_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_R6_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_R7_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_R8_MD_SW(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_R9_MD_SW(const U1 u1_a_SIG);

static U1 u1_s_GwmmCfgRead_SRPMSW(void);
static U1 u1_s_GwmmCfgRead_ACINV_SW(void);
static U1 u1_s_GwmmCfgRead_MINTRSOF(void);
static U1 u1_s_GwmmCfgRead_SSMMODE(void);
static U1 u1_s_GwmmCfgRead_TPINSEL(void);
static U1 u1_s_GwmmCfgRead_TPINSELF(void);
static U1 u1_s_GwmmCfgRead_TPINSELR(void);
static U1 u1_s_GwmmCfgRead_TPUNTSET(void);
static U1 u1_s_GwmmCfgRead_SW_AS02(void);
static U1 u1_s_GwmmCfgRead_SW_AS01(void);
static U1 u1_s_GwmmCfgRead_SW_AS05(void);
static U1 u1_s_GwmmCfgRead_TBCSW(void);
static U1 u1_s_GwmmCfgRead_TBWSW(void);
static U1 u1_s_GwmmCfgRead_MRMRQSW(void);
static U1 u1_s_GwmmCfgRead_MRMRQBK(void);
static U1 u1_s_GwmmCfgRead_PCSMSW(void);
static U1 u1_s_GwmmCfgRead_LDASW(void);
static U1 u1_s_GwmmCfgRead_CSRMSW(void);
static U1 u1_s_GwmmCfgRead_ICSMSW(void);
static U1 u1_s_GwmmCfgRead_BSMMSW(void);
static U1 u1_s_GwmmCfgRead_DOAM_SW(void);
static U1 u1_s_GwmmCfgRead_RCTAMSW(void);
static U1 u1_s_GwmmCfgRead_SW_RCD01(void);
static U1 u1_s_GwmmCfgRead_IDAMSW(void);
static U1 u1_s_GwmmCfgRead_TSR_MAIN(void);
static U1 u1_s_GwmmCfgRead_ACCADPSW(void);
static U1 u1_s_GwmmCfgRead_ACCROSSW(void);
static U1 u1_s_GwmmCfgRead_ACCACLSW(void);
static U1 u1_s_GwmmCfgRead_ACCSPSW1(void);
static U1 u1_s_GwmmCfgRead_ACCSPSW2(void);
static U1 u1_s_GwmmCfgRead_ACCRACSW(void);
static U1 u1_s_GwmmCfgRead_ACCSSOSW(void);
static U1 u1_s_GwmmCfgRead_ACCPROSW(void);
static U1 u1_s_GwmmCfgRead_ACCSPMSW(void);
static U1 u1_s_GwmmCfgRead_ACCGCRSW(void);
static U1 u1_s_GwmmCfgRead_ERMSW(void);
static U1 u1_s_GwmmCfgRead_CCSMDMSW(void);
static U1 u1_s_GwmmCfgRead_SW_DEA01(void);
static U1 u1_s_GwmmCfgRead_LDAMCUS(void);
static U1 u1_s_GwmmCfgRead_FCMMSW(void);
static U1 u1_s_GwmmCfgRead_LDALSMSW(void);
static U1 u1_s_GwmmCfgRead_LDA_SFB(void);
static U1 u1_s_GwmmCfgRead_LDAAMSW(void);
static U1 u1_s_GwmmCfgRead_SW_LTC01(void);
static U1 u1_s_GwmmCfgRead_LCASGMSW(void);
static U1 u1_s_GwmmCfgRead_DISSUISW(void);
static U1 u1_s_GwmmCfgRead_PCSWDS1(void);
static U1 u1_s_GwmmCfgRead_DM_SW_A2(void);
static U1 u1_s_GwmmCfgRead_PCSMBSW(void);
static U1 u1_s_GwmmCfgRead_IDASESW(void);
static U1 u1_s_GwmmCfgRead_CTAMSW(void);
static U1 u1_s_GwmmCfgRead_CTAWDS1(void);
static U1 u1_s_GwmmCfgRead_BUZ_POS(void);
static U1 u1_s_GwmmCfgRead_RSR_TIM(void);
static U1 u1_s_GwmmCfgRead_BSMM_ILV(void);
static U1 u1_s_GwmmCfgRead_DOAINDSW(void);
static U1 u1_s_GwmmCfgRead_DOAM_TIM(void);
static U1 u1_s_GwmmCfgRead_RSCSW_OP(void);
static U1 u1_s_GwmmCfgRead_PMARSW(void);
static U1 u1_s_GwmmCfgRead_LVNMSW(void);
static U1 u1_s_GwmmCfgRead_TMNSMSW(void);
static U1 u1_s_GwmmCfgRead_TMNVTMSW(void);
static U1 u1_s_GwmmCfgRead_TMNVSW(void);
static U1 u1_s_GwmmCfgRead_TSR_SNM(void);
static U1 u1_s_GwmmCfgRead_SW_RSA01(void);
static U1 u1_s_GwmmCfgRead_TSR_OSM(void);
static U1 u1_s_GwmmCfgRead_TSR_OSL(void);
static U1 u1_s_GwmmCfgRead_RSA_NEM(void);
static U1 u1_s_GwmmCfgRead_RSA_LSM(void);
static U1 u1_s_GwmmCfgRead_SW_ITS04(void);
static U1 u1_s_GwmmCfgRead_SW_ITS01(void);
static U1 u1_s_GwmmCfgRead_SW_ITS02(void);
static U1 u1_s_GwmmCfgRead_EMGONSW(void);
static U1 u1_s_GwmmCfgRead_CACONSW(void);
static U1 u1_s_GwmmCfgRead_ITSSETSW(void);
static U1 u1_s_GwmmCfgRead_TRA_SW(void);
static U1 u1_s_GwmmCfgRead_SLSSOSW(void);
static U1 u1_s_GwmmCfgRead_AHSSWVSW(void);
static U1 u1_s_GwmmCfgRead_AHSSDESW(void);
static U1 u1_s_GwmmCfgRead_ADINMSW(void);
static U1 u1_s_GwmmCfgRead_TRLC_ID(void);
static U1 u1_s_GwmmCfgRead_TRLC_AC(void);
static U1 u1_s_GwmmCfgRead_TRLC_TY(void);
static U1 u1_s_GwmmCfgRead_NR_MD_SW(void);
static U1 u1_s_GwmmCfgRead_PW_MD_SW(void);
static U1 u1_s_GwmmCfgRead_EC_MD_SW(void);
static U1 u1_s_GwmmCfgRead_CS_MD_SW(void);
static U1 u1_s_GwmmCfgRead_PDAMSW(void);
static U1 u1_s_GwmmCfgRead_SDGMSW(void);
static U1 u1_s_GwmmCfgRead_USMMAIN(void);
static U1 u1_s_GwmmCfgRead_HOFDIOPE(void);
static U1 u1_s_GwmmCfgRead_HOFCUS(void);
static U1 u1_s_GwmmCfgRead_DRECSW(void);
static U1 u1_s_GwmmCfgRead_DM_SW_AL(void);
static U1 u1_s_GwmmCfgRead_DM_SW_DR(void);
static U1 u1_s_GwmmCfgRead_RTWMSW(void);
static U1 u1_s_GwmmCfgRead_BSD_SMSB(void);
static U1 u1_s_GwmmCfgRead_BSD_SMSS(void);
static U1 u1_s_GwmmCfgRead_SPBZ_OPE(void);
static U1 u1_s_GwmmCfgRead_RTAN_MSW(void);
static U1 u1_s_GwmmCfgRead_RTAN_TIM(void);
static U1 u1_s_GwmmCfgRead_ADDS_MSW(void);
static U1 u1_s_GwmmCfgRead_CH_MD_SW(void);
static U1 u1_s_GwmmCfgRead_RG_MD_SW(void);
static U1 u1_s_GwmmCfgRead_P1_MD_SW(void);
static U1 u1_s_GwmmCfgRead_R1_MD_SW(void);
static U1 u1_s_GwmmCfgRead_R2_MD_SW(void);
static U1 u1_s_GwmmCfgRead_R3_MD_SW(void);
static U1 u1_s_GwmmCfgRead_R4_MD_SW(void);
static U1 u1_s_GwmmCfgRead_R5_MD_SW(void);
static U1 u1_s_GwmmCfgRead_R6_MD_SW(void);
static U1 u1_s_GwmmCfgRead_R7_MD_SW(void);
static U1 u1_s_GwmmCfgRead_R8_MD_SW(void);
static U1 u1_s_GwmmCfgRead_R9_MD_SW(void);

static void vd_s_GwmmCfgSend_L_TBCAK_ID(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_L_TBCAK_TY(const U1 u1_a_SIG);
static void vd_s_GwmmCfgSend_L_TBC_SF(const U1 u1_a_SIG);

static U1 u1_s_GwmmCfgRead_L_TBCAK_ID(void);
static U1 u1_s_GwmmCfgRead_L_TBCAK_TY(void);
static U1 u1_s_GwmmCfgRead_L_TBC_SF(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1        u1_g_GWMM_SIG_NUM         = (U1)GWMMCFG_SIG_NUM;                  /*  Gateway Signal Number           */
const U1        u1_g_GWMM_MSGBUF_NUM      = (U1)GWMMCFG_MSGBUF_NUM;               /*  Message Buf Number              */
const U1        u1_g_GWMM_MSG_MM_NUM      = (U1)GWMMCFG_MSG_MM_NUM;               /*  Message Number(MM-SUB)          */

const U1        u1_g_GWMM_DRVMD_NUM       = (U1)GATEWAY_MM_DRVMD_NUM;             /*  Drive Mode Number               */

const U1        u1_g_GWMM_TMM_SIG_NUM     = (U1)GWMMCFG_TMM_SIG_NUM;              /*  Gateway Signal(toMM) Number     */
const U1        u1_g_GWMM_TMM_MSGBUF_NUM  = (U1)GWMMCFG_TMM_MSGBUF_NUM;           /*  Message Buf(toMM) Number        */
const U1        u1_g_GWMM_TMM_MSG_MM_NUM  = (U1)GWMMCFG_TMM_MSG_MM_NUM;           /*  Message Number(toMM)            */

const ST_GWMM_MSGCOMVERT st_gp_GWMM_MSGCOMVERT[GWMMCFG_SIG_NUM] = {
/*  u1_idx         u1_bit        u4_mask                                 */
    {(U1)12U,      (U1)7U,       (U4)0x00000001U},         /*  SRPMSW    */
    {(U1)18U,      (U1)7U,       (U4)0x00000001U},         /*  ACINV_SW  */
    {(U1)13U,      (U1)7U,       (U4)0x00000001U},         /*  MINTRSOF  */
    {(U1)13U,      (U1)0U,       (U4)0x00000003U},         /*  SSMMODE   */
    {(U1)8U,       (U1)8U,       (U4)0x0000000FU},         /*  TPINSEL   */
    {(U1)8U,       (U1)16U,      (U4)0x00000007U},         /*  TPINSELF  */
    {(U1)8U,       (U1)20U,      (U4)0x00000007U},         /*  TPINSELR  */
    {(U1)8U,       (U1)13U,      (U4)0x00000007U},         /*  TPUNTSET  */
    {(U1)8U,       (U1)6U,       (U4)0x00000001U},         /*  SW_AS02   */
    {(U1)8U,       (U1)7U,       (U4)0x00000001U},         /*  SW_AS01   */
    {(U1)8U,       (U1)30U,      (U4)0x00000003U},         /*  SW_AS05   */
    {(U1)27U,      (U1)9U,       (U4)0x00000001U},         /*  TBCSW     */
    {(U1)27U,      (U1)8U,       (U4)0x00000001U},         /*  TBWSW     */
    {(U1)11U,      (U1)1U,       (U4)0x00000001U},         /*  MRMRQSW   */
    {(U1)11U,      (U1)0U,       (U4)0x00000001U},         /*  MRMRQBK   */
    {(U1)1U,       (U1)8U,       (U4)0x00000001U},         /*  PCSMSW    */
    {(U1)0U,       (U1)28U,      (U4)0x00000001U},         /*  LDASW     */
    {(U1)1U,       (U1)2U,       (U4)0x00000001U},         /*  CSRMSW    */
    {(U1)1U,       (U1)6U,       (U4)0x00000001U},         /*  ICSMSW    */
    {(U1)1U,       (U1)5U,       (U4)0x00000001U},         /*  BSMMSW    */
    {(U1)4U,       (U1)20U,      (U4)0x00000001U},         /*  DOAM_SW   */
    {(U1)1U,       (U1)7U,       (U4)0x00000001U},         /*  RCTAMSW   */
    {(U1)0U,       (U1)0U,       (U4)0x00000001U},         /*  SW_RCD01  */
    {(U1)4U,       (U1)14U,      (U4)0x00000001U},         /*  IDAMSW    */
    {(U1)5U,       (U1)24U,      (U4)0x00000001U},         /*  PDAMSW    */
    {(U1)5U,       (U1)8U,       (U4)0x00000001U},         /*  SDGMSW    */
    {(U1)2U,       (U1)31U,      (U4)0x00000001U},         /*  USMMAIN   */
    {(U1)1U,       (U1)0U,       (U4)0x00000001U},         /*  TSR_MAIN  */
    {(U1)2U,       (U1)4U,       (U4)0x00000001U},         /*  ACCADPSW  */
    {(U1)2U,       (U1)3U,       (U4)0x00000001U},         /*  ACCROSSW  */
    {(U1)2U,       (U1)13U,      (U4)0x00000007U},         /*  ACCACLSW  */
    {(U1)2U,       (U1)22U,      (U4)0x00000003U},         /*  ACCSPSW1  */
    {(U1)2U,       (U1)20U,      (U4)0x00000003U},         /*  ACCSPSW2  */
    {(U1)2U,       (U1)5U,       (U4)0x00000001U},         /*  ACCRACSW  */
    {(U1)2U,       (U1)6U,       (U4)0x00000003U},         /*  ACCSSOSW  */
    {(U1)2U,       (U1)0U,       (U4)0x00000001U},         /*  ACCPROSW  */
    {(U1)2U,       (U1)10U,      (U4)0x00000007U},         /*  ACCSPMSW  */
    {(U1)2U,       (U1)8U,       (U4)0x00000001U},         /*  ACCGCRSW  */
    {(U1)2U,       (U1)16U,      (U4)0x00000003U},         /*  ERMSW     */
    {(U1)2U,       (U1)18U,      (U4)0x00000001U},         /*  CCSMDMSW  */
    {(U1)0U,       (U1)15U,      (U4)0x00000001U},         /*  SW_DEA01  */
    {(U1)1U,       (U1)14U,      (U4)0x00000003U},         /*  LDAMCUS   */
    {(U1)1U,       (U1)20U,      (U4)0x00000001U},         /*  FCMMSW    */
    {(U1)4U,       (U1)4U,       (U4)0x00000001U},         /*  LDALSMSW  */
    {(U1)1U,       (U1)16U,      (U4)0x00000007U},         /*  LDA_SFB   */
    {(U1)5U,       (U1)21U,      (U4)0x00000007U},         /*  LDAAMSW   */
    {(U1)0U,       (U1)2U,       (U4)0x00000001U},         /*  SW_LTC01  */
    {(U1)4U,       (U1)5U,       (U4)0x00000001U},         /*  LCASGMSW  */
    {(U1)5U,       (U1)2U,       (U4)0x00000003U},         /*  HOFDIOPE  */
    {(U1)5U,       (U1)7U,       (U4)0x00000001U},         /*  HOFCUS    */
    {(U1)5U,       (U1)6U,       (U4)0x00000001U},         /*  DRECSW    */
    {(U1)3U,       (U1)8U,       (U4)0x00000001U},         /*  DM_SW_AL  */
    {(U1)3U,       (U1)19U,      (U4)0x00000001U},         /*  DM_SW_DR  */
    {(U1)5U,       (U1)27U,      (U4)0x00000001U},         /*  DISSUISW  */
    {(U1)3U,       (U1)20U,      (U4)0x00000003U},         /*  PCSWDS1   */
    {(U1)5U,       (U1)28U,      (U4)0x00000007U},         /*  DM_SW_A2  */
    {(U1)5U,       (U1)0U,       (U4)0x00000001U},         /*  PCSMBSW   */
    {(U1)3U,       (U1)16U,      (U4)0x00000001U},         /*  RTWMSW    */
    {(U1)4U,       (U1)12U,      (U4)0x00000003U},         /*  IDASESW   */
    {(U1)3U,       (U1)9U,       (U4)0x00000001U},         /*  CTAMSW    */
    {(U1)3U,       (U1)22U,      (U4)0x00000003U},         /*  CTAWDS1   */
    {(U1)4U,       (U1)16U,      (U4)0x00000001U},         /*  BUZ_POS   */
    {(U1)4U,       (U1)21U,      (U4)0x00000007U},         /*  RSR_TIM   */
    {(U1)0U,       (U1)5U,       (U4)0x00000003U},         /*  BSMM_ILV  */
    {(U1)4U,       (U1)10U,      (U4)0x00000001U},         /*  BSD_SMSB  */
    {(U1)4U,       (U1)8U,       (U4)0x00000003U},         /*  BSD_SMSS  */
    {(U1)4U,       (U1)19U,      (U4)0x00000001U},         /*  DOAINDSW  */
    {(U1)4U,       (U1)30U,      (U4)0x00000003U},         /*  DOAM_TIM  */
    {(U1)18U,      (U1)8U,       (U4)0x00000001U},         /*  RSCSW_OP  */
    {(U1)5U,       (U1)9U,       (U4)0x00000001U},         /*  PMARSW    */
    {(U1)3U,       (U1)1U,       (U4)0x00000001U},         /*  LVNMSW    */
    {(U1)3U,       (U1)0U,       (U4)0x00000001U},         /*  TMNSMSW   */
    {(U1)3U,       (U1)13U,      (U4)0x00000007U},         /*  TMNVTMSW  */
    {(U1)5U,       (U1)18U,      (U4)0x00000007U},         /*  TMNVSW    */
    {(U1)0U,       (U1)17U,      (U4)0x00000003U},         /*  TSR_SNM   */
    {(U1)0U,       (U1)13U,      (U4)0x00000003U},         /*  SW_RSA01  */
    {(U1)0U,       (U1)21U,      (U4)0x00000003U},         /*  TSR_OSM   */
    {(U1)0U,       (U1)11U,      (U4)0x00000003U},         /*  TSR_OSL   */
    {(U1)31U,      (U1)31U,      (U4)0x00000001U},         /*  SPBZ_OPE  */
    {(U1)5U,       (U1)13U,      (U4)0x00000007U},         /*  RSA_NEM   */
    {(U1)5U,       (U1)10U,      (U4)0x00000007U},         /*  RSA_LSM   */
    {(U1)1U,       (U1)1U,       (U4)0x00000001U},         /*  SW_ITS04  */
    {(U1)1U,       (U1)26U,      (U4)0x00000001U},         /*  SW_ITS01  */
    {(U1)1U,       (U1)25U,      (U4)0x00000001U},         /*  SW_ITS02  */
    {(U1)1U,       (U1)31U,      (U4)0x00000001U},         /*  EMGONSW   */
    {(U1)1U,       (U1)27U,      (U4)0x00000001U},         /*  CACONSW   */
    {(U1)0U,       (U1)26U,      (U4)0x00000001U},         /*  ITSSETSW  */
    {(U1)4U,       (U1)25U,      (U4)0x00000001U},         /*  RTAN_MSW  */
    {(U1)4U,       (U1)26U,      (U4)0x00000003U},         /*  RTAN_TIM  */
    {(U1)5U,       (U1)1U,       (U4)0x00000001U},         /*  ADDS_MSW  */
    {(U1)14U,      (U1)9U,       (U4)0x00000001U},         /*  TRA_SW    */
    {(U1)2U,       (U1)1U,       (U4)0x00000003U},         /*  SLSSOSW   */
    {(U1)2U,       (U1)19U,      (U4)0x00000001U},         /*  AHSSWVSW  */
    {(U1)3U,       (U1)10U,      (U4)0x00000007U},         /*  AHSSDESW  */
    {(U1)2U,       (U1)9U,       (U4)0x00000001U},         /*  ADINMSW   */
    {(U1)15U,      (U1)16U,      (U4)0x0000000FU},         /*  TRLC_ID   */
    {(U1)15U,      (U1)8U,       (U4)0x00000007U},         /*  TRLC_AC   */
    {(U1)15U,      (U1)29U,      (U4)0x00000007U},         /*  TRLC_TY   */
    {(U1)9U,       (U1)4U,       (U4)0x00000001U},         /*  NR_MD_SW  */
    {(U1)9U,       (U1)3U,       (U4)0x00000001U},         /*  PW_MD_SW  */
    {(U1)9U,       (U1)5U,       (U4)0x00000001U},         /*  EC_MD_SW  */
    {(U1)9U,       (U1)6U,       (U4)0x00000001U},         /*  CS_MD_SW  */
    {(U1)8U,       (U1)28U,      (U4)0x00000001U},         /*  CH_MD_SW  */
    {(U1)8U,       (U1)26U,      (U4)0x00000001U},         /*  RG_MD_SW  */
    {(U1)8U,       (U1)27U,      (U4)0x00000001U},         /*  P1_MD_SW  */
    {(U1)8U,       (U1)4U,       (U4)0x00000001U},         /*  R1_MD_SW  */
    {(U1)8U,       (U1)3U,       (U4)0x00000001U},         /*  R2_MD_SW  */
    {(U1)8U,       (U1)2U,       (U4)0x00000001U},         /*  R3_MD_SW  */
    {(U1)8U,       (U1)1U,       (U4)0x00000001U},         /*  R4_MD_SW  */
    {(U1)8U,       (U1)0U,       (U4)0x00000001U},         /*  R5_MD_SW  */
    {(U1)8U,       (U1)12U,      (U4)0x00000001U},         /*  R6_MD_SW  */
    {(U1)8U,       (U1)23U,      (U4)0x00000001U},         /*  R7_MD_SW  */
    {(U1)8U,       (U1)19U,      (U4)0x00000001U},         /*  R8_MD_SW  */
    {(U1)8U,       (U1)25U,      (U4)0x00000001U}          /*  R9_MD_SW  */
};

const ST_GWMM_SIGCONF st_gp_GWMM_SIGCONF[GWMMCFG_SIG_NUM] = {
/*  u1_pwrsts                    u1_mm_msgsts_idx                u1_sigmax      u1_drvmd_idx                                 */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC07,        (U1)1U,        (U1)0xFFU},                    /*  SRPMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC10,        (U1)1U,        (U1)GATEWAY_MM_ACINV_SW},      /*  ACINV_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC07,        (U1)1U,        (U1)0xFFU},                    /*  MINTRSOF  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC07,        (U1)3U,        (U1)0xFFU},                    /*  SSMMODE   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)15U,       (U1)0xFFU},                    /*  TPINSEL   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)7U,        (U1)0xFFU},                    /*  TPINSELF  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)7U,        (U1)0xFFU},                    /*  TPINSELR  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)7U,        (U1)0xFFU},                    /*  TPUNTSET  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  SW_AS02   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  SW_AS01   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)3U,        (U1)0xFFU},                    /*  SW_AS05   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC14,        (U1)1U,        (U1)0xFFU},                    /*  TBCSW     */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC14,        (U1)1U,        (U1)0xFFU},                    /*  TBWSW     */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC06,        (U1)1U,        (U1)GATEWAY_MM_MRMRQSW},       /*  MRMRQSW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC06,        (U1)1U,        (U1)GATEWAY_MM_MRMRQBK},       /*  MRMRQBK   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  PCSMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  LDASW     */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)GATEWAY_MM_CSRM_SW},       /*  CSRMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  ICSMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)GATEWAY_MM_BSMM_SW},       /*  BSMMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  DOAM_SW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  RCTAMSW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  SW_RCD01  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  IDAMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  PDAMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  SDGMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  USMMAIN   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  TSR_MAIN  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  ACCADPSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  ACCROSSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)7U,        (U1)0xFFU},                    /*  ACCACLSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)3U,        (U1)0xFFU},                    /*  ACCSPSW1  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)3U,        (U1)0xFFU},                    /*  ACCSPSW2  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  ACCRACSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)3U,        (U1)0xFFU},                    /*  ACCSSOSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  ACCPROSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)7U,        (U1)0xFFU},                    /*  ACCSPMSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  ACCGCRSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)3U,        (U1)0xFFU},                    /*  ERMSW     */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  CCSMDMSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  SW_DEA01  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)3U,        (U1)0xFFU},                    /*  LDAMCUS   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  FCMMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  LDALSMSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)7U,        (U1)0xFFU},                    /*  LDA_SFB   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)7U,        (U1)0xFFU},                    /*  LDAAMSW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  SW_LTC01  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  LCASGMSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)3U,        (U1)GATEWAY_MM_HOFDIOPE},      /*  HOFDIOPE  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  HOFCUS    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  DRECSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  DM_SW_AL  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  DM_SW_DR  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  DISSUISW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)3U,        (U1)0xFFU},                    /*  PCSWDS1   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)7U,        (U1)0xFFU},                    /*  DM_SW_A2  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  PCSMBSW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  RTWMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)3U,        (U1)0xFFU},                    /*  IDASESW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  CTAMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)3U,        (U1)0xFFU},                    /*  CTAWDS1   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  BUZ_POS   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)7U,        (U1)0xFFU},                    /*  RSR_TIM   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)3U,        (U1)0xFFU},                    /*  BSMM_ILV  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  BSD_SMSB  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)3U,        (U1)0xFFU},                    /*  BSD_SMSS  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  DOAINDSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)3U,        (U1)0xFFU},                    /*  DOAM_TIM  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC10,        (U1)1U,        (U1)0xFFU},                    /*  RSCSW_OP  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  PMARSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  LVNMSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  TMNSMSW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)7U,        (U1)0xFFU},                    /*  TMNVTMSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)7U,        (U1)0xFFU},                    /*  TMNVSW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)3U,        (U1)0xFFU},                    /*  TSR_SNM   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)3U,        (U1)0xFFU},                    /*  SW_RSA01  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)3U,        (U1)0xFFU},                    /*  TSR_OSM   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)3U,        (U1)0xFFU},                    /*  TSR_OSL   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC16,        (U1)1U,        (U1)0xFFU},                    /*  SPBZ_OPE  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)7U,        (U1)0xFFU},                    /*  RSA_NEM   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)7U,        (U1)0xFFU},                    /*  RSA_LSM   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  SW_ITS04  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  SW_ITS01  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  SW_ITS02  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  EMGONSW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  CACONSW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC01,        (U1)1U,        (U1)0xFFU},                    /*  ITSSETSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  RTAN_MSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)3U,        (U1)0xFFU},                    /*  RTAN_TIM  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC03,        (U1)1U,        (U1)0xFFU},                    /*  ADDS_MSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC08,        (U1)1U,        (U1)0xFFU},                    /*  TRA_SW    */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)3U,        (U1)0xFFU},                    /*  SLSSOSW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  AHSSWVSW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)7U,        (U1)0xFFU},                    /*  AHSSDESW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC02,        (U1)1U,        (U1)0xFFU},                    /*  ADINMSW   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC08,        (U1)15U,       (U1)0xFFU},                    /*  TRLC_ID   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC08,        (U1)7U,        (U1)0xFFU},                    /*  TRLC_AC   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC08,        (U1)7U,        (U1)0xFFU},                    /*  TRLC_TY   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  NR_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  PW_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  EC_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  CS_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  CH_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)GATEWAY_MM_RG_MD_SW},      /*  RG_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  P1_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  R1_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  R2_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  R3_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  R4_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  R5_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  R6_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  R7_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU},                    /*  R8_MD_SW  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_AVNMC05,        (U1)1U,        (U1)0xFFU}                     /*  R9_MD_SW  */
};

const ST_GWMM_COMIF st_gp_GWMM_COMIF[GWMMCFG_SIG_NUM] = {
/*  fp_vd_send                          fp_u1_read                                        */
    {&vd_s_GwmmCfgSend_SRPMSW,          &u1_s_GwmmCfgRead_SRPMSW},          /*  SRPMSW    */
    {&vd_s_GwmmCfgSend_ACINV_SW,        &u1_s_GwmmCfgRead_ACINV_SW},        /*  ACINV_SW  */
    {&vd_s_GwmmCfgSend_MINTRSOF,        &u1_s_GwmmCfgRead_MINTRSOF},        /*  MINTRSOF  */
    {&vd_s_GwmmCfgSend_SSMMODE,         &u1_s_GwmmCfgRead_SSMMODE},         /*  SSMMODE   */
    {&vd_s_GwmmCfgSend_TPINSEL,         &u1_s_GwmmCfgRead_TPINSEL},         /*  TPINSEL   */
    {&vd_s_GwmmCfgSend_TPINSELF,        &u1_s_GwmmCfgRead_TPINSELF},        /*  TPINSELF  */
    {&vd_s_GwmmCfgSend_TPINSELR,        &u1_s_GwmmCfgRead_TPINSELR},        /*  TPINSELR  */
    {&vd_s_GwmmCfgSend_TPUNTSET,        &u1_s_GwmmCfgRead_TPUNTSET},        /*  TPUNTSET  */
    {&vd_s_GwmmCfgSend_SW_AS02,         &u1_s_GwmmCfgRead_SW_AS02},         /*  SW_AS02   */
    {&vd_s_GwmmCfgSend_SW_AS01,         &u1_s_GwmmCfgRead_SW_AS01},         /*  SW_AS01   */
    {&vd_s_GwmmCfgSend_SW_AS05,         &u1_s_GwmmCfgRead_SW_AS05},         /*  SW_AS05   */
    {&vd_s_GwmmCfgSend_TBCSW,           &u1_s_GwmmCfgRead_TBCSW},           /*  TBCSW     */
    {&vd_s_GwmmCfgSend_TBWSW,           &u1_s_GwmmCfgRead_TBWSW},           /*  TBWSW     */
    {&vd_s_GwmmCfgSend_MRMRQSW,         &u1_s_GwmmCfgRead_MRMRQSW},         /*  MRMRQSW   */
    {&vd_s_GwmmCfgSend_MRMRQBK,         &u1_s_GwmmCfgRead_MRMRQBK},         /*  MRMRQBK   */
    {&vd_s_GwmmCfgSend_PCSMSW,          &u1_s_GwmmCfgRead_PCSMSW},          /*  PCSMSW    */
    {&vd_s_GwmmCfgSend_LDASW,           &u1_s_GwmmCfgRead_LDASW},           /*  LDASW     */
    {&vd_s_GwmmCfgSend_CSRMSW,          &u1_s_GwmmCfgRead_CSRMSW},          /*  CSRMSW    */
    {&vd_s_GwmmCfgSend_ICSMSW,          &u1_s_GwmmCfgRead_ICSMSW},          /*  ICSMSW    */
    {&vd_s_GwmmCfgSend_BSMMSW,          &u1_s_GwmmCfgRead_BSMMSW},          /*  BSMMSW    */
    {&vd_s_GwmmCfgSend_DOAM_SW,         &u1_s_GwmmCfgRead_DOAM_SW},         /*  DOAM_SW   */
    {&vd_s_GwmmCfgSend_RCTAMSW,         &u1_s_GwmmCfgRead_RCTAMSW},         /*  RCTAMSW   */
    {&vd_s_GwmmCfgSend_SW_RCD01,        &u1_s_GwmmCfgRead_SW_RCD01},        /*  SW_RCD01  */
    {&vd_s_GwmmCfgSend_IDAMSW,          &u1_s_GwmmCfgRead_IDAMSW},          /*  IDAMSW    */
    {&vd_s_GwmmCfgSend_PDAMSW,          &u1_s_GwmmCfgRead_PDAMSW},          /*  PDAMSW    */
    {&vd_s_GwmmCfgSend_SDGMSW,          &u1_s_GwmmCfgRead_SDGMSW},          /*  SDGMSW    */
    {&vd_s_GwmmCfgSend_USMMAIN,         &u1_s_GwmmCfgRead_USMMAIN},         /*  USMMAIN   */
    {&vd_s_GwmmCfgSend_TSR_MAIN,        &u1_s_GwmmCfgRead_TSR_MAIN},        /*  TSR_MAIN  */
    {&vd_s_GwmmCfgSend_ACCADPSW,        &u1_s_GwmmCfgRead_ACCADPSW},        /*  ACCADPSW  */
    {&vd_s_GwmmCfgSend_ACCROSSW,        &u1_s_GwmmCfgRead_ACCROSSW},        /*  ACCROSSW  */
    {&vd_s_GwmmCfgSend_ACCACLSW,        &u1_s_GwmmCfgRead_ACCACLSW},        /*  ACCACLSW  */
    {&vd_s_GwmmCfgSend_ACCSPSW1,        &u1_s_GwmmCfgRead_ACCSPSW1},        /*  ACCSPSW1  */
    {&vd_s_GwmmCfgSend_ACCSPSW2,        &u1_s_GwmmCfgRead_ACCSPSW2},        /*  ACCSPSW2  */
    {&vd_s_GwmmCfgSend_ACCRACSW,        &u1_s_GwmmCfgRead_ACCRACSW},        /*  ACCRACSW  */
    {&vd_s_GwmmCfgSend_ACCSSOSW,        &u1_s_GwmmCfgRead_ACCSSOSW},        /*  ACCSSOSW  */
    {&vd_s_GwmmCfgSend_ACCPROSW,        &u1_s_GwmmCfgRead_ACCPROSW},        /*  ACCPROSW  */
    {&vd_s_GwmmCfgSend_ACCSPMSW,        &u1_s_GwmmCfgRead_ACCSPMSW},        /*  ACCSPMSW  */
    {&vd_s_GwmmCfgSend_ACCGCRSW,        &u1_s_GwmmCfgRead_ACCGCRSW},        /*  ACCGCRSW  */
    {&vd_s_GwmmCfgSend_ERMSW,           &u1_s_GwmmCfgRead_ERMSW},           /*  ERMSW     */
    {&vd_s_GwmmCfgSend_CCSMDMSW,        &u1_s_GwmmCfgRead_CCSMDMSW},        /*  CCSMDMSW  */
    {&vd_s_GwmmCfgSend_SW_DEA01,        &u1_s_GwmmCfgRead_SW_DEA01},        /*  SW_DEA01  */
    {&vd_s_GwmmCfgSend_LDAMCUS,         &u1_s_GwmmCfgRead_LDAMCUS},         /*  LDAMCUS   */
    {&vd_s_GwmmCfgSend_FCMMSW,          &u1_s_GwmmCfgRead_FCMMSW},          /*  FCMMSW    */
    {&vd_s_GwmmCfgSend_LDALSMSW,        &u1_s_GwmmCfgRead_LDALSMSW},        /*  LDALSMSW  */
    {&vd_s_GwmmCfgSend_LDA_SFB,         &u1_s_GwmmCfgRead_LDA_SFB},         /*  LDA_SFB   */
    {&vd_s_GwmmCfgSend_LDAAMSW,         &u1_s_GwmmCfgRead_LDAAMSW},         /*  LDAAMSW   */
    {&vd_s_GwmmCfgSend_SW_LTC01,        &u1_s_GwmmCfgRead_SW_LTC01},        /*  SW_LTC01  */
    {&vd_s_GwmmCfgSend_LCASGMSW,        &u1_s_GwmmCfgRead_LCASGMSW},        /*  LCASGMSW  */
    {&vd_s_GwmmCfgSend_HOFDIOPE,        &u1_s_GwmmCfgRead_HOFDIOPE},        /*  HOFDIOPE  */
    {&vd_s_GwmmCfgSend_HOFCUS,          &u1_s_GwmmCfgRead_HOFCUS},          /*  HOFCUS    */
    {&vd_s_GwmmCfgSend_DRECSW,          &u1_s_GwmmCfgRead_DRECSW},          /*  DRECSW    */
    {&vd_s_GwmmCfgSend_DM_SW_AL,        &u1_s_GwmmCfgRead_DM_SW_AL},        /*  DM_SW_AL  */
    {&vd_s_GwmmCfgSend_DM_SW_DR,        &u1_s_GwmmCfgRead_DM_SW_DR},        /*  DM_SW_DR  */
    {&vd_s_GwmmCfgSend_DISSUISW,        &u1_s_GwmmCfgRead_DISSUISW},        /*  DISSUISW  */
    {&vd_s_GwmmCfgSend_PCSWDS1,         &u1_s_GwmmCfgRead_PCSWDS1},         /*  PCSWDS1   */
    {&vd_s_GwmmCfgSend_DM_SW_A2,        &u1_s_GwmmCfgRead_DM_SW_A2},        /*  DM_SW_A2  */
    {&vd_s_GwmmCfgSend_PCSMBSW,         &u1_s_GwmmCfgRead_PCSMBSW},         /*  PCSMBSW   */
    {&vd_s_GwmmCfgSend_RTWMSW,          &u1_s_GwmmCfgRead_RTWMSW},          /*  RTWMSW    */
    {&vd_s_GwmmCfgSend_IDASESW,         &u1_s_GwmmCfgRead_IDASESW},         /*  IDASESW   */
    {&vd_s_GwmmCfgSend_CTAMSW,          &u1_s_GwmmCfgRead_CTAMSW},          /*  CTAMSW    */
    {&vd_s_GwmmCfgSend_CTAWDS1,         &u1_s_GwmmCfgRead_CTAWDS1},         /*  CTAWDS1   */
    {&vd_s_GwmmCfgSend_BUZ_POS,         &u1_s_GwmmCfgRead_BUZ_POS},         /*  BUZ_POS   */
    {&vd_s_GwmmCfgSend_RSR_TIM,         &u1_s_GwmmCfgRead_RSR_TIM},         /*  RSR_TIM   */
    {&vd_s_GwmmCfgSend_BSMM_ILV,        &u1_s_GwmmCfgRead_BSMM_ILV},        /*  BSMM_ILV  */
    {&vd_s_GwmmCfgSend_BSD_SMSB,        &u1_s_GwmmCfgRead_BSD_SMSB},        /*  BSD_SMSB  */
    {&vd_s_GwmmCfgSend_BSD_SMSS,        &u1_s_GwmmCfgRead_BSD_SMSS},        /*  BSD_SMSS  */
    {&vd_s_GwmmCfgSend_DOAINDSW,        &u1_s_GwmmCfgRead_DOAINDSW},        /*  DOAINDSW  */
    {&vd_s_GwmmCfgSend_DOAM_TIM,        &u1_s_GwmmCfgRead_DOAM_TIM},        /*  DOAM_TIM  */
    {&vd_s_GwmmCfgSend_RSCSW_OP,        &u1_s_GwmmCfgRead_RSCSW_OP},        /*  RSCSW_OP  */
    {&vd_s_GwmmCfgSend_PMARSW,          &u1_s_GwmmCfgRead_PMARSW},          /*  PMARSW    */
    {&vd_s_GwmmCfgSend_LVNMSW,          &u1_s_GwmmCfgRead_LVNMSW},          /*  LVNMSW    */
    {&vd_s_GwmmCfgSend_TMNSMSW,         &u1_s_GwmmCfgRead_TMNSMSW},         /*  TMNSMSW   */
    {&vd_s_GwmmCfgSend_TMNVTMSW,        &u1_s_GwmmCfgRead_TMNVTMSW},        /*  TMNVTMSW  */
    {&vd_s_GwmmCfgSend_TMNVSW,          &u1_s_GwmmCfgRead_TMNVSW},          /*  TMNVSW    */
    {&vd_s_GwmmCfgSend_TSR_SNM,         &u1_s_GwmmCfgRead_TSR_SNM},         /*  TSR_SNM   */
    {&vd_s_GwmmCfgSend_SW_RSA01,        &u1_s_GwmmCfgRead_SW_RSA01},        /*  SW_RSA01  */
    {&vd_s_GwmmCfgSend_TSR_OSM,         &u1_s_GwmmCfgRead_TSR_OSM},         /*  TSR_OSM   */
    {&vd_s_GwmmCfgSend_TSR_OSL,         &u1_s_GwmmCfgRead_TSR_OSL},         /*  TSR_OSL   */
    {&vd_s_GwmmCfgSend_SPBZ_OPE,        &u1_s_GwmmCfgRead_SPBZ_OPE},        /*  SPBZ_OPE  */
    {&vd_s_GwmmCfgSend_RSA_NEM,         &u1_s_GwmmCfgRead_RSA_NEM},         /*  RSA_NEM   */
    {&vd_s_GwmmCfgSend_RSA_LSM,         &u1_s_GwmmCfgRead_RSA_LSM},         /*  RSA_LSM   */
    {&vd_s_GwmmCfgSend_SW_ITS04,        &u1_s_GwmmCfgRead_SW_ITS04},        /*  SW_ITS04  */
    {&vd_s_GwmmCfgSend_SW_ITS01,        &u1_s_GwmmCfgRead_SW_ITS01},        /*  SW_ITS01  */
    {&vd_s_GwmmCfgSend_SW_ITS02,        &u1_s_GwmmCfgRead_SW_ITS02},        /*  SW_ITS02  */
    {&vd_s_GwmmCfgSend_EMGONSW,         &u1_s_GwmmCfgRead_EMGONSW},         /*  EMGONSW   */
    {&vd_s_GwmmCfgSend_CACONSW,         &u1_s_GwmmCfgRead_CACONSW},         /*  CACONSW   */
    {&vd_s_GwmmCfgSend_ITSSETSW,        &u1_s_GwmmCfgRead_ITSSETSW},        /*  ITSSETSW  */
    {&vd_s_GwmmCfgSend_RTAN_MSW,        &u1_s_GwmmCfgRead_RTAN_MSW},        /*  RTAN_MSW  */
    {&vd_s_GwmmCfgSend_RTAN_TIM,        &u1_s_GwmmCfgRead_RTAN_TIM},        /*  RTAN_TIM  */
    {&vd_s_GwmmCfgSend_ADDS_MSW,        &u1_s_GwmmCfgRead_ADDS_MSW},        /*  ADDS_MSW  */
    {&vd_s_GwmmCfgSend_TRA_SW,          &u1_s_GwmmCfgRead_TRA_SW},          /*  TRA_SW    */
    {&vd_s_GwmmCfgSend_SLSSOSW,         &u1_s_GwmmCfgRead_SLSSOSW},         /*  SLSSOSW   */
    {&vd_s_GwmmCfgSend_AHSSWVSW,        &u1_s_GwmmCfgRead_AHSSWVSW},        /*  AHSSWVSW  */
    {&vd_s_GwmmCfgSend_AHSSDESW,        &u1_s_GwmmCfgRead_AHSSDESW},        /*  AHSSDESW  */
    {&vd_s_GwmmCfgSend_ADINMSW,         &u1_s_GwmmCfgRead_ADINMSW},         /*  ADINMSW   */
    {&vd_s_GwmmCfgSend_TRLC_ID,         &u1_s_GwmmCfgRead_TRLC_ID},         /*  TRLC_ID   */
    {&vd_s_GwmmCfgSend_TRLC_AC,         &u1_s_GwmmCfgRead_TRLC_AC},         /*  TRLC_AC   */
    {&vd_s_GwmmCfgSend_TRLC_TY,         &u1_s_GwmmCfgRead_TRLC_TY},         /*  TRLC_TY   */
    {&vd_s_GwmmCfgSend_NR_MD_SW,        &u1_s_GwmmCfgRead_NR_MD_SW},        /*  NR_MD_SW  */
    {&vd_s_GwmmCfgSend_PW_MD_SW,        &u1_s_GwmmCfgRead_PW_MD_SW},        /*  PW_MD_SW  */
    {&vd_s_GwmmCfgSend_EC_MD_SW,        &u1_s_GwmmCfgRead_EC_MD_SW},        /*  EC_MD_SW  */
    {&vd_s_GwmmCfgSend_CS_MD_SW,        &u1_s_GwmmCfgRead_CS_MD_SW},        /*  CS_MD_SW  */
    {&vd_s_GwmmCfgSend_CH_MD_SW,        &u1_s_GwmmCfgRead_CH_MD_SW},        /*  CH_MD_SW  */
    {&vd_s_GwmmCfgSend_RG_MD_SW,        &u1_s_GwmmCfgRead_RG_MD_SW},        /*  RG_MD_SW  */
    {&vd_s_GwmmCfgSend_P1_MD_SW,        &u1_s_GwmmCfgRead_P1_MD_SW},        /*  P1_MD_SW  */
    {&vd_s_GwmmCfgSend_R1_MD_SW,        &u1_s_GwmmCfgRead_R1_MD_SW},        /*  R1_MD_SW  */
    {&vd_s_GwmmCfgSend_R2_MD_SW,        &u1_s_GwmmCfgRead_R2_MD_SW},        /*  R2_MD_SW  */
    {&vd_s_GwmmCfgSend_R3_MD_SW,        &u1_s_GwmmCfgRead_R3_MD_SW},        /*  R3_MD_SW  */
    {&vd_s_GwmmCfgSend_R4_MD_SW,        &u1_s_GwmmCfgRead_R4_MD_SW},        /*  R4_MD_SW  */
    {&vd_s_GwmmCfgSend_R5_MD_SW,        &u1_s_GwmmCfgRead_R5_MD_SW},        /*  R5_MD_SW  */
    {&vd_s_GwmmCfgSend_R6_MD_SW,        &u1_s_GwmmCfgRead_R6_MD_SW},        /*  R6_MD_SW  */
    {&vd_s_GwmmCfgSend_R7_MD_SW,        &u1_s_GwmmCfgRead_R7_MD_SW},        /*  R7_MD_SW  */
    {&vd_s_GwmmCfgSend_R8_MD_SW,        &u1_s_GwmmCfgRead_R8_MD_SW},        /*  R8_MD_SW  */
    {&vd_s_GwmmCfgSend_R9_MD_SW,        &u1_s_GwmmCfgRead_R9_MD_SW}         /*  R9_MD_SW  */
};

const U1 u1_gp_GWMM_DRVMDPWCONF[GATEWAY_MM_DRVMD_NUM] = {
    (U1)GWMM_PWRSTS_IGR,                                                        /*  BBMS SW                  */
    (U1)GWMM_PWRSTS_IGR,                                                        /*  CSRM SW                  */
    (U1)GWMM_PWRSTS_IGR,                                                        /*  ACINV SW                 */
    (U1)GWMM_PWRSTS_IGR,                                                        /*  HOFDIOPE                 */
    (U1)GWMM_PWRSTS_IGR,                                                        /*  RG_MD_SW                 */
    (U1)GWMM_PWRSTS_IGR,                                                        /*  MRMRQSW                  */
    (U1)GWMM_PWRSTS_IGR                                                         /*  MRMRQBK                  */
};

static const U2 u2_sp_GWMMCFG_CANRXMSG[GWMMCFG_MSG_MM_NUM] = {
    (U2)MSG_AVNMC01_RXCH1,                       /*  AVNMC01                  */
    (U2)MSG_AVNMC02_RXCH1,                       /*  AVNMC02                  */
    (U2)MSG_AVNMC03_RXCH1,                       /*  AVNMC03                  */
    (U2)MSG_AVNMC04_RXCH1,                       /*  AVNMC04                  */
    (U2)MSG_AVNMC05_RXCH1,                       /*  AVNMC05                  */
    (U2)MSG_AVNMC06_RXCH1,                       /*  AVNMC06                  */
    (U2)MSG_AVNMC07_RXCH1,                       /*  AVNMC07                  */
    (U2)MSG_AVNMC08_RXCH1,                       /*  AVNMC08                  */
    (U2)MSG_AVNMC09_RXCH1,                       /*  AVNMC09                  */
    (U2)MSG_AVNMC10_RXCH1,                       /*  AVNMC10                  */
    (U2)MSG_AVNMC11_RXCH1,                       /*  AVNMC11                  */
    (U2)MSG_AVNMC12_RXCH1,                       /*  AVNMC12                  */
    (U2)MSG_AVNMC13_RXCH1,                       /*  AVNMC13                  */
    (U2)MSG_AVNMC14_RXCH1,                       /*  AVNMC14                  */
    (U2)MSG_AVNMC15_RXCH1,                       /*  AVNMC15                  */
    (U2)MSG_AVNMC16_RXCH1,                       /*  AVNMC16                  */
    (U2)MSG_AVNMC17_RXCH1                        /*  AVNMC17                  */
};

const ST_GWMM_MSGCOMVERT st_gp_GWMM_TMM_MSGCOMVERT[GWMMCFG_TMM_SIG_NUM] = {
/*  u1_idx         u1_bit        u4_mask                                   */
    {(U1)0U,       (U1)24U,      (U4)0x0000000FU},         /*  L_TBCAK_ID  */
    {(U1)1U,       (U1)5U,       (U4)0x00000007U},         /*  L_TBCAK_TY  */
    {(U1)1U,       (U1)4U,       (U4)0x00000001U}          /*  L_TBC_SF    */
};

const ST_GWMM_SIGCONF st_gp_GWMM_TMM_SIGCONF[GWMMCFG_TMM_SIG_NUM] = {
/*  u1_pwrsts                    u1_mm_msgsts_idx                u1_sigmax      u1_drvmd_idx                                   */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_TBC1S01,        (U1)15U,       (U1)0xFFU},                    /*  L_TBCAK_ID  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_TBC1S01,        (U1)7U,        (U1)0xFFU},                    /*  L_TBCAK_TY  */
    {(U1)GWMM_PWRSTS_IGR,        (U1)GWMMCFG_MSG_TBC1S01,        (U1)1U,        (U1)0xFFU}                     /*  L_TBC_SF    */
};

const ST_GWMM_COMIF st_gp_GWMM_TMM_COMIF[GWMMCFG_TMM_SIG_NUM] = {
/*  fp_vd_send                          fp_u1_read                                          */
    {&vd_s_GwmmCfgSend_L_TBCAK_ID,      &u1_s_GwmmCfgRead_L_TBCAK_ID},      /*  L_TBCAK_ID  */
    {&vd_s_GwmmCfgSend_L_TBCAK_TY,      &u1_s_GwmmCfgRead_L_TBCAK_TY},      /*  L_TBCAK_TY  */
    {&vd_s_GwmmCfgSend_L_TBC_SF,        &u1_s_GwmmCfgRead_L_TBC_SF}         /*  L_TBC_SF    */
};

static const ST_GWMM_RXMSG st_sp_GWMMCFG_TMM_CANRXMSG[GWMMCFG_TMM_MSG_MM_NUM] = {
#ifdef MSG_TBC1S01_RXCH0
    {(U2)OXCAN_PDU_RX_CAN_TBC1S01,      (U2)(3600U/OXCAN_MAIN_TICK)}    /*  TBC1S01                  */
#else
    {(U2)0xFFFFU,                       (U2)(3600U/OXCAN_MAIN_TICK)}    /*  TBC1S01                  */
#endif
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void vd_g_GwmmCfgPreTask(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_GwmmCfgPreTask(void)
{
    U1 u1_tp_msgbuf[GWMMCFG_MSGBYTESIZE];       /* Can Message Buffer */
    U1 u1_t_msgsts;                             /* Can Message Stats  */
    U1 u1_t_bufidx;                             /* Buffer Index       */
    U2 u2_t_msgid;                              /* Can Message ID     */
    U4 u4_t_lpcnt;                              /* Loop Counter       */
    U4 u4_t_data;                               /* Can Receive Data   */

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)GWMMCFG_MSG_MM_NUM; u4_t_lpcnt++){
        u2_t_msgid = u2_sp_GWMMCFG_CANRXMSG[u4_t_lpcnt];
#if 0   /* BEV BSW provisionally */
        u1_t_msgsts  = (U1)Com_GetIPDUStatus((PduIdType)u2_t_msgid);
        u1_t_msgsts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
        u1_t_msgsts = ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#endif
        if(u1_t_msgsts == (U1)0U){
            u1_t_bufidx = (U1)(u4_t_lpcnt * (U4)GWMMCFG_MSGBUF_LSB);
            (void)Com_ReadIPDU((PduIdType)u2_t_msgid, &u1_tp_msgbuf[0]);
            u4_t_data = u4_s_GwmmCfgGetBufData(&u1_tp_msgbuf[0]);
            vd_g_GatewaymmDataPut(u1_t_bufidx, u4_t_data);                                 /* Send receive data(1-4byte)       */
            u4_t_data = u4_s_GwmmCfgGetBufData(&u1_tp_msgbuf[GWMMCFG_MSGBUF_DATASIZE]);
            vd_g_GatewaymmDataPut(u1_t_bufidx + (U1)1U, u4_t_data);                        /* Send receive data(5-8byte)       */
        }
    }
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)GWMMCFG_TMM_MSG_MM_NUM; u4_t_lpcnt++){
#ifdef MSG_TBC1S01_RXCH0
        u2_t_msgid = st_sp_GWMMCFG_TMM_CANRXMSG[u4_t_lpcnt].u2_msgid;
        u1_t_msgsts  = u1_g_oXCANRxStat(u2_t_msgid, (U2)(OXCAN_RX_SYS_NRX_IGR | OXCAN_RX_SYS_TOE_IGR),
                                        st_sp_GWMMCFG_TMM_CANRXMSG[u4_t_lpcnt].u2_failtim) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        if(u1_t_msgsts == (U1)0U){
            u1_t_bufidx = (U1)(u4_t_lpcnt * (U4)GWMMCFG_MSGBUF_LSB);
            (void)Com_ReadIPDU((PduIdType)u2_t_msgid, &u1_tp_msgbuf[0]);
            u4_t_data = u4_s_GwmmCfgGetBufData(&u1_tp_msgbuf[0]);
            vd_g_GatewaymmTMMDataPut(u1_t_bufidx, u4_t_data);                                 /* Send receive data(1-4byte)       */
            u4_t_data = u4_s_GwmmCfgGetBufData(&u1_tp_msgbuf[GWMMCFG_MSGBUF_DATASIZE]);
            vd_g_GatewaymmTMMDataPut(u1_t_bufidx + (U1)1U, u4_t_data);                        /* Send receive data(5-8byte)       */
        }
        else if((U1)(u1_t_msgsts & (U1)COM_TIMEOUT) != (U1)0U){
            u1_t_bufidx = (U1)(u4_t_lpcnt * (U4)GWMMCFG_MSGBUF_LSB);
            vd_g_GatewaymmTMMDataPut(u1_t_bufidx, (U4)0x00000000U);                           /* Send receive data(1-4byte)       */
            vd_g_GatewaymmTMMDataPut(u1_t_bufidx + (U1)1U, (U4)0x00000000U);                  /* Send receive data(5-8byte)       */
        }
        else{
            /* Do Nothing */
        }
#endif
    }
}
/*===================================================================================================================================*/
/*  static U4 u4_s_GwmmCfgGetBufData(const U1 *u1_ap_MSGBUF)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      *u1_ap_MSGBUF : CAN Message Buffer                                                                               */
/*  Return:         u4_t_data     : Buffer Data                                                                                      */
/*===================================================================================================================================*/
static U4 u4_s_GwmmCfgGetBufData(const U1 *u1_ap_MSGBUF)
{
    U4 u4_t_lpcnt;                              /* Loop Counter       */
    U4 u4_t_data;                               /* Can Receive Data   */

    u4_t_data = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)GWMMCFG_MSGBUF_DATASIZE; u4_t_lpcnt++){
        u4_t_data |= (U4)u1_ap_MSGBUF[u4_t_lpcnt] << ((U4)GWMMCFG_1BYTE_SHIFT * u4_t_lpcnt);
    }
    
    return(u4_t_data);
}

/*===================================================================================================================================*/
/*  U1 u1_g_GwmmCfgGetMMGTWEsOpt(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_ret : TRUE/FALSE                                                                                            */
/*===================================================================================================================================*/
U1 u1_g_GwmmCfgGetMMGTWEsOpt(void)
{
    U1  u1_t_ret;       /* Result            */

    u1_t_ret = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  void vd_g_GwmmCfgSend_MMCKPT(const U1 u1_a_pwrsts)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_pwrsts : Power Status                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_GwmmCfgSend_MMCKPT(const U1 u1_a_pwrsts)
{
    U1    u1_t_varsup;
    U1    u1_t_rcvsig;
    U1    u1_t_pwrsts_jdg;
    
#if 0   /* BEV BSW provisionally */
#else
    u1_t_rcvsig = (U1)0U;
#endif
    u1_t_varsup = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AISMM);
    u1_t_pwrsts_jdg = u1_a_pwrsts & (U1)GWMM_PWRSTS_IGR;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MMCKPT, &u1_t_rcvsig);
    
    if((u1_t_pwrsts_jdg != (U1)0U) &&
       (u1_t_varsup <= (U1)GWMMCFG_MMCKPT_SIGMAX) &&
       (u1_t_varsup != u1_t_rcvsig)){
        (void)Com_SendSignal(ComConf_ComSignal_MMCKPT, &u1_t_varsup);
    }
}
/*===================================================================================================================================*/
/*  void vd_g_GwmmCfgSend_L_TBC_FUNC(const U1 u1_a_pwrsts)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_pwrsts : Power Status                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_GwmmCfgSend_L_TBC_FUNC(const U1 u1_a_pwrsts)
{
    U1    u1_t_varsup;
    U1    u1_t_rcvsig;
    U1    u1_t_pwrsts_jdg;
    
#if 0   /* BEV BSW provisionally */
#else
    u1_t_rcvsig = (U1)0U;
#endif
    u1_t_varsup = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_SW_TBC);
    u1_t_pwrsts_jdg = u1_a_pwrsts & (U1)GWMM_PWRSTS_IGR;
    (void)Com_ReceiveSignal(ComConf_ComSignal_L_TBC_FUNC, &u1_t_rcvsig);
    
    if((u1_t_pwrsts_jdg != (U1)0U) &&
       (u1_t_varsup <= (U1)GWMMCFG_L_TBC_FUNC_SIGMAX) &&
       (u1_t_varsup != u1_t_rcvsig)){
        (void)Com_SendSignal(ComConf_ComSignal_L_TBC_FUNC, &u1_t_varsup);
    }
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SRPMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SRPMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SRPMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SRPMSW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
#endif /* ComConf_ComSignal_SRPMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACINV_SW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACINV_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACINV_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACINV_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACINV_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_MINTRSOF(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_MINTRSOF(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_MINTRSOF
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_MINTRSOF, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
#endif /* ComConf_ComSignal_MINTRSOF */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SSMMODE(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SSMMODE(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SSMMODE
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SSMMODE, &u1_t_sig);
#endif /* ComConf_ComSignal_SSMMODE */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TPINSEL(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TPINSEL(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TPINSEL
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TPINSEL, &u1_t_sig);
#endif /* ComConf_ComSignal_TPINSEL */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TPINSELF(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TPINSELF(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TPINSELF
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TPINSELF, &u1_t_sig);
#endif /* ComConf_ComSignal_TPINSELF */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TPINSELR(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TPINSELR(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TPINSELR
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TPINSELR, &u1_t_sig);
#endif /* ComConf_ComSignal_TPINSELR */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TPUNTSET(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TPUNTSET(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TPUNTSET
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TPUNTSET, &u1_t_sig);
#endif /* ComConf_ComSignal_TPUNTSET */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SW_AS02(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SW_AS02(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SW_AS02
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SW_AS02, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_AS02 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SW_AS01(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SW_AS01(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SW_AS01
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SW_AS01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_AS01 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SW_AS05(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SW_AS05(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SW_AS05
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SW_AS05, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_AS05 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TBCSW(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TBCSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TBCSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TBCSW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
#endif /* ComConf_ComSignal_TBCSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TBWSW(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TBWSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TBWSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TBWSW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
#endif /* ComConf_ComSignal_TBWSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_MRMRQSW(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_MRMRQSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_MRMRQSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_MRMRQSW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
#endif /* ComConf_ComSignal_MRMRQSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_MRMRQBK(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_MRMRQBK(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_MRMRQBK
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_MRMRQBK, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
#endif /* ComConf_ComSignal_MRMRQBK */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_PCSMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_PCSMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_PCSMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_PCSMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_PCSMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_LDASW(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_LDASW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_LDASW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_LDASW, &u1_t_sig);
#endif /* ComConf_ComSignal_LDASW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_CSRMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_CSRMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_CSRMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_CSRMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_CSRMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ICSMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ICSMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ICSMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ICSMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ICSMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_BSMMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_BSMMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_BSMMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_BSMMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_BSMMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_DOAM_SW(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_DOAM_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_DOAM_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_DOAM_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_DOAM_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_RCTAMSW(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_RCTAMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_RCTAMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_RCTAMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_RCTAMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SW_RCD01(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SW_RCD01(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SW_RCD01
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SW_RCD01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_RCD01 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_IDAMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_IDAMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_IDAMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_IDAMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_IDAMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TSR_MAIN(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TSR_MAIN(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TSR_MAIN
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TSR_MAIN, &u1_t_sig);
#endif /* ComConf_ComSignal_TSR_MAIN */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACCADPSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACCADPSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACCADPSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACCADPSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCADPSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACCROSSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACCROSSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACCROSSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACCROSSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCROSSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACCACLSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACCACLSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACCACLSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACCACLSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCACLSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACCSPSW1(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACCSPSW1(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACCSPSW1
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACCSPSW1, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCSPSW1 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACCSPSW2(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACCSPSW2(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACCSPSW2
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACCSPSW2, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCSPSW2 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACCRACSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACCRACSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACCRACSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACCRACSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCRACSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACCSSOSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACCSSOSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACCSSOSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACCSSOSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCSSOSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACCPROSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACCPROSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACCPROSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACCPROSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCPROSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACCSPMSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACCSPMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACCSPMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACCSPMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCSPMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ACCGCRSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ACCGCRSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ACCGCRSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ACCGCRSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCGCRSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ERMSW(const U1 u1_a_SIG)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ERMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ERMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ERMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ERMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_CCSMDMSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_CCSMDMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_CCSMDMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_CCSMDMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_CCSMDMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SW_DEA01(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SW_DEA01(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SW_DEA01
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SW_DEA01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_DEA01 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_LDAMCUS(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_LDAMCUS(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_LDAMCUS
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_LDAMCUS, &u1_t_sig);
#endif /* ComConf_ComSignal_LDAMCUS */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_FCMMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_FCMMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_FCMMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_FCMMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_FCMMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_LDALSMSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_LDALSMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_LDALSMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_LDALSMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_LDALSMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_LDA_SFB(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_LDA_SFB(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_LDA_SFB
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_LDA_SFB, &u1_t_sig);
#endif /* ComConf_ComSignal_LDA_SFB */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_LDAAMSW(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_LDAAMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_LDAAMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_LDAAMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_LDAAMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SW_LTC01(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SW_LTC01(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SW_LTC01
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SW_LTC01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_LTC01 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_LCASGMSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_LCASGMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_LCASGMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_LCASGMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_LCASGMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_DISSUISW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_DISSUISW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_DISSUISW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_DISSUISW, &u1_t_sig);
#endif /* ComConf_ComSignal_DISSUISW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_PCSWDS1(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_PCSWDS1(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_PCSWDS1
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_PCSWDS1, &u1_t_sig);
#endif /* ComConf_ComSignal_PCSWDS1 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_DM_SW_A2(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_DM_SW_A2(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_DM_SW_A2
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_DM_SW_A2, &u1_t_sig);
#endif /* ComConf_ComSignal_DM_SW_A2 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_PCSMBSW(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_PCSMBSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_PCSMBSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_PCSMBSW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_MET1S10_TXCH0);
#endif /* ComConf_ComSignal_PCSMBSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_IDASESW(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_IDASESW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_IDASESW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_IDASESW, &u1_t_sig);
#endif /* ComConf_ComSignal_IDASESW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_CTAMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_CTAMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_CTAMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_CTAMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_CTAMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_CTAWDS1(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_CTAWDS1(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_CTAWDS1
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_CTAWDS1, &u1_t_sig);
#endif /* ComConf_ComSignal_CTAWDS1 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_BUZ_POS(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_BUZ_POS(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_BUZ_POS
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_BUZ_POS, &u1_t_sig);
#endif /* ComConf_ComSignal_BUZ_POS */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_RSR_TIM(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_RSR_TIM(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_RSR_TIM
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_RSR_TIM, &u1_t_sig);
#endif /* ComConf_ComSignal_RSR_TIM */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_BSMM_ILV(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_BSMM_ILV(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_BSMM_ILV
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_BSMM_ILV, &u1_t_sig);
#endif /* ComConf_ComSignal_BSMM_ILV */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_DOAINDSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_DOAINDSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_DOAINDSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_DOAINDSW, &u1_t_sig);
#endif /* ComConf_ComSignal_DOAINDSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_DOAM_TIM(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_DOAM_TIM(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_DOAM_TIM
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_DOAM_TIM, &u1_t_sig);
#endif /* ComConf_ComSignal_DOAM_TIM */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_RSCSW_OP(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_RSCSW_OP(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_RSCSW_OP
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_RSCSW_OP, &u1_t_sig);
#endif /* ComConf_ComSignal_RSCSW_OP */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_PMARSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_PMARSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_PMARSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_PMARSW, &u1_t_sig);
#endif /* ComConf_ComSignal_PMARSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_LVNMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_LVNMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_LVNMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_LVNMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_LVNMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TMNSMSW(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TMNSMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TMNSMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TMNSMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_TMNSMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TMNVTMSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TMNVTMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TMNVTMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TMNVTMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_TMNVTMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TMNVSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TMNVSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TMNVSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TMNVSW, &u1_t_sig);
#endif /* ComConf_ComSignal_TMNVSW */
}
/*===================================================================================================================================*/
/*  void        vd_g_GwmmCfgSend_TMNSSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void        vd_g_GwmmCfgSend_TMNSSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TMNSSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TMNSSW, &u1_t_sig);
#endif /* ComConf_ComSignal_TMNSSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TSR_SNM(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TSR_SNM(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TSR_SNM
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TSR_SNM, &u1_t_sig);
#endif /* ComConf_ComSignal_TSR_SNM */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SW_RSA01(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SW_RSA01(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SW_RSA01
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SW_RSA01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_RSA01 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TSR_OSM(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TSR_OSM(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TSR_OSM
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TSR_OSM, &u1_t_sig);
#endif /* ComConf_ComSignal_TSR_OSM */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TSR_OSL(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TSR_OSL(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TSR_OSL
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TSR_OSL, &u1_t_sig);
#endif /* ComConf_ComSignal_TSR_OSL */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_RSA_NEM(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_RSA_NEM(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_RSA_NEM
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_RSA_NEM, &u1_t_sig);
#endif /* ComConf_ComSignal_RSA_NEM */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_RSA_LSM(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_RSA_LSM(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_RSA_LSM
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_RSA_LSM, &u1_t_sig);
#endif /* ComConf_ComSignal_RSA_LSM */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SW_ITS04(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SW_ITS04(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SW_ITS04
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SW_ITS04, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_ITS04 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SW_ITS01(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SW_ITS01(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SW_ITS01
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SW_ITS01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_ITS01 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SW_ITS02(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SW_ITS02(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SW_ITS02
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SW_ITS02, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_ITS02 */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_EMGONSW(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_EMGONSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_EMGONSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_EMGONSW, &u1_t_sig);
#endif /* ComConf_ComSignal_EMGONSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_CACONSW(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_CACONSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_CACONSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_CACONSW, &u1_t_sig);
#endif /* ComConf_ComSignal_CACONSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ITSSETSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ITSSETSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ITSSETSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ITSSETSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ITSSETSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TRA_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TRA_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TRA_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TRA_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_TRA_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SLSSOSW(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SLSSOSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SLSSOSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SLSSOSW, &u1_t_sig);
#endif /* ComConf_ComSignal_SLSSOSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_AHSSWVSW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_AHSSWVSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_AHSSWVSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_AHSSWVSW, &u1_t_sig);
#endif /* ComConf_ComSignal_AHSSWVSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_AHSSDESW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_AHSSDESW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_AHSSDESW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_AHSSDESW, &u1_t_sig);
#endif /* ComConf_ComSignal_AHSSDESW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ADINMSW(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ADINMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ADINMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ADINMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ADINMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TRLC_ID(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TRLC_ID(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TRLC_ID
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TRLC_ID, &u1_t_sig);
#endif /* ComConf_ComSignal_TRLC_ID */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TRLC_AC(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TRLC_AC(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TRLC_AC
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TRLC_AC, &u1_t_sig);
#endif /* ComConf_ComSignal_TRLC_AC */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_TRLC_TY(const U1 u1_a_SIG)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_TRLC_TY(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_TRLC_TY
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_TRLC_TY, &u1_t_sig);
#endif /* ComConf_ComSignal_TRLC_TY */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_NR_MD_SW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_NR_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_NR_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_NR_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_NR_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_PW_MD_SW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_PW_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_PW_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_PW_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_PW_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_EC_MD_SW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_EC_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_EC_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_EC_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_EC_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_CS_MD_SW(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_CS_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_CS_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_CS_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_CS_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_PDAMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_PDAMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_PDAMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_PDAMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_PDAMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SDGMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SDGMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SDGMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SDGMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_SDGMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_USMMAIN(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_USMMAIN(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_USMMAIN
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_USMMAIN, &u1_t_sig);
#endif /* ComConf_ComSignal_USMMAIN */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_HOFDIOPE(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_HOFDIOPE(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_HOFDIOPE
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_HOFDIOPE, &u1_t_sig);
#endif /* ComConf_ComSignal_HOFDIOPE */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_HOFCUS(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_HOFCUS(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_HOFCUS
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_HOFCUS, &u1_t_sig);
#endif /* ComConf_ComSignal_HOFCUS */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_DRECSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_DRECSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_DRECSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_DRECSW, &u1_t_sig);
#endif /* ComConf_ComSignal_DRECSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_DM_SW_AL(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_DM_SW_AL(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_DM_SW_AL
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_DM_SW_AL, &u1_t_sig);
#endif /* ComConf_ComSignal_DM_SW_AL */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_DM_SW_DR(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_DM_SW_DR(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_DM_SW_DR
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_DM_SW_DR, &u1_t_sig);
#endif /* ComConf_ComSignal_DM_SW_DR */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_RTWMSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_RTWMSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_RTWMSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_RTWMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_RTWMSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_BSD_SMSB(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_BSD_SMSB(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_BSD_SMSB
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_BSD_SMSB, &u1_t_sig);
#endif /* ComConf_ComSignal_BSD_SMSB */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_BSD_SMSS(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_BSD_SMSS(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_BSD_SMSS
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_BSD_SMSS, &u1_t_sig);
#endif /* ComConf_ComSignal_BSD_SMSS */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_SPBZ_OPE(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_SPBZ_OPE(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_SPBZ_OPE
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_SPBZ_OPE, &u1_t_sig);
#endif /* ComConf_ComSignal_SPBZ_OPE */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_RTAN_MSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_RTAN_MSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_RTAN_MSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_RTAN_MSW, &u1_t_sig);
#endif /* ComConf_ComSignal_RTAN_MSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_RTAN_TIM(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_RTAN_TIM(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_RTAN_TIM
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_RTAN_TIM, &u1_t_sig);
#endif /* ComConf_ComSignal_RTAN_TIM */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_ADDS_MSW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_ADDS_MSW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_ADDS_MSW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_ADDS_MSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ADDS_MSW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_CH_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_CH_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_CH_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_CH_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_CH_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_RG_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_RG_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_RG_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_RG_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_RG_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_P1_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_P1_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_P1_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_P1_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_P1_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_R1_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_R1_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_R1_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_R1_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_R1_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_R2_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_R2_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_R2_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_R2_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_R2_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_R3_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_R3_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_R3_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_R3_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_R3_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_R4_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_R4_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_R4_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_R4_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_R4_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_R5_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_R5_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_R5_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_R5_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_R5_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_R6_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_R6_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_R6_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_R6_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_R6_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_R7_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_R7_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_R7_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_R7_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_R7_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_R8_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_R8_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_R8_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_R8_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_R8_MD_SW */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_R9_MD_SW(const U1 u1_a_SIG)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_R9_MD_SW(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_R9_MD_SW
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_R9_MD_SW, &u1_t_sig);
    (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
#endif /* ComConf_ComSignal_R9_MD_SW */
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SRPMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SRPMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SRPMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_SRPMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_SRPMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACINV_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACINV_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACINV_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACINV_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACINV_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_MINTRSOF(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_MINTRSOF(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_MINTRSOF
    (void)Com_ReceiveSignal(ComConf_ComSignal_MINTRSOF, &u1_t_sig);
#endif /* ComConf_ComSignal_MINTRSOF */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SSMMODE(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SSMMODE(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SSMMODE
    (void)Com_ReceiveSignal(ComConf_ComSignal_SSMMODE, &u1_t_sig);
#endif /* ComConf_ComSignal_SSMMODE */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TPINSEL(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TPINSEL(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TPINSEL
    (void)Com_ReceiveSignal(ComConf_ComSignal_TPINSEL, &u1_t_sig);
#endif /* ComConf_ComSignal_TPINSEL */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TPINSELF(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TPINSELF(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TPINSELF
    (void)Com_ReceiveSignal(ComConf_ComSignal_TPINSELF, &u1_t_sig);
#endif /* ComConf_ComSignal_TPINSELF */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TPINSELR(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TPINSELR(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TPINSELR
    (void)Com_ReceiveSignal(ComConf_ComSignal_TPINSELR, &u1_t_sig);
#endif /* ComConf_ComSignal_TPINSELR */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TPUNTSET(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TPUNTSET(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TPUNTSET
    (void)Com_ReceiveSignal(ComConf_ComSignal_TPUNTSET, &u1_t_sig);
#endif /* ComConf_ComSignal_TPUNTSET */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SW_AS02(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SW_AS02(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SW_AS02
    (void)Com_ReceiveSignal(ComConf_ComSignal_SW_AS02, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_AS02 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SW_AS01(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SW_AS01(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SW_AS01
    (void)Com_ReceiveSignal(ComConf_ComSignal_SW_AS01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_AS01 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SW_AS05(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SW_AS05(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SW_AS05
    (void)Com_ReceiveSignal(ComConf_ComSignal_SW_AS05, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_AS05 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TBCSW(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TBCSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TBCSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_TBCSW, &u1_t_sig);
#endif /* ComConf_ComSignal_TBCSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TBWSW(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TBWSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TBWSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_TBWSW, &u1_t_sig);
#endif /* ComConf_ComSignal_TBWSW */
    return(u1_t_sig);
}/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_MRMRQSW(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_MRMRQSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_MRMRQSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_MRMRQSW, &u1_t_sig);
#endif /* ComConf_ComSignal_MRMRQSW */
    return(u1_t_sig);
}/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_MRMRQBK(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_MRMRQBK(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_MRMRQBK
    (void)Com_ReceiveSignal(ComConf_ComSignal_MRMRQBK, &u1_t_sig);
#endif /* ComConf_ComSignal_MRMRQBK */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_PCSMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_PCSMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_PCSMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCSMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_PCSMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_LDASW(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_LDASW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_LDASW
    (void)Com_ReceiveSignal(ComConf_ComSignal_LDASW, &u1_t_sig);
#endif /* ComConf_ComSignal_LDASW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_CSRMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_CSRMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_CSRMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_CSRMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_CSRMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ICSMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ICSMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ICSMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ICSMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ICSMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_BSMMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_BSMMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_BSMMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_BSMMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_BSMMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_DOAM_SW(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_DOAM_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_DOAM_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_DOAM_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_DOAM_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_RCTAMSW(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_RCTAMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_RCTAMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_RCTAMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_RCTAMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SW_RCD01(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SW_RCD01(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SW_RCD01
    (void)Com_ReceiveSignal(ComConf_ComSignal_SW_RCD01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_RCD01 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_IDAMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_IDAMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_IDAMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_IDAMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_IDAMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TSR_MAIN(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TSR_MAIN(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TSR_MAIN
    (void)Com_ReceiveSignal(ComConf_ComSignal_TSR_MAIN, &u1_t_sig);
#endif /* ComConf_ComSignal_TSR_MAIN */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACCADPSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACCADPSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACCADPSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCADPSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCADPSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACCROSSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACCROSSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACCROSSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCROSSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCROSSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACCACLSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACCACLSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACCACLSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCACLSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCACLSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACCSPSW1(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACCSPSW1(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACCSPSW1
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCSPSW1, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCSPSW1 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACCSPSW2(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACCSPSW2(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACCSPSW2
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCSPSW2, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCSPSW2 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACCRACSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACCRACSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACCRACSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCRACSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCRACSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACCSSOSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACCSSOSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACCSSOSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCSSOSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCSSOSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACCPROSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACCPROSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACCPROSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCPROSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCPROSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACCSPMSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACCSPMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACCSPMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCSPMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCSPMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ACCGCRSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ACCGCRSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ACCGCRSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCGCRSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ACCGCRSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ERMSW(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ERMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ERMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ERMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ERMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_CCSMDMSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_CCSMDMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_CCSMDMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_CCSMDMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_CCSMDMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SW_DEA01(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SW_DEA01(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SW_DEA01
    (void)Com_ReceiveSignal(ComConf_ComSignal_SW_DEA01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_DEA01 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_LDAMCUS(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_LDAMCUS(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_LDAMCUS
    (void)Com_ReceiveSignal(ComConf_ComSignal_LDAMCUS, &u1_t_sig);
#endif /* ComConf_ComSignal_LDAMCUS */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_FCMMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_FCMMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_FCMMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_FCMMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_FCMMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_LDALSMSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_LDALSMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_LDALSMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_LDALSMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_LDALSMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_LDA_SFB(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_LDA_SFB(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_LDA_SFB
    (void)Com_ReceiveSignal(ComConf_ComSignal_LDA_SFB, &u1_t_sig);
#endif /* ComConf_ComSignal_LDA_SFB */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_LDAAMSW(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_LDAAMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_LDAAMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_LDAAMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_LDAAMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SW_LTC01(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SW_LTC01(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SW_LTC01
    (void)Com_ReceiveSignal(ComConf_ComSignal_SW_LTC01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_LTC01 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_LCASGMSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_LCASGMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_LCASGMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_LCASGMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_LCASGMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_DISSUISW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_DISSUISW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_DISSUISW
    (void)Com_ReceiveSignal(ComConf_ComSignal_DISSUISW, &u1_t_sig);
#endif /* ComConf_ComSignal_DISSUISW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_PCSWDS1(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_PCSWDS1(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_PCSWDS1
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCSWDS1, &u1_t_sig);
#endif /* ComConf_ComSignal_PCSWDS1 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_DM_SW_A2(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_DM_SW_A2(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_DM_SW_A2
    (void)Com_ReceiveSignal(ComConf_ComSignal_DM_SW_A2, &u1_t_sig);
#endif /* ComConf_ComSignal_DM_SW_A2 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_PCSMBSW(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_PCSMBSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_PCSMBSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_PCSMBSW, &u1_t_sig);
#endif /* ComConf_ComSignal_PCSMBSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_IDASESW(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_IDASESW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_IDASESW
    (void)Com_ReceiveSignal(ComConf_ComSignal_IDASESW, &u1_t_sig);
#endif /* ComConf_ComSignal_IDASESW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_CTAMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_CTAMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_CTAMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_CTAMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_CTAMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_CTAWDS1(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_CTAWDS1(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_CTAWDS1
    (void)Com_ReceiveSignal(ComConf_ComSignal_CTAWDS1, &u1_t_sig);
#endif /* ComConf_ComSignal_CTAWDS1 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_BUZ_POS(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_BUZ_POS(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_BUZ_POS
    (void)Com_ReceiveSignal(ComConf_ComSignal_BUZ_POS, &u1_t_sig);
#endif /* ComConf_ComSignal_BUZ_POS */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_RSR_TIM(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_RSR_TIM(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_RSR_TIM
    (void)Com_ReceiveSignal(ComConf_ComSignal_RSR_TIM, &u1_t_sig);
#endif /* ComConf_ComSignal_RSR_TIM */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_BSMM_ILV(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_BSMM_ILV(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_BSMM_ILV
    (void)Com_ReceiveSignal(ComConf_ComSignal_BSMM_ILV, &u1_t_sig);
#endif /* ComConf_ComSignal_BSMM_ILV */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_DOAINDSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_DOAINDSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_DOAINDSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_DOAINDSW, &u1_t_sig);
#endif /* ComConf_ComSignal_DOAINDSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_DOAM_TIM(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_DOAM_TIM(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_DOAM_TIM
    (void)Com_ReceiveSignal(ComConf_ComSignal_DOAM_TIM, &u1_t_sig);
#endif /* ComConf_ComSignal_DOAM_TIM */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_RSCSW_OP(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_RSCSW_OP(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_RSCSW_OP
    (void)Com_ReceiveSignal(ComConf_ComSignal_RSCSW_OP, &u1_t_sig);
#endif /* ComConf_ComSignal_RSCSW_OP */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_PMARSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_PMARSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_PMARSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_PMARSW, &u1_t_sig);
#endif /* ComConf_ComSignal_PMARSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_LVNMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_LVNMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_LVNMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_LVNMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_LVNMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TMNSMSW(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TMNSMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TMNSMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_TMNSMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_TMNSMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TMNVTMSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TMNVTMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TMNVTMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_TMNVTMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_TMNVTMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TMNVSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TMNVSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TMNVSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_TMNVSW, &u1_t_sig);
#endif /* ComConf_ComSignal_TMNVSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  U1        u1_g_GwmmCfgRead_TMNSSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
U1        u1_g_GwmmCfgRead_TMNSSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TMNSSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_TMNSSW, &u1_t_sig);
#endif /* ComConf_ComSignal_TMNSSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TSR_SNM(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TSR_SNM(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TSR_SNM
    (void)Com_ReceiveSignal(ComConf_ComSignal_TSR_SNM, &u1_t_sig);
#endif /* ComConf_ComSignal_TSR_SNM */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SW_RSA01(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SW_RSA01(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SW_RSA01
    (void)Com_ReceiveSignal(ComConf_ComSignal_SW_RSA01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_RSA01 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TSR_OSM(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TSR_OSM(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TSR_OSM
    (void)Com_ReceiveSignal(ComConf_ComSignal_TSR_OSM, &u1_t_sig);
#endif /* ComConf_ComSignal_TSR_OSM */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TSR_OSL(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TSR_OSL(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TSR_OSL
    (void)Com_ReceiveSignal(ComConf_ComSignal_TSR_OSL, &u1_t_sig);
#endif /* ComConf_ComSignal_TSR_OSL */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_RSA_NEM(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_RSA_NEM(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_RSA_NEM
    (void)Com_ReceiveSignal(ComConf_ComSignal_RSA_NEM, &u1_t_sig);
#endif /* ComConf_ComSignal_RSA_NEM */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_RSA_LSM(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_RSA_LSM(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_RSA_LSM
    (void)Com_ReceiveSignal(ComConf_ComSignal_RSA_LSM, &u1_t_sig);
#endif /* ComConf_ComSignal_RSA_LSM */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SW_ITS04(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SW_ITS04(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SW_ITS04
    (void)Com_ReceiveSignal(ComConf_ComSignal_SW_ITS04, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_ITS04 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SW_ITS01(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SW_ITS01(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SW_ITS01
    (void)Com_ReceiveSignal(ComConf_ComSignal_SW_ITS01, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_ITS01 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SW_ITS02(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SW_ITS02(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SW_ITS02
    (void)Com_ReceiveSignal(ComConf_ComSignal_SW_ITS02, &u1_t_sig);
#endif /* ComConf_ComSignal_SW_ITS02 */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_EMGONSW(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_EMGONSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_EMGONSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_EMGONSW, &u1_t_sig);
#endif /* ComConf_ComSignal_EMGONSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_CACONSW(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_CACONSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_CACONSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_CACONSW, &u1_t_sig);
#endif /* ComConf_ComSignal_CACONSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ITSSETSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ITSSETSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ITSSETSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ITSSETSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ITSSETSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TRA_SW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TRA_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TRA_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_TRA_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_TRA_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_SLSSOSW(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SLSSOSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SLSSOSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_SLSSOSW, &u1_t_sig);
#endif /* ComConf_ComSignal_SLSSOSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_AHSSWVSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_AHSSWVSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_AHSSWVSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_AHSSWVSW, &u1_t_sig);
#endif /* ComConf_ComSignal_AHSSWVSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_AHSSDESW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_AHSSDESW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_AHSSDESW
    (void)Com_ReceiveSignal(ComConf_ComSignal_AHSSDESW, &u1_t_sig);
#endif /* ComConf_ComSignal_AHSSDESW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_ADINMSW(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ADINMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ADINMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ADINMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ADINMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TRLC_ID(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TRLC_ID(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TRLC_ID
    (void)Com_ReceiveSignal(ComConf_ComSignal_TRLC_ID, &u1_t_sig);
#endif /* ComConf_ComSignal_TRLC_ID */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TRLC_AC(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TRLC_AC(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TRLC_AC
    (void)Com_ReceiveSignal(ComConf_ComSignal_TRLC_AC, &u1_t_sig);
#endif /* ComConf_ComSignal_TRLC_AC */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_TRLC_TY(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_TRLC_TY(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_TRLC_TY
    (void)Com_ReceiveSignal(ComConf_ComSignal_TRLC_TY, &u1_t_sig);
#endif /* ComConf_ComSignal_TRLC_TY */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_NR_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_NR_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_NR_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_NR_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_NR_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_PW_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_PW_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_PW_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_PW_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_PW_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_EC_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_EC_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_EC_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_EC_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_EC_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_CS_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_CS_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_CS_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_CS_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_CS_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_PDAMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_PDAMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_PDAMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_PDAMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_PDAMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_SDGMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SDGMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SDGMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_SDGMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_SDGMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_USMMAIN(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_USMMAIN(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_USMMAIN
    (void)Com_ReceiveSignal(ComConf_ComSignal_USMMAIN, &u1_t_sig);
#endif /* ComConf_ComSignal_USMMAIN */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_HOFDIOPE(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_HOFDIOPE(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_HOFDIOPE
    (void)Com_ReceiveSignal(ComConf_ComSignal_HOFDIOPE, &u1_t_sig);
#endif /* ComConf_ComSignal_HOFDIOPE */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_HOFCUS(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_HOFCUS(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_HOFCUS
    (void)Com_ReceiveSignal(ComConf_ComSignal_HOFCUS, &u1_t_sig);
#endif /* ComConf_ComSignal_HOFCUS */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_DRECSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_DRECSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_DRECSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_DRECSW, &u1_t_sig);
#endif /* ComConf_ComSignal_DRECSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_DM_SW_AL(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_DM_SW_AL(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_DM_SW_AL
    (void)Com_ReceiveSignal(ComConf_ComSignal_DM_SW_AL, &u1_t_sig);
#endif /* ComConf_ComSignal_DM_SW_AL */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_DM_SW_DR(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_DM_SW_DR(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_DM_SW_DR
    (void)Com_ReceiveSignal(ComConf_ComSignal_DM_SW_DR, &u1_t_sig);
#endif /* ComConf_ComSignal_DM_SW_DR */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_RTWMSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_RTWMSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_RTWMSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_RTWMSW, &u1_t_sig);
#endif /* ComConf_ComSignal_RTWMSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_BSD_SMSB(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_BSD_SMSB(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_BSD_SMSB
    (void)Com_ReceiveSignal(ComConf_ComSignal_BSD_SMSB, &u1_t_sig);
#endif /* ComConf_ComSignal_BSD_SMSB */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_BSD_SMSS(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_BSD_SMSS(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_BSD_SMSS
    (void)Com_ReceiveSignal(ComConf_ComSignal_BSD_SMSS, &u1_t_sig);
#endif /* ComConf_ComSignal_BSD_SMSS */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_SPBZ_OPE(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_SPBZ_OPE(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_SPBZ_OPE
    (void)Com_ReceiveSignal(ComConf_ComSignal_SPBZ_OPE, &u1_t_sig);
#endif /* ComConf_ComSignal_SPBZ_OPE */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_RTAN_MSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_RTAN_MSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_RTAN_MSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_RTAN_MSW, &u1_t_sig);
#endif /* ComConf_ComSignal_RTAN_MSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_RTAN_TIM(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_RTAN_TIM(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_RTAN_TIM
    (void)Com_ReceiveSignal(ComConf_ComSignal_RTAN_TIM, &u1_t_sig);
#endif /* ComConf_ComSignal_RTAN_TIM */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_ADDS_MSW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_ADDS_MSW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_ADDS_MSW
    (void)Com_ReceiveSignal(ComConf_ComSignal_ADDS_MSW, &u1_t_sig);
#endif /* ComConf_ComSignal_ADDS_MSW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_CH_MD_SW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_CH_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_CH_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_CH_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_CH_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_RG_MD_SW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_RG_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_RG_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_RG_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_RG_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_GwmmCfgRead_P1_MD_SW(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_P1_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_P1_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_P1_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_P1_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_R1_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_R1_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_R1_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_R1_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_R1_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_R2_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_R2_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_R2_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_R2_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_R2_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_R3_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_R3_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_R3_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_R3_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_R3_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_R4_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_R4_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_R4_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_R4_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_R4_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_R5_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_R5_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_R5_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_R5_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_R5_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_R6_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_R6_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_R6_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_R6_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_R6_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_R7_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_R7_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_R7_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_R7_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_R7_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_R8_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_R8_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_R8_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_R8_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_R8_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_R9_MD_SW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_R9_MD_SW(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_R9_MD_SW
    (void)Com_ReceiveSignal(ComConf_ComSignal_R9_MD_SW, &u1_t_sig);
#endif /* ComConf_ComSignal_R9_MD_SW */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_L_TBCAK_ID(const U1 u1_a_SIG)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_L_TBCAK_ID(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_L_TBCAK_ID
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_L_TBCAK_ID, &u1_t_sig);
#endif /* ComConf_ComSignal_L_TBCAK_ID */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_L_TBCAK_TY(const U1 u1_a_SIG)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_L_TBCAK_TY(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_L_TBCAK_TY
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_L_TBCAK_TY, &u1_t_sig);
#endif /* ComConf_ComSignal_L_TBCAK_TY */
}
/*===================================================================================================================================*/
/*  static void vd_s_GwmmCfgSend_L_TBC_SF(const U1 u1_a_SIG)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SIG : Send Signal Value                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_GwmmCfgSend_L_TBC_SF(const U1 u1_a_SIG)
{
#ifdef ComConf_ComSignal_L_TBC_SF
    U1    u1_t_sig;
    u1_t_sig = u1_a_SIG;
    (void)Com_SendSignal(ComConf_ComSignal_L_TBC_SF, &u1_t_sig);
#endif /* ComConf_ComSignal_L_TBC_SF */
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_L_TBCAK_ID(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_L_TBCAK_ID(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_L_TBCAK_ID
    (void)Com_ReceiveSignal(ComConf_ComSignal_L_TBCAK_ID, &u1_t_sig);
#endif /* ComConf_ComSignal_L_TBCAK_ID */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_L_TBCAK_TY(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_L_TBCAK_TY(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_L_TBCAK_TY
    (void)Com_ReceiveSignal(ComConf_ComSignal_L_TBCAK_TY, &u1_t_sig);
#endif /* ComConf_ComSignal_L_TBCAK_TY */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_GwmmCfgRead_L_TBC_SF(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
static U1 u1_s_GwmmCfgRead_L_TBC_SF(void)
{
    U1  u1_t_sig;
    u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_L_TBC_SF
    (void)Com_ReceiveSignal(ComConf_ComSignal_L_TBC_SF, &u1_t_sig);
#endif /* ComConf_ComSignal_L_TBC_SF */
    return(u1_t_sig);
}
/*===================================================================================================================================*/
/*  U1        u1_g_GwmmCfgRead_L_TMNSSW(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_sig : Receive Signal Value                                                                                  */
/*===================================================================================================================================*/
U1        u1_g_GwmmCfgRead_L_TMNSSW(void)
{
    U1  u1_t_msgsts;                            /* Can Message Stats  */
    U1  u1_t_sig;

    u1_t_msgsts  = (U1)Com_GetIPDUStatus(MSG_AVNMC03_RXCH1);
    u1_t_msgsts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if(u1_t_msgsts == (U1)0U){
        u1_t_sig = (U1)0U;
#ifdef ComConf_ComSignal_L_TMNSSW
        (void)Com_ReceiveSignal(ComConf_ComSignal_L_TMNSSW, &u1_t_sig);
#endif /* ComConf_ComSignal_L_TMNSSW */
        u1_g_gwmm_tmnssw_sigbak = u1_t_sig;
    }
    else{
        u1_t_sig = u1_g_gwmm_tmnssw_sigbak;
    }
    return(u1_t_sig);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/17/2020  RS       New.                                                                                               */
/*  1.1.0    10/ 5/2020  RS       gateway_mm.c v1.0.0 -> v1.1.0                                                                      */
/*  1.2.0     5/31/2021  SK       gateway_mm.c v1.1.0 -> v1.2.0                                                                      */
/*  1.3.0    12/14/2021  RS       gateway_mm.c v1.2.0 -> v1.3.0                                                                      */
/*  1.4.0    11/19/2022  NT       gateway_mm.c v1.3.0 -> v1.4.0                                                                      */
/*  1.5.0     1/22/2024  TH       gateway_mm.c v1.4.0 -> v1.5.0                                                                      */
/*  1.6.0     3/26/2024  SW       gateway_mm.c v1.5.0 -> v1.6.0                                                                      */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1   10/ 5/2020  RS       Change config for 800B CV-R.                                                                       */
/*  800B-2   23/ 4/2021  RS       Change PBDMSW Power Jdg PRM.                                                                       */
/*  296D-1   10/21/2022  TX       Delete DVCN_OPE and DVAT_OPE.                                                                      */
/*  296D-2   11/08/2022  TX       Add MMCUSREQ.                                                                                      */
/*                                                                                                                                   */
/*  * RS   = Ryosuke Sato, KSE                                                                                                       */
/*  * SK   = Shinichi Kato, KSE                                                                                                      */
/*  * TX   = Tong Xinyuan, DNST                                                                                                      */
/*  * NT   = Noriaki Takashima, DT                                                                                                   */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
