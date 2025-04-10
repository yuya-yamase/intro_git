/* MemIf_Types.h v1-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMIF/TYPES/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MEMIF_TYPES_H
#define MEMIF_TYPES_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define MEMIF_JOB_OK                ( ( MemIf_JobResultType )0x00U )
#define MEMIF_JOB_FAILED            ( ( MemIf_JobResultType )0x01U )
#define MEMIF_JOB_PENDING           ( ( MemIf_JobResultType )0x02U )
#define MEMIF_JOB_CANCELED          ( ( MemIf_JobResultType )0x03U )
#define MEMIF_BLOCK_INCONSISTENT    ( ( MemIf_JobResultType )0x04U )
#define MEMIF_BLOCK_INVALID         ( ( MemIf_JobResultType )0x05U )
#define MEMIF_JOB_FATALFAILED       ( ( MemIf_JobResultType )0x80U )

#define MEMIF_UNINIT                ( ( MemIf_StatusType )0x00U )
#define MEMIF_IDLE                  ( ( MemIf_StatusType )0x01U )
#define MEMIF_BUSY                  ( ( MemIf_StatusType )0x02U )
#define MEMIF_BUSY_INTERNAL         ( ( MemIf_StatusType )0x03U )

#define MEMIF_MODE_SLOW             ( ( MemIf_ModeType )0x00U )
#define MEMIF_MODE_FAST             ( ( MemIf_ModeType )0x01U )

#define MEMIF_EXT_READ_JOB          ( ( uint8 )0x00U )
#define MEMIF_EXT_WRITE_JOB         ( ( uint8 )0x01U )

#define MEMIF_EXT_LEVEL_01          ( ( uint8 )0x00U )
#define MEMIF_EXT_LEVEL_02          ( ( uint8 )0x01U )

#define MEMIF_E_EXT_ALLPASSED           ( ( MemIf_ExtProductionErrorType )0x00U )
#define MEMIF_E_EXT_REQ_FAILED          ( ( MemIf_ExtProductionErrorType )0x01U )
#define MEMIF_E_EXT_WRONG_BLOCK_ID      ( ( MemIf_ExtProductionErrorType )0x02U )
#define MEMIF_E_EXT_VERIFY_FAILED       ( ( MemIf_ExtProductionErrorType )0x04U )
#define MEMIF_E_EXT_LOSS_OF_REDUNDANCY  ( ( MemIf_ExtProductionErrorType )0x08U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8 MemIf_JobResultType;
typedef uint8 MemIf_StatusType;
typedef uint8 MemIf_ModeType;
typedef uint8 MemIf_ExtProductionErrorType;

#endif /* MEMIF_TYPES_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
