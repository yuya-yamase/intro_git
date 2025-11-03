/* 2.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Ambient Illuminance                                                                                                              */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HDIMILLMN_C_MAJOR                        (2)
#define HDIMILLMN_C_MINOR                        (1)
#define HDIMILLMN_C_PATCH                        (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hdimmgr_cfg_private.h"

#include "oxcan.h"

/* #include "illmnsnsr.h" */
#ifdef ILLMNSNSR_H
#include "calc_u8.h"
#endif /* ILLMNSNSR_H */
#include "memfill_u4.h"
#include "veh_opemd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HDIMILLMN_C_MAJOR != HDIMILLMN_H_MAJOR) || \
     (HDIMILLMN_C_MINOR != HDIMILLMN_H_MINOR) || \
     (HDIMILLMN_C_PATCH != HDIMILLMN_H_PATCH))
#error "hdimillmn.c and hdimillmn_cfg_private.h are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ++++ N_LX_IMPREMENTATION START ++++ */
typedef struct
{
    U2 u2_rcvdata;      /* N_LX   */
    U4 u4_lx;           /* Illuminance Value */
}ST_HDIMILLMN_CNLGHT;
/* ++++ N_LX_IMPREMENTATION STOP  ++++ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HDIMILLMN_MAX_LXDATA                    (50000*HDIMILLMN_LXLSB)          /* Max Illuminance                                  */
#define HDIMILLMN_DEF_LXDATA                    (70*HDIMILLMN_LXLSB)             /* Default Illuminance                              */

#define HDIMILLMN_UPDT_NON                      (0x00)
#define HDIMILLMN_UPDT_ILLMNSNSR                (0x01)

/* ++++ N_LX_IMPREMENTATION START ++++ */
#define HDIMILLMN_CNLGHT_LXDATA_FAIL            (0xffff)                         /* N_LX: Fail data                                  */
#define HDIMILLMN_CNLGHT_LXDATA_INIT            (0x1ffe)                         /* N_LX: Initial data                               */
#define HDIMILLMN_CNLGHT_LXDATA_ERROR           (0x1fff)                         /* N_LX: Error data                                 */
#define HDIMILLMN_CNLGHT_LXDATA_JUDGE_ERR       (HDIMILLMN_CNLGHT_LXDATA_INIT)   /* N_LX: Judgement data for Error                   */

#define HDIMILLMN_CNLGHT_JUDNLX                 (1000*HDIMILLMN_LXLSB)           /* N_LX:  Judgment data for illuminance calculation */
#define HDIMILLMN_CNLGHT_GURDLX                 (0x7fffffff)                     /* N_LX:  N_LX Guard Value                          */

#define HDIMILLMN_CNLGHT_HYS_ADDEP              (8)                              /* Hysterisis: Depth                                */
#define HDIMILLMN_CNLGHT_HYS_ADWID              (1)                              /* Hysterisis: Width                                */
#if (HDIMILLMN_CNLGHT_HYS_ADWID != 1)
#error "Rethink u2_s_HdimillmnCnlghtHysID if changing HDIMILLMN_CNLGHT_HYS_ADWID."
#endif

#define HDIMILLMN_CNLGHT_MOVCAL_MAX             (U1_MAX)                         /* Moving average max count                         */
#define HDIMILLMN_CNLGHT_VALID_SPDKMH           (175)                            /* Speed value(LSB:0.01km/h)                        */
#define HDIMILLMN_CNLGHT_MOVAVE_DIV_MIN         (1)                              /* Moving average count:Division Minimum            */
/* ++++ N_LX_IMPREMENTATION STOP  ++++ */

#define HDIMILLMN_ILMDAT_UPDT_TIM               (15)                             /* illuminance data Update Times    :300ms/LSB=20ms */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4   u4_s_hdimillm_illmnsnsr;                                            /* hdimillmn.c:input  (Illuminance Sensor)           */
static U4   u4_s_hdimillm_illmn;                                                /* hdimillmn.c:output (Ambient Illuminance)          */

static U1   u1_s_hdimillm_illmnsnsrsts;
static U1   u1_s_hdimillm_illmnsts;

static U1   u1_s_hdimillm_updt;

/* ++++ N_LX_IMPREMENTATION START ++++ */
static U1   u1_s_hdimillm_cnlghtsts;

static S2   s2_s_hdimillm_cnlght_hys_cnt;
static U2   u2_s_hdimillm_cnlght_id;

static U4   u4_s_hdimillm_cnlght;                                               /* hdimillmn.c:input  (Conlight Sensor)              */

static U1   u1_s_hdimillm_cnlght_iniflg;
static U2   u2_s_hdimillm_cnlght_cnt;

static U4   u4_s_hdimillm_cnlght_calsum;
static U4   u4_s_hdimillm_cnlght_calbuf[HDIMILLMN_CNLGHT_MOVCAL_MAX];

static U2   u2_s_hdimillm_cnlght_rcvdata;
/* ++++ N_LX_IMPREMENTATION STOP  ++++ */

#ifdef ILLMNSNSR_H
#else
static U1   u1_s_hdimillm_illmn_updt_cnt;
#endif /* ILLMNSNSRH */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4    u4_g_HDIMILLMN_MAX_LXDATA = (U4)HDIMILLMN_MAX_LXDATA;
const U4    u4_g_HDIMILLMN_DEF_LXDATA = (U4)HDIMILLMN_DEF_LXDATA;

