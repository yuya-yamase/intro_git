/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Pitch/Roll Indicator                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PITCHROLL_C_MAJOR                         (1)
#define PITCHROLL_C_MINOR                         (0)
#define PITCHROLL_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "pitchroll_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((PITCHROLL_C_MAJOR != PITCHROLL_H_MAJOR) || \
     (PITCHROLL_C_MINOR != PITCHROLL_H_MINOR) || \
     (PITCHROLL_C_PATCH != PITCHROLL_H_PATCH))
#error "pitchroll.c and pitchroll.h : source and header files are inconsistent!"
#endif

#if ((PITCHROLL_C_MAJOR != PITCHROLL_CFG_PRIVATE_H_MAJOR) || \
     (PITCHROLL_C_MINOR != PITCHROLL_CFG_PRIVATE_H_MINOR) || \
     (PITCHROLL_C_PATCH != PITCHROLL_CFG_PRIVATE_H_PATCH))
#error "pitchroll.c and pitchroll_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PITCHROLL_MAIN_TICK                     (10U)
#define PITCHROLL_TO_FAIL                       (3600U / PITCHROLL_MAIN_TICK)
#define PITCHROLL_SMPLCNT_UPDT                  (500U / PITCHROLL_MAIN_TICK)

#define PITCHROLL_RXSTS_NML                     (0U)
#define PITCHROLL_RXSTS_NRX                     (1U)
#define PITCHROLL_RXSTS_FAL                     (2U)

#define PITCHROLL_STSBIT_NML                    (0x00U)
#define PITCHROLL_STSBIT_INT                    (0x01U)
#define PITCHROLL_STSBIT_FAL                    (0x02U)


#define PITCHROLL_SINE_MAX                      (1000)                              /* LSB:0.001 */
#define PITCHROLL_SINE_MIN                      (-1000)                             /* LSB:0.001 */

#define PITCHROLL_DISPANG_OFFSET                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4  u4_gx0;
    U4  u4_gy0;
    U4  u4_yaw0;
    U4  u4_sp1;
}ST_PITCHROLL_SIG_SUM;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                       u1_s_pitchroll_tmcnt_smpl;
static U2                       u2_s_pitchroll_tmcnt_fail;
static U1                       u1_s_pitchroll_sts;
static U1                       u1_s_pitchroll_nrxflg;

static ST_PITCHROLL_SIG_SUM     st_s_pitchroll_sig_smpl;
static ST_PITCHROLL_SIG_SUM     st_s_pitchroll_sig_pre;
static U4                       u4_s_pitchroll_sigsum_sp1_pre2;

static S2                       s2_s_pitchroll_x;
static S2                       s2_s_pitchroll_y;

static U1                       u1_s_pitchroll_fr_disp;
static U1                       u1_s_pitchroll_rl_disp;
static U1                       u1_s_pitchroll_disp_fail;
static S2                       s2_s_pitchroll_x_pre;
static S2                       s2_s_pitchroll_y_pre;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1      u1_s_PitchRollJdgSts(void);
static  U2      u2_s_PitchRollArcsin(const U2 u2_a_sin_pml);
static  U2      u2_s_PitchRollRadToAng(const U2 u2_a_rad_pml);
static  S4      s4_s_PitchRollCalcG(const U4 u4_a_gsum_las, const U4 u4_a_gsum_pre);
static  S4      s4_s_PitchRollCalcAsp(const U4 u4_a_spsum_las, const U4 u4_a_spsum_pre2);
static  S4      s4_s_PitchRollCalcA(const U4 u4_a_yrsum_las, const U4 u4_a_yrsum_pre, const U4 u4_a_spsum_las, const U4 u4_a_spsum_pre);
static  S2      s2_s_PitchRollCalcXY(const S4 s4_a_accel_pmr, const S4 s4_a_cor_pmr);
static  S4      s4_s_PitchRollCalcS4DivRand(const S4 s4_a_dividend, const S4 s4_a_divisor);
static  void    vd_s_PitchRollSample(ST_PITCHROLL_SIG_SUM * const st_ap_sum, const U1 u1_a_spflg);
static  void    vd_s_PitchRollSumChk(U4 * const u4_ap_sum, const U2 u2_a_single);
static  void    vd_s_PitchRollClrSum(ST_PITCHROLL_SIG_SUM * const st_ap_sum);
static  void    vd_s_PitchRollUpdate(const ST_PITCHROLL_SIG_SUM * const st_ap_sum, const U1 u1_a_notfirst);

