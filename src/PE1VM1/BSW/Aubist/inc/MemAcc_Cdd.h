/* MemAcc_Cdd.h v2-0-0                                                        */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright DENSO CORPORATION. All rights reserved.                          */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemAcc/HEADER                                               */
/******************************************************************************/
#ifndef MEMACC_CDD_H
#define MEMACC_CDD_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>
#include "../MemAcc/inc/MemAcc_Mpu_Const.h"
#include "MemAcc.h"
#include "Fls.h"
#include "Fls_Cdd.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Lock status (public) */
#define MEMACC_LOCKST_UNLOCK     ((uint8)0x00U)        /* Unlock */
#define MEMACC_LOCKST_LOCK       ((uint8)0x01U)        /* Lock   */

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
FUNC( Fls_Cdd_JobResultType, MEMACC_CODE ) MemAcc_Cdd_Read( Fls_AddressType targetAddress, P2VAR( uint8, AUTOMATIC, TYPEDEF ) destinationDataPtr, Fls_LengthType length );
#endif /* MEMACC_DEVICE_CYT2Bx */
FUNC( Fls_Cdd_JobResultType, MEMACC_CODE ) MemAcc_Cdd_BlankCheck( Fls_AddressType targetAddress, Fls_LengthType length );
#ifdef MEMACC_DEVICE_CYT2Bx
/* Invalid on TraveoII */
#else /* MEMACC_DEVICE_CYT2Bx */
FUNC( Fls_Cdd_JobResultType, MEMACC_CODE ) MemAcc_Cdd_NotBlankCheck( Fls_AddressType targetAddress, Fls_LengthType length, P2VAR( Fls_AddressType, AUTOMATIC, TYPEDEF ) notBlankAddress );
#endif /* MEMACC_DEVICE_CYT2Bx */
FUNC( uint8, MEMACC_CODE ) MemAcc_Cdd_GetLockStatus( void );

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif  /* MEMACC_CDD_H */

/******************************************************************************/
/* History                                                                    */
/*  Version        :Date                                                      */
/*  2-0-0          :2024/08/08                                                */
/******************************************************************************/

/**** End of File *************************************************************/
