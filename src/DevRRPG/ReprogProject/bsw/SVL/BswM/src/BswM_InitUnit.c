/* BswM_InitUnit_c_Revision(v5.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/InitUnit/CODE                                          */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include "BswM_Local.h"

#include <Rte.h>
#include <WdgM.h>
#include <CanSM.h>
#include <ComM.h>
#include <Gdn.h>
#include <MemM.h>
#include <CanIf.h>
#include <CanTrcv.h>
#include <CodeFlsIf.h>
#include <CodeRamIf.h>
#include <ExtCodeFlsIf.h>
#include <SubMiconIf.h>
#include <WrapCrypto.h>

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
static FUNC(void, BSWM_CODE_FAST) BswM_InitUnit_1st (void);
static FUNC(void, BSWM_CODE_FAST) BswM_InitUnit_2nd (void);
static FUNC(void, BSWM_CODE_FAST) BswM_InitUnit_3rd (void);
static FUNC(void, BSWM_CODE_FAST) BswM_InitUnit_Csm (void);
static FUNC(void, BSWM_CODE_FAST) BswM_InitUnit_WdgTrigger (void);


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
/* Function Name | BswM_InitUnit                                              */
/* Description   | Initializes other unit                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_FAST) BswM_InitUnit (void)
{
    BswM_InitUnit_1st();

    BswM_InitUnit_2nd();

    BswM_InitUnit_3rd();

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_InitUnit_1st                                          */
/* Description   | Initializes other unit(1st)                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_InitUnit_1st (void)
{
    BswM_InitUnit_WdgTrigger();
    SubMiconIf_Init();

    BswM_InitUnit_WdgTrigger();
    CanTrcv_Init(NULL_PTR);

    BswM_InitUnit_WdgTrigger();
    CanIf_Init(BswM_CfgPtr->CanIfCfgDataPtr);

    BswM_InitUnit_WdgTrigger();
    ComM_Init(BswM_CfgPtr->ComMCfgDataPtr);

    BswM_InitUnit_WdgTrigger();
    CanSM_Init(BswM_CfgPtr->CanSMCfgDataPtr);

    return;
}

/******************************************************************************/
/* Function Name | BswM_InitUnit_2nd                                          */
/* Description   | Initializes other unit(2nd)                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_InitUnit_2nd (void)
{
    BswM_InitUnit_Csm();

    BswM_InitUnit_WdgTrigger();
    Rte_RpgLib_Init();

    BswM_InitUnit_WdgTrigger();
    Gdn_Init();

    BswM_InitUnit_WdgTrigger();
    Rte_RpgMfr_Init();

    BswM_InitUnit_WdgTrigger();
    Rte_RpgSpp_Init();

    BswM_InitUnit_WdgTrigger();
    Rte_Sec_Init();

    BswM_InitUnit_WdgTrigger();
    Rte_Decrypt_Init();

    BswM_InitUnit_WdgTrigger();
    Rte_CmpDecmp_Init();

    BswM_InitUnit_WdgTrigger();
    Rte_PrgChk_Init();

    BswM_InitUnit_WdgTrigger();
    Rte_FscDtct_Init();

    BswM_InitUnit_WdgTrigger();
    Rte_VehInf_Init();

    return;
}

/******************************************************************************/
/* Function Name | BswM_InitUnit_3rd                                          */
/* Description   | Initializes other unit(3rd)                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_InitUnit_3rd (void)
{
    BswM_InitUnit_WdgTrigger();
    CodeFlsIf_Init();

    BswM_InitUnit_WdgTrigger();
    ExtCodeFlsIf_Init();

    BswM_InitUnit_WdgTrigger();
    CodeRamIf_Init();

    BswM_InitUnit_WdgTrigger();
    MemM_Init();

#if (REPROG_CFG_ETH_USE == STD_ON)
    BswM_InitUnit_WdgTrigger();
    BswM_Eth_Init();
#endif

#if (REPROG_CFG_CXPI_USE == STD_ON)
    BswM_InitUnit_WdgTrigger();
    CxpiWrap_Init();
#endif

    return;
}

/******************************************************************************/
/* Function Name | BswM_InitUnit_Csm                                          */
/* Description   | Initializes Csm unit                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_InitUnit_Csm (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    BswM_InitUnit_WdgTrigger();
    WrapCrypto_Init();

    if( BswM_Cfg_Data.UidDataPtr->UidSkip == (uint8)STD_OFF )
    {
        BswM_InitUnit_WdgTrigger();
        FuncRet = WrapCrypto_Set_UID(BswM_Cfg_Data.UidDataPtr->KeyID,
                                    BswM_Cfg_Data.UidDataPtr->UidPtr,
                                    BswM_Cfg_Data.UidDataPtr->UidSize);
        if( FuncRet != (Std_ReturnType)E_OK )
        {
            BswM_ReportError(BSWM_API_ID_INITUNIT_CSM, BSWM_E_UIDSET_ERR);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_InitUnit_WdgTrigger                                   */
/* Description   | Clear watchdog timer                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_InitUnit_WdgTrigger (void)
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
/*  v2.00       :2018/02/13 :Update                                rel.AUBASS */
/*  v3.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v4.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v5.00       :2022/10/04 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

