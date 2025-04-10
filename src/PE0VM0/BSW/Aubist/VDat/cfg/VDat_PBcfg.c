/* vdat_pbcfg_c_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | VDAT/PBCFG/CODE                                           */
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
#include "./VDat_Cfg.h"

#if ( BSW_VDAT_CFG_FUNC_VDAT == BSW_VDAT_USE )
#include "../inc/bsw_vdat_trx.h"

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
/* Connection 0 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 0U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_00[ BSW_VDAT_CFG_NODE_NUM00 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 0U */

/* Connection 1 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 1U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_01[ BSW_VDAT_CFG_NODE_NUM01 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 1U */

/* Connection 2 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 2U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_02[ BSW_VDAT_CFG_NODE_NUM02 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 2U */

/* Connection 3 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 3U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_03[ BSW_VDAT_CFG_NODE_NUM03 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 3U */

/* Connection 4 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 4U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_04[ BSW_VDAT_CFG_NODE_NUM04 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 4U */

/* Connection 5 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 5U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_05[ BSW_VDAT_CFG_NODE_NUM05 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 5U */

/* Connection 6 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 6U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_06[ BSW_VDAT_CFG_NODE_NUM06 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 6U */

/* Connection 7 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 7U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_07[ BSW_VDAT_CFG_NODE_NUM07 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 7U */

/* Connection 8 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 8U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_08[ BSW_VDAT_CFG_NODE_NUM08 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 8U */

/* Connection 9 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 9U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_09[ BSW_VDAT_CFG_NODE_NUM09 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 9U */

/* Connection 10 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 10U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_10[ BSW_VDAT_CFG_NODE_NUM10 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 10U */

/* Connection 11 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 11U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_11[ BSW_VDAT_CFG_NODE_NUM11 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 11U */

/* Connection 12 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 12U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_12[ BSW_VDAT_CFG_NODE_NUM12 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 12U */

/* Connection 13 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 13U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_13[ BSW_VDAT_CFG_NODE_NUM13 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 13U */

/* Connection 14 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 14U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_14[ BSW_VDAT_CFG_NODE_NUM14 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 14U */

/* Connection 15 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 15U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_15[ BSW_VDAT_CFG_NODE_NUM15 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 15U */

/* Connection 16 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 16U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_16[ BSW_VDAT_CFG_NODE_NUM16 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 16U */

/* Connection 17 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 17U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_17[ BSW_VDAT_CFG_NODE_NUM17 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 17U */

/* Connection 18 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 18U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_18[ BSW_VDAT_CFG_NODE_NUM18 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 18U */

/* Connection 19 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 19U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_19[ BSW_VDAT_CFG_NODE_NUM19 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 19U */

/* Connection 20 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 20U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_20[ BSW_VDAT_CFG_NODE_NUM20 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 20U */

/* Connection 21 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 21U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_21[ BSW_VDAT_CFG_NODE_NUM21 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 21U */

/* Connection 22 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 22U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_22[ BSW_VDAT_CFG_NODE_NUM22 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 22U */

/* Connection 23 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 23U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_23[ BSW_VDAT_CFG_NODE_NUM23 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 23U */

/* Connection 24 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 24U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_24[ BSW_VDAT_CFG_NODE_NUM24 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 24U */

/* Connection 25 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 25U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_25[ BSW_VDAT_CFG_NODE_NUM25 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 25U */

/* Connection 26 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 26U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_26[ BSW_VDAT_CFG_NODE_NUM26 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 26U */

/* Connection 27 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 27U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_27[ BSW_VDAT_CFG_NODE_NUM27 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 27U */

/* Connection 28 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 28U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_28[ BSW_VDAT_CFG_NODE_NUM28 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 28U */

/* Connection 29 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 29U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_29[ BSW_VDAT_CFG_NODE_NUM29 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 29U */

/* Connection 30 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 30U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_30[ BSW_VDAT_CFG_NODE_NUM30 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 30U */

/* Connection 31 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 31U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_31[ BSW_VDAT_CFG_NODE_NUM31 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 31U */

