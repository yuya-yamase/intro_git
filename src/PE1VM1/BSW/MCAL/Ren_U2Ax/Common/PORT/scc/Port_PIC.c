/* Port-r04-303 */
/************************************************************************************************/
/*																								*/
/*		PORT Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Mcal_SpalCmn.h"
#include	"Std_Types.h"

#include	"Port_PIC.h"
#include	"Port_PIC_Cfg.h"
#include	"Reg_Pic1.h"

/*==============================================================================================*/
/* defines / data types / structs / unions / macros                                             */
/*==============================================================================================*/
/* PIC1	Unit/Channel Fix definition																*/
#define PORT_CFG_PIC1_PIC1TAUD0SEL      ( ( PORT_CFG_PIC1_TAUD0TTIN0  * BIT0  )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN1  * BIT2  )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN2  * BIT4  )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN3  * BIT6  )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN4  * BIT8  )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN5  * BIT10 )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN6  * BIT12 )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN7  * BIT14 )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN8  * BIT16 )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN9  * BIT18 )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN10 * BIT20 )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN11 * BIT22 )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN12 * BIT24 )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN13 * BIT26 )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN14 * BIT28 )         \
                                        + ( PORT_CFG_PIC1_TAUD0TTIN15 * BIT30 ) )

#define PORT_CFG_PIC1_PIC1TAUD1SEL      ( ( PORT_CFG_PIC1_TAUD1TTIN0  * BIT0  )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN1  * BIT2  )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN2  * BIT4  )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN3  * BIT6  )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN4  * BIT8  )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN5  * BIT10 )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN6  * BIT12 )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN7  * BIT14 )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN8  * BIT16 )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN9  * BIT18 )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN10 * BIT20 )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN11 * BIT22 )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN12 * BIT24 )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN13 * BIT26 )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN14 * BIT28 )         \
                                        + ( PORT_CFG_PIC1_TAUD1TTIN15 * BIT30 ) )

#define PORT_CFG_PIC1_PIC1TAUD2SEL      ( ( PORT_CFG_PIC1_TAUD2TTIN0  * BIT0  )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN1  * BIT1  )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN2  * BIT2  )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN3  * BIT3  )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN4  * BIT4  )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN5  * BIT5  )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN6  * BIT6  )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN7  * BIT7  )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN8  * BIT8  )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN9  * BIT9  )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN10 * BIT10 )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN11 * BIT11 )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN12 * BIT12 )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN13 * BIT13 )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN14 * BIT14 )         \
                                        + ( PORT_CFG_PIC1_TAUD2TTIN15 * BIT15 ) )

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#define PORT_START_SEC_CODE_GLOBAL
#include "Port_MemMap.h"

/************************************************************************************************/
/* Service name		:	Port_InitPic															*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	none																	*/
/* Return value		:	none																	*/
/* Limitation		:	Port_Initより後、Gpt_Initより前で呼び出すこと							*/
/************************************************************************************************/
FUNC(void, PORT_CODE) Port_InitPic( void )
{
    ((volatile Pic1_TAUDnSEL_Type*)PIC1_TAUD0SEL_ADR)->unTAUDnSEL.u4Data     = (U4)PORT_CFG_PIC1_PIC1TAUD0SEL; /* PIC1TAUD0SEL */
    ((volatile Pic1_TAUDnSEL_Type*)PIC1_TAUD1SEL_ADR)->unTAUDnSEL.u4Data     = (U4)PORT_CFG_PIC1_PIC1TAUD1SEL; /* PIC1TAUD1SEL */
    ((volatile Pic1_SelbTaud2I_Type*)PIC1_TAUD2SEL_ADR)->unSelbTaud2I.u2Data = (U2)PORT_CFG_PIC1_PIC1TAUD2SEL; /* PIC1SELB_TAUD2I */
}

#define PORT_STOP_SEC_CODE_GLOBAL
#include "Port_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
