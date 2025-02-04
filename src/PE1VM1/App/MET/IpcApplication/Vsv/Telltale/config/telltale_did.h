/* 5.5.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Telltale                                                                                                                         */
/*  MET-M_MMPHA5DI-CSTD-0-20-A-C5.xlsx                                                                                               */
/*===================================================================================================================================*/

#ifndef TELLTALE_DID_H
#define TELLTALE_DID_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TELLTALE_DID_H_MAJOR                  (5)
#define TELLTALE_DID_H_MINOR                  (5)
#define TELLTALE_DID_H_PATCH                  (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TT_NUM_DID                      (16U)
#define TT_DID_2901                     ( 0U)
#define TT_DID_2911                     ( 1U)
#define TT_DID_2912                     ( 2U)
#define TT_DID_2921                     ( 3U)
#define TT_DID_2922                     ( 4U)
#define TT_DID_2931                     ( 5U)
#define TT_DID_2932                     ( 6U)
#define TT_DID_2933                     ( 7U)
#define TT_DID_2941                     ( 8U)
#define TT_DID_2942                     ( 9U)
#define TT_DID_2943                     (10U)
#define TT_DID_2951                     (11U)
#define TT_DID_2952                     (12U)
#define TT_DID_2961                     (13U)
#define TT_DID_2971                     (14U)
#define TT_DID_2981                     (15U)

/*  DID 0x2901   */
#define TT_IOR_D2901_B06_0_XXX_UNDEF        (0x0000U) /* [  0] DID:2901, Byte:#6, b0 [Undef  :Undef]                                 */
#define TT_IOR_D2901_B06_1_XXX_UNDEF        (0x0001U) /* [  1] DID:2901, Byte:#6, b1 [Undef  :Undef]                                 */
#define TT_IOR_D2901_B06_2_XXX_UNDEF        (0x0002U) /* [  2] DID:2901, Byte:#6, b2 [Undef  :Undef]                                 */
#define TT_IOR_D2901_B06_3_YEL_GOTOSRV      (0x0003U) /* [  3] DID:2901, Byte:#6, b3 [YELLOW :Go To Service]                         */
#define TT_IOR_D2901_B06_4_RED_VHCL_STOP    (0x0004U) /* [  4] DID:2901, Byte:#6, b4 [RED    :Vehicle Stop]                          */
#define TT_IOR_D2901_B06_5_YEL_MSTR_CAU     (0x0005U) /* [  5] DID:2901, Byte:#6, b5 [YELLOW :Master Caution]                        */
#define TT_IOR_D2901_B06_6_YEL_120KWRN      (0x0006U) /* [  6] DID:2901, Byte:#6, b6 [YELLOW :MID 120kmWrn]                          */
#define TT_IOR_D2901_B06_7_YEL_LOW_FUEL     (0x0007U) /* [  7] DID:2901, Byte:#6, b7 [YELLOW :Fuel]                                  */

/*  DID 0x2911   */
#define TT_IOR_D2911_B06_0_YEL_AHBAHS       (0x0100U) /* [ 16] DID:2911, Byte:#6, b0 [YELLOW :AHB or AHS]                            */
#define TT_IOR_D2911_B06_1_GRN_AHBAHS       (0x0101U) /* [ 17] DID:2911, Byte:#6, b1 [GREEN  :AHB or AHS]                            */
#define TT_IOR_D2911_B06_2_YEL_HL_LEVEL     (0x0102U) /* [ 18] DID:2911, Byte:#6, b2 [YELLOW :HEADLAMP AUTO LEVELING]                */
#define TT_IOR_D2911_B06_3_YEL_RRFOG        (0x0103U) /* [ 19] DID:2911, Byte:#6, b3 [YELLOW :RrFOG]                                 */
#define TT_IOR_D2911_B06_4_GRN_FRFOG        (0x0104U) /* [ 20] DID:2911, Byte:#6, b4 [GREEN  :FrFOG]                                 */
#define TT_IOR_D2911_B06_5_GRN_TAIL         (0x0105U) /* [ 21] DID:2911, Byte:#6, b5 [GREEN  :TAIL]                                  */
#define TT_IOR_D2911_B06_6_GRN_HEAD         (0x0106U) /* [ 22] DID:2911, Byte:#6, b6 [GREEN  :HEAD]                                  */
#define TT_IOR_D2911_B06_7_BLU_BEAM         (0x0107U) /* [ 23] DID:2911, Byte:#6, b7 [BLUE   :BEAM]                                  */
#define TT_IOR_D2911_B08_0_RED_RR_BELT      (0x0108U) /* [ 24] DID:2911, Byte:#8, b0 [RED    :Rear Seatbelt Wrn]                     */
#define TT_IOR_D2911_B08_1_RED_P_BELT       (0x0109U) /* [ 25] DID:2911, Byte:#8, b1 [RED    :Passanger Seatbelt Wrn]                */
#define TT_IOR_D2911_B08_2_RED_D_BELT       (0x010AU) /* [ 26] DID:2911, Byte:#8, b2 [RED    :Driver Seatbelt Wrn]                   */
#define TT_IOR_D2911_B08_3_GRN_TURN_R       (0x010BU) /* [ 27] DID:2911, Byte:#8, b3 [GREEN  :Turn R]                                */
#define TT_IOR_D2911_B08_4_GRN_TURN_L       (0x010CU) /* [ 28] DID:2911, Byte:#8, b4 [GREEN  :Turn L]                                */
#define TT_IOR_D2911_B08_5_YEL_RRLIGHT      (0x010DU) /* [ 29] DID:2911, Byte:#8, b5 [YELLOW :Rr Light]                              */
#define TT_IOR_D2911_B08_6_YEL_LED_MAL      (0x010EU) /* [ 30] DID:2911, Byte:#8, b6 [YELLOW :LED Headlamp Malfunction]              */
#define TT_IOR_D2911_B08_7_YEL_AFS_OFF      (0x010FU) /* [ 31] DID:2911, Byte:#8, b7 [YELLOW :AFS OFF]                               */

