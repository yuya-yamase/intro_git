/* bsw_bswm_cs_status_bswmeth_c_v3-0-0                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/STATUS/BSWMETH/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <cs/bsw_cs_common.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../inc/bsw_bswm_cs_config.h"
#if ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_USE )
#include "../../BswM_Eth/inc/bsw_bswm_eth_MemMap.h"
#include <bswm_eth/bsw_bswm_eth.h>
#include "../inc/bsw_bswm_cs_status_bswmeth.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthInit                               */
/* Description   | Initialize Ethernet                                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthInit( void )
{
    BswM_Eth_Init();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthInitDrv                            */
/* Description   | Ethernet Initialize driver                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthInitDrv( void )
{
    BswM_Eth_InitDriver();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthPreDeInit                          */
/* Description   | Ethernet Prepare for shutdown                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthPreDeInit( void )
{
    BswM_Eth_PrepareDeInit();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthDeInit                             */
/* Description   | Ethernet Shutdown                                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthDeInit( void )
{
    BswM_Eth_DeInit();
}

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthWakeup                             */
/* Description   | Ethernet Wake-up initialization                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthWakeup( void )
{
    BswM_Eth_Wakeup();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthSleep                              */
/* Description   | Ethernet Sleep                                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthSleep( void )
{
    BswM_Eth_Sleep();
}
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthReset                              */
/* Description   | Ethernet Reset                                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthReset( void )
{
    BswM_Eth_Reset();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthMainHI                             */
/* Description   | Ethernet High-priority periodic processing - Input       */
/* Preconditions | When processing high-priority periodic process           */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthMainHI( void )
{
    BswM_Eth_MainFunctionHighIn();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthMainHC                             */
/* Description   | Ethernet High Priority Control                           */
/* Preconditions | When processing high-priority periodic process           */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthMainHC( void )
{
    BswM_Eth_MainFunctionHighCtrl();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthMainHO                             */
/* Description   | Ethernet High-priority periodic processing - Output      */
/* Preconditions | When processing high-priority periodic process           */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthMainHO( void )
{
    BswM_Eth_MainFunctionHighOut();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthMainMI                             */
/* Description   | Ethernet Medium-priority periodic processing - Input     */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthMainMI( void )
{
    BswM_Eth_MainFunctionMidIn();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthMainMC                             */
/* Description   | Ethernet Medium Priority Control                         */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthMainMC( void )
{
    BswM_Eth_MainFunctionMidCtrl();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthMainMO                             */
/* Description   | Ethernet Medium-priority periodic processing - Output    */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthMainMO( void )
{
    BswM_Eth_MainFunctionMidOut();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthUpdIPDUSt                          */
/* Description   | Request Ethernet I-PDU group update                      */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthUpdIPDUSt( void )
{
    BswM_Eth_UpdateIPDUStatus();
}

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMEthCheckRam                           */
/* Description   | Check for RAM corruption in Ethernet-related components  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMEthCheckRam( void )
{
    BswM_Eth_CheckRam();
}
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* ( BSW_BSWM_CS_FUNC_BSWMETH == BSW_NOUSE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2018/12/12                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-1-0          :2023/01/26                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
