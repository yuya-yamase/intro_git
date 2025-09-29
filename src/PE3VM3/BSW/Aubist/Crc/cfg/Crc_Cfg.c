/* Crc_Cfg_c_v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Crc/Crc_Cfg/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Crc.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/






#define CRC_TABLE_SIZE                  (0x100U)

#define CRC_MASK_8BIT_LENGTH            (0x000000FFUL)

#define CRC_BIT_SHIFT_8                 (8U)

#define CRC_VALUE_ZERO                  (0U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CRC_START_SEC_CONST_8
#include <Crc_MemMap.h>
    /* CRC_8_TABLE */
    static CONST(AB_83_ConstV uint8, CRC_CONST) Crc_8_Table[CRC_TABLE_SIZE] = { /* MISRA DEVIATION */
        0x00U, 0x1DU, 0x3AU, 0x27U, 0x74U, 0x69U, 0x4EU, 0x53U,
        0xE8U, 0xF5U, 0xD2U, 0xCFU, 0x9CU, 0x81U, 0xA6U, 0xBBU,
        0xCDU, 0xD0U, 0xF7U, 0xEAU, 0xB9U, 0xA4U, 0x83U, 0x9EU,
        0x25U, 0x38U, 0x1FU, 0x02U, 0x51U, 0x4CU, 0x6BU, 0x76U,
        0x87U, 0x9AU, 0xBDU, 0xA0U, 0xF3U, 0xEEU, 0xC9U, 0xD4U,
        0x6FU, 0x72U, 0x55U, 0x48U, 0x1BU, 0x06U, 0x21U, 0x3CU,
        0x4AU, 0x57U, 0x70U, 0x6DU, 0x3EU, 0x23U, 0x04U, 0x19U,
        0xA2U, 0xBFU, 0x98U, 0x85U, 0xD6U, 0xCBU, 0xECU, 0xF1U,

        0x13U, 0x0EU, 0x29U, 0x34U, 0x67U, 0x7AU, 0x5DU, 0x40U,
        0xFBU, 0xE6U, 0xC1U, 0xDCU, 0x8FU, 0x92U, 0xB5U, 0xA8U,
        0xDEU, 0xC3U, 0xE4U, 0xF9U, 0xAAU, 0xB7U, 0x90U, 0x8DU,
        0x36U, 0x2BU, 0x0CU, 0x11U, 0x42U, 0x5FU, 0x78U, 0x65U,
        0x94U, 0x89U, 0xAEU, 0xB3U, 0xE0U, 0xFDU, 0xDAU, 0xC7U,
        0x7CU, 0x61U, 0x46U, 0x5BU, 0x08U, 0x15U, 0x32U, 0x2FU,
        0x59U, 0x44U, 0x63U, 0x7EU, 0x2DU, 0x30U, 0x17U, 0x0AU,
        0xB1U, 0xACU, 0x8BU, 0x96U, 0xC5U, 0xD8U, 0xFFU, 0xE2U,

        0x26U, 0x3BU, 0x1CU, 0x01U, 0x52U, 0x4FU, 0x68U, 0x75U,
        0xCEU, 0xD3U, 0xF4U, 0xE9U, 0xBAU, 0xA7U, 0x80U, 0x9DU,
        0xEBU, 0xF6U, 0xD1U, 0xCCU, 0x9FU, 0x82U, 0xA5U, 0xB8U,
        0x03U, 0x1EU, 0x39U, 0x24U, 0x77U, 0x6AU, 0x4DU, 0x50U,
        0xA1U, 0xBCU, 0x9BU, 0x86U, 0xD5U, 0xC8U, 0xEFU, 0xF2U,
        0x49U, 0x54U, 0x73U, 0x6EU, 0x3DU, 0x20U, 0x07U, 0x1AU,
        0x6CU, 0x71U, 0x56U, 0x4BU, 0x18U, 0x05U, 0x22U, 0x3FU,
        0x84U, 0x99U, 0xBEU, 0xA3U, 0xF0U, 0xEDU, 0xCAU, 0xD7U,

        0x35U, 0x28U, 0x0FU, 0x12U, 0x41U, 0x5CU, 0x7BU, 0x66U,
        0xDDU, 0xC0U, 0xE7U, 0xFAU, 0xA9U, 0xB4U, 0x93U, 0x8EU,
        0xF8U, 0xE5U, 0xC2U, 0xDFU, 0x8CU, 0x91U, 0xB6U, 0xABU,
        0x10U, 0x0DU, 0x2AU, 0x37U, 0x64U, 0x79U, 0x5EU, 0x43U,
        0xB2U, 0xAFU, 0x88U, 0x95U, 0xC6U, 0xDBU, 0xFCU, 0xE1U,
        0x5AU, 0x47U, 0x60U, 0x7DU, 0x2EU, 0x33U, 0x14U, 0x09U,
        0x7FU, 0x62U, 0x45U, 0x58U, 0x0BU, 0x16U, 0x31U, 0x2CU,
        0x97U, 0x8AU, 0xADU, 0xB0U, 0xE3U, 0xFEU, 0xD9U, 0xC4U
    };
#define CRC_STOP_SEC_CONST_8
#include <Crc_MemMap.h>

#define CRC_START_SEC_CONST_8
#include <Crc_MemMap.h>
    /* CRC_8H2F_TABLE */
    static CONST(AB_83_ConstV uint8, CRC_CONST) Crc_8H2F_Table[CRC_TABLE_SIZE] = { /* MISRA DEVIATION */
        0x00U, 0x2FU, 0x5EU, 0x71U, 0xBCU, 0x93U, 0xE2U, 0xCDU,
        0x57U, 0x78U, 0x09U, 0x26U, 0xEBU, 0xC4U, 0xB5U, 0x9AU,
        0xAEU, 0x81U, 0xF0U, 0xDFU, 0x12U, 0x3DU, 0x4CU, 0x63U,
        0xF9U, 0xD6U, 0xA7U, 0x88U, 0x45U, 0x6AU, 0x1BU, 0x34U,
        0x73U, 0x5CU, 0x2DU, 0x02U, 0xCFU, 0xE0U, 0x91U, 0xBEU,
        0x24U, 0x0BU, 0x7AU, 0x55U, 0x98U, 0xB7U, 0xC6U, 0xE9U,
        0xDDU, 0xF2U, 0x83U, 0xACU, 0x61U, 0x4EU, 0x3FU, 0x10U,
        0x8AU, 0xA5U, 0xD4U, 0xFBU, 0x36U, 0x19U, 0x68U, 0x47U,

        0xE6U, 0xC9U, 0xB8U, 0x97U, 0x5AU, 0x75U, 0x04U, 0x2BU,
        0xB1U, 0x9EU, 0xEFU, 0xC0U, 0x0DU, 0x22U, 0x53U, 0x7CU,
        0x48U, 0x67U, 0x16U, 0x39U, 0xF4U, 0xDBU, 0xAAU, 0x85U,
        0x1FU, 0x30U, 0x41U, 0x6EU, 0xA3U, 0x8CU, 0xFDU, 0xD2U,
        0x95U, 0xBAU, 0xCBU, 0xE4U, 0x29U, 0x06U, 0x77U, 0x58U,
        0xC2U, 0xEDU, 0x9CU, 0xB3U, 0x7EU, 0x51U, 0x20U, 0x0FU,
        0x3BU, 0x14U, 0x65U, 0x4AU, 0x87U, 0xA8U, 0xD9U, 0xF6U,
        0x6CU, 0x43U, 0x32U, 0x1DU, 0xD0U, 0xFFU, 0x8EU, 0xA1U,

        0xE3U, 0xCCU, 0xBDU, 0x92U, 0x5FU, 0x70U, 0x01U, 0x2EU,
        0xB4U, 0x9BU, 0xEAU, 0xC5U, 0x08U, 0x27U, 0x56U, 0x79U,
        0x4DU, 0x62U, 0x13U, 0x3CU, 0xF1U, 0xDEU, 0xAFU, 0x80U,
        0x1AU, 0x35U, 0x44U, 0x6BU, 0xA6U, 0x89U, 0xF8U, 0xD7U,
        0x90U, 0xBFU, 0xCEU, 0xE1U, 0x2CU, 0x03U, 0x72U, 0x5DU,
        0xC7U, 0xE8U, 0x99U, 0xB6U, 0x7BU, 0x54U, 0x25U, 0x0AU,
        0x3EU, 0x11U, 0x60U, 0x4FU, 0x82U, 0xADU, 0xDCU, 0xF3U,
        0x69U, 0x46U, 0x37U, 0x18U, 0xD5U, 0xFAU, 0x8BU, 0xA4U,

        0x05U, 0x2AU, 0x5BU, 0x74U, 0xB9U, 0x96U, 0xE7U, 0xC8U,
        0x52U, 0x7DU, 0x0CU, 0x23U, 0xEEU, 0xC1U, 0xB0U, 0x9FU,
        0xABU, 0x84U, 0xF5U, 0xDAU, 0x17U, 0x38U, 0x49U, 0x66U,
        0xFCU, 0xD3U, 0xA2U, 0x8DU, 0x40U, 0x6FU, 0x1EU, 0x31U,
        0x76U, 0x59U, 0x28U, 0x07U, 0xCAU, 0xE5U, 0x94U, 0xBBU,
        0x21U, 0x0EU, 0x7FU, 0x50U, 0x9DU, 0xB2U, 0xC3U, 0xECU,
        0xD8U, 0xF7U, 0x86U, 0xA9U, 0x64U, 0x4BU, 0x3AU, 0x15U,
        0x8FU, 0xA0U, 0xD1U, 0xFEU, 0x33U, 0x1CU, 0x6DU, 0x42U
    };
