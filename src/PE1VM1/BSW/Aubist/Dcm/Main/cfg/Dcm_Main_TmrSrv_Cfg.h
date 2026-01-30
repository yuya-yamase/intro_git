/* Dcm_Main_TmrSrv_Cfg_h(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Main_TmrSrv_Cfg/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_MAIN_TMRSRV_CFG_H
#define DCM_MAIN_TMRSRV_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_M_TMRSRV_INVALID_VAL        ((uint8)255U)

/* Timer ID */
#define DCM_M_TMRSRV_ID_000             ((uint8)0U)
#define DCM_M_TMRSRV_ID_001             ((uint8)1U)
#define DCM_M_TMRSRV_ID_002             ((uint8)2U)
#define DCM_M_TMRSRV_ID_003             ((uint8)3U)
#define DCM_M_TMRSRV_ID_004             ((uint8)4U)
#define DCM_M_TMRSRV_ID_005             ((uint8)5U)
#define DCM_M_TMRSRV_ID_006             ((uint8)6U)
#define DCM_M_TMRSRV_ID_007             ((uint8)7U)
#define DCM_M_TMRSRV_ID_008             ((uint8)8U)
#define DCM_M_TMRSRV_ID_009             ((uint8)9U)
#define DCM_M_TMRSRV_ID_010             ((uint8)10U)
#define DCM_M_TMRSRV_ID_011             ((uint8)11U)
#define DCM_M_TMRSRV_ID_012             ((uint8)12U)
#define DCM_M_TMRSRV_ID_013             ((uint8)13U)
#define DCM_M_TMRSRV_ID_014             ((uint8)14U)
#define DCM_M_TMRSRV_ID_015             ((uint8)15U)
#define DCM_M_TMRSRV_ID_016             ((uint8)16U)
#define DCM_M_TMRSRV_ID_017             ((uint8)17U)
#define DCM_M_TMRSRV_ID_018             ((uint8)18U)
#define DCM_M_TMRSRV_ID_019             ((uint8)19U)
#define DCM_M_TMRSRV_ID_020             ((uint8)20U)
#define DCM_M_TMRSRV_ID_021             ((uint8)21U)
#define DCM_M_TMRSRV_ID_022             ((uint8)22U)
#define DCM_M_TMRSRV_ID_023             ((uint8)23U)
#define DCM_M_TMRSRV_ID_024             ((uint8)24U)
#define DCM_M_TMRSRV_ID_025             ((uint8)25U)
#define DCM_M_TMRSRV_ID_026             ((uint8)26U)
#define DCM_M_TMRSRV_ID_027             ((uint8)27U)
#define DCM_M_TMRSRV_ID_028             ((uint8)28U)
#define DCM_M_TMRSRV_ID_029             ((uint8)29U)
#define DCM_M_TMRSRV_ID_030             ((uint8)30U)
#define DCM_M_TMRSRV_ID_031             ((uint8)31U)
#define DCM_M_TMRSRV_ID_032             ((uint8)32U)
#define DCM_M_TMRSRV_ID_033             ((uint8)33U)
#define DCM_M_TMRSRV_ID_034             ((uint8)34U)
#define DCM_M_TMRSRV_ID_035             ((uint8)35U)
#define DCM_M_TMRSRV_ID_036             ((uint8)36U)
#define DCM_M_TMRSRV_ID_037             ((uint8)37U)
#define DCM_M_TMRSRV_ID_038             ((uint8)38U)
#define DCM_M_TMRSRV_ID_039             ((uint8)39U)
#define DCM_M_TMRSRV_ID_040             ((uint8)40U)
#define DCM_M_TMRSRV_ID_041             ((uint8)41U)
#define DCM_M_TMRSRV_ID_042             ((uint8)42U)
#define DCM_M_TMRSRV_ID_043             ((uint8)43U)
#define DCM_M_TMRSRV_ID_044             ((uint8)44U)
#define DCM_M_TMRSRV_ID_045             ((uint8)45U)
#define DCM_M_TMRSRV_ID_046             ((uint8)46U)
#define DCM_M_TMRSRV_ID_047             ((uint8)47U)
#define DCM_M_TMRSRV_ID_048             ((uint8)48U)
#define DCM_M_TMRSRV_ID_049             ((uint8)49U)
#define DCM_M_TMRSRV_ID_050             ((uint8)50U)
#define DCM_M_TMRSRV_ID_051             ((uint8)51U)
#define DCM_M_TMRSRV_ID_052             ((uint8)52U)
#define DCM_M_TMRSRV_ID_053             ((uint8)53U)
#define DCM_M_TMRSRV_ID_054             ((uint8)54U)
#define DCM_M_TMRSRV_ID_055             ((uint8)55U)
#define DCM_M_TMRSRV_ID_056             ((uint8)56U)
#define DCM_M_TMRSRV_ID_057             ((uint8)57U)
#define DCM_M_TMRSRV_ID_058             ((uint8)58U)
#define DCM_M_TMRSRV_ID_059             ((uint8)59U)
#define DCM_M_TMRSRV_ID_060             ((uint8)60U)
#define DCM_M_TMRSRV_ID_061             ((uint8)61U)
#define DCM_M_TMRSRV_ID_062             ((uint8)62U)
#define DCM_M_TMRSRV_ID_063             ((uint8)63U)
#define DCM_M_TMRSRV_ID_064             ((uint8)64U)
#define DCM_M_TMRSRV_ID_065             ((uint8)65U)
#define DCM_M_TMRSRV_ID_066             ((uint8)66U)
#define DCM_M_TMRSRV_ID_067             ((uint8)67U)
#define DCM_M_TMRSRV_ID_068             ((uint8)68U)
#define DCM_M_TMRSRV_ID_069             ((uint8)69U)
#define DCM_M_TMRSRV_ID_070             ((uint8)70U)
#define DCM_M_TMRSRV_ID_071             ((uint8)71U)
#define DCM_M_TMRSRV_ID_072             ((uint8)72U)
#define DCM_M_TMRSRV_ID_073             ((uint8)73U)
#define DCM_M_TMRSRV_ID_074             ((uint8)74U)
#define DCM_M_TMRSRV_ID_075             ((uint8)75U)
#define DCM_M_TMRSRV_ID_076             ((uint8)76U)
#define DCM_M_TMRSRV_ID_077             ((uint8)77U)
#define DCM_M_TMRSRV_ID_078             ((uint8)78U)
#define DCM_M_TMRSRV_ID_079             ((uint8)79U)
#define DCM_M_TMRSRV_ID_080             ((uint8)80U)
#define DCM_M_TMRSRV_ID_081             ((uint8)81U)
#define DCM_M_TMRSRV_ID_082             ((uint8)82U)
#define DCM_M_TMRSRV_ID_083             ((uint8)83U)
#define DCM_M_TMRSRV_ID_084             ((uint8)84U)
#define DCM_M_TMRSRV_ID_085             ((uint8)85U)
#define DCM_M_TMRSRV_ID_086             ((uint8)86U)
#define DCM_M_TMRSRV_ID_087             ((uint8)87U)
#define DCM_M_TMRSRV_ID_088             ((uint8)88U)
#define DCM_M_TMRSRV_ID_089             ((uint8)89U)
#define DCM_M_TMRSRV_ID_090             ((uint8)90U)
#define DCM_M_TMRSRV_ID_091             ((uint8)91U)
#define DCM_M_TMRSRV_ID_092             ((uint8)92U)
#define DCM_M_TMRSRV_ID_093             ((uint8)93U)
#define DCM_M_TMRSRV_ID_094             ((uint8)94U)
#define DCM_M_TMRSRV_ID_095             ((uint8)95U)
#define DCM_M_TMRSRV_ID_096             ((uint8)96U)
#define DCM_M_TMRSRV_ID_097             ((uint8)97U)
#define DCM_M_TMRSRV_ID_098             ((uint8)98U)
#define DCM_M_TMRSRV_ID_099             ((uint8)99U)
#define DCM_M_TMRSRV_ID_100             ((uint8)100U)
#define DCM_M_TMRSRV_ID_101             ((uint8)101U)
#define DCM_M_TMRSRV_ID_102             ((uint8)102U)
#define DCM_M_TMRSRV_ID_103             ((uint8)103U)
#define DCM_M_TMRSRV_ID_104             ((uint8)104U)
#define DCM_M_TMRSRV_ID_105             ((uint8)105U)
#define DCM_M_TMRSRV_DEFINED_LAST_ID    ((uint8)105U)
#define DCM_M_TMRSRV_DEFINED_ALL_ID_NUM ((uint8)(DCM_M_TMRSRV_DEFINED_LAST_ID + (uint8)1U))
#define DCM_M_TMRSRV_ID_NUM             ((uint8)9U)     /* Timer ID number */