/*  DID 0x2912   */
#define TT_IOR_D2912_B06_0_GRN_AC_AUTO      (0x0200U) /* [ 32] DID:2912, Byte:#6, b0 [GREEN  :A/C Auto]                              */
#define TT_IOR_D2912_B06_1_GRN_HUD_IND      (0x0201U) /* [ 33] DID:2912, Byte:#6, b1 [GREEN  :HUD Indicator]                         */
#define TT_IOR_D2912_B06_2_YEL_SMART        (0x0202U) /* [ 34] DID:2912, Byte:#6, b2 [YELLOW :Smart System]                          */
#define TT_IOR_D2912_B06_3_GRN_SMART        (0x0203U) /* [ 35] DID:2912, Byte:#6, b3 [GREEN  :Smart System]                          */
#define TT_IOR_D2912_B06_4_RED_POPUP_HD     (0x0204U) /* [ 36] DID:2912, Byte:#6, b4 [RED    :Pedestrian protect sys.]               */
#define TT_IOR_D2912_B06_5_RED_AIRBAG       (0x0205U) /* [ 37] DID:2912, Byte:#6, b5 [RED    :Airbag]                                */
#define TT_IOR_D2912_B06_6_RED_DOOR         (0x0206U) /* [ 38] DID:2912, Byte:#6, b6 [RED    :Door]                                  */
#define TT_IOR_D2912_B06_7_YEL_WASHER       (0x0207U) /* [ 39] DID:2912, Byte:#6, b7 [YELLOW :Washer Level]                          */
#define TT_IOR_D2912_B08_0_XXX_UNDEF        (0x0208U) /* [ 40] DID:2912, Byte:#8, b0 [Undef  :Undef]                                 */
#define TT_IOR_D2912_B08_1_XXX_UNDEF        (0x0209U) /* [ 41] DID:2912, Byte:#8, b1 [Undef  :Undef]                                 */
#define TT_IOR_D2912_B08_2_XXX_UNDEF        (0x020AU) /* [ 42] DID:2912, Byte:#8, b2 [Undef  :Undef]                                 */
#define TT_IOR_D2912_B08_3_XXX_UNDEF        (0x020BU) /* [ 43] DID:2912, Byte:#8, b3 [Undef  :Undef]                                 */
#define TT_IOR_D2912_B08_4_XXX_UNDEF        (0x020CU) /* [ 44] DID:2912, Byte:#8, b4 [Undef  :Undef]                                 */
#define TT_IOR_D2912_B08_5_GRN_MWLIGHT      (0x020DU) /* [ 45] DID:2912, Byte:#8, b5 [GREEN  :Multi-weather Light]                   */
#define TT_IOR_D2912_B08_6_YEL_RSCAOFF      (0x020EU) /* [ 46] DID:2912, Byte:#8, b6 [YELLOW :RSCA OFF]                              */
#define TT_IOR_D2912_B08_7_RED_EXIT         (0x020FU) /* [ 47] DID:2912, Byte:#8, b7 [RED    :Emergency Exit]                        */

/*  DID 0x2921   */
#define TT_IOR_D2921_B06_0_YEL_MAINT        (0x0300U) /* [ 48] DID:2921, Byte:#6, b0 [YELLOW :Maitenance]                            */
#define TT_IOR_D2921_B06_1_GRN_ECO_LEAF     (0x0301U) /* [ 49] DID:2921, Byte:#6, b1 [GREEN  :Eco leaf indicator]                    */
#define TT_IOR_D2921_B06_2_YEL_SEDIMENT     (0x0302U) /* [ 50] DID:2921, Byte:#6, b2 [YELLOW :Fuel Sedimenter]                       */
#define TT_IOR_D2921_B06_3_BLU_TEMP_CL      (0x0303U) /* [ 51] DID:2921, Byte:#6, b3 [BLUE   :Temprature Cool]                       */
#define TT_IOR_D2921_B06_4_RED_TEMP_HT      (0x0304U) /* [ 52] DID:2921, Byte:#6, b4 [RED    :Temprature Hot]                        */
#define TT_IOR_D2921_B06_5_YEL_GLOW         (0x0305U) /* [ 53] DID:2921, Byte:#6, b5 [YELLOW :Glow]                                  */
#define TT_IOR_D2921_B06_6_YEL_OIL_LEVEL    (0x0306U) /* [ 54] DID:2921, Byte:#6, b6 [YELLOW :Oil Level]                             */
#define TT_IOR_D2921_B06_7_RED_OIL_PRESS    (0x0307U) /* [ 55] DID:2921, Byte:#6, b7 [RED    :Oil Pressure]                          */
#define TT_IOR_D2921_B08_0_YEL_UREA_SCR     (0x0308U) /* [ 56] DID:2921, Byte:#8, b0 [YELLOW :UREA SCR]                              */
#define TT_IOR_D2921_B08_1_YEL_LPG          (0x0309U) /* [ 57] DID:2921, Byte:#8, b1 [YELLOW :LPG Indicator]                         */
#define TT_IOR_D2921_B08_2_GRN_CNG_MODE     (0x030AU) /* [ 58] DID:2921, Byte:#8, b2 [GREEN  :CNG Mode Indicator]                    */
#define TT_IOR_D2921_B08_3_YEL_CNG_REMAI    (0x030BU) /* [ 59] DID:2921, Byte:#8, b3 [YELLOW :CNG Remaining]                         */
#define TT_IOR_D2921_B08_4_YEL_PATIC_FIL    (0x030CU) /* [ 60] DID:2921, Byte:#8, b4 [YELLOW :Paticulate Filter]                     */
#define TT_IOR_D2921_B08_5_YEL_CHECK_ENG    (0x030DU) /* [ 61] DID:2921, Byte:#8, b5 [YELLOW :Check Engine]                          */
#define TT_IOR_D2921_B08_6_YEL_FUEL_FIL     (0x030EU) /* [ 62] DID:2921, Byte:#8, b6 [YELLOW :Fuel Filter]                           */
#define TT_IOR_D2921_B08_7_YEL_T_BELT       (0x030FU) /* [ 63] DID:2921, Byte:#8, b7 [YELLOW :Timing Belt Wrn]                       */

