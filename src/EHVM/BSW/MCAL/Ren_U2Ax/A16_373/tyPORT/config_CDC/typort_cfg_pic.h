/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : PORT Extension Interface For TOYOTA                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TYPORT_CFG_PIC_H
#define TYPORT_CFG_PIC_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYPORT_CFG_PIC_H_MAJOR                  (1)
#define TYPORT_CFG_PIC_H_MINOR                  (0)
#define TYPORT_CFG_PIC_H_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/**********************/
/* PIC Configuration  */
/**********************/
#define TYPORT_PIC1_UNIT_SELF     (0U)
#define TYPORT_PIC1_UNIT_OTHER    (BIT1)

#define TYPORT_PIC1_CH_SELF       (0U)
#define TYPORT_PIC1_CH_OTHER      (BIT0)

#define TYPORT_PIC1_TAUD(Group, Channel)  ((Group) + (Channel))

/* PIC1 Unit/Channel Configuration */
#define TYPORT_CFG_PIC1_TAUD0TTIN0		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN1		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN2		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN3		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN4		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN5		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN6		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN7		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN8		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN9		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN10		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN11		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN12		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN13		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN14		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD0TTIN15		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_OTHER))

#define TYPORT_CFG_PIC1_TAUD1TTIN0		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN1		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN2		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN3		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN4		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN5		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN6		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN7		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN8		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN9		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN10		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN11		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN12		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN13		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN14		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))
#define TYPORT_CFG_PIC1_TAUD1TTIN15		(TYPORT_PIC1_TAUD(TYPORT_PIC1_UNIT_SELF, TYPORT_PIC1_CH_SELF))

/* ------------------------------------------------------------------------------------*/
/* Attention :                                                                         */
/* ------------------------------------------------------------------------------------*/
/* Only TYPORT_PIC1_CH_SELF or TYPORT_PIC1_CH_OTHER should be selected in TAUD2        */
/* ------------------------------------------------------------------------------------*/
#define TYPORT_CFG_PIC1_TAUD2TTIN0		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN1		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN2		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN3		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN4		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN5		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN6		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN7		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN8		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN9		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN10		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN11		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN12		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN13		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN14		(TYPORT_PIC1_CH_SELF)
#define TYPORT_CFG_PIC1_TAUD2TTIN15		(TYPORT_PIC1_CH_SELF)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* TYPORT_CFG_PIC_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     5/ 9/2025  RY       New.                                                                                               */
/*                                                                                                                                   */
/*  * RY   = Ryosuke Yamada                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
