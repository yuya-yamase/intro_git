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
     (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [0] MSG_ABG1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [1] MSG_ABG1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [2] MSG_ABG1S09_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [3] MSG_ACN1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [4] MSG_ACN1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [5] MSG_ACN1S15_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [6] MSG_ACN1S25_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [7] MSG_ACN1S29_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [8] MSG_ADC1S27_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [9] MSG_ADC1S30_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [10] MSG_ADC1S31_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [11] MSG_ADU1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [12] MSG_ADU1S05_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [13] MSG_ADU1S06_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [14] MSG_AVN1S95_RXCH0 */
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
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [25] MSG_BDC1S41_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [26] MSG_BDC1S81_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [27] MSG_BDC1S82_RXCH0 */
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
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [32] MSG_CDC1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [33] MSG_CMB1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [34] MSG_CMB1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [35] MSG_DCM1S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [36] MSG_DDM1S00_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [37] MSG_DDM1S09_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [38] MSG_DDM1S16_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [39] MSG_DDM1S35_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [40] MSG_DDM1SFG_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [41] MSG_DDM1SFH_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [42] MSG_DKY1S26_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [43] MSG_DS11S27_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [44] MSG_EBU1D01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [45] MSG_ECT1S93_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [46] MSG_EHV1E96_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [47] MSG_EHV1F02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [48] MSG_EHV1S23_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [49] MSG_EHV2G10_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [50] MSG_EHV2G20_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [51] MSG_EIM1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [52] MSG_ENG1C01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [53] MSG_ENG1C02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [54] MSG_ENG1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [55] MSG_ENG1D52_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [56] MSG_ENG1D53_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [57] MSG_ENG1D55_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [58] MSG_ENG1D56_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [59] MSG_ENG1D59_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [60] MSG_ENG1D60_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [61] MSG_ENG1S51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [62] MSG_EPS1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [63] MSG_FCM1C01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [64] MSG_FCM1S49_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [65] MSG_FCM1S76_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [66] MSG_FCM1S79_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [67] MSG_FCM1S90_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [68] MSG_FCM1S95_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [69] MSG_IDT1S07_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [70] MSG_IDT1S15_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [71] MSG_MET1S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [72] MSG_MGC1F13_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [73] MSG_PDC1G01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [74] MSG_PWC1S41_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [75] MSG_RCP1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [76] MSG_RSE1G20_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [77] MSG_RSE1G24_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [78] MSG_RSE1G25_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [79] MSG_RSE1G26_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [80] MSG_RSE1G29_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [81] MSG_RSE1S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [82] MSG_SCS1S10_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [83] MSG_VGR1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [84] MSG_VSC1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [85] MSG_VSC1G13_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [86] MSG_WIP1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [87] MSG_ZN11S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [88] MSG_ZN11S32_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [89] MSG_ZN11S63_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [90] MSG_ZN11S64_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [91] MSG_ZN11S65_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [92] MSG_ZN11S66_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [93] MSG_ZN11S67_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [94] MSG_ZN11SF6_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [95] MSG_ZN11SF7_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U                                                                        /* Padding Area */
};

#if (BSW_COM_CFG_FAILSAFE_SIZE != 0U)
BswConst BswU1 bsw_com_data_u1MsgBufFail[BSW_COM_FAILSAFE_SIZE] = {
};
#endif /* (BSW_COM_CFG_FAILSAFE_SIZE != 0U) */

#if (BSW_COM_CFG_FAILSAFE_SIZE != 0U)
BswConst BswU1 bsw_com_data_u1FailMskTbl[BSW_COM_FAILSAFE_SIZE] = {
};
#endif /* (BSW_COM_CFG_FAILSAFE_SIZE != 0U) */

