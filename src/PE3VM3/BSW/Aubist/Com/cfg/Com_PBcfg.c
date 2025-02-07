/* com_pbcfg_c_v3-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | COM/PBCFG/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_com_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#if (BSW_BSWM_CS_FUNC_COM == BSW_USE)

#include <com/bsw_com.h>
#include "Com_Cfg.h"
#include "../inc/bsw_com_st.h"
#include "../inc/bsw_com_tx.h"
#include "../inc/bsw_com_rx.h"
#include "../inc/bsw_com_fs.h"
#include "../inc/bsw_com_data.h"
#include "../inc/bsw_com_config.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
BswU1 bsw_com_data_u1MsgBuf[BSW_COM_MSGBUF_SIZE];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
BswConst BswU1 bsw_com_data_u1MsgBufInit[BSW_COM_MSGBUF_SIZE] = {
     (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [0] MSG_CDC1S04_TXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U                                                                        /* Padding Area */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [1] MSG_ABG1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [2] MSG_ABG1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [3] MSG_ABG1S09_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [4] MSG_ACN1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [5] MSG_ACN1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [6] MSG_ACN1S15_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [7] MSG_ACN1S25_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [8] MSG_ACN1S29_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [9] MSG_ADC1S27_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [10] MSG_ADC1S30_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [11] MSG_ADC1S31_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [12] MSG_ADU1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [13] MSG_ADU1S05_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [14] MSG_ADU1S06_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [15] MSG_BAT1E45_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [16] MSG_BAT1ED1_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [17] MSG_BAT1ED4_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [18] MSG_BAT1ED5_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [19] MSG_BAT1EDA_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [20] MSG_BAT1EDB_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [21] MSG_BAT1S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [22] MSG_BAT2ED2_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [23] MSG_BDB1F03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [24] MSG_BDB1S10_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [25] MSG_BDC1S22_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [26] MSG_BDC1S41_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x01U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [27] MSG_BDC1S81_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [28] MSG_BDC1SH8_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [29] MSG_BDF3S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [30] MSG_BDF3S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [31] MSG_BDR3S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [32] MSG_CMB1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [33] MSG_CMB1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [34] MSG_DCM1S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [35] MSG_DDM1S00_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [36] MSG_DDM1S09_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [37] MSG_DDM1S16_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [38] MSG_DDM1S35_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [39] MSG_DDM1SFG_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [40] MSG_DDM1SFH_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [41] MSG_DKY1S26_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [42] MSG_DS11S27_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [43] MSG_EBU1D01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [44] MSG_ECT1S93_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x80U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [45] MSG_EHV1E96_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [46] MSG_EHV1F02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [47] MSG_EHV1S23_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [48] MSG_EHV2G10_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [49] MSG_EHV2G20_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [50] MSG_EIM1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [51] MSG_ENG1C01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [52] MSG_ENG1C02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [53] MSG_ENG1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [54] MSG_ENG1D52_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [55] MSG_ENG1D53_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [56] MSG_ENG1D55_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [57] MSG_ENG1D56_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [58] MSG_ENG1D59_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [59] MSG_ENG1D60_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [60] MSG_ENG1S51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [61] MSG_EPS1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [62] MSG_FCM1C01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [63] MSG_FCM1S49_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xF8U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [64] MSG_FCM1S76_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [65] MSG_FCM1S79_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [66] MSG_FCM1S90_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [67] MSG_FCM1S95_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [68] MSG_IDT1S07_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [69] MSG_IDT1S15_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x7FU, (BswU1)0x80U, (BswU1)0x00U  /* [70] MSG_LRS1S01_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xC0U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [71] MSG_LRS1S03_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [72] MSG_LRS1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [73] MSG_MGC1F13_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [74] MSG_PDC1G01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [75] MSG_PWC1S41_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [76] MSG_RCP1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x7FU, (BswU1)0x80U, (BswU1)0x00U  /* [77] MSG_RRS1S01_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xC0U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [78] MSG_RRS1S03_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [79] MSG_RRS1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [80] MSG_RSE1G20_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [81] MSG_RSE1G24_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [82] MSG_RSE1G25_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [83] MSG_RSE1G26_RXCH0 */
    ,(BswU1)0x31U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [84] MSG_RSE1G29_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [85] MSG_RSE1S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [86] MSG_SCS1S10_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [87] MSG_VGR1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [88] MSG_VSC1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x80U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [89] MSG_VSC1G13_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [90] MSG_WIP1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [91] MSG_ZN11S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [92] MSG_ZN11S32_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [93] MSG_ZN11S63_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [94] MSG_ZN11S64_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [95] MSG_ZN11S65_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [96] MSG_ZN11S66_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [97] MSG_ZN11S67_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [98] MSG_ZN11SF6_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [99] MSG_ZN11SF7_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U                                                                        /* Padding Area */
};

