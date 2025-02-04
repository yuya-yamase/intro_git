/* bsw_cannm_ch_config_c_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/CH/CONFIG/CODE                                  */
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
#include <cannm/bsw_cannm_cbk.h>
#include "../../inc/common/bsw_cannm_ch.h"

#include "../../inc/bsw_cannm_config.h"
#include "../../../Nm/inc/bsw_nm_config.h"

#if( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#include "../../../Com/inc/bsw_com_config.h"
#endif


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANNM_CHNUM                        (BSW_COMM_BUS_TYPE_CHNUM(CAN))
#define BSW_CANNM_CH_OFFSET                    (BSW_COMM_BUS_TYPE_OFFSET(CAN))
#if( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#define BSW_CANNM_CH_EVTWAKEUPFRAME_USE        (BSW_COM_EVENTWAKEUPFRAME_USE)
#else
#define BSW_CANNM_CH_EVTWAKEUPFRAME_USE        (BSW_NOUSE)
#endif

/* Subcomponent Index, public function table size (needs to be edited when adding subcomponents) */
#define BSW_CANNM_FUNCTBL_NONE            (0U)
#define BSW_CANNM_FUNCTBL_Z               (1U)
#define BSW_CANNM_FUNCTBL_A               (2U)
#define BSW_CANNM_FUNCTBL_A2              (3U)
#define BSW_CANNM_FUNCTBL_B               (4U)
#define BSW_CANNM_FUNCTBL_C2              (5U)
#define BSW_CANNM_FUNCTBL_E               (6U)
#define BSW_CANNM_FUNCTBL_X               (7U)
#define BSW_CANNM_FUNCTBL_Y               (8U)
#define BSW_CANNM_FUNCTBL_SIZE            (9U)

/* Number of function tables registered for each NM type (needs to be edited when adding subcomponents) */
#if ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE )
#define BSW_CANNM_NMTYPE_Z_FUNCTBL_NUM (1U)
#else
#define BSW_CANNM_NMTYPE_Z_FUNCTBL_NUM (0U)
#endif /* ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE )
#define BSW_CANNM_NMTYPE_A_FUNCTBL_NUM (1U)
#else
#define BSW_CANNM_NMTYPE_A_FUNCTBL_NUM (0U)
#endif /* ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
#define BSW_CANNM_NMTYPE_A2_FUNCTBL_NUM (1U)
#else
#define BSW_CANNM_NMTYPE_A2_FUNCTBL_NUM (0U)
#endif /* ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
#define BSW_CANNM_NMTYPE_B_FUNCTBL_NUM (1U)
#else
#define BSW_CANNM_NMTYPE_B_FUNCTBL_NUM (0U)
#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE )
#define BSW_CANNM_NMTYPE_C2_FUNCTBL_NUM (1U)
#else
#define BSW_CANNM_NMTYPE_C2_FUNCTBL_NUM (0U)
#endif /* ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE )
#define BSW_CANNM_NMTYPE_E_FUNCTBL_NUM (1U)
#else
#define BSW_CANNM_NMTYPE_E_FUNCTBL_NUM (0U)
#endif /* ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE )
#define BSW_CANNM_NMTYPE_X_FUNCTBL_NUM (1U)
#else
#define BSW_CANNM_NMTYPE_X_FUNCTBL_NUM (0U)
#endif /* ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
#define BSW_CANNM_NMTYPE_Y_FUNCTBL_NUM (1U)
#else
#define BSW_CANNM_NMTYPE_Y_FUNCTBL_NUM (0U)
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */


#define BSW_CANNM_DMY_FUNCTBL_NUM (1U)

/* Function table registration size only for the NM type used (needs to be edited when adding subcomponents) */
#define BSW_CANNM_FUNCTBL_USE_NM_SIZE \
    ( BSW_CANNM_NMTYPE_Z_FUNCTBL_NUM \
    + BSW_CANNM_NMTYPE_A_FUNCTBL_NUM \
    + BSW_CANNM_NMTYPE_A2_FUNCTBL_NUM \
    + BSW_CANNM_NMTYPE_B_FUNCTBL_NUM \
    + BSW_CANNM_NMTYPE_C2_FUNCTBL_NUM \
    + BSW_CANNM_NMTYPE_E_FUNCTBL_NUM \
    + BSW_CANNM_NMTYPE_X_FUNCTBL_NUM \
    + BSW_CANNM_NMTYPE_Y_FUNCTBL_NUM \
    + BSW_CANNM_DMY_FUNCTBL_NUM )

/* Channel to subcomponent Index conversion (needs to be edited when adding subcomponents) */
#define BSW_CANNM_IDX_NM(ch)             (BSW_CANNM_IDX_CONV_Z(ch))
#define BSW_CANNM_IDX_CONV_Z(ch)         ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_Z)  ? BSW_CANNM_FUNCTBL_Z  : BSW_CANNM_IDX_CONV_A(ch))
#define BSW_CANNM_IDX_CONV_A(ch)         ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_A)  ? BSW_CANNM_FUNCTBL_A  : BSW_CANNM_IDX_CONV_A2(ch))
#define BSW_CANNM_IDX_CONV_A2(ch)        ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_A2) ? BSW_CANNM_FUNCTBL_A2 : BSW_CANNM_IDX_CONV_B(ch))
#define BSW_CANNM_IDX_CONV_B(ch)         ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_B)  ? BSW_CANNM_FUNCTBL_B  : BSW_CANNM_IDX_CONV_C2(ch))
#define BSW_CANNM_IDX_CONV_C2(ch)        ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_C2) ? BSW_CANNM_FUNCTBL_C2 : BSW_CANNM_IDX_CONV_E(ch))
#define BSW_CANNM_IDX_CONV_E(ch)         ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_E)  ? BSW_CANNM_FUNCTBL_E  : BSW_CANNM_IDX_CONV_X(ch))
#define BSW_CANNM_IDX_CONV_X(ch)         ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_X)  ? BSW_CANNM_FUNCTBL_X  : BSW_CANNM_IDX_CONV_Y(ch))
#define BSW_CANNM_IDX_CONV_Y(ch)         ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_Y)  ? BSW_CANNM_FUNCTBL_Y  : BSW_CANNM_FUNCTBL_NONE)

/* Channel number -> Number of NM-PDUs (needs to be edited when adding subcomponents) */
#define BSW_CANNM_PDUNUM(ch)               (BSW_CANNM_PDUNUM_Z(ch))
#define BSW_CANNM_PDUNUM_Z(ch)             ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_Z)   ? CANNM_Z_PDU_NUM        : BSW_CANNM_PDUNUM_A(ch))
#define BSW_CANNM_PDUNUM_A(ch)             ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_A)   ? CANNM_A_PDU_NUM        : BSW_CANNM_PDUNUM_A2(ch))
#define BSW_CANNM_PDUNUM_A2(ch)            ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_A2)  ? CANNM_A2_PDU_NUM       : BSW_CANNM_PDUNUM_B(ch))
#define BSW_CANNM_PDUNUM_B(ch)             ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_B)   ? CANNM_B_PDU_NUM        : BSW_CANNM_PDUNUM_C2(ch))
#define BSW_CANNM_PDUNUM_C2(ch)            ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_C2)  ? CANNM_C2_PDU_NUM       : BSW_CANNM_PDUNUM_E(ch))
#define BSW_CANNM_PDUNUM_E(ch)             ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_E)   ? CANNM_E_PDU_NUM        : BSW_CANNM_PDUNUM_X(ch))
#define BSW_CANNM_PDUNUM_X(ch)             ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_X)   ? CANNM_X_PDU_NUM        : BSW_CANNM_PDUNUM_Y(ch))
#define BSW_CANNM_PDUNUM_Y(ch)             ((BSW_CANNM_NM_TYPE(ch) == BSW_CANNM_NMTYPE_Y)   ? CANNM_Y_PDU_NUM        : (0U))