BswConst Bsw_Com_DataInfoType bsw_com_stDataInfoTbl[BSW_COM_HANDLE_NUM] = {
     BSW_COM_u1EVCOND_NONE                                                                                       /* [0] ComConf_ComSignal_DRABG01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1] ComConf_ComSignal_DRABG02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [2] ComConf_ComSignal_DRABG03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [3] ComConf_ComSignal_DRABG04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [4] ComConf_ComSignal_DRABG05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [5] ComConf_ComSignal_DRABG06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [6] ComConf_ComSignal_DRABG07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [7] ComConf_ComSignal_DRABG08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [8] ComConf_ComSignal_DRABG09 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [9] ComConf_ComSignal_DRABG10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [10] ComConf_ComSignal_DRABG11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [11] ComConf_ComSignal_DRABG12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [12] ComConf_ComSignal_DRABG13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [13] ComConf_ComSignal_DRABG14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [14] ComConf_ComSignal_DRABG15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [15] ComConf_ComSignal_DRABG16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [16] ComConf_ComSignal_D00024 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [17] ComConf_ComSignal_D00025 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [18] ComConf_ComSignal_D00026 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [19] ComConf_ComSignal_D00027 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [20] ComConf_ComSignal_FLGXMAX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [21] ComConf_ComSignal_D00028 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [22] ComConf_ComSignal_D00029 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [23] ComConf_ComSignal_D00030 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [24] ComConf_ComSignal_FLVNMAX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [25] ComConf_ComSignal_FRGMAX_L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [26] ComConf_ComSignal_FRGMAX_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [27] ComConf_ComSignal_D00031 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [28] ComConf_ComSignal_D00032 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [29] ComConf_ComSignal_D00033 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [30] ComConf_ComSignal_D00034 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [31] ComConf_ComSignal_D00035 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [32] ComConf_ComSignal_D00036 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [33] ComConf_ComSignal_PT_ON */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [34] ComConf_ComSignal_FRAB_ON */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [35] ComConf_ComSignal_D00037 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [36] ComConf_ComSignal_D00038 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [37] ComConf_ComSignal_D00039 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [38] ComConf_ComSignal_D00040 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [39] ComConf_ComSignal_D00041 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [40] ComConf_ComSignal_D00042 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [41] ComConf_ComSignal_D00043 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [42] ComConf_ComSignal_D00044 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [43] ComConf_ComSignal_D00045 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [44] ComConf_ComSignal_D00046 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [45] ComConf_ComSignal_DRACN01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [46] ComConf_ComSignal_DRACN02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [47] ComConf_ComSignal_DRACN03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [48] ComConf_ComSignal_DRACN04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [49] ComConf_ComSignal_DRACN05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [50] ComConf_ComSignal_DRACN06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [51] ComConf_ComSignal_DRACN07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [52] ComConf_ComSignal_DRACN08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [53] ComConf_ComSignal_D00076 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [54] ComConf_ComSignal_D00077 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [55] ComConf_ComSignal_D00078 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [56] ComConf_ComSignal_O_STG_F */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [57] ComConf_ComSignal_D00079 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [58] ComConf_ComSignal_D00080 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [59] ComConf_ComSignal_AC_CDSP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [60] ComConf_ComSignal_D00081 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [61] ComConf_ComSignal_D00093 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [62] ComConf_ComSignal_TRTEMP_P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [63] ComConf_ComSignal_I_BLWF_P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [64] ComConf_ComSignal_D00094 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [65] ComConf_ComSignal_D00095 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [66] ComConf_ComSignal_D00096 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [67] ComConf_ComSignal_D00097 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [68] ComConf_ComSignal_D00110 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [69] ComConf_ComSignal_D00111 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [70] ComConf_ComSignal_D00112 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [71] ComConf_ComSignal_D00113 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [72] ComConf_ComSignal_D00114 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [73] ComConf_ComSignal_D00115 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [74] ComConf_ComSignal_D00116 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [75] ComConf_ComSignal_D00117 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [76] ComConf_ComSignal_D00118 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [77] ComConf_ComSignal_D00119 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [78] ComConf_ComSignal_D00120 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [79] ComConf_ComSignal_D00121 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [80] ComConf_ComSignal_D00122 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [81] ComConf_ComSignal_D00123 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [82] ComConf_ComSignal_D00124 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [83] ComConf_ComSignal_D00125 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [84] ComConf_ComSignal_D00126 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [85] ComConf_ComSignal_HQ_COMP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [86] ComConf_ComSignal_D00137 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [87] ComConf_ComSignal_D00138 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [88] ComConf_ComSignal_D00139 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [89] ComConf_ComSignal_D00140 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [90] ComConf_ComSignal_R_SHHTFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [91] ComConf_ComSignal_D00141 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [92] ComConf_ComSignal_R_SHHTFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [93] ComConf_ComSignal_D00142 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [94] ComConf_ComSignal_D00143 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [95] ComConf_ComSignal_D00144 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [96] ComConf_ComSignal_D00145 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [97] ComConf_ComSignal_D00146 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [98] ComConf_ComSignal_D00147 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [99] ComConf_ComSignal_D00148 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [100] ComConf_ComSignal_D00149 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [101] ComConf_ComSignal_RSVFLDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [102] ComConf_ComSignal_D00150 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [103] ComConf_ComSignal_RSVFRDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [104] ComConf_ComSignal_D00151 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [105] ComConf_ComSignal_R_SHHTRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [106] ComConf_ComSignal_D00152 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [107] ComConf_ComSignal_R_SHHTRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [108] ComConf_ComSignal_D00153 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [109] ComConf_ComSignal_D00154 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [110] ComConf_ComSignal_D00155 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [111] ComConf_ComSignal_D00156 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [112] ComConf_ComSignal_D00157 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [113] ComConf_ComSignal_D00158 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [114] ComConf_ComSignal_D00159 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [115] ComConf_ComSignal_D00160 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [116] ComConf_ComSignal_D00161 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [117] ComConf_ComSignal_D00162 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [118] ComConf_ComSignal_D00163 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [119] ComConf_ComSignal_RSVRLDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [120] ComConf_ComSignal_D00164 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [121] ComConf_ComSignal_RSVRRDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [122] ComConf_ComSignal_D00165 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [123] ComConf_ComSignal_R_RDHRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [124] ComConf_ComSignal_D00166 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [125] ComConf_ComSignal_R_RDHRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [126] ComConf_ComSignal_D00167 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [127] ComConf_ComSignal_R_RDHFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [128] ComConf_ComSignal_D00168 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [129] ComConf_ComSignal_R_RDHFD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [130] ComConf_ComSignal_D00169 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [131] ComConf_ComSignal_D00170 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [132] ComConf_ComSignal_D00171 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [133] ComConf_ComSignal_D00172 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [134] ComConf_ComSignal_WS_VD_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [135] ComConf_ComSignal_WS_FTG_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [136] ComConf_ComSignal_WS_ABH_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [137] ComConf_ComSignal_WS_APO_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [138] ComConf_ComSignal_ETHWU_12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [139] ComConf_ComSignal_D00219 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [140] ComConf_ComSignal_APPMD2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [141] ComConf_ComSignal_D00220 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [142] ComConf_ComSignal_D00221 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [143] ComConf_ComSignal_D00222 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [144] ComConf_ComSignal_D00223 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [145] ComConf_ComSignal_FV1C0_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [146] ComConf_ComSignal_KZK1C0_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [147] ComConf_ComSignal_ACCMAPP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [148] ComConf_ComSignal_ACCMMOD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [149] ComConf_ComSignal_ACCMDST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [150] ComConf_ComSignal_ACCMPHS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [151] ComConf_ComSignal_ACCMSGN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [152] ComConf_ComSignal_ACCMRCG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [153] ComConf_ComSignal_ACCMARB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [154] ComConf_ComSignal_LDASTATL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [155] ComConf_ComSignal_LDASTATR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [156] ComConf_ComSignal_LDARSN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [157] ComConf_ComSignal_FCMINTMP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [158] ComConf_ComSignal_LDARCGL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [159] ComConf_ComSignal_LDARCGR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [160] ComConf_ComSignal_SWSSTAT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [161] ComConf_ComSignal_V_IDACCL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [162] ComConf_ComSignal_EJDEVPRD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [163] ComConf_ComSignal_EJLDACP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [164] ComConf_ComSignal_V_IDANOA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [165] ComConf_ComSignal_V_IDARGL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [166] ComConf_ComSignal_PV_AREA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [167] ComConf_ComSignal_DM_PVMVW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [168] ComConf_ComSignal_DM_PVMCS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [169] ComConf_ComSignal_ERMCNTST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [170] ComConf_ComSignal_GAE_H_R3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [171] ComConf_ComSignal_FRDHTR_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [172] ComConf_ComSignal_SDIRT_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [173] ComConf_ComSignal_GAE_V_R1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [174] ComConf_ComSignal_DRTCNT_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [175] ComConf_ComSignal_GAERR1_V */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [176] ComConf_ComSignal_GAEVAL_H */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [177] ComConf_ComSignal_GAERR3_H */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [178] ComConf_ComSignal_DTSSSTR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [179] ComConf_ComSignal_DTSSLTID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [180] ComConf_ComSignal_MDSYNC00 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [181] ComConf_ComSignal_OTA2RSLT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [182] ComConf_ComSignal_OTA3RSLT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [183] ComConf_ComSignal_OTADRSLT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [184] ComConf_ComSignal_SRVC_STT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [185] ComConf_ComSignal_OTA2CNCL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [186] ComConf_ComSignal_OTA3CNCL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [187] ComConf_ComSignal_OTADCNCL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [188] ComConf_ComSignal_CUR_DRV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [189] ComConf_ComSignal_SRVC_PC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [190] ComConf_ComSignal_SRVC_VC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [191] ComConf_ComSignal_SRVC_AC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [192] ComConf_ComSignal_OTAPPCTL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [193] ComConf_ComSignal_CW_MD_SW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [194] ComConf_ComSignal_VNHLDRQ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [195] ComConf_ComSignal_TRNCASW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [196] ComConf_ComSignal_TRNSD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [197] ComConf_ComSignal_TRNFBPD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [198] ComConf_ComSignal_OTACDRLT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [199] ComConf_ComSignal_OTACHGEX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [200] ComConf_ComSignal_OTAACTTP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [201] ComConf_ComSignal_OTAACTPH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [202] ComConf_ComSignal_OTASWACT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [203] ComConf_ComSignal_OTASTAT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [204] ComConf_ComSignal_BIB_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [205] ComConf_ComSignal_VCELMAXG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [206] ComConf_ComSignal_VCELMING */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [207] ComConf_ComSignal_RAHRMAXG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [208] ComConf_ComSignal_RAHRMING */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [209] ComConf_ComSignal_TC_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [210] ComConf_ComSignal_TBMAX_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [211] ComConf_ComSignal_TBMIN_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [212] ComConf_ComSignal_D00809 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [213] ComConf_ComSignal_D00810 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [214] ComConf_ComSignal_D00811 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [215] ComConf_ComSignal_D_IB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [216] ComConf_ComSignal_D_VB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [217] ComConf_ComSignal_D_VBMAX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [218] ComConf_ComSignal_D_VBMIN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [219] ComConf_ComSignal_D_VMAXN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [220] ComConf_ComSignal_D_VMINN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [221] ComConf_ComSignal_D_TBMAX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [222] ComConf_ComSignal_D_TBMIN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [223] ComConf_ComSignal_D_TBMAXN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [224] ComConf_ComSignal_D_TBMINN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [225] ComConf_ComSignal_D_SOC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [226] ComConf_ComSignal_D_BATENE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [227] ComConf_ComSignal_D_BERG1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [228] ComConf_ComSignal_D_BERG2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [229] ComConf_ComSignal_D_BERG3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [230] ComConf_ComSignal_D_BALM_1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [231] ComConf_ComSignal_D_BALM_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [232] ComConf_ComSignal_D_BALM_3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [233] ComConf_ComSignal_D_BALM_4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [234] ComConf_ComSignal_D_BALM_5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [235] ComConf_ComSignal_D_BCODE1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [236] ComConf_ComSignal_D_BCODE2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [237] ComConf_ComSignal_D_BCODE3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [238] ComConf_ComSignal_D_BCODE4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [239] ComConf_ComSignal_D_BCODE5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [240] ComConf_ComSignal_D_BCODE6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [241] ComConf_ComSignal_D_BCODE7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [242] ComConf_ComSignal_D_BCODE8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [243] ComConf_ComSignal_D_VCELCH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [244] ComConf_ComSignal_D_VCELL0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [245] ComConf_ComSignal_D_VCELL1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [246] ComConf_ComSignal_D_VCELL2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [247] ComConf_ComSignal_D_VCELL3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [248] ComConf_ComSignal_D_TBCH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [249] ComConf_ComSignal_D_TB0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [250] ComConf_ComSignal_D_TB1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [251] ComConf_ComSignal_D_TB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [252] ComConf_ComSignal_D_TB3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [253] ComConf_ComSignal_D_TB4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [254] ComConf_ComSignal_D_TB5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [255] ComConf_ComSignal_D_TB6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [256] ComConf_ComSignal_D_MINFAD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [257] ComConf_ComSignal_D_MINFO1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [258] ComConf_ComSignal_D_MINFO2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [259] ComConf_ComSignal_D_MINFO3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [260] ComConf_ComSignal_D_BVIN1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [261] ComConf_ComSignal_D_BVIN2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [262] ComConf_ComSignal_D_BVIN3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [263] ComConf_ComSignal_D_BVIN4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [264] ComConf_ComSignal_D_BVIN5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [265] ComConf_ComSignal_D_BVIN6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [266] ComConf_ComSignal_D_BVIN7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [267] ComConf_ComSignal_D_BVIN8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [268] ComConf_ComSignal_D_BVIN9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [269] ComConf_ComSignal_D_BVIN10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [270] ComConf_ComSignal_D_BVIN11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [271] ComConf_ComSignal_D_BVIN12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [272] ComConf_ComSignal_D_BVIN13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [273] ComConf_ComSignal_D_BVIN14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [274] ComConf_ComSignal_D_BVIN15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [275] ComConf_ComSignal_D_BVIN16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [276] ComConf_ComSignal_D_BVIN17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [277] ComConf_ComSignal_D_BVIN18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [278] ComConf_ComSignal_D_BVIN19 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [279] ComConf_ComSignal_D_BVIN20 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [280] ComConf_ComSignal_D_BVIN21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [281] ComConf_ComSignal_D_BVIN22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [282] ComConf_ComSignal_D_BVIN23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [283] ComConf_ComSignal_D_BVIN24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [284] ComConf_ComSignal_D00887 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [285] ComConf_ComSignal_D00888 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [286] ComConf_ComSignal_D00889 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [287] ComConf_ComSignal_D00890 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [288] ComConf_ComSignal_BTWO */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [289] ComConf_ComSignal_D00891 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [290] ComConf_ComSignal_D00892 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [291] ComConf_ComSignal_D00893 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [292] ComConf_ComSignal_D00894 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [293] ComConf_ComSignal_D00895 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [294] ComConf_ComSignal_BITGB1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [295] ComConf_ComSignal_BITGB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [296] ComConf_ComSignal_BITGB3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [297] ComConf_ComSignal_BITGB4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [298] ComConf_ComSignal_STKNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [299] ComConf_ComSignal_BITGB5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [300] ComConf_ComSignal_VCELNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [301] ComConf_ComSignal_INFGB1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [302] ComConf_ComSignal_TMINNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [303] ComConf_ComSignal_INFGB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [304] ComConf_ComSignal_TMAXNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [305] ComConf_ComSignal_VBTINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [306] ComConf_ComSignal_SOCINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [307] ComConf_ComSignal_IBTINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [308] ComConf_ComSignal_TBTINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [309] ComConf_ComSignal_STPSOC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [310] ComConf_ComSignal_STPVB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [311] ComConf_ComSignal_STPCELV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [312] ComConf_ComSignal_STPTMP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [313] ComConf_ComSignal_DATAGB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [314] ComConf_ComSignal_DATAGB3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [315] ComConf_ComSignal_ID63B16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [316] ComConf_ComSignal_IF63B16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [317] ComConf_ComSignal_TRIP_CNT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [318] ComConf_ComSignal_TIME_CNT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [319] ComConf_ComSignal_D01107 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [320] ComConf_ComSignal_D01108 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [321] ComConf_ComSignal_IL_FDOME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [322] ComConf_ComSignal_IL_LOUNG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [323] ComConf_ComSignal_IL_OSSTP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [324] ComConf_ComSignal_AMB_COP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [325] ComConf_ComSignal_SUPRQ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [326] ComConf_ComSignal_D01109 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [327] ComConf_ComSignal_D01110 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [328] ComConf_ComSignal_D01215 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [329] ComConf_ComSignal_D01216 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [330] ComConf_ComSignal_D01217 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [331] ComConf_ComSignal_D01218 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [332] ComConf_ComSignal_D01219 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [333] ComConf_ComSignal_D01220 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [334] ComConf_ComSignal_D01221 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [335] ComConf_ComSignal_D01222 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [336] ComConf_ComSignal_D01223 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [337] ComConf_ComSignal_D01224 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [338] ComConf_ComSignal_AXSOC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [339] ComConf_ComSignal_D01225 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [340] ComConf_ComSignal_D01226 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [341] ComConf_ComSignal_D01227 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [342] ComConf_ComSignal_D01228 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [343] ComConf_ComSignal_D01229 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [344] ComConf_ComSignal_D01230 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [345] ComConf_ComSignal_D01231 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [346] ComConf_ComSignal_D01232 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [347] ComConf_ComSignal_D01233 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [348] ComConf_ComSignal_D01234 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [349] ComConf_ComSignal_D01235 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [350] ComConf_ComSignal_D01236 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [351] ComConf_ComSignal_D01237 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [352] ComConf_ComSignal_D01238 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [353] ComConf_ComSignal_D01239 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [354] ComConf_ComSignal_D01240 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [355] ComConf_ComSignal_D01241 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [356] ComConf_ComSignal_D01242 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [357] ComConf_ComSignal_D01243 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [358] ComConf_ComSignal_D01244 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [359] ComConf_ComSignal_D01245 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [360] ComConf_ComSignal_D01246 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [361] ComConf_ComSignal_D01247 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [362] ComConf_ComSignal_D01248 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [363] ComConf_ComSignal_D01249 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [364] ComConf_ComSignal_D01250 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [365] ComConf_ComSignal_D01251 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [366] ComConf_ComSignal_D01252 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [367] ComConf_ComSignal_D01253 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [368] ComConf_ComSignal_D01254 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [369] ComConf_ComSignal_D01255 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [370] ComConf_ComSignal_D01256 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [371] ComConf_ComSignal_D01257 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [372] ComConf_ComSignal_D01258 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [373] ComConf_ComSignal_D01259 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [374] ComConf_ComSignal_D01260 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [375] ComConf_ComSignal_D01261 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [376] ComConf_ComSignal_D01262 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [377] ComConf_ComSignal_D01263 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [378] ComConf_ComSignal_E_CRC1E3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [379] ComConf_ComSignal_E_CNT1E3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [380] ComConf_ComSignal_VPSINFO7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [381] ComConf_ComSignal_VPSINFO6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [382] ComConf_ComSignal_VPSINFO5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [383] ComConf_ComSignal_VPSINFO4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [384] ComConf_ComSignal_VPSINFO3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [385] ComConf_ComSignal_VPSINFO2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [386] ComConf_ComSignal_VPSINFO1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [387] ComConf_ComSignal_VPSINFOS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [388] ComConf_ComSignal_VPSCNG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [389] ComConf_ComSignal_VPSISOTA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [390] ComConf_ComSignal_APOFRQ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [391] ComConf_ComSignal_FV1E3_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [392] ComConf_ComSignal_KZK1E3_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [393] ComConf_ComSignal_E_CRC150 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [394] ComConf_ComSignal_E_CNT150 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [395] ComConf_ComSignal_PWRERRST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [396] ComConf_ComSignal_CRLYOF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [397] ComConf_ComSignal_D01300 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [398] ComConf_ComSignal_D01301 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [399] ComConf_ComSignal_D01302 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [400] ComConf_ComSignal_D01303 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [401] ComConf_ComSignal_D01304 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [402] ComConf_ComSignal_D01305 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [403] ComConf_ComSignal_FV150_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [404] ComConf_ComSignal_KZK150_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [405] ComConf_ComSignal_ST1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [406] ComConf_ComSignal_ST1PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [407] ComConf_ComSignal_ST2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [408] ComConf_ComSignal_ST2PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [409] ComConf_ComSignal_ST3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [410] ComConf_ComSignal_ST3PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [411] ComConf_ComSignal_ST4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [412] ComConf_ComSignal_ST4PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [413] ComConf_ComSignal_ST5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [414] ComConf_ComSignal_ST5PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [415] ComConf_ComSignal_ST6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [416] ComConf_ComSignal_ST6PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [417] ComConf_ComSignal_ST7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [418] ComConf_ComSignal_ST7PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [419] ComConf_ComSignal_ST8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [420] ComConf_ComSignal_ST8PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [421] ComConf_ComSignal_ST9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [422] ComConf_ComSignal_ST9PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [423] ComConf_ComSignal_ST10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [424] ComConf_ComSignal_ST10PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [425] ComConf_ComSignal_ST11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [426] ComConf_ComSignal_ST11PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [427] ComConf_ComSignal_ST12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [428] ComConf_ComSignal_ST12PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [429] ComConf_ComSignal_ST13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [430] ComConf_ComSignal_ST13PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [431] ComConf_ComSignal_ST14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [432] ComConf_ComSignal_ST14PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [433] ComConf_ComSignal_ST15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [434] ComConf_ComSignal_ST15PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [435] ComConf_ComSignal_ST16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [436] ComConf_ComSignal_ST16PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [437] ComConf_ComSignal_ST17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [438] ComConf_ComSignal_ST17PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [439] ComConf_ComSignal_ST18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [440] ComConf_ComSignal_ST18PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [441] ComConf_ComSignal_D01689 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [442] ComConf_ComSignal_D01690 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [443] ComConf_ComSignal_D01691 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [444] ComConf_ComSignal_D01692 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [445] ComConf_ComSignal_D01693 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [446] ComConf_ComSignal_D01694 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [447] ComConf_ComSignal_D01695 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [448] ComConf_ComSignal_D01696 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [449] ComConf_ComSignal_D01697 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [450] ComConf_ComSignal_ACPRE_AD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [451] ComConf_ComSignal_EXPMIP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [452] ComConf_ComSignal_D01698 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [453] ComConf_ComSignal_AMR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [454] ComConf_ComSignal_MIP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [455] ComConf_ComSignal_D01699 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [456] ComConf_ComSignal_D01700 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [457] ComConf_ComSignal_D01701 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [458] ComConf_ComSignal_D01702 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [459] ComConf_ComSignal_D01703 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [460] ComConf_ComSignal_D01704 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [461] ComConf_ComSignal_D01705 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [462] ComConf_ComSignal_D01706 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [463] ComConf_ComSignal_D01707 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [464] ComConf_ComSignal_D01708 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [465] ComConf_ComSignal_D01709 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [466] ComConf_ComSignal_D01710 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [467] ComConf_ComSignal_D01711 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [468] ComConf_ComSignal_D01712 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [469] ComConf_ComSignal_D01713 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [470] ComConf_ComSignal_D01714 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [471] ComConf_ComSignal_D01715 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [472] ComConf_ComSignal_D01716 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [473] ComConf_ComSignal_D01717 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [474] ComConf_ComSignal_D01718 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [475] ComConf_ComSignal_D01719 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [476] ComConf_ComSignal_FV37B_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [477] ComConf_ComSignal_KZK37B_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [478] ComConf_ComSignal_D01720 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [479] ComConf_ComSignal_D01721 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [480] ComConf_ComSignal_D01722 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [481] ComConf_ComSignal_D01723 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [482] ComConf_ComSignal_D01724 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [483] ComConf_ComSignal_D01725 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [484] ComConf_ComSignal_D01726 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [485] ComConf_ComSignal_D01727 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [486] ComConf_ComSignal_D01728 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [487] ComConf_ComSignal_D01729 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [488] ComConf_ComSignal_D01730 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [489] ComConf_ComSignal_D01731 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [490] ComConf_ComSignal_D01732 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [491] ComConf_ComSignal_D01733 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [492] ComConf_ComSignal_D01734 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [493] ComConf_ComSignal_D01735 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [494] ComConf_ComSignal_D01736 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [495] ComConf_ComSignal_D01737 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [496] ComConf_ComSignal_D01738 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [497] ComConf_ComSignal_HVH_ATPW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [498] ComConf_ComSignal_D01739 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [499] ComConf_ComSignal_D01740 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [500] ComConf_ComSignal_D01741 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [501] ComConf_ComSignal_D01742 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [502] ComConf_ComSignal_D01743 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [503] ComConf_ComSignal_D01744 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [504] ComConf_ComSignal_D01745 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [505] ComConf_ComSignal_D01746 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [506] ComConf_ComSignal_D01747 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [507] ComConf_ComSignal_D01748 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [508] ComConf_ComSignal_D01749 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [509] ComConf_ComSignal_D01750 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [510] ComConf_ComSignal_D01751 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [511] ComConf_ComSignal_D01752 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [512] ComConf_ComSignal_D01753 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [513] ComConf_ComSignal_D01754 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [514] ComConf_ComSignal_D01755 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [515] ComConf_ComSignal_D01764 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [516] ComConf_ComSignal_D01765 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [517] ComConf_ComSignal_D01766 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [518] ComConf_ComSignal_D01767 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [519] ComConf_ComSignal_COMPRP_A */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [520] ComConf_ComSignal_D01768 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [521] ComConf_ComSignal_ACMODE_P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [522] ComConf_ComSignal_D01769 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [523] ComConf_ComSignal_ETHWU_21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [524] ComConf_ComSignal_ETHWU_23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [525] ComConf_ComSignal_HED_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [526] ComConf_ComSignal_TAL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [527] ComConf_ComSignal_DRL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [528] ComConf_ComSignal_AUT_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [529] ComConf_ComSignal_OFF_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [530] ComConf_ComSignal_AHB_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [531] ComConf_ComSignal_PAS_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [532] ComConf_ComSignal_HIB_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [533] ComConf_ComSignal_BW_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [534] ComConf_ComSignal_RFG_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [535] ComConf_ComSignal_FOG_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [536] ComConf_ComSignal_CRGL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [537] ComConf_ComSignal_CRGR_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [538] ComConf_ComSignal_TRNL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [539] ComConf_ComSignal_TRNR_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [540] ComConf_ComSignal_D02823 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [541] ComConf_ComSignal_CXP_JDGT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [542] ComConf_ComSignal_WVR_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [543] ComConf_ComSignal_WSW_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [544] ComConf_ComSignal_WRSW_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [545] ComConf_ComSignal_WRON_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [546] ComConf_ComSignal_WRIN_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [547] ComConf_ComSignal_WINT_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [548] ComConf_ComSignal_WMST_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [549] ComConf_ComSignal_WA_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [550] ComConf_ComSignal_WHI_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [551] ComConf_ComSignal_WLO_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [552] ComConf_ComSignal_WOFF_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [553] ComConf_ComSignal_WAI_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [554] ComConf_ComSignal_CXP_JDGW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [555] ComConf_ComSignal_D02943 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [556] ComConf_ComSignal_ETHWU_32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [557] ComConf_ComSignal_THR_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [558] ComConf_ComSignal_TMO_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [559] ComConf_ComSignal_TTA_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [560] ComConf_ComSignal_RTA_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [561] ComConf_ComSignal_TR_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [562] ComConf_ComSignal_TM_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [563] ComConf_ComSignal_NR_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [564] ComConf_ComSignal_NM_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [565] ComConf_ComSignal_D03097 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [566] ComConf_ComSignal_NMRBR_MD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [567] ComConf_ComSignal_BHSWEXT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [568] ComConf_ComSignal_D03098 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [569] ComConf_ComSignal_NMRBSWEX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [570] ComConf_ComSignal_D03099 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [571] ComConf_ComSignal_GRLGDBCR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [572] ComConf_ComSignal_DMCNVINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [573] ComConf_ComSignal_CNV_MODE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [574] ComConf_ComSignal_DMCNVVLD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [575] ComConf_ComSignal_TEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [576] ComConf_ComSignal_DRVEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [577] ComConf_ComSignal_ALTEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [578] ComConf_ComSignal_ACEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [579] ComConf_ComSignal_BPEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [580] ComConf_ComSignal_DAEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [581] ComConf_ComSignal_CAEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [582] ComConf_ComSignal_CUMTEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [583] ComConf_ComSignal_CUMDRVEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [584] ComConf_ComSignal_CUMALTEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [585] ComConf_ComSignal_CUMACEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [586] ComConf_ComSignal_CUMBPEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [587] ComConf_ComSignal_CUMDAEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [588] ComConf_ComSignal_CUMCAEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [589] ComConf_ComSignal_CUMTEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [590] ComConf_ComSignal_CUMTEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [591] ComConf_ComSignal_CRDRVEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [592] ComConf_ComSignal_CRDRVEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [593] ComConf_ComSignal_CRALTEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [594] ComConf_ComSignal_CRALTEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [595] ComConf_ComSignal_CRACEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [596] ComConf_ComSignal_CRACEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [597] ComConf_ComSignal_CRPACEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [598] ComConf_ComSignal_CRPACEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [599] ComConf_ComSignal_CRBPEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [600] ComConf_ComSignal_CRBPEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [601] ComConf_ComSignal_CRPBPEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [602] ComConf_ComSignal_CRPBPEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [603] ComConf_ComSignal_CRDAEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [604] ComConf_ComSignal_CRDAEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [605] ComConf_ComSignal_CRPAEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [606] ComConf_ComSignal_CRPAEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [607] ComConf_ComSignal_RSISDKME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [608] ComConf_ComSignal_RSISIDDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [609] ComConf_ComSignal_D04459 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [610] ComConf_ComSignal_D04460 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [611] ComConf_ComSignal_D04514 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [612] ComConf_ComSignal_DESMUTE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [613] ComConf_ComSignal_DREBUID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [614] ComConf_ComSignal_DREBU02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [615] ComConf_ComSignal_DREBU03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [616] ComConf_ComSignal_DREBU04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [617] ComConf_ComSignal_DREBU05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [618] ComConf_ComSignal_DREBU06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [619] ComConf_ComSignal_DREBU07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [620] ComConf_ComSignal_DREBU08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [621] ComConf_ComSignal_DREBU11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [622] ComConf_ComSignal_DREBU12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [623] ComConf_ComSignal_DREBU13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [624] ComConf_ComSignal_DREBU14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [625] ComConf_ComSignal_DREBU15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [626] ComConf_ComSignal_DREBU16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [627] ComConf_ComSignal_DREBU17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [628] ComConf_ComSignal_DREBU18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [629] ComConf_ComSignal_DREBU21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [630] ComConf_ComSignal_DREBU22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [631] ComConf_ComSignal_DREBU23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [632] ComConf_ComSignal_DREBU24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [633] ComConf_ComSignal_DREBU25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [634] ComConf_ComSignal_DREBU26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [635] ComConf_ComSignal_DREBU27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [636] ComConf_ComSignal_DREBU28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [637] ComConf_ComSignal_DREBU31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [638] ComConf_ComSignal_DREBU32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [639] ComConf_ComSignal_DREBU33 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [640] ComConf_ComSignal_DREBU34 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [641] ComConf_ComSignal_DREBU35 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [642] ComConf_ComSignal_DREBU36 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [643] ComConf_ComSignal_DREBU37 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [644] ComConf_ComSignal_DREBU38 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [645] ComConf_ComSignal_DRDYSTS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [646] ComConf_ComSignal_DRDYB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [647] ComConf_ComSignal_D04741 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [648] ComConf_ComSignal_STRGCM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [649] ComConf_ComSignal_D04742 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [650] ComConf_ComSignal_D04743 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [651] ComConf_ComSignal_D04744 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [652] ComConf_ComSignal_D04745 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [653] ComConf_ComSignal_D04746 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [654] ComConf_ComSignal_D04747 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [655] ComConf_ComSignal_D04748 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [656] ComConf_ComSignal_D04749 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [657] ComConf_ComSignal_HV_SRGMD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [658] ComConf_ComSignal_D04800 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [659] ComConf_ComSignal_D04801 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [660] ComConf_ComSignal_TQRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [661] ComConf_ComSignal_D04802 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [662] ComConf_ComSignal_TQFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [663] ComConf_ComSignal_D04803 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [664] ComConf_ComSignal_D04804 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [665] ComConf_ComSignal_FCRF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [666] ComConf_ComSignal_CLE_SOCF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [667] ComConf_ComSignal_D04860 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [668] ComConf_ComSignal_D04861 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [669] ComConf_ComSignal_E_CRC075 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [670] ComConf_ComSignal_E_CNT075 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [671] ComConf_ComSignal_D04900 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [672] ComConf_ComSignal_SDRVRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [673] ComConf_ComSignal_D04901 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [674] ComConf_ComSignal_D04902 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [675] ComConf_ComSignal_SDRVFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [676] ComConf_ComSignal_D04903 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [677] ComConf_ComSignal_D04904 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [678] ComConf_ComSignal_D04905 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [679] ComConf_ComSignal_E_CRC0A1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [680] ComConf_ComSignal_E_CNT0A1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [681] ComConf_ComSignal_D04906 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [682] ComConf_ComSignal_D04907 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [683] ComConf_ComSignal_HVMRADRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [684] ComConf_ComSignal_HVMRADFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [685] ComConf_ComSignal_D05101 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [686] ComConf_ComSignal_DREIMABN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [687] ComConf_ComSignal_I_BAT_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [688] ComConf_ComSignal_U_BAT_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [689] ComConf_ComSignal_PWDTY_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [690] ComConf_ComSignal_VLO_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [691] ComConf_ComSignal_PWIF1_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [692] ComConf_ComSignal_T_BAT_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [693] ComConf_ComSignal_PWIF2_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [694] ComConf_ComSignal_SOCS_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [695] ComConf_ComSignal_SOC_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [696] ComConf_ComSignal_PWIF3_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [697] ComConf_ComSignal_PWIF4_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [698] ComConf_ComSignal_PWIF5_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [699] ComConf_ComSignal_DRENG11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [700] ComConf_ComSignal_DRENG12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [701] ComConf_ComSignal_DRENG13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [702] ComConf_ComSignal_DRENG14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [703] ComConf_ComSignal_DRENG15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [704] ComConf_ComSignal_DRENG16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [705] ComConf_ComSignal_DRENG17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [706] ComConf_ComSignal_DRENG18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [707] ComConf_ComSignal_DRENG21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [708] ComConf_ComSignal_DRENG22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [709] ComConf_ComSignal_DRENG23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [710] ComConf_ComSignal_DRENG24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [711] ComConf_ComSignal_DRENG25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [712] ComConf_ComSignal_DRENG26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [713] ComConf_ComSignal_DRENG27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [714] ComConf_ComSignal_DRENG28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [715] ComConf_ComSignal_DRENG31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [716] ComConf_ComSignal_DRENG32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [717] ComConf_ComSignal_DRENG33 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [718] ComConf_ComSignal_DRENG34 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [719] ComConf_ComSignal_DRENG35 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [720] ComConf_ComSignal_DRENG36 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [721] ComConf_ComSignal_DRENG37 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [722] ComConf_ComSignal_DRENG38 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [723] ComConf_ComSignal_DRENG51 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [724] ComConf_ComSignal_DRENG52 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [725] ComConf_ComSignal_DRENG53 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [726] ComConf_ComSignal_DRENG54 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [727] ComConf_ComSignal_DRENG55 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [728] ComConf_ComSignal_DRENG56 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [729] ComConf_ComSignal_DRENG57 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [730] ComConf_ComSignal_DRENG58 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [731] ComConf_ComSignal_DRENG61 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [732] ComConf_ComSignal_DRENG62 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [733] ComConf_ComSignal_DRENG63 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [734] ComConf_ComSignal_DRENG64 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [735] ComConf_ComSignal_DRENG65 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [736] ComConf_ComSignal_DRENG66 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [737] ComConf_ComSignal_DRENG67 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [738] ComConf_ComSignal_DRENG68 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [739] ComConf_ComSignal_DRENG91 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [740] ComConf_ComSignal_DRENG92 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [741] ComConf_ComSignal_DRENG93 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [742] ComConf_ComSignal_DRENG94 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [743] ComConf_ComSignal_DRENG95 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [744] ComConf_ComSignal_DRENG96 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [745] ComConf_ComSignal_DRENG97 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [746] ComConf_ComSignal_DRENG98 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [747] ComConf_ComSignal_DRENG101 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [748] ComConf_ComSignal_DRENG102 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [749] ComConf_ComSignal_DRENG103 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [750] ComConf_ComSignal_DRENG104 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [751] ComConf_ComSignal_DRENG105 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [752] ComConf_ComSignal_DRENG106 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [753] ComConf_ComSignal_DRENG107 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [754] ComConf_ComSignal_DRENG108 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [755] ComConf_ComSignal_VIN_1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [756] ComConf_ComSignal_VIN_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [757] ComConf_ComSignal_VIN_3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [758] ComConf_ComSignal_VIN_4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [759] ComConf_ComSignal_VIN_5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [760] ComConf_ComSignal_VIN_6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [761] ComConf_ComSignal_VIN_7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [762] ComConf_ComSignal_VIN_8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [763] ComConf_ComSignal_VIN_9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [764] ComConf_ComSignal_VIN_10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [765] ComConf_ComSignal_VIN_11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [766] ComConf_ComSignal_VIN_12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [767] ComConf_ComSignal_VIN_13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [768] ComConf_ComSignal_VIN_14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [769] ComConf_ComSignal_VIN_15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [770] ComConf_ComSignal_VIN_16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [771] ComConf_ComSignal_VIN_17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [772] ComConf_ComSignal_D05112 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [773] ComConf_ComSignal_D05113 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [774] ComConf_ComSignal_DREPS01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [775] ComConf_ComSignal_DREPS02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [776] ComConf_ComSignal_DREPS03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [777] ComConf_ComSignal_DREPS04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [778] ComConf_ComSignal_DREPS05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [779] ComConf_ComSignal_DREPS06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [780] ComConf_ComSignal_DREPS07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [781] ComConf_ComSignal_DREPS08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [782] ComConf_ComSignal_V_DIST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [783] ComConf_ComSignal_V_RELV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [784] ComConf_ComSignal_V_SWOP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [785] ComConf_ComSignal_USMREQG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [786] ComConf_ComSignal_RCURVR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [787] ComConf_ComSignal_USMDSTTS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [788] ComConf_ComSignal_COFFSET */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [789] ComConf_ComSignal_USMDSTSL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [790] ComConf_ComSignal_RSACAUF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [791] ComConf_ComSignal_OTHVW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [792] ComConf_ComSignal_OTHVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [793] ComConf_ComSignal_OTHPB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [794] ComConf_ComSignal_OTHTTC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [795] ComConf_ComSignal_OTHTTYP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [796] ComConf_ComSignal_D05167 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [797] ComConf_ComSignal_D05168 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [798] ComConf_ComSignal_FSPCSSTA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [799] ComConf_ComSignal_HITPOS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [800] ComConf_ComSignal_OTHRDANG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [801] ComConf_ComSignal_D05169 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [802] ComConf_ComSignal_D05170 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [803] ComConf_ComSignal_D05171 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [804] ComConf_ComSignal_OTHTSSST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [805] ComConf_ComSignal_D05172 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [806] ComConf_ComSignal_D05173 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [807] ComConf_ComSignal_D05174 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [808] ComConf_ComSignal_D05175 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [809] ComConf_ComSignal_D05176 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [810] ComConf_ComSignal_D05177 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [811] ComConf_ComSignal_OTHOVLPC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [812] ComConf_ComSignal_OTHRVPC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [813] ComConf_ComSignal_OTHFALD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [814] ComConf_ComSignal_OTHCOND */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [815] ComConf_ComSignal_OTHLDIS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [816] ComConf_ComSignal_OTHFALF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [817] ComConf_ComSignal_OTHCONF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [818] ComConf_ComSignal_OTHLANE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [819] ComConf_ComSignal_OTHSOR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [820] ComConf_ComSignal_OTHROR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [821] ComConf_ComSignal_OTHLX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [822] ComConf_ComSignal_OTHSOLAR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [823] ComConf_ComSignal_D05194 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [824] ComConf_ComSignal_D05195 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [825] ComConf_ComSignal_D05196 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [826] ComConf_ComSignal_D05197 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [827] ComConf_ComSignal_D05198 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [828] ComConf_ComSignal_D05199 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [829] ComConf_ComSignal_XREQFPB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [830] ComConf_ComSignal_XREQPB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [831] ComConf_ComSignal_D05200 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [832] ComConf_ComSignal_D05201 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [833] ComConf_ComSignal_XREQPBH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [834] ComConf_ComSignal_D05202 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [835] ComConf_ComSignal_D05203 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [836] ComConf_ComSignal_D05204 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [837] ComConf_ComSignal_D05205 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [838] ComConf_ComSignal_D05206 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [839] ComConf_ComSignal_D05207 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [840] ComConf_ComSignal_D05208 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [841] ComConf_ComSignal_D05209 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [842] ComConf_ComSignal_D05210 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [843] ComConf_ComSignal_D05211 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [844] ComConf_ComSignal_D05212 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [845] ComConf_ComSignal_D05213 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [846] ComConf_ComSignal_D05214 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [847] ComConf_ComSignal_D05215 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [848] ComConf_ComSignal_D05216 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [849] ComConf_ComSignal_AVSTRGR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [850] ComConf_ComSignal_PBATRGR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [851] ComConf_ComSignal_D05217 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [852] ComConf_ComSignal_D05218 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [853] ComConf_ComSignal_PCSALM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [854] ComConf_ComSignal_D05219 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [855] ComConf_ComSignal_D05220 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [856] ComConf_ComSignal_D05221 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [857] ComConf_ComSignal_D05222 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [858] ComConf_ComSignal_D05223 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [859] ComConf_ComSignal_D05224 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [860] ComConf_ComSignal_D05225 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [861] ComConf_ComSignal_D05226 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [862] ComConf_ComSignal_D05227 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [863] ComConf_ComSignal_D05228 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [864] ComConf_ComSignal_D05229 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [865] ComConf_ComSignal_D05230 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [866] ComConf_ComSignal_D05231 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [867] ComConf_ComSignal_D05232 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [868] ComConf_ComSignal_D05233 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [869] ComConf_ComSignal_D05234 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [870] ComConf_ComSignal_D05235 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [871] ComConf_ComSignal_D05236 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [872] ComConf_ComSignal_D05237 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [873] ComConf_ComSignal_D05238 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [874] ComConf_ComSignal_D05239 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [875] ComConf_ComSignal_D05240 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [876] ComConf_ComSignal_D05241 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [877] ComConf_ComSignal_D05242 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [878] ComConf_ComSignal_D05243 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [879] ComConf_ComSignal_D05244 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [880] ComConf_ComSignal_D05245 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [881] ComConf_ComSignal_D05246 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [882] ComConf_ComSignal_D05247 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [883] ComConf_ComSignal_D05248 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [884] ComConf_ComSignal_D05249 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [885] ComConf_ComSignal_D05250 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [886] ComConf_ComSignal_D05251 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [887] ComConf_ComSignal_D05252 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [888] ComConf_ComSignal_D05253 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [889] ComConf_ComSignal_D05254 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [890] ComConf_ComSignal_D05255 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [891] ComConf_ComSignal_D05256 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [892] ComConf_ComSignal_D05257 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [893] ComConf_ComSignal_FV0A8_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [894] ComConf_ComSignal_KZK0A8_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [895] ComConf_ComSignal_LK_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [896] ComConf_ComSignal_LK_FUNC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [897] ComConf_ComSignal_ULK_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [898] ComConf_ComSignal_ULK_FUNC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [899] ComConf_ComSignal_RSISIDME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [900] ComConf_ComSignal_RSISIDID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [901] ComConf_ComSignal_D05283 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [902] ComConf_ComSignal_D05284 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [903] ComConf_ComSignal_ODO_UNIT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [904] ComConf_ComSignal_ODO */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [905] ComConf_ComSignal_RTQRRLMG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [906] ComConf_ComSignal_RTQFRLMG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [907] ComConf_ComSignal_BAOF_PDC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [908] ComConf_ComSignal_SIDPWC0 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [909] ComConf_ComSignal_SIDPWC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [910] ComConf_ComSignal_SIDPWC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [911] ComConf_ComSignal_SIDPWC3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [912] ComConf_ComSignal_SIDPWC4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [913] ComConf_ComSignal_SIDPWC5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [914] ComConf_ComSignal_SIDPWC6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [915] ComConf_ComSignal_SIDPWC7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [916] ComConf_ComSignal_SIDPWC8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [917] ComConf_ComSignal_SIDPWC9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [918] ComConf_ComSignal_SIDPWC10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [919] ComConf_ComSignal_SIDPWC11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [920] ComConf_ComSignal_SIDPWC12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [921] ComConf_ComSignal_SIDPWC13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [922] ComConf_ComSignal_SIDPWC14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [923] ComConf_ComSignal_SIDPWC15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [924] ComConf_ComSignal_SIDPWC16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [925] ComConf_ComSignal_SIDPWC17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [926] ComConf_ComSignal_SIDPWC18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [927] ComConf_ComSignal_SIDPWC19 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [928] ComConf_ComSignal_SIDPWC20 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [929] ComConf_ComSignal_SIDPWC21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [930] ComConf_ComSignal_SIDPWC22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [931] ComConf_ComSignal_SIDPWC23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [932] ComConf_ComSignal_SIDPWC24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [933] ComConf_ComSignal_SIDPWC25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [934] ComConf_ComSignal_SIDPWC26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [935] ComConf_ComSignal_SIDPWC27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [936] ComConf_ComSignal_SIDPWC28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [937] ComConf_ComSignal_SIDPWC29 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [938] ComConf_ComSignal_SIDPWC30 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [939] ComConf_ComSignal_SIDPWC31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [940] ComConf_ComSignal_E_CRC14F */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [941] ComConf_ComSignal_E_CNT14F */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [942] ComConf_ComSignal_RCPMD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [943] ComConf_ComSignal_D05993 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [944] ComConf_ComSignal_RCPFAIL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [945] ComConf_ComSignal_D05994 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [946] ComConf_ComSignal_D05995 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [947] ComConf_ComSignal_D05996 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [948] ComConf_ComSignal_RCPONST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [949] ComConf_ComSignal_D05997 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [950] ComConf_ComSignal_D05998 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [951] ComConf_ComSignal_D_YEAR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [952] ComConf_ComSignal_D_MONT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [953] ComConf_ComSignal_D_DAY */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [954] ComConf_ComSignal_D_HOUR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [955] ComConf_ComSignal_D_MIN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [956] ComConf_ComSignal_D_SEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [957] ComConf_ComSignal_D06040 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [958] ComConf_ComSignal_D06041 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [959] ComConf_ComSignal_D06042 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [960] ComConf_ComSignal_D06043 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [961] ComConf_ComSignal_D06044 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [962] ComConf_ComSignal_LATUDE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [963] ComConf_ComSignal_LOTUDE1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [964] ComConf_ComSignal_D06045 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [965] ComConf_ComSignal_D06046 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [966] ComConf_ComSignal_D_LAT1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [967] ComConf_ComSignal_D_LAT2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [968] ComConf_ComSignal_D06047 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [969] ComConf_ComSignal_D06048 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [970] ComConf_ComSignal_D06049 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [971] ComConf_ComSignal_D_LON1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [972] ComConf_ComSignal_D_LON2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [973] ComConf_ComSignal_D06050 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [974] ComConf_ComSignal_D06051 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [975] ComConf_ComSignal_D06052 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [976] ComConf_ComSignal_D06053 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [977] ComConf_ComSignal_ALTITUDE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [978] ComConf_ComSignal_OTADTYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [979] ComConf_ComSignal_OTADSTAT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [980] ComConf_ComSignal_OTADPROG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [981] ComConf_ComSignal_OTADERR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [982] ComConf_ComSignal_RSCYCL11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [983] ComConf_ComSignal_RSCYCL12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [984] ComConf_ComSignal_RSCYCL13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [985] ComConf_ComSignal_RSCYCL14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [986] ComConf_ComSignal_RSCYCL15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [987] ComConf_ComSignal_RSCYCL16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [988] ComConf_ComSignal_FRVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [989] ComConf_ComSignal_FLVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [990] ComConf_ComSignal_RRVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [991] ComConf_ComSignal_RLVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [992] ComConf_ComSignal_D06161 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [993] ComConf_ComSignal_D06162 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [994] ComConf_ComSignal_D06163 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [995] ComConf_ComSignal_D06164 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [996] ComConf_ComSignal_D06165 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [997] ComConf_ComSignal_D06166 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [998] ComConf_ComSignal_D06167 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [999] ComConf_ComSignal_D06168 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1000] ComConf_ComSignal_D06169 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1001] ComConf_ComSignal_D06170 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1002] ComConf_ComSignal_D06171 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1003] ComConf_ComSignal_D06172 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1004] ComConf_ComSignal_D06173 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1005] ComConf_ComSignal_D06174 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1006] ComConf_ComSignal_D06175 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1007] ComConf_ComSignal_D06176 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1008] ComConf_ComSignal_D06177 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1009] ComConf_ComSignal_D06178 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1010] ComConf_ComSignal_D06179 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1011] ComConf_ComSignal_D06180 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1012] ComConf_ComSignal_DVGR01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1013] ComConf_ComSignal_DVGR02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1014] ComConf_ComSignal_DVGR03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1015] ComConf_ComSignal_DVGR04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1016] ComConf_ComSignal_DVGR05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1017] ComConf_ComSignal_DVGR06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1018] ComConf_ComSignal_DVGR07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1019] ComConf_ComSignal_DVGR08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1020] ComConf_ComSignal_DVGR09 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1021] ComConf_ComSignal_DVGR10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1022] ComConf_ComSignal_DVGR11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1023] ComConf_ComSignal_DVGR12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1024] ComConf_ComSignal_DVGR13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1025] ComConf_ComSignal_DVGR14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1026] ComConf_ComSignal_DVGR15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1027] ComConf_ComSignal_DVGR16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1028] ComConf_ComSignal_DVGR17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1029] ComConf_ComSignal_DVGR18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1030] ComConf_ComSignal_DVGR19 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1031] ComConf_ComSignal_DVGR20 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1032] ComConf_ComSignal_DVGR21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1033] ComConf_ComSignal_DVGR22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1034] ComConf_ComSignal_DVGR23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1035] ComConf_ComSignal_DVGR24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1036] ComConf_ComSignal_DVGR25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1037] ComConf_ComSignal_DVGR26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1038] ComConf_ComSignal_DVGR27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1039] ComConf_ComSignal_DVGR28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1040] ComConf_ComSignal_DVGR29 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1041] ComConf_ComSignal_DVGR30 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1042] ComConf_ComSignal_DVGR31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1043] ComConf_ComSignal_DVGR32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1044] ComConf_ComSignal_DRVSCID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1045] ComConf_ComSignal_DRVSC02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1046] ComConf_ComSignal_DRVSC03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1047] ComConf_ComSignal_DRVSC04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1048] ComConf_ComSignal_DRVSC05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1049] ComConf_ComSignal_DRVSC06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1050] ComConf_ComSignal_DRVSC07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1051] ComConf_ComSignal_DRVSC08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1052] ComConf_ComSignal_DRVSC11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1053] ComConf_ComSignal_DRVSC12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1054] ComConf_ComSignal_DRVSC13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1055] ComConf_ComSignal_DRVSC14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1056] ComConf_ComSignal_DRVSC15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1057] ComConf_ComSignal_DRVSC16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1058] ComConf_ComSignal_DRVSC17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1059] ComConf_ComSignal_DRVSC18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1060] ComConf_ComSignal_DRVSC21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1061] ComConf_ComSignal_DRVSC22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1062] ComConf_ComSignal_DRVSC23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1063] ComConf_ComSignal_DRVSC24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1064] ComConf_ComSignal_DRVSC25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1065] ComConf_ComSignal_DRVSC26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1066] ComConf_ComSignal_DRVSC27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1067] ComConf_ComSignal_DRVSC28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1068] ComConf_ComSignal_DREPB01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1069] ComConf_ComSignal_DREPB02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1070] ComConf_ComSignal_DREPB03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1071] ComConf_ComSignal_DREPB04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1072] ComConf_ComSignal_DREPB05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1073] ComConf_ComSignal_DREPB06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1074] ComConf_ComSignal_DREPB07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1075] ComConf_ComSignal_DREPB08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1076] ComConf_ComSignal_E_CRC09E */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1077] ComConf_ComSignal_E_CNT09E */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1078] ComConf_ComSignal_SP1S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1079] ComConf_ComSignal_GVSPDINV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1080] ComConf_ComSignal_SP1P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1081] ComConf_ComSignal_SP1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1082] ComConf_ComSignal_GVSPD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1083] ComConf_ComSignal_D06272 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1084] ComConf_ComSignal_D06273 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1085] ComConf_ComSignal_D06274 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1086] ComConf_ComSignal_D06275 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1087] ComConf_ComSignal_PWCF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1088] ComConf_ComSignal_PWC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1089] ComConf_ComSignal_D06276 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1090] ComConf_ComSignal_PWCS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1091] ComConf_ComSignal_PMCF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1092] ComConf_ComSignal_PMCS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1093] ComConf_ComSignal_PMC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1094] ComConf_ComSignal_D06277 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1095] ComConf_ComSignal_D06278 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1096] ComConf_ComSignal_D06279 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1097] ComConf_ComSignal_D06280 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1098] ComConf_ComSignal_D06281 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1099] ComConf_ComSignal_D06282 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1100] ComConf_ComSignal_D06283 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1101] ComConf_ComSignal_D06284 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1102] ComConf_ComSignal_D06285 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1103] ComConf_ComSignal_D06286 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1104] ComConf_ComSignal_D06287 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1105] ComConf_ComSignal_D06288 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1106] ComConf_ComSignal_D06289 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1107] ComConf_ComSignal_FV09E_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1108] ComConf_ComSignal_KZK09E_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1109] ComConf_ComSignal_FRWIPOPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1110] ComConf_ComSignal_FRWASH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1111] ComConf_ComSignal_RRWIPOPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1112] ComConf_ComSignal_RRWASH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1113] ComConf_ComSignal_D06704 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1114] ComConf_ComSignal_W_STPZ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1115] ComConf_ComSignal_FI_STP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1116] ComConf_ComSignal_D06773 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1117] ComConf_ComSignal_FV086_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1118] ComConf_ComSignal_KZK086_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1119] ComConf_ComSignal_RECRNOFF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1120] ComConf_ComSignal_FAV_FNC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1121] ComConf_ComSignal_CHG_FUNC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1122] ComConf_ComSignal_GSNSOFF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1123] ComConf_ComSignal_DRBDBABN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1124] ComConf_ComSignal_R_AC_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1125] ComConf_ComSignal_R_SYS_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1126] ComConf_ComSignal_R_FTE_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1127] ComConf_ComSignal_R_BD_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1128] ComConf_ComSignal_R_TIME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1129] ComConf_ComSignal_R_INT_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1130] ComConf_ComSignal_R_LMP_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1131] ComConf_ComSignal_R_SDE_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1132] ComConf_ComSignal_R_SYS_3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1133] ComConf_ComSignal_R_ST_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1134] ComConf_ComSignal_R_SYS_1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1135] ComConf_ComSignal_EIC_EQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1136] ComConf_ComSignal_EIC_FEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1137] ComConf_ComSignal_EIC_SEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1138] ComConf_ComSignal_EIC_IEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1139] ComConf_ComSignal_EIC_BEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1140] ComConf_ComSignal_QIC_BREQ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1141] ComConf_ComSignal_QIC_DISP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1142] ComConf_ComSignal_QIC_BVOL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1143] ComConf_ComSignal_QIC_DIS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1144] ComConf_ComSignal_EIC_DEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1145] ComConf_ComSignal_EIC_PEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1146] ComConf_ComSignal_EIC_REQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1147] ComConf_ComSignal_EIC_LEQP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1148] ComConf_ComSignal_AIC_DRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1149] ComConf_ComSignal_AIC_DMRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1150] ComConf_ComSignal_AIC_DFRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1151] ComConf_ComSignal_AIC_DBRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1152] ComConf_ComSignal_AIC_DRRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1153] ComConf_ComSignal_SIC_DMST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1154] ComConf_ComSignal_SIC_DCST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1155] ComConf_ComSignal_SIC_DFFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1156] ComConf_ComSignal_SIC_DFFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1157] ComConf_ComSignal_SIC_DFRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1158] ComConf_ComSignal_SIC_DFRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1159] ComConf_ComSignal_SIC_DF5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1160] ComConf_ComSignal_SIC_DFDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1161] ComConf_ComSignal_SIC_DFDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1162] ComConf_ComSignal_SIC_DF4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1163] ComConf_ComSignal_SIC_DF4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1164] ComConf_ComSignal_SIC_DF5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1165] ComConf_ComSignal_SIC_DBFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1166] ComConf_ComSignal_SIC_DBFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1167] ComConf_ComSignal_SIC_DBRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1168] ComConf_ComSignal_SIC_DBRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1169] ComConf_ComSignal_SIC_DB5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1170] ComConf_ComSignal_SIC_DBDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1171] ComConf_ComSignal_SIC_DBDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1172] ComConf_ComSignal_SIC_DB4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1173] ComConf_ComSignal_SIC_DB4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1174] ComConf_ComSignal_SIC_DB5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1175] ComConf_ComSignal_SIC_DRFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1176] ComConf_ComSignal_SIC_DRRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1177] ComConf_ComSignal_SIC_DRDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1178] ComConf_ComSignal_SIC_DR4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1179] ComConf_ComSignal_SIC_DR5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1180] ComConf_ComSignal_SIC_DRFK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1181] ComConf_ComSignal_SIC_DRRK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1182] ComConf_ComSignal_SIC_DRDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1183] ComConf_ComSignal_SIC_DR4K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1184] ComConf_ComSignal_SIC_DR5K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1185] ComConf_ComSignal_AIC_PRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1186] ComConf_ComSignal_AIC_PMRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1187] ComConf_ComSignal_AIC_PFRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1188] ComConf_ComSignal_AIC_PBRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1189] ComConf_ComSignal_AIC_PRRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1190] ComConf_ComSignal_SIC_PMST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1191] ComConf_ComSignal_SIC_PCST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1192] ComConf_ComSignal_SIC_PFFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1193] ComConf_ComSignal_SIC_PFFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1194] ComConf_ComSignal_SIC_PFRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1195] ComConf_ComSignal_SIC_PFRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1196] ComConf_ComSignal_SIC_PF5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1197] ComConf_ComSignal_SIC_PFDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1198] ComConf_ComSignal_SIC_PFDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1199] ComConf_ComSignal_SIC_PF4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1200] ComConf_ComSignal_SIC_PF4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1201] ComConf_ComSignal_SIC_PF5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1202] ComConf_ComSignal_SIC_PBFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1203] ComConf_ComSignal_SIC_PBFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1204] ComConf_ComSignal_SIC_PBRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1205] ComConf_ComSignal_SIC_PBRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1206] ComConf_ComSignal_SIC_PB5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1207] ComConf_ComSignal_SIC_PBDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1208] ComConf_ComSignal_SIC_PBDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1209] ComConf_ComSignal_SIC_PB4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1210] ComConf_ComSignal_SIC_PB4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1211] ComConf_ComSignal_SIC_PB5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1212] ComConf_ComSignal_SIC_PRFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1213] ComConf_ComSignal_SIC_PRRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1214] ComConf_ComSignal_SIC_PRDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1215] ComConf_ComSignal_SIC_PR4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1216] ComConf_ComSignal_SIC_PR5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1217] ComConf_ComSignal_SIC_PRFK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1218] ComConf_ComSignal_SIC_PRRK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1219] ComConf_ComSignal_SIC_PRDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1220] ComConf_ComSignal_SIC_PR4K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1221] ComConf_ComSignal_SIC_PR5K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1222] ComConf_ComSignal_AIC_RRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1223] ComConf_ComSignal_AIC_RMRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1224] ComConf_ComSignal_AIC_RFRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1225] ComConf_ComSignal_AIC_RBRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1226] ComConf_ComSignal_AIC_RRRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1227] ComConf_ComSignal_SIC_RMST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1228] ComConf_ComSignal_SIC_RCST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1229] ComConf_ComSignal_SIC_RFFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1230] ComConf_ComSignal_SIC_RFFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1231] ComConf_ComSignal_SIC_RFRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1232] ComConf_ComSignal_SIC_RFRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1233] ComConf_ComSignal_SIC_RF5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1234] ComConf_ComSignal_SIC_RFDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1235] ComConf_ComSignal_SIC_RFDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1236] ComConf_ComSignal_SIC_RF4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1237] ComConf_ComSignal_SIC_RF4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1238] ComConf_ComSignal_SIC_RF5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1239] ComConf_ComSignal_SIC_RBFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1240] ComConf_ComSignal_SIC_RBFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1241] ComConf_ComSignal_SIC_RBRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1242] ComConf_ComSignal_SIC_RBRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1243] ComConf_ComSignal_SIC_RB5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1244] ComConf_ComSignal_SIC_RBDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1245] ComConf_ComSignal_SIC_RBDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1246] ComConf_ComSignal_SIC_RB4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1247] ComConf_ComSignal_SIC_RB4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1248] ComConf_ComSignal_SIC_RB5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1249] ComConf_ComSignal_SIC_RRFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1250] ComConf_ComSignal_SIC_RRRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1251] ComConf_ComSignal_SIC_RRDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1252] ComConf_ComSignal_SIC_RR4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1253] ComConf_ComSignal_SIC_RR5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1254] ComConf_ComSignal_SIC_RRFK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1255] ComConf_ComSignal_SIC_RRRK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1256] ComConf_ComSignal_SIC_RRDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1257] ComConf_ComSignal_SIC_RR4K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1258] ComConf_ComSignal_SIC_RR5K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1259] ComConf_ComSignal_AIC_LRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1260] ComConf_ComSignal_AIC_LMRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1261] ComConf_ComSignal_AIC_LFRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1262] ComConf_ComSignal_AIC_LBRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1263] ComConf_ComSignal_AIC_LRRC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1264] ComConf_ComSignal_SIC_LMST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1265] ComConf_ComSignal_SIC_LCST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1266] ComConf_ComSignal_SIC_LFFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1267] ComConf_ComSignal_SIC_LFFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1268] ComConf_ComSignal_SIC_LFRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1269] ComConf_ComSignal_SIC_LFRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1270] ComConf_ComSignal_SIC_LF5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1271] ComConf_ComSignal_SIC_LFDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1272] ComConf_ComSignal_SIC_LFDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1273] ComConf_ComSignal_SIC_LF4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1274] ComConf_ComSignal_SIC_LF4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1275] ComConf_ComSignal_SIC_LF5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1276] ComConf_ComSignal_SIC_LBFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1277] ComConf_ComSignal_SIC_LBFP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1278] ComConf_ComSignal_SIC_LBRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1279] ComConf_ComSignal_SIC_LBRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1280] ComConf_ComSignal_SIC_LB5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1281] ComConf_ComSignal_SIC_LBDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1282] ComConf_ComSignal_SIC_LBDP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1283] ComConf_ComSignal_SIC_LB4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1284] ComConf_ComSignal_SIC_LB4P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1285] ComConf_ComSignal_SIC_LB5P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1286] ComConf_ComSignal_SIC_LRFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1287] ComConf_ComSignal_SIC_LRRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1288] ComConf_ComSignal_SIC_LRDL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1289] ComConf_ComSignal_SIC_LR4L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1290] ComConf_ComSignal_SIC_LR5L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1291] ComConf_ComSignal_SIC_LRFK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1292] ComConf_ComSignal_SIC_LRRK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1293] ComConf_ComSignal_SIC_LRDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1294] ComConf_ComSignal_SIC_LR4K */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [1295] ComConf_ComSignal_SIC_LR5K */
};

