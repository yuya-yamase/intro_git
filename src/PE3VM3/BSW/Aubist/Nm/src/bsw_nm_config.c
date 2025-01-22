/* bsw_nm_config_c_v3-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/NM/CONFIG/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <ComStack_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <cs/bsw_cs_system_memmap_pre.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"

#include <cs/bsw_cs_system_memmap_post.h>

#if ( BSW_BSWM_CS_FUNC_NM == BSW_USE )

#include <cs/bsw_cs_system_memmap_pre.h>

#include <nm/bsw_nmstack_types.h>
#include <nm/bsw_nm.h>
#include "../inc/bsw_nm_status.h"
#include "../inc/bsw_nm_sw.h"
#include "../inc/bsw_nm_coord.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_connector.h"

#if ( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#include "../../Com/inc/bsw_com_config.h"
#endif
#include "../inc/bsw_nm_config.h"

#if( BSW_BSWM_CS_FUNC_CAN == BSW_USE )
#include <canif/bsw_canif.h>
#include <cannm/bsw_cannm.h>
#include <cannm/bsw_cannm_cbk.h>
#endif /* BSW_BSWM_CS_FUNC_CAN == BSW_USE */

#include <cs/bsw_cs_system_memmap_post.h>

#if( BSW_BSWM_CS_FUNC_ETH == BSW_USE )
#include <udpnm/bsw_udpnm.h>
#include <udpnm/bsw_udpnm_cbk.h>
#endif /* BSW_BSWM_CS_FUNC_ETH == BSW_USE */

#if( BSW_BSWM_CS_FUNC_LIN == BSW_USE )
#include <linnm/bsw_linnm.h>
#endif /* BSW_BSWM_CS_FUNC_LIN == BSW_USE */

#if ( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
#include <bswm_vps/bsw_bswm_vps_cbk.h>
#endif

#include <cs/bsw_cs_system_memmap_pre.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_NM_CHNUM                       (BSW_COMM_CHNUM)
#define BSW_NM_TYPE_USE(type)              (BSW_COMM_BUS_TYPE_USE(type))

#define BSW_NM_u2IMM_COUNT                 ((BswU2)1U)

#if( BSW_BSWM_CS_FUNC_COM == BSW_USE )
#define BSW_NM_EVTWAKEUPFRAME_USE    (BSW_COM_EVENTWAKEUPFRAME_USE)
#else
#define BSW_NM_EVTWAKEUPFRAME_USE    (BSW_NOUSE)
#endif

/* Protocol Index, Public function table size (Editing is required when adding protocols) */
#define BSW_NM_FUNCTBL_NONE            (0U)
#define BSW_NM_FUNCTBL_CAN             (1U)
#define BSW_NM_FUNCTBL_LIN             (2U)
#define BSW_NM_FUNCTBL_UDP             (3U)
#define BSW_NM_FUNCTBL_SIZE            (4U)

/* Channel to Protocol Index Conversion (Editing is required when adding protocols) */
#define BSW_NM_IDX_NM(ch)             (BSW_NM_IDX_CONV_CAN(ch))
#define BSW_NM_IDX_CONV_CAN(ch)       ((BSW_NM_TYPE(ch) == BSW_COMM_BUS_TYPE_CAN)  ? BSW_NM_FUNCTBL_CAN  : BSW_NM_IDX_CONV_LIN(ch))
#define BSW_NM_IDX_CONV_LIN(ch)       ((BSW_NM_TYPE(ch) == BSW_COMM_BUS_TYPE_LIN)  ? BSW_NM_FUNCTBL_LIN  : BSW_NM_IDX_CONV_UDP(ch))
#define BSW_NM_IDX_CONV_UDP(ch)       ((BSW_NM_TYPE(ch) == BSW_COMM_BUS_TYPE_ETH)  ? BSW_NM_FUNCTBL_UDP  : BSW_NM_FUNCTBL_NONE)

