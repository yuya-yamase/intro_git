/* bsw_cannm_a_config_c_v3-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/CONFIG/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../../inc/bsw_cannm_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../../ComM/inc/bsw_comm_config.h"
#include "../../../BswM_CS/inc/bsw_bswm_cs_config.h"
#if( BSW_BSWM_CS_FUNC_CANNM == BSW_USE )

#include <cannm/bsw_cannm.h>
#include "../../inc/bsw_cannm_config.h"
#if ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE )

#include <canif/bsw_canif.h>
#include <nm/bsw_nm.h>
#include <nm/bsw_nm_cbk.h>

#include "../../inc/a/bsw_cannm_a_nmcfgtbl.h"
#include "../../inc/a/bsw_cannm_a_nm.h"
#include "../../inc/a/bsw_cannm_a_config_sys.h"

#include "../../../Nm/inc/bsw_nm_config.h"
#include "../../cfg/a/CanNm_A_Cfg.h"

#if( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#include "../../../Com/inc/bsw_com_config.h"
#endif

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define BSW_CANNM_A_DIRECT                      (3U)   /* CanNmA function available (must be defined with a value different from BSW_NOUSE)  */
#define BSW_CANNM_A_CAN_CH_NUM                  (BSW_COMM_BUS_TYPE_CHNUM(CAN))

#if (BSW_BSWM_CS_MSG_DELIVER == BSW_BSWM_CS_MSGDELIVER_HIGH)
#define BSW_CANNM_A_u2MS2COMTICK_RUP(msTime)    BSW_BSWM_CS_u2MS2TICK_RUP_HIGH(msTime)
#else
#define BSW_CANNM_A_u2MS2COMTICK_RUP(msTime)    BSW_BSWM_CS_u2MS2TICK_RUP_MID(msTime)
#endif

/* Node ID setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH0             (BSW_CANNM_A_CFG_NODEID_0)  /* CH0 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH1             (BSW_CANNM_A_CFG_NODEID_1)  /* CH1 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH2             (BSW_CANNM_A_CFG_NODEID_2)  /* CH2 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH3             (BSW_CANNM_A_CFG_NODEID_3)  /* CH3 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH4             (BSW_CANNM_A_CFG_NODEID_4)  /* CH4 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH5             (BSW_CANNM_A_CFG_NODEID_5)  /* CH5 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH6             (BSW_CANNM_A_CFG_NODEID_6)  /* CH6 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH7             (BSW_CANNM_A_CFG_NODEID_7)  /* CH7 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH8             (BSW_CANNM_A_CFG_NODEID_8)  /* CH8 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH9             (BSW_CANNM_A_CFG_NODEID_9)  /* CH9 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH10            (BSW_CANNM_A_CFG_NODEID_10) /* CH10 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH11            (BSW_CANNM_A_CFG_NODEID_11) /* CH11 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH12            (BSW_CANNM_A_CFG_NODEID_12) /* CH12 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH13            (BSW_CANNM_A_CFG_NODEID_13) /* CH13 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH14            (BSW_CANNM_A_CFG_NODEID_14) /* CH14 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH15            (BSW_CANNM_A_CFG_NODEID_15) /* CH15 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH16            (BSW_CANNM_A_CFG_NODEID_16) /* CH16 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH17            (BSW_CANNM_A_CFG_NODEID_17) /* CH17 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH18            (BSW_CANNM_A_CFG_NODEID_18) /* CH18 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH19            (BSW_CANNM_A_CFG_NODEID_19) /* CH19 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH20            (BSW_CANNM_A_CFG_NODEID_20) /* CH20 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH21            (BSW_CANNM_A_CFG_NODEID_21) /* CH21 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH22            (BSW_CANNM_A_CFG_NODEID_22) /* CH22 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH23            (BSW_CANNM_A_CFG_NODEID_23) /* CH23 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH24            (BSW_CANNM_A_CFG_NODEID_24) /* CH24 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH25            (BSW_CANNM_A_CFG_NODEID_25) /* CH25 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH26            (BSW_CANNM_A_CFG_NODEID_26) /* CH26 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH27            (BSW_CANNM_A_CFG_NODEID_27) /* CH27 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH28            (BSW_CANNM_A_CFG_NODEID_28) /* CH28 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH29            (BSW_CANNM_A_CFG_NODEID_29) /* CH29 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH30            (BSW_CANNM_A_CFG_NODEID_30) /* CH30 Node ID Setting */
#define BSW_CANNM_A_OWN_NODE_ID_CH31            (BSW_CANNM_A_CFG_NODEID_31) /* CH31 Node ID Setting */

/* CanNmA Use/NoUse setting */
#if      ( BSW_CANNM_NM_TYPE(0) == BSW_CANNM_NMTYPE_A )             /* CH0 NOUSE / NMDIRECT         */
#define BSW_CANNM_A_FUNCTION_CH0                (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH0                     (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH0                (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH0                     (0U)
#endif
#if      ( BSW_CANNM_NM_TYPE(1) == BSW_CANNM_NMTYPE_A )             /* CH1 NOUSE / NMDIRECT         */
#define BSW_CANNM_A_FUNCTION_CH1                (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH1                     (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH1                (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH1                     (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(2) == BSW_CANNM_NMTYPE_A  )           /* CH2 NOUSE / NMDIRECT         */
#define BSW_CANNM_A_FUNCTION_CH2                (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH2                     (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH2                (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH2                     (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(3) == BSW_CANNM_NMTYPE_A  )           /* CH3 NOUSE / NMDIRECT         */
#define BSW_CANNM_A_FUNCTION_CH3                (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH3                     (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH3                (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH3                     (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(4) == BSW_CANNM_NMTYPE_A  )           /* CH4 NOUSE / NMDIRECT         */
#define BSW_CANNM_A_FUNCTION_CH4                (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH4                     (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH4                (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH4                     (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(5) == BSW_CANNM_NMTYPE_A  )           /* CH5 NOUSE / NMDIRECT         */
#define BSW_CANNM_A_FUNCTION_CH5                (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH5                     (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH5                (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH5                     (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(6) == BSW_CANNM_NMTYPE_A  )           /* CH6 NOUSE / NMDIRECT         */
#define BSW_CANNM_A_FUNCTION_CH6                (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH6                     (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH6                (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH6                     (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(7) == BSW_CANNM_NMTYPE_A  )           /* CH7 NOUSE / NMDIRECT         */
#define BSW_CANNM_A_FUNCTION_CH7                (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH7                     (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH7                (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH7                     (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(8) == BSW_CANNM_NMTYPE_A  )           /* CH8 NOUSE / NMDIRECT         */
#define BSW_CANNM_A_FUNCTION_CH8                (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH8                     (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH8                (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH8                     (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(9) == BSW_CANNM_NMTYPE_A  )           /* CH9 NOUSE / NMDIRECT         */
#define BSW_CANNM_A_FUNCTION_CH9                (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH9                     (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH9                (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH9                     (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(10) == BSW_CANNM_NMTYPE_A  )           /* CH10 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH10               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH10                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH10               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH10                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(11) == BSW_CANNM_NMTYPE_A  )           /* CH11 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH11               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH11                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH11               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH11                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(12) == BSW_CANNM_NMTYPE_A  )           /* CH12 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH12               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH12                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH12               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH12                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(13) == BSW_CANNM_NMTYPE_A  )           /* CH13 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH13               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH13                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH13               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH13                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(14) == BSW_CANNM_NMTYPE_A  )           /* CH14 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH14               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH14                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH14               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH14                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(15) == BSW_CANNM_NMTYPE_A  )           /* CH15 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH15               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH15                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH15               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH15                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(16) == BSW_CANNM_NMTYPE_A  )           /* CH16 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH16               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH16                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH16               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH16                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(17) == BSW_CANNM_NMTYPE_A  )           /* CH17 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH17               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH17                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH17               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH17                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(18) == BSW_CANNM_NMTYPE_A  )           /* CH18 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH18               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH18                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH18               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH18                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(19) == BSW_CANNM_NMTYPE_A  )           /* CH19 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH19               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH19                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH19               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH19                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(20) == BSW_CANNM_NMTYPE_A  )           /* CH20 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH20               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH20                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH20               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH20                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(21) == BSW_CANNM_NMTYPE_A  )           /* CH21 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH21               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH21                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH21               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH21                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(22) == BSW_CANNM_NMTYPE_A  )           /* CH22 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH22               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH22                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH22               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH22                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(23) == BSW_CANNM_NMTYPE_A  )           /* CH23 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH23               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH23                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH23               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH23                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(24) == BSW_CANNM_NMTYPE_A  )           /* CH24 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH24               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH24                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH24               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH24                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(25) == BSW_CANNM_NMTYPE_A  )           /* CH25 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH25               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH25                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH25               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH25                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(26) == BSW_CANNM_NMTYPE_A  )           /* CH26 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH26               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH26                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH26               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH26                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(27) == BSW_CANNM_NMTYPE_A  )           /* CH27 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH27               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH27                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH27               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH27                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(28) == BSW_CANNM_NMTYPE_A  )           /* CH28 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH28               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH28                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH28               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH28                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(29) == BSW_CANNM_NMTYPE_A  )           /* CH29 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH29               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH29                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH29               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH29                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(30) == BSW_CANNM_NMTYPE_A  )           /* CH30 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH30               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH30                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH30               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH30                    (0U)
#endif
#if      (  BSW_CANNM_NM_TYPE(31) == BSW_CANNM_NMTYPE_A  )           /* CH31 NOUSE / NMDIRECT        */
#define BSW_CANNM_A_FUNCTION_CH31               (BSW_CANNM_A_DIRECT)  /* CanNmA is implemented on the channel   */
#define BSW_CANNM_A_USE_CH31                    (1U)
#else
#define BSW_CANNM_A_FUNCTION_CH31               (BSW_NOUSE)           /* CanNmA is not implemented in the channel */
#define BSW_CANNM_A_USE_CH31                    (0U)
#endif

/* Number of channels that implement CanNmA */
#define BSW_CANNM_A_COMMON_MAXCH    (BSW_CANNM_A_COMMON_MAXCH_0_15 + BSW_CANNM_A_COMMON_MAXCH_16_31)
#define BSW_CANNM_A_COMMON_MAXCH_0_15 \
    ( BSW_CANNM_A_USE_CH0  \
    + BSW_CANNM_A_USE_CH1  \
    + BSW_CANNM_A_USE_CH2  \
    + BSW_CANNM_A_USE_CH3  \
    + BSW_CANNM_A_USE_CH4  \
    + BSW_CANNM_A_USE_CH5  \
    + BSW_CANNM_A_USE_CH6  \
    + BSW_CANNM_A_USE_CH7  \
    + BSW_CANNM_A_USE_CH8  \
    + BSW_CANNM_A_USE_CH9  \
    + BSW_CANNM_A_USE_CH10 \
    + BSW_CANNM_A_USE_CH11 \
    + BSW_CANNM_A_USE_CH12 \
    + BSW_CANNM_A_USE_CH13 \
    + BSW_CANNM_A_USE_CH14 \
    + BSW_CANNM_A_USE_CH15)
#define BSW_CANNM_A_COMMON_MAXCH_16_31 \
    ( BSW_CANNM_A_USE_CH16 \
    + BSW_CANNM_A_USE_CH17 \
    + BSW_CANNM_A_USE_CH18 \
    + BSW_CANNM_A_USE_CH19 \
    + BSW_CANNM_A_USE_CH20 \
    + BSW_CANNM_A_USE_CH21 \
    + BSW_CANNM_A_USE_CH22 \
    + BSW_CANNM_A_USE_CH23 \
    + BSW_CANNM_A_USE_CH24 \
    + BSW_CANNM_A_USE_CH25 \
    + BSW_CANNM_A_USE_CH26 \
    + BSW_CANNM_A_USE_CH27 \
    + BSW_CANNM_A_USE_CH28 \
    + BSW_CANNM_A_USE_CH29 \
    + BSW_CANNM_A_USE_CH30 \
    + BSW_CANNM_A_USE_CH31)

