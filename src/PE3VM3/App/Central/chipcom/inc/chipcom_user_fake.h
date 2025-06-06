/****************************************************************************/

#ifndef     CHIPCOM_USER_FAKE_H
#define     CHIPCOM_USER_FAKE_H

#include "Std_Types.h"
#include "chipcom.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define ETHERSWTFAKE_SIZE_MCUINFO		((U1)181U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void ChipComUserFake_Main( void );

#ifdef CHIPCOM_MCU_SETTING  /* MCU ChipCom */ /* See chipcom_config.h */
void CanIfProxy_Transmit(const uint16 rcvLen_CanIfTransmit, const uint8* const receive_data);
void CanIfProxy_CancelTransmit(const uint16 rcvLen_CanIfTransmit, const uint8* const receive_data);
void EthSwt_SWIC_Reg_RidClear(const uint16 rcvLen_CanIfTransmit, const uint8* const receive_data);
void Vis_TimeStsReq(const uint16 rcvLen_CanIfTransmit, const uint8* const receive_data);
#else   /* SAIL ChipCom */
void CanIfStub_TxConfiramtion(const uint16 rcvLen_CanIfTransmit, const uint8* const receive_data);
void CanIfStub_RxIndication(const uint16 rcvLen_CanIfTransmit, const uint8* const receive_data);
#endif


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#endif  /* ETHERSWT_FAKE_H */
/**** End of File ***********************************************************/