static  void    vd_s_PitchRollDispAngInit(void);
static  void    vd_s_PitchRollDispAngMainTask(void);
static  U1      u1_s_PitchRollDispAngUpdate(const S2 s2_a_ang, const S2 s2_a_ang_pre, U1 * const u1_ap_curtdisp);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2 u2_sp_PITCHROLL_ARCSIN[PITCHROLL_SINE_MAX+1] = {
    (U2)0U,
    (U2)1U,
    (U2)2U,
    (U2)3U,
    (U2)4U,
    (U2)5U,
    (U2)6U,
    (U2)7U,
    (U2)8U,
    (U2)9U,
    (U2)10U,
    (U2)11U,
    (U2)12U,
    (U2)13U,
    (U2)14U,
    (U2)15U,
    (U2)16U,
    (U2)17U,
    (U2)18U,
    (U2)19U,
    (U2)20U,
    (U2)21U,
    (U2)22U,
    (U2)23U,
    (U2)24U,
    (U2)25U,
    (U2)26U,
    (U2)27U,
    (U2)28U,
    (U2)29U,
    (U2)30U,
    (U2)31U,
    (U2)32U,
    (U2)33U,
    (U2)34U,
    (U2)35U,
    (U2)36U,
    (U2)37U,
    (U2)38U,
    (U2)39U,
    (U2)40U,
    (U2)41U,
    (U2)42U,
    (U2)43U,
    (U2)44U,
    (U2)45U,
    (U2)46U,
    (U2)47U,
    (U2)48U,
    (U2)49U,
    (U2)50U,
    (U2)51U,
    (U2)52U,
    (U2)53U,
    (U2)54U,
    (U2)55U,
    (U2)56U,
    (U2)57U,
    (U2)58U,
    (U2)59U,
    (U2)60U,
    (U2)61U,
    (U2)62U,
    (U2)63U,
    (U2)64U,
    (U2)65U,
    (U2)66U,
    (U2)67U,
    (U2)68U,
    (U2)69U,
    (U2)70U,
    (U2)71U,
    (U2)72U,
    (U2)73U,
    (U2)74U,
    (U2)75U,
    (U2)76U,
    (U2)77U,
    (U2)78U,
    (U2)79U,
    (U2)80U,
    (U2)81U,
    (U2)82U,
    (U2)83U,
    (U2)84U,
    (U2)85U,
    (U2)86U,
    (U2)87U,
    (U2)88U,
    (U2)89U,
    (U2)90U,
    (U2)91U,
    (U2)92U,
    (U2)93U,
    (U2)94U,
    (U2)95U,
    (U2)96U,
    (U2)97U,
    (U2)98U,
    (U2)99U,
    (U2)100U,
    (U2)101U,
    (U2)102U,
    (U2)103U,
    (U2)104U,
    (U2)105U,
    (U2)106U,
    (U2)107U,
    (U2)108U,
    (U2)109U,
    (U2)110U,
    (U2)111U,
    (U2)112U,
    (U2)113U,
    (U2)114U,
    (U2)115U,
    (U2)116U,
    (U2)117U,
    (U2)118U,
    (U2)119U,
    (U2)120U,
    (U2)121U,
    (U2)122U,
    (U2)123U,
    (U2)124U,
    (U2)125U,
    (U2)126U,
    (U2)127U,
    (U2)128U,
    (U2)129U,
    (U2)130U,
    (U2)131U,
    (U2)132U,
    (U2)133U,
    (U2)134U,
    (U2)135U,
    (U2)136U,
    (U2)137U,
    (U2)138U,
    (U2)139U,
    (U2)140U,
    (U2)141U,
    (U2)142U,
    (U2)143U,
    (U2)145U,
    (U2)146U,
    (U2)147U,
    (U2)148U,
    (U2)149U,
    (U2)150U,
    (U2)151U,
    (U2)152U,
    (U2)153U,
    (U2)154U,
    (U2)155U,
    (U2)156U,
    (U2)157U,
    (U2)158U,
    (U2)159U,
    (U2)160U,
    (U2)161U,
    (U2)162U,
    (U2)163U,
    (U2)164U,
    (U2)165U,
    (U2)166U,
    (U2)167U,
    (U2)168U,
    (U2)169U,
    (U2)170U,
    (U2)171U,
    (U2)172U,
    (U2)173U,
    (U2)174U,
    (U2)175U,
    (U2)176U,
    (U2)177U,
    (U2)178U,
    (U2)179U,
    (U2)180U,
    (U2)181U,
    (U2)182U,
    (U2)183U,
    (U2)184U,
    (U2)185U,
    (U2)186U,
    (U2)187U,
    (U2)188U,
    (U2)189U,
    (U2)190U,
    (U2)191U,
    (U2)192U,
    (U2)193U,
    (U2)194U,
    (U2)195U,
    (U2)196U,
    (U2)197U,
    (U2)198U,
    (U2)199U,
    (U2)200U,
    (U2)201U,
    (U2)202U,
    (U2)203U,
    (U2)204U,
    (U2)205U,
    (U2)206U,
    (U2)207U,
    (U2)209U,
    (U2)210U,
    (U2)211U,
    (U2)212U,
    (U2)213U,
    (U2)214U,
    (U2)215U,
    (U2)216U,
    (U2)217U,
    (U2)218U,
    (U2)219U,
    (U2)220U,
    (U2)221U,
    (U2)222U,
    (U2)223U,
    (U2)224U,
    (U2)225U,
    (U2)226U,
    (U2)227U,
    (U2)228U,
    (U2)229U,
    (U2)230U,
    (U2)231U,
    (U2)232U,
    (U2)233U,
    (U2)234U,
    (U2)235U,
    (U2)236U,
    (U2)237U,
    (U2)238U,
    (U2)239U,
    (U2)240U,
    (U2)241U,
    (U2)242U,
    (U2)243U,
    (U2)244U,
    (U2)245U,
    (U2)246U,
    (U2)248U,
    (U2)249U,
    (U2)250U,
    (U2)251U,
    (U2)252U,
    (U2)253U,
    (U2)254U,
    (U2)255U,
    (U2)256U,
    (U2)257U,
    (U2)258U,
    (U2)259U,
    (U2)260U,
    (U2)261U,
    (U2)262U,
    (U2)263U,
    (U2)264U,
    (U2)265U,
    (U2)266U,
    (U2)267U,
    (U2)268U,
    (U2)269U,
    (U2)270U,
    (U2)271U,
    (U2)272U,
    (U2)273U,
    (U2)274U,
    (U2)275U,
    (U2)277U,
    (U2)278U,
    (U2)279U,
    (U2)280U,
    (U2)281U,
    (U2)282U,
    (U2)283U,
    (U2)284U,
    (U2)285U,
    (U2)286U,
    (U2)287U,
    (U2)288U,
    (U2)289U,
    (U2)290U,
    (U2)291U,
    (U2)292U,
    (U2)293U,
    (U2)294U,
    (U2)295U,
    (U2)296U,
    (U2)297U,
    (U2)298U,
    (U2)299U,
    (U2)301U,
    (U2)302U,
    (U2)303U,
    (U2)304U,
    (U2)305U,
    (U2)306U,
    (U2)307U,
    (U2)308U,
    (U2)309U,
    (U2)310U,
    (U2)311U,
    (U2)312U,
    (U2)313U,
    (U2)314U,
    (U2)315U,
    (U2)316U,
    (U2)317U,
    (U2)318U,
    (U2)319U,
    (U2)320U,
    (U2)322U,
    (U2)323U,
    (U2)324U,
    (U2)325U,
    (U2)326U,
    (U2)327U,
    (U2)328U,
    (U2)329U,
    (U2)330U,
    (U2)331U,
    (U2)332U,
    (U2)333U,
    (U2)334U,
    (U2)335U,
    (U2)336U,
    (U2)337U,
    (U2)338U,
    (U2)339U,
    (U2)341U,
    (U2)342U,
    (U2)343U,
    (U2)344U,
    (U2)345U,
    (U2)346U,
    (U2)347U,
    (U2)348U,
    (U2)349U,
    (U2)350U,
    (U2)351U,
    (U2)352U,
    (U2)353U,
    (U2)354U,
    (U2)355U,
    (U2)357U,
    (U2)358U,
    (U2)359U,
    (U2)360U,
    (U2)361U,
    (U2)362U,
    (U2)363U,
    (U2)364U,
    (U2)365U,
    (U2)366U,
    (U2)367U,
    (U2)368U,
    (U2)369U,
    (U2)370U,
    (U2)371U,
    (U2)373U,
    (U2)374U,
    (U2)375U,
    (U2)376U,
    (U2)377U,
    (U2)378U,
    (U2)379U,
    (U2)380U,
    (U2)381U,
    (U2)382U,
    (U2)383U,
    (U2)384U,
    (U2)385U,
    (U2)387U,
    (U2)388U,
    (U2)389U,
    (U2)390U,
    (U2)391U,
    (U2)392U,
    (U2)393U,
    (U2)394U,
    (U2)395U,
    (U2)396U,
    (U2)397U,
    (U2)398U,
    (U2)400U,
    (U2)401U,
    (U2)402U,
    (U2)403U,
    (U2)404U,
    (U2)405U,
    (U2)406U,
    (U2)407U,
    (U2)408U,
    (U2)409U,
    (U2)410U,
    (U2)412U,
    (U2)413U,
    (U2)414U,
    (U2)415U,
    (U2)416U,
    (U2)417U,
    (U2)418U,
    (U2)419U,
    (U2)420U,
    (U2)421U,
    (U2)422U,
    (U2)424U,
    (U2)425U,
    (U2)426U,
    (U2)427U,
    (U2)428U,
    (U2)429U,
    (U2)430U,
    (U2)431U,
    (U2)432U,
    (U2)433U,
    (U2)435U,
    (U2)436U,
    (U2)437U,
    (U2)438U,
    (U2)439U,
    (U2)440U,
    (U2)441U,
    (U2)442U,
    (U2)443U,
    (U2)444U,
    (U2)446U,
    (U2)447U,
    (U2)448U,
    (U2)449U,
    (U2)450U,
    (U2)451U,
    (U2)452U,
    (U2)453U,
    (U2)454U,
    (U2)456U,
    (U2)457U,
    (U2)458U,
    (U2)459U,
    (U2)460U,
    (U2)461U,
    (U2)462U,
    (U2)463U,
    (U2)465U,
    (U2)466U,
    (U2)467U,
    (U2)468U,
    (U2)469U,
    (U2)470U,
    (U2)471U,
    (U2)472U,
    (U2)473U,
    (U2)475U,
    (U2)476U,
    (U2)477U,
    (U2)478U,
    (U2)479U,
    (U2)480U,
    (U2)481U,
    (U2)483U,
    (U2)484U,
    (U2)485U,
    (U2)486U,
    (U2)487U,
    (U2)488U,
    (U2)489U,
    (U2)490U,
    (U2)492U,
    (U2)493U,
    (U2)494U,
    (U2)495U,
    (U2)496U,
    (U2)497U,
    (U2)498U,
    (U2)500U,
    (U2)501U,
    (U2)502U,
    (U2)503U,
    (U2)504U,
    (U2)505U,
    (U2)506U,
    (U2)508U,
    (U2)509U,
    (U2)510U,
    (U2)511U,
    (U2)512U,
    (U2)513U,
    (U2)514U,
    (U2)516U,
    (U2)517U,
    (U2)518U,
    (U2)519U,
    (U2)520U,
    (U2)521U,
    (U2)522U,
    (U2)524U,
    (U2)525U,
    (U2)526U,
    (U2)527U,
    (U2)528U,
    (U2)529U,
    (U2)531U,
    (U2)532U,
    (U2)533U,
    (U2)534U,
    (U2)535U,
    (U2)536U,
    (U2)538U,
    (U2)539U,
    (U2)540U,
    (U2)541U,
    (U2)542U,
    (U2)543U,
    (U2)545U,
    (U2)546U,
    (U2)547U,
    (U2)548U,
    (U2)549U,
    (U2)550U,
    (U2)552U,
    (U2)553U,
    (U2)554U,
    (U2)555U,
    (U2)556U,
    (U2)557U,
    (U2)559U,
    (U2)560U,
    (U2)561U,
    (U2)562U,
    (U2)563U,
    (U2)565U,
    (U2)566U,
    (U2)567U,
    (U2)568U,
    (U2)569U,
    (U2)570U,
    (U2)572U,
    (U2)573U,
    (U2)574U,
    (U2)575U,
    (U2)576U,
    (U2)578U,
    (U2)579U,
    (U2)580U,
    (U2)581U,
    (U2)582U,
    (U2)584U,
    (U2)585U,
    (U2)586U,
    (U2)587U,
    (U2)588U,
    (U2)590U,
    (U2)591U,
    (U2)592U,
    (U2)593U,
    (U2)594U,
    (U2)596U,
    (U2)597U,
    (U2)598U,
    (U2)599U,
    (U2)600U,
    (U2)602U,
    (U2)603U,
    (U2)604U,
    (U2)605U,
    (U2)607U,
    (U2)608U,
    (U2)609U,
    (U2)610U,
    (U2)611U,
    (U2)613U,
    (U2)614U,
    (U2)615U,
    (U2)616U,
    (U2)618U,
    (U2)619U,
    (U2)620U,
    (U2)621U,
    (U2)622U,
    (U2)624U,
    (U2)625U,
    (U2)626U,
    (U2)627U,
    (U2)629U,
    (U2)630U,
    (U2)631U,
    (U2)632U,
    (U2)634U,
    (U2)635U,
    (U2)636U,
    (U2)637U,
    (U2)639U,
    (U2)640U,
    (U2)641U,
    (U2)642U,
    (U2)644U,
    (U2)645U,
    (U2)646U,
    (U2)647U,
    (U2)649U,
    (U2)650U,
    (U2)651U,
    (U2)652U,
    (U2)654U,
    (U2)655U,
    (U2)656U,
    (U2)657U,
    (U2)659U,
    (U2)660U,
    (U2)661U,
    (U2)662U,
    (U2)664U,
    (U2)665U,
    (U2)666U,
    (U2)667U,
    (U2)669U,
    (U2)670U,
    (U2)671U,
    (U2)673U,
    (U2)674U,
    (U2)675U,
    (U2)676U,
    (U2)678U,
    (U2)679U,
    (U2)680U,
    (U2)682U,
    (U2)683U,
    (U2)684U,
    (U2)685U,
    (U2)687U,
    (U2)688U,
    (U2)689U,
    (U2)691U,
    (U2)692U,
    (U2)693U,
    (U2)694U,
    (U2)696U,
    (U2)697U,
    (U2)698U,
    (U2)700U,
    (U2)701U,
    (U2)702U,
    (U2)704U,
    (U2)705U,
    (U2)706U,
    (U2)708U,
    (U2)709U,
    (U2)710U,
    (U2)712U,
    (U2)713U,
    (U2)714U,
    (U2)716U,
    (U2)717U,
    (U2)718U,
    (U2)719U,
    (U2)721U,
    (U2)722U,
    (U2)723U,
    (U2)725U,
    (U2)726U,
    (U2)727U,
    (U2)729U,
    (U2)730U,
    (U2)732U,
    (U2)733U,
    (U2)734U,
    (U2)736U,
    (U2)737U,
    (U2)738U,
    (U2)740U,
    (U2)741U,
    (U2)742U,
    (U2)744U,
    (U2)745U,
    (U2)746U,
    (U2)748U,
    (U2)749U,
    (U2)750U,
    (U2)752U,
    (U2)753U,
    (U2)755U,
    (U2)756U,
    (U2)757U,
    (U2)759U,
    (U2)760U,
    (U2)761U,
    (U2)763U,
    (U2)764U,
    (U2)766U,
    (U2)767U,
    (U2)768U,
    (U2)770U,
    (U2)771U,
    (U2)773U,
    (U2)774U,
    (U2)775U,
    (U2)777U,
    (U2)778U,
    (U2)780U,
    (U2)781U,
    (U2)782U,
    (U2)784U,
    (U2)785U,
    (U2)787U,
    (U2)788U,
    (U2)789U,
    (U2)791U,
    (U2)792U,
    (U2)794U,
    (U2)795U,
    (U2)797U,
    (U2)798U,
    (U2)799U,
    (U2)801U,
    (U2)802U,
    (U2)804U,
    (U2)805U,
    (U2)807U,
    (U2)808U,
    (U2)810U,
    (U2)811U,
    (U2)812U,
    (U2)814U,
    (U2)815U,
    (U2)817U,
    (U2)818U,
    (U2)820U,
    (U2)821U,
    (U2)823U,
    (U2)824U,
    (U2)826U,
    (U2)827U,
    (U2)829U,
    (U2)830U,
    (U2)832U,
    (U2)833U,
    (U2)835U,
    (U2)836U,
    (U2)838U,
    (U2)839U,
    (U2)841U,
    (U2)842U,
    (U2)844U,
    (U2)845U,
    (U2)847U,
    (U2)848U,
    (U2)850U,
    (U2)851U,
    (U2)853U,
    (U2)854U,
    (U2)856U,
    (U2)857U,
    (U2)859U,
    (U2)860U,
    (U2)862U,
    (U2)863U,
    (U2)865U,
    (U2)866U,
    (U2)868U,
    (U2)869U,
    (U2)871U,
    (U2)873U,
    (U2)874U,
    (U2)876U,
    (U2)877U,
    (U2)879U,
    (U2)880U,
    (U2)882U,
    (U2)884U,
    (U2)885U,
    (U2)887U,
    (U2)888U,
    (U2)890U,
    (U2)891U,
    (U2)893U,
    (U2)895U,
    (U2)896U,
    (U2)898U,
    (U2)899U,
    (U2)901U,
    (U2)903U,
    (U2)904U,
    (U2)906U,
    (U2)908U,
    (U2)909U,
    (U2)911U,
    (U2)912U,
    (U2)914U,
    (U2)916U,
    (U2)917U,
    (U2)919U,
    (U2)921U,
    (U2)922U,
    (U2)924U,
    (U2)926U,
    (U2)927U,
    (U2)929U,
    (U2)931U,
    (U2)932U,
    (U2)934U,
    (U2)936U,
    (U2)937U,
    (U2)939U,
    (U2)941U,
    (U2)942U,
    (U2)944U,
    (U2)946U,
    (U2)948U,
    (U2)949U,
    (U2)951U,
    (U2)953U,
    (U2)954U,
    (U2)956U,
    (U2)958U,
    (U2)960U,
    (U2)961U,
    (U2)963U,
    (U2)965U,
    (U2)967U,
    (U2)968U,
    (U2)970U,
    (U2)972U,
    (U2)974U,
    (U2)976U,
    (U2)977U,
    (U2)979U,
    (U2)981U,
    (U2)983U,
    (U2)985U,
    (U2)986U,
    (U2)988U,
    (U2)990U,
    (U2)992U,
    (U2)994U,
    (U2)995U,
    (U2)997U,
    (U2)999U,
    (U2)1001U,
    (U2)1003U,
    (U2)1005U,
    (U2)1007U,
    (U2)1008U,
    (U2)1010U,
    (U2)1012U,
    (U2)1014U,
    (U2)1016U,
    (U2)1018U,
    (U2)1020U,
    (U2)1022U,
    (U2)1024U,
    (U2)1026U,
    (U2)1027U,
    (U2)1029U,
    (U2)1031U,
    (U2)1033U,
    (U2)1035U,
    (U2)1037U,
    (U2)1039U,
    (U2)1041U,
    (U2)1043U,
    (U2)1045U,
    (U2)1047U,
    (U2)1049U,
    (U2)1051U,
    (U2)1053U,
    (U2)1055U,
    (U2)1057U,
    (U2)1059U,
    (U2)1061U,
    (U2)1063U,
    (U2)1065U,
    (U2)1068U,
    (U2)1070U,
    (U2)1072U,
    (U2)1074U,
    (U2)1076U,
    (U2)1078U,
    (U2)1080U,
    (U2)1082U,
    (U2)1084U,
    (U2)1086U,
    (U2)1089U,
    (U2)1091U,
    (U2)1093U,
    (U2)1095U,
    (U2)1097U,
    (U2)1100U,
    (U2)1102U,
    (U2)1104U,
    (U2)1106U,
    (U2)1108U,
    (U2)1111U,
    (U2)1113U,
    (U2)1115U,
    (U2)1117U,
    (U2)1120U,
    (U2)1122U,
    (U2)1124U,
    (U2)1127U,
    (U2)1129U,
    (U2)1131U,
    (U2)1134U,
    (U2)1136U,
    (U2)1138U,
    (U2)1141U,
    (U2)1143U,
    (U2)1146U,
    (U2)1148U,
    (U2)1151U,
    (U2)1153U,
    (U2)1156U,
    (U2)1158U,
    (U2)1160U,
    (U2)1163U,
    (U2)1166U,
    (U2)1168U,
    (U2)1171U,
    (U2)1173U,
    (U2)1176U,
    (U2)1178U,
    (U2)1181U,
    (U2)1184U,
    (U2)1186U,
    (U2)1189U,
    (U2)1192U,
    (U2)1194U,
    (U2)1197U,
    (U2)1200U,
    (U2)1203U,
    (U2)1205U,
    (U2)1208U,
    (U2)1211U,
    (U2)1214U,
    (U2)1217U,
    (U2)1220U,
    (U2)1223U,
    (U2)1226U,
    (U2)1229U,
    (U2)1232U,
    (U2)1235U,
    (U2)1238U,
    (U2)1241U,
    (U2)1244U,
    (U2)1247U,
    (U2)1250U,
    (U2)1253U,
    (U2)1256U,
    (U2)1260U,
    (U2)1263U,
    (U2)1266U,
    (U2)1270U,
    (U2)1273U,
    (U2)1276U,
    (U2)1280U,
    (U2)1283U,
    (U2)1287U,
    (U2)1291U,
    (U2)1294U,
    (U2)1298U,
    (U2)1302U,
    (U2)1305U,
    (U2)1309U,
    (U2)1313U,
    (U2)1317U,
    (U2)1321U,
    (U2)1325U,
    (U2)1329U,
    (U2)1334U,
    (U2)1338U,
    (U2)1342U,
    (U2)1347U,
    (U2)1351U,
    (U2)1356U,
    (U2)1361U,
    (U2)1365U,
    (U2)1370U,
    (U2)1376U,
    (U2)1381U,
    (U2)1386U,
    (U2)1392U,
    (U2)1397U,
    (U2)1403U,
    (U2)1409U,
    (U2)1416U,
    (U2)1422U,
    (U2)1429U,
    (U2)1437U,
    (U2)1444U,
    (U2)1452U,
    (U2)1461U,
    (U2)1471U,
    (U2)1481U,
    (U2)1493U,
    (U2)1508U,
    (U2)1526U,
    (U2)1571U
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_PitchRollInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PitchRollInit(void)
{
    u1_s_pitchroll_tmcnt_smpl = (U1)0U;
    u2_s_pitchroll_tmcnt_fail = (U2)0U;
    u1_s_pitchroll_sts  = (U1)PITCHROLL_STSBIT_INT;
    u1_s_pitchroll_nrxflg = (U1)TRUE;
    vd_s_PitchRollClrSum(&st_s_pitchroll_sig_smpl);
    vd_s_PitchRollClrSum(&st_s_pitchroll_sig_pre);
    u4_s_pitchroll_sigsum_sp1_pre2 = (U4)0U;
    s2_s_pitchroll_x = (S2)0;
    s2_s_pitchroll_y = (S2)0;

    vd_s_PitchRollDispAngInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_PitchRollMainTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PitchRollMainTask(void)
{
    U1      u1_t_ig_on;
    U1      u1_t_prsts;

    u1_t_ig_on = u1_g_PitchRollCfgIgOn();
    u1_t_prsts = u1_s_PitchRollJdgSts();
    if(u1_t_ig_on == (U1)FALSE){
        vd_g_PitchRollInit();
    }
    else if(u1_t_prsts == (U1)PITCHROLL_RXSTS_FAL){
        u1_s_pitchroll_sts |= (U1)PITCHROLL_STSBIT_FAL;
    }
    else if(u1_t_prsts == (U1)PITCHROLL_RXSTS_NML){
        u1_s_pitchroll_sts &= (U1)(~(U1)PITCHROLL_STSBIT_FAL);
        if((u1_s_pitchroll_tmcnt_smpl % (U1)2U) == (U1)0U){
            vd_s_PitchRollSample(&st_s_pitchroll_sig_smpl, (U1)TRUE);
        }
        else{
            vd_s_PitchRollSample(&st_s_pitchroll_sig_smpl, (U1)FALSE);
        }
        u1_s_pitchroll_tmcnt_smpl++;

        if(u1_s_pitchroll_nrxflg == (U1)TRUE){
            vd_s_PitchRollUpdate(&st_s_pitchroll_sig_smpl, (U1)FALSE);
            u1_s_pitchroll_nrxflg = (U1)FALSE;
        }

        if(u1_s_pitchroll_tmcnt_smpl >= (U1)PITCHROLL_SMPLCNT_UPDT){
            vd_s_PitchRollUpdate(&st_s_pitchroll_sig_smpl, (U1)TRUE);
            u1_s_pitchroll_sts = (U1)PITCHROLL_STSBIT_NML;
            u1_s_pitchroll_tmcnt_smpl = (U1)0;
            vd_s_PitchRollClrSum(&st_s_pitchroll_sig_smpl);
        }
    }
    else{
        /* Do Nothing */
    }

    vd_s_PitchRollDispAngMainTask();
}

/*===================================================================================================================================*/
/*  U1      u1_g_PitchRollAngle(S2 * const s2_ap_angx_0p01, S2 * const s2_ap_angy_0p01)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_PitchRollAngle(S2 * const s2_ap_angx_0p01, S2 * const s2_ap_angy_0p01)
{
    U1 u1_t_sts;

    if(u1_s_pitchroll_sts == (U1)PITCHROLL_STSBIT_NML){
        u1_t_sts = (U1)PITCHROLL_STS_NOMAL;
        (*s2_ap_angx_0p01) = s2_s_pitchroll_x;
        (*s2_ap_angy_0p01) = s2_s_pitchroll_y;
    }
    else if((u1_s_pitchroll_sts & (U1)PITCHROLL_STSBIT_FAL) != (U1)0U){
        u1_t_sts = (U1)PITCHROLL_STS_FAIL;
    }
    else{
        u1_t_sts = (U1)PITCHROLL_STS_INT;
    }

    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static  void    vd_s_PitchRollDispAngInit(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_PitchRollDispAngInit(void)
{
    u1_s_pitchroll_fr_disp = u1_g_PITCHROLL_DSPANG_ABS_MAX;
    u1_s_pitchroll_rl_disp = u1_g_PITCHROLL_DSPANG_ABS_MAX;
    u1_s_pitchroll_disp_fail = (U1)FALSE;
    s2_s_pitchroll_x_pre = (S2)0;
    s2_s_pitchroll_y_pre = (S2)0;
}

/*===================================================================================================================================*/
/*  static  void    vd_s_PitchRollDispAngMainTask(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_PitchRollDispAngMainTask(void)
{
    S2      s2_t_ang_x;
    S2      s2_t_ang_y;
    U1      u1_t_sts;
    U1      u1_t_ig_on;

    u1_t_ig_on = u1_g_PitchRollCfgIgOn();
    if(u1_t_ig_on == (U1)FALSE){
        vd_s_PitchRollDispAngInit();
    }
    else{
        s2_t_ang_x = (S2)0;
        s2_t_ang_y = (S2)0;
        u1_t_sts = u1_g_PitchRollAngle(&s2_t_ang_x, &s2_t_ang_y);

        if(u1_t_sts == (U1)PITCHROLL_STS_NOMAL){
            u1_s_pitchroll_disp_fail = u1_s_PitchRollDispAngUpdate(s2_t_ang_x, s2_s_pitchroll_x_pre, &u1_s_pitchroll_fr_disp);
            u1_s_pitchroll_disp_fail |= u1_s_PitchRollDispAngUpdate(s2_t_ang_y, s2_s_pitchroll_y_pre, &u1_s_pitchroll_rl_disp);
            s2_s_pitchroll_x_pre = s2_t_ang_x;
            s2_s_pitchroll_y_pre = s2_t_ang_y;
        }
        else if(u1_t_sts == (U1)PITCHROLL_STS_FAIL){
            u1_s_pitchroll_disp_fail = (U1)TRUE;
        }
        else{
            u1_s_pitchroll_disp_fail = (U1)FALSE;
            u1_s_pitchroll_fr_disp = u1_g_PITCHROLL_DSPANG_ABS_MAX;
            u1_s_pitchroll_rl_disp = u1_g_PITCHROLL_DSPANG_ABS_MAX;
        }
    }
}

/*===================================================================================================================================*/
/*  U1      u1_g_PitchRollDispAng(U1 * const u1_ap_frdisp, U1 * const u1_ap_rldisp)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_PitchRollDispAng(U1 * const u1_ap_frdisp, U1 * const u1_ap_rldisp)
{
    if(u1_s_pitchroll_disp_fail == (U1)FALSE){
        /* Sensor Staus: Normal  &&  Communication Status: Normal  &&  -30deg/-40deg over <= angdisp <= 30deg/40deg                  */
        (*u1_ap_frdisp) = u1_s_pitchroll_fr_disp - (U1)PITCHROLL_DISPANG_OFFSET;
        (*u1_ap_rldisp) = u1_s_pitchroll_rl_disp - (U1)PITCHROLL_DISPANG_OFFSET;
    }

    return(u1_s_pitchroll_disp_fail);
}