/* ++++ N_LX_IMPREMENTATION START ++++ */
#define HDIMILLMN_CNLGHT_MAX_CONTBL             (393)
static const ST_HDIMILLMN_CNLGHT st_TBL_HDIMILLMN_CNLGHT[HDIMILLMN_CNLGHT_MAX_CONTBL] =
{
/*  N_LX        Illuminance value of instrument panel(LSB:0.01lx) */
    {(U2)1,     (U4)100},
    {(U2)1,     (U4)103},
    {(U2)1,     (U4)105},
    {(U2)1,     (U4)108},
    {(U2)1,     (U4)111},
    {(U2)1,     (U4)113},
    {(U2)1,     (U4)116},
    {(U2)1,     (U4)119},
    {(U2)1,     (U4)122},
    {(U2)1,     (U4)126},
    {(U2)1,     (U4)129},
    {(U2)1,     (U4)132},
    {(U2)1,     (U4)135},
    {(U2)1,     (U4)139},
    {(U2)1,     (U4)142},
    {(U2)1,     (U4)146},
    {(U2)1,     (U4)150},
    {(U2)1,     (U4)154},
    {(U2)1,     (U4)158},
    {(U2)1,     (U4)162},
    {(U2)1,     (U4)166},
    {(U2)1,     (U4)170},
    {(U2)1,     (U4)174},
    {(U2)1,     (U4)179},
    {(U2)1,     (U4)183},
    {(U2)2,     (U4)188},
    {(U2)2,     (U4)193},
    {(U2)2,     (U4)198},
    {(U2)2,     (U4)203},
    {(U2)2,     (U4)208},
    {(U2)2,     (U4)213},
    {(U2)2,     (U4)219},
    {(U2)2,     (U4)224},
    {(U2)2,     (U4)230},
    {(U2)2,     (U4)236},
    {(U2)2,     (U4)242},
    {(U2)2,     (U4)248},
    {(U2)2,     (U4)255},
    {(U2)2,     (U4)261},
    {(U2)2,     (U4)268},
    {(U2)2,     (U4)275},
    {(U2)2,     (U4)282},
    {(U2)2,     (U4)289},
    {(U2)2,     (U4)296},
    {(U2)2,     (U4)304},
    {(U2)2,     (U4)312},
    {(U2)3,     (U4)320},
    {(U2)3,     (U4)328},
    {(U2)3,     (U4)336},
    {(U2)3,     (U4)345},
    {(U2)3,     (U4)354},
    {(U2)3,     (U4)363},
    {(U2)3,     (U4)372},
    {(U2)3,     (U4)382},
    {(U2)3,     (U4)391},
    {(U2)3,     (U4)401},
    {(U2)3,     (U4)412},
    {(U2)3,     (U4)422},
    {(U2)3,     (U4)433},
    {(U2)4,     (U4)444},
    {(U2)4,     (U4)455},
    {(U2)4,     (U4)467},
    {(U2)4,     (U4)479},
    {(U2)4,     (U4)491},
    {(U2)4,     (U4)504},
    {(U2)4,     (U4)517},
    {(U2)4,     (U4)530},
    {(U2)4,     (U4)543},
    {(U2)4,     (U4)557},
    {(U2)5,     (U4)572},
    {(U2)5,     (U4)586},
    {(U2)5,     (U4)601},
    {(U2)5,     (U4)617},
    {(U2)5,     (U4)632},
    {(U2)5,     (U4)649},
    {(U2)5,     (U4)665},
    {(U2)5,     (U4)682},
    {(U2)6,     (U4)700},
    {(U2)6,     (U4)717},
    {(U2)6,     (U4)736},
    {(U2)6,     (U4)755},
    {(U2)6,     (U4)774},
    {(U2)6,     (U4)794},
    {(U2)7,     (U4)814},
    {(U2)7,     (U4)835},
    {(U2)7,     (U4)856},
    {(U2)7,     (U4)878},
    {(U2)7,     (U4)901},
    {(U2)7,     (U4)924},
    {(U2)8,     (U4)947},
    {(U2)8,     (U4)972},
    {(U2)8,     (U4)996},
    {(U2)8,     (U4)1022},
    {(U2)8,     (U4)1048},
    {(U2)9,     (U4)1075},
    {(U2)9,     (U4)1102},
    {(U2)9,     (U4)1131},
    {(U2)9,     (U4)1160},
    {(U2)10,    (U4)1189},
    {(U2)10,    (U4)1220},
    {(U2)10,    (U4)1251},
    {(U2)10,    (U4)1283},
    {(U2)11,    (U4)1316},
    {(U2)11,    (U4)1349},
    {(U2)11,    (U4)1384},
    {(U2)11,    (U4)1419},
    {(U2)12,    (U4)1456},
    {(U2)12,    (U4)1493},
    {(U2)12,    (U4)1531},
    {(U2)13,    (U4)1570},
    {(U2)13,    (U4)1610},
    {(U2)13,    (U4)1652},
    {(U2)14,    (U4)1694},
    {(U2)14,    (U4)1737},
    {(U2)14,    (U4)1782},
    {(U2)15,    (U4)1827},
    {(U2)15,    (U4)1874},
    {(U2)15,    (U4)1922},
    {(U2)16,    (U4)1971},
    {(U2)16,    (U4)2021},
    {(U2)17,    (U4)2073},
    {(U2)17,    (U4)2126},
    {(U2)17,    (U4)2181},
    {(U2)18,    (U4)2236},
    {(U2)18,    (U4)2294},
    {(U2)19,    (U4)2352},
    {(U2)19,    (U4)2413},
    {(U2)20,    (U4)2474},
    {(U2)20,    (U4)2538},
    {(U2)21,    (U4)2602},
    {(U2)21,    (U4)2669},
    {(U2)22,    (U4)2737},
    {(U2)22,    (U4)2807},
    {(U2)23,    (U4)2879},
    {(U2)24,    (U4)2953},
    {(U2)24,    (U4)3028},
    {(U2)25,    (U4)3106},
    {(U2)25,    (U4)3185},
    {(U2)26,    (U4)3267},
    {(U2)27,    (U4)3351},
    {(U2)27,    (U4)3436},
    {(U2)28,    (U4)3524},
    {(U2)29,    (U4)3614},
    {(U2)30,    (U4)3707},
    {(U2)30,    (U4)3802},
    {(U2)31,    (U4)3899},
    {(U2)32,    (U4)3999},
    {(U2)33,    (U4)4101},
    {(U2)34,    (U4)4206},
    {(U2)35,    (U4)4314},
    {(U2)35,    (U4)4424},
    {(U2)36,    (U4)4537},
    {(U2)37,    (U4)4653},
    {(U2)38,    (U4)4772},
    {(U2)39,    (U4)4894},
    {(U2)40,    (U4)5020},
    {(U2)41,    (U4)5148},
    {(U2)42,    (U4)5280},
    {(U2)43,    (U4)5415},
    {(U2)44,    (U4)5553},
    {(U2)46,    (U4)5695},
    {(U2)47,    (U4)5841},
    {(U2)48,    (U4)5991},
    {(U2)49,    (U4)6144},
    {(U2)50,    (U4)6301},
    {(U2)52,    (U4)6462},
    {(U2)53,    (U4)6628},
    {(U2)54,    (U4)6797},
    {(U2)56,    (U4)6971},
    {(U2)57,    (U4)7149},
    {(U2)59,    (U4)7332},
    {(U2)60,    (U4)7520},
    {(U2)62,    (U4)7712},
    {(U2)63,    (U4)7910},
    {(U2)65,    (U4)8112},
    {(U2)67,    (U4)8320},
    {(U2)68,    (U4)8532},
    {(U2)70,    (U4)8751},
    {(U2)72,    (U4)8975},
    {(U2)74,    (U4)9204},
    {(U2)76,    (U4)9440},
    {(U2)77,    (U4)9681},
    {(U2)79,    (U4)9929},
    {(U2)81,    (U4)10183},
    {(U2)84,    (U4)10444},
    {(U2)86,    (U4)10711},
    {(U2)88,    (U4)10985},
    {(U2)90,    (U4)11266},
    {(U2)92,    (U4)11554},
    {(U2)95,    (U4)11850},
    {(U2)97,    (U4)12153},
    {(U2)100,   (U4)12464},
    {(U2)102,   (U4)12783},
    {(U2)105,   (U4)13110},
    {(U2)108,   (U4)13445},
    {(U2)110,   (U4)13789},
    {(U2)113,   (U4)14142},
    {(U2)116,   (U4)14504},
    {(U2)119,   (U4)14875},
    {(U2)122,   (U4)15256},
    {(U2)125,   (U4)15646},
    {(U2)128,   (U4)16046},
    {(U2)132,   (U4)16457},
    {(U2)135,   (U4)16878},
    {(U2)138,   (U4)17310},
    {(U2)142,   (U4)17753},
    {(U2)146,   (U4)18207},
    {(U2)149,   (U4)18673},
    {(U2)153,   (U4)19150},
    {(U2)157,   (U4)19640},
    {(U2)161,   (U4)20143},
    {(U2)165,   (U4)20658},
    {(U2)169,   (U4)21187},
    {(U2)174,   (U4)21729},
    {(U2)178,   (U4)22285},
    {(U2)183,   (U4)22855},
    {(U2)188,   (U4)23440},
    {(U2)192,   (U4)24040},
    {(U2)197,   (U4)24655},
    {(U2)202,   (U4)25285},
    {(U2)207,   (U4)25932},
    {(U2)213,   (U4)26596},
    {(U2)218,   (U4)27276},
    {(U2)224,   (U4)27974},
    {(U2)230,   (U4)28690},
    {(U2)235,   (U4)29424},
    {(U2)241,   (U4)30177},
    {(U2)248,   (U4)30949},
    {(U2)254,   (U4)31741},
    {(U2)260,   (U4)32553},
    {(U2)267,   (U4)33386},
    {(U2)274,   (U4)34240},
    {(U2)281,   (U4)35116},
    {(U2)288,   (U4)36015},
    {(U2)295,   (U4)36936},
    {(U2)303,   (U4)37881},
    {(U2)311,   (U4)38850},
    {(U2)319,   (U4)39844},
    {(U2)327,   (U4)40864},
    {(U2)335,   (U4)41909},
    {(U2)344,   (U4)42982},
    {(U2)353,   (U4)44081},
    {(U2)362,   (U4)45209},
    {(U2)371,   (U4)46366},
    {(U2)380,   (U4)47552},
    {(U2)390,   (U4)48769},
    {(U2)400,   (U4)50017},
    {(U2)410,   (U4)51297},
    {(U2)421,   (U4)52609},
    {(U2)432,   (U4)53955},
    {(U2)443,   (U4)55335},
    {(U2)454,   (U4)56751},
    {(U2)466,   (U4)58203},
    {(U2)478,   (U4)59693},
    {(U2)490,   (U4)61220},
    {(U2)502,   (U4)62786},
    {(U2)515,   (U4)64393},
    {(U2)528,   (U4)66040},
    {(U2)542,   (U4)67730},
    {(U2)556,   (U4)69463},
    {(U2)570,   (U4)71240},
    {(U2)585,   (U4)73063},
    {(U2)599,   (U4)74932},
    {(U2)615,   (U4)76849},
    {(U2)631,   (U4)78816},
    {(U2)647,   (U4)80832},
    {(U2)663,   (U4)82900},
    {(U2)680,   (U4)85021},
    {(U2)698,   (U4)87197},
    {(U2)715,   (U4)89428},
    {(U2)734,   (U4)91716},
    {(U2)752,   (U4)94062},
    {(U2)772,   (U4)96469},
    {(U2)791,   (U4)98937},
    {(U2)812,   (U4)101469},
    {(U2)833,   (U4)104065},
    {(U2)854,   (U4)106727},
    {(U2)876,   (U4)109458},
    {(U2)898,   (U4)112259},
    {(U2)921,   (U4)115131},
    {(U2)945,   (U4)118077},
    {(U2)969,   (U4)121098},
    {(U2)994,   (U4)124196},
    {(U2)1019,  (U4)127374},
    {(U2)1045,  (U4)130633},
    {(U2)1072,  (U4)133975},
    {(U2)1099,  (U4)137403},
    {(U2)1127,  (U4)140919},
    {(U2)1156,  (U4)144524},
    {(U2)1186,  (U4)148222},
    {(U2)1216,  (U4)152014},
    {(U2)1247,  (U4)155904},
    {(U2)1279,  (U4)159893},
    {(U2)1312,  (U4)163984},
    {(U2)1345,  (U4)168179},
    {(U2)1380,  (U4)172482},
    {(U2)1415,  (U4)176895},
    {(U2)1451,  (U4)181421},
    {(U2)1489,  (U4)186063},
    {(U2)1527,  (U4)190824},
    {(U2)1566,  (U4)195706},
    {(U2)1606,  (U4)200714},
    {(U2)1647,  (U4)205849},
    {(U2)1689,  (U4)211116},
    {(U2)1732,  (U4)216517},
    {(U2)1776,  (U4)222057},
    {(U2)1822,  (U4)227739},
    {(U2)1869,  (U4)233566},
    {(U2)1916,  (U4)239541},
    {(U2)1965,  (U4)245670},
    {(U2)2016,  (U4)251956},
    {(U2)2067,  (U4)258403},
    {(U2)2120,  (U4)265014},
    {(U2)2174,  (U4)271795},
    {(U2)2230,  (U4)278749},
    {(U2)2287,  (U4)285881},
    {(U2)2346,  (U4)293195},
    {(U2)2406,  (U4)300697},
    {(U2)2467,  (U4)308390},
    {(U2)2530,  (U4)316281},
    {(U2)2595,  (U4)324373},
    {(U2)2661,  (U4)332673},
    {(U2)2729,  (U4)341184},
    {(U2)2799,  (U4)349914},
    {(U2)2871,  (U4)358867},
    {(U2)2944,  (U4)368048},
    {(U2)3002,  (U4)377465},
    {(U2)3007,  (U4)387123},
    {(U2)3012,  (U4)397028},
    {(U2)3017,  (U4)407186},
    {(U2)3022,  (U4)417604},
    {(U2)3027,  (U4)428289},
    {(U2)3033,  (U4)439247},
    {(U2)3038,  (U4)450486},
    {(U2)3044,  (U4)462012},
    {(U2)3050,  (U4)473833},
    {(U2)3056,  (U4)485956},
    {(U2)3062,  (U4)498390},
    {(U2)3069,  (U4)511142},
    {(U2)3075,  (U4)524220},
    {(U2)3082,  (U4)537632},
    {(U2)3089,  (U4)551388},
    {(U2)3096,  (U4)565496},
    {(U2)3103,  (U4)579964},
    {(U2)3110,  (U4)594803},
    {(U2)3118,  (U4)610022},
    {(U2)3126,  (U4)625630},
    {(U2)3134,  (U4)641637},
    {(U2)3142,  (U4)658054},
    {(U2)3150,  (U4)674891},
    {(U2)3159,  (U4)692158},
    {(U2)3168,  (U4)709868},
    {(U2)3177,  (U4)728030},
    {(U2)3186,  (U4)746657},
    {(U2)3196,  (U4)765761},
    {(U2)3206,  (U4)785354},
    {(U2)3216,  (U4)805448},
    {(U2)3226,  (U4)826056},
    {(U2)3237,  (U4)847191},
    {(U2)3247,  (U4)868867},
    {(U2)3259,  (U4)891098},
    {(U2)3270,  (U4)913898},
    {(U2)3282,  (U4)937280},
    {(U2)3294,  (U4)961262},
    {(U2)3306,  (U4)985856},
    {(U2)3319,  (U4)1011080},
    {(U2)3331,  (U4)1036949},
    {(U2)3345,  (U4)1063481},
    {(U2)3358,  (U4)1090691},
    {(U2)3372,  (U4)1118597},
    {(U2)3387,  (U4)1147217},
    {(U2)3401,  (U4)1176570},
    {(U2)3416,  (U4)1206673},
    {(U2)3432,  (U4)1237547},
    {(U2)3448,  (U4)1269211},
    {(U2)3464,  (U4)1301685},
    {(U2)3480,  (U4)1334989},
    {(U2)3498,  (U4)1369146},
    {(U2)3515,  (U4)1404177},
    {(U2)3533,  (U4)1440104},
    {(U2)3551,  (U4)1476950},
    {(U2)3570,  (U4)1514739},
    {(U2)3590,  (U4)1553495},
    {(U2)3610,  (U4)1593242},
    {(U2)3630,  (U4)1634007},
    {(U2)3651,  (U4)1675814},
    {(U2)3672,  (U4)1718691},
    {(U2)3694,  (U4)1762666},
    {(U2)3717,  (U4)1807765},
    {(U2)3740,  (U4)1854018},
    {(U2)3764,  (U4)1901455},
    {(U2)3788,  (U4)1950105},
    {(U2)3813,  (U4)2000000}
};
/* ++++ N_LX_IMPREMENTATION STOP  ++++ */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_HdimillmnSnsrUpdt(const U1 u1_a_UDPTFLG);