#define CRC_STOP_SEC_CONST_8
#include <Crc_MemMap.h>

#define CRC_START_SEC_CONST_16
#include <Crc_MemMap.h>
    /* CRC_16_TABLE */
    static CONST(AB_83_ConstV uint16, CRC_CONST) Crc_16_Table[CRC_TABLE_SIZE] = { /* MISRA DEVIATION */
        0x0000U, 0x1021U, 0x2042U, 0x3063U, 0x4084U, 0x50A5U, 0x60C6U, 0x70E7U,
        0x8108U, 0x9129U, 0xA14AU, 0xB16BU, 0xC18CU, 0xD1ADU, 0xE1CEU, 0xF1EFU,
        0x1231U, 0x0210U, 0x3273U, 0x2252U, 0x52B5U, 0x4294U, 0x72F7U, 0x62D6U,
        0x9339U, 0x8318U, 0xB37BU, 0xA35AU, 0xD3BDU, 0xC39CU, 0xF3FFU, 0xE3DEU,
        0x2462U, 0x3443U, 0x0420U, 0x1401U, 0x64E6U, 0x74C7U, 0x44A4U, 0x5485U,
        0xA56AU, 0xB54BU, 0x8528U, 0x9509U, 0xE5EEU, 0xF5CFU, 0xC5ACU, 0xD58DU,
        0x3653U, 0x2672U, 0x1611U, 0x0630U, 0x76D7U, 0x66F6U, 0x5695U, 0x46B4U,
        0xB75BU, 0xA77AU, 0x9719U, 0x8738U, 0xF7DFU, 0xE7FEU, 0xD79DU, 0xC7BCU,

        0x48C4U, 0x58E5U, 0x6886U, 0x78A7U, 0x0840U, 0x1861U, 0x2802U, 0x3823U,
        0xC9CCU, 0xD9EDU, 0xE98EU, 0xF9AFU, 0x8948U, 0x9969U, 0xA90AU, 0xB92BU,
        0x5AF5U, 0x4AD4U, 0x7AB7U, 0x6A96U, 0x1A71U, 0x0A50U, 0x3A33U, 0x2A12U,
        0xDBFDU, 0xCBDCU, 0xFBBFU, 0xEB9EU, 0x9B79U, 0x8B58U, 0xBB3BU, 0xAB1AU,
        0x6CA6U, 0x7C87U, 0x4CE4U, 0x5CC5U, 0x2C22U, 0x3C03U, 0x0C60U, 0x1C41U,
        0xEDAEU, 0xFD8FU, 0xCDECU, 0xDDCDU, 0xAD2AU, 0xBD0BU, 0x8D68U, 0x9D49U,
        0x7E97U, 0x6EB6U, 0x5ED5U, 0x4EF4U, 0x3E13U, 0x2E32U, 0x1E51U, 0x0E70U,
        0xFF9FU, 0xEFBEU, 0xDFDDU, 0xCFFCU, 0xBF1BU, 0xAF3AU, 0x9F59U, 0x8F78U,

        0x9188U, 0x81A9U, 0xB1CAU, 0xA1EBU, 0xD10CU, 0xC12DU, 0xF14EU, 0xE16FU,
        0x1080U, 0x00A1U, 0x30C2U, 0x20E3U, 0x5004U, 0x4025U, 0x7046U, 0x6067U,
        0x83B9U, 0x9398U, 0xA3FBU, 0xB3DAU, 0xC33DU, 0xD31CU, 0xE37FU, 0xF35EU,
        0x02B1U, 0x1290U, 0x22F3U, 0x32D2U, 0x4235U, 0x5214U, 0x6277U, 0x7256U,
        0xB5EAU, 0xA5CBU, 0x95A8U, 0x8589U, 0xF56EU, 0xE54FU, 0xD52CU, 0xC50DU,
        0x34E2U, 0x24C3U, 0x14A0U, 0x0481U, 0x7466U, 0x6447U, 0x5424U, 0x4405U,
        0xA7DBU, 0xB7FAU, 0x8799U, 0x97B8U, 0xE75FU, 0xF77EU, 0xC71DU, 0xD73CU,
        0x26D3U, 0x36F2U, 0x0691U, 0x16B0U, 0x6657U, 0x7676U, 0x4615U, 0x5634U,

        0xD94CU, 0xC96DU, 0xF90EU, 0xE92FU, 0x99C8U, 0x89E9U, 0xB98AU, 0xA9ABU,
        0x5844U, 0x4865U, 0x7806U, 0x6827U, 0x18C0U, 0x08E1U, 0x3882U, 0x28A3U,
        0xCB7DU, 0xDB5CU, 0xEB3FU, 0xFB1EU, 0x8BF9U, 0x9BD8U, 0xABBBU, 0xBB9AU,
        0x4A75U, 0x5A54U, 0x6A37U, 0x7A16U, 0x0AF1U, 0x1AD0U, 0x2AB3U, 0x3A92U,
        0xFD2EU, 0xED0FU, 0xDD6CU, 0xCD4DU, 0xBDAAU, 0xAD8BU, 0x9DE8U, 0x8DC9U,
        0x7C26U, 0x6C07U, 0x5C64U, 0x4C45U, 0x3CA2U, 0x2C83U, 0x1CE0U, 0x0CC1U,
        0xEF1FU, 0xFF3EU, 0xCF5DU, 0xDF7CU, 0xAF9BU, 0xBFBAU, 0x8FD9U, 0x9FF8U,
        0x6E17U, 0x7E36U, 0x4E55U, 0x5E74U, 0x2E93U, 0x3EB2U, 0x0ED1U, 0x1EF0U
    };