/*===================================================================================================================================*/
/*  static  void    vd_s_PitchRollClrSum(ST_PITCHROLL_SIG_SUM * const st_ap_sum)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_PitchRollClrSum(ST_PITCHROLL_SIG_SUM * const st_ap_sum)
{
    st_ap_sum->u4_gx0  = (U4)0U;
    st_ap_sum->u4_gy0  = (U4)0U;
    st_ap_sum->u4_yaw0 = (U4)0U;
    st_ap_sum->u4_sp1  = (U4)0U;
}

/*===================================================================================================================================*/
/*  static  U1      u1_s_PitchRollJdgSts(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_PitchRollJdgSts(void)
{
    U1      u1_t_msgstsYG;
    U1      u1_t_msgstsSP;
    U1      u1_t_gxf;
    U1      u1_t_gyf;
    U1      u1_t_gxiv;
    U1      u1_t_gyiv;
    U1      u1_t_yaws;
    U1      u1_t_yawf;
    U1      u1_t_prsts;

    u1_t_prsts = (U1)PITCHROLL_RXSTS_NML;
    u1_t_msgstsYG = u1_g_PitchRollCfgGetMsgStsYawG();
    u1_t_msgstsSP = u1_g_PitchRollCfgGetMsgStsSp();
    u1_t_gxf  = u1_g_PitchRollCfgGetVSCGXF();
    u1_t_gyf  = u1_g_PitchRollCfgGetVSCGYF();
    u1_t_gxiv = u1_g_PitchRollCfgGetVSCGXIV();
    u1_t_gyiv = u1_g_PitchRollCfgGetVSCGYIV();
    u1_t_yaws = u1_g_PitchRollCfgGetVSCYAWS();
    u1_t_yawf = u1_g_PitchRollCfgGetVSCYAWF();

    if(((u1_t_msgstsYG & (U1)PITCHROLL_RX_INVALID) != (U1)0U) ||
       ((u1_t_msgstsSP & (U1)PITCHROLL_RX_INVALID) != (U1)0U)){
        u1_t_prsts = (U1)PITCHROLL_RXSTS_FAL;
        u2_s_pitchroll_tmcnt_fail = (U2)0U;
    }
    else if(((u1_t_msgstsYG & (U1)PITCHROLL_RX_UNKNOWN) != (U1)0U) ||
            ((u1_t_msgstsSP & (U1)PITCHROLL_RX_UNKNOWN) != (U1)0U)){
            u1_t_prsts = (U1)PITCHROLL_RXSTS_NRX;
            u2_s_pitchroll_tmcnt_fail = (U2)0U;
    }
    else if((u1_t_gxf  == (U1)1U) ||
            (u1_t_gyf  == (U1)1U) ||
            (u1_t_gxiv == (U1)1U) ||
            (u1_t_gyiv == (U1)1U) ||
            (u1_t_yaws == (U1)1U) ||
            (u1_t_yawf == (U1)1U)){
            if(u2_s_pitchroll_tmcnt_fail >= (U2)PITCHROLL_TO_FAIL){
                u1_t_prsts = (U1)PITCHROLL_RXSTS_FAL;
            }
            else{
                u2_s_pitchroll_tmcnt_fail++;
            }
    }
    else{
        u2_s_pitchroll_tmcnt_fail = (U2)0U;
    }

    return(u1_t_prsts);
}


/*===================================================================================================================================*/
/*  static  void    vd_s_PitchRollSample(ST_PITCHROLL_SIG_SUM * const st_ap_sum, const U1 u1_a_spflg)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_PitchRollSample(ST_PITCHROLL_SIG_SUM * const st_ap_sum, const U1 u1_a_spflg)
{
    U2      u2_t_gx0;
    U2      u2_t_gy0;
    U2      u2_t_yaw0;
    U2      u2_t_sp1;

    u2_t_gx0  = u2_g_PitchRollCfgGetVSCGX0();
    u2_t_gy0  = u2_g_PitchRollCfgGetVSCGY0();
    u2_t_yaw0 = u2_g_PitchRollCfgGetVSCYAW0();
    if(u1_a_spflg == (U1)TRUE){
        u2_t_sp1 = u2_g_PitchRollCfgGetSP1();
    }
    else{
        u2_t_sp1 = (U2)0U;
    }
    
    vd_s_PitchRollSumChk(&(st_ap_sum->u4_gx0), u2_t_gx0);
    vd_s_PitchRollSumChk(&(st_ap_sum->u4_gy0), u2_t_gy0);
    vd_s_PitchRollSumChk(&(st_ap_sum->u4_yaw0), u2_t_yaw0);
    vd_s_PitchRollSumChk(&(st_ap_sum->u4_sp1), u2_t_sp1);
}

/*===================================================================================================================================*/
/*  static  void    vd_s_PitchRollSumChk(U4 * const u4_ap_sum, const U2 u2_a_single)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_PitchRollSumChk(U4 * const u4_ap_sum, const U2 u2_a_single)
{
    if((*u4_ap_sum) < ((U4)U4_MAX - (U4)u2_a_single)){
        (*u4_ap_sum) += (U4)u2_a_single;
    }
    else{
        (*u4_ap_sum) = (U4)U4_MAX;
    }
}

/*===================================================================================================================================*/
/*  static  void    vd_s_PitchRollUpdate(const ST_PITCHROLL_SIG_SUM * const st_ap_sum, const U1 u1_a_notfirst)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_PitchRollUpdate(const ST_PITCHROLL_SIG_SUM * const st_ap_sum, const U1 u1_a_notfirst)
{
    S4  s4_t_glav_minus;                            /* lsb:0.0001 */
    S4  s4_t_gwav;                                  /* lsb:0.0001 */
    S4  s4_t_asp;                                   /* lsb:0.0001 */
    S4  s4_t_a;                                     /* lsb:0.0001 */

    if(u1_a_notfirst == (U1)FALSE){
        u4_s_pitchroll_sigsum_sp1_pre2 = st_ap_sum->u4_sp1  * ((U4)PITCHROLL_SMPLCNT_UPDT >> 1);
        st_s_pitchroll_sig_pre.u4_gx0  = st_ap_sum->u4_gx0  * (U4)PITCHROLL_SMPLCNT_UPDT;
        st_s_pitchroll_sig_pre.u4_gy0  = st_ap_sum->u4_gy0  * (U4)PITCHROLL_SMPLCNT_UPDT;
        st_s_pitchroll_sig_pre.u4_yaw0 = st_ap_sum->u4_yaw0 * (U4)PITCHROLL_SMPLCNT_UPDT;
        st_s_pitchroll_sig_pre.u4_sp1  = st_ap_sum->u4_sp1  * ((U4)PITCHROLL_SMPLCNT_UPDT >> 1);
    }
    else{
        s4_t_glav_minus = s4_s_PitchRollCalcG(st_ap_sum->u4_gx0, st_s_pitchroll_sig_pre.u4_gx0);
        s4_t_gwav = s4_s_PitchRollCalcG(st_ap_sum->u4_gy0, st_s_pitchroll_sig_pre.u4_gy0);
        s4_t_asp = s4_s_PitchRollCalcAsp(st_ap_sum->u4_sp1, u4_s_pitchroll_sigsum_sp1_pre2);
        s4_t_a = s4_s_PitchRollCalcA(st_ap_sum->u4_yaw0, st_s_pitchroll_sig_pre.u4_yaw0, st_ap_sum->u4_sp1, st_s_pitchroll_sig_pre.u4_sp1);

        s2_s_pitchroll_x = s2_s_PitchRollCalcXY(s4_t_glav_minus, s4_t_asp);
        s2_s_pitchroll_y = s2_s_PitchRollCalcXY(s4_t_gwav, s4_t_a);

        u4_s_pitchroll_sigsum_sp1_pre2 = st_s_pitchroll_sig_pre.u4_sp1;
        st_s_pitchroll_sig_pre.u4_gx0  = st_ap_sum->u4_gx0;
        st_s_pitchroll_sig_pre.u4_gy0  = st_ap_sum->u4_gy0;
        st_s_pitchroll_sig_pre.u4_yaw0 = st_ap_sum->u4_yaw0;
        st_s_pitchroll_sig_pre.u4_sp1  = st_ap_sum->u4_sp1;
    }
}