/* Enable/disable use of immediate bus wake-up transmit offset */
#define BSW_CANNM_A_IMMWU_OFST_USE_CH0         ((BSW_CANNM_A_CFG_IMM_TXOFFSET_0 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH1         ((BSW_CANNM_A_CFG_IMM_TXOFFSET_1 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH2         ((BSW_CANNM_A_CFG_IMM_TXOFFSET_2 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH3         ((BSW_CANNM_A_CFG_IMM_TXOFFSET_3 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH4         ((BSW_CANNM_A_CFG_IMM_TXOFFSET_4 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH5         ((BSW_CANNM_A_CFG_IMM_TXOFFSET_5 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH6         ((BSW_CANNM_A_CFG_IMM_TXOFFSET_6 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH7         ((BSW_CANNM_A_CFG_IMM_TXOFFSET_7 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH8         ((BSW_CANNM_A_CFG_IMM_TXOFFSET_8 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH9         ((BSW_CANNM_A_CFG_IMM_TXOFFSET_9 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH10        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_10 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH11        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_11 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH12        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_12 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH13        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_13 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH14        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_14 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH15        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_15 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH16        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_16 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH17        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_17 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH18        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_18 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH19        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_19 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH20        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_20 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH21        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_21 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH22        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_22 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH23        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_23 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH24        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_24 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH25        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_25 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH26        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_26 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH27        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_27 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH28        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_28 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH29        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_29 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH30        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_30 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)
#define BSW_CANNM_A_IMMWU_OFST_USE_CH31        ((BSW_CANNM_A_CFG_IMM_TXOFFSET_31 == BSW_CANNM_A_IMMTXOFFSET_NONE) ? BSW_NOUSE : BSW_USE)

/* Support for all channels and CanNmA implemented channel */
#define BSW_CANNM_A_USE_CHNUM_0_0                   (BSW_CANNM_A_USE_CH0)

#define BSW_CANNM_A_USE_CHNUM_0_1                   (BSW_CANNM_A_USE_CHNUM_0_0 + BSW_CANNM_A_USE_CH1)
#define BSW_CANNM_A_USE_CHNUM_0_2                   (BSW_CANNM_A_USE_CHNUM_0_1 + BSW_CANNM_A_USE_CH2)
#define BSW_CANNM_A_USE_CHNUM_0_3                   (BSW_CANNM_A_USE_CHNUM_0_2 + BSW_CANNM_A_USE_CH3)
#define BSW_CANNM_A_USE_CHNUM_0_4                   (BSW_CANNM_A_USE_CHNUM_0_3 + BSW_CANNM_A_USE_CH4)
#define BSW_CANNM_A_USE_CHNUM_0_5                   (BSW_CANNM_A_USE_CHNUM_0_4 + BSW_CANNM_A_USE_CH5)
#define BSW_CANNM_A_USE_CHNUM_0_6                   (BSW_CANNM_A_USE_CHNUM_0_5 + BSW_CANNM_A_USE_CH6)
#define BSW_CANNM_A_USE_CHNUM_0_7                   (BSW_CANNM_A_USE_CHNUM_0_6 + BSW_CANNM_A_USE_CH7)
#define BSW_CANNM_A_USE_CHNUM_0_8                   (BSW_CANNM_A_USE_CHNUM_0_7 + BSW_CANNM_A_USE_CH8)
#define BSW_CANNM_A_USE_CHNUM_0_9                   (BSW_CANNM_A_USE_CHNUM_0_8 + BSW_CANNM_A_USE_CH9)
#define BSW_CANNM_A_USE_CHNUM_0_10                  (BSW_CANNM_A_USE_CHNUM_0_9 + BSW_CANNM_A_USE_CH10)
#define BSW_CANNM_A_USE_CHNUM_0_11                  (BSW_CANNM_A_USE_CHNUM_0_10 + BSW_CANNM_A_USE_CH11)
#define BSW_CANNM_A_USE_CHNUM_0_12                  (BSW_CANNM_A_USE_CHNUM_0_11 + BSW_CANNM_A_USE_CH12)
#define BSW_CANNM_A_USE_CHNUM_0_13                  (BSW_CANNM_A_USE_CHNUM_0_12 + BSW_CANNM_A_USE_CH13)
#define BSW_CANNM_A_USE_CHNUM_0_14                  (BSW_CANNM_A_USE_CHNUM_0_13 + BSW_CANNM_A_USE_CH14)
#define BSW_CANNM_A_USE_CHNUM_0_15                  (BSW_CANNM_A_USE_CHNUM_0_14 + BSW_CANNM_A_USE_CH15)
#define BSW_CANNM_A_USE_CHNUM_0_16                  (BSW_CANNM_A_USE_CHNUM_0_15 + BSW_CANNM_A_USE_CH16)
#define BSW_CANNM_A_USE_CHNUM_0_17                  (BSW_CANNM_A_USE_CHNUM_0_16 + BSW_CANNM_A_USE_CH17)
#define BSW_CANNM_A_USE_CHNUM_0_18                  (BSW_CANNM_A_USE_CHNUM_0_17 + BSW_CANNM_A_USE_CH18)
#define BSW_CANNM_A_USE_CHNUM_0_19                  (BSW_CANNM_A_USE_CHNUM_0_18 + BSW_CANNM_A_USE_CH19)
#define BSW_CANNM_A_USE_CHNUM_0_20                  (BSW_CANNM_A_USE_CHNUM_0_19 + BSW_CANNM_A_USE_CH20)
#define BSW_CANNM_A_USE_CHNUM_0_21                  (BSW_CANNM_A_USE_CHNUM_0_20 + BSW_CANNM_A_USE_CH21)
#define BSW_CANNM_A_USE_CHNUM_0_22                  (BSW_CANNM_A_USE_CHNUM_0_21 + BSW_CANNM_A_USE_CH22)
#define BSW_CANNM_A_USE_CHNUM_0_23                  (BSW_CANNM_A_USE_CHNUM_0_22 + BSW_CANNM_A_USE_CH23)
#define BSW_CANNM_A_USE_CHNUM_0_24                  (BSW_CANNM_A_USE_CHNUM_0_23 + BSW_CANNM_A_USE_CH24)
#define BSW_CANNM_A_USE_CHNUM_0_25                  (BSW_CANNM_A_USE_CHNUM_0_24 + BSW_CANNM_A_USE_CH25)
#define BSW_CANNM_A_USE_CHNUM_0_26                  (BSW_CANNM_A_USE_CHNUM_0_25 + BSW_CANNM_A_USE_CH26)
#define BSW_CANNM_A_USE_CHNUM_0_27                  (BSW_CANNM_A_USE_CHNUM_0_26 + BSW_CANNM_A_USE_CH27)
#define BSW_CANNM_A_USE_CHNUM_0_28                  (BSW_CANNM_A_USE_CHNUM_0_27 + BSW_CANNM_A_USE_CH28)
#define BSW_CANNM_A_USE_CHNUM_0_29                  (BSW_CANNM_A_USE_CHNUM_0_28 + BSW_CANNM_A_USE_CH29)
#define BSW_CANNM_A_USE_CHNUM_0_30                  (BSW_CANNM_A_USE_CHNUM_0_29 + BSW_CANNM_A_USE_CH30)
#define BSW_CANNM_A_USE_CHNUM_0_31                  (BSW_CANNM_A_USE_CHNUM_0_30 + BSW_CANNM_A_USE_CH31)

#if ( BSW_CANNM_A_FUNCTION_CH0 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH0               (BSW_CANNM_A_USE_CHNUM_0_0 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH0              (0U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH0               (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH0              (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH1 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH1               (BSW_CANNM_A_USE_CHNUM_0_1 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH1              (1U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH1               (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH1              (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH2 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH2               (BSW_CANNM_A_USE_CHNUM_0_2 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH2              (2U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH2               (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH2              (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH3 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH3               (BSW_CANNM_A_USE_CHNUM_0_3 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH3              (3U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH3               (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH3              (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH4 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH4               (BSW_CANNM_A_USE_CHNUM_0_4 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH4              (4U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH4               (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH4              (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH5 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH5               (BSW_CANNM_A_USE_CHNUM_0_5 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH5              (5U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH5               (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH5              (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH6 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH6               (BSW_CANNM_A_USE_CHNUM_0_6 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH6              (6U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH6               (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH6              (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH7 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH7               (BSW_CANNM_A_USE_CHNUM_0_7 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH7              (7U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH7               (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH7              (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH8 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH8               (BSW_CANNM_A_USE_CHNUM_0_8 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH8              (8U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH8               (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH8              (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH9 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH9               (BSW_CANNM_A_USE_CHNUM_0_9 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH9              (9U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH9               (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH9              (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH10 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH10              (BSW_CANNM_A_USE_CHNUM_0_10 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH10             (10U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH10              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH10             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH11 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH11              (BSW_CANNM_A_USE_CHNUM_0_11 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH11             (11U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH11              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH11             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH12 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH12              (BSW_CANNM_A_USE_CHNUM_0_12 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH12             (12U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH12              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH12             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH13 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH13              (BSW_CANNM_A_USE_CHNUM_0_13 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH13             (13U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH13              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH13             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH14 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH14              (BSW_CANNM_A_USE_CHNUM_0_14 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH14             (14U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH14              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH14             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH15 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH15              (BSW_CANNM_A_USE_CHNUM_0_15 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH15             (15U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH15              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH15             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH16 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH16              (BSW_CANNM_A_USE_CHNUM_0_16 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH16             (16U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH16              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH16             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH17 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH17              (BSW_CANNM_A_USE_CHNUM_0_17 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH17             (17U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH17              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH17             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH18 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH18              (BSW_CANNM_A_USE_CHNUM_0_18 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH18             (18U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH18              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH18             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH19 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH19              (BSW_CANNM_A_USE_CHNUM_0_19 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH19             (19U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH19              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH19             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH20 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH20              (BSW_CANNM_A_USE_CHNUM_0_20 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH20             (20U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH20              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH20             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH21 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH21              (BSW_CANNM_A_USE_CHNUM_0_21 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH21             (21U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH21              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH21             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH22 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH22              (BSW_CANNM_A_USE_CHNUM_0_22 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH22             (22U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH22              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH22             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH23 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH23              (BSW_CANNM_A_USE_CHNUM_0_23 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH23             (23U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH23              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH23             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH24 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH24              (BSW_CANNM_A_USE_CHNUM_0_24 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH24             (24U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH24              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH24             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH25 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH25              (BSW_CANNM_A_USE_CHNUM_0_25 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH25             (25U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH25              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH25             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH26 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH26              (BSW_CANNM_A_USE_CHNUM_0_26 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH26             (26U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH26              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH26             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH27 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH27              (BSW_CANNM_A_USE_CHNUM_0_27 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH27             (27U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH27              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH27             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH28 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH28              (BSW_CANNM_A_USE_CHNUM_0_28 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH28             (28U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH28              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH28             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH29 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH29              (BSW_CANNM_A_USE_CHNUM_0_29 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH29             (29U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH29              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH29             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH30 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH30              (BSW_CANNM_A_USE_CHNUM_0_30 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH30             (30U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH30              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH30             (BSW_CANNM_A_NONECH)
#endif
#if ( BSW_CANNM_A_FUNCTION_CH31 == BSW_CANNM_A_DIRECT )
#define BSW_CANNM_A_CHNOINPUT_CH31              (BSW_CANNM_A_USE_CHNUM_0_31 - 1U)
#define BSW_CANNM_A_CHNOOUTPUT_CH31             (31U)
#else
#define BSW_CANNM_A_CHNOINPUT_CH31              (BSW_CANNM_A_NONECH)
#define BSW_CANNM_A_CHNOOUTPUT_CH31             (BSW_CANNM_A_NONECH)
#endif

