/* Dma-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*                                                                                              */
/*      DMA User Configuration                                                                  */
/*                                                                                              */
/*      Copyright : DENSO CORPORATION                                                           */
/*                                                                                              */
/************************************************************************************************/

/*==============================================================================================*/
/*  include files                                                                               */
/*==============================================================================================*/
#include	"Dma.h"
#include	"pil_dmac.h"
#include	"pil_dts.h"

/*==============================================================================================*/
/*  defines / data types / structs / unions / macros                                            */
/*==============================================================================================*/

#define     Dma_SetChDataConfig(id)                         \
{                                                           \
    DMA_UCFG_CHDATA##id##_NOTIFICATION,                     \
    (Dma_ChannelDataType*)DMA_GetNotificationDataType(id),  \
    (uint16)DMA_UCFG_CHDATA##id##_HWCH,                     \
    (uint16)DMA_UCFG_CHDATA##id##_REQ,                      \
    (uint8)DMA_UCFG_CHDATA##id##_TYPE,                      \
    (uint8)DMA_UCFG_CHDATA##id##_PRILEVEL                   \
}

#define DMA_GetNotificationDataType(id)   (&stDma_Notification[id])

#define		PIL_DMA_DTS_SPIDNUM			((uint8)29U)					/* DTS SPID value 29 fixed   */
#define		PIL_DMA_DMAC0_SPIDNUM		((uint8)28U)					/* DMAC0 SPID value 28 fixed */
#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
#define		PIL_DMA_DMAC1_SPIDNUM		((uint8)27U)					/* DMAC1 SPID value 27 fixed */ 
#endif
/*==============================================================================================*/
/*  variables                                                                                   */
/*==============================================================================================*/
#define DMA_START_SEC_BSS_VAR_NO_INIT
#include "Dma_MemMap.h"
#if (DMA_UCFG_CHDATA_NUM > 0U)
static Dma_ChannelDataType		stDma_Notification[DMA_UCFG_CHDATA_NUM];
#else
static Dma_ChannelDataType		stDma_Notification[1];
#endif

#define DMA_STOP_SEC_BSS_VAR_NO_INIT
#include "Dma_MemMap.h"

/*==============================================================================================*/
/*  constants                                                                                   */
/*==============================================================================================*/
#define DMA_START_SEC_RODATA_CONST
#include "Dma_MemMap.h"

