/* Sec_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Sec/HEADER                                                  */
/******************************************************************************/
#ifndef SEC_H
#define SEC_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SEC_IDLE            ((uint8)0x00U)
#define SEC_BUSY            ((uint8)0x01U)

#define SEC_JOB_OK          ((uint8)0x00U)
#define SEC_JOB_FAILED      ((uint8)0x01U)
#define SEC_JOB_PENDING     ((uint8)0x02U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    P2VAR(uint8, TYPEDEF, SEC_APPL_DATA) Seed;
    uint16 SeedSize;
} Sec_SeedInfoType;

typedef struct {
    P2VAR(uint8, TYPEDEF, SEC_APPL_DATA) Key;
    uint16 KeySize;
} Sec_KeyInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, SEC_CODE_SLOW) Sec_Init (void);
FUNC(void, SEC_CODE_SLOW) Sec_DeInit (void);
FUNC(void, SEC_CODE_SLOW) Sec_Time (void);
FUNC(void, SEC_CODE_SLOW) Sec_MainFunction (void);
FUNC(uint8, SEC_CODE_SLOW) Sec_GetStatus (void);
FUNC(uint8, SEC_CODE_SLOW) Sec_GetJobResult (void);
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqPreGenSeed
(
    VAR(uint8, AUTOMATIC) Level
);
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqPostGenSeed (void);
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqGenSeed
(
    P2CONST(Sec_SeedInfoType, AUTOMATIC, SEC_APPL_CONST) SeedInfo
);
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqPreGenKey
(
    VAR(uint8, AUTOMATIC) Level
);
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqPostGenKey (void);
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqGenKey
(
    P2CONST(Sec_SeedInfoType, AUTOMATIC, SEC_APPL_CONST) SeedInfo,
    P2CONST(Sec_KeyInfoType, AUTOMATIC, SEC_APPL_CONST) KeyInfo
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


#endif /* SEC_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

