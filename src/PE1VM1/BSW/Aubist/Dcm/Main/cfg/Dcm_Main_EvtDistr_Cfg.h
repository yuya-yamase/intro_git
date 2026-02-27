/* Dcm_Main_EvtDistr_Cfg_h(v5-9-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Main_EvtDistr_Cfg/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_MAIN_EVTDISTR_CFG_H
#define DCM_MAIN_EVTDISTR_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_M_EVTDISTR_QUEUE_DSL_MAX    ((uint8)0x11U)      /* Queue length limit DSL */
#define DCM_M_EVTDISTR_QUEUE_DSP_MAX    ((uint8)0x03U)      /* Queue length limit DSP */
#define DCM_M_EVTDISTR_QUEUE_EX_MAX     ((uint8)0x00U)      /* Queue length limit Extend */
#define DCM_M_EVTDISTR_QUEUE_MAX        (DCM_M_EVTDISTR_QUEUE_DSL_MAX + DCM_M_EVTDISTR_QUEUE_DSP_MAX + DCM_M_EVTDISTR_QUEUE_EX_MAX)      /* Queue length limit */
#define DCM_M_EVTDISTR_DEQUEUENUM       ((uint8)0x00U)      /* One periodic send event limit */

#define DCM_M_EVTDISTR_INVALID_VAL      ((uint8)255U)