/*  DID 0x2922   */
#define TT_IOR_D2922_B06_0_XXX_UNDEF        (0x0400U) /* [ 64] DID:2922, Byte:#6, b0 [Undef  :Undef]                                 */
#define TT_IOR_D2922_B06_1_XXX_UNDEF        (0x0401U) /* [ 65] DID:2922, Byte:#6, b1 [Undef  :Undef]                                 */
#define TT_IOR_D2922_B06_2_XXX_UNDEF        (0x0402U) /* [ 66] DID:2922, Byte:#6, b2 [Undef  :Undef]                                 */
#define TT_IOR_D2922_B06_3_XXX_UNDEF        (0x0403U) /* [ 67] DID:2922, Byte:#6, b3 [Undef  :Undef]                                 */
#define TT_IOR_D2922_B06_4_XXX_UNDEF        (0x0404U) /* [ 68] DID:2922, Byte:#6, b4 [Undef  :Undef]                                 */
#define TT_IOR_D2922_B06_5_XXX_UNDEF        (0x0405U) /* [ 69] DID:2922, Byte:#6, b5 [Undef  :Undef]                                 */
#define TT_IOR_D2922_B06_6_XXX_UNDEF        (0x0406U) /* [ 70] DID:2922, Byte:#6, b6 [Undef  :Undef]                                 */
#define TT_IOR_D2922_B06_7_YEL_FLID_OPEN    (0x0407U) /* [ 71] DID:2922, Byte:#6, b7 [YELLOW :Fuel Lid Open]                         */

/*  DID 0x2931   */
#define TT_IOR_D2931_B06_0_GRN_RANGE_L      (0x0500U) /* [ 80] DID:2931, Byte:#6, b0 [GREEN  :L range]                               */
#define TT_IOR_D2931_B06_1_GRN_RANGE_2      (0x0501U) /* [ 81] DID:2931, Byte:#6, b1 [GREEN  :2 range]                               */
#define TT_IOR_D2931_B06_2_GRN_RANGE_3      (0x0502U) /* [ 82] DID:2931, Byte:#6, b2 [GREEN  :3 range]                               */
#define TT_IOR_D2931_B06_3_GRN_RANGE_4      (0x0503U) /* [ 83] DID:2931, Byte:#6, b3 [GREEN  :4 range]                               */
#define TT_IOR_D2931_B06_4_GRN_RANGE_D      (0x0504U) /* [ 84] DID:2931, Byte:#6, b4 [GREEN  :D range]                               */
#define TT_IOR_D2931_B06_5_GRN_RANGE_N      (0x0505U) /* [ 85] DID:2931, Byte:#6, b5 [GREEN  :N range]                               */
#define TT_IOR_D2931_B06_6_YEL_RANGE_R      (0x0506U) /* [ 86] DID:2931, Byte:#6, b6 [YELLOW :R range]                               */
#define TT_IOR_D2931_B06_7_GRN_RANGE_P      (0x0507U) /* [ 87] DID:2931, Byte:#6, b7 [GREEN  :P range]                               */
#define TT_IOR_D2931_B08_0_YEL_2ND_START    (0x0508U) /* [ 88] DID:2931, Byte:#8, b0 [YELLOW :2nd Start]                             */
#define TT_IOR_D2931_B08_1_YEL_ECT_SNOW     (0x0509U) /* [ 89] DID:2931, Byte:#8, b1 [YELLOW :ECT Snow]                              */
#define TT_IOR_D2931_B08_2_GRN_ECT_POWER    (0x050AU) /* [ 90] DID:2931, Byte:#8, b2 [GREEN  :ECT Power]                             */
#define TT_IOR_D2931_B08_3_YEL_OD_OFF       (0x050BU) /* [ 91] DID:2931, Byte:#8, b3 [YELLOW :OD OFF]                                */
#define TT_IOR_D2931_B08_4_GRN_MODE_S       (0x050CU) /* [ 92] DID:2931, Byte:#8, b4 [GREEN  :Sports shift S]                        */
#define TT_IOR_D2931_B08_5_YEL_MODE_M       (0x050DU) /* [ 93] DID:2931, Byte:#8, b5 [YELLOW :Sports shift M]                        */
#define TT_IOR_D2931_B08_6_GRN_RANGE_S      (0x050EU) /* [ 94] DID:2931, Byte:#8, b6 [GREEN  :S range]                               */
#define TT_IOR_D2931_B08_7_GRN_RANGE_B      (0x050FU) /* [ 95] DID:2931, Byte:#8, b7 [GREEN  :B range]                               */

