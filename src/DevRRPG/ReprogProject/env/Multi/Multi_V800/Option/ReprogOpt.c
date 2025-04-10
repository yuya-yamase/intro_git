/* ReprogOpt_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | ReprogOpt/CODE                                              */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <ReprogOpt.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
  #define REPROGOPT_SUBMICON_TYPE   (REPROGOPT_SUBMICON_TYPE_MAIN)
#elif (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)
  #define REPROGOPT_SUBMICON_TYPE   (REPROGOPT_SUBMICON_TYPE_SUB)
#else   /* REPROG_CFG_SUBMICON_NOUSE */
  #define REPROGOPT_SUBMICON_TYPE   (REPROGOPT_SUBMICON_TYPE_NOUSE)
#endif


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define REPROGOPT_START_SEC_CST
#include <ReprogOpt_MemMap.h>

CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_SubMiconConfig = REPROGOPT_SUBMICON_TYPE;
CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_CanDisableConfig = REPROG_CFG_CAN_DISABLE;
CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_SmallRamConfig = REPROG_CFG_SMALL_RAM_USE;
CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_DoubleMapConfig = REPROGOPT_DOUBLEMAP_TYPE;
CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_ParallelConfig = REPROG_CFG_PARALLEL_ENABLE;
CONST(uint8, REPROGOPT_CONFIG_DATA) ReprogOpt_DecompressConfig = REPROG_CFG_DECOMPRESS_ENABLE;

#define REPROGOPT_STOP_SEC_CST
#include <ReprogOpt_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/07/05 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/


