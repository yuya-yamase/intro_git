/* Section_ld_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Section/LD                                                  */
/******************************************************************************/

MEMORY
{
	CODEFLASH_1			: ORIGIN = 0x00000000, LENGTH = 112K	/* Code flash(User Area 0)(Bank A) */	/* 250908 changed by EPSW */
	CODEFLASH_1_END		: ORIGIN = 0x0001BFFF, LENGTH = 0K												/* 250908 changed by EPSW */

	CODEFLASH_2			: ORIGIN = 0x08000000, LENGTH = 64K		/* Code flash(User Boot Area 0)(Bank A) */
	CODEFLASH_2_END		: ORIGIN = 0x0800FFFF, LENGTH = 0K

	LRAM				: ORIGIN = 0xFDC00000, LENGTH = 64K		/* Local RAM (CPU0) */
	LRAM_END			: ORIGIN = 0xFDC0FFFF, LENGTH = 0K
	LRAM_END_NEXT		: ORIGIN = 0xFDC10000, LENGTH = 0K

	CRAM				: ORIGIN = 0xFE000000, LENGTH = 512K	/* Cluster RAM (Cluster0) */
	CRAM_END			: ORIGIN = 0xFE07FFFF, LENGTH = 0K
	CRAM_END_NEXT		: ORIGIN = 0xFE080000, LENGTH = 0K
}


DEFAULTS
{
	rpg_rom_1_addr		= 0x00000000;
	rpg_rom_1_size		= 0x00004000;
	rpg_rom_ext_1_addr	= 0x00004000;
	rpg_rom_ext_1_size	= 0x00004000;
	rpg_rom_ext_2_addr	= 0x00008000;
	rpg_rom_ext_2_size	= 0x00004000;
	rpg_rom_2_addr		= 0x0000C000;
	rpg_rom_2_size		= 0x00010000;  /* 250908 changed by EPSW */
	rpg_rom_3_addr		= 0x08000000;
	rpg_rom_3_size		= 0x00010000;

	rpg_ram_1_addr		= 0xFDC00000;
	rpg_ram_1_size		= 0x00008000;
	rpg_ram_2_addr		= 0xFE000000;
	rpg_ram_2_size		= 0x00019000;
	rpg_sbl_addr		= rpg_ram_2_addr;
	rpg_sbl_size		= 0x00001000;

	rpg_stack_size		= 0x2800;
	rpg_userinfo_size	= 0x10;
	rpg_version_size	= 0x20;
	rpg_padspace_size	= 64;
}