/* Timer correction by drive period */
#define BSW_CANNM_A_SEND_START                  (300U)
#define BSW_CANNM_A_OSEK_TTYP                   (100U - BSW_BSWM_CS_TICKTIME_MID)
#define BSW_CANNM_A_OSEK_TMAX                   (260U - BSW_BSWM_CS_TICKTIME_MID)
#define BSW_CANNM_A_OSEK_TERROR                 (1000U)

/* TWUW timer switching */
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH0           (BSW_CANNM_A_CFG_TBWDISABLESND_0)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH1           (BSW_CANNM_A_CFG_TBWDISABLESND_1)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH2           (BSW_CANNM_A_CFG_TBWDISABLESND_2)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH3           (BSW_CANNM_A_CFG_TBWDISABLESND_3)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH4           (BSW_CANNM_A_CFG_TBWDISABLESND_4)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH5           (BSW_CANNM_A_CFG_TBWDISABLESND_5)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH6           (BSW_CANNM_A_CFG_TBWDISABLESND_6)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH7           (BSW_CANNM_A_CFG_TBWDISABLESND_7)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH8           (BSW_CANNM_A_CFG_TBWDISABLESND_8)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH9           (BSW_CANNM_A_CFG_TBWDISABLESND_9)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH10          (BSW_CANNM_A_CFG_TBWDISABLESND_10)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH11          (BSW_CANNM_A_CFG_TBWDISABLESND_11)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH12          (BSW_CANNM_A_CFG_TBWDISABLESND_12)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH13          (BSW_CANNM_A_CFG_TBWDISABLESND_13)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH14          (BSW_CANNM_A_CFG_TBWDISABLESND_14)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH15          (BSW_CANNM_A_CFG_TBWDISABLESND_15)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH16          (BSW_CANNM_A_CFG_TBWDISABLESND_16)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH17          (BSW_CANNM_A_CFG_TBWDISABLESND_17)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH18          (BSW_CANNM_A_CFG_TBWDISABLESND_18)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH19          (BSW_CANNM_A_CFG_TBWDISABLESND_19)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH20          (BSW_CANNM_A_CFG_TBWDISABLESND_20)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH21          (BSW_CANNM_A_CFG_TBWDISABLESND_21)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH22          (BSW_CANNM_A_CFG_TBWDISABLESND_22)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH23          (BSW_CANNM_A_CFG_TBWDISABLESND_23)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH24          (BSW_CANNM_A_CFG_TBWDISABLESND_24)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH25          (BSW_CANNM_A_CFG_TBWDISABLESND_25)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH26          (BSW_CANNM_A_CFG_TBWDISABLESND_26)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH27          (BSW_CANNM_A_CFG_TBWDISABLESND_27)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH28          (BSW_CANNM_A_CFG_TBWDISABLESND_28)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH29          (BSW_CANNM_A_CFG_TBWDISABLESND_29)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH30          (BSW_CANNM_A_CFG_TBWDISABLESND_30)
#define BSW_CANNM_A_CVT_WKUP_WAIT_CH31          (BSW_CANNM_A_CFG_TBWDISABLESND_31)

/* Switch the control message transmission enable timer */
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH0          (BSW_CANNM_A_CFG_ENABLEPRD_0)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH1          (BSW_CANNM_A_CFG_ENABLEPRD_1)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH2          (BSW_CANNM_A_CFG_ENABLEPRD_2)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH3          (BSW_CANNM_A_CFG_ENABLEPRD_3)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH4          (BSW_CANNM_A_CFG_ENABLEPRD_4)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH5          (BSW_CANNM_A_CFG_ENABLEPRD_5)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH6          (BSW_CANNM_A_CFG_ENABLEPRD_6)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH7          (BSW_CANNM_A_CFG_ENABLEPRD_7)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH8          (BSW_CANNM_A_CFG_ENABLEPRD_8)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH9          (BSW_CANNM_A_CFG_ENABLEPRD_9)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH10         (BSW_CANNM_A_CFG_ENABLEPRD_10)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH11         (BSW_CANNM_A_CFG_ENABLEPRD_11)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH12         (BSW_CANNM_A_CFG_ENABLEPRD_12)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH13         (BSW_CANNM_A_CFG_ENABLEPRD_13)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH14         (BSW_CANNM_A_CFG_ENABLEPRD_14)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH15         (BSW_CANNM_A_CFG_ENABLEPRD_15)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH16         (BSW_CANNM_A_CFG_ENABLEPRD_16)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH17         (BSW_CANNM_A_CFG_ENABLEPRD_17)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH18         (BSW_CANNM_A_CFG_ENABLEPRD_18)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH19         (BSW_CANNM_A_CFG_ENABLEPRD_19)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH20         (BSW_CANNM_A_CFG_ENABLEPRD_20)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH21         (BSW_CANNM_A_CFG_ENABLEPRD_21)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH22         (BSW_CANNM_A_CFG_ENABLEPRD_22)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH23         (BSW_CANNM_A_CFG_ENABLEPRD_23)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH24         (BSW_CANNM_A_CFG_ENABLEPRD_24)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH25         (BSW_CANNM_A_CFG_ENABLEPRD_25)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH26         (BSW_CANNM_A_CFG_ENABLEPRD_26)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH27         (BSW_CANNM_A_CFG_ENABLEPRD_27)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH28         (BSW_CANNM_A_CFG_ENABLEPRD_28)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH29         (BSW_CANNM_A_CFG_ENABLEPRD_29)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH30         (BSW_CANNM_A_CFG_ENABLEPRD_30)
#define BSW_CANNM_A_CVT_ENPRD_WAIT_CH31         (BSW_CANNM_A_CFG_ENABLEPRD_31)

/* Switch control message transmission permission timer during immediate bus wake-up */
#define BSW_CANNM_A_CVT_ENPRDIMM_CH0            (BSW_CANNM_A_CFG_IMM_TXOFFSET_0)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH1            (BSW_CANNM_A_CFG_IMM_TXOFFSET_1)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH2            (BSW_CANNM_A_CFG_IMM_TXOFFSET_2)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH3            (BSW_CANNM_A_CFG_IMM_TXOFFSET_3)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH4            (BSW_CANNM_A_CFG_IMM_TXOFFSET_4)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH5            (BSW_CANNM_A_CFG_IMM_TXOFFSET_5)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH6            (BSW_CANNM_A_CFG_IMM_TXOFFSET_6)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH7            (BSW_CANNM_A_CFG_IMM_TXOFFSET_7)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH8            (BSW_CANNM_A_CFG_IMM_TXOFFSET_8)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH9            (BSW_CANNM_A_CFG_IMM_TXOFFSET_9)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH10           (BSW_CANNM_A_CFG_IMM_TXOFFSET_10)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH11           (BSW_CANNM_A_CFG_IMM_TXOFFSET_11)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH12           (BSW_CANNM_A_CFG_IMM_TXOFFSET_12)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH13           (BSW_CANNM_A_CFG_IMM_TXOFFSET_13)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH14           (BSW_CANNM_A_CFG_IMM_TXOFFSET_14)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH15           (BSW_CANNM_A_CFG_IMM_TXOFFSET_15)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH16           (BSW_CANNM_A_CFG_IMM_TXOFFSET_16)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH17           (BSW_CANNM_A_CFG_IMM_TXOFFSET_17)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH18           (BSW_CANNM_A_CFG_IMM_TXOFFSET_18)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH19           (BSW_CANNM_A_CFG_IMM_TXOFFSET_19)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH20           (BSW_CANNM_A_CFG_IMM_TXOFFSET_20)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH21           (BSW_CANNM_A_CFG_IMM_TXOFFSET_21)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH22           (BSW_CANNM_A_CFG_IMM_TXOFFSET_22)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH23           (BSW_CANNM_A_CFG_IMM_TXOFFSET_23)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH24           (BSW_CANNM_A_CFG_IMM_TXOFFSET_24)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH25           (BSW_CANNM_A_CFG_IMM_TXOFFSET_25)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH26           (BSW_CANNM_A_CFG_IMM_TXOFFSET_26)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH27           (BSW_CANNM_A_CFG_IMM_TXOFFSET_27)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH28           (BSW_CANNM_A_CFG_IMM_TXOFFSET_28)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH29           (BSW_CANNM_A_CFG_IMM_TXOFFSET_29)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH30           (BSW_CANNM_A_CFG_IMM_TXOFFSET_30)
#define BSW_CANNM_A_CVT_ENPRDIMM_CH31           (BSW_CANNM_A_CFG_IMM_TXOFFSET_31)

/* Add Timer :Timer value 0 (Immediate timeout)*/
#define BSW_CANNM_A_u2NONETIMER_CHX             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 0U ))

/* CH0 */
#define BSW_CANNM_A_u2POWON_WAIT_CH0            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH0             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH0             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH0             (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH0 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH0           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH0 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH0          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH0 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH0            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH0               (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH0              (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH0             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH0             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH0           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH0             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH0          (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH0            (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH0            (4U)

/* CH1 */
#define BSW_CANNM_A_u2POWON_WAIT_CH1            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH1             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH1             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH1             (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH1 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH1           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH1 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH1          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH1 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH1            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH1               (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH1              (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH1             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH1             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH1           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH1             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH1          (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH1            (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH1            (4U)

/* CH2 */
#define BSW_CANNM_A_u2POWON_WAIT_CH2            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH2             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH2             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH2             (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH2 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH2           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH2 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH2          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH2 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH2            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH2               (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH2              (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH2             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH2             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH2           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH2             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH2          (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH2            (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH2            (4U)

/* CH3 */
#define BSW_CANNM_A_u2POWON_WAIT_CH3            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH3             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH3             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH3             (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH3 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH3           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH3 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH3          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH3 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH3            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH3               (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH3              (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH3             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH3             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH3           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH3             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH3          (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH3            (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH3            (4U)

/* CH4 */
#define BSW_CANNM_A_u2POWON_WAIT_CH4            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH4             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH4             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH4             (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH4 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH4           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH4 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH4          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH4 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH4            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH4               (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH4              (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH4             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH4             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH4           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH4             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH4          (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH4            (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH4            (4U)

/* CH5 */
#define BSW_CANNM_A_u2POWON_WAIT_CH5            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH5             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH5             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH5             (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH5 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH5           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH5 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH5          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH5 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH5            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH5               (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH5              (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH5             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH5             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH5           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH5             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH5          (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH5            (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH5            (4U)

/* CH6 */
#define BSW_CANNM_A_u2POWON_WAIT_CH6            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH6             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH6             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH6             (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH6 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH6           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH6 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH6          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH6 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH6            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH6               (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH6              (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH6             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH6             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH6           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH6             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH6          (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH6            (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH6            (4U)

/* CH7 */
#define BSW_CANNM_A_u2POWON_WAIT_CH7            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH7             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH7             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH7             (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH7 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH7           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH7 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH7          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH7 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH7            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH7               (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH7              (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH7             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH7             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH7           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH7             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH7          (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH7            (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH7            (4U)

/* CH8 */
#define BSW_CANNM_A_u2POWON_WAIT_CH8            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH8             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH8             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH8             (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH8 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH8           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH8 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH8          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH8 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH8            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH8               (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH8              (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH8             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH8             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH8           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH8             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH8          (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH8            (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH8            (4U)

/* CH9 */
#define BSW_CANNM_A_u2POWON_WAIT_CH9            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH9             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH9             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH9             (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH9 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH9           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH9 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH9          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH9 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH9            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH9               (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH9              (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH9             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH9             (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH9           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH9             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH9          (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH9            (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH9            (4U)

/* CH10 */
#define BSW_CANNM_A_u2POWON_WAIT_CH10           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH10            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH10            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH10            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH10 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH10          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH10 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH10         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH10 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH10           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH10              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH10             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH10            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH10            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH10          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH10            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH10         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH10           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH10           (4U)

