/* Fee_Cfg.h                                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | FEE/CFG/HEADER                                             */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef FEE_CFG_H
#define FEE_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <MemIf_Types.h>    /* SWS_Fee_00002 */
#include <NvM_Cbk.h>        /* SWS_Fee_00002 */
#include <Fee_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_RECORDPOSTBL_ENABLE             (STD_OFF)
#define FEE_RECORDPOSTBL_FAILSAFE           (STD_OFF)
#define FEE_INTENT_RBLD_ENABLE              (STD_OFF)

#define FEE_MAIN_FUNCTION_PERIOD            (5U)

#define FEE_VOLMONI_DELAY_TIME              (400U)
#define FEE_VOLMONI_RETRY_NUM               (0U)

#define FEE_MAX_BLANK_CHECK_NUM             (490U)
#define FEE_RCRD_SPC_SRCH_NUM               (20U)
#define FEE_MAX_CALC_CHECKSUM_BYTES         (256U)

#define FEE_DATASET_SELECTION_BITS          (1U)


#define FEE_PHYSICAL_SECTOR_NUM_PER_VIRTUAL (1U)
#define FEE_AREA_NUM                        (4U)
#define FEE_SCTR_NUM_TOTAL                  (8U)

#define FEE_SCTR_NUM_A000                   (2U)
#define FEE_SCTR_NUM_A001                   (2U)
#define FEE_SCTR_NUM_A002                   (2U)
#define FEE_SCTR_NUM_A003                   (2U)

#define FEE_MAX_RCRD_NUM_A000               (64U)
#define FEE_MAX_RCRD_NUM_A001               (64U)
#define FEE_MAX_RCRD_NUM_A002               (64U)
#define FEE_MAX_RCRD_NUM_A003               (64U)

#define FEE_RCRD_SRCH_NUM_A000              (150U)
#define FEE_RCRD_SRCH_NUM_A001              (150U)
#define FEE_RCRD_SRCH_NUM_A002              (150U)
#define FEE_RCRD_SRCH_NUM_A003              (150U)

#define FEE_RCRD_WRITE_RETRY_NUM_A000       (1U)
#define FEE_RCRD_WRITE_RETRY_NUM_A001       (1U)
#define FEE_RCRD_WRITE_RETRY_NUM_A002       (1U)
#define FEE_RCRD_WRITE_RETRY_NUM_A003       (1U)

#define FEE_INTENT_RBLD_BLOCK_ID_A000       (FEE_INTENT_RBLD_BLOCK_ID_NONE)
#define FEE_INTENT_RBLD_BLOCK_ID_A001       (FEE_INTENT_RBLD_BLOCK_ID_NONE)
#define FEE_INTENT_RBLD_BLOCK_ID_A002       (FEE_INTENT_RBLD_BLOCK_ID_NONE)
#define FEE_INTENT_RBLD_BLOCK_ID_A003       (FEE_INTENT_RBLD_BLOCK_ID_NONE)

#define FEE_BLOCK_NUM_A000_LV1              (9U)
#define FEE_BLOCK_NUM_A001_LV1              (2U)
#define FEE_BLOCK_NUM_A002_LV1              (2U)
#define FEE_BLOCK_NUM_A003_LV1              (3U)

#define FEE_BLOCK_NUM_A000_LV2              (0U)
#define FEE_BLOCK_NUM_A001_LV2              (0U)
#define FEE_BLOCK_NUM_A002_LV2              (0U)
#define FEE_BLOCK_NUM_A003_LV2              (0U)

#endif /* FEE_CFG_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