SECTIONS
{
.UserAreaRomStart																: > CODEFLASH_1

	/**************************************************************************/
	/* RPRG ROM Area 1                                                        */
	/**************************************************************************/
	.RpgRom1Start						rpg_rom_1_addr							: > .

		/**********************************************************************/
		/* ROM Vector                                                         */
		/**********************************************************************/
		.P_ROM_VECT_FIXED				ALIGN(4)								: > .
		.P_ROM_VECT						ALIGN(0x200)							: > .

		/**********************************************************************/
		/* ROM.Boot.rodata                                                    */
		/**********************************************************************/
		.C_ROM_BOOT						ALIGN(4)								: > .

		.RamCopy1st_CodeFixed_SrcStart	ALIGN(16)								: > .
			.ROM_P_RAM_1ST_FIXED		ROM(.P_RAM_1ST_FIXED)					: > .
			.ROM_P_RAM_1_FIXED_PAD		ROM(.P_RAM_1_FIXED_PAD)					: > .
		.RamCopy1st_CodeFixed_SrcEnd	ALIGN(16)								: > .
		.RamCopy2nd_CodeFixed_SrcStart	ALIGN(16)								: > .
			.ROM_P_CODEFLS				ROM(.P_CODEFLS)							: > .
			.ROM_P_CODEFLS_PAD			ROM(.P_CODEFLS_PAD)						: > .
		.RamCopy2nd_CodeFixed_SrcEnd	ALIGN(16)								: > .

		.RamCopy1st_1_Cst_SrcStart		ALIGN(16)								: > .
			.ROM_C_MCU					ROM(.C_MCU)								: > .
			.ROM_C_WDG					ROM(.C_WDG)								: > .
			.ROM_C_PORT					ROM(.C_PORT)							: > .
			.ROM_C_DIO					ROM(.C_DIO)								: > .
			.ROM_C_GPT					ROM(.C_GPT)								: > .
			.ROM_C_SPI					ROM(.SPI_RODATA_CONST)					: > .
			.ROM_C_CANIC				ROM(.CANIC_RODATA_CONST)				: > .
			.ROM_C_RAM_1ST				ROM(.C_RAM_1ST)							: > .
		.RamCopy1st_1_Cst_SrcEnd		ALIGN(16)								: > .

		.RamCopy2nd_7_Code_SrcStart		ALIGN(16)								: > .
			.ROM_P_RAM_CRC				ROM(.P_RAM_CRC)							: > .
		.RamCopy2nd_7_Code_SrcEnd		ALIGN(16)								: > .

		.RamCopy2nd_1_Cst_SrcStart		ALIGN(16)								: > .
			.ROM_C_CAN					ROM(.C_CAN)								: > .
			.ROM_C_INT					ROM(.C_INT)								: > .
			.ROM_C_ECC					ROM(.C_ECC)								: > .
		.RamCopy2nd_1_Cst_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_2_Cst_SrcStart		ALIGN(16)								: > .
			.ROM_C_RAM_RPGLIB			ROM(.C_RAM_RPGLIB)						: > .
			.ROM_C_RAM_DIAGLIB			ROM(.C_RAM_DIAGLIB)						: > .
			.ROM_C_RAM_COM				ROM(.C_RAM_COM)							: > .
			.ROM_C_RAM_MEM				ROM(.C_RAM_MEM)							: > .
		.RamCopy2nd_2_Cst_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_7_Cst_SrcStart		ALIGN(16)								: > .
			.ROM_C_RAM_CRC				ROM(.C_RAM_CRC)							: > .
		.RamCopy2nd_7_Cst_SrcEnd		ALIGN(16)								: > .

		/**********************************************************************/
		/* Reserve the last 16 bytes                                          */
		/**********************************************************************/
		.ROM_1_USERINFO					rpg_rom_1_addr + rpg_rom_1_size - rpg_userinfo_size		\
										PAD(rpg_userinfo_size)					: > .

	.RpgRom1End							rpg_rom_1_addr + rpg_rom_1_size - 1		: > .

	/**************************************************************************/
	/* RPRG ROM Expansion area                                                */
	/**************************************************************************/
	.RpgRomExt1Start					rpg_rom_ext_1_addr						: > .
	.RpgRomExt1End						rpg_rom_ext_1_addr + rpg_rom_ext_1_size - 1	: > .

	.RpgRomExt2Start					rpg_rom_ext_2_addr						: > .
	.RpgRomExt2End						rpg_rom_ext_2_addr + rpg_rom_ext_2_size - 1	: > .

	/**************************************************************************/
	/* RPRG ROM Area 2                                                        */
	/**************************************************************************/
	.RpgRom2Start						rpg_rom_2_addr							: > .

		/**********************************************************************/
		/* ROM.Boot.text                                                      */
		/**********************************************************************/
		.P_ROM_BOOT						ALIGN(4)								: > .
		.P_ROM_BOOT1					ALIGN(4)								: > .

		.RamCopy2nd_CstFixed_SrcStart	ALIGN(16)								: > .
			.ROM_rosdata				ROM(.rosdata)							: > .
			.ROM_C_CODEFLS				ROM(.C_CODEFLS)							: > .
		.RamCopy2nd_CstFixed_SrcEnd		ALIGN(16)								: > .

		.RamCopy2nd_4_Code_SrcStart		ALIGN(16)								: > .
			.ROM_P_RAM_2ND				ROM(.P_RAM_2ND)							: > .
		.RamCopy2nd_4_Code_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_5_Code_SrcStart		ALIGN(16)								: > .
			.ROM_P_RAM_DECRYPT			ROM(.P_RAM_DECRYPT)						: > .
			.ROM_P_RAM_CMPDECMP			ROM(.P_RAM_CMPDECMP)					: > .
			.ROM_P_RAM_FSCDTCT			ROM(.P_RAM_FSCDTCT)						: > .
			.ROM_P_RAM_PRGCHK			ROM(.P_RAM_PRGCHK)						: > .
			.ROM_P_RAM_SEC				ROM(.P_RAM_SEC)							: > .
			.ROM_P_RAM_VEHINF			ROM(.P_RAM_VEHINF)						: > .
			.ROM_P_RAM_RPGMFR			ROM(.P_RAM_RPGMFR)						: > .
			.ROM_P_RAM_RPGSPP			ROM(.P_RAM_RPGSPP)						: > .
			.ROM_P_RAM_RPGEVTHK			ROM(.P_RAM_RPGEVTHK)					: > .
		.RamCopy2nd_5_Code_SrcEnd		ALIGN(16)								: > .

		.RamCopy2nd_3_Cst_SrcStart		ALIGN(16)								: > .
			.ROM_C_RAM_GDN				ROM(.C_RAM_GDN)							: > .
		.RamCopy2nd_3_Cst_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_4_Cst_SrcStart		ALIGN(16)								: > .
			.ROM_C_RAM_2ND				ROM(.C_RAM_2ND)							: > .
		.RamCopy2nd_4_Cst_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_5_Cst_SrcStart		ALIGN(16)								: > .
			.ROM_C_RAM_DECRYPT			ROM(.C_RAM_DECRYPT)						: > .
			.ROM_C_RAM_CMPDECMP			ROM(.C_RAM_CMPDECMP)					: > .
			.ROM_C_RAM_FSCDTCT			ROM(.C_RAM_FSCDTCT)						: > .
			.ROM_C_RAM_PRGCHK			ROM(.C_RAM_PRGCHK)						: > .
			.ROM_C_RAM_SEC				ROM(.C_RAM_SEC)							: > .
			.ROM_C_RAM_VEHINF			ROM(.C_RAM_VEHINF)						: > .
			.ROM_C_RAM_RPGMFR			ROM(.C_RAM_RPGMFR)						: > .
			.ROM_C_RAM_RPGSPP			ROM(.C_RAM_RPGSPP)						: > .
			.ROM_C_RAM_RPGEVTHK			ROM(.C_RAM_RPGEVTHK)					: > .
		.RamCopy2nd_5_Cst_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_6_Cst_SrcStart		ALIGN(16)								: > .
			.ROM_C_RAM_DIAGSRV			ROM(.C_RAM_DIAGSRV)						: > .
		.RamCopy2nd_6_Cst_SrcEnd		ALIGN(16)								: > .

		/**********************************************************************/
		/* ROM.text                                                           */
		/**********************************************************************/
		.P_ROM							ALIGN(4)								: > .
		.P_ROM_CSM						ALIGN(4)								: > .
		.P_ROM_CSM_SCHM					ALIGN(4)								: > .
		.P_ROM_CRYIF					ALIGN(4)								: > .
		.P_ROM_CRYPTO					ALIGN(4)								: > .
		.P_ROM_WRAPCRYPTO				ALIGN(4)								: > .
		.Crypto_83_sw_AES128_text		ALIGN(4)								: > .
		.Crypto_83_sw_RSA_text			ALIGN(4)								: > .
		.Crypto_83_sw_SHA256_text		ALIGN(4)								: > .
			/******************************************************************/
			/* Please add a user section(ROM.text)                            */
			/******************************************************************/

		/**********************************************************************/
		/* ROM.rodata                                                         */
		/**********************************************************************/
		.C_ROM_CSM_SHARED				ALIGN(16)								: > .
		.C_ROM							ALIGN(4)								: > .
		.C_ROM_DIAGSRV_ENCRYPTION_FLAG	ALIGN(4)								: > .
		.C_ROM_CSM						ALIGN(4)								: > .
		.C_ROM_CRYPTO					ALIGN(4)								: > .
		.C_ROM_WRAPCRYPTO				ALIGN(4)								: > .
		.C_ROM_SEC_KEY					ALIGN(4)								: > .
		.C_ROM_DECRYPT_KEY				ALIGN(4)								: > .
		.C_ROM_FSCDTCT_KEY				ALIGN(4)								: > .
		.Crypto_83_sw_AES128_const		ALIGN(4)								: > .
		.Crypto_83_sw_RSA_const			ALIGN(4)								: > .
		.Crypto_83_sw_SHA256_const		ALIGN(4)								: > .
			/******************************************************************/
			/* Please add a user section(ROM.rodata)                          */
			/******************************************************************/

		.RamCopy1st_2_Code_SrcStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.text)                            */
			/******************************************************************/
			.ROM_P_RAM_1_PAD			ROM(.P_RAM_1_PAD)						: > .
		.RamCopy1st_2_Code_SrcEnd		ALIGN(16)								: > .
		.RamCopy1st_2_Cst_SrcStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.rosdata)                         */
			/******************************************************************/
		.RamCopy1st_2_Cst_SrcEnd		ALIGN(16)								: > .
		.RamCopy1st_1_Cst2_SrcStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.rodata)                          */
			/******************************************************************/
		.RamCopy1st_1_Cst2_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_1_Cst2_SrcStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.rodata)                          */
			/******************************************************************/
			.ROM_rodata					ROM(.rodata)							: > .
		.RamCopy2nd_1_Cst2_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_8_Code_SrcStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.text)                            */
			/******************************************************************/
			.ROM_text					ROM(.text)								: > .
			.ROM_P_RAM_2_PAD			ROM(.P_RAM_2_PAD)						: > .
		.RamCopy2nd_8_Code_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_8_Cst_SrcStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.rosdata)                         */
			/******************************************************************/
		.RamCopy2nd_8_Cst_SrcEnd		ALIGN(16)								: > .