/* ++++ N_LX_IMPREMENTATION START ++++ */
static void vd_s_HdimillmnCnlghtUpdt(void);
static U2   u2_s_HdimillmnCnlght_IdCal(const U2 u2_a_DATA);
static U2   u2_s_HdimillmnCnlghtHysID(const U2 u2_a_OLD, const U2 u2_a_NEW, S2 *s2_ap_cnt);
static U4   u4_s_HdimillmnCnlght_LxCal(const U2 u2_a_ID);
static U4   u4_s_HdimillmnCnlghtInptAveCal(const U4 u4_a_LX);
static U2   u2_s_HdimillmnCnlghtGet_N_LX(void);
/* ++++ N_LX_IMPREMENTATION STOP  ++++ */

static U1   u1_s_HdimillmnCalUpdt(const U1 u1_a_SNSRUPDT);
#ifdef ILLMNSNSR_H
static U4   u4_s_HdimillmnCalAdjIllmn(const U4 u4_a_ILLMN, const U4 u4_a_ILLMNSNSR, const U4 u4_a_CNLGHTSNSR);
static U4   u4_s_HdimillmnLxCal(const U4 u4_a_ILLMN);
#endif /* ILLMNSNSR_H */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  Initialize                                                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void    vd_g_HdimillmnInit(void)
{
    u4_s_hdimillm_illmnsnsr = u4_g_HDIMILLMN_DEF_LXDATA;

    u1_s_hdimillm_illmnsnsrsts = (U1)HDIMMGR_INSTS_UNDET;

    u1_s_hdimillm_updt = (U1)HDIMILLMN_UPDT_NON;

    /* ++++ N_LX_IMPREMENTATION START ++++ */
    u1_s_hdimillm_cnlghtsts = (U1)HDIMMGR_INSTS_UNDET;

    s2_s_hdimillm_cnlght_hys_cnt = (S2)0;
    u2_s_hdimillm_cnlght_id = (U2)0;

    u4_s_hdimillm_cnlght = (U4)0;

    u1_s_hdimillm_cnlght_iniflg = (U1)FALSE;
    u2_s_hdimillm_cnlght_cnt = (U2)0;
    u4_s_hdimillm_cnlght_calsum = (U4)0;
    vd_g_MemfillU4(&u4_s_hdimillm_cnlght_calbuf[0], (U4)0, (U4)HDIMILLMN_CNLGHT_MOVCAL_MAX);

    u2_s_hdimillm_cnlght_rcvdata = (U2)HDIMILLMN_CNLGHT_LXDATA_INIT;
    /* ++++ N_LX_IMPREMENTATION STOP  ++++ */

    u4_s_hdimillm_illmn = u4_g_HDIMILLMN_DEF_LXDATA;
    u1_s_hdimillm_illmnsts = (U1)HDIMMGR_INSTS_NML;

#ifdef ILLMNSNSR_H
#else
    u1_s_hdimillm_illmn_updt_cnt = (U1)0;
#endif /* ILLMNSNSR_H */
}

