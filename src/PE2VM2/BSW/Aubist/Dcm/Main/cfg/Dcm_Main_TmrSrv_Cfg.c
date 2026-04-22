/* Dcm_Main_TmrSrv_Cfg_c(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Main_TmrSrv_Cfg/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Main/cfg/Dcm_Main_TmrSrv_Cfg.h"

#include <Dcm.h>

#include <Dcm/Dcm_Dsl_Ctrl.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_M_TmrSrv_IdToIndex[ DCM_M_TMRSRV_DEFINED_ALL_ID_NUM ] =
{
    (uint8)0U,                      /* DCM_M_TMRID_RXFSTIMER            */
    (uint8)1U,                      /* DCM_M_TMRID_TXFSTIMER            */
    (uint8)2U,                      /* DCM_M_TMRID_P4TIMER              */
    (uint8)3U,                      /* DCM_M_TMRID_PAGEDBUFFERTIMER     */
    (uint8)4U,                      /* DCM_M_TMRID_TXIFFSTIMER          */
    (uint8)5U,                      /* DCM_M_TMRID_ROERETRY_TIMER       */
    (uint8)6U,                      /* DCM_M_TMRID_P2MINTIMER           */
    (uint8)7U,                      /* DCM_M_TMRID_P2TIMER              */
    (uint8)8U,                      /* DCM_M_TMRID_S3TIMER              */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV1    */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV2    */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV3    */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV4    */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV5    */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV6    */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV7    */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV8    */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV9    */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV10   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV11   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV12   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV13   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV14   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV15   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV16   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV17   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV18   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV19   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV20   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV21   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV22   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV23   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV24   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV25   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV26   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV27   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV28   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV29   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV30   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV31   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV32   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV33   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV34   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV35   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV36   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV37   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV38   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV39   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV40   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV41   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV42   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV43   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV44   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV45   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV46   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV47   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV48   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV49   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV50   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV51   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV52   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV53   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV54   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV55   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV56   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV57   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV58   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV59   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV60   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV61   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV62   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID27_DTMR_SECLV63   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_STORAGEMNG_READALLFS */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_STORAGEMNG_WRITEFS   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_SID86_INTERMESSAGE   */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT0         */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT1         */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT2         */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT3         */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT4         */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT5         */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT6         */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT7         */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT8         */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT9         */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT10        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT11        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT12        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT13        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT14        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT15        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT16        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT17        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT18        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT19        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT20        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT21        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT22        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT23        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT24        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT25        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT26        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT27        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT28        */
    DCM_M_TMRSRV_INVALID_VAL,       /* DCM_M_TMRID_AUTH_CLIENT29        */
    DCM_M_TMRSRV_INVALID_VAL        /* DCM_M_TMRID_SYNC_OSAP_DATA       */
};

CONST( AB_83_ConstV Dcm_M_TmrSrv_NoticeTableType, DCM_CONFIG_DATA ) Dcm_M_TmrSrv_NoticeTable[ DCM_M_TMRSRV_ID_NUM ] = 
{
    { &Dcm_Dsl_RxFailSafeTOCbk,            DCM_M_TMRID_RXFSTIMER            },
    { &Dcm_Dsl_TxFailSafeTOCbk,            DCM_M_TMRID_TXFSTIMER            },
    { &Dcm_Dsl_P4TOCbk,                    DCM_M_TMRID_P4TIMER              },
    { NULL_PTR,                            DCM_M_TMRID_PAGEDBUFFERTIMER     },
    { NULL_PTR,                            DCM_M_TMRID_TXIFFSTIMER          },
    { NULL_PTR,                            DCM_M_TMRID_ROERETRY_TIMER       },
    { &Dcm_Dsl_P2MinTOCbk,                 DCM_M_TMRID_P2MINTIMER           },
    { &Dcm_Dsl_P2TOCbk,                    DCM_M_TMRID_P2TIMER              },
    { &Dcm_Dsl_S3TOCbk,                    DCM_M_TMRID_S3TIMER              }};


CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_M_TmrSrv_u1IdNum = DCM_M_TMRSRV_ID_NUM;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