/* CH11 */
#define BSW_CANNM_A_u2POWON_WAIT_CH11           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH11            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH11            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH11            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH11 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH11          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH11 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH11         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH11 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH11           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH11              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH11             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH11            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH11            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH11          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH11            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH11         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH11           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH11           (4U)

/* CH12 */
#define BSW_CANNM_A_u2POWON_WAIT_CH12           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH12            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH12            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH12            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH12 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH12          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH12 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH12         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH12 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH12           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH12              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH12             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH12            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH12            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH12          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH12            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH12         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH12           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH12           (4U)

/* CH13 */
#define BSW_CANNM_A_u2POWON_WAIT_CH13           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH13            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH13            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH13            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH13 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH13          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH13 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH13         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH13 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH13           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH13              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH13             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH13            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH13            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH13          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH13            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH13         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH13           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH13           (4U)

/* CH14 */
#define BSW_CANNM_A_u2POWON_WAIT_CH14           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH14            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH14            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH14            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH14 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH14          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH14 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH14         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH14 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH14           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH14              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH14             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH14            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH14            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH14          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH14            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH14         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH14           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH14           (4U)

/* CH15 */
#define BSW_CANNM_A_u2POWON_WAIT_CH15           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH15            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH15            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH15            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH15 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH15          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH15 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH15         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH15 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH15           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH15              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH15             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH15            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH15            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH15          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH15            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH15         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH15           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH15           (4U)

/* CH16 */
#define BSW_CANNM_A_u2POWON_WAIT_CH16           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH16            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH16            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH16            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH16 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH16          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH16 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH16         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH16 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH16           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH16              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH16             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH16            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH16            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH16          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH16            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH16         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH16           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH16           (4U)

/* CH17 */
#define BSW_CANNM_A_u2POWON_WAIT_CH17           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH17            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH17            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH17            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH17 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH17          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH17 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH17         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH17 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH17           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH17              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH17             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH17            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH17            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH17          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH17            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH17         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH17           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH17           (4U)

/* CH18 */
#define BSW_CANNM_A_u2POWON_WAIT_CH18           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH18            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH18            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH18            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH18 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH18          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH18 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH18         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH18 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH18           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH18              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH18             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH18            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH18            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH18          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH18            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH18         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH18           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH18           (4U)

/* CH19 */
#define BSW_CANNM_A_u2POWON_WAIT_CH19           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH19            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH19            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH19            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH19 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH19          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH19 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH19         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH19 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH19           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH19              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH19             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH19            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH19            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH19          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH19            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH19         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH19           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH19           (4U)

/* CH20 */
#define BSW_CANNM_A_u2POWON_WAIT_CH20           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH20            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH20            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH20            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH20 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH20          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH20 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH20         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH20 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH20           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH20              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH20             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH20            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH20            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH20          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH20            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH20         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH20           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH20           (4U)

/* CH21 */
#define BSW_CANNM_A_u2POWON_WAIT_CH21           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH21            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH21            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH21            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH21 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH21          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH21 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH21         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH21 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH21           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH21              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH21             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH21            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH21            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH21          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH21            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH21         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH21           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH21           (4U)

/* CH22 */
#define BSW_CANNM_A_u2POWON_WAIT_CH22           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH22            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH22            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH22            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH22 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH22          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH22 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH22         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH22 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH22           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH22              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH22             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH22            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH22            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH22          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH22            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH22         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH22           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH22           (4U)

/* CH23 */
#define BSW_CANNM_A_u2POWON_WAIT_CH23           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH23            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH23            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH23            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH23 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH23          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH23 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH23         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH23 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH23           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH23              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH23             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH23            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH23            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH23          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH23            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH23         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH23           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH23           (4U)

/* CH24 */
#define BSW_CANNM_A_u2POWON_WAIT_CH24           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH24            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH24            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH24            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH24 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH24          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH24 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH24         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH24 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH24           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH24              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH24             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH24            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH24            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH24          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH24            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH24         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH24           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH24           (4U)

/* CH25 */
#define BSW_CANNM_A_u2POWON_WAIT_CH25           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH25            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH25            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH25            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH25 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH25          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH25 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH25         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH25 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH25           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH25              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH25             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH25            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH25            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH25          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH25            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH25         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH25           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH25           (4U)

/* CH26 */
#define BSW_CANNM_A_u2POWON_WAIT_CH26           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH26            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH26            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH26            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH26 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH26          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH26 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH26         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH26 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH26           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH26              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH26             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH26            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH26            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH26          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH26            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH26         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH26           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH26           (4U)

/* CH27 */
#define BSW_CANNM_A_u2POWON_WAIT_CH27           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH27            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH27            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH27            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH27 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH27          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH27 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH27         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH27 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH27           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH27              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH27             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH27            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH27            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH27          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH27            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH27         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH27           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH27           (4U)

/* CH28 */
#define BSW_CANNM_A_u2POWON_WAIT_CH28           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH28            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH28            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH28            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH28 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH28          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH28 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH28         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH28 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH28           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH28              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH28             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH28            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH28            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH28          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH28            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH28         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH28           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH28           (4U)

/* CH29 */
#define BSW_CANNM_A_u2POWON_WAIT_CH29           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH29            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH29            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH29            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH29 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH29          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH29 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH29         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH29 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH29           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH29              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH29             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH29            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH29            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH29          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH29            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH29         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH29           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH29           (4U)

/* CH30 */
#define BSW_CANNM_A_u2POWON_WAIT_CH30           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH30            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH30            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH30            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH30 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH30          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH30 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH30         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH30 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH30           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH30              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH30             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH30            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH30            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH30          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH30            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH30         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH30           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH30           (4U)

/* CH31 */
#define BSW_CANNM_A_u2POWON_WAIT_CH31           (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_SEND_START ))
#define BSW_CANNM_A_u2POWON_SLP_CH31            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 3500U ))
#define BSW_CANNM_A_u2RUN_AWAKE_CH31            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 500U ))
#define BSW_CANNM_A_u2WKUP_WAIT_CH31            (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_WKUP_WAIT_CH31 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PERIODIC_WT_CH31          (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRD_WAIT_CH31 ) + (BswU2)1U)
#define BSW_CANNM_A_u2PRD_IMM_WAIT_CH31         (BSW_BSWM_CS_u2MS2TICK_RUP_MID( BSW_CANNM_A_CVT_ENPRDIMM_CH31 ))
#define BSW_CANNM_A_u2NOWUP_WAIT_CH31           (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_IMMWKUPTIME ))
#define BSW_CANNM_A_u2NONEDGE_CH31              (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_CVT_DIS_WKUP ))
#define BSW_CANNM_A_u2NRMSLPEG_CH31             (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1480U ))
#define BSW_CANNM_A_u2OSEK_TTYP_CH31            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TTYP ))
#define BSW_CANNM_A_u2OSEK_TMAX_CH31            (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TMAX ))
#define BSW_CANNM_A_u2OSEK_TERROR_CH31          (BSW_BSWM_CS_u2MILSEC2TICK_MID( BSW_CANNM_A_OSEK_TERROR ) + (BswU2)2U)
#define BSW_CANNM_A_u2OSEK_TWBS_CH31            (BSW_BSWM_CS_u2MILSEC2TICK_MID( 1500U ))
#define BSW_CANNM_A_u2OSEK_TERRWBS_CH31         (BSW_BSWM_CS_u2MILSEC2TICK_MID( 60000U ))

#define BSW_CANNM_A_OSEK_TXLIMIT_CH31           (8U)
#define BSW_CANNM_A_OSEK_RXLIMIT_CH31           (4U)

#define BSW_CANNM_A_ECUSPECNO_LBYTE_MSK         (0x00ffU)
#define BSW_CANNM_A_SHT8                        (8U)

#if( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#define BSW_CANNM_A_EVTWAKEUPFRAME_USE          (BSW_COM_EVENTWAKEUPFRAME_USE)
#else
#define BSW_CANNM_A_EVTWAKEUPFRAME_USE          (BSW_NOUSE)
#endif

#define BSW_CANNM_A_u2EVDISABLE_TIME            ((BswU2)10U)  /* Event transmission disable time */

#define BSW_CANNM_A_COM_CONTROL                 (BSW_NM_COM_CONTROL)

#if (BSW_CANNM_A_EVTWAKEUPFRAME_USE == BSW_USE)
#define BSW_CANNM_A_EVTWKUP_INIT_FUNC           (&bsw_cannm_a_ctrl_InitEvtWkup)
#define BSW_CANNM_A_EVTWKUP_CLR_FUNC            (&bsw_cannm_a_ctrl_ClrEvtWkupReq)
#define BSW_CANNM_A_EVTWKUP_TX_FUNC             (&bsw_cannm_a_ctrl_TxEvtWkupFr)
#define BSW_CANNM_A_EVTTXCONF_FUNC              (&bsw_nm_sw_EvtWkupTxConfirm)
#else
#define BSW_CANNM_A_EVTWKUP_INIT_FUNC           (&bsw_cannm_a_ctrl_InitEvtWkupNn)
#define BSW_CANNM_A_EVTWKUP_CLR_FUNC            (&bsw_cannm_a_ctrl_ClrEvWkupRqNn)
#define BSW_CANNM_A_EVTWKUP_TX_FUNC             (&bsw_cannm_a_ctrl_TxEvtWkupFrNn)
#define BSW_CANNM_A_EVTTXCONF_FUNC              (&bsw_cannm_a_ctrl_EvWkCnfNotInd)
#endif /* (BSW_CANNM_A_EVTWAKEUPFRAME_USE == BSW_USE) */

#if (BSW_CANNM_A_COM_CONTROL == BSW_USE)
#define BSW_CANNM_A_COMCTRL_INIT_FUNC           (&bsw_cannm_a_ctrl_InitComCtrl)
#define BSW_CANNM_A_COM_GETCOMSTS_FUNC          (&bsw_cannm_a_ctrl_GetComCtrlSts)
#else
#define BSW_CANNM_A_COMCTRL_INIT_FUNC           (&bsw_cannm_a_ctrl_InitComCtrlNn)
#define BSW_CANNM_A_COM_GETCOMSTS_FUNC          (&bsw_cannm_a_ctrl_GetCmCtrlStsNn)
#endif /* (BSW_CANNM_A_COM_CONTROL == BSW_USE) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* CONTOROL */
Bsw_CanNmA_STCtrlTableType   bsw_cannm_a_ctrl_stStsTbl[BSW_CANNM_A_COMMON_MAXCH];  /* CONTOROL control table */

#if (BSW_CANNM_A_EVTWAKEUPFRAME_USE == BSW_USE)
BswU1                      bsw_cannm_a_ctrl_u1EvtWkupReq[BSW_CANNM_A_COMMON_MAXCH];
#endif
#if (BSW_CANNM_A_COM_CONTROL == BSW_USE)
BswU1                      bsw_cannm_a_ctrl_u1ComCtrlReq[BSW_CANNM_A_COMMON_MAXCH];
#endif

/* CVT */
Bsw_CanNmA_STCvtTableType    bsw_cannm_a_cvtnm_stCtlTbl[BSW_CANNM_A_COMMON_MAXCH];  /* CVT control table */

/* OSEK */
static Bsw_CanNmA_STNmOsekRamDataType bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_COMMON_MAXCH];

/* TRANSPORT */
Bsw_CanNmA_STCanNmMsgSavType bsw_cannm_a_trans_stMsgSavBf[BSW_CANNM_A_COMMON_MAXCH];  /* Msg Storage buffer */
Bsw_CanNmA_STCanNmMsgQueType bsw_cannm_a_trans_stMsgQueue[BSW_CANNM_A_COMMON_MAXCH];  /* Msg Buffer for storage */

