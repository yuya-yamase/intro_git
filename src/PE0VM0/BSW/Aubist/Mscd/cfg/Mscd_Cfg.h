/* Mscd_Cfg.h v1-2-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/CFG/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_CFG_H
#define MSCD_CFG_H

#include <Mscd_Types.h>
#include <NvM_Mscd.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* Speed up switch */
#define MSCD_SPEEDUP_USE             (STD_ON)

/* Suspend switch */
#define MSCD_SUSPEND_USE             (STD_ON)

/* DataFlash direct access switch */
#define MSCD_DFAI_USE                (STD_ON)

/* Error Info switch */
#define MSCD_ERRORINFO_USE           (STD_ON)

/* Free Space switch */
#define MSCD_FREESPACE_USE           (STD_ON)

#if ( MSCD_DFAI_USE == STD_ON )

#define MSCD_DFAI_USER_AREA_SECTOR_NO_START (0xFFFFU)
#define MSCD_DFAI_USER_AREA_SECTOR_NUM      (0xFFFFU)

#endif /* ( MSCD_DFAI_USE == STD_ON ) */

#endif /* MSCD_CFG_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/01/31                                              */
/*  1-2-0          :2019/08/27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
