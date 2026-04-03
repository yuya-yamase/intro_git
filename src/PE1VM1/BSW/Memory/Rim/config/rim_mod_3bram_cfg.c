/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : MODULE_3BRAM                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_3BRAM_CFG_C_MAJOR                (1U)
#define RIM_MOD_3BRAM_CFG_C_MINOR                (3U)
#define RIM_MOD_3BRAM_CFG_C_PATCH                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "rim_ctl.h"

#include "rim_mod_3bram_private.h"
#include "rim_mod_3bram_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RIM_MOD_3BRAM_CFG_C_MAJOR != RIM_MOD_3BRAM_H_MAJOR) || \
     (RIM_MOD_3BRAM_CFG_C_MINOR != RIM_MOD_3BRAM_H_MINOR) || \
     (RIM_MOD_3BRAM_CFG_C_PATCH != RIM_MOD_3BRAM_H_PATCH))
#error "rim_mod_3bram_cfg.c and rim_mod_3bram_private.h : source and header files are inconsistent!"
#endif

#if ((RIM_MOD_3BRAM_CFG_C_MAJOR != RIM_MOD_3BRAM_CFG_PRIVATE_H_MAJOR) || \
     (RIM_MOD_3BRAM_CFG_C_MINOR != RIM_MOD_3BRAM_CFG_PRIVATE_H_MINOR) || \
     (RIM_MOD_3BRAM_CFG_C_PATCH != RIM_MOD_3BRAM_CFG_PRIVATE_H_PATCH))
#error "rim_mod_3bram_cfg.c and rim_mod_3bram_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* START : ##TOOL_OUT#RIM_MOD_3B_SIZE## */
#define RIM_MOD_3BRAM_U1_ID_NUM                  (269U)
#define RIM_MOD_3BRAM_U2_ID_NUM                  (21U)
#define RIM_MOD_3BRAM_U4_ID_NUM                  (111U)
#define RIM_MOD_3BRAM_OTHER_ID_NUM               (139U)
/* END : ##TOOL_OUT#RIM_MOD_3B_SIZE## */
/* START : ##TOOL_OUT#RIM_MOD_3B_OTR_TBL_SIZE## */
#define RIM_MOD_3BRAM_OTHER_BUF_NUM              (910U)
/* END : ##TOOL_OUT#RIM_MOD_3B_OTR_TBL_SIZE## */

/* Set st_d_RIM_MOD_3BRAM_OTR_SZ_CFG's max size */
/* START : ##TOOL_OUT#RIM_MOD_3B_OTR_SIZE_MAX## */
#define RIM_MOD_3BRAM_OTHER_ID_CFGMAX            (32U)
/* END : ##TOOL_OUT#RIM_MOD_3B_OTR_SIZE_MAX## */