/* Timer management */
/* NM Timer management timer counter */
BswU2 bsw_cannm_a_timer_u2Time ;
BswU1 bsw_cannm_a_timer_u1RunAwake[BSW_CANNM_A_COMMON_MAXCH] ;  /* AWAKE holding waiting timer - Run state */
/* CVT timeout control table  (Number of channels * Timer (2)) Hold Priority by timer number is not considered */
Bsw_CanNmA_STTimerTableType bsw_cannm_a_timer_stTimerCvtT[BSW_CANNM_A_COMMON_MAXCH][BSW_CANNM_A_TIMER_CNT_TBL_SIZE] ;
/* OSEK timeout control table (Number of channels * Timer(1)) Priority by timer number is not considered */
Bsw_CanNmA_STTimerTableType bsw_cannm_a_timer_stTimerOsekT[BSW_CANNM_A_COMMON_MAXCH][BSW_CANNM_A_TIMER_CNT_TBL_SIZE] ;

/* Event */
/* CVT event queue (number of channels * number of events) Retained */
Bsw_CanNmA_STEventTableType bsw_cannm_a_event_stCvtQue[BSW_CANNM_A_COMMON_MAXCH][BSW_CANNM_A_EVT_QMAX] ;
/* OSEK event queue (number of channels * number of events) Retained */
Bsw_CanNmA_STEventTableType bsw_cannm_a_event_stOsekQue[BSW_CANNM_A_COMMON_MAXCH][BSW_CANNM_A_EVT_QMAX];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* Maximum number of channels */
BswConst BswU1 bsw_cannm_a_ctrl_u1MaxCh = (BswU1)BSW_CANNM_A_CAN_CH_NUM;

/* Channel offset */
BswConst BswU1  bsw_cannm_a_tbl_u1ChOffset   = (BswU1)BSW_COMM_BUS_TYPE_OFFSET(CAN);

/* Event transmission disable time */
BswConst BswU2  bsw_cannm_a_ctrl_u2DisableTime = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_CANNM_A_u2EVDISABLE_TIME);

/* Event wake-up frame transmission function */
void    (* BswConst bsw_cannm_a_ctrl_InitEvWkupFunc)( void ) = BSW_CANNM_A_EVTWKUP_INIT_FUNC;
void    (* BswConst bsw_cannm_a_ctrl_ClrEvWkReqFunc)( BswU1 u1NetID ) = BSW_CANNM_A_EVTWKUP_CLR_FUNC;
void    (* BswConst bsw_cannm_a_ctrl_TxEvWkReqFunc)( BswU1 u1NetID ) = BSW_CANNM_A_EVTWKUP_TX_FUNC;
void    (* BswConst bsw_cannm_a_ctrl_EvWkCnfIndFunc)( NetworkHandleType nmNetworkHandle, uint16 DisableTime ) = BSW_CANNM_A_EVTTXCONF_FUNC;

/* Communication restriction function */
void    (* BswConst bsw_cannm_a_ctrl_InitComFunc)( void ) = BSW_CANNM_A_COMCTRL_INIT_FUNC;
BswU1   (* BswConst bsw_cannm_a_ctrl_GetCmCtStsFunc)(  BswU1 u1CanNetID  ) = BSW_CANNM_A_COM_GETCOMSTS_FUNC;

/* Config TBL   */

/* CanNmA Set the number of component implementation channels */
BswConst    BswU1 bsw_cannm_a_ctrl_u1MaxChTbl = (BswU1)BSW_CANNM_A_COMMON_MAXCH;

/* CanNmA Set whether to use  component implementation channel in total */
#define BSW_CANNM_A_CH_USE_CH0        ((BSW_CANNM_A_FUNCTION_CH0  == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_NOUSE)
#define BSW_CANNM_A_CH_USE_CH0_1      ((BSW_CANNM_A_FUNCTION_CH1  == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0)
#define BSW_CANNM_A_CH_USE_CH0_2      ((BSW_CANNM_A_FUNCTION_CH2  == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_1)
#define BSW_CANNM_A_CH_USE_CH0_3      ((BSW_CANNM_A_FUNCTION_CH3  == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_2)
#define BSW_CANNM_A_CH_USE_CH0_4      ((BSW_CANNM_A_FUNCTION_CH4  == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_3)
#define BSW_CANNM_A_CH_USE_CH0_5      ((BSW_CANNM_A_FUNCTION_CH5  == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_4)
#define BSW_CANNM_A_CH_USE_CH0_6      ((BSW_CANNM_A_FUNCTION_CH6  == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_5)
#define BSW_CANNM_A_CH_USE_CH0_7      ((BSW_CANNM_A_FUNCTION_CH7  == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_6)
#define BSW_CANNM_A_CH_USE_CH0_8      ((BSW_CANNM_A_FUNCTION_CH8  == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_7)
#define BSW_CANNM_A_CH_USE_CH0_9      ((BSW_CANNM_A_FUNCTION_CH9  == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_8)
#define BSW_CANNM_A_CH_USE_CH0_10     ((BSW_CANNM_A_FUNCTION_CH10 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_9)
#define BSW_CANNM_A_CH_USE_CH0_11     ((BSW_CANNM_A_FUNCTION_CH11 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_10)
#define BSW_CANNM_A_CH_USE_CH0_12     ((BSW_CANNM_A_FUNCTION_CH12 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_11)
#define BSW_CANNM_A_CH_USE_CH0_13     ((BSW_CANNM_A_FUNCTION_CH13 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_12)
#define BSW_CANNM_A_CH_USE_CH0_14     ((BSW_CANNM_A_FUNCTION_CH14 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_13)
#define BSW_CANNM_A_CH_USE_CH0_15     ((BSW_CANNM_A_FUNCTION_CH15 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_14)
#define BSW_CANNM_A_CH_USE_CH0_16     ((BSW_CANNM_A_FUNCTION_CH16 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_15)
#define BSW_CANNM_A_CH_USE_CH0_17     ((BSW_CANNM_A_FUNCTION_CH17 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_16)
#define BSW_CANNM_A_CH_USE_CH0_18     ((BSW_CANNM_A_FUNCTION_CH18 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_17)
#define BSW_CANNM_A_CH_USE_CH0_19     ((BSW_CANNM_A_FUNCTION_CH19 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_18)
#define BSW_CANNM_A_CH_USE_CH0_20     ((BSW_CANNM_A_FUNCTION_CH20 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_19)
#define BSW_CANNM_A_CH_USE_CH0_21     ((BSW_CANNM_A_FUNCTION_CH21 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_20)
#define BSW_CANNM_A_CH_USE_CH0_22     ((BSW_CANNM_A_FUNCTION_CH22 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_21)
#define BSW_CANNM_A_CH_USE_CH0_23     ((BSW_CANNM_A_FUNCTION_CH23 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_22)
#define BSW_CANNM_A_CH_USE_CH0_24     ((BSW_CANNM_A_FUNCTION_CH24 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_23)
#define BSW_CANNM_A_CH_USE_CH0_25     ((BSW_CANNM_A_FUNCTION_CH25 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_24)
#define BSW_CANNM_A_CH_USE_CH0_26     ((BSW_CANNM_A_FUNCTION_CH26 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_25)
#define BSW_CANNM_A_CH_USE_CH0_27     ((BSW_CANNM_A_FUNCTION_CH27 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_26)
#define BSW_CANNM_A_CH_USE_CH0_28     ((BSW_CANNM_A_FUNCTION_CH28 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_27)
#define BSW_CANNM_A_CH_USE_CH0_29     ((BSW_CANNM_A_FUNCTION_CH29 == BSW_CANNM_A_DIRECT) ? BSW_USE : BSW_CANNM_A_CH_USE_CH0_28)

