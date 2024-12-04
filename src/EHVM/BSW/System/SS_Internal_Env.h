/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Internal_Env.h
 * [Module]			MCU Information
 * [Function]		Provide MCU information
 * [Notes]			for RH850F1KM
 ****************************************************************************/

#ifndef SS_INTERNAL_ENV_H
#define SS_INTERNAL_ENV_H

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
/* HardSleepTimer */

/* RegSleepTimeのLSB */
#define SS_u4HSTM_REGSLEEP_SRCCLK (6UL)
#define SS_u4HSTM_REGSLEEP_DIV    (25UL)

/* HST's pre-scaller division sets PCLK/2^0 */
#define SS_u2HSTM_PRS_DIV (0x0000U) /* TAUJnPRSm設定値 */
#define SS_u4HSTM_DIV_NUM (1UL)     /* 上記が数値で何分周にあたるか */

/* HST's pre-scaller */
#define SS_HSTM_PRS_CK0 (0)
#define SS_HSTM_PRS_CK1 (1)
#define SS_HSTM_PRS_CK2 (2)

#define SS_HSTM_PRS (SS_HSTM_PRS_CK1)

/* HST's timer channel */
#define SS_HSTM_TAUJ_CH1 (1)
#define SS_HSTM_TAUJ_CH2 (2)

#define SS_HSTM_TAUJ_CH (SS_HSTM_TAUJ_CH1)

/* for RamTest */
#define SS_USE_ADDRBUSCHECK (STD_OFF) /* Use Address bus check */

/* for RomTest */
#define SS_USE_ROMBUFFCHECK (STD_OFF) /* Use ROM buffer check */

/* for SleepTm */
#define SS_u4REGSLEEPTIME_MIN (1000UL) /* RegSleepTime min */

/* Stack Addres */
#define SS_u4STACKADDR_0 (__ghsbegin_ss_stack)
#define SS_u4STACKADDR_1 (__ghsbegin_ss_stack1)
#define SS_u4STACKADDR_2 (__ghsbegin_ss_stack2)
#define SS_u4STACKADDR_3 (__ghsbegin_ss_stack3)

/* RTE */
#define SS_CALL_RTESTART (STD_OFF) /* ON just for EcuM-Fixed and RTE combination */

#endif /* SS_INTERNAL_ENV_H */