#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
#if (RIM_MOD_3BRAM_OTHER_ID_CFGMAX > RIM_MOD_3BRAM_OTHER_ID_MAXBYTE)
#error "This buffer number isn't supported.Please contact BSW team."
#endif  /* #if (RIM_MOD_3BRAM_OTHER_ID_CFGMAX > RIM_MOD_3BRAM_OTHER_ID_MAXBYTE) */
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (__RIM_MOD_3BRAM_U1_USE__ == TRUE)
U1  u1_dp_rimmod_3b_byte_main[RIM_MOD_3BRAM_U1_ID_NUM]           __attribute__((section(".bss_BACK_RIM1")));
U1  u1_dp_rimmod_3b_byte_mirr1[RIM_MOD_3BRAM_U1_ID_NUM]          __attribute__((section(".bss_BACK_RIM2")));
U1  u1_dp_rimmod_3b_byte_mirr2[RIM_MOD_3BRAM_U1_ID_NUM]          __attribute__((section(".bss_BACK_RIM3")));
#endif  /* #if (__RIM_MOD_3BRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U2_USE__ == TRUE)
U2  u2_dp_rimmod_3b_half_main[RIM_MOD_3BRAM_U2_ID_NUM]           __attribute__((section(".bss_BACK_RIM1")));
U2  u2_dp_rimmod_3b_half_mirr1[RIM_MOD_3BRAM_U2_ID_NUM]          __attribute__((section(".bss_BACK_RIM2")));
U2  u2_dp_rimmod_3b_half_mirr2[RIM_MOD_3BRAM_U2_ID_NUM]          __attribute__((section(".bss_BACK_RIM3")));
#endif  /* #if (__RIM_MOD_3BRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U4_USE__ == TRUE)
U4  u4_dp_rimmod_3b_word_main[RIM_MOD_3BRAM_U4_ID_NUM]           __attribute__((section(".bss_BACK_RIM1")));
U4  u4_dp_rimmod_3b_word_mirr1[RIM_MOD_3BRAM_U4_ID_NUM]          __attribute__((section(".bss_BACK_RIM2")));
U4  u4_dp_rimmod_3b_word_mirr2[RIM_MOD_3BRAM_U4_ID_NUM]          __attribute__((section(".bss_BACK_RIM3")));
#endif  /* #if (__RIM_MOD_3BRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
U4  u4_dp_rimmod_3b_oth_main[RIM_MOD_3BRAM_OTHER_BUF_NUM]        __attribute__((section(".bss_BACK_RIM1")));
U4  u4_dp_rimmod_3b_oth_mirr1[RIM_MOD_3BRAM_OTHER_BUF_NUM]       __attribute__((section(".bss_BACK_RIM2")));
U4  u4_dp_rimmod_3b_oth_mirr2[RIM_MOD_3BRAM_OTHER_BUF_NUM]       __attribute__((section(".bss_BACK_RIM3")));

U4  u4_dp_rimmod_3b_oth_cs_main[RIM_MOD_3BRAM_OTHER_ID_NUM]      __attribute__((section(".bss_BACK_RIM1")));
U4  u4_dp_rimmod_3b_oth_cs_mirr1[RIM_MOD_3BRAM_OTHER_ID_NUM]     __attribute__((section(".bss_BACK_RIM2")));
U4  u4_dp_rimmod_3b_oth_cs_mirr2[RIM_MOD_3BRAM_OTHER_ID_NUM]     __attribute__((section(".bss_BACK_RIM3")));
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2 u2_d_RIM_MOD_3BRAM_MODULE_ID = (U2)RIM_MOD_ID_0;
const U2 u2_d_RIM_MOD_3BRAM_DATA_ID_MASK = (U2)0x01FFU;

#if (__RIM_MOD_3BRAM_U1_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3BRAM_U1_ID_NUM = (U2)RIM_MOD_3BRAM_U1_ID_NUM;
#endif  /* #if (__RIM_MOD_3BRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U2_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3BRAM_U2_ID_NUM = (U2)RIM_MOD_3BRAM_U2_ID_NUM;
#endif  /* #if (__RIM_MOD_3BRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U4_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3BRAM_U4_ID_NUM = (U2)RIM_MOD_3BRAM_U4_ID_NUM;
#endif  /* #if (__RIM_MOD_3BRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3BRAM_OTR_ID_NUM = (U2)RIM_MOD_3BRAM_OTHER_ID_NUM;

