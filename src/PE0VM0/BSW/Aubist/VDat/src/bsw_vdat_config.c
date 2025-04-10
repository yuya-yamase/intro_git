/* bsw_vdat_config_c_v3-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VDAT/CONFIG/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_vdat_MemMap.h"

#include <bsw_vdat.h>
#include "../cfg/VDat_Cfg.h"
#include "../inc/bsw_vdat_config.h"

#if ( BSW_VDAT_CFG_FUNC_VDAT == BSW_VDAT_USE )

#include "../inc/bsw_vdat_trx.h"
#include "../inc/bsw_vdat_ipc.h"
#include "../inc/bsw_vdat_vcc.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Ipc Function Pointer */
#if (BSW_VDAT_IPC_FUNC == BSW_VDAT_USE)
#define BSW_VDAT_IPC_INITNODE_FUNC      (&bsw_vdat_ipc_InitNode)
#define BSW_VDAT_IPC_STARTNODE_FUNC     (&bsw_vdat_ipc_StartNode)
#define BSW_VDAT_IPC_RECEIVE_FUNC       (&bsw_vdat_ipc_Receive)
#define BSW_VDAT_IPC_TRANSMIT_FUNC      (&bsw_vdat_ipc_Transmit)
#define BSW_VDAT_IPC_DEINITNODE_FUNC    (&bsw_vdat_ipc_DeInitNode)
#else
#define BSW_VDAT_IPC_INITNODE_FUNC      (&bsw_vdat_trx_InitNodeNone)
#define BSW_VDAT_IPC_STARTNODE_FUNC     (&bsw_vdat_trx_StartNodeNone)
#define BSW_VDAT_IPC_RECEIVE_FUNC       (&bsw_vdat_trx_ReceiveNone)
#define BSW_VDAT_IPC_TRANSMIT_FUNC      (&bsw_vdat_trx_TransmitNone)
#define BSW_VDAT_IPC_DEINITNODE_FUNC    (&bsw_vdat_trx_DeInitNodeNone)
#endif

/* VCC Function Pointer */
#if (BSW_VDAT_VCC_FUNC == BSW_VDAT_USE)
#define BSW_VDAT_VCC_INITNODE_FUNC      (&bsw_vdat_vcc_InitNode)
#define BSW_VDAT_VCC_STARTNODE_FUNC     (&bsw_vdat_vcc_StartNode)
#define BSW_VDAT_VCC_RECEIVE_FUNC       (&bsw_vdat_vcc_Receive)
#define BSW_VDAT_VCC_TRANSMIT_FUNC      (&bsw_vdat_vcc_Transmit)
#define BSW_VDAT_VCC_DEINITNODE_FUNC    (&bsw_vdat_vcc_DeInitNode)
#else
#define BSW_VDAT_VCC_INITNODE_FUNC      (&bsw_vdat_trx_InitNodeNone)
#define BSW_VDAT_VCC_STARTNODE_FUNC     (&bsw_vdat_trx_StartNodeNone)
#define BSW_VDAT_VCC_RECEIVE_FUNC       (&bsw_vdat_trx_ReceiveNone)
#define BSW_VDAT_VCC_TRANSMIT_FUNC      (&bsw_vdat_trx_TransmitNone)
#define BSW_VDAT_VCC_DEINITNODE_FUNC    (&bsw_vdat_trx_DeInitNodeNone)
#endif

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
/* Number of Connections */
BswConst BswU1 bsw_vdat_trx_u1ConnectionNum = (BswU1)BSW_VDAT_CFG_CONNECTION_NUM;