/*  DID 0x2932   */
#define TT_IOR_D2932_B06_0_RED_AT_P         (0x0600U) /* [ 96] DID:2932, Byte:#6, b0 [RED    :A/T P]                                 */
#define TT_IOR_D2932_B06_1_RED_AT_OILTMP    (0x0601U) /* [ 97] DID:2932, Byte:#6, b1 [RED    :A/T Oil Temp]                          */
#define TT_IOR_D2932_B06_2_GRN_SIL_DOWN     (0x0602U) /* [ 98] DID:2932, Byte:#6, b2 [GREEN  :Sil down]                              */
#define TT_IOR_D2932_B06_3_GRN_SIL_UP       (0x0603U) /* [ 99] DID:2932, Byte:#6, b3 [GREEN  :Sil up]                                */
#define TT_IOR_D2932_B06_4_RED_SBW_MAL      (0x0604U) /* [100] DID:2932, Byte:#6, b4 [RED    :Shift by wire Wrn]                     */
#define TT_IOR_D2932_B06_5_RED_MMT_GEAR     (0x0605U) /* [101] DID:2932, Byte:#6, b5 [RED    :MMT Gear]                              */
#define TT_IOR_D2932_B06_6_GRN_ECO_MODE     (0x0606U) /* [102] DID:2932, Byte:#6, b6 [GREEN  :Eco Mode]                              */
#define TT_IOR_D2932_B06_7_GRN_SPORT        (0x0607U) /* [103] DID:2932, Byte:#6, b7 [GREEN  :Sport(CVT Sport)]                      */
#define TT_IOR_D2932_B08_0_YEL_4LO          (0x0608U) /* [104] DID:2932, Byte:#8, b0 [YELLOW :4Lo]                                   */
#define TT_IOR_D2932_B08_1_YEL_FRDIFFKLK    (0x0609U) /* [105] DID:2932, Byte:#8, b1 [YELLOW :Front Diff Lock]                       */
#define TT_IOR_D2932_B08_2_YEL_RRDIFFKLK    (0x060AU) /* [106] DID:2932, Byte:#8, b2 [YELLOW :Rear Diff Lock]                        */
#define TT_IOR_D2932_B08_3_YEL_4WDLOCK      (0x060BU) /* [107] DID:2932, Byte:#8, b3 [YELLOW :4WD Lock(Center Diff Lock)]            */
#define TT_IOR_D2932_B08_4_YEL_4WDIND       (0x060CU) /* [108] DID:2932, Byte:#8, b4 [YELLOW :4WD Indicator]                         */
#define TT_IOR_D2932_B08_5_GRN_4WDIND       (0x060DU) /* [109] DID:2932, Byte:#8, b5 [GREEN  :4WD Indicator]                         */
#define TT_IOR_D2932_B08_6_GRN_4WDAUTO      (0x060EU) /* [110] DID:2932, Byte:#8, b6 [GREEN  :4WD Auto]                              */
#define TT_IOR_D2932_B08_7_YEL_4WDWRN       (0x060FU) /* [111] DID:2932, Byte:#8, b7 [YELLOW :4WD Wrn]                               */

/*  DID 0x2933   */
#define TT_IOR_D2933_B06_0_XXX_UNDEF        (0x0700U) /* [112] DID:2933, Byte:#6, b0 [Undef  :Undef]                                 */
#define TT_IOR_D2933_B06_1_XXX_UNDEF        (0x0701U) /* [113] DID:2933, Byte:#6, b1 [Undef  :Undef]                                 */
#define TT_IOR_D2933_B06_2_XXX_UNDEF        (0x0702U) /* [114] DID:2933, Byte:#6, b2 [Undef  :Undef]                                 */
#define TT_IOR_D2933_B06_3_GRN_NAVI_CVT     (0x0703U) /* [115] DID:2933, Byte:#6, b3 [GREEN  :NAVI CVT]                              */
#define TT_IOR_D2933_B06_4_YEL_TOW_HAUL     (0x0704U) /* [116] DID:2933, Byte:#6, b4 [YELLOW :Tow Haul]                              */
#define TT_IOR_D2933_B06_5_YEL_IMT          (0x0705U) /* [117] DID:2933, Byte:#6, b5 [YELLOW :iMT]                                   */
#define TT_IOR_D2933_B06_6_GRN_IMT          (0x0706U) /* [118] DID:2933, Byte:#6, b6 [GREEN  :iMT]                                   */
#define TT_IOR_D2933_B06_7_YEL_AUTOLSD      (0x0707U) /* [119] DID:2933, Byte:#6, b7 [YELLOW :Auto LSD]                              */

