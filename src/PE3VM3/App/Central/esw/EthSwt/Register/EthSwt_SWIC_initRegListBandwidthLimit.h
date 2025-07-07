#ifndef EthSwt_SWIC_initRegListBandwidthLimit_H
#define EthSwt_SWIC_initRegListBandwidthLimit_H
/*===================================================================*/
/* インクルード宣言                                                  */
/*===================================================================*/
#include "EthSwt_SWIC_initRegCommon.h"
#define ETHSWT_START_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>

/*===================================================================*/
/* グローバル変数定義                                                */
/*===================================================================*/
static const swic_reg_data_t  g_regListBandwidthLimit[] =  {
      {0x1c,0x16,0x01,0x01,0x8000,0x0000},
};

#define ETHSWT_STOP_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>
#endif