/*===================================================================================================================================*/
/*  static  S4      s4_s_PitchRollCalcG(const U4 u4_a_gsum_las, const U4 u4_a_gsum_pre)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  S4      s4_s_PitchRollCalcG(const U4 u4_a_gsum_las, const U4 u4_a_gsum_pre)
{
/*===================================================================================================================================*/
/*   Front/Rear Direction Acceleration Calculation                                                                                   */
/*                                                                                                                                   */
/*   G = (Gx_avg_las + Gx_avg_pre) / 2                                                                                               */
/*     = (Gx_sum_las + Gx_sum_pre) / 100                                                                                             */
/*     = [(Gx0_sum_las + Gx0_sum_pre) * 0.03589 - 1837.5] / 100                                                                      */
/*     = [(Gx0_sum_las + Gx0_sum_pre) * 3589 - 183750000] / (10^7)              LSB: 1                                               */
/*     = [(Gx0_sum_las + Gx0_sum_pre) * 3589 - 183750000] / 1000                LSB: 0.0001                                          */
/*                                                                                                                                   */
/*    G: Gwav,-Glav                                                                                                                  */
/*    Gx: GW,-GL                                                                                                                     */
/*    Gx0: VSC_GY0,VSC_GX0    LSB: 0.03589    OFFSET: -18.375                                                                        */
/*===================================================================================================================================*/
    static const U4 u4_s_PTHROLCALG_MUL  = (U4)3589U;
    static const S4 s4_s_PTHROLCALG_SUB  = (S4)183750000;
    static const S4 s4_s_PTHROLCALG_DIV  = (S4)1000;

    U4  u4_t_gmul;
    S4  s4_t_g_pmr;

    u4_t_gmul = u4_a_gsum_las + u4_a_gsum_pre;
    u4_t_gmul *= u4_s_PTHROLCALG_MUL;

    if(u4_t_gmul > (U4)S4_MAX){
        s4_t_g_pmr = (S4)S4_MAX;
    }
    else{
        s4_t_g_pmr = (S4)u4_t_gmul;
        s4_t_g_pmr -= s4_s_PTHROLCALG_SUB;
        s4_t_g_pmr = s4_s_PitchRollCalcS4DivRand(s4_t_g_pmr, s4_s_PTHROLCALG_DIV);
    }
    
    return(s4_t_g_pmr);
}

