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
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
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
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [16] MSG_BAT1EDA_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [17] MSG_BAT1S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [18] MSG_BAT2ED2_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [19] MSG_BDB1F03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [20] MSG_BDB1S10_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [21] MSG_BDC1S41_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [22] MSG_BDC1S81_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [23] MSG_BDC1S82_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [24] MSG_BDC1S91_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [25] MSG_BDC1SH8_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [26] MSG_BDC1SI1_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [27] MSG_BDC1SI2_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [28] MSG_BDC1SI3_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [29] MSG_BDC1SI4_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [30] MSG_BDC1SI5_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [31] MSG_BDC1SI6_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [32] MSG_BDC1SI7_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [33] MSG_BDC1SI8_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [34] MSG_BDC1SI9_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [35] MSG_BDC1SJ0_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [36] MSG_BDC1SJ1_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [37] MSG_BDC1SJ2_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [38] MSG_BDF3S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [39] MSG_BDF3S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [40] MSG_BDR3S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [41] MSG_CDC1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [42] MSG_CMB1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [43] MSG_CMB1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [44] MSG_DCM1S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [45] MSG_DDM1S00_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [46] MSG_DDM1S09_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [47] MSG_DDM1S16_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [48] MSG_DDM1S35_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [49] MSG_DDM1SFH_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [50] MSG_DKY1S26_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [51] MSG_DS11S27_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [52] MSG_EBU1D01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [53] MSG_ECT1S93_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [54] MSG_EHV1E96_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [55] MSG_EHV1F02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [56] MSG_EHV1S23_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [57] MSG_EHV2G10_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [58] MSG_EHV2G20_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [59] MSG_EIM1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [60] MSG_ENG1C01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [61] MSG_ENG1C02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [62] MSG_ENG1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [63] MSG_ENG1D52_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [64] MSG_ENG1D53_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [65] MSG_ENG1D55_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [66] MSG_ENG1D56_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [67] MSG_ENG1D59_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [68] MSG_ENG1D60_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [69] MSG_ENG1S51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [70] MSG_EPS1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [71] MSG_FCM1C01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [72] MSG_FCM1S49_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [73] MSG_FCM1S76_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [74] MSG_FCM1S79_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [75] MSG_FCM1S90_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [76] MSG_FCM1S95_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [77] MSG_IDT1S07_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [78] MSG_IDT1S15_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [79] MSG_MET1S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [80] MSG_MGC1F13_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [81] MSG_PDC1G01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [82] MSG_RCP1S03_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [83] MSG_RCP1S04_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [84] MSG_RCP1S05_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [85] MSG_RCP1S06_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [86] MSG_RSE1G20_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [87] MSG_RSE1G24_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [88] MSG_RSE1G25_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [89] MSG_RSE1G26_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [90] MSG_RSE1S02_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [91] MSG_VGR1D50_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [92] MSG_VSC1D51_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [93] MSG_VSC1G13_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [94] MSG_WIP1S01_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [95] MSG_ZN11S08_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [96] MSG_ZN11S63_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [97] MSG_ZN11S64_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [98] MSG_ZN11S65_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [99] MSG_ZN11S66_RXCH0 */
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U
    ,(BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U, (BswU1)0x00U  /* [100] MSG_ZN11S67_RXCH0 */
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
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [16] ComConf_ComSignal_FLGXMAX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [17] ComConf_ComSignal_FLVNMAX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [18] ComConf_ComSignal_FRGMAX_L */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [19] ComConf_ComSignal_FRGMAX_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [20] ComConf_ComSignal_PT_ON */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [21] ComConf_ComSignal_FRAB_ON */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [22] ComConf_ComSignal_DRACN01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [23] ComConf_ComSignal_DRACN02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [24] ComConf_ComSignal_DRACN03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [25] ComConf_ComSignal_DRACN04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [26] ComConf_ComSignal_DRACN05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [27] ComConf_ComSignal_DRACN06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [28] ComConf_ComSignal_DRACN07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [29] ComConf_ComSignal_DRACN08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [30] ComConf_ComSignal_DRACN09 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [31] ComConf_ComSignal_DRACN10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [32] ComConf_ComSignal_DRACN11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [33] ComConf_ComSignal_DRACN12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [34] ComConf_ComSignal_DRACN13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [35] ComConf_ComSignal_DRACN14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [36] ComConf_ComSignal_DRACN15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [37] ComConf_ComSignal_DRACN16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [38] ComConf_ComSignal_DRACN17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [39] ComConf_ComSignal_DRACN18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [40] ComConf_ComSignal_DRACN19 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [41] ComConf_ComSignal_DRACN20 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [42] ComConf_ComSignal_DRACN21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [43] ComConf_ComSignal_DRACN22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [44] ComConf_ComSignal_DRACN23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [45] ComConf_ComSignal_DRACN24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [46] ComConf_ComSignal_DRACN25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [47] ComConf_ComSignal_DRACN26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [48] ComConf_ComSignal_DRACN27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [49] ComConf_ComSignal_DRACN28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [50] ComConf_ComSignal_DRACN29 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [51] ComConf_ComSignal_DRACN30 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [52] ComConf_ComSignal_DRACN31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [53] ComConf_ComSignal_DRACN32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [54] ComConf_ComSignal_O_STG_F */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [55] ComConf_ComSignal_O_STGH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [56] ComConf_ComSignal_AC_CDSP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [57] ComConf_ComSignal_TRTEMP_P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [58] ComConf_ComSignal_I_BLWF_P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [59] ComConf_ComSignal_HQ_COMP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [60] ComConf_ComSignal_R_SHLOFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [61] ComConf_ComSignal_R_SHHTFL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [62] ComConf_ComSignal_R_SHHTFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [63] ComConf_ComSignal_RSVFLDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [64] ComConf_ComSignal_RSVFRDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [65] ComConf_ComSignal_R_SHHTRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [66] ComConf_ComSignal_R_SHHTRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [67] ComConf_ComSignal_R_SHTFL3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [68] ComConf_ComSignal_R_SHTFL2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [69] ComConf_ComSignal_RSVRLDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [70] ComConf_ComSignal_RSVRRDU */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [71] ComConf_ComSignal_WS_VD_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [72] ComConf_ComSignal_WS_FTG_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [73] ComConf_ComSignal_WS_ABH_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [74] ComConf_ComSignal_WS_APO_R */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [75] ComConf_ComSignal_ETHWU_12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [76] ComConf_ComSignal_APPMD2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [77] ComConf_ComSignal_FV1C0_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [78] ComConf_ComSignal_KZK1C0_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [79] ComConf_ComSignal_ACCMAPP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [80] ComConf_ComSignal_ACCMMOD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [81] ComConf_ComSignal_ACCMDST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [82] ComConf_ComSignal_ACCMPHS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [83] ComConf_ComSignal_ACCMSGN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [84] ComConf_ComSignal_ACCMRCG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [85] ComConf_ComSignal_ACCMARB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [86] ComConf_ComSignal_LDASTATL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [87] ComConf_ComSignal_LDASTATR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [88] ComConf_ComSignal_LDARSN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [89] ComConf_ComSignal_FCMINTMP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [90] ComConf_ComSignal_LDARCGL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [91] ComConf_ComSignal_LDARCGR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [92] ComConf_ComSignal_SWSSTAT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [93] ComConf_ComSignal_V_IDACCL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [94] ComConf_ComSignal_EJDEVPRD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [95] ComConf_ComSignal_EJLDACP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [96] ComConf_ComSignal_V_IDANOA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [97] ComConf_ComSignal_V_IDARGL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [98] ComConf_ComSignal_PV_AREA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [99] ComConf_ComSignal_DM_PVMVW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [100] ComConf_ComSignal_DM_PVMCS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [101] ComConf_ComSignal_ERMCNTST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [102] ComConf_ComSignal_GAE_H_R3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [103] ComConf_ComSignal_FRDHTR_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [104] ComConf_ComSignal_SDIRT_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [105] ComConf_ComSignal_GAE_V_R1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [106] ComConf_ComSignal_DRTCNT_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [107] ComConf_ComSignal_GAERR1_V */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [108] ComConf_ComSignal_GAEVAL_H */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [109] ComConf_ComSignal_GAERR3_H */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [110] ComConf_ComSignal_DTSSSTR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [111] ComConf_ComSignal_DTSSLTID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [112] ComConf_ComSignal_MDSYNC00 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [113] ComConf_ComSignal_OTA3RSLT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [114] ComConf_ComSignal_OTADRSLT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [115] ComConf_ComSignal_SRVC_STT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [116] ComConf_ComSignal_OTA3CNCL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [117] ComConf_ComSignal_OTADCNCL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [118] ComConf_ComSignal_CUR_DRV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [119] ComConf_ComSignal_SRVC_PC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [120] ComConf_ComSignal_SRVC_VC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [121] ComConf_ComSignal_SRVC_AC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [122] ComConf_ComSignal_OTAPPCTL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [123] ComConf_ComSignal_CW_MD_SW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [124] ComConf_ComSignal_VNHLDRQ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [125] ComConf_ComSignal_TRNCASW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [126] ComConf_ComSignal_TRNSD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [127] ComConf_ComSignal_TRNFBPD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [128] ComConf_ComSignal_RDG_ACT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [129] ComConf_ComSignal_OTACDRLT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [130] ComConf_ComSignal_OTACHGEX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [131] ComConf_ComSignal_OTAACTTP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [132] ComConf_ComSignal_OTAACTPH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [133] ComConf_ComSignal_OTASWACT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [134] ComConf_ComSignal_OTASTAT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [135] ComConf_ComSignal_BIB_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [136] ComConf_ComSignal_VCELMAXG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [137] ComConf_ComSignal_VCELMING */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [138] ComConf_ComSignal_RAHRMAXG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [139] ComConf_ComSignal_RAHRMING */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [140] ComConf_ComSignal_TC_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [141] ComConf_ComSignal_TBMAX_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [142] ComConf_ComSignal_TBMIN_G */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [143] ComConf_ComSignal_D_MINFAD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [144] ComConf_ComSignal_D_MINFO1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [145] ComConf_ComSignal_D_MINFO2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [146] ComConf_ComSignal_D_MINFO3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [147] ComConf_ComSignal_BTWO */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [148] ComConf_ComSignal_BITGB1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [149] ComConf_ComSignal_BITGB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [150] ComConf_ComSignal_BITGB3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [151] ComConf_ComSignal_BITGB4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [152] ComConf_ComSignal_STKNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [153] ComConf_ComSignal_BITGB5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [154] ComConf_ComSignal_VCELNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [155] ComConf_ComSignal_INFGB1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [156] ComConf_ComSignal_TMINNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [157] ComConf_ComSignal_INFGB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [158] ComConf_ComSignal_TMAXNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [159] ComConf_ComSignal_VBTINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [160] ComConf_ComSignal_SOCINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [161] ComConf_ComSignal_IBTINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [162] ComConf_ComSignal_TBTINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [163] ComConf_ComSignal_STPSOC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [164] ComConf_ComSignal_STPVB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [165] ComConf_ComSignal_STPCELV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [166] ComConf_ComSignal_STPTMP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [167] ComConf_ComSignal_DATAGB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [168] ComConf_ComSignal_DATAGB3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [169] ComConf_ComSignal_ID63B16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [170] ComConf_ComSignal_IF63B16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [171] ComConf_ComSignal_TRIP_CNT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [172] ComConf_ComSignal_TIME_CNT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [173] ComConf_ComSignal_IL_FDOME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [174] ComConf_ComSignal_IL_LOUNG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [175] ComConf_ComSignal_IL_OSSTP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [176] ComConf_ComSignal_AMB_COP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [177] ComConf_ComSignal_SUPRQ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [178] ComConf_ComSignal_AXIB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [179] ComConf_ComSignal_AXVB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [180] ComConf_ComSignal_AXTB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [181] ComConf_ComSignal_AXSOC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [182] ComConf_ComSignal_E_CRC1E3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [183] ComConf_ComSignal_E_CNT1E3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [184] ComConf_ComSignal_VPSINFO7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [185] ComConf_ComSignal_VPSINFO6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [186] ComConf_ComSignal_VPSINFO5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [187] ComConf_ComSignal_VPSINFO4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [188] ComConf_ComSignal_VPSINFO3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [189] ComConf_ComSignal_VPSINFO2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [190] ComConf_ComSignal_VPSINFO1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [191] ComConf_ComSignal_VPSINFOS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [192] ComConf_ComSignal_VPSCNG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [193] ComConf_ComSignal_VPSISOTA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [194] ComConf_ComSignal_APOFRQ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [195] ComConf_ComSignal_FV1E3_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [196] ComConf_ComSignal_KZK1E3_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [197] ComConf_ComSignal_E_CRC150 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [198] ComConf_ComSignal_E_CNT150 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [199] ComConf_ComSignal_PWRERRST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [200] ComConf_ComSignal_CRLYOF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [201] ComConf_ComSignal_LRQ_ELRS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [202] ComConf_ComSignal_LRQ_ARSS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [203] ComConf_ComSignal_LRQ_RFRS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [204] ComConf_ComSignal_LRQ_RILM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [205] ComConf_ComSignal_LRQ_WLCH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [206] ComConf_ComSignal_LRQ_RDFG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [207] ComConf_ComSignal_LRQ_EHW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [208] ComConf_ComSignal_LRQ_RDH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [209] ComConf_ComSignal_LRQ_FRSH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [210] ComConf_ComSignal_LRQ_RRSH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [211] ComConf_ComSignal_LRQ_FRG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [212] ComConf_ComSignal_LRQ_NNE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [213] ComConf_ComSignal_LRQ_WDIC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [214] ComConf_ComSignal_LRQ_MRH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [215] ComConf_ComSignal_LRQ_STRH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [216] ComConf_ComSignal_LRQ_DMG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [217] ComConf_ComSignal_LRQ_IRP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [218] ComConf_ComSignal_LRQ_FACB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [219] ComConf_ComSignal_LRQ_RACB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [220] ComConf_ComSignal_LRQ_SPL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [221] ComConf_ComSignal_LRQ_ELF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [222] ComConf_ComSignal_LRQ_ACC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [223] ComConf_ComSignal_LRQ_USB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [224] ComConf_ComSignal_LRQ_USB2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [225] ComConf_ComSignal_LRQ_ACC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [226] ComConf_ComSignal_LRQ_TOW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [227] ComConf_ComSignal_LRQOHP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [228] ComConf_ComSignal_LRQ_SHAC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [229] ComConf_ComSignal_LRQ_SAMP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [230] ComConf_ComSignal_LRQELL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [231] ComConf_ComSignal_FV150_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [232] ComConf_ComSignal_KZK150_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [233] ComConf_ComSignal_E_CRC1E4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [234] ComConf_ComSignal_E_CNT1E4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [235] ComConf_ComSignal_VPSINF7S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [236] ComConf_ComSignal_VPSINF6S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [237] ComConf_ComSignal_VPSINF5S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [238] ComConf_ComSignal_VPSINF4S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [239] ComConf_ComSignal_VPSINF3S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [240] ComConf_ComSignal_VPSINF2S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [241] ComConf_ComSignal_VPSINF1S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [242] ComConf_ComSignal_VPSINFSS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [243] ComConf_ComSignal_VPSOTAS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [244] ComConf_ComSignal_APOFRQS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [245] ComConf_ComSignal_FV1E4_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [246] ComConf_ComSignal_KZK1E4_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [247] ComConf_ComSignal_ST1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [248] ComConf_ComSignal_ST1PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [249] ComConf_ComSignal_ST2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [250] ComConf_ComSignal_ST2PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [251] ComConf_ComSignal_ST3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [252] ComConf_ComSignal_ST3PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [253] ComConf_ComSignal_ST4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [254] ComConf_ComSignal_ST4PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [255] ComConf_ComSignal_ST5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [256] ComConf_ComSignal_ST5PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [257] ComConf_ComSignal_ST6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [258] ComConf_ComSignal_ST6PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [259] ComConf_ComSignal_ST7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [260] ComConf_ComSignal_ST7PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [261] ComConf_ComSignal_ST8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [262] ComConf_ComSignal_ST8PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [263] ComConf_ComSignal_ST9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [264] ComConf_ComSignal_ST9PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [265] ComConf_ComSignal_ST10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [266] ComConf_ComSignal_ST10PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [267] ComConf_ComSignal_ST11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [268] ComConf_ComSignal_ST11PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [269] ComConf_ComSignal_ST12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [270] ComConf_ComSignal_ST12PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [271] ComConf_ComSignal_ST13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [272] ComConf_ComSignal_ST13PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [273] ComConf_ComSignal_ST14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [274] ComConf_ComSignal_ST14PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [275] ComConf_ComSignal_ST15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [276] ComConf_ComSignal_ST15PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [277] ComConf_ComSignal_ST16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [278] ComConf_ComSignal_ST16PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [279] ComConf_ComSignal_ST17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [280] ComConf_ComSignal_ST17PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [281] ComConf_ComSignal_ST18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [282] ComConf_ComSignal_ST18PER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [283] ComConf_ComSignal_MSONS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [284] ComConf_ComSignal_UMIIFS5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [285] ComConf_ComSignal_UMIREQS5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [286] ComConf_ComSignal_UMIRSVS5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [287] ComConf_ComSignal_UMIDATS5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [288] ComConf_ComSignal_UMIIFS6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [289] ComConf_ComSignal_UMIREQS6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [290] ComConf_ComSignal_UMIRSVS6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [291] ComConf_ComSignal_UMIDATS6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [292] ComConf_ComSignal_UMIIFS7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [293] ComConf_ComSignal_UMIREQS7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [294] ComConf_ComSignal_UMIRSVS7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [295] ComConf_ComSignal_UMIDATS7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [296] ComConf_ComSignal_UMIIFS8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [297] ComConf_ComSignal_UMIREQS8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [298] ComConf_ComSignal_UMIRSVS8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [299] ComConf_ComSignal_UMIDATS8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [300] ComConf_ComSignal_UMIIFS9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [301] ComConf_ComSignal_UMIREQS9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [302] ComConf_ComSignal_UMIRSVS9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [303] ComConf_ComSignal_UMIDATS9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [304] ComConf_ComSignal_UMIIFS10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [305] ComConf_ComSignal_UMIRQS10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [306] ComConf_ComSignal_UMIRVS10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [307] ComConf_ComSignal_UMIDTS10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [308] ComConf_ComSignal_UMIIFS11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [309] ComConf_ComSignal_UMIRQS11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [310] ComConf_ComSignal_UMIRVS11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [311] ComConf_ComSignal_UMIDTS11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [312] ComConf_ComSignal_UMIIFS12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [313] ComConf_ComSignal_UMIRQS12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [314] ComConf_ComSignal_UMIRVS12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [315] ComConf_ComSignal_UMIDTS12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [316] ComConf_ComSignal_UMIIFS13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [317] ComConf_ComSignal_UMIRQS13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [318] ComConf_ComSignal_UMIRVS13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [319] ComConf_ComSignal_UMIDTS13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [320] ComConf_ComSignal_UMIIFS14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [321] ComConf_ComSignal_UMIRQS14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [322] ComConf_ComSignal_UMIRVS14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [323] ComConf_ComSignal_UMIDTS14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [324] ComConf_ComSignal_UMIIFS15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [325] ComConf_ComSignal_UMIRQS15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [326] ComConf_ComSignal_UMIRVS15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [327] ComConf_ComSignal_UMIDTS15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [328] ComConf_ComSignal_UMIIFS16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [329] ComConf_ComSignal_UMIRQS16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [330] ComConf_ComSignal_UMIRVS16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [331] ComConf_ComSignal_UMIDTS16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [332] ComConf_ComSignal_ACPRE_AD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [333] ComConf_ComSignal_EXPMIP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [334] ComConf_ComSignal_AMR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [335] ComConf_ComSignal_MIP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [336] ComConf_ComSignal_AIT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [337] ComConf_ComSignal_FV37B_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [338] ComConf_ComSignal_KZK37B_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [339] ComConf_ComSignal_HVH_ATPW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [340] ComConf_ComSignal_HVH_CLOT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [341] ComConf_ComSignal_COMPRP_A */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [342] ComConf_ComSignal_ACMODE_P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [343] ComConf_ComSignal_ETHWU_21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [344] ComConf_ComSignal_ETHWU_23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [345] ComConf_ComSignal_HED_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [346] ComConf_ComSignal_TAL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [347] ComConf_ComSignal_DRL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [348] ComConf_ComSignal_AUT_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [349] ComConf_ComSignal_OFF_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [350] ComConf_ComSignal_AHB_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [351] ComConf_ComSignal_PAS_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [352] ComConf_ComSignal_HIB_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [353] ComConf_ComSignal_BW_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [354] ComConf_ComSignal_RFG_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [355] ComConf_ComSignal_FOG_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [356] ComConf_ComSignal_CRGL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [357] ComConf_ComSignal_CRGR_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [358] ComConf_ComSignal_TRNL_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [359] ComConf_ComSignal_TRNR_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [360] ComConf_ComSignal_CXP_JDGT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [361] ComConf_ComSignal_WVR_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [362] ComConf_ComSignal_WSW_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [363] ComConf_ComSignal_WRSW_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [364] ComConf_ComSignal_WRON_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [365] ComConf_ComSignal_WRIN_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [366] ComConf_ComSignal_WINT_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [367] ComConf_ComSignal_WMST_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [368] ComConf_ComSignal_WA_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [369] ComConf_ComSignal_WHI_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [370] ComConf_ComSignal_WLO_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [371] ComConf_ComSignal_WOFF_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [372] ComConf_ComSignal_WAI_S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [373] ComConf_ComSignal_CXP_JDGW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [374] ComConf_ComSignal_ETHWU_32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [375] ComConf_ComSignal_THR_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [376] ComConf_ComSignal_TMO_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [377] ComConf_ComSignal_TTA_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [378] ComConf_ComSignal_RTA_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [379] ComConf_ComSignal_TR_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [380] ComConf_ComSignal_TM_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [381] ComConf_ComSignal_NR_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [382] ComConf_ComSignal_NM_GLOB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [383] ComConf_ComSignal_NMRBR_MD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [384] ComConf_ComSignal_BHSWEXT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [385] ComConf_ComSignal_NMRBSWEX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [386] ComConf_ComSignal_GRLGDBCR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [387] ComConf_ComSignal_BSTCNTRE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [388] ComConf_ComSignal_BSTCNT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [389] ComConf_ComSignal_CPMTSWEX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [390] ComConf_ComSignal_CPCMTVL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [391] ComConf_ComSignal_CPSMPIN5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [392] ComConf_ComSignal_BSTSTAT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [393] ComConf_ComSignal_CPSMPIN4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [394] ComConf_ComSignal_CPSMPIN3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [395] ComConf_ComSignal_BSTSWBB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [396] ComConf_ComSignal_CPSMPEX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [397] ComConf_ComSignal_CPSMPIN2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [398] ComConf_ComSignal_CPSMPIN1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [399] ComConf_ComSignal_CPDRSWEX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [400] ComConf_ComSignal_CPCDRVL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [401] ComConf_ComSignal_CP2DMC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [402] ComConf_ComSignal_BSTREJ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [403] ComConf_ComSignal_CP2DMC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [404] ComConf_ComSignal_CP2DMER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [405] ComConf_ComSignal_CP2DMEX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [406] ComConf_ComSignal_BSTCODE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [407] ComConf_ComSignal_CPCTFRCV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [408] ComConf_ComSignal_BSTMET */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [409] ComConf_ComSignal_CPCTFRMV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [410] ComConf_ComSignal_CPCTFRER */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [411] ComConf_ComSignal_B_CPMODE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [412] ComConf_ComSignal_CPSSWEX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [413] ComConf_ComSignal_DMCNVINF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [414] ComConf_ComSignal_CPCTFREX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [415] ComConf_ComSignal_CNV_MODE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [416] ComConf_ComSignal_DMCNVVLD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [417] ComConf_ComSignal_DMCNMDVL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [418] ComConf_ComSignal_XCDRST2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [419] ComConf_ComSignal_XCDRST1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [420] ComConf_ComSignal_CUMTEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [421] ComConf_ComSignal_CUMTEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [422] ComConf_ComSignal_CRDRVEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [423] ComConf_ComSignal_CRDRVEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [424] ComConf_ComSignal_CRALTEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [425] ComConf_ComSignal_CRALTEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [426] ComConf_ComSignal_CRACEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [427] ComConf_ComSignal_CRACEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [428] ComConf_ComSignal_CRPACEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [429] ComConf_ComSignal_CRPACEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [430] ComConf_ComSignal_CRBPEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [431] ComConf_ComSignal_CRBPEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [432] ComConf_ComSignal_CRPBPEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [433] ComConf_ComSignal_CRPBPEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [434] ComConf_ComSignal_CRDAEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [435] ComConf_ComSignal_CRDAEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [436] ComConf_ComSignal_CRPAEC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [437] ComConf_ComSignal_CRPAEC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [438] ComConf_ComSignal_RSISDKME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [439] ComConf_ComSignal_RSISIDDK */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [440] ComConf_ComSignal_DESMUTE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [441] ComConf_ComSignal_DREBUID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [442] ComConf_ComSignal_DREBU02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [443] ComConf_ComSignal_DREBU03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [444] ComConf_ComSignal_DREBU04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [445] ComConf_ComSignal_DREBU05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [446] ComConf_ComSignal_DREBU06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [447] ComConf_ComSignal_DREBU07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [448] ComConf_ComSignal_DREBU08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [449] ComConf_ComSignal_DREBU11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [450] ComConf_ComSignal_DREBU12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [451] ComConf_ComSignal_DREBU13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [452] ComConf_ComSignal_DREBU14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [453] ComConf_ComSignal_DREBU15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [454] ComConf_ComSignal_DREBU16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [455] ComConf_ComSignal_DREBU17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [456] ComConf_ComSignal_DREBU18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [457] ComConf_ComSignal_DREBU21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [458] ComConf_ComSignal_DREBU22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [459] ComConf_ComSignal_DREBU23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [460] ComConf_ComSignal_DREBU24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [461] ComConf_ComSignal_DREBU25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [462] ComConf_ComSignal_DREBU26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [463] ComConf_ComSignal_DREBU27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [464] ComConf_ComSignal_DREBU28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [465] ComConf_ComSignal_DREBU31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [466] ComConf_ComSignal_DREBU32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [467] ComConf_ComSignal_DREBU33 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [468] ComConf_ComSignal_DREBU34 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [469] ComConf_ComSignal_DREBU35 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [470] ComConf_ComSignal_DREBU36 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [471] ComConf_ComSignal_DREBU37 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [472] ComConf_ComSignal_DREBU38 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [473] ComConf_ComSignal_DRDYSTS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [474] ComConf_ComSignal_DRDYB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [475] ComConf_ComSignal_STRGCM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [476] ComConf_ComSignal_HV_SRGMD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [477] ComConf_ComSignal_TQRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [478] ComConf_ComSignal_TQFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [479] ComConf_ComSignal_FCRF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [480] ComConf_ComSignal_CLE_SOCF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [481] ComConf_ComSignal_SDRVRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [482] ComConf_ComSignal_SDRVFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [483] ComConf_ComSignal_E_CRC0A1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [484] ComConf_ComSignal_E_CNT0A1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [485] ComConf_ComSignal_HVMRADRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [486] ComConf_ComSignal_HVMRADFR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [487] ComConf_ComSignal_ETRQ_FS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [488] ComConf_ComSignal_HVRADRRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [489] ComConf_ComSignal_HVRADRRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [490] ComConf_ComSignal_HVRADFRL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [491] ComConf_ComSignal_HVRADFRR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [492] ComConf_ComSignal_DREIMABN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [493] ComConf_ComSignal_I_BAT_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [494] ComConf_ComSignal_U_BAT_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [495] ComConf_ComSignal_PWDTY_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [496] ComConf_ComSignal_VLO_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [497] ComConf_ComSignal_PWIF1_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [498] ComConf_ComSignal_T_BAT_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [499] ComConf_ComSignal_PWIF2_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [500] ComConf_ComSignal_SOCS_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [501] ComConf_ComSignal_SOC_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [502] ComConf_ComSignal_PWIF3_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [503] ComConf_ComSignal_PWIF4_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [504] ComConf_ComSignal_PWIF5_BD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [505] ComConf_ComSignal_DRENG11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [506] ComConf_ComSignal_DRENG12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [507] ComConf_ComSignal_DRENG13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [508] ComConf_ComSignal_DRENG14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [509] ComConf_ComSignal_DRENG15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [510] ComConf_ComSignal_DRENG16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [511] ComConf_ComSignal_DRENG17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [512] ComConf_ComSignal_DRENG18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [513] ComConf_ComSignal_DRENG21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [514] ComConf_ComSignal_DRENG22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [515] ComConf_ComSignal_DRENG23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [516] ComConf_ComSignal_DRENG24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [517] ComConf_ComSignal_DRENG25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [518] ComConf_ComSignal_DRENG26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [519] ComConf_ComSignal_DRENG27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [520] ComConf_ComSignal_DRENG28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [521] ComConf_ComSignal_DRENG31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [522] ComConf_ComSignal_DRENG32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [523] ComConf_ComSignal_DRENG33 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [524] ComConf_ComSignal_DRENG34 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [525] ComConf_ComSignal_DRENG35 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [526] ComConf_ComSignal_DRENG36 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [527] ComConf_ComSignal_DRENG37 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [528] ComConf_ComSignal_DRENG38 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [529] ComConf_ComSignal_DRENG51 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [530] ComConf_ComSignal_DRENG52 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [531] ComConf_ComSignal_DRENG53 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [532] ComConf_ComSignal_DRENG54 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [533] ComConf_ComSignal_DRENG55 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [534] ComConf_ComSignal_DRENG56 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [535] ComConf_ComSignal_DRENG57 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [536] ComConf_ComSignal_DRENG58 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [537] ComConf_ComSignal_DRENG61 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [538] ComConf_ComSignal_DRENG62 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [539] ComConf_ComSignal_DRENG63 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [540] ComConf_ComSignal_DRENG64 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [541] ComConf_ComSignal_DRENG65 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [542] ComConf_ComSignal_DRENG66 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [543] ComConf_ComSignal_DRENG67 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [544] ComConf_ComSignal_DRENG68 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [545] ComConf_ComSignal_DRENG91 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [546] ComConf_ComSignal_DRENG92 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [547] ComConf_ComSignal_DRENG93 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [548] ComConf_ComSignal_DRENG94 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [549] ComConf_ComSignal_DRENG95 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [550] ComConf_ComSignal_DRENG96 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [551] ComConf_ComSignal_DRENG97 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [552] ComConf_ComSignal_DRENG98 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [553] ComConf_ComSignal_DRENG101 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [554] ComConf_ComSignal_DRENG102 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [555] ComConf_ComSignal_DRENG103 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [556] ComConf_ComSignal_DRENG104 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [557] ComConf_ComSignal_DRENG105 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [558] ComConf_ComSignal_DRENG106 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [559] ComConf_ComSignal_DRENG107 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [560] ComConf_ComSignal_DRENG108 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [561] ComConf_ComSignal_VIN_1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [562] ComConf_ComSignal_VIN_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [563] ComConf_ComSignal_VIN_3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [564] ComConf_ComSignal_VIN_4 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [565] ComConf_ComSignal_VIN_5 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [566] ComConf_ComSignal_VIN_6 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [567] ComConf_ComSignal_VIN_7 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [568] ComConf_ComSignal_VIN_8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [569] ComConf_ComSignal_VIN_9 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [570] ComConf_ComSignal_VIN_10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [571] ComConf_ComSignal_VIN_11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [572] ComConf_ComSignal_VIN_12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [573] ComConf_ComSignal_VIN_13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [574] ComConf_ComSignal_VIN_14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [575] ComConf_ComSignal_VIN_15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [576] ComConf_ComSignal_VIN_16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [577] ComConf_ComSignal_VIN_17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [578] ComConf_ComSignal_DREPS01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [579] ComConf_ComSignal_DREPS02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [580] ComConf_ComSignal_DREPS03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [581] ComConf_ComSignal_DREPS04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [582] ComConf_ComSignal_DREPS05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [583] ComConf_ComSignal_DREPS06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [584] ComConf_ComSignal_DREPS07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [585] ComConf_ComSignal_DREPS08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [586] ComConf_ComSignal_V_DIST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [587] ComConf_ComSignal_V_RELV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [588] ComConf_ComSignal_V_SWOP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [589] ComConf_ComSignal_RCURVR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [590] ComConf_ComSignal_USMDSTTS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [591] ComConf_ComSignal_COFFSET */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [592] ComConf_ComSignal_USMDSTSL */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [593] ComConf_ComSignal_RSACAUF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [594] ComConf_ComSignal_OTHVW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [595] ComConf_ComSignal_OTHVH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [596] ComConf_ComSignal_OTHPB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [597] ComConf_ComSignal_OTHTTC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [598] ComConf_ComSignal_OTHTTYP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [599] ComConf_ComSignal_FSPCSSTA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [600] ComConf_ComSignal_HITPOS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [601] ComConf_ComSignal_OTHRDANG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [602] ComConf_ComSignal_OTHTSSST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [603] ComConf_ComSignal_OTHOVLPC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [604] ComConf_ComSignal_OTHRVPC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [605] ComConf_ComSignal_OTHFALD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [606] ComConf_ComSignal_OTHCOND */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [607] ComConf_ComSignal_OTHLDIS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [608] ComConf_ComSignal_OTHFALF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [609] ComConf_ComSignal_OTHCONF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [610] ComConf_ComSignal_OTHLANE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [611] ComConf_ComSignal_OTHSOR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [612] ComConf_ComSignal_OTHROR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [613] ComConf_ComSignal_OTHLX */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [614] ComConf_ComSignal_OTHSOLAR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [615] ComConf_ComSignal_XREQFPB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [616] ComConf_ComSignal_XREQPB */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [617] ComConf_ComSignal_XREQPBH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [618] ComConf_ComSignal_E_CRC0A8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [619] ComConf_ComSignal_E_CNT0A8 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [620] ComConf_ComSignal_AVSTRGR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [621] ComConf_ComSignal_PBATRGR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [622] ComConf_ComSignal_PCSALM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [623] ComConf_ComSignal_FV0A8_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [624] ComConf_ComSignal_KZK0A8_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [625] ComConf_ComSignal_LK_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [626] ComConf_ComSignal_LK_FUNC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [627] ComConf_ComSignal_ULK_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [628] ComConf_ComSignal_ULK_FUNC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [629] ComConf_ComSignal_RSISIDME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [630] ComConf_ComSignal_RSISIDID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [631] ComConf_ComSignal_HCPCLOP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [632] ComConf_ComSignal_HCSUPEN2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [633] ComConf_ComSignal_HCSDWEN2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [634] ComConf_ComSignal_HCSUPEN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [635] ComConf_ComSignal_HCSDWEN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [636] ComConf_ComSignal_HCSMNSW */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [637] ComConf_ComSignal_HCSETDSP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [638] ComConf_ComSignal_HCSSTPOP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [639] ComConf_ComSignal_ODO_UNIT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [640] ComConf_ComSignal_ODO */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [641] ComConf_ComSignal_RTQRRLMG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [642] ComConf_ComSignal_RTQFRLMG */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [643] ComConf_ComSignal_BAOF_PDC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [644] ComConf_ComSignal_E_CRC14F */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [645] ComConf_ComSignal_E_CNT14F */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [646] ComConf_ComSignal_RCPMD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [647] ComConf_ComSignal_RCPONST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [648] ComConf_ComSignal_LOC_ICON */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [649] ComConf_ComSignal_RT_NUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [650] ComConf_ComSignal_RPCTRMD2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [651] ComConf_ComSignal_RT1LBL1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [652] ComConf_ComSignal_RT1LBL2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [653] ComConf_ComSignal_RT1LEN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [654] ComConf_ComSignal_RT1WPNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [655] ComConf_ComSignal_RT2LBL1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [656] ComConf_ComSignal_RT2LBL2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [657] ComConf_ComSignal_RT2LEN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [658] ComConf_ComSignal_RT2WPNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [659] ComConf_ComSignal_RT3LBL1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [660] ComConf_ComSignal_RT3LBL2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [661] ComConf_ComSignal_RT3LEN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [662] ComConf_ComSignal_RT3WPNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [663] ComConf_ComSignal_RT4LBL1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [664] ComConf_ComSignal_RT4LBL2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [665] ComConf_ComSignal_RT4LEN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [666] ComConf_ComSignal_RT4WPNUM */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [667] ComConf_ComSignal_RPVCLST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [668] ComConf_ComSignal_RT_ID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [669] ComConf_ComSignal_WP1_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [670] ComConf_ComSignal_WP1_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [671] ComConf_ComSignal_WP1_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [672] ComConf_ComSignal_WP1_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [673] ComConf_ComSignal_WP2_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [674] ComConf_ComSignal_WP2_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [675] ComConf_ComSignal_WP2_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [676] ComConf_ComSignal_WP2_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [677] ComConf_ComSignal_WP3_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [678] ComConf_ComSignal_WP3_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [679] ComConf_ComSignal_WP3_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [680] ComConf_ComSignal_WP3_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [681] ComConf_ComSignal_WP4_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [682] ComConf_ComSignal_WP4_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [683] ComConf_ComSignal_WP4_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [684] ComConf_ComSignal_WP4_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [685] ComConf_ComSignal_WP5_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [686] ComConf_ComSignal_WP5_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [687] ComConf_ComSignal_WP5_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [688] ComConf_ComSignal_WP5_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [689] ComConf_ComSignal_WP6_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [690] ComConf_ComSignal_WP6_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [691] ComConf_ComSignal_WP6_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [692] ComConf_ComSignal_WP6_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [693] ComConf_ComSignal_WP7_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [694] ComConf_ComSignal_WP7_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [695] ComConf_ComSignal_WP7_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [696] ComConf_ComSignal_WP7_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [697] ComConf_ComSignal_WP8_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [698] ComConf_ComSignal_WP8_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [699] ComConf_ComSignal_WP8_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [700] ComConf_ComSignal_WP8_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [701] ComConf_ComSignal_WP9_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [702] ComConf_ComSignal_WP9_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [703] ComConf_ComSignal_WP9_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [704] ComConf_ComSignal_WP9_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [705] ComConf_ComSignal_WP10_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [706] ComConf_ComSignal_WP10_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [707] ComConf_ComSignal_WP10_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [708] ComConf_ComSignal_WP10_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [709] ComConf_ComSignal_WP11_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [710] ComConf_ComSignal_WP11_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [711] ComConf_ComSignal_WP11_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [712] ComConf_ComSignal_WP11_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [713] ComConf_ComSignal_WP12_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [714] ComConf_ComSignal_WP12_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [715] ComConf_ComSignal_WP12_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [716] ComConf_ComSignal_WP12_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [717] ComConf_ComSignal_WP13_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [718] ComConf_ComSignal_WP13_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [719] ComConf_ComSignal_WP13_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [720] ComConf_ComSignal_WP13_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [721] ComConf_ComSignal_WP14_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [722] ComConf_ComSignal_WP14_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [723] ComConf_ComSignal_WP14_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [724] ComConf_ComSignal_WP14_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [725] ComConf_ComSignal_WP15_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [726] ComConf_ComSignal_WP15_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [727] ComConf_ComSignal_WP15_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [728] ComConf_ComSignal_WP15_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [729] ComConf_ComSignal_WP16_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [730] ComConf_ComSignal_WP16_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [731] ComConf_ComSignal_WP16_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [732] ComConf_ComSignal_WP16_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [733] ComConf_ComSignal_WP17_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [734] ComConf_ComSignal_WP17_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [735] ComConf_ComSignal_WP17_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [736] ComConf_ComSignal_WP17_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [737] ComConf_ComSignal_WP18_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [738] ComConf_ComSignal_WP18_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [739] ComConf_ComSignal_WP18_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [740] ComConf_ComSignal_WP18_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [741] ComConf_ComSignal_WP19_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [742] ComConf_ComSignal_WP19_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [743] ComConf_ComSignal_WP19_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [744] ComConf_ComSignal_WP19_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [745] ComConf_ComSignal_WP20_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [746] ComConf_ComSignal_WP20_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [747] ComConf_ComSignal_WP20_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [748] ComConf_ComSignal_WP20_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [749] ComConf_ComSignal_WP21_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [750] ComConf_ComSignal_WP21_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [751] ComConf_ComSignal_WP21_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [752] ComConf_ComSignal_WP21_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [753] ComConf_ComSignal_WP22_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [754] ComConf_ComSignal_WP22_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [755] ComConf_ComSignal_WP22_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [756] ComConf_ComSignal_WP22_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [757] ComConf_ComSignal_WP23_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [758] ComConf_ComSignal_WP23_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [759] ComConf_ComSignal_WP23_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [760] ComConf_ComSignal_WP23_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [761] ComConf_ComSignal_WP24_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [762] ComConf_ComSignal_WP24_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [763] ComConf_ComSignal_WP24_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [764] ComConf_ComSignal_WP24_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [765] ComConf_ComSignal_WP25_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [766] ComConf_ComSignal_WP25_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [767] ComConf_ComSignal_WP25_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [768] ComConf_ComSignal_WP25_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [769] ComConf_ComSignal_WP26_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [770] ComConf_ComSignal_WP26_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [771] ComConf_ComSignal_WP26_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [772] ComConf_ComSignal_WP26_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [773] ComConf_ComSignal_WP27_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [774] ComConf_ComSignal_WP27_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [775] ComConf_ComSignal_WP27_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [776] ComConf_ComSignal_WP27_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [777] ComConf_ComSignal_WP28_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [778] ComConf_ComSignal_WP28_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [779] ComConf_ComSignal_WP28_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [780] ComConf_ComSignal_WP28_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [781] ComConf_ComSignal_WP29_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [782] ComConf_ComSignal_WP29_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [783] ComConf_ComSignal_WP29_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [784] ComConf_ComSignal_WP29_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [785] ComConf_ComSignal_WP30_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [786] ComConf_ComSignal_WP30_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [787] ComConf_ComSignal_WP30_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [788] ComConf_ComSignal_WP30_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [789] ComConf_ComSignal_WP31_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [790] ComConf_ComSignal_WP31_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [791] ComConf_ComSignal_WP31_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [792] ComConf_ComSignal_WP31_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [793] ComConf_ComSignal_WP32_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [794] ComConf_ComSignal_WP32_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [795] ComConf_ComSignal_WP32_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [796] ComConf_ComSignal_WP32_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [797] ComConf_ComSignal_WP33_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [798] ComConf_ComSignal_WP33_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [799] ComConf_ComSignal_WP33_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [800] ComConf_ComSignal_WP33_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [801] ComConf_ComSignal_WP34_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [802] ComConf_ComSignal_WP34_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [803] ComConf_ComSignal_WP34_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [804] ComConf_ComSignal_WP34_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [805] ComConf_ComSignal_WP35_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [806] ComConf_ComSignal_WP35_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [807] ComConf_ComSignal_WP35_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [808] ComConf_ComSignal_WP35_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [809] ComConf_ComSignal_WP36_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [810] ComConf_ComSignal_WP36_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [811] ComConf_ComSignal_WP36_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [812] ComConf_ComSignal_WP36_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [813] ComConf_ComSignal_WP37_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [814] ComConf_ComSignal_WP37_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [815] ComConf_ComSignal_WP37_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [816] ComConf_ComSignal_WP37_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [817] ComConf_ComSignal_WP38_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [818] ComConf_ComSignal_WP38_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [819] ComConf_ComSignal_WP38_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [820] ComConf_ComSignal_WP38_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [821] ComConf_ComSignal_WP39_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [822] ComConf_ComSignal_WP39_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [823] ComConf_ComSignal_WP39_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [824] ComConf_ComSignal_WP39_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [825] ComConf_ComSignal_WP40_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [826] ComConf_ComSignal_WP40_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [827] ComConf_ComSignal_WP40_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [828] ComConf_ComSignal_WP40_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [829] ComConf_ComSignal_WP41_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [830] ComConf_ComSignal_WP41_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [831] ComConf_ComSignal_WP41_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [832] ComConf_ComSignal_WP41_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [833] ComConf_ComSignal_WP42_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [834] ComConf_ComSignal_WP42_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [835] ComConf_ComSignal_WP42_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [836] ComConf_ComSignal_WP42_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [837] ComConf_ComSignal_WP43_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [838] ComConf_ComSignal_WP43_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [839] ComConf_ComSignal_WP43_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [840] ComConf_ComSignal_WP43_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [841] ComConf_ComSignal_WP44_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [842] ComConf_ComSignal_WP44_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [843] ComConf_ComSignal_WP44_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [844] ComConf_ComSignal_WP44_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [845] ComConf_ComSignal_WP45_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [846] ComConf_ComSignal_WP45_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [847] ComConf_ComSignal_WP45_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [848] ComConf_ComSignal_WP45_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [849] ComConf_ComSignal_WP46_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [850] ComConf_ComSignal_WP46_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [851] ComConf_ComSignal_WP46_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [852] ComConf_ComSignal_WP46_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [853] ComConf_ComSignal_WP47_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [854] ComConf_ComSignal_WP47_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [855] ComConf_ComSignal_WP47_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [856] ComConf_ComSignal_WP47_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [857] ComConf_ComSignal_WP48_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [858] ComConf_ComSignal_WP48_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [859] ComConf_ComSignal_WP48_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [860] ComConf_ComSignal_WP48_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [861] ComConf_ComSignal_WP49_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [862] ComConf_ComSignal_WP49_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [863] ComConf_ComSignal_WP49_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [864] ComConf_ComSignal_WP49_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [865] ComConf_ComSignal_WP50_TYPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [866] ComConf_ComSignal_WP50_X */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [867] ComConf_ComSignal_WP50_Y */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [868] ComConf_ComSignal_WP50_DIR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [869] ComConf_ComSignal_D_YEAR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [870] ComConf_ComSignal_D_MONT */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [871] ComConf_ComSignal_D_DAY */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [872] ComConf_ComSignal_D_HOUR */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [873] ComConf_ComSignal_D_MIN */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [874] ComConf_ComSignal_D_SEC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [875] ComConf_ComSignal_GNSSYNC1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [876] ComConf_ComSignal_VA_INVA */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [877] ComConf_ComSignal_LATUDE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [878] ComConf_ComSignal_LOTUDE1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [879] ComConf_ComSignal_D_LAT1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [880] ComConf_ComSignal_D_LAT2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [881] ComConf_ComSignal_GNSSYNC2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [882] ComConf_ComSignal_D_LON1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [883] ComConf_ComSignal_D_LON2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [884] ComConf_ComSignal_GNSSYNC3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [885] ComConf_ComSignal_ALTITUDE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [886] ComConf_ComSignal_RSCYCL11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [887] ComConf_ComSignal_RSCYCL12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [888] ComConf_ComSignal_RSCYCL13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [889] ComConf_ComSignal_RSCYCL14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [890] ComConf_ComSignal_RSCYCL15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [891] ComConf_ComSignal_RSCYCL16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [892] ComConf_ComSignal_DVGR01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [893] ComConf_ComSignal_DVGR02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [894] ComConf_ComSignal_DVGR03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [895] ComConf_ComSignal_DVGR04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [896] ComConf_ComSignal_DVGR05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [897] ComConf_ComSignal_DVGR06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [898] ComConf_ComSignal_DVGR07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [899] ComConf_ComSignal_DVGR08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [900] ComConf_ComSignal_DVGR09 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [901] ComConf_ComSignal_DVGR10 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [902] ComConf_ComSignal_DVGR11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [903] ComConf_ComSignal_DVGR12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [904] ComConf_ComSignal_DVGR13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [905] ComConf_ComSignal_DVGR14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [906] ComConf_ComSignal_DVGR15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [907] ComConf_ComSignal_DVGR16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [908] ComConf_ComSignal_DVGR17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [909] ComConf_ComSignal_DVGR18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [910] ComConf_ComSignal_DVGR19 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [911] ComConf_ComSignal_DVGR20 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [912] ComConf_ComSignal_DVGR21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [913] ComConf_ComSignal_DVGR22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [914] ComConf_ComSignal_DVGR23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [915] ComConf_ComSignal_DVGR24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [916] ComConf_ComSignal_DVGR25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [917] ComConf_ComSignal_DVGR26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [918] ComConf_ComSignal_DVGR27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [919] ComConf_ComSignal_DVGR28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [920] ComConf_ComSignal_DVGR29 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [921] ComConf_ComSignal_DVGR30 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [922] ComConf_ComSignal_DVGR31 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [923] ComConf_ComSignal_DVGR32 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [924] ComConf_ComSignal_DRVSCID */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [925] ComConf_ComSignal_DRVSC02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [926] ComConf_ComSignal_DRVSC03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [927] ComConf_ComSignal_DRVSC04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [928] ComConf_ComSignal_DRVSC05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [929] ComConf_ComSignal_DRVSC06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [930] ComConf_ComSignal_DRVSC07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [931] ComConf_ComSignal_DRVSC08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [932] ComConf_ComSignal_DRVSC11 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [933] ComConf_ComSignal_DRVSC12 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [934] ComConf_ComSignal_DRVSC13 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [935] ComConf_ComSignal_DRVSC14 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [936] ComConf_ComSignal_DRVSC15 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [937] ComConf_ComSignal_DRVSC16 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [938] ComConf_ComSignal_DRVSC17 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [939] ComConf_ComSignal_DRVSC18 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [940] ComConf_ComSignal_DRVSC21 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [941] ComConf_ComSignal_DRVSC22 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [942] ComConf_ComSignal_DRVSC23 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [943] ComConf_ComSignal_DRVSC24 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [944] ComConf_ComSignal_DRVSC25 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [945] ComConf_ComSignal_DRVSC26 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [946] ComConf_ComSignal_DRVSC27 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [947] ComConf_ComSignal_DRVSC28 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [948] ComConf_ComSignal_DREPB01 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [949] ComConf_ComSignal_DREPB02 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [950] ComConf_ComSignal_DREPB03 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [951] ComConf_ComSignal_DREPB04 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [952] ComConf_ComSignal_DREPB05 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [953] ComConf_ComSignal_DREPB06 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [954] ComConf_ComSignal_DREPB07 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [955] ComConf_ComSignal_DREPB08 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [956] ComConf_ComSignal_E_CRC09E */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [957] ComConf_ComSignal_E_CNT09E */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [958] ComConf_ComSignal_SP1S */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [959] ComConf_ComSignal_GVSPDINV */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [960] ComConf_ComSignal_SP1P */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [961] ComConf_ComSignal_SP1 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [962] ComConf_ComSignal_GVSPD */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [963] ComConf_ComSignal_PWCF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [964] ComConf_ComSignal_PWC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [965] ComConf_ComSignal_PWCS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [966] ComConf_ComSignal_PMCF */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [967] ComConf_ComSignal_PMCS */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [968] ComConf_ComSignal_PMC */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [969] ComConf_ComSignal_FV09E_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [970] ComConf_ComSignal_KZK09E_D */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [971] ComConf_ComSignal_FRWIPOPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [972] ComConf_ComSignal_FRWASH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [973] ComConf_ComSignal_RRWIPOPE */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [974] ComConf_ComSignal_RRWASH */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [975] ComConf_ComSignal_W_STPZ */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [976] ComConf_ComSignal_FI_STP */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [977] ComConf_ComSignal_R_AC_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [978] ComConf_ComSignal_R_SYS_2 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [979] ComConf_ComSignal_R_FTE_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [980] ComConf_ComSignal_R_BD_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [981] ComConf_ComSignal_R_TIME */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [982] ComConf_ComSignal_R_INT_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [983] ComConf_ComSignal_R_LMP_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [984] ComConf_ComSignal_R_SDE_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [985] ComConf_ComSignal_R_SYS_3 */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [986] ComConf_ComSignal_R_ST_ST */
    ,BSW_COM_u1EVCOND_NONE                                                                                       /* [987] ComConf_ComSignal_R_SYS_1 */
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
    ,(BswU2)2U                                                                                                   /* [16] ComConf_ComSignal_FLGXMAX */
    ,(BswU2)2U                                                                                                   /* [17] ComConf_ComSignal_FLVNMAX */
    ,(BswU2)2U                                                                                                   /* [18] ComConf_ComSignal_FRGMAX_L */
    ,(BswU2)2U                                                                                                   /* [19] ComConf_ComSignal_FRGMAX_R */
    ,(BswU2)2U                                                                                                   /* [20] ComConf_ComSignal_PT_ON */
    ,(BswU2)2U                                                                                                   /* [21] ComConf_ComSignal_FRAB_ON */
    ,(BswU2)3U                                                                                                   /* [22] ComConf_ComSignal_DRACN01 */
    ,(BswU2)3U                                                                                                   /* [23] ComConf_ComSignal_DRACN02 */
    ,(BswU2)3U                                                                                                   /* [24] ComConf_ComSignal_DRACN03 */
    ,(BswU2)3U                                                                                                   /* [25] ComConf_ComSignal_DRACN04 */
    ,(BswU2)3U                                                                                                   /* [26] ComConf_ComSignal_DRACN05 */
    ,(BswU2)3U                                                                                                   /* [27] ComConf_ComSignal_DRACN06 */
    ,(BswU2)3U                                                                                                   /* [28] ComConf_ComSignal_DRACN07 */
    ,(BswU2)3U                                                                                                   /* [29] ComConf_ComSignal_DRACN08 */
    ,(BswU2)3U                                                                                                   /* [30] ComConf_ComSignal_DRACN09 */
    ,(BswU2)3U                                                                                                   /* [31] ComConf_ComSignal_DRACN10 */
    ,(BswU2)3U                                                                                                   /* [32] ComConf_ComSignal_DRACN11 */
    ,(BswU2)3U                                                                                                   /* [33] ComConf_ComSignal_DRACN12 */
    ,(BswU2)3U                                                                                                   /* [34] ComConf_ComSignal_DRACN13 */
    ,(BswU2)3U                                                                                                   /* [35] ComConf_ComSignal_DRACN14 */
    ,(BswU2)3U                                                                                                   /* [36] ComConf_ComSignal_DRACN15 */
    ,(BswU2)3U                                                                                                   /* [37] ComConf_ComSignal_DRACN16 */
    ,(BswU2)3U                                                                                                   /* [38] ComConf_ComSignal_DRACN17 */
    ,(BswU2)3U                                                                                                   /* [39] ComConf_ComSignal_DRACN18 */
    ,(BswU2)3U                                                                                                   /* [40] ComConf_ComSignal_DRACN19 */
    ,(BswU2)3U                                                                                                   /* [41] ComConf_ComSignal_DRACN20 */
    ,(BswU2)3U                                                                                                   /* [42] ComConf_ComSignal_DRACN21 */
    ,(BswU2)3U                                                                                                   /* [43] ComConf_ComSignal_DRACN22 */
    ,(BswU2)3U                                                                                                   /* [44] ComConf_ComSignal_DRACN23 */
    ,(BswU2)3U                                                                                                   /* [45] ComConf_ComSignal_DRACN24 */
    ,(BswU2)3U                                                                                                   /* [46] ComConf_ComSignal_DRACN25 */
    ,(BswU2)3U                                                                                                   /* [47] ComConf_ComSignal_DRACN26 */
    ,(BswU2)3U                                                                                                   /* [48] ComConf_ComSignal_DRACN27 */
    ,(BswU2)3U                                                                                                   /* [49] ComConf_ComSignal_DRACN28 */
    ,(BswU2)3U                                                                                                   /* [50] ComConf_ComSignal_DRACN29 */
    ,(BswU2)3U                                                                                                   /* [51] ComConf_ComSignal_DRACN30 */
    ,(BswU2)3U                                                                                                   /* [52] ComConf_ComSignal_DRACN31 */
    ,(BswU2)3U                                                                                                   /* [53] ComConf_ComSignal_DRACN32 */
    ,(BswU2)4U                                                                                                   /* [54] ComConf_ComSignal_O_STG_F */
    ,(BswU2)4U                                                                                                   /* [55] ComConf_ComSignal_O_STGH */
    ,(BswU2)4U                                                                                                   /* [56] ComConf_ComSignal_AC_CDSP */
    ,(BswU2)5U                                                                                                   /* [57] ComConf_ComSignal_TRTEMP_P */
    ,(BswU2)5U                                                                                                   /* [58] ComConf_ComSignal_I_BLWF_P */
    ,(BswU2)6U                                                                                                   /* [59] ComConf_ComSignal_HQ_COMP */
    ,(BswU2)7U                                                                                                   /* [60] ComConf_ComSignal_R_SHLOFL */
    ,(BswU2)7U                                                                                                   /* [61] ComConf_ComSignal_R_SHHTFL */
    ,(BswU2)7U                                                                                                   /* [62] ComConf_ComSignal_R_SHHTFR */
    ,(BswU2)7U                                                                                                   /* [63] ComConf_ComSignal_RSVFLDU */
    ,(BswU2)7U                                                                                                   /* [64] ComConf_ComSignal_RSVFRDU */
    ,(BswU2)7U                                                                                                   /* [65] ComConf_ComSignal_R_SHHTRL */
    ,(BswU2)7U                                                                                                   /* [66] ComConf_ComSignal_R_SHHTRR */
    ,(BswU2)7U                                                                                                   /* [67] ComConf_ComSignal_R_SHTFL3 */
    ,(BswU2)7U                                                                                                   /* [68] ComConf_ComSignal_R_SHTFL2 */
    ,(BswU2)7U                                                                                                   /* [69] ComConf_ComSignal_RSVRLDU */
    ,(BswU2)7U                                                                                                   /* [70] ComConf_ComSignal_RSVRRDU */
    ,(BswU2)8U                                                                                                   /* [71] ComConf_ComSignal_WS_VD_R */
    ,(BswU2)8U                                                                                                   /* [72] ComConf_ComSignal_WS_FTG_R */
    ,(BswU2)8U                                                                                                   /* [73] ComConf_ComSignal_WS_ABH_R */
    ,(BswU2)8U                                                                                                   /* [74] ComConf_ComSignal_WS_APO_R */
    ,(BswU2)9U                                                                                                   /* [75] ComConf_ComSignal_ETHWU_12 */
    ,(BswU2)10U                                                                                                  /* [76] ComConf_ComSignal_APPMD2 */
    ,(BswU2)10U                                                                                                  /* [77] ComConf_ComSignal_FV1C0_D */
    ,(BswU2)10U                                                                                                  /* [78] ComConf_ComSignal_KZK1C0_D */
    ,(BswU2)11U                                                                                                  /* [79] ComConf_ComSignal_ACCMAPP */
    ,(BswU2)11U                                                                                                  /* [80] ComConf_ComSignal_ACCMMOD */
    ,(BswU2)12U                                                                                                  /* [81] ComConf_ComSignal_ACCMDST */
    ,(BswU2)12U                                                                                                  /* [82] ComConf_ComSignal_ACCMPHS */
    ,(BswU2)12U                                                                                                  /* [83] ComConf_ComSignal_ACCMSGN */
    ,(BswU2)12U                                                                                                  /* [84] ComConf_ComSignal_ACCMRCG */
    ,(BswU2)12U                                                                                                  /* [85] ComConf_ComSignal_ACCMARB */
    ,(BswU2)13U                                                                                                  /* [86] ComConf_ComSignal_LDASTATL */
    ,(BswU2)13U                                                                                                  /* [87] ComConf_ComSignal_LDASTATR */
    ,(BswU2)13U                                                                                                  /* [88] ComConf_ComSignal_LDARSN */
    ,(BswU2)13U                                                                                                  /* [89] ComConf_ComSignal_FCMINTMP */
    ,(BswU2)13U                                                                                                  /* [90] ComConf_ComSignal_LDARCGL */
    ,(BswU2)13U                                                                                                  /* [91] ComConf_ComSignal_LDARCGR */
    ,(BswU2)13U                                                                                                  /* [92] ComConf_ComSignal_SWSSTAT */
    ,(BswU2)13U                                                                                                  /* [93] ComConf_ComSignal_V_IDACCL */
    ,(BswU2)13U                                                                                                  /* [94] ComConf_ComSignal_EJDEVPRD */
    ,(BswU2)13U                                                                                                  /* [95] ComConf_ComSignal_EJLDACP */
    ,(BswU2)13U                                                                                                  /* [96] ComConf_ComSignal_V_IDANOA */
    ,(BswU2)13U                                                                                                  /* [97] ComConf_ComSignal_V_IDARGL */
    ,(BswU2)13U                                                                                                  /* [98] ComConf_ComSignal_PV_AREA */
    ,(BswU2)13U                                                                                                  /* [99] ComConf_ComSignal_DM_PVMVW */
    ,(BswU2)13U                                                                                                  /* [100] ComConf_ComSignal_DM_PVMCS */
    ,(BswU2)13U                                                                                                  /* [101] ComConf_ComSignal_ERMCNTST */
    ,(BswU2)13U                                                                                                  /* [102] ComConf_ComSignal_GAE_H_R3 */
    ,(BswU2)13U                                                                                                  /* [103] ComConf_ComSignal_FRDHTR_G */
    ,(BswU2)13U                                                                                                  /* [104] ComConf_ComSignal_SDIRT_G */
    ,(BswU2)13U                                                                                                  /* [105] ComConf_ComSignal_GAE_V_R1 */
    ,(BswU2)13U                                                                                                  /* [106] ComConf_ComSignal_DRTCNT_G */
    ,(BswU2)13U                                                                                                  /* [107] ComConf_ComSignal_GAERR1_V */
    ,(BswU2)13U                                                                                                  /* [108] ComConf_ComSignal_GAEVAL_H */
    ,(BswU2)13U                                                                                                  /* [109] ComConf_ComSignal_GAERR3_H */
    ,(BswU2)13U                                                                                                  /* [110] ComConf_ComSignal_DTSSSTR */
    ,(BswU2)13U                                                                                                  /* [111] ComConf_ComSignal_DTSSLTID */
    ,(BswU2)13U                                                                                                  /* [112] ComConf_ComSignal_MDSYNC00 */
    ,(BswU2)14U                                                                                                  /* [113] ComConf_ComSignal_OTA3RSLT */
    ,(BswU2)14U                                                                                                  /* [114] ComConf_ComSignal_OTADRSLT */
    ,(BswU2)14U                                                                                                  /* [115] ComConf_ComSignal_SRVC_STT */
    ,(BswU2)14U                                                                                                  /* [116] ComConf_ComSignal_OTA3CNCL */
    ,(BswU2)14U                                                                                                  /* [117] ComConf_ComSignal_OTADCNCL */
    ,(BswU2)14U                                                                                                  /* [118] ComConf_ComSignal_CUR_DRV */
    ,(BswU2)14U                                                                                                  /* [119] ComConf_ComSignal_SRVC_PC */
    ,(BswU2)14U                                                                                                  /* [120] ComConf_ComSignal_SRVC_VC */
    ,(BswU2)14U                                                                                                  /* [121] ComConf_ComSignal_SRVC_AC */
    ,(BswU2)14U                                                                                                  /* [122] ComConf_ComSignal_OTAPPCTL */
    ,(BswU2)14U                                                                                                  /* [123] ComConf_ComSignal_CW_MD_SW */
    ,(BswU2)14U                                                                                                  /* [124] ComConf_ComSignal_VNHLDRQ */
    ,(BswU2)14U                                                                                                  /* [125] ComConf_ComSignal_TRNCASW */
    ,(BswU2)14U                                                                                                  /* [126] ComConf_ComSignal_TRNSD */
    ,(BswU2)14U                                                                                                  /* [127] ComConf_ComSignal_TRNFBPD */
    ,(BswU2)14U                                                                                                  /* [128] ComConf_ComSignal_RDG_ACT */
    ,(BswU2)14U                                                                                                  /* [129] ComConf_ComSignal_OTACDRLT */
    ,(BswU2)14U                                                                                                  /* [130] ComConf_ComSignal_OTACHGEX */
    ,(BswU2)14U                                                                                                  /* [131] ComConf_ComSignal_OTAACTTP */
    ,(BswU2)14U                                                                                                  /* [132] ComConf_ComSignal_OTAACTPH */
    ,(BswU2)14U                                                                                                  /* [133] ComConf_ComSignal_OTASWACT */
    ,(BswU2)14U                                                                                                  /* [134] ComConf_ComSignal_OTASTAT */
    ,(BswU2)15U                                                                                                  /* [135] ComConf_ComSignal_BIB_G */
    ,(BswU2)15U                                                                                                  /* [136] ComConf_ComSignal_VCELMAXG */
    ,(BswU2)15U                                                                                                  /* [137] ComConf_ComSignal_VCELMING */
    ,(BswU2)15U                                                                                                  /* [138] ComConf_ComSignal_RAHRMAXG */
    ,(BswU2)15U                                                                                                  /* [139] ComConf_ComSignal_RAHRMING */
    ,(BswU2)15U                                                                                                  /* [140] ComConf_ComSignal_TC_G */
    ,(BswU2)15U                                                                                                  /* [141] ComConf_ComSignal_TBMAX_G */
    ,(BswU2)15U                                                                                                  /* [142] ComConf_ComSignal_TBMIN_G */
    ,(BswU2)16U                                                                                                  /* [143] ComConf_ComSignal_D_MINFAD */
    ,(BswU2)16U                                                                                                  /* [144] ComConf_ComSignal_D_MINFO1 */
    ,(BswU2)16U                                                                                                  /* [145] ComConf_ComSignal_D_MINFO2 */
    ,(BswU2)16U                                                                                                  /* [146] ComConf_ComSignal_D_MINFO3 */
    ,(BswU2)17U                                                                                                  /* [147] ComConf_ComSignal_BTWO */
    ,(BswU2)18U                                                                                                  /* [148] ComConf_ComSignal_BITGB1 */
    ,(BswU2)18U                                                                                                  /* [149] ComConf_ComSignal_BITGB2 */
    ,(BswU2)18U                                                                                                  /* [150] ComConf_ComSignal_BITGB3 */
    ,(BswU2)18U                                                                                                  /* [151] ComConf_ComSignal_BITGB4 */
    ,(BswU2)18U                                                                                                  /* [152] ComConf_ComSignal_STKNUM */
    ,(BswU2)18U                                                                                                  /* [153] ComConf_ComSignal_BITGB5 */
    ,(BswU2)18U                                                                                                  /* [154] ComConf_ComSignal_VCELNUM */
    ,(BswU2)18U                                                                                                  /* [155] ComConf_ComSignal_INFGB1 */
    ,(BswU2)18U                                                                                                  /* [156] ComConf_ComSignal_TMINNUM */
    ,(BswU2)18U                                                                                                  /* [157] ComConf_ComSignal_INFGB2 */
    ,(BswU2)18U                                                                                                  /* [158] ComConf_ComSignal_TMAXNUM */
    ,(BswU2)18U                                                                                                  /* [159] ComConf_ComSignal_VBTINF */
    ,(BswU2)18U                                                                                                  /* [160] ComConf_ComSignal_SOCINF */
    ,(BswU2)18U                                                                                                  /* [161] ComConf_ComSignal_IBTINF */
    ,(BswU2)18U                                                                                                  /* [162] ComConf_ComSignal_TBTINF */
    ,(BswU2)18U                                                                                                  /* [163] ComConf_ComSignal_STPSOC */
    ,(BswU2)18U                                                                                                  /* [164] ComConf_ComSignal_STPVB */
    ,(BswU2)18U                                                                                                  /* [165] ComConf_ComSignal_STPCELV */
    ,(BswU2)18U                                                                                                  /* [166] ComConf_ComSignal_STPTMP */
    ,(BswU2)18U                                                                                                  /* [167] ComConf_ComSignal_DATAGB2 */
    ,(BswU2)18U                                                                                                  /* [168] ComConf_ComSignal_DATAGB3 */
    ,(BswU2)19U                                                                                                  /* [169] ComConf_ComSignal_ID63B16 */
    ,(BswU2)19U                                                                                                  /* [170] ComConf_ComSignal_IF63B16 */
    ,(BswU2)19U                                                                                                  /* [171] ComConf_ComSignal_TRIP_CNT */
    ,(BswU2)19U                                                                                                  /* [172] ComConf_ComSignal_TIME_CNT */
    ,(BswU2)20U                                                                                                  /* [173] ComConf_ComSignal_IL_FDOME */
    ,(BswU2)20U                                                                                                  /* [174] ComConf_ComSignal_IL_LOUNG */
    ,(BswU2)20U                                                                                                  /* [175] ComConf_ComSignal_IL_OSSTP */
    ,(BswU2)20U                                                                                                  /* [176] ComConf_ComSignal_AMB_COP */
    ,(BswU2)20U                                                                                                  /* [177] ComConf_ComSignal_SUPRQ */
    ,(BswU2)21U                                                                                                  /* [178] ComConf_ComSignal_AXIB */
    ,(BswU2)21U                                                                                                  /* [179] ComConf_ComSignal_AXVB */
    ,(BswU2)21U                                                                                                  /* [180] ComConf_ComSignal_AXTB */
    ,(BswU2)21U                                                                                                  /* [181] ComConf_ComSignal_AXSOC */
    ,(BswU2)22U                                                                                                  /* [182] ComConf_ComSignal_E_CRC1E3 */
    ,(BswU2)22U                                                                                                  /* [183] ComConf_ComSignal_E_CNT1E3 */
    ,(BswU2)22U                                                                                                  /* [184] ComConf_ComSignal_VPSINFO7 */
    ,(BswU2)22U                                                                                                  /* [185] ComConf_ComSignal_VPSINFO6 */
    ,(BswU2)22U                                                                                                  /* [186] ComConf_ComSignal_VPSINFO5 */
    ,(BswU2)22U                                                                                                  /* [187] ComConf_ComSignal_VPSINFO4 */
    ,(BswU2)22U                                                                                                  /* [188] ComConf_ComSignal_VPSINFO3 */
    ,(BswU2)22U                                                                                                  /* [189] ComConf_ComSignal_VPSINFO2 */
    ,(BswU2)22U                                                                                                  /* [190] ComConf_ComSignal_VPSINFO1 */
    ,(BswU2)22U                                                                                                  /* [191] ComConf_ComSignal_VPSINFOS */
    ,(BswU2)22U                                                                                                  /* [192] ComConf_ComSignal_VPSCNG */
    ,(BswU2)22U                                                                                                  /* [193] ComConf_ComSignal_VPSISOTA */
    ,(BswU2)22U                                                                                                  /* [194] ComConf_ComSignal_APOFRQ */
    ,(BswU2)22U                                                                                                  /* [195] ComConf_ComSignal_FV1E3_D */
    ,(BswU2)22U                                                                                                  /* [196] ComConf_ComSignal_KZK1E3_D */
    ,(BswU2)23U                                                                                                  /* [197] ComConf_ComSignal_E_CRC150 */
    ,(BswU2)23U                                                                                                  /* [198] ComConf_ComSignal_E_CNT150 */
    ,(BswU2)23U                                                                                                  /* [199] ComConf_ComSignal_PWRERRST */
    ,(BswU2)23U                                                                                                  /* [200] ComConf_ComSignal_CRLYOF */
    ,(BswU2)23U                                                                                                  /* [201] ComConf_ComSignal_LRQ_ELRS */
    ,(BswU2)23U                                                                                                  /* [202] ComConf_ComSignal_LRQ_ARSS */
    ,(BswU2)23U                                                                                                  /* [203] ComConf_ComSignal_LRQ_RFRS */
    ,(BswU2)23U                                                                                                  /* [204] ComConf_ComSignal_LRQ_RILM */
    ,(BswU2)23U                                                                                                  /* [205] ComConf_ComSignal_LRQ_WLCH */
    ,(BswU2)23U                                                                                                  /* [206] ComConf_ComSignal_LRQ_RDFG */
    ,(BswU2)23U                                                                                                  /* [207] ComConf_ComSignal_LRQ_EHW */
    ,(BswU2)23U                                                                                                  /* [208] ComConf_ComSignal_LRQ_RDH */
    ,(BswU2)23U                                                                                                  /* [209] ComConf_ComSignal_LRQ_FRSH */
    ,(BswU2)23U                                                                                                  /* [210] ComConf_ComSignal_LRQ_RRSH */
    ,(BswU2)23U                                                                                                  /* [211] ComConf_ComSignal_LRQ_FRG */
    ,(BswU2)23U                                                                                                  /* [212] ComConf_ComSignal_LRQ_NNE */
    ,(BswU2)23U                                                                                                  /* [213] ComConf_ComSignal_LRQ_WDIC */
    ,(BswU2)23U                                                                                                  /* [214] ComConf_ComSignal_LRQ_MRH */
    ,(BswU2)23U                                                                                                  /* [215] ComConf_ComSignal_LRQ_STRH */
    ,(BswU2)23U                                                                                                  /* [216] ComConf_ComSignal_LRQ_DMG */
    ,(BswU2)23U                                                                                                  /* [217] ComConf_ComSignal_LRQ_IRP */
    ,(BswU2)23U                                                                                                  /* [218] ComConf_ComSignal_LRQ_FACB */
    ,(BswU2)23U                                                                                                  /* [219] ComConf_ComSignal_LRQ_RACB */
    ,(BswU2)23U                                                                                                  /* [220] ComConf_ComSignal_LRQ_SPL */
    ,(BswU2)23U                                                                                                  /* [221] ComConf_ComSignal_LRQ_ELF */
    ,(BswU2)23U                                                                                                  /* [222] ComConf_ComSignal_LRQ_ACC1 */
    ,(BswU2)23U                                                                                                  /* [223] ComConf_ComSignal_LRQ_USB */
    ,(BswU2)23U                                                                                                  /* [224] ComConf_ComSignal_LRQ_USB2 */
    ,(BswU2)23U                                                                                                  /* [225] ComConf_ComSignal_LRQ_ACC2 */
    ,(BswU2)23U                                                                                                  /* [226] ComConf_ComSignal_LRQ_TOW */
    ,(BswU2)23U                                                                                                  /* [227] ComConf_ComSignal_LRQOHP */
    ,(BswU2)23U                                                                                                  /* [228] ComConf_ComSignal_LRQ_SHAC */
    ,(BswU2)23U                                                                                                  /* [229] ComConf_ComSignal_LRQ_SAMP */
    ,(BswU2)23U                                                                                                  /* [230] ComConf_ComSignal_LRQELL */
    ,(BswU2)23U                                                                                                  /* [231] ComConf_ComSignal_FV150_D */
    ,(BswU2)23U                                                                                                  /* [232] ComConf_ComSignal_KZK150_D */
    ,(BswU2)24U                                                                                                  /* [233] ComConf_ComSignal_E_CRC1E4 */
    ,(BswU2)24U                                                                                                  /* [234] ComConf_ComSignal_E_CNT1E4 */
    ,(BswU2)24U                                                                                                  /* [235] ComConf_ComSignal_VPSINF7S */
    ,(BswU2)24U                                                                                                  /* [236] ComConf_ComSignal_VPSINF6S */
    ,(BswU2)24U                                                                                                  /* [237] ComConf_ComSignal_VPSINF5S */
    ,(BswU2)24U                                                                                                  /* [238] ComConf_ComSignal_VPSINF4S */
    ,(BswU2)24U                                                                                                  /* [239] ComConf_ComSignal_VPSINF3S */
    ,(BswU2)24U                                                                                                  /* [240] ComConf_ComSignal_VPSINF2S */
    ,(BswU2)24U                                                                                                  /* [241] ComConf_ComSignal_VPSINF1S */
    ,(BswU2)24U                                                                                                  /* [242] ComConf_ComSignal_VPSINFSS */
    ,(BswU2)24U                                                                                                  /* [243] ComConf_ComSignal_VPSOTAS */
    ,(BswU2)24U                                                                                                  /* [244] ComConf_ComSignal_APOFRQS */
    ,(BswU2)24U                                                                                                  /* [245] ComConf_ComSignal_FV1E4_D */
    ,(BswU2)24U                                                                                                  /* [246] ComConf_ComSignal_KZK1E4_D */
    ,(BswU2)25U                                                                                                  /* [247] ComConf_ComSignal_ST1 */
    ,(BswU2)25U                                                                                                  /* [248] ComConf_ComSignal_ST1PER */
    ,(BswU2)25U                                                                                                  /* [249] ComConf_ComSignal_ST2 */
    ,(BswU2)25U                                                                                                  /* [250] ComConf_ComSignal_ST2PER */
    ,(BswU2)25U                                                                                                  /* [251] ComConf_ComSignal_ST3 */
    ,(BswU2)25U                                                                                                  /* [252] ComConf_ComSignal_ST3PER */
    ,(BswU2)25U                                                                                                  /* [253] ComConf_ComSignal_ST4 */
    ,(BswU2)25U                                                                                                  /* [254] ComConf_ComSignal_ST4PER */
    ,(BswU2)25U                                                                                                  /* [255] ComConf_ComSignal_ST5 */
    ,(BswU2)25U                                                                                                  /* [256] ComConf_ComSignal_ST5PER */
    ,(BswU2)25U                                                                                                  /* [257] ComConf_ComSignal_ST6 */
    ,(BswU2)25U                                                                                                  /* [258] ComConf_ComSignal_ST6PER */
    ,(BswU2)25U                                                                                                  /* [259] ComConf_ComSignal_ST7 */
    ,(BswU2)25U                                                                                                  /* [260] ComConf_ComSignal_ST7PER */
    ,(BswU2)25U                                                                                                  /* [261] ComConf_ComSignal_ST8 */
    ,(BswU2)25U                                                                                                  /* [262] ComConf_ComSignal_ST8PER */
    ,(BswU2)25U                                                                                                  /* [263] ComConf_ComSignal_ST9 */
    ,(BswU2)25U                                                                                                  /* [264] ComConf_ComSignal_ST9PER */
    ,(BswU2)25U                                                                                                  /* [265] ComConf_ComSignal_ST10 */
    ,(BswU2)25U                                                                                                  /* [266] ComConf_ComSignal_ST10PER */
    ,(BswU2)25U                                                                                                  /* [267] ComConf_ComSignal_ST11 */
    ,(BswU2)25U                                                                                                  /* [268] ComConf_ComSignal_ST11PER */
    ,(BswU2)25U                                                                                                  /* [269] ComConf_ComSignal_ST12 */
    ,(BswU2)25U                                                                                                  /* [270] ComConf_ComSignal_ST12PER */
    ,(BswU2)25U                                                                                                  /* [271] ComConf_ComSignal_ST13 */
    ,(BswU2)25U                                                                                                  /* [272] ComConf_ComSignal_ST13PER */
    ,(BswU2)25U                                                                                                  /* [273] ComConf_ComSignal_ST14 */
    ,(BswU2)25U                                                                                                  /* [274] ComConf_ComSignal_ST14PER */
    ,(BswU2)25U                                                                                                  /* [275] ComConf_ComSignal_ST15 */
    ,(BswU2)25U                                                                                                  /* [276] ComConf_ComSignal_ST15PER */
    ,(BswU2)25U                                                                                                  /* [277] ComConf_ComSignal_ST16 */
    ,(BswU2)25U                                                                                                  /* [278] ComConf_ComSignal_ST16PER */
    ,(BswU2)25U                                                                                                  /* [279] ComConf_ComSignal_ST17 */
    ,(BswU2)25U                                                                                                  /* [280] ComConf_ComSignal_ST17PER */
    ,(BswU2)25U                                                                                                  /* [281] ComConf_ComSignal_ST18 */
    ,(BswU2)25U                                                                                                  /* [282] ComConf_ComSignal_ST18PER */
    ,(BswU2)25U                                                                                                  /* [283] ComConf_ComSignal_MSONS */
    ,(BswU2)26U                                                                                                  /* [284] ComConf_ComSignal_UMIIFS5 */
    ,(BswU2)26U                                                                                                  /* [285] ComConf_ComSignal_UMIREQS5 */
    ,(BswU2)26U                                                                                                  /* [286] ComConf_ComSignal_UMIRSVS5 */
    ,(BswU2)26U                                                                                                  /* [287] ComConf_ComSignal_UMIDATS5 */
    ,(BswU2)27U                                                                                                  /* [288] ComConf_ComSignal_UMIIFS6 */
    ,(BswU2)27U                                                                                                  /* [289] ComConf_ComSignal_UMIREQS6 */
    ,(BswU2)27U                                                                                                  /* [290] ComConf_ComSignal_UMIRSVS6 */
    ,(BswU2)27U                                                                                                  /* [291] ComConf_ComSignal_UMIDATS6 */
    ,(BswU2)28U                                                                                                  /* [292] ComConf_ComSignal_UMIIFS7 */
    ,(BswU2)28U                                                                                                  /* [293] ComConf_ComSignal_UMIREQS7 */
    ,(BswU2)28U                                                                                                  /* [294] ComConf_ComSignal_UMIRSVS7 */
    ,(BswU2)28U                                                                                                  /* [295] ComConf_ComSignal_UMIDATS7 */
    ,(BswU2)29U                                                                                                  /* [296] ComConf_ComSignal_UMIIFS8 */
    ,(BswU2)29U                                                                                                  /* [297] ComConf_ComSignal_UMIREQS8 */
    ,(BswU2)29U                                                                                                  /* [298] ComConf_ComSignal_UMIRSVS8 */
    ,(BswU2)29U                                                                                                  /* [299] ComConf_ComSignal_UMIDATS8 */
    ,(BswU2)30U                                                                                                  /* [300] ComConf_ComSignal_UMIIFS9 */
    ,(BswU2)30U                                                                                                  /* [301] ComConf_ComSignal_UMIREQS9 */
    ,(BswU2)30U                                                                                                  /* [302] ComConf_ComSignal_UMIRSVS9 */
    ,(BswU2)30U                                                                                                  /* [303] ComConf_ComSignal_UMIDATS9 */
    ,(BswU2)31U                                                                                                  /* [304] ComConf_ComSignal_UMIIFS10 */
    ,(BswU2)31U                                                                                                  /* [305] ComConf_ComSignal_UMIRQS10 */
    ,(BswU2)31U                                                                                                  /* [306] ComConf_ComSignal_UMIRVS10 */
    ,(BswU2)31U                                                                                                  /* [307] ComConf_ComSignal_UMIDTS10 */
    ,(BswU2)32U                                                                                                  /* [308] ComConf_ComSignal_UMIIFS11 */
    ,(BswU2)32U                                                                                                  /* [309] ComConf_ComSignal_UMIRQS11 */
    ,(BswU2)32U                                                                                                  /* [310] ComConf_ComSignal_UMIRVS11 */
    ,(BswU2)32U                                                                                                  /* [311] ComConf_ComSignal_UMIDTS11 */
    ,(BswU2)33U                                                                                                  /* [312] ComConf_ComSignal_UMIIFS12 */
    ,(BswU2)33U                                                                                                  /* [313] ComConf_ComSignal_UMIRQS12 */
    ,(BswU2)33U                                                                                                  /* [314] ComConf_ComSignal_UMIRVS12 */
    ,(BswU2)33U                                                                                                  /* [315] ComConf_ComSignal_UMIDTS12 */
    ,(BswU2)34U                                                                                                  /* [316] ComConf_ComSignal_UMIIFS13 */
    ,(BswU2)34U                                                                                                  /* [317] ComConf_ComSignal_UMIRQS13 */
    ,(BswU2)34U                                                                                                  /* [318] ComConf_ComSignal_UMIRVS13 */
    ,(BswU2)34U                                                                                                  /* [319] ComConf_ComSignal_UMIDTS13 */
    ,(BswU2)35U                                                                                                  /* [320] ComConf_ComSignal_UMIIFS14 */
    ,(BswU2)35U                                                                                                  /* [321] ComConf_ComSignal_UMIRQS14 */
    ,(BswU2)35U                                                                                                  /* [322] ComConf_ComSignal_UMIRVS14 */
    ,(BswU2)35U                                                                                                  /* [323] ComConf_ComSignal_UMIDTS14 */
    ,(BswU2)36U                                                                                                  /* [324] ComConf_ComSignal_UMIIFS15 */
    ,(BswU2)36U                                                                                                  /* [325] ComConf_ComSignal_UMIRQS15 */
    ,(BswU2)36U                                                                                                  /* [326] ComConf_ComSignal_UMIRVS15 */
    ,(BswU2)36U                                                                                                  /* [327] ComConf_ComSignal_UMIDTS15 */
    ,(BswU2)37U                                                                                                  /* [328] ComConf_ComSignal_UMIIFS16 */
    ,(BswU2)37U                                                                                                  /* [329] ComConf_ComSignal_UMIRQS16 */
    ,(BswU2)37U                                                                                                  /* [330] ComConf_ComSignal_UMIRVS16 */
    ,(BswU2)37U                                                                                                  /* [331] ComConf_ComSignal_UMIDTS16 */
    ,(BswU2)38U                                                                                                  /* [332] ComConf_ComSignal_ACPRE_AD */
    ,(BswU2)38U                                                                                                  /* [333] ComConf_ComSignal_EXPMIP */
    ,(BswU2)38U                                                                                                  /* [334] ComConf_ComSignal_AMR */
    ,(BswU2)38U                                                                                                  /* [335] ComConf_ComSignal_MIP */
    ,(BswU2)38U                                                                                                  /* [336] ComConf_ComSignal_AIT */
    ,(BswU2)38U                                                                                                  /* [337] ComConf_ComSignal_FV37B_D */
    ,(BswU2)38U                                                                                                  /* [338] ComConf_ComSignal_KZK37B_D */
    ,(BswU2)39U                                                                                                  /* [339] ComConf_ComSignal_HVH_ATPW */
    ,(BswU2)39U                                                                                                  /* [340] ComConf_ComSignal_HVH_CLOT */
    ,(BswU2)40U                                                                                                  /* [341] ComConf_ComSignal_COMPRP_A */
    ,(BswU2)40U                                                                                                  /* [342] ComConf_ComSignal_ACMODE_P */
    ,(BswU2)41U                                                                                                  /* [343] ComConf_ComSignal_ETHWU_21 */
    ,(BswU2)41U                                                                                                  /* [344] ComConf_ComSignal_ETHWU_23 */
    ,(BswU2)42U                                                                                                  /* [345] ComConf_ComSignal_HED_S */
    ,(BswU2)42U                                                                                                  /* [346] ComConf_ComSignal_TAL_S */
    ,(BswU2)42U                                                                                                  /* [347] ComConf_ComSignal_DRL_S */
    ,(BswU2)42U                                                                                                  /* [348] ComConf_ComSignal_AUT_S */
    ,(BswU2)42U                                                                                                  /* [349] ComConf_ComSignal_OFF_S */
    ,(BswU2)42U                                                                                                  /* [350] ComConf_ComSignal_AHB_S */
    ,(BswU2)42U                                                                                                  /* [351] ComConf_ComSignal_PAS_S */
    ,(BswU2)42U                                                                                                  /* [352] ComConf_ComSignal_HIB_S */
    ,(BswU2)42U                                                                                                  /* [353] ComConf_ComSignal_BW_S */
    ,(BswU2)42U                                                                                                  /* [354] ComConf_ComSignal_RFG_S */
    ,(BswU2)42U                                                                                                  /* [355] ComConf_ComSignal_FOG_S */
    ,(BswU2)42U                                                                                                  /* [356] ComConf_ComSignal_CRGL_S */
    ,(BswU2)42U                                                                                                  /* [357] ComConf_ComSignal_CRGR_S */
    ,(BswU2)42U                                                                                                  /* [358] ComConf_ComSignal_TRNL_S */
    ,(BswU2)42U                                                                                                  /* [359] ComConf_ComSignal_TRNR_S */
    ,(BswU2)42U                                                                                                  /* [360] ComConf_ComSignal_CXP_JDGT */
    ,(BswU2)43U                                                                                                  /* [361] ComConf_ComSignal_WVR_S */
    ,(BswU2)43U                                                                                                  /* [362] ComConf_ComSignal_WSW_S */
    ,(BswU2)43U                                                                                                  /* [363] ComConf_ComSignal_WRSW_S */
    ,(BswU2)43U                                                                                                  /* [364] ComConf_ComSignal_WRON_S */
    ,(BswU2)43U                                                                                                  /* [365] ComConf_ComSignal_WRIN_S */
    ,(BswU2)43U                                                                                                  /* [366] ComConf_ComSignal_WINT_S */
    ,(BswU2)43U                                                                                                  /* [367] ComConf_ComSignal_WMST_S */
    ,(BswU2)43U                                                                                                  /* [368] ComConf_ComSignal_WA_S */
    ,(BswU2)43U                                                                                                  /* [369] ComConf_ComSignal_WHI_S */
    ,(BswU2)43U                                                                                                  /* [370] ComConf_ComSignal_WLO_S */
    ,(BswU2)43U                                                                                                  /* [371] ComConf_ComSignal_WOFF_S */
    ,(BswU2)43U                                                                                                  /* [372] ComConf_ComSignal_WAI_S */
    ,(BswU2)43U                                                                                                  /* [373] ComConf_ComSignal_CXP_JDGW */
    ,(BswU2)44U                                                                                                  /* [374] ComConf_ComSignal_ETHWU_32 */
    ,(BswU2)45U                                                                                                  /* [375] ComConf_ComSignal_THR_GLOB */
    ,(BswU2)45U                                                                                                  /* [376] ComConf_ComSignal_TMO_GLOB */
    ,(BswU2)45U                                                                                                  /* [377] ComConf_ComSignal_TTA_GLOB */
    ,(BswU2)45U                                                                                                  /* [378] ComConf_ComSignal_RTA_GLOB */
    ,(BswU2)46U                                                                                                  /* [379] ComConf_ComSignal_TR_GLOB */
    ,(BswU2)46U                                                                                                  /* [380] ComConf_ComSignal_TM_GLOB */
    ,(BswU2)46U                                                                                                  /* [381] ComConf_ComSignal_NR_GLOB */
    ,(BswU2)46U                                                                                                  /* [382] ComConf_ComSignal_NM_GLOB */
    ,(BswU2)47U                                                                                                  /* [383] ComConf_ComSignal_NMRBR_MD */
    ,(BswU2)47U                                                                                                  /* [384] ComConf_ComSignal_BHSWEXT */
    ,(BswU2)47U                                                                                                  /* [385] ComConf_ComSignal_NMRBSWEX */
    ,(BswU2)48U                                                                                                  /* [386] ComConf_ComSignal_GRLGDBCR */
    ,(BswU2)48U                                                                                                  /* [387] ComConf_ComSignal_BSTCNTRE */
    ,(BswU2)48U                                                                                                  /* [388] ComConf_ComSignal_BSTCNT */
    ,(BswU2)48U                                                                                                  /* [389] ComConf_ComSignal_CPMTSWEX */
    ,(BswU2)48U                                                                                                  /* [390] ComConf_ComSignal_CPCMTVL */
    ,(BswU2)48U                                                                                                  /* [391] ComConf_ComSignal_CPSMPIN5 */
    ,(BswU2)48U                                                                                                  /* [392] ComConf_ComSignal_BSTSTAT */
    ,(BswU2)48U                                                                                                  /* [393] ComConf_ComSignal_CPSMPIN4 */
    ,(BswU2)48U                                                                                                  /* [394] ComConf_ComSignal_CPSMPIN3 */
    ,(BswU2)48U                                                                                                  /* [395] ComConf_ComSignal_BSTSWBB */
    ,(BswU2)48U                                                                                                  /* [396] ComConf_ComSignal_CPSMPEX */
    ,(BswU2)48U                                                                                                  /* [397] ComConf_ComSignal_CPSMPIN2 */
    ,(BswU2)48U                                                                                                  /* [398] ComConf_ComSignal_CPSMPIN1 */
    ,(BswU2)48U                                                                                                  /* [399] ComConf_ComSignal_CPDRSWEX */
    ,(BswU2)48U                                                                                                  /* [400] ComConf_ComSignal_CPCDRVL */
    ,(BswU2)48U                                                                                                  /* [401] ComConf_ComSignal_CP2DMC2 */
    ,(BswU2)48U                                                                                                  /* [402] ComConf_ComSignal_BSTREJ */
    ,(BswU2)48U                                                                                                  /* [403] ComConf_ComSignal_CP2DMC1 */
    ,(BswU2)48U                                                                                                  /* [404] ComConf_ComSignal_CP2DMER */
    ,(BswU2)48U                                                                                                  /* [405] ComConf_ComSignal_CP2DMEX */
    ,(BswU2)48U                                                                                                  /* [406] ComConf_ComSignal_BSTCODE */
    ,(BswU2)48U                                                                                                  /* [407] ComConf_ComSignal_CPCTFRCV */
    ,(BswU2)48U                                                                                                  /* [408] ComConf_ComSignal_BSTMET */
    ,(BswU2)48U                                                                                                  /* [409] ComConf_ComSignal_CPCTFRMV */
    ,(BswU2)48U                                                                                                  /* [410] ComConf_ComSignal_CPCTFRER */
    ,(BswU2)48U                                                                                                  /* [411] ComConf_ComSignal_B_CPMODE */
    ,(BswU2)48U                                                                                                  /* [412] ComConf_ComSignal_CPSSWEX */
    ,(BswU2)48U                                                                                                  /* [413] ComConf_ComSignal_DMCNVINF */
    ,(BswU2)48U                                                                                                  /* [414] ComConf_ComSignal_CPCTFREX */
    ,(BswU2)48U                                                                                                  /* [415] ComConf_ComSignal_CNV_MODE */
    ,(BswU2)48U                                                                                                  /* [416] ComConf_ComSignal_DMCNVVLD */
    ,(BswU2)48U                                                                                                  /* [417] ComConf_ComSignal_DMCNMDVL */
    ,(BswU2)49U                                                                                                  /* [418] ComConf_ComSignal_XCDRST2 */
    ,(BswU2)49U                                                                                                  /* [419] ComConf_ComSignal_XCDRST1 */
    ,(BswU2)49U                                                                                                  /* [420] ComConf_ComSignal_CUMTEC1 */
    ,(BswU2)49U                                                                                                  /* [421] ComConf_ComSignal_CUMTEC2 */
    ,(BswU2)49U                                                                                                  /* [422] ComConf_ComSignal_CRDRVEC1 */
    ,(BswU2)49U                                                                                                  /* [423] ComConf_ComSignal_CRDRVEC2 */
    ,(BswU2)49U                                                                                                  /* [424] ComConf_ComSignal_CRALTEC1 */
    ,(BswU2)49U                                                                                                  /* [425] ComConf_ComSignal_CRALTEC2 */
    ,(BswU2)49U                                                                                                  /* [426] ComConf_ComSignal_CRACEC1 */
    ,(BswU2)49U                                                                                                  /* [427] ComConf_ComSignal_CRACEC2 */
    ,(BswU2)49U                                                                                                  /* [428] ComConf_ComSignal_CRPACEC1 */
    ,(BswU2)49U                                                                                                  /* [429] ComConf_ComSignal_CRPACEC2 */
    ,(BswU2)49U                                                                                                  /* [430] ComConf_ComSignal_CRBPEC1 */
    ,(BswU2)49U                                                                                                  /* [431] ComConf_ComSignal_CRBPEC2 */
    ,(BswU2)49U                                                                                                  /* [432] ComConf_ComSignal_CRPBPEC1 */
    ,(BswU2)49U                                                                                                  /* [433] ComConf_ComSignal_CRPBPEC2 */
    ,(BswU2)49U                                                                                                  /* [434] ComConf_ComSignal_CRDAEC1 */
    ,(BswU2)49U                                                                                                  /* [435] ComConf_ComSignal_CRDAEC2 */
    ,(BswU2)49U                                                                                                  /* [436] ComConf_ComSignal_CRPAEC1 */
    ,(BswU2)49U                                                                                                  /* [437] ComConf_ComSignal_CRPAEC2 */
    ,(BswU2)50U                                                                                                  /* [438] ComConf_ComSignal_RSISDKME */
    ,(BswU2)50U                                                                                                  /* [439] ComConf_ComSignal_RSISIDDK */
    ,(BswU2)51U                                                                                                  /* [440] ComConf_ComSignal_DESMUTE */
    ,(BswU2)52U                                                                                                  /* [441] ComConf_ComSignal_DREBUID */
    ,(BswU2)52U                                                                                                  /* [442] ComConf_ComSignal_DREBU02 */
    ,(BswU2)52U                                                                                                  /* [443] ComConf_ComSignal_DREBU03 */
    ,(BswU2)52U                                                                                                  /* [444] ComConf_ComSignal_DREBU04 */
    ,(BswU2)52U                                                                                                  /* [445] ComConf_ComSignal_DREBU05 */
    ,(BswU2)52U                                                                                                  /* [446] ComConf_ComSignal_DREBU06 */
    ,(BswU2)52U                                                                                                  /* [447] ComConf_ComSignal_DREBU07 */
    ,(BswU2)52U                                                                                                  /* [448] ComConf_ComSignal_DREBU08 */
    ,(BswU2)52U                                                                                                  /* [449] ComConf_ComSignal_DREBU11 */
    ,(BswU2)52U                                                                                                  /* [450] ComConf_ComSignal_DREBU12 */
    ,(BswU2)52U                                                                                                  /* [451] ComConf_ComSignal_DREBU13 */
    ,(BswU2)52U                                                                                                  /* [452] ComConf_ComSignal_DREBU14 */
    ,(BswU2)52U                                                                                                  /* [453] ComConf_ComSignal_DREBU15 */
    ,(BswU2)52U                                                                                                  /* [454] ComConf_ComSignal_DREBU16 */
    ,(BswU2)52U                                                                                                  /* [455] ComConf_ComSignal_DREBU17 */
    ,(BswU2)52U                                                                                                  /* [456] ComConf_ComSignal_DREBU18 */
    ,(BswU2)52U                                                                                                  /* [457] ComConf_ComSignal_DREBU21 */
    ,(BswU2)52U                                                                                                  /* [458] ComConf_ComSignal_DREBU22 */
    ,(BswU2)52U                                                                                                  /* [459] ComConf_ComSignal_DREBU23 */
    ,(BswU2)52U                                                                                                  /* [460] ComConf_ComSignal_DREBU24 */
    ,(BswU2)52U                                                                                                  /* [461] ComConf_ComSignal_DREBU25 */
    ,(BswU2)52U                                                                                                  /* [462] ComConf_ComSignal_DREBU26 */
    ,(BswU2)52U                                                                                                  /* [463] ComConf_ComSignal_DREBU27 */
    ,(BswU2)52U                                                                                                  /* [464] ComConf_ComSignal_DREBU28 */
    ,(BswU2)52U                                                                                                  /* [465] ComConf_ComSignal_DREBU31 */
    ,(BswU2)52U                                                                                                  /* [466] ComConf_ComSignal_DREBU32 */
    ,(BswU2)52U                                                                                                  /* [467] ComConf_ComSignal_DREBU33 */
    ,(BswU2)52U                                                                                                  /* [468] ComConf_ComSignal_DREBU34 */
    ,(BswU2)52U                                                                                                  /* [469] ComConf_ComSignal_DREBU35 */
    ,(BswU2)52U                                                                                                  /* [470] ComConf_ComSignal_DREBU36 */
    ,(BswU2)52U                                                                                                  /* [471] ComConf_ComSignal_DREBU37 */
    ,(BswU2)52U                                                                                                  /* [472] ComConf_ComSignal_DREBU38 */
    ,(BswU2)53U                                                                                                  /* [473] ComConf_ComSignal_DRDYSTS */
    ,(BswU2)53U                                                                                                  /* [474] ComConf_ComSignal_DRDYB */
    ,(BswU2)54U                                                                                                  /* [475] ComConf_ComSignal_STRGCM */
    ,(BswU2)55U                                                                                                  /* [476] ComConf_ComSignal_HV_SRGMD */
    ,(BswU2)55U                                                                                                  /* [477] ComConf_ComSignal_TQRR */
    ,(BswU2)55U                                                                                                  /* [478] ComConf_ComSignal_TQFR */
    ,(BswU2)56U                                                                                                  /* [479] ComConf_ComSignal_FCRF */
    ,(BswU2)56U                                                                                                  /* [480] ComConf_ComSignal_CLE_SOCF */
    ,(BswU2)57U                                                                                                  /* [481] ComConf_ComSignal_SDRVRR */
    ,(BswU2)57U                                                                                                  /* [482] ComConf_ComSignal_SDRVFR */
    ,(BswU2)58U                                                                                                  /* [483] ComConf_ComSignal_E_CRC0A1 */
    ,(BswU2)58U                                                                                                  /* [484] ComConf_ComSignal_E_CNT0A1 */
    ,(BswU2)58U                                                                                                  /* [485] ComConf_ComSignal_HVMRADRR */
    ,(BswU2)58U                                                                                                  /* [486] ComConf_ComSignal_HVMRADFR */
    ,(BswU2)58U                                                                                                  /* [487] ComConf_ComSignal_ETRQ_FS */
    ,(BswU2)58U                                                                                                  /* [488] ComConf_ComSignal_HVRADRRL */
    ,(BswU2)58U                                                                                                  /* [489] ComConf_ComSignal_HVRADRRR */
    ,(BswU2)58U                                                                                                  /* [490] ComConf_ComSignal_HVRADFRL */
    ,(BswU2)58U                                                                                                  /* [491] ComConf_ComSignal_HVRADFRR */
    ,(BswU2)59U                                                                                                  /* [492] ComConf_ComSignal_DREIMABN */
    ,(BswU2)60U                                                                                                  /* [493] ComConf_ComSignal_I_BAT_BD */
    ,(BswU2)60U                                                                                                  /* [494] ComConf_ComSignal_U_BAT_BD */
    ,(BswU2)60U                                                                                                  /* [495] ComConf_ComSignal_PWDTY_BD */
    ,(BswU2)60U                                                                                                  /* [496] ComConf_ComSignal_VLO_BD */
    ,(BswU2)60U                                                                                                  /* [497] ComConf_ComSignal_PWIF1_BD */
    ,(BswU2)61U                                                                                                  /* [498] ComConf_ComSignal_T_BAT_BD */
    ,(BswU2)61U                                                                                                  /* [499] ComConf_ComSignal_PWIF2_BD */
    ,(BswU2)61U                                                                                                  /* [500] ComConf_ComSignal_SOCS_BD */
    ,(BswU2)61U                                                                                                  /* [501] ComConf_ComSignal_SOC_BD */
    ,(BswU2)61U                                                                                                  /* [502] ComConf_ComSignal_PWIF3_BD */
    ,(BswU2)61U                                                                                                  /* [503] ComConf_ComSignal_PWIF4_BD */
    ,(BswU2)61U                                                                                                  /* [504] ComConf_ComSignal_PWIF5_BD */
    ,(BswU2)62U                                                                                                  /* [505] ComConf_ComSignal_DRENG11 */
    ,(BswU2)62U                                                                                                  /* [506] ComConf_ComSignal_DRENG12 */
    ,(BswU2)62U                                                                                                  /* [507] ComConf_ComSignal_DRENG13 */
    ,(BswU2)62U                                                                                                  /* [508] ComConf_ComSignal_DRENG14 */
    ,(BswU2)62U                                                                                                  /* [509] ComConf_ComSignal_DRENG15 */
    ,(BswU2)62U                                                                                                  /* [510] ComConf_ComSignal_DRENG16 */
    ,(BswU2)62U                                                                                                  /* [511] ComConf_ComSignal_DRENG17 */
    ,(BswU2)62U                                                                                                  /* [512] ComConf_ComSignal_DRENG18 */
    ,(BswU2)63U                                                                                                  /* [513] ComConf_ComSignal_DRENG21 */
    ,(BswU2)63U                                                                                                  /* [514] ComConf_ComSignal_DRENG22 */
    ,(BswU2)63U                                                                                                  /* [515] ComConf_ComSignal_DRENG23 */
    ,(BswU2)63U                                                                                                  /* [516] ComConf_ComSignal_DRENG24 */
    ,(BswU2)63U                                                                                                  /* [517] ComConf_ComSignal_DRENG25 */
    ,(BswU2)63U                                                                                                  /* [518] ComConf_ComSignal_DRENG26 */
    ,(BswU2)63U                                                                                                  /* [519] ComConf_ComSignal_DRENG27 */
    ,(BswU2)63U                                                                                                  /* [520] ComConf_ComSignal_DRENG28 */
    ,(BswU2)64U                                                                                                  /* [521] ComConf_ComSignal_DRENG31 */
    ,(BswU2)64U                                                                                                  /* [522] ComConf_ComSignal_DRENG32 */
    ,(BswU2)64U                                                                                                  /* [523] ComConf_ComSignal_DRENG33 */
    ,(BswU2)64U                                                                                                  /* [524] ComConf_ComSignal_DRENG34 */
    ,(BswU2)64U                                                                                                  /* [525] ComConf_ComSignal_DRENG35 */
    ,(BswU2)64U                                                                                                  /* [526] ComConf_ComSignal_DRENG36 */
    ,(BswU2)64U                                                                                                  /* [527] ComConf_ComSignal_DRENG37 */
    ,(BswU2)64U                                                                                                  /* [528] ComConf_ComSignal_DRENG38 */
    ,(BswU2)65U                                                                                                  /* [529] ComConf_ComSignal_DRENG51 */
    ,(BswU2)65U                                                                                                  /* [530] ComConf_ComSignal_DRENG52 */
    ,(BswU2)65U                                                                                                  /* [531] ComConf_ComSignal_DRENG53 */
    ,(BswU2)65U                                                                                                  /* [532] ComConf_ComSignal_DRENG54 */
    ,(BswU2)65U                                                                                                  /* [533] ComConf_ComSignal_DRENG55 */
    ,(BswU2)65U                                                                                                  /* [534] ComConf_ComSignal_DRENG56 */
    ,(BswU2)65U                                                                                                  /* [535] ComConf_ComSignal_DRENG57 */
    ,(BswU2)65U                                                                                                  /* [536] ComConf_ComSignal_DRENG58 */
    ,(BswU2)66U                                                                                                  /* [537] ComConf_ComSignal_DRENG61 */
    ,(BswU2)66U                                                                                                  /* [538] ComConf_ComSignal_DRENG62 */
    ,(BswU2)66U                                                                                                  /* [539] ComConf_ComSignal_DRENG63 */
    ,(BswU2)66U                                                                                                  /* [540] ComConf_ComSignal_DRENG64 */
    ,(BswU2)66U                                                                                                  /* [541] ComConf_ComSignal_DRENG65 */
    ,(BswU2)66U                                                                                                  /* [542] ComConf_ComSignal_DRENG66 */
    ,(BswU2)66U                                                                                                  /* [543] ComConf_ComSignal_DRENG67 */
    ,(BswU2)66U                                                                                                  /* [544] ComConf_ComSignal_DRENG68 */
    ,(BswU2)67U                                                                                                  /* [545] ComConf_ComSignal_DRENG91 */
    ,(BswU2)67U                                                                                                  /* [546] ComConf_ComSignal_DRENG92 */
    ,(BswU2)67U                                                                                                  /* [547] ComConf_ComSignal_DRENG93 */
    ,(BswU2)67U                                                                                                  /* [548] ComConf_ComSignal_DRENG94 */
    ,(BswU2)67U                                                                                                  /* [549] ComConf_ComSignal_DRENG95 */
    ,(BswU2)67U                                                                                                  /* [550] ComConf_ComSignal_DRENG96 */
    ,(BswU2)67U                                                                                                  /* [551] ComConf_ComSignal_DRENG97 */
    ,(BswU2)67U                                                                                                  /* [552] ComConf_ComSignal_DRENG98 */
    ,(BswU2)68U                                                                                                  /* [553] ComConf_ComSignal_DRENG101 */
    ,(BswU2)68U                                                                                                  /* [554] ComConf_ComSignal_DRENG102 */
    ,(BswU2)68U                                                                                                  /* [555] ComConf_ComSignal_DRENG103 */
    ,(BswU2)68U                                                                                                  /* [556] ComConf_ComSignal_DRENG104 */
    ,(BswU2)68U                                                                                                  /* [557] ComConf_ComSignal_DRENG105 */
    ,(BswU2)68U                                                                                                  /* [558] ComConf_ComSignal_DRENG106 */
    ,(BswU2)68U                                                                                                  /* [559] ComConf_ComSignal_DRENG107 */
    ,(BswU2)68U                                                                                                  /* [560] ComConf_ComSignal_DRENG108 */
    ,(BswU2)69U                                                                                                  /* [561] ComConf_ComSignal_VIN_1 */
    ,(BswU2)69U                                                                                                  /* [562] ComConf_ComSignal_VIN_2 */
    ,(BswU2)69U                                                                                                  /* [563] ComConf_ComSignal_VIN_3 */
    ,(BswU2)69U                                                                                                  /* [564] ComConf_ComSignal_VIN_4 */
    ,(BswU2)69U                                                                                                  /* [565] ComConf_ComSignal_VIN_5 */
    ,(BswU2)69U                                                                                                  /* [566] ComConf_ComSignal_VIN_6 */
    ,(BswU2)69U                                                                                                  /* [567] ComConf_ComSignal_VIN_7 */
    ,(BswU2)69U                                                                                                  /* [568] ComConf_ComSignal_VIN_8 */
    ,(BswU2)69U                                                                                                  /* [569] ComConf_ComSignal_VIN_9 */
    ,(BswU2)69U                                                                                                  /* [570] ComConf_ComSignal_VIN_10 */
    ,(BswU2)69U                                                                                                  /* [571] ComConf_ComSignal_VIN_11 */
    ,(BswU2)69U                                                                                                  /* [572] ComConf_ComSignal_VIN_12 */
    ,(BswU2)69U                                                                                                  /* [573] ComConf_ComSignal_VIN_13 */
    ,(BswU2)69U                                                                                                  /* [574] ComConf_ComSignal_VIN_14 */
    ,(BswU2)69U                                                                                                  /* [575] ComConf_ComSignal_VIN_15 */
    ,(BswU2)69U                                                                                                  /* [576] ComConf_ComSignal_VIN_16 */
    ,(BswU2)69U                                                                                                  /* [577] ComConf_ComSignal_VIN_17 */
    ,(BswU2)70U                                                                                                  /* [578] ComConf_ComSignal_DREPS01 */
    ,(BswU2)70U                                                                                                  /* [579] ComConf_ComSignal_DREPS02 */
    ,(BswU2)70U                                                                                                  /* [580] ComConf_ComSignal_DREPS03 */
    ,(BswU2)70U                                                                                                  /* [581] ComConf_ComSignal_DREPS04 */
    ,(BswU2)70U                                                                                                  /* [582] ComConf_ComSignal_DREPS05 */
    ,(BswU2)70U                                                                                                  /* [583] ComConf_ComSignal_DREPS06 */
    ,(BswU2)70U                                                                                                  /* [584] ComConf_ComSignal_DREPS07 */
    ,(BswU2)70U                                                                                                  /* [585] ComConf_ComSignal_DREPS08 */
    ,(BswU2)71U                                                                                                  /* [586] ComConf_ComSignal_V_DIST */
    ,(BswU2)71U                                                                                                  /* [587] ComConf_ComSignal_V_RELV */
    ,(BswU2)71U                                                                                                  /* [588] ComConf_ComSignal_V_SWOP */
    ,(BswU2)71U                                                                                                  /* [589] ComConf_ComSignal_RCURVR */
    ,(BswU2)71U                                                                                                  /* [590] ComConf_ComSignal_USMDSTTS */
    ,(BswU2)71U                                                                                                  /* [591] ComConf_ComSignal_COFFSET */
    ,(BswU2)71U                                                                                                  /* [592] ComConf_ComSignal_USMDSTSL */
    ,(BswU2)71U                                                                                                  /* [593] ComConf_ComSignal_RSACAUF */
    ,(BswU2)72U                                                                                                  /* [594] ComConf_ComSignal_OTHVW */
    ,(BswU2)72U                                                                                                  /* [595] ComConf_ComSignal_OTHVH */
    ,(BswU2)72U                                                                                                  /* [596] ComConf_ComSignal_OTHPB */
    ,(BswU2)72U                                                                                                  /* [597] ComConf_ComSignal_OTHTTC */
    ,(BswU2)72U                                                                                                  /* [598] ComConf_ComSignal_OTHTTYP */
    ,(BswU2)72U                                                                                                  /* [599] ComConf_ComSignal_FSPCSSTA */
    ,(BswU2)72U                                                                                                  /* [600] ComConf_ComSignal_HITPOS */
    ,(BswU2)72U                                                                                                  /* [601] ComConf_ComSignal_OTHRDANG */
    ,(BswU2)72U                                                                                                  /* [602] ComConf_ComSignal_OTHTSSST */
    ,(BswU2)72U                                                                                                  /* [603] ComConf_ComSignal_OTHOVLPC */
    ,(BswU2)72U                                                                                                  /* [604] ComConf_ComSignal_OTHRVPC */
    ,(BswU2)73U                                                                                                  /* [605] ComConf_ComSignal_OTHFALD */
    ,(BswU2)73U                                                                                                  /* [606] ComConf_ComSignal_OTHCOND */
    ,(BswU2)73U                                                                                                  /* [607] ComConf_ComSignal_OTHLDIS */
    ,(BswU2)73U                                                                                                  /* [608] ComConf_ComSignal_OTHFALF */
    ,(BswU2)73U                                                                                                  /* [609] ComConf_ComSignal_OTHCONF */
    ,(BswU2)73U                                                                                                  /* [610] ComConf_ComSignal_OTHLANE */
    ,(BswU2)74U                                                                                                  /* [611] ComConf_ComSignal_OTHSOR */
    ,(BswU2)74U                                                                                                  /* [612] ComConf_ComSignal_OTHROR */
    ,(BswU2)74U                                                                                                  /* [613] ComConf_ComSignal_OTHLX */
    ,(BswU2)74U                                                                                                  /* [614] ComConf_ComSignal_OTHSOLAR */
    ,(BswU2)75U                                                                                                  /* [615] ComConf_ComSignal_XREQFPB */
    ,(BswU2)75U                                                                                                  /* [616] ComConf_ComSignal_XREQPB */
    ,(BswU2)75U                                                                                                  /* [617] ComConf_ComSignal_XREQPBH */
    ,(BswU2)76U                                                                                                  /* [618] ComConf_ComSignal_E_CRC0A8 */
    ,(BswU2)76U                                                                                                  /* [619] ComConf_ComSignal_E_CNT0A8 */
    ,(BswU2)76U                                                                                                  /* [620] ComConf_ComSignal_AVSTRGR */
    ,(BswU2)76U                                                                                                  /* [621] ComConf_ComSignal_PBATRGR */
    ,(BswU2)76U                                                                                                  /* [622] ComConf_ComSignal_PCSALM */
    ,(BswU2)76U                                                                                                  /* [623] ComConf_ComSignal_FV0A8_D */
    ,(BswU2)76U                                                                                                  /* [624] ComConf_ComSignal_KZK0A8_D */
    ,(BswU2)77U                                                                                                  /* [625] ComConf_ComSignal_LK_ST */
    ,(BswU2)77U                                                                                                  /* [626] ComConf_ComSignal_LK_FUNC */
    ,(BswU2)77U                                                                                                  /* [627] ComConf_ComSignal_ULK_ST */
    ,(BswU2)77U                                                                                                  /* [628] ComConf_ComSignal_ULK_FUNC */
    ,(BswU2)78U                                                                                                  /* [629] ComConf_ComSignal_RSISIDME */
    ,(BswU2)78U                                                                                                  /* [630] ComConf_ComSignal_RSISIDID */
    ,(BswU2)79U                                                                                                  /* [631] ComConf_ComSignal_HCPCLOP */
    ,(BswU2)79U                                                                                                  /* [632] ComConf_ComSignal_HCSUPEN2 */
    ,(BswU2)79U                                                                                                  /* [633] ComConf_ComSignal_HCSDWEN2 */
    ,(BswU2)79U                                                                                                  /* [634] ComConf_ComSignal_HCSUPEN */
    ,(BswU2)79U                                                                                                  /* [635] ComConf_ComSignal_HCSDWEN */
    ,(BswU2)79U                                                                                                  /* [636] ComConf_ComSignal_HCSMNSW */
    ,(BswU2)79U                                                                                                  /* [637] ComConf_ComSignal_HCSETDSP */
    ,(BswU2)79U                                                                                                  /* [638] ComConf_ComSignal_HCSSTPOP */
    ,(BswU2)79U                                                                                                  /* [639] ComConf_ComSignal_ODO_UNIT */
    ,(BswU2)79U                                                                                                  /* [640] ComConf_ComSignal_ODO */
    ,(BswU2)80U                                                                                                  /* [641] ComConf_ComSignal_RTQRRLMG */
    ,(BswU2)80U                                                                                                  /* [642] ComConf_ComSignal_RTQFRLMG */
    ,(BswU2)81U                                                                                                  /* [643] ComConf_ComSignal_BAOF_PDC */
    ,(BswU2)82U                                                                                                  /* [644] ComConf_ComSignal_E_CRC14F */
    ,(BswU2)82U                                                                                                  /* [645] ComConf_ComSignal_E_CNT14F */
    ,(BswU2)82U                                                                                                  /* [646] ComConf_ComSignal_RCPMD */
    ,(BswU2)82U                                                                                                  /* [647] ComConf_ComSignal_RCPONST */
    ,(BswU2)83U                                                                                                  /* [648] ComConf_ComSignal_LOC_ICON */
    ,(BswU2)83U                                                                                                  /* [649] ComConf_ComSignal_RT_NUM */
    ,(BswU2)83U                                                                                                  /* [650] ComConf_ComSignal_RPCTRMD2 */
    ,(BswU2)83U                                                                                                  /* [651] ComConf_ComSignal_RT1LBL1 */
    ,(BswU2)83U                                                                                                  /* [652] ComConf_ComSignal_RT1LBL2 */
    ,(BswU2)83U                                                                                                  /* [653] ComConf_ComSignal_RT1LEN */
    ,(BswU2)83U                                                                                                  /* [654] ComConf_ComSignal_RT1WPNUM */
    ,(BswU2)83U                                                                                                  /* [655] ComConf_ComSignal_RT2LBL1 */
    ,(BswU2)83U                                                                                                  /* [656] ComConf_ComSignal_RT2LBL2 */
    ,(BswU2)83U                                                                                                  /* [657] ComConf_ComSignal_RT2LEN */
    ,(BswU2)83U                                                                                                  /* [658] ComConf_ComSignal_RT2WPNUM */
    ,(BswU2)83U                                                                                                  /* [659] ComConf_ComSignal_RT3LBL1 */
    ,(BswU2)83U                                                                                                  /* [660] ComConf_ComSignal_RT3LBL2 */
    ,(BswU2)83U                                                                                                  /* [661] ComConf_ComSignal_RT3LEN */
    ,(BswU2)83U                                                                                                  /* [662] ComConf_ComSignal_RT3WPNUM */
    ,(BswU2)83U                                                                                                  /* [663] ComConf_ComSignal_RT4LBL1 */
    ,(BswU2)83U                                                                                                  /* [664] ComConf_ComSignal_RT4LBL2 */
    ,(BswU2)83U                                                                                                  /* [665] ComConf_ComSignal_RT4LEN */
    ,(BswU2)83U                                                                                                  /* [666] ComConf_ComSignal_RT4WPNUM */
    ,(BswU2)83U                                                                                                  /* [667] ComConf_ComSignal_RPVCLST */
    ,(BswU2)84U                                                                                                  /* [668] ComConf_ComSignal_RT_ID */
    ,(BswU2)84U                                                                                                  /* [669] ComConf_ComSignal_WP1_TYPE */
    ,(BswU2)84U                                                                                                  /* [670] ComConf_ComSignal_WP1_X */
    ,(BswU2)84U                                                                                                  /* [671] ComConf_ComSignal_WP1_Y */
    ,(BswU2)84U                                                                                                  /* [672] ComConf_ComSignal_WP1_DIR */
    ,(BswU2)84U                                                                                                  /* [673] ComConf_ComSignal_WP2_TYPE */
    ,(BswU2)84U                                                                                                  /* [674] ComConf_ComSignal_WP2_X */
    ,(BswU2)84U                                                                                                  /* [675] ComConf_ComSignal_WP2_Y */
    ,(BswU2)84U                                                                                                  /* [676] ComConf_ComSignal_WP2_DIR */
    ,(BswU2)84U                                                                                                  /* [677] ComConf_ComSignal_WP3_TYPE */
    ,(BswU2)84U                                                                                                  /* [678] ComConf_ComSignal_WP3_X */
    ,(BswU2)84U                                                                                                  /* [679] ComConf_ComSignal_WP3_Y */
    ,(BswU2)84U                                                                                                  /* [680] ComConf_ComSignal_WP3_DIR */
    ,(BswU2)84U                                                                                                  /* [681] ComConf_ComSignal_WP4_TYPE */
    ,(BswU2)84U                                                                                                  /* [682] ComConf_ComSignal_WP4_X */
    ,(BswU2)84U                                                                                                  /* [683] ComConf_ComSignal_WP4_Y */
    ,(BswU2)84U                                                                                                  /* [684] ComConf_ComSignal_WP4_DIR */
    ,(BswU2)84U                                                                                                  /* [685] ComConf_ComSignal_WP5_TYPE */
    ,(BswU2)84U                                                                                                  /* [686] ComConf_ComSignal_WP5_X */
    ,(BswU2)84U                                                                                                  /* [687] ComConf_ComSignal_WP5_Y */
    ,(BswU2)84U                                                                                                  /* [688] ComConf_ComSignal_WP5_DIR */
    ,(BswU2)84U                                                                                                  /* [689] ComConf_ComSignal_WP6_TYPE */
    ,(BswU2)84U                                                                                                  /* [690] ComConf_ComSignal_WP6_X */
    ,(BswU2)84U                                                                                                  /* [691] ComConf_ComSignal_WP6_Y */
    ,(BswU2)84U                                                                                                  /* [692] ComConf_ComSignal_WP6_DIR */
    ,(BswU2)84U                                                                                                  /* [693] ComConf_ComSignal_WP7_TYPE */
    ,(BswU2)84U                                                                                                  /* [694] ComConf_ComSignal_WP7_X */
    ,(BswU2)84U                                                                                                  /* [695] ComConf_ComSignal_WP7_Y */
    ,(BswU2)84U                                                                                                  /* [696] ComConf_ComSignal_WP7_DIR */
    ,(BswU2)84U                                                                                                  /* [697] ComConf_ComSignal_WP8_TYPE */
    ,(BswU2)84U                                                                                                  /* [698] ComConf_ComSignal_WP8_X */
    ,(BswU2)84U                                                                                                  /* [699] ComConf_ComSignal_WP8_Y */
    ,(BswU2)84U                                                                                                  /* [700] ComConf_ComSignal_WP8_DIR */
    ,(BswU2)84U                                                                                                  /* [701] ComConf_ComSignal_WP9_TYPE */
    ,(BswU2)84U                                                                                                  /* [702] ComConf_ComSignal_WP9_X */
    ,(BswU2)84U                                                                                                  /* [703] ComConf_ComSignal_WP9_Y */
    ,(BswU2)84U                                                                                                  /* [704] ComConf_ComSignal_WP9_DIR */
    ,(BswU2)84U                                                                                                  /* [705] ComConf_ComSignal_WP10_TYPE */
    ,(BswU2)84U                                                                                                  /* [706] ComConf_ComSignal_WP10_X */
    ,(BswU2)84U                                                                                                  /* [707] ComConf_ComSignal_WP10_Y */
    ,(BswU2)84U                                                                                                  /* [708] ComConf_ComSignal_WP10_DIR */
    ,(BswU2)84U                                                                                                  /* [709] ComConf_ComSignal_WP11_TYPE */
    ,(BswU2)84U                                                                                                  /* [710] ComConf_ComSignal_WP11_X */
    ,(BswU2)84U                                                                                                  /* [711] ComConf_ComSignal_WP11_Y */
    ,(BswU2)84U                                                                                                  /* [712] ComConf_ComSignal_WP11_DIR */
    ,(BswU2)84U                                                                                                  /* [713] ComConf_ComSignal_WP12_TYPE */
    ,(BswU2)84U                                                                                                  /* [714] ComConf_ComSignal_WP12_X */
    ,(BswU2)84U                                                                                                  /* [715] ComConf_ComSignal_WP12_Y */
    ,(BswU2)84U                                                                                                  /* [716] ComConf_ComSignal_WP12_DIR */
    ,(BswU2)84U                                                                                                  /* [717] ComConf_ComSignal_WP13_TYPE */
    ,(BswU2)84U                                                                                                  /* [718] ComConf_ComSignal_WP13_X */
    ,(BswU2)84U                                                                                                  /* [719] ComConf_ComSignal_WP13_Y */
    ,(BswU2)84U                                                                                                  /* [720] ComConf_ComSignal_WP13_DIR */
    ,(BswU2)84U                                                                                                  /* [721] ComConf_ComSignal_WP14_TYPE */
    ,(BswU2)84U                                                                                                  /* [722] ComConf_ComSignal_WP14_X */
    ,(BswU2)84U                                                                                                  /* [723] ComConf_ComSignal_WP14_Y */
    ,(BswU2)84U                                                                                                  /* [724] ComConf_ComSignal_WP14_DIR */
    ,(BswU2)84U                                                                                                  /* [725] ComConf_ComSignal_WP15_TYPE */
    ,(BswU2)84U                                                                                                  /* [726] ComConf_ComSignal_WP15_X */
    ,(BswU2)84U                                                                                                  /* [727] ComConf_ComSignal_WP15_Y */
    ,(BswU2)84U                                                                                                  /* [728] ComConf_ComSignal_WP15_DIR */
    ,(BswU2)84U                                                                                                  /* [729] ComConf_ComSignal_WP16_TYPE */
    ,(BswU2)84U                                                                                                  /* [730] ComConf_ComSignal_WP16_X */
    ,(BswU2)84U                                                                                                  /* [731] ComConf_ComSignal_WP16_Y */
    ,(BswU2)84U                                                                                                  /* [732] ComConf_ComSignal_WP16_DIR */
    ,(BswU2)84U                                                                                                  /* [733] ComConf_ComSignal_WP17_TYPE */
    ,(BswU2)84U                                                                                                  /* [734] ComConf_ComSignal_WP17_X */
    ,(BswU2)84U                                                                                                  /* [735] ComConf_ComSignal_WP17_Y */
    ,(BswU2)84U                                                                                                  /* [736] ComConf_ComSignal_WP17_DIR */
    ,(BswU2)84U                                                                                                  /* [737] ComConf_ComSignal_WP18_TYPE */
    ,(BswU2)84U                                                                                                  /* [738] ComConf_ComSignal_WP18_X */
    ,(BswU2)84U                                                                                                  /* [739] ComConf_ComSignal_WP18_Y */
    ,(BswU2)84U                                                                                                  /* [740] ComConf_ComSignal_WP18_DIR */
    ,(BswU2)84U                                                                                                  /* [741] ComConf_ComSignal_WP19_TYPE */
    ,(BswU2)84U                                                                                                  /* [742] ComConf_ComSignal_WP19_X */
    ,(BswU2)84U                                                                                                  /* [743] ComConf_ComSignal_WP19_Y */
    ,(BswU2)84U                                                                                                  /* [744] ComConf_ComSignal_WP19_DIR */
    ,(BswU2)84U                                                                                                  /* [745] ComConf_ComSignal_WP20_TYPE */
    ,(BswU2)84U                                                                                                  /* [746] ComConf_ComSignal_WP20_X */
    ,(BswU2)84U                                                                                                  /* [747] ComConf_ComSignal_WP20_Y */
    ,(BswU2)84U                                                                                                  /* [748] ComConf_ComSignal_WP20_DIR */
    ,(BswU2)84U                                                                                                  /* [749] ComConf_ComSignal_WP21_TYPE */
    ,(BswU2)84U                                                                                                  /* [750] ComConf_ComSignal_WP21_X */
    ,(BswU2)84U                                                                                                  /* [751] ComConf_ComSignal_WP21_Y */
    ,(BswU2)84U                                                                                                  /* [752] ComConf_ComSignal_WP21_DIR */
    ,(BswU2)84U                                                                                                  /* [753] ComConf_ComSignal_WP22_TYPE */
    ,(BswU2)84U                                                                                                  /* [754] ComConf_ComSignal_WP22_X */
    ,(BswU2)84U                                                                                                  /* [755] ComConf_ComSignal_WP22_Y */
    ,(BswU2)84U                                                                                                  /* [756] ComConf_ComSignal_WP22_DIR */
    ,(BswU2)84U                                                                                                  /* [757] ComConf_ComSignal_WP23_TYPE */
    ,(BswU2)84U                                                                                                  /* [758] ComConf_ComSignal_WP23_X */
    ,(BswU2)84U                                                                                                  /* [759] ComConf_ComSignal_WP23_Y */
    ,(BswU2)84U                                                                                                  /* [760] ComConf_ComSignal_WP23_DIR */
    ,(BswU2)84U                                                                                                  /* [761] ComConf_ComSignal_WP24_TYPE */
    ,(BswU2)84U                                                                                                  /* [762] ComConf_ComSignal_WP24_X */
    ,(BswU2)84U                                                                                                  /* [763] ComConf_ComSignal_WP24_Y */
    ,(BswU2)84U                                                                                                  /* [764] ComConf_ComSignal_WP24_DIR */
    ,(BswU2)84U                                                                                                  /* [765] ComConf_ComSignal_WP25_TYPE */
    ,(BswU2)84U                                                                                                  /* [766] ComConf_ComSignal_WP25_X */
    ,(BswU2)84U                                                                                                  /* [767] ComConf_ComSignal_WP25_Y */
    ,(BswU2)84U                                                                                                  /* [768] ComConf_ComSignal_WP25_DIR */
    ,(BswU2)85U                                                                                                  /* [769] ComConf_ComSignal_WP26_TYPE */
    ,(BswU2)85U                                                                                                  /* [770] ComConf_ComSignal_WP26_X */
    ,(BswU2)85U                                                                                                  /* [771] ComConf_ComSignal_WP26_Y */
    ,(BswU2)85U                                                                                                  /* [772] ComConf_ComSignal_WP26_DIR */
    ,(BswU2)85U                                                                                                  /* [773] ComConf_ComSignal_WP27_TYPE */
    ,(BswU2)85U                                                                                                  /* [774] ComConf_ComSignal_WP27_X */
    ,(BswU2)85U                                                                                                  /* [775] ComConf_ComSignal_WP27_Y */
    ,(BswU2)85U                                                                                                  /* [776] ComConf_ComSignal_WP27_DIR */
    ,(BswU2)85U                                                                                                  /* [777] ComConf_ComSignal_WP28_TYPE */
    ,(BswU2)85U                                                                                                  /* [778] ComConf_ComSignal_WP28_X */
    ,(BswU2)85U                                                                                                  /* [779] ComConf_ComSignal_WP28_Y */
    ,(BswU2)85U                                                                                                  /* [780] ComConf_ComSignal_WP28_DIR */
    ,(BswU2)85U                                                                                                  /* [781] ComConf_ComSignal_WP29_TYPE */
    ,(BswU2)85U                                                                                                  /* [782] ComConf_ComSignal_WP29_X */
    ,(BswU2)85U                                                                                                  /* [783] ComConf_ComSignal_WP29_Y */
    ,(BswU2)85U                                                                                                  /* [784] ComConf_ComSignal_WP29_DIR */
    ,(BswU2)85U                                                                                                  /* [785] ComConf_ComSignal_WP30_TYPE */
    ,(BswU2)85U                                                                                                  /* [786] ComConf_ComSignal_WP30_X */
    ,(BswU2)85U                                                                                                  /* [787] ComConf_ComSignal_WP30_Y */
    ,(BswU2)85U                                                                                                  /* [788] ComConf_ComSignal_WP30_DIR */
    ,(BswU2)85U                                                                                                  /* [789] ComConf_ComSignal_WP31_TYPE */
    ,(BswU2)85U                                                                                                  /* [790] ComConf_ComSignal_WP31_X */
    ,(BswU2)85U                                                                                                  /* [791] ComConf_ComSignal_WP31_Y */
    ,(BswU2)85U                                                                                                  /* [792] ComConf_ComSignal_WP31_DIR */
    ,(BswU2)85U                                                                                                  /* [793] ComConf_ComSignal_WP32_TYPE */
    ,(BswU2)85U                                                                                                  /* [794] ComConf_ComSignal_WP32_X */
    ,(BswU2)85U                                                                                                  /* [795] ComConf_ComSignal_WP32_Y */
    ,(BswU2)85U                                                                                                  /* [796] ComConf_ComSignal_WP32_DIR */
    ,(BswU2)85U                                                                                                  /* [797] ComConf_ComSignal_WP33_TYPE */
    ,(BswU2)85U                                                                                                  /* [798] ComConf_ComSignal_WP33_X */
    ,(BswU2)85U                                                                                                  /* [799] ComConf_ComSignal_WP33_Y */
    ,(BswU2)85U                                                                                                  /* [800] ComConf_ComSignal_WP33_DIR */
    ,(BswU2)85U                                                                                                  /* [801] ComConf_ComSignal_WP34_TYPE */
    ,(BswU2)85U                                                                                                  /* [802] ComConf_ComSignal_WP34_X */
    ,(BswU2)85U                                                                                                  /* [803] ComConf_ComSignal_WP34_Y */
    ,(BswU2)85U                                                                                                  /* [804] ComConf_ComSignal_WP34_DIR */
    ,(BswU2)85U                                                                                                  /* [805] ComConf_ComSignal_WP35_TYPE */
    ,(BswU2)85U                                                                                                  /* [806] ComConf_ComSignal_WP35_X */
    ,(BswU2)85U                                                                                                  /* [807] ComConf_ComSignal_WP35_Y */
    ,(BswU2)85U                                                                                                  /* [808] ComConf_ComSignal_WP35_DIR */
    ,(BswU2)85U                                                                                                  /* [809] ComConf_ComSignal_WP36_TYPE */
    ,(BswU2)85U                                                                                                  /* [810] ComConf_ComSignal_WP36_X */
    ,(BswU2)85U                                                                                                  /* [811] ComConf_ComSignal_WP36_Y */
    ,(BswU2)85U                                                                                                  /* [812] ComConf_ComSignal_WP36_DIR */
    ,(BswU2)85U                                                                                                  /* [813] ComConf_ComSignal_WP37_TYPE */
    ,(BswU2)85U                                                                                                  /* [814] ComConf_ComSignal_WP37_X */
    ,(BswU2)85U                                                                                                  /* [815] ComConf_ComSignal_WP37_Y */
    ,(BswU2)85U                                                                                                  /* [816] ComConf_ComSignal_WP37_DIR */
    ,(BswU2)85U                                                                                                  /* [817] ComConf_ComSignal_WP38_TYPE */
    ,(BswU2)85U                                                                                                  /* [818] ComConf_ComSignal_WP38_X */
    ,(BswU2)85U                                                                                                  /* [819] ComConf_ComSignal_WP38_Y */
    ,(BswU2)85U                                                                                                  /* [820] ComConf_ComSignal_WP38_DIR */
    ,(BswU2)85U                                                                                                  /* [821] ComConf_ComSignal_WP39_TYPE */
    ,(BswU2)85U                                                                                                  /* [822] ComConf_ComSignal_WP39_X */
    ,(BswU2)85U                                                                                                  /* [823] ComConf_ComSignal_WP39_Y */
    ,(BswU2)85U                                                                                                  /* [824] ComConf_ComSignal_WP39_DIR */
    ,(BswU2)85U                                                                                                  /* [825] ComConf_ComSignal_WP40_TYPE */
    ,(BswU2)85U                                                                                                  /* [826] ComConf_ComSignal_WP40_X */
    ,(BswU2)85U                                                                                                  /* [827] ComConf_ComSignal_WP40_Y */
    ,(BswU2)85U                                                                                                  /* [828] ComConf_ComSignal_WP40_DIR */
    ,(BswU2)85U                                                                                                  /* [829] ComConf_ComSignal_WP41_TYPE */
    ,(BswU2)85U                                                                                                  /* [830] ComConf_ComSignal_WP41_X */
    ,(BswU2)85U                                                                                                  /* [831] ComConf_ComSignal_WP41_Y */
    ,(BswU2)85U                                                                                                  /* [832] ComConf_ComSignal_WP41_DIR */
    ,(BswU2)85U                                                                                                  /* [833] ComConf_ComSignal_WP42_TYPE */
    ,(BswU2)85U                                                                                                  /* [834] ComConf_ComSignal_WP42_X */
    ,(BswU2)85U                                                                                                  /* [835] ComConf_ComSignal_WP42_Y */
    ,(BswU2)85U                                                                                                  /* [836] ComConf_ComSignal_WP42_DIR */
    ,(BswU2)85U                                                                                                  /* [837] ComConf_ComSignal_WP43_TYPE */
    ,(BswU2)85U                                                                                                  /* [838] ComConf_ComSignal_WP43_X */
    ,(BswU2)85U                                                                                                  /* [839] ComConf_ComSignal_WP43_Y */
    ,(BswU2)85U                                                                                                  /* [840] ComConf_ComSignal_WP43_DIR */
    ,(BswU2)85U                                                                                                  /* [841] ComConf_ComSignal_WP44_TYPE */
    ,(BswU2)85U                                                                                                  /* [842] ComConf_ComSignal_WP44_X */
    ,(BswU2)85U                                                                                                  /* [843] ComConf_ComSignal_WP44_Y */
    ,(BswU2)85U                                                                                                  /* [844] ComConf_ComSignal_WP44_DIR */
    ,(BswU2)85U                                                                                                  /* [845] ComConf_ComSignal_WP45_TYPE */
    ,(BswU2)85U                                                                                                  /* [846] ComConf_ComSignal_WP45_X */
    ,(BswU2)85U                                                                                                  /* [847] ComConf_ComSignal_WP45_Y */
    ,(BswU2)85U                                                                                                  /* [848] ComConf_ComSignal_WP45_DIR */
    ,(BswU2)85U                                                                                                  /* [849] ComConf_ComSignal_WP46_TYPE */
    ,(BswU2)85U                                                                                                  /* [850] ComConf_ComSignal_WP46_X */
    ,(BswU2)85U                                                                                                  /* [851] ComConf_ComSignal_WP46_Y */
    ,(BswU2)85U                                                                                                  /* [852] ComConf_ComSignal_WP46_DIR */
    ,(BswU2)85U                                                                                                  /* [853] ComConf_ComSignal_WP47_TYPE */
    ,(BswU2)85U                                                                                                  /* [854] ComConf_ComSignal_WP47_X */
    ,(BswU2)85U                                                                                                  /* [855] ComConf_ComSignal_WP47_Y */
    ,(BswU2)85U                                                                                                  /* [856] ComConf_ComSignal_WP47_DIR */
    ,(BswU2)85U                                                                                                  /* [857] ComConf_ComSignal_WP48_TYPE */
    ,(BswU2)85U                                                                                                  /* [858] ComConf_ComSignal_WP48_X */
    ,(BswU2)85U                                                                                                  /* [859] ComConf_ComSignal_WP48_Y */
    ,(BswU2)85U                                                                                                  /* [860] ComConf_ComSignal_WP48_DIR */
    ,(BswU2)85U                                                                                                  /* [861] ComConf_ComSignal_WP49_TYPE */
    ,(BswU2)85U                                                                                                  /* [862] ComConf_ComSignal_WP49_X */
    ,(BswU2)85U                                                                                                  /* [863] ComConf_ComSignal_WP49_Y */
    ,(BswU2)85U                                                                                                  /* [864] ComConf_ComSignal_WP49_DIR */
    ,(BswU2)85U                                                                                                  /* [865] ComConf_ComSignal_WP50_TYPE */
    ,(BswU2)85U                                                                                                  /* [866] ComConf_ComSignal_WP50_X */
    ,(BswU2)85U                                                                                                  /* [867] ComConf_ComSignal_WP50_Y */
    ,(BswU2)85U                                                                                                  /* [868] ComConf_ComSignal_WP50_DIR */
    ,(BswU2)86U                                                                                                  /* [869] ComConf_ComSignal_D_YEAR */
    ,(BswU2)86U                                                                                                  /* [870] ComConf_ComSignal_D_MONT */
    ,(BswU2)86U                                                                                                  /* [871] ComConf_ComSignal_D_DAY */
    ,(BswU2)86U                                                                                                  /* [872] ComConf_ComSignal_D_HOUR */
    ,(BswU2)86U                                                                                                  /* [873] ComConf_ComSignal_D_MIN */
    ,(BswU2)86U                                                                                                  /* [874] ComConf_ComSignal_D_SEC */
    ,(BswU2)87U                                                                                                  /* [875] ComConf_ComSignal_GNSSYNC1 */
    ,(BswU2)87U                                                                                                  /* [876] ComConf_ComSignal_VA_INVA */
    ,(BswU2)87U                                                                                                  /* [877] ComConf_ComSignal_LATUDE */
    ,(BswU2)87U                                                                                                  /* [878] ComConf_ComSignal_LOTUDE1 */
    ,(BswU2)87U                                                                                                  /* [879] ComConf_ComSignal_D_LAT1 */
    ,(BswU2)87U                                                                                                  /* [880] ComConf_ComSignal_D_LAT2 */
    ,(BswU2)88U                                                                                                  /* [881] ComConf_ComSignal_GNSSYNC2 */
    ,(BswU2)88U                                                                                                  /* [882] ComConf_ComSignal_D_LON1 */
    ,(BswU2)88U                                                                                                  /* [883] ComConf_ComSignal_D_LON2 */
    ,(BswU2)89U                                                                                                  /* [884] ComConf_ComSignal_GNSSYNC3 */
    ,(BswU2)89U                                                                                                  /* [885] ComConf_ComSignal_ALTITUDE */
    ,(BswU2)90U                                                                                                  /* [886] ComConf_ComSignal_RSCYCL11 */
    ,(BswU2)90U                                                                                                  /* [887] ComConf_ComSignal_RSCYCL12 */
    ,(BswU2)90U                                                                                                  /* [888] ComConf_ComSignal_RSCYCL13 */
    ,(BswU2)90U                                                                                                  /* [889] ComConf_ComSignal_RSCYCL14 */
    ,(BswU2)90U                                                                                                  /* [890] ComConf_ComSignal_RSCYCL15 */
    ,(BswU2)90U                                                                                                  /* [891] ComConf_ComSignal_RSCYCL16 */
    ,(BswU2)91U                                                                                                  /* [892] ComConf_ComSignal_DVGR01 */
    ,(BswU2)91U                                                                                                  /* [893] ComConf_ComSignal_DVGR02 */
    ,(BswU2)91U                                                                                                  /* [894] ComConf_ComSignal_DVGR03 */
    ,(BswU2)91U                                                                                                  /* [895] ComConf_ComSignal_DVGR04 */
    ,(BswU2)91U                                                                                                  /* [896] ComConf_ComSignal_DVGR05 */
    ,(BswU2)91U                                                                                                  /* [897] ComConf_ComSignal_DVGR06 */
    ,(BswU2)91U                                                                                                  /* [898] ComConf_ComSignal_DVGR07 */
    ,(BswU2)91U                                                                                                  /* [899] ComConf_ComSignal_DVGR08 */
    ,(BswU2)91U                                                                                                  /* [900] ComConf_ComSignal_DVGR09 */
    ,(BswU2)91U                                                                                                  /* [901] ComConf_ComSignal_DVGR10 */
    ,(BswU2)91U                                                                                                  /* [902] ComConf_ComSignal_DVGR11 */
    ,(BswU2)91U                                                                                                  /* [903] ComConf_ComSignal_DVGR12 */
    ,(BswU2)91U                                                                                                  /* [904] ComConf_ComSignal_DVGR13 */
    ,(BswU2)91U                                                                                                  /* [905] ComConf_ComSignal_DVGR14 */
    ,(BswU2)91U                                                                                                  /* [906] ComConf_ComSignal_DVGR15 */
    ,(BswU2)91U                                                                                                  /* [907] ComConf_ComSignal_DVGR16 */
    ,(BswU2)91U                                                                                                  /* [908] ComConf_ComSignal_DVGR17 */
    ,(BswU2)91U                                                                                                  /* [909] ComConf_ComSignal_DVGR18 */
    ,(BswU2)91U                                                                                                  /* [910] ComConf_ComSignal_DVGR19 */
    ,(BswU2)91U                                                                                                  /* [911] ComConf_ComSignal_DVGR20 */
    ,(BswU2)91U                                                                                                  /* [912] ComConf_ComSignal_DVGR21 */
    ,(BswU2)91U                                                                                                  /* [913] ComConf_ComSignal_DVGR22 */
    ,(BswU2)91U                                                                                                  /* [914] ComConf_ComSignal_DVGR23 */
    ,(BswU2)91U                                                                                                  /* [915] ComConf_ComSignal_DVGR24 */
    ,(BswU2)91U                                                                                                  /* [916] ComConf_ComSignal_DVGR25 */
    ,(BswU2)91U                                                                                                  /* [917] ComConf_ComSignal_DVGR26 */
    ,(BswU2)91U                                                                                                  /* [918] ComConf_ComSignal_DVGR27 */
    ,(BswU2)91U                                                                                                  /* [919] ComConf_ComSignal_DVGR28 */
    ,(BswU2)91U                                                                                                  /* [920] ComConf_ComSignal_DVGR29 */
    ,(BswU2)91U                                                                                                  /* [921] ComConf_ComSignal_DVGR30 */
    ,(BswU2)91U                                                                                                  /* [922] ComConf_ComSignal_DVGR31 */
    ,(BswU2)91U                                                                                                  /* [923] ComConf_ComSignal_DVGR32 */
    ,(BswU2)92U                                                                                                  /* [924] ComConf_ComSignal_DRVSCID */
    ,(BswU2)92U                                                                                                  /* [925] ComConf_ComSignal_DRVSC02 */
    ,(BswU2)92U                                                                                                  /* [926] ComConf_ComSignal_DRVSC03 */
    ,(BswU2)92U                                                                                                  /* [927] ComConf_ComSignal_DRVSC04 */
    ,(BswU2)92U                                                                                                  /* [928] ComConf_ComSignal_DRVSC05 */
    ,(BswU2)92U                                                                                                  /* [929] ComConf_ComSignal_DRVSC06 */
    ,(BswU2)92U                                                                                                  /* [930] ComConf_ComSignal_DRVSC07 */
    ,(BswU2)92U                                                                                                  /* [931] ComConf_ComSignal_DRVSC08 */
    ,(BswU2)92U                                                                                                  /* [932] ComConf_ComSignal_DRVSC11 */
    ,(BswU2)92U                                                                                                  /* [933] ComConf_ComSignal_DRVSC12 */
    ,(BswU2)92U                                                                                                  /* [934] ComConf_ComSignal_DRVSC13 */
    ,(BswU2)92U                                                                                                  /* [935] ComConf_ComSignal_DRVSC14 */
    ,(BswU2)92U                                                                                                  /* [936] ComConf_ComSignal_DRVSC15 */
    ,(BswU2)92U                                                                                                  /* [937] ComConf_ComSignal_DRVSC16 */
    ,(BswU2)92U                                                                                                  /* [938] ComConf_ComSignal_DRVSC17 */
    ,(BswU2)92U                                                                                                  /* [939] ComConf_ComSignal_DRVSC18 */
    ,(BswU2)92U                                                                                                  /* [940] ComConf_ComSignal_DRVSC21 */
    ,(BswU2)92U                                                                                                  /* [941] ComConf_ComSignal_DRVSC22 */
    ,(BswU2)92U                                                                                                  /* [942] ComConf_ComSignal_DRVSC23 */
    ,(BswU2)92U                                                                                                  /* [943] ComConf_ComSignal_DRVSC24 */
    ,(BswU2)92U                                                                                                  /* [944] ComConf_ComSignal_DRVSC25 */
    ,(BswU2)92U                                                                                                  /* [945] ComConf_ComSignal_DRVSC26 */
    ,(BswU2)92U                                                                                                  /* [946] ComConf_ComSignal_DRVSC27 */
    ,(BswU2)92U                                                                                                  /* [947] ComConf_ComSignal_DRVSC28 */
    ,(BswU2)92U                                                                                                  /* [948] ComConf_ComSignal_DREPB01 */
    ,(BswU2)92U                                                                                                  /* [949] ComConf_ComSignal_DREPB02 */
    ,(BswU2)92U                                                                                                  /* [950] ComConf_ComSignal_DREPB03 */
    ,(BswU2)92U                                                                                                  /* [951] ComConf_ComSignal_DREPB04 */
    ,(BswU2)92U                                                                                                  /* [952] ComConf_ComSignal_DREPB05 */
    ,(BswU2)92U                                                                                                  /* [953] ComConf_ComSignal_DREPB06 */
    ,(BswU2)92U                                                                                                  /* [954] ComConf_ComSignal_DREPB07 */
    ,(BswU2)92U                                                                                                  /* [955] ComConf_ComSignal_DREPB08 */
    ,(BswU2)93U                                                                                                  /* [956] ComConf_ComSignal_E_CRC09E */
    ,(BswU2)93U                                                                                                  /* [957] ComConf_ComSignal_E_CNT09E */
    ,(BswU2)93U                                                                                                  /* [958] ComConf_ComSignal_SP1S */
    ,(BswU2)93U                                                                                                  /* [959] ComConf_ComSignal_GVSPDINV */
    ,(BswU2)93U                                                                                                  /* [960] ComConf_ComSignal_SP1P */
    ,(BswU2)93U                                                                                                  /* [961] ComConf_ComSignal_SP1 */
    ,(BswU2)93U                                                                                                  /* [962] ComConf_ComSignal_GVSPD */
    ,(BswU2)93U                                                                                                  /* [963] ComConf_ComSignal_PWCF */
    ,(BswU2)93U                                                                                                  /* [964] ComConf_ComSignal_PWC */
    ,(BswU2)93U                                                                                                  /* [965] ComConf_ComSignal_PWCS */
    ,(BswU2)93U                                                                                                  /* [966] ComConf_ComSignal_PMCF */
    ,(BswU2)93U                                                                                                  /* [967] ComConf_ComSignal_PMCS */
    ,(BswU2)93U                                                                                                  /* [968] ComConf_ComSignal_PMC */
    ,(BswU2)93U                                                                                                  /* [969] ComConf_ComSignal_FV09E_D */
    ,(BswU2)93U                                                                                                  /* [970] ComConf_ComSignal_KZK09E_D */
    ,(BswU2)94U                                                                                                  /* [971] ComConf_ComSignal_FRWIPOPE */
    ,(BswU2)94U                                                                                                  /* [972] ComConf_ComSignal_FRWASH */
    ,(BswU2)94U                                                                                                  /* [973] ComConf_ComSignal_RRWIPOPE */
    ,(BswU2)94U                                                                                                  /* [974] ComConf_ComSignal_RRWASH */
    ,(BswU2)95U                                                                                                  /* [975] ComConf_ComSignal_W_STPZ */
    ,(BswU2)95U                                                                                                  /* [976] ComConf_ComSignal_FI_STP */
    ,(BswU2)96U                                                                                                  /* [977] ComConf_ComSignal_R_AC_ST */
    ,(BswU2)96U                                                                                                  /* [978] ComConf_ComSignal_R_SYS_2 */
    ,(BswU2)97U                                                                                                  /* [979] ComConf_ComSignal_R_FTE_ST */
    ,(BswU2)97U                                                                                                  /* [980] ComConf_ComSignal_R_BD_ST */
    ,(BswU2)97U                                                                                                  /* [981] ComConf_ComSignal_R_TIME */
    ,(BswU2)98U                                                                                                  /* [982] ComConf_ComSignal_R_INT_ST */
    ,(BswU2)99U                                                                                                  /* [983] ComConf_ComSignal_R_LMP_ST */
    ,(BswU2)99U                                                                                                  /* [984] ComConf_ComSignal_R_SDE_ST */
    ,(BswU2)99U                                                                                                  /* [985] ComConf_ComSignal_R_SYS_3 */
    ,(BswU2)100U                                                                                                 /* [986] ComConf_ComSignal_R_ST_ST */
    ,(BswU2)100U                                                                                                 /* [987] ComConf_ComSignal_R_SYS_1 */
};