/* CanNmA Configure per-channel configuration */
BswConst    Bsw_CanNmA_STConfgTblChType  bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_COMMON_MAXCH] = {
#if      ( BSW_CANNM_A_FUNCTION_CH0 == BSW_CANNM_A_DIRECT )
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH0,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH0,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(0U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_0 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_0 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH1 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH1,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH1,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(1U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_1 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_1 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH2 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_1 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH2,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH2,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(2U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_2 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_2 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH3 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_2 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH3,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH3,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(3U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_3 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_3 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH4 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_3 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH4,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH4,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(4U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_4 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_4 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH5 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_4 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH5,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH5,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(5U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_5 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_5 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH6 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_5 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH6,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH6,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(6U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_6 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_6 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH7 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_6 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH7,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH7,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(7U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_7 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_7 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH8 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_7 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH8,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH8,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(8U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_8 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_8 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH9 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_8 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH9,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH9,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(9U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_9 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_9 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH10 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_9 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH10,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH10,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(10U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_10 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_10 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH11 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_10 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH11,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH11,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(11U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_11 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_11 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH12 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_11 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH12,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH12,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(12U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_12 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_12 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH13 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_12 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH13,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH13,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(13U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_13 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_13 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH14 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_13 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH14,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH14,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(14U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_14 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_14 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH15 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_14 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH15,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH15,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(15U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_15 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_15 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH16 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_15 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH16,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH16,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(16U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_16 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_16 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH17 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_16 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH17,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH17,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(17U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_17 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_17 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH18 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_17 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH18,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH18,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(18U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_18 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_18 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH19 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_18 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH19,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH19,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(19U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_19 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_19 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH20 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_19 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH20,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH20,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(20U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_20 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_20 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH21 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_20 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH21,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH21,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(21U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_21 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_21 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH22 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_21 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH22,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH22,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(22U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_22 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_22 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH23 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_22 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH23,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH23,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(23U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_23 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_23 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH24 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_23 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH24,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH24,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(24U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_24 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_24 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH25 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_24 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH25,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH25,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(25U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_25 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_25 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH26 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_25 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH26,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH26,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(26U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_26 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_26 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH27 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_26 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH27,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH27,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(27U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_27 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_27 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH28 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_27 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH28,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH28,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(28U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_28 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_28 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH29 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_28 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH29,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH29,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(29U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_29 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_29 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH30 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_29 == BSW_USE )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH30,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH30,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(30U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_30 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_30 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH31 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_COMMON_MAXCH != 1U )
             ,
#endif
            { (BswU1)BSW_CANNM_A_OWN_NODE_ID_CH31,
              (BswU1)BSW_CANNM_A_IMMWU_OFST_USE_CH31,
              (BswU1)BSW_CANNM_BUSSLEEP_USE(31U),
             {(BswU1)0U,
              (BswU1)((BSW_CANNM_A_CFG_ECUSPECNO_31 >> BSW_CANNM_A_SHT8) & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)(BSW_CANNM_A_CFG_ECUSPECNO_31 & BSW_CANNM_A_ECUSPECNO_LBYTE_MSK),
              (BswU1)0U,(BswU1)0U,(BswU1)0U} }
#endif
                          };


/* Set TBL for the channel that implements CanNmA. Corresponding TBL for channels and CanNmA-implementing channels */
BswConst    BswU1 bsw_cannm_a_ctrl_u1CnoChgIn[ BSW_CANNM_A_CAN_CH_NUM ]  = {   /* All CH No. -> CanNmA CH No  */
             (BswU1)BSW_CANNM_A_CHNOINPUT_CH0
#if (BSW_CANNM_A_CAN_CH_NUM > 1U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH1
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 2U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH2
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 3U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH3
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 4U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH4
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 5U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH5
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 6U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH6
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 7U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH7
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 8U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH8
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 9U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH9
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 10U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH10
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 11U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH11
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 12U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH12
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 13U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH13
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 14U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH14
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 15U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH15
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 16U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH16
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 17U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH17
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 18U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH18
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 19U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH19
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 20U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH20
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 21U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH21
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 22U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH22
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 23U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH23
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 24U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH24
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 25U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH25
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 26U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH26
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 27U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH27
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 28U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH28
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 29U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH29
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 30U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH30
#endif
#if (BSW_CANNM_A_CAN_CH_NUM > 31U)
             , (BswU1)BSW_CANNM_A_CHNOINPUT_CH31
#endif
              };

BswConst    BswU1 bsw_cannm_a_ctrl_u1CnoChgOut[BSW_CANNM_A_COMMON_MAXCH]  = { /* CanNmA CH No -> Entire CH No */
#if      ( BSW_CANNM_A_FUNCTION_CH0 == BSW_CANNM_A_DIRECT )
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH0
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH1 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH1
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH2 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_1 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH2
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH3 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_2 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH3
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH4 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_3 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH4
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH5 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_4 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH5
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH6 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_5 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH6
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH7 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_6 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH7
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH8 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_7 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH8
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH9 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_8 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH9
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH10 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_9 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH10
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH11 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_10 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH11
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH12 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_11 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH12
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH13 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_12 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH13
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH14 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_13 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH14
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH15 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_14 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH15
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH16 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_15 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH16
#endif

#if      ( BSW_CANNM_A_FUNCTION_CH17 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_16 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH17
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH18 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_17 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH18
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH19 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_18 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH19
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH20 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_19 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH20
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH21 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_20 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH21
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH22 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_21 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH22
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH23 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_22 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH23
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH24 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_23 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH24
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH25 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_24 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH25
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH26 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_25 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH26
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH27 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_26 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH27
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH28 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_27 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH28
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH29 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_28 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH29
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH30 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_29 == BSW_USE )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH30
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH31 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_COMMON_MAXCH != 1U )
             ,
#endif
             (BswU1)BSW_CANNM_A_CHNOOUTPUT_CH31
#endif
        };

/* CVT table */

/* DisableSend Time value table */
BswConst    BswU2 bsw_cannm_a_cvtnm_u2DisSendTbl[BSW_CANNM_A_COMMON_MAXCH]  =
{
#if      ( BSW_CANNM_A_FUNCTION_CH0 == BSW_CANNM_A_DIRECT )
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH0 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH1 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH1 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH2 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_1 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH2 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH3 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_2 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH3 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH4 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_3 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH4 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH5 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_4 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH5 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH6 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_5 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH6 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH7 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_6 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH7 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH8 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_7 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH8 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH9 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_8 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH9 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH10 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_9 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH10 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH11 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_10 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH11 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH12 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_11 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH12 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH13 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_12 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH13 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH14 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_13 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH14 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH15 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_14 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH15 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH16 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_15 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH16 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH17 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_16 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH17 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH18 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_17 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH18 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH19 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_18 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH19 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH20 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_19 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH20 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH21 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_20 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH21 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH22 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_21 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH22 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH23 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_22 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH23 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH24 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_23 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH24 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH25 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_24 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH25 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH26 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_25 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH26 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH27 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_26 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH27 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH28 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_27 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH28 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH29 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_28 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH29 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH30 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_29 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH30 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH31 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_COMMON_MAXCH != 1U )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_WKUP_WAIT_CH31 )
#endif
};

/* EnablePeriodic Time value table */
BswConst    BswU2 bsw_cannm_a_cvtnm_u2EnaPeriTbl[BSW_CANNM_A_COMMON_MAXCH]  =
{
#if      ( BSW_CANNM_A_FUNCTION_CH0 == BSW_CANNM_A_DIRECT )
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH0 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH1 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH1 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH2 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_1 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH2 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH3 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_2 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH3 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH4 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_3 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH4 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH5 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_4 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH5 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH6 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_5 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH6 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH7 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_6 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH7 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH8 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_7 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH8 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH9 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_8 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH9 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH10 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_9 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH10 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH11 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_10 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH11 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH12 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_11 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH12 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH13 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_12 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH13 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH14 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_13 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH14 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH15 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_14 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH15 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH16 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_15 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH16 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH17 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_16 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH17 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH18 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_17 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH18 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH19 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_18 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH19 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH20 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_19 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH20 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH21 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_20 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH21 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH22 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_21 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH22 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH23 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_22 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH23 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH24 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_23 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH24 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH25 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_24 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH25 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH26 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_25 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH26 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH27 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_26 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH27 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH28 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_27 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH28 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH29 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_28 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH29 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH30 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_29 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH30 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH31 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_COMMON_MAXCH != 1U )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRD_WAIT_CH31 )
#endif
};

/* Immediate Transmission Offset value table */
BswConst    BswU2 bsw_cannm_a_cvtnm_u2ImmTxOfsTbl[BSW_CANNM_A_COMMON_MAXCH]  =
{
#if      ( BSW_CANNM_A_FUNCTION_CH0 == BSW_CANNM_A_DIRECT )
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH0 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH1 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH1 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH2 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_1 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH2 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH3 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_2 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH3 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH4 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_3 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH4 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH5 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_4 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH5 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH6 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_5 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH6 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH7 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_6 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH7 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH8 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_7 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH8 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH9 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_8 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH9 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH10 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_9 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH10 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH11 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_10 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH11 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH12 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_11 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH12 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH13 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_12 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH13 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH14 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_13 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH14 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH15 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_14 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH15 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH16 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_15 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH16 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH17 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_16 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH17 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH18 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_17 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH18 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH19 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_18 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH19 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH20 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_19 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH20 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH21 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_20 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH21 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH22 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_21 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH22 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH23 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_22 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH23 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH24 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_23 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH24 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH25 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_24 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH25 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH26 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_25 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH26 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH27 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_26 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH27 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH28 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_27 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH28 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH29 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_28 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH29 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH30 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_29 == BSW_USE )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH30 )
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH31 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_COMMON_MAXCH != 1U )
             ,
#endif
        BSW_CANNM_A_u2MS2COMTICK_RUP( BSW_CANNM_A_CVT_ENPRDIMM_CH31 )
#endif
};

/* OSEK table */

static BswConst    Bsw_CanNmA_STNmOsekRomDataType bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_COMMON_MAXCH] =
{
#if      ( BSW_CANNM_A_FUNCTION_CH0 == BSW_CANNM_A_DIRECT )
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH0].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH0,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH0
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH1 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH1].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH1,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH1
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH2 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_1 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH2].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH2,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH2
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH3 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_2 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH3].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH3,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH3
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH4 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_3 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH4].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH4,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH4
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH5 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_4 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH5].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH5,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH5
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH6 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_5 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH6].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH6,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH6
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH7 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_6 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH7].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH7,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH7
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH8 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_7 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH8].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH8,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH8
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH9 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_8 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH9].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH9,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH9
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH10 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_9 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH10].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH10,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH10
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH11 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_10 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH11].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH11,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH11
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH12 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_11 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH12].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH12,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH12
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH13 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_12 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH13].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH13,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH13
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH14 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_13 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH14].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH14,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH14
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH15 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_14 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH15].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH15,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH15
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH16 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_15 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH16].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH16,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH16
    }
#endif

#if      ( BSW_CANNM_A_FUNCTION_CH17 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_16 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH17].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH17,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH17
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH18 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_17 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH18].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH18,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH18
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH19 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_18 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH19].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH19,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH19
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH20 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_19 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH20].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH20,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH20
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH21 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_20 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH21].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH21,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH21
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH22 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_21 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH22].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH22,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH22
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH23 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_22 == BSW_USE )
             ,
#endif
     {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH23].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH23,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH23
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH24 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_23 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH24].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH24,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH24
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH25 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_24 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH25].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH25,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH25
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH26 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_25 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH26].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH26,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH26
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH27 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_26 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH27].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH27,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH27
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH28 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_27 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH28].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH28,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH28
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH29 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_28 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH29].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH29,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH29
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH30 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_29 == BSW_USE )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH30].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH30,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH30
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH31 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_COMMON_MAXCH != 1U )
             ,
#endif
    {
        &bsw_cannm_a_ctrl_stChTbl[BSW_CANNM_A_CHNOINPUT_CH31].u1MsgData[0],
        (BswU1)BSW_CANNM_A_OSEK_TXLIMIT_CH31,
        (BswU1)BSW_CANNM_A_OSEK_RXLIMIT_CH31
    }
#endif
};

/* OSEK control table */
BswConst    Bsw_CanNmA_STNmOsekCntXTType bsw_cannm_a_oseknm_stContextTbl[BSW_CANNM_A_COMMON_MAXCH] =
{
#if      ( BSW_CANNM_A_FUNCTION_CH0 == BSW_CANNM_A_DIRECT )
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH0], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH0]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH1 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH1], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH1]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH2 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_1 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH2], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH2]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH3 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_2 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH3], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH3]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH4 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_3 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH4], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH4]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH5 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_4 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH5], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH5]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH6 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_5 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH6], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH6]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH7 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_6 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH7], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH7]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH8 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_7 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH8], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH8]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH9 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_8 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH9], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH9]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH10 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_9 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH10], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH10]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH11 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_10 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH11], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH11]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH12 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_11 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH12], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH12]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH13 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_12 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH13], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH13]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH14 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_13 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH14], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH14]}
#endif

#if      ( BSW_CANNM_A_FUNCTION_CH15 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_14 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH15], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH15]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH16 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_15 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH16], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH16]}
#endif

#if      ( BSW_CANNM_A_FUNCTION_CH17 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_16 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH17], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH17]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH18 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_17 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH18], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH18]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH19 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_18 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH19], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH19]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH20 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_19 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH20], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH20]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH21 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_20 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH21], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH21]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH22 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_21 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH22], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH22]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH23 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_22 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH23], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH23]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH24 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_23 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH24], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH24]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH25 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_24 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH25], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH25]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH26 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_25 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH26], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH26]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH27 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_26 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH27], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH27]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH28 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_27 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH28], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH28]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH29 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_28 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH29], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH29]}
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH30 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_29 == BSW_USE )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH30], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH30]}
#endif

#if      ( BSW_CANNM_A_FUNCTION_CH31 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_COMMON_MAXCH != 1U )
             ,
#endif
    {&bsw_cannm_a_stOsekRomDataTbl[BSW_CANNM_A_CHNOINPUT_CH31], &bsw_cannm_a_stOsekRamDataTbl[BSW_CANNM_A_CHNOINPUT_CH31]}
#endif
};

