/**
 * @file
 ***********************************************************************************************
 * @brief HOST side implementation of standard library functions. The c file is in the
 * common folder. HSM and HOST have different header files because HSM side uses additional
 * functions.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_BASICSRVS_H
#define ECY_HSM_BASICSRVS_H

/* *** includes *******************************************************************************/

#include "Std_Types.h"

/* To avoid the Guam specific file includes*/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#endif /* #if defined(GUAM) */
/**
 * @brief Return number of bytes for a even bit length e.g. 32bit >> 3 = 4 full byte
 *
 * @param[in] _x    number of bits
 *
 */
#define ecy_hsm_BITS_TO_BYTES_LENGTH(_x)     (((uint32)(_x)) >> 3UL)

/**
 * @brief Return number of full bytes for a uneven bit length e.g. 27bit+7bit=34bit >> 3 = 4 full byte
 *
 * @param[in] _x    number of bits
 *
 * @note This implementation works on the full [0..2^32-1] uint32 range and won't overflow unlike the previous implementation
 */
#define ecy_hsm_BITS_TO_FULL_BYTE_LENGTH(_x) (((uint32)(_x) >> 3) + ((((uint32)(_x) & 7U) != 0U) ? 1U : 0U))

/**
 * @brief Return number of bits for a number of bytes e.g. 16 byte << 3 = 128 bits
 *
 * @note Due to the nature of shifting, this might overflow the 32 bit.
 *
 * @param[in] _x    number of bytes
 *
 */
#define ecy_hsm_BYTES_TO_BIT_LENGTH(_x)      (((uint32)(_x)) << 3UL)

/**
 * @brief Return minimum of two values.
 *
 * @param[in] a First value
 * @param[in] b Second value
 *
 * @note This macro will evaluate \a a or \a b
 * \b twice. Thus, \a a and \a b should be constants and
 * not expressions.
 */
#define ecy_hsm_MIN(a, b)                    (((a) < (b)) ? (a) : (b))

/**
 * @brief Return maximum of two values.
 *
 * @param[in] a First value
 * @param[in] b Second value
 *
 * @note This macro will evaluate \a a or \a b
 * \b twice. Thus, \a a and \a b should be constants and
 * not expressions.
 */
#define ecy_hsm_MAX(a, b)                    (((a) > (b)) ? (a) : (b))

/**
 * @brief Return true if pointer is aligned. False otherwise
 *
 * @param[in] _x    pointer
 * @param[in] _type data type
 *
 * @note pointer will be casted to uint32
 */
#define IS_POINTER_ALIGNED(_x, _type) \
    ( ((uint32)(_x) & (sizeof( _type)-1UL)) == 0U)

/**
 * @brief Return true if pointers are aligned.
 *
 * @param[in] _x    pointer
 * @param[in] _y    pointer
 * @param[in] _type data type
 *
 * @note  pointers will be casted to uint32
 */
#define ARE_POINTERS_ALIGNED(_x, _y, _type)    \
    (((((uint32)(_x)) | ((uint32)(_y))) & (sizeof(_type)-1UL)) == 0U)

/**
 * @brief Returns a pointer to destination in x from copied source element wise
 *
 * @param[out] x    pointer to destination
 * @param[in]  y    pointer to source
 * @param[in]  type data type
 */
#define COPY_1_ELEMENT(x, y, type)          \
{                                           \
    /* PRQA S 3410 5 */ /* <Deviation: rule_20.7_3410.*/ \
    type *xType = (type *)(x);              \
    const type * yType = (const type *)(y); \
    *xType++ = *yType++;                    \
    x = (void *)xType;                      \
    y = (const void *)yType;                \
}

/**
 * @brief Fills _x  with _a content of type _type element wise
 *
 * @param[out] _x    pointer to destination
 * @param[in]  _a    content to be filled
 * @param[in]  _type data type
 */
#define SET_1_ELEMENT(_x, _a, _type)        \
{                                           \
    /* PRQA S 3410 5 */ /* <Deviation: Expression enclosing parentheses omitted at left-hand
     *                                 side of assignment expression. This will not affect the functionality.*/ \
    volatile _type *xType = (volatile _type *)(_x);           \
    *xType = (_a);                          \
    xType++;                                \
    _x = (volatile void *)xType;            \
} /* end of define */

/**
 * @brief Maps the division of _x/_y to the least integer greater than or equal to _y.
 *
 * @param[out] _x    Dividend
 * @param[in]  _y    Divisor
 */
#define ecy_hsm_CEILING(_x, _y) (((_x) + (_y) - 1) / (_y))