/*===================================================================================================================================*/
/*  HudDimmer Illuminance Update                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void    vd_g_HdimillmnUpdt(void)
{
    U1  u1_t_is_cal_updt;
    U1  u1_t_is_snsr_updt;

    u1_t_is_snsr_updt = u1_s_HdimillmnSnsrUpdt(u1_s_hdimillm_updt);
    u1_s_hdimillm_updt = (U1)HDIMILLMN_UPDT_NON;
    vd_s_HdimillmnCnlghtUpdt();

    u1_t_is_cal_updt = u1_s_HdimillmnCalUpdt(u1_t_is_snsr_updt);

    if(u1_t_is_cal_updt == (U1)TRUE){
        /* setting dimadj hook function */
        vd_g_HdimadjHookIllmnCalUpdt();
    }
}

/*===================================================================================================================================*/
/*  HudDimmer Illuminance Data                                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   * u4_a_illmn:Illuminance Data                                                                                        */
/*  Return      u1_s_hdimillm_illmnsts:Ambient Illuminance Status                                                                    */
/*===================================================================================================================================*/
U1    u1_g_HdimillmnGetIllmnVal(U4 * u4_a_illmn)
{
    (*u4_a_illmn) = u4_s_hdimillm_illmn;

    return(u1_s_hdimillm_illmnsts);
}

