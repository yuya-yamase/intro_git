/* DiagSrv_0x3E_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x3E/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagLib.h>
#include <RpgMfr.h>
#include <RpgSpp.h>

#include <DiagSrv.h>
#include "DiagSrv_0x3E.h"
#include "DiagSrv_0x3E_Cfg.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Message Parameter Position */
#define DIAGSRV_0X3E_SID_POS            ((uint8)0U)
#define DIAGSRV_0X3E_SUBFUNC_POS        ((uint8)1U)

/* Data Length */
#define DIAGSRV_0X3E_RSP_MSG_LEN        ((uint16)2U)

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>

/******************************************************************************/
/* Function Name | DiagSrv_0x3E_Init                                          */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x3E_Init (void)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x3E_Time                                          */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x3E_Time (void)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x3E_Processing                                    */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x3E_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Index;
    VAR(uint16, AUTOMATIC) MsgLen;

    Index = 0U;

    Nrc = DiagLib_CheckSubfunctionSupport(Msg, &DiagSrv_0x3E_SubfuncConfig, &Index);
    if( Nrc == DIAG_NRC_PR )
    {
        MsgLen = DIAG_SUBFUNCMSG_MIN_SIZE + DiagSrv_0x3E_SubfuncConfig.InfoPtr[Index].Length;
        if( Msg->ReqDataLen != MsgLen )
        {
            Nrc = DIAG_NRC_IMLOIF;
        }
        else
        {
            Nrc = RpgMfr_MsgCheckCondition(Msg);
            if( Nrc == DIAG_NRC_PR )
            {
                Nrc = RpgSpp_MsgCheckCondition(Msg);
            }
        }
    }

    if( Nrc == DIAG_NRC_PR )
    {
        Msg->ResData[DIAGSRV_0X3E_SID_POS] = DIAG_MAKE_POSRSP_SID(Msg);
        Msg->ResData[DIAGSRV_0X3E_SUBFUNC_POS] = DIAG_GET_SUBFUNCTION(Msg);
        Msg->ResDataLen = DIAGSRV_0X3E_RSP_MSG_LEN;
        DiagLib_SendPosRsp(Msg);
    }
    else
    {
        DiagLib_SendNegRsp(Nrc, Msg);
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x3E_Confirmation                                  */
/* Description   | Confirmation function                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Transmission complete status                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x3E_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2019/12/03 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

