/* IntHndlr_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | IntHndlr/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <IntHndlr.h>
#include "IntHndlr_Local.h"

#include <Shutdown.h>
#include <Rte.h>
#include <Gpt.h>
#include <Can.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Timer Channel ID */
#define INTHNDLR_GPT_CHANNEL_ID_0   (0U)
#define INTHNDLR_GPT_CHANNEL_ID_1   (1U)

#define INTHNDLR_NOTIFYFUNCINFO_NUM (sizeof(IntHndlr_NotifyFuncInfo) / sizeof(IntHndlr_NotifyFuncInfo[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef P2FUNC(Std_ReturnType, INTHNDLR_CALLOUT_CODE, IntHndlr_NotifyFuncType)
(
    VAR(uint32, AUTOMATIC) Eiic
);

typedef struct {
    IntHndlr_NotifyFuncType Func;
} IntHndlr_NotifyFuncInfoType;

typedef struct {
    uint32 Num;
    P2CONST(IntHndlr_NotifyFuncInfoType, TYPEDEF, INTHNDLR_APPL_CONST) FuncPtr;
} IntHndlr_NotifyInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(Std_ReturnType, INTHNDLR_CODE_FAST) IntHndlr_Notification_Gpt
(
    VAR(uint32, AUTOMATIC) Eiic
);
#if (REPROG_CFG_CAN_DISABLE != STD_ON)
static FUNC(Std_ReturnType, INTHNDLR_CODE_FAST) IntHndlr_Notification_Can
(
    VAR(uint32, AUTOMATIC) Eiic
);
#endif
static FUNC(Std_ReturnType, INTHNDLR_CODE_FAST) IntHndlr_Notification_UsrHook
(
    VAR(uint32, AUTOMATIC) Eiic
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define INTHNDLR_START_SEC_VAR
#include <IntHndlr_MemMap.h>

#define INTHNDLR_STOP_SEC_VAR
#include <IntHndlr_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define INTHNDLR_START_SEC_CST
#include <IntHndlr_MemMap.h>

static CONST(IntHndlr_NotifyFuncInfoType, INTHNDLR_CONST) IntHndlr_NotifyFuncInfo[] = {
    { &IntHndlr_Notification_Gpt     }
#if (REPROG_CFG_CAN_DISABLE != STD_ON)
   ,{ &IntHndlr_Notification_Can     }
#endif
   ,{ &IntHndlr_Notification_UsrHook } /* This function is defined at the end of the table */
};

static CONST(AB_83_ConstV IntHndlr_NotifyInfoType, INTHNDLR_CONST) IntHndlr_NotifyInfo = {
    INTHNDLR_NOTIFYFUNCINFO_NUM,
    &IntHndlr_NotifyFuncInfo[0]
};

#define INTHNDLR_STOP_SEC_CST
#include <IntHndlr_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define INTHNDLR_START_SEC_CODE
#include <IntHndlr_MemMap.h>

/******************************************************************************/
/* Function Name | IntHndlr_EIINT_Sub                                         */
/* Description   | EIINT routine                                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Eiic : Exception code                                 */
/* Return Value  | None                                                       */
/* Notes         | This function will never return unless interrupt factor.   */
/******************************************************************************/
FUNC(void, INTHNDLR_CODE_FAST) IntHndlr_EIINT_Sub
(
    VAR(uint32, AUTOMATIC) Eiic
)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    for( i = 0UL; i < IntHndlr_NotifyInfo.Num; i++ )
    {
        Ret = IntHndlr_NotifyInfo.FuncPtr[i].Func(Eiic);
        if( Ret == (Std_ReturnType)E_OK )
        {
            break;
        }
    }

    if( Ret != (Std_ReturnType)E_OK )
    {
        /* Reset MCU(no return) */
        Shutdown_ResetMcuRam();
    }

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | IntHndlr_Notification_Gpt                                  */
/* Description   | Notify MCAL Gpt driver of a exception code                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] Eiic : Exception code                                 */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, INTHNDLR_CODE_FAST) IntHndlr_Notification_Gpt
(
    VAR(uint32, AUTOMATIC) Eiic
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    /* When exception factor is  GPT channel 0 or 1, notify MCAL Gpt driver */
    if( Eiic == IntHndlr_Cfg_Data.GptDataPtr->Gpt0IntCode )
    {
        Gpt_Interrupt((Gpt_ChannelType)INTHNDLR_GPT_CHANNEL_ID_0);
        Ret = E_OK;
    }
    else if( Eiic == IntHndlr_Cfg_Data.GptDataPtr->Gpt1IntCode )
    {
        Gpt_Interrupt((Gpt_ChannelType)INTHNDLR_GPT_CHANNEL_ID_1);
        Ret = E_OK;
    }
    else
    {
        /* No process */
    }

    return Ret;
}

