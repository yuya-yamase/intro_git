/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name | Comtype/HEADER                                             */
/*----------------------------------------------------------------          */
/* Revision History                                                         */
/*   Revision    :Date       :Description                                   */
/*   v1_0_0      :2017/02/16 :New created                                   */
/*   v2_0_0      :2022/12/06 :Update                                        */
/*----------------------------------------------------------------          */
/* Notes                                                                    */
/****************************************************************************/

/* With this file, the following SWS numbers are non-applications. */
/* SWS_COMTYPE_00029 */
/* SWS_COMTYPE_00030 */

/* SWS_COMTYPE_00016 */
#ifndef COMSTACK_CFG_H   
#define COMSTACK_CFG_H

/* SWS_COMTYPE_00005 */
typedef uint16 PduIdType;
/* SWS_COMTYPE_00008 */
#if (REPROG_CFG_PDULENGTHTYPE_16 == STD_ON)
typedef uint16 PduLengthType;
#else
typedef uint8  PduLengthType;
#endif

#endif    /* COMSTACK_CFG_H */
