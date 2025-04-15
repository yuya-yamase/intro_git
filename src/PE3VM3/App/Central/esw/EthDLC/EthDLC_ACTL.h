/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_ACTL.h                                                */
/* -------------------------------------------------------------------------- */
#ifndef ETHDLC_ACTL_CFG_H_
#define ETHDLC_ACTL_CFG_H_
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <Dio_Symbols.h>
#include <Dio.h>
/* -------------------------------------------------------------------------- */
#define ETHDLC_GET_ACTL_SIGNAL  Dio_ReadChannel(DIO_ID_PORT10_CH14)

#define D_ACTL_ON_FILTER		(15U)       /* CPUクロック誤差考慮前 */
#define D_ACTL_OFF_FILTER		(205U)      /* CPUクロック誤差考慮前 */

void EthDLC_ACTL_Init(void);
void EthDLC_ACTL_Observe(void);
Std_ReturnType EthDLC_ACTL_GetPortSatus(void);
/* -------------------------------------------------------------------------- */
#endif/*ETHDLC_ACTL_CFG_H_*/
