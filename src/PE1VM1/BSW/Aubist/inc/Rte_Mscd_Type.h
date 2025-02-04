/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
#ifndef RTE_Mscd_TYPE_H
#define RTE_Mscd_TYPE_H

#include <Rte_Type.h>

#ifndef MSCD_MS_STATE_IDLE
#define MSCD_MS_STATE_IDLE ((Mscd_MsStatusType)15U)
#endif /* MSCD_MS_STATE_IDLE */
        
#ifndef MSCD_MS_STATE_BUSY
#define MSCD_MS_STATE_BUSY ((Mscd_MsStatusType)30U)
#endif /* MSCD_MS_STATE_BUSY */
        
#ifndef MSCD_MS_STATE_ERROR
#define MSCD_MS_STATE_ERROR ((Mscd_MsStatusType)240U)
#endif /* MSCD_MS_STATE_ERROR */
    
        
#ifndef NVM_READ_BLOCK
#define NVM_READ_BLOCK ((NvM_BlockRequestType)0x00U)
#endif /* NVM_READ_BLOCK */
        
#ifndef NVM_WRITE_BLOCK
#define NVM_WRITE_BLOCK ((NvM_BlockRequestType)0x01U)
#endif /* NVM_WRITE_BLOCK */
        
#ifndef NVM_RESTORE_BLOCK_DEFAULTS
#define NVM_RESTORE_BLOCK_DEFAULTS ((NvM_BlockRequestType)0x02U)
#endif /* NVM_RESTORE_BLOCK_DEFAULTS */
        
#ifndef NVM_ERASE_NV_BLOCK
#define NVM_ERASE_NV_BLOCK ((NvM_BlockRequestType)0x03U)
#endif /* NVM_ERASE_NV_BLOCK */
        
#ifndef NVM_INVALIDATE_NV_BLOCK
#define NVM_INVALIDATE_NV_BLOCK ((NvM_BlockRequestType)0x04U)
#endif /* NVM_INVALIDATE_NV_BLOCK */
        
#ifndef NVM_READ_ALL_BLOCK
#define NVM_READ_ALL_BLOCK ((NvM_BlockRequestType)0x05U)
#endif /* NVM_READ_ALL_BLOCK */
        
#ifndef NVM_WRITE_ALL_BLOCK
#define NVM_WRITE_ALL_BLOCK ((NvM_BlockRequestType)0x06U)
#endif /* NVM_WRITE_ALL_BLOCK */
    
        
#ifndef NVM_READ_ALL
#define NVM_READ_ALL ((NvM_MultiBlockRequestType)0x00U)
#endif /* NVM_READ_ALL */
        
#ifndef NVM_WRITE_ALL
#define NVM_WRITE_ALL ((NvM_MultiBlockRequestType)0x01U)
#endif /* NVM_WRITE_ALL */
        
#ifndef NVM_VALIDATE_ALL
#define NVM_VALIDATE_ALL ((NvM_MultiBlockRequestType)0x02U)
#endif /* NVM_VALIDATE_ALL */
        
#ifndef NVM_FIRST_INIT_ALL
#define NVM_FIRST_INIT_ALL ((NvM_MultiBlockRequestType)0x03U)
#endif /* NVM_FIRST_INIT_ALL */
        
#ifndef NVM_CANCEL_WRITE_ALL
#define NVM_CANCEL_WRITE_ALL ((NvM_MultiBlockRequestType)0x04U)
#endif /* NVM_CANCEL_WRITE_ALL */

#endif /* RTE_Mscd_TYPE_H */
