/* DiagSrv_0x22_Usr_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x22/Usr/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

/*===== Sample ===============================================================*/
#include <Rte.h>
/*===== Sample ===============================================================*/

#include "DiagSrv_0x22.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#define DIAGSRV_0X22_USR_DID_HARDWARENUMBER         ((uint16)0xF191U)
#define DIAGSRV_0X22_USR_DID_SERIALNUMBER           ((uint16)0xF18CU)

#define DIAGSRV_0X22_USR_HARDWARENUMBER_LENGTH      (sizeof(DiagSrv_0x22_Usr_HwNumber_Data) / sizeof(DiagSrv_0x22_Usr_HwNumber_Data[0]))
#define DIAGSRV_0X22_USR_SERIALNUMBER_LENGTH        (sizeof(DiagSrv_0x22_Usr_SerialNumber_Data) / sizeof(DiagSrv_0x22_Usr_SerialNumber_Data[0]))

#define DIAGSRV_0X22_USR_PROCESS_NONE               ((uint8)0x00U)
#define DIAGSRV_0X22_USR_PROCESS_READ_START         ((uint8)0x01U)
#define DIAGSRV_0X22_USR_PROCESS_READ_END           ((uint8)0x02U)
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
typedef struct {
    P2VAR(uint8, TYPEDEF, DIAGSRV_APPL_DATA) Data;
    uint16 Did;
    uint16 DataLength;
    uint8 Result;
    uint8 Status;
    uint8 Process;
} DiagSrv_0x22_Usr_JobInfoType;
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(DiagSrv_0x22_Usr_JobInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x22_Usr_Job;
/*===== Sample ===============================================================*/

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

/*===== Sample ===============================================================*/
static CONST(uint8, DIAGSRV_CONST) DiagSrv_0x22_Usr_HwNumber_Data[] = {
    0x01U, 0x0CU, 0x01U,
    0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU,
    0x3FU, 0x3FU, 0x3FU, 0x3FU
};
static CONST(uint8, DIAGSRV_CONST) DiagSrv_0x22_Usr_SerialNumber_Data[] = {
    0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU,
    0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU, 0x3FU,
    0x3FU, 0x3FU, 0x3FU, 0x3FU
};
/*===== Sample ===============================================================*/

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Usr_Init                                      */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Usr_Init (void)
{
/*===== Sample ===============================================================*/
    DiagSrv_0x22_Usr_Job.Did = 0U;
    DiagSrv_0x22_Usr_Job.Data = NULL_PTR;
    DiagSrv_0x22_Usr_Job.DataLength = 0U;
    DiagSrv_0x22_Usr_Job.Result = DIAG_NRC_GR;
    DiagSrv_0x22_Usr_Job.Status = DIAGSRV_0X22_USR_IDLE;
    DiagSrv_0x22_Usr_Job.Process = DIAGSRV_0X22_USR_PROCESS_NONE;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Usr_Time                                      */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Usr_Time (void)
{
/*===== Sample ===============================================================*/
    if( DiagSrv_0x22_Usr_Job.Process == DIAGSRV_0X22_USR_PROCESS_READ_START )
    {
        if( DiagSrv_0x22_Usr_Job.Did == DIAGSRV_0X22_USR_DID_HARDWARENUMBER )
        {
            Rte_Rpg_MemCopy(DiagSrv_0x22_Usr_Job.Data,
                            DiagSrv_0x22_Usr_HwNumber_Data,
                            (uint32)DiagSrv_0x22_Usr_Job.DataLength);
        }
        else    /* DIAGSRV_0X22_USR_DID_SERIALNUMBER */
        {
            Rte_Rpg_MemCopy(DiagSrv_0x22_Usr_Job.Data,
                            DiagSrv_0x22_Usr_SerialNumber_Data,
                            (uint32)DiagSrv_0x22_Usr_Job.DataLength);
        }
        DiagSrv_0x22_Usr_Job.Process = DIAGSRV_0X22_USR_PROCESS_READ_END;
    }

    if( DiagSrv_0x22_Usr_Job.Process == DIAGSRV_0X22_USR_PROCESS_READ_END )
    {
        DiagSrv_0x22_Usr_Job.Did = 0U;
        DiagSrv_0x22_Usr_Job.Data = NULL_PTR;
        DiagSrv_0x22_Usr_Job.DataLength = 0U;
        DiagSrv_0x22_Usr_Job.Result = DIAG_NRC_PR;
        DiagSrv_0x22_Usr_Job.Status = DIAGSRV_0X22_USR_IDLE;
        DiagSrv_0x22_Usr_Job.Process = DIAGSRV_0X22_USR_PROCESS_NONE;
    }
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Usr_ReqReadDidData                            */
/* Description   | Read did data                                              */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Did        : DID                                     */
/*               | [OUT] Data       : Data address                            */
/*               | [IN]  DataLength : Data length                             */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_XX                                               */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_Usr_ReqReadDidData
(
    VAR(uint16, AUTOMATIC) Did,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Data,
    VAR(uint16, AUTOMATIC) DataLength
)
{
/*===== Sample ===============================================================*/
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GR;

    if( DiagSrv_0x22_Usr_Job.Status == DIAGSRV_0X22_USR_IDLE )
    {
        if( (Data != NULL_PTR) &&
            (((Did == DIAGSRV_0X22_USR_DID_HARDWARENUMBER) && (DataLength == DIAGSRV_0X22_USR_HARDWARENUMBER_LENGTH)) ||
             ((Did == DIAGSRV_0X22_USR_DID_SERIALNUMBER) && (DataLength == DIAGSRV_0X22_USR_SERIALNUMBER_LENGTH))) )
        {
            DiagSrv_0x22_Usr_Job.Did = Did;
            DiagSrv_0x22_Usr_Job.Data = Data;
            DiagSrv_0x22_Usr_Job.DataLength = DataLength;
            DiagSrv_0x22_Usr_Job.Result = DIAG_NRC_GR;
            DiagSrv_0x22_Usr_Job.Status = DIAGSRV_0X22_USR_BUSY;
            DiagSrv_0x22_Usr_Job.Process = DIAGSRV_0X22_USR_PROCESS_READ_START;

            Nrc = DIAG_NRC_RCRRP;
        }
    }

    return Nrc;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Usr_GetStatus                                 */
/* Description   | Acquires status of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  DIAGSRV_0X22_USR_IDLE                                     */
/*               |  DIAGSRV_0X22_USR_BUSY                                     */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_Usr_GetStatus (void)
{
/*===== Sample ===============================================================*/
    return DiagSrv_0x22_Usr_Job.Status;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | DiagSrv_0x22_Usr_GetJobResult                              */
/* Description   | Acquires result of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_XX                                               */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_Usr_GetJobResult (void)
{
/*===== Sample ===============================================================*/
    return DiagSrv_0x22_Usr_Job.Result;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/07/05 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

