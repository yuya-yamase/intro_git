/* BswM_DeinitUnit_c_Revision(v4.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/DeinitUnit/CODE                                        */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Rte.h>
#include <WdgM.h>
#include <ComM.h>
#include <Gdn.h>
#include <MemM.h>
#include <CodeFlsIf.h>
#include <CodeRamIf.h>
#include <ExtCodeFlsIf.h>
#include <SubMiconIf.h>

#if (REPROG_CFG_ETH_USE == STD_ON)
#include <BswM_Eth.h>
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
#include <CxpiWrap_FarcallWrapper.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, BSWM_CODE_FAST) BswM_DeinitUnit_1st (void);
static FUNC(void, BSWM_CODE_FAST) BswM_DeinitUnit_2nd (void);
static FUNC(void, BSWM_CODE_FAST) BswM_DeinitUnit_3rd (void);
static FUNC(void, BSWM_CODE_FAST) BswM_DeinitUnit_WdgTrigger (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_VAR
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC_VAR
#include <BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_CST
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC_CST
#include <BswM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define BSWM_START_SEC_CODE
#include <BswM_MemMap.h>

/******************************************************************************/
/* Function Name | BswM_DeinitUnit                                            */
/* Description   | Deinitializes other unit                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_FAST) BswM_DeinitUnit (void)
{
    BswM_DeinitUnit_1st();

    BswM_DeinitUnit_2nd();

    BswM_DeinitUnit_3rd();

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_DeinitUnit_1st                                        */
/* Description   | Deinitializes other unit(1st)                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_DeinitUnit_1st (void)
{
#if (REPROG_CFG_CXPI_USE == STD_ON)
    BswM_DeinitUnit_WdgTrigger();
    CxpiWrap_SsDeInit();
#endif

#if (REPROG_CFG_ETH_USE == STD_ON)
    BswM_DeinitUnit_WdgTrigger();
    BswM_Eth_PrepareDeInit();

    BswM_DeinitUnit_WdgTrigger();
    BswM_Eth_DeInit();
#endif

    BswM_DeinitUnit_WdgTrigger();
    MemM_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    CodeRamIf_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    ExtCodeFlsIf_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    CodeFlsIf_DeInit();

    return;
}

/******************************************************************************/
/* Function Name | BswM_DeinitUnit_2nd                                        */
/* Description   | Deinitializes other unit(2nd)                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_DeinitUnit_2nd (void)
{
    BswM_DeinitUnit_WdgTrigger();
    Rte_VehInf_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    Rte_FscDtct_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    Rte_PrgChk_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    Rte_CmpDecmp_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    Rte_Decrypt_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    Rte_Sec_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    Rte_RpgSpp_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    Rte_RpgMfr_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    Gdn_Shutdown();

    BswM_DeinitUnit_WdgTrigger();
    Rte_RpgLib_DeInit();

    return;
}

/******************************************************************************/
/* Function Name | BswM_DeinitUnit_3rd                                        */
/* Description   | Deinitializes other unit(3rd)                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_DeinitUnit_3rd (void)
{
    BswM_DeinitUnit_WdgTrigger();
    ComM_DeInit();

    BswM_DeinitUnit_WdgTrigger();
    SubMiconIf_DeInit();

    return;
}

/******************************************************************************/
/* Function Name | BswM_DeinitUnit_WdgTrigger                                 */
/* Description   | Clear watchdog timer                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_DeinitUnit_WdgTrigger (void)
{
    WdgM_SetTriggerCondition();
    WdgM_Trigger();

    return;
}

#define BSWM_STOP_SEC_CODE
#include <BswM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v3.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v4.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

