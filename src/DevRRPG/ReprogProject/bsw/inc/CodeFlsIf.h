/* CodeFlsIf_h_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CodeFlsIf/HEADER                                            */
/******************************************************************************/
#ifndef CODEFLSIF_H
#define CODEFLSIF_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CODEFLSIF_UNINIT            ((CodeFlsIf_StatusType)0x00U)
#define CODEFLSIF_IDLE              ((CodeFlsIf_StatusType)0x01U)
#define CODEFLSIF_BUSY              ((CodeFlsIf_StatusType)0x02U)
#define CODEFLSIF_UPDATEIDLE        ((CodeFlsIf_StatusType)0x03U)
#define CODEFLSIF_UPDATEBUSY        ((CodeFlsIf_StatusType)0x04U)
#define CODEFLSIF_UPDATECOMPLETE    ((CodeFlsIf_StatusType)0x05U)

#define CODEFLSIF_JOB_OK            ((CodeFlsIf_JobResultType)0x00U)
#define CODEFLSIF_JOB_FAILED        ((CodeFlsIf_JobResultType)0x01U)
#define CODEFLSIF_JOB_PENDING       ((CodeFlsIf_JobResultType)0x02U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8 CodeFlsIf_StatusType;
typedef uint8 CodeFlsIf_JobResultType;

typedef struct {
    uint32  SkipAddr;
    uint32  ExpectedValue;
} CodeFlsIf_SkipInfoType;

#if ( REPROG_CFG_GETBLOCKINFO_USE == STD_ON )
typedef struct {
    uint32 Addr;
    uint32 Size;
} CodeFlsIf_BlockInfoType;
#endif


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_Erase
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
);
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_WriteStart
(
    VAR(uint32, AUTOMATIC) DestAddr,
    VAR(uint32, AUTOMATIC) TotalSize,
    VAR(uint8, AUTOMATIC) SkipNum,
    P2CONST(CodeFlsIf_SkipInfoType, AUTOMATIC, CODEFLSIF_APPL_CONST) SkipInfo
);
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_WriteUpdate
(
    P2CONST(uint8, AUTOMATIC, CODEFLSIF_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_WriteFinish (void);
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_Read
(
    VAR(uint32, AUTOMATIC) SrcAddr,
    P2VAR(uint8, AUTOMATIC, CODEFLSIF_APPL_DATA) DestAddr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_WritableCheck
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    P2CONST(uint8, AUTOMATIC, CODEFLSIF_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) DataSize
);
FUNC(void, CODEFLSIF_CODE_SLOW) CodeFlsIf_SwitchValidArea (void);
FUNC(CodeFlsIf_StatusType, CODEFLSIF_CODE_SLOW) CodeFlsIf_GetStatus (void);
FUNC(CodeFlsIf_JobResultType, CODEFLSIF_CODE_SLOW) CodeFlsIf_GetJobResult (void);
FUNC(void, CODEFLSIF_CODE_SLOW) CodeFlsIf_Init (void);
FUNC(void, CODEFLSIF_CODE_SLOW) CodeFlsIf_MainFunction (void);
FUNC(void, CODEFLSIF_CODE_SLOW) CodeFlsIf_DeInit (void);
FUNC(void, CODEFLSIF_CODE_SLOW) CodeFlsIf_ReprogComplete (void);
#if ( REPROG_CFG_GETBLOCKINFO_USE == STD_ON )
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_GetBlockInfo
(
    VAR(uint32, AUTOMATIC) Addr,
    P2VAR(CodeFlsIf_BlockInfoType, AUTOMATIC, CODEFLSIF_APPL_DATA) BlockInfo
);
#endif
FUNC(uint32, CODEFLSIF_CODE_SLOW) CodeFlsIf_GetNextWriteAddr (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* CODEFLSIF_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