/* NM-PDU per channel */
#define BSW_CANNM_PDUID_OFFSET_0           (0U)
#define BSW_CANNM_PDUID_OFFSET_1           (BSW_CANNM_PDUID_OFFSET_0  + BSW_CANNM_PDUNUM( 0 ))
#define BSW_CANNM_PDUID_OFFSET_2           (BSW_CANNM_PDUID_OFFSET_1  + BSW_CANNM_PDUNUM( 1 ))
#define BSW_CANNM_PDUID_OFFSET_3           (BSW_CANNM_PDUID_OFFSET_2  + BSW_CANNM_PDUNUM( 2 ))
#define BSW_CANNM_PDUID_OFFSET_4           (BSW_CANNM_PDUID_OFFSET_3  + BSW_CANNM_PDUNUM( 3 ))
#define BSW_CANNM_PDUID_OFFSET_5           (BSW_CANNM_PDUID_OFFSET_4  + BSW_CANNM_PDUNUM( 4 ))
#define BSW_CANNM_PDUID_OFFSET_6           (BSW_CANNM_PDUID_OFFSET_5  + BSW_CANNM_PDUNUM( 5 ))
#define BSW_CANNM_PDUID_OFFSET_7           (BSW_CANNM_PDUID_OFFSET_6  + BSW_CANNM_PDUNUM( 6 ))
#define BSW_CANNM_PDUID_OFFSET_8           (BSW_CANNM_PDUID_OFFSET_7  + BSW_CANNM_PDUNUM( 7 ))
#define BSW_CANNM_PDUID_OFFSET_9           (BSW_CANNM_PDUID_OFFSET_8  + BSW_CANNM_PDUNUM( 8 ))
#define BSW_CANNM_PDUID_OFFSET_10          (BSW_CANNM_PDUID_OFFSET_9  + BSW_CANNM_PDUNUM( 9 ))
#define BSW_CANNM_PDUID_OFFSET_11          (BSW_CANNM_PDUID_OFFSET_10  + BSW_CANNM_PDUNUM( 10 ))
#define BSW_CANNM_PDUID_OFFSET_12          (BSW_CANNM_PDUID_OFFSET_11  + BSW_CANNM_PDUNUM( 11 ))
#define BSW_CANNM_PDUID_OFFSET_13          (BSW_CANNM_PDUID_OFFSET_12  + BSW_CANNM_PDUNUM( 12 ))
#define BSW_CANNM_PDUID_OFFSET_14          (BSW_CANNM_PDUID_OFFSET_13  + BSW_CANNM_PDUNUM( 13 ))
#define BSW_CANNM_PDUID_OFFSET_15          (BSW_CANNM_PDUID_OFFSET_14  + BSW_CANNM_PDUNUM( 14 ))
#define BSW_CANNM_PDUID_OFFSET_16          (BSW_CANNM_PDUID_OFFSET_15  + BSW_CANNM_PDUNUM( 15 ))
#define BSW_CANNM_PDUID_OFFSET_17          (BSW_CANNM_PDUID_OFFSET_16  + BSW_CANNM_PDUNUM( 16 ))
#define BSW_CANNM_PDUID_OFFSET_18          (BSW_CANNM_PDUID_OFFSET_17  + BSW_CANNM_PDUNUM( 17 ))
#define BSW_CANNM_PDUID_OFFSET_19          (BSW_CANNM_PDUID_OFFSET_18  + BSW_CANNM_PDUNUM( 18 ))
#define BSW_CANNM_PDUID_OFFSET_20          (BSW_CANNM_PDUID_OFFSET_19  + BSW_CANNM_PDUNUM( 19 ))
#define BSW_CANNM_PDUID_OFFSET_21          (BSW_CANNM_PDUID_OFFSET_20  + BSW_CANNM_PDUNUM( 20 ))
#define BSW_CANNM_PDUID_OFFSET_22          (BSW_CANNM_PDUID_OFFSET_21  + BSW_CANNM_PDUNUM( 21 ))
#define BSW_CANNM_PDUID_OFFSET_23          (BSW_CANNM_PDUID_OFFSET_22  + BSW_CANNM_PDUNUM( 22 ))
#define BSW_CANNM_PDUID_OFFSET_24          (BSW_CANNM_PDUID_OFFSET_23  + BSW_CANNM_PDUNUM( 23 ))
#define BSW_CANNM_PDUID_OFFSET_25          (BSW_CANNM_PDUID_OFFSET_24  + BSW_CANNM_PDUNUM( 24 ))
#define BSW_CANNM_PDUID_OFFSET_26          (BSW_CANNM_PDUID_OFFSET_25  + BSW_CANNM_PDUNUM( 25 ))
#define BSW_CANNM_PDUID_OFFSET_27          (BSW_CANNM_PDUID_OFFSET_26  + BSW_CANNM_PDUNUM( 26 ))
#define BSW_CANNM_PDUID_OFFSET_28          (BSW_CANNM_PDUID_OFFSET_27  + BSW_CANNM_PDUNUM( 27 ))
#define BSW_CANNM_PDUID_OFFSET_29          (BSW_CANNM_PDUID_OFFSET_28  + BSW_CANNM_PDUNUM( 28 ))
#define BSW_CANNM_PDUID_OFFSET_30          (BSW_CANNM_PDUID_OFFSET_29  + BSW_CANNM_PDUNUM( 29 ))
#define BSW_CANNM_PDUID_OFFSET_31          (BSW_CANNM_PDUID_OFFSET_30  + BSW_CANNM_PDUNUM( 30 ))

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
BswConst   BswU1               bsw_cannm_ch_u1ChOffset  = (BswU1)BSW_CANNM_CH_OFFSET;     /* NM channel offset */
BswConst   BswU1               bsw_cannm_ch_u1FuncTblSize = (BswU1)BSW_CANNM_FUNCTBL_SIZE; /* Function table size */
BswConst   BswU1               bsw_cannm_ch_u1UseNmTypeNum = (BswU1)(BSW_CANNM_FUNCTBL_USE_NM_SIZE - BSW_CANNM_DMY_FUNCTBL_NUM); /* Number of NM types to use */

