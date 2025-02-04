#include "dma_drv_channel_STUB.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  void    vd_g_DmaEnaCh(const U1 u1_a_DMA_CH, const U4 * u4_ap_CFG_CH)                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DMA_CFG_CH_NUM_WORD                      (8U)

#define DMA_CFG_CH_ADDR_SRC                      (0U)   /* DMAC Source Address Register (DSAn)              */
#define DMA_CFG_CH_ADDR_DST                      (1U)   /* DMAC Destination Address Register (DDAn)         */
#define DMA_CFG_CH_CTRL_DTC                      (2U)   /* DMAC Transfer Count Register (DTCn)              */
#define DMA_CFG_CH_CTRL_DTCT                     (3U)   /* DMAC Transfer Control Register (DTCTn)           */
#define DMA_CFG_CH_ADDR_RSRC                     (4U)   /* DMAC Reload Source Address Register (DRSAn)      */
#define DMA_CFG_CH_ADDR_RDST                     (5U)   /* DMAC Reload Destination Address Register (DRDAn) */
#define DMA_CFG_CH_CTRL_DRTC                     (6U)   /* DMAC Reload Transfer Count Register (DRTCn)      */
#define DMA_CFG_CH_CTRL_DTCC                     (7U)   /* DMAC Transfer Count Compare Register (DTCCn)     */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define DMA_CFG_CH_ADDR_SRC                      (0U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define DMA_CFG_CH_ADDR_DST                      (1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define DMA_CFG_CH_CTRL_DTC                      (2U) */
#define DMA_CTRL_DTC_LSB_ARC                     (16U)
#define DMA_CTRL_DTC_LSB_TRC                     (0U)

#define DMA_CTRL_DTC_ARC_FIELDS                  (0xffff0000U)
#define DMA_CTRL_DTC_TRC_FIELDS                  (0x0000ffffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define DMA_CFG_CH_CTRL_DTCT                     (3U) */
/* #define DMA_CTRL_DTCT_BIT_ERR_CONT            (0x00000000U) */ /* DMA DTCT : Transfer after error detect cycle     */
#define DMA_CTRL_DTCT_BIT_ERR_STOP               (0x08000000U)  /* DMA DTCT : Not executed after error detect cycle   */

#define DMA_CTRL_DTCT_BIT_ISEL_SW                (0x00000000U)  /* DMA DTCT : Input Select software                   */
#define DMA_CTRL_DTCT_BIT_ISEL_HW                (0x04000000U)  /* DMA DTCT : Input Select hardware                   */

#define DMA_CTRL_DTCT_BIT_IRQEN_CMPR             (0x00008000U)  /* DMA DTCT : Count match interrupt                   */
#define DMA_CTRL_DTCT_BIT_IRQEN_CMPLT            (0x00004000U)  /* DMA DTCT : Completion interrupt                    */
#define DMA_CTRL_DTCT_BIT_IRQEN                  (0x0000c000U)  /* DMA DTCT : Both interrupt                          */

/* #define DMA_CTRL_DTCT_BIT_TX_NOTCONT          (0x00000000U) */ /* DMA DTCT : Continuous transfer disabled          */
#define DMA_CTRL_DTCT_BIT_TX_CONT                (0x00002000U)  /* DMA DTCT : Continuous transfer                     */

/* #define DMA_CTRL_DTCT_BIT_RLD1_DSBL           (0x00000000U) */ /* DMA DTCT : Reload1 not used                      */
#define DMA_CTRL_DTCT_BIT_RLD1_SRC               (0x00000200U)  /* DMA DTCT : Reload1 used and source reloaded        */
#define DMA_CTRL_DTCT_BIT_RLD1_DST               (0x00000400U)  /* DMA DTCT : Reload1 used and destination reloaded   */
#define DMA_CTRL_DTCT_BIT_RLD1_BOTH              (0x00000600U)  /* DMA DTCT : Reload1 used and both addr. reloaded    */

/* #define DMA_CTRL_DTCT_BIT_RLD2_DSBL           (0x00000000U) */ /* DMA DTCT : Reload2 not used                      */
#define DMA_CTRL_DTCT_BIT_RLD2_SRC               (0x00000800U)  /* DMA DTCT : Reload2 used and source reloaded        */
#define DMA_CTRL_DTCT_BIT_RLD2_DST               (0x00001000U)  /* DMA DTCT : Reload2 used and destination reloaded   */
#define DMA_CTRL_DTCT_BIT_RLD2_BOTH              (0x00001800U)  /* DMA DTCT : Reload2 used and both addr. reloaded    */