/*===================================================================================================================================*/
/*  static  S4      s4_s_PitchRollCalcAsp(const U4 u4_a_spsum_las, const U4 u4_a_spsum_pre2)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  S4      s4_s_PitchRollCalcAsp(const U4 u4_a_spsum_las, const U4 u4_a_spsum_pre2)
{
/*===================================================================================================================================*/
/*   Acceleration of Vehicle Speed Calculation                                                                                       */
/*                                                                                                                                   */
/*   Asp = (Spav_las - Spav_pre) / (3.6 * 0.5)                                                                                       */
/*       = [(Sp_avg_las + Sp_avg_pre) - (Sp_avg_pre + Sp_avg_pre2)] / (3.6 * 0.5 *2)                                                 */
/*       = (Sp_avg_las - Sp_avg_pre2)  / 3.6                                                                                         */
/*       = (SP1_sum_las - SP1_sum_pre2) * 0.01 / (3.6 * 25)                                                                          */
/*       = (SP1_sum_las - SP1_sum_pre2) / 9000                                          LSB: 1                                       */
/*       = (SP1_sum_las - SP1_sum_pre2) * 10 / 9                                        LSB: 0.0001                                  */
/*                                                                                                                                   */
/*    SP1  LSB: 0.01   OFFSET: 0                                                                                                     */
/*===================================================================================================================================*/
    static const S4 s4_s_PTHROLCALASP_MUL  = (S4)10;
    static const S4 s4_s_PTHROLCALASP_DIV  = (S4)9;

    S4  s4_t_asp_pmr;

    if((u4_a_spsum_las > (U4)S4_MAX) || (u4_a_spsum_pre2 > (U4)S4_MAX)){
        s4_t_asp_pmr = (S4)S4_MAX;
    }
    else{
        s4_t_asp_pmr = (S4)u4_a_spsum_las - (S4)u4_a_spsum_pre2;
        s4_t_asp_pmr *= s4_s_PTHROLCALASP_MUL;
        s4_t_asp_pmr = s4_s_PitchRollCalcS4DivRand(s4_t_asp_pmr, s4_s_PTHROLCALASP_DIV);
    }

    return(s4_t_asp_pmr);
}