/* Event ID */
#define DCM_M_EVTDISTR_ID_000               ((uint8)0U)
#define DCM_M_EVTDISTR_ID_001               ((uint8)1U)
#define DCM_M_EVTDISTR_ID_002               ((uint8)2U)
#define DCM_M_EVTDISTR_ID_003               ((uint8)3U)
#define DCM_M_EVTDISTR_ID_004               ((uint8)4U)
#define DCM_M_EVTDISTR_ID_005               ((uint8)5U)
#define DCM_M_EVTDISTR_ID_006               ((uint8)6U)
#define DCM_M_EVTDISTR_ID_007               ((uint8)7U)
#define DCM_M_EVTDISTR_ID_008               ((uint8)8U)
#define DCM_M_EVTDISTR_ID_009               ((uint8)9U)
#define DCM_M_EVTDISTR_ID_010               ((uint8)10U)
#define DCM_M_EVTDISTR_ID_011               ((uint8)11U)
#define DCM_M_EVTDISTR_ID_012               ((uint8)12U)
#define DCM_M_EVTDISTR_ID_013               ((uint8)13U)
#define DCM_M_EVTDISTR_ID_014               ((uint8)14U)
#define DCM_M_EVTDISTR_ID_015               ((uint8)15U)
#define DCM_M_EVTDISTR_ID_016               ((uint8)16U)
#define DCM_M_EVTDISTR_ID_017               ((uint8)17U)
#define DCM_M_EVTDISTR_ID_018               ((uint8)18U)
#define DCM_M_EVTDISTR_ID_019               ((uint8)19U)
#define DCM_M_EVTDISTR_ID_020               ((uint8)20U)
#define DCM_M_EVTDISTR_ID_021               ((uint8)21U)
#define DCM_M_EVTDISTR_ID_022               ((uint8)22U)
#define DCM_M_EVTDISTR_ID_023               ((uint8)23U)
#define DCM_M_EVTDISTR_ID_024               ((uint8)24U)
#define DCM_M_EVTDISTR_ID_025               ((uint8)25U)
#define DCM_M_EVTDISTR_ID_026               ((uint8)26U)
#define DCM_M_EVTDISTR_ID_027               ((uint8)27U)
#define DCM_M_EVTDISTR_ID_028               ((uint8)28U)
#define DCM_M_EVTDISTR_ID_029               ((uint8)29U)
#define DCM_M_EVTDISTR_ID_030               ((uint8)30U)
#define DCM_M_EVTDISTR_ID_031               ((uint8)31U)
#define DCM_M_EVTDISTR_ID_032               ((uint8)32U)
#define DCM_M_EVTDISTR_ID_033               ((uint8)33U)
#define DCM_M_EVTDISTR_ID_034               ((uint8)34U)
#define DCM_M_EVTDISTR_ID_035               ((uint8)35U)
#define DCM_M_EVTDISTR_ID_036               ((uint8)36U)
#define DCM_M_EVTDISTR_ID_037               ((uint8)37U)
#define DCM_M_EVTDISTR_ID_038               ((uint8)38U)
#define DCM_M_EVTDISTR_ID_039               ((uint8)39U)
#define DCM_M_EVTDISTR_ID_040               ((uint8)40U)
#define DCM_M_EVTDISTR_ID_041               ((uint8)41U)
#define DCM_M_EVTDISTR_ID_042               ((uint8)42U)
#define DCM_M_EVTDISTR_ID_043               ((uint8)43U)
#define DCM_M_EVTDISTR_ID_044               ((uint8)44U)
#define DCM_M_EVTDISTR_ID_045               ((uint8)45U)
#define DCM_M_EVTDISTR_ID_046               ((uint8)46U)
#define DCM_M_EVTDISTR_ID_047               ((uint8)47U)
#define DCM_M_EVTDISTR_ID_048               ((uint8)48U)
#define DCM_M_EVTDISTR_ID_049               ((uint8)49U)
#define DCM_M_EVTDISTR_ID_050               ((uint8)50U)
#define DCM_M_EVTDISTR_ID_051               ((uint8)51U)
#define DCM_M_EVTDISTR_ID_052               ((uint8)52U)
#define DCM_M_EVTDISTR_ID_053               ((uint8)53U)
#define DCM_M_EVTDISTR_ID_054               ((uint8)54U)
#define DCM_M_EVTDISTR_ID_055               ((uint8)55U)
#define DCM_M_EVTDISTR_ID_056               ((uint8)56U)
#define DCM_M_EVTDISTR_ID_057               ((uint8)57U)
#define DCM_M_EVTDISTR_ID_058               ((uint8)58U)
#define DCM_M_EVTDISTR_ID_059               ((uint8)59U)
#define DCM_M_EVTDISTR_ID_060               ((uint8)60U)
#define DCM_M_EVTDISTR_ID_061               ((uint8)61U)
#define DCM_M_EVTDISTR_ID_062               ((uint8)62U)
#define DCM_M_EVTDISTR_ID_063               ((uint8)63U)
#define DCM_M_EVTDISTR_ID_064               ((uint8)64U)
#define DCM_M_EVTDISTR_ID_065               ((uint8)65U)
#define DCM_M_EVTDISTR_ID_066               ((uint8)66U)
#define DCM_M_EVTDISTR_ID_067               ((uint8)67U)
#define DCM_M_EVTDISTR_ID_068               ((uint8)68U)
#define DCM_M_EVTDISTR_ID_069               ((uint8)69U)
#define DCM_M_EVTDISTR_ID_070               ((uint8)70U)
#define DCM_M_EVTDISTR_ID_071               ((uint8)71U)
#define DCM_M_EVTDISTR_ID_072               ((uint8)72U)
#define DCM_M_EVTDISTR_ID_073               ((uint8)73U)
#define DCM_M_EVTDISTR_ID_074               ((uint8)74U)
#define DCM_M_EVTDISTR_ID_075               ((uint8)75U)
#define DCM_M_EVTDISTR_ID_076               ((uint8)76U)
#define DCM_M_EVTDISTR_ID_077               ((uint8)77U)
#define DCM_M_EVTDISTR_ID_078               ((uint8)78U)
#define DCM_M_EVTDISTR_ID_079               ((uint8)79U)
#define DCM_M_EVTDISTR_ID_080               ((uint8)80U)
#define DCM_M_EVTDISTR_ID_081               ((uint8)81U)
#define DCM_M_EVTDISTR_ID_082               ((uint8)82U)
#define DCM_M_EVTDISTR_ID_083               ((uint8)83U)
#define DCM_M_EVTDISTR_ID_084               ((uint8)84U)
#define DCM_M_EVTDISTR_ID_085               ((uint8)85U)
#define DCM_M_EVTDISTR_ID_086               ((uint8)86U)
#define DCM_M_EVTDISTR_ID_087               ((uint8)87U)
#define DCM_M_EVTDISTR_ID_088               ((uint8)88U)
#define DCM_M_EVTDISTR_ID_089               ((uint8)89U)
#define DCM_M_EVTDISTR_ID_090               ((uint8)90U)
#define DCM_M_EVTDISTR_ID_091               ((uint8)91U)
#define DCM_M_EVTDISTR_ID_092               ((uint8)92U)
#define DCM_M_EVTDISTR_ID_093               ((uint8)93U)
#define DCM_M_EVTDISTR_ID_094               ((uint8)94U)
#define DCM_M_EVTDISTR_ID_095               ((uint8)95U)
#define DCM_M_EVTDISTR_ID_096               ((uint8)96U)
#define DCM_M_EVTDISTR_ID_097               ((uint8)97U)
#define DCM_M_EVTDISTR_ID_098               ((uint8)98U)
#define DCM_M_EVTDISTR_ID_099               ((uint8)99U)
#define DCM_M_EVTDISTR_ID_100               ((uint8)100U)
#define DCM_M_EVTDISTR_ID_101               ((uint8)101U)
#define DCM_M_EVTDISTR_ID_102               ((uint8)102U)
#define DCM_M_EVTDISTR_ID_103               ((uint8)103U)
#define DCM_M_EVTDISTR_ID_104               ((uint8)104U)
#define DCM_M_EVTDISTR_ID_105               ((uint8)105U)
#define DCM_M_EVTDISTR_ID_106               ((uint8)106U)
#define DCM_M_EVTDISTR_DEFINED_LAST_ID      ((uint8)106U)
#define DCM_M_EVTDISTR_DEFINED_ALL_ID_NUM   ((uint8)(DCM_M_EVTDISTR_DEFINED_LAST_ID + (uint8)1U))
#define DCM_M_EVTDISTR_ID_NUM               ((uint8)34U)     /* Event ID number */

