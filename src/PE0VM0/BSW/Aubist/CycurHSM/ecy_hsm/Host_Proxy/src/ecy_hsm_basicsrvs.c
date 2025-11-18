/**
 * @file
 ***********************************************************************************************
 * @brief HOST and HSM side implementation of standard library functions.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2015, all rights reserved
 **********************************************************************************************/

#if defined(GUAM)
#include "ecy_hsm_general.h"
#if (BUILDING == HOST_BUILD)
#include "ecy_hsm_basicsrvs.h"
#else
#include "basicsrvs.h"
#endif /* #if (BUILDING == HOST_BUILD) */
#else
#include "ecy_hsm_general_pubcfg.h"
#include "ecy_hsm_basicsrvs.h"
#endif

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* PRQA S 4603 1 */ /* <Deviation: rule_21.2_4603_4604 */
void *ecy_memcpy(void* s1, const void* s2, uint32 n)
{
    void* dest = s1;

    /* PRQA S 0303, 306 2 */ /* <Deviation: rule_11.6_303_306 */
    while(!ARE_POINTERS_ALIGNED(s1, s2, uint32) && (n > 0UL))
    {
        n--;
         /* PRQA S 3440,3387 4 */ /* <Justification: Using the result from a ++ operation is safe here. This will not affect
         the functionality.*/
         /* PRQA S 0316 2 */ /* <Justification: Unavoidable cast of void pointer to char* or const char*. This will not
         affect the functionality.*/
        COPY_1_ELEMENT(s1, s2, uint8);
    }

    while(n >= sizeof(uint32))
    {
        n -= sizeof(uint32);
        /* PRQA S 3440,3387 4 */ /* <Justification: Using the result from a ++ operation is safe here. This will not affect
        the functionality.*/
        /* PRQA S 0316 2 */ /* <Justification: Unavoidable cast of void pointer to char* or const char*. This will not
                affect the functionality.*/
        COPY_1_ELEMENT(s1, s2, uint32);
    }

    while(n >= sizeof(uint8))
    {
        n--;
         /* PRQA S 3440,3387 4 */ /* <Justification: Using the result from a ++ operation is safe here. This will not affect
         the functionality.*/
         /* PRQA S 0316 2 */ /* <Justification: Unavoidable cast of void pointer to char* or const char*. This will not
         affect the functionality.*/
        COPY_1_ELEMENT(s1, s2, uint8);
    }

    return (dest);
}

/* PRQA S 4603 2 */ /* <Deviation: rule_21.2_4603_4604 */
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1 */
void *ecy_memset(void* s, uint8 c, uint32 n)
{
    uint32 full_value = (uint32) c | ((uint32) c << 8U) | ((uint32) c << 16U) | ((uint32) c << 24U);
    volatile void* dest = s;

    /* PRQA S 0303 2 */ /* <Justification: The casting from  pointer to integer is needed and intended at this alignment
    check*/
    while(!IS_POINTER_ALIGNED(dest, uint32) && (n > 0UL))
    {
        n--;
        /* PRQA S 0316 2 */ /* <Justification: Unavoidable cast of void pointer to char* or const char*. This will not
        affect the functionality.*/
        SET_1_ELEMENT(dest, c, uint8);
    }

    while(n >= sizeof(uint32))
    {
        n -= sizeof(uint32);
        /* PRQA S 0316 1 */ /* <Deviation: Unavoidable cast of void pointer to char* or const char*. This will not affect the functionality.*/
        SET_1_ELEMENT(dest, full_value, uint32);
    }

    while(n >= sizeof(uint8))
    {
        n--;
        /* PRQA S 0316 2 */ /* <Justification: Unavoidable cast of void pointer to char* or const char*. This will not
        affect the functionality.*/
        SET_1_ELEMENT(dest, c, uint8);
    }
    return s;
}

/* PRQA S 4603 2 */ /* <Deviation: rule_21.2_4603_4604 */
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1 */
sint32 ecy_memcmp(const void* s1, const void* s2, uint32 n)
{
    sint32 ret = 0;
    /* PRQA S 0316 3 */ /* <Justification: Unavoidable cast of void pointer to char* or const char*. This will not
    affect the functionality.*/
    const uint8* tx = (const uint8*) s1;
    const uint8* ty = (const uint8*) s2;

    while(n > 0u)
    {
        ret = (sint32) *tx - (sint32) *ty;
        if(0 != ret)
        {
            break;
        }
        tx++;
        ty++;
        n--;
    }
    return ret;
}

