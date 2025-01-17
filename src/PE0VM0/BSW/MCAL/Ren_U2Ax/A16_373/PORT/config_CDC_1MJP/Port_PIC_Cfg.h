/* Port-r04-303 */
/************************************************************************************************/
/*                                                                                              */
/*     PORT Driver                                                                              */
/*                                                                                              */
/*      Copyright : DENSO CORPORATION                                                           */
/*                                                                                              */
/************************************************************************************************/
#ifndef PORT_PIC_CONFIG_H
#define PORT_PIC_CONFIG_H

#include "Mcal_SpalCmn.h"
#include "Std_Types.h"

/*==============================================================================================*/
/* defines / data types / structs / unions / macros                                             */
/*==============================================================================================*/
#define PORT_PIC1_UNIT_SELF     (0U)
#define PORT_PIC1_UNIT_OTHER    (BIT1)

#define PORT_PIC1_CH_SELF       (0U)
#define PORT_PIC1_CH_OTHER      (BIT0)

#define PORT_PIC1_TAUD(Group, Channel)  ((Group) + (Channel))

/*==============================================================================================*/
/* PIC1	Unit/Channel Configuration																*/
/*==============================================================================================*/
#define PORT_CFG_PIC1_TAUD0TTIN0		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN1		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN2		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN3		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN4		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN5		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN6		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN7		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN8		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN9		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN10		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN11		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN12		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN13		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN14		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD0TTIN15		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_OTHER))

#define PORT_CFG_PIC1_TAUD1TTIN0		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN1		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN2		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN3		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN4		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN5		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN6		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN7		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN8		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN9		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN10		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN11		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN12		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN13		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN14		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))
#define PORT_CFG_PIC1_TAUD1TTIN15		(PORT_PIC1_TAUD( PORT_PIC1_UNIT_SELF, PORT_PIC1_CH_SELF ))

/* Caution: Only PORT_PIC1_CH_SELF or PORT_PIC1_CH_OTHER should be selected in TAUD2 */
#define PORT_CFG_PIC1_TAUD2TTIN0		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN1		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN2		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN3		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN4		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN5		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN6		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN7		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN8		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN9		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN10		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN11		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN12		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN13		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN14		(PORT_PIC1_CH_SELF)
#define PORT_CFG_PIC1_TAUD2TTIN15		(PORT_PIC1_CH_SELF)

#endif /* PORT_PIC_CONFIG_H */
/*-- End Of File -------------------------------------------------------------------------------*/