/* DMA configuration settings */
#if ( DMA_UCFG_CHDATA_NUM > 0U )
 static   const   Dma_ChDataDefType   cstDma_UcfgChData[DMA_UCFG_CHDATA_NUM] = {
    Dma_SetChDataConfig(0)
  #if ( DMA_UCFG_CHDATA_NUM > 1U )
      ,Dma_SetChDataConfig(1)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 2U )
      ,Dma_SetChDataConfig(2)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 3U )
      ,Dma_SetChDataConfig(3)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 4U )
      ,Dma_SetChDataConfig(4)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 5U )
      ,Dma_SetChDataConfig(5)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 6U )
      ,Dma_SetChDataConfig(6)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 7U )
      ,Dma_SetChDataConfig(7)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 8U )
      ,Dma_SetChDataConfig(8)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 9U )
      ,Dma_SetChDataConfig(9)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 10U )
      ,Dma_SetChDataConfig(10)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 11U )
      ,Dma_SetChDataConfig(11)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 12U )
      ,Dma_SetChDataConfig(12)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 13U )
      ,Dma_SetChDataConfig(13)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 14U )
      ,Dma_SetChDataConfig(14)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 15U )
      ,Dma_SetChDataConfig(15)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 16U )
      ,Dma_SetChDataConfig(16)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 17U )
      ,Dma_SetChDataConfig(17)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 18U )
      ,Dma_SetChDataConfig(18)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 19U )
      ,Dma_SetChDataConfig(19)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 20U )
      ,Dma_SetChDataConfig(20)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 21U )
      ,Dma_SetChDataConfig(21)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 22U )
      ,Dma_SetChDataConfig(22)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 23U )
      ,Dma_SetChDataConfig(23)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 24U )
      ,Dma_SetChDataConfig(24)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 25U )
      ,Dma_SetChDataConfig(25)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 26U )
      ,Dma_SetChDataConfig(26)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 27U )
      ,Dma_SetChDataConfig(27)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 28U )
      ,Dma_SetChDataConfig(28)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 29U )
      ,Dma_SetChDataConfig(29)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 30U )
      ,Dma_SetChDataConfig(30)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 31U )
      ,Dma_SetChDataConfig(31)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 32U )
      ,Dma_SetChDataConfig(32)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 33U )
      ,Dma_SetChDataConfig(33)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 34U )
      ,Dma_SetChDataConfig(34)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 35U )
      ,Dma_SetChDataConfig(35)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 36U )
      ,Dma_SetChDataConfig(36)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 37U )
      ,Dma_SetChDataConfig(37)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 38U )
      ,Dma_SetChDataConfig(38)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 39U )
      ,Dma_SetChDataConfig(39)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 40U )
      ,Dma_SetChDataConfig(40)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 41U )
      ,Dma_SetChDataConfig(41)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 42U )
      ,Dma_SetChDataConfig(42)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 43U )
      ,Dma_SetChDataConfig(43)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 44U )
      ,Dma_SetChDataConfig(44)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 45U )
      ,Dma_SetChDataConfig(45)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 46U )
      ,Dma_SetChDataConfig(46)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 47U )
      ,Dma_SetChDataConfig(47)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 48U )
      ,Dma_SetChDataConfig(48)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 49U )
      ,Dma_SetChDataConfig(49)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 50U )
      ,Dma_SetChDataConfig(50)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 51U )
      ,Dma_SetChDataConfig(51)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 52U )
      ,Dma_SetChDataConfig(52)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 53U )
      ,Dma_SetChDataConfig(53)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 54U )
      ,Dma_SetChDataConfig(54)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 55U )
      ,Dma_SetChDataConfig(55)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 56U )
      ,Dma_SetChDataConfig(56)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 57U )
      ,Dma_SetChDataConfig(57)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 58U )
      ,Dma_SetChDataConfig(58)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 59U )
      ,Dma_SetChDataConfig(59)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 60U )
      ,Dma_SetChDataConfig(60)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 61U )
      ,Dma_SetChDataConfig(61)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 62U )
      ,Dma_SetChDataConfig(62)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 63U )
      ,Dma_SetChDataConfig(63)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 64U )
      ,Dma_SetChDataConfig(64)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 65U )
      ,Dma_SetChDataConfig(65)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 66U )
      ,Dma_SetChDataConfig(66)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 67U )
      ,Dma_SetChDataConfig(67)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 68U )
      ,Dma_SetChDataConfig(68)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 69U )
      ,Dma_SetChDataConfig(69)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 70U )
      ,Dma_SetChDataConfig(70)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 71U )
      ,Dma_SetChDataConfig(71)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 72U )
      ,Dma_SetChDataConfig(72)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 73U )
      ,Dma_SetChDataConfig(73)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 74U )
      ,Dma_SetChDataConfig(74)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 75U )
      ,Dma_SetChDataConfig(75)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 76U )
      ,Dma_SetChDataConfig(76)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 77U )
      ,Dma_SetChDataConfig(77)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 78U )
      ,Dma_SetChDataConfig(78)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 79U )
      ,Dma_SetChDataConfig(79)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 80U )
      ,Dma_SetChDataConfig(80)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 81U )
      ,Dma_SetChDataConfig(81)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 82U )
      ,Dma_SetChDataConfig(82)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 83U )
      ,Dma_SetChDataConfig(83)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 84U )
      ,Dma_SetChDataConfig(84)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 85U )
      ,Dma_SetChDataConfig(85)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 86U )
      ,Dma_SetChDataConfig(86)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 87U )
      ,Dma_SetChDataConfig(87)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 88U )
      ,Dma_SetChDataConfig(88)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 89U )
      ,Dma_SetChDataConfig(89)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 90U )
      ,Dma_SetChDataConfig(90)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 91U )
      ,Dma_SetChDataConfig(91)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 92U )
      ,Dma_SetChDataConfig(92)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 93U )
      ,Dma_SetChDataConfig(93)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 94U )
      ,Dma_SetChDataConfig(94)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 95U )
      ,Dma_SetChDataConfig(95)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 96U )
      ,Dma_SetChDataConfig(96)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 97U )
      ,Dma_SetChDataConfig(97)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 98U )
      ,Dma_SetChDataConfig(98)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 99U )
      ,Dma_SetChDataConfig(99)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 100U )
      ,Dma_SetChDataConfig(100)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 101U )
      ,Dma_SetChDataConfig(101)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 102U )
      ,Dma_SetChDataConfig(102)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 103U )
      ,Dma_SetChDataConfig(103)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 104U )
      ,Dma_SetChDataConfig(104)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 105U )
      ,Dma_SetChDataConfig(105)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 106U )
      ,Dma_SetChDataConfig(106)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 107U )
      ,Dma_SetChDataConfig(107)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 108U )
      ,Dma_SetChDataConfig(108)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 109U )
      ,Dma_SetChDataConfig(109)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 110U )
      ,Dma_SetChDataConfig(110)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 111U )
      ,Dma_SetChDataConfig(111)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 112U )
      ,Dma_SetChDataConfig(112)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 113U )
      ,Dma_SetChDataConfig(113)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 114U )
      ,Dma_SetChDataConfig(114)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 115U )
      ,Dma_SetChDataConfig(115)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 116U )
      ,Dma_SetChDataConfig(116)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 117U )
      ,Dma_SetChDataConfig(117)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 118U )
      ,Dma_SetChDataConfig(118)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 119U )
      ,Dma_SetChDataConfig(119)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 120U )
      ,Dma_SetChDataConfig(120)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 121U )
      ,Dma_SetChDataConfig(121)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 122U )
      ,Dma_SetChDataConfig(122)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 123U )
      ,Dma_SetChDataConfig(123)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 124U )
      ,Dma_SetChDataConfig(124)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 125U )
      ,Dma_SetChDataConfig(125)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 126U )
      ,Dma_SetChDataConfig(126)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 127U )
      ,Dma_SetChDataConfig(127)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 128U )
      ,Dma_SetChDataConfig(128)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 129U )
      ,Dma_SetChDataConfig(129)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 130U )
      ,Dma_SetChDataConfig(130)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 131U )
      ,Dma_SetChDataConfig(131)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 132U )
      ,Dma_SetChDataConfig(132)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 133U )
      ,Dma_SetChDataConfig(133)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 134U )
      ,Dma_SetChDataConfig(134)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 135U )
      ,Dma_SetChDataConfig(135)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 136U )
      ,Dma_SetChDataConfig(136)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 137U )
      ,Dma_SetChDataConfig(137)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 138U )
      ,Dma_SetChDataConfig(138)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 139U )
      ,Dma_SetChDataConfig(139)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 140U )
      ,Dma_SetChDataConfig(140)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 141U )
      ,Dma_SetChDataConfig(141)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 142U )
      ,Dma_SetChDataConfig(142)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 143U )
      ,Dma_SetChDataConfig(143)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 144U )
      ,Dma_SetChDataConfig(144)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 145U )
      ,Dma_SetChDataConfig(145)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 146U )
      ,Dma_SetChDataConfig(146)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 147U )
      ,Dma_SetChDataConfig(147)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 148U )
      ,Dma_SetChDataConfig(148)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 149U )
      ,Dma_SetChDataConfig(149)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 150U )
      ,Dma_SetChDataConfig(150)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 151U )
      ,Dma_SetChDataConfig(151)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 152U )
      ,Dma_SetChDataConfig(152)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 153U )
      ,Dma_SetChDataConfig(153)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 154U )
      ,Dma_SetChDataConfig(154)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 155U )
      ,Dma_SetChDataConfig(155)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 156U )
      ,Dma_SetChDataConfig(156)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 157U )
      ,Dma_SetChDataConfig(157)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 158U )
      ,Dma_SetChDataConfig(158)
  #endif
  #if ( DMA_UCFG_CHDATA_NUM > 159U )
      ,Dma_SetChDataConfig(159)
  #endif
 };