#define CRC_STOP_SEC_CONST_16
#include <Crc_MemMap.h>

#define CRC_START_SEC_CONST_32
#include <Crc_MemMap.h>
    /* CRC_32_TABLE */
    static CONST(AB_83_ConstV uint32, CRC_CONST) Crc_32_Table[CRC_TABLE_SIZE] = { /* MISRA DEVIATION */
        0x00000000UL, 0x77073096UL, 0xEE0E612CUL, 0x990951BAUL,
        0x076DC419UL, 0x706AF48FUL, 0xE963A535UL, 0x9E6495A3UL,
        0x0EDB8832UL, 0x79DCB8A4UL, 0xE0D5E91EUL, 0x97D2D988UL,
        0x09B64C2BUL, 0x7EB17CBDUL, 0xE7B82D07UL, 0x90BF1D91UL,
        0x1DB71064UL, 0x6AB020F2UL, 0xF3B97148UL, 0x84BE41DEUL,
        0x1ADAD47DUL, 0x6DDDE4EBUL, 0xF4D4B551UL, 0x83D385C7UL,
        0x136C9856UL, 0x646BA8C0UL, 0xFD62F97AUL, 0x8A65C9ECUL,
        0x14015C4FUL, 0x63066CD9UL, 0xFA0F3D63UL, 0x8D080DF5UL,
        0x3B6E20C8UL, 0x4C69105EUL, 0xD56041E4UL, 0xA2677172UL,
        0x3C03E4D1UL, 0x4B04D447UL, 0xD20D85FDUL, 0xA50AB56BUL,
        0x35B5A8FAUL, 0x42B2986CUL, 0xDBBBC9D6UL, 0xACBCF940UL,
        0x32D86CE3UL, 0x45DF5C75UL, 0xDCD60DCFUL, 0xABD13D59UL,
        0x26D930ACUL, 0x51DE003AUL, 0xC8D75180UL, 0xBFD06116UL,
        0x21B4F4B5UL, 0x56B3C423UL, 0xCFBA9599UL, 0xB8BDA50FUL,
        0x2802B89EUL, 0x5F058808UL, 0xC60CD9B2UL, 0xB10BE924UL,
        0x2F6F7C87UL, 0x58684C11UL, 0xC1611DABUL, 0xB6662D3DUL,

        0x76DC4190UL, 0x01DB7106UL, 0x98D220BCUL, 0xEFD5102AUL,
        0x71B18589UL, 0x06B6B51FUL, 0x9FBFE4A5UL, 0xE8B8D433UL,
        0x7807C9A2UL, 0x0F00F934UL, 0x9609A88EUL, 0xE10E9818UL,
        0x7F6A0DBBUL, 0x086D3D2DUL, 0x91646C97UL, 0xE6635C01UL,
        0x6B6B51F4UL, 0x1C6C6162UL, 0x856530D8UL, 0xF262004EUL,
        0x6C0695EDUL, 0x1B01A57BUL, 0x8208F4C1UL, 0xF50FC457UL,
        0x65B0D9C6UL, 0x12B7E950UL, 0x8BBEB8EAUL, 0xFCB9887CUL,
        0x62DD1DDFUL, 0x15DA2D49UL, 0x8CD37CF3UL, 0xFBD44C65UL,
        0x4DB26158UL, 0x3AB551CEUL, 0xA3BC0074UL, 0xD4BB30E2UL,
        0x4ADFA541UL, 0x3DD895D7UL, 0xA4D1C46DUL, 0xD3D6F4FBUL,
        0x4369E96AUL, 0x346ED9FCUL, 0xAD678846UL, 0xDA60B8D0UL,
        0x44042D73UL, 0x33031DE5UL, 0xAA0A4C5FUL, 0xDD0D7CC9UL,
        0x5005713CUL, 0x270241AAUL, 0xBE0B1010UL, 0xC90C2086UL,
        0x5768B525UL, 0x206F85B3UL, 0xB966D409UL, 0xCE61E49FUL,
        0x5EDEF90EUL, 0x29D9C998UL, 0xB0D09822UL, 0xC7D7A8B4UL,
        0x59B33D17UL, 0x2EB40D81UL, 0xB7BD5C3BUL, 0xC0BA6CADUL,

        0xEDB88320UL, 0x9ABFB3B6UL, 0x03B6E20CUL, 0x74B1D29AUL,
        0xEAD54739UL, 0x9DD277AFUL, 0x04DB2615UL, 0x73DC1683UL,
        0xE3630B12UL, 0x94643B84UL, 0x0D6D6A3EUL, 0x7A6A5AA8UL,
        0xE40ECF0BUL, 0x9309FF9DUL, 0x0A00AE27UL, 0x7D079EB1UL,
        0xF00F9344UL, 0x8708A3D2UL, 0x1E01F268UL, 0x6906C2FEUL,
        0xF762575DUL, 0x806567CBUL, 0x196C3671UL, 0x6E6B06E7UL,
        0xFED41B76UL, 0x89D32BE0UL, 0x10DA7A5AUL, 0x67DD4ACCUL,
        0xF9B9DF6FUL, 0x8EBEEFF9UL, 0x17B7BE43UL, 0x60B08ED5UL,
        0xD6D6A3E8UL, 0xA1D1937EUL, 0x38D8C2C4UL, 0x4FDFF252UL,
        0xD1BB67F1UL, 0xA6BC5767UL, 0x3FB506DDUL, 0x48B2364BUL,
        0xD80D2BDAUL, 0xAF0A1B4CUL, 0x36034AF6UL, 0x41047A60UL,
        0xDF60EFC3UL, 0xA867DF55UL, 0x316E8EEFUL, 0x4669BE79UL,
        0xCB61B38CUL, 0xBC66831AUL, 0x256FD2A0UL, 0x5268E236UL,
        0xCC0C7795UL, 0xBB0B4703UL, 0x220216B9UL, 0x5505262FUL,
        0xC5BA3BBEUL, 0xB2BD0B28UL, 0x2BB45A92UL, 0x5CB36A04UL,
        0xC2D7FFA7UL, 0xB5D0CF31UL, 0x2CD99E8BUL, 0x5BDEAE1DUL,

        0x9B64C2B0UL, 0xEC63F226UL, 0x756AA39CUL, 0x026D930AUL,
        0x9C0906A9UL, 0xEB0E363FUL, 0x72076785UL, 0x05005713UL,
        0x95BF4A82UL, 0xE2B87A14UL, 0x7BB12BAEUL, 0x0CB61B38UL,
        0x92D28E9BUL, 0xE5D5BE0DUL, 0x7CDCEFB7UL, 0x0BDBDF21UL,
        0x86D3D2D4UL, 0xF1D4E242UL, 0x68DDB3F8UL, 0x1FDA836EUL,
        0x81BE16CDUL, 0xF6B9265BUL, 0x6FB077E1UL, 0x18B74777UL,
        0x88085AE6UL, 0xFF0F6A70UL, 0x66063BCAUL, 0x11010B5CUL,
        0x8F659EFFUL, 0xF862AE69UL, 0x616BFFD3UL, 0x166CCF45UL,
        0xA00AE278UL, 0xD70DD2EEUL, 0x4E048354UL, 0x3903B3C2UL,
        0xA7672661UL, 0xD06016F7UL, 0x4969474DUL, 0x3E6E77DBUL,
        0xAED16A4AUL, 0xD9D65ADCUL, 0x40DF0B66UL, 0x37D83BF0UL,
        0xA9BCAE53UL, 0xDEBB9EC5UL, 0x47B2CF7FUL, 0x30B5FFE9UL,
        0xBDBDF21CUL, 0xCABAC28AUL, 0x53B39330UL, 0x24B4A3A6UL,
        0xBAD03605UL, 0xCDD70693UL, 0x54DE5729UL, 0x23D967BFUL,
        0xB3667A2EUL, 0xC4614AB8UL, 0x5D681B02UL, 0x2A6F2B94UL,
        0xB40BBE37UL, 0xC30C8EA1UL, 0x5A05DF1BUL, 0x2D02EF8DUL
    };