/* Timer value table (number of channels * number of timers) Retained */
BswConst    BswU2 bsw_cannm_a_timer_u2TmCntTbl[BSW_CANNM_A_COMMON_MAXCH][BSW_CANNM_A_TIMER_TBLMAX]  =
{
#if      ( BSW_CANNM_A_FUNCTION_CH0 == BSW_CANNM_A_DIRECT )
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH0,
        BSW_CANNM_A_u2RUN_AWAKE_CH0,
        BSW_CANNM_A_u2POWON_SLP_CH0,
        BSW_CANNM_A_u2NOWUP_WAIT_CH0,
        BSW_CANNM_A_u2WKUP_WAIT_CH0,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH0,
        BSW_CANNM_A_u2NRMSLPEG_CH0,
        BSW_CANNM_A_u2PERIODIC_WT_CH0,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH0,
        BSW_CANNM_A_u2OSEK_TTYP_CH0,
        BSW_CANNM_A_u2OSEK_TMAX_CH0,
        BSW_CANNM_A_u2OSEK_TERROR_CH0,
        BSW_CANNM_A_u2OSEK_TWBS_CH0,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH0
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH1 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH1,
        BSW_CANNM_A_u2RUN_AWAKE_CH1,
        BSW_CANNM_A_u2POWON_SLP_CH1,
        BSW_CANNM_A_u2NOWUP_WAIT_CH1,
        BSW_CANNM_A_u2WKUP_WAIT_CH1,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH1,
        BSW_CANNM_A_u2NRMSLPEG_CH1,
        BSW_CANNM_A_u2PERIODIC_WT_CH1,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH1,
        BSW_CANNM_A_u2OSEK_TTYP_CH1,
        BSW_CANNM_A_u2OSEK_TMAX_CH1,
        BSW_CANNM_A_u2OSEK_TERROR_CH1,
        BSW_CANNM_A_u2OSEK_TWBS_CH1,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH1
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH2 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_1 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH2,
        BSW_CANNM_A_u2RUN_AWAKE_CH2,
        BSW_CANNM_A_u2POWON_SLP_CH2,
        BSW_CANNM_A_u2NOWUP_WAIT_CH2,
        BSW_CANNM_A_u2WKUP_WAIT_CH2,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH2,
        BSW_CANNM_A_u2NRMSLPEG_CH2,
        BSW_CANNM_A_u2PERIODIC_WT_CH2,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH2,
        BSW_CANNM_A_u2OSEK_TTYP_CH2,
        BSW_CANNM_A_u2OSEK_TMAX_CH2,
        BSW_CANNM_A_u2OSEK_TERROR_CH2,
        BSW_CANNM_A_u2OSEK_TWBS_CH2,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH2
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH3 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_2 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH3,
        BSW_CANNM_A_u2RUN_AWAKE_CH3,
        BSW_CANNM_A_u2POWON_SLP_CH3,
        BSW_CANNM_A_u2NOWUP_WAIT_CH3,
        BSW_CANNM_A_u2WKUP_WAIT_CH3,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH3,
        BSW_CANNM_A_u2NRMSLPEG_CH3,
        BSW_CANNM_A_u2PERIODIC_WT_CH3,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH3,
        BSW_CANNM_A_u2OSEK_TTYP_CH3,
        BSW_CANNM_A_u2OSEK_TMAX_CH3,
        BSW_CANNM_A_u2OSEK_TERROR_CH3,
        BSW_CANNM_A_u2OSEK_TWBS_CH3,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH3
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH4 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_3 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH4,
        BSW_CANNM_A_u2RUN_AWAKE_CH4,
        BSW_CANNM_A_u2POWON_SLP_CH4,
        BSW_CANNM_A_u2NOWUP_WAIT_CH4,
        BSW_CANNM_A_u2WKUP_WAIT_CH4,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH4,
        BSW_CANNM_A_u2NRMSLPEG_CH4,
        BSW_CANNM_A_u2PERIODIC_WT_CH4,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH4,
        BSW_CANNM_A_u2OSEK_TTYP_CH4,
        BSW_CANNM_A_u2OSEK_TMAX_CH4,
        BSW_CANNM_A_u2OSEK_TERROR_CH4,
        BSW_CANNM_A_u2OSEK_TWBS_CH4,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH4
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH5 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_4 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH5,
        BSW_CANNM_A_u2RUN_AWAKE_CH5,
        BSW_CANNM_A_u2POWON_SLP_CH5,
        BSW_CANNM_A_u2NOWUP_WAIT_CH5,
        BSW_CANNM_A_u2WKUP_WAIT_CH5,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH5,
        BSW_CANNM_A_u2NRMSLPEG_CH5,
        BSW_CANNM_A_u2PERIODIC_WT_CH5,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH5,
        BSW_CANNM_A_u2OSEK_TTYP_CH5,
        BSW_CANNM_A_u2OSEK_TMAX_CH5,
        BSW_CANNM_A_u2OSEK_TERROR_CH5,
        BSW_CANNM_A_u2OSEK_TWBS_CH5,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH5
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH6 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_5 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH6,
        BSW_CANNM_A_u2RUN_AWAKE_CH6,
        BSW_CANNM_A_u2POWON_SLP_CH6,
        BSW_CANNM_A_u2NOWUP_WAIT_CH6,
        BSW_CANNM_A_u2WKUP_WAIT_CH6,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH6,
        BSW_CANNM_A_u2NRMSLPEG_CH6,
        BSW_CANNM_A_u2PERIODIC_WT_CH6,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH6,
        BSW_CANNM_A_u2OSEK_TTYP_CH6,
        BSW_CANNM_A_u2OSEK_TMAX_CH6,
        BSW_CANNM_A_u2OSEK_TERROR_CH6,
        BSW_CANNM_A_u2OSEK_TWBS_CH6,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH6
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH7 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_6 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH7,
        BSW_CANNM_A_u2RUN_AWAKE_CH7,
        BSW_CANNM_A_u2POWON_SLP_CH7,
        BSW_CANNM_A_u2NOWUP_WAIT_CH7,
        BSW_CANNM_A_u2WKUP_WAIT_CH7,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH7,
        BSW_CANNM_A_u2NRMSLPEG_CH7,
        BSW_CANNM_A_u2PERIODIC_WT_CH7,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH7,
        BSW_CANNM_A_u2OSEK_TTYP_CH7,
        BSW_CANNM_A_u2OSEK_TMAX_CH7,
        BSW_CANNM_A_u2OSEK_TERROR_CH7,
        BSW_CANNM_A_u2OSEK_TWBS_CH7,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH7
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH8 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_7 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH8,
        BSW_CANNM_A_u2RUN_AWAKE_CH8,
        BSW_CANNM_A_u2POWON_SLP_CH8,
        BSW_CANNM_A_u2NOWUP_WAIT_CH8,
        BSW_CANNM_A_u2WKUP_WAIT_CH8,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH8,
        BSW_CANNM_A_u2NRMSLPEG_CH8,
        BSW_CANNM_A_u2PERIODIC_WT_CH8,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH8,
        BSW_CANNM_A_u2OSEK_TTYP_CH8,
        BSW_CANNM_A_u2OSEK_TMAX_CH8,
        BSW_CANNM_A_u2OSEK_TERROR_CH8,
        BSW_CANNM_A_u2OSEK_TWBS_CH8,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH8
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH9 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_8 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH9,
        BSW_CANNM_A_u2RUN_AWAKE_CH9,
        BSW_CANNM_A_u2POWON_SLP_CH9,
        BSW_CANNM_A_u2NOWUP_WAIT_CH9,
        BSW_CANNM_A_u2WKUP_WAIT_CH9,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH9,
        BSW_CANNM_A_u2NRMSLPEG_CH9,
        BSW_CANNM_A_u2PERIODIC_WT_CH9,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH9,
        BSW_CANNM_A_u2OSEK_TTYP_CH9,
        BSW_CANNM_A_u2OSEK_TMAX_CH9,
        BSW_CANNM_A_u2OSEK_TERROR_CH9,
        BSW_CANNM_A_u2OSEK_TWBS_CH9,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH9
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH10 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_9 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH10,
        BSW_CANNM_A_u2RUN_AWAKE_CH10,
        BSW_CANNM_A_u2POWON_SLP_CH10,
        BSW_CANNM_A_u2NOWUP_WAIT_CH10,
        BSW_CANNM_A_u2WKUP_WAIT_CH10,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH10,
        BSW_CANNM_A_u2NRMSLPEG_CH10,
        BSW_CANNM_A_u2PERIODIC_WT_CH10,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH10,
        BSW_CANNM_A_u2OSEK_TTYP_CH10,
        BSW_CANNM_A_u2OSEK_TMAX_CH10,
        BSW_CANNM_A_u2OSEK_TERROR_CH10,
        BSW_CANNM_A_u2OSEK_TWBS_CH10,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH10
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH11 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_10 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH11,
        BSW_CANNM_A_u2RUN_AWAKE_CH11,
        BSW_CANNM_A_u2POWON_SLP_CH11,
        BSW_CANNM_A_u2NOWUP_WAIT_CH11,
        BSW_CANNM_A_u2WKUP_WAIT_CH11,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH11,
        BSW_CANNM_A_u2NRMSLPEG_CH11,
        BSW_CANNM_A_u2PERIODIC_WT_CH11,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH11,
        BSW_CANNM_A_u2OSEK_TTYP_CH11,
        BSW_CANNM_A_u2OSEK_TMAX_CH11,
        BSW_CANNM_A_u2OSEK_TERROR_CH11,
        BSW_CANNM_A_u2OSEK_TWBS_CH11,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH11
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH12 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_11 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH12,
        BSW_CANNM_A_u2RUN_AWAKE_CH12,
        BSW_CANNM_A_u2POWON_SLP_CH12,
        BSW_CANNM_A_u2NOWUP_WAIT_CH12,
        BSW_CANNM_A_u2WKUP_WAIT_CH12,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH12,
        BSW_CANNM_A_u2NRMSLPEG_CH12,
        BSW_CANNM_A_u2PERIODIC_WT_CH12,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH12,
        BSW_CANNM_A_u2OSEK_TTYP_CH12,
        BSW_CANNM_A_u2OSEK_TMAX_CH12,
        BSW_CANNM_A_u2OSEK_TERROR_CH12,
        BSW_CANNM_A_u2OSEK_TWBS_CH12,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH12
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH13 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_12 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH13,
        BSW_CANNM_A_u2RUN_AWAKE_CH13,
        BSW_CANNM_A_u2POWON_SLP_CH13,
        BSW_CANNM_A_u2NOWUP_WAIT_CH13,
        BSW_CANNM_A_u2WKUP_WAIT_CH13,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH13,
        BSW_CANNM_A_u2NRMSLPEG_CH13,
        BSW_CANNM_A_u2PERIODIC_WT_CH13,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH13,
        BSW_CANNM_A_u2OSEK_TTYP_CH13,
        BSW_CANNM_A_u2OSEK_TMAX_CH13,
        BSW_CANNM_A_u2OSEK_TERROR_CH13,
        BSW_CANNM_A_u2OSEK_TWBS_CH13,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH13
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH14 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_13 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH14,
        BSW_CANNM_A_u2RUN_AWAKE_CH14,
        BSW_CANNM_A_u2POWON_SLP_CH14,
        BSW_CANNM_A_u2NOWUP_WAIT_CH14,
        BSW_CANNM_A_u2WKUP_WAIT_CH14,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH14,
        BSW_CANNM_A_u2NRMSLPEG_CH14,
        BSW_CANNM_A_u2PERIODIC_WT_CH14,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH14,
        BSW_CANNM_A_u2OSEK_TTYP_CH14,
        BSW_CANNM_A_u2OSEK_TMAX_CH14,
        BSW_CANNM_A_u2OSEK_TERROR_CH14,
        BSW_CANNM_A_u2OSEK_TWBS_CH14,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH14
    }
#endif

#if      ( BSW_CANNM_A_FUNCTION_CH15 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_14 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH15,
        BSW_CANNM_A_u2RUN_AWAKE_CH15,
        BSW_CANNM_A_u2POWON_SLP_CH15,
        BSW_CANNM_A_u2NOWUP_WAIT_CH15,
        BSW_CANNM_A_u2WKUP_WAIT_CH15,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH15,
        BSW_CANNM_A_u2NRMSLPEG_CH15,
        BSW_CANNM_A_u2PERIODIC_WT_CH15,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH15,
        BSW_CANNM_A_u2OSEK_TTYP_CH15,
        BSW_CANNM_A_u2OSEK_TMAX_CH15,
        BSW_CANNM_A_u2OSEK_TERROR_CH15,
        BSW_CANNM_A_u2OSEK_TWBS_CH15,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH15
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH16 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_15 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH16,
        BSW_CANNM_A_u2RUN_AWAKE_CH16,
        BSW_CANNM_A_u2POWON_SLP_CH16,
        BSW_CANNM_A_u2NOWUP_WAIT_CH16,
        BSW_CANNM_A_u2WKUP_WAIT_CH16,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH16,
        BSW_CANNM_A_u2NRMSLPEG_CH16,
        BSW_CANNM_A_u2PERIODIC_WT_CH16,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH16,
        BSW_CANNM_A_u2OSEK_TTYP_CH16,
        BSW_CANNM_A_u2OSEK_TMAX_CH16,
        BSW_CANNM_A_u2OSEK_TERROR_CH16,
        BSW_CANNM_A_u2OSEK_TWBS_CH16,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH16
    }
#endif