#if (REPROG_CFG_SBL_TYPE_WITHIN == 1)
		.RamCopy2nd_Sbl_SrcStart		ALIGN(16)								: > .
			.ROM_P_CODEFLS_NORESIDE		ROM(.P_CODEFLS_NORESIDE)				: > .
			.ROM_P_RAM_NORESIDE			ROM(.P_RAM_NORESIDE)					: > .
			/******************************************************************/
			/* Please add a user section(SBL.text)                            */
			/******************************************************************/
			.ROM_P_RAM_SBL_PAD			ROM(.P_RAM_SBL_PAD)						: > .
		.RamCopy2nd_Sbl_SrcEnd			ADDR(.RamCopy2nd_Sbl_SrcStart) + rpg_sbl_size	: > .
#endif

		/**********************************************************************/
		/* Reserve the last 16 bytes                                          */
		/**********************************************************************/
		.ROM_2_USERINFO					rpg_rom_2_addr + rpg_rom_2_size - rpg_userinfo_size		\
										PAD(rpg_userinfo_size)					: > .

	.RpgRom2End							rpg_rom_2_addr + rpg_rom_2_size - 1		: > .

.UserAreaRomEnd																	: > CODEFLASH_1_END

.UserBootAreaRomStart															: > CODEFLASH_2

	/**************************************************************************/
	/* RPRG ROM Area 3                                                        */
	/**************************************************************************/
	.RpgRom3Start						rpg_rom_3_addr							: > .

		/**********************************************************************/
		/* ROM Vector                                                         */
		/**********************************************************************/
		.P_ROM_VECT_USERBOOT			ALIGN(4)								: > .

		.ROM_P_RAM_VECT					ROM(.P_RAM_VECT)						: > .

		.RamCopy1st_1_Code_SrcStart		ALIGN(16)								: > .
			.ROM_P_MCU					ROM(.P_MCU)								: > .
			.ROM_P_WDG					ROM(.P_WDG)								: > .
			.ROM_P_PORT					ROM(.P_PORT)							: > .
			.ROM_P_DIO					ROM(.P_DIO)								: > .
			.ROM_P_GPT					ROM(.P_GPT)								: > .
			.ROM_P_SPI					ROM(.SPI_TEXT_CODE)						: > .
			.ROM_P_CANIC				ROM(.CANIC_TEXT_CODE)					: > .
			.ROM_P_RAM_1ST				ROM(.P_RAM_1ST)							: > .
		.RamCopy1st_1_Code_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_1_Code_SrcStart		ALIGN(16)								: > .
			.ROM_P_CAN					ROM(.P_CAN)								: > .
			.ROM_P_INT					ROM(.P_INT)								: > .
			.ROM_P_ECC					ROM(.P_ECC)								: > .
		.RamCopy2nd_1_Code_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_2_Code_SrcStart		ALIGN(16)								: > .
			.ROM_P_RAM_RPGLIB			ROM(.P_RAM_RPGLIB)						: > .
			.ROM_P_RAM_DIAGLIB			ROM(.P_RAM_DIAGLIB)						: > .
			.ROM_P_RAM_COM				ROM(.P_RAM_COM)							: > .
			.ROM_P_RAM_MEM				ROM(.P_RAM_MEM)							: > .
		.RamCopy2nd_2_Code_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_3_Code_SrcStart		ALIGN(16)								: > .
			.ROM_P_RAM_GDN				ROM(.P_RAM_GDN)							: > .
		.RamCopy2nd_3_Code_SrcEnd		ALIGN(16)								: > .
		.RamCopy2nd_6_Code_SrcStart		ALIGN(16)								: > .
			.ROM_P_RAM_DIAGSRV			ROM(.P_RAM_DIAGSRV)						: > .
		.RamCopy2nd_6_Code_SrcEnd		ALIGN(16)								: > .

		.secinfo						ALIGN(4)								: > .

		/**********************************************************************/
		/* Version                                                            */
		/**********************************************************************/
		.C_ROM_VER						rpg_rom_3_addr + rpg_rom_3_size - rpg_userinfo_size - rpg_version_size	: > .

		/**********************************************************************/
		/* Reserve the last 16 bytes                                          */
		/**********************************************************************/
		.ROM_3_USERINFO					rpg_rom_3_addr + rpg_rom_3_size - rpg_userinfo_size		\
										PAD(rpg_userinfo_size)					: > .

	.RpgRom3End							rpg_rom_3_addr + rpg_rom_3_size - 1		: > .