#define DCM_M_TMRID_RXFSTIMER               (DCM_M_TMRSRV_ID_000)
#define DCM_M_TMRID_TXFSTIMER               (DCM_M_TMRSRV_ID_001)
#define DCM_M_TMRID_P4TIMER                 (DCM_M_TMRSRV_ID_002)
#define DCM_M_TMRID_PAGEDBUFFERTIMER        (DCM_M_TMRSRV_ID_003)
#define DCM_M_TMRID_TXIFFSTIMER             (DCM_M_TMRSRV_ID_004)
#define DCM_M_TMRID_ROERETRY_TIMER          (DCM_M_TMRSRV_ID_005)
#define DCM_M_TMRID_P2MINTIMER              (DCM_M_TMRSRV_ID_006)
#define DCM_M_TMRID_P2TIMER                 (DCM_M_TMRSRV_ID_007)
#define DCM_M_TMRID_S3TIMER                 (DCM_M_TMRSRV_ID_008)
#define DCM_M_TMRID_SID27_DTMR_SECLV1       (DCM_M_TMRSRV_ID_009)
#define DCM_M_TMRID_SID27_DTMR_SECLV2       (DCM_M_TMRSRV_ID_010)
#define DCM_M_TMRID_SID27_DTMR_SECLV3       (DCM_M_TMRSRV_ID_011)
#define DCM_M_TMRID_SID27_DTMR_SECLV4       (DCM_M_TMRSRV_ID_012)
#define DCM_M_TMRID_SID27_DTMR_SECLV5       (DCM_M_TMRSRV_ID_013)
#define DCM_M_TMRID_SID27_DTMR_SECLV6       (DCM_M_TMRSRV_ID_014)
#define DCM_M_TMRID_SID27_DTMR_SECLV7       (DCM_M_TMRSRV_ID_015)
#define DCM_M_TMRID_SID27_DTMR_SECLV8       (DCM_M_TMRSRV_ID_016)
#define DCM_M_TMRID_SID27_DTMR_SECLV9       (DCM_M_TMRSRV_ID_017)
#define DCM_M_TMRID_SID27_DTMR_SECLV10      (DCM_M_TMRSRV_ID_018)
#define DCM_M_TMRID_SID27_DTMR_SECLV11      (DCM_M_TMRSRV_ID_019)
#define DCM_M_TMRID_SID27_DTMR_SECLV12      (DCM_M_TMRSRV_ID_020)
#define DCM_M_TMRID_SID27_DTMR_SECLV13      (DCM_M_TMRSRV_ID_021)
#define DCM_M_TMRID_SID27_DTMR_SECLV14      (DCM_M_TMRSRV_ID_022)
#define DCM_M_TMRID_SID27_DTMR_SECLV15      (DCM_M_TMRSRV_ID_023)
#define DCM_M_TMRID_SID27_DTMR_SECLV16      (DCM_M_TMRSRV_ID_024)
#define DCM_M_TMRID_SID27_DTMR_SECLV17      (DCM_M_TMRSRV_ID_025)
#define DCM_M_TMRID_SID27_DTMR_SECLV18      (DCM_M_TMRSRV_ID_026)
#define DCM_M_TMRID_SID27_DTMR_SECLV19      (DCM_M_TMRSRV_ID_027)
#define DCM_M_TMRID_SID27_DTMR_SECLV20      (DCM_M_TMRSRV_ID_028)
#define DCM_M_TMRID_SID27_DTMR_SECLV21      (DCM_M_TMRSRV_ID_029)
#define DCM_M_TMRID_SID27_DTMR_SECLV22      (DCM_M_TMRSRV_ID_030)
#define DCM_M_TMRID_SID27_DTMR_SECLV23      (DCM_M_TMRSRV_ID_031)
#define DCM_M_TMRID_SID27_DTMR_SECLV24      (DCM_M_TMRSRV_ID_032)
#define DCM_M_TMRID_SID27_DTMR_SECLV25      (DCM_M_TMRSRV_ID_033)
#define DCM_M_TMRID_SID27_DTMR_SECLV26      (DCM_M_TMRSRV_ID_034)
#define DCM_M_TMRID_SID27_DTMR_SECLV27      (DCM_M_TMRSRV_ID_035)
#define DCM_M_TMRID_SID27_DTMR_SECLV28      (DCM_M_TMRSRV_ID_036)
#define DCM_M_TMRID_SID27_DTMR_SECLV29      (DCM_M_TMRSRV_ID_037)
#define DCM_M_TMRID_SID27_DTMR_SECLV30      (DCM_M_TMRSRV_ID_038)
#define DCM_M_TMRID_SID27_DTMR_SECLV31      (DCM_M_TMRSRV_ID_039)
#define DCM_M_TMRID_SID27_DTMR_SECLV32      (DCM_M_TMRSRV_ID_040)
#define DCM_M_TMRID_SID27_DTMR_SECLV33      (DCM_M_TMRSRV_ID_041)
#define DCM_M_TMRID_SID27_DTMR_SECLV34      (DCM_M_TMRSRV_ID_042)
#define DCM_M_TMRID_SID27_DTMR_SECLV35      (DCM_M_TMRSRV_ID_043)
#define DCM_M_TMRID_SID27_DTMR_SECLV36      (DCM_M_TMRSRV_ID_044)
#define DCM_M_TMRID_SID27_DTMR_SECLV37      (DCM_M_TMRSRV_ID_045)
#define DCM_M_TMRID_SID27_DTMR_SECLV38      (DCM_M_TMRSRV_ID_046)
#define DCM_M_TMRID_SID27_DTMR_SECLV39      (DCM_M_TMRSRV_ID_047)
#define DCM_M_TMRID_SID27_DTMR_SECLV40      (DCM_M_TMRSRV_ID_048)
#define DCM_M_TMRID_SID27_DTMR_SECLV41      (DCM_M_TMRSRV_ID_049)
#define DCM_M_TMRID_SID27_DTMR_SECLV42      (DCM_M_TMRSRV_ID_050)
#define DCM_M_TMRID_SID27_DTMR_SECLV43      (DCM_M_TMRSRV_ID_051)
#define DCM_M_TMRID_SID27_DTMR_SECLV44      (DCM_M_TMRSRV_ID_052)
#define DCM_M_TMRID_SID27_DTMR_SECLV45      (DCM_M_TMRSRV_ID_053)
#define DCM_M_TMRID_SID27_DTMR_SECLV46      (DCM_M_TMRSRV_ID_054)
#define DCM_M_TMRID_SID27_DTMR_SECLV47      (DCM_M_TMRSRV_ID_055)
#define DCM_M_TMRID_SID27_DTMR_SECLV48      (DCM_M_TMRSRV_ID_056)
#define DCM_M_TMRID_SID27_DTMR_SECLV49      (DCM_M_TMRSRV_ID_057)
#define DCM_M_TMRID_SID27_DTMR_SECLV50      (DCM_M_TMRSRV_ID_058)
#define DCM_M_TMRID_SID27_DTMR_SECLV51      (DCM_M_TMRSRV_ID_059)
#define DCM_M_TMRID_SID27_DTMR_SECLV52      (DCM_M_TMRSRV_ID_060)
#define DCM_M_TMRID_SID27_DTMR_SECLV53      (DCM_M_TMRSRV_ID_061)
#define DCM_M_TMRID_SID27_DTMR_SECLV54      (DCM_M_TMRSRV_ID_062)
#define DCM_M_TMRID_SID27_DTMR_SECLV55      (DCM_M_TMRSRV_ID_063)
#define DCM_M_TMRID_SID27_DTMR_SECLV56      (DCM_M_TMRSRV_ID_064)
#define DCM_M_TMRID_SID27_DTMR_SECLV57      (DCM_M_TMRSRV_ID_065)
#define DCM_M_TMRID_SID27_DTMR_SECLV58      (DCM_M_TMRSRV_ID_066)
#define DCM_M_TMRID_SID27_DTMR_SECLV59      (DCM_M_TMRSRV_ID_067)
#define DCM_M_TMRID_SID27_DTMR_SECLV60      (DCM_M_TMRSRV_ID_068)
#define DCM_M_TMRID_SID27_DTMR_SECLV61      (DCM_M_TMRSRV_ID_069)
#define DCM_M_TMRID_SID27_DTMR_SECLV62      (DCM_M_TMRSRV_ID_070)
#define DCM_M_TMRID_SID27_DTMR_SECLV63      (DCM_M_TMRSRV_ID_071)
#define DCM_M_TMRID_STORAGEMNG_READALLFS    (DCM_M_TMRSRV_ID_072)
#define DCM_M_TMRID_STORAGEMNG_WRITEFS      (DCM_M_TMRSRV_ID_073)
#define DCM_M_TMRID_SID86_INTERMESSAGE      (DCM_M_TMRSRV_ID_074)
#define DCM_M_TMRID_AUTH_CLIENT0            (DCM_M_TMRSRV_ID_075)
#define DCM_M_TMRID_AUTH_CLIENT1            (DCM_M_TMRSRV_ID_076)
#define DCM_M_TMRID_AUTH_CLIENT2            (DCM_M_TMRSRV_ID_077)
#define DCM_M_TMRID_AUTH_CLIENT3            (DCM_M_TMRSRV_ID_078)
#define DCM_M_TMRID_AUTH_CLIENT4            (DCM_M_TMRSRV_ID_079)
#define DCM_M_TMRID_AUTH_CLIENT5            (DCM_M_TMRSRV_ID_080)
#define DCM_M_TMRID_AUTH_CLIENT6            (DCM_M_TMRSRV_ID_081)
#define DCM_M_TMRID_AUTH_CLIENT7            (DCM_M_TMRSRV_ID_082)
#define DCM_M_TMRID_AUTH_CLIENT8            (DCM_M_TMRSRV_ID_083)
#define DCM_M_TMRID_AUTH_CLIENT9            (DCM_M_TMRSRV_ID_084)
#define DCM_M_TMRID_AUTH_CLIENT10           (DCM_M_TMRSRV_ID_085)
#define DCM_M_TMRID_AUTH_CLIENT11           (DCM_M_TMRSRV_ID_086)
#define DCM_M_TMRID_AUTH_CLIENT12           (DCM_M_TMRSRV_ID_087)
#define DCM_M_TMRID_AUTH_CLIENT13           (DCM_M_TMRSRV_ID_088)
#define DCM_M_TMRID_AUTH_CLIENT14           (DCM_M_TMRSRV_ID_089)
#define DCM_M_TMRID_AUTH_CLIENT15           (DCM_M_TMRSRV_ID_090)
#define DCM_M_TMRID_AUTH_CLIENT16           (DCM_M_TMRSRV_ID_091)
#define DCM_M_TMRID_AUTH_CLIENT17           (DCM_M_TMRSRV_ID_092)
#define DCM_M_TMRID_AUTH_CLIENT18           (DCM_M_TMRSRV_ID_093)
#define DCM_M_TMRID_AUTH_CLIENT19           (DCM_M_TMRSRV_ID_094)
#define DCM_M_TMRID_AUTH_CLIENT20           (DCM_M_TMRSRV_ID_095)
#define DCM_M_TMRID_AUTH_CLIENT21           (DCM_M_TMRSRV_ID_096)
#define DCM_M_TMRID_AUTH_CLIENT22           (DCM_M_TMRSRV_ID_097)
#define DCM_M_TMRID_AUTH_CLIENT23           (DCM_M_TMRSRV_ID_098)
#define DCM_M_TMRID_AUTH_CLIENT24           (DCM_M_TMRSRV_ID_099)
#define DCM_M_TMRID_AUTH_CLIENT25           (DCM_M_TMRSRV_ID_100)
#define DCM_M_TMRID_AUTH_CLIENT26           (DCM_M_TMRSRV_ID_101)
#define DCM_M_TMRID_AUTH_CLIENT27           (DCM_M_TMRSRV_ID_102)
#define DCM_M_TMRID_AUTH_CLIENT28           (DCM_M_TMRSRV_ID_103)
#define DCM_M_TMRID_AUTH_CLIENT29           (DCM_M_TMRSRV_ID_104)
#define DCM_M_TMRID_SYNC_OSAP_DATA          (DCM_M_TMRSRV_ID_105)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef P2FUNC( void, DCM_CODE, Dcm_M_TmrSrv_FuncType )( const uint8 u1TimerId );
typedef struct tagDcm_M_TmrSrv_NoticeTableType{
    Dcm_M_TmrSrv_FuncType ptFnc;
    uint8 u1TimerId;
}Dcm_M_TmrSrv_NoticeTableType;

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

extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_M_TmrSrv_IdToIndex[ DCM_M_TMRSRV_DEFINED_ALL_ID_NUM ];
extern CONST( AB_83_ConstV Dcm_M_TmrSrv_NoticeTableType, DCM_CONFIG_DATA ) Dcm_M_TmrSrv_NoticeTable[ DCM_M_TMRSRV_ID_NUM ];
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_M_TmrSrv_u1IdNum;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_MAIN_TMRSRV_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
