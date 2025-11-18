/* bsw_bswm_cs_status_c_v3-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/STATUS/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_bswm_cs_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../inc/bsw_bswm_cs_config.h"
#if ( BSW_BSWM_CS_FUNC_BSWMCS == BSW_USE )

#include <nm/bsw_nm.h>
#include <com/bsw_com.h>
#include <pdur/bsw_pdur.h>
#include <ldcom/bsw_ldcom.h>
#include <ipdum/bsw_ipdum.h>

#include "../inc/bsw_bswm_cs_status.h"
#include "../inc/bsw_bswm_cs_status_bswmeth.h"
#include "../inc/bsw_bswm_cs_status_bswmlin.h"
#include "../inc/bsw_bswm_cs_status_xcp.h"
#include "../inc/bsw_bswm_cs_sysstat.h"
#include "../inc/bsw_bswm_cs_ctrl.h"
#include "../inc/bsw_bswm_cs_connector.h"

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#include "../../Com/inc/bsw_com_config.h"
#endif

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
#include <bswm_can/bsw_bswm_can.h>
#endif

#if ( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
#include <bswm_vps/bsw_bswm_vps.h>
#endif

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_CS_u2VERIFY_KEY_B8            ((BswU2)0x00FFU)
#define BSW_BSWM_CS_u2SHIFT_B8                 ((BswU2)0x0008U)

#define BSW_BSWM_CS_u2OFFSETTIME_NONE          ((BswU2)0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void bsw_bswm_cs_st_InitIpduGrVct( void );
static void bsw_bswm_cs_st_MainFuncMidIn( void );
static void bsw_bswm_cs_st_MainFuncMidCtrl( void );
static void bsw_bswm_cs_st_MainFuncMidOut( void );

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
static void bsw_bswm_cs_st_SetTxStatEnable( void );
#endif

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
static void bsw_bswm_cs_st_CheckRam( void );
#endif

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
BswU2    bsw_bswm_cs_st_u2CSStatus;     /* BSWM/CS state      */
BswU1    bsw_bswm_cs_st_u1Clock;        /* Clock supply log */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_Init                                      */
/* Description   | Initialize CS                                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_CS_Init                             */
/****************************************************************************/
void
bsw_bswm_cs_st_Init( void )
{
    bsw_bswm_cs_st_u2CSStatus = BSW_BSWM_CS_u2PVTST_UNINIT;

#if ( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
    BswM_VPS_InitCS();
#endif

    bsw_bswm_cs_st_InitIpduGrVct();
    bsw_bswm_cs_sysst_Init();
    bsw_bswm_cs_ctrl_Init();

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_Init();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthInit();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinInit();
#endif

    ComM_Init( NULL_PTR );
    bsw_bswm_cs_user_CbkWkupSrcInd();
    Nm_Init();

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    Com_Init( NULL_PTR );
    bsw_bswm_cs_st_SetTxStatEnable();
#endif
#if ( BSW_BSWM_CS_FUNC_LDCOM == BSW_USE )
    LdCom_Init( NULL_PTR );
#endif

#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
    bsw_bswm_cs_st_XcpInit();
#endif

#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
    IpduM_Init( NULL_PTR );
#endif

#if ( BSW_BSWM_CS_FUNC_PDUR == BSW_USE )
    PduR_Init( NULL_PTR );
#endif

    /* The clock input timing is always notified at reset startup */
    bsw_bswm_cs_user_CbkProvClkInit();
    bsw_bswm_cs_st_u1Clock = BSW_BSWM_CS_u1CLOCKPROV_ON;

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
        BswM_Can_InitDriver();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
        bsw_bswm_cs_st_BswMEthInitDrv();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
        bsw_bswm_cs_st_BswMLinInitDrv();
#endif
    bsw_bswm_cs_st_u2CSStatus = BSW_BSWM_CS_u2PVTST_RUN;
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_PrepareDeInit                             */
/* Description   | CS Prepare for shutdown                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_CS_PrepareDeInit                    */
/****************************************************************************/
void
bsw_bswm_cs_st_PrepareDeInit( void )
{
    bsw_bswm_cs_st_u2CSStatus = BSW_BSWM_CS_u2PVTST_UNINIT;

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_PrepareDeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthPreDeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinPreDeInit();
#endif

    ComM_DeInit();
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    Com_DeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_LDCOM == BSW_USE )
    LdCom_DeInit();
#endif
    Nm_DeInit();
#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
    bsw_bswm_cs_st_XcpDeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
    IpduM_DeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_PDUR == BSW_USE )
    PduR_DeInit();
