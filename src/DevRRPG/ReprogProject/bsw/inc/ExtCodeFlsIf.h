/* ExtCodeFlsIf_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | ExtCodeFlsIf/HEADER                                         */
/******************************************************************************/
#ifndef EXTCODEFLSIF_H
#define EXTCODEFLSIF_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define EXTCODEFLSIF_UNINIT         ((ExtCodeFlsIf_StatusType)0x00U)
#define EXTCODEFLSIF_IDLE           ((ExtCodeFlsIf_StatusType)0x01U)
#define EXTCODEFLSIF_BUSY           ((ExtCodeFlsIf_StatusType)0x02U)
#define EXTCODEFLSIF_UPDATEIDLE     ((ExtCodeFlsIf_StatusType)0x03U)
#define EXTCODEFLSIF_UPDATEBUSY     ((ExtCodeFlsIf_StatusType)0x04U)
#define EXTCODEFLSIF_UPDATECOMPLETE ((ExtCodeFlsIf_StatusType)0x05U)

#define EXTCODEFLSIF_JOB_OK         ((ExtCodeFlsIf_JobResultType)0x00U)
#define EXTCODEFLSIF_JOB_FAILED     ((ExtCodeFlsIf_JobResultType)0x01U)
#define EXTCODEFLSIF_JOB_PENDING    ((ExtCodeFlsIf_JobResultType)0x02U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8 ExtCodeFlsIf_StatusType;
typedef uint8 ExtCodeFlsIf_JobResultType;

#if ( REPROG_CFG_GETBLOCKINFO_USE == STD_ON )
typedef struct {
    uint32 Addr;
    uint32 Size;
} ExtCodeFlsIf_BlockInfoType;
#endif


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_Erase
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
);
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_WriteStart
(
    VAR(uint32, AUTOMATIC) DestAddr,
    VAR(uint32, AUTOMATIC) TotalSize
);
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_WriteUpdate
(
    P2CONST(uint8, AUTOMATIC, EXTCODEFLSIF_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_WriteFinish (void);
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_Read
(
    VAR(uint32, AUTOMATIC) SrcAddr,
    P2VAR(uint8, AUTOMATIC, EXTCODEFLSIF_APPL_DATA) DestAddr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(ExtCodeFlsIf_StatusType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_GetStatus (void);
FUNC(ExtCodeFlsIf_JobResultType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_GetJobResult (void);
FUNC(void, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_Init (void);
FUNC(void, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_MainFunction (void);
FUNC(void, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_DeInit (void);
#if ( REPROG_CFG_GETBLOCKINFO_USE == STD_ON )
FUNC(Std_ReturnType, EXTCODEFLSIF_CODE_SLOW) ExtCodeFlsIf_GetBlockInfo
(
    VAR(uint32, AUTOMATIC) Addr,
    P2VAR(ExtCodeFlsIf_BlockInfoType, AUTOMATIC, EXTCODEFLSIF_APPL_DATA) BlockInfo
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* EXTCODEFLSIF_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/10/23 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