/* Shutdown timer time */
#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH0 > BSW_NM_CFG_SHUTDOWN_TIME_CH1 )
#define BSW_NM_MAX_SHUTDOWN_TIM_0_1     BSW_NM_CFG_SHUTDOWN_TIME_CH0
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_0_1     BSW_NM_CFG_SHUTDOWN_TIME_CH1
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH0 > BSW_NM_CFG_SHUTDOWN_TIME_CH1 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH2 > BSW_NM_CFG_SHUTDOWN_TIME_CH3 )
#define BSW_NM_MAX_SHUTDOWN_TIM_2_3     BSW_NM_CFG_SHUTDOWN_TIME_CH2
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_2_3     BSW_NM_CFG_SHUTDOWN_TIME_CH3
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH2 > BSW_NM_CFG_SHUTDOWN_TIME_CH3 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH4 > BSW_NM_CFG_SHUTDOWN_TIME_CH5 )
#define BSW_NM_MAX_SHUTDOWN_TIM_4_5     BSW_NM_CFG_SHUTDOWN_TIME_CH4
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_4_5     BSW_NM_CFG_SHUTDOWN_TIME_CH5
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH4 > BSW_NM_CFG_SHUTDOWN_TIME_CH5 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH6 > BSW_NM_CFG_SHUTDOWN_TIME_CH7 )
#define BSW_NM_MAX_SHUTDOWN_TIM_6_7     BSW_NM_CFG_SHUTDOWN_TIME_CH6
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_6_7     BSW_NM_CFG_SHUTDOWN_TIME_CH7
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH6 > BSW_NM_CFG_SHUTDOWN_TIME_CH7 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH8 > BSW_NM_CFG_SHUTDOWN_TIME_CH9 )
#define BSW_NM_MAX_SHUTDOWN_TIM_8_9     BSW_NM_CFG_SHUTDOWN_TIME_CH8
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_8_9     BSW_NM_CFG_SHUTDOWN_TIME_CH9
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH8 > BSW_NM_CFG_SHUTDOWN_TIME_CH9 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH10 > BSW_NM_CFG_SHUTDOWN_TIME_CH11 )
#define BSW_NM_MAX_SHUTDOWN_TIM_10_11   BSW_NM_CFG_SHUTDOWN_TIME_CH10
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_10_11   BSW_NM_CFG_SHUTDOWN_TIME_CH11
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH10 > BSW_NM_CFG_SHUTDOWN_TIME_CH11 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH12 > BSW_NM_CFG_SHUTDOWN_TIME_CH13 )
#define BSW_NM_MAX_SHUTDOWN_TIM_12_13   BSW_NM_CFG_SHUTDOWN_TIME_CH12
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_12_13   BSW_NM_CFG_SHUTDOWN_TIME_CH13
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH12 > BSW_NM_CFG_SHUTDOWN_TIME_CH13 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH14 > BSW_NM_CFG_SHUTDOWN_TIME_CH15 )
#define BSW_NM_MAX_SHUTDOWN_TIM_14_15   BSW_NM_CFG_SHUTDOWN_TIME_CH14
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_14_15   BSW_NM_CFG_SHUTDOWN_TIME_CH15
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH14 > BSW_NM_CFG_SHUTDOWN_TIME_CH15 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH16 > BSW_NM_CFG_SHUTDOWN_TIME_CH17 )
#define BSW_NM_MAX_SHUTDOWN_TIM_16_17   BSW_NM_CFG_SHUTDOWN_TIME_CH16
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_16_17   BSW_NM_CFG_SHUTDOWN_TIME_CH17
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH16 > BSW_NM_CFG_SHUTDOWN_TIME_CH17 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH18 > BSW_NM_CFG_SHUTDOWN_TIME_CH19 )
#define BSW_NM_MAX_SHUTDOWN_TIM_18_19   BSW_NM_CFG_SHUTDOWN_TIME_CH18
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_18_19   BSW_NM_CFG_SHUTDOWN_TIME_CH19
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH18 > BSW_NM_CFG_SHUTDOWN_TIME_CH19 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH20 > BSW_NM_CFG_SHUTDOWN_TIME_CH21 )
#define BSW_NM_MAX_SHUTDOWN_TIM_20_21   BSW_NM_CFG_SHUTDOWN_TIME_CH20
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_20_21   BSW_NM_CFG_SHUTDOWN_TIME_CH21
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH20 > BSW_NM_CFG_SHUTDOWN_TIME_CH21 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH22 > BSW_NM_CFG_SHUTDOWN_TIME_CH23 )
#define BSW_NM_MAX_SHUTDOWN_TIM_22_23   BSW_NM_CFG_SHUTDOWN_TIME_CH22
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_22_23   BSW_NM_CFG_SHUTDOWN_TIME_CH23
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH22 > BSW_NM_CFG_SHUTDOWN_TIME_CH23 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH24 > BSW_NM_CFG_SHUTDOWN_TIME_CH25 )
#define BSW_NM_MAX_SHUTDOWN_TIM_24_25   BSW_NM_CFG_SHUTDOWN_TIME_CH24
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_24_25   BSW_NM_CFG_SHUTDOWN_TIME_CH25
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH24 > BSW_NM_CFG_SHUTDOWN_TIME_CH25 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH26 > BSW_NM_CFG_SHUTDOWN_TIME_CH27 )
#define BSW_NM_MAX_SHUTDOWN_TIM_26_27   BSW_NM_CFG_SHUTDOWN_TIME_CH26
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_26_27   BSW_NM_CFG_SHUTDOWN_TIME_CH27
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH26 > BSW_NM_CFG_SHUTDOWN_TIME_CH27 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH28 > BSW_NM_CFG_SHUTDOWN_TIME_CH29 )
#define BSW_NM_MAX_SHUTDOWN_TIM_28_29   BSW_NM_CFG_SHUTDOWN_TIME_CH28
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_28_29   BSW_NM_CFG_SHUTDOWN_TIME_CH29
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH28 > BSW_NM_CFG_SHUTDOWN_TIME_CH29 ) */

