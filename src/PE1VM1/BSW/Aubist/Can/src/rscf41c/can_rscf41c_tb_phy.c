/* can_rscf41c_tb_phy_c_m10700_v3-0-0                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF41C/TB/PHYSICAL/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>

#include "../../cfg/common/can_cv_cfg.h"
#include "../../cfg/rscf41c/can_rscf41c_cfg_ext.h"
#include "../../cfg/rscf41c/can_rscf41c_cfg.h"

#include <can/common/can_cv_can.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf41c/can_rscf41c.h>
#include <can/rscf41c/can_rscf41c_cm_phy.h>
#include <can/common/can_memmap.h>
#include <can/rscf41c/can_rscf41c_tb_phy.h>
#include <can/rscf41c/can_rscf41c_st.h>
#include <can/rscf41c/can_rscf41c_tx.h>
#include <can/rscf41c/can_rscf41c_rx.h>
#include <can/rscf41c/can_rscf41c_fs.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_TB_RXRULE_OFFSET0           ( 0U )
#define CAN_TB_RXRULE_OFFSET1           ( CAN_TB_RXRULE_OFFSET0 + CAN_CFG_HRHNUM_0 )
#define CAN_TB_RXRULE_OFFSET2           ( CAN_TB_RXRULE_OFFSET1 + CAN_CFG_HRHNUM_1 )
#define CAN_TB_RXRULE_OFFSET3           ( CAN_TB_RXRULE_OFFSET2 + CAN_CFG_HRHNUM_2 )
#define CAN_TB_RXRULE_OFFSET4           ( CAN_TB_RXRULE_OFFSET3 + CAN_CFG_HRHNUM_3 )
#define CAN_TB_RXRULE_OFFSET5           ( CAN_TB_RXRULE_OFFSET4 + CAN_CFG_HRHNUM_4 )
#define CAN_TB_RXRULE_OFFSET6           ( CAN_TB_RXRULE_OFFSET5 + CAN_CFG_HRHNUM_5 )
#define CAN_TB_RXRULE_OFFSET7           ( CAN_TB_RXRULE_OFFSET6 + CAN_CFG_HRHNUM_6 )


#define CAN_TB_MBSET_0( mb )            ( CAN_CFG_MBOXSET_0_MB##mb )
#define CAN_TB_MBSET_1( mb )            ( CAN_CFG_MBOXSET_1_MB##mb )
#define CAN_TB_MBSET_2( mb )            ( CAN_CFG_MBOXSET_2_MB##mb )
#define CAN_TB_MBSET_3( mb )            ( CAN_CFG_MBOXSET_3_MB##mb )
#define CAN_TB_MBSET_4( mb )            ( CAN_CFG_MBOXSET_4_MB##mb )
#define CAN_TB_MBSET_5( mb )            ( CAN_CFG_MBOXSET_5_MB##mb )
#define CAN_TB_MBSET_6( mb )            ( CAN_CFG_MBOXSET_6_MB##mb )
#define CAN_TB_MBSET_7( mb )            ( CAN_CFG_MBOXSET_7_MB##mb )
#define CAN_TB_MBSET( ch, mb )          ( CAN_TB_MBSET_##ch( mb ) )


#define CAN_TB_MBNUM_UTX( ch )          ( CAN_CFG_USERTXMBOXNUM_##ch )
#define CAN_TB_MBNUM_TX( ch )           ( ( CAN_CFG_HTHNUM_##ch ) + ( CAN_TB_MBNUM_UTX( ch ) ) )
#define CAN_TB_MBNUM_RX( ch )           ( CAN_CFG_HRHNUM_##ch )

#define CAN_TB_MBNUM( ch, kind )        ( CAN_TB_MBNUM_##kind( ch ) )


#define CAN_TB_REG_BASE_ADDR            ( CAN_CFG_REG_BASEADDR )

#define CAN_TB_ptu4CH0_CmNCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000000UL) )
#define CAN_TB_ptu4CH0_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000004UL) )
#define CAN_TB_ptu4CH0_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000008UL) )
#define CAN_TB_ptu4CH0_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000000CUL) )
#define CAN_TB_ptu4CH0_CFCC_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000120UL) )
#define CAN_TB_ptu4CH0_CFCCE_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000180UL) )
#define CAN_TB_ptu4CH0_CFSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001E0UL) )
#define CAN_TB_ptu4CH0_CFPCTR_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000240UL) )
#define CAN_TB_ptu1CH0_TMC_ADDR         ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x000002D0UL) )
#define CAN_TB_ptu1CH0_TMSTS_ADDR       ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x000007D0UL) )
#define CAN_TB_ptu4CH0_TMTRSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000CD0UL) )
#define CAN_TB_ptu4CH0_TMTARSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000D70UL) )
#define CAN_TB_ptu4CH0_TMTCSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000E10UL) )
#define CAN_TB_ptu4CH0_TMTASTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000EB0UL) )
#define CAN_TB_ptu4CH0_TMIEC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000F50UL) )
#define CAN_TB_ptu4CH0_TXQCC0_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001000UL) )
#define CAN_TB_ptu4CH0_TXQSTS0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001020UL) )
#define CAN_TB_ptu4CH0_TXQPCTR0_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001040UL) )
#define CAN_TB_ptu4CH0_TXQCC1_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001060UL) )
#define CAN_TB_ptu4CH0_TXQSTS1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001080UL) )
#define CAN_TB_ptu4CH0_TXQPCTR1_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010A0UL) )
#define CAN_TB_ptu4CH0_TXQCC2_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010C0UL) )
#define CAN_TB_ptu4CH0_TXQSTS2_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010E0UL) )
#define CAN_TB_ptu4CH0_TXQPCTR2_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001100UL) )
#define CAN_TB_ptu4CH0_TXQCC3_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001120UL) )
#define CAN_TB_ptu4CH0_TXQSTS3_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001140UL) )
#define CAN_TB_ptu4CH0_TXQPCTR3_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001160UL) )
#define CAN_TB_ptu4CH0_THLCC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001200UL) )
#define CAN_TB_ptu4CH0_THLSTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001220UL) )
#define CAN_TB_ptu4CH0_THLPCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001240UL) )
#define CAN_TB_ptu4CH0_GRINTSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001350UL) )
#define CAN_TB_ptu4CH0_VMCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013A0UL) )
#define CAN_TB_ptu4CH0_VMISTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013E0UL) )
#define CAN_TB_ptu4CH0_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001400UL) )
#define CAN_TB_ptu4CH0_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001404UL) )
#define CAN_TB_ptu4CH0_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001408UL) )
#define CAN_TB_ptu4CH0_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000140CUL) )
#define CAN_TB_ptu4CH0_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001410UL) )
#define CAN_TB_ptu4CH0_CmBLCT_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001418UL) )
#define CAN_TB_ptu4CH0_CmBLSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000141CUL) )
#define CAN_TB_ptu4CH0_THLACC0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008000UL) )
#define CAN_TB_ptu4CH0_THLACC1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008004UL) )
#define CAN_TB_ptstCH0_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00006400UL) )
#define CAN_TB_ptstCH0_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00010000UL) )

#define CAN_TB_ptu4CH1_CmNCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000010UL) )
#define CAN_TB_ptu4CH1_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000014UL) )
#define CAN_TB_ptu4CH1_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000018UL) )
#define CAN_TB_ptu4CH1_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000001CUL) )
#define CAN_TB_ptu4CH1_CFCC_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000012CUL) )
#define CAN_TB_ptu4CH1_CFCCE_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000018CUL) )
#define CAN_TB_ptu4CH1_CFSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001ECUL) )
#define CAN_TB_ptu4CH1_CFPCTR_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000024CUL) )
#define CAN_TB_ptu1CH1_TMC_ADDR         ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000310UL) )
#define CAN_TB_ptu1CH1_TMSTS_ADDR       ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000810UL) )
#define CAN_TB_ptu4CH1_TMTRSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000CD8UL) )
#define CAN_TB_ptu4CH1_TMTARSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000D78UL) )
#define CAN_TB_ptu4CH1_TMTCSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000E18UL) )
#define CAN_TB_ptu4CH1_TMTASTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000EB8UL) )
#define CAN_TB_ptu4CH1_TMIEC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000F58UL) )
#define CAN_TB_ptu4CH1_TXQCC0_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001004UL) )
#define CAN_TB_ptu4CH1_TXQSTS0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001024UL) )
#define CAN_TB_ptu4CH1_TXQPCTR0_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001044UL) )
#define CAN_TB_ptu4CH1_TXQCC1_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001064UL) )
#define CAN_TB_ptu4CH1_TXQSTS1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001084UL) )
#define CAN_TB_ptu4CH1_TXQPCTR1_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010A4UL) )
#define CAN_TB_ptu4CH1_TXQCC2_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010C4UL) )
#define CAN_TB_ptu4CH1_TXQSTS2_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010E4UL) )
#define CAN_TB_ptu4CH1_TXQPCTR2_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001104UL) )
#define CAN_TB_ptu4CH1_TXQCC3_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001124UL) )
#define CAN_TB_ptu4CH1_TXQSTS3_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001144UL) )
#define CAN_TB_ptu4CH1_TXQPCTR3_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001164UL) )
#define CAN_TB_ptu4CH1_THLCC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001204UL) )
#define CAN_TB_ptu4CH1_THLSTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001224UL) )
#define CAN_TB_ptu4CH1_THLPCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001244UL) )
#define CAN_TB_ptu4CH1_GRINTSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001354UL) )
#define CAN_TB_ptu4CH1_VMCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013A4UL) )
#define CAN_TB_ptu4CH1_VMISTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013E4UL) )
#define CAN_TB_ptu4CH1_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001420UL) )
#define CAN_TB_ptu4CH1_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001424UL) )
#define CAN_TB_ptu4CH1_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001428UL) )
#define CAN_TB_ptu4CH1_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000142CUL) )
#define CAN_TB_ptu4CH1_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001430UL) )
#define CAN_TB_ptu4CH1_CmBLCT_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001438UL) )
#define CAN_TB_ptu4CH1_CmBLSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000143CUL) )
#define CAN_TB_ptu4CH1_THLACC0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008008UL) )
#define CAN_TB_ptu4CH1_THLACC1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000800CUL) )
#define CAN_TB_ptstCH1_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00006580UL) )
#define CAN_TB_ptstCH1_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00012000UL) )

#define CAN_TB_ptu4CH2_CmNCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000020UL) )
#define CAN_TB_ptu4CH2_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000024UL) )
#define CAN_TB_ptu4CH2_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000028UL) )
#define CAN_TB_ptu4CH2_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000002CUL) )
#define CAN_TB_ptu4CH2_CFCC_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000138UL) )
#define CAN_TB_ptu4CH2_CFCCE_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000198UL) )
#define CAN_TB_ptu4CH2_CFSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001F8UL) )
#define CAN_TB_ptu4CH2_CFPCTR_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000258UL) )
#define CAN_TB_ptu1CH2_TMC_ADDR         ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000350UL) )
#define CAN_TB_ptu1CH2_TMSTS_ADDR       ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000850UL) )
#define CAN_TB_ptu4CH2_TMTRSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000CE0UL) )
#define CAN_TB_ptu4CH2_TMTARSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000D80UL) )
#define CAN_TB_ptu4CH2_TMTCSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000E20UL) )
#define CAN_TB_ptu4CH2_TMTASTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000EC0UL) )
#define CAN_TB_ptu4CH2_TMIEC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000F60UL) )
#define CAN_TB_ptu4CH2_TXQCC0_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001008UL) )
#define CAN_TB_ptu4CH2_TXQSTS0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001028UL) )
#define CAN_TB_ptu4CH2_TXQPCTR0_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001048UL) )
#define CAN_TB_ptu4CH2_TXQCC1_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001068UL) )
#define CAN_TB_ptu4CH2_TXQSTS1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001088UL) )
#define CAN_TB_ptu4CH2_TXQPCTR1_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010A8UL) )
#define CAN_TB_ptu4CH2_TXQCC2_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010C8UL) )
#define CAN_TB_ptu4CH2_TXQSTS2_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010E8UL) )
#define CAN_TB_ptu4CH2_TXQPCTR2_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001108UL) )
#define CAN_TB_ptu4CH2_TXQCC3_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001128UL) )
#define CAN_TB_ptu4CH2_TXQSTS3_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001148UL) )
#define CAN_TB_ptu4CH2_TXQPCTR3_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001168UL) )
#define CAN_TB_ptu4CH2_THLCC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001208UL) )
#define CAN_TB_ptu4CH2_THLSTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001228UL) )
#define CAN_TB_ptu4CH2_THLPCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001248UL) )
#define CAN_TB_ptu4CH2_GRINTSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001358UL) )
#define CAN_TB_ptu4CH2_VMCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013A8UL) )
#define CAN_TB_ptu4CH2_VMISTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013E8UL) )
#define CAN_TB_ptu4CH2_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001440UL) )
#define CAN_TB_ptu4CH2_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001444UL) )
#define CAN_TB_ptu4CH2_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001448UL) )
#define CAN_TB_ptu4CH2_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000144CUL) )
#define CAN_TB_ptu4CH2_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001450UL) )
#define CAN_TB_ptu4CH2_CmBLCT_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001458UL) )
#define CAN_TB_ptu4CH2_CmBLSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000145CUL) )
#define CAN_TB_ptu4CH2_THLACC0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008010UL) )
#define CAN_TB_ptu4CH2_THLACC1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008014UL) )
#define CAN_TB_ptstCH2_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00006700UL) )
#define CAN_TB_ptstCH2_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00014000UL) )

#define CAN_TB_ptu4CH3_CmNCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000030UL) )
#define CAN_TB_ptu4CH3_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000034UL) )
#define CAN_TB_ptu4CH3_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000038UL) )
#define CAN_TB_ptu4CH3_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000003CUL) )
#define CAN_TB_ptu4CH3_CFCC_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000144UL) )
#define CAN_TB_ptu4CH3_CFCCE_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001A4UL) )
#define CAN_TB_ptu4CH3_CFSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000204UL) )
#define CAN_TB_ptu4CH3_CFPCTR_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000264UL) )
#define CAN_TB_ptu1CH3_TMC_ADDR         ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000390UL) )
#define CAN_TB_ptu1CH3_TMSTS_ADDR       ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000890UL) )
#define CAN_TB_ptu4CH3_TMTRSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000CE8UL) )
#define CAN_TB_ptu4CH3_TMTARSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000D88UL) )
#define CAN_TB_ptu4CH3_TMTCSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000E28UL) )
#define CAN_TB_ptu4CH3_TMTASTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000EC8UL) )
#define CAN_TB_ptu4CH3_TMIEC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000F68UL) )
#define CAN_TB_ptu4CH3_TXQCC0_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000100CUL) )
#define CAN_TB_ptu4CH3_TXQSTS0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000102CUL) )
#define CAN_TB_ptu4CH3_TXQPCTR0_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000104CUL) )
#define CAN_TB_ptu4CH3_TXQCC1_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000106CUL) )
#define CAN_TB_ptu4CH3_TXQSTS1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000108CUL) )
#define CAN_TB_ptu4CH3_TXQPCTR1_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010ACUL) )
#define CAN_TB_ptu4CH3_TXQCC2_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010CCUL) )
#define CAN_TB_ptu4CH3_TXQSTS2_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010ECUL) )
#define CAN_TB_ptu4CH3_TXQPCTR2_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000110CUL) )
#define CAN_TB_ptu4CH3_TXQCC3_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000112CUL) )
#define CAN_TB_ptu4CH3_TXQSTS3_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000114CUL) )
#define CAN_TB_ptu4CH3_TXQPCTR3_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000116CUL) )
#define CAN_TB_ptu4CH3_THLCC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000120CUL) )
#define CAN_TB_ptu4CH3_THLSTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000122CUL) )
#define CAN_TB_ptu4CH3_THLPCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000124CUL) )
#define CAN_TB_ptu4CH3_GRINTSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000135CUL) )
#define CAN_TB_ptu4CH3_VMCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013ACUL) )
#define CAN_TB_ptu4CH3_VMISTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013ECUL) )
#define CAN_TB_ptu4CH3_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001460UL) )
#define CAN_TB_ptu4CH3_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001464UL) )
#define CAN_TB_ptu4CH3_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001468UL) )
#define CAN_TB_ptu4CH3_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000146CUL) )
#define CAN_TB_ptu4CH3_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001470UL) )
#define CAN_TB_ptu4CH3_CmBLCT_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001478UL) )
#define CAN_TB_ptu4CH3_CmBLSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000147CUL) )
#define CAN_TB_ptu4CH3_THLACC0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008018UL) )
#define CAN_TB_ptu4CH3_THLACC1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000801CUL) )
#define CAN_TB_ptstCH3_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00006880UL) )
#define CAN_TB_ptstCH3_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00016000UL) )

#define CAN_TB_ptu4CH4_CmNCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000040UL) )
#define CAN_TB_ptu4CH4_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000044UL) )
#define CAN_TB_ptu4CH4_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000048UL) )
#define CAN_TB_ptu4CH4_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000004CUL) )
#define CAN_TB_ptu4CH4_CFCC_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000150UL) )
#define CAN_TB_ptu4CH4_CFCCE_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001B0UL) )
#define CAN_TB_ptu4CH4_CFSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000210UL) )
#define CAN_TB_ptu4CH4_CFPCTR_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000270UL) )
#define CAN_TB_ptu1CH4_TMC_ADDR         ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x000003D0UL) )
#define CAN_TB_ptu1CH4_TMSTS_ADDR       ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x000008D0UL) )
#define CAN_TB_ptu4CH4_TMTRSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000CF0UL) )
#define CAN_TB_ptu4CH4_TMTARSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000D90UL) )
#define CAN_TB_ptu4CH4_TMTCSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000E30UL) )
#define CAN_TB_ptu4CH4_TMTASTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000ED0UL) )
#define CAN_TB_ptu4CH4_TMIEC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000F70UL) )
#define CAN_TB_ptu4CH4_TXQCC0_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001010UL) )
#define CAN_TB_ptu4CH4_TXQSTS0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001030UL) )
#define CAN_TB_ptu4CH4_TXQPCTR0_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001050UL) )
#define CAN_TB_ptu4CH4_TXQCC1_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001070UL) )
#define CAN_TB_ptu4CH4_TXQSTS1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001090UL) )
#define CAN_TB_ptu4CH4_TXQPCTR1_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010B0UL) )
#define CAN_TB_ptu4CH4_TXQCC2_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010D0UL) )
#define CAN_TB_ptu4CH4_TXQSTS2_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010F0UL) )
#define CAN_TB_ptu4CH4_TXQPCTR2_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001110UL) )
#define CAN_TB_ptu4CH4_TXQCC3_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001130UL) )
#define CAN_TB_ptu4CH4_TXQSTS3_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001150UL) )
#define CAN_TB_ptu4CH4_TXQPCTR3_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001170UL) )
#define CAN_TB_ptu4CH4_THLCC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001210UL) )
#define CAN_TB_ptu4CH4_THLSTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001230UL) )
#define CAN_TB_ptu4CH4_THLPCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001250UL) )
#define CAN_TB_ptu4CH4_GRINTSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001360UL) )
#define CAN_TB_ptu4CH4_VMCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013B0UL) )
#define CAN_TB_ptu4CH4_VMISTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013F0UL) )
#define CAN_TB_ptu4CH4_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001480UL) )
#define CAN_TB_ptu4CH4_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001484UL) )
#define CAN_TB_ptu4CH4_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001488UL) )
#define CAN_TB_ptu4CH4_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000148CUL) )
#define CAN_TB_ptu4CH4_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001490UL) )
#define CAN_TB_ptu4CH4_CmBLCT_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001498UL) )
#define CAN_TB_ptu4CH4_CmBLSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000149CUL) )
#define CAN_TB_ptu4CH4_THLACC0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008020UL) )
#define CAN_TB_ptu4CH4_THLACC1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008024UL) )
#define CAN_TB_ptstCH4_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00006A00UL) )
#define CAN_TB_ptstCH4_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00018000UL) )

#define CAN_TB_ptu4CH5_CmNCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000050UL) )
#define CAN_TB_ptu4CH5_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000054UL) )
#define CAN_TB_ptu4CH5_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000058UL) )
#define CAN_TB_ptu4CH5_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000005CUL) )
#define CAN_TB_ptu4CH5_CFCC_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000015CUL) )
#define CAN_TB_ptu4CH5_CFCCE_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001BCUL) )
#define CAN_TB_ptu4CH5_CFSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000021CUL) )
#define CAN_TB_ptu4CH5_CFPCTR_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000027CUL) )
#define CAN_TB_ptu1CH5_TMC_ADDR         ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000410UL) )
#define CAN_TB_ptu1CH5_TMSTS_ADDR       ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000910UL) )
#define CAN_TB_ptu4CH5_TMTRSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000CF8UL) )
#define CAN_TB_ptu4CH5_TMTARSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000D98UL) )
#define CAN_TB_ptu4CH5_TMTCSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000E38UL) )
#define CAN_TB_ptu4CH5_TMTASTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000ED8UL) )
#define CAN_TB_ptu4CH5_TMIEC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000F78UL) )
#define CAN_TB_ptu4CH5_TXQCC0_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001014UL) )
#define CAN_TB_ptu4CH5_TXQSTS0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001034UL) )
#define CAN_TB_ptu4CH5_TXQPCTR0_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001054UL) )
#define CAN_TB_ptu4CH5_TXQCC1_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001074UL) )
#define CAN_TB_ptu4CH5_TXQSTS1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001094UL) )
#define CAN_TB_ptu4CH5_TXQPCTR1_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010B4UL) )
#define CAN_TB_ptu4CH5_TXQCC2_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010D4UL) )
#define CAN_TB_ptu4CH5_TXQSTS2_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010F4UL) )
#define CAN_TB_ptu4CH5_TXQPCTR2_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001114UL) )
#define CAN_TB_ptu4CH5_TXQCC3_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001134UL) )
#define CAN_TB_ptu4CH5_TXQSTS3_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001154UL) )
#define CAN_TB_ptu4CH5_TXQPCTR3_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001174UL) )
#define CAN_TB_ptu4CH5_THLCC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001214UL) )
#define CAN_TB_ptu4CH5_THLSTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001234UL) )
#define CAN_TB_ptu4CH5_THLPCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001254UL) )
#define CAN_TB_ptu4CH5_GRINTSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001364UL) )
#define CAN_TB_ptu4CH5_VMCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013B4UL) )
#define CAN_TB_ptu4CH5_VMISTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013F4UL) )
#define CAN_TB_ptu4CH5_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014A0UL) )
#define CAN_TB_ptu4CH5_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014A4UL) )
#define CAN_TB_ptu4CH5_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014A8UL) )
#define CAN_TB_ptu4CH5_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014ACUL) )
#define CAN_TB_ptu4CH5_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014B0UL) )
#define CAN_TB_ptu4CH5_CmBLCT_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014B8UL) )
#define CAN_TB_ptu4CH5_CmBLSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014BCUL) )
#define CAN_TB_ptu4CH5_THLACC0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008028UL) )
#define CAN_TB_ptu4CH5_THLACC1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000802CUL) )
#define CAN_TB_ptstCH5_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00006B80UL) )
#define CAN_TB_ptstCH5_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x0001A000UL) )

#define CAN_TB_ptu4CH6_CmNCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000060UL) )
#define CAN_TB_ptu4CH6_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000064UL) )
#define CAN_TB_ptu4CH6_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000068UL) )
#define CAN_TB_ptu4CH6_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000006CUL) )
#define CAN_TB_ptu4CH6_CFCC_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000168UL) )
#define CAN_TB_ptu4CH6_CFCCE_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001C8UL) )
#define CAN_TB_ptu4CH6_CFSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000228UL) )
#define CAN_TB_ptu4CH6_CFPCTR_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000288UL) )
#define CAN_TB_ptu1CH6_TMC_ADDR         ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000450UL) )
#define CAN_TB_ptu1CH6_TMSTS_ADDR       ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000950UL) )
#define CAN_TB_ptu4CH6_TMTRSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000D00UL) )
#define CAN_TB_ptu4CH6_TMTARSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000DA0UL) )
#define CAN_TB_ptu4CH6_TMTCSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000E40UL) )
#define CAN_TB_ptu4CH6_TMTASTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000EE0UL) )
#define CAN_TB_ptu4CH6_TMIEC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000F80UL) )
#define CAN_TB_ptu4CH6_TXQCC0_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001018UL) )
#define CAN_TB_ptu4CH6_TXQSTS0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001038UL) )
#define CAN_TB_ptu4CH6_TXQPCTR0_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001058UL) )
#define CAN_TB_ptu4CH6_TXQCC1_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001078UL) )
#define CAN_TB_ptu4CH6_TXQSTS1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001098UL) )
#define CAN_TB_ptu4CH6_TXQPCTR1_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010B8UL) )
#define CAN_TB_ptu4CH6_TXQCC2_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010D8UL) )
#define CAN_TB_ptu4CH6_TXQSTS2_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010F8UL) )
#define CAN_TB_ptu4CH6_TXQPCTR2_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001118UL) )
#define CAN_TB_ptu4CH6_TXQCC3_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001138UL) )
#define CAN_TB_ptu4CH6_TXQSTS3_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001158UL) )
#define CAN_TB_ptu4CH6_TXQPCTR3_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001178UL) )
#define CAN_TB_ptu4CH6_THLCC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001218UL) )
#define CAN_TB_ptu4CH6_THLSTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001238UL) )
#define CAN_TB_ptu4CH6_THLPCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001258UL) )
#define CAN_TB_ptu4CH6_GRINTSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001368UL) )
#define CAN_TB_ptu4CH6_VMCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013B8UL) )
#define CAN_TB_ptu4CH6_VMISTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013F8UL) )
#define CAN_TB_ptu4CH6_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014C0UL) )
#define CAN_TB_ptu4CH6_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014C4UL) )
#define CAN_TB_ptu4CH6_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014C8UL) )
#define CAN_TB_ptu4CH6_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014CCUL) )
#define CAN_TB_ptu4CH6_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014D0UL) )
#define CAN_TB_ptu4CH6_CmBLCT_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014D8UL) )
#define CAN_TB_ptu4CH6_CmBLSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014DCUL) )
#define CAN_TB_ptu4CH6_THLACC0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008030UL) )
#define CAN_TB_ptu4CH6_THLACC1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008034UL) )
#define CAN_TB_ptstCH6_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00006D00UL) )
#define CAN_TB_ptstCH6_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x0001C000UL) )

#define CAN_TB_ptu4CH7_CmNCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000070UL) )
#define CAN_TB_ptu4CH7_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000074UL) )
#define CAN_TB_ptu4CH7_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000078UL) )
#define CAN_TB_ptu4CH7_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000007CUL) )
#define CAN_TB_ptu4CH7_CFCC_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000174UL) )
#define CAN_TB_ptu4CH7_CFCCE_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001D4UL) )
#define CAN_TB_ptu4CH7_CFSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000234UL) )
#define CAN_TB_ptu4CH7_CFPCTR_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000294UL) )
#define CAN_TB_ptu1CH7_TMC_ADDR         ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000490UL) )
#define CAN_TB_ptu1CH7_TMSTS_ADDR       ( (volatile uint8  *)(CAN_TB_REG_BASE_ADDR + 0x00000990UL) )
#define CAN_TB_ptu4CH7_TMTRSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000D08UL) )
#define CAN_TB_ptu4CH7_TMTARSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000DA8UL) )
#define CAN_TB_ptu4CH7_TMTCSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000E48UL) )
#define CAN_TB_ptu4CH7_TMTASTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000EE8UL) )
#define CAN_TB_ptu4CH7_TMIEC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000F88UL) )
#define CAN_TB_ptu4CH7_TXQCC0_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000101CUL) )
#define CAN_TB_ptu4CH7_TXQSTS0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000103CUL) )
#define CAN_TB_ptu4CH7_TXQPCTR0_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000105CUL) )
#define CAN_TB_ptu4CH7_TXQCC1_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000107CUL) )
#define CAN_TB_ptu4CH7_TXQSTS1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000109CUL) )
#define CAN_TB_ptu4CH7_TXQPCTR1_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010BCUL) )
#define CAN_TB_ptu4CH7_TXQCC2_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010DCUL) )
#define CAN_TB_ptu4CH7_TXQSTS2_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000010FCUL) )
#define CAN_TB_ptu4CH7_TXQPCTR2_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000111CUL) )
#define CAN_TB_ptu4CH7_TXQCC3_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000113CUL) )
#define CAN_TB_ptu4CH7_TXQSTS3_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000115CUL) )
#define CAN_TB_ptu4CH7_TXQPCTR3_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000117CUL) )
#define CAN_TB_ptu4CH7_THLCC_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000121CUL) )
#define CAN_TB_ptu4CH7_THLSTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000123CUL) )
#define CAN_TB_ptu4CH7_THLPCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000125CUL) )
#define CAN_TB_ptu4CH7_GRINTSTS_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000136CUL) )
#define CAN_TB_ptu4CH7_VMCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013BCUL) )
#define CAN_TB_ptu4CH7_VMISTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013FCUL) )
#define CAN_TB_ptu4CH7_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014E0UL) )
#define CAN_TB_ptu4CH7_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014E4UL) )
#define CAN_TB_ptu4CH7_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014E8UL) )
#define CAN_TB_ptu4CH7_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014ECUL) )
#define CAN_TB_ptu4CH7_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014F0UL) )
#define CAN_TB_ptu4CH7_CmBLCT_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014F8UL) )
#define CAN_TB_ptu4CH7_CmBLSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000014FCUL) )
#define CAN_TB_ptu4CH7_THLACC0_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008038UL) )
#define CAN_TB_ptu4CH7_THLACC1_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000803CUL) )
#define CAN_TB_ptstCH7_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00006E80UL) )
#define CAN_TB_ptstCH7_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x0001E000UL) )

#define CAN_TB_ptu4GIPV_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000080UL) )
#define CAN_TB_ptu4GCFG_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000084UL) )
#define CAN_TB_ptu4GCTR_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000088UL) )
#define CAN_TB_ptu4GSTS_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000008CUL) )
#define CAN_TB_ptu4GERFL_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000090UL) )
#define CAN_TB_ptu4GTSC_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000094UL) )
#define CAN_TB_ptu4GAFLECTR_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000098UL) )
#define CAN_TB_ptu4GAFLCFG_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000009CUL) )
#define CAN_TB_ptu4RMNB_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000000ACUL) )
#define CAN_TB_ptu4RMND_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000000B0UL) )
#define CAN_TB_ptu4RFCC_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000000C0UL) )
#define CAN_TB_ptu4RFSTS_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000000E0UL) )
#define CAN_TB_ptu4RFPCTR_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000100UL) )
#define CAN_TB_ptu4FESTS_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000002A0UL) )
#define CAN_TB_ptu4FFSTS_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000002A4UL) )
#define CAN_TB_ptu4FMSTS_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000002A8UL) )
#define CAN_TB_ptu4RFISTS_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000002ACUL) )
#define CAN_TB_ptu4CFRISTS_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000002B0UL) )
#define CAN_TB_ptu4CFTISTS_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000002B4UL) )
#define CAN_TB_ptu4CFOFRISTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000002B8UL) )
#define CAN_TB_ptu4CFOFTISTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000002BCUL) )
#define CAN_TB_ptu4CFMOWSTS_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000002C0UL) )
#define CAN_TB_ptu4FFFSTS_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000002C4UL) )
#define CAN_TB_ptu4TXQESTS_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001180UL) )
#define CAN_TB_ptu4TXQFISTS_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001184UL) )
#define CAN_TB_ptu4TXQMSTS_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001188UL) )
#define CAN_TB_ptu4TXQOWSTS_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000118CUL) )
#define CAN_TB_ptu4TXQISTS_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001190UL) )
#define CAN_TB_ptu4TXQOFTISTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001194UL) )
#define CAN_TB_ptu4TXQOFRISTS_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001198UL) )
#define CAN_TB_ptu4TXQFSTS_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000119CUL) )
#define CAN_TB_ptu4GTINTSTS_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001300UL) )
#define CAN_TB_ptu4GTSTCFG_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001308UL) )
#define CAN_TB_ptu4GTSTCTR_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000130CUL) )
#define CAN_TB_ptu4GFDCFG_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001314UL) )
#define CAN_TB_ptu4GLOCKK_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000131CUL) )
#define CAN_TB_ptu4GAFLIGNENT_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001324UL) )
#define CAN_TB_ptu4GAFLIGNCTR_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001328UL) )
#define CAN_TB_ptu4CDTCT_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001330UL) )
#define CAN_TB_ptu4CDTSTS_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001334UL) )
#define CAN_TB_ptu4CDTTCT_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001340UL) )
#define CAN_TB_ptu4CDTTSTS_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001344UL) )
#define CAN_TB_ptu4GPFLECTR_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001370UL) )
#define CAN_TB_ptu4GPFLCFG_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001374UL) )
#define CAN_TB_ptu4GRSTC_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001380UL) )
#define CAN_TB_ptu4GFCMC_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001384UL) )
#define CAN_TB_ptu4GFTBAC_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000138CUL) )
#define CAN_TB_ptu4GFFIMC_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001390UL) )
#define CAN_TB_ptu4GVMEIS_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001394UL) )
#define CAN_TB_ptu4VMRFCFG_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000013C0UL) )
#define CAN_TB_ptstGAFL_ADDR            ( (volatile CanTbRegRxRuleType *)(CAN_TB_REG_BASE_ADDR + 0x00001800UL) )
#define CAN_TB_ptstGPFL_ADDR            ( (volatile CanTbRegPFLType *)(CAN_TB_REG_BASE_ADDR + 0x00001A00UL) )
#define CAN_TB_ptu4RPGACC_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008400UL) )
#define CAN_TB_ptstRM_ADDR              ( (volatile CanTbRegCANRMType *)(CAN_TB_REG_BASE_ADDR + 0x00002000UL) )
#define CAN_TB_ptstRF_ADDR              ( (volatile CanTbRegCANRFType *)(CAN_TB_REG_BASE_ADDR + 0x00006000UL) )


#define CAN_TB_RAM_SIZE                     ( CAN_CFG_RAM_SIZE_0 )

#define CAN_TB_TESTPAGENUM                  ( CAN_TB_RAM_SIZE / 256UL )

#define CAN_TB_TESTREGNUM                   ( ( CAN_TB_RAM_SIZE % 256UL ) / 4UL )

#define CAN_TB_TESTPAGE_CYCLE               ( ( CAN_TB_TESTPAGENUM - 1UL ) / ( (uint32)CAN_CFG_CHKSTKREG_LIMIT - 1UL ) )

#define CAN_TB_TESTPAGE_MOD                 ( ( CAN_TB_TESTPAGENUM - 1UL ) % ( (uint32)CAN_CFG_CHKSTKREG_LIMIT - 1UL ) )

#define CAN_TB_TESTPAGE_MOD_CYCLE(num)      ( ( ( num ) > CAN_TB_TESTPAGE_MOD ) ? 0UL : 1UL )


#if (CAN_CFG_CHKSTKREG_LIMIT >= 1U)
#define CAN_TB_STUCK_CHK_PAGE_0             ( (CAN_CFG_CHKSTKREG_LIMIT == 1U) ? CAN_TB_TESTPAGENUM : 1UL )
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 1U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 5U)
#define CAN_TB_STUCK_CHK_PAGE_1             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 1UL ) )
#define CAN_TB_STUCK_CHK_PAGE_2             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 2UL ) )
#define CAN_TB_STUCK_CHK_PAGE_3             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 3UL ) )
#define CAN_TB_STUCK_CHK_PAGE_4             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 4UL ) )
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 5U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 10U)
#define CAN_TB_STUCK_CHK_PAGE_5             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 5UL ) )
#define CAN_TB_STUCK_CHK_PAGE_6             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 6UL ) )
#define CAN_TB_STUCK_CHK_PAGE_7             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 7UL ) )
#define CAN_TB_STUCK_CHK_PAGE_8             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 8UL ) )
#define CAN_TB_STUCK_CHK_PAGE_9             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 9UL ) )
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 10U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 12U)
#define CAN_TB_STUCK_CHK_PAGE_10            ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 10UL ) )
#define CAN_TB_STUCK_CHK_PAGE_11            ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 11UL ) )
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 12U) */

#if (CAN_CFG_CHKSTKREG_LIMIT >= 1U)
#define CAN_TB_STUCK_CHK_START_0            ( 0UL )
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 1U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 5U)
#define CAN_TB_STUCK_CHK_START_1            ( CAN_TB_STUCK_CHK_PAGE_0 )
#define CAN_TB_STUCK_CHK_START_2            ( CAN_TB_STUCK_CHK_START_1  + CAN_TB_STUCK_CHK_PAGE_1 )
#define CAN_TB_STUCK_CHK_START_3            ( CAN_TB_STUCK_CHK_START_2  + CAN_TB_STUCK_CHK_PAGE_2 )
#define CAN_TB_STUCK_CHK_START_4            ( CAN_TB_STUCK_CHK_START_3  + CAN_TB_STUCK_CHK_PAGE_3 )
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 5U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 10U)
#define CAN_TB_STUCK_CHK_START_5            ( CAN_TB_STUCK_CHK_START_4  + CAN_TB_STUCK_CHK_PAGE_4 )
#define CAN_TB_STUCK_CHK_START_6            ( CAN_TB_STUCK_CHK_START_5  + CAN_TB_STUCK_CHK_PAGE_5 )
#define CAN_TB_STUCK_CHK_START_7            ( CAN_TB_STUCK_CHK_START_6  + CAN_TB_STUCK_CHK_PAGE_6 )
#define CAN_TB_STUCK_CHK_START_8            ( CAN_TB_STUCK_CHK_START_7  + CAN_TB_STUCK_CHK_PAGE_7 )
#define CAN_TB_STUCK_CHK_START_9            ( CAN_TB_STUCK_CHK_START_8  + CAN_TB_STUCK_CHK_PAGE_8 )
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 10U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 12U)
#define CAN_TB_STUCK_CHK_START_10           ( CAN_TB_STUCK_CHK_START_9  + CAN_TB_STUCK_CHK_PAGE_9 )
#define CAN_TB_STUCK_CHK_START_11           ( CAN_TB_STUCK_CHK_START_10 + CAN_TB_STUCK_CHK_PAGE_10 )
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 12U) */


#define CAN_TB_u4GAFLID_DUMMY               ( 0xFFFFFFFFUL )
#define CAN_TB_u4GAFLP0_DUMMY               ( 0x00000000UL )
#define CAN_TB_u4GAFLP1_DUMMY               ( 0x00000000UL )
#define CAN_TB_u1RXMASK_DUMMY               ( 0U )

#define CAN_TB_u4RXMB_CH0_INT               ( (uint32)( 0x00000001UL << ( ( 0U * 3U ) + 0U + 8U ) ) )
#define CAN_TB_u4RXMB_CH0_POL               ( (uint32)( 0x00000001UL << ( ( 0U * 3U ) + 1U + 8U ) ) )
#define CAN_TB_u4RXMB_CH1_INT               ( (uint32)( 0x00000001UL << ( ( 1U * 3U ) + 0U + 8U ) ) )
#define CAN_TB_u4RXMB_CH1_POL               ( (uint32)( 0x00000001UL << ( ( 1U * 3U ) + 1U + 8U ) ) )
#define CAN_TB_u4RXMB_CH2_INT               ( (uint32)( 0x00000001UL << ( ( 2U * 3U ) + 0U + 8U ) ) )
#define CAN_TB_u4RXMB_CH2_POL               ( (uint32)( 0x00000001UL << ( ( 2U * 3U ) + 1U + 8U ) ) )
#define CAN_TB_u4RXMB_CH3_INT               ( (uint32)( 0x00000001UL << ( ( 3U * 3U ) + 0U + 8U ) ) )
#define CAN_TB_u4RXMB_CH3_POL               ( (uint32)( 0x00000001UL << ( ( 3U * 3U ) + 1U + 8U ) ) )
#define CAN_TB_u4RXMB_CH4_INT               ( (uint32)( 0x00000001UL << ( ( 4U * 3U ) + 0U + 8U ) ) )
#define CAN_TB_u4RXMB_CH4_POL               ( (uint32)( 0x00000001UL << ( ( 4U * 3U ) + 1U + 8U ) ) )
#define CAN_TB_u4RXMB_CH5_INT               ( (uint32)( 0x00000001UL << ( ( 5U * 3U ) + 0U + 8U ) ) )
#define CAN_TB_u4RXMB_CH5_POL               ( (uint32)( 0x00000001UL << ( ( 5U * 3U ) + 1U + 8U ) ) )
#define CAN_TB_u4RXMB_CH6_INT               ( (uint32)( 0x00000001UL << ( ( 6U * 3U ) + 0U + 8U ) ) )
#define CAN_TB_u4RXMB_CH6_POL               ( (uint32)( 0x00000001UL << ( ( 6U * 3U ) + 1U + 8U ) ) )
#define CAN_TB_u4RXMB_CH7_INT               ( (uint32)( 0x00000001UL << ( ( 7U * 3U ) + 0U + 8U ) ) )
#define CAN_TB_u4RXMB_CH7_POL               ( (uint32)( 0x00000001UL << ( ( 7U * 3U ) + 1U + 8U ) ) )


#define CAN_TB_u1RXMASKREFIDX_IDTYPE( id ) \
    ( (((id) & CAN_u4BIT31) != CAN_u4BIT_NONE) ? (uint8)( CAN_CFG_FILTER_MASK_NUM + 1U ) : (uint8)CAN_CFG_FILTER_MASK_NUM )

#define CAN_TB_u1CONV_RXMASKREFIDX( no, id ) \
    ( ((no) == CAN_RXMASK_NOUSE) ? CAN_TB_u1RXMASKREFIDX_IDTYPE( id ) : (uint8)(no) )


#define CAN_TB_u4RXMASK_EXT( no )           ( ((~(CAN_CFG_FILTER_MASK_VALUE_##no)) & CAN_u4GAFLM_GAFLIDM_EXT_MSK) | CAN_u4GAFLM_GAFLRTRM_SET | CAN_u4GAFLM_GAFLIDEM_SET )

#define CAN_TB_u4RXMASK_STD( no )           ( ((~(CAN_CFG_FILTER_MASK_VALUE_##no)) & CAN_u4GAFLM_GAFLIDM_STD_MSK) | CAN_u4GAFLM_GAFLRTRM_SET | CAN_u4GAFLM_GAFLIDEM_SET )

#define CAN_TB_u4RXMASK_VAL( no ) \
    ( ((CAN_CFG_FILTER_MASK_VALUE_##no & CAN_u4BIT31) != CAN_u4BIT_NONE) ? CAN_TB_u4RXMASK_EXT( no ) : CAN_TB_u4RXMASK_STD( no ) )


#define CAN_TB_u4MB_RXLABEL( mb )           ( (uint32)( ( (uint32)(mb) ) << 16U ) & 0xFFFF0000UL )


#define CAN_TB_u4MB_RXKIND_0( mb ) \
        ( ((CAN_TB_MBSET_0( mb ) & CAN_MB_INTERRUPT) != CAN_MB_NOUSE) ? CAN_TB_u4RXMB_CH0_INT : CAN_TB_u4RXMB_CH0_POL )
#define CAN_TB_u4MB_RXKIND_1( mb ) \
        ( ((CAN_TB_MBSET_1( mb ) & CAN_MB_INTERRUPT) != CAN_MB_NOUSE) ? CAN_TB_u4RXMB_CH1_INT : CAN_TB_u4RXMB_CH1_POL )
#define CAN_TB_u4MB_RXKIND_2( mb ) \
        ( ((CAN_TB_MBSET_2( mb ) & CAN_MB_INTERRUPT) != CAN_MB_NOUSE) ? CAN_TB_u4RXMB_CH2_INT : CAN_TB_u4RXMB_CH2_POL )
#define CAN_TB_u4MB_RXKIND_3( mb ) \
        ( ((CAN_TB_MBSET_3( mb ) & CAN_MB_INTERRUPT) != CAN_MB_NOUSE) ? CAN_TB_u4RXMB_CH3_INT : CAN_TB_u4RXMB_CH3_POL )
#define CAN_TB_u4MB_RXKIND_4( mb ) \
        ( ((CAN_TB_MBSET_4( mb ) & CAN_MB_INTERRUPT) != CAN_MB_NOUSE) ? CAN_TB_u4RXMB_CH4_INT : CAN_TB_u4RXMB_CH4_POL )
#define CAN_TB_u4MB_RXKIND_5( mb ) \
        ( ((CAN_TB_MBSET_5( mb ) & CAN_MB_INTERRUPT) != CAN_MB_NOUSE) ? CAN_TB_u4RXMB_CH5_INT : CAN_TB_u4RXMB_CH5_POL )
#define CAN_TB_u4MB_RXKIND_6( mb ) \
        ( ((CAN_TB_MBSET_6( mb ) & CAN_MB_INTERRUPT) != CAN_MB_NOUSE) ? CAN_TB_u4RXMB_CH6_INT : CAN_TB_u4RXMB_CH6_POL )
#define CAN_TB_u4MB_RXKIND_7( mb ) \
        ( ((CAN_TB_MBSET_7( mb ) & CAN_MB_INTERRUPT) != CAN_MB_NOUSE) ? CAN_TB_u4RXMB_CH7_INT : CAN_TB_u4RXMB_CH7_POL )
#define CAN_TB_u4MB_RXKIND( ch, mb )        ( CAN_TB_u4MB_RXKIND_##ch( mb ) )


#define CAN_TB_u4MBBIT000                   (0x00000001UL)
#define CAN_TB_u4MBBIT001                   (0x00000002UL)
#define CAN_TB_u4MBBIT002                   (0x00000004UL)
#define CAN_TB_u4MBBIT003                   (0x00000008UL)
#define CAN_TB_u4MBBIT004                   (0x00000010UL)
#define CAN_TB_u4MBBIT005                   (0x00000020UL)
#define CAN_TB_u4MBBIT006                   (0x00000040UL)
#define CAN_TB_u4MBBIT007                   (0x00000080UL)
#define CAN_TB_u4MBBIT008                   (0x00000100UL)
#define CAN_TB_u4MBBIT009                   (0x00000200UL)
#define CAN_TB_u4MBBIT010                   (0x00000400UL)
#define CAN_TB_u4MBBIT011                   (0x00000800UL)
#define CAN_TB_u4MBBIT012                   (0x00001000UL)
#define CAN_TB_u4MBBIT013                   (0x00002000UL)
#define CAN_TB_u4MBBIT014                   (0x00004000UL)
#define CAN_TB_u4MBBIT015                   (0x00008000UL)
#define CAN_TB_u4MBBIT016                   (0x00010000UL)
#define CAN_TB_u4MBBIT017                   (0x00020000UL)
#define CAN_TB_u4MBBIT018                   (0x00040000UL)
#define CAN_TB_u4MBBIT019                   (0x00080000UL)
#define CAN_TB_u4MBBIT020                   (0x00100000UL)
#define CAN_TB_u4MBBIT021                   (0x00200000UL)
#define CAN_TB_u4MBBIT022                   (0x00400000UL)
#define CAN_TB_u4MBBIT023                   (0x00800000UL)
#define CAN_TB_u4MBBIT024                   (0x01000000UL)
#define CAN_TB_u4MBBIT025                   (0x02000000UL)
#define CAN_TB_u4MBBIT026                   (0x04000000UL)
#define CAN_TB_u4MBBIT027                   (0x08000000UL)
#define CAN_TB_u4MBBIT028                   (0x10000000UL)
#define CAN_TB_u4MBBIT029                   (0x20000000UL)
#define CAN_TB_u4MBBIT030                   (0x40000000UL)
#define CAN_TB_u4MBBIT031                   (0x80000000UL)
#define CAN_TB_u4MBBIT032                   (0x00000001UL)
#define CAN_TB_u4MBBIT033                   (0x00000002UL)
#define CAN_TB_u4MBBIT034                   (0x00000004UL)
#define CAN_TB_u4MBBIT035                   (0x00000008UL)
#define CAN_TB_u4MBBIT036                   (0x00000010UL)
#define CAN_TB_u4MBBIT037                   (0x00000020UL)
#define CAN_TB_u4MBBIT038                   (0x00000040UL)
#define CAN_TB_u4MBBIT039                   (0x00000080UL)
#define CAN_TB_u4MBBIT040                   (0x00000100UL)
#define CAN_TB_u4MBBIT041                   (0x00000200UL)
#define CAN_TB_u4MBBIT042                   (0x00000400UL)
#define CAN_TB_u4MBBIT043                   (0x00000800UL)
#define CAN_TB_u4MBBIT044                   (0x00001000UL)
#define CAN_TB_u4MBBIT045                   (0x00002000UL)
#define CAN_TB_u4MBBIT046                   (0x00004000UL)
#define CAN_TB_u4MBBIT047                   (0x00008000UL)
#define CAN_TB_u4MBBIT048                   (0x00010000UL)
#define CAN_TB_u4MBBIT049                   (0x00020000UL)
#define CAN_TB_u4MBBIT050                   (0x00040000UL)
#define CAN_TB_u4MBBIT051                   (0x00080000UL)
#define CAN_TB_u4MBBIT052                   (0x00100000UL)
#define CAN_TB_u4MBBIT053                   (0x00200000UL)
#define CAN_TB_u4MBBIT054                   (0x00400000UL)
#define CAN_TB_u4MBBIT055                   (0x00800000UL)
#define CAN_TB_u4MBBIT056                   (0x01000000UL)
#define CAN_TB_u4MBBIT057                   (0x02000000UL)
#define CAN_TB_u4MBBIT058                   (0x04000000UL)
#define CAN_TB_u4MBBIT059                   (0x08000000UL)
#define CAN_TB_u4MBBIT060                   (0x10000000UL)
#define CAN_TB_u4MBBIT061                   (0x20000000UL)
#define CAN_TB_u4MBBIT062                   (0x40000000UL)
#define CAN_TB_u4MBBIT063                   (0x80000000UL)
#define CAN_TB_u4MBBIT064                   (0x00000001UL)
#define CAN_TB_u4MBBIT065                   (0x00000002UL)
#define CAN_TB_u4MBBIT066                   (0x00000004UL)
#define CAN_TB_u4MBBIT067                   (0x00000008UL)
#define CAN_TB_u4MBBIT068                   (0x00000010UL)
#define CAN_TB_u4MBBIT069                   (0x00000020UL)
#define CAN_TB_u4MBBIT070                   (0x00000040UL)
#define CAN_TB_u4MBBIT071                   (0x00000080UL)
#define CAN_TB_u4MBBIT072                   (0x00000100UL)
#define CAN_TB_u4MBBIT073                   (0x00000200UL)
#define CAN_TB_u4MBBIT074                   (0x00000400UL)
#define CAN_TB_u4MBBIT075                   (0x00000800UL)
#define CAN_TB_u4MBBIT076                   (0x00001000UL)
#define CAN_TB_u4MBBIT077                   (0x00002000UL)
#define CAN_TB_u4MBBIT078                   (0x00004000UL)
#define CAN_TB_u4MBBIT079                   (0x00008000UL)
#define CAN_TB_u4MBBIT080                   (0x00010000UL)
#define CAN_TB_u4MBBIT081                   (0x00020000UL)
#define CAN_TB_u4MBBIT082                   (0x00040000UL)
#define CAN_TB_u4MBBIT083                   (0x00080000UL)
#define CAN_TB_u4MBBIT084                   (0x00100000UL)
#define CAN_TB_u4MBBIT085                   (0x00200000UL)
#define CAN_TB_u4MBBIT086                   (0x00400000UL)
#define CAN_TB_u4MBBIT087                   (0x00800000UL)
#define CAN_TB_u4MBBIT088                   (0x01000000UL)
#define CAN_TB_u4MBBIT089                   (0x02000000UL)
#define CAN_TB_u4MBBIT090                   (0x04000000UL)
#define CAN_TB_u4MBBIT091                   (0x08000000UL)
#define CAN_TB_u4MBBIT092                   (0x10000000UL)
#define CAN_TB_u4MBBIT093                   (0x20000000UL)
#define CAN_TB_u4MBBIT094                   (0x40000000UL)
#define CAN_TB_u4MBBIT095                   (0x80000000UL)
#define CAN_TB_u4MBBIT096                   (0x00000001UL)
#define CAN_TB_u4MBBIT097                   (0x00000002UL)
#define CAN_TB_u4MBBIT098                   (0x00000004UL)
#define CAN_TB_u4MBBIT099                   (0x00000008UL)
#define CAN_TB_u4MBBIT100                   (0x00000010UL)
#define CAN_TB_u4MBBIT101                   (0x00000020UL)
#define CAN_TB_u4MBBIT102                   (0x00000040UL)
#define CAN_TB_u4MBBIT103                   (0x00000080UL)
#define CAN_TB_u4MBBIT104                   (0x00000100UL)
#define CAN_TB_u4MBBIT105                   (0x00000200UL)
#define CAN_TB_u4MBBIT106                   (0x00000400UL)
#define CAN_TB_u4MBBIT107                   (0x00000800UL)
#define CAN_TB_u4MBBIT108                   (0x00001000UL)
#define CAN_TB_u4MBBIT109                   (0x00002000UL)
#define CAN_TB_u4MBBIT110                   (0x00004000UL)
#define CAN_TB_u4MBBIT111                   (0x00008000UL)
#define CAN_TB_u4MBBIT112                   (0x00010000UL)
#define CAN_TB_u4MBBIT113                   (0x00020000UL)
#define CAN_TB_u4MBBIT114                   (0x00040000UL)
#define CAN_TB_u4MBBIT115                   (0x00080000UL)
#define CAN_TB_u4MBBIT116                   (0x00100000UL)
#define CAN_TB_u4MBBIT117                   (0x00200000UL)
#define CAN_TB_u4MBBIT118                   (0x00400000UL)
#define CAN_TB_u4MBBIT119                   (0x00800000UL)
#define CAN_TB_u4MBBIT120                   (0x01000000UL)
#define CAN_TB_u4MBBIT121                   (0x02000000UL)
#define CAN_TB_u4MBBIT122                   (0x04000000UL)
#define CAN_TB_u4MBBIT123                   (0x08000000UL)
#define CAN_TB_u4MBBIT124                   (0x10000000UL)
#define CAN_TB_u4MBBIT125                   (0x20000000UL)
#define CAN_TB_u4MBBIT126                   (0x40000000UL)
#define CAN_TB_u4MBBIT127                   (0x80000000UL)
#define CAN_TB_u4MBBIT128                   (0x00000001UL)
#define CAN_TB_u4MBBIT129                   (0x00000002UL)
#define CAN_TB_u4MBBIT130                   (0x00000004UL)
#define CAN_TB_u4MBBIT131                   (0x00000008UL)
#define CAN_TB_u4MBBIT132                   (0x00000010UL)
#define CAN_TB_u4MBBIT133                   (0x00000020UL)
#define CAN_TB_u4MBBIT134                   (0x00000040UL)
#define CAN_TB_u4MBBIT135                   (0x00000080UL)
#define CAN_TB_u4MBBIT136                   (0x00000100UL)
#define CAN_TB_u4MBBIT137                   (0x00000200UL)
#define CAN_TB_u4MBBIT138                   (0x00000400UL)
#define CAN_TB_u4MBBIT139                   (0x00000800UL)
#define CAN_TB_u4MBBIT140                   (0x00001000UL)
#define CAN_TB_u4MBBIT141                   (0x00002000UL)
#define CAN_TB_u4MBBIT142                   (0x00004000UL)
#define CAN_TB_u4MBBIT143                   (0x00008000UL)
#define CAN_TB_u4MBBIT144                   (0x00010000UL)
#define CAN_TB_u4MBBIT145                   (0x00020000UL)
#define CAN_TB_u4MBBIT146                   (0x00040000UL)
#define CAN_TB_u4MBBIT147                   (0x00080000UL)
#define CAN_TB_u4MBBIT148                   (0x00100000UL)
#define CAN_TB_u4MBBIT149                   (0x00200000UL)
#define CAN_TB_u4MBBIT150                   (0x00400000UL)
#define CAN_TB_u4MBBIT151                   (0x00800000UL)
#define CAN_TB_u4MBBIT152                   (0x01000000UL)
#define CAN_TB_u4MBBIT153                   (0x02000000UL)
#define CAN_TB_u4MBBIT154                   (0x04000000UL)
#define CAN_TB_u4MBBIT155                   (0x08000000UL)
#define CAN_TB_u4MBBIT156                   (0x10000000UL)
#define CAN_TB_u4MBBIT157                   (0x20000000UL)
#define CAN_TB_u4MBBIT158                   (0x40000000UL)
#define CAN_TB_u4MBBIT159                   (0x80000000UL)
#define CAN_TB_u4MBBIT160                   (0x00000001UL)
#define CAN_TB_u4MBBIT161                   (0x00000002UL)
#define CAN_TB_u4MBBIT162                   (0x00000004UL)
#define CAN_TB_u4MBBIT163                   (0x00000008UL)
#define CAN_TB_u4MBBIT164                   (0x00000010UL)
#define CAN_TB_u4MBBIT165                   (0x00000020UL)
#define CAN_TB_u4MBBIT166                   (0x00000040UL)
#define CAN_TB_u4MBBIT167                   (0x00000080UL)
#define CAN_TB_u4MBBIT168                   (0x00000100UL)
#define CAN_TB_u4MBBIT169                   (0x00000200UL)
#define CAN_TB_u4MBBIT170                   (0x00000400UL)
#define CAN_TB_u4MBBIT171                   (0x00000800UL)
#define CAN_TB_u4MBBIT172                   (0x00001000UL)
#define CAN_TB_u4MBBIT173                   (0x00002000UL)
#define CAN_TB_u4MBBIT174                   (0x00004000UL)
#define CAN_TB_u4MBBIT175                   (0x00008000UL)
#define CAN_TB_u4MBBIT176                   (0x00010000UL)
#define CAN_TB_u4MBBIT177                   (0x00020000UL)
#define CAN_TB_u4MBBIT178                   (0x00040000UL)
#define CAN_TB_u4MBBIT179                   (0x00080000UL)
#define CAN_TB_u4MBBIT180                   (0x00100000UL)
#define CAN_TB_u4MBBIT181                   (0x00200000UL)
#define CAN_TB_u4MBBIT182                   (0x00400000UL)
#define CAN_TB_u4MBBIT183                   (0x00800000UL)
#define CAN_TB_u4MBBIT184                   (0x01000000UL)
#define CAN_TB_u4MBBIT185                   (0x02000000UL)
#define CAN_TB_u4MBBIT186                   (0x04000000UL)
#define CAN_TB_u4MBBIT187                   (0x08000000UL)
#define CAN_TB_u4MBBIT188                   (0x10000000UL)
#define CAN_TB_u4MBBIT189                   (0x20000000UL)
#define CAN_TB_u4MBBIT190                   (0x40000000UL)
#define CAN_TB_u4MBBIT191                   (0x80000000UL)
#define CAN_TB_u4MBBIT( mb )                ( CAN_TB_u4MBBIT##mb )

#define CAN_TB_u4MBBIT_TX( ch, mb )         ( ((CAN_TB_MBSET( ch, mb ) & CAN_MB_TRANSMIT)  != CAN_MB_NOUSE) ? (CAN_TB_u4MBBIT( mb )) : CAN_u4BIT_NONE )
#define CAN_TB_u4MBBIT_RX( ch, mb )         ( ((CAN_TB_MBSET( ch, mb ) & CAN_MB_RECEPTION) != CAN_MB_NOUSE) ? (CAN_TB_u4MBBIT( mb )) : CAN_u4BIT_NONE )
#define CAN_TB_u4MBBIT_INT( ch, mb )        ( ((CAN_TB_MBSET( ch, mb ) & CAN_MB_INTERRUPT) != CAN_MB_NOUSE) ? (CAN_TB_u4MBBIT( mb )) : CAN_u4BIT_NONE )
#define CAN_TB_u4MBBIT_POL( ch, mb )        ( ((CAN_TB_MBSET( ch, mb ) & CAN_MB_POLLING)   != CAN_MB_NOUSE) ? (CAN_TB_u4MBBIT( mb )) : CAN_u4BIT_NONE )
#define CAN_TB_u4MBBIT_MB( ch, kind, mb )   ( CAN_TB_u4MBBIT_##kind( ch, mb ) )

#define CAN_TB_u4MBBIT_LLL0( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 000 ) | CAN_TB_u4MBBIT_MB( ch, kind, 001 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 002 ) | CAN_TB_u4MBBIT_MB( ch, kind, 003 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 004 ) | CAN_TB_u4MBBIT_MB( ch, kind, 005 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 006 ) | CAN_TB_u4MBBIT_MB( ch, kind, 007 ) )
#define CAN_TB_u4MBBIT_LLL1( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 008 ) | CAN_TB_u4MBBIT_MB( ch, kind, 009 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 010 ) | CAN_TB_u4MBBIT_MB( ch, kind, 011 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 012 ) | CAN_TB_u4MBBIT_MB( ch, kind, 013 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 014 ) | CAN_TB_u4MBBIT_MB( ch, kind, 015 ) )
#define CAN_TB_u4MBBIT_LLL2( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 016 ) | CAN_TB_u4MBBIT_MB( ch, kind, 017 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 018 ) | CAN_TB_u4MBBIT_MB( ch, kind, 019 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 020 ) | CAN_TB_u4MBBIT_MB( ch, kind, 021 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 022 ) | CAN_TB_u4MBBIT_MB( ch, kind, 023 ) )
#define CAN_TB_u4MBBIT_LLL3( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 024 ) | CAN_TB_u4MBBIT_MB( ch, kind, 025 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 026 ) | CAN_TB_u4MBBIT_MB( ch, kind, 027 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 028 ) | CAN_TB_u4MBBIT_MB( ch, kind, 029 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 030 ) | CAN_TB_u4MBBIT_MB( ch, kind, 031 ) )
#define CAN_TB_u4MBBIT_LLL( ch, kind ) \
   (  CAN_TB_u4MBBIT_LLL0( ch, kind ) | CAN_TB_u4MBBIT_LLL1( ch, kind ) \
    | CAN_TB_u4MBBIT_LLL2( ch, kind ) | CAN_TB_u4MBBIT_LLL3( ch, kind ) )

#define CAN_TB_u4MBBIT_LLH0( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 032 ) | CAN_TB_u4MBBIT_MB( ch, kind, 033 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 034 ) | CAN_TB_u4MBBIT_MB( ch, kind, 035 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 036 ) | CAN_TB_u4MBBIT_MB( ch, kind, 037 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 038 ) | CAN_TB_u4MBBIT_MB( ch, kind, 039 ) )
#define CAN_TB_u4MBBIT_LLH1( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 040 ) | CAN_TB_u4MBBIT_MB( ch, kind, 041 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 042 ) | CAN_TB_u4MBBIT_MB( ch, kind, 043 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 044 ) | CAN_TB_u4MBBIT_MB( ch, kind, 045 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 046 ) | CAN_TB_u4MBBIT_MB( ch, kind, 047 ) )
#define CAN_TB_u4MBBIT_LLH2( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 048 ) | CAN_TB_u4MBBIT_MB( ch, kind, 049 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 050 ) | CAN_TB_u4MBBIT_MB( ch, kind, 051 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 052 ) | CAN_TB_u4MBBIT_MB( ch, kind, 053 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 054 ) | CAN_TB_u4MBBIT_MB( ch, kind, 055 ) )
#define CAN_TB_u4MBBIT_LLH3( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 056 ) | CAN_TB_u4MBBIT_MB( ch, kind, 057 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 058 ) | CAN_TB_u4MBBIT_MB( ch, kind, 059 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 060 ) | CAN_TB_u4MBBIT_MB( ch, kind, 061 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 062 ) | CAN_TB_u4MBBIT_MB( ch, kind, 063 ) )
#define CAN_TB_u4MBBIT_LLH( ch, kind ) \
   (  CAN_TB_u4MBBIT_LLH0( ch, kind ) | CAN_TB_u4MBBIT_LLH1( ch, kind ) \
    | CAN_TB_u4MBBIT_LLH2( ch, kind ) | CAN_TB_u4MBBIT_LLH3( ch, kind ) )

#define CAN_TB_u4MBBIT_LHL0( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 064 ) | CAN_TB_u4MBBIT_MB( ch, kind, 065 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 066 ) | CAN_TB_u4MBBIT_MB( ch, kind, 067 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 068 ) | CAN_TB_u4MBBIT_MB( ch, kind, 069 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 070 ) | CAN_TB_u4MBBIT_MB( ch, kind, 071 ) )
#define CAN_TB_u4MBBIT_LHL1( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 072 ) | CAN_TB_u4MBBIT_MB( ch, kind, 073 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 074 ) | CAN_TB_u4MBBIT_MB( ch, kind, 075 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 076 ) | CAN_TB_u4MBBIT_MB( ch, kind, 077 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 078 ) | CAN_TB_u4MBBIT_MB( ch, kind, 079 ) )
#define CAN_TB_u4MBBIT_LHL2( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 080 ) | CAN_TB_u4MBBIT_MB( ch, kind, 081 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 082 ) | CAN_TB_u4MBBIT_MB( ch, kind, 083 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 084 ) | CAN_TB_u4MBBIT_MB( ch, kind, 085 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 086 ) | CAN_TB_u4MBBIT_MB( ch, kind, 087 ) )
#define CAN_TB_u4MBBIT_LHL3( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 088 ) | CAN_TB_u4MBBIT_MB( ch, kind, 089 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 090 ) | CAN_TB_u4MBBIT_MB( ch, kind, 091 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 092 ) | CAN_TB_u4MBBIT_MB( ch, kind, 093 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 094 ) | CAN_TB_u4MBBIT_MB( ch, kind, 095 ) )
#define CAN_TB_u4MBBIT_LHL( ch, kind ) \
   (  CAN_TB_u4MBBIT_LHL0( ch, kind ) | CAN_TB_u4MBBIT_LHL1( ch, kind ) \
    | CAN_TB_u4MBBIT_LHL2( ch, kind ) | CAN_TB_u4MBBIT_LHL3( ch, kind ) )

#define CAN_TB_u4MBBIT_LHH0( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 096 ) | CAN_TB_u4MBBIT_MB( ch, kind, 097 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 098 ) | CAN_TB_u4MBBIT_MB( ch, kind, 099 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 100 ) | CAN_TB_u4MBBIT_MB( ch, kind, 101 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 102 ) | CAN_TB_u4MBBIT_MB( ch, kind, 103 ) )
#define CAN_TB_u4MBBIT_LHH1( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 104 ) | CAN_TB_u4MBBIT_MB( ch, kind, 105 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 106 ) | CAN_TB_u4MBBIT_MB( ch, kind, 107 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 108 ) | CAN_TB_u4MBBIT_MB( ch, kind, 109 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 110 ) | CAN_TB_u4MBBIT_MB( ch, kind, 111 ) )
#define CAN_TB_u4MBBIT_LHH2( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 112 ) | CAN_TB_u4MBBIT_MB( ch, kind, 113 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 114 ) | CAN_TB_u4MBBIT_MB( ch, kind, 115 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 116 ) | CAN_TB_u4MBBIT_MB( ch, kind, 117 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 118 ) | CAN_TB_u4MBBIT_MB( ch, kind, 119 ) )
#define CAN_TB_u4MBBIT_LHH3( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 120 ) | CAN_TB_u4MBBIT_MB( ch, kind, 121 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 122 ) | CAN_TB_u4MBBIT_MB( ch, kind, 123 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 124 ) | CAN_TB_u4MBBIT_MB( ch, kind, 125 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 126 ) | CAN_TB_u4MBBIT_MB( ch, kind, 127 ) )
#define CAN_TB_u4MBBIT_LHH( ch, kind ) \
   (  CAN_TB_u4MBBIT_LHH0( ch, kind ) | CAN_TB_u4MBBIT_LHH1( ch, kind ) \
    | CAN_TB_u4MBBIT_LHH2( ch, kind ) | CAN_TB_u4MBBIT_LHH3( ch, kind ) )

#define CAN_TB_u4MBBIT_HLL0( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 128 ) | CAN_TB_u4MBBIT_MB( ch, kind, 129 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 130 ) | CAN_TB_u4MBBIT_MB( ch, kind, 131 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 132 ) | CAN_TB_u4MBBIT_MB( ch, kind, 133 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 134 ) | CAN_TB_u4MBBIT_MB( ch, kind, 135 ) )
#define CAN_TB_u4MBBIT_HLL1( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 136 ) | CAN_TB_u4MBBIT_MB( ch, kind, 137 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 138 ) | CAN_TB_u4MBBIT_MB( ch, kind, 139 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 140 ) | CAN_TB_u4MBBIT_MB( ch, kind, 141 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 142 ) | CAN_TB_u4MBBIT_MB( ch, kind, 143 ) )
#define CAN_TB_u4MBBIT_HLL2( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 144 ) | CAN_TB_u4MBBIT_MB( ch, kind, 145 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 146 ) | CAN_TB_u4MBBIT_MB( ch, kind, 147 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 148 ) | CAN_TB_u4MBBIT_MB( ch, kind, 149 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 150 ) | CAN_TB_u4MBBIT_MB( ch, kind, 151 ) )
#define CAN_TB_u4MBBIT_HLL3( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 152 ) | CAN_TB_u4MBBIT_MB( ch, kind, 153 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 154 ) | CAN_TB_u4MBBIT_MB( ch, kind, 155 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 156 ) | CAN_TB_u4MBBIT_MB( ch, kind, 157 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 158 ) | CAN_TB_u4MBBIT_MB( ch, kind, 159 ) )
#define CAN_TB_u4MBBIT_HLL( ch, kind ) \
   (  CAN_TB_u4MBBIT_HLL0( ch, kind ) | CAN_TB_u4MBBIT_HLL1( ch, kind ) \
    | CAN_TB_u4MBBIT_HLL2( ch, kind ) | CAN_TB_u4MBBIT_HLL3( ch, kind ) )

#define CAN_TB_u4MBBIT_HLH0( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 160 ) | CAN_TB_u4MBBIT_MB( ch, kind, 161 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 162 ) | CAN_TB_u4MBBIT_MB( ch, kind, 163 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 164 ) | CAN_TB_u4MBBIT_MB( ch, kind, 165 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 166 ) | CAN_TB_u4MBBIT_MB( ch, kind, 167 ) )
#define CAN_TB_u4MBBIT_HLH1( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 168 ) | CAN_TB_u4MBBIT_MB( ch, kind, 169 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 170 ) | CAN_TB_u4MBBIT_MB( ch, kind, 171 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 172 ) | CAN_TB_u4MBBIT_MB( ch, kind, 173 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 174 ) | CAN_TB_u4MBBIT_MB( ch, kind, 175 ) )
#define CAN_TB_u4MBBIT_HLH2( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 176 ) | CAN_TB_u4MBBIT_MB( ch, kind, 177 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 178 ) | CAN_TB_u4MBBIT_MB( ch, kind, 179 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 180 ) | CAN_TB_u4MBBIT_MB( ch, kind, 181 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 182 ) | CAN_TB_u4MBBIT_MB( ch, kind, 183 ) )
#define CAN_TB_u4MBBIT_HLH3( ch, kind ) \
   (  CAN_TB_u4MBBIT_MB( ch, kind, 184 ) | CAN_TB_u4MBBIT_MB( ch, kind, 185 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 186 ) | CAN_TB_u4MBBIT_MB( ch, kind, 187 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 188 ) | CAN_TB_u4MBBIT_MB( ch, kind, 189 ) \
    | CAN_TB_u4MBBIT_MB( ch, kind, 190 ) | CAN_TB_u4MBBIT_MB( ch, kind, 191 ) )
#define CAN_TB_u4MBBIT_HLH( ch, kind ) \
   (  CAN_TB_u4MBBIT_HLH0( ch, kind ) | CAN_TB_u4MBBIT_HLH1( ch, kind ) \
    | CAN_TB_u4MBBIT_HLH2( ch, kind ) | CAN_TB_u4MBBIT_HLH3( ch, kind ) )


#define CAN_TB_RXPOLLING_Lxx( ch ) \
 (((( CAN_TB_u4MBBIT_LLL( ch, RX ) & CAN_TB_u4MBBIT_LLL( ch, POL ) ) != CAN_u4BIT_NONE ) \
 ||(( CAN_TB_u4MBBIT_LLH( ch, RX ) & CAN_TB_u4MBBIT_LLH( ch, POL ) ) != CAN_u4BIT_NONE ) \
 ||(( CAN_TB_u4MBBIT_LHL( ch, RX ) & CAN_TB_u4MBBIT_LHL( ch, POL ) ) != CAN_u4BIT_NONE ) \
 ||(( CAN_TB_u4MBBIT_LHH( ch, RX ) & CAN_TB_u4MBBIT_LHH( ch, POL ) ) != CAN_u4BIT_NONE )) ? CAN_USE : CAN_NOUSE )

#define CAN_TB_RXPOLLING_Hxx( ch ) \
 (((( CAN_TB_u4MBBIT_HLL( ch, RX ) & CAN_TB_u4MBBIT_HLL( ch, POL ) ) != CAN_u4BIT_NONE ) \
 ||(( CAN_TB_u4MBBIT_HLH( ch, RX ) & CAN_TB_u4MBBIT_HLH( ch, POL ) ) != CAN_u4BIT_NONE )) ? CAN_USE : CAN_NOUSE )

#define CAN_TB_RXPOLLING( ch ) \
 ((( CAN_TB_RXPOLLING_Lxx( ch ) == CAN_USE ) \
 ||( CAN_TB_RXPOLLING_Hxx( ch ) == CAN_USE )) ? CAN_USE : CAN_NOUSE )


#define CAN_TB_u4TXMBBIT_L( ch, kind )      ( CAN_TB_u4MBBIT_LLL( ch, TX ) & CAN_TB_u4MBBIT_LLL( ch, kind ) )
#define CAN_TB_u4TXMBBIT_H( ch, kind )      ( CAN_TB_u4MBBIT_LLH( ch, TX ) & CAN_TB_u4MBBIT_LLH( ch, kind ) )


#define CAN_TB_u4CmNCFG_BTPTN_USERMASK      ( 0xFFFFFFFFUL )

#define CAN_TB_u4CmNCFG_UBTPTN( ch )        ( CAN_CFG_USER_BAUDRATE_##ch & CAN_TB_u4CmNCFG_BTPTN_USERMASK )
#define CAN_TB_BAUDRATE( ch )               ( CAN_CFG_CONTROLLER_BAUDRATE_##ch )

#define CAN_TB_u4CmNCFG_CONF( ch ) \
    ( (CAN_TB_BAUDRATE( ch ) == CAN_TB_USER_BAUDRATE) ? CAN_TB_u4CmNCFG_UBTPTN( ch ) : CAN_TB_BAUDRATE( ch ) )


#define CAN_TB_u4CmDCFG_BTPTN_USERMASK      ( 0x0F0F1FFFUL )
#define CAN_TB_u4CmDCFG_UBTPTN( ch )        ( CAN_CFG_USER_DBAUDRATE_##ch & CAN_TB_u4CmDCFG_BTPTN_USERMASK )
#define CAN_TB_CONTROLLER_DBAUDRATE( ch )   ( CAN_CFG_CONTROLLER_DBAUDRATE_##ch )
#define CAN_TB_DATABAUDRATE_CANFD( ch ) \
    ( (CAN_TB_CONTROLLER_DBAUDRATE( ch ) == CAN_TB_USER_DATABAUDRATE) ? CAN_TB_u4CmDCFG_UBTPTN( ch ) : CAN_TB_CONTROLLER_DBAUDRATE( ch ) )
#define CAN_TB_DATABAUDRATE_CAN             ( 0x00000000UL )

#define CAN_TB_u4CmDCFG_CONF( ch ) \
    ( (CAN_CFG_OPEMODE_##ch == CAN_OPEMODE_CAN) ? CAN_TB_DATABAUDRATE_CAN : CAN_TB_DATABAUDRATE_CANFD( ch ) )


#define CAN_TB_u4CMCTR_BASE                 ( 0x00800000UL )

#define CAN_TB_u4CMCTR_BOM_AUTO             ( 0x00000000UL )
#define CAN_TB_u4CMCTR_BOM_MANUAL           ( 0x00200000UL )

#define CAN_TB_u4CMCTR_BOM_CONF( ch ) \
    ( (CAN_CFG_BUSOFF_RECOVERY_##ch == CAN_MANUAL) ? CAN_TB_u4CMCTR_BOM_MANUAL : CAN_TB_u4CMCTR_BOM_AUTO )

#define CAN_TB_u4CMCTR_CONF( ch )           ( CAN_TB_u4CMCTR_BASE | CAN_TB_u4CMCTR_BOM_CONF( ch ) )


#define CAN_TB_u4CMFDCFG_CLOE_DIS           ( 0x00000000UL )
#define CAN_TB_u4CMFDCFG_CLOE_ENA           ( 0x40000000UL )

#define CAN_TB_u4CMFDCFG_REFE_DIS           ( 0x00000000UL )
#define CAN_TB_u4CMFDCFG_REFE_ENA           ( 0x20000000UL )

#define CAN_TB_u4CMFDCFG_REFE_CONF( ch ) \
    ( (CAN_CFG_EDGE_FILTERING_##ch == CAN_USE) ? CAN_TB_u4CMFDCFG_REFE_ENA : CAN_TB_u4CMFDCFG_REFE_DIS )

#define CAN_TB_u4CMFDCFG_DBRP( ch )         ( (uint32)( ( CAN_TB_u4CmDCFG_CONF( ch ) & CAN_TB_u4CmDCFG_BIT_DBRP   ) >> CAN_TB_CmDCFG_SFT_DBRP   ) )
#define CAN_TB_u4CMFDCFG_DTSEG1( ch )       ( (uint32)( ( CAN_TB_u4CmDCFG_CONF( ch ) & CAN_TB_u4CmDCFG_BIT_DTSEG1 ) >> CAN_TB_CmDCFG_SFT_DTSEG1 ) )
#define CAN_TB_u4CMFDCFG_TDCO_VAL( ch )     ( (uint32)( ( (uint32)( 1UL + ( CAN_TB_u4CMFDCFG_DTSEG1( ch ) + 1UL ) ) * ( CAN_TB_u4CMFDCFG_DBRP( ch ) + 1UL ) ) - 1UL ) )

#define CAN_TB_u4CMFDCFG_TDCO( ch )         ( (uint32)( CAN_TB_u4CMFDCFG_TDCO_VAL( ch ) << CAN_TB_CMFDCFG_SFT_TDCO ) & CAN_u4CMFDCFG_TDCO_MSK )

#define CAN_TB_u4CMFDCFG_TDCO_CONF( ch ) \
    ( (CAN_CFG_DBAUDRATE_SWT_##ch == CAN_USE) ? CAN_TB_u4CMFDCFG_TDCO( ch ) : 0x00000000UL )

#define CAN_TB_u4CMFDCFG_ESIC_ALWAYS        ( 0x00000000UL )
#define CAN_TB_u4CMFDCFG_ESIC_MB            ( 0x00000400UL )

#define CAN_TB_u4CMFDCFG_ESIC_CONF( ch ) \
    ( (CAN_CFG_ESI_##ch == CAN_USE) ? CAN_TB_u4CMFDCFG_ESIC_ALWAYS : CAN_TB_u4CMFDCFG_ESIC_MB )

#define CAN_TB_u4CMFDCFG_TDCE_DIS           ( 0x00000000UL )
#define CAN_TB_u4CMFDCFG_TDCE_ENA           ( 0x00000200UL )

#define CAN_TB_u4CMFDCFG_TDCE_CONF( ch ) \
    ( (CAN_CFG_DBAUDRATE_SWT_##ch == CAN_USE) ? CAN_TB_u4CMFDCFG_TDCE_ENA : CAN_TB_u4CMFDCFG_TDCE_DIS )

#define CAN_TB_u4CMFDCFG_TDCOC_MEASURE      ( 0x00000000UL )

#define CAN_TB_u4CMFDCFG_CONF_CAN           ( CAN_TB_u4CMFDCFG_CLOE_ENA )
#define CAN_TB_u4CMFDCFG_CONF_CANFD( ch ) \
    ( CAN_TB_u4CMFDCFG_CLOE_DIS        | CAN_TB_u4CMFDCFG_REFE_CONF( ch ) | CAN_TB_u4CMFDCFG_TDCO_CONF( ch ) \
    | CAN_TB_u4CMFDCFG_ESIC_CONF( ch ) | CAN_TB_u4CMFDCFG_TDCE_CONF( ch ) | CAN_TB_u4CMFDCFG_TDCOC_MEASURE )

#define CAN_TB_u4CMFDCFG_CONF( ch ) \
    ( (CAN_CFG_OPEMODE_##ch == CAN_OPEMODE_CAN) ? CAN_TB_u4CMFDCFG_CONF_CAN : CAN_TB_u4CMFDCFG_CONF_CANFD( ch ) )


#define CAN_TB_u4CFCC_CFDC_0                ( 0x00000000UL )
#define CAN_TB_u4CFCC_CFDC_4                ( 0x00200000UL )
#define CAN_TB_u4CFCC_CFDC_32               ( 0x00800000UL )
#define CAN_TB_u4CFCC_CFDC_48               ( 0x00A00000UL )
#define CAN_TB_u4CFCC_CFDC_64               ( 0x00C00000UL )

#define CAN_TB_RXPOL_FIFO_SIZE( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 32U ) ? CAN_TB_u4CFCC_CFDC_32 : CAN_TB_RXPOL_FIFO_SIZE_1( ch ) )
#define CAN_TB_RXPOL_FIFO_SIZE_1( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 48U ) ? CAN_TB_u4CFCC_CFDC_48 : CAN_TB_RXPOL_FIFO_SIZE_2( ch ) )
#define CAN_TB_RXPOL_FIFO_SIZE_2( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 64U ) ? CAN_TB_u4CFCC_CFDC_64 : CAN_TB_u4CFCC_CFDC_0 )

#define CAN_TB_u4CFCC_CFDC_RXPOL( ch )      ( CAN_TB_RXPOL_FIFO_SIZE( ch ) )

#define CAN_TB_u4CFCC_CFIM_CFIGCV           ( 0x00000000UL )
#define CAN_TB_u4CFCC_CFIM_ON_1MSG          ( 0x00001000UL )

#define CAN_TB_u4CFCC_CFM_RX                ( 0x00000000UL )

#define CAN_TB_u4CFCC_CFPLS_8               ( 0x00000000UL )
#define CAN_TB_u4CFCC_CFPLS_64              ( 0x00000070UL )

#define CAN_TB_u4CFCC_CFTXIE_DIS            ( 0x00000000UL )

#define CAN_TB_u4CFCC_CFRXIE_DIS            ( 0x00000000UL )
#define CAN_TB_u4CFCC_CFRXIE_ENA            ( 0x00000002UL )

#define CAN_TB_u4CFCC_CFE_NOUSE             ( 0x00000000UL )
#define CAN_TB_u4CFCC_CFE_USE               ( 0x00000001UL )

#define CAN_TB_u4CFCC_RXINT( ch )           ( CAN_TB_u4CFCC_CFDC_4           | CAN_TB_u4CFCC_CFIM_ON_1MSG | CAN_TB_u4CFCC_CFM_RX | CAN_TB_u4CFCC_CFPLS_64 | CAN_TB_u4CFCC_CFTXIE_DIS | CAN_TB_u4CFCC_CFRXIE_ENA | CAN_TB_u4CFCC_CFE_USE   )
#define CAN_TB_u4CFCC_RXPOL( ch )           ( CAN_TB_u4CFCC_CFDC_RXPOL( ch ) | CAN_TB_u4CFCC_CFIM_CFIGCV  | CAN_TB_u4CFCC_CFM_RX | CAN_TB_u4CFCC_CFPLS_64 | CAN_TB_u4CFCC_CFTXIE_DIS | CAN_TB_u4CFCC_CFRXIE_DIS | CAN_TB_u4CFCC_CFE_USE   )
#define CAN_TB_u4CFCC_NOUSE                 ( CAN_TB_u4CFCC_CFDC_0           | CAN_TB_u4CFCC_CFIM_CFIGCV  | CAN_TB_u4CFCC_CFM_RX | CAN_TB_u4CFCC_CFPLS_8  | CAN_TB_u4CFCC_CFTXIE_DIS | CAN_TB_u4CFCC_CFRXIE_DIS | CAN_TB_u4CFCC_CFE_NOUSE )

#define CAN_TB_u4CFCC0_CONF( ch )           ( (CAN_CFG_RX_PROCESSING_##ch == CAN_INTERRUPT) ? CAN_TB_u4CFCC_RXINT( ch ) : CAN_TB_u4CFCC_NOUSE )
#define CAN_TB_u4CFCC1_CONF( ch )           ( (CAN_TB_RXPOLLING( ch )     == CAN_USE      ) ? CAN_TB_u4CFCC_RXPOL( ch ) : CAN_TB_u4CFCC_NOUSE )
#define CAN_TB_u4CFCC2_CONF( ch )           ( CAN_TB_u4CFCC_NOUSE )


#define CAN_TB_u4CFSTS_CONF( ch )           ( (CAN_CFG_RX_PROCESSING_##ch == CAN_INTERRUPT) ? CAN_u4CFSTS_CFRXIF_EXC_CLR : CAN_u4CFSTS_CLEARALL )


#define CAN_TB_u4TMFDCTR_CONF( ch )         ( (CAN_CFG_ESI_##ch == CAN_USE) ? CAN_u4TMFDCTR_ESI_E_ACT : CAN_u4TMFDCTR_ESI_E_PCV )


#define CAN_TB_u4GAFLCFG0_CONF \
    ( ( (uint32)(CAN_CFG_HRHNUM_0) << 16U ) \
    + ( (uint32)(CAN_CFG_HRHNUM_1) <<  0U ) )


#define CAN_TB_u4GAFLCFG1_CONF \
    ( ( (uint32)(CAN_CFG_HRHNUM_2) << 16U ) \
    + ( (uint32)(CAN_CFG_HRHNUM_3) <<  0U ) )


#define CAN_TB_u4GAFLCFG2_CONF \
    ( ( (uint32)(CAN_CFG_HRHNUM_4) << 16U ) \
    + ( (uint32)(CAN_CFG_HRHNUM_5) <<  0U ) )


#define CAN_TB_u4GAFLCFG3_CONF \
    ( ( (uint32)(CAN_CFG_HRHNUM_6) << 16U ) \
    + ( (uint32)(CAN_CFG_HRHNUM_7) <<  0U ) )


#define CAN_TB_u4GCFG_BASE                  ( 0xFFFF0000UL )

#define CAN_TB_u4GCFG_DCS_XINCAN            ( 0x00000010UL )
#define CAN_TB_u4GCFG_DCS_CLKC              ( 0x00000000UL )
#define CAN_TB_u4GCFG_DCS_CONF \
    ( (CAN_CFG_BAUDRATE_CLK_SOURCE == CAN_CLK_XINCAN) ? CAN_TB_u4GCFG_DCS_XINCAN : CAN_TB_u4GCFG_DCS_CLKC )

#define CAN_TB_TXPRIMD                      ( CAN_CFG_TXPRIMD_0 )

#define CAN_TB_u4GCFG_TPRI_ID               ( 0x00000000UL )
#define CAN_TB_u4GCFG_TPRI_MB               ( 0x00000001UL )
#define CAN_TB_u4GCFG_TPRI_CONF \
    ( (CAN_TB_TXPRIMD == CAN_IDMODE) ? CAN_TB_u4GCFG_TPRI_ID : CAN_TB_u4GCFG_TPRI_MB )

#define CAN_TB_u4GCFG_CONF                  ( CAN_TB_u4GCFG_BASE | CAN_TB_u4GCFG_DCS_CONF | CAN_TB_u4GCFG_TPRI_CONF )


#define CAN_TB_u4GFDCFG_BASE                ( 0x00000000UL )

#define CAN_TB_PROTOCOL_EXCEPTION           ( CAN_CFG_PROTOCOL_EXCEPTION_0 )

#define CAN_TB_u4GFDCFG_RPED_ENA            ( 0x00000000UL )
#define CAN_TB_u4GFDCFG_RPED_DIS            ( 0x00000001UL )

#define CAN_TB_u4GFDCFG_RPED_CONF \
    ( (CAN_TB_PROTOCOL_EXCEPTION == CAN_USE) ? CAN_TB_u4GFDCFG_RPED_ENA : CAN_TB_u4GFDCFG_RPED_DIS )

#define CAN_TB_u4GFDCFG_CONF                ( CAN_TB_u4GFDCFG_BASE | CAN_TB_u4GFDCFG_RPED_CONF )


#define CAN_TB_DIV_ROUNDUP( dividend, divisor ) \
    ( ( ( ( dividend ) - ( ( dividend ) % ( divisor ) ) ) / ( divisor ) ) + 1U )

#define CAN_TB_ADD_MARGIN( time )           ( CAN_TB_DIV_ROUNDUP( ( ( time ) * 3U), 2U ) )

#define CAN_TB_1CANBITTIME_125              ( 8U )

#define CAN_TB_1CANBITTIME_COUNT            ( CAN_TB_ADD_MARGIN( CAN_TB_1CANBITTIME_125 * CAN_CFG_CONTROLLER_CLK ) )


#define CAN_TB_1TQTIME_COUNT                ( CAN_TB_ADD_MARGIN( CAN_CFG_CONTROLLER_CLK ) )


#define CAN_TB_1PCLKTIME_COUNT_NOMARGIN     ( 1U )

#define CAN_TB_1PCLKTIME_COUNT              ( CAN_TB_ADD_MARGIN( CAN_TB_1PCLKTIME_COUNT_NOMARGIN ) )


#define CAN_TB_1CLKCTIME_COUNT_NOMARGIN     ( CAN_TB_DIV_ROUNDUP( CAN_CFG_CONTROLLER_CLK, CAN_CFG_BAUDRATE_CLK ) )

#define CAN_TB_1CLKCTIME_COUNT              ( CAN_TB_ADD_MARGIN( CAN_TB_1CLKCTIME_COUNT_NOMARGIN ) )


#define CAN_TB_CMODE_RST2COM_BITTIME        (4U)

#define CAN_TB_CMODE_RST2COM_CYCLE          ( CAN_TB_1CANBITTIME_COUNT * CAN_TB_CMODE_RST2COM_BITTIME )


#define CAN_TB_CMODE_ANY2RST_BITTIME        (2U)

#define CAN_TB_CMODE_ANY2RST_CYCLE          ( CAN_TB_1CANBITTIME_COUNT * CAN_TB_CMODE_ANY2RST_BITTIME )


#define CAN_TB_GMODE_ANY2RST_BITTIME        (2U)

#define CAN_TB_GMODE_ANY2RST_CYCLE          ( CAN_TB_1CANBITTIME_COUNT * CAN_TB_GMODE_ANY2RST_BITTIME )


#define CAN_TB_u1BRS_INIT_CONF( ch )        ( (CAN_CFG_DBAUDRATE_SWT_##ch == CAN_USE) ? ((uint8)CAN_ST_BRS_USE) : ((uint8)CAN_ST_BRS_NOUSE) )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#if (CAN_CFG_CORE != CAN_G4MH)
#if ( (CAN_TX_TXFINISH_USE_0 == CAN_USE) || (CAN_RX_RXFINISH_USE_0 == CAN_USE) )
static uint8 Can_tb_Interrupt_0( void );
#endif /* ( (CAN_TX_TXFINISH_USE_0 == CAN_USE) || (CAN_RX_RXFINISH_USE_0 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_1 == CAN_USE) || (CAN_RX_RXFINISH_USE_1 == CAN_USE) )
static uint8 Can_tb_Interrupt_1( void );
#endif /* ( (CAN_TX_TXFINISH_USE_1 == CAN_USE) || (CAN_RX_RXFINISH_USE_1 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_2 == CAN_USE) || (CAN_RX_RXFINISH_USE_2 == CAN_USE) )
static uint8 Can_tb_Interrupt_2( void );
#endif /* ( (CAN_TX_TXFINISH_USE_2 == CAN_USE) || (CAN_RX_RXFINISH_USE_2 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_3 == CAN_USE) || (CAN_RX_RXFINISH_USE_3 == CAN_USE) )
static uint8 Can_tb_Interrupt_3( void );
#endif /* ( (CAN_TX_TXFINISH_USE_3 == CAN_USE) || (CAN_RX_RXFINISH_USE_3 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_4 == CAN_USE) || (CAN_RX_RXFINISH_USE_4 == CAN_USE) )
static uint8 Can_tb_Interrupt_4( void );
#endif /* ( (CAN_TX_TXFINISH_USE_4 == CAN_USE) || (CAN_RX_RXFINISH_USE_4 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_5 == CAN_USE) || (CAN_RX_RXFINISH_USE_5 == CAN_USE) )
static uint8 Can_tb_Interrupt_5( void );
#endif /* ( (CAN_TX_TXFINISH_USE_5 == CAN_USE) || (CAN_RX_RXFINISH_USE_5 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_6 == CAN_USE) || (CAN_RX_RXFINISH_USE_6 == CAN_USE) )
static uint8 Can_tb_Interrupt_6( void );
#endif /* ( (CAN_TX_TXFINISH_USE_6 == CAN_USE) || (CAN_RX_RXFINISH_USE_6 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_7 == CAN_USE) || (CAN_RX_RXFINISH_USE_7 == CAN_USE) )
static uint8 Can_tb_Interrupt_7( void );
#endif /* ( (CAN_TX_TXFINISH_USE_7 == CAN_USE) || (CAN_RX_RXFINISH_USE_7 == CAN_USE) ) */
#endif /* (CAN_CFG_CORE != CAN_G4MH) */


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
CanConst CanTbCtrlInfoType Can_tb_stCtrlInfo[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /* u2RxRuleOffSetId             , u1RxRuleUseNum         , u1CtrlAct                             , u1CtrlUse                      , u1CtrlOpeMode             */
     { (uint16)CAN_TB_RXRULE_OFFSET0, (uint8)CAN_CFG_HRHNUM_0, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_0, (uint8)CAN_CFG_CONTROLLER_CAN_0, (uint8)CAN_CFG_OPEMODE_0  }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET1, (uint8)CAN_CFG_HRHNUM_1, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_1, (uint8)CAN_CFG_CONTROLLER_CAN_1, (uint8)CAN_CFG_OPEMODE_1  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET2, (uint8)CAN_CFG_HRHNUM_2, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_2, (uint8)CAN_CFG_CONTROLLER_CAN_2, (uint8)CAN_CFG_OPEMODE_2  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET3, (uint8)CAN_CFG_HRHNUM_3, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_3, (uint8)CAN_CFG_CONTROLLER_CAN_3, (uint8)CAN_CFG_OPEMODE_3  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET4, (uint8)CAN_CFG_HRHNUM_4, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_4, (uint8)CAN_CFG_CONTROLLER_CAN_4, (uint8)CAN_CFG_OPEMODE_4  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET5, (uint8)CAN_CFG_HRHNUM_5, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_5, (uint8)CAN_CFG_CONTROLLER_CAN_5, (uint8)CAN_CFG_OPEMODE_5  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET6, (uint8)CAN_CFG_HRHNUM_6, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_6, (uint8)CAN_CFG_CONTROLLER_CAN_6, (uint8)CAN_CFG_OPEMODE_6  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET7, (uint8)CAN_CFG_HRHNUM_7, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_7, (uint8)CAN_CFG_CONTROLLER_CAN_7, (uint8)CAN_CFG_OPEMODE_7  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};

#if (CAN_CFG_TRANSMIT == CAN_USE)
CanConst CanTbMbNumType Can_tb_stMbNum[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /*  u1TxMbNum                  */
     { (uint8)CAN_TB_MBNUM( 0, TX ) }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,{ (uint8)CAN_TB_MBNUM( 1, TX ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,{ (uint8)CAN_TB_MBNUM( 2, TX ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,{ (uint8)CAN_TB_MBNUM( 3, TX ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,{ (uint8)CAN_TB_MBNUM( 4, TX ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,{ (uint8)CAN_TB_MBNUM( 5, TX ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,{ (uint8)CAN_TB_MBNUM( 6, TX ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,{ (uint8)CAN_TB_MBNUM( 7, TX ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */

CanConst CanTbChRegType Can_tb_stChReg[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /* CONTROLLER 0 */
     {
         CAN_TB_ptu4CH0_CmNCFG_ADDR        /* ptu4CmNCFG        */
        ,CAN_TB_ptu4CH0_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH0_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH0_CmERFL_ADDR        /* ptu4CmERFL        */
        ,CAN_TB_ptu4CH0_CFCC_ADDR          /* ptu4CFCC          */
        ,CAN_TB_ptu4CH0_CFCCE_ADDR         /* ptu4CFCCE         */
        ,CAN_TB_ptu4CH0_CFSTS_ADDR         /* ptu4CFSTS         */
        ,CAN_TB_ptu4CH0_CFPCTR_ADDR        /* ptu4CFPCTR        */
        ,CAN_TB_ptu1CH0_TMC_ADDR           /* ptu1TMC           */
        ,CAN_TB_ptu1CH0_TMSTS_ADDR         /* ptu1TMSTS         */
        ,CAN_TB_ptu4CH0_TMTRSTS_ADDR       /* ptu4TMTRSTS       */
        ,CAN_TB_ptu4CH0_TMTARSTS_ADDR      /* ptu4TMTARSTS      */
        ,CAN_TB_ptu4CH0_TMTCSTS_ADDR       /* ptu4TMTCSTS       */
        ,CAN_TB_ptu4CH0_TMTASTS_ADDR       /* ptu4TMTASTS       */
        ,CAN_TB_ptu4CH0_TMIEC_ADDR         /* ptu4TMIEC         */
        ,CAN_TB_ptu4CH0_TXQCC0_ADDR        /* ptu4TXQCC0        */
        ,CAN_TB_ptu4CH0_TXQSTS0_ADDR       /* ptu4TXQSTS0       */
        ,CAN_TB_ptu4CH0_TXQPCTR0_ADDR      /* ptu4TXQPCTR0      */
        ,CAN_TB_ptu4CH0_TXQCC1_ADDR        /* ptu4TXQCC1        */
        ,CAN_TB_ptu4CH0_TXQSTS1_ADDR       /* ptu4TXQSTS1       */
        ,CAN_TB_ptu4CH0_TXQPCTR1_ADDR      /* ptu4TXQPCTR1      */
        ,CAN_TB_ptu4CH0_TXQCC2_ADDR        /* ptu4TXQCC2        */
        ,CAN_TB_ptu4CH0_TXQSTS2_ADDR       /* ptu4TXQSTS2       */
        ,CAN_TB_ptu4CH0_TXQPCTR2_ADDR      /* ptu4TXQPCTR2      */
        ,CAN_TB_ptu4CH0_TXQCC3_ADDR        /* ptu4TXQCC3        */
        ,CAN_TB_ptu4CH0_TXQSTS3_ADDR       /* ptu4TXQSTS3       */
        ,CAN_TB_ptu4CH0_TXQPCTR3_ADDR      /* ptu4TXQPCTR3      */
        ,CAN_TB_ptu4CH0_THLCC_ADDR         /* ptu4THLCC         */
        ,CAN_TB_ptu4CH0_THLSTS_ADDR        /* ptu4THLSTS        */
        ,CAN_TB_ptu4CH0_THLPCTR_ADDR       /* ptu4THLPCTR       */
        ,CAN_TB_ptu4CH0_GRINTSTS_ADDR      /* ptu4GRINTSTS      */
        ,CAN_TB_ptu4CH0_VMCFG_ADDR         /* ptu4VMCFG         */
        ,CAN_TB_ptu4CH0_VMISTS_ADDR        /* ptu4VMISTS        */
        ,CAN_TB_ptu4CH0_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH0_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH0_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH0_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH0_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
        ,CAN_TB_ptu4CH0_CmBLCT_ADDR        /* ptu4CmBLCT        */
        ,CAN_TB_ptu4CH0_CmBLSTS_ADDR       /* ptu4CmBLSTS       */
        ,CAN_TB_ptu4CH0_THLACC0_ADDR       /* ptu4THLACC0       */
        ,CAN_TB_ptu4CH0_THLACC1_ADDR       /* ptu4THLACC1       */
        ,CAN_TB_ptstCH0_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH0_TM_ADDR            /* ptstTM            */
    }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    /* CONTROLLER 1 */
    ,{
         CAN_TB_ptu4CH1_CmNCFG_ADDR        /* ptu4CmNCFG        */
        ,CAN_TB_ptu4CH1_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH1_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH1_CmERFL_ADDR        /* ptu4CmERFL        */
        ,CAN_TB_ptu4CH1_CFCC_ADDR          /* ptu4CFCC          */
        ,CAN_TB_ptu4CH1_CFCCE_ADDR         /* ptu4CFCCE         */
        ,CAN_TB_ptu4CH1_CFSTS_ADDR         /* ptu4CFSTS         */
        ,CAN_TB_ptu4CH1_CFPCTR_ADDR        /* ptu4CFPCTR        */
        ,CAN_TB_ptu1CH1_TMC_ADDR           /* ptu1TMC           */
        ,CAN_TB_ptu1CH1_TMSTS_ADDR         /* ptu1TMSTS         */
        ,CAN_TB_ptu4CH1_TMTRSTS_ADDR       /* ptu4TMTRSTS       */
        ,CAN_TB_ptu4CH1_TMTARSTS_ADDR      /* ptu4TMTARSTS      */
        ,CAN_TB_ptu4CH1_TMTCSTS_ADDR       /* ptu4TMTCSTS       */
        ,CAN_TB_ptu4CH1_TMTASTS_ADDR       /* ptu4TMTASTS       */
        ,CAN_TB_ptu4CH1_TMIEC_ADDR         /* ptu4TMIEC         */
        ,CAN_TB_ptu4CH1_TXQCC0_ADDR        /* ptu4TXQCC0        */
        ,CAN_TB_ptu4CH1_TXQSTS0_ADDR       /* ptu4TXQSTS0       */
        ,CAN_TB_ptu4CH1_TXQPCTR0_ADDR      /* ptu4TXQPCTR0      */
        ,CAN_TB_ptu4CH1_TXQCC1_ADDR        /* ptu4TXQCC1        */
        ,CAN_TB_ptu4CH1_TXQSTS1_ADDR       /* ptu4TXQSTS1       */
        ,CAN_TB_ptu4CH1_TXQPCTR1_ADDR      /* ptu4TXQPCTR1      */
        ,CAN_TB_ptu4CH1_TXQCC2_ADDR        /* ptu4TXQCC2        */
        ,CAN_TB_ptu4CH1_TXQSTS2_ADDR       /* ptu4TXQSTS2       */
        ,CAN_TB_ptu4CH1_TXQPCTR2_ADDR      /* ptu4TXQPCTR2      */
        ,CAN_TB_ptu4CH1_TXQCC3_ADDR        /* ptu4TXQCC3        */
        ,CAN_TB_ptu4CH1_TXQSTS3_ADDR       /* ptu4TXQSTS3       */
        ,CAN_TB_ptu4CH1_TXQPCTR3_ADDR      /* ptu4TXQPCTR3      */
        ,CAN_TB_ptu4CH1_THLCC_ADDR         /* ptu4THLCC         */
        ,CAN_TB_ptu4CH1_THLSTS_ADDR        /* ptu4THLSTS        */
        ,CAN_TB_ptu4CH1_THLPCTR_ADDR       /* ptu4THLPCTR       */
        ,CAN_TB_ptu4CH1_GRINTSTS_ADDR      /* ptu4GRINTSTS      */
        ,CAN_TB_ptu4CH1_VMCFG_ADDR         /* ptu4VMCFG         */
        ,CAN_TB_ptu4CH1_VMISTS_ADDR        /* ptu4VMISTS        */
        ,CAN_TB_ptu4CH1_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH1_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH1_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH1_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH1_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
        ,CAN_TB_ptu4CH1_CmBLCT_ADDR        /* ptu4CmBLCT        */
        ,CAN_TB_ptu4CH1_CmBLSTS_ADDR       /* ptu4CmBLSTS       */
        ,CAN_TB_ptu4CH1_THLACC0_ADDR       /* ptu4THLACC0       */
        ,CAN_TB_ptu4CH1_THLACC1_ADDR       /* ptu4THLACC1       */
        ,CAN_TB_ptstCH1_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH1_TM_ADDR            /* ptstTM            */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    /* CONTROLLER 2 */
    ,{
         CAN_TB_ptu4CH2_CmNCFG_ADDR        /* ptu4CmNCFG        */
        ,CAN_TB_ptu4CH2_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH2_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH2_CmERFL_ADDR        /* ptu4CmERFL        */
        ,CAN_TB_ptu4CH2_CFCC_ADDR          /* ptu4CFCC          */
        ,CAN_TB_ptu4CH2_CFCCE_ADDR         /* ptu4CFCCE         */
        ,CAN_TB_ptu4CH2_CFSTS_ADDR         /* ptu4CFSTS         */
        ,CAN_TB_ptu4CH2_CFPCTR_ADDR        /* ptu4CFPCTR        */
        ,CAN_TB_ptu1CH2_TMC_ADDR           /* ptu1TMC           */
        ,CAN_TB_ptu1CH2_TMSTS_ADDR         /* ptu1TMSTS         */
        ,CAN_TB_ptu4CH2_TMTRSTS_ADDR       /* ptu4TMTRSTS       */
        ,CAN_TB_ptu4CH2_TMTARSTS_ADDR      /* ptu4TMTARSTS      */
        ,CAN_TB_ptu4CH2_TMTCSTS_ADDR       /* ptu4TMTCSTS       */
        ,CAN_TB_ptu4CH2_TMTASTS_ADDR       /* ptu4TMTASTS       */
        ,CAN_TB_ptu4CH2_TMIEC_ADDR         /* ptu4TMIEC         */
        ,CAN_TB_ptu4CH2_TXQCC0_ADDR        /* ptu4TXQCC0        */
        ,CAN_TB_ptu4CH2_TXQSTS0_ADDR       /* ptu4TXQSTS0       */
        ,CAN_TB_ptu4CH2_TXQPCTR0_ADDR      /* ptu4TXQPCTR0      */
        ,CAN_TB_ptu4CH2_TXQCC1_ADDR        /* ptu4TXQCC1        */
        ,CAN_TB_ptu4CH2_TXQSTS1_ADDR       /* ptu4TXQSTS1       */
        ,CAN_TB_ptu4CH2_TXQPCTR1_ADDR      /* ptu4TXQPCTR1      */
        ,CAN_TB_ptu4CH2_TXQCC2_ADDR        /* ptu4TXQCC2        */
        ,CAN_TB_ptu4CH2_TXQSTS2_ADDR       /* ptu4TXQSTS2       */
        ,CAN_TB_ptu4CH2_TXQPCTR2_ADDR      /* ptu4TXQPCTR2      */
        ,CAN_TB_ptu4CH2_TXQCC3_ADDR        /* ptu4TXQCC3        */
        ,CAN_TB_ptu4CH2_TXQSTS3_ADDR       /* ptu4TXQSTS3       */
        ,CAN_TB_ptu4CH2_TXQPCTR3_ADDR      /* ptu4TXQPCTR3      */
        ,CAN_TB_ptu4CH2_THLCC_ADDR         /* ptu4THLCC         */
        ,CAN_TB_ptu4CH2_THLSTS_ADDR        /* ptu4THLSTS        */
        ,CAN_TB_ptu4CH2_THLPCTR_ADDR       /* ptu4THLPCTR       */
        ,CAN_TB_ptu4CH2_GRINTSTS_ADDR      /* ptu4GRINTSTS      */
        ,CAN_TB_ptu4CH2_VMCFG_ADDR         /* ptu4VMCFG         */
        ,CAN_TB_ptu4CH2_VMISTS_ADDR        /* ptu4VMISTS        */
        ,CAN_TB_ptu4CH2_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH2_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH2_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH2_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH2_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
        ,CAN_TB_ptu4CH2_CmBLCT_ADDR        /* ptu4CmBLCT        */
        ,CAN_TB_ptu4CH2_CmBLSTS_ADDR       /* ptu4CmBLSTS       */
        ,CAN_TB_ptu4CH2_THLACC0_ADDR       /* ptu4THLACC0       */
        ,CAN_TB_ptu4CH2_THLACC1_ADDR       /* ptu4THLACC1       */
        ,CAN_TB_ptstCH2_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH2_TM_ADDR            /* ptstTM            */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    /* CONTROLLER 3 */
    ,{
         CAN_TB_ptu4CH3_CmNCFG_ADDR        /* ptu4CmNCFG        */
        ,CAN_TB_ptu4CH3_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH3_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH3_CmERFL_ADDR        /* ptu4CmERFL        */
        ,CAN_TB_ptu4CH3_CFCC_ADDR          /* ptu4CFCC          */
        ,CAN_TB_ptu4CH3_CFCCE_ADDR         /* ptu4CFCCE         */
        ,CAN_TB_ptu4CH3_CFSTS_ADDR         /* ptu4CFSTS         */
        ,CAN_TB_ptu4CH3_CFPCTR_ADDR        /* ptu4CFPCTR        */
        ,CAN_TB_ptu1CH3_TMC_ADDR           /* ptu1TMC           */
        ,CAN_TB_ptu1CH3_TMSTS_ADDR         /* ptu1TMSTS         */
        ,CAN_TB_ptu4CH3_TMTRSTS_ADDR       /* ptu4TMTRSTS       */
        ,CAN_TB_ptu4CH3_TMTARSTS_ADDR      /* ptu4TMTARSTS      */
        ,CAN_TB_ptu4CH3_TMTCSTS_ADDR       /* ptu4TMTCSTS       */
        ,CAN_TB_ptu4CH3_TMTASTS_ADDR       /* ptu4TMTASTS       */
        ,CAN_TB_ptu4CH3_TMIEC_ADDR         /* ptu4TMIEC         */
        ,CAN_TB_ptu4CH3_TXQCC0_ADDR        /* ptu4TXQCC0        */
        ,CAN_TB_ptu4CH3_TXQSTS0_ADDR       /* ptu4TXQSTS0       */
        ,CAN_TB_ptu4CH3_TXQPCTR0_ADDR      /* ptu4TXQPCTR0      */
        ,CAN_TB_ptu4CH3_TXQCC1_ADDR        /* ptu4TXQCC1        */
        ,CAN_TB_ptu4CH3_TXQSTS1_ADDR       /* ptu4TXQSTS1       */
        ,CAN_TB_ptu4CH3_TXQPCTR1_ADDR      /* ptu4TXQPCTR1      */
        ,CAN_TB_ptu4CH3_TXQCC2_ADDR        /* ptu4TXQCC2        */
        ,CAN_TB_ptu4CH3_TXQSTS2_ADDR       /* ptu4TXQSTS2       */
        ,CAN_TB_ptu4CH3_TXQPCTR2_ADDR      /* ptu4TXQPCTR2      */
        ,CAN_TB_ptu4CH3_TXQCC3_ADDR        /* ptu4TXQCC3        */
        ,CAN_TB_ptu4CH3_TXQSTS3_ADDR       /* ptu4TXQSTS3       */
        ,CAN_TB_ptu4CH3_TXQPCTR3_ADDR      /* ptu4TXQPCTR3      */
        ,CAN_TB_ptu4CH3_THLCC_ADDR         /* ptu4THLCC         */
        ,CAN_TB_ptu4CH3_THLSTS_ADDR        /* ptu4THLSTS        */
        ,CAN_TB_ptu4CH3_THLPCTR_ADDR       /* ptu4THLPCTR       */
        ,CAN_TB_ptu4CH3_GRINTSTS_ADDR      /* ptu4GRINTSTS      */
        ,CAN_TB_ptu4CH3_VMCFG_ADDR         /* ptu4VMCFG         */
        ,CAN_TB_ptu4CH3_VMISTS_ADDR        /* ptu4VMISTS        */
        ,CAN_TB_ptu4CH3_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH3_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH3_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH3_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH3_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
        ,CAN_TB_ptu4CH3_CmBLCT_ADDR        /* ptu4CmBLCT        */
        ,CAN_TB_ptu4CH3_CmBLSTS_ADDR       /* ptu4CmBLSTS       */
        ,CAN_TB_ptu4CH3_THLACC0_ADDR       /* ptu4THLACC0       */
        ,CAN_TB_ptu4CH3_THLACC1_ADDR       /* ptu4THLACC1       */
        ,CAN_TB_ptstCH3_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH3_TM_ADDR            /* ptstTM            */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    /* CONTROLLER 4 */
    ,{
         CAN_TB_ptu4CH4_CmNCFG_ADDR        /* ptu4CmNCFG        */
        ,CAN_TB_ptu4CH4_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH4_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH4_CmERFL_ADDR        /* ptu4CmERFL        */
        ,CAN_TB_ptu4CH4_CFCC_ADDR          /* ptu4CFCC          */
        ,CAN_TB_ptu4CH4_CFCCE_ADDR         /* ptu4CFCCE         */
        ,CAN_TB_ptu4CH4_CFSTS_ADDR         /* ptu4CFSTS         */
        ,CAN_TB_ptu4CH4_CFPCTR_ADDR        /* ptu4CFPCTR        */
        ,CAN_TB_ptu1CH4_TMC_ADDR           /* ptu1TMC           */
        ,CAN_TB_ptu1CH4_TMSTS_ADDR         /* ptu1TMSTS         */
        ,CAN_TB_ptu4CH4_TMTRSTS_ADDR       /* ptu4TMTRSTS       */
        ,CAN_TB_ptu4CH4_TMTARSTS_ADDR      /* ptu4TMTARSTS      */
        ,CAN_TB_ptu4CH4_TMTCSTS_ADDR       /* ptu4TMTCSTS       */
        ,CAN_TB_ptu4CH4_TMTASTS_ADDR       /* ptu4TMTASTS       */
        ,CAN_TB_ptu4CH4_TMIEC_ADDR         /* ptu4TMIEC         */
        ,CAN_TB_ptu4CH4_TXQCC0_ADDR        /* ptu4TXQCC0        */
        ,CAN_TB_ptu4CH4_TXQSTS0_ADDR       /* ptu4TXQSTS0       */
        ,CAN_TB_ptu4CH4_TXQPCTR0_ADDR      /* ptu4TXQPCTR0      */
        ,CAN_TB_ptu4CH4_TXQCC1_ADDR        /* ptu4TXQCC1        */
        ,CAN_TB_ptu4CH4_TXQSTS1_ADDR       /* ptu4TXQSTS1       */
        ,CAN_TB_ptu4CH4_TXQPCTR1_ADDR      /* ptu4TXQPCTR1      */
        ,CAN_TB_ptu4CH4_TXQCC2_ADDR        /* ptu4TXQCC2        */
        ,CAN_TB_ptu4CH4_TXQSTS2_ADDR       /* ptu4TXQSTS2       */
        ,CAN_TB_ptu4CH4_TXQPCTR2_ADDR      /* ptu4TXQPCTR2      */
        ,CAN_TB_ptu4CH4_TXQCC3_ADDR        /* ptu4TXQCC3        */
        ,CAN_TB_ptu4CH4_TXQSTS3_ADDR       /* ptu4TXQSTS3       */
        ,CAN_TB_ptu4CH4_TXQPCTR3_ADDR      /* ptu4TXQPCTR3      */
        ,CAN_TB_ptu4CH4_THLCC_ADDR         /* ptu4THLCC         */
        ,CAN_TB_ptu4CH4_THLSTS_ADDR        /* ptu4THLSTS        */
        ,CAN_TB_ptu4CH4_THLPCTR_ADDR       /* ptu4THLPCTR       */
        ,CAN_TB_ptu4CH4_GRINTSTS_ADDR      /* ptu4GRINTSTS      */
        ,CAN_TB_ptu4CH4_VMCFG_ADDR         /* ptu4VMCFG         */
        ,CAN_TB_ptu4CH4_VMISTS_ADDR        /* ptu4VMISTS        */
        ,CAN_TB_ptu4CH4_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH4_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH4_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH4_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH4_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
        ,CAN_TB_ptu4CH4_CmBLCT_ADDR        /* ptu4CmBLCT        */
        ,CAN_TB_ptu4CH4_CmBLSTS_ADDR       /* ptu4CmBLSTS       */
        ,CAN_TB_ptu4CH4_THLACC0_ADDR       /* ptu4THLACC0       */
        ,CAN_TB_ptu4CH4_THLACC1_ADDR       /* ptu4THLACC1       */
        ,CAN_TB_ptstCH4_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH4_TM_ADDR            /* ptstTM            */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    /* CONTROLLER 5 */
    ,{
         CAN_TB_ptu4CH5_CmNCFG_ADDR        /* ptu4CmNCFG        */
        ,CAN_TB_ptu4CH5_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH5_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH5_CmERFL_ADDR        /* ptu4CmERFL        */
        ,CAN_TB_ptu4CH5_CFCC_ADDR          /* ptu4CFCC          */
        ,CAN_TB_ptu4CH5_CFCCE_ADDR         /* ptu4CFCCE         */
        ,CAN_TB_ptu4CH5_CFSTS_ADDR         /* ptu4CFSTS         */
        ,CAN_TB_ptu4CH5_CFPCTR_ADDR        /* ptu4CFPCTR        */
        ,CAN_TB_ptu1CH5_TMC_ADDR           /* ptu1TMC           */
        ,CAN_TB_ptu1CH5_TMSTS_ADDR         /* ptu1TMSTS         */
        ,CAN_TB_ptu4CH5_TMTRSTS_ADDR       /* ptu4TMTRSTS       */
        ,CAN_TB_ptu4CH5_TMTARSTS_ADDR      /* ptu4TMTARSTS      */
        ,CAN_TB_ptu4CH5_TMTCSTS_ADDR       /* ptu4TMTCSTS       */
        ,CAN_TB_ptu4CH5_TMTASTS_ADDR       /* ptu4TMTASTS       */
        ,CAN_TB_ptu4CH5_TMIEC_ADDR         /* ptu4TMIEC         */
        ,CAN_TB_ptu4CH5_TXQCC0_ADDR        /* ptu4TXQCC0        */
        ,CAN_TB_ptu4CH5_TXQSTS0_ADDR       /* ptu4TXQSTS0       */
        ,CAN_TB_ptu4CH5_TXQPCTR0_ADDR      /* ptu4TXQPCTR0      */
        ,CAN_TB_ptu4CH5_TXQCC1_ADDR        /* ptu4TXQCC1        */
        ,CAN_TB_ptu4CH5_TXQSTS1_ADDR       /* ptu4TXQSTS1       */
        ,CAN_TB_ptu4CH5_TXQPCTR1_ADDR      /* ptu4TXQPCTR1      */
        ,CAN_TB_ptu4CH5_TXQCC2_ADDR        /* ptu4TXQCC2        */
        ,CAN_TB_ptu4CH5_TXQSTS2_ADDR       /* ptu4TXQSTS2       */
        ,CAN_TB_ptu4CH5_TXQPCTR2_ADDR      /* ptu4TXQPCTR2      */
        ,CAN_TB_ptu4CH5_TXQCC3_ADDR        /* ptu4TXQCC3        */
        ,CAN_TB_ptu4CH5_TXQSTS3_ADDR       /* ptu4TXQSTS3       */
        ,CAN_TB_ptu4CH5_TXQPCTR3_ADDR      /* ptu4TXQPCTR3      */
        ,CAN_TB_ptu4CH5_THLCC_ADDR         /* ptu4THLCC         */
        ,CAN_TB_ptu4CH5_THLSTS_ADDR        /* ptu4THLSTS        */
        ,CAN_TB_ptu4CH5_THLPCTR_ADDR       /* ptu4THLPCTR       */
        ,CAN_TB_ptu4CH5_GRINTSTS_ADDR      /* ptu4GRINTSTS      */
        ,CAN_TB_ptu4CH5_VMCFG_ADDR         /* ptu4VMCFG         */
        ,CAN_TB_ptu4CH5_VMISTS_ADDR        /* ptu4VMISTS        */
        ,CAN_TB_ptu4CH5_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH5_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH5_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH5_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH5_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
        ,CAN_TB_ptu4CH5_CmBLCT_ADDR        /* ptu4CmBLCT        */
        ,CAN_TB_ptu4CH5_CmBLSTS_ADDR       /* ptu4CmBLSTS       */
        ,CAN_TB_ptu4CH5_THLACC0_ADDR       /* ptu4THLACC0       */
        ,CAN_TB_ptu4CH5_THLACC1_ADDR       /* ptu4THLACC1       */
        ,CAN_TB_ptstCH5_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH5_TM_ADDR            /* ptstTM            */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    /* CONTROLLER 6 */
    ,{
         CAN_TB_ptu4CH6_CmNCFG_ADDR        /* ptu4CmNCFG        */
        ,CAN_TB_ptu4CH6_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH6_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH6_CmERFL_ADDR        /* ptu4CmERFL        */
        ,CAN_TB_ptu4CH6_CFCC_ADDR          /* ptu4CFCC          */
        ,CAN_TB_ptu4CH6_CFCCE_ADDR         /* ptu4CFCCE         */
        ,CAN_TB_ptu4CH6_CFSTS_ADDR         /* ptu4CFSTS         */
        ,CAN_TB_ptu4CH6_CFPCTR_ADDR        /* ptu4CFPCTR        */
        ,CAN_TB_ptu1CH6_TMC_ADDR           /* ptu1TMC           */
        ,CAN_TB_ptu1CH6_TMSTS_ADDR         /* ptu1TMSTS         */
        ,CAN_TB_ptu4CH6_TMTRSTS_ADDR       /* ptu4TMTRSTS       */
        ,CAN_TB_ptu4CH6_TMTARSTS_ADDR      /* ptu4TMTARSTS      */
        ,CAN_TB_ptu4CH6_TMTCSTS_ADDR       /* ptu4TMTCSTS       */
        ,CAN_TB_ptu4CH6_TMTASTS_ADDR       /* ptu4TMTASTS       */
        ,CAN_TB_ptu4CH6_TMIEC_ADDR         /* ptu4TMIEC         */
        ,CAN_TB_ptu4CH6_TXQCC0_ADDR        /* ptu4TXQCC0        */
        ,CAN_TB_ptu4CH6_TXQSTS0_ADDR       /* ptu4TXQSTS0       */
        ,CAN_TB_ptu4CH6_TXQPCTR0_ADDR      /* ptu4TXQPCTR0      */
        ,CAN_TB_ptu4CH6_TXQCC1_ADDR        /* ptu4TXQCC1        */
        ,CAN_TB_ptu4CH6_TXQSTS1_ADDR       /* ptu4TXQSTS1       */
        ,CAN_TB_ptu4CH6_TXQPCTR1_ADDR      /* ptu4TXQPCTR1      */
        ,CAN_TB_ptu4CH6_TXQCC2_ADDR        /* ptu4TXQCC2        */
        ,CAN_TB_ptu4CH6_TXQSTS2_ADDR       /* ptu4TXQSTS2       */
        ,CAN_TB_ptu4CH6_TXQPCTR2_ADDR      /* ptu4TXQPCTR2      */
        ,CAN_TB_ptu4CH6_TXQCC3_ADDR        /* ptu4TXQCC3        */
        ,CAN_TB_ptu4CH6_TXQSTS3_ADDR       /* ptu4TXQSTS3       */
        ,CAN_TB_ptu4CH6_TXQPCTR3_ADDR      /* ptu4TXQPCTR3      */
        ,CAN_TB_ptu4CH6_THLCC_ADDR         /* ptu4THLCC         */
        ,CAN_TB_ptu4CH6_THLSTS_ADDR        /* ptu4THLSTS        */
        ,CAN_TB_ptu4CH6_THLPCTR_ADDR       /* ptu4THLPCTR       */
        ,CAN_TB_ptu4CH6_GRINTSTS_ADDR      /* ptu4GRINTSTS      */
        ,CAN_TB_ptu4CH6_VMCFG_ADDR         /* ptu4VMCFG         */
        ,CAN_TB_ptu4CH6_VMISTS_ADDR        /* ptu4VMISTS        */
        ,CAN_TB_ptu4CH6_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH6_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH6_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH6_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH6_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
        ,CAN_TB_ptu4CH6_CmBLCT_ADDR        /* ptu4CmBLCT        */
        ,CAN_TB_ptu4CH6_CmBLSTS_ADDR       /* ptu4CmBLSTS       */
        ,CAN_TB_ptu4CH6_THLACC0_ADDR       /* ptu4THLACC0       */
        ,CAN_TB_ptu4CH6_THLACC1_ADDR       /* ptu4THLACC1       */
        ,CAN_TB_ptstCH6_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH6_TM_ADDR            /* ptstTM            */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    /* CONTROLLER 7 */
    ,{
         CAN_TB_ptu4CH7_CmNCFG_ADDR        /* ptu4CmNCFG        */
        ,CAN_TB_ptu4CH7_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH7_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH7_CmERFL_ADDR        /* ptu4CmERFL        */
        ,CAN_TB_ptu4CH7_CFCC_ADDR          /* ptu4CFCC          */
        ,CAN_TB_ptu4CH7_CFCCE_ADDR         /* ptu4CFCCE         */
        ,CAN_TB_ptu4CH7_CFSTS_ADDR         /* ptu4CFSTS         */
        ,CAN_TB_ptu4CH7_CFPCTR_ADDR        /* ptu4CFPCTR        */
        ,CAN_TB_ptu1CH7_TMC_ADDR           /* ptu1TMC           */
        ,CAN_TB_ptu1CH7_TMSTS_ADDR         /* ptu1TMSTS         */
        ,CAN_TB_ptu4CH7_TMTRSTS_ADDR       /* ptu4TMTRSTS       */
        ,CAN_TB_ptu4CH7_TMTARSTS_ADDR      /* ptu4TMTARSTS      */
        ,CAN_TB_ptu4CH7_TMTCSTS_ADDR       /* ptu4TMTCSTS       */
        ,CAN_TB_ptu4CH7_TMTASTS_ADDR       /* ptu4TMTASTS       */
        ,CAN_TB_ptu4CH7_TMIEC_ADDR         /* ptu4TMIEC         */
        ,CAN_TB_ptu4CH7_TXQCC0_ADDR        /* ptu4TXQCC0        */
        ,CAN_TB_ptu4CH7_TXQSTS0_ADDR       /* ptu4TXQSTS0       */
        ,CAN_TB_ptu4CH7_TXQPCTR0_ADDR      /* ptu4TXQPCTR0      */
        ,CAN_TB_ptu4CH7_TXQCC1_ADDR        /* ptu4TXQCC1        */
        ,CAN_TB_ptu4CH7_TXQSTS1_ADDR       /* ptu4TXQSTS1       */
        ,CAN_TB_ptu4CH7_TXQPCTR1_ADDR      /* ptu4TXQPCTR1      */
        ,CAN_TB_ptu4CH7_TXQCC2_ADDR        /* ptu4TXQCC2        */
        ,CAN_TB_ptu4CH7_TXQSTS2_ADDR       /* ptu4TXQSTS2       */
        ,CAN_TB_ptu4CH7_TXQPCTR2_ADDR      /* ptu4TXQPCTR2      */
        ,CAN_TB_ptu4CH7_TXQCC3_ADDR        /* ptu4TXQCC3        */
        ,CAN_TB_ptu4CH7_TXQSTS3_ADDR       /* ptu4TXQSTS3       */
        ,CAN_TB_ptu4CH7_TXQPCTR3_ADDR      /* ptu4TXQPCTR3      */
        ,CAN_TB_ptu4CH7_THLCC_ADDR         /* ptu4THLCC         */
        ,CAN_TB_ptu4CH7_THLSTS_ADDR        /* ptu4THLSTS        */
        ,CAN_TB_ptu4CH7_THLPCTR_ADDR       /* ptu4THLPCTR       */
        ,CAN_TB_ptu4CH7_GRINTSTS_ADDR      /* ptu4GRINTSTS      */
        ,CAN_TB_ptu4CH7_VMCFG_ADDR         /* ptu4VMCFG         */
        ,CAN_TB_ptu4CH7_VMISTS_ADDR        /* ptu4VMISTS        */
        ,CAN_TB_ptu4CH7_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH7_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH7_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH7_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH7_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
        ,CAN_TB_ptu4CH7_CmBLCT_ADDR        /* ptu4CmBLCT        */
        ,CAN_TB_ptu4CH7_CmBLSTS_ADDR       /* ptu4CmBLSTS       */
        ,CAN_TB_ptu4CH7_THLACC0_ADDR       /* ptu4THLACC0       */
        ,CAN_TB_ptu4CH7_THLACC1_ADDR       /* ptu4THLACC1       */
        ,CAN_TB_ptstCH7_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH7_TM_ADDR            /* ptstTM            */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};

CanConst CanTbGlobalRegType Can_tb_stGlobalReg =
{
     CAN_TB_ptu4GIPV_ADDR                  /* ptu4GIPV          */
    ,CAN_TB_ptu4GCFG_ADDR                  /* ptu4GCFG          */
    ,CAN_TB_ptu4GCTR_ADDR                  /* ptu4GCTR          */
    ,CAN_TB_ptu4GSTS_ADDR                  /* ptu4GSTS          */
    ,CAN_TB_ptu4GERFL_ADDR                 /* ptu4GERFL         */
    ,CAN_TB_ptu4GTSC_ADDR                  /* ptu4GTSC          */
    ,CAN_TB_ptu4GAFLECTR_ADDR              /* ptu4GAFLECTR      */
    ,CAN_TB_ptu4GAFLCFG_ADDR               /* ptu4GAFLCFG       */
    ,CAN_TB_ptu4RMNB_ADDR                  /* ptu4RMNB          */
    ,CAN_TB_ptu4RMND_ADDR                  /* ptu4RMND          */
    ,CAN_TB_ptu4RFCC_ADDR                  /* ptu4RFCC          */
    ,CAN_TB_ptu4RFSTS_ADDR                 /* ptu4RFSTS         */
    ,CAN_TB_ptu4RFPCTR_ADDR                /* ptu4RFPCTR        */
    ,CAN_TB_ptu4FESTS_ADDR                 /* ptu4FESTS         */
    ,CAN_TB_ptu4FFSTS_ADDR                 /* ptu4FFSTS         */
    ,CAN_TB_ptu4FMSTS_ADDR                 /* ptu4FMSTS         */
    ,CAN_TB_ptu4RFISTS_ADDR                /* ptu4RFISTS        */
    ,CAN_TB_ptu4CFRISTS_ADDR               /* ptu4CFRISTS       */
    ,CAN_TB_ptu4CFTISTS_ADDR               /* ptu4CFTISTS       */
    ,CAN_TB_ptu4CFOFRISTS_ADDR             /* ptu4CFOFRISTS     */
    ,CAN_TB_ptu4CFOFTISTS_ADDR             /* ptu4CFOFTISTS     */
    ,CAN_TB_ptu4CFMOWSTS_ADDR              /* ptu4CFMOWSTS      */
    ,CAN_TB_ptu4FFFSTS_ADDR                /* ptu4FFFSTS        */
    ,CAN_TB_ptu4TXQESTS_ADDR               /* ptu4TXQESTS       */
    ,CAN_TB_ptu4TXQFISTS_ADDR              /* ptu4TXQFISTS      */
    ,CAN_TB_ptu4TXQMSTS_ADDR               /* ptu4TXQMSTS       */
    ,CAN_TB_ptu4TXQOWSTS_ADDR              /* ptu4TXQOWSTS      */
    ,CAN_TB_ptu4TXQISTS_ADDR               /* ptu4TXQISTS       */
    ,CAN_TB_ptu4TXQOFTISTS_ADDR            /* ptu4TXQOFTISTS    */
    ,CAN_TB_ptu4TXQOFRISTS_ADDR            /* ptu4TXQOFRISTS    */
    ,CAN_TB_ptu4TXQFSTS_ADDR               /* ptu4TXQFSTS       */
    ,CAN_TB_ptu4GTINTSTS_ADDR              /* ptu4GTINTSTS      */
    ,CAN_TB_ptu4GTSTCFG_ADDR               /* ptu4GTSTCFG       */
    ,CAN_TB_ptu4GTSTCTR_ADDR               /* ptu4GTSTCTR       */
    ,CAN_TB_ptu4GFDCFG_ADDR                /* ptu4GFDCFG        */
    ,CAN_TB_ptu4GLOCKK_ADDR                /* ptu4GLOCKK        */
    ,CAN_TB_ptu4GAFLIGNENT_ADDR            /* ptu4GAFLIGNENT    */
    ,CAN_TB_ptu4GAFLIGNCTR_ADDR            /* ptu4GAFLIGNCTR    */
    ,CAN_TB_ptu4CDTCT_ADDR                 /* ptu4CDTCT         */
    ,CAN_TB_ptu4CDTSTS_ADDR                /* ptu4CDTSTS        */
    ,CAN_TB_ptu4CDTTCT_ADDR                /* ptu4CDTTCT        */
    ,CAN_TB_ptu4CDTTSTS_ADDR               /* ptu4CDTTSTS       */
    ,CAN_TB_ptu4GPFLECTR_ADDR              /* ptu4GPFLECTR      */
    ,CAN_TB_ptu4GPFLCFG_ADDR               /* ptu4GPFLCFG       */
    ,CAN_TB_ptu4GRSTC_ADDR                 /* ptu4GRSTC         */
    ,CAN_TB_ptu4GFCMC_ADDR                 /* ptu4GFCMC         */
    ,CAN_TB_ptu4GFTBAC_ADDR                /* ptu4GFTBAC        */
    ,CAN_TB_ptu4GFFIMC_ADDR                /* ptu4GFFIMC        */
    ,CAN_TB_ptu4GVMEIS_ADDR                /* ptu4GVMEIS        */
    ,CAN_TB_ptu4VMRFCFG_ADDR               /* ptu4VMRFCFG       */
    ,CAN_TB_ptstGAFL_ADDR                  /* ptstGAFL          */
    ,CAN_TB_ptstGPFL_ADDR                  /* ptstGPFL          */
    ,CAN_TB_ptu4RPGACC_ADDR                /* ptu4RPGACC        */
    ,CAN_TB_ptstRM_ADDR                    /* ptstRM            */
    ,CAN_TB_ptstRF_ADDR                    /* ptstRF            */
};

CanConst CanTbCheckStuckParaType Can_tb_stCheckStuckPara[ CAN_CFG_CHKSTKREG_LIMIT ] =
{
    /*  u2StChkStart                     , u2StChkPage                     */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 1U)
     {  (uint16)CAN_TB_STUCK_CHK_START_0 , (uint16)CAN_TB_STUCK_CHK_PAGE_0  }
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 1U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 5U)
    ,{  (uint16)CAN_TB_STUCK_CHK_START_1 , (uint16)CAN_TB_STUCK_CHK_PAGE_1  }
    ,{  (uint16)CAN_TB_STUCK_CHK_START_2 , (uint16)CAN_TB_STUCK_CHK_PAGE_2  }
    ,{  (uint16)CAN_TB_STUCK_CHK_START_3 , (uint16)CAN_TB_STUCK_CHK_PAGE_3  }
    ,{  (uint16)CAN_TB_STUCK_CHK_START_4 , (uint16)CAN_TB_STUCK_CHK_PAGE_4  }
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 5U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 10U)
    ,{  (uint16)CAN_TB_STUCK_CHK_START_5 , (uint16)CAN_TB_STUCK_CHK_PAGE_5  }
    ,{  (uint16)CAN_TB_STUCK_CHK_START_6 , (uint16)CAN_TB_STUCK_CHK_PAGE_6  }
    ,{  (uint16)CAN_TB_STUCK_CHK_START_7 , (uint16)CAN_TB_STUCK_CHK_PAGE_7  }
    ,{  (uint16)CAN_TB_STUCK_CHK_START_8 , (uint16)CAN_TB_STUCK_CHK_PAGE_8  }
    ,{  (uint16)CAN_TB_STUCK_CHK_START_9 , (uint16)CAN_TB_STUCK_CHK_PAGE_9  }
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 10U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 12U)
    ,{  (uint16)CAN_TB_STUCK_CHK_START_10, (uint16)CAN_TB_STUCK_CHK_PAGE_10 }
    ,{  (uint16)CAN_TB_STUCK_CHK_START_11, (uint16)CAN_TB_STUCK_CHK_PAGE_11 }
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 12U) */
};

CanConst CanTbTxMbBitType Can_tb_stTxMbBit[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /*  {  u4TxIntrBit[0]              , u4TxIntrBit[1]                } */
    /* ,{  u4TxPollBit[0]              , u4TxPollBit[1]                } */
    /* Controller 0 */
     {  {  CAN_TB_u4TXMBBIT_L( 0, INT ), CAN_TB_u4TXMBBIT_H( 0, INT )  }
       ,{  CAN_TB_u4TXMBBIT_L( 0, POL ), CAN_TB_u4TXMBBIT_H( 0, POL )  }  }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    /* Controller 1 */
    ,{  {  CAN_TB_u4TXMBBIT_L( 1, INT ), CAN_TB_u4TXMBBIT_H( 1, INT )  }
       ,{  CAN_TB_u4TXMBBIT_L( 1, POL ), CAN_TB_u4TXMBBIT_H( 1, POL )  }  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    /* Controller 2 */
    ,{  {  CAN_TB_u4TXMBBIT_L( 2, INT ), CAN_TB_u4TXMBBIT_H( 2, INT )  }
       ,{  CAN_TB_u4TXMBBIT_L( 2, POL ), CAN_TB_u4TXMBBIT_H( 2, POL )  }  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    /* Controller 3 */
    ,{  {  CAN_TB_u4TXMBBIT_L( 3, INT ), CAN_TB_u4TXMBBIT_H( 3, INT )  }
       ,{  CAN_TB_u4TXMBBIT_L( 3, POL ), CAN_TB_u4TXMBBIT_H( 3, POL )  }  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    /* Controller 4 */
    ,{  {  CAN_TB_u4TXMBBIT_L( 4, INT ), CAN_TB_u4TXMBBIT_H( 4, INT )  }
       ,{  CAN_TB_u4TXMBBIT_L( 4, POL ), CAN_TB_u4TXMBBIT_H( 4, POL )  }  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    /* Controller 5 */
    ,{  {  CAN_TB_u4TXMBBIT_L( 5, INT ), CAN_TB_u4TXMBBIT_H( 5, INT )  }
       ,{  CAN_TB_u4TXMBBIT_L( 5, POL ), CAN_TB_u4TXMBBIT_H( 5, POL )  }  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    /* Controller 6 */
    ,{  {  CAN_TB_u4TXMBBIT_L( 6, INT ), CAN_TB_u4TXMBBIT_H( 6, INT )  }
       ,{  CAN_TB_u4TXMBBIT_L( 6, POL ), CAN_TB_u4TXMBBIT_H( 6, POL )  }  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    /* Controller 7 */
    ,{  {  CAN_TB_u4TXMBBIT_L( 7, INT ), CAN_TB_u4TXMBBIT_H( 7, INT )  }
       ,{  CAN_TB_u4TXMBBIT_L( 7, POL ), CAN_TB_u4TXMBBIT_H( 7, POL )  }  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};

CanConst CanTbRxRuleSettingType Can_tb_stRxRuleSetting[ CAN_TB_RXRULESETTBLSIZE ] =
{
    /* u4GAFLIDConf            , u4GAFLP0Conf                    , u4GAFLP1Conf                , u1RxMaskRef                                                                            */

    /* Controller 0 */
#if ( (CAN_CFG_MBOXSET_0_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB000, CAN_TB_u4MB_RXLABEL( CAN_MB000 ), CAN_TB_u4MB_RXKIND( 0, 000 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB000, CAN_CFG_ID_VALUE_0_MB000 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB001, CAN_TB_u4MB_RXLABEL( CAN_MB001 ), CAN_TB_u4MB_RXKIND( 0, 001 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB001, CAN_CFG_ID_VALUE_0_MB001 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB002, CAN_TB_u4MB_RXLABEL( CAN_MB002 ), CAN_TB_u4MB_RXKIND( 0, 002 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB002, CAN_CFG_ID_VALUE_0_MB002 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB003, CAN_TB_u4MB_RXLABEL( CAN_MB003 ), CAN_TB_u4MB_RXKIND( 0, 003 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB003, CAN_CFG_ID_VALUE_0_MB003 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB004, CAN_TB_u4MB_RXLABEL( CAN_MB004 ), CAN_TB_u4MB_RXKIND( 0, 004 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB004, CAN_CFG_ID_VALUE_0_MB004 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB005, CAN_TB_u4MB_RXLABEL( CAN_MB005 ), CAN_TB_u4MB_RXKIND( 0, 005 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB005, CAN_CFG_ID_VALUE_0_MB005 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB006, CAN_TB_u4MB_RXLABEL( CAN_MB006 ), CAN_TB_u4MB_RXKIND( 0, 006 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB006, CAN_CFG_ID_VALUE_0_MB006 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB007, CAN_TB_u4MB_RXLABEL( CAN_MB007 ), CAN_TB_u4MB_RXKIND( 0, 007 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB007, CAN_CFG_ID_VALUE_0_MB007 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB008, CAN_TB_u4MB_RXLABEL( CAN_MB008 ), CAN_TB_u4MB_RXKIND( 0, 008 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB008, CAN_CFG_ID_VALUE_0_MB008 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB009, CAN_TB_u4MB_RXLABEL( CAN_MB009 ), CAN_TB_u4MB_RXKIND( 0, 009 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB009, CAN_CFG_ID_VALUE_0_MB009 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB010, CAN_TB_u4MB_RXLABEL( CAN_MB010 ), CAN_TB_u4MB_RXKIND( 0, 010 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB010, CAN_CFG_ID_VALUE_0_MB010 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB011, CAN_TB_u4MB_RXLABEL( CAN_MB011 ), CAN_TB_u4MB_RXKIND( 0, 011 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB011, CAN_CFG_ID_VALUE_0_MB011 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB012, CAN_TB_u4MB_RXLABEL( CAN_MB012 ), CAN_TB_u4MB_RXKIND( 0, 012 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB012, CAN_CFG_ID_VALUE_0_MB012 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB013, CAN_TB_u4MB_RXLABEL( CAN_MB013 ), CAN_TB_u4MB_RXKIND( 0, 013 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB013, CAN_CFG_ID_VALUE_0_MB013 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB014, CAN_TB_u4MB_RXLABEL( CAN_MB014 ), CAN_TB_u4MB_RXKIND( 0, 014 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB014, CAN_CFG_ID_VALUE_0_MB014 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB015, CAN_TB_u4MB_RXLABEL( CAN_MB015 ), CAN_TB_u4MB_RXKIND( 0, 015 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB015, CAN_CFG_ID_VALUE_0_MB015 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB016, CAN_TB_u4MB_RXLABEL( CAN_MB016 ), CAN_TB_u4MB_RXKIND( 0, 016 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB016, CAN_CFG_ID_VALUE_0_MB016 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB017, CAN_TB_u4MB_RXLABEL( CAN_MB017 ), CAN_TB_u4MB_RXKIND( 0, 017 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB017, CAN_CFG_ID_VALUE_0_MB017 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB018, CAN_TB_u4MB_RXLABEL( CAN_MB018 ), CAN_TB_u4MB_RXKIND( 0, 018 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB018, CAN_CFG_ID_VALUE_0_MB018 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB019, CAN_TB_u4MB_RXLABEL( CAN_MB019 ), CAN_TB_u4MB_RXKIND( 0, 019 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB019, CAN_CFG_ID_VALUE_0_MB019 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB020, CAN_TB_u4MB_RXLABEL( CAN_MB020 ), CAN_TB_u4MB_RXKIND( 0, 020 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB020, CAN_CFG_ID_VALUE_0_MB020 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB021, CAN_TB_u4MB_RXLABEL( CAN_MB021 ), CAN_TB_u4MB_RXKIND( 0, 021 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB021, CAN_CFG_ID_VALUE_0_MB021 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB022, CAN_TB_u4MB_RXLABEL( CAN_MB022 ), CAN_TB_u4MB_RXKIND( 0, 022 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB022, CAN_CFG_ID_VALUE_0_MB022 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB023, CAN_TB_u4MB_RXLABEL( CAN_MB023 ), CAN_TB_u4MB_RXKIND( 0, 023 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB023, CAN_CFG_ID_VALUE_0_MB023 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB024, CAN_TB_u4MB_RXLABEL( CAN_MB024 ), CAN_TB_u4MB_RXKIND( 0, 024 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB024, CAN_CFG_ID_VALUE_0_MB024 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB025, CAN_TB_u4MB_RXLABEL( CAN_MB025 ), CAN_TB_u4MB_RXKIND( 0, 025 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB025, CAN_CFG_ID_VALUE_0_MB025 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB026, CAN_TB_u4MB_RXLABEL( CAN_MB026 ), CAN_TB_u4MB_RXKIND( 0, 026 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB026, CAN_CFG_ID_VALUE_0_MB026 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB027, CAN_TB_u4MB_RXLABEL( CAN_MB027 ), CAN_TB_u4MB_RXKIND( 0, 027 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB027, CAN_CFG_ID_VALUE_0_MB027 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB028, CAN_TB_u4MB_RXLABEL( CAN_MB028 ), CAN_TB_u4MB_RXKIND( 0, 028 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB028, CAN_CFG_ID_VALUE_0_MB028 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB029, CAN_TB_u4MB_RXLABEL( CAN_MB029 ), CAN_TB_u4MB_RXKIND( 0, 029 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB029, CAN_CFG_ID_VALUE_0_MB029 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB030, CAN_TB_u4MB_RXLABEL( CAN_MB030 ), CAN_TB_u4MB_RXKIND( 0, 030 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB030, CAN_CFG_ID_VALUE_0_MB030 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB031, CAN_TB_u4MB_RXLABEL( CAN_MB031 ), CAN_TB_u4MB_RXKIND( 0, 031 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB031, CAN_CFG_ID_VALUE_0_MB031 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB032, CAN_TB_u4MB_RXLABEL( CAN_MB032 ), CAN_TB_u4MB_RXKIND( 0, 032 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB032, CAN_CFG_ID_VALUE_0_MB032 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB033, CAN_TB_u4MB_RXLABEL( CAN_MB033 ), CAN_TB_u4MB_RXKIND( 0, 033 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB033, CAN_CFG_ID_VALUE_0_MB033 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB034, CAN_TB_u4MB_RXLABEL( CAN_MB034 ), CAN_TB_u4MB_RXKIND( 0, 034 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB034, CAN_CFG_ID_VALUE_0_MB034 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB035, CAN_TB_u4MB_RXLABEL( CAN_MB035 ), CAN_TB_u4MB_RXKIND( 0, 035 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB035, CAN_CFG_ID_VALUE_0_MB035 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB036, CAN_TB_u4MB_RXLABEL( CAN_MB036 ), CAN_TB_u4MB_RXKIND( 0, 036 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB036, CAN_CFG_ID_VALUE_0_MB036 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB037, CAN_TB_u4MB_RXLABEL( CAN_MB037 ), CAN_TB_u4MB_RXKIND( 0, 037 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB037, CAN_CFG_ID_VALUE_0_MB037 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB038, CAN_TB_u4MB_RXLABEL( CAN_MB038 ), CAN_TB_u4MB_RXKIND( 0, 038 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB038, CAN_CFG_ID_VALUE_0_MB038 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB039, CAN_TB_u4MB_RXLABEL( CAN_MB039 ), CAN_TB_u4MB_RXKIND( 0, 039 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB039, CAN_CFG_ID_VALUE_0_MB039 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB040, CAN_TB_u4MB_RXLABEL( CAN_MB040 ), CAN_TB_u4MB_RXKIND( 0, 040 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB040, CAN_CFG_ID_VALUE_0_MB040 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB041, CAN_TB_u4MB_RXLABEL( CAN_MB041 ), CAN_TB_u4MB_RXKIND( 0, 041 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB041, CAN_CFG_ID_VALUE_0_MB041 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB042, CAN_TB_u4MB_RXLABEL( CAN_MB042 ), CAN_TB_u4MB_RXKIND( 0, 042 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB042, CAN_CFG_ID_VALUE_0_MB042 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB043, CAN_TB_u4MB_RXLABEL( CAN_MB043 ), CAN_TB_u4MB_RXKIND( 0, 043 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB043, CAN_CFG_ID_VALUE_0_MB043 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB044, CAN_TB_u4MB_RXLABEL( CAN_MB044 ), CAN_TB_u4MB_RXKIND( 0, 044 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB044, CAN_CFG_ID_VALUE_0_MB044 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB045, CAN_TB_u4MB_RXLABEL( CAN_MB045 ), CAN_TB_u4MB_RXKIND( 0, 045 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB045, CAN_CFG_ID_VALUE_0_MB045 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB046, CAN_TB_u4MB_RXLABEL( CAN_MB046 ), CAN_TB_u4MB_RXKIND( 0, 046 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB046, CAN_CFG_ID_VALUE_0_MB046 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB047, CAN_TB_u4MB_RXLABEL( CAN_MB047 ), CAN_TB_u4MB_RXKIND( 0, 047 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB047, CAN_CFG_ID_VALUE_0_MB047 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB048, CAN_TB_u4MB_RXLABEL( CAN_MB048 ), CAN_TB_u4MB_RXKIND( 0, 048 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB048, CAN_CFG_ID_VALUE_0_MB048 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB049, CAN_TB_u4MB_RXLABEL( CAN_MB049 ), CAN_TB_u4MB_RXKIND( 0, 049 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB049, CAN_CFG_ID_VALUE_0_MB049 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB050, CAN_TB_u4MB_RXLABEL( CAN_MB050 ), CAN_TB_u4MB_RXKIND( 0, 050 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB050, CAN_CFG_ID_VALUE_0_MB050 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB051, CAN_TB_u4MB_RXLABEL( CAN_MB051 ), CAN_TB_u4MB_RXKIND( 0, 051 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB051, CAN_CFG_ID_VALUE_0_MB051 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB052, CAN_TB_u4MB_RXLABEL( CAN_MB052 ), CAN_TB_u4MB_RXKIND( 0, 052 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB052, CAN_CFG_ID_VALUE_0_MB052 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB053, CAN_TB_u4MB_RXLABEL( CAN_MB053 ), CAN_TB_u4MB_RXKIND( 0, 053 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB053, CAN_CFG_ID_VALUE_0_MB053 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB054, CAN_TB_u4MB_RXLABEL( CAN_MB054 ), CAN_TB_u4MB_RXKIND( 0, 054 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB054, CAN_CFG_ID_VALUE_0_MB054 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB055, CAN_TB_u4MB_RXLABEL( CAN_MB055 ), CAN_TB_u4MB_RXKIND( 0, 055 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB055, CAN_CFG_ID_VALUE_0_MB055 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB056, CAN_TB_u4MB_RXLABEL( CAN_MB056 ), CAN_TB_u4MB_RXKIND( 0, 056 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB056, CAN_CFG_ID_VALUE_0_MB056 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB057, CAN_TB_u4MB_RXLABEL( CAN_MB057 ), CAN_TB_u4MB_RXKIND( 0, 057 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB057, CAN_CFG_ID_VALUE_0_MB057 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB058, CAN_TB_u4MB_RXLABEL( CAN_MB058 ), CAN_TB_u4MB_RXKIND( 0, 058 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB058, CAN_CFG_ID_VALUE_0_MB058 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB059, CAN_TB_u4MB_RXLABEL( CAN_MB059 ), CAN_TB_u4MB_RXKIND( 0, 059 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB059, CAN_CFG_ID_VALUE_0_MB059 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB060, CAN_TB_u4MB_RXLABEL( CAN_MB060 ), CAN_TB_u4MB_RXKIND( 0, 060 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB060, CAN_CFG_ID_VALUE_0_MB060 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB061, CAN_TB_u4MB_RXLABEL( CAN_MB061 ), CAN_TB_u4MB_RXKIND( 0, 061 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB061, CAN_CFG_ID_VALUE_0_MB061 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB062, CAN_TB_u4MB_RXLABEL( CAN_MB062 ), CAN_TB_u4MB_RXKIND( 0, 062 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB062, CAN_CFG_ID_VALUE_0_MB062 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB063, CAN_TB_u4MB_RXLABEL( CAN_MB063 ), CAN_TB_u4MB_RXKIND( 0, 063 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB063, CAN_CFG_ID_VALUE_0_MB063 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB064, CAN_TB_u4MB_RXLABEL( CAN_MB064 ), CAN_TB_u4MB_RXKIND( 0, 064 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB064, CAN_CFG_ID_VALUE_0_MB064 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB065, CAN_TB_u4MB_RXLABEL( CAN_MB065 ), CAN_TB_u4MB_RXKIND( 0, 065 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB065, CAN_CFG_ID_VALUE_0_MB065 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB066, CAN_TB_u4MB_RXLABEL( CAN_MB066 ), CAN_TB_u4MB_RXKIND( 0, 066 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB066, CAN_CFG_ID_VALUE_0_MB066 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB067, CAN_TB_u4MB_RXLABEL( CAN_MB067 ), CAN_TB_u4MB_RXKIND( 0, 067 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB067, CAN_CFG_ID_VALUE_0_MB067 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB068, CAN_TB_u4MB_RXLABEL( CAN_MB068 ), CAN_TB_u4MB_RXKIND( 0, 068 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB068, CAN_CFG_ID_VALUE_0_MB068 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB069, CAN_TB_u4MB_RXLABEL( CAN_MB069 ), CAN_TB_u4MB_RXKIND( 0, 069 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB069, CAN_CFG_ID_VALUE_0_MB069 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB070, CAN_TB_u4MB_RXLABEL( CAN_MB070 ), CAN_TB_u4MB_RXKIND( 0, 070 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB070, CAN_CFG_ID_VALUE_0_MB070 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB071, CAN_TB_u4MB_RXLABEL( CAN_MB071 ), CAN_TB_u4MB_RXKIND( 0, 071 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB071, CAN_CFG_ID_VALUE_0_MB071 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB072, CAN_TB_u4MB_RXLABEL( CAN_MB072 ), CAN_TB_u4MB_RXKIND( 0, 072 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB072, CAN_CFG_ID_VALUE_0_MB072 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB073, CAN_TB_u4MB_RXLABEL( CAN_MB073 ), CAN_TB_u4MB_RXKIND( 0, 073 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB073, CAN_CFG_ID_VALUE_0_MB073 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB074, CAN_TB_u4MB_RXLABEL( CAN_MB074 ), CAN_TB_u4MB_RXKIND( 0, 074 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB074, CAN_CFG_ID_VALUE_0_MB074 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB075, CAN_TB_u4MB_RXLABEL( CAN_MB075 ), CAN_TB_u4MB_RXKIND( 0, 075 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB075, CAN_CFG_ID_VALUE_0_MB075 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB076, CAN_TB_u4MB_RXLABEL( CAN_MB076 ), CAN_TB_u4MB_RXKIND( 0, 076 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB076, CAN_CFG_ID_VALUE_0_MB076 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB077, CAN_TB_u4MB_RXLABEL( CAN_MB077 ), CAN_TB_u4MB_RXKIND( 0, 077 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB077, CAN_CFG_ID_VALUE_0_MB077 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB078, CAN_TB_u4MB_RXLABEL( CAN_MB078 ), CAN_TB_u4MB_RXKIND( 0, 078 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB078, CAN_CFG_ID_VALUE_0_MB078 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB079, CAN_TB_u4MB_RXLABEL( CAN_MB079 ), CAN_TB_u4MB_RXKIND( 0, 079 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB079, CAN_CFG_ID_VALUE_0_MB079 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB080, CAN_TB_u4MB_RXLABEL( CAN_MB080 ), CAN_TB_u4MB_RXKIND( 0, 080 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB080, CAN_CFG_ID_VALUE_0_MB080 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB081, CAN_TB_u4MB_RXLABEL( CAN_MB081 ), CAN_TB_u4MB_RXKIND( 0, 081 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB081, CAN_CFG_ID_VALUE_0_MB081 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB082, CAN_TB_u4MB_RXLABEL( CAN_MB082 ), CAN_TB_u4MB_RXKIND( 0, 082 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB082, CAN_CFG_ID_VALUE_0_MB082 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB083, CAN_TB_u4MB_RXLABEL( CAN_MB083 ), CAN_TB_u4MB_RXKIND( 0, 083 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB083, CAN_CFG_ID_VALUE_0_MB083 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB084, CAN_TB_u4MB_RXLABEL( CAN_MB084 ), CAN_TB_u4MB_RXKIND( 0, 084 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB084, CAN_CFG_ID_VALUE_0_MB084 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB085, CAN_TB_u4MB_RXLABEL( CAN_MB085 ), CAN_TB_u4MB_RXKIND( 0, 085 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB085, CAN_CFG_ID_VALUE_0_MB085 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB086, CAN_TB_u4MB_RXLABEL( CAN_MB086 ), CAN_TB_u4MB_RXKIND( 0, 086 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB086, CAN_CFG_ID_VALUE_0_MB086 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB087, CAN_TB_u4MB_RXLABEL( CAN_MB087 ), CAN_TB_u4MB_RXKIND( 0, 087 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB087, CAN_CFG_ID_VALUE_0_MB087 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB088, CAN_TB_u4MB_RXLABEL( CAN_MB088 ), CAN_TB_u4MB_RXKIND( 0, 088 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB088, CAN_CFG_ID_VALUE_0_MB088 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB089, CAN_TB_u4MB_RXLABEL( CAN_MB089 ), CAN_TB_u4MB_RXKIND( 0, 089 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB089, CAN_CFG_ID_VALUE_0_MB089 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB090, CAN_TB_u4MB_RXLABEL( CAN_MB090 ), CAN_TB_u4MB_RXKIND( 0, 090 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB090, CAN_CFG_ID_VALUE_0_MB090 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB091, CAN_TB_u4MB_RXLABEL( CAN_MB091 ), CAN_TB_u4MB_RXKIND( 0, 091 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB091, CAN_CFG_ID_VALUE_0_MB091 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB092, CAN_TB_u4MB_RXLABEL( CAN_MB092 ), CAN_TB_u4MB_RXKIND( 0, 092 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB092, CAN_CFG_ID_VALUE_0_MB092 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB093, CAN_TB_u4MB_RXLABEL( CAN_MB093 ), CAN_TB_u4MB_RXKIND( 0, 093 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB093, CAN_CFG_ID_VALUE_0_MB093 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB094, CAN_TB_u4MB_RXLABEL( CAN_MB094 ), CAN_TB_u4MB_RXKIND( 0, 094 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB094, CAN_CFG_ID_VALUE_0_MB094 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB095, CAN_TB_u4MB_RXLABEL( CAN_MB095 ), CAN_TB_u4MB_RXKIND( 0, 095 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB095, CAN_CFG_ID_VALUE_0_MB095 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB096, CAN_TB_u4MB_RXLABEL( CAN_MB096 ), CAN_TB_u4MB_RXKIND( 0, 096 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB096, CAN_CFG_ID_VALUE_0_MB096 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB097, CAN_TB_u4MB_RXLABEL( CAN_MB097 ), CAN_TB_u4MB_RXKIND( 0, 097 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB097, CAN_CFG_ID_VALUE_0_MB097 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB098, CAN_TB_u4MB_RXLABEL( CAN_MB098 ), CAN_TB_u4MB_RXKIND( 0, 098 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB098, CAN_CFG_ID_VALUE_0_MB098 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB099, CAN_TB_u4MB_RXLABEL( CAN_MB099 ), CAN_TB_u4MB_RXKIND( 0, 099 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB099, CAN_CFG_ID_VALUE_0_MB099 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB100, CAN_TB_u4MB_RXLABEL( CAN_MB100 ), CAN_TB_u4MB_RXKIND( 0, 100 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB100, CAN_CFG_ID_VALUE_0_MB100 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB101, CAN_TB_u4MB_RXLABEL( CAN_MB101 ), CAN_TB_u4MB_RXKIND( 0, 101 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB101, CAN_CFG_ID_VALUE_0_MB101 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB102, CAN_TB_u4MB_RXLABEL( CAN_MB102 ), CAN_TB_u4MB_RXKIND( 0, 102 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB102, CAN_CFG_ID_VALUE_0_MB102 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB103, CAN_TB_u4MB_RXLABEL( CAN_MB103 ), CAN_TB_u4MB_RXKIND( 0, 103 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB103, CAN_CFG_ID_VALUE_0_MB103 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB104, CAN_TB_u4MB_RXLABEL( CAN_MB104 ), CAN_TB_u4MB_RXKIND( 0, 104 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB104, CAN_CFG_ID_VALUE_0_MB104 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB105, CAN_TB_u4MB_RXLABEL( CAN_MB105 ), CAN_TB_u4MB_RXKIND( 0, 105 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB105, CAN_CFG_ID_VALUE_0_MB105 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB106, CAN_TB_u4MB_RXLABEL( CAN_MB106 ), CAN_TB_u4MB_RXKIND( 0, 106 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB106, CAN_CFG_ID_VALUE_0_MB106 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB107, CAN_TB_u4MB_RXLABEL( CAN_MB107 ), CAN_TB_u4MB_RXKIND( 0, 107 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB107, CAN_CFG_ID_VALUE_0_MB107 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB108, CAN_TB_u4MB_RXLABEL( CAN_MB108 ), CAN_TB_u4MB_RXKIND( 0, 108 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB108, CAN_CFG_ID_VALUE_0_MB108 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB109, CAN_TB_u4MB_RXLABEL( CAN_MB109 ), CAN_TB_u4MB_RXKIND( 0, 109 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB109, CAN_CFG_ID_VALUE_0_MB109 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB110, CAN_TB_u4MB_RXLABEL( CAN_MB110 ), CAN_TB_u4MB_RXKIND( 0, 110 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB110, CAN_CFG_ID_VALUE_0_MB110 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB111, CAN_TB_u4MB_RXLABEL( CAN_MB111 ), CAN_TB_u4MB_RXKIND( 0, 111 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB111, CAN_CFG_ID_VALUE_0_MB111 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB112, CAN_TB_u4MB_RXLABEL( CAN_MB112 ), CAN_TB_u4MB_RXKIND( 0, 112 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB112, CAN_CFG_ID_VALUE_0_MB112 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB113, CAN_TB_u4MB_RXLABEL( CAN_MB113 ), CAN_TB_u4MB_RXKIND( 0, 113 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB113, CAN_CFG_ID_VALUE_0_MB113 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB114, CAN_TB_u4MB_RXLABEL( CAN_MB114 ), CAN_TB_u4MB_RXKIND( 0, 114 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB114, CAN_CFG_ID_VALUE_0_MB114 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB115, CAN_TB_u4MB_RXLABEL( CAN_MB115 ), CAN_TB_u4MB_RXKIND( 0, 115 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB115, CAN_CFG_ID_VALUE_0_MB115 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB116, CAN_TB_u4MB_RXLABEL( CAN_MB116 ), CAN_TB_u4MB_RXKIND( 0, 116 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB116, CAN_CFG_ID_VALUE_0_MB116 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB117, CAN_TB_u4MB_RXLABEL( CAN_MB117 ), CAN_TB_u4MB_RXKIND( 0, 117 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB117, CAN_CFG_ID_VALUE_0_MB117 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB118, CAN_TB_u4MB_RXLABEL( CAN_MB118 ), CAN_TB_u4MB_RXKIND( 0, 118 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB118, CAN_CFG_ID_VALUE_0_MB118 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB119, CAN_TB_u4MB_RXLABEL( CAN_MB119 ), CAN_TB_u4MB_RXKIND( 0, 119 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB119, CAN_CFG_ID_VALUE_0_MB119 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB120, CAN_TB_u4MB_RXLABEL( CAN_MB120 ), CAN_TB_u4MB_RXKIND( 0, 120 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB120, CAN_CFG_ID_VALUE_0_MB120 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB121, CAN_TB_u4MB_RXLABEL( CAN_MB121 ), CAN_TB_u4MB_RXKIND( 0, 121 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB121, CAN_CFG_ID_VALUE_0_MB121 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB122, CAN_TB_u4MB_RXLABEL( CAN_MB122 ), CAN_TB_u4MB_RXKIND( 0, 122 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB122, CAN_CFG_ID_VALUE_0_MB122 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB123, CAN_TB_u4MB_RXLABEL( CAN_MB123 ), CAN_TB_u4MB_RXKIND( 0, 123 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB123, CAN_CFG_ID_VALUE_0_MB123 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB124, CAN_TB_u4MB_RXLABEL( CAN_MB124 ), CAN_TB_u4MB_RXKIND( 0, 124 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB124, CAN_CFG_ID_VALUE_0_MB124 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB125, CAN_TB_u4MB_RXLABEL( CAN_MB125 ), CAN_TB_u4MB_RXKIND( 0, 125 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB125, CAN_CFG_ID_VALUE_0_MB125 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB126, CAN_TB_u4MB_RXLABEL( CAN_MB126 ), CAN_TB_u4MB_RXKIND( 0, 126 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB126, CAN_CFG_ID_VALUE_0_MB126 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB127, CAN_TB_u4MB_RXLABEL( CAN_MB127 ), CAN_TB_u4MB_RXKIND( 0, 127 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB127, CAN_CFG_ID_VALUE_0_MB127 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB128, CAN_TB_u4MB_RXLABEL( CAN_MB128 ), CAN_TB_u4MB_RXKIND( 0, 128 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB128, CAN_CFG_ID_VALUE_0_MB128 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB129, CAN_TB_u4MB_RXLABEL( CAN_MB129 ), CAN_TB_u4MB_RXKIND( 0, 129 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB129, CAN_CFG_ID_VALUE_0_MB129 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB130, CAN_TB_u4MB_RXLABEL( CAN_MB130 ), CAN_TB_u4MB_RXKIND( 0, 130 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB130, CAN_CFG_ID_VALUE_0_MB130 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB131, CAN_TB_u4MB_RXLABEL( CAN_MB131 ), CAN_TB_u4MB_RXKIND( 0, 131 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB131, CAN_CFG_ID_VALUE_0_MB131 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB132, CAN_TB_u4MB_RXLABEL( CAN_MB132 ), CAN_TB_u4MB_RXKIND( 0, 132 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB132, CAN_CFG_ID_VALUE_0_MB132 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB133, CAN_TB_u4MB_RXLABEL( CAN_MB133 ), CAN_TB_u4MB_RXKIND( 0, 133 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB133, CAN_CFG_ID_VALUE_0_MB133 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB134, CAN_TB_u4MB_RXLABEL( CAN_MB134 ), CAN_TB_u4MB_RXKIND( 0, 134 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB134, CAN_CFG_ID_VALUE_0_MB134 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB135, CAN_TB_u4MB_RXLABEL( CAN_MB135 ), CAN_TB_u4MB_RXKIND( 0, 135 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB135, CAN_CFG_ID_VALUE_0_MB135 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB136, CAN_TB_u4MB_RXLABEL( CAN_MB136 ), CAN_TB_u4MB_RXKIND( 0, 136 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB136, CAN_CFG_ID_VALUE_0_MB136 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB137, CAN_TB_u4MB_RXLABEL( CAN_MB137 ), CAN_TB_u4MB_RXKIND( 0, 137 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB137, CAN_CFG_ID_VALUE_0_MB137 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB138, CAN_TB_u4MB_RXLABEL( CAN_MB138 ), CAN_TB_u4MB_RXKIND( 0, 138 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB138, CAN_CFG_ID_VALUE_0_MB138 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB139, CAN_TB_u4MB_RXLABEL( CAN_MB139 ), CAN_TB_u4MB_RXKIND( 0, 139 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB139, CAN_CFG_ID_VALUE_0_MB139 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB140, CAN_TB_u4MB_RXLABEL( CAN_MB140 ), CAN_TB_u4MB_RXKIND( 0, 140 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB140, CAN_CFG_ID_VALUE_0_MB140 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB141, CAN_TB_u4MB_RXLABEL( CAN_MB141 ), CAN_TB_u4MB_RXKIND( 0, 141 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB141, CAN_CFG_ID_VALUE_0_MB141 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB142, CAN_TB_u4MB_RXLABEL( CAN_MB142 ), CAN_TB_u4MB_RXKIND( 0, 142 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB142, CAN_CFG_ID_VALUE_0_MB142 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB143, CAN_TB_u4MB_RXLABEL( CAN_MB143 ), CAN_TB_u4MB_RXKIND( 0, 143 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB143, CAN_CFG_ID_VALUE_0_MB143 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB144, CAN_TB_u4MB_RXLABEL( CAN_MB144 ), CAN_TB_u4MB_RXKIND( 0, 144 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB144, CAN_CFG_ID_VALUE_0_MB144 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB145, CAN_TB_u4MB_RXLABEL( CAN_MB145 ), CAN_TB_u4MB_RXKIND( 0, 145 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB145, CAN_CFG_ID_VALUE_0_MB145 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB146, CAN_TB_u4MB_RXLABEL( CAN_MB146 ), CAN_TB_u4MB_RXKIND( 0, 146 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB146, CAN_CFG_ID_VALUE_0_MB146 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB147, CAN_TB_u4MB_RXLABEL( CAN_MB147 ), CAN_TB_u4MB_RXKIND( 0, 147 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB147, CAN_CFG_ID_VALUE_0_MB147 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB148, CAN_TB_u4MB_RXLABEL( CAN_MB148 ), CAN_TB_u4MB_RXKIND( 0, 148 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB148, CAN_CFG_ID_VALUE_0_MB148 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB149, CAN_TB_u4MB_RXLABEL( CAN_MB149 ), CAN_TB_u4MB_RXKIND( 0, 149 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB149, CAN_CFG_ID_VALUE_0_MB149 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB150, CAN_TB_u4MB_RXLABEL( CAN_MB150 ), CAN_TB_u4MB_RXKIND( 0, 150 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB150, CAN_CFG_ID_VALUE_0_MB150 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB151, CAN_TB_u4MB_RXLABEL( CAN_MB151 ), CAN_TB_u4MB_RXKIND( 0, 151 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB151, CAN_CFG_ID_VALUE_0_MB151 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB152, CAN_TB_u4MB_RXLABEL( CAN_MB152 ), CAN_TB_u4MB_RXKIND( 0, 152 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB152, CAN_CFG_ID_VALUE_0_MB152 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB153, CAN_TB_u4MB_RXLABEL( CAN_MB153 ), CAN_TB_u4MB_RXKIND( 0, 153 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB153, CAN_CFG_ID_VALUE_0_MB153 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB154, CAN_TB_u4MB_RXLABEL( CAN_MB154 ), CAN_TB_u4MB_RXKIND( 0, 154 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB154, CAN_CFG_ID_VALUE_0_MB154 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB155, CAN_TB_u4MB_RXLABEL( CAN_MB155 ), CAN_TB_u4MB_RXKIND( 0, 155 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB155, CAN_CFG_ID_VALUE_0_MB155 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB156, CAN_TB_u4MB_RXLABEL( CAN_MB156 ), CAN_TB_u4MB_RXKIND( 0, 156 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB156, CAN_CFG_ID_VALUE_0_MB156 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB157, CAN_TB_u4MB_RXLABEL( CAN_MB157 ), CAN_TB_u4MB_RXKIND( 0, 157 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB157, CAN_CFG_ID_VALUE_0_MB157 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB158, CAN_TB_u4MB_RXLABEL( CAN_MB158 ), CAN_TB_u4MB_RXKIND( 0, 158 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB158, CAN_CFG_ID_VALUE_0_MB158 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB159, CAN_TB_u4MB_RXLABEL( CAN_MB159 ), CAN_TB_u4MB_RXKIND( 0, 159 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB159, CAN_CFG_ID_VALUE_0_MB159 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB160, CAN_TB_u4MB_RXLABEL( CAN_MB160 ), CAN_TB_u4MB_RXKIND( 0, 160 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB160, CAN_CFG_ID_VALUE_0_MB160 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB161, CAN_TB_u4MB_RXLABEL( CAN_MB161 ), CAN_TB_u4MB_RXKIND( 0, 161 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB161, CAN_CFG_ID_VALUE_0_MB161 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB162, CAN_TB_u4MB_RXLABEL( CAN_MB162 ), CAN_TB_u4MB_RXKIND( 0, 162 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB162, CAN_CFG_ID_VALUE_0_MB162 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB163, CAN_TB_u4MB_RXLABEL( CAN_MB163 ), CAN_TB_u4MB_RXKIND( 0, 163 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB163, CAN_CFG_ID_VALUE_0_MB163 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB164, CAN_TB_u4MB_RXLABEL( CAN_MB164 ), CAN_TB_u4MB_RXKIND( 0, 164 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB164, CAN_CFG_ID_VALUE_0_MB164 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB165, CAN_TB_u4MB_RXLABEL( CAN_MB165 ), CAN_TB_u4MB_RXKIND( 0, 165 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB165, CAN_CFG_ID_VALUE_0_MB165 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB166, CAN_TB_u4MB_RXLABEL( CAN_MB166 ), CAN_TB_u4MB_RXKIND( 0, 166 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB166, CAN_CFG_ID_VALUE_0_MB166 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB167, CAN_TB_u4MB_RXLABEL( CAN_MB167 ), CAN_TB_u4MB_RXKIND( 0, 167 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB167, CAN_CFG_ID_VALUE_0_MB167 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB168, CAN_TB_u4MB_RXLABEL( CAN_MB168 ), CAN_TB_u4MB_RXKIND( 0, 168 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB168, CAN_CFG_ID_VALUE_0_MB168 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB169, CAN_TB_u4MB_RXLABEL( CAN_MB169 ), CAN_TB_u4MB_RXKIND( 0, 169 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB169, CAN_CFG_ID_VALUE_0_MB169 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB170, CAN_TB_u4MB_RXLABEL( CAN_MB170 ), CAN_TB_u4MB_RXKIND( 0, 170 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB170, CAN_CFG_ID_VALUE_0_MB170 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB171, CAN_TB_u4MB_RXLABEL( CAN_MB171 ), CAN_TB_u4MB_RXKIND( 0, 171 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB171, CAN_CFG_ID_VALUE_0_MB171 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB172, CAN_TB_u4MB_RXLABEL( CAN_MB172 ), CAN_TB_u4MB_RXKIND( 0, 172 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB172, CAN_CFG_ID_VALUE_0_MB172 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB173, CAN_TB_u4MB_RXLABEL( CAN_MB173 ), CAN_TB_u4MB_RXKIND( 0, 173 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB173, CAN_CFG_ID_VALUE_0_MB173 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB174, CAN_TB_u4MB_RXLABEL( CAN_MB174 ), CAN_TB_u4MB_RXKIND( 0, 174 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB174, CAN_CFG_ID_VALUE_0_MB174 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB175, CAN_TB_u4MB_RXLABEL( CAN_MB175 ), CAN_TB_u4MB_RXKIND( 0, 175 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB175, CAN_CFG_ID_VALUE_0_MB175 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB176, CAN_TB_u4MB_RXLABEL( CAN_MB176 ), CAN_TB_u4MB_RXKIND( 0, 176 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB176, CAN_CFG_ID_VALUE_0_MB176 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB177, CAN_TB_u4MB_RXLABEL( CAN_MB177 ), CAN_TB_u4MB_RXKIND( 0, 177 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB177, CAN_CFG_ID_VALUE_0_MB177 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB178, CAN_TB_u4MB_RXLABEL( CAN_MB178 ), CAN_TB_u4MB_RXKIND( 0, 178 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB178, CAN_CFG_ID_VALUE_0_MB178 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB179, CAN_TB_u4MB_RXLABEL( CAN_MB179 ), CAN_TB_u4MB_RXKIND( 0, 179 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB179, CAN_CFG_ID_VALUE_0_MB179 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB180, CAN_TB_u4MB_RXLABEL( CAN_MB180 ), CAN_TB_u4MB_RXKIND( 0, 180 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB180, CAN_CFG_ID_VALUE_0_MB180 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB181, CAN_TB_u4MB_RXLABEL( CAN_MB181 ), CAN_TB_u4MB_RXKIND( 0, 181 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB181, CAN_CFG_ID_VALUE_0_MB181 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB182, CAN_TB_u4MB_RXLABEL( CAN_MB182 ), CAN_TB_u4MB_RXKIND( 0, 182 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB182, CAN_CFG_ID_VALUE_0_MB182 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB183, CAN_TB_u4MB_RXLABEL( CAN_MB183 ), CAN_TB_u4MB_RXKIND( 0, 183 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB183, CAN_CFG_ID_VALUE_0_MB183 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB184, CAN_TB_u4MB_RXLABEL( CAN_MB184 ), CAN_TB_u4MB_RXKIND( 0, 184 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB184, CAN_CFG_ID_VALUE_0_MB184 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB185, CAN_TB_u4MB_RXLABEL( CAN_MB185 ), CAN_TB_u4MB_RXKIND( 0, 185 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB185, CAN_CFG_ID_VALUE_0_MB185 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB186, CAN_TB_u4MB_RXLABEL( CAN_MB186 ), CAN_TB_u4MB_RXKIND( 0, 186 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB186, CAN_CFG_ID_VALUE_0_MB186 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB187, CAN_TB_u4MB_RXLABEL( CAN_MB187 ), CAN_TB_u4MB_RXKIND( 0, 187 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB187, CAN_CFG_ID_VALUE_0_MB187 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB188, CAN_TB_u4MB_RXLABEL( CAN_MB188 ), CAN_TB_u4MB_RXKIND( 0, 188 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB188, CAN_CFG_ID_VALUE_0_MB188 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB189, CAN_TB_u4MB_RXLABEL( CAN_MB189 ), CAN_TB_u4MB_RXKIND( 0, 189 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB189, CAN_CFG_ID_VALUE_0_MB189 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB190, CAN_TB_u4MB_RXLABEL( CAN_MB190 ), CAN_TB_u4MB_RXKIND( 0, 190 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB190, CAN_CFG_ID_VALUE_0_MB190 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_0_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_0_MB191, CAN_TB_u4MB_RXLABEL( CAN_MB191 ), CAN_TB_u4MB_RXKIND( 0, 191 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_0_MB191, CAN_CFG_ID_VALUE_0_MB191 ) },
#endif /* ( (CAN_CFG_MBOXSET_0_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */

    /* Controller 1 */
#if ( (CAN_CFG_MBOXSET_1_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB000, CAN_TB_u4MB_RXLABEL( CAN_MB000 ), CAN_TB_u4MB_RXKIND( 1, 000 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB000, CAN_CFG_ID_VALUE_1_MB000 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB001, CAN_TB_u4MB_RXLABEL( CAN_MB001 ), CAN_TB_u4MB_RXKIND( 1, 001 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB001, CAN_CFG_ID_VALUE_1_MB001 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB002, CAN_TB_u4MB_RXLABEL( CAN_MB002 ), CAN_TB_u4MB_RXKIND( 1, 002 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB002, CAN_CFG_ID_VALUE_1_MB002 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB003, CAN_TB_u4MB_RXLABEL( CAN_MB003 ), CAN_TB_u4MB_RXKIND( 1, 003 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB003, CAN_CFG_ID_VALUE_1_MB003 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB004, CAN_TB_u4MB_RXLABEL( CAN_MB004 ), CAN_TB_u4MB_RXKIND( 1, 004 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB004, CAN_CFG_ID_VALUE_1_MB004 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB005, CAN_TB_u4MB_RXLABEL( CAN_MB005 ), CAN_TB_u4MB_RXKIND( 1, 005 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB005, CAN_CFG_ID_VALUE_1_MB005 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB006, CAN_TB_u4MB_RXLABEL( CAN_MB006 ), CAN_TB_u4MB_RXKIND( 1, 006 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB006, CAN_CFG_ID_VALUE_1_MB006 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB007, CAN_TB_u4MB_RXLABEL( CAN_MB007 ), CAN_TB_u4MB_RXKIND( 1, 007 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB007, CAN_CFG_ID_VALUE_1_MB007 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB008, CAN_TB_u4MB_RXLABEL( CAN_MB008 ), CAN_TB_u4MB_RXKIND( 1, 008 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB008, CAN_CFG_ID_VALUE_1_MB008 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB009, CAN_TB_u4MB_RXLABEL( CAN_MB009 ), CAN_TB_u4MB_RXKIND( 1, 009 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB009, CAN_CFG_ID_VALUE_1_MB009 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB010, CAN_TB_u4MB_RXLABEL( CAN_MB010 ), CAN_TB_u4MB_RXKIND( 1, 010 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB010, CAN_CFG_ID_VALUE_1_MB010 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB011, CAN_TB_u4MB_RXLABEL( CAN_MB011 ), CAN_TB_u4MB_RXKIND( 1, 011 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB011, CAN_CFG_ID_VALUE_1_MB011 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB012, CAN_TB_u4MB_RXLABEL( CAN_MB012 ), CAN_TB_u4MB_RXKIND( 1, 012 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB012, CAN_CFG_ID_VALUE_1_MB012 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB013, CAN_TB_u4MB_RXLABEL( CAN_MB013 ), CAN_TB_u4MB_RXKIND( 1, 013 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB013, CAN_CFG_ID_VALUE_1_MB013 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB014, CAN_TB_u4MB_RXLABEL( CAN_MB014 ), CAN_TB_u4MB_RXKIND( 1, 014 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB014, CAN_CFG_ID_VALUE_1_MB014 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB015, CAN_TB_u4MB_RXLABEL( CAN_MB015 ), CAN_TB_u4MB_RXKIND( 1, 015 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB015, CAN_CFG_ID_VALUE_1_MB015 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB016, CAN_TB_u4MB_RXLABEL( CAN_MB016 ), CAN_TB_u4MB_RXKIND( 1, 016 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB016, CAN_CFG_ID_VALUE_1_MB016 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB017, CAN_TB_u4MB_RXLABEL( CAN_MB017 ), CAN_TB_u4MB_RXKIND( 1, 017 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB017, CAN_CFG_ID_VALUE_1_MB017 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB018, CAN_TB_u4MB_RXLABEL( CAN_MB018 ), CAN_TB_u4MB_RXKIND( 1, 018 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB018, CAN_CFG_ID_VALUE_1_MB018 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB019, CAN_TB_u4MB_RXLABEL( CAN_MB019 ), CAN_TB_u4MB_RXKIND( 1, 019 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB019, CAN_CFG_ID_VALUE_1_MB019 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB020, CAN_TB_u4MB_RXLABEL( CAN_MB020 ), CAN_TB_u4MB_RXKIND( 1, 020 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB020, CAN_CFG_ID_VALUE_1_MB020 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB021, CAN_TB_u4MB_RXLABEL( CAN_MB021 ), CAN_TB_u4MB_RXKIND( 1, 021 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB021, CAN_CFG_ID_VALUE_1_MB021 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB022, CAN_TB_u4MB_RXLABEL( CAN_MB022 ), CAN_TB_u4MB_RXKIND( 1, 022 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB022, CAN_CFG_ID_VALUE_1_MB022 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB023, CAN_TB_u4MB_RXLABEL( CAN_MB023 ), CAN_TB_u4MB_RXKIND( 1, 023 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB023, CAN_CFG_ID_VALUE_1_MB023 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB024, CAN_TB_u4MB_RXLABEL( CAN_MB024 ), CAN_TB_u4MB_RXKIND( 1, 024 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB024, CAN_CFG_ID_VALUE_1_MB024 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB025, CAN_TB_u4MB_RXLABEL( CAN_MB025 ), CAN_TB_u4MB_RXKIND( 1, 025 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB025, CAN_CFG_ID_VALUE_1_MB025 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB026, CAN_TB_u4MB_RXLABEL( CAN_MB026 ), CAN_TB_u4MB_RXKIND( 1, 026 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB026, CAN_CFG_ID_VALUE_1_MB026 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB027, CAN_TB_u4MB_RXLABEL( CAN_MB027 ), CAN_TB_u4MB_RXKIND( 1, 027 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB027, CAN_CFG_ID_VALUE_1_MB027 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB028, CAN_TB_u4MB_RXLABEL( CAN_MB028 ), CAN_TB_u4MB_RXKIND( 1, 028 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB028, CAN_CFG_ID_VALUE_1_MB028 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB029, CAN_TB_u4MB_RXLABEL( CAN_MB029 ), CAN_TB_u4MB_RXKIND( 1, 029 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB029, CAN_CFG_ID_VALUE_1_MB029 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB030, CAN_TB_u4MB_RXLABEL( CAN_MB030 ), CAN_TB_u4MB_RXKIND( 1, 030 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB030, CAN_CFG_ID_VALUE_1_MB030 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB031, CAN_TB_u4MB_RXLABEL( CAN_MB031 ), CAN_TB_u4MB_RXKIND( 1, 031 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB031, CAN_CFG_ID_VALUE_1_MB031 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB032, CAN_TB_u4MB_RXLABEL( CAN_MB032 ), CAN_TB_u4MB_RXKIND( 1, 032 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB032, CAN_CFG_ID_VALUE_1_MB032 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB033, CAN_TB_u4MB_RXLABEL( CAN_MB033 ), CAN_TB_u4MB_RXKIND( 1, 033 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB033, CAN_CFG_ID_VALUE_1_MB033 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB034, CAN_TB_u4MB_RXLABEL( CAN_MB034 ), CAN_TB_u4MB_RXKIND( 1, 034 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB034, CAN_CFG_ID_VALUE_1_MB034 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB035, CAN_TB_u4MB_RXLABEL( CAN_MB035 ), CAN_TB_u4MB_RXKIND( 1, 035 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB035, CAN_CFG_ID_VALUE_1_MB035 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB036, CAN_TB_u4MB_RXLABEL( CAN_MB036 ), CAN_TB_u4MB_RXKIND( 1, 036 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB036, CAN_CFG_ID_VALUE_1_MB036 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB037, CAN_TB_u4MB_RXLABEL( CAN_MB037 ), CAN_TB_u4MB_RXKIND( 1, 037 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB037, CAN_CFG_ID_VALUE_1_MB037 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB038, CAN_TB_u4MB_RXLABEL( CAN_MB038 ), CAN_TB_u4MB_RXKIND( 1, 038 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB038, CAN_CFG_ID_VALUE_1_MB038 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB039, CAN_TB_u4MB_RXLABEL( CAN_MB039 ), CAN_TB_u4MB_RXKIND( 1, 039 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB039, CAN_CFG_ID_VALUE_1_MB039 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB040, CAN_TB_u4MB_RXLABEL( CAN_MB040 ), CAN_TB_u4MB_RXKIND( 1, 040 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB040, CAN_CFG_ID_VALUE_1_MB040 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB041, CAN_TB_u4MB_RXLABEL( CAN_MB041 ), CAN_TB_u4MB_RXKIND( 1, 041 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB041, CAN_CFG_ID_VALUE_1_MB041 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB042, CAN_TB_u4MB_RXLABEL( CAN_MB042 ), CAN_TB_u4MB_RXKIND( 1, 042 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB042, CAN_CFG_ID_VALUE_1_MB042 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB043, CAN_TB_u4MB_RXLABEL( CAN_MB043 ), CAN_TB_u4MB_RXKIND( 1, 043 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB043, CAN_CFG_ID_VALUE_1_MB043 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB044, CAN_TB_u4MB_RXLABEL( CAN_MB044 ), CAN_TB_u4MB_RXKIND( 1, 044 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB044, CAN_CFG_ID_VALUE_1_MB044 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB045, CAN_TB_u4MB_RXLABEL( CAN_MB045 ), CAN_TB_u4MB_RXKIND( 1, 045 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB045, CAN_CFG_ID_VALUE_1_MB045 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB046, CAN_TB_u4MB_RXLABEL( CAN_MB046 ), CAN_TB_u4MB_RXKIND( 1, 046 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB046, CAN_CFG_ID_VALUE_1_MB046 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB047, CAN_TB_u4MB_RXLABEL( CAN_MB047 ), CAN_TB_u4MB_RXKIND( 1, 047 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB047, CAN_CFG_ID_VALUE_1_MB047 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB048, CAN_TB_u4MB_RXLABEL( CAN_MB048 ), CAN_TB_u4MB_RXKIND( 1, 048 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB048, CAN_CFG_ID_VALUE_1_MB048 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB049, CAN_TB_u4MB_RXLABEL( CAN_MB049 ), CAN_TB_u4MB_RXKIND( 1, 049 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB049, CAN_CFG_ID_VALUE_1_MB049 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB050, CAN_TB_u4MB_RXLABEL( CAN_MB050 ), CAN_TB_u4MB_RXKIND( 1, 050 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB050, CAN_CFG_ID_VALUE_1_MB050 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB051, CAN_TB_u4MB_RXLABEL( CAN_MB051 ), CAN_TB_u4MB_RXKIND( 1, 051 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB051, CAN_CFG_ID_VALUE_1_MB051 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB052, CAN_TB_u4MB_RXLABEL( CAN_MB052 ), CAN_TB_u4MB_RXKIND( 1, 052 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB052, CAN_CFG_ID_VALUE_1_MB052 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB053, CAN_TB_u4MB_RXLABEL( CAN_MB053 ), CAN_TB_u4MB_RXKIND( 1, 053 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB053, CAN_CFG_ID_VALUE_1_MB053 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB054, CAN_TB_u4MB_RXLABEL( CAN_MB054 ), CAN_TB_u4MB_RXKIND( 1, 054 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB054, CAN_CFG_ID_VALUE_1_MB054 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB055, CAN_TB_u4MB_RXLABEL( CAN_MB055 ), CAN_TB_u4MB_RXKIND( 1, 055 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB055, CAN_CFG_ID_VALUE_1_MB055 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB056, CAN_TB_u4MB_RXLABEL( CAN_MB056 ), CAN_TB_u4MB_RXKIND( 1, 056 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB056, CAN_CFG_ID_VALUE_1_MB056 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB057, CAN_TB_u4MB_RXLABEL( CAN_MB057 ), CAN_TB_u4MB_RXKIND( 1, 057 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB057, CAN_CFG_ID_VALUE_1_MB057 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB058, CAN_TB_u4MB_RXLABEL( CAN_MB058 ), CAN_TB_u4MB_RXKIND( 1, 058 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB058, CAN_CFG_ID_VALUE_1_MB058 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB059, CAN_TB_u4MB_RXLABEL( CAN_MB059 ), CAN_TB_u4MB_RXKIND( 1, 059 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB059, CAN_CFG_ID_VALUE_1_MB059 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB060, CAN_TB_u4MB_RXLABEL( CAN_MB060 ), CAN_TB_u4MB_RXKIND( 1, 060 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB060, CAN_CFG_ID_VALUE_1_MB060 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB061, CAN_TB_u4MB_RXLABEL( CAN_MB061 ), CAN_TB_u4MB_RXKIND( 1, 061 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB061, CAN_CFG_ID_VALUE_1_MB061 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB062, CAN_TB_u4MB_RXLABEL( CAN_MB062 ), CAN_TB_u4MB_RXKIND( 1, 062 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB062, CAN_CFG_ID_VALUE_1_MB062 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB063, CAN_TB_u4MB_RXLABEL( CAN_MB063 ), CAN_TB_u4MB_RXKIND( 1, 063 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB063, CAN_CFG_ID_VALUE_1_MB063 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB064, CAN_TB_u4MB_RXLABEL( CAN_MB064 ), CAN_TB_u4MB_RXKIND( 1, 064 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB064, CAN_CFG_ID_VALUE_1_MB064 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB065, CAN_TB_u4MB_RXLABEL( CAN_MB065 ), CAN_TB_u4MB_RXKIND( 1, 065 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB065, CAN_CFG_ID_VALUE_1_MB065 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB066, CAN_TB_u4MB_RXLABEL( CAN_MB066 ), CAN_TB_u4MB_RXKIND( 1, 066 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB066, CAN_CFG_ID_VALUE_1_MB066 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB067, CAN_TB_u4MB_RXLABEL( CAN_MB067 ), CAN_TB_u4MB_RXKIND( 1, 067 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB067, CAN_CFG_ID_VALUE_1_MB067 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB068, CAN_TB_u4MB_RXLABEL( CAN_MB068 ), CAN_TB_u4MB_RXKIND( 1, 068 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB068, CAN_CFG_ID_VALUE_1_MB068 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB069, CAN_TB_u4MB_RXLABEL( CAN_MB069 ), CAN_TB_u4MB_RXKIND( 1, 069 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB069, CAN_CFG_ID_VALUE_1_MB069 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB070, CAN_TB_u4MB_RXLABEL( CAN_MB070 ), CAN_TB_u4MB_RXKIND( 1, 070 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB070, CAN_CFG_ID_VALUE_1_MB070 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB071, CAN_TB_u4MB_RXLABEL( CAN_MB071 ), CAN_TB_u4MB_RXKIND( 1, 071 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB071, CAN_CFG_ID_VALUE_1_MB071 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB072, CAN_TB_u4MB_RXLABEL( CAN_MB072 ), CAN_TB_u4MB_RXKIND( 1, 072 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB072, CAN_CFG_ID_VALUE_1_MB072 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB073, CAN_TB_u4MB_RXLABEL( CAN_MB073 ), CAN_TB_u4MB_RXKIND( 1, 073 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB073, CAN_CFG_ID_VALUE_1_MB073 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB074, CAN_TB_u4MB_RXLABEL( CAN_MB074 ), CAN_TB_u4MB_RXKIND( 1, 074 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB074, CAN_CFG_ID_VALUE_1_MB074 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB075, CAN_TB_u4MB_RXLABEL( CAN_MB075 ), CAN_TB_u4MB_RXKIND( 1, 075 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB075, CAN_CFG_ID_VALUE_1_MB075 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB076, CAN_TB_u4MB_RXLABEL( CAN_MB076 ), CAN_TB_u4MB_RXKIND( 1, 076 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB076, CAN_CFG_ID_VALUE_1_MB076 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB077, CAN_TB_u4MB_RXLABEL( CAN_MB077 ), CAN_TB_u4MB_RXKIND( 1, 077 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB077, CAN_CFG_ID_VALUE_1_MB077 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB078, CAN_TB_u4MB_RXLABEL( CAN_MB078 ), CAN_TB_u4MB_RXKIND( 1, 078 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB078, CAN_CFG_ID_VALUE_1_MB078 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB079, CAN_TB_u4MB_RXLABEL( CAN_MB079 ), CAN_TB_u4MB_RXKIND( 1, 079 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB079, CAN_CFG_ID_VALUE_1_MB079 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB080, CAN_TB_u4MB_RXLABEL( CAN_MB080 ), CAN_TB_u4MB_RXKIND( 1, 080 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB080, CAN_CFG_ID_VALUE_1_MB080 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB081, CAN_TB_u4MB_RXLABEL( CAN_MB081 ), CAN_TB_u4MB_RXKIND( 1, 081 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB081, CAN_CFG_ID_VALUE_1_MB081 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB082, CAN_TB_u4MB_RXLABEL( CAN_MB082 ), CAN_TB_u4MB_RXKIND( 1, 082 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB082, CAN_CFG_ID_VALUE_1_MB082 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB083, CAN_TB_u4MB_RXLABEL( CAN_MB083 ), CAN_TB_u4MB_RXKIND( 1, 083 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB083, CAN_CFG_ID_VALUE_1_MB083 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB084, CAN_TB_u4MB_RXLABEL( CAN_MB084 ), CAN_TB_u4MB_RXKIND( 1, 084 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB084, CAN_CFG_ID_VALUE_1_MB084 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB085, CAN_TB_u4MB_RXLABEL( CAN_MB085 ), CAN_TB_u4MB_RXKIND( 1, 085 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB085, CAN_CFG_ID_VALUE_1_MB085 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB086, CAN_TB_u4MB_RXLABEL( CAN_MB086 ), CAN_TB_u4MB_RXKIND( 1, 086 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB086, CAN_CFG_ID_VALUE_1_MB086 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB087, CAN_TB_u4MB_RXLABEL( CAN_MB087 ), CAN_TB_u4MB_RXKIND( 1, 087 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB087, CAN_CFG_ID_VALUE_1_MB087 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB088, CAN_TB_u4MB_RXLABEL( CAN_MB088 ), CAN_TB_u4MB_RXKIND( 1, 088 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB088, CAN_CFG_ID_VALUE_1_MB088 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB089, CAN_TB_u4MB_RXLABEL( CAN_MB089 ), CAN_TB_u4MB_RXKIND( 1, 089 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB089, CAN_CFG_ID_VALUE_1_MB089 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB090, CAN_TB_u4MB_RXLABEL( CAN_MB090 ), CAN_TB_u4MB_RXKIND( 1, 090 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB090, CAN_CFG_ID_VALUE_1_MB090 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB091, CAN_TB_u4MB_RXLABEL( CAN_MB091 ), CAN_TB_u4MB_RXKIND( 1, 091 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB091, CAN_CFG_ID_VALUE_1_MB091 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB092, CAN_TB_u4MB_RXLABEL( CAN_MB092 ), CAN_TB_u4MB_RXKIND( 1, 092 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB092, CAN_CFG_ID_VALUE_1_MB092 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB093, CAN_TB_u4MB_RXLABEL( CAN_MB093 ), CAN_TB_u4MB_RXKIND( 1, 093 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB093, CAN_CFG_ID_VALUE_1_MB093 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB094, CAN_TB_u4MB_RXLABEL( CAN_MB094 ), CAN_TB_u4MB_RXKIND( 1, 094 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB094, CAN_CFG_ID_VALUE_1_MB094 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB095, CAN_TB_u4MB_RXLABEL( CAN_MB095 ), CAN_TB_u4MB_RXKIND( 1, 095 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB095, CAN_CFG_ID_VALUE_1_MB095 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB096, CAN_TB_u4MB_RXLABEL( CAN_MB096 ), CAN_TB_u4MB_RXKIND( 1, 096 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB096, CAN_CFG_ID_VALUE_1_MB096 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB097, CAN_TB_u4MB_RXLABEL( CAN_MB097 ), CAN_TB_u4MB_RXKIND( 1, 097 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB097, CAN_CFG_ID_VALUE_1_MB097 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB098, CAN_TB_u4MB_RXLABEL( CAN_MB098 ), CAN_TB_u4MB_RXKIND( 1, 098 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB098, CAN_CFG_ID_VALUE_1_MB098 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB099, CAN_TB_u4MB_RXLABEL( CAN_MB099 ), CAN_TB_u4MB_RXKIND( 1, 099 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB099, CAN_CFG_ID_VALUE_1_MB099 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB100, CAN_TB_u4MB_RXLABEL( CAN_MB100 ), CAN_TB_u4MB_RXKIND( 1, 100 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB100, CAN_CFG_ID_VALUE_1_MB100 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB101, CAN_TB_u4MB_RXLABEL( CAN_MB101 ), CAN_TB_u4MB_RXKIND( 1, 101 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB101, CAN_CFG_ID_VALUE_1_MB101 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB102, CAN_TB_u4MB_RXLABEL( CAN_MB102 ), CAN_TB_u4MB_RXKIND( 1, 102 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB102, CAN_CFG_ID_VALUE_1_MB102 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB103, CAN_TB_u4MB_RXLABEL( CAN_MB103 ), CAN_TB_u4MB_RXKIND( 1, 103 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB103, CAN_CFG_ID_VALUE_1_MB103 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB104, CAN_TB_u4MB_RXLABEL( CAN_MB104 ), CAN_TB_u4MB_RXKIND( 1, 104 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB104, CAN_CFG_ID_VALUE_1_MB104 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB105, CAN_TB_u4MB_RXLABEL( CAN_MB105 ), CAN_TB_u4MB_RXKIND( 1, 105 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB105, CAN_CFG_ID_VALUE_1_MB105 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB106, CAN_TB_u4MB_RXLABEL( CAN_MB106 ), CAN_TB_u4MB_RXKIND( 1, 106 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB106, CAN_CFG_ID_VALUE_1_MB106 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB107, CAN_TB_u4MB_RXLABEL( CAN_MB107 ), CAN_TB_u4MB_RXKIND( 1, 107 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB107, CAN_CFG_ID_VALUE_1_MB107 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB108, CAN_TB_u4MB_RXLABEL( CAN_MB108 ), CAN_TB_u4MB_RXKIND( 1, 108 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB108, CAN_CFG_ID_VALUE_1_MB108 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB109, CAN_TB_u4MB_RXLABEL( CAN_MB109 ), CAN_TB_u4MB_RXKIND( 1, 109 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB109, CAN_CFG_ID_VALUE_1_MB109 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB110, CAN_TB_u4MB_RXLABEL( CAN_MB110 ), CAN_TB_u4MB_RXKIND( 1, 110 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB110, CAN_CFG_ID_VALUE_1_MB110 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB111, CAN_TB_u4MB_RXLABEL( CAN_MB111 ), CAN_TB_u4MB_RXKIND( 1, 111 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB111, CAN_CFG_ID_VALUE_1_MB111 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB112, CAN_TB_u4MB_RXLABEL( CAN_MB112 ), CAN_TB_u4MB_RXKIND( 1, 112 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB112, CAN_CFG_ID_VALUE_1_MB112 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB113, CAN_TB_u4MB_RXLABEL( CAN_MB113 ), CAN_TB_u4MB_RXKIND( 1, 113 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB113, CAN_CFG_ID_VALUE_1_MB113 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB114, CAN_TB_u4MB_RXLABEL( CAN_MB114 ), CAN_TB_u4MB_RXKIND( 1, 114 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB114, CAN_CFG_ID_VALUE_1_MB114 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB115, CAN_TB_u4MB_RXLABEL( CAN_MB115 ), CAN_TB_u4MB_RXKIND( 1, 115 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB115, CAN_CFG_ID_VALUE_1_MB115 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB116, CAN_TB_u4MB_RXLABEL( CAN_MB116 ), CAN_TB_u4MB_RXKIND( 1, 116 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB116, CAN_CFG_ID_VALUE_1_MB116 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB117, CAN_TB_u4MB_RXLABEL( CAN_MB117 ), CAN_TB_u4MB_RXKIND( 1, 117 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB117, CAN_CFG_ID_VALUE_1_MB117 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB118, CAN_TB_u4MB_RXLABEL( CAN_MB118 ), CAN_TB_u4MB_RXKIND( 1, 118 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB118, CAN_CFG_ID_VALUE_1_MB118 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB119, CAN_TB_u4MB_RXLABEL( CAN_MB119 ), CAN_TB_u4MB_RXKIND( 1, 119 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB119, CAN_CFG_ID_VALUE_1_MB119 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB120, CAN_TB_u4MB_RXLABEL( CAN_MB120 ), CAN_TB_u4MB_RXKIND( 1, 120 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB120, CAN_CFG_ID_VALUE_1_MB120 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB121, CAN_TB_u4MB_RXLABEL( CAN_MB121 ), CAN_TB_u4MB_RXKIND( 1, 121 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB121, CAN_CFG_ID_VALUE_1_MB121 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB122, CAN_TB_u4MB_RXLABEL( CAN_MB122 ), CAN_TB_u4MB_RXKIND( 1, 122 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB122, CAN_CFG_ID_VALUE_1_MB122 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB123, CAN_TB_u4MB_RXLABEL( CAN_MB123 ), CAN_TB_u4MB_RXKIND( 1, 123 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB123, CAN_CFG_ID_VALUE_1_MB123 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB124, CAN_TB_u4MB_RXLABEL( CAN_MB124 ), CAN_TB_u4MB_RXKIND( 1, 124 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB124, CAN_CFG_ID_VALUE_1_MB124 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB125, CAN_TB_u4MB_RXLABEL( CAN_MB125 ), CAN_TB_u4MB_RXKIND( 1, 125 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB125, CAN_CFG_ID_VALUE_1_MB125 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB126, CAN_TB_u4MB_RXLABEL( CAN_MB126 ), CAN_TB_u4MB_RXKIND( 1, 126 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB126, CAN_CFG_ID_VALUE_1_MB126 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB127, CAN_TB_u4MB_RXLABEL( CAN_MB127 ), CAN_TB_u4MB_RXKIND( 1, 127 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB127, CAN_CFG_ID_VALUE_1_MB127 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB128, CAN_TB_u4MB_RXLABEL( CAN_MB128 ), CAN_TB_u4MB_RXKIND( 1, 128 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB128, CAN_CFG_ID_VALUE_1_MB128 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB129, CAN_TB_u4MB_RXLABEL( CAN_MB129 ), CAN_TB_u4MB_RXKIND( 1, 129 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB129, CAN_CFG_ID_VALUE_1_MB129 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB130, CAN_TB_u4MB_RXLABEL( CAN_MB130 ), CAN_TB_u4MB_RXKIND( 1, 130 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB130, CAN_CFG_ID_VALUE_1_MB130 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB131, CAN_TB_u4MB_RXLABEL( CAN_MB131 ), CAN_TB_u4MB_RXKIND( 1, 131 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB131, CAN_CFG_ID_VALUE_1_MB131 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB132, CAN_TB_u4MB_RXLABEL( CAN_MB132 ), CAN_TB_u4MB_RXKIND( 1, 132 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB132, CAN_CFG_ID_VALUE_1_MB132 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB133, CAN_TB_u4MB_RXLABEL( CAN_MB133 ), CAN_TB_u4MB_RXKIND( 1, 133 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB133, CAN_CFG_ID_VALUE_1_MB133 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB134, CAN_TB_u4MB_RXLABEL( CAN_MB134 ), CAN_TB_u4MB_RXKIND( 1, 134 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB134, CAN_CFG_ID_VALUE_1_MB134 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB135, CAN_TB_u4MB_RXLABEL( CAN_MB135 ), CAN_TB_u4MB_RXKIND( 1, 135 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB135, CAN_CFG_ID_VALUE_1_MB135 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB136, CAN_TB_u4MB_RXLABEL( CAN_MB136 ), CAN_TB_u4MB_RXKIND( 1, 136 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB136, CAN_CFG_ID_VALUE_1_MB136 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB137, CAN_TB_u4MB_RXLABEL( CAN_MB137 ), CAN_TB_u4MB_RXKIND( 1, 137 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB137, CAN_CFG_ID_VALUE_1_MB137 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB138, CAN_TB_u4MB_RXLABEL( CAN_MB138 ), CAN_TB_u4MB_RXKIND( 1, 138 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB138, CAN_CFG_ID_VALUE_1_MB138 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB139, CAN_TB_u4MB_RXLABEL( CAN_MB139 ), CAN_TB_u4MB_RXKIND( 1, 139 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB139, CAN_CFG_ID_VALUE_1_MB139 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB140, CAN_TB_u4MB_RXLABEL( CAN_MB140 ), CAN_TB_u4MB_RXKIND( 1, 140 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB140, CAN_CFG_ID_VALUE_1_MB140 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB141, CAN_TB_u4MB_RXLABEL( CAN_MB141 ), CAN_TB_u4MB_RXKIND( 1, 141 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB141, CAN_CFG_ID_VALUE_1_MB141 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB142, CAN_TB_u4MB_RXLABEL( CAN_MB142 ), CAN_TB_u4MB_RXKIND( 1, 142 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB142, CAN_CFG_ID_VALUE_1_MB142 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB143, CAN_TB_u4MB_RXLABEL( CAN_MB143 ), CAN_TB_u4MB_RXKIND( 1, 143 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB143, CAN_CFG_ID_VALUE_1_MB143 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB144, CAN_TB_u4MB_RXLABEL( CAN_MB144 ), CAN_TB_u4MB_RXKIND( 1, 144 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB144, CAN_CFG_ID_VALUE_1_MB144 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB145, CAN_TB_u4MB_RXLABEL( CAN_MB145 ), CAN_TB_u4MB_RXKIND( 1, 145 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB145, CAN_CFG_ID_VALUE_1_MB145 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB146, CAN_TB_u4MB_RXLABEL( CAN_MB146 ), CAN_TB_u4MB_RXKIND( 1, 146 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB146, CAN_CFG_ID_VALUE_1_MB146 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB147, CAN_TB_u4MB_RXLABEL( CAN_MB147 ), CAN_TB_u4MB_RXKIND( 1, 147 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB147, CAN_CFG_ID_VALUE_1_MB147 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB148, CAN_TB_u4MB_RXLABEL( CAN_MB148 ), CAN_TB_u4MB_RXKIND( 1, 148 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB148, CAN_CFG_ID_VALUE_1_MB148 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB149, CAN_TB_u4MB_RXLABEL( CAN_MB149 ), CAN_TB_u4MB_RXKIND( 1, 149 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB149, CAN_CFG_ID_VALUE_1_MB149 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB150, CAN_TB_u4MB_RXLABEL( CAN_MB150 ), CAN_TB_u4MB_RXKIND( 1, 150 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB150, CAN_CFG_ID_VALUE_1_MB150 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB151, CAN_TB_u4MB_RXLABEL( CAN_MB151 ), CAN_TB_u4MB_RXKIND( 1, 151 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB151, CAN_CFG_ID_VALUE_1_MB151 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB152, CAN_TB_u4MB_RXLABEL( CAN_MB152 ), CAN_TB_u4MB_RXKIND( 1, 152 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB152, CAN_CFG_ID_VALUE_1_MB152 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB153, CAN_TB_u4MB_RXLABEL( CAN_MB153 ), CAN_TB_u4MB_RXKIND( 1, 153 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB153, CAN_CFG_ID_VALUE_1_MB153 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB154, CAN_TB_u4MB_RXLABEL( CAN_MB154 ), CAN_TB_u4MB_RXKIND( 1, 154 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB154, CAN_CFG_ID_VALUE_1_MB154 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB155, CAN_TB_u4MB_RXLABEL( CAN_MB155 ), CAN_TB_u4MB_RXKIND( 1, 155 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB155, CAN_CFG_ID_VALUE_1_MB155 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB156, CAN_TB_u4MB_RXLABEL( CAN_MB156 ), CAN_TB_u4MB_RXKIND( 1, 156 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB156, CAN_CFG_ID_VALUE_1_MB156 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB157, CAN_TB_u4MB_RXLABEL( CAN_MB157 ), CAN_TB_u4MB_RXKIND( 1, 157 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB157, CAN_CFG_ID_VALUE_1_MB157 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB158, CAN_TB_u4MB_RXLABEL( CAN_MB158 ), CAN_TB_u4MB_RXKIND( 1, 158 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB158, CAN_CFG_ID_VALUE_1_MB158 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB159, CAN_TB_u4MB_RXLABEL( CAN_MB159 ), CAN_TB_u4MB_RXKIND( 1, 159 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB159, CAN_CFG_ID_VALUE_1_MB159 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB160, CAN_TB_u4MB_RXLABEL( CAN_MB160 ), CAN_TB_u4MB_RXKIND( 1, 160 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB160, CAN_CFG_ID_VALUE_1_MB160 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB161, CAN_TB_u4MB_RXLABEL( CAN_MB161 ), CAN_TB_u4MB_RXKIND( 1, 161 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB161, CAN_CFG_ID_VALUE_1_MB161 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB162, CAN_TB_u4MB_RXLABEL( CAN_MB162 ), CAN_TB_u4MB_RXKIND( 1, 162 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB162, CAN_CFG_ID_VALUE_1_MB162 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB163, CAN_TB_u4MB_RXLABEL( CAN_MB163 ), CAN_TB_u4MB_RXKIND( 1, 163 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB163, CAN_CFG_ID_VALUE_1_MB163 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB164, CAN_TB_u4MB_RXLABEL( CAN_MB164 ), CAN_TB_u4MB_RXKIND( 1, 164 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB164, CAN_CFG_ID_VALUE_1_MB164 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB165, CAN_TB_u4MB_RXLABEL( CAN_MB165 ), CAN_TB_u4MB_RXKIND( 1, 165 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB165, CAN_CFG_ID_VALUE_1_MB165 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB166, CAN_TB_u4MB_RXLABEL( CAN_MB166 ), CAN_TB_u4MB_RXKIND( 1, 166 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB166, CAN_CFG_ID_VALUE_1_MB166 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB167, CAN_TB_u4MB_RXLABEL( CAN_MB167 ), CAN_TB_u4MB_RXKIND( 1, 167 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB167, CAN_CFG_ID_VALUE_1_MB167 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB168, CAN_TB_u4MB_RXLABEL( CAN_MB168 ), CAN_TB_u4MB_RXKIND( 1, 168 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB168, CAN_CFG_ID_VALUE_1_MB168 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB169, CAN_TB_u4MB_RXLABEL( CAN_MB169 ), CAN_TB_u4MB_RXKIND( 1, 169 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB169, CAN_CFG_ID_VALUE_1_MB169 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB170, CAN_TB_u4MB_RXLABEL( CAN_MB170 ), CAN_TB_u4MB_RXKIND( 1, 170 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB170, CAN_CFG_ID_VALUE_1_MB170 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB171, CAN_TB_u4MB_RXLABEL( CAN_MB171 ), CAN_TB_u4MB_RXKIND( 1, 171 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB171, CAN_CFG_ID_VALUE_1_MB171 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB172, CAN_TB_u4MB_RXLABEL( CAN_MB172 ), CAN_TB_u4MB_RXKIND( 1, 172 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB172, CAN_CFG_ID_VALUE_1_MB172 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB173, CAN_TB_u4MB_RXLABEL( CAN_MB173 ), CAN_TB_u4MB_RXKIND( 1, 173 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB173, CAN_CFG_ID_VALUE_1_MB173 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB174, CAN_TB_u4MB_RXLABEL( CAN_MB174 ), CAN_TB_u4MB_RXKIND( 1, 174 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB174, CAN_CFG_ID_VALUE_1_MB174 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB175, CAN_TB_u4MB_RXLABEL( CAN_MB175 ), CAN_TB_u4MB_RXKIND( 1, 175 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB175, CAN_CFG_ID_VALUE_1_MB175 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB176, CAN_TB_u4MB_RXLABEL( CAN_MB176 ), CAN_TB_u4MB_RXKIND( 1, 176 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB176, CAN_CFG_ID_VALUE_1_MB176 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB177, CAN_TB_u4MB_RXLABEL( CAN_MB177 ), CAN_TB_u4MB_RXKIND( 1, 177 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB177, CAN_CFG_ID_VALUE_1_MB177 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB178, CAN_TB_u4MB_RXLABEL( CAN_MB178 ), CAN_TB_u4MB_RXKIND( 1, 178 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB178, CAN_CFG_ID_VALUE_1_MB178 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB179, CAN_TB_u4MB_RXLABEL( CAN_MB179 ), CAN_TB_u4MB_RXKIND( 1, 179 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB179, CAN_CFG_ID_VALUE_1_MB179 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB180, CAN_TB_u4MB_RXLABEL( CAN_MB180 ), CAN_TB_u4MB_RXKIND( 1, 180 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB180, CAN_CFG_ID_VALUE_1_MB180 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB181, CAN_TB_u4MB_RXLABEL( CAN_MB181 ), CAN_TB_u4MB_RXKIND( 1, 181 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB181, CAN_CFG_ID_VALUE_1_MB181 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB182, CAN_TB_u4MB_RXLABEL( CAN_MB182 ), CAN_TB_u4MB_RXKIND( 1, 182 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB182, CAN_CFG_ID_VALUE_1_MB182 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB183, CAN_TB_u4MB_RXLABEL( CAN_MB183 ), CAN_TB_u4MB_RXKIND( 1, 183 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB183, CAN_CFG_ID_VALUE_1_MB183 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB184, CAN_TB_u4MB_RXLABEL( CAN_MB184 ), CAN_TB_u4MB_RXKIND( 1, 184 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB184, CAN_CFG_ID_VALUE_1_MB184 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB185, CAN_TB_u4MB_RXLABEL( CAN_MB185 ), CAN_TB_u4MB_RXKIND( 1, 185 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB185, CAN_CFG_ID_VALUE_1_MB185 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB186, CAN_TB_u4MB_RXLABEL( CAN_MB186 ), CAN_TB_u4MB_RXKIND( 1, 186 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB186, CAN_CFG_ID_VALUE_1_MB186 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB187, CAN_TB_u4MB_RXLABEL( CAN_MB187 ), CAN_TB_u4MB_RXKIND( 1, 187 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB187, CAN_CFG_ID_VALUE_1_MB187 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB188, CAN_TB_u4MB_RXLABEL( CAN_MB188 ), CAN_TB_u4MB_RXKIND( 1, 188 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB188, CAN_CFG_ID_VALUE_1_MB188 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB189, CAN_TB_u4MB_RXLABEL( CAN_MB189 ), CAN_TB_u4MB_RXKIND( 1, 189 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB189, CAN_CFG_ID_VALUE_1_MB189 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB190, CAN_TB_u4MB_RXLABEL( CAN_MB190 ), CAN_TB_u4MB_RXKIND( 1, 190 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB190, CAN_CFG_ID_VALUE_1_MB190 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_1_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_1_MB191, CAN_TB_u4MB_RXLABEL( CAN_MB191 ), CAN_TB_u4MB_RXKIND( 1, 191 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_1_MB191, CAN_CFG_ID_VALUE_1_MB191 ) },
#endif /* ( (CAN_CFG_MBOXSET_1_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */

    /* Controller 2 */
#if ( (CAN_CFG_MBOXSET_2_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB000, CAN_TB_u4MB_RXLABEL( CAN_MB000 ), CAN_TB_u4MB_RXKIND( 2, 000 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB000, CAN_CFG_ID_VALUE_2_MB000 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB001, CAN_TB_u4MB_RXLABEL( CAN_MB001 ), CAN_TB_u4MB_RXKIND( 2, 001 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB001, CAN_CFG_ID_VALUE_2_MB001 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB002, CAN_TB_u4MB_RXLABEL( CAN_MB002 ), CAN_TB_u4MB_RXKIND( 2, 002 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB002, CAN_CFG_ID_VALUE_2_MB002 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB003, CAN_TB_u4MB_RXLABEL( CAN_MB003 ), CAN_TB_u4MB_RXKIND( 2, 003 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB003, CAN_CFG_ID_VALUE_2_MB003 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB004, CAN_TB_u4MB_RXLABEL( CAN_MB004 ), CAN_TB_u4MB_RXKIND( 2, 004 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB004, CAN_CFG_ID_VALUE_2_MB004 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB005, CAN_TB_u4MB_RXLABEL( CAN_MB005 ), CAN_TB_u4MB_RXKIND( 2, 005 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB005, CAN_CFG_ID_VALUE_2_MB005 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB006, CAN_TB_u4MB_RXLABEL( CAN_MB006 ), CAN_TB_u4MB_RXKIND( 2, 006 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB006, CAN_CFG_ID_VALUE_2_MB006 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB007, CAN_TB_u4MB_RXLABEL( CAN_MB007 ), CAN_TB_u4MB_RXKIND( 2, 007 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB007, CAN_CFG_ID_VALUE_2_MB007 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB008, CAN_TB_u4MB_RXLABEL( CAN_MB008 ), CAN_TB_u4MB_RXKIND( 2, 008 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB008, CAN_CFG_ID_VALUE_2_MB008 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB009, CAN_TB_u4MB_RXLABEL( CAN_MB009 ), CAN_TB_u4MB_RXKIND( 2, 009 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB009, CAN_CFG_ID_VALUE_2_MB009 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB010, CAN_TB_u4MB_RXLABEL( CAN_MB010 ), CAN_TB_u4MB_RXKIND( 2, 010 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB010, CAN_CFG_ID_VALUE_2_MB010 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB011, CAN_TB_u4MB_RXLABEL( CAN_MB011 ), CAN_TB_u4MB_RXKIND( 2, 011 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB011, CAN_CFG_ID_VALUE_2_MB011 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB012, CAN_TB_u4MB_RXLABEL( CAN_MB012 ), CAN_TB_u4MB_RXKIND( 2, 012 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB012, CAN_CFG_ID_VALUE_2_MB012 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB013, CAN_TB_u4MB_RXLABEL( CAN_MB013 ), CAN_TB_u4MB_RXKIND( 2, 013 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB013, CAN_CFG_ID_VALUE_2_MB013 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB014, CAN_TB_u4MB_RXLABEL( CAN_MB014 ), CAN_TB_u4MB_RXKIND( 2, 014 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB014, CAN_CFG_ID_VALUE_2_MB014 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB015, CAN_TB_u4MB_RXLABEL( CAN_MB015 ), CAN_TB_u4MB_RXKIND( 2, 015 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB015, CAN_CFG_ID_VALUE_2_MB015 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB016, CAN_TB_u4MB_RXLABEL( CAN_MB016 ), CAN_TB_u4MB_RXKIND( 2, 016 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB016, CAN_CFG_ID_VALUE_2_MB016 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB017, CAN_TB_u4MB_RXLABEL( CAN_MB017 ), CAN_TB_u4MB_RXKIND( 2, 017 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB017, CAN_CFG_ID_VALUE_2_MB017 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB018, CAN_TB_u4MB_RXLABEL( CAN_MB018 ), CAN_TB_u4MB_RXKIND( 2, 018 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB018, CAN_CFG_ID_VALUE_2_MB018 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB019, CAN_TB_u4MB_RXLABEL( CAN_MB019 ), CAN_TB_u4MB_RXKIND( 2, 019 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB019, CAN_CFG_ID_VALUE_2_MB019 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB020, CAN_TB_u4MB_RXLABEL( CAN_MB020 ), CAN_TB_u4MB_RXKIND( 2, 020 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB020, CAN_CFG_ID_VALUE_2_MB020 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB021, CAN_TB_u4MB_RXLABEL( CAN_MB021 ), CAN_TB_u4MB_RXKIND( 2, 021 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB021, CAN_CFG_ID_VALUE_2_MB021 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB022, CAN_TB_u4MB_RXLABEL( CAN_MB022 ), CAN_TB_u4MB_RXKIND( 2, 022 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB022, CAN_CFG_ID_VALUE_2_MB022 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB023, CAN_TB_u4MB_RXLABEL( CAN_MB023 ), CAN_TB_u4MB_RXKIND( 2, 023 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB023, CAN_CFG_ID_VALUE_2_MB023 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB024, CAN_TB_u4MB_RXLABEL( CAN_MB024 ), CAN_TB_u4MB_RXKIND( 2, 024 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB024, CAN_CFG_ID_VALUE_2_MB024 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB025, CAN_TB_u4MB_RXLABEL( CAN_MB025 ), CAN_TB_u4MB_RXKIND( 2, 025 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB025, CAN_CFG_ID_VALUE_2_MB025 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB026, CAN_TB_u4MB_RXLABEL( CAN_MB026 ), CAN_TB_u4MB_RXKIND( 2, 026 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB026, CAN_CFG_ID_VALUE_2_MB026 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB027, CAN_TB_u4MB_RXLABEL( CAN_MB027 ), CAN_TB_u4MB_RXKIND( 2, 027 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB027, CAN_CFG_ID_VALUE_2_MB027 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB028, CAN_TB_u4MB_RXLABEL( CAN_MB028 ), CAN_TB_u4MB_RXKIND( 2, 028 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB028, CAN_CFG_ID_VALUE_2_MB028 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB029, CAN_TB_u4MB_RXLABEL( CAN_MB029 ), CAN_TB_u4MB_RXKIND( 2, 029 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB029, CAN_CFG_ID_VALUE_2_MB029 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB030, CAN_TB_u4MB_RXLABEL( CAN_MB030 ), CAN_TB_u4MB_RXKIND( 2, 030 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB030, CAN_CFG_ID_VALUE_2_MB030 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB031, CAN_TB_u4MB_RXLABEL( CAN_MB031 ), CAN_TB_u4MB_RXKIND( 2, 031 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB031, CAN_CFG_ID_VALUE_2_MB031 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB032, CAN_TB_u4MB_RXLABEL( CAN_MB032 ), CAN_TB_u4MB_RXKIND( 2, 032 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB032, CAN_CFG_ID_VALUE_2_MB032 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB033, CAN_TB_u4MB_RXLABEL( CAN_MB033 ), CAN_TB_u4MB_RXKIND( 2, 033 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB033, CAN_CFG_ID_VALUE_2_MB033 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB034, CAN_TB_u4MB_RXLABEL( CAN_MB034 ), CAN_TB_u4MB_RXKIND( 2, 034 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB034, CAN_CFG_ID_VALUE_2_MB034 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB035, CAN_TB_u4MB_RXLABEL( CAN_MB035 ), CAN_TB_u4MB_RXKIND( 2, 035 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB035, CAN_CFG_ID_VALUE_2_MB035 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB036, CAN_TB_u4MB_RXLABEL( CAN_MB036 ), CAN_TB_u4MB_RXKIND( 2, 036 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB036, CAN_CFG_ID_VALUE_2_MB036 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB037, CAN_TB_u4MB_RXLABEL( CAN_MB037 ), CAN_TB_u4MB_RXKIND( 2, 037 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB037, CAN_CFG_ID_VALUE_2_MB037 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB038, CAN_TB_u4MB_RXLABEL( CAN_MB038 ), CAN_TB_u4MB_RXKIND( 2, 038 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB038, CAN_CFG_ID_VALUE_2_MB038 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB039, CAN_TB_u4MB_RXLABEL( CAN_MB039 ), CAN_TB_u4MB_RXKIND( 2, 039 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB039, CAN_CFG_ID_VALUE_2_MB039 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB040, CAN_TB_u4MB_RXLABEL( CAN_MB040 ), CAN_TB_u4MB_RXKIND( 2, 040 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB040, CAN_CFG_ID_VALUE_2_MB040 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB041, CAN_TB_u4MB_RXLABEL( CAN_MB041 ), CAN_TB_u4MB_RXKIND( 2, 041 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB041, CAN_CFG_ID_VALUE_2_MB041 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB042, CAN_TB_u4MB_RXLABEL( CAN_MB042 ), CAN_TB_u4MB_RXKIND( 2, 042 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB042, CAN_CFG_ID_VALUE_2_MB042 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB043, CAN_TB_u4MB_RXLABEL( CAN_MB043 ), CAN_TB_u4MB_RXKIND( 2, 043 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB043, CAN_CFG_ID_VALUE_2_MB043 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB044, CAN_TB_u4MB_RXLABEL( CAN_MB044 ), CAN_TB_u4MB_RXKIND( 2, 044 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB044, CAN_CFG_ID_VALUE_2_MB044 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB045, CAN_TB_u4MB_RXLABEL( CAN_MB045 ), CAN_TB_u4MB_RXKIND( 2, 045 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB045, CAN_CFG_ID_VALUE_2_MB045 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB046, CAN_TB_u4MB_RXLABEL( CAN_MB046 ), CAN_TB_u4MB_RXKIND( 2, 046 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB046, CAN_CFG_ID_VALUE_2_MB046 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB047, CAN_TB_u4MB_RXLABEL( CAN_MB047 ), CAN_TB_u4MB_RXKIND( 2, 047 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB047, CAN_CFG_ID_VALUE_2_MB047 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB048, CAN_TB_u4MB_RXLABEL( CAN_MB048 ), CAN_TB_u4MB_RXKIND( 2, 048 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB048, CAN_CFG_ID_VALUE_2_MB048 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB049, CAN_TB_u4MB_RXLABEL( CAN_MB049 ), CAN_TB_u4MB_RXKIND( 2, 049 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB049, CAN_CFG_ID_VALUE_2_MB049 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB050, CAN_TB_u4MB_RXLABEL( CAN_MB050 ), CAN_TB_u4MB_RXKIND( 2, 050 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB050, CAN_CFG_ID_VALUE_2_MB050 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB051, CAN_TB_u4MB_RXLABEL( CAN_MB051 ), CAN_TB_u4MB_RXKIND( 2, 051 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB051, CAN_CFG_ID_VALUE_2_MB051 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB052, CAN_TB_u4MB_RXLABEL( CAN_MB052 ), CAN_TB_u4MB_RXKIND( 2, 052 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB052, CAN_CFG_ID_VALUE_2_MB052 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB053, CAN_TB_u4MB_RXLABEL( CAN_MB053 ), CAN_TB_u4MB_RXKIND( 2, 053 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB053, CAN_CFG_ID_VALUE_2_MB053 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB054, CAN_TB_u4MB_RXLABEL( CAN_MB054 ), CAN_TB_u4MB_RXKIND( 2, 054 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB054, CAN_CFG_ID_VALUE_2_MB054 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB055, CAN_TB_u4MB_RXLABEL( CAN_MB055 ), CAN_TB_u4MB_RXKIND( 2, 055 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB055, CAN_CFG_ID_VALUE_2_MB055 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB056, CAN_TB_u4MB_RXLABEL( CAN_MB056 ), CAN_TB_u4MB_RXKIND( 2, 056 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB056, CAN_CFG_ID_VALUE_2_MB056 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB057, CAN_TB_u4MB_RXLABEL( CAN_MB057 ), CAN_TB_u4MB_RXKIND( 2, 057 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB057, CAN_CFG_ID_VALUE_2_MB057 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB058, CAN_TB_u4MB_RXLABEL( CAN_MB058 ), CAN_TB_u4MB_RXKIND( 2, 058 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB058, CAN_CFG_ID_VALUE_2_MB058 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB059, CAN_TB_u4MB_RXLABEL( CAN_MB059 ), CAN_TB_u4MB_RXKIND( 2, 059 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB059, CAN_CFG_ID_VALUE_2_MB059 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB060, CAN_TB_u4MB_RXLABEL( CAN_MB060 ), CAN_TB_u4MB_RXKIND( 2, 060 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB060, CAN_CFG_ID_VALUE_2_MB060 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB061, CAN_TB_u4MB_RXLABEL( CAN_MB061 ), CAN_TB_u4MB_RXKIND( 2, 061 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB061, CAN_CFG_ID_VALUE_2_MB061 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB062, CAN_TB_u4MB_RXLABEL( CAN_MB062 ), CAN_TB_u4MB_RXKIND( 2, 062 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB062, CAN_CFG_ID_VALUE_2_MB062 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB063, CAN_TB_u4MB_RXLABEL( CAN_MB063 ), CAN_TB_u4MB_RXKIND( 2, 063 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB063, CAN_CFG_ID_VALUE_2_MB063 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB064, CAN_TB_u4MB_RXLABEL( CAN_MB064 ), CAN_TB_u4MB_RXKIND( 2, 064 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB064, CAN_CFG_ID_VALUE_2_MB064 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB065, CAN_TB_u4MB_RXLABEL( CAN_MB065 ), CAN_TB_u4MB_RXKIND( 2, 065 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB065, CAN_CFG_ID_VALUE_2_MB065 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB066, CAN_TB_u4MB_RXLABEL( CAN_MB066 ), CAN_TB_u4MB_RXKIND( 2, 066 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB066, CAN_CFG_ID_VALUE_2_MB066 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB067, CAN_TB_u4MB_RXLABEL( CAN_MB067 ), CAN_TB_u4MB_RXKIND( 2, 067 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB067, CAN_CFG_ID_VALUE_2_MB067 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB068, CAN_TB_u4MB_RXLABEL( CAN_MB068 ), CAN_TB_u4MB_RXKIND( 2, 068 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB068, CAN_CFG_ID_VALUE_2_MB068 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB069, CAN_TB_u4MB_RXLABEL( CAN_MB069 ), CAN_TB_u4MB_RXKIND( 2, 069 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB069, CAN_CFG_ID_VALUE_2_MB069 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB070, CAN_TB_u4MB_RXLABEL( CAN_MB070 ), CAN_TB_u4MB_RXKIND( 2, 070 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB070, CAN_CFG_ID_VALUE_2_MB070 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB071, CAN_TB_u4MB_RXLABEL( CAN_MB071 ), CAN_TB_u4MB_RXKIND( 2, 071 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB071, CAN_CFG_ID_VALUE_2_MB071 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB072, CAN_TB_u4MB_RXLABEL( CAN_MB072 ), CAN_TB_u4MB_RXKIND( 2, 072 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB072, CAN_CFG_ID_VALUE_2_MB072 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB073, CAN_TB_u4MB_RXLABEL( CAN_MB073 ), CAN_TB_u4MB_RXKIND( 2, 073 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB073, CAN_CFG_ID_VALUE_2_MB073 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB074, CAN_TB_u4MB_RXLABEL( CAN_MB074 ), CAN_TB_u4MB_RXKIND( 2, 074 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB074, CAN_CFG_ID_VALUE_2_MB074 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB075, CAN_TB_u4MB_RXLABEL( CAN_MB075 ), CAN_TB_u4MB_RXKIND( 2, 075 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB075, CAN_CFG_ID_VALUE_2_MB075 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB076, CAN_TB_u4MB_RXLABEL( CAN_MB076 ), CAN_TB_u4MB_RXKIND( 2, 076 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB076, CAN_CFG_ID_VALUE_2_MB076 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB077, CAN_TB_u4MB_RXLABEL( CAN_MB077 ), CAN_TB_u4MB_RXKIND( 2, 077 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB077, CAN_CFG_ID_VALUE_2_MB077 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB078, CAN_TB_u4MB_RXLABEL( CAN_MB078 ), CAN_TB_u4MB_RXKIND( 2, 078 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB078, CAN_CFG_ID_VALUE_2_MB078 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB079, CAN_TB_u4MB_RXLABEL( CAN_MB079 ), CAN_TB_u4MB_RXKIND( 2, 079 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB079, CAN_CFG_ID_VALUE_2_MB079 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB080, CAN_TB_u4MB_RXLABEL( CAN_MB080 ), CAN_TB_u4MB_RXKIND( 2, 080 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB080, CAN_CFG_ID_VALUE_2_MB080 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB081, CAN_TB_u4MB_RXLABEL( CAN_MB081 ), CAN_TB_u4MB_RXKIND( 2, 081 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB081, CAN_CFG_ID_VALUE_2_MB081 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB082, CAN_TB_u4MB_RXLABEL( CAN_MB082 ), CAN_TB_u4MB_RXKIND( 2, 082 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB082, CAN_CFG_ID_VALUE_2_MB082 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB083, CAN_TB_u4MB_RXLABEL( CAN_MB083 ), CAN_TB_u4MB_RXKIND( 2, 083 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB083, CAN_CFG_ID_VALUE_2_MB083 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB084, CAN_TB_u4MB_RXLABEL( CAN_MB084 ), CAN_TB_u4MB_RXKIND( 2, 084 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB084, CAN_CFG_ID_VALUE_2_MB084 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB085, CAN_TB_u4MB_RXLABEL( CAN_MB085 ), CAN_TB_u4MB_RXKIND( 2, 085 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB085, CAN_CFG_ID_VALUE_2_MB085 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB086, CAN_TB_u4MB_RXLABEL( CAN_MB086 ), CAN_TB_u4MB_RXKIND( 2, 086 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB086, CAN_CFG_ID_VALUE_2_MB086 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB087, CAN_TB_u4MB_RXLABEL( CAN_MB087 ), CAN_TB_u4MB_RXKIND( 2, 087 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB087, CAN_CFG_ID_VALUE_2_MB087 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB088, CAN_TB_u4MB_RXLABEL( CAN_MB088 ), CAN_TB_u4MB_RXKIND( 2, 088 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB088, CAN_CFG_ID_VALUE_2_MB088 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB089, CAN_TB_u4MB_RXLABEL( CAN_MB089 ), CAN_TB_u4MB_RXKIND( 2, 089 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB089, CAN_CFG_ID_VALUE_2_MB089 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB090, CAN_TB_u4MB_RXLABEL( CAN_MB090 ), CAN_TB_u4MB_RXKIND( 2, 090 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB090, CAN_CFG_ID_VALUE_2_MB090 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB091, CAN_TB_u4MB_RXLABEL( CAN_MB091 ), CAN_TB_u4MB_RXKIND( 2, 091 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB091, CAN_CFG_ID_VALUE_2_MB091 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB092, CAN_TB_u4MB_RXLABEL( CAN_MB092 ), CAN_TB_u4MB_RXKIND( 2, 092 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB092, CAN_CFG_ID_VALUE_2_MB092 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB093, CAN_TB_u4MB_RXLABEL( CAN_MB093 ), CAN_TB_u4MB_RXKIND( 2, 093 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB093, CAN_CFG_ID_VALUE_2_MB093 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB094, CAN_TB_u4MB_RXLABEL( CAN_MB094 ), CAN_TB_u4MB_RXKIND( 2, 094 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB094, CAN_CFG_ID_VALUE_2_MB094 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB095, CAN_TB_u4MB_RXLABEL( CAN_MB095 ), CAN_TB_u4MB_RXKIND( 2, 095 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB095, CAN_CFG_ID_VALUE_2_MB095 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB096, CAN_TB_u4MB_RXLABEL( CAN_MB096 ), CAN_TB_u4MB_RXKIND( 2, 096 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB096, CAN_CFG_ID_VALUE_2_MB096 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB097, CAN_TB_u4MB_RXLABEL( CAN_MB097 ), CAN_TB_u4MB_RXKIND( 2, 097 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB097, CAN_CFG_ID_VALUE_2_MB097 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB098, CAN_TB_u4MB_RXLABEL( CAN_MB098 ), CAN_TB_u4MB_RXKIND( 2, 098 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB098, CAN_CFG_ID_VALUE_2_MB098 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB099, CAN_TB_u4MB_RXLABEL( CAN_MB099 ), CAN_TB_u4MB_RXKIND( 2, 099 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB099, CAN_CFG_ID_VALUE_2_MB099 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB100, CAN_TB_u4MB_RXLABEL( CAN_MB100 ), CAN_TB_u4MB_RXKIND( 2, 100 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB100, CAN_CFG_ID_VALUE_2_MB100 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB101, CAN_TB_u4MB_RXLABEL( CAN_MB101 ), CAN_TB_u4MB_RXKIND( 2, 101 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB101, CAN_CFG_ID_VALUE_2_MB101 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB102, CAN_TB_u4MB_RXLABEL( CAN_MB102 ), CAN_TB_u4MB_RXKIND( 2, 102 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB102, CAN_CFG_ID_VALUE_2_MB102 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB103, CAN_TB_u4MB_RXLABEL( CAN_MB103 ), CAN_TB_u4MB_RXKIND( 2, 103 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB103, CAN_CFG_ID_VALUE_2_MB103 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB104, CAN_TB_u4MB_RXLABEL( CAN_MB104 ), CAN_TB_u4MB_RXKIND( 2, 104 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB104, CAN_CFG_ID_VALUE_2_MB104 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB105, CAN_TB_u4MB_RXLABEL( CAN_MB105 ), CAN_TB_u4MB_RXKIND( 2, 105 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB105, CAN_CFG_ID_VALUE_2_MB105 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB106, CAN_TB_u4MB_RXLABEL( CAN_MB106 ), CAN_TB_u4MB_RXKIND( 2, 106 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB106, CAN_CFG_ID_VALUE_2_MB106 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB107, CAN_TB_u4MB_RXLABEL( CAN_MB107 ), CAN_TB_u4MB_RXKIND( 2, 107 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB107, CAN_CFG_ID_VALUE_2_MB107 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB108, CAN_TB_u4MB_RXLABEL( CAN_MB108 ), CAN_TB_u4MB_RXKIND( 2, 108 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB108, CAN_CFG_ID_VALUE_2_MB108 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB109, CAN_TB_u4MB_RXLABEL( CAN_MB109 ), CAN_TB_u4MB_RXKIND( 2, 109 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB109, CAN_CFG_ID_VALUE_2_MB109 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB110, CAN_TB_u4MB_RXLABEL( CAN_MB110 ), CAN_TB_u4MB_RXKIND( 2, 110 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB110, CAN_CFG_ID_VALUE_2_MB110 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB111, CAN_TB_u4MB_RXLABEL( CAN_MB111 ), CAN_TB_u4MB_RXKIND( 2, 111 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB111, CAN_CFG_ID_VALUE_2_MB111 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB112, CAN_TB_u4MB_RXLABEL( CAN_MB112 ), CAN_TB_u4MB_RXKIND( 2, 112 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB112, CAN_CFG_ID_VALUE_2_MB112 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB113, CAN_TB_u4MB_RXLABEL( CAN_MB113 ), CAN_TB_u4MB_RXKIND( 2, 113 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB113, CAN_CFG_ID_VALUE_2_MB113 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB114, CAN_TB_u4MB_RXLABEL( CAN_MB114 ), CAN_TB_u4MB_RXKIND( 2, 114 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB114, CAN_CFG_ID_VALUE_2_MB114 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB115, CAN_TB_u4MB_RXLABEL( CAN_MB115 ), CAN_TB_u4MB_RXKIND( 2, 115 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB115, CAN_CFG_ID_VALUE_2_MB115 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB116, CAN_TB_u4MB_RXLABEL( CAN_MB116 ), CAN_TB_u4MB_RXKIND( 2, 116 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB116, CAN_CFG_ID_VALUE_2_MB116 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB117, CAN_TB_u4MB_RXLABEL( CAN_MB117 ), CAN_TB_u4MB_RXKIND( 2, 117 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB117, CAN_CFG_ID_VALUE_2_MB117 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB118, CAN_TB_u4MB_RXLABEL( CAN_MB118 ), CAN_TB_u4MB_RXKIND( 2, 118 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB118, CAN_CFG_ID_VALUE_2_MB118 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB119, CAN_TB_u4MB_RXLABEL( CAN_MB119 ), CAN_TB_u4MB_RXKIND( 2, 119 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB119, CAN_CFG_ID_VALUE_2_MB119 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB120, CAN_TB_u4MB_RXLABEL( CAN_MB120 ), CAN_TB_u4MB_RXKIND( 2, 120 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB120, CAN_CFG_ID_VALUE_2_MB120 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB121, CAN_TB_u4MB_RXLABEL( CAN_MB121 ), CAN_TB_u4MB_RXKIND( 2, 121 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB121, CAN_CFG_ID_VALUE_2_MB121 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB122, CAN_TB_u4MB_RXLABEL( CAN_MB122 ), CAN_TB_u4MB_RXKIND( 2, 122 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB122, CAN_CFG_ID_VALUE_2_MB122 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB123, CAN_TB_u4MB_RXLABEL( CAN_MB123 ), CAN_TB_u4MB_RXKIND( 2, 123 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB123, CAN_CFG_ID_VALUE_2_MB123 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB124, CAN_TB_u4MB_RXLABEL( CAN_MB124 ), CAN_TB_u4MB_RXKIND( 2, 124 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB124, CAN_CFG_ID_VALUE_2_MB124 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB125, CAN_TB_u4MB_RXLABEL( CAN_MB125 ), CAN_TB_u4MB_RXKIND( 2, 125 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB125, CAN_CFG_ID_VALUE_2_MB125 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB126, CAN_TB_u4MB_RXLABEL( CAN_MB126 ), CAN_TB_u4MB_RXKIND( 2, 126 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB126, CAN_CFG_ID_VALUE_2_MB126 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB127, CAN_TB_u4MB_RXLABEL( CAN_MB127 ), CAN_TB_u4MB_RXKIND( 2, 127 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB127, CAN_CFG_ID_VALUE_2_MB127 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB128, CAN_TB_u4MB_RXLABEL( CAN_MB128 ), CAN_TB_u4MB_RXKIND( 2, 128 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB128, CAN_CFG_ID_VALUE_2_MB128 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB129, CAN_TB_u4MB_RXLABEL( CAN_MB129 ), CAN_TB_u4MB_RXKIND( 2, 129 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB129, CAN_CFG_ID_VALUE_2_MB129 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB130, CAN_TB_u4MB_RXLABEL( CAN_MB130 ), CAN_TB_u4MB_RXKIND( 2, 130 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB130, CAN_CFG_ID_VALUE_2_MB130 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB131, CAN_TB_u4MB_RXLABEL( CAN_MB131 ), CAN_TB_u4MB_RXKIND( 2, 131 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB131, CAN_CFG_ID_VALUE_2_MB131 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB132, CAN_TB_u4MB_RXLABEL( CAN_MB132 ), CAN_TB_u4MB_RXKIND( 2, 132 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB132, CAN_CFG_ID_VALUE_2_MB132 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB133, CAN_TB_u4MB_RXLABEL( CAN_MB133 ), CAN_TB_u4MB_RXKIND( 2, 133 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB133, CAN_CFG_ID_VALUE_2_MB133 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB134, CAN_TB_u4MB_RXLABEL( CAN_MB134 ), CAN_TB_u4MB_RXKIND( 2, 134 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB134, CAN_CFG_ID_VALUE_2_MB134 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB135, CAN_TB_u4MB_RXLABEL( CAN_MB135 ), CAN_TB_u4MB_RXKIND( 2, 135 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB135, CAN_CFG_ID_VALUE_2_MB135 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB136, CAN_TB_u4MB_RXLABEL( CAN_MB136 ), CAN_TB_u4MB_RXKIND( 2, 136 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB136, CAN_CFG_ID_VALUE_2_MB136 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB137, CAN_TB_u4MB_RXLABEL( CAN_MB137 ), CAN_TB_u4MB_RXKIND( 2, 137 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB137, CAN_CFG_ID_VALUE_2_MB137 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB138, CAN_TB_u4MB_RXLABEL( CAN_MB138 ), CAN_TB_u4MB_RXKIND( 2, 138 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB138, CAN_CFG_ID_VALUE_2_MB138 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB139, CAN_TB_u4MB_RXLABEL( CAN_MB139 ), CAN_TB_u4MB_RXKIND( 2, 139 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB139, CAN_CFG_ID_VALUE_2_MB139 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB140, CAN_TB_u4MB_RXLABEL( CAN_MB140 ), CAN_TB_u4MB_RXKIND( 2, 140 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB140, CAN_CFG_ID_VALUE_2_MB140 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB141, CAN_TB_u4MB_RXLABEL( CAN_MB141 ), CAN_TB_u4MB_RXKIND( 2, 141 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB141, CAN_CFG_ID_VALUE_2_MB141 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB142, CAN_TB_u4MB_RXLABEL( CAN_MB142 ), CAN_TB_u4MB_RXKIND( 2, 142 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB142, CAN_CFG_ID_VALUE_2_MB142 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB143, CAN_TB_u4MB_RXLABEL( CAN_MB143 ), CAN_TB_u4MB_RXKIND( 2, 143 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB143, CAN_CFG_ID_VALUE_2_MB143 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB144, CAN_TB_u4MB_RXLABEL( CAN_MB144 ), CAN_TB_u4MB_RXKIND( 2, 144 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB144, CAN_CFG_ID_VALUE_2_MB144 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB145, CAN_TB_u4MB_RXLABEL( CAN_MB145 ), CAN_TB_u4MB_RXKIND( 2, 145 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB145, CAN_CFG_ID_VALUE_2_MB145 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB146, CAN_TB_u4MB_RXLABEL( CAN_MB146 ), CAN_TB_u4MB_RXKIND( 2, 146 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB146, CAN_CFG_ID_VALUE_2_MB146 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB147, CAN_TB_u4MB_RXLABEL( CAN_MB147 ), CAN_TB_u4MB_RXKIND( 2, 147 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB147, CAN_CFG_ID_VALUE_2_MB147 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB148, CAN_TB_u4MB_RXLABEL( CAN_MB148 ), CAN_TB_u4MB_RXKIND( 2, 148 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB148, CAN_CFG_ID_VALUE_2_MB148 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB149, CAN_TB_u4MB_RXLABEL( CAN_MB149 ), CAN_TB_u4MB_RXKIND( 2, 149 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB149, CAN_CFG_ID_VALUE_2_MB149 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB150, CAN_TB_u4MB_RXLABEL( CAN_MB150 ), CAN_TB_u4MB_RXKIND( 2, 150 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB150, CAN_CFG_ID_VALUE_2_MB150 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB151, CAN_TB_u4MB_RXLABEL( CAN_MB151 ), CAN_TB_u4MB_RXKIND( 2, 151 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB151, CAN_CFG_ID_VALUE_2_MB151 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB152, CAN_TB_u4MB_RXLABEL( CAN_MB152 ), CAN_TB_u4MB_RXKIND( 2, 152 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB152, CAN_CFG_ID_VALUE_2_MB152 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB153, CAN_TB_u4MB_RXLABEL( CAN_MB153 ), CAN_TB_u4MB_RXKIND( 2, 153 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB153, CAN_CFG_ID_VALUE_2_MB153 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB154, CAN_TB_u4MB_RXLABEL( CAN_MB154 ), CAN_TB_u4MB_RXKIND( 2, 154 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB154, CAN_CFG_ID_VALUE_2_MB154 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB155, CAN_TB_u4MB_RXLABEL( CAN_MB155 ), CAN_TB_u4MB_RXKIND( 2, 155 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB155, CAN_CFG_ID_VALUE_2_MB155 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB156, CAN_TB_u4MB_RXLABEL( CAN_MB156 ), CAN_TB_u4MB_RXKIND( 2, 156 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB156, CAN_CFG_ID_VALUE_2_MB156 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB157, CAN_TB_u4MB_RXLABEL( CAN_MB157 ), CAN_TB_u4MB_RXKIND( 2, 157 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB157, CAN_CFG_ID_VALUE_2_MB157 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB158, CAN_TB_u4MB_RXLABEL( CAN_MB158 ), CAN_TB_u4MB_RXKIND( 2, 158 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB158, CAN_CFG_ID_VALUE_2_MB158 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB159, CAN_TB_u4MB_RXLABEL( CAN_MB159 ), CAN_TB_u4MB_RXKIND( 2, 159 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB159, CAN_CFG_ID_VALUE_2_MB159 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB160, CAN_TB_u4MB_RXLABEL( CAN_MB160 ), CAN_TB_u4MB_RXKIND( 2, 160 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB160, CAN_CFG_ID_VALUE_2_MB160 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB161, CAN_TB_u4MB_RXLABEL( CAN_MB161 ), CAN_TB_u4MB_RXKIND( 2, 161 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB161, CAN_CFG_ID_VALUE_2_MB161 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB162, CAN_TB_u4MB_RXLABEL( CAN_MB162 ), CAN_TB_u4MB_RXKIND( 2, 162 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB162, CAN_CFG_ID_VALUE_2_MB162 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB163, CAN_TB_u4MB_RXLABEL( CAN_MB163 ), CAN_TB_u4MB_RXKIND( 2, 163 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB163, CAN_CFG_ID_VALUE_2_MB163 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB164, CAN_TB_u4MB_RXLABEL( CAN_MB164 ), CAN_TB_u4MB_RXKIND( 2, 164 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB164, CAN_CFG_ID_VALUE_2_MB164 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB165, CAN_TB_u4MB_RXLABEL( CAN_MB165 ), CAN_TB_u4MB_RXKIND( 2, 165 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB165, CAN_CFG_ID_VALUE_2_MB165 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB166, CAN_TB_u4MB_RXLABEL( CAN_MB166 ), CAN_TB_u4MB_RXKIND( 2, 166 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB166, CAN_CFG_ID_VALUE_2_MB166 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB167, CAN_TB_u4MB_RXLABEL( CAN_MB167 ), CAN_TB_u4MB_RXKIND( 2, 167 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB167, CAN_CFG_ID_VALUE_2_MB167 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB168, CAN_TB_u4MB_RXLABEL( CAN_MB168 ), CAN_TB_u4MB_RXKIND( 2, 168 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB168, CAN_CFG_ID_VALUE_2_MB168 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB169, CAN_TB_u4MB_RXLABEL( CAN_MB169 ), CAN_TB_u4MB_RXKIND( 2, 169 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB169, CAN_CFG_ID_VALUE_2_MB169 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB170, CAN_TB_u4MB_RXLABEL( CAN_MB170 ), CAN_TB_u4MB_RXKIND( 2, 170 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB170, CAN_CFG_ID_VALUE_2_MB170 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB171, CAN_TB_u4MB_RXLABEL( CAN_MB171 ), CAN_TB_u4MB_RXKIND( 2, 171 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB171, CAN_CFG_ID_VALUE_2_MB171 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB172, CAN_TB_u4MB_RXLABEL( CAN_MB172 ), CAN_TB_u4MB_RXKIND( 2, 172 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB172, CAN_CFG_ID_VALUE_2_MB172 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB173, CAN_TB_u4MB_RXLABEL( CAN_MB173 ), CAN_TB_u4MB_RXKIND( 2, 173 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB173, CAN_CFG_ID_VALUE_2_MB173 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB174, CAN_TB_u4MB_RXLABEL( CAN_MB174 ), CAN_TB_u4MB_RXKIND( 2, 174 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB174, CAN_CFG_ID_VALUE_2_MB174 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB175, CAN_TB_u4MB_RXLABEL( CAN_MB175 ), CAN_TB_u4MB_RXKIND( 2, 175 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB175, CAN_CFG_ID_VALUE_2_MB175 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB176, CAN_TB_u4MB_RXLABEL( CAN_MB176 ), CAN_TB_u4MB_RXKIND( 2, 176 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB176, CAN_CFG_ID_VALUE_2_MB176 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB177, CAN_TB_u4MB_RXLABEL( CAN_MB177 ), CAN_TB_u4MB_RXKIND( 2, 177 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB177, CAN_CFG_ID_VALUE_2_MB177 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB178, CAN_TB_u4MB_RXLABEL( CAN_MB178 ), CAN_TB_u4MB_RXKIND( 2, 178 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB178, CAN_CFG_ID_VALUE_2_MB178 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB179, CAN_TB_u4MB_RXLABEL( CAN_MB179 ), CAN_TB_u4MB_RXKIND( 2, 179 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB179, CAN_CFG_ID_VALUE_2_MB179 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB180, CAN_TB_u4MB_RXLABEL( CAN_MB180 ), CAN_TB_u4MB_RXKIND( 2, 180 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB180, CAN_CFG_ID_VALUE_2_MB180 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB181, CAN_TB_u4MB_RXLABEL( CAN_MB181 ), CAN_TB_u4MB_RXKIND( 2, 181 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB181, CAN_CFG_ID_VALUE_2_MB181 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB182, CAN_TB_u4MB_RXLABEL( CAN_MB182 ), CAN_TB_u4MB_RXKIND( 2, 182 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB182, CAN_CFG_ID_VALUE_2_MB182 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB183, CAN_TB_u4MB_RXLABEL( CAN_MB183 ), CAN_TB_u4MB_RXKIND( 2, 183 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB183, CAN_CFG_ID_VALUE_2_MB183 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB184, CAN_TB_u4MB_RXLABEL( CAN_MB184 ), CAN_TB_u4MB_RXKIND( 2, 184 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB184, CAN_CFG_ID_VALUE_2_MB184 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB185, CAN_TB_u4MB_RXLABEL( CAN_MB185 ), CAN_TB_u4MB_RXKIND( 2, 185 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB185, CAN_CFG_ID_VALUE_2_MB185 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB186, CAN_TB_u4MB_RXLABEL( CAN_MB186 ), CAN_TB_u4MB_RXKIND( 2, 186 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB186, CAN_CFG_ID_VALUE_2_MB186 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB187, CAN_TB_u4MB_RXLABEL( CAN_MB187 ), CAN_TB_u4MB_RXKIND( 2, 187 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB187, CAN_CFG_ID_VALUE_2_MB187 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB188, CAN_TB_u4MB_RXLABEL( CAN_MB188 ), CAN_TB_u4MB_RXKIND( 2, 188 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB188, CAN_CFG_ID_VALUE_2_MB188 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB189, CAN_TB_u4MB_RXLABEL( CAN_MB189 ), CAN_TB_u4MB_RXKIND( 2, 189 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB189, CAN_CFG_ID_VALUE_2_MB189 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB190, CAN_TB_u4MB_RXLABEL( CAN_MB190 ), CAN_TB_u4MB_RXKIND( 2, 190 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB190, CAN_CFG_ID_VALUE_2_MB190 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_2_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_2_MB191, CAN_TB_u4MB_RXLABEL( CAN_MB191 ), CAN_TB_u4MB_RXKIND( 2, 191 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_2_MB191, CAN_CFG_ID_VALUE_2_MB191 ) },
#endif /* ( (CAN_CFG_MBOXSET_2_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */

    /* Controller 3 */
#if ( (CAN_CFG_MBOXSET_3_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB000, CAN_TB_u4MB_RXLABEL( CAN_MB000 ), CAN_TB_u4MB_RXKIND( 3, 000 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB000, CAN_CFG_ID_VALUE_3_MB000 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB001, CAN_TB_u4MB_RXLABEL( CAN_MB001 ), CAN_TB_u4MB_RXKIND( 3, 001 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB001, CAN_CFG_ID_VALUE_3_MB001 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB002, CAN_TB_u4MB_RXLABEL( CAN_MB002 ), CAN_TB_u4MB_RXKIND( 3, 002 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB002, CAN_CFG_ID_VALUE_3_MB002 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB003, CAN_TB_u4MB_RXLABEL( CAN_MB003 ), CAN_TB_u4MB_RXKIND( 3, 003 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB003, CAN_CFG_ID_VALUE_3_MB003 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB004, CAN_TB_u4MB_RXLABEL( CAN_MB004 ), CAN_TB_u4MB_RXKIND( 3, 004 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB004, CAN_CFG_ID_VALUE_3_MB004 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB005, CAN_TB_u4MB_RXLABEL( CAN_MB005 ), CAN_TB_u4MB_RXKIND( 3, 005 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB005, CAN_CFG_ID_VALUE_3_MB005 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB006, CAN_TB_u4MB_RXLABEL( CAN_MB006 ), CAN_TB_u4MB_RXKIND( 3, 006 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB006, CAN_CFG_ID_VALUE_3_MB006 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB007, CAN_TB_u4MB_RXLABEL( CAN_MB007 ), CAN_TB_u4MB_RXKIND( 3, 007 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB007, CAN_CFG_ID_VALUE_3_MB007 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB008, CAN_TB_u4MB_RXLABEL( CAN_MB008 ), CAN_TB_u4MB_RXKIND( 3, 008 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB008, CAN_CFG_ID_VALUE_3_MB008 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB009, CAN_TB_u4MB_RXLABEL( CAN_MB009 ), CAN_TB_u4MB_RXKIND( 3, 009 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB009, CAN_CFG_ID_VALUE_3_MB009 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB010, CAN_TB_u4MB_RXLABEL( CAN_MB010 ), CAN_TB_u4MB_RXKIND( 3, 010 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB010, CAN_CFG_ID_VALUE_3_MB010 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB011, CAN_TB_u4MB_RXLABEL( CAN_MB011 ), CAN_TB_u4MB_RXKIND( 3, 011 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB011, CAN_CFG_ID_VALUE_3_MB011 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB012, CAN_TB_u4MB_RXLABEL( CAN_MB012 ), CAN_TB_u4MB_RXKIND( 3, 012 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB012, CAN_CFG_ID_VALUE_3_MB012 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB013, CAN_TB_u4MB_RXLABEL( CAN_MB013 ), CAN_TB_u4MB_RXKIND( 3, 013 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB013, CAN_CFG_ID_VALUE_3_MB013 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB014, CAN_TB_u4MB_RXLABEL( CAN_MB014 ), CAN_TB_u4MB_RXKIND( 3, 014 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB014, CAN_CFG_ID_VALUE_3_MB014 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB015, CAN_TB_u4MB_RXLABEL( CAN_MB015 ), CAN_TB_u4MB_RXKIND( 3, 015 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB015, CAN_CFG_ID_VALUE_3_MB015 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB016, CAN_TB_u4MB_RXLABEL( CAN_MB016 ), CAN_TB_u4MB_RXKIND( 3, 016 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB016, CAN_CFG_ID_VALUE_3_MB016 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB017, CAN_TB_u4MB_RXLABEL( CAN_MB017 ), CAN_TB_u4MB_RXKIND( 3, 017 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB017, CAN_CFG_ID_VALUE_3_MB017 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB018, CAN_TB_u4MB_RXLABEL( CAN_MB018 ), CAN_TB_u4MB_RXKIND( 3, 018 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB018, CAN_CFG_ID_VALUE_3_MB018 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB019, CAN_TB_u4MB_RXLABEL( CAN_MB019 ), CAN_TB_u4MB_RXKIND( 3, 019 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB019, CAN_CFG_ID_VALUE_3_MB019 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB020, CAN_TB_u4MB_RXLABEL( CAN_MB020 ), CAN_TB_u4MB_RXKIND( 3, 020 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB020, CAN_CFG_ID_VALUE_3_MB020 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB021, CAN_TB_u4MB_RXLABEL( CAN_MB021 ), CAN_TB_u4MB_RXKIND( 3, 021 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB021, CAN_CFG_ID_VALUE_3_MB021 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB022, CAN_TB_u4MB_RXLABEL( CAN_MB022 ), CAN_TB_u4MB_RXKIND( 3, 022 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB022, CAN_CFG_ID_VALUE_3_MB022 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB023, CAN_TB_u4MB_RXLABEL( CAN_MB023 ), CAN_TB_u4MB_RXKIND( 3, 023 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB023, CAN_CFG_ID_VALUE_3_MB023 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB024, CAN_TB_u4MB_RXLABEL( CAN_MB024 ), CAN_TB_u4MB_RXKIND( 3, 024 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB024, CAN_CFG_ID_VALUE_3_MB024 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB025, CAN_TB_u4MB_RXLABEL( CAN_MB025 ), CAN_TB_u4MB_RXKIND( 3, 025 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB025, CAN_CFG_ID_VALUE_3_MB025 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB026, CAN_TB_u4MB_RXLABEL( CAN_MB026 ), CAN_TB_u4MB_RXKIND( 3, 026 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB026, CAN_CFG_ID_VALUE_3_MB026 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB027, CAN_TB_u4MB_RXLABEL( CAN_MB027 ), CAN_TB_u4MB_RXKIND( 3, 027 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB027, CAN_CFG_ID_VALUE_3_MB027 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB028, CAN_TB_u4MB_RXLABEL( CAN_MB028 ), CAN_TB_u4MB_RXKIND( 3, 028 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB028, CAN_CFG_ID_VALUE_3_MB028 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB029, CAN_TB_u4MB_RXLABEL( CAN_MB029 ), CAN_TB_u4MB_RXKIND( 3, 029 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB029, CAN_CFG_ID_VALUE_3_MB029 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB030, CAN_TB_u4MB_RXLABEL( CAN_MB030 ), CAN_TB_u4MB_RXKIND( 3, 030 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB030, CAN_CFG_ID_VALUE_3_MB030 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB031, CAN_TB_u4MB_RXLABEL( CAN_MB031 ), CAN_TB_u4MB_RXKIND( 3, 031 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB031, CAN_CFG_ID_VALUE_3_MB031 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB032, CAN_TB_u4MB_RXLABEL( CAN_MB032 ), CAN_TB_u4MB_RXKIND( 3, 032 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB032, CAN_CFG_ID_VALUE_3_MB032 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB033, CAN_TB_u4MB_RXLABEL( CAN_MB033 ), CAN_TB_u4MB_RXKIND( 3, 033 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB033, CAN_CFG_ID_VALUE_3_MB033 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB034, CAN_TB_u4MB_RXLABEL( CAN_MB034 ), CAN_TB_u4MB_RXKIND( 3, 034 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB034, CAN_CFG_ID_VALUE_3_MB034 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB035, CAN_TB_u4MB_RXLABEL( CAN_MB035 ), CAN_TB_u4MB_RXKIND( 3, 035 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB035, CAN_CFG_ID_VALUE_3_MB035 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB036, CAN_TB_u4MB_RXLABEL( CAN_MB036 ), CAN_TB_u4MB_RXKIND( 3, 036 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB036, CAN_CFG_ID_VALUE_3_MB036 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB037, CAN_TB_u4MB_RXLABEL( CAN_MB037 ), CAN_TB_u4MB_RXKIND( 3, 037 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB037, CAN_CFG_ID_VALUE_3_MB037 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB038, CAN_TB_u4MB_RXLABEL( CAN_MB038 ), CAN_TB_u4MB_RXKIND( 3, 038 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB038, CAN_CFG_ID_VALUE_3_MB038 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB039, CAN_TB_u4MB_RXLABEL( CAN_MB039 ), CAN_TB_u4MB_RXKIND( 3, 039 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB039, CAN_CFG_ID_VALUE_3_MB039 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB040, CAN_TB_u4MB_RXLABEL( CAN_MB040 ), CAN_TB_u4MB_RXKIND( 3, 040 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB040, CAN_CFG_ID_VALUE_3_MB040 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB041, CAN_TB_u4MB_RXLABEL( CAN_MB041 ), CAN_TB_u4MB_RXKIND( 3, 041 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB041, CAN_CFG_ID_VALUE_3_MB041 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB042, CAN_TB_u4MB_RXLABEL( CAN_MB042 ), CAN_TB_u4MB_RXKIND( 3, 042 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB042, CAN_CFG_ID_VALUE_3_MB042 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB043, CAN_TB_u4MB_RXLABEL( CAN_MB043 ), CAN_TB_u4MB_RXKIND( 3, 043 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB043, CAN_CFG_ID_VALUE_3_MB043 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB044, CAN_TB_u4MB_RXLABEL( CAN_MB044 ), CAN_TB_u4MB_RXKIND( 3, 044 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB044, CAN_CFG_ID_VALUE_3_MB044 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB045, CAN_TB_u4MB_RXLABEL( CAN_MB045 ), CAN_TB_u4MB_RXKIND( 3, 045 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB045, CAN_CFG_ID_VALUE_3_MB045 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB046, CAN_TB_u4MB_RXLABEL( CAN_MB046 ), CAN_TB_u4MB_RXKIND( 3, 046 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB046, CAN_CFG_ID_VALUE_3_MB046 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB047, CAN_TB_u4MB_RXLABEL( CAN_MB047 ), CAN_TB_u4MB_RXKIND( 3, 047 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB047, CAN_CFG_ID_VALUE_3_MB047 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB048, CAN_TB_u4MB_RXLABEL( CAN_MB048 ), CAN_TB_u4MB_RXKIND( 3, 048 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB048, CAN_CFG_ID_VALUE_3_MB048 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB049, CAN_TB_u4MB_RXLABEL( CAN_MB049 ), CAN_TB_u4MB_RXKIND( 3, 049 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB049, CAN_CFG_ID_VALUE_3_MB049 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB050, CAN_TB_u4MB_RXLABEL( CAN_MB050 ), CAN_TB_u4MB_RXKIND( 3, 050 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB050, CAN_CFG_ID_VALUE_3_MB050 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB051, CAN_TB_u4MB_RXLABEL( CAN_MB051 ), CAN_TB_u4MB_RXKIND( 3, 051 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB051, CAN_CFG_ID_VALUE_3_MB051 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB052, CAN_TB_u4MB_RXLABEL( CAN_MB052 ), CAN_TB_u4MB_RXKIND( 3, 052 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB052, CAN_CFG_ID_VALUE_3_MB052 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB053, CAN_TB_u4MB_RXLABEL( CAN_MB053 ), CAN_TB_u4MB_RXKIND( 3, 053 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB053, CAN_CFG_ID_VALUE_3_MB053 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB054, CAN_TB_u4MB_RXLABEL( CAN_MB054 ), CAN_TB_u4MB_RXKIND( 3, 054 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB054, CAN_CFG_ID_VALUE_3_MB054 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB055, CAN_TB_u4MB_RXLABEL( CAN_MB055 ), CAN_TB_u4MB_RXKIND( 3, 055 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB055, CAN_CFG_ID_VALUE_3_MB055 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB056, CAN_TB_u4MB_RXLABEL( CAN_MB056 ), CAN_TB_u4MB_RXKIND( 3, 056 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB056, CAN_CFG_ID_VALUE_3_MB056 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB057, CAN_TB_u4MB_RXLABEL( CAN_MB057 ), CAN_TB_u4MB_RXKIND( 3, 057 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB057, CAN_CFG_ID_VALUE_3_MB057 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB058, CAN_TB_u4MB_RXLABEL( CAN_MB058 ), CAN_TB_u4MB_RXKIND( 3, 058 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB058, CAN_CFG_ID_VALUE_3_MB058 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB059, CAN_TB_u4MB_RXLABEL( CAN_MB059 ), CAN_TB_u4MB_RXKIND( 3, 059 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB059, CAN_CFG_ID_VALUE_3_MB059 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB060, CAN_TB_u4MB_RXLABEL( CAN_MB060 ), CAN_TB_u4MB_RXKIND( 3, 060 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB060, CAN_CFG_ID_VALUE_3_MB060 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB061, CAN_TB_u4MB_RXLABEL( CAN_MB061 ), CAN_TB_u4MB_RXKIND( 3, 061 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB061, CAN_CFG_ID_VALUE_3_MB061 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB062, CAN_TB_u4MB_RXLABEL( CAN_MB062 ), CAN_TB_u4MB_RXKIND( 3, 062 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB062, CAN_CFG_ID_VALUE_3_MB062 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB063, CAN_TB_u4MB_RXLABEL( CAN_MB063 ), CAN_TB_u4MB_RXKIND( 3, 063 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB063, CAN_CFG_ID_VALUE_3_MB063 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB064, CAN_TB_u4MB_RXLABEL( CAN_MB064 ), CAN_TB_u4MB_RXKIND( 3, 064 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB064, CAN_CFG_ID_VALUE_3_MB064 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB065, CAN_TB_u4MB_RXLABEL( CAN_MB065 ), CAN_TB_u4MB_RXKIND( 3, 065 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB065, CAN_CFG_ID_VALUE_3_MB065 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB066, CAN_TB_u4MB_RXLABEL( CAN_MB066 ), CAN_TB_u4MB_RXKIND( 3, 066 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB066, CAN_CFG_ID_VALUE_3_MB066 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB067, CAN_TB_u4MB_RXLABEL( CAN_MB067 ), CAN_TB_u4MB_RXKIND( 3, 067 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB067, CAN_CFG_ID_VALUE_3_MB067 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB068, CAN_TB_u4MB_RXLABEL( CAN_MB068 ), CAN_TB_u4MB_RXKIND( 3, 068 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB068, CAN_CFG_ID_VALUE_3_MB068 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB069, CAN_TB_u4MB_RXLABEL( CAN_MB069 ), CAN_TB_u4MB_RXKIND( 3, 069 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB069, CAN_CFG_ID_VALUE_3_MB069 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB070, CAN_TB_u4MB_RXLABEL( CAN_MB070 ), CAN_TB_u4MB_RXKIND( 3, 070 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB070, CAN_CFG_ID_VALUE_3_MB070 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB071, CAN_TB_u4MB_RXLABEL( CAN_MB071 ), CAN_TB_u4MB_RXKIND( 3, 071 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB071, CAN_CFG_ID_VALUE_3_MB071 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB072, CAN_TB_u4MB_RXLABEL( CAN_MB072 ), CAN_TB_u4MB_RXKIND( 3, 072 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB072, CAN_CFG_ID_VALUE_3_MB072 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB073, CAN_TB_u4MB_RXLABEL( CAN_MB073 ), CAN_TB_u4MB_RXKIND( 3, 073 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB073, CAN_CFG_ID_VALUE_3_MB073 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB074, CAN_TB_u4MB_RXLABEL( CAN_MB074 ), CAN_TB_u4MB_RXKIND( 3, 074 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB074, CAN_CFG_ID_VALUE_3_MB074 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB075, CAN_TB_u4MB_RXLABEL( CAN_MB075 ), CAN_TB_u4MB_RXKIND( 3, 075 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB075, CAN_CFG_ID_VALUE_3_MB075 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB076, CAN_TB_u4MB_RXLABEL( CAN_MB076 ), CAN_TB_u4MB_RXKIND( 3, 076 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB076, CAN_CFG_ID_VALUE_3_MB076 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB077, CAN_TB_u4MB_RXLABEL( CAN_MB077 ), CAN_TB_u4MB_RXKIND( 3, 077 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB077, CAN_CFG_ID_VALUE_3_MB077 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB078, CAN_TB_u4MB_RXLABEL( CAN_MB078 ), CAN_TB_u4MB_RXKIND( 3, 078 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB078, CAN_CFG_ID_VALUE_3_MB078 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB079, CAN_TB_u4MB_RXLABEL( CAN_MB079 ), CAN_TB_u4MB_RXKIND( 3, 079 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB079, CAN_CFG_ID_VALUE_3_MB079 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB080, CAN_TB_u4MB_RXLABEL( CAN_MB080 ), CAN_TB_u4MB_RXKIND( 3, 080 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB080, CAN_CFG_ID_VALUE_3_MB080 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB081, CAN_TB_u4MB_RXLABEL( CAN_MB081 ), CAN_TB_u4MB_RXKIND( 3, 081 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB081, CAN_CFG_ID_VALUE_3_MB081 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB082, CAN_TB_u4MB_RXLABEL( CAN_MB082 ), CAN_TB_u4MB_RXKIND( 3, 082 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB082, CAN_CFG_ID_VALUE_3_MB082 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB083, CAN_TB_u4MB_RXLABEL( CAN_MB083 ), CAN_TB_u4MB_RXKIND( 3, 083 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB083, CAN_CFG_ID_VALUE_3_MB083 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB084, CAN_TB_u4MB_RXLABEL( CAN_MB084 ), CAN_TB_u4MB_RXKIND( 3, 084 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB084, CAN_CFG_ID_VALUE_3_MB084 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB085, CAN_TB_u4MB_RXLABEL( CAN_MB085 ), CAN_TB_u4MB_RXKIND( 3, 085 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB085, CAN_CFG_ID_VALUE_3_MB085 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB086, CAN_TB_u4MB_RXLABEL( CAN_MB086 ), CAN_TB_u4MB_RXKIND( 3, 086 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB086, CAN_CFG_ID_VALUE_3_MB086 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB087, CAN_TB_u4MB_RXLABEL( CAN_MB087 ), CAN_TB_u4MB_RXKIND( 3, 087 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB087, CAN_CFG_ID_VALUE_3_MB087 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB088, CAN_TB_u4MB_RXLABEL( CAN_MB088 ), CAN_TB_u4MB_RXKIND( 3, 088 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB088, CAN_CFG_ID_VALUE_3_MB088 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB089, CAN_TB_u4MB_RXLABEL( CAN_MB089 ), CAN_TB_u4MB_RXKIND( 3, 089 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB089, CAN_CFG_ID_VALUE_3_MB089 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB090, CAN_TB_u4MB_RXLABEL( CAN_MB090 ), CAN_TB_u4MB_RXKIND( 3, 090 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB090, CAN_CFG_ID_VALUE_3_MB090 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB091, CAN_TB_u4MB_RXLABEL( CAN_MB091 ), CAN_TB_u4MB_RXKIND( 3, 091 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB091, CAN_CFG_ID_VALUE_3_MB091 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB092, CAN_TB_u4MB_RXLABEL( CAN_MB092 ), CAN_TB_u4MB_RXKIND( 3, 092 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB092, CAN_CFG_ID_VALUE_3_MB092 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB093, CAN_TB_u4MB_RXLABEL( CAN_MB093 ), CAN_TB_u4MB_RXKIND( 3, 093 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB093, CAN_CFG_ID_VALUE_3_MB093 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB094, CAN_TB_u4MB_RXLABEL( CAN_MB094 ), CAN_TB_u4MB_RXKIND( 3, 094 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB094, CAN_CFG_ID_VALUE_3_MB094 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB095, CAN_TB_u4MB_RXLABEL( CAN_MB095 ), CAN_TB_u4MB_RXKIND( 3, 095 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB095, CAN_CFG_ID_VALUE_3_MB095 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB096, CAN_TB_u4MB_RXLABEL( CAN_MB096 ), CAN_TB_u4MB_RXKIND( 3, 096 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB096, CAN_CFG_ID_VALUE_3_MB096 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB097, CAN_TB_u4MB_RXLABEL( CAN_MB097 ), CAN_TB_u4MB_RXKIND( 3, 097 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB097, CAN_CFG_ID_VALUE_3_MB097 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB098, CAN_TB_u4MB_RXLABEL( CAN_MB098 ), CAN_TB_u4MB_RXKIND( 3, 098 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB098, CAN_CFG_ID_VALUE_3_MB098 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB099, CAN_TB_u4MB_RXLABEL( CAN_MB099 ), CAN_TB_u4MB_RXKIND( 3, 099 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB099, CAN_CFG_ID_VALUE_3_MB099 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB100, CAN_TB_u4MB_RXLABEL( CAN_MB100 ), CAN_TB_u4MB_RXKIND( 3, 100 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB100, CAN_CFG_ID_VALUE_3_MB100 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB101, CAN_TB_u4MB_RXLABEL( CAN_MB101 ), CAN_TB_u4MB_RXKIND( 3, 101 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB101, CAN_CFG_ID_VALUE_3_MB101 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB102, CAN_TB_u4MB_RXLABEL( CAN_MB102 ), CAN_TB_u4MB_RXKIND( 3, 102 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB102, CAN_CFG_ID_VALUE_3_MB102 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB103, CAN_TB_u4MB_RXLABEL( CAN_MB103 ), CAN_TB_u4MB_RXKIND( 3, 103 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB103, CAN_CFG_ID_VALUE_3_MB103 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB104, CAN_TB_u4MB_RXLABEL( CAN_MB104 ), CAN_TB_u4MB_RXKIND( 3, 104 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB104, CAN_CFG_ID_VALUE_3_MB104 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB105, CAN_TB_u4MB_RXLABEL( CAN_MB105 ), CAN_TB_u4MB_RXKIND( 3, 105 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB105, CAN_CFG_ID_VALUE_3_MB105 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB106, CAN_TB_u4MB_RXLABEL( CAN_MB106 ), CAN_TB_u4MB_RXKIND( 3, 106 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB106, CAN_CFG_ID_VALUE_3_MB106 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB107, CAN_TB_u4MB_RXLABEL( CAN_MB107 ), CAN_TB_u4MB_RXKIND( 3, 107 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB107, CAN_CFG_ID_VALUE_3_MB107 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB108, CAN_TB_u4MB_RXLABEL( CAN_MB108 ), CAN_TB_u4MB_RXKIND( 3, 108 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB108, CAN_CFG_ID_VALUE_3_MB108 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB109, CAN_TB_u4MB_RXLABEL( CAN_MB109 ), CAN_TB_u4MB_RXKIND( 3, 109 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB109, CAN_CFG_ID_VALUE_3_MB109 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB110, CAN_TB_u4MB_RXLABEL( CAN_MB110 ), CAN_TB_u4MB_RXKIND( 3, 110 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB110, CAN_CFG_ID_VALUE_3_MB110 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB111, CAN_TB_u4MB_RXLABEL( CAN_MB111 ), CAN_TB_u4MB_RXKIND( 3, 111 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB111, CAN_CFG_ID_VALUE_3_MB111 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB112, CAN_TB_u4MB_RXLABEL( CAN_MB112 ), CAN_TB_u4MB_RXKIND( 3, 112 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB112, CAN_CFG_ID_VALUE_3_MB112 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB113, CAN_TB_u4MB_RXLABEL( CAN_MB113 ), CAN_TB_u4MB_RXKIND( 3, 113 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB113, CAN_CFG_ID_VALUE_3_MB113 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB114, CAN_TB_u4MB_RXLABEL( CAN_MB114 ), CAN_TB_u4MB_RXKIND( 3, 114 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB114, CAN_CFG_ID_VALUE_3_MB114 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB115, CAN_TB_u4MB_RXLABEL( CAN_MB115 ), CAN_TB_u4MB_RXKIND( 3, 115 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB115, CAN_CFG_ID_VALUE_3_MB115 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB116, CAN_TB_u4MB_RXLABEL( CAN_MB116 ), CAN_TB_u4MB_RXKIND( 3, 116 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB116, CAN_CFG_ID_VALUE_3_MB116 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB117, CAN_TB_u4MB_RXLABEL( CAN_MB117 ), CAN_TB_u4MB_RXKIND( 3, 117 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB117, CAN_CFG_ID_VALUE_3_MB117 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB118, CAN_TB_u4MB_RXLABEL( CAN_MB118 ), CAN_TB_u4MB_RXKIND( 3, 118 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB118, CAN_CFG_ID_VALUE_3_MB118 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB119, CAN_TB_u4MB_RXLABEL( CAN_MB119 ), CAN_TB_u4MB_RXKIND( 3, 119 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB119, CAN_CFG_ID_VALUE_3_MB119 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB120, CAN_TB_u4MB_RXLABEL( CAN_MB120 ), CAN_TB_u4MB_RXKIND( 3, 120 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB120, CAN_CFG_ID_VALUE_3_MB120 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB121, CAN_TB_u4MB_RXLABEL( CAN_MB121 ), CAN_TB_u4MB_RXKIND( 3, 121 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB121, CAN_CFG_ID_VALUE_3_MB121 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB122, CAN_TB_u4MB_RXLABEL( CAN_MB122 ), CAN_TB_u4MB_RXKIND( 3, 122 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB122, CAN_CFG_ID_VALUE_3_MB122 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB123, CAN_TB_u4MB_RXLABEL( CAN_MB123 ), CAN_TB_u4MB_RXKIND( 3, 123 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB123, CAN_CFG_ID_VALUE_3_MB123 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB124, CAN_TB_u4MB_RXLABEL( CAN_MB124 ), CAN_TB_u4MB_RXKIND( 3, 124 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB124, CAN_CFG_ID_VALUE_3_MB124 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB125, CAN_TB_u4MB_RXLABEL( CAN_MB125 ), CAN_TB_u4MB_RXKIND( 3, 125 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB125, CAN_CFG_ID_VALUE_3_MB125 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB126, CAN_TB_u4MB_RXLABEL( CAN_MB126 ), CAN_TB_u4MB_RXKIND( 3, 126 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB126, CAN_CFG_ID_VALUE_3_MB126 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB127, CAN_TB_u4MB_RXLABEL( CAN_MB127 ), CAN_TB_u4MB_RXKIND( 3, 127 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB127, CAN_CFG_ID_VALUE_3_MB127 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB128, CAN_TB_u4MB_RXLABEL( CAN_MB128 ), CAN_TB_u4MB_RXKIND( 3, 128 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB128, CAN_CFG_ID_VALUE_3_MB128 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB129, CAN_TB_u4MB_RXLABEL( CAN_MB129 ), CAN_TB_u4MB_RXKIND( 3, 129 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB129, CAN_CFG_ID_VALUE_3_MB129 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB130, CAN_TB_u4MB_RXLABEL( CAN_MB130 ), CAN_TB_u4MB_RXKIND( 3, 130 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB130, CAN_CFG_ID_VALUE_3_MB130 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB131, CAN_TB_u4MB_RXLABEL( CAN_MB131 ), CAN_TB_u4MB_RXKIND( 3, 131 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB131, CAN_CFG_ID_VALUE_3_MB131 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB132, CAN_TB_u4MB_RXLABEL( CAN_MB132 ), CAN_TB_u4MB_RXKIND( 3, 132 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB132, CAN_CFG_ID_VALUE_3_MB132 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB133, CAN_TB_u4MB_RXLABEL( CAN_MB133 ), CAN_TB_u4MB_RXKIND( 3, 133 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB133, CAN_CFG_ID_VALUE_3_MB133 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB134, CAN_TB_u4MB_RXLABEL( CAN_MB134 ), CAN_TB_u4MB_RXKIND( 3, 134 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB134, CAN_CFG_ID_VALUE_3_MB134 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB135, CAN_TB_u4MB_RXLABEL( CAN_MB135 ), CAN_TB_u4MB_RXKIND( 3, 135 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB135, CAN_CFG_ID_VALUE_3_MB135 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB136, CAN_TB_u4MB_RXLABEL( CAN_MB136 ), CAN_TB_u4MB_RXKIND( 3, 136 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB136, CAN_CFG_ID_VALUE_3_MB136 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB137, CAN_TB_u4MB_RXLABEL( CAN_MB137 ), CAN_TB_u4MB_RXKIND( 3, 137 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB137, CAN_CFG_ID_VALUE_3_MB137 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB138, CAN_TB_u4MB_RXLABEL( CAN_MB138 ), CAN_TB_u4MB_RXKIND( 3, 138 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB138, CAN_CFG_ID_VALUE_3_MB138 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB139, CAN_TB_u4MB_RXLABEL( CAN_MB139 ), CAN_TB_u4MB_RXKIND( 3, 139 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB139, CAN_CFG_ID_VALUE_3_MB139 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB140, CAN_TB_u4MB_RXLABEL( CAN_MB140 ), CAN_TB_u4MB_RXKIND( 3, 140 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB140, CAN_CFG_ID_VALUE_3_MB140 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB141, CAN_TB_u4MB_RXLABEL( CAN_MB141 ), CAN_TB_u4MB_RXKIND( 3, 141 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB141, CAN_CFG_ID_VALUE_3_MB141 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB142, CAN_TB_u4MB_RXLABEL( CAN_MB142 ), CAN_TB_u4MB_RXKIND( 3, 142 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB142, CAN_CFG_ID_VALUE_3_MB142 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB143, CAN_TB_u4MB_RXLABEL( CAN_MB143 ), CAN_TB_u4MB_RXKIND( 3, 143 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB143, CAN_CFG_ID_VALUE_3_MB143 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB144, CAN_TB_u4MB_RXLABEL( CAN_MB144 ), CAN_TB_u4MB_RXKIND( 3, 144 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB144, CAN_CFG_ID_VALUE_3_MB144 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB145, CAN_TB_u4MB_RXLABEL( CAN_MB145 ), CAN_TB_u4MB_RXKIND( 3, 145 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB145, CAN_CFG_ID_VALUE_3_MB145 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB146, CAN_TB_u4MB_RXLABEL( CAN_MB146 ), CAN_TB_u4MB_RXKIND( 3, 146 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB146, CAN_CFG_ID_VALUE_3_MB146 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB147, CAN_TB_u4MB_RXLABEL( CAN_MB147 ), CAN_TB_u4MB_RXKIND( 3, 147 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB147, CAN_CFG_ID_VALUE_3_MB147 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB148, CAN_TB_u4MB_RXLABEL( CAN_MB148 ), CAN_TB_u4MB_RXKIND( 3, 148 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB148, CAN_CFG_ID_VALUE_3_MB148 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB149, CAN_TB_u4MB_RXLABEL( CAN_MB149 ), CAN_TB_u4MB_RXKIND( 3, 149 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB149, CAN_CFG_ID_VALUE_3_MB149 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB150, CAN_TB_u4MB_RXLABEL( CAN_MB150 ), CAN_TB_u4MB_RXKIND( 3, 150 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB150, CAN_CFG_ID_VALUE_3_MB150 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB151, CAN_TB_u4MB_RXLABEL( CAN_MB151 ), CAN_TB_u4MB_RXKIND( 3, 151 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB151, CAN_CFG_ID_VALUE_3_MB151 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB152, CAN_TB_u4MB_RXLABEL( CAN_MB152 ), CAN_TB_u4MB_RXKIND( 3, 152 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB152, CAN_CFG_ID_VALUE_3_MB152 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB153, CAN_TB_u4MB_RXLABEL( CAN_MB153 ), CAN_TB_u4MB_RXKIND( 3, 153 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB153, CAN_CFG_ID_VALUE_3_MB153 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB154, CAN_TB_u4MB_RXLABEL( CAN_MB154 ), CAN_TB_u4MB_RXKIND( 3, 154 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB154, CAN_CFG_ID_VALUE_3_MB154 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB155, CAN_TB_u4MB_RXLABEL( CAN_MB155 ), CAN_TB_u4MB_RXKIND( 3, 155 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB155, CAN_CFG_ID_VALUE_3_MB155 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB156, CAN_TB_u4MB_RXLABEL( CAN_MB156 ), CAN_TB_u4MB_RXKIND( 3, 156 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB156, CAN_CFG_ID_VALUE_3_MB156 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB157, CAN_TB_u4MB_RXLABEL( CAN_MB157 ), CAN_TB_u4MB_RXKIND( 3, 157 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB157, CAN_CFG_ID_VALUE_3_MB157 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB158, CAN_TB_u4MB_RXLABEL( CAN_MB158 ), CAN_TB_u4MB_RXKIND( 3, 158 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB158, CAN_CFG_ID_VALUE_3_MB158 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB159, CAN_TB_u4MB_RXLABEL( CAN_MB159 ), CAN_TB_u4MB_RXKIND( 3, 159 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB159, CAN_CFG_ID_VALUE_3_MB159 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB160, CAN_TB_u4MB_RXLABEL( CAN_MB160 ), CAN_TB_u4MB_RXKIND( 3, 160 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB160, CAN_CFG_ID_VALUE_3_MB160 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB161, CAN_TB_u4MB_RXLABEL( CAN_MB161 ), CAN_TB_u4MB_RXKIND( 3, 161 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB161, CAN_CFG_ID_VALUE_3_MB161 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB162, CAN_TB_u4MB_RXLABEL( CAN_MB162 ), CAN_TB_u4MB_RXKIND( 3, 162 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB162, CAN_CFG_ID_VALUE_3_MB162 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB163, CAN_TB_u4MB_RXLABEL( CAN_MB163 ), CAN_TB_u4MB_RXKIND( 3, 163 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB163, CAN_CFG_ID_VALUE_3_MB163 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB164, CAN_TB_u4MB_RXLABEL( CAN_MB164 ), CAN_TB_u4MB_RXKIND( 3, 164 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB164, CAN_CFG_ID_VALUE_3_MB164 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB165, CAN_TB_u4MB_RXLABEL( CAN_MB165 ), CAN_TB_u4MB_RXKIND( 3, 165 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB165, CAN_CFG_ID_VALUE_3_MB165 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB166, CAN_TB_u4MB_RXLABEL( CAN_MB166 ), CAN_TB_u4MB_RXKIND( 3, 166 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB166, CAN_CFG_ID_VALUE_3_MB166 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB167, CAN_TB_u4MB_RXLABEL( CAN_MB167 ), CAN_TB_u4MB_RXKIND( 3, 167 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB167, CAN_CFG_ID_VALUE_3_MB167 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB168, CAN_TB_u4MB_RXLABEL( CAN_MB168 ), CAN_TB_u4MB_RXKIND( 3, 168 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB168, CAN_CFG_ID_VALUE_3_MB168 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB169, CAN_TB_u4MB_RXLABEL( CAN_MB169 ), CAN_TB_u4MB_RXKIND( 3, 169 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB169, CAN_CFG_ID_VALUE_3_MB169 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB170, CAN_TB_u4MB_RXLABEL( CAN_MB170 ), CAN_TB_u4MB_RXKIND( 3, 170 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB170, CAN_CFG_ID_VALUE_3_MB170 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB171, CAN_TB_u4MB_RXLABEL( CAN_MB171 ), CAN_TB_u4MB_RXKIND( 3, 171 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB171, CAN_CFG_ID_VALUE_3_MB171 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB172, CAN_TB_u4MB_RXLABEL( CAN_MB172 ), CAN_TB_u4MB_RXKIND( 3, 172 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB172, CAN_CFG_ID_VALUE_3_MB172 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB173, CAN_TB_u4MB_RXLABEL( CAN_MB173 ), CAN_TB_u4MB_RXKIND( 3, 173 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB173, CAN_CFG_ID_VALUE_3_MB173 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB174, CAN_TB_u4MB_RXLABEL( CAN_MB174 ), CAN_TB_u4MB_RXKIND( 3, 174 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB174, CAN_CFG_ID_VALUE_3_MB174 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB175, CAN_TB_u4MB_RXLABEL( CAN_MB175 ), CAN_TB_u4MB_RXKIND( 3, 175 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB175, CAN_CFG_ID_VALUE_3_MB175 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB176, CAN_TB_u4MB_RXLABEL( CAN_MB176 ), CAN_TB_u4MB_RXKIND( 3, 176 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB176, CAN_CFG_ID_VALUE_3_MB176 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB177, CAN_TB_u4MB_RXLABEL( CAN_MB177 ), CAN_TB_u4MB_RXKIND( 3, 177 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB177, CAN_CFG_ID_VALUE_3_MB177 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB178, CAN_TB_u4MB_RXLABEL( CAN_MB178 ), CAN_TB_u4MB_RXKIND( 3, 178 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB178, CAN_CFG_ID_VALUE_3_MB178 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB179, CAN_TB_u4MB_RXLABEL( CAN_MB179 ), CAN_TB_u4MB_RXKIND( 3, 179 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB179, CAN_CFG_ID_VALUE_3_MB179 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB180, CAN_TB_u4MB_RXLABEL( CAN_MB180 ), CAN_TB_u4MB_RXKIND( 3, 180 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB180, CAN_CFG_ID_VALUE_3_MB180 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB181, CAN_TB_u4MB_RXLABEL( CAN_MB181 ), CAN_TB_u4MB_RXKIND( 3, 181 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB181, CAN_CFG_ID_VALUE_3_MB181 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB182, CAN_TB_u4MB_RXLABEL( CAN_MB182 ), CAN_TB_u4MB_RXKIND( 3, 182 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB182, CAN_CFG_ID_VALUE_3_MB182 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB183, CAN_TB_u4MB_RXLABEL( CAN_MB183 ), CAN_TB_u4MB_RXKIND( 3, 183 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB183, CAN_CFG_ID_VALUE_3_MB183 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB184, CAN_TB_u4MB_RXLABEL( CAN_MB184 ), CAN_TB_u4MB_RXKIND( 3, 184 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB184, CAN_CFG_ID_VALUE_3_MB184 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB185, CAN_TB_u4MB_RXLABEL( CAN_MB185 ), CAN_TB_u4MB_RXKIND( 3, 185 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB185, CAN_CFG_ID_VALUE_3_MB185 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB186, CAN_TB_u4MB_RXLABEL( CAN_MB186 ), CAN_TB_u4MB_RXKIND( 3, 186 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB186, CAN_CFG_ID_VALUE_3_MB186 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB187, CAN_TB_u4MB_RXLABEL( CAN_MB187 ), CAN_TB_u4MB_RXKIND( 3, 187 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB187, CAN_CFG_ID_VALUE_3_MB187 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB188, CAN_TB_u4MB_RXLABEL( CAN_MB188 ), CAN_TB_u4MB_RXKIND( 3, 188 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB188, CAN_CFG_ID_VALUE_3_MB188 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB189, CAN_TB_u4MB_RXLABEL( CAN_MB189 ), CAN_TB_u4MB_RXKIND( 3, 189 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB189, CAN_CFG_ID_VALUE_3_MB189 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB190, CAN_TB_u4MB_RXLABEL( CAN_MB190 ), CAN_TB_u4MB_RXKIND( 3, 190 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB190, CAN_CFG_ID_VALUE_3_MB190 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_3_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_3_MB191, CAN_TB_u4MB_RXLABEL( CAN_MB191 ), CAN_TB_u4MB_RXKIND( 3, 191 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_3_MB191, CAN_CFG_ID_VALUE_3_MB191 ) },
#endif /* ( (CAN_CFG_MBOXSET_3_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */

    /* Controller 4 */
#if ( (CAN_CFG_MBOXSET_4_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB000, CAN_TB_u4MB_RXLABEL( CAN_MB000 ), CAN_TB_u4MB_RXKIND( 4, 000 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB000, CAN_CFG_ID_VALUE_4_MB000 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB001, CAN_TB_u4MB_RXLABEL( CAN_MB001 ), CAN_TB_u4MB_RXKIND( 4, 001 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB001, CAN_CFG_ID_VALUE_4_MB001 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB002, CAN_TB_u4MB_RXLABEL( CAN_MB002 ), CAN_TB_u4MB_RXKIND( 4, 002 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB002, CAN_CFG_ID_VALUE_4_MB002 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB003, CAN_TB_u4MB_RXLABEL( CAN_MB003 ), CAN_TB_u4MB_RXKIND( 4, 003 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB003, CAN_CFG_ID_VALUE_4_MB003 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB004, CAN_TB_u4MB_RXLABEL( CAN_MB004 ), CAN_TB_u4MB_RXKIND( 4, 004 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB004, CAN_CFG_ID_VALUE_4_MB004 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB005, CAN_TB_u4MB_RXLABEL( CAN_MB005 ), CAN_TB_u4MB_RXKIND( 4, 005 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB005, CAN_CFG_ID_VALUE_4_MB005 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB006, CAN_TB_u4MB_RXLABEL( CAN_MB006 ), CAN_TB_u4MB_RXKIND( 4, 006 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB006, CAN_CFG_ID_VALUE_4_MB006 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB007, CAN_TB_u4MB_RXLABEL( CAN_MB007 ), CAN_TB_u4MB_RXKIND( 4, 007 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB007, CAN_CFG_ID_VALUE_4_MB007 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB008, CAN_TB_u4MB_RXLABEL( CAN_MB008 ), CAN_TB_u4MB_RXKIND( 4, 008 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB008, CAN_CFG_ID_VALUE_4_MB008 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB009, CAN_TB_u4MB_RXLABEL( CAN_MB009 ), CAN_TB_u4MB_RXKIND( 4, 009 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB009, CAN_CFG_ID_VALUE_4_MB009 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB010, CAN_TB_u4MB_RXLABEL( CAN_MB010 ), CAN_TB_u4MB_RXKIND( 4, 010 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB010, CAN_CFG_ID_VALUE_4_MB010 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB011, CAN_TB_u4MB_RXLABEL( CAN_MB011 ), CAN_TB_u4MB_RXKIND( 4, 011 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB011, CAN_CFG_ID_VALUE_4_MB011 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB012, CAN_TB_u4MB_RXLABEL( CAN_MB012 ), CAN_TB_u4MB_RXKIND( 4, 012 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB012, CAN_CFG_ID_VALUE_4_MB012 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB013, CAN_TB_u4MB_RXLABEL( CAN_MB013 ), CAN_TB_u4MB_RXKIND( 4, 013 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB013, CAN_CFG_ID_VALUE_4_MB013 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB014, CAN_TB_u4MB_RXLABEL( CAN_MB014 ), CAN_TB_u4MB_RXKIND( 4, 014 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB014, CAN_CFG_ID_VALUE_4_MB014 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB015, CAN_TB_u4MB_RXLABEL( CAN_MB015 ), CAN_TB_u4MB_RXKIND( 4, 015 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB015, CAN_CFG_ID_VALUE_4_MB015 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB016, CAN_TB_u4MB_RXLABEL( CAN_MB016 ), CAN_TB_u4MB_RXKIND( 4, 016 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB016, CAN_CFG_ID_VALUE_4_MB016 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB017, CAN_TB_u4MB_RXLABEL( CAN_MB017 ), CAN_TB_u4MB_RXKIND( 4, 017 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB017, CAN_CFG_ID_VALUE_4_MB017 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB018, CAN_TB_u4MB_RXLABEL( CAN_MB018 ), CAN_TB_u4MB_RXKIND( 4, 018 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB018, CAN_CFG_ID_VALUE_4_MB018 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB019, CAN_TB_u4MB_RXLABEL( CAN_MB019 ), CAN_TB_u4MB_RXKIND( 4, 019 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB019, CAN_CFG_ID_VALUE_4_MB019 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB020, CAN_TB_u4MB_RXLABEL( CAN_MB020 ), CAN_TB_u4MB_RXKIND( 4, 020 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB020, CAN_CFG_ID_VALUE_4_MB020 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB021, CAN_TB_u4MB_RXLABEL( CAN_MB021 ), CAN_TB_u4MB_RXKIND( 4, 021 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB021, CAN_CFG_ID_VALUE_4_MB021 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB022, CAN_TB_u4MB_RXLABEL( CAN_MB022 ), CAN_TB_u4MB_RXKIND( 4, 022 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB022, CAN_CFG_ID_VALUE_4_MB022 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB023, CAN_TB_u4MB_RXLABEL( CAN_MB023 ), CAN_TB_u4MB_RXKIND( 4, 023 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB023, CAN_CFG_ID_VALUE_4_MB023 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB024, CAN_TB_u4MB_RXLABEL( CAN_MB024 ), CAN_TB_u4MB_RXKIND( 4, 024 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB024, CAN_CFG_ID_VALUE_4_MB024 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB025, CAN_TB_u4MB_RXLABEL( CAN_MB025 ), CAN_TB_u4MB_RXKIND( 4, 025 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB025, CAN_CFG_ID_VALUE_4_MB025 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB026, CAN_TB_u4MB_RXLABEL( CAN_MB026 ), CAN_TB_u4MB_RXKIND( 4, 026 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB026, CAN_CFG_ID_VALUE_4_MB026 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB027, CAN_TB_u4MB_RXLABEL( CAN_MB027 ), CAN_TB_u4MB_RXKIND( 4, 027 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB027, CAN_CFG_ID_VALUE_4_MB027 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB028, CAN_TB_u4MB_RXLABEL( CAN_MB028 ), CAN_TB_u4MB_RXKIND( 4, 028 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB028, CAN_CFG_ID_VALUE_4_MB028 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB029, CAN_TB_u4MB_RXLABEL( CAN_MB029 ), CAN_TB_u4MB_RXKIND( 4, 029 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB029, CAN_CFG_ID_VALUE_4_MB029 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB030, CAN_TB_u4MB_RXLABEL( CAN_MB030 ), CAN_TB_u4MB_RXKIND( 4, 030 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB030, CAN_CFG_ID_VALUE_4_MB030 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB031, CAN_TB_u4MB_RXLABEL( CAN_MB031 ), CAN_TB_u4MB_RXKIND( 4, 031 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB031, CAN_CFG_ID_VALUE_4_MB031 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB032, CAN_TB_u4MB_RXLABEL( CAN_MB032 ), CAN_TB_u4MB_RXKIND( 4, 032 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB032, CAN_CFG_ID_VALUE_4_MB032 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB033, CAN_TB_u4MB_RXLABEL( CAN_MB033 ), CAN_TB_u4MB_RXKIND( 4, 033 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB033, CAN_CFG_ID_VALUE_4_MB033 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB034, CAN_TB_u4MB_RXLABEL( CAN_MB034 ), CAN_TB_u4MB_RXKIND( 4, 034 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB034, CAN_CFG_ID_VALUE_4_MB034 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB035, CAN_TB_u4MB_RXLABEL( CAN_MB035 ), CAN_TB_u4MB_RXKIND( 4, 035 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB035, CAN_CFG_ID_VALUE_4_MB035 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB036, CAN_TB_u4MB_RXLABEL( CAN_MB036 ), CAN_TB_u4MB_RXKIND( 4, 036 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB036, CAN_CFG_ID_VALUE_4_MB036 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB037, CAN_TB_u4MB_RXLABEL( CAN_MB037 ), CAN_TB_u4MB_RXKIND( 4, 037 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB037, CAN_CFG_ID_VALUE_4_MB037 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB038, CAN_TB_u4MB_RXLABEL( CAN_MB038 ), CAN_TB_u4MB_RXKIND( 4, 038 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB038, CAN_CFG_ID_VALUE_4_MB038 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB039, CAN_TB_u4MB_RXLABEL( CAN_MB039 ), CAN_TB_u4MB_RXKIND( 4, 039 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB039, CAN_CFG_ID_VALUE_4_MB039 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB040, CAN_TB_u4MB_RXLABEL( CAN_MB040 ), CAN_TB_u4MB_RXKIND( 4, 040 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB040, CAN_CFG_ID_VALUE_4_MB040 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB041, CAN_TB_u4MB_RXLABEL( CAN_MB041 ), CAN_TB_u4MB_RXKIND( 4, 041 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB041, CAN_CFG_ID_VALUE_4_MB041 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB042, CAN_TB_u4MB_RXLABEL( CAN_MB042 ), CAN_TB_u4MB_RXKIND( 4, 042 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB042, CAN_CFG_ID_VALUE_4_MB042 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB043, CAN_TB_u4MB_RXLABEL( CAN_MB043 ), CAN_TB_u4MB_RXKIND( 4, 043 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB043, CAN_CFG_ID_VALUE_4_MB043 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB044, CAN_TB_u4MB_RXLABEL( CAN_MB044 ), CAN_TB_u4MB_RXKIND( 4, 044 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB044, CAN_CFG_ID_VALUE_4_MB044 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB045, CAN_TB_u4MB_RXLABEL( CAN_MB045 ), CAN_TB_u4MB_RXKIND( 4, 045 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB045, CAN_CFG_ID_VALUE_4_MB045 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB046, CAN_TB_u4MB_RXLABEL( CAN_MB046 ), CAN_TB_u4MB_RXKIND( 4, 046 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB046, CAN_CFG_ID_VALUE_4_MB046 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB047, CAN_TB_u4MB_RXLABEL( CAN_MB047 ), CAN_TB_u4MB_RXKIND( 4, 047 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB047, CAN_CFG_ID_VALUE_4_MB047 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB048, CAN_TB_u4MB_RXLABEL( CAN_MB048 ), CAN_TB_u4MB_RXKIND( 4, 048 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB048, CAN_CFG_ID_VALUE_4_MB048 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB049, CAN_TB_u4MB_RXLABEL( CAN_MB049 ), CAN_TB_u4MB_RXKIND( 4, 049 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB049, CAN_CFG_ID_VALUE_4_MB049 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB050, CAN_TB_u4MB_RXLABEL( CAN_MB050 ), CAN_TB_u4MB_RXKIND( 4, 050 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB050, CAN_CFG_ID_VALUE_4_MB050 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB051, CAN_TB_u4MB_RXLABEL( CAN_MB051 ), CAN_TB_u4MB_RXKIND( 4, 051 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB051, CAN_CFG_ID_VALUE_4_MB051 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB052, CAN_TB_u4MB_RXLABEL( CAN_MB052 ), CAN_TB_u4MB_RXKIND( 4, 052 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB052, CAN_CFG_ID_VALUE_4_MB052 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB053, CAN_TB_u4MB_RXLABEL( CAN_MB053 ), CAN_TB_u4MB_RXKIND( 4, 053 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB053, CAN_CFG_ID_VALUE_4_MB053 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB054, CAN_TB_u4MB_RXLABEL( CAN_MB054 ), CAN_TB_u4MB_RXKIND( 4, 054 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB054, CAN_CFG_ID_VALUE_4_MB054 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB055, CAN_TB_u4MB_RXLABEL( CAN_MB055 ), CAN_TB_u4MB_RXKIND( 4, 055 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB055, CAN_CFG_ID_VALUE_4_MB055 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB056, CAN_TB_u4MB_RXLABEL( CAN_MB056 ), CAN_TB_u4MB_RXKIND( 4, 056 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB056, CAN_CFG_ID_VALUE_4_MB056 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB057, CAN_TB_u4MB_RXLABEL( CAN_MB057 ), CAN_TB_u4MB_RXKIND( 4, 057 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB057, CAN_CFG_ID_VALUE_4_MB057 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB058, CAN_TB_u4MB_RXLABEL( CAN_MB058 ), CAN_TB_u4MB_RXKIND( 4, 058 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB058, CAN_CFG_ID_VALUE_4_MB058 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB059, CAN_TB_u4MB_RXLABEL( CAN_MB059 ), CAN_TB_u4MB_RXKIND( 4, 059 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB059, CAN_CFG_ID_VALUE_4_MB059 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB060, CAN_TB_u4MB_RXLABEL( CAN_MB060 ), CAN_TB_u4MB_RXKIND( 4, 060 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB060, CAN_CFG_ID_VALUE_4_MB060 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB061, CAN_TB_u4MB_RXLABEL( CAN_MB061 ), CAN_TB_u4MB_RXKIND( 4, 061 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB061, CAN_CFG_ID_VALUE_4_MB061 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB062, CAN_TB_u4MB_RXLABEL( CAN_MB062 ), CAN_TB_u4MB_RXKIND( 4, 062 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB062, CAN_CFG_ID_VALUE_4_MB062 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB063, CAN_TB_u4MB_RXLABEL( CAN_MB063 ), CAN_TB_u4MB_RXKIND( 4, 063 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB063, CAN_CFG_ID_VALUE_4_MB063 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB064, CAN_TB_u4MB_RXLABEL( CAN_MB064 ), CAN_TB_u4MB_RXKIND( 4, 064 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB064, CAN_CFG_ID_VALUE_4_MB064 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB065, CAN_TB_u4MB_RXLABEL( CAN_MB065 ), CAN_TB_u4MB_RXKIND( 4, 065 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB065, CAN_CFG_ID_VALUE_4_MB065 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB066, CAN_TB_u4MB_RXLABEL( CAN_MB066 ), CAN_TB_u4MB_RXKIND( 4, 066 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB066, CAN_CFG_ID_VALUE_4_MB066 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB067, CAN_TB_u4MB_RXLABEL( CAN_MB067 ), CAN_TB_u4MB_RXKIND( 4, 067 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB067, CAN_CFG_ID_VALUE_4_MB067 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB068, CAN_TB_u4MB_RXLABEL( CAN_MB068 ), CAN_TB_u4MB_RXKIND( 4, 068 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB068, CAN_CFG_ID_VALUE_4_MB068 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB069, CAN_TB_u4MB_RXLABEL( CAN_MB069 ), CAN_TB_u4MB_RXKIND( 4, 069 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB069, CAN_CFG_ID_VALUE_4_MB069 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB070, CAN_TB_u4MB_RXLABEL( CAN_MB070 ), CAN_TB_u4MB_RXKIND( 4, 070 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB070, CAN_CFG_ID_VALUE_4_MB070 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB071, CAN_TB_u4MB_RXLABEL( CAN_MB071 ), CAN_TB_u4MB_RXKIND( 4, 071 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB071, CAN_CFG_ID_VALUE_4_MB071 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB072, CAN_TB_u4MB_RXLABEL( CAN_MB072 ), CAN_TB_u4MB_RXKIND( 4, 072 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB072, CAN_CFG_ID_VALUE_4_MB072 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB073, CAN_TB_u4MB_RXLABEL( CAN_MB073 ), CAN_TB_u4MB_RXKIND( 4, 073 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB073, CAN_CFG_ID_VALUE_4_MB073 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB074, CAN_TB_u4MB_RXLABEL( CAN_MB074 ), CAN_TB_u4MB_RXKIND( 4, 074 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB074, CAN_CFG_ID_VALUE_4_MB074 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB075, CAN_TB_u4MB_RXLABEL( CAN_MB075 ), CAN_TB_u4MB_RXKIND( 4, 075 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB075, CAN_CFG_ID_VALUE_4_MB075 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB076, CAN_TB_u4MB_RXLABEL( CAN_MB076 ), CAN_TB_u4MB_RXKIND( 4, 076 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB076, CAN_CFG_ID_VALUE_4_MB076 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB077, CAN_TB_u4MB_RXLABEL( CAN_MB077 ), CAN_TB_u4MB_RXKIND( 4, 077 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB077, CAN_CFG_ID_VALUE_4_MB077 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB078, CAN_TB_u4MB_RXLABEL( CAN_MB078 ), CAN_TB_u4MB_RXKIND( 4, 078 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB078, CAN_CFG_ID_VALUE_4_MB078 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB079, CAN_TB_u4MB_RXLABEL( CAN_MB079 ), CAN_TB_u4MB_RXKIND( 4, 079 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB079, CAN_CFG_ID_VALUE_4_MB079 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB080, CAN_TB_u4MB_RXLABEL( CAN_MB080 ), CAN_TB_u4MB_RXKIND( 4, 080 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB080, CAN_CFG_ID_VALUE_4_MB080 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB081, CAN_TB_u4MB_RXLABEL( CAN_MB081 ), CAN_TB_u4MB_RXKIND( 4, 081 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB081, CAN_CFG_ID_VALUE_4_MB081 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB082, CAN_TB_u4MB_RXLABEL( CAN_MB082 ), CAN_TB_u4MB_RXKIND( 4, 082 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB082, CAN_CFG_ID_VALUE_4_MB082 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB083, CAN_TB_u4MB_RXLABEL( CAN_MB083 ), CAN_TB_u4MB_RXKIND( 4, 083 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB083, CAN_CFG_ID_VALUE_4_MB083 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB084, CAN_TB_u4MB_RXLABEL( CAN_MB084 ), CAN_TB_u4MB_RXKIND( 4, 084 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB084, CAN_CFG_ID_VALUE_4_MB084 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB085, CAN_TB_u4MB_RXLABEL( CAN_MB085 ), CAN_TB_u4MB_RXKIND( 4, 085 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB085, CAN_CFG_ID_VALUE_4_MB085 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB086, CAN_TB_u4MB_RXLABEL( CAN_MB086 ), CAN_TB_u4MB_RXKIND( 4, 086 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB086, CAN_CFG_ID_VALUE_4_MB086 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB087, CAN_TB_u4MB_RXLABEL( CAN_MB087 ), CAN_TB_u4MB_RXKIND( 4, 087 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB087, CAN_CFG_ID_VALUE_4_MB087 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB088, CAN_TB_u4MB_RXLABEL( CAN_MB088 ), CAN_TB_u4MB_RXKIND( 4, 088 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB088, CAN_CFG_ID_VALUE_4_MB088 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB089, CAN_TB_u4MB_RXLABEL( CAN_MB089 ), CAN_TB_u4MB_RXKIND( 4, 089 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB089, CAN_CFG_ID_VALUE_4_MB089 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB090, CAN_TB_u4MB_RXLABEL( CAN_MB090 ), CAN_TB_u4MB_RXKIND( 4, 090 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB090, CAN_CFG_ID_VALUE_4_MB090 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB091, CAN_TB_u4MB_RXLABEL( CAN_MB091 ), CAN_TB_u4MB_RXKIND( 4, 091 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB091, CAN_CFG_ID_VALUE_4_MB091 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB092, CAN_TB_u4MB_RXLABEL( CAN_MB092 ), CAN_TB_u4MB_RXKIND( 4, 092 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB092, CAN_CFG_ID_VALUE_4_MB092 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB093, CAN_TB_u4MB_RXLABEL( CAN_MB093 ), CAN_TB_u4MB_RXKIND( 4, 093 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB093, CAN_CFG_ID_VALUE_4_MB093 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB094, CAN_TB_u4MB_RXLABEL( CAN_MB094 ), CAN_TB_u4MB_RXKIND( 4, 094 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB094, CAN_CFG_ID_VALUE_4_MB094 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB095, CAN_TB_u4MB_RXLABEL( CAN_MB095 ), CAN_TB_u4MB_RXKIND( 4, 095 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB095, CAN_CFG_ID_VALUE_4_MB095 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB096, CAN_TB_u4MB_RXLABEL( CAN_MB096 ), CAN_TB_u4MB_RXKIND( 4, 096 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB096, CAN_CFG_ID_VALUE_4_MB096 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB097, CAN_TB_u4MB_RXLABEL( CAN_MB097 ), CAN_TB_u4MB_RXKIND( 4, 097 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB097, CAN_CFG_ID_VALUE_4_MB097 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB098, CAN_TB_u4MB_RXLABEL( CAN_MB098 ), CAN_TB_u4MB_RXKIND( 4, 098 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB098, CAN_CFG_ID_VALUE_4_MB098 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB099, CAN_TB_u4MB_RXLABEL( CAN_MB099 ), CAN_TB_u4MB_RXKIND( 4, 099 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB099, CAN_CFG_ID_VALUE_4_MB099 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB100, CAN_TB_u4MB_RXLABEL( CAN_MB100 ), CAN_TB_u4MB_RXKIND( 4, 100 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB100, CAN_CFG_ID_VALUE_4_MB100 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB101, CAN_TB_u4MB_RXLABEL( CAN_MB101 ), CAN_TB_u4MB_RXKIND( 4, 101 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB101, CAN_CFG_ID_VALUE_4_MB101 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB102, CAN_TB_u4MB_RXLABEL( CAN_MB102 ), CAN_TB_u4MB_RXKIND( 4, 102 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB102, CAN_CFG_ID_VALUE_4_MB102 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB103, CAN_TB_u4MB_RXLABEL( CAN_MB103 ), CAN_TB_u4MB_RXKIND( 4, 103 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB103, CAN_CFG_ID_VALUE_4_MB103 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB104, CAN_TB_u4MB_RXLABEL( CAN_MB104 ), CAN_TB_u4MB_RXKIND( 4, 104 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB104, CAN_CFG_ID_VALUE_4_MB104 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB105, CAN_TB_u4MB_RXLABEL( CAN_MB105 ), CAN_TB_u4MB_RXKIND( 4, 105 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB105, CAN_CFG_ID_VALUE_4_MB105 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB106, CAN_TB_u4MB_RXLABEL( CAN_MB106 ), CAN_TB_u4MB_RXKIND( 4, 106 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB106, CAN_CFG_ID_VALUE_4_MB106 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB107, CAN_TB_u4MB_RXLABEL( CAN_MB107 ), CAN_TB_u4MB_RXKIND( 4, 107 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB107, CAN_CFG_ID_VALUE_4_MB107 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB108, CAN_TB_u4MB_RXLABEL( CAN_MB108 ), CAN_TB_u4MB_RXKIND( 4, 108 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB108, CAN_CFG_ID_VALUE_4_MB108 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB109, CAN_TB_u4MB_RXLABEL( CAN_MB109 ), CAN_TB_u4MB_RXKIND( 4, 109 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB109, CAN_CFG_ID_VALUE_4_MB109 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB110, CAN_TB_u4MB_RXLABEL( CAN_MB110 ), CAN_TB_u4MB_RXKIND( 4, 110 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB110, CAN_CFG_ID_VALUE_4_MB110 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB111, CAN_TB_u4MB_RXLABEL( CAN_MB111 ), CAN_TB_u4MB_RXKIND( 4, 111 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB111, CAN_CFG_ID_VALUE_4_MB111 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB112, CAN_TB_u4MB_RXLABEL( CAN_MB112 ), CAN_TB_u4MB_RXKIND( 4, 112 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB112, CAN_CFG_ID_VALUE_4_MB112 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB113, CAN_TB_u4MB_RXLABEL( CAN_MB113 ), CAN_TB_u4MB_RXKIND( 4, 113 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB113, CAN_CFG_ID_VALUE_4_MB113 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB114, CAN_TB_u4MB_RXLABEL( CAN_MB114 ), CAN_TB_u4MB_RXKIND( 4, 114 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB114, CAN_CFG_ID_VALUE_4_MB114 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB115, CAN_TB_u4MB_RXLABEL( CAN_MB115 ), CAN_TB_u4MB_RXKIND( 4, 115 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB115, CAN_CFG_ID_VALUE_4_MB115 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB116, CAN_TB_u4MB_RXLABEL( CAN_MB116 ), CAN_TB_u4MB_RXKIND( 4, 116 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB116, CAN_CFG_ID_VALUE_4_MB116 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB117, CAN_TB_u4MB_RXLABEL( CAN_MB117 ), CAN_TB_u4MB_RXKIND( 4, 117 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB117, CAN_CFG_ID_VALUE_4_MB117 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB118, CAN_TB_u4MB_RXLABEL( CAN_MB118 ), CAN_TB_u4MB_RXKIND( 4, 118 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB118, CAN_CFG_ID_VALUE_4_MB118 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB119, CAN_TB_u4MB_RXLABEL( CAN_MB119 ), CAN_TB_u4MB_RXKIND( 4, 119 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB119, CAN_CFG_ID_VALUE_4_MB119 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB120, CAN_TB_u4MB_RXLABEL( CAN_MB120 ), CAN_TB_u4MB_RXKIND( 4, 120 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB120, CAN_CFG_ID_VALUE_4_MB120 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB121, CAN_TB_u4MB_RXLABEL( CAN_MB121 ), CAN_TB_u4MB_RXKIND( 4, 121 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB121, CAN_CFG_ID_VALUE_4_MB121 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB122, CAN_TB_u4MB_RXLABEL( CAN_MB122 ), CAN_TB_u4MB_RXKIND( 4, 122 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB122, CAN_CFG_ID_VALUE_4_MB122 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB123, CAN_TB_u4MB_RXLABEL( CAN_MB123 ), CAN_TB_u4MB_RXKIND( 4, 123 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB123, CAN_CFG_ID_VALUE_4_MB123 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB124, CAN_TB_u4MB_RXLABEL( CAN_MB124 ), CAN_TB_u4MB_RXKIND( 4, 124 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB124, CAN_CFG_ID_VALUE_4_MB124 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB125, CAN_TB_u4MB_RXLABEL( CAN_MB125 ), CAN_TB_u4MB_RXKIND( 4, 125 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB125, CAN_CFG_ID_VALUE_4_MB125 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB126, CAN_TB_u4MB_RXLABEL( CAN_MB126 ), CAN_TB_u4MB_RXKIND( 4, 126 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB126, CAN_CFG_ID_VALUE_4_MB126 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB127, CAN_TB_u4MB_RXLABEL( CAN_MB127 ), CAN_TB_u4MB_RXKIND( 4, 127 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB127, CAN_CFG_ID_VALUE_4_MB127 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB128, CAN_TB_u4MB_RXLABEL( CAN_MB128 ), CAN_TB_u4MB_RXKIND( 4, 128 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB128, CAN_CFG_ID_VALUE_4_MB128 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB129, CAN_TB_u4MB_RXLABEL( CAN_MB129 ), CAN_TB_u4MB_RXKIND( 4, 129 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB129, CAN_CFG_ID_VALUE_4_MB129 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB130, CAN_TB_u4MB_RXLABEL( CAN_MB130 ), CAN_TB_u4MB_RXKIND( 4, 130 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB130, CAN_CFG_ID_VALUE_4_MB130 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB131, CAN_TB_u4MB_RXLABEL( CAN_MB131 ), CAN_TB_u4MB_RXKIND( 4, 131 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB131, CAN_CFG_ID_VALUE_4_MB131 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB132, CAN_TB_u4MB_RXLABEL( CAN_MB132 ), CAN_TB_u4MB_RXKIND( 4, 132 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB132, CAN_CFG_ID_VALUE_4_MB132 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB133, CAN_TB_u4MB_RXLABEL( CAN_MB133 ), CAN_TB_u4MB_RXKIND( 4, 133 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB133, CAN_CFG_ID_VALUE_4_MB133 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB134, CAN_TB_u4MB_RXLABEL( CAN_MB134 ), CAN_TB_u4MB_RXKIND( 4, 134 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB134, CAN_CFG_ID_VALUE_4_MB134 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB135, CAN_TB_u4MB_RXLABEL( CAN_MB135 ), CAN_TB_u4MB_RXKIND( 4, 135 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB135, CAN_CFG_ID_VALUE_4_MB135 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB136, CAN_TB_u4MB_RXLABEL( CAN_MB136 ), CAN_TB_u4MB_RXKIND( 4, 136 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB136, CAN_CFG_ID_VALUE_4_MB136 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB137, CAN_TB_u4MB_RXLABEL( CAN_MB137 ), CAN_TB_u4MB_RXKIND( 4, 137 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB137, CAN_CFG_ID_VALUE_4_MB137 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB138, CAN_TB_u4MB_RXLABEL( CAN_MB138 ), CAN_TB_u4MB_RXKIND( 4, 138 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB138, CAN_CFG_ID_VALUE_4_MB138 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB139, CAN_TB_u4MB_RXLABEL( CAN_MB139 ), CAN_TB_u4MB_RXKIND( 4, 139 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB139, CAN_CFG_ID_VALUE_4_MB139 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB140, CAN_TB_u4MB_RXLABEL( CAN_MB140 ), CAN_TB_u4MB_RXKIND( 4, 140 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB140, CAN_CFG_ID_VALUE_4_MB140 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB141, CAN_TB_u4MB_RXLABEL( CAN_MB141 ), CAN_TB_u4MB_RXKIND( 4, 141 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB141, CAN_CFG_ID_VALUE_4_MB141 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB142, CAN_TB_u4MB_RXLABEL( CAN_MB142 ), CAN_TB_u4MB_RXKIND( 4, 142 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB142, CAN_CFG_ID_VALUE_4_MB142 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB143, CAN_TB_u4MB_RXLABEL( CAN_MB143 ), CAN_TB_u4MB_RXKIND( 4, 143 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB143, CAN_CFG_ID_VALUE_4_MB143 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB144, CAN_TB_u4MB_RXLABEL( CAN_MB144 ), CAN_TB_u4MB_RXKIND( 4, 144 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB144, CAN_CFG_ID_VALUE_4_MB144 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB145, CAN_TB_u4MB_RXLABEL( CAN_MB145 ), CAN_TB_u4MB_RXKIND( 4, 145 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB145, CAN_CFG_ID_VALUE_4_MB145 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB146, CAN_TB_u4MB_RXLABEL( CAN_MB146 ), CAN_TB_u4MB_RXKIND( 4, 146 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB146, CAN_CFG_ID_VALUE_4_MB146 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB147, CAN_TB_u4MB_RXLABEL( CAN_MB147 ), CAN_TB_u4MB_RXKIND( 4, 147 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB147, CAN_CFG_ID_VALUE_4_MB147 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB148, CAN_TB_u4MB_RXLABEL( CAN_MB148 ), CAN_TB_u4MB_RXKIND( 4, 148 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB148, CAN_CFG_ID_VALUE_4_MB148 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB149, CAN_TB_u4MB_RXLABEL( CAN_MB149 ), CAN_TB_u4MB_RXKIND( 4, 149 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB149, CAN_CFG_ID_VALUE_4_MB149 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB150, CAN_TB_u4MB_RXLABEL( CAN_MB150 ), CAN_TB_u4MB_RXKIND( 4, 150 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB150, CAN_CFG_ID_VALUE_4_MB150 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB151, CAN_TB_u4MB_RXLABEL( CAN_MB151 ), CAN_TB_u4MB_RXKIND( 4, 151 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB151, CAN_CFG_ID_VALUE_4_MB151 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB152, CAN_TB_u4MB_RXLABEL( CAN_MB152 ), CAN_TB_u4MB_RXKIND( 4, 152 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB152, CAN_CFG_ID_VALUE_4_MB152 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB153, CAN_TB_u4MB_RXLABEL( CAN_MB153 ), CAN_TB_u4MB_RXKIND( 4, 153 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB153, CAN_CFG_ID_VALUE_4_MB153 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB154, CAN_TB_u4MB_RXLABEL( CAN_MB154 ), CAN_TB_u4MB_RXKIND( 4, 154 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB154, CAN_CFG_ID_VALUE_4_MB154 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB155, CAN_TB_u4MB_RXLABEL( CAN_MB155 ), CAN_TB_u4MB_RXKIND( 4, 155 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB155, CAN_CFG_ID_VALUE_4_MB155 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB156, CAN_TB_u4MB_RXLABEL( CAN_MB156 ), CAN_TB_u4MB_RXKIND( 4, 156 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB156, CAN_CFG_ID_VALUE_4_MB156 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB157, CAN_TB_u4MB_RXLABEL( CAN_MB157 ), CAN_TB_u4MB_RXKIND( 4, 157 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB157, CAN_CFG_ID_VALUE_4_MB157 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB158, CAN_TB_u4MB_RXLABEL( CAN_MB158 ), CAN_TB_u4MB_RXKIND( 4, 158 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB158, CAN_CFG_ID_VALUE_4_MB158 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB159, CAN_TB_u4MB_RXLABEL( CAN_MB159 ), CAN_TB_u4MB_RXKIND( 4, 159 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB159, CAN_CFG_ID_VALUE_4_MB159 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB160, CAN_TB_u4MB_RXLABEL( CAN_MB160 ), CAN_TB_u4MB_RXKIND( 4, 160 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB160, CAN_CFG_ID_VALUE_4_MB160 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB161, CAN_TB_u4MB_RXLABEL( CAN_MB161 ), CAN_TB_u4MB_RXKIND( 4, 161 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB161, CAN_CFG_ID_VALUE_4_MB161 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB162, CAN_TB_u4MB_RXLABEL( CAN_MB162 ), CAN_TB_u4MB_RXKIND( 4, 162 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB162, CAN_CFG_ID_VALUE_4_MB162 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB163, CAN_TB_u4MB_RXLABEL( CAN_MB163 ), CAN_TB_u4MB_RXKIND( 4, 163 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB163, CAN_CFG_ID_VALUE_4_MB163 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB164, CAN_TB_u4MB_RXLABEL( CAN_MB164 ), CAN_TB_u4MB_RXKIND( 4, 164 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB164, CAN_CFG_ID_VALUE_4_MB164 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB165, CAN_TB_u4MB_RXLABEL( CAN_MB165 ), CAN_TB_u4MB_RXKIND( 4, 165 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB165, CAN_CFG_ID_VALUE_4_MB165 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB166, CAN_TB_u4MB_RXLABEL( CAN_MB166 ), CAN_TB_u4MB_RXKIND( 4, 166 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB166, CAN_CFG_ID_VALUE_4_MB166 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB167, CAN_TB_u4MB_RXLABEL( CAN_MB167 ), CAN_TB_u4MB_RXKIND( 4, 167 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB167, CAN_CFG_ID_VALUE_4_MB167 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB168, CAN_TB_u4MB_RXLABEL( CAN_MB168 ), CAN_TB_u4MB_RXKIND( 4, 168 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB168, CAN_CFG_ID_VALUE_4_MB168 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB169, CAN_TB_u4MB_RXLABEL( CAN_MB169 ), CAN_TB_u4MB_RXKIND( 4, 169 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB169, CAN_CFG_ID_VALUE_4_MB169 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB170, CAN_TB_u4MB_RXLABEL( CAN_MB170 ), CAN_TB_u4MB_RXKIND( 4, 170 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB170, CAN_CFG_ID_VALUE_4_MB170 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB171, CAN_TB_u4MB_RXLABEL( CAN_MB171 ), CAN_TB_u4MB_RXKIND( 4, 171 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB171, CAN_CFG_ID_VALUE_4_MB171 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB172, CAN_TB_u4MB_RXLABEL( CAN_MB172 ), CAN_TB_u4MB_RXKIND( 4, 172 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB172, CAN_CFG_ID_VALUE_4_MB172 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB173, CAN_TB_u4MB_RXLABEL( CAN_MB173 ), CAN_TB_u4MB_RXKIND( 4, 173 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB173, CAN_CFG_ID_VALUE_4_MB173 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB174, CAN_TB_u4MB_RXLABEL( CAN_MB174 ), CAN_TB_u4MB_RXKIND( 4, 174 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB174, CAN_CFG_ID_VALUE_4_MB174 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB175, CAN_TB_u4MB_RXLABEL( CAN_MB175 ), CAN_TB_u4MB_RXKIND( 4, 175 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB175, CAN_CFG_ID_VALUE_4_MB175 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB176, CAN_TB_u4MB_RXLABEL( CAN_MB176 ), CAN_TB_u4MB_RXKIND( 4, 176 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB176, CAN_CFG_ID_VALUE_4_MB176 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB177, CAN_TB_u4MB_RXLABEL( CAN_MB177 ), CAN_TB_u4MB_RXKIND( 4, 177 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB177, CAN_CFG_ID_VALUE_4_MB177 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB178, CAN_TB_u4MB_RXLABEL( CAN_MB178 ), CAN_TB_u4MB_RXKIND( 4, 178 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB178, CAN_CFG_ID_VALUE_4_MB178 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB179, CAN_TB_u4MB_RXLABEL( CAN_MB179 ), CAN_TB_u4MB_RXKIND( 4, 179 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB179, CAN_CFG_ID_VALUE_4_MB179 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB180, CAN_TB_u4MB_RXLABEL( CAN_MB180 ), CAN_TB_u4MB_RXKIND( 4, 180 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB180, CAN_CFG_ID_VALUE_4_MB180 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB181, CAN_TB_u4MB_RXLABEL( CAN_MB181 ), CAN_TB_u4MB_RXKIND( 4, 181 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB181, CAN_CFG_ID_VALUE_4_MB181 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB182, CAN_TB_u4MB_RXLABEL( CAN_MB182 ), CAN_TB_u4MB_RXKIND( 4, 182 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB182, CAN_CFG_ID_VALUE_4_MB182 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB183, CAN_TB_u4MB_RXLABEL( CAN_MB183 ), CAN_TB_u4MB_RXKIND( 4, 183 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB183, CAN_CFG_ID_VALUE_4_MB183 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB184, CAN_TB_u4MB_RXLABEL( CAN_MB184 ), CAN_TB_u4MB_RXKIND( 4, 184 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB184, CAN_CFG_ID_VALUE_4_MB184 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB185, CAN_TB_u4MB_RXLABEL( CAN_MB185 ), CAN_TB_u4MB_RXKIND( 4, 185 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB185, CAN_CFG_ID_VALUE_4_MB185 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB186, CAN_TB_u4MB_RXLABEL( CAN_MB186 ), CAN_TB_u4MB_RXKIND( 4, 186 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB186, CAN_CFG_ID_VALUE_4_MB186 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB187, CAN_TB_u4MB_RXLABEL( CAN_MB187 ), CAN_TB_u4MB_RXKIND( 4, 187 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB187, CAN_CFG_ID_VALUE_4_MB187 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB188, CAN_TB_u4MB_RXLABEL( CAN_MB188 ), CAN_TB_u4MB_RXKIND( 4, 188 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB188, CAN_CFG_ID_VALUE_4_MB188 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB189, CAN_TB_u4MB_RXLABEL( CAN_MB189 ), CAN_TB_u4MB_RXKIND( 4, 189 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB189, CAN_CFG_ID_VALUE_4_MB189 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB190, CAN_TB_u4MB_RXLABEL( CAN_MB190 ), CAN_TB_u4MB_RXKIND( 4, 190 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB190, CAN_CFG_ID_VALUE_4_MB190 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_4_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_4_MB191, CAN_TB_u4MB_RXLABEL( CAN_MB191 ), CAN_TB_u4MB_RXKIND( 4, 191 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_4_MB191, CAN_CFG_ID_VALUE_4_MB191 ) },
#endif /* ( (CAN_CFG_MBOXSET_4_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */

    /* Controller 5 */
#if ( (CAN_CFG_MBOXSET_5_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB000, CAN_TB_u4MB_RXLABEL( CAN_MB000 ), CAN_TB_u4MB_RXKIND( 5, 000 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB000, CAN_CFG_ID_VALUE_5_MB000 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB001, CAN_TB_u4MB_RXLABEL( CAN_MB001 ), CAN_TB_u4MB_RXKIND( 5, 001 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB001, CAN_CFG_ID_VALUE_5_MB001 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB002, CAN_TB_u4MB_RXLABEL( CAN_MB002 ), CAN_TB_u4MB_RXKIND( 5, 002 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB002, CAN_CFG_ID_VALUE_5_MB002 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB003, CAN_TB_u4MB_RXLABEL( CAN_MB003 ), CAN_TB_u4MB_RXKIND( 5, 003 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB003, CAN_CFG_ID_VALUE_5_MB003 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB004, CAN_TB_u4MB_RXLABEL( CAN_MB004 ), CAN_TB_u4MB_RXKIND( 5, 004 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB004, CAN_CFG_ID_VALUE_5_MB004 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB005, CAN_TB_u4MB_RXLABEL( CAN_MB005 ), CAN_TB_u4MB_RXKIND( 5, 005 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB005, CAN_CFG_ID_VALUE_5_MB005 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB006, CAN_TB_u4MB_RXLABEL( CAN_MB006 ), CAN_TB_u4MB_RXKIND( 5, 006 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB006, CAN_CFG_ID_VALUE_5_MB006 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB007, CAN_TB_u4MB_RXLABEL( CAN_MB007 ), CAN_TB_u4MB_RXKIND( 5, 007 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB007, CAN_CFG_ID_VALUE_5_MB007 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB008, CAN_TB_u4MB_RXLABEL( CAN_MB008 ), CAN_TB_u4MB_RXKIND( 5, 008 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB008, CAN_CFG_ID_VALUE_5_MB008 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB009, CAN_TB_u4MB_RXLABEL( CAN_MB009 ), CAN_TB_u4MB_RXKIND( 5, 009 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB009, CAN_CFG_ID_VALUE_5_MB009 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB010, CAN_TB_u4MB_RXLABEL( CAN_MB010 ), CAN_TB_u4MB_RXKIND( 5, 010 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB010, CAN_CFG_ID_VALUE_5_MB010 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB011, CAN_TB_u4MB_RXLABEL( CAN_MB011 ), CAN_TB_u4MB_RXKIND( 5, 011 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB011, CAN_CFG_ID_VALUE_5_MB011 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB012, CAN_TB_u4MB_RXLABEL( CAN_MB012 ), CAN_TB_u4MB_RXKIND( 5, 012 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB012, CAN_CFG_ID_VALUE_5_MB012 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB013, CAN_TB_u4MB_RXLABEL( CAN_MB013 ), CAN_TB_u4MB_RXKIND( 5, 013 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB013, CAN_CFG_ID_VALUE_5_MB013 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB014, CAN_TB_u4MB_RXLABEL( CAN_MB014 ), CAN_TB_u4MB_RXKIND( 5, 014 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB014, CAN_CFG_ID_VALUE_5_MB014 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB015, CAN_TB_u4MB_RXLABEL( CAN_MB015 ), CAN_TB_u4MB_RXKIND( 5, 015 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB015, CAN_CFG_ID_VALUE_5_MB015 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB016, CAN_TB_u4MB_RXLABEL( CAN_MB016 ), CAN_TB_u4MB_RXKIND( 5, 016 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB016, CAN_CFG_ID_VALUE_5_MB016 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB017, CAN_TB_u4MB_RXLABEL( CAN_MB017 ), CAN_TB_u4MB_RXKIND( 5, 017 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB017, CAN_CFG_ID_VALUE_5_MB017 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB018, CAN_TB_u4MB_RXLABEL( CAN_MB018 ), CAN_TB_u4MB_RXKIND( 5, 018 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB018, CAN_CFG_ID_VALUE_5_MB018 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB019, CAN_TB_u4MB_RXLABEL( CAN_MB019 ), CAN_TB_u4MB_RXKIND( 5, 019 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB019, CAN_CFG_ID_VALUE_5_MB019 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB020, CAN_TB_u4MB_RXLABEL( CAN_MB020 ), CAN_TB_u4MB_RXKIND( 5, 020 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB020, CAN_CFG_ID_VALUE_5_MB020 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB021, CAN_TB_u4MB_RXLABEL( CAN_MB021 ), CAN_TB_u4MB_RXKIND( 5, 021 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB021, CAN_CFG_ID_VALUE_5_MB021 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB022, CAN_TB_u4MB_RXLABEL( CAN_MB022 ), CAN_TB_u4MB_RXKIND( 5, 022 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB022, CAN_CFG_ID_VALUE_5_MB022 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB023, CAN_TB_u4MB_RXLABEL( CAN_MB023 ), CAN_TB_u4MB_RXKIND( 5, 023 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB023, CAN_CFG_ID_VALUE_5_MB023 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB024, CAN_TB_u4MB_RXLABEL( CAN_MB024 ), CAN_TB_u4MB_RXKIND( 5, 024 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB024, CAN_CFG_ID_VALUE_5_MB024 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB025, CAN_TB_u4MB_RXLABEL( CAN_MB025 ), CAN_TB_u4MB_RXKIND( 5, 025 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB025, CAN_CFG_ID_VALUE_5_MB025 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB026, CAN_TB_u4MB_RXLABEL( CAN_MB026 ), CAN_TB_u4MB_RXKIND( 5, 026 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB026, CAN_CFG_ID_VALUE_5_MB026 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB027, CAN_TB_u4MB_RXLABEL( CAN_MB027 ), CAN_TB_u4MB_RXKIND( 5, 027 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB027, CAN_CFG_ID_VALUE_5_MB027 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB028, CAN_TB_u4MB_RXLABEL( CAN_MB028 ), CAN_TB_u4MB_RXKIND( 5, 028 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB028, CAN_CFG_ID_VALUE_5_MB028 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB029, CAN_TB_u4MB_RXLABEL( CAN_MB029 ), CAN_TB_u4MB_RXKIND( 5, 029 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB029, CAN_CFG_ID_VALUE_5_MB029 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB030, CAN_TB_u4MB_RXLABEL( CAN_MB030 ), CAN_TB_u4MB_RXKIND( 5, 030 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB030, CAN_CFG_ID_VALUE_5_MB030 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB031, CAN_TB_u4MB_RXLABEL( CAN_MB031 ), CAN_TB_u4MB_RXKIND( 5, 031 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB031, CAN_CFG_ID_VALUE_5_MB031 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB032, CAN_TB_u4MB_RXLABEL( CAN_MB032 ), CAN_TB_u4MB_RXKIND( 5, 032 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB032, CAN_CFG_ID_VALUE_5_MB032 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB033, CAN_TB_u4MB_RXLABEL( CAN_MB033 ), CAN_TB_u4MB_RXKIND( 5, 033 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB033, CAN_CFG_ID_VALUE_5_MB033 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB034, CAN_TB_u4MB_RXLABEL( CAN_MB034 ), CAN_TB_u4MB_RXKIND( 5, 034 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB034, CAN_CFG_ID_VALUE_5_MB034 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB035, CAN_TB_u4MB_RXLABEL( CAN_MB035 ), CAN_TB_u4MB_RXKIND( 5, 035 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB035, CAN_CFG_ID_VALUE_5_MB035 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB036, CAN_TB_u4MB_RXLABEL( CAN_MB036 ), CAN_TB_u4MB_RXKIND( 5, 036 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB036, CAN_CFG_ID_VALUE_5_MB036 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB037, CAN_TB_u4MB_RXLABEL( CAN_MB037 ), CAN_TB_u4MB_RXKIND( 5, 037 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB037, CAN_CFG_ID_VALUE_5_MB037 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB038, CAN_TB_u4MB_RXLABEL( CAN_MB038 ), CAN_TB_u4MB_RXKIND( 5, 038 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB038, CAN_CFG_ID_VALUE_5_MB038 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB039, CAN_TB_u4MB_RXLABEL( CAN_MB039 ), CAN_TB_u4MB_RXKIND( 5, 039 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB039, CAN_CFG_ID_VALUE_5_MB039 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB040, CAN_TB_u4MB_RXLABEL( CAN_MB040 ), CAN_TB_u4MB_RXKIND( 5, 040 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB040, CAN_CFG_ID_VALUE_5_MB040 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB041, CAN_TB_u4MB_RXLABEL( CAN_MB041 ), CAN_TB_u4MB_RXKIND( 5, 041 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB041, CAN_CFG_ID_VALUE_5_MB041 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB042, CAN_TB_u4MB_RXLABEL( CAN_MB042 ), CAN_TB_u4MB_RXKIND( 5, 042 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB042, CAN_CFG_ID_VALUE_5_MB042 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB043, CAN_TB_u4MB_RXLABEL( CAN_MB043 ), CAN_TB_u4MB_RXKIND( 5, 043 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB043, CAN_CFG_ID_VALUE_5_MB043 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB044, CAN_TB_u4MB_RXLABEL( CAN_MB044 ), CAN_TB_u4MB_RXKIND( 5, 044 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB044, CAN_CFG_ID_VALUE_5_MB044 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB045, CAN_TB_u4MB_RXLABEL( CAN_MB045 ), CAN_TB_u4MB_RXKIND( 5, 045 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB045, CAN_CFG_ID_VALUE_5_MB045 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB046, CAN_TB_u4MB_RXLABEL( CAN_MB046 ), CAN_TB_u4MB_RXKIND( 5, 046 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB046, CAN_CFG_ID_VALUE_5_MB046 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB047, CAN_TB_u4MB_RXLABEL( CAN_MB047 ), CAN_TB_u4MB_RXKIND( 5, 047 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB047, CAN_CFG_ID_VALUE_5_MB047 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB048, CAN_TB_u4MB_RXLABEL( CAN_MB048 ), CAN_TB_u4MB_RXKIND( 5, 048 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB048, CAN_CFG_ID_VALUE_5_MB048 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB049, CAN_TB_u4MB_RXLABEL( CAN_MB049 ), CAN_TB_u4MB_RXKIND( 5, 049 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB049, CAN_CFG_ID_VALUE_5_MB049 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB050, CAN_TB_u4MB_RXLABEL( CAN_MB050 ), CAN_TB_u4MB_RXKIND( 5, 050 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB050, CAN_CFG_ID_VALUE_5_MB050 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB051, CAN_TB_u4MB_RXLABEL( CAN_MB051 ), CAN_TB_u4MB_RXKIND( 5, 051 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB051, CAN_CFG_ID_VALUE_5_MB051 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB052, CAN_TB_u4MB_RXLABEL( CAN_MB052 ), CAN_TB_u4MB_RXKIND( 5, 052 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB052, CAN_CFG_ID_VALUE_5_MB052 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB053, CAN_TB_u4MB_RXLABEL( CAN_MB053 ), CAN_TB_u4MB_RXKIND( 5, 053 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB053, CAN_CFG_ID_VALUE_5_MB053 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB054, CAN_TB_u4MB_RXLABEL( CAN_MB054 ), CAN_TB_u4MB_RXKIND( 5, 054 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB054, CAN_CFG_ID_VALUE_5_MB054 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB055, CAN_TB_u4MB_RXLABEL( CAN_MB055 ), CAN_TB_u4MB_RXKIND( 5, 055 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB055, CAN_CFG_ID_VALUE_5_MB055 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB056, CAN_TB_u4MB_RXLABEL( CAN_MB056 ), CAN_TB_u4MB_RXKIND( 5, 056 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB056, CAN_CFG_ID_VALUE_5_MB056 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB057, CAN_TB_u4MB_RXLABEL( CAN_MB057 ), CAN_TB_u4MB_RXKIND( 5, 057 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB057, CAN_CFG_ID_VALUE_5_MB057 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB058, CAN_TB_u4MB_RXLABEL( CAN_MB058 ), CAN_TB_u4MB_RXKIND( 5, 058 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB058, CAN_CFG_ID_VALUE_5_MB058 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB059, CAN_TB_u4MB_RXLABEL( CAN_MB059 ), CAN_TB_u4MB_RXKIND( 5, 059 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB059, CAN_CFG_ID_VALUE_5_MB059 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB060, CAN_TB_u4MB_RXLABEL( CAN_MB060 ), CAN_TB_u4MB_RXKIND( 5, 060 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB060, CAN_CFG_ID_VALUE_5_MB060 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB061, CAN_TB_u4MB_RXLABEL( CAN_MB061 ), CAN_TB_u4MB_RXKIND( 5, 061 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB061, CAN_CFG_ID_VALUE_5_MB061 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB062, CAN_TB_u4MB_RXLABEL( CAN_MB062 ), CAN_TB_u4MB_RXKIND( 5, 062 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB062, CAN_CFG_ID_VALUE_5_MB062 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB063, CAN_TB_u4MB_RXLABEL( CAN_MB063 ), CAN_TB_u4MB_RXKIND( 5, 063 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB063, CAN_CFG_ID_VALUE_5_MB063 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB064, CAN_TB_u4MB_RXLABEL( CAN_MB064 ), CAN_TB_u4MB_RXKIND( 5, 064 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB064, CAN_CFG_ID_VALUE_5_MB064 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB065, CAN_TB_u4MB_RXLABEL( CAN_MB065 ), CAN_TB_u4MB_RXKIND( 5, 065 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB065, CAN_CFG_ID_VALUE_5_MB065 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB066, CAN_TB_u4MB_RXLABEL( CAN_MB066 ), CAN_TB_u4MB_RXKIND( 5, 066 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB066, CAN_CFG_ID_VALUE_5_MB066 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB067, CAN_TB_u4MB_RXLABEL( CAN_MB067 ), CAN_TB_u4MB_RXKIND( 5, 067 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB067, CAN_CFG_ID_VALUE_5_MB067 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB068, CAN_TB_u4MB_RXLABEL( CAN_MB068 ), CAN_TB_u4MB_RXKIND( 5, 068 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB068, CAN_CFG_ID_VALUE_5_MB068 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB069, CAN_TB_u4MB_RXLABEL( CAN_MB069 ), CAN_TB_u4MB_RXKIND( 5, 069 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB069, CAN_CFG_ID_VALUE_5_MB069 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB070, CAN_TB_u4MB_RXLABEL( CAN_MB070 ), CAN_TB_u4MB_RXKIND( 5, 070 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB070, CAN_CFG_ID_VALUE_5_MB070 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB071, CAN_TB_u4MB_RXLABEL( CAN_MB071 ), CAN_TB_u4MB_RXKIND( 5, 071 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB071, CAN_CFG_ID_VALUE_5_MB071 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB072, CAN_TB_u4MB_RXLABEL( CAN_MB072 ), CAN_TB_u4MB_RXKIND( 5, 072 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB072, CAN_CFG_ID_VALUE_5_MB072 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB073, CAN_TB_u4MB_RXLABEL( CAN_MB073 ), CAN_TB_u4MB_RXKIND( 5, 073 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB073, CAN_CFG_ID_VALUE_5_MB073 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB074, CAN_TB_u4MB_RXLABEL( CAN_MB074 ), CAN_TB_u4MB_RXKIND( 5, 074 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB074, CAN_CFG_ID_VALUE_5_MB074 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB075, CAN_TB_u4MB_RXLABEL( CAN_MB075 ), CAN_TB_u4MB_RXKIND( 5, 075 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB075, CAN_CFG_ID_VALUE_5_MB075 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB076, CAN_TB_u4MB_RXLABEL( CAN_MB076 ), CAN_TB_u4MB_RXKIND( 5, 076 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB076, CAN_CFG_ID_VALUE_5_MB076 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB077, CAN_TB_u4MB_RXLABEL( CAN_MB077 ), CAN_TB_u4MB_RXKIND( 5, 077 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB077, CAN_CFG_ID_VALUE_5_MB077 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB078, CAN_TB_u4MB_RXLABEL( CAN_MB078 ), CAN_TB_u4MB_RXKIND( 5, 078 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB078, CAN_CFG_ID_VALUE_5_MB078 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB079, CAN_TB_u4MB_RXLABEL( CAN_MB079 ), CAN_TB_u4MB_RXKIND( 5, 079 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB079, CAN_CFG_ID_VALUE_5_MB079 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB080, CAN_TB_u4MB_RXLABEL( CAN_MB080 ), CAN_TB_u4MB_RXKIND( 5, 080 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB080, CAN_CFG_ID_VALUE_5_MB080 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB081, CAN_TB_u4MB_RXLABEL( CAN_MB081 ), CAN_TB_u4MB_RXKIND( 5, 081 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB081, CAN_CFG_ID_VALUE_5_MB081 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB082, CAN_TB_u4MB_RXLABEL( CAN_MB082 ), CAN_TB_u4MB_RXKIND( 5, 082 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB082, CAN_CFG_ID_VALUE_5_MB082 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB083, CAN_TB_u4MB_RXLABEL( CAN_MB083 ), CAN_TB_u4MB_RXKIND( 5, 083 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB083, CAN_CFG_ID_VALUE_5_MB083 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB084, CAN_TB_u4MB_RXLABEL( CAN_MB084 ), CAN_TB_u4MB_RXKIND( 5, 084 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB084, CAN_CFG_ID_VALUE_5_MB084 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB085, CAN_TB_u4MB_RXLABEL( CAN_MB085 ), CAN_TB_u4MB_RXKIND( 5, 085 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB085, CAN_CFG_ID_VALUE_5_MB085 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB086, CAN_TB_u4MB_RXLABEL( CAN_MB086 ), CAN_TB_u4MB_RXKIND( 5, 086 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB086, CAN_CFG_ID_VALUE_5_MB086 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB087, CAN_TB_u4MB_RXLABEL( CAN_MB087 ), CAN_TB_u4MB_RXKIND( 5, 087 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB087, CAN_CFG_ID_VALUE_5_MB087 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB088, CAN_TB_u4MB_RXLABEL( CAN_MB088 ), CAN_TB_u4MB_RXKIND( 5, 088 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB088, CAN_CFG_ID_VALUE_5_MB088 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB089, CAN_TB_u4MB_RXLABEL( CAN_MB089 ), CAN_TB_u4MB_RXKIND( 5, 089 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB089, CAN_CFG_ID_VALUE_5_MB089 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB090, CAN_TB_u4MB_RXLABEL( CAN_MB090 ), CAN_TB_u4MB_RXKIND( 5, 090 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB090, CAN_CFG_ID_VALUE_5_MB090 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB091, CAN_TB_u4MB_RXLABEL( CAN_MB091 ), CAN_TB_u4MB_RXKIND( 5, 091 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB091, CAN_CFG_ID_VALUE_5_MB091 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB092, CAN_TB_u4MB_RXLABEL( CAN_MB092 ), CAN_TB_u4MB_RXKIND( 5, 092 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB092, CAN_CFG_ID_VALUE_5_MB092 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB093, CAN_TB_u4MB_RXLABEL( CAN_MB093 ), CAN_TB_u4MB_RXKIND( 5, 093 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB093, CAN_CFG_ID_VALUE_5_MB093 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB094, CAN_TB_u4MB_RXLABEL( CAN_MB094 ), CAN_TB_u4MB_RXKIND( 5, 094 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB094, CAN_CFG_ID_VALUE_5_MB094 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB095, CAN_TB_u4MB_RXLABEL( CAN_MB095 ), CAN_TB_u4MB_RXKIND( 5, 095 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB095, CAN_CFG_ID_VALUE_5_MB095 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB096, CAN_TB_u4MB_RXLABEL( CAN_MB096 ), CAN_TB_u4MB_RXKIND( 5, 096 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB096, CAN_CFG_ID_VALUE_5_MB096 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB097, CAN_TB_u4MB_RXLABEL( CAN_MB097 ), CAN_TB_u4MB_RXKIND( 5, 097 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB097, CAN_CFG_ID_VALUE_5_MB097 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB098, CAN_TB_u4MB_RXLABEL( CAN_MB098 ), CAN_TB_u4MB_RXKIND( 5, 098 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB098, CAN_CFG_ID_VALUE_5_MB098 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB099, CAN_TB_u4MB_RXLABEL( CAN_MB099 ), CAN_TB_u4MB_RXKIND( 5, 099 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB099, CAN_CFG_ID_VALUE_5_MB099 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB100, CAN_TB_u4MB_RXLABEL( CAN_MB100 ), CAN_TB_u4MB_RXKIND( 5, 100 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB100, CAN_CFG_ID_VALUE_5_MB100 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB101, CAN_TB_u4MB_RXLABEL( CAN_MB101 ), CAN_TB_u4MB_RXKIND( 5, 101 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB101, CAN_CFG_ID_VALUE_5_MB101 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB102, CAN_TB_u4MB_RXLABEL( CAN_MB102 ), CAN_TB_u4MB_RXKIND( 5, 102 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB102, CAN_CFG_ID_VALUE_5_MB102 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB103, CAN_TB_u4MB_RXLABEL( CAN_MB103 ), CAN_TB_u4MB_RXKIND( 5, 103 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB103, CAN_CFG_ID_VALUE_5_MB103 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB104, CAN_TB_u4MB_RXLABEL( CAN_MB104 ), CAN_TB_u4MB_RXKIND( 5, 104 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB104, CAN_CFG_ID_VALUE_5_MB104 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB105, CAN_TB_u4MB_RXLABEL( CAN_MB105 ), CAN_TB_u4MB_RXKIND( 5, 105 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB105, CAN_CFG_ID_VALUE_5_MB105 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB106, CAN_TB_u4MB_RXLABEL( CAN_MB106 ), CAN_TB_u4MB_RXKIND( 5, 106 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB106, CAN_CFG_ID_VALUE_5_MB106 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB107, CAN_TB_u4MB_RXLABEL( CAN_MB107 ), CAN_TB_u4MB_RXKIND( 5, 107 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB107, CAN_CFG_ID_VALUE_5_MB107 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB108, CAN_TB_u4MB_RXLABEL( CAN_MB108 ), CAN_TB_u4MB_RXKIND( 5, 108 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB108, CAN_CFG_ID_VALUE_5_MB108 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB109, CAN_TB_u4MB_RXLABEL( CAN_MB109 ), CAN_TB_u4MB_RXKIND( 5, 109 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB109, CAN_CFG_ID_VALUE_5_MB109 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB110, CAN_TB_u4MB_RXLABEL( CAN_MB110 ), CAN_TB_u4MB_RXKIND( 5, 110 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB110, CAN_CFG_ID_VALUE_5_MB110 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB111, CAN_TB_u4MB_RXLABEL( CAN_MB111 ), CAN_TB_u4MB_RXKIND( 5, 111 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB111, CAN_CFG_ID_VALUE_5_MB111 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB112, CAN_TB_u4MB_RXLABEL( CAN_MB112 ), CAN_TB_u4MB_RXKIND( 5, 112 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB112, CAN_CFG_ID_VALUE_5_MB112 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB113, CAN_TB_u4MB_RXLABEL( CAN_MB113 ), CAN_TB_u4MB_RXKIND( 5, 113 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB113, CAN_CFG_ID_VALUE_5_MB113 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB114, CAN_TB_u4MB_RXLABEL( CAN_MB114 ), CAN_TB_u4MB_RXKIND( 5, 114 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB114, CAN_CFG_ID_VALUE_5_MB114 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB115, CAN_TB_u4MB_RXLABEL( CAN_MB115 ), CAN_TB_u4MB_RXKIND( 5, 115 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB115, CAN_CFG_ID_VALUE_5_MB115 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB116, CAN_TB_u4MB_RXLABEL( CAN_MB116 ), CAN_TB_u4MB_RXKIND( 5, 116 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB116, CAN_CFG_ID_VALUE_5_MB116 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB117, CAN_TB_u4MB_RXLABEL( CAN_MB117 ), CAN_TB_u4MB_RXKIND( 5, 117 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB117, CAN_CFG_ID_VALUE_5_MB117 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB118, CAN_TB_u4MB_RXLABEL( CAN_MB118 ), CAN_TB_u4MB_RXKIND( 5, 118 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB118, CAN_CFG_ID_VALUE_5_MB118 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB119, CAN_TB_u4MB_RXLABEL( CAN_MB119 ), CAN_TB_u4MB_RXKIND( 5, 119 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB119, CAN_CFG_ID_VALUE_5_MB119 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB120, CAN_TB_u4MB_RXLABEL( CAN_MB120 ), CAN_TB_u4MB_RXKIND( 5, 120 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB120, CAN_CFG_ID_VALUE_5_MB120 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB121, CAN_TB_u4MB_RXLABEL( CAN_MB121 ), CAN_TB_u4MB_RXKIND( 5, 121 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB121, CAN_CFG_ID_VALUE_5_MB121 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB122, CAN_TB_u4MB_RXLABEL( CAN_MB122 ), CAN_TB_u4MB_RXKIND( 5, 122 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB122, CAN_CFG_ID_VALUE_5_MB122 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB123, CAN_TB_u4MB_RXLABEL( CAN_MB123 ), CAN_TB_u4MB_RXKIND( 5, 123 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB123, CAN_CFG_ID_VALUE_5_MB123 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB124, CAN_TB_u4MB_RXLABEL( CAN_MB124 ), CAN_TB_u4MB_RXKIND( 5, 124 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB124, CAN_CFG_ID_VALUE_5_MB124 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB125, CAN_TB_u4MB_RXLABEL( CAN_MB125 ), CAN_TB_u4MB_RXKIND( 5, 125 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB125, CAN_CFG_ID_VALUE_5_MB125 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB126, CAN_TB_u4MB_RXLABEL( CAN_MB126 ), CAN_TB_u4MB_RXKIND( 5, 126 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB126, CAN_CFG_ID_VALUE_5_MB126 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB127, CAN_TB_u4MB_RXLABEL( CAN_MB127 ), CAN_TB_u4MB_RXKIND( 5, 127 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB127, CAN_CFG_ID_VALUE_5_MB127 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB128, CAN_TB_u4MB_RXLABEL( CAN_MB128 ), CAN_TB_u4MB_RXKIND( 5, 128 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB128, CAN_CFG_ID_VALUE_5_MB128 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB129, CAN_TB_u4MB_RXLABEL( CAN_MB129 ), CAN_TB_u4MB_RXKIND( 5, 129 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB129, CAN_CFG_ID_VALUE_5_MB129 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB130, CAN_TB_u4MB_RXLABEL( CAN_MB130 ), CAN_TB_u4MB_RXKIND( 5, 130 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB130, CAN_CFG_ID_VALUE_5_MB130 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB131, CAN_TB_u4MB_RXLABEL( CAN_MB131 ), CAN_TB_u4MB_RXKIND( 5, 131 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB131, CAN_CFG_ID_VALUE_5_MB131 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB132, CAN_TB_u4MB_RXLABEL( CAN_MB132 ), CAN_TB_u4MB_RXKIND( 5, 132 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB132, CAN_CFG_ID_VALUE_5_MB132 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB133, CAN_TB_u4MB_RXLABEL( CAN_MB133 ), CAN_TB_u4MB_RXKIND( 5, 133 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB133, CAN_CFG_ID_VALUE_5_MB133 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB134, CAN_TB_u4MB_RXLABEL( CAN_MB134 ), CAN_TB_u4MB_RXKIND( 5, 134 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB134, CAN_CFG_ID_VALUE_5_MB134 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB135, CAN_TB_u4MB_RXLABEL( CAN_MB135 ), CAN_TB_u4MB_RXKIND( 5, 135 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB135, CAN_CFG_ID_VALUE_5_MB135 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB136, CAN_TB_u4MB_RXLABEL( CAN_MB136 ), CAN_TB_u4MB_RXKIND( 5, 136 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB136, CAN_CFG_ID_VALUE_5_MB136 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB137, CAN_TB_u4MB_RXLABEL( CAN_MB137 ), CAN_TB_u4MB_RXKIND( 5, 137 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB137, CAN_CFG_ID_VALUE_5_MB137 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB138, CAN_TB_u4MB_RXLABEL( CAN_MB138 ), CAN_TB_u4MB_RXKIND( 5, 138 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB138, CAN_CFG_ID_VALUE_5_MB138 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB139, CAN_TB_u4MB_RXLABEL( CAN_MB139 ), CAN_TB_u4MB_RXKIND( 5, 139 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB139, CAN_CFG_ID_VALUE_5_MB139 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB140, CAN_TB_u4MB_RXLABEL( CAN_MB140 ), CAN_TB_u4MB_RXKIND( 5, 140 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB140, CAN_CFG_ID_VALUE_5_MB140 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB141, CAN_TB_u4MB_RXLABEL( CAN_MB141 ), CAN_TB_u4MB_RXKIND( 5, 141 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB141, CAN_CFG_ID_VALUE_5_MB141 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB142, CAN_TB_u4MB_RXLABEL( CAN_MB142 ), CAN_TB_u4MB_RXKIND( 5, 142 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB142, CAN_CFG_ID_VALUE_5_MB142 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB143, CAN_TB_u4MB_RXLABEL( CAN_MB143 ), CAN_TB_u4MB_RXKIND( 5, 143 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB143, CAN_CFG_ID_VALUE_5_MB143 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB144, CAN_TB_u4MB_RXLABEL( CAN_MB144 ), CAN_TB_u4MB_RXKIND( 5, 144 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB144, CAN_CFG_ID_VALUE_5_MB144 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB145, CAN_TB_u4MB_RXLABEL( CAN_MB145 ), CAN_TB_u4MB_RXKIND( 5, 145 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB145, CAN_CFG_ID_VALUE_5_MB145 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB146, CAN_TB_u4MB_RXLABEL( CAN_MB146 ), CAN_TB_u4MB_RXKIND( 5, 146 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB146, CAN_CFG_ID_VALUE_5_MB146 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB147, CAN_TB_u4MB_RXLABEL( CAN_MB147 ), CAN_TB_u4MB_RXKIND( 5, 147 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB147, CAN_CFG_ID_VALUE_5_MB147 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB148, CAN_TB_u4MB_RXLABEL( CAN_MB148 ), CAN_TB_u4MB_RXKIND( 5, 148 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB148, CAN_CFG_ID_VALUE_5_MB148 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB149, CAN_TB_u4MB_RXLABEL( CAN_MB149 ), CAN_TB_u4MB_RXKIND( 5, 149 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB149, CAN_CFG_ID_VALUE_5_MB149 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB150, CAN_TB_u4MB_RXLABEL( CAN_MB150 ), CAN_TB_u4MB_RXKIND( 5, 150 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB150, CAN_CFG_ID_VALUE_5_MB150 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB151, CAN_TB_u4MB_RXLABEL( CAN_MB151 ), CAN_TB_u4MB_RXKIND( 5, 151 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB151, CAN_CFG_ID_VALUE_5_MB151 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB152, CAN_TB_u4MB_RXLABEL( CAN_MB152 ), CAN_TB_u4MB_RXKIND( 5, 152 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB152, CAN_CFG_ID_VALUE_5_MB152 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB153, CAN_TB_u4MB_RXLABEL( CAN_MB153 ), CAN_TB_u4MB_RXKIND( 5, 153 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB153, CAN_CFG_ID_VALUE_5_MB153 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB154, CAN_TB_u4MB_RXLABEL( CAN_MB154 ), CAN_TB_u4MB_RXKIND( 5, 154 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB154, CAN_CFG_ID_VALUE_5_MB154 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB155, CAN_TB_u4MB_RXLABEL( CAN_MB155 ), CAN_TB_u4MB_RXKIND( 5, 155 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB155, CAN_CFG_ID_VALUE_5_MB155 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB156, CAN_TB_u4MB_RXLABEL( CAN_MB156 ), CAN_TB_u4MB_RXKIND( 5, 156 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB156, CAN_CFG_ID_VALUE_5_MB156 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB157, CAN_TB_u4MB_RXLABEL( CAN_MB157 ), CAN_TB_u4MB_RXKIND( 5, 157 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB157, CAN_CFG_ID_VALUE_5_MB157 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB158, CAN_TB_u4MB_RXLABEL( CAN_MB158 ), CAN_TB_u4MB_RXKIND( 5, 158 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB158, CAN_CFG_ID_VALUE_5_MB158 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB159, CAN_TB_u4MB_RXLABEL( CAN_MB159 ), CAN_TB_u4MB_RXKIND( 5, 159 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB159, CAN_CFG_ID_VALUE_5_MB159 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB160, CAN_TB_u4MB_RXLABEL( CAN_MB160 ), CAN_TB_u4MB_RXKIND( 5, 160 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB160, CAN_CFG_ID_VALUE_5_MB160 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB161, CAN_TB_u4MB_RXLABEL( CAN_MB161 ), CAN_TB_u4MB_RXKIND( 5, 161 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB161, CAN_CFG_ID_VALUE_5_MB161 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB162, CAN_TB_u4MB_RXLABEL( CAN_MB162 ), CAN_TB_u4MB_RXKIND( 5, 162 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB162, CAN_CFG_ID_VALUE_5_MB162 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB163, CAN_TB_u4MB_RXLABEL( CAN_MB163 ), CAN_TB_u4MB_RXKIND( 5, 163 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB163, CAN_CFG_ID_VALUE_5_MB163 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB164, CAN_TB_u4MB_RXLABEL( CAN_MB164 ), CAN_TB_u4MB_RXKIND( 5, 164 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB164, CAN_CFG_ID_VALUE_5_MB164 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB165, CAN_TB_u4MB_RXLABEL( CAN_MB165 ), CAN_TB_u4MB_RXKIND( 5, 165 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB165, CAN_CFG_ID_VALUE_5_MB165 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB166, CAN_TB_u4MB_RXLABEL( CAN_MB166 ), CAN_TB_u4MB_RXKIND( 5, 166 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB166, CAN_CFG_ID_VALUE_5_MB166 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB167, CAN_TB_u4MB_RXLABEL( CAN_MB167 ), CAN_TB_u4MB_RXKIND( 5, 167 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB167, CAN_CFG_ID_VALUE_5_MB167 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB168, CAN_TB_u4MB_RXLABEL( CAN_MB168 ), CAN_TB_u4MB_RXKIND( 5, 168 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB168, CAN_CFG_ID_VALUE_5_MB168 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB169, CAN_TB_u4MB_RXLABEL( CAN_MB169 ), CAN_TB_u4MB_RXKIND( 5, 169 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB169, CAN_CFG_ID_VALUE_5_MB169 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB170, CAN_TB_u4MB_RXLABEL( CAN_MB170 ), CAN_TB_u4MB_RXKIND( 5, 170 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB170, CAN_CFG_ID_VALUE_5_MB170 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB171, CAN_TB_u4MB_RXLABEL( CAN_MB171 ), CAN_TB_u4MB_RXKIND( 5, 171 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB171, CAN_CFG_ID_VALUE_5_MB171 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB172, CAN_TB_u4MB_RXLABEL( CAN_MB172 ), CAN_TB_u4MB_RXKIND( 5, 172 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB172, CAN_CFG_ID_VALUE_5_MB172 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB173, CAN_TB_u4MB_RXLABEL( CAN_MB173 ), CAN_TB_u4MB_RXKIND( 5, 173 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB173, CAN_CFG_ID_VALUE_5_MB173 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB174, CAN_TB_u4MB_RXLABEL( CAN_MB174 ), CAN_TB_u4MB_RXKIND( 5, 174 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB174, CAN_CFG_ID_VALUE_5_MB174 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB175, CAN_TB_u4MB_RXLABEL( CAN_MB175 ), CAN_TB_u4MB_RXKIND( 5, 175 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB175, CAN_CFG_ID_VALUE_5_MB175 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB176, CAN_TB_u4MB_RXLABEL( CAN_MB176 ), CAN_TB_u4MB_RXKIND( 5, 176 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB176, CAN_CFG_ID_VALUE_5_MB176 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB177, CAN_TB_u4MB_RXLABEL( CAN_MB177 ), CAN_TB_u4MB_RXKIND( 5, 177 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB177, CAN_CFG_ID_VALUE_5_MB177 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB178, CAN_TB_u4MB_RXLABEL( CAN_MB178 ), CAN_TB_u4MB_RXKIND( 5, 178 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB178, CAN_CFG_ID_VALUE_5_MB178 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB179, CAN_TB_u4MB_RXLABEL( CAN_MB179 ), CAN_TB_u4MB_RXKIND( 5, 179 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB179, CAN_CFG_ID_VALUE_5_MB179 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB180, CAN_TB_u4MB_RXLABEL( CAN_MB180 ), CAN_TB_u4MB_RXKIND( 5, 180 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB180, CAN_CFG_ID_VALUE_5_MB180 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB181, CAN_TB_u4MB_RXLABEL( CAN_MB181 ), CAN_TB_u4MB_RXKIND( 5, 181 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB181, CAN_CFG_ID_VALUE_5_MB181 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB182, CAN_TB_u4MB_RXLABEL( CAN_MB182 ), CAN_TB_u4MB_RXKIND( 5, 182 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB182, CAN_CFG_ID_VALUE_5_MB182 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB183, CAN_TB_u4MB_RXLABEL( CAN_MB183 ), CAN_TB_u4MB_RXKIND( 5, 183 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB183, CAN_CFG_ID_VALUE_5_MB183 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB184, CAN_TB_u4MB_RXLABEL( CAN_MB184 ), CAN_TB_u4MB_RXKIND( 5, 184 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB184, CAN_CFG_ID_VALUE_5_MB184 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB185, CAN_TB_u4MB_RXLABEL( CAN_MB185 ), CAN_TB_u4MB_RXKIND( 5, 185 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB185, CAN_CFG_ID_VALUE_5_MB185 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB186, CAN_TB_u4MB_RXLABEL( CAN_MB186 ), CAN_TB_u4MB_RXKIND( 5, 186 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB186, CAN_CFG_ID_VALUE_5_MB186 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB187, CAN_TB_u4MB_RXLABEL( CAN_MB187 ), CAN_TB_u4MB_RXKIND( 5, 187 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB187, CAN_CFG_ID_VALUE_5_MB187 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB188, CAN_TB_u4MB_RXLABEL( CAN_MB188 ), CAN_TB_u4MB_RXKIND( 5, 188 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB188, CAN_CFG_ID_VALUE_5_MB188 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB189, CAN_TB_u4MB_RXLABEL( CAN_MB189 ), CAN_TB_u4MB_RXKIND( 5, 189 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB189, CAN_CFG_ID_VALUE_5_MB189 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB190, CAN_TB_u4MB_RXLABEL( CAN_MB190 ), CAN_TB_u4MB_RXKIND( 5, 190 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB190, CAN_CFG_ID_VALUE_5_MB190 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_5_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_5_MB191, CAN_TB_u4MB_RXLABEL( CAN_MB191 ), CAN_TB_u4MB_RXKIND( 5, 191 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_5_MB191, CAN_CFG_ID_VALUE_5_MB191 ) },
#endif /* ( (CAN_CFG_MBOXSET_5_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */

    /* Controller 6 */
#if ( (CAN_CFG_MBOXSET_6_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB000, CAN_TB_u4MB_RXLABEL( CAN_MB000 ), CAN_TB_u4MB_RXKIND( 6, 000 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB000, CAN_CFG_ID_VALUE_6_MB000 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB001, CAN_TB_u4MB_RXLABEL( CAN_MB001 ), CAN_TB_u4MB_RXKIND( 6, 001 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB001, CAN_CFG_ID_VALUE_6_MB001 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB002, CAN_TB_u4MB_RXLABEL( CAN_MB002 ), CAN_TB_u4MB_RXKIND( 6, 002 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB002, CAN_CFG_ID_VALUE_6_MB002 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB003, CAN_TB_u4MB_RXLABEL( CAN_MB003 ), CAN_TB_u4MB_RXKIND( 6, 003 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB003, CAN_CFG_ID_VALUE_6_MB003 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB004, CAN_TB_u4MB_RXLABEL( CAN_MB004 ), CAN_TB_u4MB_RXKIND( 6, 004 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB004, CAN_CFG_ID_VALUE_6_MB004 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB005, CAN_TB_u4MB_RXLABEL( CAN_MB005 ), CAN_TB_u4MB_RXKIND( 6, 005 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB005, CAN_CFG_ID_VALUE_6_MB005 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB006, CAN_TB_u4MB_RXLABEL( CAN_MB006 ), CAN_TB_u4MB_RXKIND( 6, 006 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB006, CAN_CFG_ID_VALUE_6_MB006 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB007, CAN_TB_u4MB_RXLABEL( CAN_MB007 ), CAN_TB_u4MB_RXKIND( 6, 007 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB007, CAN_CFG_ID_VALUE_6_MB007 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB008, CAN_TB_u4MB_RXLABEL( CAN_MB008 ), CAN_TB_u4MB_RXKIND( 6, 008 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB008, CAN_CFG_ID_VALUE_6_MB008 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB009, CAN_TB_u4MB_RXLABEL( CAN_MB009 ), CAN_TB_u4MB_RXKIND( 6, 009 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB009, CAN_CFG_ID_VALUE_6_MB009 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB010, CAN_TB_u4MB_RXLABEL( CAN_MB010 ), CAN_TB_u4MB_RXKIND( 6, 010 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB010, CAN_CFG_ID_VALUE_6_MB010 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB011, CAN_TB_u4MB_RXLABEL( CAN_MB011 ), CAN_TB_u4MB_RXKIND( 6, 011 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB011, CAN_CFG_ID_VALUE_6_MB011 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB012, CAN_TB_u4MB_RXLABEL( CAN_MB012 ), CAN_TB_u4MB_RXKIND( 6, 012 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB012, CAN_CFG_ID_VALUE_6_MB012 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB013, CAN_TB_u4MB_RXLABEL( CAN_MB013 ), CAN_TB_u4MB_RXKIND( 6, 013 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB013, CAN_CFG_ID_VALUE_6_MB013 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB014, CAN_TB_u4MB_RXLABEL( CAN_MB014 ), CAN_TB_u4MB_RXKIND( 6, 014 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB014, CAN_CFG_ID_VALUE_6_MB014 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB015, CAN_TB_u4MB_RXLABEL( CAN_MB015 ), CAN_TB_u4MB_RXKIND( 6, 015 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB015, CAN_CFG_ID_VALUE_6_MB015 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB016, CAN_TB_u4MB_RXLABEL( CAN_MB016 ), CAN_TB_u4MB_RXKIND( 6, 016 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB016, CAN_CFG_ID_VALUE_6_MB016 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB017, CAN_TB_u4MB_RXLABEL( CAN_MB017 ), CAN_TB_u4MB_RXKIND( 6, 017 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB017, CAN_CFG_ID_VALUE_6_MB017 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB018, CAN_TB_u4MB_RXLABEL( CAN_MB018 ), CAN_TB_u4MB_RXKIND( 6, 018 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB018, CAN_CFG_ID_VALUE_6_MB018 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB019, CAN_TB_u4MB_RXLABEL( CAN_MB019 ), CAN_TB_u4MB_RXKIND( 6, 019 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB019, CAN_CFG_ID_VALUE_6_MB019 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB020, CAN_TB_u4MB_RXLABEL( CAN_MB020 ), CAN_TB_u4MB_RXKIND( 6, 020 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB020, CAN_CFG_ID_VALUE_6_MB020 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB021, CAN_TB_u4MB_RXLABEL( CAN_MB021 ), CAN_TB_u4MB_RXKIND( 6, 021 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB021, CAN_CFG_ID_VALUE_6_MB021 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB022, CAN_TB_u4MB_RXLABEL( CAN_MB022 ), CAN_TB_u4MB_RXKIND( 6, 022 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB022, CAN_CFG_ID_VALUE_6_MB022 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB023, CAN_TB_u4MB_RXLABEL( CAN_MB023 ), CAN_TB_u4MB_RXKIND( 6, 023 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB023, CAN_CFG_ID_VALUE_6_MB023 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB024, CAN_TB_u4MB_RXLABEL( CAN_MB024 ), CAN_TB_u4MB_RXKIND( 6, 024 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB024, CAN_CFG_ID_VALUE_6_MB024 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB025, CAN_TB_u4MB_RXLABEL( CAN_MB025 ), CAN_TB_u4MB_RXKIND( 6, 025 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB025, CAN_CFG_ID_VALUE_6_MB025 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB026, CAN_TB_u4MB_RXLABEL( CAN_MB026 ), CAN_TB_u4MB_RXKIND( 6, 026 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB026, CAN_CFG_ID_VALUE_6_MB026 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB027, CAN_TB_u4MB_RXLABEL( CAN_MB027 ), CAN_TB_u4MB_RXKIND( 6, 027 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB027, CAN_CFG_ID_VALUE_6_MB027 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB028, CAN_TB_u4MB_RXLABEL( CAN_MB028 ), CAN_TB_u4MB_RXKIND( 6, 028 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB028, CAN_CFG_ID_VALUE_6_MB028 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB029, CAN_TB_u4MB_RXLABEL( CAN_MB029 ), CAN_TB_u4MB_RXKIND( 6, 029 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB029, CAN_CFG_ID_VALUE_6_MB029 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB030, CAN_TB_u4MB_RXLABEL( CAN_MB030 ), CAN_TB_u4MB_RXKIND( 6, 030 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB030, CAN_CFG_ID_VALUE_6_MB030 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB031, CAN_TB_u4MB_RXLABEL( CAN_MB031 ), CAN_TB_u4MB_RXKIND( 6, 031 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB031, CAN_CFG_ID_VALUE_6_MB031 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB032, CAN_TB_u4MB_RXLABEL( CAN_MB032 ), CAN_TB_u4MB_RXKIND( 6, 032 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB032, CAN_CFG_ID_VALUE_6_MB032 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB033, CAN_TB_u4MB_RXLABEL( CAN_MB033 ), CAN_TB_u4MB_RXKIND( 6, 033 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB033, CAN_CFG_ID_VALUE_6_MB033 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB034, CAN_TB_u4MB_RXLABEL( CAN_MB034 ), CAN_TB_u4MB_RXKIND( 6, 034 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB034, CAN_CFG_ID_VALUE_6_MB034 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB035, CAN_TB_u4MB_RXLABEL( CAN_MB035 ), CAN_TB_u4MB_RXKIND( 6, 035 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB035, CAN_CFG_ID_VALUE_6_MB035 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB036, CAN_TB_u4MB_RXLABEL( CAN_MB036 ), CAN_TB_u4MB_RXKIND( 6, 036 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB036, CAN_CFG_ID_VALUE_6_MB036 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB037, CAN_TB_u4MB_RXLABEL( CAN_MB037 ), CAN_TB_u4MB_RXKIND( 6, 037 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB037, CAN_CFG_ID_VALUE_6_MB037 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB038, CAN_TB_u4MB_RXLABEL( CAN_MB038 ), CAN_TB_u4MB_RXKIND( 6, 038 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB038, CAN_CFG_ID_VALUE_6_MB038 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB039, CAN_TB_u4MB_RXLABEL( CAN_MB039 ), CAN_TB_u4MB_RXKIND( 6, 039 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB039, CAN_CFG_ID_VALUE_6_MB039 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB040, CAN_TB_u4MB_RXLABEL( CAN_MB040 ), CAN_TB_u4MB_RXKIND( 6, 040 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB040, CAN_CFG_ID_VALUE_6_MB040 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB041, CAN_TB_u4MB_RXLABEL( CAN_MB041 ), CAN_TB_u4MB_RXKIND( 6, 041 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB041, CAN_CFG_ID_VALUE_6_MB041 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB042, CAN_TB_u4MB_RXLABEL( CAN_MB042 ), CAN_TB_u4MB_RXKIND( 6, 042 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB042, CAN_CFG_ID_VALUE_6_MB042 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB043, CAN_TB_u4MB_RXLABEL( CAN_MB043 ), CAN_TB_u4MB_RXKIND( 6, 043 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB043, CAN_CFG_ID_VALUE_6_MB043 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB044, CAN_TB_u4MB_RXLABEL( CAN_MB044 ), CAN_TB_u4MB_RXKIND( 6, 044 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB044, CAN_CFG_ID_VALUE_6_MB044 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB045, CAN_TB_u4MB_RXLABEL( CAN_MB045 ), CAN_TB_u4MB_RXKIND( 6, 045 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB045, CAN_CFG_ID_VALUE_6_MB045 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB046, CAN_TB_u4MB_RXLABEL( CAN_MB046 ), CAN_TB_u4MB_RXKIND( 6, 046 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB046, CAN_CFG_ID_VALUE_6_MB046 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB047, CAN_TB_u4MB_RXLABEL( CAN_MB047 ), CAN_TB_u4MB_RXKIND( 6, 047 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB047, CAN_CFG_ID_VALUE_6_MB047 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB048, CAN_TB_u4MB_RXLABEL( CAN_MB048 ), CAN_TB_u4MB_RXKIND( 6, 048 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB048, CAN_CFG_ID_VALUE_6_MB048 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB049, CAN_TB_u4MB_RXLABEL( CAN_MB049 ), CAN_TB_u4MB_RXKIND( 6, 049 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB049, CAN_CFG_ID_VALUE_6_MB049 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB050, CAN_TB_u4MB_RXLABEL( CAN_MB050 ), CAN_TB_u4MB_RXKIND( 6, 050 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB050, CAN_CFG_ID_VALUE_6_MB050 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB051, CAN_TB_u4MB_RXLABEL( CAN_MB051 ), CAN_TB_u4MB_RXKIND( 6, 051 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB051, CAN_CFG_ID_VALUE_6_MB051 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB052, CAN_TB_u4MB_RXLABEL( CAN_MB052 ), CAN_TB_u4MB_RXKIND( 6, 052 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB052, CAN_CFG_ID_VALUE_6_MB052 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB053, CAN_TB_u4MB_RXLABEL( CAN_MB053 ), CAN_TB_u4MB_RXKIND( 6, 053 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB053, CAN_CFG_ID_VALUE_6_MB053 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB054, CAN_TB_u4MB_RXLABEL( CAN_MB054 ), CAN_TB_u4MB_RXKIND( 6, 054 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB054, CAN_CFG_ID_VALUE_6_MB054 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB055, CAN_TB_u4MB_RXLABEL( CAN_MB055 ), CAN_TB_u4MB_RXKIND( 6, 055 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB055, CAN_CFG_ID_VALUE_6_MB055 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB056, CAN_TB_u4MB_RXLABEL( CAN_MB056 ), CAN_TB_u4MB_RXKIND( 6, 056 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB056, CAN_CFG_ID_VALUE_6_MB056 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB057, CAN_TB_u4MB_RXLABEL( CAN_MB057 ), CAN_TB_u4MB_RXKIND( 6, 057 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB057, CAN_CFG_ID_VALUE_6_MB057 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB058, CAN_TB_u4MB_RXLABEL( CAN_MB058 ), CAN_TB_u4MB_RXKIND( 6, 058 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB058, CAN_CFG_ID_VALUE_6_MB058 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB059, CAN_TB_u4MB_RXLABEL( CAN_MB059 ), CAN_TB_u4MB_RXKIND( 6, 059 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB059, CAN_CFG_ID_VALUE_6_MB059 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB060, CAN_TB_u4MB_RXLABEL( CAN_MB060 ), CAN_TB_u4MB_RXKIND( 6, 060 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB060, CAN_CFG_ID_VALUE_6_MB060 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB061, CAN_TB_u4MB_RXLABEL( CAN_MB061 ), CAN_TB_u4MB_RXKIND( 6, 061 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB061, CAN_CFG_ID_VALUE_6_MB061 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB062, CAN_TB_u4MB_RXLABEL( CAN_MB062 ), CAN_TB_u4MB_RXKIND( 6, 062 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB062, CAN_CFG_ID_VALUE_6_MB062 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB063, CAN_TB_u4MB_RXLABEL( CAN_MB063 ), CAN_TB_u4MB_RXKIND( 6, 063 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB063, CAN_CFG_ID_VALUE_6_MB063 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB064, CAN_TB_u4MB_RXLABEL( CAN_MB064 ), CAN_TB_u4MB_RXKIND( 6, 064 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB064, CAN_CFG_ID_VALUE_6_MB064 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB065, CAN_TB_u4MB_RXLABEL( CAN_MB065 ), CAN_TB_u4MB_RXKIND( 6, 065 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB065, CAN_CFG_ID_VALUE_6_MB065 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB066, CAN_TB_u4MB_RXLABEL( CAN_MB066 ), CAN_TB_u4MB_RXKIND( 6, 066 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB066, CAN_CFG_ID_VALUE_6_MB066 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB067, CAN_TB_u4MB_RXLABEL( CAN_MB067 ), CAN_TB_u4MB_RXKIND( 6, 067 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB067, CAN_CFG_ID_VALUE_6_MB067 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB068, CAN_TB_u4MB_RXLABEL( CAN_MB068 ), CAN_TB_u4MB_RXKIND( 6, 068 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB068, CAN_CFG_ID_VALUE_6_MB068 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB069, CAN_TB_u4MB_RXLABEL( CAN_MB069 ), CAN_TB_u4MB_RXKIND( 6, 069 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB069, CAN_CFG_ID_VALUE_6_MB069 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB070, CAN_TB_u4MB_RXLABEL( CAN_MB070 ), CAN_TB_u4MB_RXKIND( 6, 070 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB070, CAN_CFG_ID_VALUE_6_MB070 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB071, CAN_TB_u4MB_RXLABEL( CAN_MB071 ), CAN_TB_u4MB_RXKIND( 6, 071 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB071, CAN_CFG_ID_VALUE_6_MB071 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB072, CAN_TB_u4MB_RXLABEL( CAN_MB072 ), CAN_TB_u4MB_RXKIND( 6, 072 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB072, CAN_CFG_ID_VALUE_6_MB072 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB073, CAN_TB_u4MB_RXLABEL( CAN_MB073 ), CAN_TB_u4MB_RXKIND( 6, 073 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB073, CAN_CFG_ID_VALUE_6_MB073 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB074, CAN_TB_u4MB_RXLABEL( CAN_MB074 ), CAN_TB_u4MB_RXKIND( 6, 074 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB074, CAN_CFG_ID_VALUE_6_MB074 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB075, CAN_TB_u4MB_RXLABEL( CAN_MB075 ), CAN_TB_u4MB_RXKIND( 6, 075 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB075, CAN_CFG_ID_VALUE_6_MB075 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB076, CAN_TB_u4MB_RXLABEL( CAN_MB076 ), CAN_TB_u4MB_RXKIND( 6, 076 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB076, CAN_CFG_ID_VALUE_6_MB076 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB077, CAN_TB_u4MB_RXLABEL( CAN_MB077 ), CAN_TB_u4MB_RXKIND( 6, 077 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB077, CAN_CFG_ID_VALUE_6_MB077 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB078, CAN_TB_u4MB_RXLABEL( CAN_MB078 ), CAN_TB_u4MB_RXKIND( 6, 078 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB078, CAN_CFG_ID_VALUE_6_MB078 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB079, CAN_TB_u4MB_RXLABEL( CAN_MB079 ), CAN_TB_u4MB_RXKIND( 6, 079 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB079, CAN_CFG_ID_VALUE_6_MB079 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB080, CAN_TB_u4MB_RXLABEL( CAN_MB080 ), CAN_TB_u4MB_RXKIND( 6, 080 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB080, CAN_CFG_ID_VALUE_6_MB080 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB081, CAN_TB_u4MB_RXLABEL( CAN_MB081 ), CAN_TB_u4MB_RXKIND( 6, 081 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB081, CAN_CFG_ID_VALUE_6_MB081 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB082, CAN_TB_u4MB_RXLABEL( CAN_MB082 ), CAN_TB_u4MB_RXKIND( 6, 082 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB082, CAN_CFG_ID_VALUE_6_MB082 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB083, CAN_TB_u4MB_RXLABEL( CAN_MB083 ), CAN_TB_u4MB_RXKIND( 6, 083 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB083, CAN_CFG_ID_VALUE_6_MB083 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB084, CAN_TB_u4MB_RXLABEL( CAN_MB084 ), CAN_TB_u4MB_RXKIND( 6, 084 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB084, CAN_CFG_ID_VALUE_6_MB084 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB085, CAN_TB_u4MB_RXLABEL( CAN_MB085 ), CAN_TB_u4MB_RXKIND( 6, 085 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB085, CAN_CFG_ID_VALUE_6_MB085 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB086, CAN_TB_u4MB_RXLABEL( CAN_MB086 ), CAN_TB_u4MB_RXKIND( 6, 086 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB086, CAN_CFG_ID_VALUE_6_MB086 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB087, CAN_TB_u4MB_RXLABEL( CAN_MB087 ), CAN_TB_u4MB_RXKIND( 6, 087 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB087, CAN_CFG_ID_VALUE_6_MB087 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB088, CAN_TB_u4MB_RXLABEL( CAN_MB088 ), CAN_TB_u4MB_RXKIND( 6, 088 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB088, CAN_CFG_ID_VALUE_6_MB088 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB089, CAN_TB_u4MB_RXLABEL( CAN_MB089 ), CAN_TB_u4MB_RXKIND( 6, 089 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB089, CAN_CFG_ID_VALUE_6_MB089 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB090, CAN_TB_u4MB_RXLABEL( CAN_MB090 ), CAN_TB_u4MB_RXKIND( 6, 090 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB090, CAN_CFG_ID_VALUE_6_MB090 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB091, CAN_TB_u4MB_RXLABEL( CAN_MB091 ), CAN_TB_u4MB_RXKIND( 6, 091 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB091, CAN_CFG_ID_VALUE_6_MB091 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB092, CAN_TB_u4MB_RXLABEL( CAN_MB092 ), CAN_TB_u4MB_RXKIND( 6, 092 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB092, CAN_CFG_ID_VALUE_6_MB092 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB093, CAN_TB_u4MB_RXLABEL( CAN_MB093 ), CAN_TB_u4MB_RXKIND( 6, 093 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB093, CAN_CFG_ID_VALUE_6_MB093 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB094, CAN_TB_u4MB_RXLABEL( CAN_MB094 ), CAN_TB_u4MB_RXKIND( 6, 094 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB094, CAN_CFG_ID_VALUE_6_MB094 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB095, CAN_TB_u4MB_RXLABEL( CAN_MB095 ), CAN_TB_u4MB_RXKIND( 6, 095 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB095, CAN_CFG_ID_VALUE_6_MB095 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB096, CAN_TB_u4MB_RXLABEL( CAN_MB096 ), CAN_TB_u4MB_RXKIND( 6, 096 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB096, CAN_CFG_ID_VALUE_6_MB096 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB097, CAN_TB_u4MB_RXLABEL( CAN_MB097 ), CAN_TB_u4MB_RXKIND( 6, 097 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB097, CAN_CFG_ID_VALUE_6_MB097 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB098, CAN_TB_u4MB_RXLABEL( CAN_MB098 ), CAN_TB_u4MB_RXKIND( 6, 098 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB098, CAN_CFG_ID_VALUE_6_MB098 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB099, CAN_TB_u4MB_RXLABEL( CAN_MB099 ), CAN_TB_u4MB_RXKIND( 6, 099 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB099, CAN_CFG_ID_VALUE_6_MB099 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB100, CAN_TB_u4MB_RXLABEL( CAN_MB100 ), CAN_TB_u4MB_RXKIND( 6, 100 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB100, CAN_CFG_ID_VALUE_6_MB100 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB101, CAN_TB_u4MB_RXLABEL( CAN_MB101 ), CAN_TB_u4MB_RXKIND( 6, 101 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB101, CAN_CFG_ID_VALUE_6_MB101 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB102, CAN_TB_u4MB_RXLABEL( CAN_MB102 ), CAN_TB_u4MB_RXKIND( 6, 102 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB102, CAN_CFG_ID_VALUE_6_MB102 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB103, CAN_TB_u4MB_RXLABEL( CAN_MB103 ), CAN_TB_u4MB_RXKIND( 6, 103 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB103, CAN_CFG_ID_VALUE_6_MB103 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB104, CAN_TB_u4MB_RXLABEL( CAN_MB104 ), CAN_TB_u4MB_RXKIND( 6, 104 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB104, CAN_CFG_ID_VALUE_6_MB104 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB105, CAN_TB_u4MB_RXLABEL( CAN_MB105 ), CAN_TB_u4MB_RXKIND( 6, 105 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB105, CAN_CFG_ID_VALUE_6_MB105 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB106, CAN_TB_u4MB_RXLABEL( CAN_MB106 ), CAN_TB_u4MB_RXKIND( 6, 106 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB106, CAN_CFG_ID_VALUE_6_MB106 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB107, CAN_TB_u4MB_RXLABEL( CAN_MB107 ), CAN_TB_u4MB_RXKIND( 6, 107 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB107, CAN_CFG_ID_VALUE_6_MB107 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB108, CAN_TB_u4MB_RXLABEL( CAN_MB108 ), CAN_TB_u4MB_RXKIND( 6, 108 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB108, CAN_CFG_ID_VALUE_6_MB108 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB109, CAN_TB_u4MB_RXLABEL( CAN_MB109 ), CAN_TB_u4MB_RXKIND( 6, 109 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB109, CAN_CFG_ID_VALUE_6_MB109 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB110, CAN_TB_u4MB_RXLABEL( CAN_MB110 ), CAN_TB_u4MB_RXKIND( 6, 110 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB110, CAN_CFG_ID_VALUE_6_MB110 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB111, CAN_TB_u4MB_RXLABEL( CAN_MB111 ), CAN_TB_u4MB_RXKIND( 6, 111 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB111, CAN_CFG_ID_VALUE_6_MB111 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB112, CAN_TB_u4MB_RXLABEL( CAN_MB112 ), CAN_TB_u4MB_RXKIND( 6, 112 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB112, CAN_CFG_ID_VALUE_6_MB112 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB113, CAN_TB_u4MB_RXLABEL( CAN_MB113 ), CAN_TB_u4MB_RXKIND( 6, 113 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB113, CAN_CFG_ID_VALUE_6_MB113 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB114, CAN_TB_u4MB_RXLABEL( CAN_MB114 ), CAN_TB_u4MB_RXKIND( 6, 114 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB114, CAN_CFG_ID_VALUE_6_MB114 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB115, CAN_TB_u4MB_RXLABEL( CAN_MB115 ), CAN_TB_u4MB_RXKIND( 6, 115 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB115, CAN_CFG_ID_VALUE_6_MB115 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB116, CAN_TB_u4MB_RXLABEL( CAN_MB116 ), CAN_TB_u4MB_RXKIND( 6, 116 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB116, CAN_CFG_ID_VALUE_6_MB116 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB117, CAN_TB_u4MB_RXLABEL( CAN_MB117 ), CAN_TB_u4MB_RXKIND( 6, 117 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB117, CAN_CFG_ID_VALUE_6_MB117 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB118, CAN_TB_u4MB_RXLABEL( CAN_MB118 ), CAN_TB_u4MB_RXKIND( 6, 118 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB118, CAN_CFG_ID_VALUE_6_MB118 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB119, CAN_TB_u4MB_RXLABEL( CAN_MB119 ), CAN_TB_u4MB_RXKIND( 6, 119 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB119, CAN_CFG_ID_VALUE_6_MB119 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB120, CAN_TB_u4MB_RXLABEL( CAN_MB120 ), CAN_TB_u4MB_RXKIND( 6, 120 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB120, CAN_CFG_ID_VALUE_6_MB120 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB121, CAN_TB_u4MB_RXLABEL( CAN_MB121 ), CAN_TB_u4MB_RXKIND( 6, 121 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB121, CAN_CFG_ID_VALUE_6_MB121 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB122, CAN_TB_u4MB_RXLABEL( CAN_MB122 ), CAN_TB_u4MB_RXKIND( 6, 122 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB122, CAN_CFG_ID_VALUE_6_MB122 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB123, CAN_TB_u4MB_RXLABEL( CAN_MB123 ), CAN_TB_u4MB_RXKIND( 6, 123 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB123, CAN_CFG_ID_VALUE_6_MB123 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB124, CAN_TB_u4MB_RXLABEL( CAN_MB124 ), CAN_TB_u4MB_RXKIND( 6, 124 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB124, CAN_CFG_ID_VALUE_6_MB124 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB125, CAN_TB_u4MB_RXLABEL( CAN_MB125 ), CAN_TB_u4MB_RXKIND( 6, 125 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB125, CAN_CFG_ID_VALUE_6_MB125 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB126, CAN_TB_u4MB_RXLABEL( CAN_MB126 ), CAN_TB_u4MB_RXKIND( 6, 126 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB126, CAN_CFG_ID_VALUE_6_MB126 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB127, CAN_TB_u4MB_RXLABEL( CAN_MB127 ), CAN_TB_u4MB_RXKIND( 6, 127 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB127, CAN_CFG_ID_VALUE_6_MB127 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB128, CAN_TB_u4MB_RXLABEL( CAN_MB128 ), CAN_TB_u4MB_RXKIND( 6, 128 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB128, CAN_CFG_ID_VALUE_6_MB128 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB129, CAN_TB_u4MB_RXLABEL( CAN_MB129 ), CAN_TB_u4MB_RXKIND( 6, 129 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB129, CAN_CFG_ID_VALUE_6_MB129 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB130, CAN_TB_u4MB_RXLABEL( CAN_MB130 ), CAN_TB_u4MB_RXKIND( 6, 130 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB130, CAN_CFG_ID_VALUE_6_MB130 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB131, CAN_TB_u4MB_RXLABEL( CAN_MB131 ), CAN_TB_u4MB_RXKIND( 6, 131 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB131, CAN_CFG_ID_VALUE_6_MB131 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB132, CAN_TB_u4MB_RXLABEL( CAN_MB132 ), CAN_TB_u4MB_RXKIND( 6, 132 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB132, CAN_CFG_ID_VALUE_6_MB132 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB133, CAN_TB_u4MB_RXLABEL( CAN_MB133 ), CAN_TB_u4MB_RXKIND( 6, 133 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB133, CAN_CFG_ID_VALUE_6_MB133 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB134, CAN_TB_u4MB_RXLABEL( CAN_MB134 ), CAN_TB_u4MB_RXKIND( 6, 134 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB134, CAN_CFG_ID_VALUE_6_MB134 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB135, CAN_TB_u4MB_RXLABEL( CAN_MB135 ), CAN_TB_u4MB_RXKIND( 6, 135 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB135, CAN_CFG_ID_VALUE_6_MB135 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB136, CAN_TB_u4MB_RXLABEL( CAN_MB136 ), CAN_TB_u4MB_RXKIND( 6, 136 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB136, CAN_CFG_ID_VALUE_6_MB136 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB137, CAN_TB_u4MB_RXLABEL( CAN_MB137 ), CAN_TB_u4MB_RXKIND( 6, 137 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB137, CAN_CFG_ID_VALUE_6_MB137 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB138, CAN_TB_u4MB_RXLABEL( CAN_MB138 ), CAN_TB_u4MB_RXKIND( 6, 138 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB138, CAN_CFG_ID_VALUE_6_MB138 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB139, CAN_TB_u4MB_RXLABEL( CAN_MB139 ), CAN_TB_u4MB_RXKIND( 6, 139 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB139, CAN_CFG_ID_VALUE_6_MB139 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB140, CAN_TB_u4MB_RXLABEL( CAN_MB140 ), CAN_TB_u4MB_RXKIND( 6, 140 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB140, CAN_CFG_ID_VALUE_6_MB140 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB141, CAN_TB_u4MB_RXLABEL( CAN_MB141 ), CAN_TB_u4MB_RXKIND( 6, 141 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB141, CAN_CFG_ID_VALUE_6_MB141 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB142, CAN_TB_u4MB_RXLABEL( CAN_MB142 ), CAN_TB_u4MB_RXKIND( 6, 142 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB142, CAN_CFG_ID_VALUE_6_MB142 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB143, CAN_TB_u4MB_RXLABEL( CAN_MB143 ), CAN_TB_u4MB_RXKIND( 6, 143 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB143, CAN_CFG_ID_VALUE_6_MB143 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB144, CAN_TB_u4MB_RXLABEL( CAN_MB144 ), CAN_TB_u4MB_RXKIND( 6, 144 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB144, CAN_CFG_ID_VALUE_6_MB144 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB145, CAN_TB_u4MB_RXLABEL( CAN_MB145 ), CAN_TB_u4MB_RXKIND( 6, 145 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB145, CAN_CFG_ID_VALUE_6_MB145 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB146, CAN_TB_u4MB_RXLABEL( CAN_MB146 ), CAN_TB_u4MB_RXKIND( 6, 146 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB146, CAN_CFG_ID_VALUE_6_MB146 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB147, CAN_TB_u4MB_RXLABEL( CAN_MB147 ), CAN_TB_u4MB_RXKIND( 6, 147 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB147, CAN_CFG_ID_VALUE_6_MB147 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB148, CAN_TB_u4MB_RXLABEL( CAN_MB148 ), CAN_TB_u4MB_RXKIND( 6, 148 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB148, CAN_CFG_ID_VALUE_6_MB148 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB149, CAN_TB_u4MB_RXLABEL( CAN_MB149 ), CAN_TB_u4MB_RXKIND( 6, 149 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB149, CAN_CFG_ID_VALUE_6_MB149 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB150, CAN_TB_u4MB_RXLABEL( CAN_MB150 ), CAN_TB_u4MB_RXKIND( 6, 150 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB150, CAN_CFG_ID_VALUE_6_MB150 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB151, CAN_TB_u4MB_RXLABEL( CAN_MB151 ), CAN_TB_u4MB_RXKIND( 6, 151 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB151, CAN_CFG_ID_VALUE_6_MB151 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB152, CAN_TB_u4MB_RXLABEL( CAN_MB152 ), CAN_TB_u4MB_RXKIND( 6, 152 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB152, CAN_CFG_ID_VALUE_6_MB152 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB153, CAN_TB_u4MB_RXLABEL( CAN_MB153 ), CAN_TB_u4MB_RXKIND( 6, 153 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB153, CAN_CFG_ID_VALUE_6_MB153 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB154, CAN_TB_u4MB_RXLABEL( CAN_MB154 ), CAN_TB_u4MB_RXKIND( 6, 154 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB154, CAN_CFG_ID_VALUE_6_MB154 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB155, CAN_TB_u4MB_RXLABEL( CAN_MB155 ), CAN_TB_u4MB_RXKIND( 6, 155 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB155, CAN_CFG_ID_VALUE_6_MB155 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB156, CAN_TB_u4MB_RXLABEL( CAN_MB156 ), CAN_TB_u4MB_RXKIND( 6, 156 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB156, CAN_CFG_ID_VALUE_6_MB156 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB157, CAN_TB_u4MB_RXLABEL( CAN_MB157 ), CAN_TB_u4MB_RXKIND( 6, 157 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB157, CAN_CFG_ID_VALUE_6_MB157 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB158, CAN_TB_u4MB_RXLABEL( CAN_MB158 ), CAN_TB_u4MB_RXKIND( 6, 158 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB158, CAN_CFG_ID_VALUE_6_MB158 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB159, CAN_TB_u4MB_RXLABEL( CAN_MB159 ), CAN_TB_u4MB_RXKIND( 6, 159 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB159, CAN_CFG_ID_VALUE_6_MB159 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB160, CAN_TB_u4MB_RXLABEL( CAN_MB160 ), CAN_TB_u4MB_RXKIND( 6, 160 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB160, CAN_CFG_ID_VALUE_6_MB160 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB161, CAN_TB_u4MB_RXLABEL( CAN_MB161 ), CAN_TB_u4MB_RXKIND( 6, 161 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB161, CAN_CFG_ID_VALUE_6_MB161 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB162, CAN_TB_u4MB_RXLABEL( CAN_MB162 ), CAN_TB_u4MB_RXKIND( 6, 162 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB162, CAN_CFG_ID_VALUE_6_MB162 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB163, CAN_TB_u4MB_RXLABEL( CAN_MB163 ), CAN_TB_u4MB_RXKIND( 6, 163 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB163, CAN_CFG_ID_VALUE_6_MB163 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB164, CAN_TB_u4MB_RXLABEL( CAN_MB164 ), CAN_TB_u4MB_RXKIND( 6, 164 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB164, CAN_CFG_ID_VALUE_6_MB164 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB165, CAN_TB_u4MB_RXLABEL( CAN_MB165 ), CAN_TB_u4MB_RXKIND( 6, 165 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB165, CAN_CFG_ID_VALUE_6_MB165 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB166, CAN_TB_u4MB_RXLABEL( CAN_MB166 ), CAN_TB_u4MB_RXKIND( 6, 166 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB166, CAN_CFG_ID_VALUE_6_MB166 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB167, CAN_TB_u4MB_RXLABEL( CAN_MB167 ), CAN_TB_u4MB_RXKIND( 6, 167 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB167, CAN_CFG_ID_VALUE_6_MB167 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB168, CAN_TB_u4MB_RXLABEL( CAN_MB168 ), CAN_TB_u4MB_RXKIND( 6, 168 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB168, CAN_CFG_ID_VALUE_6_MB168 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB169, CAN_TB_u4MB_RXLABEL( CAN_MB169 ), CAN_TB_u4MB_RXKIND( 6, 169 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB169, CAN_CFG_ID_VALUE_6_MB169 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB170, CAN_TB_u4MB_RXLABEL( CAN_MB170 ), CAN_TB_u4MB_RXKIND( 6, 170 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB170, CAN_CFG_ID_VALUE_6_MB170 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB171, CAN_TB_u4MB_RXLABEL( CAN_MB171 ), CAN_TB_u4MB_RXKIND( 6, 171 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB171, CAN_CFG_ID_VALUE_6_MB171 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB172, CAN_TB_u4MB_RXLABEL( CAN_MB172 ), CAN_TB_u4MB_RXKIND( 6, 172 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB172, CAN_CFG_ID_VALUE_6_MB172 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB173, CAN_TB_u4MB_RXLABEL( CAN_MB173 ), CAN_TB_u4MB_RXKIND( 6, 173 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB173, CAN_CFG_ID_VALUE_6_MB173 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB174, CAN_TB_u4MB_RXLABEL( CAN_MB174 ), CAN_TB_u4MB_RXKIND( 6, 174 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB174, CAN_CFG_ID_VALUE_6_MB174 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB175, CAN_TB_u4MB_RXLABEL( CAN_MB175 ), CAN_TB_u4MB_RXKIND( 6, 175 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB175, CAN_CFG_ID_VALUE_6_MB175 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB176, CAN_TB_u4MB_RXLABEL( CAN_MB176 ), CAN_TB_u4MB_RXKIND( 6, 176 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB176, CAN_CFG_ID_VALUE_6_MB176 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB177, CAN_TB_u4MB_RXLABEL( CAN_MB177 ), CAN_TB_u4MB_RXKIND( 6, 177 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB177, CAN_CFG_ID_VALUE_6_MB177 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB178, CAN_TB_u4MB_RXLABEL( CAN_MB178 ), CAN_TB_u4MB_RXKIND( 6, 178 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB178, CAN_CFG_ID_VALUE_6_MB178 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB179, CAN_TB_u4MB_RXLABEL( CAN_MB179 ), CAN_TB_u4MB_RXKIND( 6, 179 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB179, CAN_CFG_ID_VALUE_6_MB179 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB180, CAN_TB_u4MB_RXLABEL( CAN_MB180 ), CAN_TB_u4MB_RXKIND( 6, 180 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB180, CAN_CFG_ID_VALUE_6_MB180 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB181, CAN_TB_u4MB_RXLABEL( CAN_MB181 ), CAN_TB_u4MB_RXKIND( 6, 181 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB181, CAN_CFG_ID_VALUE_6_MB181 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB182, CAN_TB_u4MB_RXLABEL( CAN_MB182 ), CAN_TB_u4MB_RXKIND( 6, 182 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB182, CAN_CFG_ID_VALUE_6_MB182 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB183, CAN_TB_u4MB_RXLABEL( CAN_MB183 ), CAN_TB_u4MB_RXKIND( 6, 183 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB183, CAN_CFG_ID_VALUE_6_MB183 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB184, CAN_TB_u4MB_RXLABEL( CAN_MB184 ), CAN_TB_u4MB_RXKIND( 6, 184 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB184, CAN_CFG_ID_VALUE_6_MB184 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB185, CAN_TB_u4MB_RXLABEL( CAN_MB185 ), CAN_TB_u4MB_RXKIND( 6, 185 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB185, CAN_CFG_ID_VALUE_6_MB185 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB186, CAN_TB_u4MB_RXLABEL( CAN_MB186 ), CAN_TB_u4MB_RXKIND( 6, 186 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB186, CAN_CFG_ID_VALUE_6_MB186 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB187, CAN_TB_u4MB_RXLABEL( CAN_MB187 ), CAN_TB_u4MB_RXKIND( 6, 187 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB187, CAN_CFG_ID_VALUE_6_MB187 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB188, CAN_TB_u4MB_RXLABEL( CAN_MB188 ), CAN_TB_u4MB_RXKIND( 6, 188 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB188, CAN_CFG_ID_VALUE_6_MB188 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB189, CAN_TB_u4MB_RXLABEL( CAN_MB189 ), CAN_TB_u4MB_RXKIND( 6, 189 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB189, CAN_CFG_ID_VALUE_6_MB189 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB190, CAN_TB_u4MB_RXLABEL( CAN_MB190 ), CAN_TB_u4MB_RXKIND( 6, 190 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB190, CAN_CFG_ID_VALUE_6_MB190 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_6_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_6_MB191, CAN_TB_u4MB_RXLABEL( CAN_MB191 ), CAN_TB_u4MB_RXKIND( 6, 191 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_6_MB191, CAN_CFG_ID_VALUE_6_MB191 ) },
#endif /* ( (CAN_CFG_MBOXSET_6_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */

    /* Controller 7 */
#if ( (CAN_CFG_MBOXSET_7_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB000, CAN_TB_u4MB_RXLABEL( CAN_MB000 ), CAN_TB_u4MB_RXKIND( 7, 000 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB000, CAN_CFG_ID_VALUE_7_MB000 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB000 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB001, CAN_TB_u4MB_RXLABEL( CAN_MB001 ), CAN_TB_u4MB_RXKIND( 7, 001 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB001, CAN_CFG_ID_VALUE_7_MB001 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB001 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB002, CAN_TB_u4MB_RXLABEL( CAN_MB002 ), CAN_TB_u4MB_RXKIND( 7, 002 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB002, CAN_CFG_ID_VALUE_7_MB002 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB002 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB003, CAN_TB_u4MB_RXLABEL( CAN_MB003 ), CAN_TB_u4MB_RXKIND( 7, 003 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB003, CAN_CFG_ID_VALUE_7_MB003 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB003 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB004, CAN_TB_u4MB_RXLABEL( CAN_MB004 ), CAN_TB_u4MB_RXKIND( 7, 004 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB004, CAN_CFG_ID_VALUE_7_MB004 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB004 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB005, CAN_TB_u4MB_RXLABEL( CAN_MB005 ), CAN_TB_u4MB_RXKIND( 7, 005 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB005, CAN_CFG_ID_VALUE_7_MB005 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB005 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB006, CAN_TB_u4MB_RXLABEL( CAN_MB006 ), CAN_TB_u4MB_RXKIND( 7, 006 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB006, CAN_CFG_ID_VALUE_7_MB006 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB006 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB007, CAN_TB_u4MB_RXLABEL( CAN_MB007 ), CAN_TB_u4MB_RXKIND( 7, 007 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB007, CAN_CFG_ID_VALUE_7_MB007 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB007 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB008, CAN_TB_u4MB_RXLABEL( CAN_MB008 ), CAN_TB_u4MB_RXKIND( 7, 008 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB008, CAN_CFG_ID_VALUE_7_MB008 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB008 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB009, CAN_TB_u4MB_RXLABEL( CAN_MB009 ), CAN_TB_u4MB_RXKIND( 7, 009 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB009, CAN_CFG_ID_VALUE_7_MB009 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB009 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB010, CAN_TB_u4MB_RXLABEL( CAN_MB010 ), CAN_TB_u4MB_RXKIND( 7, 010 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB010, CAN_CFG_ID_VALUE_7_MB010 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB010 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB011, CAN_TB_u4MB_RXLABEL( CAN_MB011 ), CAN_TB_u4MB_RXKIND( 7, 011 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB011, CAN_CFG_ID_VALUE_7_MB011 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB011 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB012, CAN_TB_u4MB_RXLABEL( CAN_MB012 ), CAN_TB_u4MB_RXKIND( 7, 012 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB012, CAN_CFG_ID_VALUE_7_MB012 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB012 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB013, CAN_TB_u4MB_RXLABEL( CAN_MB013 ), CAN_TB_u4MB_RXKIND( 7, 013 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB013, CAN_CFG_ID_VALUE_7_MB013 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB013 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB014, CAN_TB_u4MB_RXLABEL( CAN_MB014 ), CAN_TB_u4MB_RXKIND( 7, 014 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB014, CAN_CFG_ID_VALUE_7_MB014 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB014 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB015, CAN_TB_u4MB_RXLABEL( CAN_MB015 ), CAN_TB_u4MB_RXKIND( 7, 015 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB015, CAN_CFG_ID_VALUE_7_MB015 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB015 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB016, CAN_TB_u4MB_RXLABEL( CAN_MB016 ), CAN_TB_u4MB_RXKIND( 7, 016 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB016, CAN_CFG_ID_VALUE_7_MB016 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB016 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB017, CAN_TB_u4MB_RXLABEL( CAN_MB017 ), CAN_TB_u4MB_RXKIND( 7, 017 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB017, CAN_CFG_ID_VALUE_7_MB017 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB017 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB018, CAN_TB_u4MB_RXLABEL( CAN_MB018 ), CAN_TB_u4MB_RXKIND( 7, 018 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB018, CAN_CFG_ID_VALUE_7_MB018 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB018 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB019, CAN_TB_u4MB_RXLABEL( CAN_MB019 ), CAN_TB_u4MB_RXKIND( 7, 019 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB019, CAN_CFG_ID_VALUE_7_MB019 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB019 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB020, CAN_TB_u4MB_RXLABEL( CAN_MB020 ), CAN_TB_u4MB_RXKIND( 7, 020 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB020, CAN_CFG_ID_VALUE_7_MB020 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB020 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB021, CAN_TB_u4MB_RXLABEL( CAN_MB021 ), CAN_TB_u4MB_RXKIND( 7, 021 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB021, CAN_CFG_ID_VALUE_7_MB021 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB021 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB022, CAN_TB_u4MB_RXLABEL( CAN_MB022 ), CAN_TB_u4MB_RXKIND( 7, 022 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB022, CAN_CFG_ID_VALUE_7_MB022 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB022 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB023, CAN_TB_u4MB_RXLABEL( CAN_MB023 ), CAN_TB_u4MB_RXKIND( 7, 023 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB023, CAN_CFG_ID_VALUE_7_MB023 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB023 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB024, CAN_TB_u4MB_RXLABEL( CAN_MB024 ), CAN_TB_u4MB_RXKIND( 7, 024 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB024, CAN_CFG_ID_VALUE_7_MB024 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB024 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB025, CAN_TB_u4MB_RXLABEL( CAN_MB025 ), CAN_TB_u4MB_RXKIND( 7, 025 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB025, CAN_CFG_ID_VALUE_7_MB025 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB025 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB026, CAN_TB_u4MB_RXLABEL( CAN_MB026 ), CAN_TB_u4MB_RXKIND( 7, 026 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB026, CAN_CFG_ID_VALUE_7_MB026 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB026 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB027, CAN_TB_u4MB_RXLABEL( CAN_MB027 ), CAN_TB_u4MB_RXKIND( 7, 027 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB027, CAN_CFG_ID_VALUE_7_MB027 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB027 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB028, CAN_TB_u4MB_RXLABEL( CAN_MB028 ), CAN_TB_u4MB_RXKIND( 7, 028 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB028, CAN_CFG_ID_VALUE_7_MB028 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB028 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB029, CAN_TB_u4MB_RXLABEL( CAN_MB029 ), CAN_TB_u4MB_RXKIND( 7, 029 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB029, CAN_CFG_ID_VALUE_7_MB029 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB029 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB030, CAN_TB_u4MB_RXLABEL( CAN_MB030 ), CAN_TB_u4MB_RXKIND( 7, 030 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB030, CAN_CFG_ID_VALUE_7_MB030 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB030 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB031, CAN_TB_u4MB_RXLABEL( CAN_MB031 ), CAN_TB_u4MB_RXKIND( 7, 031 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB031, CAN_CFG_ID_VALUE_7_MB031 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB031 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB032, CAN_TB_u4MB_RXLABEL( CAN_MB032 ), CAN_TB_u4MB_RXKIND( 7, 032 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB032, CAN_CFG_ID_VALUE_7_MB032 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB032 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB033, CAN_TB_u4MB_RXLABEL( CAN_MB033 ), CAN_TB_u4MB_RXKIND( 7, 033 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB033, CAN_CFG_ID_VALUE_7_MB033 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB033 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB034, CAN_TB_u4MB_RXLABEL( CAN_MB034 ), CAN_TB_u4MB_RXKIND( 7, 034 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB034, CAN_CFG_ID_VALUE_7_MB034 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB034 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB035, CAN_TB_u4MB_RXLABEL( CAN_MB035 ), CAN_TB_u4MB_RXKIND( 7, 035 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB035, CAN_CFG_ID_VALUE_7_MB035 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB035 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB036, CAN_TB_u4MB_RXLABEL( CAN_MB036 ), CAN_TB_u4MB_RXKIND( 7, 036 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB036, CAN_CFG_ID_VALUE_7_MB036 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB036 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB037, CAN_TB_u4MB_RXLABEL( CAN_MB037 ), CAN_TB_u4MB_RXKIND( 7, 037 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB037, CAN_CFG_ID_VALUE_7_MB037 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB037 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB038, CAN_TB_u4MB_RXLABEL( CAN_MB038 ), CAN_TB_u4MB_RXKIND( 7, 038 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB038, CAN_CFG_ID_VALUE_7_MB038 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB038 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB039, CAN_TB_u4MB_RXLABEL( CAN_MB039 ), CAN_TB_u4MB_RXKIND( 7, 039 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB039, CAN_CFG_ID_VALUE_7_MB039 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB039 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB040, CAN_TB_u4MB_RXLABEL( CAN_MB040 ), CAN_TB_u4MB_RXKIND( 7, 040 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB040, CAN_CFG_ID_VALUE_7_MB040 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB040 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB041, CAN_TB_u4MB_RXLABEL( CAN_MB041 ), CAN_TB_u4MB_RXKIND( 7, 041 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB041, CAN_CFG_ID_VALUE_7_MB041 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB041 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB042, CAN_TB_u4MB_RXLABEL( CAN_MB042 ), CAN_TB_u4MB_RXKIND( 7, 042 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB042, CAN_CFG_ID_VALUE_7_MB042 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB042 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB043, CAN_TB_u4MB_RXLABEL( CAN_MB043 ), CAN_TB_u4MB_RXKIND( 7, 043 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB043, CAN_CFG_ID_VALUE_7_MB043 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB043 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB044, CAN_TB_u4MB_RXLABEL( CAN_MB044 ), CAN_TB_u4MB_RXKIND( 7, 044 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB044, CAN_CFG_ID_VALUE_7_MB044 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB044 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB045, CAN_TB_u4MB_RXLABEL( CAN_MB045 ), CAN_TB_u4MB_RXKIND( 7, 045 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB045, CAN_CFG_ID_VALUE_7_MB045 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB045 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB046, CAN_TB_u4MB_RXLABEL( CAN_MB046 ), CAN_TB_u4MB_RXKIND( 7, 046 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB046, CAN_CFG_ID_VALUE_7_MB046 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB046 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB047, CAN_TB_u4MB_RXLABEL( CAN_MB047 ), CAN_TB_u4MB_RXKIND( 7, 047 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB047, CAN_CFG_ID_VALUE_7_MB047 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB047 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB048, CAN_TB_u4MB_RXLABEL( CAN_MB048 ), CAN_TB_u4MB_RXKIND( 7, 048 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB048, CAN_CFG_ID_VALUE_7_MB048 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB048 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB049, CAN_TB_u4MB_RXLABEL( CAN_MB049 ), CAN_TB_u4MB_RXKIND( 7, 049 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB049, CAN_CFG_ID_VALUE_7_MB049 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB049 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB050, CAN_TB_u4MB_RXLABEL( CAN_MB050 ), CAN_TB_u4MB_RXKIND( 7, 050 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB050, CAN_CFG_ID_VALUE_7_MB050 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB050 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB051, CAN_TB_u4MB_RXLABEL( CAN_MB051 ), CAN_TB_u4MB_RXKIND( 7, 051 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB051, CAN_CFG_ID_VALUE_7_MB051 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB051 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB052, CAN_TB_u4MB_RXLABEL( CAN_MB052 ), CAN_TB_u4MB_RXKIND( 7, 052 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB052, CAN_CFG_ID_VALUE_7_MB052 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB052 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB053, CAN_TB_u4MB_RXLABEL( CAN_MB053 ), CAN_TB_u4MB_RXKIND( 7, 053 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB053, CAN_CFG_ID_VALUE_7_MB053 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB053 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB054, CAN_TB_u4MB_RXLABEL( CAN_MB054 ), CAN_TB_u4MB_RXKIND( 7, 054 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB054, CAN_CFG_ID_VALUE_7_MB054 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB054 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB055, CAN_TB_u4MB_RXLABEL( CAN_MB055 ), CAN_TB_u4MB_RXKIND( 7, 055 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB055, CAN_CFG_ID_VALUE_7_MB055 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB055 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB056, CAN_TB_u4MB_RXLABEL( CAN_MB056 ), CAN_TB_u4MB_RXKIND( 7, 056 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB056, CAN_CFG_ID_VALUE_7_MB056 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB056 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB057, CAN_TB_u4MB_RXLABEL( CAN_MB057 ), CAN_TB_u4MB_RXKIND( 7, 057 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB057, CAN_CFG_ID_VALUE_7_MB057 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB057 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB058, CAN_TB_u4MB_RXLABEL( CAN_MB058 ), CAN_TB_u4MB_RXKIND( 7, 058 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB058, CAN_CFG_ID_VALUE_7_MB058 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB058 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB059, CAN_TB_u4MB_RXLABEL( CAN_MB059 ), CAN_TB_u4MB_RXKIND( 7, 059 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB059, CAN_CFG_ID_VALUE_7_MB059 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB059 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB060, CAN_TB_u4MB_RXLABEL( CAN_MB060 ), CAN_TB_u4MB_RXKIND( 7, 060 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB060, CAN_CFG_ID_VALUE_7_MB060 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB060 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB061, CAN_TB_u4MB_RXLABEL( CAN_MB061 ), CAN_TB_u4MB_RXKIND( 7, 061 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB061, CAN_CFG_ID_VALUE_7_MB061 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB061 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB062, CAN_TB_u4MB_RXLABEL( CAN_MB062 ), CAN_TB_u4MB_RXKIND( 7, 062 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB062, CAN_CFG_ID_VALUE_7_MB062 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB062 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB063, CAN_TB_u4MB_RXLABEL( CAN_MB063 ), CAN_TB_u4MB_RXKIND( 7, 063 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB063, CAN_CFG_ID_VALUE_7_MB063 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB063 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB064, CAN_TB_u4MB_RXLABEL( CAN_MB064 ), CAN_TB_u4MB_RXKIND( 7, 064 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB064, CAN_CFG_ID_VALUE_7_MB064 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB064 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB065, CAN_TB_u4MB_RXLABEL( CAN_MB065 ), CAN_TB_u4MB_RXKIND( 7, 065 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB065, CAN_CFG_ID_VALUE_7_MB065 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB065 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB066, CAN_TB_u4MB_RXLABEL( CAN_MB066 ), CAN_TB_u4MB_RXKIND( 7, 066 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB066, CAN_CFG_ID_VALUE_7_MB066 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB066 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB067, CAN_TB_u4MB_RXLABEL( CAN_MB067 ), CAN_TB_u4MB_RXKIND( 7, 067 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB067, CAN_CFG_ID_VALUE_7_MB067 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB067 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB068, CAN_TB_u4MB_RXLABEL( CAN_MB068 ), CAN_TB_u4MB_RXKIND( 7, 068 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB068, CAN_CFG_ID_VALUE_7_MB068 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB068 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB069, CAN_TB_u4MB_RXLABEL( CAN_MB069 ), CAN_TB_u4MB_RXKIND( 7, 069 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB069, CAN_CFG_ID_VALUE_7_MB069 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB069 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB070, CAN_TB_u4MB_RXLABEL( CAN_MB070 ), CAN_TB_u4MB_RXKIND( 7, 070 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB070, CAN_CFG_ID_VALUE_7_MB070 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB070 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB071, CAN_TB_u4MB_RXLABEL( CAN_MB071 ), CAN_TB_u4MB_RXKIND( 7, 071 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB071, CAN_CFG_ID_VALUE_7_MB071 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB071 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB072, CAN_TB_u4MB_RXLABEL( CAN_MB072 ), CAN_TB_u4MB_RXKIND( 7, 072 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB072, CAN_CFG_ID_VALUE_7_MB072 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB072 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB073, CAN_TB_u4MB_RXLABEL( CAN_MB073 ), CAN_TB_u4MB_RXKIND( 7, 073 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB073, CAN_CFG_ID_VALUE_7_MB073 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB073 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB074, CAN_TB_u4MB_RXLABEL( CAN_MB074 ), CAN_TB_u4MB_RXKIND( 7, 074 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB074, CAN_CFG_ID_VALUE_7_MB074 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB074 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB075, CAN_TB_u4MB_RXLABEL( CAN_MB075 ), CAN_TB_u4MB_RXKIND( 7, 075 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB075, CAN_CFG_ID_VALUE_7_MB075 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB075 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB076, CAN_TB_u4MB_RXLABEL( CAN_MB076 ), CAN_TB_u4MB_RXKIND( 7, 076 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB076, CAN_CFG_ID_VALUE_7_MB076 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB076 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB077, CAN_TB_u4MB_RXLABEL( CAN_MB077 ), CAN_TB_u4MB_RXKIND( 7, 077 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB077, CAN_CFG_ID_VALUE_7_MB077 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB077 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB078, CAN_TB_u4MB_RXLABEL( CAN_MB078 ), CAN_TB_u4MB_RXKIND( 7, 078 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB078, CAN_CFG_ID_VALUE_7_MB078 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB078 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB079, CAN_TB_u4MB_RXLABEL( CAN_MB079 ), CAN_TB_u4MB_RXKIND( 7, 079 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB079, CAN_CFG_ID_VALUE_7_MB079 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB079 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB080, CAN_TB_u4MB_RXLABEL( CAN_MB080 ), CAN_TB_u4MB_RXKIND( 7, 080 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB080, CAN_CFG_ID_VALUE_7_MB080 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB080 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB081, CAN_TB_u4MB_RXLABEL( CAN_MB081 ), CAN_TB_u4MB_RXKIND( 7, 081 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB081, CAN_CFG_ID_VALUE_7_MB081 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB081 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB082, CAN_TB_u4MB_RXLABEL( CAN_MB082 ), CAN_TB_u4MB_RXKIND( 7, 082 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB082, CAN_CFG_ID_VALUE_7_MB082 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB082 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB083, CAN_TB_u4MB_RXLABEL( CAN_MB083 ), CAN_TB_u4MB_RXKIND( 7, 083 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB083, CAN_CFG_ID_VALUE_7_MB083 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB083 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB084, CAN_TB_u4MB_RXLABEL( CAN_MB084 ), CAN_TB_u4MB_RXKIND( 7, 084 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB084, CAN_CFG_ID_VALUE_7_MB084 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB084 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB085, CAN_TB_u4MB_RXLABEL( CAN_MB085 ), CAN_TB_u4MB_RXKIND( 7, 085 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB085, CAN_CFG_ID_VALUE_7_MB085 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB085 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB086, CAN_TB_u4MB_RXLABEL( CAN_MB086 ), CAN_TB_u4MB_RXKIND( 7, 086 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB086, CAN_CFG_ID_VALUE_7_MB086 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB086 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB087, CAN_TB_u4MB_RXLABEL( CAN_MB087 ), CAN_TB_u4MB_RXKIND( 7, 087 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB087, CAN_CFG_ID_VALUE_7_MB087 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB087 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB088, CAN_TB_u4MB_RXLABEL( CAN_MB088 ), CAN_TB_u4MB_RXKIND( 7, 088 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB088, CAN_CFG_ID_VALUE_7_MB088 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB088 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB089, CAN_TB_u4MB_RXLABEL( CAN_MB089 ), CAN_TB_u4MB_RXKIND( 7, 089 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB089, CAN_CFG_ID_VALUE_7_MB089 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB089 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB090, CAN_TB_u4MB_RXLABEL( CAN_MB090 ), CAN_TB_u4MB_RXKIND( 7, 090 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB090, CAN_CFG_ID_VALUE_7_MB090 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB090 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB091, CAN_TB_u4MB_RXLABEL( CAN_MB091 ), CAN_TB_u4MB_RXKIND( 7, 091 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB091, CAN_CFG_ID_VALUE_7_MB091 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB091 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB092, CAN_TB_u4MB_RXLABEL( CAN_MB092 ), CAN_TB_u4MB_RXKIND( 7, 092 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB092, CAN_CFG_ID_VALUE_7_MB092 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB092 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB093, CAN_TB_u4MB_RXLABEL( CAN_MB093 ), CAN_TB_u4MB_RXKIND( 7, 093 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB093, CAN_CFG_ID_VALUE_7_MB093 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB093 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB094, CAN_TB_u4MB_RXLABEL( CAN_MB094 ), CAN_TB_u4MB_RXKIND( 7, 094 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB094, CAN_CFG_ID_VALUE_7_MB094 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB094 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB095, CAN_TB_u4MB_RXLABEL( CAN_MB095 ), CAN_TB_u4MB_RXKIND( 7, 095 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB095, CAN_CFG_ID_VALUE_7_MB095 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB095 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB096, CAN_TB_u4MB_RXLABEL( CAN_MB096 ), CAN_TB_u4MB_RXKIND( 7, 096 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB096, CAN_CFG_ID_VALUE_7_MB096 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB096 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB097, CAN_TB_u4MB_RXLABEL( CAN_MB097 ), CAN_TB_u4MB_RXKIND( 7, 097 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB097, CAN_CFG_ID_VALUE_7_MB097 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB097 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB098, CAN_TB_u4MB_RXLABEL( CAN_MB098 ), CAN_TB_u4MB_RXKIND( 7, 098 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB098, CAN_CFG_ID_VALUE_7_MB098 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB098 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB099, CAN_TB_u4MB_RXLABEL( CAN_MB099 ), CAN_TB_u4MB_RXKIND( 7, 099 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB099, CAN_CFG_ID_VALUE_7_MB099 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB099 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB100, CAN_TB_u4MB_RXLABEL( CAN_MB100 ), CAN_TB_u4MB_RXKIND( 7, 100 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB100, CAN_CFG_ID_VALUE_7_MB100 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB100 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB101, CAN_TB_u4MB_RXLABEL( CAN_MB101 ), CAN_TB_u4MB_RXKIND( 7, 101 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB101, CAN_CFG_ID_VALUE_7_MB101 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB101 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB102, CAN_TB_u4MB_RXLABEL( CAN_MB102 ), CAN_TB_u4MB_RXKIND( 7, 102 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB102, CAN_CFG_ID_VALUE_7_MB102 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB102 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB103, CAN_TB_u4MB_RXLABEL( CAN_MB103 ), CAN_TB_u4MB_RXKIND( 7, 103 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB103, CAN_CFG_ID_VALUE_7_MB103 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB103 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB104, CAN_TB_u4MB_RXLABEL( CAN_MB104 ), CAN_TB_u4MB_RXKIND( 7, 104 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB104, CAN_CFG_ID_VALUE_7_MB104 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB104 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB105, CAN_TB_u4MB_RXLABEL( CAN_MB105 ), CAN_TB_u4MB_RXKIND( 7, 105 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB105, CAN_CFG_ID_VALUE_7_MB105 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB105 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB106, CAN_TB_u4MB_RXLABEL( CAN_MB106 ), CAN_TB_u4MB_RXKIND( 7, 106 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB106, CAN_CFG_ID_VALUE_7_MB106 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB106 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB107, CAN_TB_u4MB_RXLABEL( CAN_MB107 ), CAN_TB_u4MB_RXKIND( 7, 107 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB107, CAN_CFG_ID_VALUE_7_MB107 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB107 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB108, CAN_TB_u4MB_RXLABEL( CAN_MB108 ), CAN_TB_u4MB_RXKIND( 7, 108 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB108, CAN_CFG_ID_VALUE_7_MB108 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB108 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB109, CAN_TB_u4MB_RXLABEL( CAN_MB109 ), CAN_TB_u4MB_RXKIND( 7, 109 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB109, CAN_CFG_ID_VALUE_7_MB109 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB109 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB110, CAN_TB_u4MB_RXLABEL( CAN_MB110 ), CAN_TB_u4MB_RXKIND( 7, 110 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB110, CAN_CFG_ID_VALUE_7_MB110 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB110 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB111, CAN_TB_u4MB_RXLABEL( CAN_MB111 ), CAN_TB_u4MB_RXKIND( 7, 111 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB111, CAN_CFG_ID_VALUE_7_MB111 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB111 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB112, CAN_TB_u4MB_RXLABEL( CAN_MB112 ), CAN_TB_u4MB_RXKIND( 7, 112 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB112, CAN_CFG_ID_VALUE_7_MB112 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB112 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB113, CAN_TB_u4MB_RXLABEL( CAN_MB113 ), CAN_TB_u4MB_RXKIND( 7, 113 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB113, CAN_CFG_ID_VALUE_7_MB113 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB113 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB114, CAN_TB_u4MB_RXLABEL( CAN_MB114 ), CAN_TB_u4MB_RXKIND( 7, 114 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB114, CAN_CFG_ID_VALUE_7_MB114 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB114 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB115, CAN_TB_u4MB_RXLABEL( CAN_MB115 ), CAN_TB_u4MB_RXKIND( 7, 115 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB115, CAN_CFG_ID_VALUE_7_MB115 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB115 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB116, CAN_TB_u4MB_RXLABEL( CAN_MB116 ), CAN_TB_u4MB_RXKIND( 7, 116 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB116, CAN_CFG_ID_VALUE_7_MB116 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB116 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB117, CAN_TB_u4MB_RXLABEL( CAN_MB117 ), CAN_TB_u4MB_RXKIND( 7, 117 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB117, CAN_CFG_ID_VALUE_7_MB117 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB117 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB118, CAN_TB_u4MB_RXLABEL( CAN_MB118 ), CAN_TB_u4MB_RXKIND( 7, 118 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB118, CAN_CFG_ID_VALUE_7_MB118 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB118 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB119, CAN_TB_u4MB_RXLABEL( CAN_MB119 ), CAN_TB_u4MB_RXKIND( 7, 119 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB119, CAN_CFG_ID_VALUE_7_MB119 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB119 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB120, CAN_TB_u4MB_RXLABEL( CAN_MB120 ), CAN_TB_u4MB_RXKIND( 7, 120 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB120, CAN_CFG_ID_VALUE_7_MB120 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB120 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB121, CAN_TB_u4MB_RXLABEL( CAN_MB121 ), CAN_TB_u4MB_RXKIND( 7, 121 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB121, CAN_CFG_ID_VALUE_7_MB121 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB121 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB122, CAN_TB_u4MB_RXLABEL( CAN_MB122 ), CAN_TB_u4MB_RXKIND( 7, 122 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB122, CAN_CFG_ID_VALUE_7_MB122 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB122 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB123, CAN_TB_u4MB_RXLABEL( CAN_MB123 ), CAN_TB_u4MB_RXKIND( 7, 123 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB123, CAN_CFG_ID_VALUE_7_MB123 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB123 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB124, CAN_TB_u4MB_RXLABEL( CAN_MB124 ), CAN_TB_u4MB_RXKIND( 7, 124 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB124, CAN_CFG_ID_VALUE_7_MB124 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB124 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB125, CAN_TB_u4MB_RXLABEL( CAN_MB125 ), CAN_TB_u4MB_RXKIND( 7, 125 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB125, CAN_CFG_ID_VALUE_7_MB125 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB125 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB126, CAN_TB_u4MB_RXLABEL( CAN_MB126 ), CAN_TB_u4MB_RXKIND( 7, 126 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB126, CAN_CFG_ID_VALUE_7_MB126 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB126 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB127, CAN_TB_u4MB_RXLABEL( CAN_MB127 ), CAN_TB_u4MB_RXKIND( 7, 127 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB127, CAN_CFG_ID_VALUE_7_MB127 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB127 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB128, CAN_TB_u4MB_RXLABEL( CAN_MB128 ), CAN_TB_u4MB_RXKIND( 7, 128 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB128, CAN_CFG_ID_VALUE_7_MB128 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB128 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB129, CAN_TB_u4MB_RXLABEL( CAN_MB129 ), CAN_TB_u4MB_RXKIND( 7, 129 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB129, CAN_CFG_ID_VALUE_7_MB129 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB129 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB130, CAN_TB_u4MB_RXLABEL( CAN_MB130 ), CAN_TB_u4MB_RXKIND( 7, 130 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB130, CAN_CFG_ID_VALUE_7_MB130 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB130 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB131, CAN_TB_u4MB_RXLABEL( CAN_MB131 ), CAN_TB_u4MB_RXKIND( 7, 131 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB131, CAN_CFG_ID_VALUE_7_MB131 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB131 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB132, CAN_TB_u4MB_RXLABEL( CAN_MB132 ), CAN_TB_u4MB_RXKIND( 7, 132 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB132, CAN_CFG_ID_VALUE_7_MB132 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB132 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB133, CAN_TB_u4MB_RXLABEL( CAN_MB133 ), CAN_TB_u4MB_RXKIND( 7, 133 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB133, CAN_CFG_ID_VALUE_7_MB133 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB133 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB134, CAN_TB_u4MB_RXLABEL( CAN_MB134 ), CAN_TB_u4MB_RXKIND( 7, 134 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB134, CAN_CFG_ID_VALUE_7_MB134 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB134 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB135, CAN_TB_u4MB_RXLABEL( CAN_MB135 ), CAN_TB_u4MB_RXKIND( 7, 135 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB135, CAN_CFG_ID_VALUE_7_MB135 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB135 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB136, CAN_TB_u4MB_RXLABEL( CAN_MB136 ), CAN_TB_u4MB_RXKIND( 7, 136 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB136, CAN_CFG_ID_VALUE_7_MB136 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB136 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB137, CAN_TB_u4MB_RXLABEL( CAN_MB137 ), CAN_TB_u4MB_RXKIND( 7, 137 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB137, CAN_CFG_ID_VALUE_7_MB137 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB137 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB138, CAN_TB_u4MB_RXLABEL( CAN_MB138 ), CAN_TB_u4MB_RXKIND( 7, 138 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB138, CAN_CFG_ID_VALUE_7_MB138 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB138 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB139, CAN_TB_u4MB_RXLABEL( CAN_MB139 ), CAN_TB_u4MB_RXKIND( 7, 139 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB139, CAN_CFG_ID_VALUE_7_MB139 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB139 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB140, CAN_TB_u4MB_RXLABEL( CAN_MB140 ), CAN_TB_u4MB_RXKIND( 7, 140 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB140, CAN_CFG_ID_VALUE_7_MB140 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB140 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB141, CAN_TB_u4MB_RXLABEL( CAN_MB141 ), CAN_TB_u4MB_RXKIND( 7, 141 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB141, CAN_CFG_ID_VALUE_7_MB141 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB141 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB142, CAN_TB_u4MB_RXLABEL( CAN_MB142 ), CAN_TB_u4MB_RXKIND( 7, 142 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB142, CAN_CFG_ID_VALUE_7_MB142 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB142 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB143, CAN_TB_u4MB_RXLABEL( CAN_MB143 ), CAN_TB_u4MB_RXKIND( 7, 143 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB143, CAN_CFG_ID_VALUE_7_MB143 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB143 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB144, CAN_TB_u4MB_RXLABEL( CAN_MB144 ), CAN_TB_u4MB_RXKIND( 7, 144 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB144, CAN_CFG_ID_VALUE_7_MB144 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB144 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB145, CAN_TB_u4MB_RXLABEL( CAN_MB145 ), CAN_TB_u4MB_RXKIND( 7, 145 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB145, CAN_CFG_ID_VALUE_7_MB145 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB145 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB146, CAN_TB_u4MB_RXLABEL( CAN_MB146 ), CAN_TB_u4MB_RXKIND( 7, 146 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB146, CAN_CFG_ID_VALUE_7_MB146 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB146 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB147, CAN_TB_u4MB_RXLABEL( CAN_MB147 ), CAN_TB_u4MB_RXKIND( 7, 147 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB147, CAN_CFG_ID_VALUE_7_MB147 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB147 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB148, CAN_TB_u4MB_RXLABEL( CAN_MB148 ), CAN_TB_u4MB_RXKIND( 7, 148 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB148, CAN_CFG_ID_VALUE_7_MB148 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB148 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB149, CAN_TB_u4MB_RXLABEL( CAN_MB149 ), CAN_TB_u4MB_RXKIND( 7, 149 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB149, CAN_CFG_ID_VALUE_7_MB149 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB149 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB150, CAN_TB_u4MB_RXLABEL( CAN_MB150 ), CAN_TB_u4MB_RXKIND( 7, 150 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB150, CAN_CFG_ID_VALUE_7_MB150 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB150 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB151, CAN_TB_u4MB_RXLABEL( CAN_MB151 ), CAN_TB_u4MB_RXKIND( 7, 151 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB151, CAN_CFG_ID_VALUE_7_MB151 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB151 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB152, CAN_TB_u4MB_RXLABEL( CAN_MB152 ), CAN_TB_u4MB_RXKIND( 7, 152 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB152, CAN_CFG_ID_VALUE_7_MB152 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB152 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB153, CAN_TB_u4MB_RXLABEL( CAN_MB153 ), CAN_TB_u4MB_RXKIND( 7, 153 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB153, CAN_CFG_ID_VALUE_7_MB153 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB153 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB154, CAN_TB_u4MB_RXLABEL( CAN_MB154 ), CAN_TB_u4MB_RXKIND( 7, 154 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB154, CAN_CFG_ID_VALUE_7_MB154 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB154 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB155, CAN_TB_u4MB_RXLABEL( CAN_MB155 ), CAN_TB_u4MB_RXKIND( 7, 155 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB155, CAN_CFG_ID_VALUE_7_MB155 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB155 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB156, CAN_TB_u4MB_RXLABEL( CAN_MB156 ), CAN_TB_u4MB_RXKIND( 7, 156 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB156, CAN_CFG_ID_VALUE_7_MB156 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB156 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB157, CAN_TB_u4MB_RXLABEL( CAN_MB157 ), CAN_TB_u4MB_RXKIND( 7, 157 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB157, CAN_CFG_ID_VALUE_7_MB157 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB157 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB158, CAN_TB_u4MB_RXLABEL( CAN_MB158 ), CAN_TB_u4MB_RXKIND( 7, 158 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB158, CAN_CFG_ID_VALUE_7_MB158 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB158 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB159, CAN_TB_u4MB_RXLABEL( CAN_MB159 ), CAN_TB_u4MB_RXKIND( 7, 159 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB159, CAN_CFG_ID_VALUE_7_MB159 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB159 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB160, CAN_TB_u4MB_RXLABEL( CAN_MB160 ), CAN_TB_u4MB_RXKIND( 7, 160 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB160, CAN_CFG_ID_VALUE_7_MB160 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB160 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB161, CAN_TB_u4MB_RXLABEL( CAN_MB161 ), CAN_TB_u4MB_RXKIND( 7, 161 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB161, CAN_CFG_ID_VALUE_7_MB161 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB161 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB162, CAN_TB_u4MB_RXLABEL( CAN_MB162 ), CAN_TB_u4MB_RXKIND( 7, 162 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB162, CAN_CFG_ID_VALUE_7_MB162 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB162 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB163, CAN_TB_u4MB_RXLABEL( CAN_MB163 ), CAN_TB_u4MB_RXKIND( 7, 163 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB163, CAN_CFG_ID_VALUE_7_MB163 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB163 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB164, CAN_TB_u4MB_RXLABEL( CAN_MB164 ), CAN_TB_u4MB_RXKIND( 7, 164 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB164, CAN_CFG_ID_VALUE_7_MB164 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB164 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB165, CAN_TB_u4MB_RXLABEL( CAN_MB165 ), CAN_TB_u4MB_RXKIND( 7, 165 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB165, CAN_CFG_ID_VALUE_7_MB165 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB165 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB166, CAN_TB_u4MB_RXLABEL( CAN_MB166 ), CAN_TB_u4MB_RXKIND( 7, 166 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB166, CAN_CFG_ID_VALUE_7_MB166 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB166 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB167, CAN_TB_u4MB_RXLABEL( CAN_MB167 ), CAN_TB_u4MB_RXKIND( 7, 167 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB167, CAN_CFG_ID_VALUE_7_MB167 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB167 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB168, CAN_TB_u4MB_RXLABEL( CAN_MB168 ), CAN_TB_u4MB_RXKIND( 7, 168 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB168, CAN_CFG_ID_VALUE_7_MB168 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB168 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB169, CAN_TB_u4MB_RXLABEL( CAN_MB169 ), CAN_TB_u4MB_RXKIND( 7, 169 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB169, CAN_CFG_ID_VALUE_7_MB169 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB169 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB170, CAN_TB_u4MB_RXLABEL( CAN_MB170 ), CAN_TB_u4MB_RXKIND( 7, 170 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB170, CAN_CFG_ID_VALUE_7_MB170 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB170 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB171, CAN_TB_u4MB_RXLABEL( CAN_MB171 ), CAN_TB_u4MB_RXKIND( 7, 171 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB171, CAN_CFG_ID_VALUE_7_MB171 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB171 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB172, CAN_TB_u4MB_RXLABEL( CAN_MB172 ), CAN_TB_u4MB_RXKIND( 7, 172 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB172, CAN_CFG_ID_VALUE_7_MB172 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB172 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB173, CAN_TB_u4MB_RXLABEL( CAN_MB173 ), CAN_TB_u4MB_RXKIND( 7, 173 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB173, CAN_CFG_ID_VALUE_7_MB173 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB173 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB174, CAN_TB_u4MB_RXLABEL( CAN_MB174 ), CAN_TB_u4MB_RXKIND( 7, 174 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB174, CAN_CFG_ID_VALUE_7_MB174 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB174 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB175, CAN_TB_u4MB_RXLABEL( CAN_MB175 ), CAN_TB_u4MB_RXKIND( 7, 175 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB175, CAN_CFG_ID_VALUE_7_MB175 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB175 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB176, CAN_TB_u4MB_RXLABEL( CAN_MB176 ), CAN_TB_u4MB_RXKIND( 7, 176 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB176, CAN_CFG_ID_VALUE_7_MB176 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB176 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB177, CAN_TB_u4MB_RXLABEL( CAN_MB177 ), CAN_TB_u4MB_RXKIND( 7, 177 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB177, CAN_CFG_ID_VALUE_7_MB177 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB177 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB178, CAN_TB_u4MB_RXLABEL( CAN_MB178 ), CAN_TB_u4MB_RXKIND( 7, 178 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB178, CAN_CFG_ID_VALUE_7_MB178 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB178 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB179, CAN_TB_u4MB_RXLABEL( CAN_MB179 ), CAN_TB_u4MB_RXKIND( 7, 179 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB179, CAN_CFG_ID_VALUE_7_MB179 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB179 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB180, CAN_TB_u4MB_RXLABEL( CAN_MB180 ), CAN_TB_u4MB_RXKIND( 7, 180 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB180, CAN_CFG_ID_VALUE_7_MB180 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB180 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB181, CAN_TB_u4MB_RXLABEL( CAN_MB181 ), CAN_TB_u4MB_RXKIND( 7, 181 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB181, CAN_CFG_ID_VALUE_7_MB181 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB181 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB182, CAN_TB_u4MB_RXLABEL( CAN_MB182 ), CAN_TB_u4MB_RXKIND( 7, 182 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB182, CAN_CFG_ID_VALUE_7_MB182 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB182 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB183, CAN_TB_u4MB_RXLABEL( CAN_MB183 ), CAN_TB_u4MB_RXKIND( 7, 183 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB183, CAN_CFG_ID_VALUE_7_MB183 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB183 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB184, CAN_TB_u4MB_RXLABEL( CAN_MB184 ), CAN_TB_u4MB_RXKIND( 7, 184 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB184, CAN_CFG_ID_VALUE_7_MB184 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB184 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB185, CAN_TB_u4MB_RXLABEL( CAN_MB185 ), CAN_TB_u4MB_RXKIND( 7, 185 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB185, CAN_CFG_ID_VALUE_7_MB185 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB185 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB186, CAN_TB_u4MB_RXLABEL( CAN_MB186 ), CAN_TB_u4MB_RXKIND( 7, 186 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB186, CAN_CFG_ID_VALUE_7_MB186 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB186 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB187, CAN_TB_u4MB_RXLABEL( CAN_MB187 ), CAN_TB_u4MB_RXKIND( 7, 187 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB187, CAN_CFG_ID_VALUE_7_MB187 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB187 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB188, CAN_TB_u4MB_RXLABEL( CAN_MB188 ), CAN_TB_u4MB_RXKIND( 7, 188 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB188, CAN_CFG_ID_VALUE_7_MB188 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB188 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB189, CAN_TB_u4MB_RXLABEL( CAN_MB189 ), CAN_TB_u4MB_RXKIND( 7, 189 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB189, CAN_CFG_ID_VALUE_7_MB189 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB189 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB190, CAN_TB_u4MB_RXLABEL( CAN_MB190 ), CAN_TB_u4MB_RXKIND( 7, 190 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB190, CAN_CFG_ID_VALUE_7_MB190 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB190 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
#if ( (CAN_CFG_MBOXSET_7_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE )
     { CAN_CFG_ID_VALUE_7_MB191, CAN_TB_u4MB_RXLABEL( CAN_MB191 ), CAN_TB_u4MB_RXKIND( 7, 191 ), CAN_TB_u1CONV_RXMASKREFIDX( CAN_CFG_MASK_REFERENCE_7_MB191, CAN_CFG_ID_VALUE_7_MB191 ) },
#endif /* ( (CAN_CFG_MBOXSET_7_MB191 & CAN_MB_RECEPTION) != CAN_MB_NOUSE ) */
     { CAN_TB_u4GAFLID_DUMMY   , CAN_TB_u4GAFLP0_DUMMY           , CAN_TB_u4GAFLP1_DUMMY       , (uint8)CAN_TB_u1RXMASK_DUMMY                                                           }
};

CanConst uint32 Can_tb_u4RxMask[ CAN_TB_RXMKTBLSIZE ] =
{
#if (CAN_CFG_FILTER_MASK_NUM > 0U)
    CAN_TB_u4RXMASK_VAL( 0 ),
    CAN_TB_u4RXMASK_VAL( 1 ),
    CAN_TB_u4RXMASK_VAL( 2 ),
    CAN_TB_u4RXMASK_VAL( 3 ),
    CAN_TB_u4RXMASK_VAL( 4 ),
    CAN_TB_u4RXMASK_VAL( 5 ),
    CAN_TB_u4RXMASK_VAL( 6 ),
    CAN_TB_u4RXMASK_VAL( 7 ),
#endif /* (CAN_CFG_FILTER_MASK_NUM > 0U) */
#if (CAN_CFG_FILTER_MASK_NUM > 8U)
    CAN_TB_u4RXMASK_VAL( 8 ),
    CAN_TB_u4RXMASK_VAL( 9 ),
    CAN_TB_u4RXMASK_VAL( 10 ),
    CAN_TB_u4RXMASK_VAL( 11 ),
    CAN_TB_u4RXMASK_VAL( 12 ),
    CAN_TB_u4RXMASK_VAL( 13 ),
    CAN_TB_u4RXMASK_VAL( 14 ),
    CAN_TB_u4RXMASK_VAL( 15 ),
#endif /* (CAN_CFG_FILTER_MASK_NUM > 8U) */
#if (CAN_CFG_FILTER_MASK_NUM > 16U)
    CAN_TB_u4RXMASK_VAL( 16 ),
    CAN_TB_u4RXMASK_VAL( 17 ),
    CAN_TB_u4RXMASK_VAL( 18 ),
    CAN_TB_u4RXMASK_VAL( 19 ),
    CAN_TB_u4RXMASK_VAL( 20 ),
    CAN_TB_u4RXMASK_VAL( 21 ),
    CAN_TB_u4RXMASK_VAL( 22 ),
    CAN_TB_u4RXMASK_VAL( 23 ),
    CAN_TB_u4RXMASK_VAL( 24 ),
    CAN_TB_u4RXMASK_VAL( 25 ),
    CAN_TB_u4RXMASK_VAL( 26 ),
    CAN_TB_u4RXMASK_VAL( 27 ),
    CAN_TB_u4RXMASK_VAL( 28 ),
    CAN_TB_u4RXMASK_VAL( 29 ),
    CAN_TB_u4RXMASK_VAL( 30 ),
    CAN_TB_u4RXMASK_VAL( 31 ),
#endif /* (CAN_CFG_FILTER_MASK_NUM > 16U) */
#if (CAN_CFG_FILTER_MASK_NUM > 32U)
    CAN_TB_u4RXMASK_VAL( 32 ),
    CAN_TB_u4RXMASK_VAL( 33 ),
    CAN_TB_u4RXMASK_VAL( 34 ),
    CAN_TB_u4RXMASK_VAL( 35 ),
    CAN_TB_u4RXMASK_VAL( 36 ),
    CAN_TB_u4RXMASK_VAL( 37 ),
    CAN_TB_u4RXMASK_VAL( 38 ),
    CAN_TB_u4RXMASK_VAL( 39 ),
    CAN_TB_u4RXMASK_VAL( 40 ),
    CAN_TB_u4RXMASK_VAL( 41 ),
    CAN_TB_u4RXMASK_VAL( 42 ),
    CAN_TB_u4RXMASK_VAL( 43 ),
    CAN_TB_u4RXMASK_VAL( 44 ),
    CAN_TB_u4RXMASK_VAL( 45 ),
    CAN_TB_u4RXMASK_VAL( 46 ),
    CAN_TB_u4RXMASK_VAL( 47 ),
#endif /* (CAN_CFG_FILTER_MASK_NUM > 32U) */
#if (CAN_CFG_FILTER_MASK_NUM > 48U)
    CAN_TB_u4RXMASK_VAL( 48 ),
    CAN_TB_u4RXMASK_VAL( 49 ),
    CAN_TB_u4RXMASK_VAL( 50 ),
    CAN_TB_u4RXMASK_VAL( 51 ),
    CAN_TB_u4RXMASK_VAL( 52 ),
    CAN_TB_u4RXMASK_VAL( 53 ),
    CAN_TB_u4RXMASK_VAL( 54 ),
    CAN_TB_u4RXMASK_VAL( 55 ),
    CAN_TB_u4RXMASK_VAL( 56 ),
    CAN_TB_u4RXMASK_VAL( 57 ),
    CAN_TB_u4RXMASK_VAL( 58 ),
    CAN_TB_u4RXMASK_VAL( 59 ),
    CAN_TB_u4RXMASK_VAL( 60 ),
    CAN_TB_u4RXMASK_VAL( 61 ),
    CAN_TB_u4RXMASK_VAL( 62 ),
    CAN_TB_u4RXMASK_VAL( 63 ),
#endif /* (CAN_CFG_FILTER_MASK_NUM > 48U) */
#if (CAN_CFG_FILTER_MASK_NUM > 64U)
    CAN_TB_u4RXMASK_VAL( 64 ),
    CAN_TB_u4RXMASK_VAL( 65 ),
    CAN_TB_u4RXMASK_VAL( 66 ),
    CAN_TB_u4RXMASK_VAL( 67 ),
    CAN_TB_u4RXMASK_VAL( 68 ),
    CAN_TB_u4RXMASK_VAL( 69 ),
    CAN_TB_u4RXMASK_VAL( 70 ),
    CAN_TB_u4RXMASK_VAL( 71 ),
    CAN_TB_u4RXMASK_VAL( 72 ),
    CAN_TB_u4RXMASK_VAL( 73 ),
    CAN_TB_u4RXMASK_VAL( 74 ),
    CAN_TB_u4RXMASK_VAL( 75 ),
    CAN_TB_u4RXMASK_VAL( 76 ),
    CAN_TB_u4RXMASK_VAL( 77 ),
    CAN_TB_u4RXMASK_VAL( 78 ),
    CAN_TB_u4RXMASK_VAL( 79 ),
#endif /* (CAN_CFG_FILTER_MASK_NUM > 64U) */
#if (CAN_CFG_FILTER_MASK_NUM > 80U)
    CAN_TB_u4RXMASK_VAL( 80 ),
    CAN_TB_u4RXMASK_VAL( 81 ),
    CAN_TB_u4RXMASK_VAL( 82 ),
    CAN_TB_u4RXMASK_VAL( 83 ),
    CAN_TB_u4RXMASK_VAL( 84 ),
    CAN_TB_u4RXMASK_VAL( 85 ),
    CAN_TB_u4RXMASK_VAL( 86 ),
    CAN_TB_u4RXMASK_VAL( 87 ),
    CAN_TB_u4RXMASK_VAL( 88 ),
    CAN_TB_u4RXMASK_VAL( 89 ),
    CAN_TB_u4RXMASK_VAL( 90 ),
    CAN_TB_u4RXMASK_VAL( 91 ),
    CAN_TB_u4RXMASK_VAL( 92 ),
    CAN_TB_u4RXMASK_VAL( 93 ),
    CAN_TB_u4RXMASK_VAL( 94 ),
    CAN_TB_u4RXMASK_VAL( 95 ),
#endif /* (CAN_CFG_FILTER_MASK_NUM > 80U) */
#if (CAN_CFG_FILTER_MASK_NUM > 96U)
    CAN_TB_u4RXMASK_VAL( 96 ),
    CAN_TB_u4RXMASK_VAL( 97 ),
    CAN_TB_u4RXMASK_VAL( 98 ),
    CAN_TB_u4RXMASK_VAL( 99 ),
    CAN_TB_u4RXMASK_VAL( 100 ),
    CAN_TB_u4RXMASK_VAL( 101 ),
    CAN_TB_u4RXMASK_VAL( 102 ),
    CAN_TB_u4RXMASK_VAL( 103 ),
    CAN_TB_u4RXMASK_VAL( 104 ),
    CAN_TB_u4RXMASK_VAL( 105 ),
    CAN_TB_u4RXMASK_VAL( 106 ),
    CAN_TB_u4RXMASK_VAL( 107 ),
    CAN_TB_u4RXMASK_VAL( 108 ),
    CAN_TB_u4RXMASK_VAL( 109 ),
    CAN_TB_u4RXMASK_VAL( 110 ),
    CAN_TB_u4RXMASK_VAL( 111 ),
#endif /* (CAN_CFG_FILTER_MASK_NUM > 96U) */
#if (CAN_CFG_FILTER_MASK_NUM > 112U)
    CAN_TB_u4RXMASK_VAL( 112 ),
    CAN_TB_u4RXMASK_VAL( 113 ),
    CAN_TB_u4RXMASK_VAL( 114 ),
    CAN_TB_u4RXMASK_VAL( 115 ),
    CAN_TB_u4RXMASK_VAL( 116 ),
    CAN_TB_u4RXMASK_VAL( 117 ),
    CAN_TB_u4RXMASK_VAL( 118 ),
    CAN_TB_u4RXMASK_VAL( 119 ),
    CAN_TB_u4RXMASK_VAL( 120 ),
    CAN_TB_u4RXMASK_VAL( 121 ),
    CAN_TB_u4RXMASK_VAL( 122 ),
    CAN_TB_u4RXMASK_VAL( 123 ),
    CAN_TB_u4RXMASK_VAL( 124 ),
    CAN_TB_u4RXMASK_VAL( 125 ),
    CAN_TB_u4RXMASK_VAL( 126 ),
    CAN_TB_u4RXMASK_VAL( 127 ),
#endif /* (CAN_CFG_FILTER_MASK_NUM > 112U) */
    CAN_u4GAFLM_STDIDMSK_NOUSE,
    CAN_u4GAFLM_EXTIDMSK_NOUSE
};

CanConst CanTbSetRSCANRegType Can_tb_stSetRSCANReg[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /* u4CFCC0Conf                  , u4CFCC1Conf                  , u4CFCC2Conf                , u4CmNCFGConf               */
    /*,u4CmCTRConf                  , u4CFSTSConf                  , u4CmDCFGConf               , u4CmFDCFGConf              */
    /*,u4TMFDCTRConf                                                                                                         */
    /* Controller 0 */
     { CAN_TB_u4CFCC0_CONF( 0 )     , CAN_TB_u4CFCC1_CONF( 0 )     , CAN_TB_u4CFCC2_CONF( 0 )   , CAN_TB_u4CmNCFG_CONF( 0 )
      ,CAN_TB_u4CMCTR_CONF( 0 )     , CAN_TB_u4CFSTS_CONF( 0 )     , CAN_TB_u4CmDCFG_CONF( 0 )  , CAN_TB_u4CMFDCFG_CONF( 0 )
      ,CAN_TB_u4TMFDCTR_CONF( 0 )
     }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    /* Controller 1 */
    ,{ CAN_TB_u4CFCC0_CONF( 1 )     , CAN_TB_u4CFCC1_CONF( 1 )     , CAN_TB_u4CFCC2_CONF( 1 )   , CAN_TB_u4CmNCFG_CONF( 1 )
      ,CAN_TB_u4CMCTR_CONF( 1 )     , CAN_TB_u4CFSTS_CONF( 1 )     , CAN_TB_u4CmDCFG_CONF( 1 )  , CAN_TB_u4CMFDCFG_CONF( 1 )
      ,CAN_TB_u4TMFDCTR_CONF( 1 )
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    /* Controller 2 */
    ,{ CAN_TB_u4CFCC0_CONF( 2 )     , CAN_TB_u4CFCC1_CONF( 2 )     , CAN_TB_u4CFCC2_CONF( 2 )   , CAN_TB_u4CmNCFG_CONF( 2 )
      ,CAN_TB_u4CMCTR_CONF( 2 )     , CAN_TB_u4CFSTS_CONF( 2 )     , CAN_TB_u4CmDCFG_CONF( 2 )  , CAN_TB_u4CMFDCFG_CONF( 2 )
      ,CAN_TB_u4TMFDCTR_CONF( 2 )
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    /* Controller 3 */
    ,{ CAN_TB_u4CFCC0_CONF( 3 )     , CAN_TB_u4CFCC1_CONF( 3 )     , CAN_TB_u4CFCC2_CONF( 3 )   , CAN_TB_u4CmNCFG_CONF( 3 )
      ,CAN_TB_u4CMCTR_CONF( 3 )     , CAN_TB_u4CFSTS_CONF( 3 )     , CAN_TB_u4CmDCFG_CONF( 3 )  , CAN_TB_u4CMFDCFG_CONF( 3 )
      ,CAN_TB_u4TMFDCTR_CONF( 3 )
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    /* Controller 4 */
    ,{ CAN_TB_u4CFCC0_CONF( 4 )     , CAN_TB_u4CFCC1_CONF( 4 )     , CAN_TB_u4CFCC2_CONF( 4 )   , CAN_TB_u4CmNCFG_CONF( 4 )
      ,CAN_TB_u4CMCTR_CONF( 4 )     , CAN_TB_u4CFSTS_CONF( 4 )     , CAN_TB_u4CmDCFG_CONF( 4 )  , CAN_TB_u4CMFDCFG_CONF( 4 )
      ,CAN_TB_u4TMFDCTR_CONF( 4 )
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    /* Controller 5 */
    ,{ CAN_TB_u4CFCC0_CONF( 5 )     , CAN_TB_u4CFCC1_CONF( 5 )     , CAN_TB_u4CFCC2_CONF( 5 )   , CAN_TB_u4CmNCFG_CONF( 5 )
      ,CAN_TB_u4CMCTR_CONF( 5 )     , CAN_TB_u4CFSTS_CONF( 5 )     , CAN_TB_u4CmDCFG_CONF( 5 )  , CAN_TB_u4CMFDCFG_CONF( 5 )
      ,CAN_TB_u4TMFDCTR_CONF( 5 )
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    /* Controller 6 */
    ,{ CAN_TB_u4CFCC0_CONF( 6 )     , CAN_TB_u4CFCC1_CONF( 6 )     , CAN_TB_u4CFCC2_CONF( 6 )   , CAN_TB_u4CmNCFG_CONF( 6 )
      ,CAN_TB_u4CMCTR_CONF( 6 )     , CAN_TB_u4CFSTS_CONF( 6 )     , CAN_TB_u4CmDCFG_CONF( 6 )  , CAN_TB_u4CMFDCFG_CONF( 6 )
      ,CAN_TB_u4TMFDCTR_CONF( 6 )
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    /* Controller 7 */
    ,{ CAN_TB_u4CFCC0_CONF( 7 )     , CAN_TB_u4CFCC1_CONF( 7 )     , CAN_TB_u4CFCC2_CONF( 7 )   , CAN_TB_u4CmNCFG_CONF( 7 )
      ,CAN_TB_u4CMCTR_CONF( 7 )     , CAN_TB_u4CFSTS_CONF( 7 )     , CAN_TB_u4CmDCFG_CONF( 7 )  , CAN_TB_u4CMFDCFG_CONF( 7 )
      ,CAN_TB_u4TMFDCTR_CONF( 7 )
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};

CanConst uint8 Can_tb_u1BRSInitConf[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
     CAN_TB_u1BRS_INIT_CONF( 0 )       /* Controller 0 */
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,CAN_TB_u1BRS_INIT_CONF( 1 )       /* Controller 1 */
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,CAN_TB_u1BRS_INIT_CONF( 2 )       /* Controller 2 */
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,CAN_TB_u1BRS_INIT_CONF( 3 )       /* Controller 3 */
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,CAN_TB_u1BRS_INIT_CONF( 4 )       /* Controller 4 */
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,CAN_TB_u1BRS_INIT_CONF( 5 )       /* Controller 5 */
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,CAN_TB_u1BRS_INIT_CONF( 6 )       /* Controller 6 */
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,CAN_TB_u1BRS_INIT_CONF( 7 )       /* Controller 7 */
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};

CanConst CanBaudrateSwtCfgType * CanConst Can_tb_ptBaudrateSwtCfgTbl = &(Can_stBaudrateSwtCfgTbl[ CAN_IDX0 ]);

CanConst uint8 * CanConst Can_tb_ptBRSwtCfgTbl_ARYSIZE = &(Can_stBRSwtCfgTbl_ARYSIZE);

CanConst uint32 Can_tb_u4RAMInitCycleMax = (uint32)CAN_CFG_RAM_INIT_CYCLE;

CanConst uint16 Can_tb_u2CmodeRst2ComWaitCnt = (uint16)(CAN_TB_CMODE_RST2COM_CYCLE);
CanConst uint16 Can_tb_u2CmodeAny2RstWaitCnt = (uint16)(CAN_TB_CMODE_ANY2RST_CYCLE);
CanConst uint16 Can_tb_u2GmodeAny2RstWaitCnt = (uint16)(CAN_TB_GMODE_ANY2RST_CYCLE);

CanConst uint8 Can_tb_u1CtrlNum = (uint8)CAN_CFG_CONTROLLERNUM_MAX;

CanConst uint16 Can_tb_u2MaxNumRxRule = (uint16)CAN_TB_MAX_NUMBER_OF_RX_RULE;

CanConst uint8 Can_tb_u1RxRulePageNum = (uint8)CAN_CFG_AFL_PAGE_NUM;

CanConst uint16 Can_tb_u2LastTestpage = (uint16)CAN_TB_TESTPAGENUM;

CanConst uint8 Can_tb_u1LastTestpageRegNum = (uint8)CAN_TB_TESTREGNUM;

CanConst uint32 Can_tb_u4GAFLCFG0Conf = CAN_TB_u4GAFLCFG0_CONF;
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
CanConst uint32 Can_tb_u4GAFLCFG1Conf = CAN_TB_u4GAFLCFG1_CONF;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
CanConst uint32 Can_tb_u4GAFLCFG2Conf = CAN_TB_u4GAFLCFG2_CONF;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
CanConst uint32 Can_tb_u4GAFLCFG3Conf = CAN_TB_u4GAFLCFG3_CONF;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */

CanConst uint32 Can_tb_u4GCFGConf = CAN_TB_u4GCFG_CONF;

CanConst uint32 Can_tb_u4GFDCFGConf = CAN_TB_u4GFDCFG_CONF;


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#if (CAN_CFG_CORE != CAN_G4MH)
/****************************************************************************/
/* Function Name | Can_tb_Interrupt                                         */
/* Description   | Interrupt Judgment Process                               */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) || (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) )
void
Can_tb_Interrupt( void )
{
    volatile uint32     u4DummyRead;
    uint8               u1IntResult;

    u1IntResult = (uint8)CAN_NONE;

#if ( (CAN_TX_TXFINISH_USE_0 == CAN_USE) || (CAN_RX_RXFINISH_USE_0 == CAN_USE) )
    u1IntResult = Can_tb_Interrupt_0();
#endif /* ( (CAN_TX_TXFINISH_USE_0 == CAN_USE) || (CAN_RX_RXFINISH_USE_0 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_1 == CAN_USE) || (CAN_RX_RXFINISH_USE_1 == CAN_USE) )
    if( u1IntResult == (uint8)CAN_NONE )
    {
        u1IntResult = Can_tb_Interrupt_1();
    }
#endif /*  ( (CAN_TX_TXFINISH_USE_1 == CAN_USE) || (CAN_RX_RXFINISH_USE_1 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_2 == CAN_USE) || (CAN_RX_RXFINISH_USE_2 == CAN_USE) )
    if( u1IntResult == (uint8)CAN_NONE )
    {
        u1IntResult = Can_tb_Interrupt_2();
    }
#endif /*  ( (CAN_TX_TXFINISH_USE_2 == CAN_USE) || (CAN_RX_RXFINISH_USE_2 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_3 == CAN_USE) || (CAN_RX_RXFINISH_USE_3 == CAN_USE) )
    if( u1IntResult == (uint8)CAN_NONE )
    {
        u1IntResult = Can_tb_Interrupt_3();
    }
#endif /*  ( (CAN_TX_TXFINISH_USE_3 == CAN_USE) || (CAN_RX_RXFINISH_USE_3 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_4 == CAN_USE) || (CAN_RX_RXFINISH_USE_4 == CAN_USE) )
    if( u1IntResult == (uint8)CAN_NONE )
    {
        u1IntResult = Can_tb_Interrupt_4();
    }
#endif /*  ( (CAN_TX_TXFINISH_USE_4 == CAN_USE) || (CAN_RX_RXFINISH_USE_4 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_5 == CAN_USE) || (CAN_RX_RXFINISH_USE_5 == CAN_USE) )
    if( u1IntResult == (uint8)CAN_NONE )
    {
        u1IntResult = Can_tb_Interrupt_5();
    }
#endif /*  ( (CAN_TX_TXFINISH_USE_5 == CAN_USE) || (CAN_RX_RXFINISH_USE_5 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_6 == CAN_USE) || (CAN_RX_RXFINISH_USE_6 == CAN_USE) )
    if( u1IntResult == (uint8)CAN_NONE )
    {
        u1IntResult = Can_tb_Interrupt_6();
    }
#endif /*  ( (CAN_TX_TXFINISH_USE_6 == CAN_USE) || (CAN_RX_RXFINISH_USE_6 == CAN_USE) ) */
#if ( (CAN_TX_TXFINISH_USE_7 == CAN_USE) || (CAN_RX_RXFINISH_USE_7 == CAN_USE) )
    if( u1IntResult == (uint8)CAN_NONE )
    {
        u1IntResult = Can_tb_Interrupt_7();
    }
#endif /*  ( (CAN_TX_TXFINISH_USE_7 == CAN_USE) || (CAN_RX_RXFINISH_USE_7 == CAN_USE) ) */

    if( u1IntResult == (uint8)CAN_NONE )
    {
#if (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE)
        Can_fs_ResetInterrupt( (uint8)CAN_CONTROLLER_0 );
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) */
#if (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE)
        Can_fs_ResetInterrupt( (uint8)CAN_CONTROLLER_1 );
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) */
#if (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE)
        Can_fs_ResetInterrupt( (uint8)CAN_CONTROLLER_2 );
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) */
#if (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE)
        Can_fs_ResetInterrupt( (uint8)CAN_CONTROLLER_3 );
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) */
#if (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE)
        Can_fs_ResetInterrupt( (uint8)CAN_CONTROLLER_4 );
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) */
#if (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE)
        Can_fs_ResetInterrupt( (uint8)CAN_CONTROLLER_5 );
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) */
#if (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE)
        Can_fs_ResetInterrupt( (uint8)CAN_CONTROLLER_6 );
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) */
#if (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE)
        Can_fs_ResetInterrupt( (uint8)CAN_CONTROLLER_7 );
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) */
    }

    u4DummyRead = *( Can_tb_stGlobalReg.ptu4GSTS );
}
#endif /* ( (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) || (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) ) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_tb_Interrupt_0                                       */
/* Description   | Interrupt Judgment Internal Process                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_USE_0 == CAN_USE) || (CAN_RX_RXFINISH_USE_0 == CAN_USE) )
static uint8
Can_tb_Interrupt_0( void )
{
    CanConst CanTbChRegType*  ptChReg;
    uint32                    u4CmSTS;
    uint8                     u1Ret;
#if (CAN_CFG_TX_PROCESSING_0 == CAN_INTERRUPT)
    uint8                     u1TxResult;
#endif /* (CAN_CFG_TX_PROCESSING_0 == CAN_INTERRUPT) */
#if (CAN_CFG_RX_PROCESSING_0 == CAN_INTERRUPT)
    uint8                     u1RxResult;
#endif /* (CAN_CFG_RX_PROCESSING_0 == CAN_INTERRUPT) */

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &( Can_tb_stChReg[ CAN_CONTROLLER_0 ] );

    u4CmSTS = *( ptChReg->ptu4CmSTS );

    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {
#if (CAN_CFG_TX_PROCESSING_0 == CAN_INTERRUPT)
        u1TxResult = Can_tx_ChkTxFinMbox( (uint8)CAN_CONTROLLER_0, (uint8)CAN_INTERRUPT );

        if ( u1TxResult == (uint8)CAN_EXIST )
        {
            u1Ret = (uint8)CAN_EXIST;
        }
        else
#endif /* (CAN_CFG_TX_PROCESSING_0 == CAN_INTERRUPT) */
        {
#if (CAN_CFG_RX_PROCESSING_0 == CAN_INTERRUPT)
            u1RxResult = Can_rx_ChkRxFinMbox( (uint8)CAN_CONTROLLER_0, (uint8)CAN_INTERRUPT );

            if ( u1RxResult == (uint8)CAN_EXIST )
            {
                u1Ret = (uint8)CAN_EXIST;
            }
#endif /* (CAN_CFG_RX_PROCESSING_0 == CAN_INTERRUPT) */
        }
    }

    return ( u1Ret );
}
#endif /* ( (CAN_TX_TXFINISH_USE_0 == CAN_USE) || (CAN_RX_RXFINISH_USE_0 == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_tb_Interrupt_1                                       */
/* Description   | Interrupt Judgment Internal Process                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_USE_1 == CAN_USE) || (CAN_RX_RXFINISH_USE_1 == CAN_USE) )
static uint8
Can_tb_Interrupt_1( void )
{
    CanConst CanTbChRegType*  ptChReg;
    uint32                    u4CmSTS;
    uint8                     u1Ret;
#if (CAN_CFG_TX_PROCESSING_1 == CAN_INTERRUPT)
    uint8                     u1TxResult;
#endif /* (CAN_CFG_TX_PROCESSING_1 == CAN_INTERRUPT) */
#if (CAN_CFG_RX_PROCESSING_1 == CAN_INTERRUPT)
    uint8                     u1RxResult;
#endif /* (CAN_CFG_RX_PROCESSING_1 == CAN_INTERRUPT) */

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &( Can_tb_stChReg[ CAN_CONTROLLER_1 ] );

    u4CmSTS = *( ptChReg->ptu4CmSTS );

    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {
#if (CAN_CFG_TX_PROCESSING_1 == CAN_INTERRUPT)
        u1TxResult = Can_tx_ChkTxFinMbox( (uint8)CAN_CONTROLLER_1, (uint8)CAN_INTERRUPT );

        if ( u1TxResult == (uint8)CAN_EXIST )
        {
            u1Ret = (uint8)CAN_EXIST;
        }
        else
#endif /* (CAN_CFG_TX_PROCESSING_1 == CAN_INTERRUPT) */
        {
#if (CAN_CFG_RX_PROCESSING_1 == CAN_INTERRUPT)
            u1RxResult = Can_rx_ChkRxFinMbox( (uint8)CAN_CONTROLLER_1, (uint8)CAN_INTERRUPT );

            if ( u1RxResult == (uint8)CAN_EXIST )
            {
                u1Ret = (uint8)CAN_EXIST;
            }
#endif /* (CAN_CFG_RX_PROCESSING_1 == CAN_INTERRUPT) */
        }
    }

    return ( u1Ret );
}
#endif /* ( (CAN_TX_TXFINISH_USE_1 == CAN_USE) || (CAN_RX_RXFINISH_USE_1 == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_tb_Interrupt_2                                       */
/* Description   | Interrupt Judgment Internal Process                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_USE_2 == CAN_USE) || (CAN_RX_RXFINISH_USE_2 == CAN_USE) )
static uint8
Can_tb_Interrupt_2( void )
{
    CanConst CanTbChRegType*  ptChReg;
    uint32                    u4CmSTS;
    uint8                     u1Ret;
#if (CAN_CFG_TX_PROCESSING_2 == CAN_INTERRUPT)
    uint8                     u1TxResult;
#endif /* (CAN_CFG_TX_PROCESSING_2 == CAN_INTERRUPT) */
#if (CAN_CFG_RX_PROCESSING_2 == CAN_INTERRUPT)
    uint8                     u1RxResult;
#endif /* (CAN_CFG_RX_PROCESSING_2 == CAN_INTERRUPT) */

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &( Can_tb_stChReg[ CAN_CONTROLLER_2 ] );

    u4CmSTS = *( ptChReg->ptu4CmSTS );

    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {
#if (CAN_CFG_TX_PROCESSING_2 == CAN_INTERRUPT)
        u1TxResult = Can_tx_ChkTxFinMbox( (uint8)CAN_CONTROLLER_2, (uint8)CAN_INTERRUPT );

        if ( u1TxResult == (uint8)CAN_EXIST )
        {
            u1Ret = (uint8)CAN_EXIST;
        }
        else
#endif /* (CAN_CFG_TX_PROCESSING_2 == CAN_INTERRUPT) */
        {
#if (CAN_CFG_RX_PROCESSING_2 == CAN_INTERRUPT)
            u1RxResult = Can_rx_ChkRxFinMbox( (uint8)CAN_CONTROLLER_2, (uint8)CAN_INTERRUPT );

            if ( u1RxResult == (uint8)CAN_EXIST )
            {
                u1Ret = (uint8)CAN_EXIST;
            }
#endif /* (CAN_CFG_RX_PROCESSING_2 == CAN_INTERRUPT) */
        }
    }

    return ( u1Ret );
}
#endif /* ( (CAN_TX_TXFINISH_USE_2 == CAN_USE) || (CAN_RX_RXFINISH_USE_2 == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_tb_Interrupt_3                                       */
/* Description   | Interrupt Judgment Internal Process                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_USE_3 == CAN_USE) || (CAN_RX_RXFINISH_USE_3 == CAN_USE) )
static uint8
Can_tb_Interrupt_3( void )
{
    CanConst CanTbChRegType*  ptChReg;
    uint32                    u4CmSTS;
    uint8                     u1Ret;
#if (CAN_CFG_TX_PROCESSING_3 == CAN_INTERRUPT)
    uint8                     u1TxResult;
#endif /* (CAN_CFG_TX_PROCESSING_3 == CAN_INTERRUPT) */
#if (CAN_CFG_RX_PROCESSING_3 == CAN_INTERRUPT)
    uint8                     u1RxResult;
#endif /* (CAN_CFG_RX_PROCESSING_3 == CAN_INTERRUPT) */

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &( Can_tb_stChReg[ CAN_CONTROLLER_3 ] );

    u4CmSTS = *( ptChReg->ptu4CmSTS );

    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {
#if (CAN_CFG_TX_PROCESSING_3 == CAN_INTERRUPT)
        u1TxResult = Can_tx_ChkTxFinMbox( (uint8)CAN_CONTROLLER_3, (uint8)CAN_INTERRUPT );

        if ( u1TxResult == (uint8)CAN_EXIST )
        {
            u1Ret = (uint8)CAN_EXIST;
        }
        else
#endif /* (CAN_CFG_TX_PROCESSING_3 == CAN_INTERRUPT) */
        {
#if (CAN_CFG_RX_PROCESSING_3 == CAN_INTERRUPT)
            u1RxResult = Can_rx_ChkRxFinMbox( (uint8)CAN_CONTROLLER_3, (uint8)CAN_INTERRUPT );

            if ( u1RxResult == (uint8)CAN_EXIST )
            {
                u1Ret = (uint8)CAN_EXIST;
            }
#endif /* (CAN_CFG_RX_PROCESSING_3 == CAN_INTERRUPT) */
        }
    }

    return ( u1Ret );
}
#endif /* ( (CAN_TX_TXFINISH_USE_3 == CAN_USE) || (CAN_RX_RXFINISH_USE_3 == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_tb_Interrupt_4                                       */
/* Description   | Interrupt Judgment Internal Process                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_USE_4 == CAN_USE) || (CAN_RX_RXFINISH_USE_4 == CAN_USE) )
static uint8
Can_tb_Interrupt_4( void )
{
    CanConst CanTbChRegType*  ptChReg;
    uint32                    u4CmSTS;
    uint8                     u1Ret;
#if (CAN_CFG_TX_PROCESSING_4 == CAN_INTERRUPT)
    uint8                     u1TxResult;
#endif /* (CAN_CFG_TX_PROCESSING_4 == CAN_INTERRUPT) */
#if (CAN_CFG_RX_PROCESSING_4 == CAN_INTERRUPT)
    uint8                     u1RxResult;
#endif /* (CAN_CFG_RX_PROCESSING_4 == CAN_INTERRUPT) */

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &( Can_tb_stChReg[ CAN_CONTROLLER_4 ] );

    u4CmSTS = *( ptChReg->ptu4CmSTS );

    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {
#if (CAN_CFG_TX_PROCESSING_4 == CAN_INTERRUPT)
        u1TxResult = Can_tx_ChkTxFinMbox( (uint8)CAN_CONTROLLER_4, (uint8)CAN_INTERRUPT );

        if ( u1TxResult == (uint8)CAN_EXIST )
        {
            u1Ret = (uint8)CAN_EXIST;
        }
        else
#endif /* (CAN_CFG_TX_PROCESSING_4 == CAN_INTERRUPT) */
        {
#if (CAN_CFG_RX_PROCESSING_4 == CAN_INTERRUPT)
            u1RxResult = Can_rx_ChkRxFinMbox( (uint8)CAN_CONTROLLER_4, (uint8)CAN_INTERRUPT );

            if ( u1RxResult == (uint8)CAN_EXIST )
            {
                u1Ret = (uint8)CAN_EXIST;
            }
#endif /* (CAN_CFG_RX_PROCESSING_4 == CAN_INTERRUPT) */
        }
    }

    return ( u1Ret );
}
#endif /* ( (CAN_TX_TXFINISH_USE_4 == CAN_USE) || (CAN_RX_RXFINISH_USE_4 == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_tb_Interrupt_5                                       */
/* Description   | Interrupt Judgment Internal Process                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_USE_5 == CAN_USE) || (CAN_RX_RXFINISH_USE_5 == CAN_USE) )
static uint8
Can_tb_Interrupt_5( void )
{
    CanConst CanTbChRegType*  ptChReg;
    uint32                    u4CmSTS;
    uint8                     u1Ret;
#if (CAN_CFG_TX_PROCESSING_5 == CAN_INTERRUPT)
    uint8                     u1TxResult;
#endif /* (CAN_CFG_TX_PROCESSING_5 == CAN_INTERRUPT) */
#if (CAN_CFG_RX_PROCESSING_5 == CAN_INTERRUPT)
    uint8                     u1RxResult;
#endif /* (CAN_CFG_RX_PROCESSING_5 == CAN_INTERRUPT) */

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &( Can_tb_stChReg[ CAN_CONTROLLER_5 ] );

    u4CmSTS = *( ptChReg->ptu4CmSTS );

    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {
#if (CAN_CFG_TX_PROCESSING_5 == CAN_INTERRUPT)
        u1TxResult = Can_tx_ChkTxFinMbox( (uint8)CAN_CONTROLLER_5, (uint8)CAN_INTERRUPT );

        if ( u1TxResult == (uint8)CAN_EXIST )
        {
            u1Ret = (uint8)CAN_EXIST;
        }
        else
#endif /* (CAN_CFG_TX_PROCESSING_5 == CAN_INTERRUPT) */
        {
#if (CAN_CFG_RX_PROCESSING_5 == CAN_INTERRUPT)
            u1RxResult = Can_rx_ChkRxFinMbox( (uint8)CAN_CONTROLLER_5, (uint8)CAN_INTERRUPT );

            if ( u1RxResult == (uint8)CAN_EXIST )
            {
                u1Ret = (uint8)CAN_EXIST;
            }
#endif /* (CAN_CFG_RX_PROCESSING_5 == CAN_INTERRUPT) */
        }
    }

    return ( u1Ret );
}
#endif /* ( (CAN_TX_TXFINISH_USE_5 == CAN_USE) || (CAN_RX_RXFINISH_USE_5 == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_tb_Interrupt_6                                       */
/* Description   | Interrupt Judgment Internal Process                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_USE_6 == CAN_USE) || (CAN_RX_RXFINISH_USE_6 == CAN_USE) )
static uint8
Can_tb_Interrupt_6( void )
{
    CanConst CanTbChRegType*  ptChReg;
    uint32                    u4CmSTS;
    uint8                     u1Ret;
#if (CAN_CFG_TX_PROCESSING_6 == CAN_INTERRUPT)
    uint8                     u1TxResult;
#endif /* (CAN_CFG_TX_PROCESSING_6 == CAN_INTERRUPT) */
#if (CAN_CFG_RX_PROCESSING_6 == CAN_INTERRUPT)
    uint8                     u1RxResult;
#endif /* (CAN_CFG_RX_PROCESSING_6 == CAN_INTERRUPT) */

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &( Can_tb_stChReg[ CAN_CONTROLLER_6 ] );

    u4CmSTS = *( ptChReg->ptu4CmSTS );

    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {
#if (CAN_CFG_TX_PROCESSING_6 == CAN_INTERRUPT)
        u1TxResult = Can_tx_ChkTxFinMbox( (uint8)CAN_CONTROLLER_6, (uint8)CAN_INTERRUPT );

        if ( u1TxResult == (uint8)CAN_EXIST )
        {
            u1Ret = (uint8)CAN_EXIST;
        }
        else
#endif /* (CAN_CFG_TX_PROCESSING_6 == CAN_INTERRUPT) */
        {
#if (CAN_CFG_RX_PROCESSING_6 == CAN_INTERRUPT)
            u1RxResult = Can_rx_ChkRxFinMbox( (uint8)CAN_CONTROLLER_6, (uint8)CAN_INTERRUPT );

            if ( u1RxResult == (uint8)CAN_EXIST )
            {
                u1Ret = (uint8)CAN_EXIST;
            }
#endif /* (CAN_CFG_RX_PROCESSING_6 == CAN_INTERRUPT) */
        }
    }

    return ( u1Ret );
}
#endif /* ( (CAN_TX_TXFINISH_USE_6 == CAN_USE) || (CAN_RX_RXFINISH_USE_6 == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_tb_Interrupt_7                                       */
/* Description   | Interrupt Judgment Internal Process                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_USE_7 == CAN_USE) || (CAN_RX_RXFINISH_USE_7 == CAN_USE) )
static uint8
Can_tb_Interrupt_7( void )
{
    CanConst CanTbChRegType*  ptChReg;
    uint32                    u4CmSTS;
    uint8                     u1Ret;
#if (CAN_CFG_TX_PROCESSING_7 == CAN_INTERRUPT)
    uint8                     u1TxResult;
#endif /* (CAN_CFG_TX_PROCESSING_7 == CAN_INTERRUPT) */
#if (CAN_CFG_RX_PROCESSING_7 == CAN_INTERRUPT)
    uint8                     u1RxResult;
#endif /* (CAN_CFG_RX_PROCESSING_7 == CAN_INTERRUPT) */

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &( Can_tb_stChReg[ CAN_CONTROLLER_7 ] );

    u4CmSTS = *( ptChReg->ptu4CmSTS );

    if( ( ( u4CmSTS & CAN_u4CMSTS_MODEALL_MSK ) == CAN_u4CMSTS_CMODE_COMM ) || ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF ) )
    {
#if (CAN_CFG_TX_PROCESSING_7 == CAN_INTERRUPT)
        u1TxResult = Can_tx_ChkTxFinMbox( (uint8)CAN_CONTROLLER_7, (uint8)CAN_INTERRUPT );

        if ( u1TxResult == (uint8)CAN_EXIST )
        {
            u1Ret = (uint8)CAN_EXIST;
        }
        else
#endif /* (CAN_CFG_TX_PROCESSING_7 == CAN_INTERRUPT) */
        {
#if (CAN_CFG_RX_PROCESSING_7 == CAN_INTERRUPT)
            u1RxResult = Can_rx_ChkRxFinMbox( (uint8)CAN_CONTROLLER_7, (uint8)CAN_INTERRUPT );

            if ( u1RxResult == (uint8)CAN_EXIST )
            {
                u1Ret = (uint8)CAN_EXIST;
            }
#endif /* (CAN_CFG_RX_PROCESSING_7 == CAN_INTERRUPT) */
        }
    }

    return ( u1Ret );
}
#endif /* ( (CAN_TX_TXFINISH_USE_7 == CAN_USE) || (CAN_RX_RXFINISH_USE_7 == CAN_USE) ) */
#endif /* (CAN_CFG_CORE != CAN_G4MH) */


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-1         :2022/12/15                                              */
/*  v2-2-2         :2023/05/10                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