const ST_RIM_MOD_3BRAM_SIZE st_d_RIM_MOD_3BRAM_OTR_SZ_CFG[RIM_MOD_3BRAM_OTHER_ID_NUM] = {
/*  index           size    */
/* START : ##TOOL_OUT#RIM_MOD_3B_OTR_TABLE## */
    {(U2)0U,        (U2)8U      },      /* 0    : RIMID_OTR_NVMC_DA_DTF_WRI_282 */
    {(U2)2U,        (U2)12U     },      /* 1    : RIMID_OTR_NVMC_DA_DTF_WRI_283 */
    {(U2)5U,        (U2)12U     },      /* 2    : RIMID_OTR_NVMC_DA_DTF_WRI_284 */
    {(U2)8U,        (U2)28U     },      /* 3    : RIMID_OTR_NVMC_DA_DTF_WRI_461 */
    {(U2)15U,       (U2)28U     },      /* 4    : RIMID_OTR_NVMC_DA_DTF_WRI_462 */
    {(U2)22U,       (U2)28U     },      /* 5    : RIMID_OTR_NVMC_DA_DTF_WRI_463 */
    {(U2)29U,       (U2)28U     },      /* 6    : RIMID_OTR_NVMC_DA_DTF_WRI_464 */
    {(U2)36U,       (U2)28U     },      /* 7    : RIMID_OTR_NVMC_DA_DTF_WRI_465 */
    {(U2)43U,       (U2)28U     },      /* 8    : RIMID_OTR_NVMC_DA_DTF_WRI_466 */
    {(U2)50U,       (U2)28U     },      /* 9    : RIMID_OTR_NVMC_DA_DTF_WRI_467 */
    {(U2)57U,       (U2)28U     },      /* 10   : RIMID_OTR_NVMC_DA_DTF_WRI_468 */
    {(U2)64U,       (U2)28U     },      /* 11   : RIMID_OTR_NVMC_DA_DTF_WRI_469 */
    {(U2)71U,       (U2)28U     },      /* 12   : RIMID_OTR_NVMC_DA_DTF_WRI_470 */
    {(U2)78U,       (U2)28U     },      /* 13   : RIMID_OTR_NVMC_DA_DTF_WRI_471 */
    {(U2)85U,       (U2)28U     },      /* 14   : RIMID_OTR_NVMC_DA_DTF_WRI_472 */
    {(U2)92U,       (U2)28U     },      /* 15   : RIMID_OTR_NVMC_DA_DTF_WRI_473 */
    {(U2)99U,       (U2)28U     },      /* 16   : RIMID_OTR_NVMC_DA_DTF_WRI_474 */
    {(U2)106U,      (U2)28U     },      /* 17   : RIMID_OTR_NVMC_DA_DTF_WRI_475 */
    {(U2)113U,      (U2)28U     },      /* 18   : RIMID_OTR_NVMC_DA_DTF_WRI_476 */
    {(U2)120U,      (U2)28U     },      /* 19   : RIMID_OTR_NVMC_DA_DTF_WRI_477 */
    {(U2)127U,      (U2)28U     },      /* 20   : RIMID_OTR_NVMC_DA_DTF_WRI_478 */
    {(U2)134U,      (U2)28U     },      /* 21   : RIMID_OTR_NVMC_DA_DTF_WRI_479 */
    {(U2)141U,      (U2)28U     },      /* 22   : RIMID_OTR_NVMC_DA_DTF_WRI_480 */
    {(U2)148U,      (U2)32U     },      /* 23   : RIMID_OTR_NVMC_DA_DTF_WRI_482 */
    {(U2)156U,      (U2)16U     },      /* 24   : RIMID_OTR_NVMC_DA_DTF_WRI_483 */
    {(U2)160U,      (U2)32U     },      /* 25   : RIMID_OTR_NVMC_DA_DTF_WRI_484 */
    {(U2)168U,      (U2)16U     },      /* 26   : RIMID_OTR_NVMC_DA_DTF_WRI_485 */
    {(U2)172U,      (U2)32U     },      /* 27   : RIMID_OTR_NVMC_DA_DTF_WRI_486 */
    {(U2)180U,      (U2)16U     },      /* 28   : RIMID_OTR_NVMC_DA_DTF_WRI_487 */
    {(U2)184U,      (U2)32U     },      /* 29   : RIMID_OTR_NVMC_DA_DTF_WRI_488 */
    {(U2)192U,      (U2)16U     },      /* 30   : RIMID_OTR_NVMC_DA_DTF_WRI_489 */
    {(U2)196U,      (U2)32U     },      /* 31   : RIMID_OTR_NVMC_DA_DTF_WRI_490 */
    {(U2)204U,      (U2)16U     },      /* 32   : RIMID_OTR_NVMC_DA_DTF_WRI_491 */
    {(U2)208U,      (U2)32U     },      /* 33   : RIMID_OTR_NVMC_DA_DTF_WRI_492 */
    {(U2)216U,      (U2)16U     },      /* 34   : RIMID_OTR_NVMC_DA_DTF_WRI_493 */
    {(U2)220U,      (U2)32U     },      /* 35   : RIMID_OTR_NVMC_DA_DTF_WRI_494 */
    {(U2)228U,      (U2)16U     },      /* 36   : RIMID_OTR_NVMC_DA_DTF_WRI_495 */
    {(U2)232U,      (U2)32U     },      /* 37   : RIMID_OTR_NVMC_DA_DTF_WRI_496 */
    {(U2)240U,      (U2)16U     },      /* 38   : RIMID_OTR_NVMC_DA_DTF_WRI_497 */
    {(U2)244U,      (U2)32U     },      /* 39   : RIMID_OTR_NVMC_DA_DTF_WRI_498 */
    {(U2)252U,      (U2)16U     },      /* 40   : RIMID_OTR_NVMC_DA_DTF_WRI_499 */
    {(U2)256U,      (U2)32U     },      /* 41   : RIMID_OTR_NVMC_DA_DTF_WRI_500 */
    {(U2)264U,      (U2)16U     },      /* 42   : RIMID_OTR_NVMC_DA_DTF_WRI_501 */
    {(U2)268U,      (U2)32U     },      /* 43   : RIMID_OTR_NVMC_DA_DTF_WRI_502 */
    {(U2)276U,      (U2)16U     },      /* 44   : RIMID_OTR_NVMC_DA_DTF_WRI_503 */
    {(U2)280U,      (U2)32U     },      /* 45   : RIMID_OTR_NVMC_DA_DTF_WRI_504 */
    {(U2)288U,      (U2)16U     },      /* 46   : RIMID_OTR_NVMC_DA_DTF_WRI_505 */
    {(U2)292U,      (U2)32U     },      /* 47   : RIMID_OTR_NVMC_DA_DTF_WRI_506 */
    {(U2)300U,      (U2)16U     },      /* 48   : RIMID_OTR_NVMC_DA_DTF_WRI_507 */
    {(U2)304U,      (U2)32U     },      /* 49   : RIMID_OTR_NVMC_DA_DTF_WRI_508 */
    {(U2)312U,      (U2)16U     },      /* 50   : RIMID_OTR_NVMC_DA_DTF_WRI_509 */
    {(U2)316U,      (U2)32U     },      /* 51   : RIMID_OTR_NVMC_DA_DTF_WRI_510 */
    {(U2)324U,      (U2)16U     },      /* 52   : RIMID_OTR_NVMC_DA_DTF_WRI_511 */
    {(U2)328U,      (U2)32U     },      /* 53   : RIMID_OTR_NVMC_DA_DTF_WRI_512 */
    {(U2)336U,      (U2)16U     },      /* 54   : RIMID_OTR_NVMC_DA_DTF_WRI_513 */
    {(U2)340U,      (U2)32U     },      /* 55   : RIMID_OTR_NVMC_DA_DTF_WRI_514 */
    {(U2)348U,      (U2)16U     },      /* 56   : RIMID_OTR_NVMC_DA_DTF_WRI_515 */
    {(U2)352U,      (U2)32U     },      /* 57   : RIMID_OTR_NVMC_DA_DTF_WRI_516 */
    {(U2)360U,      (U2)16U     },      /* 58   : RIMID_OTR_NVMC_DA_DTF_WRI_517 */
    {(U2)364U,      (U2)32U     },      /* 59   : RIMID_OTR_NVMC_DA_DTF_WRI_518 */
    {(U2)372U,      (U2)16U     },      /* 60   : RIMID_OTR_NVMC_DA_DTF_WRI_519 */
    {(U2)376U,      (U2)32U     },      /* 61   : RIMID_OTR_NVMC_DA_DTF_WRI_520 */
    {(U2)384U,      (U2)16U     },      /* 62   : RIMID_OTR_NVMC_DA_DTF_WRI_521 */
    {(U2)388U,      (U2)28U     },      /* 63   : RIMID_OTR_NVMC_DA_DTF_WRI_523 */
    {(U2)395U,      (U2)28U     },      /* 64   : RIMID_OTR_NVMC_DA_DTF_WRI_524 */
    {(U2)402U,      (U2)28U     },      /* 65   : RIMID_OTR_NVMC_DA_DTF_WRI_525 */
    {(U2)409U,      (U2)28U     },      /* 66   : RIMID_OTR_NVMC_DA_DTF_WRI_526 */
    {(U2)416U,      (U2)28U     },      /* 67   : RIMID_OTR_NVMC_DA_DTF_WRI_527 */
    {(U2)423U,      (U2)32U     },      /* 68   : RIMID_OTR_NVMC_DA_DTF_WRI_529 */
    {(U2)431U,      (U2)20U     },      /* 69   : RIMID_OTR_NVMC_DA_DTF_WRI_530 */
    {(U2)436U,      (U2)32U     },      /* 70   : RIMID_OTR_NVMC_DA_DTF_WRI_531 */
    {(U2)444U,      (U2)20U     },      /* 71   : RIMID_OTR_NVMC_DA_DTF_WRI_532 */
    {(U2)449U,      (U2)32U     },      /* 72   : RIMID_OTR_NVMC_DA_DTF_WRI_533 */
    {(U2)457U,      (U2)20U     },      /* 73   : RIMID_OTR_NVMC_DA_DTF_WRI_534 */
    {(U2)462U,      (U2)32U     },      /* 74   : RIMID_OTR_NVMC_DA_DTF_WRI_535 */
    {(U2)470U,      (U2)20U     },      /* 75   : RIMID_OTR_NVMC_DA_DTF_WRI_536 */
    {(U2)475U,      (U2)32U     },      /* 76   : RIMID_OTR_NVMC_DA_DTF_WRI_537 */
    {(U2)483U,      (U2)20U     },      /* 77   : RIMID_OTR_NVMC_DA_DTF_WRI_538 */
    {(U2)488U,      (U2)28U     },      /* 78   : RIMID_OTR_NVMC_DA_DTF_WRI_540 */
    {(U2)495U,      (U2)28U     },      /* 79   : RIMID_OTR_NVMC_DA_DTF_WRI_541 */
    {(U2)502U,      (U2)28U     },      /* 80   : RIMID_OTR_NVMC_DA_DTF_WRI_542 */
    {(U2)509U,      (U2)28U     },      /* 81   : RIMID_OTR_NVMC_DA_DTF_WRI_543 */
    {(U2)516U,      (U2)28U     },      /* 82   : RIMID_OTR_NVMC_DA_DTF_WRI_544 */
    {(U2)523U,      (U2)28U     },      /* 83   : RIMID_OTR_NVMC_DA_DTF_WRI_545 */
    {(U2)530U,      (U2)28U     },      /* 84   : RIMID_OTR_NVMC_DA_DTF_WRI_546 */
    {(U2)537U,      (U2)28U     },      /* 85   : RIMID_OTR_NVMC_DA_DTF_WRI_547 */
    {(U2)544U,      (U2)28U     },      /* 86   : RIMID_OTR_NVMC_DA_DTF_WRI_548 */
    {(U2)551U,      (U2)28U     },      /* 87   : RIMID_OTR_NVMC_DA_DTF_WRI_549 */
    {(U2)558U,      (U2)28U     },      /* 88   : RIMID_OTR_NVMC_DA_DTF_WRI_550 */
    {(U2)565U,      (U2)28U     },      /* 89   : RIMID_OTR_NVMC_DA_DTF_WRI_551 */
    {(U2)572U,      (U2)28U     },      /* 90   : RIMID_OTR_NVMC_DA_DTF_WRI_552 */
    {(U2)579U,      (U2)28U     },      /* 91   : RIMID_OTR_NVMC_DA_DTF_WRI_553 */
    {(U2)586U,      (U2)28U     },      /* 92   : RIMID_OTR_NVMC_DA_DTF_WRI_554 */
    {(U2)593U,      (U2)28U     },      /* 93   : RIMID_OTR_NVMC_DA_DTF_WRI_555 */
    {(U2)600U,      (U2)28U     },      /* 94   : RIMID_OTR_NVMC_DA_DTF_WRI_556 */
    {(U2)607U,      (U2)28U     },      /* 95   : RIMID_OTR_NVMC_DA_DTF_WRI_557 */
    {(U2)614U,      (U2)28U     },      /* 96   : RIMID_OTR_NVMC_DA_DTF_WRI_558 */
    {(U2)621U,      (U2)28U     },      /* 97   : RIMID_OTR_NVMC_DA_DTF_WRI_559 */
    {(U2)628U,      (U2)32U     },      /* 98   : RIMID_OTR_NVMC_DA_DTF_WRI_561 */
    {(U2)636U,      (U2)32U     },      /* 99   : RIMID_OTR_NVMC_DA_DTF_WRI_563 */
    {(U2)644U,      (U2)32U     },      /* 100  : RIMID_OTR_NVMC_DA_DTF_WRI_565 */
    {(U2)652U,      (U2)32U     },      /* 101  : RIMID_OTR_NVMC_DA_DTF_WRI_567 */
    {(U2)660U,      (U2)32U     },      /* 102  : RIMID_OTR_NVMC_DA_DTF_WRI_569 */
    {(U2)668U,      (U2)32U     },      /* 103  : RIMID_OTR_NVMC_DA_DTF_WRI_571 */
    {(U2)676U,      (U2)32U     },      /* 104  : RIMID_OTR_NVMC_DA_DTF_WRI_573 */
    {(U2)684U,      (U2)32U     },      /* 105  : RIMID_OTR_NVMC_DA_DTF_WRI_575 */
    {(U2)692U,      (U2)32U     },      /* 106  : RIMID_OTR_NVMC_DA_DTF_WRI_577 */
    {(U2)700U,      (U2)32U     },      /* 107  : RIMID_OTR_NVMC_DA_DTF_WRI_579 */
    {(U2)708U,      (U2)32U     },      /* 108  : RIMID_OTR_NVMC_DA_DTF_WRI_581 */
    {(U2)716U,      (U2)32U     },      /* 109  : RIMID_OTR_NVMC_DA_DTF_WRI_583 */
    {(U2)724U,      (U2)32U     },      /* 110  : RIMID_OTR_NVMC_DA_DTF_WRI_585 */
    {(U2)732U,      (U2)32U     },      /* 111  : RIMID_OTR_NVMC_DA_DTF_WRI_587 */
    {(U2)740U,      (U2)32U     },      /* 112  : RIMID_OTR_NVMC_DA_DTF_WRI_589 */
    {(U2)748U,      (U2)32U     },      /* 113  : RIMID_OTR_NVMC_DA_DTF_WRI_591 */
    {(U2)756U,      (U2)32U     },      /* 114  : RIMID_OTR_NVMC_DA_DTF_WRI_593 */
    {(U2)764U,      (U2)32U     },      /* 115  : RIMID_OTR_NVMC_DA_DTF_WRI_595 */
    {(U2)772U,      (U2)32U     },      /* 116  : RIMID_OTR_NVMC_DA_DTF_WRI_597 */
    {(U2)780U,      (U2)32U     },      /* 117  : RIMID_OTR_NVMC_DA_DTF_WRI_599 */
    {(U2)788U,      (U2)24U     },      /* 118  : RIMID_OTR_NVMC_DA_DTF_WRI_602 */
    {(U2)794U,      (U2)24U     },      /* 119  : RIMID_OTR_NVMC_DA_DTF_WRI_603 */
    {(U2)800U,      (U2)24U     },      /* 120  : RIMID_OTR_NVMC_DA_DTF_WRI_604 */
    {(U2)806U,      (U2)24U     },      /* 121  : RIMID_OTR_NVMC_DA_DTF_WRI_605 */
    {(U2)812U,      (U2)24U     },      /* 122  : RIMID_OTR_NVMC_DA_DTF_WRI_606 */
    {(U2)818U,      (U2)24U     },      /* 123  : RIMID_OTR_NVMC_DA_DTF_WRI_607 */
    {(U2)824U,      (U2)24U     },      /* 124  : RIMID_OTR_NVMC_DA_DTF_WRI_608 */
    {(U2)830U,      (U2)24U     },      /* 125  : RIMID_OTR_NVMC_DA_DTF_WRI_609 */
    {(U2)836U,      (U2)24U     },      /* 126  : RIMID_OTR_NVMC_DA_DTF_WRI_610 */
    {(U2)842U,      (U2)24U     },      /* 127  : RIMID_OTR_NVMC_DA_DTF_WRI_611 */
    {(U2)848U,      (U2)24U     },      /* 128  : RIMID_OTR_NVMC_DA_DTF_WRI_612 */
    {(U2)854U,      (U2)24U     },      /* 129  : RIMID_OTR_NVMC_DA_DTF_WRI_613 */
    {(U2)860U,      (U2)24U     },      /* 130  : RIMID_OTR_NVMC_DA_DTF_WRI_614 */
    {(U2)866U,      (U2)24U     },      /* 131  : RIMID_OTR_NVMC_DA_DTF_WRI_615 */
    {(U2)872U,      (U2)24U     },      /* 132  : RIMID_OTR_NVMC_DA_DTF_WRI_616 */
    {(U2)878U,      (U2)24U     },      /* 133  : RIMID_OTR_NVMC_DA_DTF_WRI_617 */
    {(U2)884U,      (U2)24U     },      /* 134  : RIMID_OTR_NVMC_DA_DTF_WRI_618 */
    {(U2)890U,      (U2)24U     },      /* 135  : RIMID_OTR_NVMC_DA_DTF_WRI_619 */
    {(U2)896U,      (U2)24U     },      /* 136  : RIMID_OTR_NVMC_DA_DTF_WRI_620 */
    {(U2)902U,      (U2)24U     },      /* 137  : RIMID_OTR_NVMC_DA_DTF_WRI_621 */
    {(U2)908U,      (U2)8U      }       /* 138  : RIMID_OTR_NVMC_DA_DTF_WRI_624 */
/* END : ##TOOL_OUT#RIM_MOD_3B_OTR_TABLE## */
};

#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           11/18/2014  KM      New.                                                                                         */
/*  1.1.0           03/30/2015  MH      Update version check                                                                         */
/*  1.1.1           07/14/2015  HK      Comment correction                                                                           */
/*  1.2.0           09/07/2015  HK      Correction of the error message                                                              */
/*                                      Condition judgment addition with the preprocessor                                            */
/*                                      Revision up by "rim_mod_3bram.c" correction                                                  */
/*  1.2.1           10/07/2015  HK      Expand DataID to 9bit                                                                        */
/*  1.2.2           02/29/2016  HK      Correspond non-library                                                                       */
/*  1.2.3           12/07/2016  HK      Fixed AIP3GBSW-25 issue.                                                                     */
/*  1.2.4            9/14/2021  TN      rim_mod_3bram.c v1.2.3 -> v1.2.4.                                                            */
/*  1.3.0            9/16/2021  TN      rim_mod_3bram.c v1.2.4 -> v1.3.0.                                                            */
/*  1.3.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
