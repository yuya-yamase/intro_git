/* Sec_Local_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Sec/Local/HEADER                                            */
/******************************************************************************/
#ifndef SEC_LOCAL_H
#define SEC_LOCAL_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SEC_GENSEED_START   ((uint8)0x00U)
#define SEC_GENSEED_GET     ((uint8)0x01U)
#define SEC_GENSEED_STOP    ((uint8)0x02U)

#define SEC_E_PENDING       ((Std_ReturnType)0x02U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, SEC_CODE_FAST) Sec_Usr_Init (void);
FUNC(void, SEC_CODE_FAST) Sec_Usr_DeInit (void);
FUNC(void, SEC_CODE_FAST) Sec_Usr_Time (void);
FUNC(void, SEC_CODE_FAST) Sec_Usr_MainFunction (void);
FUNC(Std_ReturnType, SEC_CODE_FAST) Sec_Usr_GenSeedValue
(
    VAR(uint8, AUTOMATIC) Op,
    P2VAR(uint8, AUTOMATIC, SEC_APPL_DATA) Seed,
    VAR(uint8, AUTOMATIC) SeedSize
);
FUNC(void, SEC_CODE_FAST) Sec_Usr_Get_ToolAuthKey
(
    P2CONST(uint8, AUTOMATIC, SEC_APPL_CONST) RomPtr,
    VAR(uint32, AUTOMATIC) KeySize,
    P2VAR(uint8, AUTOMATIC, SEC_APPL_DATA) KeyPtr
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define SEC_START_SEC_VAR
#include <Sec_MemMap.h>

#define SEC_STOP_SEC_VAR
#include <Sec_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SEC_START_SEC_CST
#include <Sec_MemMap.h>

#define SEC_STOP_SEC_CST
#include <Sec_MemMap.h>


#endif /* SEC_LOCAL_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

