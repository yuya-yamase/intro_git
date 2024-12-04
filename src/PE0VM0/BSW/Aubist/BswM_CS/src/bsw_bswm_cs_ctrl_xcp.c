/* bsw_bswm_cs_ctrl_xcp_c_v2-0-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/CTRL/XCP/CODE                                 */
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
#if ( BSW_BSWM_CS_FUNC_XCP == BSW_USE )

#include <../Xcp/inc/bswc_xcp_memmap.h>
#include <Xcp.h>
#include "../inc/bsw_bswm_cs_ctrl_xcp.h"

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
/* Function Name | bsw_bswm_cs_ctrl_XcpDrive                                */
/* Description   | Drive XCP channel                                        */
/* Preconditions | None                                                     */
/* Parameters    | NetworkHandleType Network: Channel                       */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_XcpDrive( NetworkHandleType Network )
{
    Xcp_Drive( Network );
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_XcpSuspend                              */
/* Description   | Stop XCP channel                                         */
/* Preconditions | None                                                     */
/* Parameters    | NetworkHandleType Network: Channel                       */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_XcpSuspend( NetworkHandleType Network )
{
    Xcp_Suspend( Network );
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_XcpClearTxReq                           */
/* Description   | Clear XCP transmission request                           */
/* Preconditions | None                                                     */
/* Parameters    | NetworkHandleType Network: Channel                       */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_XcpClearTxReq( NetworkHandleType Network )
{
    Xcp_ClearTxReq( Network );
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_ctrl_XcpSetTrnsMode                          */
/* Description   | Control XCP transmit channel                             */
/* Preconditions | None                                                     */
/* Parameters    | NetworkHandleType Network: Channel                       */
/*               | BswU1 u1TxMode           : Transmit mode                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_ctrl_XcpSetTrnsMode( NetworkHandleType Network, BswU1 u1TxMode )
{
    if( u1TxMode == (BswU1)BSW_BSWM_CS_XCPMODE_ON )
    {
        Xcp_SetTransmissionMode( Network, (Xcp_TransmissionModeType)XCP_TX_ON );
    }
    else
    {
        Xcp_SetTransmissionMode( Network, (Xcp_TransmissionModeType)XCP_TX_OFF );
    }
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* ( BSW_BSWM_CS_FUNC_XCP == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/01/18                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