/*===================================================================================================================================*/
/*  static S4 s4_s_PitchRollCalcA(const U4 u4_a_yrsum_las, const U4 u4_a_yrsum_pre, const U4 u4_a_spsum_las, const U4 u4_a_spsum_pre)*/
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  S4      s4_s_PitchRollCalcA(const U4 u4_a_yrsum_las, const U4 u4_a_yrsum_pre, const U4 u4_a_spsum_las, const U4 u4_a_spsum_pre)
{
/*===================================================================================================================================*/
/*  Centrifugal Force Calculation                                                                                                    */
/*                                                                                                                                   */
/*  a = w * 3.141592 / 180 * Spav / 3.6                                                                                              */
/*    = w * Spav * 3.141592 / 648                                                                                                    */
/*    = (YR1_avg_las + YR1_avg_pre) * (Sp_avg_las + Sp_avg_pre) * 3.141592 / 2592                                                    */
/*    = (YR1_sum_las + YR1_sum_pre) / 50 * (Sp_sum_las + Sp_sum_pre) / 25 * 3.141592 / 2592                                          */
/*    = (YR1_sum_las + YR1_sum_pre) * (Sp_sum_las + Sp_sum_pre) * 3.141592 / (3.24*10^6)                                             */
/*    = [(YAW0_sum_las + YAW0_sum_pre) * 0.244 - 12500] * (SP1_sum_las + SP1_sum_pre) * 0.01 * 3.141592 / (3.24*10^6)                */
/*    = [(YAW0_sum_las + YAW0_sum_pre) * 244 - (1.25*10^7)] * (SP1_sum_las + SP1_sum_pre) * 392699 / (4.05*10^16)        LSB: 1      */
/*    = [(YAW0_sum_las + YAW0_sum_pre) * 244 - (1.25*10^7)] * (SP1_sum_las + SP1_sum_pre) * 392699 / (4.05*10^12)        LSB: 0.0001 */
/*    = [(YAW0_sum_las + YAW0_sum_pre) * 244 - (1.25*10^7)] /(10^4) * (SP1_sum_las + SP1_sum_pre) * 392699 / (4.05*10^8) LSB: 0.0001 */
/*                                                                                                                                   */
/*   YAW0: VSC_YAW0    LSB: 0.244    OFFSET: -125                                                                                    */
/*   SP1  LSB: 0.01   OFFSET: 0                                                                                                      */
/*===================================================================================================================================*/
    static const U4 u4_s_PTHROLCALA_YRLSB    = (U4)244U;
    static const U4 u4_s_PTHROLCALA_YROFFSET = (U4)12500000U;
    static const U4 u4_s_PTHROLCALA_DIV1     = (U4)10000U;
    static const U4 u4_s_PTHROLCALA_MUL      = (U4)392699U;
    static const U4 u4_s_PTHROLCALA_DIV2     = (U4)405000000U;

    U4  u4_t_yrsum;
    U4  u4_t_spsum;
    S4  s4_t_sign;
    U4  u4_t_a_pmr;
    S4  s4_t_a_pmr;

    u4_t_yrsum = u4_a_yrsum_las + u4_a_yrsum_pre;
    u4_t_yrsum *= u4_s_PTHROLCALA_YRLSB;
    if(u4_t_yrsum < u4_s_PTHROLCALA_YROFFSET){
        s4_t_sign = (S4)-1;
        u4_t_yrsum = u4_s_PTHROLCALA_YROFFSET - u4_t_yrsum;
    }
    else{
        s4_t_sign = (S4)1;
        u4_t_yrsum -= u4_s_PTHROLCALA_YROFFSET;
    }
    u4_t_spsum  = u4_a_spsum_las + u4_a_spsum_pre;
    u4_t_a_pmr = u4_g_PitchRollCfgCalcU8MulDiv(u4_t_yrsum, u4_t_spsum, u4_s_PTHROLCALA_DIV1);
    u4_t_a_pmr = u4_g_PitchRollCfgCalcU8MulDiv(u4_t_a_pmr, u4_s_PTHROLCALA_MUL, u4_s_PTHROLCALA_DIV2);

    if(u4_t_a_pmr > (U4)S4_MAX){
        s4_t_a_pmr = (S4)S4_MAX;
    }
    else{
        s4_t_a_pmr = (S4)u4_t_a_pmr * s4_t_sign;
    }

    return(s4_t_a_pmr);
}