.UserBootAreaRomEnd																: > CODEFLASH_2_END

.LocalRamStart																	: > LRAM
	/**************************************************************************/
	/* RPRG RAM Area 1                                                        */
	/**************************************************************************/
	.RpgRam1Start						rpg_ram_1_addr							: > .
		/**********************************************************************/
		/* Ram.Vector                                                         */
		/**********************************************************************/
		.P_RAM_VECT						ALIGN(0x200)							: > .

		/**********************************************************************/
		/* Fix offset from sda for SBL compatibility                          */
		/**********************************************************************/
		.sdabase						ALIGN(4)								: > .
		.Ram2nd_B_Fixed_Start			ALIGN(16)								: > .
			.B_CODEFLS					ALIGN(4)								: > .
		.Ram2nd_B_Fixed_End				ALIGN(16)								: > .

		/**********************************************************************/
		/* (Before clock up) .sbss                                            */
		/**********************************************************************/
		.Ram1st_1_B_Start				ALIGN(16)								: > .
			.B_MCU						ALIGN(4)								: > .
			.B_WDG						ALIGN(4)								: > .
			.B_PORT						ALIGN(4)								: > .
			.B_DIO						ALIGN(4)								: > .
			.B_GPT						ALIGN(4)								: > .
			.bss_SHARE_SPI_MODEA_CHANNELDATA	ALIGN(4)						: > .
			.CANIC_BSS_VAR_NO_INIT		ALIGN(4)								: > .
			.B_RAM_1ST					ALIGN(4)								: > .
		.Ram1st_1_B_End					ALIGN(16)								: > .
		.Ram1st_2_B_Start				ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.sbss)                            */
			/******************************************************************/
		.Ram1st_2_B_End					ALIGN(16)								: > .

		/**********************************************************************/
		/* (After clock up) .sbss                                             */
		/**********************************************************************/
		.Ram2nd_1_B_Start				ALIGN(16)								: > .
			.B_CAN						ALIGN(4)								: > .
			.B_INT						ALIGN(4)								: > .
			.B_ECC						ALIGN(4)								: > .
			.B_RAM_2ND					ALIGN(4)								: > .
			.B_RAM_RPGLIB				ALIGN(4)								: > .
			.B_RAM_DIAGLIB				ALIGN(4)								: > .
			.B_RAM_DIAGSRV				ALIGN(4)								: > .
			.B_RAM_DECRYPT				ALIGN(4)								: > .
			.B_RAM_CMPDECMP				ALIGN(4)								: > .
			.B_RAM_FSCDTCT				ALIGN(4)								: > .
			.B_RAM_PRGCHK				ALIGN(4)								: > .
			.B_RAM_SEC					ALIGN(4)								: > .
			.B_RAM_VEHINF				ALIGN(4)								: > .
			.B_RAM_RPGMFR				ALIGN(4)								: > .
			.B_RAM_RPGSPP				ALIGN(4)								: > .
			.B_RAM_RPGEVTHK				ALIGN(4)								: > .
		.Ram2nd_1_B_End					ALIGN(16)								: > .
		.Ram2nd_2_B_Start				ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(.sbss)                               */
			/******************************************************************/
			.sbss						ALIGN(4)								: > .
		.Ram2nd_2_B_End					ALIGN(16)								: > .

		/**********************************************************************/
		/* Fix offset from sda for SBL compatibility                          */
		/**********************************************************************/
		.RamCopy2nd_CstFixed_DstStart	ALIGN(16)								: > .
			.rosdata					ALIGN(4)								: > .
			.C_CODEFLS					ALIGN(4)								: > .
		.RamCopy2nd_CstFixed_DstEnd		ALIGN(16)								: > .

		/**********************************************************************/
		/* ROM->RAM(Before clock up) .rosdata                                 */
		/**********************************************************************/
		.RamCopy1st_1_Cst_DstStart		ALIGN(16)								: > .
			.C_MCU						ALIGN(4)								: > .
			.C_WDG						ALIGN(4)								: > .
			.C_PORT						ALIGN(4)								: > .
			.C_DIO						ALIGN(4)								: > .
			.C_GPT						ALIGN(4)								: > .
			.SPI_RODATA_CONST			ALIGN(4)								: > .
			.CANIC_RODATA_CONST			ALIGN(4)								: > .
			.C_RAM_1ST					ALIGN(4)								: > .
		.RamCopy1st_1_Cst_DstEnd		ALIGN(16)								: > .
		.RamCopy1st_2_Cst_DstStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.rosdata)                         */
			/******************************************************************/
		.RamCopy1st_2_Cst_DstEnd		ALIGN(16)								: > .

		/**********************************************************************/
		/* ROM->RAM(After clock up) .rosdata                                  */
		/**********************************************************************/
		.RamCopy2nd_1_Cst_DstStart		ALIGN(16)								: > .
			.C_CAN						ALIGN(4)								: > .
			.C_INT						ALIGN(4)								: > .
			.C_ECC						ALIGN(4)								: > .
		.RamCopy2nd_1_Cst_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_2_Cst_DstStart		ALIGN(16)								: > .
			.C_RAM_RPGLIB				ALIGN(4)								: > .
			.C_RAM_DIAGLIB				ALIGN(4)								: > .
			.C_RAM_COM					ALIGN(4)								: > .
			.C_RAM_MEM					ALIGN(4)								: > .
		.RamCopy2nd_2_Cst_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_3_Cst_DstStart		ALIGN(16)								: > .
			.C_RAM_GDN					ALIGN(4)								: > .
		.RamCopy2nd_3_Cst_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_4_Cst_DstStart		ALIGN(16)								: > .
			.C_RAM_2ND					ALIGN(4)								: > .
		.RamCopy2nd_4_Cst_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_5_Cst_DstStart		ALIGN(16)								: > .
			.C_RAM_DECRYPT				ALIGN(4)								: > .
			.C_RAM_CMPDECMP				ALIGN(4)								: > .
			.C_RAM_FSCDTCT				ALIGN(4)								: > .
			.C_RAM_PRGCHK				ALIGN(4)								: > .
			.C_RAM_SEC					ALIGN(4)								: > .
			.C_RAM_VEHINF				ALIGN(4)								: > .
			.C_RAM_RPGMFR				ALIGN(4)								: > .
			.C_RAM_RPGSPP				ALIGN(4)								: > .
			.C_RAM_RPGEVTHK				ALIGN(4)								: > .
		.RamCopy2nd_5_Cst_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_6_Cst_DstStart		ALIGN(16)								: > .
			.C_RAM_DIAGSRV				ALIGN(4)								: > .
		.RamCopy2nd_6_Cst_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_7_Cst_DstStart		ALIGN(16)								: > .
			.C_RAM_CRC					ALIGN(4)								: > .
		.RamCopy2nd_7_Cst_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_8_Cst_DstStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.rosdata)                         */
			/******************************************************************/
		.RamCopy2nd_8_Cst_DstEnd		ALIGN(16)								: > .

		/**********************************************************************/
		/* Stack                                                              */
		/**********************************************************************/
		.RpgStackLow					ALIGN(4)	PAD(rpg_stack_size)			: > .
		.RpgStackHigh					ALIGN(4)								: > .

		.tdata							ALIGN(4)								: > .

	.RpgRam1End							rpg_ram_1_addr + rpg_ram_1_size			: > .

