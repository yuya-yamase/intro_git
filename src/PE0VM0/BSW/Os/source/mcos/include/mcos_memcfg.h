/*
    Copyright (C) 2013 eSOL Co.,Ltd. Tokyo, Japan

    This software is protected by the law and the agreement concerning
    a Japanese country copyright method, an international agreement,
    and other intellectual property right and may be used and copied
    only in accordance with the terms of such license and with the inclusion
    of the above copyright notice.

    This software or any other copies thereof may not be provided
    or otherwise made available to any other person.  No title to
    and ownership of the software is hereby transferred.

    The information in this software is subject to change without
    notice and should not be construed as a commitment by eSOL Co.,Ltd.
*/
/****************************************************************************
[ mcos_memcfg.h ] - MCOS memory configuration header
****************************************************************************/
#ifndef MCOS_MEMCFG_H
#define MCOS_MEMCFG_H

#if !MCOS_AUTOSAR

#include "mcos_basic.h"

#define MEM_SELF                0

/* Virtual Memory Object */
#define MEM_TYPE_VIRTUAL        0x1
/* Real Memory Object  */
#define MEM_TYPE_REAL           0x0
/* Server  */
#define MEM_TYPE_SERVER         0x2
/* Core */
#define MEM_TYPE_CORE           0x0
/* enable to ask parent memory object */
#define MEM_ASK_ENABLE          0x4
/* Non-PMA */
#define MEM_ASK_DISABLE         0x0

#define MEM_TYPE_V_CORE         (MEM_TYPE_VIRTUAL | MEM_TYPE_CORE)
#define MEM_TYPE_V_SERVER       (MEM_TYPE_VIRTUAL | MEM_TYPE_SERVER)
#define MEM_TYPE_R_CORE         (MEM_TYPE_REAL | MEM_TYPE_CORE)
#define MEM_TYPE_R_SERVER       (MEM_TYPE_REAL | MEM_TYPE_SERVER)

/* memory object id mask */
#define MEM_LAYER_MASK          0xfff8

#define MEM_LAYER_SHIFT         3
#define MEM_ID_SHIFT            16

#define MEM_IDX2HEAPID(idx)     ((uint32_t)(idx) + (uint32_t)1)
#define MEM_RCIDX2HEAPID(rcidx)     MEM_IDX2HEAPID(rcidx)

#define MEM_HEAPID2IDX(heapid)     ((uint32_t)(heapid) - (uint32_t)1)

#define MOBJID(type, layer, idx)     \
    (((uint32_t)MEM_IDX2HEAPID(idx) << (uint32_t)MEM_ID_SHIFT) | ((uint32_t)(layer) << (uint32_t)MEM_LAYER_SHIFT) | (uint32_t)(type))
#define HEAPID(mobjid, pma)         ((uint32_t)(mobjid) | (uint32_t)(pma))
#define MEM_GET_MOBJID(heapid_impl) \
    ((heapid_impl) & (uint32_t)~MEM_ASK_ENABLE)
#define MEM_GET_HEAPID_IMPL(type, layer, heapid, pma)   \
    (((uint32_t)(heapid) << (uint32_t)MEM_ID_SHIFT) | ((uint32_t)(layer) << (uint32_t)MEM_LAYER_SHIFT) | (uint32_t)(type) | (uint32_t)(pma))

#define IMPL_MEMOBJ_CORE        MOBJID(MEM_TYPE_V_CORE, 0, MEM_HEAPID2IDX(MEM_SELF))
#define IMPL_MEMOBJ_CLUSTER     MOBJID(MEM_TYPE_V_SERVER, 1, MEM_HEAPID2IDX(MEM_SELF))
#define IMPL_MEMOBJ_GLOBAL      MOBJID(MEM_TYPE_V_SERVER, 2, MEM_HEAPID2IDX(MEM_SELF))

#define LV_MEMOBJ_CORE_LOCAL    0x0

