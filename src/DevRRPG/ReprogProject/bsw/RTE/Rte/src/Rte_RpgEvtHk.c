/* Rte_RpgEvtHk_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/RpgEvtHk/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Rte_RpgEvtHk.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define RTE_RPGEVTHK_START_SEC_VAR
#include <Rte_RpgEvtHk_MemMap.h>

#define RTE_RPGEVTHK_STOP_SEC_VAR
#include <Rte_RpgEvtHk_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RTE_RPGEVTHK_START_SEC_CST
#include <Rte_RpgEvtHk_MemMap.h>

#define RTE_RPGEVTHK_STOP_SEC_CST
#include <Rte_RpgEvtHk_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define RTE_RPGEVTHK_START_SEC_CODE
#include <Rte_RpgEvtHk_MemMap.h>

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SchEvt_InitFirst                              */
/* Description   | Wrapper of RpgEvtHk_SchEvt_InitFirst()                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_InitFirst (void)
{
    RpgEvtHk_SchEvt_InitFirst();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SchEvt_InitLast                               */
/* Description   | Wrapper of RpgEvtHk_SchEvt_InitLast()                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_InitLast (void)
{
    RpgEvtHk_SchEvt_InitLast();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SchEvt_DeInitFirst                            */
/* Description   | Wrapper of RpgEvtHk_SchEvt_DeInitFirst()                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_DeInitFirst (void)
{
    RpgEvtHk_SchEvt_DeInitFirst();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SchEvt_DeInitLast                             */
/* Description   | Wrapper of RpgEvtHk_SchEvt_DeInitLast()                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_DeInitLast (void)
{
    RpgEvtHk_SchEvt_DeInitLast();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SchEvt_RunFirst                               */
/* Description   | Wrapper of RpgEvtHk_SchEvt_RunFirst()                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_RunFirst (void)
{
    RpgEvtHk_SchEvt_RunFirst();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SchEvt_RunLast                                */
/* Description   | Wrapper of RpgEvtHk_SchEvt_RunLast()                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_RunLast (void)
{
    RpgEvtHk_SchEvt_RunLast();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SchEvt_MainFunction                           */
/* Description   | Wrapper of RpgEvtHk_SchEvt_MainFunction()                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_MainFunction (void)
{
    RpgEvtHk_SchEvt_MainFunction();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SchEvt_TimeHigh                               */
/* Description   | Wrapper of RpgEvtHk_SchEvt_TimeHigh()                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_TimeHigh (void)
{
    RpgEvtHk_SchEvt_TimeHigh();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SchEvt_TimeLow                                */
/* Description   | Wrapper of RpgEvtHk_SchEvt_TimeLow()                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_TimeLow (void)
{
    RpgEvtHk_SchEvt_TimeLow();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SessionEvt_Def                                */
/* Description   | RpgEvtHk_SessionEvt_Def() is restrained to call            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SessionEvt_Def (void)
{
    /* No process */

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SessionEvt_Ext                                */
/* Description   | RpgEvtHk_SessionEvt_Ext() is restrained to call            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SessionEvt_Ext (void)
{
    /* No process */

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_SessionEvt_Prg                                */
/* Description   | RpgEvtHk_SessionEvt_Prg() is restrained to call            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SessionEvt_Prg (void)
{
    /* No process */

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_RpgEvt_UnlockSec                              */
/* Description   | RpgEvtHk_RpgEvt_UnlockSec() is restrained to call          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_UnlockSec (void)
{
    /* No process */

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_RpgEvt_LockSec                                */
/* Description   | RpgEvtHk_RpgEvt_LockSec() is restrained to call            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_LockSec (void)
{
    /* No process */

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_RpgEvt_FlsPrgNotReady                         */
/* Description   | RpgEvtHk_RpgEvt_FlsPrgNotReady() is restrained to call     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_FlsPrgNotReady (void)
{
    /* No process */

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_RpgEvt_FlsPrgReady                            */
/* Description   | RpgEvtHk_RpgEvt_FlsPrgReady() is restrained to call        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_FlsPrgReady (void)
{
    /* No process */

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_RpgEvt_PreMemErase                            */
/* Description   | RpgEvtHk_RpgEvt_PreMemErase() is restrained to call        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_PreMemErase (void)
{
    /* No process */

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_RpgEvt_PostPrgChk                             */
/* Description   | RpgEvtHk_RpgEvt_PostPrgChk() is restrained to call         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_PostPrgChk (void)
{
    /* No process */

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_ModeEvt_CanStart                              */
/* Description   | Wrapper of RpgEvtHk_ModeEvt_CanStart()                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_CanStart (void)
{
    RpgEvtHk_ModeEvt_CanStart();

    return;
}

#if (REPROG_CFG_ETH_USE == STD_ON)
/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_ModeEvt_EthStart                              */
/* Description   | Wrapper of RpgEvtHk_ModeEvt_EthStart()                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_EthStart (void)
{
    RpgEvtHk_ModeEvt_EthStart();

    return;
}
#endif

#if (REPROG_CFG_CXPI_USE == STD_ON)
/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_ModeEvt_CxpiStart                             */
/* Description   | Wrapper of RpgEvtHk_ModeEvt_CxpiStart()                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_CxpiStart (void)
{
    RpgEvtHk_ModeEvt_CxpiStart();

    return;
}
#endif

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_ModeEvt_AccOn                                 */
/* Description   | Wrapper of RpgEvtHk_ModeEvt_AccOn()                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_AccOn (void)
{
    RpgEvtHk_ModeEvt_AccOn();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_ModeEvt_AccOff                                */
/* Description   | Wrapper of RpgEvtHk_ModeEvt_AccOff()                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_AccOff (void)
{
    RpgEvtHk_ModeEvt_AccOff();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_ModeEvt_IgOn                                  */
/* Description   | Wrapper of RpgEvtHk_ModeEvt_IgOn()                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_IgOn (void)
{
    RpgEvtHk_ModeEvt_IgOn();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_ModeEvt_IgOff                                 */
/* Description   | Wrapper of RpgEvtHk_ModeEvt_IgOff()                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_IgOff (void)
{
    RpgEvtHk_ModeEvt_IgOff();

    return;
}

/******************************************************************************/
/* Function Name | Rte_RpgEvtHk_ExcptEvt                                      */
/* Description   | Wrapper of RpgEvtHk_ExcptEvt()                             */
/* Preconditions |                                                            */
/* Parameters    | [IN]  ExcptCode   : Exceptions code                        */
/* Return Value  | Recovery status                                            */
/*               |  RTE_RPGEVTHK_EXCPT_RECOVER                                */
/*               |  RTE_RPGEVTHK_EXCPT_UNRECOVER                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint32, RTE_CODE_SLOW) Rte_RpgEvtHk_ExcptEvt
(
    VAR(uint32, AUTOMATIC) ExcptCode
)
{
    VAR(uint32, AUTOMATIC) Ret;

    Ret = RpgEvtHk_ExcptEvt(ExcptCode);

    return Ret;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define RTE_RPGEVTHK_STOP_SEC_CODE
#include <Rte_RpgEvtHk_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

