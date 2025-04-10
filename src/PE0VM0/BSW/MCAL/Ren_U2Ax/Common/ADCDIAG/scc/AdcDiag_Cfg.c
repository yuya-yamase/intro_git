/* ADCDIAG-r04-303 */
/************************************************************************************************/
/*                                                                                              */
/*        ADC DIAG Driver : User Configuration                                                  */
/*                                                                                              */
/*        Copyright : DENSO CORPORATION                                                         */
/*                                                                                              */
/************************************************************************************************/

/*==============================================================================================*/
/*    include files                                                                             */
/*==============================================================================================*/
#include    "Std_Types.h"
#include    "Mcal_SpalCmn.h"
#include    "McalCommon_lib.h"

#include    "AdcDiag.h"
#include    "Reg_Adc.h"
/*==============================================================================================*/
/*    defines / data types / structs / unions    / macros                                       */
/*==============================================================================================*/
/* features */

#define ADCDIAG_START_SEC_CONST_8                /* ADC DIAG RODATA CONST 8bit Section Start */
#include "AdcDiag_MemMap.h"

static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group00ChannelList[ADCDIAG_CFG_GRP00_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP00_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group02ChannelList[ADCDIAG_CFG_GRP02_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP02_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group03ChannelList[ADCDIAG_CFG_GRP03_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP03_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group05ChannelList[ADCDIAG_CFG_GRP05_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP05_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group06ChannelList[ADCDIAG_CFG_GRP06_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP06_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group07ChannelList[ADCDIAG_CFG_GRP07_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP07_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group08ChannelList[ADCDIAG_CFG_GRP08_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP08_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group09ChannelList[ADCDIAG_CFG_GRP09_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP09_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group10ChannelList[ADCDIAG_CFG_GRP10_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP10_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group11ChannelList[ADCDIAG_CFG_GRP11_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP11_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group12ChannelList[ADCDIAG_CFG_GRP12_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP12_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group13ChannelList[ADCDIAG_CFG_GRP13_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP13_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group14ChannelList[ADCDIAG_CFG_GRP14_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP14_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group16ChannelList[ADCDIAG_CFG_GRP16_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP16_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group17ChannelList[ADCDIAG_CFG_GRP17_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP17_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group18ChannelList[ADCDIAG_CFG_GRP18_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP18_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group19ChannelList[ADCDIAG_CFG_GRP19_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP19_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group20ChannelList[ADCDIAG_CFG_GRP20_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP20_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group21ChannelList[ADCDIAG_CFG_GRP21_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP21_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group22ChannelList[ADCDIAG_CFG_GRP22_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP22_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group23ChannelList[ADCDIAG_CFG_GRP23_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP23_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group25ChannelList[ADCDIAG_CFG_GRP25_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP25_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group26ChannelList[ADCDIAG_CFG_GRP26_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP26_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group27ChannelList[ADCDIAG_CFG_GRP27_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP27_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group28ChannelList[ADCDIAG_CFG_GRP28_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP28_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group29ChannelList[ADCDIAG_CFG_GRP29_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP29_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group31ChannelList[ADCDIAG_CFG_GRP31_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP31_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group32ChannelList[ADCDIAG_CFG_GRP32_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP32_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group33ChannelList[ADCDIAG_CFG_GRP33_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP33_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group34ChannelList[ADCDIAG_CFG_GRP34_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP34_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group35ChannelList[ADCDIAG_CFG_GRP35_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP35_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group36ChannelList[ADCDIAG_CFG_GRP36_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP36_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group37ChannelList[ADCDIAG_CFG_GRP37_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP37_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group38ChannelList[ADCDIAG_CFG_GRP38_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP38_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group39ChannelList[ADCDIAG_CFG_GRP39_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP39_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group40ChannelList[ADCDIAG_CFG_GRP40_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP40_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group41ChannelList[ADCDIAG_CFG_GRP41_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP41_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group42ChannelList[ADCDIAG_CFG_GRP42_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP42_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group43ChannelList[ADCDIAG_CFG_GRP43_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP43_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group44ChannelList[ADCDIAG_CFG_GRP44_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP44_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group46ChannelList[ADCDIAG_CFG_GRP46_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP46_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group47ChannelList[ADCDIAG_CFG_GRP47_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP47_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group48ChannelList[ADCDIAG_CFG_GRP48_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP48_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group49ChannelList[ADCDIAG_CFG_GRP49_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP49_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group50ChannelList[ADCDIAG_CFG_GRP50_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP50_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group52ChannelList[ADCDIAG_CFG_GRP52_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP52_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group53ChannelList[ADCDIAG_CFG_GRP53_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP53_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group54ChannelList[ADCDIAG_CFG_GRP54_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP54_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group55ChannelList[ADCDIAG_CFG_GRP55_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP55_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group56ChannelList[ADCDIAG_CFG_GRP56_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP56_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group58ChannelList[ADCDIAG_CFG_GRP58_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP58_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group59ChannelList[ADCDIAG_CFG_GRP59_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP59_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group61ChannelList[ADCDIAG_CFG_GRP61_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP61_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group62ChannelList[ADCDIAG_CFG_GRP62_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP62_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group63ChannelList[ADCDIAG_CFG_GRP63_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP63_CNV_CH;
static CONST(uint8, ADC_CONST) s_cstAdcDiag_Group64ChannelList[ADCDIAG_CFG_GRP64_PHYSICAL_CH_NO] = ADCDIAG_CFG_GRP64_CNV_CH;

#define ADCDIAG_STOP_SEC_CONST_8                 /* ADC DIAG RODATA 8bit Section Stop */
#include "AdcDiag_MemMap.h"

#define ADCDIAG_START_SEC_CONST_UNSPECIFIED      /* ADC DIAG RODATA CONST UNSPECIFIED Section Start */
#include "AdcDiag_MemMap.h"

static CONST(AdcDiag_GroupConfigType, ADCDIAG_CONST) s_cstAdcDiag_GroupConfig[ADCDIAG_CFG_GRP_SIZE] = {
    {
        ADCDIAG_CFG_GRP00_HWUNIT,
        ADCDIAG_CFG_GRP00_SG,
        ADCDIAG_CFG_GRP00_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group00ChannelList,
        ADCDIAG_CFG_GRP00_START_POINTER,
        ADCDIAG_CFG_GRP00_STOP_POINTER,
        ADCDIAG_CFG_GRP00_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP01_HWUNIT,
        ADCDIAG_CFG_GRP01_SG,
        ADCDIAG_CFG_GRP01_PHYSICAL_CH_NO,
        NULL_PTR,
        ADCDIAG_CFG_GRP01_START_POINTER,
        ADCDIAG_CFG_GRP01_STOP_POINTER,
        ADCDIAG_CFG_GRP01_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP02_HWUNIT,
        ADCDIAG_CFG_GRP02_SG,
        ADCDIAG_CFG_GRP02_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group02ChannelList,
        ADCDIAG_CFG_GRP02_START_POINTER,
        ADCDIAG_CFG_GRP02_STOP_POINTER,
        ADCDIAG_CFG_GRP02_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP03_HWUNIT,
        ADCDIAG_CFG_GRP03_SG,
        ADCDIAG_CFG_GRP03_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group03ChannelList,
        ADCDIAG_CFG_GRP03_START_POINTER,
        ADCDIAG_CFG_GRP03_STOP_POINTER,
        ADCDIAG_CFG_GRP03_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP04_HWUNIT,
        ADCDIAG_CFG_GRP04_SG,
        ADCDIAG_CFG_GRP04_PHYSICAL_CH_NO,
        NULL_PTR,
        ADCDIAG_CFG_GRP04_START_POINTER,
        ADCDIAG_CFG_GRP04_STOP_POINTER,
        ADCDIAG_CFG_GRP04_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP05_HWUNIT,
        ADCDIAG_CFG_GRP05_SG,
        ADCDIAG_CFG_GRP05_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group05ChannelList,
        ADCDIAG_CFG_GRP05_START_POINTER,
        ADCDIAG_CFG_GRP05_STOP_POINTER,
        ADCDIAG_CFG_GRP05_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP06_HWUNIT,
        ADCDIAG_CFG_GRP06_SG,
        ADCDIAG_CFG_GRP06_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group06ChannelList,
        ADCDIAG_CFG_GRP06_START_POINTER,
        ADCDIAG_CFG_GRP06_STOP_POINTER,
        ADCDIAG_CFG_GRP06_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP07_HWUNIT,
        ADCDIAG_CFG_GRP07_SG,
        ADCDIAG_CFG_GRP07_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group07ChannelList,
        ADCDIAG_CFG_GRP07_START_POINTER,
        ADCDIAG_CFG_GRP07_STOP_POINTER,
        ADCDIAG_CFG_GRP07_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP08_HWUNIT,
        ADCDIAG_CFG_GRP08_SG,
        ADCDIAG_CFG_GRP08_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group08ChannelList,
        ADCDIAG_CFG_GRP08_START_POINTER,
        ADCDIAG_CFG_GRP08_STOP_POINTER,
        ADCDIAG_CFG_GRP08_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP09_HWUNIT,
        ADCDIAG_CFG_GRP09_SG,
        ADCDIAG_CFG_GRP09_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group09ChannelList,
        ADCDIAG_CFG_GRP09_START_POINTER,
        ADCDIAG_CFG_GRP09_STOP_POINTER,
        ADCDIAG_CFG_GRP09_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP10_HWUNIT,
        ADCDIAG_CFG_GRP10_SG,
        ADCDIAG_CFG_GRP10_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group10ChannelList,
        ADCDIAG_CFG_GRP10_START_POINTER,
        ADCDIAG_CFG_GRP10_STOP_POINTER,
        ADCDIAG_CFG_GRP10_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP11_HWUNIT,
        ADCDIAG_CFG_GRP11_SG,
        ADCDIAG_CFG_GRP11_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group11ChannelList,
        ADCDIAG_CFG_GRP11_START_POINTER,
        ADCDIAG_CFG_GRP11_STOP_POINTER,
        ADCDIAG_CFG_GRP11_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP12_HWUNIT,
        ADCDIAG_CFG_GRP12_SG,
        ADCDIAG_CFG_GRP12_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group12ChannelList,
        ADCDIAG_CFG_GRP12_START_POINTER,
        ADCDIAG_CFG_GRP12_STOP_POINTER,
        ADCDIAG_CFG_GRP12_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP13_HWUNIT,
        ADCDIAG_CFG_GRP13_SG,
        ADCDIAG_CFG_GRP13_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group13ChannelList,
        ADCDIAG_CFG_GRP13_START_POINTER,
        ADCDIAG_CFG_GRP13_STOP_POINTER,
        ADCDIAG_CFG_GRP13_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP14_HWUNIT,
        ADCDIAG_CFG_GRP14_SG,
        ADCDIAG_CFG_GRP14_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group14ChannelList,
        ADCDIAG_CFG_GRP14_START_POINTER,
        ADCDIAG_CFG_GRP14_STOP_POINTER,
        ADCDIAG_CFG_GRP14_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP15_HWUNIT,
        ADCDIAG_CFG_GRP15_SG,
        ADCDIAG_CFG_GRP15_PHYSICAL_CH_NO,
        NULL_PTR,
        ADCDIAG_CFG_GRP15_START_POINTER,
        ADCDIAG_CFG_GRP15_STOP_POINTER,
        ADCDIAG_CFG_GRP15_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP16_HWUNIT,
        ADCDIAG_CFG_GRP16_SG,
        ADCDIAG_CFG_GRP16_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group16ChannelList,
        ADCDIAG_CFG_GRP16_START_POINTER,
        ADCDIAG_CFG_GRP16_STOP_POINTER,
        ADCDIAG_CFG_GRP16_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP17_HWUNIT,
        ADCDIAG_CFG_GRP17_SG,
        ADCDIAG_CFG_GRP17_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group17ChannelList,
        ADCDIAG_CFG_GRP17_START_POINTER,
        ADCDIAG_CFG_GRP17_STOP_POINTER,
        ADCDIAG_CFG_GRP17_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP18_HWUNIT,
        ADCDIAG_CFG_GRP18_SG,
        ADCDIAG_CFG_GRP18_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group18ChannelList,
        ADCDIAG_CFG_GRP18_START_POINTER,
        ADCDIAG_CFG_GRP18_STOP_POINTER,
        ADCDIAG_CFG_GRP18_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP19_HWUNIT,
        ADCDIAG_CFG_GRP19_SG,
        ADCDIAG_CFG_GRP19_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group19ChannelList,
        ADCDIAG_CFG_GRP19_START_POINTER,
        ADCDIAG_CFG_GRP19_STOP_POINTER,
        ADCDIAG_CFG_GRP19_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP20_HWUNIT,
        ADCDIAG_CFG_GRP20_SG,
        ADCDIAG_CFG_GRP20_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group20ChannelList,
        ADCDIAG_CFG_GRP20_START_POINTER,
        ADCDIAG_CFG_GRP20_STOP_POINTER,
        ADCDIAG_CFG_GRP20_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP21_HWUNIT,
        ADCDIAG_CFG_GRP21_SG,
        ADCDIAG_CFG_GRP21_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group21ChannelList,
        ADCDIAG_CFG_GRP21_START_POINTER,
        ADCDIAG_CFG_GRP21_STOP_POINTER,
        ADCDIAG_CFG_GRP21_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP22_HWUNIT,
        ADCDIAG_CFG_GRP22_SG,
        ADCDIAG_CFG_GRP22_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group22ChannelList,
        ADCDIAG_CFG_GRP22_START_POINTER,
        ADCDIAG_CFG_GRP22_STOP_POINTER,
        ADCDIAG_CFG_GRP22_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP23_HWUNIT,
        ADCDIAG_CFG_GRP23_SG,
        ADCDIAG_CFG_GRP23_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group23ChannelList,
        ADCDIAG_CFG_GRP23_START_POINTER,
        ADCDIAG_CFG_GRP23_STOP_POINTER,
        ADCDIAG_CFG_GRP23_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP24_HWUNIT,
        ADCDIAG_CFG_GRP24_SG,
        ADCDIAG_CFG_GRP24_PHYSICAL_CH_NO,
        NULL_PTR,
        ADCDIAG_CFG_GRP24_START_POINTER,
        ADCDIAG_CFG_GRP24_STOP_POINTER,
        ADCDIAG_CFG_GRP24_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP25_HWUNIT,
        ADCDIAG_CFG_GRP25_SG,
        ADCDIAG_CFG_GRP25_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group25ChannelList,
        ADCDIAG_CFG_GRP25_START_POINTER,
        ADCDIAG_CFG_GRP25_STOP_POINTER,
        ADCDIAG_CFG_GRP25_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP26_HWUNIT,
        ADCDIAG_CFG_GRP26_SG,
        ADCDIAG_CFG_GRP26_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group26ChannelList,
        ADCDIAG_CFG_GRP26_START_POINTER,
        ADCDIAG_CFG_GRP26_STOP_POINTER,
        ADCDIAG_CFG_GRP26_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP27_HWUNIT,
        ADCDIAG_CFG_GRP27_SG,
        ADCDIAG_CFG_GRP27_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group27ChannelList,
        ADCDIAG_CFG_GRP27_START_POINTER,
        ADCDIAG_CFG_GRP27_STOP_POINTER,
        ADCDIAG_CFG_GRP27_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP28_HWUNIT,
        ADCDIAG_CFG_GRP28_SG,
        ADCDIAG_CFG_GRP28_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group28ChannelList,
        ADCDIAG_CFG_GRP28_START_POINTER,
        ADCDIAG_CFG_GRP28_STOP_POINTER,
        ADCDIAG_CFG_GRP28_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP29_HWUNIT,
        ADCDIAG_CFG_GRP29_SG,
        ADCDIAG_CFG_GRP29_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group29ChannelList,
        ADCDIAG_CFG_GRP29_START_POINTER,
        ADCDIAG_CFG_GRP29_STOP_POINTER,
        ADCDIAG_CFG_GRP29_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP30_HWUNIT,
        ADCDIAG_CFG_GRP30_SG,
        ADCDIAG_CFG_GRP30_PHYSICAL_CH_NO,
        NULL_PTR,
        ADCDIAG_CFG_GRP30_START_POINTER,
        ADCDIAG_CFG_GRP30_STOP_POINTER,
        ADCDIAG_CFG_GRP30_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP31_HWUNIT,
        ADCDIAG_CFG_GRP31_SG,
        ADCDIAG_CFG_GRP31_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group31ChannelList,
        ADCDIAG_CFG_GRP31_START_POINTER,
        ADCDIAG_CFG_GRP31_STOP_POINTER,
        ADCDIAG_CFG_GRP31_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP32_HWUNIT,
        ADCDIAG_CFG_GRP32_SG,
        ADCDIAG_CFG_GRP32_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group32ChannelList,
        ADCDIAG_CFG_GRP32_START_POINTER,
        ADCDIAG_CFG_GRP32_STOP_POINTER,
        ADCDIAG_CFG_GRP32_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP33_HWUNIT,
        ADCDIAG_CFG_GRP33_SG,
        ADCDIAG_CFG_GRP33_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group33ChannelList,
        ADCDIAG_CFG_GRP33_START_POINTER,
        ADCDIAG_CFG_GRP33_STOP_POINTER,
        ADCDIAG_CFG_GRP33_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP34_HWUNIT,
        ADCDIAG_CFG_GRP34_SG,
        ADCDIAG_CFG_GRP34_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group34ChannelList,
        ADCDIAG_CFG_GRP34_START_POINTER,
        ADCDIAG_CFG_GRP34_STOP_POINTER,
        ADCDIAG_CFG_GRP34_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP35_HWUNIT,
        ADCDIAG_CFG_GRP35_SG,
        ADCDIAG_CFG_GRP35_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group35ChannelList,
        ADCDIAG_CFG_GRP35_START_POINTER,
        ADCDIAG_CFG_GRP35_STOP_POINTER,
        ADCDIAG_CFG_GRP35_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP36_HWUNIT,
        ADCDIAG_CFG_GRP36_SG,
        ADCDIAG_CFG_GRP36_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group36ChannelList,
        ADCDIAG_CFG_GRP36_START_POINTER,
        ADCDIAG_CFG_GRP36_STOP_POINTER,
        ADCDIAG_CFG_GRP36_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP37_HWUNIT,
        ADCDIAG_CFG_GRP37_SG,
        ADCDIAG_CFG_GRP37_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group37ChannelList,
        ADCDIAG_CFG_GRP37_START_POINTER,
        ADCDIAG_CFG_GRP37_STOP_POINTER,
        ADCDIAG_CFG_GRP37_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP38_HWUNIT,
        ADCDIAG_CFG_GRP38_SG,
        ADCDIAG_CFG_GRP38_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group38ChannelList,
        ADCDIAG_CFG_GRP38_START_POINTER,
        ADCDIAG_CFG_GRP38_STOP_POINTER,
        ADCDIAG_CFG_GRP38_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP39_HWUNIT,
        ADCDIAG_CFG_GRP39_SG,
        ADCDIAG_CFG_GRP39_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group39ChannelList,
        ADCDIAG_CFG_GRP39_START_POINTER,
        ADCDIAG_CFG_GRP39_STOP_POINTER,
        ADCDIAG_CFG_GRP39_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP40_HWUNIT,
        ADCDIAG_CFG_GRP40_SG,
        ADCDIAG_CFG_GRP40_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group40ChannelList,
        ADCDIAG_CFG_GRP40_START_POINTER,
        ADCDIAG_CFG_GRP40_STOP_POINTER,
        ADCDIAG_CFG_GRP40_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP41_HWUNIT,
        ADCDIAG_CFG_GRP41_SG,
        ADCDIAG_CFG_GRP41_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group41ChannelList,
        ADCDIAG_CFG_GRP41_START_POINTER,
        ADCDIAG_CFG_GRP41_STOP_POINTER,
        ADCDIAG_CFG_GRP41_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP42_HWUNIT,
        ADCDIAG_CFG_GRP42_SG,
        ADCDIAG_CFG_GRP42_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group42ChannelList,
        ADCDIAG_CFG_GRP42_START_POINTER,
        ADCDIAG_CFG_GRP42_STOP_POINTER,
        ADCDIAG_CFG_GRP42_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP43_HWUNIT,
        ADCDIAG_CFG_GRP43_SG,
        ADCDIAG_CFG_GRP43_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group43ChannelList,
        ADCDIAG_CFG_GRP43_START_POINTER,
        ADCDIAG_CFG_GRP43_STOP_POINTER,
        ADCDIAG_CFG_GRP43_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP44_HWUNIT,
        ADCDIAG_CFG_GRP44_SG,
        ADCDIAG_CFG_GRP44_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group44ChannelList,
        ADCDIAG_CFG_GRP44_START_POINTER,
        ADCDIAG_CFG_GRP44_STOP_POINTER,
        ADCDIAG_CFG_GRP44_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP45_HWUNIT,
        ADCDIAG_CFG_GRP45_SG,
        ADCDIAG_CFG_GRP45_PHYSICAL_CH_NO,
        NULL_PTR,
        ADCDIAG_CFG_GRP45_START_POINTER,
        ADCDIAG_CFG_GRP45_STOP_POINTER,
        ADCDIAG_CFG_GRP45_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP46_HWUNIT,
        ADCDIAG_CFG_GRP46_SG,
        ADCDIAG_CFG_GRP46_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group46ChannelList,
        ADCDIAG_CFG_GRP46_START_POINTER,
        ADCDIAG_CFG_GRP46_STOP_POINTER,
        ADCDIAG_CFG_GRP46_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP47_HWUNIT,
        ADCDIAG_CFG_GRP47_SG,
        ADCDIAG_CFG_GRP47_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group47ChannelList,
        ADCDIAG_CFG_GRP47_START_POINTER,
        ADCDIAG_CFG_GRP47_STOP_POINTER,
        ADCDIAG_CFG_GRP47_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP48_HWUNIT,
        ADCDIAG_CFG_GRP48_SG,
        ADCDIAG_CFG_GRP48_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group48ChannelList,
        ADCDIAG_CFG_GRP48_START_POINTER,
        ADCDIAG_CFG_GRP48_STOP_POINTER,
        ADCDIAG_CFG_GRP48_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP49_HWUNIT,
        ADCDIAG_CFG_GRP49_SG,
        ADCDIAG_CFG_GRP49_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group49ChannelList,
        ADCDIAG_CFG_GRP49_START_POINTER,
        ADCDIAG_CFG_GRP49_STOP_POINTER,
        ADCDIAG_CFG_GRP49_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP50_HWUNIT,
        ADCDIAG_CFG_GRP50_SG,
        ADCDIAG_CFG_GRP50_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group50ChannelList,
        ADCDIAG_CFG_GRP50_START_POINTER,
        ADCDIAG_CFG_GRP50_STOP_POINTER,
        ADCDIAG_CFG_GRP50_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP51_HWUNIT,
        ADCDIAG_CFG_GRP51_SG,
        ADCDIAG_CFG_GRP51_PHYSICAL_CH_NO,
        NULL_PTR,
        ADCDIAG_CFG_GRP51_START_POINTER,
        ADCDIAG_CFG_GRP51_STOP_POINTER,
        ADCDIAG_CFG_GRP51_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP52_HWUNIT,
        ADCDIAG_CFG_GRP52_SG,
        ADCDIAG_CFG_GRP52_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group52ChannelList,
        ADCDIAG_CFG_GRP52_START_POINTER,
        ADCDIAG_CFG_GRP52_STOP_POINTER,
        ADCDIAG_CFG_GRP52_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP53_HWUNIT,
        ADCDIAG_CFG_GRP53_SG,
        ADCDIAG_CFG_GRP53_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group53ChannelList,
        ADCDIAG_CFG_GRP53_START_POINTER,
        ADCDIAG_CFG_GRP53_STOP_POINTER,
        ADCDIAG_CFG_GRP53_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP54_HWUNIT,
        ADCDIAG_CFG_GRP54_SG,
        ADCDIAG_CFG_GRP54_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group54ChannelList,
        ADCDIAG_CFG_GRP54_START_POINTER,
        ADCDIAG_CFG_GRP54_STOP_POINTER,
        ADCDIAG_CFG_GRP54_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP55_HWUNIT,
        ADCDIAG_CFG_GRP55_SG,
        ADCDIAG_CFG_GRP55_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group55ChannelList,
        ADCDIAG_CFG_GRP55_START_POINTER,
        ADCDIAG_CFG_GRP55_STOP_POINTER,
        ADCDIAG_CFG_GRP55_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP56_HWUNIT,
        ADCDIAG_CFG_GRP56_SG,
        ADCDIAG_CFG_GRP56_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group56ChannelList,
        ADCDIAG_CFG_GRP56_START_POINTER,
        ADCDIAG_CFG_GRP56_STOP_POINTER,
        ADCDIAG_CFG_GRP56_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP57_HWUNIT,
        ADCDIAG_CFG_GRP57_SG,
        ADCDIAG_CFG_GRP57_PHYSICAL_CH_NO,
        NULL_PTR,
        ADCDIAG_CFG_GRP57_START_POINTER,
        ADCDIAG_CFG_GRP57_STOP_POINTER,
        ADCDIAG_CFG_GRP57_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP58_HWUNIT,
        ADCDIAG_CFG_GRP58_SG,
        ADCDIAG_CFG_GRP58_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group58ChannelList,
        ADCDIAG_CFG_GRP58_START_POINTER,
        ADCDIAG_CFG_GRP58_STOP_POINTER,
        ADCDIAG_CFG_GRP58_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP59_HWUNIT,
        ADCDIAG_CFG_GRP59_SG,
        ADCDIAG_CFG_GRP59_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group59ChannelList,
        ADCDIAG_CFG_GRP59_START_POINTER,
        ADCDIAG_CFG_GRP59_STOP_POINTER,
        ADCDIAG_CFG_GRP59_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP60_HWUNIT,
        ADCDIAG_CFG_GRP60_SG,
        ADCDIAG_CFG_GRP60_PHYSICAL_CH_NO,
        NULL_PTR,
        ADCDIAG_CFG_GRP60_START_POINTER,
        ADCDIAG_CFG_GRP60_STOP_POINTER,
        ADCDIAG_CFG_GRP60_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP61_HWUNIT,
        ADCDIAG_CFG_GRP61_SG,
        ADCDIAG_CFG_GRP61_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group61ChannelList,
        ADCDIAG_CFG_GRP61_START_POINTER,
        ADCDIAG_CFG_GRP61_STOP_POINTER,
        ADCDIAG_CFG_GRP61_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP62_HWUNIT,
        ADCDIAG_CFG_GRP62_SG,
        ADCDIAG_CFG_GRP62_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group62ChannelList,
        ADCDIAG_CFG_GRP62_START_POINTER,
        ADCDIAG_CFG_GRP62_STOP_POINTER,
        ADCDIAG_CFG_GRP62_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP63_HWUNIT,
        ADCDIAG_CFG_GRP63_SG,
        ADCDIAG_CFG_GRP63_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group63ChannelList,
        ADCDIAG_CFG_GRP63_START_POINTER,
        ADCDIAG_CFG_GRP63_STOP_POINTER,
        ADCDIAG_CFG_GRP63_DIAG_TYPE
    },
    {
        ADCDIAG_CFG_GRP64_HWUNIT,
        ADCDIAG_CFG_GRP64_SG,
        ADCDIAG_CFG_GRP64_PHYSICAL_CH_NO,
        s_cstAdcDiag_Group64ChannelList,
        ADCDIAG_CFG_GRP64_START_POINTER,
        ADCDIAG_CFG_GRP64_STOP_POINTER,
        ADCDIAG_CFG_GRP64_DIAG_TYPE
    }
};

static CONST(AdcDiag_HWConfigType, ADCDIAG_CONST) s_cstAdcDiag_HWConfig[ADC_HWUNIT_NUM] = {
        {
            ADC_ADCR2_DFMT_12BIT_FIXED_POINT,          /* Data Format ADC0 */
#if ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON )
            ADCDIAG_CFG_HW_UNIT0_USER_NOTIFICATION,    /* User Notification */
#endif /* ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON ) - */
            ADCDIAG_CFG_HW_UNIT0_USED                  /* Hw Unit Used */
        },
        {
            ADC_ADCR2_DFMT_12BIT_FIXED_POINT,          /* Data Format ADC1 */
#if ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON )
            ADCDIAG_CFG_HW_UNIT1_USER_NOTIFICATION,    /* User Notification */
#endif /* ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON ) - */
            ADCDIAG_CFG_HW_UNIT1_USED                  /* Hw Unit Used */
        },
        {
            ADC_ADCR2_DFMT_12BIT_FIXED_POINT,         /* Data Format ADC2 */
#if ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON )
            ADCDIAG_CFG_HW_UNIT2_USER_NOTIFICATION,   /* User Notification */
#endif /* ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON ) - */
            ADCDIAG_CFG_HW_UNIT2_USED                 /* Hw Unit Used */
        }
};

static CONST(AdcDiag_LevelVoltage, ADCDIAG_CONST) s_cstAdcDiag_THVoltageLevelCombinations[ADCDIAG_CFG_TH_VOLTAGE_LEVEL_TOTAL_COMBINATION] = {

    {ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL0, ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL1},
    {ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL1, ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL2},
    {ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL2, ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL3},
    {ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL3, ADCDIAG_CFG_PIN_LVL_VOLTAGE_LEVEL0}
};

static CONST(AdcDiag_TimeoutValue, ADCDIAG_CONST) s_cstAdcDiag_TimeoutValues = {
    ADCDIAG_CFG_SELFDIAG_WIRINGBREAK_TIMEOUT,
    ADCDIAG_CFG_SELFDIAG_TH_TIMEOUT,
    ADCDIAG_CFG_SELFDIAG_TH_VCH0_TIMEOUT,
    ADCDIAG_CFG_WIRINGBREAK_TIMEOUT,
    ADCDIAG_CFG_PINLEVEL_TIMEOUT,
    ADCDIAG_CFG_ADCORE_TIMEOUT,
    ADCDIAG_CFG_MODULE_RESET_TIMEOUT
};

#define ADCDIAG_STOP_SEC_CONST_UNSPECIFIED      /* ADC DIAG RODATA CONST UNSPECIFIED Section Stop */
#include "AdcDiag_MemMap.h"

#define ADCDIAG_START_SEC_CONST_16              /* ADC DIAG RODATA CONST 16bit Section Start */
#include "AdcDiag_MemMap.h"

static CONST(uint16, ADCDIAG_CONST) s_cstAdcDiag_WiringBreakRangesValue[u1ADCDIAG_WIRING_BREAK_TOTAL_COMBINATION][u1ADCDIAG_WIRING_BREAK_TOTAL_COMBINATION] = {
    {ADCDIAG_CFG_WIRING_BREAK_MIN_RANGE_VSS, ADCDIAG_CFG_WIRING_BREAK_MAX_RANGE_VSS},
    {ADCDIAG_CFG_WIRING_BREAK_MIN_RANGE_VCC, ADCDIAG_CFG_WIRING_BREAK_MAX_RANGE_VCC}
};

#define ADCDIAG_STOP_SEC_CONST_16                 /* ADC DIAG RODATA CONST 16bit Section Stop */
#include "AdcDiag_MemMap.h"

#define ADCDIAG_START_SEC_CONST_PTR               /* ADC DIAG RODATA CONST Pointer Section Start */
#include "AdcDiag_MemMap.h"

/* AdcDiag_ConfigType */
CONST(AdcDiag_ConfigType, ADCDIAG_CONST) cstAdcDiag_UserConfig = {
    &s_cstAdcDiag_GroupConfig[0],                   /* ADC Diag Group Configuration */
    &s_cstAdcDiag_HWConfig[0],                      /* ADC Diag HW Configuration */
    &s_cstAdcDiag_THVoltageLevelCombinations[0],    /* ADC Diag T&H Voltage Level Combinations used in PreAdcInit() */
    &s_cstAdcDiag_WiringBreakRangesValue[0],        /* ADC Diag Wiring Break Ranges Value */
    &s_cstAdcDiag_TimeoutValues                     /* ADC Diag Timeout Values */
};

#define ADCDIAG_STOP_SEC_CONST_PTR                 /* ADC DIAG RODATA CONST Pointer Section Stop */
#include "AdcDiag_MemMap.h"

/*---------------------------------- End Of File ------------------------------------------------*/