#define DMA_CTRL_DTCT_BIT_DST_INC                (0x00000000U)  /* DMA DTCT : Destination is incremented              */
#define DMA_CTRL_DTCT_BIT_DST_DEC                (0x00000080U)  /* DMA DTCT : Destination is decremented              */
#define DMA_CTRL_DTCT_BIT_DST_FIX                (0x00000100U)  /* DMA DTCT : Destination is fixed                    */

#define DMA_CTRL_DTCT_BIT_SRC_INC                (0x00000000U)  /* DMA DTCT : Source is incremented                   */
#define DMA_CTRL_DTCT_BIT_SRC_DEC                (0x00000020U)  /* DMA DTCT : Source is decremented                   */
#define DMA_CTRL_DTCT_BIT_SRC_FIX                (0x00000040U)  /* DMA DTCT : Source is fixed                         */

#define DMA_CTRL_DTCT_BIT_TXW_BYTE               (0x00000000U)  /* DMA DTCT : Tx width = 1  byte                      */
#define DMA_CTRL_DTCT_BIT_TXW_HALF               (0x00000004U)  /* DMA DTCT : Tx width = 2  byte                      */
#define DMA_CTRL_DTCT_BIT_TXW_WORD               (0x00000008U)  /* DMA DTCT : Tx width = 4  byte                      */
#define DMA_CTRL_DTCT_BIT_TXW_DOUB               (0x0000000cU)  /* DMA DTCT : Tx width = 8  byte                      */
#define DMA_CTRL_DTCT_BIT_TXW_QUAD               (0x00000010U)  /* DMA DTCT : Tx width = 16 byte                      */

#define DMA_CTRL_DTCT_BIT_TX_SINGLE              (0x00000000U)  /* DMA DTCT : Single Transfer                         */
#define DMA_CTRL_DTCT_BIT_TX_BLOCK1              (0x00000001U)  /* DMA DTCT : Block1 Transfer                         */
#define DMA_CTRL_DTCT_BIT_TX_BLOCK2              (0x00000002U)  /* DMA DTCT : Block2 Transfer                         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define DMA_CFG_CH_ADDR_RSRC                     (4U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define DMA_CFG_CH_ADDR_RDST                     (5U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define DMA_CFG_CH_CTRL_DRTC                     (6U) */
/* #define DMA_CTRL_DRTC_LSB_RARC                   (16U)         same as DMA_CTRL_DTC_LSB_ARC    */
/* #define DMA_CTRL_DRTC_LSB_RTRC                   (0U)          same as DMA_CTRL_DTC_LSB_TRC    */

/* #define DMA_CTRL_DRTC_RARC_FIELDS                (0xffff0000U) same as DMA_CTRL_DTC_ARC_FIELDS */
/* #define DMA_CTRL_DRTC_RTRC_FIELDS                (0x0000ffffU) same as DMA_CTRL_DTC_TRC_FIELDS */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define DMA_CFG_CH_CTRL_DTCC                     (7U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  U4      u4_g_DmaStsfield(const U1 u1_a_DMA_CH, const U4 u4_a_W_CLRBIT)                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DMA_STSBIT_IRQST_TX_FAIL                 (0x00000080U)
#define DMA_STSBIT_IRQST_TX_CMPR                 (0x00000020U)
#define DMA_STSBIT_IRQST_TX_CMPLT                (0x00000010U)
#define DMA_STSBIT_IRQST_FIELDS                  (0x000000b0U)

#define DMA_STSBIT_ENA                           (0x80000000U)
#define DMA_STSBIT_HLT                           (0x40000000U)

#define DMA_STSBIT_SOFT_REQ                      (0x00000001U)
#define DMA_STSBIT_HARD_REQ                      (0x00000002U)

#define DMA_STSBIT_IRQEN_CMPR                    (0x00008000U)
#define DMA_STSBIT_IRQEN_CMPLT                   (0x00004000U)
#define DMA_STSBIT_RUN                           (0x00000100U)

#define DMA_STSBIT_UNKNWN                        (0x00000000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DMA_CLRBIT_NOTCLR                        (0x00000000U)
#define DMA_CLRBIT_SOFT_REQ                      (0x00000001U)
#define DMA_CLRBIT_HARD_REQ                      (0x00000002U)
#define DMA_CLRBIT_IRQST_CMPLT                   (0x00000010U)
#define DMA_CLRBIT_IRQST_CMPR                    (0x00000020U)
#define DMA_CLRBIT_IRQST_FAIL                    (0x00000080U)
#define DMA_CLRBIT_CLRALL                        (0x000000b3U)