#define CRC_STOP_SEC_CONST_32
#include <Crc_MemMap.h>

#define CRC_START_SEC_CONST_32
#include <Crc_MemMap.h>
    /* CRC_32P4_TABLE */
    static CONST(AB_83_ConstV uint32, CRC_CONST) Crc_32P4_Table[CRC_TABLE_SIZE] = { /* MISRA DEVIATION */
        0x00000000UL, 0x30850FF5UL, 0x610A1FEAUL, 0x518F101FUL,
        0xC2143FD4UL, 0xF2913021UL, 0xA31E203EUL, 0x939B2FCBUL,
        0x159615F7UL, 0x25131A02UL, 0x749C0A1DUL, 0x441905E8UL,
        0xD7822A23UL, 0xE70725D6UL, 0xB68835C9UL, 0x860D3A3CUL,
        0x2B2C2BEEUL, 0x1BA9241BUL, 0x4A263404UL, 0x7AA33BF1UL,
        0xE938143AUL, 0xD9BD1BCFUL, 0x88320BD0UL, 0xB8B70425UL,
        0x3EBA3E19UL, 0x0E3F31ECUL, 0x5FB021F3UL, 0x6F352E06UL,
        0xFCAE01CDUL, 0xCC2B0E38UL, 0x9DA41E27UL, 0xAD2111D2UL,
        0x565857DCUL, 0x66DD5829UL, 0x37524836UL, 0x07D747C3UL,
        0x944C6808UL, 0xA4C967FDUL, 0xF54677E2UL, 0xC5C37817UL,
        0x43CE422BUL, 0x734B4DDEUL, 0x22C45DC1UL, 0x12415234UL,
        0x81DA7DFFUL, 0xB15F720AUL, 0xE0D06215UL, 0xD0556DE0UL,
        0x7D747C32UL, 0x4DF173C7UL, 0x1C7E63D8UL, 0x2CFB6C2DUL,
        0xBF6043E6UL, 0x8FE54C13UL, 0xDE6A5C0CUL, 0xEEEF53F9UL,
        0x68E269C5UL, 0x58676630UL, 0x09E8762FUL, 0x396D79DAUL,
        0xAAF65611UL, 0x9A7359E4UL, 0xCBFC49FBUL, 0xFB79460EUL,

        0xACB0AFB8UL, 0x9C35A04DUL, 0xCDBAB052UL, 0xFD3FBFA7UL,
        0x6EA4906CUL, 0x5E219F99UL, 0x0FAE8F86UL, 0x3F2B8073UL,
        0xB926BA4FUL, 0x89A3B5BAUL, 0xD82CA5A5UL, 0xE8A9AA50UL,
        0x7B32859BUL, 0x4BB78A6EUL, 0x1A389A71UL, 0x2ABD9584UL,
        0x879C8456UL, 0xB7198BA3UL, 0xE6969BBCUL, 0xD6139449UL,
        0x4588BB82UL, 0x750DB477UL, 0x2482A468UL, 0x1407AB9DUL,
        0x920A91A1UL, 0xA28F9E54UL, 0xF3008E4BUL, 0xC38581BEUL,
        0x501EAE75UL, 0x609BA180UL, 0x3114B19FUL, 0x0191BE6AUL,
        0xFAE8F864UL, 0xCA6DF791UL, 0x9BE2E78EUL, 0xAB67E87BUL,
        0x38FCC7B0UL, 0x0879C845UL, 0x59F6D85AUL, 0x6973D7AFUL,
        0xEF7EED93UL, 0xDFFBE266UL, 0x8E74F279UL, 0xBEF1FD8CUL,
        0x2D6AD247UL, 0x1DEFDDB2UL, 0x4C60CDADUL, 0x7CE5C258UL,
        0xD1C4D38AUL, 0xE141DC7FUL, 0xB0CECC60UL, 0x804BC395UL,
        0x13D0EC5EUL, 0x2355E3ABUL, 0x72DAF3B4UL, 0x425FFC41UL,
        0xC452C67DUL, 0xF4D7C988UL, 0xA558D997UL, 0x95DDD662UL,
        0x0646F9A9UL, 0x36C3F65CUL, 0x674CE643UL, 0x57C9E9B6UL,

        0xC8DF352FUL, 0xF85A3ADAUL, 0xA9D52AC5UL, 0x99502530UL,
        0x0ACB0AFBUL, 0x3A4E050EUL, 0x6BC11511UL, 0x5B441AE4UL,
        0xDD4920D8UL, 0xEDCC2F2DUL, 0xBC433F32UL, 0x8CC630C7UL,
        0x1F5D1F0CUL, 0x2FD810F9UL, 0x7E5700E6UL, 0x4ED20F13UL,
        0xE3F31EC1UL, 0xD3761134UL, 0x82F9012BUL, 0xB27C0EDEUL,
        0x21E72115UL, 0x11622EE0UL, 0x40ED3EFFUL, 0x7068310AUL,
        0xF6650B36UL, 0xC6E004C3UL, 0x976F14DCUL, 0xA7EA1B29UL,
        0x347134E2UL, 0x04F43B17UL, 0x557B2B08UL, 0x65FE24FDUL,
        0x9E8762F3UL, 0xAE026D06UL, 0xFF8D7D19UL, 0xCF0872ECUL,
        0x5C935D27UL, 0x6C1652D2UL, 0x3D9942CDUL, 0x0D1C4D38UL,
        0x8B117704UL, 0xBB9478F1UL, 0xEA1B68EEUL, 0xDA9E671BUL,
        0x490548D0UL, 0x79804725UL, 0x280F573AUL, 0x188A58CFUL,
        0xB5AB491DUL, 0x852E46E8UL, 0xD4A156F7UL, 0xE4245902UL,
        0x77BF76C9UL, 0x473A793CUL, 0x16B56923UL, 0x263066D6UL,
        0xA03D5CEAUL, 0x90B8531FUL, 0xC1374300UL, 0xF1B24CF5UL,
        0x6229633EUL, 0x52AC6CCBUL, 0x03237CD4UL, 0x33A67321UL,

        0x646F9A97UL, 0x54EA9562UL, 0x0565857DUL, 0x35E08A88UL,
        0xA67BA543UL, 0x96FEAAB6UL, 0xC771BAA9UL, 0xF7F4B55CUL,
        0x71F98F60UL, 0x417C8095UL, 0x10F3908AUL, 0x20769F7FUL,
        0xB3EDB0B4UL, 0x8368BF41UL, 0xD2E7AF5EUL, 0xE262A0ABUL,
        0x4F43B179UL, 0x7FC6BE8CUL, 0x2E49AE93UL, 0x1ECCA166UL,
        0x8D578EADUL, 0xBDD28158UL, 0xEC5D9147UL, 0xDCD89EB2UL,
        0x5AD5A48EUL, 0x6A50AB7BUL, 0x3BDFBB64UL, 0x0B5AB491UL,
        0x98C19B5AUL, 0xA84494AFUL, 0xF9CB84B0UL, 0xC94E8B45UL,
        0x3237CD4BUL, 0x02B2C2BEUL, 0x533DD2A1UL, 0x63B8DD54UL,
        0xF023F29FUL, 0xC0A6FD6AUL, 0x9129ED75UL, 0xA1ACE280UL,
        0x27A1D8BCUL, 0x1724D749UL, 0x46ABC756UL, 0x762EC8A3UL,
        0xE5B5E768UL, 0xD530E89DUL, 0x84BFF882UL, 0xB43AF777UL,
        0x191BE6A5UL, 0x299EE950UL, 0x7811F94FUL, 0x4894F6BAUL,
        0xDB0FD971UL, 0xEB8AD684UL, 0xBA05C69BUL, 0x8A80C96EUL,
        0x0C8DF352UL, 0x3C08FCA7UL, 0x6D87ECB8UL, 0x5D02E34DUL,
        0xCE99CC86UL, 0xFE1CC373UL, 0xAF93D36CUL, 0x9F16DC99UL
    };
