/* Dma-r04-3000-0100-a-v01 */
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
    (U2)DMA_UCFG_CHDATA##id##_HWCH,                         \
    (U2)DMA_UCFG_CHDATA##id##_REQ,                          \
    (U1)DMA_UCFG_CHDATA##id##_TYPE,                         \
    (U1)DMA_UCFG_CHDATA##id##_PRILEVEL                      \
}

#define DMA_GetNotificationDataType(id)   (&stDma_Notification[id])
/*==============================================================================================*/
/*  variables                                                                                   */
/*==============================================================================================*/
#define DMA_START_SEC_BSS_VAR_NO_INIT
#include "Dma_MemMap.h"
#if (DMA_UCFG_CHDATA_NUM > 0U)
Dma_ChannelDataType		stDma_Notification[DMA_UCFG_CHDATA_NUM]          __attribute__((section(".bss_SHARE_DMA_NOTICATION")));
#else
Dma_ChannelDataType		stDma_Notification[1]                            __attribute__((section(".bss_SHARE_DMA_NOTICATION")));
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
 const   Dma_ChDataDefType   cstDma_UcfgChData[DMA_UCFG_CHDATA_NUM] = {
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
const   Dma_ChDataDefType   cstDma_UcfgChData[1] = {
    {
        NULL_PTR, 
        (Dma_ChannelDataType*) &stDma_Notification[0],
        (U2)0x0000,
        (U2)0x0000,
        (U1)0x00,
        (U1)0x00
    }
};
#endif

const   Dma_UserConfigType  cstDma_UcfgData =
{
    &cstDma_UcfgChData[0],
    (U1)DMA_UCFG_CHDATA_NUM
};

#define DMA_STOP_SEC_RODATA_CONST
#include "Dma_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
