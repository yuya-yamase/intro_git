/* Crypto_83_sw_Cfg_Fixed_h_v2-0-0                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | Crypto_83_sw/Cfg_Fixed/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

#ifndef CRYPTO_83_SW_CFG_FIXED_H
#define CRYPTO_83_SW_CFG_FIXED_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Rte_Csm_Type.h>
#include <Crypto_83_sw.h>
#include "../cfg/Crypto_83_sw_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef P2FUNC(void, CRYPTO_83_sw_APPL_CODE, Crypto_83_sw_ErrorCalloutType)(Crypto_83_sw_Ab_ErrorStatusType udErrorStatus);
typedef P2FUNC(void, CRYPTO_83_sw_APPL_CODE, Crypto_83_sw_IntervalCalloutType)(void);

typedef struct {
    P2CONST(AB_83_ConstV Crypto_83_sw_ErrorCalloutType, TYPEDEF, CRYPTO_83_sw_CONFIG_DATA) ptConfig;
    uint32 u4ConfigNum;
} Crypto_83_sw_Cfg_ErrorCalloutConfigAccessType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CONST_CONFIG
#include <Crypto_83_sw_MemMap.h>

extern CONST(AB_83_ConstV Crypto_83_sw_Cfg_ErrorCalloutConfigAccessType, CRYPTO_83_sw_CONFIG_DATA) Crypto_83_sw_Cfg_stErrorCallout;
extern CONST(AB_83_ConstV Crypto_83_sw_IntervalCalloutType, CRYPTO_83_sw_CONFIG_DATA) Crypto_83_sw_Cfg_ptIntervalCalloutFunc;
extern CONST(AB_83_ConstV boolean, CRYPTO_83_sw_CONFIG_DATA) Crypto_83_sw_Cfg_bVersionInfoApi;

#define CRYPTO_83_sw_STOP_SEC_CONST_CONFIG
#include <Crypto_83_sw_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* CRYPTO_83_SW_CFG_FIXED_H */

/****************************************************************************/
/* History                                                                  */
/*  Version            :Date                                                */
/*  v2-0-0             :2022/09/26                                          */
/****************************************************************************/

/**** End of File ***********************************************************/