/*  DID 0x2941   */
#define TT_IOR_D2941_B06_0_YEL_TRCOFF       (0x0800U) /* [128] DID:2941, Byte:#6, b0 [YELLOW :VSC TRC]                               */
#define TT_IOR_D2941_B06_1_YEL_VSCOFF       (0x0801U) /* [129] DID:2941, Byte:#6, b1 [YELLOW :VSC-OFF]                               */
#define TT_IOR_D2941_B06_2_YEL_SLIP         (0x0802U) /* [130] DID:2941, Byte:#6, b2 [YELLOW :SLIP]                                  */
#define TT_IOR_D2941_B06_3_YEL_EPB_ATOFF    (0x0803U) /* [131] DID:2941, Byte:#6, b3 [YELLOW :EPB-Auto OFF]                          */
#define TT_IOR_D2941_B06_4_YEL_ECBEPB       (0x0804U) /* [132] DID:2941, Byte:#6, b4 [YELLOW :ECB or EPB]                            */
#define TT_IOR_D2941_B06_5_YEL_ABS          (0x0805U) /* [133] DID:2941, Byte:#6, b5 [YELLOW :ABS]                                   */
#define TT_IOR_D2941_B06_6_RED_PARK         (0x0806U) /* [134] DID:2941, Byte:#6, b6 [RED    :PARK]                                  */
#define TT_IOR_D2941_B06_7_RED_BRAKE        (0x0807U) /* [135] DID:2941, Byte:#6, b7 [RED    :BRAKE]                                 */
#define TT_IOR_D2941_B08_0_YEL_CRAWL        (0x0808U) /* [136] DID:2941, Byte:#8, b0 [YELLOW :CRAWL]                                 */
#define TT_IOR_D2941_B08_1_GRN_CRAWL        (0x0809U) /* [137] DID:2941, Byte:#8, b1 [GREEN  :CRAWL]                                 */
#define TT_IOR_D2941_B08_2_YEL_DAC          (0x080AU) /* [138] DID:2941, Byte:#8, b2 [YELLOW :Downhill Assist Control]               */
#define TT_IOR_D2941_B08_3_GRN_DAC          (0x080BU) /* [139] DID:2941, Byte:#8, b3 [GREEN  :Downhill Assist Control]               */
#define TT_IOR_D2941_B08_4_YEL_HOLD         (0x080CU) /* [140] DID:2941, Byte:#8, b4 [YELLOW :Hold]                                  */
#define TT_IOR_D2941_B08_5_GRN_HOLD_STB     (0x080DU) /* [141] DID:2941, Byte:#8, b5 [GREEN  :Hold Standby]                          */
#define TT_IOR_D2941_B08_6_YEL_ACT_TRC      (0x080EU) /* [142] DID:2941, Byte:#8, b6 [YELLOW :Active TRC]                            */
#define TT_IOR_D2941_B08_7_GRN_ACT_TRC      (0x080FU) /* [143] DID:2941, Byte:#8, b7 [GREEN  :Active TRC]                            */

/*  DID 0x2942   */
#define TT_IOR_D2942_B06_0_YEL_VGRS         (0x0900U) /* [144] DID:2942, Byte:#6, b0 [YELLOW :VGRS]                                  */
#define TT_IOR_D2942_B06_1_YEL_EPS          (0x0901U) /* [145] DID:2942, Byte:#6, b1 [YELLOW :PPS or EPS]                            */
#define TT_IOR_D2942_B06_2_RED_EPS          (0x0902U) /* [146] DID:2942, Byte:#6, b2 [RED    :EPS]                                   */
#define TT_IOR_D2942_B06_3_YEL_TIRE_PRSS    (0x0903U) /* [147] DID:2942, Byte:#6, b3 [YELLOW :Tire Pressure]                         */
#define TT_IOR_D2942_B06_4_YEL_OFFRD_AST    (0x0904U) /* [148] DID:2942, Byte:#6, b4 [YELLOW :Offroad Turn Assist]                   */
#define TT_IOR_D2942_B06_5_GRN_OFFRD_AST    (0x0905U) /* [149] DID:2942, Byte:#6, b5 [GREEN  :Offroad Turn Assist]                   */
#define TT_IOR_D2942_B06_6_YEL_MLT_TER      (0x0906U) /* [150] DID:2942, Byte:#6, b6 [YELLOW :Multi Terrain Select]                  */
#define TT_IOR_D2942_B06_7_GRN_MLT_TER      (0x0907U) /* [151] DID:2942, Byte:#6, b7 [GREEN  :Multi Terrain Select]                  */
#define TT_IOR_D2942_B08_0_GRN_AIRSUS_LO    (0x0908U) /* [152] DID:2942, Byte:#8, b0 [GREEN  :Air Suspension Lo]                     */
#define TT_IOR_D2942_B08_1_GRN_AIRSUS_N     (0x0909U) /* [153] DID:2942, Byte:#8, b1 [GREEN  :Air Suspension Normal]                 */
#define TT_IOR_D2942_B08_2_GRN_AIRSUS_HI    (0x090AU) /* [154] DID:2942, Byte:#8, b2 [GREEN  :Air Suspension Hi]                     */
#define TT_IOR_D2942_B08_3_YEL_HEIGHT_HI    (0x090BU) /* [155] DID:2942, Byte:#8, b3 [YELLOW :Height High]                           */
#define TT_IOR_D2942_B08_4_GRN_HEIGHT_HI    (0x090CU) /* [156] DID:2942, Byte:#8, b4 [GREEN  :Height High]                           */
#define TT_IOR_D2942_B08_5_YEL_KDSS         (0x090DU) /* [157] DID:2942, Byte:#8, b5 [YELLOW :KDSS]                                  */
#define TT_IOR_D2942_B08_6_GRN_AVS_CMFRT    (0x090EU) /* [158] DID:2942, Byte:#8, b6 [GREEN  :AVS Comfort]                           */
#define TT_IOR_D2942_B08_7_GRN_AVS_SPORT    (0x090FU) /* [159] DID:2942, Byte:#8, b7 [GREEN  :AVS Sports]                            */