#define TOTAL_LAYER_NUM(layerinfono)            (layerinfono)
#define CORE_LAYER_NUM(layerinfono)             ((uint32_t)(layerinfono) + (uint32_t)1)
#define NEAREST_CLUSTER(layerinfono)            ((uint32_t)(layerinfono) + (uint32_t)2)
#define MK_MEMOBJ_ID(layerinfono, layer)        ((uint32_t)(layerinfono) + (uint32_t)(layer) + (uint32_t)3)

typedef uint16_t mcos_memindex_t;
typedef mcos_memindex_t mcos_memsrver_t;

typedef struct
{
    void * addr;
    size_t size;
} mcos_memory_t;

typedef struct
{
    uint8_t memcnt;
    mcos_memindex_t index;
} mcos_meminfo_t;

typedef struct
{
    mcos_memindex_t meminfono;
    uint8_t layerinfono;
    uint8_t srvinfono;
} mcos_memmk_t;

typedef struct
{
     uint8_t tree;
     uint8_t id;
} mcos_memsrver_location_t;

typedef struct
{
     const char * name;
     mcos_memsrver_location_t location;
     mcos_id_t heapid;
     mcos_id_t rcidx;
} mcos_memsrver_info_t;

typedef struct
{
    mcos_id_t heapidmax;
    const mcos_memmk_t * memmk;
    const mcos_memsrver_t * const * memserver;
    const mcos_memindex_t * index;
    const mcos_memory_t * memory;
    const uint8_t * layerinfo;
    const mcos_meminfo_t * meminfo;
    const uint8_t * srvinfo;
} mcos_memcfg_t;

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const mcos_memcfg_t mcos_memcfg;

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const uint32_t mcos_heapid_table[];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

extern const mcos_memsrver_info_t mcos_heapsrv_info[];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

MCOS_INLINE mcos_bool_t memcfg_isValidHeapId(const mcos_id_t heapid);
MCOS_INLINE const mcos_memory_t * memcfg_getMemory(const mcos_meminfo_t * const meminfo, const uint8_t memnum);
MCOS_INLINE mcos_bool_t memcfg_hasNextMemory(const mcos_meminfo_t * const meminfo, const uint8_t memnum);
MCOS_INLINE uint32_t memcfg_getLayer(const uint32_t heapid_impl);
MCOS_INLINE mcos_bool_t memcfg_canAskParent(const uint32_t heapid_impl);
MCOS_INLINE mcos_id_t memcfg_getId(const uint32_t heapid_impl);
MCOS_INLINE mcos_bool_t memcfg_isVirtualMemoryObject(const uint32_t heapid_impl);
MCOS_INLINE mcos_bool_t memcfg_isServerRequest(const uint32_t heapid_impl);
MCOS_INLINE uint8_t memcfg_getCoreLayerNum(const mcos_id_t rcidx);
MCOS_INLINE uint8_t memcfg_getLayerNum(const mcos_id_t rcidx);
MCOS_INLINE uint8_t memcfg_getNearestClusterLMLayer(const mcos_id_t rcidx);
MCOS_INLINE uint8_t memcfg_getNearestGlobalMLayer (const mcos_id_t rcidx);
MCOS_INLINE const mcos_meminfo_t * memcfg_getCoreMemoryInfo(const mcos_id_t rcidx);
MCOS_INLINE const mcos_meminfo_t * memcfg_getCoreMemoryInfo_by_lcid(const mcos_id_t lcid);
MCOS_INLINE const mcos_meminfo_t * memcfg_getServerMemoryInfo(const mcos_id_t servno);
MCOS_INLINE uint8_t memcfg_getMemServerId(const mcos_id_t rcidx, uint8_t index);
MCOS_INLINE uint8_t memcfg_getMkMemobjId(const mcos_id_t rcidx, const uint8_t index);
MCOS_INLINE uint32_t memcfg_getHeapIdImpl(const mcos_id_t heapid);
MCOS_INLINE mcos_id_t memcfg_getServerHeapId(const mcos_id_t servno);
MCOS_INLINE const char * memcfg_getServerName(const int32_t i);
MCOS_INLINE mcos_id_t memcfg_getServerLcid(const int32_t i);