#if ( BSW_NM_CFG_SHUTDOWN_TIME_CH30 > BSW_NM_CFG_SHUTDOWN_TIME_CH31 )
#define BSW_NM_MAX_SHUTDOWN_TIM_30_31   BSW_NM_CFG_SHUTDOWN_TIME_CH30
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_30_31   BSW_NM_CFG_SHUTDOWN_TIME_CH31
#endif /*  ( BSW_NM_CFG_SHUTDOWN_TIME_CH30 > BSW_NM_CFG_SHUTDOWN_TIME_CH31 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_0_1 > BSW_NM_MAX_SHUTDOWN_TIM_2_3 )
#define BSW_NM_MAX_SHUTDOWN_TIM_0_3     BSW_NM_MAX_SHUTDOWN_TIM_0_1
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_0_3     BSW_NM_MAX_SHUTDOWN_TIM_2_3
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_0_1 > BSW_NM_MAX_SHUTDOWN_TIM_2_3 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_4_5 > BSW_NM_MAX_SHUTDOWN_TIM_6_7 )
#define BSW_NM_MAX_SHUTDOWN_TIM_4_7     BSW_NM_MAX_SHUTDOWN_TIM_4_5
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_4_7     BSW_NM_MAX_SHUTDOWN_TIM_6_7
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_4_5 > BSW_NM_MAX_SHUTDOWN_TIM_6_7 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_8_9 > BSW_NM_MAX_SHUTDOWN_TIM_10_11 )
#define BSW_NM_MAX_SHUTDOWN_TIM_8_11    BSW_NM_MAX_SHUTDOWN_TIM_8_9
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_8_11    BSW_NM_MAX_SHUTDOWN_TIM_10_11
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_8_9 > BSW_NM_MAX_SHUTDOWN_TIM_10_11 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_12_13 > BSW_NM_MAX_SHUTDOWN_TIM_14_15 )
#define BSW_NM_MAX_SHUTDOWN_TIM_12_15   BSW_NM_MAX_SHUTDOWN_TIM_12_13
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_12_15   BSW_NM_MAX_SHUTDOWN_TIM_14_15
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_12_13 > BSW_NM_MAX_SHUTDOWN_TIM_14_15 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_16_17 > BSW_NM_MAX_SHUTDOWN_TIM_18_19 )
#define BSW_NM_MAX_SHUTDOWN_TIM_16_19   BSW_NM_MAX_SHUTDOWN_TIM_16_17
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_16_19   BSW_NM_MAX_SHUTDOWN_TIM_18_19
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_16_17 > BSW_NM_MAX_SHUTDOWN_TIM_18_19 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_20_21 > BSW_NM_MAX_SHUTDOWN_TIM_22_23 )
#define BSW_NM_MAX_SHUTDOWN_TIM_20_23   BSW_NM_MAX_SHUTDOWN_TIM_20_21
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_20_23   BSW_NM_MAX_SHUTDOWN_TIM_22_23
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_20_21 > BSW_NM_MAX_SHUTDOWN_TIM_22_23 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_24_25 > BSW_NM_MAX_SHUTDOWN_TIM_26_27 )
#define BSW_NM_MAX_SHUTDOWN_TIM_24_27   BSW_NM_MAX_SHUTDOWN_TIM_24_25
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_24_27   BSW_NM_MAX_SHUTDOWN_TIM_26_27
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_24_25 > BSW_NM_MAX_SHUTDOWN_TIM_26_27 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_28_29 > BSW_NM_MAX_SHUTDOWN_TIM_30_31 )
#define BSW_NM_MAX_SHUTDOWN_TIM_28_31   BSW_NM_MAX_SHUTDOWN_TIM_28_29
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_28_31   BSW_NM_MAX_SHUTDOWN_TIM_30_31
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_28_29 > BSW_NM_MAX_SHUTDOWN_TIM_30_31 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_0_3 > BSW_NM_MAX_SHUTDOWN_TIM_4_7 )
#define BSW_NM_MAX_SHUTDOWN_TIM_0_7     BSW_NM_MAX_SHUTDOWN_TIM_0_3
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_0_7     BSW_NM_MAX_SHUTDOWN_TIM_4_7
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_0_3 > BSW_NM_MAX_SHUTDOWN_TIM_4_7 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_8_11 > BSW_NM_MAX_SHUTDOWN_TIM_12_15 )
#define BSW_NM_MAX_SHUTDOWN_TIM_8_15    BSW_NM_MAX_SHUTDOWN_TIM_8_11
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_8_15    BSW_NM_MAX_SHUTDOWN_TIM_12_15
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_8_11 > BSW_NM_MAX_SHUTDOWN_TIM_12_15 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_16_19 > BSW_NM_MAX_SHUTDOWN_TIM_20_23 )
#define BSW_NM_MAX_SHUTDOWN_TIM_16_23   BSW_NM_MAX_SHUTDOWN_TIM_16_19
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_16_23   BSW_NM_MAX_SHUTDOWN_TIM_20_23
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_16_19 > BSW_NM_MAX_SHUTDOWN_TIM_20_23 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_24_27 > BSW_NM_MAX_SHUTDOWN_TIM_28_31 )
#define BSW_NM_MAX_SHUTDOWN_TIM_24_31   BSW_NM_MAX_SHUTDOWN_TIM_24_27
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_24_31   BSW_NM_MAX_SHUTDOWN_TIM_28_31
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_24_27 > BSW_NM_MAX_SHUTDOWN_TIM_28_31 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_0_7 > BSW_NM_MAX_SHUTDOWN_TIM_8_15 )
#define BSW_NM_MAX_SHUTDOWN_TIM_0_15    BSW_NM_MAX_SHUTDOWN_TIM_0_7
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_0_15    BSW_NM_MAX_SHUTDOWN_TIM_8_15
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_0_7 > BSW_NM_MAX_SHUTDOWN_TIM_8_15 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_16_23 > BSW_NM_MAX_SHUTDOWN_TIM_24_31 )
#define BSW_NM_MAX_SHUTDOWN_TIM_16_31   BSW_NM_MAX_SHUTDOWN_TIM_16_23
#else
#define BSW_NM_MAX_SHUTDOWN_TIM_16_31   BSW_NM_MAX_SHUTDOWN_TIM_24_31
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_16_23 > BSW_NM_MAX_SHUTDOWN_TIM_24_31 ) */

#if ( BSW_NM_MAX_SHUTDOWN_TIM_0_15 > BSW_NM_MAX_SHUTDOWN_TIM_16_31 )
#define BSW_NM_MAX_SHUTDOWN_TIM         BSW_NM_MAX_SHUTDOWN_TIM_0_15
#else
#define BSW_NM_MAX_SHUTDOWN_TIM         BSW_NM_MAX_SHUTDOWN_TIM_16_31
#endif /*  ( BSW_NM_MAX_SHUTDOWN_TIM_0_15 > BSW_NM_MAX_SHUTDOWN_TIM_16_31 ) */

/* Multi-stage sleep synchronization function */
#if (BSW_NM_SLEEPSYNC == BSW_USE)
#define BSW_NM_COORD_INITSLPSYNC_FUNC     ( &bsw_nm_coord_InitSleepSync )
#define BSW_NM_COORD_DELAYSLEEP_FUNC      ( &bsw_nm_coord_DelaySleep )
#define BSW_NM_STOPSYNCSLEEP_FUNC         ( &bsw_nm_coord_StopSyncSleep )
#define BSW_NM_STOPSLEEPDELAY_FUNC        ( &bsw_nm_coord_StopSleepDelay )
#else
#define BSW_NM_COORD_INITSLPSYNC_FUNC     ( &bsw_nm_coord_InitSleepSyncNone )
#define BSW_NM_COORD_DELAYSLEEP_FUNC      ( &bsw_nm_coord_DelaySleepNone )
#define BSW_NM_STOPSYNCSLEEP_FUNC         ( &bsw_nm_sw_StopSyncSleepNone )
#define BSW_NM_STOPSLEEPDELAY_FUNC        ( &bsw_nm_sw_StopSleepDelayNone )
#endif /*(BSW_NM_SLEEPSYNC == BSW_USE)*/

/* Request cooperation bus-sleep (Editing is required when adding protocols) */
#define BSW_NM_REQ_BUS_SYNC_CH(ch)        ( BSW_NM_CFG_REQ_BUS_SYNC_CH##ch )

#define BSW_NM_REQBUSSYNC_FUNC(ch)        ( (BSW_NM_REQ_BUS_SYNC_CH(ch) == BSW_NOUSE) ? &bsw_nm_coord_RequestBusSyncNone : &bsw_nm_sw_RequestBusSync )

/* PN multi-stage sleep synchronization function */
#if (BSW_NM_SYNC_PNC_SHUTDOWN == BSW_USE)
#define BSW_NM_COORD_CANCELPNSLP_FUNC     ( &bsw_nm_sw_CancelSyncPncSlp )
#else
#define BSW_NM_COORD_CANCELPNSLP_FUNC     ( &bsw_nm_coord_CancelSyncPncSlpNone )
#endif /*(BSW_NM_SYNC_PNC_SHUTDOWN == BSW_USE)*/