#if      ( BSW_CANNM_A_FUNCTION_CH17 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_16 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH17,
        BSW_CANNM_A_u2RUN_AWAKE_CH17,
        BSW_CANNM_A_u2POWON_SLP_CH17,
        BSW_CANNM_A_u2NOWUP_WAIT_CH17,
        BSW_CANNM_A_u2WKUP_WAIT_CH17,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH17,
        BSW_CANNM_A_u2NRMSLPEG_CH17,
        BSW_CANNM_A_u2PERIODIC_WT_CH17,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH17,
        BSW_CANNM_A_u2OSEK_TTYP_CH17,
        BSW_CANNM_A_u2OSEK_TMAX_CH17,
        BSW_CANNM_A_u2OSEK_TERROR_CH17,
        BSW_CANNM_A_u2OSEK_TWBS_CH17,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH17
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH18 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_17 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH18,
        BSW_CANNM_A_u2RUN_AWAKE_CH18,
        BSW_CANNM_A_u2POWON_SLP_CH18,
        BSW_CANNM_A_u2NOWUP_WAIT_CH18,
        BSW_CANNM_A_u2WKUP_WAIT_CH18,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH18,
        BSW_CANNM_A_u2NRMSLPEG_CH18,
        BSW_CANNM_A_u2PERIODIC_WT_CH18,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH18,
        BSW_CANNM_A_u2OSEK_TTYP_CH18,
        BSW_CANNM_A_u2OSEK_TMAX_CH18,
        BSW_CANNM_A_u2OSEK_TERROR_CH18,
        BSW_CANNM_A_u2OSEK_TWBS_CH18,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH18
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH19 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_18 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH19,
        BSW_CANNM_A_u2RUN_AWAKE_CH19,
        BSW_CANNM_A_u2POWON_SLP_CH19,
        BSW_CANNM_A_u2NOWUP_WAIT_CH19,
        BSW_CANNM_A_u2WKUP_WAIT_CH19,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH19,
        BSW_CANNM_A_u2NRMSLPEG_CH19,
        BSW_CANNM_A_u2PERIODIC_WT_CH19,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH19,
        BSW_CANNM_A_u2OSEK_TTYP_CH19,
        BSW_CANNM_A_u2OSEK_TMAX_CH19,
        BSW_CANNM_A_u2OSEK_TERROR_CH19,
        BSW_CANNM_A_u2OSEK_TWBS_CH19,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH19
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH20 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_19 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH20,
        BSW_CANNM_A_u2RUN_AWAKE_CH20,
        BSW_CANNM_A_u2POWON_SLP_CH20,
        BSW_CANNM_A_u2NOWUP_WAIT_CH20,
        BSW_CANNM_A_u2WKUP_WAIT_CH20,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH20,
        BSW_CANNM_A_u2NRMSLPEG_CH20,
        BSW_CANNM_A_u2PERIODIC_WT_CH20,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH20,
        BSW_CANNM_A_u2OSEK_TTYP_CH20,
        BSW_CANNM_A_u2OSEK_TMAX_CH20,
        BSW_CANNM_A_u2OSEK_TERROR_CH20,
        BSW_CANNM_A_u2OSEK_TWBS_CH20,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH20
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH21 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_20 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH21,
        BSW_CANNM_A_u2RUN_AWAKE_CH21,
        BSW_CANNM_A_u2POWON_SLP_CH21,
        BSW_CANNM_A_u2NOWUP_WAIT_CH21,
        BSW_CANNM_A_u2WKUP_WAIT_CH21,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH21,
        BSW_CANNM_A_u2NRMSLPEG_CH21,
        BSW_CANNM_A_u2PERIODIC_WT_CH21,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH21,
        BSW_CANNM_A_u2OSEK_TTYP_CH21,
        BSW_CANNM_A_u2OSEK_TMAX_CH21,
        BSW_CANNM_A_u2OSEK_TERROR_CH21,
        BSW_CANNM_A_u2OSEK_TWBS_CH21,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH21
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH22 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_21 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH22,
        BSW_CANNM_A_u2RUN_AWAKE_CH22,
        BSW_CANNM_A_u2POWON_SLP_CH22,
        BSW_CANNM_A_u2NOWUP_WAIT_CH22,
        BSW_CANNM_A_u2WKUP_WAIT_CH22,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH22,
        BSW_CANNM_A_u2NRMSLPEG_CH22,
        BSW_CANNM_A_u2PERIODIC_WT_CH22,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH22,
        BSW_CANNM_A_u2OSEK_TTYP_CH22,
        BSW_CANNM_A_u2OSEK_TMAX_CH22,
        BSW_CANNM_A_u2OSEK_TERROR_CH22,
        BSW_CANNM_A_u2OSEK_TWBS_CH22,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH22
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH23 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_22 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH23,
        BSW_CANNM_A_u2RUN_AWAKE_CH23,
        BSW_CANNM_A_u2POWON_SLP_CH23,
        BSW_CANNM_A_u2NOWUP_WAIT_CH23,
        BSW_CANNM_A_u2WKUP_WAIT_CH23,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH23,
        BSW_CANNM_A_u2NRMSLPEG_CH23,
        BSW_CANNM_A_u2PERIODIC_WT_CH23,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH23,
        BSW_CANNM_A_u2OSEK_TTYP_CH23,
        BSW_CANNM_A_u2OSEK_TMAX_CH23,
        BSW_CANNM_A_u2OSEK_TERROR_CH23,
        BSW_CANNM_A_u2OSEK_TWBS_CH23,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH23
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH24 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_23 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH24,
        BSW_CANNM_A_u2RUN_AWAKE_CH24,
        BSW_CANNM_A_u2POWON_SLP_CH24,
        BSW_CANNM_A_u2NOWUP_WAIT_CH24,
        BSW_CANNM_A_u2WKUP_WAIT_CH24,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH24,
        BSW_CANNM_A_u2NRMSLPEG_CH24,
        BSW_CANNM_A_u2PERIODIC_WT_CH24,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH24,
        BSW_CANNM_A_u2OSEK_TTYP_CH24,
        BSW_CANNM_A_u2OSEK_TMAX_CH24,
        BSW_CANNM_A_u2OSEK_TERROR_CH24,
        BSW_CANNM_A_u2OSEK_TWBS_CH24,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH24
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH25 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_24 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH25,
        BSW_CANNM_A_u2RUN_AWAKE_CH25,
        BSW_CANNM_A_u2POWON_SLP_CH25,
        BSW_CANNM_A_u2NOWUP_WAIT_CH25,
        BSW_CANNM_A_u2WKUP_WAIT_CH25,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH25,
        BSW_CANNM_A_u2NRMSLPEG_CH25,
        BSW_CANNM_A_u2PERIODIC_WT_CH25,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH25,
        BSW_CANNM_A_u2OSEK_TTYP_CH25,
        BSW_CANNM_A_u2OSEK_TMAX_CH25,
        BSW_CANNM_A_u2OSEK_TERROR_CH25,
        BSW_CANNM_A_u2OSEK_TWBS_CH25,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH25
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH26 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_25 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH26,
        BSW_CANNM_A_u2RUN_AWAKE_CH26,
        BSW_CANNM_A_u2POWON_SLP_CH26,
        BSW_CANNM_A_u2NOWUP_WAIT_CH26,
        BSW_CANNM_A_u2WKUP_WAIT_CH26,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH26,
        BSW_CANNM_A_u2NRMSLPEG_CH26,
        BSW_CANNM_A_u2PERIODIC_WT_CH26,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH26,
        BSW_CANNM_A_u2OSEK_TTYP_CH26,
        BSW_CANNM_A_u2OSEK_TMAX_CH26,
        BSW_CANNM_A_u2OSEK_TERROR_CH26,
        BSW_CANNM_A_u2OSEK_TWBS_CH26,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH26
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH27 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_26 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH27,
        BSW_CANNM_A_u2RUN_AWAKE_CH27,
        BSW_CANNM_A_u2POWON_SLP_CH27,
        BSW_CANNM_A_u2NOWUP_WAIT_CH27,
        BSW_CANNM_A_u2WKUP_WAIT_CH27,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH27,
        BSW_CANNM_A_u2NRMSLPEG_CH27,
        BSW_CANNM_A_u2PERIODIC_WT_CH27,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH27,
        BSW_CANNM_A_u2OSEK_TTYP_CH27,
        BSW_CANNM_A_u2OSEK_TMAX_CH27,
        BSW_CANNM_A_u2OSEK_TERROR_CH27,
        BSW_CANNM_A_u2OSEK_TWBS_CH27,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH27
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH28 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_27 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH28,
        BSW_CANNM_A_u2RUN_AWAKE_CH28,
        BSW_CANNM_A_u2POWON_SLP_CH28,
        BSW_CANNM_A_u2NOWUP_WAIT_CH28,
        BSW_CANNM_A_u2WKUP_WAIT_CH28,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH28,
        BSW_CANNM_A_u2NRMSLPEG_CH28,
        BSW_CANNM_A_u2PERIODIC_WT_CH28,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH28,
        BSW_CANNM_A_u2OSEK_TTYP_CH28,
        BSW_CANNM_A_u2OSEK_TMAX_CH28,
        BSW_CANNM_A_u2OSEK_TERROR_CH28,
        BSW_CANNM_A_u2OSEK_TWBS_CH28,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH28
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH29 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_28 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH29,
        BSW_CANNM_A_u2RUN_AWAKE_CH29,
        BSW_CANNM_A_u2POWON_SLP_CH29,
        BSW_CANNM_A_u2NOWUP_WAIT_CH29,
        BSW_CANNM_A_u2WKUP_WAIT_CH29,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH29,
        BSW_CANNM_A_u2NRMSLPEG_CH29,
        BSW_CANNM_A_u2PERIODIC_WT_CH29,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH29,
        BSW_CANNM_A_u2OSEK_TTYP_CH29,
        BSW_CANNM_A_u2OSEK_TMAX_CH29,
        BSW_CANNM_A_u2OSEK_TERROR_CH29,
        BSW_CANNM_A_u2OSEK_TWBS_CH29,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH29
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH30 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_CH_USE_CH0_29 == BSW_USE )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH30,
        BSW_CANNM_A_u2RUN_AWAKE_CH30,
        BSW_CANNM_A_u2POWON_SLP_CH30,
        BSW_CANNM_A_u2NOWUP_WAIT_CH30,
        BSW_CANNM_A_u2WKUP_WAIT_CH30,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH30,
        BSW_CANNM_A_u2NRMSLPEG_CH30,
        BSW_CANNM_A_u2PERIODIC_WT_CH30,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH30,
        BSW_CANNM_A_u2OSEK_TTYP_CH30,
        BSW_CANNM_A_u2OSEK_TMAX_CH30,
        BSW_CANNM_A_u2OSEK_TERROR_CH30,
        BSW_CANNM_A_u2OSEK_TWBS_CH30,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH30
    }
#endif
#if      ( BSW_CANNM_A_FUNCTION_CH31 == BSW_CANNM_A_DIRECT )
#if      ( BSW_CANNM_A_COMMON_MAXCH != 1U )
             ,
#endif
    {
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2POWON_WAIT_CH31,
        BSW_CANNM_A_u2RUN_AWAKE_CH31,
        BSW_CANNM_A_u2POWON_SLP_CH31,
        BSW_CANNM_A_u2NOWUP_WAIT_CH31,
        BSW_CANNM_A_u2WKUP_WAIT_CH31,
        BSW_CANNM_A_u2NONETIMER_CHX,
        BSW_CANNM_A_u2NONEDGE_CH31,
        BSW_CANNM_A_u2NRMSLPEG_CH31,
        BSW_CANNM_A_u2PERIODIC_WT_CH31,
        BSW_CANNM_A_u2PRD_IMM_WAIT_CH31,
        BSW_CANNM_A_u2OSEK_TTYP_CH31,
        BSW_CANNM_A_u2OSEK_TMAX_CH31,
        BSW_CANNM_A_u2OSEK_TERROR_CH31,
        BSW_CANNM_A_u2OSEK_TWBS_CH31,
        BSW_CANNM_A_u2OSEK_TERRWBS_CH31
    }
#endif
};


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif  /* ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE ) */
#endif /* ( BSW_BSWM_CS_FUNC_CANNM == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-1-0          :2018/12/25                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2025/01/17                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