/*===================================================================================================================================*/
/*  HudDimmer Illuminance Sensor Data                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   * u4_a_illmn:Illuminance Sensor Data                                                                                 */
/*  Return      u1_s_hdimillm_illmnsnsrsts:Illuminance Sensor Status                                                                 */
/*===================================================================================================================================*/
U1    u1_g_HdimillmnGetIllmnSnsrVal(U4 * u4_a_illmn)
{
    (*u4_a_illmn) = u4_s_hdimillm_illmnsnsr;

    return(u1_s_hdimillm_illmnsnsrsts);
}

/*===================================================================================================================================*/
/*  HudDimmer Conlight Sensor Data                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   * u4_a_illmn:Conlight Sensor Data                                                                                    */
/*  Return      u1_s_hdimillm_cnlghtsts:Conlight Sensor Status                                                                       */
/*===================================================================================================================================*/
U1    u1_g_HdimillmnGetCnlghtSnsrRawVal(U4 * u4_a_illmn)
{
    U2  u2_t_nlx_id;
    U4  u4_t_illmn;

    u2_t_nlx_id = u2_s_HdimillmnCnlght_IdCal(u2_s_hdimillm_cnlght_rcvdata);
    u4_t_illmn  = u4_s_HdimillmnCnlght_LxCal(u2_t_nlx_id);

    (*u4_a_illmn) = u4_t_illmn;

    return(u1_s_hdimillm_cnlghtsts);
}

/*===================================================================================================================================*/
/*  HudDimmer Illuminance Raw Data                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      u2_t_ret : HudDimmer Illuminance Raw Data(LSB:Lx)                                                                    */
/*===================================================================================================================================*/
U2    u2_g_HdimillmnGetIllmnRawVal(void)
{
#ifdef ILLMNSNSR_H
    U4 u4_t_illmn_raw;
    U4 u4_t_illmn_k;
    U4 u4_t_illmn;

    U2 u2_t_ret;

    u4_t_illmn_raw = u4_g_IllmnSnsrGetRawValue();                                                     /* LSB (0.1Lx)                 */
    u4_t_illmn_k = u4_s_HdimillmnLxCal(u4_t_illmn_raw);                                               /* LSB (0.01Lx)                */

    u4_t_illmn = u4_t_illmn_k / (U4)HDIMILLMN_LXLSB;                                                  /* LSB (Lx)                    */

    if(u4_t_illmn > (U4)U2_MAX){
        u2_t_ret = (U2)U2_MAX;
    }
    else{
        u2_t_ret = (U2)u4_t_illmn;
    }

    return (u2_t_ret);
#else
    return ((U2)0);
#endif /* ILLMNSNSR_H */
}

/*===================================================================================================================================*/
/*  HudDimmer Illuminance Sensor Update Hook                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void    vd_g_HdimillmnHookIllmnSnsrUpdt(void)
{
    u1_s_hdimillm_updt |= (U1)HDIMILLMN_UPDT_ILLMNSNSR;
}

/*===================================================================================================================================*/
/*  HudDimmer Illuminance Update                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   u1_a_UDPTFLG:Sensor Update Information                                                                               */
/*  Return      u1_t_is_calprmt:TRUE:Illuminance Caluclation Permit,FALSEIlluminance Caluclation No Permit                           */
/*===================================================================================================================================*/
static U1 u1_s_HdimillmnSnsrUpdt(const U1 u1_a_UDPTFLG)
{
#ifdef ILLMNSNSR_H
    U4  u4_t_illmn;

    U1  u1_t_sts;
    U1  u1_t_is_calprmt;

    u1_t_is_calprmt = (U1)FALSE;
    /* Illuminance Sensor SFH5711 */
    u1_t_sts = u1_g_IllmnSnsrGetDvcSts();
    if((u1_a_UDPTFLG & (U1)HDIMILLMN_UPDT_ILLMNSNSR) == (U1)HDIMILLMN_UPDT_ILLMNSNSR){
        u1_t_is_calprmt = (U1)TRUE;

        switch(u1_t_sts){
            case (U1)ILLMNSNSR_DVCSTS_NML:
                u1_s_hdimillm_illmnsnsrsts = (U1)HDIMMGR_INSTS_NML;
                u4_t_illmn = u4_g_IllmnSnsrGetValue();
                u4_s_hdimillm_illmnsnsr = u4_s_HdimillmnLxCal(u4_t_illmn);
                break;

            case (U1)ILLMNSNSR_DVCSTS_ERR:
                u1_s_hdimillm_illmnsnsrsts = (U1)HDIMMGR_INSTS_ERR;
                u4_s_hdimillm_illmnsnsr = (U4)HDIMILLMN_DEF_LXDATA;
                break;

            case (U1)ILLMNSNSR_DVCSTS_UNDET:
                /* break */
            default:
                u1_s_hdimillm_illmnsnsrsts = (U1)HDIMMGR_INSTS_UNDET;
                u4_s_hdimillm_illmnsnsr = (U4)HDIMILLMN_DEF_LXDATA;
                break;
        }
    }

    return (u1_t_is_calprmt);
#else
    U1  u1_t_is_calprmt;

    u1_t_is_calprmt = (U1)TRUE;
    u1_s_hdimillm_illmnsnsrsts = (U1)HDIMMGR_INSTS_NML;
    u4_s_hdimillm_illmnsnsr = u4_g_HDIMILLMN_DEF_LXDATA;

    return (u1_t_is_calprmt);
#endif /* ILLMNSNSR_H */
}