#endif

#if ( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
    BswM_VPS_DeInitCS();
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_DeInit                                    */
/* Description   | CS Shutdown                                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_CS_DeInit                           */
/****************************************************************************/
void
bsw_bswm_cs_st_DeInit( void )
{
    bsw_bswm_cs_st_u2CSStatus = BSW_BSWM_CS_u2PVTST_UNINIT;

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_DeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthDeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinDeInit();
#endif

    ComM_DeInit();
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    Com_DeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_LDCOM == BSW_USE )
    LdCom_DeInit();
#endif
    Nm_DeInit();
#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
    bsw_bswm_cs_st_XcpDeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
    IpduM_DeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_PDUR == BSW_USE )
    PduR_DeInit();
#endif

#if ( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
    BswM_VPS_DeInitCS();
#endif
}

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_Wakeup                                    */
/* Description   | CS Wake-up initialization                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_CS_Wakeup                           */
/****************************************************************************/
void
bsw_bswm_cs_st_Wakeup( void )
{
    bsw_bswm_cs_st_u2CSStatus = BSW_BSWM_CS_u2PVTST_UNINIT;

    bsw_bswm_cs_user_CbkPreWakeup();

#if ( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
    BswM_VPS_WakeupCS();
#endif

    bsw_bswm_cs_st_InitIpduGrVct();
    bsw_bswm_cs_sysst_Wakeup();
    bsw_bswm_cs_ctrl_Init();

    /* If BswM_CS_RequestProvideClock() is called before bsw_bswm_cs_st_NotifyPrvClkWkup() is called, */
    /* "bsw_bswm_cs_st_u1Clock" is turned on and can request a clock input.                           */
    bsw_bswm_cs_st_u1Clock = BSW_BSWM_CS_u1CLOCKPROV_OFF;
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_Wakeup();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthWakeup();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinWakeup();
#endif

    ComM_Init( NULL_PTR );
    bsw_bswm_cs_user_CbkWkupSrcInd();
    Nm_Init();

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    Com_Wakeup( NULL_PTR );
    bsw_bswm_cs_st_SetTxStatEnable();
#endif
#if ( BSW_BSWM_CS_FUNC_LDCOM == BSW_USE )
    LdCom_Init( NULL_PTR );
#endif
#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
    bsw_bswm_cs_st_XcpInit();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
    IpduM_Init( NULL_PTR );
#endif
#if ( BSW_BSWM_CS_FUNC_PDUR == BSW_USE )
    PduR_Init( NULL_PTR );
#endif

    bsw_bswm_cs_st_NotifyPrvClkWkup( BSW_BSWM_CS_u1TMGTYP_WAKEUP );

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
        BswM_Can_InitDriver();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
        bsw_bswm_cs_st_BswMEthInitDrv();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
        bsw_bswm_cs_st_BswMLinInitDrv();
#endif

    bsw_bswm_cs_st_u2CSStatus = BSW_BSWM_CS_u2PVTST_RUN;

}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_Sleep                                     */
/* Description   | CS Sleep                                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_CS_Sleep                            */
/****************************************************************************/
void
bsw_bswm_cs_st_Sleep( void )
{
    bsw_bswm_cs_st_u2CSStatus = BSW_BSWM_CS_u2PVTST_UNINIT;

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_Sleep();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthSleep();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinSleep();
#endif

    ComM_DeInit();
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    Com_Sleep();
#endif
#if ( BSW_BSWM_CS_FUNC_LDCOM == BSW_USE )
    LdCom_DeInit();
#endif
    Nm_DeInit();
#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
    bsw_bswm_cs_st_XcpDeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
    IpduM_DeInit();
#endif
#if ( BSW_BSWM_CS_FUNC_PDUR == BSW_USE )
    PduR_DeInit();
#endif

    bsw_bswm_cs_user_CbkPostSleep();
}
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_Reset                                     */
/* Description   | CS Reset                                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Supported API : BswM_CS_Reset                            */
/****************************************************************************/
void
bsw_bswm_cs_st_Reset( void )
{
    bsw_bswm_cs_st_u2CSStatus = BSW_BSWM_CS_u2PVTST_UNINIT;

#if ( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
    BswM_VPS_InitCS();
#endif

    bsw_bswm_cs_st_InitIpduGrVct();
    bsw_bswm_cs_sysst_Init();
    bsw_bswm_cs_ctrl_Init();

#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_Reset();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthReset();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinReset();
#endif

    ComM_Init( NULL_PTR );
    bsw_bswm_cs_user_CbkWkupSrcInd();
    Nm_Init();

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    Com_Reset( NULL_PTR );
    bsw_bswm_cs_st_SetTxStatEnable();
#endif
#if ( BSW_BSWM_CS_FUNC_LDCOM == BSW_USE )
    LdCom_Init( NULL_PTR );
#endif
#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
    bsw_bswm_cs_st_XcpInit();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
    IpduM_Init( NULL_PTR );
#endif
#if ( BSW_BSWM_CS_FUNC_PDUR == BSW_USE )
    PduR_Init( NULL_PTR );
#endif

    /* The clock input timing is always notified at reset */
    bsw_bswm_cs_user_CbkProvClkInit();
    bsw_bswm_cs_st_u1Clock = BSW_BSWM_CS_u1CLOCKPROV_ON;

    bsw_bswm_cs_st_u2CSStatus = BSW_BSWM_CS_u2PVTST_RUN;
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_MainFunctionHigh                          */
/* Description   | High-priority periodic processing                        */
/* Preconditions | When processing high-priority periodic process           */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_MainFunctionHigh                 */
/****************************************************************************/
void
bsw_bswm_cs_st_MainFunctionHigh( void )
{
    BswU2 u2CSStat;

    u2CSStat = bsw_bswm_cs_st_u2CSStatus;
    if( u2CSStat == BSW_BSWM_CS_u2PVTST_RUN )
    {
        bsw_bswm_cs_user_CbkPreMFuncHi();

        /********         Input part         ********/
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
        BswM_Can_MainFunctionHighIn();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
        bsw_bswm_cs_st_BswMEthMainHI();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
        bsw_bswm_cs_st_BswMLinMainHI();
#endif

        /********         Control part         ********/
#if ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_HIGH )
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
#if ( BSW_BSWM_CS_MUX_MA_PTN == BSW_BSWM_CS_MUX_MA_MSG )
        IpduM_MainFunctionRx();
#endif
#endif
#if ( BSW_BSWM_CS_FUNC_SECOC == BSW_USE )
        bsw_bswm_cs_user_CbkSecMFuncRx();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
#if ( BSW_BSWM_CS_MUX_MA_PTN != BSW_BSWM_CS_MUX_MA_MSG )
        IpduM_MainFunctionRx();
#endif
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
        BswM_Can_MainFunctionPreComRx();
#endif
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
        Com_MainFunctionRx();
#endif
        bsw_bswm_cs_user_CbkAppMainFunc();
#if ( BSW_BSWM_CS_FUNC_DCM ==  BSW_USE )
        bsw_bswm_cs_user_CbkDcmMainFunc();
#endif

#endif    /* ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_HIGH ) */

#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthMainHC();
#endif

#if ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_HIGH )
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
        Com_MainFunctionTx();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
        BswM_Can_MainFunctionPostComTx();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
#if ( BSW_BSWM_CS_MUX_MA_PTN != BSW_BSWM_CS_MUX_MA_MSG )
        IpduM_MainFunctionTx();
#endif
#endif
#if ( BSW_BSWM_CS_FUNC_SECOC == BSW_USE )
        bsw_bswm_cs_user_CbkSecMFuncTx();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
#if ( BSW_BSWM_CS_MUX_MA_PTN == BSW_BSWM_CS_MUX_MA_MSG )
        IpduM_MainFunctionTx();
#endif
#endif
#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
        bsw_bswm_cs_st_XcpMainFunction();
#endif
#endif    /* ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_HIGH ) */

        /********         Output part         ********/
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
        BswM_Can_MainFunctionHighOut();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
        bsw_bswm_cs_st_BswMEthMainHO();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
        bsw_bswm_cs_st_BswMLinMainHO();
#endif
        bsw_bswm_cs_user_CbkPostMFuncHi();
    }
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_MainFunctionMid                           */
/* Description   | Medium-priority processing                               */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_MainFunctionMiddle               */
/****************************************************************************/
void
bsw_bswm_cs_st_MainFunctionMid( void )
{
    BswU2 u2CSStat;

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
    /* Check RAM corruption */
    bsw_bswm_cs_st_CheckRam();
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */

    /* Since the system shuts down immediately when checking for RAM corruption, the CS status is got at this timing */
    u2CSStat = bsw_bswm_cs_st_u2CSStatus;

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
    if( u2CSStat == BSW_BSWM_CS_u2PVTST_FATAL )
    {
        bsw_bswm_cs_st_DeInit();
        bsw_bswm_cs_user_CbkDetectFail();
    }
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */

    if( u2CSStat == BSW_BSWM_CS_u2PVTST_RUN )
    {
        /* Notification before medium-priority periodic processing */
        bsw_bswm_cs_user_CbkPreMFuncMid();

        /******** Input part ********/
        bsw_bswm_cs_st_MainFuncMidIn();

        /******** Control part ********/
        bsw_bswm_cs_st_MainFuncMidCtrl();

        /******** Output part ********/
        bsw_bswm_cs_st_MainFuncMidOut();

        /* Notification after medium-priority periodic processing */
        bsw_bswm_cs_user_CbkPostMFuncMd();
    }
}

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_DetectFail                                */
/* Description   | Processing when a failure is detected                    */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | Supported API : BswM_CS_DetectFail                       */
/****************************************************************************/
void
bsw_bswm_cs_st_DetectFail( void )
{
    bsw_bswm_cs_st_u2CSStatus = BSW_BSWM_CS_u2PVTST_FATAL;
}
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_ChkU2Dat                                  */
/* Description   | Check RAM corruption (2-byte data)                       */
/* Preconditions | None                                                     */
/* Parameters    | u2Val  Value of the check target                         */
/*               |   (The target is data where the upper and lower levels   */
/*               |    are mirrors.)                                         */
/* Return Value  | Check result                                             */
/*               | BSW_BSWM_CS_u1RESULT_OK : Normal                         */
/*               | BSW_BSWM_CS_u1RESULT_NG : failure                        */
/* Notes         | Function to check that the upper and lower level         */
/*               | are mirrors                                              */
/****************************************************************************/
BswU1
bsw_bswm_cs_st_ChkU2Dat( BswU2 u2Val )
{
    BswU1  u1Ret;
    BswU2  u2TmpHi;
    BswU2  u2TmpLo;
    BswU2  u2TmpSum;

    u1Ret = (BswU1)BSW_BSWM_CS_u1RESULT_OK;

    u2TmpHi  = u2Val >> BSW_BSWM_CS_u2SHIFT_B8;
    u2TmpLo  = u2Val &  BSW_BSWM_CS_u2VERIFY_KEY_B8;

    /* The upper bits are masked to account for the case where the value to be checked is sign-extended when the upper bits are shifted */
    u2TmpSum = (u2TmpHi + u2TmpLo) & BSW_BSWM_CS_u2VERIFY_KEY_B8;
    if( u2TmpSum != BSW_BSWM_CS_u2VERIFY_KEY_B8 )
    {
        u1Ret = (BswU1)BSW_BSWM_CS_u1RESULT_NG;
    }

    return u1Ret;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_InitIpduGrVct                             */
/* Description   | Initialize I-PDU Group Vector                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_bswm_cs_st_InitIpduGrVct( void )
{
    BswU1   u1Index;
    BswU1   u1IpduGrpVectSize;
    BswU2   u2PwVectIndex;
#if ( BSW_BSWM_CS_FUNC_PNCIPDU == BSW_USE )
    BswU2   u2PncVectIndex;
#endif

    u2PwVectIndex = (BswU2)0U;
    u1IpduGrpVectSize = bsw_bswm_cs_st_u1IpduGrpVctSz;
#if ( BSW_BSWM_CS_FUNC_PNCIPDU == BSW_USE )
    u2PncVectIndex = (BswU2)0U;
#endif

    for( u1Index = (BswU1)0U; u1Index < u1IpduGrpVectSize; u1Index++ )
    {
        bsw_bswm_cs_st_u4IpduGrpVect[u2PwVectIndex + (BswU2)BSW_BSWM_CS_u1INDEX_0] = (BswU4)BSW_BSWM_CS_SYSSTAT_NONE;
        bsw_bswm_cs_st_u4IpduGrpVect[u2PwVectIndex + (BswU2)BSW_BSWM_CS_u1INDEX_1] = (BswU4)BSW_BSWM_CS_SYSSTAT_NONE;
        bsw_bswm_cs_st_u4DmIpduGrpVect[u2PwVectIndex + (BswU2)BSW_BSWM_CS_u1INDEX_0] = (BswU4)BSW_BSWM_CS_SYSSTAT_NONE;
        bsw_bswm_cs_st_u4DmIpduGrpVect[u2PwVectIndex + (BswU2)BSW_BSWM_CS_u1INDEX_1] = (BswU4)BSW_BSWM_CS_SYSSTAT_NONE;
        bsw_bswm_cs_st_u4WkupIpduGrVct[u2PwVectIndex + (BswU2)BSW_BSWM_CS_u1INDEX_0] = (BswU4)BSW_BSWM_CS_SYSSTAT_NONE;
        bsw_bswm_cs_st_u4WkupIpduGrVct[u2PwVectIndex + (BswU2)BSW_BSWM_CS_u1INDEX_1] = (BswU4)BSW_BSWM_CS_SYSSTAT_NONE;
        u2PwVectIndex += (BswU2)BSW_BSWM_CS_SYSSTATTBLNUM;

#if ( BSW_BSWM_CS_FUNC_PNCIPDU == BSW_USE )
        bsw_bswm_cs_st_u4PncIpduGrpVect[u2PncVectIndex + BSW_BSWM_CS_u2PNCVECT_INDEX0] = BSW_BSWM_CS_u4PNCSTAT_NONE;
        bsw_bswm_cs_st_u4PncIpduGrpVect[u2PncVectIndex + BSW_BSWM_CS_u2PNCVECT_INDEX1] = BSW_BSWM_CS_u4PNCSTAT_NONE;

        bsw_bswm_cs_st_u4PncDmIpduGrVct[u2PncVectIndex + BSW_BSWM_CS_u2PNCVECT_INDEX0] = BSW_BSWM_CS_u4PNCSTAT_NONE;
        bsw_bswm_cs_st_u4PncDmIpduGrVct[u2PncVectIndex + BSW_BSWM_CS_u2PNCVECT_INDEX1] = BSW_BSWM_CS_u4PNCSTAT_NONE;

        bsw_bswm_cs_st_u4PncTxStatusVct[u2PncVectIndex + BSW_BSWM_CS_u2PNCVECT_INDEX0] = BSW_BSWM_CS_u4PNCSTAT_NONE;
        bsw_bswm_cs_st_u4PncTxStatusVct[u2PncVectIndex + BSW_BSWM_CS_u2PNCVECT_INDEX1] = BSW_BSWM_CS_u4PNCSTAT_NONE;

        u2PncVectIndex += (BswU2)BSW_BSWM_CS_PNC_REQNUM;
#endif
    }
}

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_SetTxStatEnable                           */
/* Description   | Judge Event/periodic transmission enable/disable         */
/*               | (When PDU transmission control is not used)              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_bswm_cs_st_SetTxStatEnable( void )
{
    BswU1               u1Channel;
    BswU1               u1ChannelMax;

    u1ChannelMax = bsw_bswm_cs_ctrl_u1ChNum;
    for( u1Channel = (BswU1)0U; u1Channel < u1ChannelMax; u1Channel++ )
    {
        if(bsw_bswm_cs_ctrl_u1PduTxCtrlUse[u1Channel] != (BswU1)BSW_USE )
        {
            /* When the PDU transmission control function is not used, the periodic timer shall be reset */
            Com_ResetPeriodicTx( u1Channel, (BswU1)COM_RSTR_RESUMETX, BSW_BSWM_CS_u2OFFSETTIME_NONE );

            /* When the PDU transmission control function is not used, event/periodic transmission is permitted */
            Com_SetTxStatus( u1Channel, (Com_TxStatusType)(COM_EVENT_TX_ENABLE|COM_PERIODIC_TX_ENABLE) );
        }
    }
}
#endif

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_CheckRam                                  */
/* Description   | Check for RAM corruption in CS packages                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static void
bsw_bswm_cs_st_CheckRam( void )
{
    BswU2 u2CSStat;
    BswU1 u1RamChk;

#if ( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
    BswM_VPS_CheckRam();
#endif

    /* Check RAM corruption for BswM/CS */
    /* CS state RAM corruption check */
    u2CSStat = bsw_bswm_cs_st_u2CSStatus;
    u1RamChk = bsw_bswm_cs_st_ChkU2Dat( u2CSStat );
    if( u1RamChk == BSW_BSWM_CS_u1RESULT_NG )
    {
        bsw_bswm_cs_st_DetectFail();
    }

    /* System state RAM corruption check */
    bsw_bswm_cs_sysst_ChkSysStatRam();

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#if ( BSW_COM_EVENTWAKEUPFRAME_USE == BSW_USE )
    /* Check for event wake-up function RAM corruption */
    bsw_bswm_cs_ctrl_ChkEvWkupRam();
