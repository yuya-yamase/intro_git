/* 0.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Local Communication SPI                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_CAN_C_MAJOR                     (0U)
#define XSPI_CAN_C_MINOR                     (4U)
#define XSPI_CAN_C_PATCH                     (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "xspi_met.h"
#include "xspi_met_can.h"

/* Platform */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_CAN_C_MAJOR != XSPI_MET_H_MAJOR) || \
     (XSPI_CAN_C_MINOR != XSPI_MET_H_MINOR) || \
     (XSPI_CAN_C_PATCH != XSPI_MET_H_PATCH))
#error "xspi_met.c and xspi_met.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#define XSPI_MET_BITSHIFT_CALCMASK          (0x0FU)
#define XSPI_MET_INDEX_CALCSHIFT            (4U)

#define XSPI_MET_CAN_NUM_DLC                (3U)
#define XSPI_MET_CAN_DLC_08                 (0U)
#define XSPI_MET_CAN_DLC_32                 (1U)
#define XSPI_MET_CAN_DLC_64                 (2U)

#define XSPI_MET_CAN_64                     (64U)

#define XSPI_MET_NUM_RTE                    (550U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2                          u2_idx;
    U2                          u2_num_idx;
    U2                          u2_buf;
    U2                          u2_num_buf;
}ST_XSPI_MET_CANGW_STA;

typedef struct{
    U2                          u2_pos;
    U2                          u2_msg;
    U1                          u1_dlc;
    U2                          u2_stspos;
}ST_XSPI_MET_MSG2POSLEN;

typedef void       ( * FP_XSPI_MET_CANGW_PAD)(const U1 * u1_a_SRC, U4 * u4_a_DST);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4 u4_s_xspi_rte_gw[XSPI_MET_NUM_RTE];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_XSpiMETPad08(const U1 * u1_a_SRC, U4 * u4_a_DST);
static void vd_s_XSpiMETPad32(const U1 * u1_a_SRC, U4 * u4_a_DST);
static void vd_s_XSpiMETPad64(const U1 * u1_a_SRC, U4 * u4_a_DST);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_XSPI_MET_CANGW_STA st_s_XSPI_MET_CANGW_RTE_BUF_STA[XSPIMETCANGW_NUM_BLOCK] = {
        /* u2_idx   u2_num_idx  u2_buf      u2_num_buf   */
        {(U2)0U,    (U2)123U,   (U2)0U,     (U2)550U   } 
};

