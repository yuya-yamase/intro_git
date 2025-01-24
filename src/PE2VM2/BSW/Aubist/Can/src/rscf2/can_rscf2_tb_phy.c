/* can_rscf2_tb_phy_c_m10700_v2-2-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF2/TB/PHYSICAL/CODE                                */
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
#include "../../cfg/rscf2/can_rscf2_cfg_ext.h"
#include "../../cfg/rscf2/can_rscf2_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_memmap.h>
#include <can/rscf2/can_rscf2.h>
#include <can/rscf2/can_rscf2_cm_phy.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf2/can_rscf2_tb_phy.h>
#include <can/rscf2/can_rscf2_st.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*======================================*/
/* コントローラ管理情報テーブル設定定義 */
/*======================================*/
/* 受信ルール設定テーブル・先頭インデックス */
#define CAN_TB_RXRULE_OFFSET0           ( 0U )
#define CAN_TB_RXRULE_OFFSET1           ( CAN_TB_RXRULE_OFFSET0 + CAN_CFG_HRHNUM_0 )
#define CAN_TB_RXRULE_OFFSET2           ( CAN_TB_RXRULE_OFFSET1 + CAN_CFG_HRHNUM_1 )
#define CAN_TB_RXRULE_OFFSET3           ( CAN_TB_RXRULE_OFFSET2 + CAN_CFG_HRHNUM_2 )
#define CAN_TB_RXRULE_OFFSET4           ( CAN_TB_RXRULE_OFFSET3 + CAN_CFG_HRHNUM_3 )
#define CAN_TB_RXRULE_OFFSET5           ( CAN_TB_RXRULE_OFFSET4 + CAN_CFG_HRHNUM_4 )
#define CAN_TB_RXRULE_OFFSET6           ( CAN_TB_RXRULE_OFFSET5 + CAN_CFG_HRHNUM_5 )
#define CAN_TB_RXRULE_OFFSET7           ( CAN_TB_RXRULE_OFFSET6 + CAN_CFG_HRHNUM_6 )


/*======================================*/
/* MBOX要素数テーブル設定定義           */
/*======================================*/
/*----------------------------------------*/
/* コントローラ別MBOX設定コンフィグ参照   */
/*  macro  : CAN_TB_MBSET( ch, mb )       */
/*  param1 : ch 0..7                      */
/*  param2 : mb 000..143                  */
/*----------------------------------------*/
#define CAN_TB_MBSET_0( mb )            ( CAN_CFG_MBOXSET_0_MB##mb )
#define CAN_TB_MBSET_1( mb )            ( CAN_CFG_MBOXSET_1_MB##mb )
#define CAN_TB_MBSET_2( mb )            ( CAN_CFG_MBOXSET_2_MB##mb )
#define CAN_TB_MBSET_3( mb )            ( CAN_CFG_MBOXSET_3_MB##mb )
#define CAN_TB_MBSET_4( mb )            ( CAN_CFG_MBOXSET_4_MB##mb )
#define CAN_TB_MBSET_5( mb )            ( CAN_CFG_MBOXSET_5_MB##mb )
#define CAN_TB_MBSET_6( mb )            ( CAN_CFG_MBOXSET_6_MB##mb )
#define CAN_TB_MBSET_7( mb )            ( CAN_CFG_MBOXSET_7_MB##mb )
#define CAN_TB_MBSET( ch, mb )          ( CAN_TB_MBSET_##ch( mb ) )


/*----------------------------------------*/
/* 種別毎MBOX数                           */
/*  macro  : CAN_TB_MBNUM( ch, kind )     */
/*  param1 : ch   0..7                    */
/*  param2 : kind UTX/TX/RX               */
/*----------------------------------------*/
#define CAN_TB_MBNUM_UTX( ch )          ( CAN_CFG_USERTXMBOXNUM_##ch )
#define CAN_TB_MBNUM_TX( ch )           ( ( CAN_CFG_HTHNUM_##ch ) + ( CAN_TB_MBNUM_UTX( ch ) ) )
#define CAN_TB_MBNUM_RX( ch )           ( CAN_CFG_HRHNUM_##ch )

#define CAN_TB_MBNUM( ch, kind )        ( CAN_TB_MBNUM_##kind( ch ) )


/*======================================*/
/* RS-CANレジスタアドレス設定定義       */
/*======================================*/
/* CANレジスタベースアドレス */
#define CAN_TB_REG_BASE_ADDR            ( CAN_CFG_REG_BASEADDR )

/* コントローラ別レジスタアドレス */
#define CAN_TB_ptu4CH0_CmCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000000UL) )
#define CAN_TB_ptu4CH0_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000004UL) )
#define CAN_TB_ptu4CH0_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000008UL) )
#define CAN_TB_ptu4CH0_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000000CUL) )
#define CAN_TB_ptu4CH1_CmCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000010UL) )
#define CAN_TB_ptu4CH1_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000014UL) )
#define CAN_TB_ptu4CH1_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000018UL) )
#define CAN_TB_ptu4CH1_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000001CUL) )
#define CAN_TB_ptu4CH2_CmCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000020UL) )
#define CAN_TB_ptu4CH2_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000024UL) )
#define CAN_TB_ptu4CH2_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000028UL) )
#define CAN_TB_ptu4CH2_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000002CUL) )
#define CAN_TB_ptu4CH3_CmCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000030UL) )
#define CAN_TB_ptu4CH3_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000034UL) )
#define CAN_TB_ptu4CH3_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000038UL) )
#define CAN_TB_ptu4CH3_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000003CUL) )
#define CAN_TB_ptu4CH4_CmCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000040UL) )
#define CAN_TB_ptu4CH4_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000044UL) )
#define CAN_TB_ptu4CH4_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000048UL) )
#define CAN_TB_ptu4CH4_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000004CUL) )
#define CAN_TB_ptu4CH5_CmCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000050UL) )
#define CAN_TB_ptu4CH5_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000054UL) )
#define CAN_TB_ptu4CH5_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000058UL) )
#define CAN_TB_ptu4CH5_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000005CUL) )
#define CAN_TB_ptu4CH6_CmCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000060UL) )
#define CAN_TB_ptu4CH6_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000064UL) )
#define CAN_TB_ptu4CH6_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000068UL) )
#define CAN_TB_ptu4CH6_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000006CUL) )
#define CAN_TB_ptu4CH7_CmCFG_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000070UL) )
#define CAN_TB_ptu4CH7_CmCTR_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000074UL) )
#define CAN_TB_ptu4CH7_CmSTS_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000078UL) )
#define CAN_TB_ptu4CH7_CmERFL_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000007CUL) )

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
#define CAN_TB_ptu4CH0_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000500UL) )
#define CAN_TB_ptu4CH0_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000504UL) )
#define CAN_TB_ptu4CH0_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000508UL) )
#define CAN_TB_ptu4CH0_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000050CUL) )
#define CAN_TB_ptu4CH0_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000510UL) )
#define CAN_TB_ptu4CH1_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000520UL) )
#define CAN_TB_ptu4CH1_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000524UL) )
#define CAN_TB_ptu4CH1_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000528UL) )
#define CAN_TB_ptu4CH1_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000052CUL) )
#define CAN_TB_ptu4CH1_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000530UL) )
#define CAN_TB_ptu4CH2_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000540UL) )
#define CAN_TB_ptu4CH2_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000544UL) )
#define CAN_TB_ptu4CH2_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000548UL) )
#define CAN_TB_ptu4CH2_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000054CUL) )
#define CAN_TB_ptu4CH2_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000550UL) )
#define CAN_TB_ptu4CH3_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000560UL) )
#define CAN_TB_ptu4CH3_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000564UL) )
#define CAN_TB_ptu4CH3_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000568UL) )
#define CAN_TB_ptu4CH3_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000056CUL) )
#define CAN_TB_ptu4CH3_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000570UL) )
#define CAN_TB_ptu4CH4_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000580UL) )
#define CAN_TB_ptu4CH4_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000584UL) )
#define CAN_TB_ptu4CH4_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000588UL) )
#define CAN_TB_ptu4CH4_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000058CUL) )
#define CAN_TB_ptu4CH4_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000590UL) )
#define CAN_TB_ptu4CH5_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005A0UL) )
#define CAN_TB_ptu4CH5_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005A4UL) )
#define CAN_TB_ptu4CH5_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005A8UL) )
#define CAN_TB_ptu4CH5_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005ACUL) )
#define CAN_TB_ptu4CH5_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005B0UL) )
#define CAN_TB_ptu4CH6_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005C0UL) )
#define CAN_TB_ptu4CH6_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005C4UL) )
#define CAN_TB_ptu4CH6_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005C8UL) )
#define CAN_TB_ptu4CH6_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005CCUL) )
#define CAN_TB_ptu4CH6_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005D0UL) )
#define CAN_TB_ptu4CH7_CmDCFG_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005E0UL) )
#define CAN_TB_ptu4CH7_CmFDCFG_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005E4UL) )
#define CAN_TB_ptu4CH7_CmFDCTR_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005E8UL) )
#define CAN_TB_ptu4CH7_CmFDSTS_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005ECUL) )
#define CAN_TB_ptu4CH7_CmFDCRC_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000005F0UL) )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */

#define CAN_TB_ptu2CH0_TMTRSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000350UL) )
#define CAN_TB_ptu2CH1_TMTRSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000352UL) )
#define CAN_TB_ptu2CH2_TMTRSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000354UL) )
#define CAN_TB_ptu2CH3_TMTRSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000356UL) )
#define CAN_TB_ptu2CH4_TMTRSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000358UL) )
#define CAN_TB_ptu2CH5_TMTRSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000035AUL) )
#define CAN_TB_ptu2CH6_TMTRSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000035CUL) )
#define CAN_TB_ptu2CH7_TMTRSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000035EUL) )

#define CAN_TB_ptu2CH0_TMTARSTSy_ADDR   ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000360UL) )
#define CAN_TB_ptu2CH1_TMTARSTSy_ADDR   ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000362UL) )
#define CAN_TB_ptu2CH2_TMTARSTSy_ADDR   ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000364UL) )
#define CAN_TB_ptu2CH3_TMTARSTSy_ADDR   ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000366UL) )
#define CAN_TB_ptu2CH4_TMTARSTSy_ADDR   ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000368UL) )
#define CAN_TB_ptu2CH5_TMTARSTSy_ADDR   ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000036AUL) )
#define CAN_TB_ptu2CH6_TMTARSTSy_ADDR   ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000036CUL) )
#define CAN_TB_ptu2CH7_TMTARSTSy_ADDR   ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000036EUL) )

#define CAN_TB_ptu2CH0_TMTCSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000370UL) )
#define CAN_TB_ptu2CH1_TMTCSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000372UL) )
#define CAN_TB_ptu2CH2_TMTCSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000374UL) )
#define CAN_TB_ptu2CH3_TMTCSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000376UL) )
#define CAN_TB_ptu2CH4_TMTCSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000378UL) )
#define CAN_TB_ptu2CH5_TMTCSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000037AUL) )
#define CAN_TB_ptu2CH6_TMTCSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000037CUL) )
#define CAN_TB_ptu2CH7_TMTCSTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000037EUL) )

#define CAN_TB_ptu2CH0_TMTASTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000380UL) )
#define CAN_TB_ptu2CH1_TMTASTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000382UL) )
#define CAN_TB_ptu2CH2_TMTASTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000384UL) )
#define CAN_TB_ptu2CH3_TMTASTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000386UL) )
#define CAN_TB_ptu2CH4_TMTASTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000388UL) )
#define CAN_TB_ptu2CH5_TMTASTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000038AUL) )
#define CAN_TB_ptu2CH6_TMTASTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000038CUL) )
#define CAN_TB_ptu2CH7_TMTASTSy_ADDR    ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000038EUL) )

#define CAN_TB_ptu2CH0_TMIECy_ADDR      ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000390UL) )
#define CAN_TB_ptu2CH1_TMIECy_ADDR      ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000392UL) )
#define CAN_TB_ptu2CH2_TMIECy_ADDR      ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000394UL) )
#define CAN_TB_ptu2CH3_TMIECy_ADDR      ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000396UL) )
#define CAN_TB_ptu2CH4_TMIECy_ADDR      ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x00000398UL) )
#define CAN_TB_ptu2CH5_TMIECy_ADDR      ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000039AUL) )
#define CAN_TB_ptu2CH6_TMIECy_ADDR      ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000039CUL) )
#define CAN_TB_ptu2CH7_TMIECy_ADDR      ( (volatile uint16 *)(CAN_TB_REG_BASE_ADDR + 0x0000039EUL) )

#define CAN_TB_ptu4CH0_TXQCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003A0UL) )
#define CAN_TB_ptu4CH1_TXQCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003A4UL) )
#define CAN_TB_ptu4CH2_TXQCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003A8UL) )
#define CAN_TB_ptu4CH3_TXQCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003ACUL) )
#define CAN_TB_ptu4CH4_TXQCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003B0UL) )
#define CAN_TB_ptu4CH5_TXQCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003B4UL) )
#define CAN_TB_ptu4CH6_TXQCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003B8UL) )
#define CAN_TB_ptu4CH7_TXQCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003BCUL) )

#define CAN_TB_ptu4CH0_TXQSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003C0UL) )
#define CAN_TB_ptu4CH1_TXQSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003C4UL) )
#define CAN_TB_ptu4CH2_TXQSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003C8UL) )
#define CAN_TB_ptu4CH3_TXQSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003CCUL) )
#define CAN_TB_ptu4CH4_TXQSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003D0UL) )
#define CAN_TB_ptu4CH5_TXQSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003D4UL) )
#define CAN_TB_ptu4CH6_TXQSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003D8UL) )
#define CAN_TB_ptu4CH7_TXQSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003DCUL) )

#define CAN_TB_ptu4CH0_TXQPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003E0UL) )
#define CAN_TB_ptu4CH1_TXQPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003E4UL) )
#define CAN_TB_ptu4CH2_TXQPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003E8UL) )
#define CAN_TB_ptu4CH3_TXQPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003ECUL) )
#define CAN_TB_ptu4CH4_TXQPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003F0UL) )
#define CAN_TB_ptu4CH5_TXQPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003F4UL) )
#define CAN_TB_ptu4CH6_TXQPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003F8UL) )
#define CAN_TB_ptu4CH7_TXQPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000003FCUL) )

#define CAN_TB_ptu4CH0_THLCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000400UL) )
#define CAN_TB_ptu4CH1_THLCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000404UL) )
#define CAN_TB_ptu4CH2_THLCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000408UL) )
#define CAN_TB_ptu4CH3_THLCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000040CUL) )
#define CAN_TB_ptu4CH4_THLCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000410UL) )
#define CAN_TB_ptu4CH5_THLCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000414UL) )
#define CAN_TB_ptu4CH6_THLCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000418UL) )
#define CAN_TB_ptu4CH7_THLCCm_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000041CUL) )

#define CAN_TB_ptu4CH0_THLSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000420UL) )
#define CAN_TB_ptu4CH1_THLSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000424UL) )
#define CAN_TB_ptu4CH2_THLSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000428UL) )
#define CAN_TB_ptu4CH3_THLSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000042CUL) )
#define CAN_TB_ptu4CH4_THLSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000430UL) )
#define CAN_TB_ptu4CH5_THLSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000434UL) )
#define CAN_TB_ptu4CH6_THLSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000438UL) )
#define CAN_TB_ptu4CH7_THLSTSm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000043CUL) )

#define CAN_TB_ptu4CH0_THLPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000440UL) )
#define CAN_TB_ptu4CH1_THLPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000444UL) )
#define CAN_TB_ptu4CH2_THLPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000448UL) )
#define CAN_TB_ptu4CH3_THLPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000044CUL) )
#define CAN_TB_ptu4CH4_THLPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000450UL) )
#define CAN_TB_ptu4CH5_THLPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000454UL) )
#define CAN_TB_ptu4CH6_THLPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000458UL) )
#define CAN_TB_ptu4CH7_THLPCTRm_ADDR    ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000045CUL) )

#define CAN_TB_ptu4CH0_CFSTSk_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000178UL) )
#define CAN_TB_ptu4CH1_CFSTSk_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000184UL) )
#define CAN_TB_ptu4CH2_CFSTSk_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000190UL) )
#define CAN_TB_ptu4CH3_CFSTSk_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000019CUL) )
#define CAN_TB_ptu4CH4_CFSTSk_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001A8UL) )
#define CAN_TB_ptu4CH5_CFSTSk_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001B4UL) )
#define CAN_TB_ptu4CH6_CFSTSk_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001C0UL) )
#define CAN_TB_ptu4CH7_CFSTSk_ADDR      ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001CCUL) )

#define CAN_TB_ptu1CH0_TMSTSp_ADDR      ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x000002D0UL) )
#define CAN_TB_ptu1CH1_TMSTSp_ADDR      ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x000002E0UL) )
#define CAN_TB_ptu1CH2_TMSTSp_ADDR      ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x000002F0UL) )
#define CAN_TB_ptu1CH3_TMSTSp_ADDR      ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x00000300UL) )
#define CAN_TB_ptu1CH4_TMSTSp_ADDR      ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x00000310UL) )
#define CAN_TB_ptu1CH5_TMSTSp_ADDR      ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x00000320UL) )
#define CAN_TB_ptu1CH6_TMSTSp_ADDR      ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x00000330UL) )
#define CAN_TB_ptu1CH7_TMSTSp_ADDR      ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x00000340UL) )

#define CAN_TB_ptu4CH0_CFCCk_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000118UL) )
#define CAN_TB_ptu4CH1_CFCCk_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000124UL) )
#define CAN_TB_ptu4CH2_CFCCk_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000130UL) )
#define CAN_TB_ptu4CH3_CFCCk_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000013CUL) )
#define CAN_TB_ptu4CH4_CFCCk_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000148UL) )
#define CAN_TB_ptu4CH5_CFCCk_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000154UL) )
#define CAN_TB_ptu4CH6_CFCCk_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000160UL) )
#define CAN_TB_ptu4CH7_CFCCk_ADDR       ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000016CUL) )

#define CAN_TB_ptu4CH0_CFPCTRk_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001D8UL) )
#define CAN_TB_ptu4CH1_CFPCTRk_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001E4UL) )
#define CAN_TB_ptu4CH2_CFPCTRk_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001F0UL) )
#define CAN_TB_ptu4CH3_CFPCTRk_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000001FCUL) )
#define CAN_TB_ptu4CH4_CFPCTRk_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000208UL) )
#define CAN_TB_ptu4CH5_CFPCTRk_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000214UL) )
#define CAN_TB_ptu4CH6_CFPCTRk_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000220UL) )
#define CAN_TB_ptu4CH7_CFPCTRk_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000022CUL) )

#define CAN_TB_ptu1CH0_TMCp_ADDR        ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x00000250UL) )
#define CAN_TB_ptu1CH1_TMCp_ADDR        ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x00000260UL) )
#define CAN_TB_ptu1CH2_TMCp_ADDR        ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x00000270UL) )
#define CAN_TB_ptu1CH3_TMCp_ADDR        ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x00000280UL) )
#define CAN_TB_ptu1CH4_TMCp_ADDR        ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x00000290UL) )
#define CAN_TB_ptu1CH5_TMCp_ADDR        ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x000002A0UL) )
#define CAN_TB_ptu1CH6_TMCp_ADDR        ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x000002B0UL) )
#define CAN_TB_ptu1CH7_TMCp_ADDR        ( (volatile uint8 *)(CAN_TB_REG_BASE_ADDR + 0x000002C0UL) )

#if (CAN_OPEMODE == CAN_OPEMODE_CAN)
#define CAN_TB_ptstCH0_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00000E80UL) )
#define CAN_TB_ptstCH1_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00000EB0UL) )
#define CAN_TB_ptstCH2_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00000EE0UL) )
#define CAN_TB_ptstCH3_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00000F10UL) )
#define CAN_TB_ptstCH4_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00000F40UL) )
#define CAN_TB_ptstCH5_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00000F70UL) )
#define CAN_TB_ptstCH6_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00000FA0UL) )
#define CAN_TB_ptstCH7_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00000FD0UL) )
#else /* (CAN_OPEMODE != CAN_OPEMODE_CAN) */
#define CAN_TB_ptstCH0_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00003400UL) )
#define CAN_TB_ptstCH1_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00003580UL) )
#define CAN_TB_ptstCH2_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00003700UL) )
#define CAN_TB_ptstCH3_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00003880UL) )
#define CAN_TB_ptstCH4_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00003A00UL) )
#define CAN_TB_ptstCH5_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00003B80UL) )
#define CAN_TB_ptstCH6_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00003D00UL) )
#define CAN_TB_ptstCH7_CF_ADDR          ( (volatile CanTbRegCANCFType *)(CAN_TB_REG_BASE_ADDR + 0x00003E80UL) )
#endif /* (CAN_OPEMODE) */