/*===================================================================================================================================*/
/*  static  S2      s2_s_PitchRollCalcXY(const S4 s4_a_accel_pmr, const S4 s4_a_cor_pmr)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  S2      s2_s_PitchRollCalcXY(const S4 s4_a_accel_pmr, const S4 s4_a_cor_pmr)
{
    static const S4 s4_s_PTHROLCALSIN_DIV = (S4)98;

    S4  s4_t_sine_pml;
    U2  u2_t_sine;
    U2  u2_t_radian;
    U2  u2_t_ang;
    S2  s2_t_ang_pct;
    

    s4_t_sine_pml = s4_a_accel_pmr - s4_a_cor_pmr;
    s4_t_sine_pml = s4_s_PitchRollCalcS4DivRand(s4_t_sine_pml, s4_s_PTHROLCALSIN_DIV);

    if((s4_t_sine_pml > (S4)PITCHROLL_SINE_MAX) ||
        (s4_t_sine_pml < (S4)PITCHROLL_SINE_MIN)){
        s2_t_ang_pct = (S2)S2_MAX;
    }
    else if(s4_t_sine_pml < (S4)0){
        /* PITCHROLL_SINE_MIN(-1000) <= s4_t_sine_pml < 0 */
        u2_t_sine = (U2)(S2)(-s4_t_sine_pml);
        u2_t_radian = u2_s_PitchRollArcsin(u2_t_sine);
        u2_t_ang = u2_s_PitchRollRadToAng(u2_t_radian);
        if(u2_t_ang < (U2)S2_MAX){
            s2_t_ang_pct = -((S2)u2_t_ang);
        }
        else{
            s2_t_ang_pct = (S2)S2_MIN;
        }
    }
    else{
        /* 0 <= s4_t_sine_pml <= PITCHROLL_SINE_MAX(1000) */
        u2_t_sine = (U2)(S2)s4_t_sine_pml;
        u2_t_radian = u2_s_PitchRollArcsin(u2_t_sine);
        u2_t_ang = u2_s_PitchRollRadToAng(u2_t_radian);
        if(u2_t_ang < (U2)S2_MAX){
            s2_t_ang_pct = (S2)u2_t_ang;
        }
        else{
            s2_t_ang_pct = (S2)S2_MAX;
        }
    }
    
    return(s2_t_ang_pct);
}