/* PN multi-stage sleep synchronization function */
#if (BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE)
#define BSW_NM_COORD_MAINFUNCCOBUS_FUNC   ( &BswM_VPS_MainFunctionCoBus )
#define BSW_NM_SW_TRXIND_FUNC             ( &BswM_VPS_NmRxIndication )
#else
#define BSW_NM_COORD_MAINFUNCCOBUS_FUNC   ( &bsw_nm_coord_MainFunctionCoBusNone )
#define BSW_NM_SW_TRXIND_FUNC             ( &bsw_nm_sw_NmRxIndicationNone )
#endif /*(BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE)*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*----------------------------*/
/* COORD unit              */
/*----------------------------*/
#if (BSW_NM_SLEEPSYNC == BSW_USE)
Bsw_Nm_CoordTimStsType      bsw_nm_coord_stTimSts[BSW_NM_CHNUM];                  /* Timer state  */
#endif /*(BSW_NM_SLEEPSYNC == BSW_USE)*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* Number of NM channels */
BswConst   BswU1               bsw_nm_status_u1ChNum     = (BswU1)BSW_NM_CHNUM;

/* Channel number -> Function table index conversion */
BswConst BswU1 bsw_nm_sw_u1Ch2IdxTbl[BSW_NM_CHNUM] = {
    (BswU1)BSW_NM_IDX_NM(0)
#if ( BSW_NM_CHNUM > 1U )
   ,(BswU1)BSW_NM_IDX_NM(1)
#endif
#if ( BSW_NM_CHNUM > 2U )
   ,(BswU1)BSW_NM_IDX_NM(2)
#endif
#if ( BSW_NM_CHNUM > 3U )
   ,(BswU1)BSW_NM_IDX_NM(3)
#endif
#if ( BSW_NM_CHNUM > 4U )
   ,(BswU1)BSW_NM_IDX_NM(4)
#endif
#if ( BSW_NM_CHNUM > 5U )
   ,(BswU1)BSW_NM_IDX_NM(5)
#endif
#if ( BSW_NM_CHNUM > 6U )
   ,(BswU1)BSW_NM_IDX_NM(6)
#endif
#if ( BSW_NM_CHNUM > 7U )
   ,(BswU1)BSW_NM_IDX_NM(7)
#endif
#if ( BSW_NM_CHNUM > 8U )
   ,(BswU1)BSW_NM_IDX_NM(8)
#endif
#if ( BSW_NM_CHNUM > 9U )
   ,(BswU1)BSW_NM_IDX_NM(9)
#endif
#if ( BSW_NM_CHNUM > 10U )
   ,(BswU1)BSW_NM_IDX_NM(10)
#endif
#if ( BSW_NM_CHNUM > 11U )
   ,(BswU1)BSW_NM_IDX_NM(11)
#endif
#if ( BSW_NM_CHNUM > 12U )
   ,(BswU1)BSW_NM_IDX_NM(12)
#endif
#if ( BSW_NM_CHNUM > 13U )
   ,(BswU1)BSW_NM_IDX_NM(13)
#endif
#if ( BSW_NM_CHNUM > 14U )
   ,(BswU1)BSW_NM_IDX_NM(14)
#endif
#if ( BSW_NM_CHNUM > 15U )
   ,(BswU1)BSW_NM_IDX_NM(15)
#endif
#if ( BSW_NM_CHNUM > 16U )
   ,(BswU1)BSW_NM_IDX_NM(16)
#endif
#if ( BSW_NM_CHNUM > 17U )
   ,(BswU1)BSW_NM_IDX_NM(17)
#endif
#if ( BSW_NM_CHNUM > 18U )
   ,(BswU1)BSW_NM_IDX_NM(18)
#endif
#if ( BSW_NM_CHNUM > 19U )
   ,(BswU1)BSW_NM_IDX_NM(19)
#endif
#if ( BSW_NM_CHNUM > 20U )
   ,(BswU1)BSW_NM_IDX_NM(20)
#endif
#if ( BSW_NM_CHNUM > 21U )
   ,(BswU1)BSW_NM_IDX_NM(21)
#endif
#if ( BSW_NM_CHNUM > 22U )
   ,(BswU1)BSW_NM_IDX_NM(22)
#endif
#if ( BSW_NM_CHNUM > 23U )
   ,(BswU1)BSW_NM_IDX_NM(23)
#endif
#if ( BSW_NM_CHNUM > 24U )
   ,(BswU1)BSW_NM_IDX_NM(24)
#endif
#if ( BSW_NM_CHNUM > 25U )
   ,(BswU1)BSW_NM_IDX_NM(25)
#endif
#if ( BSW_NM_CHNUM > 26U )
   ,(BswU1)BSW_NM_IDX_NM(26)
#endif
#if ( BSW_NM_CHNUM > 27U )
   ,(BswU1)BSW_NM_IDX_NM(27)
#endif
#if ( BSW_NM_CHNUM > 28U )
   ,(BswU1)BSW_NM_IDX_NM(28)
#endif
#if ( BSW_NM_CHNUM > 29U )
   ,(BswU1)BSW_NM_IDX_NM(29)
#endif
#if ( BSW_NM_CHNUM > 30U )
   ,(BswU1)BSW_NM_IDX_NM(30)
#endif
#if ( BSW_NM_CHNUM > 31U )
   ,(BswU1)BSW_NM_IDX_NM(31)
#endif
};

/* Unimplemented protocol Public function table */
static BswConst Bsw_Nm_FuncTblType bsw_nm_sw_ptNotInd_FuncTbl = 
{
      &bsw_nm_sw_PassiveStUpNone
    , &bsw_nm_sw_NetworkReqNone
    , &bsw_nm_sw_NetworkRelNone
    , &bsw_nm_sw_GetStateNone
};

#if ( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_Nm_ComFuncTblType bsw_nm_sw_ptNotInd_ComFuncTbl = 
{
      &bsw_nm_sw_DisableCommNone
    , &bsw_nm_sw_EnableCommNone
 };
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */

#if ( BSW_NM_USER_DATA == BSW_USE )
static BswConst Bsw_Nm_UsrDatFuncTblType bsw_nm_sw_ptNotInd_UsrDtFuncTbl = 
{
      &bsw_nm_sw_SetUserDataNone
    , &bsw_nm_sw_GetUserDataNone
 };
#endif /* ( BSW_NM_USER_DATA == BSW_USE ) */

#if ( BSW_NM_NODE_ID == BSW_USE )
static BswConst Bsw_Nm_NodeFuncTblType bsw_nm_sw_ptNotInd_NodeFuncTbl = 
{
      &bsw_nm_sw_GetNodeIdNone
    , &bsw_nm_sw_GetLNodeIdNone
 };
#endif /* ( BSW_NM_NODE_ID == BSW_USE ) */

#if ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) )
static BswConst Bsw_Nm_PduFuncTblType bsw_nm_sw_ptNotInd_PduFuncTbl = 
{
      &bsw_nm_sw_GetPduDataNone
 };