/**
 * @brief Fills uint16 value to a uint8 array in big endian
 *
 * @param[out] _array    uint8 array
 * @param[in]  _value    uint16 value to set in the uint8 array
 */
#define CONVERT_UINT16_VALUE_TO_BIG_ENDIAN(_value, _array)          \
    do                                                              \
    {                                                               \
        /* PRQA S 3410 ++ */ /* <Deviation: rule_20.7_3410 */       \
        (_array)[0UL] = (uint8)((_value) >> 8UL);                   \
        (_array)[1UL] = (uint8)((_value));                          \
        /* PRQA S 3410 -- */                                        \
    }                                                               \
    while (0)

/**
 * @brief Fills uint32 value to a uint8 array in big endian
 *
 * @param[out] _array    uint8 array
 * @param[in]  _value    uint32 value to set in the uint8 array
 */
#define CONVERT_UINT32_VALUE_TO_BIG_ENDIAN(_value, _array)          \
    do                                                              \
    {                                                               \
        /* PRQA S 3410 ++ */ /* <Deviation: rule_20.7_3410 */       \
        (_array)[0UL] = (uint8)((_value) >> 24UL);                  \
        (_array)[1UL] = (uint8)((_value) >> 16UL);                  \
        (_array)[2UL] = (uint8)((_value) >> 8UL);                   \
        (_array)[3UL] = (uint8)((_value));                          \
        /* PRQA S 3410 -- */                                        \
    }                                                               \
    while (0)                                                                                               

/**
 * @brief Converts uint8 array in big endian into uint16.
 *
 * @param[in] _array    uint8 input array
 */
#define CONVERT_BIG_ENDIAN_TO_UINT16_VALUE(_array)  \
    (uint32)(((uint32)(_array)[0UL] << 8UL)         \
    | ((uint32)(_array)[1UL])) 

/**
 * @brief Converts uint8 array in big endian into uint32.
 *
 * @param[in] _array    uint8 input array
 */
#define CONVERT_BIG_ENDIAN_TO_UINT32_VALUE(_array)              \
    (uint32)(((uint32)(_array)[0UL] << 24UL)                    \
    | ((uint32)(_array)[1UL] << 16UL)                           \
    | ((uint32)(_array)[2UL] << 8UL)                            \
    | ((uint32)(_array)[3UL]))

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * @brief Implementation of ecy_memcpy copies the values of n bytes from the location pointed to
 * by s2 directly to the memory block pointed to by s1.
 *
 * @param[in] s1    start address of the destination memory block
 * @param[in] s2    start address of the source memory block
 * @param[in] n     length of the memory block
 * @return          Pointer to destination s1
 */
void *ecy_memcpy(void* s1, const void* s2, uint32 n);

/**
 * @brief Implementation of ecy_memset sets the first n bytes of the block of memory pointed by s to the
 * specified value c.

 * @details This will run from FLASH
 *
 * @param[out] s    Pointer to a memory block to set
 * @param[in]  c    Value to set each byte to
 * @param[in]  n    Number of bytes to set
 * @return          Pointer to destination s
 */
void *ecy_memset(void* s, uint8 c, uint32 n);

/**
 * @brief Implementation of ecy_memcmp compares two blocks of memory specified by s1 and s2.
 * The number of bytes to be compared is n.
 * @details This function will break in case the difference between pointers is not zero.
 *
 * @param[in] s1    Pointer to first memory block
 * @param[in] s2    Pointer to second memory block
 * @param[in] n     Number of bytes to compare
 * @return          Difference value resulting from pointers comparison

 */
sint32 ecy_memcmp(const void* s1, const void* s2, uint32 n);

/**
 * Implementation of memmove
 * @details copy first n bytes from s2 to s1. source and destination may overlap.
 *
 * @param[in] s1 Pointer to destination memory block
 * @param[in] s2 Pointer to source block
 * @param[in] n Number of bytes to move
 * @return    Pointer originally supplied in s
 */
void *ecy_memmove(void *s1, const void *s2, uint32 n);

/**
 * Implementation of String Compare function
 * @details Compares two strings namely pString1 and pString2.
 *
 * @param[in] pString1 A pointer to the first string to be compared
 * @param[in] pString2 A pointer to the second string to be compared
 * @return   
 *    =0 - Both the strings are equal
 *    >0 - Return a positive value if a character's ASCII value in the first string is bigger than a character's ASCII value in the second string 
 *    <0 - Return a negative number if the ASCII value of a character in the first string is smaller than the ASCII value of a character in the second string
 */
sint32 ecy_strcmp(const char* pString1, const char* pString2);

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    } /* extern "C" */
#endif
/* *INDENT-ON* */

#endif /* ECY_HSM_BASICSRVS_H */
