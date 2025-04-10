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
      {0x1cu,0x16u,0x01u,0x01u,0x8000u,0x0000u},
};

#define ETHSWT_STOP_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>
#endif