BswConst PduIdType bsw_com_u2DataHdl2MsgHdl[BSW_COM_HANDLE_NUM] = {
     (BswU2)0U                                                                                                   /* [0] ComConf_ComSignal_DRABG01 */
    ,(BswU2)0U                                                                                                   /* [1] ComConf_ComSignal_DRABG02 */
    ,(BswU2)0U                                                                                                   /* [2] ComConf_ComSignal_DRABG03 */
    ,(BswU2)0U                                                                                                   /* [3] ComConf_ComSignal_DRABG04 */
    ,(BswU2)0U                                                                                                   /* [4] ComConf_ComSignal_DRABG05 */
    ,(BswU2)0U                                                                                                   /* [5] ComConf_ComSignal_DRABG06 */
    ,(BswU2)0U                                                                                                   /* [6] ComConf_ComSignal_DRABG07 */
    ,(BswU2)0U                                                                                                   /* [7] ComConf_ComSignal_DRABG08 */
    ,(BswU2)1U                                                                                                   /* [8] ComConf_ComSignal_DRABG09 */
    ,(BswU2)1U                                                                                                   /* [9] ComConf_ComSignal_DRABG10 */
    ,(BswU2)1U                                                                                                   /* [10] ComConf_ComSignal_DRABG11 */
    ,(BswU2)1U                                                                                                   /* [11] ComConf_ComSignal_DRABG12 */
    ,(BswU2)1U                                                                                                   /* [12] ComConf_ComSignal_DRABG13 */
    ,(BswU2)1U                                                                                                   /* [13] ComConf_ComSignal_DRABG14 */
    ,(BswU2)1U                                                                                                   /* [14] ComConf_ComSignal_DRABG15 */
    ,(BswU2)1U                                                                                                   /* [15] ComConf_ComSignal_DRABG16 */
    ,(BswU2)2U                                                                                                   /* [16] ComConf_ComSignal_D00024 */
    ,(BswU2)2U                                                                                                   /* [17] ComConf_ComSignal_D00025 */
    ,(BswU2)2U                                                                                                   /* [18] ComConf_ComSignal_D00026 */
    ,(BswU2)2U                                                                                                   /* [19] ComConf_ComSignal_D00027 */
    ,(BswU2)2U                                                                                                   /* [20] ComConf_ComSignal_FLGXMAX */
    ,(BswU2)2U                                                                                                   /* [21] ComConf_ComSignal_D00028 */
    ,(BswU2)2U                                                                                                   /* [22] ComConf_ComSignal_D00029 */
    ,(BswU2)2U                                                                                                   /* [23] ComConf_ComSignal_D00030 */
    ,(BswU2)2U                                                                                                   /* [24] ComConf_ComSignal_FLVNMAX */
    ,(BswU2)2U                                                                                                   /* [25] ComConf_ComSignal_FRGMAX_L */
    ,(BswU2)2U                                                                                                   /* [26] ComConf_ComSignal_FRGMAX_R */
    ,(BswU2)2U                                                                                                   /* [27] ComConf_ComSignal_D00031 */
    ,(BswU2)2U                                                                                                   /* [28] ComConf_ComSignal_D00032 */
    ,(BswU2)2U                                                                                                   /* [29] ComConf_ComSignal_D00033 */
    ,(BswU2)2U                                                                                                   /* [30] ComConf_ComSignal_D00034 */
    ,(BswU2)2U                                                                                                   /* [31] ComConf_ComSignal_D00035 */
    ,(BswU2)2U                                                                                                   /* [32] ComConf_ComSignal_D00036 */
    ,(BswU2)2U                                                                                                   /* [33] ComConf_ComSignal_PT_ON */
    ,(BswU2)2U                                                                                                   /* [34] ComConf_ComSignal_FRAB_ON */
    ,(BswU2)2U                                                                                                   /* [35] ComConf_ComSignal_D00037 */
    ,(BswU2)2U                                                                                                   /* [36] ComConf_ComSignal_D00038 */
    ,(BswU2)2U                                                                                                   /* [37] ComConf_ComSignal_D00039 */
    ,(BswU2)2U                                                                                                   /* [38] ComConf_ComSignal_D00040 */
    ,(BswU2)2U                                                                                                   /* [39] ComConf_ComSignal_D00041 */
    ,(BswU2)2U                                                                                                   /* [40] ComConf_ComSignal_D00042 */
    ,(BswU2)2U                                                                                                   /* [41] ComConf_ComSignal_D00043 */
    ,(BswU2)2U                                                                                                   /* [42] ComConf_ComSignal_D00044 */
    ,(BswU2)2U                                                                                                   /* [43] ComConf_ComSignal_D00045 */
    ,(BswU2)2U                                                                                                   /* [44] ComConf_ComSignal_D00046 */
    ,(BswU2)3U                                                                                                   /* [45] ComConf_ComSignal_DRACN01 */
    ,(BswU2)3U                                                                                                   /* [46] ComConf_ComSignal_DRACN02 */
    ,(BswU2)3U                                                                                                   /* [47] ComConf_ComSignal_DRACN03 */
    ,(BswU2)3U                                                                                                   /* [48] ComConf_ComSignal_DRACN04 */
    ,(BswU2)3U                                                                                                   /* [49] ComConf_ComSignal_DRACN05 */
    ,(BswU2)3U                                                                                                   /* [50] ComConf_ComSignal_DRACN06 */
    ,(BswU2)3U                                                                                                   /* [51] ComConf_ComSignal_DRACN07 */
    ,(BswU2)3U                                                                                                   /* [52] ComConf_ComSignal_DRACN08 */
    ,(BswU2)4U                                                                                                   /* [53] ComConf_ComSignal_D00076 */
    ,(BswU2)4U                                                                                                   /* [54] ComConf_ComSignal_D00077 */
    ,(BswU2)4U                                                                                                   /* [55] ComConf_ComSignal_D00078 */
    ,(BswU2)4U                                                                                                   /* [56] ComConf_ComSignal_O_STG_F */
    ,(BswU2)4U                                                                                                   /* [57] ComConf_ComSignal_D00079 */
    ,(BswU2)4U                                                                                                   /* [58] ComConf_ComSignal_D00080 */
    ,(BswU2)4U                                                                                                   /* [59] ComConf_ComSignal_AC_CDSP */
    ,(BswU2)4U                                                                                                   /* [60] ComConf_ComSignal_D00081 */
    ,(BswU2)5U                                                                                                   /* [61] ComConf_ComSignal_D00093 */
    ,(BswU2)5U                                                                                                   /* [62] ComConf_ComSignal_TRTEMP_P */
    ,(BswU2)5U                                                                                                   /* [63] ComConf_ComSignal_I_BLWF_P */
    ,(BswU2)5U                                                                                                   /* [64] ComConf_ComSignal_D00094 */
    ,(BswU2)5U                                                                                                   /* [65] ComConf_ComSignal_D00095 */
    ,(BswU2)5U                                                                                                   /* [66] ComConf_ComSignal_D00096 */
    ,(BswU2)5U                                                                                                   /* [67] ComConf_ComSignal_D00097 */
    ,(BswU2)6U                                                                                                   /* [68] ComConf_ComSignal_D00110 */
    ,(BswU2)6U                                                                                                   /* [69] ComConf_ComSignal_D00111 */
    ,(BswU2)6U                                                                                                   /* [70] ComConf_ComSignal_D00112 */
    ,(BswU2)6U                                                                                                   /* [71] ComConf_ComSignal_D00113 */
    ,(BswU2)6U                                                                                                   /* [72] ComConf_ComSignal_D00114 */
    ,(BswU2)6U                                                                                                   /* [73] ComConf_ComSignal_D00115 */
    ,(BswU2)6U                                                                                                   /* [74] ComConf_ComSignal_D00116 */
    ,(BswU2)6U                                                                                                   /* [75] ComConf_ComSignal_D00117 */
    ,(BswU2)6U                                                                                                   /* [76] ComConf_ComSignal_D00118 */
    ,(BswU2)6U                                                                                                   /* [77] ComConf_ComSignal_D00119 */
    ,(BswU2)6U                                                                                                   /* [78] ComConf_ComSignal_D00120 */
    ,(BswU2)6U                                                                                                   /* [79] ComConf_ComSignal_D00121 */
    ,(BswU2)6U                                                                                                   /* [80] ComConf_ComSignal_D00122 */
    ,(BswU2)6U                                                                                                   /* [81] ComConf_ComSignal_D00123 */
    ,(BswU2)6U                                                                                                   /* [82] ComConf_ComSignal_D00124 */
    ,(BswU2)6U                                                                                                   /* [83] ComConf_ComSignal_D00125 */
    ,(BswU2)6U                                                                                                   /* [84] ComConf_ComSignal_D00126 */
    ,(BswU2)6U                                                                                                   /* [85] ComConf_ComSignal_HQ_COMP */
    ,(BswU2)7U                                                                                                   /* [86] ComConf_ComSignal_D00137 */
    ,(BswU2)7U                                                                                                   /* [87] ComConf_ComSignal_D00138 */
    ,(BswU2)7U                                                                                                   /* [88] ComConf_ComSignal_D00139 */
    ,(BswU2)7U                                                                                                   /* [89] ComConf_ComSignal_D00140 */
    ,(BswU2)7U                                                                                                   /* [90] ComConf_ComSignal_R_SHHTFL */
    ,(BswU2)7U                                                                                                   /* [91] ComConf_ComSignal_D00141 */
    ,(BswU2)7U                                                                                                   /* [92] ComConf_ComSignal_R_SHHTFR */
    ,(BswU2)7U                                                                                                   /* [93] ComConf_ComSignal_D00142 */
    ,(BswU2)7U                                                                                                   /* [94] ComConf_ComSignal_D00143 */
    ,(BswU2)7U                                                                                                   /* [95] ComConf_ComSignal_D00144 */
    ,(BswU2)7U                                                                                                   /* [96] ComConf_ComSignal_D00145 */
    ,(BswU2)7U                                                                                                   /* [97] ComConf_ComSignal_D00146 */
    ,(BswU2)7U                                                                                                   /* [98] ComConf_ComSignal_D00147 */
    ,(BswU2)7U                                                                                                   /* [99] ComConf_ComSignal_D00148 */
    ,(BswU2)7U                                                                                                   /* [100] ComConf_ComSignal_D00149 */
    ,(BswU2)7U                                                                                                   /* [101] ComConf_ComSignal_RSVFLDU */
    ,(BswU2)7U                                                                                                   /* [102] ComConf_ComSignal_D00150 */
    ,(BswU2)7U                                                                                                   /* [103] ComConf_ComSignal_RSVFRDU */
    ,(BswU2)7U                                                                                                   /* [104] ComConf_ComSignal_D00151 */
    ,(BswU2)7U                                                                                                   /* [105] ComConf_ComSignal_R_SHHTRL */
    ,(BswU2)7U                                                                                                   /* [106] ComConf_ComSignal_D00152 */
    ,(BswU2)7U                                                                                                   /* [107] ComConf_ComSignal_R_SHHTRR */
    ,(BswU2)7U                                                                                                   /* [108] ComConf_ComSignal_D00153 */
    ,(BswU2)7U                                                                                                   /* [109] ComConf_ComSignal_D00154 */
    ,(BswU2)7U                                                                                                   /* [110] ComConf_ComSignal_D00155 */
    ,(BswU2)7U                                                                                                   /* [111] ComConf_ComSignal_D00156 */
    ,(BswU2)7U                                                                                                   /* [112] ComConf_ComSignal_D00157 */
    ,(BswU2)7U                                                                                                   /* [113] ComConf_ComSignal_D00158 */
    ,(BswU2)7U                                                                                                   /* [114] ComConf_ComSignal_D00159 */
    ,(BswU2)7U                                                                                                   /* [115] ComConf_ComSignal_D00160 */
    ,(BswU2)7U                                                                                                   /* [116] ComConf_ComSignal_D00161 */
    ,(BswU2)7U                                                                                                   /* [117] ComConf_ComSignal_D00162 */
    ,(BswU2)7U                                                                                                   /* [118] ComConf_ComSignal_D00163 */
    ,(BswU2)7U                                                                                                   /* [119] ComConf_ComSignal_RSVRLDU */
    ,(BswU2)7U                                                                                                   /* [120] ComConf_ComSignal_D00164 */
    ,(BswU2)7U                                                                                                   /* [121] ComConf_ComSignal_RSVRRDU */
    ,(BswU2)7U                                                                                                   /* [122] ComConf_ComSignal_D00165 */
    ,(BswU2)7U                                                                                                   /* [123] ComConf_ComSignal_R_RDHRR */
    ,(BswU2)7U                                                                                                   /* [124] ComConf_ComSignal_D00166 */
    ,(BswU2)7U                                                                                                   /* [125] ComConf_ComSignal_R_RDHRL */
    ,(BswU2)7U                                                                                                   /* [126] ComConf_ComSignal_D00167 */
    ,(BswU2)7U                                                                                                   /* [127] ComConf_ComSignal_R_RDHFP */
    ,(BswU2)7U                                                                                                   /* [128] ComConf_ComSignal_D00168 */
    ,(BswU2)7U                                                                                                   /* [129] ComConf_ComSignal_R_RDHFD */
    ,(BswU2)7U                                                                                                   /* [130] ComConf_ComSignal_D00169 */
    ,(BswU2)7U                                                                                                   /* [131] ComConf_ComSignal_D00170 */
    ,(BswU2)7U                                                                                                   /* [132] ComConf_ComSignal_D00171 */
    ,(BswU2)7U                                                                                                   /* [133] ComConf_ComSignal_D00172 */
    ,(BswU2)8U                                                                                                   /* [134] ComConf_ComSignal_WS_VD_R */
    ,(BswU2)8U                                                                                                   /* [135] ComConf_ComSignal_WS_FTG_R */
    ,(BswU2)8U                                                                                                   /* [136] ComConf_ComSignal_WS_ABH_R */
    ,(BswU2)8U                                                                                                   /* [137] ComConf_ComSignal_WS_APO_R */
    ,(BswU2)9U                                                                                                   /* [138] ComConf_ComSignal_ETHWU_12 */
    ,(BswU2)9U                                                                                                   /* [139] ComConf_ComSignal_D00219 */
    ,(BswU2)10U                                                                                                  /* [140] ComConf_ComSignal_APPMD2 */
    ,(BswU2)10U                                                                                                  /* [141] ComConf_ComSignal_D00220 */
    ,(BswU2)10U                                                                                                  /* [142] ComConf_ComSignal_D00221 */
    ,(BswU2)10U                                                                                                  /* [143] ComConf_ComSignal_D00222 */
    ,(BswU2)10U                                                                                                  /* [144] ComConf_ComSignal_D00223 */
    ,(BswU2)10U                                                                                                  /* [145] ComConf_ComSignal_FV1C0_D */
    ,(BswU2)10U                                                                                                  /* [146] ComConf_ComSignal_KZK1C0_D */
    ,(BswU2)11U                                                                                                  /* [147] ComConf_ComSignal_ACCMAPP */
    ,(BswU2)11U                                                                                                  /* [148] ComConf_ComSignal_ACCMMOD */
    ,(BswU2)12U                                                                                                  /* [149] ComConf_ComSignal_ACCMDST */
    ,(BswU2)12U                                                                                                  /* [150] ComConf_ComSignal_ACCMPHS */
    ,(BswU2)12U                                                                                                  /* [151] ComConf_ComSignal_ACCMSGN */
    ,(BswU2)12U                                                                                                  /* [152] ComConf_ComSignal_ACCMRCG */
    ,(BswU2)12U                                                                                                  /* [153] ComConf_ComSignal_ACCMARB */
    ,(BswU2)13U                                                                                                  /* [154] ComConf_ComSignal_LDASTATL */
    ,(BswU2)13U                                                                                                  /* [155] ComConf_ComSignal_LDASTATR */
    ,(BswU2)13U                                                                                                  /* [156] ComConf_ComSignal_LDARSN */
    ,(BswU2)13U                                                                                                  /* [157] ComConf_ComSignal_FCMINTMP */
    ,(BswU2)13U                                                                                                  /* [158] ComConf_ComSignal_LDARCGL */
    ,(BswU2)13U                                                                                                  /* [159] ComConf_ComSignal_LDARCGR */
    ,(BswU2)13U                                                                                                  /* [160] ComConf_ComSignal_SWSSTAT */
    ,(BswU2)13U                                                                                                  /* [161] ComConf_ComSignal_V_IDACCL */
    ,(BswU2)13U                                                                                                  /* [162] ComConf_ComSignal_EJDEVPRD */
    ,(BswU2)13U                                                                                                  /* [163] ComConf_ComSignal_EJLDACP */
    ,(BswU2)13U                                                                                                  /* [164] ComConf_ComSignal_V_IDANOA */
    ,(BswU2)13U                                                                                                  /* [165] ComConf_ComSignal_V_IDARGL */
    ,(BswU2)13U                                                                                                  /* [166] ComConf_ComSignal_PV_AREA */
    ,(BswU2)13U                                                                                                  /* [167] ComConf_ComSignal_DM_PVMVW */
    ,(BswU2)13U                                                                                                  /* [168] ComConf_ComSignal_DM_PVMCS */
    ,(BswU2)13U                                                                                                  /* [169] ComConf_ComSignal_ERMCNTST */
    ,(BswU2)13U                                                                                                  /* [170] ComConf_ComSignal_GAE_H_R3 */
    ,(BswU2)13U                                                                                                  /* [171] ComConf_ComSignal_FRDHTR_G */
    ,(BswU2)13U                                                                                                  /* [172] ComConf_ComSignal_SDIRT_G */
    ,(BswU2)13U                                                                                                  /* [173] ComConf_ComSignal_GAE_V_R1 */
    ,(BswU2)13U                                                                                                  /* [174] ComConf_ComSignal_DRTCNT_G */
    ,(BswU2)13U                                                                                                  /* [175] ComConf_ComSignal_GAERR1_V */
    ,(BswU2)13U                                                                                                  /* [176] ComConf_ComSignal_GAEVAL_H */
    ,(BswU2)13U                                                                                                  /* [177] ComConf_ComSignal_GAERR3_H */
    ,(BswU2)13U                                                                                                  /* [178] ComConf_ComSignal_DTSSSTR */
    ,(BswU2)13U                                                                                                  /* [179] ComConf_ComSignal_DTSSLTID */
    ,(BswU2)13U                                                                                                  /* [180] ComConf_ComSignal_MDSYNC00 */
    ,(BswU2)14U                                                                                                  /* [181] ComConf_ComSignal_OTA2RSLT */
    ,(BswU2)14U                                                                                                  /* [182] ComConf_ComSignal_OTA3RSLT */
    ,(BswU2)14U                                                                                                  /* [183] ComConf_ComSignal_OTADRSLT */
    ,(BswU2)14U                                                                                                  /* [184] ComConf_ComSignal_SRVC_STT */
    ,(BswU2)14U                                                                                                  /* [185] ComConf_ComSignal_OTA2CNCL */
    ,(BswU2)14U                                                                                                  /* [186] ComConf_ComSignal_OTA3CNCL */
    ,(BswU2)14U                                                                                                  /* [187] ComConf_ComSignal_OTADCNCL */
    ,(BswU2)14U                                                                                                  /* [188] ComConf_ComSignal_CUR_DRV */
    ,(BswU2)14U                                                                                                  /* [189] ComConf_ComSignal_SRVC_PC */
    ,(BswU2)14U                                                                                                  /* [190] ComConf_ComSignal_SRVC_VC */
    ,(BswU2)14U                                                                                                  /* [191] ComConf_ComSignal_SRVC_AC */
    ,(BswU2)14U                                                                                                  /* [192] ComConf_ComSignal_OTAPPCTL */
    ,(BswU2)14U                                                                                                  /* [193] ComConf_ComSignal_CW_MD_SW */
    ,(BswU2)14U                                                                                                  /* [194] ComConf_ComSignal_VNHLDRQ */
    ,(BswU2)14U                                                                                                  /* [195] ComConf_ComSignal_TRNCASW */
    ,(BswU2)14U                                                                                                  /* [196] ComConf_ComSignal_TRNSD */
    ,(BswU2)14U                                                                                                  /* [197] ComConf_ComSignal_TRNFBPD */
    ,(BswU2)14U                                                                                                  /* [198] ComConf_ComSignal_OTACDRLT */
    ,(BswU2)14U                                                                                                  /* [199] ComConf_ComSignal_OTACHGEX */
    ,(BswU2)14U                                                                                                  /* [200] ComConf_ComSignal_OTAACTTP */
    ,(BswU2)14U                                                                                                  /* [201] ComConf_ComSignal_OTAACTPH */
    ,(BswU2)14U                                                                                                  /* [202] ComConf_ComSignal_OTASWACT */
    ,(BswU2)14U                                                                                                  /* [203] ComConf_ComSignal_OTASTAT */
    ,(BswU2)15U                                                                                                  /* [204] ComConf_ComSignal_BIB_G */
    ,(BswU2)15U                                                                                                  /* [205] ComConf_ComSignal_VCELMAXG */
    ,(BswU2)15U                                                                                                  /* [206] ComConf_ComSignal_VCELMING */
    ,(BswU2)15U                                                                                                  /* [207] ComConf_ComSignal_RAHRMAXG */
    ,(BswU2)15U                                                                                                  /* [208] ComConf_ComSignal_RAHRMING */
    ,(BswU2)15U                                                                                                  /* [209] ComConf_ComSignal_TC_G */
    ,(BswU2)15U                                                                                                  /* [210] ComConf_ComSignal_TBMAX_G */
    ,(BswU2)15U                                                                                                  /* [211] ComConf_ComSignal_TBMIN_G */
    ,(BswU2)15U                                                                                                  /* [212] ComConf_ComSignal_D00809 */
    ,(BswU2)15U                                                                                                  /* [213] ComConf_ComSignal_D00810 */
    ,(BswU2)15U                                                                                                  /* [214] ComConf_ComSignal_D00811 */
    ,(BswU2)16U                                                                                                  /* [215] ComConf_ComSignal_D_IB */
    ,(BswU2)16U                                                                                                  /* [216] ComConf_ComSignal_D_VB */
    ,(BswU2)16U                                                                                                  /* [217] ComConf_ComSignal_D_VBMAX */
    ,(BswU2)16U                                                                                                  /* [218] ComConf_ComSignal_D_VBMIN */
    ,(BswU2)16U                                                                                                  /* [219] ComConf_ComSignal_D_VMAXN */
    ,(BswU2)16U                                                                                                  /* [220] ComConf_ComSignal_D_VMINN */
    ,(BswU2)16U                                                                                                  /* [221] ComConf_ComSignal_D_TBMAX */
    ,(BswU2)16U                                                                                                  /* [222] ComConf_ComSignal_D_TBMIN */
    ,(BswU2)16U                                                                                                  /* [223] ComConf_ComSignal_D_TBMAXN */
    ,(BswU2)16U                                                                                                  /* [224] ComConf_ComSignal_D_TBMINN */
    ,(BswU2)16U                                                                                                  /* [225] ComConf_ComSignal_D_SOC */
    ,(BswU2)16U                                                                                                  /* [226] ComConf_ComSignal_D_BATENE */
    ,(BswU2)16U                                                                                                  /* [227] ComConf_ComSignal_D_BERG1 */
    ,(BswU2)16U                                                                                                  /* [228] ComConf_ComSignal_D_BERG2 */
    ,(BswU2)16U                                                                                                  /* [229] ComConf_ComSignal_D_BERG3 */
    ,(BswU2)16U                                                                                                  /* [230] ComConf_ComSignal_D_BALM_1 */
    ,(BswU2)16U                                                                                                  /* [231] ComConf_ComSignal_D_BALM_2 */
    ,(BswU2)16U                                                                                                  /* [232] ComConf_ComSignal_D_BALM_3 */
    ,(BswU2)16U                                                                                                  /* [233] ComConf_ComSignal_D_BALM_4 */
    ,(BswU2)16U                                                                                                  /* [234] ComConf_ComSignal_D_BALM_5 */
    ,(BswU2)16U                                                                                                  /* [235] ComConf_ComSignal_D_BCODE1 */
    ,(BswU2)16U                                                                                                  /* [236] ComConf_ComSignal_D_BCODE2 */
    ,(BswU2)16U                                                                                                  /* [237] ComConf_ComSignal_D_BCODE3 */
    ,(BswU2)16U                                                                                                  /* [238] ComConf_ComSignal_D_BCODE4 */
    ,(BswU2)16U                                                                                                  /* [239] ComConf_ComSignal_D_BCODE5 */
    ,(BswU2)16U                                                                                                  /* [240] ComConf_ComSignal_D_BCODE6 */
    ,(BswU2)16U                                                                                                  /* [241] ComConf_ComSignal_D_BCODE7 */
    ,(BswU2)16U                                                                                                  /* [242] ComConf_ComSignal_D_BCODE8 */
    ,(BswU2)17U                                                                                                  /* [243] ComConf_ComSignal_D_VCELCH */
    ,(BswU2)17U                                                                                                  /* [244] ComConf_ComSignal_D_VCELL0 */
    ,(BswU2)17U                                                                                                  /* [245] ComConf_ComSignal_D_VCELL1 */
    ,(BswU2)17U                                                                                                  /* [246] ComConf_ComSignal_D_VCELL2 */
    ,(BswU2)17U                                                                                                  /* [247] ComConf_ComSignal_D_VCELL3 */
    ,(BswU2)18U                                                                                                  /* [248] ComConf_ComSignal_D_TBCH */
    ,(BswU2)18U                                                                                                  /* [249] ComConf_ComSignal_D_TB0 */
    ,(BswU2)18U                                                                                                  /* [250] ComConf_ComSignal_D_TB1 */
    ,(BswU2)18U                                                                                                  /* [251] ComConf_ComSignal_D_TB2 */
    ,(BswU2)18U                                                                                                  /* [252] ComConf_ComSignal_D_TB3 */
    ,(BswU2)18U                                                                                                  /* [253] ComConf_ComSignal_D_TB4 */
    ,(BswU2)18U                                                                                                  /* [254] ComConf_ComSignal_D_TB5 */
    ,(BswU2)18U                                                                                                  /* [255] ComConf_ComSignal_D_TB6 */
    ,(BswU2)19U                                                                                                  /* [256] ComConf_ComSignal_D_MINFAD */
    ,(BswU2)19U                                                                                                  /* [257] ComConf_ComSignal_D_MINFO1 */
    ,(BswU2)19U                                                                                                  /* [258] ComConf_ComSignal_D_MINFO2 */
    ,(BswU2)19U                                                                                                  /* [259] ComConf_ComSignal_D_MINFO3 */
    ,(BswU2)20U                                                                                                  /* [260] ComConf_ComSignal_D_BVIN1 */
    ,(BswU2)20U                                                                                                  /* [261] ComConf_ComSignal_D_BVIN2 */
    ,(BswU2)20U                                                                                                  /* [262] ComConf_ComSignal_D_BVIN3 */
    ,(BswU2)20U                                                                                                  /* [263] ComConf_ComSignal_D_BVIN4 */
    ,(BswU2)20U                                                                                                  /* [264] ComConf_ComSignal_D_BVIN5 */
    ,(BswU2)20U                                                                                                  /* [265] ComConf_ComSignal_D_BVIN6 */
    ,(BswU2)20U                                                                                                  /* [266] ComConf_ComSignal_D_BVIN7 */
    ,(BswU2)20U                                                                                                  /* [267] ComConf_ComSignal_D_BVIN8 */
    ,(BswU2)20U                                                                                                  /* [268] ComConf_ComSignal_D_BVIN9 */
    ,(BswU2)20U                                                                                                  /* [269] ComConf_ComSignal_D_BVIN10 */
    ,(BswU2)20U                                                                                                  /* [270] ComConf_ComSignal_D_BVIN11 */
    ,(BswU2)20U                                                                                                  /* [271] ComConf_ComSignal_D_BVIN12 */
    ,(BswU2)20U                                                                                                  /* [272] ComConf_ComSignal_D_BVIN13 */
    ,(BswU2)20U                                                                                                  /* [273] ComConf_ComSignal_D_BVIN14 */
    ,(BswU2)20U                                                                                                  /* [274] ComConf_ComSignal_D_BVIN15 */
    ,(BswU2)20U                                                                                                  /* [275] ComConf_ComSignal_D_BVIN16 */
    ,(BswU2)20U                                                                                                  /* [276] ComConf_ComSignal_D_BVIN17 */
    ,(BswU2)20U                                                                                                  /* [277] ComConf_ComSignal_D_BVIN18 */
    ,(BswU2)20U                                                                                                  /* [278] ComConf_ComSignal_D_BVIN19 */
    ,(BswU2)20U                                                                                                  /* [279] ComConf_ComSignal_D_BVIN20 */
    ,(BswU2)20U                                                                                                  /* [280] ComConf_ComSignal_D_BVIN21 */
    ,(BswU2)20U                                                                                                  /* [281] ComConf_ComSignal_D_BVIN22 */
    ,(BswU2)20U                                                                                                  /* [282] ComConf_ComSignal_D_BVIN23 */
    ,(BswU2)20U                                                                                                  /* [283] ComConf_ComSignal_D_BVIN24 */
    ,(BswU2)21U                                                                                                  /* [284] ComConf_ComSignal_D00887 */
    ,(BswU2)21U                                                                                                  /* [285] ComConf_ComSignal_D00888 */
    ,(BswU2)21U                                                                                                  /* [286] ComConf_ComSignal_D00889 */
    ,(BswU2)21U                                                                                                  /* [287] ComConf_ComSignal_D00890 */
    ,(BswU2)21U                                                                                                  /* [288] ComConf_ComSignal_BTWO */
    ,(BswU2)21U                                                                                                  /* [289] ComConf_ComSignal_D00891 */
    ,(BswU2)21U                                                                                                  /* [290] ComConf_ComSignal_D00892 */
    ,(BswU2)21U                                                                                                  /* [291] ComConf_ComSignal_D00893 */
    ,(BswU2)21U                                                                                                  /* [292] ComConf_ComSignal_D00894 */
    ,(BswU2)21U                                                                                                  /* [293] ComConf_ComSignal_D00895 */
    ,(BswU2)22U                                                                                                  /* [294] ComConf_ComSignal_BITGB1 */
    ,(BswU2)22U                                                                                                  /* [295] ComConf_ComSignal_BITGB2 */
    ,(BswU2)22U                                                                                                  /* [296] ComConf_ComSignal_BITGB3 */
    ,(BswU2)22U                                                                                                  /* [297] ComConf_ComSignal_BITGB4 */
    ,(BswU2)22U                                                                                                  /* [298] ComConf_ComSignal_STKNUM */
    ,(BswU2)22U                                                                                                  /* [299] ComConf_ComSignal_BITGB5 */
    ,(BswU2)22U                                                                                                  /* [300] ComConf_ComSignal_VCELNUM */
    ,(BswU2)22U                                                                                                  /* [301] ComConf_ComSignal_INFGB1 */
    ,(BswU2)22U                                                                                                  /* [302] ComConf_ComSignal_TMINNUM */
    ,(BswU2)22U                                                                                                  /* [303] ComConf_ComSignal_INFGB2 */
    ,(BswU2)22U                                                                                                  /* [304] ComConf_ComSignal_TMAXNUM */
    ,(BswU2)22U                                                                                                  /* [305] ComConf_ComSignal_VBTINF */
    ,(BswU2)22U                                                                                                  /* [306] ComConf_ComSignal_SOCINF */
    ,(BswU2)22U                                                                                                  /* [307] ComConf_ComSignal_IBTINF */
    ,(BswU2)22U                                                                                                  /* [308] ComConf_ComSignal_TBTINF */
    ,(BswU2)22U                                                                                                  /* [309] ComConf_ComSignal_STPSOC */
    ,(BswU2)22U                                                                                                  /* [310] ComConf_ComSignal_STPVB */
    ,(BswU2)22U                                                                                                  /* [311] ComConf_ComSignal_STPCELV */
    ,(BswU2)22U                                                                                                  /* [312] ComConf_ComSignal_STPTMP */
    ,(BswU2)22U                                                                                                  /* [313] ComConf_ComSignal_DATAGB2 */
    ,(BswU2)22U                                                                                                  /* [314] ComConf_ComSignal_DATAGB3 */
    ,(BswU2)23U                                                                                                  /* [315] ComConf_ComSignal_ID63B16 */
    ,(BswU2)23U                                                                                                  /* [316] ComConf_ComSignal_IF63B16 */
    ,(BswU2)23U                                                                                                  /* [317] ComConf_ComSignal_TRIP_CNT */
    ,(BswU2)23U                                                                                                  /* [318] ComConf_ComSignal_TIME_CNT */
    ,(BswU2)24U                                                                                                  /* [319] ComConf_ComSignal_D01107 */
    ,(BswU2)24U                                                                                                  /* [320] ComConf_ComSignal_D01108 */
    ,(BswU2)24U                                                                                                  /* [321] ComConf_ComSignal_IL_FDOME */
    ,(BswU2)24U                                                                                                  /* [322] ComConf_ComSignal_IL_LOUNG */
    ,(BswU2)24U                                                                                                  /* [323] ComConf_ComSignal_IL_OSSTP */
    ,(BswU2)24U                                                                                                  /* [324] ComConf_ComSignal_AMB_COP */
    ,(BswU2)24U                                                                                                  /* [325] ComConf_ComSignal_SUPRQ */
    ,(BswU2)24U                                                                                                  /* [326] ComConf_ComSignal_D01109 */
    ,(BswU2)24U                                                                                                  /* [327] ComConf_ComSignal_D01110 */
    ,(BswU2)25U                                                                                                  /* [328] ComConf_ComSignal_D01215 */
    ,(BswU2)25U                                                                                                  /* [329] ComConf_ComSignal_D01216 */
    ,(BswU2)25U                                                                                                  /* [330] ComConf_ComSignal_D01217 */
    ,(BswU2)25U                                                                                                  /* [331] ComConf_ComSignal_D01218 */
    ,(BswU2)25U                                                                                                  /* [332] ComConf_ComSignal_D01219 */
    ,(BswU2)25U                                                                                                  /* [333] ComConf_ComSignal_D01220 */
    ,(BswU2)25U                                                                                                  /* [334] ComConf_ComSignal_D01221 */
    ,(BswU2)25U                                                                                                  /* [335] ComConf_ComSignal_D01222 */
    ,(BswU2)25U                                                                                                  /* [336] ComConf_ComSignal_D01223 */
    ,(BswU2)25U                                                                                                  /* [337] ComConf_ComSignal_D01224 */
    ,(BswU2)25U                                                                                                  /* [338] ComConf_ComSignal_AXSOC */
    ,(BswU2)25U                                                                                                  /* [339] ComConf_ComSignal_D01225 */
    ,(BswU2)25U                                                                                                  /* [340] ComConf_ComSignal_D01226 */
    ,(BswU2)25U                                                                                                  /* [341] ComConf_ComSignal_D01227 */
    ,(BswU2)25U                                                                                                  /* [342] ComConf_ComSignal_D01228 */
    ,(BswU2)25U                                                                                                  /* [343] ComConf_ComSignal_D01229 */
    ,(BswU2)25U                                                                                                  /* [344] ComConf_ComSignal_D01230 */
    ,(BswU2)25U                                                                                                  /* [345] ComConf_ComSignal_D01231 */
    ,(BswU2)25U                                                                                                  /* [346] ComConf_ComSignal_D01232 */
    ,(BswU2)25U                                                                                                  /* [347] ComConf_ComSignal_D01233 */
    ,(BswU2)25U                                                                                                  /* [348] ComConf_ComSignal_D01234 */
    ,(BswU2)25U                                                                                                  /* [349] ComConf_ComSignal_D01235 */
    ,(BswU2)25U                                                                                                  /* [350] ComConf_ComSignal_D01236 */
    ,(BswU2)25U                                                                                                  /* [351] ComConf_ComSignal_D01237 */
    ,(BswU2)25U                                                                                                  /* [352] ComConf_ComSignal_D01238 */
    ,(BswU2)25U                                                                                                  /* [353] ComConf_ComSignal_D01239 */
    ,(BswU2)25U                                                                                                  /* [354] ComConf_ComSignal_D01240 */
    ,(BswU2)25U                                                                                                  /* [355] ComConf_ComSignal_D01241 */
    ,(BswU2)25U                                                                                                  /* [356] ComConf_ComSignal_D01242 */
    ,(BswU2)25U                                                                                                  /* [357] ComConf_ComSignal_D01243 */
    ,(BswU2)25U                                                                                                  /* [358] ComConf_ComSignal_D01244 */
    ,(BswU2)25U                                                                                                  /* [359] ComConf_ComSignal_D01245 */
    ,(BswU2)25U                                                                                                  /* [360] ComConf_ComSignal_D01246 */
    ,(BswU2)25U                                                                                                  /* [361] ComConf_ComSignal_D01247 */
    ,(BswU2)25U                                                                                                  /* [362] ComConf_ComSignal_D01248 */
    ,(BswU2)25U                                                                                                  /* [363] ComConf_ComSignal_D01249 */
    ,(BswU2)25U                                                                                                  /* [364] ComConf_ComSignal_D01250 */
    ,(BswU2)25U                                                                                                  /* [365] ComConf_ComSignal_D01251 */
    ,(BswU2)25U                                                                                                  /* [366] ComConf_ComSignal_D01252 */
    ,(BswU2)25U                                                                                                  /* [367] ComConf_ComSignal_D01253 */
    ,(BswU2)25U                                                                                                  /* [368] ComConf_ComSignal_D01254 */
    ,(BswU2)25U                                                                                                  /* [369] ComConf_ComSignal_D01255 */
    ,(BswU2)25U                                                                                                  /* [370] ComConf_ComSignal_D01256 */
    ,(BswU2)25U                                                                                                  /* [371] ComConf_ComSignal_D01257 */
    ,(BswU2)25U                                                                                                  /* [372] ComConf_ComSignal_D01258 */
    ,(BswU2)25U                                                                                                  /* [373] ComConf_ComSignal_D01259 */
    ,(BswU2)25U                                                                                                  /* [374] ComConf_ComSignal_D01260 */
    ,(BswU2)25U                                                                                                  /* [375] ComConf_ComSignal_D01261 */
    ,(BswU2)25U                                                                                                  /* [376] ComConf_ComSignal_D01262 */
    ,(BswU2)25U                                                                                                  /* [377] ComConf_ComSignal_D01263 */
    ,(BswU2)26U                                                                                                  /* [378] ComConf_ComSignal_E_CRC1E3 */
    ,(BswU2)26U                                                                                                  /* [379] ComConf_ComSignal_E_CNT1E3 */
    ,(BswU2)26U                                                                                                  /* [380] ComConf_ComSignal_VPSINFO7 */
    ,(BswU2)26U                                                                                                  /* [381] ComConf_ComSignal_VPSINFO6 */
    ,(BswU2)26U                                                                                                  /* [382] ComConf_ComSignal_VPSINFO5 */
    ,(BswU2)26U                                                                                                  /* [383] ComConf_ComSignal_VPSINFO4 */
    ,(BswU2)26U                                                                                                  /* [384] ComConf_ComSignal_VPSINFO3 */
    ,(BswU2)26U                                                                                                  /* [385] ComConf_ComSignal_VPSINFO2 */
    ,(BswU2)26U                                                                                                  /* [386] ComConf_ComSignal_VPSINFO1 */
    ,(BswU2)26U                                                                                                  /* [387] ComConf_ComSignal_VPSINFOS */
    ,(BswU2)26U                                                                                                  /* [388] ComConf_ComSignal_VPSCNG */
    ,(BswU2)26U                                                                                                  /* [389] ComConf_ComSignal_VPSISOTA */
    ,(BswU2)26U                                                                                                  /* [390] ComConf_ComSignal_APOFRQ */
    ,(BswU2)26U                                                                                                  /* [391] ComConf_ComSignal_FV1E3_D */
    ,(BswU2)26U                                                                                                  /* [392] ComConf_ComSignal_KZK1E3_D */
    ,(BswU2)27U                                                                                                  /* [393] ComConf_ComSignal_E_CRC150 */
    ,(BswU2)27U                                                                                                  /* [394] ComConf_ComSignal_E_CNT150 */
    ,(BswU2)27U                                                                                                  /* [395] ComConf_ComSignal_PWRERRST */
    ,(BswU2)27U                                                                                                  /* [396] ComConf_ComSignal_CRLYOF */
    ,(BswU2)27U                                                                                                  /* [397] ComConf_ComSignal_D01300 */
    ,(BswU2)27U                                                                                                  /* [398] ComConf_ComSignal_D01301 */
    ,(BswU2)27U                                                                                                  /* [399] ComConf_ComSignal_D01302 */
    ,(BswU2)27U                                                                                                  /* [400] ComConf_ComSignal_D01303 */
    ,(BswU2)27U                                                                                                  /* [401] ComConf_ComSignal_D01304 */
    ,(BswU2)27U                                                                                                  /* [402] ComConf_ComSignal_D01305 */
    ,(BswU2)27U                                                                                                  /* [403] ComConf_ComSignal_FV150_D */
    ,(BswU2)27U                                                                                                  /* [404] ComConf_ComSignal_KZK150_D */
    ,(BswU2)28U                                                                                                  /* [405] ComConf_ComSignal_ST1 */
    ,(BswU2)28U                                                                                                  /* [406] ComConf_ComSignal_ST1PER */
    ,(BswU2)28U                                                                                                  /* [407] ComConf_ComSignal_ST2 */
    ,(BswU2)28U                                                                                                  /* [408] ComConf_ComSignal_ST2PER */
    ,(BswU2)28U                                                                                                  /* [409] ComConf_ComSignal_ST3 */
    ,(BswU2)28U                                                                                                  /* [410] ComConf_ComSignal_ST3PER */
    ,(BswU2)28U                                                                                                  /* [411] ComConf_ComSignal_ST4 */
    ,(BswU2)28U                                                                                                  /* [412] ComConf_ComSignal_ST4PER */
    ,(BswU2)28U                                                                                                  /* [413] ComConf_ComSignal_ST5 */
    ,(BswU2)28U                                                                                                  /* [414] ComConf_ComSignal_ST5PER */
    ,(BswU2)28U                                                                                                  /* [415] ComConf_ComSignal_ST6 */
    ,(BswU2)28U                                                                                                  /* [416] ComConf_ComSignal_ST6PER */
    ,(BswU2)28U                                                                                                  /* [417] ComConf_ComSignal_ST7 */
    ,(BswU2)28U                                                                                                  /* [418] ComConf_ComSignal_ST7PER */
    ,(BswU2)28U                                                                                                  /* [419] ComConf_ComSignal_ST8 */
    ,(BswU2)28U                                                                                                  /* [420] ComConf_ComSignal_ST8PER */
    ,(BswU2)28U                                                                                                  /* [421] ComConf_ComSignal_ST9 */
    ,(BswU2)28U                                                                                                  /* [422] ComConf_ComSignal_ST9PER */
    ,(BswU2)28U                                                                                                  /* [423] ComConf_ComSignal_ST10 */
    ,(BswU2)28U                                                                                                  /* [424] ComConf_ComSignal_ST10PER */
    ,(BswU2)28U                                                                                                  /* [425] ComConf_ComSignal_ST11 */
    ,(BswU2)28U                                                                                                  /* [426] ComConf_ComSignal_ST11PER */
    ,(BswU2)28U                                                                                                  /* [427] ComConf_ComSignal_ST12 */
    ,(BswU2)28U                                                                                                  /* [428] ComConf_ComSignal_ST12PER */
    ,(BswU2)28U                                                                                                  /* [429] ComConf_ComSignal_ST13 */
    ,(BswU2)28U                                                                                                  /* [430] ComConf_ComSignal_ST13PER */
    ,(BswU2)28U                                                                                                  /* [431] ComConf_ComSignal_ST14 */
    ,(BswU2)28U                                                                                                  /* [432] ComConf_ComSignal_ST14PER */
    ,(BswU2)28U                                                                                                  /* [433] ComConf_ComSignal_ST15 */
    ,(BswU2)28U                                                                                                  /* [434] ComConf_ComSignal_ST15PER */
    ,(BswU2)28U                                                                                                  /* [435] ComConf_ComSignal_ST16 */
    ,(BswU2)28U                                                                                                  /* [436] ComConf_ComSignal_ST16PER */
    ,(BswU2)28U                                                                                                  /* [437] ComConf_ComSignal_ST17 */
    ,(BswU2)28U                                                                                                  /* [438] ComConf_ComSignal_ST17PER */
    ,(BswU2)28U                                                                                                  /* [439] ComConf_ComSignal_ST18 */
    ,(BswU2)28U                                                                                                  /* [440] ComConf_ComSignal_ST18PER */
    ,(BswU2)29U                                                                                                  /* [441] ComConf_ComSignal_D01689 */
    ,(BswU2)29U                                                                                                  /* [442] ComConf_ComSignal_D01690 */
    ,(BswU2)29U                                                                                                  /* [443] ComConf_ComSignal_D01691 */
    ,(BswU2)29U                                                                                                  /* [444] ComConf_ComSignal_D01692 */
    ,(BswU2)29U                                                                                                  /* [445] ComConf_ComSignal_D01693 */
    ,(BswU2)29U                                                                                                  /* [446] ComConf_ComSignal_D01694 */
    ,(BswU2)29U                                                                                                  /* [447] ComConf_ComSignal_D01695 */
    ,(BswU2)29U                                                                                                  /* [448] ComConf_ComSignal_D01696 */
    ,(BswU2)29U                                                                                                  /* [449] ComConf_ComSignal_D01697 */
    ,(BswU2)29U                                                                                                  /* [450] ComConf_ComSignal_ACPRE_AD */
    ,(BswU2)29U                                                                                                  /* [451] ComConf_ComSignal_EXPMIP */
    ,(BswU2)29U                                                                                                  /* [452] ComConf_ComSignal_D01698 */
    ,(BswU2)29U                                                                                                  /* [453] ComConf_ComSignal_AMR */
    ,(BswU2)29U                                                                                                  /* [454] ComConf_ComSignal_MIP */
    ,(BswU2)29U                                                                                                  /* [455] ComConf_ComSignal_D01699 */
    ,(BswU2)29U                                                                                                  /* [456] ComConf_ComSignal_D01700 */
    ,(BswU2)29U                                                                                                  /* [457] ComConf_ComSignal_D01701 */
    ,(BswU2)29U                                                                                                  /* [458] ComConf_ComSignal_D01702 */
    ,(BswU2)29U                                                                                                  /* [459] ComConf_ComSignal_D01703 */
    ,(BswU2)29U                                                                                                  /* [460] ComConf_ComSignal_D01704 */
    ,(BswU2)29U                                                                                                  /* [461] ComConf_ComSignal_D01705 */
    ,(BswU2)29U                                                                                                  /* [462] ComConf_ComSignal_D01706 */
    ,(BswU2)29U                                                                                                  /* [463] ComConf_ComSignal_D01707 */
    ,(BswU2)29U                                                                                                  /* [464] ComConf_ComSignal_D01708 */
    ,(BswU2)29U                                                                                                  /* [465] ComConf_ComSignal_D01709 */
    ,(BswU2)29U                                                                                                  /* [466] ComConf_ComSignal_D01710 */
    ,(BswU2)29U                                                                                                  /* [467] ComConf_ComSignal_D01711 */
    ,(BswU2)29U                                                                                                  /* [468] ComConf_ComSignal_D01712 */
    ,(BswU2)29U                                                                                                  /* [469] ComConf_ComSignal_D01713 */
    ,(BswU2)29U                                                                                                  /* [470] ComConf_ComSignal_D01714 */
    ,(BswU2)29U                                                                                                  /* [471] ComConf_ComSignal_D01715 */
    ,(BswU2)29U                                                                                                  /* [472] ComConf_ComSignal_D01716 */
    ,(BswU2)29U                                                                                                  /* [473] ComConf_ComSignal_D01717 */
    ,(BswU2)29U                                                                                                  /* [474] ComConf_ComSignal_D01718 */
    ,(BswU2)29U                                                                                                  /* [475] ComConf_ComSignal_D01719 */
    ,(BswU2)29U                                                                                                  /* [476] ComConf_ComSignal_FV37B_D */
    ,(BswU2)29U                                                                                                  /* [477] ComConf_ComSignal_KZK37B_D */
    ,(BswU2)30U                                                                                                  /* [478] ComConf_ComSignal_D01720 */
    ,(BswU2)30U                                                                                                  /* [479] ComConf_ComSignal_D01721 */
    ,(BswU2)30U                                                                                                  /* [480] ComConf_ComSignal_D01722 */
    ,(BswU2)30U                                                                                                  /* [481] ComConf_ComSignal_D01723 */
    ,(BswU2)30U                                                                                                  /* [482] ComConf_ComSignal_D01724 */
    ,(BswU2)30U                                                                                                  /* [483] ComConf_ComSignal_D01725 */
    ,(BswU2)30U                                                                                                  /* [484] ComConf_ComSignal_D01726 */
    ,(BswU2)30U                                                                                                  /* [485] ComConf_ComSignal_D01727 */
    ,(BswU2)30U                                                                                                  /* [486] ComConf_ComSignal_D01728 */
    ,(BswU2)30U                                                                                                  /* [487] ComConf_ComSignal_D01729 */
    ,(BswU2)30U                                                                                                  /* [488] ComConf_ComSignal_D01730 */
    ,(BswU2)30U                                                                                                  /* [489] ComConf_ComSignal_D01731 */
    ,(BswU2)30U                                                                                                  /* [490] ComConf_ComSignal_D01732 */
    ,(BswU2)30U                                                                                                  /* [491] ComConf_ComSignal_D01733 */
    ,(BswU2)30U                                                                                                  /* [492] ComConf_ComSignal_D01734 */
    ,(BswU2)30U                                                                                                  /* [493] ComConf_ComSignal_D01735 */
    ,(BswU2)30U                                                                                                  /* [494] ComConf_ComSignal_D01736 */
    ,(BswU2)30U                                                                                                  /* [495] ComConf_ComSignal_D01737 */
    ,(BswU2)30U                                                                                                  /* [496] ComConf_ComSignal_D01738 */
    ,(BswU2)30U                                                                                                  /* [497] ComConf_ComSignal_HVH_ATPW */
    ,(BswU2)30U                                                                                                  /* [498] ComConf_ComSignal_D01739 */
    ,(BswU2)30U                                                                                                  /* [499] ComConf_ComSignal_D01740 */
    ,(BswU2)30U                                                                                                  /* [500] ComConf_ComSignal_D01741 */
    ,(BswU2)30U                                                                                                  /* [501] ComConf_ComSignal_D01742 */
    ,(BswU2)30U                                                                                                  /* [502] ComConf_ComSignal_D01743 */
    ,(BswU2)30U                                                                                                  /* [503] ComConf_ComSignal_D01744 */
    ,(BswU2)30U                                                                                                  /* [504] ComConf_ComSignal_D01745 */
    ,(BswU2)30U                                                                                                  /* [505] ComConf_ComSignal_D01746 */
    ,(BswU2)30U                                                                                                  /* [506] ComConf_ComSignal_D01747 */
    ,(BswU2)30U                                                                                                  /* [507] ComConf_ComSignal_D01748 */
    ,(BswU2)30U                                                                                                  /* [508] ComConf_ComSignal_D01749 */
    ,(BswU2)30U                                                                                                  /* [509] ComConf_ComSignal_D01750 */
    ,(BswU2)30U                                                                                                  /* [510] ComConf_ComSignal_D01751 */
    ,(BswU2)30U                                                                                                  /* [511] ComConf_ComSignal_D01752 */
    ,(BswU2)30U                                                                                                  /* [512] ComConf_ComSignal_D01753 */
    ,(BswU2)30U                                                                                                  /* [513] ComConf_ComSignal_D01754 */
    ,(BswU2)30U                                                                                                  /* [514] ComConf_ComSignal_D01755 */
    ,(BswU2)31U                                                                                                  /* [515] ComConf_ComSignal_D01764 */
    ,(BswU2)31U                                                                                                  /* [516] ComConf_ComSignal_D01765 */
    ,(BswU2)31U                                                                                                  /* [517] ComConf_ComSignal_D01766 */
    ,(BswU2)31U                                                                                                  /* [518] ComConf_ComSignal_D01767 */
    ,(BswU2)31U                                                                                                  /* [519] ComConf_ComSignal_COMPRP_A */
    ,(BswU2)31U                                                                                                  /* [520] ComConf_ComSignal_D01768 */
    ,(BswU2)31U                                                                                                  /* [521] ComConf_ComSignal_ACMODE_P */
    ,(BswU2)31U                                                                                                  /* [522] ComConf_ComSignal_D01769 */
    ,(BswU2)32U                                                                                                  /* [523] ComConf_ComSignal_ETHWU_21 */
    ,(BswU2)32U                                                                                                  /* [524] ComConf_ComSignal_ETHWU_23 */
    ,(BswU2)33U                                                                                                  /* [525] ComConf_ComSignal_HED_S */
    ,(BswU2)33U                                                                                                  /* [526] ComConf_ComSignal_TAL_S */
    ,(BswU2)33U                                                                                                  /* [527] ComConf_ComSignal_DRL_S */
    ,(BswU2)33U                                                                                                  /* [528] ComConf_ComSignal_AUT_S */
    ,(BswU2)33U                                                                                                  /* [529] ComConf_ComSignal_OFF_S */
    ,(BswU2)33U                                                                                                  /* [530] ComConf_ComSignal_AHB_S */
    ,(BswU2)33U                                                                                                  /* [531] ComConf_ComSignal_PAS_S */
    ,(BswU2)33U                                                                                                  /* [532] ComConf_ComSignal_HIB_S */
    ,(BswU2)33U                                                                                                  /* [533] ComConf_ComSignal_BW_S */
    ,(BswU2)33U                                                                                                  /* [534] ComConf_ComSignal_RFG_S */
    ,(BswU2)33U                                                                                                  /* [535] ComConf_ComSignal_FOG_S */
    ,(BswU2)33U                                                                                                  /* [536] ComConf_ComSignal_CRGL_S */
    ,(BswU2)33U                                                                                                  /* [537] ComConf_ComSignal_CRGR_S */
    ,(BswU2)33U                                                                                                  /* [538] ComConf_ComSignal_TRNL_S */
    ,(BswU2)33U                                                                                                  /* [539] ComConf_ComSignal_TRNR_S */
    ,(BswU2)33U                                                                                                  /* [540] ComConf_ComSignal_D02823 */
    ,(BswU2)33U                                                                                                  /* [541] ComConf_ComSignal_CXP_JDGT */
    ,(BswU2)34U                                                                                                  /* [542] ComConf_ComSignal_WVR_S */
    ,(BswU2)34U                                                                                                  /* [543] ComConf_ComSignal_WSW_S */
    ,(BswU2)34U                                                                                                  /* [544] ComConf_ComSignal_WRSW_S */
    ,(BswU2)34U                                                                                                  /* [545] ComConf_ComSignal_WRON_S */
    ,(BswU2)34U                                                                                                  /* [546] ComConf_ComSignal_WRIN_S */
    ,(BswU2)34U                                                                                                  /* [547] ComConf_ComSignal_WINT_S */
    ,(BswU2)34U                                                                                                  /* [548] ComConf_ComSignal_WMST_S */
    ,(BswU2)34U                                                                                                  /* [549] ComConf_ComSignal_WA_S */
    ,(BswU2)34U                                                                                                  /* [550] ComConf_ComSignal_WHI_S */
    ,(BswU2)34U                                                                                                  /* [551] ComConf_ComSignal_WLO_S */
    ,(BswU2)34U                                                                                                  /* [552] ComConf_ComSignal_WOFF_S */
    ,(BswU2)34U                                                                                                  /* [553] ComConf_ComSignal_WAI_S */
    ,(BswU2)34U                                                                                                  /* [554] ComConf_ComSignal_CXP_JDGW */
    ,(BswU2)35U                                                                                                  /* [555] ComConf_ComSignal_D02943 */
    ,(BswU2)35U                                                                                                  /* [556] ComConf_ComSignal_ETHWU_32 */
    ,(BswU2)36U                                                                                                  /* [557] ComConf_ComSignal_THR_GLOB */
    ,(BswU2)36U                                                                                                  /* [558] ComConf_ComSignal_TMO_GLOB */
    ,(BswU2)36U                                                                                                  /* [559] ComConf_ComSignal_TTA_GLOB */
    ,(BswU2)36U                                                                                                  /* [560] ComConf_ComSignal_RTA_GLOB */
    ,(BswU2)37U                                                                                                  /* [561] ComConf_ComSignal_TR_GLOB */
    ,(BswU2)37U                                                                                                  /* [562] ComConf_ComSignal_TM_GLOB */
    ,(BswU2)37U                                                                                                  /* [563] ComConf_ComSignal_NR_GLOB */
    ,(BswU2)37U                                                                                                  /* [564] ComConf_ComSignal_NM_GLOB */
    ,(BswU2)38U                                                                                                  /* [565] ComConf_ComSignal_D03097 */
    ,(BswU2)38U                                                                                                  /* [566] ComConf_ComSignal_NMRBR_MD */
    ,(BswU2)38U                                                                                                  /* [567] ComConf_ComSignal_BHSWEXT */
    ,(BswU2)38U                                                                                                  /* [568] ComConf_ComSignal_D03098 */
    ,(BswU2)38U                                                                                                  /* [569] ComConf_ComSignal_NMRBSWEX */
    ,(BswU2)38U                                                                                                  /* [570] ComConf_ComSignal_D03099 */
    ,(BswU2)39U                                                                                                  /* [571] ComConf_ComSignal_GRLGDBCR */
    ,(BswU2)39U                                                                                                  /* [572] ComConf_ComSignal_DMCNVINF */
    ,(BswU2)39U                                                                                                  /* [573] ComConf_ComSignal_CNV_MODE */
    ,(BswU2)39U                                                                                                  /* [574] ComConf_ComSignal_DMCNVVLD */
    ,(BswU2)40U                                                                                                  /* [575] ComConf_ComSignal_TEC */
    ,(BswU2)40U                                                                                                  /* [576] ComConf_ComSignal_DRVEC */
    ,(BswU2)40U                                                                                                  /* [577] ComConf_ComSignal_ALTEC */
    ,(BswU2)40U                                                                                                  /* [578] ComConf_ComSignal_ACEC */
    ,(BswU2)40U                                                                                                  /* [579] ComConf_ComSignal_BPEC */
    ,(BswU2)40U                                                                                                  /* [580] ComConf_ComSignal_DAEC */
    ,(BswU2)40U                                                                                                  /* [581] ComConf_ComSignal_CAEC */
    ,(BswU2)40U                                                                                                  /* [582] ComConf_ComSignal_CUMTEC */
    ,(BswU2)40U                                                                                                  /* [583] ComConf_ComSignal_CUMDRVEC */
    ,(BswU2)40U                                                                                                  /* [584] ComConf_ComSignal_CUMALTEC */
    ,(BswU2)40U                                                                                                  /* [585] ComConf_ComSignal_CUMACEC */
    ,(BswU2)41U                                                                                                  /* [586] ComConf_ComSignal_CUMBPEC */
    ,(BswU2)41U                                                                                                  /* [587] ComConf_ComSignal_CUMDAEC */
    ,(BswU2)41U                                                                                                  /* [588] ComConf_ComSignal_CUMCAEC */
    ,(BswU2)41U                                                                                                  /* [589] ComConf_ComSignal_CUMTEC1 */
    ,(BswU2)41U                                                                                                  /* [590] ComConf_ComSignal_CUMTEC2 */
    ,(BswU2)41U                                                                                                  /* [591] ComConf_ComSignal_CRDRVEC1 */
    ,(BswU2)41U                                                                                                  /* [592] ComConf_ComSignal_CRDRVEC2 */
    ,(BswU2)41U                                                                                                  /* [593] ComConf_ComSignal_CRALTEC1 */
    ,(BswU2)41U                                                                                                  /* [594] ComConf_ComSignal_CRALTEC2 */
    ,(BswU2)41U                                                                                                  /* [595] ComConf_ComSignal_CRACEC1 */
    ,(BswU2)41U                                                                                                  /* [596] ComConf_ComSignal_CRACEC2 */
    ,(BswU2)41U                                                                                                  /* [597] ComConf_ComSignal_CRPACEC1 */
    ,(BswU2)41U                                                                                                  /* [598] ComConf_ComSignal_CRPACEC2 */
    ,(BswU2)41U                                                                                                  /* [599] ComConf_ComSignal_CRBPEC1 */
    ,(BswU2)41U                                                                                                  /* [600] ComConf_ComSignal_CRBPEC2 */
    ,(BswU2)41U                                                                                                  /* [601] ComConf_ComSignal_CRPBPEC1 */
    ,(BswU2)41U                                                                                                  /* [602] ComConf_ComSignal_CRPBPEC2 */
    ,(BswU2)41U                                                                                                  /* [603] ComConf_ComSignal_CRDAEC1 */
    ,(BswU2)41U                                                                                                  /* [604] ComConf_ComSignal_CRDAEC2 */
    ,(BswU2)41U                                                                                                  /* [605] ComConf_ComSignal_CRPAEC1 */
    ,(BswU2)41U                                                                                                  /* [606] ComConf_ComSignal_CRPAEC2 */
    ,(BswU2)42U                                                                                                  /* [607] ComConf_ComSignal_RSISDKME */
    ,(BswU2)42U                                                                                                  /* [608] ComConf_ComSignal_RSISIDDK */
    ,(BswU2)42U                                                                                                  /* [609] ComConf_ComSignal_D04459 */
    ,(BswU2)42U                                                                                                  /* [610] ComConf_ComSignal_D04460 */
    ,(BswU2)43U                                                                                                  /* [611] ComConf_ComSignal_D04514 */
    ,(BswU2)43U                                                                                                  /* [612] ComConf_ComSignal_DESMUTE */
    ,(BswU2)44U                                                                                                  /* [613] ComConf_ComSignal_DREBUID */
    ,(BswU2)44U                                                                                                  /* [614] ComConf_ComSignal_DREBU02 */
    ,(BswU2)44U                                                                                                  /* [615] ComConf_ComSignal_DREBU03 */
    ,(BswU2)44U                                                                                                  /* [616] ComConf_ComSignal_DREBU04 */
    ,(BswU2)44U                                                                                                  /* [617] ComConf_ComSignal_DREBU05 */
    ,(BswU2)44U                                                                                                  /* [618] ComConf_ComSignal_DREBU06 */
    ,(BswU2)44U                                                                                                  /* [619] ComConf_ComSignal_DREBU07 */
    ,(BswU2)44U                                                                                                  /* [620] ComConf_ComSignal_DREBU08 */
    ,(BswU2)44U                                                                                                  /* [621] ComConf_ComSignal_DREBU11 */
    ,(BswU2)44U                                                                                                  /* [622] ComConf_ComSignal_DREBU12 */
    ,(BswU2)44U                                                                                                  /* [623] ComConf_ComSignal_DREBU13 */
    ,(BswU2)44U                                                                                                  /* [624] ComConf_ComSignal_DREBU14 */
    ,(BswU2)44U                                                                                                  /* [625] ComConf_ComSignal_DREBU15 */
    ,(BswU2)44U                                                                                                  /* [626] ComConf_ComSignal_DREBU16 */
    ,(BswU2)44U                                                                                                  /* [627] ComConf_ComSignal_DREBU17 */
    ,(BswU2)44U                                                                                                  /* [628] ComConf_ComSignal_DREBU18 */
    ,(BswU2)44U                                                                                                  /* [629] ComConf_ComSignal_DREBU21 */
    ,(BswU2)44U                                                                                                  /* [630] ComConf_ComSignal_DREBU22 */
    ,(BswU2)44U                                                                                                  /* [631] ComConf_ComSignal_DREBU23 */
    ,(BswU2)44U                                                                                                  /* [632] ComConf_ComSignal_DREBU24 */
    ,(BswU2)44U                                                                                                  /* [633] ComConf_ComSignal_DREBU25 */
    ,(BswU2)44U                                                                                                  /* [634] ComConf_ComSignal_DREBU26 */
    ,(BswU2)44U                                                                                                  /* [635] ComConf_ComSignal_DREBU27 */
    ,(BswU2)44U                                                                                                  /* [636] ComConf_ComSignal_DREBU28 */
    ,(BswU2)44U                                                                                                  /* [637] ComConf_ComSignal_DREBU31 */
    ,(BswU2)44U                                                                                                  /* [638] ComConf_ComSignal_DREBU32 */
    ,(BswU2)44U                                                                                                  /* [639] ComConf_ComSignal_DREBU33 */
    ,(BswU2)44U                                                                                                  /* [640] ComConf_ComSignal_DREBU34 */
    ,(BswU2)44U                                                                                                  /* [641] ComConf_ComSignal_DREBU35 */
    ,(BswU2)44U                                                                                                  /* [642] ComConf_ComSignal_DREBU36 */
    ,(BswU2)44U                                                                                                  /* [643] ComConf_ComSignal_DREBU37 */
    ,(BswU2)44U                                                                                                  /* [644] ComConf_ComSignal_DREBU38 */
    ,(BswU2)45U                                                                                                  /* [645] ComConf_ComSignal_DRDYSTS */
    ,(BswU2)45U                                                                                                  /* [646] ComConf_ComSignal_DRDYB */
    ,(BswU2)46U                                                                                                  /* [647] ComConf_ComSignal_D04741 */
    ,(BswU2)46U                                                                                                  /* [648] ComConf_ComSignal_STRGCM */
    ,(BswU2)46U                                                                                                  /* [649] ComConf_ComSignal_D04742 */
    ,(BswU2)46U                                                                                                  /* [650] ComConf_ComSignal_D04743 */
    ,(BswU2)46U                                                                                                  /* [651] ComConf_ComSignal_D04744 */
    ,(BswU2)46U                                                                                                  /* [652] ComConf_ComSignal_D04745 */
    ,(BswU2)46U                                                                                                  /* [653] ComConf_ComSignal_D04746 */
    ,(BswU2)46U                                                                                                  /* [654] ComConf_ComSignal_D04747 */
    ,(BswU2)46U                                                                                                  /* [655] ComConf_ComSignal_D04748 */
    ,(BswU2)46U                                                                                                  /* [656] ComConf_ComSignal_D04749 */
    ,(BswU2)47U                                                                                                  /* [657] ComConf_ComSignal_HV_SRGMD */
    ,(BswU2)47U                                                                                                  /* [658] ComConf_ComSignal_D04800 */
    ,(BswU2)47U                                                                                                  /* [659] ComConf_ComSignal_D04801 */
    ,(BswU2)47U                                                                                                  /* [660] ComConf_ComSignal_TQRR */
    ,(BswU2)47U                                                                                                  /* [661] ComConf_ComSignal_D04802 */
    ,(BswU2)47U                                                                                                  /* [662] ComConf_ComSignal_TQFR */
    ,(BswU2)47U                                                                                                  /* [663] ComConf_ComSignal_D04803 */
    ,(BswU2)47U                                                                                                  /* [664] ComConf_ComSignal_D04804 */
    ,(BswU2)48U                                                                                                  /* [665] ComConf_ComSignal_FCRF */
    ,(BswU2)48U                                                                                                  /* [666] ComConf_ComSignal_CLE_SOCF */
    ,(BswU2)48U                                                                                                  /* [667] ComConf_ComSignal_D04860 */
    ,(BswU2)48U                                                                                                  /* [668] ComConf_ComSignal_D04861 */
    ,(BswU2)49U                                                                                                  /* [669] ComConf_ComSignal_E_CRC075 */
    ,(BswU2)49U                                                                                                  /* [670] ComConf_ComSignal_E_CNT075 */
    ,(BswU2)49U                                                                                                  /* [671] ComConf_ComSignal_D04900 */
    ,(BswU2)49U                                                                                                  /* [672] ComConf_ComSignal_SDRVRR */
    ,(BswU2)49U                                                                                                  /* [673] ComConf_ComSignal_D04901 */
    ,(BswU2)49U                                                                                                  /* [674] ComConf_ComSignal_D04902 */
    ,(BswU2)49U                                                                                                  /* [675] ComConf_ComSignal_SDRVFR */
    ,(BswU2)49U                                                                                                  /* [676] ComConf_ComSignal_D04903 */
    ,(BswU2)49U                                                                                                  /* [677] ComConf_ComSignal_D04904 */
    ,(BswU2)49U                                                                                                  /* [678] ComConf_ComSignal_D04905 */
    ,(BswU2)50U                                                                                                  /* [679] ComConf_ComSignal_E_CRC0A1 */
    ,(BswU2)50U                                                                                                  /* [680] ComConf_ComSignal_E_CNT0A1 */
    ,(BswU2)50U                                                                                                  /* [681] ComConf_ComSignal_D04906 */
    ,(BswU2)50U                                                                                                  /* [682] ComConf_ComSignal_D04907 */
    ,(BswU2)50U                                                                                                  /* [683] ComConf_ComSignal_HVMRADRR */
    ,(BswU2)50U                                                                                                  /* [684] ComConf_ComSignal_HVMRADFR */
    ,(BswU2)51U                                                                                                  /* [685] ComConf_ComSignal_D05101 */
    ,(BswU2)51U                                                                                                  /* [686] ComConf_ComSignal_DREIMABN */
    ,(BswU2)52U                                                                                                  /* [687] ComConf_ComSignal_I_BAT_BD */
    ,(BswU2)52U                                                                                                  /* [688] ComConf_ComSignal_U_BAT_BD */
    ,(BswU2)52U                                                                                                  /* [689] ComConf_ComSignal_PWDTY_BD */
    ,(BswU2)52U                                                                                                  /* [690] ComConf_ComSignal_VLO_BD */
    ,(BswU2)52U                                                                                                  /* [691] ComConf_ComSignal_PWIF1_BD */
    ,(BswU2)53U                                                                                                  /* [692] ComConf_ComSignal_T_BAT_BD */
    ,(BswU2)53U                                                                                                  /* [693] ComConf_ComSignal_PWIF2_BD */
    ,(BswU2)53U                                                                                                  /* [694] ComConf_ComSignal_SOCS_BD */
    ,(BswU2)53U                                                                                                  /* [695] ComConf_ComSignal_SOC_BD */
    ,(BswU2)53U                                                                                                  /* [696] ComConf_ComSignal_PWIF3_BD */
    ,(BswU2)53U                                                                                                  /* [697] ComConf_ComSignal_PWIF4_BD */
    ,(BswU2)53U                                                                                                  /* [698] ComConf_ComSignal_PWIF5_BD */
    ,(BswU2)54U                                                                                                  /* [699] ComConf_ComSignal_DRENG11 */
    ,(BswU2)54U                                                                                                  /* [700] ComConf_ComSignal_DRENG12 */
    ,(BswU2)54U                                                                                                  /* [701] ComConf_ComSignal_DRENG13 */
    ,(BswU2)54U                                                                                                  /* [702] ComConf_ComSignal_DRENG14 */
    ,(BswU2)54U                                                                                                  /* [703] ComConf_ComSignal_DRENG15 */
    ,(BswU2)54U                                                                                                  /* [704] ComConf_ComSignal_DRENG16 */
    ,(BswU2)54U                                                                                                  /* [705] ComConf_ComSignal_DRENG17 */
    ,(BswU2)54U                                                                                                  /* [706] ComConf_ComSignal_DRENG18 */
    ,(BswU2)55U                                                                                                  /* [707] ComConf_ComSignal_DRENG21 */
    ,(BswU2)55U                                                                                                  /* [708] ComConf_ComSignal_DRENG22 */
    ,(BswU2)55U                                                                                                  /* [709] ComConf_ComSignal_DRENG23 */
    ,(BswU2)55U                                                                                                  /* [710] ComConf_ComSignal_DRENG24 */
    ,(BswU2)55U                                                                                                  /* [711] ComConf_ComSignal_DRENG25 */
    ,(BswU2)55U                                                                                                  /* [712] ComConf_ComSignal_DRENG26 */
    ,(BswU2)55U                                                                                                  /* [713] ComConf_ComSignal_DRENG27 */
    ,(BswU2)55U                                                                                                  /* [714] ComConf_ComSignal_DRENG28 */
    ,(BswU2)56U                                                                                                  /* [715] ComConf_ComSignal_DRENG31 */
    ,(BswU2)56U                                                                                                  /* [716] ComConf_ComSignal_DRENG32 */
    ,(BswU2)56U                                                                                                  /* [717] ComConf_ComSignal_DRENG33 */
    ,(BswU2)56U                                                                                                  /* [718] ComConf_ComSignal_DRENG34 */
    ,(BswU2)56U                                                                                                  /* [719] ComConf_ComSignal_DRENG35 */
    ,(BswU2)56U                                                                                                  /* [720] ComConf_ComSignal_DRENG36 */
    ,(BswU2)56U                                                                                                  /* [721] ComConf_ComSignal_DRENG37 */
    ,(BswU2)56U                                                                                                  /* [722] ComConf_ComSignal_DRENG38 */
    ,(BswU2)57U                                                                                                  /* [723] ComConf_ComSignal_DRENG51 */
    ,(BswU2)57U                                                                                                  /* [724] ComConf_ComSignal_DRENG52 */
    ,(BswU2)57U                                                                                                  /* [725] ComConf_ComSignal_DRENG53 */
    ,(BswU2)57U                                                                                                  /* [726] ComConf_ComSignal_DRENG54 */
    ,(BswU2)57U                                                                                                  /* [727] ComConf_ComSignal_DRENG55 */
    ,(BswU2)57U                                                                                                  /* [728] ComConf_ComSignal_DRENG56 */
    ,(BswU2)57U                                                                                                  /* [729] ComConf_ComSignal_DRENG57 */
    ,(BswU2)57U                                                                                                  /* [730] ComConf_ComSignal_DRENG58 */
    ,(BswU2)58U                                                                                                  /* [731] ComConf_ComSignal_DRENG61 */
    ,(BswU2)58U                                                                                                  /* [732] ComConf_ComSignal_DRENG62 */
    ,(BswU2)58U                                                                                                  /* [733] ComConf_ComSignal_DRENG63 */
    ,(BswU2)58U                                                                                                  /* [734] ComConf_ComSignal_DRENG64 */
    ,(BswU2)58U                                                                                                  /* [735] ComConf_ComSignal_DRENG65 */
    ,(BswU2)58U                                                                                                  /* [736] ComConf_ComSignal_DRENG66 */
    ,(BswU2)58U                                                                                                  /* [737] ComConf_ComSignal_DRENG67 */
    ,(BswU2)58U                                                                                                  /* [738] ComConf_ComSignal_DRENG68 */
    ,(BswU2)59U                                                                                                  /* [739] ComConf_ComSignal_DRENG91 */
    ,(BswU2)59U                                                                                                  /* [740] ComConf_ComSignal_DRENG92 */
    ,(BswU2)59U                                                                                                  /* [741] ComConf_ComSignal_DRENG93 */
    ,(BswU2)59U                                                                                                  /* [742] ComConf_ComSignal_DRENG94 */
    ,(BswU2)59U                                                                                                  /* [743] ComConf_ComSignal_DRENG95 */
    ,(BswU2)59U                                                                                                  /* [744] ComConf_ComSignal_DRENG96 */
    ,(BswU2)59U                                                                                                  /* [745] ComConf_ComSignal_DRENG97 */
    ,(BswU2)59U                                                                                                  /* [746] ComConf_ComSignal_DRENG98 */
    ,(BswU2)60U                                                                                                  /* [747] ComConf_ComSignal_DRENG101 */
    ,(BswU2)60U                                                                                                  /* [748] ComConf_ComSignal_DRENG102 */
    ,(BswU2)60U                                                                                                  /* [749] ComConf_ComSignal_DRENG103 */
    ,(BswU2)60U                                                                                                  /* [750] ComConf_ComSignal_DRENG104 */
    ,(BswU2)60U                                                                                                  /* [751] ComConf_ComSignal_DRENG105 */
    ,(BswU2)60U                                                                                                  /* [752] ComConf_ComSignal_DRENG106 */
    ,(BswU2)60U                                                                                                  /* [753] ComConf_ComSignal_DRENG107 */
    ,(BswU2)60U                                                                                                  /* [754] ComConf_ComSignal_DRENG108 */
    ,(BswU2)61U                                                                                                  /* [755] ComConf_ComSignal_VIN_1 */
    ,(BswU2)61U                                                                                                  /* [756] ComConf_ComSignal_VIN_2 */
    ,(BswU2)61U                                                                                                  /* [757] ComConf_ComSignal_VIN_3 */
    ,(BswU2)61U                                                                                                  /* [758] ComConf_ComSignal_VIN_4 */
    ,(BswU2)61U                                                                                                  /* [759] ComConf_ComSignal_VIN_5 */
    ,(BswU2)61U                                                                                                  /* [760] ComConf_ComSignal_VIN_6 */
    ,(BswU2)61U                                                                                                  /* [761] ComConf_ComSignal_VIN_7 */
    ,(BswU2)61U                                                                                                  /* [762] ComConf_ComSignal_VIN_8 */
    ,(BswU2)61U                                                                                                  /* [763] ComConf_ComSignal_VIN_9 */
    ,(BswU2)61U                                                                                                  /* [764] ComConf_ComSignal_VIN_10 */
    ,(BswU2)61U                                                                                                  /* [765] ComConf_ComSignal_VIN_11 */
    ,(BswU2)61U                                                                                                  /* [766] ComConf_ComSignal_VIN_12 */
    ,(BswU2)61U                                                                                                  /* [767] ComConf_ComSignal_VIN_13 */
    ,(BswU2)61U                                                                                                  /* [768] ComConf_ComSignal_VIN_14 */
    ,(BswU2)61U                                                                                                  /* [769] ComConf_ComSignal_VIN_15 */
    ,(BswU2)61U                                                                                                  /* [770] ComConf_ComSignal_VIN_16 */
    ,(BswU2)61U                                                                                                  /* [771] ComConf_ComSignal_VIN_17 */
    ,(BswU2)61U                                                                                                  /* [772] ComConf_ComSignal_D05112 */
    ,(BswU2)61U                                                                                                  /* [773] ComConf_ComSignal_D05113 */
    ,(BswU2)62U                                                                                                  /* [774] ComConf_ComSignal_DREPS01 */
    ,(BswU2)62U                                                                                                  /* [775] ComConf_ComSignal_DREPS02 */
    ,(BswU2)62U                                                                                                  /* [776] ComConf_ComSignal_DREPS03 */
    ,(BswU2)62U                                                                                                  /* [777] ComConf_ComSignal_DREPS04 */
    ,(BswU2)62U                                                                                                  /* [778] ComConf_ComSignal_DREPS05 */
    ,(BswU2)62U                                                                                                  /* [779] ComConf_ComSignal_DREPS06 */
    ,(BswU2)62U                                                                                                  /* [780] ComConf_ComSignal_DREPS07 */
    ,(BswU2)62U                                                                                                  /* [781] ComConf_ComSignal_DREPS08 */
    ,(BswU2)63U                                                                                                  /* [782] ComConf_ComSignal_V_DIST */
    ,(BswU2)63U                                                                                                  /* [783] ComConf_ComSignal_V_RELV */
    ,(BswU2)63U                                                                                                  /* [784] ComConf_ComSignal_V_SWOP */
    ,(BswU2)63U                                                                                                  /* [785] ComConf_ComSignal_USMREQG */
    ,(BswU2)63U                                                                                                  /* [786] ComConf_ComSignal_RCURVR */
    ,(BswU2)63U                                                                                                  /* [787] ComConf_ComSignal_USMDSTTS */
    ,(BswU2)63U                                                                                                  /* [788] ComConf_ComSignal_COFFSET */
    ,(BswU2)63U                                                                                                  /* [789] ComConf_ComSignal_USMDSTSL */
    ,(BswU2)63U                                                                                                  /* [790] ComConf_ComSignal_RSACAUF */
    ,(BswU2)64U                                                                                                  /* [791] ComConf_ComSignal_OTHVW */
    ,(BswU2)64U                                                                                                  /* [792] ComConf_ComSignal_OTHVH */
    ,(BswU2)64U                                                                                                  /* [793] ComConf_ComSignal_OTHPB */
    ,(BswU2)64U                                                                                                  /* [794] ComConf_ComSignal_OTHTTC */
    ,(BswU2)64U                                                                                                  /* [795] ComConf_ComSignal_OTHTTYP */
    ,(BswU2)64U                                                                                                  /* [796] ComConf_ComSignal_D05167 */
    ,(BswU2)64U                                                                                                  /* [797] ComConf_ComSignal_D05168 */
    ,(BswU2)64U                                                                                                  /* [798] ComConf_ComSignal_FSPCSSTA */
    ,(BswU2)64U                                                                                                  /* [799] ComConf_ComSignal_HITPOS */
    ,(BswU2)64U                                                                                                  /* [800] ComConf_ComSignal_OTHRDANG */
    ,(BswU2)64U                                                                                                  /* [801] ComConf_ComSignal_D05169 */
    ,(BswU2)64U                                                                                                  /* [802] ComConf_ComSignal_D05170 */
    ,(BswU2)64U                                                                                                  /* [803] ComConf_ComSignal_D05171 */
    ,(BswU2)64U                                                                                                  /* [804] ComConf_ComSignal_OTHTSSST */
    ,(BswU2)64U                                                                                                  /* [805] ComConf_ComSignal_D05172 */
    ,(BswU2)64U                                                                                                  /* [806] ComConf_ComSignal_D05173 */
    ,(BswU2)64U                                                                                                  /* [807] ComConf_ComSignal_D05174 */
    ,(BswU2)64U                                                                                                  /* [808] ComConf_ComSignal_D05175 */
    ,(BswU2)64U                                                                                                  /* [809] ComConf_ComSignal_D05176 */
    ,(BswU2)64U                                                                                                  /* [810] ComConf_ComSignal_D05177 */
    ,(BswU2)64U                                                                                                  /* [811] ComConf_ComSignal_OTHOVLPC */
    ,(BswU2)64U                                                                                                  /* [812] ComConf_ComSignal_OTHRVPC */
    ,(BswU2)65U                                                                                                  /* [813] ComConf_ComSignal_OTHFALD */
    ,(BswU2)65U                                                                                                  /* [814] ComConf_ComSignal_OTHCOND */
    ,(BswU2)65U                                                                                                  /* [815] ComConf_ComSignal_OTHLDIS */
    ,(BswU2)65U                                                                                                  /* [816] ComConf_ComSignal_OTHFALF */
    ,(BswU2)65U                                                                                                  /* [817] ComConf_ComSignal_OTHCONF */
    ,(BswU2)65U                                                                                                  /* [818] ComConf_ComSignal_OTHLANE */
    ,(BswU2)66U                                                                                                  /* [819] ComConf_ComSignal_OTHSOR */
    ,(BswU2)66U                                                                                                  /* [820] ComConf_ComSignal_OTHROR */
    ,(BswU2)66U                                                                                                  /* [821] ComConf_ComSignal_OTHLX */
    ,(BswU2)66U                                                                                                  /* [822] ComConf_ComSignal_OTHSOLAR */
    ,(BswU2)66U                                                                                                  /* [823] ComConf_ComSignal_D05194 */
    ,(BswU2)66U                                                                                                  /* [824] ComConf_ComSignal_D05195 */
    ,(BswU2)67U                                                                                                  /* [825] ComConf_ComSignal_D05196 */
    ,(BswU2)67U                                                                                                  /* [826] ComConf_ComSignal_D05197 */
    ,(BswU2)67U                                                                                                  /* [827] ComConf_ComSignal_D05198 */
    ,(BswU2)67U                                                                                                  /* [828] ComConf_ComSignal_D05199 */
    ,(BswU2)67U                                                                                                  /* [829] ComConf_ComSignal_XREQFPB */
    ,(BswU2)67U                                                                                                  /* [830] ComConf_ComSignal_XREQPB */
    ,(BswU2)67U                                                                                                  /* [831] ComConf_ComSignal_D05200 */
    ,(BswU2)67U                                                                                                  /* [832] ComConf_ComSignal_D05201 */
    ,(BswU2)67U                                                                                                  /* [833] ComConf_ComSignal_XREQPBH */
    ,(BswU2)67U                                                                                                  /* [834] ComConf_ComSignal_D05202 */
    ,(BswU2)67U                                                                                                  /* [835] ComConf_ComSignal_D05203 */
    ,(BswU2)67U                                                                                                  /* [836] ComConf_ComSignal_D05204 */
    ,(BswU2)67U                                                                                                  /* [837] ComConf_ComSignal_D05205 */
    ,(BswU2)67U                                                                                                  /* [838] ComConf_ComSignal_D05206 */
    ,(BswU2)67U                                                                                                  /* [839] ComConf_ComSignal_D05207 */
    ,(BswU2)67U                                                                                                  /* [840] ComConf_ComSignal_D05208 */
    ,(BswU2)67U                                                                                                  /* [841] ComConf_ComSignal_D05209 */
    ,(BswU2)67U                                                                                                  /* [842] ComConf_ComSignal_D05210 */
    ,(BswU2)67U                                                                                                  /* [843] ComConf_ComSignal_D05211 */
    ,(BswU2)67U                                                                                                  /* [844] ComConf_ComSignal_D05212 */
    ,(BswU2)67U                                                                                                  /* [845] ComConf_ComSignal_D05213 */
    ,(BswU2)67U                                                                                                  /* [846] ComConf_ComSignal_D05214 */
    ,(BswU2)67U                                                                                                  /* [847] ComConf_ComSignal_D05215 */
    ,(BswU2)67U                                                                                                  /* [848] ComConf_ComSignal_D05216 */
    ,(BswU2)68U                                                                                                  /* [849] ComConf_ComSignal_AVSTRGR */
    ,(BswU2)68U                                                                                                  /* [850] ComConf_ComSignal_PBATRGR */
    ,(BswU2)68U                                                                                                  /* [851] ComConf_ComSignal_D05217 */
    ,(BswU2)68U                                                                                                  /* [852] ComConf_ComSignal_D05218 */
    ,(BswU2)68U                                                                                                  /* [853] ComConf_ComSignal_PCSALM */
    ,(BswU2)68U                                                                                                  /* [854] ComConf_ComSignal_D05219 */
    ,(BswU2)68U                                                                                                  /* [855] ComConf_ComSignal_D05220 */
    ,(BswU2)68U                                                                                                  /* [856] ComConf_ComSignal_D05221 */
    ,(BswU2)68U                                                                                                  /* [857] ComConf_ComSignal_D05222 */
    ,(BswU2)68U                                                                                                  /* [858] ComConf_ComSignal_D05223 */
    ,(BswU2)68U                                                                                                  /* [859] ComConf_ComSignal_D05224 */
    ,(BswU2)68U                                                                                                  /* [860] ComConf_ComSignal_D05225 */
    ,(BswU2)68U                                                                                                  /* [861] ComConf_ComSignal_D05226 */
    ,(BswU2)68U                                                                                                  /* [862] ComConf_ComSignal_D05227 */
    ,(BswU2)68U                                                                                                  /* [863] ComConf_ComSignal_D05228 */
    ,(BswU2)68U                                                                                                  /* [864] ComConf_ComSignal_D05229 */
    ,(BswU2)68U                                                                                                  /* [865] ComConf_ComSignal_D05230 */
    ,(BswU2)68U                                                                                                  /* [866] ComConf_ComSignal_D05231 */
    ,(BswU2)68U                                                                                                  /* [867] ComConf_ComSignal_D05232 */
    ,(BswU2)68U                                                                                                  /* [868] ComConf_ComSignal_D05233 */
    ,(BswU2)68U                                                                                                  /* [869] ComConf_ComSignal_D05234 */
    ,(BswU2)68U                                                                                                  /* [870] ComConf_ComSignal_D05235 */
    ,(BswU2)68U                                                                                                  /* [871] ComConf_ComSignal_D05236 */
    ,(BswU2)68U                                                                                                  /* [872] ComConf_ComSignal_D05237 */
    ,(BswU2)68U                                                                                                  /* [873] ComConf_ComSignal_D05238 */
    ,(BswU2)68U                                                                                                  /* [874] ComConf_ComSignal_D05239 */
    ,(BswU2)68U                                                                                                  /* [875] ComConf_ComSignal_D05240 */
    ,(BswU2)68U                                                                                                  /* [876] ComConf_ComSignal_D05241 */
    ,(BswU2)68U                                                                                                  /* [877] ComConf_ComSignal_D05242 */
    ,(BswU2)68U                                                                                                  /* [878] ComConf_ComSignal_D05243 */
    ,(BswU2)68U                                                                                                  /* [879] ComConf_ComSignal_D05244 */
    ,(BswU2)68U                                                                                                  /* [880] ComConf_ComSignal_D05245 */
    ,(BswU2)68U                                                                                                  /* [881] ComConf_ComSignal_D05246 */
    ,(BswU2)68U                                                                                                  /* [882] ComConf_ComSignal_D05247 */
    ,(BswU2)68U                                                                                                  /* [883] ComConf_ComSignal_D05248 */
    ,(BswU2)68U                                                                                                  /* [884] ComConf_ComSignal_D05249 */
    ,(BswU2)68U                                                                                                  /* [885] ComConf_ComSignal_D05250 */
    ,(BswU2)68U                                                                                                  /* [886] ComConf_ComSignal_D05251 */
    ,(BswU2)68U                                                                                                  /* [887] ComConf_ComSignal_D05252 */
    ,(BswU2)68U                                                                                                  /* [888] ComConf_ComSignal_D05253 */
    ,(BswU2)68U                                                                                                  /* [889] ComConf_ComSignal_D05254 */
    ,(BswU2)68U                                                                                                  /* [890] ComConf_ComSignal_D05255 */
    ,(BswU2)68U                                                                                                  /* [891] ComConf_ComSignal_D05256 */
    ,(BswU2)68U                                                                                                  /* [892] ComConf_ComSignal_D05257 */
    ,(BswU2)68U                                                                                                  /* [893] ComConf_ComSignal_FV0A8_D */
    ,(BswU2)68U                                                                                                  /* [894] ComConf_ComSignal_KZK0A8_D */
    ,(BswU2)69U                                                                                                  /* [895] ComConf_ComSignal_LK_ST */
    ,(BswU2)69U                                                                                                  /* [896] ComConf_ComSignal_LK_FUNC */
    ,(BswU2)69U                                                                                                  /* [897] ComConf_ComSignal_ULK_ST */
    ,(BswU2)69U                                                                                                  /* [898] ComConf_ComSignal_ULK_FUNC */
    ,(BswU2)70U                                                                                                  /* [899] ComConf_ComSignal_RSISIDME */
    ,(BswU2)70U                                                                                                  /* [900] ComConf_ComSignal_RSISIDID */
    ,(BswU2)70U                                                                                                  /* [901] ComConf_ComSignal_D05283 */
    ,(BswU2)70U                                                                                                  /* [902] ComConf_ComSignal_D05284 */
    ,(BswU2)71U                                                                                                  /* [903] ComConf_ComSignal_ODO_UNIT */
    ,(BswU2)71U                                                                                                  /* [904] ComConf_ComSignal_ODO */
    ,(BswU2)72U                                                                                                  /* [905] ComConf_ComSignal_RTQRRLMG */
    ,(BswU2)72U                                                                                                  /* [906] ComConf_ComSignal_RTQFRLMG */
    ,(BswU2)73U                                                                                                  /* [907] ComConf_ComSignal_BAOF_PDC */
    ,(BswU2)74U                                                                                                  /* [908] ComConf_ComSignal_SIDPWC0 */
    ,(BswU2)74U                                                                                                  /* [909] ComConf_ComSignal_SIDPWC1 */
    ,(BswU2)74U                                                                                                  /* [910] ComConf_ComSignal_SIDPWC2 */
    ,(BswU2)74U                                                                                                  /* [911] ComConf_ComSignal_SIDPWC3 */
    ,(BswU2)74U                                                                                                  /* [912] ComConf_ComSignal_SIDPWC4 */
    ,(BswU2)74U                                                                                                  /* [913] ComConf_ComSignal_SIDPWC5 */
    ,(BswU2)74U                                                                                                  /* [914] ComConf_ComSignal_SIDPWC6 */
    ,(BswU2)74U                                                                                                  /* [915] ComConf_ComSignal_SIDPWC7 */
    ,(BswU2)74U                                                                                                  /* [916] ComConf_ComSignal_SIDPWC8 */
    ,(BswU2)74U                                                                                                  /* [917] ComConf_ComSignal_SIDPWC9 */
    ,(BswU2)74U                                                                                                  /* [918] ComConf_ComSignal_SIDPWC10 */
    ,(BswU2)74U                                                                                                  /* [919] ComConf_ComSignal_SIDPWC11 */
    ,(BswU2)74U                                                                                                  /* [920] ComConf_ComSignal_SIDPWC12 */
    ,(BswU2)74U                                                                                                  /* [921] ComConf_ComSignal_SIDPWC13 */
    ,(BswU2)74U                                                                                                  /* [922] ComConf_ComSignal_SIDPWC14 */
    ,(BswU2)74U                                                                                                  /* [923] ComConf_ComSignal_SIDPWC15 */
    ,(BswU2)74U                                                                                                  /* [924] ComConf_ComSignal_SIDPWC16 */
    ,(BswU2)74U                                                                                                  /* [925] ComConf_ComSignal_SIDPWC17 */
    ,(BswU2)74U                                                                                                  /* [926] ComConf_ComSignal_SIDPWC18 */
    ,(BswU2)74U                                                                                                  /* [927] ComConf_ComSignal_SIDPWC19 */
    ,(BswU2)74U                                                                                                  /* [928] ComConf_ComSignal_SIDPWC20 */
    ,(BswU2)74U                                                                                                  /* [929] ComConf_ComSignal_SIDPWC21 */
    ,(BswU2)74U                                                                                                  /* [930] ComConf_ComSignal_SIDPWC22 */
    ,(BswU2)74U                                                                                                  /* [931] ComConf_ComSignal_SIDPWC23 */
    ,(BswU2)74U                                                                                                  /* [932] ComConf_ComSignal_SIDPWC24 */
    ,(BswU2)74U                                                                                                  /* [933] ComConf_ComSignal_SIDPWC25 */
    ,(BswU2)74U                                                                                                  /* [934] ComConf_ComSignal_SIDPWC26 */
    ,(BswU2)74U                                                                                                  /* [935] ComConf_ComSignal_SIDPWC27 */
    ,(BswU2)74U                                                                                                  /* [936] ComConf_ComSignal_SIDPWC28 */
    ,(BswU2)74U                                                                                                  /* [937] ComConf_ComSignal_SIDPWC29 */
    ,(BswU2)74U                                                                                                  /* [938] ComConf_ComSignal_SIDPWC30 */
    ,(BswU2)74U                                                                                                  /* [939] ComConf_ComSignal_SIDPWC31 */
    ,(BswU2)75U                                                                                                  /* [940] ComConf_ComSignal_E_CRC14F */
    ,(BswU2)75U                                                                                                  /* [941] ComConf_ComSignal_E_CNT14F */
    ,(BswU2)75U                                                                                                  /* [942] ComConf_ComSignal_RCPMD */
    ,(BswU2)75U                                                                                                  /* [943] ComConf_ComSignal_D05993 */
    ,(BswU2)75U                                                                                                  /* [944] ComConf_ComSignal_RCPFAIL */
    ,(BswU2)75U                                                                                                  /* [945] ComConf_ComSignal_D05994 */
    ,(BswU2)75U                                                                                                  /* [946] ComConf_ComSignal_D05995 */
    ,(BswU2)75U                                                                                                  /* [947] ComConf_ComSignal_D05996 */
    ,(BswU2)75U                                                                                                  /* [948] ComConf_ComSignal_RCPONST */
    ,(BswU2)75U                                                                                                  /* [949] ComConf_ComSignal_D05997 */
    ,(BswU2)75U                                                                                                  /* [950] ComConf_ComSignal_D05998 */
    ,(BswU2)76U                                                                                                  /* [951] ComConf_ComSignal_D_YEAR */
    ,(BswU2)76U                                                                                                  /* [952] ComConf_ComSignal_D_MONT */
    ,(BswU2)76U                                                                                                  /* [953] ComConf_ComSignal_D_DAY */
    ,(BswU2)76U                                                                                                  /* [954] ComConf_ComSignal_D_HOUR */
    ,(BswU2)76U                                                                                                  /* [955] ComConf_ComSignal_D_MIN */
    ,(BswU2)76U                                                                                                  /* [956] ComConf_ComSignal_D_SEC */
    ,(BswU2)77U                                                                                                  /* [957] ComConf_ComSignal_D06040 */
    ,(BswU2)77U                                                                                                  /* [958] ComConf_ComSignal_D06041 */
    ,(BswU2)77U                                                                                                  /* [959] ComConf_ComSignal_D06042 */
    ,(BswU2)77U                                                                                                  /* [960] ComConf_ComSignal_D06043 */
    ,(BswU2)77U                                                                                                  /* [961] ComConf_ComSignal_D06044 */
    ,(BswU2)77U                                                                                                  /* [962] ComConf_ComSignal_LATUDE */
    ,(BswU2)77U                                                                                                  /* [963] ComConf_ComSignal_LOTUDE1 */
    ,(BswU2)77U                                                                                                  /* [964] ComConf_ComSignal_D06045 */
    ,(BswU2)77U                                                                                                  /* [965] ComConf_ComSignal_D06046 */
    ,(BswU2)77U                                                                                                  /* [966] ComConf_ComSignal_D_LAT1 */
    ,(BswU2)77U                                                                                                  /* [967] ComConf_ComSignal_D_LAT2 */
    ,(BswU2)78U                                                                                                  /* [968] ComConf_ComSignal_D06047 */
    ,(BswU2)78U                                                                                                  /* [969] ComConf_ComSignal_D06048 */
    ,(BswU2)78U                                                                                                  /* [970] ComConf_ComSignal_D06049 */
    ,(BswU2)78U                                                                                                  /* [971] ComConf_ComSignal_D_LON1 */
    ,(BswU2)78U                                                                                                  /* [972] ComConf_ComSignal_D_LON2 */
    ,(BswU2)79U                                                                                                  /* [973] ComConf_ComSignal_D06050 */
    ,(BswU2)79U                                                                                                  /* [974] ComConf_ComSignal_D06051 */
    ,(BswU2)79U                                                                                                  /* [975] ComConf_ComSignal_D06052 */
    ,(BswU2)79U                                                                                                  /* [976] ComConf_ComSignal_D06053 */
    ,(BswU2)79U                                                                                                  /* [977] ComConf_ComSignal_ALTITUDE */
    ,(BswU2)80U                                                                                                  /* [978] ComConf_ComSignal_OTADTYPE */
    ,(BswU2)80U                                                                                                  /* [979] ComConf_ComSignal_OTADSTAT */
    ,(BswU2)80U                                                                                                  /* [980] ComConf_ComSignal_OTADPROG */
    ,(BswU2)80U                                                                                                  /* [981] ComConf_ComSignal_OTADERR */
    ,(BswU2)81U                                                                                                  /* [982] ComConf_ComSignal_RSCYCL11 */
    ,(BswU2)81U                                                                                                  /* [983] ComConf_ComSignal_RSCYCL12 */
    ,(BswU2)81U                                                                                                  /* [984] ComConf_ComSignal_RSCYCL13 */
    ,(BswU2)81U                                                                                                  /* [985] ComConf_ComSignal_RSCYCL14 */
    ,(BswU2)81U                                                                                                  /* [986] ComConf_ComSignal_RSCYCL15 */
    ,(BswU2)81U                                                                                                  /* [987] ComConf_ComSignal_RSCYCL16 */
    ,(BswU2)82U                                                                                                  /* [988] ComConf_ComSignal_FRVH */
    ,(BswU2)82U                                                                                                  /* [989] ComConf_ComSignal_FLVH */
    ,(BswU2)82U                                                                                                  /* [990] ComConf_ComSignal_RRVH */
    ,(BswU2)82U                                                                                                  /* [991] ComConf_ComSignal_RLVH */
    ,(BswU2)82U                                                                                                  /* [992] ComConf_ComSignal_D06161 */
    ,(BswU2)82U                                                                                                  /* [993] ComConf_ComSignal_D06162 */
    ,(BswU2)82U                                                                                                  /* [994] ComConf_ComSignal_D06163 */
    ,(BswU2)82U                                                                                                  /* [995] ComConf_ComSignal_D06164 */
    ,(BswU2)82U                                                                                                  /* [996] ComConf_ComSignal_D06165 */
    ,(BswU2)82U                                                                                                  /* [997] ComConf_ComSignal_D06166 */
    ,(BswU2)82U                                                                                                  /* [998] ComConf_ComSignal_D06167 */
    ,(BswU2)82U                                                                                                  /* [999] ComConf_ComSignal_D06168 */
    ,(BswU2)82U                                                                                                  /* [1000] ComConf_ComSignal_D06169 */
    ,(BswU2)82U                                                                                                  /* [1001] ComConf_ComSignal_D06170 */
    ,(BswU2)82U                                                                                                  /* [1002] ComConf_ComSignal_D06171 */
    ,(BswU2)82U                                                                                                  /* [1003] ComConf_ComSignal_D06172 */
    ,(BswU2)82U                                                                                                  /* [1004] ComConf_ComSignal_D06173 */
    ,(BswU2)82U                                                                                                  /* [1005] ComConf_ComSignal_D06174 */
    ,(BswU2)82U                                                                                                  /* [1006] ComConf_ComSignal_D06175 */
    ,(BswU2)82U                                                                                                  /* [1007] ComConf_ComSignal_D06176 */
    ,(BswU2)82U                                                                                                  /* [1008] ComConf_ComSignal_D06177 */
    ,(BswU2)82U                                                                                                  /* [1009] ComConf_ComSignal_D06178 */
    ,(BswU2)82U                                                                                                  /* [1010] ComConf_ComSignal_D06179 */
    ,(BswU2)82U                                                                                                  /* [1011] ComConf_ComSignal_D06180 */
    ,(BswU2)83U                                                                                                  /* [1012] ComConf_ComSignal_DVGR01 */
    ,(BswU2)83U                                                                                                  /* [1013] ComConf_ComSignal_DVGR02 */
    ,(BswU2)83U                                                                                                  /* [1014] ComConf_ComSignal_DVGR03 */
    ,(BswU2)83U                                                                                                  /* [1015] ComConf_ComSignal_DVGR04 */
    ,(BswU2)83U                                                                                                  /* [1016] ComConf_ComSignal_DVGR05 */
    ,(BswU2)83U                                                                                                  /* [1017] ComConf_ComSignal_DVGR06 */
    ,(BswU2)83U                                                                                                  /* [1018] ComConf_ComSignal_DVGR07 */
    ,(BswU2)83U                                                                                                  /* [1019] ComConf_ComSignal_DVGR08 */
    ,(BswU2)83U                                                                                                  /* [1020] ComConf_ComSignal_DVGR09 */
    ,(BswU2)83U                                                                                                  /* [1021] ComConf_ComSignal_DVGR10 */
    ,(BswU2)83U                                                                                                  /* [1022] ComConf_ComSignal_DVGR11 */
    ,(BswU2)83U                                                                                                  /* [1023] ComConf_ComSignal_DVGR12 */
    ,(BswU2)83U                                                                                                  /* [1024] ComConf_ComSignal_DVGR13 */
    ,(BswU2)83U                                                                                                  /* [1025] ComConf_ComSignal_DVGR14 */
    ,(BswU2)83U                                                                                                  /* [1026] ComConf_ComSignal_DVGR15 */
    ,(BswU2)83U                                                                                                  /* [1027] ComConf_ComSignal_DVGR16 */
    ,(BswU2)83U                                                                                                  /* [1028] ComConf_ComSignal_DVGR17 */
    ,(BswU2)83U                                                                                                  /* [1029] ComConf_ComSignal_DVGR18 */
    ,(BswU2)83U                                                                                                  /* [1030] ComConf_ComSignal_DVGR19 */
    ,(BswU2)83U                                                                                                  /* [1031] ComConf_ComSignal_DVGR20 */
    ,(BswU2)83U                                                                                                  /* [1032] ComConf_ComSignal_DVGR21 */
    ,(BswU2)83U                                                                                                  /* [1033] ComConf_ComSignal_DVGR22 */
    ,(BswU2)83U                                                                                                  /* [1034] ComConf_ComSignal_DVGR23 */
    ,(BswU2)83U                                                                                                  /* [1035] ComConf_ComSignal_DVGR24 */
    ,(BswU2)83U                                                                                                  /* [1036] ComConf_ComSignal_DVGR25 */
    ,(BswU2)83U                                                                                                  /* [1037] ComConf_ComSignal_DVGR26 */
    ,(BswU2)83U                                                                                                  /* [1038] ComConf_ComSignal_DVGR27 */
    ,(BswU2)83U                                                                                                  /* [1039] ComConf_ComSignal_DVGR28 */
    ,(BswU2)83U                                                                                                  /* [1040] ComConf_ComSignal_DVGR29 */
    ,(BswU2)83U                                                                                                  /* [1041] ComConf_ComSignal_DVGR30 */
    ,(BswU2)83U                                                                                                  /* [1042] ComConf_ComSignal_DVGR31 */
    ,(BswU2)83U                                                                                                  /* [1043] ComConf_ComSignal_DVGR32 */
    ,(BswU2)84U                                                                                                  /* [1044] ComConf_ComSignal_DRVSCID */
    ,(BswU2)84U                                                                                                  /* [1045] ComConf_ComSignal_DRVSC02 */
    ,(BswU2)84U                                                                                                  /* [1046] ComConf_ComSignal_DRVSC03 */
    ,(BswU2)84U                                                                                                  /* [1047] ComConf_ComSignal_DRVSC04 */
    ,(BswU2)84U                                                                                                  /* [1048] ComConf_ComSignal_DRVSC05 */
    ,(BswU2)84U                                                                                                  /* [1049] ComConf_ComSignal_DRVSC06 */
    ,(BswU2)84U                                                                                                  /* [1050] ComConf_ComSignal_DRVSC07 */
    ,(BswU2)84U                                                                                                  /* [1051] ComConf_ComSignal_DRVSC08 */
    ,(BswU2)84U                                                                                                  /* [1052] ComConf_ComSignal_DRVSC11 */
    ,(BswU2)84U                                                                                                  /* [1053] ComConf_ComSignal_DRVSC12 */
    ,(BswU2)84U                                                                                                  /* [1054] ComConf_ComSignal_DRVSC13 */
    ,(BswU2)84U                                                                                                  /* [1055] ComConf_ComSignal_DRVSC14 */
    ,(BswU2)84U                                                                                                  /* [1056] ComConf_ComSignal_DRVSC15 */
    ,(BswU2)84U                                                                                                  /* [1057] ComConf_ComSignal_DRVSC16 */
    ,(BswU2)84U                                                                                                  /* [1058] ComConf_ComSignal_DRVSC17 */
    ,(BswU2)84U                                                                                                  /* [1059] ComConf_ComSignal_DRVSC18 */
    ,(BswU2)84U                                                                                                  /* [1060] ComConf_ComSignal_DRVSC21 */
    ,(BswU2)84U                                                                                                  /* [1061] ComConf_ComSignal_DRVSC22 */
    ,(BswU2)84U                                                                                                  /* [1062] ComConf_ComSignal_DRVSC23 */
    ,(BswU2)84U                                                                                                  /* [1063] ComConf_ComSignal_DRVSC24 */
    ,(BswU2)84U                                                                                                  /* [1064] ComConf_ComSignal_DRVSC25 */
    ,(BswU2)84U                                                                                                  /* [1065] ComConf_ComSignal_DRVSC26 */
    ,(BswU2)84U                                                                                                  /* [1066] ComConf_ComSignal_DRVSC27 */
    ,(BswU2)84U                                                                                                  /* [1067] ComConf_ComSignal_DRVSC28 */
    ,(BswU2)84U                                                                                                  /* [1068] ComConf_ComSignal_DREPB01 */
    ,(BswU2)84U                                                                                                  /* [1069] ComConf_ComSignal_DREPB02 */
    ,(BswU2)84U                                                                                                  /* [1070] ComConf_ComSignal_DREPB03 */
    ,(BswU2)84U                                                                                                  /* [1071] ComConf_ComSignal_DREPB04 */
    ,(BswU2)84U                                                                                                  /* [1072] ComConf_ComSignal_DREPB05 */
    ,(BswU2)84U                                                                                                  /* [1073] ComConf_ComSignal_DREPB06 */
    ,(BswU2)84U                                                                                                  /* [1074] ComConf_ComSignal_DREPB07 */
    ,(BswU2)84U                                                                                                  /* [1075] ComConf_ComSignal_DREPB08 */
    ,(BswU2)85U                                                                                                  /* [1076] ComConf_ComSignal_E_CRC09E */
    ,(BswU2)85U                                                                                                  /* [1077] ComConf_ComSignal_E_CNT09E */
    ,(BswU2)85U                                                                                                  /* [1078] ComConf_ComSignal_SP1S */
    ,(BswU2)85U                                                                                                  /* [1079] ComConf_ComSignal_GVSPDINV */
    ,(BswU2)85U                                                                                                  /* [1080] ComConf_ComSignal_SP1P */
    ,(BswU2)85U                                                                                                  /* [1081] ComConf_ComSignal_SP1 */
    ,(BswU2)85U                                                                                                  /* [1082] ComConf_ComSignal_GVSPD */
    ,(BswU2)85U                                                                                                  /* [1083] ComConf_ComSignal_D06272 */
    ,(BswU2)85U                                                                                                  /* [1084] ComConf_ComSignal_D06273 */
    ,(BswU2)85U                                                                                                  /* [1085] ComConf_ComSignal_D06274 */
    ,(BswU2)85U                                                                                                  /* [1086] ComConf_ComSignal_D06275 */
    ,(BswU2)85U                                                                                                  /* [1087] ComConf_ComSignal_PWCF */
    ,(BswU2)85U                                                                                                  /* [1088] ComConf_ComSignal_PWC */
    ,(BswU2)85U                                                                                                  /* [1089] ComConf_ComSignal_D06276 */
    ,(BswU2)85U                                                                                                  /* [1090] ComConf_ComSignal_PWCS */
    ,(BswU2)85U                                                                                                  /* [1091] ComConf_ComSignal_PMCF */
    ,(BswU2)85U                                                                                                  /* [1092] ComConf_ComSignal_PMCS */
    ,(BswU2)85U                                                                                                  /* [1093] ComConf_ComSignal_PMC */
    ,(BswU2)85U                                                                                                  /* [1094] ComConf_ComSignal_D06277 */
    ,(BswU2)85U                                                                                                  /* [1095] ComConf_ComSignal_D06278 */
    ,(BswU2)85U                                                                                                  /* [1096] ComConf_ComSignal_D06279 */
    ,(BswU2)85U                                                                                                  /* [1097] ComConf_ComSignal_D06280 */
    ,(BswU2)85U                                                                                                  /* [1098] ComConf_ComSignal_D06281 */
    ,(BswU2)85U                                                                                                  /* [1099] ComConf_ComSignal_D06282 */
    ,(BswU2)85U                                                                                                  /* [1100] ComConf_ComSignal_D06283 */
    ,(BswU2)85U                                                                                                  /* [1101] ComConf_ComSignal_D06284 */
    ,(BswU2)85U                                                                                                  /* [1102] ComConf_ComSignal_D06285 */
    ,(BswU2)85U                                                                                                  /* [1103] ComConf_ComSignal_D06286 */
    ,(BswU2)85U                                                                                                  /* [1104] ComConf_ComSignal_D06287 */
    ,(BswU2)85U                                                                                                  /* [1105] ComConf_ComSignal_D06288 */
    ,(BswU2)85U                                                                                                  /* [1106] ComConf_ComSignal_D06289 */
    ,(BswU2)85U                                                                                                  /* [1107] ComConf_ComSignal_FV09E_D */
    ,(BswU2)85U                                                                                                  /* [1108] ComConf_ComSignal_KZK09E_D */
    ,(BswU2)86U                                                                                                  /* [1109] ComConf_ComSignal_FRWIPOPE */
    ,(BswU2)86U                                                                                                  /* [1110] ComConf_ComSignal_FRWASH */
    ,(BswU2)86U                                                                                                  /* [1111] ComConf_ComSignal_RRWIPOPE */
    ,(BswU2)86U                                                                                                  /* [1112] ComConf_ComSignal_RRWASH */
    ,(BswU2)86U                                                                                                  /* [1113] ComConf_ComSignal_D06704 */
    ,(BswU2)87U                                                                                                  /* [1114] ComConf_ComSignal_W_STPZ */
    ,(BswU2)87U                                                                                                  /* [1115] ComConf_ComSignal_FI_STP */
    ,(BswU2)87U                                                                                                  /* [1116] ComConf_ComSignal_D06773 */
    ,(BswU2)87U                                                                                                  /* [1117] ComConf_ComSignal_FV086_D */
    ,(BswU2)87U                                                                                                  /* [1118] ComConf_ComSignal_KZK086_D */
    ,(BswU2)88U                                                                                                  /* [1119] ComConf_ComSignal_RECRNOFF */
    ,(BswU2)88U                                                                                                  /* [1120] ComConf_ComSignal_FAV_FNC */
    ,(BswU2)88U                                                                                                  /* [1121] ComConf_ComSignal_CHG_FUNC */
    ,(BswU2)88U                                                                                                  /* [1122] ComConf_ComSignal_GSNSOFF */
    ,(BswU2)88U                                                                                                  /* [1123] ComConf_ComSignal_DRBDBABN */
    ,(BswU2)89U                                                                                                  /* [1124] ComConf_ComSignal_R_AC_ST */
    ,(BswU2)89U                                                                                                  /* [1125] ComConf_ComSignal_R_SYS_2 */
    ,(BswU2)90U                                                                                                  /* [1126] ComConf_ComSignal_R_FTE_ST */
    ,(BswU2)90U                                                                                                  /* [1127] ComConf_ComSignal_R_BD_ST */
    ,(BswU2)90U                                                                                                  /* [1128] ComConf_ComSignal_R_TIME */
    ,(BswU2)91U                                                                                                  /* [1129] ComConf_ComSignal_R_INT_ST */
    ,(BswU2)92U                                                                                                  /* [1130] ComConf_ComSignal_R_LMP_ST */
    ,(BswU2)92U                                                                                                  /* [1131] ComConf_ComSignal_R_SDE_ST */
    ,(BswU2)92U                                                                                                  /* [1132] ComConf_ComSignal_R_SYS_3 */
    ,(BswU2)93U                                                                                                  /* [1133] ComConf_ComSignal_R_ST_ST */
    ,(BswU2)93U                                                                                                  /* [1134] ComConf_ComSignal_R_SYS_1 */
    ,(BswU2)94U                                                                                                  /* [1135] ComConf_ComSignal_EIC_EQP */
    ,(BswU2)94U                                                                                                  /* [1136] ComConf_ComSignal_EIC_FEQP */
    ,(BswU2)94U                                                                                                  /* [1137] ComConf_ComSignal_EIC_SEQP */
    ,(BswU2)94U                                                                                                  /* [1138] ComConf_ComSignal_EIC_IEQP */
    ,(BswU2)94U                                                                                                  /* [1139] ComConf_ComSignal_EIC_BEQP */
    ,(BswU2)94U                                                                                                  /* [1140] ComConf_ComSignal_QIC_BREQ */
    ,(BswU2)94U                                                                                                  /* [1141] ComConf_ComSignal_QIC_DISP */
    ,(BswU2)94U                                                                                                  /* [1142] ComConf_ComSignal_QIC_BVOL */
    ,(BswU2)94U                                                                                                  /* [1143] ComConf_ComSignal_QIC_DIS */
    ,(BswU2)94U                                                                                                  /* [1144] ComConf_ComSignal_EIC_DEQP */
    ,(BswU2)94U                                                                                                  /* [1145] ComConf_ComSignal_EIC_PEQP */
    ,(BswU2)94U                                                                                                  /* [1146] ComConf_ComSignal_EIC_REQP */
    ,(BswU2)94U                                                                                                  /* [1147] ComConf_ComSignal_EIC_LEQP */
    ,(BswU2)94U                                                                                                  /* [1148] ComConf_ComSignal_AIC_DRC */
    ,(BswU2)94U                                                                                                  /* [1149] ComConf_ComSignal_AIC_DMRC */
    ,(BswU2)94U                                                                                                  /* [1150] ComConf_ComSignal_AIC_DFRC */
    ,(BswU2)94U                                                                                                  /* [1151] ComConf_ComSignal_AIC_DBRC */
    ,(BswU2)94U                                                                                                  /* [1152] ComConf_ComSignal_AIC_DRRC */
    ,(BswU2)94U                                                                                                  /* [1153] ComConf_ComSignal_SIC_DMST */
    ,(BswU2)94U                                                                                                  /* [1154] ComConf_ComSignal_SIC_DCST */
    ,(BswU2)94U                                                                                                  /* [1155] ComConf_ComSignal_SIC_DFFL */
    ,(BswU2)94U                                                                                                  /* [1156] ComConf_ComSignal_SIC_DFFP */
    ,(BswU2)94U                                                                                                  /* [1157] ComConf_ComSignal_SIC_DFRL */
    ,(BswU2)94U                                                                                                  /* [1158] ComConf_ComSignal_SIC_DFRP */
    ,(BswU2)94U                                                                                                  /* [1159] ComConf_ComSignal_SIC_DF5L */
    ,(BswU2)94U                                                                                                  /* [1160] ComConf_ComSignal_SIC_DFDL */
    ,(BswU2)94U                                                                                                  /* [1161] ComConf_ComSignal_SIC_DFDP */
    ,(BswU2)94U                                                                                                  /* [1162] ComConf_ComSignal_SIC_DF4L */
    ,(BswU2)94U                                                                                                  /* [1163] ComConf_ComSignal_SIC_DF4P */
    ,(BswU2)94U                                                                                                  /* [1164] ComConf_ComSignal_SIC_DF5P */
    ,(BswU2)94U                                                                                                  /* [1165] ComConf_ComSignal_SIC_DBFL */
    ,(BswU2)94U                                                                                                  /* [1166] ComConf_ComSignal_SIC_DBFP */
    ,(BswU2)94U                                                                                                  /* [1167] ComConf_ComSignal_SIC_DBRL */
    ,(BswU2)94U                                                                                                  /* [1168] ComConf_ComSignal_SIC_DBRP */
    ,(BswU2)94U                                                                                                  /* [1169] ComConf_ComSignal_SIC_DB5L */
    ,(BswU2)94U                                                                                                  /* [1170] ComConf_ComSignal_SIC_DBDL */
    ,(BswU2)94U                                                                                                  /* [1171] ComConf_ComSignal_SIC_DBDP */
    ,(BswU2)94U                                                                                                  /* [1172] ComConf_ComSignal_SIC_DB4L */
    ,(BswU2)94U                                                                                                  /* [1173] ComConf_ComSignal_SIC_DB4P */
    ,(BswU2)94U                                                                                                  /* [1174] ComConf_ComSignal_SIC_DB5P */
    ,(BswU2)94U                                                                                                  /* [1175] ComConf_ComSignal_SIC_DRFL */
    ,(BswU2)94U                                                                                                  /* [1176] ComConf_ComSignal_SIC_DRRL */
    ,(BswU2)94U                                                                                                  /* [1177] ComConf_ComSignal_SIC_DRDL */
    ,(BswU2)94U                                                                                                  /* [1178] ComConf_ComSignal_SIC_DR4L */
    ,(BswU2)94U                                                                                                  /* [1179] ComConf_ComSignal_SIC_DR5L */
    ,(BswU2)94U                                                                                                  /* [1180] ComConf_ComSignal_SIC_DRFK */
    ,(BswU2)94U                                                                                                  /* [1181] ComConf_ComSignal_SIC_DRRK */
    ,(BswU2)94U                                                                                                  /* [1182] ComConf_ComSignal_SIC_DRDK */
    ,(BswU2)94U                                                                                                  /* [1183] ComConf_ComSignal_SIC_DR4K */
    ,(BswU2)94U                                                                                                  /* [1184] ComConf_ComSignal_SIC_DR5K */
    ,(BswU2)94U                                                                                                  /* [1185] ComConf_ComSignal_AIC_PRC */
    ,(BswU2)94U                                                                                                  /* [1186] ComConf_ComSignal_AIC_PMRC */
    ,(BswU2)94U                                                                                                  /* [1187] ComConf_ComSignal_AIC_PFRC */
    ,(BswU2)94U                                                                                                  /* [1188] ComConf_ComSignal_AIC_PBRC */
    ,(BswU2)94U                                                                                                  /* [1189] ComConf_ComSignal_AIC_PRRC */
    ,(BswU2)94U                                                                                                  /* [1190] ComConf_ComSignal_SIC_PMST */
    ,(BswU2)94U                                                                                                  /* [1191] ComConf_ComSignal_SIC_PCST */
    ,(BswU2)94U                                                                                                  /* [1192] ComConf_ComSignal_SIC_PFFL */
    ,(BswU2)94U                                                                                                  /* [1193] ComConf_ComSignal_SIC_PFFP */
    ,(BswU2)94U                                                                                                  /* [1194] ComConf_ComSignal_SIC_PFRL */
    ,(BswU2)94U                                                                                                  /* [1195] ComConf_ComSignal_SIC_PFRP */
    ,(BswU2)94U                                                                                                  /* [1196] ComConf_ComSignal_SIC_PF5L */
    ,(BswU2)94U                                                                                                  /* [1197] ComConf_ComSignal_SIC_PFDL */
    ,(BswU2)94U                                                                                                  /* [1198] ComConf_ComSignal_SIC_PFDP */
    ,(BswU2)94U                                                                                                  /* [1199] ComConf_ComSignal_SIC_PF4L */
    ,(BswU2)94U                                                                                                  /* [1200] ComConf_ComSignal_SIC_PF4P */
    ,(BswU2)94U                                                                                                  /* [1201] ComConf_ComSignal_SIC_PF5P */
    ,(BswU2)94U                                                                                                  /* [1202] ComConf_ComSignal_SIC_PBFL */
    ,(BswU2)94U                                                                                                  /* [1203] ComConf_ComSignal_SIC_PBFP */
    ,(BswU2)94U                                                                                                  /* [1204] ComConf_ComSignal_SIC_PBRL */
    ,(BswU2)94U                                                                                                  /* [1205] ComConf_ComSignal_SIC_PBRP */
    ,(BswU2)94U                                                                                                  /* [1206] ComConf_ComSignal_SIC_PB5L */
    ,(BswU2)94U                                                                                                  /* [1207] ComConf_ComSignal_SIC_PBDL */
    ,(BswU2)94U                                                                                                  /* [1208] ComConf_ComSignal_SIC_PBDP */
    ,(BswU2)94U                                                                                                  /* [1209] ComConf_ComSignal_SIC_PB4L */
    ,(BswU2)94U                                                                                                  /* [1210] ComConf_ComSignal_SIC_PB4P */
    ,(BswU2)94U                                                                                                  /* [1211] ComConf_ComSignal_SIC_PB5P */
    ,(BswU2)94U                                                                                                  /* [1212] ComConf_ComSignal_SIC_PRFL */
    ,(BswU2)94U                                                                                                  /* [1213] ComConf_ComSignal_SIC_PRRL */
    ,(BswU2)94U                                                                                                  /* [1214] ComConf_ComSignal_SIC_PRDL */
    ,(BswU2)94U                                                                                                  /* [1215] ComConf_ComSignal_SIC_PR4L */
    ,(BswU2)94U                                                                                                  /* [1216] ComConf_ComSignal_SIC_PR5L */
    ,(BswU2)94U                                                                                                  /* [1217] ComConf_ComSignal_SIC_PRFK */
    ,(BswU2)94U                                                                                                  /* [1218] ComConf_ComSignal_SIC_PRRK */
    ,(BswU2)94U                                                                                                  /* [1219] ComConf_ComSignal_SIC_PRDK */
    ,(BswU2)94U                                                                                                  /* [1220] ComConf_ComSignal_SIC_PR4K */
    ,(BswU2)94U                                                                                                  /* [1221] ComConf_ComSignal_SIC_PR5K */
    ,(BswU2)95U                                                                                                  /* [1222] ComConf_ComSignal_AIC_RRC */
    ,(BswU2)95U                                                                                                  /* [1223] ComConf_ComSignal_AIC_RMRC */
    ,(BswU2)95U                                                                                                  /* [1224] ComConf_ComSignal_AIC_RFRC */
    ,(BswU2)95U                                                                                                  /* [1225] ComConf_ComSignal_AIC_RBRC */
    ,(BswU2)95U                                                                                                  /* [1226] ComConf_ComSignal_AIC_RRRC */
    ,(BswU2)95U                                                                                                  /* [1227] ComConf_ComSignal_SIC_RMST */
    ,(BswU2)95U                                                                                                  /* [1228] ComConf_ComSignal_SIC_RCST */
    ,(BswU2)95U                                                                                                  /* [1229] ComConf_ComSignal_SIC_RFFL */
    ,(BswU2)95U                                                                                                  /* [1230] ComConf_ComSignal_SIC_RFFP */
    ,(BswU2)95U                                                                                                  /* [1231] ComConf_ComSignal_SIC_RFRL */
    ,(BswU2)95U                                                                                                  /* [1232] ComConf_ComSignal_SIC_RFRP */
    ,(BswU2)95U                                                                                                  /* [1233] ComConf_ComSignal_SIC_RF5L */
    ,(BswU2)95U                                                                                                  /* [1234] ComConf_ComSignal_SIC_RFDL */
    ,(BswU2)95U                                                                                                  /* [1235] ComConf_ComSignal_SIC_RFDP */
    ,(BswU2)95U                                                                                                  /* [1236] ComConf_ComSignal_SIC_RF4L */
    ,(BswU2)95U                                                                                                  /* [1237] ComConf_ComSignal_SIC_RF4P */
    ,(BswU2)95U                                                                                                  /* [1238] ComConf_ComSignal_SIC_RF5P */
    ,(BswU2)95U                                                                                                  /* [1239] ComConf_ComSignal_SIC_RBFL */
    ,(BswU2)95U                                                                                                  /* [1240] ComConf_ComSignal_SIC_RBFP */
    ,(BswU2)95U                                                                                                  /* [1241] ComConf_ComSignal_SIC_RBRL */
    ,(BswU2)95U                                                                                                  /* [1242] ComConf_ComSignal_SIC_RBRP */
    ,(BswU2)95U                                                                                                  /* [1243] ComConf_ComSignal_SIC_RB5L */
    ,(BswU2)95U                                                                                                  /* [1244] ComConf_ComSignal_SIC_RBDL */
    ,(BswU2)95U                                                                                                  /* [1245] ComConf_ComSignal_SIC_RBDP */
    ,(BswU2)95U                                                                                                  /* [1246] ComConf_ComSignal_SIC_RB4L */
    ,(BswU2)95U                                                                                                  /* [1247] ComConf_ComSignal_SIC_RB4P */
    ,(BswU2)95U                                                                                                  /* [1248] ComConf_ComSignal_SIC_RB5P */
    ,(BswU2)95U                                                                                                  /* [1249] ComConf_ComSignal_SIC_RRFL */
    ,(BswU2)95U                                                                                                  /* [1250] ComConf_ComSignal_SIC_RRRL */
    ,(BswU2)95U                                                                                                  /* [1251] ComConf_ComSignal_SIC_RRDL */
    ,(BswU2)95U                                                                                                  /* [1252] ComConf_ComSignal_SIC_RR4L */
    ,(BswU2)95U                                                                                                  /* [1253] ComConf_ComSignal_SIC_RR5L */
    ,(BswU2)95U                                                                                                  /* [1254] ComConf_ComSignal_SIC_RRFK */
    ,(BswU2)95U                                                                                                  /* [1255] ComConf_ComSignal_SIC_RRRK */
    ,(BswU2)95U                                                                                                  /* [1256] ComConf_ComSignal_SIC_RRDK */
    ,(BswU2)95U                                                                                                  /* [1257] ComConf_ComSignal_SIC_RR4K */
    ,(BswU2)95U                                                                                                  /* [1258] ComConf_ComSignal_SIC_RR5K */
    ,(BswU2)95U                                                                                                  /* [1259] ComConf_ComSignal_AIC_LRC */
    ,(BswU2)95U                                                                                                  /* [1260] ComConf_ComSignal_AIC_LMRC */
    ,(BswU2)95U                                                                                                  /* [1261] ComConf_ComSignal_AIC_LFRC */
    ,(BswU2)95U                                                                                                  /* [1262] ComConf_ComSignal_AIC_LBRC */
    ,(BswU2)95U                                                                                                  /* [1263] ComConf_ComSignal_AIC_LRRC */
    ,(BswU2)95U                                                                                                  /* [1264] ComConf_ComSignal_SIC_LMST */
    ,(BswU2)95U                                                                                                  /* [1265] ComConf_ComSignal_SIC_LCST */
    ,(BswU2)95U                                                                                                  /* [1266] ComConf_ComSignal_SIC_LFFL */
    ,(BswU2)95U                                                                                                  /* [1267] ComConf_ComSignal_SIC_LFFP */
    ,(BswU2)95U                                                                                                  /* [1268] ComConf_ComSignal_SIC_LFRL */
    ,(BswU2)95U                                                                                                  /* [1269] ComConf_ComSignal_SIC_LFRP */
    ,(BswU2)95U                                                                                                  /* [1270] ComConf_ComSignal_SIC_LF5L */
    ,(BswU2)95U                                                                                                  /* [1271] ComConf_ComSignal_SIC_LFDL */
    ,(BswU2)95U                                                                                                  /* [1272] ComConf_ComSignal_SIC_LFDP */
    ,(BswU2)95U                                                                                                  /* [1273] ComConf_ComSignal_SIC_LF4L */
    ,(BswU2)95U                                                                                                  /* [1274] ComConf_ComSignal_SIC_LF4P */
    ,(BswU2)95U                                                                                                  /* [1275] ComConf_ComSignal_SIC_LF5P */
    ,(BswU2)95U                                                                                                  /* [1276] ComConf_ComSignal_SIC_LBFL */
    ,(BswU2)95U                                                                                                  /* [1277] ComConf_ComSignal_SIC_LBFP */
    ,(BswU2)95U                                                                                                  /* [1278] ComConf_ComSignal_SIC_LBRL */
    ,(BswU2)95U                                                                                                  /* [1279] ComConf_ComSignal_SIC_LBRP */
    ,(BswU2)95U                                                                                                  /* [1280] ComConf_ComSignal_SIC_LB5L */
    ,(BswU2)95U                                                                                                  /* [1281] ComConf_ComSignal_SIC_LBDL */
    ,(BswU2)95U                                                                                                  /* [1282] ComConf_ComSignal_SIC_LBDP */
    ,(BswU2)95U                                                                                                  /* [1283] ComConf_ComSignal_SIC_LB4L */
    ,(BswU2)95U                                                                                                  /* [1284] ComConf_ComSignal_SIC_LB4P */
    ,(BswU2)95U                                                                                                  /* [1285] ComConf_ComSignal_SIC_LB5P */
    ,(BswU2)95U                                                                                                  /* [1286] ComConf_ComSignal_SIC_LRFL */
    ,(BswU2)95U                                                                                                  /* [1287] ComConf_ComSignal_SIC_LRRL */
    ,(BswU2)95U                                                                                                  /* [1288] ComConf_ComSignal_SIC_LRDL */
    ,(BswU2)95U                                                                                                  /* [1289] ComConf_ComSignal_SIC_LR4L */
    ,(BswU2)95U                                                                                                  /* [1290] ComConf_ComSignal_SIC_LR5L */
    ,(BswU2)95U                                                                                                  /* [1291] ComConf_ComSignal_SIC_LRFK */
    ,(BswU2)95U                                                                                                  /* [1292] ComConf_ComSignal_SIC_LRRK */
    ,(BswU2)95U                                                                                                  /* [1293] ComConf_ComSignal_SIC_LRDK */
    ,(BswU2)95U                                                                                                  /* [1294] ComConf_ComSignal_SIC_LR4K */
    ,(BswU2)95U                                                                                                  /* [1295] ComConf_ComSignal_SIC_LR5K */
};

