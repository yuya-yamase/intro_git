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
	ROM1				: ORIGIN = 0x00000000, LENGTH =	 8M
	ROM1_END			: ORIGIN = 0x007FFFFF, LENGTH =	 0K

	LOCAL_RAM_CPU0		: ORIGIN = 0xFDC00000, LENGTH =	64K
	LOCAL_RAM_CPU0_END	: ORIGIN = 0xFDC0FFFF, LENGTH =	 0K

}


DEFAULTS
{
	apl_version_size		=	  0x18;
	apl_jump_addr			=	  0x007BFDF8;	/* 250908 changed by EPSW */
}

SECTIONS
{
	/* Rom */
	.Rom1Start							ALIGN(4)						: > ROM1
		.APL_VERSION					(apl_jump_addr - apl_version_size)	: > .
		.APL_JUMPADDR					(apl_jump_addr)					: > .

	.Rom1End															: > ROM1_END

	/* Ram */
	.LocalRamStart						ALIGN(4)						: > LOCAL_RAM_CPU0
		.sdabase						ALIGN(4)						: > .
		.rosdata						ALIGN(4)						: > .
		.tdata							ALIGN(4)						: > .
	.LocalRamEnd														: > LOCAL_RAM_CPU0_END

}

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Data       :Description                                      */
/*  v1.00       :2021/MM/DD :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