#define CRC_STOP_SEC_CONST_32
#include <Crc_MemMap.h>

#define CRC_START_SEC_CONST_64
#include <Crc_MemMap.h>
    /* CRC_64_TABLE */
    static CONST(AB_83_ConstV uint64, CRC_CONST) Crc_64_Table[CRC_TABLE_SIZE] = { /* MISRA DEVIATION */
        0x0000000000000000ULL, 0xB32E4CBE03A75F6FULL, 0xF4843657A840A05BULL, 0x47AA7AE9ABE7FF34ULL,
        0x7BD0C384FF8F5E33ULL, 0xC8FE8F3AFC28015CULL, 0x8F54F5D357CFFE68ULL, 0x3C7AB96D5468A107ULL,
        0xF7A18709FF1EBC66ULL, 0x448FCBB7FCB9E309ULL, 0x0325B15E575E1C3DULL, 0xB00BFDE054F94352ULL,
        0x8C71448D0091E255ULL, 0x3F5F08330336BD3AULL, 0x78F572DAA8D1420EULL, 0xCBDB3E64AB761D61ULL,
        0x7D9BA13851336649ULL, 0xCEB5ED8652943926ULL, 0x891F976FF973C612ULL, 0x3A31DBD1FAD4997DULL,
        0x064B62BCAEBC387AULL, 0xB5652E02AD1B6715ULL, 0xF2CF54EB06FC9821ULL, 0x41E11855055BC74EULL,
        0x8A3A2631AE2DDA2FULL, 0x39146A8FAD8A8540ULL, 0x7EBE1066066D7A74ULL, 0xCD905CD805CA251BULL,
        0xF1EAE5B551A2841CULL, 0x42C4A90B5205DB73ULL, 0x056ED3E2F9E22447ULL, 0xB6409F5CFA457B28ULL,
        0xFB374270A266CC92ULL, 0x48190ECEA1C193FDULL, 0x0FB374270A266CC9ULL, 0xBC9D3899098133A6ULL,
        0x80E781F45DE992A1ULL, 0x33C9CD4A5E4ECDCEULL, 0x7463B7A3F5A932FAULL, 0xC74DFB1DF60E6D95ULL,
        0x0C96C5795D7870F4ULL, 0xBFB889C75EDF2F9BULL, 0xF812F32EF538D0AFULL, 0x4B3CBF90F69F8FC0ULL,
        0x774606FDA2F72EC7ULL, 0xC4684A43A15071A8ULL, 0x83C230AA0AB78E9CULL, 0x30EC7C140910D1F3ULL,
        0x86ACE348F355AADBULL, 0x3582AFF6F0F2F5B4ULL, 0x7228D51F5B150A80ULL, 0xC10699A158B255EFULL,
        0xFD7C20CC0CDAF4E8ULL, 0x4E526C720F7DAB87ULL, 0x09F8169BA49A54B3ULL, 0xBAD65A25A73D0BDCULL,
        0x710D64410C4B16BDULL, 0xC22328FF0FEC49D2ULL, 0x85895216A40BB6E6ULL, 0x36A71EA8A7ACE989ULL,
        0x0ADDA7C5F3C4488EULL, 0xB9F3EB7BF06317E1ULL, 0xFE5991925B84E8D5ULL, 0x4D77DD2C5823B7BAULL,

        0x64B62BCAEBC387A1ULL, 0xD7986774E864D8CEULL, 0x90321D9D438327FAULL, 0x231C512340247895ULL,
        0x1F66E84E144CD992ULL, 0xAC48A4F017EB86FDULL, 0xEBE2DE19BC0C79C9ULL, 0x58CC92A7BFAB26A6ULL,
        0x9317ACC314DD3BC7ULL, 0x2039E07D177A64A8ULL, 0x67939A94BC9D9B9CULL, 0xD4BDD62ABF3AC4F3ULL,
        0xE8C76F47EB5265F4ULL, 0x5BE923F9E8F53A9BULL, 0x1C4359104312C5AFULL, 0xAF6D15AE40B59AC0ULL,
        0x192D8AF2BAF0E1E8ULL, 0xAA03C64CB957BE87ULL, 0xEDA9BCA512B041B3ULL, 0x5E87F01B11171EDCULL,
        0x62FD4976457FBFDBULL, 0xD1D305C846D8E0B4ULL, 0x96797F21ED3F1F80ULL, 0x2557339FEE9840EFULL,
        0xEE8C0DFB45EE5D8EULL, 0x5DA24145464902E1ULL, 0x1A083BACEDAEFDD5ULL, 0xA9267712EE09A2BAULL,
        0x955CCE7FBA6103BDULL, 0x267282C1B9C65CD2ULL, 0x61D8F8281221A3E6ULL, 0xD2F6B4961186FC89ULL,
        0x9F8169BA49A54B33ULL, 0x2CAF25044A02145CULL, 0x6B055FEDE1E5EB68ULL, 0xD82B1353E242B407ULL,
        0xE451AA3EB62A1500ULL, 0x577FE680B58D4A6FULL, 0x10D59C691E6AB55BULL, 0xA3FBD0D71DCDEA34ULL,
        0x6820EEB3B6BBF755ULL, 0xDB0EA20DB51CA83AULL, 0x9CA4D8E41EFB570EULL, 0x2F8A945A1D5C0861ULL,
        0x13F02D374934A966ULL, 0xA0DE61894A93F609ULL, 0xE7741B60E174093DULL, 0x545A57DEE2D35652ULL,
        0xE21AC88218962D7AULL, 0x5134843C1B317215ULL, 0x169EFED5B0D68D21ULL, 0xA5B0B26BB371D24EULL,
        0x99CA0B06E7197349ULL, 0x2AE447B8E4BE2C26ULL, 0x6D4E3D514F59D312ULL, 0xDE6071EF4CFE8C7DULL,
        0x15BB4F8BE788911CULL, 0xA6950335E42FCE73ULL, 0xE13F79DC4FC83147ULL, 0x521135624C6F6E28ULL,
        0x6E6B8C0F1807CF2FULL, 0xDD45C0B11BA09040ULL, 0x9AEFBA58B0476F74ULL, 0x29C1F6E6B3E0301BULL,

        0xC96C5795D7870F42ULL, 0x7A421B2BD420502DULL, 0x3DE861C27FC7AF19ULL, 0x8EC62D7C7C60F076ULL,
        0xB2BC941128085171ULL, 0x0192D8AF2BAF0E1EULL, 0x4638A2468048F12AULL, 0xF516EEF883EFAE45ULL,
        0x3ECDD09C2899B324ULL, 0x8DE39C222B3EEC4BULL, 0xCA49E6CB80D9137FULL, 0x7967AA75837E4C10ULL,
        0x451D1318D716ED17ULL, 0xF6335FA6D4B1B278ULL, 0xB199254F7F564D4CULL, 0x02B769F17CF11223ULL,
        0xB4F7F6AD86B4690BULL, 0x07D9BA1385133664ULL, 0x4073C0FA2EF4C950ULL, 0xF35D8C442D53963FULL,
        0xCF273529793B3738ULL, 0x7C0979977A9C6857ULL, 0x3BA3037ED17B9763ULL, 0x888D4FC0D2DCC80CULL,
        0x435671A479AAD56DULL, 0xF0783D1A7A0D8A02ULL, 0xB7D247F3D1EA7536ULL, 0x04FC0B4DD24D2A59ULL,
        0x3886B22086258B5EULL, 0x8BA8FE9E8582D431ULL, 0xCC0284772E652B05ULL, 0x7F2CC8C92DC2746AULL,
        0x325B15E575E1C3D0ULL, 0x8175595B76469CBFULL, 0xC6DF23B2DDA1638BULL, 0x75F16F0CDE063CE4ULL,
        0x498BD6618A6E9DE3ULL, 0xFAA59ADF89C9C28CULL, 0xBD0FE036222E3DB8ULL, 0x0E21AC88218962D7ULL,
        0xC5FA92EC8AFF7FB6ULL, 0x76D4DE52895820D9ULL, 0x317EA4BB22BFDFEDULL, 0x8250E80521188082ULL,
        0xBE2A516875702185ULL, 0x0D041DD676D77EEAULL, 0x4AAE673FDD3081DEULL, 0xF9802B81DE97DEB1ULL,
        0x4FC0B4DD24D2A599ULL, 0xFCEEF8632775FAF6ULL, 0xBB44828A8C9205C2ULL, 0x086ACE348F355AADULL,
        0x34107759DB5DFBAAULL, 0x873E3BE7D8FAA4C5ULL, 0xC094410E731D5BF1ULL, 0x73BA0DB070BA049EULL,
        0xB86133D4DBCC19FFULL, 0x0B4F7F6AD86B4690ULL, 0x4CE50583738CB9A4ULL, 0xFFCB493D702BE6CBULL,
        0xC3B1F050244347CCULL, 0x709FBCEE27E418A3ULL, 0x3735C6078C03E797ULL, 0x841B8AB98FA4B8F8ULL,

        0xADDA7C5F3C4488E3ULL, 0x1EF430E13FE3D78CULL, 0x595E4A08940428B8ULL, 0xEA7006B697A377D7ULL,
        0xD60ABFDBC3CBD6D0ULL, 0x6524F365C06C89BFULL, 0x228E898C6B8B768BULL, 0x91A0C532682C29E4ULL,
        0x5A7BFB56C35A3485ULL, 0xE955B7E8C0FD6BEAULL, 0xAEFFCD016B1A94DEULL, 0x1DD181BF68BDCBB1ULL,
        0x21AB38D23CD56AB6ULL, 0x9285746C3F7235D9ULL, 0xD52F0E859495CAEDULL, 0x6601423B97329582ULL,
        0xD041DD676D77EEAAULL, 0x636F91D96ED0B1C5ULL, 0x24C5EB30C5374EF1ULL, 0x97EBA78EC690119EULL,
        0xAB911EE392F8B099ULL, 0x18BF525D915FEFF6ULL, 0x5F1528B43AB810C2ULL, 0xEC3B640A391F4FADULL,
        0x27E05A6E926952CCULL, 0x94CE16D091CE0DA3ULL, 0xD3646C393A29F297ULL, 0x604A2087398EADF8ULL,
        0x5C3099EA6DE60CFFULL, 0xEF1ED5546E415390ULL, 0xA8B4AFBDC5A6ACA4ULL, 0x1B9AE303C601F3CBULL,
        0x56ED3E2F9E224471ULL, 0xE5C372919D851B1EULL, 0xA26908783662E42AULL, 0x114744C635C5BB45ULL,
        0x2D3DFDAB61AD1A42ULL, 0x9E13B115620A452DULL, 0xD9B9CBFCC9EDBA19ULL, 0x6A978742CA4AE576ULL,
        0xA14CB926613CF817ULL, 0x1262F598629BA778ULL, 0x55C88F71C97C584CULL, 0xE6E6C3CFCADB0723ULL,
        0xDA9C7AA29EB3A624ULL, 0x69B2361C9D14F94BULL, 0x2E184CF536F3067FULL, 0x9D36004B35545910ULL,
        0x2B769F17CF112238ULL, 0x9858D3A9CCB67D57ULL, 0xDFF2A94067518263ULL, 0x6CDCE5FE64F6DD0CULL,
        0x50A65C93309E7C0BULL, 0xE388102D33392364ULL, 0xA4226AC498DEDC50ULL, 0x170C267A9B79833FULL,
        0xDCD7181E300F9E5EULL, 0x6FF954A033A8C131ULL, 0x28532E49984F3E05ULL, 0x9B7D62F79BE8616AULL,
        0xA707DB9ACF80C06DULL, 0x14299724CC279F02ULL, 0x5383EDCD67C06036ULL, 0xE0ADA17364673F59ULL
    };