#if (BSW_COM_CFG_FAILSAFE_SIZE != 0U)
BswConst BswU1 bsw_com_data_u1MsgBufFail[BSW_COM_FAILSAFE_SIZE] = {
     (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [0] MSG_CDC1S04_TXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U                                                                        /* Padding Area */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [1] MSG_ABG1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [2] MSG_ABG1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [3] MSG_ABG1S09_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [4] MSG_ACN1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [5] MSG_ACN1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [6] MSG_ACN1S15_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [7] MSG_ACN1S25_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [8] MSG_ACN1S29_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [9] MSG_ADC1S27_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [10] MSG_ADC1S30_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [11] MSG_ADC1S31_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [12] MSG_ADU1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [13] MSG_ADU1S05_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [14] MSG_ADU1S06_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [15] MSG_BAT1E45_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [16] MSG_BAT1ED1_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [17] MSG_BAT1ED4_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [18] MSG_BAT1ED5_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [19] MSG_BAT1EDA_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [20] MSG_BAT1EDB_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [21] MSG_BAT1S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [22] MSG_BAT2ED2_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [23] MSG_BDB1F03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [24] MSG_BDB1S10_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [25] MSG_BDC1S22_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [26] MSG_BDC1S41_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [27] MSG_BDC1S81_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [28] MSG_BDC1SH8_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [29] MSG_BDF3S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [30] MSG_BDF3S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [31] MSG_BDR3S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [32] MSG_CMB1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [33] MSG_CMB1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [34] MSG_DCM1S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [35] MSG_DDM1S00_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [36] MSG_DDM1S09_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [37] MSG_DDM1S16_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [38] MSG_DDM1S35_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [39] MSG_DDM1SFG_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [40] MSG_DDM1SFH_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [41] MSG_DKY1S26_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [42] MSG_DS11S27_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [43] MSG_EBU1D01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [44] MSG_ECT1S93_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [45] MSG_EHV1E96_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [46] MSG_EHV1F02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [47] MSG_EHV1S23_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [48] MSG_EHV2G10_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [49] MSG_EHV2G20_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [50] MSG_EIM1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [51] MSG_ENG1C01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [52] MSG_ENG1C02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [53] MSG_ENG1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [54] MSG_ENG1D52_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [55] MSG_ENG1D53_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [56] MSG_ENG1D55_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [57] MSG_ENG1D56_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [58] MSG_ENG1D59_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [59] MSG_ENG1D60_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [60] MSG_ENG1S51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [61] MSG_EPS1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [62] MSG_FCM1C01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [63] MSG_FCM1S49_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [64] MSG_FCM1S76_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [65] MSG_FCM1S79_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [66] MSG_FCM1S90_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [67] MSG_FCM1S95_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [68] MSG_IDT1S07_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [69] MSG_IDT1S15_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [70] MSG_LRS1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [71] MSG_LRS1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [72] MSG_LRS1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [73] MSG_MGC1F13_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [74] MSG_PDC1G01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [75] MSG_PWC1S41_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [76] MSG_RCP1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [77] MSG_RRS1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [78] MSG_RRS1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [79] MSG_RRS1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [80] MSG_RSE1G20_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [81] MSG_RSE1G24_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [82] MSG_RSE1G25_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [83] MSG_RSE1G26_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [84] MSG_RSE1G29_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [85] MSG_RSE1S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [86] MSG_SCS1S10_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [87] MSG_VGR1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [88] MSG_VSC1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [89] MSG_VSC1G13_RXCH0 */
    ,(BswU1)0xE0U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [90] MSG_WIP1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [91] MSG_ZN11S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [92] MSG_ZN11S32_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [93] MSG_ZN11S63_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [94] MSG_ZN11S64_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [95] MSG_ZN11S65_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [96] MSG_ZN11S66_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [97] MSG_ZN11S67_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [98] MSG_ZN11SF6_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [99] MSG_ZN11SF7_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U                                                                        /* Padding Area */
};
#endif /* (BSW_COM_CFG_FAILSAFE_SIZE != 0U) */

#if (BSW_COM_CFG_FAILSAFE_SIZE != 0U)
BswConst BswU1 bsw_com_data_u1FailMskTbl[BSW_COM_FAILSAFE_SIZE] = {
     (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [0] MSG_CDC1S04_TXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U                                                                        /* Padding Area */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [1] MSG_ABG1D50_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [2] MSG_ABG1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x03U, (BswU1)0x3FU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x3FU
    ,(BswU1)0x3FU, (BswU1)0x1FU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x3FU, (BswU1)0x3FU, (BswU1)0x7FU, (BswU1)0x7FU
    ,(BswU1)0x7FU, (BswU1)0x7FU, (BswU1)0x0FU, (BswU1)0x0FU, (BswU1)0x03U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0x0FU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [3] MSG_ABG1S09_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [4] MSG_ACN1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x0FU, (BswU1)0x00U, (BswU1)0xC0U, (BswU1)0xC0U, (BswU1)0x03U, (BswU1)0x00U, (BswU1)0x00U  /* [5] MSG_ACN1S03_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0xF1U, (BswU1)0x22U, (BswU1)0xFFU, (BswU1)0x00U  /* [6] MSG_ACN1S15_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x1FU, (BswU1)0x07U, (BswU1)0xFFU, (BswU1)0x07U, (BswU1)0xFFU
    ,(BswU1)0x07U, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [7] MSG_ACN1S25_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xDFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x1FU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [8] MSG_ACN1S29_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [9] MSG_ADC1S27_RXCH0 */
    ,(BswU1)0x20U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [10] MSG_ADC1S30_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x01U, (BswU1)0x07U, (BswU1)0x07U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [11] MSG_ADC1S31_RXCH0 */
    ,(BswU1)0x3FU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [12] MSG_ADU1S03_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x80U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [13] MSG_ADU1S05_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xF8U, (BswU1)0xFFU, (BswU1)0xFEU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xF8U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xE0U, (BswU1)0x00U  /* [14] MSG_ADU1S06_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xF0U
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFCU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [15] MSG_BAT1E45_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [16] MSG_BAT1ED1_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U  /* [17] MSG_BAT1ED4_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [18] MSG_BAT1ED5_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [19] MSG_BAT1EDA_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [20] MSG_BAT1EDB_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xF7U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFEU, (BswU1)0x00U  /* [21] MSG_BAT1S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [22] MSG_BAT2ED2_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [23] MSG_BDB1F03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0xF0U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xF0U  /* [24] MSG_BDB1S10_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFCU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [25] MSG_BDC1S22_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xF8U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x80U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0x00U  /* [26] MSG_BDC1S41_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [27] MSG_BDC1S81_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [28] MSG_BDC1SH8_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x01U
    ,(BswU1)0xFFU, (BswU1)0x03U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0x0FU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x3FU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [29] MSG_BDF3S01_RXCH0 */
    ,(BswU1)0x3FU, (BswU1)0xFFU, (BswU1)0x03U, (BswU1)0xFFU, (BswU1)0x19U, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x3FU
    ,(BswU1)0xFFU, (BswU1)0xC0U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xF3U, (BswU1)0xFCU, (BswU1)0x07U, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFEU, (BswU1)0x00U, (BswU1)0x3FU, (BswU1)0x01U, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0x01U, (BswU1)0xFFU, (BswU1)0x03U, (BswU1)0x3FU, (BswU1)0xFFU, (BswU1)0x3FU, (BswU1)0xFFU  /* [30] MSG_BDF3S02_RXCH0 */
    ,(BswU1)0xE1U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x80U, (BswU1)0x07U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [31] MSG_BDR3S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [32] MSG_CMB1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x15U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x07U, (BswU1)0x00U  /* [33] MSG_CMB1S04_RXCH0 */
    ,(BswU1)0x80U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [34] MSG_DCM1S08_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [35] MSG_DDM1S00_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [36] MSG_DDM1S09_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0x38U, (BswU1)0xFCU, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [37] MSG_DDM1S16_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [38] MSG_DDM1S35_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [39] MSG_DDM1SFG_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [40] MSG_DDM1SFH_RXCH0 */
    ,(BswU1)0xFEU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [41] MSG_DKY1S26_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x08U, (BswU1)0x00U, (BswU1)0x00U  /* [42] MSG_DS11S27_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [43] MSG_EBU1D01_RXCH0 */
    ,(BswU1)0x38U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [44] MSG_ECT1S93_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xE0U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [45] MSG_EHV1E96_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x18U, (BswU1)0x00U, (BswU1)0x08U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U  /* [46] MSG_EHV1F02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x3EU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [47] MSG_EHV1S23_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xF0U, (BswU1)0x00U, (BswU1)0x88U, (BswU1)0x00U, (BswU1)0xA1U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [48] MSG_EHV2G10_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x18U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [49] MSG_EHV2G20_RXCH0 */
    ,(BswU1)0x0CU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [50] MSG_EIM1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [51] MSG_ENG1C01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [52] MSG_ENG1C02_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [53] MSG_ENG1D51_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [54] MSG_ENG1D52_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [55] MSG_ENG1D53_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [56] MSG_ENG1D55_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [57] MSG_ENG1D56_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [58] MSG_ENG1D59_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [59] MSG_ENG1D60_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x1FU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [60] MSG_ENG1S51_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [61] MSG_EPS1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [62] MSG_FCM1C01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFCU, (BswU1)0xFEU, (BswU1)0x10U, (BswU1)0xFFU, (BswU1)0xF0U
    ,(BswU1)0x00U, (BswU1)0xF8U, (BswU1)0xFFU, (BswU1)0xE0U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0x80U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xF8U, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0x80U, (BswU1)0x00U, (BswU1)0x0FU, (BswU1)0xFFU, (BswU1)0xFCU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [63] MSG_FCM1S49_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [64] MSG_FCM1S76_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [65] MSG_FCM1S79_RXCH0 */
    ,(BswU1)0x7FU, (BswU1)0xFFU, (BswU1)0x0FU, (BswU1)0x3FU, (BswU1)0xFFU, (BswU1)0x7FU, (BswU1)0x3FU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0x07U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [66] MSG_FCM1S90_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xE7U, (BswU1)0x0CU, (BswU1)0x3FU, (BswU1)0xFFU, (BswU1)0x00U
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFCU, (BswU1)0xFFU, (BswU1)0x7FU
    ,(BswU1)0x03U, (BswU1)0xFFU, (BswU1)0x03U, (BswU1)0xFFU, (BswU1)0x01U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xC0U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [67] MSG_FCM1S95_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x0FU  /* [68] MSG_IDT1S07_RXCH0 */
    ,(BswU1)0xFEU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [69] MSG_IDT1S15_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x80U, (BswU1)0x7CU, (BswU1)0x00U  /* [70] MSG_LRS1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x3FU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xC0U  /* [71] MSG_LRS1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFCU, (BswU1)0x00U  /* [72] MSG_LRS1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [73] MSG_MGC1F13_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [74] MSG_PDC1G01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [75] MSG_PWC1S41_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x15U, (BswU1)0xC3U, (BswU1)0x03U, (BswU1)0x00U, (BswU1)0x00U  /* [76] MSG_RCP1S03_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x80U, (BswU1)0x7CU, (BswU1)0x00U  /* [77] MSG_RRS1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x3FU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xC0U  /* [78] MSG_RRS1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFCU, (BswU1)0x00U  /* [79] MSG_RRS1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [80] MSG_RSE1G20_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [81] MSG_RSE1G24_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [82] MSG_RSE1G25_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x3FU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [83] MSG_RSE1G26_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [84] MSG_RSE1G29_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [85] MSG_RSE1S02_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFEU
    ,(BswU1)0x00U, (BswU1)0xC0U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [86] MSG_SCS1S10_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [87] MSG_VGR1D50_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [88] MSG_VSC1D51_RXCH0 */
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x40U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFBU, (BswU1)0xFFU, (BswU1)0xFBU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [89] MSG_VSC1G13_RXCH0 */
    ,(BswU1)0xF0U, (BswU1)0xE0U, (BswU1)0x3EU, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [90] MSG_WIP1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xB8U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU
    ,(BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU, (BswU1)0xFFU  /* [91] MSG_ZN11S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [92] MSG_ZN11S32_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [93] MSG_ZN11S63_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [94] MSG_ZN11S64_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [95] MSG_ZN11S65_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [96] MSG_ZN11S66_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [97] MSG_ZN11S67_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [98] MSG_ZN11SF6_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [99] MSG_ZN11SF7_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U                                                                        /* Padding Area */
};
#endif /* (BSW_COM_CFG_FAILSAFE_SIZE != 0U) */

BswConst Bsw_Com_DataInfoType bsw_com_stDataInfoTbl[BSW_COM_HANDLE_NUM] = {
     BSW_COM_u1EVCOND_VALCHG                                                                                     /* [0] ComConf_ComSignal_ETHWU_21 */
    ,BSW_COM_u1EVCOND_VALCHG                                                                                     /* [1] ComConf_ComSignal_ETHWU_23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [2] ComConf_ComSignal_DRABG01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [3] ComConf_ComSignal_DRABG02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [4] ComConf_ComSignal_DRABG03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [5] ComConf_ComSignal_DRABG04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [6] ComConf_ComSignal_DRABG05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [7] ComConf_ComSignal_DRABG06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [8] ComConf_ComSignal_DRABG07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [9] ComConf_ComSignal_DRABG08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [10] ComConf_ComSignal_DRABG09 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [11] ComConf_ComSignal_DRABG10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [12] ComConf_ComSignal_DRABG11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [13] ComConf_ComSignal_DRABG12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [14] ComConf_ComSignal_DRABG13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [15] ComConf_ComSignal_DRABG14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [16] ComConf_ComSignal_DRABG15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [17] ComConf_ComSignal_DRABG16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [18] ComConf_ComSignal_D00024 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [19] ComConf_ComSignal_D00025 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [20] ComConf_ComSignal_D00026 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [21] ComConf_ComSignal_D00027 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [22] ComConf_ComSignal_FLGXMAX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [23] ComConf_ComSignal_D00028 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [24] ComConf_ComSignal_D00029 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [25] ComConf_ComSignal_D00030 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [26] ComConf_ComSignal_FLVNMAX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [27] ComConf_ComSignal_FRGMAX_L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [28] ComConf_ComSignal_FRGMAX_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [29] ComConf_ComSignal_D00031 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [30] ComConf_ComSignal_D00032 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [31] ComConf_ComSignal_D00033 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [32] ComConf_ComSignal_D00034 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [33] ComConf_ComSignal_D00035 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [34] ComConf_ComSignal_D00036 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [35] ComConf_ComSignal_PT_ON */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [36] ComConf_ComSignal_FRAB_ON */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [37] ComConf_ComSignal_D00037 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [38] ComConf_ComSignal_D00038 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [39] ComConf_ComSignal_D00039 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [40] ComConf_ComSignal_D00040 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [41] ComConf_ComSignal_D00041 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [42] ComConf_ComSignal_D00042 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [43] ComConf_ComSignal_D00043 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [44] ComConf_ComSignal_D00044 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [45] ComConf_ComSignal_D00045 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [46] ComConf_ComSignal_D00046 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [47] ComConf_ComSignal_DRACN01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [48] ComConf_ComSignal_DRACN02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [49] ComConf_ComSignal_DRACN03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [50] ComConf_ComSignal_DRACN04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [51] ComConf_ComSignal_DRACN05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [52] ComConf_ComSignal_DRACN06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [53] ComConf_ComSignal_DRACN07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [54] ComConf_ComSignal_DRACN08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [55] ComConf_ComSignal_D00075 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [56] ComConf_ComSignal_D00076 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [57] ComConf_ComSignal_D00077 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [58] ComConf_ComSignal_O_STG_F */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [59] ComConf_ComSignal_D00078 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [60] ComConf_ComSignal_D00079 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [61] ComConf_ComSignal_AC_CDSP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [62] ComConf_ComSignal_D00080 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [63] ComConf_ComSignal_D00092 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [64] ComConf_ComSignal_TRTEMP_P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [65] ComConf_ComSignal_I_BLWF_P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [66] ComConf_ComSignal_D00093 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [67] ComConf_ComSignal_D00094 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [68] ComConf_ComSignal_D00095 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [69] ComConf_ComSignal_D00096 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [70] ComConf_ComSignal_D00109 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [71] ComConf_ComSignal_D00110 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [72] ComConf_ComSignal_D00111 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [73] ComConf_ComSignal_D00112 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [74] ComConf_ComSignal_D00113 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [75] ComConf_ComSignal_D00114 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [76] ComConf_ComSignal_D00115 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [77] ComConf_ComSignal_D00116 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [78] ComConf_ComSignal_D00117 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [79] ComConf_ComSignal_D00118 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [80] ComConf_ComSignal_D00119 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [81] ComConf_ComSignal_D00120 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [82] ComConf_ComSignal_D00121 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [83] ComConf_ComSignal_D00122 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [84] ComConf_ComSignal_D00123 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [85] ComConf_ComSignal_D00124 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [86] ComConf_ComSignal_HQ_COMP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [87] ComConf_ComSignal_D00135 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [88] ComConf_ComSignal_D00136 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [89] ComConf_ComSignal_D00137 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [90] ComConf_ComSignal_D00138 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [91] ComConf_ComSignal_R_SHHTFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [92] ComConf_ComSignal_D00139 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [93] ComConf_ComSignal_R_SHHTFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [94] ComConf_ComSignal_D00140 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [95] ComConf_ComSignal_D00141 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [96] ComConf_ComSignal_D00142 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [97] ComConf_ComSignal_D00143 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [98] ComConf_ComSignal_D00144 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [99] ComConf_ComSignal_D00145 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [100] ComConf_ComSignal_D00146 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [101] ComConf_ComSignal_D00147 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [102] ComConf_ComSignal_RSVFLDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [103] ComConf_ComSignal_D00148 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [104] ComConf_ComSignal_RSVFRDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [105] ComConf_ComSignal_D00149 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [106] ComConf_ComSignal_R_SHHTRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [107] ComConf_ComSignal_D00150 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [108] ComConf_ComSignal_R_SHHTRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [109] ComConf_ComSignal_D00151 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [110] ComConf_ComSignal_D00152 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [111] ComConf_ComSignal_D00153 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [112] ComConf_ComSignal_D00154 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [113] ComConf_ComSignal_D00155 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [114] ComConf_ComSignal_D00156 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [115] ComConf_ComSignal_D00157 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [116] ComConf_ComSignal_D00158 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [117] ComConf_ComSignal_D00159 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [118] ComConf_ComSignal_RSVRLDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [119] ComConf_ComSignal_D00160 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [120] ComConf_ComSignal_RSVRRDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [121] ComConf_ComSignal_D00161 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [122] ComConf_ComSignal_R_RDHRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [123] ComConf_ComSignal_D00162 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [124] ComConf_ComSignal_R_RDHRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [125] ComConf_ComSignal_D00163 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [126] ComConf_ComSignal_R_RDHFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [127] ComConf_ComSignal_D00164 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [128] ComConf_ComSignal_R_RDHFD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [129] ComConf_ComSignal_D00165 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [130] ComConf_ComSignal_D00166 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [131] ComConf_ComSignal_D00167 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [132] ComConf_ComSignal_D00168 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [133] ComConf_ComSignal_WS_VD_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [134] ComConf_ComSignal_WS_FTG_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [135] ComConf_ComSignal_WS_ABH_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [136] ComConf_ComSignal_WS_APO_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [137] ComConf_ComSignal_ETHWU_12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [138] ComConf_ComSignal_D00214 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [139] ComConf_ComSignal_APPMD2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [140] ComConf_ComSignal_D00215 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [141] ComConf_ComSignal_D00216 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [142] ComConf_ComSignal_D00217 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [143] ComConf_ComSignal_FV1C0_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [144] ComConf_ComSignal_KZK1C0_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [145] ComConf_ComSignal_ACCMAPP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [146] ComConf_ComSignal_ACCMMOD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [147] ComConf_ComSignal_ACCMDST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [148] ComConf_ComSignal_ACCMPHS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [149] ComConf_ComSignal_ACCMSGN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [150] ComConf_ComSignal_ACCMRCG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [151] ComConf_ComSignal_ACCMARB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [152] ComConf_ComSignal_LDASTATL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [153] ComConf_ComSignal_LDASTATR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [154] ComConf_ComSignal_LDARSN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [155] ComConf_ComSignal_FCMINTMP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [156] ComConf_ComSignal_LDARCGL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [157] ComConf_ComSignal_LDARCGR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [158] ComConf_ComSignal_SWSSTAT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [159] ComConf_ComSignal_V_IDACCL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [160] ComConf_ComSignal_EJDEVPRD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [161] ComConf_ComSignal_EJLDACP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [162] ComConf_ComSignal_V_IDANOA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [163] ComConf_ComSignal_V_IDARGL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [164] ComConf_ComSignal_PV_AREA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [165] ComConf_ComSignal_DM_PVMVW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [166] ComConf_ComSignal_DM_PVMCS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [167] ComConf_ComSignal_ERMCNTST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [168] ComConf_ComSignal_GAE_H_R3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [169] ComConf_ComSignal_FRDHTR_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [170] ComConf_ComSignal_SDIRT_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [171] ComConf_ComSignal_GAE_V_R1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [172] ComConf_ComSignal_DRTCNT_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [173] ComConf_ComSignal_GAERR1_V */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [174] ComConf_ComSignal_GAEVAL_H */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [175] ComConf_ComSignal_GAERR3_H */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [176] ComConf_ComSignal_DTSSSTR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [177] ComConf_ComSignal_DTSSLTID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [178] ComConf_ComSignal_MDSYNC00 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [179] ComConf_ComSignal_BIB_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [180] ComConf_ComSignal_VCELMAXG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [181] ComConf_ComSignal_VCELMING */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [182] ComConf_ComSignal_RAHRMAXG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [183] ComConf_ComSignal_RAHRMING */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [184] ComConf_ComSignal_TC_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [185] ComConf_ComSignal_TBMAX_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [186] ComConf_ComSignal_TBMIN_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [187] ComConf_ComSignal_D00520 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [188] ComConf_ComSignal_D00521 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [189] ComConf_ComSignal_D00522 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [190] ComConf_ComSignal_D_IB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [191] ComConf_ComSignal_D_VB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [192] ComConf_ComSignal_D_VBMAX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [193] ComConf_ComSignal_D_VBMIN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [194] ComConf_ComSignal_D_VMAXN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [195] ComConf_ComSignal_D_VMINN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [196] ComConf_ComSignal_D_TBMAX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [197] ComConf_ComSignal_D_TBMIN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [198] ComConf_ComSignal_D_TBMAXN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [199] ComConf_ComSignal_D_TBMINN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [200] ComConf_ComSignal_D_SOC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [201] ComConf_ComSignal_D_BATENE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [202] ComConf_ComSignal_D_BERG1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [203] ComConf_ComSignal_D_BERG2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [204] ComConf_ComSignal_D_BERG3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [205] ComConf_ComSignal_D_BALM_1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [206] ComConf_ComSignal_D_BALM_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [207] ComConf_ComSignal_D_BALM_3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [208] ComConf_ComSignal_D_BALM_4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [209] ComConf_ComSignal_D_BALM_5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [210] ComConf_ComSignal_D_BCODE1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [211] ComConf_ComSignal_D_BCODE2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [212] ComConf_ComSignal_D_BCODE3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [213] ComConf_ComSignal_D_BCODE4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [214] ComConf_ComSignal_D_BCODE5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [215] ComConf_ComSignal_D_BCODE6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [216] ComConf_ComSignal_D_BCODE7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [217] ComConf_ComSignal_D_BCODE8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [218] ComConf_ComSignal_D_VCELCH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [219] ComConf_ComSignal_D_VCELL0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [220] ComConf_ComSignal_D_VCELL1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [221] ComConf_ComSignal_D_VCELL2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [222] ComConf_ComSignal_D_VCELL3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [223] ComConf_ComSignal_D_TBCH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [224] ComConf_ComSignal_D_TB0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [225] ComConf_ComSignal_D_TB1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [226] ComConf_ComSignal_D_TB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [227] ComConf_ComSignal_D_TB3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [228] ComConf_ComSignal_D_TB4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [229] ComConf_ComSignal_D_TB5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [230] ComConf_ComSignal_D_TB6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [231] ComConf_ComSignal_D_MINFAD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [232] ComConf_ComSignal_D_MINFO1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [233] ComConf_ComSignal_D_MINFO2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [234] ComConf_ComSignal_D_MINFO3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [235] ComConf_ComSignal_D_BVIN1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [236] ComConf_ComSignal_D_BVIN2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [237] ComConf_ComSignal_D_BVIN3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [238] ComConf_ComSignal_D_BVIN4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [239] ComConf_ComSignal_D_BVIN5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [240] ComConf_ComSignal_D_BVIN6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [241] ComConf_ComSignal_D_BVIN7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [242] ComConf_ComSignal_D_BVIN8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [243] ComConf_ComSignal_D_BVIN9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [244] ComConf_ComSignal_D_BVIN10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [245] ComConf_ComSignal_D_BVIN11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [246] ComConf_ComSignal_D_BVIN12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [247] ComConf_ComSignal_D_BVIN13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [248] ComConf_ComSignal_D_BVIN14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [249] ComConf_ComSignal_D_BVIN15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [250] ComConf_ComSignal_D_BVIN16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [251] ComConf_ComSignal_D_BVIN17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [252] ComConf_ComSignal_D_BVIN18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [253] ComConf_ComSignal_D_BVIN19 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [254] ComConf_ComSignal_D_BVIN20 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [255] ComConf_ComSignal_D_BVIN21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [256] ComConf_ComSignal_D_BVIN22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [257] ComConf_ComSignal_D_BVIN23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [258] ComConf_ComSignal_D_BVIN24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [259] ComConf_ComSignal_D00596 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [260] ComConf_ComSignal_D00597 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [261] ComConf_ComSignal_D00598 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [262] ComConf_ComSignal_D00599 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [263] ComConf_ComSignal_BTWO */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [264] ComConf_ComSignal_D00600 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [265] ComConf_ComSignal_D00601 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [266] ComConf_ComSignal_D00602 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [267] ComConf_ComSignal_D00603 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [268] ComConf_ComSignal_D00604 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [269] ComConf_ComSignal_BITGB1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [270] ComConf_ComSignal_BITGB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [271] ComConf_ComSignal_BITGB3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [272] ComConf_ComSignal_BITGB4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [273] ComConf_ComSignal_STKNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [274] ComConf_ComSignal_BITGB5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [275] ComConf_ComSignal_VCELNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [276] ComConf_ComSignal_INFGB1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [277] ComConf_ComSignal_TMINNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [278] ComConf_ComSignal_INFGB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [279] ComConf_ComSignal_TMAXNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [280] ComConf_ComSignal_VBTINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [281] ComConf_ComSignal_SOCINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [282] ComConf_ComSignal_IBTINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [283] ComConf_ComSignal_TBTINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [284] ComConf_ComSignal_STPSOC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [285] ComConf_ComSignal_STPVB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [286] ComConf_ComSignal_STPCELV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [287] ComConf_ComSignal_STPTMP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [288] ComConf_ComSignal_DATAGB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [289] ComConf_ComSignal_DATAGB3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [290] ComConf_ComSignal_ID63B16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [291] ComConf_ComSignal_IF63B16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [292] ComConf_ComSignal_TRIP_CNT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [293] ComConf_ComSignal_TIME_CNT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [294] ComConf_ComSignal_D00809 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [295] ComConf_ComSignal_D00810 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [296] ComConf_ComSignal_IL_FDOME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [297] ComConf_ComSignal_IL_LOUNG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [298] ComConf_ComSignal_IL_OSSTP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [299] ComConf_ComSignal_AMB_COP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [300] ComConf_ComSignal_SUPRQ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [301] ComConf_ComSignal_D00811 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [302] ComConf_ComSignal_D00812 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [303] ComConf_ComSignal_THEFTD1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [304] ComConf_ComSignal_THEFTD2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [305] ComConf_ComSignal_D00908 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [306] ComConf_ComSignal_D00909 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [307] ComConf_ComSignal_D00910 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [308] ComConf_ComSignal_D00911 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [309] ComConf_ComSignal_D00912 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [310] ComConf_ComSignal_D00913 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [311] ComConf_ComSignal_D00914 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [312] ComConf_ComSignal_D00915 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [313] ComConf_ComSignal_D00916 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [314] ComConf_ComSignal_D00917 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [315] ComConf_ComSignal_AXSOC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [316] ComConf_ComSignal_D00918 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [317] ComConf_ComSignal_D00919 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [318] ComConf_ComSignal_D00920 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [319] ComConf_ComSignal_D00921 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [320] ComConf_ComSignal_D00922 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [321] ComConf_ComSignal_D00923 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [322] ComConf_ComSignal_D00924 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [323] ComConf_ComSignal_D00925 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [324] ComConf_ComSignal_D00926 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [325] ComConf_ComSignal_D00927 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [326] ComConf_ComSignal_D00928 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [327] ComConf_ComSignal_D00929 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [328] ComConf_ComSignal_D00930 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [329] ComConf_ComSignal_D00931 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [330] ComConf_ComSignal_D00932 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [331] ComConf_ComSignal_D00933 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [332] ComConf_ComSignal_D00934 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [333] ComConf_ComSignal_D00935 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [334] ComConf_ComSignal_D00936 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [335] ComConf_ComSignal_D00937 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [336] ComConf_ComSignal_D00938 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [337] ComConf_ComSignal_D00939 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [338] ComConf_ComSignal_D00940 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [339] ComConf_ComSignal_D00941 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [340] ComConf_ComSignal_D00942 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [341] ComConf_ComSignal_D00943 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [342] ComConf_ComSignal_D00944 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [343] ComConf_ComSignal_D00945 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [344] ComConf_ComSignal_D00946 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [345] ComConf_ComSignal_D00947 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [346] ComConf_ComSignal_D00948 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [347] ComConf_ComSignal_D00949 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [348] ComConf_ComSignal_D00950 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [349] ComConf_ComSignal_D00951 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [350] ComConf_ComSignal_D00952 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [351] ComConf_ComSignal_D00953 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [352] ComConf_ComSignal_D00954 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [353] ComConf_ComSignal_D00955 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [354] ComConf_ComSignal_D00956 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [355] ComConf_ComSignal_E_CRC1E3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [356] ComConf_ComSignal_E_CNT1E3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [357] ComConf_ComSignal_VPSINFO7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [358] ComConf_ComSignal_VPSINFO6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [359] ComConf_ComSignal_VPSINFO5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [360] ComConf_ComSignal_VPSINFO4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [361] ComConf_ComSignal_VPSINFO3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [362] ComConf_ComSignal_VPSINFO2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [363] ComConf_ComSignal_VPSINFO1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [364] ComConf_ComSignal_VPSINFOS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [365] ComConf_ComSignal_D00976 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [366] ComConf_ComSignal_VPSISOTA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [367] ComConf_ComSignal_APOFRQ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [368] ComConf_ComSignal_FV1E3_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [369] ComConf_ComSignal_KZK1E3_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [370] ComConf_ComSignal_ST1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [371] ComConf_ComSignal_ST1PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [372] ComConf_ComSignal_ST2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [373] ComConf_ComSignal_ST2PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [374] ComConf_ComSignal_ST3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [375] ComConf_ComSignal_ST3PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [376] ComConf_ComSignal_ST4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [377] ComConf_ComSignal_ST4PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [378] ComConf_ComSignal_ST5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [379] ComConf_ComSignal_ST5PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [380] ComConf_ComSignal_ST6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [381] ComConf_ComSignal_ST6PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [382] ComConf_ComSignal_ST7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [383] ComConf_ComSignal_ST7PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [384] ComConf_ComSignal_ST8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [385] ComConf_ComSignal_ST8PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [386] ComConf_ComSignal_ST9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [387] ComConf_ComSignal_ST9PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [388] ComConf_ComSignal_ST10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [389] ComConf_ComSignal_ST10PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [390] ComConf_ComSignal_ST11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [391] ComConf_ComSignal_ST11PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [392] ComConf_ComSignal_ST12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [393] ComConf_ComSignal_ST12PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [394] ComConf_ComSignal_ST13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [395] ComConf_ComSignal_ST13PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [396] ComConf_ComSignal_ST14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [397] ComConf_ComSignal_ST14PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [398] ComConf_ComSignal_ST15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [399] ComConf_ComSignal_ST15PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [400] ComConf_ComSignal_ST16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [401] ComConf_ComSignal_ST16PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [402] ComConf_ComSignal_ST17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [403] ComConf_ComSignal_ST17PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [404] ComConf_ComSignal_ST18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [405] ComConf_ComSignal_ST18PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [406] ComConf_ComSignal_D01286 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [407] ComConf_ComSignal_D01287 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [408] ComConf_ComSignal_D01288 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [409] ComConf_ComSignal_D01289 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [410] ComConf_ComSignal_D01290 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [411] ComConf_ComSignal_D01291 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [412] ComConf_ComSignal_D01292 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [413] ComConf_ComSignal_D01293 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [414] ComConf_ComSignal_D01294 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [415] ComConf_ComSignal_ACPRE_AD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [416] ComConf_ComSignal_EXPMIP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [417] ComConf_ComSignal_D01295 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [418] ComConf_ComSignal_AMR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [419] ComConf_ComSignal_MIP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [420] ComConf_ComSignal_D01296 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [421] ComConf_ComSignal_D01297 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [422] ComConf_ComSignal_D01298 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [423] ComConf_ComSignal_D01299 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [424] ComConf_ComSignal_D01300 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [425] ComConf_ComSignal_D01301 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [426] ComConf_ComSignal_D01302 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [427] ComConf_ComSignal_D01303 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [428] ComConf_ComSignal_D01304 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [429] ComConf_ComSignal_D01305 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [430] ComConf_ComSignal_D01306 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [431] ComConf_ComSignal_D01307 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [432] ComConf_ComSignal_D01308 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [433] ComConf_ComSignal_D01309 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [434] ComConf_ComSignal_D01310 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [435] ComConf_ComSignal_D01311 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [436] ComConf_ComSignal_D01312 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [437] ComConf_ComSignal_D01313 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [438] ComConf_ComSignal_D01314 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [439] ComConf_ComSignal_D01315 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [440] ComConf_ComSignal_D01316 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [441] ComConf_ComSignal_FV37B_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [442] ComConf_ComSignal_KZK37B_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [443] ComConf_ComSignal_D01317 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [444] ComConf_ComSignal_D01318 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [445] ComConf_ComSignal_D01319 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [446] ComConf_ComSignal_D01320 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [447] ComConf_ComSignal_D01321 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [448] ComConf_ComSignal_D01322 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [449] ComConf_ComSignal_D01323 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [450] ComConf_ComSignal_D01324 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [451] ComConf_ComSignal_D01325 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [452] ComConf_ComSignal_D01326 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [453] ComConf_ComSignal_D01327 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [454] ComConf_ComSignal_D01328 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [455] ComConf_ComSignal_D01329 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [456] ComConf_ComSignal_D01330 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [457] ComConf_ComSignal_D01331 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [458] ComConf_ComSignal_D01332 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [459] ComConf_ComSignal_D01333 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [460] ComConf_ComSignal_D01334 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [461] ComConf_ComSignal_D01335 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [462] ComConf_ComSignal_HVH_ATPW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [463] ComConf_ComSignal_D01336 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [464] ComConf_ComSignal_D01337 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [465] ComConf_ComSignal_D01338 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [466] ComConf_ComSignal_D01339 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [467] ComConf_ComSignal_D01340 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [468] ComConf_ComSignal_D01341 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [469] ComConf_ComSignal_D01342 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [470] ComConf_ComSignal_D01343 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [471] ComConf_ComSignal_D01344 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [472] ComConf_ComSignal_D01345 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [473] ComConf_ComSignal_D01346 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [474] ComConf_ComSignal_D01347 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [475] ComConf_ComSignal_D01348 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [476] ComConf_ComSignal_D01349 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [477] ComConf_ComSignal_D01350 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [478] ComConf_ComSignal_D01351 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [479] ComConf_ComSignal_D01352 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [480] ComConf_ComSignal_D01361 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [481] ComConf_ComSignal_D01362 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [482] ComConf_ComSignal_D01363 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [483] ComConf_ComSignal_D01364 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [484] ComConf_ComSignal_COMPRP_A */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [485] ComConf_ComSignal_D01365 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [486] ComConf_ComSignal_ACMODE_P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [487] ComConf_ComSignal_D01366 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [488] ComConf_ComSignal_HED_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [489] ComConf_ComSignal_TAL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [490] ComConf_ComSignal_DRL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [491] ComConf_ComSignal_AUT_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [492] ComConf_ComSignal_OFF_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [493] ComConf_ComSignal_AHB_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [494] ComConf_ComSignal_PAS_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [495] ComConf_ComSignal_HIB_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [496] ComConf_ComSignal_BW_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [497] ComConf_ComSignal_RFG_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [498] ComConf_ComSignal_FOG_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [499] ComConf_ComSignal_CRGL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [500] ComConf_ComSignal_CRGR_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [501] ComConf_ComSignal_TRNL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [502] ComConf_ComSignal_TRNR_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [503] ComConf_ComSignal_CXP_TERR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [504] ComConf_ComSignal_CXP_JDGT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [505] ComConf_ComSignal_WVR_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [506] ComConf_ComSignal_WSW_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [507] ComConf_ComSignal_WRSW_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [508] ComConf_ComSignal_WRON_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [509] ComConf_ComSignal_WRIN_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [510] ComConf_ComSignal_WINT_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [511] ComConf_ComSignal_WMST_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [512] ComConf_ComSignal_WA_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [513] ComConf_ComSignal_WHI_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [514] ComConf_ComSignal_WLO_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [515] ComConf_ComSignal_WOFF_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [516] ComConf_ComSignal_WAI_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [517] ComConf_ComSignal_CXP_WERR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [518] ComConf_ComSignal_CXP_JDGW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [519] ComConf_ComSignal_D02498 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [520] ComConf_ComSignal_ETHWU_32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [521] ComConf_ComSignal_THR_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [522] ComConf_ComSignal_TMO_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [523] ComConf_ComSignal_TTA_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [524] ComConf_ComSignal_RTA_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [525] ComConf_ComSignal_TR_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [526] ComConf_ComSignal_TM_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [527] ComConf_ComSignal_NR_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [528] ComConf_ComSignal_NM_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [529] ComConf_ComSignal_D02649 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [530] ComConf_ComSignal_NMRBR_MD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [531] ComConf_ComSignal_BHSWEXT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [532] ComConf_ComSignal_D02650 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [533] ComConf_ComSignal_D02651 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [534] ComConf_ComSignal_GRLGDBCR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [535] ComConf_ComSignal_DMCNVINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [536] ComConf_ComSignal_CNV_MODE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [537] ComConf_ComSignal_DMCNVVLD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [538] ComConf_ComSignal_TEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [539] ComConf_ComSignal_DRVEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [540] ComConf_ComSignal_ALTEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [541] ComConf_ComSignal_ACEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [542] ComConf_ComSignal_BPEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [543] ComConf_ComSignal_DAEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [544] ComConf_ComSignal_CAEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [545] ComConf_ComSignal_CUMTEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [546] ComConf_ComSignal_CUMDRVEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [547] ComConf_ComSignal_CUMALTEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [548] ComConf_ComSignal_CUMACEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [549] ComConf_ComSignal_CUMBPEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [550] ComConf_ComSignal_CUMDAEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [551] ComConf_ComSignal_CUMCAEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [552] ComConf_ComSignal_RBSCC_E */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [553] ComConf_ComSignal_RBSCC_F */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [554] ComConf_ComSignal_RBSCC_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [555] ComConf_ComSignal_RBSCC_H */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [556] ComConf_ComSignal_CHGCAL1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [557] ComConf_ComSignal_CHGCAL2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [558] ComConf_ComSignal_FSWRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [559] ComConf_ComSignal_U1TOCDC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [560] ComConf_ComSignal_U1TOCDC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [561] ComConf_ComSignal_U1TOCDC3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [562] ComConf_ComSignal_S2TOCDC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [563] ComConf_ComSignal_S2TOCDC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [564] ComConf_ComSignal_S2TOCDC3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [565] ComConf_ComSignal_RSISDKME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [566] ComConf_ComSignal_RSISIDDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [567] ComConf_ComSignal_D03957 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [568] ComConf_ComSignal_D03958 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [569] ComConf_ComSignal_D04012 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [570] ComConf_ComSignal_DESMUTE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [571] ComConf_ComSignal_DREBUID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [572] ComConf_ComSignal_DREBU02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [573] ComConf_ComSignal_DREBU03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [574] ComConf_ComSignal_DREBU04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [575] ComConf_ComSignal_DREBU05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [576] ComConf_ComSignal_DREBU06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [577] ComConf_ComSignal_DREBU07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [578] ComConf_ComSignal_DREBU08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [579] ComConf_ComSignal_DREBU11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [580] ComConf_ComSignal_DREBU12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [581] ComConf_ComSignal_DREBU13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [582] ComConf_ComSignal_DREBU14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [583] ComConf_ComSignal_DREBU15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [584] ComConf_ComSignal_DREBU16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [585] ComConf_ComSignal_DREBU17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [586] ComConf_ComSignal_DREBU18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [587] ComConf_ComSignal_DREBU21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [588] ComConf_ComSignal_DREBU22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [589] ComConf_ComSignal_DREBU23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [590] ComConf_ComSignal_DREBU24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [591] ComConf_ComSignal_DREBU25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [592] ComConf_ComSignal_DREBU26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [593] ComConf_ComSignal_DREBU27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [594] ComConf_ComSignal_DREBU28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [595] ComConf_ComSignal_DREBU31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [596] ComConf_ComSignal_DREBU32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [597] ComConf_ComSignal_DREBU33 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [598] ComConf_ComSignal_DREBU34 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [599] ComConf_ComSignal_DREBU35 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [600] ComConf_ComSignal_DREBU36 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [601] ComConf_ComSignal_DREBU37 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [602] ComConf_ComSignal_DREBU38 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [603] ComConf_ComSignal_DRDYSTS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [604] ComConf_ComSignal_DRDYB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [605] ComConf_ComSignal_D04218 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [606] ComConf_ComSignal_STRGCM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [607] ComConf_ComSignal_D04219 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [608] ComConf_ComSignal_D04220 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [609] ComConf_ComSignal_D04221 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [610] ComConf_ComSignal_D04222 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [611] ComConf_ComSignal_D04223 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [612] ComConf_ComSignal_D04224 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [613] ComConf_ComSignal_D04225 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [614] ComConf_ComSignal_D04226 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [615] ComConf_ComSignal_HV_SRGMD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [616] ComConf_ComSignal_D04276 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [617] ComConf_ComSignal_D04277 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [618] ComConf_ComSignal_TQRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [619] ComConf_ComSignal_D04278 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [620] ComConf_ComSignal_TQFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [621] ComConf_ComSignal_D04279 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [622] ComConf_ComSignal_D04280 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [623] ComConf_ComSignal_FCRF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [624] ComConf_ComSignal_CLE_SOCF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [625] ComConf_ComSignal_D04334 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [626] ComConf_ComSignal_D04335 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [627] ComConf_ComSignal_E_CRC075 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [628] ComConf_ComSignal_E_CNT075 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [629] ComConf_ComSignal_D04374 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [630] ComConf_ComSignal_SDRVRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [631] ComConf_ComSignal_D04375 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [632] ComConf_ComSignal_D04376 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [633] ComConf_ComSignal_SDRVFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [634] ComConf_ComSignal_D04377 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [635] ComConf_ComSignal_D04378 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [636] ComConf_ComSignal_D04379 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [637] ComConf_ComSignal_E_CRC0A1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [638] ComConf_ComSignal_E_CNT0A1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [639] ComConf_ComSignal_D04380 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [640] ComConf_ComSignal_D04381 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [641] ComConf_ComSignal_HVMRADRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [642] ComConf_ComSignal_HVMRADFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [643] ComConf_ComSignal_D04568 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [644] ComConf_ComSignal_DREIMABN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [645] ComConf_ComSignal_I_BAT_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [646] ComConf_ComSignal_U_BAT_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [647] ComConf_ComSignal_PWDTY_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [648] ComConf_ComSignal_VLO_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [649] ComConf_ComSignal_PWIF1_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [650] ComConf_ComSignal_T_BAT_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [651] ComConf_ComSignal_PWIF2_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [652] ComConf_ComSignal_SOCS_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [653] ComConf_ComSignal_SOC_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [654] ComConf_ComSignal_PWIF3_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [655] ComConf_ComSignal_PWIF4_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [656] ComConf_ComSignal_PWIF5_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [657] ComConf_ComSignal_DRENG11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [658] ComConf_ComSignal_DRENG12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [659] ComConf_ComSignal_DRENG13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [660] ComConf_ComSignal_DRENG14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [661] ComConf_ComSignal_DRENG15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [662] ComConf_ComSignal_DRENG16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [663] ComConf_ComSignal_DRENG17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [664] ComConf_ComSignal_DRENG18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [665] ComConf_ComSignal_DRENG21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [666] ComConf_ComSignal_DRENG22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [667] ComConf_ComSignal_DRENG23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [668] ComConf_ComSignal_DRENG24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [669] ComConf_ComSignal_DRENG25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [670] ComConf_ComSignal_DRENG26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [671] ComConf_ComSignal_DRENG27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [672] ComConf_ComSignal_DRENG28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [673] ComConf_ComSignal_DRENG31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [674] ComConf_ComSignal_DRENG32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [675] ComConf_ComSignal_DRENG33 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [676] ComConf_ComSignal_DRENG34 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [677] ComConf_ComSignal_DRENG35 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [678] ComConf_ComSignal_DRENG36 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [679] ComConf_ComSignal_DRENG37 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [680] ComConf_ComSignal_DRENG38 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [681] ComConf_ComSignal_DRENG51 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [682] ComConf_ComSignal_DRENG52 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [683] ComConf_ComSignal_DRENG53 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [684] ComConf_ComSignal_DRENG54 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [685] ComConf_ComSignal_DRENG55 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [686] ComConf_ComSignal_DRENG56 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [687] ComConf_ComSignal_DRENG57 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [688] ComConf_ComSignal_DRENG58 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [689] ComConf_ComSignal_DRENG61 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [690] ComConf_ComSignal_DRENG62 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [691] ComConf_ComSignal_DRENG63 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [692] ComConf_ComSignal_DRENG64 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [693] ComConf_ComSignal_DRENG65 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [694] ComConf_ComSignal_DRENG66 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [695] ComConf_ComSignal_DRENG67 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [696] ComConf_ComSignal_DRENG68 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [697] ComConf_ComSignal_DRENG91 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [698] ComConf_ComSignal_DRENG92 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [699] ComConf_ComSignal_DRENG93 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [700] ComConf_ComSignal_DRENG94 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [701] ComConf_ComSignal_DRENG95 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [702] ComConf_ComSignal_DRENG96 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [703] ComConf_ComSignal_DRENG97 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [704] ComConf_ComSignal_DRENG98 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [705] ComConf_ComSignal_DRENG101 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [706] ComConf_ComSignal_DRENG102 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [707] ComConf_ComSignal_DRENG103 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [708] ComConf_ComSignal_DRENG104 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [709] ComConf_ComSignal_DRENG105 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [710] ComConf_ComSignal_DRENG106 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [711] ComConf_ComSignal_DRENG107 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [712] ComConf_ComSignal_DRENG108 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [713] ComConf_ComSignal_VIN_1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [714] ComConf_ComSignal_VIN_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [715] ComConf_ComSignal_VIN_3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [716] ComConf_ComSignal_VIN_4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [717] ComConf_ComSignal_VIN_5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [718] ComConf_ComSignal_VIN_6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [719] ComConf_ComSignal_VIN_7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [720] ComConf_ComSignal_VIN_8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [721] ComConf_ComSignal_VIN_9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [722] ComConf_ComSignal_VIN_10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [723] ComConf_ComSignal_VIN_11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [724] ComConf_ComSignal_VIN_12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [725] ComConf_ComSignal_VIN_13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [726] ComConf_ComSignal_VIN_14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [727] ComConf_ComSignal_VIN_15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [728] ComConf_ComSignal_VIN_16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [729] ComConf_ComSignal_VIN_17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [730] ComConf_ComSignal_D04580 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [731] ComConf_ComSignal_D04581 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [732] ComConf_ComSignal_DREPS01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [733] ComConf_ComSignal_DREPS02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [734] ComConf_ComSignal_DREPS03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [735] ComConf_ComSignal_DREPS04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [736] ComConf_ComSignal_DREPS05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [737] ComConf_ComSignal_DREPS06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [738] ComConf_ComSignal_DREPS07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [739] ComConf_ComSignal_DREPS08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [740] ComConf_ComSignal_V_DIST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [741] ComConf_ComSignal_V_RELV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [742] ComConf_ComSignal_V_SWOP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [743] ComConf_ComSignal_USMREQG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [744] ComConf_ComSignal_RCURVR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [745] ComConf_ComSignal_USMDSTTS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [746] ComConf_ComSignal_COFFSET */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [747] ComConf_ComSignal_USMDSTSL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [748] ComConf_ComSignal_RSACAUF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [749] ComConf_ComSignal_OTHVW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [750] ComConf_ComSignal_OTHVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [751] ComConf_ComSignal_OTHPB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [752] ComConf_ComSignal_OTHTTC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [753] ComConf_ComSignal_OTHTTYP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [754] ComConf_ComSignal_D04634 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [755] ComConf_ComSignal_D04635 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [756] ComConf_ComSignal_D04636 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [757] ComConf_ComSignal_HITPOS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [758] ComConf_ComSignal_OTHRDANG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [759] ComConf_ComSignal_D04637 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [760] ComConf_ComSignal_D04638 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [761] ComConf_ComSignal_D04639 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [762] ComConf_ComSignal_D04640 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [763] ComConf_ComSignal_D04641 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [764] ComConf_ComSignal_D04642 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [765] ComConf_ComSignal_D04643 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [766] ComConf_ComSignal_D04644 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [767] ComConf_ComSignal_D04645 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [768] ComConf_ComSignal_D04646 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [769] ComConf_ComSignal_OTHOVLPC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [770] ComConf_ComSignal_OTHRVPC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [771] ComConf_ComSignal_OTHFALD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [772] ComConf_ComSignal_OTHCOND */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [773] ComConf_ComSignal_OTHLDIS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [774] ComConf_ComSignal_OTHFALF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [775] ComConf_ComSignal_OTHCONF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [776] ComConf_ComSignal_OTHLANE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [777] ComConf_ComSignal_OTHSOR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [778] ComConf_ComSignal_OTHROR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [779] ComConf_ComSignal_OTHLX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [780] ComConf_ComSignal_OTHSOLAR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [781] ComConf_ComSignal_D04663 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [782] ComConf_ComSignal_D04664 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [783] ComConf_ComSignal_D04665 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [784] ComConf_ComSignal_D04666 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [785] ComConf_ComSignal_D04667 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [786] ComConf_ComSignal_D04668 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [787] ComConf_ComSignal_XREQFPB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [788] ComConf_ComSignal_XREQPB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [789] ComConf_ComSignal_D04669 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [790] ComConf_ComSignal_D04670 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [791] ComConf_ComSignal_XREQPBH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [792] ComConf_ComSignal_D04671 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [793] ComConf_ComSignal_D04672 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [794] ComConf_ComSignal_D04673 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [795] ComConf_ComSignal_D04674 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [796] ComConf_ComSignal_D04675 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [797] ComConf_ComSignal_D04676 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [798] ComConf_ComSignal_D04677 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [799] ComConf_ComSignal_D04678 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [800] ComConf_ComSignal_D04679 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [801] ComConf_ComSignal_D04680 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [802] ComConf_ComSignal_D04681 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [803] ComConf_ComSignal_D04682 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [804] ComConf_ComSignal_D04683 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [805] ComConf_ComSignal_D04684 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [806] ComConf_ComSignal_D04685 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [807] ComConf_ComSignal_AVSTRGR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [808] ComConf_ComSignal_PBATRGR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [809] ComConf_ComSignal_D04686 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [810] ComConf_ComSignal_D04687 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [811] ComConf_ComSignal_PCSALM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [812] ComConf_ComSignal_D04688 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [813] ComConf_ComSignal_D04689 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [814] ComConf_ComSignal_D04690 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [815] ComConf_ComSignal_D04691 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [816] ComConf_ComSignal_D04692 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [817] ComConf_ComSignal_D04693 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [818] ComConf_ComSignal_D04694 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [819] ComConf_ComSignal_D04695 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [820] ComConf_ComSignal_D04696 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [821] ComConf_ComSignal_D04697 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [822] ComConf_ComSignal_D04698 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [823] ComConf_ComSignal_D04699 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [824] ComConf_ComSignal_D04700 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [825] ComConf_ComSignal_D04701 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [826] ComConf_ComSignal_D04702 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [827] ComConf_ComSignal_D04703 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [828] ComConf_ComSignal_D04704 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [829] ComConf_ComSignal_D04705 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [830] ComConf_ComSignal_D04706 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [831] ComConf_ComSignal_D04707 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [832] ComConf_ComSignal_D04708 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [833] ComConf_ComSignal_D04709 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [834] ComConf_ComSignal_D04710 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [835] ComConf_ComSignal_D04711 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [836] ComConf_ComSignal_D04712 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [837] ComConf_ComSignal_D04713 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [838] ComConf_ComSignal_D04714 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [839] ComConf_ComSignal_D04715 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [840] ComConf_ComSignal_D04716 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [841] ComConf_ComSignal_D04717 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [842] ComConf_ComSignal_D04718 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [843] ComConf_ComSignal_D04719 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [844] ComConf_ComSignal_D04720 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [845] ComConf_ComSignal_D04721 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [846] ComConf_ComSignal_D04722 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [847] ComConf_ComSignal_D04723 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [848] ComConf_ComSignal_D04724 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [849] ComConf_ComSignal_D04725 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [850] ComConf_ComSignal_D04726 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [851] ComConf_ComSignal_FV0A8_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [852] ComConf_ComSignal_KZK0A8_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [853] ComConf_ComSignal_LK_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [854] ComConf_ComSignal_LK_FUNC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [855] ComConf_ComSignal_ULK_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [856] ComConf_ComSignal_ULK_FUNC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [857] ComConf_ComSignal_RSISIDME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [858] ComConf_ComSignal_RSISIDID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [859] ComConf_ComSignal_D04752 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [860] ComConf_ComSignal_D04753 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [861] ComConf_ComSignal_D04818 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [862] ComConf_ComSignal_D04819 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [863] ComConf_ComSignal_D04820 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [864] ComConf_ComSignal_D04821 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [865] ComConf_ComSignal_D04822 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [866] ComConf_ComSignal_D04823 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [867] ComConf_ComSignal_D04824 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [868] ComConf_ComSignal_D04825 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [869] ComConf_ComSignal_D04826 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [870] ComConf_ComSignal_LR_RC_PS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [871] ComConf_ComSignal_D04827 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [872] ComConf_ComSignal_D04828 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [873] ComConf_ComSignal_LR_SL_PS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [874] ComConf_ComSignal_D04829 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [875] ComConf_ComSignal_D04830 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [876] ComConf_ComSignal_D04831 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [877] ComConf_ComSignal_D04832 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [878] ComConf_ComSignal_D04833 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [879] ComConf_ComSignal_D04834 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [880] ComConf_ComSignal_D04835 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [881] ComConf_ComSignal_D04836 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [882] ComConf_ComSignal_D04837 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [883] ComConf_ComSignal_D04838 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [884] ComConf_ComSignal_D04839 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [885] ComConf_ComSignal_LR_LF_PS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [886] ComConf_ComSignal_D04840 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [887] ComConf_ComSignal_D04841 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [888] ComConf_ComSignal_D04842 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [889] ComConf_ComSignal_D04843 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [890] ComConf_ComSignal_D04844 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [891] ComConf_ComSignal_D04845 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [892] ComConf_ComSignal_D04846 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [893] ComConf_ComSignal_D04847 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [894] ComConf_ComSignal_D04848 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [895] ComConf_ComSignal_D04849 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [896] ComConf_ComSignal_D04850 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [897] ComConf_ComSignal_RTQRRLMG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [898] ComConf_ComSignal_RTQFRLMG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [899] ComConf_ComSignal_BAOF_PDC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [900] ComConf_ComSignal_SIDPWC0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [901] ComConf_ComSignal_SIDPWC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [902] ComConf_ComSignal_SIDPWC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [903] ComConf_ComSignal_SIDPWC3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [904] ComConf_ComSignal_SIDPWC4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [905] ComConf_ComSignal_SIDPWC5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [906] ComConf_ComSignal_SIDPWC6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [907] ComConf_ComSignal_SIDPWC7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [908] ComConf_ComSignal_SIDPWC8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [909] ComConf_ComSignal_SIDPWC9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [910] ComConf_ComSignal_SIDPWC10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [911] ComConf_ComSignal_SIDPWC11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [912] ComConf_ComSignal_SIDPWC12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [913] ComConf_ComSignal_SIDPWC13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [914] ComConf_ComSignal_SIDPWC14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [915] ComConf_ComSignal_SIDPWC15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [916] ComConf_ComSignal_SIDPWC16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [917] ComConf_ComSignal_SIDPWC17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [918] ComConf_ComSignal_SIDPWC18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [919] ComConf_ComSignal_SIDPWC19 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [920] ComConf_ComSignal_SIDPWC20 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [921] ComConf_ComSignal_SIDPWC21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [922] ComConf_ComSignal_SIDPWC22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [923] ComConf_ComSignal_SIDPWC23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [924] ComConf_ComSignal_SIDPWC24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [925] ComConf_ComSignal_SIDPWC25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [926] ComConf_ComSignal_SIDPWC26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [927] ComConf_ComSignal_SIDPWC27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [928] ComConf_ComSignal_SIDPWC28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [929] ComConf_ComSignal_SIDPWC29 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [930] ComConf_ComSignal_SIDPWC30 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [931] ComConf_ComSignal_SIDPWC31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [932] ComConf_ComSignal_E_CRC14F */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [933] ComConf_ComSignal_E_CNT14F */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [934] ComConf_ComSignal_RCPMD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [935] ComConf_ComSignal_D05431 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [936] ComConf_ComSignal_RCPFAIL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [937] ComConf_ComSignal_D05432 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [938] ComConf_ComSignal_D05433 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [939] ComConf_ComSignal_D05434 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [940] ComConf_ComSignal_RCPONST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [941] ComConf_ComSignal_D05435 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [942] ComConf_ComSignal_D05436 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [943] ComConf_ComSignal_D05441 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [944] ComConf_ComSignal_D05442 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [945] ComConf_ComSignal_D05443 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [946] ComConf_ComSignal_D05444 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [947] ComConf_ComSignal_D05445 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [948] ComConf_ComSignal_D05446 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [949] ComConf_ComSignal_D05447 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [950] ComConf_ComSignal_D05448 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [951] ComConf_ComSignal_D05449 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [952] ComConf_ComSignal_RR_RC_PS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [953] ComConf_ComSignal_D05450 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [954] ComConf_ComSignal_D05451 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [955] ComConf_ComSignal_RR_SL_PS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [956] ComConf_ComSignal_D05452 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [957] ComConf_ComSignal_D05453 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [958] ComConf_ComSignal_D05454 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [959] ComConf_ComSignal_D05455 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [960] ComConf_ComSignal_D05456 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [961] ComConf_ComSignal_D05457 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [962] ComConf_ComSignal_D05458 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [963] ComConf_ComSignal_D05459 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [964] ComConf_ComSignal_D05460 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [965] ComConf_ComSignal_D05461 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [966] ComConf_ComSignal_D05462 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [967] ComConf_ComSignal_RR_LF_PS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [968] ComConf_ComSignal_D05463 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [969] ComConf_ComSignal_D05464 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [970] ComConf_ComSignal_D05465 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [971] ComConf_ComSignal_D05466 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [972] ComConf_ComSignal_D05467 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [973] ComConf_ComSignal_D05468 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [974] ComConf_ComSignal_D05469 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [975] ComConf_ComSignal_D05470 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [976] ComConf_ComSignal_D05471 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [977] ComConf_ComSignal_D05472 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [978] ComConf_ComSignal_D05473 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [979] ComConf_ComSignal_D_YEAR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [980] ComConf_ComSignal_D_MONT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [981] ComConf_ComSignal_D_DAY */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [982] ComConf_ComSignal_D_HOUR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [983] ComConf_ComSignal_D_MIN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [984] ComConf_ComSignal_D_SEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [985] ComConf_ComSignal_D05474 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [986] ComConf_ComSignal_D05475 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [987] ComConf_ComSignal_D05476 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [988] ComConf_ComSignal_D05477 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [989] ComConf_ComSignal_D05478 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [990] ComConf_ComSignal_LATUDE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [991] ComConf_ComSignal_LOTUDE1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [992] ComConf_ComSignal_D05479 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [993] ComConf_ComSignal_D05480 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [994] ComConf_ComSignal_D_LAT1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [995] ComConf_ComSignal_D_LAT2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [996] ComConf_ComSignal_D05481 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [997] ComConf_ComSignal_D05482 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [998] ComConf_ComSignal_D05483 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [999] ComConf_ComSignal_D_LON1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1000] ComConf_ComSignal_D_LON2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1001] ComConf_ComSignal_D05484 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1002] ComConf_ComSignal_D05485 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1003] ComConf_ComSignal_D05486 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1004] ComConf_ComSignal_D05487 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1005] ComConf_ComSignal_ALTITUDE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1006] ComConf_ComSignal_OTADTYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1007] ComConf_ComSignal_OTADSTAT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1008] ComConf_ComSignal_OTADPROG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1009] ComConf_ComSignal_OTADERR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1010] ComConf_ComSignal_RSCYCL11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1011] ComConf_ComSignal_RSCYCL12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1012] ComConf_ComSignal_RSCYCL13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1013] ComConf_ComSignal_RSCYCL14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1014] ComConf_ComSignal_RSCYCL15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1015] ComConf_ComSignal_RSCYCL16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1016] ComConf_ComSignal_FRVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1017] ComConf_ComSignal_FLVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1018] ComConf_ComSignal_RRVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1019] ComConf_ComSignal_RLVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1020] ComConf_ComSignal_D05601 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1021] ComConf_ComSignal_D05602 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1022] ComConf_ComSignal_D05603 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1023] ComConf_ComSignal_D05604 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1024] ComConf_ComSignal_D05605 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1025] ComConf_ComSignal_D05606 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1026] ComConf_ComSignal_D05607 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1027] ComConf_ComSignal_D05608 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1028] ComConf_ComSignal_D05609 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1029] ComConf_ComSignal_D05610 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1030] ComConf_ComSignal_D05611 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1031] ComConf_ComSignal_D05612 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1032] ComConf_ComSignal_D05613 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1033] ComConf_ComSignal_D05614 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1034] ComConf_ComSignal_D05615 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1035] ComConf_ComSignal_D05616 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1036] ComConf_ComSignal_D05617 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1037] ComConf_ComSignal_D05618 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1038] ComConf_ComSignal_D05619 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1039] ComConf_ComSignal_D05620 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1040] ComConf_ComSignal_DVGR01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1041] ComConf_ComSignal_DVGR02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1042] ComConf_ComSignal_DVGR03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1043] ComConf_ComSignal_DVGR04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1044] ComConf_ComSignal_DVGR05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1045] ComConf_ComSignal_DVGR06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1046] ComConf_ComSignal_DVGR07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1047] ComConf_ComSignal_DVGR08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1048] ComConf_ComSignal_DVGR09 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1049] ComConf_ComSignal_DVGR10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1050] ComConf_ComSignal_DVGR11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1051] ComConf_ComSignal_DVGR12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1052] ComConf_ComSignal_DVGR13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1053] ComConf_ComSignal_DVGR14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1054] ComConf_ComSignal_DVGR15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1055] ComConf_ComSignal_DVGR16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1056] ComConf_ComSignal_DVGR17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1057] ComConf_ComSignal_DVGR18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1058] ComConf_ComSignal_DVGR19 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1059] ComConf_ComSignal_DVGR20 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1060] ComConf_ComSignal_DVGR21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1061] ComConf_ComSignal_DVGR22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1062] ComConf_ComSignal_DVGR23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1063] ComConf_ComSignal_DVGR24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1064] ComConf_ComSignal_DVGR25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1065] ComConf_ComSignal_DVGR26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1066] ComConf_ComSignal_DVGR27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1067] ComConf_ComSignal_DVGR28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1068] ComConf_ComSignal_DVGR29 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1069] ComConf_ComSignal_DVGR30 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1070] ComConf_ComSignal_DVGR31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1071] ComConf_ComSignal_DVGR32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1072] ComConf_ComSignal_DRVSCID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1073] ComConf_ComSignal_DRVSC02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1074] ComConf_ComSignal_DRVSC03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1075] ComConf_ComSignal_DRVSC04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1076] ComConf_ComSignal_DRVSC05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1077] ComConf_ComSignal_DRVSC06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1078] ComConf_ComSignal_DRVSC07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1079] ComConf_ComSignal_DRVSC08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1080] ComConf_ComSignal_DRVSC11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1081] ComConf_ComSignal_DRVSC12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1082] ComConf_ComSignal_DRVSC13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1083] ComConf_ComSignal_DRVSC14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1084] ComConf_ComSignal_DRVSC15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1085] ComConf_ComSignal_DRVSC16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1086] ComConf_ComSignal_DRVSC17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1087] ComConf_ComSignal_DRVSC18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1088] ComConf_ComSignal_DRVSC21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1089] ComConf_ComSignal_DRVSC22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1090] ComConf_ComSignal_DRVSC23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1091] ComConf_ComSignal_DRVSC24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1092] ComConf_ComSignal_DRVSC25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1093] ComConf_ComSignal_DRVSC26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1094] ComConf_ComSignal_DRVSC27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1095] ComConf_ComSignal_DRVSC28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1096] ComConf_ComSignal_DREPB01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1097] ComConf_ComSignal_DREPB02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1098] ComConf_ComSignal_DREPB03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1099] ComConf_ComSignal_DREPB04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1100] ComConf_ComSignal_DREPB05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1101] ComConf_ComSignal_DREPB06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1102] ComConf_ComSignal_DREPB07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1103] ComConf_ComSignal_DREPB08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1104] ComConf_ComSignal_E_CRC09E */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1105] ComConf_ComSignal_E_CNT09E */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1106] ComConf_ComSignal_SP1S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1107] ComConf_ComSignal_GVSPDINV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1108] ComConf_ComSignal_SP1P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1109] ComConf_ComSignal_SP1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1110] ComConf_ComSignal_GVSPD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1111] ComConf_ComSignal_D05713 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1112] ComConf_ComSignal_D05714 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1113] ComConf_ComSignal_D05715 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1114] ComConf_ComSignal_D05716 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1115] ComConf_ComSignal_PWCF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1116] ComConf_ComSignal_PWC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1117] ComConf_ComSignal_D05717 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1118] ComConf_ComSignal_PWCS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1119] ComConf_ComSignal_PMCF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1120] ComConf_ComSignal_PMCS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1121] ComConf_ComSignal_PMC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1122] ComConf_ComSignal_D05718 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1123] ComConf_ComSignal_D05719 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1124] ComConf_ComSignal_D05720 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1125] ComConf_ComSignal_D05721 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1126] ComConf_ComSignal_D05722 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1127] ComConf_ComSignal_D05723 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1128] ComConf_ComSignal_D05724 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1129] ComConf_ComSignal_D05725 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1130] ComConf_ComSignal_D05726 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1131] ComConf_ComSignal_D05727 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1132] ComConf_ComSignal_D05728 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1133] ComConf_ComSignal_D05729 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1134] ComConf_ComSignal_FV09E_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1135] ComConf_ComSignal_KZK09E_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1136] ComConf_ComSignal_FRWIPOPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1137] ComConf_ComSignal_FRWASH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1138] ComConf_ComSignal_RRWIPOPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1139] ComConf_ComSignal_RRWASH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1140] ComConf_ComSignal_D06141 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1141] ComConf_ComSignal_W_STPZ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1142] ComConf_ComSignal_FI_STP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1143] ComConf_ComSignal_D06210 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1144] ComConf_ComSignal_FV086_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1145] ComConf_ComSignal_KZK086_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1146] ComConf_ComSignal_RECRNOFF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1147] ComConf_ComSignal_FAV_FNC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1148] ComConf_ComSignal_CHG_FUNC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1149] ComConf_ComSignal_GSNSOFF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1150] ComConf_ComSignal_DRBDBABN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1151] ComConf_ComSignal_R_AC_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1152] ComConf_ComSignal_R_SYS_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1153] ComConf_ComSignal_R_FTE_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1154] ComConf_ComSignal_R_BD_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1155] ComConf_ComSignal_R_TIME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1156] ComConf_ComSignal_R_INT_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1157] ComConf_ComSignal_R_LMP_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1158] ComConf_ComSignal_R_SDE_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1159] ComConf_ComSignal_R_SYS_3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1160] ComConf_ComSignal_R_ST_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1161] ComConf_ComSignal_R_SYS_1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1162] ComConf_ComSignal_EIC_EQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1163] ComConf_ComSignal_EIC_FEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1164] ComConf_ComSignal_EIC_SEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1165] ComConf_ComSignal_EIC_IEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1166] ComConf_ComSignal_EIC_BEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1167] ComConf_ComSignal_QIC_BREQ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1168] ComConf_ComSignal_QIC_DISP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1169] ComConf_ComSignal_QIC_BVOL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1170] ComConf_ComSignal_QIC_DIS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1171] ComConf_ComSignal_EIC_DEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1172] ComConf_ComSignal_EIC_PEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1173] ComConf_ComSignal_EIC_REQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1174] ComConf_ComSignal_EIC_LEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1175] ComConf_ComSignal_AIC_DRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1176] ComConf_ComSignal_AIC_DMRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1177] ComConf_ComSignal_AIC_DFRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1178] ComConf_ComSignal_AIC_DBRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1179] ComConf_ComSignal_AIC_DRRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1180] ComConf_ComSignal_SIC_DMST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1181] ComConf_ComSignal_SIC_DCST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1182] ComConf_ComSignal_SIC_DFFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1183] ComConf_ComSignal_SIC_DFFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1184] ComConf_ComSignal_SIC_DFRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1185] ComConf_ComSignal_SIC_DFRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1186] ComConf_ComSignal_SIC_DF5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1187] ComConf_ComSignal_SIC_DFDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1188] ComConf_ComSignal_SIC_DFDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1189] ComConf_ComSignal_SIC_DF4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1190] ComConf_ComSignal_SIC_DF4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1191] ComConf_ComSignal_SIC_DF5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1192] ComConf_ComSignal_SIC_DBFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1193] ComConf_ComSignal_SIC_DBFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1194] ComConf_ComSignal_SIC_DBRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1195] ComConf_ComSignal_SIC_DBRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1196] ComConf_ComSignal_SIC_DB5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1197] ComConf_ComSignal_SIC_DBDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1198] ComConf_ComSignal_SIC_DBDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1199] ComConf_ComSignal_SIC_DB4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1200] ComConf_ComSignal_SIC_DB4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1201] ComConf_ComSignal_SIC_DB5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1202] ComConf_ComSignal_SIC_DRFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1203] ComConf_ComSignal_SIC_DRRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1204] ComConf_ComSignal_SIC_DRDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1205] ComConf_ComSignal_SIC_DR4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1206] ComConf_ComSignal_SIC_DR5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1207] ComConf_ComSignal_SIC_DRFK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1208] ComConf_ComSignal_SIC_DRRK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1209] ComConf_ComSignal_SIC_DRDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1210] ComConf_ComSignal_SIC_DR4K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1211] ComConf_ComSignal_SIC_DR5K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1212] ComConf_ComSignal_AIC_PRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1213] ComConf_ComSignal_AIC_PMRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1214] ComConf_ComSignal_AIC_PFRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1215] ComConf_ComSignal_AIC_PBRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1216] ComConf_ComSignal_AIC_PRRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1217] ComConf_ComSignal_SIC_PMST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1218] ComConf_ComSignal_SIC_PCST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1219] ComConf_ComSignal_SIC_PFFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1220] ComConf_ComSignal_SIC_PFFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1221] ComConf_ComSignal_SIC_PFRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1222] ComConf_ComSignal_SIC_PFRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1223] ComConf_ComSignal_SIC_PF5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1224] ComConf_ComSignal_SIC_PFDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1225] ComConf_ComSignal_SIC_PFDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1226] ComConf_ComSignal_SIC_PF4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1227] ComConf_ComSignal_SIC_PF4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1228] ComConf_ComSignal_SIC_PF5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1229] ComConf_ComSignal_SIC_PBFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1230] ComConf_ComSignal_SIC_PBFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1231] ComConf_ComSignal_SIC_PBRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1232] ComConf_ComSignal_SIC_PBRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1233] ComConf_ComSignal_SIC_PB5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1234] ComConf_ComSignal_SIC_PBDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1235] ComConf_ComSignal_SIC_PBDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1236] ComConf_ComSignal_SIC_PB4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1237] ComConf_ComSignal_SIC_PB4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1238] ComConf_ComSignal_SIC_PB5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1239] ComConf_ComSignal_SIC_PRFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1240] ComConf_ComSignal_SIC_PRRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1241] ComConf_ComSignal_SIC_PRDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1242] ComConf_ComSignal_SIC_PR4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1243] ComConf_ComSignal_SIC_PR5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1244] ComConf_ComSignal_SIC_PRFK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1245] ComConf_ComSignal_SIC_PRRK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1246] ComConf_ComSignal_SIC_PRDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1247] ComConf_ComSignal_SIC_PR4K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1248] ComConf_ComSignal_SIC_PR5K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1249] ComConf_ComSignal_AIC_RRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1250] ComConf_ComSignal_AIC_RMRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1251] ComConf_ComSignal_AIC_RFRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1252] ComConf_ComSignal_AIC_RBRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1253] ComConf_ComSignal_AIC_RRRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1254] ComConf_ComSignal_SIC_RMST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1255] ComConf_ComSignal_SIC_RCST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1256] ComConf_ComSignal_SIC_RFFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1257] ComConf_ComSignal_SIC_RFFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1258] ComConf_ComSignal_SIC_RFRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1259] ComConf_ComSignal_SIC_RFRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1260] ComConf_ComSignal_SIC_RF5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1261] ComConf_ComSignal_SIC_RFDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1262] ComConf_ComSignal_SIC_RFDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1263] ComConf_ComSignal_SIC_RF4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1264] ComConf_ComSignal_SIC_RF4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1265] ComConf_ComSignal_SIC_RF5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1266] ComConf_ComSignal_SIC_RBFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1267] ComConf_ComSignal_SIC_RBFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1268] ComConf_ComSignal_SIC_RBRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1269] ComConf_ComSignal_SIC_RBRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1270] ComConf_ComSignal_SIC_RB5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1271] ComConf_ComSignal_SIC_RBDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1272] ComConf_ComSignal_SIC_RBDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1273] ComConf_ComSignal_SIC_RB4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1274] ComConf_ComSignal_SIC_RB4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1275] ComConf_ComSignal_SIC_RB5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1276] ComConf_ComSignal_SIC_RRFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1277] ComConf_ComSignal_SIC_RRRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1278] ComConf_ComSignal_SIC_RRDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1279] ComConf_ComSignal_SIC_RR4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1280] ComConf_ComSignal_SIC_RR5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1281] ComConf_ComSignal_SIC_RRFK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1282] ComConf_ComSignal_SIC_RRRK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1283] ComConf_ComSignal_SIC_RRDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1284] ComConf_ComSignal_SIC_RR4K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1285] ComConf_ComSignal_SIC_RR5K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1286] ComConf_ComSignal_AIC_LRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1287] ComConf_ComSignal_AIC_LMRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1288] ComConf_ComSignal_AIC_LFRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1289] ComConf_ComSignal_AIC_LBRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1290] ComConf_ComSignal_AIC_LRRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1291] ComConf_ComSignal_SIC_LMST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1292] ComConf_ComSignal_SIC_LCST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1293] ComConf_ComSignal_SIC_LFFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1294] ComConf_ComSignal_SIC_LFFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1295] ComConf_ComSignal_SIC_LFRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1296] ComConf_ComSignal_SIC_LFRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1297] ComConf_ComSignal_SIC_LF5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1298] ComConf_ComSignal_SIC_LFDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1299] ComConf_ComSignal_SIC_LFDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1300] ComConf_ComSignal_SIC_LF4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1301] ComConf_ComSignal_SIC_LF4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1302] ComConf_ComSignal_SIC_LF5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1303] ComConf_ComSignal_SIC_LBFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1304] ComConf_ComSignal_SIC_LBFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1305] ComConf_ComSignal_SIC_LBRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1306] ComConf_ComSignal_SIC_LBRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1307] ComConf_ComSignal_SIC_LB5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1308] ComConf_ComSignal_SIC_LBDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1309] ComConf_ComSignal_SIC_LBDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1310] ComConf_ComSignal_SIC_LB4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1311] ComConf_ComSignal_SIC_LB4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1312] ComConf_ComSignal_SIC_LB5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1313] ComConf_ComSignal_SIC_LRFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1314] ComConf_ComSignal_SIC_LRRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1315] ComConf_ComSignal_SIC_LRDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1316] ComConf_ComSignal_SIC_LR4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1317] ComConf_ComSignal_SIC_LR5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1318] ComConf_ComSignal_SIC_LRFK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1319] ComConf_ComSignal_SIC_LRRK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1320] ComConf_ComSignal_SIC_LRDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1321] ComConf_ComSignal_SIC_LR4K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1322] ComConf_ComSignal_SIC_LR5K */
};