#if (CAN_OPEMODE == CAN_OPEMODE_CAN)
#define CAN_TB_ptstCH0_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00001000UL) )
#define CAN_TB_ptstCH1_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00001100UL) )
#define CAN_TB_ptstCH2_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00001200UL) )
#define CAN_TB_ptstCH3_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00001300UL) )
#define CAN_TB_ptstCH4_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00001400UL) )
#define CAN_TB_ptstCH5_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00001500UL) )
#define CAN_TB_ptstCH6_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00001600UL) )
#define CAN_TB_ptstCH7_TM_ADDR          ( (volatile CanTbRegCANTMType *)(CAN_TB_REG_BASE_ADDR + 0x00001700UL) )
#else /* (CAN_OPEMODE != CAN_OPEMODE_CAN) */
#define CAN_TB_ptstCH0_TM_ADDR          ( (volatile CanTbRegCANTMType *)   (CAN_TB_REG_BASE_ADDR + 0x00004000UL) )
#define CAN_TB_ptstCH0_TM_MERGE_ADDR    ( (volatile CanTbRegCANTMMRGType *)(CAN_TB_REG_BASE_ADDR + 0x00004000UL) )
#define CAN_TB_ptstCH1_TM_ADDR          ( (volatile CanTbRegCANTMType *)   (CAN_TB_REG_BASE_ADDR + 0x00004200UL) )
#define CAN_TB_ptstCH1_TM_MERGE_ADDR    ( (volatile CanTbRegCANTMMRGType *)(CAN_TB_REG_BASE_ADDR + 0x00004200UL) )
#define CAN_TB_ptstCH2_TM_ADDR          ( (volatile CanTbRegCANTMType *)   (CAN_TB_REG_BASE_ADDR + 0x00004400UL) )
#define CAN_TB_ptstCH2_TM_MERGE_ADDR    ( (volatile CanTbRegCANTMMRGType *)(CAN_TB_REG_BASE_ADDR + 0x00004400UL) )
#define CAN_TB_ptstCH3_TM_ADDR          ( (volatile CanTbRegCANTMType *)   (CAN_TB_REG_BASE_ADDR + 0x00004600UL) )
#define CAN_TB_ptstCH3_TM_MERGE_ADDR    ( (volatile CanTbRegCANTMMRGType *)(CAN_TB_REG_BASE_ADDR + 0x00004600UL) )
#define CAN_TB_ptstCH4_TM_ADDR          ( (volatile CanTbRegCANTMType *)   (CAN_TB_REG_BASE_ADDR + 0x00004800UL) )
#define CAN_TB_ptstCH4_TM_MERGE_ADDR    ( (volatile CanTbRegCANTMMRGType *)(CAN_TB_REG_BASE_ADDR + 0x00004800UL) )
#define CAN_TB_ptstCH5_TM_ADDR          ( (volatile CanTbRegCANTMType *)   (CAN_TB_REG_BASE_ADDR + 0x00004A00UL) )
#define CAN_TB_ptstCH5_TM_MERGE_ADDR    ( (volatile CanTbRegCANTMMRGType *)(CAN_TB_REG_BASE_ADDR + 0x00004A00UL) )
#define CAN_TB_ptstCH6_TM_ADDR          ( (volatile CanTbRegCANTMType *)   (CAN_TB_REG_BASE_ADDR + 0x00004C00UL) )
#define CAN_TB_ptstCH6_TM_MERGE_ADDR    ( (volatile CanTbRegCANTMMRGType *)(CAN_TB_REG_BASE_ADDR + 0x00004C00UL) )
#define CAN_TB_ptstCH7_TM_ADDR          ( (volatile CanTbRegCANTMType *)   (CAN_TB_REG_BASE_ADDR + 0x00004E00UL) )
#define CAN_TB_ptstCH7_TM_MERGE_ADDR    ( (volatile CanTbRegCANTMMRGType *)(CAN_TB_REG_BASE_ADDR + 0x00004E00UL) )
#endif /* (CAN_OPEMODE) */

#if (CAN_OPEMODE == CAN_OPEMODE_CAN)
#define CAN_TB_ptu4CH0_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001800UL) )
#define CAN_TB_ptu4CH1_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001804UL) )
#define CAN_TB_ptu4CH2_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001808UL) )
#define CAN_TB_ptu4CH3_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000180CUL) )
#define CAN_TB_ptu4CH4_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001810UL) )
#define CAN_TB_ptu4CH5_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001814UL) )
#define CAN_TB_ptu4CH6_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001818UL) )
#define CAN_TB_ptu4CH7_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000181CUL) )
#else /* (CAN_OPEMODE != CAN_OPEMODE_CAN) */
#define CAN_TB_ptu4CH0_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00006000UL) )
#define CAN_TB_ptu4CH1_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00006004UL) )
#define CAN_TB_ptu4CH2_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00006008UL) )
#define CAN_TB_ptu4CH3_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000600CUL) )
#define CAN_TB_ptu4CH4_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00006010UL) )
#define CAN_TB_ptu4CH5_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00006014UL) )
#define CAN_TB_ptu4CH6_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00006018UL) )
#define CAN_TB_ptu4CH7_THLACCm_ADDR     ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000601CUL) )
#endif /* (CAN_OPEMODE) */

/* グローバルレジスタアドレス */
#define CAN_TB_ptu4GCFG_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000084UL) )
#define CAN_TB_ptu4GCTR_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000088UL) )
#define CAN_TB_ptu4GSTS_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000008CUL) )
#define CAN_TB_ptu4GERFL_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000090UL) )
#define CAN_TB_ptu4GTSC_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000094UL) )
#define CAN_TB_ptu4GAFLECTR_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000098UL) )
#define CAN_TB_ptu4GAFLCFG_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000009CUL) )
#define CAN_TB_ptu4RMNB_ADDR            ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000000A4UL) )
#define CAN_TB_ptu4RMNDy_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000000A8UL) )
#define CAN_TB_ptu4RFCCx_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000000B8UL) )
#define CAN_TB_ptu4RFSTSx_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000000D8UL) )
#define CAN_TB_ptu4RFPCTRx_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000000F8UL) )
#define CAN_TB_ptu4FESTS_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000238UL) )
#define CAN_TB_ptu4FFSTS_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000023CUL) )
#define CAN_TB_ptu4FMSTS_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000240UL) )
#define CAN_TB_ptu4RFISTS_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000244UL) )
#define CAN_TB_ptu4CFRISTS_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000248UL) )
#define CAN_TB_ptu4CFTISTS_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000024CUL) )
#define CAN_TB_ptu4GTINTSTS_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000460UL) )
#define CAN_TB_ptu4GTSTCFG_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000468UL) )
#define CAN_TB_ptu4GTSTCTR_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000046CUL) )
#define CAN_TB_ptu4GFDCFG_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000474UL) )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
#define CAN_TB_ptu4GCRCCFG_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000478UL) )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#define CAN_TB_ptu4GLOCKK_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x0000047CUL) )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
#define CAN_TB_ptu4CDTCT_ADDR           ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000490UL) )
#define CAN_TB_ptu4CDTSTS_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00000494UL) )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#define CAN_TB_ptu4GRMCFG_ADDR          ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x000004FCUL) )
#if (CAN_OPEMODE == CAN_OPEMODE_CAN)
#define CAN_TB_ptstGAFL_ADDR            ( (volatile CanTbRegRxRuleType *)(CAN_TB_REG_BASE_ADDR + 0x00000500UL) )
#define CAN_TB_ptstRM_ADDR              ( (volatile CanTbRegCANRMType *)(CAN_TB_REG_BASE_ADDR + 0x00000600UL) )
#define CAN_TB_ptstRF_ADDR              ( (volatile CanTbRegCANRFType *)(CAN_TB_REG_BASE_ADDR + 0x00000E00UL) )
#define CAN_TB_ptu4RPGACCr_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00001900UL) )
#else /* (CAN_OPEMODE != CAN_OPEMODE_CAN) */
#define CAN_TB_ptstGAFL_ADDR            ( (volatile CanTbRegRxRuleType *)(CAN_TB_REG_BASE_ADDR + 0x00001000UL) )
#define CAN_TB_ptstRM_ADDR              ( (volatile CanTbRegCANRMType *)(CAN_TB_REG_BASE_ADDR + 0x00002000UL) )
#define CAN_TB_ptstRF_ADDR              ( (volatile CanTbRegCANRFType *)(CAN_TB_REG_BASE_ADDR + 0x00003000UL) )
#define CAN_TB_ptu4RPGACCr_ADDR         ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00006400UL) )
#endif /* (CAN_OPEMODE) */
#define CAN_TB_ptu4CANFDMDR_ADDR        ( (volatile uint32 *)(CAN_TB_REG_BASE_ADDR + 0x00008000UL) )


/*======================================*/
/* レジスタ固着チェック分割定義         */
/*======================================*/
/* レジスタ固着チェック対象RAMサイズ */
/* 本マイコンではコントローラ別CAN RAMサイズ(チャネル0)の値を */
/* レジスタ固着チェック対象RAMサイズとして使用する            */
#define CAN_TB_RAM_SIZE                     ( CAN_CFG_RAM_SIZE_0 )

/* レジスタ固着チェック総ページ数 */
/* ※ プリプロ処理でのみ使用する前提で除算利用                                 */
#define CAN_TB_TESTPAGENUM                  ( CAN_TB_RAM_SIZE / 256UL )

/* レジスタ固着チェック端数レジスタ数 */
/* ※ プリプロ処理でのみ使用する前提で剰余算、除算利用                         */
#define CAN_TB_TESTREGNUM                   ( ( CAN_TB_RAM_SIZE % 256UL ) / 4UL )

/* レジスタ固着チェック周期毎ページ数 */
/* ※ プリプロ処理でのみ使用する前提で除算利用                                 */
/* 本マクロは (CAN_CFG_CHKSTKREG_LIMIT > 1) の場合のみ使用されるように設計する */
#define CAN_TB_TESTPAGE_CYCLE               ( ( CAN_TB_TESTPAGENUM - 1UL ) / ( (uint32)CAN_CFG_CHKSTKREG_LIMIT - 1UL ) )

/* レジスタ固着チェックページ端数 */
/* ※ プリプロ処理でのみ使用する前提で剰余算利用                               */
/* 本マクロは (CAN_CFG_CHKSTKREG_LIMIT > 1) の場合のみ使用されるように設計する */
#define CAN_TB_TESTPAGE_MOD                 ( ( CAN_TB_TESTPAGENUM - 1UL ) % ( (uint32)CAN_CFG_CHKSTKREG_LIMIT - 1UL ) )

/* レジスタ固着チェック周期毎ページ端数 */
/* CAN_TB_TESTPAGE_MOD以下の周期では、CAN_TB_TESTPAGE_CYCLEより1ページ多くチェックする */
#define CAN_TB_TESTPAGE_MOD_CYCLE(num)      ( ( ( num ) > CAN_TB_TESTPAGE_MOD ) ? 0UL : 1UL )


/* レジスタ固着チェックページ数 */
/* 分割する場合、1周期目は1ページ固定、それ以降の周期で残りのページを等分する */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 1U)
#define CAN_TB_STUCK_CHK_PAGE_0             ( (CAN_CFG_CHKSTKREG_LIMIT == 1U) ? CAN_TB_TESTPAGENUM : 1UL )   /*   1回目チェックページ数         */
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 1U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 5U)
#define CAN_TB_STUCK_CHK_PAGE_1             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 1UL ) )     /*   2回目チェックページ数         */
#define CAN_TB_STUCK_CHK_PAGE_2             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 2UL ) )     /*   3回目チェックページ数         */
#define CAN_TB_STUCK_CHK_PAGE_3             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 3UL ) )     /*   4回目チェックページ数         */
#define CAN_TB_STUCK_CHK_PAGE_4             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 4UL ) )     /*   5回目チェックページ数         */
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 5U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 10U)
#define CAN_TB_STUCK_CHK_PAGE_5             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 5UL ) )     /*   6回目チェックページ数         */
#define CAN_TB_STUCK_CHK_PAGE_6             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 6UL ) )     /*   7回目チェックページ数         */
#define CAN_TB_STUCK_CHK_PAGE_7             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 7UL ) )     /*   8回目チェックページ数         */
#define CAN_TB_STUCK_CHK_PAGE_8             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 8UL ) )     /*   9回目チェックページ数         */
#define CAN_TB_STUCK_CHK_PAGE_9             ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 9UL ) )     /*  10回目チェックページ数         */
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 10U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 12U)
#define CAN_TB_STUCK_CHK_PAGE_10            ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 10UL ) )    /*  11回目チェックページ数         */
#define CAN_TB_STUCK_CHK_PAGE_11            ( CAN_TB_TESTPAGE_CYCLE + CAN_TB_TESTPAGE_MOD_CYCLE( 11UL ) )    /*  12回目チェックページ数         */
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 12U) */

/* レジスタ固着チェック開始ページ */
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


/*======================================*/
/* 受信ルール設定値テーブル定義         */
/*======================================*/
/* 受信ルール設定値テーブル用ダミー値(受信ルールID用) */
#define CAN_TB_u4GAFLID_DUMMY               ( 0xFFFFFFFFUL )
/* 受信ルール設定値テーブル用ダミー値(受信ルールポインタ0用) */
#define CAN_TB_u4GAFLP0_DUMMY               ( 0x00000000UL )
/* 受信ルール設定値テーブル用ダミー値(受信ルールポインタ1用) */
#define CAN_TB_u4GAFLP1_DUMMY               ( 0x00000000UL )
/* 受信ルール設定値テーブル用ダミー値(受信IDマスク番号用) */
#define CAN_TB_u1RXMASK_DUMMY               ( 0U )

/* 受信MBOX処理方式 */
#define CAN_TB_u4RXMB_CH0_INT               ( (uint32)( 0x00000001UL << ( ( 0U * 3U ) + 2U + 8U ) ) )
#define CAN_TB_u4RXMB_CH1_INT               ( (uint32)( 0x00000001UL << ( ( 1U * 3U ) + 2U + 8U ) ) )
#define CAN_TB_u4RXMB_CH2_INT               ( (uint32)( 0x00000001UL << ( ( 2U * 3U ) + 2U + 8U ) ) )
#define CAN_TB_u4RXMB_CH3_INT               ( (uint32)( 0x00000001UL << ( ( 3U * 3U ) + 2U + 8U ) ) )
#define CAN_TB_u4RXMB_CH4_INT               ( (uint32)( 0x00000001UL << ( ( 4U * 3U ) + 2U + 8U ) ) )
#define CAN_TB_u4RXMB_CH5_INT               ( (uint32)( 0x00000001UL << ( ( 5U * 3U ) + 2U + 8U ) ) )
#define CAN_TB_u4RXMB_CH6_INT               ( (uint32)( 0x00000001UL << ( ( 6U * 3U ) + 2U + 8U ) ) )
#define CAN_TB_u4RXMB_CH7_INT               ( (uint32)( 0x00000001UL << ( ( 7U * 3U ) + 2U + 8U ) ) )
#define CAN_TB_u4RXMB_CH0_POL               ( (uint32)( 0x00000001UL << 0U ) )
#define CAN_TB_u4RXMB_CH1_POL               ( (uint32)( 0x00000001UL << 1U ) )
#define CAN_TB_u4RXMB_CH2_POL               ( (uint32)( 0x00000001UL << 2U ) )
#define CAN_TB_u4RXMB_CH3_POL               ( (uint32)( 0x00000001UL << 3U ) )
#define CAN_TB_u4RXMB_CH4_POL               ( (uint32)( 0x00000001UL << 4U ) )
#define CAN_TB_u4RXMB_CH5_POL               ( (uint32)( 0x00000001UL << 5U ) )
#define CAN_TB_u4RXMB_CH6_POL               ( (uint32)( 0x00000001UL << 6U ) )
#define CAN_TB_u4RXMB_CH7_POL               ( (uint32)( 0x00000001UL << 7U ) )


/*-------------------------------------------------*/
/* 受信マスク値テーブルインデックス変換            */
/*  macro  : CAN_TB_u1CONV_RXMASKREFIDX( no, id )  */
/*  param1 : no 0..127, 255                        */
/*  param2 : id 0x00000000UL..0x000007FFUL,        */
/*              0x80000000UL..0x9FFFFFFFUL         */
/*-------------------------------------------------*/
/* 標準ID/拡張ID別 受信マスク値テーブルインデックス */
#define CAN_TB_u1RXMASKREFIDX_IDTYPE( id ) \
    ( (((id) & CAN_u4BIT31) != CAN_u4BIT_NONE) ? (uint8)( CAN_CFG_FILTER_MASK_NUM + 1U ) : (uint8)CAN_CFG_FILTER_MASK_NUM )

/* 受信マスク値テーブルインデックス変換 */
#define CAN_TB_u1CONV_RXMASKREFIDX( no, id ) \
    ( ((no) == CAN_RXMASK_NOUSE) ? CAN_TB_u1RXMASKREFIDX_IDTYPE( id ) : (uint8)(no) )

/*----------------------------------------*/
/* 受信IDマスク値                         */
/*  macro  : CAN_TB_u4RXMASK_VAL( no )    */
/*  param1 : no 0..127                    */
/*----------------------------------------*/
/* マスク値の考え方                                                                                                              */
/*   コンフィグ定義は、ビットが0の場合、受信時に対応ビットを比較する。ビットが1の場合、受信時に対応ビットを比較しない。          */
/*   受信ルールマスク(GAFLM)は、ビットが0の場合、受信時に対応ビットを比較しない。ビットが1の場合、受信時に対応ビットを比較する。 */
/* よって、コンフィグ値を反転したものをレジスタ設定する。                                                                        */
#define CAN_TB_u4RXMASK_EXT( no )           ( ((~(CAN_CFG_FILTER_MASK_VALUE_##no)) & CAN_u4GAFLMJ_GAFLIDM_EXT_MSK) | CAN_u4GAFLMJ_GAFLRTRM_SET | CAN_u4GAFLMJ_GAFLIDEM_SET )

/* 標準ID用マスク値変換 */
#define CAN_TB_u4RXMASK_STD( no )           ( ((~(CAN_CFG_FILTER_MASK_VALUE_##no)) & CAN_u4GAFLMJ_GAFLIDM_STD_MSK) | CAN_u4GAFLMJ_GAFLRTRM_SET  | CAN_u4GAFLMJ_GAFLIDEM_SET )