#define CRC_STOP_SEC_CONST_64
#include <Crc_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CRC_START_SEC_CODE
#include <Crc_MemMap.h>
/****************************************************************************/
/* Function Name    | Crc_CalculateCRC8                                     */
/* Description      | This service makes a CRC8 calculation on Crc_Length   */
/*                  | data bytes, with SAE J1850 parameters.                */
/* Preconditions    | None                                                  */
/* Parameters       | *Crc_DataPtr          : Pointer to data block         */
/*                  | Crc_Length            : Length of data block[Byte]    */
/*                  | Crc_StartValue8       : Start value of the calculation*/
/*                  | Crc_IsFirstCall       : First call flag[TRUEorFALSE]  */
/* Return Value     | uint8                 : Result of CRC calculation     */
/* Notes            | SWS_Crc_00031, SWS_Crc_00030 , SWS_Crc_00052          */
/*                  | SWS_Crc_00032                                         */
/****************************************************************************/
/* [lib_SC1-1_crc_0001] */
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8
/* Implements [lib_SDD1-1_crc_0001] */
( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall )
{
    uint8     u1_crc8;                         /* CRC result */
    uint32    u4_counter;                      /* Counter[set to Crc_Length] */
    uint32    u4_position = CRC_DATAPOS_INIT;  /* Crc_DataPtr[u4_position] */
    uint8     u1_StartValue;                   /* Start value */
    uint8     u1_ret;                          /* Return value */

    /* Set parameters */
    u1_StartValue = Crc_StartValue8 ^ (uint8)CRC_CRC8_XOR_VALUE;  /* SWS_Crc_00041 */
    if( Crc_IsFirstCall == (boolean)TRUE )
    {
        u1_StartValue = (uint8)CRC_CRC8_INIT_VALUE;  /* SWS_Crc_00014 */
    }
    u4_counter = Crc_Length;

    /* SWS_Crc_00013 */
    /*                */
    /* CRC_8_TABLE    */
    /*                */
    /* SWS_Crc_00014 */
    u1_crc8 = u1_StartValue;
    while( u4_counter > (uint32)CRC_VALUE_ZERO )
    {
        u1_crc8 = Crc_8_Table[u1_crc8 ^ Crc_DataPtr[u4_position]];
        u4_position++;
        u4_counter--;
    }

    u1_ret = u1_crc8 ^ (uint8)CRC_CRC8_XOR_VALUE;

    return u1_ret;
}

