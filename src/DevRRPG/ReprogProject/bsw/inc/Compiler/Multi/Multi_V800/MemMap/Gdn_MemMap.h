/* Gdn_MemMap_h_00_0002 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | ソースコードのセクション配置                                 */
/* Notes       | 本セクション配置のヘッダファイルは2重インクルード可能        */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/30   DN 毛    テンプレート新規作成                      */
/*  00_0001   2017/10/17   AUBASS   リプログ対応                              */
/*  00_0002   2018/12/11   AUBASS   Update                                    */
/******************************************************************************/
/*#ifndef GDN_MEMMAP_H*/
/*#define GDN_MEMMAP_H*/

#ifdef GDN_START_SEC_CODE
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section text = ".P_ROM_GDN"
 #else
 #pragma ghs section text = ".P_RAM_GDN"
 #endif
#undef GDN_START_SEC_CODE
#endif

#ifdef GDN_STOP_SEC_CODE
#pragma ghs section text = default
#undef GDN_STOP_SEC_CODE
#endif

#ifdef GDN_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_2ND"
#undef GDN_START_SEC_VAR
#endif

#ifdef GDN_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef GDN_STOP_SEC_VAR
#endif

#ifdef GDN_START_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs startdata
 #pragma ghs section rodata = ".C_ROM_GDN"
 #else
 #pragma ghs startsda
 #pragma ghs section rosdata = ".C_RAM_GDN"
 #endif
#undef GDN_START_SEC_CST
#endif

#ifdef GDN_STOP_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section rodata = default
 #pragma ghs enddata
 #else
 #pragma ghs section rosdata = default
 #pragma ghs endsda
 #endif
#undef GDN_STOP_SEC_CST
#endif

/*#endif*/ /* GDN_MEMMAP_H */
/**** End of File *************************************************************/
