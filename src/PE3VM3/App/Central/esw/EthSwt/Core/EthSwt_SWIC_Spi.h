/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Spi.h                                            */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_SPI_H
#define ETHSWT_SWIC_SPI_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthSwt_SWIC_initRegCommon.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Spi_Init(void);
void EthSwt_SWIC_Spi_ReqInit(void);
Std_ReturnType EthSwt_SWIC_Spi_Write(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx);
Std_ReturnType EthSwt_SWIC_Spi_WriteSPI(const swic_reg_data_t tbl[], const uint32 idx, const uint16 SndData);
Std_ReturnType EthSwt_SWIC_Spi_ReadSPI(const swic_reg_data_t tbl[], const uint32 idx, uint16 *const RcvData);
Std_ReturnType EthSwt_SWIC_Spi_Read(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint16 *const RcvData);
uint8 EthSwt_SWIC_Spi_GetSpiRegErr(void);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_SPI_H */
/* -------------------------------------------------------------------------- */