/****************************************************************************/
/* Function Name    | Crc_CalculateCRC8H2F                                  */
/* Description      | This service makes a CRC8 calculation with the        */
/*                  | Polynomial 0x2F on Crc_Length.                        */
/* Preconditions    | None                                                  */
/* Parameters       | *Crc_DataPtr          : Pointer to data block         */
/*                  | Crc_Length            : Length of data block[Byte]    */
/*                  | Crc_StartValue8H2F    : Start value of the calculation*/
/*                  | Crc_IsFirstCall       : First call flag[TRUEorFALSE]  */
/* Return Value     | uint8                 : Result of CRC calculation     */
/* Notes            | SWS_Crc_00043 , SWS_Crc_00042 , SWS_Crc_00053         */
/*                  | SWS_Crc_00044                                         */
/****************************************************************************/
/* [lib_SC1-1_crc_0002] */
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8H2F
/* Implements [lib_SDD1-1_crc_0002] */
( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall )
{
    uint8     u1_crc8h2f;                      /* CRC result */
    uint32    u4_counter;                      /* Counter[set to Crc_Length] */
    uint32    u4_position = CRC_DATAPOS_INIT;  /* Crc_DataPtr[u4_position] */
    uint8     u1_StartValue;                   /* Start value */
    uint8     u1_ret;                          /* Return value */

    /* Set parameters */
    u1_StartValue = Crc_StartValue8H2F ^ (uint8)CRC_CRC8H2F_XOR_VALUE;  /* SWS_Crc_00041 */
    if( Crc_IsFirstCall == (boolean)TRUE )
    {
        u1_StartValue = (uint8)CRC_CRC8H2F_INIT_VALUE;  /* SWS_Crc_00014 */
    }
    u4_counter = Crc_Length;
    
    /* SWS_Crc_00013 */
    /*                */
    /* CRC_8H2F_TABLE */
    /*                */
    /* SWS_Crc_00014 */
    u1_crc8h2f = u1_StartValue;
    while( u4_counter > (uint32)CRC_VALUE_ZERO )
    {
        u1_crc8h2f = Crc_8H2F_Table[u1_crc8h2f ^ Crc_DataPtr[u4_position]];
        u4_position++;
        u4_counter--;
    }

    u1_ret = u1_crc8h2f ^ (uint8)CRC_CRC8H2F_XOR_VALUE;

    return u1_ret;

}

/****************************************************************************/
/* Function Name    | Crc_CalculateCRC16                                    */
/* Description      | This service makes a CRC16 calculation on Crc_Length  */
/*                  | data bytes.                                           */
/* Preconditions    | None                                                  */
/* Parameters       | *Crc_DataPtr          : Pointer to data block         */
/*                  | Crc_Length            : Length of data block[Byte]    */
/*                  | Crc_StartValue16      : Start value of the calculation*/
/*                  | Crc_IsFirstCall       : First call flag[TRUEorFALSE]  */
/* Return Value     | uint16                : Result of CRC calculation     */
/* Notes            | SWS_Crc_00019 , SWS_Crc_00002 , SWS_Crc_00054         */
/*                  | SWS_Crc_00015                                         */
/****************************************************************************/
/* [lib_SC1-1_crc_0003] */
FUNC(uint16, CRC_CODE) Crc_CalculateCRC16
/* Implements [lib_SDD1-1_crc_0003] */
( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall )
{
    uint16    u2_crc16;          /* CRC result */

    uint32    u4_counter;                      /* Counter[set to Crc_Length] */
    uint32    u4_position = CRC_DATAPOS_INIT;  /* Crc_DataPtr[u4_position] */
    uint16    u2_StartValue;                   /* Start value */
    uint16    u2_ret;                          /* Return value */

    /* Set parameters */
    u2_StartValue = Crc_StartValue16;  /* SWS_Crc_00041 */
    if( Crc_IsFirstCall == (boolean)TRUE )
    {
        u2_StartValue = (uint16)CRC_CRC16_INIT_VALUE;  /* SWS_Crc_00014 */
    }
    u4_counter = Crc_Length;

    /* SWS_Crc_00013 */
    /*              */
    /* CRC_16_TABLE */
    /*              */
    /* SWS_Crc_00014 */
    u2_crc16 = u2_StartValue;
    while( u4_counter > (uint32)CRC_VALUE_ZERO )
    {
        u2_crc16 = Crc_16_Table[(u2_crc16 >> (uint16)CRC_BIT_SHIFT_8) ^ (uint16)Crc_DataPtr[u4_position]] ^ (uint16)((u2_crc16 & (uint16)CRC_MASK_8BIT_LENGTH) << (uint16)CRC_BIT_SHIFT_8);
        u4_position++;
        u4_counter--;
    }

    u2_ret = u2_crc16;

    return u2_ret;

}

/****************************************************************************/
/* Function Name    | Crc_CalculateCRC32                                    */
/* Description      | This service makes a CRC32 calculation on Crc_Length  */
/*                  | data bytes.                                           */
/* Preconditions    | None                                                  */
/* Parameters       | *Crc_DataPtr          : Pointer to data block         */
/*                  | Crc_Length            : Length of data block[Byte]    */
/*                  | Crc_StartValue32      : Start value of the calculation*/
/*                  | Crc_IsFirstCall       : First call flag[TRUEorFALSE]  */
/* Return Value     | uint32                : Result of CRC calculation     */
/* Notes            | SWS_Crc_00020 , SWS_Crc_00003 , SWS_Crc_00055         */
/*                  | SWS_Crc_00016                                         */
/****************************************************************************/
/* [lib_SC1-1_crc_0004] */
FUNC(uint32, CRC_CODE) Crc_CalculateCRC32
/* Implements [lib_SDD1-1_crc_0004] */
( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall )
{
    uint32    u4_crc32;          /* CRC result */

    uint32    u4_counter;                      /* Counter[set to Crc_Length] */
    uint32    u4_position = CRC_DATAPOS_INIT;  /* Crc_DataPtr[u4_position] */
    uint32    u4_StartValue;                   /* Start value */
    uint32    u4_ret;                          /* Return value */

    /* Set parameters */
    u4_StartValue = Crc_StartValue32 ^ (uint32)CRC_CRC32_XOR_VALUE;  /* SWS_Crc_00041 */
    if( Crc_IsFirstCall == (boolean)TRUE )
    {
        u4_StartValue = (uint32)CRC_CRC32_INIT_VALUE;  /* SWS_Crc_00014 */
    }
    u4_counter = Crc_Length;

    /* SWS_Crc_00013 */
    /*              */
    /* CRC_32_TABLE */
    /*              */
    /* SWS_Crc_00041 */
    u4_crc32 = u4_StartValue;
    while( u4_counter > (uint32)CRC_VALUE_ZERO )
    {
        u4_crc32 = Crc_32_Table[(u4_crc32 ^ (uint32)Crc_DataPtr[u4_position]) & (uint32)CRC_MASK_8BIT_LENGTH] ^ (u4_crc32 >> (uint32)CRC_BIT_SHIFT_8);
        u4_position++;
        u4_counter--;
    }
    u4_ret = u4_crc32 ^ (uint32)CRC_CRC32_XOR_VALUE;

    return u4_ret;

}