/* Channel number -> Function table index conversion */
BswConst BswU1 bsw_cannm_ch_u1Ch2IdxTbl[BSW_CANNM_CHNUM] = {
    (BswU1)BSW_CANNM_IDX_NM(0)
#if (BSW_CANNM_CHNUM > 1U)
   ,(BswU1)BSW_CANNM_IDX_NM(1)
#endif
#if (BSW_CANNM_CHNUM > 2U)
   ,(BswU1)BSW_CANNM_IDX_NM(2)
#endif
#if (BSW_CANNM_CHNUM > 3U)
   ,(BswU1)BSW_CANNM_IDX_NM(3)
#endif
#if (BSW_CANNM_CHNUM > 4U)
   ,(BswU1)BSW_CANNM_IDX_NM(4)
#endif
#if (BSW_CANNM_CHNUM > 5U)
   ,(BswU1)BSW_CANNM_IDX_NM(5)
#endif
#if (BSW_CANNM_CHNUM > 6U)
   ,(BswU1)BSW_CANNM_IDX_NM(6)
#endif
#if (BSW_CANNM_CHNUM > 7U)
   ,(BswU1)BSW_CANNM_IDX_NM(7)
#endif
#if (BSW_CANNM_CHNUM > 8U)
   ,(BswU1)BSW_CANNM_IDX_NM(8)
#endif
#if (BSW_CANNM_CHNUM > 9U)
   ,(BswU1)BSW_CANNM_IDX_NM(9)
#endif
#if (BSW_CANNM_CHNUM > 10U)
   ,(BswU1)BSW_CANNM_IDX_NM(10)
#endif
#if (BSW_CANNM_CHNUM > 11U)
   ,(BswU1)BSW_CANNM_IDX_NM(11)
#endif
#if (BSW_CANNM_CHNUM > 12U)
   ,(BswU1)BSW_CANNM_IDX_NM(12)
#endif
#if (BSW_CANNM_CHNUM > 13U)
   ,(BswU1)BSW_CANNM_IDX_NM(13)
#endif
#if (BSW_CANNM_CHNUM > 14U)
   ,(BswU1)BSW_CANNM_IDX_NM(14)
#endif
#if (BSW_CANNM_CHNUM > 15U)
   ,(BswU1)BSW_CANNM_IDX_NM(15)
#endif
#if (BSW_CANNM_CHNUM > 16U)
   ,(BswU1)BSW_CANNM_IDX_NM(16)
#endif
#if (BSW_CANNM_CHNUM > 17U)
   ,(BswU1)BSW_CANNM_IDX_NM(17)
#endif
#if (BSW_CANNM_CHNUM > 18U)
   ,(BswU1)BSW_CANNM_IDX_NM(18)
#endif
#if (BSW_CANNM_CHNUM > 19U)
   ,(BswU1)BSW_CANNM_IDX_NM(19)
#endif
#if (BSW_CANNM_CHNUM > 20U)
   ,(BswU1)BSW_CANNM_IDX_NM(20)
#endif
#if (BSW_CANNM_CHNUM > 21U)
   ,(BswU1)BSW_CANNM_IDX_NM(21)
#endif
#if (BSW_CANNM_CHNUM > 22U)
   ,(BswU1)BSW_CANNM_IDX_NM(22)
#endif
#if (BSW_CANNM_CHNUM > 23U)
   ,(BswU1)BSW_CANNM_IDX_NM(23)
#endif
#if (BSW_CANNM_CHNUM > 24U)
   ,(BswU1)BSW_CANNM_IDX_NM(24)
#endif
#if (BSW_CANNM_CHNUM > 25U)
   ,(BswU1)BSW_CANNM_IDX_NM(25)
#endif
#if (BSW_CANNM_CHNUM > 26U)
   ,(BswU1)BSW_CANNM_IDX_NM(26)
#endif
#if (BSW_CANNM_CHNUM > 27U)
   ,(BswU1)BSW_CANNM_IDX_NM(27)
#endif
#if (BSW_CANNM_CHNUM > 28U)
   ,(BswU1)BSW_CANNM_IDX_NM(28)
#endif
#if (BSW_CANNM_CHNUM > 29U)
   ,(BswU1)BSW_CANNM_IDX_NM(29)
#endif
#if (BSW_CANNM_CHNUM > 30U)
   ,(BswU1)BSW_CANNM_IDX_NM(30)
#endif
#if (BSW_CANNM_CHNUM > 31U)
   ,(BswU1)BSW_CANNM_IDX_NM(31)
#endif
};

/* Table to judge whether bus-sleep is used or not */
BswConst BswU1 bsw_cannm_ch_u1BusSleepTbl[BSW_CANNM_CHNUM] =
{
    (BswU1)BSW_CANNM_BUSSLEEP_USE(0U)
#if (BSW_CANNM_CHNUM > 1U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(1U)
#endif
#if (BSW_CANNM_CHNUM > 2U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(2U)
#endif
#if (BSW_CANNM_CHNUM > 3U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(3U)
#endif
#if (BSW_CANNM_CHNUM > 4U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(4U)
#endif
#if (BSW_CANNM_CHNUM > 5U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(5U)
#endif
#if (BSW_CANNM_CHNUM > 6U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(6U)
#endif
#if (BSW_CANNM_CHNUM > 7U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(7U)
#endif
#if (BSW_CANNM_CHNUM > 8U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(8U)
#endif
#if (BSW_CANNM_CHNUM > 9U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(9U)
#endif
#if (BSW_CANNM_CHNUM > 10U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(10U)
#endif
#if (BSW_CANNM_CHNUM > 11U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(11U)
#endif
#if (BSW_CANNM_CHNUM > 12U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(12U)
#endif
#if (BSW_CANNM_CHNUM > 13U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(13U)
#endif
#if (BSW_CANNM_CHNUM > 14U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(14U)
#endif
#if (BSW_CANNM_CHNUM > 15U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(15U)
#endif
#if (BSW_CANNM_CHNUM > 16U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(16U)
#endif
#if (BSW_CANNM_CHNUM > 17U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(17U)
#endif
#if (BSW_CANNM_CHNUM > 18U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(18U)
#endif
#if (BSW_CANNM_CHNUM > 19U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(19U)
#endif
#if (BSW_CANNM_CHNUM > 20U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(20U)
#endif
#if (BSW_CANNM_CHNUM > 21U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(21U)
#endif
#if (BSW_CANNM_CHNUM > 22U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(22U)
#endif
#if (BSW_CANNM_CHNUM > 23U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(23U)
#endif
#if (BSW_CANNM_CHNUM > 24U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(24U)
#endif
#if (BSW_CANNM_CHNUM > 25U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(25U)
#endif
#if (BSW_CANNM_CHNUM > 26U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(26U)
#endif
#if (BSW_CANNM_CHNUM > 27U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(27U)
#endif
#if (BSW_CANNM_CHNUM > 28U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(28U)
#endif
#if (BSW_CANNM_CHNUM > 29U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(29U)
#endif
#if (BSW_CANNM_CHNUM > 30U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(30U)
#endif
#if (BSW_CANNM_CHNUM > 31U)
   ,(BswU1)BSW_CANNM_BUSSLEEP_USE(31U)
#endif
};