MCOS_INLINE mcos_bool_t memcfg_isValidHeapId (
    const mcos_id_t heapid)
{
    return (((int32_t)heapid > (int32_t)0) && ((int32_t)heapid <= (int32_t)mcos_memcfg.heapidmax)) ? mcos_true : mcos_false;
}

/* get memory */
MCOS_INLINE const mcos_memory_t * memcfg_getMemory (
    const mcos_meminfo_t * const meminfo,
    const uint8_t memnum)
{
    mcos_memindex_t index;

    index = mcos_memcfg.index[(uint32_t)meminfo->index + (uint32_t)memnum];
    return &mcos_memcfg.memory[index];
}

MCOS_INLINE mcos_bool_t memcfg_hasNextMemory (
    const mcos_meminfo_t * const meminfo,
    const uint8_t memnum)
{
    return (((uint32_t)memnum + (uint32_t)1) < (uint32_t)meminfo->memcnt)? mcos_true : mcos_false;
}

MCOS_INLINE uint32_t memcfg_getLayer (
    const uint32_t heapid_impl)
{
    return ((uint32_t)MEM_LAYER_MASK & (uint32_t)heapid_impl) >> (uint32_t)MEM_LAYER_SHIFT;
}

MCOS_INLINE mcos_bool_t memcfg_canAskParent (
    const uint32_t heapid_impl)
{
    return ((heapid_impl & (uint32_t)MEM_ASK_ENABLE) != (uint32_t)0) ? mcos_true : mcos_false;
}

MCOS_INLINE mcos_id_t memcfg_getId (
    const uint32_t heapid_impl)
{
    return (mcos_id_t)(heapid_impl >> (uint32_t)MEM_ID_SHIFT);
}

MCOS_INLINE mcos_bool_t memcfg_isVirtualMemoryObject (
    const uint32_t heapid_impl)
{
    return (heapid_impl & (uint32_t)MEM_TYPE_VIRTUAL) ? mcos_true : mcos_false;
}

MCOS_INLINE mcos_bool_t memcfg_isServerRequest (
    const uint32_t heapid_impl)
{
    return (heapid_impl & (uint32_t)MEM_TYPE_SERVER) ? mcos_true : mcos_false;
}

MCOS_INLINE uint8_t memcfg_getCoreLayerNum (
    const mcos_id_t rcidx)
{
    uint8_t layerinfono;

    layerinfono = mcos_memcfg.memmk[(uint32_t)rcidx].layerinfono;
    return mcos_memcfg.layerinfo[CORE_LAYER_NUM(layerinfono)];
}

MCOS_INLINE uint8_t memcfg_getLayerNum (
    const mcos_id_t rcidx)
{
    uint8_t layerinfono;

    layerinfono = mcos_memcfg.memmk[(uint32_t)rcidx].layerinfono;
    return mcos_memcfg.layerinfo[TOTAL_LAYER_NUM(layerinfono)];
}

MCOS_INLINE uint8_t memcfg_getNearestClusterLMLayer (
    const mcos_id_t rcidx)
{
    uint8_t layerinfono;

    layerinfono = mcos_memcfg.memmk[(uint32_t)rcidx].layerinfono;
    return mcos_memcfg.layerinfo[NEAREST_CLUSTER(layerinfono)];
}

/*
 * NOTE: The memory of the MOA_CLUSTER attribute is premised on that there is
 * only one layer.
 */
MCOS_INLINE uint8_t memcfg_getNearestGlobalMLayer (
    const mcos_id_t rcidx)
{
    uint8_t layerinfono;

    layerinfono = mcos_memcfg.memmk[(uint32_t)rcidx].layerinfono;
    return (uint8_t)((uint32_t)mcos_memcfg.layerinfo[NEAREST_CLUSTER(layerinfono)] + (uint32_t)1);
}