/****************************************************************************/
/* Function Name    | Crc_CalculateCRC32P4                                  */
/* Description      | This service makes a CRC32 calculation on Crc_Length  */
/*                  | data bytes, using the polynomial 0xF4ACFB13 .         */
/*                  | This CRC routine is used by E2E Profile 4 .           */
/* Preconditions    | None                                                  */
/* Parameters       | *Crc_DataPtr          : Pointer to data block         */
/*                  | Crc_Length            : Length of data block[Byte]    */
/*                  | Crc_StartValue32      : Start value of the calculation*/
/*                  | Crc_IsFirstCall       : First call flag[TRUEorFALSE]  */
/* Return Value     | uint32                : Result of CRC calculation     */
/* Notes            | SWS_Crc_00058 , SWS_Crc_00056 , SWS_Crc_00057         */
/*                  | SWS_Crc_00059                                         */
/****************************************************************************/
/* [lib_SC1-1_crc_0005] */
FUNC(uint32, CRC_CODE) Crc_CalculateCRC32P4
/* Implements [lib_SDD1-1_crc_0005] */
( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall )
{
    uint32    u4_crc32p4;                      /* CRC result */
    uint32    u4_counter;                      /* Counter[set to Crc_Length] */
    uint32    u4_position = CRC_DATAPOS_INIT;  /* Crc_DataPtr[u4_position] */
    uint32    u4_StartValue;                   /* Start value */
    uint32    u4_ret;                          /* Return value */

    /* Set parameters */
    u4_StartValue = Crc_StartValue32 ^ (uint32)CRC_CRC32P4_XOR_VALUE;  /* SWS_Crc_00041 */
    if( Crc_IsFirstCall == (boolean)TRUE )
    {
        u4_StartValue = (uint32)CRC_CRC32P4_INIT_VALUE;  /* SWS_Crc_00014 */
    }
    u4_counter = Crc_Length;

    /* SWS_Crc_00013 */
    /*                */
    /* CRC_32P4_TABLE */
    /*                */
    /* SWS_Crc_00041 */
    u4_crc32p4 = u4_StartValue;
    while( u4_counter > (uint32)CRC_VALUE_ZERO )
    {
        u4_crc32p4 = Crc_32P4_Table[(u4_crc32p4 ^ (uint32)Crc_DataPtr[u4_position]) & (uint32)CRC_MASK_8BIT_LENGTH] ^ (u4_crc32p4 >> (uint32)CRC_BIT_SHIFT_8);
        u4_position++;
        u4_counter--;
    }
    u4_ret = u4_crc32p4 ^ (uint32)CRC_CRC32P4_XOR_VALUE;

    return u4_ret;

}

/****************************************************************************/
/* Function Name    | Crc_CalculateCRC64                                    */
/* Description      | This service makes a CRC64 calculation on Crc_Length  */
/*                  | data bytes, using the polynomial 0x42F0E1EBA9EA3693 . */
/*                  | This CRC routine is used by E2E Profile 7 .           */
/* Preconditions    | None                                                  */
/* Parameters       | *Crc_DataPtr          : Pointer to data block         */
/*                  | Crc_Length            : Length of data block[Byte]    */
/*                  | Crc_StartValue64      : Start value of the calculation*/
/*                  | Crc_IsFirstCall       : First call flag[TRUEorFALSE]  */
/* Return Value     | uint64                : Result of CRC calculation     */
/* Notes            | SWS_Crc_00061 , SWS_Crc_00062 , SWS_Crc_00063         */
/*                  | SWS_Crc_00064 , SWS_Crc_00065                         */
/****************************************************************************/
/* [lib_SC1-1_crc_0007] */
FUNC(uint64, CRC_CODE) Crc_CalculateCRC64
/* Implements [lib_SDD1-1_crc_0007] */
( P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataPtr, uint32 Crc_Length, uint64 Crc_StartValue64, boolean Crc_IsFirstCall )
{
    uint64    u8_crc64;                        /* CRC result */
    uint32    u4_counter;                      /* Counter[set to Crc_Length] */
    uint32    u4_position = CRC_DATAPOS_INIT;  /* Crc_DataPtr[u4_position] */
    uint64    u8_StartValue;                   /* Start value */
    uint64    u8_ret;                          /* Return value */

    /* Set parameters */
    u8_StartValue = Crc_StartValue64 ^ (uint64)CRC_CRC64_XOR_VALUE;  /* SWS_Crc_00041 */
    if( Crc_IsFirstCall == (boolean)TRUE )
    {
        u8_StartValue = (uint64)CRC_CRC64_INIT_VALUE;  /* SWS_Crc_00014 */
    }
    u4_counter = Crc_Length;

    /* SWS_Crc_00013 */
    /*                */
    /* CRC_64_TABLE */
    /*                */
    /* SWS_Crc_00014 */
    u8_crc64 = u8_StartValue;

    while( u4_counter > (uint32)CRC_VALUE_ZERO )
    {
        u8_crc64 = Crc_64_Table[(u8_crc64 ^ (uint32)Crc_DataPtr[u4_position]) & (uint32)CRC_MASK_8BIT_LENGTH] ^ (u8_crc64 >> (uint64)CRC_BIT_SHIFT_8);
        u4_position++;
        u4_counter--;
    }
    u8_ret = u8_crc64 ^ (uint64)CRC_CRC64_XOR_VALUE;

    return u8_ret;

}

/****************************************************************************/
/* Function Name    | Crc_GetVersionInfo                                    */
/* Description      | This service returns the version information of this  */
/*                  | module.                                               */
/* Preconditions    | None                                                  */
/* Parameters       | *VersionInfo   : Pointer to the version info.         */
/*                  |                  A caller perform the guarantee       */
/*                  |                  [e.g., DO not be NULL] of the value. */
/* Return Value     | None                                                  */
/* Notes            | SWS_Crc_00021 , SWS_Crc_00017                         */
/****************************************************************************/
/* [lib_SC1-1_crc_0006] */
FUNC(void, CRC_CODE) Crc_GetVersionInfo
/* Implements [lib_SDD1-1_crc_0006] */
( P2VAR(Std_VersionInfoType, AUTOMATIC, CRC_APPL_DATA) Versioninfo )
{
    /* SWS_Crc_00011 , SWS_Crc_00018 */
    Versioninfo->vendorID = CRC_VENDOR_ID;
    Versioninfo->moduleID = CRC_MODULE_ID;
    Versioninfo->sw_major_version = CRC_SW_MAJOR_VERSION;
    Versioninfo->sw_minor_version = CRC_SW_MINOR_VERSION;
    Versioninfo->sw_patch_version = CRC_SW_PATCH_VERSION;
    
    return;
}

#define CRC_STOP_SEC_CODE
#include <Crc_MemMap.h>

/* The following SWS does not need to make the source code.                  */
/* SWS_Crc_00051, SWS_Crc_00033, SWS_Crc_00045                               */
/* SWS_Crc_00009, SWS_Crc_00010, SWS_Crc_00060                               */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2020/12/18                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