/************************************************/
/* CanNm Function definition when not in use                       */
/************************************************/
static BswConst Bsw_CanNm_FuncTblType bsw_cannm_ch_ptNotIndFuncTbl = 
{
      &bsw_cannm_ch_InitNone
    , &bsw_cannm_ch_DeInitNone
    , &bsw_cannm_ch_MainFuncNone
    , &bsw_cannm_ch_CheckAwakeNone
    , &bsw_cannm_ch_PassiveStrtUpNone
    , &bsw_cannm_ch_NetworkReqNone
    , &bsw_cannm_ch_NetworkRelNone
    , &bsw_cannm_ch_GetStateNone
    , &bsw_cannm_ch_GetIPDUStateNone
    , &bsw_cannm_ch_SetBusOffNone
    , &bsw_cannm_ch_TxConfirmationNone
    , &bsw_cannm_ch_RxIndicationNone
};

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
static BswConst Bsw_CanNm_SlpFuncTblType bsw_cannm_ch_ptNotIndSlpFuncTbl = 
{
      &bsw_cannm_ch_WakeupNone
    , &bsw_cannm_ch_SleepNone
    , &bsw_cannm_ch_GetBackupDataNone
    , &bsw_cannm_ch_SetBackupDataNone
};
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

#if( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_CanNm_ComFuncTblType bsw_cannm_ch_ptNotIndComFuncTbl = 
{
      &bsw_cannm_ch_DisableComNone
    , &bsw_cannm_ch_EnableComNone
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */

#if ( BSW_NM_USER_DATA == BSW_USE )
static BswConst Bsw_CanNm_UsrDatFuncTblType bsw_cannm_ch_ptNotIndUDFuncTbl = 
{
      &bsw_cannm_ch_SetUserDataNone
    , &bsw_cannm_ch_GetUserDataNone
};
#endif /* ( BSW_NM_USER_DATA == BSW_USE ) */

#if ( BSW_NM_NODE_ID == BSW_USE )
static BswConst Bsw_CanNm_NodeFuncTblType bsw_cannm_ch_ptNotIndNodFuncTbl = 
{
      &bsw_cannm_ch_GetNodeIdNone
    , &bsw_cannm_ch_GetLNodeIdNone
};
#endif /* ( BSW_NM_NODE_ID == BSW_USE ) */

#if ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) )
static BswConst Bsw_CanNm_PduFuncTblType bsw_cannm_ch_ptNotIndPduFuncTbl = 
{
      &bsw_cannm_ch_GetPduDataNone
};
#endif /* ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) ) */

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
static BswConst Bsw_CanNm_ChkRamFuncTblType bsw_cannm_ch_ptNotIndChkFuncTbl = 
{
      &bsw_cannm_ch_CheckRamNone
};
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */

#if (BSW_NM_SYNC_PNC_SHUTDOWN == BSW_USE)
static BswConst Bsw_CanNm_SyncPncSlpFuncTblType bsw_cannm_ch_ptNotIndPnSFuncTbl = 
{
      &bsw_cannm_ch_ReqSyncPncSlpNone
    , &bsw_cannm_ch_CancelSyncPncSlpNone
};
#endif /* (BSW_NM_SYNC_PNC_SHUTDOWN == BSW_USE) */

/************************************************/
/* CanNmZ public function definition                          */
/************************************************/
#if ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE )
static BswConst Bsw_CanNm_FuncTblType bsw_cannm_ch_ptZFuncTbl = 
{
      &CanNmZ_Init
    , &CanNmZ_DeInit
    , &CanNmZ_MainFunction
    , &bsw_cannm_ch_CheckAwakeNone
    , &bsw_cannm_ch_PassiveStrtUpNone
    , &CanNmZ_NetworkRequest
    , &CanNmZ_NetworkRelease
    , &CanNmZ_GetState
    , &CanNmZ_GetIPDUState
    , &bsw_cannm_ch_SetBusOffNone
    , &bsw_cannm_ch_TxConfirmationNone
    , &bsw_cannm_ch_RxIndicationNone
};

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
static BswConst Bsw_CanNm_SlpFuncTblType bsw_cannm_ch_ptZSlpFuncTbl = 
{
      &CanNmZ_Init
    , &CanNmZ_DeInit
    , &bsw_cannm_ch_GetBackupDataNone
    , &bsw_cannm_ch_SetBackupDataNone
};
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
static BswConst Bsw_CanNm_ChkRamFuncTblType bsw_cannm_ch_ptZChkRamFuncTbl = 
{
      &CanNmZ_CheckRam
};
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */
#endif /* ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE ) */

/************************************************/
/* CanNmA Public function definition                          */
/************************************************/
#if ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE )
static BswConst Bsw_CanNm_FuncTblType bsw_cannm_ch_ptAFuncTbl = 
{
      &CanNmA_Init
    , &CanNmA_DeInit
    , &CanNmA_MainFunction
    , &CanNmA_CheckAwake
    , &CanNmA_PassiveStartUp
    , &CanNmA_NetworkRequest
    , &CanNmA_NetworkRelease
    , &CanNmA_GetState
    , &CanNmA_GetIPDUState
    , &CanNmA_SetBusOff
    , &CanNmA_TxConfirmation
    , &CanNmA_RxIndication
};

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
static BswConst Bsw_CanNm_SlpFuncTblType bsw_cannm_ch_ptASlpFuncTbl = 
{
      &CanNmA_Wakeup
    , &CanNmA_Sleep
    , &CanNmA_GetBackupData
    , &CanNmA_SetBackupData
};
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

#if( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_CanNm_ComFuncTblType bsw_cannm_ch_ptAComFuncTbl = 
{
      &CanNmA_DisableCommunication
    , &CanNmA_EnableCommunication
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
static BswConst Bsw_CanNm_ChkRamFuncTblType bsw_cannm_ch_ptAChkRamFuncTbl = 
{
      &CanNmA_CheckRam
};
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */
#endif /* ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE ) */


/************************************************/
/* CanNmA Public function definition                         */
/************************************************/
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
static BswConst Bsw_CanNm_FuncTblType bsw_cannm_ch_ptA2FuncTbl = 
{
      &CanNmA2_Init
    , &CanNmA2_DeInit
    , &CanNmA2_MainFunction
    , &CanNmA2_CheckAwake
    , &CanNmA2_PassiveStartUp
    , &CanNmA2_NetworkRequest
    , &CanNmA2_NetworkRelease
    , &CanNmA2_GetState
    , &CanNmA2_GetIPDUState
    , &CanNmA2_SetBusOff
    , &CanNmA2_TxConfirmation
    , &CanNmA2_RxIndication
};

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
static BswConst Bsw_CanNm_SlpFuncTblType bsw_cannm_ch_ptA2SlpFuncTbl = 
{
      &CanNmA2_Wakeup
    , &CanNmA2_Sleep
    , &bsw_cannm_ch_GetBackupDataNone
    , &bsw_cannm_ch_SetBackupDataNone
};
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

#if( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_CanNm_ComFuncTblType bsw_cannm_ch_ptA2ComFuncTbl = 
{
      &CanNmA2_DisableCommunication
    , &CanNmA2_EnableCommunication
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */
#if ( BSW_NM_USER_DATA == BSW_USE )
static BswConst Bsw_CanNm_UsrDatFuncTblType bsw_cannm_ch_ptA2UsrDatFuncTbl = 
{
      &CanNmA2_SetUserData
    , &CanNmA2_GetUserData
 };
#endif /* ( BSW_NM_USER_DATA == BSW_USE ) */

#if ( BSW_NM_NODE_ID == BSW_USE )
static BswConst Bsw_CanNm_NodeFuncTblType bsw_cannm_ch_ptA2NodeFuncTbl = 
{
      &CanNmA2_GetNodeIdentifier
    , &CanNmA2_GetLocalNodeIdentifier
 };
#endif /* ( BSW_NM_NODE_ID == BSW_USE ) */

#if ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) )
static BswConst Bsw_CanNm_PduFuncTblType bsw_cannm_ch_ptA2PduFuncTbl = 
{
      &CanNmA2_GetPduData
 };
#endif /* ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) ) */

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
static BswConst Bsw_CanNm_ChkRamFuncTblType bsw_cannm_ch_ptA2ChkRamFuncTbl = 
{
      &CanNmA2_CheckRam
};
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */
#endif /* ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE ) */


/************************************************/
/* CanNmB public function definition                          */
/************************************************/
#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
static BswConst Bsw_CanNm_FuncTblType bsw_cannm_ch_ptBFuncTbl = 
{
      &CanNmB_Init
    , &CanNmB_DeInit
    , &CanNmB_MainFunction
    , &CanNmB_CheckAwake
    , &CanNmB_PassiveStartUp
    , &CanNmB_NetworkRequest
    , &CanNmB_NetworkRelease
    , &CanNmB_GetState
    , &CanNmB_GetIPDUState
    , &bsw_cannm_ch_SetBusOffNone
    , &CanNmB_TxConfirmation
    , &CanNmB_RxIndication
};

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
static BswConst Bsw_CanNm_SlpFuncTblType bsw_cannm_ch_ptBSlpFuncTbl = 
{
      &CanNmB_Wakeup
    , &CanNmB_Sleep
    , &bsw_cannm_ch_GetBackupDataNone
    , &bsw_cannm_ch_SetBackupDataNone
};
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

#if( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_CanNm_ComFuncTblType bsw_cannm_ch_ptBComFuncTbl = 
{
      &CanNmB_DisableCommunication
    , &CanNmB_EnableCommunication
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
static BswConst Bsw_CanNm_ChkRamFuncTblType bsw_cannm_ch_ptBChkRamFuncTbl = 
{
      &CanNmB_CheckRam
};
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */
#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */


/************************************************/
/* CanNmC2 public function definition                         */
/************************************************/
#if ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE )
static BswConst Bsw_CanNm_FuncTblType bsw_cannm_ch_ptC2FuncTbl = 
{
      &CanNmC2_Init
    , &CanNmC2_DeInit
    , &CanNmC2_MainFunction
    , &CanNmC2_CheckAwake
    , &CanNmC2_PassiveStartUp
    , &CanNmC2_NetworkRequest
    , &CanNmC2_NetworkRelease
    , &CanNmC2_GetState
    , &CanNmC2_GetIPDUState
    , &bsw_cannm_ch_SetBusOffNone
    , &CanNmC2_TxConfirmation
    , &CanNmC2_RxIndication
};

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
static BswConst Bsw_CanNm_SlpFuncTblType bsw_cannm_ch_ptC2SlpFuncTbl = 
{
      &CanNmC2_Wakeup
    , &CanNmC2_Sleep
    , &bsw_cannm_ch_GetBackupDataNone
    , &bsw_cannm_ch_SetBackupDataNone
};
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

#if( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_CanNm_ComFuncTblType bsw_cannm_ch_ptC2ComFuncTbl = 
{
      &CanNmC2_DisableCommunication
    , &CanNmC2_EnableCommunication
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */
#if ( BSW_NM_USER_DATA == BSW_USE )
static BswConst Bsw_CanNm_UsrDatFuncTblType bsw_cannm_ch_ptC2UsrDatFuncTbl = 
{
      &CanNmC2_SetUserData
    , &CanNmC2_GetUserData
 };
#endif /* ( BSW_NM_USER_DATA == BSW_USE ) */

#if ( BSW_NM_NODE_ID == BSW_USE )
static BswConst Bsw_CanNm_NodeFuncTblType bsw_cannm_ch_ptC2NodeFuncTbl = 
{
      &CanNmC2_GetNodeIdentifier
    , &CanNmC2_GetLocalNodeIdentifier
 };
#endif /* ( BSW_NM_NODE_ID == BSW_USE ) */

#if ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) )
static BswConst Bsw_CanNm_PduFuncTblType bsw_cannm_ch_ptC2PduFuncTbl = 
{
      &CanNmC2_GetPduData
 };
#endif /* ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) ) */

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
static BswConst Bsw_CanNm_ChkRamFuncTblType bsw_cannm_ch_ptC2ChkRamFuncTbl = 
{
      &CanNmC2_CheckRam
};
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */
#endif /* ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE ) */

/************************************************/
/* CanNmE public function definition                          */
/************************************************/
#if ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE )
static BswConst Bsw_CanNm_FuncTblType bsw_cannm_ch_ptEFuncTbl = 
{
      &CanNmE_Init
    , &CanNmE_DeInit
    , &CanNmE_MainFunction
    , &CanNmE_CheckAwake
    , &CanNmE_PassiveStartUp
    , &CanNmE_NetworkRequest
    , &CanNmE_NetworkRelease
    , &CanNmE_GetState
    , &CanNmE_GetIPDUState
    , &bsw_cannm_ch_SetBusOffNone
    , &CanNmE_TxConfirmation
    , &CanNmE_RxIndication
};

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
static BswConst Bsw_CanNm_SlpFuncTblType bsw_cannm_ch_ptESlpFuncTbl = 
{
      &CanNmE_Wakeup
    , &CanNmE_Sleep
    , &bsw_cannm_ch_GetBackupDataNone
    , &bsw_cannm_ch_SetBackupDataNone
};
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

#if( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_CanNm_ComFuncTblType bsw_cannm_ch_ptEComFuncTbl = 
{
      &CanNmE_DisableCommunication
    , &CanNmE_EnableCommunication
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
static BswConst Bsw_CanNm_ChkRamFuncTblType bsw_cannm_ch_ptEChkRamFuncTbl = 
{
      &CanNmE_CheckRam
};
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */
#endif /* ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE ) */

/************************************************/
/* CanNmX public function definition                         */
/************************************************/
#if ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE )
static BswConst Bsw_CanNm_FuncTblType bsw_cannm_ch_ptXFuncTbl = 
{
      &CanNmX_CbkInit
    , &CanNmX_CbkDeInit
    , &CanNmX_CbkMainFunction
    , &CanNmX_CbkCheckAwake
    , &CanNmX_CbkPassiveStartUp
    , &CanNmX_CbkNetworkRequest
    , &CanNmX_CbkNetworkRelease
    , &CanNmX_CbkGetState
    , &CanNmX_CbkGetIPDUState
    , &bsw_cannm_ch_SetBusOffNone
    , &CanNmX_CbkTxConfirmation
    , &CanNmX_CbkRxIndication
};

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
static BswConst Bsw_CanNm_SlpFuncTblType bsw_cannm_ch_ptXSlpFuncTbl = 
{
      &CanNmX_CbkWakeup
    , &CanNmX_CbkSleep
    , &bsw_cannm_ch_GetBackupDataNone
    , &bsw_cannm_ch_SetBackupDataNone
};
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

#if( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_CanNm_ComFuncTblType bsw_cannm_ch_ptXComFuncTbl = 
{
      &CanNmX_CbkDisableCommunication
    , &CanNmX_CbkEnableCommunication
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */
#endif /* ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE ) */

/************************************************/
/* CanNmY public function definition                         */
/************************************************/
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
static BswConst Bsw_CanNm_FuncTblType bsw_cannm_ch_ptYFuncTbl = 
{
      &CanNmY_Init
    , &CanNmY_DeInit
    , &CanNmY_MainFunction
    , &CanNmY_CheckAwake
    , &CanNmY_PassiveStartUp
    , &CanNmY_NetworkRequest
    , &CanNmY_NetworkRelease
    , &CanNmY_GetState
    , &CanNmY_GetIPDUState
    , &bsw_cannm_ch_SetBusOffNone
    , &CanNmY_TxConfirmation
    , &CanNmY_RxIndication
};

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
static BswConst Bsw_CanNm_SlpFuncTblType bsw_cannm_ch_ptYSlpFuncTbl = 
{
      &CanNmY_Wakeup
    , &CanNmY_Sleep
    , &bsw_cannm_ch_GetBackupDataNone
    , &bsw_cannm_ch_SetBackupDataNone
};
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

#if( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_CanNm_ComFuncTblType bsw_cannm_ch_ptYComFuncTbl = 
{
      &CanNmY_DisableCommunication
    , &CanNmY_EnableCommunication
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */
#if ( BSW_NM_USER_DATA == BSW_USE )
static BswConst Bsw_CanNm_UsrDatFuncTblType bsw_cannm_ch_ptYUsrDatFuncTbl = 
{
      &CanNmY_SetUserData
    , &CanNmY_GetUserData
 };
#endif /* ( BSW_NM_USER_DATA == BSW_USE ) */

#if ( BSW_NM_NODE_ID == BSW_USE )
static BswConst Bsw_CanNm_NodeFuncTblType bsw_cannm_ch_ptYNodeFuncTbl = 
{
      &CanNmY_GetNodeIdentifier
    , &CanNmY_GetLocalNodeIdentifier
 };
#endif /* ( BSW_NM_NODE_ID == BSW_USE ) */

#if ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) )
static BswConst Bsw_CanNm_PduFuncTblType bsw_cannm_ch_ptYPduFuncTbl = 
{
      &CanNmY_GetPduData
 };
#endif /* ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) ) */

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
static BswConst Bsw_CanNm_ChkRamFuncTblType bsw_cannm_ch_ptYChkRamFuncTbl = 
{
      &CanNmY_CheckRam
};
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */

#if (BSW_NM_SYNC_PNC_SHUTDOWN == BSW_USE)
static BswConst Bsw_CanNm_SyncPncSlpFuncTblType bsw_cannm_ch_ptYPncSyncFuncTbl = 
{
      &CanNmY_RequestSynchronizedPncShutdown
    , &CanNmY_CancelSynchronizedPncShutdown
 };
#endif /* (BSW_NM_SYNC_PNC_SHUTDOWN == BSW_USE) */
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */

/* Public function table (needs to be edited when adding subcomponents) */
BswConst Bsw_CanNm_FuncTblType* BswConst bsw_cannm_ch_ptFuncTbl[BSW_CANNM_FUNCTBL_SIZE] = {
    &bsw_cannm_ch_ptNotIndFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE )
   ,&bsw_cannm_ch_ptZFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE )
   ,&bsw_cannm_ch_ptAFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
   ,&bsw_cannm_ch_ptA2FuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
   ,&bsw_cannm_ch_ptBFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE )
   ,&bsw_cannm_ch_ptC2FuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE )
   ,&bsw_cannm_ch_ptEFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE )
   ,&bsw_cannm_ch_ptXFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
   ,&bsw_cannm_ch_ptYFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */
};

/* Public function table (Use only NM)(needs to be edited when adding subcomponents) */
BswConst Bsw_CanNm_FuncTblType* BswConst bsw_cannm_ch_ptUseNmTypeFuncTbl[BSW_CANNM_FUNCTBL_USE_NM_SIZE] = {
#if ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE )
    &bsw_cannm_ch_ptZFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE )
    &bsw_cannm_ch_ptAFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
    &bsw_cannm_ch_ptA2FuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
    &bsw_cannm_ch_ptBFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE )
    &bsw_cannm_ch_ptC2FuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE )
    &bsw_cannm_ch_ptEFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE )
    &bsw_cannm_ch_ptXFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
    &bsw_cannm_ch_ptYFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */

    &bsw_cannm_ch_ptNotIndFuncTbl
};

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
/* Public function table for microcontroller sleep (needs to be edited when adding subcomponents) */
BswConst Bsw_CanNm_SlpFuncTblType* BswConst bsw_cannm_ch_ptSlpFuncTbl[BSW_CANNM_FUNCTBL_SIZE] = {
     &bsw_cannm_ch_ptNotIndSlpFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE )
   ,&bsw_cannm_ch_ptZSlpFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndSlpFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE )
   ,&bsw_cannm_ch_ptASlpFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndSlpFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
   ,&bsw_cannm_ch_ptA2SlpFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndSlpFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
   ,&bsw_cannm_ch_ptBSlpFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndSlpFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE )
   ,&bsw_cannm_ch_ptC2SlpFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndSlpFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE )
   ,&bsw_cannm_ch_ptESlpFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndSlpFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE )
   ,&bsw_cannm_ch_ptXSlpFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndSlpFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
   ,&bsw_cannm_ch_ptYSlpFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndSlpFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */
};
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