static const ST_XSPI_MET_MSG2POSLEN st_sp_XSPI_MET_MSG2POSLEN[] = {
        {   (U2)0U, (U2)MSG_ABG1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,   (U2)0},/* Index  0 */
        {   (U2)2U, (U2)MSG_ACN1S04_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,   (U2)1},/* Index  1 */
        {  (U2)10U, (U2)MSG_ADC1S14_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,   (U2)2},/* Index  2 */
        {  (U2)18U, (U2)MSG_ADC1S17_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,   (U2)3},/* Index  3 */
        {  (U2)26U, (U2)MSG_ADU1S07_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,   (U2)4},/* Index  4 */
        {  (U2)34U, (U2)MSG_ARS1S90_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,   (U2)5},/* Index  5 */
        {  (U2)36U, (U2)MSG_BAT1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,   (U2)6},/* Index  6 */
        {  (U2)44U, (U2)MSG_BCC1S06_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,   (U2)7},/* Index  7 */
        {  (U2)46U, (U2)MSG_BDB1F01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,   (U2)8},/* Index  8 */
        {  (U2)48U, (U2)MSG_BDB1F02_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,   (U2)9},/* Index  9 */
        {  (U2)52U, (U2)MSG_BDB1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)11},/* Index 10 */
        {  (U2)54U, (U2)MSG_BDB1S03_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)12},/* Index 11 */
        {  (U2)56U, (U2)MSG_BDB1S04_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)13},/* Index 12 */
        {  (U2)58U, (U2)MSG_BDB1S05_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)14},/* Index 13 */
        {  (U2)60U, (U2)MSG_ZN11S14_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)15},/* Index 14 */
        {  (U2)62U, (U2)MSG_BDB1S13_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)16},/* Index 15 */
        {  (U2)64U, (U2)MSG_BDB1S27_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)17},/* Index 16 */
        {  (U2)66U, (U2)MSG_BDB1S28_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)18},/* Index 17 */
        {  (U2)68U, (U2)MSG_BDC1S13_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)19},/* Index 18 */
        {  (U2)76U, (U2)MSG_BDC1S23_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)20},/* Index 19 */
        {  (U2)78U, (U2)MSG_BDC1S33_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)21},/* Index 20 */
        {  (U2)80U, (U2)MSG_BDC1SH8_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)22},/* Index 21 */
        {  (U2)82U, (U2)MSG_BDC1SV2_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)23},/* Index 22 */
        {  (U2)90U, (U2)MSG_BDC1S45_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)24},/* Index 23 */
        {  (U2)92U, (U2)MSG_BDC1S46_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)25},/* Index 24 */
        {  (U2)94U, (U2)MSG_BDC1S48_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)26},/* Index 25 */
        { (U2)118U, (U2)MSG_DDM1S35_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)28},/* Index 26 */
        { (U2)134U, (U2)MSG_BDC1S74_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)29},/* Index 27 */
        { (U2)136U, (U2)MSG_BDC1S81_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)30},/* Index 28 */
        { (U2)144U, (U2)MSG_BKD1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)31},/* Index 29 */
        { (U2)146U, (U2)MSG_BSR1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)32},/* Index 30 */
        { (U2)148U, (U2)MSG_BSR1S02_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)33},/* Index 31 */
        { (U2)150U, (U2)MSG_BSR1S03_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)34},/* Index 32 */
        { (U2)152U, (U2)MSG_CSR1S04_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)35},/* Index 33 */
        { (U2)154U, (U2)MSG_CSR1S07_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)36},/* Index 34 */
        { (U2)156U, (U2)MSG_CSR1S08_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)37},/* Index 35 */
        { (U2)158U, (U2)MSG_DDM1S12_RXCH0,     (U1)XSPI_MET_CAN_DLC_64,  (U2)38},/* Index 36 */
        { (U2)174U, (U2)MSG_DDM1S17_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)39},/* Index 37 */
        { (U2)182U, (U2)MSG_DMC1S08_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)40},/* Index 38 */
        { (U2)194U, (U2)MSG_DS11S37_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)43},/* Index 39 */
        { (U2)196U, (U2)MSG_DS11S40_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)44},/* Index 40 */
        { (U2)198U, (U2)MSG_DS12F02_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)45},/* Index 41 */
        { (U2)200U, (U2)MSG_DS12F03_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)46},/* Index 42 */
        { (U2)202U, (U2)MSG_DST1S02_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)47},/* Index 43 */
        { (U2)204U, (U2)MSG_ECT1G01_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)48},/* Index 44 */
        { (U2)212U, (U2)MSG_ECT1G92_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)49},/* Index 45 */
        { (U2)214U, (U2)MSG_ECT1S93_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)50},/* Index 46 */
        { (U2)216U, (U2)MSG_EHV1S26_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)51},/* Index 47 */
        { (U2)218U, (U2)MSG_EHV1S31_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)52},/* Index 48 */
        { (U2)220U, (U2)MSG_EHV1S90_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)53},/* Index 49 */
        { (U2)222U, (U2)MSG_EHV1S94_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)54},/* Index 50 */
        { (U2)224U, (U2)MSG_EHV1S95_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)55},/* Index 51 */
        { (U2)226U, (U2)MSG_EHV1S96_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)56},/* Index 52 */
        { (U2)228U, (U2)MSG_EHV1S97_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)57},/* Index 53 */
        { (U2)230U, (U2)MSG_EHV1S99_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)58},/* Index 54 */
        { (U2)232U, (U2)MSG_EHV2G02_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)59},/* Index 55 */
        { (U2)234U, (U2)MSG_EHV2G70_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)60},/* Index 56 */
        { (U2)242U, (U2)MSG_ENG1G03_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)61},/* Index 57 */
        { (U2)250U, (U2)MSG_ENG1G90_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)62},/* Index 58 */
        { (U2)252U, (U2)MSG_ENG1G92_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)63},/* Index 59 */
        { (U2)254U, (U2)MSG_ENG1S60_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)64},/* Index 60 */
        { (U2)262U, (U2)MSG_ENG1S99_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)65},/* Index 61 */
        { (U2)264U, (U2)MSG_EPS1S11_RXCH0,     (U1)XSPI_MET_CAN_DLC_64,  (U2)66},/* Index 62 */
        { (U2)280U, (U2)MSG_EPS1S90_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)67},/* Index 63 */
        { (U2)282U, (U2)MSG_FCM1S10_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)68},/* Index 64 */
        { (U2)290U, (U2)MSG_FCM1S12_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)69},/* Index 65 */
        { (U2)292U, (U2)MSG_FCM1S39_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)70},/* Index 66 */
        { (U2)294U, (U2)MSG_FCM1S40_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)71},/* Index 67 */
        { (U2)296U, (U2)MSG_FCM1S41_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)72},/* Index 68 */
        { (U2)298U, (U2)MSG_FCM1S51_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)73},/* Index 69 */
        { (U2)306U, (U2)MSG_FCM1S52_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)74},/* Index 70 */
        { (U2)308U, (U2)MSG_FCM1S58_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)75},/* Index 71 */
        { (U2)310U, (U2)MSG_FCM1S70_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)76},/* Index 72 */
        { (U2)312U, (U2)MSG_FCM1S78_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)77},/* Index 73 */
        { (U2)314U, (U2)MSG_FCM1S92_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)78},/* Index 74 */
        { (U2)316U, (U2)MSG_FWD1S10_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)79},/* Index 75 */
        { (U2)318U, (U2)MSG_IDT1S02_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)80},/* Index 76 */
        { (U2)320U, (U2)MSG_IPA1S05_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)81},/* Index 77 */
        { (U2)322U, (U2)MSG_ITS1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)82},/* Index 78 */
        { (U2)324U, (U2)MSG_ITS1S05_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)83},/* Index 79 */
        { (U2)326U, (U2)MSG_LVN1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)84},/* Index 80 */
        { (U2)328U, (U2)MSG_PCN1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)85},/* Index 81 */
        { (U2)336U, (U2)MSG_PDC1G02_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)86},/* Index 82 */
        { (U2)338U, (U2)MSG_PDS1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)87},/* Index 83 */
        { (U2)340U, (U2)MSG_PLG1G16_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)88},/* Index 84 */
        { (U2)348U, (U2)MSG_PLG1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)89},/* Index 85 */
        { (U2)350U, (U2)MSG_PLG1S06_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)90},/* Index 86 */
        { (U2)352U, (U2)MSG_PLG1S20_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)91},/* Index 87 */
        { (U2)360U, (U2)MSG_PLG1S21_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)92},/* Index 88 */
        { (U2)368U, (U2)MSG_PMN1G03_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)93},/* Index 89 */
        { (U2)370U, (U2)MSG_PST1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)94},/* Index 90 */
        { (U2)372U, (U2)MSG_RSE1G20_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)95},/* Index 91 */
        { (U2)374U, (U2)MSG_SBW1G02_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)96},/* Index 92 */
        { (U2)382U, (U2)MSG_SCN1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)97},/* Index 93 */
        { (U2)384U, (U2)MSG_SCN1S02_RXCH0,     (U1)XSPI_MET_CAN_DLC_08,  (U2)98},/* Index 94 */
        { (U2)386U, (U2)MSG_SCS1S11_RXCH0,     (U1)XSPI_MET_CAN_DLC_32,  (U2)99},/* Index 95 */
        { (U2)394U, (U2)MSG_SCS1S14_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)100},/* Index 96 */
        { (U2)402U, (U2)MSG_SOL1S02_RXCH0,     (U1)XSPI_MET_CAN_DLC_08, (U2)101},/* Index 97 */
        { (U2)404U, (U2)MSG_SOL1S06_RXCH0,     (U1)XSPI_MET_CAN_DLC_08, (U2)102},/* Index 98 */
        { (U2)406U, (U2)MSG_TPM1S02_RXCH0,     (U1)XSPI_MET_CAN_DLC_08, (U2)103},/* Index 99 */
        { (U2)408U, (U2)MSG_TPM1S03_RXCH0,     (U1)XSPI_MET_CAN_DLC_08, (U2)104},/* Index100 */
        { (U2)410U, (U2)MSG_TPM1S04_RXCH0,     (U1)XSPI_MET_CAN_DLC_08, (U2)105},/* Index101 */
        { (U2)412U, (U2)MSG_TPM1S05_RXCH0,     (U1)XSPI_MET_CAN_DLC_08, (U2)106},/* Index102 */
        { (U2)414U, (U2)MSG_TPM1S07_RXCH0,     (U1)XSPI_MET_CAN_DLC_08, (U2)107},/* Index103 */
        { (U2)416U, (U2)MSG_TRA1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08, (U2)108},/* Index104 */
        { (U2)418U, (U2)MSG_UCB1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)109},/* Index105 */
        { (U2)426U, (U2)MSG_VAS1S01_RXCH0,     (U1)XSPI_MET_CAN_DLC_08, (U2)110},/* Index106 */
        { (U2)428U, (U2)MSG_VSC1G12_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)111},/* Index107 */
        { (U2)436U, (U2)MSG_VSC1G13_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)112},/* Index108 */
        { (U2)444U, (U2)MSG_VSC1G96_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)113},/* Index109 */
        { (U2)452U, (U2)MSG_ZN11S17_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)114},/* Index110 */
        { (U2)460U, (U2)MSG_ZN11S19_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)115},/* Index111 */
        { (U2)468U, (U2)MSG_ZN11S26_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)116},/* Index112 */
        { (U2)476U, (U2)MSG_ZN11S38_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)117},/* Index113 */
        { (U2)484U, (U2)MSG_ZN11S60_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)118},/* Index114 */
        { (U2)492U, (U2)MSG_ZN21S13_RXCH0,     (U1)XSPI_MET_CAN_DLC_08, (U2)119},/* Index115 */
        { (U2)494U, (U2)MSG_ADC1S13_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)120},/* Index116 */
        { (U2)502U, (U2)MSG_BDC1S91_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)121},/* Index117 */
        { (U2)510U, (U2)MSG_BDC1S97_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)122},/* Index118 */
        { (U2)518U, (U2)MSG_BDC1S98_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)123},/* Index119 */
        { (U2)526U, (U2)MSG_BDC1S99_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)124},/* Index120 */
        { (U2)534U, (U2)MSG_BDC1SV1_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)125},/* Index121 */
        { (U2)542U, (U2)MSG_BDB1S08_RXCH0,     (U1)XSPI_MET_CAN_DLC_32, (U2)126} /* Index122 */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_XSpiMETCANGWInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiMETCANGWInit(void)
{

    vd_g_MemfillU4(&u4_s_xspi_rte_gw[0],
                   (U4)0U,
                   (U4)XSPI_MET_NUM_RTE);

}

