/****************************************************************************************************************/
/*                                                                                                              */
/*      Csmユーザコールアウト関数                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#define CSM_CALLOUT_USER_C

#include "Csm_User.h"

FUNC( void, CSM_CODE ) CsmCallback_KeySetValid( uint32 jobId, Crypto_ResultType result )
{

}

FUNC( void, CSM_CODE ) CsmCallback_General( uint32 jobId, Crypto_ResultType result )
{

}

FUNC( void, CSM_CODE ) WrapCrypto_ErrorCallout( Csm_Ab_ErrorStatusType udErrorStatus )
{

}

FUNC( void, CSM_CODE ) WrapCrypto_TimeoutCallout( uint32 u4ChannelId )
{

}