/* Number of Nodes per Connection */
BswConst BswU1 bsw_vdat_trx_u1NodeNum[ BSW_VDAT_CFG_CONNECTION_NUM ] =
{
    (BswU1)BSW_VDAT_CFG_NODE_NUM00
#if (BSW_VDAT_CFG_CONNECTION_NUM > 1U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM01
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 2U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM02
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 3U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM03
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 4U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM04
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 5U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM05
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 6U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM06
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 7U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM07
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 8U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM08
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 9U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM09
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 10U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM10
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 11U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM11
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 12U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM12
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 13U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM13
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 14U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM14
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 15U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM15
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 16U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM16
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 17U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM17
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 18U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM18
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 19U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM19
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 20U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM20
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 21U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM21
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 22U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM22
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 23U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM23
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 24U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM24
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 25U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM25
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 26U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM26
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 27U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM27
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 28U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM28
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 29U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM29
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 30U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM30
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 31U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM31
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 32U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM32
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 33U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM33
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 34U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM34
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 35U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM35
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 36U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM36
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 37U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM37
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 38U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM38
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 39U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM39
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 40U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM40
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 41U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM41
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 42U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM42
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 43U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM43
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 44U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM44
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 45U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM45
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 46U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM46
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 47U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM47
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 48U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM48
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 49U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM49
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 50U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM50
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 51U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM51
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 52U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM52
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 53U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM53
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 54U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM54
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 55U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM55
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 56U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM56
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 57U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM57
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 58U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM58
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 59U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM59
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 60U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM60
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 61U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM61
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 62U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM62
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 63U)
   ,(BswU1)BSW_VDAT_CFG_NODE_NUM63
#endif
};

/* Inter-processor Communication */
BswConst BswU1 bsw_vdat_trx_u1ComFunc[ BSW_VDAT_CFG_CONNECTION_NUM ] =
{
    (BswU1)BSW_VDAT_CFG_COM_FUNC00
#if (BSW_VDAT_CFG_CONNECTION_NUM > 1U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC01
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 2U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC02
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 3U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC03
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 4U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC04
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 5U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC05
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 6U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC06
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 7U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC07
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 8U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC08
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 9U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC09
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 10U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC10
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 11U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC11
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 12U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC12
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 13U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC13
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 14U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC14
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 15U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC15
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 16U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC16
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 17U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC17
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 18U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC18
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 19U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC19
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 20U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC20
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 21U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC21
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 22U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC22
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 23U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC23
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 24U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC24
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 25U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC25
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 26U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC26
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 27U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC27
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 28U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC28
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 29U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC29
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 30U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC30
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 31U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC31
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 32U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC32
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 33U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC33
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 34U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC34
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 35U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC35
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 36U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC36
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 37U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC37
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 38U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC38
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 39U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC39
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 40U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC40
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 41U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC41
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 42U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC42
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 43U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC43
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 44U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC44
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 45U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC45
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 46U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC46
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 47U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC47
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 48U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC48
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 49U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC49
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 50U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC50
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 51U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC51
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 52U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC52
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 53U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC53
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 54U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC54
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 55U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC55
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 56U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC56
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 57U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC57
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 58U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC58
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 59U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC59
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 60U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC60
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 61U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC61
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 62U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC62
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 63U)
   ,(BswU1)BSW_VDAT_CFG_COM_FUNC63
#endif
};

#if ( BSW_VDAT_IPC_FUNC == BSW_VDAT_USE )
/* Kind of Inter-processor Communication */
BswConst BswU1 bsw_vdat_trx_u1IpcBusId[ BSW_VDAT_CFG_CONNECTION_NUM ] =
{
    (BswU1)BSW_VDAT_CFG_IPC_BUSID00
#if (BSW_VDAT_CFG_CONNECTION_NUM > 1U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID01
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 2U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID02
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 3U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID03
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 4U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID04
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 5U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID05
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 6U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID06
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 7U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID07
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 8U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID08
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 9U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID09
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 10U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID10
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 11U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID11
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 12U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID12
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 13U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID13
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 14U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID14
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 15U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID15
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 16U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID16
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 17U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID17
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 18U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID18
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 19U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID19
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 20U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID20
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 21U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID21
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 22U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID22
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 23U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID23
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 24U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID24
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 25U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID25
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 26U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID26
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 27U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID27
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 28U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID28
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 29U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID29
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 30U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID30
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 31U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID31
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 32U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID32
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 33U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID33
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 34U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID34
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 35U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID35
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 36U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID36
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 37U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID37
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 38U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID38
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 39U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID39
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 40U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID40
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 41U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID41
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 42U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID42
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 43U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID43
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 44U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID44
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 45U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID45
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 46U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID46
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 47U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID47
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 48U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID48
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 49U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID49
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 50U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID50
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 51U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID51
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 52U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID52
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 53U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID53
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 54U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID54
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 55U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID55
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 56U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID56
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 57U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID57
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 58U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID58
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 59U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID59
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 60U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID60
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 61U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID61
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 62U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID62
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 63U)
   ,(BswU1)BSW_VDAT_CFG_IPC_BUSID63