#if( BSW_NM_COM_CONTROL == BSW_USE )
/* Public function table for communication restriction (needs to be edited when adding subcomponents) */
BswConst Bsw_CanNm_ComFuncTblType* BswConst bsw_cannm_ch_ptComFuncTbl[BSW_CANNM_FUNCTBL_SIZE] = {
    &bsw_cannm_ch_ptNotIndComFuncTbl
   ,&bsw_cannm_ch_ptNotIndComFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE )
   ,&bsw_cannm_ch_ptAComFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndComFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
   ,&bsw_cannm_ch_ptA2ComFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndComFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
   ,&bsw_cannm_ch_ptBComFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndComFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE )
   ,&bsw_cannm_ch_ptC2ComFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndComFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE )
   ,&bsw_cannm_ch_ptEComFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndComFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE )
   ,&bsw_cannm_ch_ptXComFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndComFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
   ,&bsw_cannm_ch_ptYComFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndComFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */

#if ( BSW_NM_USER_DATA == BSW_USE )
/* Table of user data publishing functions (Editing is required when adding protocols) */
BswConst Bsw_CanNm_UsrDatFuncTblType* BswConst bsw_cannm_ch_ptUsrDatFuncTbl[BSW_CANNM_FUNCTBL_SIZE] = {
    &bsw_cannm_ch_ptNotIndUDFuncTbl
   ,&bsw_cannm_ch_ptNotIndUDFuncTbl
   ,&bsw_cannm_ch_ptNotIndUDFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
   ,&bsw_cannm_ch_ptA2UsrDatFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndUDFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE ) */
   ,&bsw_cannm_ch_ptNotIndUDFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE )
   ,&bsw_cannm_ch_ptC2UsrDatFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndUDFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE ) */
   ,&bsw_cannm_ch_ptNotIndUDFuncTbl
   ,&bsw_cannm_ch_ptNotIndUDFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
   ,&bsw_cannm_ch_ptYUsrDatFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndUDFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */
};
#endif /* ( BSW_NM_USER_DATA == BSW_USE ) */