/* PRQA S 4603 2 */ /* <Deviation: rule_21.2_4603_4604 */
/* PRQA S 1503 1 */ /* <Deviation: rule_2.1 */
void *ecy_memmove(void *s1, const void *s2, uint32 n)
{
/* PRQA S 0316 5 */ /*Unavoidable pointer indexing. This will not affect the intended functionality.*/
    uint8* tx = (uint8*)s1;
/* PRQA S 0316 5 */ /*Unavoidable pointer indexing. This will not affect the intended functionality.*/
    const uint8* ty = (const uint8*)s2;

    /* if regions overlap and moving to the right, begin copying from end */
    /* PRQA S 0488 2 */ /* Justification: pointer arithmetic is required and safe here */
    if ((ty < tx) && (tx < (ty + n)))
    {
        /* PRQA S 0488 2 */ /* Justification: pointer arithmetic is required and safe here */
        ty += n;
        tx += n;
        while (n>0u)
        {
           tx--;
           ty--;
           *tx = *ty;
            n--;
        }
    }
    else
    {
        while (n>0u)
        {
            *tx = *ty;
            tx++;
            ty++;
            n--;
        }
    }
    return s1;
}

/* PRQA S 1503 2 */ /* Justification: The function is used in tests */
sint32 ecy_strcmp(const char* pString1, const char* pString2)
{
    uint32 idx = 0U;

    while ((pString1[idx] != '\0') && (pString1[idx] == pString2[idx]))
    {
        idx++;
    }

    return (sint32)(pString1[idx] - pString2[idx]);
}

#if defined(GUAM)
#if (BUILDING == HSM_BOOT_BUILD) || (BUILDING == HSM_CORE_BUILD)
uint32 ecy_memcmp_tc(const void* s1, const void* s2, uint32 n)
{
   /* PRQA S 0316 3 */ /* <Justification: Unavoidable cast of void pointer to char* or const char*. This will not affect
   the functionality.*/
    const uint8 *ip1 = (const uint8*) s1;
    const uint8 *ip2 = (const uint8*) s2;
    uint32 res = 0;

    for(; n >  0U; n--)
    {
        res  |= ((uint32)*ip1 ^(uint32) *ip2);
        ip1++;
        ip2++;
    }
    return res;
}

uint32 ecy_fetchUint32(uint8 const* pBuf)
{
    uint32 out;
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    out =  (((uint32)(pBuf[0])) << 0U);
    out |= (((uint32)(pBuf[1])) << 8U);
    out |= (((uint32)(pBuf[2])) << 16U);
    out |= (((uint32)(pBuf[3])) << 24U);
#else
    out =  (((uint32)(pBuf[0])) << 24U);
    out |= (((uint32)(pBuf[1])) << 16U);
    out |= (((uint32)(pBuf[2])) << 8U);
    out |= (((uint32)(pBuf[3])) << 0U);
#endif /* #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */
    return out;
}

uint16 ecy_fetchUint16(uint8 const* pBuf)
{
    uint16 out;
    uint32 temp;
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    temp = (((uint32)(pBuf[0])) << 0U);
    temp |= (((uint32)(pBuf[1])) << 8U);
#else
    temp = (((uint32)(pBuf[0])) << 8U);
    temp |= (((uint32)(pBuf[1])) << 0U);
#endif /* #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */
    out = (uint16)temp;
    return out;
}

/* Not testable via Cantata unit test */
#ifndef __CANTATA_TESTING__
/*
 * Needs to be aligned to a 4-byte boundary because its address is written
 * into CADDR4 during the test startup, and CADDR4 b1 is zero.
 * __attribute__ cannot be changed. This is used to make the memory allocation 4 byte aligned.
 */
NORETURN __attribute__((aligned(4))) void ecy_endless_loop(void)
{
    while(1)
    {
        /* Loop forever */
    }
}
#endif /* #ifndef __CANTATA_TESTING__ */
#endif
#endif /* defined(GUAM) */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