/* ++++ N_LX_IMPREMENTATION START ++++ */
/*===================================================================================================================================*/
/*  HudDimmer Conlight Sensor Update                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_HdimillmnCnlghtUpdt(void)
{
    U1  u1_t_rec;
    U2  u2_t_lxdata;
    U2  u2_t_nlx_id;

#if 0   /* BEV Rebase provisionally */
    u1_t_rec = Com_GetIPDUStatus((PduIdType)MSG_BDB1S19_RXCH0);
    u1_t_rec &= (U1)(COM_TIMEOUT | COM_NO_RX);
#else   /* BEV Rebase provisionally */
    u1_t_rec = (U1)COM_NO_RX;
#endif   /* BEV Rebase provisionally */

    if(u1_t_rec == (U1)0){
        u2_t_lxdata = u2_s_HdimillmnCnlghtGet_N_LX();

        if(u2_t_lxdata != (U2)HDIMILLMN_CNLGHT_LXDATA_FAIL){
            u2_s_hdimillm_cnlght_rcvdata = u2_t_lxdata;
            u2_t_nlx_id = u2_s_HdimillmnCnlght_IdCal(u2_t_lxdata);
            u2_s_hdimillm_cnlght_id = u2_s_HdimillmnCnlghtHysID(u2_s_hdimillm_cnlght_id, u2_t_nlx_id, &s2_s_hdimillm_cnlght_hys_cnt);
            u4_s_hdimillm_cnlght = u4_s_HdimillmnCnlght_LxCal(u2_s_hdimillm_cnlght_id);
            u4_s_hdimillm_cnlght = u4_s_HdimillmnCnlghtInptAveCal(u4_s_hdimillm_cnlght);
            u1_s_hdimillm_cnlghtsts = (U1)HDIMMGR_INSTS_NML;
        }
        else{
            u2_s_hdimillm_cnlght_rcvdata = (U2)HDIMILLMN_CNLGHT_LXDATA_FAIL;
            u4_s_hdimillm_cnlght = u4_g_HDIMILLMN_DEF_LXDATA;
            u1_s_hdimillm_cnlghtsts = (U1)HDIMMGR_INSTS_ERR;
            u1_s_hdimillm_cnlght_iniflg = (U1)FALSE;
        }
    }
    else{
        u2_s_hdimillm_cnlght_rcvdata = (U2)HDIMILLMN_CNLGHT_LXDATA_FAIL;
        u4_s_hdimillm_cnlght = u4_g_HDIMILLMN_DEF_LXDATA;
        u1_s_hdimillm_cnlghtsts = (U1)HDIMMGR_INSTS_ERR;
        u1_s_hdimillm_cnlght_iniflg = (U1)FALSE;
    }
}

/*===================================================================================================================================*/
/*  static U2 u2_s_HdimillmnCnlght_IdCal(const U2 u2_a_DATA)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   : u2_a_DATA             : N_LX                                                                                       */
/*  Return      : u2_t_adr              : N_LX ID                                                                                    */
/*===================================================================================================================================*/
static U2 u2_s_HdimillmnCnlght_IdCal(const U2 u2_a_DATA)
{
    U2  u2_t_adr;

    for(u2_t_adr = (U2)0; u2_t_adr < (U2)HDIMILLMN_CNLGHT_MAX_CONTBL; u2_t_adr++){
        if(st_TBL_HDIMILLMN_CNLGHT[u2_t_adr].u2_rcvdata >= u2_a_DATA){
            break;
        }
    }

    return (u2_t_adr);
}

/*===================================================================================================================================*/
/*  static U2 u2_s_HdimillmnCnlghtHysID(const U2 u2_a_OLD, const U2 u2_a_NEW, S2 *s2_ap_cnt)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : -->  u2_a_OLD         : Previous value                                                                           */
/*                : -->  u2_a_NEW         : Current value                                                                            */
/*                : --> *s2_ap_cnt        : Hysterisis depth counter                                                                 */
/*  Return        : <--  u2_t_ret         : Result value                                                                             */
/*===================================================================================================================================*/
static U2 u2_s_HdimillmnCnlghtHysID(const U2 u2_a_OLD, const U2 u2_a_NEW, S2 *s2_ap_cnt)
{
    U2  u2_t_ret;

    u2_t_ret = u2_a_OLD;
    if(u2_a_OLD == u2_a_NEW){
        *s2_ap_cnt = (S2)0;
    }
    else if(u2_a_OLD > u2_a_NEW){
        if((u2_a_OLD - u2_a_NEW) > (U2)HDIMILLMN_CNLGHT_HYS_ADWID){
            *s2_ap_cnt = (S2)0;
            u2_t_ret = u2_a_NEW;
        }
        else{
            if(*s2_ap_cnt > (S2)0){
                *s2_ap_cnt = (S2)0;
            }
            (*s2_ap_cnt)--;
            if(((*s2_ap_cnt) + (S2)HDIMILLMN_CNLGHT_HYS_ADDEP) <= (S2)0){
                *s2_ap_cnt = (S2)0;
                u2_t_ret = u2_a_NEW;
            }
        }
    }
    else{
        if((u2_a_NEW - u2_a_OLD) > (U2)HDIMILLMN_CNLGHT_HYS_ADWID){
            *s2_ap_cnt = (S2)0;
            u2_t_ret = u2_a_NEW;
        }
        else{
            if(*s2_ap_cnt < (S2)0){
                *s2_ap_cnt = (S2)0;
            }
            (*s2_ap_cnt)++;
            if(*s2_ap_cnt >= (S2)HDIMILLMN_CNLGHT_HYS_ADDEP){
                *s2_ap_cnt = (S2)0;
                u2_t_ret = u2_a_NEW;
            }
        }
    }
    return(u2_t_ret);
}