#define CAN_TB_u4RXMASK_VAL( no ) \
    ( ((CAN_CFG_FILTER_MASK_VALUE_##no & CAN_u4BIT31) != CAN_u4BIT_NONE) ? CAN_TB_u4RXMASK_EXT( no ) : CAN_TB_u4RXMASK_STD( no ) )

/*----------------------------------------*/
/* 受信MBOXラベル設定                     */
/*  macro  : CAN_TB_u4MB_RXLABEL( mb )    */
/*  param1 : mb 0..143                    */
/*----------------------------------------*/
#define CAN_TB_u4MB_RXLABEL( mb )           ( (uint32)( ( (uint32)(mb) ) << 16U ) & 0x0FFF0000UL )


/*----------------------------------------*/
/* 受信MBOX処理方式設定                   */
/*  macro  : CAN_TB_u4MB_RXKIND( ch, mb ) */
/*  param1 : ch 0..7                      */
/*  param2 : mb 000..143                  */
/*----------------------------------------*/
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


/*-----------------------------------------*/
/* 種別毎MBOXBit位置                       */
/*  macro  : CAN_TB_u4MBBIT_LLL( ch, kind )*/
/*           CAN_TB_u4MBBIT_LLH( ch, kind )*/
/*           CAN_TB_u4MBBIT_LHL( ch, kind )*/
/*           CAN_TB_u4MBBIT_LHH( ch, kind )*/
/*           CAN_TB_u4MBBIT_HLL( ch, kind )*/
/*  param1 :ch   0..7                      */
/*  param2 :kind TX/RX/INT/POL/NO          */
/*-----------------------------------------*/
/* MBOX bit位置定義 */
#define CAN_TB_u4MBBIT000                   (0x00000001UL)          /* bit位置 MBOX000 */
#define CAN_TB_u4MBBIT001                   (0x00000002UL)          /* bit位置 MBOX001 */
#define CAN_TB_u4MBBIT002                   (0x00000004UL)          /* bit位置 MBOX002 */
#define CAN_TB_u4MBBIT003                   (0x00000008UL)          /* bit位置 MBOX003 */
#define CAN_TB_u4MBBIT004                   (0x00000010UL)          /* bit位置 MBOX004 */
#define CAN_TB_u4MBBIT005                   (0x00000020UL)          /* bit位置 MBOX005 */
#define CAN_TB_u4MBBIT006                   (0x00000040UL)          /* bit位置 MBOX006 */
#define CAN_TB_u4MBBIT007                   (0x00000080UL)          /* bit位置 MBOX007 */
#define CAN_TB_u4MBBIT008                   (0x00000100UL)          /* bit位置 MBOX008 */
#define CAN_TB_u4MBBIT009                   (0x00000200UL)          /* bit位置 MBOX009 */
#define CAN_TB_u4MBBIT010                   (0x00000400UL)          /* bit位置 MBOX010 */
#define CAN_TB_u4MBBIT011                   (0x00000800UL)          /* bit位置 MBOX011 */
#define CAN_TB_u4MBBIT012                   (0x00001000UL)          /* bit位置 MBOX012 */
#define CAN_TB_u4MBBIT013                   (0x00002000UL)          /* bit位置 MBOX013 */
#define CAN_TB_u4MBBIT014                   (0x00004000UL)          /* bit位置 MBOX014 */
#define CAN_TB_u4MBBIT015                   (0x00008000UL)          /* bit位置 MBOX015 */
#define CAN_TB_u4MBBIT016                   (0x00010000UL)          /* bit位置 MBOX016 */
#define CAN_TB_u4MBBIT017                   (0x00020000UL)          /* bit位置 MBOX017 */
#define CAN_TB_u4MBBIT018                   (0x00040000UL)          /* bit位置 MBOX018 */
#define CAN_TB_u4MBBIT019                   (0x00080000UL)          /* bit位置 MBOX019 */
#define CAN_TB_u4MBBIT020                   (0x00100000UL)          /* bit位置 MBOX020 */
#define CAN_TB_u4MBBIT021                   (0x00200000UL)          /* bit位置 MBOX021 */
#define CAN_TB_u4MBBIT022                   (0x00400000UL)          /* bit位置 MBOX022 */
#define CAN_TB_u4MBBIT023                   (0x00800000UL)          /* bit位置 MBOX023 */
#define CAN_TB_u4MBBIT024                   (0x01000000UL)          /* bit位置 MBOX024 */
#define CAN_TB_u4MBBIT025                   (0x02000000UL)          /* bit位置 MBOX025 */
#define CAN_TB_u4MBBIT026                   (0x04000000UL)          /* bit位置 MBOX026 */
#define CAN_TB_u4MBBIT027                   (0x08000000UL)          /* bit位置 MBOX027 */
#define CAN_TB_u4MBBIT028                   (0x10000000UL)          /* bit位置 MBOX028 */
#define CAN_TB_u4MBBIT029                   (0x20000000UL)          /* bit位置 MBOX029 */
#define CAN_TB_u4MBBIT030                   (0x40000000UL)          /* bit位置 MBOX030 */
#define CAN_TB_u4MBBIT031                   (0x80000000UL)          /* bit位置 MBOX031 */
#define CAN_TB_u4MBBIT032                   (0x00000001UL)          /* bit位置 MBOX032 */
#define CAN_TB_u4MBBIT033                   (0x00000002UL)          /* bit位置 MBOX033 */
#define CAN_TB_u4MBBIT034                   (0x00000004UL)          /* bit位置 MBOX034 */
#define CAN_TB_u4MBBIT035                   (0x00000008UL)          /* bit位置 MBOX035 */
#define CAN_TB_u4MBBIT036                   (0x00000010UL)          /* bit位置 MBOX036 */
#define CAN_TB_u4MBBIT037                   (0x00000020UL)          /* bit位置 MBOX037 */
#define CAN_TB_u4MBBIT038                   (0x00000040UL)          /* bit位置 MBOX038 */
#define CAN_TB_u4MBBIT039                   (0x00000080UL)          /* bit位置 MBOX039 */
#define CAN_TB_u4MBBIT040                   (0x00000100UL)          /* bit位置 MBOX040 */
#define CAN_TB_u4MBBIT041                   (0x00000200UL)          /* bit位置 MBOX041 */
#define CAN_TB_u4MBBIT042                   (0x00000400UL)          /* bit位置 MBOX042 */
#define CAN_TB_u4MBBIT043                   (0x00000800UL)          /* bit位置 MBOX043 */
#define CAN_TB_u4MBBIT044                   (0x00001000UL)          /* bit位置 MBOX044 */
#define CAN_TB_u4MBBIT045                   (0x00002000UL)          /* bit位置 MBOX045 */
#define CAN_TB_u4MBBIT046                   (0x00004000UL)          /* bit位置 MBOX046 */
#define CAN_TB_u4MBBIT047                   (0x00008000UL)          /* bit位置 MBOX047 */
#define CAN_TB_u4MBBIT048                   (0x00010000UL)          /* bit位置 MBOX048 */
#define CAN_TB_u4MBBIT049                   (0x00020000UL)          /* bit位置 MBOX049 */
#define CAN_TB_u4MBBIT050                   (0x00040000UL)          /* bit位置 MBOX050 */
#define CAN_TB_u4MBBIT051                   (0x00080000UL)          /* bit位置 MBOX051 */
#define CAN_TB_u4MBBIT052                   (0x00100000UL)          /* bit位置 MBOX052 */
#define CAN_TB_u4MBBIT053                   (0x00200000UL)          /* bit位置 MBOX053 */
#define CAN_TB_u4MBBIT054                   (0x00400000UL)          /* bit位置 MBOX054 */
#define CAN_TB_u4MBBIT055                   (0x00800000UL)          /* bit位置 MBOX055 */
#define CAN_TB_u4MBBIT056                   (0x01000000UL)          /* bit位置 MBOX056 */
#define CAN_TB_u4MBBIT057                   (0x02000000UL)          /* bit位置 MBOX057 */
#define CAN_TB_u4MBBIT058                   (0x04000000UL)          /* bit位置 MBOX058 */
#define CAN_TB_u4MBBIT059                   (0x08000000UL)          /* bit位置 MBOX059 */
#define CAN_TB_u4MBBIT060                   (0x10000000UL)          /* bit位置 MBOX060 */
#define CAN_TB_u4MBBIT061                   (0x20000000UL)          /* bit位置 MBOX061 */
#define CAN_TB_u4MBBIT062                   (0x40000000UL)          /* bit位置 MBOX062 */
#define CAN_TB_u4MBBIT063                   (0x80000000UL)          /* bit位置 MBOX063 */
#define CAN_TB_u4MBBIT064                   (0x00000001UL)          /* bit位置 MBOX064 */
#define CAN_TB_u4MBBIT065                   (0x00000002UL)          /* bit位置 MBOX065 */
#define CAN_TB_u4MBBIT066                   (0x00000004UL)          /* bit位置 MBOX066 */
#define CAN_TB_u4MBBIT067                   (0x00000008UL)          /* bit位置 MBOX067 */
#define CAN_TB_u4MBBIT068                   (0x00000010UL)          /* bit位置 MBOX068 */
#define CAN_TB_u4MBBIT069                   (0x00000020UL)          /* bit位置 MBOX069 */
#define CAN_TB_u4MBBIT070                   (0x00000040UL)          /* bit位置 MBOX070 */
#define CAN_TB_u4MBBIT071                   (0x00000080UL)          /* bit位置 MBOX071 */
#define CAN_TB_u4MBBIT072                   (0x00000100UL)          /* bit位置 MBOX072 */
#define CAN_TB_u4MBBIT073                   (0x00000200UL)          /* bit位置 MBOX073 */
#define CAN_TB_u4MBBIT074                   (0x00000400UL)          /* bit位置 MBOX074 */
#define CAN_TB_u4MBBIT075                   (0x00000800UL)          /* bit位置 MBOX075 */
#define CAN_TB_u4MBBIT076                   (0x00001000UL)          /* bit位置 MBOX076 */
#define CAN_TB_u4MBBIT077                   (0x00002000UL)          /* bit位置 MBOX077 */
#define CAN_TB_u4MBBIT078                   (0x00004000UL)          /* bit位置 MBOX078 */
#define CAN_TB_u4MBBIT079                   (0x00008000UL)          /* bit位置 MBOX079 */
#define CAN_TB_u4MBBIT080                   (0x00010000UL)          /* bit位置 MBOX080 */
#define CAN_TB_u4MBBIT081                   (0x00020000UL)          /* bit位置 MBOX081 */
#define CAN_TB_u4MBBIT082                   (0x00040000UL)          /* bit位置 MBOX082 */
#define CAN_TB_u4MBBIT083                   (0x00080000UL)          /* bit位置 MBOX083 */
#define CAN_TB_u4MBBIT084                   (0x00100000UL)          /* bit位置 MBOX084 */
#define CAN_TB_u4MBBIT085                   (0x00200000UL)          /* bit位置 MBOX085 */
#define CAN_TB_u4MBBIT086                   (0x00400000UL)          /* bit位置 MBOX086 */
#define CAN_TB_u4MBBIT087                   (0x00800000UL)          /* bit位置 MBOX087 */
#define CAN_TB_u4MBBIT088                   (0x01000000UL)          /* bit位置 MBOX088 */
#define CAN_TB_u4MBBIT089                   (0x02000000UL)          /* bit位置 MBOX089 */
#define CAN_TB_u4MBBIT090                   (0x04000000UL)          /* bit位置 MBOX090 */
#define CAN_TB_u4MBBIT091                   (0x08000000UL)          /* bit位置 MBOX091 */
#define CAN_TB_u4MBBIT092                   (0x10000000UL)          /* bit位置 MBOX092 */
#define CAN_TB_u4MBBIT093                   (0x20000000UL)          /* bit位置 MBOX093 */
#define CAN_TB_u4MBBIT094                   (0x40000000UL)          /* bit位置 MBOX094 */
#define CAN_TB_u4MBBIT095                   (0x80000000UL)          /* bit位置 MBOX095 */
#define CAN_TB_u4MBBIT096                   (0x00000001UL)          /* bit位置 MBOX096 */
#define CAN_TB_u4MBBIT097                   (0x00000002UL)          /* bit位置 MBOX097 */
#define CAN_TB_u4MBBIT098                   (0x00000004UL)          /* bit位置 MBOX098 */
#define CAN_TB_u4MBBIT099                   (0x00000008UL)          /* bit位置 MBOX099 */
#define CAN_TB_u4MBBIT100                   (0x00000010UL)          /* bit位置 MBOX100 */
#define CAN_TB_u4MBBIT101                   (0x00000020UL)          /* bit位置 MBOX101 */
#define CAN_TB_u4MBBIT102                   (0x00000040UL)          /* bit位置 MBOX102 */
#define CAN_TB_u4MBBIT103                   (0x00000080UL)          /* bit位置 MBOX103 */
#define CAN_TB_u4MBBIT104                   (0x00000100UL)          /* bit位置 MBOX104 */
#define CAN_TB_u4MBBIT105                   (0x00000200UL)          /* bit位置 MBOX105 */
#define CAN_TB_u4MBBIT106                   (0x00000400UL)          /* bit位置 MBOX106 */
#define CAN_TB_u4MBBIT107                   (0x00000800UL)          /* bit位置 MBOX107 */
#define CAN_TB_u4MBBIT108                   (0x00001000UL)          /* bit位置 MBOX108 */
#define CAN_TB_u4MBBIT109                   (0x00002000UL)          /* bit位置 MBOX109 */
#define CAN_TB_u4MBBIT110                   (0x00004000UL)          /* bit位置 MBOX110 */
#define CAN_TB_u4MBBIT111                   (0x00008000UL)          /* bit位置 MBOX111 */
#define CAN_TB_u4MBBIT112                   (0x00010000UL)          /* bit位置 MBOX112 */
#define CAN_TB_u4MBBIT113                   (0x00020000UL)          /* bit位置 MBOX113 */
#define CAN_TB_u4MBBIT114                   (0x00040000UL)          /* bit位置 MBOX114 */
#define CAN_TB_u4MBBIT115                   (0x00080000UL)          /* bit位置 MBOX115 */
#define CAN_TB_u4MBBIT116                   (0x00100000UL)          /* bit位置 MBOX116 */
#define CAN_TB_u4MBBIT117                   (0x00200000UL)          /* bit位置 MBOX117 */
#define CAN_TB_u4MBBIT118                   (0x00400000UL)          /* bit位置 MBOX118 */
#define CAN_TB_u4MBBIT119                   (0x00800000UL)          /* bit位置 MBOX119 */
#define CAN_TB_u4MBBIT120                   (0x01000000UL)          /* bit位置 MBOX120 */
#define CAN_TB_u4MBBIT121                   (0x02000000UL)          /* bit位置 MBOX121 */
#define CAN_TB_u4MBBIT122                   (0x04000000UL)          /* bit位置 MBOX122 */
#define CAN_TB_u4MBBIT123                   (0x08000000UL)          /* bit位置 MBOX123 */
#define CAN_TB_u4MBBIT124                   (0x10000000UL)          /* bit位置 MBOX124 */
#define CAN_TB_u4MBBIT125                   (0x20000000UL)          /* bit位置 MBOX125 */
#define CAN_TB_u4MBBIT126                   (0x40000000UL)          /* bit位置 MBOX126 */
#define CAN_TB_u4MBBIT127                   (0x80000000UL)          /* bit位置 MBOX127 */
#define CAN_TB_u4MBBIT128                   (0x00000001UL)          /* bit位置 MBOX128 */
#define CAN_TB_u4MBBIT129                   (0x00000002UL)          /* bit位置 MBOX129 */
#define CAN_TB_u4MBBIT130                   (0x00000004UL)          /* bit位置 MBOX130 */
#define CAN_TB_u4MBBIT131                   (0x00000008UL)          /* bit位置 MBOX131 */
#define CAN_TB_u4MBBIT132                   (0x00000010UL)          /* bit位置 MBOX132 */
#define CAN_TB_u4MBBIT133                   (0x00000020UL)          /* bit位置 MBOX133 */
#define CAN_TB_u4MBBIT134                   (0x00000040UL)          /* bit位置 MBOX134 */
#define CAN_TB_u4MBBIT135                   (0x00000080UL)          /* bit位置 MBOX135 */
#define CAN_TB_u4MBBIT136                   (0x00000100UL)          /* bit位置 MBOX136 */
#define CAN_TB_u4MBBIT137                   (0x00000200UL)          /* bit位置 MBOX137 */
#define CAN_TB_u4MBBIT138                   (0x00000400UL)          /* bit位置 MBOX138 */
#define CAN_TB_u4MBBIT139                   (0x00000800UL)          /* bit位置 MBOX139 */
#define CAN_TB_u4MBBIT140                   (0x00001000UL)          /* bit位置 MBOX140 */
#define CAN_TB_u4MBBIT141                   (0x00002000UL)          /* bit位置 MBOX141 */
#define CAN_TB_u4MBBIT142                   (0x00004000UL)          /* bit位置 MBOX142 */
#define CAN_TB_u4MBBIT143                   (0x00008000UL)          /* bit位置 MBOX143 */
#define CAN_TB_u4MBBIT( mb )                ( CAN_TB_u4MBBIT##mb )

#define CAN_TB_u4MBBIT_TX( ch, mb )         ( ((CAN_TB_MBSET( ch, mb ) & CAN_MB_TRANSMIT)  != CAN_MB_NOUSE) ? (CAN_TB_u4MBBIT( mb )) : CAN_u4BIT_NONE )
#define CAN_TB_u4MBBIT_RX( ch, mb )         ( ((CAN_TB_MBSET( ch, mb ) & CAN_MB_RECEPTION) != CAN_MB_NOUSE) ? (CAN_TB_u4MBBIT( mb )) : CAN_u4BIT_NONE )
#define CAN_TB_u4MBBIT_INT( ch, mb )        ( ((CAN_TB_MBSET( ch, mb ) & CAN_MB_INTERRUPT) != CAN_MB_NOUSE) ? (CAN_TB_u4MBBIT( mb )) : CAN_u4BIT_NONE )
#define CAN_TB_u4MBBIT_POL( ch, mb )        ( ((CAN_TB_MBSET( ch, mb ) & CAN_MB_POLLING)   != CAN_MB_NOUSE) ? (CAN_TB_u4MBBIT( mb )) : CAN_u4BIT_NONE )
#define CAN_TB_u4MBBIT_MB( ch, kind, mb )   ( CAN_TB_u4MBBIT_##kind( ch, mb ) )

/* MBOX000-031 */
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

/* MBOX032-063 */
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

/* MBOX064-095 */
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

/* MBOX096-127 */
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

/* MBOX128-143 */
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
#define CAN_TB_u4MBBIT_HLL( ch, kind ) \
   (  CAN_TB_u4MBBIT_HLL0( ch, kind ) | CAN_TB_u4MBBIT_HLL1( ch, kind ) )


/*----------------------------------------*/
/* ポーリング受信MBOX有無                 */
/*  macro  : CAN_TB_RXPOLLING( ch )       */
/*  param1 : ch 0..7                      */
/*----------------------------------------*/
#define CAN_TB_RXPOLLING( ch ) \
 (((( CAN_TB_u4MBBIT_LLL( ch, RX ) & CAN_TB_u4MBBIT_LLL( ch, POL ) ) != CAN_u4BIT_NONE ) \
 ||(( CAN_TB_u4MBBIT_LLH( ch, RX ) & CAN_TB_u4MBBIT_LLH( ch, POL ) ) != CAN_u4BIT_NONE ) \
 ||(( CAN_TB_u4MBBIT_LHL( ch, RX ) & CAN_TB_u4MBBIT_LHL( ch, POL ) ) != CAN_u4BIT_NONE ) \
 ||(( CAN_TB_u4MBBIT_LHH( ch, RX ) & CAN_TB_u4MBBIT_LHH( ch, POL ) ) != CAN_u4BIT_NONE ) \
 ||(( CAN_TB_u4MBBIT_HLL( ch, RX ) & CAN_TB_u4MBBIT_HLL( ch, POL ) ) != CAN_u4BIT_NONE )) ? CAN_USE : CAN_NOUSE )


/*----------------------------------------*/
/* 種別毎送信MBOXBit位置                  */
/*  macro  : CAN_TB_u2TXMBBIT( ch, kind ) */
/*  param1 :ch   0..7                     */
/*  param2 :kind INT/POL                  */
/*----------------------------------------*/
/* 送信MBOXは0から15しか指定されないため        */
/* CAN_TB_u4MBBIT_LLLのみを参照する             */
/* また、uint16にキャストしても情報は欠落しない */
#define CAN_TB_u2TXMBBIT( ch, kind )   ( (uint16)( CAN_TB_u4MBBIT_LLL( ch, TX ) & CAN_TB_u4MBBIT_LLL( ch, kind ) ) )


/*======================================*/
/* ボーレート設定テーブル設定定義       */
/*======================================*/
/*----------------------------------------------------*/
/* クラシカルCANモード：CmCFG レジスタ設定値 (Config) */
/* CAN FDモード       ：CmNCFGレジスタ設定値 (Config) */
/*  macro  : CAN_TB_u4CmCFG_CONF( ch )                */
/*  param1 : ch 0..7                                  */
/*----------------------------------------------------*/
#if (CAN_OPEMODE == CAN_OPEMODE_CAN)
#define CAN_TB_u4CmCFG_BTPTN_USERMASK       ( 0x037F03FFUL )                       /* ユーザ用設定値                        */
#else /* (CAN_OPEMODE != CAN_OPEMODE_CAN) */
#define CAN_TB_u4CmCFG_BTPTN_USERMASK       ( 0x1F7FFBFFUL )                       /* ユーザ用設定値                        */
#endif /* (CAN_OPEMODE) */

#define CAN_TB_u4CmCFG_UBTPTN( ch )         ( CAN_CFG_USER_BAUDRATE_##ch & CAN_TB_u4CmCFG_BTPTN_USERMASK )
#define CAN_TB_BAUDRATE( ch )               ( CAN_CFG_CONTROLLER_BAUDRATE_##ch )

/* クラシカルCANモード：CmCFG レジスタ設定値 (Config) */
/* CAN FDモード       ：CmNCFGレジスタ設定値 (Config) */
#define CAN_TB_u4CmCFG_CONF( ch ) \
    ( (CAN_TB_BAUDRATE( ch ) == CAN_TB_USER_BAUDRATE) ? CAN_TB_u4CmCFG_UBTPTN( ch ) : CAN_TB_BAUDRATE( ch ) )


#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
/*-------------------------------------------*/
/* CmDCFGレジスタ設定値 (Config)             */
/*  macro  : CAN_TB_u4CmDCFG_CONF( ch )      */
/*  param1 : ch 0..7                         */
/*-------------------------------------------*/
#define CAN_TB_u4CmDCFG_BTPTN_USERMASK      ( 0x077F00FFUL )                       /* ユーザ用設定値                        */
#define CAN_TB_u4CmDCFG_UBTPTN( ch )        ( CAN_CFG_USER_DBAUDRATE_##ch & CAN_TB_u4CmDCFG_BTPTN_USERMASK )
#define CAN_TB_DATABAUDRATE( ch )           ( CAN_CFG_CONTROLLER_DBAUDRATE_##ch )

/* CmDCFGレジスタ設定値 (Config) */
#define CAN_TB_u4CmDCFG_CONF( ch ) \
    ( (CAN_TB_DATABAUDRATE( ch ) == CAN_TB_USER_DATABAUDRATE) ? CAN_TB_u4CmDCFG_UBTPTN( ch ) : CAN_TB_DATABAUDRATE( ch ) )

#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */


/*----------------------------------------*/
/* CMCTRレジスタ設定値 (Config)           */
/*  macro  : CAN_TB_u4CMCTR_CONF( ch )    */
/*  param1 : ch 0..7                      */
/*----------------------------------------*/
/* [bit23]    ERRD エラー表示モード選択ビット               */
/*   1: 発生した全てのエラー情報のエラーフラグを表示        */
#define CAN_TB_u4CMCTR_BASE                 ( 0x00800000UL )

/* [bit22-21] BOM  バスオフ復帰モード選択ビット(コンフィグ) */
/*   00: ISO11898-1準拠(自動復帰用)                         */
/*   01: バスオフ開始でチャネル待機モード遷移(自動復帰用)   */
#define CAN_TB_u4CMCTR_BOM_AUTO             ( 0x00000000UL )
#define CAN_TB_u4CMCTR_BOM_MANUAL           ( 0x00200000UL )

/* CmCTR.BOM設定値 */
#define CAN_TB_u4CMCTR_BOM_CONF( ch ) \
    ( (CAN_CFG_BUSOFF_RECOVERY_##ch == CAN_MANUAL) ? CAN_TB_u4CMCTR_BOM_MANUAL : CAN_TB_u4CMCTR_BOM_AUTO )

/* CmCTRレジスタ設定値 */
#define CAN_TB_u4CMCTR_CONF( ch )           ( CAN_TB_u4CMCTR_BASE | CAN_TB_u4CMCTR_BOM_CONF( ch ) )


/*----------------------------------------*/
/* CmFDCFGレジスタ設定値 (Config)         */
/*  macro  : CAN_TB_u4CMFDCFG_CONF( ch )  */
/*  param1 : ch 0..7                      */
/*----------------------------------------*/
/* [bit29]    REFE 受信データエッジフィルタ許可ビット       */
/*   0: 受信データエッジフィルタ禁止                        */
/*   1: 受信データエッジフィルタ許可                        */
#define CAN_TB_u4CMFDCFG_REFE_DIS           ( 0x00000000UL )
#define CAN_TB_u4CMFDCFG_REFE_ENA           ( 0x20000000UL )

#define CAN_TB_u4CMFDCFG_REFE_CONF( ch ) \
    ( (CAN_CFG_EDGE_FILTERING_##ch == CAN_USE) ? CAN_TB_u4CMFDCFG_REFE_ENA : CAN_TB_u4CMFDCFG_REFE_DIS )

/* [bit27]    TMME 送信バッファマージモード許可ビット       */
/*   1: 送信バッファマージモード許可                        */
#define CAN_TB_u4CMFDCFG_TMME_ENA           ( 0x08000000UL )

/* [bit22-16] TDCO 送信遅延オフセット設定ビット(コンフィグ) */
/*   データボーレートのサンプリングポイントをfCANクロック時間で設定する                 */
/*   サンプリングポイント = ( SS + TSEG1 )[Tq] * データビットレート プリスケーラ分周比  */
/*                        = ( 1 + ( CmDCFG.DTSEG1設定値+1 ) ) * ( CmDCFG.DBRP設定値+1 ) */
/*   CmFDCFG.TDCO設定値   = サンプリングポイント - 1                                    */
#define CAN_TB_u4CMFDCFG_DBRP( ch )         ( (uint32)( ( CAN_TB_u4CmDCFG_CONF( ch ) & CAN_TB_u4CmDCFG_BIT_DBRP   ) >> CAN_TB_CmDCFG_SFT_DBRP   ) )
#define CAN_TB_u4CMFDCFG_DTSEG1( ch )       ( (uint32)( ( CAN_TB_u4CmDCFG_CONF( ch ) & CAN_TB_u4CmDCFG_BIT_DTSEG1 ) >> CAN_TB_CmDCFG_SFT_DTSEG1 ) )
#define CAN_TB_u4CMFDCFG_TDCO_VAL( ch )     ( (uint32)( ( (uint32)( 1UL + ( CAN_TB_u4CMFDCFG_DTSEG1( ch ) + 1UL ) ) * ( CAN_TB_u4CMFDCFG_DBRP( ch ) + 1UL ) ) - 1UL ) )

#define CAN_TB_u4CMFDCFG_TDCO( ch )         ( (uint32)( CAN_TB_u4CMFDCFG_TDCO_VAL( ch ) << CAN_TB_CMFDCFG_SFT_TDCO ) & CAN_u4CMFDCFG_TDCO_MSK )

#define CAN_TB_u4CMFDCFG_TDCO_CONF( ch ) \
    ( (CAN_CFG_DBAUDRATE_SWT_##ch == CAN_USE) ? CAN_TB_u4CMFDCFG_TDCO( ch ) : 0x00000000UL )

/* [bit10]    ESIC エラーステート表示モード選択ビット(コンフィグ) */
/*   0: 常にチャネルのエラーステートをフレームのESIビット   */
/*      として送信                                          */
/*   1: チャネルがエラーパッシブ以外の場合は                */
/*      メッセージバッファのエラーステートをESIビットとして送信 */
#define CAN_TB_u4CMFDCFG_ESIC_ALWAYS        ( 0x00000000UL )
#define CAN_TB_u4CMFDCFG_ESIC_MB            ( 0x00000400UL )

#define CAN_TB_u4CMFDCFG_ESIC_CONF( ch ) \
    ( (CAN_CFG_ESI_##ch == CAN_USE) ? CAN_TB_u4CMFDCFG_ESIC_ALWAYS : CAN_TB_u4CMFDCFG_ESIC_MB )

/* [bit9]     TDCE 送信遅延補正許可ビット                   */
/*   0: 送信遅延補正禁止                                    */
/*   1: 送信遅延補正許可                                    */
#define CAN_TB_u4CMFDCFG_TDCE_DIS           ( 0x00000000UL )
#define CAN_TB_u4CMFDCFG_TDCE_ENA           ( 0x00000200UL )

#define CAN_TB_u4CMFDCFG_TDCE_CONF( ch ) \
    ( (CAN_CFG_DBAUDRATE_SWT_##ch == CAN_USE) ? CAN_TB_u4CMFDCFG_TDCE_ENA : CAN_TB_u4CMFDCFG_TDCE_DIS )

/* [bit8]     TDCOC 送信遅延補正計測選択ビット              */
/*   0: 計測およびオフセット                                */
#define CAN_TB_u4CMFDCFG_TDCOC_MEASURE      ( 0x00000000UL )

/* CmFDCFGレジスタ設定値 */
#define CAN_TB_u4CMFDCFG_CONF( ch ) \
    ( CAN_TB_u4CMFDCFG_REFE_CONF( ch ) | CAN_TB_u4CMFDCFG_TMME_ENA        | CAN_TB_u4CMFDCFG_TDCO_CONF( ch ) \
    | CAN_TB_u4CMFDCFG_ESIC_CONF( ch ) | CAN_TB_u4CMFDCFG_TDCE_CONF( ch ) | CAN_TB_u4CMFDCFG_TDCOC_MEASURE )


/*----------------------------------------*/
/* CFCCkレジスタ設定値 (Config)           */
/*  macro  : CAN_TB_u4CFCC0_CONF( ch )    */
/*           CAN_TB_u4CFCC1_CONF( ch )    */
/*           CAN_TB_u4CFCC2_CONF( ch )    */
/*  param1 : ch 0..7                      */
/*----------------------------------------*/
/* CFTML(送信バッファリンク設定) */
#define CAN_TB_u4CFCCk_SFT_CFTML            ( 20U )
#define CAN_TB_u4CFCCk_BIT_CFTML            ( 0x00F00000UL )

#define CAN_TB_u4CFCCk_CFTML_TX0( ch )      ( ( (uint32)( (uint32)CAN_CFG_TX_FIFO_0_LINK_##ch << CAN_TB_u4CFCCk_SFT_CFTML) ) & CAN_TB_u4CFCCk_BIT_CFTML )
#define CAN_TB_u4CFCCk_CFTML_TX1( ch )      ( ( (uint32)( (uint32)CAN_CFG_TX_FIFO_1_LINK_##ch << CAN_TB_u4CFCCk_SFT_CFTML) ) & CAN_TB_u4CFCCk_BIT_CFTML )


/* CFM(送受信FIFOモード) */
#define CAN_TB_u4CFCCk_CFM_RX               ( 0x00000000UL )              /* 受信モード                                           */
#define CAN_TB_u4CFCCk_CFM_TX               ( 0x00010000UL )              /* 送信モード                                           */

/* CFIM(送受信FIFO割込み要因) */
#define CAN_TB_u4CFCCk_CFIM_CFIGCV          ( 0x00000000UL )              /* 受信モード：                                         */
                                                                          /*   CFICGVに指定したタイミングで割り込み               */
                                                                          /* 送信モード：                                         */
                                                                          /*   送信完了にてバッファが空になったとき割り込み       */
                                                                          /* (リセット初期値)                                     */
#define CAN_TB_u4CFCCk_CFIM_ON_1MSG         ( 0x00001000UL )              /* 1メッセージ送受信する毎に割り込み                    */

#define CAN_TB_u4TX_FIFO_0_MBBIT_INT( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_LINK_##ch == 6U )  ? CAN_TB_u4MBBIT_INT( ch, 006 ) : CAN_TB_u4TX_FIFO_0_MBBIT_INT_1( ch ) )
#define CAN_TB_u4TX_FIFO_0_MBBIT_INT_1( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_LINK_##ch == 7U )  ? CAN_TB_u4MBBIT_INT( ch, 007 ) : CAN_TB_u4TX_FIFO_0_MBBIT_INT_2( ch ) )
#define CAN_TB_u4TX_FIFO_0_MBBIT_INT_2( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_LINK_##ch == 8U )  ? CAN_TB_u4MBBIT_INT( ch, 008 ) : CAN_TB_u4TX_FIFO_0_MBBIT_INT_3( ch ) )
#define CAN_TB_u4TX_FIFO_0_MBBIT_INT_3( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_LINK_##ch == 9U )  ? CAN_TB_u4MBBIT_INT( ch, 009 ) : CAN_TB_u4TX_FIFO_0_MBBIT_INT_4( ch ) )
#define CAN_TB_u4TX_FIFO_0_MBBIT_INT_4( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_LINK_##ch == 10U ) ? CAN_TB_u4MBBIT_INT( ch, 010 ) : CAN_TB_u4TX_FIFO_0_MBBIT_INT_5( ch ) )
#define CAN_TB_u4TX_FIFO_0_MBBIT_INT_5( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_LINK_##ch == 11U ) ? CAN_TB_u4MBBIT_INT( ch, 011 ) : CAN_TB_u4TX_FIFO_0_MBBIT_INT_6( ch ) )
#define CAN_TB_u4TX_FIFO_0_MBBIT_INT_6( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_LINK_##ch == 12U ) ? CAN_TB_u4MBBIT_INT( ch, 012 ) : CAN_TB_u4TX_FIFO_0_MBBIT_INT_7( ch ) )
#define CAN_TB_u4TX_FIFO_0_MBBIT_INT_7( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_LINK_##ch == 13U ) ? CAN_TB_u4MBBIT_INT( ch, 013 ) : CAN_TB_u4TX_FIFO_0_MBBIT_INT_8( ch ) )
#define CAN_TB_u4TX_FIFO_0_MBBIT_INT_8( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_LINK_##ch == 14U ) ? CAN_TB_u4MBBIT_INT( ch, 014 ) : CAN_TB_u4TX_FIFO_0_MBBIT_INT_9( ch ) )
#define CAN_TB_u4TX_FIFO_0_MBBIT_INT_9( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_LINK_##ch == 15U ) ? CAN_TB_u4MBBIT_INT( ch, 015 ) : CAN_u4BIT_NONE )

#define CAN_TB_u4TX_FIFO_1_MBBIT_INT( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_LINK_##ch == 6U )  ? CAN_TB_u4MBBIT_INT( ch, 006 ) : CAN_TB_u4TX_FIFO_1_MBBIT_INT_1( ch ) )
#define CAN_TB_u4TX_FIFO_1_MBBIT_INT_1( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_LINK_##ch == 7U )  ? CAN_TB_u4MBBIT_INT( ch, 007 ) : CAN_TB_u4TX_FIFO_1_MBBIT_INT_2( ch ) )
#define CAN_TB_u4TX_FIFO_1_MBBIT_INT_2( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_LINK_##ch == 8U )  ? CAN_TB_u4MBBIT_INT( ch, 008 ) : CAN_TB_u4TX_FIFO_1_MBBIT_INT_3( ch ) )
#define CAN_TB_u4TX_FIFO_1_MBBIT_INT_3( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_LINK_##ch == 9U )  ? CAN_TB_u4MBBIT_INT( ch, 009 ) : CAN_TB_u4TX_FIFO_1_MBBIT_INT_4( ch ) )
#define CAN_TB_u4TX_FIFO_1_MBBIT_INT_4( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_LINK_##ch == 10U ) ? CAN_TB_u4MBBIT_INT( ch, 010 ) : CAN_TB_u4TX_FIFO_1_MBBIT_INT_5( ch ) )
#define CAN_TB_u4TX_FIFO_1_MBBIT_INT_5( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_LINK_##ch == 11U ) ? CAN_TB_u4MBBIT_INT( ch, 011 ) : CAN_TB_u4TX_FIFO_1_MBBIT_INT_6( ch ) )
#define CAN_TB_u4TX_FIFO_1_MBBIT_INT_6( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_LINK_##ch == 12U ) ? CAN_TB_u4MBBIT_INT( ch, 012 ) : CAN_TB_u4TX_FIFO_1_MBBIT_INT_7( ch ) )
#define CAN_TB_u4TX_FIFO_1_MBBIT_INT_7( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_LINK_##ch == 13U ) ? CAN_TB_u4MBBIT_INT( ch, 013 ) : CAN_TB_u4TX_FIFO_1_MBBIT_INT_8( ch ) )
#define CAN_TB_u4TX_FIFO_1_MBBIT_INT_8( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_LINK_##ch == 14U ) ? CAN_TB_u4MBBIT_INT( ch, 014 ) : CAN_TB_u4TX_FIFO_1_MBBIT_INT_9( ch ) )
#define CAN_TB_u4TX_FIFO_1_MBBIT_INT_9( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_LINK_##ch == 15U ) ? CAN_TB_u4MBBIT_INT( ch, 015 ) : CAN_u4BIT_NONE )

#define CAN_TB_u4CFCCk_CFIM_TX0( ch )       ( ( CAN_TB_u4TX_FIFO_0_MBBIT_INT( ch ) != CAN_u4BIT_NONE ) ? CAN_TB_u4CFCCk_CFIM_ON_1MSG : CAN_TB_u4CFCCk_CFIM_CFIGCV )
#define CAN_TB_u4CFCCk_CFIM_TX1( ch )       ( ( CAN_TB_u4TX_FIFO_1_MBBIT_INT( ch ) != CAN_u4BIT_NONE ) ? CAN_TB_u4CFCCk_CFIM_ON_1MSG : CAN_TB_u4CFCCk_CFIM_CFIGCV )

/* CFDC(送受信FIFO段数) */
#define CAN_TB_u4CFCCk_CFDC_0               ( 0x00000000UL )              /* 送受信FIFO 0段(未使用)設定値                         */
#define CAN_TB_u4CFCCk_CFDC_4               ( 0x00000100UL )              /* 送受信FIFO 4段設定値                                 */
#define CAN_TB_u4CFCCk_CFDC_8               ( 0x00000200UL )              /* 送受信FIFO 8段設定値                                 */
#define CAN_TB_u4CFCCk_CFDC_16              ( 0x00000300UL )              /* 送受信FIFO 16段設定値                                */
#define CAN_TB_u4CFCCk_CFDC_32              ( 0x00000400UL )              /* 送受信FIFO 32段設定値                                */
#define CAN_TB_u4CFCCk_CFDC_48              ( 0x00000500UL )              /* 送受信FIFO 48段設定値                                */
#define CAN_TB_u4CFCCk_CFDC_64              ( 0x00000600UL )              /* 送受信FIFO 64段設定値                                */
#define CAN_TB_u4CFCCk_CFDC_128             ( 0x00000700UL )              /* 送受信FIFO 128段設定値                               */

#define CAN_TB_u4CFCCk_CFDC_TX0             ( CAN_TB_u4CFCCk_CFDC_4 )     /* 送信用FIFO0段数設定値(4段固定)                       */
#define CAN_TB_u4CFCCk_CFDC_TX1             ( CAN_TB_u4CFCCk_CFDC_4 )     /* 送信用FIFO1段数設定値(4段固定)                       */
#define CAN_TB_u4CFCCk_CFDC_RXINT           ( CAN_TB_u4CFCCk_CFDC_4 )     /* 割り込み受信用FIFO段数設定値(4段固定)                */

/* CFPLS(送受信FIFOベイロード格納サイズ) */
#define CAN_TB_u4CFCCk_CFPLS_8              ( 0x00000000UL )              /* 送受信FIFO 8バイト設定値                             */
#define CAN_TB_u4CFCCk_CFPLS_12             ( 0x00000010UL )              /* 送受信FIFO 12バイト設定値                            */
#define CAN_TB_u4CFCCk_CFPLS_16             ( 0x00000020UL )              /* 送受信FIFO 16バイト設定値                            */
#define CAN_TB_u4CFCCk_CFPLS_20             ( 0x00000030UL )              /* 送受信FIFO 20バイト設定値                            */
#define CAN_TB_u4CFCCk_CFPLS_24             ( 0x00000040UL )              /* 送受信FIFO 24バイト設定値                            */
#define CAN_TB_u4CFCCk_CFPLS_32             ( 0x00000050UL )              /* 送受信FIFO 32バイト設定値                            */
#define CAN_TB_u4CFCCk_CFPLS_48             ( 0x00000060UL )              /* 送受信FIFO 48バイト設定値                            */
#define CAN_TB_u4CFCCk_CFPLS_64             ( 0x00000070UL )              /* 送受信FIFO 64バイト設定値                            */

#define CAN_TB_TX_FIFO_0_PAYLOAD( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_PAYLOAD_##ch == 8U )  ? CAN_TB_u4CFCCk_CFPLS_8  : CAN_TB_TX_FIFO_0_PAYLOAD_1( ch ) )
#define CAN_TB_TX_FIFO_0_PAYLOAD_1( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_PAYLOAD_##ch == 12U ) ? CAN_TB_u4CFCCk_CFPLS_12 : CAN_TB_TX_FIFO_0_PAYLOAD_2( ch ) )
#define CAN_TB_TX_FIFO_0_PAYLOAD_2( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_PAYLOAD_##ch == 16U ) ? CAN_TB_u4CFCCk_CFPLS_16 : CAN_TB_TX_FIFO_0_PAYLOAD_3( ch ) )
#define CAN_TB_TX_FIFO_0_PAYLOAD_3( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_PAYLOAD_##ch == 20U ) ? CAN_TB_u4CFCCk_CFPLS_20 : CAN_TB_TX_FIFO_0_PAYLOAD_4( ch ) )
#define CAN_TB_TX_FIFO_0_PAYLOAD_4( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_PAYLOAD_##ch == 24U ) ? CAN_TB_u4CFCCk_CFPLS_24 : CAN_TB_TX_FIFO_0_PAYLOAD_5( ch ) )
#define CAN_TB_TX_FIFO_0_PAYLOAD_5( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_PAYLOAD_##ch == 32U ) ? CAN_TB_u4CFCCk_CFPLS_32 : CAN_TB_TX_FIFO_0_PAYLOAD_6( ch ) )
#define CAN_TB_TX_FIFO_0_PAYLOAD_6( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_PAYLOAD_##ch == 48U ) ? CAN_TB_u4CFCCk_CFPLS_48 : CAN_TB_TX_FIFO_0_PAYLOAD_7( ch ) )
#define CAN_TB_TX_FIFO_0_PAYLOAD_7( ch ) \
    ( ( CAN_CFG_TX_FIFO_0_PAYLOAD_##ch == 64U ) ? CAN_TB_u4CFCCk_CFPLS_64 : CAN_TB_u4CFCCk_CFPLS_8 )

#define CAN_TB_TX_FIFO_1_PAYLOAD( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_PAYLOAD_##ch == 8U )  ? CAN_TB_u4CFCCk_CFPLS_8  : CAN_TB_TX_FIFO_1_PAYLOAD_1( ch ) )
#define CAN_TB_TX_FIFO_1_PAYLOAD_1( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_PAYLOAD_##ch == 12U ) ? CAN_TB_u4CFCCk_CFPLS_12 : CAN_TB_TX_FIFO_1_PAYLOAD_2( ch ) )
#define CAN_TB_TX_FIFO_1_PAYLOAD_2( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_PAYLOAD_##ch == 16U ) ? CAN_TB_u4CFCCk_CFPLS_16 : CAN_TB_TX_FIFO_1_PAYLOAD_3( ch ) )
#define CAN_TB_TX_FIFO_1_PAYLOAD_3( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_PAYLOAD_##ch == 20U ) ? CAN_TB_u4CFCCk_CFPLS_20 : CAN_TB_TX_FIFO_1_PAYLOAD_4( ch ) )
#define CAN_TB_TX_FIFO_1_PAYLOAD_4( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_PAYLOAD_##ch == 24U ) ? CAN_TB_u4CFCCk_CFPLS_24 : CAN_TB_TX_FIFO_1_PAYLOAD_5( ch ) )
#define CAN_TB_TX_FIFO_1_PAYLOAD_5( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_PAYLOAD_##ch == 32U ) ? CAN_TB_u4CFCCk_CFPLS_32 : CAN_TB_TX_FIFO_1_PAYLOAD_6( ch ) )
#define CAN_TB_TX_FIFO_1_PAYLOAD_6( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_PAYLOAD_##ch == 48U ) ? CAN_TB_u4CFCCk_CFPLS_48 : CAN_TB_TX_FIFO_1_PAYLOAD_7( ch ) )
#define CAN_TB_TX_FIFO_1_PAYLOAD_7( ch ) \
    ( ( CAN_CFG_TX_FIFO_1_PAYLOAD_##ch == 64U ) ? CAN_TB_u4CFCCk_CFPLS_64 : CAN_TB_u4CFCCk_CFPLS_8 )

#define CAN_TB_RXINT_FIFO_PAYLOAD( ch ) \
    ( ( CAN_CFG_RXINT_FIFO_PAYLOAD_##ch == 8U )  ? CAN_TB_u4CFCCk_CFPLS_8  : CAN_TB_RXINT_FIFO_PAYLOAD_1( ch ) )
#define CAN_TB_RXINT_FIFO_PAYLOAD_1( ch ) \
    ( ( CAN_CFG_RXINT_FIFO_PAYLOAD_##ch == 12U ) ? CAN_TB_u4CFCCk_CFPLS_12 : CAN_TB_RXINT_FIFO_PAYLOAD_2( ch ) )
#define CAN_TB_RXINT_FIFO_PAYLOAD_2( ch ) \
    ( ( CAN_CFG_RXINT_FIFO_PAYLOAD_##ch == 16U ) ? CAN_TB_u4CFCCk_CFPLS_16 : CAN_TB_RXINT_FIFO_PAYLOAD_3( ch ) )
#define CAN_TB_RXINT_FIFO_PAYLOAD_3( ch ) \
    ( ( CAN_CFG_RXINT_FIFO_PAYLOAD_##ch == 20U ) ? CAN_TB_u4CFCCk_CFPLS_20 : CAN_TB_RXINT_FIFO_PAYLOAD_4( ch ) )
#define CAN_TB_RXINT_FIFO_PAYLOAD_4( ch ) \
    ( ( CAN_CFG_RXINT_FIFO_PAYLOAD_##ch == 24U ) ? CAN_TB_u4CFCCk_CFPLS_24 : CAN_TB_RXINT_FIFO_PAYLOAD_5( ch ) )
#define CAN_TB_RXINT_FIFO_PAYLOAD_5( ch ) \
    ( ( CAN_CFG_RXINT_FIFO_PAYLOAD_##ch == 32U ) ? CAN_TB_u4CFCCk_CFPLS_32 : CAN_TB_RXINT_FIFO_PAYLOAD_6( ch ) )
#define CAN_TB_RXINT_FIFO_PAYLOAD_6( ch ) \
    ( ( CAN_CFG_RXINT_FIFO_PAYLOAD_##ch == 48U ) ? CAN_TB_u4CFCCk_CFPLS_48 : CAN_TB_RXINT_FIFO_PAYLOAD_7( ch ) )
#define CAN_TB_RXINT_FIFO_PAYLOAD_7( ch ) \
    ( ( CAN_CFG_RXINT_FIFO_PAYLOAD_##ch == 64U ) ? CAN_TB_u4CFCCk_CFPLS_64 : CAN_TB_u4CFCCk_CFPLS_8 )

#define CAN_TB_u4CFCCk_CFPLS_TX0( ch )      ( CAN_TB_TX_FIFO_0_PAYLOAD( ch ) )  /* 送信用FIFO0ペイロード設定値(Config)            */
#define CAN_TB_u4CFCCk_CFPLS_TX1( ch )      ( CAN_TB_TX_FIFO_1_PAYLOAD( ch ) )  /* 送信用FIFO1ペイロード設定値(Config)            */
#define CAN_TB_u4CFCCk_CFPLS_RXINT( ch )    ( CAN_TB_RXINT_FIFO_PAYLOAD( ch ) ) /* 割り込み受信用FIFOペイロード設定値(Config)     */


/* CFTXIE(送信割込み許可) */
#define CAN_TB_u4CFCCk_CFTXIE_DIS           ( 0x00000000UL )              /* 送信割込み禁止                                       */
#define CAN_TB_u4CFCCk_CFTXIE_ENA           ( 0x00000004UL )              /* 送信割込み許可                                       */

#define CAN_TB_u4CFCCk_CFTXIE_TX0( ch )     ( ( CAN_TB_u4TX_FIFO_0_MBBIT_INT( ch ) != CAN_u4BIT_NONE ) ? CAN_TB_u4CFCCk_CFTXIE_ENA : CAN_TB_u4CFCCk_CFTXIE_DIS )
#define CAN_TB_u4CFCCk_CFTXIE_TX1( ch )     ( ( CAN_TB_u4TX_FIFO_1_MBBIT_INT( ch ) != CAN_u4BIT_NONE ) ? CAN_TB_u4CFCCk_CFTXIE_ENA : CAN_TB_u4CFCCk_CFTXIE_DIS )

/* CFRXIE(受信割込み許可) */
#define CAN_TB_u4CFCCk_CFRXIE_DIS           ( 0x00000000UL )              /* 受信割込み禁止                                       */
#define CAN_TB_u4CFCCk_CFRXIE_ENA           ( 0x00000002UL )              /* 受信割込み許可                                       */

/* CFE(送受信FIFO使用) */
#define CAN_TB_u4CFCCk_CFE_NOUSE            ( 0x00000000UL )              /* 未使用                                               */
#define CAN_TB_u4CFCCk_CFE_USE              ( 0x00000001UL )              /* 使用                                                 */

#if (CAN_OPEMODE == CAN_OPEMODE_CAN)
/* 用途別設定値 */
#define CAN_TB_u4CFCCk_TXNOUSE              (                                  CAN_TB_u4CFCCk_CFM_TX | CAN_TB_u4CFCCk_CFIM_CFIGCV    | CAN_TB_u4CFCCk_CFDC_0                                        | CAN_TB_u4CFCCk_CFTXIE_DIS       | CAN_TB_u4CFCCk_CFRXIE_DIS | CAN_TB_u4CFCCk_CFE_NOUSE ) /* 送信未使用設定値         */
#define CAN_TB_u4CFCCk_RXINT( ch )          (                                  CAN_TB_u4CFCCk_CFM_RX | CAN_TB_u4CFCCk_CFIM_ON_1MSG   | CAN_TB_u4CFCCk_CFDC_RXINT                                    | CAN_TB_u4CFCCk_CFTXIE_DIS       | CAN_TB_u4CFCCk_CFRXIE_ENA | CAN_TB_u4CFCCk_CFE_USE )   /* 割り込み受信動作用設定値 */
#define CAN_TB_u4CFCCk_RXNOUSE              (                                  CAN_TB_u4CFCCk_CFM_RX | CAN_TB_u4CFCCk_CFIM_CFIGCV    | CAN_TB_u4CFCCk_CFDC_0                                        | CAN_TB_u4CFCCk_CFTXIE_DIS       | CAN_TB_u4CFCCk_CFRXIE_DIS | CAN_TB_u4CFCCk_CFE_NOUSE ) /* 受信未使用設定値         */
#else /* (CAN_OPEMODE != CAN_OPEMODE_CAN) */
/* 用途別設定値 */
#define CAN_TB_u4CFCCk_TX0( ch )            ( CAN_TB_u4CFCCk_CFTML_TX0( ch ) | CAN_TB_u4CFCCk_CFM_TX | CAN_TB_u4CFCCk_CFIM_TX0( ch ) | CAN_TB_u4CFCCk_CFDC_TX0   | CAN_TB_u4CFCCk_CFPLS_TX0( ch )   | CAN_TB_u4CFCCk_CFTXIE_TX0( ch ) | CAN_TB_u4CFCCk_CFRXIE_DIS | CAN_TB_u4CFCCk_CFE_USE )   /* 送受信FIFO0動作用設定値  */
#define CAN_TB_u4CFCCk_TX1( ch )            ( CAN_TB_u4CFCCk_CFTML_TX1( ch ) | CAN_TB_u4CFCCk_CFM_TX | CAN_TB_u4CFCCk_CFIM_TX1( ch ) | CAN_TB_u4CFCCk_CFDC_TX1   | CAN_TB_u4CFCCk_CFPLS_TX1( ch )   | CAN_TB_u4CFCCk_CFTXIE_TX1( ch ) | CAN_TB_u4CFCCk_CFRXIE_DIS | CAN_TB_u4CFCCk_CFE_USE )   /* 送受信FIFO1動作用設定値  */
#define CAN_TB_u4CFCCk_TXNOUSE              (                                  CAN_TB_u4CFCCk_CFM_TX | CAN_TB_u4CFCCk_CFIM_CFIGCV    | CAN_TB_u4CFCCk_CFDC_0     | CAN_TB_u4CFCCk_CFPLS_8           | CAN_TB_u4CFCCk_CFTXIE_DIS       | CAN_TB_u4CFCCk_CFRXIE_DIS | CAN_TB_u4CFCCk_CFE_NOUSE ) /* 送信未使用設定値         */
#define CAN_TB_u4CFCCk_RXINT( ch )          (                                  CAN_TB_u4CFCCk_CFM_RX | CAN_TB_u4CFCCk_CFIM_ON_1MSG   | CAN_TB_u4CFCCk_CFDC_RXINT | CAN_TB_u4CFCCk_CFPLS_RXINT( ch ) | CAN_TB_u4CFCCk_CFTXIE_DIS       | CAN_TB_u4CFCCk_CFRXIE_ENA | CAN_TB_u4CFCCk_CFE_USE )   /* 割り込み受信動作用設定値 */
#define CAN_TB_u4CFCCk_RXNOUSE              (                                  CAN_TB_u4CFCCk_CFM_RX | CAN_TB_u4CFCCk_CFIM_CFIGCV    | CAN_TB_u4CFCCk_CFDC_0     | CAN_TB_u4CFCCk_CFPLS_8           | CAN_TB_u4CFCCk_CFTXIE_DIS       | CAN_TB_u4CFCCk_CFRXIE_DIS | CAN_TB_u4CFCCk_CFE_NOUSE ) /* 受信未使用設定値         */
#endif /* (CAN_OPEMODE) */

/* CFCC0レジスタ設定値 */
#if (CAN_OPEMODE == CAN_OPEMODE_CAN)
#define CAN_TB_u4CFCC0_CONF( ch )           ( CAN_TB_u4CFCCk_TXNOUSE )
#else /* (CAN_OPEMODE != CAN_OPEMODE_CAN) */
#define CAN_TB_u4CFCC0_CONF( ch )           ( ( CAN_CFG_TX_FIFO_0_LINK_##ch < CAN_TB_MBNUM_TX( ch ) ) ? CAN_TB_u4CFCCk_TX0( ch )   : CAN_TB_u4CFCCk_TXNOUSE )
#endif /* (CAN_OPEMODE) */

/* CFCC1レジスタ設定値 */
#if (CAN_OPEMODE == CAN_OPEMODE_CAN)
#define CAN_TB_u4CFCC1_CONF( ch )           ( CAN_TB_u4CFCCk_TXNOUSE )
#else /* (CAN_OPEMODE != CAN_OPEMODE_CAN) */
#define CAN_TB_u4CFCC1_CONF( ch )           ( ( CAN_CFG_TX_FIFO_1_LINK_##ch < CAN_TB_MBNUM_TX( ch ) ) ? CAN_TB_u4CFCCk_TX1( ch )   : CAN_TB_u4CFCCk_TXNOUSE )
#endif /* (CAN_OPEMODE) */

/* CFCC2レジスタ設定値 */
#define CAN_TB_u4CFCC2_CONF( ch )           ( ( CAN_CFG_RX_PROCESSING_##ch == CAN_INTERRUPT)          ? CAN_TB_u4CFCCk_RXINT( ch ) : CAN_TB_u4CFCCk_RXNOUSE )


/*----------------------------------------*/
/* CFSTS0レジスタ設定値 (Config)          */
/*  macro  : CAN_TB_u4CFSTS0_CONF( ch )   */
/*  param1 : ch 0..7                      */
/*----------------------------------------*/
/* CFSTS0レジスタ設定値 */
/* 不正割り込み時用送受信FIFO0割り込みフラグクリア用 */
#define CAN_TB_u4CFSTS0_CONF( ch )          ( ( CAN_TB_u4TX_FIFO_0_MBBIT_INT( ch ) != CAN_u4BIT_NONE ) ? ( CAN_u4CFSTSK_CFRXIF_CLR & CAN_u4CFSTSK_CFMLT_CLR ) : CAN_u4CFSTSK_CLEARALL )


/*----------------------------------------*/
/* CFSTS1レジスタ設定値 (Config)          */
/*  macro  : CAN_TB_u4CFSTS1_CONF( ch )   */
/*  param1 : ch 0..7                      */
/*----------------------------------------*/
/* CFSTS1レジスタ設定値 */
/* 不正割り込み時用送受信FIFO1割り込みフラグクリア用 */
#define CAN_TB_u4CFSTS1_CONF( ch )          ( ( CAN_TB_u4TX_FIFO_1_MBBIT_INT( ch ) != CAN_u4BIT_NONE ) ? ( CAN_u4CFSTSK_CFRXIF_CLR & CAN_u4CFSTSK_CFMLT_CLR ) : CAN_u4CFSTSK_CLEARALL )


/*----------------------------------------*/
/* CFSTS2レジスタ設定値 (Config)          */
/*  macro  : CAN_TB_u4CFSTS2_CONF( ch )   */
/*  param1 : ch 0..7                      */
/*----------------------------------------*/
/* CFSTS2レジスタ設定値 */
/* 不正割り込み時用送受信FIFO2割り込みフラグクリア用 */
#define CAN_TB_u4CFSTS2_CONF( ch )          ( (CAN_CFG_RX_PROCESSING_##ch == CAN_INTERRUPT) ? ( CAN_u4CFSTSK_CFTXIF_CLR & CAN_u4CFSTSK_CFMLT_CLR ) : CAN_u4CFSTSK_CLEARALL )


/*----------------------------------------*/
/* TMFDCTRpレジスタ設定値 (Config)        */
/*  macro  : CAN_TB_u4TMFDCTRp_CONF( ch ) */
/*  param1 : ch 0..7                      */
/*----------------------------------------*/
/* TMFDCTRpレジスタ設定値 */
/* 送信要求時用TMESIビット設定値用 */
#define CAN_TB_u4TMFDCTRp_CONF( ch )        ( (CAN_CFG_ESI_##ch == CAN_USE) ? CAN_u4TMFDCTR_ESI_E_ACT : CAN_u4TMFDCTR_ESI_E_PCV )


/*----------------------------------------*/
/* CFFDCSTSkレジスタ設定値 (Config)       */
/*  macro  : CAN_TB_u4CFFDCSTSk_CONF( ch )*/
/*  param1 : ch 0..7                      */
/*----------------------------------------*/
/* CFFDCSTSkレジスタ設定値 */
/* 送信要求時用CFESIビット設定値用 */
#define CAN_TB_u4CFFDCSTSk_CONF( ch )        ( (CAN_CFG_ESI_##ch == CAN_USE) ? CAN_u4CFFDCSTSK_CFESI_E_ACT : CAN_u4CFFDCSTSK_CFESI_E_PCV )


/*----------------------------------------*/
/* RFCCxレジスタ設定値 (Config)           */
/*  macro  : CAN_TB_u4RFCC_CONF( ch )     */
/*  param1 : ch 0..7                      */
/*----------------------------------------*/
/* RFIM(受信FIFO割込み要因) */
#define CAN_TB_u4RFCCx_RFIM_RFIGCV          ( 0x00000000UL )              /* RFICGVに指定したタイミングで割り込み(リセット初期値) */
#define CAN_TB_u4RFCCx_RFIM_ON_1MSG         ( 0x00001000UL )              /* 1メッセージ受信する毎に割り込み                      */

/* RFDC(受信FIFO段数) */
#define CAN_TB_u4RFCCx_RFDC_0               ( 0x00000000UL )              /* 受信FIFO 0段(未使用)設定値                           */
#define CAN_TB_u4RFCCx_RFDC_4               ( 0x00000100UL )              /* 受信FIFO 4段設定値                                   */
#define CAN_TB_u4RFCCx_RFDC_8               ( 0x00000200UL )              /* 受信FIFO 8段設定値                                   */
#define CAN_TB_u4RFCCx_RFDC_16              ( 0x00000300UL )              /* 受信FIFO 16段設定値                                  */
#define CAN_TB_u4RFCCx_RFDC_32              ( 0x00000400UL )              /* 受信FIFO 32段設定値                                  */
#define CAN_TB_u4RFCCx_RFDC_48              ( 0x00000500UL )              /* 受信FIFO 48段設定値                                  */
#define CAN_TB_u4RFCCx_RFDC_64              ( 0x00000600UL )              /* 受信FIFO 64段設定値                                  */
#define CAN_TB_u4RFCCx_RFDC_128             ( 0x00000700UL )              /* 受信FIFO 128段設定値                                 */

#define CAN_TB_RXPOL_FIFO_SIZE( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 0U )   ? CAN_TB_u4RFCCx_RFDC_0   : CAN_TB_RXPOL_FIFO_SIZE_1( ch ) )
#define CAN_TB_RXPOL_FIFO_SIZE_1( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 4U )   ? CAN_TB_u4RFCCx_RFDC_4   : CAN_TB_RXPOL_FIFO_SIZE_2( ch ) )
#define CAN_TB_RXPOL_FIFO_SIZE_2( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 8U )   ? CAN_TB_u4RFCCx_RFDC_8   : CAN_TB_RXPOL_FIFO_SIZE_3( ch ) )
#define CAN_TB_RXPOL_FIFO_SIZE_3( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 16U )  ? CAN_TB_u4RFCCx_RFDC_16  : CAN_TB_RXPOL_FIFO_SIZE_4( ch ) )
#define CAN_TB_RXPOL_FIFO_SIZE_4( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 32U )  ? CAN_TB_u4RFCCx_RFDC_32  : CAN_TB_RXPOL_FIFO_SIZE_5( ch ) )
#define CAN_TB_RXPOL_FIFO_SIZE_5( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 48U )  ? CAN_TB_u4RFCCx_RFDC_48  : CAN_TB_RXPOL_FIFO_SIZE_6( ch ) )
#define CAN_TB_RXPOL_FIFO_SIZE_6( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 64U )  ? CAN_TB_u4RFCCx_RFDC_64  : CAN_TB_RXPOL_FIFO_SIZE_7( ch ) )
#define CAN_TB_RXPOL_FIFO_SIZE_7( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_SIZE_##ch == 128U ) ? CAN_TB_u4RFCCx_RFDC_128 : CAN_TB_u4RFCCx_RFDC_0 )

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
#define CAN_TB_u4RFCCx_RFDC_POL( ch )       ( CAN_TB_RXPOL_FIFO_SIZE( ch ) ) /* CANFDモード:ポーリング受信用FIFO段数設定値(Config)*/
#else /* (CAN_OPEMODE != CAN_OPEMODE_CANFD) */
#define CAN_TB_u4RFCCx_RFDC_POL( ch )       ( CAN_TB_u4RFCCx_RFDC_48 )    /* CANモード:ポーリング受信用FIFO段数設定値(48段固定)   */
#endif /* (CAN_OPEMODE) */

/* RFPLS(受信FIFOベイロード格納サイズ) */
#define CAN_TB_u4RFCCx_RFPLS_8              ( 0x00000000UL )              /* 受信FIFO 8バイト設定値                               */
#define CAN_TB_u4RFCCx_RFPLS_12             ( 0x00000010UL )              /* 受信FIFO 12バイト設定値                              */
#define CAN_TB_u4RFCCx_RFPLS_16             ( 0x00000020UL )              /* 受信FIFO 16バイト設定値                              */
#define CAN_TB_u4RFCCx_RFPLS_20             ( 0x00000030UL )              /* 受信FIFO 20バイト設定値                              */
#define CAN_TB_u4RFCCx_RFPLS_24             ( 0x00000040UL )              /* 受信FIFO 24バイト設定値                              */
#define CAN_TB_u4RFCCx_RFPLS_32             ( 0x00000050UL )              /* 受信FIFO 32バイト設定値                              */
#define CAN_TB_u4RFCCx_RFPLS_48             ( 0x00000060UL )              /* 受信FIFO 48バイト設定値                              */
#define CAN_TB_u4RFCCx_RFPLS_64             ( 0x00000070UL )              /* 受信FIFO 64バイト設定値                              */

#define CAN_TB_RXPOL_FIFO_PAYLOAD( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_PAYLOAD_##ch == 8U )  ? CAN_TB_u4RFCCx_RFPLS_8  : CAN_TB_RXPOL_FIFO_PAYLOAD_1( ch ) )
#define CAN_TB_RXPOL_FIFO_PAYLOAD_1( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_PAYLOAD_##ch == 12U ) ? CAN_TB_u4RFCCx_RFPLS_12 : CAN_TB_RXPOL_FIFO_PAYLOAD_2( ch ) )
#define CAN_TB_RXPOL_FIFO_PAYLOAD_2( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_PAYLOAD_##ch == 16U ) ? CAN_TB_u4RFCCx_RFPLS_16 : CAN_TB_RXPOL_FIFO_PAYLOAD_3( ch ) )
#define CAN_TB_RXPOL_FIFO_PAYLOAD_3( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_PAYLOAD_##ch == 20U ) ? CAN_TB_u4RFCCx_RFPLS_20 : CAN_TB_RXPOL_FIFO_PAYLOAD_4( ch ) )
#define CAN_TB_RXPOL_FIFO_PAYLOAD_4( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_PAYLOAD_##ch == 24U ) ? CAN_TB_u4RFCCx_RFPLS_24 : CAN_TB_RXPOL_FIFO_PAYLOAD_5( ch ) )
#define CAN_TB_RXPOL_FIFO_PAYLOAD_5( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_PAYLOAD_##ch == 32U ) ? CAN_TB_u4RFCCx_RFPLS_32 : CAN_TB_RXPOL_FIFO_PAYLOAD_6( ch ) )
#define CAN_TB_RXPOL_FIFO_PAYLOAD_6( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_PAYLOAD_##ch == 48U ) ? CAN_TB_u4RFCCx_RFPLS_48 : CAN_TB_RXPOL_FIFO_PAYLOAD_7( ch ) )
#define CAN_TB_RXPOL_FIFO_PAYLOAD_7( ch ) \
    ( ( CAN_CFG_RXPOL_FIFO_PAYLOAD_##ch == 64U ) ? CAN_TB_u4RFCCx_RFPLS_64 : CAN_TB_u4RFCCx_RFPLS_8 )

#define CAN_TB_u4RFCCx_RFPLS_POL( ch )      ( CAN_TB_RXPOL_FIFO_PAYLOAD( ch ) ) /* ポーリング受信用FIFOペイロード設定値(Config)   */

/* RFIE(受信割込み許可) */
#define CAN_TB_u4RFCCx_RFIE_DIS             ( 0x00000000UL )              /* 受信割込み禁止                                       */

/* RFE(受信FIFO使用) */
#define CAN_TB_u4RFCCx_RFE_NOUSE            ( 0x00000000UL )              /* 未使用                                               */
#define CAN_TB_u4RFCCx_RFE_USE              ( 0x00000001UL )              /* 使用                                                 */

#if (CAN_OPEMODE == CAN_OPEMODE_CAN)
/* 用途別設定値 */
#define CAN_TB_u4RFCCx_POLLING( ch )        ( CAN_TB_u4RFCCx_RFIM_ON_1MSG | CAN_TB_u4RFCCx_RFDC_POL( ch )                                  | CAN_TB_u4RFCCx_RFIE_DIS | CAN_TB_u4RFCCx_RFE_USE )   /* ポーリング受信動作用設定値 */
#define CAN_TB_u4RFCCx_NOUSE                ( CAN_TB_u4RFCCx_RFIM_RFIGCV  | CAN_TB_u4RFCCx_RFDC_0                                          | CAN_TB_u4RFCCx_RFIE_DIS | CAN_TB_u4RFCCx_RFE_NOUSE ) /* 未使用設定値               */
#else /* (CAN_OPEMODE != CAN_OPEMODE_CAN) */
/* 用途別設定値 */
#define CAN_TB_u4RFCCx_POLLING( ch )        ( CAN_TB_u4RFCCx_RFIM_ON_1MSG | CAN_TB_u4RFCCx_RFDC_POL( ch ) | CAN_TB_u4RFCCx_RFPLS_POL( ch ) | CAN_TB_u4RFCCx_RFIE_DIS | CAN_TB_u4RFCCx_RFE_USE )   /* ポーリング受信動作用設定値 */
#define CAN_TB_u4RFCCx_NOUSE                ( CAN_TB_u4RFCCx_RFIM_RFIGCV  | CAN_TB_u4RFCCx_RFDC_0         | CAN_TB_u4RFCCx_RFPLS_8         | CAN_TB_u4RFCCx_RFIE_DIS | CAN_TB_u4RFCCx_RFE_NOUSE ) /* 未使用設定値               */
#endif /* (CAN_OPEMODE) */

/* RFCCレジスタ設定値 */
#define CAN_TB_u4RFCC_CONF( ch )            ( ( CAN_TB_RXPOLLING( ch ) == CAN_USE ) ? CAN_TB_u4RFCCx_POLLING( ch ) : CAN_TB_u4RFCCx_NOUSE )


/*--------------------------------------------------------*/
/* 受信ルールコンフィグレーションレジスタ0設定値 (Config) */
/*--------------------------------------------------------*/
#define CAN_TB_u4GAFLCFG0_CONF \
    ( ( (uint32)(CAN_CFG_HRHNUM_0) << 24U ) \
    + ( (uint32)(CAN_CFG_HRHNUM_1) << 16U ) \
    + ( (uint32)(CAN_CFG_HRHNUM_2) <<  8U ) \
    + ( (uint32)(CAN_CFG_HRHNUM_3) <<  0U ))

/*--------------------------------------------------------*/
/* 受信ルールコンフィグレーションレジスタ1設定値 (Config) */
/*--------------------------------------------------------*/
#define CAN_TB_u4GAFLCFG1_CONF \
    ( ( (uint32)(CAN_CFG_HRHNUM_4) << 24U ) \
    + ( (uint32)(CAN_CFG_HRHNUM_5) << 16U ) \
    + ( (uint32)(CAN_CFG_HRHNUM_6) <<  8U ) \
    + ( (uint32)(CAN_CFG_HRHNUM_7) <<  0U ))


/*------------------------------------------*/
/* GCFGレジスタ設定値 (Config)              */
/*------------------------------------------*/
/* [bit31-16] インターバルタイマプリスケーラ設定ビット              */
/* [bit15-13] タイムスタンプクロック源選択ビット                    */
/* [bit12]    タイムスタンプソース選択                              */
/* [bit11-8]  タイムスタンプクロック源分周ビット                    */
/* [bit7]     送信タイムスタンプ許可ビット(クラシカルCANモード)     */
/* [bit6]     ECC エラーフラグ許可ビット(クラシカルCANモード)       */
/* [bit3]     ミラー機能許可ビット                                  */
/* [bit2]     DLC 置換許可ビット                                    */
/* [bit1]     DLC チェック許可ビット                                */
#define CAN_TB_u4GCFG_BASE                  ( 0xFFFF0000UL )

/* [bit5]     ペイロードオーバフローモード選択ビット(CAN FDモード)  */
/*   0: オーバーフロー時メッセージは格納されない                    */
/*   1: オーバーフロー時、バッファサイズを超える分のペイロードは    */
/*      切り捨てられて格納される                                    */
#define CAN_TB_u4GCFG_CMPOC_STORED          ( 0x00000020UL )
#define CAN_TB_u4GCFG_CMPOC_NOTSTORED       ( 0x00000000UL )
#define CAN_TB_u4GCFG_CMPOC_CONF \
    ( (CAN_CFG_PAYLOAD_OVERFLOW_MODE == CAN_PAYLOAD_OVERFLOW_NOTSTORED) ? CAN_TB_u4GCFG_CMPOC_NOTSTORED : CAN_TB_u4GCFG_CMPOC_STORED )

/* [bit4] DCS CANクロック源選択ビット  */
/*   0: clkc                           */
/*   1: clk_xincan                     */
#define CAN_TB_u4GCFG_DCS_XINCAN            ( 0x00000010UL )
#define CAN_TB_u4GCFG_DCS_CLKC              ( 0x00000000UL )
#define CAN_TB_u4GCFG_DCS_CONF \
    ( (CAN_CFG_BAUDRATE_CLK_SOURCE == CAN_CLK_XINCAN) ? CAN_TB_u4GCFG_DCS_XINCAN : CAN_TB_u4GCFG_DCS_CLKC )

/* [bit0] TPRI 送信優先順位選択ビット  */
/*   0: ID優先                         */
/*   1: 送信バッファ番号優先           */

/* コンフィグ制約にて全チャネル同じ設定になるため代表でCH0の設定を参照する */
#define CAN_TB_TXPRIMD                      ( CAN_CFG_TXPRIMD_0 )

#define CAN_TB_u4GCFG_TPRI_ID               ( 0x00000000UL )
#define CAN_TB_u4GCFG_TPRI_MB               ( 0x00000001UL )
#define CAN_TB_u4GCFG_TPRI_CONF \
    ( (CAN_TB_TXPRIMD == CAN_IDMODE) ? CAN_TB_u4GCFG_TPRI_ID : CAN_TB_u4GCFG_TPRI_MB )

#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
#define CAN_TB_u4GCFG_CONF                  ( CAN_TB_u4GCFG_BASE | CAN_TB_u4GCFG_CMPOC_CONF | CAN_TB_u4GCFG_DCS_CONF | CAN_TB_u4GCFG_TPRI_CONF )
#else /* (CAN_OPEMODE != CAN_OPEMODE_CANFD) */
#define CAN_TB_u4GCFG_CONF                  ( CAN_TB_u4GCFG_BASE                            | CAN_TB_u4GCFG_DCS_CONF | CAN_TB_u4GCFG_TPRI_CONF )
#endif /* (CAN_OPEMODE) */



/*------------------------------------------*/
/* GFDCFGレジスタ設定値 (Config)            */
/*------------------------------------------*/
/* [bit0] PRED プロトコル例外イベント検出禁止ビット */
/*   0: プロトコル例外イベント検出許可              */
/*   1: プロトコル例外イベント検出禁止              */

/* コンフィグ制約にて全チャネル同じ設定になるため代表でCH0の設定を参照する */
#define CAN_TB_PROTOCOL_EXCEPTION           ( CAN_CFG_PROTOCOL_EXCEPTION_0 )

#define CAN_TB_u4GFDCFG_PRED_ENA            ( 0x00000000UL )
#define CAN_TB_u4GFDCFG_PRED_DIS            ( 0x00000001UL )

#define CAN_TB_u4GFDCFG_PRED_CONF \
    ( (CAN_TB_PROTOCOL_EXCEPTION == CAN_USE) ? CAN_TB_u4GFDCFG_PRED_ENA : CAN_TB_u4GFDCFG_PRED_DIS )

#define CAN_TB_u4GFDCFG_CONF                ( CAN_TB_u4GFDCFG_PRED_CONF )


/*------------------------------------------*/
/* 1CanBit時間ウェイト用カウンタ値 (Config) */
/*  macro  : CAN_TB_1CANBITTIME_COUNT       */
/*------------------------------------------*/
/* 待ち時間のタイムアウトに使用されるのみのため      */
/* コンフィグのダイナミクスのうち1CanBit時間が       */
/* 最大値となるボーレート125kbps時の値を常に使用する */

/* 除算・切り上げマクロ                                */
/* ※ プリプロ処理でのみ使用する前提で除算、剰余算利用 */
/* ※ divisorには0を指定しないこと                     */
/* ※ 本マクロは、割り切れる場合は期待値よりも1大きい  */
/*    値を応答する事に注意して利用すること             */
/*    (待ち時間のマージンに含める想定)                 */
#define CAN_TB_DIV_ROUNDUP( dividend, divisor ) \
    ( ( ( ( dividend ) - ( ( dividend ) % ( divisor ) ) ) / ( divisor ) ) + 1U )

/* マージン付与マクロ */
/* ※ 通信バスの同期のズレを考慮し、理論上のWAITカウントに1.5を乗算 */
#define CAN_TB_ADD_MARGIN( time )           ( CAN_TB_DIV_ROUNDUP( ( ( time ) * 3U), 2U ) )

/* 1CanBit時間(125kbps) */
#define CAN_TB_1CANBITTIME_125              ( 8U )

/* 1CanBit時間経過させるために必要なCANレジスタアクセス回数                 */
/* CANレジスタアクセスにかかる時間は1CANマクロ動作クロックとして計算する    */
/* 1CANBIT時間(us) / ( 1 / CANマクロ動作クロック(MHz) )                     */
/*   = 1CANBIT時間(us) * CANマクロ動作クロック(MHz)                         */
#define CAN_TB_1CANBITTIME_COUNT            ( CAN_TB_ADD_MARGIN( CAN_TB_1CANBITTIME_125 * CAN_CFG_CONTROLLER_CLK ) )

/*--------------------------------------------------*/
/* ビットレートスイッチ使用/未使用設定値 (Config)   */
/*  macro  : CAN_TB_u1BRS_INIT_CONF( ch )           */
/*  param1 : ch 0..7                                */
/*--------------------------------------------------*/
#define CAN_TB_u1BRS_INIT_CONF( ch )        ( (CAN_CFG_DBAUDRATE_SWT_##ch == CAN_USE) ? ((uint8)CAN_ST_BRS_USE) : ((uint8)CAN_ST_BRS_NOUSE) )


/*--------------------------------------------------*/
/* 送信用FIFO接続MBOXビットマスク                   */
/*  macro  : CAN_TB_u2FIFO_BITMASK( ch )            */
/*  param1 : ch 0..7                                */
/*--------------------------------------------------*/
#define CAN_TB_u1TX_FIFO_MASK               ( (uint8)0x0F ) /* 有効MBOX番号ビットマスク */

#define CAN_TB_u2TX_FIFO_0_BIT( ch )        ( (uint16)( CAN_u2BIT0 << ( (uint8)CAN_CFG_TX_FIFO_0_LINK_##ch & CAN_TB_u1TX_FIFO_MASK ) ) ) /* 送信用FIFO0接続MBOXビット位置 */
#define CAN_TB_u2TX_FIFO_1_BIT( ch )        ( (uint16)( CAN_u2BIT0 << ( (uint8)CAN_CFG_TX_FIFO_1_LINK_##ch & CAN_TB_u1TX_FIFO_MASK ) ) ) /* 送信用FIFO1接続MBOXビット位置 */

#define CAN_TB_u2TX_FIFO_0_BITMASK( ch )    ( (CAN_CFG_TX_FIFO_0_LINK_##ch < CAN_TB_MBNUM_TX( ch )) ? ( CAN_u2ALLBIT ^ CAN_TB_u2TX_FIFO_0_BIT( ch ) ) : CAN_u2ALLBIT )
#define CAN_TB_u2TX_FIFO_1_BITMASK( ch )    ( (CAN_CFG_TX_FIFO_1_LINK_##ch < CAN_TB_MBNUM_TX( ch )) ? ( CAN_u2ALLBIT ^ CAN_TB_u2TX_FIFO_1_BIT( ch ) ) : CAN_u2ALLBIT )

#define CAN_TB_u2TX_FIFO_BITMASK( ch )      ( CAN_TB_u2TX_FIFO_0_BITMASK( ch ) & CAN_TB_u2TX_FIFO_1_BITMASK( ch ) )


/*--------------------------------------------------*/
/* 送信用FIFO毎書き込み回数の最大値                 */
/*  macro  : CAN_TB_FIFO_0_WRITESIZE( ch )          */
/*           CAN_TB_FIFO_1_WRITESIZE( ch )          */
/*  param1 : ch 0..7                                */
/*--------------------------------------------------*/
#define CAN_TB_FIFO_0_WRITESIZE( ch )       ( (uint8)( CAN_CFG_TX_FIFO_0_PAYLOAD_##ch >> 2U ) )
#define CAN_TB_FIFO_1_WRITESIZE( ch )       ( (uint8)( CAN_CFG_TX_FIFO_1_PAYLOAD_##ch >> 2U ) )


/*--------------------------------------------------*/
/* ポーリング受信用受信FIFO読み出し回数の最大値     */
/*  macro  : CAN_TB_RXPOL_FIFO_READSIZE( ch )       */
/*  param1 : ch 0..7                                */
/*--------------------------------------------------*/
#define CAN_TB_RXPOL_FIFO_READSIZE( ch )    ( (uint8)( CAN_CFG_RXPOL_FIFO_PAYLOAD_##ch >> 2U ) )


/*--------------------------------------------------*/
/* 割り込み受信用送受信FIFO 2 読み出し回数の最大値  */
/*  macro  : CAN_TB_RXINT_FIFO_READSIZE( ch )       */
/*  param1 : ch 0..7                                */
/*--------------------------------------------------*/
#define CAN_TB_RXINT_FIFO_READSIZE( ch )    ( (uint8)( CAN_CFG_RXINT_FIFO_PAYLOAD_##ch >> 2U ) )


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
/*==================================================================*/
/* コントローラ管理情報テーブル                                     */
/*==================================================================*/
/* param1 : コントローラ番号                                        */
/* value  : コントローラ使用情報                                    */
/*   - u2RxRuleOffSetId 受信ルール設定テーブル・先頭インデックス    */
/*   - u1RxRuleUseNum   受信ルールの数                              */
/*   - u1CtrlAct        コントローラ別制御対象/非対象               */
/*   - u1CtrlUse        コントローラ別使用/未使用                   */
/*------------------------------------------------------------------*/
CanConst CanTbCtrlInfoType Can_tb_stCtrlInfo[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /* u2RxRuleOffSetId             , u1RxRuleUseNum         , u1CtrlAct                             , u1CtrlUse                       */
     { (uint16)CAN_TB_RXRULE_OFFSET0, (uint8)CAN_CFG_HRHNUM_0, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_0, (uint8)CAN_CFG_CONTROLLER_CAN_0  }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET1, (uint8)CAN_CFG_HRHNUM_1, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_1, (uint8)CAN_CFG_CONTROLLER_CAN_1  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET2, (uint8)CAN_CFG_HRHNUM_2, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_2, (uint8)CAN_CFG_CONTROLLER_CAN_2  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET3, (uint8)CAN_CFG_HRHNUM_3, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_3, (uint8)CAN_CFG_CONTROLLER_CAN_3  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET4, (uint8)CAN_CFG_HRHNUM_4, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_4, (uint8)CAN_CFG_CONTROLLER_CAN_4  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET5, (uint8)CAN_CFG_HRHNUM_5, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_5, (uint8)CAN_CFG_CONTROLLER_CAN_5  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET6, (uint8)CAN_CFG_HRHNUM_6, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_6, (uint8)CAN_CFG_CONTROLLER_CAN_6  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,{ (uint16)CAN_TB_RXRULE_OFFSET7, (uint8)CAN_CFG_HRHNUM_7, (uint8)CAN_CFG_CONTROLLER_ACTIVATION_7, (uint8)CAN_CFG_CONTROLLER_CAN_7  }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};


/*==================================================================*/
/* MBOX要素数テーブル                                               */
/*==================================================================*/
/* param1 : コントローラ番号                                        */
/* value  : MBOX配置情報                                            */
/*   - u1TxMbNum    送信MBOX数                                      */
/* ※ コンフィグ項目名称、及びlog層とのI/FをMBOXで統一しているため  */
/*    テーブル名、要素名はMBOXとする                                */
/*   ※u1TxMbNumはユーザ送信用MBOXを含む                            */
/*------------------------------------------------------------------*/
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


/*==================================================================*/
/* チャネル単位のレジスタアドレステーブル                           */
/*==================================================================*/
CanConst CanTbChRegType Can_tb_stChReg[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /* CONTROLLER 0 */
     {
         CAN_TB_ptu2CH0_TMIECy_ADDR        /* ptu2TMIECy        */
        ,CAN_TB_ptu2CH0_TMTRSTSy_ADDR      /* ptu2TMTRSTSy      */
        ,CAN_TB_ptu2CH0_TMTARSTSy_ADDR     /* ptu2TMTARSTSy     */
        ,CAN_TB_ptu2CH0_TMTCSTSy_ADDR      /* ptu2TMTCSTSy      */
        ,CAN_TB_ptu2CH0_TMTASTSy_ADDR      /* ptu2TMTASTSy      */
        ,CAN_TB_ptu4CH0_CmCFG_ADDR         /* ptu4CmCFG         */
        ,CAN_TB_ptu4CH0_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH0_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH0_CmERFL_ADDR        /* ptu4CmERFL        */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptu4CH0_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH0_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH0_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH0_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH0_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH0_TXQCCm_ADDR        /* ptu4TXQCCm        */
        ,CAN_TB_ptu4CH0_TXQSTSm_ADDR       /* ptu4TXQSTSm       */
        ,CAN_TB_ptu4CH0_TXQPCTRm_ADDR      /* ptu4TXQPCTRm      */
        ,CAN_TB_ptu4CH0_THLCCm_ADDR        /* ptu4THLCCm        */
        ,CAN_TB_ptu4CH0_THLSTSm_ADDR       /* ptu4THLSTSm       */
        ,CAN_TB_ptu4CH0_THLPCTRm_ADDR      /* ptu4THLPCTRm      */
        ,CAN_TB_ptu4CH0_CFSTSk_ADDR        /* ptu4CFSTSk        */
        ,CAN_TB_ptu1CH0_TMSTSp_ADDR        /* ptu1TMSTSp        */
        ,CAN_TB_ptu4CH0_CFCCk_ADDR         /* ptu4CFCCk         */
        ,CAN_TB_ptu4CH0_CFPCTRk_ADDR       /* ptu4CFPCTRk       */
        ,CAN_TB_ptu1CH0_TMCp_ADDR          /* ptu1TMCp          */
        ,CAN_TB_ptstCH0_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH0_TM_ADDR            /* ptstTM            */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptstCH0_TM_MERGE_ADDR      /* ptstTM_MERGE      */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH0_THLACCm_ADDR       /* ptu4THLACCm       */
    }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    /* CONTROLLER 1 */
    ,{
         CAN_TB_ptu2CH1_TMIECy_ADDR        /* ptu2TMIECy        */
        ,CAN_TB_ptu2CH1_TMTRSTSy_ADDR      /* ptu2TMTRSTSy      */
        ,CAN_TB_ptu2CH1_TMTARSTSy_ADDR     /* ptu2TMTARSTSy     */
        ,CAN_TB_ptu2CH1_TMTCSTSy_ADDR      /* ptu2TMTCSTSy      */
        ,CAN_TB_ptu2CH1_TMTASTSy_ADDR      /* ptu2TMTASTSy      */
        ,CAN_TB_ptu4CH1_CmCFG_ADDR         /* ptu4CmCFG         */
        ,CAN_TB_ptu4CH1_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH1_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH1_CmERFL_ADDR        /* ptu4CmERFL        */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptu4CH1_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH1_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH1_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH1_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH1_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH1_TXQCCm_ADDR        /* ptu4TXQCCm        */
        ,CAN_TB_ptu4CH1_TXQSTSm_ADDR       /* ptu4TXQSTSm       */
        ,CAN_TB_ptu4CH1_TXQPCTRm_ADDR      /* ptu4TXQPCTRm      */
        ,CAN_TB_ptu4CH1_THLCCm_ADDR        /* ptu4THLCCm        */
        ,CAN_TB_ptu4CH1_THLSTSm_ADDR       /* ptu4THLSTSm       */
        ,CAN_TB_ptu4CH1_THLPCTRm_ADDR      /* ptu4THLPCTRm      */
        ,CAN_TB_ptu4CH1_CFSTSk_ADDR        /* ptu4CFSTSk        */
        ,CAN_TB_ptu1CH1_TMSTSp_ADDR        /* ptu1TMSTSp        */
        ,CAN_TB_ptu4CH1_CFCCk_ADDR         /* ptu4CFCCk         */
        ,CAN_TB_ptu4CH1_CFPCTRk_ADDR       /* ptu4CFPCTRk       */
        ,CAN_TB_ptu1CH1_TMCp_ADDR          /* ptu1TMCp          */
        ,CAN_TB_ptstCH1_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH1_TM_ADDR            /* ptstTM            */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptstCH1_TM_MERGE_ADDR      /* ptstTM_MERGE      */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH1_THLACCm_ADDR       /* ptu4THLACCm       */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    /* CONTROLLER 2 */
    ,{
         CAN_TB_ptu2CH2_TMIECy_ADDR        /* ptu2TMIECy        */
        ,CAN_TB_ptu2CH2_TMTRSTSy_ADDR      /* ptu2TMTRSTSy      */
        ,CAN_TB_ptu2CH2_TMTARSTSy_ADDR     /* ptu2TMTARSTSy     */
        ,CAN_TB_ptu2CH2_TMTCSTSy_ADDR      /* ptu2TMTCSTSy      */
        ,CAN_TB_ptu2CH2_TMTASTSy_ADDR      /* ptu2TMTASTSy      */
        ,CAN_TB_ptu4CH2_CmCFG_ADDR         /* ptu4CmCFG         */
        ,CAN_TB_ptu4CH2_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH2_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH2_CmERFL_ADDR        /* ptu4CmERFL        */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptu4CH2_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH2_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH2_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH2_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH2_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH2_TXQCCm_ADDR        /* ptu4TXQCCm        */
        ,CAN_TB_ptu4CH2_TXQSTSm_ADDR       /* ptu4TXQSTSm       */
        ,CAN_TB_ptu4CH2_TXQPCTRm_ADDR      /* ptu4TXQPCTRm      */
        ,CAN_TB_ptu4CH2_THLCCm_ADDR        /* ptu4THLCCm        */
        ,CAN_TB_ptu4CH2_THLSTSm_ADDR       /* ptu4THLSTSm       */
        ,CAN_TB_ptu4CH2_THLPCTRm_ADDR      /* ptu4THLPCTRm      */
        ,CAN_TB_ptu4CH2_CFSTSk_ADDR        /* ptu4CFSTSk        */
        ,CAN_TB_ptu1CH2_TMSTSp_ADDR        /* ptu1TMSTSp        */
        ,CAN_TB_ptu4CH2_CFCCk_ADDR         /* ptu4CFCCk         */
        ,CAN_TB_ptu4CH2_CFPCTRk_ADDR       /* ptu4CFPCTRk       */
        ,CAN_TB_ptu1CH2_TMCp_ADDR          /* ptu1TMCp          */
        ,CAN_TB_ptstCH2_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH2_TM_ADDR            /* ptstTM            */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptstCH2_TM_MERGE_ADDR      /* ptstTM_MERGE      */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH2_THLACCm_ADDR       /* ptu4THLACCm       */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    /* CONTROLLER 3 */
    ,{
         CAN_TB_ptu2CH3_TMIECy_ADDR        /* ptu2TMIECy        */
        ,CAN_TB_ptu2CH3_TMTRSTSy_ADDR      /* ptu2TMTRSTSy      */
        ,CAN_TB_ptu2CH3_TMTARSTSy_ADDR     /* ptu2TMTARSTSy     */
        ,CAN_TB_ptu2CH3_TMTCSTSy_ADDR      /* ptu2TMTCSTSy      */
        ,CAN_TB_ptu2CH3_TMTASTSy_ADDR      /* ptu2TMTASTSy      */
        ,CAN_TB_ptu4CH3_CmCFG_ADDR         /* ptu4CmCFG         */
        ,CAN_TB_ptu4CH3_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH3_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH3_CmERFL_ADDR        /* ptu4CmERFL        */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptu4CH3_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH3_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH3_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH3_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH3_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH3_TXQCCm_ADDR        /* ptu4TXQCCm        */
        ,CAN_TB_ptu4CH3_TXQSTSm_ADDR       /* ptu4TXQSTSm       */
        ,CAN_TB_ptu4CH3_TXQPCTRm_ADDR      /* ptu4TXQPCTRm      */
        ,CAN_TB_ptu4CH3_THLCCm_ADDR        /* ptu4THLCCm        */
        ,CAN_TB_ptu4CH3_THLSTSm_ADDR       /* ptu4THLSTSm       */
        ,CAN_TB_ptu4CH3_THLPCTRm_ADDR      /* ptu4THLPCTRm      */
        ,CAN_TB_ptu4CH3_CFSTSk_ADDR        /* ptu4CFSTSk        */
        ,CAN_TB_ptu1CH3_TMSTSp_ADDR        /* ptu1TMSTSp        */
        ,CAN_TB_ptu4CH3_CFCCk_ADDR         /* ptu4CFCCk         */
        ,CAN_TB_ptu4CH3_CFPCTRk_ADDR       /* ptu4CFPCTRk       */
        ,CAN_TB_ptu1CH3_TMCp_ADDR          /* ptu1TMCp          */
        ,CAN_TB_ptstCH3_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH3_TM_ADDR            /* ptstTM            */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptstCH3_TM_MERGE_ADDR      /* ptstTM_MERGE      */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH3_THLACCm_ADDR       /* ptu4THLACCm       */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    /* CONTROLLER 4 */
    ,{
         CAN_TB_ptu2CH4_TMIECy_ADDR        /* ptu2TMIECy        */
        ,CAN_TB_ptu2CH4_TMTRSTSy_ADDR      /* ptu2TMTRSTSy      */
        ,CAN_TB_ptu2CH4_TMTARSTSy_ADDR     /* ptu2TMTARSTSy     */
        ,CAN_TB_ptu2CH4_TMTCSTSy_ADDR      /* ptu2TMTCSTSy      */
        ,CAN_TB_ptu2CH4_TMTASTSy_ADDR      /* ptu2TMTASTSy      */
        ,CAN_TB_ptu4CH4_CmCFG_ADDR         /* ptu4CmCFG         */
        ,CAN_TB_ptu4CH4_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH4_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH4_CmERFL_ADDR        /* ptu4CmERFL        */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptu4CH4_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH4_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH4_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH4_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH4_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH4_TXQCCm_ADDR        /* ptu4TXQCCm        */
        ,CAN_TB_ptu4CH4_TXQSTSm_ADDR       /* ptu4TXQSTSm       */
        ,CAN_TB_ptu4CH4_TXQPCTRm_ADDR      /* ptu4TXQPCTRm      */
        ,CAN_TB_ptu4CH4_THLCCm_ADDR        /* ptu4THLCCm        */
        ,CAN_TB_ptu4CH4_THLSTSm_ADDR       /* ptu4THLSTSm       */
        ,CAN_TB_ptu4CH4_THLPCTRm_ADDR      /* ptu4THLPCTRm      */
        ,CAN_TB_ptu4CH4_CFSTSk_ADDR        /* ptu4CFSTSk        */
        ,CAN_TB_ptu1CH4_TMSTSp_ADDR        /* ptu1TMSTSp        */
        ,CAN_TB_ptu4CH4_CFCCk_ADDR         /* ptu4CFCCk         */
        ,CAN_TB_ptu4CH4_CFPCTRk_ADDR       /* ptu4CFPCTRk       */
        ,CAN_TB_ptu1CH4_TMCp_ADDR          /* ptu1TMCp          */
        ,CAN_TB_ptstCH4_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH4_TM_ADDR            /* ptstTM            */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptstCH4_TM_MERGE_ADDR      /* ptstTM_MERGE      */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH4_THLACCm_ADDR       /* ptu4THLACCm       */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    /* CONTROLLER 5 */
    ,{
         CAN_TB_ptu2CH5_TMIECy_ADDR        /* ptu2TMIECy        */
        ,CAN_TB_ptu2CH5_TMTRSTSy_ADDR      /* ptu2TMTRSTSy      */
        ,CAN_TB_ptu2CH5_TMTARSTSy_ADDR     /* ptu2TMTARSTSy     */
        ,CAN_TB_ptu2CH5_TMTCSTSy_ADDR      /* ptu2TMTCSTSy      */
        ,CAN_TB_ptu2CH5_TMTASTSy_ADDR      /* ptu2TMTASTSy      */
        ,CAN_TB_ptu4CH5_CmCFG_ADDR         /* ptu4CmCFG         */
        ,CAN_TB_ptu4CH5_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH5_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH5_CmERFL_ADDR        /* ptu4CmERFL        */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptu4CH5_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH5_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH5_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH5_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH5_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH5_TXQCCm_ADDR        /* ptu4TXQCCm        */
        ,CAN_TB_ptu4CH5_TXQSTSm_ADDR       /* ptu4TXQSTSm       */
        ,CAN_TB_ptu4CH5_TXQPCTRm_ADDR      /* ptu4TXQPCTRm      */
        ,CAN_TB_ptu4CH5_THLCCm_ADDR        /* ptu4THLCCm        */
        ,CAN_TB_ptu4CH5_THLSTSm_ADDR       /* ptu4THLSTSm       */
        ,CAN_TB_ptu4CH5_THLPCTRm_ADDR      /* ptu4THLPCTRm      */
        ,CAN_TB_ptu4CH5_CFSTSk_ADDR        /* ptu4CFSTSk        */
        ,CAN_TB_ptu1CH5_TMSTSp_ADDR        /* ptu1TMSTSp        */
        ,CAN_TB_ptu4CH5_CFCCk_ADDR         /* ptu4CFCCk         */
        ,CAN_TB_ptu4CH5_CFPCTRk_ADDR       /* ptu4CFPCTRk       */
        ,CAN_TB_ptu1CH5_TMCp_ADDR          /* ptu1TMCp          */
        ,CAN_TB_ptstCH5_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH5_TM_ADDR            /* ptstTM            */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptstCH5_TM_MERGE_ADDR      /* ptstTM_MERGE      */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH5_THLACCm_ADDR       /* ptu4THLACCm       */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    /* CONTROLLER 6 */
    ,{
         CAN_TB_ptu2CH6_TMIECy_ADDR        /* ptu2TMIECy        */
        ,CAN_TB_ptu2CH6_TMTRSTSy_ADDR      /* ptu2TMTRSTSy      */
        ,CAN_TB_ptu2CH6_TMTARSTSy_ADDR     /* ptu2TMTARSTSy     */
        ,CAN_TB_ptu2CH6_TMTCSTSy_ADDR      /* ptu2TMTCSTSy      */
        ,CAN_TB_ptu2CH6_TMTASTSy_ADDR      /* ptu2TMTASTSy      */
        ,CAN_TB_ptu4CH6_CmCFG_ADDR         /* ptu4CmCFG         */
        ,CAN_TB_ptu4CH6_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH6_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH6_CmERFL_ADDR        /* ptu4CmERFL        */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptu4CH6_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH6_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH6_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH6_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH6_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH6_TXQCCm_ADDR        /* ptu4TXQCCm        */
        ,CAN_TB_ptu4CH6_TXQSTSm_ADDR       /* ptu4TXQSTSm       */
        ,CAN_TB_ptu4CH6_TXQPCTRm_ADDR      /* ptu4TXQPCTRm      */
        ,CAN_TB_ptu4CH6_THLCCm_ADDR        /* ptu4THLCCm        */
        ,CAN_TB_ptu4CH6_THLSTSm_ADDR       /* ptu4THLSTSm       */
        ,CAN_TB_ptu4CH6_THLPCTRm_ADDR      /* ptu4THLPCTRm      */
        ,CAN_TB_ptu4CH6_CFSTSk_ADDR        /* ptu4CFSTSk        */
        ,CAN_TB_ptu1CH6_TMSTSp_ADDR        /* ptu1TMSTSp        */
        ,CAN_TB_ptu4CH6_CFCCk_ADDR         /* ptu4CFCCk         */
        ,CAN_TB_ptu4CH6_CFPCTRk_ADDR       /* ptu4CFPCTRk       */
        ,CAN_TB_ptu1CH6_TMCp_ADDR          /* ptu1TMCp          */
        ,CAN_TB_ptstCH6_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH6_TM_ADDR            /* ptstTM            */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptstCH6_TM_MERGE_ADDR      /* ptstTM_MERGE      */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH6_THLACCm_ADDR       /* ptu4THLACCm       */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    /* CONTROLLER 7 */
    ,{
         CAN_TB_ptu2CH7_TMIECy_ADDR        /* ptu2TMIECy        */
        ,CAN_TB_ptu2CH7_TMTRSTSy_ADDR      /* ptu2TMTRSTSy      */
        ,CAN_TB_ptu2CH7_TMTARSTSy_ADDR     /* ptu2TMTARSTSy     */
        ,CAN_TB_ptu2CH7_TMTCSTSy_ADDR      /* ptu2TMTCSTSy      */
        ,CAN_TB_ptu2CH7_TMTASTSy_ADDR      /* ptu2TMTASTSy      */
        ,CAN_TB_ptu4CH7_CmCFG_ADDR         /* ptu4CmCFG         */
        ,CAN_TB_ptu4CH7_CmCTR_ADDR         /* ptu4CmCTR         */
        ,CAN_TB_ptu4CH7_CmSTS_ADDR         /* ptu4CmSTS         */
        ,CAN_TB_ptu4CH7_CmERFL_ADDR        /* ptu4CmERFL        */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptu4CH7_CmDCFG_ADDR        /* ptu4CmDCFG        */
        ,CAN_TB_ptu4CH7_CmFDCFG_ADDR       /* ptu4CmFDCFG       */
        ,CAN_TB_ptu4CH7_CmFDCTR_ADDR       /* ptu4CmFDCTR       */
        ,CAN_TB_ptu4CH7_CmFDSTS_ADDR       /* ptu4CmFDSTS       */
        ,CAN_TB_ptu4CH7_CmFDCRC_ADDR       /* ptu4CmFDCRC       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH7_TXQCCm_ADDR        /* ptu4TXQCCm        */
        ,CAN_TB_ptu4CH7_TXQSTSm_ADDR       /* ptu4TXQSTSm       */
        ,CAN_TB_ptu4CH7_TXQPCTRm_ADDR      /* ptu4TXQPCTRm      */
        ,CAN_TB_ptu4CH7_THLCCm_ADDR        /* ptu4THLCCm        */
        ,CAN_TB_ptu4CH7_THLSTSm_ADDR       /* ptu4THLSTSm       */
        ,CAN_TB_ptu4CH7_THLPCTRm_ADDR      /* ptu4THLPCTRm      */
        ,CAN_TB_ptu4CH7_CFSTSk_ADDR        /* ptu4CFSTSk        */
        ,CAN_TB_ptu1CH7_TMSTSp_ADDR        /* ptu1TMSTSp        */
        ,CAN_TB_ptu4CH7_CFCCk_ADDR         /* ptu4CFCCk         */
        ,CAN_TB_ptu4CH7_CFPCTRk_ADDR       /* ptu4CFPCTRk       */
        ,CAN_TB_ptu1CH7_TMCp_ADDR          /* ptu1TMCp          */
        ,CAN_TB_ptstCH7_CF_ADDR            /* ptstCF            */
        ,CAN_TB_ptstCH7_TM_ADDR            /* ptstTM            */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
        ,CAN_TB_ptstCH7_TM_MERGE_ADDR      /* ptstTM_MERGE      */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
        ,CAN_TB_ptu4CH7_THLACCm_ADDR       /* ptu4THLACCm       */
    }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};


/*==================================================================*/
/* グローバルレジスタアドレステーブル                               */
/*==================================================================*/
CanConst CanTbGlobalRegType Can_tb_stGlobalReg =
{
     CAN_TB_ptu4GRMCFG_ADDR                /* ptu4GRMCFG        */
    ,CAN_TB_ptu4GCFG_ADDR                  /* ptu4GCFG          */
    ,CAN_TB_ptu4GCTR_ADDR                  /* ptu4GCTR          */
    ,CAN_TB_ptu4GSTS_ADDR                  /* ptu4GSTS          */
    ,CAN_TB_ptu4GERFL_ADDR                 /* ptu4GERFL         */
    ,CAN_TB_ptu4GTSC_ADDR                  /* ptu4GTSC          */
    ,CAN_TB_ptu4GAFLECTR_ADDR              /* ptu4GAFLECTR      */
    ,CAN_TB_ptu4GAFLCFG_ADDR               /* ptu4GAFLCFG       */
    ,CAN_TB_ptu4RMNB_ADDR                  /* ptu4RMNB          */
    ,CAN_TB_ptu4RMNDy_ADDR                 /* ptu4RMNDy         */
    ,CAN_TB_ptu4RFCCx_ADDR                 /* ptu4RFCCx         */
    ,CAN_TB_ptu4RFSTSx_ADDR                /* ptu4RFSTSx        */
    ,CAN_TB_ptu4RFPCTRx_ADDR               /* ptu4RFPCTRx       */
    ,CAN_TB_ptu4FESTS_ADDR                 /* ptu4FESTS         */
    ,CAN_TB_ptu4FFSTS_ADDR                 /* ptu4FFSTS         */
    ,CAN_TB_ptu4FMSTS_ADDR                 /* ptu4FMSTS         */
    ,CAN_TB_ptu4RFISTS_ADDR                /* ptu4RFISTS        */
    ,CAN_TB_ptu4CFRISTS_ADDR               /* ptu4CFRISTS       */
    ,CAN_TB_ptu4CFTISTS_ADDR               /* ptu4CFTISTS       */
    ,CAN_TB_ptu4GTINTSTS_ADDR              /* ptu4GTINTSTS      */
    ,CAN_TB_ptu4GTSTCFG_ADDR               /* ptu4GTSTCFG       */
    ,CAN_TB_ptu4GTSTCTR_ADDR               /* ptu4GTSTCTR       */
    ,CAN_TB_ptu4GFDCFG_ADDR                /* ptu4GFDCFG        */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    ,CAN_TB_ptu4GCRCCFG_ADDR               /* ptu4GCRCCFG       */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    ,CAN_TB_ptu4GLOCKK_ADDR                /* ptu4GLOCKK        */
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
    ,CAN_TB_ptu4CDTCT_ADDR                 /* ptu4CDTCT         */
    ,CAN_TB_ptu4CDTSTS_ADDR                /* ptu4CDTSTS        */
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
    ,CAN_TB_ptstGAFL_ADDR                  /* ptstGAFL          */
    ,CAN_TB_ptstRM_ADDR                    /* ptstRM            */
    ,CAN_TB_ptstRF_ADDR                    /* ptstRF            */
    ,CAN_TB_ptu4RPGACCr_ADDR               /* ptu4RPGACCr       */
    ,CAN_TB_ptu4CANFDMDR_ADDR              /* ptu4CANFDMDR      */
};


/*==================================================================*/
/* レジスタ固着チェック分割情報テーブル                             */
/*==================================================================*/
/* param1 : レジスタ固着チェック実施 最大分割回数                   */
/* value  : レジスタ固着チェック分割情報                            */
/*   - u1StChkStart レジスタ固着チェック開始ページ                  */
/*   - u1StChkPage  レジスタ固着チェックページ数                    */
/*------------------------------------------------------------------*/
CanConst CanTbCheckStuckParaType Can_tb_stCheckStuckPara[ CAN_CFG_CHKSTKREG_LIMIT ] =
{
    /*  u1StChkStart                    , u1StChkPage                    */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 1U)
     {  (uint8)CAN_TB_STUCK_CHK_START_0 , (uint8)CAN_TB_STUCK_CHK_PAGE_0  }
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 1U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 5U)
    ,{  (uint8)CAN_TB_STUCK_CHK_START_1 , (uint8)CAN_TB_STUCK_CHK_PAGE_1  }
    ,{  (uint8)CAN_TB_STUCK_CHK_START_2 , (uint8)CAN_TB_STUCK_CHK_PAGE_2  }
    ,{  (uint8)CAN_TB_STUCK_CHK_START_3 , (uint8)CAN_TB_STUCK_CHK_PAGE_3  }
    ,{  (uint8)CAN_TB_STUCK_CHK_START_4 , (uint8)CAN_TB_STUCK_CHK_PAGE_4  }
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 5U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 10U)
    ,{  (uint8)CAN_TB_STUCK_CHK_START_5 , (uint8)CAN_TB_STUCK_CHK_PAGE_5  }
    ,{  (uint8)CAN_TB_STUCK_CHK_START_6 , (uint8)CAN_TB_STUCK_CHK_PAGE_6  }
    ,{  (uint8)CAN_TB_STUCK_CHK_START_7 , (uint8)CAN_TB_STUCK_CHK_PAGE_7  }
    ,{  (uint8)CAN_TB_STUCK_CHK_START_8 , (uint8)CAN_TB_STUCK_CHK_PAGE_8  }
    ,{  (uint8)CAN_TB_STUCK_CHK_START_9 , (uint8)CAN_TB_STUCK_CHK_PAGE_9  }
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 10U) */
#if (CAN_CFG_CHKSTKREG_LIMIT >= 12U)
    ,{  (uint8)CAN_TB_STUCK_CHK_START_10, (uint8)CAN_TB_STUCK_CHK_PAGE_10 }
    ,{  (uint8)CAN_TB_STUCK_CHK_START_11, (uint8)CAN_TB_STUCK_CHK_PAGE_11 }
#endif /* (CAN_CFG_CHKSTKREG_LIMIT >= 12U) */
};


/*==================================================================*/
/* 送信MBOX種別ビット情報テーブル                                   */
/*==================================================================*/
/* param1 : コントローラ番号                                        */
/* value  : MBOX種別ビット情報                                      */
/*   - u2TxIntrBit 割り込み送信MBOX bit列                           */
/*   - u2TxPollBit ポーリング送信MBOX bit列                         */
/*   ※u2TxIntrBitおよびu2TxPollBitはユーザ送信用MBOXを含む         */
/*------------------------------------------------------------------*/
CanConst CanTbTxMbBitType Can_tb_stTxMbBit[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /*   u2TxIntrBit              , u2TxPollBit                 */
    /* Controller 0 */
     {  CAN_TB_u2TXMBBIT( 0, INT ), CAN_TB_u2TXMBBIT( 0, POL ) }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    /* Controller 1 */
    ,{  CAN_TB_u2TXMBBIT( 1, INT ), CAN_TB_u2TXMBBIT( 1, POL ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    /* Controller 2 */
    ,{  CAN_TB_u2TXMBBIT( 2, INT ), CAN_TB_u2TXMBBIT( 2, POL ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    /* Controller 3 */
    ,{  CAN_TB_u2TXMBBIT( 3, INT ), CAN_TB_u2TXMBBIT( 3, POL ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    /* Controller 4 */
    ,{  CAN_TB_u2TXMBBIT( 4, INT ), CAN_TB_u2TXMBBIT( 4, POL ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    /* Controller 5 */
    ,{  CAN_TB_u2TXMBBIT( 5, INT ), CAN_TB_u2TXMBBIT( 5, POL ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    /* Controller 6 */
    ,{  CAN_TB_u2TXMBBIT( 6, INT ), CAN_TB_u2TXMBBIT( 6, POL ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    /* Controller 7 */
    ,{  CAN_TB_u2TXMBBIT( 7, INT ), CAN_TB_u2TXMBBIT( 7, POL ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};


/*==================================================================*/
/* 受信ルール設定値テーブル                                         */
/*==================================================================*/
/* param1 : 受信用MBOX番号(Offset減算)                              */
/* value  : 受信ルール情報                                          */
/*   - u4GAFLIDjConf 受信ルールIDレジスタ設定値                     */
/*   - u4GAFLP0jConf 受信ルールポインタ0レジスタ設定値              */
/*   - u4GAFLP1jConf 受信ルールポインタ1レジスタ設定値              */
/*   - u1RxMaskRef   受信IDマスク番号                               */
/* ※ 受信用に使用するMBOX数分(コンフィグ)+1の要素数を持つ。        */
/*    受信MBOX数0を考慮しDummyを定義する。                          */
/* ※ 受信用MBOXは間隔を空けず連続で設定される前提とする。          */
/*    MBOX番号から受信MBOX開始番号を減算した値をインデクスとする。  */
/*------------------------------------------------------------------*/
CanConst CanTbRxRuleSettingType Can_tb_stRxRuleSetting[ CAN_TB_RXRULESETTBLSIZE ] =
{
    /* u4GAFLIDjConf           , u4GAFLP0jConf                   , u4GAFLP1jConf               , u1RxMaskRef                                                                                */

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
     { CAN_TB_u4GAFLID_DUMMY   , CAN_TB_u4GAFLP0_DUMMY           , CAN_TB_u4GAFLP1_DUMMY       , (uint8)CAN_TB_u1RXMASK_DUMMY                                                             }     /* Dummy定義 */
};


/*==================================================================*/
/* 受信マスク値テーブル                                             */
/*==================================================================*/
/* param1 : 受信マスクID                                            */
/* value  : 受信マスク値                                            */
/*   ※使用する受信IDマスク数分(コンフィグ)の要素数 + 2 を持つ。    */
/*     配列要素の最終メンバ - 1 は、標準ID用 受信IDマスク未使用時   */
/*     のレジスタ設定値を設定する。                                 */
/*     配列要素の最終メンバは、拡張ID用 受信IDマスク未使用時の      */
/*     レジスタ設定値を設定する。                                   */
/*------------------------------------------------------------------*/
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
    CAN_u4GAFLMJ_STDIDMSK_NOUSE,                /* 標準IDフィルタマスク初期化値(受信IDマスク未使用) */
    CAN_u4GAFLMJ_EXTIDMSK_NOUSE                 /* 拡張IDフィルタマスク初期化値(受信IDマスク未使用) */
};


/*====================================================================================*/
/* RSCANレジスタ設定値テーブル                                                        */
/*====================================================================================*/
/* param1 : コントローラ番号                                                          */
/* value  : RSCANレジスタ設定値                                                       */
/*   - u4CFCC0Conf       送受信FIFOバッファ0コンフィグレーションレジスタ設定値        */
/*   - u4CFCC1Conf       送受信FIFOバッファ1コンフィグレーションレジスタ設定値        */
/*   - u4CFCC2Conf       送受信FIFOバッファ2コンフィグレーションレジスタ設定値        */
/*   - u4CmCFGConf       クラシカルCANモード：                                        */
/*                         チャネルコンフィグレーションレジスタ設定値                 */
/*                       CAN FDモード       ：                                        */
/*                         チャネル通常ビットレートコンフィグレーションレジスタ設定値 */
/*   - u4CmCTRConf       チャネル制御レジスタ設定値                                   */
/*   - u4CFSTS0Conf      不正割り込み時用送受信FIFOバッファ0割り込みフラグクリア値    */
/*   - u4CFSTS1Conf      不正割り込み時用送受信FIFOバッファ1割り込みフラグクリア値    */
/*   - u4CFSTS2Conf      不正割り込み時用送受信FIFOバッファ2割り込みフラグクリア値    */
/*   - u4RFCCConf        受信FIFOバッファコンフィグレーションレジスタ設定値           */
/*   - u4CmDCFGConf      チャネルデータビットレートコンフィグレーションレジスタ設定値 */
/*   - u4CmFDCFGConf     チャネルCAN FDコンフィグレーションレジスタ設定値             */
/*   - u4TMFDCTRpConf    送信要求時用TMESIビット設定値                                */
/*   - u4CFFDCSTSkConf   送信要求時用CFESIビット設定値                                */
/*------------------------------------------------------------------------------------*/
CanConst CanTbSetRSCANRegType Can_tb_stSetRSCANReg[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
    /* u4CFCC0Conf              , u4CFCC1Conf               , u4CFCC2Conf                , u4CmCFGConf                   */
    /*,u4CmCTRConf              , u4CFSTS0Conf              , u4CFSTS1Conf               , u4CFSTS2Conf                  */
    /*,u4RFCCConf                                                                                                        */
    /*,u4CmDCFGConf             , u4CmFDCFGConf             , u4TMFDCTRpConf             , u4CFFDCSTSkConf               */
    /* Controller 0 */
     { CAN_TB_u4CFCC0_CONF( 0 ) , CAN_TB_u4CFCC1_CONF( 0 )  , CAN_TB_u4CFCC2_CONF( 0 )   , CAN_TB_u4CmCFG_CONF( 0 )
      ,CAN_TB_u4CMCTR_CONF( 0 ) , CAN_TB_u4CFSTS0_CONF( 0 ) , CAN_TB_u4CFSTS1_CONF( 0 )  , CAN_TB_u4CFSTS2_CONF( 0 )
      ,CAN_TB_u4RFCC_CONF( 0 )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
      ,CAN_TB_u4CmDCFG_CONF( 0 ), CAN_TB_u4CMFDCFG_CONF( 0 ), CAN_TB_u4TMFDCTRp_CONF( 0 ), CAN_TB_u4CFFDCSTSk_CONF( 0 )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
     }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    /* Controller 1 */
    ,{ CAN_TB_u4CFCC0_CONF( 1 ) , CAN_TB_u4CFCC1_CONF( 1 )  , CAN_TB_u4CFCC2_CONF( 1 )   , CAN_TB_u4CmCFG_CONF( 1 )
      ,CAN_TB_u4CMCTR_CONF( 1 ) , CAN_TB_u4CFSTS0_CONF( 1 ) , CAN_TB_u4CFSTS1_CONF( 1 )  , CAN_TB_u4CFSTS2_CONF( 1 )
      ,CAN_TB_u4RFCC_CONF( 1 )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
      ,CAN_TB_u4CmDCFG_CONF( 1 ), CAN_TB_u4CMFDCFG_CONF( 1 ), CAN_TB_u4TMFDCTRp_CONF( 1 ), CAN_TB_u4CFFDCSTSk_CONF( 1 )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    /* Controller 2 */
    ,{ CAN_TB_u4CFCC0_CONF( 2 ) , CAN_TB_u4CFCC1_CONF( 2 )  , CAN_TB_u4CFCC2_CONF( 2 )   , CAN_TB_u4CmCFG_CONF( 2 )
      ,CAN_TB_u4CMCTR_CONF( 2 ) , CAN_TB_u4CFSTS0_CONF( 2 ) , CAN_TB_u4CFSTS1_CONF( 2 )  , CAN_TB_u4CFSTS2_CONF( 2 )
      ,CAN_TB_u4RFCC_CONF( 2 )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
      ,CAN_TB_u4CmDCFG_CONF( 2 ), CAN_TB_u4CMFDCFG_CONF( 2 ), CAN_TB_u4TMFDCTRp_CONF( 2 ), CAN_TB_u4CFFDCSTSk_CONF( 2 )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    /* Controller 3 */
    ,{ CAN_TB_u4CFCC0_CONF( 3 ) , CAN_TB_u4CFCC1_CONF( 3 )  , CAN_TB_u4CFCC2_CONF( 3 )   , CAN_TB_u4CmCFG_CONF( 3 )
      ,CAN_TB_u4CMCTR_CONF( 3 ) , CAN_TB_u4CFSTS0_CONF( 3 ) , CAN_TB_u4CFSTS1_CONF( 3 )  , CAN_TB_u4CFSTS2_CONF( 3 )
      ,CAN_TB_u4RFCC_CONF( 3 )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
      ,CAN_TB_u4CmDCFG_CONF( 3 ), CAN_TB_u4CMFDCFG_CONF( 3 ), CAN_TB_u4TMFDCTRp_CONF( 3 ), CAN_TB_u4CFFDCSTSk_CONF( 3 )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    /* Controller 4 */
    ,{ CAN_TB_u4CFCC0_CONF( 4 ) , CAN_TB_u4CFCC1_CONF( 4 )  , CAN_TB_u4CFCC2_CONF( 4 )   , CAN_TB_u4CmCFG_CONF( 4 )
      ,CAN_TB_u4CMCTR_CONF( 4 ) , CAN_TB_u4CFSTS0_CONF( 4 ) , CAN_TB_u4CFSTS1_CONF( 4 )  , CAN_TB_u4CFSTS2_CONF( 4 )
      ,CAN_TB_u4RFCC_CONF( 4 )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
      ,CAN_TB_u4CmDCFG_CONF( 4 ), CAN_TB_u4CMFDCFG_CONF( 4 ), CAN_TB_u4TMFDCTRp_CONF( 4 ), CAN_TB_u4CFFDCSTSk_CONF( 4 )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    /* Controller 5 */
    ,{ CAN_TB_u4CFCC0_CONF( 5 ) , CAN_TB_u4CFCC1_CONF( 5 )  , CAN_TB_u4CFCC2_CONF( 5 )   , CAN_TB_u4CmCFG_CONF( 5 )
      ,CAN_TB_u4CMCTR_CONF( 5 ) , CAN_TB_u4CFSTS0_CONF( 5 ) , CAN_TB_u4CFSTS1_CONF( 5 )  , CAN_TB_u4CFSTS2_CONF( 5 )
      ,CAN_TB_u4RFCC_CONF( 5 )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
      ,CAN_TB_u4CmDCFG_CONF( 5 ), CAN_TB_u4CMFDCFG_CONF( 5 ), CAN_TB_u4TMFDCTRp_CONF( 5 ), CAN_TB_u4CFFDCSTSk_CONF( 5 )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    /* Controller 6 */
    ,{ CAN_TB_u4CFCC0_CONF( 6 ) , CAN_TB_u4CFCC1_CONF( 6 )  , CAN_TB_u4CFCC2_CONF( 6 )   , CAN_TB_u4CmCFG_CONF( 6 )
      ,CAN_TB_u4CMCTR_CONF( 6 ) , CAN_TB_u4CFSTS0_CONF( 6 ) , CAN_TB_u4CFSTS1_CONF( 6 )  , CAN_TB_u4CFSTS2_CONF( 6 )
      ,CAN_TB_u4RFCC_CONF( 6 )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
      ,CAN_TB_u4CmDCFG_CONF( 6 ), CAN_TB_u4CMFDCFG_CONF( 6 ), CAN_TB_u4TMFDCTRp_CONF( 6 ), CAN_TB_u4CFFDCSTSk_CONF( 6 )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    /* Controller 7 */
    ,{ CAN_TB_u4CFCC0_CONF( 7 ) , CAN_TB_u4CFCC1_CONF( 7 )  , CAN_TB_u4CFCC2_CONF( 7 )   , CAN_TB_u4CmCFG_CONF( 7 )
      ,CAN_TB_u4CMCTR_CONF( 7 ) , CAN_TB_u4CFSTS0_CONF( 7 ) , CAN_TB_u4CFSTS1_CONF( 7 )  , CAN_TB_u4CFSTS2_CONF( 7 )
      ,CAN_TB_u4RFCC_CONF( 7 )
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
      ,CAN_TB_u4CmDCFG_CONF( 7 ), CAN_TB_u4CMFDCFG_CONF( 7 ), CAN_TB_u4TMFDCTRp_CONF( 7 ), CAN_TB_u4CFFDCSTSk_CONF( 7 )
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
     }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};


/*==================================================================*/
/* ビットレートスイッチ設定値テーブル                               */
/*==================================================================*/
/* param1 : コントローラ番号                                        */
/* value  : ビットレートスイッチ使用/未使用初期設定値               */
/*------------------------------------------------------------------*/
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
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
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */


/*==================================================================*/
/* ボーレート切り替えコンフィグ情報テーブル参照ポインタ             */
/*==================================================================*/
/* param1 : なし                                                    */
/* value  : ボーレート切り替えコンフィグ情報ポインタ                */
/*------------------------------------------------------------------*/
/* 将来コンフィグセット複数対応する場合に、コンフィグセット毎の     */
/* テーブルを切り替えられるようにするためのポインタ。               */
CanConst CanBaudrateSwtCfgType * CanConst Can_tb_ptBaudrateSwtCfgTbl = &(Can_stBaudrateSwtCfgTbl[ CAN_IDX0 ]);


/*==================================================================*/
/* ボーレート切り替えコンフィグ情報テーブルの要素数参照ポインタ     */
/*==================================================================*/
/* 将来コンフィグセット複数対応する場合に、コンフィグセット毎の     */
/* テーブルを切り替えられるようにするためのポインタ。               */
CanConst uint8 * CanConst Can_tb_ptBRSwtCfgTbl_ARYSIZE = &(Can_stBRSwtCfgTbl_ARYSIZE);


/*==================================================================*/
/* CAN RAM初期化用カウンタ最大値                                    */
/*==================================================================*/
CanConst uint32 Can_tb_u4RAMInitCycleMax = (uint32)CAN_CFG_RAM_INIT_CYCLE;


/*==================================================================*/
/* モード遷移完了待ちカウンタ値                                     */
/*==================================================================*/
CanConst uint16 Can_tb_u2CmodeRst2ComWaitCnt = (uint16)(CAN_TB_1CANBITTIME_COUNT * CAN_CMODE_RST2COM_BITTIME); /* チャネルリセットモードからチャネル通信モード       */
CanConst uint16 Can_tb_u2CmodeAny2RstWaitCnt = (uint16)(CAN_TB_1CANBITTIME_COUNT * CAN_CMODE_ANY2RST_BITTIME); /* 任意のチャネルモードからチャネルリセットモード     */
CanConst uint16 Can_tb_u2GmodeAny2RstWaitCnt = (uint16)(CAN_TB_1CANBITTIME_COUNT * CAN_GMODE_ANY2RST_BITTIME); /* 任意のグローバルモードからグローバルリセットモード */


/*==================================================================*/
/* 総コントローラ数                                                 */
/*==================================================================*/
CanConst uint8 Can_tb_u1CtrlNum = (uint8)CAN_CFG_CONTROLLERNUM_MAX;


/*==================================================================*/
/* 受信ルール数                                                     */
/*==================================================================*/
CanConst uint16 Can_tb_u2MaxNumRxRule = (uint16)CAN_TB_MAX_NUMBER_OF_RX_RULE;


/*==================================================================*/
/* 受信ルールページ数                                               */
/*==================================================================*/
CanConst uint8 Can_tb_u1RxRulePageNum = (uint8)(CAN_NUM_RULETABLE_PAGE_CH * CAN_CFG_CONTROLLERNUM_MAX);


/*==================================================================*/
/* レジスタ固着チェック対象最終ページ                               */
/*==================================================================*/
CanConst uint8 Can_tb_u1LastTestpage = (uint8)CAN_TB_TESTPAGENUM;


/*==================================================================*/
/* レジスタ固着チェック対象最終ページ 端数レジスタ数                */
/*==================================================================*/
CanConst uint8 Can_tb_u1LastTestpageRegNum = (uint8)CAN_TB_TESTREGNUM;


/*==================================================================*/
/* 受信ルールコンフィグレーションレジスタ設定値                     */
/*==================================================================*/
CanConst uint32 Can_tb_u4GAFLCFG0Conf = CAN_TB_u4GAFLCFG0_CONF;
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
CanConst uint32 Can_tb_u4GAFLCFG1Conf = CAN_TB_u4GAFLCFG1_CONF;
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */


/*==================================================================*/
/* グローバルコンフィグレーションレジスタ設定値                     */
/*==================================================================*/
CanConst uint32 Can_tb_u4GCFGConf = CAN_TB_u4GCFG_CONF;


/*==================================================================*/
/* グローバルFDコンフィグレーションレジスタ設定値                   */
/*==================================================================*/
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
CanConst uint32 Can_tb_u4GFDCFGConf = CAN_TB_u4GFDCFG_CONF;
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */


/*==================================================================*/
/* 送信用FIFO0接続MBOX番号テーブル                                  */
/*==================================================================*/
/* param1 : コントローラ番号                                        */
/* value  : 送受信FIFO0を使用する場合   : 送信用FIFO0接続MBOX番号   */
/*        : 送受信FIFO0を使用しない場合 : 無効なMBOX番号            */
/*------------------------------------------------------------------*/
#if (CAN_CFG_TRANSMIT == CAN_USE)
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
CanConst uint8 Can_tb_u1TxFifo0LinkConf[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
     CAN_CFG_TX_FIFO_0_LINK_0
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,CAN_CFG_TX_FIFO_0_LINK_1
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,CAN_CFG_TX_FIFO_0_LINK_2
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,CAN_CFG_TX_FIFO_0_LINK_3
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,CAN_CFG_TX_FIFO_0_LINK_4
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,CAN_CFG_TX_FIFO_0_LINK_5
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,CAN_CFG_TX_FIFO_0_LINK_6
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,CAN_CFG_TX_FIFO_0_LINK_7
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/*==================================================================*/
/* 送信用FIFO1接続MBOX番号テーブル                                  */
/*==================================================================*/
/* param1 : コントローラ番号                                        */
/* value  : 送受信FIFO1を使用する場合   : 送信用FIFO1接続MBOX番号   */
/*        : 送受信FIFO1を使用しない場合 : 無効なMBOX番号            */
/*------------------------------------------------------------------*/
#if (CAN_CFG_TRANSMIT == CAN_USE)
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
CanConst uint8 Can_tb_u1TxFifo1LinkConf[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
     CAN_CFG_TX_FIFO_1_LINK_0
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,CAN_CFG_TX_FIFO_1_LINK_1
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,CAN_CFG_TX_FIFO_1_LINK_2
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,CAN_CFG_TX_FIFO_1_LINK_3
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,CAN_CFG_TX_FIFO_1_LINK_4
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,CAN_CFG_TX_FIFO_1_LINK_5
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,CAN_CFG_TX_FIFO_1_LINK_6
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,CAN_CFG_TX_FIFO_1_LINK_7
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/*==================================================================*/
/* 送信用FIFO接続MBOXビットマスクテーブル                           */
/*==================================================================*/
/* param1 : コントローラ番号                                        */
/* value  : 送受信FIFOを使用する場合   :                            */
/*        :     送信用FIFO接続MBOXのビットマスク                    */
/*        :         送信用FIFO接続MBOX位置 : 0                      */
/*        :         その他のビット         : 1                      */
/*        : 送受信FIFOを使用しない場合 : 0xFFFF                     */
/*------------------------------------------------------------------*/
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
CanConst uint16 Can_tb_u2TxFifoBitMask[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
     CAN_TB_u2TX_FIFO_BITMASK( 0 )
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,CAN_TB_u2TX_FIFO_BITMASK( 1 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,CAN_TB_u2TX_FIFO_BITMASK( 2 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,CAN_TB_u2TX_FIFO_BITMASK( 3 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,CAN_TB_u2TX_FIFO_BITMASK( 4 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,CAN_TB_u2TX_FIFO_BITMASK( 5 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,CAN_TB_u2TX_FIFO_BITMASK( 6 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,CAN_TB_u2TX_FIFO_BITMASK( 7 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */


/*==================================================================*/
/* 送信用FIFO書き込み回数の最大値テーブル                           */
/*==================================================================*/
/* param1 : コントローラ番号                                        */
/* param1 : 送受信FIFO番号                                          */
/* value  : 書き込み回数の最大値                                    */
/*------------------------------------------------------------------*/
#if (CAN_CFG_TRANSMIT == CAN_USE)
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
CanConst uint8 Can_tb_u1FifoWriteSize[ CAN_CFG_CONTROLLERNUM_MAX ][ CAN_TRX_FIFO_FOR_TX ] =
{
     { (uint8)CAN_TB_FIFO_0_WRITESIZE( 0 ), (uint8)CAN_TB_FIFO_1_WRITESIZE( 0 ) }
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,{ (uint8)CAN_TB_FIFO_0_WRITESIZE( 1 ), (uint8)CAN_TB_FIFO_1_WRITESIZE( 1 ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,{ (uint8)CAN_TB_FIFO_0_WRITESIZE( 2 ), (uint8)CAN_TB_FIFO_1_WRITESIZE( 2 ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,{ (uint8)CAN_TB_FIFO_0_WRITESIZE( 3 ), (uint8)CAN_TB_FIFO_1_WRITESIZE( 3 ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,{ (uint8)CAN_TB_FIFO_0_WRITESIZE( 4 ), (uint8)CAN_TB_FIFO_1_WRITESIZE( 4 ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,{ (uint8)CAN_TB_FIFO_0_WRITESIZE( 5 ), (uint8)CAN_TB_FIFO_1_WRITESIZE( 5 ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,{ (uint8)CAN_TB_FIFO_0_WRITESIZE( 6 ), (uint8)CAN_TB_FIFO_1_WRITESIZE( 6 ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,{ (uint8)CAN_TB_FIFO_0_WRITESIZE( 7 ), (uint8)CAN_TB_FIFO_1_WRITESIZE( 7 ) }
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/*==================================================================*/
/* ポーリング受信用受信FIFO読み出し回数の最大値テーブル             */
/*==================================================================*/
/* param1 : コントローラ番号                                        */
/* value  : 読み出し回数の最大値                                    */
/*------------------------------------------------------------------*/
#if (CAN_CFG_RECEIVE == CAN_USE)
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
CanConst uint8 Can_tb_u1FifoReadSizePol[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
     (uint8)CAN_TB_RXPOL_FIFO_READSIZE( 0 )
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,(uint8)CAN_TB_RXPOL_FIFO_READSIZE( 1 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,(uint8)CAN_TB_RXPOL_FIFO_READSIZE( 2 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,(uint8)CAN_TB_RXPOL_FIFO_READSIZE( 3 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,(uint8)CAN_TB_RXPOL_FIFO_READSIZE( 4 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,(uint8)CAN_TB_RXPOL_FIFO_READSIZE( 5 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,(uint8)CAN_TB_RXPOL_FIFO_READSIZE( 6 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,(uint8)CAN_TB_RXPOL_FIFO_READSIZE( 7 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#endif /* (CAN_CFG_RECEIVE == CAN_USE) */


/*==================================================================*/
/* 割り込み受信用送受信FIFO 2 読み出し回数の最大値テーブル          */
/*==================================================================*/
/* param1 : コントローラ番号                                        */
/* value  : 読み出し回数の最大値                                    */
/*------------------------------------------------------------------*/
#if (CAN_CFG_RECEIVE == CAN_USE)
#if (CAN_OPEMODE == CAN_OPEMODE_CANFD)
CanConst uint8 Can_tb_u1FifoReadSizeInt[ CAN_CFG_CONTROLLERNUM_MAX ] =
{
     (uint8)CAN_TB_RXINT_FIFO_READSIZE( 0 )
#if (CAN_CFG_CONTROLLERNUM_MAX > 1U)
    ,(uint8)CAN_TB_RXINT_FIFO_READSIZE( 1 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 1U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 2U)
    ,(uint8)CAN_TB_RXINT_FIFO_READSIZE( 2 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 2U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 3U)
    ,(uint8)CAN_TB_RXINT_FIFO_READSIZE( 3 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 3U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 4U)
    ,(uint8)CAN_TB_RXINT_FIFO_READSIZE( 4 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 4U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 5U)
    ,(uint8)CAN_TB_RXINT_FIFO_READSIZE( 5 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 5U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 6U)
    ,(uint8)CAN_TB_RXINT_FIFO_READSIZE( 6 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 6U) */
#if (CAN_CFG_CONTROLLERNUM_MAX > 7U)
    ,(uint8)CAN_TB_RXINT_FIFO_READSIZE( 7 )
#endif /* (CAN_CFG_CONTROLLERNUM_MAX > 7U) */
};
#endif /* (CAN_OPEMODE == CAN_OPEMODE_CANFD) */
#endif /* (CAN_CFG_RECEIVE == CAN_USE) */




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
/*  v2-0-0         :2017/02/22                                              */
/*  v2-0-1         :2017/03/28                                              */
/*  v2-0-2         :2017/04/24                                              */
/*  v2-0-3         :2019/08/07                                              */
/*  v2-2-0         :2020/02/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