#if ( BSW_NM_NODE_ID == BSW_USE )
/* Node ID public function table (Editing is required when adding protocols) */
BswConst Bsw_CanNm_NodeFuncTblType* BswConst bsw_cannm_ch_ptNodeFuncTbl[BSW_CANNM_FUNCTBL_SIZE] = {
    &bsw_cannm_ch_ptNotIndNodFuncTbl
   ,&bsw_cannm_ch_ptNotIndNodFuncTbl
   ,&bsw_cannm_ch_ptNotIndNodFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
   ,&bsw_cannm_ch_ptA2NodeFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndNodFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE ) */
   ,&bsw_cannm_ch_ptNotIndNodFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE )
   ,&bsw_cannm_ch_ptC2NodeFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndNodFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE ) */
   ,&bsw_cannm_ch_ptNotIndNodFuncTbl
   ,&bsw_cannm_ch_ptNotIndNodFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
   ,&bsw_cannm_ch_ptYNodeFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndNodFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */
};
#endif /* ( BSW_NM_NODE_ID == BSW_USE ) */

#if ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) )
/* NM-PDU public function table (Editing is required when adding protocols) */
BswConst Bsw_CanNm_PduFuncTblType* BswConst bsw_cannm_ch_ptPduFuncTbl[BSW_CANNM_FUNCTBL_SIZE] = {
    &bsw_cannm_ch_ptNotIndPduFuncTbl
   ,&bsw_cannm_ch_ptNotIndPduFuncTbl
   ,&bsw_cannm_ch_ptNotIndPduFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
   ,&bsw_cannm_ch_ptA2PduFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndPduFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE ) */
   ,&bsw_cannm_ch_ptNotIndPduFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE )
   ,&bsw_cannm_ch_ptC2PduFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndPduFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE ) */
   ,&bsw_cannm_ch_ptNotIndPduFuncTbl
   ,&bsw_cannm_ch_ptNotIndPduFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
   ,&bsw_cannm_ch_ptYPduFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndPduFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */
};
#endif /* ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) ) */

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
/* Public function table for RAM check (Editing is required when adding protocols) */
BswConst Bsw_CanNm_ChkRamFuncTblType* BswConst bsw_cannm_ch_ptChkRamFuncTbl[BSW_CANNM_FUNCTBL_USE_NM_SIZE] = {
#if ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE )
    &bsw_cannm_ch_ptZChkRamFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_Z == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE )
    &bsw_cannm_ch_ptAChkRamFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
    &bsw_cannm_ch_ptA2ChkRamFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
    &bsw_cannm_ch_ptBChkRamFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE )
    &bsw_cannm_ch_ptC2ChkRamFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_C2 == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE )
    &bsw_cannm_ch_ptEChkRamFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_E == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE )
    &bsw_cannm_ch_ptNotIndChkFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_X == BSW_USE ) */
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
    &bsw_cannm_ch_ptYChkRamFuncTbl,
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */
    &bsw_cannm_ch_ptNotIndChkFuncTbl
};
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */
#if ( BSW_NM_SYNC_PNC_SHUTDOWN == BSW_USE )
/* PNC synchronization request public function table(Editing is required when adding protocols) */
BswConst Bsw_CanNm_SyncPncSlpFuncTblType* BswConst bsw_cannm_ch_ptPncSyncFuncTbl[BSW_CANNM_FUNCTBL_SIZE] = {
    &bsw_cannm_ch_ptNotIndPnSFuncTbl
   ,&bsw_cannm_ch_ptNotIndPnSFuncTbl
   ,&bsw_cannm_ch_ptNotIndPnSFuncTbl
   ,&bsw_cannm_ch_ptNotIndPnSFuncTbl
   ,&bsw_cannm_ch_ptNotIndPnSFuncTbl
   ,&bsw_cannm_ch_ptNotIndPnSFuncTbl
   ,&bsw_cannm_ch_ptNotIndPnSFuncTbl
   ,&bsw_cannm_ch_ptNotIndPnSFuncTbl
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
   ,&bsw_cannm_ch_ptYPncSyncFuncTbl
#else
   ,&bsw_cannm_ch_ptNotIndPnSFuncTbl
#endif /* ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE ) */
};
#endif /* ( BSW_NM_SYNC_PNC_SHUTDOWN == BSW_USE ) */
/* Channel number -> NM-PDU offset conversion */
BswConst BswU1 bsw_cannm_ch_u1PduOffset[BSW_CANNM_CHNUM] =
{
    (BswU1)BSW_CANNM_PDUID_OFFSET_0
#if( BSW_CANNM_CHNUM > 1U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_1
#endif /* BSW_CANNM_CHNUM > 1U */
#if( BSW_CANNM_CHNUM > 2U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_2
#endif /* BSW_CANNM_CHNUM > 2U */
#if( BSW_CANNM_CHNUM > 3U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_3
#endif /* BSW_CANNM_CHNUM > 3U */
#if( BSW_CANNM_CHNUM > 4U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_4
#endif /* BSW_CANNM_CHNUM > 4U */
#if( BSW_CANNM_CHNUM > 5U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_5
#endif /* BSW_CANNM_CHNUM > 5U */
#if( BSW_CANNM_CHNUM > 6U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_6
#endif /* BSW_CANNM_CHNUM > 6U */
#if( BSW_CANNM_CHNUM > 7U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_7
#endif /* BSW_CANNM_CHNUM > 7U */
#if( BSW_CANNM_CHNUM > 8U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_8
#endif /* BSW_CANNM_CHNUM > 8U */
#if( BSW_CANNM_CHNUM > 9U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_9
#endif /* BSW_CANNM_CHNUM > 9U */
#if( BSW_CANNM_CHNUM > 10U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_10
#endif /* BSW_CANNM_CHNUM > 10U */
#if( BSW_CANNM_CHNUM > 11U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_11
#endif /* BSW_CANNM_CHNUM > 11U */
#if( BSW_CANNM_CHNUM > 12U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_12
#endif /* BSW_CANNM_CHNUM > 12U */
#if( BSW_CANNM_CHNUM > 13U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_13
#endif /* BSW_CANNM_CHNUM > 13U */
#if( BSW_CANNM_CHNUM > 14U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_14
#endif /* BSW_CANNM_CHNUM > 14U */
#if( BSW_CANNM_CHNUM > 15U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_15
#endif /* BSW_CANNM_CHNUM > 15U */
#if( BSW_CANNM_CHNUM > 16U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_16
#endif /* BSW_CANNM_CHNUM > 16U */
#if( BSW_CANNM_CHNUM > 17U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_17
#endif /* BSW_CANNM_CHNUM > 17U */
#if( BSW_CANNM_CHNUM > 18U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_18
#endif /* BSW_CANNM_CHNUM > 18U */
#if( BSW_CANNM_CHNUM > 19U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_19
#endif /* BSW_CANNM_CHNUM > 19U */
#if( BSW_CANNM_CHNUM > 20U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_20
#endif /* BSW_CANNM_CHNUM > 20U */
#if( BSW_CANNM_CHNUM > 21U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_21
#endif /* BSW_CANNM_CHNUM > 21U */
#if( BSW_CANNM_CHNUM > 22U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_22
#endif /* BSW_CANNM_CHNUM > 22U */
#if( BSW_CANNM_CHNUM > 23U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_23
#endif /* BSW_CANNM_CHNUM > 23U */
#if( BSW_CANNM_CHNUM > 24U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_24
#endif /* BSW_CANNM_CHNUM > 24U */
#if( BSW_CANNM_CHNUM > 25U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_25
#endif /* BSW_CANNM_CHNUM > 25U */
#if( BSW_CANNM_CHNUM > 26U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_26
#endif /* BSW_CANNM_CHNUM > 26U */
#if( BSW_CANNM_CHNUM > 27U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_27
#endif /* BSW_CANNM_CHNUM > 27U */
#if( BSW_CANNM_CHNUM > 28U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_28
#endif /* BSW_CANNM_CHNUM > 28U */
#if( BSW_CANNM_CHNUM > 29U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_29
#endif /* BSW_CANNM_CHNUM > 29U */
#if( BSW_CANNM_CHNUM > 30U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_30
#endif /* BSW_CANNM_CHNUM > 30U */
#if( BSW_CANNM_CHNUM > 31U )
    , (BswU1)BSW_CANNM_PDUID_OFFSET_31
#endif /* BSW_CANNM_CHNUM > 31U */
};