/*===================================================================================================================================*/
/*  static U4 u4_s_HdimillmnCnlght_LxCal(const U2 u2_a_ID)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   : u2_a_ID               : ID                                                                                         */
/*  Return      : u4_t_retlx            : LSB:0.01Lx                                                                                 */
/*===================================================================================================================================*/
static U4 u4_s_HdimillmnCnlght_LxCal(const U2 u2_a_ID)
{
    U4 u4_t_retlx;                                                              /* LSB:0.01Lx                                        */

    if(u2_a_ID < (U2)HDIMILLMN_CNLGHT_MAX_CONTBL){
        u4_t_retlx = st_TBL_HDIMILLMN_CNLGHT[u2_a_ID].u4_lx;
    }
    else{
        u4_t_retlx = st_TBL_HDIMILLMN_CNLGHT[HDIMILLMN_CNLGHT_MAX_CONTBL - 1].u4_lx;
    }

    return (u4_t_retlx);
}

/*===================================================================================================================================*/
/*  static U4 u4_s_HdimillmnCnlghtInptAveCal(const U4 u4_a_LX)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   : u4_a_LX               : Latest illuminance value(LSB:0.01Lx)                                                       */
/*  Return      : u4_t_retlx            : Result illuminance value(LSB:0.01Lx)                                                       */
/*===================================================================================================================================*/
static U4 u4_s_HdimillmnCnlghtInptAveCal(const U4 u4_a_LX)
{
    U2 u2_t_spd;                                                                /* LSB:0.01km/h                                      */
    U4 u4_t_movave;
    U4 u4_t_oldest_data;
    U4 u4_t_retlx;                                                              /* LSB:0.01Lx                                        */
    U1 u1_t_msgsts;
    U1 u1_t_ig;
    U1 u1_t_aconmavecnt;

    u2_t_spd = (U2)0U;
    u1_t_ig = u1_g_VehopemdIgnOn();
    if(u1_t_ig == (U1)TRUE){
        u1_t_msgsts = Com_GetIPDUStatus((PduIdType)MSG_VSC1G13_RXCH0);
        u1_t_msgsts &= (U1)(COM_TIMEOUT | COM_NO_RX);
        if(u1_t_msgsts == (U1)0U){
            (void)Com_ReceiveSignal(ComConf_ComSignal_SP1, &u2_t_spd);
        }
    }

    u1_t_aconmavecnt = u1_CALIB_MCUID0580_ACONMVAVECNT;

    if((u2_t_spd         > (U2)HDIMILLMN_CNLGHT_VALID_SPDKMH  ) ||
       (u1_t_aconmavecnt < (U1)HDIMILLMN_CNLGHT_MOVAVE_DIV_MIN)){
        u1_s_hdimillm_cnlght_iniflg = (U1)FALSE;
        u4_t_retlx = u4_a_LX;
    }
    else{
        if(u1_s_hdimillm_cnlght_iniflg == (U1)FALSE){
            vd_g_MemfillU4(&u4_s_hdimillm_cnlght_calbuf[0], u4_a_LX, (U4)u1_t_aconmavecnt);
            u2_s_hdimillm_cnlght_cnt = (U2)0U;
            u4_s_hdimillm_cnlght_calsum = u4_a_LX * (U4)u1_t_aconmavecnt;      /* PRQA S 3383 # over detection */
            u4_t_movave = u4_a_LX;
        }
        else{
            if(u2_s_hdimillm_cnlght_cnt >= (U2)u1_t_aconmavecnt){
                u2_s_hdimillm_cnlght_cnt = (U2)0U;
            }
            u4_t_oldest_data = u4_s_hdimillm_cnlght_calbuf[u2_s_hdimillm_cnlght_cnt];

            if(u4_s_hdimillm_cnlght_calsum >= u4_t_oldest_data){
                u4_s_hdimillm_cnlght_calsum = u4_s_hdimillm_cnlght_calsum - u4_t_oldest_data;
            }
            else{
                u4_s_hdimillm_cnlght_calsum = (U4)0U;
            }
            if(u4_a_LX >= ((U4)U4_MAX - u4_s_hdimillm_cnlght_calsum)){
                u4_s_hdimillm_cnlght_calsum = (U4)U4_MAX;
            }
            else{
                u4_s_hdimillm_cnlght_calsum = u4_s_hdimillm_cnlght_calsum + u4_a_LX;      /* PRQA S 3383 # over detection */
            }
            u4_t_movave = u4_s_hdimillm_cnlght_calsum / (U4)u1_t_aconmavecnt;
            u4_s_hdimillm_cnlght_calbuf[u2_s_hdimillm_cnlght_cnt] = u4_a_LX;
            u2_s_hdimillm_cnlght_cnt++;                                                   /* PRQA S 3383 # over detection */
        }
        u1_s_hdimillm_cnlght_iniflg = (U1)TRUE;
        u4_t_retlx = u4_t_movave;
    }

    if(u4_t_retlx > (U4)HDIMILLMN_CNLGHT_GURDLX){
        u4_t_retlx = (U4)HDIMILLMN_CNLGHT_GURDLX;
    }

    return (u4_t_retlx);
}

/*===================================================================================================================================*/
/*  static U2    u2_s_HdimillmnCnlghtGet_N_LX(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      u2_t_lxdata : N_LX                                                                                                   */
/*===================================================================================================================================*/
static U2    u2_s_HdimillmnCnlghtGet_N_LX(void)
{
    U2 u2_t_lxdata;

#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_N_LX, &u2_t_lxdata);
#else   /* BEV Rebase provisionally */
    u2_t_lxdata = (U1)0U;
#endif   /* BEV Rebase provisionally */
    if(u2_t_lxdata >= (U2)HDIMILLMN_CNLGHT_LXDATA_JUDGE_ERR){
        u2_t_lxdata = (U2)HDIMILLMN_CNLGHT_LXDATA_FAIL;
    }

    return (u2_t_lxdata);
}
/* ++++ N_LX_IMPREMENTATION STOP  ++++ */