/* Connection 32 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 32U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_32[ BSW_VDAT_CFG_NODE_NUM32 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 32U */

/* Connection 33 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 33U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_33[ BSW_VDAT_CFG_NODE_NUM33 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 33U */

/* Connection 34 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 34U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_34[ BSW_VDAT_CFG_NODE_NUM34 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 34U */

/* Connection 35 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 35U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_35[ BSW_VDAT_CFG_NODE_NUM35 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 35U */

/* Connection 36 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 36U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_36[ BSW_VDAT_CFG_NODE_NUM36 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 36U */

/* Connection 37 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 37U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_37[ BSW_VDAT_CFG_NODE_NUM37 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 37U */

/* Connection 38 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 38U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_38[ BSW_VDAT_CFG_NODE_NUM38 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 38U */

/* Connection 39 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 39U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_39[ BSW_VDAT_CFG_NODE_NUM39 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 39U */

/* Connection 40 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 40U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_40[ BSW_VDAT_CFG_NODE_NUM40 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 40U */

/* Connection 41 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 41U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_41[ BSW_VDAT_CFG_NODE_NUM41 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 41U */

/* Connection 42 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 42U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_42[ BSW_VDAT_CFG_NODE_NUM42 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 42U */

/* Connection 43 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 43U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_43[ BSW_VDAT_CFG_NODE_NUM43 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 43U */

/* Connection 44 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 44U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_44[ BSW_VDAT_CFG_NODE_NUM44 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 44U */

/* Connection 45 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 45U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_45[ BSW_VDAT_CFG_NODE_NUM45 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 45U */

/* Connection 46 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 46U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_46[ BSW_VDAT_CFG_NODE_NUM46 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 46U */

/* Connection 47 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 47U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_47[ BSW_VDAT_CFG_NODE_NUM47 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 47U */

/* Connection 48 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 48U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_48[ BSW_VDAT_CFG_NODE_NUM48 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 48U */

/* Connection 49 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 49U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_49[ BSW_VDAT_CFG_NODE_NUM49 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 49U */

/* Connection 50 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 50U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_50[ BSW_VDAT_CFG_NODE_NUM50 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 50U */

/* Connection 51 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 51U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_51[ BSW_VDAT_CFG_NODE_NUM51 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 51U */

/* Connection 52 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 52U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_52[ BSW_VDAT_CFG_NODE_NUM52 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 52U */

/* Connection 53 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 53U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_53[ BSW_VDAT_CFG_NODE_NUM53 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 53U */

/* Connection 54 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 54U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_54[ BSW_VDAT_CFG_NODE_NUM54 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 54U */

/* Connection 55 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 55U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_55[ BSW_VDAT_CFG_NODE_NUM55 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 55U */

/* Connection 56 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 56U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_56[ BSW_VDAT_CFG_NODE_NUM56 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 56U */

/* Connection 57 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 57U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_57[ BSW_VDAT_CFG_NODE_NUM57 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 57U */

/* Connection 58 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 58U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_58[ BSW_VDAT_CFG_NODE_NUM58 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 58U */

/* Connection 59 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 59U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_59[ BSW_VDAT_CFG_NODE_NUM59 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 59U */

/* Connection 60 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 60U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_60[ BSW_VDAT_CFG_NODE_NUM60 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 60U */

/* Connection 61 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 61U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_61[ BSW_VDAT_CFG_NODE_NUM61 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 61U */

/* Connection 62 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 62U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_62[ BSW_VDAT_CFG_NODE_NUM62 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 62U */

/* Connection 63 */
#if ( BSW_VDAT_CFG_CONNECTION_NUM > 63U )
BswConst BswU4 bsw_vdat_u4QueueIDTbl_63[ BSW_VDAT_CFG_NODE_NUM63 ] =
{
};
#endif /* BSW_VDAT_CFG_CONNECTION_NUM > 63U */

#endif /* BSW_VDAT_CFG_FUNC_VDAT == BSW_VDAT_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/02/02                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