#if (BSW_CANNM_CH_EVTWAKEUPFRAME_USE == BSW_USE)
uint16 (* BswConst bsw_cannm_ch_ptTransEvtWkupFunc[BSW_CANNM_FUNCTBL_SIZE])( NetworkHandleType nmNetworkHandle ) = {
      &bsw_cannm_ch_TrEvWkupNone
    , &bsw_cannm_ch_TrEvWkupNone
#if ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE )
    , &CanNmA_TransmitEvtWkup
#else
    , &bsw_cannm_ch_TrEvWkupNone
#endif
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
    , &CanNmA2_TransmitEvtWkup
#else
    , &bsw_cannm_ch_TrEvWkupNone
#endif
#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
    , &CanNmB_TransmitEvtWkup
#else
    , &bsw_cannm_ch_TrEvWkupNone
#endif
    , &bsw_cannm_ch_TrEvWkupNone
    , &bsw_cannm_ch_TrEvWkupNone
    , &bsw_cannm_ch_TrEvWkupNone
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
    , &CanNmY_TransmitEvtWkup
#else
    , &bsw_cannm_ch_TrEvWkupNone
#endif
};
void (* BswConst bsw_cannm_ch_ptEvtWkupClFunc[BSW_CANNM_FUNCTBL_SIZE])( NetworkHandleType nmNetworkHandle ) = {
      &bsw_cannm_ch_ClEvWkupNone
    , &bsw_cannm_ch_ClEvWkupNone
#if ( BSW_CANNM_NM_TYPE_USE_A == BSW_USE )
    , &CanNmA_CancelEvtWkup
#else
    , &bsw_cannm_ch_ClEvWkupNone
#endif
#if ( BSW_CANNM_NM_TYPE_USE_A2 == BSW_USE )
    , &CanNmA2_CancelEvtWkup
#else
    , &bsw_cannm_ch_ClEvWkupNone
#endif
#if ( BSW_CANNM_NM_TYPE_USE_B == BSW_USE )
    , &CanNmB_CancelEvtWkup
#else
    , &bsw_cannm_ch_ClEvWkupNone
#endif
    , &bsw_cannm_ch_ClEvWkupNone
    , &bsw_cannm_ch_ClEvWkupNone
    , &bsw_cannm_ch_ClEvWkupNone
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
    , &CanNmY_CancelEvtWkup
#else
    , &bsw_cannm_ch_ClEvWkupNone
#endif
};
#endif

