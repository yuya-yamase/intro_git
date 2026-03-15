// ==================================================
//         セクション定義 ( RH850/U2A )
// ==================================================

// ------------------------
// メモリマップ
// ------------------------
MEMORY {
// Address Space:Code flash (User Area 1) (Bank B)
    rom_memory_const    : ORIGIN = 0x0001C000, LENGTH = 0x004000                  //LENGTH:16KB
    vector_core         : ORIGIN = 0x00020000, LENGTH = 0x000200                  //LENGTH:0.5KB
    rom_memory          : ORIGIN = 0x00020200, LENGTH = 0x1EFE00                  //LENGTH:1983.5KB(1984KB-0.5KB)

// Address Space:Local RAM (CPU1)
// ORIGIN = 0xFDA00000, LENGTH = 64K
//  Local RAM (self)    : ORIGIN = 0xFDA00000, LENGTH = 0x4000                    //LENGTH:16KB
    ram_memory_core     : ORIGIN = 0xFDA08000, LENGTH = 0x8000                    //LENGTH:32KB
    ram_end_core        : ORIGIN = 0xFDA10000, LENGTH = 0

// Address Space:Cluster RAM (Cluster0)
    ram_memory_cluster0 : ORIGIN = 0xFE020000, LENGTH = 0x10000                   //LENGTH:64KB
    ram_end_cluster0    : ORIGIN = 0xFE030000, LENGTH = 0

// Address Space:Cluster RAM (Cluster1)
    ram_memory_cluster1 : ORIGIN = 0xFE120000, LENGTH = 0x10000                   //LENGTH:64KB
    ram_end_cluster1    : ORIGIN = 0xFE130000, LENGTH = 0

// Address Space:Cluster RAM (Cluster2 share)
    ram_memory_cluster2_share : ORIGIN = 0xFE430000, LENGTH = 0x10000             //LENGTH:64KB
    ram_end_cluster2_share    : ORIGIN = 0xFE440000, LENGTH = 0

// Address Space:Cluster RAM (Cluster2)
    ram_memory_cluster2 : ORIGIN = 0xFE4C0000, LENGTH = 0x40000                   //LENGTH:256KB
    ram_end_cluster2    : ORIGIN = 0xFE500000, LENGTH = 0

// Address Space:Cluster RAM (Cluster3) (Retention RAM)
    retention_ram       : ORIGIN = 0xFE810000, LENGTH = 0x8000                    //LENGTH:32KB
    retention_ram_end   : ORIGIN = 0xFE818000, LENGTH = 0
}

DEFAULTS {
//1byte (0xFE430000 - 0xFE430100)
//2byte (0xFE430100 - 0xFE430300)
//4byte (0xFE430300 - 0xFE430700)
//Struct

//MET Const Data
    MEMORY_CONST_SIZE = 0x00004000                                 //LENGTH:16kbyte
    MCUCONST_4B_SIZE  = 0x000000F0                                 //LENGTH:240B
    MCUCONST_2B_SIZE  = 0x00000670                                 //LENGTH:1648B
    MCUCONST_1B_SIZE  = 0x00000300                                 //LENGTH:768B
    MEMORY_CONST_ADDR = 0x0001C000                                 //MET_PARAMETER_CONST start address
    MCUCONST_4B_ADDR  = MEMORY_CONST_ADDR                          //4byte start address:0x0001C000
    MCUCONST_2B_ADDR  = MCUCONST_4B_ADDR + MCUCONST_4B_SIZE        //2byte start address:0x0001C0F0
    MCUCONST_1B_ADDR  = MCUCONST_2B_ADDR + MCUCONST_2B_SIZE        //1byte start address:0x0001C760
    MCUCONST_CRC_ADDR = MEMORY_CONST_ADDR + MEMORY_CONST_SIZE - 4  //CRC   start address:0x0001FFFC
}
