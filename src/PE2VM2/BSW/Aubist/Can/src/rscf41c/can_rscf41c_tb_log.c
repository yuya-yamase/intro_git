/* can_rscf41c_tb_log_c_v2-2-1                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF41C/TB/LOGICAL/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>
#include <CanIf_Cbk.h>

#include "../../cfg/common/can_cv_cfg.h"
#include "../../cfg/rscf41c/can_rscf41c_cfg_ext.h"
#include "../../cfg/rscf41c/can_rscf41c_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_cv_cbk.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf41c/can_rscf41c.h>
#include <can/rscf41c/can_rscf41c_cm_phy.h>
#include <can/common/can_memmap.h>
#include <can/rscf41c/can_rscf41c_tb_log.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_TB_HTH_OFS_0                ( CAN_TB_HRHNUM )
#define CAN_TB_HTH_OFS_1                ( CAN_TB_HTH_OFS_0 + CAN_CFG_HTHNUM_0 )
#define CAN_TB_HTH_OFS_2                ( CAN_TB_HTH_OFS_1 + CAN_CFG_HTHNUM_1 )
#define CAN_TB_HTH_OFS_3                ( CAN_TB_HTH_OFS_2 + CAN_CFG_HTHNUM_2 )
#define CAN_TB_HTH_OFS_4                ( CAN_TB_HTH_OFS_3 + CAN_CFG_HTHNUM_3 )
#define CAN_TB_HTH_OFS_5                ( CAN_TB_HTH_OFS_4 + CAN_CFG_HTHNUM_4 )
#define CAN_TB_HTH_OFS_6                ( CAN_TB_HTH_OFS_5 + CAN_CFG_HTHNUM_5 )
#define CAN_TB_HTH_OFS_7                ( CAN_TB_HTH_OFS_6 + CAN_CFG_HTHNUM_6 )

#define CAN_TB_HRH_OFS_0                ( 0U )
#define CAN_TB_HRH_OFS_1                ( CAN_TB_HRH_OFS_0 + CAN_CFG_HRHNUM_0 )
#define CAN_TB_HRH_OFS_2                ( CAN_TB_HRH_OFS_1 + CAN_CFG_HRHNUM_1 )
#define CAN_TB_HRH_OFS_3                ( CAN_TB_HRH_OFS_2 + CAN_CFG_HRHNUM_2 )
#define CAN_TB_HRH_OFS_4                ( CAN_TB_HRH_OFS_3 + CAN_CFG_HRHNUM_3 )
#define CAN_TB_HRH_OFS_5                ( CAN_TB_HRH_OFS_4 + CAN_CFG_HRHNUM_4 )
#define CAN_TB_HRH_OFS_6                ( CAN_TB_HRH_OFS_5 + CAN_CFG_HRHNUM_5 )
#define CAN_TB_HRH_OFS_7                ( CAN_TB_HRH_OFS_6 + CAN_CFG_HRHNUM_6 )


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
CanConst CanTbControllerConfigType Can_tb_stControllerCfgTbl[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /* u1ControllerActivation                , u1ControllerUse                , u1BusoffProcessing                , u1BusoffRecovery                 */
     { (uint8)CAN_CFG_CONTROLLER_ACTIVATION_0, (uint8)CAN_CFG_CONTROLLER_CAN_0, (uint8)CAN_CFG_BUSOFF_PROCESSING_0, (uint8)CAN_CFG_BUSOFF_RECOVERY_0  }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,{ (uint8)CAN_CFG_CONTROLLER_ACTIVATION_1, (uint8)CAN_CFG_CONTROLLER_CAN_1, (uint8)CAN_CFG_BUSOFF_PROCESSING_1, (uint8)CAN_CFG_BUSOFF_RECOVERY_1  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,{ (uint8)CAN_CFG_CONTROLLER_ACTIVATION_2, (uint8)CAN_CFG_CONTROLLER_CAN_2, (uint8)CAN_CFG_BUSOFF_PROCESSING_2, (uint8)CAN_CFG_BUSOFF_RECOVERY_2  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,{ (uint8)CAN_CFG_CONTROLLER_ACTIVATION_3, (uint8)CAN_CFG_CONTROLLER_CAN_3, (uint8)CAN_CFG_BUSOFF_PROCESSING_3, (uint8)CAN_CFG_BUSOFF_RECOVERY_3  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,{ (uint8)CAN_CFG_CONTROLLER_ACTIVATION_4, (uint8)CAN_CFG_CONTROLLER_CAN_4, (uint8)CAN_CFG_BUSOFF_PROCESSING_4, (uint8)CAN_CFG_BUSOFF_RECOVERY_4  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,{ (uint8)CAN_CFG_CONTROLLER_ACTIVATION_5, (uint8)CAN_CFG_CONTROLLER_CAN_5, (uint8)CAN_CFG_BUSOFF_PROCESSING_5, (uint8)CAN_CFG_BUSOFF_RECOVERY_5  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,{ (uint8)CAN_CFG_CONTROLLER_ACTIVATION_6, (uint8)CAN_CFG_CONTROLLER_CAN_6, (uint8)CAN_CFG_BUSOFF_PROCESSING_6, (uint8)CAN_CFG_BUSOFF_RECOVERY_6  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,{ (uint8)CAN_CFG_CONTROLLER_ACTIVATION_7, (uint8)CAN_CFG_CONTROLLER_CAN_7, (uint8)CAN_CFG_BUSOFF_PROCESSING_7, (uint8)CAN_CFG_BUSOFF_RECOVERY_7  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};

CanConst CanTbHohMbAllocType Can_tb_stHohMbAlloc[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /* u2HthOffset                 , u2HrhOffset                 , u1HthNum               , u1HrhNum                 */
    /*,u1HthMbOffset               , u1HrhMbOffset                                                                   */
     { (uint16)CAN_TB_HTH_OFS_0    , (uint16)CAN_TB_HRH_OFS_0    , (uint8)CAN_CFG_HTHNUM_0, (uint8)CAN_CFG_HRHNUM_0
      ,(uint8)CAN_CFG_MB_TXOFFSET_0, (uint8)CAN_CFG_MB_RXOFFSET_0                                                     }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,{ (uint16)CAN_TB_HTH_OFS_1    , (uint16)CAN_TB_HRH_OFS_1    , (uint8)CAN_CFG_HTHNUM_1, (uint8)CAN_CFG_HRHNUM_1
     , (uint8)CAN_CFG_MB_TXOFFSET_1, (uint8)CAN_CFG_MB_RXOFFSET_1                                                     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,{ (uint16)CAN_TB_HTH_OFS_2    , (uint16)CAN_TB_HRH_OFS_2    , (uint8)CAN_CFG_HTHNUM_2, (uint8)CAN_CFG_HRHNUM_2
      ,(uint8)CAN_CFG_MB_TXOFFSET_2, (uint8)CAN_CFG_MB_RXOFFSET_2                                                     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,{ (uint16)CAN_TB_HTH_OFS_3    , (uint16)CAN_TB_HRH_OFS_3    , (uint8)CAN_CFG_HTHNUM_3, (uint8)CAN_CFG_HRHNUM_3
      ,(uint8)CAN_CFG_MB_TXOFFSET_3, (uint8)CAN_CFG_MB_RXOFFSET_3                                                     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,{ (uint16)CAN_TB_HTH_OFS_4    , (uint16)CAN_TB_HRH_OFS_4    , (uint8)CAN_CFG_HTHNUM_4, (uint8)CAN_CFG_HRHNUM_4
      ,(uint8)CAN_CFG_MB_TXOFFSET_4, (uint8)CAN_CFG_MB_RXOFFSET_4                                                     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,{ (uint16)CAN_TB_HTH_OFS_5    , (uint16)CAN_TB_HRH_OFS_5    , (uint8)CAN_CFG_HTHNUM_5, (uint8)CAN_CFG_HRHNUM_5
      ,(uint8)CAN_CFG_MB_TXOFFSET_5, (uint8)CAN_CFG_MB_RXOFFSET_5                                                     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,{ (uint16)CAN_TB_HTH_OFS_6    , (uint16)CAN_TB_HRH_OFS_6    , (uint8)CAN_CFG_HTHNUM_6, (uint8)CAN_CFG_HRHNUM_6
      ,(uint8)CAN_CFG_MB_TXOFFSET_6, (uint8)CAN_CFG_MB_RXOFFSET_6                                                     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,{ (uint16)CAN_TB_HTH_OFS_7    , (uint16)CAN_TB_HRH_OFS_7    , (uint8)CAN_CFG_HTHNUM_7, (uint8)CAN_CFG_HRHNUM_7
      ,(uint8)CAN_CFG_MB_TXOFFSET_7, (uint8)CAN_CFG_MB_RXOFFSET_7                                                     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};

#if (CAN_CFG_TRANSMIT == CAN_USE)
CanConst CanHohCfgType * CanConst Can_tb_ptHohCfgTbl = &(Can_stHohCfgTbl[ CAN_IDX0 ]);
#endif /*  (CAN_CFG_TRANSMIT == CAN_USE) */

CanConst uint8 Can_tb_u1RegChkNum = (uint8)CAN_CFG_CHKSTKREG_LIMIT;

CanConst uint8 Can_tb_u1ControllerNumMax = (uint8)CAN_CFG_CONTROLLERNUM_MAX;

#if (CAN_CFG_TRANSMIT == CAN_USE)
CanConst uint16 Can_tb_u2HrhNumMax = (uint16)CAN_TB_HRHNUM_MAX;
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */

#if (CAN_CFG_TRANSMIT == CAN_USE)
CanConst uint16 Can_tb_u2HthNumMax = (uint16)CAN_TB_HTHNUM_MAX;
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */

#if (CAN_CFG_TRANSMIT == CAN_USE)
#if (CAN_CFG_USER_TRANSMIT == CAN_USE)
CanConst CanTbUTxMbAllocType Can_tb_stUTxMbAlloc[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /* u1UTxMbOffset                ,  u1UTxMbNum                   */
     { (uint8)CAN_CFG_MB_UTXOFFSET_0, (uint8)CAN_CFG_USERTXMBOXNUM_0 }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,{ (uint8)CAN_CFG_MB_UTXOFFSET_1, (uint8)CAN_CFG_USERTXMBOXNUM_1 }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,{ (uint8)CAN_CFG_MB_UTXOFFSET_2, (uint8)CAN_CFG_USERTXMBOXNUM_2 }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,{ (uint8)CAN_CFG_MB_UTXOFFSET_3, (uint8)CAN_CFG_USERTXMBOXNUM_3 }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,{ (uint8)CAN_CFG_MB_UTXOFFSET_4, (uint8)CAN_CFG_USERTXMBOXNUM_4 }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,{ (uint8)CAN_CFG_MB_UTXOFFSET_5, (uint8)CAN_CFG_USERTXMBOXNUM_5 }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,{ (uint8)CAN_CFG_MB_UTXOFFSET_6, (uint8)CAN_CFG_USERTXMBOXNUM_6 }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,{ (uint8)CAN_CFG_MB_UTXOFFSET_7, (uint8)CAN_CFG_USERTXMBOXNUM_7 }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};
#endif /* (CAN_CFG_USER_TRANSMIT == CAN_USE) */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-1         :2022/03/09                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