/*===================================================================================================================================*/
/*  Calucuration Sensor Update Timing                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   u1_a_SNSRUDP:Sensor Update Timing                                                                                    */
/*  Return      u1_t_is_avecalprmt: TRUE,Illuminance Average Caluculation Permit,FALSE:Illuminance Average Caluculation No Permit    */
/*===================================================================================================================================*/
static U1   u1_s_HdimillmnCalUpdt(const U1 u1_a_SNSRUPDT)
{
#ifdef ILLMNSNSR_H
    U1  u1_t_is_avecalprmt;

    u1_t_is_avecalprmt = (U1)FALSE;

    if(u1_a_SNSRUPDT == (U1)TRUE){
        u1_s_hdimillm_illmnsts = (U1)HDIMMGR_INSTS_NML;
        u4_s_hdimillm_illmn = u4_s_HdimillmnCalAdjIllmn(u4_s_hdimillm_illmn, u4_s_hdimillm_illmnsnsr, u4_s_hdimillm_cnlght);
        u1_t_is_avecalprmt = (U1)TRUE;
    }

    return (u1_t_is_avecalprmt);
#else
    U1  u1_t_is_avecalprmt;

    u1_t_is_avecalprmt = (U1)FALSE;

    if(u1_s_hdimillm_illmn_updt_cnt >= (U1)HDIMILLMN_ILMDAT_UPDT_TIM){
        u1_s_hdimillm_illmn_updt_cnt = (U1)0;

        u1_s_hdimillm_illmnsts = (U1)HDIMMGR_INSTS_NML;
        u4_s_hdimillm_illmn = u4_s_hdimillm_cnlght;
        u1_t_is_avecalprmt = (U1)TRUE;
    }
    u1_s_hdimillm_illmn_updt_cnt++;                         /* PRQA S 3383 # over detection */

    return (u1_t_is_avecalprmt);
#endif /* ILLMNSNSR_H */
}

/*===================================================================================================================================*/
/*  Adjust Illuminance Caluculation                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   u4_a_ILLMN     :Ambient Illuminance                                                                                  */
/*              u4_a_ILLMNSNSR :Illuminance Sensor                                                                                   */
/*              u4_a_CNLGHTSNSR:Conlight Sensor                                                                                      */
/*  Return      u4_t_illmn     :Ambient Illuminance                                                                                  */
/*===================================================================================================================================*/
#ifdef ILLMNSNSR_H
static U4   u4_s_HdimillmnCalAdjIllmn(const U4 u4_a_ILLMN, const U4 u4_a_ILLMNSNSR, const U4 u4_a_CNLGHTSNSR)
{
    U4  u4_t_tmp;
    U4  u4_t_illmn;

    U4  u4_tp_term1[CALC_U8_NUM_TERM];
    U4  u4_tp_term2[CALC_U8_NUM_TERM];
    U4  u4_tp_dat1[CALC_U8_NUM_RSLT];
    U4  u4_tp_dat2[CALC_U8_NUM_RSLT];
    U1  u1_t_rsltbit;

    u4_t_illmn = u4_a_ILLMN;
    if(u4_a_ILLMNSNSR >= u4_a_CNLGHTSNSR){
        if(u4_a_ILLMNSNSR < (U4)HDIMILLMN_CNLGHT_JUDNLX){
            /* PN * (PA + (HDIMILLMN_CNLGHT_JUDNLX - PN) / HDIMILLMN_CNLGHT_JUDNLX */
            /* (PA + (HDIMILLMN_CNLGHT_JUDNLX - PN) */
            u4_t_tmp = u4_a_ILLMNSNSR + ((U4)HDIMILLMN_CNLGHT_JUDNLX - u4_a_CNLGHTSNSR);

            /* PN * u4_t_tmp    */
            u4_tp_term1[CALC_U8_LO] = u4_a_CNLGHTSNSR;
            u4_tp_term1[CALC_U8_HI] = u4_t_tmp;
            u4_tp_term1[CALC_U8_DIV] = (U4)0;
            (void)u1_g_MulU8(&u4_tp_term1[0],&u4_tp_dat1[0]);

            u4_tp_term2[CALC_U8_LO] = u4_tp_dat1[CALC_U8_LO];
            u4_tp_term2[CALC_U8_HI] = u4_tp_dat1[CALC_U8_HI];
            u4_tp_term2[CALC_U8_DIV] = (U4)HDIMILLMN_CNLGHT_JUDNLX;
            /* PN * u4_t_tmp / HDIMILLMN_CNLGHT_JUDNLX */
            u1_t_rsltbit = u1_g_DivU8(&u4_tp_term2[0], &u4_tp_dat2[0]);

            if((u1_t_rsltbit & (U1)CALC_U8_RSLT_DIVBYZERO) != (U1)CALC_U8_RSLT_DIVBYZERO){
                if((u1_t_rsltbit & (U1)CALC_U8_RSLT_OVRFLW_U4) == (U1)CALC_U8_RSLT_OVRFLW_U4){
                    u4_t_illmn = (U4)U4_MAX;
                }
                else{
                    u4_t_illmn = u4_tp_dat2[CALC_U8_QUO];
                }
            }
            else{   /* division by zero */
                /* u4_t_illmn is last data. */
            }
        }
        else{
            u4_t_illmn = u4_a_ILLMNSNSR;
        }
    }
    else{
        u4_t_illmn = u4_a_CNLGHTSNSR;
    }

    return (u4_t_illmn);
}
#endif /* ILLMNSNSR_H */

/*===================================================================================================================================*/
/*  Calculation Illuminance Sensor to Ambient Illuminance                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   u4_a_ILLMN : Illuminance Value(0.1Lx)                                                                                */
/*  Return      u4_t_retlx : Ambient Illuminance Value(0.01Lx)                                                                       */
/*===================================================================================================================================*/
#ifdef ILLMNSNSR_H
static U4   u4_s_HdimillmnLxCal(const U4 u4_a_ILLMN)
{
    static const U1 u1_s_HDIMILLMN_SNSR_K = (U1)240;    /* LSB:0.1 */

    U4          u4_t_retlx;

    u4_t_retlx = u4_a_ILLMN * (U4)u1_s_HDIMILLMN_SNSR_K;

    return (u4_t_retlx);
}
#endif /* ILLMNSNSR_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           2017.03.03  HS      New (Based on 15MYHUD_NXT_E00t00_AA_HUD_NXT_025::HudDimmer::dimlightsnsr)                    */
/*                                      Adjust Illuminance Function was added.(Illuminance Sensor and Conlight Sensor)               */
/*  2.0.0           2020.02.27  MaO     Added LSB configuration.                                                                     */
/*  2.1.0           2023.09.27  AA      Applied calibration implementation                                                           */
/*  2.2.1           2024.07.02  His     Delete Calibration Guard Process.                                                            */
/*                                                                                                                                   */
/*  Revision         Date        Author   Change Description                                                                         */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1            2025.10.29  MA      Change for BEV rebase.                                                                      */
/*                                                                                                                                   */
/*  * HS = Hidenobu Suzuki, NCOS                                                                                                     */
/*  * HiS = Hidenobu Suzuki, MSE                                                                                                     */
/*  * MaO = Masayuki Okada, DENSO                                                                                                    */
/*  * AA = Anna Asuncion, DT                                                                                                         */
/*  * MA = Misaki Aiki, Denso Techno                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
