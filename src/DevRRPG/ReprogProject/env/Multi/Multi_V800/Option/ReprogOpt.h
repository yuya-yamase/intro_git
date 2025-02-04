/* ReprogOpt_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | ReprogOpt/HEADER                                            */
/******************************************************************************/
#ifndef REPROGOPT_H
#define REPROGOPT_H


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define REPROGOPT_SUBMICON_TYPE_NOUSE   ((uint8)1U)
#define REPROGOPT_SUBMICON_TYPE_MAIN    ((uint8)2U)
#define REPROGOPT_SUBMICON_TYPE_SUB     ((uint8)3U)

#define REPROGOPT_DOUBLEMAP_OFF             (0U)
#define REPROGOPT_DOUBLEMAP_REWRITE_INVALID (1U) /* Rewrite invalid side */
#define REPROGOPT_DOUBLEMAP_REWRITE_VALID   (2U) /* Rewrite valid side */

#if (REPROG_CFG_DOUBLE_MAP_USE == STD_ON)
  #if (REPROG_CFG_DOUBLE_MAP_REWRITE_VALID == STD_ON)
  #define REPROGOPT_DOUBLEMAP_TYPE          (REPROGOPT_DOUBLEMAP_REWRITE_VALID)
  #else
  #define REPROGOPT_DOUBLEMAP_TYPE          (REPROGOPT_DOUBLEMAP_REWRITE_INVALID)
  #endif
#else
  #define REPROGOPT_DOUBLEMAP_TYPE          (REPROGOPT_DOUBLEMAP_OFF)
#endif


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define REPROGOPT_START_SEC_CST
#include <ReprogOpt_MemMap.h>

extern CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_SubMiconConfig;
extern CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_CanDisableConfig;
extern CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_SmallRamConfig;
extern CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_DoubleMapConfig;
extern CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_ParallelConfig;
extern CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_DecompressConfig;

#define REPROGOPT_STOP_SEC_CST
#include <ReprogOpt_MemMap.h>


#endif /* REPROGOPT_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/07/05 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/