BswConst Bsw_Com_MsgInfoType bsw_com_stMsgInfoTbl[BSW_COM_MSG_NUM] = {
     { BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [0] MSG_ABG1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [1] MSG_ABG1D51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [2] MSG_ABG1S09_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [3] MSG_ACN1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [4] MSG_ACN1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [5] MSG_ACN1S15_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [6] MSG_ACN1S25_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [7] MSG_ACN1S29_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [8] MSG_ADC1S27_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [9] MSG_ADC1S30_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 2000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [10] MSG_ADC1S31_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [11] MSG_ADU1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [12] MSG_ADU1S05_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [13] MSG_ADU1S06_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [14] MSG_AVN1S95_RXCH0 */
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
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [25] MSG_BDC1S41_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [26] MSG_BDC1S81_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [27] MSG_BDC1S82_RXCH0 */
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
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [32] MSG_CDC1S04_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [33] MSG_CMB1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [34] MSG_CMB1S04_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [35] MSG_DCM1S08_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [36] MSG_DDM1S00_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [37] MSG_DDM1S09_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [38] MSG_DDM1S16_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [39] MSG_DDM1S35_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [40] MSG_DDM1SFG_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [41] MSG_DDM1SFH_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [42] MSG_DKY1S26_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [43] MSG_DS11S27_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [44] MSG_EBU1D01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [45] MSG_ECT1S93_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 2000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [46] MSG_EHV1E96_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  160U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [47] MSG_EHV1F02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [48] MSG_EHV1S23_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  160U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [49] MSG_EHV2G10_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  240U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [50] MSG_EHV2G20_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [51] MSG_EIM1S01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [52] MSG_ENG1C01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [53] MSG_ENG1C02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [54] MSG_ENG1D51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [55] MSG_ENG1D52_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [56] MSG_ENG1D53_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [57] MSG_ENG1D55_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [58] MSG_ENG1D56_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [59] MSG_ENG1D59_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [60] MSG_ENG1D60_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(15000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [61] MSG_ENG1S51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [62] MSG_EPS1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [63] MSG_FCM1C01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [64] MSG_FCM1S49_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [65] MSG_FCM1S76_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [66] MSG_FCM1S79_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [67] MSG_FCM1S90_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [68] MSG_FCM1S95_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [69] MSG_IDT1S07_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [70] MSG_IDT1S15_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [71] MSG_MET1S02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(   80U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [72] MSG_MGC1F13_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [73] MSG_PDC1G01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [74] MSG_PWC1S41_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [75] MSG_RCP1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [76] MSG_RSE1G20_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [77] MSG_RSE1G24_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [78] MSG_RSE1G25_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [79] MSG_RSE1G26_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [80] MSG_RSE1G29_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [81] MSG_RSE1S02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [82] MSG_SCS1S10_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [83] MSG_VGR1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [84] MSG_VSC1D51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(   60U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [85] MSG_VSC1G13_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [86] MSG_WIP1S01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [87] MSG_ZN11S08_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [88] MSG_ZN11S32_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [89] MSG_ZN11S63_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [90] MSG_ZN11S64_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [91] MSG_ZN11S65_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [92] MSG_ZN11S66_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [93] MSG_ZN11S67_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [94] MSG_ZN11SF6_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [95] MSG_ZN11SF7_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
};

BswConst BswU4 bsw_com_u4SysStatTbl[BSW_COM_MSG_NUM][BSW_COM_SYSSTATTBLNUM] =
{
     {    /* [0] MSG_ABG1D50_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [1] MSG_ABG1D51_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [2] MSG_ABG1S09_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [3] MSG_ACN1D50_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [4] MSG_ACN1S03_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [5] MSG_ACN1S15_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [6] MSG_ACN1S25_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [7] MSG_ACN1S29_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [8] MSG_ADC1S27_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [9] MSG_ADC1S30_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [10] MSG_ADC1S31_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [11] MSG_ADU1S03_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [12] MSG_ADU1S05_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [13] MSG_ADU1S06_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [14] MSG_AVN1S95_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [15] MSG_BAT1E45_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [16] MSG_BAT1ED1_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [17] MSG_BAT1ED4_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [18] MSG_BAT1ED5_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [19] MSG_BAT1EDA_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [20] MSG_BAT1EDB_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [21] MSG_BAT1S08_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [22] MSG_BAT2ED2_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [23] MSG_BDB1F03_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [24] MSG_BDB1S10_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [25] MSG_BDC1S41_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [26] MSG_BDC1S81_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [27] MSG_BDC1S82_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [28] MSG_BDC1SH8_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [29] MSG_BDF3S01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [30] MSG_BDF3S02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [31] MSG_BDR3S02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [32] MSG_CDC1S04_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [33] MSG_CMB1S03_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [34] MSG_CMB1S04_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [35] MSG_DCM1S08_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [36] MSG_DDM1S00_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [37] MSG_DDM1S09_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [38] MSG_DDM1S16_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [39] MSG_DDM1S35_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [40] MSG_DDM1SFG_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [41] MSG_DDM1SFH_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [42] MSG_DKY1S26_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [43] MSG_DS11S27_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [44] MSG_EBU1D01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [45] MSG_ECT1S93_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [46] MSG_EHV1E96_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [47] MSG_EHV1F02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [48] MSG_EHV1S23_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [49] MSG_EHV2G10_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [50] MSG_EHV2G20_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [51] MSG_EIM1S01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [52] MSG_ENG1C01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [53] MSG_ENG1C02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [54] MSG_ENG1D51_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [55] MSG_ENG1D52_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [56] MSG_ENG1D53_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [57] MSG_ENG1D55_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [58] MSG_ENG1D56_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [59] MSG_ENG1D59_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [60] MSG_ENG1D60_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [61] MSG_ENG1S51_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [62] MSG_EPS1D50_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [63] MSG_FCM1C01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [64] MSG_FCM1S49_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [65] MSG_FCM1S76_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [66] MSG_FCM1S79_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [67] MSG_FCM1S90_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [68] MSG_FCM1S95_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [69] MSG_IDT1S07_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [70] MSG_IDT1S15_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [71] MSG_MET1S02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [72] MSG_MGC1F13_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [73] MSG_PDC1G01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [74] MSG_PWC1S41_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [75] MSG_RCP1S03_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [76] MSG_RSE1G20_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [77] MSG_RSE1G24_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [78] MSG_RSE1G25_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [79] MSG_RSE1G26_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [80] MSG_RSE1G29_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [81] MSG_RSE1S02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [82] MSG_SCS1S10_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [83] MSG_VGR1D50_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [84] MSG_VSC1D51_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [85] MSG_VSC1G13_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [86] MSG_WIP1S01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [87] MSG_ZN11S08_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [88] MSG_ZN11S32_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [89] MSG_ZN11S63_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [90] MSG_ZN11S64_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [91] MSG_ZN11S65_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [92] MSG_ZN11S66_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [93] MSG_ZN11S67_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [94] MSG_ZN11SF6_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [95] MSG_ZN11SF7_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
};

#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2TxDelayTbl[BSW_COM_TX_MSG_NUM] = {
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */

BswConst Bsw_Com_MsgOffsetType bsw_com_u2MsgOffsTbl[BSW_COM_MSG_NUM] = {
     (BswU2)0U                                                                                                   /* [0] MSG_ABG1D50_RXCH0 */
    ,(BswU2)8U                                                                                                   /* [1] MSG_ABG1D51_RXCH0 */
    ,(BswU2)16U                                                                                                  /* [2] MSG_ABG1S09_RXCH0 */
    ,(BswU2)48U                                                                                                  /* [3] MSG_ACN1D50_RXCH0 */
    ,(BswU2)56U                                                                                                  /* [4] MSG_ACN1S03_RXCH0 */
    ,(BswU2)64U                                                                                                  /* [5] MSG_ACN1S15_RXCH0 */
    ,(BswU2)72U                                                                                                  /* [6] MSG_ACN1S25_RXCH0 */
    ,(BswU2)104U                                                                                                 /* [7] MSG_ACN1S29_RXCH0 */
    ,(BswU2)136U                                                                                                 /* [8] MSG_ADC1S27_RXCH0 */
    ,(BswU2)168U                                                                                                 /* [9] MSG_ADC1S30_RXCH0 */
    ,(BswU2)176U                                                                                                 /* [10] MSG_ADC1S31_RXCH0 */
    ,(BswU2)208U                                                                                                 /* [11] MSG_ADU1S03_RXCH0 */
    ,(BswU2)240U                                                                                                 /* [12] MSG_ADU1S05_RXCH0 */
    ,(BswU2)272U                                                                                                 /* [13] MSG_ADU1S06_RXCH0 */
    ,(BswU2)304U                                                                                                 /* [14] MSG_AVN1S95_RXCH0 */
    ,(BswU2)312U                                                                                                 /* [15] MSG_BAT1E45_RXCH0 */
    ,(BswU2)344U                                                                                                 /* [16] MSG_BAT1ED1_RXCH0 */
    ,(BswU2)376U                                                                                                 /* [17] MSG_BAT1ED4_RXCH0 */
    ,(BswU2)384U                                                                                                 /* [18] MSG_BAT1ED5_RXCH0 */
    ,(BswU2)392U                                                                                                 /* [19] MSG_BAT1EDA_RXCH0 */
    ,(BswU2)400U                                                                                                 /* [20] MSG_BAT1EDB_RXCH0 */
    ,(BswU2)432U                                                                                                 /* [21] MSG_BAT1S08_RXCH0 */
    ,(BswU2)440U                                                                                                 /* [22] MSG_BAT2ED2_RXCH0 */
    ,(BswU2)448U                                                                                                 /* [23] MSG_BDB1F03_RXCH0 */
    ,(BswU2)456U                                                                                                 /* [24] MSG_BDB1S10_RXCH0 */
    ,(BswU2)464U                                                                                                 /* [25] MSG_BDC1S41_RXCH0 */
    ,(BswU2)496U                                                                                                 /* [26] MSG_BDC1S81_RXCH0 */
    ,(BswU2)528U                                                                                                 /* [27] MSG_BDC1S82_RXCH0 */
    ,(BswU2)560U                                                                                                 /* [28] MSG_BDC1SH8_RXCH0 */
    ,(BswU2)568U                                                                                                 /* [29] MSG_BDF3S01_RXCH0 */
    ,(BswU2)600U                                                                                                 /* [30] MSG_BDF3S02_RXCH0 */
    ,(BswU2)632U                                                                                                 /* [31] MSG_BDR3S02_RXCH0 */
    ,(BswU2)664U                                                                                                 /* [32] MSG_CDC1S04_RXCH0 */
    ,(BswU2)672U                                                                                                 /* [33] MSG_CMB1S03_RXCH0 */
    ,(BswU2)680U                                                                                                 /* [34] MSG_CMB1S04_RXCH0 */
    ,(BswU2)688U                                                                                                 /* [35] MSG_DCM1S08_RXCH0 */
    ,(BswU2)696U                                                                                                 /* [36] MSG_DDM1S00_RXCH0 */
    ,(BswU2)704U                                                                                                 /* [37] MSG_DDM1S09_RXCH0 */
    ,(BswU2)712U                                                                                                 /* [38] MSG_DDM1S16_RXCH0 */
    ,(BswU2)744U                                                                                                 /* [39] MSG_DDM1S35_RXCH0 */
    ,(BswU2)776U                                                                                                 /* [40] MSG_DDM1SFG_RXCH0 */
    ,(BswU2)808U                                                                                                 /* [41] MSG_DDM1SFH_RXCH0 */
    ,(BswU2)840U                                                                                                 /* [42] MSG_DKY1S26_RXCH0 */
    ,(BswU2)848U                                                                                                 /* [43] MSG_DS11S27_RXCH0 */
    ,(BswU2)856U                                                                                                 /* [44] MSG_EBU1D01_RXCH0 */
    ,(BswU2)888U                                                                                                 /* [45] MSG_ECT1S93_RXCH0 */
    ,(BswU2)896U                                                                                                 /* [46] MSG_EHV1E96_RXCH0 */
    ,(BswU2)928U                                                                                                 /* [47] MSG_EHV1F02_RXCH0 */
    ,(BswU2)936U                                                                                                 /* [48] MSG_EHV1S23_RXCH0 */
    ,(BswU2)944U                                                                                                 /* [49] MSG_EHV2G10_RXCH0 */
    ,(BswU2)976U                                                                                                 /* [50] MSG_EHV2G20_RXCH0 */
    ,(BswU2)1008U                                                                                                /* [51] MSG_EIM1S01_RXCH0 */
    ,(BswU2)1016U                                                                                                /* [52] MSG_ENG1C01_RXCH0 */
    ,(BswU2)1024U                                                                                                /* [53] MSG_ENG1C02_RXCH0 */
    ,(BswU2)1032U                                                                                                /* [54] MSG_ENG1D51_RXCH0 */
    ,(BswU2)1040U                                                                                                /* [55] MSG_ENG1D52_RXCH0 */
    ,(BswU2)1048U                                                                                                /* [56] MSG_ENG1D53_RXCH0 */
    ,(BswU2)1056U                                                                                                /* [57] MSG_ENG1D55_RXCH0 */
    ,(BswU2)1064U                                                                                                /* [58] MSG_ENG1D56_RXCH0 */
    ,(BswU2)1072U                                                                                                /* [59] MSG_ENG1D59_RXCH0 */
    ,(BswU2)1080U                                                                                                /* [60] MSG_ENG1D60_RXCH0 */
    ,(BswU2)1088U                                                                                                /* [61] MSG_ENG1S51_RXCH0 */
    ,(BswU2)1120U                                                                                                /* [62] MSG_EPS1D50_RXCH0 */
    ,(BswU2)1128U                                                                                                /* [63] MSG_FCM1C01_RXCH0 */
    ,(BswU2)1136U                                                                                                /* [64] MSG_FCM1S49_RXCH0 */
    ,(BswU2)1168U                                                                                                /* [65] MSG_FCM1S76_RXCH0 */
    ,(BswU2)1176U                                                                                                /* [66] MSG_FCM1S79_RXCH0 */
    ,(BswU2)1184U                                                                                                /* [67] MSG_FCM1S90_RXCH0 */
    ,(BswU2)1216U                                                                                                /* [68] MSG_FCM1S95_RXCH0 */
    ,(BswU2)1280U                                                                                                /* [69] MSG_IDT1S07_RXCH0 */
    ,(BswU2)1288U                                                                                                /* [70] MSG_IDT1S15_RXCH0 */
    ,(BswU2)1296U                                                                                                /* [71] MSG_MET1S02_RXCH0 */
    ,(BswU2)1304U                                                                                                /* [72] MSG_MGC1F13_RXCH0 */
    ,(BswU2)1336U                                                                                                /* [73] MSG_PDC1G01_RXCH0 */
    ,(BswU2)1344U                                                                                                /* [74] MSG_PWC1S41_RXCH0 */
    ,(BswU2)1376U                                                                                                /* [75] MSG_RCP1S03_RXCH0 */
    ,(BswU2)1384U                                                                                                /* [76] MSG_RSE1G20_RXCH0 */
    ,(BswU2)1392U                                                                                                /* [77] MSG_RSE1G24_RXCH0 */
    ,(BswU2)1400U                                                                                                /* [78] MSG_RSE1G25_RXCH0 */
    ,(BswU2)1408U                                                                                                /* [79] MSG_RSE1G26_RXCH0 */
    ,(BswU2)1416U                                                                                                /* [80] MSG_RSE1G29_RXCH0 */
    ,(BswU2)1424U                                                                                                /* [81] MSG_RSE1S02_RXCH0 */
    ,(BswU2)1432U                                                                                                /* [82] MSG_SCS1S10_RXCH0 */
    ,(BswU2)1464U                                                                                                /* [83] MSG_VGR1D50_RXCH0 */
    ,(BswU2)1496U                                                                                                /* [84] MSG_VSC1D51_RXCH0 */
    ,(BswU2)1528U                                                                                                /* [85] MSG_VSC1G13_RXCH0 */
    ,(BswU2)1560U                                                                                                /* [86] MSG_WIP1S01_RXCH0 */
    ,(BswU2)1568U                                                                                                /* [87] MSG_ZN11S08_RXCH0 */
    ,(BswU2)1600U                                                                                                /* [88] MSG_ZN11S32_RXCH0 */
    ,(BswU2)1632U                                                                                                /* [89] MSG_ZN11S63_RXCH0 */
    ,(BswU2)1664U                                                                                                /* [90] MSG_ZN11S64_RXCH0 */
    ,(BswU2)1696U                                                                                                /* [91] MSG_ZN11S65_RXCH0 */
    ,(BswU2)1728U                                                                                                /* [92] MSG_ZN11S66_RXCH0 */
    ,(BswU2)1760U                                                                                                /* [93] MSG_ZN11S67_RXCH0 */
    ,(BswU2)1792U                                                                                                /* [94] MSG_ZN11SF6_RXCH0 */
    ,(BswU2)1824U                                                                                                /* [95] MSG_ZN11SF7_RXCH0 */
};

#if( BSW_COM_CFG_METADATA_USE == BSW_USE )
BswConst BswU1 bsw_com_u1MetaDataSizeTbl[BSW_COM_MSG_NUM] = {
};
#endif /* BSW_COM_CFG_METADATA_USE == BSW_USE */

BswConst Bsw_Com_NetInfoType bsw_com_stNetInfoTxMsgTbl[BSW_COM_NETWORK_NUM] = {
     { (BswU2)0U,   (BswU2)0U   }                                                                                /* [0] CH0  */
};

BswConst Bsw_Com_NetInfoType bsw_com_stNetInfoRxMsgTbl[BSW_COM_NETWORK_NUM] = {
     { (BswU2)0U,   (BswU2)96U  }                                                                                /* [0] CH0 CDC_VCAN_BUS */
};

#if (BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE)
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2DelayTbl[BSW_COM_TX_MSG_NUM] = {
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */
#endif /* BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE */

#if ( (BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE) && (BSW_COM_CFG_TX_DLYSW_USE == BSW_USE) )
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2PrdDelayTbl[BSW_COM_TX_MSG_NUM] = {
};
#endif /* (BSW_COM_TX_MSG_NUM != 0U) */
#endif /* (BSW_COM_CFG_TX_DLYBYMSG_USE == BSW_USE) && (BSW_COM_CFG_TX_DLYSW_USE == BSW_USE) */

#if (BSW_COM_CFG_TX_TIMEOUT_USE == BSW_USE)
#if (BSW_COM_TX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2TxTimeoutTbl[BSW_COM_TX_MSG_NUM] = {
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

     BSW_COM_u2MILSEC(0U)                                                       /* [0] MSG_ABG1D50_RXCH0 */
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
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [14] MSG_AVN1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [15] MSG_BAT1E45_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [16] MSG_BAT1ED1_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [17] MSG_BAT1ED4_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [18] MSG_BAT1ED5_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [19] MSG_BAT1EDA_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [20] MSG_BAT1EDB_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [21] MSG_BAT1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [22] MSG_BAT2ED2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [23] MSG_BDB1F03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [24] MSG_BDB1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [25] MSG_BDC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [26] MSG_BDC1S81_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [27] MSG_BDC1S82_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [28] MSG_BDC1SH8_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [29] MSG_BDF3S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [30] MSG_BDF3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [31] MSG_BDR3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [32] MSG_CDC1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [33] MSG_CMB1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [34] MSG_CMB1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [35] MSG_DCM1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [36] MSG_DDM1S00_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [37] MSG_DDM1S09_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [38] MSG_DDM1S16_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [39] MSG_DDM1S35_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [40] MSG_DDM1SFG_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [41] MSG_DDM1SFH_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [42] MSG_DKY1S26_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [43] MSG_DS11S27_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [44] MSG_EBU1D01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [45] MSG_ECT1S93_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [46] MSG_EHV1E96_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [47] MSG_EHV1F02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [48] MSG_EHV1S23_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [49] MSG_EHV2G10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [50] MSG_EHV2G20_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [51] MSG_EIM1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [52] MSG_ENG1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [53] MSG_ENG1C02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [54] MSG_ENG1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [55] MSG_ENG1D52_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [56] MSG_ENG1D53_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [57] MSG_ENG1D55_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [58] MSG_ENG1D56_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [59] MSG_ENG1D59_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [60] MSG_ENG1D60_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [61] MSG_ENG1S51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [62] MSG_EPS1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [63] MSG_FCM1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [64] MSG_FCM1S49_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [65] MSG_FCM1S76_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [66] MSG_FCM1S79_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [67] MSG_FCM1S90_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [68] MSG_FCM1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [69] MSG_IDT1S07_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [70] MSG_IDT1S15_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [71] MSG_MET1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [72] MSG_MGC1F13_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [73] MSG_PDC1G01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [74] MSG_PWC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [75] MSG_RCP1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [76] MSG_RSE1G20_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [77] MSG_RSE1G24_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [78] MSG_RSE1G25_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [79] MSG_RSE1G26_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [80] MSG_RSE1G29_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [81] MSG_RSE1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [82] MSG_SCS1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [83] MSG_VGR1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [84] MSG_VSC1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [85] MSG_VSC1G13_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [86] MSG_WIP1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [87] MSG_ZN11S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [88] MSG_ZN11S32_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [89] MSG_ZN11S63_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [90] MSG_ZN11S64_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [91] MSG_ZN11S65_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [92] MSG_ZN11S66_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [93] MSG_ZN11S67_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [94] MSG_ZN11SF6_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [95] MSG_ZN11SF7_RXCH0 */
};

BswConst Bsw_Com_TickTimeType bsw_com_u2WakeupMsk[BSW_COM_RX_MSG_NUM] = {

     BSW_COM_u2MILSEC(0U)                                                       /* [0] MSG_ABG1D50_RXCH0 */
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
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [14] MSG_AVN1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [15] MSG_BAT1E45_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [16] MSG_BAT1ED1_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [17] MSG_BAT1ED4_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [18] MSG_BAT1ED5_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [19] MSG_BAT1EDA_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [20] MSG_BAT1EDB_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [21] MSG_BAT1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [22] MSG_BAT2ED2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [23] MSG_BDB1F03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [24] MSG_BDB1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [25] MSG_BDC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [26] MSG_BDC1S81_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [27] MSG_BDC1S82_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [28] MSG_BDC1SH8_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [29] MSG_BDF3S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [30] MSG_BDF3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [31] MSG_BDR3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [32] MSG_CDC1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [33] MSG_CMB1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [34] MSG_CMB1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [35] MSG_DCM1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [36] MSG_DDM1S00_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [37] MSG_DDM1S09_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [38] MSG_DDM1S16_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [39] MSG_DDM1S35_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [40] MSG_DDM1SFG_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [41] MSG_DDM1SFH_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [42] MSG_DKY1S26_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [43] MSG_DS11S27_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [44] MSG_EBU1D01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [45] MSG_ECT1S93_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [46] MSG_EHV1E96_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [47] MSG_EHV1F02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [48] MSG_EHV1S23_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [49] MSG_EHV2G10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [50] MSG_EHV2G20_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [51] MSG_EIM1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [52] MSG_ENG1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [53] MSG_ENG1C02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [54] MSG_ENG1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [55] MSG_ENG1D52_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [56] MSG_ENG1D53_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [57] MSG_ENG1D55_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [58] MSG_ENG1D56_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [59] MSG_ENG1D59_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [60] MSG_ENG1D60_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [61] MSG_ENG1S51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [62] MSG_EPS1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [63] MSG_FCM1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [64] MSG_FCM1S49_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [65] MSG_FCM1S76_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [66] MSG_FCM1S79_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [67] MSG_FCM1S90_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [68] MSG_FCM1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [69] MSG_IDT1S07_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [70] MSG_IDT1S15_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [71] MSG_MET1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [72] MSG_MGC1F13_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [73] MSG_PDC1G01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [74] MSG_PWC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [75] MSG_RCP1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [76] MSG_RSE1G20_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [77] MSG_RSE1G24_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [78] MSG_RSE1G25_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [79] MSG_RSE1G26_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [80] MSG_RSE1G29_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [81] MSG_RSE1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [82] MSG_SCS1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [83] MSG_VGR1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [84] MSG_VSC1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [85] MSG_VSC1G13_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [86] MSG_WIP1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [87] MSG_ZN11S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [88] MSG_ZN11S32_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [89] MSG_ZN11S63_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [90] MSG_ZN11S64_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [91] MSG_ZN11S65_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [92] MSG_ZN11S66_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [93] MSG_ZN11S67_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [94] MSG_ZN11SF6_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [95] MSG_ZN11SF7_RXCH0 */
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
};

BswConst Bsw_Com_TickTimeType bsw_com_u2DisableSendTbl[BSW_COM_TX_MSG_NUM] = {
};

BswConst Bsw_Com_TickTimeType bsw_com_u2EnablePeriodicTbl[BSW_COM_TX_MSG_NUM] = {
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