BswConst Bsw_Com_MsgInfoType bsw_com_stMsgInfoTbl[BSW_COM_MSG_NUM] = {
     { BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [0] MSG_ABG1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [1] MSG_ABG1D51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [2] MSG_ABG1S09_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [3] MSG_ACN1D50_RXCH0 */
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
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [14] MSG_AVN1S95_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [15] MSG_BAT1E45_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [16] MSG_BAT1EDA_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [17] MSG_BAT1S08_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [18] MSG_BAT2ED2_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 5000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [19] MSG_BDB1F03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [20] MSG_BDB1S10_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [21] MSG_BDC1S41_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [22] MSG_BDC1S81_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [23] MSG_BDC1S82_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  900U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [24] MSG_BDC1S91_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [25] MSG_BDC1SH8_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [26] MSG_BDC1SI1_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [27] MSG_BDC1SI2_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [28] MSG_BDC1SI3_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [29] MSG_BDC1SI4_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [30] MSG_BDC1SI5_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [31] MSG_BDC1SI6_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [32] MSG_BDC1SI7_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [33] MSG_BDC1SI8_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [34] MSG_BDC1SI9_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [35] MSG_BDC1SJ0_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [36] MSG_BDC1SJ1_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [37] MSG_BDC1SJ2_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [38] MSG_BDF3S01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [39] MSG_BDF3S02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [40] MSG_BDR3S02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [41] MSG_CDC1S04_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [42] MSG_CMB1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [43] MSG_CMB1S04_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [44] MSG_DCM1S08_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [45] MSG_DDM1S00_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [46] MSG_DDM1S09_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [47] MSG_DDM1S16_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [48] MSG_DDM1S35_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [49] MSG_DDM1SFH_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [50] MSG_DKY1S26_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [51] MSG_DS11S27_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [52] MSG_EBU1D01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [53] MSG_ECT1S93_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 2000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [54] MSG_EHV1E96_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  160U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [55] MSG_EHV1F02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [56] MSG_EHV1S23_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  160U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [57] MSG_EHV2G10_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  240U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [58] MSG_EHV2G20_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [59] MSG_EIM1S01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [60] MSG_ENG1C01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [61] MSG_ENG1C02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [62] MSG_ENG1D51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [63] MSG_ENG1D52_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [64] MSG_ENG1D53_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [65] MSG_ENG1D55_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [66] MSG_ENG1D56_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [67] MSG_ENG1D59_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [68] MSG_ENG1D60_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(15000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [69] MSG_ENG1S51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [70] MSG_EPS1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [71] MSG_FCM1C01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [72] MSG_FCM1S49_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [73] MSG_FCM1S76_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(  500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [74] MSG_FCM1S79_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [75] MSG_FCM1S90_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [76] MSG_FCM1S95_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [77] MSG_IDT1S07_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [78] MSG_IDT1S15_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [79] MSG_MET1S02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(   80U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [80] MSG_MGC1F13_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [81] MSG_PDC1G01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [82] MSG_RCP1S03_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [83] MSG_RCP1S04_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [84] MSG_RCP1S05_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)64U   /* [85] MSG_RCP1S06_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 3000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [86] MSG_RSE1G20_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [87] MSG_RSE1G24_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [88] MSG_RSE1G25_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [89] MSG_RSE1G26_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [90] MSG_RSE1S02_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [91] MSG_VGR1D50_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC( 1500U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [92] MSG_VSC1D51_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(   60U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [93] MSG_VSC1G13_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(10000U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [94] MSG_WIP1S01_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)8U   /* [95] MSG_ZN11S08_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [96] MSG_ZN11S63_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [97] MSG_ZN11S64_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [98] MSG_ZN11S65_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [99] MSG_ZN11S66_RXCH0 */
      ,(BswU1)( BSW_COM_EVENTDELAY_NOUSE | BSW_COM_EVTAWAKE_NOUSE | BSW_COM_PREPRDTXRTRG_NOUSE | BSW_COM_SENDNTIMES_NOUSE | BSW_COM_CHGPRDIPDU_NOUSE | BSW_COM_EVTWAKEUPTX_NOUSE )
      ,(BswU1)( BSW_COM_TXREQCONF_NOUSE | BSW_COM_TXCONF_NOUSE | BSW_COM_RXMSG_USE   | BSW_COM_PRESTORE_USE   | BSW_COM_ALIVECOUNTER_NOUSE | BSW_COM_PRETX_NOUSE ) }
    ,{ BSW_COM_u2MILSEC(    0U), BSW_COM_u1CH00, (BswU1)(BSW_COM_VPS_NOUSE), (BswU2)32U   /* [100] MSG_ZN11S67_RXCH0 */
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
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
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
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
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
    ,{    /* [16] MSG_BAT1EDA_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [17] MSG_BAT1S08_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [18] MSG_BAT2ED2_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [19] MSG_BDB1F03_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [20] MSG_BDB1S10_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [21] MSG_BDC1S41_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [22] MSG_BDC1S81_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [23] MSG_BDC1S82_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [24] MSG_BDC1S91_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [25] MSG_BDC1SH8_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [26] MSG_BDC1SI1_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [27] MSG_BDC1SI2_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [28] MSG_BDC1SI3_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [29] MSG_BDC1SI4_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [30] MSG_BDC1SI5_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [31] MSG_BDC1SI6_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [32] MSG_BDC1SI7_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [33] MSG_BDC1SI8_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [34] MSG_BDC1SI9_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [35] MSG_BDC1SJ0_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [36] MSG_BDC1SJ1_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [37] MSG_BDC1SJ2_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [38] MSG_BDF3S01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [39] MSG_BDF3S02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [40] MSG_BDR3S02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [41] MSG_CDC1S04_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [42] MSG_CMB1S03_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [43] MSG_CMB1S04_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [44] MSG_DCM1S08_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [45] MSG_DDM1S00_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [46] MSG_DDM1S09_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [47] MSG_DDM1S16_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [48] MSG_DDM1S35_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [49] MSG_DDM1SFH_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [50] MSG_DKY1S26_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [51] MSG_DS11S27_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [52] MSG_EBU1D01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [53] MSG_ECT1S93_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [54] MSG_EHV1E96_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [55] MSG_EHV1F02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [56] MSG_EHV1S23_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [57] MSG_EHV2G10_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [58] MSG_EHV2G20_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [59] MSG_EIM1S01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [60] MSG_ENG1C01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [61] MSG_ENG1C02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [62] MSG_ENG1D51_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [63] MSG_ENG1D52_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [64] MSG_ENG1D53_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [65] MSG_ENG1D55_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [66] MSG_ENG1D56_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [67] MSG_ENG1D59_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [68] MSG_ENG1D60_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [69] MSG_ENG1S51_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [70] MSG_EPS1D50_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [71] MSG_FCM1C01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [72] MSG_FCM1S49_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [73] MSG_FCM1S76_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [74] MSG_FCM1S79_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [75] MSG_FCM1S90_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [76] MSG_FCM1S95_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [77] MSG_IDT1S07_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [78] MSG_IDT1S15_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [79] MSG_MET1S02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [80] MSG_MGC1F13_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [81] MSG_PDC1G01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [82] MSG_RCP1S03_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [83] MSG_RCP1S04_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [84] MSG_RCP1S05_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [85] MSG_RCP1S06_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [86] MSG_RSE1G20_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [87] MSG_RSE1G24_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [88] MSG_RSE1G25_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [89] MSG_RSE1G26_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [90] MSG_RSE1S02_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [91] MSG_VGR1D50_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [92] MSG_VSC1D51_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [93] MSG_VSC1G13_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [94] MSG_WIP1S01_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_BAT|BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_PBA|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [95] MSG_ZN11S08_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [96] MSG_ZN11S63_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [97] MSG_ZN11S64_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [98] MSG_ZN11S65_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [99] MSG_ZN11S66_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
         ,( BSW_COM_u4IPDUGROUP_NONE )
     }
    ,{    /* [100] MSG_ZN11S67_RXCH0 */
          ( BSW_COM_u4IPDUGROUP_ACC|BSW_COM_u4IPDUGROUP_IG|ComConf_SysStatusName_IGR )
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
    ,(BswU2)80U                                                                                                  /* [4] MSG_ACN1S03_RXCH0 */
    ,(BswU2)88U                                                                                                  /* [5] MSG_ACN1S15_RXCH0 */
    ,(BswU2)96U                                                                                                  /* [6] MSG_ACN1S25_RXCH0 */
    ,(BswU2)128U                                                                                                 /* [7] MSG_ACN1S29_RXCH0 */
    ,(BswU2)160U                                                                                                 /* [8] MSG_ADC1S27_RXCH0 */
    ,(BswU2)192U                                                                                                 /* [9] MSG_ADC1S30_RXCH0 */
    ,(BswU2)200U                                                                                                 /* [10] MSG_ADC1S31_RXCH0 */
    ,(BswU2)232U                                                                                                 /* [11] MSG_ADU1S03_RXCH0 */
    ,(BswU2)264U                                                                                                 /* [12] MSG_ADU1S05_RXCH0 */
    ,(BswU2)296U                                                                                                 /* [13] MSG_ADU1S06_RXCH0 */
    ,(BswU2)328U                                                                                                 /* [14] MSG_AVN1S95_RXCH0 */
    ,(BswU2)336U                                                                                                 /* [15] MSG_BAT1E45_RXCH0 */
    ,(BswU2)368U                                                                                                 /* [16] MSG_BAT1EDA_RXCH0 */
    ,(BswU2)376U                                                                                                 /* [17] MSG_BAT1S08_RXCH0 */
    ,(BswU2)384U                                                                                                 /* [18] MSG_BAT2ED2_RXCH0 */
    ,(BswU2)392U                                                                                                 /* [19] MSG_BDB1F03_RXCH0 */
    ,(BswU2)400U                                                                                                 /* [20] MSG_BDB1S10_RXCH0 */
    ,(BswU2)408U                                                                                                 /* [21] MSG_BDC1S41_RXCH0 */
    ,(BswU2)440U                                                                                                 /* [22] MSG_BDC1S81_RXCH0 */
    ,(BswU2)472U                                                                                                 /* [23] MSG_BDC1S82_RXCH0 */
    ,(BswU2)504U                                                                                                 /* [24] MSG_BDC1S91_RXCH0 */
    ,(BswU2)536U                                                                                                 /* [25] MSG_BDC1SH8_RXCH0 */
    ,(BswU2)544U                                                                                                 /* [26] MSG_BDC1SI1_RXCH0 */
    ,(BswU2)608U                                                                                                 /* [27] MSG_BDC1SI2_RXCH0 */
    ,(BswU2)672U                                                                                                 /* [28] MSG_BDC1SI3_RXCH0 */
    ,(BswU2)736U                                                                                                 /* [29] MSG_BDC1SI4_RXCH0 */
    ,(BswU2)800U                                                                                                 /* [30] MSG_BDC1SI5_RXCH0 */
    ,(BswU2)864U                                                                                                 /* [31] MSG_BDC1SI6_RXCH0 */
    ,(BswU2)928U                                                                                                 /* [32] MSG_BDC1SI7_RXCH0 */
    ,(BswU2)992U                                                                                                 /* [33] MSG_BDC1SI8_RXCH0 */
    ,(BswU2)1056U                                                                                                /* [34] MSG_BDC1SI9_RXCH0 */
    ,(BswU2)1120U                                                                                                /* [35] MSG_BDC1SJ0_RXCH0 */
    ,(BswU2)1184U                                                                                                /* [36] MSG_BDC1SJ1_RXCH0 */
    ,(BswU2)1248U                                                                                                /* [37] MSG_BDC1SJ2_RXCH0 */
    ,(BswU2)1312U                                                                                                /* [38] MSG_BDF3S01_RXCH0 */
    ,(BswU2)1344U                                                                                                /* [39] MSG_BDF3S02_RXCH0 */
    ,(BswU2)1376U                                                                                                /* [40] MSG_BDR3S02_RXCH0 */
    ,(BswU2)1408U                                                                                                /* [41] MSG_CDC1S04_RXCH0 */
    ,(BswU2)1416U                                                                                                /* [42] MSG_CMB1S03_RXCH0 */
    ,(BswU2)1424U                                                                                                /* [43] MSG_CMB1S04_RXCH0 */
    ,(BswU2)1432U                                                                                                /* [44] MSG_DCM1S08_RXCH0 */
    ,(BswU2)1440U                                                                                                /* [45] MSG_DDM1S00_RXCH0 */
    ,(BswU2)1448U                                                                                                /* [46] MSG_DDM1S09_RXCH0 */
    ,(BswU2)1456U                                                                                                /* [47] MSG_DDM1S16_RXCH0 */
    ,(BswU2)1488U                                                                                                /* [48] MSG_DDM1S35_RXCH0 */
    ,(BswU2)1520U                                                                                                /* [49] MSG_DDM1SFH_RXCH0 */
    ,(BswU2)1552U                                                                                                /* [50] MSG_DKY1S26_RXCH0 */
    ,(BswU2)1560U                                                                                                /* [51] MSG_DS11S27_RXCH0 */
    ,(BswU2)1568U                                                                                                /* [52] MSG_EBU1D01_RXCH0 */
    ,(BswU2)1600U                                                                                                /* [53] MSG_ECT1S93_RXCH0 */
    ,(BswU2)1608U                                                                                                /* [54] MSG_EHV1E96_RXCH0 */
    ,(BswU2)1640U                                                                                                /* [55] MSG_EHV1F02_RXCH0 */
    ,(BswU2)1648U                                                                                                /* [56] MSG_EHV1S23_RXCH0 */
    ,(BswU2)1656U                                                                                                /* [57] MSG_EHV2G10_RXCH0 */
    ,(BswU2)1688U                                                                                                /* [58] MSG_EHV2G20_RXCH0 */
    ,(BswU2)1720U                                                                                                /* [59] MSG_EIM1S01_RXCH0 */
    ,(BswU2)1728U                                                                                                /* [60] MSG_ENG1C01_RXCH0 */
    ,(BswU2)1736U                                                                                                /* [61] MSG_ENG1C02_RXCH0 */
    ,(BswU2)1744U                                                                                                /* [62] MSG_ENG1D51_RXCH0 */
    ,(BswU2)1752U                                                                                                /* [63] MSG_ENG1D52_RXCH0 */
    ,(BswU2)1760U                                                                                                /* [64] MSG_ENG1D53_RXCH0 */
    ,(BswU2)1768U                                                                                                /* [65] MSG_ENG1D55_RXCH0 */
    ,(BswU2)1776U                                                                                                /* [66] MSG_ENG1D56_RXCH0 */
    ,(BswU2)1784U                                                                                                /* [67] MSG_ENG1D59_RXCH0 */
    ,(BswU2)1792U                                                                                                /* [68] MSG_ENG1D60_RXCH0 */
    ,(BswU2)1800U                                                                                                /* [69] MSG_ENG1S51_RXCH0 */
    ,(BswU2)1832U                                                                                                /* [70] MSG_EPS1D50_RXCH0 */
    ,(BswU2)1840U                                                                                                /* [71] MSG_FCM1C01_RXCH0 */
    ,(BswU2)1848U                                                                                                /* [72] MSG_FCM1S49_RXCH0 */
    ,(BswU2)1880U                                                                                                /* [73] MSG_FCM1S76_RXCH0 */
    ,(BswU2)1888U                                                                                                /* [74] MSG_FCM1S79_RXCH0 */
    ,(BswU2)1896U                                                                                                /* [75] MSG_FCM1S90_RXCH0 */
    ,(BswU2)1928U                                                                                                /* [76] MSG_FCM1S95_RXCH0 */
    ,(BswU2)1992U                                                                                                /* [77] MSG_IDT1S07_RXCH0 */
    ,(BswU2)2000U                                                                                                /* [78] MSG_IDT1S15_RXCH0 */
    ,(BswU2)2008U                                                                                                /* [79] MSG_MET1S02_RXCH0 */
    ,(BswU2)2016U                                                                                                /* [80] MSG_MGC1F13_RXCH0 */
    ,(BswU2)2048U                                                                                                /* [81] MSG_PDC1G01_RXCH0 */
    ,(BswU2)2056U                                                                                                /* [82] MSG_RCP1S03_RXCH0 */
    ,(BswU2)2064U                                                                                                /* [83] MSG_RCP1S04_RXCH0 */
    ,(BswU2)2096U                                                                                                /* [84] MSG_RCP1S05_RXCH0 */
    ,(BswU2)2160U                                                                                                /* [85] MSG_RCP1S06_RXCH0 */
    ,(BswU2)2224U                                                                                                /* [86] MSG_RSE1G20_RXCH0 */
    ,(BswU2)2232U                                                                                                /* [87] MSG_RSE1G24_RXCH0 */
    ,(BswU2)2240U                                                                                                /* [88] MSG_RSE1G25_RXCH0 */
    ,(BswU2)2248U                                                                                                /* [89] MSG_RSE1G26_RXCH0 */
    ,(BswU2)2256U                                                                                                /* [90] MSG_RSE1S02_RXCH0 */
    ,(BswU2)2264U                                                                                                /* [91] MSG_VGR1D50_RXCH0 */
    ,(BswU2)2296U                                                                                                /* [92] MSG_VSC1D51_RXCH0 */
    ,(BswU2)2328U                                                                                                /* [93] MSG_VSC1G13_RXCH0 */
    ,(BswU2)2360U                                                                                                /* [94] MSG_WIP1S01_RXCH0 */
    ,(BswU2)2368U                                                                                                /* [95] MSG_ZN11S08_RXCH0 */
    ,(BswU2)2376U                                                                                                /* [96] MSG_ZN11S63_RXCH0 */
    ,(BswU2)2408U                                                                                                /* [97] MSG_ZN11S64_RXCH0 */
    ,(BswU2)2440U                                                                                                /* [98] MSG_ZN11S65_RXCH0 */
    ,(BswU2)2472U                                                                                                /* [99] MSG_ZN11S66_RXCH0 */
    ,(BswU2)2504U                                                                                                /* [100] MSG_ZN11S67_RXCH0 */
};

#if( BSW_COM_CFG_METADATA_USE == BSW_USE )
BswConst BswU1 bsw_com_u1MetaDataSizeTbl[BSW_COM_MSG_NUM] = {
};
#endif /* BSW_COM_CFG_METADATA_USE == BSW_USE */

BswConst Bsw_Com_NetInfoType bsw_com_stNetInfoTxMsgTbl[BSW_COM_NETWORK_NUM] = {
     { (BswU2)0U,   (BswU2)0U   }                                                                                /* [0] CH0  */
};

BswConst Bsw_Com_NetInfoType bsw_com_stNetInfoRxMsgTbl[BSW_COM_NETWORK_NUM] = {
     { (BswU2)0U,   (BswU2)101U }                                                                                /* [0] CH0 CDC_VCAN_BUS */
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
    ,BSW_COM_u2MILSEC(0U)                                                       /* [14] MSG_AVN1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [15] MSG_BAT1E45_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [16] MSG_BAT1EDA_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [17] MSG_BAT1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [18] MSG_BAT2ED2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [19] MSG_BDB1F03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [20] MSG_BDB1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [21] MSG_BDC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [22] MSG_BDC1S81_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [23] MSG_BDC1S82_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [24] MSG_BDC1S91_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [25] MSG_BDC1SH8_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [26] MSG_BDC1SI1_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [27] MSG_BDC1SI2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [28] MSG_BDC1SI3_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [29] MSG_BDC1SI4_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [30] MSG_BDC1SI5_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [31] MSG_BDC1SI6_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [32] MSG_BDC1SI7_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [33] MSG_BDC1SI8_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [34] MSG_BDC1SI9_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [35] MSG_BDC1SJ0_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [36] MSG_BDC1SJ1_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [37] MSG_BDC1SJ2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [38] MSG_BDF3S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [39] MSG_BDF3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [40] MSG_BDR3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [41] MSG_CDC1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [42] MSG_CMB1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [43] MSG_CMB1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [44] MSG_DCM1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [45] MSG_DDM1S00_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [46] MSG_DDM1S09_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [47] MSG_DDM1S16_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [48] MSG_DDM1S35_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [49] MSG_DDM1SFH_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [50] MSG_DKY1S26_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [51] MSG_DS11S27_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [52] MSG_EBU1D01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [53] MSG_ECT1S93_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [54] MSG_EHV1E96_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [55] MSG_EHV1F02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [56] MSG_EHV1S23_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [57] MSG_EHV2G10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [58] MSG_EHV2G20_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [59] MSG_EIM1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [60] MSG_ENG1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [61] MSG_ENG1C02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [62] MSG_ENG1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [63] MSG_ENG1D52_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [64] MSG_ENG1D53_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [65] MSG_ENG1D55_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [66] MSG_ENG1D56_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [67] MSG_ENG1D59_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [68] MSG_ENG1D60_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [69] MSG_ENG1S51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [70] MSG_EPS1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [71] MSG_FCM1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [72] MSG_FCM1S49_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [73] MSG_FCM1S76_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [74] MSG_FCM1S79_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [75] MSG_FCM1S90_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [76] MSG_FCM1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [77] MSG_IDT1S07_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [78] MSG_IDT1S15_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [79] MSG_MET1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [80] MSG_MGC1F13_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [81] MSG_PDC1G01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [82] MSG_RCP1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [83] MSG_RCP1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [84] MSG_RCP1S05_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [85] MSG_RCP1S06_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [86] MSG_RSE1G20_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [87] MSG_RSE1G24_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [88] MSG_RSE1G25_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [89] MSG_RSE1G26_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [90] MSG_RSE1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [91] MSG_VGR1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [92] MSG_VSC1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [93] MSG_VSC1G13_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [94] MSG_WIP1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [95] MSG_ZN11S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [96] MSG_ZN11S63_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [97] MSG_ZN11S64_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [98] MSG_ZN11S65_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [99] MSG_ZN11S66_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [100] MSG_ZN11S67_RXCH0 */
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
    ,BSW_COM_u2MILSEC(0U)                                                       /* [14] MSG_AVN1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [15] MSG_BAT1E45_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [16] MSG_BAT1EDA_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [17] MSG_BAT1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [18] MSG_BAT2ED2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [19] MSG_BDB1F03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [20] MSG_BDB1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [21] MSG_BDC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [22] MSG_BDC1S81_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [23] MSG_BDC1S82_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [24] MSG_BDC1S91_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [25] MSG_BDC1SH8_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [26] MSG_BDC1SI1_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [27] MSG_BDC1SI2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [28] MSG_BDC1SI3_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [29] MSG_BDC1SI4_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [30] MSG_BDC1SI5_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [31] MSG_BDC1SI6_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [32] MSG_BDC1SI7_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [33] MSG_BDC1SI8_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [34] MSG_BDC1SI9_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [35] MSG_BDC1SJ0_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [36] MSG_BDC1SJ1_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [37] MSG_BDC1SJ2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [38] MSG_BDF3S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [39] MSG_BDF3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [40] MSG_BDR3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [41] MSG_CDC1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [42] MSG_CMB1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [43] MSG_CMB1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [44] MSG_DCM1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [45] MSG_DDM1S00_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [46] MSG_DDM1S09_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [47] MSG_DDM1S16_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [48] MSG_DDM1S35_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [49] MSG_DDM1SFH_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [50] MSG_DKY1S26_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [51] MSG_DS11S27_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [52] MSG_EBU1D01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [53] MSG_ECT1S93_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [54] MSG_EHV1E96_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [55] MSG_EHV1F02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [56] MSG_EHV1S23_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [57] MSG_EHV2G10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [58] MSG_EHV2G20_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [59] MSG_EIM1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [60] MSG_ENG1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [61] MSG_ENG1C02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [62] MSG_ENG1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [63] MSG_ENG1D52_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [64] MSG_ENG1D53_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [65] MSG_ENG1D55_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [66] MSG_ENG1D56_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [67] MSG_ENG1D59_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [68] MSG_ENG1D60_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [69] MSG_ENG1S51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [70] MSG_EPS1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [71] MSG_FCM1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [72] MSG_FCM1S49_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [73] MSG_FCM1S76_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [74] MSG_FCM1S79_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [75] MSG_FCM1S90_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [76] MSG_FCM1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [77] MSG_IDT1S07_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [78] MSG_IDT1S15_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [79] MSG_MET1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [80] MSG_MGC1F13_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [81] MSG_PDC1G01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [82] MSG_RCP1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [83] MSG_RCP1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [84] MSG_RCP1S05_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [85] MSG_RCP1S06_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [86] MSG_RSE1G20_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [87] MSG_RSE1G24_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [88] MSG_RSE1G25_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [89] MSG_RSE1G26_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [90] MSG_RSE1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [91] MSG_VGR1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [92] MSG_VSC1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [93] MSG_VSC1G13_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [94] MSG_WIP1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [95] MSG_ZN11S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [96] MSG_ZN11S63_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [97] MSG_ZN11S64_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [98] MSG_ZN11S65_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [99] MSG_ZN11S66_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [100] MSG_ZN11S67_RXCH0 */
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
     {    /* [0] MSG_ABG1D50_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [1] MSG_ABG1D51_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [2] MSG_ABG1S09_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [3] MSG_ACN1D50_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [4] MSG_ACN1S03_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [5] MSG_ACN1S15_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [6] MSG_ACN1S25_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [7] MSG_ACN1S29_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [8] MSG_ADC1S27_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [9] MSG_ADC1S30_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_43 )
     }
    ,{    /* [10] MSG_ADC1S31_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_43 )
     }
    ,{    /* [11] MSG_ADU1S03_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [12] MSG_ADU1S05_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [13] MSG_ADU1S06_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [14] MSG_AVN1S95_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 | BSW_COM_u4IPDUGRP_PNC_43 | BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [15] MSG_BAT1E45_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [16] MSG_BAT1EDA_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [17] MSG_BAT1S08_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [18] MSG_BAT2ED2_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [19] MSG_BDB1F03_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [20] MSG_BDB1S10_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [21] MSG_BDC1S41_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [22] MSG_BDC1S81_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [23] MSG_BDC1S82_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [24] MSG_BDC1S91_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [25] MSG_BDC1SH8_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [26] MSG_BDC1SI1_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [27] MSG_BDC1SI2_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [28] MSG_BDC1SI3_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [29] MSG_BDC1SI4_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [30] MSG_BDC1SI5_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [31] MSG_BDC1SI6_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [32] MSG_BDC1SI7_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [33] MSG_BDC1SI8_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [34] MSG_BDC1SI9_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [35] MSG_BDC1SJ0_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [36] MSG_BDC1SJ1_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [37] MSG_BDC1SJ2_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [38] MSG_BDF3S01_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [39] MSG_BDF3S02_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [40] MSG_BDR3S02_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [41] MSG_CDC1S04_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 | BSW_COM_u4IPDUGRP_PNC_43 | BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [42] MSG_CMB1S03_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [43] MSG_CMB1S04_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [44] MSG_DCM1S08_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [45] MSG_DDM1S00_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [46] MSG_DDM1S09_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [47] MSG_DDM1S16_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [48] MSG_DDM1S35_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [49] MSG_DDM1SFH_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [50] MSG_DKY1S26_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [51] MSG_DS11S27_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_43 )
     }
    ,{    /* [52] MSG_EBU1D01_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [53] MSG_ECT1S93_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [54] MSG_EHV1E96_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [55] MSG_EHV1F02_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [56] MSG_EHV1S23_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [57] MSG_EHV2G10_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [58] MSG_EHV2G20_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [59] MSG_EIM1S01_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [60] MSG_ENG1C01_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [61] MSG_ENG1C02_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [62] MSG_ENG1D51_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [63] MSG_ENG1D52_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [64] MSG_ENG1D53_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [65] MSG_ENG1D55_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [66] MSG_ENG1D56_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [67] MSG_ENG1D59_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [68] MSG_ENG1D60_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [69] MSG_ENG1S51_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [70] MSG_EPS1D50_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [71] MSG_FCM1C01_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [72] MSG_FCM1S49_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [73] MSG_FCM1S76_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [74] MSG_FCM1S79_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_43 )
     }
    ,{    /* [75] MSG_FCM1S90_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_43 )
     }
    ,{    /* [76] MSG_FCM1S95_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [77] MSG_IDT1S07_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [78] MSG_IDT1S15_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [79] MSG_MET1S02_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 | BSW_COM_u4IPDUGRP_PNC_43 | BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [80] MSG_MGC1F13_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [81] MSG_PDC1G01_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [82] MSG_RCP1S03_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_43 )
     }
    ,{    /* [83] MSG_RCP1S04_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [84] MSG_RCP1S05_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [85] MSG_RCP1S06_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [86] MSG_RSE1G20_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [87] MSG_RSE1G24_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [88] MSG_RSE1G25_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [89] MSG_RSE1G26_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [90] MSG_RSE1S02_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [91] MSG_VGR1D50_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [92] MSG_VSC1D51_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_NONE )
     }
    ,{    /* [93] MSG_VSC1G13_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_40 )
     }
    ,{    /* [94] MSG_WIP1S01_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [95] MSG_ZN11S08_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [96] MSG_ZN11S63_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [97] MSG_ZN11S64_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [98] MSG_ZN11S65_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [99] MSG_ZN11S66_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
    ,{    /* [100] MSG_ZN11S67_RXCH0 */
          ( BSW_COM_u4IPDUGRP_PNC_16 )
         ,( BSW_COM_u4IPDUGRP_PNC_44 )
     }
};

#if (BSW_COM_RX_MSG_NUM != 0U)
BswConst Bsw_Com_TickTimeType bsw_com_u2PnconMsk[BSW_COM_RX_MSG_NUM] = {

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
    ,BSW_COM_u2MILSEC(0U)                                                       /* [14] MSG_AVN1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [15] MSG_BAT1E45_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [16] MSG_BAT1EDA_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [17] MSG_BAT1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [18] MSG_BAT2ED2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [19] MSG_BDB1F03_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [20] MSG_BDB1S10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [21] MSG_BDC1S41_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [22] MSG_BDC1S81_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [23] MSG_BDC1S82_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [24] MSG_BDC1S91_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [25] MSG_BDC1SH8_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [26] MSG_BDC1SI1_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [27] MSG_BDC1SI2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [28] MSG_BDC1SI3_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [29] MSG_BDC1SI4_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [30] MSG_BDC1SI5_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [31] MSG_BDC1SI6_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [32] MSG_BDC1SI7_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [33] MSG_BDC1SI8_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [34] MSG_BDC1SI9_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [35] MSG_BDC1SJ0_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [36] MSG_BDC1SJ1_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [37] MSG_BDC1SJ2_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [38] MSG_BDF3S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [39] MSG_BDF3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [40] MSG_BDR3S02_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [41] MSG_CDC1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [42] MSG_CMB1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [43] MSG_CMB1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [44] MSG_DCM1S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [45] MSG_DDM1S00_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [46] MSG_DDM1S09_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [47] MSG_DDM1S16_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [48] MSG_DDM1S35_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [49] MSG_DDM1SFH_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [50] MSG_DKY1S26_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [51] MSG_DS11S27_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [52] MSG_EBU1D01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [53] MSG_ECT1S93_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [54] MSG_EHV1E96_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [55] MSG_EHV1F02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [56] MSG_EHV1S23_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [57] MSG_EHV2G10_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [58] MSG_EHV2G20_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [59] MSG_EIM1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [60] MSG_ENG1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [61] MSG_ENG1C02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [62] MSG_ENG1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [63] MSG_ENG1D52_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [64] MSG_ENG1D53_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [65] MSG_ENG1D55_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [66] MSG_ENG1D56_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [67] MSG_ENG1D59_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [68] MSG_ENG1D60_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [69] MSG_ENG1S51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [70] MSG_EPS1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [71] MSG_FCM1C01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [72] MSG_FCM1S49_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [73] MSG_FCM1S76_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [74] MSG_FCM1S79_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [75] MSG_FCM1S90_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [76] MSG_FCM1S95_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [77] MSG_IDT1S07_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [78] MSG_IDT1S15_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [79] MSG_MET1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [80] MSG_MGC1F13_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [81] MSG_PDC1G01_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [82] MSG_RCP1S03_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [83] MSG_RCP1S04_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [84] MSG_RCP1S05_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [85] MSG_RCP1S06_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [86] MSG_RSE1G20_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [87] MSG_RSE1G24_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [88] MSG_RSE1G25_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [89] MSG_RSE1G26_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [90] MSG_RSE1S02_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [91] MSG_VGR1D50_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [92] MSG_VSC1D51_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [93] MSG_VSC1G13_RXCH0 */
    ,BSW_COM_u2MILSEC(3000U)                                                    /* [94] MSG_WIP1S01_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [95] MSG_ZN11S08_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [96] MSG_ZN11S63_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [97] MSG_ZN11S64_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [98] MSG_ZN11S65_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [99] MSG_ZN11S66_RXCH0 */
    ,BSW_COM_u2MILSEC(0U)                                                       /* [100] MSG_ZN11S67_RXCH0 */
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
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