/*  DID 0x2943   */
#define TT_IOR_D2943_B06_0_GRN_TRAIL_MD     (0x0A00U) /* [160] DID:2943, Byte:#6, b0 [GREEN  :Trail Mode]                            */
#define TT_IOR_D2943_B06_1_GRN_ROCK_DIRT    (0x0A01U) /* [161] DID:2943, Byte:#6, b1 [GREEN  :Rock and Dirt Mode]                    */
#define TT_IOR_D2943_B06_2_GRN_MUD_SAND     (0x0A02U) /* [162] DID:2943, Byte:#6, b2 [GREEN  :Mud and Sand Mode]                     */
#define TT_IOR_D2943_B06_3_GRN_AST          (0x0A03U) /* [163] DID:2943, Byte:#6, b3 [GREEN  :AST]                                   */
#define TT_IOR_D2943_B06_4_YEL_STR_HEAT     (0x0A04U) /* [164] DID:2943, Byte:#6, b4 [YELLOW :Steering Heater]                       */
#define TT_IOR_D2943_B06_5_YEL_NEELDOWN     (0x0A05U) /* [165] DID:2943, Byte:#6, b5 [YELLOW :Neel Down mode]                        */
#define TT_IOR_D2943_B06_6_GRN_NEELDOWN     (0x0A06U) /* [166] DID:2943, Byte:#6, b6 [GREEN  :Neel Down mode]                        */
#define TT_IOR_D2943_B06_7_GRN_RIDE_MODE    (0x0A07U) /* [167] DID:2943, Byte:#6, b7 [GREEN  :Ride Mode]                             */

/*  DID 0x2951   */
#define TT_IOR_D2951_B06_0_GRN_LDASTR_AC    (0x0B00U) /* [176] DID:2951, Byte:#6, b0 [GREEN  :LDA Steering Support Active]           */
#define TT_IOR_D2951_B06_1_GRN_CRS_SET      (0x0B01U) /* [177] DID:2951, Byte:#6, b1 [GREEN  :Cruise Set Indicator]                  */
#define TT_IOR_D2951_B06_2_YEL_CC           (0x0B02U) /* [178] DID:2951, Byte:#6, b2 [YELLOW :Normal Cruise Control]                 */
#define TT_IOR_D2951_B06_3_GRN_CC           (0x0B03U) /* [179] DID:2951, Byte:#6, b3 [GREEN  :Normal Cruise Control]                 */
#define TT_IOR_D2951_B06_4_YEL_ACC          (0x0B04U) /* [180] DID:2951, Byte:#6, b4 [YELLOW :Adaptive Cruise Control]               */
#define TT_IOR_D2951_B06_5_GRN_ACC          (0x0B05U) /* [181] DID:2951, Byte:#6, b5 [GREEN  :Adaptive Cruise Control]               */
#define TT_IOR_D2951_B06_6_YEL_PCS_WRN      (0x0B06U) /* [182] DID:2951, Byte:#6, b6 [YELLOW :PCS Wrn]                               */
#define TT_IOR_D2951_B06_7_YEL_PCS_OFF      (0x0B07U) /* [183] DID:2951, Byte:#6, b7 [YELLOW :PCS OFF]                               */
#define TT_IOR_D2951_B08_0_YEL_WHI_LN_R     (0x0B08U) /* [184] DID:2951, Byte:#8, b0 [YELLOW :White Line of Road Right]              */
#define TT_IOR_D2951_B08_1_GRN_WHI_LN_R     (0x0B09U) /* [185] DID:2951, Byte:#8, b1 [GREEN  :White Line of Road Right]              */
#define TT_IOR_D2951_B08_2_YEL_WHI_LN_L     (0x0B0AU) /* [186] DID:2951, Byte:#8, b2 [YELLOW :White Line of Road Left]               */
#define TT_IOR_D2951_B08_3_GRN_WHI_LN_L     (0x0B0BU) /* [187] DID:2951, Byte:#8, b3 [GREEN  :White Line of Road Left]               */
#define TT_IOR_D2951_B08_4_YEL_LDA          (0x0B0CU) /* [188] DID:2951, Byte:#8, b4 [YELLOW :LDA]                                   */
#define TT_IOR_D2951_B08_5_GRN_LDA          (0x0B0DU) /* [189] DID:2951, Byte:#8, b5 [GREEN  :LDA]                                   */
#define TT_IOR_D2951_B08_6_YEL_LKA          (0x0B0EU) /* [190] DID:2951, Byte:#8, b6 [YELLOW :LKA]                                   */
#define TT_IOR_D2951_B08_7_GRN_LKA          (0x0B0FU) /* [191] DID:2951, Byte:#8, b7 [GREEN  :LKA]                                   */