.LocalRamEnd																	: > LRAM_END
.LocalRamEndNext																: > LRAM_END_NEXT

.Cluster0RamStart																: > CRAM
	/**************************************************************************/
	/* RPRG RAM Area 2                                                        */
	/**************************************************************************/
	.RpgRam2Start						rpg_ram_2_addr							: > .
		/**********************************************************************/
		/* SBL.text                                                           */
		/**********************************************************************/
		.RamCopy2nd_Sbl_DstStart		rpg_sbl_addr							: > .
			.P_CODEFLS_NORESIDE			ALIGN(16)								: > .
			.P_RAM_NORESIDE				ALIGN(4)								: > .
			/******************************************************************/
			/* Please add a user section(SBL.text)                            */
			/******************************************************************/
			.P_RAM_SBL_PAD				MIN_SIZE(rpg_padspace_size)				: > .
		.RamCopy2nd_Sbl_DstEnd			rpg_sbl_addr + rpg_sbl_size				: > .

		/**********************************************************************/
		/* Fix the address to maintain SBL compatibility                      */
		/**********************************************************************/
		.RamCopy1st_CodeFixed_DstStart	ALIGN(16)								: > .
			.P_RAM_1ST_FIXED			ALIGN(4)								: > .
			.P_RAM_1_FIXED_PAD			MIN_SIZE(rpg_padspace_size)				: > .
		.RamCopy1st_CodeFixed_DstEnd	ALIGN(16)								: > .
		.RamCopy2nd_CodeFixed_DstStart	ALIGN(16)								: > .
			.P_CODEFLS					ALIGN(16)								:
										{ CodeFls.lib(*(.P_CODEFLS)) CodeFls_usr.rel.o(.P_CODEFLS) } > .
			.P_CODEFLS_PAD				MIN_SIZE(rpg_padspace_size)				: > .
		.RamCopy2nd_CodeFixed_DstEnd	ALIGN(16)								: > .

		/**********************************************************************/
		/* Ram.text(Before clock up)                                          */
		/**********************************************************************/
		.RamCopy1st_1_Code_DstStart		ALIGN(16)								: > .
			.P_MCU						ALIGN(16)								: > .
			.P_WDG						ALIGN(4)								: > .
			.P_PORT						ALIGN(4)								: > .
			.P_DIO						ALIGN(4)								: > .
			.P_GPT						ALIGN(4)								: > .
			.SPI_TEXT_CODE				ALIGN(4)								: > .
			.CANIC_TEXT_CODE			ALIGN(4)								: > .
			.P_RAM_1ST					ALIGN(4)								: > .
		.RamCopy1st_1_Code_DstEnd		ALIGN(16)								: > .
		.RamCopy1st_2_Code_DstStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.text)                            */
			/******************************************************************/
			.P_RAM_1_PAD				MIN_SIZE(rpg_padspace_size)				: > .
		.RamCopy1st_2_Code_DstEnd		ALIGN(16)								: > .

		/**********************************************************************/
		/* Ram.text(After clock up)                                           */
		/**********************************************************************/
		.RamCopy2nd_1_Code_DstStart		ALIGN(16)								: > .
			.P_CAN						ALIGN(16)								: > .
			.P_INT						ALIGN(4)								: > .
			.P_ECC						ALIGN(4)								: > .
		.RamCopy2nd_1_Code_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_2_Code_DstStart		ALIGN(16)								: > .
			.P_RAM_RPGLIB				ALIGN(4)								: > .
			.P_RAM_DIAGLIB				ALIGN(4)								: > .
			.P_RAM_COM					ALIGN(4)								: > .
			.P_RAM_MEM					ALIGN(4)								: > .
		.RamCopy2nd_2_Code_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_3_Code_DstStart		ALIGN(16)								: > .
			.P_RAM_GDN					ALIGN(4)								: > .
		.RamCopy2nd_3_Code_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_4_Code_DstStart		ALIGN(16)								: > .
			.P_RAM_2ND					ALIGN(4)								: > .
		.RamCopy2nd_4_Code_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_5_Code_DstStart		ALIGN(16)								: > .
			.P_RAM_DECRYPT				ALIGN(4)								: > .
			.P_RAM_CMPDECMP				ALIGN(4)								: > .
			.P_RAM_FSCDTCT				ALIGN(4)								: > .
			.P_RAM_PRGCHK				ALIGN(4)								: > .
			.P_RAM_SEC					ALIGN(4)								: > .
			.P_RAM_VEHINF				ALIGN(4)								: > .
			.P_RAM_RPGMFR				ALIGN(4)								: > .
			.P_RAM_RPGSPP				ALIGN(4)								: > .
			.P_RAM_RPGEVTHK				ALIGN(4)								: > .
		.RamCopy2nd_5_Code_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_6_Code_DstStart		ALIGN(16)								: > .
			.P_RAM_DIAGSRV				ALIGN(4)								: > .
		.RamCopy2nd_6_Code_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_7_Code_DstStart		ALIGN(16)								: > .
			.P_RAM_CRC					ALIGN(4)								: > .
		.RamCopy2nd_7_Code_DstEnd		ALIGN(16)								: > .
		.RamCopy2nd_8_Code_DstStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.text)                            */
			/******************************************************************/
			.text						ALIGN(4)								: > .
			.P_RAM_2_PAD				MIN_SIZE(rpg_padspace_size)				: > .
		.RamCopy2nd_8_Code_DstEnd		ALIGN(16)								: > .

		/**********************************************************************/
		/* (Before clock up) .bss                                             */
		/**********************************************************************/
		.Ram1st_1_B2_Start				ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.bss)                             */
			/******************************************************************/
		.Ram1st_1_B2_End				ALIGN(16)								: > .

		/**********************************************************************/
		/* (After clock up) .bss                                              */
		/**********************************************************************/
		.Ram2nd_1_B2_Start				ALIGN(16)								: > .
			.B_RAM_CSM_SHARED			ALIGN(16)								: > .
			.B_RAM_CRYIF_SHARED			ALIGN(16)								: > .
			.B_RAM_DIAGSRV_SEED_SHARED	ALIGN(16)								: > .
			.B_RAM_DIAGSRV_KEY_SHARED	ALIGN(16)								: > .
			.B_RAM_DIAGSRV_NONCE_SHARED	ALIGN(16)								: > .
			.B_RAM_DECRYPT_CIPHER_SHARED	ALIGN(16)							: > .
			.B_RAM_DECRYPT_PLAIN_SHARED	ALIGN(16)								: > .
			.B_RAM_DECRYPT_PLAINSIZE_SHARED	ALIGN(16)							: > .
			.B_RAM_FSCDTCT_SIGTARGET_SHARED	ALIGN(16)							: > .
			.B_RAM_FSCDTCT_SIGDATA_SHARED	ALIGN(16)							: > .
			.B_RAM_SEC_ENCRYPTSIZE_SHARED	ALIGN(16)							: > .
			.B_RAM_WRAPCRYPTO_SIGVERIFY_RET_SHARED		ALIGN(16)				: > .
			.B_RAM_SEC_RANDOMSEED_SHARED	ALIGN(16)							: > .	/* Sample(See Sec.c) */
			.B_RAM_SEC_RANDOMSIZE_SHARED	ALIGN(16)							: > .	/* Sample(See Sec.c) */
			.B_RAM_WRAPCRYPTO_DECRYPT_DUMMYBUFF_SHARED	ALIGN(16)				: > .	/* Sample(See WrapCrypto_Decrypt.c) */
			.B_RAM_WRAPCRYPTO_DECRYPT_DUMMYSIZE_SHARED	ALIGN(16)				: > .	/* Sample(See WrapCrypto_Decrypt.c) */
			.B_RAM_2ND_LARGE			ALIGN(4)								: > .
			.B_RAM_CMPDECMP_LARGE		ALIGN(4)								: > .
			.B_RAM_CSM					ALIGN(4)								: > .
			.B_RAM_CRYPTO				ALIGN(4)								: > .
			.B_RAM_WRAPCRYPTO			ALIGN(4)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.bss)                             */
			/******************************************************************/
			.bss						ALIGN(4)								: > .
		.Ram2nd_1_B2_End				ALIGN(16)								: > .

		/**********************************************************************/
		/* ROM->RAM(Before clock up) .rodata                                  */
		/**********************************************************************/
		.RamCopy1st_1_Cst2_DstStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.rodata)                          */
			/******************************************************************/
		.RamCopy1st_1_Cst2_DstEnd		ALIGN(16)								: > .

		/**********************************************************************/
		/* (After clock up) RAM.rodata                                        */
		/**********************************************************************/
		.RamCopy2nd_1_Cst2_DstStart		ALIGN(16)								: > .
			/******************************************************************/
			/* Please add a user section(RAM.rodata)                          */
			/******************************************************************/
			.rodata						ALIGN(4)								: > .
		.RamCopy2nd_1_Cst2_DstEnd		ALIGN(16)								: > .

	.RpgRam2End							rpg_ram_2_addr + rpg_ram_2_size			: > .

.Cluster0RamEnd																	: > CRAM_END
.Cluster0RamEndNext																: > CRAM_END_NEXT
}

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