#if (BSW_NM_SLEEPSYNC == BSW_USE)
Std_ReturnType (* BswConst bsw_cannm_ch_ptSetSRBFunc[BSW_CANNM_FUNCTBL_SIZE])( NetworkHandleType nmChannelHandle, boolean nmSleepReadyBit ) = {
    &bsw_cannm_ch_SetSlpReadyBitNone
   ,&bsw_cannm_ch_SetSlpReadyBitNone
   ,&bsw_cannm_ch_SetSlpReadyBitNone
   ,&bsw_cannm_ch_SetSlpReadyBitNone
   ,&bsw_cannm_ch_SetSlpReadyBitNone
   ,&bsw_cannm_ch_SetSlpReadyBitNone
   ,&bsw_cannm_ch_SetSlpReadyBitNone
   ,&bsw_cannm_ch_SetSlpReadyBitNone
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
   ,&CanNmY_SetSleepReadyBit
#else
   ,&bsw_cannm_ch_SetSlpReadyBitNone
#endif
};

#if (BSW_NM_REQ_BUS_SYNC_USE_CAN == BSW_USE)
Std_ReturnType (* BswConst bsw_cannm_ch_ptRqBusSyncFunc[BSW_CANNM_FUNCTBL_SIZE])( NetworkHandleType nmChannelHandle ) = {
    &bsw_cannm_ch_RequestBusSyncNone
   ,&bsw_cannm_ch_RequestBusSyncNone
   ,&bsw_cannm_ch_RequestBusSyncNone
   ,&bsw_cannm_ch_RequestBusSyncNone
   ,&bsw_cannm_ch_RequestBusSyncNone
   ,&bsw_cannm_ch_RequestBusSyncNone
   ,&bsw_cannm_ch_RequestBusSyncNone
   ,&bsw_cannm_ch_RequestBusSyncNone
#if ( BSW_CANNM_NM_TYPE_USE_Y == BSW_USE )
   ,&CanNmY_RequestBusSynchronization
#else
   ,&bsw_cannm_ch_RequestBusSyncNone
#endif
};
#endif /* (BSW_NM_REQ_BUS_SYNC_USE_CAN == BSW_USE) */
#endif /* (BSW_NM_SLEEPSYNC == BSW_USE) */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* (BSW_BSWM_CS_FUNC_CANNM == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-1-0          :2018/12/13                                             */
/*  v1-2-0          :2020/04/15                                             */
/*  v1-2-1          :2020/05/14                                             */
/*  v2-0-0          :2022/01/13                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