/*  DID 0x2952   */
#define TT_IOR_D2952_B06_0_GRN_IPA          (0x0C00U) /* [192] DID:2952, Byte: #6, b0 [GREEN  :Intelligent Parking Assist]           */
#define TT_IOR_D2952_B06_1_YEL_ICS_OFF      (0x0C01U) /* [193] DID:2952, Byte: #6, b1 [YELLOW :Intelligent Clearance Sonar OFF]      */
#define TT_IOR_D2952_B06_2_GRN_CS_ACT       (0x0C02U) /* [194] DID:2952, Byte: #6, b2 [GREEN  :Clearance Sonar]                      */
#define TT_IOR_D2952_B06_3_GRN_RCTA_ACT     (0x0C03U) /* [195] DID:2952, Byte: #6, b3 [GREEN  :Rear Cross Traffic Alert]             */
#define TT_IOR_D2952_B06_4_YEL_BSM          (0x0C04U) /* [196] DID:2952, Byte: #6, b4 [YELLOW :Blind Spot Monitor]                   */
#define TT_IOR_D2952_B06_5_GRN_BSM          (0x0C05U) /* [197] DID:2952, Byte: #6, b5 [GREEN  :Blind Spot Monitor]                   */
#define TT_IOR_D2952_B06_6_YEL_ASL          (0x0C06U) /* [198] DID:2952, Byte: #6, b6 [YELLOW :Adjustable Speed Limiter]             */
#define TT_IOR_D2952_B06_7_GRN_ASL          (0x0C07U) /* [199] DID:2952, Byte: #6, b7 [GREEN  :Adjustable Speed Limiter]             */
#define TT_IOR_D2952_B08_0_YEL_BSM_OFF      (0x0C08U) /* [200] DID:2952, Byte: #8, b0 [YELLOW :BSM OFF]                              */
#define TT_IOR_D2952_B08_1_YEL_RCTA_OFF     (0x0C09U) /* [201] DID:2952, Byte: #8, b1 [YELLOW :Rear Cross Traffic Alert OFF]         */
#define TT_IOR_D2952_B08_2_YEL_CS_OFF       (0x0C0AU) /* [202] DID:2952, Byte: #8, b2 [YELLOW :Clearance Sonar OFF]                  */
#define TT_IOR_D2952_B08_3_WHT_LDA          (0x0C0BU) /* [203] DID:2952, Byte: #8, b3 [WHITE  :LDA]                                  */
#define TT_IOR_D2952_B08_4_GRN_NIGHT_V      (0x0C0CU) /* [204] DID:2952, Byte: #8, b4 [GREEN  :Night View]                           */
#define TT_IOR_D2952_B08_5_YEL_ERUN_CAN     (0x0C0DU) /* [205] DID:2952, Byte: #8, b5 [YELLOW :Ecorun System(Idle stop system) OFF]  */
#define TT_IOR_D2952_B08_6_GRN_ERUN_ACT     (0x0C0EU) /* [206] DID:2952, Byte: #8, b6 [GREEN  :Ecorun System(Idle stop system)]      */
#define TT_IOR_D2952_B08_7_YEL_BRAKE_OR     (0x0C0FU) /* [207] DID:2952, Byte: #8, b7 [YELLOW :Brake override system]                */
#define TT_IOR_D2952_B10_0_UNDEF            (0x0C10U) /* [200] DID:2952, Byte:#10, b0 [Undef  :Undef]                                */
#define TT_IOR_D2952_B10_1_UNDEF            (0x0C11U) /* [201] DID:2952, Byte:#10, b1 [Undef  :Undef]                                */
#define TT_IOR_D2952_B10_2_UNDEF            (0x0C12U) /* [202] DID:2952, Byte:#10, b2 [Undef  :Undef]                                */
#define TT_IOR_D2952_B10_3_UNDEF            (0x0C13U) /* [203] DID:2952, Byte:#10, b3 [Undef  :Undef]                                */
#define TT_IOR_D2952_B10_4_YEL_CS_ACT       (0x0C14U) /* [204] DID:2952, Byte:#10, b4 [Yellow :Clearance Sonar]                      */
#define TT_IOR_D2952_B10_5_GRN_PLUS_SUP     (0x0C15U) /* [205] DID:2952, Byte:#10, b5 [GREEN  :Plus Support                          */
#define TT_IOR_D2952_B10_6_YEL_ADAS_STS     (0x0C16U) /* [206] DID:2952, Byte:#10, b6 [YELLOW :ADAS Status                           */
#define TT_IOR_D2952_B10_7_YEL_RCD_OFF      (0x0C17U) /* [207] DID:2952, Byte:#10, b7 [YELLOW :RCD Off]                              */