/*===================================================================================================================================*/
/*  static  U2      u2_s_PitchRollRadToAng(const U2 u2_a_rad_pml)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_PitchRollRadToAng(const U2 u2_a_rad_pml)
{
/*===================================================================================================================================*/
/*   Radian to Angle Convert                                                                                                         */
/*                                                                                                                                   */
/*   ang = rad * 180 / 3.141592                 LSB: 0.001                                                                           */
/*       = rad * (2.25*10^7) / 392699           LSB: 0.001                                                                           */
/*       = rad * (2.25*10^6) / 392699           LSB: 0.01                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
    static const U4 u4_s_PTHROLRAD2ANG_MUL = (U4)2250000U;
    static const U4 u4_s_PTHROLRAD2ANG_DIV = (U4)392699U;
    U4  u4_t_ang;
    U2  u2_t_ang_pct;

    u4_t_ang = u4_g_PitchRollCfgCalcU8MulDiv((U4)u2_a_rad_pml, u4_s_PTHROLRAD2ANG_MUL, u4_s_PTHROLRAD2ANG_DIV);
    if(u4_t_ang < (U4)U2_MAX){
        u2_t_ang_pct = (U2)u4_t_ang;
    }
    else{
        u2_t_ang_pct = (U2)U2_MAX;
    }

    return(u2_t_ang_pct);
}

/*===================================================================================================================================*/
/*  static  U2      u2_s_PitchRollArcsin(const U2 u2_a_sin_pml)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_PitchRollArcsin(const U2 u2_a_sin_pml)
{
    U2  u2_t_radian_pml;

    if(u2_a_sin_pml > (U2)PITCHROLL_SINE_MAX){
        u2_t_radian_pml = (U2)U2_MAX;
    }
    else{
        u2_t_radian_pml = u2_sp_PITCHROLL_ARCSIN[u2_a_sin_pml];
    }

    return(u2_t_radian_pml);
}

/*===================================================================================================================================*/
/*  static  S4      s4_s_PitchRollCalcS4DivRand(const S4 s4_a_dividend, const S4 s4_a_divisor)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  S4      s4_s_PitchRollCalcS4DivRand(const S4 s4_a_dividend, const S4 s4_a_divisor)
{
    S4  s4_t_divd_abs;
    S4  s4_t_divs_abs;
    S4  s4_t_sign;
    S4  s4_t_rand;
    S4  s4_t_rslt;

    if(s4_a_divisor != (S4)0){
        if(s4_a_dividend < (S4)0){
            s4_t_divd_abs = -s4_a_dividend;
            s4_t_sign = (S4)-1;
        }
        else{
            s4_t_divd_abs = s4_a_dividend;
            s4_t_sign = (S4)1;
        }
        if(s4_a_divisor < (S4)0){
            s4_t_divs_abs = -s4_a_divisor;
            s4_t_sign = -s4_t_sign;
        }
        else{
            s4_t_divs_abs = s4_a_divisor;
        }

        s4_t_rand = s4_t_divs_abs / (S4)2;
        s4_t_rslt = s4_t_divd_abs + s4_t_rand;
        s4_t_rslt = s4_t_rslt / s4_t_divs_abs;
        s4_t_rslt *= s4_t_sign;
    }
    else{
        s4_t_rslt = (S4)S4_MAX;
    }

    return(s4_t_rslt);
}

/*===================================================================================================================================*/
/*  static  U1      u1_s_PitchRollDispAngUpdate(const S2 s2_a_ang, const S2 s2_a_ang_pre, U1 * const u1_ap_curtdisp)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_PitchRollDispAngUpdate(const S2 s2_a_ang, const S2 s2_a_ang_pre, U1 * const u1_ap_curtdisp)
{
    U2      u2_t_ang_abs;
    U1      u1_t_disp_abs;
    U1      u1_t_disp_fail;

    if(s2_a_ang < (S2)0){
        u2_t_ang_abs = (U2)(-s2_a_ang);
    }
    else{
        u2_t_ang_abs = (U2)s2_a_ang;
    }

    if(((s2_a_ang > (S2)0) && (s2_a_ang_pre < (S2)0)) ||
       ((s2_a_ang < (S2)0) && (s2_a_ang_pre > (S2)0))){
        u1_t_disp_abs = (U1)0U;
    }
    else{
        if((*u1_ap_curtdisp) < u1_g_PITCHROLL_DSPANG_ABS_MAX){
            u1_t_disp_abs = u1_g_PITCHROLL_DSPANG_ABS_MAX - (*u1_ap_curtdisp);
        }
        else{
            u1_t_disp_abs = (*u1_ap_curtdisp) - u1_g_PITCHROLL_DSPANG_ABS_MAX;
        }
    }

    u1_t_disp_abs = (U1)u2_g_PitchRollCfgRngCmprU2((U2)u1_t_disp_abs, u2_t_ang_abs);
    if(u1_t_disp_abs > u1_g_PITCHROLL_DSPANG_ABS_MAX){
        u1_t_disp_abs = u1_g_PITCHROLL_DSPANG_ABS_MAX;
    }

    if(s2_a_ang < (S2)0){
        (*u1_ap_curtdisp) = u1_g_PITCHROLL_DSPANG_ABS_MAX - u1_t_disp_abs;
    }
    else{
        (*u1_ap_curtdisp) = u1_g_PITCHROLL_DSPANG_ABS_MAX + u1_t_disp_abs;
    }

    if(u1_t_disp_abs > (u1_g_PITCHROLL_DSPANG_ABS_MAX - (U1)PITCHROLL_DISPANG_OFFSET)){
        u1_t_disp_fail = (U1)TRUE;
    }
    else{
        u1_t_disp_fail = (U1)FALSE;
    }

    return(u1_t_disp_fail);
}


/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    09/30/2022  TX       New.                                                                                               */
/*                                                                                                                                   */
/*  * TX   = Tong Xinyuan, DNST                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