#if (REPROG_CFG_CAN_DISABLE != STD_ON)
/******************************************************************************/
/* Function Name | IntHndlr_Notification_Can                                  */
/* Description   | Notify MCAL Can driver of a exception code                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] Eiic : Exception code                                 */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, INTHNDLR_CODE_FAST) IntHndlr_Notification_Can
(
    VAR(uint32, AUTOMATIC) Eiic
)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    for( i = 0UL; i < IntHndlr_Cfg_Data.CanDataPtr->CanNum; i++ )
    {
        /* When exception factor is CAN receive interrupt, */
        /* notify MCAL CAN driver.                         */
        if( Eiic == IntHndlr_Cfg_Data.CanDataPtr->CanInfoPtr[i].CanIntRxCode )
        {
            Can_Interrupt((U1)IntHndlr_Cfg_Data.CanDataPtr->CanInfoPtr[i].CanChannelNo,
                          (U4)IntHndlr_Cfg_Data.CanDataPtr->CanInfoPtr[i].CanIntRxCodeNotify);
            Ret = E_OK;
        }
        /* When exception factor is CAN transmit interrupt, */
        /* notify MCAL CAN driver.                          */
        else if( Eiic == IntHndlr_Cfg_Data.CanDataPtr->CanInfoPtr[i].CanIntTxCode )
        {
            Can_Interrupt((U1)IntHndlr_Cfg_Data.CanDataPtr->CanInfoPtr[i].CanChannelNo,
                          (U4)IntHndlr_Cfg_Data.CanDataPtr->CanInfoPtr[i].CanIntTxCodeNotify);
            Ret = E_OK;
        }
        else
        {
            /* No process */
        }

        if( Ret == (Std_ReturnType)E_OK )
        {
            break;
        }
    }

    return Ret;
}
#endif

/******************************************************************************/
/* Function Name | IntHndlr_Notification_UsrHook                              */
/* Description   | Notify UsrHook of a exception code                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] Eiic : Exception code                                 */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | This function will never return when Rte returned          */
/*               | as unrecoverable .                                         */
/******************************************************************************/
static FUNC(Std_ReturnType, INTHNDLR_CODE_FAST) IntHndlr_Notification_UsrHook
(
    VAR(uint32, AUTOMATIC) Eiic
)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint32, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    for( i = 0UL; i < IntHndlr_Cfg_Data.UsrDataPtr->UsrNum; i++ )
    {
        /* When exception factor is user defined interrupt, */
        /* notify RTE unit.                                 */
        if( Eiic == IntHndlr_Cfg_Data.UsrDataPtr->UsrInfoPtr[i].UsrIntCode )
        {
            Result = Rte_RpgEvtHk_ExcptEvt(Eiic);
            if( Result != RTE_RPGEVTHK_EXCPT_RECOVER )
            {
                /* Reset MCU(no return) */
                Shutdown_ResetMcuRam();
            }

            Ret = E_OK;
            break;
        }
    }

    return Ret;
}


#define INTHNDLR_STOP_SEC_CODE
#include <IntHndlr_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/02/13 :Update                                rel.AUBASS */
/*  v3.00       :2021/03/09 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