#define DCM_M_EVTDISTR_ID_EX_NUM            ((uint8)0U)

#define DCM_M_EVTDISTR_ID_EX_TBL            (DCM_M_EVTDISTR_ID_EX_NUM + (uint8)1U)

#define DCM_M_EVTID_DSL_RECEIVE             (DCM_M_EVTDISTR_ID_000)
#define DCM_M_EVTID_DSL_TRANSMIT            (DCM_M_EVTDISTR_ID_001)
#define DCM_M_EVTID_DSL_CANCELRECEIVE       (DCM_M_EVTDISTR_ID_002)
#define DCM_M_EVTID_DSL_CANCELTXSERVICE     (DCM_M_EVTDISTR_ID_003)
#define DCM_M_EVTID_DSL_CONF_FUNCTIONALITY  (DCM_M_EVTDISTR_ID_004)
#define DCM_M_EVTID_DSL_SETDEFSES           (DCM_M_EVTDISTR_ID_005)
#define DCM_M_EVTID_DSL_TXRETRY             (DCM_M_EVTDISTR_ID_006)
#define DCM_M_EVTID_DSL_RESPREQ_AFRST       (DCM_M_EVTDISTR_ID_007)
#define DCM_M_EVTID_DSL_COMM_ACTIVE         (DCM_M_EVTDISTR_ID_008)
#define DCM_M_EVTID_DSL_PAGEDBUFFER         (DCM_M_EVTDISTR_ID_009)
#define DCM_M_EVTID_DSL_RESETTODEFSES       (DCM_M_EVTDISTR_ID_010)
#define DCM_M_EVTID_SID04_ALLCLEARDTC       (DCM_M_EVTDISTR_ID_011)
#define DCM_M_EVTID_SID04_CLEARCHK          (DCM_M_EVTDISTR_ID_012)
#define DCM_M_EVTID_SID09_GET_INFOTYPE      (DCM_M_EVTDISTR_ID_013)
#define DCM_M_EVTID_SID10_SETPROG           (DCM_M_EVTDISTR_ID_014)
#define DCM_M_EVTID_SID10_CHKSESCTRL        (DCM_M_EVTDISTR_ID_015)
#define DCM_M_EVTID_SID11_GETPRERESET       (DCM_M_EVTDISTR_ID_016)
#define DCM_M_EVTID_SID14_CLEARDTC          (DCM_M_EVTDISTR_ID_017)
#define DCM_M_EVTID_SID14_CLEARCHK          (DCM_M_EVTDISTR_ID_018)
#define DCM_M_EVTID_SID19_SUB01_GETNOD      (DCM_M_EVTDISTR_ID_019)
#define DCM_M_EVTID_SID19_SUB02_GETSIZE     (DCM_M_EVTDISTR_ID_020)
#define DCM_M_EVTID_SID19_SUB02_GETDTC      (DCM_M_EVTDISTR_ID_021)
#define DCM_M_EVTID_SID19_SUB03_GETRECORD   (DCM_M_EVTDISTR_ID_022)
#define DCM_M_EVTID_SID19_SUB04_DISREC      (DCM_M_EVTDISTR_ID_023)
#define DCM_M_EVTID_SID19_SUB04_GETSTS      (DCM_M_EVTDISTR_ID_024)
#define DCM_M_EVTID_SID19_SUB04_GETSIZE     (DCM_M_EVTDISTR_ID_025)
#define DCM_M_EVTID_SID19_SUB04_RMNASIZE    (DCM_M_EVTDISTR_ID_026)
#define DCM_M_EVTID_SID19_SUB04_GETFFDT     (DCM_M_EVTDISTR_ID_027)
#define DCM_M_EVTID_SID19_SUB05_STDSDATA    (DCM_M_EVTDISTR_ID_028)
#define DCM_M_EVTID_SID19_SUB05_GETSIZE     (DCM_M_EVTDISTR_ID_029)
#define DCM_M_EVTID_SID19_SUB05_GETDSDT     (DCM_M_EVTDISTR_ID_030)
#define DCM_M_EVTID_SID19_SUB06_DISREC      (DCM_M_EVTDISTR_ID_031)
#define DCM_M_EVTID_SID19_SUB06_GETEDR      (DCM_M_EVTDISTR_ID_032)
#define DCM_M_EVTID_SID19_SUB0A_GETSIZE     (DCM_M_EVTDISTR_ID_033)
#define DCM_M_EVTID_SID19_SUB0A_GETDTC      (DCM_M_EVTDISTR_ID_034)
#define DCM_M_EVTID_SID19_SUB17_GETSIZE     (DCM_M_EVTDISTR_ID_035)
#define DCM_M_EVTID_SID19_SUB17_GETDTC      (DCM_M_EVTDISTR_ID_036)
#define DCM_M_EVTID_SID19_SUB18_DISREC      (DCM_M_EVTDISTR_ID_037)
#define DCM_M_EVTID_SID19_SUB18_GETSTS      (DCM_M_EVTDISTR_ID_038)
#define DCM_M_EVTID_SID19_SUB18_GETSIZE     (DCM_M_EVTDISTR_ID_039)
#define DCM_M_EVTID_SID19_SUB18_GETFFDT     (DCM_M_EVTDISTR_ID_040)
#define DCM_M_EVTID_SID19_SUB19_DISREC      (DCM_M_EVTDISTR_ID_041)
#define DCM_M_EVTID_SID19_SUB19_GETEDR      (DCM_M_EVTDISTR_ID_042)
#define DCM_M_EVTID_SID19_SUB1A_GETSIZE     (DCM_M_EVTDISTR_ID_043)
#define DCM_M_EVTID_SID19_SUB1A_GETDTC      (DCM_M_EVTDISTR_ID_044)
#define DCM_M_EVTID_SID19_SUB42_GETSIZE     (DCM_M_EVTDISTR_ID_045)
#define DCM_M_EVTID_SID19_SUB42_GETDTC      (DCM_M_EVTDISTR_ID_046)
#define DCM_M_EVTID_SID19_SUB55_GETDTC      (DCM_M_EVTDISTR_ID_047)
#define DCM_M_EVTID_SID19_SUB56_GETSIZE     (DCM_M_EVTDISTR_ID_048)
#define DCM_M_EVTID_SID19_SUB56_GETDTC      (DCM_M_EVTDISTR_ID_049)
#define DCM_M_EVTID_SID22_DIDAVAILABLE      (DCM_M_EVTDISTR_ID_050)
#define DCM_M_EVTID_SID22_RANGE_DATA_LEN    (DCM_M_EVTDISTR_ID_051)
#define DCM_M_EVTID_SID22_CHKSUP_CYCLE      (DCM_M_EVTDISTR_ID_052)
#define DCM_M_EVTID_SID22_READ_DID_DATA     (DCM_M_EVTDISTR_ID_053)
#define DCM_M_EVTID_SID22_READ_CYCLE        (DCM_M_EVTDISTR_ID_054)
#define DCM_M_EVTID_SID22_UPDATEPAGE        (DCM_M_EVTDISTR_ID_055)
#define DCM_M_EVTID_SID22_UPDATERCRRP       (DCM_M_EVTDISTR_ID_056)
#define DCM_M_EVTID_SID23_READMEM           (DCM_M_EVTDISTR_ID_057)
#define DCM_M_EVTID_SID23_UPDATEPAGE        (DCM_M_EVTDISTR_ID_058)
#define DCM_M_EVTID_SID27_GET_SEED          (DCM_M_EVTDISTR_ID_059)
#define DCM_M_EVTID_SID27_COMPARE_KEY       (DCM_M_EVTDISTR_ID_060)
#define DCM_M_EVTID_SID27_READCONF          (DCM_M_EVTDISTR_ID_061)
#define DCM_M_EVTID_SID28_COMPCOMCTRL       (DCM_M_EVTDISTR_ID_062)
#define DCM_M_EVTID_SID29_VRFYCERTUNIDIR    (DCM_M_EVTDISTR_ID_063)
#define DCM_M_EVTID_SID29_VRFYCERTBIDIR     (DCM_M_EVTDISTR_ID_064)
#define DCM_M_EVTID_SID29_VRFYPOWN          (DCM_M_EVTDISTR_ID_065)
#define DCM_M_EVTID_SID2A_DIDAVAILABLE      (DCM_M_EVTDISTR_ID_066)
#define DCM_M_EVTID_SID2A_RANGE_DATA_LEN    (DCM_M_EVTDISTR_ID_067)
#define DCM_M_EVTID_SID2C_DIDAVAILABLE      (DCM_M_EVTDISTR_ID_068)
#define DCM_M_EVTID_SID2C_CHKPOSSIZE        (DCM_M_EVTDISTR_ID_069)
#define DCM_M_EVTID_SID2E_DIDAVAILABLE      (DCM_M_EVTDISTR_ID_070)
#define DCM_M_EVTID_SID2E_RANGE_DATA_LEN    (DCM_M_EVTDISTR_ID_071)
#define DCM_M_EVTID_SID2E_WRITE_DID_DATA    (DCM_M_EVTDISTR_ID_072)
#define DCM_M_EVTID_SID2F_IO_CONTROL        (DCM_M_EVTDISTR_ID_073)
#define DCM_M_EVTID_SID2F_READ_DATA         (DCM_M_EVTDISTR_ID_074)
#define DCM_M_EVTID_SID31_EXECUTE           (DCM_M_EVTDISTR_ID_075)
#define DCM_M_EVTID_SID31_UPDATEPAGE        (DCM_M_EVTDISTR_ID_076)
#define DCM_M_EVTID_SID31_UPDATERCRRP       (DCM_M_EVTDISTR_ID_077)
#define DCM_M_EVTID_SID34_CHKDFID           (DCM_M_EVTDISTR_ID_078)
#define DCM_M_EVTID_SID34_PROCREQDL         (DCM_M_EVTDISTR_ID_079)
#define DCM_M_EVTID_SID35_CHKDFID           (DCM_M_EVTDISTR_ID_080)
#define DCM_M_EVTID_SID35_PROCREQUL         (DCM_M_EVTDISTR_ID_081)
#define DCM_M_EVTID_SID36_CHKMSGLEN         (DCM_M_EVTDISTR_ID_082)
#define DCM_M_EVTID_SID36_CHKREQSEQUENCE    (DCM_M_EVTDISTR_ID_083)
#define DCM_M_EVTID_SID36_CHKREQSEQUENCEUL  (DCM_M_EVTDISTR_ID_084)
#define DCM_M_EVTID_SID36_CHKTFRDATSUSPEND  (DCM_M_EVTDISTR_ID_085)
#define DCM_M_EVTID_SID36_CHKTFRDATSUSPENDUL (DCM_M_EVTDISTR_ID_086)
#define DCM_M_EVTID_SID36_PROCTFRDATAWRITE  (DCM_M_EVTDISTR_ID_087)
#define DCM_M_EVTID_SID36_PROCTFRDATAREAD   (DCM_M_EVTDISTR_ID_088)
#define DCM_M_EVTID_SID37_CHKPROGPROCFIN    (DCM_M_EVTDISTR_ID_089)
#define DCM_M_EVTID_SID37_PROCREQTFREXIT    (DCM_M_EVTDISTR_ID_090)
#define DCM_M_EVTID_SID3D_WRITEMEM          (DCM_M_EVTDISTR_ID_091)
#define DCM_M_EVTID_SID85_SUB01_ENA_DTC     (DCM_M_EVTDISTR_ID_092)
#define DCM_M_EVTID_SID85_SUB02_DIS_DTC     (DCM_M_EVTDISTR_ID_093)
#define DCM_M_EVTID_SID86_SERVTORESPTO      (DCM_M_EVTDISTR_ID_094)
#define DCM_M_EVTID_SID86_RESPQUEOVER       (DCM_M_EVTDISTR_ID_095)
#define DCM_M_EVTID_SID86_READCOMP          (DCM_M_EVTDISTR_ID_096)
#define DCM_M_EVTID_SIDA4_CLEARDTC          (DCM_M_EVTDISTR_ID_097)
#define DCM_M_EVTID_SIDA4_CLEARCHK          (DCM_M_EVTDISTR_ID_098)
#define DCM_M_EVTID_SIDA4_CLEAROBS          (DCM_M_EVTDISTR_ID_099)
#define DCM_M_EVTID_SIDBA_GETBEHAVIORMEMORY (DCM_M_EVTDISTR_ID_100)
#define DCM_M_EVTID_DSL_TXIFRETRY           (DCM_M_EVTDISTR_ID_101)
#define DCM_M_EVTID_STORAGEMNG_READALL      (DCM_M_EVTDISTR_ID_102)
#define DCM_M_EVTID_STORAGEMNG_READBLOCK    (DCM_M_EVTDISTR_ID_103)
#define DCM_M_EVTID_STORAGEMNG_WRITEGETSTS  (DCM_M_EVTDISTR_ID_104)
#define DCM_M_EVTID_STORAGEMNG_WRITEDEQ     (DCM_M_EVTDISTR_ID_105)
#define DCM_M_EVTID_STORAGEMNG_WRITERETRY   (DCM_M_EVTDISTR_ID_106)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef P2FUNC( void, DCM_CODE, Dcm_M_EvtDistr_FuncType )( const uint8 u1EventId );

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_M_EvtDistr_IdToIndex[ DCM_M_EVTDISTR_DEFINED_ALL_ID_NUM ];
extern CONST( AB_83_ConstV Dcm_M_EvtDistr_FuncType, DCM_CONFIG_DATA ) Dcm_M_EvtDistr_NoticeTable[ DCM_M_EVTDISTR_ID_NUM ];
extern CONST( AB_83_ConstV Dcm_M_EvtDistr_FuncType, DCM_CONFIG_DATA ) Dcm_M_EvtDistr_NoticeTable_Ex[ DCM_M_EVTDISTR_ID_EX_TBL ];
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_M_EvtDistr_u1EventIdNum;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_M_EvtDistr_u1EventIdExNum;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_MAIN_EVTDISTR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-02-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
