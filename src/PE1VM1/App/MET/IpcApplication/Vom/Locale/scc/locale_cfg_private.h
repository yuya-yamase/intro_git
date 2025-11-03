/* 2.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Locale                                                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef LOCALE_CFG_H
#define LOCALE_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LOCALE_CFG_H_MAJOR                     (2)
#define LOCALE_CFG_H_MINOR                     (0)
#define LOCALE_CFG_H_PATCH                     (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "nvmc_mgr.h"
#include "rim_ctl.h"
#include "locale.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LOCALE_NUM_IDX              (7U)
#define LOCALE_IDX_LANGUAGE         (0U)
#define LOCALE_IDX_UNIT_DIST        (1U)
#define LOCALE_IDX_UNIT_SPEED       (2U)
#define LOCALE_IDX_UNIT_FUECO       (3U)
#define LOCALE_IDX_UNIT_ELECO       (4U)
#define LOCALE_IDX_UNIT_AMBTMP      (5U)
#define LOCALE_IDX_TIMEFORMAT       (6U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define LOCALE_LNGDB_NUM            (7U)

#define LOCALE_LNGDB_BITPOS         (0x80U)

#define LOCALE_CHKLNGDBPOS          (8U)
#define LOCALE_CHKLNGDBPOSDEF       (6U)

#define VUCLANG_HUDLANG_NUM                        (LANG_NUM_VAL)
#define VUCLANG_HUDLANG_JPN                        (0x00)
#define VUCLANG_HUDLANG_CHN_SMP                    (0x01)
#define VUCLANG_HUDLANG_CHN_TRA                    (0x02)
#define VUCLANG_HUDLANG_KOREAN                     (0x03)
#define VUCLANG_HUDLANG_THAI                       (0x04)
#define VUCLANG_HUDLANG_JPN_ENGLISH                (0x05)
#define VUCLANG_HUDLANG_MALAY                      (0x06)
#define VUCLANG_HUDLANG_INDONESIAN                 (0x07)
#define VUCLANG_HUDLANG_TAIWANESE                  (0x08)
#define VUCLANG_HUDLANG_INDIA_ENG                  (0x09)
#define VUCLANG_HUDLANG_HINDI                      (0x0A)
#define VUCLANG_HUDLANG_VIETNAMESE                 (0x0B)
#define VUCLANG_HUDLANG_FILIPINO                   (0x0C)
#define VUCLANG_HUDLANG_TAMIL                      (0x0D)
#define VUCLANG_HUDLANG_FRENCH                     (0x40)
#define VUCLANG_HUDLANG_GERMAN                     (0x41)
#define VUCLANG_HUDLANG_ITALIAN                    (0x42)
#define VUCLANG_HUDLANG_DUTCH                      (0x43)
#define VUCLANG_HUDLANG_SPANISH                    (0x44)
#define VUCLANG_HUDLANG_SWEDISH                    (0x45)
#define VUCLANG_HUDLANG_DANISH                     (0x46)
#define VUCLANG_HUDLANG_NORWEGIAN                  (0x47)
#define VUCLANG_HUDLANG_PORTUGUESE                 (0x48)
#define VUCLANG_HUDLANG_RUSSIAN                    (0x49)
#define VUCLANG_HUDLANG_GREEK                      (0x4A)
#define VUCLANG_HUDLANG_POLISH                     (0x4B)
#define VUCLANG_HUDLANG_FINNISH                    (0x4C)
#define VUCLANG_HUDLANG_UKRAINIAN                  (0x4D)
#define VUCLANG_HUDLANG_TURKISH                    (0x4E)
#define VUCLANG_HUDLANG_HUNGARIAN                  (0x4F)
#define VUCLANG_HUDLANG_CZECH                      (0x50)
#define VUCLANG_HUDLANG_SLOVAK                     (0x51)
#define VUCLANG_HUDLANG_ROMANIAN                   (0x52)
#define VUCLANG_HUDLANG_EUSKARA                    (0x53)
#define VUCLANG_HUDLANG_BULGARIAN                  (0x54)
#define VUCLANG_HUDLANG_VLAAMS                     (0x55)
#define VUCLANG_HUDLANG_USA_ENG                    (0x80)
#define VUCLANG_HUDLANG_BRI_ENG                    (0x81)
#define VUCLANG_HUDLANG_BRA_PORTUGU                (0x82)
#define VUCLANG_HUDLANG_SA_SPANISH                 (0x83)
#define VUCLANG_HUDLANG_CAN_FRENCH                 (0x84)
#define VUCLANG_HUDLANG_MEX_SPANISH                (0x85)
#define VUCLANG_HUDLANG_AU_ENG                     (0x86)
#define VUCLANG_HUDLANG_ARABIC                     (0xC0)
#define VUCLANG_HUDLANG_MIDEAST_ENG                (0xC1)
#define VUCLANG_HUDLANG_PERSIAN                    (0xC2)
#define VUCLANG_HUDLANG_HEBREW                     (0xC3)
#define VUCLANG_HUDLANG_ISRAEL                     (0xC4)
#define VUCLANG_HUDLANG_SLOVENIAN                  (0x56)
#define VUCLANG_HUDLANG_UNDEF                      (0xFF)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_LocaleComTxInit(void);
void    vd_g_LocaleComTxTask(void);

U1      u1_g_LocaleCfgLangDef(void);
U1      u1_g_LocaleCfgMmLangChk(const U1 u1_a_LANG);
U1      u1_g_LocaleCfgTimeFormatDef(void);
U1      u1_g_LocaleCfgSubSpd(const U1 u1_a_UNIT);
U1      u1_g_LocaleCfgLang(void);
void    vd_g_LocaleCfgLangPut(const U1 u1_a_LANG);
U1      u1_g_LocaleCfgUnit(const U1 u1_a_UNITIDX);
void    vd_g_LocaleCfgUnitPut(const U1 u1_a_UNITIDX, const U1 u1_a_VAL);
void    vd_g_LocaleCfgTfmPut(const U1 u1_a_FRMT);
U1      u1_g_LocaleCfgTfm(void);
U1      u1_g_LocaleCfgUnitdef(const U1 u1_a_UNITIDX);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U1 u1_g_LANG_NUM;

/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* LOCALE_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  locale.c                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
