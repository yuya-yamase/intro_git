/* CmpDecmp_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CmpDecmp/HEADER                                             */
/******************************************************************************/
#ifndef CMPDECMP_H
#define CMPDECMP_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CMPDECMP_DECMP_START    ((uint8)0x00U)
#define CMPDECMP_DECMP_RESUME   ((uint8)0x01U)

#define CMPDECMP_E_PENDING      ((Std_ReturnType)0x02U)
#define CMPDECMP_E_SUSPEND      ((Std_ReturnType)0x03U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    P2CONST(uint8, TYPEDEF, CMPDECMP_APPL_CONST) CompData;
    uint32 CompDataSize;
    uint32 CompDataTotalSize;
    P2VAR(uint8, TYPEDEF, CMPDECMP_APPL_DATA) DecompBuf;
    uint32 DecompResultSize;
} CmpDecmp_DecompressInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, CMPDECMP_CODE_SLOW) CmpDecmp_Init (void);
FUNC(void, CMPDECMP_CODE_SLOW) CmpDecmp_DeInit (void);
FUNC(void, CMPDECMP_CODE_SLOW) CmpDecmp_Time (void);
FUNC(void, CMPDECMP_CODE_SLOW) CmpDecmp_MainFunction (void);
FUNC(Std_ReturnType, CMPDECMP_CODE_SLOW) CmpDecmp_PreDecompress (void);
FUNC(Std_ReturnType, CMPDECMP_CODE_SLOW) CmpDecmp_PostDecompress (void);
FUNC(Std_ReturnType, CMPDECMP_CODE_SLOW) CmpDecmp_Decompress
(
    VAR(uint8, AUTOMATIC) Op,
    P2VAR(CmpDecmp_DecompressInfoType, AUTOMATIC, CMPDECMP_APPL_DATA) DecmpInfo
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define CMPDECMP_START_SEC_VAR
#include <CmpDecmp_MemMap.h>

#define CMPDECMP_STOP_SEC_VAR
#include <CmpDecmp_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CMPDECMP_START_SEC_CST
#include <CmpDecmp_MemMap.h>

#define CMPDECMP_STOP_SEC_CST
#include <CmpDecmp_MemMap.h>


#endif /* CMPDECMP_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