#endif /* ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) ) */

#if( BSW_NM_TYPE_USE(CAN) == BSW_USE )
/* NM Type:CanNm Public Function Table */
static BswConst Bsw_Nm_FuncTblType bsw_nm_sw_ptCan_FuncTbl = 
{
      &CanNm_PassiveStartUp
    , &CanNm_NetworkRequest
    , &CanNm_NetworkRelease
    , &CanNm_GetState
};

#if ( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_Nm_ComFuncTblType bsw_nm_sw_ptCan_ComFuncTbl = 
{
      &CanNm_DisableCommunication
    , &CanNm_EnableCommunication
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */
#if ( BSW_NM_USER_DATA == BSW_USE )
static BswConst Bsw_Nm_UsrDatFuncTblType bsw_nm_sw_ptCan_UsrDtFuncTbl = 
{
      &CanNm_SetUserData
    , &CanNm_GetUserData
 };
#endif /* ( BSW_NM_USER_DATA == BSW_USE ) */
#if ( BSW_NM_NODE_ID == BSW_USE )
static BswConst Bsw_Nm_NodeFuncTblType bsw_nm_sw_ptCan_NodeFuncTbl = 
{
      &CanNm_GetNodeIdentifier
    , &CanNm_GetLocalNodeIdentifier
 };
#endif /* ( BSW_NM_NODE_ID == BSW_USE ) */
#if ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) )
static BswConst Bsw_Nm_PduFuncTblType bsw_nm_sw_ptCan_PduFuncTbl = 
{
      &CanNm_GetPduData
 };
#endif /* ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) ) */
#endif /* ( BSW_NM_TYPE_USE(CAN) == BSW_USE ) */

#if( BSW_NM_TYPE_USE(LIN) == BSW_USE )
/* NM Type:LinNm Public Function Table */
static BswConst Bsw_Nm_FuncTblType bsw_nm_sw_ptLin_FuncTbl = 
{
      &LinNm_PassiveStartUp
    , &LinNm_NetworkRequest
    , &LinNm_NetworkRelease
    , &LinNm_GetState
};
#if ( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_Nm_ComFuncTblType bsw_nm_sw_Lin_ComFuncTbl = 
{
      &LinNm_DisableCommunication
    , &LinNm_EnableCommunication
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */
#if ( BSW_NM_USER_DATA == BSW_USE )
static BswConst Bsw_Nm_UsrDatFuncTblType bsw_nm_sw_ptLin_UsrDtFuncTbl = 
{
      &LinNm_SetUserData
    , &LinNm_GetUserData
 };
#endif /* ( BSW_NM_USER_DATA == BSW_USE ) */
#if ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) )
static BswConst Bsw_Nm_PduFuncTblType bsw_nm_sw_ptLin_PduFuncTbl = 
{
      &LinNm_GetPduData
 };
#endif /* ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) ) */
#endif /* ( BSW_NM_TYPE_USE(LIN) == BSW_USE ) */

#if( BSW_NM_TYPE_USE(ETH) == BSW_USE )
/* NM Type:UdpNm Public Function Table */
static BswConst Bsw_Nm_FuncTblType bsw_nm_sw_ptUdp_FuncTbl = 
{
      &UdpNm_PassiveStartUp
    , &UdpNm_NetworkRequest
    , &UdpNm_NetworkRelease
    , &UdpNm_GetState
};
#if ( BSW_NM_COM_CONTROL == BSW_USE )
static BswConst Bsw_Nm_ComFuncTblType bsw_nm_sw_ptUdp_ComFuncTbl = 
{
      &UdpNm_DisableCommunication
    , &UdpNm_EnableCommunication
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */
#if ( BSW_NM_USER_DATA == BSW_USE )
static BswConst Bsw_Nm_UsrDatFuncTblType bsw_nm_sw_ptUdp_UsrDtFuncTbl = 
{
      &UdpNm_SetUserData
    , &UdpNm_GetUserData
 };
#endif /* ( BSW_NM_USER_DATA == BSW_USE ) */
#if ( BSW_NM_NODE_ID == BSW_USE )
static BswConst Bsw_Nm_NodeFuncTblType bsw_nm_sw_ptUdp_NodeFuncTbl = 
{
      &UdpNm_GetNodeIdentifier
    , &UdpNm_GetLocalNodeIdentifier
 };
#endif /* ( BSW_NM_NODE_ID == BSW_USE ) */
#if ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) )
static BswConst Bsw_Nm_PduFuncTblType bsw_nm_sw_ptUdp_PduFuncTbl = 
{
      &UdpNm_GetPduData
 };
#endif /* ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) ) */
#endif /* ( BSW_NM_TYPE_USE(ETH) == BSW_USE ) */

/* Public function table (Editing is required when adding protocols) */
BswConst Bsw_Nm_FuncTblType* BswConst bsw_nm_sw_ptFuncTbl[BSW_NM_FUNCTBL_SIZE] = {
    &bsw_nm_sw_ptNotInd_FuncTbl

#if ( BSW_NM_TYPE_USE(CAN)  == BSW_USE )
   ,&bsw_nm_sw_ptCan_FuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_FuncTbl
#endif

#if ( BSW_NM_TYPE_USE(LIN)  == BSW_USE )
   ,&bsw_nm_sw_ptLin_FuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_FuncTbl
#endif

#if ( BSW_NM_TYPE_USE(ETH)  == BSW_USE )
   ,&bsw_nm_sw_ptUdp_FuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_FuncTbl
#endif
};

#if ( BSW_NM_COM_CONTROL == BSW_USE )
/* Public function table for communication restriction (Editing is required when adding protocols) */
BswConst Bsw_Nm_ComFuncTblType* BswConst bsw_nm_sw_ptComFuncTbl[BSW_NM_FUNCTBL_SIZE] = {
    &bsw_nm_sw_ptNotInd_ComFuncTbl
#if ( BSW_NM_TYPE_USE(CAN)  == BSW_USE )
   ,&bsw_nm_sw_ptCan_ComFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_ComFuncTbl
#endif
#if ( BSW_NM_TYPE_USE(LIN)  == BSW_USE )
   ,&bsw_nm_sw_Lin_ComFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_ComFuncTbl
#endif
#if ( BSW_NM_TYPE_USE(ETH)  == BSW_USE )
   ,&bsw_nm_sw_ptUdp_ComFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_ComFuncTbl
#endif
};
#endif /* ( BSW_NM_COM_CONTROL == BSW_USE ) */

#if ( BSW_NM_USER_DATA == BSW_USE )
/* Table of user data publishing functions (Editing is required when adding protocols) */
BswConst Bsw_Nm_UsrDatFuncTblType* BswConst bsw_nm_sw_ptUsrDatFuncTbl[BSW_NM_FUNCTBL_SIZE] = {
    &bsw_nm_sw_ptNotInd_UsrDtFuncTbl
#if ( BSW_NM_TYPE_USE(CAN)  == BSW_USE )
   ,&bsw_nm_sw_ptCan_UsrDtFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_UsrDtFuncTbl
#endif
#if ( BSW_NM_TYPE_USE(LIN)  == BSW_USE )
   ,&bsw_nm_sw_ptLin_UsrDtFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_UsrDtFuncTbl
#endif
#if ( BSW_NM_TYPE_USE(ETH)  == BSW_USE )
   ,&bsw_nm_sw_ptUdp_UsrDtFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_UsrDtFuncTbl
#endif
};
#endif /* ( BSW_NM_USER_DATA == BSW_USE ) */

#if ( BSW_NM_NODE_ID == BSW_USE )
/* Node ID public function table (Editing is required when adding protocols) */
BswConst Bsw_Nm_NodeFuncTblType* BswConst bsw_nm_sw_ptNodeFuncTbl[BSW_NM_FUNCTBL_SIZE] = {
    &bsw_nm_sw_ptNotInd_NodeFuncTbl
#if ( BSW_NM_TYPE_USE(CAN)  == BSW_USE )
   ,&bsw_nm_sw_ptCan_NodeFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_NodeFuncTbl
#endif
   ,&bsw_nm_sw_ptNotInd_NodeFuncTbl
#if ( BSW_NM_TYPE_USE(ETH)  == BSW_USE )
   ,&bsw_nm_sw_ptUdp_NodeFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_NodeFuncTbl
#endif
};
#endif /* ( BSW_NM_NODE_ID == BSW_USE ) */

#if ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) )
/* NM-PDU public function table (Editing is required when adding protocols) */
BswConst Bsw_Nm_PduFuncTblType* BswConst bsw_nm_sw_ptPduFuncTbl[BSW_NM_FUNCTBL_SIZE] = {
    &bsw_nm_sw_ptNotInd_PduFuncTbl
#if ( BSW_NM_TYPE_USE(CAN)  == BSW_USE )
   ,&bsw_nm_sw_ptCan_PduFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_PduFuncTbl
#endif
#if ( BSW_NM_TYPE_USE(LIN)  == BSW_USE )
   ,&bsw_nm_sw_ptLin_PduFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_PduFuncTbl
#endif
#if ( BSW_NM_TYPE_USE(ETH)  == BSW_USE )
   ,&bsw_nm_sw_ptUdp_PduFuncTbl
#else
   ,&bsw_nm_sw_ptNotInd_PduFuncTbl
#endif
};
#endif /* ( ( BSW_NM_USER_DATA == BSW_USE ) || ( BSW_NM_NODE_ID == BSW_USE ) ) */

#if (BSW_NM_EVTWAKEUPFRAME_USE == BSW_USE)
/* Public function table (Editing is required when adding protocols) */
uint16 (* BswConst bsw_nm_sw_ptEvtWkupFuncTbl[BSW_NM_FUNCTBL_SIZE])( NetworkHandleType nmChannelHandle ) = {
    &bsw_nm_sw_TransmitEvWakeupNone
#if ( BSW_NM_TYPE_USE(CAN)  == BSW_USE )
   ,&CanNm_TransmitEvtWakeup
#else
   ,&bsw_nm_sw_TransmitEvWakeupNone
#endif
   ,&bsw_nm_sw_TransmitEvWakeupNone
   ,&bsw_nm_sw_TransmitEvWakeupNone
};
void (* BswConst bsw_nm_sw_ptEvtWkupClFuncTbl[BSW_NM_FUNCTBL_SIZE])( NetworkHandleType nmChannelHandle ) = {
    &bsw_nm_sw_CancelEvWakeupNone
#if ( BSW_NM_TYPE_USE(CAN)  == BSW_USE )
   ,&CanNm_CancelEvtWakeup
#else
   ,&bsw_nm_sw_CancelEvWakeupNone
#endif
   ,&bsw_nm_sw_CancelEvWakeupNone
   ,&bsw_nm_sw_CancelEvWakeupNone
};

#endif /* (BSW_NM_EVTWAKEUPFRAME_USE == BSW_USE) */

void  (* BswConst bsw_nm_coord_ptInitSlpSyncFunc)( void ) = BSW_NM_COORD_INITSLPSYNC_FUNC;
void  (* BswConst bsw_nm_coord_ptDelaySleepFunc)( void )  = BSW_NM_COORD_DELAYSLEEP_FUNC;
void  (* BswConst bsw_nm_sw_ptStopSyncSleepFunc)( NetworkHandleType NetworkHandle ) = BSW_NM_STOPSYNCSLEEP_FUNC;
void  (* BswConst bsw_nm_sw_ptStopSleepDelayFunc)( NetworkHandleType NetworkHandle ) = BSW_NM_STOPSLEEPDELAY_FUNC;

#if (BSW_NM_SLEEPSYNC == BSW_USE)
/* Public function table for setting SleepReadyBit (Editing is required when adding protocols) */
Std_ReturnType (* BswConst bsw_nm_sw_ptSetSlpRdyBitFuncTbl[BSW_NM_FUNCTBL_SIZE])( NetworkHandleType nmChannelHandle, boolean nmSleepReadyBit ) = {
    &bsw_nm_sw_SetSleepReadyBitNone
#if ( BSW_NM_TYPE_USE(CAN)  == BSW_USE )
   ,&CanNm_SetSleepReadyBit
#else
   ,&bsw_nm_sw_SetSleepReadyBitNone
#endif
   ,&bsw_nm_sw_SetSleepReadyBitNone
#if ( BSW_NM_TYPE_USE(ETH)  == BSW_USE )
   ,&UdpNm_SetSleepReadyBit
#else
   ,&bsw_nm_sw_SetSleepReadyBitNone
#endif
};

#if (BSW_NM_REQ_BUS_SYNC_USE == BSW_USE)
/* Function table for bus synchronization request (Editing is required when adding protocols) */
Std_ReturnType (* BswConst bsw_nm_sw_ptRqBusSyncFuncTbl[BSW_NM_FUNCTBL_SIZE])( NetworkHandleType nmChannelHandle ) = {
    &bsw_nm_sw_RequestBusSyncNone
#if ( BSW_NM_REQ_BUS_SYNC_USE_CAN == BSW_USE )
   ,&CanNm_RequestBusSynchronization
#else
   ,&bsw_nm_sw_RequestBusSyncNone
#endif
   ,&bsw_nm_sw_RequestBusSyncNone
#if ( BSW_NM_REQ_BUS_SYNC_USE_ETH == BSW_USE )
   ,&UdpNm_RequestBusSynchronization
#else
   ,&bsw_nm_sw_RequestBusSyncNone
#endif
};
#endif /* (BSW_NM_REQ_BUS_SYNC_USE == BSW_USE) */

/* Bus synchronization request fanction table */
Std_ReturnType  (* BswConst bsw_nm_coord_ptRqBusSyncFuncTbl[BSW_NM_CHNUM])( NetworkHandleType nmChannelHandle ) = {
    BSW_NM_REQBUSSYNC_FUNC(0)
#if( BSW_NM_CHNUM > 1U )
   ,BSW_NM_REQBUSSYNC_FUNC(1)
#endif /* ( BSW_NM_CHNUM > 1U ) */
#if( BSW_NM_CHNUM > 2U )
   ,BSW_NM_REQBUSSYNC_FUNC(2)
#endif /* ( BSW_NM_CHNUM > 2U ) */
#if( BSW_NM_CHNUM > 3U )
   ,BSW_NM_REQBUSSYNC_FUNC(3)
#endif /* ( BSW_NM_CHNUM > 3U ) */
#if( BSW_NM_CHNUM > 4U )
   ,BSW_NM_REQBUSSYNC_FUNC(4)
#endif /* ( BSW_NM_CHNUM > 4U ) */
#if( BSW_NM_CHNUM > 5U )
   ,BSW_NM_REQBUSSYNC_FUNC(5)
#endif /* ( BSW_NM_CHNUM > 5U ) */
#if( BSW_NM_CHNUM > 6U )
   ,BSW_NM_REQBUSSYNC_FUNC(6)
#endif /* ( BSW_NM_CHNUM > 6U ) */
#if( BSW_NM_CHNUM > 7U )
   ,BSW_NM_REQBUSSYNC_FUNC(7)
#endif /* ( BSW_NM_CHNUM > 7U ) */
#if( BSW_NM_CHNUM > 8U )
   ,BSW_NM_REQBUSSYNC_FUNC(8)
#endif /* ( BSW_NM_CHNUM > 8U ) */
#if( BSW_NM_CHNUM > 9U )
   ,BSW_NM_REQBUSSYNC_FUNC(9)
#endif /* ( BSW_NM_CHNUM > 9U ) */
#if( BSW_NM_CHNUM > 10U )
   ,BSW_NM_REQBUSSYNC_FUNC(10)
#endif /* ( BSW_NM_CHNUM > 10U ) */
#if( BSW_NM_CHNUM > 11U )
   ,BSW_NM_REQBUSSYNC_FUNC(11)
#endif /* ( BSW_NM_CHNUM > 11U ) */
#if( BSW_NM_CHNUM > 12U )
   ,BSW_NM_REQBUSSYNC_FUNC(12)
#endif /* ( BSW_NM_CHNUM > 12U ) */
#if( BSW_NM_CHNUM > 13U )
   ,BSW_NM_REQBUSSYNC_FUNC(13)
#endif /* ( BSW_NM_CHNUM > 13U ) */
#if( BSW_NM_CHNUM > 14U )
   ,BSW_NM_REQBUSSYNC_FUNC(14)
#endif /* ( BSW_NM_CHNUM > 14U ) */
#if( BSW_NM_CHNUM > 15U )
   ,BSW_NM_REQBUSSYNC_FUNC(15)
#endif /* ( BSW_NM_CHNUM > 15U ) */
#if( BSW_NM_CHNUM > 16U )
   ,BSW_NM_REQBUSSYNC_FUNC(16)
#endif /* ( BSW_NM_CHNUM > 16U ) */
#if( BSW_NM_CHNUM > 17U )
   ,BSW_NM_REQBUSSYNC_FUNC(17)
#endif /* ( BSW_NM_CHNUM > 17U ) */
#if( BSW_NM_CHNUM > 18U )
   ,BSW_NM_REQBUSSYNC_FUNC(18)
#endif /* ( BSW_NM_CHNUM > 18U ) */
#if( BSW_NM_CHNUM > 19U )
   ,BSW_NM_REQBUSSYNC_FUNC(19)
#endif /* ( BSW_NM_CHNUM > 19U ) */
#if( BSW_NM_CHNUM > 20U )
   ,BSW_NM_REQBUSSYNC_FUNC(20)
#endif /* ( BSW_NM_CHNUM > 20U ) */
#if( BSW_NM_CHNUM > 21U )
   ,BSW_NM_REQBUSSYNC_FUNC(21)
#endif /* ( BSW_NM_CHNUM > 21U ) */
#if( BSW_NM_CHNUM > 22U )
   ,BSW_NM_REQBUSSYNC_FUNC(22)
#endif /* ( BSW_NM_CHNUM > 22U ) */
#if( BSW_NM_CHNUM > 23U )
   ,BSW_NM_REQBUSSYNC_FUNC(23)
#endif /* ( BSW_NM_CHNUM > 23U ) */
#if( BSW_NM_CHNUM > 24U )
   ,BSW_NM_REQBUSSYNC_FUNC(24)
#endif /* ( BSW_NM_CHNUM > 24U ) */
#if( BSW_NM_CHNUM > 25U )
   ,BSW_NM_REQBUSSYNC_FUNC(25)
#endif /* ( BSW_NM_CHNUM > 25U ) */
#if( BSW_NM_CHNUM > 26U )
   ,BSW_NM_REQBUSSYNC_FUNC(26)
#endif /* ( BSW_NM_CHNUM > 26U ) */
#if( BSW_NM_CHNUM > 27U )
   ,BSW_NM_REQBUSSYNC_FUNC(27)
#endif /* ( BSW_NM_CHNUM > 27U ) */
#if( BSW_NM_CHNUM > 28U )
   ,BSW_NM_REQBUSSYNC_FUNC(28)
#endif /* ( BSW_NM_CHNUM > 28U ) */
#if( BSW_NM_CHNUM > 29U )
   ,BSW_NM_REQBUSSYNC_FUNC(29)
#endif /* ( BSW_NM_CHNUM > 29U ) */
#if( BSW_NM_CHNUM > 30U )
   ,BSW_NM_REQBUSSYNC_FUNC(30)
#endif /* ( BSW_NM_CHNUM > 30U ) */
#if( BSW_NM_CHNUM > 31U )
   ,BSW_NM_REQBUSSYNC_FUNC(31)
#endif /* ( BSW_NM_CHNUM > 31U ) */
};

BswConst BswU2 bsw_nm_coord_ShutdownTim[BSW_NM_CHNUM] =
{
    BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH0) + BSW_NM_u2IMM_COUNT
#if( BSW_NM_CHNUM > 1U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH1) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 1U ) */
#if( BSW_NM_CHNUM > 2U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH2) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 2U ) */
#if( BSW_NM_CHNUM > 3U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH3) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 3U ) */
#if( BSW_NM_CHNUM > 4U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH4) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 4U ) */
#if( BSW_NM_CHNUM > 5U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH5) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 5U ) */
#if( BSW_NM_CHNUM > 6U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH6) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 6U ) */
#if( BSW_NM_CHNUM > 7U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH7) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 7U ) */
#if( BSW_NM_CHNUM > 8U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH8) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 8U ) */
#if( BSW_NM_CHNUM > 9U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH9) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 9U ) */
#if( BSW_NM_CHNUM > 10U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH10) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 10U ) */
#if( BSW_NM_CHNUM > 11U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH11) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 11U ) */
#if( BSW_NM_CHNUM > 12U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH12) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 12U ) */
#if( BSW_NM_CHNUM > 13U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH13) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 13U ) */
#if( BSW_NM_CHNUM > 14U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH14) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 14U ) */
#if( BSW_NM_CHNUM > 15U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH15) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 15U ) */
#if( BSW_NM_CHNUM > 16U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH16) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 16U ) */
#if( BSW_NM_CHNUM > 17U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH17) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 17U ) */
#if( BSW_NM_CHNUM > 18U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH18) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 18U ) */
#if( BSW_NM_CHNUM > 19U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH19) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 19U ) */
#if( BSW_NM_CHNUM > 20U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH20) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 20U ) */
#if( BSW_NM_CHNUM > 21U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH21) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 21U ) */
#if( BSW_NM_CHNUM > 22U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH22) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 22U ) */
#if( BSW_NM_CHNUM > 23U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH23) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 23U ) */
#if( BSW_NM_CHNUM > 24U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH24) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 24U ) */
#if( BSW_NM_CHNUM > 25U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH25) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 25U ) */
#if( BSW_NM_CHNUM > 26U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH26) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 26U ) */
#if( BSW_NM_CHNUM > 27U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH27) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 27U ) */
#if( BSW_NM_CHNUM > 28U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH28) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 28U ) */
#if( BSW_NM_CHNUM > 29U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH29) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 29U ) */
#if( BSW_NM_CHNUM > 30U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH30) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 30U ) */
#if( BSW_NM_CHNUM > 31U )
   ,BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_CFG_SHUTDOWN_TIME_CH31) + BSW_NM_u2IMM_COUNT
#endif /* ( BSW_NM_CHNUM > 31U ) */
};

/* Maximum value of the shutdown timer */
BswConst BswU2 bsw_nm_coord_u2MaxShutdownTim      = (BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_NM_MAX_SHUTDOWN_TIM));
#endif /* (BSW_NM_SLEEPSYNC == BSW_USE) */