BswConst PduIdType bsw_com_u2DataHdl2MsgHdl[BSW_COM_HANDLE_NUM] = {
     (BswU2)0U                                                                                                   /* [0] ComConf_ComSignal_ETHWU_21 */
    ,(BswU2)0U                                                                                                   /* [1] ComConf_ComSignal_ETHWU_23 */
    ,(BswU2)1U                                                                                                   /* [2] ComConf_ComSignal_DRABG01 */
    ,(BswU2)1U                                                                                                   /* [3] ComConf_ComSignal_DRABG02 */
    ,(BswU2)1U                                                                                                   /* [4] ComConf_ComSignal_DRABG03 */
    ,(BswU2)1U                                                                                                   /* [5] ComConf_ComSignal_DRABG04 */
    ,(BswU2)1U                                                                                                   /* [6] ComConf_ComSignal_DRABG05 */
    ,(BswU2)1U                                                                                                   /* [7] ComConf_ComSignal_DRABG06 */
    ,(BswU2)1U                                                                                                   /* [8] ComConf_ComSignal_DRABG07 */
    ,(BswU2)1U                                                                                                   /* [9] ComConf_ComSignal_DRABG08 */
    ,(BswU2)2U                                                                                                   /* [10] ComConf_ComSignal_DRABG09 */
    ,(BswU2)2U                                                                                                   /* [11] ComConf_ComSignal_DRABG10 */
    ,(BswU2)2U                                                                                                   /* [12] ComConf_ComSignal_DRABG11 */
    ,(BswU2)2U                                                                                                   /* [13] ComConf_ComSignal_DRABG12 */
    ,(BswU2)2U                                                                                                   /* [14] ComConf_ComSignal_DRABG13 */
    ,(BswU2)2U                                                                                                   /* [15] ComConf_ComSignal_DRABG14 */
    ,(BswU2)2U                                                                                                   /* [16] ComConf_ComSignal_DRABG15 */
    ,(BswU2)2U                                                                                                   /* [17] ComConf_ComSignal_DRABG16 */
    ,(BswU2)3U                                                                                                   /* [18] ComConf_ComSignal_D00024 */
    ,(BswU2)3U                                                                                                   /* [19] ComConf_ComSignal_D00025 */
    ,(BswU2)3U                                                                                                   /* [20] ComConf_ComSignal_D00026 */
    ,(BswU2)3U                                                                                                   /* [21] ComConf_ComSignal_D00027 */
    ,(BswU2)3U                                                                                                   /* [22] ComConf_ComSignal_FLGXMAX */
    ,(BswU2)3U                                                                                                   /* [23] ComConf_ComSignal_D00028 */
    ,(BswU2)3U                                                                                                   /* [24] ComConf_ComSignal_D00029 */
    ,(BswU2)3U                                                                                                   /* [25] ComConf_ComSignal_D00030 */
    ,(BswU2)3U                                                                                                   /* [26] ComConf_ComSignal_FLVNMAX */
    ,(BswU2)3U                                                                                                   /* [27] ComConf_ComSignal_FRGMAX_L */
    ,(BswU2)3U                                                                                                   /* [28] ComConf_ComSignal_FRGMAX_R */
    ,(BswU2)3U                                                                                                   /* [29] ComConf_ComSignal_D00031 */
    ,(BswU2)3U                                                                                                   /* [30] ComConf_ComSignal_D00032 */
    ,(BswU2)3U                                                                                                   /* [31] ComConf_ComSignal_D00033 */
    ,(BswU2)3U                                                                                                   /* [32] ComConf_ComSignal_D00034 */
    ,(BswU2)3U                                                                                                   /* [33] ComConf_ComSignal_D00035 */
    ,(BswU2)3U                                                                                                   /* [34] ComConf_ComSignal_D00036 */
    ,(BswU2)3U                                                                                                   /* [35] ComConf_ComSignal_PT_ON */
    ,(BswU2)3U                                                                                                   /* [36] ComConf_ComSignal_FRAB_ON */
    ,(BswU2)3U                                                                                                   /* [37] ComConf_ComSignal_D00037 */
    ,(BswU2)3U                                                                                                   /* [38] ComConf_ComSignal_D00038 */
    ,(BswU2)3U                                                                                                   /* [39] ComConf_ComSignal_D00039 */
    ,(BswU2)3U                                                                                                   /* [40] ComConf_ComSignal_D00040 */
    ,(BswU2)3U                                                                                                   /* [41] ComConf_ComSignal_D00041 */
    ,(BswU2)3U                                                                                                   /* [42] ComConf_ComSignal_D00042 */
    ,(BswU2)3U                                                                                                   /* [43] ComConf_ComSignal_D00043 */
    ,(BswU2)3U                                                                                                   /* [44] ComConf_ComSignal_D00044 */
    ,(BswU2)3U                                                                                                   /* [45] ComConf_ComSignal_D00045 */
    ,(BswU2)3U                                                                                                   /* [46] ComConf_ComSignal_D00046 */
    ,(BswU2)4U                                                                                                   /* [47] ComConf_ComSignal_DRACN01 */
    ,(BswU2)4U                                                                                                   /* [48] ComConf_ComSignal_DRACN02 */
    ,(BswU2)4U                                                                                                   /* [49] ComConf_ComSignal_DRACN03 */
    ,(BswU2)4U                                                                                                   /* [50] ComConf_ComSignal_DRACN04 */
    ,(BswU2)4U                                                                                                   /* [51] ComConf_ComSignal_DRACN05 */
    ,(BswU2)4U                                                                                                   /* [52] ComConf_ComSignal_DRACN06 */
    ,(BswU2)4U                                                                                                   /* [53] ComConf_ComSignal_DRACN07 */
    ,(BswU2)4U                                                                                                   /* [54] ComConf_ComSignal_DRACN08 */
    ,(BswU2)5U                                                                                                   /* [55] ComConf_ComSignal_D00075 */
    ,(BswU2)5U                                                                                                   /* [56] ComConf_ComSignal_D00076 */
    ,(BswU2)5U                                                                                                   /* [57] ComConf_ComSignal_D00077 */
    ,(BswU2)5U                                                                                                   /* [58] ComConf_ComSignal_O_STG_F */
    ,(BswU2)5U                                                                                                   /* [59] ComConf_ComSignal_D00078 */
    ,(BswU2)5U                                                                                                   /* [60] ComConf_ComSignal_D00079 */
    ,(BswU2)5U                                                                                                   /* [61] ComConf_ComSignal_AC_CDSP */
    ,(BswU2)5U                                                                                                   /* [62] ComConf_ComSignal_D00080 */
    ,(BswU2)6U                                                                                                   /* [63] ComConf_ComSignal_D00092 */
    ,(BswU2)6U                                                                                                   /* [64] ComConf_ComSignal_TRTEMP_P */
    ,(BswU2)6U                                                                                                   /* [65] ComConf_ComSignal_I_BLWF_P */
    ,(BswU2)6U                                                                                                   /* [66] ComConf_ComSignal_D00093 */
    ,(BswU2)6U                                                                                                   /* [67] ComConf_ComSignal_D00094 */
    ,(BswU2)6U                                                                                                   /* [68] ComConf_ComSignal_D00095 */
    ,(BswU2)6U                                                                                                   /* [69] ComConf_ComSignal_D00096 */
    ,(BswU2)7U                                                                                                   /* [70] ComConf_ComSignal_D00109 */
    ,(BswU2)7U                                                                                                   /* [71] ComConf_ComSignal_D00110 */
    ,(BswU2)7U                                                                                                   /* [72] ComConf_ComSignal_D00111 */
    ,(BswU2)7U                                                                                                   /* [73] ComConf_ComSignal_D00112 */
    ,(BswU2)7U                                                                                                   /* [74] ComConf_ComSignal_D00113 */
    ,(BswU2)7U                                                                                                   /* [75] ComConf_ComSignal_D00114 */
    ,(BswU2)7U                                                                                                   /* [76] ComConf_ComSignal_D00115 */
    ,(BswU2)7U                                                                                                   /* [77] ComConf_ComSignal_D00116 */
    ,(BswU2)7U                                                                                                   /* [78] ComConf_ComSignal_D00117 */
    ,(BswU2)7U                                                                                                   /* [79] ComConf_ComSignal_D00118 */
    ,(BswU2)7U                                                                                                   /* [80] ComConf_ComSignal_D00119 */
    ,(BswU2)7U                                                                                                   /* [81] ComConf_ComSignal_D00120 */
    ,(BswU2)7U                                                                                                   /* [82] ComConf_ComSignal_D00121 */
    ,(BswU2)7U                                                                                                   /* [83] ComConf_ComSignal_D00122 */
    ,(BswU2)7U                                                                                                   /* [84] ComConf_ComSignal_D00123 */
    ,(BswU2)7U                                                                                                   /* [85] ComConf_ComSignal_D00124 */
    ,(BswU2)7U                                                                                                   /* [86] ComConf_ComSignal_HQ_COMP */
    ,(BswU2)8U                                                                                                   /* [87] ComConf_ComSignal_D00135 */
    ,(BswU2)8U                                                                                                   /* [88] ComConf_ComSignal_D00136 */
    ,(BswU2)8U                                                                                                   /* [89] ComConf_ComSignal_D00137 */
    ,(BswU2)8U                                                                                                   /* [90] ComConf_ComSignal_D00138 */
    ,(BswU2)8U                                                                                                   /* [91] ComConf_ComSignal_R_SHHTFL */
    ,(BswU2)8U                                                                                                   /* [92] ComConf_ComSignal_D00139 */
    ,(BswU2)8U                                                                                                   /* [93] ComConf_ComSignal_R_SHHTFR */
    ,(BswU2)8U                                                                                                   /* [94] ComConf_ComSignal_D00140 */
    ,(BswU2)8U                                                                                                   /* [95] ComConf_ComSignal_D00141 */
    ,(BswU2)8U                                                                                                   /* [96] ComConf_ComSignal_D00142 */
    ,(BswU2)8U                                                                                                   /* [97] ComConf_ComSignal_D00143 */
    ,(BswU2)8U                                                                                                   /* [98] ComConf_ComSignal_D00144 */
    ,(BswU2)8U                                                                                                   /* [99] ComConf_ComSignal_D00145 */
    ,(BswU2)8U                                                                                                   /* [100] ComConf_ComSignal_D00146 */
    ,(BswU2)8U                                                                                                   /* [101] ComConf_ComSignal_D00147 */
    ,(BswU2)8U                                                                                                   /* [102] ComConf_ComSignal_RSVFLDU */
    ,(BswU2)8U                                                                                                   /* [103] ComConf_ComSignal_D00148 */
    ,(BswU2)8U                                                                                                   /* [104] ComConf_ComSignal_RSVFRDU */
    ,(BswU2)8U                                                                                                   /* [105] ComConf_ComSignal_D00149 */
    ,(BswU2)8U                                                                                                   /* [106] ComConf_ComSignal_R_SHHTRL */
    ,(BswU2)8U                                                                                                   /* [107] ComConf_ComSignal_D00150 */
    ,(BswU2)8U                                                                                                   /* [108] ComConf_ComSignal_R_SHHTRR */
    ,(BswU2)8U                                                                                                   /* [109] ComConf_ComSignal_D00151 */
    ,(BswU2)8U                                                                                                   /* [110] ComConf_ComSignal_D00152 */
    ,(BswU2)8U                                                                                                   /* [111] ComConf_ComSignal_D00153 */
    ,(BswU2)8U                                                                                                   /* [112] ComConf_ComSignal_D00154 */
    ,(BswU2)8U                                                                                                   /* [113] ComConf_ComSignal_D00155 */
    ,(BswU2)8U                                                                                                   /* [114] ComConf_ComSignal_D00156 */
    ,(BswU2)8U                                                                                                   /* [115] ComConf_ComSignal_D00157 */
    ,(BswU2)8U                                                                                                   /* [116] ComConf_ComSignal_D00158 */
    ,(BswU2)8U                                                                                                   /* [117] ComConf_ComSignal_D00159 */
    ,(BswU2)8U                                                                                                   /* [118] ComConf_ComSignal_RSVRLDU */
    ,(BswU2)8U                                                                                                   /* [119] ComConf_ComSignal_D00160 */
    ,(BswU2)8U                                                                                                   /* [120] ComConf_ComSignal_RSVRRDU */
    ,(BswU2)8U                                                                                                   /* [121] ComConf_ComSignal_D00161 */
    ,(BswU2)8U                                                                                                   /* [122] ComConf_ComSignal_R_RDHRR */
    ,(BswU2)8U                                                                                                   /* [123] ComConf_ComSignal_D00162 */
    ,(BswU2)8U                                                                                                   /* [124] ComConf_ComSignal_R_RDHRL */
    ,(BswU2)8U                                                                                                   /* [125] ComConf_ComSignal_D00163 */
    ,(BswU2)8U                                                                                                   /* [126] ComConf_ComSignal_R_RDHFP */
    ,(BswU2)8U                                                                                                   /* [127] ComConf_ComSignal_D00164 */
    ,(BswU2)8U                                                                                                   /* [128] ComConf_ComSignal_R_RDHFD */
    ,(BswU2)8U                                                                                                   /* [129] ComConf_ComSignal_D00165 */
    ,(BswU2)8U                                                                                                   /* [130] ComConf_ComSignal_D00166 */
    ,(BswU2)8U                                                                                                   /* [131] ComConf_ComSignal_D00167 */
    ,(BswU2)8U                                                                                                   /* [132] ComConf_ComSignal_D00168 */
    ,(BswU2)9U                                                                                                   /* [133] ComConf_ComSignal_WS_VD_R */
    ,(BswU2)9U                                                                                                   /* [134] ComConf_ComSignal_WS_FTG_R */
    ,(BswU2)9U                                                                                                   /* [135] ComConf_ComSignal_WS_ABH_R */
    ,(BswU2)9U                                                                                                   /* [136] ComConf_ComSignal_WS_APO_R */
    ,(BswU2)10U                                                                                                  /* [137] ComConf_ComSignal_ETHWU_12 */
    ,(BswU2)10U                                                                                                  /* [138] ComConf_ComSignal_D00214 */
    ,(BswU2)11U                                                                                                  /* [139] ComConf_ComSignal_APPMD2 */
    ,(BswU2)11U                                                                                                  /* [140] ComConf_ComSignal_D00215 */
    ,(BswU2)11U                                                                                                  /* [141] ComConf_ComSignal_D00216 */
    ,(BswU2)11U                                                                                                  /* [142] ComConf_ComSignal_D00217 */
    ,(BswU2)11U                                                                                                  /* [143] ComConf_ComSignal_FV1C0_D */
    ,(BswU2)11U                                                                                                  /* [144] ComConf_ComSignal_KZK1C0_D */
    ,(BswU2)12U                                                                                                  /* [145] ComConf_ComSignal_ACCMAPP */
    ,(BswU2)12U                                                                                                  /* [146] ComConf_ComSignal_ACCMMOD */
    ,(BswU2)13U                                                                                                  /* [147] ComConf_ComSignal_ACCMDST */
    ,(BswU2)13U                                                                                                  /* [148] ComConf_ComSignal_ACCMPHS */
    ,(BswU2)13U                                                                                                  /* [149] ComConf_ComSignal_ACCMSGN */
    ,(BswU2)13U                                                                                                  /* [150] ComConf_ComSignal_ACCMRCG */
    ,(BswU2)13U                                                                                                  /* [151] ComConf_ComSignal_ACCMARB */
    ,(BswU2)14U                                                                                                  /* [152] ComConf_ComSignal_LDASTATL */
    ,(BswU2)14U                                                                                                  /* [153] ComConf_ComSignal_LDASTATR */
    ,(BswU2)14U                                                                                                  /* [154] ComConf_ComSignal_LDARSN */
    ,(BswU2)14U                                                                                                  /* [155] ComConf_ComSignal_FCMINTMP */
    ,(BswU2)14U                                                                                                  /* [156] ComConf_ComSignal_LDARCGL */
    ,(BswU2)14U                                                                                                  /* [157] ComConf_ComSignal_LDARCGR */
    ,(BswU2)14U                                                                                                  /* [158] ComConf_ComSignal_SWSSTAT */
    ,(BswU2)14U                                                                                                  /* [159] ComConf_ComSignal_V_IDACCL */
    ,(BswU2)14U                                                                                                  /* [160] ComConf_ComSignal_EJDEVPRD */
    ,(BswU2)14U                                                                                                  /* [161] ComConf_ComSignal_EJLDACP */
    ,(BswU2)14U                                                                                                  /* [162] ComConf_ComSignal_V_IDANOA */
    ,(BswU2)14U                                                                                                  /* [163] ComConf_ComSignal_V_IDARGL */
    ,(BswU2)14U                                                                                                  /* [164] ComConf_ComSignal_PV_AREA */
    ,(BswU2)14U                                                                                                  /* [165] ComConf_ComSignal_DM_PVMVW */
    ,(BswU2)14U                                                                                                  /* [166] ComConf_ComSignal_DM_PVMCS */
    ,(BswU2)14U                                                                                                  /* [167] ComConf_ComSignal_ERMCNTST */
    ,(BswU2)14U                                                                                                  /* [168] ComConf_ComSignal_GAE_H_R3 */
    ,(BswU2)14U                                                                                                  /* [169] ComConf_ComSignal_FRDHTR_G */
    ,(BswU2)14U                                                                                                  /* [170] ComConf_ComSignal_SDIRT_G */
    ,(BswU2)14U                                                                                                  /* [171] ComConf_ComSignal_GAE_V_R1 */
    ,(BswU2)14U                                                                                                  /* [172] ComConf_ComSignal_DRTCNT_G */
    ,(BswU2)14U                                                                                                  /* [173] ComConf_ComSignal_GAERR1_V */
    ,(BswU2)14U                                                                                                  /* [174] ComConf_ComSignal_GAEVAL_H */
    ,(BswU2)14U                                                                                                  /* [175] ComConf_ComSignal_GAERR3_H */
    ,(BswU2)14U                                                                                                  /* [176] ComConf_ComSignal_DTSSSTR */
    ,(BswU2)14U                                                                                                  /* [177] ComConf_ComSignal_DTSSLTID */
    ,(BswU2)14U                                                                                                  /* [178] ComConf_ComSignal_MDSYNC00 */
    ,(BswU2)15U                                                                                                  /* [179] ComConf_ComSignal_BIB_G */
    ,(BswU2)15U                                                                                                  /* [180] ComConf_ComSignal_VCELMAXG */
    ,(BswU2)15U                                                                                                  /* [181] ComConf_ComSignal_VCELMING */
    ,(BswU2)15U                                                                                                  /* [182] ComConf_ComSignal_RAHRMAXG */
    ,(BswU2)15U                                                                                                  /* [183] ComConf_ComSignal_RAHRMING */
    ,(BswU2)15U                                                                                                  /* [184] ComConf_ComSignal_TC_G */
    ,(BswU2)15U                                                                                                  /* [185] ComConf_ComSignal_TBMAX_G */
    ,(BswU2)15U                                                                                                  /* [186] ComConf_ComSignal_TBMIN_G */
    ,(BswU2)15U                                                                                                  /* [187] ComConf_ComSignal_D00520 */
    ,(BswU2)15U                                                                                                  /* [188] ComConf_ComSignal_D00521 */
    ,(BswU2)15U                                                                                                  /* [189] ComConf_ComSignal_D00522 */
    ,(BswU2)16U                                                                                                  /* [190] ComConf_ComSignal_D_IB */
    ,(BswU2)16U                                                                                                  /* [191] ComConf_ComSignal_D_VB */
    ,(BswU2)16U                                                                                                  /* [192] ComConf_ComSignal_D_VBMAX */
    ,(BswU2)16U                                                                                                  /* [193] ComConf_ComSignal_D_VBMIN */
    ,(BswU2)16U                                                                                                  /* [194] ComConf_ComSignal_D_VMAXN */
    ,(BswU2)16U                                                                                                  /* [195] ComConf_ComSignal_D_VMINN */
    ,(BswU2)16U                                                                                                  /* [196] ComConf_ComSignal_D_TBMAX */
    ,(BswU2)16U                                                                                                  /* [197] ComConf_ComSignal_D_TBMIN */
    ,(BswU2)16U                                                                                                  /* [198] ComConf_ComSignal_D_TBMAXN */
    ,(BswU2)16U                                                                                                  /* [199] ComConf_ComSignal_D_TBMINN */
    ,(BswU2)16U                                                                                                  /* [200] ComConf_ComSignal_D_SOC */
    ,(BswU2)16U                                                                                                  /* [201] ComConf_ComSignal_D_BATENE */
    ,(BswU2)16U                                                                                                  /* [202] ComConf_ComSignal_D_BERG1 */
    ,(BswU2)16U                                                                                                  /* [203] ComConf_ComSignal_D_BERG2 */
    ,(BswU2)16U                                                                                                  /* [204] ComConf_ComSignal_D_BERG3 */
    ,(BswU2)16U                                                                                                  /* [205] ComConf_ComSignal_D_BALM_1 */
    ,(BswU2)16U                                                                                                  /* [206] ComConf_ComSignal_D_BALM_2 */
    ,(BswU2)16U                                                                                                  /* [207] ComConf_ComSignal_D_BALM_3 */
    ,(BswU2)16U                                                                                                  /* [208] ComConf_ComSignal_D_BALM_4 */
    ,(BswU2)16U                                                                                                  /* [209] ComConf_ComSignal_D_BALM_5 */
    ,(BswU2)16U                                                                                                  /* [210] ComConf_ComSignal_D_BCODE1 */
    ,(BswU2)16U                                                                                                  /* [211] ComConf_ComSignal_D_BCODE2 */
    ,(BswU2)16U                                                                                                  /* [212] ComConf_ComSignal_D_BCODE3 */
    ,(BswU2)16U                                                                                                  /* [213] ComConf_ComSignal_D_BCODE4 */
    ,(BswU2)16U                                                                                                  /* [214] ComConf_ComSignal_D_BCODE5 */
    ,(BswU2)16U                                                                                                  /* [215] ComConf_ComSignal_D_BCODE6 */
    ,(BswU2)16U                                                                                                  /* [216] ComConf_ComSignal_D_BCODE7 */
    ,(BswU2)16U                                                                                                  /* [217] ComConf_ComSignal_D_BCODE8 */
    ,(BswU2)17U                                                                                                  /* [218] ComConf_ComSignal_D_VCELCH */
    ,(BswU2)17U                                                                                                  /* [219] ComConf_ComSignal_D_VCELL0 */
    ,(BswU2)17U                                                                                                  /* [220] ComConf_ComSignal_D_VCELL1 */
    ,(BswU2)17U                                                                                                  /* [221] ComConf_ComSignal_D_VCELL2 */
    ,(BswU2)17U                                                                                                  /* [222] ComConf_ComSignal_D_VCELL3 */
    ,(BswU2)18U                                                                                                  /* [223] ComConf_ComSignal_D_TBCH */
    ,(BswU2)18U                                                                                                  /* [224] ComConf_ComSignal_D_TB0 */
    ,(BswU2)18U                                                                                                  /* [225] ComConf_ComSignal_D_TB1 */
    ,(BswU2)18U                                                                                                  /* [226] ComConf_ComSignal_D_TB2 */
    ,(BswU2)18U                                                                                                  /* [227] ComConf_ComSignal_D_TB3 */
    ,(BswU2)18U                                                                                                  /* [228] ComConf_ComSignal_D_TB4 */
    ,(BswU2)18U                                                                                                  /* [229] ComConf_ComSignal_D_TB5 */
    ,(BswU2)18U                                                                                                  /* [230] ComConf_ComSignal_D_TB6 */
    ,(BswU2)19U                                                                                                  /* [231] ComConf_ComSignal_D_MINFAD */
    ,(BswU2)19U                                                                                                  /* [232] ComConf_ComSignal_D_MINFO1 */
    ,(BswU2)19U                                                                                                  /* [233] ComConf_ComSignal_D_MINFO2 */
    ,(BswU2)19U                                                                                                  /* [234] ComConf_ComSignal_D_MINFO3 */
    ,(BswU2)20U                                                                                                  /* [235] ComConf_ComSignal_D_BVIN1 */
    ,(BswU2)20U                                                                                                  /* [236] ComConf_ComSignal_D_BVIN2 */
    ,(BswU2)20U                                                                                                  /* [237] ComConf_ComSignal_D_BVIN3 */
    ,(BswU2)20U                                                                                                  /* [238] ComConf_ComSignal_D_BVIN4 */
    ,(BswU2)20U                                                                                                  /* [239] ComConf_ComSignal_D_BVIN5 */
    ,(BswU2)20U                                                                                                  /* [240] ComConf_ComSignal_D_BVIN6 */
    ,(BswU2)20U                                                                                                  /* [241] ComConf_ComSignal_D_BVIN7 */
    ,(BswU2)20U                                                                                                  /* [242] ComConf_ComSignal_D_BVIN8 */
    ,(BswU2)20U                                                                                                  /* [243] ComConf_ComSignal_D_BVIN9 */
    ,(BswU2)20U                                                                                                  /* [244] ComConf_ComSignal_D_BVIN10 */
    ,(BswU2)20U                                                                                                  /* [245] ComConf_ComSignal_D_BVIN11 */
    ,(BswU2)20U                                                                                                  /* [246] ComConf_ComSignal_D_BVIN12 */
    ,(BswU2)20U                                                                                                  /* [247] ComConf_ComSignal_D_BVIN13 */
    ,(BswU2)20U                                                                                                  /* [248] ComConf_ComSignal_D_BVIN14 */
    ,(BswU2)20U                                                                                                  /* [249] ComConf_ComSignal_D_BVIN15 */
    ,(BswU2)20U                                                                                                  /* [250] ComConf_ComSignal_D_BVIN16 */
    ,(BswU2)20U                                                                                                  /* [251] ComConf_ComSignal_D_BVIN17 */
    ,(BswU2)20U                                                                                                  /* [252] ComConf_ComSignal_D_BVIN18 */
    ,(BswU2)20U                                                                                                  /* [253] ComConf_ComSignal_D_BVIN19 */
    ,(BswU2)20U                                                                                                  /* [254] ComConf_ComSignal_D_BVIN20 */
    ,(BswU2)20U                                                                                                  /* [255] ComConf_ComSignal_D_BVIN21 */
    ,(BswU2)20U                                                                                                  /* [256] ComConf_ComSignal_D_BVIN22 */
    ,(BswU2)20U                                                                                                  /* [257] ComConf_ComSignal_D_BVIN23 */
    ,(BswU2)20U                                                                                                  /* [258] ComConf_ComSignal_D_BVIN24 */
    ,(BswU2)21U                                                                                                  /* [259] ComConf_ComSignal_D00596 */
    ,(BswU2)21U                                                                                                  /* [260] ComConf_ComSignal_D00597 */
    ,(BswU2)21U                                                                                                  /* [261] ComConf_ComSignal_D00598 */
    ,(BswU2)21U                                                                                                  /* [262] ComConf_ComSignal_D00599 */
    ,(BswU2)21U                                                                                                  /* [263] ComConf_ComSignal_BTWO */
    ,(BswU2)21U                                                                                                  /* [264] ComConf_ComSignal_D00600 */
    ,(BswU2)21U                                                                                                  /* [265] ComConf_ComSignal_D00601 */
    ,(BswU2)21U                                                                                                  /* [266] ComConf_ComSignal_D00602 */
    ,(BswU2)21U                                                                                                  /* [267] ComConf_ComSignal_D00603 */
    ,(BswU2)21U                                                                                                  /* [268] ComConf_ComSignal_D00604 */
    ,(BswU2)22U                                                                                                  /* [269] ComConf_ComSignal_BITGB1 */
    ,(BswU2)22U                                                                                                  /* [270] ComConf_ComSignal_BITGB2 */
    ,(BswU2)22U                                                                                                  /* [271] ComConf_ComSignal_BITGB3 */
    ,(BswU2)22U                                                                                                  /* [272] ComConf_ComSignal_BITGB4 */
    ,(BswU2)22U                                                                                                  /* [273] ComConf_ComSignal_STKNUM */
    ,(BswU2)22U                                                                                                  /* [274] ComConf_ComSignal_BITGB5 */
    ,(BswU2)22U                                                                                                  /* [275] ComConf_ComSignal_VCELNUM */
    ,(BswU2)22U                                                                                                  /* [276] ComConf_ComSignal_INFGB1 */
    ,(BswU2)22U                                                                                                  /* [277] ComConf_ComSignal_TMINNUM */
    ,(BswU2)22U                                                                                                  /* [278] ComConf_ComSignal_INFGB2 */
    ,(BswU2)22U                                                                                                  /* [279] ComConf_ComSignal_TMAXNUM */
    ,(BswU2)22U                                                                                                  /* [280] ComConf_ComSignal_VBTINF */
    ,(BswU2)22U                                                                                                  /* [281] ComConf_ComSignal_SOCINF */
    ,(BswU2)22U                                                                                                  /* [282] ComConf_ComSignal_IBTINF */
    ,(BswU2)22U                                                                                                  /* [283] ComConf_ComSignal_TBTINF */
    ,(BswU2)22U                                                                                                  /* [284] ComConf_ComSignal_STPSOC */
    ,(BswU2)22U                                                                                                  /* [285] ComConf_ComSignal_STPVB */
    ,(BswU2)22U                                                                                                  /* [286] ComConf_ComSignal_STPCELV */
    ,(BswU2)22U                                                                                                  /* [287] ComConf_ComSignal_STPTMP */
    ,(BswU2)22U                                                                                                  /* [288] ComConf_ComSignal_DATAGB2 */
    ,(BswU2)22U                                                                                                  /* [289] ComConf_ComSignal_DATAGB3 */
    ,(BswU2)23U                                                                                                  /* [290] ComConf_ComSignal_ID63B16 */
    ,(BswU2)23U                                                                                                  /* [291] ComConf_ComSignal_IF63B16 */
    ,(BswU2)23U                                                                                                  /* [292] ComConf_ComSignal_TRIP_CNT */
    ,(BswU2)23U                                                                                                  /* [293] ComConf_ComSignal_TIME_CNT */
    ,(BswU2)24U                                                                                                  /* [294] ComConf_ComSignal_D00809 */
    ,(BswU2)24U                                                                                                  /* [295] ComConf_ComSignal_D00810 */
    ,(BswU2)24U                                                                                                  /* [296] ComConf_ComSignal_IL_FDOME */
    ,(BswU2)24U                                                                                                  /* [297] ComConf_ComSignal_IL_LOUNG */
    ,(BswU2)24U                                                                                                  /* [298] ComConf_ComSignal_IL_OSSTP */
    ,(BswU2)24U                                                                                                  /* [299] ComConf_ComSignal_AMB_COP */
    ,(BswU2)24U                                                                                                  /* [300] ComConf_ComSignal_SUPRQ */
    ,(BswU2)24U                                                                                                  /* [301] ComConf_ComSignal_D00811 */
    ,(BswU2)24U                                                                                                  /* [302] ComConf_ComSignal_D00812 */
    ,(BswU2)25U                                                                                                  /* [303] ComConf_ComSignal_THEFTD1 */
    ,(BswU2)25U                                                                                                  /* [304] ComConf_ComSignal_THEFTD2 */
    ,(BswU2)26U                                                                                                  /* [305] ComConf_ComSignal_D00908 */
    ,(BswU2)26U                                                                                                  /* [306] ComConf_ComSignal_D00909 */
    ,(BswU2)26U                                                                                                  /* [307] ComConf_ComSignal_D00910 */
    ,(BswU2)26U                                                                                                  /* [308] ComConf_ComSignal_D00911 */
    ,(BswU2)26U                                                                                                  /* [309] ComConf_ComSignal_D00912 */
    ,(BswU2)26U                                                                                                  /* [310] ComConf_ComSignal_D00913 */
    ,(BswU2)26U                                                                                                  /* [311] ComConf_ComSignal_D00914 */
    ,(BswU2)26U                                                                                                  /* [312] ComConf_ComSignal_D00915 */
    ,(BswU2)26U                                                                                                  /* [313] ComConf_ComSignal_D00916 */
    ,(BswU2)26U                                                                                                  /* [314] ComConf_ComSignal_D00917 */
    ,(BswU2)26U                                                                                                  /* [315] ComConf_ComSignal_AXSOC */
    ,(BswU2)26U                                                                                                  /* [316] ComConf_ComSignal_D00918 */
    ,(BswU2)26U                                                                                                  /* [317] ComConf_ComSignal_D00919 */
    ,(BswU2)26U                                                                                                  /* [318] ComConf_ComSignal_D00920 */
    ,(BswU2)26U                                                                                                  /* [319] ComConf_ComSignal_D00921 */
    ,(BswU2)26U                                                                                                  /* [320] ComConf_ComSignal_D00922 */
    ,(BswU2)26U                                                                                                  /* [321] ComConf_ComSignal_D00923 */
    ,(BswU2)26U                                                                                                  /* [322] ComConf_ComSignal_D00924 */
    ,(BswU2)26U                                                                                                  /* [323] ComConf_ComSignal_D00925 */
    ,(BswU2)26U                                                                                                  /* [324] ComConf_ComSignal_D00926 */
    ,(BswU2)26U                                                                                                  /* [325] ComConf_ComSignal_D00927 */
    ,(BswU2)26U                                                                                                  /* [326] ComConf_ComSignal_D00928 */
    ,(BswU2)26U                                                                                                  /* [327] ComConf_ComSignal_D00929 */
    ,(BswU2)26U                                                                                                  /* [328] ComConf_ComSignal_D00930 */
    ,(BswU2)26U                                                                                                  /* [329] ComConf_ComSignal_D00931 */
    ,(BswU2)26U                                                                                                  /* [330] ComConf_ComSignal_D00932 */
    ,(BswU2)26U                                                                                                  /* [331] ComConf_ComSignal_D00933 */
    ,(BswU2)26U                                                                                                  /* [332] ComConf_ComSignal_D00934 */
    ,(BswU2)26U                                                                                                  /* [333] ComConf_ComSignal_D00935 */
    ,(BswU2)26U                                                                                                  /* [334] ComConf_ComSignal_D00936 */
    ,(BswU2)26U                                                                                                  /* [335] ComConf_ComSignal_D00937 */
    ,(BswU2)26U                                                                                                  /* [336] ComConf_ComSignal_D00938 */
    ,(BswU2)26U                                                                                                  /* [337] ComConf_ComSignal_D00939 */
    ,(BswU2)26U                                                                                                  /* [338] ComConf_ComSignal_D00940 */
    ,(BswU2)26U                                                                                                  /* [339] ComConf_ComSignal_D00941 */
    ,(BswU2)26U                                                                                                  /* [340] ComConf_ComSignal_D00942 */
    ,(BswU2)26U                                                                                                  /* [341] ComConf_ComSignal_D00943 */
    ,(BswU2)26U                                                                                                  /* [342] ComConf_ComSignal_D00944 */
    ,(BswU2)26U                                                                                                  /* [343] ComConf_ComSignal_D00945 */
    ,(BswU2)26U                                                                                                  /* [344] ComConf_ComSignal_D00946 */
    ,(BswU2)26U                                                                                                  /* [345] ComConf_ComSignal_D00947 */
    ,(BswU2)26U                                                                                                  /* [346] ComConf_ComSignal_D00948 */
    ,(BswU2)26U                                                                                                  /* [347] ComConf_ComSignal_D00949 */
    ,(BswU2)26U                                                                                                  /* [348] ComConf_ComSignal_D00950 */
    ,(BswU2)26U                                                                                                  /* [349] ComConf_ComSignal_D00951 */
    ,(BswU2)26U                                                                                                  /* [350] ComConf_ComSignal_D00952 */
    ,(BswU2)26U                                                                                                  /* [351] ComConf_ComSignal_D00953 */
    ,(BswU2)26U                                                                                                  /* [352] ComConf_ComSignal_D00954 */
    ,(BswU2)26U                                                                                                  /* [353] ComConf_ComSignal_D00955 */
    ,(BswU2)26U                                                                                                  /* [354] ComConf_ComSignal_D00956 */
    ,(BswU2)27U                                                                                                  /* [355] ComConf_ComSignal_E_CRC1E3 */
    ,(BswU2)27U                                                                                                  /* [356] ComConf_ComSignal_E_CNT1E3 */
    ,(BswU2)27U                                                                                                  /* [357] ComConf_ComSignal_VPSINFO7 */
    ,(BswU2)27U                                                                                                  /* [358] ComConf_ComSignal_VPSINFO6 */
    ,(BswU2)27U                                                                                                  /* [359] ComConf_ComSignal_VPSINFO5 */
    ,(BswU2)27U                                                                                                  /* [360] ComConf_ComSignal_VPSINFO4 */
    ,(BswU2)27U                                                                                                  /* [361] ComConf_ComSignal_VPSINFO3 */
    ,(BswU2)27U                                                                                                  /* [362] ComConf_ComSignal_VPSINFO2 */
    ,(BswU2)27U                                                                                                  /* [363] ComConf_ComSignal_VPSINFO1 */
    ,(BswU2)27U                                                                                                  /* [364] ComConf_ComSignal_VPSINFOS */
    ,(BswU2)27U                                                                                                  /* [365] ComConf_ComSignal_D00976 */
    ,(BswU2)27U                                                                                                  /* [366] ComConf_ComSignal_VPSISOTA */
    ,(BswU2)27U                                                                                                  /* [367] ComConf_ComSignal_APOFRQ */
    ,(BswU2)27U                                                                                                  /* [368] ComConf_ComSignal_FV1E3_D */
    ,(BswU2)27U                                                                                                  /* [369] ComConf_ComSignal_KZK1E3_D */
    ,(BswU2)28U                                                                                                  /* [370] ComConf_ComSignal_ST1 */
    ,(BswU2)28U                                                                                                  /* [371] ComConf_ComSignal_ST1PER */
    ,(BswU2)28U                                                                                                  /* [372] ComConf_ComSignal_ST2 */
    ,(BswU2)28U                                                                                                  /* [373] ComConf_ComSignal_ST2PER */
    ,(BswU2)28U                                                                                                  /* [374] ComConf_ComSignal_ST3 */
    ,(BswU2)28U                                                                                                  /* [375] ComConf_ComSignal_ST3PER */
    ,(BswU2)28U                                                                                                  /* [376] ComConf_ComSignal_ST4 */
    ,(BswU2)28U                                                                                                  /* [377] ComConf_ComSignal_ST4PER */
    ,(BswU2)28U                                                                                                  /* [378] ComConf_ComSignal_ST5 */
    ,(BswU2)28U                                                                                                  /* [379] ComConf_ComSignal_ST5PER */
    ,(BswU2)28U                                                                                                  /* [380] ComConf_ComSignal_ST6 */
    ,(BswU2)28U                                                                                                  /* [381] ComConf_ComSignal_ST6PER */
    ,(BswU2)28U                                                                                                  /* [382] ComConf_ComSignal_ST7 */
    ,(BswU2)28U                                                                                                  /* [383] ComConf_ComSignal_ST7PER */
    ,(BswU2)28U                                                                                                  /* [384] ComConf_ComSignal_ST8 */
    ,(BswU2)28U                                                                                                  /* [385] ComConf_ComSignal_ST8PER */
    ,(BswU2)28U                                                                                                  /* [386] ComConf_ComSignal_ST9 */
    ,(BswU2)28U                                                                                                  /* [387] ComConf_ComSignal_ST9PER */
    ,(BswU2)28U                                                                                                  /* [388] ComConf_ComSignal_ST10 */
    ,(BswU2)28U                                                                                                  /* [389] ComConf_ComSignal_ST10PER */
    ,(BswU2)28U                                                                                                  /* [390] ComConf_ComSignal_ST11 */
    ,(BswU2)28U                                                                                                  /* [391] ComConf_ComSignal_ST11PER */
    ,(BswU2)28U                                                                                                  /* [392] ComConf_ComSignal_ST12 */
    ,(BswU2)28U                                                                                                  /* [393] ComConf_ComSignal_ST12PER */
    ,(BswU2)28U                                                                                                  /* [394] ComConf_ComSignal_ST13 */
    ,(BswU2)28U                                                                                                  /* [395] ComConf_ComSignal_ST13PER */
    ,(BswU2)28U                                                                                                  /* [396] ComConf_ComSignal_ST14 */
    ,(BswU2)28U                                                                                                  /* [397] ComConf_ComSignal_ST14PER */
    ,(BswU2)28U                                                                                                  /* [398] ComConf_ComSignal_ST15 */
    ,(BswU2)28U                                                                                                  /* [399] ComConf_ComSignal_ST15PER */
    ,(BswU2)28U                                                                                                  /* [400] ComConf_ComSignal_ST16 */
    ,(BswU2)28U                                                                                                  /* [401] ComConf_ComSignal_ST16PER */
    ,(BswU2)28U                                                                                                  /* [402] ComConf_ComSignal_ST17 */
    ,(BswU2)28U                                                                                                  /* [403] ComConf_ComSignal_ST17PER */
    ,(BswU2)28U                                                                                                  /* [404] ComConf_ComSignal_ST18 */
    ,(BswU2)28U                                                                                                  /* [405] ComConf_ComSignal_ST18PER */
    ,(BswU2)29U                                                                                                  /* [406] ComConf_ComSignal_D01286 */
    ,(BswU2)29U                                                                                                  /* [407] ComConf_ComSignal_D01287 */
    ,(BswU2)29U                                                                                                  /* [408] ComConf_ComSignal_D01288 */
    ,(BswU2)29U                                                                                                  /* [409] ComConf_ComSignal_D01289 */
    ,(BswU2)29U                                                                                                  /* [410] ComConf_ComSignal_D01290 */
    ,(BswU2)29U                                                                                                  /* [411] ComConf_ComSignal_D01291 */
    ,(BswU2)29U                                                                                                  /* [412] ComConf_ComSignal_D01292 */
    ,(BswU2)29U                                                                                                  /* [413] ComConf_ComSignal_D01293 */
    ,(BswU2)29U                                                                                                  /* [414] ComConf_ComSignal_D01294 */
    ,(BswU2)29U                                                                                                  /* [415] ComConf_ComSignal_ACPRE_AD */
    ,(BswU2)29U                                                                                                  /* [416] ComConf_ComSignal_EXPMIP */
    ,(BswU2)29U                                                                                                  /* [417] ComConf_ComSignal_D01295 */
    ,(BswU2)29U                                                                                                  /* [418] ComConf_ComSignal_AMR */
    ,(BswU2)29U                                                                                                  /* [419] ComConf_ComSignal_MIP */
    ,(BswU2)29U                                                                                                  /* [420] ComConf_ComSignal_D01296 */
    ,(BswU2)29U                                                                                                  /* [421] ComConf_ComSignal_D01297 */
    ,(BswU2)29U                                                                                                  /* [422] ComConf_ComSignal_D01298 */
    ,(BswU2)29U                                                                                                  /* [423] ComConf_ComSignal_D01299 */
    ,(BswU2)29U                                                                                                  /* [424] ComConf_ComSignal_D01300 */
    ,(BswU2)29U                                                                                                  /* [425] ComConf_ComSignal_D01301 */
    ,(BswU2)29U                                                                                                  /* [426] ComConf_ComSignal_D01302 */
    ,(BswU2)29U                                                                                                  /* [427] ComConf_ComSignal_D01303 */
    ,(BswU2)29U                                                                                                  /* [428] ComConf_ComSignal_D01304 */
    ,(BswU2)29U                                                                                                  /* [429] ComConf_ComSignal_D01305 */
    ,(BswU2)29U                                                                                                  /* [430] ComConf_ComSignal_D01306 */
    ,(BswU2)29U                                                                                                  /* [431] ComConf_ComSignal_D01307 */
    ,(BswU2)29U                                                                                                  /* [432] ComConf_ComSignal_D01308 */
    ,(BswU2)29U                                                                                                  /* [433] ComConf_ComSignal_D01309 */
    ,(BswU2)29U                                                                                                  /* [434] ComConf_ComSignal_D01310 */
    ,(BswU2)29U                                                                                                  /* [435] ComConf_ComSignal_D01311 */
    ,(BswU2)29U                                                                                                  /* [436] ComConf_ComSignal_D01312 */
    ,(BswU2)29U                                                                                                  /* [437] ComConf_ComSignal_D01313 */
    ,(BswU2)29U                                                                                                  /* [438] ComConf_ComSignal_D01314 */
    ,(BswU2)29U                                                                                                  /* [439] ComConf_ComSignal_D01315 */
    ,(BswU2)29U                                                                                                  /* [440] ComConf_ComSignal_D01316 */
    ,(BswU2)29U                                                                                                  /* [441] ComConf_ComSignal_FV37B_D */
    ,(BswU2)29U                                                                                                  /* [442] ComConf_ComSignal_KZK37B_D */
    ,(BswU2)30U                                                                                                  /* [443] ComConf_ComSignal_D01317 */
    ,(BswU2)30U                                                                                                  /* [444] ComConf_ComSignal_D01318 */
    ,(BswU2)30U                                                                                                  /* [445] ComConf_ComSignal_D01319 */
    ,(BswU2)30U                                                                                                  /* [446] ComConf_ComSignal_D01320 */
    ,(BswU2)30U                                                                                                  /* [447] ComConf_ComSignal_D01321 */
    ,(BswU2)30U                                                                                                  /* [448] ComConf_ComSignal_D01322 */
    ,(BswU2)30U                                                                                                  /* [449] ComConf_ComSignal_D01323 */
    ,(BswU2)30U                                                                                                  /* [450] ComConf_ComSignal_D01324 */
    ,(BswU2)30U                                                                                                  /* [451] ComConf_ComSignal_D01325 */
    ,(BswU2)30U                                                                                                  /* [452] ComConf_ComSignal_D01326 */
    ,(BswU2)30U                                                                                                  /* [453] ComConf_ComSignal_D01327 */
    ,(BswU2)30U                                                                                                  /* [454] ComConf_ComSignal_D01328 */
    ,(BswU2)30U                                                                                                  /* [455] ComConf_ComSignal_D01329 */
    ,(BswU2)30U                                                                                                  /* [456] ComConf_ComSignal_D01330 */
    ,(BswU2)30U                                                                                                  /* [457] ComConf_ComSignal_D01331 */
    ,(BswU2)30U                                                                                                  /* [458] ComConf_ComSignal_D01332 */
    ,(BswU2)30U                                                                                                  /* [459] ComConf_ComSignal_D01333 */
    ,(BswU2)30U                                                                                                  /* [460] ComConf_ComSignal_D01334 */
    ,(BswU2)30U                                                                                                  /* [461] ComConf_ComSignal_D01335 */
    ,(BswU2)30U                                                                                                  /* [462] ComConf_ComSignal_HVH_ATPW */
    ,(BswU2)30U                                                                                                  /* [463] ComConf_ComSignal_D01336 */
    ,(BswU2)30U                                                                                                  /* [464] ComConf_ComSignal_D01337 */
    ,(BswU2)30U                                                                                                  /* [465] ComConf_ComSignal_D01338 */
    ,(BswU2)30U                                                                                                  /* [466] ComConf_ComSignal_D01339 */
    ,(BswU2)30U                                                                                                  /* [467] ComConf_ComSignal_D01340 */
    ,(BswU2)30U                                                                                                  /* [468] ComConf_ComSignal_D01341 */
    ,(BswU2)30U                                                                                                  /* [469] ComConf_ComSignal_D01342 */
    ,(BswU2)30U                                                                                                  /* [470] ComConf_ComSignal_D01343 */
    ,(BswU2)30U                                                                                                  /* [471] ComConf_ComSignal_D01344 */
    ,(BswU2)30U                                                                                                  /* [472] ComConf_ComSignal_D01345 */
    ,(BswU2)30U                                                                                                  /* [473] ComConf_ComSignal_D01346 */
    ,(BswU2)30U                                                                                                  /* [474] ComConf_ComSignal_D01347 */
    ,(BswU2)30U                                                                                                  /* [475] ComConf_ComSignal_D01348 */
    ,(BswU2)30U                                                                                                  /* [476] ComConf_ComSignal_D01349 */
    ,(BswU2)30U                                                                                                  /* [477] ComConf_ComSignal_D01350 */
    ,(BswU2)30U                                                                                                  /* [478] ComConf_ComSignal_D01351 */
    ,(BswU2)30U                                                                                                  /* [479] ComConf_ComSignal_D01352 */
    ,(BswU2)31U                                                                                                  /* [480] ComConf_ComSignal_D01361 */
    ,(BswU2)31U                                                                                                  /* [481] ComConf_ComSignal_D01362 */
    ,(BswU2)31U                                                                                                  /* [482] ComConf_ComSignal_D01363 */
    ,(BswU2)31U                                                                                                  /* [483] ComConf_ComSignal_D01364 */
    ,(BswU2)31U                                                                                                  /* [484] ComConf_ComSignal_COMPRP_A */
    ,(BswU2)31U                                                                                                  /* [485] ComConf_ComSignal_D01365 */
    ,(BswU2)31U                                                                                                  /* [486] ComConf_ComSignal_ACMODE_P */
    ,(BswU2)31U                                                                                                  /* [487] ComConf_ComSignal_D01366 */
    ,(BswU2)32U                                                                                                  /* [488] ComConf_ComSignal_HED_S */
    ,(BswU2)32U                                                                                                  /* [489] ComConf_ComSignal_TAL_S */
    ,(BswU2)32U                                                                                                  /* [490] ComConf_ComSignal_DRL_S */
    ,(BswU2)32U                                                                                                  /* [491] ComConf_ComSignal_AUT_S */
    ,(BswU2)32U                                                                                                  /* [492] ComConf_ComSignal_OFF_S */
    ,(BswU2)32U                                                                                                  /* [493] ComConf_ComSignal_AHB_S */
    ,(BswU2)32U                                                                                                  /* [494] ComConf_ComSignal_PAS_S */
    ,(BswU2)32U                                                                                                  /* [495] ComConf_ComSignal_HIB_S */
    ,(BswU2)32U                                                                                                  /* [496] ComConf_ComSignal_BW_S */
    ,(BswU2)32U                                                                                                  /* [497] ComConf_ComSignal_RFG_S */
    ,(BswU2)32U                                                                                                  /* [498] ComConf_ComSignal_FOG_S */
    ,(BswU2)32U                                                                                                  /* [499] ComConf_ComSignal_CRGL_S */
    ,(BswU2)32U                                                                                                  /* [500] ComConf_ComSignal_CRGR_S */
    ,(BswU2)32U                                                                                                  /* [501] ComConf_ComSignal_TRNL_S */
    ,(BswU2)32U                                                                                                  /* [502] ComConf_ComSignal_TRNR_S */
    ,(BswU2)32U                                                                                                  /* [503] ComConf_ComSignal_CXP_TERR */
    ,(BswU2)32U                                                                                                  /* [504] ComConf_ComSignal_CXP_JDGT */
    ,(BswU2)33U                                                                                                  /* [505] ComConf_ComSignal_WVR_S */
    ,(BswU2)33U                                                                                                  /* [506] ComConf_ComSignal_WSW_S */
    ,(BswU2)33U                                                                                                  /* [507] ComConf_ComSignal_WRSW_S */
    ,(BswU2)33U                                                                                                  /* [508] ComConf_ComSignal_WRON_S */
    ,(BswU2)33U                                                                                                  /* [509] ComConf_ComSignal_WRIN_S */
    ,(BswU2)33U                                                                                                  /* [510] ComConf_ComSignal_WINT_S */
    ,(BswU2)33U                                                                                                  /* [511] ComConf_ComSignal_WMST_S */
    ,(BswU2)33U                                                                                                  /* [512] ComConf_ComSignal_WA_S */
    ,(BswU2)33U                                                                                                  /* [513] ComConf_ComSignal_WHI_S */
    ,(BswU2)33U                                                                                                  /* [514] ComConf_ComSignal_WLO_S */
    ,(BswU2)33U                                                                                                  /* [515] ComConf_ComSignal_WOFF_S */
    ,(BswU2)33U                                                                                                  /* [516] ComConf_ComSignal_WAI_S */
    ,(BswU2)33U                                                                                                  /* [517] ComConf_ComSignal_CXP_WERR */
    ,(BswU2)33U                                                                                                  /* [518] ComConf_ComSignal_CXP_JDGW */
    ,(BswU2)34U                                                                                                  /* [519] ComConf_ComSignal_D02498 */
    ,(BswU2)34U                                                                                                  /* [520] ComConf_ComSignal_ETHWU_32 */
    ,(BswU2)35U                                                                                                  /* [521] ComConf_ComSignal_THR_GLOB */
    ,(BswU2)35U                                                                                                  /* [522] ComConf_ComSignal_TMO_GLOB */
    ,(BswU2)35U                                                                                                  /* [523] ComConf_ComSignal_TTA_GLOB */
    ,(BswU2)35U                                                                                                  /* [524] ComConf_ComSignal_RTA_GLOB */
    ,(BswU2)36U                                                                                                  /* [525] ComConf_ComSignal_TR_GLOB */
    ,(BswU2)36U                                                                                                  /* [526] ComConf_ComSignal_TM_GLOB */
    ,(BswU2)36U                                                                                                  /* [527] ComConf_ComSignal_NR_GLOB */
    ,(BswU2)36U                                                                                                  /* [528] ComConf_ComSignal_NM_GLOB */
    ,(BswU2)37U                                                                                                  /* [529] ComConf_ComSignal_D02649 */
    ,(BswU2)37U                                                                                                  /* [530] ComConf_ComSignal_NMRBR_MD */
    ,(BswU2)37U                                                                                                  /* [531] ComConf_ComSignal_BHSWEXT */
    ,(BswU2)37U                                                                                                  /* [532] ComConf_ComSignal_D02650 */
    ,(BswU2)37U                                                                                                  /* [533] ComConf_ComSignal_D02651 */
    ,(BswU2)38U                                                                                                  /* [534] ComConf_ComSignal_GRLGDBCR */
    ,(BswU2)38U                                                                                                  /* [535] ComConf_ComSignal_DMCNVINF */
    ,(BswU2)38U                                                                                                  /* [536] ComConf_ComSignal_CNV_MODE */
    ,(BswU2)38U                                                                                                  /* [537] ComConf_ComSignal_DMCNVVLD */
    ,(BswU2)39U                                                                                                  /* [538] ComConf_ComSignal_TEC */
    ,(BswU2)39U                                                                                                  /* [539] ComConf_ComSignal_DRVEC */
    ,(BswU2)39U                                                                                                  /* [540] ComConf_ComSignal_ALTEC */
    ,(BswU2)39U                                                                                                  /* [541] ComConf_ComSignal_ACEC */
    ,(BswU2)39U                                                                                                  /* [542] ComConf_ComSignal_BPEC */
    ,(BswU2)39U                                                                                                  /* [543] ComConf_ComSignal_DAEC */
    ,(BswU2)39U                                                                                                  /* [544] ComConf_ComSignal_CAEC */
    ,(BswU2)39U                                                                                                  /* [545] ComConf_ComSignal_CUMTEC */
    ,(BswU2)39U                                                                                                  /* [546] ComConf_ComSignal_CUMDRVEC */
    ,(BswU2)39U                                                                                                  /* [547] ComConf_ComSignal_CUMALTEC */
    ,(BswU2)39U                                                                                                  /* [548] ComConf_ComSignal_CUMACEC */
    ,(BswU2)40U                                                                                                  /* [549] ComConf_ComSignal_CUMBPEC */
    ,(BswU2)40U                                                                                                  /* [550] ComConf_ComSignal_CUMDAEC */
    ,(BswU2)40U                                                                                                  /* [551] ComConf_ComSignal_CUMCAEC */
    ,(BswU2)40U                                                                                                  /* [552] ComConf_ComSignal_RBSCC_E */
    ,(BswU2)40U                                                                                                  /* [553] ComConf_ComSignal_RBSCC_F */
    ,(BswU2)40U                                                                                                  /* [554] ComConf_ComSignal_RBSCC_G */
    ,(BswU2)40U                                                                                                  /* [555] ComConf_ComSignal_RBSCC_H */
    ,(BswU2)40U                                                                                                  /* [556] ComConf_ComSignal_CHGCAL1 */
    ,(BswU2)40U                                                                                                  /* [557] ComConf_ComSignal_CHGCAL2 */
    ,(BswU2)40U                                                                                                  /* [558] ComConf_ComSignal_FSWRP */
    ,(BswU2)40U                                                                                                  /* [559] ComConf_ComSignal_U1TOCDC1 */
    ,(BswU2)40U                                                                                                  /* [560] ComConf_ComSignal_U1TOCDC2 */
    ,(BswU2)40U                                                                                                  /* [561] ComConf_ComSignal_U1TOCDC3 */
    ,(BswU2)40U                                                                                                  /* [562] ComConf_ComSignal_S2TOCDC1 */
    ,(BswU2)40U                                                                                                  /* [563] ComConf_ComSignal_S2TOCDC2 */
    ,(BswU2)40U                                                                                                  /* [564] ComConf_ComSignal_S2TOCDC3 */
    ,(BswU2)41U                                                                                                  /* [565] ComConf_ComSignal_RSISDKME */
    ,(BswU2)41U                                                                                                  /* [566] ComConf_ComSignal_RSISIDDK */
    ,(BswU2)41U                                                                                                  /* [567] ComConf_ComSignal_D03957 */
    ,(BswU2)41U                                                                                                  /* [568] ComConf_ComSignal_D03958 */
    ,(BswU2)42U                                                                                                  /* [569] ComConf_ComSignal_D04012 */
    ,(BswU2)42U                                                                                                  /* [570] ComConf_ComSignal_DESMUTE */
    ,(BswU2)43U                                                                                                  /* [571] ComConf_ComSignal_DREBUID */
    ,(BswU2)43U                                                                                                  /* [572] ComConf_ComSignal_DREBU02 */
    ,(BswU2)43U                                                                                                  /* [573] ComConf_ComSignal_DREBU03 */
    ,(BswU2)43U                                                                                                  /* [574] ComConf_ComSignal_DREBU04 */
    ,(BswU2)43U                                                                                                  /* [575] ComConf_ComSignal_DREBU05 */
    ,(BswU2)43U                                                                                                  /* [576] ComConf_ComSignal_DREBU06 */
    ,(BswU2)43U                                                                                                  /* [577] ComConf_ComSignal_DREBU07 */
    ,(BswU2)43U                                                                                                  /* [578] ComConf_ComSignal_DREBU08 */
    ,(BswU2)43U                                                                                                  /* [579] ComConf_ComSignal_DREBU11 */
    ,(BswU2)43U                                                                                                  /* [580] ComConf_ComSignal_DREBU12 */
    ,(BswU2)43U                                                                                                  /* [581] ComConf_ComSignal_DREBU13 */
    ,(BswU2)43U                                                                                                  /* [582] ComConf_ComSignal_DREBU14 */
    ,(BswU2)43U                                                                                                  /* [583] ComConf_ComSignal_DREBU15 */
    ,(BswU2)43U                                                                                                  /* [584] ComConf_ComSignal_DREBU16 */
    ,(BswU2)43U                                                                                                  /* [585] ComConf_ComSignal_DREBU17 */
    ,(BswU2)43U                                                                                                  /* [586] ComConf_ComSignal_DREBU18 */
    ,(BswU2)43U                                                                                                  /* [587] ComConf_ComSignal_DREBU21 */
    ,(BswU2)43U                                                                                                  /* [588] ComConf_ComSignal_DREBU22 */
    ,(BswU2)43U                                                                                                  /* [589] ComConf_ComSignal_DREBU23 */
    ,(BswU2)43U                                                                                                  /* [590] ComConf_ComSignal_DREBU24 */
    ,(BswU2)43U                                                                                                  /* [591] ComConf_ComSignal_DREBU25 */
    ,(BswU2)43U                                                                                                  /* [592] ComConf_ComSignal_DREBU26 */
    ,(BswU2)43U                                                                                                  /* [593] ComConf_ComSignal_DREBU27 */
    ,(BswU2)43U                                                                                                  /* [594] ComConf_ComSignal_DREBU28 */
    ,(BswU2)43U                                                                                                  /* [595] ComConf_ComSignal_DREBU31 */
    ,(BswU2)43U                                                                                                  /* [596] ComConf_ComSignal_DREBU32 */
    ,(BswU2)43U                                                                                                  /* [597] ComConf_ComSignal_DREBU33 */
    ,(BswU2)43U                                                                                                  /* [598] ComConf_ComSignal_DREBU34 */
    ,(BswU2)43U                                                                                                  /* [599] ComConf_ComSignal_DREBU35 */
    ,(BswU2)43U                                                                                                  /* [600] ComConf_ComSignal_DREBU36 */
    ,(BswU2)43U                                                                                                  /* [601] ComConf_ComSignal_DREBU37 */
    ,(BswU2)43U                                                                                                  /* [602] ComConf_ComSignal_DREBU38 */
    ,(BswU2)44U                                                                                                  /* [603] ComConf_ComSignal_DRDYSTS */
    ,(BswU2)44U                                                                                                  /* [604] ComConf_ComSignal_DRDYB */
    ,(BswU2)45U                                                                                                  /* [605] ComConf_ComSignal_D04218 */
    ,(BswU2)45U                                                                                                  /* [606] ComConf_ComSignal_STRGCM */
    ,(BswU2)45U                                                                                                  /* [607] ComConf_ComSignal_D04219 */
    ,(BswU2)45U                                                                                                  /* [608] ComConf_ComSignal_D04220 */
    ,(BswU2)45U                                                                                                  /* [609] ComConf_ComSignal_D04221 */
    ,(BswU2)45U                                                                                                  /* [610] ComConf_ComSignal_D04222 */
    ,(BswU2)45U                                                                                                  /* [611] ComConf_ComSignal_D04223 */
    ,(BswU2)45U                                                                                                  /* [612] ComConf_ComSignal_D04224 */
    ,(BswU2)45U                                                                                                  /* [613] ComConf_ComSignal_D04225 */
    ,(BswU2)45U                                                                                                  /* [614] ComConf_ComSignal_D04226 */
    ,(BswU2)46U                                                                                                  /* [615] ComConf_ComSignal_HV_SRGMD */
    ,(BswU2)46U                                                                                                  /* [616] ComConf_ComSignal_D04276 */
    ,(BswU2)46U                                                                                                  /* [617] ComConf_ComSignal_D04277 */
    ,(BswU2)46U                                                                                                  /* [618] ComConf_ComSignal_TQRR */
    ,(BswU2)46U                                                                                                  /* [619] ComConf_ComSignal_D04278 */
    ,(BswU2)46U                                                                                                  /* [620] ComConf_ComSignal_TQFR */
    ,(BswU2)46U                                                                                                  /* [621] ComConf_ComSignal_D04279 */
    ,(BswU2)46U                                                                                                  /* [622] ComConf_ComSignal_D04280 */
    ,(BswU2)47U                                                                                                  /* [623] ComConf_ComSignal_FCRF */
    ,(BswU2)47U                                                                                                  /* [624] ComConf_ComSignal_CLE_SOCF */
    ,(BswU2)47U                                                                                                  /* [625] ComConf_ComSignal_D04334 */
    ,(BswU2)47U                                                                                                  /* [626] ComConf_ComSignal_D04335 */
    ,(BswU2)48U                                                                                                  /* [627] ComConf_ComSignal_E_CRC075 */
    ,(BswU2)48U                                                                                                  /* [628] ComConf_ComSignal_E_CNT075 */
    ,(BswU2)48U                                                                                                  /* [629] ComConf_ComSignal_D04374 */
    ,(BswU2)48U                                                                                                  /* [630] ComConf_ComSignal_SDRVRR */
    ,(BswU2)48U                                                                                                  /* [631] ComConf_ComSignal_D04375 */
    ,(BswU2)48U                                                                                                  /* [632] ComConf_ComSignal_D04376 */
    ,(BswU2)48U                                                                                                  /* [633] ComConf_ComSignal_SDRVFR */
    ,(BswU2)48U                                                                                                  /* [634] ComConf_ComSignal_D04377 */
    ,(BswU2)48U                                                                                                  /* [635] ComConf_ComSignal_D04378 */
    ,(BswU2)48U                                                                                                  /* [636] ComConf_ComSignal_D04379 */
    ,(BswU2)49U                                                                                                  /* [637] ComConf_ComSignal_E_CRC0A1 */
    ,(BswU2)49U                                                                                                  /* [638] ComConf_ComSignal_E_CNT0A1 */
    ,(BswU2)49U                                                                                                  /* [639] ComConf_ComSignal_D04380 */
    ,(BswU2)49U                                                                                                  /* [640] ComConf_ComSignal_D04381 */
    ,(BswU2)49U                                                                                                  /* [641] ComConf_ComSignal_HVMRADRR */
    ,(BswU2)49U                                                                                                  /* [642] ComConf_ComSignal_HVMRADFR */
    ,(BswU2)50U                                                                                                  /* [643] ComConf_ComSignal_D04568 */
    ,(BswU2)50U                                                                                                  /* [644] ComConf_ComSignal_DREIMABN */
    ,(BswU2)51U                                                                                                  /* [645] ComConf_ComSignal_I_BAT_BD */
    ,(BswU2)51U                                                                                                  /* [646] ComConf_ComSignal_U_BAT_BD */
    ,(BswU2)51U                                                                                                  /* [647] ComConf_ComSignal_PWDTY_BD */
    ,(BswU2)51U                                                                                                  /* [648] ComConf_ComSignal_VLO_BD */
    ,(BswU2)51U                                                                                                  /* [649] ComConf_ComSignal_PWIF1_BD */
    ,(BswU2)52U                                                                                                  /* [650] ComConf_ComSignal_T_BAT_BD */
    ,(BswU2)52U                                                                                                  /* [651] ComConf_ComSignal_PWIF2_BD */
    ,(BswU2)52U                                                                                                  /* [652] ComConf_ComSignal_SOCS_BD */
    ,(BswU2)52U                                                                                                  /* [653] ComConf_ComSignal_SOC_BD */
    ,(BswU2)52U                                                                                                  /* [654] ComConf_ComSignal_PWIF3_BD */
    ,(BswU2)52U                                                                                                  /* [655] ComConf_ComSignal_PWIF4_BD */
    ,(BswU2)52U                                                                                                  /* [656] ComConf_ComSignal_PWIF5_BD */
    ,(BswU2)53U                                                                                                  /* [657] ComConf_ComSignal_DRENG11 */
    ,(BswU2)53U                                                                                                  /* [658] ComConf_ComSignal_DRENG12 */
    ,(BswU2)53U                                                                                                  /* [659] ComConf_ComSignal_DRENG13 */
    ,(BswU2)53U                                                                                                  /* [660] ComConf_ComSignal_DRENG14 */
    ,(BswU2)53U                                                                                                  /* [661] ComConf_ComSignal_DRENG15 */
    ,(BswU2)53U                                                                                                  /* [662] ComConf_ComSignal_DRENG16 */
    ,(BswU2)53U                                                                                                  /* [663] ComConf_ComSignal_DRENG17 */
    ,(BswU2)53U                                                                                                  /* [664] ComConf_ComSignal_DRENG18 */
    ,(BswU2)54U                                                                                                  /* [665] ComConf_ComSignal_DRENG21 */
    ,(BswU2)54U                                                                                                  /* [666] ComConf_ComSignal_DRENG22 */
    ,(BswU2)54U                                                                                                  /* [667] ComConf_ComSignal_DRENG23 */
    ,(BswU2)54U                                                                                                  /* [668] ComConf_ComSignal_DRENG24 */
    ,(BswU2)54U                                                                                                  /* [669] ComConf_ComSignal_DRENG25 */
    ,(BswU2)54U                                                                                                  /* [670] ComConf_ComSignal_DRENG26 */
    ,(BswU2)54U                                                                                                  /* [671] ComConf_ComSignal_DRENG27 */
    ,(BswU2)54U                                                                                                  /* [672] ComConf_ComSignal_DRENG28 */
    ,(BswU2)55U                                                                                                  /* [673] ComConf_ComSignal_DRENG31 */
    ,(BswU2)55U                                                                                                  /* [674] ComConf_ComSignal_DRENG32 */
    ,(BswU2)55U                                                                                                  /* [675] ComConf_ComSignal_DRENG33 */
    ,(BswU2)55U                                                                                                  /* [676] ComConf_ComSignal_DRENG34 */
    ,(BswU2)55U                                                                                                  /* [677] ComConf_ComSignal_DRENG35 */
    ,(BswU2)55U                                                                                                  /* [678] ComConf_ComSignal_DRENG36 */
    ,(BswU2)55U                                                                                                  /* [679] ComConf_ComSignal_DRENG37 */
    ,(BswU2)55U                                                                                                  /* [680] ComConf_ComSignal_DRENG38 */
    ,(BswU2)56U                                                                                                  /* [681] ComConf_ComSignal_DRENG51 */
    ,(BswU2)56U                                                                                                  /* [682] ComConf_ComSignal_DRENG52 */
    ,(BswU2)56U                                                                                                  /* [683] ComConf_ComSignal_DRENG53 */
    ,(BswU2)56U                                                                                                  /* [684] ComConf_ComSignal_DRENG54 */
    ,(BswU2)56U                                                                                                  /* [685] ComConf_ComSignal_DRENG55 */
    ,(BswU2)56U                                                                                                  /* [686] ComConf_ComSignal_DRENG56 */
    ,(BswU2)56U                                                                                                  /* [687] ComConf_ComSignal_DRENG57 */
    ,(BswU2)56U                                                                                                  /* [688] ComConf_ComSignal_DRENG58 */
    ,(BswU2)57U                                                                                                  /* [689] ComConf_ComSignal_DRENG61 */
    ,(BswU2)57U                                                                                                  /* [690] ComConf_ComSignal_DRENG62 */
    ,(BswU2)57U                                                                                                  /* [691] ComConf_ComSignal_DRENG63 */
    ,(BswU2)57U                                                                                                  /* [692] ComConf_ComSignal_DRENG64 */
    ,(BswU2)57U                                                                                                  /* [693] ComConf_ComSignal_DRENG65 */
    ,(BswU2)57U                                                                                                  /* [694] ComConf_ComSignal_DRENG66 */
    ,(BswU2)57U                                                                                                  /* [695] ComConf_ComSignal_DRENG67 */
    ,(BswU2)57U                                                                                                  /* [696] ComConf_ComSignal_DRENG68 */
    ,(BswU2)58U                                                                                                  /* [697] ComConf_ComSignal_DRENG91 */
    ,(BswU2)58U                                                                                                  /* [698] ComConf_ComSignal_DRENG92 */
    ,(BswU2)58U                                                                                                  /* [699] ComConf_ComSignal_DRENG93 */
    ,(BswU2)58U                                                                                                  /* [700] ComConf_ComSignal_DRENG94 */
    ,(BswU2)58U                                                                                                  /* [701] ComConf_ComSignal_DRENG95 */
    ,(BswU2)58U                                                                                                  /* [702] ComConf_ComSignal_DRENG96 */
    ,(BswU2)58U                                                                                                  /* [703] ComConf_ComSignal_DRENG97 */
    ,(BswU2)58U                                                                                                  /* [704] ComConf_ComSignal_DRENG98 */
    ,(BswU2)59U                                                                                                  /* [705] ComConf_ComSignal_DRENG101 */
    ,(BswU2)59U                                                                                                  /* [706] ComConf_ComSignal_DRENG102 */
    ,(BswU2)59U                                                                                                  /* [707] ComConf_ComSignal_DRENG103 */
    ,(BswU2)59U                                                                                                  /* [708] ComConf_ComSignal_DRENG104 */
    ,(BswU2)59U                                                                                                  /* [709] ComConf_ComSignal_DRENG105 */
    ,(BswU2)59U                                                                                                  /* [710] ComConf_ComSignal_DRENG106 */
    ,(BswU2)59U                                                                                                  /* [711] ComConf_ComSignal_DRENG107 */
    ,(BswU2)59U                                                                                                  /* [712] ComConf_ComSignal_DRENG108 */
    ,(BswU2)60U                                                                                                  /* [713] ComConf_ComSignal_VIN_1 */
    ,(BswU2)60U                                                                                                  /* [714] ComConf_ComSignal_VIN_2 */
    ,(BswU2)60U                                                                                                  /* [715] ComConf_ComSignal_VIN_3 */
    ,(BswU2)60U                                                                                                  /* [716] ComConf_ComSignal_VIN_4 */
    ,(BswU2)60U                                                                                                  /* [717] ComConf_ComSignal_VIN_5 */
    ,(BswU2)60U                                                                                                  /* [718] ComConf_ComSignal_VIN_6 */
    ,(BswU2)60U                                                                                                  /* [719] ComConf_ComSignal_VIN_7 */
    ,(BswU2)60U                                                                                                  /* [720] ComConf_ComSignal_VIN_8 */
    ,(BswU2)60U                                                                                                  /* [721] ComConf_ComSignal_VIN_9 */
    ,(BswU2)60U                                                                                                  /* [722] ComConf_ComSignal_VIN_10 */
    ,(BswU2)60U                                                                                                  /* [723] ComConf_ComSignal_VIN_11 */
    ,(BswU2)60U                                                                                                  /* [724] ComConf_ComSignal_VIN_12 */
    ,(BswU2)60U                                                                                                  /* [725] ComConf_ComSignal_VIN_13 */
    ,(BswU2)60U                                                                                                  /* [726] ComConf_ComSignal_VIN_14 */
    ,(BswU2)60U                                                                                                  /* [727] ComConf_ComSignal_VIN_15 */
    ,(BswU2)60U                                                                                                  /* [728] ComConf_ComSignal_VIN_16 */
    ,(BswU2)60U                                                                                                  /* [729] ComConf_ComSignal_VIN_17 */
    ,(BswU2)60U                                                                                                  /* [730] ComConf_ComSignal_D04580 */
    ,(BswU2)60U                                                                                                  /* [731] ComConf_ComSignal_D04581 */
    ,(BswU2)61U                                                                                                  /* [732] ComConf_ComSignal_DREPS01 */
    ,(BswU2)61U                                                                                                  /* [733] ComConf_ComSignal_DREPS02 */
    ,(BswU2)61U                                                                                                  /* [734] ComConf_ComSignal_DREPS03 */
    ,(BswU2)61U                                                                                                  /* [735] ComConf_ComSignal_DREPS04 */
    ,(BswU2)61U                                                                                                  /* [736] ComConf_ComSignal_DREPS05 */
    ,(BswU2)61U                                                                                                  /* [737] ComConf_ComSignal_DREPS06 */
    ,(BswU2)61U                                                                                                  /* [738] ComConf_ComSignal_DREPS07 */
    ,(BswU2)61U                                                                                                  /* [739] ComConf_ComSignal_DREPS08 */
    ,(BswU2)62U                                                                                                  /* [740] ComConf_ComSignal_V_DIST */
    ,(BswU2)62U                                                                                                  /* [741] ComConf_ComSignal_V_RELV */
    ,(BswU2)62U                                                                                                  /* [742] ComConf_ComSignal_V_SWOP */
    ,(BswU2)62U                                                                                                  /* [743] ComConf_ComSignal_USMREQG */
    ,(BswU2)62U                                                                                                  /* [744] ComConf_ComSignal_RCURVR */
    ,(BswU2)62U                                                                                                  /* [745] ComConf_ComSignal_USMDSTTS */
    ,(BswU2)62U                                                                                                  /* [746] ComConf_ComSignal_COFFSET */
    ,(BswU2)62U                                                                                                  /* [747] ComConf_ComSignal_USMDSTSL */
    ,(BswU2)62U                                                                                                  /* [748] ComConf_ComSignal_RSACAUF */
    ,(BswU2)63U                                                                                                  /* [749] ComConf_ComSignal_OTHVW */
    ,(BswU2)63U                                                                                                  /* [750] ComConf_ComSignal_OTHVH */
    ,(BswU2)63U                                                                                                  /* [751] ComConf_ComSignal_OTHPB */
    ,(BswU2)63U                                                                                                  /* [752] ComConf_ComSignal_OTHTTC */
    ,(BswU2)63U                                                                                                  /* [753] ComConf_ComSignal_OTHTTYP */
    ,(BswU2)63U                                                                                                  /* [754] ComConf_ComSignal_D04634 */
    ,(BswU2)63U                                                                                                  /* [755] ComConf_ComSignal_D04635 */
    ,(BswU2)63U                                                                                                  /* [756] ComConf_ComSignal_D04636 */
    ,(BswU2)63U                                                                                                  /* [757] ComConf_ComSignal_HITPOS */
    ,(BswU2)63U                                                                                                  /* [758] ComConf_ComSignal_OTHRDANG */
    ,(BswU2)63U                                                                                                  /* [759] ComConf_ComSignal_D04637 */
    ,(BswU2)63U                                                                                                  /* [760] ComConf_ComSignal_D04638 */
    ,(BswU2)63U                                                                                                  /* [761] ComConf_ComSignal_D04639 */
    ,(BswU2)63U                                                                                                  /* [762] ComConf_ComSignal_D04640 */
    ,(BswU2)63U                                                                                                  /* [763] ComConf_ComSignal_D04641 */
    ,(BswU2)63U                                                                                                  /* [764] ComConf_ComSignal_D04642 */
    ,(BswU2)63U                                                                                                  /* [765] ComConf_ComSignal_D04643 */
    ,(BswU2)63U                                                                                                  /* [766] ComConf_ComSignal_D04644 */
    ,(BswU2)63U                                                                                                  /* [767] ComConf_ComSignal_D04645 */
    ,(BswU2)63U                                                                                                  /* [768] ComConf_ComSignal_D04646 */
    ,(BswU2)63U                                                                                                  /* [769] ComConf_ComSignal_OTHOVLPC */
    ,(BswU2)63U                                                                                                  /* [770] ComConf_ComSignal_OTHRVPC */
    ,(BswU2)64U                                                                                                  /* [771] ComConf_ComSignal_OTHFALD */
    ,(BswU2)64U                                                                                                  /* [772] ComConf_ComSignal_OTHCOND */
    ,(BswU2)64U                                                                                                  /* [773] ComConf_ComSignal_OTHLDIS */
    ,(BswU2)64U                                                                                                  /* [774] ComConf_ComSignal_OTHFALF */
    ,(BswU2)64U                                                                                                  /* [775] ComConf_ComSignal_OTHCONF */
    ,(BswU2)64U                                                                                                  /* [776] ComConf_ComSignal_OTHLANE */
    ,(BswU2)65U                                                                                                  /* [777] ComConf_ComSignal_OTHSOR */
    ,(BswU2)65U                                                                                                  /* [778] ComConf_ComSignal_OTHROR */
    ,(BswU2)65U                                                                                                  /* [779] ComConf_ComSignal_OTHLX */
    ,(BswU2)65U                                                                                                  /* [780] ComConf_ComSignal_OTHSOLAR */
    ,(BswU2)65U                                                                                                  /* [781] ComConf_ComSignal_D04663 */
    ,(BswU2)65U                                                                                                  /* [782] ComConf_ComSignal_D04664 */
    ,(BswU2)66U                                                                                                  /* [783] ComConf_ComSignal_D04665 */
    ,(BswU2)66U                                                                                                  /* [784] ComConf_ComSignal_D04666 */
    ,(BswU2)66U                                                                                                  /* [785] ComConf_ComSignal_D04667 */
    ,(BswU2)66U                                                                                                  /* [786] ComConf_ComSignal_D04668 */
    ,(BswU2)66U                                                                                                  /* [787] ComConf_ComSignal_XREQFPB */
    ,(BswU2)66U                                                                                                  /* [788] ComConf_ComSignal_XREQPB */
    ,(BswU2)66U                                                                                                  /* [789] ComConf_ComSignal_D04669 */
    ,(BswU2)66U                                                                                                  /* [790] ComConf_ComSignal_D04670 */
    ,(BswU2)66U                                                                                                  /* [791] ComConf_ComSignal_XREQPBH */
    ,(BswU2)66U                                                                                                  /* [792] ComConf_ComSignal_D04671 */
    ,(BswU2)66U                                                                                                  /* [793] ComConf_ComSignal_D04672 */
    ,(BswU2)66U                                                                                                  /* [794] ComConf_ComSignal_D04673 */
    ,(BswU2)66U                                                                                                  /* [795] ComConf_ComSignal_D04674 */
    ,(BswU2)66U                                                                                                  /* [796] ComConf_ComSignal_D04675 */
    ,(BswU2)66U                                                                                                  /* [797] ComConf_ComSignal_D04676 */
    ,(BswU2)66U                                                                                                  /* [798] ComConf_ComSignal_D04677 */
    ,(BswU2)66U                                                                                                  /* [799] ComConf_ComSignal_D04678 */
    ,(BswU2)66U                                                                                                  /* [800] ComConf_ComSignal_D04679 */
    ,(BswU2)66U                                                                                                  /* [801] ComConf_ComSignal_D04680 */
    ,(BswU2)66U                                                                                                  /* [802] ComConf_ComSignal_D04681 */
    ,(BswU2)66U                                                                                                  /* [803] ComConf_ComSignal_D04682 */
    ,(BswU2)66U                                                                                                  /* [804] ComConf_ComSignal_D04683 */
    ,(BswU2)66U                                                                                                  /* [805] ComConf_ComSignal_D04684 */
    ,(BswU2)66U                                                                                                  /* [806] ComConf_ComSignal_D04685 */
    ,(BswU2)67U                                                                                                  /* [807] ComConf_ComSignal_AVSTRGR */
    ,(BswU2)67U                                                                                                  /* [808] ComConf_ComSignal_PBATRGR */
    ,(BswU2)67U                                                                                                  /* [809] ComConf_ComSignal_D04686 */
    ,(BswU2)67U                                                                                                  /* [810] ComConf_ComSignal_D04687 */
    ,(BswU2)67U                                                                                                  /* [811] ComConf_ComSignal_PCSALM */
    ,(BswU2)67U                                                                                                  /* [812] ComConf_ComSignal_D04688 */
    ,(BswU2)67U                                                                                                  /* [813] ComConf_ComSignal_D04689 */
    ,(BswU2)67U                                                                                                  /* [814] ComConf_ComSignal_D04690 */
    ,(BswU2)67U                                                                                                  /* [815] ComConf_ComSignal_D04691 */
    ,(BswU2)67U                                                                                                  /* [816] ComConf_ComSignal_D04692 */
    ,(BswU2)67U                                                                                                  /* [817] ComConf_ComSignal_D04693 */
    ,(BswU2)67U                                                                                                  /* [818] ComConf_ComSignal_D04694 */
    ,(BswU2)67U                                                                                                  /* [819] ComConf_ComSignal_D04695 */
    ,(BswU2)67U                                                                                                  /* [820] ComConf_ComSignal_D04696 */
    ,(BswU2)67U                                                                                                  /* [821] ComConf_ComSignal_D04697 */
    ,(BswU2)67U                                                                                                  /* [822] ComConf_ComSignal_D04698 */
    ,(BswU2)67U                                                                                                  /* [823] ComConf_ComSignal_D04699 */
    ,(BswU2)67U                                                                                                  /* [824] ComConf_ComSignal_D04700 */
    ,(BswU2)67U                                                                                                  /* [825] ComConf_ComSignal_D04701 */
    ,(BswU2)67U                                                                                                  /* [826] ComConf_ComSignal_D04702 */
    ,(BswU2)67U                                                                                                  /* [827] ComConf_ComSignal_D04703 */
    ,(BswU2)67U                                                                                                  /* [828] ComConf_ComSignal_D04704 */
    ,(BswU2)67U                                                                                                  /* [829] ComConf_ComSignal_D04705 */
    ,(BswU2)67U                                                                                                  /* [830] ComConf_ComSignal_D04706 */
    ,(BswU2)67U                                                                                                  /* [831] ComConf_ComSignal_D04707 */
    ,(BswU2)67U                                                                                                  /* [832] ComConf_ComSignal_D04708 */
    ,(BswU2)67U                                                                                                  /* [833] ComConf_ComSignal_D04709 */
    ,(BswU2)67U                                                                                                  /* [834] ComConf_ComSignal_D04710 */
    ,(BswU2)67U                                                                                                  /* [835] ComConf_ComSignal_D04711 */
    ,(BswU2)67U                                                                                                  /* [836] ComConf_ComSignal_D04712 */
    ,(BswU2)67U                                                                                                  /* [837] ComConf_ComSignal_D04713 */
    ,(BswU2)67U                                                                                                  /* [838] ComConf_ComSignal_D04714 */
    ,(BswU2)67U                                                                                                  /* [839] ComConf_ComSignal_D04715 */
    ,(BswU2)67U                                                                                                  /* [840] ComConf_ComSignal_D04716 */
    ,(BswU2)67U                                                                                                  /* [841] ComConf_ComSignal_D04717 */
    ,(BswU2)67U                                                                                                  /* [842] ComConf_ComSignal_D04718 */
    ,(BswU2)67U                                                                                                  /* [843] ComConf_ComSignal_D04719 */
    ,(BswU2)67U                                                                                                  /* [844] ComConf_ComSignal_D04720 */
    ,(BswU2)67U                                                                                                  /* [845] ComConf_ComSignal_D04721 */
    ,(BswU2)67U                                                                                                  /* [846] ComConf_ComSignal_D04722 */
    ,(BswU2)67U                                                                                                  /* [847] ComConf_ComSignal_D04723 */
    ,(BswU2)67U                                                                                                  /* [848] ComConf_ComSignal_D04724 */
    ,(BswU2)67U                                                                                                  /* [849] ComConf_ComSignal_D04725 */
    ,(BswU2)67U                                                                                                  /* [850] ComConf_ComSignal_D04726 */
    ,(BswU2)67U                                                                                                  /* [851] ComConf_ComSignal_FV0A8_D */
    ,(BswU2)67U                                                                                                  /* [852] ComConf_ComSignal_KZK0A8_D */
    ,(BswU2)68U                                                                                                  /* [853] ComConf_ComSignal_LK_ST */
    ,(BswU2)68U                                                                                                  /* [854] ComConf_ComSignal_LK_FUNC */
    ,(BswU2)68U                                                                                                  /* [855] ComConf_ComSignal_ULK_ST */
    ,(BswU2)68U                                                                                                  /* [856] ComConf_ComSignal_ULK_FUNC */
    ,(BswU2)69U                                                                                                  /* [857] ComConf_ComSignal_RSISIDME */
    ,(BswU2)69U                                                                                                  /* [858] ComConf_ComSignal_RSISIDID */
    ,(BswU2)69U                                                                                                  /* [859] ComConf_ComSignal_D04752 */
    ,(BswU2)69U                                                                                                  /* [860] ComConf_ComSignal_D04753 */
    ,(BswU2)70U                                                                                                  /* [861] ComConf_ComSignal_D04818 */
    ,(BswU2)70U                                                                                                  /* [862] ComConf_ComSignal_D04819 */
    ,(BswU2)70U                                                                                                  /* [863] ComConf_ComSignal_D04820 */
    ,(BswU2)70U                                                                                                  /* [864] ComConf_ComSignal_D04821 */
    ,(BswU2)70U                                                                                                  /* [865] ComConf_ComSignal_D04822 */
    ,(BswU2)70U                                                                                                  /* [866] ComConf_ComSignal_D04823 */
    ,(BswU2)70U                                                                                                  /* [867] ComConf_ComSignal_D04824 */
    ,(BswU2)70U                                                                                                  /* [868] ComConf_ComSignal_D04825 */
    ,(BswU2)70U                                                                                                  /* [869] ComConf_ComSignal_D04826 */
    ,(BswU2)70U                                                                                                  /* [870] ComConf_ComSignal_LR_RC_PS */
    ,(BswU2)70U                                                                                                  /* [871] ComConf_ComSignal_D04827 */
    ,(BswU2)70U                                                                                                  /* [872] ComConf_ComSignal_D04828 */
    ,(BswU2)71U                                                                                                  /* [873] ComConf_ComSignal_LR_SL_PS */
    ,(BswU2)71U                                                                                                  /* [874] ComConf_ComSignal_D04829 */
    ,(BswU2)71U                                                                                                  /* [875] ComConf_ComSignal_D04830 */
    ,(BswU2)71U                                                                                                  /* [876] ComConf_ComSignal_D04831 */
    ,(BswU2)71U                                                                                                  /* [877] ComConf_ComSignal_D04832 */
    ,(BswU2)71U                                                                                                  /* [878] ComConf_ComSignal_D04833 */
    ,(BswU2)71U                                                                                                  /* [879] ComConf_ComSignal_D04834 */
    ,(BswU2)71U                                                                                                  /* [880] ComConf_ComSignal_D04835 */
    ,(BswU2)71U                                                                                                  /* [881] ComConf_ComSignal_D04836 */
    ,(BswU2)71U                                                                                                  /* [882] ComConf_ComSignal_D04837 */
    ,(BswU2)71U                                                                                                  /* [883] ComConf_ComSignal_D04838 */
    ,(BswU2)71U                                                                                                  /* [884] ComConf_ComSignal_D04839 */
    ,(BswU2)72U                                                                                                  /* [885] ComConf_ComSignal_LR_LF_PS */
    ,(BswU2)72U                                                                                                  /* [886] ComConf_ComSignal_D04840 */
    ,(BswU2)72U                                                                                                  /* [887] ComConf_ComSignal_D04841 */
    ,(BswU2)72U                                                                                                  /* [888] ComConf_ComSignal_D04842 */
    ,(BswU2)72U                                                                                                  /* [889] ComConf_ComSignal_D04843 */
    ,(BswU2)72U                                                                                                  /* [890] ComConf_ComSignal_D04844 */
    ,(BswU2)72U                                                                                                  /* [891] ComConf_ComSignal_D04845 */
    ,(BswU2)72U                                                                                                  /* [892] ComConf_ComSignal_D04846 */
    ,(BswU2)72U                                                                                                  /* [893] ComConf_ComSignal_D04847 */
    ,(BswU2)72U                                                                                                  /* [894] ComConf_ComSignal_D04848 */
    ,(BswU2)72U                                                                                                  /* [895] ComConf_ComSignal_D04849 */
    ,(BswU2)72U                                                                                                  /* [896] ComConf_ComSignal_D04850 */
    ,(BswU2)73U                                                                                                  /* [897] ComConf_ComSignal_RTQRRLMG */
    ,(BswU2)73U                                                                                                  /* [898] ComConf_ComSignal_RTQFRLMG */
    ,(BswU2)74U                                                                                                  /* [899] ComConf_ComSignal_BAOF_PDC */
    ,(BswU2)75U                                                                                                  /* [900] ComConf_ComSignal_SIDPWC0 */
    ,(BswU2)75U                                                                                                  /* [901] ComConf_ComSignal_SIDPWC1 */
    ,(BswU2)75U                                                                                                  /* [902] ComConf_ComSignal_SIDPWC2 */
    ,(BswU2)75U                                                                                                  /* [903] ComConf_ComSignal_SIDPWC3 */
    ,(BswU2)75U                                                                                                  /* [904] ComConf_ComSignal_SIDPWC4 */
    ,(BswU2)75U                                                                                                  /* [905] ComConf_ComSignal_SIDPWC5 */
    ,(BswU2)75U                                                                                                  /* [906] ComConf_ComSignal_SIDPWC6 */
    ,(BswU2)75U                                                                                                  /* [907] ComConf_ComSignal_SIDPWC7 */
    ,(BswU2)75U                                                                                                  /* [908] ComConf_ComSignal_SIDPWC8 */
    ,(BswU2)75U                                                                                                  /* [909] ComConf_ComSignal_SIDPWC9 */
    ,(BswU2)75U                                                                                                  /* [910] ComConf_ComSignal_SIDPWC10 */
    ,(BswU2)75U                                                                                                  /* [911] ComConf_ComSignal_SIDPWC11 */
    ,(BswU2)75U                                                                                                  /* [912] ComConf_ComSignal_SIDPWC12 */
    ,(BswU2)75U                                                                                                  /* [913] ComConf_ComSignal_SIDPWC13 */
    ,(BswU2)75U                                                                                                  /* [914] ComConf_ComSignal_SIDPWC14 */
    ,(BswU2)75U                                                                                                  /* [915] ComConf_ComSignal_SIDPWC15 */
    ,(BswU2)75U                                                                                                  /* [916] ComConf_ComSignal_SIDPWC16 */
    ,(BswU2)75U                                                                                                  /* [917] ComConf_ComSignal_SIDPWC17 */
    ,(BswU2)75U                                                                                                  /* [918] ComConf_ComSignal_SIDPWC18 */
    ,(BswU2)75U                                                                                                  /* [919] ComConf_ComSignal_SIDPWC19 */
    ,(BswU2)75U                                                                                                  /* [920] ComConf_ComSignal_SIDPWC20 */
    ,(BswU2)75U                                                                                                  /* [921] ComConf_ComSignal_SIDPWC21 */
    ,(BswU2)75U                                                                                                  /* [922] ComConf_ComSignal_SIDPWC22 */
    ,(BswU2)75U                                                                                                  /* [923] ComConf_ComSignal_SIDPWC23 */
    ,(BswU2)75U                                                                                                  /* [924] ComConf_ComSignal_SIDPWC24 */
    ,(BswU2)75U                                                                                                  /* [925] ComConf_ComSignal_SIDPWC25 */
    ,(BswU2)75U                                                                                                  /* [926] ComConf_ComSignal_SIDPWC26 */
    ,(BswU2)75U                                                                                                  /* [927] ComConf_ComSignal_SIDPWC27 */
    ,(BswU2)75U                                                                                                  /* [928] ComConf_ComSignal_SIDPWC28 */
    ,(BswU2)75U                                                                                                  /* [929] ComConf_ComSignal_SIDPWC29 */
    ,(BswU2)75U                                                                                                  /* [930] ComConf_ComSignal_SIDPWC30 */
    ,(BswU2)75U                                                                                                  /* [931] ComConf_ComSignal_SIDPWC31 */
    ,(BswU2)76U                                                                                                  /* [932] ComConf_ComSignal_E_CRC14F */
    ,(BswU2)76U                                                                                                  /* [933] ComConf_ComSignal_E_CNT14F */
    ,(BswU2)76U                                                                                                  /* [934] ComConf_ComSignal_RCPMD */
    ,(BswU2)76U                                                                                                  /* [935] ComConf_ComSignal_D05431 */
    ,(BswU2)76U                                                                                                  /* [936] ComConf_ComSignal_RCPFAIL */
    ,(BswU2)76U                                                                                                  /* [937] ComConf_ComSignal_D05432 */
    ,(BswU2)76U                                                                                                  /* [938] ComConf_ComSignal_D05433 */
    ,(BswU2)76U                                                                                                  /* [939] ComConf_ComSignal_D05434 */
    ,(BswU2)76U                                                                                                  /* [940] ComConf_ComSignal_RCPONST */
    ,(BswU2)76U                                                                                                  /* [941] ComConf_ComSignal_D05435 */
    ,(BswU2)76U                                                                                                  /* [942] ComConf_ComSignal_D05436 */
    ,(BswU2)77U                                                                                                  /* [943] ComConf_ComSignal_D05441 */
    ,(BswU2)77U                                                                                                  /* [944] ComConf_ComSignal_D05442 */
    ,(BswU2)77U                                                                                                  /* [945] ComConf_ComSignal_D05443 */
    ,(BswU2)77U                                                                                                  /* [946] ComConf_ComSignal_D05444 */
    ,(BswU2)77U                                                                                                  /* [947] ComConf_ComSignal_D05445 */
    ,(BswU2)77U                                                                                                  /* [948] ComConf_ComSignal_D05446 */
    ,(BswU2)77U                                                                                                  /* [949] ComConf_ComSignal_D05447 */
    ,(BswU2)77U                                                                                                  /* [950] ComConf_ComSignal_D05448 */
    ,(BswU2)77U                                                                                                  /* [951] ComConf_ComSignal_D05449 */
    ,(BswU2)77U                                                                                                  /* [952] ComConf_ComSignal_RR_RC_PS */
    ,(BswU2)77U                                                                                                  /* [953] ComConf_ComSignal_D05450 */
    ,(BswU2)77U                                                                                                  /* [954] ComConf_ComSignal_D05451 */
    ,(BswU2)78U                                                                                                  /* [955] ComConf_ComSignal_RR_SL_PS */
    ,(BswU2)78U                                                                                                  /* [956] ComConf_ComSignal_D05452 */
    ,(BswU2)78U                                                                                                  /* [957] ComConf_ComSignal_D05453 */
    ,(BswU2)78U                                                                                                  /* [958] ComConf_ComSignal_D05454 */
    ,(BswU2)78U                                                                                                  /* [959] ComConf_ComSignal_D05455 */
    ,(BswU2)78U                                                                                                  /* [960] ComConf_ComSignal_D05456 */
    ,(BswU2)78U                                                                                                  /* [961] ComConf_ComSignal_D05457 */
    ,(BswU2)78U                                                                                                  /* [962] ComConf_ComSignal_D05458 */
    ,(BswU2)78U                                                                                                  /* [963] ComConf_ComSignal_D05459 */
    ,(BswU2)78U                                                                                                  /* [964] ComConf_ComSignal_D05460 */
    ,(BswU2)78U                                                                                                  /* [965] ComConf_ComSignal_D05461 */
    ,(BswU2)78U                                                                                                  /* [966] ComConf_ComSignal_D05462 */
    ,(BswU2)79U                                                                                                  /* [967] ComConf_ComSignal_RR_LF_PS */
    ,(BswU2)79U                                                                                                  /* [968] ComConf_ComSignal_D05463 */
    ,(BswU2)79U                                                                                                  /* [969] ComConf_ComSignal_D05464 */
    ,(BswU2)79U                                                                                                  /* [970] ComConf_ComSignal_D05465 */
    ,(BswU2)79U                                                                                                  /* [971] ComConf_ComSignal_D05466 */
    ,(BswU2)79U                                                                                                  /* [972] ComConf_ComSignal_D05467 */
    ,(BswU2)79U                                                                                                  /* [973] ComConf_ComSignal_D05468 */
    ,(BswU2)79U                                                                                                  /* [974] ComConf_ComSignal_D05469 */
    ,(BswU2)79U                                                                                                  /* [975] ComConf_ComSignal_D05470 */
    ,(BswU2)79U                                                                                                  /* [976] ComConf_ComSignal_D05471 */
    ,(BswU2)79U                                                                                                  /* [977] ComConf_ComSignal_D05472 */
    ,(BswU2)79U                                                                                                  /* [978] ComConf_ComSignal_D05473 */
    ,(BswU2)80U                                                                                                  /* [979] ComConf_ComSignal_D_YEAR */
    ,(BswU2)80U                                                                                                  /* [980] ComConf_ComSignal_D_MONT */
    ,(BswU2)80U                                                                                                  /* [981] ComConf_ComSignal_D_DAY */
    ,(BswU2)80U                                                                                                  /* [982] ComConf_ComSignal_D_HOUR */
    ,(BswU2)80U                                                                                                  /* [983] ComConf_ComSignal_D_MIN */
    ,(BswU2)80U                                                                                                  /* [984] ComConf_ComSignal_D_SEC */
    ,(BswU2)81U                                                                                                  /* [985] ComConf_ComSignal_D05474 */
    ,(BswU2)81U                                                                                                  /* [986] ComConf_ComSignal_D05475 */
    ,(BswU2)81U                                                                                                  /* [987] ComConf_ComSignal_D05476 */
    ,(BswU2)81U                                                                                                  /* [988] ComConf_ComSignal_D05477 */
    ,(BswU2)81U                                                                                                  /* [989] ComConf_ComSignal_D05478 */
    ,(BswU2)81U                                                                                                  /* [990] ComConf_ComSignal_LATUDE */
    ,(BswU2)81U                                                                                                  /* [991] ComConf_ComSignal_LOTUDE1 */
    ,(BswU2)81U                                                                                                  /* [992] ComConf_ComSignal_D05479 */
    ,(BswU2)81U                                                                                                  /* [993] ComConf_ComSignal_D05480 */
    ,(BswU2)81U                                                                                                  /* [994] ComConf_ComSignal_D_LAT1 */
    ,(BswU2)81U                                                                                                  /* [995] ComConf_ComSignal_D_LAT2 */
    ,(BswU2)82U                                                                                                  /* [996] ComConf_ComSignal_D05481 */
    ,(BswU2)82U                                                                                                  /* [997] ComConf_ComSignal_D05482 */
    ,(BswU2)82U                                                                                                  /* [998] ComConf_ComSignal_D05483 */
    ,(BswU2)82U                                                                                                  /* [999] ComConf_ComSignal_D_LON1 */
    ,(BswU2)82U                                                                                                  /* [1000] ComConf_ComSignal_D_LON2 */
    ,(BswU2)83U                                                                                                  /* [1001] ComConf_ComSignal_D05484 */
    ,(BswU2)83U                                                                                                  /* [1002] ComConf_ComSignal_D05485 */
    ,(BswU2)83U                                                                                                  /* [1003] ComConf_ComSignal_D05486 */
    ,(BswU2)83U                                                                                                  /* [1004] ComConf_ComSignal_D05487 */
    ,(BswU2)83U                                                                                                  /* [1005] ComConf_ComSignal_ALTITUDE */
    ,(BswU2)84U                                                                                                  /* [1006] ComConf_ComSignal_OTADTYPE */
    ,(BswU2)84U                                                                                                  /* [1007] ComConf_ComSignal_OTADSTAT */
    ,(BswU2)84U                                                                                                  /* [1008] ComConf_ComSignal_OTADPROG */
    ,(BswU2)84U                                                                                                  /* [1009] ComConf_ComSignal_OTADERR */
    ,(BswU2)85U                                                                                                  /* [1010] ComConf_ComSignal_RSCYCL11 */
    ,(BswU2)85U                                                                                                  /* [1011] ComConf_ComSignal_RSCYCL12 */
    ,(BswU2)85U                                                                                                  /* [1012] ComConf_ComSignal_RSCYCL13 */
    ,(BswU2)85U                                                                                                  /* [1013] ComConf_ComSignal_RSCYCL14 */
    ,(BswU2)85U                                                                                                  /* [1014] ComConf_ComSignal_RSCYCL15 */
    ,(BswU2)85U                                                                                                  /* [1015] ComConf_ComSignal_RSCYCL16 */
    ,(BswU2)86U                                                                                                  /* [1016] ComConf_ComSignal_FRVH */
    ,(BswU2)86U                                                                                                  /* [1017] ComConf_ComSignal_FLVH */
    ,(BswU2)86U                                                                                                  /* [1018] ComConf_ComSignal_RRVH */
    ,(BswU2)86U                                                                                                  /* [1019] ComConf_ComSignal_RLVH */
    ,(BswU2)86U                                                                                                  /* [1020] ComConf_ComSignal_D05601 */
    ,(BswU2)86U                                                                                                  /* [1021] ComConf_ComSignal_D05602 */
    ,(BswU2)86U                                                                                                  /* [1022] ComConf_ComSignal_D05603 */
    ,(BswU2)86U                                                                                                  /* [1023] ComConf_ComSignal_D05604 */
    ,(BswU2)86U                                                                                                  /* [1024] ComConf_ComSignal_D05605 */
    ,(BswU2)86U                                                                                                  /* [1025] ComConf_ComSignal_D05606 */
    ,(BswU2)86U                                                                                                  /* [1026] ComConf_ComSignal_D05607 */
    ,(BswU2)86U                                                                                                  /* [1027] ComConf_ComSignal_D05608 */
    ,(BswU2)86U                                                                                                  /* [1028] ComConf_ComSignal_D05609 */
    ,(BswU2)86U                                                                                                  /* [1029] ComConf_ComSignal_D05610 */
    ,(BswU2)86U                                                                                                  /* [1030] ComConf_ComSignal_D05611 */
    ,(BswU2)86U                                                                                                  /* [1031] ComConf_ComSignal_D05612 */
    ,(BswU2)86U                                                                                                  /* [1032] ComConf_ComSignal_D05613 */
    ,(BswU2)86U                                                                                                  /* [1033] ComConf_ComSignal_D05614 */
    ,(BswU2)86U                                                                                                  /* [1034] ComConf_ComSignal_D05615 */
    ,(BswU2)86U                                                                                                  /* [1035] ComConf_ComSignal_D05616 */
    ,(BswU2)86U                                                                                                  /* [1036] ComConf_ComSignal_D05617 */
    ,(BswU2)86U                                                                                                  /* [1037] ComConf_ComSignal_D05618 */
    ,(BswU2)86U                                                                                                  /* [1038] ComConf_ComSignal_D05619 */
    ,(BswU2)86U                                                                                                  /* [1039] ComConf_ComSignal_D05620 */
    ,(BswU2)87U                                                                                                  /* [1040] ComConf_ComSignal_DVGR01 */
    ,(BswU2)87U                                                                                                  /* [1041] ComConf_ComSignal_DVGR02 */
    ,(BswU2)87U                                                                                                  /* [1042] ComConf_ComSignal_DVGR03 */
    ,(BswU2)87U                                                                                                  /* [1043] ComConf_ComSignal_DVGR04 */
    ,(BswU2)87U                                                                                                  /* [1044] ComConf_ComSignal_DVGR05 */
    ,(BswU2)87U                                                                                                  /* [1045] ComConf_ComSignal_DVGR06 */
    ,(BswU2)87U                                                                                                  /* [1046] ComConf_ComSignal_DVGR07 */
    ,(BswU2)87U                                                                                                  /* [1047] ComConf_ComSignal_DVGR08 */
    ,(BswU2)87U                                                                                                  /* [1048] ComConf_ComSignal_DVGR09 */
    ,(BswU2)87U                                                                                                  /* [1049] ComConf_ComSignal_DVGR10 */
    ,(BswU2)87U                                                                                                  /* [1050] ComConf_ComSignal_DVGR11 */
    ,(BswU2)87U                                                                                                  /* [1051] ComConf_ComSignal_DVGR12 */
    ,(BswU2)87U                                                                                                  /* [1052] ComConf_ComSignal_DVGR13 */
    ,(BswU2)87U                                                                                                  /* [1053] ComConf_ComSignal_DVGR14 */
    ,(BswU2)87U                                                                                                  /* [1054] ComConf_ComSignal_DVGR15 */
    ,(BswU2)87U                                                                                                  /* [1055] ComConf_ComSignal_DVGR16 */
    ,(BswU2)87U                                                                                                  /* [1056] ComConf_ComSignal_DVGR17 */
    ,(BswU2)87U                                                                                                  /* [1057] ComConf_ComSignal_DVGR18 */
    ,(BswU2)87U                                                                                                  /* [1058] ComConf_ComSignal_DVGR19 */
    ,(BswU2)87U                                                                                                  /* [1059] ComConf_ComSignal_DVGR20 */
    ,(BswU2)87U                                                                                                  /* [1060] ComConf_ComSignal_DVGR21 */
    ,(BswU2)87U                                                                                                  /* [1061] ComConf_ComSignal_DVGR22 */
    ,(BswU2)87U                                                                                                  /* [1062] ComConf_ComSignal_DVGR23 */
    ,(BswU2)87U                                                                                                  /* [1063] ComConf_ComSignal_DVGR24 */
    ,(BswU2)87U                                                                                                  /* [1064] ComConf_ComSignal_DVGR25 */
    ,(BswU2)87U                                                                                                  /* [1065] ComConf_ComSignal_DVGR26 */
    ,(BswU2)87U                                                                                                  /* [1066] ComConf_ComSignal_DVGR27 */
    ,(BswU2)87U                                                                                                  /* [1067] ComConf_ComSignal_DVGR28 */
    ,(BswU2)87U                                                                                                  /* [1068] ComConf_ComSignal_DVGR29 */
    ,(BswU2)87U                                                                                                  /* [1069] ComConf_ComSignal_DVGR30 */
    ,(BswU2)87U                                                                                                  /* [1070] ComConf_ComSignal_DVGR31 */
    ,(BswU2)87U                                                                                                  /* [1071] ComConf_ComSignal_DVGR32 */
    ,(BswU2)88U                                                                                                  /* [1072] ComConf_ComSignal_DRVSCID */
    ,(BswU2)88U                                                                                                  /* [1073] ComConf_ComSignal_DRVSC02 */
    ,(BswU2)88U                                                                                                  /* [1074] ComConf_ComSignal_DRVSC03 */
    ,(BswU2)88U                                                                                                  /* [1075] ComConf_ComSignal_DRVSC04 */
    ,(BswU2)88U                                                                                                  /* [1076] ComConf_ComSignal_DRVSC05 */
    ,(BswU2)88U                                                                                                  /* [1077] ComConf_ComSignal_DRVSC06 */
    ,(BswU2)88U                                                                                                  /* [1078] ComConf_ComSignal_DRVSC07 */
    ,(BswU2)88U                                                                                                  /* [1079] ComConf_ComSignal_DRVSC08 */
    ,(BswU2)88U                                                                                                  /* [1080] ComConf_ComSignal_DRVSC11 */
    ,(BswU2)88U                                                                                                  /* [1081] ComConf_ComSignal_DRVSC12 */
    ,(BswU2)88U                                                                                                  /* [1082] ComConf_ComSignal_DRVSC13 */
    ,(BswU2)88U                                                                                                  /* [1083] ComConf_ComSignal_DRVSC14 */
    ,(BswU2)88U                                                                                                  /* [1084] ComConf_ComSignal_DRVSC15 */
    ,(BswU2)88U                                                                                                  /* [1085] ComConf_ComSignal_DRVSC16 */
    ,(BswU2)88U                                                                                                  /* [1086] ComConf_ComSignal_DRVSC17 */
    ,(BswU2)88U                                                                                                  /* [1087] ComConf_ComSignal_DRVSC18 */
    ,(BswU2)88U                                                                                                  /* [1088] ComConf_ComSignal_DRVSC21 */
    ,(BswU2)88U                                                                                                  /* [1089] ComConf_ComSignal_DRVSC22 */
    ,(BswU2)88U                                                                                                  /* [1090] ComConf_ComSignal_DRVSC23 */
    ,(BswU2)88U                                                                                                  /* [1091] ComConf_ComSignal_DRVSC24 */
    ,(BswU2)88U                                                                                                  /* [1092] ComConf_ComSignal_DRVSC25 */
    ,(BswU2)88U                                                                                                  /* [1093] ComConf_ComSignal_DRVSC26 */
    ,(BswU2)88U                                                                                                  /* [1094] ComConf_ComSignal_DRVSC27 */
    ,(BswU2)88U                                                                                                  /* [1095] ComConf_ComSignal_DRVSC28 */
    ,(BswU2)88U                                                                                                  /* [1096] ComConf_ComSignal_DREPB01 */
    ,(BswU2)88U                                                                                                  /* [1097] ComConf_ComSignal_DREPB02 */
    ,(BswU2)88U                                                                                                  /* [1098] ComConf_ComSignal_DREPB03 */
    ,(BswU2)88U                                                                                                  /* [1099] ComConf_ComSignal_DREPB04 */
    ,(BswU2)88U                                                                                                  /* [1100] ComConf_ComSignal_DREPB05 */
    ,(BswU2)88U                                                                                                  /* [1101] ComConf_ComSignal_DREPB06 */
    ,(BswU2)88U                                                                                                  /* [1102] ComConf_ComSignal_DREPB07 */
    ,(BswU2)88U                                                                                                  /* [1103] ComConf_ComSignal_DREPB08 */
    ,(BswU2)89U                                                                                                  /* [1104] ComConf_ComSignal_E_CRC09E */
    ,(BswU2)89U                                                                                                  /* [1105] ComConf_ComSignal_E_CNT09E */
    ,(BswU2)89U                                                                                                  /* [1106] ComConf_ComSignal_SP1S */
    ,(BswU2)89U                                                                                                  /* [1107] ComConf_ComSignal_GVSPDINV */
    ,(BswU2)89U                                                                                                  /* [1108] ComConf_ComSignal_SP1P */
    ,(BswU2)89U                                                                                                  /* [1109] ComConf_ComSignal_SP1 */
    ,(BswU2)89U                                                                                                  /* [1110] ComConf_ComSignal_GVSPD */
    ,(BswU2)89U                                                                                                  /* [1111] ComConf_ComSignal_D05713 */
    ,(BswU2)89U                                                                                                  /* [1112] ComConf_ComSignal_D05714 */
    ,(BswU2)89U                                                                                                  /* [1113] ComConf_ComSignal_D05715 */
    ,(BswU2)89U                                                                                                  /* [1114] ComConf_ComSignal_D05716 */
    ,(BswU2)89U                                                                                                  /* [1115] ComConf_ComSignal_PWCF */
    ,(BswU2)89U                                                                                                  /* [1116] ComConf_ComSignal_PWC */
    ,(BswU2)89U                                                                                                  /* [1117] ComConf_ComSignal_D05717 */
    ,(BswU2)89U                                                                                                  /* [1118] ComConf_ComSignal_PWCS */
    ,(BswU2)89U                                                                                                  /* [1119] ComConf_ComSignal_PMCF */
    ,(BswU2)89U                                                                                                  /* [1120] ComConf_ComSignal_PMCS */
    ,(BswU2)89U                                                                                                  /* [1121] ComConf_ComSignal_PMC */
    ,(BswU2)89U                                                                                                  /* [1122] ComConf_ComSignal_D05718 */
    ,(BswU2)89U                                                                                                  /* [1123] ComConf_ComSignal_D05719 */
    ,(BswU2)89U                                                                                                  /* [1124] ComConf_ComSignal_D05720 */
    ,(BswU2)89U                                                                                                  /* [1125] ComConf_ComSignal_D05721 */
    ,(BswU2)89U                                                                                                  /* [1126] ComConf_ComSignal_D05722 */
    ,(BswU2)89U                                                                                                  /* [1127] ComConf_ComSignal_D05723 */
    ,(BswU2)89U                                                                                                  /* [1128] ComConf_ComSignal_D05724 */
    ,(BswU2)89U                                                                                                  /* [1129] ComConf_ComSignal_D05725 */
    ,(BswU2)89U                                                                                                  /* [1130] ComConf_ComSignal_D05726 */
    ,(BswU2)89U                                                                                                  /* [1131] ComConf_ComSignal_D05727 */
    ,(BswU2)89U                                                                                                  /* [1132] ComConf_ComSignal_D05728 */
    ,(BswU2)89U                                                                                                  /* [1133] ComConf_ComSignal_D05729 */
    ,(BswU2)89U                                                                                                  /* [1134] ComConf_ComSignal_FV09E_D */
    ,(BswU2)89U                                                                                                  /* [1135] ComConf_ComSignal_KZK09E_D */
    ,(BswU2)90U                                                                                                  /* [1136] ComConf_ComSignal_FRWIPOPE */
    ,(BswU2)90U                                                                                                  /* [1137] ComConf_ComSignal_FRWASH */
    ,(BswU2)90U                                                                                                  /* [1138] ComConf_ComSignal_RRWIPOPE */
    ,(BswU2)90U                                                                                                  /* [1139] ComConf_ComSignal_RRWASH */
    ,(BswU2)90U                                                                                                  /* [1140] ComConf_ComSignal_D06141 */
    ,(BswU2)91U                                                                                                  /* [1141] ComConf_ComSignal_W_STPZ */
    ,(BswU2)91U                                                                                                  /* [1142] ComConf_ComSignal_FI_STP */
    ,(BswU2)91U                                                                                                  /* [1143] ComConf_ComSignal_D06210 */
    ,(BswU2)91U                                                                                                  /* [1144] ComConf_ComSignal_FV086_D */
    ,(BswU2)91U                                                                                                  /* [1145] ComConf_ComSignal_KZK086_D */
    ,(BswU2)92U                                                                                                  /* [1146] ComConf_ComSignal_RECRNOFF */
    ,(BswU2)92U                                                                                                  /* [1147] ComConf_ComSignal_FAV_FNC */
    ,(BswU2)92U                                                                                                  /* [1148] ComConf_ComSignal_CHG_FUNC */
    ,(BswU2)92U                                                                                                  /* [1149] ComConf_ComSignal_GSNSOFF */
    ,(BswU2)92U                                                                                                  /* [1150] ComConf_ComSignal_DRBDBABN */
    ,(BswU2)93U                                                                                                  /* [1151] ComConf_ComSignal_R_AC_ST */
    ,(BswU2)93U                                                                                                  /* [1152] ComConf_ComSignal_R_SYS_2 */
    ,(BswU2)94U                                                                                                  /* [1153] ComConf_ComSignal_R_FTE_ST */
    ,(BswU2)94U                                                                                                  /* [1154] ComConf_ComSignal_R_BD_ST */
    ,(BswU2)94U                                                                                                  /* [1155] ComConf_ComSignal_R_TIME */
    ,(BswU2)95U                                                                                                  /* [1156] ComConf_ComSignal_R_INT_ST */
    ,(BswU2)96U                                                                                                  /* [1157] ComConf_ComSignal_R_LMP_ST */
    ,(BswU2)96U                                                                                                  /* [1158] ComConf_ComSignal_R_SDE_ST */
    ,(BswU2)96U                                                                                                  /* [1159] ComConf_ComSignal_R_SYS_3 */
    ,(BswU2)97U                                                                                                  /* [1160] ComConf_ComSignal_R_ST_ST */
    ,(BswU2)97U                                                                                                  /* [1161] ComConf_ComSignal_R_SYS_1 */
    ,(BswU2)98U                                                                                                  /* [1162] ComConf_ComSignal_EIC_EQP */
    ,(BswU2)98U                                                                                                  /* [1163] ComConf_ComSignal_EIC_FEQP */
    ,(BswU2)98U                                                                                                  /* [1164] ComConf_ComSignal_EIC_SEQP */
    ,(BswU2)98U                                                                                                  /* [1165] ComConf_ComSignal_EIC_IEQP */
    ,(BswU2)98U                                                                                                  /* [1166] ComConf_ComSignal_EIC_BEQP */
    ,(BswU2)98U                                                                                                  /* [1167] ComConf_ComSignal_QIC_BREQ */
    ,(BswU2)98U                                                                                                  /* [1168] ComConf_ComSignal_QIC_DISP */
    ,(BswU2)98U                                                                                                  /* [1169] ComConf_ComSignal_QIC_BVOL */
    ,(BswU2)98U                                                                                                  /* [1170] ComConf_ComSignal_QIC_DIS */
    ,(BswU2)98U                                                                                                  /* [1171] ComConf_ComSignal_EIC_DEQP */
    ,(BswU2)98U                                                                                                  /* [1172] ComConf_ComSignal_EIC_PEQP */
    ,(BswU2)98U                                                                                                  /* [1173] ComConf_ComSignal_EIC_REQP */
    ,(BswU2)98U                                                                                                  /* [1174] ComConf_ComSignal_EIC_LEQP */
    ,(BswU2)98U                                                                                                  /* [1175] ComConf_ComSignal_AIC_DRC */
    ,(BswU2)98U                                                                                                  /* [1176] ComConf_ComSignal_AIC_DMRC */
    ,(BswU2)98U                                                                                                  /* [1177] ComConf_ComSignal_AIC_DFRC */
    ,(BswU2)98U                                                                                                  /* [1178] ComConf_ComSignal_AIC_DBRC */
    ,(BswU2)98U                                                                                                  /* [1179] ComConf_ComSignal_AIC_DRRC */
    ,(BswU2)98U                                                                                                  /* [1180] ComConf_ComSignal_SIC_DMST */
    ,(BswU2)98U                                                                                                  /* [1181] ComConf_ComSignal_SIC_DCST */
    ,(BswU2)98U                                                                                                  /* [1182] ComConf_ComSignal_SIC_DFFL */
    ,(BswU2)98U                                                                                                  /* [1183] ComConf_ComSignal_SIC_DFFP */
    ,(BswU2)98U                                                                                                  /* [1184] ComConf_ComSignal_SIC_DFRL */
    ,(BswU2)98U                                                                                                  /* [1185] ComConf_ComSignal_SIC_DFRP */
    ,(BswU2)98U                                                                                                  /* [1186] ComConf_ComSignal_SIC_DF5L */
    ,(BswU2)98U                                                                                                  /* [1187] ComConf_ComSignal_SIC_DFDL */
    ,(BswU2)98U                                                                                                  /* [1188] ComConf_ComSignal_SIC_DFDP */
    ,(BswU2)98U                                                                                                  /* [1189] ComConf_ComSignal_SIC_DF4L */
    ,(BswU2)98U                                                                                                  /* [1190] ComConf_ComSignal_SIC_DF4P */
    ,(BswU2)98U                                                                                                  /* [1191] ComConf_ComSignal_SIC_DF5P */
    ,(BswU2)98U                                                                                                  /* [1192] ComConf_ComSignal_SIC_DBFL */
    ,(BswU2)98U                                                                                                  /* [1193] ComConf_ComSignal_SIC_DBFP */
    ,(BswU2)98U                                                                                                  /* [1194] ComConf_ComSignal_SIC_DBRL */
    ,(BswU2)98U                                                                                                  /* [1195] ComConf_ComSignal_SIC_DBRP */
    ,(BswU2)98U                                                                                                  /* [1196] ComConf_ComSignal_SIC_DB5L */
    ,(BswU2)98U                                                                                                  /* [1197] ComConf_ComSignal_SIC_DBDL */
    ,(BswU2)98U                                                                                                  /* [1198] ComConf_ComSignal_SIC_DBDP */
    ,(BswU2)98U                                                                                                  /* [1199] ComConf_ComSignal_SIC_DB4L */
    ,(BswU2)98U                                                                                                  /* [1200] ComConf_ComSignal_SIC_DB4P */
    ,(BswU2)98U                                                                                                  /* [1201] ComConf_ComSignal_SIC_DB5P */
    ,(BswU2)98U                                                                                                  /* [1202] ComConf_ComSignal_SIC_DRFL */
    ,(BswU2)98U                                                                                                  /* [1203] ComConf_ComSignal_SIC_DRRL */
    ,(BswU2)98U                                                                                                  /* [1204] ComConf_ComSignal_SIC_DRDL */
    ,(BswU2)98U                                                                                                  /* [1205] ComConf_ComSignal_SIC_DR4L */
    ,(BswU2)98U                                                                                                  /* [1206] ComConf_ComSignal_SIC_DR5L */
    ,(BswU2)98U                                                                                                  /* [1207] ComConf_ComSignal_SIC_DRFK */
    ,(BswU2)98U                                                                                                  /* [1208] ComConf_ComSignal_SIC_DRRK */
    ,(BswU2)98U                                                                                                  /* [1209] ComConf_ComSignal_SIC_DRDK */
    ,(BswU2)98U                                                                                                  /* [1210] ComConf_ComSignal_SIC_DR4K */
    ,(BswU2)98U                                                                                                  /* [1211] ComConf_ComSignal_SIC_DR5K */
    ,(BswU2)98U                                                                                                  /* [1212] ComConf_ComSignal_AIC_PRC */
    ,(BswU2)98U                                                                                                  /* [1213] ComConf_ComSignal_AIC_PMRC */
    ,(BswU2)98U                                                                                                  /* [1214] ComConf_ComSignal_AIC_PFRC */
    ,(BswU2)98U                                                                                                  /* [1215] ComConf_ComSignal_AIC_PBRC */
    ,(BswU2)98U                                                                                                  /* [1216] ComConf_ComSignal_AIC_PRRC */
    ,(BswU2)98U                                                                                                  /* [1217] ComConf_ComSignal_SIC_PMST */
    ,(BswU2)98U                                                                                                  /* [1218] ComConf_ComSignal_SIC_PCST */
    ,(BswU2)98U                                                                                                  /* [1219] ComConf_ComSignal_SIC_PFFL */
    ,(BswU2)98U                                                                                                  /* [1220] ComConf_ComSignal_SIC_PFFP */
    ,(BswU2)98U                                                                                                  /* [1221] ComConf_ComSignal_SIC_PFRL */
    ,(BswU2)98U                                                                                                  /* [1222] ComConf_ComSignal_SIC_PFRP */
    ,(BswU2)98U                                                                                                  /* [1223] ComConf_ComSignal_SIC_PF5L */
    ,(BswU2)98U                                                                                                  /* [1224] ComConf_ComSignal_SIC_PFDL */
    ,(BswU2)98U                                                                                                  /* [1225] ComConf_ComSignal_SIC_PFDP */
    ,(BswU2)98U                                                                                                  /* [1226] ComConf_ComSignal_SIC_PF4L */
    ,(BswU2)98U                                                                                                  /* [1227] ComConf_ComSignal_SIC_PF4P */
    ,(BswU2)98U                                                                                                  /* [1228] ComConf_ComSignal_SIC_PF5P */
    ,(BswU2)98U                                                                                                  /* [1229] ComConf_ComSignal_SIC_PBFL */
    ,(BswU2)98U                                                                                                  /* [1230] ComConf_ComSignal_SIC_PBFP */
    ,(BswU2)98U                                                                                                  /* [1231] ComConf_ComSignal_SIC_PBRL */
    ,(BswU2)98U                                                                                                  /* [1232] ComConf_ComSignal_SIC_PBRP */
    ,(BswU2)98U                                                                                                  /* [1233] ComConf_ComSignal_SIC_PB5L */
    ,(BswU2)98U                                                                                                  /* [1234] ComConf_ComSignal_SIC_PBDL */
    ,(BswU2)98U                                                                                                  /* [1235] ComConf_ComSignal_SIC_PBDP */
    ,(BswU2)98U                                                                                                  /* [1236] ComConf_ComSignal_SIC_PB4L */
    ,(BswU2)98U                                                                                                  /* [1237] ComConf_ComSignal_SIC_PB4P */
    ,(BswU2)98U                                                                                                  /* [1238] ComConf_ComSignal_SIC_PB5P */
    ,(BswU2)98U                                                                                                  /* [1239] ComConf_ComSignal_SIC_PRFL */
    ,(BswU2)98U                                                                                                  /* [1240] ComConf_ComSignal_SIC_PRRL */
    ,(BswU2)98U                                                                                                  /* [1241] ComConf_ComSignal_SIC_PRDL */
    ,(BswU2)98U                                                                                                  /* [1242] ComConf_ComSignal_SIC_PR4L */
    ,(BswU2)98U                                                                                                  /* [1243] ComConf_ComSignal_SIC_PR5L */
    ,(BswU2)98U                                                                                                  /* [1244] ComConf_ComSignal_SIC_PRFK */
    ,(BswU2)98U                                                                                                  /* [1245] ComConf_ComSignal_SIC_PRRK */
    ,(BswU2)98U                                                                                                  /* [1246] ComConf_ComSignal_SIC_PRDK */
    ,(BswU2)98U                                                                                                  /* [1247] ComConf_ComSignal_SIC_PR4K */
    ,(BswU2)98U                                                                                                  /* [1248] ComConf_ComSignal_SIC_PR5K */
    ,(BswU2)99U                                                                                                  /* [1249] ComConf_ComSignal_AIC_RRC */
    ,(BswU2)99U                                                                                                  /* [1250] ComConf_ComSignal_AIC_RMRC */
    ,(BswU2)99U                                                                                                  /* [1251] ComConf_ComSignal_AIC_RFRC */
    ,(BswU2)99U                                                                                                  /* [1252] ComConf_ComSignal_AIC_RBRC */
    ,(BswU2)99U                                                                                                  /* [1253] ComConf_ComSignal_AIC_RRRC */
    ,(BswU2)99U                                                                                                  /* [1254] ComConf_ComSignal_SIC_RMST */
    ,(BswU2)99U                                                                                                  /* [1255] ComConf_ComSignal_SIC_RCST */
    ,(BswU2)99U                                                                                                  /* [1256] ComConf_ComSignal_SIC_RFFL */
    ,(BswU2)99U                                                                                                  /* [1257] ComConf_ComSignal_SIC_RFFP */
    ,(BswU2)99U                                                                                                  /* [1258] ComConf_ComSignal_SIC_RFRL */
    ,(BswU2)99U                                                                                                  /* [1259] ComConf_ComSignal_SIC_RFRP */
    ,(BswU2)99U                                                                                                  /* [1260] ComConf_ComSignal_SIC_RF5L */
    ,(BswU2)99U                                                                                                  /* [1261] ComConf_ComSignal_SIC_RFDL */
    ,(BswU2)99U                                                                                                  /* [1262] ComConf_ComSignal_SIC_RFDP */
    ,(BswU2)99U                                                                                                  /* [1263] ComConf_ComSignal_SIC_RF4L */
    ,(BswU2)99U                                                                                                  /* [1264] ComConf_ComSignal_SIC_RF4P */
    ,(BswU2)99U                                                                                                  /* [1265] ComConf_ComSignal_SIC_RF5P */
    ,(BswU2)99U                                                                                                  /* [1266] ComConf_ComSignal_SIC_RBFL */
    ,(BswU2)99U                                                                                                  /* [1267] ComConf_ComSignal_SIC_RBFP */
    ,(BswU2)99U                                                                                                  /* [1268] ComConf_ComSignal_SIC_RBRL */
    ,(BswU2)99U                                                                                                  /* [1269] ComConf_ComSignal_SIC_RBRP */
    ,(BswU2)99U                                                                                                  /* [1270] ComConf_ComSignal_SIC_RB5L */
    ,(BswU2)99U                                                                                                  /* [1271] ComConf_ComSignal_SIC_RBDL */
    ,(BswU2)99U                                                                                                  /* [1272] ComConf_ComSignal_SIC_RBDP */
    ,(BswU2)99U                                                                                                  /* [1273] ComConf_ComSignal_SIC_RB4L */
    ,(BswU2)99U                                                                                                  /* [1274] ComConf_ComSignal_SIC_RB4P */
    ,(BswU2)99U                                                                                                  /* [1275] ComConf_ComSignal_SIC_RB5P */
    ,(BswU2)99U                                                                                                  /* [1276] ComConf_ComSignal_SIC_RRFL */
    ,(BswU2)99U                                                                                                  /* [1277] ComConf_ComSignal_SIC_RRRL */
    ,(BswU2)99U                                                                                                  /* [1278] ComConf_ComSignal_SIC_RRDL */
    ,(BswU2)99U                                                                                                  /* [1279] ComConf_ComSignal_SIC_RR4L */
    ,(BswU2)99U                                                                                                  /* [1280] ComConf_ComSignal_SIC_RR5L */
    ,(BswU2)99U                                                                                                  /* [1281] ComConf_ComSignal_SIC_RRFK */
    ,(BswU2)99U                                                                                                  /* [1282] ComConf_ComSignal_SIC_RRRK */
    ,(BswU2)99U                                                                                                  /* [1283] ComConf_ComSignal_SIC_RRDK */
    ,(BswU2)99U                                                                                                  /* [1284] ComConf_ComSignal_SIC_RR4K */
    ,(BswU2)99U                                                                                                  /* [1285] ComConf_ComSignal_SIC_RR5K */
    ,(BswU2)99U                                                                                                  /* [1286] ComConf_ComSignal_AIC_LRC */
    ,(BswU2)99U                                                                                                  /* [1287] ComConf_ComSignal_AIC_LMRC */
    ,(BswU2)99U                                                                                                  /* [1288] ComConf_ComSignal_AIC_LFRC */
    ,(BswU2)99U                                                                                                  /* [1289] ComConf_ComSignal_AIC_LBRC */
    ,(BswU2)99U                                                                                                  /* [1290] ComConf_ComSignal_AIC_LRRC */
    ,(BswU2)99U                                                                                                  /* [1291] ComConf_ComSignal_SIC_LMST */
    ,(BswU2)99U                                                                                                  /* [1292] ComConf_ComSignal_SIC_LCST */
    ,(BswU2)99U                                                                                                  /* [1293] ComConf_ComSignal_SIC_LFFL */
    ,(BswU2)99U                                                                                                  /* [1294] ComConf_ComSignal_SIC_LFFP */
    ,(BswU2)99U                                                                                                  /* [1295] ComConf_ComSignal_SIC_LFRL */
    ,(BswU2)99U                                                                                                  /* [1296] ComConf_ComSignal_SIC_LFRP */
    ,(BswU2)99U                                                                                                  /* [1297] ComConf_ComSignal_SIC_LF5L */
    ,(BswU2)99U                                                                                                  /* [1298] ComConf_ComSignal_SIC_LFDL */
    ,(BswU2)99U                                                                                                  /* [1299] ComConf_ComSignal_SIC_LFDP */
    ,(BswU2)99U                                                                                                  /* [1300] ComConf_ComSignal_SIC_LF4L */
    ,(BswU2)99U                                                                                                  /* [1301] ComConf_ComSignal_SIC_LF4P */
    ,(BswU2)99U                                                                                                  /* [1302] ComConf_ComSignal_SIC_LF5P */
    ,(BswU2)99U                                                                                                  /* [1303] ComConf_ComSignal_SIC_LBFL */
    ,(BswU2)99U                                                                                                  /* [1304] ComConf_ComSignal_SIC_LBFP */
    ,(BswU2)99U                                                                                                  /* [1305] ComConf_ComSignal_SIC_LBRL */
    ,(BswU2)99U                                                                                                  /* [1306] ComConf_ComSignal_SIC_LBRP */
    ,(BswU2)99U                                                                                                  /* [1307] ComConf_ComSignal_SIC_LB5L */
    ,(BswU2)99U                                                                                                  /* [1308] ComConf_ComSignal_SIC_LBDL */
    ,(BswU2)99U                                                                                                  /* [1309] ComConf_ComSignal_SIC_LBDP */
    ,(BswU2)99U                                                                                                  /* [1310] ComConf_ComSignal_SIC_LB4L */
    ,(BswU2)99U                                                                                                  /* [1311] ComConf_ComSignal_SIC_LB4P */
    ,(BswU2)99U                                                                                                  /* [1312] ComConf_ComSignal_SIC_LB5P */
    ,(BswU2)99U                                                                                                  /* [1313] ComConf_ComSignal_SIC_LRFL */
    ,(BswU2)99U                                                                                                  /* [1314] ComConf_ComSignal_SIC_LRRL */
    ,(BswU2)99U                                                                                                  /* [1315] ComConf_ComSignal_SIC_LRDL */
    ,(BswU2)99U                                                                                                  /* [1316] ComConf_ComSignal_SIC_LR4L */
    ,(BswU2)99U                                                                                                  /* [1317] ComConf_ComSignal_SIC_LR5L */
    ,(BswU2)99U                                                                                                  /* [1318] ComConf_ComSignal_SIC_LRFK */
    ,(BswU2)99U                                                                                                  /* [1319] ComConf_ComSignal_SIC_LRRK */
    ,(BswU2)99U                                                                                                  /* [1320] ComConf_ComSignal_SIC_LRDK */
    ,(BswU2)99U                                                                                                  /* [1321] ComConf_ComSignal_SIC_LR4K */
    ,(BswU2)99U                                                                                                  /* [1322] ComConf_ComSignal_SIC_LR5K */
};