#else
static   const   Dma_ChDataDefType   cstDma_UcfgChData[1] = {
    {
        NULL_PTR, 
        (Dma_ChannelDataType*) &stDma_Notification[0],
        (uint16)0x0000,
        (uint16)0x0000,
        (uint8)0x00,
        (uint8)0x00
    }
};
#endif

const   Dma_UserConfigType  cstDma_UcfgData =
{
    &cstDma_UcfgChData[0],
    (uint8)DMA_UCFG_CHDATA_NUM
};

/*  SPID table for DTS channels */
#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
const   uint8   cu1Pil_Dma_Ucfg_Dts_ChSpidTable[DMA_DTS_CH_NUM] ={
		#ifdef PIL_DMA_UCFG_DTS_CH0_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH0_SPID,
		#else
		    PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH1_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH1_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH2_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH2_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH3_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH3_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH4_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH4_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH5_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH5_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH6_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH6_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH7_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH7_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH8_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH8_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH9_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH9_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH10_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH10_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH11_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH11_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH12_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH12_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH13_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH13_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH14_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH14_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH15_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH15_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH16_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH16_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH17_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH17_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH18_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH18_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH19_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH19_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH20_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH20_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH21_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH21_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH22_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH22_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH23_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH23_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH24_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH24_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH25_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH25_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH26_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH26_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH27_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH27_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH28_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH28_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH29_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH29_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH30_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH30_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH31_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH31_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH32_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH32_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH33_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH33_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH34_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH34_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH35_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH35_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH36_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH36_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH37_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH37_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH38_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH38_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH39_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH39_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH40_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH40_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH41_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH41_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH42_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH42_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH43_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH43_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH44_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH44_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH45_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH45_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH46_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH46_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH47_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH47_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH48_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH48_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH49_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH49_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH50_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH50_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH51_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH51_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH52_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH52_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH53_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH53_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH54_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH54_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH55_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH55_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH56_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH56_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH57_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH57_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH58_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH58_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH59_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH59_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH60_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH60_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH61_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH61_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH62_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH62_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH63_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH63_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH64_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH64_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH65_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH65_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH66_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH66_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH67_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH67_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH68_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH68_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH69_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH69_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH70_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH70_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH71_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH71_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH72_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH72_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH73_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH73_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH74_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH74_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH75_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH75_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH76_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH76_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH77_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH77_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH78_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH78_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH79_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH79_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH80_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH80_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH81_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH81_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH82_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH82_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH83_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH83_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH84_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH84_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH85_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH85_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH86_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH86_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH87_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH87_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH88_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH88_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH89_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH89_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH90_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH90_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH91_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH91_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH92_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH92_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH93_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH93_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH94_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH94_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH95_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH95_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH96_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH96_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH97_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH97_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH98_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH98_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH99_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH99_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH100_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH100_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH101_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH101_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH102_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH102_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH103_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH103_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH104_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH104_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH105_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH105_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH106_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH106_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH107_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH107_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH108_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH108_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH109_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH109_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH110_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH110_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH111_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH111_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH112_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH112_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH113_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH113_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH114_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH114_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH115_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH115_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH116_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH116_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH117_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH117_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH118_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH118_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH119_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH119_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH120_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH120_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH121_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH121_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH122_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH122_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH123_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH123_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH124_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH124_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH125_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH125_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH126_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH126_SPID,
		#else
			PIL_DMA_DTS_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DTS_CH127_SPID
			(uint8)PIL_DMA_UCFG_DTS_CH127_SPID
		#else
			PIL_DMA_DTS_SPIDNUM
		#endif		
};
#endif
/*  SPID table for DMAC0 channels */
#if ( DMA_CFG_DMA0_ACCESS == STD_ON )
const   uint8   cu1Pil_Dma_Ucfg_Dmac0_ChSpidTable[DMA_DMAC_CH_NUM] ={
		#ifdef PIL_DMA_UCFG_DMAC0_CH0_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH0_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH1_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH1_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH2_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH2_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH3_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH3_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH4_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH4_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH5_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH5_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH6_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH6_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH7_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH7_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH8_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH8_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH9_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH9_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH10_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH10_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH11_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH11_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH12_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH12_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH13_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH13_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH14_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH14_SPID,
		#else
			PIL_DMA_DMAC0_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC0_CH15_SPID
			(uint8)PIL_DMA_UCFG_DMAC0_CH15_SPID
		#else
			PIL_DMA_DMAC0_SPIDNUM
		#endif
};
#endif

#if ( DMA_CFG_DMA1_ACCESS == STD_ON )
#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
/*  SPID table for DMAC1 channels */
const   uint8   cu1Pil_Dma_Ucfg_Dmac1_ChSpidTable[DMA_DMAC_CH_NUM] ={
		#ifdef PIL_DMA_UCFG_DMAC1_CH0_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH0_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH1_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH1_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH2_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH2_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH3_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH3_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH4_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH4_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH5_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH5_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH6_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH6_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH7_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH7_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH8_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH8_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH9_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH9_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH10_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH10_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH11_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH11_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH12_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH12_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH13_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH13_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH14_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH14_SPID,
		#else
			PIL_DMA_DMAC1_SPIDNUM,
		#endif
		#ifdef PIL_DMA_UCFG_DMAC1_CH15_SPID
			(uint8)PIL_DMA_UCFG_DMAC1_CH15_SPID
		#else
			PIL_DMA_DMAC1_SPIDNUM
		#endif
};
#endif
#endif

#define DMA_STOP_SEC_RODATA_CONST
#include "Dma_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
