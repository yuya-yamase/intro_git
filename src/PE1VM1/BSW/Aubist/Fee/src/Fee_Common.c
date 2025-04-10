/* Fee_Common.c v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/COMMON/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Mpu_Dev_Const.h"

/* MHA[データFlash]I/Fヘッダ */
#include "../inc/Fee_Legacy.h"

/* MHA[データFlash]ヘッダ */
#include "../inc/Fee_Lib.h"

/* MHA[データFlash]ライブラリヘッダ */
#include "../inc/Fee_Common.h"


/* D.F.C.ヘッダ */
#include "../inc/Fee_Dfc.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

/* WC 書き込みデータ */
CONST(uint8, FEE_CONST) Fee_FixWCData[ FEE_DFLASH_FORMAT_WC_MAX_SIZE ] =
{
    FEE_WCDAT_PHYSICAL_IMAGE_UPPER,
    FEE_WCDAT_PHYSICAL_IMAGE_LOWER,
    FEE_WCDAT_PHYSICAL_IMAGE_UPPER,
    FEE_WCDAT_PHYSICAL_IMAGE_LOWER,
    FEE_WCDAT_PHYSICAL_IMAGE_UPPER,
    FEE_WCDAT_PHYSICAL_IMAGE_LOWER,
    FEE_WCDAT_PHYSICAL_IMAGE_UPPER,
    FEE_WCDAT_PHYSICAL_IMAGE_LOWER
};
/* DATA-STATUS書き込みデータ */
CONST(uint8, FEE_CONST) Fee_FixDSData[ FEE_DFLASH_FORMAT_DS_MAX_SIZE ] =
{
    FEE_DSDAT_PHYSICAL_IMAGE_UPPER,
    FEE_DSDAT_PHYSICAL_IMAGE_LOWER,
    FEE_DSDAT_PHYSICAL_IMAGE_UPPER,
    FEE_DSDAT_PHYSICAL_IMAGE_LOWER,
    FEE_DSDAT_PHYSICAL_IMAGE_UPPER,
    FEE_DSDAT_PHYSICAL_IMAGE_LOWER,
    FEE_DSDAT_PHYSICAL_IMAGE_UPPER,
    FEE_DSDAT_PHYSICAL_IMAGE_LOWER
};
/* BS初期ステータスデータ */
CONST(uint8, FEE_CONST) Fee_FixBSData[ FEE_DFLASH_FORMAT_BS_MAX_SIZE ] =
{
    FEE_BSDAT_PHYSICAL_IMAGE_UPPER,
    FEE_BSDAT_PHYSICAL_IMAGE_LOWER,
    FEE_BSDAT_PHYSICAL_IMAGE_UPPER,
    FEE_BSDAT_PHYSICAL_IMAGE_LOWER,
    FEE_BSDAT_PHYSICAL_IMAGE_UPPER,
    FEE_BSDAT_PHYSICAL_IMAGE_LOWER,
    FEE_BSDAT_PHYSICAL_IMAGE_UPPER,
    FEE_BSDAT_PHYSICAL_IMAGE_LOWER
};
/* XFlag value */
CONST(uint8, FEE_CONST) Fee_FixXFlagData[ FEE_DFLASH_FORMAT_XFLAG_MAX_SIZE ] =
{
    FEE_XFLAGDAT_PHYSICAL_IMAGE,
    FEE_XFLAGDAT_PHYSICAL_IMAGE,
    FEE_XFLAGDAT_PHYSICAL_IMAGE,
    FEE_XFLAGDAT_PHYSICAL_IMAGE,
    FEE_XFLAGDAT_PHYSICAL_IMAGE,
    FEE_XFLAGDAT_PHYSICAL_IMAGE,
    FEE_XFLAGDAT_PHYSICAL_IMAGE,
    FEE_XFLAGDAT_PHYSICAL_IMAGE
};

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