/*  DID 0x2961   */
#define TT_IOR_D2961_B06_0_YEL_HV_OVHT      (0x0D00U) /* [208] DID:2961, Byte:#6, b0 [YELLOW :Hybrid Unit Overheat]                  */
#define TT_IOR_D2961_B06_1_YEL_BATTERY      (0x0D01U) /* [209] DID:2961, Byte:#6, b1 [YELLOW :Battery for Driving]                   */
#define TT_IOR_D2961_B06_2_GRN_BATTERY      (0x0D02U) /* [210] DID:2961, Byte:#6, b2 [GREEN  :Battery for Driving]                   */
#define TT_IOR_D2961_B06_3_YEL_HVSYS_MAL    (0x0D03U) /* [211] DID:2961, Byte:#6, b3 [YELLOW :Hybrid System Wrn]                     */
#define TT_IOR_D2961_B06_4_YEL_P_REQEST     (0x0D04U) /* [212] DID:2961, Byte:#6, b4 [YELLOW :Prange Request]                        */
#define TT_IOR_D2961_B06_5_GRN_EV_STATUS    (0x0D05U) /* [213] DID:2961, Byte:#6, b5 [GREEN  :EV Status Indicator]                   */
#define TT_IOR_D2961_B06_6_GRN_EV_MODE      (0x0D06U) /* [214] DID:2961, Byte:#6, b6 [GREEN  :EV Mode Indicator]                     */
#define TT_IOR_D2961_B06_7_GRN_READY        (0x0D07U) /* [215] DID:2961, Byte:#6, b7 [GREEN  :Ready Indicator]                       */
#define TT_IOR_D2961_B08_0_RED_PLUGIN       (0x0D08U) /* [216] DID:2961, Byte:#8, b0 [RED    :Plug-in]                               */
#define TT_IOR_D2961_B08_1_YEL_APRCH_MAL    (0x0D09U) /* [217] DID:2961, Byte:#8, b1 [YELLOW :Approch Wrn System Malfunction]        */
#define TT_IOR_D2961_B08_2_RED_HYDRO_WRN    (0x0D0AU) /* [218] DID:2961, Byte:#8, b2 [RED    :Hydrogen Wrn]                          */
#define TT_IOR_D2961_B08_3_YEL_PLUGIN       (0x0D0BU) /* [219] DID:2961, Byte:#8, b3 [YELLOW :Plug-in]                               */
#define TT_IOR_D2961_B08_4_GRN_PLUGIN       (0x0D0CU) /* [220] DID:2961, Byte:#8, b4 [GREEN  :Plug-in]                               */
#define TT_IOR_D2961_B08_5_YEL_RUNM_LIM     (0x0D0DU) /* [221] DID:2961, Byte:#8, b5 [YELLOW :Run mode Limit]                        */
#define TT_IOR_D2961_B08_6_YEL_SOCWRN       (0x0D0EU) /* [222] DID:2961, Byte:#8, b6 [YELLOW :SCO Wrn]                               */
#define TT_IOR_D2961_B08_7_YEL_APRCH_OFF    (0x0D0FU) /* [223] DID:2961, Byte:#8, b7 [YELLOW :Approch Wrn OFF]                       */

/*  DID 0x2971   */
#define TT_IOR_D2971_B06_0_XXX_UNDEF        (0x0E00U) /* [224] DID:2971, Byte:#6, b0 [Undef  :Undef]                                 */
#define TT_IOR_D2971_B06_1_XXX_UNDEF        (0x0E01U) /* [225] DID:2971, Byte:#6, b1 [Undef  :Undef]                                 */
#define TT_IOR_D2971_B06_2_XXX_UNDEF        (0x0E02U) /* [226] DID:2971, Byte:#6, b2 [Undef  :Undef]                                 */
#define TT_IOR_D2971_B06_3_XXX_UNDEF        (0x0E03U) /* [227] DID:2971, Byte:#6, b3 [Undef  :Undef]                                 */
#define TT_IOR_D2971_B06_4_XXX_UNDEF        (0x0E04U) /* [228] DID:2971, Byte:#6, b4 [Undef  :Undef]                                 */
#define TT_IOR_D2971_B06_5_XXX_UNDEF        (0x0E05U) /* [229] DID:2971, Byte:#6, b5 [Undef  :Undef]                                 */
#define TT_IOR_D2971_B06_6_XXX_UNDEF        (0x0E06U) /* [230] DID:2971, Byte:#6, b6 [Undef  :Undef]                                 */
#define TT_IOR_D2971_B06_7_XXX_UNDEF        (0x0E07U) /* [231] DID:2971, Byte:#6, b7 [Undef  :Undef]                                 */

/*  DID 0x2981   */
#define TT_IOR_D2981_B06_0_XXX_UNDEF        (0x0F00U) /* [240] DID:2981, Byte:#6, b0 [Undef  :Undef]                                 */
#define TT_IOR_D2981_B06_1_XXX_UNDEF        (0x0F01U) /* [241] DID:2981, Byte:#6, b1 [Undef  :Undef]                                 */
#define TT_IOR_D2981_B06_2_XXX_UNDEF        (0x0F02U) /* [242] DID:2981, Byte:#6, b2 [Undef  :Undef]                                 */
#define TT_IOR_D2981_B06_3_XXX_UNDEF        (0x0F03U) /* [243] DID:2981, Byte:#6, b3 [Undef  :Undef]                                 */
#define TT_IOR_D2981_B06_4_XXX_UNDEF        (0x0F04U) /* [244] DID:2981, Byte:#6, b4 [Undef  :Undef]                                 */
#define TT_IOR_D2981_B06_5_XXX_UNDEF        (0x0F05U) /* [245] DID:2981, Byte:#6, b5 [Undef  :Undef]                                 */
#define TT_IOR_D2981_B06_6_RED_CAHRGE       (0x0F06U) /* [246] DID:2981, Byte:#6, b6 [RED    :Charge]                                */
#define TT_IOR_D2981_B06_7_ALLON            (0x0F07U) /* [247] DID:2981, Byte:#6, b7 [Undef  :ALL Telltale ON]                       */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* TELLTALE_REQIDX_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  telltale.c                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
