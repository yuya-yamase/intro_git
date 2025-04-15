#ifndef EthSwt_SWIC_initRegListAcl_H
#define EthSwt_SWIC_initRegListAcl_H
/*===================================================================*/
/* インクルード宣言                                                  */
/*===================================================================*/
#include "EthSwt_SWIC_initRegCommon.h"
#define ETHSWT_START_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>

/*===================================================================*/
/* グローバル変数定義                                                */
/*===================================================================*/
#define g_regListAcl NULL_PTR

#define ETHSWT_STOP_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>
#endif