/*===================================================================================================================================*/
/*  void    vd_g_XSpiMETCANGWPushPDU(const U2 u2_a_MSG)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiMETCANGWPushPDU(const U2 u2_a_MSG)
{
    static const FP_XSPI_MET_CANGW_PAD fp_sp_XSPI_MET_CANGW_PAD[XSPI_MET_CAN_NUM_DLC] ={
        &vd_s_XSpiMETPad08,     /* 8Byte  */
        &vd_s_XSpiMETPad32,     /* 32Byte */
        &vd_s_XSpiMETPad64      /* 64Byte */
    };
    static const U2 u2_s_XSPI_MET_CANGW_MIN      = (U2)MSG_ABG1D50_RXCH0;
    static const U2 u2_s_XSPI_MET_CANGW_MAX      = (U2)MSG_ZN21S72_RXCH0;

    static const U2 u2_sp_XSPI_MET_CANGW_OX2IDX[] = {
        (U2)U2_MAX, /*      0:MSG_ABG1D50_CH0     (23U)  */
        (U2)U2_MAX, /*      1:MSG_ABG1D51_CH0     (24U)  */
        (U2)0U,     /*      2:MSG_ABG1S01_CH0     (25U)  */
        (U2)U2_MAX, /*      3:MSG_ABG1S09_CH0     (26U)  */
        (U2)U2_MAX, /*      4:MSG_ACN1D50_CH0     (27U)  */
        (U2)U2_MAX, /*      5:MSG_ACN1S03_CH0     (28U)  */
        (U2)1U,     /*      6:MSG_ACN1S04_CH0     (29U)  */
        (U2)U2_MAX, /*      7:MSG_ACN1S07_CH0     (30U)  */
        (U2)U2_MAX, /*      8:MSG_ACN1S15_CH0     (31U)  */
        (U2)U2_MAX, /*      9:MSG_ACN1S25_CH0     (32U)  */
        (U2)U2_MAX, /*     10:MSG_ACN1S29_CH0     (33U)  */
        (U2)U2_MAX, /*     11:MSG_ADC1S08_CH0     (34U)  */
        (U2)U2_MAX, /*     12:MSG_ADC1S10_CH0     (35U)  */
        (U2)U2_MAX, /*     13:MSG_ADC1S11_CH0     (36U)  */
        (U2)U2_MAX, /*     14:MSG_ADC1S12_CH0     (37U)  */
        (U2)116U,   /*     15:MSG_ADC1S13_CH0     (38U)  */
        (U2)2U,     /*     16:MSG_ADC1S14_CH0     (39U)  */
        (U2)U2_MAX, /*     17:MSG_ADC1S15_CH0     (40U)  */
        (U2)U2_MAX, /*     18:MSG_ADC1S16_CH0     (41U)  */
        (U2)3U,     /*     19:MSG_ADC1S17_CH0     (42U)  */
        (U2)U2_MAX, /*     20:MSG_ADC1S27_CH0     (43U)  */
        (U2)U2_MAX, /*     21:MSG_ADC1S31_CH0     (44U)  */
        (U2)U2_MAX, /*     22:MSG_ADU1S03_CH0     (45U)  */
        (U2)U2_MAX, /*     23:MSG_ADU1S05_CH0     (46U)  */
        (U2)U2_MAX, /*     24:MSG_ADU1S06_CH0     (47U)  */
        (U2)4U,     /*     25:MSG_ADU1S07_CH0     (48U)  */
        (U2)U2_MAX, /*     26:MSG_ARS1S01_CH0     (49U)  */
        (U2)5U,     /*     27:MSG_ARS1S90_CH0     (50U)  */
        (U2)U2_MAX, /*     28:MSG_BAT1E45_CH0     (51U)  */
        (U2)U2_MAX, /*     29:MSG_BAT1ED1_CH0     (52U)  */
        (U2)U2_MAX, /*     30:MSG_BAT1ED5_CH0     (53U)  */
        (U2)U2_MAX, /*     31:MSG_BAT1EDA_CH0     (54U)  */
        (U2)U2_MAX, /*     32:MSG_BAT1EDB_CH0     (55U)  */
        (U2)6U,     /*     33:MSG_BAT1S01_CH0     (56U)  */
        (U2)U2_MAX, /*     34:MSG_BAT1S08_CH0     (57U)  */
        (U2)U2_MAX, /*     35:MSG_BAT1S11_CH0     (58U)  */
        (U2)U2_MAX, /*     36:MSG_BAT2ED2_CH0     (59U)  */
        (U2)7U,     /*     37:MSG_BCC1S06_CH0     (60U)  */
        (U2)8U,     /*     38:MSG_BDB1F01_CH0     (61U)  */
        (U2)9U,     /*     39:MSG_BDB1F02_CH0     (62U)  */
        (U2)U2_MAX, /*     40:MSG_BDB1F03_CH0     (63U)  */
        (U2)10U,    /*     41:MSG_BDB1S01_CH0     (64U)  */
        (U2)U2_MAX, /*     42:MSG_BDB1S02_CH0     (65U)  */
        (U2)11U,    /*     43:MSG_BDB1S03_CH0     (66U)  */
        (U2)12U,    /*     44:MSG_BDB1S04_CH0     (67U)  */
        (U2)13U,    /*     45:MSG_BDB1S05_CH0     (68U)  */
        (U2)122U,   /*     46:MSG_BDB1S08_CH0     (69U)  */
        (U2)U2_MAX, /*     47:MSG_BDB1S10_CH0     (70U)  */
        (U2)15U,    /*     48:MSG_BDB1S13_CH0     (71U)  */
        (U2)16U,    /*     49:MSG_BDB1S27_CH0     (72U)  */
        (U2)17U,    /*     50:MSG_BDB1S28_CH0     (73U)  */
        (U2)U2_MAX, /*     51:MSG_BDB1S29_CH0     (74U)  */
        (U2)U2_MAX, /*     52:MSG_BDB1S36_CH0     (75U)  */
        (U2)18U,    /*     53:MSG_BDC1S13_CH0     (76U)  */
        (U2)19U,    /*     54:MSG_BDC1S23_CH0     (77U)  */
        (U2)20U,    /*     55:MSG_BDC1S33_CH0     (78U)  */
        (U2)U2_MAX, /*     56:MSG_BDC1S41_CH0     (79U)  */
        (U2)23U,    /*     57:MSG_BDC1S45_CH0     (80U)  */
        (U2)24U,    /*     58:MSG_BDC1S46_CH0     (81U)  */
        (U2)25U,    /*     59:MSG_BDC1S48_CH0     (82U)  */
        (U2)U2_MAX, /*     60:MSG_BDC1S52_CH0     (83U)  */
        (U2)U2_MAX, /*     61:MSG_BDC1S60_CH0     (84U)  */
        (U2)27U,    /*     62:MSG_BDC1S74_CH0     (85U)  */
        (U2)28U,    /*     63:MSG_BDC1S81_CH0     (86U)  */
        (U2)117U,   /*     64:MSG_BDC1S91_CH0     (87U)  */
        (U2)118U,   /*     65:MSG_BDC1S97_CH0     (88U)  */
        (U2)119U,   /*     66:MSG_BDC1S98_CH0     (89U)  */
        (U2)120U,   /*     67:MSG_BDC1S99_CH0     (90U)  */
        (U2)U2_MAX, /*     68:MSG_BDC1SC1_CH0     (91U)  */
        (U2)U2_MAX, /*     69:MSG_BDC1SC2_CH0     (92U)  */
        (U2)U2_MAX, /*     70:MSG_BDC1SC3_CH0     (93U)  */
        (U2)U2_MAX, /*     71:MSG_BDC1SC4_CH0     (94U)  */
        (U2)U2_MAX, /*     72:MSG_BDC1SC5_CH0     (95U)  */
        (U2)U2_MAX, /*     73:MSG_BDC1SC6_CH0     (96U)  */
        (U2)U2_MAX, /*     74:MSG_BDC1SC7_CH0     (97U)  */
        (U2)U2_MAX, /*     75:MSG_BDC1SC8_CH0     (98U)  */
        (U2)U2_MAX, /*     76:MSG_BDC1SC9_CH0     (99U)  */
        (U2)U2_MAX, /*     77:MSG_BDC1SD1_CH0     (100U) */
        (U2)U2_MAX, /*     78:MSG_BDC1SD2_CH0     (101U) */
        (U2)U2_MAX, /*     79:MSG_BDC1SD3_CH0     (102U) */
        (U2)U2_MAX, /*     80:MSG_BDC1SD4_CH0     (103U) */
        (U2)U2_MAX, /*     81:MSG_BDC1SD5_CH0     (104U) */
        (U2)U2_MAX, /*     82:MSG_BDC1SD6_CH0     (105U) */
        (U2)U2_MAX, /*     83:MSG_BDC1SD7_CH0     (106U) */
        (U2)U2_MAX, /*     84:MSG_BDC1SD8_CH0     (107U) */
        (U2)U2_MAX, /*     85:MSG_BDC1SD9_CH0     (108U) */
        (U2)U2_MAX, /*     86:MSG_BDC1SE1_CH0     (109U) */
        (U2)U2_MAX, /*     87:MSG_BDC1SE2_CH0     (110U) */
        (U2)U2_MAX, /*     88:MSG_BDC1SE3_CH0     (111U) */
        (U2)U2_MAX, /*     89:MSG_BDC1SE4_CH0     (112U) */
        (U2)U2_MAX, /*     90:MSG_BDC1SE5_CH0     (113U) */
        (U2)U2_MAX, /*     91:MSG_BDC1SE6_CH0     (114U) */
        (U2)U2_MAX, /*     92:MSG_BDC1SE7_CH0     (115U) */
        (U2)U2_MAX, /*     93:MSG_BDC1SH3_CH0     (116U) */
        (U2)21U,    /*     94:MSG_BDC1SH8_CH0     (117U) */
        (U2)U2_MAX, /*     95:MSG_BDC1SI1_CH0     (118U) */
        (U2)U2_MAX, /*     96:MSG_BDC1SI2_CH0     (119U) */
        (U2)U2_MAX, /*     97:MSG_BDC1SI3_CH0     (120U) */
        (U2)U2_MAX, /*     98:MSG_BDC1SI4_CH0     (121U) */
        (U2)U2_MAX, /*     99:MSG_BDC1SI5_CH0     (122U) */
        (U2)U2_MAX, /*    100:MSG_BDC1SI6_CH0     (123U) */
        (U2)U2_MAX, /*    101:MSG_BDC1SI7_CH0     (124U) */
        (U2)U2_MAX, /*    102:MSG_BDC1SI8_CH0     (125U) */
        (U2)U2_MAX, /*    103:MSG_BDC1SI9_CH0     (126U) */
        (U2)U2_MAX, /*    104:MSG_BDC1SJ0_CH0     (127U) */
        (U2)U2_MAX, /*    105:MSG_BDC1SJ1_CH0     (128U) */
        (U2)U2_MAX, /*    106:MSG_BDC1SJ2_CH0     (129U) */
        (U2)U2_MAX, /*    107:MSG_BDC1SJ5_CH0     (130U) */
        (U2)121U,   /*    108:MSG_BDC1SV1_CH0     (131U) */
        (U2)22U,    /*    109:MSG_BDC1SV2_CH0     (132U) */
        (U2)U2_MAX, /*    110:MSG_BDF3S01_CH0     (133U) */
        (U2)U2_MAX, /*    111:MSG_BDF3S02_CH0     (134U) */
        (U2)U2_MAX, /*    112:MSG_BDR3S02_CH0     (135U) */
        (U2)29U,    /*    113:MSG_BKD1S01_CH0     (136U) */
        (U2)U2_MAX, /*    114:MSG_BKD1S02_CH0     (137U) */
        (U2)30U,    /*    115:MSG_BSR1S01_CH0     (138U) */
        (U2)31U,    /*    116:MSG_BSR1S02_CH0     (139U) */
        (U2)32U,    /*    117:MSG_BSR1S03_CH0     (140U) */
        (U2)U2_MAX, /*    118:MSG_CMB1S03_CH0     (141U) */
        (U2)U2_MAX, /*    119:MSG_CMB1S04_CH0     (142U) */
        (U2)U2_MAX, /*    120:MSG_CSR1G10_CH0     (143U) */
        (U2)33U,    /*    121:MSG_CSR1S04_CH0     (144U) */
        (U2)34U,    /*    122:MSG_CSR1S07_CH0     (145U) */
        (U2)35U,    /*    123:MSG_CSR1S08_CH0     (146U) */
        (U2)U2_MAX, /*    124:MSG_DDM1S00_CH0     (147U) */
        (U2)U2_MAX, /*    125:MSG_DDM1S09_CH0     (148U) */
        (U2)36U,    /*    126:MSG_DDM1S12_CH0     (149U) */
        (U2)U2_MAX, /*    127:MSG_DDM1S16_CH0     (150U) */
        (U2)37U,    /*    128:MSG_DDM1S17_CH0     (151U) */
        (U2)U2_MAX, /*    129:MSG_DDM1S32_CH0     (152U) */
        (U2)26U,    /*    130:MSG_DDM1S35_CH0     (153U) */
        (U2)U2_MAX, /*    131:MSG_DDM1SFH_CH0     (154U) */
        (U2)U2_MAX, /*    132:MSG_DKY1S26_CH0     (155U) */
        (U2)38U,    /*    133:MSG_DMC1S08_CH0     (156U) */
        (U2)U2_MAX, /*    134:MSG_DRL1S03_CH0     (157U) */
        (U2)U2_MAX, /*    135:MSG_DRR1S03_CH0     (158U) */
        (U2)U2_MAX, /*    136:MSG_DS11S27_CH0     (159U) */
        (U2)39U,    /*    137:MSG_DS11S37_CH0     (160U) */
        (U2)40U,    /*    138:MSG_DS11S40_CH0     (161U) */
        (U2)41U,    /*    139:MSG_DS12F02_CH0     (162U) */
        (U2)42U,    /*    140:MSG_DS12F03_CH0     (163U) */
        (U2)43U,    /*    141:MSG_DST1S02_CH0     (164U) */
        (U2)U2_MAX, /*    142:MSG_EBU1D01_CH0     (165U) */
        (U2)44U,    /*    143:MSG_ECT1G01_CH0     (166U) */
        (U2)45U,    /*    144:MSG_ECT1G92_CH0     (167U) */
        (U2)U2_MAX, /*    145:MSG_ECT1S80_CH0     (168U) */
        (U2)46U,    /*    146:MSG_ECT1S93_CH0     (169U) */
        (U2)U2_MAX, /*    147:MSG_EHV1E96_CH0     (170U) */
        (U2)U2_MAX, /*    148:MSG_EHV1F02_CH0     (171U) */
        (U2)U2_MAX, /*    149:MSG_EHV1F04_CH0     (172U) */
        (U2)U2_MAX, /*    150:MSG_EHV1G30_CH0     (173U) */
        (U2)U2_MAX, /*    151:MSG_EHV1S23_CH0     (174U) */
        (U2)47U,    /*    152:MSG_EHV1S26_CH0     (175U) */
        (U2)48U,    /*    153:MSG_EHV1S31_CH0     (176U) */
        (U2)49U,    /*    154:MSG_EHV1S90_CH0     (177U) */
        (U2)50U,    /*    155:MSG_EHV1S94_CH0     (178U) */
        (U2)51U,    /*    156:MSG_EHV1S95_CH0     (179U) */
        (U2)52U,    /*    157:MSG_EHV1S96_CH0     (180U) */
        (U2)53U,    /*    158:MSG_EHV1S97_CH0     (181U) */
        (U2)54U,    /*    159:MSG_EHV1S99_CH0     (182U) */
        (U2)55U,    /*    160:MSG_EHV2G02_CH0     (183U) */
        (U2)U2_MAX, /*    161:MSG_EHV2G10_CH0     (184U) */
        (U2)U2_MAX, /*    162:MSG_EHV2G20_CH0     (185U) */
        (U2)56U,    /*    163:MSG_EHV2G70_CH0     (186U) */
        (U2)U2_MAX, /*    164:MSG_EIM1S01_CH0     (187U) */
        (U2)U2_MAX, /*    165:MSG_ENG1C01_CH0     (188U) */
        (U2)U2_MAX, /*    166:MSG_ENG1C02_CH0     (189U) */
        (U2)U2_MAX, /*    167:MSG_ENG1D51_CH0     (190U) */
        (U2)U2_MAX, /*    168:MSG_ENG1D52_CH0     (191U) */
        (U2)U2_MAX, /*    169:MSG_ENG1D53_CH0     (192U) */
        (U2)U2_MAX, /*    170:MSG_ENG1D55_CH0     (193U) */
        (U2)U2_MAX, /*    171:MSG_ENG1D56_CH0     (194U) */
        (U2)U2_MAX, /*    172:MSG_ENG1D59_CH0     (195U) */
        (U2)U2_MAX, /*    173:MSG_ENG1D60_CH0     (196U) */
        (U2)57U,    /*    174:MSG_ENG1G03_CH0     (197U) */
        (U2)U2_MAX, /*    175:MSG_ENG1G13_CH0     (198U) */
        (U2)U2_MAX, /*    176:MSG_ENG1G17_CH0     (199U) */
        (U2)58U,    /*    177:MSG_ENG1G90_CH0     (200U) */
        (U2)59U,    /*    178:MSG_ENG1G92_CH0     (201U) */
        (U2)60U,    /*    179:MSG_ENG1S60_CH0     (202U) */
        (U2)61U,    /*    180:MSG_ENG1S99_CH0     (203U) */
        (U2)U2_MAX, /*    181:MSG_EPS1D50_CH0     (204U) */
        (U2)62U,    /*    182:MSG_EPS1S11_CH0     (205U) */
        (U2)63U,    /*    183:MSG_EPS1S90_CH0     (206U) */
        (U2)U2_MAX, /*    184:MSG_FCM1C01_CH0     (207U) */
        (U2)64U,    /*    185:MSG_FCM1S10_CH0     (208U) */
        (U2)65U,    /*    186:MSG_FCM1S12_CH0     (209U) */
        (U2)66U,    /*    187:MSG_FCM1S39_CH0     (210U) */
        (U2)67U,    /*    188:MSG_FCM1S40_CH0     (211U) */
        (U2)68U,    /*    189:MSG_FCM1S41_CH0     (212U) */
        (U2)U2_MAX, /*    190:MSG_FCM1S49_CH0     (213U) */
        (U2)69U,    /*    191:MSG_FCM1S51_CH0     (214U) */
        (U2)70U,    /*    192:MSG_FCM1S52_CH0     (215U) */
        (U2)71U,    /*    193:MSG_FCM1S58_CH0     (216U) */
        (U2)72U,    /*    194:MSG_FCM1S70_CH0     (217U) */
        (U2)U2_MAX, /*    195:MSG_FCM1S76_CH0     (218U) */
        (U2)73U,    /*    196:MSG_FCM1S78_CH0     (219U) */
        (U2)U2_MAX, /*    197:MSG_FCM1S79_CH0     (220U) */
        (U2)U2_MAX, /*    198:MSG_FCM1S90_CH0     (221U) */
        (U2)74U,    /*    199:MSG_FCM1S92_CH0     (222U) */
        (U2)U2_MAX, /*    200:MSG_FCM1S95_CH0     (223U) */
        (U2)75U,    /*    201:MSG_FWD1S10_CH0     (224U) */
        (U2)76U,    /*    202:MSG_IDT1S02_CH0     (225U) */
        (U2)U2_MAX, /*    203:MSG_IDT1S07_CH0     (226U) */
        (U2)U2_MAX, /*    204:MSG_IDT1S15_CH0     (227U) */
        (U2)77U,    /*    205:MSG_IPA1S05_CH0     (228U) */
        (U2)78U,    /*    206:MSG_ITS1S01_CH0     (229U) */
        (U2)U2_MAX, /*    207:MSG_ITS1S04_CH0     (230U) */
        (U2)79U,    /*    208:MSG_ITS1S05_CH0     (231U) */
        (U2)80U,    /*    209:MSG_LVN1S01_CH0     (232U) */
        (U2)U2_MAX, /*    210:MSG_MET1S33_CH0     (233U) */
        (U2)U2_MAX, /*    211:MSG_MGC1F13_CH0     (234U) */
        (U2)81U,    /*    212:MSG_PCN1S01_CH0     (235U) */
        (U2)U2_MAX, /*    213:MSG_PDC1G01_CH0     (236U) */
        (U2)82U,    /*    214:MSG_PDC1G02_CH0     (237U) */
        (U2)83U,    /*    215:MSG_PDS1S01_CH0     (238U) */
        (U2)U2_MAX, /*    216:MSG_PLG1G15_CH0     (239U) */
        (U2)84U,    /*    217:MSG_PLG1G16_CH0     (240U) */
        (U2)85U,    /*    218:MSG_PLG1S01_CH0     (241U) */
        (U2)86U,    /*    219:MSG_PLG1S06_CH0     (242U) */
        (U2)87U,    /*    220:MSG_PLG1S20_CH0     (243U) */
        (U2)88U,    /*    221:MSG_PLG1S21_CH0     (244U) */
        (U2)89U,    /*    222:MSG_PMN1G03_CH0     (245U) */
        (U2)90U,    /*    223:MSG_PST1S01_CH0     (246U) */
        (U2)U2_MAX, /*    224:MSG_RCP1S02_CH0     (247U) */
        (U2)U2_MAX, /*    225:MSG_RCP1S03_CH0     (248U) */
        (U2)U2_MAX, /*    226:MSG_RCP1S04_CH0     (249U) */
        (U2)U2_MAX, /*    227:MSG_RCP1S05_CH0     (250U) */
        (U2)U2_MAX, /*    228:MSG_RCP1S06_CH0     (251U) */
        (U2)91U,    /*    229:MSG_RSE1G20_CH0     (252U) */
        (U2)U2_MAX, /*    230:MSG_RSE1G24_CH0     (253U) */
        (U2)U2_MAX, /*    231:MSG_RSE1G25_CH0     (254U) */
        (U2)U2_MAX, /*    232:MSG_RSE1G26_CH0     (255U) */
        (U2)U2_MAX, /*    233:MSG_RSE1S02_CH0     (256U) */
        (U2)92U,    /*    234:MSG_SBW1G02_CH0     (257U) */
        (U2)93U,    /*    235:MSG_SCN1S01_CH0     (258U) */
        (U2)94U,    /*    236:MSG_SCN1S02_CH0     (259U) */
        (U2)U2_MAX, /*    237:MSG_SCS1S10_CH0     (260U) */
        (U2)95U,    /*    238:MSG_SCS1S11_CH0     (261U) */
        (U2)96U,    /*    239:MSG_SCS1S14_CH0     (262U) */
        (U2)97U,    /*    240:MSG_SOL1S02_CH0     (263U) */
        (U2)98U,    /*    241:MSG_SOL1S06_CH0     (264U) */
        (U2)99U,    /*    242:MSG_TPM1S02_CH0     (265U) */
        (U2)100U,   /*    243:MSG_TPM1S03_CH0     (266U) */
        (U2)101U,   /*    244:MSG_TPM1S04_CH0     (267U) */
        (U2)102U,   /*    245:MSG_TPM1S05_CH0     (268U) */
        (U2)103U,   /*    246:MSG_TPM1S07_CH0     (269U) */
        (U2)104U,   /*    247:MSG_TRA1S01_CH0     (270U) */
        (U2)105U,   /*    248:MSG_UCB1S01_CH0     (271U) */
        (U2)106U,   /*    249:MSG_VAS1S01_CH0     (272U) */
        (U2)U2_MAX, /*    250:MSG_VGR1D50_CH0     (273U) */
        (U2)U2_MAX, /*    251:MSG_VSC1D51_CH0     (274U) */
        (U2)U2_MAX, /*    252:MSG_VSC1F01_CH0     (275U) */
        (U2)107U,   /*    253:MSG_VSC1G12_CH0     (276U) */
        (U2)108U,   /*    254:MSG_VSC1G13_CH0     (277U) */
        (U2)U2_MAX, /*    255:MSG_VSC1G14_CH0     (278U) */
        (U2)109U,   /*    256:MSG_VSC1G96_CH0     (279U) */
        (U2)U2_MAX, /*    257:MSG_VUM1S01_CH0     (280U) */
        (U2)U2_MAX, /*    258:MSG_WIP1S01_CH0     (281U) */
        (U2)U2_MAX, /*    259:MSG_ZN11S02_CH0     (282U) */
        (U2)U2_MAX, /*    260:MSG_ZN11S03_CH0     (283U) */
        (U2)U2_MAX, /*    261:MSG_ZN11S08_CH0     (284U) */
        (U2)14U,    /*    262:MSG_ZN11S14_CH0     (285U) */
        (U2)110U,   /*    263:MSG_ZN11S17_CH0     (286U) */
        (U2)111U,   /*    264:MSG_ZN11S19_CH0     (287U) */
        (U2)112U,   /*    265:MSG_ZN11S26_CH0     (288U) */
        (U2)U2_MAX, /*    266:MSG_ZN11S32_CH0     (289U) */
        (U2)113U,   /*    267:MSG_ZN11S38_CH0     (290U) */
        (U2)114U,   /*    268:MSG_ZN11S60_CH0     (291U) */
        (U2)U2_MAX, /*    269:MSG_ZN11S63_CH0     (292U) */
        (U2)U2_MAX, /*    270:MSG_ZN11S64_CH0     (293U) */
        (U2)U2_MAX, /*    271:MSG_ZN11S65_CH0     (294U) */
        (U2)U2_MAX, /*    272:MSG_ZN11S66_CH0     (295U) */
        (U2)U2_MAX, /*    273:MSG_ZN11S67_CH0     (296U) */
        (U2)U2_MAX, /*    274:MSG_ZN11SF6_CH0     (297U) */
        (U2)U2_MAX, /*    275:MSG_ZN11SF7_CH0     (298U) */
        (U2)U2_MAX, /*    276:MSG_ZN21S05_CH0     (299U) */
        (U2)115U,   /*    277:MSG_ZN21S13_CH0     (300U) */
        (U2)U2_MAX  /*    278:MSG_ZN21S72_CH0     (301U) */
    };

    U2  u2_t_idx;
    U2  u2_t_pos;
    U1  u1_t_dlc;
    U1  u1_tp_sgnl[XSPI_MET_CAN_64];
    
    if((u2_a_MSG >= u2_s_XSPI_MET_CANGW_MIN) &&
       (u2_a_MSG <= u2_s_XSPI_MET_CANGW_MAX)    ){
        u2_t_idx = u2_sp_XSPI_MET_CANGW_OX2IDX[u2_a_MSG - u2_s_XSPI_MET_CANGW_MIN];
        if(u2_t_idx != (U2)U2_MAX){
            u2_t_pos = st_sp_XSPI_MET_MSG2POSLEN[u2_t_idx].u2_pos;
            u1_t_dlc = st_sp_XSPI_MET_MSG2POSLEN[u2_t_idx].u1_dlc;

            vd_g_MemfillU1(&u1_tp_sgnl[0], (U1)0U, (U1)XSPI_MET_CAN_64);

            (void)Com_ReadIPDU((PduIdType)u2_a_MSG, &u1_tp_sgnl[0] );
            (*fp_sp_XSPI_MET_CANGW_PAD[u1_t_dlc])(&u1_tp_sgnl[0], &u4_s_xspi_rte_gw[u2_t_pos]);
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiMETPduTxCAN(U4 * u4_ap_TX_HEAD, const ST_XSPIMET_CAN_TXCFG stp_a_TX_CFG)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiMETPduTxCAN(U4 * u4_ap_TX_HEAD, const ST_XSPIMET_CAN_TXCFG * const stp_a_TX_CFG)
{
    U4                          u4_t_loop;
    U4 *                        u4p_t_data;
    U4 *                        u4p_t_src;
    U4                          u4_t_num;
    const ST_XSPI_MET_MSG2POSLEN *    stp_t_msg2poslen;
    U2                          u2_t_msgidx;
    U1                          u1_t_pdusts;
    U1                          u2_t_bitsft;
    U2                          u2_t_idx;

    if((u4_ap_TX_HEAD != vdp_PTR_NA) && 
       (stp_a_TX_CFG  != vdp_PTR_NA)){

        u4p_t_data = &u4_ap_TX_HEAD[0];
        for(u4_t_loop = (U4)(stp_a_TX_CFG->u2_sts_sta) ; u4_t_loop <= (U4)(stp_a_TX_CFG->u2_sts_end) ; u4_t_loop++){
            *u4p_t_data = (U4)0U;
            u4p_t_data++;
        }

        u4p_t_data = &u4_ap_TX_HEAD[0];
        stp_t_msg2poslen = &st_sp_XSPI_MET_MSG2POSLEN[st_s_XSPI_MET_CANGW_RTE_BUF_STA[XSPIMETCANGW_BLOCK].u2_idx];
        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)st_s_XSPI_MET_CANGW_RTE_BUF_STA[XSPIMETCANGW_BLOCK].u2_num_idx; u4_t_loop++){
            u2_t_msgidx           = stp_t_msg2poslen->u2_msg;
            u1_t_pdusts           = Com_GetIPDUStatus( (PduIdType)u2_t_msgidx ) & ((U1)COM_NO_RX | (U1)COM_TIMEOUT);
            u2_t_bitsft           = stp_t_msg2poslen->u2_stspos   &  (U2)XSPI_MET_BITSHIFT_CALCMASK;
            u2_t_idx              = (stp_t_msg2poslen->u2_stspos  >> XSPI_MET_INDEX_CALCSHIFT );
            u4p_t_data[u2_t_idx] |= (U4)u1_t_pdusts  <<     (u2_t_bitsft << 1);
            stp_t_msg2poslen++;
        }

        u4p_t_data = &u4_ap_TX_HEAD[stp_a_TX_CFG->u2_pdu_sta];
        u4p_t_src  = &u4_s_xspi_rte_gw[st_s_XSPI_MET_CANGW_RTE_BUF_STA[XSPIMETCANGW_BLOCK].u2_buf];
        u4_t_num   = (U4)(st_s_XSPI_MET_CANGW_RTE_BUF_STA[XSPIMETCANGW_BLOCK].u2_num_buf);
        vd_g_MemcpyU4(u4p_t_data, u4p_t_src, u4_t_num);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_XSpiMETPad08(const U1 * u1_a_SRC, U4 * u4_a_DST)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_XSpiMETPad08(const U1 * u1_a_SRC, U4 * u4_a_DST)
{
    u4_a_DST[0]  = ((U4)u1_a_SRC[0])    << 24;
    u4_a_DST[0] |= ((U4)u1_a_SRC[1])    << 16;
    u4_a_DST[0] |= ((U4)u1_a_SRC[2])    <<  8;
    u4_a_DST[0] |= ((U4)u1_a_SRC[3]);/* <<  0;*/
    u4_a_DST[1]  = ((U4)u1_a_SRC[4])    << 24;
    u4_a_DST[1] |= ((U4)u1_a_SRC[5])    << 16;
    u4_a_DST[1] |= ((U4)u1_a_SRC[6])    <<  8;
    u4_a_DST[1] |= ((U4)u1_a_SRC[7]);/* <<  0;*/
}

static void vd_s_XSpiMETPad32(const U1 * u1_a_SRC, U4 * u4_a_DST)
{
    u4_a_DST[0]  = ((U4)u1_a_SRC[ 0])    << 24;
    u4_a_DST[0] |= ((U4)u1_a_SRC[ 1])    << 16;
    u4_a_DST[0] |= ((U4)u1_a_SRC[ 2])    <<  8;
    u4_a_DST[0] |= ((U4)u1_a_SRC[ 3]);/* <<  0;*/
    u4_a_DST[1]  = ((U4)u1_a_SRC[ 4])    << 24;
    u4_a_DST[1] |= ((U4)u1_a_SRC[ 5])    << 16;
    u4_a_DST[1] |= ((U4)u1_a_SRC[ 6])    <<  8;
    u4_a_DST[1] |= ((U4)u1_a_SRC[ 7]);/* <<  0;*/
    u4_a_DST[2]  = ((U4)u1_a_SRC[ 8])    << 24;
    u4_a_DST[2] |= ((U4)u1_a_SRC[ 9])    << 16;
    u4_a_DST[2] |= ((U4)u1_a_SRC[10])    <<  8;
    u4_a_DST[2] |= ((U4)u1_a_SRC[11]);/* <<  0;*/
    u4_a_DST[3]  = ((U4)u1_a_SRC[12])    << 24;
    u4_a_DST[3] |= ((U4)u1_a_SRC[13])    << 16;
    u4_a_DST[3] |= ((U4)u1_a_SRC[14])    <<  8;
    u4_a_DST[3] |= ((U4)u1_a_SRC[15]);/* <<  0;*/
    u4_a_DST[4]  = ((U4)u1_a_SRC[16])    << 24;
    u4_a_DST[4] |= ((U4)u1_a_SRC[17])    << 16;
    u4_a_DST[4] |= ((U4)u1_a_SRC[18])    <<  8;
    u4_a_DST[4] |= ((U4)u1_a_SRC[19]);/* <<  0;*/
    u4_a_DST[5]  = ((U4)u1_a_SRC[20])    << 24;
    u4_a_DST[5] |= ((U4)u1_a_SRC[21])    << 16;
    u4_a_DST[5] |= ((U4)u1_a_SRC[22])    <<  8;
    u4_a_DST[5] |= ((U4)u1_a_SRC[23]);/* <<  0;*/
    u4_a_DST[6]  = ((U4)u1_a_SRC[24])    << 24;
    u4_a_DST[6] |= ((U4)u1_a_SRC[25])    << 16;
    u4_a_DST[6] |= ((U4)u1_a_SRC[26])    <<  8;
    u4_a_DST[6] |= ((U4)u1_a_SRC[27]);/* <<  0;*/
    u4_a_DST[7]  = ((U4)u1_a_SRC[28])    << 24;
    u4_a_DST[7] |= ((U4)u1_a_SRC[29])    << 16;
    u4_a_DST[7] |= ((U4)u1_a_SRC[30])    <<  8;
    u4_a_DST[7] |= ((U4)u1_a_SRC[31]);/* <<  0;*/
}
static void vd_s_XSpiMETPad64(const U1 * u1_a_SRC, U4 * u4_a_DST)
{
    u4_a_DST[ 0]  = ((U4)u1_a_SRC[ 0])    << 24;
    u4_a_DST[ 0] |= ((U4)u1_a_SRC[ 1])    << 16;
    u4_a_DST[ 0] |= ((U4)u1_a_SRC[ 2])    <<  8;
    u4_a_DST[ 0] |= ((U4)u1_a_SRC[ 3]);/* <<  0;*/
    u4_a_DST[ 1]  = ((U4)u1_a_SRC[ 4])    << 24;
    u4_a_DST[ 1] |= ((U4)u1_a_SRC[ 5])    << 16;
    u4_a_DST[ 1] |= ((U4)u1_a_SRC[ 6])    <<  8;
    u4_a_DST[ 1] |= ((U4)u1_a_SRC[ 7]);/* <<  0;*/
    u4_a_DST[ 2]  = ((U4)u1_a_SRC[ 8])    << 24;
    u4_a_DST[ 2] |= ((U4)u1_a_SRC[ 9])    << 16;
    u4_a_DST[ 2] |= ((U4)u1_a_SRC[10])    <<  8;
    u4_a_DST[ 2] |= ((U4)u1_a_SRC[11]);/* <<  0;*/
    u4_a_DST[ 3]  = ((U4)u1_a_SRC[12])    << 24;
    u4_a_DST[ 3] |= ((U4)u1_a_SRC[13])    << 16;
    u4_a_DST[ 3] |= ((U4)u1_a_SRC[14])    <<  8;
    u4_a_DST[ 3] |= ((U4)u1_a_SRC[15]);/* <<  0;*/
    u4_a_DST[ 4]  = ((U4)u1_a_SRC[16])    << 24;
    u4_a_DST[ 4] |= ((U4)u1_a_SRC[17])    << 16;
    u4_a_DST[ 4] |= ((U4)u1_a_SRC[18])    <<  8;
    u4_a_DST[ 4] |= ((U4)u1_a_SRC[19]);/* <<  0;*/
    u4_a_DST[ 5]  = ((U4)u1_a_SRC[20])    << 24;
    u4_a_DST[ 5] |= ((U4)u1_a_SRC[21])    << 16;
    u4_a_DST[ 5] |= ((U4)u1_a_SRC[22])    <<  8;
    u4_a_DST[ 5] |= ((U4)u1_a_SRC[23]);/* <<  0;*/
    u4_a_DST[ 6]  = ((U4)u1_a_SRC[24])    << 24;
    u4_a_DST[ 6] |= ((U4)u1_a_SRC[25])    << 16;
    u4_a_DST[ 6] |= ((U4)u1_a_SRC[26])    <<  8;
    u4_a_DST[ 6] |= ((U4)u1_a_SRC[27]);/* <<  0;*/
    u4_a_DST[ 7]  = ((U4)u1_a_SRC[28])    << 24;
    u4_a_DST[ 7] |= ((U4)u1_a_SRC[29])    << 16;
    u4_a_DST[ 7] |= ((U4)u1_a_SRC[30])    <<  8;
    u4_a_DST[ 7] |= ((U4)u1_a_SRC[31]);/* <<  0;*/
    u4_a_DST[ 8]  = ((U4)u1_a_SRC[32])    << 24;
    u4_a_DST[ 8] |= ((U4)u1_a_SRC[33])    << 16;
    u4_a_DST[ 8] |= ((U4)u1_a_SRC[34])    <<  8;
    u4_a_DST[ 8] |= ((U4)u1_a_SRC[35]);/* <<  0;*/
    u4_a_DST[ 9]  = ((U4)u1_a_SRC[36])    << 24;
    u4_a_DST[ 9] |= ((U4)u1_a_SRC[37])    << 16;
    u4_a_DST[ 9] |= ((U4)u1_a_SRC[38])    <<  8;
    u4_a_DST[ 9] |= ((U4)u1_a_SRC[39]);/* <<  0;*/
    u4_a_DST[10]  = ((U4)u1_a_SRC[40])    << 24;
    u4_a_DST[10] |= ((U4)u1_a_SRC[41])    << 16;
    u4_a_DST[10] |= ((U4)u1_a_SRC[42])    <<  8;
    u4_a_DST[10] |= ((U4)u1_a_SRC[43]);/* <<  0;*/
    u4_a_DST[11]  = ((U4)u1_a_SRC[44])    << 24;
    u4_a_DST[11] |= ((U4)u1_a_SRC[45])    << 16;
    u4_a_DST[11] |= ((U4)u1_a_SRC[46])    <<  8;
    u4_a_DST[11] |= ((U4)u1_a_SRC[47]);/* <<  0;*/
    u4_a_DST[12]  = ((U4)u1_a_SRC[48])    << 24;
    u4_a_DST[12] |= ((U4)u1_a_SRC[49])    << 16;
    u4_a_DST[12] |= ((U4)u1_a_SRC[50])    <<  8;
    u4_a_DST[12] |= ((U4)u1_a_SRC[51]);/* <<  0;*/
    u4_a_DST[13]  = ((U4)u1_a_SRC[52])    << 24;
    u4_a_DST[13] |= ((U4)u1_a_SRC[53])    << 16;
    u4_a_DST[13] |= ((U4)u1_a_SRC[54])    <<  8;
    u4_a_DST[13] |= ((U4)u1_a_SRC[55]);/* <<  0;*/
    u4_a_DST[14]  = ((U4)u1_a_SRC[56])    << 24;
    u4_a_DST[14] |= ((U4)u1_a_SRC[57])    << 16;
    u4_a_DST[14] |= ((U4)u1_a_SRC[58])    <<  8;
    u4_a_DST[14] |= ((U4)u1_a_SRC[59]);/* <<  0;*/
    u4_a_DST[15]  = ((U4)u1_a_SRC[60])    << 24;
    u4_a_DST[15] |= ((U4)u1_a_SRC[61])    << 16;
    u4_a_DST[15] |= ((U4)u1_a_SRC[62])    <<  8;
    u4_a_DST[15] |= ((U4)u1_a_SRC[63]);/* <<  0;*/

}

/*===================================================================================================================================*/
/*  void    vd_s_XSpiMETTxSCL(U4 * u4_ap_pdu_tx)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiMETTxSCL(U4 * u4_ap_pdu_tx)
{
    U1 u1_t_ecscl;
    U1 u1_t_unit6;
    U1 u1_t_odo_unit;
    U1 u1_t_dbkl_met;
    U1 u1_t_pbkl_met;
    U1 u1_t_rlbklmet;
    U1 u1_t_rcbklmet;
    U1 u1_t_rrbklmet;
    U1 u1_t_bkl3lmet;
    U1 u1_t_bkl3cmet;
    U1 u1_t_bkl3rmet;
    U4 u4_t_odo;
    
    u1_t_ecscl    = (U1)0U;
    u1_t_unit6    = (U1)0U;
    u1_t_odo_unit = (U1)0U;
    u1_t_dbkl_met = (U1)0U;
    u1_t_pbkl_met = (U1)0U;
    u1_t_rlbklmet = (U1)0U;
    u1_t_rcbklmet = (U1)0U;
    u1_t_rrbklmet = (U1)0U;
    u1_t_bkl3lmet = (U1)0U;
    u1_t_bkl3cmet = (U1)0U;
    u1_t_bkl3rmet = (U1)0U;
    u4_t_odo      = (U4)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_EC_SCL,   &u1_t_ecscl);
    (void)Com_ReceiveSignal(ComConf_ComSignal_UNIT_6,   &u1_t_unit6);
    (void)Com_ReceiveSignal(ComConf_ComSignal_ODO_UNIT, &u1_t_odo_unit);
    (void)Com_ReceiveSignal(ComConf_ComSignal_DBKL_MET, &u1_t_dbkl_met);
    (void)Com_ReceiveSignal(ComConf_ComSignal_PBKL_MET, &u1_t_pbkl_met);
    (void)Com_ReceiveSignal(ComConf_ComSignal_RLBKLMET, &u1_t_rlbklmet);
    (void)Com_ReceiveSignal(ComConf_ComSignal_RCBKLMET, &u1_t_rcbklmet);
    (void)Com_ReceiveSignal(ComConf_ComSignal_RRBKLMET, &u1_t_rrbklmet);
    (void)Com_ReceiveSignal(ComConf_ComSignal_BKL3LMET, &u1_t_bkl3lmet);
    (void)Com_ReceiveSignal(ComConf_ComSignal_BKL3CMET, &u1_t_bkl3cmet);
    (void)Com_ReceiveSignal(ComConf_ComSignal_BKL3RMET, &u1_t_bkl3rmet);
    (void)Com_ReceiveSignal(ComConf_ComSignal_ODO,      &u4_t_odo);

    u4_ap_pdu_tx[0]  = ((U4)u1_t_ecscl << 3);      /* EC_SCL   */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_unit6 << 6);      /* UNIT_6   */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_odo_unit << 9);   /* ODO_UNIT */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_dbkl_met << 16);  /* DBKL_MET */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_pbkl_met << 18);  /* PBKL_MET */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_rlbklmet << 20);  /* RLBKLMET */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_rcbklmet << 22);  /* RCBKLMET */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_rrbklmet << 24);  /* RRBKLMET */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_bkl3lmet << 26);  /* BKL3LMET */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_bkl3cmet << 28);  /* BKL3CMET */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_bkl3rmet << 30);  /* BKL3RMET */
    u4_ap_pdu_tx[1]  = u4_t_odo;                   /* ODO      */

}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Rx Functions                                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    12/18/2024  KT       New.                                                                                               */
/*  0.1.0    06/09/2025  KT       Change for xspi IF.(1byte -> 4byte)                                                                */
/*  0.2.0    07/07/2025  KT       Change for BEV System_Consideration_2.(CAN V7.3)                                                   */
/*  0.3.0    10/02/2025  TN       Refer to xspi_met.c.                                                                               */
/*  0.4.0    12/09/2025  TN       Refer to xspi_met.c.                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