#if (BSW_NM_SYNC_PNC_SHUTDOWN == BSW_USE)
/* Cooperative PN sleep start timing notification function table(Editing is required when adding protocols) */
Std_ReturnType (* BswConst bsw_nm_sw_ptSyncPncShutdownFuncTbl[BSW_NM_FUNCTBL_SIZE])( NetworkHandleType nmNetworkHandle, PNCHandleType PNC ) = {
    &bsw_nm_sw_ReqSyncPncSlpNone
#if ( BSW_NM_TYPE_USE(CAN)  == BSW_USE )
   ,&CanNm_RequestSynchronizedPncShutdown
#else
   ,&bsw_nm_sw_ReqSyncPncSlpNone
#endif
   ,&bsw_nm_sw_ReqSyncPncSlpNone
#if ( BSW_NM_TYPE_USE(ETH)  == BSW_USE )
   ,&UdpNm_RequestSynchronizedPncShutdown
#else
   ,&bsw_nm_sw_ReqSyncPncSlpNone
#endif
};

/* Cooperative PN sleep cancellation function table(Editing is required when adding protocols) */
Std_ReturnType (* BswConst bsw_nm_sw_ptCancelReqSyncPncShutdownFuncTbl[BSW_NM_FUNCTBL_SIZE])( NetworkHandleType nmNetworkHandle, PNCHandleType PNC ) = {
    &bsw_nm_sw_CancelSyncPncSlpNone
#if ( BSW_NM_TYPE_USE(CAN)  == BSW_USE )
   ,&CanNm_CancelSynchronizedPncShutdown
#else
   ,&bsw_nm_sw_CancelSyncPncSlpNone
#endif
   ,&bsw_nm_sw_CancelSyncPncSlpNone
#if ( BSW_NM_TYPE_USE(ETH)  == BSW_USE )
   ,&UdpNm_CancelSynchronizedPncShutdown
#else
   ,&bsw_nm_sw_CancelSyncPncSlpNone
#endif
};
#endif /* (BSW_NM_SYNC_PNC_SHUTDOWN == BSW_USE) */

Std_ReturnType (* BswConst bsw_nm_coord_ptCancelSyncPncSlpFn)( NetworkHandleType nmNetworkHandle, PNCHandleType PNC ) = BSW_NM_COORD_CANCELPNSLP_FUNC;
void           (* BswConst bsw_nm_coord_ptMainFuncCoBusFn)( void ) = BSW_NM_COORD_MAINFUNCCOBUS_FUNC;
void           (* BswConst bsw_nm_sw_ptNmRxIndicationFn)(  NetworkHandleType nmNetworkHandle, BswConstR PduInfoType* PduInfoPtr ) = BSW_NM_SW_TRXIND_FUNC;


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#include <cs/bsw_cs_system_memmap_post.h>

#endif /* ( BSW_BSWM_CS_FUNC_NM == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-1-0          :2018/12/13                                             */
/*  v1-2-0          :2020/04/15                                             */
/*  v2-0-0          :2022/01/13                                             */
/*  v2-1-0          :2023/02/03                                             */
/*  v3-0-0          :2024/10/15                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
