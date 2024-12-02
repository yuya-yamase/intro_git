/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_MemmapSdaSelectE_Env.h
 * [Module]			System
 * [Function]		System Enviroment
 * [Notes]			None
 ****************************************************************************/
#ifndef SS_MEMMAPSDASELECTE_ENV_H
#define SS_MEMMAPSDASELECTE_ENV_H

#include <SS_Memmap_Cfg.h>

#if (SS_MEMMAP_ACCESS_SDA == STD_ON)

/* 強制的にSDAに配置する指定 (終了側) */
#pragma ghs endsda

#elif (SS_MEMMAP_ACCESS_SDA == STD_OFF)

/* 強制的に非SDAに配置する指定 (終了側) */
#pragma ghs enddata

#else
#error invalid SS_MEMMAP_ACCESS_SDA
#endif

#endif /* SS_MEMMAPSDASELECTE_ENV_H */
