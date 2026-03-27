/* IdsM_General_h_v2-0-2                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/General/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef IDSM_GENERAL_H
#define IDSM_GENERAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define IDSM_S_UNINIT           ((IdsM_StatusType)0x00U)
#define IDSM_S_INIT             ((IdsM_StatusType)0xE1U)
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
#define IDSM_S_RAMERROR         ((IdsM_StatusType)0xD2U)
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

#define IDSM_INVALID_TIMESTAMP  ((IdsM_TimestampType)0xFFFFFFFFFFFFFFFFU)
#define IDSM_INVALID_INDEX      ((uint16)0xFFFFU)

#if (IDSM_CFG_USE_IDSR == STD_ON)
#define IDSM_E_BUSY             ((Std_ReturnType)2U)
#endif  /* ( IDSM_CFG_USE_IDSR == STD_ON ) */

#define IDSM_BIT_SHIFT_2        ((uint8)2U)
#define IDSM_BIT_SHIFT_4        ((uint8)4U)
#define IDSM_BIT_SHIFT_6        ((uint8)6U)
#define IDSM_BIT_SHIFT_8        ((uint8)8U)
#if (IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE)
#define IDSM_BIT_SHIFT_16       ((uint8)16U)
#define IDSM_BIT_SHIFT_24       ((uint8)24U)
#define IDSM_BIT_SHIFT_32       ((uint8)32U)
#define IDSM_BIT_SHIFT_40       ((uint8)40U)
#define IDSM_BIT_SHIFT_48       ((uint8)48U)
#define IDSM_BIT_SHIFT_56       ((uint8)56U)
#endif  /* ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE ) */

#if (( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ))
#define IDSM_UINT16_MAX         ((uint16)0xFFFFU)
#endif  /* (( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )) */

#define IDSM_START_BLOCKSTATE   ((uint8)0U)
#if ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )
#define IDSM_START_TRAFFICLIMIT ((uint8)1U)
#endif /* ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
#define IDSM_START_THRESHOLD    ((uint8)3U)
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
#define IDSM_RED_INIT_U2     ((uint16)0xFFFFU)
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

#define IDSM_NO_COUNT           ((uint16)0x01)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8 IdsM_StatusType;
typedef uint8 IdsM_FilterResultType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
FUNC(void, IDSM_CODE) IdsM_General_SetRamError
(
    void
);
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* IDSM_GENERAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/*  v2-0-1     :2023/01/23                                                  */
/*  v2-0-2     :2023/02/24                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
