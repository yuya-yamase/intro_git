/* can_rscf41_tb_phy_h_m10700_v3-0-0                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF41/TB/PHYSICAL/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF41_TB_PHY_H
#define     CAN_RSCF41_TB_PHY_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_TB_RXMKTBLSIZE              ( CAN_CFG_FILTER_MASK_NUM + 2U )

#define CAN_TB_MB_DATA_ARYSIZE          ( 16U )

#define CAN_TB_PFL_REG_RSV              ( 7U )

#define CAN_TB_MB_REG_RSV               ( 13U )

#define CAN_TB_MAX_NUMBER_OF_RX_RULE \
    ( CAN_CFG_HRHNUM_0 + CAN_CFG_HRHNUM_1 + CAN_CFG_HRHNUM_2 + CAN_CFG_HRHNUM_3 \
    + CAN_CFG_HRHNUM_4 + CAN_CFG_HRHNUM_5 + CAN_CFG_HRHNUM_6 + CAN_CFG_HRHNUM_7 )

#define CAN_TB_RXRULESETTBLSIZE         ( CAN_TB_MAX_NUMBER_OF_RX_RULE + 1U )

#define CAN_TB_TXMBSIZE                 ( 2U )


#define CAN_TB_PSG2_125K_2M_PTN1            (  4UL )
#define CAN_TB_PSG2_125K_2P5M_PTN1          (  5UL )
#define CAN_TB_PSG2_250K_4M_PTN1            (  4UL )
#define CAN_TB_PSG2_250K_4M_PTN2            (  2UL )
#define CAN_TB_PSG2_250K_5M_PTN1            (  5UL )
#define CAN_TB_PSG2_250K_5M_PTN2            (  3UL )
#define CAN_TB_PSG2_500K_8M_PTN1            (  3UL )
#define CAN_TB_PSG2_500K_8M_PTN2            (  3UL )
#define CAN_TB_PSG2_500K_8M_PTN3            (  4UL )
#define CAN_TB_PSG2_500K_8M_PTN4            (  4UL )
#define CAN_TB_PSG2_500K_8M_PTN5            (  2UL )
#define CAN_TB_PSG2_500K_10M_PTN1           (  5UL )
#define CAN_TB_PSG2_500K_10M_PTN2           (  4UL )
#define CAN_TB_PSG2_500K_10M_PTN3           (  4UL )
#define CAN_TB_PSG2_500K_10M_PTN4           (  3UL )
#define CAN_TB_PSG2_500K_10M_PTN5           (  3UL )
#define CAN_TB_PSG2_500K_20M_PTN1           (  8UL )
#define CAN_TB_PSG2_500K_32M_PTN1           ( 12UL )
#define CAN_TB_PSG2_500K_40M_PTN1           ( 16UL )
#define CAN_TB_PSG2_500K_40M_PTN2           ( 16UL )
#define CAN_TB_PSG2_500K_80M_PTN1           ( 32UL )

#define CAN_TB_PRP_PSG1_125K_2M_PTN1        (  11UL )
#define CAN_TB_PRP_PSG1_125K_2P5M_PTN1      (  14UL )
#define CAN_TB_PRP_PSG1_250K_4M_PTN1        (  11UL )
#define CAN_TB_PRP_PSG1_250K_4M_PTN2        (  13UL )
#define CAN_TB_PRP_PSG1_250K_5M_PTN1        (  14UL )
#define CAN_TB_PRP_PSG1_250K_5M_PTN2        (  16UL )
#define CAN_TB_PRP_PSG1_500K_8M_PTN1        (  12UL )
#define CAN_TB_PRP_PSG1_500K_8M_PTN2        (  12UL )
#define CAN_TB_PRP_PSG1_500K_8M_PTN3        (  11UL )
#define CAN_TB_PRP_PSG1_500K_8M_PTN4        (  11UL )
#define CAN_TB_PRP_PSG1_500K_8M_PTN5        (  13UL )
#define CAN_TB_PRP_PSG1_500K_10M_PTN1       (  14UL )
#define CAN_TB_PRP_PSG1_500K_10M_PTN2       (  15UL )
#define CAN_TB_PRP_PSG1_500K_10M_PTN3       (  15UL )
#define CAN_TB_PRP_PSG1_500K_10M_PTN4       (  16UL )
#define CAN_TB_PRP_PSG1_500K_10M_PTN5       (  16UL )
#define CAN_TB_PRP_PSG1_500K_20M_PTN1       (  31UL )
#define CAN_TB_PRP_PSG1_500K_32M_PTN1       (  51UL )
#define CAN_TB_PRP_PSG1_500K_40M_PTN1       (  63UL )
#define CAN_TB_PRP_PSG1_500K_40M_PTN2       (  63UL )
#define CAN_TB_PRP_PSG1_500K_80M_PTN1       ( 127UL )

#define CAN_TB_SJW_125K_2M_PTN1             (  4UL )
#define CAN_TB_SJW_125K_2P5M_PTN1           (  4UL )
#define CAN_TB_SJW_250K_4M_PTN1             (  4UL )
#define CAN_TB_SJW_250K_4M_PTN2             (  1UL )
#define CAN_TB_SJW_250K_5M_PTN1             (  4UL )
#define CAN_TB_SJW_250K_5M_PTN2             (  1UL )
#define CAN_TB_SJW_500K_8M_PTN1             (  2UL )
#define CAN_TB_SJW_500K_8M_PTN2             (  3UL )
#define CAN_TB_SJW_500K_8M_PTN3             (  2UL )
#define CAN_TB_SJW_500K_8M_PTN4             (  4UL )
#define CAN_TB_SJW_500K_8M_PTN5             (  1UL )
#define CAN_TB_SJW_500K_10M_PTN1            (  2UL )
#define CAN_TB_SJW_500K_10M_PTN2            (  3UL )
#define CAN_TB_SJW_500K_10M_PTN3            (  4UL )
#define CAN_TB_SJW_500K_10M_PTN4            (  2UL )
#define CAN_TB_SJW_500K_10M_PTN5            (  1UL )
#define CAN_TB_SJW_500K_20M_PTN1            (  5UL )
#define CAN_TB_SJW_500K_32M_PTN1            (  7UL )
#define CAN_TB_SJW_500K_40M_PTN1            (  8UL )
#define CAN_TB_SJW_500K_40M_PTN2            ( 16UL )
#define CAN_TB_SJW_500K_80M_PTN1            ( 32UL )

#define CAN_TB_CLK_FRQ_125K_2M_PTN1         (  2000UL )
#define CAN_TB_CLK_FRQ_125K_2P5M_PTN1       (  2500UL )
#define CAN_TB_CLK_FRQ_250K_4M_PTN1         (  4000UL )
#define CAN_TB_CLK_FRQ_250K_4M_PTN2         (  4000UL )
#define CAN_TB_CLK_FRQ_250K_5M_PTN1         (  5000UL )
#define CAN_TB_CLK_FRQ_250K_5M_PTN2         (  5000UL )
#define CAN_TB_CLK_FRQ_500K_8M_PTN1         (  8000UL )
#define CAN_TB_CLK_FRQ_500K_8M_PTN2         (  8000UL )
#define CAN_TB_CLK_FRQ_500K_8M_PTN3         (  8000UL )
#define CAN_TB_CLK_FRQ_500K_8M_PTN4         (  8000UL )
#define CAN_TB_CLK_FRQ_500K_8M_PTN5         (  8000UL )
#define CAN_TB_CLK_FRQ_500K_10M_PTN1        ( 10000UL )
#define CAN_TB_CLK_FRQ_500K_10M_PTN2        ( 10000UL )
#define CAN_TB_CLK_FRQ_500K_10M_PTN3        ( 10000UL )
#define CAN_TB_CLK_FRQ_500K_10M_PTN4        ( 10000UL )
#define CAN_TB_CLK_FRQ_500K_10M_PTN5        ( 10000UL )
#define CAN_TB_CLK_FRQ_500K_20M_PTN1        ( 20000UL )
#define CAN_TB_CLK_FRQ_500K_32M_PTN1        ( 32000UL )
#define CAN_TB_CLK_FRQ_500K_40M_PTN1        ( 40000UL )
#define CAN_TB_CLK_FRQ_500K_40M_PTN2        ( 40000UL )
#define CAN_TB_CLK_FRQ_500K_80M_PTN1        ( 80000UL )
#define CAN_TB_CLK_FRQ( ptn )               ( CAN_TB_CLK_FRQ_##ptn )

#define CAN_TB_CAN_CLK_KHZ                  ( (uint32)CAN_CFG_BAUDRATE_CLK * 1000UL )

#define CAN_TB_BAUDRATE_DISABLE             ( 0U )
#define CAN_TB_BAUDRATE_ENABLE              ( 1U )
#define CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) \
    ( ( ( CAN_TB_CAN_CLK_KHZ % CAN_TB_CLK_FRQ( ptn ) ) == 0UL ) ? CAN_TB_BAUDRATE_ENABLE : CAN_TB_BAUDRATE_DISABLE )

#define CAN_TB_u4CmNCFG_BRP_PLUS1( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( CAN_TB_CAN_CLK_KHZ / CAN_TB_CLK_FRQ( ptn ) ) : 1UL )
#define CAN_TB_u4CmNCFG_BRP( ptn )          ( CAN_TB_u4CmNCFG_BRP_PLUS1( ptn ) - 1UL )

#define CAN_TB_u4CmNCFG_TSEG1( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_PRP_PSG1_##ptn - 1UL ) : 0UL )

#define CAN_TB_u4CmNCFG_TSEG2( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_PSG2_##ptn - 1UL ) : 0UL )

#define CAN_TB_u4CmNCFG_SJW( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn )  == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_SJW_##ptn - 1UL ) : 0UL )

#define CAN_TB_CmNCFG_SFT_SJW               ( 10U )
#define CAN_TB_CmNCFG_SFT_TSEG2             ( 25U )
#define CAN_TB_CmNCFG_SFT_TSEG1             ( 17U )
#define CAN_TB_CmNCFG_SFT_BRP               (  0U )
#define CAN_TB_u4CmNCFG_BIT_SJW             ( 0x0001FC00UL )
#define CAN_TB_u4CmNCFG_BIT_TSEG2           ( 0xFE000000UL )
#define CAN_TB_u4CmNCFG_BIT_TSEG1           ( 0x01FE0000UL )
#define CAN_TB_u4CmNCFG_BIT_BRP             ( 0x000003FFUL )

#define CAN_TB_u4CmNCFG( ptn ) \
    ( (((uint32)CAN_TB_u4CmNCFG_BRP( ptn )   << CAN_TB_CmNCFG_SFT_BRP)   & CAN_TB_u4CmNCFG_BIT_BRP   ) \
    | (((uint32)CAN_TB_u4CmNCFG_TSEG1( ptn ) << CAN_TB_CmNCFG_SFT_TSEG1) & CAN_TB_u4CmNCFG_BIT_TSEG1 ) \
    | (((uint32)CAN_TB_u4CmNCFG_TSEG2( ptn ) << CAN_TB_CmNCFG_SFT_TSEG2) & CAN_TB_u4CmNCFG_BIT_TSEG2 ) \
    | (((uint32)CAN_TB_u4CmNCFG_SJW( ptn )   << CAN_TB_CmNCFG_SFT_SJW)   & CAN_TB_u4CmNCFG_BIT_SJW   ) )

#define CAN_TB_USER_BAUDRATE                ( 0xFFFFFFFFUL )
#define CAN_TB_125K_2M_PTN1                 ( CAN_TB_u4CmNCFG( 125K_2M_PTN1 ) )
#define CAN_TB_125K_2P5M_PTN1               ( CAN_TB_u4CmNCFG( 125K_2P5M_PTN1 ) )
#define CAN_TB_250K_4M_PTN1                 ( CAN_TB_u4CmNCFG( 250K_4M_PTN1 ) )
#define CAN_TB_250K_4M_PTN2                 ( CAN_TB_u4CmNCFG( 250K_4M_PTN2 ) )
#define CAN_TB_250K_5M_PTN1                 ( CAN_TB_u4CmNCFG( 250K_5M_PTN1 ) )
#define CAN_TB_250K_5M_PTN2                 ( CAN_TB_u4CmNCFG( 250K_5M_PTN2 ) )
#define CAN_TB_500K_8M_PTN1                 ( CAN_TB_u4CmNCFG( 500K_8M_PTN1 ) )
#define CAN_TB_500K_8M_PTN2                 ( CAN_TB_u4CmNCFG( 500K_8M_PTN2 ) )
#define CAN_TB_500K_8M_PTN3                 ( CAN_TB_u4CmNCFG( 500K_8M_PTN3 ) )
#define CAN_TB_500K_8M_PTN4                 ( CAN_TB_u4CmNCFG( 500K_8M_PTN4 ) )
#define CAN_TB_500K_8M_PTN5                 ( CAN_TB_u4CmNCFG( 500K_8M_PTN5 ) )
#define CAN_TB_500K_10M_PTN1                ( CAN_TB_u4CmNCFG( 500K_10M_PTN1 ) )
#define CAN_TB_500K_10M_PTN2                ( CAN_TB_u4CmNCFG( 500K_10M_PTN2 ) )
#define CAN_TB_500K_10M_PTN3                ( CAN_TB_u4CmNCFG( 500K_10M_PTN3 ) )
#define CAN_TB_500K_10M_PTN4                ( CAN_TB_u4CmNCFG( 500K_10M_PTN4 ) )
#define CAN_TB_500K_10M_PTN5                ( CAN_TB_u4CmNCFG( 500K_10M_PTN5 ) )
#define CAN_TB_500K_20M_PTN1                ( CAN_TB_u4CmNCFG( 500K_20M_PTN1 ) )
#define CAN_TB_500K_32M_PTN1                ( CAN_TB_u4CmNCFG( 500K_32M_PTN1 ) )
#define CAN_TB_500K_40M_PTN1                ( CAN_TB_u4CmNCFG( 500K_40M_PTN1 ) )
#define CAN_TB_500K_40M_PTN2                ( CAN_TB_u4CmNCFG( 500K_40M_PTN2 ) )
#define CAN_TB_500K_80M_PTN1                ( CAN_TB_u4CmNCFG( 500K_80M_PTN1 ) )


#define CAN_TB_PSG2_2M_20M_PTN1             (  2UL )
#define CAN_TB_PSG2_2M_32M_PTN1             (  3UL )
#define CAN_TB_PSG2_2M_40M_PTN1             (  4UL )
#define CAN_TB_PSG2_2M_40M_PTN2             (  6UL )
#define CAN_TB_PSG2_2M_80M_PTN1             ( 12UL )
#define CAN_TB_PSG2_5M_80M_PTN1             (  5UL )

#define CAN_TB_PRP_PSG1_2M_20M_PTN1         (  7UL )
#define CAN_TB_PRP_PSG1_2M_32M_PTN1         ( 12UL )
#define CAN_TB_PRP_PSG1_2M_40M_PTN1         ( 15UL )
#define CAN_TB_PRP_PSG1_2M_40M_PTN2         ( 13UL )
#define CAN_TB_PRP_PSG1_2M_80M_PTN1         ( 27UL )
#define CAN_TB_PRP_PSG1_5M_80M_PTN1         ( 10UL )

#define CAN_TB_SJW_2M_20M_PTN1              (  2UL )
#define CAN_TB_SJW_2M_32M_PTN1              (  2UL )
#define CAN_TB_SJW_2M_40M_PTN1              (  3UL )
#define CAN_TB_SJW_2M_40M_PTN2              (  6UL )
#define CAN_TB_SJW_2M_80M_PTN1              ( 12UL )
#define CAN_TB_SJW_5M_80M_PTN1              (  5UL )

#define CAN_TB_CLK_FRQ_2M_20M_PTN1          ( 20000UL )
#define CAN_TB_CLK_FRQ_2M_32M_PTN1          ( 32000UL )
#define CAN_TB_CLK_FRQ_2M_40M_PTN1          ( 40000UL )
#define CAN_TB_CLK_FRQ_2M_40M_PTN2          ( 40000UL )
#define CAN_TB_CLK_FRQ_2M_80M_PTN1          ( 80000UL )
#define CAN_TB_CLK_FRQ_5M_80M_PTN1          ( 80000UL )

#define CAN_TB_u4CmDCFG_DBRP_PLUS1( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( CAN_TB_CAN_CLK_KHZ / CAN_TB_CLK_FRQ( ptn ) ) : 1UL )
#define CAN_TB_u4CmDCFG_DBRP( ptn )        ( CAN_TB_u4CmDCFG_DBRP_PLUS1( ptn ) - 1UL )

#define CAN_TB_u4CmDCFG_DTSEG1( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_PRP_PSG1_##ptn - 1UL ) : 0UL )

#define CAN_TB_u4CmDCFG_DTSEG2( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn ) == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_PSG2_##ptn - 1UL ) : 0UL )

#define CAN_TB_u4CmDCFG_DSJW( ptn ) \
    ( ( CAN_TB_CHK_BAUDRATE_CLK_ENABLE( ptn )  == CAN_TB_BAUDRATE_ENABLE ) ? (uint32)( (uint32)CAN_TB_SJW_##ptn - 1UL ) : 0UL )

#define CAN_TB_CmDCFG_SFT_DSJW              ( 24U )
#define CAN_TB_CmDCFG_SFT_DTSEG2            ( 16U )
#define CAN_TB_CmDCFG_SFT_DTSEG1            (  8U )
#define CAN_TB_CmDCFG_SFT_DBRP              (  0U )
#define CAN_TB_u4CmDCFG_BIT_DSJW            ( 0x0F000000UL )
#define CAN_TB_u4CmDCFG_BIT_DTSEG2          ( 0x000F0000UL )
#define CAN_TB_u4CmDCFG_BIT_DTSEG1          ( 0x00001F00UL )
#define CAN_TB_u4CmDCFG_BIT_DBRP            ( 0x000000FFUL )

#define CAN_TB_u4CmDCFG( ptn ) \
    ( (((uint32)CAN_TB_u4CmDCFG_DBRP( ptn )   << CAN_TB_CmDCFG_SFT_DBRP)   & CAN_TB_u4CmDCFG_BIT_DBRP   ) \
    | (((uint32)CAN_TB_u4CmDCFG_DTSEG1( ptn ) << CAN_TB_CmDCFG_SFT_DTSEG1) & CAN_TB_u4CmDCFG_BIT_DTSEG1 ) \
    | (((uint32)CAN_TB_u4CmDCFG_DTSEG2( ptn ) << CAN_TB_CmDCFG_SFT_DTSEG2) & CAN_TB_u4CmDCFG_BIT_DTSEG2 ) \
    | (((uint32)CAN_TB_u4CmDCFG_DSJW( ptn )   << CAN_TB_CmDCFG_SFT_DSJW)   & CAN_TB_u4CmDCFG_BIT_DSJW   ) )

#define CAN_TB_USER_DATABAUDRATE            ( 0xFFFFFFFFUL )
#define CAN_TB_DB_125K_2M_PTN1              ( CAN_TB_u4CmDCFG( 125K_2M_PTN1   ) )
#define CAN_TB_DB_125K_2P5M_PTN1            ( CAN_TB_u4CmDCFG( 125K_2P5M_PTN1 ) )
#define CAN_TB_DB_250K_4M_PTN1              ( CAN_TB_u4CmDCFG( 250K_4M_PTN1   ) )
#define CAN_TB_DB_250K_4M_PTN2              ( CAN_TB_u4CmDCFG( 250K_4M_PTN2   ) )
#define CAN_TB_DB_250K_5M_PTN1              ( CAN_TB_u4CmDCFG( 250K_5M_PTN1   ) )
#define CAN_TB_DB_250K_5M_PTN2              ( CAN_TB_u4CmDCFG( 250K_5M_PTN2   ) )
#define CAN_TB_DB_500K_8M_PTN1              ( CAN_TB_u4CmDCFG( 500K_8M_PTN1   ) )
#define CAN_TB_DB_500K_8M_PTN2              ( CAN_TB_u4CmDCFG( 500K_8M_PTN2   ) )
#define CAN_TB_DB_500K_8M_PTN3              ( CAN_TB_u4CmDCFG( 500K_8M_PTN3   ) )
#define CAN_TB_DB_500K_8M_PTN4              ( CAN_TB_u4CmDCFG( 500K_8M_PTN4   ) )
#define CAN_TB_DB_500K_8M_PTN5              ( CAN_TB_u4CmDCFG( 500K_8M_PTN5   ) )
#define CAN_TB_DB_500K_10M_PTN1             ( CAN_TB_u4CmDCFG( 500K_10M_PTN1  ) )
#define CAN_TB_DB_500K_10M_PTN2             ( CAN_TB_u4CmDCFG( 500K_10M_PTN2  ) )
#define CAN_TB_DB_500K_10M_PTN3             ( CAN_TB_u4CmDCFG( 500K_10M_PTN3  ) )
#define CAN_TB_DB_500K_10M_PTN4             ( CAN_TB_u4CmDCFG( 500K_10M_PTN4  ) )
#define CAN_TB_DB_500K_10M_PTN5             ( CAN_TB_u4CmDCFG( 500K_10M_PTN5  ) )
#define CAN_TB_DB_500K_20M_PTN1             ( CAN_TB_u4CmDCFG( 500K_20M_PTN1  ) )
#define CAN_TB_DB_500K_32M_PTN1             ( CAN_TB_u4CmDCFG( 500K_32M_PTN1  ) )
#define CAN_TB_DB_500K_40M_PTN1             ( CAN_TB_u4CmDCFG( 500K_40M_PTN1  ) )
#define CAN_TB_DB_500K_40M_PTN2             ( CAN_TB_u4CmDCFG( 500K_40M_PTN2  ) )
#define CAN_TB_DB_500K_80M_PTN1             ( CAN_TB_u4CmDCFG( 500K_80M_PTN1  ) )
#define CAN_TB_DB_2M_20M_PTN1               ( CAN_TB_u4CmDCFG( 2M_20M_PTN1    ) )
#define CAN_TB_DB_2M_32M_PTN1               ( CAN_TB_u4CmDCFG( 2M_32M_PTN1    ) )
#define CAN_TB_DB_2M_40M_PTN1               ( CAN_TB_u4CmDCFG( 2M_40M_PTN1    ) )
#define CAN_TB_DB_2M_40M_PTN2               ( CAN_TB_u4CmDCFG( 2M_40M_PTN2    ) )
#define CAN_TB_DB_2M_80M_PTN1               ( CAN_TB_u4CmDCFG( 2M_80M_PTN1    ) )
#define CAN_TB_DB_5M_80M_PTN1               ( CAN_TB_u4CmDCFG( 5M_80M_PTN1    ) )


#define CAN_TB_CMFDCFG_SFT_TDCO             ( 16U )

#define CAN_TB_u4TDCO_VAL( ptn )            ( (uint32)( ( (uint32)( 1UL + ( CAN_TB_u4CmDCFG_DTSEG1( ptn ) + 1UL ) ) * ( CAN_TB_u4CmDCFG_DBRP( ptn ) + 1UL ) ) - 1UL ) )
#define CAN_TB_u4TDCO( ptn )                ( (uint32)( CAN_TB_u4TDCO_VAL(ptn) << CAN_TB_CMFDCFG_SFT_TDCO ) & CAN_u4CMFDCFG_TDCO_MSK )

#define CAN_TB_SSPOFFSET_NOUSE              ( 0x00000000UL )
#define CAN_TB_SSPOFFSET_2M_20M_PTN1        ( CAN_TB_u4TDCO( 2M_20M_PTN1 ) )
#define CAN_TB_SSPOFFSET_2M_32M_PTN1        ( CAN_TB_u4TDCO( 2M_32M_PTN1 ) )
#define CAN_TB_SSPOFFSET_2M_40M_PTN1        ( CAN_TB_u4TDCO( 2M_40M_PTN1 ) )
#define CAN_TB_SSPOFFSET_2M_40M_PTN2        ( CAN_TB_u4TDCO( 2M_40M_PTN2 ) )
#define CAN_TB_SSPOFFSET_2M_80M_PTN1        ( CAN_TB_u4TDCO( 2M_80M_PTN1 ) )
#define CAN_TB_SSPOFFSET_5M_80M_PTN1        ( CAN_TB_u4TDCO( 5M_80M_PTN1 ) )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint16 u2RxRuleOffSetId;
    uint8  u1RxRuleUseNum;
    uint8  u1CtrlAct;
    uint8  u1CtrlUse;
    uint8  u1CtrlOpeMode;
} CanTbCtrlInfoType;

typedef struct
{
    uint8  u1TxMbNum;
} CanTbMbNumType;

typedef struct
{
    uint32 u4TxIntrBit[ CAN_TB_TXMBSIZE ];
    uint32 u4TxPollBit[ CAN_TB_TXMBSIZE ];
} CanTbTxMbBitType;

typedef struct
{
    volatile uint32 u4GAFLID;
    volatile uint32 u4GAFLM;
    volatile uint32 u4GAFLP0;
    volatile uint32 u4GAFLP1;
} CanTbRegRxRuleType;

typedef struct
{
    volatile uint32 u4GPFLID;
    volatile uint32 u4GPFLM;
    volatile uint32 u4GPFLP0;
    volatile uint32 u4GPFLP1;
    volatile uint32 u4GPFLPT;
    volatile uint32 u4GPFLPD0;
    volatile uint32 u4GPFLPM0;
    volatile uint32 u4GPFLPD1;
    volatile uint32 u4GPFLPM1;
    volatile uint32 u4RegPad[ CAN_TB_PFL_REG_RSV ];
} CanTbRegPFLType;

typedef struct
{
    volatile uint32 u4IDReg;
    volatile uint32 u4PTRReg;
    volatile uint32 u4FDSTSReg;
    volatile uint32 u4DFReg[ CAN_TB_MB_DATA_ARYSIZE ];
    volatile uint32 u4RegPad[ CAN_TB_MB_REG_RSV ];
} CanTbRegCANRMType;

typedef struct
{
    volatile uint32 u4IDReg;
    volatile uint32 u4PTRReg;
    volatile uint32 u4FDSTSReg;
    volatile uint32 u4DFReg [ CAN_TB_MB_DATA_ARYSIZE ];
    volatile uint32 u4RegPad[ CAN_TB_MB_REG_RSV ];
} CanTbRegCANRFType;

typedef struct
{
    volatile uint32 u4IDReg;
    volatile uint32 u4PTRReg;
    volatile uint32 u4FDCTRReg;
    volatile uint32 u4DFReg[ CAN_TB_MB_DATA_ARYSIZE ];
    volatile uint32 u4RegPad[ CAN_TB_MB_REG_RSV ];
} CanTbRegCANTMType;

typedef struct
{
    volatile uint32 u4IDReg;
    volatile uint32 u4PTRReg;
    volatile uint32 u4FDCSTSReg;
    volatile uint32 u4DFReg [ CAN_TB_MB_DATA_ARYSIZE ];
    volatile uint32 u4RegPad[ CAN_TB_MB_REG_RSV ];
} CanTbRegCANCFType;

typedef struct
{
    volatile uint32 *                CanConst ptu4CmNCFG;
    volatile uint32 *                CanConst ptu4CmCTR;
    volatile uint32 *                CanConst ptu4CmSTS;
    volatile uint32 *                CanConst ptu4CmERFL;
    volatile uint32 *                CanConst ptu4CFCC;
    volatile uint32 *                CanConst ptu4CFCCE;
    volatile uint32 *                CanConst ptu4CFSTS;
    volatile uint32 *                CanConst ptu4CFPCTR;
    volatile uint8  *                CanConst ptu1TMC;
    volatile uint8  *                CanConst ptu1TMSTS;
    volatile uint32 *                CanConst ptu4TMTRSTS;
    volatile uint32 *                CanConst ptu4TMTARSTS;
    volatile uint32 *                CanConst ptu4TMTCSTS;
    volatile uint32 *                CanConst ptu4TMTASTS;
    volatile uint32 *                CanConst ptu4TMIEC;
    volatile uint32 *                CanConst ptu4TXQCC0;
    volatile uint32 *                CanConst ptu4TXQSTS0;
    volatile uint32 *                CanConst ptu4TXQPCTR0;
    volatile uint32 *                CanConst ptu4TXQCC1;
    volatile uint32 *                CanConst ptu4TXQSTS1;
    volatile uint32 *                CanConst ptu4TXQPCTR1;
    volatile uint32 *                CanConst ptu4TXQCC2;
    volatile uint32 *                CanConst ptu4TXQSTS2;
    volatile uint32 *                CanConst ptu4TXQPCTR2;
    volatile uint32 *                CanConst ptu4TXQCC3;
    volatile uint32 *                CanConst ptu4TXQSTS3;
    volatile uint32 *                CanConst ptu4TXQPCTR3;
    volatile uint32 *                CanConst ptu4THLCC;
    volatile uint32 *                CanConst ptu4THLSTS;
    volatile uint32 *                CanConst ptu4THLPCTR;
    volatile uint32 *                CanConst ptu4GRINTSTS;
    volatile uint32 *                CanConst ptu4VMCFG;
    volatile uint32 *                CanConst ptu4VMISTS;
    volatile uint32 *                CanConst ptu4CmDCFG;
    volatile uint32 *                CanConst ptu4CmFDCFG;
    volatile uint32 *                CanConst ptu4CmFDCTR;
    volatile uint32 *                CanConst ptu4CmFDSTS;
    volatile uint32 *                CanConst ptu4CmFDCRC;
    volatile uint32 *                CanConst ptu4CmBLCT;
    volatile uint32 *                CanConst ptu4CmBLSTS;
    volatile uint32 *                CanConst ptu4THLACC0;
    volatile uint32 *                CanConst ptu4THLACC1;
    volatile CanTbRegCANCFType *     CanConst ptstCF;
    volatile CanTbRegCANTMType *     CanConst ptstTM;
} CanTbChRegType;

typedef struct
{
    volatile uint32 *                CanConst ptu4GIPV;
    volatile uint32 *                CanConst ptu4GCFG;
    volatile uint32 *                CanConst ptu4GCTR;
    volatile uint32 *                CanConst ptu4GSTS;
    volatile uint32 *                CanConst ptu4GERFL;
    volatile uint32 *                CanConst ptu4GTSC;
    volatile uint32 *                CanConst ptu4GAFLECTR;
    volatile uint32 *                CanConst ptu4GAFLCFG;
    volatile uint32 *                CanConst ptu4RMNB;
    volatile uint32 *                CanConst ptu4RMND;
    volatile uint32 *                CanConst ptu4RFCC;
    volatile uint32 *                CanConst ptu4RFSTS;
    volatile uint32 *                CanConst ptu4RFPCTR;
    volatile uint32 *                CanConst ptu4FESTS;
    volatile uint32 *                CanConst ptu4FFSTS;
    volatile uint32 *                CanConst ptu4FMSTS;
    volatile uint32 *                CanConst ptu4RFISTS;
    volatile uint32 *                CanConst ptu4CFRISTS;
    volatile uint32 *                CanConst ptu4CFTISTS;
    volatile uint32 *                CanConst ptu4CFOFRISTS;
    volatile uint32 *                CanConst ptu4CFOFTISTS;
    volatile uint32 *                CanConst ptu4CFMOWSTS;
    volatile uint32 *                CanConst ptu4FFFSTS;
    volatile uint32 *                CanConst ptu4TXQESTS;
    volatile uint32 *                CanConst ptu4TXQFISTS;
    volatile uint32 *                CanConst ptu4TXQMSTS;
    volatile uint32 *                CanConst ptu4TXQOWSTS;
    volatile uint32 *                CanConst ptu4TXQISTS;
    volatile uint32 *                CanConst ptu4TXQOFTISTS;
    volatile uint32 *                CanConst ptu4TXQOFRISTS;
    volatile uint32 *                CanConst ptu4TXQFSTS;
    volatile uint32 *                CanConst ptu4GTINTSTS;
    volatile uint32 *                CanConst ptu4GTSTCFG;
    volatile uint32 *                CanConst ptu4GTSTCTR;
    volatile uint32 *                CanConst ptu4GFDCFG;
    volatile uint32 *                CanConst ptu4GLOCKK;
    volatile uint32 *                CanConst ptu4GAFLIGNENT;
    volatile uint32 *                CanConst ptu4GAFLIGNCTR;
    volatile uint32 *                CanConst ptu4CDTCT;
    volatile uint32 *                CanConst ptu4CDTSTS;
    volatile uint32 *                CanConst ptu4CDTTCT;
    volatile uint32 *                CanConst ptu4CDTTSTS;
    volatile uint32 *                CanConst ptu4GPFLECTR;
    volatile uint32 *                CanConst ptu4GPFLCFG;
    volatile uint32 *                CanConst ptu4GRSTC;
    volatile uint32 *                CanConst ptu4GFCMC;
    volatile uint32 *                CanConst ptu4GFTBAC;
    volatile uint32 *                CanConst ptu4GFFIMC;
    volatile uint32 *                CanConst ptu4GVMEIS;
    volatile uint32 *                CanConst ptu4VMRFCFG;
    volatile CanTbRegRxRuleType *    CanConst ptstGAFL;
    volatile CanTbRegPFLType *       CanConst ptstGPFL;
    volatile uint32 *                CanConst ptu4RPGACC;
    volatile CanTbRegCANRMType *     CanConst ptstRM;
    volatile CanTbRegCANRFType *     CanConst ptstRF;
} CanTbGlobalRegType;

typedef struct
{
    uint16 u2StChkStart;
    uint16 u2StChkPage;
} CanTbCheckStuckParaType;

typedef struct
{
    uint32 u4GAFLIDConf;
    uint32 u4GAFLP0Conf;
    uint32 u4GAFLP1Conf;
    uint8  u1RxMaskRef;
} CanTbRxRuleSettingType;

typedef struct
{
    uint32 u4CFCC0Conf;
    uint32 u4CFCC1Conf;
    uint32 u4CFCC2Conf;
    uint32 u4CmNCFGConf;
    uint32 u4CmCTRConf;
    uint32 u4CFSTSConf;
    uint32 u4CmDCFGConf;
    uint32 u4CmFDCFGConf;
    uint32 u4TMFDCTRConf;
} CanTbSetRSCANRegType;

typedef struct
{
    uint32 u4Baudrate;
    uint32 u4DataBaudrate;
    uint32 u4BaudrateInfo_1;
    uint32 u4BaudrateInfo_2;
    uint32 u4BaudrateInfo_3;
} CanBaudrateSwtCfgType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void Can_tb_Interrupt( void );

void Can_tb_SYNCP( void );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern CanConst CanTbCtrlInfoType Can_tb_stCtrlInfo[ CAN_CFG_CONTROLLERNUM_MAX ];

extern CanConst CanTbMbNumType Can_tb_stMbNum[ CAN_CFG_CONTROLLERNUM_MAX ];

extern CanConst CanTbTxMbBitType Can_tb_stTxMbBit[ CAN_CFG_CONTROLLERNUM_MAX ];

extern CanConst uint32 Can_tb_u4RxMask[ CAN_TB_RXMKTBLSIZE ];

extern CanConst CanTbCheckStuckParaType Can_tb_stCheckStuckPara[ CAN_CFG_CHKSTKREG_LIMIT ];

extern CanConst CanTbRxRuleSettingType Can_tb_stRxRuleSetting[ CAN_TB_RXRULESETTBLSIZE ];

extern CanConst CanTbChRegType Can_tb_stChReg[ CAN_CFG_CONTROLLERNUM_MAX ];

extern CanConst CanTbGlobalRegType  Can_tb_stGlobalReg;

extern CanConst CanTbSetRSCANRegType Can_tb_stSetRSCANReg[ CAN_CFG_CONTROLLERNUM_MAX ];

extern CanConst uint8 Can_tb_u1BRSInitConf[ CAN_CFG_CONTROLLERNUM_MAX ];

extern CanConst CanBaudrateSwtCfgType Can_stBaudrateSwtCfgTbl[ CAN_CFG_BRSCFGTBL_SIZE ];

extern CanConst uint8 Can_stBRSwtCfgTbl_ARYSIZE;

extern CanConst CanBaudrateSwtCfgType * CanConst Can_tb_ptBaudrateSwtCfgTbl;

extern CanConst uint8 * CanConst Can_tb_ptBRSwtCfgTbl_ARYSIZE;

extern CanConst uint32 Can_tb_u4RAMInitCycleMax;

extern CanConst uint16 Can_tb_u2CmodeRst2ComWaitCnt;
extern CanConst uint16 Can_tb_u2CmodeAny2RstWaitCnt;
extern CanConst uint16 Can_tb_u2GmodeAny2RstWaitCnt;

extern CanConst uint8 Can_tb_u1CtrlNum;

extern CanConst uint16 Can_tb_u2MaxNumRxRule;

extern CanConst uint8 Can_tb_u1RxRulePageNum;

extern CanConst uint16 Can_tb_u2LastTestpage;

extern CanConst uint8 Can_tb_u1LastTestpageRegNum;

extern CanConst uint32 Can_tb_u4GAFLCFG0Conf;
extern CanConst uint32 Can_tb_u4GAFLCFG1Conf;
extern CanConst uint32 Can_tb_u4GAFLCFG2Conf;
extern CanConst uint32 Can_tb_u4GAFLCFG3Conf;

extern CanConst uint32 Can_tb_u4GCFGConf;

extern CanConst uint32 Can_tb_u4GFDCFGConf;


#endif  /* CAN_RSCF41_TB_PHY_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-1         :2022/05/25                                              */
/*  v2-2-2         :2023/04/17                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
