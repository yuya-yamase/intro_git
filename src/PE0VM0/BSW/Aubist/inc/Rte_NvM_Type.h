/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

#ifndef RTE_NVM_TYPE_H
#define RTE_NVM_TYPE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Rte_Type.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
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
    
        
#ifndef NVM_INIT_READ_BLOCK
#define NVM_INIT_READ_BLOCK ((NvM_InitBlockRequestType)0x00U)
#endif /* NVM_INIT_READ_BLOCK */
        
#ifndef NVM_INIT_RESTORE_BLOCK_DEFAULTS
#define NVM_INIT_RESTORE_BLOCK_DEFAULTS ((NvM_InitBlockRequestType)0x01U)
#endif /* NVM_INIT_RESTORE_BLOCK_DEFAULTS */
        
#ifndef NVM_INIT_READ_ALL_BLOCK
#define NVM_INIT_READ_ALL_BLOCK ((NvM_InitBlockRequestType)0x02U)
#endif /* NVM_INIT_READ_ALL_BLOCK */
        
#ifndef NVM_INIT_FIRST_INIT_ALL
#define NVM_INIT_FIRST_INIT_ALL ((NvM_InitBlockRequestType)0x03U)
#endif /* NVM_INIT_FIRST_INIT_ALL */
    
        
#ifndef NVM_REQ_OK
#define NVM_REQ_OK ((NvM_RequestResultType)0x00U)
#endif /* NVM_REQ_OK */
        
#ifndef NVM_REQ_NOT_OK
#define NVM_REQ_NOT_OK ((NvM_RequestResultType)0x01U)
#endif /* NVM_REQ_NOT_OK */
        
#ifndef NVM_REQ_PENDING
#define NVM_REQ_PENDING ((NvM_RequestResultType)0x02U)
#endif /* NVM_REQ_PENDING */
        
#ifndef NVM_REQ_INTEGRITY_FAILED
#define NVM_REQ_INTEGRITY_FAILED ((NvM_RequestResultType)0x03U)
#endif /* NVM_REQ_INTEGRITY_FAILED */
        
#ifndef NVM_REQ_BLOCK_SKIPPED
#define NVM_REQ_BLOCK_SKIPPED ((NvM_RequestResultType)0x04U)
#endif /* NVM_REQ_BLOCK_SKIPPED */
        
#ifndef NVM_REQ_NV_INVALIDATED
#define NVM_REQ_NV_INVALIDATED ((NvM_RequestResultType)0x05U)
#endif /* NVM_REQ_NV_INVALIDATED */
        
#ifndef NVM_REQ_CANCELED
#define NVM_REQ_CANCELED ((NvM_RequestResultType)0x06U)
#endif /* NVM_REQ_CANCELED */
        
#ifndef NVM_REQ_RESTORED_FROM_ROM
#define NVM_REQ_RESTORED_FROM_ROM ((NvM_RequestResultType)0x08U)
#endif /* NVM_REQ_RESTORED_FROM_ROM */

#endif /* RTE_NVM_TYPE_H */