BswConst Bsw_Com_MsgInfoType bsw_com_stMsgInfoTbl[BSW_COM_MSG_NUM] = {
     { BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [0] MSG_CDC1S04_TXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_USE   )
      ,(BswU1)( BSW_COM_TXREQCONF_USE   | BSW_COM_TXCONF_USE   | BSW_COM_RXMSG_NOUSE | BSW_COM_PRESTORE_NOUSE | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [1] MSG_ABG1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [2] MSG_ABG1D51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [3] MSG_ABG1S09_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [4] MSG_ACN1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [5] MSG_ACN1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [6] MSG_ACN1S15_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [7] MSG_ACN1S25_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [8] MSG_ACN1S29_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [9] MSG_ADC1S27_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [10] MSG_ADC1S30_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 2000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [11] MSG_ADC1S31_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [12] MSG_ADU1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [13] MSG_ADU1S05_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [14] MSG_ADU1S06_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [15] MSG_BAT1E45_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [16] MSG_BAT1ED1_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [17] MSG_BAT1ED4_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [18] MSG_BAT1ED5_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [19] MSG_BAT1EDA_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [20] MSG_BAT1EDB_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [21] MSG_BAT1S08_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [22] MSG_BAT2ED2_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 5000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [23] MSG_BDB1F03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [24] MSG_BDB1S10_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [25] MSG_BDC1S22_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [26] MSG_BDC1S41_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [27] MSG_BDC1S81_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [28] MSG_BDC1SH8_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [29] MSG_BDF3S01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [30] MSG_BDF3S02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [31] MSG_BDR3S02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [32] MSG_CMB1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [33] MSG_CMB1S04_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [34] MSG_DCM1S08_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [35] MSG_DDM1S00_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [36] MSG_DDM1S09_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [37] MSG_DDM1S16_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [38] MSG_DDM1S35_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [39] MSG_DDM1SFG_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [40] MSG_DDM1SFH_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [41] MSG_DKY1S26_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [42] MSG_DS11S27_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [43] MSG_EBU1D01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [44] MSG_ECT1S93_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 2000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [45] MSG_EHV1E96_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  160U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [46] MSG_EHV1F02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [47] MSG_EHV1S23_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  160U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [48] MSG_EHV2G10_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  240U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [49] MSG_EHV2G20_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [50] MSG_EIM1S01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [51] MSG_ENG1C01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [52] MSG_ENG1C02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [53] MSG_ENG1D51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [54] MSG_ENG1D52_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [55] MSG_ENG1D53_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [56] MSG_ENG1D55_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [57] MSG_ENG1D56_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [58] MSG_ENG1D59_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [59] MSG_ENG1D60_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(15000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [60] MSG_ENG1S51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [61] MSG_EPS1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [62] MSG_FCM1C01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [63] MSG_FCM1S49_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [64] MSG_FCM1S76_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [65] MSG_FCM1S79_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [66] MSG_FCM1S90_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [67] MSG_FCM1S95_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [68] MSG_IDT1S07_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [69] MSG_IDT1S15_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [70] MSG_LRS1S01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [71] MSG_LRS1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [72] MSG_LRS1S04_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(   80U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [73] MSG_MGC1F13_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [74] MSG_PDC1G01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [75] MSG_PWC1S41_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [76] MSG_RCP1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [77] MSG_RRS1S01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [78] MSG_RRS1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [79] MSG_RRS1S04_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [80] MSG_RSE1G20_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [81] MSG_RSE1G24_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [82] MSG_RSE1G25_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [83] MSG_RSE1G26_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [84] MSG_RSE1G29_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [85] MSG_RSE1S02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [86] MSG_SCS1S10_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [87] MSG_VGR1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [88] MSG_VSC1D51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(   60U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [89] MSG_VSC1G13_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [90] MSG_WIP1S01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [91] MSG_ZN11S08_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [92] MSG_ZN11S32_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [93] MSG_ZN11S63_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [94] MSG_ZN11S64_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [95] MSG_ZN11S65_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [96] MSG_ZN11S66_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [97] MSG_ZN11S67_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [98] MSG_ZN11SF6_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [99] MSG_ZN11SF7_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
};

BswConst BswU4 bsw_com_u4SysStatTbl[BSW_COM_MSG_NUM][BSW_COM_SYSSTATTBLNUM] =
{
     {    /* [0] MSG_CDC1S04_TXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [1] MSG_ABG1D50_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [2] MSG_ABG1D51_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [3] MSG_ABG1S09_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [4] MSG_ACN1D50_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [5] MSG_ACN1S03_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [6] MSG_ACN1S15_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [7] MSG_ACN1S25_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [8] MSG_ACN1S29_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [9] MSG_ADC1S27_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [10] MSG_ADC1S30_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [11] MSG_ADC1S31_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [12] MSG_ADU1S03_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [13] MSG_ADU1S05_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [14] MSG_ADU1S06_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [15] MSG_BAT1E45_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [16] MSG_BAT1ED1_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [17] MSG_BAT1ED4_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [18] MSG_BAT1ED5_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [19] MSG_BAT1EDA_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [20] MSG_BAT1EDB_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [21] MSG_BAT1S08_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [22] MSG_BAT2ED2_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [23] MSG_BDB1F03_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [24] MSG_BDB1S10_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [25] MSG_BDC1S22_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [26] MSG_BDC1S41_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [27] MSG_BDC1S81_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [28] MSG_BDC1SH8_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [29] MSG_BDF3S01_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [30] MSG_BDF3S02_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [31] MSG_BDR3S02_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [32] MSG_CMB1S03_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [33] MSG_CMB1S04_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [34] MSG_DCM1S08_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [35] MSG_DDM1S00_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [36] MSG_DDM1S09_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [37] MSG_DDM1S16_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [38] MSG_DDM1S35_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [39] MSG_DDM1SFG_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [40] MSG_DDM1SFH_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [41] MSG_DKY1S26_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [42] MSG_DS11S27_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [43] MSG_EBU1D01_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [44] MSG_ECT1S93_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [45] MSG_EHV1E96_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [46] MSG_EHV1F02_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [47] MSG_EHV1S23_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [48] MSG_EHV2G10_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [49] MSG_EHV2G20_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [50] MSG_EIM1S01_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [51] MSG_ENG1C01_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [52] MSG_ENG1C02_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [53] MSG_ENG1D51_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [54] MSG_ENG1D52_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [55] MSG_ENG1D53_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [56] MSG_ENG1D55_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [57] MSG_ENG1D56_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [58] MSG_ENG1D59_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [59] MSG_ENG1D60_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [60] MSG_ENG1S51_RXCH0 */
          ( ComConf_SysStatusName_PON )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [61] MSG_EPS1D50_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [62] MSG_FCM1C01_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [63] MSG_FCM1S49_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [64] MSG_FCM1S76_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [65] MSG_FCM1S79_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [66] MSG_FCM1S90_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [67] MSG_FCM1S95_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [68] MSG_IDT1S07_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [69] MSG_IDT1S15_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [70] MSG_LRS1S01_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [71] MSG_LRS1S03_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [72] MSG_LRS1S04_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [73] MSG_MGC1F13_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [74] MSG_PDC1G01_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [75] MSG_PWC1S41_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [76] MSG_RCP1S03_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [77] MSG_RRS1S01_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [78] MSG_RRS1S03_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [79] MSG_RRS1S04_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [80] MSG_RSE1G20_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [81] MSG_RSE1G24_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [82] MSG_RSE1G25_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [83] MSG_RSE1G26_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [84] MSG_RSE1G29_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [85] MSG_RSE1S02_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [86] MSG_SCS1S10_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [87] MSG_VGR1D50_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [88] MSG_VSC1D51_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [89] MSG_VSC1G13_RXCH0 */
          ( ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [90] MSG_WIP1S01_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [91] MSG_ZN11S08_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [92] MSG_ZN11S32_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [93] MSG_ZN11S63_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [94] MSG_ZN11S64_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [95] MSG_ZN11S65_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [96] MSG_ZN11S66_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [97] MSG_ZN11S67_RXCH0 */
          ( ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [98] MSG_ZN11SF6_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [99] MSG_ZN11SF7_RXCH0 */
          ( ComConf_SysStatusName_PAR|ComConf_SysStatusName_RID|ComConf_SysStatusName_PON|ComConf_SysStatusName_POE|ComConf_SysStatusName_PAR_HV|ComConf_SysStatusName_PAR_HVHC|ComConf_SysStatusName_CHK )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
};

#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2TxDelayTbl[BSW_COM_TX_MSG_NUM] = {
     BSW_COM_u2MILSEC(0U)                                                                                        /* [0] MSG_CDC1S04_TXCH0 */
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */

BswConst Bsw_Com_MsgOffsetType bsw_com_u2MsgOffsTbl[BSW_COM_MSG_NUM] = {
     (BswU2)0U                                                                                                   /* [0] MSG_CDC1S04_TXCH0 */
    ,(BswU2)11U                                                                                                  /* [1] MSG_ABG1D50_RXCH0 */
    ,(BswU2)19U                                                                                                  /* [2] MSG_ABG1D51_RXCH0 */
    ,(BswU2)27U                                                                                                  /* [3] MSG_ABG1S09_RXCH0 */
    ,(BswU2)59U                                                                                                  /* [4] MSG_ACN1D50_RXCH0 */
    ,(BswU2)67U                                                                                                  /* [5] MSG_ACN1S03_RXCH0 */
    ,(BswU2)75U                                                                                                  /* [6] MSG_ACN1S15_RXCH0 */
    ,(BswU2)83U                                                                                                  /* [7] MSG_ACN1S25_RXCH0 */
    ,(BswU2)115U                                                                                                 /* [8] MSG_ACN1S29_RXCH0 */
    ,(BswU2)147U                                                                                                 /* [9] MSG_ADC1S27_RXCH0 */
    ,(BswU2)179U                                                                                                 /* [10] MSG_ADC1S30_RXCH0 */
    ,(BswU2)187U                                                                                                 /* [11] MSG_ADC1S31_RXCH0 */
    ,(BswU2)219U                                                                                                 /* [12] MSG_ADU1S03_RXCH0 */
    ,(BswU2)251U                                                                                                 /* [13] MSG_ADU1S05_RXCH0 */
    ,(BswU2)283U                                                                                                 /* [14] MSG_ADU1S06_RXCH0 */
    ,(BswU2)315U                                                                                                 /* [15] MSG_BAT1E45_RXCH0 */
    ,(BswU2)347U                                                                                                 /* [16] MSG_BAT1ED1_RXCH0 */
    ,(BswU2)379U                                                                                                 /* [17] MSG_BAT1ED4_RXCH0 */
    ,(BswU2)387U                                                                                                 /* [18] MSG_BAT1ED5_RXCH0 */
    ,(BswU2)395U                                                                                                 /* [19] MSG_BAT1EDA_RXCH0 */
    ,(BswU2)403U                                                                                                 /* [20] MSG_BAT1EDB_RXCH0 */
    ,(BswU2)435U                                                                                                 /* [21] MSG_BAT1S08_RXCH0 */
    ,(BswU2)443U                                                                                                 /* [22] MSG_BAT2ED2_RXCH0 */
    ,(BswU2)451U                                                                                                 /* [23] MSG_BDB1F03_RXCH0 */
    ,(BswU2)459U                                                                                                 /* [24] MSG_BDB1S10_RXCH0 */
    ,(BswU2)467U                                                                                                 /* [25] MSG_BDC1S22_RXCH0 */
    ,(BswU2)475U                                                                                                 /* [26] MSG_BDC1S41_RXCH0 */
    ,(BswU2)507U                                                                                                 /* [27] MSG_BDC1S81_RXCH0 */
    ,(BswU2)539U                                                                                                 /* [28] MSG_BDC1SH8_RXCH0 */
    ,(BswU2)547U                                                                                                 /* [29] MSG_BDF3S01_RXCH0 */
    ,(BswU2)579U                                                                                                 /* [30] MSG_BDF3S02_RXCH0 */
    ,(BswU2)611U                                                                                                 /* [31] MSG_BDR3S02_RXCH0 */
    ,(BswU2)643U                                                                                                 /* [32] MSG_CMB1S03_RXCH0 */
    ,(BswU2)651U                                                                                                 /* [33] MSG_CMB1S04_RXCH0 */
    ,(BswU2)659U                                                                                                 /* [34] MSG_DCM1S08_RXCH0 */
    ,(BswU2)667U                                                                                                 /* [35] MSG_DDM1S00_RXCH0 */
    ,(BswU2)675U                                                                                                 /* [36] MSG_DDM1S09_RXCH0 */
    ,(BswU2)683U                                                                                                 /* [37] MSG_DDM1S16_RXCH0 */
    ,(BswU2)715U                                                                                                 /* [38] MSG_DDM1S35_RXCH0 */
    ,(BswU2)747U                                                                                                 /* [39] MSG_DDM1SFG_RXCH0 */
    ,(BswU2)779U                                                                                                 /* [40] MSG_DDM1SFH_RXCH0 */
    ,(BswU2)811U                                                                                                 /* [41] MSG_DKY1S26_RXCH0 */
    ,(BswU2)819U                                                                                                 /* [42] MSG_DS11S27_RXCH0 */
    ,(BswU2)827U                                                                                                 /* [43] MSG_EBU1D01_RXCH0 */
    ,(BswU2)859U                                                                                                 /* [44] MSG_ECT1S93_RXCH0 */
    ,(BswU2)867U                                                                                                 /* [45] MSG_EHV1E96_RXCH0 */
    ,(BswU2)899U                                                                                                 /* [46] MSG_EHV1F02_RXCH0 */
    ,(BswU2)907U                                                                                                 /* [47] MSG_EHV1S23_RXCH0 */
    ,(BswU2)915U                                                                                                 /* [48] MSG_EHV2G10_RXCH0 */
    ,(BswU2)947U                                                                                                 /* [49] MSG_EHV2G20_RXCH0 */
    ,(BswU2)979U                                                                                                 /* [50] MSG_EIM1S01_RXCH0 */
    ,(BswU2)987U                                                                                                 /* [51] MSG_ENG1C01_RXCH0 */
    ,(BswU2)995U                                                                                                 /* [52] MSG_ENG1C02_RXCH0 */
    ,(BswU2)1003U                                                                                                /* [53] MSG_ENG1D51_RXCH0 */
    ,(BswU2)1011U                                                                                                /* [54] MSG_ENG1D52_RXCH0 */
    ,(BswU2)1019U                                                                                                /* [55] MSG_ENG1D53_RXCH0 */
    ,(BswU2)1027U                                                                                                /* [56] MSG_ENG1D55_RXCH0 */
    ,(BswU2)1035U                                                                                                /* [57] MSG_ENG1D56_RXCH0 */
    ,(BswU2)1043U                                                                                                /* [58] MSG_ENG1D59_RXCH0 */
    ,(BswU2)1051U                                                                                                /* [59] MSG_ENG1D60_RXCH0 */
    ,(BswU2)1059U                                                                                                /* [60] MSG_ENG1S51_RXCH0 */
    ,(BswU2)1091U                                                                                                /* [61] MSG_EPS1D50_RXCH0 */
    ,(BswU2)1099U                                                                                                /* [62] MSG_FCM1C01_RXCH0 */
    ,(BswU2)1107U                                                                                                /* [63] MSG_FCM1S49_RXCH0 */
    ,(BswU2)1139U                                                                                                /* [64] MSG_FCM1S76_RXCH0 */
    ,(BswU2)1147U                                                                                                /* [65] MSG_FCM1S79_RXCH0 */
    ,(BswU2)1155U                                                                                                /* [66] MSG_FCM1S90_RXCH0 */
    ,(BswU2)1187U                                                                                                /* [67] MSG_FCM1S95_RXCH0 */
    ,(BswU2)1251U                                                                                                /* [68] MSG_IDT1S07_RXCH0 */
    ,(BswU2)1259U                                                                                                /* [69] MSG_IDT1S15_RXCH0 */
    ,(BswU2)1267U                                                                                                /* [70] MSG_LRS1S01_RXCH0 */
    ,(BswU2)1275U                                                                                                /* [71] MSG_LRS1S03_RXCH0 */
    ,(BswU2)1283U                                                                                                /* [72] MSG_LRS1S04_RXCH0 */
    ,(BswU2)1291U                                                                                                /* [73] MSG_MGC1F13_RXCH0 */
    ,(BswU2)1323U                                                                                                /* [74] MSG_PDC1G01_RXCH0 */
    ,(BswU2)1331U                                                                                                /* [75] MSG_PWC1S41_RXCH0 */
    ,(BswU2)1363U                                                                                                /* [76] MSG_RCP1S03_RXCH0 */
    ,(BswU2)1371U                                                                                                /* [77] MSG_RRS1S01_RXCH0 */
    ,(BswU2)1379U                                                                                                /* [78] MSG_RRS1S03_RXCH0 */
    ,(BswU2)1387U                                                                                                /* [79] MSG_RRS1S04_RXCH0 */
    ,(BswU2)1395U                                                                                                /* [80] MSG_RSE1G20_RXCH0 */
    ,(BswU2)1403U                                                                                                /* [81] MSG_RSE1G24_RXCH0 */
    ,(BswU2)1411U                                                                                                /* [82] MSG_RSE1G25_RXCH0 */
    ,(BswU2)1419U                                                                                                /* [83] MSG_RSE1G26_RXCH0 */
    ,(BswU2)1427U                                                                                                /* [84] MSG_RSE1G29_RXCH0 */
    ,(BswU2)1435U                                                                                                /* [85] MSG_RSE1S02_RXCH0 */
    ,(BswU2)1443U                                                                                                /* [86] MSG_SCS1S10_RXCH0 */
    ,(BswU2)1475U                                                                                                /* [87] MSG_VGR1D50_RXCH0 */
    ,(BswU2)1507U                                                                                                /* [88] MSG_VSC1D51_RXCH0 */
    ,(BswU2)1539U                                                                                                /* [89] MSG_VSC1G13_RXCH0 */
    ,(BswU2)1571U                                                                                                /* [90] MSG_WIP1S01_RXCH0 */
    ,(BswU2)1579U                                                                                                /* [91] MSG_ZN11S08_RXCH0 */
    ,(BswU2)1611U                                                                                                /* [92] MSG_ZN11S32_RXCH0 */
    ,(BswU2)1643U                                                                                                /* [93] MSG_ZN11S63_RXCH0 */
    ,(BswU2)1675U                                                                                                /* [94] MSG_ZN11S64_RXCH0 */
    ,(BswU2)1707U                                                                                                /* [95] MSG_ZN11S65_RXCH0 */
    ,(BswU2)1739U                                                                                                /* [96] MSG_ZN11S66_RXCH0 */
    ,(BswU2)1771U                                                                                                /* [97] MSG_ZN11S67_RXCH0 */
    ,(BswU2)1803U                                                                                                /* [98] MSG_ZN11SF6_RXCH0 */
    ,(BswU2)1835U                                                                                                /* [99] MSG_ZN11SF7_RXCH0 */
};

#if( BSW_COM_CFG_METADATA_USE == BSW_USE )
BswConst BswU1 bsw_com_u1MetaDataSizeTbl[BSW_COM_MSG_NUM] = {
};
#endif /* BSW_COM_CFG_METADATA_USE == BSW_USE */

BswConst Bsw_Com_NetInfoType bsw_com_stNetInfoTxMsgTbl[BSW_COM_NETWORK_NUM] = {
     { (BswU2)0U,   (BswU2)1U   }                                                                                /* [0] CH0 CDC_VCAN_BUS */
};

BswConst Bsw_Com_NetInfoType bsw_com_stNetInfoRxMsgTbl[BSW_COM_NETWORK_NUM] = {
     { (BswU2)1U,   (BswU2)99U  }                                                                                /* [0] CH0 CDC_VCAN_BUS */
};

#if (BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE)
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2DelayTbl[BSW_COM_TX_MSG_NUM] = {
     BSW_COM_u2MILSEC_RUP(1U)                                                                                    /* [0] MSG_CDC1S04_TXCH0 */
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */
#endif /* BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE */

#if ( (BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE) && (BSW_COM_CFG_TX_DLYSW_USE == BSW_USE) )
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2PrdDelayTbl[BSW_COM_TX_MSG_NUM] = {
     BSW_COM_u2MILSEC_RUP(1U)                                                                                    /* [0] MSG_CDC1S04_TXCH0 */
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */
#endif /* (BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE) && (BSW_COM_CFG_TX_DLYSW_USE == BSW_USE) */

#if (BSW_COM_CFG_TX_TIMEOUT_USE == BSW_USE)
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2TxTimeoutTbl[BSW_COM_TX_MSG_NUM] = {
     BSW_COM_u2MILSEC_RUP(420U)                                                                                  /* [0] MSG_CDC1S04_TXCH0 */
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */
#if ( (BSW_COM_TX_MSG_NUM != 0U) && (BSW_COM_FIRSTTXTIMEOUT_USE == BSW_USE) )
BswConst Bsw_Com_TickTimeType bsw_com_u2FirstTxTimeoutTbl[BSW_COM_TX_MSG_NUM] = {
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) && (BSW_COM_FIRSTTXTIMEOUT_USE == BSW_USE) */
#endif /* BSW_COM_CFG_TX_TIMEOUT_USE == BSW_USE */

#if (BSW_COM_ALIVECOUNTER_PTN2_USE == BSW_USE)
#if (BSW_COM_TX_ALVCNTMSG_NUM != 0U)
BswConst Bsw_Com_AliveInfoType bsw_com_AlvCnt2TxInfo[BSW_COM_TX_MSG_NUM] =
{
};
#endif /* (BSW_COM_TX_ALVCNTMSG_NUM != 0U) */
#if (BSW_COM_RX_ALVCNTMSG_NUM != 0U)
BswConst Bsw_Com_AliveInfoType bsw_com_AlvCnt2RxInfo[BSW_COM_RX_MSG_NUM] =
{
};
#endif /* (BSW_COM_RX_ALVCNTMSG_NUM != 0U) */
#endif /* (BSW_COM_CFG_CHx_ALVCNTR_PTN == BSW_COM_ALIVECOUNTER_PTN2) */

#if (BSW_COM_ALIVECOUNTER_PTN3_USE == BSW_USE)
#if (BSW_COM_TX_ALVCNT3MSG_NUM != 0U)
BswConst Bsw_Com_AlvCnt3TxInfoType bsw_com_AlvCnt3TxInfo[BSW_COM_TX_MSG_NUM] =
{
};
#endif /* (BSW_COM_TX_ALVCNT3MSG_NUM != 0U) */
#if (BSW_COM_RX_ALVCNT3MSG_NUM != 0U)
BswConst Bsw_Com_AlvCnt3RxInfoType bsw_com_AlvCnt3RxInfo[BSW_COM_RX_MSG_NUM] =
{
};
#endif /* (BSW_COM_RX_ALVCNT3MSG_NUM != 0U) */
#endif /* (BSW_COM_CFG_CHx_ALVCNTR_PTN == BSW_COM_ALIVECOUNTER_PTN3) */

#if (BSW_COM_RX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2PwonMsk[BSW_COM_RX_MSG_NUM] = {

     BSW_COM_u2MILSEC(3000U)                                                    /* [0] MSG_ABG1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [1] MSG_ABG1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [2] MSG_ABG1S09_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [3] MSG_ACN1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [4] MSG_ACN1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [5] MSG_ACN1S15_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [6] MSG_ACN1S25_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [7] MSG_ACN1S29_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [8] MSG_ADC1S27_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [9] MSG_ADC1S30_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [10] MSG_ADC1S31_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [11] MSG_ADU1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [12] MSG_ADU1S05_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [13] MSG_ADU1S06_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [14] MSG_BAT1E45_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [15] MSG_BAT1ED1_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [16] MSG_BAT1ED4_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [17] MSG_BAT1ED5_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [18] MSG_BAT1EDA_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [19] MSG_BAT1EDB_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [20] MSG_BAT1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [21] MSG_BAT2ED2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [22] MSG_BDB1F03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [23] MSG_BDB1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [24] MSG_BDC1S22_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [25] MSG_BDC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [26] MSG_BDC1S81_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [27] MSG_BDC1SH8_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [28] MSG_BDF3S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [29] MSG_BDF3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [30] MSG_BDR3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [31] MSG_CMB1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [32] MSG_CMB1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [33] MSG_DCM1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [34] MSG_DDM1S00_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [35] MSG_DDM1S09_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [36] MSG_DDM1S16_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [37] MSG_DDM1S35_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [38] MSG_DDM1SFG_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [39] MSG_DDM1SFH_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [40] MSG_DKY1S26_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [41] MSG_DS11S27_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [42] MSG_EBU1D01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [43] MSG_ECT1S93_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [44] MSG_EHV1E96_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [45] MSG_EHV1F02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [46] MSG_EHV1S23_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [47] MSG_EHV2G10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [48] MSG_EHV2G20_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [49] MSG_EIM1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [50] MSG_ENG1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [51] MSG_ENG1C02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [52] MSG_ENG1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [53] MSG_ENG1D52_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [54] MSG_ENG1D53_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [55] MSG_ENG1D55_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [56] MSG_ENG1D56_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [57] MSG_ENG1D59_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [58] MSG_ENG1D60_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [59] MSG_ENG1S51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [60] MSG_EPS1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [61] MSG_FCM1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [62] MSG_FCM1S49_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [63] MSG_FCM1S76_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [64] MSG_FCM1S79_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [65] MSG_FCM1S90_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [66] MSG_FCM1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [67] MSG_IDT1S07_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [68] MSG_IDT1S15_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [69] MSG_LRS1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [70] MSG_LRS1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [71] MSG_LRS1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [72] MSG_MGC1F13_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [73] MSG_PDC1G01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [74] MSG_PWC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [75] MSG_RCP1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [76] MSG_RRS1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [77] MSG_RRS1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [78] MSG_RRS1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [79] MSG_RSE1G20_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [80] MSG_RSE1G24_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [81] MSG_RSE1G25_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [82] MSG_RSE1G26_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [83] MSG_RSE1G29_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [84] MSG_RSE1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [85] MSG_SCS1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [86] MSG_VGR1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [87] MSG_VSC1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [88] MSG_VSC1G13_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [89] MSG_WIP1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [90] MSG_ZN11S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [91] MSG_ZN11S32_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [92] MSG_ZN11S63_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [93] MSG_ZN11S64_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [94] MSG_ZN11S65_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [95] MSG_ZN11S66_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [96] MSG_ZN11S67_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [97] MSG_ZN11SF6_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [98] MSG_ZN11SF7_RXCH0 */
};

BswConst Bsw_Com_TickTimeType bsw_com_u2WakeupMsk[BSW_COM_RX_MSG_NUM] = {

     BSW_COM_u2MILSEC(3000U)                                                    /* [0] MSG_ABG1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [1] MSG_ABG1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [2] MSG_ABG1S09_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [3] MSG_ACN1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [4] MSG_ACN1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [5] MSG_ACN1S15_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [6] MSG_ACN1S25_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [7] MSG_ACN1S29_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [8] MSG_ADC1S27_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [9] MSG_ADC1S30_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [10] MSG_ADC1S31_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [11] MSG_ADU1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [12] MSG_ADU1S05_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [13] MSG_ADU1S06_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [14] MSG_BAT1E45_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [15] MSG_BAT1ED1_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [16] MSG_BAT1ED4_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [17] MSG_BAT1ED5_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [18] MSG_BAT1EDA_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [19] MSG_BAT1EDB_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [20] MSG_BAT1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [21] MSG_BAT2ED2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [22] MSG_BDB1F03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [23] MSG_BDB1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [24] MSG_BDC1S22_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [25] MSG_BDC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [26] MSG_BDC1S81_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [27] MSG_BDC1SH8_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [28] MSG_BDF3S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [29] MSG_BDF3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [30] MSG_BDR3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [31] MSG_CMB1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [32] MSG_CMB1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [33] MSG_DCM1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [34] MSG_DDM1S00_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [35] MSG_DDM1S09_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [36] MSG_DDM1S16_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [37] MSG_DDM1S35_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [38] MSG_DDM1SFG_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [39] MSG_DDM1SFH_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [40] MSG_DKY1S26_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [41] MSG_DS11S27_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [42] MSG_EBU1D01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [43] MSG_ECT1S93_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [44] MSG_EHV1E96_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [45] MSG_EHV1F02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [46] MSG_EHV1S23_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [47] MSG_EHV2G10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [48] MSG_EHV2G20_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [49] MSG_EIM1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [50] MSG_ENG1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [51] MSG_ENG1C02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [52] MSG_ENG1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [53] MSG_ENG1D52_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [54] MSG_ENG1D53_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [55] MSG_ENG1D55_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [56] MSG_ENG1D56_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [57] MSG_ENG1D59_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [58] MSG_ENG1D60_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [59] MSG_ENG1S51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [60] MSG_EPS1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [61] MSG_FCM1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [62] MSG_FCM1S49_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [63] MSG_FCM1S76_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [64] MSG_FCM1S79_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [65] MSG_FCM1S90_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [66] MSG_FCM1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [67] MSG_IDT1S07_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [68] MSG_IDT1S15_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [69] MSG_LRS1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [70] MSG_LRS1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [71] MSG_LRS1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [72] MSG_MGC1F13_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [73] MSG_PDC1G01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [74] MSG_PWC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [75] MSG_RCP1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [76] MSG_RRS1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [77] MSG_RRS1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [78] MSG_RRS1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [79] MSG_RSE1G20_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [80] MSG_RSE1G24_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [81] MSG_RSE1G25_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [82] MSG_RSE1G26_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [83] MSG_RSE1G29_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [84] MSG_RSE1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [85] MSG_SCS1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [86] MSG_VGR1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [87] MSG_VSC1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [88] MSG_VSC1G13_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [89] MSG_WIP1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [90] MSG_ZN11S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [91] MSG_ZN11S32_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [92] MSG_ZN11S63_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [93] MSG_ZN11S64_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [94] MSG_ZN11S65_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [95] MSG_ZN11S66_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [96] MSG_ZN11S67_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [97] MSG_ZN11SF6_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [98] MSG_ZN11SF7_RXCH0 */
};
#endif /* (BSW_COM_RX_MSG_NUM != 0U) */

/* Send N Times Information (MessageID, Interval, Send-Times, Extend) */
#if (BSW_COM_CFG_SENDNTIMES_MSG_NUM != 0U)
BswConst Bsw_Com_NTimesInfoType bsw_com_tx_stSendNTimesInfo[BSW_COM_CFG_SENDNTIMES_MSG_NUM] =
{
};
#endif /* (BSW_COM_CFG_SENDNTIMES_MSG_NUM != 0U) */

/* Change Period Information (MessageID, Changing Interval, Send-Times, Off ImmSend, TimerRetrigger, Extend) */
#if (BSW_COM_CFG_CHGPERIOD_MSG_NUM != 0U)
BswConst Bsw_Com_ChgPrdInfoType bsw_com_tx_stChgPeriodIpduInfo[BSW_COM_CFG_CHGPERIOD_MSG_NUM] =
{
};
#endif /* (BSW_COM_CFG_CHGPERIOD_MSG_NUM != 0U) */

#if (BSW_COM_CFG_BACKUPPDU_USE == BSW_USE)
BswConst PduIdType bsw_com_data_u2BackupPduId[BSW_COM_CFG_BACKUPPDU_NUM] =
{
};
#endif /* (BSW_COM_CFG_BACKUPPDU_USE == BSW_USE) */

#if ( BSW_COM_FUNC_PNCIPDU == BSW_USE )
BswConst BswU4 bsw_com_u4PncStatTbl[BSW_COM_MSG_NUM][BSW_COM_PNC_REQNUM] = 
{
};

#if (BSW_COM_RX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2PnconMsk[BSW_COM_RX_MSG_NUM] = {
};
#endif /* (BSW_COM_RX_MSG_NUM != 0U) */
#endif /* ( BSW_COM_FUNC_PNCIPDU == BSW_USE ) */

#if (BSW_COM_TX_DISTIMBYMSG == BSW_USE)
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2SendStartPwTbl[BSW_COM_TX_MSG_NUM] = {
     BSW_COM_u2MILSEC(0U)                                                                                        /* [0] MSG_CDC1S04_TXCH0 */
};

BswConst Bsw_Com_TickTimeType bsw_com_u2DisableSendTbl[BSW_COM_TX_MSG_NUM] = {
     BSW_COM_u2MILSEC(0U)                                                                                        /* [0] MSG_CDC1S04_TXCH0 */
};

BswConst Bsw_Com_TickTimeType bsw_com_u2EnablePeriodicTbl[BSW_COM_TX_MSG_NUM] = {
     BSW_COM_u2MILSEC(0U)                                                                                        /* [0] MSG_CDC1S04_TXCH0 */
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */
#endif /* BSW_COM_TX_DISTIMBYMSG == BSW_USE */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (BSW_BSWM_CS_FUNC_COM == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/10/16                                             */
/*  v1-1-0          :2018/12/17                                             */
/*  v1-2-0          :2019/12/06                                             */
/*  v2-0-0          :2021/12/09                                             */
/*  v2-1-0          :2022/06/17                                             */
/*  v2-2-0          :2023/05/23                                             */
/*  v3-0-0          :2024/11/11                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