MCOS_INLINE const mcos_meminfo_t * memcfg_getCoreMemoryInfo (
    const mcos_id_t rcidx)
{
    return &mcos_memcfg.meminfo[mcos_memcfg.memmk[(uint32_t)rcidx].meminfono];
}

MCOS_INLINE const mcos_meminfo_t * memcfg_getCoreMemoryInfo_by_lcid (
    const mcos_id_t lcid)
{
    return memcfg_getCoreMemoryInfo((mcos_id_t)LCID2RCIDX(lcid));
}

MCOS_INLINE const mcos_meminfo_t * memcfg_getServerMemoryInfo (
    const mcos_id_t servno)
{
    const mcos_memsrver_t * memsrver;
    const mcos_memsrver_location_t * memsrver_info;

    memsrver_info = &mcos_heapsrv_info[servno].location;
    memsrver = mcos_memcfg.memserver[memsrver_info->tree];
    return &mcos_memcfg.meminfo[memsrver[memsrver_info->id]];
}

MCOS_INLINE uint8_t memcfg_getMemServerId (
    const mcos_id_t rcidx,
    uint8_t index)
{
    uint8_t srvinfono;

    index = (uint8_t)((uint32_t)index - (uint32_t)memcfg_getCoreLayerNum(rcidx));

    srvinfono = mcos_memcfg.memmk[(uint32_t)rcidx].srvinfono;
    return mcos_memcfg.srvinfo[(uint32_t)srvinfono + (uint32_t)index];
}

MCOS_INLINE uint8_t memcfg_getMkMemobjId (
    const mcos_id_t rcidx,
    const uint8_t index)
{
    uint8_t layerinfono;

    layerinfono = mcos_memcfg.memmk[(uint32_t)rcidx].layerinfono;
    return mcos_memcfg.layerinfo[MK_MEMOBJ_ID(layerinfono, index)];
}

MCOS_INLINE uint32_t memcfg_getHeapIdImpl (
    const mcos_id_t heapid)
{
    uint32_t heapid_impl;

    if ((int32_t)heapid <= (int32_t)MP_CONTROL_CORE_COUNT)
    {
        heapid_impl = MEM_GET_HEAPID_IMPL(MEM_TYPE_R_CORE, LV_MEMOBJ_CORE_LOCAL, heapid, MEM_ASK_DISABLE);
    }
    else
    {
        heapid_impl = mcos_heapid_table[(uint32_t)heapid - (uint32_t)MP_CONTROL_CORE_COUNT - (uint32_t)1];
    }

    return heapid_impl;
}

MCOS_INLINE mcos_id_t memcfg_getServerHeapId (
    const mcos_id_t servno)
{
    return mcos_heapsrv_info[(int32_t)servno].heapid;
}

/* Get server name */
MCOS_INLINE const char * memcfg_getServerName(
    const int32_t i)
{
    return mcos_heapsrv_info[i].name;
}

/* Get server lcid */
MCOS_INLINE mcos_id_t memcfg_getServerLcid(
    const int32_t i)
{
    return (mcos_id_t)MCOS_RCIDX2LCID(mcos_heapsrv_info[i].rcidx);
}

void mcos_memcfg_excludeUsedArea (
    const mcos_memory_t * pmemory,
    void * usedend,
    mcos_memory_t * memory);

/* is global memory */
mcos_bool_t mcos_memcfg_isGlobal (
    const void *addr,
    size_t size);

/* is core local memory */
mcos_bool_t mcos_memcfg_isLocal(
    mcos_id_t lcid,
    const void *addr,
    size_t size);

/* Is memory accessible_ */
mcos_bool_t mcos_memcfg_is_accessible(
    mcos_id_t lcid,
    const void *addr,
    size_t size);

#endif /* #if !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MEMCFG_H */