#endif
#endif

    /* Check RAM corruption for communication protocol(CAN,LIN,ETH only) */
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_CheckRam();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthCheckRam();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinCheckRam();
#endif

    /* RAM corruption check for common component */
    ComM_CheckRam();
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    Com_CheckRam();
#endif
}
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_MainFuncMidIn                             */
/* Description   | Medium-priority input processing                         */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | NONE                                                     */
/****************************************************************************/
static void
bsw_bswm_cs_st_MainFuncMidIn( void )
{
    /* Processing the input for each protocol */
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_MainFunctionMidIn();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthMainMI();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinMainMI();
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_MainFuncMidCtrl                           */
/* Description   | Medium-priority control processing                       */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | NONE                                                     */
/****************************************************************************/
static void
bsw_bswm_cs_st_MainFuncMidCtrl( void )
{
#if ( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
    BswM_VPS_MainFunctionCS();
#endif

    /* Power status confirmed */
    bsw_bswm_cs_sysst_UpdtSysStat();

    /* Update the channel bus awake factor */
    ComM_UpdateChannelBusAwake();

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
    /* Clock supply timing control */
    bsw_bswm_cs_st_CtrlPrvClkTiming();
#endif
        /* Initialize driver */
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_InitDriver();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthInitDrv();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinInitDrv();
#endif

    /* Control I-PDU for each protocol */
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_UpdateIPDUStatus();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthUpdIPDUSt();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinUpdIPDUSt();
#endif

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    /* I-PDU control request */
    Com_IpduGroupControl( bsw_bswm_cs_st_u4IpduGrpVect );
    Com_SetWakeupMask( bsw_bswm_cs_st_u4WkupIpduGrVct );
    Com_ReceptionDMControl( bsw_bswm_cs_st_u4DmIpduGrpVect );
#endif

#if ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_MIDDLE )
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
#if ( BSW_BSWM_CS_MUX_MA_PTN == BSW_BSWM_CS_MUX_MA_MSG )
    IpduM_MainFunctionRx();
#endif
#endif
#if ( BSW_BSWM_CS_FUNC_SECOC == BSW_USE )
    bsw_bswm_cs_user_CbkSecMFuncRx();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
#if ( BSW_BSWM_CS_MUX_MA_PTN != BSW_BSWM_CS_MUX_MA_MSG )
    IpduM_MainFunctionRx();
#endif
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_MainFunctionPreComRx();
#endif
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    Com_MainFunctionRx();
#endif
    /* Notify app update timing */
    bsw_bswm_cs_user_CbkAppMainFunc();
#if ( BSW_BSWM_CS_FUNC_DCM ==  BSW_USE )
    /* Notify diag periodic processing timing */
    bsw_bswm_cs_user_CbkDcmMainFunc();
#endif
#endif /* ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_MIDDLE ) */

    /* Determine EIRA */
    ComM_MainFunctionEira();

    /* Notify user Awake collection timing */
    bsw_bswm_cs_user_CbkSetBusAwake();

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#if ( BSW_COM_EVENTAWAKE_USE == BSW_USE )
    /* Count the event awake maintain time */
    bsw_bswm_cs_ctrl_CntEvtAwTimer();
#endif
#if ( BSW_COM_EVENTWAKEUPFRAME_USE == BSW_USE )
    /* Count event transmission waiting time */
    bsw_bswm_cs_ctrl_CntEvtTxDlyTmr();
#endif
#endif

    /* Channel/NW Control */
    Nm_MainFunction();
    ComM_MainFunction();

    /* Control channels/networks for each protocol */
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_MainFunctionMidCtrl();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthMainMC();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinMainMC();
#endif

#if ( BSW_BSWM_CS_FUNC_PNCIPDU == BSW_USE )
    bsw_bswm_cs_st_UpdPncIpduStat();
#endif
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_MainFuncMidOut                            */
/* Description   | Medium-priority output processing                        */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | NONE                                                     */
/* Return Value  | NONE                                                     */
/* Notes         | NONE                                                     */
/****************************************************************************/
static void
bsw_bswm_cs_st_MainFuncMidOut( void )
{
#if ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_MIDDLE )
#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
    Com_MainFunctionTx();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_MainFunctionPostComTx();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
#if ( BSW_BSWM_CS_MUX_MA_PTN != BSW_BSWM_CS_MUX_MA_MSG )
    IpduM_MainFunctionTx();
#endif
#endif
#if ( BSW_BSWM_CS_FUNC_SECOC == BSW_USE )
    bsw_bswm_cs_user_CbkSecMFuncTx();
#endif
#if ( BSW_BSWM_CS_FUNC_IPDUM == BSW_USE )
#if ( BSW_BSWM_CS_MUX_MA_PTN == BSW_BSWM_CS_MUX_MA_MSG )
    IpduM_MainFunctionTx();
#endif
#endif
#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )
    bsw_bswm_cs_st_XcpMainFunction();
#endif
#endif /* ( BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_MIDDLE )*/

    /* Processing the output for each protocol */
#if ( BSW_BSWM_CS_FUNC_BSWMCAN == BSW_USE )
    BswM_Can_MainFunctionMidOut();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
    bsw_bswm_cs_st_BswMEthMainMO();
#endif
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
    bsw_bswm_cs_st_BswMLinMainMO();
#endif
}

#endif /* ( BSW_BSWM_CS_FUNC_BSWMCS == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-0-1          :2018/02/01                                             */
/*  v1-1-0          :2019/01/16                                             */
/*  v2-0-0          :2021/12/08                                             */
/*  v2-1-0          :2022/10/31                                             */
/*  v2-2-0          :2023/05/08                                             */
/*  v3-0-0          :2025/02/03                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
