/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]      ehvm_callout_ghs.h
 * [Module]         ehvm_callout
 * [Function]       Callouts for EHVM
 * [Notes]          
 ****************************************************************************/

#ifndef EHVM_CALLOUT_GHS_H
#define EHVM_CALLOUT_GHS_H

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/

/* Copied from "user_em_ghs.h" (AUBASS LWH) */
/*                  | | |                   */
/*                  V V V                   */

extern ehvm_uint32_t ehvm_em_cbk_getFEPC(void);
extern ehvm_uint32_t ehvm_em_cbk_getMEA(void);
extern ehvm_uint32_t ehvm_em_cbk_getMCR(void);
extern ehvm_uint32_t ehvm_em_cbk_getMCA(void);
extern ehvm_uint32_t ehvm_em_cbk_getMCS(void);
extern ehvm_uint32_t ehvm_em_cbk_getFEIC(void);
extern void ehvm_em_cbk_loop(void);

/*                  ^ ^ ^                   */
/*                  | | |                   */
/* Copied from "user_em_ghs.h" (AUBASS LWH) */

/* Copied from "user_hook_ghs.h" (AUBASS LWH) */
/*                    | | |                   */
/*                    V V V                   */

extern void user_wait_100us(void);

/*                    ^ ^ ^                   */
/*                    | | |                   */
/* Copied from "user_hook_ghs.h" (AUBASS LWH) */

/* Copied from "user_intm_ghs.h" (AUBASS LWH) */
/*                    | | |                   */
/*                    V V V                   */

extern void ehvm_intm_loop(void);

/*                    ^ ^ ^                   */
/*                    | | |                   */
/* Copied from "user_intm_ghs.h" (AUBASS LWH) */

/*----------------------------------------------------------------------------
 *      Codes
 *--------------------------------------------------------------------------*/


#endif /* EHVM_CALLOUT_GHS_H */
