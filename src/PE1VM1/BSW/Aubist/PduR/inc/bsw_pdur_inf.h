/* bsw_pdur_inf_h_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/PDUR/INF/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_PDUR_INF_H
#define BSW_PDUR_INF_H

#include <Std_Types.h>
#include <ComStack_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef PduIdType (*Bsw_PduR_GetIpduIdType)( PduIdType PduId );
typedef PduIdType (*Bsw_PduR_GetLpduIdType)( PduIdType PduId );

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Unit internal public definition */
PduIdType bsw_pdur_inf_GetIpduIdSingle( PduIdType PduId );
PduIdType bsw_pdur_inf_GetIpduIdMulti( PduIdType PduId );
PduIdType bsw_pdur_inf_ComGetLpduIdSingle( PduIdType PduId );
PduIdType bsw_pdur_inf_ComGetLpduIdMulti( PduIdType PduId );
PduIdType bsw_pdur_inf_LdComGetLpduIdMulti( PduIdType PduId );
PduIdType bsw_pdur_inf_Cdd1GetLpduIdMulti( PduIdType PduId );
PduIdType bsw_pdur_inf_Cdd2GetLpduIdMulti( PduIdType PduId );

/* Dummy function */
PduIdType bsw_pdur_inf_dummy_GetLpduId( PduIdType PduId );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst Bsw_PduR_GetIpduIdType bsw_pdur_rom_ptGetIpduIdFunc;
extern BswConst Bsw_PduR_GetLpduIdType bsw_pdur_rom_ptGetLpduIdFunc;
extern BswConst Bsw_PduR_GetLpduIdType bsw_pdur_rom_ptGetLIdFuncTbl[];

#endif /* BSW_PDUR_INF_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/03/07                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2024/10/07                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
