/* CodeRamIf_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CodeRamIf/HEADER                                            */
/******************************************************************************/
#ifndef CODERAMIF_H
#define CODERAMIF_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CODERAMIF_UNINIT            ((CodeRamIf_StatusType)0x00U)
#define CODERAMIF_IDLE              ((CodeRamIf_StatusType)0x01U)
#define CODERAMIF_BUSY              ((CodeRamIf_StatusType)0x02U)
#define CODERAMIF_UPDATEIDLE        ((CodeRamIf_StatusType)0x03U)
#define CODERAMIF_UPDATEBUSY        ((CodeRamIf_StatusType)0x04U)
#define CODERAMIF_UPDATECOMPLETE    ((CodeRamIf_StatusType)0x05U)

#define CODERAMIF_JOB_OK            ((CodeRamIf_JobResultType)0x00U)
#define CODERAMIF_JOB_FAILED        ((CodeRamIf_JobResultType)0x01U)
#define CODERAMIF_JOB_PENDING       ((CodeRamIf_JobResultType)0x02U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8 CodeRamIf_StatusType;
typedef uint8 CodeRamIf_JobResultType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(Std_ReturnType, CODERAMIF_CODE_SLOW) CodeRamIf_WriteStart
(
    VAR(uint32, AUTOMATIC) DestAddr,
    VAR(uint32, AUTOMATIC) TotalSize
);
FUNC(Std_ReturnType, CODERAMIF_CODE_SLOW) CodeRamIf_WriteUpdate
(
    P2CONST(uint8, AUTOMATIC, CODERAMIF_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(Std_ReturnType, CODERAMIF_CODE_SLOW) CodeRamIf_WriteFinish (void);
FUNC(Std_ReturnType, CODERAMIF_CODE_SLOW) CodeRamIf_Read
(
    VAR(uint32, AUTOMATIC) SrcAddr,
    P2VAR(uint8, AUTOMATIC, CODERAMIF_APPL_DATA) DestAddr,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(CodeRamIf_StatusType, CODERAMIF_CODE_SLOW) CodeRamIf_GetStatus (void);
FUNC(CodeRamIf_JobResultType, CODERAMIF_CODE_SLOW) CodeRamIf_GetJobResult (void);
FUNC(void, CODERAMIF_CODE_SLOW) CodeRamIf_Init (void);
FUNC(void, CODERAMIF_CODE_SLOW) CodeRamIf_MainFunction (void);
FUNC(void, CODERAMIF_CODE_SLOW) CodeRamIf_DeInit (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* CODERAMIF_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/02/12 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