#endif
};
#endif /* BSW_VDAT_IPC_FUNC == BSW_VDAT_USE */

/* Queue ID Pointer */
BswConst BswU4 * BswConst bsw_vdat_trx_u4QueueIDTbl[ BSW_VDAT_CFG_CONNECTION_NUM ] = 
{
    &(bsw_vdat_u4QueueIDTbl_00[0])
#if (BSW_VDAT_CFG_CONNECTION_NUM > 1U)
   ,&(bsw_vdat_u4QueueIDTbl_01[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 2U)
   ,&(bsw_vdat_u4QueueIDTbl_02[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 3U)
   ,&(bsw_vdat_u4QueueIDTbl_03[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 4U)
   ,&(bsw_vdat_u4QueueIDTbl_04[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 5U)
   ,&(bsw_vdat_u4QueueIDTbl_05[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 6U)
   ,&(bsw_vdat_u4QueueIDTbl_06[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 7U)
   ,&(bsw_vdat_u4QueueIDTbl_07[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 8U)
   ,&(bsw_vdat_u4QueueIDTbl_08[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 9U)
   ,&(bsw_vdat_u4QueueIDTbl_09[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 10U)
   ,&(bsw_vdat_u4QueueIDTbl_10[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 11U)
   ,&(bsw_vdat_u4QueueIDTbl_11[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 12U)
   ,&(bsw_vdat_u4QueueIDTbl_12[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 13U)
   ,&(bsw_vdat_u4QueueIDTbl_13[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 14U)
   ,&(bsw_vdat_u4QueueIDTbl_14[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 15U)
   ,&(bsw_vdat_u4QueueIDTbl_15[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 16U)
   ,&(bsw_vdat_u4QueueIDTbl_16[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 17U)
   ,&(bsw_vdat_u4QueueIDTbl_17[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 18U)
   ,&(bsw_vdat_u4QueueIDTbl_18[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 19U)
   ,&(bsw_vdat_u4QueueIDTbl_19[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 20U)
   ,&(bsw_vdat_u4QueueIDTbl_20[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 21U)
   ,&(bsw_vdat_u4QueueIDTbl_21[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 22U)
   ,&(bsw_vdat_u4QueueIDTbl_22[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 23U)
   ,&(bsw_vdat_u4QueueIDTbl_23[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 24U)
   ,&(bsw_vdat_u4QueueIDTbl_24[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 25U)
   ,&(bsw_vdat_u4QueueIDTbl_25[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 26U)
   ,&(bsw_vdat_u4QueueIDTbl_26[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 27U)
   ,&(bsw_vdat_u4QueueIDTbl_27[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 28U)
   ,&(bsw_vdat_u4QueueIDTbl_28[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 29U)
   ,&(bsw_vdat_u4QueueIDTbl_29[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 30U)
   ,&(bsw_vdat_u4QueueIDTbl_30[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 31U)
   ,&(bsw_vdat_u4QueueIDTbl_31[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 32U)
   ,&(bsw_vdat_u4QueueIDTbl_32[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 33U)
   ,&(bsw_vdat_u4QueueIDTbl_33[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 34U)
   ,&(bsw_vdat_u4QueueIDTbl_34[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 35U)
   ,&(bsw_vdat_u4QueueIDTbl_35[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 36U)
   ,&(bsw_vdat_u4QueueIDTbl_36[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 37U)
   ,&(bsw_vdat_u4QueueIDTbl_37[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 38U)
   ,&(bsw_vdat_u4QueueIDTbl_38[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 39U)
   ,&(bsw_vdat_u4QueueIDTbl_39[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 40U)
   ,&(bsw_vdat_u4QueueIDTbl_40[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 41U)
   ,&(bsw_vdat_u4QueueIDTbl_41[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 42U)
   ,&(bsw_vdat_u4QueueIDTbl_42[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 43U)
   ,&(bsw_vdat_u4QueueIDTbl_43[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 44U)
   ,&(bsw_vdat_u4QueueIDTbl_44[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 45U)
   ,&(bsw_vdat_u4QueueIDTbl_45[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 46U)
   ,&(bsw_vdat_u4QueueIDTbl_46[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 47U)
   ,&(bsw_vdat_u4QueueIDTbl_47[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 48U)
   ,&(bsw_vdat_u4QueueIDTbl_48[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 49U)
   ,&(bsw_vdat_u4QueueIDTbl_49[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 50U)
   ,&(bsw_vdat_u4QueueIDTbl_50[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 51U)
   ,&(bsw_vdat_u4QueueIDTbl_51[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 52U)
   ,&(bsw_vdat_u4QueueIDTbl_52[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 53U)
   ,&(bsw_vdat_u4QueueIDTbl_53[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 54U)
   ,&(bsw_vdat_u4QueueIDTbl_54[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 55U)
   ,&(bsw_vdat_u4QueueIDTbl_55[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 56U)
   ,&(bsw_vdat_u4QueueIDTbl_56[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 57U)
   ,&(bsw_vdat_u4QueueIDTbl_57[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 58U)
   ,&(bsw_vdat_u4QueueIDTbl_58[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 59U)
   ,&(bsw_vdat_u4QueueIDTbl_59[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 60U)
   ,&(bsw_vdat_u4QueueIDTbl_60[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 61U)
   ,&(bsw_vdat_u4QueueIDTbl_61[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 62U)
   ,&(bsw_vdat_u4QueueIDTbl_62[0])
#endif
#if (BSW_VDAT_CFG_CONNECTION_NUM > 63U)
   ,&(bsw_vdat_u4QueueIDTbl_63[0])
#endif
};

/* Function Pointer */
BswConst Bsw_VDat_FuncTblType bsw_vdat_trx_stFuncTbl[BSW_VDAT_FUNC_TBL_NUM] =
{
    /* Ipc */
    {
        BSW_VDAT_IPC_INITNODE_FUNC,
        BSW_VDAT_IPC_STARTNODE_FUNC,
        BSW_VDAT_IPC_RECEIVE_FUNC,
        BSW_VDAT_IPC_TRANSMIT_FUNC,
        BSW_VDAT_IPC_DEINITNODE_FUNC
    },
    /* VCC */
    {
        BSW_VDAT_VCC_INITNODE_FUNC,
        BSW_VDAT_VCC_STARTNODE_FUNC,
        BSW_VDAT_VCC_RECEIVE_FUNC,
        BSW_VDAT_VCC_TRANSMIT_FUNC,
        BSW_VDAT_VCC_DEINITNODE_FUNC
    }
};

/* Definition to prevent deletion by optimization (Posix) */
BswConst Bsw_VDat_InitNodePubType    bsw_vdat_InitNodePubFunc    = &bsw_vdat_InitNode;
BswConst Bsw_VDat_StartNodePubType   bsw_vdat_StartNodePubFunc   = &bsw_vdat_StartNode;
BswConst Bsw_VDat_ReceivePubType     bsw_vdat_ReceivePubFunc     = &bsw_vdat_Receive;
BswConst Bsw_VDat_TransmitPubType    bsw_vdat_TransmitPubFunc    = &bsw_vdat_Transmit;
BswConst Bsw_VDat_DeInitNodePubType  bsw_vdat_DeInitNodePubFunc  = &bsw_vdat_DeInitNode;

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* BSW_VDAT_CFG_FUNC_VDAT == BSW_VDAT_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/04/08                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
